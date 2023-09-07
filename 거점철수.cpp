/*
수정 by 일송정

이 스크립트는 PK2.1 기본 제공 스크립트 중 하나이며, 기마책사님이 별도로 수정하신 스크립트입니다.
여기에 제가 추가로 자잘하게 몇가지 수정을 했는데요.
거점 내 잔여병력이 일정 수준 이하면서 더 긴박한 순간에 철수를 하도록 추가 설정을 하였습니다.

[수정 내용]
1. 거점을 철수 하는 조건 중 '잔여 병력이 아슬아슬한 경우'에 거점 병력 2200 미만일 경우에 철수 하도록 조건 추가 
2. '잔여 병력이 아슬아슬한 경우2' 항목 추가
3. '잔여 내구가 아슬아슬한 경우 2 ' 항목 추가

*/



/*
pk2.1 기본제공되는 거점철수 기능에서 수정

@수정자: 기마책사
@Update: '19.3.5     / 변경내용 : 거점철수 세팅값 조정, 기존 거점원군 기능은 별도 스크립트로 분리, 원거리이동/임시도주설정 기능 추가
@Update: '19.3.9     / 변경내용 : 거점철수 조건 세팅값 조정, 거점검색모드 추가
@Update: '19.4.5     / 변경내용 : 마지막 도시인 경우 철수불가

*/


namespace 거점철수
{
    
    //---------------------------------------------------------------------------------------
    // 유저 설정
    
    const bool  거점철수_원거리이동  = true;     // 철수부대 이동 1회 추가 (추천기능 : 보너스이동으로 탈출)
    const bool  거점철수_일시도주설정 = true;     // 철수부대 출진순간 도주효과 일시적용 (추천기능 : 포위망 돌파가능)
    
    const float 거점철수_물자회수율 = 0.50f;    // 철수 시 금/병량 회수율 (0.0f ~ 1.0f 사이)
    const float 거점철수_병기회수율 = 0.95f;    // 철수 시 병기 회수율   (0.0f ~ 1.0f 사이)
    
    const int   거점철수_거점검색모드 = 1;       // 0: 도시만 검색하여 철수,  1: 도시+관문+항구 모두 검색하여 철수
    
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

            if (!pk::is_campaign())
            {                
                // 플레이어, 이민족 세력은 제외.
                if (!force.is_player() and pk::is_normal_force(force_id))
                {
                    for (int i = 0; i < 건물_거점끝; i++)
                    {
                        auto base = pk::get_building(i);
                        
                        if (base.get_force_id() == force_id and needRetreat(base))
                            PushRetreat(base);
                              
                    }
                }
            }
            
