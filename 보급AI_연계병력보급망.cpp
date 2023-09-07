/*
제작 by 일송정

본 스크립트는 기마책사님이 제작하신 거점원군.cpp와 기마책사님이 수정하신 거점철수.cpp의 상당 부분을 차용하고 있음을 알려드립니다. 
기마책사님께 감사드립니다.

*/

namespace 연계병력보급망
{

    //---------------------------------------------------------------------------------------
    // 유저 설정_기마책사님 자료에서 따옴
    
    const bool  거점수송_원거리이동  = true;     // 수송부대 이동 1회 추가 (추천기능 : 보너스이동으로 탈출)
    const bool  거점수송_일시도주설정 = false;     // 수송부대 출진순간 도주효과 일시적용 (추천기능 : 포위망 돌파가능)
    
    const bool 대사표시_설정 = false; 

    
    //---------------------------------------------------------------------------------------

	class Main
	{
		pk::func261_t@ prev_callback_;

		Main()
		{
			@prev_callback_ = cast<pk::func261_t@>(pk::get_func(261));
			pk::reset_func(261);
			pk::set_func(261, pk::func261_t(callback));
		}


                int retreat_skill = -1; // 수정금지

		bool callback(pk::force@ force)
		{
			int force_id = force.get_id();

			// 플레이어 조종 거점, 이민족 세력은 제외.
			if ( pk::is_normal_force(force_id))
			{
				for (int i = 0; i < 건물_거점끝; i++)
				{
					auto base = pk::get_building(i);
                                        pk::district@ district = pk::get_district(base.get_district_id());


	if (!force.is_player() or ( force.is_player() and !pk::is_player_controlled(base) and pk::is_alive(district) and district.transport ) )

		{

                    if (base.get_force_id() == force_id and needChaintroops0(base))
                        PushChaintroops0(base);

                    if (base.get_force_id() == force_id and needChaintroops0_G(base))
                        PushChaintroops0_G(base);

                    if (base.get_force_id() == force_id and needChaintroops0_F(base))
                        PushChaintroops0_F(base);

                    if (base.get_force_id() == force_id and needChaintroops(base))
                        PushChaintroops(base);

                    if (base.get_force_id() == force_id and needChain2troops(base))
                        PushChain2troops(base);



		}

				}
			}

			// 이전 핸들러가 있다면 체인.
			if (prev_callback_ !is null)
				return prev_callback_(force);
			return false;
		}




        //----------------------------------------------------------------------------------
        //  준전방에서 전방으로 지원군 파병 (병력 수송)
        //----------------------------------------------------------------------------------




		/** 병력 있는 거점 찾기 */

		bool needChaintroops0 (pk::building@ base)
		{

			if (!no_enemy_around(base)) return false;

			int base_troops = pk::get_troops(base);


			pk::city@ city_a = pk::get_city(pk::get_city_id(base.pos));



	// 병력 5만 이상 있고, 적 침공에서 안전한 준전방 도시에서 보급 보내라
	if ( 50000 <= base_troops and 건물_도시시작 <= base.get_id() and base.get_id() < 건물_도시끝 and no_enemy_around(base) and 1 <= func_enemy_city_count(city_a, 1) )
				return true;


            
			return false;
		}







		/** 전투부대 파견 */

		bool PushChaintroops0 (pk::building@ base)
		{
			// 명령 가능한 무장이 있는지 확인.
			auto person_list = pk::get_idle_person_list(base);
			if (person_list.count == 0) return false;

			// 수송할 인접 거접이 있는지 확인.
			int target = getUrgentBase0(base);
			if (target == -1) return false;

            pk::list<pk::person@> actors;
            for (int i = 0; i < person_list.count; i++)
            {
            if (pk::is_unitize(person_list[i])) continue;
            if (pk::is_absent(person_list[i])) continue;
            if (person_list[i].order != -1) continue;				
            if (person_list[i].get_force_id() != base.get_force_id()) continue; 
            if (person_list[i].get_force_id() != pk::get_building(target).get_force_id()) continue; 
            if (person_list[i].location != person_list[i].service) continue;
            if (person_list[i].action_done) continue;
            if (pk::is_absent(person_list[i])) continue;
            if (person_list[i].mibun == 신분_포로) continue;
            if (person_list[i].mibun == 신분_재야) continue;

            if (!pk::is_unitize(person_list[i]) and !pk::is_absent(person_list[i])
                and person_list[i].order == -1 and person_list[i].get_force_id() == base.get_force_id() and person_list[i].get_force_id() == pk::get_building(target).get_force_id() 
                and person_list[i].location == person_list[i].service and !person_list[i].action_done and !pk::is_absent(person_list[i])
                and (person_list[i].mibun == 신분_군주 or person_list[i].mibun == 신분_도독 or person_list[i].mibun == 신분_태수 or person_list[i].mibun == 신분_일반)) 
				
                actors.add(person_list[i]);
            }

       if (actors.count == 0 ) return false;
            
            // 통솔+무력 높은 순으로 정렬.
			actors.sort(function(a, b)
			{

                
				return (a.stat[무장능력_무력] + a.stat[무장능력_통솔]) > (b.stat[무장능력_무력] + b.stat[무장능력_통솔]);
			});
            pk::person@ leader = pk::get_person(actors[0].get_id());
            
            // 원군 병력 산정 : 기준 병력 초과분, 지휘가능병력 확인
            int reinforce_troops = pk::min(pk::get_command(leader), pk::max(int (pk::get_troops(base) * 0.35f) , pk::get_troops(base) - 10000));

            // 최적 무기 선택
            int ground_weapon_id = 병기_검;
            int water_weapon_id = 병기_주가;

            
            // 육상 무기 선택
            get_ground_weapon0(base, leader, reinforce_troops, ground_weapon_id, reinforce_troops);
            if (ground_weapon_id == 0) return false;    // 병기 부족
            
            // 수상 무기 선택
            if (leader.tekisei[병종_수군] == 적성_C)
                water_weapon_id = 병기_주가;
            else
            {
                if      (pk::get_weapon_amount(base, 병기_누선) > 0) water_weapon_id = 병기_누선;
                else if (pk::get_weapon_amount(base, 병기_투함) > 0) water_weapon_id = 병기_투함;
            }
            
            // 병량 계산
            int unit_food = int(pk::min( 0.3f * pk::get_food(base), 2.0f * reinforce_troops));
            if (unit_food < int(0.9f * reinforce_troops)) return false;   // 병량 부족
            if (pk::get_food(base) - unit_food < (pk::get_troops(base) - reinforce_troops) * 0.7f) return false;   // 거점 병량 부족
            
            // 출진 명령

                // 출진 명령 정보 생성.
                pk::com_deploy_cmd_info cmd;
                @cmd.base = @base;
                cmd.type = 부대종류_전투;
                cmd.member[0] = leader.get_id();
                cmd.gold = (pk::get_gold(base) >= 1000) ? int(pk::min(1000.f, pk::get_gold(base) * 0.1f)) : 0;
                cmd.troops = pk::max(1, reinforce_troops);
                cmd.weapon_id[0] = ground_weapon_id;
                cmd.weapon_id[1] = water_weapon_id;
                cmd.weapon_amount[0] = reinforce_troops;
                cmd.weapon_amount[1] = (water_weapon_id == 병기_주가)? 0 : 1;
                cmd.food = unit_food;

                cmd.order = 부대임무_공격;
                cmd.target_pos = pk::get_building(target).get_pos();  // 목표는 전투중인 거점

	if (대사표시_설정) 
                pk::say(pk::u8encode("여기서부턴 접경지대다!\n전투병들로 병력을 지원하겠다!"), leader);																											  

                // 출진.
                int unit_id = pk::command(cmd);
                if (unit_id != -1)
                    pk::get_unit(unit_id).action_done = true;

            
            return true;
        }
        
  
        
