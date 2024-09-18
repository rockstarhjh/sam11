/*
@ 만든이: 기마책사
@ UPDATE: '18.11.6
@ UPDATE: '18.11.27  / 변경내용: 게임시작시에는 발동안하게 수정
@ UPDATE: '19.1.4    / 변경내용: 풍향설정 및 화계확산효과 추가 
@ UPDATE: '19.1.19   / 변경내용: 도시특산효과 추가
@ UPDATE: '19.1.22   / 변경내용: 무장출신주효과 추가
@ UPDATE: '19.2.3    / 변경내용: 무장출신주효과 NPC부대 제외조건 추가
@ UPDATE: '19.2.7    / 변경내용: 무장출신주효과 설정용 변수설정 오류 수정
@ UPDATE: '19.2.16   / 변경내용: 대화표시확률 추가
@ UPDATE: '19.2.19   / 변경내용: 도시특산효과에 회복한계값 설정 추가
@ UPDATE: '19.3.10   / 변경내용: 수상부대휩쓸림 삭제 (PK2.1 기본제공 패치 사용 바람)
@ UPDATE: '20.8.26   / 변경내용: 화계확산효과 오류 수정, 캠페인에서는 스크립트 동작안하도록 수정
*/

namespace 야전부대효과
{
    
    //---------------------------------------------------------------------------------------
    // 유저 설정 (true = on, false = off)
    const bool 대화표시설정 = true;   // 야전부대 효과의 대화 표시 여부 설정
    const int  대화표시확률 = 30;     // 야전부대 효과의 상시대화 확률 설정
    
    const bool 야전포위효과 = true;   // 포위당한 부대는 매턴 기력 감소
    const bool 야전계절효과 = true;   // 계절에 따라 부대기력 감소
    const bool 야전지형설정 = true;   // 지형에 따라 부대기력 감소
    const bool 야전탈영설정 = true;   // 기력 저조 부대 병력 감소 적용
    
    const bool 화계확산효과 = true;    // 매턴 바람방향에 따른 화계 확산 효과
    const int  화계확산확률 = 50;
    const bool 풍향메세지표시 = true;
    
    const bool 도시특산효과 = true;    // 부대병과가 소속도시의 특산병종과 일치하면 부대기력 증가
    const bool 무장출신주효과 = true;   // 무장의 출신(주)와 소속도시의 주 일치 시 부대기력 증가
    
    //---------------------------------------------------------------------------------------
    
    
	class Main
	{
       
		Main()
		{
            pk::bind(103, pk::trigger103_t(onGameInit));
			pk::bind(107, pk::trigger107_t(onNewDay));
            
            pk::bind(120, pk::trigger120_t(onDrawGame));
		}

		void onNewDay()
		{
            if (pk::is_campaign()) return;
            
            // 게임시작시에는 발동안함
            if (pk::get_elapsed_days() <= 0) return;
            
			auto list = pk::list_to_array(pk::get_unit_list());
			for (int i = 0; i < int(list.length); i++)
			{
				pk::unit@ unit = list[i];
                pk::point pos = unit.get_pos();
                pk::hex@ hex = pk::get_hex(pos);    // 부대의 좌표
                
                
                // 야전부대별 효과적용 함수 호출
                // 함수 마지막을 true/false 설정에 따라 효과 on/off 설정 가능
                func_야전_포위(unit, pos, hex, 야전포위효과);
                func_야전_계절(unit, pos, hex, 야전계절효과);
                func_야전_지형(unit, pos, hex, 야전지형설정);
                func_야전_탈영(unit, pos, hex, 야전탈영설정);
                
                func_도시특산효과(unit, pos, 도시특산효과);
                func_무장출신주효과(unit, pos, 무장출신주효과);
            }
            
            func_화계확산효과(화계확산효과);
        }
        
        
        bool wind_init;
        int  wind_dir;
        
        void onGameInit()
        {
            if (pk::is_campaign()) return;
            
            main.wind_init = true;
            main.wind_dir = pk::rand(방향_끝);
            
            show_log_wind_dir(main.wind_dir);
        }
        
