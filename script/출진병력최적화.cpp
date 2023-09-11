/*     
// 만든이: 기마책사
// Update: '19.2.17  / 최초적용: 출진부대의 병력수 제한 테스트, 교전여부 판단
// Update: '19.2.27  / 변경적용: 거점구역에서 도시구역으로 병력합산 변경, 주도권 위임 트리거 추가, 최소 요격병력 제한값만 임시적용
// Update: '19.3.3   / 변경적용: 원정부대 제한조건 추가 (계략부대, 공성부대)
// Update: '20.8.26  / 변경적용: 캠페인에서는 스크립트 동작하지 않도록 수정
// Update: '20.9.14  / 변경적용: 부대임무 및 출진목표 확인 조건 추가
// Update: '20.9.20  / 변경적용: 요격출진 시 거점최소방어 병력 고려하도록 수정
*/

namespace 출진병력최적화
{
	
    //---------------------------------------------------------------------------------------
    // 유저 설정
    const int  출진병력최적화_세력조건 = 0;     // 0: 컴퓨터AI 와 플레이어_위임군단 모두,  1: 플레이어_위임군단만, 2: 컴퓨터AI만,  3: 모두 미적용
    const bool 출진병력최적화_유저군단적용 = false;   // 세력조건과 별개로 적용여부 설정, 유저의 부대편성 무시되므로 false 권장
    const bool 출진병력제한_대화표시 = false;       // 출진 시 병력 조절 결과 메시지 표시
    
    //---------------------------------------------------------------------------------------
    
    // 요격병력제한 옵션설정
    const bool 요격병력제한_제한적용 = true;      // 요격부대의 병력 제한설정 (false=미적용 : 기타 옵션 무시)
    
    const bool 요격병력제한_최소제한적용 = true;   // 요격부대의 최소병력 제한설정
    const int  요격병력제한_최소제한병력 = 1000;   // 요격부대의 최소병력 기준 (게임 기본값 = 5000)
    const bool 요격병력제한_최대제한적용 = true;   // 요격부대의 최대병력 제한설정
    const int  요격병력제한_최대제한병력 = 12000;  // 요격부대의 최대병력 기준
    const bool 요격병력제한_능력가중치적용 = true;  // 요격부대의 최대병력 제한 시 공격/방어 평균 능력에 따른 가중치 적용 (약체부대 병력 제한)
    const int  요격병력제한_거점잔여병력 = 5000;   // 요격부대의 출진 시 소속거점의 최소잔여병력
	
    // 건설편제 제한 : 요격/원정 모두 적용
    const bool 건설편제_제외설정 = true;      // 건설편제 조건 만족 시 AI부대 무장변경 안함 (특기_축성 보유 또는 금/병력 기준 판단)
    const int 건설편제_기준소지금 = 1500;     // 기준 소지금 이상 & 기준 병력 이하일 경우 건설부대로 취급하여 무장변경 안함
    const int 건설편제_기준병력  = 3000;     // 기준 소지금 이상 & 기준 병력 이하일 경우 건설부대로 취급하여 무장변경 안함
    
    //---------------------------------------------------------------------------------------
    
    // 원정병력제한 옵션설정
    const bool 원정병력제한_제한적용 = true;     // 원정부대의 병력 제한설정 (false=미적용, 기타 옵션 무시)
    const int  원정병력제한_거점잔여병력 = 5000;   // 요격부대의 출진 시 소속거점의 최소잔여병력
    
    // 공성부대 제한 : 원정 부대에만 적용
    const bool  공성부대_제한설정  = true;  // true=제한적용, false=미적용
    const int  공성부대_제한기준병력 = 5000;   // 공성부대의 기준병력 기준
    const int  공성부대_적성고려단위 = 1500;   // 부대적성에 따라 기준병력 대비 추가할 등급당 병력단위 (적성C 추가없음, 적성S 단위의 3배 추가) 
    
    // 계략부대 제한 : 원정 부대에만 적용
    const bool  계략부대_제한설정  = true;  // true=제한적용, false=미적용
    const bool  계략부대_적성고려 = true;   // 부대 적성이 S이상인 경우 전투부대로 취급 (모든 특기 무시)    
    // 신/장 계열 특기는 무조건 전투부대 취급 (계략게열 특기 보유여부 무시)
    // 신산,허실,백출,귀모,연환은 무조건 계략부대 우대 (지력공방비 무시)
    const bool  계략부대_특기우대 = true;     // 계략게열 특기 보유한 부대 우대 (지력공방비 무시)
    const float 계략부대_지력공방비 = 1.5f;    // 부대지력이 부대공방평균 대비 기준 이상이면 계략부대로 취급
    const int  계략부대_최대제한병력 = 5000;   // 계략부대의 최대병력 기준
    
