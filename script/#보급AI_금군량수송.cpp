/*
제작 by 일송정

본 스크립트는 기마책사님이 제작하신 거점원군.cpp와 기마책사님이 수정하신 거점철수.cpp의 상당 부분을 차용하고 있음을 알려드립니다. 
기마책사님께 감사드립니다.

*/

namespace 금군량수송
{

    //---------------------------------------------------------------------------------------
    // 유저 설정_기마책사님 자료에서 따옴
    
    const bool  거점수송_원거리이동  = true;     // 수송부대 이동 1회 추가 (추천기능 : 보너스이동으로 탈출)
    const bool  거점수송_일시도주설정 = false;     // 수송부대 출진순간 도주효과 일시적용 (추천기능 : 포위망 돌파가능)
    const int   거점수송_거점검색모드 = 1;       // 0: 도시만 검색하여 수송,  1: 도시+관문+항구 모두 검색하여 수송  


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
			if (pk::is_normal_force(force_id))
			{
				for (int i = 0; i < 건물_거점끝; i++)
				{
					auto base = pk::get_building(i);
                                        pk::district@ district = pk::get_district(base.get_district_id());	

	if (!force.is_player() or ( force.is_player() and !pk::is_player_controlled(base) and pk::is_alive(district) and district.transport ) )

		{
                    if (base.get_force_id() == force_id and needGEXfood(base))
                        PushGEXfood(base);           //  전투 중인 항관에서도 군량이 너무 많으면 인근 도시로 수송  (군량)


                    if (base.get_force_id() == force_id and needEXgold(base))
                        PushEXgold(base);           //  물자 포화 상태일때 다른 곳으로 배분  (금)


                    if (base.get_force_id() == force_id and needEXfood(base))
                        PushEXfood(base);           //  물자 포화 상태일때 다른 곳으로 배분  (군량)


                    if (base.get_force_id() == force_id and needPeacetimegold(base))
                        PushPeacetimegold(base);    //  평시 보급대 보내기  (금)


                    if (base.get_force_id() == force_id and needPeacetimefood(base))
                        PushPeacetimefood(base);    //  평시 보급대 보내기  (군량)


                    if (base.get_force_id() == force_id and needERgold(base))
                        PushERgold(base);           //   (금) 바닥났을 때 긴급 수송


                    if (base.get_force_id() == force_id and needERfood(base))
                        PushERfood(base);           //  (군량) 바닥났을 때 긴급 수송 


                    if (base.get_force_id() == force_id and needXERgold(base))
                        PushXERgold(base);          //   접경지 (금) 바닥났을 때 긴급 수송 - 항구 관문에서 도시로


                    if (base.get_force_id() == force_id and needXERgold1(base))
                        PushXERgold1(base);         //   접경지 (금) 바닥났을 때 긴급 수송 - 도시에서 항구 관문으로 


                    if (base.get_force_id() == force_id and needXERfood(base))
                        PushXERfood(base);          //  접경지 (군량) 바닥났을 때 긴급 수송 - 항구 관문에서 도시로


                    if (base.get_force_id() == force_id and needXERfood1(base))
                        PushXERfood1(base);         //  접경지 (군량) 바닥났을 때 긴급 수송 - 도시에서 항구 관문으로


	       }

				}
			}

			// 이전 핸들러가 있다면 체인.
			if (prev_callback_ !is null)
				return prev_callback_(force);
			return false;
		}







        //----------------------------------------------------------------------------------
        // 전투 중인 항관에서도 군량이 너무 많으면 인근 도시로 수송  (군량)
        //----------------------------------------------------------------------------------




		/** 병력 있는 거점 찾기 */

		bool needGEXfood(pk::building@ base)
		{
			// 근접한 적 부대 수
			int enemy_units1 = 0;
			int enemy_troops1 = 0;

			// 3칸 이내 적 부대 수
			int enemy_units3 = 0;
			// 3칸 이내 적 병력 수
			int enemy_troops3 = 0;



			int force_units7 = 0;



			auto range = pk::range(base.get_pos(), 1, 10);
			for (int i = 0; i < int(range.length); i++)
			{
				auto unit = pk::get_unit(range[i]);
				if (pk::is_alive(unit))
				{
					int distance = pk::get_distance(base.get_pos(), range[i]);
					if (pk::is_enemy(base, unit))
					{
						if (distance <= 1)
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


					else if (base.get_force_id() == unit.get_force_id() and unit.type == 부대종류_전투)
					{
                                                if (distance <= 4)
						{
							force_units7++;
						}
					}


					else
					{
					}
				}
			}

			if (enemy_units1 >= 10)  // 거점 포위 상태로 수송 불가
				return false;
						
			int base_troops = pk::get_troops(base);


                        int enemy_weight = countNeighborEnemyBase(base);
            pk::city@ city_a = pk::get_city(pk::get_city_id(base.pos));




	//  주변에 적이 있으면서 아군부대도 있으며 병력 대비 군량이 3.5배 이상 있고 병량이 45000이상인 병력은 6800 이상 있는 항관

if (건물_관문시작 <= base.get_id() and base.get_id() < 건물_항구끝 and pk::get_troops(base) * 3.5f <= pk::get_food(base) and 45000 <= pk::get_food(base) and force_units7 > 0 and enemy_troops3 > 0 and enemy_units3 > 0 and 6800 <= pk::get_troops(base) )
				return true;

            
			return false;
		}







		/** 군량 병력 2배분 남기고 보급 명령 (나머지 5%)  */

		bool PushGEXfood(pk::building@ base)
		{
            int reinforce_troops = pk::min(1000,  int (pk::get_troops(base) * 0.15f) );
			// 명령 가능한 무장이 있는지 확인.
			auto person_list = pk::get_idle_person_list(base);
			if (person_list.count == 0) return false;

			//  인접 거접이 있는지 확인.
			int target = getGEXFBase(base);
			if (target == -1) return false;

			if (enemy_approach(pk::get_building(target))) return false;

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
         

            int unit_food = pk::get_food(base) - (pk::get_troops(base) * 2.5f);
            if (unit_food < int(1.0f * reinforce_troops)) return false;   // 병량 부족     

            float supply_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            float weapon_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            
			// 출진 명령 정보 생성.
			pk::com_deploy_cmd_info cmd;
			@cmd.base = @base;
			cmd.type = 부대종류_수송;
			cmd.member[0] = leader.get_id();
			cmd.gold = pk::min(int(pk::get_gold(base) * 0.4f), 10000);
                if (건물_관문시작 <= base.get_id() and base.get_id() < 건물_항구끝)
			cmd.food = pk::min(pk::max (int(pk::get_food(base) * 0.20f) , unit_food), 60000);

                if (건물_도시시작 <= base.get_id() and base.get_id() < 건물_도시끝)			
			cmd.food = pk::min(pk::max (int(pk::get_food(base) * 0.20f) , unit_food), 60000);
			cmd.troops = reinforce_troops;
			int i = 0;
			for (int weapon_id = 0; weapon_id < 병기_끝; weapon_id++)
			{
                int weapon_amount = 0;
                if (weapon_id < 병기_충차)
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id) * 0.3f), 4000);
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
                pk::say(pk::u8encode(pk::format("이곳이 전투 중이긴 하나\n군량을 \x1b[2x{}\x1b[0x(으)로 수송하라!", pk::u8decode(pk::get_name(pk::get_building(target)))  )), leader);	
            
            // 임시 도주 효과 ('19.3.6)
            if (거점수송_일시도주설정)
            {
                leader.skill = retreat_skill;         // 특기 복원
            }
            
            
			return true;
		}





        
		/** 가장 가깝고 위기에 빠진 아군 도시에 보급을 보냄 */

        pk::building@ src_GEXF;
		int getGEXFBase(pk::building@ src)
		{
			int best_dst = -1;
			int best_distance = 0;
            int src_id = src.get_id();
            pk::list<pk::building@> dst_list; 
            @src_GEXF = @src;



            
            int search_base = 건물_도시끝;
            if      (거점수송_거점검색모드 == 0) search_base = 건물_도시끝;
            else if (거점수송_거점검색모드 == 1) search_base = 건물_거점끝;
            
            pk::force@ force = pk::get_force(src.get_force_id());
            
			// 거점 검색

                for (int i = 0; i < search_base; i++)
                {
                    pk::building@ dst = pk::get_building(i);
                    int dst_id = dst.get_id();
			int base2_troops = pk::get_troops(dst);


                    // 도시거리
                    int city_dist = -1;
                    if (dst_id < 건물_도시끝 and src_id < 건물_도시끝)
                        city_dist = pk::get_city_distance(dst_id, src_id);
                    
                    // 거점거리
                    int base_dist = pk::get_building_distance(dst_id, src_id, src.get_force_id());
                    
                    // 거리 조건 만족 시 (거리 1~3)
                if ( (base_dist == 1 and !intercept1_Enemy_base(src, dst) and !intercept_delta_Enemy_base(src, dst)) or (base_dist == 2 and Between_Enemy_base(src) == 0 and Between_Enemy_base(dst) == 0 and Between_Friendly_base(src) > 0 and Between_Friendly_base(dst) > 0) ) 
                    {
                       // 목적지가 메뚜기 재해지역이면서 병력 대비 병량이 1.5배 초과면 안감. (전방 도시라 병력 출진 필요. 병력대비 1.5 이하면 병량 수송함)
	          pk::city@ city_c = pk::get_city(pk::get_city_id(dst.pos));
                        if (city_c.inago and pk::get_troops(dst) * 1.5f < pk::get_food(dst))  continue;

                        int enemy_weight = countNeighborEnemyBase(dst);

	// 병량 3만 6천 이상에 병력 대비 4.5배 이상 있거나, 병량 최대 보유까지 20만 이하 여유 밖에 안남았거나, 도시보다 오히려 병량이 많은, 적 침공 중인 병력 6천 8백 이상 관문, 항구에서 보급 보내라

        if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst))
	   {

            if ((36000 <= pk::get_food(src) and pk::get_food(src) >= pk::get_troops(src) * 4.5f) or pk::get_max_food(src) - pk::get_food(src) <= 200000 or pk::get_food(src) >= pk::get_food(dst)) 
    	       {
                   
	// 군량이 5만 이하나 병력 대비 4배 이하이거나 병량 최대 보유까지 40만 이상 남은 도시로 보급 보내라
                    
        if (건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and  ( pk::get_max_food(dst) - pk::get_food(dst) >= 400000 or pk::get_troops(dst) * 4.f >= pk::get_food(dst)) and func_already (dst) <= 3)
                    {
             if (!enemy_inside(src, dst))
                        {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
                        }
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
                    return (float(pk::get_food(a) + 10) / float(pk::get_troops(a) + 10) < float(pk::get_food(b) + 10) / float(pk::get_troops(b) + 10));	

                    int build_dist_a = pk::get_building_distance(a.get_id(), main.src_GEXF.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.src_GEXF.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.src_GEXF.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.src_GEXF.pos);

                    if (build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);
                    
                    return (pos_dist_a < pos_dist_b);
                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
		}




        // ***** 주변 적 항관 병력 수 확인 ***** //
        int Between_Enemy_base(pk::building@ src)
        {
            int weight = 0;
            int troops = 0;
            for (int i = 0; i < 건물_거점끝; i++)
			{
                pk::building@ dst = pk::get_building(i);
                int src_id = src.get_id();
                int dst_id = dst.get_id();
                
                if (src_id != dst_id and pk::is_neighbor_base(src_id, dst_id) and pk::is_enemy(src, dst) and dst_id >= 건물_관문시작 and dst_id < 건물_거점끝 )
                    troops += pk::get_troops(dst);
            }
            
            weight = int(troops / 3000);
            return weight;
        }



        // ***** 주변 아군 항관 병력 수 확인 ***** //
        int Between_Friendly_base(pk::building@ src)
        {
            int weight = 0;
            int troops = 0;
            for (int i = 0; i < 건물_거점끝; i++)
			{
                pk::building@ dst = pk::get_building(i);
                int src_id = src.get_id();
                int dst_id = dst.get_id();
                
                if (src_id != dst_id and pk::is_neighbor_base(src_id, dst_id) and !pk::is_enemy(src, dst) and dst_id >= 건물_관문시작 and dst_id < 건물_거점끝 )
                    troops += pk::get_troops(dst);
            }
            
            weight = int(troops / 3000);
            return weight;
        }






        //----------------------------------------------------------------------------------
        //  물자 포화 상태일때 다른 곳으로 배분  (금)
        //----------------------------------------------------------------------------------




		/** 병력 있는 거점 찾기 */

		bool needEXgold(pk::building@ base)
		{

			if (!no_enemy_around(base)) return false;

			int base_troops = pk::get_troops(base);


                        int enemy_weight = countNeighborEnemyBase(base);
            pk::city@ city_a = pk::get_city(pk::get_city_id(base.pos));

	//  금 1만 이상 있고 , 적 침공에서 안전한 병력 2천 이상 관문, 항구에서 보급 보내라

if ( 10000 <= pk::get_gold(base) and pk::get_troops(base) * 0.6f <= pk::get_gold(base) and 건물_관문시작 <= base.get_id() and base.get_id() < 건물_항구끝 and no_enemy_around(base) and 2000 <= pk::get_troops(base)  )
				return true;


	// 금 3만 이상 있고, 적 침공에서 안전한 병력 4천 이상 도시에서 보급 보내라
if ( 30000 <= pk::get_gold(base) and pk::get_troops(base) * 0.6f <= pk::get_gold(base) and 건물_도시시작 <= base.get_id() and base.get_id() < 건물_도시끝 and no_enemy_around(base) and 4000 <= pk::get_troops(base) )
				return true;


            
			return false;
		}







		/** 금 20% 보급 명령 (나머지 5%)  */

		bool PushEXgold(pk::building@ base)
		{
            int reinforce_troops = pk::min(1000,  int (pk::get_troops(base) * 0.15f) );
			// 명령 가능한 무장이 있는지 확인.
			auto person_list = pk::get_idle_person_list(base);
			if (person_list.count == 0) return false;

			// 인접 거접이 있는지 확인.
			int target = getEXGBase(base);
			if (target == -1) return false;

			if (!no_enemy_around(pk::get_building(target))) return false;
			if (enemy_approach(pk::get_building(target))) return false;
			if (close_combat(pk::get_building(target))) return false;

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

            int unit_food = int(pk::min( 0.3f * pk::get_food(base), 2.0f * reinforce_troops));
            if (unit_food < int(1.0f * reinforce_troops)) return false;   // 병량 부족            

            float supply_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            float weapon_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            
			// 출진 명령 정보 생성.
			pk::com_deploy_cmd_info cmd;
			@cmd.base = @base;
			cmd.type = 부대종류_수송;
			cmd.member[0] = leader.get_id();
                if (건물_관문시작 <= base.get_id() and base.get_id() < 건물_항구끝)
			cmd.gold = pk::min(int(pk::get_gold(base) * 0.20f ), 10000);

                if (건물_도시시작 <= base.get_id() and base.get_id() < 건물_도시끝)			
			cmd.gold = pk::min(int(pk::get_gold(base) * 0.20f), 10000);
			cmd.food = pk::min(pk::max (1000 , unit_food), 25000);
			cmd.troops = reinforce_troops;
			int i = 0;
			for (int weapon_id = 0; weapon_id < 병기_끝; weapon_id++)
			{
                int weapon_amount = 0;
                if (weapon_id < 병기_충차)
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id) * 0.05f), 4000);
                else
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id)), 1);
                
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
            pk::say(pk::u8encode("이곳은 금이 충분하다! \n다른 곳으로 나르자!"), leader);
            
            // 임시 도주 효과 ('19.3.6)
            if (거점수송_일시도주설정)
            {
                leader.skill = retreat_skill;         // 특기 복원
            }
            
            
			return true;
		}





        
		/** 가장 가까운아군 도시에 보급을 보냄 */

        pk::building@ src_EXG;
		int getEXGBase(pk::building@ src)
		{
			int best_dst = -1;
			int best_distance = 0;
            int src_id = src.get_id();
            pk::list<pk::building@> dst_list; 
            @src_EXG = @src;



            
            int search_base = 건물_도시끝;
            if      (거점수송_거점검색모드 == 0) search_base = 건물_도시끝;
            else if (거점수송_거점검색모드 == 1) search_base = 건물_거점끝;
            
            pk::force@ force = pk::get_force(src.get_force_id());
            
			// 거점 검색

                for (int i = 0; i < search_base; i++)
                {
                    pk::building@ dst = pk::get_building(i);
                    int dst_id = dst.get_id();

			int base2_troops = pk::get_troops(dst);


                    // 도시거리
                    int city_dist = -1;
                    if (dst_id < 건물_도시끝 and src_id < 건물_도시끝)
                        city_dist = pk::get_city_distance(dst_id, src_id);
                    
                    // 거점거리
                    int base_dist = pk::get_building_distance(dst_id, src_id, src.get_force_id());
                    
                    // 거리 조건 만족 시 (거리 1~3)
                if ( (base_dist == 1 and !intercept1_Enemy_base(src, dst) and !intercept_delta_Enemy_base(src, dst)) or ((base_dist == 2 or (city_dist == 1 and base_dist <= 3)) and !intercept2_Enemy_base(src, dst) and !intercept_delta_Enemy_base(src, dst)) )   
                    {



                        int enemy_weight = countNeighborEnemyBase(dst);

	// 항관에서 보낼 땐 금 한계보유량까지 4만 이상 여유 OR  도시에서 보낼 땐 공급지 보다 금 2만 이상 적은, 적 침공에서 안전한 도시로 보급 보내라
                    
if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst) and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and ( ( 건물_관문시작 <= src_id and src_id < 건물_항구끝 and 40000 <= pk::get_max_gold(dst) - pk::get_gold(dst) ) or ( 건물_도시시작 <= src_id and src_id < 건물_도시끝 and pk::get_gold(dst) + 20000 <= pk::get_gold(src) ) ) and no_enemy_around(dst) and enemy_weight  == 0 and func_already (dst) <= 3)
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
                    }



           // 금 3천 이하 OR 공급지 보다 금 1만 2천 이상 적은,  공급지보다 금 보유 한도 1만 더 여유 있는 적 침공에서 안전한 관문, 항구로 보급 보내라

