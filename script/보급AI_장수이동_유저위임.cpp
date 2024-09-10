/*
제작 by 일송정

본 스크립트는 기마책사님이 제작하신 거점원군.cpp와 기마책사님이 수정하신 거점철수.cpp의 상당 부분을 차용하고 있음을 알려드립니다. 
기마책사님께 감사드립니다.

*/

namespace 장수이동_유저위임utf8
{



	class Main
	{
		pk::func261_t@ prev_callback_;

		Main()
		{
			@prev_callback_ = cast<pk::func261_t@>(pk::get_func(261));
			pk::reset_func(261);
			pk::set_func(261, pk::func261_t(callback));
		}



		bool callback(pk::force@ force)
		{
			int force_id = force.get_id();

            // 플레이어 세력이면서 플레이어가 직접 조종하지 않는 지역, 이민족 세력은 제외.
            if (force.is_player() and pk::is_normal_force(force_id) and pk::get_elapsed_months() > 3)
			{
				for (int i = 건물_관문시작; i < 건물_거점끝; i++)
				{
				  auto base = pk::get_building(i);
                  pk::district@ district = pk::get_district(base.get_district_id());				

	              if (pk::is_alive(district) and !pk::is_player_controlled(base) and district.personnel)
		          {

                    if (base.get_force_id() == force_id and needRetreat(base))
                        PushRetreat(base);     //  관, 항구에 짱박힌 장수들 다시 도시로 불러들이기

                    if (base.get_force_id() == force_id and needDispatch(base))
                        PushDispatch(base);    //  도시가 위급하고, 항구에 구원 병력은 있는데, 장수가 없어 지원이 안나오는 경우, 항구와 관문에 장수 보내기

                    if (base.get_force_id() == force_id and needConvoy(base))
                        PushConvoy(base);      //  평시에 항구와 관문에 병사가 많이 쌓여 있어 병력 증발 위험시, 수송을 위한 항구와 관문에 장수 보내기 


                    if (base.get_force_id() == force_id and needGold(base))
                        PushGold(base);        //  평시에 항구와 관문에 금이 쌓여, 도시로의 수송을 위한 항구와 관문에 장수 보내기 

                    if (base.get_force_id() == force_id and needFood(base))
                        PushFood(base);        //  평시에 항구와 관문에 군량이 쌓여, 도시로의 수송을 위한 항구와 관문에 장수 보내기

                    if (base.get_force_id() == force_id and needEvac(base))
                        PushEvac(base);  // 위급 상황의 거점에 장수를 보내 병력,금, 군량 가지고 탈출시키도록 


                    if (base.get_force_id() == force_id and needConvoy1(base))
                        PushConvoy1(base);     //  포화 거점에 장수 보내기

		          }

				}
				
				for (int j = 0; j < 건물_거점끝; j++)
				{
				  auto base = pk::get_building(j);
                  pk::district@ district = pk::get_district(base.get_district_id());				

	              if (pk::is_alive(district) and !pk::is_player_controlled(base) and district.personnel)
		          {
					  
                    if (base.get_force_id() == force_id and needExodus(base))
                        PushExodus(base);     //  함락 직전 도시에서 장수들 탈출하기
		          }

				}				
				
			}

			// 이전 핸들러가 있다면 체인.
			if (prev_callback_ !is null)
				return prev_callback_(force);
			return false;
		}


        
        //----------------------------------------------------------------------------------
        //  관, 항구에 짱박힌 장수들 다시 도시로 불러들이기
        //----------------------------------------------------------------------------------


        /** 장수 수가 모자르는 도시들 (3명 이하) **/
        bool needRetreat(pk::building@ src)
		{

            if (!pk::is_alive(src)) return false;

			if (src.get_force_id() == -1) return false;

			pk::district@ district = pk::get_district(src.get_district_id());
			int district_id = district.get_id();


			// 플레이어 세력 중 플레이어가 조종하지 않는 구역 한정, 이민족 세력은 제외.
			if (!pk::is_player_controlled(district) and !pk::is_player_controlled(src) and pk::is_normal_force(district_id))
			{

            auto person_list = pk::get_idle_person_list(src);
			pk::city@ city_a = pk::get_city(pk::get_city_id(src.pos));
			
            if ( ( pk::get_troops(src) <= 4500 or src.hp <= 700 ) and pk::enemies_around(src) ) 
            return false;	

			// 3칸 이내 적 부대 수
			int enemy_units3 = 0;

			auto range = pk::range(src.get_pos(), 1, 7);
			for (int i = 0; i < int(range.length); i++)
			{
				auto unit = pk::get_unit(range[i]);
				if (pk::is_alive(unit))
				{
					int distance_s = pk::get_distance(src.get_pos(), range[i]);
					if (pk::is_enemy(src, unit))
					{
						if (distance_s <= 7)
						{
							enemy_units3++;

						}
					}

				}
			}

// 항관만 취급
        if (건물_도시시작 <= src.get_id() and src.get_id() < 건물_도시끝)
        return false;			
					
// 적 침입 없는 항관에는 장수 최대 1명만

        if (person_list.count >= 2 and 0 == enemy_units3 and 건물_관문시작 <= src.get_id() and src.get_id() < 건물_항구끝)
        return true;


// 적 침입 없는 항관의 경우, 내구도 손상이 크지 않으면 
// 세력의 장수수가 도시당 7명이 안되면 매월 1일에는 도시로 돌아와
        if (7.0f > float( pk::get_person_list(district, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반)).count / float ( pk::get_city_count(district) )))
        {
        if (person_list.count >= 1 and 0 == enemy_units3 and pk::get_day() == 1 and pk::get_max_hp(src) * 0.9f <= src.hp and 건물_관문시작 <= src.get_id() and src.get_id() < 건물_항구끝 )
        return true;			
        }	
		
// 세력의 장수수가 도시당 7명 이상이면 홀수달 1일에는 도시로 돌아와	
        else if (7.0f <= float( pk::get_person_list(district, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반)).count / float ( pk::get_city_count(district) )))
        {
        if (person_list.count >= 1 and 0 == enemy_units3 and (pk::get_month() == 1 or pk::get_month() == 3 or pk::get_month() == 5 or pk::get_month() == 7 or pk::get_month() == 9 or pk::get_month() == 11) and pk::get_day() == 1 and pk::get_max_hp(src) * 0.9f <= src.hp and 건물_관문시작 <= src.get_id() and src.get_id() < 건물_항구끝 )
        return true;			
        }	



// 적 침입 있는 항관에 병력 당 장수 숫자 많으면

        if ( ( person_list.count >= 5 or person_list.count - 1 >= float (pk::get_troops(src) / 10000.f) ) and 1 <= enemy_units3 and 건물_관문시작 <= src.get_id() and src.get_id() < 건물_항구끝 )
        return true;


