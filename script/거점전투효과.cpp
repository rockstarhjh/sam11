/*
@ 만든이: 기마책사
@ UPDATE: '18.11.6   / 최초적용: 거점포위효과, 거점주악효과, 거점명성효과, 거점축성효과
@ UPDATE: '18.11.11  / 변경내용: 이팩트 효과적용, 거점화계반격 추가
@ UPDATE: '18.11.23  / 변경내용: AI/Player전차별설정 추가, 거점내구회복 -AI공성전 시 발동안함
@ UPDATE: '18.11.26  / 변경내용: 거점화계반격 NPC부대 에러 수정
@ UPDATE: '18.12.5   / 변경내용: 거점화계반격 태수확인 조건 추가, 효과발동 건물타입 설정옵션 추가
@ UPDATE: '20.8.26   / 변경내용: 캠페인에서는 스크립트 동작 안하도록 수정
*/

namespace 거점전투효과
{
    //---------------------------------------------------------------------------------------
    // 유저 설정 (true = on, false = off)
    const bool 대화표시설정 = true;
    
    const bool 효과_AI만 = false;      // true =AI만 효과적용, false =유저와 AI 모두 효과 적용 (발동기준)
    const bool 효과_Player만 = false;  // true =Player만 효과적용, false =유저와 AI 모두 효과 적용
    //---------------------------------------------------------------------------------------
    const bool 효과_도시설정 = true;  // 도시 거점에 대해서 효과 적용 여부
    const bool 효과_관문설정 = true;  // 관문 거점에 대해서 효과 적용 여부
    const bool 효과_항구설정 = true;  // 항구 거점에 대해서 효과 적용 여부
    //---------------------------------------------------------------------------------------
    
    const bool 거점내구회복 = true;   // 성 내 무장 있을 시 정치력 합산에 비례하여 내구 회복
    const bool 거점축성효과 = true;   // 특기_축성 보유 거점 매턴 내구 회복
    const bool 거점포위효과 = true;   // 주변에 적군 있을 시 병력이탈, 기력감소
    
    const bool 거점화계반격 = true;   // 성벽에 달라붙을 시 적부대에 화계발동 : 특기_화공, 화신 우대 ('18.11.11)
    
    const bool 거점주악효과 = true;   // 특기_주악 보유 거점은 기력 회복 (시상 효과 2배)
    const bool 거점명성효과 = true;   // 특기_명성 보유 거점은 병력 증가
    
    //---------------------------------------------------------------------------------------
    
    
	class Main
	{
		Main()
		{
			pk::bind(107, pk::trigger107_t(onNewDay));
		}

		void onNewDay()     // 턴별
		{
            if (pk::is_campaign()) return;
            
            // 게임시작시에는 발동안함
            if (pk::get_elapsed_days() <= 0) return;
            
            // 거점_도시
            for (int i = 건물_도시시작; i < 건물_도시끝; i++)
                func_building_effect(pk::get_building(i), 효과_도시설정);

            // 거점_관문
            for (int i = 건물_관문시작; i < 건물_관문끝; i++)
                func_building_effect(pk::get_building(i), 효과_관문설정);

            // 거점_항구
            for (int i = 건물_항구시작; i < 건물_항구끝; i++)
                func_building_effect(pk::get_building(i), 효과_항구설정);
            
        }
        
        void func_building_effect(pk::building@ building, bool 효과적용)
        {
            if (효과적용)
            {
                // 건물별 적용효과 함수 호출
                // 함수 마지막을 true/false 설정에 따라 효과 on/off 설정 가능
                func_거점_내구회복(building, 거점내구회복);    // 턴별 
                func_거점_축성효과(building, 거점축성효과);    // 턴별
                func_거점_포위효과(building, 거점포위효과);    // 턴별 
                func_거점_화계반격(building, 거점화계반격);    // 턴별
                func_거점_주악효과(building, 거점주악효과);    // 월별 (pk::trigger108_t 미사용)
                func_거점_명성효과(building, 거점명성효과);    // 분기별 (pk::trigger109_t 미사용)
            }
        }
        
        
        
