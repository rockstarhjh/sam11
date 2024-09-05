/*
제작 by 일송정

본 스크립트는 기마책사님이 제작하신 거점원군.cpp와 기마책사님이 수정하신 거점철수.cpp의 상당 부분을 차용하고 있음을 알려드립니다. 
기마책사님께 감사드립니다.

*/

namespace 매월_인사이동utf8
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

                // 플레이어, 이민족 세력은 제외.
                if (!force.is_player() and pk::is_normal_force(force_id) and pk::get_elapsed_months() > 3)
			{
				for (int i = 0; i < 건물_거점끝; i++)
				{
					auto base = pk::get_building(i);

                    if (base.get_force_id() == force_id and (pk::get_month() == 1 or pk::get_month() == 6) and (pk::get_day() == 1 or pk::get_day() == 21))
                        Pushkunshu(base);


                    if (base.get_force_id() == force_id and needValor(base) and (pk::get_day() == 1))
                        PushValor(base);

                    if (base.get_force_id() == force_id and needTactician(base) and (pk::get_day() == 11))
                        PushTactician(base);



                    if (base.get_force_id() == force_id and needREAR(base) and (pk::get_day() == 1 or pk::get_day() == 21))
                        PushREAR(base);

                    if (base.get_force_id() == force_id and needGARRISON(base) and (pk::get_day() == 1 or pk::get_day() == 21))
                        PushGARRISON(base);

                    if (base.get_force_id() == force_id and needFRONT(base) and (pk::get_day() == 1 or pk::get_day() == 11))
                        PushFRONT(base);

                    if (base.get_force_id() == force_id and needUnitleader(base) and (pk::get_day() == 1 or pk::get_day() == 21))
                        PushUnitleader(base);




				}
			}

			// 이전 핸들러가 있다면 체인.
			if (prev_callback_ !is null)
				return prev_callback_(force);
			return false;
		}



        //----------------------------------------------------------------------------------
        //  세력 도시 5개 이상이면 군주를 후방 도시로
        //----------------------------------------------------------------------------------

        
        // ***** 무장 지원 명령 ***** //
        pk::building@ src_kunshu;		
        bool Pushkunshu(pk::building@ base)
        {
            @src_kunshu = @base;
			
			pk::force@ force = pk::get_force(base.get_force_id());
	        pk::person@ kunshu = pk::get_person(pk::get_kunshu_id(base));

            pk::building@ kunshu_base = pk::get_building(kunshu.service);

            // 군주 소속 거점은 베이스와 동일
			if (base.get_id() != kunshu_base.get_id()) return false;
			
            // 군주 소재지와 소속지가 같아야			
            if (kunshu.location != kunshu.service) return false;

            // 군주 미행동이고 부재중이 아니어야
            if (kunshu.action_done) return false;
            if (pk::is_absent(kunshu)) return false;
			
            // 후방 거점 있는지 확인
			int target = getkunshu(base);
			if (target == -1) return false;
            
            // 군주 보낼 거점
            pk::building@ dst_base = pk::get_building(target);

            pk::city@ city_c = pk::get_city(pk::get_city_id(base.pos));
            int enemy_weight = countNeighborEnemyBase(base);


            // 세력 도시수가 5개 이상이어야
            if (pk::get_city_list(force).count < 5) return false;

            // 이미 군주가 15만 대도시의 후방지역에 있다면 제외
            if (0 == func_enemy_city_count(city_c, 2) and 0 == enemy_weight and pk::get_max_troops(base) == 150000 ) return false; 
								 
            // 군주의 국적과 베이스와 군주 받는 곳 국적이 같아야
            if (kunshu.get_force_id() != kunshu_base.get_force_id()) return false;
            if (kunshu.get_force_id() != base.get_force_id()) return false;	
            if (kunshu.get_force_id() != dst_base.get_force_id()) return false;	
            if (base.get_force_id() != dst_base.get_force_id()) return false;		
			
            // 군주가 있는 곳의 장수수가 부족하면 제외
            int count = pk::get_person_list(base, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반)).count; 
            auto person_list = pk::get_idle_person_list(base);
            if (count <  float( pk::get_person_list(force, pk::mibun_flags(신분_도독,신분_태수,신분_일반)).count / float ( pk::get_city_count(force) ) )  * 0.2f ) return false;   // 무장 부족
          
            // 경계지역 이상의 위험지대거나 최대병력한도 15만 미만인 거점에 군주가 있다면 보내라
            pk::list<pk::person@> actors;

            if (pk::get_city_list(force).count >= 5 and ((1 <= func_enemy_city_count(city_c, 2) or 0 < enemy_weight) or pk::get_max_troops(base) < 150000 )
            and base.get_id() == kunshu_base.get_id() and kunshu.location == kunshu.service and !kunshu.action_done and !pk::is_absent(kunshu)
		    and kunshu.get_force_id() == kunshu_base.get_force_id() and kunshu.get_force_id() == base.get_force_id() 
			and kunshu.get_force_id() == dst_base.get_force_id() and base.get_force_id() == dst_base.get_force_id() ) 				

                actors.add(kunshu);

            
            // 소환 명령
            pk::summon_cmd_info cmd_summon;
            @cmd_summon.base   = dst_base;
            cmd_summon.actors  = actors;
            pk::command(cmd_summon);
            
            return true;
        }

		/** 군주보낼만한 거점 */
		int getkunshu(pk::building@ src)
		{
			int best_dst = -1;
			int best_distance = 0;
            int src_id = src.get_id();
            pk::list<pk::building@> dst_list; 
            
            pk::force@ force = pk::get_force(src.get_force_id());
            
			// 후보 거점 검색

                for (int i = 0; i < 건물_거점끝; i++)
                {
                    pk::building@ dst = pk::get_building(i);
                    int dst_id = dst.get_id();

            pk::city@ city_d = pk::get_city(pk::get_city_id(dst.pos));
            int enemy_weight = countNeighborEnemyBase(dst);
              
	// 후방 거점들 리스트 추가
                    
        if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst) and 건물_도시시작 <= dst_id and dst_id < 건물_도시끝 )
                    {
						
                    if (0 == func_enemy_city_count(city_d, 2) and 0 == enemy_weight)
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
                    return (pk::get_max_troops(a) > pk::get_max_troops(b));					
					
                    int build_dist_a = pk::get_building_distance(a.get_id(), main.src_kunshu.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.src_kunshu.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.src_kunshu.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.src_kunshu.pos);

            auto person_list_a = pk::get_idle_person_list(a);
            auto person_list_b = pk::get_idle_person_list(b);

                    if (pk::get_max_troops(a) == pk::get_max_troops(b))
                    return (person_list_a.count - build_dist_a < person_list_b.count - build_dist_b );

                    if (build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);
                    
                    return (pos_dist_a < pos_dist_b);
                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
		}

        
        //----------------------------------------------------------------------------------
        //  무력 86 이상들 전방 배치
        //----------------------------------------------------------------------------------


        /** 전방 거점 조건 **/
        bool needValor(pk::building@ base)
		{

            if (!pk::is_alive(base)) return false;

			if (base.get_force_id() == -1) return false;

			pk::force@ force = pk::get_force(base.get_force_id());
			int force_id = force.get_id();



			// 플레이어, 이민족 세력은 제외.
			if (!force.is_player() and pk::is_normal_force(force_id))
			{


			// 전방에 병력 1만 5천 이상인 도시

            pk::city@ city_a = pk::get_city(pk::get_city_id(base.pos));
            int count = pk::get_person_list(base, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반)).count;

            
            auto person_list = pk::get_idle_person_list(base);


            // 거점 내 능력치 86 이상 무장들 정리
           
           pk::list<pk::person@> base86_list;

            auto b_list = pk::list_to_array(pk::get_person_list(base, pk::mibun_flags(신분_군주,신분_도독,신분_태수,신분_일반) ) );
            
           if (0 < b_list.length)
            {
                for (int i = 0; i < int(b_list.length); i++)
                {
                    pk::person@ person = b_list[i];


                             if (b_list[i].stat[무장능력_무력] >= 86 and !b_list[i].action_done   and b_list[i].get_force_id() == base.get_force_id() )

                             base86_list.add(b_list[i]);

	        }

	    }



            //  세력 내 86 이상 무장들 정리
           
           pk::list<pk::person@> force86_list;

            auto f_list = pk::list_to_array(pk::get_person_list(force, pk::mibun_flags(신분_군주,신분_도독,신분_태수,신분_일반) ) );

           if (0 < f_list.length)
            {
                for (int i = 0; i < int(f_list.length); i++)
                {
                    pk::person@ person = f_list[i];


                             if (f_list[i].stat[무장능력_무력] >= 86 and !f_list[i].action_done and !pk::is_absent(f_list[i]) and f_list[i].get_force_id() == base.get_force_id() )

                             force86_list.add(f_list[i]);

	        }

	    }
                             
       if (force86_list.count == 0 ) return false;   // 86 이상 무장 부족



            // 전방의 거점 개수 

        pk::list<pk::building@> hotzone;

	for (int i = 0; i < 건물_도시끝; i++)
	{
	     int force_id = force.get_id();
	     pk::building@ base  = pk::get_building(i);
             pk::city@ city_a = pk::get_city(pk::get_city_id(base.pos));
            int enemy_weight = countNeighborEnemyBase(base);

             if (base.get_force_id() == force_id and (1 <= func_enemy_city_count(city_a, 1) or 0 < enemy_weight) and 6000 <= pk::get_troops(base))

                hotzone.add(base);

	}


            int hotzone_count = hotzone.count;
            if (hotzone_count == 0 ) return false;   // 전방 거점 부재



            if (1 <= func_enemy_city_count(city_a, 1) and 6000 <= pk::get_troops(base) and 건물_도시시작 <= base.get_id() and base.get_id() < 건물_도시끝 and base86_list.count < float ( force86_list.count/ float ( hotzone_count ))) 
                return true;
            }        
            return false;
        }



        
        // ***** 무장 지원 명령 ***** //
        bool PushValor(pk::building@ dst_base)
        {

            pk::list<pk::person@> candis;

            
            // 미행동 무장리스트
	    pk::force@ force = pk::get_force( dst_base.get_force_id());

            int person_count = pk::get_person_list(force, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반)).count;
            if (person_count == 0 ) return false;   // 무장 부족
 


            // 세력에 86이상 무장 있는가

            if (above86count(force, 무장능력_무력)  == 0 ) return false;   // 세력 내 86 이상 무장 부재
	   
	   
            // 전방의 거점 개수 

        pk::list<pk::building@> hotzone;

	for (int i = 0; i < 건물_도시끝; i++)
	{
	     int force_id = force.get_id();
	     pk::building@ base  = pk::get_building(i);
             pk::city@ city_a = pk::get_city(pk::get_city_id(base.pos));
            int enemy_weight = countNeighborEnemyBase(base);

             if (base.get_force_id() == force_id and (1 <= func_enemy_city_count(city_a, 1) or 0 < enemy_weight) and 6000 <= pk::get_troops(base))

                hotzone.add(base);

	}


            int hotzone_count = hotzone.count;
            if (hotzone_count == 0 ) return false;   // 전방 거점 부재



            // 거점 내  86 이상 무장들 정리
           
           pk::list<pk::person@> base86_list;

            auto b_list = pk::list_to_array(pk::get_person_list(dst_base, pk::mibun_flags(신분_군주,신분_도독,신분_태수,신분_일반) ) );
            
           if (0 < b_list.length)
            {
                for (int i = 0; i < int(b_list.length); i++)
                {
                    pk::person@ person = b_list[i];


                             if (b_list[i].stat[무장능력_무력] >= 86 and !b_list[i].action_done   and b_list[i].get_force_id() == dst_base.get_force_id() )

                             base86_list.add(b_list[i]);

	        }

	    }




            //  이동 대상 86 이상 무장들 정리
           
           pk::list<pk::person@> candidate86_list;

            auto c_list = pk::list_to_array(pk::get_person_list(force, pk::mibun_flags(신분_군주,신분_도독,신분_태수,신분_일반) ) );
            
           if (0 < c_list.length)
            {
                for (int i = 0; i < int(c_list.length); i++)
                {
                    pk::person@ person = c_list[i];
                    pk::building@ building = pk::get_building(person.service);
                    pk::building@ src_base = pk::get_building(person.location);					
             pk::city@ city_b = pk::get_city(pk::get_city_id(building.pos));

            if (pk::is_unitize(c_list[i])) continue;
            if (pk::is_absent(c_list[i])) continue;
            if (c_list[i].order != -1) continue;
            if (c_list[i].get_force_id() != src_base.get_force_id()) continue; 
            if (c_list[i].get_force_id() != dst_base.get_force_id()) continue; 
            if (c_list[i].location != c_list[i].service) continue;
            if (c_list[i].action_done) continue;
            if (pk::is_absent(c_list[i])) continue;
            if (c_list[i].mibun == 신분_포로) continue;
            if (c_list[i].mibun == 신분_재야) continue;
			
                   if (!pk::is_unitize(c_list[i]) and !pk::is_absent(c_list[i]) and c_list[i].order == -1 and c_list[i].service != dst_base.get_id() and c_list[i].location != dst_base.get_id() and c_list[i].stat[무장능력_무력] >= 86 and c_list[i].location == c_list[i].service and !c_list[i].action_done and !pk::is_absent(c_list[i]) and (c_list[i].mibun == 신분_군주 or c_list[i].mibun == 신분_도독 or c_list[i].mibun == 신분_태수 or c_list[i].mibun == 신분_일반) and c_list[i].get_force_id() == src_base.get_force_id() and c_list[i].get_force_id() == dst_base.get_force_id() and 0 == func_enemy_city_count(city_b, 1))
                      {

                             if (pk::get_city_list(force).count >= 5 and c_list[i].mibun != 신분_군주)
                             candidate86_list.add(c_list[i]);

                             if (pk::get_city_list(force).count < 5)
                             candidate86_list.add(c_list[i]);

	              }
	        }

	    }
                             
       if (candidate86_list.count == 0 ) return false;   // 86 이상 무장 부족




			candidate86_list.sort(function(a, b)
			{
				
				if ((a.mibun == 신분_군주 and b.mibun != 신분_군주) or (a.mibun != 신분_군주 and b.mibun == 신분_군주))
					return a.mibun > b.mibun;	
				
				return (a.stat[무장능력_무력] + a.stat[무장능력_통솔]) > (b.stat[무장능력_무력] + b.stat[무장능력_통솔]);
			});



           
            // 소환할 무장수
            int max = pk::max( 1 , int( (candidate86_list.count / float (hotzone_count)) - base86_list.count ) );
            
            // 소환 대상 무장
            pk::list<pk::person@> actors;
            for (int i = 0; i < max; i++)
            {
                actors.add(candidate86_list[i]);
            }

       if (actors.count == 0 ) return false;
            
            // 소환 명령
            pk::summon_cmd_info cmd_summon;
            @cmd_summon.base   = dst_base;
            cmd_summon.actors  = actors;
            pk::command(cmd_summon);
            
            return true;
        }


        
     

        
        //----------------------------------------------------------------------------------
        //  지력 상위 10%들 전방 배치
        //----------------------------------------------------------------------------------


        /** 전방 거점 조건 **/
        bool needTactician(pk::building@ base)
		{

            if (!pk::is_alive(base)) return false;

			if (base.get_force_id() == -1) return false;

			pk::force@ force = pk::get_force(base.get_force_id());
			int force_id = force.get_id();



			// 플레이어, 이민족 세력은 제외.
			if (!force.is_player() and pk::is_normal_force(force_id))
			{


			// 전방에 병력 1만 5천 이상인 도시

            pk::city@ city_a = pk::get_city(pk::get_city_id(base.pos));
            int count = pk::get_person_list(base, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반)).count;

            
            auto person_list = pk::get_idle_person_list(base);


            // 거점 내 86 이상 무장들 정리
           
           pk::list<pk::person@> base86_list;

            auto b_list = pk::list_to_array(pk::get_person_list(base, pk::mibun_flags(신분_군주,신분_도독,신분_태수,신분_일반) ) );
            
           if (0 < b_list.length)
            {
                for (int i = 0; i < int(b_list.length); i++)
                {
                    pk::person@ person = b_list[i];


                             if (b_list[i].stat[무장능력_지력] >= 86 and !b_list[i].action_done   and b_list[i].get_force_id() == base.get_force_id() )

                             base86_list.add(b_list[i]);

	        }

	    }



            // 세력 내 86 이상 무장들 정리
           
           pk::list<pk::person@> force86_list;

            auto f_list = pk::list_to_array(pk::get_person_list(force, pk::mibun_flags(신분_군주,신분_도독,신분_태수,신분_일반) ) );

           if (0 < f_list.length)
            {
                for (int i = 0; i < int(f_list.length); i++)
                {
                    pk::person@ person = f_list[i];


                             if (f_list[i].stat[무장능력_지력] >= 86 and !f_list[i].action_done and !pk::is_absent(f_list[i]) and f_list[i].get_force_id() == base.get_force_id() )

                             force86_list.add(f_list[i]);

	        }

	    }
                             
       if (force86_list.count == 0 ) return false;   // 86 이상 무장 부족


            // 전방의 거점 개수 

        pk::list<pk::building@> hotzone;

	for (int i = 0; i < 건물_도시끝; i++)
	{
	     int force_id = force.get_id();
	     pk::building@ base  = pk::get_building(i);
             pk::city@ city_a = pk::get_city(pk::get_city_id(base.pos));
            int enemy_weight = countNeighborEnemyBase(base);

             if (base.get_force_id() == force_id and (1 <= func_enemy_city_count(city_a, 1) or 0 < enemy_weight) and 6000 <= pk::get_troops(base))

                hotzone.add(base);

	}


            int hotzone_count = hotzone.count;
            if (hotzone_count == 0 ) return false;   // 전방 거점 부재



            if (1 <= func_enemy_city_count(city_a, 1) and 6000 <= pk::get_troops(base) and 건물_도시시작 <= base.get_id() and base.get_id() < 건물_도시끝 and base86_list.count < float ( force86_list.count/ float ( hotzone_count )) ) 
                return true;
            }        
            return false;
        }



        
        // ***** 무장 지원 명령 ***** //
        bool PushTactician(pk::building@ dst_base)
        {

            pk::list<pk::person@> candis;

            
            // 미행동 무장리스트
	    pk::force@ force = pk::get_force( dst_base.get_force_id());

            int person_count = pk::get_person_list(force, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반)).count;
            if (person_count == 0 ) return false;   // 무장 부족
 


            // 세력에 86이상 무장 있는가

            if (above86count(force, 무장능력_지력)  == 0 ) return false;   // 세력 내 86 이상 무장 부재
	   

            // 전방의 거점 개수 

        pk::list<pk::building@> hotzone;

	for (int i = 0; i < 건물_도시끝; i++)
	{
	     int force_id = force.get_id();
	     pk::building@ base  = pk::get_building(i);
             pk::city@ city_a = pk::get_city(pk::get_city_id(base.pos));
            int enemy_weight = countNeighborEnemyBase(base);

             if (base.get_force_id() == force_id and (1 <= func_enemy_city_count(city_a, 1) or 0 < enemy_weight) and 6000 <= pk::get_troops(base))

                hotzone.add(base);

	}


            int hotzone_count = hotzone.count;
            if (hotzone_count == 0 ) return false;   // 전방 거점 부재




            // 거점 내 86 이상 무장들 정리
           
           pk::list<pk::person@> base86_list;

            auto b_list = pk::list_to_array(pk::get_person_list(dst_base, pk::mibun_flags(신분_군주,신분_도독,신분_태수,신분_일반) ) );
            
           if (0 < b_list.length)
            {
                for (int i = 0; i < int(b_list.length); i++)
                {
                    pk::person@ person = b_list[i];


                             if (b_list[i].stat[무장능력_지력] >= 86 and !b_list[i].action_done   and b_list[i].get_force_id() == dst_base.get_force_id() )

                             base86_list.add(b_list[i]);

	        }

	    }



            // 이동 대상 86 이상 무장들 정리
           
           pk::list<pk::person@> candidate86_list;

            auto c_list = pk::list_to_array(pk::get_person_list(force, pk::mibun_flags(신분_군주,신분_도독,신분_태수,신분_일반) ) );
            
           if (0 < c_list.length)
            {
                for (int i = 0; i < int(c_list.length); i++)
                {
                    pk::person@ person = c_list[i];
                    pk::building@ building = pk::get_building(person.service);
                    pk::building@ src_base = pk::get_building(person.location);						
             pk::city@ city_b = pk::get_city(pk::get_city_id(building.pos));

            if (pk::is_unitize(c_list[i])) continue;
            if (pk::is_absent(c_list[i])) continue;
            if (c_list[i].order != -1) continue;
            if (c_list[i].get_force_id() != src_base.get_force_id()) continue; 
            if (c_list[i].get_force_id() != dst_base.get_force_id()) continue; 
            if (c_list[i].location != c_list[i].service) continue;
            if (c_list[i].action_done) continue;
            if (pk::is_absent(c_list[i])) continue;
            if (c_list[i].mibun == 신분_포로) continue;
            if (c_list[i].mibun == 신분_재야) continue;

                      if (!pk::is_unitize(c_list[i]) and !pk::is_absent(c_list[i]) and c_list[i].order == -1 and c_list[i].service != dst_base.get_id() and c_list[i].location != dst_base.get_id() and c_list[i].stat[무장능력_지력] >= 86 and c_list[i].location == c_list[i].service and !c_list[i].action_done and !pk::is_absent(c_list[i]) and (c_list[i].mibun == 신분_군주 or c_list[i].mibun == 신분_도독 or c_list[i].mibun == 신분_태수 or c_list[i].mibun == 신분_일반) and c_list[i].get_force_id() == src_base.get_force_id() and c_list[i].get_force_id() == dst_base.get_force_id() and 0 == func_enemy_city_count(city_b, 1))
                      {
                             if (pk::get_city_list(force).count >= 5 and c_list[i].mibun != 신분_군주)
                             candidate86_list.add(c_list[i]);

                             if (pk::get_city_list(force).count < 5)
                             candidate86_list.add(c_list[i]);
	               }
	        }

	    }
                             
       if (candidate86_list.count == 0 ) return false;   // 86 이상 무장 부족



			candidate86_list.sort(function(a, b)
			{
				
				if ((a.mibun == 신분_군주 and b.mibun != 신분_군주) or (a.mibun != 신분_군주 and b.mibun == 신분_군주))
					return a.mibun > b.mibun;				
				
				return (a.stat[무장능력_지력] ) > (b.stat[무장능력_지력]);
			});



           
            // 소환할 무장수
            int max = pk::max( 1 , int( (candidate86_list.count / float ( hotzone_count)) -base86_list.count ) );
            
            // 소환 대상 무장
            pk::list<pk::person@> actors;
            for (int i = 0; i < max; i++)
            {
                actors.add(candidate86_list[i]);
            }

       if (actors.count == 0 ) return false;
            
            // 소환 명령
            pk::summon_cmd_info cmd_summon;
            @cmd_summon.base   = dst_base;
            cmd_summon.actors  = actors;
            pk::command(cmd_summon);
            
            return true;
        }



        







        //----------------------------------------------------------------------------------
        //  후방 도시에 무장 수가 부족하면 무장 지원
        //----------------------------------------------------------------------------------


        /** 평균 무장수 이하 거점에 파견이 필요한지 판단 **/
        bool needREAR(pk::building@ base)
		{

            if (!pk::is_alive(base)) return false;

			if (base.get_force_id() == -1) return false;

			pk::force@ force = pk::get_force(base.get_force_id());
			int force_id = force.get_id();



                // 플레이어, 이민족 세력은 제외.
                if (!force.is_player() and pk::is_normal_force(force_id))
			{

            pk::city@ city_a = pk::get_city(pk::get_city_id(base.pos));
            int count = pk::get_person_list(base, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반)).count;
            int enemy_weight = countNeighborEnemyBase(base);
            

 if ( (count + func_already(base) <=  0.5f * float(pk::get_person_list(force, pk::mibun_flags(신분_도독,신분_태수,신분_일반)).count / float (pk::get_city_list(force).count) ) ) and 건물_도시시작 <= base.get_id() and base.get_id() < 건물_도시끝 and 0 == func_enemy_city_count(city_a, 2) and 0 == func_user_city_count(city_a, 1) ) 
                return true;

 if ( (count + func_already(base) <=  1.0f * float(pk::get_person_list(force, pk::mibun_flags(신분_도독,신분_태수,신분_일반)).count / float (pk::get_city_list(force).count) ) ) and 건물_도시시작 <= base.get_id() and base.get_id() < 건물_도시끝 and 0 == func_enemy_city_count(city_a, 2) and 0 == func_user_city_count(city_a, 1) and !check_city_dev_complete(city_a)) 
                return true;			
			
            }        
            return false;
        }
        
        // ***** 무장 지원 명령 ***** //
        pk::building@ dst_REAR;
        bool PushREAR(pk::building@ dst_base)
        {
            @dst_REAR = @dst_base;
            // 무장이 있는 인근 거점이 있는지 확인
			int target = getEXTRAPerson(dst_base);
			if (target == -1) return false;
            
            // 지원가능 무장 소속거점
            pk::building@ src_base = pk::get_building(target);
            
            // 미행동 무장리스트
			pk::force@ force = pk::get_force( src_base.get_force_id());
																				   
            // 장수 보내는 곳과 받는 곳 국적이 같아야 하고, 받는 곳 장수 숫자가 보내는 곳 장수 숫자보다 그렇게 많이 적지 않으면 보내지 말것
		if (dst_base.get_force_id() != src_base.get_force_id()) return false;
		
		if (pk::get_person_list(dst_base, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반)).count + 2 >= pk::get_person_list(src_base, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반)).count) return false;

            int count = pk::get_person_list(src_base, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반)).count; 
            auto person_list = pk::get_idle_person_list(src_base);
            if (count <  float( pk::get_person_list(force, pk::mibun_flags(신분_도독,신분_태수,신분_일반)).count / float ( pk::get_city_count(force) ) ) * 0.2f ) return false;   // 무장 부족
          
            // 5개 능력치 총합이 낮은 순부터 행선지 상황따라 정렬.

            pk::city@ city_c = pk::get_city(pk::get_city_id(dst_base.pos));
            int enemy_weight = countNeighborEnemyBase(dst_base);

            pk::city@ city_s = pk::get_city(pk::get_city_id(src_base.pos));

            // 경계지역 이상의 위험지역에서 후방지역으로 장수 보낼땐 군주먼저 보내라. 나머지 경우엔 능력치 낮은 장수들부터 후방으로 보내라
		if (1 <= func_enemy_city_count(city_s, 2))
			person_list.sort(function(a, b)
			{
				
				if ((a.mibun == 신분_군주 and b.mibun != 신분_군주) or (a.mibun != 신분_군주 and b.mibun == 신분_군주))
					return a.mibun < b.mibun;	
				
return (a.stat[무장능력_무력] + a.stat[무장능력_통솔] + a.stat[무장능력_지력] + a.stat[무장능력_정치] + a.stat[무장능력_매력]) < (b.stat[무장능력_무력] + b.stat[무장능력_통솔] + b.stat[무장능력_지력] + b.stat[무장능력_정치] + b.stat[무장능력_매력]);

			});

        else 
			person_list.sort(function(a, b)
			{
return (a.stat[무장능력_무력] + a.stat[무장능력_통솔] + a.stat[무장능력_지력] + a.stat[무장능력_정치] + a.stat[무장능력_매력]) < (b.stat[무장능력_무력] + b.stat[무장능력_통솔] + b.stat[무장능력_지력] + b.stat[무장능력_정치] + b.stat[무장능력_매력]);

			});

     
	 
            // 소환할 무장수
            int max = pk::max( 1 , pk::min(1, person_list.count * 0.05) );
            
            // 소환 대상 무장 (소속과 소재거점이 다르면 제외, 같고 보내려는 장수와 보내는 도시의 국적이 같으면 보내라)
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
        int getEXTRAPerson(pk::building@ dst)
		{
			int best_src = -1;
			int best_distance = 0;
            pk::list<pk::building@> src_list; 			
            
			// 거점까지 확인.
			for (int i = 0; i < 건물_도시끝; i++)
			{
				pk::building@ src = pk::get_building(i);
                
				if (dst.get_id() != i and dst.get_force_id() == src.get_force_id()  )
                {
                    int distance = pk::get_city_distance(src.get_id(), dst.get_id());

                    int count = pk::get_person_list(src, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반)).count;        
                    int count_dst = pk::get_person_list(dst, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반)).count;       					
                    auto person_idle_list = pk::get_idle_person_list(src);


            int src_id = src.get_id();
            int dst_id = dst.get_id();

            pk::city@ city_d = pk::get_city(pk::get_city_id(src.pos));
            int enemy_weight = countNeighborEnemyBase(src);

	    pk::force@ force_s = pk::get_force(src.get_force_id());
                    
                    int max_distance = 12;
                    if (!force_s.is_player() and (0 <= distance and distance <= max_distance))
                    {


			pk::force@ force = pk::get_force(dst.get_force_id());
			if ( distance <= 12 )
                        {
// 후방에 장수 숫자가 많을 때 (내정 개발 건설 완료 조건에 따라 2분류)

if (  person_idle_list.count > 0 and (count > count_dst + 2 or count > 0.7f * float( pk::get_person_list(force, pk::mibun_flags(신분_도독,신분_태수,신분_일반)).count / float( pk::get_city_count(force) ))) and pk::is_alive(src) and pk::is_alive(dst) and src_id != dst_id and src.get_force_id() == dst.get_force_id() and 0 == func_enemy_city_count(city_d, 2) and 0 == func_user_city_count(city_d, 1) and 0 == enemy_weight and check_city_dev_complete(city_d) )
                        {
                        best_src = src_id;
                        src_list.add(src);  // 수송가능 거점리스트 추가
                        }

if (  person_idle_list.count > 0 and (count > 2.5f * float( pk::get_person_list(force, pk::mibun_flags(신분_도독,신분_태수,신분_일반)).count / float( pk::get_city_count(force) ))) and pk::is_alive(src) and pk::is_alive(dst) and src_id != dst_id and src.get_force_id() == dst.get_force_id() and 0 == func_enemy_city_count(city_d, 2) and 0 == func_user_city_count(city_d, 1) and 0 == enemy_weight and !check_city_dev_complete(city_d) )
                        {
                        best_src = src_id;
                        src_list.add(src);  // 수송가능 거점리스트 추가
                        }
						


// 그 다음은 장수 숫자가 좀 있는 경계에서라도 (내정 개발 건설 완료 조건에 따라 2분류)

else if ( person_idle_list.count > 0 and (count > 11 or count > 1.3f * float( pk::get_person_list(force, pk::mibun_flags(신분_도독,신분_태수,신분_일반)).count / float( pk::get_city_count(force) ))) and pk::is_alive(src) and pk::is_alive(dst) and src_id != dst_id and src.get_force_id() == dst.get_force_id() and ( (1 <= func_enemy_city_count(city_d, 2) and 0 == func_enemy_city_count(city_d, 1) and 0 == enemy_weight) or 1 <= func_user_city_count(city_d, 1) ) and check_city_dev_complete(city_d))
                        {
                        best_src = src_id;
                        src_list.add(src);  // 수송가능 거점리스트 추가
                        }
						
else if ( person_idle_list.count > 0 and (count > 2.5f * float( pk::get_person_list(force, pk::mibun_flags(신분_도독,신분_태수,신분_일반)).count / float( pk::get_city_count(force) ))) and pk::is_alive(src) and pk::is_alive(dst) and src_id != dst_id and src.get_force_id() == dst.get_force_id() and ( (1 <= func_enemy_city_count(city_d, 2) and 0 == func_enemy_city_count(city_d, 1) and 0 == enemy_weight) or 1 <= func_user_city_count(city_d, 1) ) and !check_city_dev_complete(city_d))
                        {
                        best_src = src_id;
                        src_list.add(src);  // 수송가능 거점리스트 추가
                        }						

// 최후엔 전방에 잉여 장수 많은 도시에서라도
else if ( person_idle_list.count > 10 and (count > 22 or count > 3.1f * float( pk::get_person_list(force, pk::mibun_flags(신분_도독,신분_태수,신분_일반)).count / float( pk::get_city_count(force) ))) and pk::is_alive(src) and pk::is_alive(dst) and src_id != dst_id and src.get_force_id() == dst.get_force_id() and (1 <= func_enemy_city_count(city_d, 1) or 0 < enemy_weight) )
                        {
                        best_src = src_id;
                        src_list.add(src);  // 수송가능 거점리스트 추가
                        }


                        }
                    }
                }
			}
			
            if (src_list.count == 0)
                best_src = -1;
            else
            {
                src_list.sort(function(a, b)
                {
                    int build_dist_a = pk::get_building_distance(a.get_id(), main.dst_REAR.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.dst_REAR.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.dst_REAR.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.dst_REAR.pos);

            auto person_list_a = pk::get_idle_person_list(a);
            auto person_list_b = pk::get_idle_person_list(b);

                    return (person_list_a.count - build_dist_a > person_list_b.count - build_dist_b );
			
                    if (build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);
                    
                    return (pos_dist_a < pos_dist_b);
                });
                best_src = src_list[0].get_id();
            }
			
			return best_src;
		}
        
         







        //----------------------------------------------------------------------------------
        //  경계 도시에 무장 수가 부족하면 무장 지원
        //----------------------------------------------------------------------------------


        /** 평균 무장수 이하 거점에 파견이 필요한지 판단 **/
        bool needGARRISON(pk::building@ base)
		{

            if (!pk::is_alive(base)) return false;

			if (base.get_force_id() == -1) return false;

			pk::force@ force = pk::get_force(base.get_force_id());
			int force_id = force.get_id();



                // 플레이어, 이민족 세력은 제외.
                if (!force.is_player() and pk::is_normal_force(force_id))
			{

            pk::city@ city_a = pk::get_city(pk::get_city_id(base.pos));
            int count = pk::get_person_list(base, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반)).count;
            int enemy_weight = countNeighborEnemyBase(base);
            

 if ( (count + func_already(base) <=  0.8f * float(pk::get_person_list(force, pk::mibun_flags(신분_도독,신분_태수,신분_일반)).count / float( pk::get_city_list(force).count)) ) and 건물_도시시작 <= base.get_id() and base.get_id() < 건물_도시끝 and ( (1 <= func_enemy_city_count(city_a, 2) and 0 == func_enemy_city_count(city_a, 1) and 0 == enemy_weight) or 1 <= func_user_city_count(city_a, 1) ) )
                return true;
			
 if ( (count + func_already(base) <=  1.0f * float(pk::get_person_list(force, pk::mibun_flags(신분_도독,신분_태수,신분_일반)).count / float( pk::get_city_list(force).count)) ) and 건물_도시시작 <= base.get_id() and base.get_id() < 건물_도시끝 and ( (1 <= func_enemy_city_count(city_a, 2) and 0 == func_enemy_city_count(city_a, 1) and 0 == enemy_weight) or 1 <= func_user_city_count(city_a, 1) ) and !check_city_dev_complete(city_a) )
                return true;			
			
            }        
            return false;
        }
        
        // ***** 무장 지원 명령 ***** //
        pk::building@ dst_GARRISON;		
        bool PushGARRISON(pk::building@ dst_base)
        {
            @dst_GARRISON = @dst_base;			
            // 무장이 있는 인근 거점이 있는지 확인
			int target = getGARRISONPerson(dst_base);
			if (target == -1) return false;
            
            // 지원가능 무장 소속거점
            pk::building@ src_base = pk::get_building(target);
            
            // 미행동 무장리스트
			pk::force@ force = pk::get_force( src_base.get_force_id());

            // 장수 보내는 곳과 받는 곳 국적이 같아야
		if (dst_base.get_force_id() != src_base.get_force_id()) return false;
		
            int count = pk::get_person_list(src_base, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반)).count;  
            auto person_list = pk::get_idle_person_list(src_base);
            if (count <  float( pk::get_person_list(force, pk::mibun_flags(신분_도독,신분_태수,신분_일반)).count / float( pk::get_city_count(force)) ) * 0.2f ) return false;   // 무장 부족
          
            // 5개 능력치 총합 행선지 상황따라 정렬.

            pk::city@ city_s = pk::get_city(pk::get_city_id(src_base.pos));
            pk::city@ city_c = pk::get_city(pk::get_city_id(dst_base.pos));
            int enemy_weight = countNeighborEnemyBase(dst_base);


            // 후방지역에서 경계지역으로 장수 보낼땐 군주를 제일 나중에 보내라. 나머지는 능력치 좋은 장수들부터 보내라 

