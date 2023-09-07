/*
제작 by 일송정

본 스크립트는 기마책사님이 제작하신 거점원군.cpp와 기마책사님이 수정하신 거점철수.cpp의 상당 부분을 차용하고 있음을 알려드립니다. 
기마책사님께 감사드립니다.

*/

namespace 계륵6항구_장수탈출utf8
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

			// 플레이어 조종 거점, 이민족 세력은 제외.
			if (pk::is_normal_force(force_id))
			{
				for (int i = 0; i < 건물_거점끝; i++)
				{
					auto base = pk::get_building(i);


                    if (!pk::is_player_controlled(base) and base.get_force_id() == force_id and needPersonSupport(base))
                        PushPersonSupport(base);

				}
			}

			// 이전 핸들러가 있다면 체인.
			if (prev_callback_ !is null)
				return prev_callback_(force);
			return false;
		}




        //----------------------------------------------------------------------------------
        //  6항구 탈출
        //----------------------------------------------------------------------------------


        /** 거점이란 거점은 다 대상, 6항구에서 장수 탈출시키기 **/
        bool needPersonSupport(pk::building@ base)
		{

            if (!pk::is_alive(base)) return false;

			if (base.get_force_id() == -1) return false;

			pk::force@ force = pk::get_force(base.get_force_id());
			int force_id = force.get_id();



			// 플레이어 조종 거점, 이민족 세력은 제외하고 거점이란 거점은 다 대상
			if ( pk::is_normal_force(force_id))
			{
			if (건물_파양항 != base.get_id() and 건물_노릉항 != base.get_id() and 건물_서하항 != base.get_id() and 건물_하양항 != base.get_id() and 건물_해현항 != base.get_id() and 건물_강도항 != base.get_id()) return false;	
            
            int count = pk::get_person_list(base, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반)).count;
			if (count == 0) return false;
			
			// 6항구에 장수가 있으면 내보내야			
			
            if ( base.get_id() < 건물_거점끝 and (건물_파양항 == base.get_id() or 건물_노릉항 == base.get_id() or 건물_서하항 == base.get_id() or 건물_하양항 == base.get_id() or 건물_해현항 == base.get_id() or 건물_강도항 == base.get_id()) and count > 0) 
                return true;
            }        
            return false;
        }
        
        // ***** 무장 지원 명령 ***** //
        bool PushPersonSupport(pk::building@ src_base)
        {
            // 무장을 보낼 인근 아군 거점 찾기
			int target = getNearestDST(src_base);
			if (target == -1) return false;
            
            // 탈출 장수들 갈 곳
            pk::building@ dst_base = pk::get_building(target);
            
			pk::force@ force = pk::get_force( src_base.get_force_id());
 
            auto person_list = pk::get_idle_person_list(src_base);
            if (person_list.count == 0 ) return false;   // 무장 부족
          
            // 통솔+무력 높은 순으로 정렬.
			person_list.sort(function(a, b)
			{
				return (a.stat[무장능력_무력] + a.stat[무장능력_통솔]) > (b.stat[무장능력_무력] + b.stat[무장능력_통솔]);
			});
            
            // 소환할 무장수
            int max = pk::max( 1 , person_list.count );
            
            // 소환 대상 무장
            pk::list<pk::person@> actors;
            for (int i = 0; i < max; i++)
            {
            if (pk::is_unitize(person_list[i])) continue;
            if (pk::is_absent(person_list[i])) continue;
            if (person_list[i].order != -1) continue;					
            if (person_list[i].get_force_id() != src_base.get_force_id()) continue; 
            if (person_list[i].get_force_id() != dst_base.get_force_id()) continue; 
            if (person_list[i].location != person_list[i].service) continue;
            if (person_list[i].action_done) continue;
            if (pk::is_absent(person_list[i])) continue;
            if (person_list[i].mibun == 신분_포로) continue;
            if (person_list[i].mibun == 신분_재야) continue;

            if (!pk::is_unitize(person_list[i]) and !pk::is_absent(person_list[i])
                and person_list[i].order == -1 and person_list[i].get_force_id() == src_base.get_force_id() and person_list[i].get_force_id() == dst_base.get_force_id() 
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
        pk::building@ src_port;		
        int getNearestDST(pk::building@ src)
		{
			int best_dst = -1;
			int best_distance = 0;

            int src_id = src.get_id();			
            pk::list<pk::building@> dst_list; 	
            @src_port = @src;			
            
			// 거점까지 확인.
			for (int i = 0; i < 건물_거점끝; i++)
			{
                    pk::building@ dst = pk::get_building(i);
                    int dst_id = dst.get_id();					
                
                    if (src_id != dst_id and src.get_force_id() == dst.get_force_id())
                {
                    int distance = pk::get_building_distance(src_id, dst_id, src.get_force_id());

                    // 도시거리
                    int city_dist = -1;
                        city_dist = pk::get_city_distance(pk::get_city_id(src.pos), pk::get_city_id(dst.pos));
                    
                    auto person_list = pk::get_idle_person_list(src);
                   
                    int max_distance = 3;
                    if ((0 <= distance and distance <= max_distance) or city_dist <= 3)
                    {


			pk::force@ force = pk::get_force(dst.get_force_id());

if (person_list.count > 0 and pk::is_alive(src) and pk::is_alive(dst) and src_id != dst_id and src.get_force_id() == dst.get_force_id() and (건물_파양항 == src_id or 건물_노릉항 == src_id or 건물_서하항 == src_id or 건물_하양항 == src_id or 건물_해현항 == src_id or 건물_강도항 == src_id ) )
                     {
            if ( dst_id < 건물_거점끝 and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id) 			
                        {							
                        best_dst = dst_id;
                        dst_list.add(dst);  // 거점리스트 추가
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
                    int build_dist_a = pk::get_building_distance(a.get_id(), main.src_port.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.src_port.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.src_port.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.src_port.pos);
                    
                    if (build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);
                    
                    return (pos_dist_a < pos_dist_b);
                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
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
            
            weight = int(troops / 3000);
            return weight;
        }



         //  거리에 따른 인근 적대 도시 숫자 체크, masterpiecek님의 AI_도시물자수송.cpp﻿를 참조했습니다.

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