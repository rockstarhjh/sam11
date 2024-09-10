/*
제작 by 일송정

본 스크립트는 기마책사님이 제작하신 거점원군.cpp와 기마책사님이 수정하신 거점철수.cpp의 상당 부분을 차용하고 있음을 알려드립니다. 
기마책사님께 감사드립니다.

*/

namespace 병기반송
{

    //---------------------------------------------------------------------------------------
    // 유저 설정_기마책사님 자료에서 따옴
    
    const bool  거점수송_원거리이동  = true;     // 수송부대 이동 1회 추가 (추천기능 : 보너스이동으로 탈출)
    const bool  거점수송_일시도주설정 = false;     // 수송부대 출진순간 도주효과 일시적용 (추천기능 : 포위망 돌파가능)
    const int   거점수송_거점검색모드 = 1;       // 0: 도시만 검색하여 수송,  1: 도시+관문+항구 모두 검색하여 수송   

    const bool  위임군단_수송관할_지정여부  = true;    //플레이어 위임군단이 수송을 보낼 수 있는 군단 구분해줄 것인지 여부, false면 모든 군단 상대로 수송대 보냄

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
			if (pk::is_normal_force(force_id) and pk::get_elapsed_months() > 3)
			{
				for (int i = 0; i < 건물_거점끝; i++)
				{
					auto base = pk::get_building(i);
                                        pk::district@ district = pk::get_district(base.get_district_id());


	if (!force.is_player() or ( force.is_player() and !pk::is_player_controlled(base) and pk::is_alive(district) and district.transport ) )

		{

                    if (base.get_force_id() == force_id and sendWeapon(base))
                        receiveWeapon(base);

                    if (base.get_force_id() == force_id and ExtraWartimeWeapon(base))
                        sendEXweapon(base);

                    if (base.get_force_id() == force_id and needEXweapon(base))
                        PushEXweapon(base);


                    if (base.get_force_id() == force_id and needEXSweapon(base))
                        PushEXSweapon(base);


                    if (base.get_force_id() == force_id and needEXWweapon(base))
                        PushEXWweapon(base);

		}

					
				}
			}