else if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst)  and 건물_관문시작 <= dst_id and dst_id < 건물_항구끝 and ( pk::get_gold(dst) <= 3000 or pk::get_gold(dst) + 22000 <= pk::get_gold(src) ) and pk::get_max_gold(src) - pk::get_gold(src) + 10000 <= pk::get_max_gold(dst) - pk::get_gold(dst) and no_enemy_around(dst) and enemy_weight  == 0 and func_already (dst) <= 3 and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id)
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
                    }



	// 항관에서 보낼 땐 금 한계보유량까지 4만 이상 여유  OR  도시에서 보낼 땐 공급지 보다 금 2만 이상 적은,  접경 도시로 보급 보내라
                    
else if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst)   and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and ( ( 건물_관문시작 <= src_id and src_id < 건물_항구끝 and 40000 <= pk::get_max_gold(dst) - pk::get_gold(dst)) or ( 건물_도시시작 <= src_id and src_id < 건물_도시끝 and pk::get_gold(dst) + 20000 <= pk::get_gold(src) ) ) and no_enemy_around(dst) and func_already (dst) <= 3)
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
                    }



           // 금 3천 이하 OR 공급지 보다 금 1만 2천 이상 적은, 공급지보다 금 보유 한도 1만 더 여유 있는 접경  관문, 항구로 보급 보내라