        //-------------------------------------------------------------------------------------------------
        // 유저 또는 AI만 적용 시 판단함수
        bool only_AI_unit(pk::unit@ unit)
        {
            if (효과_AI만 and unit.is_player()) return false;
            return true;
        }
        bool only_AI_building(pk::building@ building)
        {
            if (효과_AI만 and building.is_player()) return false;
            return true;
        }
        bool only_player_unit(pk::unit@ unit)
        {
            if (효과_Player만 and !unit.is_player()) return false;
            return true;
        }
        bool only_player_building(pk::building@ building)
        {
            if (효과_Player만 and !building.is_player()) return false;
            return true;
        }
        
        //-------------------------------------------------------------------------------------------------
        //-------------------------------------------------------------------------------------------------
        
        // 거점 내 내구도 회복 : 정치 합계 x10 ('18.11.10)
        void func_거점_내구회복(pk::building@ building, bool 효과적용)
        {
            // 주위 5칸 이내 Player 또는 AI끼리 교전 중인지 확인 ('18.11.23)
            // AI 공성전 시에는 회복 안함!!! 
            // Player 공성전 시에는 회복량 1.5배
            bool engage_AI_unit = false;
            bool engage_player_unit = false;
            auto range = pk::range(building.pos, 1, 5);
            for (int j = 0; j < int(range.length); j++)
            {
                pk::unit@ unit = pk::get_unit(range[j]);
                if (unit !is null and !building.is_player() and !unit.is_player() and pk::is_enemy(building, unit))
                    engage_AI_unit = true;
                if (unit !is null and !building.is_player() and  unit.is_player() and pk::is_enemy(building, unit))
                    engage_player_unit = true;
            }
            
            if (효과적용 and only_AI_building(building) and !engage_AI_unit)
            {
                if (int(building.hp) < int(pk::get_max_hp(building)))
                {
                    if (pk::is_in_screen(building.pos))
                    {
                        pk::person@ taishu = pk::get_person(pk::get_taishu_id(building));
                        if (대화표시설정)
                            pk::say(pk::encode("적군이 공격하기 전에 보수하라"), taishu );
                    }
                    
                    int build_point = 10 * func_stat_sum(building, 무장능력_정치); // 성 내 무장의 정치 능력 부분 합산
                    
                    if (engage_player_unit)    // player 와 교전 중이면 내구 회복량 1.5배
                        build_point = int(build_point * 1.5f);
                    
                    pk::add_hp(building, build_point, true );
                }
                
            }            
        }        
		int func_stat_sum(pk::building@ building, int stat_type)
		{
            //도시 내 무장 능력 반영 (각 무장의 정치 합산) ('18.10.7)
            float add_ratio = 10;    // 합산 보조율 : 무장별 10%
            int stat_sum = 0;
            
            auto list = pk::list_to_array(pk::get_person_list(building, pk::mibun_flags(신분_군주, 신분_태수, 신분_일반) ) );
            if (0 < list.length)
            {
                for (int i = 0; i < int(list.length); i++)
                {
                    pk::person@ person = list[i];
                    //출진 또는 부재중 상태가 아닌 장수이며, 태수와 혐오 관계가 아닌 장수만 능력 치 합산
                    if (!pk::is_unitize(person) and !pk::is_absent(person))
                    {
                        stat_sum += int((pk::max(person.stat[stat_type] - 25, 20)) * (add_ratio / 100.f));
                    }
                }
            }
            return stat_sum;
		}
                

        //-------------------------------------------------------------------------------------------------
        // 거점 주변에 적부대 있을 경우 병력 및 기력 감소 ('18.10.21)
        void func_거점_포위효과(pk::building@ building, bool 효과적용)
        {
            if (효과적용 and only_player_building(building))
            {
                if (pk::enemies_around(building))
                {
                    int n = pk::max(pk::get_troops(building), 100);
                    n = int(pk::rand(400) + 40 * sqrt(n / 100));
                
                    pk::add_troops(building, -n, true);   // 전시효과로 병력 감소 
                    pk::add_energy(building, -3, true);   // 전시효과로 기력 3 감소
                }
                
            }
        }
        