if ( 0 == func_enemy_city_count(city_s, 2) and dst_base.get_force_id() == src_base.get_force_id())

			person_list.sort(function(a, b)
			{
				if ((a.mibun == 신분_군주 and b.mibun != 신분_군주) or (a.mibun != 신분_군주 and b.mibun == 신분_군주))
					return a.mibun > b.mibun;					
				
return (a.stat[무장능력_무력] + a.stat[무장능력_통솔] + a.stat[무장능력_지력] + a.stat[무장능력_정치] + a.stat[무장능력_매력]) > (b.stat[무장능력_무력] + b.stat[무장능력_통솔] + b.stat[무장능력_지력] + b.stat[무장능력_정치] + b.stat[무장능력_매력]);

			});


            // 경계 지역 이상의 위험지역에서 경계지역으로 장수 보낼땐 군주를 먼저 보내라. 나머지는 능력치 낮은 장수들부터 보내라.

if ( ( 1 <= func_enemy_city_count(city_s, 1)  or ( 1 <= func_enemy_city_count(city_s, 2) and 0 == func_enemy_city_count(city_s, 1) ) ) and dst_base.get_force_id() == src_base.get_force_id() )

			person_list.sort(function(a, b)
			{
				if ((a.mibun == 신분_군주 and b.mibun != 신분_군주) or (a.mibun != 신분_군주 and b.mibun == 신분_군주))
					return a.mibun < b.mibun;	
				
return (a.stat[무장능력_무력] + a.stat[무장능력_통솔] + a.stat[무장능력_지력] + a.stat[무장능력_정치] + a.stat[무장능력_매력]) < (b.stat[무장능력_무력] + b.stat[무장능력_통솔] + b.stat[무장능력_지력] + b.stat[무장능력_정치] + b.stat[무장능력_매력]);

			});


            
            // 소환할 무장수
            int max = pk::max( 1 ,  pk::min(1, person_list.count * 0.05) );
            
            // 소환 대상 무장 (소속과 소재거점이 다르면 제외, 같고 보내려는 장수와 보내는 도시의 국적이 같으면 보내라)
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
        int getGARRISONPerson(pk::building@ dst)
		{
			int best_src = -1;
			int best_distance = 0;
             pk::list<pk::building@> src_list; 
			 
			// 거점까지 확인.
			for (int i = 0; i < 건물_도시끝; i++)
			{
				pk::building@ src = pk::get_building(i);
                
				if (dst.get_id() != i and dst.get_force_id() == src.get_force_id()  )
                {
                    int distance = pk::get_city_distance(src.get_id(), dst.get_id());
                    int count = pk::get_person_list(src, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반)).count;        
                    int count_dst = pk::get_person_list(dst, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반)).count;  					
                    auto person_idle_list = pk::get_idle_person_list(src);


            int src_id = src.get_id();
            int dst_id = dst.get_id();

            pk::city@ city_d = pk::get_city(pk::get_city_id(src.pos));
            int enemy_weight = countNeighborEnemyBase(src);

	    pk::force@ force_s = pk::get_force(src.get_force_id());
                    
                    int max_distance = 12;
                    if (!force_s.is_player() and (0 <= distance and distance <= max_distance))
                    {


			pk::force@ force = pk::get_force(dst.get_force_id());
			if ( distance <= 12 )			
                        {
// 후방에 장수 숫자가 많을 때 (내정 개발 건설 완료 조건에 따라 2분류)

if ( person_idle_list.count > 0 and (count >= count_dst or count > 0.7f * float( pk::get_person_list(force, pk::mibun_flags(신분_도독,신분_태수,신분_일반)).count / float( pk::get_city_count(force) ))) and pk::is_alive(src) and pk::is_alive(dst) and src_id != dst_id and src.get_force_id() == dst.get_force_id() and 0 == func_enemy_city_count(city_d, 2) and 0 == func_user_city_count(city_d, 1) and  0 == enemy_weight and check_city_dev_complete(city_d) )
                        {
                        best_src = src_id;
                        src_list.add(src);  // 수송가능 거점리스트 추가
                        }

if ( person_idle_list.count > 0 and (count >  2.5f * float( pk::get_person_list(force, pk::mibun_flags(신분_도독,신분_태수,신분_일반)).count / float( pk::get_city_count(force) ))) and pk::is_alive(src) and pk::is_alive(dst) and src_id != dst_id and src.get_force_id() == dst.get_force_id() and 0 == func_enemy_city_count(city_d, 2) and 0 == func_user_city_count(city_d, 1) and  0 == enemy_weight and !check_city_dev_complete(city_d) )
                        {
                        best_src = src_id;
                        src_list.add(src);  // 수송가능 거점리스트 추가
                        }



// 그 다음은 장수 숫자가 좀 있는 경계에서라도 (내정 개발 건설 완료 조건에 따라 2분류)

else if ( person_idle_list.count > 0 and (count > count_dst + 2 or count > 1.3f * float( pk::get_person_list(force, pk::mibun_flags(신분_도독,신분_태수,신분_일반)).count / float( pk::get_city_count(force) ))) and pk::is_alive(src) and pk::is_alive(dst) and src_id != dst_id and src.get_force_id() == dst.get_force_id() and ( (1 <= func_enemy_city_count(city_d, 2) and 0 == func_enemy_city_count(city_d, 1) and 0 == enemy_weight) or 1 <= func_user_city_count(city_d, 1) ) and check_city_dev_complete(city_d) and count > count_dst + 2)
                        {
                        best_src = src_id;
                        src_list.add(src);  // 수송가능 거점리스트 추가
                        }


else if ( person_idle_list.count > 0 and (count >  2.5f * float( pk::get_person_list(force, pk::mibun_flags(신분_도독,신분_태수,신분_일반)).count / float( pk::get_city_count(force) ))) and pk::is_alive(src) and pk::is_alive(dst) and src_id != dst_id and src.get_force_id() == dst.get_force_id() and ( (1 <= func_enemy_city_count(city_d, 2) and 0 == func_enemy_city_count(city_d, 1) and 0 == enemy_weight) or 1 <= func_user_city_count(city_d, 1) ) and !check_city_dev_complete(city_d) and count > count_dst + 2)
                        {
                        best_src = src_id;
                        src_list.add(src);  // 수송가능 거점리스트 추가
                        }

// 최후엔 전방에 잉여 장수 많은 도시에서라도

				   

else if ( person_idle_list.count > 10 and (count > 22 or count > 3.1f * float( pk::get_person_list(force, pk::mibun_flags(신분_도독,신분_태수,신분_일반)).count / float( pk::get_city_count(force) ))) and pk::is_alive(src) and pk::is_alive(dst) and src_id != dst_id and src.get_force_id() == dst.get_force_id() and (1 <= func_enemy_city_count(city_d, 1) or 0 < enemy_weight) and count > count_dst + 2)
                        {
                        best_src = src_id;
                        src_list.add(src);  // 수송가능 거점리스트 추가
                        }


                        }
                    }
                }
			}

            if (src_list.count == 0)
                best_src = -1;
            else
            {
                src_list.sort(function(a, b)
                {
                    int build_dist_a = pk::get_building_distance(a.get_id(), main.dst_GARRISON.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.dst_GARRISON.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.dst_GARRISON.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.dst_GARRISON.pos);

            auto person_list_a = pk::get_idle_person_list(a);
            auto person_list_b = pk::get_idle_person_list(b);

                    return (person_list_a.count - build_dist_a > person_list_b.count - build_dist_b );
			
                    if (build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);
                    
                    return (pos_dist_a < pos_dist_b);
                });
                best_src = src_list[0].get_id();
            }

			return best_src;
		}
        
         















        //----------------------------------------------------------------------------------
        //  전방 도시에 무장 수가 부족하면 무장 지원
        //----------------------------------------------------------------------------------


        /** 평균 무장수 이하 거점에 파견이 필요한지 판단 **/
        bool needFRONT(pk::building@ base)
		{

            if (!pk::is_alive(base)) return false;

			if (base.get_force_id() == -1) return false;

			pk::force@ force = pk::get_force(base.get_force_id());
			int force_id = force.get_id();



                // 플레이어, 이민족 세력은 제외.
                if (!force.is_player() and pk::is_normal_force(force_id))
			{

            pk::city@ city_a = pk::get_city(pk::get_city_id(base.pos));
            int count = pk::get_person_list(base, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반)).count;
            int enemy_weight = countNeighborEnemyBase(base);

 if ( ( pk::get_troops(base) <= 4500 or base.hp <= 700 ) and pk::enemies_around(base) ) 
            return false;
            
 if ( (count + func_already(base) <= 2.5f * float(pk::get_person_list(force, pk::mibun_flags(신분_도독,신분_태수,신분_일반)).count / float(pk::get_city_list(force).count) )) and 건물_도시시작 <= base.get_id() and base.get_id() < 건물_도시끝 and (1 <= func_enemy_city_count(city_a, 1) or 0 < enemy_weight)) 
                return true;
            }        
            return false;
        }
        
        // ***** 무장 지원 명령 ***** //
        pk::building@ dst_FRONT;	
        bool PushFRONT(pk::building@ dst_base)
        {
            @dst_FRONT = @dst_base;			
            // 무장이 있는 인근 거점이 있는지 확인
			int target = getFRONTPerson(dst_base);
			if (target == -1) return false;
            
            // 지원가능 무장 소속거점
            pk::building@ src_base = pk::get_building(target);
            
            // 미행동 무장리스트
			pk::force@ force = pk::get_force( src_base.get_force_id());

            // 장수 보내는 곳과 받는 곳 국적이 같아야
		if (dst_base.get_force_id() != src_base.get_force_id()) return false;

            int count = pk::get_person_list(src_base, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반)).count;   
            auto person_list = pk::get_idle_person_list(src_base);
            if (count <  float( pk::get_person_list(force, pk::mibun_flags(신분_도독,신분_태수,신분_일반)).count / float(pk::get_city_count(force) )) * 0.2f ) return false;   // 무장 부족
          
            // 5개 능력치 총합 행선지 상황따라 정렬.

            pk::city@ city_s = pk::get_city(pk::get_city_id(src_base.pos));
            pk::city@ city_c = pk::get_city(pk::get_city_id(dst_base.pos));
            int enemy_weight = countNeighborEnemyBase(dst_base);


            // 경계 지역 이하의 저위험지역에서 전방으로 장수 보낼땐 군주를 나중에 보내라. 나머지는 능력치 높은 장수들부터 보내라.
			