else if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst)  and 건물_관문시작 <= dst_id and dst_id < 건물_항구끝 and ( pk::get_gold(dst) <= 3000 or pk::get_gold(dst) + 22000 <= pk::get_gold(src) ) and pk::get_max_gold(src) - pk::get_gold(src) + 10000 <= pk::get_max_gold(dst) - pk::get_gold(dst) and no_enemy_around(dst) and func_already (dst) <= 3 and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id)
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
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
                    return (pk::get_max_gold(a) - pk::get_gold(a) > pk::get_max_gold(b) - pk::get_gold(b));					
					
                    int build_dist_a = pk::get_building_distance(a.get_id(), main.src_EXG.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.src_EXG.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.src_EXG.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.src_EXG.pos);

                    if (build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);
                    
                    return (pos_dist_a < pos_dist_b);
                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
		}













        //----------------------------------------------------------------------------------
        //  물자 포화 상태일때 다른 곳으로 배분  (군량)
        //----------------------------------------------------------------------------------




		/** 병력 있는 거점 찾기 */

		bool needEXfood(pk::building@ base)
		{
			if (!no_enemy_around(base)) return false;

			int base_troops = pk::get_troops(base);


                        int enemy_weight = countNeighborEnemyBase(base);
            pk::city@ city_a = pk::get_city(pk::get_city_id(base.pos));




	//  병량 6만 이상에 병력 대비 6배 이상 있거나 병량 최대 보유까지 20만 이하 여유 밖에 안남은, 적 침공에서 안전한 병력 2천 이상 관문, 항구에서 보급 보내라

if ( ((60000 <= pk::get_food(base) and pk::get_food(base) >= pk::get_troops(base) * 6.f) or pk::get_max_food(base) - pk::get_food(base) <= 200000 ) and 건물_관문시작 <= base.get_id() and base.get_id() < 건물_항구끝 and no_enemy_around(base) and 2000 <= pk::get_troops(base) )
				return true;



       // 병량 30만 이상에 병력 대비 7배 이상 있거나 병량 최대 보유까지 20만 이하 여유 밖에 안남은, 적 침공에서 안전한 병력 4천 이상 도시에서 보급 보내라
if ( ((300000 <= pk::get_food(base) and pk::get_food(base) >= pk::get_troops(base) * 7.f ) or pk::get_max_food(base) - pk::get_food(base) <= 200000 ) and 건물_도시시작 <= base.get_id() and base.get_id() < 건물_도시끝 and no_enemy_around(base) and 4000 <= pk::get_troops(base) )
				return true;


            
			return false;
		}







		/** 군량 20% 보급 명령 (나머지 5%)  */

		bool PushEXfood(pk::building@ base)
		{
            int reinforce_troops = pk::min(1000,  int (pk::get_troops(base) * 0.15f) );
			// 명령 가능한 무장이 있는지 확인.
			auto person_list = pk::get_idle_person_list(base);
			if (person_list.count == 0) return false;

			//  인접 거접이 있는지 확인.
			int target = getEXFBase(base);
			if (target == -1) return false;

			if (!no_enemy_around(pk::get_building(target))) return false;
			if (enemy_approach(pk::get_building(target))) return false;
			if (close_combat(pk::get_building(target))) return false;

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
         

            int unit_food = int(pk::min( 0.3f * pk::get_food(base), 5.0f * reinforce_troops));
                if (건물_관문시작 <= base.get_id() and base.get_id() < 건물_항구끝 and 건물_도시시작 <= target and target < 건물_도시끝)	
                   unit_food = pk::get_food(base) - (pk::get_troops(base) * 2.5f);					
            if (unit_food < int(1.0f * reinforce_troops)) return false;   // 병량 부족     

            float supply_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            float weapon_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            
			// 출진 명령 정보 생성.
			pk::com_deploy_cmd_info cmd;
			@cmd.base = @base;
			cmd.type = 부대종류_수송;
			cmd.member[0] = leader.get_id();
			cmd.gold = pk::min(int(pk::get_gold(base) * 0.05f), 10000);
                if (건물_관문시작 <= base.get_id() and base.get_id() < 건물_항구끝)
			cmd.food = pk::min(pk::max (int(pk::get_food(base) * 0.20f) , unit_food), 60000);

                if (건물_도시시작 <= base.get_id() and base.get_id() < 건물_도시끝)			
			cmd.food = pk::min(pk::max (int(pk::get_food(base) * 0.20f) , unit_food), 60000);
			cmd.troops = reinforce_troops;
			int i = 0;
			for (int weapon_id = 0; weapon_id < 병기_끝; weapon_id++)
			{
                int weapon_amount = 0;
                if (weapon_id < 병기_충차)
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id) * 0.05f), 4000);
                else
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id)), 1);
                
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
            pk::say(pk::u8encode("이곳은 군량이 충분하다! \n다른 거점으로 보내자!"), leader);
            
            // 임시 도주 효과 ('19.3.6)
            if (거점수송_일시도주설정)
            {
                leader.skill = retreat_skill;         // 특기 복원
            }
            
            
			return true;
		}





        
		/** 가장 가깝고 위기에 빠진 아군 도시에 보급을 보냄 */

        pk::building@ src_EXF;
		int getEXFBase(pk::building@ src)
		{
			int best_dst = -1;
			int best_distance = 0;
            int src_id = src.get_id();
            pk::list<pk::building@> dst_list; 
            @src_EXF = @src;



            
            int search_base = 건물_도시끝;
            if      (거점수송_거점검색모드 == 0) search_base = 건물_도시끝;
            else if (거점수송_거점검색모드 == 1) search_base = 건물_거점끝;
            
            pk::force@ force = pk::get_force(src.get_force_id());
            
			// 거점 검색

                for (int i = 0; i < search_base; i++)
                {
                    pk::building@ dst = pk::get_building(i);
                    int dst_id = dst.get_id();
			int base2_troops = pk::get_troops(dst);


                    // 도시거리
                    int city_dist = -1;
                    if (dst_id < 건물_도시끝 and src_id < 건물_도시끝)
                        city_dist = pk::get_city_distance(dst_id, src_id);
                    
                    // 거점거리
                    int base_dist = pk::get_building_distance(dst_id, src_id, src.get_force_id());
                    
                    // 거리 조건 만족 시 (거리 1~3)
                if ( (base_dist == 1 and !intercept1_Enemy_base(src, dst) and !intercept_delta_Enemy_base(src, dst)) or ((base_dist == 2 or (city_dist == 1 and base_dist <= 3)) and !intercept2_Enemy_base(src, dst) and !intercept_delta_Enemy_base(src, dst)) )    
                    {

                if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst)) 
                      {
                       // 목적지가 메뚜기 재해지역이면서 병력 대비 병량이 0.35배 초과면 안감. (0.35배 이하면 병력들 굶어죽을까봐 병량 수송함)
	          pk::city@ city_c = pk::get_city(pk::get_city_id(dst.pos));
                        if (city_c.inago and pk::get_troops(dst) * 0.35f < pk::get_food(dst))  continue;

                        int enemy_weight = countNeighborEnemyBase(dst);

	// 병량 최대 보유 한도와 현재 소유 병량 차이가 보내는 곳보다 20만 이상 더 많이 남았거나 병량이 병력 대비 3배 이하인, 적 침공에서 안전한 도시로 보급 보내라
                    
        if (건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and (pk::get_max_food(dst) - pk::get_food(dst) >= 200000 + pk::get_max_food(src) - pk::get_food(src) or pk::get_troops(dst) * 3.f >= pk::get_food(dst)) and no_enemy_around(dst) and enemy_weight  == 0 and func_already (dst) <= 3)
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
                    }



           //군량이 1만5천 이하나 병력 대비 3배 이하이거나 병량 최대 보유까지 30만 이상 남은, 적 침공에서 안전한 관문, 항구로 보급 보내라

      else if (건물_관문시작 <= dst_id and dst_id < 건물_항구끝 and (( pk::get_max_food(src) - pk::get_food(src) <= 200000 and pk::get_max_food(dst) - pk::get_food(dst) >= 300000 ) or  pk::get_troops(dst) * 3.f >= pk::get_food(dst) ) and no_enemy_around(dst) and enemy_weight  == 0 and func_already (dst) <= 3 and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id)
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
                    }


	// 병량 최대 보유 한도와 현재 소유 병량 차이가 보내는 곳보다 20만 이상 더 많이 남았거나 병량이 병력 대비 3배 이하인, 접경 도시로 보급 보내라
                    
        if (건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and (pk::get_max_food(dst) - pk::get_food(dst) >= 200000 + pk::get_max_food(src) - pk::get_food(src) or pk::get_troops(dst) * 3.f >= pk::get_food(dst)) and no_enemy_around(dst) and func_already (dst) <= 3)
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
                    }



           //군량이 1만5천 이하나 병력 대비 3배 이하이거나 병량 최대 보유까지 30만 이상 남은, 접경 관문, 항구로 보급 보내라

        else if (건물_관문시작 <= dst_id and dst_id < 건물_항구끝 and  ((pk::get_max_food(src) - pk::get_food(src) <= 200000 and pk::get_max_food(dst) - pk::get_food(dst) >= 300000 ) or  pk::get_troops(dst) * 3.f >= pk::get_food(dst) ) and no_enemy_around(dst) and func_already (dst) <= 3 and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id)
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
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
                    return (float(pk::get_food(a) + 10) / float(pk::get_troops(a) + 10) < float(pk::get_food(b) + 10) / float(pk::get_troops(b) + 10));		
					
                    int build_dist_a = pk::get_building_distance(a.get_id(), main.src_EXF.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.src_EXF.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.src_EXF.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.src_EXF.pos);

                    if (build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);
                    
                    return (pos_dist_a < pos_dist_b);
                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
		}










        //----------------------------------------------------------------------------------
        //  평시 보급대 보내기  (금)
        //----------------------------------------------------------------------------------




		/** 병력 있는 거점 찾기 */

		bool needPeacetimegold(pk::building@ base)
		{

			if (!no_enemy_around(base)) return false;

			int base_troops = pk::get_troops(base);


                        int enemy_weight = countNeighborEnemyBase(base);
            pk::city@ city_a = pk::get_city(pk::get_city_id(base.pos));

	//  금 5천 이상 있고 , 적 침공에서 안전한 병력 2천 이상 관문, 항구에서 보급 보내라

if ( 5000 <= pk::get_gold(base) and pk::get_troops(base) * 0.4f <= pk::get_gold(base) and 건물_관문시작 <= base.get_id() and base.get_id() < 건물_항구끝 and no_enemy_around(base) and 2000 <= pk::get_troops(base)  )
				return true;



	// 금 1만 5천 이상 있고, 적 침공에서 안전한 병력 4천 이상 도시에서 보급 보내라
if ( 15000 <= pk::get_gold(base) and pk::get_troops(base) * 0.4f <= pk::get_gold(base) and 건물_도시시작 <= base.get_id() and base.get_id() < 건물_도시끝 and no_enemy_around(base) and pk::get_max_troops(base) * 0.5  <= pk::get_troops(base) and 91 <= city_a.public_order )
				return true;

            
			return false;
		}







		/** 금 20% 보급 명령 (나머지 5%)  */

		bool PushPeacetimegold(pk::building@ base)
		{
            int reinforce_troops = pk::min(1000,  int (pk::get_troops(base) * 0.15f) );
			// 명령 가능한 무장이 있는지 확인.
			auto person_list = pk::get_idle_person_list(base);
			if (person_list.count == 0) return false;

			// 인접 거접이 있는지 확인.
			int target = getBackupGBase(base);
			if (target == -1) return false;

			if (!no_enemy_around(pk::get_building(target))) return false;
			if (enemy_approach(pk::get_building(target))) return false;
			if (close_combat(pk::get_building(target))) return false;

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

            int unit_food = int(pk::min( 0.3f * pk::get_food(base), 2.0f * reinforce_troops));
            if (unit_food < int(1.0f * reinforce_troops)) return false;   // 병량 부족            

            float supply_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            float weapon_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            
			// 출진 명령 정보 생성.
			pk::com_deploy_cmd_info cmd;
			@cmd.base = @base;
			cmd.type = 부대종류_수송;
			cmd.member[0] = leader.get_id();
			cmd.gold = pk::min(int(pk::get_gold(base) * 0.20f), 10000);
			cmd.food = pk::min(pk::max (1000 , unit_food), 25000);
			cmd.troops = reinforce_troops;
			int i = 0;
			for (int weapon_id = 0; weapon_id < 병기_끝; weapon_id++)
			{
                int weapon_amount = 0;
                if (weapon_id < 병기_충차)
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id) * 0.05f), 4000);
                else
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id)), 1);
                
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
            pk::say(pk::u8encode("아군의 거점에 금이 부족! \n어서 금을 나르자!"), leader);
            
            // 임시 도주 효과 ('19.3.6)
            if (거점수송_일시도주설정)
            {
                leader.skill = retreat_skill;         // 특기 복원
            }
            
            
			return true;
		}





        
		/** 가장 가깝고 위기에 빠진 아군 도시에 보급을 보냄 */

        pk::building@ src_y;
		int getBackupGBase(pk::building@ src)
		{
			int best_dst = -1;
			int best_distance = 0;
            int src_id = src.get_id();
            pk::list<pk::building@> dst_list; 
            @src_y = @src;



            
            int search_base = 건물_도시끝;
            if      (거점수송_거점검색모드 == 0) search_base = 건물_도시끝;
            else if (거점수송_거점검색모드 == 1) search_base = 건물_거점끝;
            
            pk::force@ force = pk::get_force(src.get_force_id());
            
			// 거점 검색

                for (int i = 0; i < search_base; i++)
                {
                    pk::building@ dst = pk::get_building(i);
                    int dst_id = dst.get_id();

			int base2_troops = pk::get_troops(dst);

                
                    // 도시거리
                    int city_dist = -1;
                    if (dst_id < 건물_도시끝 and src_id < 건물_도시끝)
                        city_dist = pk::get_city_distance(dst_id, src_id);
                    
                    // 거점거리
                    int base_dist = pk::get_building_distance(dst_id, src_id, src.get_force_id());
                    
                    // 거리 조건 만족 시  (거리 1~3)
                if ( (base_dist == 1 and !intercept1_Enemy_base(src, dst) and !intercept_delta_Enemy_base(src, dst)) or ((base_dist == 2 or (city_dist == 1 and base_dist <= 3)) and !intercept2_Enemy_base(src, dst) and !intercept_delta_Enemy_base(src, dst)) )   
                    {



                        int enemy_weight = countNeighborEnemyBase(dst);

	// 공급지가 항관이면 금 8천 이하고, 공급지가 도시면 금이 공급지보다 절반 이하로, 적 침공에서 안전한 도시로 보급 보내라
                    
if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst) and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and ( ( 건물_관문시작 <= src_id and src_id < 건물_항구끝 and pk::get_gold(dst) <= 8000 ) or ( 건물_도시시작 <= src_id and src_id < 건물_도시끝 and pk::get_gold(dst) <= pk::get_gold(src) * 0.5f ) ) and no_enemy_around(dst) and enemy_weight  == 0 and func_already (dst) <= 1 and func_supplycheck(src,dst) == 0)
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
                    }



           //금 3천 이하로, 적 침공에서 안전한 관문, 항구로 보급 보내라

else if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst)  and 건물_관문시작 <= dst_id and dst_id < 건물_항구끝 and  pk::get_gold(dst) <= 3000 and no_enemy_around(dst) and enemy_weight  == 0 and func_already (dst) <= 1 and func_supplycheck(src,dst) == 0 and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id)
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
                    }



           // 공급지가 항관이면 금 1만1천 이하고, 공급지가 도시면 금이 공급지보다 70% 이하로 , 접경지대의 도시로 보급 보내라

else if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst) and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and ( ( 건물_관문시작 <= src_id and src_id < 건물_항구끝 and pk::get_gold(dst) <= 11000 ) or ( 건물_도시시작 <= src_id and src_id < 건물_도시끝 and pk::get_gold(dst) <= pk::get_gold(src) * 0.7f ) ) and no_enemy_around(dst) and  1 <= enemy_weight and func_already (dst) <= 1 and func_supplycheck(src,dst) == 0 )
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
                    }



           // 금 4천 이하로 , 접경지대의 관문, 항구로 보급 보내라

