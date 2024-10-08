/*
// 작성자: 기마책사
// Update: '20.10.21    / 최초내용 : 거점 관문/항구 방어를 위한 간접공격 요격부대 출진

*/


namespace 거점방어
{
    
    //=======================================================================================
    // 관문/항구 방어군 출진 (by 기마책사)
    const bool 관문항구_방어설정 = true;        // true=적용, false=미적용 (노병,정란,투석: 후방으로 출진)
    
    const int  거점방어_최대출진부대수 = 2;       // 한 거점에서 연속으로 방어출진 가능한 부대수 (1~3)
    const int  거점방어_거점최소병력 = 8500;     // 해당 관문/항구에서 출진 후 남길 최소병력
    const int  거점방어_출진최소병력 = 3000;     // 출진할 부대의 최소병력 기준
    const int  거점방어_출진최대병력 = 5000;     // 출진할 부대의 최대병력 기준
    
    //=======================================================================================
    
	class Main
	{

		Main()
		{
			@prev_callback_261 = cast<pk::func261_t@>(pk::get_func(261));
			pk::reset_func(261);
			pk::set_func(261, pk::func261_t(callback_261));
            
		}
        
		pk::func261_t@ prev_callback_261;
        array<bool> arr_base_defence(건물_거점끝, false);
        
        
        //---------------------------------------------------------------------------------------
        
        // AI세력 스크립트
		bool callback_261(pk::force@ force)
		{
			int force_id = force.get_id();
            if (!pk::is_campaign())
			{
                // 플레이어, 이민족 세력은 제외, 난이도 특급 시에만 동작
                if (!force.is_player() and pk::is_normal_force(force_id) and pk::get_scenario().difficulty == 난이도_특급)
                {
                    if (관문항구_방어설정) func_base_defence(force);
                }
			}

			// 이전 핸들러가 있다면 체인.
			if (prev_callback_261 !is null)
				return prev_callback_261(force);
            
			return false;
		}
        
        
        
        
        //=======================================================================================
        //      거점방어 부대출진        
        //---------------------------------------------------------------------------------------
        
        //----- 거점방어 실행함수
        void func_base_defence(pk::force@ force)
        {
            int force_id = force.get_id();
            for (int i = 건물_관문시작; i < 건물_항구끝; i++)
            {
                arr_base_defence[i] = false;
                
                pk::building@ base = pk::get_building(i);
                pk::district@ district = pk::get_district(base.get_district_id());
                
                bool cmd = false;
                if (base.get_force_id() == force_id and enemy_unit_around(base))
                {
                    if (디버그모드) pk::info(pk::format("관문항구방어: {}", pk::decode(pk::get_name(base)) ));
                    
                    int max_count = pk::max(1, pk::min(3, 거점방어_최대출진부대수));
                    for (int push_count = 0; push_count < max_count; push_count++)
                        cmd = (PushCoveringUnit(base) or cmd);
                }
                
                if (cmd) arr_base_defence[i] = true;
            }
        }
        
        // ***** 방어군 출진 명령 ***** //
        bool PushCoveringUnit(pk::building@ src_base)
		{
            // 부대 방어좌표 선정
            pk::point dst_pos = get_dst_pos_nearby(src_base);
            if (dst_pos == -1) return false;
            
            // 공격목표부대 설정
            pk::unit@ target = list_enemy_unit[0];
            
            // 전투부대 출진
            int unit_id = PushRangeDefUnit(src_base, dst_pos, target, true);     
            if (unit_id != -1) return true;
            
			return false;
		}
        
        /** 방어군 출진필요 판단 **/
        bool enemy_unit_around(pk::building@ base)
		{
            if (!pk::is_alive(base)) return false;
            int base_type = base.facility;
            if (base_type != 시설_관문 and base_type != 시설_항구) return false;
            
            list_enemy_unit.clear();
            
            int enemy_troops = 0;   // 거점에 인접한 적부대 수 확인 추가
            pk::array<pk::point> range = pk::range(base.pos, 1, 1);
			for (int i = 0; i < int(range.length); i++)
			{
				pk::unit@ unit = pk::get_unit(range[i]);
				if (pk::is_alive(unit) and pk::is_enemy(base, unit) and !list_enemy_unit.contains(unit))
                {
                    enemy_troops += unit.troops;
                    list_enemy_unit.add(unit);
                }
			}
            int count = pk::get_idle_person_list(base).count;
            if (count > 0 and pk::get_troops(base) >= (거점방어_거점최소병력 + 거점방어_출진최소병력) and list_enemy_unit.count > 0 and enemy_troops >= 4000) 
                return true;
            
            return false;
        }
        
        //----------------------------------------------------------------------------------
        