    //---------------------------------------------------------------------------------------
    
    
	class Main
	{
		
		Main()
		{
            pk::bind(102, pk::trigger102_t(onGameInit));
            pk::bind(132, pk::trigger132_t(onForceLeaveControl));
            pk::bind(111, pk::trigger111_t(onTurnStart));
            
			pk::bind(170, 출진병력최적화_트리거_우선순위, pk::trigger170_t(onUnitCreate));
            pk::bind(172, 출진병력최적화_트리거_우선순위, pk::trigger172_t(onUnitPosChange));
		}
		
        
        int 출진병력최적화_트리거_우선순위 = 99; // 값이 높을수록 먼저 실행 (출진부대최적화.cpp 크고 출진무장최적화.cpp 보다 낮게 설정 필요)
        
        array<int> def_troopsbase(건물_도시끝, 0);   // 구역 내 거점벙력
        array<int> def_troops_sum(건물_도시끝, 0);   // 구역 내 수비군 벙력합
        array<int> def_unit_count(건물_도시끝, 0);   // 구역 내 수비군 부대수
        array<int> atk_troops_sum(건물_도시끝, 0);   // 구역 내 공격군 벙력합
        array<int> atk_unit_count(건물_도시끝, 0);   // 구역 내 공격군 부대수
        
        bool limit_defence = false;
        bool limit_attack = false;
        pk::list<pk::unit@> limit_def_unit_list;
        pk::list<pk::unit@> limit_atk_unit_list;
        
        //---------------------------------------------------------------------------------------

        void onGameInit()
        {
            if (pk::is_campaign()) return;
            
            pk::force@ force = pk::get_force(pk::get_current_turn_force_id());
            onTurnStart(force);
        }
        
        void onForceLeaveControl(pk::force@ force)
		{
            if (pk::is_campaign()) return;
            
            // 턴 세력 거점 구역별 : 교전하는 병력합, 부대수 업데이트
            clear_engage_info();
            update_engage_info();
        }
            
        void onTurnStart(pk::force@ force)
        {
            if (pk::is_campaign()) return;
            
            // 턴 세력 거점 구역별 : 교전하는 병력합, 부대수 업데이트
            clear_engage_info();
            update_engage_info();
        }
        
        // 부대 생성 시 병력제한 대상여부 판단
		void onUnitCreate(pk::unit@ unit, int type) 
		{
            if (pk::is_campaign()) return;
            
            // 변수 초기화
            limit_defence = false;
            limit_attack = false;
            limit_def_unit_list.clear();
            limit_atk_unit_list.clear();
            
            // 정상적인 출진부대인지 확인
            if (!check_valid_unit(unit, type)) return ;
            // 출진무장 최적화할 세력 확인
            if (!check_force_option(unit)) return ;
            // AI건설편제인 경우 
            if (건설편제_제외설정 and check_construction_unit(unit)) return ;
            // 출진부대 소속거점
            pk::building@ base = pk::get_building(pk::get_service(unit));
            if (!pk::is_alive(base)) return;
            // 소속거점이 구역의 도시와 동일세력이 아니면 제외
            if (base.get_force_id() != pk::get_city(pk::get_city_id(base.pos)).get_force_id()) return;
            
            // 적부대 침략확인
            bool is_invaded = check_enemy_invasion(base);
            if (is_invaded and 요격병력제한_제한적용)
            {
                limit_defence = true;
                limit_def_unit_list.add(unit);
            }
            else if (!is_invaded and 원정병력제한_제한적용)
            {
                limit_attack = true;
                limit_atk_unit_list.add(unit);
            }
		}
        
