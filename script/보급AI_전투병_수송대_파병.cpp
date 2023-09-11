/*
제작 by 일송정

본 스크립트는 기마책사님이 제작하신 거점원군.cpp와 기마책사님이 수정하신 거점철수.cpp의 상당 부분을 차용하고 있음을 알려드립니다. 
기마책사님께 감사드립니다.

*/

namespace 전투병_수송대_파병
{

    //---------------------------------------------------------------------------------------
    // 유저 설정_기마책사님 자료 발췌
    
    const bool  거점수송_원거리이동  = true;     // 수송부대 이동 1회 추가 (추천기능 : 보너스이동으로 탈출)
    const bool  거점수송_일시도주설정 = false;     // 수송부대 출진순간 도주효과 일시적용 (추천기능 : 포위망 돌파가능)
    const int   거점수송_거점검색모드 = 1;       // 0: 도시만 검색하여 수송,  1: 도시+관문+항구 모두 검색하여 수송    

    const int  출동부대수_한도 = 3;

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

                    if (base.get_force_id() == force_id and needSupport(base))
                        func_redispatch(base);             //  여유 병력 있는 거점에서 위급한 교전 거점으로 지원군 파병


                    if (base.get_force_id() == force_id and needGP_PEXtroops(base))
                        PushGP_PEXtroops(base);                //    초극도로 포화된 항구 관문에서 보급대 보내기  (병력)

                    if (base.get_force_id() == force_id and needS_PEXtroops(base))
                        PushS_PEXtroops(base);                //  초극도로 포화된 도시에서 보급대 보내기  (병력)

                    if (base.get_force_id() == force_id and needPEXtroops(base))
                        PushPEXtroops(base);                //  평시 포화된 도시에서 보급대 보내기  (병력)

                    if (base.get_force_id() == force_id and needarmy(base))
                        Pusharmy(base);                    //  병력이 극소수인 거점으로 병력 보내기

                    if (base.get_force_id() == force_id and needPorttroops(base))
                        PushPorttroops(base);        //  평시 항구에서 도시로 보급대 보내기  (병력) 3천만 남기는 프로그램 대신

                    if (base.get_force_id() == force_id and needReversetroops(base))
                        PushReversetroops(base);       //  항구나 관문 병력이 도시보다 많을때 보급대 보내기  (병력) 

                    if (base.get_force_id() == force_id and need4thtroops(base))
                        Push4thtroops(base);        //  항구나 관문 병력이 적을때 도시에서 보급대 보내기  (병력) 


                    if (base.get_force_id() == force_id and needEMERtroops(base))
                        PushEMERtroops(base);        //  전시 관문, 항구에서 세력멸망 직전 도시로 보급대 보내기  (병력)