        pk::list<pk::unit@> list_enemy_unit;
        pk::list<pk::person@> person_list;
        
        
        // 주변에 빈 좌표 확인
        pk::point get_dst_pos_nearby(pk::building@ base)
        {
            pk::array<pk::point> arr_empty_pos;
            pk::array<pk::point> arr_neighbor_pos = pk::range(base.pos, 1, 1);
            for (int i = 0; i < int(arr_neighbor_pos.length); i++)
            {
                pk::point neighbor_pos = arr_neighbor_pos[i];
                if (pk::is_valid_pos(neighbor_pos))
                {
                    pk::hex@ hex = pk::get_hex(neighbor_pos);
                    int terrain_id = hex.terrain;
                    if (pk::is_enabled_terrain(terrain_id) and !hex.has_building and !hex.has_unit)
                    {
                        bool check = true;
                        pk::array<pk::unit@> arr_unit = pk::list_to_array(list_enemy_unit);
                        for (int j = 0; j < int(arr_unit.length); j++)
                        {
                            if (!check or (pk::get_distance(neighbor_pos, arr_unit[j].pos) < 2))
                                check = false;
                            if (!check or bool(pk::core["지형"][terrain_id]["이동가능"]) == false)
                                check = false;
                            if (!check or terrain_id == 지형_산 or terrain_id == 지형_물가)
                                check = false;
                            if (!check or pk::is_on_fire(neighbor_pos))
                                check = false;
                        }
                        if (check)
                            arr_empty_pos.insertLast(neighbor_pos);
                    }
                }
            }
            if (int(arr_empty_pos.length) == 0) return -1;
            
            pk::point dst_pos = arr_empty_pos[0];
            
            return dst_pos;
        }
        
        
        //----------------------------------------------------------------------------------
        
        // 전투부대 출진 처리
        int amt_siege_wpn;
        int amt_range_wpn;
        int amt_dragn_wpn;
        