        void onDrawGame()
		{
            if (pk::is_campaign()) return;
            
            if (화계확산효과)
            {
                string wind_name = get_wind_name(main.wind_dir);
                pk::draw_text(pk::encode(wind_name), pk::point(250, 45), 0xffffffff, FONT_BIG, 0xff000000);
            }
        }
        
        
        //---------------------------------------------------------------------------------------
        // 혈로특기 없는 부대가 포위당한 경우 기력 데미지 발생 ('18.10.24)
        void func_야전_포위(pk::unit@ unit, pk::point pos, pk::hex@ hex, bool 효과적용)
        {
            if (효과적용)
            {
                    
                int cnt_enemy = 0;
                array<pk::point> arr = pk::range(pos, 1, 1);
                for (int j = 0; j < int(arr.length); j++)
                {
                    pk::unit@ target_unit = pk::get_unit(arr[j]);
                    if (target_unit !is null and pk::is_enemy(unit, target_unit))
                    {
                        cnt_enemy += 1; 
                    }
                }
                if ((cnt_enemy >= 3) and !unit.has_skill(특기_혈로))
                {
                    pk::add_energy(unit, -(2 + cnt_enemy), true);      // 포위당하면 기력 -5 이상
                    
                    if (대화표시설정 and pk::is_in_screen(pos))
                        pk::say(pk::encode("어서 포위망을 돌파하라"), pk::get_person(unit.leader));
                    
                }
                
            }
        }
        
        //---------------------------------------------------------------------------------------
        // 혹서/혹한 계절 시 매턴 기력 저하 효과
        void func_야전_계절(pk::unit@ unit, pk::point pos, pk::hex@ hex, bool 효과적용)
        {
            int energy_damage = -1;     // 매턴 야전부대 기력저하 기본

            if (효과적용)
            {
              
                int unit_tekisei = pk::get_tekisei(unit);
                switch(pk::get_season())
                {
                    case 계절_여름 :         // 1.여름 : 턴별 A기준 적성차 만큼 감소
                        energy_damage = energy_damage + unit_tekisei - 적성_A -1;
                        
                        if (대화표시설정 and pk::rand_bool(대화표시확률) and pk::is_in_screen(pos))  // 화면 안 부대만 대화 표시
                        {
                            switch (pk::rand(4))
                            {
                                case 0: pk::say(pk::encode("혹서기에는 병사들이 지치는군"), pk::get_person(unit.leader)); break;
                                case 1: pk::say(pk::encode("더위를 먹었나"), pk::get_person(unit.leader)); break;
                                case 2: pk::say(pk::encode("햇살이 너무 따갑다"), pk::get_person(unit.leader)); break;
                                case 3: pk::say(pk::encode("목이 타들어 가는구나"), pk::get_person(unit.leader)); break;
                            }
                        }
                        break;
                        
                    case 계절_겨울:         // 3.겨울 : 턴별 S기준 적성차 + 1 만큼 감소
                        energy_damage = energy_damage + unit_tekisei - 적성_S -1;
                        
                        if (대화표시설정 and pk::rand_bool(대화표시확률) and pk::is_in_screen(pos))  // 화면 안 부대만 대화 표시
                        {
                            switch (pk::rand(4))
                            {
                                case 0: pk::say(pk::encode("혹한기에는 병사들이 지치는군"), pk::get_person(unit.leader)); break;
                                case 1: pk::say(pk::encode("추위를 타는군"), pk::get_person(unit.leader)); break;
                                case 2: pk::say(pk::encode("찬 바람이 매섭다"), pk::get_person(unit.leader)); break;
                                case 3: pk::say(pk::encode("얼어 죽을 것 같다"), pk::get_person(unit.leader)); break;
                            }
                        }
                        break;
                }
            }
            
            // 기력 감소 처리
            pk::add_energy(unit, energy_damage, true);   
            
        }
             