        // 부대 출진이동 후 초과병력 반환
        void onUnitPosChange(pk::unit@ unit, const pk::point &in pos)
        {
            if (pk::is_campaign()) return;
            
            if (디버그모드)
            {
                string unit_name  = pk::decode(pk::get_name(pk::get_person(unit.leader)));
                string target_info;
                if (unit.target_type == 부대임무대상_거점) target_info = pk::decode(pk::get_name(pk::get_building(unit.target)));
                if (unit.target_type == 부대임무대상_부대) target_info = pk::decode(pk::get_name(pk::get_person(pk::get_unit(unit.target).leader)));
                pk::info(pk::format("{}대 {}: {}", unit_name, get_order_info(unit.order), target_info));
            }
            
            // 요격 부대 제한
            if (요격병력제한_제한적용 and limit_defence and limit_def_unit_list.contains(unit))
            {
                limit_defence = false;
                limit_def_unit_list.clear();
                
                pk::building@ base = pk::get_building(pk::get_service(unit));
                if (!pk::is_alive(base)) return;
                
                // 부대임무목표 확인 ('20.9.14, 추가)
                if (unit.order == 부대임무_정복) return;
                // 타세력 거점 공략 제외, 자세력 타거점 방어지원 제외
                if (unit.target_type == 부대임무대상_거점)
                {
                    pk::building@ dst_base = pk::get_building(unit.target);
                    if (pk::is_alive(dst_base))
                    {   
                        if (dst_base.get_force_id() != base.get_force_id()) return;
                        if (dst_base.get_force_id() == base.get_force_id() and dst_base.get_id() != base.get_id()) return;
                    }
                }                
                // 병력제한값 계산 함수
                int limit_value = get_defence_limit(base, unit);
                // 출진병력제한 함수 : 초과병력 거점으로 반환
                return_over_troops(base, unit, limit_value);
                
            }
            // 원정 부대 제한
            if (원정병력제한_제한적용 and limit_attack and limit_atk_unit_list.contains(unit))
            {
                limit_attack = false;
                limit_atk_unit_list.clear();
                
                pk::building@ base = pk::get_building(pk::get_service(unit));
                if (!pk::is_alive(base)) return;
                
                // 부대임무목표 확인 ('20.9.14, 추가)
                if (unit.order == 부대임무_물림) return;
                // 자세력 타거점 방어지원 제외
                if (unit.target_type == 부대임무대상_거점)
                {
                    pk::building@ dst_base = pk::get_building(unit.target);
                    if (pk::is_alive(dst_base))
                    {   
                        if (dst_base.get_force_id() == base.get_force_id() and dst_base.get_id() != base.get_id()) return;
                    }
                }
                
                // 병력제한값 계산 함수
                int limit_value = get_attack_limit(base, unit);
                // 출진병력제한 함수 : 초과병력 거점으로 반환
                return_over_troops(base, unit, limit_value);
                
            }
        }
        
        
        //---------------------------------------------------------------------------------------
        // 거점별 병력 현황 업데이트
        //---------------------------------------------------------------------------------------
        
        // 턴 세력 거점 구역별 : 병력정보 초기화
        void clear_engage_info()
        {
            for (int city_id = 0; city_id < 건물_도시끝; city_id++)
            {
                def_troopsbase[city_id] = 0;
                def_troops_sum[city_id] = 0;
                def_unit_count[city_id] = 0;
                atk_troops_sum[city_id] = 0;
                atk_unit_count[city_id] = 0;
            }
        }
        
        // 턴 세력 거점 구역별 : 교전하는 병력합, 부대수 업데이트
        void update_engage_info()
        {
            pk::array<pk::unit@> arr_unit = pk::list_to_array(pk::get_unit_list());
            for (int i = 0; i < int(arr_unit.length); i++)
            {
                pk::unit@ unit = arr_unit[i];
                int unit_id = unit.get_id();
                int city_id = pk::get_city_id(unit.pos);    // 부대가 위치한 좌표 구역의 거점
                if (city_id >= 0 and city_id <= 건물_도시끝)
                {
                    pk::city@ city = pk::get_city(city_id);
                    if (unit.get_force_id() == city.get_force_id()) // 부대와 거점이 동일 세력
                    {
                        def_troops_sum[city_id] += unit.troops; // 구역 수비병력합
                        def_unit_count[city_id] += 1;           // 구역 수비부대수
                    }
                    else if (pk::is_enemy(unit, city))          // 부대와 거점이 적대세력
                    {
                        atk_troops_sum[city_id] += unit.troops; // 구역 공격병력합
                        atk_unit_count[city_id] += 1;           // 구역 공격부대수
                    }
                }
            }
            for (int city_id = 0; city_id < 건물_도시끝; city_id++)
            {
                pk::city@ city = pk::get_city(city_id);
                def_troopsbase[city_id] = pk::get_troops(city);
            }
        }
        
        
        //---------------------------------------------------------------------------------------
        // 출진 병력 제한
        //---------------------------------------------------------------------------------------
        