if ( ( 0 == func_enemy_city_count(city_s, 2)  or ( 1 <= func_enemy_city_count(city_s, 2) and 0 == func_enemy_city_count(city_s, 1) ) ) and dst_base.get_force_id() == src_base.get_force_id() )

			person_list.sort(function(a, b)
			{
				if ((a.mibun == 신분_군주 and b.mibun != 신분_군주) or (a.mibun != 신분_군주 and b.mibun == 신분_군주))
					return a.mibun > b.mibun;	
				
return (a.stat[무장능력_무력] + a.stat[무장능력_통솔] + a.stat[무장능력_지력] + a.stat[무장능력_정치] + a.stat[무장능력_매력]) > (b.stat[무장능력_무력] + b.stat[무장능력_통솔] + b.stat[무장능력_지력] + b.stat[무장능력_정치] + b.stat[무장능력_매력]);
	
			});


            // 전방에서 전방으로 장수 보낼땐 군주를 나중에 보내라. 나머지는 능력치 낮은 장수들부터 보내라.

if ( 1 <= func_enemy_city_count(city_s, 1) and dst_base.get_force_id() == src_base.get_force_id() )

			person_list.sort(function(a, b)
			{
				if ((a.mibun == 신분_군주 and b.mibun != 신분_군주) or (a.mibun != 신분_군주 and b.mibun == 신분_군주))
					return a.mibun > b.mibun;	
				
return (a.stat[무장능력_무력] + a.stat[무장능력_통솔] + a.stat[무장능력_지력] + a.stat[무장능력_정치] + a.stat[무장능력_매력]) < (b.stat[무장능력_무력] + b.stat[무장능력_통솔] + b.stat[무장능력_지력] + b.stat[무장능력_정치] + b.stat[무장능력_매력]);

			});



            
            // 소환할 무장수
            int max = pk::max( 1 , pk::min(1, person_list.count * 0.05) );
            
            // 소환 대상 무장 (소속과 소재거점이 다르면 제외, 같고 보내려는 장수와 보내는 도시의 국적이 같으면 보내라)
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
        int getFRONTPerson(pk::building@ dst)
		{
			int best_src = -1;
			int best_distance = 0;
             pk::list<pk::building@> src_list; 			
            
			// 거점까지 확인.
			for (int i = 0; i < 건물_도시끝; i++)
			{
				pk::building@ src = pk::get_building(i);
                
				if (dst.get_id() != i and dst.get_force_id() == src.get_force_id()  )
                {
                    int distance = pk::get_city_distance(src.get_id(), dst.get_id());
                    int count = pk::get_person_list(src, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반)).count; 
                    int count_dst = pk::get_person_list(dst, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반)).count;  		
                    auto person_idle_list = pk::get_idle_person_list(src);


            int src_id = src.get_id();
            int dst_id = dst.get_id();

            pk::city@ city_d = pk::get_city(pk::get_city_id(src.pos));
            int enemy_weight = countNeighborEnemyBase(src);

	    pk::force@ force_s = pk::get_force(src.get_force_id());
 
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


			auto range = pk::range(dst.get_pos(), 1, 14);
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
						if (distance <= 14)
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

 
                    int max_distance = 12;
                    if (!force_s.is_player() and (0 <= distance and distance <= max_distance))
                    {


			pk::force@ force = pk::get_force(dst.get_force_id());
			if ( distance <= 12 )			
                        {

// 후방에 장수 숫자가 많을 때  (내정 개발 건설 완료 조건에 따라 2분류)

if ( person_idle_list.count > 0 and (count >= count_dst or count > 0.7f * float( pk::get_person_list(force, pk::mibun_flags(신분_도독,신분_태수,신분_일반)).count / float(pk::get_city_count(force) ))) and pk::is_alive(src) and pk::is_alive(dst) and src_id != dst_id and src.get_force_id() == dst.get_force_id() and 0 == func_enemy_city_count(city_d, 2) and 0 == func_user_city_count(city_d, 1) and  0 == enemy_weight and ( check_city_dev_complete(city_d) or 0 < enemy_units3 ) )
                        {
                        best_src = src_id;
                        src_list.add(src);  // 수송가능 거점리스트 추가
                        }


if ( person_idle_list.count > 0 and (count >  2.5f * float( pk::get_person_list(force, pk::mibun_flags(신분_도독,신분_태수,신분_일반)).count / float(pk::get_city_count(force) ))) and pk::is_alive(src) and pk::is_alive(dst) and src_id != dst_id and src.get_force_id() == dst.get_force_id() and 0 == func_enemy_city_count(city_d, 2) and 0 == func_user_city_count(city_d, 1) and  0 == enemy_weight and !check_city_dev_complete(city_d) )
                        {
                        best_src = src_id;
                        src_list.add(src);  // 수송가능 거점리스트 추가
                        }


// 그 다음은 장수 숫자가 좀 있는 경계에서라도  (내정 개발 건설 완료 조건에 따라 2분류)

else if ( person_idle_list.count > 0 and (count >= count_dst or count >  1.3f * float( pk::get_person_list(force, pk::mibun_flags(신분_도독,신분_태수,신분_일반)).count / float(pk::get_city_count(force) ))) and pk::is_alive(src) and pk::is_alive(dst) and src_id != dst_id and src.get_force_id() == dst.get_force_id() and ( (1 <= func_enemy_city_count(city_d, 2) and 0 == func_enemy_city_count(city_d, 1) and 0 == enemy_weight) or 1 <= func_user_city_count(city_d, 1) ) and ( check_city_dev_complete(city_d) or 0 < enemy_units3 ) )
                        {
                        best_src = src_id;
                        src_list.add(src);  // 수송가능 거점리스트 추가
                        }


else if ( person_idle_list.count > 0 and (count >  2.5f * float( pk::get_person_list(force, pk::mibun_flags(신분_도독,신분_태수,신분_일반)).count / float(pk::get_city_count(force) ))) and pk::is_alive(src) and pk::is_alive(dst) and src_id != dst_id and src.get_force_id() == dst.get_force_id() and ( (1 <= func_enemy_city_count(city_d, 2) and 0 == func_enemy_city_count(city_d, 1) and 0 == enemy_weight) or 1 <= func_user_city_count(city_d, 1) ) and !check_city_dev_complete(city_d) )
                        {
                        best_src = src_id;
                        src_list.add(src);  // 수송가능 거점리스트 추가
                        }

// 최후엔 전방에 잉여 장수 많은 도시에서라도 (세력의 도시 모두 전방인 경우와 아닌 경우 나눠서)

else if (pk::get_city_list(force_s).count == func_FRONT_city_count(force_s) and person_idle_list.count > count_dst and (count > count_dst + 2 or count >  1.2f * float( pk::get_person_list(force, pk::mibun_flags(신분_도독,신분_태수,신분_일반)).count / float(pk::get_city_count(force) ))) and pk::is_alive(src) and pk::is_alive(dst) and src_id != dst_id and src.get_force_id() == dst.get_force_id() and (1 <= func_enemy_city_count(city_d, 1) or 0 < enemy_weight) and count > count_dst + 2)
                        {
                        best_src = src_id;
                        src_list.add(src);  // 수송가능 거점리스트 추가
                        }

				   
				   

else if (pk::get_city_list(force_s).count > func_FRONT_city_count(force_s) and person_idle_list.count > 10 and (count > count_dst + 2 or count >  1.5f * float( pk::get_person_list(force, pk::mibun_flags(신분_도독,신분_태수,신분_일반)).count / float(pk::get_city_count(force) ))) and pk::is_alive(src) and pk::is_alive(dst) and src_id != dst_id and src.get_force_id() == dst.get_force_id() and (1 <= func_enemy_city_count(city_d, 1) or 0 < enemy_weight) and count > count_dst + 2)
                        {
                        best_src = src_id;
                        src_list.add(src);  // 수송가능 거점리스트 추가
                        }

                        }
                    }
                }
			}
			
            if (src_list.count == 0)
                best_src = -1;
            else
            {
                src_list.sort(function(a, b)
                {
                    int build_dist_a = pk::get_building_distance(a.get_id(), main.dst_FRONT.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.dst_FRONT.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.dst_FRONT.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.dst_FRONT.pos);

            auto person_list_a = pk::get_idle_person_list(a);
            auto person_list_b = pk::get_idle_person_list(b);

                    return (person_list_a.count - build_dist_a > person_list_b.count - build_dist_b );
			
                    if (build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);
                    
                    return (pos_dist_a < pos_dist_b);
                });
                best_src = src_list[0].get_id();
            }			
			
			return best_src;
		}
        
         










        //----------------------------------------------------------------------------------
        //  전방 도시에 병력 5천 당 무장 1명 배치
        //----------------------------------------------------------------------------------



        /** 병력 5천 당 무장 수가 적은 거점에 파견이 필요한지 판단 **/
        bool needUnitleader(pk::building@ base)
		{

            if (!pk::is_alive(base)) return false;

			if (base.get_force_id() == -1) return false;

			pk::force@ force = pk::get_force(base.get_force_id());
			int force_id = force.get_id();



                // 플레이어, 이민족 세력은 제외.
                if (!force.is_player() and pk::is_normal_force(force_id))
			{
            pk::city@ city_a = pk::get_city(pk::get_city_id(base.pos));
            int count = pk::get_idle_person_list(base).count;
            int enemy_weight = countNeighborEnemyBase(base);

 if ( ( pk::get_troops(base) <= 4500 or base.hp <= 700 ) and pk::enemies_around(base) ) 
            return false;
		
if (count + func_already(base) <=  float ( pk::get_troops(base) / 5000.f ) and (1 <= func_enemy_city_count(city_a, 1) or 0 < enemy_weight) and 건물_파양항 != base.get_id() and 건물_노릉항 != base.get_id() and 건물_서하항 != base.get_id() and 건물_하양항 != base.get_id() and 건물_해현항 != base.get_id() and 건물_강도항 != base.get_id() and 건물_도시시작 <= base.get_id() and base.get_id() < 건물_도시끝) 

                return true;
            }        
            return false;
        }
        
        // ***** 무장 지원 명령 ***** //
        pk::building@ dst_Unitleader;		
        bool PushUnitleader(pk::building@ dst_base)
        {
            @dst_Unitleader = @dst_base;			
            // 무장이 있는 인근 거점이 있는지 확인
			int target = getNearestPerson1(dst_base);
			if (target == -1) return false;
            
            // 지원가능 무장 소속거점
            pk::building@ src_base = pk::get_building(target);
            
            // 미행동 무장리스트
			pk::force@ force = pk::get_force( src_base.get_force_id());

            // 장수 보내는 곳과 받는 곳 국적이 같아야
		if (dst_base.get_force_id() != src_base.get_force_id()) return false;
 
            auto person_list = pk::get_idle_person_list(src_base);
            if (person_list.count <  float( pk::get_person_list(force, pk::mibun_flags(신분_도독,신분_태수,신분_일반)).count / float( pk::get_city_count(force) )) * 0.2f ) return false;   // 무장 부족
          
            // 5개 능력치 총합 행선지 상황따라 정렬.

            pk::city@ city_s = pk::get_city(pk::get_city_id(src_base.pos));
            pk::city@ city_c = pk::get_city(pk::get_city_id(dst_base.pos));
            int enemy_weight = countNeighborEnemyBase(dst_base);

            // 경계 지역 이하의 저위험지역에서 전방으로 장수 보낼땐 군주를 나중에 보내라. 나머지는 능력치 높은 장수들부터 보내라.

if ( ( 0 == func_enemy_city_count(city_s, 2)  or ( 1 <= func_enemy_city_count(city_s, 2)  and  0 == func_enemy_city_count(city_s, 1) ) ) and dst_base.get_force_id() == src_base.get_force_id() )

			person_list.sort(function(a, b)
			{
				if ((a.mibun == 신분_군주 and b.mibun != 신분_군주) or (a.mibun != 신분_군주 and b.mibun == 신분_군주))
					return a.mibun > b.mibun;						

return (a.stat[무장능력_무력] + a.stat[무장능력_통솔] + a.stat[무장능력_지력] + a.stat[무장능력_정치] + a.stat[무장능력_매력]) > (b.stat[무장능력_무력] + b.stat[무장능력_통솔] + b.stat[무장능력_지력] + b.stat[무장능력_정치] + b.stat[무장능력_매력]);

			});


            // 전방에서 전방으로 장수 보낼땐 군주를 나중에 보내라. 나머지는 능력치 낮은 장수들부터 보내라.

if ( 1 <= func_enemy_city_count(city_s, 1) and dst_base.get_force_id() == src_base.get_force_id())

			person_list.sort(function(a, b)
			{
				if ((a.mibun == 신분_군주 and b.mibun != 신분_군주) or (a.mibun != 신분_군주 and b.mibun == 신분_군주))
					return a.mibun > b.mibun;		
				
return (a.stat[무장능력_무력] + a.stat[무장능력_통솔] + a.stat[무장능력_지력] + a.stat[무장능력_정치] + a.stat[무장능력_매력]) < (b.stat[무장능력_무력] + b.stat[무장능력_통솔] + b.stat[무장능력_지력] + b.stat[무장능력_정치] + b.stat[무장능력_매력]);

			});



            
            // 소환할 무장수
            int max = pk::max( 1 , pk::min(3, person_list.count * 0.05) );
            
            // 소환 대상 무장 (소속과 소재거점이 다르면 제외, 같고 보내려는 장수와 보내는 도시의 국적이 같으면 보내라)
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
        int getNearestPerson1(pk::building@ dst)
		{
			int best_src = -1;
			int best_distance = 0;
             pk::list<pk::building@> src_list; 			
            
			// 거점까지 확인.
			for (int i = 0; i < 건물_도시끝; i++)
			{
				pk::building@ src = pk::get_building(i);
                
				if (dst.get_id() != i and dst.get_force_id() == src.get_force_id()  )
                {
                    int distance = pk::get_city_distance(src.get_id(), dst.get_id());
                    
                    auto person_list = pk::get_idle_person_list(src);

            int src_id = src.get_id();
            int dst_id = dst.get_id();

            pk::city@ city_d = pk::get_city(pk::get_city_id(src.pos));
            int enemy_weight = countNeighborEnemyBase(src);

	    pk::force@ force_s = pk::get_force(src.get_force_id());

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


			auto range = pk::range(dst.get_pos(), 1, 14);
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
						if (distance <= 14)
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


                    
                    int max_distance = 12;
                    if (!force_s.is_player() and (0 <= distance and distance <= max_distance))
                    {


			pk::force@ force = pk::get_force(dst.get_force_id());
			if ( distance <= 12 )				
                        {
// 후방에 장수 숫자가 많을 때  (내정 개발 건설 완료 조건에 따라 2분류)

if ( (person_list.count > 0.7f * float( pk::get_person_list(force, pk::mibun_flags(신분_도독,신분_태수,신분_일반)).count / float( pk::get_city_count(force) ))) and pk::is_alive(src) and pk::is_alive(dst) and src_id != dst_id and src.get_force_id() == dst.get_force_id() and 0 == func_enemy_city_count(city_d, 2) and 0 == func_user_city_count(city_d, 1) and  0 == enemy_weight and ( check_city_dev_complete(city_d) or 0 < enemy_units3 ) )
                        {
                        best_src = src_id;
                        src_list.add(src);  // 수송가능 거점리스트 추가
                        }


if ( (person_list.count >  2.5f * float( pk::get_person_list(force, pk::mibun_flags(신분_도독,신분_태수,신분_일반)).count / float( pk::get_city_count(force) ))) and pk::is_alive(src) and pk::is_alive(dst) and src_id != dst_id and src.get_force_id() == dst.get_force_id() and 0 == func_enemy_city_count(city_d, 2) and 0 == func_user_city_count(city_d, 1) and  0 == enemy_weight and !check_city_dev_complete(city_d) )
                        {
                        best_src = src_id;
                        src_list.add(src);  // 수송가능 거점리스트 추가
                        }
						

// 그 다음은 장수 숫자가 좀 있는 경계에서라도  (내정 개발 건설 완료 조건에 따라 2분류)

else if ( (person_list.count > 1.3f * float( pk::get_person_list(force, pk::mibun_flags(신분_도독,신분_태수,신분_일반)).count / float( pk::get_city_count(force) ))) and pk::is_alive(src) and pk::is_alive(dst) and src_id != dst_id and src.get_force_id() == dst.get_force_id() and ( (1 <= func_enemy_city_count(city_d, 2) and 0 == func_enemy_city_count(city_d, 1) and  0 == enemy_weight) or 1 <= func_user_city_count(city_d, 1) ) and ( check_city_dev_complete(city_d) or 0 < enemy_units3 ) )
                        {
                        best_src = src_id;
                        src_list.add(src);  // 수송가능 거점리스트 추가
                        }


else if ( (person_list.count >  2.5f * float( pk::get_person_list(force, pk::mibun_flags(신분_도독,신분_태수,신분_일반)).count / float( pk::get_city_count(force) ))) and pk::is_alive(src) and pk::is_alive(dst) and src_id != dst_id and src.get_force_id() == dst.get_force_id() and ( (1 <= func_enemy_city_count(city_d, 2) and 0 == func_enemy_city_count(city_d, 1) and  0 == enemy_weight) or 1 <= func_user_city_count(city_d, 1) ) and !check_city_dev_complete(city_d) )
                        {
                        best_src = src_id;
                        src_list.add(src);  // 수송가능 거점리스트 추가
                        }


// 최후엔 전방에 잉여 장수 많은 도시에서라도

				   
				   
				   

else if ( (person_list.count > 3.1f * float( pk::get_person_list(force, pk::mibun_flags(신분_도독,신분_태수,신분_일반)).count / float( pk::get_city_count(force) ))) and pk::is_alive(src) and pk::is_alive(dst) and src_id != dst_id and src.get_force_id() == dst.get_force_id() and (1 <= func_enemy_city_count(city_d, 1) or 0 < enemy_weight) and pk::get_person_list(dst, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반)).count + 2 < pk::get_person_list(src, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반)).count)
                        {
                        best_src = src_id;
                        src_list.add(src);  // 수송가능 거점리스트 추가
                        }



                        }
                    }
                }
			}
			
            if (src_list.count == 0)
                best_src = -1;
            else
            {
                src_list.sort(function(a, b)
                {
                    int build_dist_a = pk::get_building_distance(a.get_id(), main.dst_Unitleader.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.dst_Unitleader.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.dst_Unitleader.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.dst_Unitleader.pos);

            auto person_list_a = pk::get_idle_person_list(a);
            auto person_list_b = pk::get_idle_person_list(b);

                    return (person_list_a.count - build_dist_a > person_list_b.count - build_dist_b );
			
                    if (build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);
                    
                    return (pos_dist_a < pos_dist_b);
                });
                best_src = src_list[0].get_id();
            }			
			
			return best_src;
		}






        //----------------------------------------------------------------------------------
        //  도시 내 86 이상 장수들 파악
        //----------------------------------------------------------------------------------



	int above86count(pk::force@ force, int attributes)
	{

            int above_count = 0;
           
  if (pk::is_alive(force))
        {
            auto list = pk::list_to_array(pk::get_person_list(force, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반) ) );
            if (0 < list.length)
            {
                for (int i = 0; i < int(list.length); i++)
                {
                    pk::person@ person = list[i];

                       if (person.stat[attributes] >= 86)
				above_count++;
                }
            }
        }
            return above_count;

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
                
if (src_id != dst_id and pk::is_neighbor_base(src_id, dst_id) and pk::is_enemy(src, dst) and (건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id ) )
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
		

         //  한 세력의 전방 도시 숫자 체크, masterpiecek님의 AI_도시물자수송.cpp﻿를 참조했습니다.

		int func_FRONT_city_count(pk::force@ force)
		{
			int FRONT_city_count = 0;
			for (int i = 0; i < 도시_끝; i++)
			{
				pk::city@ FRONTcity = pk::get_city(i);

			        int force_id = force.get_id();

				if (pk::is_alive(FRONTcity) and pk::is_normal_force(force_id) and FRONTcity.get_force_id() == force_id and 1 <= func_enemy_city_count(FRONTcity, 1)) 

				FRONT_city_count++;
																	  										  				   
			}

			return FRONT_city_count;
		}	

        // 내정시설 건설율 100% 여부 확인
        bool check_city_dev_complete(pk::city@ city)
        {
            if (city.num_devs < city.max_devs * 0.7f )
                return false;
            
            return true;
        }


	};

	Main main;
}