			// 이전 핸들러가 있다면 체인.
			if (prev_callback_ !is null)
				return prev_callback_(force);
			return false;
		}
        
        
        
        //----------------------------------------------------------------------------------
        //          거점 철수 
        //----------------------------------------------------------------------------------
        
		/** 철수가 필요한 거점인지 판단(조건문이 매우 허술한 상태입니다. 입맛에 맞게 수정해서 사용해 보세요.) */
		bool needRetreat(pk::building@ base)
		{
			// 근접한 적 부대 수
			int enemy_units1 = 0;
			// 3칸 이내 적 부대 수
			int enemy_units3 = 0;
			// 3칸 이내 적 병력 수
			int enemy_troops3 = 0;

			auto range = pk::range(base.get_pos(), 1, 4 + (base.facility == 시설_도시 ? 1 : 0));
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
						}
						if (distance <= 3)
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

			if (enemy_units1 >= 10)  // 거점 포위 상태로 철수 불가
				return false;
			int base_troops = pk::get_troops(base);
			int base_hp = base.hp;
			// 잔여 내구가 아슬아슬한 경우
			if (enemy_units3 > 0 and base_troops < enemy_troops3 * 0.8f and base_hp < pk::max(500, int(pk::get_max_hp(base) * 0.3f)) )
				return true;

			// 잔여 내구가 아슬아슬한 경우 2 (2020.08.31. 일송정 추가)
			if (enemy_units3 > 0 and enemy_troops3 >= 4000 and base_hp <= 700 )
				return true;


			// 잔여 병력이 아슬아슬한 경우  
			// 2200명 이하 미만 추가 ,일송정 수정 2021.01.15
			
			if (enemy_units3 > 0 and base_troops < pk::max(1, int(enemy_troops3 * 0.1f)) and base_troops < 2200 )
				return true;

			// 잔여 병력이 아슬아슬한 경우2,일송정 수정 2021.01.15 
			if (enemy_units3 > 0 and int(base_troops * 3.8f) < enemy_troops3 and base_troops < 1500 )
				return true;

            
			return false;
		}


		/** 철수 명령 */
		bool PushRetreat(pk::building@ base)
		{
			// 명령 가능한 무장이 있는지 확인.
			auto person_list = pk::get_idle_person_list(base);
			if (person_list.count == 0) return false;

			// 철수할 인접 거접이 있는지 확인.
			int target = getNearestBase(base);
			if (target == -1) return false;

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

			// 정치력 높은 순으로 정렬.
			actors.sort(function(a, b)
			{
				return (a.stat[무장능력_정치] / a.stat[무장능력_무력]) > (b.stat[무장능력_정치] / b.stat[무장능력_무력]);
			});
            pk::person@ leader = pk::get_person(actors[0].get_id());
            
            // 임시 도주 효과 ('19.3.6)
            if (거점철수_일시도주설정)
            {
                retreat_skill = leader.skill;   // 특기 백업
                leader.skill = 특기_도주;         // 도주 특기 부여
            }
            

            float supply_rate = pk::min(1.0f, pk::max(0.0f, 거점철수_물자회수율));
            float weapon_rate = pk::min(1.0f, pk::max(0.0f, 거점철수_병기회수율));
            
			// 출진 명령 정보 생성.
			pk::com_deploy_cmd_info cmd;
			@cmd.base = @base;
			cmd.type = 부대종류_수송;
			cmd.member[0] = leader.get_id();
			cmd.gold = pk::min(int(pk::get_gold(base) * supply_rate), 100000);
			cmd.food = pk::min(int(pk::get_food(base) * supply_rate), 500000);
			cmd.troops = pk::min(int(pk::max(1.f, pk::get_troops(base) * 0.60f)), 60000);
			int i = 0;
			for (int weapon_id = 0; weapon_id < 병기_끝; weapon_id++)
			{
                int weapon_amount = 0;
                if (weapon_id < 병기_충차)
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id) * weapon_rate), 100000);
                else
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id)), 100);
                
				if (weapon_amount > 0)
				{
					cmd.weapon_id[i] = weapon_id;
					cmd.weapon_amount[i] = weapon_amount;
					i++;
				}
			}
			cmd.order = 부대임무_이동;
			cmd.target_pos = pk::get_building(target).get_pos();

			// 출진.
			int unit_id = pk::command(cmd);
            pk::unit@ unit_cmd = pk::get_unit(unit_id);
			if (pk::is_alive(unit_cmd))
				unit_cmd.action_done = (!거점철수_원거리이동);  // 기본값 true 에서 false 로 변경하여 2회 이동하도록 함 ('19.3.5)
            
            
            pk::say(pk::encode("어서 적진을 돌파하여 철수하라"), leader);
            
            // 임시 도주 효과 ('19.3.6)
            if (거점철수_일시도주설정)
            {
                leader.skill = retreat_skill;         // 특기 복원
            }
            
            
			return true;
		}
        
		/** 가장 가까운 아군 거점을 얻음. */
        pk::building@ src_t;
		int getNearestBase(pk::building@ src)
		{
			int best_dst = -1;
			int best_distance = 0;
            int src_id = src.get_id();
            pk::list<pk::building@> dst_list; 
            @src_t = @src;
            
            int search_base = 건물_도시끝;
            if      (거점철수_거점검색모드 == 0) search_base = 건물_도시끝;
            else if (거점철수_거점검색모드 == 1) search_base = 건물_거점끝;
            
            pk::force@ force = pk::get_force(src.get_force_id());
            
			// 철수 거점 검색
            if (pk::get_city_list(force).count <= 1 and src_id < 건물_도시끝)
                return -1;      // 마지막 도시인 경우 철수 불가
            else
            {
                for (int i = 0; i < search_base; i++)
                {
                    pk::building@ dst = pk::get_building(i);
                    int dst_id = dst.get_id();
                    
                    if (src_id != dst_id and src.get_force_id() == dst.get_force_id())
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // 철수가능 거점리스트 추가
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
                    int build_dist_a = pk::get_building_distance(a.get_id(), main.src_t.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.src_t.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.src_t.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.src_t.pos);
                    
                    if (build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);
                    
                    return (pos_dist_a < pos_dist_b);
                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
		}
        
        
	};

	Main main;
}