        // 출진병력제한 함수 : 병력제한 기준에 따라 초과분 소속거점으로 병력/병장기/병량 반환
		void return_over_troops(pk::building@ base, pk::unit@ unit, int limit) 
		{
            if (limit <= 0) return;
			if (!pk::is_alive(base) or !pk::is_alive(unit)) return;
            
            int troops = unit.troops;
            if (troops > limit)
            {
                // 병력 반환
                int return_amount = troops - limit;
                pk::add_troops(unit, -return_amount, false);    // 부대 병력 조정
                pk::add_troops(base, +return_amount, false);    // 거점 병력 반환
                
                // 병장기 반환
                int weapon_id = pk::get_ground_weapon_id(unit);
                if (병기_창 <= weapon_id and weapon_id <= 병기_군마)
                    pk::add_weapon_amount(base, weapon_id, return_amount, false);   // 거점 병기 반환
                
                // 병량 반환
                int food_amount = int(float(unit.food) * float(return_amount) / float(troops));
                pk::add_food(unit, -food_amount, false);        // 부대 병량 조정
                pk::add_food(base, +food_amount, false);        // 거점 병량 조정
                
                pk::person@ leader = pk::get_person(unit.leader);
                if (출진병력제한_대화표시)
                {
                    string weapon_name = get_weapon_name(weapon_id);
                    string base_name = pk::decode(pk::get_name(base));
                    pk::say(pk::encode(pk::format("출진병력제한으로 \x1b[17x{} \x1b[1x{}명\x1b[0x을 \n\x1b[2x{}\x1b[0x(으)로 반환하겠습니다", weapon_name, return_amount, base_name)), leader);
                }
                if (디버그모드)
                {
                    string name = pk::decode(pk::get_name(leader));
                    pk::info(pk::format("{}대 기존병력={} 제한={} 반환={} 최종={}", name, troops, limit, return_amount, unit.troops));
                }
                
            }
            
		}
        
        
        //---------------------------------------------------------------------------------------
        //   요격 부대 제한
        //---------------------------------------------------------------------------------------
        
        // 병력제한값 계산 함수 ('19.2.27)
        int get_defence_limit(pk::building@ base, pk::unit@ unit)
        {
            int city_id = pk::get_city_id(base.pos);
            
            // 방어군 거점+부대병력 총합
            int def_troops  = def_troopsbase[city_id] + def_troops_sum[city_id];
            
            // 출진최소병력 (제한기준값 vs.공격병력합 최소값)
            int min_limit; 
            if (요격병력제한_최소제한적용)
                min_limit = pk::max(1, 요격병력제한_최소제한병력, atk_troops_sum[city_id]);
            else 
                min_limit = unit.troops;
            
            // 평균 공격병력
            int atk_troops_avg; 
            if (atk_unit_count[city_id] == 0)
                atk_troops_avg = 1;
            else 
                atk_troops_avg = int(atk_troops_sum[city_id] / atk_unit_count[city_id]);
            
            // 출진최대병력 계산
            int max_limit; 
            if (요격병력제한_최대제한적용)
                max_limit = pk::max(3000, pk::min(요격병력제한_최대제한병력, int(get_defence_weight(unit) * atk_troops_avg)));
            else 
                max_limit = unit.troops;
            
            // 거점잔여병력 계산 ('20.9.20)
            int base_limit = get_base_limit(base, unit, 요격병력제한_거점잔여병력);
            
            // 최대병력 가중치 적용
            int limit = pk::min(min_limit, max_limit, base_limit);
            
            return int(limit/100)*100;
            
        }
        
        // 요격 병력 가중치 함수
        float get_defence_weight(pk::unit@ unit)
        {
            float weight = 1.1f;
            if (요격병력제한_능력가중치적용)
            {
                float avg_stat = (unit.attr.stat[부대능력_공격] + unit.attr.stat[부대능력_방어]) / 2.f;
                weight = weight * avg_stat / 50.f; 
            }
            return weight;
        }
        