        //-------------------------------------------------------------------------------------------------
        // 거점에 적부대 달라 붙을 경우 화계 발동 ('18.11.11)
        void func_거점_화계반격(pk::building@ building, bool 효과적용)
        {
            if (효과적용 and only_AI_building(building))
            {
                int msg_count = 0;
                int dst_range = (building.get_id() < 건물_도시끝)? 2 : 1;
                
                array<pk::point> arr = pk::range(building.pos, dst_range, dst_range);
                for (int j = 0; j < int(arr.length); j++)
                {
                    pk::unit@ unit = pk::get_unit(arr[j]);
                    if (unit !is null and pk::is_enemy(unit, building))
                    {
                        int fire_chance = 0;
                        int fire_timer = 0;
                        int fire_person_id = 0;
                        
                        pk::person@ taishu = pk::get_person(pk::get_taishu_id(building));
                        
                        int stat_delta = 100;
                        if (taishu is null) 
                            stat_delta = 0;
                        else if (unit.leader < 무장_영제 or unit.leader > 무장_학자)
                            stat_delta = pk::max(0, taishu.stat[무장능력_지력] - unit.attr.stat[부대능력_지력]);
                        
                        // 발동 확률 및 타이머 설정
                        if (taishu is null) 
                            fire_chance = 0;
                        else if (pk::is_valid_person_id(building.who_has_skill(특기_화신)))
                        {
                            fire_chance = 100;
                            fire_timer = 1;
                            fire_person_id = building.who_has_skill(특기_화신);
                        }
                        else if (pk::is_valid_person_id(building.who_has_skill(특기_화공)))
                        {
                            fire_chance = pk::min(100, stat_delta + 50);
                            fire_timer = 1;
                            fire_person_id = building.who_has_skill(특기_화공);
                        }
                        else
                        {
                            fire_chance = pk::min(100, stat_delta);
                            fire_person_id = pk::get_taishu_id(building);
                        }
                        

                        // 화계 발동
                        if (pk::rand_bool(fire_chance) and !pk::is_on_fire(unit.pos))
                        {
                            if (대화표시설정 and pk::is_in_screen(building.pos) and msg_count == 0)
                            {
                                msg_count = 1;
                                pk::say(pk::encode("뜨거운 기름에 불을 지펴라"), pk::get_person(fire_person_id) );
                                pk::play_se(0x39, building.pos);
                                switch (pk::rand(3))
                                {
                                    case 0: pk::play_voice(0x33, pk::get_person(fire_person_id) ); break;   // 음성 : 화계
                                    case 1: pk::play_voice(0x34, pk::get_person(fire_person_id) ); break;   // 음성 : 화계
                                    case 2: pk::play_voice(0x35, pk::get_person(fire_person_id) ); break;   // 음성 : 화계
                                }
                            }
                            
                            pk::create_fire(unit.pos, pk::rand(1) + 1 + fire_timer, unit, true);
                            
                            if (대화표시설정 and pk::is_in_screen(building.pos))
                            {
                                switch (pk::rand(4))
                                {
                                    case 0: pk::say(pk::encode("으아악.."), pk::get_person(무장_병사), unit); break;
                                    case 1: pk::say(pk::encode("내 얼굴"), pk::get_person(무장_병사), unit); break;
                                    case 2: pk::say(pk::encode("빨리 불을 피해라"), pk::get_person(무장_병사), unit); break;
                                    case 3: pk::say(pk::encode("불. 불이다!"), pk::get_person(무장_병사), unit); break;
                                }
                            }
                        }
                        
                    }
                }
            }
        }
        
