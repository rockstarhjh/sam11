/*
제작 by 일송정

본 스크립트는 기마책사님이 제작하신 거점원군.cpp와 기마책사님이 수정하신 거점철수.cpp의 상당 부분을 차용하고 있음을 알려드립니다. 
기마책사님께 감사드립니다.

*/

namespace 공성전utf8
{

	// ==================CUSTOMIZE =================

        const int  출동부대수_한도 = 3;

		const bool 대사표시_설정 = false;   
	
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


                    if ( ( !force.is_player() and base.get_force_id() == force_id and needCastleAttack(base) ) or ( force.is_player() and pk::is_normal_force(force_id) and pk::is_alive(district) and !pk::is_player_controlled(base) and base.get_force_id() == force_id and needCastleAttack(base) and district.attack ) )

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
                
                int max_count = pk::max(1, pk::min(출동부대수_한도, 11));
               
                bool cmd = false;
                while(push_count < max_count)
                {
                    push_count += 1;
                    cmd = (PushCastleAttack(base) or cmd);  
                }

        }

        //----------------------------------------------------------------------------------
        //  적 공격 시 적 거점에 적부대가 없으면 공성 작전
        //----------------------------------------------------------------------------------




		/** 병력 있는 거점 찾기 */

		bool needCastleAttack (pk::building@ base)
		{
            if ( count_War_Zone(base) == 0 ) return false;				
			
			// 근접한 적 부대 수
			int enemy_units1 = 0;
			// 3칸 이내 적 부대 수
			int enemy_units3 = 0;
			// 3칸 이내 적 병력 수
			int enemy_troops3 = 0;



			int force_units7 = 0;



			auto range = pk::range(base.get_pos(), 1, 7);
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
						}
						if (distance <= 7)
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

			if (enemy_units1 >= 10)  // 거점 포위 상태로 작전 불가
				return false;
			int base_troops = pk::get_troops(base);


	// 병력 1만2천명 이상 있고, 적 침공에 견딜 수 있는 관문, 항구에서 공성 보내라

			if ( 12000 <= base_troops and 건물_관문시작 <= base.get_id() and base.get_id() < 건물_항구끝 and enemy_troops3 * 5.0f <= base_troops )
				return true;


	// 병력 1만2천명 이상 있고, 적 침공에 견딜 수 있는 도시에서 공성 보내라

			if ( 12000 <= base_troops and 건물_도시시작 <= base.get_id() and base.get_id() < 건물_도시끝 and enemy_troops3 * 5.0f <= base_troops )
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
              if ( (0 <= base_dist and base_dist <= max_distance) or city_dist == 1)  
                  {
												          
                if (src_id != dst_id and pk::is_enemy(src, dst) and pk::is_alive(src) and pk::is_alive(dst))
                     {
																											
                      if (건물_도시시작 <= dst_id and dst_id < 건물_항구끝 and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id)
																						  
                            {
		                    War_Zone++;
                            }

                       }

                  }

	
 
               } 
            

            return War_Zone;
        }



		/** 공성 부대 파견 */

		bool PushCastleAttack(pk::building@ base)
		{
			// 명령 가능한 무장이 있는지 확인.
			auto person_list = pk::get_idle_person_list(base);
			if (person_list.count == 0) return false;

			// 인접 거접이 있는지 확인.
			int target = getSiegedBase(base);
			if (target == -1) return false;

            pk::list<pk::person@> actors;
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
            
            // 통솔+무력 높은 순으로 정렬.
			actors.sort(function(a, b)
			{
                    bool a_Siege = (pk::has_skill(a, 특기_공신) or pk::has_skill(a, 특기_공성) or pk::has_skill(a, 특기_사정));
                    bool b_Siege = (pk::has_skill(b, 특기_공신) or pk::has_skill(b, 특기_공성) or pk::has_skill(b, 특기_사정));
                    if ( a_Siege and !b_Siege) return true;   
                    if (!a_Siege and  b_Siege) return false;   				

                    // 병기 적성
                    if (a.tekisei[병종_병기] != b.tekisei[병종_병기]) return (a.tekisei[병종_병기] > b.tekisei[병종_병기]);
							                               
				return (a.stat[무장능력_무력] + a.stat[무장능력_통솔]) > (b.stat[무장능력_무력] + b.stat[무장능력_통솔]);
			});
            pk::person@ leader = pk::get_person(actors[0].get_id());
            
            // 원군 병력 산정 : 기준 병력 초과분, 지휘가능병력 확인
            int reinforce_troops = pk::min(pk::get_command(leader), pk::max(4999, pk::get_troops(base) - 7000));
			if (reinforce_troops < 4000 ) return false;			

            // 최적 무기 선택
            int ground_weapon_id = 병기_검;
            int water_weapon_id = 병기_주가;
            int unit_troops = reinforce_troops;
            
            // 육상 무기 선택
            get_siege_weapon(base, pk::get_building(target), leader, reinforce_troops, ground_weapon_id, unit_troops);
            if (ground_weapon_id == 0) return false;    // 병기 부족
            

            // 병량 계산
            int unit_food = int(pk::min( 0.35f * pk::get_food(base), 2.0f * reinforce_troops));
            if (unit_food < int(0.9f * reinforce_troops)) return false;   // 병량 부족
            if (pk::get_food(base) - unit_food < (pk::get_troops(base) - unit_troops) * 0.6f ) return false;   // 거점 병량 부족

            
            // 출진 명령

                // 출진 명령 정보 생성.
                pk::com_deploy_cmd_info cmd;
                @cmd.base = @base;
                cmd.type = 부대종류_전투;
                cmd.member[0] = leader.get_id();
                cmd.gold = (pk::get_gold(base) >= 1000) ? int(pk::min(1000.f, pk::get_gold(base) * 0.1f)) : 0;
                cmd.troops = pk::max(4999, unit_troops);
                cmd.weapon_id[0] = ground_weapon_id;
                cmd.weapon_id[1] = water_weapon_id;
                cmd.weapon_amount[0] = 1;
                cmd.weapon_amount[1] = (water_weapon_id == 병기_주가)? 0 : 1;
                cmd.food = unit_food;

                cmd.order = 부대임무_공격;
                cmd.target_pos = pk::get_building(target).get_pos();  // 목표는 전투중인 거점

	if (대사표시_설정) 
                pk::say(pk::u8encode("공성전에는 공성병기가 제격!"), leader);																											  

                // 출진.
                int unit_id = pk::command(cmd);
                if (unit_id != -1)
                    pk::get_unit(unit_id).action_done = true;

            
            return true;
        }
        
    
        
        //----------------------------------------------------------------------------------
        
        // 무기 선택 함수
        void get_siege_weapon(pk::building@ base, pk::building@ dst, pk::person@ leader, int troops_max, int &out weapon_sel, int &out troops_sel)
        {
            int troops_min = 4999;
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

                    if (건물_관문시작 <= dst_id and dst_id < 건물_항구끝 and ( Siege_weapon_Short_units3 >= 2 or func_already_Short(dst) >= 2 ))
                       {
                        id_1 = 병기_정란;
                        id_2 = 병기_투석;
                        }


            // 목적지가 항관인데 단거리 공성병기가 2대 미만 정도만이 향하고 있거나 이미 가 있으면 공성병기 아무나 보내라

                    else if (건물_관문시작 <= dst_id and dst_id < 건물_항구끝 and Siege_weapon_Short_units3 < 2 and func_already_Short(dst) < 2 )
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

                    if (troops_max == 5000)
                    {

                        troops_sel = pk::min(4999, troops_max);
                    }

                    if (troops_max == 6000)
                    {

                        troops_sel = pk::min(5999, troops_max);
                    }

                    if (troops_max == 7000)
                    {

                        troops_sel = pk::min(6999, troops_max);
                    }

                    if (troops_max == 8000)
                    {

                        troops_sel = pk::min(7999, troops_max);
                    }

                    if (troops_max == 9000)
                    {

                        troops_sel = pk::min(8999, troops_max);
                    }


                    if (troops_max == 10000)
                    {

                        troops_sel = pk::min(9999, troops_max);
                    }

                    if (troops_max == 11000)
                    {

                        troops_sel = pk::min(10999, troops_max);
                    }

                    if (troops_max == 12000)
                    {

                        troops_sel = pk::min(11999, troops_max);
                    }


                    if (troops_max == 13000)
                    {

                        troops_sel = pk::min(12999, troops_max);
                    }

                    if (troops_max == 14000)
                    {

                        troops_sel = pk::min(13999, troops_max);
                    }

                    if (troops_max == 15000)
                    {

                        troops_sel = pk::min(14999, troops_max);
                    }

                    }
                }

            
            if (weapon_sel == 0)
            {
                troops_sel = troops_min;
            }
        }
        
        //----------------------------------------------------------------------------------



        
		/** 가장 가깝고 포위 속에 있는 적도시 */


        pk::building@ src_c;
		int getSiegedBase(pk::building@ src)
		{
			int best_dst = -1;
			int best_distance = 0;


            int src_id = src.get_id();
            pk::list<pk::building@> dst_list; 
            @src_c = @src;

            
            pk::force@ force = pk::get_force(src.get_force_id());
            
            
			// 거점 검색

                for (int i = 0; i < 건물_거점끝; i++)
                {
                    pk::building@ dst = pk::get_building(i);
                    int dst_id = dst.get_id();
			int base2_troops = pk::get_troops(dst);



            int max_distance = (dst_id >= 건물_도시끝)? 2 : 1;


			// 근접한 적 부대 수
			
			int enemy_units0 = 0;
			int enemy_troops0 = 0;			
			
			int enemy_units1 = 0;
			int enemy_troops1 = 0;

			// 3칸 이내 적 부대 수
			int enemy_units3 = 0;

			// 3칸 이내 적 병력 수
			int enemy_troops3 = 0;

			int force_units7 = 0;

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
						if (distance <= 10)
						{
							enemy_units3++;
							enemy_troops3 += unit.troops;
						}
					}

					else if (pk::is_enemy(dst, unit) and src.get_force_id() == unit.get_force_id() and unit.type == 부대종류_전투 and ( unit.weapon == 병기_충차 or unit.weapon == 병기_정란 or unit.weapon == 병기_투석 or unit.weapon == 병기_목수 ) )
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
         // 출진하려는 거점의 병력이 공격 대상 거점을 제외한 인접한 적의 거점 병력 총합의 50% 이상은 되어야 함

if (src_id != dst_id and src.get_force_id() != dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst) and (EnemyBase_troops(src) - pk::get_troops(dst)) * 0.5f < pk::get_troops(src) )
          {

   // 교전 중이면서 방어 부대 없는 도시에 병력 보낸다
                    
if (건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and  pk::is_enemy(src, dst)  and  enemy_units1 >= 2 and force_units7 <= 1  and func_already (dst) <= 12 and Siege_weapon_units3 <= 12)
                       {
                           best_dst = dst_id;
                           dst_list.add(dst);  // 가능 거점리스트 추가
                        }




  // 교전 중이면서 정문 진입로가 확보된 관문에 병력 보낸다

if (건물_관문시작 <= dst_id and dst_id < 건물_관문끝 and  pk::is_enemy(src, dst) and (enemy_units0 >= 1 or !close_combat(dst)) and  enemy_units1 >= 2 and (enemy_units3 >= 4 or force_units7 <= 1)  and func_already (dst) <= 6 and Siege_weapon_units3 <= 6)
                       {
                           best_dst = dst_id;
                           dst_list.add(dst);  // 가능 거점리스트 추가
                        }



  // 교전 중이면서 정문 진입로가 확보된 항구에 병력 보낸다

  if (건물_항구시작 <= dst_id and dst_id < 건물_항구끝 and  pk::is_enemy(src, dst) and (enemy_units0 >= 1 or !close_combat(dst)) and enemy_units1 >= 2 and (enemy_units3 >= 4 or force_units7 <= 1) and enemy_units3 <= 11 and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id and Siege_weapon_units3 <= 6)
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
                    int build_dist_a = pk::get_building_distance(a.get_id(), main.src_c.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.src_c.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.src_c.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.src_c.pos);

                    if (build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);
                    
                    return (pos_dist_a < pos_dist_b);
                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
		}



            // 공격 대상 거점으로 미리 출진한 병기부대 숫자 체크, masterpiecek님의 AI_도시물자수송.cpp﻿를 참조했습니다.

	 int func_already(pk::building@ building)
		{
			int already = 0;
			for (int unit_id = 0; unit_id < 부대_끝; unit_id++)
			{
				pk::unit@ unit = pk::get_unit(unit_id);
			if (building.get_force_id() == -1) continue;
			if (unit.get_force_id() == -1) continue;
				if ( pk::is_alive(unit) and unit.type == 부대종류_전투 and (병기_충차 <= unit.weapon and unit.weapon <= 병기_목수) and unit.get_force_id() != building.get_force_id() and unit.target == building.get_id()) 

				already++;
			}

			return already;
		}



            // 공격 대상 거점으로 미리 출진한 단거리 공격 병기부대 숫자 체크, masterpiecek님의 AI_도시물자수송.cpp﻿를 참조했습니다.

	 int func_already_Short(pk::building@ building)
		{
			int already = 0;
			for (int unit_id = 0; unit_id < 부대_끝; unit_id++)
			{
				pk::unit@ unit = pk::get_unit(unit_id);
			if (building.get_force_id() == -1) continue;
			if (unit.get_force_id() == -1) continue;
				if ( pk::is_alive(unit) and unit.type == 부대종류_전투 and (unit.weapon == 병기_충차 or unit.weapon == 병기_목수) and unit.get_force_id() != building.get_force_id() and unit.target == building.get_id()) 

				already++;
			}

			return already;
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

	};

	Main main;
}