        // 출병 시 거점잔여병력 고려한 제한값
        int get_base_limit(pk::building@ base, pk::unit@ unit, int remain_limit)
        {
            int unit_troops = unit.troops;
            int base_troops = pk::get_troops(base);
            int base_remain = base_troops - pk::max(0, remain_limit);
            int base_limit  = unit_troops;
            if (base_remain > unit_troops)
                base_limit = unit_troops;
            else if (unit_troops > base_remain and base_remain >= 0)
                base_limit = pk::max(1000, unit_troops - (unit_troops - base_remain)/2);
            else if (base_remain < 0 and base_troops > 0)
                base_limit = pk::max(1, base_troops / 2);
            
            return base_limit;
        }
        
        
        //---------------------------------------------------------------------------------------
        // 원정 부대 제한
        //---------------------------------------------------------------------------------------
        
        int get_attack_limit(pk::building@ base, pk::unit@ unit)
        {
            int limit = unit.troops;
            
            // 원정 공성부대인 경우
            if (공성부대_제한설정 and check_siege_unit(unit))
            {
                int tekisei = pk::min(적성_S, pk::get_tekisei(unit, pk::get_ground_weapon_id(unit)));
                limit = 공성부대_제한기준병력 + (공성부대_적성고려단위 * (tekisei - 적성_C));
            }
            
            // 원정 계략부대인 경우 
            else if (계략부대_제한설정 and check_atk_strategy_unit(unit))
            {
                limit = 계략부대_최대제한병력;
            }
            
            // 거점잔여병력 계산 ('20.9.20)
            int base_limit = get_base_limit(base, unit, 원정병력제한_거점잔여병력);
            
            // 최대병력 가중치 적용
            limit = pk::min(limit, base_limit);
            
            
            return int(limit/100)*100;
        }
        
        
        //---------------------------------------------------------------------------------------
        // 출진 제한 조건 확인
        //---------------------------------------------------------------------------------------
        
        // 정상적인 출진부대인지 확인
        bool check_valid_unit(pk::unit@ unit_t, int type)
        {
            if (!pk::is_alive(unit_t))      return false;
            if (type != 0)                  return false;	// 출진 부대가 아닌 경우 제외 (임의 생성 부대)
			if (unit_t.type != 부대종류_전투)	return false;	// 수송 부대 제외
            if (unit_t.attr.stat[부대능력_이동] < 2)	return false;	// 2칸 이상 이동불가 시 부대생성 자동 취소 (이동력 2~4 = 평지 1칸)
            if (pk::get_service(unit_t) >= 건물_거점끝) return false;      // 소속 거점 확인
            
            int force_id = unit_t.get_force_id();
            pk::force@ force = pk::get_force(force_id);
			if (!pk::is_alive(force) or !pk::is_normal_force(force)) return false;  // 소속 세력 확인  
            if (force_id != pk::get_current_turn_force_id()) return false;  // 현재 턴세력 아닌 경우 ('19.2.15)        
            
            return true;
        }
        
        // 출진무장 최적화할 세력 확인
        bool check_force_option(pk::unit@ unit_t)
        {
            // 플레이어 군단 미적용 (유저의 부대편성 무시하면서 주장편성하므로 미적용 권장)
            if (pk::is_player_controlled(unit_t)) 
            {
                if (출진병력최적화_유저군단적용) return true;
                else return false;   
            }
            
            // 0: 컴퓨터AI 와 플레이어_위임군단 모두,  1: 플레이어_위임군단만, 2: 컴퓨터AI만,  3: 모두 미적용
            if      (출진병력최적화_세력조건 == 0 and !pk::is_player_controlled(unit_t)) return true;
            else if (출진병력최적화_세력조건 == 1 and unit_t.is_player() and !pk::is_player_controlled(unit_t)) return true;
            else if (출진병력최적화_세력조건 == 2 and !unit_t.is_player()) return true;
            else if (출진병력최적화_세력조건 == 3) return false;
            
            return false;
        }
        
        //---------------------------------------------------------------------------------------
        
        // 요격출진여부 판단 함수 : 침략한 적부대 병력수준 확인
        bool check_enemy_invasion(pk::building@ base)
        {
            if (!pk::is_alive(base)) return false;
            
            int city_id = pk::get_city_id(base.pos);
            if (atk_unit_count[city_id] == 0) return false;
            
            return true;
        }
        