        int PushRangeDefUnit(pk::building@ src_base, pk::point dst_pos, pk::unit@ target, bool do_cmd = true)
        {
            if (!pk::is_alive(src_base) or !pk::is_valid_pos(dst_pos) or !pk::is_alive(target)) return -1;
            pk::hex@ hex = pk::get_hex(dst_pos);
            if (hex.has_building or hex.has_unit) return -1;    // 이동불가좌표
            if (pk::get_distance(src_base.pos, dst_pos) != 1) return -1;
            
            // 목표좌표가 수상인지 확인
            int terrain_id = pk::get_hex(dst_pos).terrain;
            if (!pk::is_enabled_terrain(terrain_id)) return -1;
            bool is_water_pos = pk::is_water_terrain(terrain_id);

            int src_troops = pk::get_troops(src_base);
            int ref_troops = 거점방어_거점최소병력;
            if (src_troops <= (ref_troops + 거점방어_출진최소병력)) return -1;    // 병력 부족
            
            person_list = pk::get_idle_person_list(src_base);
            if (person_list.count == 0) return -1;   // 무장 부족

            // 무장 정렬, 특기 우대, 통솔+무력 높은 순으로 정렬.
			func_sort_person_list();
            pk::person@ leader = pk::get_person(person_list[0].get_id());
            
            // 원거리 무기 보유 여부 확인
            int siege_rng_id = (pk::has_tech(src_base, 기교_투석개발))? 병기_투석 : 병기_정란;
            main.amt_siege_wpn = pk::get_weapon_amount(src_base, siege_rng_id);
            main.amt_range_wpn = pk::get_weapon_amount(src_base, 병기_노);
            main.amt_dragn_wpn = (pk::has_tech(src_base, 기교_기사) or pk::has_skill(leader, 특기_백마))? pk::get_weapon_amount(src_base, 병기_군마) : 0;
            if ((main.amt_range_wpn + main.amt_siege_wpn + main.amt_dragn_wpn) == 0) return -1;
            
            // 방어군 병력 산정 : 기준 병력 초과분, 지휘가능병력 확인
            int def_troops = pk::min(거점방어_출진최대병력, pk::get_command(leader), pk::max(1, src_troops - ref_troops));
            
            // 최적 무기 선택
            int ground_weapon_id = 병기_검;    // 육상병과 임시지정
            int water_weapon_id = 병기_주가;
            if (!is_water_pos or leader.tekisei[병종_수군] == 적성_C)
                water_weapon_id = 병기_주가;
            else if (is_water_pos)
            {
                if      (pk::get_weapon_amount(src_base, 병기_누선) > 0) water_weapon_id = 병기_누선;
                else if (pk::get_weapon_amount(src_base, 병기_투함) > 0) water_weapon_id = 병기_투함;
                else water_weapon_id = 병기_주가;
            }
            int unit_troops = def_troops;
            
            // 간접 병기 선택
            if (!is_water_pos) get_range_weapon(src_base, leader, def_troops, ground_weapon_id, unit_troops);
            if (!is_water_pos and ground_weapon_id == 0) return -1;    // 병기 부족
            
            // 병량 계산
            int unit_food = int(pk::min(2.0f * unit_troops, pk::max( 0.5f * pk::get_food(src_base), 1.2f * unit_troops)));
            if (unit_food < int(0.5f * unit_troops)) return -1;   // 병량 부족
            
            // 병과 이동가능지형 확인
            if (bool(pk::core["지형"][terrain_id]["이동가능"]) == false) return -1;
            int terrain_weapon_id = (is_water_pos)? water_weapon_id : ground_weapon_id;
            int movement_cost = pk::get_equipment(terrain_weapon_id).movement_cost[terrain_id];
            if (movement_cost < 0 or movement_cost >= 255) return -1;
            
            // 출진 명령
            if (do_cmd)
            {
                // 출진 명령 정보 생성.
                pk::com_deploy_cmd_info cmd;
                @cmd.base = @src_base;
                cmd.type = 부대종류_전투;
                cmd.member[0] = leader.get_id();
                cmd.gold = (pk::get_gold(src_base) >= 1000) ? int(pk::min(1000.f, pk::get_gold(src_base) * 0.1f)) : 0;
                cmd.troops = pk::max(1, unit_troops);
                cmd.weapon_id[0] = ground_weapon_id;
                cmd.weapon_id[1] = water_weapon_id;
                cmd.weapon_amount[0] = (is_siege_weapon(ground_weapon_id))? 1 : pk::max(1, unit_troops);
                cmd.weapon_amount[1] = (water_weapon_id == 병기_주가)? 0 : 1;
                cmd.food = pk::min(50000, unit_food);
                
                //cmd.order = 부대임무_이동;        // 부대 출진
                //cmd.target_pos = dst_pos;  // 목표 설정
                
                cmd.order = 부대임무_공격;        // 부대 출진
                cmd.target_pos = target.pos;  // 목표 설정

                // 출진 이동
                int unit_id = pk::command(cmd);
                if (unit_id == -1) return -1;
                
                pk::unit@ unit_cmd = pk::get_unit(unit_id);
                if (pk::is_alive(unit_cmd))
                {
                    //unit_cmd.action_done = false;   // 부대 출진 후 인근 적부대를 공격하기 위해 행동 미완료로 설정
                    //pk::set_order(unit_cmd, 부대임무_공격, target.pos);
                    //pk::run_order(unit_cmd);
                    
                    unit_cmd.action_done = true;    // 부대 행동완료로 변경
                    
                    if (디버그모드) 
                    {
                        string src_name      = pk::decode(pk::get_name(src_base));
                        string unit_name     = pk::decode(pk::get_name(leader));
                        string weapon_name   = get_weapon_name(unit_cmd.weapon);
                        pk::person@ target_p = pk::get_person(target.leader);
                        string target_name   = (pk::is_alive(target_p))? pk::decode(pk::get_name(target_p)) : "";
                        string order_str     = get_order_info(unit_cmd.order);
                        pk::info(pk::format("거점방어군: {}대({}), {} 인근({},{})에서 {}대 요격", unit_name, weapon_name, src_name, unit_cmd.pos.x, unit_cmd.pos.y, target_name));
                    }
                    return unit_id;
                }
            }
            
            return -1;
        }
        