        //---------------------------------------------------------------------------------------  
        void func_야전_지형(pk::unit@ unit, pk::point pos, pk::hex@ hex, bool 효과적용)
        {   
            if (효과적용)
            {        
                // 부대가 산악 행군 시 매턴 기력 -2
                if (hex.terrain == 지형_산) 
                {
                    if (대화표시설정 and pk::is_in_screen(pos))  // 화면 안 부대만 대화 표시
                    {
                        switch (pk::rand(4))
                        {
                            case 0: pk::say(pk::encode("이 고비만 넘으면 된다"), pk::get_person(unit.leader)); break;
                            case 1: pk::say(pk::encode("산악행군은 병사들을 지치게 하는군"), pk::get_person(unit.leader)); break;
                            case 2: pk::say(pk::encode("걸음이 더디다. 속도를 내라"), pk::get_person(unit.leader)); break;
                            case 3: pk::say(pk::encode("고지가 눈앞에 있다"), pk::get_person(unit.leader)); break;
                        }
                    }
                    
                    pk::add_energy(unit, -2, true);
                }
            }
        }
                
                
        //---------------------------------------------------------------------------------------     
        // 야전부대 탈영병 효과       
        void func_야전_탈영(pk::unit@ unit, pk::point pos, pk::hex@ hex, bool 효과적용)
        {
            if (효과적용)
            { 
        
                uint troops_loss = 0;
                
                // 혼란 부대 탈영병 효과 : 병력 5% 이탈
                if (unit.status == 부대상태_혼란)
                {
                    troops_loss = int(pk::min(unit.troops, pk::max(100.f, unit.troops*0.05f)));
                    pk::add_troops(unit, -troops_loss, true );
                    
                    if (대화표시설정 and pk::is_in_screen(pos))  // 화면 안 부대만 대화 표시
                    {
                        switch (pk::rand(4))
                        {
                            case 0: pk::say(pk::encode("빨리 혼란을 수습해야 된다"), pk::get_person(unit.leader));  break;
                            case 1: pk::say(pk::encode("병사들이 도망간다"), pk::get_person(unit.leader));  break;
                            case 2: pk::say(pk::encode("부대를 어서 정비하라"), pk::get_person(unit.leader)); break;
                            case 3: pk::say(pk::encode("이대로 가다가는 전멸한다"), pk::get_person(unit.leader)); break;
                        }
                    }
                }
                
                // 기력 저조 부대 탈영병 효과 : 야전부대 기력 10이하 시 병력10%, 25이하 시 병력5% 감소
                if (unit.energy <= 25)
                {
                    if (unit.energy <= 10)
                    {
                        troops_loss = int(pk::min(unit.troops, pk::max(100.f, unit.troops*0.10f)));
                        pk::add_troops(unit, -troops_loss, true );
                    }
                    else if (unit.energy <= 25)
                    {
                        troops_loss = int(pk::min(unit.troops, pk::max(100.f, unit.troops*0.05f)));
                        pk::add_troops(unit, -troops_loss, true );
                    }
                    
                    
                    if (대화표시설정 and pk::is_in_screen(pos))  // 화면 안 부대만 대화 표시
                    {
                        switch (pk::rand(4))
                        {
                            case 0: pk::say(pk::encode("탈영병이 속출하는군"), pk::get_person(unit.leader));  break;
                            case 1: pk::say(pk::encode("병사들이 도망간다"), pk::get_person(unit.leader));  break;
                            case 2: pk::say(pk::encode("부대 사기가 말이 아니군"), pk::get_person(unit.leader)); break;
                            case 3: pk::say(pk::encode("이대로 가다가는 전멸한다"), pk::get_person(unit.leader)); break;
                        }
                    }
                }
                // 병력 0 이 되면 부대 궤멸
                if (unit.troops == 0)       
                    pk::kill(unit);
                
            }
        }   
        