        //----------------------------------------------------------------------------------
        
        // 무기 선택 함수
        void get_ground_weapon0(pk::building@ base, pk::person@ leader, int troops_max, int &out weapon_sel, int &out troops_sel)
        {
            int troops_min = 2200;
            int weapon_max = 0;
            int best_tekisei = 적성_C;
            
            weapon_sel = 병기_검;
            troops_sel = 0;
            


                // 출병병력 이상 보유한 무기 중 최고 적성 확인
                for (int id = 병기_창; id <= 병기_군마; id++)
                {
                    int tekisei = leader.tekisei[pk::equipment_id_to_heishu(id)];
                    int weapon_t = pk::get_weapon_amount(base, id);
                    if (troops_min <= weapon_t and best_tekisei <= tekisei)
                        best_tekisei = tekisei;
                }
                
                // 최고 적성 이상의 병과 중 무기 가장 많은 병과 선택
                for (int id = 병기_창; id <= 병기_군마; id++)
                {
                    int tekisei = leader.tekisei[pk::equipment_id_to_heishu(id)];
                    int weapon_t = pk::get_weapon_amount(base, id);
                    if (troops_min <= weapon_t and weapon_max <= weapon_t and best_tekisei <= tekisei)
                    {
                        best_tekisei = tekisei;
                        weapon_max = weapon_t;
                        weapon_sel = id;
                        troops_sel = pk::min(weapon_max, troops_max);
                    }
                }
            
            
            if (weapon_sel == 0)
            {
                troops_sel = troops_min;
            }
        }
        
        //----------------------------------------------------------------------------------



        
		/** 가장 가깝고 위기에 빠진 아군 도시에 지원군 보냄 */


        pk::building@ src_cha0;
		int getUrgentBase0(pk::building@ src)
		{
			int best_dst = -1;
			int best_distance = 0;


            int src_id = src.get_id();
            pk::list<pk::building@> dst_list; 
            @src_cha0 = @src;

                        
            pk::force@ force = pk::get_force(src.get_force_id());
            
            
			// 수송 거점 검색

                for (int i = 0; i < 건물_도시끝; i++)
                {
                    pk::building@ dst = pk::get_building(i);
                    int dst_id = dst.get_id();
			int base2_troops = pk::get_troops(dst);



            int max_distance = (dst_id >= 건물_도시끝)? 1 : 1;




			// 근접한 적 부대 수
			int enemy_units1 = 0;
			int enemy_troops1 = 0;
			// 3칸 이내 적 부대 수
			int enemy_units3 = 0;
			// 3칸 이내 적 병력 수
			int enemy_troops3 = 0;



			int force_units7 = 0;



			auto range = pk::range(dst.get_pos(), 1, 10);
			for (int i = 0; i < int(range.length); i++)
			{
				auto unit = pk::get_unit(range[i]);
				if (pk::is_alive(unit))
				{
					int distance = pk::get_distance(dst.get_pos(), range[i]);
					if (pk::is_enemy(dst, unit))
					{
						if (distance <= 3)
						{
							enemy_units1++;
							enemy_troops1 += unit.troops;

						}
						if (distance <= 10)
						{
							enemy_units3++;
							enemy_troops3 += unit.troops;
						}
					}


					else if (dst.get_force_id() == unit.get_force_id() and unit.type == 부대종류_전투)
					{
                                                if (distance <= 7)
						{
							force_units7++;
						}
					}


					else
					{
					}
				}
			}




                    // 도시거리
                    int city_dist = -1;
                    if (dst_id < 건물_도시끝 and src_id < 건물_도시끝)
                        city_dist = pk::get_city_distance(dst_id, src_id);
                    
                    // 거점거리
                    int base_dist = pk::get_building_distance(dst_id, src_id, src.get_force_id());
                    
                    // 거리 조건 만족 시
                    if ( (0 <= base_dist and base_dist <= max_distance) or (city_dist == 1 and base_dist <= 3))
                    {
	          pk::city@ city_c = pk::get_city(pk::get_city_id(dst.pos));

                       // 목적지가 역병 혹은 메뚜기 재해지역이면 수송 안보냄
                        if (city_c.ekibyou or city_c.inago)  continue;

           // 구원군 보내는 곳이 받는 곳보다 1만명 이상이면, 접경지대의 도시로 보급 보내라

        if (src_id != dst_id and src.get_force_id() == dst.get_force_id()  and pk::is_alive(src) and pk::is_alive(dst) and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and base2_troops <= pk::get_max_troops(dst) * 0.4f and base2_troops + 10000 <= pk::get_troops(src) and (1 <= enemy_units3  or  1 <= func_enemy_city_count(city_c, 1) )   )
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 수송가능 거점리스트 추가
                    }

                    }

		
 	  }           


