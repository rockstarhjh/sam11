/*
제작 by 일송정

본 스크립트는 기마책사님이 제작하신 거점원군.cpp와 기마책사님이 수정하신 거점철수.cpp의 상당 부분을 차용하고 있음을 알려드립니다. 
기마책사님께 감사드립니다.

*/

namespace 전쟁_공격_공성
{

	// ==================CUSTOMIZE =================

        const float 출동부대수_한도비율 = 0.6f;  

        const bool  거점수송_원거리이동  = true;     // 공성부대 이동 1회 추가 (추천기능 : 보너스이동으로 탈출)	
		
		const bool 대사표시_설정 = true;   
	
	// =============================================

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
				for (int i = 0; i < 건물_거점끝; i++)
				{
					auto base = pk::get_building(i);
                    pk::district@ district = pk::get_district(base.get_district_id());					


                    if ( ( !force.is_player() and base.get_force_id() == force_id and needWanderers(base)) 
					or ( force.is_player() and pk::is_alive(district) and !pk::is_player_controlled(base) and base.get_force_id() == force_id and needWanderers(base) and district.attack ) )

                        func_redispatch(base); 


				}
			}

			// 이전 핸들러가 있다면 체인.
			if (prev_callback_ !is null)
				return prev_callback_(force);
			return false;
		}


        //---------------------------------------------------------------------------------------
        //          반복
        //---------------------------------------------------------------------------------------
        
        void func_redispatch(pk::building@ base)
        {

                int push_count = 0; 
                
            auto person_list = pk::get_idle_person_list(base);
                float max_count = pk::max(1.0f, pk::min(person_list.count * 출동부대수_한도비율, 11.0f));
               
	pk::city@ city_a = pk::get_city(pk::get_city_id(base.pos));

                bool cmd = false;
                while(push_count < max_count and pk::get_max_troops(base) * 0.1f + pk::max((func_enemy_city_count(city_a, 1) - 1) * 10000 , 0) < pk::get_troops(base) )
                {
                    push_count += 1;
                    cmd = (PushWanderers(base) or cmd);  
                }

        }



        //----------------------------------------------------------------------------------
        //  도시 정복 부대 출격
        //----------------------------------------------------------------------------------




		/** 병력 있는 거점 찾기 */

		bool needWanderers(pk::building@ base)
		{

			int base_troops = pk::get_troops(base);
			pk::city@ city_a = pk::get_city(pk::get_city_id(base.pos));

			int a = pk::get_person(pk::get_kunshu_id(base)).character;
            auto person_list = pk::get_idle_person_list(base);
            if (person_list.count <  1  ) return false;   // 무장 부족

            if (pk::get_food(base) <= pk::get_troops(base) * 1.2f)  return false;  // 거점에 전쟁 치를 병량 준비 부족

            if (func_enemy_city_count(city_a, 2) == 0) return false; 

            if (pk::enemies_around(base)) return false;  
            //공격대상지와의 거리 사이 (최대 10)에 적부대가 있으면 안됨  							
            if (Enemy_unit_around(base) > 0) return false;  			
			
            //도시 정복 가능 여부 
            if (10000 + pk::max((func_enemy_city_count(city_a, 1) - 1) * 10000 , 0) <= base_troops and (EnemyBase_troops(base) * 0.4f) + ((3 - a) * 7000) - (Friendly_base(base) * 0.2f) <= base_troops and !front_base(base) and person_list.count > (base_troops - (pk::get_max_troops(base) * 0.1f)) / 6000.f )
	        return true;
			/** 내가 수정 */
			if (pk::max((func_enemy_city_count(city_a, 1) - 1) * 5000 , 0) <= base_troops and (EnemyBase_troops(base) * 0.25f) + ((3 - a) * 6000) - (Friendly_base(base) * 0.4f) <= base_troops and !front_base(base) and person_list.count > (base_troops - (pk::get_max_troops(base) * 0.1f)) / 6000.f ) return true;

            //공성 가능 여부
            else if (18000 <= base_troops and !front_base(base))
		    {				
			   if ( count_War_Zone(base) > 0 )
		       {				   
	           return true;
		       }
			   else if (count_Weak_Enemy(base) > 0 )
		       {				   
	           return true;
		       }			   
		    }            
			return false;
		}




        // ***** 인근에 전투 발생 지역 있는지 확인 ***** //
        int Enemy_unit_around(pk::building@ src)
        {
            int Enemy_unit = 0;

           for (int i = 0; i < 건물_거점끝; i++)
           {
                    pk::building@ dst = pk::get_building(i);
                    int dst_id = dst.get_id();
                    int src_id = src.get_id();

            int max_distance = (dst_id >= 건물_도시끝)? 2 : 1;

                    // 도시거리
                    int city_dist = -1;
                    if (dst_id < 건물_도시끝 and src_id < 건물_도시끝)
                        city_dist = pk::get_city_distance(dst_id, src_id);
                    
                    // 거점거리
                    int base_dist = pk::get_building_distance(src_id, dst_id, src.get_force_id());
                    
                    // 거리 조건 만족 시
             if ( (0 <= base_dist and base_dist <= max_distance) or city_dist == 1)  
             {
												          
                if (src_id != dst_id and pk::is_enemy(src, dst) and pk::is_alive(src) and pk::is_alive(dst))
                {
			   if (건물_파양항 == dst_id or 건물_노릉항 == dst_id or 건물_서하항 == dst_id or 건물_하양항 == dst_id or 건물_해현항 == dst_id or 건물_강도항 == dst_id)	continue;	
																																																	   																																								
                      if (건물_도시시작 <= dst_id and dst_id < 건물_항구끝 
					  and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id)																						  
                      {
                      int pos_dist = pk::min(pk::get_distance(src.pos, dst.pos), 10);	
                      if (enemy_around_distance(src, pos_dist))							
		                    Enemy_unit++;
                       }

                }

             }

           } 
            
            return Enemy_unit;
        }




        // ***** 인근에 전투 발생 지역 있는지 확인 ***** //
        int count_War_Zone(pk::building@ src)
        {
            int War_Zone = 0;

                for (int i = 0; i < 건물_거점끝; i++)
                {
                    pk::building@ dst = pk::get_building(i);
                    int dst_id = dst.get_id();
                    int src_id = src.get_id();

            int max_distance = (dst_id >= 건물_도시끝)? 2 : 1;

                    // 도시거리
                    int city_dist = -1;
                    if (dst_id < 건물_도시끝 and src_id < 건물_도시끝)
                        city_dist = pk::get_city_distance(dst_id, src_id);
                    
                    // 거점거리
                    int base_dist = pk::get_building_distance(src_id, dst_id, src.get_force_id());
                    
                    // 거리 조건 만족 시
              if ( (0 <= base_dist and base_dist <= max_distance) or city_dist == 1)  
                  {
												          
                if (src_id != dst_id and pk::is_enemy(src, dst) and pk::is_alive(src) and pk::is_alive(dst))
                     {
			          if (건물_파양항 == dst_id or 건물_노릉항 == dst_id or 건물_서하항 == dst_id or 건물_하양항 == dst_id or 건물_해현항 == dst_id or 건물_강도항 == dst_id)	continue;	
	                  if (!pk::enemies_around(dst)) continue;  												 
																											
                      if (건물_도시시작 <= dst_id and dst_id < 건물_항구끝 
					  and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id
					  and pk::enemies_around(dst))
																						  
                            {
		                    War_Zone++;
                            }

                       }

                  }

               } 
            

            return War_Zone;
        }



        // ***** 인근에 전투 발생 지역 있는지 확인 ***** //
        int count_Weak_Enemy(pk::building@ src)
        {
            int War_Zone = 0;

                for (int i = 0; i < 건물_거점끝; i++)
                {
                    pk::building@ dst = pk::get_building(i);
                    int dst_id = dst.get_id();
                    int src_id = src.get_id();

            int max_distance = (dst_id >= 건물_도시끝)? 2 : 1;

                    // 도시거리
                    int city_dist = -1;
                    if (dst_id < 건물_도시끝 and src_id < 건물_도시끝)
                        city_dist = pk::get_city_distance(dst_id, src_id);
                    
                    // 거점거리
                    int base_dist = pk::get_building_distance(src_id, dst_id, src.get_force_id());
                    
                    // 거리 조건 만족 시
              if ( (0 <= base_dist and base_dist <= max_distance) or city_dist == 1)  
                  {
												          
                if (src_id != dst_id and pk::is_enemy(src, dst) and pk::is_alive(src) and pk::is_alive(dst))
                     {
			          if (건물_파양항 == dst_id or 건물_노릉항 == dst_id or 건물_서하항 == dst_id or 건물_하양항 == dst_id or 건물_해현항 == dst_id or 건물_강도항 == dst_id)	continue;	
												 																											
                      if (건물_도시시작 <= dst_id and dst_id < 건물_항구끝 
					  and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id
					  and (pk::get_troops(dst) < 16000 or pk::get_troops(dst) * 2 < pk::get_troops(src)))
																						  
                            {
		                    War_Zone++;
                            }

                       }

                  }

               } 
            

            return War_Zone;
        }

		/** 전투부대 파견 */

		bool PushWanderers(pk::building@ base)
		{
			// 명령 가능한 무장이 있는지 확인.
			auto person_list = pk::get_idle_person_list(base);
			if (person_list.count == 0) return false;

			// 파병할 인접 거접이 있는지 확인.
			int target = getUrgentBase1(base);
			if (target == -1) return false;

             pk::force@ force = pk::get_force(base.get_force_id());
             int force_id = base.get_force_id();

             pk::force@ enemy_force = pk::get_force(pk::get_building(target).get_force_id());

            // 플레이어 세력의 위임군단인 경우
            pk::district@ district = pk::get_district(base.get_district_id());		
			if (force.is_player() and pk::is_alive(district) and !pk::is_player_controlled(base))
            {	
			if (!district.attack) return false;
			if (district.policy == 군단방침_도시공략 and district.policy_target != pk::get_city_id(pk::get_building(target).pos)) return false;
			if (district.policy == 군단방침_세력공략 and district.policy_target != pk::get_building(target).get_force_id()) return false;		
            }		

            // 적국의 전력이 상당해서 아군도 전체적으로 준비가 좀 필요하냐?
			/** 내가 수정 0.7f -> 0.5f로 */
            if (5 < pk::get_city_list(enemy_force).count and preparation(force) < pk::get_city_list(force).count * 0.5f) return false; 

            pk::list<pk::person@> actors;
            actors.clear();				
            for (int i = 0; i < person_list.count; i++)
            {
            if (pk::is_unitize(person_list[i])) continue;
            if (pk::is_absent(person_list[i])) continue;
            if (person_list[i].order != -1) continue;				
            if (person_list[i].get_force_id() != base.get_force_id()) continue; 

            if (person_list[i].location != person_list[i].service) continue;
            if (person_list[i].action_done) continue;
            if (pk::is_absent(person_list[i])) continue;
            if (person_list[i].mibun == 신분_포로) continue;
            if (person_list[i].mibun == 신분_재야) continue;

            if (!pk::is_unitize(person_list[i]) and !pk::is_absent(person_list[i])
                and person_list[i].order == -1 and person_list[i].get_force_id() == base.get_force_id()
                and person_list[i].location == person_list[i].service and !person_list[i].action_done and !pk::is_absent(person_list[i])
                and (person_list[i].mibun == 신분_군주 or person_list[i].mibun == 신분_도독 or person_list[i].mibun == 신분_태수 or person_list[i].mibun == 신분_일반)) 
				
                actors.add(person_list[i]);
            }

       if (actors.count == 0 ) return false;
            	
         // 공성병기 출진시			
          if (siege_unit_attack(base, pk::get_building(target)))			
          {			
            // 공성에 특화된 장수 먼저
			actors.sort(function(a, b)
			{                
                // 공성 특기 우대
                bool a_skill = (pk::has_skill(a, 특기_공신) or pk::has_skill(a, 특기_공성) or pk::has_skill(a, 특기_사정));
                bool b_skill = (pk::has_skill(b, 특기_공신) or pk::has_skill(b, 특기_공성) or pk::has_skill(b, 특기_사정));
                if ( a_skill and !b_skill) return true;   
                if (!a_skill and  b_skill) return false;  
                // 기력회복 특기 우대
                bool a_energy = (pk::has_skill(a, 특기_주악) or pk::has_skill(a, 특기_시상) or pk::has_skill(a, 특기_노발));
                bool b_energy = (pk::has_skill(b, 특기_주악) or pk::has_skill(b, 특기_시상) or pk::has_skill(b, 특기_노발));
                if ( a_energy and !b_energy) return true;   
                if (!a_energy and  b_energy) return false;  
                // 병기 적성
                if (a.tekisei[병종_병기] != b.tekisei[병종_병기]) return (a.tekisei[병종_병기] > b.tekisei[병종_병기]);
                // 무장 능력
                return (a.stat[무장능력_무력] + a.stat[무장능력_통솔]) > (b.stat[무장능력_무력] + b.stat[무장능력_통솔]);
			});

            pk::person@ leader = pk::get_person(actors[0].get_id());
	//내가 수정
            if ((leader.tekisei[병종_병기] == 적성_C) and (int(leader.stat[무장능력_무력]) >80) and (int(leader.stat[무장능력_무력]) >80)) return false; 
           
            // 원군 병력 산정 : 기준 병력 초과분, 지휘가능병력 확인
            int reinforce_troops = pk::min(pk::get_command(leader), pk::max(1000 , pk::get_troops(base) - 10000));
			if (reinforce_troops < 4000 ) return false;			

            // 최적 무기 선택
            int ground_weapon_id = 병기_검;
            int water_weapon_id = 병기_주가;
            int unit_troops = reinforce_troops;
            
            // 육상 무기 선택
            get_siege_weapon(base, pk::get_building(target), leader, reinforce_troops, ground_weapon_id, unit_troops);

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
            int unit_food = int(pk::min( 0.3f * pk::get_food(base), 2.0f * unit_troops));

            if (pk::get_food(base) >= pk::get_troops(base) * 2.0f)
                unit_food = int(pk::min( 0.3f * pk::get_food(base), pk::min(float ( float(pk::get_food(base)) / float(pk::get_troops(base)) ) * unit_troops, 3.0f * unit_troops)));				
            if (unit_food < int(0.9f * unit_troops)) return false;   // 병량 부족
            if (pk::get_food(base) - unit_food < (pk::get_troops(base) - unit_troops) * 0.7f ) return false;   // 거점 병량 부족

            
            // 출진 명령

                // 출진 명령 정보 생성.
                pk::com_deploy_cmd_info cmd;
                @cmd.base = @base;
                cmd.type = 부대종류_전투;
                cmd.member[0] = leader.get_id();

            // 첫번째 부장 - 지력 높은 장수 
            pk::list<pk::person@> advisor_group;
            advisor_group.clear();				
            for (int j = 0; j < actors.count; j++)
            {
            if (actors[j].get_id() != leader.get_id() and pk::get_command(leader) > pk::get_command(actors[j]) + 3000)	
				
                advisor_group.add(actors[j]);
            }

            if (advisor_group.count > 0 ) 
            {		   
				advisor_group.sort(function(a, b)
				{                
				return (a.stat[무장능력_지력]) > (b.stat[무장능력_지력]);
				});
            	pk::person@ advisor = pk::get_person(advisor_group[0].get_id());


            	// 두번째 부장 - 무력 높은 장수 
            	pk::list<pk::person@> bodyguard_group;
                bodyguard_group.clear();				
            	for (int k = 0; k < advisor_group.count; k++)
            	{
            	if (advisor_group[k].get_id() != leader.get_id() and advisor_group[k].get_id() != advisor.get_id() and pk::get_command(leader) > pk::get_command(advisor_group[k]) + 3000)	
				
                bodyguard_group.add(advisor_group[k]);
            	}

       		     if (bodyguard_group.count > 0 )
	             {				 
				   bodyguard_group.sort(function(a, b)
				   {                
				   return (a.stat[무장능력_무력]) > (b.stat[무장능력_무력]);
				   });
				   pk::person@ bodyguard = pk::get_person(bodyguard_group[0].get_id());


				   if (actors.count > 5 and pk::is_alive(pk::get_person(cmd.member[0])) and pk::is_alive(advisor)
				   and (leader.mibun == 신분_군주 or leader.mibun == 신분_도독 or leader.mibun == 신분_태수) and pk::get_command(leader) > pk::get_command(advisor))
				   cmd.member[1] = advisor.get_id();

				   if (actors.count > 8 and pk::is_alive(pk::get_person(cmd.member[0])) and pk::is_alive(pk::get_person(cmd.member[1])) and pk::is_alive(bodyguard) 
				   and (leader.mibun == 신분_군주 or leader.mibun == 신분_도독 or leader.mibun == 신분_태수) and pk::get_command(leader) > pk::get_command(bodyguard))
				   cmd.member[2] = bodyguard.get_id();
				   
                 }
            }
			
                cmd.gold = (pk::get_gold(base) >= 1000) ? int(pk::min(1000.f, pk::get_gold(base) * 0.1f)) : 0;
                cmd.troops = pk::max(1, unit_troops);
                cmd.weapon_id[0] = ground_weapon_id;
                cmd.weapon_id[1] = water_weapon_id;
                cmd.weapon_amount[0] = (ground_weapon_id == 병기_충차 or ground_weapon_id == 병기_정란 or ground_weapon_id == 병기_투석 or ground_weapon_id == 병기_목수)? 1 : unit_troops;
                cmd.weapon_amount[1] = (water_weapon_id == 병기_주가)? 0 : 1;
                cmd.food = unit_food;

                cmd.order = 부대임무_정복;
                cmd.target_pos = pk::get_building(target).get_pos();  // 목표는 전투중인 거점

                string target_name = pk::u8decode(pk::get_name(pk::get_building(target)));
	            if (대사표시_설정) 
	            {
	              if (ground_weapon_id == 병기_충차 or ground_weapon_id == 병기_정란 or ground_weapon_id == 병기_투석 or ground_weapon_id == 병기_목수)		   
                  pk::say(pk::u8encode(pk::format("아군이 적의 도시 입구까지 다다른 것 같다!\n\x1b[2x{}\x1b[0x에 공성병기를 보내라!", target_name)), leader);
                else
                pk::say(pk::u8encode(pk::format("드디어 우리의 영토를 넓힐 기회다!\n\x1b[2x{}\x1b[0x을(를) 공격하라", target_name)), leader);																										  
                }
	   
                // 출진.
                int unit_id = pk::command(cmd);
                if (unit_id != -1)
	            {
	              if (ground_weapon_id == 병기_충차 or ground_weapon_id == 병기_정란 or ground_weapon_id == 병기_투석 or ground_weapon_id == 병기_목수)		   
				  pk::get_unit(unit_id).action_done = (!거점수송_원거리이동);
                else
                pk::get_unit(unit_id).action_done = true;																								  
                }					
            
            return true;
			
          }
		  
          // 공성병기 이외 전투병 출진시	 
          else
          {			
            // 통솔+무력 높은 순으로 정렬.
			actors.sort(function(a, b)
			{                
				return (a.stat[무장능력_무력] + a.stat[무장능력_통솔]) > (b.stat[무장능력_무력] + b.stat[무장능력_통솔]);
			});

            pk::person@ leader = pk::get_person(actors[0].get_id());

           
            // 원군 병력 산정 : 기준 병력 초과분, 지휘가능병력 확인
            int reinforce_troops = pk::min(pk::get_command(leader), pk::max(1000 , pk::get_troops(base) - 10000));
			if (reinforce_troops < 4000 ) return false;				

            // 최적 무기 선택
            int ground_weapon_id = 병기_검;
            int water_weapon_id = 병기_주가;
            int unit_troops = reinforce_troops;
            
            // 육상 무기 선택
            get_ground_weapon1(base, leader, reinforce_troops, ground_weapon_id, unit_troops);
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
            int unit_food = int(pk::min( 0.3f * pk::get_food(base), 2.0f * unit_troops));

            if (pk::get_food(base) >= pk::get_troops(base) * 2.0f)
                unit_food = int(pk::min( 0.3f * pk::get_food(base), pk::min(float ( float(pk::get_food(base)) / float(pk::get_troops(base)) ) * unit_troops, 3.0f * unit_troops)));				
            if (unit_food < int(0.9f * unit_troops)) return false;   // 병량 부족
            if (pk::get_food(base) - unit_food < (pk::get_troops(base) - unit_troops) * 0.7f ) return false;   // 거점 병량 부족

            
            // 출진 명령

                // 출진 명령 정보 생성.
                pk::com_deploy_cmd_info cmd;
                @cmd.base = @base;
                cmd.type = 부대종류_전투;
                cmd.member[0] = leader.get_id();

            // 첫번째 부장 - 지력 높은 장수 
            pk::list<pk::person@> advisor_group;
            advisor_group.clear();				
            for (int j = 0; j < actors.count; j++)
            {
            if (actors[j].get_id() != leader.get_id() and pk::get_command(leader) > pk::get_command(actors[j]) + 3000)	
				
                advisor_group.add(actors[j]);
            }

            if (advisor_group.count > 0 ) 
            {		   
				advisor_group.sort(function(a, b)
				{                
				return (a.stat[무장능력_지력]) > (b.stat[무장능력_지력]);
				});
            	pk::person@ advisor = pk::get_person(advisor_group[0].get_id());


            	// 두번째 부장 - 무력 높은 장수 
            	pk::list<pk::person@> bodyguard_group;
                bodyguard_group.clear();				
            	for (int k = 0; k < advisor_group.count; k++)
            	{
            	if (advisor_group[k].get_id() != leader.get_id() and advisor_group[k].get_id() != advisor.get_id() and pk::get_command(leader) > pk::get_command(advisor_group[k]) + 3000)	
				
                bodyguard_group.add(advisor_group[k]);
            	}

       		     if (bodyguard_group.count > 0 )
	             {				 
				   bodyguard_group.sort(function(a, b)
				   {                
				   return (a.stat[무장능력_무력]) > (b.stat[무장능력_무력]);
				   });
				   pk::person@ bodyguard = pk::get_person(bodyguard_group[0].get_id());


				   if (actors.count > 5 and pk::is_alive(pk::get_person(cmd.member[0])) and pk::is_alive(advisor)
				   and (leader.mibun == 신분_군주 or leader.mibun == 신분_도독 or leader.mibun == 신분_태수) and pk::get_command(leader) > pk::get_command(advisor))
				   cmd.member[1] = advisor.get_id();

				   if (actors.count > 8 and pk::is_alive(pk::get_person(cmd.member[0])) and pk::is_alive(pk::get_person(cmd.member[1])) and pk::is_alive(bodyguard) 
				   and (leader.mibun == 신분_군주 or leader.mibun == 신분_도독 or leader.mibun == 신분_태수) and pk::get_command(leader) > pk::get_command(bodyguard))
				   cmd.member[2] = bodyguard.get_id();
				   
                 }
            }
			
                cmd.gold = (pk::get_gold(base) >= 1000) ? int(pk::min(1000.f, pk::get_gold(base) * 0.1f)) : 0;
                cmd.troops = pk::max(1, unit_troops);
                cmd.weapon_id[0] = ground_weapon_id;
                cmd.weapon_id[1] = water_weapon_id;
                cmd.weapon_amount[0] = unit_troops;
                cmd.weapon_amount[1] = (water_weapon_id == 병기_주가)? 0 : 1;
                cmd.food = unit_food;

                cmd.order = 부대임무_정복;
                cmd.target_pos = pk::get_building(target).get_pos();  // 목표는 전투중인 거점

                string target_name = pk::u8decode(pk::get_name(pk::get_building(target)));
	if (대사표시_설정) 
                pk::say(pk::u8encode(pk::format("드디어 우리의 영토를 넓힐 기회다!\n\x1b[2x{}\x1b[0x을(를) 공격하라", target_name)), leader);																										  

                // 출진.
                int unit_id = pk::command(cmd);
                if (unit_id != -1)
                    pk::get_unit(unit_id).action_done = true;

            
            return true;
			
          }		  
			
        }
        
 
        
        //----------------------------------------------------------------------------------
        
        // 무기 선택 함수
        void get_ground_weapon1(pk::building@ base, pk::person@ leader, int troops_max, int &out weapon_sel, int &out troops_sel)
        {
            int troops_min = 4000;
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



        
		/** 출격 대상 도시 검색 */


        pk::building@ src_wd;
		int getUrgentBase1(pk::building@ src)
		{
			int best_dst = -1;
			int best_distance = 0;


            int src_id = src.get_id();
            pk::list<pk::building@> dst_list; 
            dst_list.clear();				
            @src_wd = @src;

            
            pk::force@ force = pk::get_force(src.get_force_id());
	pk::city@ city_a = pk::get_city(pk::get_city_id(src.pos));            
            
			// 파병 거점 검색

                for (int i = 0; i < 건물_거점끝; i++)
                {
                    pk::building@ dst = pk::get_building(i);
                    int dst_id = dst.get_id();
			int base2_troops = pk::get_troops(dst);

			if (건물_파양항 == dst_id or 건물_노릉항 == dst_id or 건물_서하항 == dst_id or 건물_하양항 == dst_id or 건물_해현항 == dst_id or 건물_강도항 == dst_id)	continue;	
								
            int max_distance = (dst_id >= 건물_도시끝)? 2 : 1;

                    // 도시거리
                    int city_dist = -1;
                    if (dst_id < 건물_도시끝 and src_id < 건물_도시끝)
                        city_dist = pk::get_city_distance(dst_id, src_id);
                    
                    // 거점거리
                    int base_dist = pk::get_building_distance(dst_id, src_id, src.get_force_id());
                    
            // 거리 조건 만족 시
            if ( (func_enemy_city_count(city_a, 1) >= 1 and ((0 <= base_dist and base_dist <= max_distance) or city_dist == 1)) 

	        or (pk::has_tech(force, 기교_난소행군) and func_enemy_city_count(city_a, 1) == 0 and ((src_id == 건물_천수 and dst_id == 건물_자동) or (src_id == 건물_자동 and (dst_id == 건물_영안 or dst_id == 건물_천수 or dst_id == 건물_강주)) or (src_id == 건물_강주 and (dst_id == 건물_자동 or dst_id == 건물_건녕)) or (src_id == 건물_영안 and (dst_id == 건물_자동 or dst_id == 건물_성도)) or (src_id == 건물_성도 and (dst_id == 건물_영안 or dst_id == 건물_한중)) or (src_id == 건물_한중 and (dst_id == 건물_성도 or dst_id == 건물_장안)) or (src_id == 건물_장안 and dst_id == 건물_상용) or (src_id == 건물_상용 and dst_id == 건물_장안) ) )  

            or (pk::has_tech(force, 기교_투석개발) and func_enemy_city_count(city_a, 1) == 0 and ((src_id == 건물_시상 and (dst_id == 건물_호림항 or dst_id == 건물_무호항)) or (src_id == 건물_여강 and (dst_id == 건물_호림항 or dst_id == 건물_무호항 or dst_id == 건물_곡아항)) or (src_id == 건물_수춘 and dst_id == 건물_곡아항)  ) ) )
            {

            auto person_list = pk::get_idle_person_list(src);



			// 3칸 이내 적 부대 수
			int enemy_units1 = 0;
			// 3칸 이내 적 병력 수
			int enemy_troops1 = 0;

			// 3칸 이내 적 부대 수
			int enemy_units3 = 0;
			// 3칸 이내 적 병력 수
			int enemy_troops3 = 0;

			int force_units1 = 0;
			int force_troops1 = 0;

			int force_units3 = 0;
			int force_troops3 = 0;

			int Usual_weapon_units3 = 0;
			int Usual_weapon_troops3 = 0;

			int Siege_weapon_units3 = 0;
			int Siege_weapon_troops3 = 0;

			auto range = pk::range(dst.get_pos(), 1, 10);
			for (int i = 0; i < int(range.length); i++)
			{
				auto unit = pk::get_unit(range[i]);
				if (pk::is_alive(unit))
				{
					int distance = pk::get_distance(dst.get_pos(), range[i]);
					if (pk::is_enemy(dst, unit))
					{
						if (distance <= 5)
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
					if (pk::is_enemy(dst, unit) and src.get_force_id() == unit.get_force_id() and unit.type == 부대종류_전투 and ( unit.weapon == 병기_창 or unit.weapon == 병기_극 or unit.weapon == 병기_노 or unit.weapon == 병기_군마 ) )
					{

						if (distance <= 9)
						{
							Usual_weapon_units3++;
                            Usual_weapon_troops3 += unit.troops;
						}
					}
					if (pk::is_enemy(dst, unit) and src.get_force_id() == unit.get_force_id() and unit.type == 부대종류_전투 and ( unit.weapon == 병기_충차 or unit.weapon == 병기_정란 or unit.weapon == 병기_투석 or unit.weapon == 병기_목수 ) )
					{

						if (distance <= 9)
						{
							Siege_weapon_units3++;
                            Siege_weapon_troops3 += unit.troops;
						}
					}

					else if (dst.get_force_id() == unit.get_force_id() and unit.type == 부대종류_전투)
					{
						if (distance <=5)
						{
							force_units1++;
							force_troops1 += unit.troops;
						}												
						if (distance <=10)
						{
							force_units3++;
							force_troops3 += unit.troops;
						}
					}

				}
			}





			// 3칸 이내 적 부대 수
			int src_enemy_units3 = 0;
			// 3칸 이내 적 병력 수
			int src_enemy_troops3 = 0;

			int src_force_units3 = 0;
			int src_force_troops3 = 0;

			auto range_src = pk::range(src.get_pos(), 1, 10);
			for (int i = 0; i < int(range_src.length); i++)
			{
				auto unit = pk::get_unit(range_src[i]);
				if (pk::is_alive(unit))
				{
					int distance = pk::get_distance(src.get_pos(), range_src[i]);
					if (pk::is_enemy(src, unit))
					{

						if (distance <= 10)
						{
							src_enemy_units3++;
							src_enemy_troops3 += unit.troops;
						}						
					}


					else if (src.get_force_id() == unit.get_force_id() and unit.type == 부대종류_전투)
					{
					    if (distance <= 10)
						{
							src_force_units3++;
							src_force_troops3 += unit.troops;
						}						
					}

				}
			}

         // 목적지외의 거리 사이에 적부대가 있으면 안됨. (거리10이 최대)
    int pos_dist = pk::min(pk::get_distance(src.pos, dst.pos), 10);			 
    if (enemy_around_distance(src, pos_dist)) continue;

         // 해당 거점에 너무 많은 부대를 이미 보냈다면 중지

    if (func_already(src, dst) >= 14) continue;

         // 해당 거점에 일반병기 13부대, 공성병기부대 5부대 이상씩 가있으면 중지
    if (Usual_weapon_units3 >= 14 and Siege_weapon_units3 >= 6) continue;		 

         // 적 거점이 압도적인 전력차로 밀리고 있을땐 굳이 안보낸다.
    if (((enemy_units1 - force_units1 >= 10 and force_units1 <= 1 and enemy_troops1 - (force_troops1 + base2_troops) >= 30000) or enemy_troops1 - (force_troops1 + base2_troops) >= 60000)
    and ((건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and Siege_weapon_units3 > 9) or (건물_관문시작 <= dst_id and dst_id < 건물_항구끝 and Siege_weapon_units3 > 6)))
    continue;
 
         // 적 거점에 공격 보낸다
			int a = pk::get_person(pk::get_kunshu_id(src)).character;
            int friendly_weight = countNeighborBase(dst);			
            int friendly_weight2 = countNeighborBase2(dst);				

                if (src_id != dst_id and src.get_force_id() != dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst) and dst_id < 건물_거점끝  and  pk::is_enemy(src, dst)
				and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id )
                {
         // 공성전				
                  if (siege_unit_attack(src, dst))
                       {																																				 
                           best_dst = dst_id;
                           dst_list.add(dst);  // 파병가능 거점리스트 추가
                       }
         // 통상적인 침공					   
                  else if (40000 + force_troops3 + pk::max((func_enemy_city_count(city_a, 1) - 1) * 10000 , 0) - (src_force_troops3 + enemy_troops3)  <= pk::get_troops(src) and (EnemyBase_troops(src) * 0.4f) + ((3 - a) * 7000) + force_troops3 - (Friendly_base(src) * 0.2f)  - (src_force_troops3 + enemy_troops3) <= pk::get_troops(src) )
                       {
						 if (person_list.count <= (pk::get_troops(src) - (pk::get_max_troops(src) * 0.1f)) / 6000.f)  continue;
	
                           best_dst = dst_id;
                           dst_list.add(dst);  // 파병가능 거점리스트 추가
                       }
					   
         // 병력 3배 이상 적거나 공격쪽 거점에는 4만 이상 있고, 수비측엔 1만 이하 병력 있는 적 거점에 공격 보낸다

                  else if (func_already (src, dst) <= 3 and enemy_units3 <= 3 and (( force_troops3 + pk::get_troops(dst) ) * 3 <= pk::get_troops(src) or (force_troops3 + pk::get_troops(dst) <= 10000 and 40000 + ( ( 3 - a ) * 5000 ) <= pk::get_troops(src))) 
				  and ((건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and friendly_weight == 0)
				  or (건물_관문시작 <= dst_id and dst_id < 건물_항구끝 and friendly_weight2 == 0 and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id)))
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
                bool siege_unit_attack_a = main.siege_unit_attack(main.src_wd, a);
                bool siege_unit_attack_b = main.siege_unit_attack(main.src_wd, b);
                if ( siege_unit_attack_a and !siege_unit_attack_b) return true;				
                if (!siege_unit_attack_a and  siege_unit_attack_b) return false;				
	
				
                    int build_dist_a = pk::get_building_distance(a.get_id(), main.src_wd.get_id(), main.src_wd.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.src_wd.get_id(), main.src_wd.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.src_wd.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.src_wd.pos);

                    if (build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);
                    
                    return (pk::get_troops(a) + (1000 * pos_dist_a) < pk::get_troops(b) + (1000 * pos_dist_b));
                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
		}


  //---------------------------------------------------------------------------------------
        // ***** 적거점 주변 적의 지원 거점 병력 수 ***** //
        // ***** 주변의 지원나올만한 항관의 병력수 ***** //		
        int countNeighborBase(pk::building@ src)
        {
            int weight = 0;
            int troops = 0;
            for (int i = 0; i < 건물_거점끝; i++)
			{
                pk::building@ dst = pk::get_building(i);
                int src_id = src.get_id();
                int dst_id = dst.get_id();
                
                if (src_id != dst_id and pk::is_neighbor_base(src_id, dst_id) and !pk::is_enemy(src, dst) and 건물_관문시작 <= dst_id and dst_id < 건물_항구끝)
                    troops += pk::get_troops(dst);
            }
            
            weight = int(troops / 2300);
            return weight;
        }	

        // ***** 주변의 지원나올만한 도시의 병력수 ***** //	
        int countNeighborBase2(pk::building@ src)
        {
            int weight = 0;
            int troops = 0;
            for (int i = 0; i < 건물_거점끝; i++)
			{
                pk::building@ dst = pk::get_building(i);
                int src_id = src.get_id();
                int dst_id = dst.get_id();
                
                if (src_id != dst_id and pk::is_neighbor_base(src_id, dst_id) and !pk::is_enemy(src, dst) and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝)
                    troops += pk::get_troops(dst);
            }
            
            weight = int(troops);
            return weight;
        }
  //---------------------------------------------------------------------------------------


         // 거리에 따른 인근 적대 도시 숫자 체크, masterpiecek님의 AI_도시물자수송.cpp﻿를 참조했습니다.

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


  //---------------------------------------------------------------------------------------


        // ***** 주변 적거점 병력 수 확인 ***** //
        int EnemyBase_troops(pk::building@ src)
        {

            int troops = 0;
            for (int i = 0; i < 건물_거점끝; i++)
			{
                pk::building@ dst = pk::get_building(i);
                int src_id = src.get_id();
                int dst_id = dst.get_id();
                
                if (src_id != dst_id and pk::is_neighbor_base(src_id, dst_id) and pk::is_enemy(src, dst))
                    troops += pk::get_troops(dst);
            }
            

            return troops;
        }


  //---------------------------------------------------------------------------------------


        // ***** 거점에서 공격 나가기전 다른 아군 거점 공격 당하는 지 ***** //
        bool front_base(pk::building@ building)
        {
            for (int f = 0; f < 건물_거점끝; f++)
			{
				
                pk::force@ force = pk::get_force(building.get_force_id());				
				if (pk::get_city_count(force) <= 1) return false;	
				
                    pk::building@ front_base = pk::get_building(f);
                int building_id = building.get_id();					
                int front_base_id = front_base.get_id();	
                    int city_dist = pk::get_city_distance(pk::get_city_id(building.pos), pk::get_city_id(front_base.pos));

			if (!pk::is_alive(front_base)) continue;
			if (building_id == front_base_id) continue;
			if (building.get_force_id() != front_base.get_force_id()) continue;
			if (city_dist > 2 and building.get_district_id() != front_base.get_district_id()) continue;
			
			int front_enemy_units3 = 0;
			int front_enemy_troops3 = 0;

			int front_force_units3 = 0;
			int front_force_troops3 = 0;

            // 적군검색범위
			pk::array<pk::point> front_range = pk::range(front_base.pos, 1, ((front_base.facility == 시설_도시) ? 11 : 11 ) );
			for (int i = 0; i < int(front_range.length); i++)
			{
                pk::point pos = front_range[i];
				pk::unit@ unit = pk::get_unit(pos);
				if (pk::is_alive(unit))
				{
					int distance = pk::get_distance(front_base.get_pos(), pos);
					if (pk::is_enemy(front_base, unit) and unit.type == 부대종류_전투 )
					{
						if (distance <= 10)
						{
							front_enemy_units3++;
							front_enemy_troops3 += unit.troops;
						}
					}
					else if (front_base.get_force_id() == unit.get_force_id() and unit.type == 부대종류_전투)
					{
                        if (distance <= 10)
						{
							front_force_units3++;
							front_force_troops3 += unit.troops;		
						}
					}
				}
			}
                int a = pk::get_person(pk::get_kunshu_id(building)).character;

      if (front_base_id < 건물_도시끝 and ((front_force_troops3 + pk::get_troops(front_base) + troops_already(front_base) + (( a - 1 ) * 6000) <= front_enemy_troops3)
	  or (pk::get_troops(front_base) + front_force_troops3 < 10000))) 	return true;
  
      if (front_base_id >= 건물_도시끝 and ((front_force_troops3 + pk::get_troops(front_base) + troops_already(front_base) + (Friendly_base(front_base) * 0.5f) <= front_enemy_troops3)
      or (pk::get_troops(front_base) + front_force_troops3 < 4000)))    return true;
		  
            }
            
	return false;
        }
	
	
  //---------------------------------------------------------------------------------------
	
	
         // 목표 거점으로 이미 출발한 지원군 병력 합산, masterpiecek님의 AI_도시물자수송.cpp?를 참조했습니다.																																			  
	 int troops_already(pk::building@ building)
		{
			int already = 0;
			for (int unit_id = 0; unit_id < 부대_끝; unit_id++)
			{
				pk::unit@ unit = pk::get_unit(unit_id);
			if (!pk::is_alive(unit)) continue;				
			if (building.get_force_id() == -1) continue;
			if (unit.get_force_id() == -1) continue;
			if (unit.get_force_id() != building.get_force_id()) continue;			
			if (unit.target != building.get_id()) continue;	

				already += unit.troops;
			}

			return already;
		}


        // ***** 주변 아군 거점 병력 수 확인 ***** //
        int Friendly_base(pk::building@ src)
        {
            int troops = 0;
            for (int i = 0; i < 건물_거점끝; i++)
			{
                pk::building@ dst = pk::get_building(i);
                int src_id = src.get_id();
                int dst_id = dst.get_id();
                
                if (src_id != dst_id and pk::is_neighbor_base(src_id, dst_id) and src.get_force_id() == dst.get_force_id() )
                    troops += pk::get_troops(dst);
            }
            
            return troops;
        }


        //---------------------------------------------------------------------------------------

        // ***** 적 부대의 아군 거점 근처 존재 여부 (2022.06. 일송정 추가)***** //
        bool no_enemy_around(pk::building@ base)
        {

			int enemy_units3 = 0;
			int enemy_troops3 = 0;

			auto range = pk::range(base.get_pos(), 1, 10 + (base.facility == 시설_도시 ? 1 : 0));
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

        // ***** 적이 아군 거점에 다가오는가? (항관이 있어서 바로 못오는 경우까지 감안)***** //
        bool enemy_approach_direct(pk::building@ base)
        {
                pk::array<pk::point> range = pk::range(base.pos, 1, 15);  // 거점 주변 검색
                for (int i = 0; i < int(range.length); i++)
                {
				auto unit_e = pk::get_unit(range[i]);
				if (pk::is_alive(unit_e) and pk::is_enemy(base, unit_e))
				{
			        int target = get_neighbor_enemy_base_direct(unit_e);
			        int target2 = get_neighbor_enemy_base_direct_2(unit_e);					
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
        // 적부대가 우리 거점 경계 범위 까지 올 수 있는 상황 (항관이 있어서 바로 못오는 경우까지 감안)
		int get_neighbor_enemy_base_direct(pk::unit@ unit)
        {
			int best_dst = -1;			
            pk::array<pk::point> arr_range = pk::get_movable_pos(unit);  // 이동가능좌표
            for (int j = 0; j < int(arr_range.length); j++)
            {
                pk::point pos = arr_range[j];				

                pk::array<pk::point> arr_t = pk::range(pos, 1, 2);   // 주변좌표

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


		int get_neighbor_enemy_base_direct_2(pk::unit@ unit)
        {
			    int best_dst = -1;				
                pk::array<pk::point> arr_tm = pk::range(unit.pos, 1, 2);   // 주변좌표		

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

 int preparation(pk::force@ force)
 {
    int count = 0;
    int force_id = force.get_id();
    int a = pk::get_person(pk::get_kunshu_id(force)).character;
    for (int i = 0; i < 건물_도시끝; i++)
    {
      auto base = pk::get_building(i);
      if (force_id == base.get_force_id() and pk::get_troops(base) >= 15000 + ( 4000 * ( 4 - a ) ) )
      count += 1;
     }
      return count;
 }


  //---------------------------------------------------------------------------------------
  //---------------------------------------------------------------------------------------


         // 이미 해당 거점으로 출진한 부대 숫자 체크, masterpiecek님의 AI_도시물자수송.cpp﻿를 참조했습니다.
		 // if (unit.weapon == 병기_충차 or unit.weapon == 병기_정란 or unit.weapon == 병기_투석 or unit.weapon == 병기_목수) continue;	 일단 삭제

	 int func_already(pk::building@ src, pk::building@ building)
		{
			int already = 0;
			for (int unit_id = 0; unit_id < 부대_끝; unit_id++)
			{
				pk::unit@ unit = pk::get_unit(unit_id);
                pk::building@ service = pk::get_building(pk::get_service(unit));	
				
			if (building.get_force_id() == -1) continue;
			if (unit.get_force_id() == -1) continue;
			if (unit.get_force_id() != src.get_force_id()) continue;
			if (unit.type != 부대종류_전투) continue;	
            if (unit.order != 부대임무_정복) continue;
            if (unit.target != building.get_id()) continue;		
            if (unit.troops	< 3000) continue;	
		
            if (service.get_id() != src.get_id()) continue;
			
				if ( pk::is_alive(unit) and unit.type == 부대종류_전투 and unit.get_force_id() != building.get_force_id() and unit.get_force_id() == src.get_force_id() and service.get_id() == src.get_id() and unit.target == building.get_id()  and  pk::is_enemy(unit, building) ) 

				already++;
			}

			return already;
		}

  //---------------------------------------------------------------------------------------
  //---------------------------------------------------------------------------------------

        // ***** 공성전 할 상황인지***** //
        bool siege_unit_attack(pk::building@ src, pk::building@ dst)
        {
            int src_id = src.get_id();
            int dst_id = dst.get_id();
			int base2_troops = pk::get_troops(dst);
            int max_distance = (dst_id >= 건물_도시끝)? 2 : 1;

			// 근접한 적 부대 수
			
			int enemy_units0 = 0;
			int enemy_troops0 = 0;			
			
			int enemy_units1 = 0;
			int enemy_troops1 = 0;

			int enemy_units2 = 0;
			int enemy_troops2 = 0;

			// 3칸 이내 적 부대 수
			int enemy_units3 = 0;

			// 3칸 이내 적 병력 수
			int enemy_troops3 = 0;

			int force_units7 = 0;
			int force_troops7 = 0;			

			int Siege_weapon_units3 = 0;
			int Siege_weapon_troops3 = 0;



			auto range = pk::range(dst.get_pos(), 1, 10);
			for (int i = 0; i < int(range.length); i++)
			{
				auto unit = pk::get_unit(range[i]);
				if (pk::is_alive(unit))
				{
                    int weapon_id = unit.weapon;
					int distance = pk::get_distance(dst.get_pos(), range[i]);
					if (pk::is_enemy(dst, unit) and src.get_force_id() == unit.get_force_id())
					{
						if (distance <= 1)
						{
							enemy_units0++;
							enemy_troops0 += unit.troops;

						}						
						if (distance <= 3)
						{
							enemy_units1++;
							enemy_troops1 += unit.troops;

						}
						if (distance <= 7)
						{
							enemy_units2++;
							enemy_troops2 += unit.troops;

						}						
						if (distance <= 10)
						{
							enemy_units3++;
							enemy_troops3 += unit.troops;
						}
					}

					if (pk::is_enemy(dst, unit) and src.get_force_id() == unit.get_force_id() and unit.type == 부대종류_전투 and ( unit.weapon == 병기_충차 or unit.weapon == 병기_정란 or unit.weapon == 병기_투석 or unit.weapon == 병기_목수 ) )
					{

						if (distance <= 9)
						{
							Siege_weapon_units3++;
                            Siege_weapon_troops3 += unit.troops;
						}
					}



					else if (dst.get_force_id() == unit.get_force_id() and unit.type == 부대종류_전투)
					{
                        if (distance <= 7)
						{
							force_units7++;
							force_troops7 += unit.troops;							
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
                    if ( (0 <= base_dist and base_dist <= max_distance) or city_dist == 1)
                    {
         // 출진하려는 거점의 병력이 공격 대상 거점을 제외한 인접한 적의 거점 병력 총합의 50% 이상은 되어야 함

if (src_id != dst_id and src.get_force_id() != dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst))
          {

   // 교전 중이면서 방어 부대 없는 도시에 병력 보낸다
                    
if (건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and pk::is_enemy(src, dst) and ((enemy_units1 >= 2 and force_units7 <= 1) or (enemy_units2 >= 6 and force_units7 <= 3) or (enemy_units1 >= 1 and enemy_troops2 >= 25000 and force_troops7 + base2_troops <= 23000)) and (func_already_siege(src, dst) <= 9 or Siege_weapon_units3 <= 9))
	            return true;




  // 교전 중이면서 정문 진입로가 확보된 관문에 병력 보낸다

if (건물_관문시작 <= dst_id and dst_id < 건물_관문끝 and pk::is_enemy(src, dst) and (enemy_units0 >= 1 or !close_combat(dst)) and enemy_units1 >= 2 and (enemy_units3 >= 4 or force_units7 <= 1) and (func_already_siege(src, dst) <= 6 or Siege_weapon_units3 <= 6))
	            return true;



  // 교전 중이면서 정문 진입로가 확보된 항구에 병력 보낸다

  if (건물_항구시작 <= dst_id and dst_id < 건물_항구끝 and pk::is_enemy(src, dst) and (enemy_units0 >= 1 or !close_combat(dst)) and enemy_units1 >= 2 and (enemy_units3 >= 4 or force_units7 <= 1) and enemy_units3 <= 11 and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id and Siege_weapon_units3 <= 4)
	            return true;

         }


                    }
	return false;
        }
		
  //---------------------------------------------------------------------------------------	
        // ***** 특정 거점에서 이미 해당 전투지역으로 보낸 공성병기 숫자***** //
		
	 int func_already_siege(pk::building@ src, pk::building@ building)
		{
			int already = 0;
			for (int unit_id = 0; unit_id < 부대_끝; unit_id++)
			{
				pk::unit@ unit = pk::get_unit(unit_id);
			if (building.get_force_id() == -1) continue;
			if (unit.get_force_id() == -1) continue;
			if (unit.get_force_id() != src.get_force_id()) continue;			
				if ( pk::is_alive(unit) and unit.type == 부대종류_전투 and (병기_충차 <= unit.weapon and unit.weapon <= 병기_목수) and unit.get_force_id() == src.get_force_id() and unit.get_force_id() != building.get_force_id() and unit.target == building.get_id()) 

				already++;
			}

			return already;
		}


        //----------------------------------------------------------------------------------
        
        // 무기 선택 함수
        void get_siege_weapon(pk::building@ base, pk::building@ dst, pk::person@ leader, int troops_max, int &out weapon_sel, int &out troops_sel)
        {
            int troops_min = 4000;
            int weapon_max = 0;
            int best_tekisei = 적성_C;
            
            weapon_sel = 병기_검;
            troops_sel = 0;
            


			// 근접한 단거리 공격 공성병기 적 부대 수

			int Siege_weapon_Short_units3 = 0;

			auto range = pk::range(dst.get_pos(), 1, 10);
			for (int i = 0; i < int(range.length); i++)
			{
				auto unit = pk::get_unit(range[i]);
				if (pk::is_alive(unit))
				{
                    int weapon_id = unit.weapon;
					int distance = pk::get_distance(dst.get_pos(), range[i]);

					if (pk::is_enemy(dst, unit) and base.get_force_id() == unit.get_force_id() and unit.type == 부대종류_전투 and ( unit.weapon == 병기_충차 or unit.weapon == 병기_목수 ) )
					{

						if (distance <= 10)
						{
							Siege_weapon_Short_units3++;
						}
					}



				}
			}


            // 항관에 단거리 공성공격부대가 2부대 이미 향하고 있으면 원거리 부대로 

                    int dst_id = dst.get_id();
                    int id_1 = 병기_정란;
                    int id_2 = 병기_투석;

            // 목적지가 항관인데 이미 단거리 공성병기가 2대 정도 향하고 있거나 이미 가 있으면 정란, 투석으로 보내라

                    if (건물_관문시작 <= dst_id and dst_id < 건물_항구끝 and ( Siege_weapon_Short_units3 >= 2 or func_already_Short(base, dst) >= 2 ))
                       {
                        id_1 = 병기_정란;
                        id_2 = 병기_투석;
                        }


            // 목적지가 항관인데 단거리 공성병기가 2대 미만 정도만이 향하고 있거나 이미 가 있으면 공성병기 아무나 보내라

                    else if (건물_관문시작 <= dst_id and dst_id < 건물_항구끝 and Siege_weapon_Short_units3 < 2 and func_already_Short(base, dst) < 2 )
                       {
                        id_1 = 병기_충차;
                        id_2 = 병기_목수;
                        }


            // 목적지가 도시면 공성병기 아무나 보내라

                    else if (건물_도시시작 <= dst_id and dst_id < 건물_도시끝)
                       {
                        id_1 = 병기_충차;
                        id_2 = 병기_목수;
                        }




            // 일반 출진

                // 1개 이상 보유한 무기 중 최고 적성 확인

                    int id = 병기_충차;               

                for (int id = id_1; id <= id_2; id++)
                {
                    int tekisei = leader.tekisei[pk::equipment_id_to_heishu(id)];
                    int weapon_t = pk::get_weapon_amount(base, id);
                    if (1 <= weapon_t and best_tekisei <= tekisei)
                        best_tekisei = tekisei;
                }

                // 최고 적성 이상의 병과 중 무기 가장 많은 병과 선택


                for (int id = id_1; id <= id_2; id++)
                {
                    int tekisei = leader.tekisei[pk::equipment_id_to_heishu(id)];
                    int weapon_t = pk::get_weapon_amount(base, id);
                    if (1 <= weapon_t and weapon_max <= weapon_t and best_tekisei <= tekisei)
                    {
                        best_tekisei = tekisei;
                        weapon_max = weapon_t;
                        weapon_sel = id;

                        troops_sel = troops_max;
                    
                    }
                }
           
            if (weapon_sel == 0)
            {
                troops_sel = troops_min;
            }
        }
        
        //----------------------------------------------------------------------------------
            // 공격 대상 거점으로 미리 출진한 단거리 공격 병기부대 숫자 체크, masterpiecek님의 AI_도시물자수송.cpp﻿를 참조했습니다.

	 int func_already_Short(pk::building@ src, pk::building@ building)
		{
			int already = 0;
			for (int unit_id = 0; unit_id < 부대_끝; unit_id++)
			{
				pk::unit@ unit = pk::get_unit(unit_id);
			if (building.get_force_id() == -1) continue;
			if (unit.get_force_id() == -1) continue;
			if (unit.get_force_id() != src.get_force_id()) continue;			
				if ( pk::is_alive(unit) and unit.type == 부대종류_전투 and (unit.weapon == 병기_충차 or unit.weapon == 병기_목수) and unit.get_force_id() == src.get_force_id() and unit.get_force_id() != building.get_force_id() and unit.target == building.get_id()) 

				already++;
			}

			return already;
		}

  //---------------------------------------------------------------------------------------

        // ***** 적 부대의 아군 거점 근처 존재 여부, 거리 변수(2024.04. 일송정 추가)***** //
        bool enemy_around_distance(pk::building@ base, int unit_distance)
        {

			int enemy_units3 = 0;
			int enemy_troops3 = 0;

			auto range = pk::range(base.get_pos(), 1, unit_distance);
			for (int i = 0; i < int(range.length); i++)
			{
				auto unit = pk::get_unit(range[i]);
				if (pk::is_alive(unit))
				{
					int distance = pk::get_distance(base.get_pos(), range[i]);
					if (pk::is_enemy(base, unit))
					{

						if (distance <= unit_distance)
						{
							enemy_units3++;
							enemy_troops3 += unit.troops;
						}
					}

				}
			}


	
		if (enemy_troops3 > 0 and enemy_units3 > 0)					
	            return true;

				
            
	return false;
        }

        //---------------------------------------------------------------------------------------
       		
		
	};

	Main main;
}