       if ( person_list.count >= 6 and person_list.count >= pk::get_troops(src) / 4000.f and 0 == enemy_units3 and 건물_관문시작 <= src.get_id() and src.get_id() < 건물_항구끝)
        return true;			
			
			
            }        
            return false;
        }



        
        // ***** 무장 지원 명령 ***** //
        bool PushRetreat(pk::building@ src_base)
        {
            // 무장이 있는 인근 거점이 있는지 확인
			int target = getClosestPerson(src_base);
			if (target == -1) return false;
            
            // 지원가능 무장 소속거점
            pk::building@ dst_base = pk::get_building(target);

          
            // 미행동 무장리스트
			pk::district@ district = pk::get_district( src_base.get_district_id());
 
            auto person_list = pk::get_idle_person_list(src_base);
            if (person_list.count <  1  ) return false;   // 무장 부족
          
            // 능력 높은 순으로 정렬.
			person_list.sort(function(a, b)
			{
				if ((a.mibun <= 신분_일반 or b.mibun <= 신분_일반) and a.mibun != b.mibun)
					return a.mibun < b.mibun;					
				return (a.stat[무장능력_무력] + a.stat[무장능력_통솔] + a.stat[무장능력_지력] + a.stat[무장능력_정치] + a.stat[무장능력_매력]) > (b.stat[무장능력_무력] + b.stat[무장능력_통솔] + b.stat[무장능력_지력] + b.stat[무장능력_정치] + b.stat[무장능력_매력]);
			});
            
            // 소환할 무장수
            int max = pk::max( 1 , pk::min(2, person_list.count * 0.05) );
            
            // 소환 대상 무장
            pk::list<pk::person@> actors;
            actors.clear();					
            for (int i = 0; i < max; i++)
            {
            if (pk::is_unitize(person_list[i])) continue;
            if (pk::is_absent(person_list[i])) continue;
            if (person_list[i].order != -1) continue;				
            if (person_list[i].get_district_id() != src_base.get_district_id()) continue; 
            if (person_list[i].get_district_id() != dst_base.get_district_id()) continue; 
            if (person_list[i].location != person_list[i].service) continue;
            if (person_list[i].action_done) continue;
            if (pk::is_absent(person_list[i])) continue;
            if (person_list[i].mibun == 신분_포로) continue;
            if (person_list[i].mibun == 신분_재야) continue;

            if (!pk::is_unitize(person_list[i]) and !pk::is_absent(person_list[i])
                and person_list[i].order == -1 and person_list[i].get_district_id() == src_base.get_district_id() and person_list[i].get_district_id() == dst_base.get_district_id() 
                and person_list[i].location == person_list[i].service and !person_list[i].action_done and !pk::is_absent(person_list[i])
                and (person_list[i].mibun == 신분_군주 or person_list[i].mibun == 신분_도독 or person_list[i].mibun == 신분_태수 or person_list[i].mibun == 신분_일반)) 

                actors.add(person_list[i]);
            }

       if (actors.count == 0 ) return false;
            
            // 소환 명령
            pk::summon_cmd_info cmd_summon;
            @cmd_summon.base   = dst_base;
            cmd_summon.actors  = actors;
            pk::command(cmd_summon);
            
            return true;
        }

        /** 무장이 있는 가까운 아군 거점을 얻음. */
        int getClosestPerson(pk::building@ src)
		{
			int best_dst = -1;
			int best_distance = 0;
            
			// 거점까지 확인.
			for (int i = 0; i < 건물_도시끝; i++)
			{
				pk::building@ dst = pk::get_building(i);
                
				if (dst.get_id() != src.get_id() and dst.get_district_id() == src.get_district_id()  )
                {
                    int distance = pk::get_building_distance(dst.get_id(), src.get_id(), src.get_force_id());
                    
                    auto person_list = pk::get_idle_person_list(src);
                    auto person_list_dst = pk::get_idle_person_list(dst);

			pk::district@ district_s = pk::get_district(src.get_district_id());


            int src_id = src.get_id();
            int dst_id = dst.get_id();
                    
                    int max_distance = 2;
			if (!pk::is_player_controlled(district_s) and !pk::is_player_controlled(src) and ((0 <= distance and distance < best_distance and distance <= max_distance) or best_dst == -1))
			{

			pk::force@ force = pk::get_force(dst.get_force_id());

            int enemy_weight = countNeighborEnemyBase(src);
            pk::city@ city_a = pk::get_city(pk::get_city_id(dst.pos));						

         if ( distance <= 2 and i >= 건물_도시시작 and i < 건물_도시끝 and pk::is_alive(src) and pk::is_alive(dst)  and src_id != dst_id and src.get_district_id() == dst.get_district_id() )			
         {
            if (1 <= func_enemy_city_count(city_a, 1) and 건물_도시시작 <= dst.get_id() and dst.get_id() < 건물_도시끝 ) 
                        {
                            best_dst = i;
                            best_distance = distance;
                        }	

            else if (person_list_dst.count <= 15 and !pk::enemies_around(dst) and 건물_도시시작 <= dst.get_id() and dst.get_id() < 건물_도시끝 ) 
                        {
                            best_dst = i;
                            best_distance = distance;
                        }								

            else if (건물_도시시작 <= dst.get_id() and dst.get_id() < 건물_도시끝 ) 
                        {
                            best_dst = i;
                            best_distance = distance;
                        }								

          }		  
                    }
                }
			}
			return best_dst;
		}
        
         




        //----------------------------------------------------------------------------------
        //  도시가 위급하고, 항구에 구원 병력은 있는데, 장수가 없어 지원이 안나오는 경우, 항구와 관문에 장수 보내기 
        //----------------------------------------------------------------------------------


        /** 병력 있는 항구 찾기 **/
        bool needDispatch(pk::building@ base)
		{

            if (!pk::is_alive(base)) return false;

			if (base.get_force_id() == -1) return false;

			pk::district@ district = pk::get_district(base.get_district_id());
			int district_id = district.get_id();

			int base_troops = pk::get_troops(base);
			pk::force@ force = pk::get_force(base.get_force_id());			


	// 플레이어 조종 거점, 이민족 세력은 제외. 항구 관문 중 도시 1개만 있을땐 병력 2천 이상, 2개 이상일땐 1만3천 이상, 장수 없는 곳

			if (!pk::is_player_controlled(district) and !pk::is_player_controlled(base) and pk::is_normal_force(district_id) and 건물_관문시작 <= base.get_id() and base.get_id() < 건물_항구끝)
			{
            
            auto person_list = pk::get_idle_person_list(base);
            if (person_list.count + func_already(base) < 1 and ((pk::get_city_list(force).count <= 1 and 2000 <= base_troops) or (pk::get_city_list(force).count > 1 and 13000 <= base_troops)) and 건물_파양항 != base.get_id() and 건물_노릉항 != base.get_id() and 건물_서하항 != base.get_id() and 건물_하양항 != base.get_id() and 건물_해현항 != base.get_id() and 건물_강도항 != base.get_id()) 
                return true;
            }        
            return false;
        }
        
        // ***** 무장 지원 명령 ***** //
        bool PushDispatch(pk::building@ dst_base)
        {
            // 무장이 있는 인근 거점이 있는지 확인
			int target = getAdjacentPerson(dst_base);
			if (target == -1) return false;
            
            // 지원가능 무장 소속거점
            pk::building@ src_base = pk::get_building(target);
            
            // 미행동 무장리스트
			pk::district@ district = pk::get_district( src_base.get_district_id());
 
            auto person_list = pk::get_idle_person_list(src_base);
            if (person_list.count <  1  ) return false;   // 무장 부족
          
            // 통솔+무력 높은 순으로 정렬.
			person_list.sort(function(a, b)
			{
				if ((a.mibun <= 신분_일반 or b.mibun <= 신분_일반) and a.mibun != b.mibun)
					return a.mibun > b.mibun;				
				return (a.stat[무장능력_무력] + a.stat[무장능력_통솔]) > (b.stat[무장능력_무력] + b.stat[무장능력_통솔]);
			});
            
            // 소환할 무장수
            int max = pk::max( 1 , pk::min(3, person_list.count * 0.05) );
            
            // 소환 대상 무장
            pk::list<pk::person@> actors;
            actors.clear();				
            for (int i = 0; i < max; i++)
            {
            if (pk::is_unitize(person_list[i])) continue;
            if (pk::is_absent(person_list[i])) continue;
            if (person_list[i].order != -1) continue;					
            if (person_list[i].get_district_id() != src_base.get_district_id()) continue; 
            if (person_list[i].get_district_id() != dst_base.get_district_id()) continue; 
            if (person_list[i].location != person_list[i].service) continue;
            if (person_list[i].action_done) continue;
            if (pk::is_absent(person_list[i])) continue;
            if (person_list[i].mibun == 신분_포로) continue;
            if (person_list[i].mibun == 신분_재야) continue;
            if (person_list[i].mibun != 신분_일반) continue;				

            if (!pk::is_unitize(person_list[i]) and !pk::is_absent(person_list[i])
                and person_list[i].order == -1 and person_list[i].get_district_id() == src_base.get_district_id() and person_list[i].get_district_id() == dst_base.get_district_id() 
                and person_list[i].location == person_list[i].service and !person_list[i].action_done and !pk::is_absent(person_list[i])
                and person_list[i].mibun == 신분_일반) 
 			
                actors.add(person_list[i]);
            }

       if (actors.count == 0 ) return false;
      
            // 소환 명령
            pk::summon_cmd_info cmd_summon;
            @cmd_summon.base   = dst_base;
            cmd_summon.actors  = actors;
            pk::command(cmd_summon);
            
            return true;
        }

        /** 무장이 있는 가까운 아군 거점을 얻음. */
        int getAdjacentPerson(pk::building@ dst)
		{
			int best_src = -1;
			int best_distance = 0;

            
			// 거점까지 확인.
			for (int i = 0; i < 건물_도시끝; i++)
			{
				pk::building@ src = pk::get_building(i);
                
				if (dst.get_id() != src.get_id() and dst.get_district_id() == src.get_district_id()  )
                {
                    int distance = pk::get_building_distance(dst.get_id(), src.get_id(), src.get_force_id());
                    
                    auto person_list = pk::get_idle_person_list(src);

            int src_id = src.get_id();
            int dst_id = dst.get_id();

			pk::district@ district_s = pk::get_district(src.get_district_id());
			
                    int max_distance = 2;
			int base1_troops = pk::get_troops(src);


                    if (!pk::is_player_controlled(district_s) and !pk::is_player_controlled(src) and (0 <= distance and distance < best_distance and distance <= max_distance) or best_src == -1)
                    {



			// 근접한 적 부대 수
			int enemy_units1 = 0;
			// 3칸 이내 적 부대 수
			int enemy_units3 = 0;
			// 3칸 이내 적 병력 수
			int enemy_troops3 = 0;



			int force_units7 = 0;



			auto range = pk::range(src.get_pos(), 1, 7);
			for (int i = 0; i < int(range.length); i++)
			{
				auto unit = pk::get_unit(range[i]);
				if (pk::is_alive(unit))
				{
					int distance_s = pk::get_distance(src.get_pos(), range[i]);
					if (pk::is_enemy(src, unit))
					{
						if (distance_s <= 3)
						{
							enemy_units1++;
						}
						if (distance_s <= 7)
						{
							enemy_units3++;
							enemy_troops3 += unit.troops;
						}
					}


					else if (src.get_force_id() == unit.get_force_id() and unit.type == 부대종류_전투)
					{
                        if (distance_s <= 7)
						{
							force_units7++;
						}
					}

				}
			}





     // 적의 공격 받는 도시 중에서, 장수가 1명이라도 있고, 병력이 7900명 이하면 항구, 관문에 장수를 보내라

			pk::district@ district = pk::get_district(dst.get_district_id());
                    if ( distance <= 2)			
                        {
          if (!pk::is_player_controlled(src) and person_list.count > 0 and  base1_troops <= 7900 and  1 <= enemy_units3  and pk::is_alive(src) and pk::is_alive(dst)  and src_id != dst_id and src.get_district_id() == dst.get_district_id() and i < 건물_도시끝)
                        {
                            best_src = i;
                            best_distance = distance;

                        }
                        }
                    }
                }
			}
			return best_src;
		}
        
         










        //----------------------------------------------------------------------------------
        //  평시에 항구와 관문에 병사가 많이 쌓여 있어 병력 증발 위험시, 수송을 위한 항구와 관문에 장수 보내기 
        //----------------------------------------------------------------------------------


        /** 병력 있는 항구 찾기 **/
        bool needConvoy(pk::building@ base)
		{

            if (!pk::is_alive(base)) return false;

			if (base.get_force_id() == -1) return false;

			pk::district@ district = pk::get_district(base.get_district_id());
			int district_id = district.get_id();

			int base_troops = pk::get_troops(base);
            pk::city@ city_a = pk::get_city(pk::get_city_id(base.pos));


	// 플레이어 조종 거점, 이민족 세력은 제외. 항구 관문 중 후방은 병력 1만 3천 이상, 전방은 1만 8천 이상 중 장수 없는 곳

			if (!pk::is_player_controlled(district) and !pk::is_player_controlled(base) and pk::is_normal_force(district_id) and 건물_관문시작 <= base.get_id() and base.get_id() < 건물_항구끝)
			{
            
            auto person_list = pk::get_idle_person_list(base);
            int enemy_weight = countNeighborEnemyBase(base);

           if (person_list.count + func_already(base) < 1 and 13000 <= base_troops  and 0 == enemy_weight and 건물_파양항 != base.get_id() and 건물_노릉항 != base.get_id() and 건물_서하항 != base.get_id() and 건물_하양항 != base.get_id() and 건물_해현항 != base.get_id() and 건물_강도항 != base.get_id()) 
                return true;

           if (person_list.count + func_already(base) < 1 and 18000 <= base_troops  and 0 < enemy_weight and 건물_파양항 != base.get_id() and 건물_노릉항 != base.get_id() and 건물_서하항 != base.get_id() and 건물_하양항 != base.get_id() and 건물_해현항 != base.get_id() and 건물_강도항 != base.get_id()) 
                return true;

            }        
            return false;
        }
        
        // ***** 무장 지원 명령 ***** //
        bool PushConvoy(pk::building@ dst_base)
        {
            // 무장이 있는 인근 거점이 있는지 확인
			int target = getConvoyPerson(dst_base);
			if (target == -1) return false;
            
            // 지원가능 무장 소속거점
            pk::building@ src_base = pk::get_building(target);
            
            // 미행동 무장리스트
			pk::district@ district = pk::get_district( src_base.get_district_id());
 
            auto person_list = pk::get_idle_person_list(src_base);
            if (person_list.count <  1  ) return false;   // 무장 부족
          
            // 통솔+무력 낮은 순으로 정렬.
			person_list.sort(function(a, b)
			{
				if ((a.mibun <= 신분_일반 or b.mibun <= 신분_일반) and a.mibun != b.mibun)
					return a.mibun > b.mibun;				
				return (a.stat[무장능력_무력] + a.stat[무장능력_통솔]) < (b.stat[무장능력_무력] + b.stat[무장능력_통솔]);
			});
            
            // 소환할 무장수
            int max = pk::max( 1 , pk::min(1, person_list.count * 0.05) );
            
            // 소환 대상 무장
            pk::list<pk::person@> actors;
            actors.clear();				
            for (int i = 0; i < max; i++)
            {
            if (pk::is_unitize(person_list[i])) continue;
            if (pk::is_absent(person_list[i])) continue;
            if (person_list[i].order != -1) continue;					
            if (person_list[i].get_district_id() != src_base.get_district_id()) continue; 
            if (person_list[i].get_district_id() != dst_base.get_district_id()) continue; 
            if (person_list[i].location != person_list[i].service) continue;
            if (person_list[i].action_done) continue;
            if (pk::is_absent(person_list[i])) continue;
            if (person_list[i].mibun == 신분_포로) continue;
            if (person_list[i].mibun == 신분_재야) continue;
            if (person_list[i].mibun != 신분_일반) continue;				

            if (!pk::is_unitize(person_list[i]) and !pk::is_absent(person_list[i])
                and person_list[i].order == -1 and person_list[i].get_district_id() == src_base.get_district_id() and person_list[i].get_district_id() == dst_base.get_district_id() 
                and person_list[i].location == person_list[i].service and !person_list[i].action_done and !pk::is_absent(person_list[i])
                and person_list[i].mibun == 신분_일반) 
 			
                actors.add(person_list[i]);
            }

       if (actors.count == 0 ) return false;
	   
            // 소환 명령
            pk::summon_cmd_info cmd_summon;
            @cmd_summon.base   = dst_base;
            cmd_summon.actors  = actors;
            pk::command(cmd_summon);
            
            return true;
        }

        /** 무장이 있는 가까운 아군 거점을 얻음. */
        int getConvoyPerson(pk::building@ dst)
		{
			int best_src = -1;
			int best_distance = 0;

            
			// 거점까지 확인.
			for (int i = 0; i < 건물_도시끝; i++)
			{
				pk::building@ src = pk::get_building(i);
                
				if (dst.get_id() != src.get_id() and dst.get_district_id() == src.get_district_id()  )
                {
                    int distance = pk::get_building_distance(dst.get_id(), src.get_id(), src.get_force_id());
                    
                    auto person_list = pk::get_idle_person_list(src);

            int src_id = src.get_id();
            int dst_id = dst.get_id();

			pk::district@ district_s = pk::get_district(src.get_district_id());
			
                    int max_distance = 2;
			int base1_troops = pk::get_troops(src);


                   if (!pk::is_player_controlled(district_s) and !pk::is_player_controlled(src) and ((0 <= distance and distance < best_distance and distance <= max_distance) or best_src == -1 ) and func_already(dst) == 0 )
                    {


     // 장수가 3명이상 있고, 병력이 최대치의 50% 이하면 항구, 관문에 장수를 보내라
                   int src_count = pk::get_person_list(src, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반)).count;	 
			pk::district@ district = pk::get_district(dst.get_district_id());
                    if ( distance <= 2)					
                        {
                        if (person_list.count > 0 and src_count > 2 and  base1_troops <= pk::get_max_troops(src) * 0.5f and pk::is_alive(src) and pk::is_alive(dst) and src_id != dst_id and src.get_district_id() == dst.get_district_id() and i < 건물_도시끝)
                        {
                            best_src = i;
                            best_distance = distance;
                        }
                        }
                    }
                }
			}
			return best_src;
		}
        
         









        //----------------------------------------------------------------------------------
        //  평시에 항구와 관문에 금이 쌓여, 도시로의 수송을 위한 항구와 관문에 장수 보내기 
        //----------------------------------------------------------------------------------


        /** 병력 있는 항구 찾기 **/
        bool needGold(pk::building@ base)
		{

            if (!pk::is_alive(base)) return false;

			if (base.get_force_id() == -1) return false;

			pk::district@ district = pk::get_district(base.get_district_id());
			int district_id = district.get_id();

			int base_troops = pk::get_troops(base);
            pk::city@ city_a = pk::get_city(pk::get_city_id(base.pos));


	// 플레이어 조종 거점, 이민족 세력은 제외. 항구 관문 중 금 5천 이상 있는 곳

			if (!pk::is_player_controlled(district) and !pk::is_player_controlled(base) and pk::is_normal_force(district_id) and 건물_관문시작 <= base.get_id() and base.get_id() < 건물_항구끝)
			{
            
            auto person_list = pk::get_idle_person_list(base);
            int enemy_weight = countNeighborEnemyBase(base);

           if (person_list.count + func_already(base) < 1 and 5000 <= pk::get_gold(base) and 건물_파양항 != base.get_id() and 건물_노릉항 != base.get_id() and 건물_서하항 != base.get_id() and 건물_하양항 != base.get_id() and 건물_해현항 != base.get_id() and 건물_강도항 != base.get_id() ) 
                return true;


            }        
            return false;
        }
        
        // ***** 무장 지원 명령 ***** //
        bool PushGold(pk::building@ dst_base)
        {
            // 무장이 있는 인근 거점이 있는지 확인
			int target = getGoldPerson(dst_base);
			if (target == -1) return false;
            
            // 지원가능 무장 소속거점
            pk::building@ src_base = pk::get_building(target);
            
            // 미행동 무장리스트
			pk::district@ district = pk::get_district( src_base.get_district_id());
 
            auto person_list = pk::get_idle_person_list(src_base);
            if (person_list.count <  1  ) return false;   // 무장 부족
          
            // 통솔+무력 낮은 순으로 정렬.
			person_list.sort(function(a, b)
			{
				if ((a.mibun <= 신분_일반 or b.mibun <= 신분_일반) and a.mibun != b.mibun)
					return a.mibun > b.mibun;					
				return (a.stat[무장능력_무력] + a.stat[무장능력_통솔]) < (b.stat[무장능력_무력] + b.stat[무장능력_통솔]);
			});
            
            // 소환할 무장수
            int max = pk::max( 1 , pk::min(1, person_list.count * 0.05) );
            
            // 소환 대상 무장
            pk::list<pk::person@> actors;
            actors.clear();				
            for (int i = 0; i < max; i++)
            {
            if (pk::is_unitize(person_list[i])) continue;
            if (pk::is_absent(person_list[i])) continue;
            if (person_list[i].order != -1) continue;					
            if (person_list[i].get_district_id() != src_base.get_district_id()) continue; 
            if (person_list[i].get_district_id() != dst_base.get_district_id()) continue; 
            if (person_list[i].location != person_list[i].service) continue;
            if (person_list[i].action_done) continue;
            if (pk::is_absent(person_list[i])) continue;
            if (person_list[i].mibun == 신분_포로) continue;
            if (person_list[i].mibun == 신분_재야) continue;
            if (person_list[i].mibun != 신분_일반) continue;				

            if (!pk::is_unitize(person_list[i]) and !pk::is_absent(person_list[i])
                and person_list[i].order == -1 and person_list[i].get_district_id() == src_base.get_district_id() and person_list[i].get_district_id() == dst_base.get_district_id() 
                and person_list[i].location == person_list[i].service and !person_list[i].action_done and !pk::is_absent(person_list[i])
                and person_list[i].mibun == 신분_일반) 
 			
                actors.add(person_list[i]);
            }

       if (actors.count == 0 ) return false;
  
            // 소환 명령
            pk::summon_cmd_info cmd_summon;
            @cmd_summon.base   = dst_base;
            cmd_summon.actors  = actors;
            pk::command(cmd_summon);
            
            return true;
        }

        /** 무장이 있는 가까운 아군 거점을 얻음. */
        int getGoldPerson(pk::building@ dst)
		{
			int best_src = -1;
			int best_distance = 0;

            
			// 거점까지 확인.
			for (int i = 0; i < 건물_도시끝; i++)
			{
				pk::building@ src = pk::get_building(i);
                
				if (dst.get_id() != src.get_id() and dst.get_district_id() == src.get_district_id()  )
                {
                    int distance = pk::get_building_distance(dst.get_id(), src.get_id(), src.get_force_id());
                    
                    auto person_list = pk::get_idle_person_list(src);

            int src_id = src.get_id();
            int dst_id = dst.get_id();

			pk::district@ district_s = pk::get_district(src.get_district_id());
			
                    int max_distance = 2;
			int base1_troops = pk::get_troops(src);


                   if (!pk::is_player_controlled(district_s) and !pk::is_player_controlled(src) and ((0 <= distance and distance < best_distance and distance <= max_distance) or best_src == -1 ) and func_already(dst) == 0 )
                    {


     //  장수가 3명 이상 있고, 도시의 금이 1만1천 이하거나 항구 관문보다 금이 적거나 항구, 관문이 보유한도까지 2만 이하 남은 상태고 장수 보내려는 도시도 한도까지 여유 있으면 장수를 보내라
                    int src_count = pk::get_person_list(src, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반)).count;
			pk::district@ district = pk::get_district(dst.get_district_id());
                    if ( distance <= 2)				
                        {
   if (person_list.count > 0 and src_count > 2 and ( pk::get_gold(src) <= 11000 or pk::get_gold(src) <=  pk::get_gold(dst)  or ( 20000 >= pk::get_max_gold(dst) - pk::get_gold(dst) and 40000 <= pk::get_max_gold(src) - pk::get_gold(src) )) and pk::is_alive(src) and pk::is_alive(dst) and src_id != dst_id and src.get_district_id() == dst.get_district_id() and i < 건물_도시끝)
                        {
                            best_src = i;
                            best_distance = distance;
                        }
                        }
                    }
                }
			}
			return best_src;
		}
        
         











        //----------------------------------------------------------------------------------
        //  평시에 항구와 관문에 군량이 쌓여, 도시로의 수송을 위한 항구와 관문에 장수 보내기 
        //----------------------------------------------------------------------------------


        /** 병력 있는 항구 찾기 **/
        bool needFood(pk::building@ base)
		{

            if (!pk::is_alive(base)) return false;

			if (base.get_force_id() == -1) return false;

			pk::district@ district = pk::get_district(base.get_district_id());
			int district_id = district.get_id();

			int base_troops = pk::get_troops(base);
            pk::city@ city_a = pk::get_city(pk::get_city_id(base.pos));


	// 플레이어 조종 거점, 이민족 세력은 제외. 항구 관문 중 군량 5천 이상에 병력 대비 2.5배 이상 있는 곳으로 장수 보냄

			if (!pk::is_player_controlled(district) and !pk::is_player_controlled(base) and pk::is_normal_force(district_id) and 건물_관문시작 <= base.get_id() and base.get_id() < 건물_항구끝)
			{
            
            auto person_list = pk::get_idle_person_list(base);
            int enemy_weight = countNeighborEnemyBase(base);

           if (person_list.count + func_already(base) < 1 and base_troops * 2.5f <= pk::get_food(base) and 5000 <= pk::get_food(base) and 건물_파양항 != base.get_id() and 건물_노릉항 != base.get_id() and 건물_서하항 != base.get_id() and 건물_하양항 != base.get_id() and 건물_해현항 != base.get_id() and 건물_강도항 != base.get_id() ) 
                return true;


            }        
            return false;
        }
        
        // ***** 무장 지원 명령 ***** //
        bool PushFood(pk::building@ dst_base)
        {
            // 무장이 있는 인근 거점이 있는지 확인
			int target = getFoodPerson(dst_base);
			if (target == -1) return false;
            
            // 지원가능 무장 소속거점
            pk::building@ src_base = pk::get_building(target);
            
            // 미행동 무장리스트
			pk::district@ district = pk::get_district( src_base.get_district_id());
 
            auto person_list = pk::get_idle_person_list(src_base);
            if (person_list.count <  1  ) return false;   // 무장 부족
          
            // 통솔+무력 낮은 순으로 정렬.
			person_list.sort(function(a, b)
			{
				if ((a.mibun <= 신분_일반 or b.mibun <= 신분_일반) and a.mibun != b.mibun)
					return a.mibun > b.mibun;				
				return (a.stat[무장능력_무력] + a.stat[무장능력_통솔]) < (b.stat[무장능력_무력] + b.stat[무장능력_통솔]);
			});
            
            // 소환할 무장수
            int max = pk::max( 1 , pk::min(1, person_list.count * 0.05) );
            
            // 소환 대상 무장
            pk::list<pk::person@> actors;
            actors.clear();				
            for (int i = 0; i < max; i++)
            {
            if (pk::is_unitize(person_list[i])) continue;
            if (pk::is_absent(person_list[i])) continue;
            if (person_list[i].order != -1) continue;					
            if (person_list[i].get_district_id() != src_base.get_district_id()) continue; 
            if (person_list[i].get_district_id() != dst_base.get_district_id()) continue; 
            if (person_list[i].location != person_list[i].service) continue;
            if (person_list[i].action_done) continue;
            if (pk::is_absent(person_list[i])) continue;
            if (person_list[i].mibun == 신분_포로) continue;
            if (person_list[i].mibun == 신분_재야) continue;
            if (person_list[i].mibun != 신분_일반) continue;				

            if (!pk::is_unitize(person_list[i]) and !pk::is_absent(person_list[i])
                and person_list[i].order == -1 and person_list[i].get_district_id() == src_base.get_district_id() and person_list[i].get_district_id() == dst_base.get_district_id() 
                and person_list[i].location == person_list[i].service and !person_list[i].action_done and !pk::is_absent(person_list[i])
                and person_list[i].mibun == 신분_일반) 
 			
                actors.add(person_list[i]);
            }

       if (actors.count == 0 ) return false;
  
            // 소환 명령
            pk::summon_cmd_info cmd_summon;
            @cmd_summon.base   = dst_base;
            cmd_summon.actors  = actors;
            pk::command(cmd_summon);
            
            return true;
        }

        /** 무장이 있는 가까운 아군 거점을 얻음. */
        int getFoodPerson(pk::building@ dst)
		{
			int best_src = -1;
			int best_distance = 0;

            
			// 거점까지 확인.
			for (int i = 0; i < 건물_도시끝; i++)
			{
				pk::building@ src = pk::get_building(i);
                
				if (dst.get_id() != src.get_id() and dst.get_district_id() == src.get_district_id()  )
                {
                    int distance = pk::get_building_distance(dst.get_id(), src.get_id(), src.get_force_id());
                    
                    auto person_list = pk::get_idle_person_list(src);

            int src_id = src.get_id();
            int dst_id = dst.get_id();

			pk::district@ district_s = pk::get_district(src.get_district_id());
			
                    int max_distance = 2;
			int base1_troops = pk::get_troops(src);


                   if (!pk::is_player_controlled(district_s) and !pk::is_player_controlled(src) and ((0 <= distance and distance < best_distance and distance <= max_distance) or best_src == -1 ) and func_already(dst) == 0 )
                    {


     //  장수가 3명이상 있고, 군량이 3만 이하거나 병력 대비 0.8이하거나 항구, 관문 보다 군량이 적거나, 항구 관문에 군량이 병력대비 2.5배 이상이거나 도시의 군량이 3만 이하 혹은 병력대비 2.5 이하 혹은 항관의 병량이 한도치까지 20만 이하로 남았고 도시는 아직 여유있으면 항구, 관문에 장수를 보내라
                    int src_count = pk::get_person_list(src, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반)).count;
			pk::district@ district = pk::get_district(dst.get_district_id());
                    if ( distance <= 2)				
                        {
if (person_list.count > 0 and src_count > 2 and 10000 <= pk::get_food(dst) and pk::get_food(dst) >= pk::get_troops(dst) * 2.5f  and  pk::get_troops(src) * 2.5f  >= pk::get_food(src) and (pk::get_food(src) <= 30000 or pk::get_food(src) <= base1_troops * 0.8f or pk::get_food(src) <= pk::get_food(dst) or ( pk::get_max_food(dst) - pk::get_food(dst) <= 200000 and pk::get_max_food(src) - pk::get_food(src) >= 400000 )  ) and pk::is_alive(src) and pk::is_alive(dst) and src_id != dst_id and src.get_district_id() == dst.get_district_id() and i < 건물_도시끝)
                        {
                            best_src = i;
                            best_distance = distance;
                        }
                        }
                    }
                }
			}
			return best_src;
		}
		
		
		
		
		

        //----------------------------------------------------------------------------------
        //  위급 상황의 거점에 장수를 보내 병력,금, 군량 가지고 탈출시키도록 
        //----------------------------------------------------------------------------------


        /** 위급한 항구, 관문 찾기 **/
        bool needEvac(pk::building@ base)
		{

            if (!pk::is_alive(base)) return false;

			if (base.get_force_id() == -1) return false;

			pk::district@ district = pk::get_district(base.get_district_id());
			int district_id = district.get_id();

			int base_troops = pk::get_troops(base);
            pk::city@ city_a = pk::get_city(pk::get_city_id(base.pos));


	// 플레이어 조종 거점, 이민족 세력은 제외. 항구 관문 중 물자,병력 있는 위급거점으로 보냄

			if (!pk::is_player_controlled(district) and !pk::is_player_controlled(base) and pk::is_normal_force(district_id) and 건물_관문시작 <= base.get_id() and base.get_id() < 건물_항구끝)
			{
            
            auto person_list = pk::get_idle_person_list(base);
            int enemy_weight = countNeighborEnemyBase(base);

           if (person_list.count + func_already(base) < 1 and pk::enemies_around(base) and ( ( base.hp < 800 and ( 5000 <= base_troops or 4000 <= pk::get_gold(base) or 8000 <= pk::get_food(base) ) ) or ( base_troops <= 2500 and 450 <  base.hp and (4000 <= pk::get_gold(base) or 8000 <= pk::get_food(base) ) ) )  and 건물_파양항 != base.get_id() and 건물_노릉항 != base.get_id() and 건물_서하항 != base.get_id() and 건물_하양항 != base.get_id() and 건물_해현항 != base.get_id() and 건물_강도항 != base.get_id() ) 
                return true;


            }        
            return false;
        }
        
        // ***** 무장 지원 명령 ***** //
        bool PushEvac(pk::building@ dst_base)
        {
            // 무장이 있는 인근 거점이 있는지 확인
			int target = getEvac(dst_base);
			if (target == -1) return false;
            
            // 지원가능 무장 소속거점
            pk::building@ src_base = pk::get_building(target);
            
            // 미행동 무장리스트
			pk::district@ district = pk::get_district( src_base.get_district_id());
 
            auto person_list = pk::get_idle_person_list(src_base);
            if (person_list.count <  1  ) return false;   // 무장 부족
          
            // 통솔+무력 낮은 순으로 정렬.
			person_list.sort(function(a, b)
			{
				if ((a.mibun <= 신분_일반 or b.mibun <= 신분_일반) and a.mibun != b.mibun)
					return a.mibun > b.mibun;				
				return (a.stat[무장능력_무력] + a.stat[무장능력_통솔]) < (b.stat[무장능력_무력] + b.stat[무장능력_통솔]);
			});
            
            // 소환할 무장수
            int max = pk::max( 1 , pk::min(2, person_list.count * 0.05) );
            
            // 소환 대상 무장
            pk::list<pk::person@> actors;
            actors.clear();				
            for (int i = 0; i < max; i++)
            {
            if (pk::is_unitize(person_list[i])) continue;
            if (pk::is_absent(person_list[i])) continue;
            if (person_list[i].order != -1) continue;					
            if (person_list[i].get_district_id() != src_base.get_district_id()) continue; 
            if (person_list[i].get_district_id() != dst_base.get_district_id()) continue; 
            if (person_list[i].location != person_list[i].service) continue;
            if (person_list[i].action_done) continue;
            if (pk::is_absent(person_list[i])) continue;
            if (person_list[i].mibun == 신분_포로) continue;
            if (person_list[i].mibun == 신분_재야) continue;
            if (person_list[i].mibun != 신분_일반) continue;				

            if (!pk::is_unitize(person_list[i]) and !pk::is_absent(person_list[i])
                and person_list[i].order == -1 and person_list[i].get_district_id() == src_base.get_district_id() and person_list[i].get_district_id() == dst_base.get_district_id() 
                and person_list[i].location == person_list[i].service and !person_list[i].action_done and !pk::is_absent(person_list[i])
                and person_list[i].mibun == 신분_일반) 
 			
                actors.add(person_list[i]);
            }

       if (actors.count == 0 ) return false;
	
            // 소환 명령
            pk::summon_cmd_info cmd_summon;
            @cmd_summon.base   = dst_base;
            cmd_summon.actors  = actors;
            pk::command(cmd_summon);
            
            return true;
        }

        /** 무장이 있는 가까운 아군 거점을 얻음. */
        int getEvac(pk::building@ dst)
		{
			int best_src = -1;
			int best_distance = 0;

            
			// 거점까지 확인.
			for (int i = 0; i < 건물_도시끝; i++)
			{
				pk::building@ src = pk::get_building(i);
                
				if (dst.get_id() != src.get_id() and dst.get_district_id() == src.get_district_id()  )
                {
                    int distance = pk::get_building_distance(dst.get_id(), src.get_id(), src.get_force_id());
                    
                    auto person_list = pk::get_idle_person_list(src);

            int src_id = src.get_id();
            int dst_id = dst.get_id();

			pk::district@ district_s = pk::get_district(src.get_district_id());  
			
                    int max_distance = 2;
			int base1_troops = pk::get_troops(src);

														  


                   if (!pk::is_player_controlled(district_s) and !pk::is_player_controlled(src) and ((0 <= distance and distance < best_distance and distance <= max_distance) or best_src == -1 ) and func_already(dst) == 0 )
                    {


     // 장수가 1명이라도 있으면 항구, 관문에 장수를 보내라
	 
			pk::district@ district = pk::get_district(dst.get_district_id());
                    if ( distance <= 2)				
                        {
if (person_list.count > 0 and  pk::is_alive(src) and pk::is_alive(dst) and src_id != dst_id and src.get_district_id() == dst.get_district_id() and i < 건물_도시끝)
                        {
                            best_src = i;
                            best_distance = distance;
                        }
                        }
                    }
                }
			}
			return best_src;
		}		
        
         















        //----------------------------------------------------------------------------------
        //  포화 거점에 장수 보내기  
        //----------------------------------------------------------------------------------


        /** 병력 포화 거점 찾기 **/
        bool needConvoy1(pk::building@ base)
		{

            if (!pk::is_alive(base)) return false;

			if (base.get_force_id() == -1) return false;

			pk::district@ district = pk::get_district(base.get_district_id());
			int district_id = district.get_id();

			int base_troops = pk::get_troops(base);



	// 플레이어 조종 거점, 이민족 세력은 제외. 거점 병력 52% 이상, 장수가 3명 이하인 곳

			if (!pk::is_player_controlled(district) and !pk::is_player_controlled(base) and pk::is_normal_force(district_id) and base.get_id() < 건물_거점끝)
			{
            
            auto person_list = pk::get_idle_person_list(base);
            if (person_list.count + func_already(base) <= 3 and pk::get_max_troops(base) * 0.52f <= base_troops and 건물_파양항 != base.get_id() and 건물_노릉항 != base.get_id() and 건물_서하항 != base.get_id() and 건물_하양항 != base.get_id() and 건물_해현항 != base.get_id() and 건물_강도항 != base.get_id() ) 
                return true;
            }        
            return false;
        }
        
        // ***** 무장 지원 명령 ***** //
        bool PushConvoy1(pk::building@ dst_base)
        {
            // 무장이 있는 인근 거점이 있는지 확인
			int target = getConvoyPerson1(dst_base);
			if (target == -1) return false;
            
            // 지원가능 무장 소속거점
            pk::building@ src_base = pk::get_building(target);
            
            // 미행동 무장리스트
			pk::district@ district = pk::get_district( src_base.get_district_id());
 
            auto person_list = pk::get_idle_person_list(src_base);
            if (person_list.count <  1  ) return false;   // 무장 부족
          
            // 통솔+무력 낮은 순으로 정렬.
			person_list.sort(function(a, b)
			{
				if ((a.mibun <= 신분_일반 or b.mibun <= 신분_일반) and a.mibun != b.mibun)
					return a.mibun > b.mibun;				
				return (a.stat[무장능력_무력] + a.stat[무장능력_통솔]) < (b.stat[무장능력_무력] + b.stat[무장능력_통솔]);
			});
            
            // 소환할 무장수
            int max = pk::max( 1 , pk::min(1, person_list.count * 0.05) );
            
            // 소환 대상 무장
            pk::list<pk::person@> actors;
            actors.clear();				
            for (int i = 0; i < max; i++)
            {
            if (pk::is_unitize(person_list[i])) continue;
            if (pk::is_absent(person_list[i])) continue;
            if (person_list[i].order != -1) continue;					
            if (person_list[i].get_district_id() != src_base.get_district_id()) continue; 
            if (person_list[i].get_district_id() != dst_base.get_district_id()) continue; 
            if (person_list[i].location != person_list[i].service) continue;
            if (person_list[i].action_done) continue;
            if (pk::is_absent(person_list[i])) continue;
            if (person_list[i].mibun == 신분_포로) continue;
            if (person_list[i].mibun == 신분_재야) continue;

            if (!pk::is_unitize(person_list[i]) and !pk::is_absent(person_list[i])
                and person_list[i].order == -1 and person_list[i].get_district_id() == src_base.get_district_id() and person_list[i].get_district_id() == dst_base.get_district_id() 
                and person_list[i].location == person_list[i].service and !person_list[i].action_done and !pk::is_absent(person_list[i])
                and (person_list[i].mibun == 신분_군주 or person_list[i].mibun == 신분_도독 or person_list[i].mibun == 신분_태수 or person_list[i].mibun == 신분_일반)) 
 			
                actors.add(person_list[i]);
            }

       if (actors.count == 0 ) return false;
		 
            // 소환 명령
            pk::summon_cmd_info cmd_summon;
            @cmd_summon.base   = dst_base;
            cmd_summon.actors  = actors;
            pk::command(cmd_summon);
            
            return true;
        }

        /** 무장이 있는 가까운 아군 거점을 얻음. */
        int getConvoyPerson1(pk::building@ dst)
		{
			int best_src = -1;
			int best_distance = 0;

            
			// 거점까지 확인.
			for (int i = 0; i < 건물_도시끝; i++)
			{
				pk::building@ src = pk::get_building(i);
                
				if (dst.get_id() != src.get_id() and dst.get_district_id() == src.get_district_id()  )
                {
                    int distance = pk::get_building_distance(dst.get_id(), src.get_id(), src.get_force_id());
                    
                    auto person_list = pk::get_idle_person_list(src);

            int src_id = src.get_id();
            int dst_id = dst.get_id();

			pk::district@ district_s = pk::get_district(src.get_district_id());
			
                    int max_distance = 3;
			int base1_troops = pk::get_troops(src);
			int enemy_weight = countNeighborEnemyBase(src);


                   if (!pk::is_player_controlled(district_s) and !pk::is_player_controlled(src) and ((0 <= distance and distance < best_distance and distance <= max_distance) or best_src == -1))
                    {


     // 장수가 6명 이상, 병력이 최대치의 50% 이하면 장수를 보내라

			pk::district@ district = pk::get_district(dst.get_district_id());
                    if ( distance <= 3)				
                        {
                        if (person_list.count > 5 and  base1_troops <= pk::get_max_troops(src) * 0.50f and pk::is_alive(src) and pk::is_alive(dst) and src_id != dst_id and src.get_district_id() == dst.get_district_id() and enemy_weight == 0 )
                        {
                            best_src = i;
                            best_distance = distance;
                        }
                        }
                    }
                }
			}
			return best_src;
		}



   


   
        //----------------------------------------------------------------------------------
        //  함락 직전 거점에서 장수들 탈출하기
        //----------------------------------------------------------------------------------


        /** 근처 아군 도시들 **/
        bool needExodus(pk::building@ src)
		{

            if (!pk::is_alive(src)) return false;

			if (src.get_force_id() == -1) return false;

			pk::district@ district = pk::get_district(src.get_district_id());
			int district_id = district.get_id();



			// 플레이어 세력 중 플레이어가 조종하지 않는 구역 한정, 이민족 세력은 제외.
			if (!pk::is_player_controlled(district) and !pk::is_player_controlled(src) and pk::is_normal_force(district_id))
			{


			// 근처 아군 도시가 대상
            
            auto person_list = pk::get_idle_person_list(src);
			pk::city@ city_a = pk::get_city(pk::get_city_id(src.pos));
			
			
			// 3칸 이내 적 부대 수
			int enemy_units3 = 0;
			// 3칸 이내 적 병력 수
			int enemy_troops3 = 0;

			int force_units7 = 0;
			int force_troops7 = 0;			



			auto range = pk::range(src.get_pos(), 1, 7);
			for (int i = 0; i < int(range.length); i++)
			{
				auto unit = pk::get_unit(range[i]);
				if (pk::is_alive(unit))
				{
					int distance_s = pk::get_distance(src.get_pos(), range[i]);
					if (pk::is_enemy(src, unit))
					{
						if (distance_s <= 7)
						{
							enemy_units3++;
							enemy_troops3 += unit.troops;
						}
					}


					else if (src.get_force_id() == unit.get_force_id() and unit.type == 부대종류_전투)
					{
                        if (distance_s <= 7)
						{
							force_units7++;
							force_troops7 += unit.troops;							
						}
					}


				}
			}

            // 적의 공격 받는 도시 중에서, 장수가 5명 이상에, 병력이 태수 성격에 따라 3000명 안팎이면 장수를 내보내라, (항구, 관문의 경우에는 장수 2명 이상에, 2000명)


                    pk::person@ taishu = pk::get_person(pk::get_taishu_id(src));
    
                    if (건물_도시시작 <= src.get_id() and src.get_id() < 건물_도시끝 and pk::is_alive(taishu))			
                        {
                        int a = taishu.character;

                        if (person_list.count >= 5 and ((pk::get_troops(src) <= 3000 + ( ( 3 - a ) * 300 ) and ( force_troops7 + pk::get_troops(src)) * 2 <= enemy_troops3 and 1 <= enemy_units3) or (3000 <= enemy_troops3 and src.hp <= 450)))
                return true;


                        }


                    if (건물_관문시작 <= src.get_id() and src.get_id() < 건물_항구끝 and pk::is_alive(taishu))			
                        {
                        int a = taishu.character;

                        if (person_list.count >= 2 and ((pk::get_troops(src) <= 2000 + ( ( 3 - a ) * 300 ) and ( force_troops7 + pk::get_troops(src)) * 2 <= enemy_troops3 and 1 <= enemy_units3) or (3000 <= enemy_troops3 and src.hp <= 450)))
                return true;


                        }			
			
						
            }        
            return false;
        }



        
        // ***** 무장 지원 명령 ***** //
        bool PushExodus(pk::building@ src_base)
        {
            // 무장이 있는 인근 거점이 있는지 확인
			int target = getExodusPerson(src_base);
			if (target == -1) return false;
            
            // 지원가능 무장 소속거점
            pk::building@ dst_base = pk::get_building(target);
           
            // 미행동 무장리스트
			pk::district@ district = pk::get_district( src_base.get_district_id());
 
            auto person_list = pk::get_idle_person_list(src_base);
            if (person_list.count <  1  ) return false;   // 무장 부족
          
            // 능력 높은 순으로 정렬.
			person_list.sort(function(a, b)
			{
				if ((a.mibun <= 신분_일반 or b.mibun <= 신분_일반) and a.mibun != b.mibun)
					return a.mibun < b.mibun;				
				return (a.stat[무장능력_무력] + a.stat[무장능력_통솔] + a.stat[무장능력_지력] + a.stat[무장능력_정치] + a.stat[무장능력_매력]) > (b.stat[무장능력_무력] + b.stat[무장능력_통솔] + b.stat[무장능력_지력] + b.stat[무장능력_정치] + b.stat[무장능력_매력]);
			});
            
            // 소환할 무장수
            int max = pk::max( 1 , pk::max(1, person_list.count * 0.5) );

	    if (건물_도시시작 <= src_base.get_id() and src_base.get_id() < 건물_도시끝)
                max = pk::max( 1 , pk::max(1, person_list.count * 0.5) );

	    else if (건물_관문시작 <= src_base.get_id() and src_base.get_id() < 건물_항구끝)
                max = pk::max( 1 , person_list.count - 1 );

            
            // 소환 대상 무장
            pk::list<pk::person@> actors;
            actors.clear();					
            for (int i = 0; i < max; i++)
            {
            if (pk::is_unitize(person_list[i])) continue;
            if (pk::is_absent(person_list[i])) continue;
            if (person_list[i].order != -1) continue;				
            if (person_list[i].get_district_id() != src_base.get_district_id()) continue; 
            if (person_list[i].get_district_id() != dst_base.get_district_id()) continue; 
            if (person_list[i].location != person_list[i].service) continue;
            if (person_list[i].action_done) continue;
            if (pk::is_absent(person_list[i])) continue;
            if (person_list[i].mibun == 신분_포로) continue;
            if (person_list[i].mibun == 신분_재야) continue;

            if (!pk::is_unitize(person_list[i]) and !pk::is_absent(person_list[i])
                and person_list[i].order == -1 and person_list[i].get_district_id() == src_base.get_district_id() and person_list[i].get_district_id() == dst_base.get_district_id() 
                and person_list[i].location == person_list[i].service and !person_list[i].action_done and !pk::is_absent(person_list[i])
                and (person_list[i].mibun == 신분_군주 or person_list[i].mibun == 신분_도독 or person_list[i].mibun == 신분_태수 or person_list[i].mibun == 신분_일반)) 

                actors.add(person_list[i]);
            }

       if (actors.count == 0 ) return false;
  
            // 소환 명령
            pk::summon_cmd_info cmd_summon;
            @cmd_summon.base   = dst_base;
            cmd_summon.actors  = actors;
            pk::command(cmd_summon);
            
            return true;
        }

        /** 무장이 있는 가까운 아군 거점을 얻음. */
        int getExodusPerson(pk::building@ src)
		{
			int best_dst = -1;
			int best_distance = 0;
            
			// 거점까지 확인.
			for (int i = 0; i < 건물_거점끝; i++)
			{
				pk::building@ dst = pk::get_building(i);
                
				if (dst.get_id() != src.get_id() and dst.get_district_id() == src.get_district_id()  )
                {
                    int distance = pk::get_building_distance(dst.get_id(), src.get_id(), src.get_force_id());
                    
                    auto person_list = pk::get_idle_person_list(src);
                    auto person_list_dst = pk::get_idle_person_list(dst);

			pk::force@ force_s = pk::get_force(src.get_force_id());


            int src_id = src.get_id();
            int dst_id = dst.get_id();

            if (pk::get_city_list(force_s).count <= 1 and src_id < 건물_도시끝)
                return -1;      // 마지막 도시인 경우 철수 불가

			pk::district@ district_s = pk::get_district(src.get_district_id());
                 
            int max_distance = 2;
			if (!pk::is_player_controlled(district_s) and !pk::is_player_controlled(src) and ((0 <= distance and distance < best_distance and distance <= max_distance) or best_dst == -1))
			{


            // 적의 공격 받는 도시 중에서, 장수가 5명 이상에, 병력이 태수 성격에 따라 3000명 안팎이면 장수를 내보내라, (항구, 관문의 경우에는 장수 2명 이상에, 2000명)


                    pk::person@ taishu = pk::get_person(pk::get_taishu_id(src));
    
           if (distance <= 2 and pk::is_alive(taishu) and pk::is_alive(src) and pk::is_alive(dst)  and src_id != dst_id and src.get_district_id() == dst.get_district_id())			
           {
                        int a = taishu.character;

            if (!pk::enemies_around(dst) and 건물_도시시작 <= dst.get_id() and dst.get_id() < 건물_도시끝 ) 
                        {
                            best_dst = i;
                            best_distance = distance;
                        }


            }




                    }
                }
			}
			return best_dst;
		}
        
  


  
// 이미 해당거점으로 이동 결정한 장수 체크. masterpiecek님의 AI_도시물자수송.cpp﻿를 참조했습니다.

	 int func_already(pk::building@ building)
		{
			int already = 0;
			for (int person_id = 0; person_id < 무장_끝; person_id++)
			{
			pk::person@ person = pk::get_person(person_id);
			if (building.get_force_id() == -1) continue;
			if (person.get_force_id() == -1) continue;
			if (!pk::is_alive(person)) continue;

                        int order = person.order;

if ( pk::is_alive(person) and (order == 무장임무_이동 or order == 무장임무_소환) and person.get_force_id() == building.get_force_id() and person.target[0] == building.get_id() and (person.mibun == 신분_군주 or person.mibun == 신분_도독 or person.mibun == 신분_태수 or person.mibun == 신분_일반)) 

				already++;
			}

			return already;
		}
   
       






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



         //  거리에 따른 인근 적대 도시 숫자 체크, masterpiecek님의 AI_도시물자수송.cpp﻿를 참조했습니다.
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

	};

	Main main;
}