			// 이전 핸들러가 있다면 체인.
			if (prev_callback_ !is null)
				return prev_callback_(force);
			return false;
		}







        //----------------------------------------------------------------------------------
        //  일반 병기가 부족한 거점으로 병기들을 보내기 
        //----------------------------------------------------------------------------------




		/** 병력 있는 거점 찾기 */

		bool sendWeapon(pk::building@ src)
		{
			if (!no_enemy_around(src)) return false;
            int src_id = src.get_id();
                        int enemy_weight = countNeighborEnemyBase(src);
            pk::city@ city_a = pk::get_city(pk::get_city_id(src.pos));
			
            if (건물_파양항 == src_id or 건물_노릉항 == src_id or 건물_서하항 == src_id or 건물_하양항 == src_id or 건물_해현항 == src_id or 건물_강도항 == src_id) return false;			

	// 병기들 총합이 3만 이상인 적 침공에서 안전한 도시에서 보급 보내라
                    
if (건물_도시시작 <= src_id and src_id < 건물_도시끝 and pk::get_weapon_amount(src, 병기_창) + pk::get_weapon_amount(src, 병기_극) + pk::get_weapon_amount(src, 병기_노) + pk::get_weapon_amount(src, 병기_군마) >= 30000 
and pk::get_troops(src) >= 9000 )
				return true;



   //병기들 총합이 병력 숫자의 1.5배 이상인 적 침공에서 안전한 관문, 항구에서 보급 보내라

else if (건물_관문시작 <= src_id and src_id < 건물_항구끝 and pk::get_weapon_amount(src, 병기_창) + pk::get_weapon_amount(src, 병기_극) + pk::get_weapon_amount(src, 병기_노) + pk::get_weapon_amount(src, 병기_군마) >= pk::get_troops(src) * 1.5f 
and pk::get_troops(src) >= 5000 and 건물_파양항 != src_id and 건물_노릉항 != src_id and 건물_서하항 != src_id and 건물_하양항 != src_id and 건물_해현항 != src_id and 건물_강도항 != src_id)
				return true;

            
			return false;
		}







		/** 병기 20% 최대 15000 보급 명령 (나머지 15%)  */

		bool receiveWeapon(pk::building@ base)
		{
            int reinforce_troops = pk::min(1000,  int (pk::get_troops(base) * 0.15f) );
			// 명령 가능한 무장이 있는지 확인.
			auto person_list = pk::get_idle_person_list(base);
			if (person_list.count == 0) return false;

			// 인접 거접이 있는지 확인.
			int target = getNWBase(base);
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
			cmd.gold = pk::min(int(pk::get_gold(base) * 0.15f), 10000);
			cmd.food = pk::min(pk::max (1000 , unit_food), 25000);
			cmd.troops = reinforce_troops;
			int i = 0;
			for (int weapon_id = 0; weapon_id < 병기_끝; weapon_id++)
			{
                int weapon_amount = 0;
                if (weapon_id < 병기_충차)
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id) * 0.25f), 15000);
                else
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id)), 2);
                
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
                pk::say(pk::u8encode(pk::format("일반병기들이 부족한 아군 거점이 있다!\n\x1b[2x{}\x1b[0x(으)로 병기들을 보내자!", target_name)), leader);	

            
            // 임시 도주 효과 ('19.3.6)
            if (거점수송_일시도주설정)
            {
                leader.skill = retreat_skill;         // 특기 복원
            }
            
            
			return true;
		}





        
		/** 가장 가까운아군 도시에 보급을 보냄 */

        pk::building@ src_sW;
		int getNWBase(pk::building@ src)
		{
			int best_dst = -1;
			int best_distance = 0;
            int src_id = src.get_id();
            pk::list<pk::building@> dst_list; 
			dst_list.clear();			
            @src_sW = @src;



            
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
                    
              if (건물_파양항 == dst_id or 건물_노릉항 == dst_id or 건물_서하항 == dst_id or 건물_하양항 == dst_id or 건물_해현항 == dst_id or 건물_강도항 == dst_id) continue;

                    // 거리 조건 만족 시 (거리 1~3)
                if ( (base_dist == 1 and !intercept1_Enemy_base(src, dst) and !intercept_delta_Enemy_base(src, dst)) or ((base_dist == 2 or (city_dist == 1 and base_dist <= 3)) and !intercept2_Enemy_base(src, dst) and !intercept_delta_Enemy_base(src, dst)) ) 
                    {


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

                        int enemy_weight = countNeighborEnemyBase(dst);
			pk::city@ city_c = pk::get_city(pk::get_city_id(dst.pos));

 if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst))
     {

	//  일반 병기 총합이 13000 이하고 병력의 0.6배 이하인 거점

			if (pk::get_weapon_amount(dst, 병기_창) + pk::get_weapon_amount(dst, 병기_극) + pk::get_weapon_amount(dst, 병기_노) + pk::get_weapon_amount(dst, 병기_군마) <= 13000
			and pk::get_weapon_amount(dst, 병기_창) + pk::get_weapon_amount(dst, 병기_극) + pk::get_weapon_amount(dst, 병기_노) + pk::get_weapon_amount(dst, 병기_군마) <= pk::get_troops(dst) * 0.6f
			and func_already (dst) <= 6
			and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id)
                    {
						if (enemy_inside(src, dst)) continue;							
						
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
                    return ((pk::get_weapon_amount(a, 병기_창) + pk::get_weapon_amount(a, 병기_극) + pk::get_weapon_amount(a, 병기_노) + pk::get_weapon_amount(a, 병기_군마) + 1) / float(pk::get_troops(a) + 1) < (pk::get_weapon_amount(b, 병기_창) + pk::get_weapon_amount(b, 병기_극) + pk::get_weapon_amount(b, 병기_노) + pk::get_weapon_amount(b, 병기_군마) + 1) / float(pk::get_troops(b) + 1) );

                    int build_dist_a = pk::get_building_distance(a.get_id(), main.src_sW.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.src_sW.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.src_sW.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.src_sW.pos);

                    if ((pk::get_weapon_amount(a, 병기_창) + pk::get_weapon_amount(a, 병기_극) + pk::get_weapon_amount(a, 병기_노) + pk::get_weapon_amount(a, 병기_군마) + 1) / float(pk::get_troops(a) + 1) == (pk::get_weapon_amount(b, 병기_창) + pk::get_weapon_amount(b, 병기_극) + pk::get_weapon_amount(b, 병기_노) + pk::get_weapon_amount(b, 병기_군마) + 1) / float(pk::get_troops(b) + 1) 
					     and build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);

                    if ((pk::get_weapon_amount(a, 병기_창) + pk::get_weapon_amount(a, 병기_극) + pk::get_weapon_amount(a, 병기_노) + pk::get_weapon_amount(a, 병기_군마) + 1) / float(pk::get_troops(a) + 1) == (pk::get_weapon_amount(b, 병기_창) + pk::get_weapon_amount(b, 병기_극) + pk::get_weapon_amount(b, 병기_노) + pk::get_weapon_amount(b, 병기_군마) + 1) / float(pk::get_troops(b) + 1)
					     and build_dist_a == build_dist_b)                    
                    return (pos_dist_a < pos_dist_b);
                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
		}







        //----------------------------------------------------------------------------------
        //  전투 중인 항관에서도 병기가 너무 많으면 인근 도시로 수송  (군량)
        //----------------------------------------------------------------------------------




		/** 병력 있는 거점 찾기 */

		bool ExtraWartimeWeapon(pk::building@ base)
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

				}
			}

			if (enemy_units1 >= 10)  // 거점 포위 상태로 수송 불가
				return false;
						
			int base_troops = pk::get_troops(base);


                        int enemy_weight = countNeighborEnemyBase(base);
            pk::city@ city_a = pk::get_city(pk::get_city_id(base.pos));


	//  일반 병기 중 한 품목이라도 40000 이상인 , 적 침공에서 안전한 병력 2천 이상 관문, 항구에서 보급 보내라