else if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst)  and 건물_관문시작 <= dst_id and dst_id < 건물_항구끝 and  pk::get_gold(dst) <= 4000 and no_enemy_around(dst) and 1 <= enemy_weight and func_already (dst) <= 1 and func_supplycheck(src,dst) == 0 and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id)
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
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
                    return (pk::get_max_gold(a) - pk::get_gold(a) > pk::get_max_gold(b) - pk::get_gold(b));						
					
                    int build_dist_a = pk::get_building_distance(a.get_id(), main.src_y.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.src_y.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.src_y.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.src_y.pos);

                    if (build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);
                    
                    return (pos_dist_a < pos_dist_b);
                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
		}









        //----------------------------------------------------------------------------------
        //  평시 보급대 보내기  (군량)
        //----------------------------------------------------------------------------------




		/** 병력 있는 거점 찾기 */

		bool needPeacetimefood(pk::building@ base)
		{

			if (!no_enemy_around(base)) return false;

			int base_troops = pk::get_troops(base);


                        int enemy_weight = countNeighborEnemyBase(base);
            pk::city@ city_a = pk::get_city(pk::get_city_id(base.pos));


	//  병량 1만 이상에 병력 대비 3.5배 이상 있고, 적 침공에서 안전한 병력 2천 이상 관문, 항구에서 보급 보내라

if ( 10000 <= pk::get_food(base) and pk::get_food(base) >= pk::get_troops(base) * 3.5f and 건물_관문시작 <= base.get_id() and base.get_id() < 건물_항구끝 and no_enemy_around(base) and 2000 <= pk::get_troops(base) )
				return true;


	// 병량 7만 이상에 병력 대비 3.5배 이상 있고, 적 침공에서 안전한 병력 4천 이상 도시에서 보급 보내라
if ( 70000 <= pk::get_food(base) and pk::get_food(base) >= pk::get_troops(base) * 3.5f and 건물_도시시작 <= base.get_id() and base.get_id() < 건물_도시끝 and no_enemy_around(base) and pk::get_max_troops(base) * 0.5 <= pk::get_troops(base) and 91 <= city_a.public_order )
				return true;

            
			return false;
		}







		/** 군량 20% 보급 명령 (나머지 5%)  */

		bool PushPeacetimefood(pk::building@ base)
		{
            int reinforce_troops = pk::min(1000,  int (pk::get_troops(base) * 0.15f) );
			// 명령 가능한 무장이 있는지 확인.
			auto person_list = pk::get_idle_person_list(base);
			if (person_list.count == 0) return false;

			//  인접 거접이 있는지 확인.
			int target = getBackupFBase(base);
			if (target == -1) return false;

			if (!no_enemy_around(pk::get_building(target))) return false;
			if (enemy_approach(pk::get_building(target))) return false;
			if (close_combat(pk::get_building(target))) return false;

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
         

            int unit_food = int(pk::min( 0.3f * pk::get_food(base), 5.0f * reinforce_troops));
                if (건물_관문시작 <= base.get_id() and base.get_id() < 건물_항구끝 and 건물_도시시작 <= target and target < 건물_도시끝)	
                   unit_food = pk::get_food(base) - (pk::get_troops(base) * 2.5f);				
            if (unit_food < int(1.0f * reinforce_troops)) return false;   // 병량 부족     

            float supply_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            float weapon_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            
			// 출진 명령 정보 생성.
			pk::com_deploy_cmd_info cmd;
			@cmd.base = @base;
			cmd.type = 부대종류_수송;
			cmd.member[0] = leader.get_id();
			cmd.gold = pk::min(int(pk::get_gold(base) * 0.05f), 10000);
			cmd.food = pk::min(pk::max (int(pk::get_food(base) * 0.20f) , unit_food), 60000);
			cmd.troops = reinforce_troops;
			int i = 0;
			for (int weapon_id = 0; weapon_id < 병기_끝; weapon_id++)
			{
                int weapon_amount = 0;
                if (weapon_id < 병기_충차)
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id) * 0.05f), 4000);
                else
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id)), 1);
                
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
            pk::say(pk::u8encode("아군의 거점에 군량이 부족! \n군량 수송 실시!"), leader);
            
            // 임시 도주 효과 ('19.3.6)
            if (거점수송_일시도주설정)
            {
                leader.skill = retreat_skill;         // 특기 복원
            }
            
            
			return true;
		}





        
		/** 가장 가깝고 위기에 빠진 아군 도시에 보급을 보냄 */

        pk::building@ src_z;
		int getBackupFBase(pk::building@ src)
		{
			int best_dst = -1;
			int best_distance = 0;
            int src_id = src.get_id();
            pk::list<pk::building@> dst_list; 
            @src_z = @src;



            
            int search_base = 건물_도시끝;
            if      (거점수송_거점검색모드 == 0) search_base = 건물_도시끝;
            else if (거점수송_거점검색모드 == 1) search_base = 건물_거점끝;
            
            pk::force@ force = pk::get_force(src.get_force_id());
            
			// 거점 검색

                for (int i = 0; i < search_base; i++)
                {
                    pk::building@ dst = pk::get_building(i);
                    int dst_id = dst.get_id();
			int base2_troops = pk::get_troops(dst);


                    // 도시거리
                    int city_dist = -1;
                    if (dst_id < 건물_도시끝 and src_id < 건물_도시끝)
                        city_dist = pk::get_city_distance(dst_id, src_id);
                    
                    // 거점거리
                    int base_dist = pk::get_building_distance(dst_id, src_id, src.get_force_id());
                    
                    // 거리 조건 만족 시  (거리 1~3)
                if ( (base_dist == 1 and !intercept1_Enemy_base(src, dst) and !intercept_delta_Enemy_base(src, dst)) or ((base_dist == 2 or (city_dist == 1 and base_dist <= 3)) and !intercept2_Enemy_base(src, dst) and !intercept_delta_Enemy_base(src, dst)) )   
                    {
                       // 목적지가 메뚜기 재해지역이면서 병력 대비 병량이 0.35배 초과면 안감. (0.35배 이하면 병력들 굶어죽을까봐 병량 수송함)
	          pk::city@ city_c = pk::get_city(pk::get_city_id(dst.pos));
                        if (city_c.inago and pk::get_troops(dst) * 0.35f < pk::get_food(dst))  continue;

                        int enemy_weight = countNeighborEnemyBase(dst);

	// 군량이 3만 이하나 병력 대비 2.5배 이하인, 적 침공에서 안전한 도시로 보급 보내라
                    
        if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst)  and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and  ( pk::get_food(dst) <= 30000 or  pk::get_troops(dst) * 2.5f >= pk::get_food(dst) or pk::get_food(dst) *3 < pk::get_food(src) )  and no_enemy_around(dst) and enemy_weight  == 0 and func_already (dst) <= 1 and func_supplycheck(src,dst) == 0)
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
                    }



           //군량이 5천 이하나 병력 대비 2.5배 이하인, 적 침공에서 안전한 관문, 항구로 보급 보내라

       else if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst)   and 건물_관문시작 <= dst_id and dst_id < 건물_항구끝 and  ( pk::get_food(dst) <= 5000 or  pk::get_troops(dst) * 2.5f >= pk::get_food(dst) ) and no_enemy_around(dst) and enemy_weight  == 0 and func_already (dst) <= 1 and func_supplycheck(src,dst) == 0 and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id)
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
                    }



           // 군량이 3만 이하나 병력 대비 3배 이하인 , 접경지대의 도시로 보급 보내라

       else if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst) and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and  ( pk::get_food(dst) <=  30000 or  pk::get_troops(dst) * 3.f >= pk::get_food(dst) or pk::get_food(dst) *3 < pk::get_food(src)) and no_enemy_around(dst) and  1 <= enemy_weight and func_already (dst) <= 1 and func_supplycheck(src,dst) == 0)
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
                    }



           // 군량이 1만 이하나 병력 대비 3배 이하인 , 접경지대의 관문, 항구로 보급 보내라

       else if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst)  and 건물_관문시작 <= dst_id and dst_id < 건물_항구끝 and  ( pk::get_food(dst) <=  10000 or  pk::get_troops(dst) * 3.f >= pk::get_food(dst) ) and no_enemy_around(dst) and  1 <= enemy_weight  and func_already (dst) <= 1 and func_supplycheck(src,dst) == 0 and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id)
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
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
                    return (float(pk::get_food(a) + 10) / float(pk::get_troops(a) + 10) < float(pk::get_food(b) + 10) / float(pk::get_troops(b) + 10));							
					
                    int build_dist_a = pk::get_building_distance(a.get_id(), main.src_z.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.src_z.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.src_z.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.src_z.pos);

                    if (build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);
                    
                    return (pos_dist_a < pos_dist_b);
                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
		}













        //----------------------------------------------------------------------------------
        //   (금) 바닥났을 때 긴급 수송 
        //----------------------------------------------------------------------------------




		/** 병력 있는 거점 찾기 */

		bool needERgold(pk::building@ base)
		{
			// 근접한 적 부대 수
			int enemy_units1 = 0;
			int enemy_troops1 = 0;

			// 3칸 이내 적 부대 수
			int enemy_units3 = 0;
			// 3칸 이내 적 병력 수
			int enemy_troops3 = 0;

			// 4칸 이내 적 부대 수
			int enemy_units4 = 0;
			// 4칸 이내 적 병력 수
			int enemy_troops4 = 0;
			

			int force_units7 = 0;



			auto range = pk::range(base.get_pos(), 1, 22);
			for (int i = 0; i < int(range.length); i++)
			{
				auto unit = pk::get_unit(range[i]);
				if (pk::is_alive(unit))
				{
					int distance = pk::get_distance(base.get_pos(), range[i]);
					if (pk::is_enemy(base, unit))
					{
						if (distance <= 1)
						{
							enemy_units1++;
							enemy_troops1 += unit.troops;
						}
						if (distance <= 10)
						{
							enemy_units3++;
							enemy_troops3 += unit.troops;
						}
						
						if (distance <= 22)
						{
							enemy_units4++;
							enemy_troops4 += unit.troops;
						}							
					}


					else if (base.get_force_id() == unit.get_force_id() and unit.type == 부대종류_전투)
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

			if (enemy_units1 >= 10)  // 거점 포위 상태로 수송 불가
				return false;
			int base_troops = pk::get_troops(base);
            pk::force@ force = pk::get_force(base.get_force_id()); 

                        int enemy_weight = countNeighborEnemyBase(base);
            pk::city@ city_a = pk::get_city(pk::get_city_id(base.pos));

	//  금 3000 이상 있고 , 적 침공에서 안전한 병력 2천 이상 관문, 항구에서 보급 보내라

	if ( 3000 <= pk::get_gold(base) and 건물_관문시작 <= base.get_id() and base.get_id() < 건물_항구끝 and enemy_troops3  == 0 and  enemy_units3  == 0 and (func_enemy_city_count(city_a, 1)  == 0 or enemy_units4  == 0) and 2000 <= pk::get_troops(base) )
				return true;


	// 금 3000 이상 있고, 적 침공에서 안전한 병력 4천 이상 도시에서 보급 보내라

	if ( 3000 <= pk::get_gold(base) and 건물_도시시작 <= base.get_id() and base.get_id() < 건물_도시끝 and enemy_troops3  == 0 and  enemy_units3  == 0 and (func_enemy_city_count(city_a, 1)  == 0 or enemy_units4  == 0) and 4000 <= pk::get_troops(base) )
				return true;

            
	// 도시가 1개 남았을때는 금 3000 이상 있고, 적이 근처에 없는 거점들에서
			if ( 3000 <= pk::get_gold(base)  and base.get_id() < 건물_거점끝 and enemy_troops3  == 0 and  enemy_units3  == 0 and pk::get_city_list(force).count <= 1  )
				return true;	
			
			return false;
		}







		/** 금 20% 보급 명령 (나머지 5%)  */

		bool PushERgold(pk::building@ base)
		{
            int reinforce_troops = pk::min(1000,  int (pk::get_troops(base) * 0.15f) );
			// 명령 가능한 무장이 있는지 확인.
			auto person_list = pk::get_idle_person_list(base);
			if (person_list.count == 0) return false;

			// 인접 거접이 있는지 확인.
			int target = getBackupEGBase(base);
			if (target == -1) return false;

			if (!no_enemy_around(pk::get_building(target))) return false;
			if (enemy_approach(pk::get_building(target))) return false;
			if (close_combat(pk::get_building(target))) return false;

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
            int unit_food = int(pk::min( 0.3f * pk::get_food(base), 2.0f * reinforce_troops));
            if (unit_food < int(1.0f * reinforce_troops)) return false;   // 병량 부족            

            float supply_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            float weapon_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            
			// 출진 명령 정보 생성.
			pk::com_deploy_cmd_info cmd;
			@cmd.base = @base;
			cmd.type = 부대종류_수송;
			cmd.member[0] = leader.get_id();
			cmd.gold = pk::min(int(pk::get_gold(base) * 0.20f), 3000);
			cmd.food = pk::min(pk::max (1000 , unit_food), 25000);
			cmd.troops = reinforce_troops;
			int i = 0;
			for (int weapon_id = 0; weapon_id < 병기_끝; weapon_id++)
			{
                int weapon_amount = 0;
                if (weapon_id < 병기_충차)
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id) * 0.05f), 4000);
                else
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id)), 1);
                
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
            pk::say(pk::u8encode("금이 바닥나겠군...! \n빨리 금을 보내자."), leader);
            
            // 임시 도주 효과 ('19.3.6)
            if (거점수송_일시도주설정)
            {
                leader.skill = retreat_skill;         // 특기 복원
            }
            
            
			return true;
		}





        
		/** 가장 가깝고 위기에 빠진 아군 도시에 보급을 보냄 */

        pk::building@ src_eg;
		int getBackupEGBase(pk::building@ src)
		{
			int best_dst = -1;
			int best_distance = 0;
            int src_id = src.get_id();
            pk::list<pk::building@> dst_list; 
            @src_eg = @src;



            
            int search_base = 건물_도시끝;
            if      (거점수송_거점검색모드 == 0) search_base = 건물_도시끝;
            else if (거점수송_거점검색모드 == 1) search_base = 건물_거점끝;
            
            pk::force@ force = pk::get_force(src.get_force_id());
            
			// 거점 검색

                for (int i = 0; i < search_base; i++)
                {
                    pk::building@ dst = pk::get_building(i);
                    int dst_id = dst.get_id();

			int base2_troops = pk::get_troops(dst);

                
                    // 도시거리
                    int city_dist = -1;
                    if (dst_id < 건물_도시끝 and src_id < 건물_도시끝)
                        city_dist = pk::get_city_distance(dst_id, src_id);
                    
                    // 거점거리
                    int base_dist = pk::get_building_distance(dst_id, src_id, src.get_force_id());
                    
                    // 거리 조건 만족 시  (거리 1~3)
                if ( (base_dist == 1 and !intercept1_Enemy_base(src, dst) and !intercept_delta_Enemy_base(src, dst)) or ((base_dist == 2 or (city_dist == 1 and base_dist <= 3)) and !intercept2_Enemy_base(src, dst) and !intercept_delta_Enemy_base(src, dst)) )   
                    {



                        int enemy_weight = countNeighborEnemyBase(dst);


	// 공급지가 항관이고 금이 항관보다 적은 적 침공에서 안전한 도시로 보급 보내라

if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst) and 건물_관문시작 <= src_id and src_id < 건물_항구끝 and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and  pk::get_gold(dst) <= pk::get_gold(src) and no_enemy_around(dst) and enemy_weight  == 0 and func_already (dst) <= 1 and func_supplycheck(src,dst) == 0)
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
                    }


	// 금 1천 이하로, 적 침공에서 안전한 도시로 보급 보내라
                    
