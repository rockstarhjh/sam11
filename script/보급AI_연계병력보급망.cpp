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
 
    const bool  위임군단_수송관할_지정여부  = true;    //플레이어 위임군단이 수송을 보낼 수 있는 군단 구분해줄 것인지 여부, false면 모든 군단 상대로 수송대 보냄
 
    const bool 대사표시_설정 = true; 

    
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
			if ( pk::is_normal_force(force_id) and pk::get_elapsed_months() > 3)
			{
				for (int i = 0; i < 건물_도시끝; i++)
				{
					auto base = pk::get_building(i);
                                        pk::district@ district = pk::get_district(base.get_district_id());


	if (!force.is_player() or ( force.is_player() and !pk::is_player_controlled(base) and pk::is_alive(district) and district.transport ) )

		{

                    if (base.get_force_id() == force_id and needChaintroops0(base))
                        PushChaintroops0(base);              //  준전방에서 전방으로 지원군 파병 (병력 수송)

                    if (base.get_force_id() == force_id and needChaintroops0_PortF(base))
                        PushChaintroops0_PortF(base);        //  준전방에서 전방의 항관으로 지원군 파병 (군량 수송)

                    if (base.get_force_id() == force_id and needChain2troops(base))
                        PushChain2troops(base);              //  평시 후방에서 전선으로 순차 보급대 보내기  (병력)



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

        int enemy_weight = countNeighborEnemyBase(base);	

	// 병력 5만 이상 있고, 적과 맞닿은 도시에서 보급 보내라
	if (enemy_weight > 0 and 50000 <= base_troops and 건물_도시시작 <= base.get_id() and base.get_id() < 건물_도시끝 and 1 <= func_enemy_city_count(city_a, 2) )
				return true;

	// 병력 3만 5천 이상 있고, 적 침공에서 안전한 준전방 도시에서 보급 보내라
	if (enemy_weight == 0 and 35000 <= base_troops and 건물_도시시작 <= base.get_id() and base.get_id() < 건물_도시끝 and 1 <= func_enemy_city_count(city_a, 2) )
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
            actors.clear();			
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
            int reinforce_troops = pk::min(pk::get_command(leader), pk::max(10000 , pk::get_troops(base) - 10000));

            // 최적 무기 선택
            int ground_weapon_id = 병기_검;
            int water_weapon_id = 병기_주가;

            
            // 육상 무기 선택
            get_ground_weapon0(base, leader, reinforce_troops, ground_weapon_id, reinforce_troops);
            if (ground_weapon_id == 0) return false;    // 병기 부족
            
            // 수상 무기 선택
            if (pk::get_weapon_amount(base, 병기_누선) < 10 and pk::get_weapon_amount(base, 병기_투함) < 10
			and leader.mibun != 신분_군주 and leader.mibun != 신분_도독 and leader.mibun != 신분_태수 and leader.mibun == 신분_일반
			and leader.tekisei[병종_수군] == 적성_C)
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

                string target_name = pk::u8decode(pk::get_name(pk::get_building(target)));
	if (대사표시_설정) 
                pk::say(pk::u8encode(pk::format("여기서부턴 접경지대다!\n전투병들로 \x1b[2x{}\x1b[0x(을)를 지원하라!", target_name)), leader);	
				
                // 출진.
                int unit_id = pk::command(cmd);
                if (unit_id != -1)
				pk::get_unit(unit_id).action_done = (!거점수송_원거리이동);

            
            return true;
        }
        
  
        
        //----------------------------------------------------------------------------------
        
        // 무기 선택 함수
        void get_ground_weapon0(pk::building@ base, pk::person@ leader, int troops_max, int &out weapon_sel, int &out troops_sel)
        {
            int troops_min = pk::get_command(leader);
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
			dst_list.clear();			
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


    // src. dst는 alive 상태에, 서로 다른 아이디에, 국적이 같아야
    if (!pk::is_alive(src)) continue;
    if (!pk::is_alive(dst)) continue;
    if (src_id == dst_id) continue;	
    if (src.get_force_id() != dst.get_force_id()) continue;
	
		   
         // 유저 세력의 위임군단이면
         //src의 위임설정 물자 수송지를 플레이어 조종 거점으로 설정하면, 아무 제약없이 플레이어 조종 거점까지도 교류 (플레이어 거점에서 플레이어 의지 상관없이 갑자기 수송대가 나갈수도 있음)   
    if (위임군단_수송관할_지정여부)
    {    		 
         pk::district@ src_district = pk::get_district(src.get_district_id());
         pk::district@ dst_district = pk::get_district(dst.get_district_id());

         if (force.is_player() and !pk::is_player_controlled(src) and pk::is_alive(src_district) and pk::is_alive(dst_district) and src_district.transport) 
         {	
         pk::building@ target_building = pk::get_building(src_district.transport_building);
		 
         // src의 위임설정 물자 수송지가 같은 군단 소속이면 같은 군단 내에서만 이동 가능 , src와 dst의 군단이 다르거나 dst가 플레이어 조종 군단이면 안됨  
         if (target_building.get_district_id() == src_district.get_id() and (src.get_district_id() != dst.get_district_id() or pk::is_player_controlled(dst))) continue;

         // src의 위임설정 물자 수송지가 (플레이어가 조종못하는) 위임군단이고, src의 군단과 다른 곳이면, dst도 위임군단이어야 (dst가 플레이어 조종 군단이면 안된다) = 위임군단끼리만 주고 받는 설정. 플레이어 군단만 제외.
         if (!pk::is_player_controlled(target_building) and target_building.get_district_id() != src_district.get_id() and pk::is_player_controlled(dst)) continue;
         }
     }

		pk::city@ city_a = pk::get_city(pk::get_city_id(src.pos));
        int enemy_weight_dst = countNeighborEnemyBase(dst);

           // 구원군 보내는 곳이 받는 곳보다 2만5천명 이상이면, 접경지대의 도시로 보급 보내라

        if (src_id != dst_id and src.get_force_id() == dst.get_force_id()  and pk::is_alive(src) and pk::is_alive(dst) and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 
		and base2_troops <= pk::get_max_troops(dst) * 0.4f and base2_troops + 25000 <= pk::get_troops(src) and ((0 < enemy_weight_dst and 1 <= func_enemy_city_count(city_a, 1)) or 1 <= enemy_units3 ) )
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
                bool no_enemy_around_a = (main.no_enemy_around(a));
                bool no_enemy_around_b = (main.no_enemy_around(b));
                if (!no_enemy_around_a and  no_enemy_around_b) return true;				
                if ( no_enemy_around_a and !no_enemy_around_b) return false;	

                bool enemies_around_a = (pk::enemies_around(a));
                bool enemies_around_b = (pk::enemies_around(b));
                if ( enemies_around_a and !enemies_around_b) return true;				
                if (!enemies_around_a and  enemies_around_b) return false;				
				
                    return (pk::get_troops(a) < pk::get_troops(b));					
					
                    int build_dist_a = pk::get_building_distance(a.get_id(), main.src_cha0.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.src_cha0.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.src_cha0.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.src_cha0.pos);

                    if (pk::get_troops(a) == pk::get_troops(b) and build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);

                    if (pk::get_troops(a) == pk::get_troops(b) and build_dist_a == build_dist_b)                     
                    return (pos_dist_a < pos_dist_b);
                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
		}











        //----------------------------------------------------------------------------------
        //  준전방에서 전방의 항관으로 지원군 파병 (군량 수송)
        //----------------------------------------------------------------------------------




		/** 병력 있는 거점 찾기 */

		bool needChaintroops0_PortF (pk::building@ base)
		{



			int base_troops = pk::get_troops(base);
            int base_id = base.get_id();		

			pk::city@ city_a = pk::get_city(pk::get_city_id(base.pos));
            pk::list<pk::building@> dst_list; 	
			dst_list.clear();			
			
            for (int i = 건물_관문시작; i < 건물_거점끝; i++)
            {
             pk::building@ dst = pk::get_building(i);
             int dst_id = dst.get_id();		
			pk::city@ city_c = pk::get_city(pk::get_city_id(dst.pos));	
			
        if (base_id != dst_id and base.get_force_id() == dst.get_force_id() and pk::is_alive(base) and pk::is_alive(dst) and 건물_관문시작 <= dst_id and dst_id < 건물_항구끝 
		and (pk::get_food(dst) <= pk::get_troops(dst) * 0.9f or pk::get_gold(dst) <= 500 or pk::get_troops(dst) <= 8000 ) 
		and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id)			 
                dst_list.add(dst);			 
			 
		    }	
			
			if (dst_list.count == 0) 
				return false;			


	// 거점 내 병력 2만 이상
	// 금 보유량 최소 1000
	// 병량 보유량이 최소 2만 이상에 병력의0.8배 이상이어야 함, 병력 2만 이상, 
	// 적 침공에서 안전한 준전방 도시에서 보급 보내라
	if ( pk::get_gold(base) >= 1000 and 20000 <= pk::get_food(base) and pk::get_troops(base) * 0.8f <= pk::get_food(base) and 20000 <= base_troops and 건물_도시시작 <= base.get_id() and base.get_id() < 건물_도시끝 and 1 <= func_enemy_city_count(city_a, 1) )
				return true;


            
			return false;
		}







		/** 전투부대 파견 */

		bool PushChaintroops0_PortF (pk::building@ base)
		{
			// 명령 가능한 무장이 있는지 확인.
			auto person_list = pk::get_idle_person_list(base);
			if (person_list.count == 0) return false;

			// 수송할 인접 거접이 있는지 확인.
			int target = getUrgentBase0_PortF(base);
			if (target == -1) return false;

            pk::list<pk::person@> actors;
            actors.clear();				
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

                
				return (a.stat[무장능력_무력] + a.stat[무장능력_통솔]) < (b.stat[무장능력_무력] + b.stat[무장능력_통솔]);
			});
            pk::person@ leader = pk::get_person(actors[0].get_id());
            
            // 원군 병력 산정 : 기준 병력 초과분, 지휘가능병력 확인
            int reinforce_troops = pk::min(4888, pk::max(int (pk::get_troops(base) * 0.35f) , pk::get_troops(base) - 10000));

            // 최적 무기 선택
            int ground_weapon_id = 병기_검;
            int water_weapon_id = 병기_주가;

            
            // 육상 무기 선택
            get_ground_weapon0_PortF(base, leader, reinforce_troops, ground_weapon_id, reinforce_troops);
            if (ground_weapon_id == 0) return false;    // 병기 부족
            
            // 수상 무기 선택
            if (pk::get_weapon_amount(base, 병기_누선) < 10 and pk::get_weapon_amount(base, 병기_투함) < 10
			and leader.mibun != 신분_군주 and leader.mibun != 신분_도독 and leader.mibun != 신분_태수 and leader.mibun == 신분_일반
			and leader.tekisei[병종_수군] == 적성_C)
                water_weapon_id = 병기_주가;
            else
            {
                if      (pk::get_weapon_amount(base, 병기_누선) > 0) water_weapon_id = 병기_누선;
                else if (pk::get_weapon_amount(base, 병기_투함) > 0) water_weapon_id = 병기_투함;
            }
            
            // 병량 계산
            pk::building@ target_building = pk::get_building(target);			

            // 병량비율- 목적지 군량이 병력대비 0.9배 이하면 (병량 지원이 필요한 상태) 
			// 1번 = 지원군 * 3.5배의 군량을 가져감. 
			// 2번 = 지원군 * 1.7배의 군량밖에 못가져가면 부대병량 부족으로 간주. (지원 못보냄) 
			// 3번 = 출발하는 거점에서 지원군과 지원병량 내보낸 후 남은 병량이 병력 대비 0.4배면 거점 병량 부족으로 간주. (지원 못보냄)			
            float food_ratio_1 = (pk::get_troops(target_building) * 0.9f >= pk::get_food(target_building)) ? 3.5f : 2.0f;
            float food_ratio_2 = (pk::get_troops(target_building) * 0.9f >= pk::get_food(target_building)) ? 1.7f : 0.9f;			
            float food_ratio_3 = (pk::get_troops(target_building) * 0.9f >= pk::get_food(target_building)) ? 0.4f : 0.5f;	
			
            int unit_food = int(pk::min( 0.3f * pk::get_food(base), food_ratio_1 * reinforce_troops));
            if (unit_food < int(food_ratio_2 * reinforce_troops)) return false;   // 병량 부족
            if (pk::get_food(base) - unit_food < (pk::get_troops(base) - reinforce_troops) * food_ratio_3) return false;   // 거점 병량 부족
            
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

                string target_name = pk::u8decode(pk::get_name(target_building));																	 
	if (대사표시_설정)
    {		
	       if (pk::get_troops(target_building) * 0.9f >= pk::get_food(target_building) and pk::get_gold(target_building) > 500)		
                pk::say(pk::u8encode(pk::format("군량이 부족한 항관까지 접경지대다!\n전투병들로 \x1b[2x{}\x1b[0x에 수송하겠다!", target_name)), leader);	
				
	       else if (pk::get_troops(target_building) * 0.9f < pk::get_food(target_building) and pk::get_gold(target_building) <= 500)		
                pk::say(pk::u8encode(pk::format("금이 부족한 항관까지 접경지대다!\n전투병들로 \x1b[2x{}\x1b[0x에 수송하겠다!", target_name)), leader);	
				
	       else if (pk::get_troops(target_building) * 0.9f >= pk::get_food(target_building) and pk::get_gold(target_building) <= 500)		
                pk::say(pk::u8encode(pk::format("금과 군량이 부족한 항관까지 접경지대다!\n전투병들로 \x1b[2x{}\x1b[0x에 수송하겠다!", target_name)), leader);	

	       else	
                pk::say(pk::u8encode(pk::format("병력이 부족한 항관까지 접경지대다!\n전투병들로 \x1b[2x{}\x1b[0x에 수송하겠다!", target_name)), leader);	
								
    }
                // 출진.
                int unit_id = pk::command(cmd);
                if (unit_id != -1)
				pk::get_unit(unit_id).action_done = (!거점수송_원거리이동);

            
            return true;
        }
        
  
        
        //----------------------------------------------------------------------------------
        
        // 무기 선택 함수
        void get_ground_weapon0_PortF(pk::building@ base, pk::person@ leader, int troops_max, int &out weapon_sel, int &out troops_sel)
        {
            int troops_min = 4888;
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


        pk::building@ src_cha0_PortF;
		int getUrgentBase0_PortF(pk::building@ src)
		{
			int best_dst = -1;
			int best_distance = 0;


            int src_id = src.get_id();
            pk::list<pk::building@> dst_list;
			dst_list.clear();			
            @src_cha0_PortF = @src;

                       
            pk::force@ force = pk::get_force(src.get_force_id());
            
            
			// 수송 거점 검색

                for (int i = 0; i < 건물_거점끝; i++)
                {
                    pk::building@ dst = pk::get_building(i);
                    int dst_id = dst.get_id();
			int base2_troops = pk::get_troops(dst);

            int max_distance = (dst_id >= 건물_도시끝)? 2 : 1;




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


    // src. dst는 alive 상태에, 서로 다른 아이디에, 국적이 같아야
    if (!pk::is_alive(src)) continue;
    if (!pk::is_alive(dst)) continue;
    if (src_id == dst_id) continue;	
    if (src.get_force_id() != dst.get_force_id()) continue;
	
		   
         // 유저 세력의 위임군단이면
         //src의 위임설정 물자 수송지를 플레이어 조종 거점으로 설정하면, 아무 제약없이 플레이어 조종 거점까지도 교류 (플레이어 거점에서 플레이어 의지 상관없이 갑자기 수송대가 나갈수도 있음)   
    if (위임군단_수송관할_지정여부)
    {    		 
         pk::district@ src_district = pk::get_district(src.get_district_id());
         pk::district@ dst_district = pk::get_district(dst.get_district_id());

         if (force.is_player() and !pk::is_player_controlled(src) and pk::is_alive(src_district) and pk::is_alive(dst_district) and src_district.transport) 
         {	
         pk::building@ target_building = pk::get_building(src_district.transport_building);
		 
         // src의 위임설정 물자 수송지가 같은 군단 소속이면 같은 군단 내에서만 이동 가능 , src와 dst의 군단이 다르거나 dst가 플레이어 조종 군단이면 안됨  
         if (target_building.get_district_id() == src_district.get_id() and (src.get_district_id() != dst.get_district_id() or pk::is_player_controlled(dst))) continue;

         // src의 위임설정 물자 수송지가 (플레이어가 조종못하는) 위임군단이고, src의 군단과 다른 곳이면, dst도 위임군단이어야 (dst가 플레이어 조종 군단이면 안된다) = 위임군단끼리만 주고 받는 설정. 플레이어 군단만 제외.
         if (!pk::is_player_controlled(target_building) and target_building.get_district_id() != src_district.get_id() and pk::is_player_controlled(dst)) continue;
         }
     }

   
           // 전방 혹은 적이 쳐들어온 항관 중 
           // 군량 보유량이 병력 대비 0.9배 이하 (항관이 적의 도시 소속일 경우에 한해)
		   // 금 보유량이 500 이하 (항관이 적의 도시 소속일 경우에 한해)
		   // 병력 8천 이하		   
        int enemy_weight = countNeighborEnemyBase(dst);		   

        if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst) and 건물_관문시작 <= dst_id and dst_id < 건물_항구끝    
		and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id)
               {

        if ((pk::get_food(dst) <= pk::get_troops(dst) * 0.9f or pk::get_gold(dst) <= 500) and dst.get_force_id() != city_c.get_force_id()
	    and (1 <= enemy_units3 or enemy_weight > 0 or 1 <= func_enemy_city_count(city_c, 1) ))
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 수송가능 거점리스트 추가
                    }
					
        if (pk::get_troops(dst) <= 8000 and func_already (dst) == 0 and no_enemy_around(src) and !pk::enemies_around(dst)
	    and (1 <= enemy_units3 or enemy_weight > 0))
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 수송가능 거점리스트 추가
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
                    return (float(pk::get_food(a)) / float(pk::get_troops(a) + 1) < float(pk::get_food(b)) / float(pk::get_troops(b) + 1));					
					
                    int build_dist_a = pk::get_building_distance(a.get_id(), main.src_cha0_PortF.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.src_cha0_PortF.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.src_cha0_PortF.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.src_cha0_PortF.pos);

                    if (float(pk::get_food(a)) / float(pk::get_troops(a)) == float(pk::get_food(b)) / float(pk::get_troops(b)) and build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);

                    if (float(pk::get_food(a)) / float(pk::get_troops(a)) == float(pk::get_food(b)) / float(pk::get_troops(b)) and build_dist_a == build_dist_b)                     
                    return (pos_dist_a < pos_dist_b);
                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
		}







        //----------------------------------------------------------------------------------
        //  평시 후방에서 전선으로 순차 보급대 보내기  (병력)
        //----------------------------------------------------------------------------------




		/** 병력 있는 거점 찾기 */

		bool needChain2troops (pk::building@ base)
		{
			if (!no_enemy_around(base)) return false;

			int base_troops = pk::get_troops(base);

			pk::city@ city_a = pk::get_city(pk::get_city_id(base.pos));

	      for (int k = 0; k < 11; k++)
		  {

	// 병력 5만 이상 있고, 적 침공에서 안전한 도시에서 보급 보내라
	if (  50000 <= base_troops and 건물_도시시작 <= base.get_id() and base.get_id() < 건물_도시끝 and 1 <= func_enemy_city_count(city_a, k + 2) and  func_enemy_city_count(city_a, k + 1) == 0)
				return true;

		   }


            
			return false;
		}







		/** 35% 보급 명령 */

		bool PushChain2troops(pk::building@ base)
		{

            int reinforce_troops = pk::min(15000, pk::max(5000, int (pk::get_troops(base) * 0.35f) ));
			// 명령 가능한 무장이 있는지 확인.
			auto person_list = pk::get_idle_person_list(base);
			if (person_list.count == 0) return false;

			// 수송할 인접 거접이 있는지 확인.
			int target = getBackup2Cha(base);
			if (target == -1) return false;

            if (target >= 건물_도시끝)
            reinforce_troops = pk::min(4500, pk::max(3000, int (pk::get_troops(base) * 0.35f) ));

            pk::list<pk::person@> actors;
            actors.clear();					
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

                string target_name = pk::u8decode(pk::get_name(pk::get_building(target)));
	if (대사표시_설정) 
                pk::say(pk::u8encode(pk::format("후방에서 전선으로!\n연계보급으로 \x1b[2x{}\x1b[0x(을)를 지원하라!", target_name)), leader);	
            
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
			dst_list.clear();			
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


    // src. dst는 alive 상태에, 서로 다른 아이디에, 국적이 같아야
    if (!pk::is_alive(src)) continue;
    if (!pk::is_alive(dst)) continue;
    if (src_id == dst_id) continue;	
    if (src.get_force_id() != dst.get_force_id()) continue;
	
		   
         // 유저 세력의 위임군단이면
         //src의 위임설정 물자 수송지를 플레이어 조종 거점으로 설정하면, 아무 제약없이 플레이어 조종 거점까지도 교류 (플레이어 거점에서 플레이어 의지 상관없이 갑자기 수송대가 나갈수도 있음)   
    if (위임군단_수송관할_지정여부)
    {    		 
         pk::district@ src_district = pk::get_district(src.get_district_id());
         pk::district@ dst_district = pk::get_district(dst.get_district_id());

         if (force.is_player() and !pk::is_player_controlled(src) and pk::is_alive(src_district) and pk::is_alive(dst_district) and src_district.transport) 
         {	
         pk::building@ target_building = pk::get_building(src_district.transport_building);
		 
         // src의 위임설정 물자 수송지가 같은 군단 소속이면 같은 군단 내에서만 이동 가능 , src와 dst의 군단이 다르거나 dst가 플레이어 조종 군단이면 안됨  
         if (target_building.get_district_id() == src_district.get_id() and (src.get_district_id() != dst.get_district_id() or pk::is_player_controlled(dst))) continue;

         // src의 위임설정 물자 수송지가 (플레이어가 조종못하는) 위임군단이고, src의 군단과 다른 곳이면, dst도 위임군단이어야 (dst가 플레이어 조종 군단이면 안된다) = 위임군단끼리만 주고 받는 설정. 플레이어 군단만 제외.
         if (!pk::is_player_controlled(target_building) and target_building.get_district_id() != src_district.get_id() and pk::is_player_controlled(dst)) continue;
         }
     }

			if (!no_enemy_around(dst)) continue;


           // 병력 최대 기준 50% 이하로, 접경지대의 도시로 보급 보내라

	for (int k = 0; k < 11; k++)
	{
if (1 <= func_enemy_city_count(city_a, k + 2) and  func_enemy_city_count(city_a, k + 1) == 0)
	    {
    if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst)  and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and base2_troops <= pk::get_max_troops(dst) * 0.50f and 1 <= func_enemy_city_count(city_c, k + 1) 
	and ((k > 0 and func_enemy_city_count(city_c, k ) == 0) or (k == 0 and base_dist <= 3)) and func_already (dst) <= 2 and func_supplycheck(src,dst) == 0 )
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

                    if (pk::get_troops(a) == pk::get_troops(b) and build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);

                    if (pk::get_troops(a) == pk::get_troops(b) and build_dist_a == build_dist_b)                    
                    return (pos_dist_a < pos_dist_b);
                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
		}






         //  거리에 따른 거점 주변 적대 도시 숫자 체크, masterpiecek님의 AI_도시물자수송.cpp﻿를 참조했습니다.

		int func_enemy_city_count(pk::city@ city, int distance)
		{
			int enemy_cities = 0;
			for (int city_id = 0; city_id < 도시_끝; city_id++)
			{
				pk::city@ enemy_city = pk::get_city(city_id);
				if (!pk::is_alive(enemy_city)) continue;

				// 검색기준 도시 제외
				if (city.get_id() == city_id) continue;

				// 검색기준 도시와 확인대상 도시가 적이 아닌 경우 제외
				if (!pk::is_enemy(city, enemy_city)) continue;

				// 도시 간 거리가 일정거리를 초과하는 경우 제외
				int city_distance = pk::get_city_distance(city.get_id(), city_id);
				if (city_distance > distance) continue;

				enemy_cities++;
			}

			return enemy_cities;
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

			    int target = get_neighbor_enemy_unit(unit_e);		  
                pk::unit@ unit_f = pk::get_unit(target);
				
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
			        int target = get_neighbor_enemy_base(unit_e);
			        int target2 = get_neighbor_enemy_base_2(unit_e);					
                    pk::building@ base_t = pk::get_building(target);
                    pk::building@ base_k = pk::get_building(target2);
					
				if (pk::is_alive(base_t) and base_t.get_id() == base.get_id())					
	            return true;
			
				else if (pk::is_alive(base_k) and base_k.get_id() == base.get_id())					
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

                else if (pk::is_valid_pos(neighbor_pos_mark))
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
		int get_neighbor_enemy_unit(pk::unit@ unit)
        {
			int best_unit = -1;			
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
                        best_unit = unit_t.get_id();
                }

                else if (pk::is_valid_pos(neighbor_pos_mark))
                {
                    pk::unit@ unit_m = pk::get_unit(neighbor_pos_mark);	
										
                    if (pk::is_alive(unit_m) and unit_m.get_id() != unit.get_id() and pk::is_enemy(unit, unit_m))
                        best_unit = unit_m.get_id();				
                }
            }  
            }			
			return best_unit;
        }
        //---------------------------------------------------------------------------------------

        //---------------------------------------------------------------------------------------
        // 적부대가 우리 거점 경계 범위 까지 올 수 있는 상황
		int get_neighbor_enemy_base(pk::unit@ unit)
        {
			int best_dst = -1;		
			
            pk::array<pk::point> arr_range = pk::get_movable_pos(unit);  // 이동가능좌표
            for (int j = 0; j < int(arr_range.length); j++)
            {
                pk::point pos = arr_range[j];				

                pk::array<pk::point> arr_t = pk::range(pos, 1, 4);   // 주변좌표
	
                for (int k = 0; k < int(arr_t.length); k++)
                {				
                if (pk::is_valid_pos(arr_t[k]))
                {
                    pk::building@ base = pk::get_building(arr_t[k]);
                    if (pk::is_alive(base) and base.get_id() < 건물_거점끝 and pk::is_enemy(unit, base))
                        best_dst = base.get_id();
                }
                }

            }			
			return best_dst;
        }		
		
		int get_neighbor_enemy_base_2(pk::unit@ unit)
        {
			    int best_dst = -1;			
                pk::array<pk::point> arr_tm = pk::range(unit.pos, 1, 4);   // 주변좌표

                for (int j = 0; j < int(arr_tm.length); j++)
                {				
                if (pk::is_valid_pos(arr_tm[j]))
                {
                    pk::building@ base_mark = pk::get_building(arr_tm[j]);

                    if (pk::is_alive(base_mark) and base_mark.get_id() < 건물_거점끝 and pk::is_enemy(unit, base_mark))
                        best_dst = base_mark.get_id();

                }
                }				            
            			
			return best_dst;
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

				}
			}


	
		if (enemy_troops3 == 0 and enemy_units3 == 0)					
	            return true;

				
            
	return false;
        }

        //---------------------------------------------------------------------------------------

        // ***** 주변 적거점 수 확인 ***** //
        int countNeighborEnemyBase(pk::building@ src)
        {
            int weight = 0;
            int troops = 0;
            for (int i = 0; i < 건물_거점끝; i++)
			{
                pk::building@ dst = pk::get_building(i);
                int src_id = src.get_id();
                int dst_id = dst.get_id();
                
                if (src_id != dst_id and pk::is_neighbor_base(src_id, dst_id) and pk::is_enemy(src, dst))
                    troops += pk::get_troops(dst);
            }
            
            weight = int(troops);
            return weight;
        }
		
        //---------------------------------------------------------------------------------------


	};

	Main main;
}