        //-------------------------------------------------------------------------------------------------
        // 거점 내 특기_주악 무장이 소속 시 기력 회복 +5 ~ +10 ('18.10.21)
        void func_거점_주악효과(pk::building@ building, bool 효과적용)
        {            
            if (효과적용 and only_AI_building(building))
            {
                // 월별 적용, 매월 1일에 발동
                int cheer_point = 0;
                if (pk::is_valid_person_id(building.who_has_skill(특기_주악)) and (pk::get_day() == 1))
                {
                    if (pk::get_energy(building) < pk::get_max_energy(building))
                    {
                        if (대화표시설정 and pk::is_in_screen(building.pos))
                        {
                            pk::say(pk::encode("병사들의 사기를 회복하라"), pk::get_person(building.who_has_skill(특기_주악)) );
                            pk::play_se(0x39, building.pos);
                            pk::play_voice(0x37, pk::get_person(building.who_has_skill(특기_주악)) );   // 음성 : 전투_진정
                        }
                        
                        cheer_point = 5;
                        if (pk::is_valid_person_id(building.who_has_skill(특기_시상)) )
                            cheer_point *= 2;
                        
                        pk::add_energy(building, cheer_point, true);
                    }
                }
                
            }
        }  
         
        //-------------------------------------------------------------------------------------------------
        // 거점 내 특기_명성 무장이 소속 시 매분기별 병력 증가 : 매력 x 10 ('18.10.22)
        void func_거점_명성효과(pk::building@ building, bool 효과적용)
        {       
            if (효과적용 and only_AI_building(building))
            {
                // 분기별 적용, 매분기 첫달 1일에만 발동
                int famous_point = 0;
                if (pk::is_valid_person_id(building.who_has_skill(특기_명성)) and pk::is_first_month_of_quarter(pk::get_month()) and (pk::get_day() == 1) )
                {
                    if (pk::get_troops(building) < pk::get_max_troops(building))
                    {
                        if (대화표시설정 and pk::is_in_screen(building.pos))
                        {
                            pk::say(pk::encode("저희를 병사로 받아주십시오"), pk::get_person(무장_청년), building);
                            pk::play_se(0x39, building.pos);
                            pk::play_voice(0x31, pk::get_person(building.who_has_skill(특기_명성)) );   // 음성 : 전투_계략2
                        }
                        
                        famous_point += 10 * (pk::get_person(building.who_has_skill(특기_명성)).stat[무장능력_매력]);
                        pk::add_troops(building, famous_point, true );
                    }
                    
                }
                
            }
        }
        
        //-------------------------------------------------------------------------------------------------
        // 거점 내 특기_축성 무장이 소속 시 내구도 회복 : 정치 x 5 ('18.10.22)
        void func_거점_축성효과(pk::building@ building, bool 효과적용)
        {
            if (효과적용 and only_AI_building(building))
            {
                int build_point = 0;
                if (pk::is_valid_person_id(building.who_has_skill(특기_축성)) )
                {
                    if (int(building.hp) < int(pk::get_max_hp(building)))
                    {
                        if (대화표시설정 and pk::is_in_screen(building.pos))
                        {
                            pk::say(pk::encode("어서 성벽을 보수하라"), pk::get_person(building.who_has_skill(특기_축성)) );
                            pk::play_se(0x39, building.pos);
                            switch(pk::rand(2))
                            {
                                case 0 : pk::play_voice(0x39, pk::get_person(building.who_has_skill(특기_축성)) ); break;   // 음성 : 설치
                                case 1 : pk::play_voice(0x3a, pk::get_person(building.who_has_skill(특기_축성)) ); break;   // 음성 : 설치
                            }
                        }
                        
                        build_point += 5 * (pk::get_person(building.who_has_skill(특기_축성)).stat[무장능력_정치]);
                        pk::add_hp(building, build_point, true );
                    }
                }
                
            }
        }
        
        
        //-------------------------------------------------------------------------------------------------
        
	}

	Main main;
}