        // 건설편제 여부 판단 ('19.2.15)
        bool check_construction_unit(pk::unit@ unit)
        {
            if (pk::is_player_controlled(unit)) return false; // 유저군단은 무조건 제외
            
            if (unit.has_skill(특기_축성) and unit.gold >= 건설편제_기준소지금) return true;  // 축성 특기
            
            if (unit.type == 부대종류_전투 and pk::get_member_count(unit) <= 1)   // 1인대
            {
                if (unit.gold >= 건설편제_기준소지금 and unit.troops <= 건설편제_기준병력) 
                    return true; 
            }
            return false;
        }
        
        // 공성부대 여부 판단 함수 ('19.3.3)
        bool check_siege_unit(pk::unit@ unit)
        {
            if (pk::is_player_controlled(unit)) return false; // 유저군단은 무조건 제외
            
            int weapon_id = pk::get_ground_weapon_id(unit);
            if (pk::equipment_id_to_heishu(weapon_id) == 병종_병기)
                return true;
            
            return false;
        }
        
        
        // 원정 계략부대 여부 판단 함수 ('19.3.1)
        bool check_atk_strategy_unit(pk::unit@ unit)
        {
            if (pk::is_player_controlled(unit)) return false; // 유저군단은 무조건 제외
            
            // 부대 적성 판정 : S이상인 경우 전투부대 취급
            if (계략부대_적성고려 and pk::get_tekisei(unit) >= 적성_S)
                return false;
            
            // 보유 특기 확인
            for (int i = 0; i < 3; i++)
            {
                pk::person@ member = pk::get_person(unit.member[i]);
                if (pk::is_alive(member))
                {
                    int skill_id = member.skill;
                    pk::skill@ skill = pk::get_skill(skill_id);
                    
                    // 신/장 계열 공격특기인 경우 전투부대 취급 
                    if (skill_id >= 특기_창장 and skill_id <= 특기_맹장)
                        return false;   
                    
                    // 계략특기 우대
                    if (계략부대_특기우대 and pk::is_alive(skill))
                    {
                        if (skill.type == 특기종류_계략) return true;    
                    }
                }
            }
            
            // 무조건 우대 특기
            if (unit.has_skill(특기_신산) or unit.has_skill(특기_허실) or unit.has_skill(특기_백출) 
                or unit.has_skill(특기_귀모) or unit.has_skill(특기_연환)) 
                return true;
            
            // 지력 대 공방 비율 판단
            float stat_ratio = float(2.0f * unit.attr.stat[부대능력_지력] / (unit.attr.stat[부대능력_공격] + unit.attr.stat[부대능력_방어]));
            if (stat_ratio >= 계략부대_지력공방비) 
                return true;
            
            return false;
        }
        
		
        //---------------------------------------------------------------------------------------
        
        
        string get_weapon_name(int weapon_id)
        {
            string weapon_name;
            switch(weapon_id)
            {
                case 병기_검  : weapon_name = "검병"; break;
                case 병기_창  : weapon_name = "창병"; break;
                case 병기_극  : weapon_name = "극병"; break;
                case 병기_노  : weapon_name = "노병"; break;
                case 병기_군마 : weapon_name = "기병"; break;
                case 병기_충차 : weapon_name = "충차"; break;
                case 병기_정란 : weapon_name = "정란"; break;
                case 병기_투석 : weapon_name = "투석"; break;
                case 병기_목수 : weapon_name = "목수"; break;
                case 병기_주가 : weapon_name = "수군"; break;
                case 병기_누선 : weapon_name = "수군"; break;
                case 병기_투함 : weapon_name = "수군"; break;
                default : weapon_name = "??"; break;
            }
            return weapon_name;
        }
        
        string get_order_info(int order)
        {
            string name;
            switch(order)
            {
                case 0  : name = "부대임무_대기"; break;
                case 1  : name = "부대임무_이동"; break;
                case 2  : name = "부대임무_설치"; break;
                case 3  : name = "부대임무_공격"; break;
                case 4  : name = "부대임무_퇴각"; break;
                case 5  : name = "부대임무_물림"; break;
                case 6  : name = "부대임무_호위"; break;
                case 7  : name = "부대임무_공성"; break;
                case 8  : name = "부대임무_수복"; break;
                case 9  : name = "부대임무_정복"; break;
                case 10 : name = "부대임무_보급"; break;
                case 11 : name = "부대임무_섬멸"; break;
                case 12 : name = "부대임무_추종"; break;
                case 13 : name = "부대임무_끝" ; break;
                default : name = "부대임무_없음"; break;
            }
            
            return name;
        }
        
        
        bool 디버그모드 = false;
        
	} 

	Main main;
	
} 