            // 출진가능 거점리스트 정렬 (거점 거리 오름차순, 좌표거리 오름차순)
            if (dst_list.count == 0)
                best_dst = -1;
            else
            {
                dst_list.sort(function(a, b)
                {
                    return (pk::get_troops(a) < pk::get_troops(b));					
					
                    int build_dist_a = pk::get_building_distance(a.get_id(), main.src_cha0.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.src_cha0.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.src_cha0.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.src_cha0.pos);

                    if (build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);
                    
                    return (pos_dist_a < pos_dist_b);
                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
		}










        //----------------------------------------------------------------------------------
        //  준전방에서 전방으로 지원군 파병 (금 수송)
        //----------------------------------------------------------------------------------




		/** 병력 있는 거점 찾기 */

		bool needChaintroops0_G (pk::building@ base)
		{

			if (!no_enemy_around(base)) return false;

			int base_troops = pk::get_troops(base);


			pk::city@ city_a = pk::get_city(pk::get_city_id(base.pos));



	// 병력 5만 이상 있고, 금 1만 이상, 병력의 0.4배 이상의 금 소유 중인 적 침공에서 안전한 준전방 도시에서 보급 보내라
	if ( 10000 <= pk::get_gold(base) and pk::get_troops(base) * 0.4f <= pk::get_gold(base) and 50000 <= base_troops and 건물_도시시작 <= base.get_id() and base.get_id() < 건물_도시끝 and no_enemy_around(base) and 1 <= func_enemy_city_count(city_a, 1) )
				return true;


            
			return false;
		}







		/** 전투부대 파견 */

		bool PushChaintroops0_G (pk::building@ base)
		{
			// 명령 가능한 무장이 있는지 확인.
			auto person_list = pk::get_idle_person_list(base);
			if (person_list.count == 0) return false;

			// 수송할 인접 거접이 있는지 확인.
			int target = getUrgentBase0_G(base);
			if (target == -1) return false;

            pk::list<pk::person@> actors;
            for (int i = 0; i < person_list.count; i++)
            {
            if (pk::is_unitize(person_list[i])) continue;
            if (pk::is_absent(person_list[i])) continue;
            if (person_list[i].order != -1) continue;				
            if (person_list[i].get_force_id() != base.get_force_id()) continue; 
            if (person_list[i].get_force_id() != pk::get_building(target).get_force_id()) continue; 
            if (person_list[i].location != person_list[i].service) continue;
            if (person_list[i].action_done) continue;
            if (pk::is_absent(person_list[i])) continue;
            if (person_list[i].mibun == 신분_포로) continue;
            if (person_list[i].mibun == 신분_재야) continue;

            if (!pk::is_unitize(person_list[i]) and !pk::is_absent(person_list[i])
                and person_list[i].order == -1 and person_list[i].get_force_id() == base.get_force_id() and person_list[i].get_force_id() == pk::get_building(target).get_force_id() 
                and person_list[i].location == person_list[i].service and !person_list[i].action_done and !pk::is_absent(person_list[i])
                and (person_list[i].mibun == 신분_군주 or person_list[i].mibun == 신분_도독 or person_list[i].mibun == 신분_태수 or person_list[i].mibun == 신분_일반)) 
				
                actors.add(person_list[i]);
            }

       if (actors.count == 0 ) return false;
            
            // 통솔+무력 높은 순으로 정렬.
			actors.sort(function(a, b)
			{

                
				return (a.stat[무장능력_무력] + a.stat[무장능력_통솔]) > (b.stat[무장능력_무력] + b.stat[무장능력_통솔]);
			});
            pk::person@ leader = pk::get_person(actors[0].get_id());
            
            // 원군 병력 산정 : 기준 병력 초과분, 지휘가능병력 확인
            int reinforce_troops = pk::min(pk::get_command(leader), pk::max(int (pk::get_troops(base) * 0.35f) , pk::get_troops(base) - 10000));

            // 최적 무기 선택
            int ground_weapon_id = 병기_검;
            int water_weapon_id = 병기_주가;

            
            // 육상 무기 선택
            get_ground_weapon0_G(base, leader, reinforce_troops, ground_weapon_id, reinforce_troops);
            if (ground_weapon_id == 0) return false;    // 병기 부족
            
            // 수상 무기 선택
            if (leader.tekisei[병종_수군] == 적성_C)
                water_weapon_id = 병기_주가;
            else
            {
                if      (pk::get_weapon_amount(base, 병기_누선) > 0) water_weapon_id = 병기_누선;
                else if (pk::get_weapon_amount(base, 병기_투함) > 0) water_weapon_id = 병기_투함;
            }
            
            // 병량 계산
            int unit_food = int(pk::min( 0.3f * pk::get_food(base), 2.0f * reinforce_troops));
            if (unit_food < int(0.9f * reinforce_troops)) return false;   // 병량 부족
            if (pk::get_food(base) - unit_food < (pk::get_troops(base) - reinforce_troops) * 0.7f) return false;   // 거점 병량 부족
            
            // 출진 명령

                // 출진 명령 정보 생성.
                pk::com_deploy_cmd_info cmd;
                @cmd.base = @base;
                cmd.type = 부대종류_전투;
                cmd.member[0] = leader.get_id();
                cmd.gold = pk::min(int(pk::get_gold(base) * 0.20f), 10000);
                cmd.troops = pk::max(1, reinforce_troops);
                cmd.weapon_id[0] = ground_weapon_id;
                cmd.weapon_id[1] = water_weapon_id;
                cmd.weapon_amount[0] = reinforce_troops;
                cmd.weapon_amount[1] = (water_weapon_id == 병기_주가)? 0 : 1;
                cmd.food = unit_food;

                cmd.order = 부대임무_공격;
                cmd.target_pos = pk::get_building(target).get_pos();  // 목표는 전투중인 거점

	if (대사표시_설정) 
                pk::say(pk::u8encode("여기서부턴 접경지대다!\n전투병들로 금을 수송하겠다!"), leader);																											  

                // 출진.
                int unit_id = pk::command(cmd);
                if (unit_id != -1)
                    pk::get_unit(unit_id).action_done = true;

            
            return true;
        }
        
  
        
        //----------------------------------------------------------------------------------
        
        // 무기 선택 함수
        void get_ground_weapon0_G(pk::building@ base, pk::person@ leader, int troops_max, int &out weapon_sel, int &out troops_sel)
        {
            int troops_min = 2200;
            int weapon_max = 0;
            int best_tekisei = 적성_C;
            
            weapon_sel = 병기_검;
            troops_sel = 0;
            


                // 출병병력 이상 보유한 무기 중 최고 적성 확인
                for (int id = 병기_창; id <= 병기_군마; id++)
                {
                    int tekisei = leader.tekisei[pk::equipment_id_to_heishu(id)];
                    int weapon_t = pk::get_weapon_amount(base, id);
                    if (troops_min <= weapon_t and best_tekisei <= tekisei)
                        best_tekisei = tekisei;
                }
                
                // 최고 적성 이상의 병과 중 무기 가장 많은 병과 선택
                for (int id = 병기_창; id <= 병기_군마; id++)
                {
                    int tekisei = leader.tekisei[pk::equipment_id_to_heishu(id)];
                    int weapon_t = pk::get_weapon_amount(base, id);
                    if (troops_min <= weapon_t and weapon_max <= weapon_t and best_tekisei <= tekisei)
                    {
                        best_tekisei = tekisei;
                        weapon_max = weapon_t;
                        weapon_sel = id;
                        troops_sel = pk::min(weapon_max, troops_max);
                    }
                }
            
            
            if (weapon_sel == 0)
            {
                troops_sel = troops_min;
            }
        }
        
        //----------------------------------------------------------------------------------



        
		/** 가장 가깝고 위기에 빠진 아군 도시에 지원군 보냄 */


        pk::building@ src_cha0_G;
		int getUrgentBase0_G(pk::building@ src)
		{
			int best_dst = -1;
			int best_distance = 0;


            int src_id = src.get_id();
            pk::list<pk::building@> dst_list; 
            @src_cha0_G = @src;

                       
            pk::force@ force = pk::get_force(src.get_force_id());
            
            
			// 수송 거점 검색

                for (int i = 0; i < 건물_도시끝; i++)
                {
                    pk::building@ dst = pk::get_building(i);
                    int dst_id = dst.get_id();
			int base2_troops = pk::get_troops(dst);



            int max_distance = (dst_id >= 건물_도시끝)? 1 : 1;




			// 근접한 적 부대 수
			int enemy_units1 = 0;
			int enemy_troops1 = 0;
			// 3칸 이내 적 부대 수
			int enemy_units3 = 0;
			// 3칸 이내 적 병력 수
			int enemy_troops3 = 0;



			int force_units7 = 0;



			auto range = pk::range(dst.get_pos(), 1, 10);
			for (int i = 0; i < int(range.length); i++)
			{
				auto unit = pk::get_unit(range[i]);
				if (pk::is_alive(unit))
				{
					int distance = pk::get_distance(dst.get_pos(), range[i]);
					if (pk::is_enemy(dst, unit))
					{
						if (distance <= 3)
						{
							enemy_units1++;
							enemy_troops1 += unit.troops;

						}
						if (distance <= 10)
						{
							enemy_units3++;
							enemy_troops3 += unit.troops;
						}
					}


					else if (dst.get_force_id() == unit.get_force_id() and unit.type == 부대종류_전투)
					{
                                                if (distance <= 7)
						{
							force_units7++;
						}
					}


					else
					{
					}
				}
			}




                    // 도시거리
                    int city_dist = -1;
                    if (dst_id < 건물_도시끝 and src_id < 건물_도시끝)
                        city_dist = pk::get_city_distance(dst_id, src_id);
                    
                    // 거점거리
                    int base_dist = pk::get_building_distance(dst_id, src_id, src.get_force_id());
                    
                    // 거리 조건 만족 시
                    if ( (0 <= base_dist and base_dist <= max_distance) or (city_dist == 1 and base_dist <= 3))
                    {
	          pk::city@ city_c = pk::get_city(pk::get_city_id(dst.pos));

                       // 목적지가 역병 혹은 메뚜기 재해지역이면 수송 안보냄
                        if (city_c.ekibyou or city_c.inago)  continue;

           // 금 4천 이하인, 접경지대의 도시로 보급 보내라

        if (src_id != dst_id and src.get_force_id() == dst.get_force_id()  and pk::is_alive(src) and pk::is_alive(dst) and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and pk::get_gold(dst) <= 4000 and (1 <= enemy_units3  or  1 <= func_enemy_city_count(city_c, 1) )   )
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 수송가능 거점리스트 추가
                    }

                    }

		
 	  }           


            // 출진가능 거점리스트 정렬 (거점 거리 오름차순, 좌표거리 오름차순)
            if (dst_list.count == 0)
                best_dst = -1;
            else
            {
                dst_list.sort(function(a, b)
                {
                    return (pk::get_gold(a) < pk::get_gold(b));	
					
                    int build_dist_a = pk::get_building_distance(a.get_id(), main.src_cha0_G.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.src_cha0_G.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.src_cha0_G.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.src_cha0_G.pos);

                    if (build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);
                    
                    return (pos_dist_a < pos_dist_b);
                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
		}














        //----------------------------------------------------------------------------------
        //  준전방에서 전방으로 지원군 파병 (군량 수송)
        //----------------------------------------------------------------------------------




		/** 병력 있는 거점 찾기 */

		bool needChaintroops0_F (pk::building@ base)
		{

			if (!no_enemy_around(base)) return false;

			int base_troops = pk::get_troops(base);


			pk::city@ city_a = pk::get_city(pk::get_city_id(base.pos));



	// 6만 이상이며 병력 2.5배 이상의 병량에, 병력 5만 이상, 적 침공에서 안전한 준전방 도시에서 보급 보내라
	if ( 60000 <= pk::get_food(base) and pk::get_troops(base) * 2.5f <= pk::get_food(base) and 50000 <= base_troops and 건물_도시시작 <= base.get_id() and base.get_id() < 건물_도시끝 and no_enemy_around(base) and 1 <= func_enemy_city_count(city_a, 1) )
				return true;


            
			return false;
		}







		/** 전투부대 파견 */

		bool PushChaintroops0_F (pk::building@ base)
		{
			// 명령 가능한 무장이 있는지 확인.
			auto person_list = pk::get_idle_person_list(base);
			if (person_list.count == 0) return false;

			// 수송할 인접 거접이 있는지 확인.
			int target = getUrgentBase0_F(base);
			if (target == -1) return false;

            pk::list<pk::person@> actors;
            for (int i = 0; i < person_list.count; i++)
            {
            if (pk::is_unitize(person_list[i])) continue;
            if (pk::is_absent(person_list[i])) continue;
            if (person_list[i].order != -1) continue;				
            if (person_list[i].get_force_id() != base.get_force_id()) continue; 
            if (person_list[i].get_force_id() != pk::get_building(target).get_force_id()) continue; 
            if (person_list[i].location != person_list[i].service) continue;
            if (person_list[i].action_done) continue;
            if (pk::is_absent(person_list[i])) continue;
            if (person_list[i].mibun == 신분_포로) continue;
            if (person_list[i].mibun == 신분_재야) continue;

            if (!pk::is_unitize(person_list[i]) and !pk::is_absent(person_list[i])
                and person_list[i].order == -1 and person_list[i].get_force_id() == base.get_force_id() and person_list[i].get_force_id() == pk::get_building(target).get_force_id() 
                and person_list[i].location == person_list[i].service and !person_list[i].action_done and !pk::is_absent(person_list[i])
                and (person_list[i].mibun == 신분_군주 or person_list[i].mibun == 신분_도독 or person_list[i].mibun == 신분_태수 or person_list[i].mibun == 신분_일반)) 
				
                actors.add(person_list[i]);
            }

       if (actors.count == 0 ) return false;
            
            // 통솔+무력 높은 순으로 정렬.
			actors.sort(function(a, b)
			{

                
				return (a.stat[무장능력_무력] + a.stat[무장능력_통솔]) > (b.stat[무장능력_무력] + b.stat[무장능력_통솔]);
			});
            pk::person@ leader = pk::get_person(actors[0].get_id());
            
            // 원군 병력 산정 : 기준 병력 초과분, 지휘가능병력 확인
            int reinforce_troops = pk::min(pk::get_command(leader), pk::max(int (pk::get_troops(base) * 0.35f) , pk::get_troops(base) - 10000));

            // 최적 무기 선택
            int ground_weapon_id = 병기_검;
            int water_weapon_id = 병기_주가;

            
            // 육상 무기 선택
            get_ground_weapon0_F(base, leader, reinforce_troops, ground_weapon_id, reinforce_troops);
            if (ground_weapon_id == 0) return false;    // 병기 부족
            
            // 수상 무기 선택
            if (leader.tekisei[병종_수군] == 적성_C)
                water_weapon_id = 병기_주가;
            else
            {
                if      (pk::get_weapon_amount(base, 병기_누선) > 0) water_weapon_id = 병기_누선;
                else if (pk::get_weapon_amount(base, 병기_투함) > 0) water_weapon_id = 병기_투함;
            }
            
            // 병량 계산
            int unit_food = int(pk::min( 0.3f * pk::get_food(base), 3.5f * reinforce_troops));
            if (unit_food < int(1.7f * reinforce_troops)) return false;   // 병량 부족
            if (pk::get_food(base) - unit_food < pk::get_troops(base) - reinforce_troops ) return false;   // 거점 병량 부족
            
            // 출진 명령

                // 출진 명령 정보 생성.
                pk::com_deploy_cmd_info cmd;
                @cmd.base = @base;
                cmd.type = 부대종류_전투;
                cmd.member[0] = leader.get_id();
                cmd.gold = (pk::get_gold(base) >= 1000) ? int(pk::min(1000.f, pk::get_gold(base) * 0.1f)) : 0;
                cmd.troops = pk::max(1, reinforce_troops);
                cmd.weapon_id[0] = ground_weapon_id;
                cmd.weapon_id[1] = water_weapon_id;
                cmd.weapon_amount[0] = reinforce_troops;
                cmd.weapon_amount[1] = (water_weapon_id == 병기_주가)? 0 : 1;
                cmd.food = unit_food;

                cmd.order = 부대임무_공격;
                cmd.target_pos = pk::get_building(target).get_pos();  // 목표는 전투중인 거점

	if (대사표시_설정) 
                pk::say(pk::u8encode("여기서부턴 접경지대다!\n전투병들로 병량을 수송하겠다!"), leader);																											  

                // 출진.
                int unit_id = pk::command(cmd);
                if (unit_id != -1)
                    pk::get_unit(unit_id).action_done = true;

            
            return true;
        }
        
  
        
        //----------------------------------------------------------------------------------
        
        // 무기 선택 함수
        void get_ground_weapon0_F(pk::building@ base, pk::person@ leader, int troops_max, int &out weapon_sel, int &out troops_sel)
        {
            int troops_min = 2200;
            int weapon_max = 0;
            int best_tekisei = 적성_C;
            
            weapon_sel = 병기_검;
            troops_sel = 0;
            


                // 출병병력 이상 보유한 무기 중 최고 적성 확인
                for (int id = 병기_창; id <= 병기_군마; id++)
                {
                    int tekisei = leader.tekisei[pk::equipment_id_to_heishu(id)];
                    int weapon_t = pk::get_weapon_amount(base, id);
                    if (troops_min <= weapon_t and best_tekisei <= tekisei)
                        best_tekisei = tekisei;
                }
                
                // 최고 적성 이상의 병과 중 무기 가장 많은 병과 선택
                for (int id = 병기_창; id <= 병기_군마; id++)
                {
                    int tekisei = leader.tekisei[pk::equipment_id_to_heishu(id)];
                    int weapon_t = pk::get_weapon_amount(base, id);
                    if (troops_min <= weapon_t and weapon_max <= weapon_t and best_tekisei <= tekisei)
                    {
                        best_tekisei = tekisei;
                        weapon_max = weapon_t;
                        weapon_sel = id;
                        troops_sel = pk::min(weapon_max, troops_max);
                    }
                }
            
            
            if (weapon_sel == 0)
            {
                troops_sel = troops_min;
            }
        }
        
        //----------------------------------------------------------------------------------



        
		/** 가장 가깝고 위기에 빠진 아군 도시에 지원군 보냄 */


        pk::building@ src_cha0_F;
		int getUrgentBase0_F(pk::building@ src)
		{
			int best_dst = -1;
			int best_distance = 0;


            int src_id = src.get_id();
            pk::list<pk::building@> dst_list; 
            @src_cha0_F = @src;

                       
            pk::force@ force = pk::get_force(src.get_force_id());
            
            
			// 수송 거점 검색

                for (int i = 0; i < 건물_도시끝; i++)
                {
                    pk::building@ dst = pk::get_building(i);
                    int dst_id = dst.get_id();
			int base2_troops = pk::get_troops(dst);



            int max_distance = (dst_id >= 건물_도시끝)? 1 : 1;




			// 근접한 적 부대 수
			int enemy_units1 = 0;
			int enemy_troops1 = 0;
			// 3칸 이내 적 부대 수
			int enemy_units3 = 0;
			// 3칸 이내 적 병력 수
			int enemy_troops3 = 0;



			int force_units7 = 0;



			auto range = pk::range(dst.get_pos(), 1, 10);
			for (int i = 0; i < int(range.length); i++)
			{
				auto unit = pk::get_unit(range[i]);
				if (pk::is_alive(unit))
				{
					int distance = pk::get_distance(dst.get_pos(), range[i]);
					if (pk::is_enemy(dst, unit))
					{
						if (distance <= 3)
						{
							enemy_units1++;
							enemy_troops1 += unit.troops;

						}
						if (distance <= 10)
						{
							enemy_units3++;
							enemy_troops3 += unit.troops;
						}
					}


					else if (dst.get_force_id() == unit.get_force_id() and unit.type == 부대종류_전투)
					{
                                                if (distance <= 7)
						{
							force_units7++;
						}
					}


					else
					{
					}
				}
			}



                    // 도시거리
                    int city_dist = -1;
                    if (dst_id < 건물_도시끝 and src_id < 건물_도시끝)
                        city_dist = pk::get_city_distance(dst_id, src_id);
                    
                    // 거점거리
                    int base_dist = pk::get_building_distance(dst_id, src_id, src.get_force_id());
                    
                    // 거리 조건 만족 시
                    if ( (0 <= base_dist and base_dist <= max_distance) or (city_dist == 1 and base_dist <= 3))
                    {
	          pk::city@ city_c = pk::get_city(pk::get_city_id(dst.pos));

                       // 목적지가 역병 혹은 메뚜기 재해지역이면 수송 안보냄
                        if (city_c.ekibyou or city_c.inago)  continue;

           // 군량이 2만 이하나 병력 대비 1.5배 이하인, 적 침공에서 안전한 도시로 보급 보내라

        if (src_id != dst_id and src.get_force_id() == dst.get_force_id()  and pk::is_alive(src) and pk::is_alive(dst) and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and  ( pk::get_food(dst) <= 20000 or pk::get_food(dst) <=  pk::get_troops(dst) * 1.5f or pk::get_food(dst) * 3 < pk::get_food(src) ) and (1 <= enemy_units3  or  1 <= func_enemy_city_count(city_c, 1) )   )
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 수송가능 거점리스트 추가
                    }

                    }

		
 	  }           


            // 출진가능 거점리스트 정렬 (거점 거리 오름차순, 좌표거리 오름차순)
            if (dst_list.count == 0)
                best_dst = -1;
            else
            {
                dst_list.sort(function(a, b)
                {
                    return (float(pk::get_food(a)) / float(pk::get_troops(a)) < float(pk::get_food(b)) / float(pk::get_troops(b)));					
					
                    int build_dist_a = pk::get_building_distance(a.get_id(), main.src_cha0_F.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.src_cha0_F.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.src_cha0_F.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.src_cha0_F.pos);

                    if (build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);
                    
                    return (pos_dist_a < pos_dist_b);
                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
		}











        //----------------------------------------------------------------------------------
        //  평시 경계에서 전방으로 순차 보급대 보내기  (병력)
        //----------------------------------------------------------------------------------




		/** 병력 있는 거점 찾기 */

		bool needChaintroops (pk::building@ base)
		{

			if (!no_enemy_around(base)) return false;

			int base_troops = pk::get_troops(base);


			pk::city@ city_a = pk::get_city(pk::get_city_id(base.pos));



	// 병력 5만 이상 있고, 적 침공에서 안전한 경계 도시에서 보급 보내라
	if ( 50000 <= base_troops and 건물_도시시작 <= base.get_id() and base.get_id() < 건물_도시끝 and no_enemy_around(base) and 1 <= func_enemy_city_count(city_a, 2) and  func_enemy_city_count(city_a, 1) == 0 )
				return true;



            
			return false;
		}







		/** 35% 보급 명령 */

		bool PushChaintroops(pk::building@ base)
		{

            int reinforce_troops = pk::min(15000, pk::max(3000, int (pk::get_troops(base) * 0.35f) ));
			// 명령 가능한 무장이 있는지 확인.
			auto person_list = pk::get_idle_person_list(base);
			if (person_list.count == 0) return false;

			// 수송할 인접 거접이 있는지 확인.
			int target = getBackup1Cha(base);
			if (target == -1) return false;

			if (!no_enemy_around(pk::get_building(target))) return false;
			if (enemy_approach(pk::get_building(target))) return false;
			if (close_combat(pk::get_building(target))) return false;

            if (target >= 건물_도시끝)
            reinforce_troops = pk::min(4000, pk::max(3000, int (pk::get_troops(base) * 0.35f) ));

            pk::list<pk::person@> actors;
            for (int i = 0; i < person_list.count; i++)
            {
            if (pk::is_unitize(person_list[i])) continue;
            if (pk::is_absent(person_list[i])) continue;
            if (person_list[i].order != -1) continue;				
            if (person_list[i].get_force_id() != base.get_force_id()) continue; 
            if (person_list[i].get_force_id() != pk::get_building(target).get_force_id()) continue; 
            if (person_list[i].location != person_list[i].service) continue;
            if (person_list[i].action_done) continue;
            if (pk::is_absent(person_list[i])) continue;
            if (person_list[i].mibun == 신분_포로) continue;
            if (person_list[i].mibun == 신분_재야) continue;

            if (!pk::is_unitize(person_list[i]) and !pk::is_absent(person_list[i])
                and person_list[i].order == -1 and person_list[i].get_force_id() == base.get_force_id() and person_list[i].get_force_id() == pk::get_building(target).get_force_id() 
                and person_list[i].location == person_list[i].service and !person_list[i].action_done and !pk::is_absent(person_list[i])
                and (person_list[i].mibun == 신분_군주 or person_list[i].mibun == 신분_도독 or person_list[i].mibun == 신분_태수 or person_list[i].mibun == 신분_일반)) 
				
                actors.add(person_list[i]);
            }

       if (actors.count == 0 ) return false;
	   
			// 무력 통솔 낮은 순으로 정렬.
			actors.sort(function(a, b)
			{
                        bool a_Supply = pk::has_skill(a, 특기_운반);
                        bool b_Supply = pk::has_skill(b, 특기_운반);
                        if ( a_Supply and !b_Supply) return true;
                        if (!a_Supply and  b_Supply) return false;					
				return (a.stat[무장능력_무력] + a.stat[무장능력_통솔]) < (b.stat[무장능력_무력] + b.stat[무장능력_통솔]);
			});
            pk::person@ leader = pk::get_person(actors[0].get_id());
            
            // 임시 도주 효과 ('19.3.6)
            if (거점수송_일시도주설정)
            {
                retreat_skill = leader.skill;   // 특기 백업
                leader.skill = 특기_도주;         // 도주 특기 부여
            }

            // 수송대 보내는 곳의 병량 보유 충분도에 따라 부대 병량을 다르게      
            float food_ratio = 2.0f; 
            if (pk::get_food(base) > pk::get_troops(base) * 2.0f)
            food_ratio = 3.5f;  

            int unit_food = int(pk::min( 0.3f * pk::get_food(base), food_ratio * reinforce_troops));
            if (unit_food < int(0.5f * reinforce_troops)) return false;   // 병량 부족 
            if (pk::get_food(base) - unit_food < (pk::get_troops(base) - reinforce_troops) * 0.5f) return false;   // 거점 병량 부족  

            float supply_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            float weapon_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            
			// 출진 명령 정보 생성.
			pk::com_deploy_cmd_info cmd;
			@cmd.base = @base;
			cmd.type = 부대종류_수송;
			cmd.member[0] = leader.get_id();
			cmd.gold = pk::min(int(pk::get_gold(base) * 0.2f), 5000);
			cmd.food = pk::min(pk::max (5000 , unit_food), 60000);
			cmd.troops = reinforce_troops;
			int i = 0;
			for (int weapon_id = 0; weapon_id < 병기_끝; weapon_id++)
			{
                int weapon_amount = 0;
                if (weapon_id < 병기_충차)
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id) * 0.25f), 20000);
                else
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id)), 4);
                
				if (weapon_amount > 0)
				{
					cmd.weapon_id[i] = weapon_id;
					cmd.weapon_amount[i] = weapon_amount;
					i++;
				}
			}
			cmd.order = 부대임무_공격;
			cmd.target_pos = pk::get_building(target).get_pos();

			// 출진.
			int unit_id = pk::command(cmd);
			if (unit_id != -1)
				pk::get_unit(unit_id).action_done = (!거점수송_원거리이동);  // 기본값 true 에서 false 로 변경하여 2회 이동하도록 함 ('19.3.5)
            
	if (대사표시_설정)             
            pk::say(pk::u8encode("경계 지역에서 전방으로!\n어서 전선으로 가자!"), leader);
            
            // 임시 도주 효과 ('19.3.6)
            if (거점수송_일시도주설정)
            {
                leader.skill = retreat_skill;         // 특기 복원
            }
            
            
			return true;
		}





        
		/** 가장 가깝고 위기에 빠진 아군 도시에 보급을 보냄 */