if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst) and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and  pk::get_gold(dst) <= 1000  and no_enemy_around(dst) and enemy_weight  == 0 and func_already (dst) <= 1 and func_supplycheck(src,dst) == 0)
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
                    }



           //금 1천 이하로, 적 침공에서 안전한 관문, 항구로 보급 보내라

else if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst) and 건물_관문시작 <= dst_id and dst_id < 건물_항구끝 and  pk::get_gold(dst) <= 1000 and no_enemy_around(dst) and enemy_weight  == 0 and func_already (dst) <= 1 and func_supplycheck(src,dst) == 0 and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id)
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
                    }






           // 공급지가 항관이고 금이 항관보다 적은 접경 지대의 도시로 보급 보내라

else if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst) and 건물_관문시작 <= src_id and src_id < 건물_항구끝 and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and  pk::get_gold(dst) <= pk::get_gold(src) and no_enemy_around(dst) and  1 <= enemy_weight and func_already (dst) <= 1 and func_supplycheck(src,dst) == 0 )
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
                    }
			
			
           // 금 2천 이하로, 접경지대의 도시로 보급 보내라

else if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst) and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and  pk::get_gold(dst) <= 2000 and no_enemy_around(dst) and  1 <= enemy_weight and func_already (dst) <= 1 and func_supplycheck(src,dst) == 0 )
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
                    }



           // 금 2천 이하로, 접경지대의 관문, 항구로 보급 보내라

else if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst) and 건물_관문시작 <= dst_id and dst_id < 건물_항구끝 and  pk::get_gold(dst) <= 2000 and no_enemy_around(dst) and  1 <= enemy_weight and func_already (dst) <= 1 and func_supplycheck(src,dst) == 0 and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id)
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
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
					
                    int build_dist_a = pk::get_building_distance(a.get_id(), main.src_eg.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.src_eg.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.src_eg.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.src_eg.pos);

                    if (build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);
                    
                    return (pos_dist_a < pos_dist_b);
                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
		}






        //----------------------------------------------------------------------------------
        //  (군량) 바닥났을 때 긴급 수송 
        //----------------------------------------------------------------------------------




		/** 병력 있는 거점 찾기 */

		bool needERfood(pk::building@ base)
		{
			// 근접한 적 부대 수
			int enemy_units1 = 0;
			int enemy_troops1 = 0;

			// 3칸 이내 적 부대 수
			int enemy_units3 = 0;
			// 3칸 이내 적 병력 수
			int enemy_troops3 = 0;


			// 4칸 이내 적 부대 수
			int enemy_units4 = 0;
			// 4칸 이내 적 병력 수
			int enemy_troops4 = 0;
			

			int force_units7 = 0;



			auto range = pk::range(base.get_pos(), 1, 22);
			for (int i = 0; i < int(range.length); i++)
			{
				auto unit = pk::get_unit(range[i]);
				if (pk::is_alive(unit))
				{
					int distance = pk::get_distance(base.get_pos(), range[i]);
					if (pk::is_enemy(base, unit))
					{
						if (distance <= 1)
						{
							enemy_units1++;
							enemy_troops1 += unit.troops;
						}
						if (distance <= 10)
						{
							enemy_units3++;
							enemy_troops3 += unit.troops;
						}
						
						if (distance <= 22)
						{
							enemy_units4++;
							enemy_troops4 += unit.troops;
						}
						
					}


					else if (base.get_force_id() == unit.get_force_id() and unit.type == 부대종류_전투)
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

			if (enemy_units1 >= 10)  // 거점 포위 상태로 수송 불가
				return false;
			int base_troops = pk::get_troops(base);
            pk::force@ force = pk::get_force(base.get_force_id());

                        int enemy_weight = countNeighborEnemyBase(base);
            pk::city@ city_a = pk::get_city(pk::get_city_id(base.pos));

	//  병량 1만 이상에 병력 대비 1배 이상 있고, 적 침공에서 안전한 병력 2천 이상 관문, 항구에서 보급 보내라

if ( 10000 <= pk::get_food(base) and pk::get_food(base) >= pk::get_troops(base) * 1.f and 건물_관문시작 <= base.get_id() and base.get_id() < 건물_항구끝 and enemy_troops3  == 0 and  enemy_units3  == 0 and (func_enemy_city_count(city_a, 1)  == 0 or enemy_troops4  == 0 ) and 2000 <= pk::get_troops(base)  )
				return true;


	// 병량 1만 이상에 병력 대비 1배 이상 있고, 적 침공에서 안전한 병력 4천 이상 도시에서 보급 보내라
if ( 10000 <= pk::get_food(base) and pk::get_food(base) >= pk::get_troops(base) * 1.f  and  건물_도시시작 <= base.get_id() and base.get_id() < 건물_도시끝 and enemy_troops3  == 0 and  enemy_units3  == 0 and (func_enemy_city_count(city_a, 1)  == 0 or enemy_troops4  == 0 and 4000 <= pk::get_troops(base) )  )
				return true;


	// 도시가 1개 남았을땐, 병량 1만 이상에 병력 대비 1배 이상 있고, 적 부대가 근처에 없는 거점에서 보급 보내라
			if ( 10000 <= pk::get_food(base) and pk::get_food(base) >= pk::get_troops(base) * 1.f  and  base.get_id() < 건물_거점끝 and enemy_troops3  == 0 and  enemy_units3  == 0 and pk::get_city_list(force).count <= 1  )
				return true;      
			
			return false;
		}







		/** 군량 20% 보급 명령 (나머지 5%)  */

		bool PushERfood(pk::building@ base)
		{
            int reinforce_troops = pk::min(1000,  int (pk::get_troops(base) * 0.15f) );
			// 명령 가능한 무장이 있는지 확인.
			auto person_list = pk::get_idle_person_list(base);
			if (person_list.count == 0) return false;

			// 인접 거접이 있는지 확인.
			int target = getBackupEFBase(base);
			if (target == -1) return false;

			if (!no_enemy_around(pk::get_building(target))) return false;
			if (enemy_approach(pk::get_building(target))) return false;
			if (close_combat(pk::get_building(target))) return false;

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
            
            int unit_food = int(pk::min( 0.3f * pk::get_food(base), 5.0f * reinforce_troops));
            if (unit_food < int(1.0f * reinforce_troops)) return false;   // 병량 부족      


            float supply_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            float weapon_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            
			// 출진 명령 정보 생성.
			pk::com_deploy_cmd_info cmd;
			@cmd.base = @base;
			cmd.type = 부대종류_수송;
			cmd.member[0] = leader.get_id();
			cmd.gold = pk::min(int(pk::get_gold(base) * 0.01f), 10000);
			cmd.food = pk::min(pk::max (int(pk::get_food(base) * 0.20f) , unit_food), 60000);
			cmd.troops = reinforce_troops;
			int i = 0;
			for (int weapon_id = 0; weapon_id < 병기_끝; weapon_id++)
			{
                int weapon_amount = 0;
                if (weapon_id < 병기_충차)
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id) * 0.05f), 4000);
                else
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id)), 1);
                
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
            pk::say(pk::u8encode("군량이 바닥나겠군... \n빨리 군량을 보내자."), leader);
            
            // 임시 도주 효과 ('19.3.6)
            if (거점수송_일시도주설정)
            {
                leader.skill = retreat_skill;         // 특기 복원
            }
            
            
			return true;
		}





        
		/** 가장 가깝고 위기에 빠진 아군 도시에 보급을 보냄 */

        pk::building@ src_ef;
		int getBackupEFBase(pk::building@ src)
		{
			int best_dst = -1;
			int best_distance = 0;
            int src_id = src.get_id();
            pk::list<pk::building@> dst_list; 
            @src_ef = @src;



            
            int search_base = 건물_도시끝;
            if      (거점수송_거점검색모드 == 0) search_base = 건물_도시끝;
            else if (거점수송_거점검색모드 == 1) search_base = 건물_거점끝;
            
            pk::force@ force = pk::get_force(src.get_force_id());
            
			// 거점 검색

                for (int i = 0; i < search_base; i++)
                {
                    pk::building@ dst = pk::get_building(i);
                    int dst_id = dst.get_id();
			int base2_troops = pk::get_troops(dst);

                
                    // 도시거리
                    int city_dist = -1;
                    if (dst_id < 건물_도시끝 and src_id < 건물_도시끝)
                        city_dist = pk::get_city_distance(dst_id, src_id);
                    
                    // 거점거리
                    int base_dist = pk::get_building_distance(dst_id, src_id, src.get_force_id());
                    
                    // 거리 조건 만족 시  (거리 1~3)
                if ( (base_dist == 1 and !intercept1_Enemy_base(src, dst) and !intercept_delta_Enemy_base(src, dst)) or ((base_dist == 2 or (city_dist == 1 and base_dist <= 3)) and !intercept2_Enemy_base(src, dst) and !intercept_delta_Enemy_base(src, dst)) )   
                    {
                       // 목적지가 메뚜기 재해지역이면서 병력 대비 병량이 0.35배 초과면 안감. (0.35배 이하면 병력들 굶어죽을까봐 병량 수송함)
	          pk::city@ city_c = pk::get_city(pk::get_city_id(dst.pos));
                        if (city_c.inago and pk::get_troops(dst) * 0.35f < pk::get_food(dst))  continue;

                        int enemy_weight = countNeighborEnemyBase(dst);

	// 공급지가 항관이고 군량이 항관보다 적은 적 침공에서 안전한 도시로 보급 보내라

        if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst) and 건물_관문시작 <= src_id and src_id < 건물_항구끝 and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and  pk::get_food(dst) <= pk::get_food(src) and no_enemy_around(dst) and enemy_weight  == 0 and func_already (dst) <= 1 and func_supplycheck(src,dst) == 0 )
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
                    }


	// 군량이 4천 이하나 병력 대비 0.5배 이하인, 적 침공에서 안전한 도시로 보급 보내라
                    
        if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst) and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and  ( pk::get_food(dst) <=  4000 or  pk::get_troops(dst) * 0.5f >= pk::get_food(dst) ) and no_enemy_around(dst) and enemy_weight  == 0 and func_already (dst) <= 1 and func_supplycheck(src,dst) == 0 )
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
                    }



           //군량이 3천 이하나 병력 대비 0.5배 이하인, 적 침공에서 안전한 관문, 항구로 보급 보내라

       else if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst) and 건물_관문시작 <= dst_id and dst_id < 건물_항구끝 and  ( pk::get_food(dst) <=  3000 or  pk::get_troops(dst) * 0.5f >= pk::get_food(dst) ) and no_enemy_around(dst) and enemy_weight  == 0 and func_already (dst) <= 1 and func_supplycheck(src,dst) == 0 and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id)
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
                    }





           // 공급지가 항관이고 군량이 항관보다 적은 접경지대의 도시로 보급 보내라

       else if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst) and 건물_관문시작 <= src_id and src_id < 건물_항구끝 and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and  pk::get_food(dst) <=  pk::get_food(src) and no_enemy_around(dst) and  1 <= enemy_weight and func_already (dst) <= 1 and func_supplycheck(src,dst) == 0 )
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
                    }


           // 군량이 1만 이하나 병력 대비 0.5배 이하인 , 접경지대의 도시로 보급 보내라

       else if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst) and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and  ( pk::get_food(dst) <=  10000 or  pk::get_troops(dst) * 0.5f >= pk::get_food(dst) ) and no_enemy_around(dst) and  1 <= enemy_weight and func_already (dst) <= 1 and func_supplycheck(src,dst) == 0 )
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
                    }



           // 군량이 4천 이하나 병력 대비 0.5배 이하인 , 접경지대의 관문, 항구로 보급 보내라

       else if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst) and 건물_관문시작 <= dst_id and dst_id < 건물_항구끝 and  ( pk::get_food(dst) <=  4000 or  pk::get_troops(dst) * 0.5f >= pk::get_food(dst) ) and no_enemy_around(dst) and  1 <= enemy_weight  and func_already (dst) <= 1 and func_supplycheck(src,dst) == 0 and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id)
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
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
                    return (float(pk::get_food(a) + 10) / float(pk::get_troops(a) + 10) < float(pk::get_food(b) + 10) / float(pk::get_troops(b) + 10));							
					
                    int build_dist_a = pk::get_building_distance(a.get_id(), main.src_ef.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.src_ef.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.src_ef.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.src_ef.pos);

                    if (build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);
                    
                    return (pos_dist_a < pos_dist_b);
                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
		}







        //----------------------------------------------------------------------------------
        //   접경지 (금) 바닥났을 때 긴급 수송 - 항구 관문에서 도시로
        //----------------------------------------------------------------------------------




		/** 병력 있는 거점 찾기 */

		bool needXERgold(pk::building@ base)
		{
			if (!no_enemy_around(base)) return false;

			int base_troops = pk::get_troops(base);
            pk::force@ force = pk::get_force(base.get_force_id()); 

                        int enemy_weight = countNeighborEnemyBase(base);
            pk::city@ city_a = pk::get_city(pk::get_city_id(base.pos));

	//  금 3000 이상 있고 , 적 침공에서 안전한 병력 2천 이상 관문, 항구에서 보급 보내라

	if ( 3000 <= pk::get_gold(base) and 건물_관문시작 <= base.get_id() and base.get_id() < 건물_항구끝 and no_enemy_around(base) and 1 <= func_enemy_city_count(city_a, 1) and 2 <= pk::get_city_list(force).count and 2000 <= pk::get_troops(base) )
				return true;




			return false;            

		}







		/** 금 20% 보급 명령 (나머지 5%)  */

		bool PushXERgold(pk::building@ base)
		{
            int reinforce_troops = pk::min(1000,  int (pk::get_troops(base) * 0.15f) );
			// 명령 가능한 무장이 있는지 확인.
			auto person_list = pk::get_idle_person_list(base);
			if (person_list.count == 0) return false;

			// 인접 거접이 있는지 확인.
			int target = getBackupXEGBase(base);
			if (target == -1) return false;

			if (!no_enemy_around(pk::get_building(target))) return false;
			if (enemy_approach(pk::get_building(target))) return false;
			if (close_combat(pk::get_building(target))) return false;

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
            int unit_food = int(pk::min( 0.3f * pk::get_food(base), 2.0f * reinforce_troops));
            if (unit_food < int(1.0f * reinforce_troops)) return false;   // 병량 부족            

            float supply_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            float weapon_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            
			// 출진 명령 정보 생성.
			pk::com_deploy_cmd_info cmd;
			@cmd.base = @base;
			cmd.type = 부대종류_수송;
			cmd.member[0] = leader.get_id();
			cmd.gold = pk::min(int(pk::get_gold(base) * 0.20f), 3000);
			cmd.food = pk::min(pk::max (1000 , unit_food), 25000);
			cmd.troops = reinforce_troops;
			int i = 0;
			for (int weapon_id = 0; weapon_id < 병기_끝; weapon_id++)
			{
                int weapon_amount = 0;
                if (weapon_id < 병기_충차)
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id) * 0.05f), 4000);
                else
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id)), 1);
                
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
            pk::say(pk::u8encode("아군 도시 금이 부족하다.\n접경지니 조심하도록."), leader);
            
            // 임시 도주 효과 ('19.3.6)
            if (거점수송_일시도주설정)
            {
                leader.skill = retreat_skill;         // 특기 복원
            }
            
            
			return true;
		}





        
		/** 가장 가깝고 위기에 빠진 아군 도시에 보급을 보냄 */

        pk::building@ src_Xeg;
		int getBackupXEGBase(pk::building@ src)
		{
			int best_dst = -1;
			int best_distance = 0;
            int src_id = src.get_id();
            pk::list<pk::building@> dst_list; 
            @src_Xeg = @src;



            
            int search_base = 건물_도시끝;
            if      (거점수송_거점검색모드 == 0) search_base = 건물_도시끝;
            else if (거점수송_거점검색모드 == 1) search_base = 건물_거점끝;
            
            pk::force@ force = pk::get_force(src.get_force_id());
            
			// 거점 검색

                for (int i = 0; i < search_base; i++)
                {
                    pk::building@ dst = pk::get_building(i);
                    int dst_id = dst.get_id();

			int base2_troops = pk::get_troops(dst);

                
                    // 도시거리
                    int city_dist = -1;
                    if (dst_id < 건물_도시끝 and src_id < 건물_도시끝)
                        city_dist = pk::get_city_distance(dst_id, src_id);
                    
                    // 거점거리
                    int base_dist = pk::get_building_distance(dst_id, src_id, src.get_force_id());
                    
                    // 거리 조건 만족 시  (거리 1~3)
                if ( (base_dist == 1 and !intercept1_Enemy_base(src, dst) and !intercept_delta_Enemy_base(src, dst)) or ((base_dist == 2 or (city_dist == 1 and base_dist <= 3)) and !intercept2_Enemy_base(src, dst) and !intercept_delta_Enemy_base(src, dst)) )    
                    {



                        int enemy_weight = countNeighborEnemyBase(dst);




			int force_base18 = 0;
                        pk::list<pk::building@> fbase_list; 


			int enemy_base12 = 0;
                        pk::list<pk::building@> ebase_list; 


			auto building_range = pk::range(dst.get_pos(), 1, 19 + (dst.facility == 시설_도시 ? 1 : 0));
			for (int i = 0; i < int(building_range.length); i++)
			{
				auto base = pk::get_building(building_range[i]);
				if (pk::is_alive(base))
				{
					int distance = pk::get_distance(dst.get_pos(), building_range[i]);

					if (pk::is_enemy(dst, base))
					{

						if (distance <= 12)
						{
                                                        ebase_list.add(base);                                                         
							enemy_base12 ++;
						}
					}

					else if (dst.get_force_id() == base.get_force_id() )
					{
                                                if (distance <= 18)
						{
                                                        fbase_list.add(base);                                                         
							force_base18++;
						}
					}



				}
			}


			int senemy_base12  = 0;
                        pk::list<pk::building@> sebase_list; 

			auto sbuilding_range = pk::range(src.get_pos(), 1, 19 + (src.facility == 시설_도시 ? 1 : 0));
			for (int i = 0; i < int(sbuilding_range.length); i++)
			{
				auto sebase = pk::get_building(sbuilding_range[i]);
				if (pk::is_alive(sebase))
				{
					int distance = pk::get_distance(src.get_pos(), sbuilding_range[i]);



					if (pk::is_enemy(src, sebase) )
					{
                                                if (distance <= 12)
						{
                                                        sebase_list.add(sebase);                                                         
							senemy_base12 ++;
						}
					}



				}
			}



	// 금 1천 이하거나 공급 거점보다 2배 이하의, 적 침공에서 안전한 도시로 보급 보내라
                    
if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst) and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and (pk::get_gold(dst) <= 1000 or pk::get_gold(dst) *2 <= pk::get_gold(src)) and no_enemy_around(dst) and enemy_weight  == 0 and func_already (dst) <= 1 and func_supplycheck(src,dst) == 0)
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
                    }






           // 금 2천 이하거나 공급 거점보다 2배 이하의 접경지대의 도시로 보급 보내라