        //---------------------------------------------------------------------------------------
        void func_화계확산효과(bool 효과적용)
        {
            if (효과적용)
            {
                pk::array<pk::point> arr_fire;
                
                // 풍향 업데이트
                if (wind_init) 
                    wind_init = false;  // 시나리오 시작 또는 로딩 후
                else if (pk::get_day() == 1 and pk::is_first_month_of_quarter(pk::get_month()))
                    main.wind_dir = pk::rand(방향_끝);  // 새 계절이 되면 무작위로 풍향 변경
                else
                    main.wind_dir = get_wind_dir(main.wind_dir);  // 랜덤하게 방향 미세 변경
                
                // 풍향 안내
                if (풍향메세지표시 and pk::get_player_count() > 0) 
                    show_log_wind_dir(main.wind_dir);
                
                int fire_dir = pk::get_opposite_direction(main.wind_dir);
                for (int pos_x = 0; pos_x < 200; pos_x++)
                {
                    for (int pos_y = 0; pos_y < 200; pos_y++)
                    {
                        pk::point pos;
                        pos.x = pos_x;
                        pos.y = pos_y;
                        
                        pk::hex@ hex = pk::get_hex(pos);
                        if (pk::is_valid_pos(pos) and pk::is_valid_hex_direction(fire_dir) and pk::is_on_fire(pos) and !contains_pos(arr_fire, pos))
                        {
                            pk::point neighbor_pos = pk::get_neighbor_pos(pos, fire_dir);
                            if (pk::is_valid_pos(neighbor_pos))
                            {
                                pk::hex@ neighbor_hex = pk::get_hex(neighbor_pos);
                                int terrain_id = neighbor_hex.terrain;
                                
                                if (pk::rand_bool(화계확산확률) and pk::is_enabled_terrain(terrain_id) )
                                {
                                    if (!pk::is_water_terrain(terrain_id) or (pk::is_water_terrain(terrain_id) and neighbor_hex.has_unit))
                                    {
                                        arr_fire.insertLast(neighbor_pos);
                                        pk::create_fire(neighbor_pos, (1 + pk::rand(2)) );
                                        
                                        pk::unit@ unit = pk::get_unit(neighbor_pos);
                                        if (unit !is null and pk::is_in_screen(neighbor_pos))
                                        {
                                            switch (pk::rand(4))
                                            {
                                                case 0: pk::say(pk::encode("당황하지 마라!"), pk::get_person(unit.leader)); break;
                                                case 1: pk::say(pk::encode("어서 불을 꺼라"), pk::get_person(unit.leader)); break;
                                                case 2: pk::say(pk::encode("불이 번지지 않도록 해라"), pk::get_person(unit.leader)); break;
                                                case 3: pk::say(pk::encode("여기를 벗어나야 한다"), pk::get_person(unit.leader)); break;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        
        // 풍향 생성 함수
        int get_wind_dir(int seed_dir)
        {
            int new_dir;
            int rand_dir = pk::rand(5);
            
            switch(seed_dir)
            {
                case 방향_북서: 
                    switch(rand_dir)
                    {
                        case 0: new_dir = 방향_남서; break;
                        case 1: new_dir = 방향_남서; break;
                        case 2: new_dir = 방향_북서; break;
                        case 3: new_dir = 방향_북; break;
                        case 4: new_dir = 방향_북; break;
                    }
                    break;
                    
                case 방향_북 :
                    switch(rand_dir)
                    {
                        case 0: new_dir = 방향_북서; break;
                        case 1: new_dir = 방향_북서; break;
                        case 2: new_dir = 방향_북; break;
                        case 3: new_dir = 방향_북동; break;
                        case 4: new_dir = 방향_북동; break;
                    }
                    break;
                    
                case 방향_북동:
                    switch(rand_dir)
                    {
                        case 0: new_dir = 방향_북; break;
                        case 1: new_dir = 방향_북; break;
                        case 2: new_dir = 방향_북동; break;
                        case 3: new_dir = 방향_남동; break;
                        case 4: new_dir = 방향_남동; break;
                    }
                    break;
                    
                case 방향_남서:
                    switch(rand_dir)
                    {
                        case 0: new_dir = 방향_남; break;
                        case 1: new_dir = 방향_남; break;
                        case 2: new_dir = 방향_남서; break;
                        case 3: new_dir = 방향_북서; break;
                        case 4: new_dir = 방향_북서; break;
                    }
                    break;
                    
                case 방향_남 : 
                    switch(rand_dir)
                    {
                        case 0: new_dir = 방향_남동; break;
                        case 1: new_dir = 방향_남동; break;
                        case 2: new_dir = 방향_남; break;
                        case 3: new_dir = 방향_남서; break;
                        case 4: new_dir = 방향_남서; break;
                    }
                    break;
                    
                case 방향_남동:
                    switch(rand_dir)
                    {
                        case 0: new_dir = 방향_북동; break;
                        case 1: new_dir = 방향_북동; break;
                        case 2: new_dir = 방향_남동; break;
                        case 3: new_dir = 방향_남; break;
                        case 4: new_dir = 방향_남; break;
                    }
                    break;
            }
            
            return new_dir;
        }
        
        // 풍향 메세지 출력 함수
        void show_log_wind_dir(int direction)
        {
            string wind_name = get_wind_name(direction);
            
            int pause = int(pk::option["MessagePause"]);
            pk::option["MessagePause"] = 5;
            switch(pk::rand(4))
            {
                case 0: pk::message_box(pk::encode(pk::format("현재 바람은 \x1b[1x{}\x1b[0x이라네", wind_name)), pk::get_person(무장_좌자)); break;
                case 1: pk::message_box(pk::encode(pk::format("음...\x1b[1x{}\x1b[0x이 부는구먼", wind_name)), pk::get_person(무장_관로)); break;
                case 2: pk::message_box(pk::encode(pk::format("이보게. \x1b[1x{}\x1b[0x이 불어오는구려", wind_name)), pk::get_person(무장_허소)); break;
                case 3: pk::message_box(pk::encode(pk::format("풍향을 아는가? \x1b[1x{}\x1b[0x이라고", wind_name)), pk::get_person(무장_예형)); break;
            }
            pk::option["MessagePause"] = pause;
        }
        
        
        // 풍향명 반환 함수
        string get_wind_name(int direction)
        {
            string wind_name;
            switch(direction)
            {
               case 방향_북서 : wind_name = "북서풍";  break;
               case 방향_북  : wind_name = "북풍";  break;
               case 방향_북동 : wind_name = "북동풍";  break;
               case 방향_남서 : wind_name = "남서풍";  break;
               case 방향_남  : wind_name = "남풍";  break;
               case 방향_남동 : wind_name = "남동풍";  break;
            }
            return wind_name;
        }
        
        
        bool contains_pos(pk::array<pk::point> arr_pos, pk::point pos)
        {
            for (int i = 0; i < int(arr_pos.length); i++)
            {
                if (pos == arr_pos[i]) return true;
            }
            
            return false;
        }
        
        //---------------------------------------------------------------------------------------
        
        
        void func_도시특산효과(pk::unit@ unit, pk::point pos, bool 효과적용)
        {
            if (!pk::is_normal_force(unit.get_force_id())) return;
            
            if (효과적용)
            {
                pk::city@ city = pk::get_city(pk::get_service(unit));
                if (pk::is_alive(city))
                {
                    int weapon_heishu = pk::equipment_id_to_heishu(unit.weapon);
                    
                    // 소속도시가 대도시인 경우 병력 회복
                    if (pk::is_large_city(city) and unit.type == 부대종류_전투 and unit.troops < 3000)
                    {
                        pk::add_troops(unit, int(0.05f * unit.troops), true); 
                    }
                    // 부대 병과가 소속도시 특산과 일치하면 기력 회복
                    if (city.tokusan[weapon_heishu] and unit.energy < 40)
                    {
                        if (대화표시설정 and pk::rand_bool(대화표시확률) and pk::is_in_screen(pos))  // 화면 안 부대만 대화 표시
                        {
                            string city_name = pk::decode(pk::get_name(city));
                            string weapon_name = get_weapon_name(unit.weapon);
                            
                            switch(pk::rand(4))
                            {
                            case 0: pk::say(pk::encode(pk::format("이것이 \x1b[2x{} \x1b[1x{}\x1b[0x의 기세다", city_name, weapon_name)), pk::get_person(unit.leader)); break;
                            case 1: pk::say(pk::encode(pk::format("\x1b[2x{} \x1b[1x{}\x1b[0x의 위력을 보여주자", city_name, weapon_name)), pk::get_person(unit.leader)); break;
                            case 2: pk::say(pk::encode(pk::format("\x1b[2x{}는 자고로 \x1b[1x{}\x1b[0x이 유명하지", city_name, weapon_name)), pk::get_person(unit.leader)); break;
                            case 3: pk::say(pk::encode(pk::format("\x1b[2x{}라면 \x1b[1x{}\x1b[0x이다", city_name, weapon_name)), pk::get_person(unit.leader)); break;
                            }
                        }
                        
                        pk::add_energy(unit, +5, true); 
                    }
                    
                }
            }
        }
        
        string get_weapon_name(int weapon_id)
        {
            string weapon_name;
            switch(weapon_id)
            {
                case 병기_검  : weapon_name = "검병"; break;
                case 병기_창  : weapon_name = "창병"; break;
                case 병기_극  : weapon_name = "극병"; break;
                case 병기_노  : weapon_name = "노병"; break;
                case 병기_군마 : weapon_name = "기병"; break;
                case 병기_충차 : weapon_name = "충차"; break;
                case 병기_정란 : weapon_name = "정란"; break;
                case 병기_투석 : weapon_name = "투석"; break;
                case 병기_목수 : weapon_name = "목수"; break;
                case 병기_주가 : weapon_name = "수군"; break;
                case 병기_누선 : weapon_name = "수군"; break;
                case 병기_투함 : weapon_name = "수군"; break;
                default : weapon_name = "??"; break;
            }
            return weapon_name;
        }
        
        //---------------------------------------------------------------------------------------
        
        
        void func_무장출신주효과(pk::unit@ unit, pk::point pos, bool 효과적용)
        {
            if (!pk::is_normal_force(unit.get_force_id())) return;
            
            if (효과적용)
            {
                pk::person@ leader = pk::get_person(unit.leader);
                int birth_province = leader.birthplace;
                
                pk::building@ building = pk::get_building(pk::get_service(unit));
                if (!pk::is_alive(building)) return;
                    
                pk::city@ service_city = pk::get_city(pk::get_city_id(building.pos));
                int service_province = service_city.province;
            
                if (birth_province == service_province)
                {
                    if (대화표시설정 and pk::rand_bool(대화표시확률) and pk::is_in_screen(pos))  // 화면 안 부대만 대화 표시
                    {
                        string service_province_name = pk::decode(pk::get_name(pk::get_province(service_province)));
                        
                        switch(pk::rand(4))
                        {
                        case 0: pk::say(pk::encode(pk::format("동향의 \x1b[1x{}지역\x1b[0x 병사들과 \n함께라면 기운이 나는군", service_province_name)), pk::get_person(unit.leader)); break;
                        case 1: pk::say(pk::encode(pk::format("\x1b[1x{}지역\x1b[0x 병사들이여 나를 따르라", service_province_name)), pk::get_person(unit.leader)); break;
                        case 2: pk::say(pk::encode(pk::format("나도 \x1b[1x{}지역\x1b[0x 출신이라고", service_province_name)), pk::get_person(unit.leader)); break;
                        case 3: pk::say(pk::encode(pk::format("\x1b[1x{}지역\x1b[0x 출신 부대의 위력을 보여주지", service_province_name)), pk::get_person(unit.leader)); break;
                        }
                    }
                    
                    pk::add_energy(unit, +5, true); 
                }
            }
        }
        
        
        //---------------------------------------------------------------------------------------
        
	}

	Main main;
}