if ((40000 <= pk::get_weapon_amount(base, 병기_창) or 40000 <= pk::get_weapon_amount(base, 병기_극) or 40000 <= pk::get_weapon_amount(base, 병기_노) or 40000 <= pk::get_weapon_amount(base, 병기_군마))
and 건물_관문시작 <= base.get_id() and base.get_id() < 건물_항구끝 and force_units7 > 0 and enemy_troops3 > 0 and enemy_units3 > 0 and 6800 <= pk::get_troops(base) )
				return true;

            
			return false;
		}







		/** 병기 20% 최대 15000 보급 명령 (나머지 15%)  */

		bool sendEXweapon(pk::building@ base)
		{
            int reinforce_troops = pk::min(1000,  int (pk::get_troops(base) * 0.15f) );
			// 명령 가능한 무장이 있는지 확인.
			auto person_list = pk::get_idle_person_list(base);
			if (person_list.count == 0) return false;

			// 인접 거접이 있는지 확인.
			int target = getfreeWeaponBase(base);
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
			cmd.gold = pk::min(int(pk::get_gold(base) * 0.15f), 10000);
			cmd.food = pk::min(pk::max (1000 , unit_food), 25000);
			cmd.troops = reinforce_troops;
			int i = 0;
			for (int weapon_id = 0; weapon_id < 병기_끝; weapon_id++)
			{
                int weapon_amount = 0;
                if (weapon_id < 병기_충차)
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id) * 0.35f), 15000);
                else
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id)), 2);
                
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
                pk::say(pk::u8encode(pk::format("전방 항관이지만 일반병기 재고 초과다!\n\x1b[2x{}\x1b[0x(으)로 병기들을 보내자!", target_name)), leader);	

            
            // 임시 도주 효과 ('19.3.6)
            if (거점수송_일시도주설정)
            {
                leader.skill = retreat_skill;         // 특기 복원
            }
            
            
			return true;
		}





        
		/** 가장 가까운아군 도시에 보급을 보냄 */

        pk::building@ src_efw;
		int getfreeWeaponBase(pk::building@ src)
		{
			int best_dst = -1;
			int best_distance = 0;
            int src_id = src.get_id();
            pk::list<pk::building@> dst_list; 
			dst_list.clear();			
            @src_efw = @src;



            
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


                        int enemy_weight = countNeighborEnemyBase(dst);
			pk::city@ city_c = pk::get_city(pk::get_city_id(dst.pos));

 if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst))
 {

	// 병기들이 각각 5만 이하로, 적 침공에서 안전한 도시로 보급 보내라
                    
if (건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and (50000 >= pk::get_weapon_amount(dst, 병기_창) and 50000 >= pk::get_weapon_amount(dst, 병기_극) and 50000 >= pk::get_weapon_amount(dst, 병기_노) and 50000 >= pk::get_weapon_amount(dst, 병기_군마)) and func_already (dst) <= 6  )
                    {
             if (!enemy_inside(src, dst))
                        {
						if (dst.hp <= 700 and pk::enemies_around(dst)) continue;
						if (enemy_approach(dst)) continue;							
							
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
                        }
                    }



           //병기들이 각각 10000 이하로, 적 침공에서 안전한 관문, 항구로 보급 보내라

else if (건물_관문시작 <= dst_id and dst_id < 건물_항구끝 and (10000 >= pk::get_weapon_amount(dst, 병기_창) and 10000 >= pk::get_weapon_amount(dst, 병기_극) and 10000 >= pk::get_weapon_amount(dst, 병기_노) and 10000 >= pk::get_weapon_amount(dst, 병기_군마)) and base2_troops <= pk::get_max_troops(dst) * 0.7 and func_already (dst) <= 6 and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id)
                    {
             if (!enemy_inside(src, dst))
                        {
						if (dst.hp <= 700 and pk::enemies_around(dst)) continue;
						if (enemy_approach(dst)) continue;								
							
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
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
                    return ((pk::get_max_weapon_amount(a, 병기_창) + pk::get_max_weapon_amount(a, 병기_극) + pk::get_max_weapon_amount(a, 병기_노) + pk::get_max_weapon_amount(a, 병기_군마)) - (pk::get_weapon_amount(a, 병기_창) + pk::get_weapon_amount(a, 병기_극) + pk::get_weapon_amount(a, 병기_노) + pk::get_weapon_amount(a, 병기_군마)) > (pk::get_max_weapon_amount(b, 병기_창) + pk::get_max_weapon_amount(b, 병기_극) + pk::get_max_weapon_amount(b, 병기_노) + pk::get_max_weapon_amount(b, 병기_군마)) - (pk::get_weapon_amount(b, 병기_창) + pk::get_weapon_amount(b, 병기_극) + pk::get_weapon_amount(b, 병기_노) + pk::get_weapon_amount(b, 병기_군마)));

                    int build_dist_a = pk::get_building_distance(a.get_id(), main.src_efw.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.src_efw.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.src_efw.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.src_efw.pos);

                    if ((pk::get_max_weapon_amount(a, 병기_창) + pk::get_max_weapon_amount(a, 병기_극) + pk::get_max_weapon_amount(a, 병기_노) + pk::get_max_weapon_amount(a, 병기_군마)) - (pk::get_weapon_amount(a, 병기_창) + pk::get_weapon_amount(a, 병기_극) + pk::get_weapon_amount(a, 병기_노) + pk::get_weapon_amount(a, 병기_군마)) 
						== (pk::get_max_weapon_amount(b, 병기_창) + pk::get_max_weapon_amount(b, 병기_극) + pk::get_max_weapon_amount(b, 병기_노) + pk::get_max_weapon_amount(b, 병기_군마)) - (pk::get_weapon_amount(b, 병기_창) + pk::get_weapon_amount(b, 병기_극) + pk::get_weapon_amount(b, 병기_노) + pk::get_weapon_amount(b, 병기_군마))
					     and build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);

                    if ((pk::get_max_weapon_amount(a, 병기_창) + pk::get_max_weapon_amount(a, 병기_극) + pk::get_max_weapon_amount(a, 병기_노) + pk::get_max_weapon_amount(a, 병기_군마)) - (pk::get_weapon_amount(a, 병기_창) + pk::get_weapon_amount(a, 병기_극) + pk::get_weapon_amount(a, 병기_노) + pk::get_weapon_amount(a, 병기_군마)) 
						== (pk::get_max_weapon_amount(b, 병기_창) + pk::get_max_weapon_amount(b, 병기_극) + pk::get_max_weapon_amount(b, 병기_노) + pk::get_max_weapon_amount(b, 병기_군마)) - (pk::get_weapon_amount(b, 병기_창) + pk::get_weapon_amount(b, 병기_극) + pk::get_weapon_amount(b, 병기_노) + pk::get_weapon_amount(b, 병기_군마))
					     and build_dist_a == build_dist_b)                    
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
        //  일반 병기 포화 상태일때 다른 곳으로 배분 
        //----------------------------------------------------------------------------------




		/** 병력 있는 거점 찾기 */

		bool needEXweapon(pk::building@ base)
		{
			if (!no_enemy_around(base)) return false;

			int base_troops = pk::get_troops(base);


                        int enemy_weight = countNeighborEnemyBase(base);
            pk::city@ city_a = pk::get_city(pk::get_city_id(base.pos));

	//  일반 병기 중 한 품목이라도 40000 이상인 , 적 침공에서 안전한 병력 2천 이상 관문, 항구에서 보급 보내라

			if ( (40000 <= pk::get_weapon_amount(base, 병기_창) or 40000 <= pk::get_weapon_amount(base, 병기_극) or 40000 <= pk::get_weapon_amount(base, 병기_노) or 40000 <= pk::get_weapon_amount(base, 병기_군마)) and 2000 <= pk::get_troops(base) and 건물_관문시작 <= base.get_id() and base.get_id() < 건물_항구끝 )
				return true;


	// 일반 병기 중 한 품목이라도 80000 이상인, 적 침공에서 병력 4천 이상 안전한 도시에서 보급 보내라

			if ( (80000 <= pk::get_weapon_amount(base, 병기_창) or 80000 <= pk::get_weapon_amount(base, 병기_극) or 80000 <= pk::get_weapon_amount(base, 병기_노) or 80000 <= pk::get_weapon_amount(base, 병기_군마)) and 4000 <= pk::get_troops(base) and 건물_도시시작 <= base.get_id() and base.get_id() < 건물_도시끝 )
				return true;


            
			return false;
		}







		/** 병기 20% 최대 15000 보급 명령 (나머지 15%)  */

		bool PushEXweapon(pk::building@ base)
		{
            int reinforce_troops = pk::min(1000,  int (pk::get_troops(base) * 0.15f) );
			// 명령 가능한 무장이 있는지 확인.
			auto person_list = pk::get_idle_person_list(base);
			if (person_list.count == 0) return false;

			// 인접 거접이 있는지 확인.
			int target = getEXWBase(base);
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
			cmd.gold = pk::min(int(pk::get_gold(base) * 0.15f), 10000);
			cmd.food = pk::min(pk::max (1000 , unit_food), 25000);
			cmd.troops = reinforce_troops;
			int i = 0;
			for (int weapon_id = 0; weapon_id < 병기_끝; weapon_id++)
			{
                int weapon_amount = 0;
                if (weapon_id < 병기_충차)
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id) * 0.20f), 15000);
                else
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id)), 2);
                
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
                pk::say(pk::u8encode(pk::format("여긴 일반병기 재고 초과다!\n\x1b[2x{}\x1b[0x(으)로 병기들을 보내자!", target_name)), leader);

            
            // 임시 도주 효과 ('19.3.6)
            if (거점수송_일시도주설정)
            {
                leader.skill = retreat_skill;         // 특기 복원
            }
            
            
			return true;
		}





        
		/** 가장 가까운아군 도시에 보급을 보냄 */

        pk::building@ src_EXW;
		int getEXWBase(pk::building@ src)
		{
			int best_dst = -1;
			int best_distance = 0;
            int src_id = src.get_id();
            pk::list<pk::building@> dst_list; 
			dst_list.clear();			
            @src_EXW = @src;



            
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
				
												

                        int enemy_weight = countNeighborEnemyBase(dst);
			pk::city@ city_c = pk::get_city(pk::get_city_id(dst.pos));

 if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst))
     {

	// 병기들이 각각 5만 이하로, 적 침공에서 안전한 도시로 보급 보내라
                    
if (건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and (50000 >= pk::get_weapon_amount(dst, 병기_창) and 50000 >= pk::get_weapon_amount(dst, 병기_극) and 50000 >= pk::get_weapon_amount(dst, 병기_노) and 50000 >= pk::get_weapon_amount(dst, 병기_군마)) and func_already (dst) <= 6  )
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
                    }



           //병기들이 각각 10000 이하로, 적 침공에서 안전한 관문, 항구로 보급 보내라