else if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst) and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and (pk::get_gold(dst) <= 2000 or pk::get_gold(dst) *2 <= pk::get_gold(src)) and no_enemy_around(dst) and 1 <= enemy_weight and func_already (dst) <= 1 and func_supplycheck(src,dst) == 0 and 1 <= force_base18 and fbase_list.contains(src) and ( enemy_base12 == 0 or senemy_base12 == 0 ) )
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
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
                    int build_dist_a = pk::get_building_distance(a.get_id(), main.src_Xeg.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.src_Xeg.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.src_Xeg.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.src_Xeg.pos);

                    if (build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);
                    
                    return (pos_dist_a < pos_dist_b);
                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
		}








        //----------------------------------------------------------------------------------
        //   접경지 (금) 바닥났을 때 긴급 수송 - 도시에서 항구 관문으로 
        //----------------------------------------------------------------------------------




		/** 병력 있는 거점 찾기 */

		bool needXERgold1(pk::building@ base)
		{
			if (!no_enemy_around(base)) return false;

			int base_troops = pk::get_troops(base);
            pk::force@ force = pk::get_force(base.get_force_id()); 

                        int enemy_weight = countNeighborEnemyBase(base);
            pk::city@ city_a = pk::get_city(pk::get_city_id(base.pos));




	// 금 3000 이상 있고, 적 침공에서 안전한 병력 4천 이상 도시에서 보급 보내라
	if ( 3000 <= pk::get_gold(base) and 건물_도시시작 <= base.get_id() and base.get_id() < 건물_도시끝 and no_enemy_around(base) and 1 <= func_enemy_city_count(city_a, 1) and 2 <= pk::get_city_list(force).count and 4000 <= pk::get_troops(base) )
				return true;

			return false;            

		}







		/** 금 20% 보급 명령 (나머지 5%)  */

		bool PushXERgold1(pk::building@ base)
		{
            int reinforce_troops = pk::min(1000,  int (pk::get_troops(base) * 0.15f) );
			// 명령 가능한 무장이 있는지 확인.
			auto person_list = pk::get_idle_person_list(base);
			if (person_list.count == 0) return false;

			// 인접 거접이 있는지 확인.
			int target = getBackupXEGBase1(base);
			if (target == -1) return false;

			if (!no_enemy_around(pk::get_building(target))) return false;
			if (enemy_approach(pk::get_building(target))) return false;
			if (close_combat(pk::get_building(target))) return false;

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
            int unit_food = int(pk::min( 0.3f * pk::get_food(base), 2.0f * reinforce_troops));
            if (unit_food < int(1.0f * reinforce_troops)) return false;   // 병량 부족            

            float supply_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            float weapon_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            
			// 출진 명령 정보 생성.
			pk::com_deploy_cmd_info cmd;
			@cmd.base = @base;
			cmd.type = 부대종류_수송;
			cmd.member[0] = leader.get_id();
			cmd.gold = pk::min(int(pk::get_gold(base) * 0.20f), 3000);
			cmd.food = pk::min(pk::max (1000 , unit_food), 25000);
			cmd.troops = reinforce_troops;
			int i = 0;
			for (int weapon_id = 0; weapon_id < 병기_끝; weapon_id++)
			{
                int weapon_amount = 0;
                if (weapon_id < 병기_충차)
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id) * 0.05f), 4000);
                else
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id)), 1);
                
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
            pk::say(pk::u8encode("항관의금이 부족하다.\n접경지니 조심하도록."), leader);
            
            // 임시 도주 효과 ('19.3.6)
            if (거점수송_일시도주설정)
            {
                leader.skill = retreat_skill;         // 특기 복원
            }
            
            
			return true;
		}





        
		/** 가장 가깝고 위기에 빠진 아군 도시에 보급을 보냄 */

        pk::building@ src_Xeg1;
		int getBackupXEGBase1(pk::building@ src)
		{
			int best_dst = -1;
			int best_distance = 0;
            int src_id = src.get_id();
            pk::list<pk::building@> dst_list; 
            @src_Xeg1 = @src;



            
            int search_base = 건물_도시끝;
            if      (거점수송_거점검색모드 == 0) search_base = 건물_도시끝;
            else if (거점수송_거점검색모드 == 1) search_base = 건물_거점끝;
            
            pk::force@ force = pk::get_force(src.get_force_id());
            
			// 거점 검색

                for (int i = 0; i < search_base; i++)
                {
                    pk::building@ dst = pk::get_building(i);
                    int dst_id = dst.get_id();

			int base2_troops = pk::get_troops(dst);

                
                    // 도시거리
                    int city_dist = -1;
                    if (dst_id < 건물_도시끝 and src_id < 건물_도시끝)
                        city_dist = pk::get_city_distance(dst_id, src_id);
                    
                    // 거점거리
                    int base_dist = pk::get_building_distance(dst_id, src_id, src.get_force_id());
                    
                    // 거리 조건 만족 시  (거리 1~3)
                if ( (base_dist == 1 and !intercept1_Enemy_base(src, dst) and !intercept_delta_Enemy_base(src, dst)) or ((base_dist == 2 or (city_dist == 1 and base_dist <= 3)) and !intercept2_Enemy_base(src, dst) and !intercept_delta_Enemy_base(src, dst)) )      
                    {



                        int enemy_weight = countNeighborEnemyBase(dst);


			int force_base18 = 0;
                        pk::list<pk::building@> fbase_list; 


			int enemy_base12 = 0;
                        pk::list<pk::building@> ebase_list; 


			auto building_range = pk::range(dst.get_pos(), 1, 19 + (dst.facility == 시설_도시 ? 1 : 0));
			for (int i = 0; i < int(building_range.length); i++)
			{
				auto base = pk::get_building(building_range[i]);
				if (pk::is_alive(base))
				{
					int distance = pk::get_distance(dst.get_pos(), building_range[i]);

					if (pk::is_enemy(dst, base))
					{

						if (distance <= 12)
						{
                                                        ebase_list.add(base);                                                         
							enemy_base12 ++;
						}
					}

					else if (dst.get_force_id() == base.get_force_id() )
					{
                                                if (distance <= 18)
						{
                                                        fbase_list.add(base);                                                         
							force_base18++;
						}
					}



				}
			}


			int senemy_base12  = 0;
                        pk::list<pk::building@> sebase_list; 

			auto sbuilding_range = pk::range(src.get_pos(), 1, 19 + (src.facility == 시설_도시 ? 1 : 0));
			for (int i = 0; i < int(sbuilding_range.length); i++)
			{
				auto sebase = pk::get_building(sbuilding_range[i]);
				if (pk::is_alive(sebase))
				{
					int distance = pk::get_distance(src.get_pos(), sbuilding_range[i]);



					if (pk::is_enemy(src, sebase) )
					{
                                                if (distance <= 12)
						{
                                                        sebase_list.add(sebase);                                                         
							senemy_base12 ++;
						}
					}



				}
			}





           //금 1천 이하로, 적 침공에서 안전한 관문, 항구로 보급 보내라

if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst) and 건물_관문시작 <= dst_id and dst_id < 건물_항구끝 and  pk::get_gold(dst) <= 1000 and no_enemy_around(dst) and enemy_weight  == 0 and func_already (dst) <= 1 and func_supplycheck(src,dst) == 0 and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id)
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
                    }






           // 금 2천 이하로, 접경지대의 관문, 항구로 보급 보내라