        pk::building@ src_cha;
		int getBackup1Cha (pk::building@ src)
		{
			int best_dst = -1;
			int best_distance = 0;
            int src_id = src.get_id();
            pk::list<pk::building@> dst_list; 
            @src_cha = @src;

            
            pk::force@ force = pk::get_force(src.get_force_id());
            
			// 수송 거점 검색

                for (int i = 0; i < 건물_도시끝; i++)
                {
                    pk::building@ dst = pk::get_building(i);
                    int dst_id = dst.get_id();
			int base2_troops = pk::get_troops(dst);

            int max_distance = (dst_id >= 건물_도시끝)? 1 : 1;

                
                    // 도시거리
                    int city_dist = -1;
                    if (dst_id < 건물_도시끝 and src_id < 건물_도시끝)
                        city_dist = pk::get_city_distance(dst_id, src_id);
                    
                    // 거점거리
                    int base_dist = pk::get_building_distance(dst_id, src_id, src.get_force_id());
                    
                    // 거리 조건 만족 시
                    if ( (0 <= base_dist and base_dist <= max_distance) or (city_dist == 1 and base_dist <= 3))
                    {
	          pk::city@ city_c = pk::get_city(pk::get_city_id(dst.pos));

                       // 목적지가 역병 혹은 메뚜기 재해지역이면 수송 안보냄
                        if (city_c.ekibyou or city_c.inago)  continue;

           // 병력 최대 기준 50% 이하로, 접경지대의 도시로 보급 보내라

        if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst)  and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and base2_troops <= pk::get_max_troops(dst) * 0.50f and no_enemy_around(dst) and 1 <= func_enemy_city_count(city_c, 1)  and func_already (dst) <= 2 and func_supplycheck(src,dst) == 0  )
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 수송가능 거점리스트 추가
                    }
 






                }
            	
   } 

            
            // 출진가능 거점리스트 정렬 (거점 거리 오름차순, 좌표거리 오름차순)
            if (dst_list.count == 0)
                best_dst = -1;
            else
            {
                dst_list.sort(function(a, b)
                {
                    return (pk::get_troops(a) < pk::get_troops(b));	
					
                    int build_dist_a = pk::get_building_distance(a.get_id(), main.src_cha.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.src_cha.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.src_cha.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.src_cha.pos);

                    if (build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);
                    
                    return (pos_dist_a < pos_dist_b);
                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
		}










        //----------------------------------------------------------------------------------
        //  평시 후방에서 경계로 순차 보급대 보내기  (병력)
        //----------------------------------------------------------------------------------




		/** 병력 있는 거점 찾기 */

		bool needChain2troops (pk::building@ base)
		{
			if (!no_enemy_around(base)) return false;

			int base_troops = pk::get_troops(base);

			pk::city@ city_a = pk::get_city(pk::get_city_id(base.pos));

	      for (int k = 0; k < 13; k++)
		  {

	// 병력 5만 이상 있고, 적 침공에서 안전한 도시에서 보급 보내라
	if (  50000 <= base_troops and 건물_도시시작 <= base.get_id() and base.get_id() < 건물_도시끝 and no_enemy_around(base) and 1 <= func_enemy_city_count(city_a, k + 3) and  func_enemy_city_count(city_a, k + 2) == 0)
				return true;

		   }


            
			return false;
		}







		/** 35% 보급 명령 */

		bool PushChain2troops(pk::building@ base)
		{

            int reinforce_troops = pk::min(15000, pk::max(3000, int (pk::get_troops(base) * 0.35f) ));
			// 명령 가능한 무장이 있는지 확인.
			auto person_list = pk::get_idle_person_list(base);
			if (person_list.count == 0) return false;

			// 수송할 인접 거접이 있는지 확인.
			int target = getBackup2Cha(base);
			if (target == -1) return false;





            if (target >= 건물_도시끝)
            reinforce_troops = pk::min(4500, pk::max(3000, int (pk::get_troops(base) * 0.35f) ));

            pk::list<pk::person@> actors;
            for (int i = 0; i < person_list.count; i++)
            {
            if (pk::is_unitize(person_list[i])) continue;
            if (pk::is_absent(person_list[i])) continue;
            if (person_list[i].order != -1) continue;				
            if (person_list[i].get_force_id() != base.get_force_id()) continue; 
            if (person_list[i].get_force_id() != pk::get_building(target).get_force_id()) continue; 
            if (person_list[i].location != person_list[i].service) continue;
            if (person_list[i].action_done) continue;
            if (pk::is_absent(person_list[i])) continue;
            if (person_list[i].mibun == 신분_포로) continue;
            if (person_list[i].mibun == 신분_재야) continue;

            if (!pk::is_unitize(person_list[i]) and !pk::is_absent(person_list[i])
                and person_list[i].order == -1 and person_list[i].get_force_id() == base.get_force_id() and person_list[i].get_force_id() == pk::get_building(target).get_force_id() 
                and person_list[i].location == person_list[i].service and !person_list[i].action_done and !pk::is_absent(person_list[i])
                and (person_list[i].mibun == 신분_군주 or person_list[i].mibun == 신분_도독 or person_list[i].mibun == 신분_태수 or person_list[i].mibun == 신분_일반)) 
				
                actors.add(person_list[i]);
            }

       if (actors.count == 0 ) return false;
	   
			// 무력 통솔 낮은 순으로 정렬.
			actors.sort(function(a, b)
			{
                        bool a_Supply = pk::has_skill(a, 특기_운반);
                        bool b_Supply = pk::has_skill(b, 특기_운반);
                        if ( a_Supply and !b_Supply) return true;
                        if (!a_Supply and  b_Supply) return false;					
				return (a.stat[무장능력_무력] + a.stat[무장능력_통솔]) < (b.stat[무장능력_무력] + b.stat[무장능력_통솔]);
			});
            pk::person@ leader = pk::get_person(actors[0].get_id());
            
            // 임시 도주 효과 ('19.3.6)
            if (거점수송_일시도주설정)
            {
                retreat_skill = leader.skill;   // 특기 백업
                leader.skill = 특기_도주;         // 도주 특기 부여
            }
     
            // 수송대 보내는 곳의 병량 보유 충분도에 따라 부대 병량을 다르게      
            float food_ratio = 2.0f; 
            if (pk::get_food(base) > pk::get_troops(base) * 2.0f)
            food_ratio = 5.0f;  

            int unit_food = int(pk::min( 0.3f * pk::get_food(base), food_ratio * reinforce_troops));
            if (unit_food < int(0.5f * reinforce_troops)) return false;   // 병량 부족 
            if (pk::get_food(base) - unit_food < (pk::get_troops(base) - reinforce_troops) * 0.5f) return false;   // 거점 병량 부족      

            float supply_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            float weapon_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            
			// 출진 명령 정보 생성.
			pk::com_deploy_cmd_info cmd;
			@cmd.base = @base;
			cmd.type = 부대종류_수송;
			cmd.member[0] = leader.get_id();
			cmd.gold = pk::min(int(pk::get_gold(base) * 0.3f), 10000);
			cmd.food = pk::min(pk::max (5000 , unit_food), 60000);
			cmd.troops = reinforce_troops;
			int i = 0;
			for (int weapon_id = 0; weapon_id < 병기_끝; weapon_id++)
			{
                int weapon_amount = 0;
                if (weapon_id < 병기_충차)
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id) * 0.25f), 20000);
                else
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id)), 4);
                
				if (weapon_amount > 0)
				{
					cmd.weapon_id[i] = weapon_id;
					cmd.weapon_amount[i] = weapon_amount;
					i++;
				}
			}
			cmd.order = 부대임무_공격;
			cmd.target_pos = pk::get_building(target).get_pos();

			// 출진.
			int unit_id = pk::command(cmd);
			if (unit_id != -1)
				pk::get_unit(unit_id).action_done = (!거점수송_원거리이동);  // 기본값 true 에서 false 로 변경하여 2회 이동하도록 함 ('19.3.5)
            
	if (대사표시_설정)             
            pk::say(pk::u8encode("후방에서 경계 지역으로!\n전쟁을 대비하자!"), leader);
            
            // 임시 도주 효과 ('19.3.6)
            if (거점수송_일시도주설정)
            {
                leader.skill = retreat_skill;         // 특기 복원
            }
            
            
			return true;
		}





        
		/** 가장 가깝고 위기에 빠진 아군 도시에 보급을 보냄 */

        pk::building@ src_cha2;
		int getBackup2Cha(pk::building@ src)
		{
			int best_dst = -1;
			int best_distance = 0;
            int src_id = src.get_id();
            pk::list<pk::building@> dst_list; 
            @src_cha2 = @src;

                        
            pk::force@ force = pk::get_force(src.get_force_id());
            
			// 수송 거점 검색

                for (int i = 0; i < 건물_도시끝; i++)
                {
                    pk::building@ dst = pk::get_building(i);
                    int dst_id = dst.get_id();
			int base2_troops = pk::get_troops(dst);

            int max_distance = (dst_id >= 건물_도시끝)? 1 : 1;

                
                    // 도시거리
                    int city_dist = -1;
                    if (dst_id < 건물_도시끝 and src_id < 건물_도시끝)
                        city_dist = pk::get_city_distance(dst_id, src_id);
                    
                    // 거점거리
                    int base_dist = pk::get_building_distance(dst_id, src_id, src.get_force_id());
                    
                    // 거리 조건 만족 시
                    if ( (0 <= base_dist and base_dist <= max_distance) or city_dist == 1)
                    {

			pk::city@ city_a = pk::get_city(pk::get_city_id(src.pos));
			pk::city@ city_c = pk::get_city(pk::get_city_id(dst.pos));

                       // 목적지가 역병 혹은 메뚜기 재해지역이면 수송 안보냄
                        if (city_c.ekibyou or city_c.inago)  continue;

           // 병력 최대 기준 50% 이하로, , 접경지대의 도시로 보급 보내라

	for (int k = 0; k < 13; k++)
	{
if (1 <= func_enemy_city_count(city_a, k + 3) and  func_enemy_city_count(city_a, k + 2) == 0)
	    {
    if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst)  and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and base2_troops <= pk::get_max_troops(dst) * 0.50f and 1 <= func_enemy_city_count(city_c, k + 2) and  func_enemy_city_count(city_c, k + 1) == 0 and func_already (dst) <= 2 and func_supplycheck(src,dst) == 0 )
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 수송가능 거점리스트 추가
                    } 

             }
         }

                }

	
   } 

            
            // 출진가능 거점리스트 정렬 (거점 거리 오름차순, 좌표거리 오름차순)
            if (dst_list.count == 0)
                best_dst = -1;
            else
            {
                dst_list.sort(function(a, b)
                {
                    return (pk::get_troops(a) < pk::get_troops(b));	
					
                    int build_dist_a = pk::get_building_distance(a.get_id(), main.src_cha2.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.src_cha2.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.src_cha2.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.src_cha2.pos);

                    if (build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);
                    
                    return (pos_dist_a < pos_dist_b);
                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
		}






         //  거리에 따른 거점 주변 적대 도시 숫자 체크, masterpiecek님의 AI_도시물자수송.cpp﻿를 참조했습니다.

		int func_enemy_city_count(pk::city@ city, int distance)
		{
			int enemy_city_count = 0;
			for (int i = 0; i < 도시_끝; i++)
			{
				pk::city@ enemycity = pk::get_city(i);
				int city_distance = pk::get_city_distance(city.get_id(), i);

				if (pk::is_alive(enemycity) and city.get_id() != i and ( pk::is_enemy(city, enemycity) or (!city.is_player() and enemycity.is_player() ) ) and city_distance <= distance) 

				enemy_city_count++;
																	  										  				   
			}

			return enemy_city_count;
		}



         // 목표 거점으로 이미 출진한 부대 숫자 체크, masterpiecek님의 AI_도시물자수송.cpp﻿를 참조했습니다.

	 int func_already(pk::building@ building)
		{
			int already = 0;
			for (int unit_id = 0; unit_id < 부대_끝; unit_id++)
			{
				pk::unit@ unit = pk::get_unit(unit_id);
			if (building.get_force_id() == -1) continue;
			if (unit.get_force_id() == -1) continue;
				if ( pk::is_alive(unit) and 3000 <= unit.troops and unit.get_force_id() == building.get_force_id() and unit.target == building.get_id()) 

				already++;
			}

			return already;
		}





         // 해당거점으로 특정공급 거점에서 이미 출진한 부대 숫자 체크 (한 공급 거점에서 똑같은 거점으로 2번 이상의 수송대 보내는 걸 막자) . masterpiecek님의 AI_도시물자수송.cpp﻿를 참조했습니다.

	 int func_supplycheck(pk::building@ building, pk::building@ building2)
		{
			int supplycheck = 0;
			for (int unit_id = 0; unit_id < 부대_끝; unit_id++)
			{
				pk::unit@ unit = pk::get_unit(unit_id);
                pk::building@ base = pk::get_building(pk::get_service(unit));

			if (building.get_force_id() == -1) continue;
			if (building2.get_force_id() == -1) continue;
			if (unit.get_force_id() == -1) continue;
		if ( pk::is_alive(unit) and unit.type == 부대종류_수송 and unit.get_force_id() == building.get_force_id() and unit.get_force_id() == building2.get_force_id() and base.get_id() == building.get_id()  and unit.target == building2.get_id()  ) 

				supplycheck++;
			}

			return supplycheck;
		}


        //---------------------------------------------------------------------------------------

        //---------------------------------------------------------------------------------------

        // ***** 거점 근처에서 적과 아군이 간격 없이 직접적으로 교전중인가? ***** //
        bool close_combat(pk::building@ base)
        {
																										 
																											  
                pk::array<pk::point> range = pk::range(base.pos, 1, 15);  // 거점 주변 검색																   						 
                for (int i = 0; i < int(range.length); i++)
                {
                            pk::point pos_i = range[i];
                            pk::unit@ unit_e = pk::get_unit(pos_i);
                            if (pk::is_alive(unit_e) and pk::is_enemy(base, unit_e))
				{	
		  
                pk::unit@ unit_f = get_neighbor_enemy_unit(unit_e);
				
				if (pk::is_alive(unit_f) and pk::is_enemy(unit_e, unit_f) and base.get_force_id() == unit_f.get_force_id())					
	            return true;
                }
                }				
            
	return false;
        }


        //---------------------------------------------------------------------------------------

        //---------------------------------------------------------------------------------------

        // ***** 적이 아군 거점에 다가오는가? ***** //
        bool enemy_approach(pk::building@ base)
        {
                pk::array<pk::point> range = pk::range(base.pos, 1, 15);  // 거점 주변 검색
                for (int i = 0; i < int(range.length); i++)
                {
				auto unit_e = pk::get_unit(range[i]);
				if (pk::is_alive(unit_e) and pk::is_enemy(base, unit_e))
				{	
                    pk::building@ base_t = get_neighbor_enemy_base(unit_e);	
				if (pk::is_alive(base_t) and base_t.get_id() == base.get_id())					
	            return true;
                }
                }				
            
	return false;
        }

        //---------------------------------------------------------------------------------------

        //---------------------------------------------------------------------------------------

        // *****  적부대가 아군부대와 직접 마주할 상황 여부 (2022.06. 일송정 추가)***** //
        bool status_neighbor_enemy_unit(pk::unit@ unit)
        {
            pk::array<pk::point> arr_range = pk::get_movable_pos(unit);  // 이동가능좌표
            for (int j = 0; j < int(arr_range.length); j++)
            {
                pk::point pos = arr_range[j];				
            for (int i = 0; i < 방향_끝; i++)
            {
                pk::point neighbor_pos = pk::get_neighbor_pos(pos, i);				
                pk::point neighbor_pos_mark = pk::get_neighbor_pos(unit.pos, i);
                if (pk::is_valid_pos(neighbor_pos))
                {
                    pk::unit@ unit_t = pk::get_unit(neighbor_pos);

                    if (pk::is_alive(unit_t) and unit_t.get_id() != unit.get_id() and pk::is_enemy(unit, unit_t))
	            return true;
                }

                if (pk::is_valid_pos(neighbor_pos_mark))
                {
                    pk::unit@ unit_m = pk::get_unit(neighbor_pos_mark);	
										
                    if (pk::is_alive(unit_m) and unit_m.get_id() != unit.get_id() and pk::is_enemy(unit, unit_m))
	            return true;					
                }
            }  
            }			
	return false;
        }
		
        //---------------------------------------------------------------------------------------

        //---------------------------------------------------------------------------------------
        // 적부대가 아군부대와 직접 마주할 상황 (2022.06. 일송정 추가)
        pk::unit@ get_neighbor_enemy_unit(pk::unit@ unit)
        {
            pk::array<pk::point> arr_range = pk::get_movable_pos(unit);  // 이동가능좌표
            for (int j = 0; j < int(arr_range.length); j++)
            {
                pk::point pos = arr_range[j];				
            for (int i = 0; i < 방향_끝; i++)
            {
                pk::point neighbor_pos = pk::get_neighbor_pos(pos, i);				
                pk::point neighbor_pos_mark = pk::get_neighbor_pos(unit.pos, i);
                if (pk::is_valid_pos(neighbor_pos))
                {
                    pk::unit@ unit_t = pk::get_unit(neighbor_pos);

                    if (pk::is_alive(unit_t) and unit_t.get_id() != unit.get_id() and pk::is_enemy(unit, unit_t))
                        return unit_t;
                }

                if (pk::is_valid_pos(neighbor_pos_mark))
                {
                    pk::unit@ unit_m = pk::get_unit(neighbor_pos_mark);	
										
                    if (pk::is_alive(unit_m) and unit_m.get_id() != unit.get_id() and pk::is_enemy(unit, unit_m))
                        return unit_m;					
                }
            }  
            }			
            return null;
        }
        //---------------------------------------------------------------------------------------

        //---------------------------------------------------------------------------------------
        // 적부대가 우리 거점 경계 범위 까지 올 수 있는 상황
        pk::building@ get_neighbor_enemy_base(pk::unit@ unit)
        {
            pk::array<pk::point> arr_range = pk::get_movable_pos(unit);  // 이동가능좌표
            for (int j = 0; j < int(arr_range.length); j++)
            {
                pk::point pos = arr_range[j];				

                pk::array<pk::point> arr_t = pk::range(pos, 1, 4);   // 주변좌표
                pk::array<pk::point> arr_tm = pk::range(unit.pos, 1, 4);   // 주변좌표	
                for (int j = 0; j < int(arr_t.length); j++)
                {				
                if (pk::is_valid_pos(arr_t[j]))
                {
                    pk::building@ base = pk::get_building(arr_t[j]);
                    if (pk::is_alive(base) and pk::is_enemy(unit, base))
                        return base;
                }
                }
                for (int j = 0; j < int(arr_tm.length); j++)
                {				
                if (pk::is_valid_pos(arr_tm[j]))
                {
                    pk::building@ base_mark = pk::get_building(arr_tm[j]);

                    if (pk::is_alive(base_mark) and pk::is_enemy(unit, base_mark))
                        return base_mark;

                }
                }				            
            }			
            return null;
        }
        //---------------------------------------------------------------------------------------
        //---------------------------------------------------------------------------------------

        // ***** 적 부대의 아군 거점 근처 존재 여부***** //
        bool no_enemy_around(pk::building@ base)
        {

			int enemy_units3 = 0;
			int enemy_troops3 = 0;

			auto range = pk::range(base.get_pos(), 1, 10);
			for (int i = 0; i < int(range.length); i++)
			{
				auto unit = pk::get_unit(range[i]);
				if (pk::is_alive(unit))
				{
					int distance = pk::get_distance(base.get_pos(), range[i]);
					if (pk::is_enemy(base, unit))
					{

						if (distance <= 10)
						{
							enemy_units3++;
							enemy_troops3 += unit.troops;
						}
					}

					else
					{
					}
				}
			}


	
		if (enemy_troops3 == 0 and enemy_units3 == 0)					
	            return true;

				
            
	return false;
        }

        //---------------------------------------------------------------------------------------



	};

	Main main;
}