else if (건물_관문시작 <= dst_id and dst_id < 건물_항구끝 and (10000 >= pk::get_weapon_amount(dst, 병기_창) and 10000 >= pk::get_weapon_amount(dst, 병기_극) and 10000 >= pk::get_weapon_amount(dst, 병기_노) and 10000 >= pk::get_weapon_amount(dst, 병기_군마)) and base2_troops <= pk::get_max_troops(dst) * 0.7 and func_already (dst) <= 6 and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id)
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
                    return ((pk::get_max_weapon_amount(a, 병기_창) + pk::get_max_weapon_amount(a, 병기_극) + pk::get_max_weapon_amount(a, 병기_노) + pk::get_max_weapon_amount(a, 병기_군마)) - (pk::get_weapon_amount(a, 병기_창) + pk::get_weapon_amount(a, 병기_극) + pk::get_weapon_amount(a, 병기_노) + pk::get_weapon_amount(a, 병기_군마)) > (pk::get_max_weapon_amount(b, 병기_창) + pk::get_max_weapon_amount(b, 병기_극) + pk::get_max_weapon_amount(b, 병기_노) + pk::get_max_weapon_amount(b, 병기_군마)) - (pk::get_weapon_amount(b, 병기_창) + pk::get_weapon_amount(b, 병기_극) + pk::get_weapon_amount(b, 병기_노) + pk::get_weapon_amount(b, 병기_군마)));

                    int build_dist_a = pk::get_building_distance(a.get_id(), main.src_EXW.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.src_EXW.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.src_EXW.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.src_EXW.pos);

                    if ((pk::get_max_weapon_amount(a, 병기_창) + pk::get_max_weapon_amount(a, 병기_극) + pk::get_max_weapon_amount(a, 병기_노) + pk::get_max_weapon_amount(a, 병기_군마)) - (pk::get_weapon_amount(a, 병기_창) + pk::get_weapon_amount(a, 병기_극) + pk::get_weapon_amount(a, 병기_노) + pk::get_weapon_amount(a, 병기_군마)) 
						== (pk::get_max_weapon_amount(b, 병기_창) + pk::get_max_weapon_amount(b, 병기_극) + pk::get_max_weapon_amount(b, 병기_노) + pk::get_max_weapon_amount(b, 병기_군마)) - (pk::get_weapon_amount(b, 병기_창) + pk::get_weapon_amount(b, 병기_극) + pk::get_weapon_amount(b, 병기_노) + pk::get_weapon_amount(b, 병기_군마))
					     and build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);

                    if ((pk::get_max_weapon_amount(a, 병기_창) + pk::get_max_weapon_amount(a, 병기_극) + pk::get_max_weapon_amount(a, 병기_노) + pk::get_max_weapon_amount(a, 병기_군마)) - (pk::get_weapon_amount(a, 병기_창) + pk::get_weapon_amount(a, 병기_극) + pk::get_weapon_amount(a, 병기_노) + pk::get_weapon_amount(a, 병기_군마)) 
						== (pk::get_max_weapon_amount(b, 병기_창) + pk::get_max_weapon_amount(b, 병기_극) + pk::get_max_weapon_amount(b, 병기_노) + pk::get_max_weapon_amount(b, 병기_군마)) - (pk::get_weapon_amount(b, 병기_창) + pk::get_weapon_amount(b, 병기_극) + pk::get_weapon_amount(b, 병기_노) + pk::get_weapon_amount(b, 병기_군마))
					     and build_dist_a == build_dist_b)                    
                    return (pos_dist_a < pos_dist_b);
                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
		}






        //----------------------------------------------------------------------------------
        //  공성 병기 포화 상태일때 다른 곳으로 배분 
        //----------------------------------------------------------------------------------




		/** 병력 있는 거점 찾기 */

		bool needEXSweapon(pk::building@ base)
		{

			if (!no_enemy_around(base)) return false;

			int base_troops = pk::get_troops(base);


                        int enemy_weight = countNeighborEnemyBase(base);
            pk::city@ city_a = pk::get_city(pk::get_city_id(base.pos));

	//  공성 병기 중 한 품목이라도 70 이상인 , 적 침공에서 안전한 병력 2천 이상 관문, 항구에서 보급 보내라

			if ( (70 <= pk::get_weapon_amount(base, 병기_충차) or 70 <= pk::get_weapon_amount(base, 병기_정란) or 70 <= pk::get_weapon_amount(base, 병기_투석) or 70 <= pk::get_weapon_amount(base, 병기_목수)) and 2000 <= pk::get_troops(base) and 건물_관문시작 <= base.get_id() and base.get_id() < 건물_항구끝 )
				return true;


	// 공성 병기 중 한 품목이라도 70 이상인, 적 침공에서 안전한 병력 4천 이상 도시에서 보급 보내라

			if ( (70 <= pk::get_weapon_amount(base, 병기_충차) or 70 <= pk::get_weapon_amount(base, 병기_정란) or 70 <= pk::get_weapon_amount(base, 병기_투석) or 70 <= pk::get_weapon_amount(base, 병기_목수)) and 4000 <= pk::get_troops(base) and 건물_도시시작 <= base.get_id() and base.get_id() < 건물_도시끝 )
				return true;


            
			return false;
		}







		/** 병기 10개 보급 명령 (나머지 15%)  */

		bool PushEXSweapon(pk::building@ base)
		{
            int reinforce_troops = pk::min(1000,  int (pk::get_troops(base) * 0.15f) );
			// 명령 가능한 무장이 있는지 확인.
			auto person_list = pk::get_idle_person_list(base);
			if (person_list.count == 0) return false;

			// 인접 거접이 있는지 확인.
			int target = getEXSWBase(base);
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
			cmd.gold = pk::min(int(pk::get_gold(base) * 0.15f), 10000);
			cmd.food = pk::min(pk::max (1000 , unit_food), 25000);
			cmd.troops = reinforce_troops;
			int i = 0;
			for (int weapon_id = 0; weapon_id < 병기_끝; weapon_id++)
			{
                int weapon_amount = 0;
                if (weapon_id < 병기_충차)
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id) * 0.05f), 5000);
                else if (병기_충차 <= weapon_id and weapon_id < 병기_주가)
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id)), 10);
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
            
                string target_name = pk::u8decode(pk::get_name(pk::get_building(target)));
	if (대사표시_설정) 
                pk::say(pk::u8encode(pk::format("여긴 공성병기 재고 초과다!\n\x1b[2x{}\x1b[0x(으)로 공성병기들을 보내자!", target_name)), leader);			
			
            
            // 임시 도주 효과 ('19.3.6)
            if (거점수송_일시도주설정)
            {
                leader.skill = retreat_skill;         // 특기 복원
            }
            
            
			return true;
		}





        
		/** 가장 가까운아군 도시에 보급을 보냄 */

        pk::building@ src_EXSW;
		int getEXSWBase(pk::building@ src)
		{
			int best_dst = -1;
			int best_distance = 0;
            int src_id = src.get_id();
            pk::list<pk::building@> dst_list; 
			dst_list.clear();			
            @src_EXSW = @src;



            
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
										

                        int enemy_weight = countNeighborEnemyBase(dst);
			pk::city@ city_c = pk::get_city(pk::get_city_id(dst.pos));

   if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst))
     {

	// 공성병기 각각 40개 이하로, 적 침공에서 안전한 도시로 보급 보내라
                    
if (건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and  (40 >= pk::get_weapon_amount(dst, 병기_충차) or 40 >= pk::get_weapon_amount(dst, 병기_정란) or 40 >= pk::get_weapon_amount(dst, 병기_투석) or 40 >= pk::get_weapon_amount(dst, 병기_목수)) and func_already (dst) <= 6  )
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
                    }



           // 공성병기 각각 40개 이하로, 적 침공에서 안전한 관문, 항구로 보급 보내라