else if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst) and 건물_관문시작 <= dst_id and dst_id < 건물_항구끝 and  pk::get_gold(dst) <= 2000 and no_enemy_around(dst) and 1 <= enemy_weight and func_already (dst) <= 1 and func_supplycheck(src,dst) == 0  and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id  and 1 <= force_base18 and fbase_list.contains(src) and ( enemy_base12 == 0 or senemy_base12 == 0 ))
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
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
                    int build_dist_a = pk::get_building_distance(a.get_id(), main.src_Xeg1.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.src_Xeg1.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.src_Xeg1.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.src_Xeg1.pos);

                    if (build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);
                    
                    return (pos_dist_a < pos_dist_b);
                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
		}






















        //----------------------------------------------------------------------------------
        //  접경지 (군량) 바닥났을 때 긴급 수송 - 항구 관문에서 도시로
        //----------------------------------------------------------------------------------




		/** 병력 있는 거점 찾기 */

		bool needXERfood(pk::building@ base)
		{
			if (!no_enemy_around(base)) return false;

			int base_troops = pk::get_troops(base);
            pk::force@ force = pk::get_force(base.get_force_id());

                        int enemy_weight = countNeighborEnemyBase(base);
            pk::city@ city_a = pk::get_city(pk::get_city_id(base.pos));

	//  병량 5천 이상에 병력 대비 1.5배 이상 있고, 적 침공에서 안전한 병력 2천 이상 관문, 항구에서 보급 보내라

if ( 5000 <= pk::get_food(base) and pk::get_food(base) >= pk::get_troops(base) * 1.5f and 건물_관문시작 <= base.get_id() and base.get_id() < 건물_항구끝 and no_enemy_around(base) and 1 <= func_enemy_city_count(city_a, 1) and 2 <= pk::get_city_list(force).count and 2000 <= pk::get_troops(base) )
				return true;




   
			
			return false;
		}







		/** 군량 20% 보급 명령 (나머지 5%)  */

		bool PushXERfood(pk::building@ base)
		{
            int reinforce_troops = pk::min(1000,  int (pk::get_troops(base) * 0.15f) );
			// 명령 가능한 무장이 있는지 확인.
			auto person_list = pk::get_idle_person_list(base);
			if (person_list.count == 0) return false;

			// 인접 거접이 있는지 확인.
			int target = getBackupXEFBase(base);
			if (target == -1) return false;

			if (!no_enemy_around(pk::get_building(target))) return false;
			if (enemy_approach(pk::get_building(target))) return false;
			if (close_combat(pk::get_building(target))) return false;

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
            
            int unit_food = int(pk::min( 0.3f * pk::get_food(base), 5.0f * reinforce_troops));
            if (unit_food < int(1.0f * reinforce_troops)) return false;   // 병량 부족      


            float supply_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            float weapon_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            
			// 출진 명령 정보 생성.
			pk::com_deploy_cmd_info cmd;
			@cmd.base = @base;
			cmd.type = 부대종류_수송;
			cmd.member[0] = leader.get_id();
			cmd.gold = pk::min(int(pk::get_gold(base) * 0.01f), 10000);
			cmd.food = pk::min(pk::max (int(pk::get_food(base) * 0.20f) , unit_food), 60000);
			cmd.troops = reinforce_troops;
			int i = 0;
			for (int weapon_id = 0; weapon_id < 병기_끝; weapon_id++)
			{
                int weapon_amount = 0;
                if (weapon_id < 병기_충차)
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id) * 0.05f), 4000);
                else
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id)), 1);
                
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
            pk::say(pk::u8encode("아군 도시 군량이 부족하다.\n접경지니 조심하도록."), leader);
            
            // 임시 도주 효과 ('19.3.6)
            if (거점수송_일시도주설정)
            {
                leader.skill = retreat_skill;         // 특기 복원
            }
            
            
			return true;
		}





        
		/** 가장 가깝고 위기에 빠진 아군 도시에 보급을 보냄 */

        pk::building@ src_Xef;
		int getBackupXEFBase(pk::building@ src)
		{
			int best_dst = -1;
			int best_distance = 0;
            int src_id = src.get_id();
            pk::list<pk::building@> dst_list; 
            @src_Xef = @src;



            
            int search_base = 건물_도시끝;
            if      (거점수송_거점검색모드 == 0) search_base = 건물_도시끝;
            else if (거점수송_거점검색모드 == 1) search_base = 건물_거점끝;
            
            pk::force@ force = pk::get_force(src.get_force_id());
            
			// 거점 검색

                for (int i = 0; i < search_base; i++)
                {
                    pk::building@ dst = pk::get_building(i);
                    int dst_id = dst.get_id();
			int base2_troops = pk::get_troops(dst);

                
                    // 도시거리
                    int city_dist = -1;
                    if (dst_id < 건물_도시끝 and src_id < 건물_도시끝)
                        city_dist = pk::get_city_distance(dst_id, src_id);
                    
                    // 거점거리
                    int base_dist = pk::get_building_distance(dst_id, src_id, src.get_force_id());
                    
                    // 거리 조건 만족 시 (거리 1~3)
                if ( (base_dist == 1 and !intercept1_Enemy_base(src, dst) and !intercept_delta_Enemy_base(src, dst)) or ((base_dist == 2 or (city_dist == 1 and base_dist <= 3)) and !intercept2_Enemy_base(src, dst) and !intercept_delta_Enemy_base(src, dst)) )   
                    {
                       // 목적지가 메뚜기 재해지역이면서 병력 대비 병량이 0.35배 초과면 안감. (0.35배 이하면 병력들 굶어죽을까봐 병량 수송함)
	          pk::city@ city_c = pk::get_city(pk::get_city_id(dst.pos));
                        if (city_c.inago and pk::get_troops(dst) * 0.35f < pk::get_food(dst))  continue;

                        int enemy_weight = countNeighborEnemyBase(dst);

			int force_base18 = 0;
                        pk::list<pk::building@> fbase_list; 


			int enemy_base12 = 0;
                        pk::list<pk::building@> ebase_list; 


			auto building_range = pk::range(dst.get_pos(), 1, 19 + (dst.facility == 시설_도시 ? 1 : 0));
			for (int i = 0; i < int(building_range.length); i++)
			{
				auto base = pk::get_building(building_range[i]);
				if (pk::is_alive(base))
				{
					int distance = pk::get_distance(dst.get_pos(), building_range[i]);

					if (pk::is_enemy(dst, base))
					{

						if (distance <= 12)
						{
                                                        ebase_list.add(base);                                                         
							enemy_base12 ++;
						}
					}

					else if (dst.get_force_id() == base.get_force_id() )
					{
                                                if (distance <= 18)
						{
                                                        fbase_list.add(base);                                                         
							force_base18++;
						}
					}



				}
			}


			int senemy_base12  = 0;
                        pk::list<pk::building@> sebase_list; 

			auto sbuilding_range = pk::range(src.get_pos(), 1, 19 + (src.facility == 시설_도시 ? 1 : 0));
			for (int i = 0; i < int(sbuilding_range.length); i++)
			{
				auto sebase = pk::get_building(sbuilding_range[i]);
				if (pk::is_alive(sebase))
				{
					int distance = pk::get_distance(src.get_pos(), sbuilding_range[i]);



					if (pk::is_enemy(src, sebase) )
					{
                                                if (distance <= 12)
						{
                                                        sebase_list.add(sebase);                                                         
							senemy_base12 ++;
						}
					}



				}
			}



	// 군량이 4천 이하나 병력 대비 1.2배 이하인, 적 침공에서 안전한 도시로 보급 보내라
                    
        if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst) and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and  ( pk::get_food(dst) <=  4000 or  pk::get_troops(dst) * 1.2f >= pk::get_food(dst) )  and no_enemy_around(dst) and enemy_weight  == 0 and func_already (dst) <= 1 and func_supplycheck(src,dst) == 0 )
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
                    }





           // 군량이 1만 이하나 병력 대비 1.5배 이하인 , 접경지대의 도시로 보급 보내라

       else if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst) and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and  ( pk::get_food(dst) <=  10000 or  pk::get_troops(dst) * 1.5f >= pk::get_food(dst) or ( pk::get_food(dst) <= pk::get_food(src) and pk::get_troops(src) * 2.f <= base2_troops ) ) and no_enemy_around(dst) and 1 <= enemy_weight and func_already (dst) <= 1 and func_supplycheck(src,dst) == 0 and 1 <= force_base18 and fbase_list.contains(src) and ( enemy_base12 == 0 or senemy_base12 == 0 ))
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
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
                    int build_dist_a = pk::get_building_distance(a.get_id(), main.src_Xef.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.src_Xef.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.src_Xef.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.src_Xef.pos);

                    if (build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);
                    
                    return (pos_dist_a < pos_dist_b);
                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
		}






        //----------------------------------------------------------------------------------
        //  접경지 (군량) 바닥났을 때 긴급 수송 - 도시에서 항구 관문으로
        //----------------------------------------------------------------------------------




		/** 병력 있는 거점 찾기 */

		bool needXERfood1(pk::building@ base)
		{
			if (!no_enemy_around(base)) return false;

			int base_troops = pk::get_troops(base);
            pk::force@ force = pk::get_force(base.get_force_id());

                        int enemy_weight = countNeighborEnemyBase(base);
            pk::city@ city_a = pk::get_city(pk::get_city_id(base.pos));



	// 병량 1만 이상에 병력 대비 1.5배 이상 있고, 적 침공에서 안전한 병력 4천 이상 도시에서 보급 보내라
if ( 10000 <= pk::get_food(base) and pk::get_food(base) >= pk::get_troops(base) * 1.5f and 건물_도시시작 <= base.get_id() and base.get_id() < 건물_도시끝 and no_enemy_around(base) and 1 <= func_enemy_city_count(city_a, 1) and 2 <= pk::get_city_list(force).count and 4000 <= pk::get_troops(base)  )
				return true;

   
			
			return false;
		}







		/** 군량 20% 보급 명령 (나머지 5%)  */

		bool PushXERfood1(pk::building@ base)
		{
            int reinforce_troops = pk::min(1000,  int (pk::get_troops(base) * 0.15f) );
			// 명령 가능한 무장이 있는지 확인.
			auto person_list = pk::get_idle_person_list(base);
			if (person_list.count == 0) return false;

			// 인접 거접이 있는지 확인.
			int target = getBackupXEFBase1(base);
			if (target == -1) return false;

			if (!no_enemy_around(pk::get_building(target))) return false;
			if (enemy_approach(pk::get_building(target))) return false;
			if (close_combat(pk::get_building(target))) return false;

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
            
            int unit_food = int(pk::min( 0.3f * pk::get_food(base), 5.0f * reinforce_troops));
            if (unit_food < int(1.0f * reinforce_troops)) return false;   // 병량 부족      


            float supply_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            float weapon_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            
			// 출진 명령 정보 생성.
			pk::com_deploy_cmd_info cmd;
			@cmd.base = @base;
			cmd.type = 부대종류_수송;
			cmd.member[0] = leader.get_id();
			cmd.gold = pk::min(int(pk::get_gold(base) * 0.01f), 10000);
			cmd.food = pk::min(pk::max (int(pk::get_food(base) * 0.20f) , unit_food), 60000);
			cmd.troops = reinforce_troops;
			int i = 0;
			for (int weapon_id = 0; weapon_id < 병기_끝; weapon_id++)
			{
                int weapon_amount = 0;
                if (weapon_id < 병기_충차)
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id) * 0.05f), 4000);
                else
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id)), 1);
                
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
            pk::say(pk::u8encode("항관의 군량이 부족하다.\n접경지니 조심하도록."), leader);
            
            // 임시 도주 효과 ('19.3.6)
            if (거점수송_일시도주설정)
            {
                leader.skill = retreat_skill;         // 특기 복원
            }
            
            
			return true;
		}





        
		/** 가장 가깝고 위기에 빠진 아군 도시에 보급을 보냄 */

        pk::building@ src_Xef1;
		int getBackupXEFBase1(pk::building@ src)
		{
			int best_dst = -1;
			int best_distance = 0;
            int src_id = src.get_id();
            pk::list<pk::building@> dst_list; 
            @src_Xef1 = @src;



            
            int search_base = 건물_도시끝;
            if      (거점수송_거점검색모드 == 0) search_base = 건물_도시끝;
            else if (거점수송_거점검색모드 == 1) search_base = 건물_거점끝;
            
            pk::force@ force = pk::get_force(src.get_force_id());
            
			// 거점 검색

                for (int i = 0; i < search_base; i++)
                {
                    pk::building@ dst = pk::get_building(i);
                    int dst_id = dst.get_id();
			int base2_troops = pk::get_troops(dst);

                
                    // 도시거리
                    int city_dist = -1;
                    if (dst_id < 건물_도시끝 and src_id < 건물_도시끝)
                        city_dist = pk::get_city_distance(dst_id, src_id);
                    
                    // 거점거리
                    int base_dist = pk::get_building_distance(dst_id, src_id, src.get_force_id());
                    
                    // 거리 조건 만족 시 (거리 1~3)
                if ( (base_dist == 1 and !intercept1_Enemy_base(src, dst) and !intercept_delta_Enemy_base(src, dst)) or ((base_dist == 2 or (city_dist == 1 and base_dist <= 3)) and !intercept2_Enemy_base(src, dst) and !intercept_delta_Enemy_base(src, dst)) )    
                    {
                       // 목적지가 메뚜기 재해지역이면서 병력 대비 병량이 0.35배 초과면 안감. (0.35배 이하면 병력들 굶어죽을까봐 병량 수송함)
	          pk::city@ city_c = pk::get_city(pk::get_city_id(dst.pos));
                        if (city_c.inago and pk::get_troops(dst) * 0.35f < pk::get_food(dst))  continue;

                        int enemy_weight = countNeighborEnemyBase(dst);

			int force_base18 = 0;
                        pk::list<pk::building@> fbase_list; 


			int enemy_base12 = 0;
                        pk::list<pk::building@> ebase_list; 


			auto building_range = pk::range(dst.get_pos(), 1, 19 + (dst.facility == 시설_도시 ? 1 : 0));
			for (int i = 0; i < int(building_range.length); i++)
			{
				auto base = pk::get_building(building_range[i]);
				if (pk::is_alive(base))
				{
					int distance = pk::get_distance(dst.get_pos(), building_range[i]);

					if (pk::is_enemy(dst, base))
					{

						if (distance <= 12)
						{
                                                        ebase_list.add(base);                                                         
							enemy_base12 ++;
						}
					}

					else if (dst.get_force_id() == base.get_force_id() )
					{
                                                if (distance <= 18)
						{
                                                        fbase_list.add(base);                                                         
							force_base18++;
						}
					}



				}
			}


			int senemy_base12  = 0;
                        pk::list<pk::building@> sebase_list; 

			auto sbuilding_range = pk::range(src.get_pos(), 1, 19 + (src.facility == 시설_도시 ? 1 : 0));
			for (int i = 0; i < int(sbuilding_range.length); i++)
			{
				auto sebase = pk::get_building(sbuilding_range[i]);
				if (pk::is_alive(sebase))
				{
					int distance = pk::get_distance(src.get_pos(), sbuilding_range[i]);



					if (pk::is_enemy(src, sebase) )
					{
                                                if (distance <= 12)
						{
                                                        sebase_list.add(sebase);                                                         
							senemy_base12 ++;
						}
					}



				}
			}








           //군량이 2천 이하나 병력 대비 0.7배 이하인, 적 침공에서 안전한 관문, 항구로 보급 보내라

       if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst) and 건물_관문시작 <= dst_id and dst_id < 건물_항구끝 and  ( pk::get_food(dst) <= 2000 or  pk::get_troops(dst) * 0.7f >= pk::get_food(dst) ) and no_enemy_around(dst) and enemy_weight  == 0 and func_already (dst) <= 1 and func_supplycheck(src,dst) == 0 and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id)
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
                    }






           // 군량이 3천 이하나 병력 대비 0.9배 이하인 , 접경지대의 관문, 항구로 보급 보내라

       else if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst) and 건물_관문시작 <= dst_id and dst_id < 건물_항구끝 and  ( pk::get_food(dst) <= 3000 or  pk::get_troops(dst) * 0.9f >= pk::get_food(dst) ) and no_enemy_around(dst) and  1 <= enemy_weight  and func_already (dst) <= 1 and func_supplycheck(src,dst) == 0 and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id and 1 <= force_base18 and fbase_list.contains(src) and ( enemy_base12 == 0 or senemy_base12 == 0 ))
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
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
                    int build_dist_a = pk::get_building_distance(a.get_id(), main.src_Xef1.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.src_Xef1.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.src_Xef1.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.src_Xef1.pos);

                    if (build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);
                    
                    return (pos_dist_a < pos_dist_b);
                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
		}











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
            
            weight = int(troops / 3000);
            return weight;
        }



         //  거리에 따른 인근 적대 도시 숫자 체크. masterpiecek님의 AI_도시물자수송.cpp﻿를 참조했습니다.


		int func_enemy_city_count(pk::city@ city, int distance)
		{
			int enemy_city_count = 0;
			for (int i = 0; i < 도시_끝; i++)
			{
				pk::city@ enemycity = pk::get_city(i);
				int city_distance = pk::get_city_distance(city.get_id(), i);

				if (pk::is_alive(enemycity) and city.get_id() != i and pk::is_enemy(city, enemycity) and city_distance <= distance) 

				enemy_city_count++;
																	  										   				   
			}

			return enemy_city_count;
		}



         // 이미 해당거점으로 출진한 부대 숫자 체크. masterpiecek님의 AI_도시물자수송.cpp﻿를 참조했습니다.

	 int func_already(pk::building@ building)
		{
			int already = 0;
			for (int unit_id = 0; unit_id < 부대_끝; unit_id++)
			{
				pk::unit@ unit = pk::get_unit(unit_id);
			if (building.get_force_id() == -1) continue;
			if (unit.get_force_id() == -1) continue;
		if ( pk::is_alive(unit) and unit.type == 부대종류_수송 and unit.get_force_id() == building.get_force_id() and unit.target == building.get_id() and (1000 <= unit.gold or 5000 <= unit.food) ) 

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




        // ***** 거리 1 간 수송시 중간의 적 거점 확인 ***** //
        bool intercept1_Enemy_base(pk::building@ src, pk::building@ dst)
        {
            for (int i = 0; i < 건물_거점끝; i++)
			{
                pk::building@ intercept = pk::get_building(i);
                int src_id = src.get_id();
                int dst_id = dst.get_id();
                int intercept_id = intercept.get_id();
                
                if (src_id != dst_id and src_id != intercept_id and dst_id != intercept_id and pk::is_enemy(src, intercept) and pk::is_enemy(dst, intercept) and
                    pk::get_building_distance(src_id, dst_id, src.get_force_id()) == 1 and
                    pk::get_building_distance(src_id, intercept_id, src.get_force_id()) == 1 and pk::get_building_distance(dst_id, intercept_id, dst.get_force_id()) == 1)

	return true;
            }
            
	return false;
        }




        // ***** 거리 2 간 수송시 중간의 적 거점 확인 ***** //
        bool intercept2_Enemy_base(pk::building@ src, pk::building@ dst)
        {
            for (int i = 0; i < 건물_거점끝; i++)
			{
                pk::building@ intercept = pk::get_building(i);
                int src_id = src.get_id();
                int dst_id = dst.get_id();
                int intercept_id = intercept.get_id();
                
                if (src_id != dst_id and src_id != intercept_id and dst_id != intercept_id and pk::is_enemy(src, intercept) and pk::is_enemy(dst, intercept) and
                    (pk::get_building_distance(src_id, dst_id, src.get_force_id()) == 2 or pk::get_building_distance(src_id, dst_id, src.get_force_id()) == 3 ) and
                    pk::get_building_distance(src_id, intercept_id, src.get_force_id()) <= 2 and pk::get_building_distance(dst_id, intercept_id, dst.get_force_id()) <= 2)

	return true;
            }
            
	return false;
        }



        // ***** 허창 3각지대 간 수송시 중간의 적 거점 확인 ***** //
        bool intercept_delta_Enemy_base(pk::building@ src, pk::building@ dst)
        {
            for (int i = 0; i < 건물_거점끝; i++)
			{
                pk::building@ intercept = pk::get_building(i);
                int src_id = src.get_id();
                int dst_id = dst.get_id();
                int intercept_id = intercept.get_id();
                
                if (src_id != dst_id and src_id != intercept_id and dst_id != intercept_id and pk::is_enemy(src, intercept) and pk::is_enemy(dst, intercept) and
                   (((src_id == 건물_진류 or src_id == 건물_허창 or src_id == 건물_완 or src_id == 건물_낙양 or src_id == 건물_관도항) and
                   (dst_id == 건물_진류 or dst_id == 건물_허창 or dst_id == 건물_완 or dst_id == 건물_낙양 or dst_id == 건물_관도항) and
                   (intercept_id == 건물_진류 or intercept_id == 건물_허창 or intercept_id == 건물_완 or intercept_id == 건물_호로관 or intercept_id == 건물_관도항)) or
                   ((src_id == 건물_진류 or src_id == 건물_허창 or src_id == 건물_완 or src_id == 건물_호로관 or src_id == 건물_관도항) and
                   (dst_id == 건물_진류 or dst_id == 건물_허창 or dst_id == 건물_완 or dst_id == 건물_호로관 or dst_id == 건물_관도항) and
                   (intercept_id == 건물_진류 or intercept_id == 건물_허창 or intercept_id == 건물_완 or intercept_id == 건물_호로관 or intercept_id == 건물_관도항))) )

	return true;
            }
            
	return false;
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
        //---------------------------------------------------------------------------------------

        // ***** 두 거점 사이에 적 부대가 있는지 ***** //
        bool enemy_inside(pk::building@ base, pk::building@ dst)
        {
                pk::array<pk::point> range = pk::range(base.pos, 1, 14);  // 거점 주변 검색
                for (int i = 0; i < int(range.length); i++)
                {
				auto unit_f = pk::get_unit(range[i]);
				if (pk::is_alive(unit_f) and base.get_force_id() == unit_f.get_force_id())  // 아군 부대 찾음
				{	
			            auto paths_base_dst = pk::get_path(unit_f, base.pos, dst.pos);  // 아군 부대의 base-dst 사이 이동 경로
            
				    for (int e = 0; e < int(range.length); e++)
				    {
				        auto unit_e = pk::get_unit(range[e]);

				        if (pk::is_alive(unit_e) and pk::is_enemy(unit_e, base) and pk::is_enemy(unit_e, unit_f))  // 거점 주변에 적부대가 있다면
					{	
				            pk::array<pk::point> arr_range = pk::get_movable_pos(unit_e);  // 적 부대가 이동 가능한 범위
				            for (int j = 0; j < int(arr_range.length); j++)
				            {
				                pk::point pos_e = arr_range[j];	  // 적 부대 이동 가능 지점들

			                           for (int d = 0; d < 방향_끝; d++)
			                           {
			                               pk::point neighbor_pos = pk::get_neighbor_pos(pos_e, d);		  // 적 부대 이동 가능 지점들의 그 이웃 지점들			
			                               pk::point neighbor_pos_mark = pk::get_neighbor_pos(unit_e.pos, d);      // 적 부대의 현재 위치 지점의 그 이웃지점들

		            		               for (int f = 0; f < int(paths_base_dst.length); f++)
		            		               {
		            		                 pk::point pos_f = paths_base_dst[f];     // 아군 부대의 이동 경로 지점들
		            		                 pk::hex@ hex = pk::get_hex(neighbor_pos);
		            		                 pk::hex@ hex_mark = pk::get_hex(neighbor_pos_mark);

			                                    if (pk::is_valid_pos(neighbor_pos) and !hex.has_building)	  // 적 부대 이동 지점과 그 이웃지점들이 유효한 좌표고 건물이 없을때 
			                                    {
			                                        if (pos_f == neighbor_pos)	  // 아군 부대 이동 동선과 적부대의 이동 가능 동선이 겹치면 인정
			                                        {
			                                        return true;
			                                        }
			                                    }

			                                    if (pk::is_valid_pos(neighbor_pos_mark) and !hex_mark.has_building)	  // 적 부대의 현재 위치 지점과 그 이웃지점들이 유효한 좌표고 건물이 없을때 
			                                    {
			                                        if (pos_f == neighbor_pos_mark)	  // 아군 부대 이동 동선과 적부대의 현재 위치가 겹치면 인정
			                                        {
			                                        return true;
			                                        }					
			                                    }

		                                        }   // for

	                                             }   // for

	                                       }   // for
	
                                         }   // if
	
                                     }   // for	

                             }   // if        					

                 }   // for					
            
	return false;
        }

        //---------------------------------------------------------------------------------------


	};

	Main main;
}