                    if (base.get_force_id() == force_id and needEMER1troops(base))
                        PushEMER1troops(base);       //  전시 관문, 항구에서 세력멸망 직전 도시로 지원군 파병

		}

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
                
                int max_count = pk::max(1, pk::min(출동부대수_한도, 11));
               
                bool cmd = false;
                while(push_count < max_count)
                {
                    push_count += 1;
                    cmd = (PushSupport(base) or cmd);  
                }

        }

        //----------------------------------------------------------------------------------
        //  여유 병력 있는 거점에서 위급한 교전 거점으로 지원군 파병
        //----------------------------------------------------------------------------------




		/** 병력 있는 거점 찾기 */

		bool needSupport(pk::building@ base)
		{
            if ( count_War_Zone(base) == 0 ) return false;			
			
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


	// 병력 7천명 이상 있고, 적 침공에 견딜 수 있는 관문, 항구에서 파병 보내라

			if ( 7000 <= base_troops and 건물_관문시작 <= base.get_id() and base.get_id() < 건물_항구끝 and enemy_troops1 * 2.0f <= base_troops and pk::get_city_list(force).count > 1  )
				return true;


	// 병력 8천명 이상 있고, 적 침공에 견딜 수 있는 도시에서 파병 보내라

			if ( 8000 <= base_troops and 건물_도시시작 <= base.get_id() and base.get_id() < 건물_도시끝 and enemy_troops1 * 2.0f <= base_troops and pk::get_city_list(force).count > 0  )
				return true;


            
			return false;
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
                    int base_dist = pk::get_building_distance(dst_id, src_id, src.get_force_id());
                    
																				   
					
                    // 거리 조건 만족 시 
             if ((0 <= base_dist and base_dist <= max_distance) or city_dist == 1)   
                  {
												          
                if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst))
                     {
																											
                      if (건물_도시시작 <= dst_id and dst_id < 건물_항구끝 and !no_enemy_around(dst) and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id)
																						  
                            {
		                    War_Zone++;
                            }

                       }

                  }

	
 
               } 
            

            return War_Zone;
        }




		/** 전투부대 파견 */

		bool PushSupport(pk::building@ base)
		{
			// 명령 가능한 무장이 있는지 확인.
			auto person_list = pk::get_idle_person_list(base);
			if (person_list.count == 0) return false;

			// 수송할 인접 거접이 있는지 확인.
			int target = getUrgentBase(base);
			if (target == -1) return false;

			if ( 450 > pk::get_building(target).hp) return false;

            // 대상거점이 관문/항구인 경우 노병 출진 우대
            cmd_archer = (건물_관문시작 <= base.get_id() and base.get_id() < 건물_항구끝);

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
                if (main.cmd_archer)    // 노병 우대 출진
                {
                    if (a.tekisei[병종_노병] != b.tekisei[병종_노병]) return (a.tekisei[병종_노병] > b.tekisei[병종_노병]);
                    
                    return (a.stat[무장능력_무력] + a.stat[무장능력_통솔]) > (b.stat[무장능력_무력] + b.stat[무장능력_통솔]);
                }
                
				return (a.stat[무장능력_무력] + a.stat[무장능력_통솔]) > (b.stat[무장능력_무력] + b.stat[무장능력_통솔]);
			});
            pk::person@ leader = pk::get_person(actors[0].get_id());
            
            // 원군 병력 산정 : 기준 병력 초과분, 지휘가능병력 확인
            int reinforce_troops = pk::min(pk::get_command(leader), pk::max(int (pk::get_troops(base) * 0.35f) , pk::get_troops(base) - 10000));
			if (reinforce_troops < 4000 ) return false;

            // 최적 무기 선택
            int ground_weapon_id = 병기_검;
            int water_weapon_id = 병기_주가;
            int unit_troops = reinforce_troops;
            
            // 육상 무기 선택
            get_ground_weapon(base, leader, reinforce_troops, ground_weapon_id, unit_troops);
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
            int unit_food = int(pk::min( 0.3f * pk::get_food(base), 2.0f * unit_troops));
            if (pk::get_food(base) <= pk::get_troops(base) * 1.5f and 건물_도시시작 <= target and target < 건물_도시끝 ) 
                unit_food = int(pk::min( 0.3f * pk::get_food(base), 1.5f * unit_troops));	
            if (pk::get_food(base) <= pk::get_troops(base) * 1.5f and 건물_관문시작 <= target and target < 건물_항구끝 ) 
                unit_food = int(pk::min( 0.3f * pk::get_food(base), 1.2f * unit_troops));			
            if (unit_food < int(0.9f * unit_troops)) return false;   // 병량 부족
            if (pk::get_food(base) - unit_food < (pk::get_troops(base) - unit_troops) * 0.7f ) return false;   // 거점 병량 부족
            
            // 출진 명령

                // 출진 명령 정보 생성.
                pk::com_deploy_cmd_info cmd;
                @cmd.base = @base;
                cmd.type = 부대종류_전투;
                cmd.member[0] = leader.get_id();
                cmd.gold = (pk::get_gold(base) >= 1000) ? int(pk::min(1000.f, pk::get_gold(base) * 0.1f)) : 0;
                cmd.troops = pk::max(1, unit_troops);
                cmd.weapon_id[0] = ground_weapon_id;
                cmd.weapon_id[1] = water_weapon_id;
                cmd.weapon_amount[0] = unit_troops;
                cmd.weapon_amount[1] = (water_weapon_id == 병기_주가)? 0 : 1;
                cmd.food = unit_food;

                cmd.order = 부대임무_공격;
                cmd.target_pos = pk::get_building(target).get_pos();  // 목표는 전투중인 거점

	if (대사표시_설정) 
                pk::say(pk::u8encode("아군 거점에 적이 많으니\n전투병으로 참전하겠다!"), leader);																											  

                // 출진.
                int unit_id = pk::command(cmd);
                if (unit_id != -1)
                    pk::get_unit(unit_id).action_done = true;

            
            return true;
        }
        
        // 노병우대 출진여부
        bool cmd_archer = false;    
        
        //----------------------------------------------------------------------------------
        
        // 무기 선택 함수
        void get_ground_weapon(pk::building@ base, pk::person@ leader, int troops_max, int &out weapon_sel, int &out troops_sel)
        {
            int troops_min = 2200;
            int weapon_max = 0;
            int best_tekisei = 적성_C;
            
            weapon_sel = 병기_검;
            troops_sel = 0;
            
            // 노병 우대 출진
            if (cmd_archer)
            {
                int tekisei = leader.tekisei[pk::equipment_id_to_heishu(병종_노병)];
                int weapon = pk::get_weapon_amount(base, 병기_노);
                if (troops_min <= weapon and 적성_B <= tekisei)
                {
                    weapon_sel = 병기_노;
                    troops_sel = pk::min(weapon, troops_max);
                }
            }
            // 일반 출진
            else    
            {
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
            }
            
            if (weapon_sel == 0)
            {
                troops_sel = troops_min;
            }
        }
        
        //----------------------------------------------------------------------------------



        
		/** 가장 가깝고 위기에 빠진 아군 도시에 지원군 보냄 */


        pk::building@ src_k;
		int getUrgentBase(pk::building@ src)
		{
			int best_dst = -1;
			int best_distance = 0;


            int src_id = src.get_id();
            pk::list<pk::building@> dst_list; 
            @src_k = @src;




            int search_base = 건물_도시끝;
            if      (거점수송_거점검색모드 == 0) search_base = 건물_도시끝;
            else if (거점수송_거점검색모드 == 1) search_base = 건물_거점끝;
            
            pk::force@ force = pk::get_force(src.get_force_id());
            
            
			// 수송 거점 검색

                for (int i = 0; i < search_base; i++)
                {
                    pk::building@ dst = pk::get_building(i);
                    int dst_id = dst.get_id();
			int base2_troops = pk::get_troops(dst);


            int max_distance = (dst_id >= 건물_도시끝)? 2 : 1;





			// 근접한 적 부대 수
			int enemy_units1 = 0;
			int enemy_troops1 = 0;


			int enemy_units2 = 0;
			int enemy_troops2 = 0;

			// 3칸 이내 적 부대 수
			int enemy_units3 = 0;
			// 3칸 이내 적 병력 수
			int enemy_troops3 = 0;

			int force_units1 = 0;
			int force_troops1 = 0;

			int force_units7 = 0;
			int force_troops3 = 0;


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


					else if (dst.get_force_id() == unit.get_force_id() and unit.type == 부대종류_전투)
					{
                                                if (distance <= 3)
						{
							force_units1++;
							force_troops1 += unit.troops;
						}						
                                                if (distance <= 7)
						{
							force_units7++;
							force_troops3 += unit.troops;
						}
					}


					else
					{
					}
				}
			}







			// 근접한 적 부대 수
			int src_enemy_units1 = 0;
			int src_enemy_troops1 = 0;


			int src_enemy_units2 = 0;
			int src_enemy_troops2 = 0;

			// 3칸 이내 적 부대 수
			int src_enemy_units3 = 0;
			// 3칸 이내 적 병력 수
			int src_enemy_troops3 = 0;



			int src_force_units7 = 0;
			int src_force_troops3 = 0;

                pk::person@ Home_taishu = pk::get_person(pk::get_taishu_id(src));	

			auto range_src = pk::range(src.get_pos(), 1, 10);
			for (int i = 0; i < int(range_src.length); i++)
			{
				auto unit = pk::get_unit(range_src[i]);
				if (pk::is_alive(unit))
				{
					int distance = pk::get_distance(src.get_pos(), range_src[i]);
					if (pk::is_enemy(src, unit))
					{
						if (distance <= 3)
						{
							src_enemy_units1++;
							src_enemy_troops1 += unit.troops;

						}
						if (distance <= 7)
						{
							src_enemy_units2++;
							src_enemy_troops2 += unit.troops;
						}
						if (distance <= 10)
						{
							src_enemy_units3++;
							src_enemy_troops3 += unit.troops;
						}						
					}


					else if (src.get_force_id() == unit.get_force_id() and unit.type == 부대종류_전투)
					{
                        if (distance <= 5)
						{
							src_force_units7++;
							src_force_troops3 += unit.troops;
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

                    int enemy_weight_src = countNeighborEnemyBase(src);

                        pk::city@ city_s = pk::get_city(pk::get_city_id(src.pos));	
                    
                    // 거리 조건 만족 시
                    if ((0 <= base_dist and base_dist <= max_distance) or city_dist == 1)
                    {

		/** 적의 거점으로부터 떨어진 후방거점들 */

if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst) and pk::is_alive(Home_taishu))
       {

		    int a = Home_taishu.character;

// 후방 도시에서 7900명 이하거나 1.0배의 적 공격 받는 도시에 병력 보낸다
                    
if (건물_도시시작 <= src_id and src_id < 건물_도시끝 and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and ((base2_troops + force_troops1 <= 7900 and 0 < enemy_units1) or ((base2_troops + force_troops3 + troops_already(dst)) * 1.0f < enemy_troops3)) and enemy_weight_src == 0 and func_enemy_city_count(city_s, 1) == 0 and 3 >= battle_unit_check(src, dst) and 20000 + (4000 * ( 3 - a )) < pk::get_troops(src))
                       {
                           best_dst = dst_id;
                           dst_list.add(dst);  // 수송가능 거점리스트 추가
                        }



// 후방 항관에서 7900명 이하거나 1.0배의 적 공격 받는 도시에 병력 보낸다
                    
if (건물_관문시작 <= src_id and src_id < 건물_항구끝 and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and ((base2_troops + force_troops1 <= 7900 and 0 < enemy_units1) or ((base2_troops + force_troops3 + troops_already(dst)) * 1.0f < enemy_troops3)) and enemy_weight_src == 0 and func_enemy_city_count(city_s, 1) == 0 and 3 >= battle_unit_check(src, dst) )
                       {
                           best_dst = dst_id;
                           dst_list.add(dst);  // 수송가능 거점리스트 추가
                        }







// 후방 도시에서 6900명 이하거나 1.0배의 적 공격 받는관문에 병력 보낸다

  else if (건물_도시시작 <= src_id and src_id < 건물_도시끝 and 건물_관문시작 <= dst_id and dst_id < 건물_관문끝 and ((base2_troops + force_troops1 <= 6900 and 0 < enemy_units1) or ((base2_troops + force_troops1 + troops_already(dst)) * 1.0f < enemy_troops1)) and enemy_weight_src == 0 and func_enemy_city_count(city_s, 1) == 0 and 3 >= battle_unit_check(src, dst) )
                       {
                           best_dst = dst_id;
                           dst_list.add(dst);  // 수송가능 거점리스트 추가
                       }



// 후방 항관에서 6900명 이하거나 1.0배의 적 공격 받는관문에 병력 보낸다

  else if (건물_관문시작 <= src_id and src_id < 건물_항구끝 and 건물_관문시작 <= dst_id and dst_id < 건물_관문끝 and ((base2_troops + force_troops1 <= 6900 and 0 < enemy_units1) or ((base2_troops + force_troops3 + troops_already(dst)) * 1.0f < enemy_troops3)) and enemy_weight_src == 0 and func_enemy_city_count(city_s, 1) == 0 and 3 >= battle_unit_check(src, dst) )
                       {
                           best_dst = dst_id;
                           dst_list.add(dst);  // 수송가능 거점리스트 추가
                       }







// 후방 도시에서 6900명 이하거나 1.0배의 적 공격 받는 항구에 병력 보낸다

   else if (건물_도시시작 <= src_id and src_id < 건물_도시끝 and 건물_항구시작 <= dst_id and dst_id < 건물_항구끝 and ((base2_troops + force_troops1 <= 6900 and 0 < enemy_units1) or ((base2_troops + force_troops1 + troops_already(dst)) * 1.0f < enemy_troops1)) and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id and enemy_weight_src == 0 and func_enemy_city_count(city_s, 1) == 0 and 3 >= battle_unit_check(src, dst) )
                       {
                           best_dst = dst_id;
                           dst_list.add(dst);  // 수송가능 거점리스트 추가
                       }



// 후방 항관에서 6900명 이하거나 1.0배의 적 공격 받는 항구에 병력 보낸다

   else if (건물_관문시작 <= src_id and src_id < 건물_항구끝 and 건물_항구시작 <= dst_id and dst_id < 건물_항구끝 and ((base2_troops + force_troops1 <= 6900 and 0 < enemy_units1) or ((base2_troops + force_troops3 + troops_already(dst)) * 1.0f < enemy_troops3)) and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id and enemy_weight_src == 0 and func_enemy_city_count(city_s, 1) == 0 and 3 >= battle_unit_check(src, dst) )
                       {
                           best_dst = dst_id;
                           dst_list.add(dst);  // 수송가능 거점리스트 추가
                       }









		/** 전방거점이지만 적의 거점과 직접적으로 닿아 있진 않은 거점들 */

// 전방 도시 중 바로 적 거점과 인접하지 않은 도시에서 7900명 이하거나 1.0배의 적 공격 받는 도시에 병력 보낸다
                    
if (건물_도시시작 <= src_id and src_id < 건물_도시끝 and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and ((base2_troops + force_troops1 <= 7900 and 0 < enemy_units1) or ((base2_troops + force_troops3 + troops_already(dst)) * 1.0f < enemy_troops3)) and enemy_weight_src == 0 and func_enemy_city_count(city_s, 1) >= 1 and 3 >= battle_unit_check(src, dst) and 20000 + (4000 * ( 3 - a )) < pk::get_troops(src))
                       {
                           best_dst = dst_id;
                           dst_list.add(dst);  // 수송가능 거점리스트 추가
                        }



// 전방 항관 중 바로 적 거점과 인접하지 않은 항관에서에서 7900명 이하거나 1.0배의 적 공격 받는 도시에 병력 보낸다
                    
if (건물_관문시작 <= src_id and src_id < 건물_항구끝 and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and ((base2_troops + force_troops1 <= 7900 and 0 < enemy_units1) or ((base2_troops + force_troops3 + troops_already(dst)) * 1.0f < enemy_troops3)) and enemy_weight_src == 0 and func_enemy_city_count(city_s, 1) >= 1 and 3 >= battle_unit_check(src, dst) )
                       {
                           best_dst = dst_id;
                           dst_list.add(dst);  // 수송가능 거점리스트 추가
                        }






																								 
// 전방 도시 중 바로 적 거점과 인접하지 않은 도시에서 6900명 이하거나 1.0배의 적 공격 받는관문에 병력 보낸다

  else if (건물_도시시작 <= src_id and src_id < 건물_도시끝 and 건물_관문시작 <= dst_id and dst_id < 건물_관문끝 and ((base2_troops + force_troops1 <= 6900 and 0 < enemy_units1) or ((base2_troops + force_troops1 + troops_already(dst)) * 1.0f < enemy_troops1 )) and enemy_weight_src == 0 and func_enemy_city_count(city_s, 1) >= 1 and 3 >= battle_unit_check(src, dst) )
                       {
                           best_dst = dst_id;
                           dst_list.add(dst);  // 수송가능 거점리스트 추가
                       }



// 전방 항관 중 바로 적 거점과 인접하지 않은 항관에서 6900명 이하거나 1.0배의 적 공격 받는관문에 병력 보낸다

  else if (건물_관문시작 <= src_id and src_id < 건물_항구끝 and 건물_관문시작 <= dst_id and dst_id < 건물_관문끝 and ((base2_troops + force_troops1 <= 6900 and 0 < enemy_units1) or ((base2_troops + force_troops3 + troops_already(dst)) * 1.0f < enemy_troops3 )) and enemy_weight_src == 0 and func_enemy_city_count(city_s, 1) >= 1 and 3 >= battle_unit_check(src, dst) )
                       {
                           best_dst = dst_id;
                           dst_list.add(dst);  // 수송가능 거점리스트 추가
                       }






																								  
// 전방 도시 중 바로 적 거점과 인접하지 않은 도시에서 6900명 이하거나 1.0배의 적 공격 받는 항구에 병력 보낸다

   else if (건물_도시시작 <= src_id and src_id < 건물_도시끝 and 건물_항구시작 <= dst_id and dst_id < 건물_항구끝 and ((base2_troops + force_troops1 <= 6900 and 0 < enemy_units1) or ((base2_troops + force_troops1 + troops_already(dst)) * 1.0f < enemy_troops1)) and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id and enemy_weight_src == 0 and func_enemy_city_count(city_s, 1) >= 1 and 3 >= battle_unit_check(src, dst) )
                       {
                           best_dst = dst_id;
                           dst_list.add(dst);  // 수송가능 거점리스트 추가
                       }



// 전방 항관 중 바로 적 거점과 인접하지 않은 항관에서 6900명 이하거나 1.0배의 적 공격 받는 항구에 병력 보낸다

   else if (건물_관문시작 <= src_id and src_id < 건물_항구끝 and 건물_항구시작 <= dst_id and dst_id < 건물_항구끝 and ((base2_troops + force_troops1 <= 6900 and 0 < enemy_units1) or ((base2_troops + force_troops3 + troops_already(dst)) * 1.0f < enemy_troops3)) and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id and enemy_weight_src == 0 and func_enemy_city_count(city_s, 1) >= 1 and 3 >= battle_unit_check(src, dst) )
                       {
                           best_dst = dst_id;
                           dst_list.add(dst);  // 수송가능 거점리스트 추가
                       }












		/** 적의 거점과 맞닿아있는 전방 거점들 */

// 적 거점과 맞닿은 전방 도시에서 7900명 이하거나 1.0배의 적 공격 받는 도시에 병력 보낸다
                    
if (건물_도시시작 <= src_id and src_id < 건물_도시끝 and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and ((base2_troops + force_troops1 <= 7900 and 0 < enemy_units1) or ((base2_troops + force_troops3 + troops_already(dst)) * 1.0f < enemy_troops3)) and enemy_weight_src > 0  and func_enemy_city_count(city_s, 1) >= 1 and 1 >= battle_unit_check(src, dst) and (EnemyBase_troops(src) * 0.5f) + ( ( 3 - a ) * 7000 ) < pk::get_troops(src) and src_enemy_troops3 * ( 4 - a ) < pk::get_troops(src) )
                       {
                           best_dst = dst_id;
                           dst_list.add(dst);  // 수송가능 거점리스트 추가
                        }



// 적 거점과 맞닿은 전방 항구 관문에서 7900명 이하거나 1.0배의 적 공격 받는 도시에 병력 보낸다
                    
if (건물_관문시작 <= src_id and src_id < 건물_항구끝 and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and ((base2_troops + force_troops1 <= 7900 and 0 < enemy_units1) or ((base2_troops + force_troops3 + troops_already(dst)) * 1.0f < enemy_troops3)) and enemy_weight_src > 0 and func_enemy_city_count(city_s, 1) >= 1 and 1 >= battle_unit_check(src, dst) and src_enemy_troops1 * ( 4 - a ) < pk::get_troops(src) )
                       {
                           best_dst = dst_id;
                           dst_list.add(dst);  // 수송가능 거점리스트 추가
                        }






// 적 거점과 맞닿은 전방 도시에서 6900명 이하거나 1.0배의 적 공격 받는관문에 병력 보낸다

  else if (건물_도시시작 <= src_id and src_id < 건물_도시끝 and 건물_관문시작 <= dst_id and dst_id < 건물_관문끝 and ((base2_troops + force_troops1 <= 6900 and 0 < enemy_units1) or ((base2_troops + force_troops1 + troops_already(dst)) * 1.0f < enemy_troops1)) and enemy_weight_src > 0 and func_enemy_city_count(city_s, 1) >= 1 and 1 >= battle_unit_check(src, dst) and ((base_dist == 1 and src_enemy_troops1 * ( 4 - a ) < pk::get_troops(src)) or (base_dist == 2 and src_enemy_troops2 + (4000 * ( 4 - a )) < pk::get_troops(src))) and !enemy_approach_direct(src) )
                       {
                           best_dst = dst_id;
                           dst_list.add(dst);  // 수송가능 거점리스트 추가
                       }



// 적 거점과 맞닿은 전방 항관에서 6900명 이하거나 1.0배의 적 공격 받는관문에 병력 보낸다

  else if (건물_관문시작 <= src_id and src_id < 건물_항구끝 and 건물_관문시작 <= dst_id and dst_id < 건물_관문끝 and ((base2_troops + force_troops1 <= 6900 and 0 < enemy_units1) or ((base2_troops + force_troops3 + troops_already(dst)) * 1.0f < enemy_troops3)) and enemy_weight_src > 0 and func_enemy_city_count(city_s, 1) >= 1 and 1 >= battle_unit_check(src, dst) and ((base_dist == 1 and src_enemy_troops1 * ( 4 - a ) < pk::get_troops(src)) or (base_dist == 2 and src_enemy_troops3 + (5000 * ( 4 - a )) < pk::get_troops(src))) )
                       {
                           best_dst = dst_id;
                           dst_list.add(dst);  // 수송가능 거점리스트 추가
                       }






// 적 거점과 맞닿은 전방 도시에서 6900명 이하거나 1.0배의 적 공격 받는 항구에 병력 보낸다

   else if (건물_도시시작 <= src_id and src_id < 건물_도시끝 and 건물_항구시작 <= dst_id and dst_id < 건물_항구끝 and ((base2_troops + force_troops1 <= 6900 and 0 < enemy_units1) or ((base2_troops + force_troops1 + troops_already(dst)) * 1.0f < enemy_troops1)) and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id and enemy_weight_src > 0 and func_enemy_city_count(city_s, 1) >= 1 and 1 >= battle_unit_check(src, dst) and ((base_dist == 1 and src_enemy_troops1 * ( 4 - a ) < pk::get_troops(src)) or (base_dist == 2 and src_enemy_troops3 + (5000 * ( 4 - a )) < pk::get_troops(src))) and !enemy_approach_direct(src))
                       {
                           best_dst = dst_id;
                           dst_list.add(dst);  // 수송가능 거점리스트 추가
                       }



// 적 거점과 맞닿은 전방 항관에서 6900명 이하거나 1.0배의 적 공격 받는 항구에 병력 보낸다

   else if (건물_관문시작 <= src_id and src_id < 건물_항구끝 and 건물_항구시작 <= dst_id and dst_id < 건물_항구끝 and ((base2_troops + force_troops1 <= 6900 and 0 < enemy_units1) or ((base2_troops + force_troops3 + troops_already(dst)) * 1.0f < enemy_troops3)) and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id and enemy_weight_src > 0 and func_enemy_city_count(city_s, 1) >= 1 and 1 >= battle_unit_check(src, dst) and ((base_dist == 1 and src_enemy_troops1 * ( 4 - a ) < pk::get_troops(src)) or (base_dist == 2 and src_enemy_troops3 + (5000 * ( 4 - a )) < pk::get_troops(src))) )
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
					
                   return (main.gap_troops(a) - main.troops_already(a) > main.gap_troops(b) - main.troops_already(b));								
					
                    int build_dist_a = pk::get_building_distance(a.get_id(), main.src_k.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.src_k.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.src_k.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.src_k.pos);

                    if (build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);
                    
                    return (pos_dist_a < pos_dist_b);
                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
		}










        //----------------------------------------------------------------------------------
        //   초극도로 포화된 항구 관문에서 보급대 보내기  (병력)
        //----------------------------------------------------------------------------------




		/** 병력 있는 거점 찾기 */

		bool needGP_PEXtroops (pk::building@ base)
		{

			if (!no_enemy_around(base)) return false;

			int base_troops = pk::get_troops(base);


                        int enemy_weight = countNeighborEnemyBase(base);





	// 거점의 병력 최대 제한치까지 여유 공간이 3만5천 이하로 줄어들기 시작하면, 주변에 적이 있던 말던  관문, 항구에서 보급 보내라

			if ( pk::get_max_troops(base) - 35000 <= base_troops and 건물_관문시작 <= base.get_id() and base.get_id() < 건물_항구끝 and no_enemy_around(base))
				return true;



            
			return false;
		}







		/** 35% 보급 명령 */

		bool PushGP_PEXtroops(pk::building@ base)
		{

            int reinforce_troops = pk::min(10000, pk::max(3000, int (pk::get_troops(base) * 0.35f) ));
			// 명령 가능한 무장이 있는지 확인.
			auto person_list = pk::get_idle_person_list(base);
			if (person_list.count == 0) return false;

			// 수송할 인접 거접이 있는지 확인.
			int target = getBackupGP_PEXBase(base);
			if (target == -1) return false;

			if (!no_enemy_around(pk::get_building(target))) return false;
			if (enemy_approach(pk::get_building(target))) return false;
			if (close_combat(pk::get_building(target))) return false;

            pk::building@ target_base = pk::get_building(target);

            if (건물_관문시작 <= target and target < 건물_항구끝)
            reinforce_troops = pk::min(4500, pk::max(3000, int (pk::get_troops(base) * 0.35f) ));

            if (건물_도시시작 <= target and target < 건물_도시끝 and 45000 <= pk::get_max_troops(target_base) - pk::get_troops(target_base))
            reinforce_troops = pk::min(15000, pk::min(pk::get_troops(base) - 10000, pk::get_max_troops(target_base) - pk::get_troops(target_base) - 31000 ));		

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
            if (unit_food < int(0.5f * reinforce_troops)) return false;   // 병량 부족 
       

            float supply_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            float weapon_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            
			// 출진 명령 정보 생성.
			pk::com_deploy_cmd_info cmd;
			@cmd.base = @base;
			cmd.type = 부대종류_수송;
			cmd.member[0] = leader.get_id();
			cmd.gold = pk::min(int(pk::get_gold(base) * 0.2f), 5000);
			cmd.food = pk::min(pk::max (5000 , unit_food), 25000);
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
            pk::say(pk::u8encode("항관이 과포화 상태다!\n어디 빈 거점 없나?"), leader);
            
            // 임시 도주 효과 ('19.3.6)
            if (거점수송_일시도주설정)
            {
                leader.skill = retreat_skill;         // 특기 복원
            }
            
            
			return true;
		}





        
		/** 가장 가깝고 위기에 빠진 아군 도시에 보급을 보냄 */

        pk::building@ src_GP_PEX;
		int getBackupGP_PEXBase(pk::building@ src)
		{
			int best_dst = -1;
			int best_distance = 0;
            int src_id = src.get_id();
            pk::list<pk::building@> dst_list; 
            @src_GP_PEX = @src;



            
            int search_base = 건물_도시끝;
            if      (거점수송_거점검색모드 == 0) search_base = 건물_도시끝;
            else if (거점수송_거점검색모드 == 1) search_base = 건물_거점끝;
            
            pk::force@ force = pk::get_force(src.get_force_id());
            
			// 수송 거점 검색

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
                       // 목적지가 역병 혹은 메뚜기 재해지역이면 수송 안보냄
	          pk::city@ city_c = pk::get_city(pk::get_city_id(dst.pos));
                        if (city_c.ekibyou or city_c.inago)  continue;

                        int enemy_weight = countNeighborEnemyBase(dst);
						int enemy_weight_src = countNeighborEnemyBase(src);

	// 병력 최대치까지 아직 4만 여유 있는 , 적 침공에서 안전한 도시로 보급 보내라
                    
        if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst)  and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and ( base2_troops <= pk::get_max_troops(dst) - 40000 ) and  no_enemy_around(dst) and enemy_weight == 0 and func_already (dst) <= 3 )
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 수송가능 거점리스트 추가
                    }



           // 병력 최대치까지 아직 4만 여유 있는 , 적 침공에서 안전한 관문, 항구로 보급 보내라

       else if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst)  and 건물_관문시작 <= dst_id and dst_id < 건물_항구끝 and  base2_troops <= pk::get_max_troops(dst) - 40000 and no_enemy_around(dst) and enemy_weight  == 0 and func_already (dst) <= 3 and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id)
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 수송가능 거점리스트 추가
                    }


           // 병력 최대치까지 아직 4만 여유 있는 , 접경지대의 도시로 보급 보내라

       else if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst)  and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and base2_troops <= pk::get_max_troops(dst) - 40000 and no_enemy_around(dst) and  1 <= enemy_weight and enemy_weight_src == 0 and func_already (dst) <= 3 )
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 수송가능 거점리스트 추가
                    }



           // 병력 최대치까지 아직 4만 여유 있는 , 접경지대의 관문, 항구로 보급 보내라

       else if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst)  and 건물_관문시작 <= dst_id and dst_id < 건물_항구끝 and base2_troops <= pk::get_max_troops(dst) - 40000 and no_enemy_around(dst) and 1 <= enemy_weight and enemy_weight_src == 0 and func_already (dst) <= 3 and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id)
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
                    return (pk::get_max_troops(a) - pk::get_troops(a) > pk::get_max_troops(b) - pk::get_troops(b));					
					
                    int build_dist_a = pk::get_building_distance(a.get_id(), main.src_GP_PEX.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.src_GP_PEX.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.src_GP_PEX.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.src_GP_PEX.pos);

                    if (build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);
                    
                    return (pos_dist_a < pos_dist_b);
                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
		}














        //----------------------------------------------------------------------------------
        //   초극도로 포화된 도시에서 보급대 보내기  (병력)
        //----------------------------------------------------------------------------------




		/** 병력 있는 거점 찾기 */

		bool needS_PEXtroops (pk::building@ base)
		{
			if (!no_enemy_around(base)) return false;

			int base_troops = pk::get_troops(base);


                        int enemy_weight = countNeighborEnemyBase(base);





	// 거점의 병력 최대 제한치까지 여유 공간이 1만5천 이하로 줄어들기 시작한 적 침공에서 안전하고, 주변에 적의 거점이 없는  관문, 항구에서 보급 보내라

			if ( pk::get_max_troops(base) - 15000 <= base_troops and 건물_관문시작 <= base.get_id() and base.get_id() < 건물_항구끝 and no_enemy_around(base) and enemy_weight  == 0 )
				return true;


	// 거점의 병력 최대 제한치까지 여유 공간이 1만5천 이하로 줄어들기 시작한 적 침공에서 안전하고, 주변에 적의 거점이 없는 도시에서 보급 보내라

			if ( pk::get_max_troops(base) - 15000 <= base_troops and 건물_도시시작 <= base.get_id() and base.get_id() < 건물_도시끝 and no_enemy_around(base) and enemy_weight  == 0)
				return true;



	// 거점의 병력 최대 제한치까지 여유 공간이 1만5천 이하로 줄어들기 시작하면 보급 보내라
			if ( pk::get_max_troops(base) - 15000 <= base_troops and base.get_id() < 건물_거점끝 and no_enemy_around(base)  )
				return true;

            
			return false;
		}







		/** 35% 보급 명령 */

		bool PushS_PEXtroops(pk::building@ base)
		{

            int reinforce_troops = pk::min(10000, pk::max(3000, int (pk::get_troops(base) * 0.35f) ));
			// 명령 가능한 무장이 있는지 확인.
			auto person_list = pk::get_idle_person_list(base);
			if (person_list.count == 0) return false;

			// 수송할 인접 거접이 있는지 확인.
			int target = getBackupS_PEXBase(base);
			if (target == -1) return false;

			if (!no_enemy_around(pk::get_building(target))) return false;
			if (enemy_approach(pk::get_building(target))) return false;
			if (close_combat(pk::get_building(target))) return false;


            if (건물_관문시작 <= target and target < 건물_항구끝)
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
     

            int unit_food = int(pk::min( 0.3f * pk::get_food(base), 2.0f * reinforce_troops));
            if (unit_food < int(0.5f * reinforce_troops)) return false;   // 병량 부족 
       

            float supply_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            float weapon_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            
			// 출진 명령 정보 생성.
			pk::com_deploy_cmd_info cmd;
			@cmd.base = @base;
			cmd.type = 부대종류_수송;
			cmd.member[0] = leader.get_id();
			cmd.gold = pk::min(int(pk::get_gold(base) * 0.2f), 5000);
			cmd.food = pk::min(pk::max (5000 , unit_food), 25000);
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
            pk::say(pk::u8encode("안돼...병력 과포화 상태다!\n어디 빈 거점 없나?"), leader);
            
            // 임시 도주 효과 ('19.3.6)
            if (거점수송_일시도주설정)
            {
                leader.skill = retreat_skill;         // 특기 복원
            }
            
            
			return true;
		}





        
		/** 가장 가깝고 위기에 빠진 아군 도시에 보급을 보냄 */

        pk::building@ src_S_PEX;
		int getBackupS_PEXBase(pk::building@ src)
		{
			int best_dst = -1;
			int best_distance = 0;
            int src_id = src.get_id();
            pk::list<pk::building@> dst_list; 
            @src_S_PEX = @src;



            
            int search_base = 건물_도시끝;
            if      (거점수송_거점검색모드 == 0) search_base = 건물_도시끝;
            else if (거점수송_거점검색모드 == 1) search_base = 건물_거점끝;
            
            pk::force@ force = pk::get_force(src.get_force_id());
            
			// 수송 거점 검색

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
                       // 목적지가 역병 혹은 메뚜기 재해지역이면 수송 안보냄
	          pk::city@ city_c = pk::get_city(pk::get_city_id(dst.pos));
                        if (city_c.ekibyou or city_c.inago)  continue;

                        int enemy_weight = countNeighborEnemyBase(dst);

	// 병력 최대치까지 아직 3만 여유 있는 , 적 침공에서 안전한 도시로 보급 보내라
                    
        if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst) and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and ( base2_troops <= pk::get_max_troops(dst) - 30000 ) and no_enemy_around(dst) and enemy_weight  == 0 and func_already (dst) <= 3 )
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 수송가능 거점리스트 추가
                    }



           // 병력 최대치까지 아직 2만 여유 있는 , 적 침공에서 안전한 관문, 항구로 보급 보내라

       else if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst) and 건물_관문시작 <= dst_id and dst_id < 건물_항구끝 and  base2_troops <= pk::get_max_troops(dst) - 20000 and no_enemy_around(dst) and enemy_weight  == 0 and func_already (dst) <= 3 and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id)
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 수송가능 거점리스트 추가
                    }


           // 병력 최대치까지 아직 3만 여유 있는 , 접경지대의 도시로 보급 보내라

       else if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst) and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and base2_troops <= pk::get_max_troops(dst) - 30000 and no_enemy_around(dst) and  1 <= enemy_weight  and func_already (dst) <= 3 )
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 수송가능 거점리스트 추가
                    }



           // 병력 최대치까지 아직 2만 여유 있는 , 접경지대의 관문, 항구로 보급 보내라

       else if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst) and 건물_관문시작 <= dst_id and dst_id < 건물_항구끝 and base2_troops <= pk::get_max_troops(dst) - 20000 and no_enemy_around(dst) and 1 <= enemy_weight  and func_already (dst) <= 3 and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id)
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
                    return (pk::get_max_troops(a) - pk::get_troops(a) > pk::get_max_troops(b) - pk::get_troops(b));					
										
                    int build_dist_a = pk::get_building_distance(a.get_id(), main.src_S_PEX.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.src_S_PEX.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.src_S_PEX.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.src_S_PEX.pos);

                    if (build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);
                    
                    return (pos_dist_a < pos_dist_b);
                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
		}



















        //----------------------------------------------------------------------------------
        //  평시 포화된 도시에서 보급대 보내기  (병력)
        //----------------------------------------------------------------------------------




		/** 병력 있는 거점 찾기 */

		bool needPEXtroops (pk::building@ base)
		{
			if (!no_enemy_around(base)) return false;

			int base_troops = pk::get_troops(base);


                        int enemy_weight = countNeighborEnemyBase(base);





	// 병력 최대 기준 45% 이상 있고, 적 침공에서 안전하고, 주변에 적의 거점이 없는  관문, 항구에서 보급 보내라

			if ( pk::get_max_troops(base) * 0.45f  <= base_troops and 건물_관문시작 <= base.get_id() and base.get_id() < 건물_항구끝 and no_enemy_around(base) and enemy_weight  == 0 )
				return true;


	// 병력 최대 기준까지 여유 공간이 2만 9천 밖에 없고, 적 침공에서 안전하고, 주변에 적의 거점이 없는 도시에서 보급 보내라

			if ( pk::get_max_troops(base) - 29000 <= base_troops and 건물_도시시작 <= base.get_id() and base.get_id() < 건물_도시끝 and no_enemy_around(base) and enemy_weight  == 0)
				return true;



	// 병력 최대 기준까지 여유 공간이 2만 9천 이하 밖에 없으면 보급 보내라
			if ( pk::get_max_troops(base) - 29000 <= base_troops and base.get_id() < 건물_거점끝 and no_enemy_around(base)  )
				return true;

            
			return false;
		}







		/** 35% 보급 명령 */

		bool PushPEXtroops(pk::building@ base)
		{

            int reinforce_troops = pk::min(15000, pk::max(3000, int (pk::get_troops(base) * 0.35f) ));
			// 명령 가능한 무장이 있는지 확인.
			auto person_list = pk::get_idle_person_list(base);
			if (person_list.count == 0) return false;

			// 수송할 인접 거접이 있는지 확인.
			int target = getBackupPEXBase(base);
			if (target == -1) return false;

			if (!no_enemy_around(pk::get_building(target))) return false;
			if (enemy_approach(pk::get_building(target))) return false;
			if (close_combat(pk::get_building(target))) return false;

            if (건물_관문시작 <= target and target < 건물_항구끝)
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
     

            int unit_food = int(pk::min( 0.3f * pk::get_food(base), 2.0f * reinforce_troops));
            if (unit_food < int(0.5f * reinforce_troops)) return false;   // 병량 부족 
       

            float supply_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            float weapon_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            
			// 출진 명령 정보 생성.
			pk::com_deploy_cmd_info cmd;
			@cmd.base = @base;
			cmd.type = 부대종류_수송;
			cmd.member[0] = leader.get_id();
			cmd.gold = pk::min(int(pk::get_gold(base) * 0.2f), 5000);
			cmd.food = pk::min(pk::max (5000 , unit_food), 25000);
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
            pk::say(pk::u8encode("현재 병력 포화 상태다!\n병력을 분산 배치하라!"), leader);
            
            // 임시 도주 효과 ('19.3.6)
            if (거점수송_일시도주설정)
            {
                leader.skill = retreat_skill;         // 특기 복원
            }
            
            
			return true;
		}





        
		/** 가장 가깝고 위기에 빠진 아군 도시에 보급을 보냄 */

        pk::building@ src_PEX;
		int getBackupPEXBase(pk::building@ src)
		{
			int best_dst = -1;
			int best_distance = 0;
            int src_id = src.get_id();
            pk::list<pk::building@> dst_list; 
            @src_PEX = @src;



            
            int search_base = 건물_도시끝;
            if      (거점수송_거점검색모드 == 0) search_base = 건물_도시끝;
            else if (거점수송_거점검색모드 == 1) search_base = 건물_거점끝;
            
            pk::force@ force = pk::get_force(src.get_force_id());
            
			// 수송 거점 검색

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
                       // 목적지가 역병 혹은 메뚜기 재해지역이면 수송 안보냄
	          pk::city@ city_c = pk::get_city(pk::get_city_id(dst.pos));
                        if (city_c.ekibyou or city_c.inago)  continue;

                        int enemy_weight = countNeighborEnemyBase(dst);

	// 병력 최대 기준 42% 이하로, , 적 침공에서 안전한 도시로 보급 보내라
                    
        if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst)  and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and ( base2_troops <= pk::get_max_troops(dst) * 0.42f  or  base2_troops <= pk::get_max_troops(dst) - 70000 )  and no_enemy_around(dst) and enemy_weight  == 0 and func_already (dst) <= 3 )
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 수송가능 거점리스트 추가
                    }



           // 병력 6천 이하로 , 적 침공에서 안전한 관문, 항구로 보급 보내라

       else if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst)  and 건물_관문시작 <= dst_id and dst_id < 건물_항구끝 and  base2_troops <= 6000 and no_enemy_around(dst) and enemy_weight  == 0 and func_already (dst) <= 3 and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id)
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 수송가능 거점리스트 추가
                    }


           // 병력 최대 기준 52% 이하로,  접경지대의 도시로 보급 보내라

       else if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst)  and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and ( base2_troops <= pk::get_max_troops(dst) * 0.52f  or  base2_troops <= pk::get_max_troops(dst) - 60000 ) and no_enemy_around(dst) and  1 <= enemy_weight  and func_already (dst) <= 3 )
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 수송가능 거점리스트 추가
                    }



           // 병력 1만 3천 이하로,  접경지대의 관문, 항구로 보급 보내라

       else if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst)  and 건물_관문시작 <= dst_id and dst_id < 건물_항구끝 and base2_troops <= 13000 and no_enemy_around(dst) and 1 <= enemy_weight  and func_already (dst) <= 3 and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id)
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
                    return (pk::get_max_troops(a) - pk::get_troops(a) > pk::get_max_troops(b) - pk::get_troops(b));					
										
                    int build_dist_a = pk::get_building_distance(a.get_id(), main.src_PEX.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.src_PEX.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.src_PEX.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.src_PEX.pos);

                    if (build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);
                    
                    return (pos_dist_a < pos_dist_b);
                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
		}








        //----------------------------------------------------------------------------------
        //  병력이 극소수인 거점으로 병력 보내기
        //----------------------------------------------------------------------------------




		/** 병력 있는 거점 찾기 */

		bool needarmy(pk::building@ base)
		{
			if (!no_enemy_around(base)) return false;

			int base_troops = pk::get_troops(base);


                        int enemy_weight = countNeighborEnemyBase(base);





	// 병력 5천 이상 있고, 적 침공에서 안전하고, 주변에 적 부대가 없는  관문, 항구에서 보급 보내라

			if (5000  <= base_troops and 건물_관문시작 <= base.get_id() and base.get_id() < 건물_항구끝 and no_enemy_around(base) and  enemy_weight == 0 )
				return true;
			
	// 병력 1만 이상 있고, 적 침공에서 안전하고, 전방의 관문, 항구에서 보급 보내라

			if (10000  <= base_troops and 건물_관문시작 <= base.get_id() and base.get_id() < 건물_항구끝 and no_enemy_around(base) and  enemy_weight > 0)
				return true;			
			


	// 병력 1만 7천 이상 있고, 적 침공에서 안전하고, 주변에 적 부대가 없는 도시에서 보급 보내라

			if ( 17000  <= base_troops and 건물_도시시작 <= base.get_id() and base.get_id() < 건물_도시끝 and no_enemy_around(base) )
				return true;





            
			return false;
		}







		/** 35% 보급 명령 */

		bool Pusharmy(pk::building@ base)
		{

            int reinforce_troops = pk::min(15000, pk::max(3000, int (pk::get_troops(base) * 0.35f) ));
			// 명령 가능한 무장이 있는지 확인.
			auto person_list = pk::get_idle_person_list(base);
			if (person_list.count == 0) return false;

			// 수송할 인접 거접이 있는지 확인.
			int target = getBackupMINBase(base);
			if (target == -1) return false;

			if (!no_enemy_around(pk::get_building(target))) return false;
			if (enemy_approach(pk::get_building(target))) return false;
			if (close_combat(pk::get_building(target))) return false;

            if (건물_관문시작 <= target and target < 건물_항구끝)
            reinforce_troops = pk::min(5000, pk::max(3000, int (pk::get_troops(base) * 0.35f) ));

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
            if (unit_food < int(0.5f * reinforce_troops)) return false;   // 병량 부족 
       

            float supply_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            float weapon_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            
			// 출진 명령 정보 생성.
			pk::com_deploy_cmd_info cmd;
			@cmd.base = @base;
			cmd.type = 부대종류_수송;
			cmd.member[0] = leader.get_id();
			cmd.gold = pk::min(int(pk::get_gold(base) * 0.2f), 5000);
			cmd.food = pk::min(pk::max (5000 , unit_food), 25000);
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
            pk::say(pk::u8encode("아군 거점에 병력이 너무 적다!\n병력을 보내 충원하라!"), leader);
            
            // 임시 도주 효과 ('19.3.6)
            if (거점수송_일시도주설정)
            {
                leader.skill = retreat_skill;         // 특기 복원
            }
            
            
			return true;
		}





        
		/** 가장 가깝고 위기에 빠진 아군 도시에 보급을 보냄 */

        pk::building@ src_nar;
		int getBackupMINBase(pk::building@ src)
		{
			int best_dst = -1;
			int best_distance = 0;
            int src_id = src.get_id();
            pk::list<pk::building@> dst_list; 
            @src_nar = @src;



            
            int search_base = 건물_도시끝;
            if      (거점수송_거점검색모드 == 0) search_base = 건물_도시끝;
            else if (거점수송_거점검색모드 == 1) search_base = 건물_거점끝;
            
            pk::force@ force = pk::get_force(src.get_force_id());
            
			// 수송 거점 검색

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
                       // 목적지가 역병 혹은 메뚜기 재해지역이면 수송 안보냄
	          pk::city@ city_c = pk::get_city(pk::get_city_id(dst.pos));
                        if (city_c.ekibyou or city_c.inago)  continue;

                        int enemy_weight = countNeighborEnemyBase(src);
                        int enemy_weight_dst = countNeighborEnemyBase(dst);


	//  보급 받는 곳이 후방이면 보내는 곳도 후방, 받는 곳이 전방이면 보내는 곳은 안따짐

    if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst) and ((enemy_weight_dst == 0 and enemy_weight == 0) or enemy_weight_dst > 0))
        {

	// 병력 최대 기준 10% 이하로,적 침공에서 안전한 도시로 보급 보내라
                    
        if (건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and base2_troops <= pk::get_max_troops(dst) * 0.10f   and no_enemy_around(dst) and func_already (dst) <= 1 and func_supplycheck(src,dst) == 0)
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 수송가능 거점리스트 추가
                    }



           // 병력 2300 이하로 , 적 침공에서 안전한 관문, 항구로 보급 보내라

       else if (건물_관문시작 <= dst_id and dst_id < 건물_항구끝 and  base2_troops <= 2300 and no_enemy_around(dst) and func_already (dst) <= 1 and func_supplycheck(src,dst) == 0 and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id)
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
                    int build_dist_a = pk::get_building_distance(a.get_id(), main.src_nar.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.src_nar.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.src_nar.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.src_nar.pos);

                    if (build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);
                    
                    return (pos_dist_a < pos_dist_b);
                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
		}












        //----------------------------------------------------------------------------------
        //  평시 항구에서 도시로 보급대 보내기  (병력) 3천만 남기는 프로그램 대신
        //----------------------------------------------------------------------------------




		/** 병력 있는 거점 찾기 */

		bool needPorttroops (pk::building@ base)
		{
			if (!no_enemy_around(base)) return false;

			int base_troops = pk::get_troops(base);


                        int enemy_weight = countNeighborEnemyBase(base);
                        int user_weight = countNeighborUserBase(base);


	// 병력 1만 3천 이상, 적 침공에서 안전한 관문, 항구에서 보급 보내라

			if ( 13000  <= base_troops and 건물_관문시작 <= base.get_id() and base.get_id() < 건물_항구끝 and no_enemy_around(base) and enemy_weight == 0 and user_weight == 0 )
				return true;

	// 병력 1만 8천 이상, 전방의 안전한 관문, 항구에서 보급 보내라

			if ( 18000  <= base_troops and 건물_관문시작 <= base.get_id() and base.get_id() < 건물_항구끝 and no_enemy_around(base) and (enemy_weight >= 1 or user_weight >= 1) )
				return true;



            
			return false;
		}







		/** 45% 보급 명령 */

		bool PushPorttroops(pk::building@ base)
		{

                        int enemy_weight = countNeighborEnemyBase(base);
                        int user_weight = countNeighborUserBase(base);

            int reinforce_troops = pk::min(10000, pk::max(3000, int (pk::get_troops(base) * 0.45f) ));

			if (enemy_weight == 0 and user_weight == 0) 
            reinforce_troops = pk::min(10000, pk::max(3000, int (pk::get_troops(base) - 8000) ));

			if (enemy_weight >= 1 or user_weight >= 1) 
            reinforce_troops = pk::min(10000, pk::max(3000, int (pk::get_troops(base) - 11000) ));


			// 명령 가능한 무장이 있는지 확인.
			auto person_list = pk::get_idle_person_list(base);
			if (person_list.count == 0) return false;

			// 수송할 인접 거접이 있는지 확인.
			int target = getBackupPBase(base);
			if (target == -1) return false;

			if (enemy_approach(pk::get_building(target))) return false;
			if (close_combat(pk::get_building(target))) return false;


            if (건물_관문시작 <= target and target < 건물_항구끝)
            reinforce_troops = pk::min(5000, pk::max(3000, int (pk::get_troops(base) * 0.45f) ));

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
            if (unit_food < int(0.5f * reinforce_troops)) return false;   // 병량 부족 


            float supply_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            float weapon_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            
			// 출진 명령 정보 생성.
			pk::com_deploy_cmd_info cmd;
			@cmd.base = @base;
			cmd.type = 부대종류_수송;
			cmd.member[0] = leader.get_id();
			cmd.gold = pk::min(int(pk::get_gold(base) * 0.35f), 7000);
			cmd.food = pk::min(pk::max (5000 , unit_food), 25000);
			cmd.troops = reinforce_troops;
			int i = 0;
			for (int weapon_id = 0; weapon_id < 병기_끝; weapon_id++)
			{
                int weapon_amount = 0;
                if (weapon_id < 병기_충차)
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id) * 0.35f), 60000);
                else
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id)), 6);
                
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
            pk::say(pk::u8encode("당장의 위기는 없는 듯 하니\n성으로 병력을 이동시킨다!"), leader);
            
            // 임시 도주 효과 ('19.3.6)
            if (거점수송_일시도주설정)
            {
                leader.skill = retreat_skill;         // 특기 복원
            }
            
            
			return true;
		}





        
		/** 가장 가깝고 위기에 빠진 아군 도시에 보급을 보냄 */

        pk::building@ src_po;
		int getBackupPBase(pk::building@ src)
		{
			int best_dst = -1;
			int best_distance = 0;
            int src_id = src.get_id();
            pk::list<pk::building@> dst_list; 
            @src_po = @src;



            
            int search_base = 건물_도시끝;
            if      (거점수송_거점검색모드 == 0) search_base = 건물_도시끝;
            else if (거점수송_거점검색모드 == 1) search_base = 건물_거점끝;
            
            pk::force@ force = pk::get_force(src.get_force_id());
            
			// 수송 거점 검색

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
                       // 목적지가 역병 혹은 메뚜기 재해지역이면 수송 안보냄
	          pk::city@ city_c = pk::get_city(pk::get_city_id(dst.pos));
                        if (city_c.ekibyou or city_c.inago)  continue;

                        int enemy_weight = countNeighborEnemyBase(dst);
                        int user_weight = countNeighborUserBase(dst);

	// 병력 최대 기준 50% 이하로, 적 침공에서 안전한 도시로 보급 보내라
                    
        if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst)  and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and base2_troops <= pk::get_max_troops(dst) * 0.5f and func_already (dst) <= 1  and no_enemy_around(dst) and func_supplycheck(src,dst) == 0 )
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 수송가능 거점리스트 추가
                    }



           // 병력 5천 이하로 , 적 침공에서 안전한 관문, 항구로 보급 보내라

       else if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst)  and 건물_관문시작 <= dst_id and dst_id < 건물_항구끝 and base2_troops <= 5000 and func_already (dst) <= 1 and no_enemy_around(dst) and func_supplycheck(src,dst) == 0 and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id)
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 수송가능 거점리스트 추가
                    }


           // 병력 최대 기준 60% 이하로,  접경지대의 도시로 보급 보내라

       else if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst) and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and base2_troops <= pk::get_max_troops(dst) * 0.6f and no_enemy_around(dst) and ( 1 <= enemy_weight or 1 <= user_weight ) and func_already (dst) <= 1 and func_supplycheck(src,dst) == 0 )
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 수송가능 거점리스트 추가
                    }



           // 병력 1만 이하로, 접경지대의 관문, 항구로 보급 보내라

       else if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst)  and 건물_관문시작 <= dst_id and dst_id < 건물_항구끝 and base2_troops <= 10000 and no_enemy_around(dst) and  ( 1 <= enemy_weight or 1 <= user_weight ) and func_already (dst) <= 1 and func_supplycheck(src,dst) == 0 and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id)
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
                    int build_dist_a = pk::get_building_distance(a.get_id(), main.src_po.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.src_po.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.src_po.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.src_po.pos);

                    if (build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);
                    
                    return (pos_dist_a < pos_dist_b);
                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
		}












        //----------------------------------------------------------------------------------
        //  항구나 관문 병력이 도시보다 많을때 보급대 보내기  (병력) 
        //----------------------------------------------------------------------------------




		/** 병력 있는 거점 찾기 */

		bool needReversetroops (pk::building@ base)
		{
			if (!no_enemy_around(base)) return false;

			int base_troops = pk::get_troops(base);


                        int enemy_weight = countNeighborEnemyBase(base);


	// 병력 5천 이상, 적 침공에서 안전한 관문, 항구에서 보급 보내라

			if ( 5000  <= base_troops and 건물_관문시작 <= base.get_id() and base.get_id() < 건물_항구끝 and no_enemy_around(base) )
				return true;




            
			return false;
		}







		/** 35% 보급 명령 */

		bool PushReversetroops(pk::building@ base)
		{

            int reinforce_troops = pk::min(10000, pk::max(1500, int (pk::get_troops(base) * 0.35f) ));
			// 명령 가능한 무장이 있는지 확인.
			auto person_list = pk::get_idle_person_list(base);
			if (person_list.count == 0) return false;

			// 수송할 인접 거접이 있는지 확인.
			int target = getBackupREBase(base);
			if (target == -1) return false;

			if (!no_enemy_around(pk::get_building(target))) return false;
			if (enemy_approach(pk::get_building(target))) return false;
			if (close_combat(pk::get_building(target))) return false;

            pk::building@ target_base = pk::get_building(target);
			
            if (건물_도시시작 <= target and target < 건물_도시끝 and 16000 <= pk::get_troops(base) and 45000 <= pk::get_max_troops(target_base) - pk::get_troops(target_base))
            reinforce_troops = pk::min(15000, pk::min(pk::get_troops(base) - 10000, pk::get_max_troops(target_base) - pk::get_troops(target_base) - 31000 ));		
	

            if (건물_관문시작 <= target and target < 건물_항구끝)
            reinforce_troops = pk::min(5000, pk::max(1500, int (pk::get_troops(base) * 0.35f) ));

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
            if (unit_food < int(0.5f * reinforce_troops)) return false;   // 병량 부족 


            float supply_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            float weapon_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            
			// 출진 명령 정보 생성.
			pk::com_deploy_cmd_info cmd;
			@cmd.base = @base;
			cmd.type = 부대종류_수송;
			cmd.member[0] = leader.get_id();
			cmd.gold = pk::min(int(pk::get_gold(base) * 0.15f), 7000);
			cmd.food = pk::min(pk::max (2000 , unit_food), 25000);
			cmd.troops = reinforce_troops;
			int i = 0;
			for (int weapon_id = 0; weapon_id < 병기_끝; weapon_id++)
			{
                int weapon_amount = 0;
                if (weapon_id < 병기_충차)
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id) * 0.35f), 60000);
                else
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id)), 6);
                
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
            pk::say(pk::u8encode("성의 병력이 오히려 더 적군.\n성으로 병력을 이동시킨다!"), leader);
            
            // 임시 도주 효과 ('19.3.6)
            if (거점수송_일시도주설정)
            {
                leader.skill = retreat_skill;         // 특기 복원
            }
            
            
			return true;
		}





        
		/** 가장 가깝고 위기에 빠진 아군 도시에 보급을 보냄 */

        pk::building@ src_RE;
		int getBackupREBase(pk::building@ src)
		{
			int best_dst = -1;
			int best_distance = 0;
            int src_id = src.get_id();
            pk::list<pk::building@> dst_list; 
            @src_RE = @src;



            
            int search_base = 건물_도시끝;
            if      (거점수송_거점검색모드 == 0) search_base = 건물_도시끝;
            else if (거점수송_거점검색모드 == 1) search_base = 건물_거점끝;
            
            pk::force@ force = pk::get_force(src.get_force_id());
            
			// 수송 거점 검색

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
                       // 목적지가 역병 혹은 메뚜기 재해지역이면 수송 안보냄
	          pk::city@ city_c = pk::get_city(pk::get_city_id(dst.pos));
                        if (city_c.ekibyou or city_c.inago)  continue;

                        int enemy_weight = countNeighborEnemyBase(dst);

	// 병력이 항구 관문보다 적은 적의 침공에서 안전한 도시로 보급 보내라
                    
 if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst)  and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and base2_troops <= pk::get_troops(src) and func_already (dst) <= 1 and no_enemy_around(dst) and func_supplycheck(src,dst) == 0 )
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
                    int build_dist_a = pk::get_building_distance(a.get_id(), main.src_RE.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.src_RE.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.src_RE.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.src_RE.pos);

                    if (build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);
                    
                    return (pos_dist_a < pos_dist_b);
                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
		}
		
		
        //----------------------------------------------------------------------------------
        //  항구나 관문 병력이 적을때 도시에서 보급대 보내기  (병력) 
        //----------------------------------------------------------------------------------




		/** 병력 있는 거점 찾기 */

		bool need4thtroops (pk::building@ base)
		{
			if (!no_enemy_around(base)) return false;

			int base_troops = pk::get_troops(base);


                        int enemy_weight = countNeighborEnemyBase(base);


	// 병력 1만 2천 이상, 적 침공에서 안전한 도시에서 보급 보내라

			if ( 12000  <= base_troops and 건물_도시시작 <= base.get_id() and base.get_id() < 건물_도시끝 and no_enemy_around(base) )
				return true;



            
			return false;
		}







		/** 15% 보급 명령 */

		bool Push4thtroops(pk::building@ base)
		{

            int reinforce_troops = pk::min(1500, int (pk::get_troops(base) * 0.15f));
			// 명령 가능한 무장이 있는지 확인.
			auto person_list = pk::get_idle_person_list(base);
			if (person_list.count == 0) return false;

			// 수송할 인접 거접이 있는지 확인.
			int target = getBackup4thBase(base);
			if (target == -1) return false;

			if (enemy_approach(pk::get_building(target))) return false;
			if (close_combat(pk::get_building(target))) return false;


            if (건물_관문시작 <= target and target < 건물_항구끝)
            reinforce_troops = pk::min(5000, int (pk::get_troops(base) * 0.15f));

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
            if (unit_food < int(0.5f * reinforce_troops)) return false;   // 병량 부족 


            float supply_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            float weapon_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            
			// 출진 명령 정보 생성.
			pk::com_deploy_cmd_info cmd;
			@cmd.base = @base;
			cmd.type = 부대종류_수송;
			cmd.member[0] = leader.get_id();
			cmd.gold = pk::min(int(pk::get_gold(base) * 0.05f), 7000);
			cmd.food = pk::min(pk::max (2000 , unit_food), 25000);
			cmd.troops = reinforce_troops;
			int i = 0;
			for (int weapon_id = 0; weapon_id < 병기_끝; weapon_id++)
			{
                int weapon_amount = 0;
                if (weapon_id < 병기_충차)
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id) * 0.15f), 60000);
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
            pk::say(pk::u8encode("항관에 병력이 모자른다.\n병력을 이동시킨다!"), leader);
            
            // 임시 도주 효과 ('19.3.6)
            if (거점수송_일시도주설정)
            {
                leader.skill = retreat_skill;         // 특기 복원
            }
            
            
			return true;
		}





        
		/** 가장 가깝고 위기에 빠진 아군 도시에 보급을 보냄 */

        pk::building@ src_4th;
		int getBackup4thBase(pk::building@ src)
		{
			int best_dst = -1;
			int best_distance = 0;
            int src_id = src.get_id();
            pk::list<pk::building@> dst_list; 
            @src_4th = @src;



            
            int search_base = 건물_도시끝;
            if      (거점수송_거점검색모드 == 0) search_base = 건물_도시끝;
            else if (거점수송_거점검색모드 == 1) search_base = 건물_거점끝;
            
            pk::force@ force = pk::get_force(src.get_force_id());
            
			// 수송 거점 검색

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
                       // 목적지가 역병 혹은 메뚜기 재해지역이면 수송 안보냄
	          pk::city@ city_c = pk::get_city(pk::get_city_id(dst.pos));
                        if (city_c.ekibyou or city_c.inago)  continue;

                        int enemy_weight = countNeighborEnemyBase(dst);
                    int user_weight = countNeighborUserBase(dst);

	// 병력이 6천 이하인 적의 침공에서 안전한 항구 관문으로 보급 보내라
                    
 if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst) and 건물_관문시작 <= dst_id and dst_id < 건물_항구끝 and base2_troops <= 6000 and enemy_weight == 0 and user_weight == 0  and 13000 <= pk::get_troops(src) and func_already (dst) <= 1 and no_enemy_around(dst) and func_supplycheck(src,dst) == 0  and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id)
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 수송가능 거점리스트 추가
                    }
					
					
	// 병력이 8천 이하인 전방의 항구 관문으로 보급 보내라
                    					
 if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst) and 건물_관문시작 <= dst_id and dst_id < 건물_항구끝 and base2_troops <= 8000 and (1 <= enemy_weight or 1 <= user_weight) and 13000 <= pk::get_troops(src) and func_already (dst) <= 1 and no_enemy_around(dst) and func_supplycheck(src,dst) == 0  and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id)
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
                    int build_dist_a = pk::get_building_distance(a.get_id(), main.src_4th.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.src_4th.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.src_4th.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.src_4th.pos);

                    if (build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);
                    
                    return (pos_dist_a < pos_dist_b);
                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
		}





        //----------------------------------------------------------------------------------
        //  전시 관문, 항구에서 세력멸망 직전 도시로 보급대 보내기  (병력) 
        //----------------------------------------------------------------------------------




		/** 병력 있는 거점 찾기 */

		bool needEMERtroops (pk::building@ base)
		{
            pk::force@ force = pk::get_force(base.get_force_id());
			if (pk::get_city_list(force).count > 1) return false;			
			
			if (!no_enemy_around(base)) return false;

			int base_troops = pk::get_troops(base);


                        int enemy_weight = countNeighborEnemyBase(base);


	// 병력 2천 이상 있고, 당장은 안전한 관문, 항구에서 보급 보내라

			if ( 2000  <= base_troops and 건물_관문시작 <= base.get_id() and base.get_id() < 건물_항구끝 and no_enemy_around(base) and pk::get_city_list(force).count <= 1 )
				return true;




            
			return false;
		}







		/** 60% 보급 명령 */

		bool PushEMERtroops(pk::building@ base)
		{

            int reinforce_troops = pk::min(26000, pk::max(pk::get_troops(base) - 1000, int (pk::get_troops(base) * 0.60f) ));
			// 명령 가능한 무장이 있는지 확인.
			auto person_list = pk::get_idle_person_list(base);
			if (person_list.count == 0) return false;

			// 수송할 인접 거접이 있는지 확인.
			int target = getBackupBPBase(base);
			if (target == -1) return false;

			if (!enemy_approach_direct(pk::get_building(target))) return false;



            if (건물_관문시작 <= target and target < 건물_항구끝)
            reinforce_troops = pk::min(26000, pk::max(pk::get_troops(base) - 1000, int (pk::get_troops(base) * 0.60f) ));

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
            
            int unit_food = int(pk::min( 0.7f * pk::get_food(base), 2.0f * reinforce_troops));
            if (unit_food < int(0.4f * reinforce_troops)) return false;   // 병량 부족 

            float supply_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            float weapon_rate = pk::min(1.0f, pk::max(0.0f, 0.9f));
            
			// 출진 명령 정보 생성.
			pk::com_deploy_cmd_info cmd;
			@cmd.base = @base;
			cmd.type = 부대종류_수송;
			cmd.member[0] = leader.get_id();
			cmd.gold = pk::min(int(pk::get_gold(base) * 0.60f), 10000);
			cmd.food = pk::min(pk::max (5000 , unit_food), 25000);
			cmd.troops = reinforce_troops;
			int i = 0;
			for (int weapon_id = 0; weapon_id < 병기_끝; weapon_id++)
			{
                int weapon_amount = 0;
                if (weapon_id < 병기_충차)
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id) * 0.60f), 100000);
                else
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id)), 10);
                
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
            pk::say(pk::u8encode("성이 함락 직전이다!\n속히 보급을 보내겠다!"), leader);
            
            // 임시 도주 효과 ('19.3.6)
            if (거점수송_일시도주설정)
            {
                leader.skill = retreat_skill;         // 특기 복원
            }
            
            
			return true;
		}





        
		/** 가장 가깝고 위기에 빠진 아군 도시에 보급을 보냄 */

        pk::building@ src_em;
		int getBackupBPBase(pk::building@ src)
		{
			int best_dst = -1;
			int best_distance = 0;
            int src_id = src.get_id();
            pk::list<pk::building@> dst_list; 
            @src_em = @src;



            
            int search_base = 건물_도시끝;
            if      (거점수송_거점검색모드 == 0) search_base = 건물_도시끝;
            else if (거점수송_거점검색모드 == 1) search_base = 건물_거점끝;
            
            pk::force@ force = pk::get_force(src.get_force_id());
            
			// 수송 거점 검색

                for (int i = 0; i < search_base; i++)
                {
                    pk::building@ dst = pk::get_building(i);
                    int dst_id = dst.get_id();
			int base2_troops = pk::get_troops(dst);

            int max_distance = (dst_id >= 건물_도시끝)? 2 : 2;


                    // 도시거리
                    int city_dist = -1;
                    if (dst_id < 건물_도시끝 and src_id < 건물_도시끝)
                        city_dist = pk::get_city_distance(dst_id, src_id);
                    
                    // 거점거리
                    int base_dist = pk::get_building_distance(dst_id, src_id, src.get_force_id());
                    
                    // 거리 조건 만족 시
                    if ( (0 <= base_dist and base_dist <= max_distance) or city_dist == 1)
                    {


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
                                                if (distance <= 3)
						{
							force_units7++;
						}
					}


					else
					{
					}
				}
			}


                        int enemy_weight = countNeighborEnemyBase(dst);




           // 병력 8천 이하에 위기의 도시로 보급 보내라

       if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst) and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and base2_troops <= 8000 and 1 <= enemy_units3 and 0 == enemy_units1 and force_units7 == 0 and func_already (dst) <= 3 and 0 < enemy_weight )
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
                    int build_dist_a = pk::get_building_distance(a.get_id(), main.src_em.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.src_em.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.src_em.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.src_em.pos);

                    if (build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);
                    
                    return (pos_dist_a < pos_dist_b);
                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
		}











        //----------------------------------------------------------------------------------
        //  전시 관문, 항구에서 세력멸망 직전 도시로 지원군 파병
        //----------------------------------------------------------------------------------





		/** 병력 있는 거점 찾기 */

		bool needEMER1troops (pk::building@ base)
		{
            pk::force@ force = pk::get_force(base.get_force_id());			
			if (pk::get_city_list(force).count > 1) return false;			
			
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


                        int enemy_weight = countNeighborEnemyBase(base);


	// 병력 2천 이상 있고, 당장은 안전한 관문, 항구에서 보급 보내라

			if ( 2000  <= base_troops and 건물_관문시작 <= base.get_id() and base.get_id() < 건물_항구끝 and pk::get_city_list(force).count <= 1  )
				return true;



            
			return false;
		}







		/** 전투부대 파견 */

		bool PushEMER1troops(pk::building@ base)
		{
			// 명령 가능한 무장이 있는지 확인.
			auto person_list = pk::get_idle_person_list(base);
			if (person_list.count == 0) return false;

			// 수송할 인접 거접이 있는지 확인.
			int target = getUrgentBaseEM(base);
			if (target == -1) return false;

			if (!enemy_approach_direct(pk::get_building(target))) return false;

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
            int reinforce_troops = pk::min(pk::get_command(leader), pk::max(1000, pk::get_troops(base) - 1000));

            // 최적 무기 선택
            int ground_weapon_id = 병기_검;
            int water_weapon_id = 병기_주가;
            int unit_troops = reinforce_troops;
            
            // 육상 무기 선택
            get_ground_weaponEM(base, leader, reinforce_troops, ground_weapon_id, unit_troops);
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
            int unit_food = int(pk::min( 0.7f * pk::get_food(base), 2.0f * unit_troops));
            if (unit_food < int(0.4f * unit_troops)) return false;   // 병량 부족
            
            // 출진 명령

                // 출진 명령 정보 생성.
                pk::com_deploy_cmd_info cmd;
                @cmd.base = @base;
                cmd.type = 부대종류_전투;
                cmd.member[0] = leader.get_id();
                cmd.gold = (pk::get_gold(base) >= 1000) ? int(pk::min(1000.f, pk::get_gold(base) * 0.1f)) : 0;
                cmd.troops = pk::max(1, unit_troops);
                cmd.weapon_id[0] = ground_weapon_id;
                cmd.weapon_id[1] = water_weapon_id;
                cmd.weapon_amount[0] = unit_troops;
                cmd.weapon_amount[1] = (water_weapon_id == 병기_주가)? 0 : 1;
                cmd.food = unit_food;

                cmd.order = 부대임무_이동;
                cmd.target_pos = pk::get_building(target).get_pos();  // 목표는 전투중인 거점

	if (대사표시_설정) 
                pk::say(pk::u8encode("아군 거점이 절체절명!\n전투병들을 투입하라!"), leader);																											  

                // 출진.
                int unit_id = pk::command(cmd);
                if (unit_id != -1)
                    pk::get_unit(unit_id).action_done = true;

            
            return true;
        }
        
  
        
        //----------------------------------------------------------------------------------
        
        // 무기 선택 함수
        void get_ground_weaponEM(pk::building@ base, pk::person@ leader, int troops_max, int &out weapon_sel, int &out troops_sel)
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


        pk::building@ src_kEM;
		int getUrgentBaseEM(pk::building@ src)
		{
			int best_dst = -1;
			int best_distance = 0;


            int src_id = src.get_id();
            pk::list<pk::building@> dst_list; 
            @src_kEM = @src;




            int search_base = 건물_도시끝;
            if      (거점수송_거점검색모드 == 0) search_base = 건물_도시끝;
            else if (거점수송_거점검색모드 == 1) search_base = 건물_거점끝;
            
            pk::force@ force = pk::get_force(src.get_force_id());
            
            
			// 수송 거점 검색

                for (int i = 0; i < search_base; i++)
                {
                    pk::building@ dst = pk::get_building(i);
                    int dst_id = dst.get_id();
			int base2_troops = pk::get_troops(dst);


            int max_distance = (dst_id >= 건물_도시끝)? 2 : 2;





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
                    if ( (0 <= base_dist and base_dist <= max_distance) or city_dist == 1)
                    {



           // 병력 1만2천 이하거나 항관보다 병력 적은 위기의 도시로 보급 보내라
                        int enemy_weight = countNeighborEnemyBase(dst);
       if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst) and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and (base2_troops <= 12000 or base2_troops <= pk::get_troops(src)) and 1 <= enemy_units1 and  force_units7 <= 1 and 0 < enemy_weight )
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
                    int build_dist_a = pk::get_building_distance(a.get_id(), main.src_kEM.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.src_kEM.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.src_kEM.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.src_kEM.pos);

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



        // ***** 주변 유저 거점 수 확인 ***** //
        int countNeighborUserBase(pk::building@ src)
        {
            int weight = 0;
            int troops = 0;
            for (int i = 0; i < 건물_거점끝; i++)
			{
                pk::building@ dst = pk::get_building(i);
                int src_id = src.get_id();
                int dst_id = dst.get_id();
                
                if (src_id != dst_id and pk::is_neighbor_base(src_id, dst_id) and !pk::is_enemy(src, dst) and !src.is_player() and dst.is_player() )
                    troops += pk::get_troops(dst);
            }
            
            weight = int(troops / 3000);
            return weight;
        }



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






         // 목표 거점으로 이미 출발한 부대 숫자 체크, masterpiecek님의 AI_도시물자수송.cpp﻿를 참조했습니다.


	 int func_already(pk::building@ building)
		{
			int already = 0;
			for (int unit_id = 0; unit_id < 부대_끝; unit_id++)
			{
				pk::unit@ unit = pk::get_unit(unit_id);
			if (building.get_force_id() == -1) continue;
			if (unit.get_force_id() == -1) continue;
				if ( pk::is_alive(unit) and 3000 <= unit.troops  and unit.get_force_id() == building.get_force_id() and unit.target == building.get_id()) 

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





         // 해당거점으로 특정공급 거점에서 이미 출진한 전투 부대 숫자 체크. masterpiecek님의 AI_도시물자수송.cpp﻿를 참조했습니다.

	 int battle_unit_check(pk::building@ building, pk::building@ building2)
		{
			int unit_check = 0;
			for (int unit_id = 0; unit_id < 부대_끝; unit_id++)
			{
				pk::unit@ unit = pk::get_unit(unit_id);
                pk::building@ base = pk::get_building(pk::get_service(unit));

			if (building.get_force_id() == -1) continue;
			if (building2.get_force_id() == -1) continue;
			if (unit.get_force_id() == -1) continue;
		if ( pk::is_alive(unit) and unit.type == 부대종류_전투 and unit.get_force_id() == building.get_force_id() and unit.get_force_id() == building2.get_force_id() and base.get_id() == building.get_id()  and unit.target == building2.get_id() and 3000 <= unit.troops ) 

				unit_check++;
			}

			return unit_check;
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
		
		
         //  거리에 따른 인근 동맹상태의 유저 도시 숫자 체크, masterpiecek님의 AI_도시물자수송.cpp﻿를 참조했습니다.

		int func_user_city_count(pk::city@ city, int distance)
		{
			int user_city_count = 0;
			for (int i = 0; i < 도시_끝; i++)
			{
				pk::city@ usercity = pk::get_city(i);
				int city_distance = pk::get_city_distance(city.get_id(), i);

				if (pk::is_alive(usercity) and city.get_id() != i and usercity.is_player() and !pk::is_enemy(city, usercity) and city_distance <= distance) 

				user_city_count++;
																	  										  				   
			}

			return user_city_count;
		}		
				
		

        // 전투 지역 내 적과 아군 병력 격차 //
        int gap_troops(pk::building@ dst)
        {
						   
            int troops = 0;

			// 근접한 적 부대 수
			int enemy_units1 = 0;
			int enemy_troops1 = 0;


			int enemy_units2 = 0;
			int enemy_troops2 = 0;

			// 3칸 이내 적 부대 수
			int enemy_units3 = 0;
			// 3칸 이내 적 병력 수
			int enemy_troops3 = 0;



			int force_units7 = 0;
			int force_troops3 = 0;


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


					else if (dst.get_force_id() == unit.get_force_id() and unit.type == 부대종류_전투)
					{
                                                if (distance <= 7)
						{
							force_units7++;
							force_troops3 += unit.troops;
						}
					}


					else
					{
					}
				}
			}
            
            troops = enemy_troops3 - (pk::get_troops(dst) + force_troops3);
            return troops;
        }



         // 목표 거점으로 이미 출발한 지원군 병력 합산, masterpiecek님의 AI_도시물자수송.cpp﻿를 참조했습니다.


	 int troops_already(pk::building@ building)
		{
			int already = 0;
			for (int unit_id = 0; unit_id < 부대_끝; unit_id++)
			{
				pk::unit@ unit = pk::get_unit(unit_id);
			if (building.get_force_id() == -1) continue;
			if (unit.get_force_id() == -1) continue;
				if ( pk::is_alive(unit) and 1 <= unit.troops  and unit.get_force_id() == building.get_force_id() and unit.target == building.get_id()) 

				already += unit.troops;
			}

			return already;
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

        // ***** 적이 아군 거점에 다가오는가? (항관이 있어서 바로 못오는 경우까지 감안)***** //
        bool enemy_approach_direct(pk::building@ base)
        {
                pk::array<pk::point> range = pk::range(base.pos, 1, 15);  // 거점 주변 검색
                for (int i = 0; i < int(range.length); i++)
                {
				auto unit_e = pk::get_unit(range[i]);
				if (pk::is_alive(unit_e) and pk::is_enemy(base, unit_e))
				{	
                    pk::building@ base_t = get_neighbor_enemy_base_direct(unit_e);	
				if (pk::is_alive(base_t) and base_t.get_id() == base.get_id())					
	            return true;
                }
                }				
            
	return false;
        }

        //---------------------------------------------------------------------------------------
        //---------------------------------------------------------------------------------------
        // 적부대가 우리 거점 경계 범위 까지 올 수 있는 상황 (항관이 있어서 바로 못오는 경우까지 감안)
        pk::building@ get_neighbor_enemy_base_direct(pk::unit@ unit)
        {
            pk::array<pk::point> arr_range = pk::get_movable_pos(unit);  // 이동가능좌표
            for (int j = 0; j < int(arr_range.length); j++)
            {
                pk::point pos = arr_range[j];				

                pk::array<pk::point> arr_t = pk::range(pos, 1, 2);   // 주변좌표
                pk::array<pk::point> arr_tm = pk::range(unit.pos, 1, 2);   // 주변좌표	
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