else if (건물_관문시작 <= dst_id and dst_id < 건물_항구끝 and  (40 >= pk::get_weapon_amount(dst, 병기_충차) or 40 >= pk::get_weapon_amount(dst, 병기_정란) or 40 >= pk::get_weapon_amount(dst, 병기_투석) or 40 >= pk::get_weapon_amount(dst, 병기_목수)) and base2_troops <= pk::get_max_troops(dst) * 0.7 and func_already (dst) <= 6 and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id)
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
                    return (pk::get_weapon_amount(a, 병기_충차) + pk::get_weapon_amount(a, 병기_정란) + pk::get_weapon_amount(a, 병기_투석) + pk::get_weapon_amount(a, 병기_목수) < pk::get_weapon_amount(b, 병기_충차) + pk::get_weapon_amount(b, 병기_정란) + pk::get_weapon_amount(b, 병기_투석) + pk::get_weapon_amount(b, 병기_목수));
										
                    int build_dist_a = pk::get_building_distance(a.get_id(), main.src_EXSW.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.src_EXSW.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.src_EXSW.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.src_EXSW.pos);

                    if (pk::get_weapon_amount(a, 병기_충차) + pk::get_weapon_amount(a, 병기_정란) + pk::get_weapon_amount(a, 병기_투석) + pk::get_weapon_amount(a, 병기_목수) == pk::get_weapon_amount(b, 병기_충차) + pk::get_weapon_amount(b, 병기_정란) + pk::get_weapon_amount(b, 병기_투석) + pk::get_weapon_amount(b, 병기_목수)
					    and build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);

                    if (pk::get_weapon_amount(a, 병기_충차) + pk::get_weapon_amount(a, 병기_정란) + pk::get_weapon_amount(a, 병기_투석) + pk::get_weapon_amount(a, 병기_목수) == pk::get_weapon_amount(b, 병기_충차) + pk::get_weapon_amount(b, 병기_정란) + pk::get_weapon_amount(b, 병기_투석) + pk::get_weapon_amount(b, 병기_목수)
					    and build_dist_a == build_dist_b)                     
                    return (pos_dist_a < pos_dist_b);
                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
		}





        //----------------------------------------------------------------------------------
        //  수상 병기 포화 상태일때 다른 곳으로 배분 
        //----------------------------------------------------------------------------------




		/** 병력 있는 거점 찾기 */

		bool needEXWweapon(pk::building@ base)
		{
			if (!no_enemy_around(base)) return false;

			int base_troops = pk::get_troops(base);


                        int enemy_weight = countNeighborEnemyBase(base);
            pk::city@ city_a = pk::get_city(pk::get_city_id(base.pos));

	//  수상 병기 중 한 품목이라도 70 이상인 , 적 침공에서 안전한 벙력 2천 이상 관문, 항구에서 보급 보내라

			if ( (70 <= pk::get_weapon_amount(base, 병기_누선) or 70 <= pk::get_weapon_amount(base, 병기_투함) ) and 2000 <= pk::get_troops(base) and 건물_관문시작 <= base.get_id() and base.get_id() < 건물_항구끝 )
				return true;


	// 수상 병기 중 한 품목이라도 70 이상인, 적 침공에서 안전한 병력 4천 이상 도시에서 보급 보내라

			if ( (70 <= pk::get_weapon_amount(base, 병기_누선) or 70 <= pk::get_weapon_amount(base, 병기_투함) ) and 4000 <= pk::get_troops(base) and 건물_도시시작 <= base.get_id() and base.get_id() < 건물_도시끝 )
				return true;


            
			return false;
		}







		/** 병기 10개 보급 명령 (나머지 15%)  */

		bool PushEXWweapon(pk::building@ base)
		{
            int reinforce_troops = pk::min(1000,  int (pk::get_troops(base) * 0.15f) );
			// 명령 가능한 무장이 있는지 확인.
			auto person_list = pk::get_idle_person_list(base);
			if (person_list.count == 0) return false;

			// 인접 거접이 있는지 확인.
			int target = getEXWWBase(base);
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
			cmd.gold = pk::min(int(pk::get_gold(base) * 0.15f), 10000);
			cmd.food = pk::min(pk::max (1000 , unit_food), 25000);
			cmd.troops = reinforce_troops;
			int i = 0;
			for (int weapon_id = 0; weapon_id < 병기_끝; weapon_id++)
			{
                int weapon_amount = 0;
                if (weapon_id < 병기_주가)
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id) * 0.05f), 5000);
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

                string target_name = pk::u8decode(pk::get_name(pk::get_building(target)));
	if (대사표시_설정) 
                pk::say(pk::u8encode(pk::format("여긴 함선 재고 초과다!\n\x1b[2x{}\x1b[0x(으)로 배들을 보내자!", target_name)), leader);

            
            // 임시 도주 효과 ('19.3.6)
            if (거점수송_일시도주설정)
            {
                leader.skill = retreat_skill;         // 특기 복원
            }
            
            
			return true;
		}





        
		/** 가장 가까운아군 도시에 보급을 보냄 */

        pk::building@ src_EXWW;
		int getEXWWBase(pk::building@ src)
		{
			int best_dst = -1;
			int best_distance = 0;
            int src_id = src.get_id();
            pk::list<pk::building@> dst_list; 
			dst_list.clear();			
            @src_EXWW = @src;



            
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
				

                        int enemy_weight = countNeighborEnemyBase(dst);
			pk::city@ city_c = pk::get_city(pk::get_city_id(dst.pos));


if (src_id != dst_id and src.get_force_id() == dst.get_force_id() and pk::is_alive(src) and pk::is_alive(dst))
      {

           // 수상병기 각각 40개 이하로, 적 침공에서 안전한 관문, 항구로 보급 보내라

if (건물_관문시작 <= dst_id and dst_id < 건물_항구끝 and  (40 >= pk::get_weapon_amount(dst, 병기_누선) or 40 >= pk::get_weapon_amount(dst, 병기_투함) ) and base2_troops <= pk::get_max_troops(dst) * 0.7 and func_already (dst) <= 6 and 건물_파양항 != dst_id and 건물_노릉항 != dst_id and 건물_서하항 != dst_id and 건물_하양항 != dst_id and 건물_해현항 != dst_id and 건물_강도항 != dst_id)
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 가능 거점리스트 추가
                    }




	// 수상병기 각각 40개 이하로, 적 침공에서 안전한 도시로 보급 보내라
                    
else if (건물_도시시작 <= dst_id and dst_id < 건물_도시끝 and  (40 >= pk::get_weapon_amount(dst, 병기_누선) or 40 >= pk::get_weapon_amount(dst, 병기_투함) ) and func_already (dst) <= 6  )
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
                    return (pk::get_weapon_amount(a, 병기_누선) + pk::get_weapon_amount(a, 병기_투함) < pk::get_weapon_amount(b, 병기_누선) + pk::get_weapon_amount(b, 병기_투함));
																		
                    int build_dist_a = pk::get_building_distance(a.get_id(), main.src_EXWW.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.src_EXWW.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.src_EXWW.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.src_EXWW.pos);

                    if (pk::get_weapon_amount(a, 병기_누선) + pk::get_weapon_amount(a, 병기_투함) == pk::get_weapon_amount(b, 병기_누선) + pk::get_weapon_amount(b, 병기_투함) 
						and build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);

                    if (pk::get_weapon_amount(a, 병기_누선) + pk::get_weapon_amount(a, 병기_투함) == pk::get_weapon_amount(b, 병기_누선) + pk::get_weapon_amount(b, 병기_투함) 
						and build_dist_a == build_dist_b)                    
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
            
            weight = int(troops);
            return weight;
        }



         //  거리에 따른 인근 적대 도시 숫자 체크. masterpiecek님의 AI_도시물자수송.cpp﻿를 참조했습니다.
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



         // 이미 해당거점으로 출진한 부대 숫자 체크. masterpiecek님의 AI_도시물자수송.cpp﻿를 참조했습니다.

	 int func_already(pk::building@ building)
		{
			int already = 0;
			for (int unit_id = 0; unit_id < 부대_끝; unit_id++)
			{
				pk::unit@ unit = pk::get_unit(unit_id);
			if (building.get_force_id() == -1) continue;
			if (unit.get_force_id() == -1) continue;

		if ( pk::is_alive(unit) and unit.type == 부대종류_수송 and unit.get_force_id() == building.get_force_id() and unit.target == building.get_id() and unit.troops <= 2800 and (5000 <= unit.gold or 10000 <= unit.food) ) 

				already++;
			}

			return already;
		}




        // ***** 거리 1 간 수송시 중간의 적 거점 확인 ***** //
        bool intercept1_Enemy_base(pk::building@ src, pk::building@ dst)
        {
		    int distance = pk::get_distance(src.get_pos(), dst.get_pos());
	        if (distance <= 10)	return false;
				
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
		    int distance = pk::get_distance(src.get_pos(), dst.get_pos());
	        if (distance <= 10)	return false;
				
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



        // ***** 허창, 완, 북평 3각지대 간 수송시 중간의 적 거점 확인 ***** //
        bool intercept_delta_Enemy_base(pk::building@ src, pk::building@ dst)
        {
            for (int i = 0; i < 건물_거점끝; i++)
			{
                pk::building@ intercept = pk::get_building(i);
                int src_id = src.get_id();
                int dst_id = dst.get_id();
                int intercept_id = intercept.get_id();
                
				// 허창 3각지대
                if (src_id != dst_id and src_id != intercept_id and dst_id != intercept_id and pk::is_enemy(src, intercept) and pk::is_enemy(dst, intercept) and
                   (((src_id == 건물_진류 or src_id == 건물_허창 or src_id == 건물_완 or src_id == 건물_낙양) and
                   (dst_id == 건물_진류 or dst_id == 건물_허창 or dst_id == 건물_완 or dst_id == 건물_낙양) and
                   (intercept_id == 건물_진류 or intercept_id == 건물_허창 or intercept_id == 건물_완 or intercept_id == 건물_호로관 or intercept_id == 건물_관도항)) or
				   
                   ((src_id == 건물_진류 or src_id == 건물_허창 or src_id == 건물_완 or src_id == 건물_호로관) and
                   (dst_id == 건물_진류 or dst_id == 건물_허창 or dst_id == 건물_완 or dst_id == 건물_호로관) and
                   (intercept_id == 건물_진류 or intercept_id == 건물_허창 or intercept_id == 건물_완 or intercept_id == 건물_호로관 or intercept_id == 건물_관도항)) or
				   
                   (src_id == 건물_관도항 and
                   (dst_id == 건물_허창 or dst_id == 건물_완 or dst_id == 건물_낙양) and
                   (intercept_id == 건물_진류 or intercept_id == 건물_허창 or intercept_id == 건물_완 or intercept_id == 건물_호로관)) or		

                   ((src_id == 건물_허창 or src_id == 건물_완 or src_id == 건물_낙양) and
                   dst_id == 건물_관도항 and
                   (intercept_id == 건물_진류 or intercept_id == 건물_허창 or intercept_id == 건물_완 or intercept_id == 건물_호로관)) or		

                   (src_id == 건물_관도항 and
                   (dst_id == 건물_허창 or dst_id == 건물_완 or dst_id == 건물_호로관) and
                   (intercept_id == 건물_진류 or intercept_id == 건물_허창 or intercept_id == 건물_완 or intercept_id == 건물_호로관)) or

                   ((src_id == 건물_허창 or src_id == 건물_완 or src_id == 건물_호로관) and
                   dst_id == 건물_관도항 and
                   (intercept_id == 건물_진류 or intercept_id == 건물_허창 or intercept_id == 건물_완 or intercept_id == 건물_호로관)) ) )
	               return true;


				// 북평 3각지대
                if (src_id != dst_id and src_id != intercept_id and dst_id != intercept_id and pk::is_enemy(src, intercept) and pk::is_enemy(dst, intercept) and
                   (src_id == 건물_북평 or src_id == 건물_계 or src_id == 건물_남피) and
                   (dst_id == 건물_북평 or dst_id == 건물_계 or dst_id == 건물_남피) and
                   (intercept_id == 건물_북평 or intercept_id == 건물_계 or intercept_id == 건물_남피))				   
	               return true;
				   
				   
				// 완 3각지대
                if (src_id != dst_id and src_id != intercept_id and dst_id != intercept_id and pk::is_enemy(src, intercept) and pk::is_enemy(dst, intercept) and
                   (src_id == 건물_상용 or src_id == 건물_무관) and
                   (dst_id == 건물_상용 or dst_id == 건물_무관) and
                   intercept_id == 건물_완)				   
	               return true;			

                if (src_id != dst_id and src_id != intercept_id and dst_id != intercept_id and pk::is_enemy(src, intercept) and pk::is_enemy(dst, intercept) and
                   (src_id == 건물_방릉항 or src_id == 건물_무관) and
                   (dst_id == 건물_방릉항 or dst_id == 건물_무관) and
                   intercept_id == 건물_완)				   
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
        //---------------------------------------------------------------------------------------

        // ***** 두 거점 사이에 적 부대가 있는지 ***** //
        bool enemy_inside(pk::building@ base, pk::building@ dst)
        {
             pk::array<pk::point> range = pk::range(base.pos, 1, 5);  // 거점 주변 검색
             for (int i = 0; i < int(range.length); i++)
             {
				auto unit_f = pk::get_unit(range[i]);
				if (pk::is_alive(unit_f) and base.get_force_id() == unit_f.get_force_id())  // 아군 부대 찾음
				{	
			        auto paths_base_dst = pk::get_path(unit_f, base.pos, dst.pos);  // 아군 부대의 base-dst 사이 이동 경로

                    pk::array<pk::point> range_e = pk::range(base.pos, 1, 14);  // 거점 주변 검색            
				    for (int e = 0; e < int(range_e.length); e++)
				    {
				        auto unit_e = pk::get_unit(range_e[e]);

				      if (pk::is_alive(unit_e) and pk::is_enemy(unit_e, base) and pk::is_enemy(unit_e, unit_f))  // 거점 주변에 적부대가 있다면
					  {	
				            pk::array<pk::point> arr_range = pk::get_movable_pos(unit_e);  // 적 부대가 이동 가능한 범위
				            for (int j = 0; j < int(arr_range.length); j++)
				            {
				                pk::point pos_e = arr_range[j];	  // 적 부대 이동 가능 지점들

		            		    for (int f = 0; f < int(paths_base_dst.length); f++)
		            		    {
		            		       pk::point pos_f = paths_base_dst[f];     // 아군 부대의 이동 경로 지점들

			                          if (pos_f == pos_e)	  // 아군 부대 이동 동선과 적부대의 이동 가능 동선이 겹치면 인정
			                           {
			                           return true;
			                           }

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