        // 노병우대 출진여부
        bool cmd_archer = false;    
        
        
        void func_sort_person_list()
        {
            person_list.sort(function(a, b)
			{
                // 노병 특기 반영 ('20.9.13)
                if (main.amt_range_wpn > 0)
                {
                    bool a_archer = (pk::has_skill(a, 특기_궁신) or pk::has_skill(a, 특기_궁장) or pk::has_skill(a, 특기_사수));
                    bool b_archer = (pk::has_skill(b, 특기_궁신) or pk::has_skill(b, 특기_궁장) or pk::has_skill(b, 특기_사수));
                    if ( a_archer and !b_archer) return true;   
                    if (!a_archer and  b_archer) return false;  
                    // 노병 적성
                    if (a.tekisei[병종_노병] != b.tekisei[병종_노병]) return (a.tekisei[병종_노병] > b.tekisei[병종_노병]);
                }
                // 공성 특기 우대
                else if (main.amt_siege_wpn > 0)
                {
                    bool a_skill = (pk::has_skill(a, 특기_공신) or pk::has_skill(a, 특기_공성) or pk::has_skill(a, 특기_사정));
                    bool b_skill = (pk::has_skill(b, 특기_궁신) or pk::has_skill(b, 특기_공성) or pk::has_skill(b, 특기_사정));
                    if ( a_skill and !b_skill) return true;   
                    if (!a_skill and  b_skill) return false;  
                    // 기력회복 특기 우대
                    bool a_energy = (pk::has_skill(a, 특기_주악) or pk::has_skill(a, 특기_시상) or pk::has_skill(a, 특기_노발));
                    bool b_energy = (pk::has_skill(b, 특기_주악) or pk::has_skill(b, 특기_시상) or pk::has_skill(b, 특기_노발));
                    if ( a_energy and !b_energy) return true;   
                    if (!a_energy and  b_energy) return false;  
                    // 병기 적성
                    if (a.tekisei[병종_병기] != b.tekisei[병종_병기]) return (a.tekisei[병종_병기] > b.tekisei[병종_병기]);
                }
                // 백마 특기 우대
                else if (main.amt_dragn_wpn > 0)
                {
                    bool a_dragn = (pk::has_skill(a, 특기_기신) or pk::has_skill(a, 특기_기장) or pk::has_skill(a, 특기_백마));
                    bool b_dragn = (pk::has_skill(b, 특기_기신) or pk::has_skill(b, 특기_기장) or pk::has_skill(b, 특기_백마));
                    if ( a_dragn and !b_dragn) return true;   
                    if (!a_dragn and  b_dragn) return false;  
                    // 노병 적성
                    if (a.tekisei[병종_기병] != b.tekisei[병종_기병]) return (a.tekisei[병종_기병] > b.tekisei[병종_기병]);
                }
                // 무장 능력
                return (a.stat[무장능력_무력] + a.stat[무장능력_통솔]) > (b.stat[무장능력_무력] + b.stat[무장능력_통솔]);
			});
    }
        
        
        //----------------------------------------------------------------------------------
        
        // 무기 선택 함수
        void get_range_weapon(pk::building@ src_base, pk::person@ leader, int troops_max, int &out weapon_sel, int &out troops_sel)
        {
            int troops_min = 거점방어_출진최소병력;
            int weapon_max = 0;
            int best_tekisei = 적성_C;
            
            weapon_sel = 병기_검;
            troops_sel = 0;
            
            // 노병 출진
            if (main.amt_range_wpn > 0 and weapon_sel == 병기_검)
            {
                int tekisei = leader.tekisei[pk::equipment_id_to_heishu(병종_노병)];
                if (troops_min <= amt_range_wpn and 적성_B <= tekisei)
                {
                    weapon_sel = 병기_노;
                    troops_sel = pk::min(amt_range_wpn, troops_max);
                }
            }
            // 간접공성병기 출진
            else if (main.amt_siege_wpn > 0 and weapon_sel == 병기_검)
            {
                weapon_sel = 병기_노;
                troops_sel = pk::min(4000, troops_max);
            }
            // 기사군마 출진
            else if (main.amt_dragn_wpn > 0 and weapon_sel == 병기_검)
            {
                if (troops_min <= amt_dragn_wpn)
                {
                    weapon_sel = 병기_군마;
                    troops_sel = pk::min(amt_dragn_wpn, troops_max);
                }
            }
            
            if (weapon_sel == 병기_검)
            {
                troops_sel = troops_min;
            }
        }
        
        // 병과 속성 확인
        bool is_dir_weapon(int weapon_id) { return ((병기_검 <= weapon_id and weapon_id <= 병기_군마) and weapon_id != 병기_노); }
        bool is_siege_weapon(int weapon_id) { return (병기_충차 <= weapon_id and weapon_id <= 병기_목수); }
        bool is_ship_weapon(int weapon_id) { return (weapon_id == 병기_누선 or weapon_id == 병기_투함); }
        
        
        //=======================================================================================
        
        
        
        
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
        
        string get_order_info(int order)
        {
            string name;
            switch(order)
            {
                case 0  : name = "부대임무_대기"; break;
                case 1  : name = "부대임무_이동"; break;
                case 2  : name = "부대임무_설치"; break;
                case 3  : name = "부대임무_공격"; break;
                case 4  : name = "부대임무_퇴각"; break;
                case 5  : name = "부대임무_물림"; break;
                case 6  : name = "부대임무_호위"; break;
                case 7  : name = "부대임무_공성"; break;
                case 8  : name = "부대임무_수복"; break;
                case 9  : name = "부대임무_정복"; break;
                case 10 : name = "부대임무_보급"; break;
                case 11 : name = "부대임무_섬멸"; break;
                case 12 : name = "부대임무_추종"; break;
                case 13 : name = "부대임무_끝" ; break;
                default : name = "부대임무_없음"; break;
            }
            
            return name;
        }
        
        //---------------------------------------------------------------------------------------
        
        
        bool 디버그모드 = false;
        
        
	};

	Main main;
}