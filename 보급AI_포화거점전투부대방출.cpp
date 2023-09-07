﻿/*
제작 by 일송정

본 스크립트는 기마책사님이 제작하신 거점원군.cpp와 기마책사님이 수정하신 거점철수.cpp의 상당 부분을 차용하고 있음을 알려드립니다. 
기마책사님께 감사드립니다.

*/

namespace 포화거점전투부대방출
{

	// ==================CUSTOMIZE =================

        const int  출동부대수_한도 = 5;

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


                    if ( ( !force.is_player() and base.get_force_id() == force_id and needWanderers(base) and pk::get_elapsed_months() > 3 ) or ( force.is_player() and pk::is_alive(district) and !pk::is_player_controlled(base) and base.get_force_id() == force_id and needWanderers(base) and pk::get_elapsed_months() > 3 and district.attack ) )

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
                while(push_count < max_count and pk::get_max_troops(base) * 0.5f < pk::get_troops(base) )
                {
                    push_count += 1;
                    cmd = (PushWanderers(base) or cmd);  
                }

        }



        //----------------------------------------------------------------------------------
        //  포화 거점에서 전투 부대 방출
        //----------------------------------------------------------------------------------




		/** 병력 있는 거점 찾기 */

		bool needWanderers(pk::building@ base)
		{

			int base_troops = pk::get_troops(base);
			pk::city@ city_a = pk::get_city(pk::get_city_id(base.pos));


	// 병력 77% 이상 있는 관문, 항구에서 파병 보내라

			if ( pk::get_max_troops(base) * 0.77f <= base_troops and 건물_관문시작 <= base.get_id() and base.get_id() < 건물_항구끝 )
				return true;


	// 병력 77% 이상 있는 도시에서 파병 보내라

			if ( pk::get_max_troops(base) * 0.77f <= base_troops and 건물_도시시작 <= base.get_id() and base.get_id() < 건물_도시끝 )
				return true;


            
			return false;
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

                
				return (a.stat[무장능력_무력] + a.stat[무장능력_통솔]) > (b.stat[무장능력_무력] + b.stat[무장능력_통솔]);
			});
            pk::person@ leader = pk::get_person(actors[0].get_id());
            
            // 원군 병력 산정 : 기준 병력 초과분, 지휘가능병력 확인
            int reinforce_troops = pk::min(pk::get_command(leader), pk::max(int (pk::get_troops(base) * 0.35f) , pk::get_troops(base) - 10000));

            // 최적 무기 선택
            int ground_weapon_id = 병기_검;
            int water_weapon_id = 병기_주가;
            int unit_troops = reinforce_troops;
            
            // 육상 무기 선택
            get_ground_weapon1(base, leader, reinforce_troops, ground_weapon_id, unit_troops);
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
            int unit_food = int(pk::min( 0.5f * pk::get_food(base), 2.0f * unit_troops));
            if (unit_food < int(0.5f * unit_troops)) return false;   // 병량 부족


            
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
                pk::say(pk::u8encode("거점이 포화상태다!\n여유 병력들은 이동하라!"), leader);																											  

                // 출진.
                int unit_id = pk::command(cmd);
                if (unit_id != -1)
                    pk::get_unit(unit_id).action_done = true;

            
            return true;
        }
        
 
        
        //----------------------------------------------------------------------------------
        
        // 무기 선택 함수
        void get_ground_weapon1(pk::building@ base, pk::person@ leader, int troops_max, int &out weapon_sel, int &out troops_sel)
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


        pk::building@ src_wd;
		int getUrgentBase1(pk::building@ src)
		{
			int best_dst = -1;
			int best_distance = 0;


            int src_id = src.get_id();
            pk::list<pk::building@> dst_list; 
            @src_wd = @src;

            
            pk::force@ force = pk::get_force(src.get_force_id());
            
            
			// 파병 거점 검색

                for (int i = 0; i < 건물_거점끝; i++)
                {
                    pk::building@ dst = pk::get_building(i);
                    int dst_id = dst.get_id();
			int base2_troops = pk::get_troops(dst);



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



         // 적 거점에 공격 보낸다

                       if (src_id != dst_id and src.get_force_id() != dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst) and dst_id < 건물_거점끝  and  pk::is_enemy(src, dst) )
                       {
                           best_dst = dst_id;
                           dst_list.add(dst);  // 파병가능 거점리스트 추가
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
                    int build_dist_a = pk::get_building_distance(a.get_id(), main.src_wd.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.src_wd.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.src_wd.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.src_wd.pos);

                    if (build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);
                    
                    return (pos_dist_a < pos_dist_b);
                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
		}


         // 거리에 따른 인근 적대 도시 숫자 체크, masterpiecek님의 AI_도시물자수송.cpp﻿를 참조했습니다.

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





	};

	Main main;
}