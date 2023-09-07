/*
수정 by 일송정

이 스크립트는 기마책사님이 직접 만드신 스크립트입니다 .
여기에 제가 추가로 자잘하게 몇가지 수정을 했는데요.
AI의 부대가 아군 거점의 병력이 부족하여 함락 위기인 경우, 위급한 거점을 더 신경써서 구원하도록 우선순위를 좀 매겼습니다. 
거점으로부터의 거리에 따라 적의 공격 부대 병력 수를 체크하여 구원가도록 추가 설정한 부분이 있습니다. 
또 공격 AI에겐 병력이 부족한 적의 거점에 좀 더 집중하도록 만들기도 했고요.
병력 초과를 막기 위해서 거점의 60-70%만 활용하는 설정으로 밸런스를 맞추는 작업도 했습니다.

[수정 내용]
1. const bool 건설편제_제외설정 true에서 false로

2. const bool  계략부대_제외설정 true에서 false로

3. const float 진입부대_초과한도기준 1.0f에서 0.7f로

4. '진입부대_초과한도기준'를 응용한 항구, 관문의 초과한도를 다루는 '항관진입_초과한도기준' 항목 추가

5. '아군 거점 수성 지원'에 거리 개념을 추가한 '거점병력부족_부대수성허용' 항목, '병력부족거점_수성지원' 항목 추가. 
    부대가 '아군 거점 수성 지원' '거점병력부족_부대수성허용' '병력부족거점_수성지원' '적거점_점령허용' 여부를 먼저 더 우선시 하게 설정.

6. '적거점_점령허용'에 적 거점이 1천 이하 혹은 약해보이면 무조건 공격하도록 추가 설정.

7. '아군거점_수성지원' 항목에서 'if (unit.type != 부대종류_전투) return false;    // 전투 병과 아니면 제외' 부분 삭제.

8. 진입 부대의 병기 초과항목을 계산하는 수식에서 '진입부대_초과한도기준'를 적용 받지 않도록 exceed_limit 삭제.

9. 부대병력 2000 이상 증발 시 부대가 거점에 들어가지 못하는 설정을 부대병력 1 이상 증발 시 못들어가도록 설정.

10. 공성/함선병기 1이상 또는 전투병기 2000 이상 증발 시 거점에 부대가 진입 못하는 설정을 공성/함선병기 10이상 또는 전투병기 20000 이상 증발 시로 수정

11. 부대가 야전에서 행군 중 공백지를 인지하면 점령

12. 병량 부족한 부대는 후퇴

13. 전투가 벌어지는 거점 근처에 부대들 너무 몰리는 것 방지

14. 징병 못하게 병영 공격

15. 국경에 적 침입시 출진했던 일부 부대들 복귀 

16. 병목현상 방지 위해 지나치게 한 곳에 부대가 모이면 다른 곳으로 이동, 

17. 거점 내구도가 낮아 함락위기인 경우 수비측 부대는 거점에 진입하지 않고 대기하라

18. 전황상 유리한 경우 진격, 불리한 경우 후퇴

19. 수상전에서 공격측 부대들이 수비측 항구에 너무 몰린 경우 다른 항구로 진격
*/


/*
// 만든이: 기마책사
// Update: '19.2.1     / 최초내용: 전투병과부대 인접한 공격목표부대 재지정하는 스크립트 작성 
// Update: '19.2.19    / 변경내용: 가중치옵션(방어력,신분), 건설편제 제외옵션, 계략부대 제외옵션, 적거점 점령허용 옵션 반영
// Update: '19.2.27    / 변경내용: NPC부대 제외조건 추가
// Update: '19.3.1     / 변경내용: 부대목표변경_병력가중치적용 옵션 추가
// Update: '19.3.4     / 변경내용: null point error 오류 수정
// Update: '19.3.9     / 변경내용: 궤멸직전 부대 소속거점으로 복귀 기능 추가
// Update: '19.3.25    / 변경내용: 주변 거점 교전 시 거점으로 지원 이동
// Update: '20.8.26    / 변경내용: 캠페인에서는 스크립트 효과 발동되지 않도록 수정, 난이도_특급에서만 동작하도록 수정
// Update: '20.9.8     / 변경내용: 계략특기 우대부대 집중공격을 위한 가중치 조건 추가, 간접공성병기 교전조건 추가, 임무 업데이트 범위제한(검색리소스 개선)
// Update: '20.9.16    / 변경내용: 적거점점령/아군거점수성지원 알고리즘 조건 추가
// Update: '20.9.19    / 변경내용: 아군거점수성지원 알고리즘 수정, 진입부대_초과병력귀환 기능 추가, 거점원군 파병부대의 거점진입 방지 추가
// Update: '20.9.21    / 변경내용: 진입부대_초과병력귀환 병기초과 확인조건 추가, 목표거점 영토에 있을 경우에만 초과여부 확인 (거점원군 출진고려)
*/

namespace 야전부대교전최적화
{
    //=======================================================================================
    // 유저 설정 (true = on, false = off)
    
    // 부대/거점 공격목표 변경 시기 설정 (3: 턴시작/중간 모두, 2: 턴중간 변동조건마다, 1: 턴시작 시에만,  0: 기능OFF)
    const int  업데이트_주기설정 = 3;       // 주의 : 업데이트 주기를 2 또는 3으로 설정 시 유닛이 많아지면 게임이 느려질 수 있음
    
    const bool 목표부대변경     = true;    // 공격목표부대 재설정 시 타켓부대 설정여부 (거점목표 변경에는 영향 안줌)
    const bool 대화표시설정     = false;    // 공격목표 변경내용 대화표시여부      (2021.09.08. 일송정이 false로 수정)
    
    const int  부대목표변경_세력조건 = 0;     // 0: 컴퓨터AI 와 플레이어_위임군단 모두,  1: 플레이어_위임군단만, 2: 컴퓨터AI만,  3: 모두 미적용
    const bool 부대목표변경_유저군단적용 = false;   // 세력조건과 별개로 적용여부 설정, 유저의 임무지정 무시되므로 false 권장
    
    // 가중치 추가옵션 설정 (기본적으로는 병과/적성만으로 판단함)
    const bool 부대목표변경_공격가중치적용 = false;   // 목표대상의 부대공격력을 가중치 추가 적용
    const bool 부대목표변경_방어가중치적용 = true;   // 목표대상의 부대방어력을 가중치 추가 적용
    const bool 부대목표변경_신분가중치적용 = true;   // 목표대상이 군주/도독 부대인 경우 가중치 추가 적용 (패시브효과.cpp 내 부대궤멸효과 사용 시 추천 설정)
    const bool 부대목표변경_병력가중치적용 = true;   // 목표대상과 임무부대의 병력차이에 대한 가중치 추가 적용 (궤멸시키기 쉬운 소부대를 공격할 가능성 높임)
    const bool 부대목표변경_계략가중치적용 = false;   // 목표대상이 계략특기 보유부대인 경우 가중치 추가 적용
    
    // 교전가능 시 건설편제 판단 기준
    const bool 건설편제_제외설정    = false;   // 2021.01.15 일송정 수정
    const int  건설편제_기준소지금  = 1000;     // 기준값이 높아지면 컴퓨터 건설명령불가
    const int  건설편제_기준병력    = 3000;     // 기준 소지금 이상 및 기준병력 이하인 경우 건설편제로 취급
    const bool 건설편제_임무우대    = true;     // 부대임무가 설치로 설정된 경우 함정 외 시설 허용
    
    // 교전가능 시 계략부대 판단 기준
    const bool  계략부대_제외설정  = false;   // 2021.01.15 일송정 수정
    const bool  계략부대_특기우대 = true;     // 계략계열 특기 보유한 부대 우대 (신산,허실,백출,귀모,연환은 무조건 우대)
    const float 계략부대_지력공방비 = 1.5f;      // 부대지력이 부대공방평균 대비 기준 이상이면 계략부대로 취급
    
    // 교전가능 시 목수/정란/투석 부대 부대전투 설정 ('20.8.30)
    const bool  공성병기_부대전투_참여설정  = true; // 공성병기부대가 부대간 전투에 참여할지 설정
    const int   공성병기_부대전투_기준기력  = 60;   // 공성병기부대가 부대간 전투에 참여기준 (기력 이상인 경우 참여)
    
    //---------------------------------------------------------------------------------------
    
    // 교전 중인 주변 거점 병력 부족 시 지원
    const bool 아군거점_수성지원 = true;   // 근접 전투 부대 주변의 교전 중인 거점에 병력 적을 시 거점 진입하여 수성 지원
    const bool 도시거점_수성지원 = true;   // 아군거점_수성지원 설정 true 인 경우: 도시거점 수성지원 여부 활성화
    const bool 관문항구_수성지원 = true;   // 아군거점_수성지원 설정 true 인 경우: 관문항구 수성지원 여부 활성화
    
    // 적지 침투 부대의 거점공략 허용
    const bool 적거점_점령허용    = true;   // 부대가 적지에 있을 시 주변에 교전가능한 부대가 없을 경우 거점 공략으로 임무설정됨
    const bool 적거점_점령성격적용 = true;   // 점령 허용 시 부대 주장의 성격에 따른 행동 (true=대담,저돌만 점령실행  / false=성격 관계없이 점령실행)

    const bool 적거점_계속공격허용 = true;   // 적의 거점과 적 부대 병력이 적어보이면 계속 공격 , 2021.09.18. 일송정 수정.
    
    // 거점 진입 시 병력 초과인 경우 소속거점으로 복귀 
    const bool  진입부대_초과병력귀환 = true;   // 거점으로 부대진입 전 병력한도 초과여부 확인 후 귀환목표 재설정
    const float 진입부대_초과한도기준 = 0.7f;   // 거점최대병력 대비 병력/병기(거점+부대) 한도초과 기준설정 (0.0f~1.0f)  , 2021.01.15 일송정 수정
    const float 항관진입_초과한도기준 = 0.4f;   // 항구와 관문 한도초과 기준설정 (0.0f~1.0f) , 2021.01.15 일송정 수정
    const bool  진입부대_초과병기귀환 = true;   // 거점으로 부대진입 전 병기한도 초과여부 확인 후 귀환목표 재설정
    const float 진입부대_초과병기_거점병력기준 = 0.5f;   // 거점최대병력 대비 현재병력이 기준 이하일 경우 병기 초과 무시 (0.0f~1.0f)
    
    //---------------------------------------------------------------------------------------
    const bool 극소병력부대_거점복귀허용 = false;    // 궤멸직전 AI부대 소속거점으로 복귀 기능 (유저부대 미적용)
    const int  극소병력부대_복귀병력기준 = 650;     // 소속거점 복귀 기준 병력, 기준 미만 시 거점 복귀함
    const float 부대복귀_병량기준_비율 = 0.4f;     // 소속거점 복귀 기준 병량 비율, 2021.08.27 일송정 수정		

    const bool 군량_병력부족시_인접거점이동 = true;    // 군량이나 병력 부족한 부대를 인근 거점으로 이동  (유저부대 미적용). 2022.04.27. 일송정 추가

    const bool 거점병력부족_부대수성허용 = true;    // 궤멸직전의 소속거점으로 복귀 기능 (유저부대 미적용), 2021.01.15 일송정 수정	

    const bool 전방국경_침입_후퇴 = true;   // 전방 거점에 침입 발생하여 후퇴 2022.06.02 일송정 수정 	
 
    const bool 거점근처_부대혼잡방지 = true;   // 거점 근처에 너무 많은 부대들 복귀시키기, 2021.09.02 일송정 수정 	

    const bool 아군부대_정체방지 = true;   // 아군 부대들 대치 상황 너무 길어지면 후퇴 2022.06.18 일송정 수정
	
    const bool 거점붕괴_부대대기허용 = true;   // 거점 붕괴 우려시 진입을 막음, 2022.06.02 일송정 수정		
    const bool 작전상_후퇴 = true;   // 전투 추세상 후퇴 2022.06.02 일송정 수정 																																											 																																											 	
    const bool 무조건_공격허용_대상 = true;   // 무조건 공격 먼저 해야할 병력 빈약 거점, 2022.06.18. 일송정 수정 	

    const bool 공백지_공격허용 = true;   // 무조건 공격 먼저 해야할 공백지, 2022.06.18. 일송정 수정 
    const bool 병영_공격허용 = true;   // 무조건 공격 먼저 해야할 병영 , 2022.06.18. 일송정 수정 
    
    //=======================================================================================
    
    
	class Main
	{
        
        Main()
		{
            pk::bind(102, pk::trigger102_t(onGameInit));
            pk::bind(111, pk::trigger111_t(onTurnStart));
            
            pk::bind(160, pk::trigger160_t(onBuildingCreate));
            pk::bind(161, pk::trigger161_t(onBuildingDestroyed));

            pk::bind(170, pk::trigger170_t(onUnitCreate));
            pk::bind(171, pk::trigger171_t(onUnitEliminated));
            pk::bind(172, pk::trigger172_t(onUnitPosChange));
            pk::bind(173, pk::trigger173_t(onUnitExpAdd));
        }
        //---------------------------------------------------------------------------
        
        pk::unit@ src_unit;
        pk::unit@ dst_unit_old;
        pk::unit@ dst_unit_new;
        
        pk::list<pk::unit@> list_candidate_unit;
        array<int> arr_target_unit_id(부대_끝, -1);
        array<int> arr_target_base_id(부대_끝, -1);
        
        array<float> heishu_weight(6, 0.0f);
        float heishu_null   = 0.0f;   
        float heishu_weak   = 0.5f;   
        float heishu_normal = 1.0f;   
        float heishu_strong = 1.5f;   
        int order_update_range = 10;  // 건물 생성/제거 또는 유닛 생성/제거/이동 시 임무업데이트 대상부대 검색범위 ('20.9.7)
        
        //---------------------------------------------------------------------------
        // 트리거 동작부
        //---------------------------------------------------------------------------
        
        // 게임 초기화 시 업데이트
        void onGameInit()
        {
            if (pk::is_campaign()) return ;
            if (pk::get_scenario().no >= 16) return;
            if (pk::get_scenario().difficulty < 난이도_특급) return;
            clear_target_info();
            pk::force@ force = pk::get_force(pk::get_current_turn_force_id());
            onTurnStart(force);
        }
        
        // 턴 시작 시 업데이트
        void onTurnStart(pk::force@ force)
        {
            if (pk::is_campaign()) return;
            if (pk::get_scenario().difficulty < 난이도_특급) return;
            
            if (!pk::is_normal_force(force)) return;
            optimize_current_force_target();    // 공통함수호출
			optimize_unit_target_At_Turn_Start();    // 턴시작때에만 할 것들. 2022.08.25 일송정 추가
        }
        
        // 건물 생성 시 업데이트
        void onBuildingCreate(pk::building@ building, int type)
        {
            if (pk::is_campaign()) return;
            if (pk::get_scenario().difficulty < 난이도_특급) return;
            
            optimize_pos_range_target(building.pos);    // 공통함수호출 ('20.9.7)
        }
        
        // 건물 파괴 시 업데이트
        void onBuildingDestroyed(pk::building@ building, int type)
        {
            if (pk::is_campaign()) return;
            if (pk::get_scenario().difficulty < 난이도_특급) return;
            
            optimize_pos_range_target(building.pos);    // 공통함수호출 ('20.9.7)
        }
        
        // 부대 생성 시 업데이트
        void onUnitCreate(pk::unit@ unit, int type)
        {
            if (pk::is_campaign()) return;
            if (pk::get_scenario().difficulty < 난이도_특급) return;
            
            // 생성된 부대의 공격목표값 초기화
            arr_target_unit_id[unit.get_id()] = -1;
            arr_target_base_id[unit.get_id()] = -1;
        }
        
        // 부대 궤멸 시 업데이트
        void onUnitEliminated(pk::unit@ unit, int type)
        {
            if (pk::is_campaign()) return;
            if (pk::get_scenario().difficulty < 난이도_특급) return;
            
            // 궤멸된 부대의 공격목표값 초기화
            arr_target_unit_id[unit.get_id()] = -1;
            arr_target_base_id[unit.get_id()] = -1;
            
            optimize_pos_range_target(unit.pos);    // 공통함수호출 ('20.9.7)
        }
        
        // 부대 경험치 획득 시
        void onUnitExpAdd(pk::unit@ unit, int type)
        {
            if (pk::is_campaign()) return;
            if (pk::get_scenario().difficulty < 난이도_특급) return;
            if (!pk::is_alive(unit)) return;

            optimize_pos_range_target(unit.pos);    // 공통함수호출 ('20.9.7)
        }
        
        // 부대 위치 변동 시 (전법에 의한 이동 포함)
        void onUnitPosChange(pk::unit@ unit_t, const pk::point &in pos)
        {
            if (pk::is_campaign()) return;
            if (pk::get_scenario().difficulty < 난이도_특급) return;
            
            if (!check_valid_unit(unit_t)) return;
            
            int force_id = pk::get_current_turn_force_id();
            if (!pk::is_normal_force(force_id)) return;
            pk::force@ force = pk::get_force(force_id);
            
            optimize_pos_range_target(pos);    // 공통함수호출 ('20.9.7)
            
        }
        
        //---------------------------------------------------------------------------
        // 기준 좌표로부터 일정 거리 내에 있는 현재 턴 세력 부대 최적화 (공통함수 추가, '20.9.7)
        void optimize_pos_range_target(pk::point pos_t)
        {
            if (업데이트_주기설정 != 2 and 업데이트_주기설정 != 3) return;
            
            if (!pk::is_valid_pos(pos_t)) return;
            
            int force_id = pk::get_current_turn_force_id();
            if (!pk::is_normal_force(force_id)) return;
            pk::force@ force = pk::get_force(force_id);
            
            // 해당 좌표로부터 범위 내 현재 턴 부대검색
            pk::array<pk::point> arr_range = pk::range(pos_t, 1, order_update_range);
            for (int i = 0; i < int(arr_range.length); i++)
            {
                pk::unit@ unit = pk::get_unit(arr_range[i]);
                if (check_valid_unit(unit) and check_force_option(unit))
                {
                    if (!unit.action_done and unit.get_force_id() == force_id )
                        optimize_combat_unit_target(unit);     // 부대목표 재설정 함수    
                }
            }
        }
        
        // 현재 턴 세력 부대 최적화 (공통함수)
        void optimize_current_force_target()
        {
            if (업데이트_주기설정 != 1 and 업데이트_주기설정 != 3) return;
            
            int force_id = pk::get_current_turn_force_id();
            if (!pk::is_normal_force(force_id)) return;
            pk::force@ force = pk::get_force(force_id);
            
            // 세력 전체 미행동 부대 
            pk::array<pk::unit@> arr_unit_list = pk::list_to_array(pk::get_unit_list());
            if (int(arr_unit_list.length) == 0) return;
            for (int i = 0; i < int(arr_unit_list.length); i++)
            {
                pk::unit@ unit = arr_unit_list[i];
                if (check_valid_unit(unit) and check_force_option(unit))
                {
                    if (!unit.action_done and unit.get_force_id() == force_id )
                        optimize_combat_unit_target(unit);     // 부대목표 재설정 함수    
                }
            }
        }

        // 부대들이 턴시작때에만 할 것들. 2022.08.25 일송정 추가
        void optimize_unit_target_At_Turn_Start()
        {
          
            int force_id = pk::get_current_turn_force_id();
            if (!pk::is_normal_force(force_id)) return;
            pk::force@ force = pk::get_force(force_id);
            
            // 세력 전체 미행동 부대 
            pk::array<pk::unit@> arr_unit_list = pk::list_to_array(pk::get_unit_list());
            if (int(arr_unit_list.length) == 0) return;
            for (int i = 0; i < int(arr_unit_list.length); i++)
            {
                pk::unit@ unit = arr_unit_list[i];
                if (check_valid_unit(unit) and check_force_option(unit))
                {
                    if (!unit.action_done and unit.get_force_id() == force_id )
                        optimize_At_Turn_Start(unit);     // 부대목표 재설정 함수    
                }
            }
        }
        
        //---------------------------------------------------------------------------
        //---------------------------------------------------------------------------
        
        // 부대목표 재설정 함수
        void optimize_combat_unit_target(pk::unit@ unit)
        {
            // 정상부대가 아니면 종료
            if (!pk::is_alive(unit)) return;
            if (unit.status != 부대상태_통상) return;
            
            // 부대 목표
            @dst_unit_old = pk::hex_object_to_unit(pk::get_hex_object(unit.target_pos));
            
            // ------ 공격 가능한 적부대 검색함수 호출 -------------
            // 주의 :: def_force_base_nearby, atk_enemy_base_nearby, retreat_exceed_unit 함수보다 먼저 사용할 것
            get_list_candidate_unit(unit);
            int candidate_count = list_candidate_unit.count;
            if (candidate_count == 0)   // 부대가 원군도착인 경우 거점주변 추가탐색
            {
                search_enemy_on_reinforce_engage(unit);
                candidate_count = list_candidate_unit.count;
            }// --------------------------------------------
            
            // 개발자 디버깅용 로그 출력
            if (디버그모드)  
            {
                string src_name = (pk::is_alive(unit))?         pk::decode(pk::get_name(pk::get_person(unit.leader)))+"대"         : "확인불가" ;
                string dst_name = (pk::is_alive(dst_unit_old))? pk::decode(pk::get_name(pk::get_person(dst_unit_old.leader)))+"대" : "확인불가" ;
                pk::info( pk::format("{} 근처부대수={}", src_name, candidate_count) );
            }

            // 거점점령, 수성지원, 점령군 초과병력귀환
            if (아군거점_수성지원 and def_force_base_nearby(unit)) return;  // 주변의 교전 중인 아군 거점 지원
            if (적거점_점령허용  and atk_enemy_base_nearby(unit)) return;  // 부대좌표로 요격/원정 여부 판단 : 적지원정이면 거점공략 설정
            if ((진입부대_초과병력귀환 or 진입부대_초과병기귀환) and retreat_exceed_unit(unit)) return;  // 거점 병력/병기 초과 시 타거점으로 진로변경
            
            // 궤멸직전 부대 거점 복귀 ('19.3.9)
            if (극소병력부대_거점복귀허용 and retreat_battlefield(unit)) return;

            // AI건설편제인 경우 임무 미변경
            if (건설편제_제외설정 and (check_construction_unit(unit))) return ;
            
            // 계략부대인 경우 임무 미변경
            if (계략부대_제외설정 and (func_strategy_unit_type(unit) > 0)) return ;
            
            // 공격목표부대 변경
            if (목표부대변경 and candidate_count > 0)
                func_change_target_unit(unit);  // 주변 적부대 공격설정

            // 거점병력 부족 부대 복귀
            if (거점병력부족_부대수성허용  and defend_castle (unit)) return;      // 2021.01.15 일송정 수정

            // 적의 취약거점 무조건 공격 
            if (무조건_공격허용_대상 and no_holds_barred(unit)) return;     // 2022.06.18 일송정 추가.

            // 군량 적고 병력 적은 부대 거점 복귀 ('22.04.27)
            if (군량_병력부족시_인접거점이동 and retreat_battlefield_nearby(unit)) return;

        }
        
        
        //---------------------------------------------------------------------------
        //---------------------------------------------------------------------------
        
        // 부대목표 재설정 함수, 턴시작때에만 할 것들. 2022.08.25 일송정 추가
        void optimize_At_Turn_Start(pk::unit@ unit)
        {
            // 정상부대가 아니면 종료
            if (!pk::is_alive(unit)) return;
            if (unit.status != 부대상태_통상) return;
            
            // 부대 목표
            @dst_unit_old = pk::hex_object_to_unit(pk::get_hex_object(unit.target_pos));
            
            // ------ 공격 가능한 적부대 검색함수 호출 -------------
            // 주의 :: def_force_base_nearby, atk_enemy_base_nearby, retreat_exceed_unit 함수보다 먼저 사용할 것
            get_list_candidate_unit(unit);
            int candidate_count = list_candidate_unit.count;
            if (candidate_count == 0)   // 부대가 원군도착인 경우 거점주변 추가탐색
            {
                search_enemy_on_reinforce_engage(unit);
                candidate_count = list_candidate_unit.count;
            }// --------------------------------------------
            
            // 개발자 디버깅용 로그 출력
            if (디버그모드)  
            {
                string src_name = (pk::is_alive(unit))?         pk::decode(pk::get_name(pk::get_person(unit.leader)))+"대"         : "확인불가" ;
                string dst_name = (pk::is_alive(dst_unit_old))? pk::decode(pk::get_name(pk::get_person(dst_unit_old.leader)))+"대" : "확인불가" ;
                pk::info( pk::format("{} 근처부대수={}", src_name, candidate_count) );
            }

            // 거점붕괴 우려시 부대 진입 막음		
            if (거점붕괴_부대대기허용 and collapse_base_nearby (unit)) return;      // 2022.06.02 일송정 추가

            // 전방 국경에 침입 발생하여 후퇴
            if (전방국경_침입_후퇴 and front_base_retreat(unit)) return;     // 2022.06.02 일송정 추가

            // 전투 추세상 투회
            if (작전상_후퇴 and retreat_unit (unit)) return;     // 2022.06.02 일송정 추가

			
            // 적의 공백지,병영 무조건 공격 
			
            if (공백지_공격허용 and attack_empty_base(unit)) return;     // 2022.06.18 일송정 추가.
			
            if (병영_공격허용 and attack_barrack(unit)) return;     // 2022.06.18 일송정 추가.
			
			
            if (적거점_계속공격허용 and keep_atk_enemy_base_nearby(unit)) return;  // 2021.09.18 일송정 추가.
			
						
            // 거점 근처 너무 많은 부대들 복귀 2021.09.02 일송정 수정
            if (거점근처_부대혼잡방지 and unit_base_nearby(unit)) return;

            // 부대 대치 상황 너무 길어지면 퇴각 2022.06.18 일송정 수정
            if (아군부대_정체방지 and unit_jam(unit)) return;

        }
        
        
        //---------------------------------------------------------------------------



        // 항관 내구도 바닥시 주위 부대들 후퇴      (2022.06.02 일송정 추가 )
        bool collapse_base_nearby(pk::unit@ unit)
        {
            if (!pk::is_alive(unit)) return false;

            if (pk::is_player_controlled(unit)) return false;            
            

            pk::array<pk::point> arr = pk::get_movable_pos(unit);
            for (int i = 0; i < int(arr.length); i++)
            {
            pk::building@ target_base = pk::get_building(arr[i]);
            pk::building@ service_base = pk::get_building(pk::get_service(unit));


            if (pk::is_alive(target_base) and 건물_관문시작 <= target_base.get_id() and target_base.get_id() < 건물_항구끝)
            {
                int unit_id    = unit.get_id();
                int service_id = service_base.get_id();
                int target_id  = target_base.get_id();
                pk::person@ leader = pk::get_person(unit.leader);
                


                //  항관 내구도 바닥시 주위 부대들 후퇴
                if ( target_base.get_force_id() == unit.get_force_id() and enemy_approach_direct(target_base) and target_base.hp <= 450 )
                {
																		   
                        pk::set_order(unit, 부대임무_이동, unit.pos);							
                        // 목표변경 메시지
                        if (대화표시설정 and pk::is_in_screen(unit.pos))
                        {
                            string target_name = pk::decode(pk::get_name(target_base));
                            switch(pk::rand(3))
                            {
                                case 0: pk::say(pk::encode(pk::format("거점이 붕괴하려 한다.\n\x1b[2x{}\x1b[0x 외곽에서 대기하라!", target_name)), leader); break;
                                case 1: pk::say(pk::encode(pk::format("거점이 붕괴하려 한다.\n\x1b[2x{}\x1b[0x 외곽에서 대기하라!", target_name)), leader); break;
                                case 2: pk::say(pk::encode(pk::format("거점이 붕괴하려 한다.\n\x1b[2x{}\x1b[0x 외곽에서 대기하라!", target_name)), leader); break;
                            }
                        }
                        
                         return true;    
              
                  }	

               }


				  
            }
            return false;            
        }



        //---------------------------------------------------------------------------

        
        // 극소병력 부대 야전 이탈 명령,  (2021.08.27. 병량조건 추가 일송정 수정)
        bool retreat_battlefield(pk::unit@ unit)
        {
            if (!pk::is_alive(unit)) return false;
            if (pk::is_player_controlled(unit)) return false;
            
            if (int(unit.troops) < 극소병력부대_복귀병력기준 or unit.food < float (부대복귀_병량기준_비율 * unit.troops ))
            {
                int unit_id = unit.get_id();
                int service_id = pk::get_service(unit);
                pk::building@ base = pk::get_building(pk::get_service(unit));
                if (pk::is_alive(base) and arr_target_base_id[unit_id] != service_id and pk::get_distance(base.pos, unit.pos) <= 25)
                {
                    arr_target_base_id[unit_id] = service_id;
                    pk::set_order(unit, 부대임무_이동, base.pos);
                    return true;
                }
            }
            
            return false;
        }
        
        //---------------------------------------------------------------------------


        // 군량 적고 병력 적은 부대 거점 복귀,  (2022.04.27. 일송정 추가)
        bool retreat_battlefield_nearby(pk::unit@ unit) 
        {
            if (!pk::is_alive(unit)) return false;
            if (pk::is_player_controlled(unit)) return false;

       if (!pk::is_player_controlled(unit) and (int(unit.troops) < 극소병력부대_복귀병력기준 or unit.food < float (부대복귀_병량기준_비율 * unit.troops )))   
          {				
            pk::person@ leader = pk::get_person(unit.leader);
            string leader_name = pk::decode(pk::get_name(leader));
            string target_name;
            pk::building@ target_base;
            pk::array<pk::point> arr = pk::get_movable_pos(unit);
            for (int i = 0; i < int(arr.length); i++)
            {
                pk::building@ base = pk::get_building(arr[i]);
                if (pk::is_alive(base))
                  {
                    if (건물_도시시작 <= base.get_id() and base.get_id() < 건물_거점끝 and 450 <= base.hp and unit.get_force_id() == base.get_force_id())  
                    {
                        @target_base = @base;
                        
                    }
                  }
            }

			int targetFriendly = getAdjacentBase(unit);
            
            if (pk::is_alive(target_base) or (pk::is_alive(pk::get_building(targetFriendly)) and 450 <= pk::get_building(targetFriendly).hp ))
            {

                    // 아군 거점 이동 재설정
                    pk::set_order(unit, 부대임무_공격, (pk::is_alive(target_base)) ? target_base.pos : pk::get_building(targetFriendly).get_pos());
                    // 목표변경 메시지
                    if (대화표시설정 and pk::is_in_screen(unit.pos))
                    {
                        string target_name = (pk::is_alive(target_base)) ? pk::decode(pk::get_name(target_base)) : pk::decode(pk::get_name(pk::get_building(targetFriendly)));						
                        switch(pk::rand(3))
                        {
                            case 0: pk::say(pk::encode(pk::format("지금은 부대 존속조차 어렵다. \n인근의 \x1b[2x{}\x1b[0x(으)로 간다!", target_name)), leader); break;
                            case 1: pk::say(pk::encode(pk::format("지금은 부대 존속조차 어렵다. \n인근의 \x1b[2x{}\x1b[0x(으)로 간다!", target_name)), leader); break;
                            case 2: pk::say(pk::encode(pk::format("지금은 부대 존속조차 어렵다. \n인근의 \x1b[2x{}\x1b[0x(으)로 간다!", target_name)), leader); break;
                        }
                    }
                    
                    if (디버그모드)
                        pk::info( pk::format("{} 임무목표:{}", leader_name, target_name) );
                    
                    return true;

                }
            }
            
            return false;
        }

        //---------------------------------------------------------------------------



     // 거점병력 부족시 부대 수성 명령, 2021.01.15 일송정 수정
        bool defend_castle (pk::unit@ unit)
        {

            if (!pk::is_alive(unit)) return false;
            if (pk::is_player_controlled(unit)) return false;
            
            pk::building@ service = pk::get_building(pk::get_service(unit));
            if (!pk::is_alive(service)) return false;
            
            pk::person@ leader = pk::get_person(unit.leader);
            string leader_name = pk::decode(pk::get_name(leader));
            string target_name;
            pk::building@ target_base;
            pk::array<pk::point> arr = pk::get_movable_pos(unit);
            for (int i = 0; i < int(arr.length); i++)
            {
                pk::building@ base = pk::get_building(arr[i]);

                if (pk::is_alive(base))

                 {

                    if ((건물_도시시작 <= base.get_id() and base.get_id() < 건물_거점끝)
                        and unit.get_force_id() == base.get_force_id() 
                        and ((pk::enemies_around(base) and pk::get_troops(base) <= 8000) or ((close_combat(base) or gap_troops(base) >= 0) and enemy_approach(base) and pk::get_troops(base) <= 7000))					
                        and 450 <= base.hp and func_already_base(base) <= 1)   // 거점 내구도 심각하게 떨어진 수준이면 제외 2021.09.07 일송정 수정
                    {
                        @target_base = @base;
                        target_name = pk::decode(pk::get_name(target_base));
                        
                    }

                }

            }

            
            if (pk::is_alive(target_base))
            {
                int target_id  = target_base.get_id();
                int unit_id    = unit.get_id();
                
                // 아군 거점으로 이동
                if (arr_target_base_id[unit_id] != target_id)
                {
                    // 목표 재설정 정보 저장
                    arr_target_base_id[unit_id] = target_id;
                    // 아군 거점 이동 재설정
                    pk::set_order(unit, 부대임무_공격, target_base.pos);
                    // 목표변경 메시지
                    if (대화표시설정 and pk::is_in_screen(unit.pos))
                    {
                        switch(pk::rand(3))
                        {
                            case 0: pk::say(pk::encode(pk::format("거점을 지켜야한다.\n\x1b[2x{}\x1b[0x을(를) 지원하라", target_name)), leader); break;
                            case 1: pk::say(pk::encode(pk::format("거점을 지켜야한다.\n우리는 \x1b[2x{}\x1b[0x을(를) 지원한다", target_name)), leader); break;
                            case 2: pk::say(pk::encode(pk::format("거점을 지켜야한다.\n\x1b[2x{}\x1b[0x(으)로 향하라", target_name)), leader); break;
                        }
                    }
                    
                    if (디버그모드)
                        pk::info( pk::format("{} 임무목표:{}", leader_name, target_name) );
                    
                    return true;
                }
            }

            
            return false;
        }
             




        //---------------------------------------------------------------------------




        // ----- 전방 국경에 적의 침입으로 후퇴 (2022.06.02 일송정 추가)  

        bool front_base_retreat(pk::unit@ unit)
        {
            if (!pk::is_alive(unit)) return false;
            if (unit.type != 부대종류_전투) return false;
            if (pk::is_player_controlled(unit)) return false;
            
            int candidate_count = list_candidate_unit.count;
            if (candidate_count > 0) return false;
        
            pk::building@ service_base = pk::get_building(pk::get_service(unit));


                int unit_id    = unit.get_id();
                int service_id = service_base.get_id();

                pk::person@ leader = pk::get_person(unit.leader);
                pk::person@ Home_taishu = pk::get_person(pk::get_taishu_id(service_base));	
                int a = pk::get_person(pk::get_kunshu_id(service_base)).character;

            pk::building@ unit_base = pk::get_building(pk::get_building_id(unit.pos));
            int unit_base_id = unit_base.get_id();			
                

			// 인근 아군 거점 여부 확인.
			int targetFriendly = getAdjacentBase(unit);
			if (targetFriendly == -1) return false;

        // 전방의 다른 거점 혹은 국경에 적의 습격이 있는 거 같아 후퇴 

			// 전방 거점 여부 확인.
			int target = getFrontBase(unit);
			if (target == -1) return false;
						
      if (pk::is_alive(pk::get_building(target)) and neighbor_city_base(pk::get_building(target), service_base))
       {

             if ( 건물_도시시작 <= pk::get_building(target).get_id() and pk::get_building(target).get_id() < 건물_거점끝)
	        {

                if (service_base.get_force_id() == pk::get_building(target).get_force_id() and pk::get_building(target).get_id() != unit_base_id and neighbor_city_base(unit_base, service_base))
                 {


                    // 도시거리
                    int front_city_dist = -1;
                        front_city_dist = pk::get_city_distance(pk::get_city_id(pk::get_building(target).pos), pk::get_city_id(unit_base.pos));
                    
                    // 거점거리
                    int front_base_dist = pk::get_building_distance(pk::get_building(target).get_id(), unit_base_id, unit.get_force_id());


                        int enemy_weight = countNeighborEnemyBase(pk::get_building(target));	
                        int enemy_weight_service = countNeighborEnemyBase(service_base);


			// 부대가 있는 거점 근처에서 교전이 있거나 발생할 가능성 있으면 후퇴 안함
			if (!enemy_approach(pk::get_building(target))) return false;
			if (close_combat(unit_base)) return false;
			
            pk::district@ front_district = pk::get_district(pk::get_building(target).get_district_id());
            pk::person@ front_taishu = pk::get_person(pk::get_taishu_id(pk::get_building(target)));
			pk::person@ front_totoku = pk::get_person(front_district.totoku);		
			pk::person@ front_gunshi = pk::get_person(pk::get_force(front_district.get_force_id()).gunshi);			
	        pk::person@ front_kunshu = pk::get_person(pk::get_kunshu_id(pk::get_building(target)));	
					
// 공격당하는 전방 거점 내 장수가 태수, 도독, 군사, 군주 중 한사람만 혐오해도 작동 안함


    auto ilban_list = pk::list_to_array(pk::get_person_list(pk::get_building(target), pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반)  ) );
    {

         if (0 < ilban_list.length)
         {
                   
             for (int i = 0; i < int(ilban_list.length); i++)
             {
                pk::person@ ilban = ilban_list[i];
						
	     	    if (pk::is_alive(ilban))
	            {						
					
                   if (pk::is_alive(front_taishu))
                    {
                        if (pk::is_dislike(ilban, front_taishu.get_id()))	 
							return false;	
						
                    }					

                   if (pk::is_alive(front_totoku))
                    {
                        if (pk::is_dislike(ilban, front_totoku.get_id()))	 
							return false;													

                    }	
				
                   if (pk::is_alive(front_gunshi))
                    {
                        if (pk::is_dislike(ilban, front_gunshi.get_id()))	 
							return false;													

                    }	

                   if (pk::is_alive(front_kunshu))
                    {
                        if (pk::is_dislike(ilban, front_kunshu.get_id()))	 
							return false;													

                    }					

                }	
				
             }
         }
    }					

            auto paths = pk::get_path(unit, unit.pos, pk::get_building(target).get_pos());
            
            // 중간이동지점
            for (int i = 0; i < int(paths.length); i++)
            {
                pk::hex@ hex = pk::get_hex(paths[i]);
                pk::point pos = paths[i];

                if (hex.has_building)
                   {
                   pk::building@ base_p = pk::get_building(pk::get_building_id(paths[i]));
                   if (pk::is_enemy(base_p, unit)) return false;
                   if (pk::get_city_distance(pk::get_city_id(pk::get_building(target).pos), pk::get_city_id(base_p.pos)) > 1 and pk::get_city_distance(pk::get_city_id(unit_base.pos), pk::get_city_id(base_p.pos)) > 1) return false;			   
                   }

                if (!pk::is_enabled_terrain(hex.terrain)) return false;
                
            }

            auto paths_UnitTarget = pk::get_path(unit, unit.pos, pk::get_building(target).get_pos());
            auto paths_TargetFriendly = pk::get_path(unit, pk::get_building(target).get_pos(), pk::get_building(targetFriendly).get_pos());
					
                    // 부대가 아군 세력권 내 있는 상태면 (도시 거리 1 내)						
                    if (!pk::is_enemy(pk::get_building(target), unit_base) and no_enemy_around(unit_base) and ((0 <= front_base_dist and front_base_dist <= 1) or (0 <= front_city_dist and front_city_dist <= 1)) )
                    {

			if (enemy_approach(unit_base)) return false;
			if (close_combat(unit_base)) return false;


                        // 적지이면 적거점 공격 재설정						
                        pk::set_order(unit, 부대임무_공격, ((paths_TargetFriendly.length <= paths_UnitTarget.length) ? pk::get_building(targetFriendly).get_pos() : pk::get_building(target).get_pos() ) );
                        // 목표변경 메시지
                        if (대화표시설정 and pk::is_in_screen(unit.pos))
                        {
                            string front_base_name = pk::decode(pk::get_name(pk::get_building(target)));
                            string target_name = ((paths_TargetFriendly.length <= paths_UnitTarget.length) ? pk::decode(pk::get_name(pk::get_building(targetFriendly))) : pk::decode(pk::get_name(pk::get_building(target))) );
                            switch(pk::rand(3))
                            {
                                case 0: pk::say(pk::encode(pk::format("가까운 \x1b[1x{}\x1b[0x에 침입이 발생했다.\n\x1b[2x{}\x1b[0x(으)로 가자!", front_base_name, target_name)), leader); break;
                                case 1: pk::say(pk::encode(pk::format("가까운 \x1b[1x{}\x1b[0x에 침입이 발생했다.\n\x1b[2x{}\x1b[0x(으)로 가자!", front_base_name, target_name)), leader); break;
                                case 2: pk::say(pk::encode(pk::format("가까운 \x1b[1x{}\x1b[0x에 침입이 발생했다.\n\x1b[2x{}\x1b[0x(으)로 가자!", front_base_name, target_name)), leader); break;
                            }
                        }


                        return true;     
                    }


                    // 부대가 아군 세력권 내 있는 상태면 (도시 거리 2)
                    if (!pk::is_enemy(pk::get_building(target), unit_base) and no_enemy_around(unit_base) and front_city_dist == 2 )
                    {

			if (enemy_approach(unit_base)) return false;
			if (close_combat(unit_base)) return false;


                        // 적지이면 적거점 공격 재설정						
                        pk::set_order(unit, 부대임무_공격, ((paths_TargetFriendly.length <= paths_UnitTarget.length) ? pk::get_building(targetFriendly).get_pos() : pk::get_building(target).get_pos() ) );
                        // 목표변경 메시지
                        if (대화표시설정 and pk::is_in_screen(unit.pos))
                        {
                            string front_base_name = pk::decode(pk::get_name(pk::get_building(target)));							
                            string target_name = ((paths_TargetFriendly.length <= paths_UnitTarget.length) ? pk::decode(pk::get_name(pk::get_building(targetFriendly))) : pk::decode(pk::get_name(pk::get_building(target))) );
                            switch(pk::rand(3))
                            {
                                case 0: pk::say(pk::encode(pk::format("멀리 \x1b[1x{}\x1b[0x에 침입이 발생했다.\n\x1b[2x{}\x1b[0x(으)로 가자!", front_base_name, target_name)), leader); break;
                                case 1: pk::say(pk::encode(pk::format("멀리 \x1b[1x{}\x1b[0x에 침입이 발생했다.\n\x1b[2x{}\x1b[0x(으)로 가자!", front_base_name, target_name)), leader); break;
                                case 2: pk::say(pk::encode(pk::format("멀리 \x1b[1x{}\x1b[0x에 침입이 발생했다.\n\x1b[2x{}\x1b[0x(으)로 가자!", front_base_name, target_name)), leader); break;
                            }
                        }
                        return true;     
                    }


                    // 부대가 적 세력권에 있는 상태면
                    if (pk::is_enemy(pk::get_building(target), unit_base) and 0 <= front_city_dist and front_city_dist <= 2 and unit.target != pk::get_building(target).get_id() and 450 <= unit_base.hp and 8000 <= pk::get_troops(unit_base) and gap_troops(unit_base) <= pk::get_troops(unit_base) * 3 )
                    {

                        // 적지이면 적거점 공격 재설정						
                        pk::set_order(unit, 부대임무_공격, ((paths_TargetFriendly.length <= paths_UnitTarget.length) ? pk::get_building(targetFriendly).get_pos() : pk::get_building(target).get_pos() ) );
                        // 목표변경 메시지
                        if (대화표시설정 and pk::is_in_screen(unit.pos))
                        {
                            string front_base_name = pk::decode(pk::get_name(pk::get_building(target)));							
                            string target_name = ((paths_TargetFriendly.length <= paths_UnitTarget.length) ? pk::decode(pk::get_name(pk::get_building(targetFriendly))) : pk::decode(pk::get_name(pk::get_building(target))) );
                            switch(pk::rand(3))
                            {
                                case 0: pk::say(pk::encode(pk::format("하필 공격 중에 \x1b[1x{}\x1b[0x에 침입이?\n\x1b[2x{}\x1b[0x(으)로 가자!", front_base_name, target_name)), leader); break;
                                case 1: pk::say(pk::encode(pk::format("하필 공격 중에 \x1b[1x{}\x1b[0x에 침입이?\n\x1b[2x{}\x1b[0x(으)로 가자!", front_base_name, target_name)), leader); break;
                                case 2: pk::say(pk::encode(pk::format("하필 공격 중에 \x1b[1x{}\x1b[0x에 침입이?\n\x1b[2x{}\x1b[0x(으)로 가자!", front_base_name, target_name)), leader); break;
                            }
                        }
                        return true;     
                    }
            


           }

        }

      }


		
            return false;            
        }



        //---------------------------------------------------------------------------
        
		/** 위기의 전방 거점 찾기 */


        pk::unit@ unit_Front;
		int getFrontBase(pk::unit@ unit)
		{
			int best_dst = -1;
			int best_distance = 0;


            int unit_id = unit.get_id();
            pk::list<pk::building@> dst_list; 
            @unit_Front = @unit;
																              
            pk::force@ force = pk::get_force(unit.get_force_id());
            
  for (int f = 0; f < 건물_거점끝; f++)
   {

                    pk::building@ front_base = pk::get_building(f);																				 																				 
            pk::building@ service_base = pk::get_building(pk::get_service(unit));
			
                int unit_id    = unit.get_id();
                int service_id = service_base.get_id();
                int front_base_id = front_base.get_id();	
            pk::building@ unit_base = pk::get_building(pk::get_building_id(unit.pos));
            int unit_base_id = unit_base.get_id();				

                pk::person@ Home_taishu = pk::get_person(pk::get_taishu_id(service_base));	
                int a = pk::get_person(pk::get_kunshu_id(service_base)).character;				

      if (pk::is_alive(front_base) and pk::is_alive(service_base) and neighbor_city_base(front_base, service_base))
       {

             if ( 건물_도시시작 <= front_base.get_id() and front_base.get_id() < 건물_거점끝)
	{

                if (service_base.get_force_id() == front_base.get_force_id() and front_base_id != unit_base_id and neighbor_city_base(unit_base, service_base))
                 {            



                    // 도시거리
                    int front_city_dist = -1;
                        front_city_dist = pk::get_city_distance(pk::get_city_id(front_base.pos), pk::get_city_id(unit_base.pos));
                    
                    // 거점거리
                    int front_base_dist = pk::get_building_distance(front_base_id, unit_base_id, front_base.get_force_id());


                        int enemy_weight = countNeighborEnemyBase(front_base);	
                        int enemy_weight_service = countNeighborEnemyBase(service_base);

                    
		/** 적의 거점으로부터 떨어진 후방거점들 */


            if (11 <= pk::get_distance(front_base.pos, unit.pos) and enemy_approach(front_base) and ((front_base_id < 건물_도시끝 and troops_already(front_base) + (( a - 1 ) * 6000) <= gap_troops(front_base)) or (front_base_id >= 건물_도시끝 and troops_already(front_base) + (Friendly_base(front_base) * 0.5f) <= gap_troops(front_base))) and 450 <= front_base.hp and 0 < enemy_weight )
                   {

					
                    if ((0 <= front_base_dist and front_base_dist <= 1) or (0 <= front_city_dist and front_city_dist <= 2) )
                       {
                           best_dst = front_base_id;
                           dst_list.add(front_base);  // 전방 리스트 추가
                        }


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
            pk::building@ unit_base = pk::get_building(pk::get_building_id(main.unit_Front.pos));
            int unit_base_id = unit_base.get_id();

                    int build_dist_a = pk::get_building_distance(a.get_id(), unit_base.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), unit_base.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.unit_Front.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.unit_Front.pos);

                    if (build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);
                    
                    return (pos_dist_a < pos_dist_b);

                   return (main.gap_troops(a) - main.troops_already(a) > main.gap_troops(b) - main.troops_already(b));	
                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
		}


        //---------------------------------------------------------------------------


        // ----- 전체 판도로 인한 후퇴 (2022.06. 일송정 추가)  

        bool retreat_unit(pk::unit@ unit)
        {
            if (!pk::is_alive(unit)) return false;
            if (unit.type != 부대종류_전투) return false;
            if (pk::is_player_controlled(unit)) return false;
            
            int candidate_count = list_candidate_unit.count;
            if (candidate_count > 0) return false;
        
          for (int i = 0; i < 건물_거점끝; i++)
          {
            pk::building@ target_base = pk::get_building(i);  
		
            pk::building@ service_base = pk::get_building(pk::get_service(unit));

            if (pk::is_alive(service_base) and pk::is_alive(target_base))
            {
                int unit_id    = unit.get_id();
                int service_id = service_base.get_id();
                int target_id  = target_base.get_id();
                pk::person@ leader = pk::get_person(unit.leader);
                pk::person@ Home_taishu = pk::get_person(pk::get_taishu_id(service_base));	
                int a = pk::get_person(pk::get_kunshu_id(service_base)).character;

            pk::building@ unit_base = pk::get_building(pk::get_building_id(unit.pos));
            int unit_base_id = unit_base.get_id();			
                
                // 거점으로 계속 공격

                    // 도시거리
                    int city_dist = -1;
                        city_dist = pk::get_city_distance(pk::get_city_id(target_base.pos), pk::get_city_id(service_base.pos));
                    
                    // 거점거리
                    int base_dist = pk::get_building_distance(target_id, service_id, service_base.get_force_id());
                    
                    // 거리 조건 만족 시
                    if ( (0 <= base_dist and base_dist <= 2) or city_dist == 1)
                    {
									

			// 인근 아군 거점 여부 확인.
			int targetFriendly = getAdjacentBase(unit);
			if (targetFriendly == -1) return false;


        // 적의 전력에 밀려 후퇴 

                    if (pk::is_enemy(target_base, unit) and pk::get_troops (target_base) >= 8000 and target_base.hp >= 1900 and 0 >= gap_troops(target_base) + (pk::get_troops (target_base) * 0.5) + ((a + 1) * 7000) + (pk::get_troops (service_base) * 0.7) and pk::get_distance(target_base.get_pos(), unit.pos) <= 7 and jam_f_units_around(unit) <= 3)
                    {
                        // 목표 재설정 정보 저장
                        arr_target_base_id[unit_id] = target_id;
                        // 적지이면 적거점 공격 재설정
                        pk::set_order(unit, 부대임무_공격, pk::get_building(targetFriendly).get_pos());
                        // 목표변경 메시지
                        if (대화표시설정 and pk::is_in_screen(unit.pos))
                        {
			    string target_base_name = pk::decode(pk::get_name(target_base));							
                            string target_name = pk::decode(pk::get_name(pk::get_building(targetFriendly)));
                            switch(pk::rand(3))
                            {
                                case 0: pk::say(pk::encode(pk::format("\x1b[1x{}\x1b[0x의 전황이 불리하다.\n\x1b[2x{}\x1b[0x(으)로 후퇴하라!", target_base_name, target_name)), leader); break;
                                case 1: pk::say(pk::encode(pk::format("\x1b[1x{}\x1b[0x의 전황이 불리하다.\n우리는 \x1b[2x{}\x1b[0x(으)로 후퇴한다!", target_base_name, target_name)), leader); break;
                                case 2: pk::say(pk::encode(pk::format("\x1b[1x{}\x1b[0x의 전황이 불리하다.\n\x1b[2x{}\x1b[0x(으)로 돌아가자!", target_base_name, target_name)), leader); break;
                            }
                        }
                        return true;     
                    }



                }
            }
			
          }			
            return false;            
        }


        //---------------------------------------------------------------------------


        // 전투 지역 내 적과 아군 병력 격차 (2022.06. 일송정 추가)//
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


			auto range = pk::range(dst.get_pos(), 1, 11 + (dst.facility == 시설_도시 ? 1 : 0));
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



        //---------------------------------------------------------------------------

        // ***** 주변 아군 거점 병력 수 확인 (2022.06. 일송정 추가)***** //
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

			auto range = pk::range(base.get_pos(), 1, 11 + (base.facility == 시설_도시 ? 1 : 0));
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



        //---------------------------------------------------------------------------
        
        // 공격 가능한 적부대 검색함수
        void get_list_candidate_unit(pk::unit@ unit)
        {
            // 리스트 초기화
            if (!pk::is_alive(unit)) return;
            list_candidate_unit.clear();
            
            int weapon_id = unit.weapon;
            int weapon_type = get_weapon_type(weapon_id);   // 0:검, 1:전투, 2:충차, 3:공성기타, 4:수군
            
            // 충차는 검색대상에서 제외
            if (weapon_id == 병기_충차) return;   
            // 목수/정란/투석 검색대상에서 제외여부
            if (!공성병기_부대전투_참여설정 and weapon_type == 3) return;
            if ( 공성병기_부대전투_참여설정 and weapon_type == 3 and (unit.energy < 공성병기_부대전투_기준기력)) return;
            
            // 공격 사거리 설정 --- 함수 변경 ('20.9.13)
            pk::int_int atk_range = get_atk_range(unit);
            int min = (weapon_id == 병기_충차)? 0 : atk_range.first;
            int max = (weapon_id == 병기_충차)? 0 : atk_range.second;
            
            pk::array<pk::point> range = pk::get_movable_pos(unit);  // 이동가능좌표
            for (int i = 0; i < int(range.length); i++)
			{
                pk::point pos = range[i];
                pk::hex@ hex = pk::get_hex(pos);
                pk::array<pk::point> arr_t = pk::range(pos, min, max);   // 주변좌표
                for (int j = 0; j < int(arr_t.length); j++)
                {
                    pk::unit@ target_unit = pk::get_unit(arr_t[j]);
                    if (!hex.has_building and !hex.has_unit and pk::is_alive(target_unit) 
                        and pk::is_enemy(unit, target_unit) and !list_candidate_unit.contains(target_unit))
                    {
                        list_candidate_unit.add(target_unit);   // 적부대 공격 가능 시 리스트 추가
                    }
                }
			}
        }
        
        // 부대임무가 자세력 거점으로 이동인 경우, 거점주변에 적부대 있는지 추가 확인
        void search_enemy_on_reinforce_engage(pk::unit@ unit)
        {
            if (!pk::is_alive(unit)) return;
            if (list_candidate_unit.count > 0) return;
            if (unit.type != 부대종류_전투) return;
            if (unit.weapon > 병기_군마) return;
            
            pk::building@ service_base = pk::get_building(pk::get_service(unit));
            if (!pk::is_alive(service_base)) return;
            
            pk::building@ base_p = pk::get_building(pk::get_building_id(unit.pos));
            if (!pk::is_alive(base_p)) return;
            
            int service_id = service_base.get_id();
            int base_p_id = base_p.get_id();
            if (base_p_id == service_id or unit.get_force_id() != base_p.get_force_id()) return;    // 소속거점 영토이거나 타세력 영토인 경우
            
            if (unit.target_type == 부대임무대상_거점)
            {
                pk::building@ base_t = pk::get_building(unit.target);
                if (pk::is_alive(base_t))
                {
                    int base_t_id = base_t.get_id();
                    // 목표거점과 부대좌표거점이 같거나, 부대 이동거리 내에 목표거점이 존재하는 경우
                    if (base_t_id < 건물_거점끝 and (base_t_id == base_p_id or check_base_in_movable_range(unit, base_t)))
                    {
                        pk::array<pk::point> range = pk::range(base_p.pos, 1, 12);  // 거점 주변 검색
                        for (int i = 0; i < int(range.length); i++)
                        {
                            pk::point pos_i = range[i];
                            pk::unit@ unit_i = pk::get_unit(pos_i);
                            if (pk::is_alive(unit_i) and pk::get_building_id(pos_i) == base_p_id
                                and pk::is_enemy(unit, unit_i) and !list_candidate_unit.contains(unit_i))
                            {
                                list_candidate_unit.add(unit_i);   // 적부대 공격 가능 시 리스트 추가
                            }
                        }
                    }
                }
            }
        }
        
        
        // 공격목표부대 변경 함수
        void func_change_target_unit(pk::unit@ unit)
        {
            if (!pk::is_alive(unit)) return;
            
            @src_unit = @unit;
            int target_count = list_candidate_unit.count;   // 후보 부대수
            if (target_count == 0) return;

            // 병과종류
            int weapon_id = src_unit.weapon;
            int weapon_type = get_weapon_type(weapon_id);   // 0:검, 1:전투, 2:충차, 3:공성기타, 4:수군

            // 임무변경 대상부대
            bool combat_update = false;
            if      (weapon_type == 1 or weapon_type >= 4) combat_update = true;
            else if (weapon_type == 3 and 공성병기_부대전투_참여설정 and (unit.energy >= 공성병기_부대전투_기준기력)) combat_update = true;
            else combat_update = false;
            
            if (combat_update)
            {
                // 병종상성 설정
                set_heishu_weight(weapon_id);
                
                // 병종상성, 적성, 방어력 가중치 적용한 목표부대 능력치 정렬
                list_candidate_unit.sort(function(a, b)
                {
                    float stat_a = main.get_attr_weight(a);
                    float stat_b = main.get_attr_weight(b);
                    return (stat_a > stat_b);
                });
                
                // 목표부대 설정
                pk::array<pk::unit@> arr_candidate_unit = pk::list_to_array(list_candidate_unit);
                @dst_unit_new = arr_candidate_unit[0];
                
                // 개발자 디버깅용 로그 출력
                if (디버그모드)
                {
                    string src_name = (pk::is_alive(unit))?         pk::decode(pk::get_name(pk::get_person(unit.leader)))+"대"         : "확인불가" ;
                    string dst_name = (pk::is_alive(dst_unit_new))? pk::decode(pk::get_name(pk::get_person(dst_unit_new.leader)))+"대" : "확인불가" ;
                    pk::info( pk::format("{} 임무목표:{}", src_name, dst_name) );
                }
                
                if (pk::is_alive(dst_unit_new))
                {
                    int src_id = src_unit.get_id();
                    int dst_id = dst_unit_new.get_id();
                    
                    // 새 목표부대로 변경된 경우 공격임무 재설정
                    if (arr_target_unit_id[src_id] != dst_id)
                    {
                        // 목표 재설정 정보 저장
                        arr_target_unit_id[src_id] = dst_id;
                        arr_target_base_id[src_id] = -1;
                        
                        // 공격임무 재설정
                        int old_order = src_unit.order;
                        if (old_order == 부대임무_물림 or old_order == 부대임무_섬멸)
                            pk::set_order(src_unit, old_order, dst_unit_new.pos);
                        else
                            pk::set_order(src_unit, 부대임무_공격, dst_unit_new.pos);
                        
                        // 부대임무변경 대화 표시
                        if (대화표시설정 and pk::is_in_screen(src_unit.pos))  
                            say_change_target_unit();
                    }
                }
            }
        }

        
        void say_change_target_unit()
        {
            string str_f0 = pk::decode(pk::get_name(pk::get_force(src_unit.get_force_id())));
            string str_p0 = pk::decode(pk::get_name(pk::get_person(src_unit.leader)));
            string str_w0 = get_weapon_name(src_unit.weapon);
            string str_t0 = get_tekisei_name(pk::get_tekisei(src_unit));
            //string str_f1 = pk::decode(pk::get_name(pk::get_force(dst_unit_old.get_force_id())));
            //string str_p1 = pk::decode(pk::get_name(pk::get_person(dst_unit_old.leader)));
            //string str_w1 = get_weapon_name(dst_unit_old.weapon);
            //string str_t1 = get_tekisei_name(pk::get_tekisei(dst_unit_old));
            string str_f2 = pk::decode(pk::get_name(pk::get_force(dst_unit_new.get_force_id())));
            string str_p2 = pk::decode(pk::get_name(pk::get_person(dst_unit_new.leader)));
            string str_w2 = get_weapon_name(dst_unit_new.weapon);
            string str_t2 = get_tekisei_name(pk::get_tekisei(dst_unit_new));
            string str_color = get_heishu_color(dst_unit_new.weapon);
            
            string str_line0 = pk::format("\x1b[2x{}군 \x1b[1x{}대 \x1b[17x{}{}\x1b[0x 임무변경!!", str_f0, str_p0, str_w0, str_t0);
            string str_line1 = pk::format("→ \x1b[2x{}군 \x1b[1x{}대 {}{}{}\x1b[0x 공격", str_f2, str_p2, str_color, str_w2, str_t2);
            
            pk::person@ leader = pk::get_person(src_unit.leader);
            pk::say(pk::encode(pk::format("{}\n{}", str_line0, str_line1)), leader);
        }
        
        //---------------------------------------------------------------------------
        //---------------------------------------------------------------------------



        // ----- 적거점_계속공격허용 (2021.09.18 일송정 추가)  

        bool keep_atk_enemy_base_nearby(pk::unit@ unit)
        {
            if (!pk::is_alive(unit)) return false;
            if (unit.type != 부대종류_전투) return false;
            if (pk::is_player_controlled(unit)) return false;
            
            int candidate_count = list_candidate_unit.count;
            if (candidate_count > 0) return false;

			// 전방 거점 여부 확인.
			int target = getEnemyBase(unit);
			if (target == -1) return false;        
		
            pk::building@ service_base = pk::get_building(pk::get_service(unit));

            if (pk::is_alive(service_base) and pk::is_alive(pk::get_building(target)) and pk::get_elapsed_months() > 3)
            {
                int unit_id    = unit.get_id();
                int service_id = service_base.get_id();
                int target_id  = pk::get_building(target).get_id();
                pk::person@ leader = pk::get_person(unit.leader);
                pk::person@ Home_taishu = pk::get_person(pk::get_taishu_id(service_base));
            pk::force@ unit_force = pk::get_force(unit.get_force_id());				

            pk::building@ unit_base = pk::get_building(pk::get_building_id(unit.pos));
            int unit_base_id = unit_base.get_id();
			
                // 거점으로 계속 공격

                    // 도시거리
                    int city_dist = -1;
                        city_dist = pk::get_city_distance(pk::get_city_id(pk::get_building(target).pos), pk::get_city_id(service_base.pos));
                    
                    // 거점거리
                    int base_dist = pk::get_building_distance(target_id, service_id, service_base.get_force_id());
                   
                    // 거리 조건 만족 시
                    if ( service_id != pk::get_building(target).get_id() and (0 <= base_dist and base_dist <= 2) or city_dist == 1)
                    {



        //  계속 공격					
             int a = pk::get_person(pk::get_kunshu_id(service_base)).character;
                        int enemy_weight_target = countNeighborEnemyBase(pk::get_building(target));
						
                    if (enemy_approach(service_base)) return false;
					
			if (close_combat(service_base)) return false;
			if (friendlies_around_base(unit_force, pk::get_building(target), 5) >= 7 ) return false;
			
            auto paths = pk::get_path(unit, unit.pos, pk::get_building(target).get_pos());
            
            // 중간이동지점
            for (int i = 0; i < int(paths.length); i++)
            {
                pk::hex@ hex = pk::get_hex(paths[i]);
                pk::point pos = paths[i];

                if (hex.has_building)
                   {
                   pk::building@ base_p = pk::get_building(pk::get_building_id(paths[i]));
                   if (pk::is_enemy(base_p, unit)) return false;
                   }

                if (!pk::is_enabled_terrain(hex.terrain)) return false;
                
            }

                        // 목표 재설정 정보 저장
                        arr_target_base_id[unit_id] = target_id;
                        // 적지이면 적거점 공격 재설정
                        pk::set_order(unit, 부대임무_공격, pk::get_building(target).get_pos());
                        // 목표변경 메시지
                        if (대화표시설정 and pk::is_in_screen(unit.pos))
                        {
                            string target_name = pk::decode(pk::get_name(pk::get_building(target)));
                            switch(pk::rand(3))
                            {
                                case 0: pk::say(pk::encode(pk::format("진격!승산은 충분하다!\n\x1b[2x{}\x1b[0x을(를) 공략하라", target_name)), leader); break;
                                case 1: pk::say(pk::encode(pk::format("진격!승산은 충분하다!\n우리는 \x1b[2x{}\x1b[0x을(를) 공격한다", target_name)), leader); break;
                                case 2: pk::say(pk::encode(pk::format("진격!승산은 충분하다!\n\x1b[2x{}\x1b[0x(으)로 향하라", target_name)), leader); break;
                            }
                        }
                    																		
                        return true;     

                }
            }
					
            return false;            
        }




        
		/** 진격할만한 적의 거점 찾기 (2022.06. 일송정 추가) */


        pk::unit@ unit_e;
		int getEnemyBase(pk::unit@ unit)
		{
			int best_dst = -1;
			int best_distance = 0;


            int unit_id = unit.get_id();
            pk::list<pk::building@> dst_list; 
            @unit_e = @unit;
																              
            pk::force@ force = pk::get_force(unit.get_force_id());
            
          for (int i = 0; i < 건물_거점끝; i++)
          {
            pk::building@ target_base = pk::get_building(i);  
		
            pk::building@ service_base = pk::get_building(pk::get_service(unit));

            if (pk::is_alive(service_base) and pk::is_alive(target_base))
            {
                int unit_id    = unit.get_id();
                int service_id = service_base.get_id();
                int target_id  = target_base.get_id();
                pk::person@ leader = pk::get_person(unit.leader);
                pk::person@ Home_taishu = pk::get_person(pk::get_taishu_id(service_base));				

            pk::building@ unit_base = pk::get_building(pk::get_building_id(unit.pos));
            int unit_base_id = unit_base.get_id();
			
                // 거점으로 계속 공격

                    // 도시거리
                    int city_dist = -1;
                        city_dist = pk::get_city_distance(pk::get_city_id(target_base.pos), pk::get_city_id(service_base.pos));
                    
                    // 거점거리
                    int base_dist = pk::get_building_distance(target_id, service_id, service_base.get_force_id());
                    
                    // 거리 조건 만족 시
                    if ( service_id != target_id and (0 <= base_dist and base_dist <= 2) or city_dist == 1)
                    {

        //  계속 공격					
             int a = pk::get_person(pk::get_kunshu_id(service_base)).character;
                        int enemy_weight_target = countNeighborEnemyBase(target_base);
                    if (pk::is_enemy(target_base, unit) and 0 < enemy_weight_target)
                    {						
						
                    if ((pk::get_troops (target_base) < 5000 or target_base.hp < 500 or ((3 - a) * 5000) < gap_troops(target_base) ) and 0 >= gap_troops(service_base) + ((6 - a) * 6000) and unit.troops >= 3000 and unit.food >= unit.troops * 0.7 )
                        {
                        if (unit.get_force_id() == unit_base.get_force_id() and 8 <= pk::get_distance(target_base.get_pos(), unit.pos) and pk::get_distance(target_base.get_pos(), unit.pos) <= 20)	
                           {								
                           best_dst = target_id;
                           dst_list.add(target_base);  // 전방 리스트 추가
	                       }					   
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

            pk::building@ unit_base = pk::get_building(pk::get_building_id(main.unit_e.pos));
            int unit_base_id = unit_base.get_id();

                    int build_dist_a = pk::get_building_distance(a.get_id(), unit_base.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), unit_base.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.unit_e.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.unit_e.pos);

                    if (build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);
                    
                    return (pos_dist_a < pos_dist_b);

                    return (pk::get_max_troops(a) - pk::get_troops(a) > pk::get_max_troops(b) - pk::get_troops(b));
                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
		}









        
		/** 인근 적의 다른 항구 찾기 (2022.06. 일송정 추가) */


        pk::unit@ unit_P;
		int getEnemyPort(pk::unit@ unit)
		{
			int best_dst = -1;
			int best_distance = 0;


            int unit_id = unit.get_id();
            pk::list<pk::building@> dst_list; 
            @unit_P = @unit;
																              
            pk::force@ force = pk::get_force(unit.get_force_id());
            pk::building@ unit_base = pk::get_building(pk::get_building_id(unit.pos));
            int unit_base_id = unit_base.get_id();
            
  for (int f = 0; f < 건물_거점끝; f++)
   {

                pk::building@ adjacent_base = pk::get_building(f);																				 																				 
                int adjacent_base_id = adjacent_base.get_id();	
				


                if (unit_base_id != adjacent_base_id and 건물_항구시작 <= adjacent_base_id and adjacent_base_id < 건물_거점끝)
                 {            


					                      
		/** 적의 거점으로부터 떨어진 후방거점들 */


                    if (pk::is_enemy(adjacent_base, unit) and !pk::enemies_around(adjacent_base) and 2 >= pk::get_building_distance(unit_base_id, adjacent_base_id, unit.get_force_id()))
                       {
                           best_dst = adjacent_base_id;
                           dst_list.add(adjacent_base);  // 전방 리스트 추가
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

            pk::building@ unit_base = pk::get_building(pk::get_building_id(main.unit_P.pos));
            int unit_base_id = unit_base.get_id();

                    int build_dist_a = pk::get_building_distance(a.get_id(), unit_base.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), unit_base.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.unit_P.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.unit_P.pos);

                    if (build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);
                    
                    return (pos_dist_a < pos_dist_b);

                    return (pk::get_max_troops(a) - pk::get_troops(a) > pk::get_max_troops(b) - pk::get_troops(b));
                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
		}















        // ***** 두 거점이 이웃하다 할만 한지 (2022.06. 일송정 추가)***** //
        bool neighbor_city_base(pk::building@ building, pk::building@ building2)
        {
                if (pk::get_city_id(building.pos) == pk::get_city_id(building2.pos) or pk::get_city_distance(pk::get_city_id(building.pos), pk::get_city_id(building2.pos)) == 1 or building.get_district_id() == building2.get_district_id())
	 return true;

	 return false;
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


        //---------------------------------------------------------------------------
        
        // ----- 적거점_점령허용  
        // 공격부대 : 현재 좌표구역의 거점 세력 확인 : true=원정 또는 원군 / false=요격 판단
        bool atk_enemy_base_nearby(pk::unit@ unit)
        {
            if (!pk::is_alive(unit)) return false;
            if (unit.type != 부대종류_전투) return false;
            
            int candidate_count = list_candidate_unit.count;
            if (candidate_count > 4) return false;
            
            pk::building@ service_base = pk::get_building(pk::get_service(unit));
            pk::building@ target_base = pk::get_building(pk::get_building_id(unit.pos));
            if (pk::is_alive(service_base) and pk::is_alive(target_base))
            {
                int unit_id    = unit.get_id();
                int service_id = service_base.get_id();
                int target_id  = target_base.get_id();
                pk::person@ leader = pk::get_person(unit.leader);
                
                // 적 거점 공략 (근접 교전 이후 주변에 부대 없을 시에만 동작, 최초 출진 시에는 미동작)
                bool is_enemy_base = pk::is_enemy(unit, target_base);
                bool is_candidate_base = (candidate_count == 0 or (is_weak_base(target_base) and candidate_count > 0));
                if (is_enemy_base and is_candidate_base and (arr_target_base_id[unit_id] != target_id and arr_target_unit_id[unit_id] != -1) )
                {
                    if ((적거점_점령성격적용 and (leader.character == 성격_대담 or leader.character == 성격_저돌)) or !적거점_점령성격적용)
                    {
                        // 목표 재설정 정보 저장
                        arr_target_base_id[unit_id] = target_id;
                        // 적지이면 적거점 공격 재설정
                        pk::set_order(unit, 부대임무_공격, target_base.pos);
                        // 목표변경 메시지
                        if (대화표시설정 and pk::is_in_screen(unit.pos))
                        {
                            string target_name = pk::decode(pk::get_name(target_base));
                            switch(pk::rand(3))
                            {
                                case 0: pk::say(pk::encode(pk::format("\x1b[2x{}\x1b[0x을(를) 공략하라", target_name)), leader); break;
                                case 1: pk::say(pk::encode(pk::format("우리는 \x1b[2x{}\x1b[0x을(를) 공격한다", target_name)), leader); break;
                                case 2: pk::say(pk::encode(pk::format("\x1b[2x{}\x1b[0x(으)로 향하라", target_name)), leader); break;
                            }
                        }
                        return true;     
                    }
                }
            }
            return false;            
        }
        
        
        //---------------------------------------------------------------------------      


        
        // ----- 적의 취약거점 무조건 공격
        // 공격부대 : 현재 좌표구역의 거점 세력 확인 : true=원정 또는 원군 / false=요격 판단
        bool no_holds_barred(pk::unit@ unit)
        {
            if (!pk::is_alive(unit)) return false;
            if (unit.type != 부대종류_전투) return false;
            if (pk::is_player_controlled(unit)) return false;			
                        
            pk::building@ service_base = pk::get_building(pk::get_service(unit));
            pk::building@ unit_base = pk::get_building(pk::get_building_id(unit.pos));
            if (pk::is_alive(service_base) and pk::is_alive(unit_base))
            {
                int unit_id    = unit.get_id();
                int service_id = service_base.get_id();
                int unit_base_id  = unit_base.get_id();
                pk::person@ leader = pk::get_person(unit.leader);
                				
	
                // 적 거점 공략 (적 거점이 1천 이하 혹은 약해보이면 무조건 공격), 2021.01.15 일송정 수정
          for (int i = 0; i < 건물_거점끝; i++)
          {
            pk::building@ enemy_base = pk::get_building(i); 
			int enemy_base_id  = enemy_base.get_id();
                if (pk::get_distance(enemy_base.get_pos(), unit.pos) <= 7 and pk::is_enemy(unit, enemy_base) )
                {
					
            auto paths = pk::get_path(unit, unit.pos, enemy_base.get_pos());
            
            // 중간이동지점
            for (int i = 0; i < int(paths.length); i++)
            {
                pk::hex@ hex = pk::get_hex(paths[i]);
                pk::point pos = paths[i];

                if (hex.has_building)
                   {
                   pk::building@ base_p = pk::get_building(pk::get_building_id(paths[i]));
                   if (pk::is_enemy(base_p, unit)) return false;
                   }

                if (!pk::is_enabled_terrain(hex.terrain)) return false;
                
            }					
					
                    pk::person@ leader = pk::get_person(unit.leader);
                    if (((pk::get_troops (enemy_base) < 3000 or enemy_base.hp < 500) or (pk::get_troops (enemy_base) < unit.troops * 0.7 and unit.troops > 3000)) and func_already (enemy_base) <= 4 )
                    {

																
                        // 적지이면 적거점 공격 재설정
                        pk::set_order(unit, 부대임무_공격, enemy_base.pos);
                        // 목표변경 메시지
                        if (대화표시설정 and pk::is_in_screen(unit.pos))
                        {
                            string target_name = pk::decode(pk::get_name(enemy_base));
                            switch(pk::rand(3))
                            {
                                case 0: pk::say(pk::encode(pk::format("진격! 적의 거점이 풍전등화구나!\n\x1b[2x{}\x1b[0x을(를) 공략하라", target_name)), leader); break;
                                case 1: pk::say(pk::encode(pk::format("진격! 적의 거점이 풍전등화구나!\n우리는 \x1b[2x{}\x1b[0x을(를) 공격한다", target_name)), leader); break;
                                case 2: pk::say(pk::encode(pk::format("진격! 적의 거점이 풍전등화구나!\n\x1b[2x{}\x1b[0x(으)로 향하라", target_name)), leader); break;
                            }
                        }
                        
                         return true;    
                    }

                  }	
             }


				
            }
            return false;            
        }
        



        //---------------------------------------------------------------------------      


        
        // ----- 공백지 무조건 공격
        // 공격부대 : 현재 좌표구역의 거점 세력 확인 : true=원정 또는 원군 / false=요격 판단
        bool attack_empty_base(pk::unit@ unit)
        {
            if (!pk::is_alive(unit)) return false;
            if (unit.type != 부대종류_전투) return false;
            if (pk::is_player_controlled(unit)) return false;			
                        
            pk::building@ service_base = pk::get_building(pk::get_service(unit));
            pk::building@ unit_base = pk::get_building(pk::get_building_id(unit.pos));
            if (pk::is_alive(service_base) and pk::is_alive(unit_base))
            {
                int unit_id    = unit.get_id();
                int service_id = service_base.get_id();
                int unit_base_id  = unit_base.get_id();
                pk::person@ leader = pk::get_person(unit.leader);

            pk::building@ unit_target_base = pk::get_building(unit.target);
            if (pk::is_alive(unit_target_base) and unit_target_base.get_force_id() == -1 and pk::get_troops(unit_target_base) == 0 and unit_target_base.get_id() < 건물_도시끝) return false;   

			// 전방 거점 여부 확인.
			int target = get_empty_base(unit);
			if (target == -1) return false;         				

            auto paths = pk::get_path(unit, unit.pos, pk::get_building(target).pos);
            
            // 중간이동지점
            for (int i = 0; i < int(paths.length); i++)
            {
                pk::hex@ hex = pk::get_hex(paths[i]);
                pk::point pos = paths[i];

                if (hex.has_building)
                   {
                   pk::building@ base_p = pk::get_building(pk::get_building_id(paths[i]));
                   if (pk::is_enemy(base_p, unit)) return false;
                   }

                if (!pk::is_enabled_terrain(hex.terrain)) return false;
                
            }
																
                        // 적지이면 적거점 공격 재설정
                        pk::set_order(unit, 부대임무_공격, pk::get_building(target).pos);
                        // 목표변경 메시지
                        if (대화표시설정 and pk::is_in_screen(unit.pos))
                        {
                            string target_name = pk::decode(pk::get_name(pk::get_building(target)));
                            switch(pk::rand(3))
                            {
                                case 0: pk::say(pk::encode(pk::format("\x1b[2x{}\x1b[0x을(를) 공략하라!\n공백지다!", target_name)), leader); break;
                                case 1: pk::say(pk::encode(pk::format("우리는 \x1b[2x{}\x1b[0x을(를) 공격한다!\n공백지다!", target_name)), leader); break;
                                case 2: pk::say(pk::encode(pk::format("\x1b[2x{}\x1b[0x(으)로 향하라!\n공백지다!", target_name)), leader); break;
                            }
                        }
                        
                         return true;    


				
            }
            return false;            
        }

       
		/** 진격할만한 적의 거점 찾기 (2022.06. 일송정 추가) */


        pk::unit@ unit_empty_base;
		int get_empty_base(pk::unit@ unit)
		{
			int best_dst = -1;
			int best_distance = 0;


            int unit_id = unit.get_id();
            pk::list<pk::building@> dst_list; 
            @unit_empty_base = @unit;
																              
          for (int i = 0; i < 건물_거점끝; i++)
          {
            pk::building@ empty_base = pk::get_building(i); 
		
                int unit_id    = unit.get_id();
                int empty_base_id  = empty_base.get_id();
                pk::person@ leader = pk::get_person(unit.leader);

            pk::building@ unit_base = pk::get_building(pk::get_building_id(unit.pos));
            int unit_base_id = unit_base.get_id();

            if (pk::is_alive(empty_base) and pk::is_alive(unit_base))
            {
                    
                if (empty_base.get_force_id() == -1 and pk::get_troops(empty_base) == 0 and func_already_empty(empty_base) <= 1 )
                    {

                if (건물_파양항 == empty_base_id or 건물_노릉항 == empty_base_id or 건물_서하항 == empty_base_id or 건물_하양항 == empty_base_id or 건물_해현항 == empty_base_id or 건물_강도항 == empty_base_id )
				    continue;	
                    												
                    if (pk::is_neighbor_base(empty_base_id, unit_base_id) or empty_base_id == unit_base_id)
                           {								
                           best_dst = empty_base_id;
                           dst_list.add(empty_base);  // 전방 리스트 추가
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
                if (a.get_id() < 건물_도시끝 or b.get_id() < 건물_도시끝)	
                return (a.get_id() < b.get_id());					

            pk::building@ unit_base = pk::get_building(pk::get_building_id(main.unit_empty_base.pos));
            int unit_base_id = unit_base.get_id();

                    int build_dist_a = pk::get_building_distance(a.get_id(), unit_base.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), unit_base.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.unit_empty_base.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.unit_empty_base.pos);

                    if (build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);
                    
                    return (pos_dist_a < pos_dist_b);

                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
		}




        //---------------------------------------------------------------------------      


        
        // ----- 적의 병영 무조건 공격
        // 공격부대 : 현재 좌표구역의 거점 세력 확인 : true=원정 또는 원군 / false=요격 판단
        bool attack_barrack(pk::unit@ unit)
        {
            if (!pk::is_alive(unit)) return false;
            if (unit.type != 부대종류_전투) return false;
            if (pk::is_player_controlled(unit)) return false;			
                        
            pk::building@ service_base = pk::get_building(pk::get_service(unit));
            pk::building@ unit_base = pk::get_building(pk::get_building_id(unit.pos));
            if (pk::is_alive(service_base) and pk::is_alive(unit_base))
            {
                int unit_id    = unit.get_id();
                int service_id = service_base.get_id();
                int unit_base_id  = unit_base.get_id();
                pk::person@ leader = pk::get_person(unit.leader);
                				
	
                // 징병 못하게 병영 공격 2021.09.27 일송정 수정
				
                if (pk::is_enemy(unit, unit_base) and pk::is_alive(unit) and pk::is_alive(unit_base))
                {
					
                   pk::city@ city = pk::building_to_city(unit_base);	
                   if (city is null)    return false;				   
					
                    pk::person@ leader = pk::get_person(unit.leader);
                    if ( pk::has_facility(city, 시설_병영) or pk::has_facility(city, 시설_병영2단) or pk::has_facility(city, 시설_병영3단) )
                    {

            for (int i = 0; i < int(city.max_devs); i++)
            {
                pk::building@ building = city.dev[i].building;
                if (pk::is_alive(building) and pk::is_enemy(unit, building) and ( building.facility == 시설_병영 or building.facility == 시설_병영2단 or building.facility == 시설_병영3단 ) )
                {
					
		          if (pk::get_distance(building.get_pos(), unit.pos) <= 4 and pk::get_troops (unit_base) >= 5000 and unit_base.hp >= 1000)				

				    {						

																
                        // 적지이면 적거점 공격 재설정
                        pk::set_order(unit, 부대임무_공격, building.pos);
                        // 목표변경 메시지
                        if (대화표시설정 and pk::is_in_screen(unit.pos))
                        {
                            string target_name = pk::decode(pk::get_name(unit_base));
                            switch(pk::rand(3))
                            {
                                case 0: pk::say(pk::encode("다시는 병력을 모으지 못하게\n병영을 공격해라!"), leader); break;
                                case 1: pk::say(pk::encode("다시는 병력을 모으지 못하게\n병영을 공격해라!"), leader); break;
                                case 2: pk::say(pk::encode("다시는 병력을 모으지 못하게\n병영을 공격해라!"), leader); break;
                            }
                        }

                    }

                }		

            }				
                        
                         return true;    
                    }

                  }	



				
            }
            return false;            
        }



        //---------------------------------------------------------------------------      



      // 해당 공백지로 미리 출진한 부대 숫자 체크, masterpiecek님의 AI_도시물자수송.cpp를 참조했습니다. (2022.06. 일송정 추가)

	 int func_already_empty(pk::building@ building)
		{
			int already = 0;
			for (int unit_id = 0; unit_id < 부대_끝; unit_id++)
			{
				pk::unit@ unit = pk::get_unit(unit_id);

			if (unit.get_force_id() == -1) continue;
				if ( pk::is_alive(unit) and unit.type == 부대종류_전투 and unit.target == building.get_id() ) 

				already++;
			}

			return already;
		}




        // 수성 공성 작전시 거점 주변에 부대들이 너무 몰려있는 걸 방지      (2021.09.02 일송정 추가 )
        bool unit_base_nearby(pk::unit@ unit)
        {
            if (!pk::is_alive(unit)) return false;
            if (unit.type != 부대종류_전투) return false;
            if (pk::is_player_controlled(unit)) return false;			
            
            int candidate_count = list_candidate_unit.count;
            if (candidate_count > 0) return false;

            if (status_neighbor_enemy_unit(unit)) return false;  
			
            pk::building@ service_base = pk::get_building(pk::get_service(unit));
            pk::building@ target_base = pk::get_building(pk::get_building_id(unit.pos));
            if (pk::is_alive(service_base) and pk::is_alive(target_base))
            {
                int unit_id    = unit.get_id();
                int service_id = service_base.get_id();
                int target_id  = target_base.get_id();
                pk::person@ leader = pk::get_person(unit.leader);
                
			// 전방 거점 여부 확인.
			int target = getAdjacentBase(unit);
			if (target == -1) return false;
			
                // 관문 공성전시 너무 많은 공격부대 퇴각 
                if (pk::is_enemy(unit, target_base) )
                {
                    pk::person@ leader = pk::get_person(unit.leader);
                    pk::building@ service_base = pk::get_building(pk::get_service(unit));

			int Siege_weapon_units1 = 0;
			int Siege_weapon_units2 = 0;
			int Siege_weapon_units3 = 0;
			int Siege_weapon_troops1 = 0;
			int Siege_weapon_troops2 = 0;
			int Siege_weapon_troops3 = 0;
			int enemy_units3 = 0;

			int normal_weapon_units3 = 0;

            // 적군검색범위
			pk::array<pk::point> range = pk::range(target_base.pos, 1, ((target_base.facility == 시설_도시) ? 14 : 14 ) );
			for (int i = 0; i < int(range.length); i++)
			{
                pk::point pos = range[i];
				pk::unit@ unit = pk::get_unit(pos);
				if (pk::is_alive(unit))
				{
					int distance = pk::get_distance(target_base.get_pos(), pos);
					if (pk::is_enemy(target_base, unit) and unit.type == 부대종류_전투 and ( unit.weapon == 병기_충차 or unit.weapon == 병기_정란 or unit.weapon == 병기_투석 or unit.weapon == 병기_목수 ) )
					{
						if (distance <= 1)
						{
							Siege_weapon_units1++;
						}
						if (distance <= 9)
						{
							Siege_weapon_units2++;
							Siege_weapon_troops2 += unit.troops;
						}
                                                 if (distance <= 14)
						{
							Siege_weapon_units3++;
                                                        Siege_weapon_troops3 += unit.troops;
						}
					}
					else if (target_base.get_force_id() == unit.get_force_id() and unit.type == 부대종류_전투)
					{
                                             if (distance <= 7)
						{
							enemy_units3++;
						}
					}
					else if (pk::is_enemy(target_base, unit) and unit.type == 부대종류_전투 and ( unit.weapon == 병기_군마 or unit.weapon == 병기_창 or unit.weapon == 병기_극 or unit.weapon == 병기_노 or unit.weapon == 병기_검))
					{
                                             if (distance <= 14)
						{
							normal_weapon_units3++;
						}
					}
				}
			}
            

                    if ( pk::is_alive(unit) and pk::is_alive(target_base) and (((( Siege_weapon_units1 >= 1 and Siege_weapon_units2 >= 4 and normal_weapon_units3 >= 8 ) or normal_weapon_units3 >= 18) and ( unit.weapon == 병기_군마 or unit.weapon == 병기_창 or unit.weapon == 병기_극 or unit.weapon == 병기_노 or unit.weapon == 병기_검) and 건물_관문시작 <= target_base.get_id() and target_base.get_id() < 건물_항구끝 and pk::get_troops (target_base) >= 3000 and (( 1 <= pk::get_distance(target_base.get_pos(), unit.pos) and pk::get_distance(target_base.get_pos(), unit.pos) <= 2 ) or pk::get_distance(target_base.get_pos(), unit.pos) <= 3 ))  ) )
                    {
                        // 목표 재설정 정보 저장
                        arr_target_base_id[unit_id] = target_id;
                        // 적지이면 적거점 공격 재설정
                        pk::set_order(unit, 부대임무_공격, pk::get_building(target).get_pos());
                        // 목표변경 메시지
                        if (대화표시설정 and pk::is_in_screen(unit.pos))
                        {
                            string target_name = pk::decode(pk::get_name(pk::get_building(target)));
                            switch(pk::rand(3))
                            {
                                case 0: pk::say(pk::encode(pk::format("효과적인 공성전을 위해\n우리는 \x1b[2x{}\x1b[0x(으)로 돌아가자.", target_name)), leader); break;
                                case 1: pk::say(pk::encode(pk::format("효과적인 공성전을 위해\n우리는 \x1b[2x{}\x1b[0x(으)로 돌아가자.", target_name)), leader); break;
                                case 2: pk::say(pk::encode(pk::format("효과적인 공성전을 위해\n우리는 \x1b[2x{}\x1b[0x(으)로 돌아가자.", target_name)), leader); break;
                            }
                        }
                        
                         return true;    
                    }

                  }	




                // 항구 수상전시 너무 많은 공격 함선들 퇴각
                if (pk::is_enemy(unit, target_base) )
                {
                    pk::person@ leader = pk::get_person(unit.leader);
                    pk::building@ service_base = pk::get_building(pk::get_service(unit));

			int Sea_weapon_units1 = 0;
			int Sea_weapon_units2 = 0;
			int Sea_weapon_units3 = 0;
			int Sea_weapon_troops1 = 0;
			int Sea_weapon_troops2 = 0;
			int Sea_weapon_troops3 = 0;
			int enemy_units3 = 0;

			int normal_weapon_units3 = 0;

            // 적군검색범위
			pk::array<pk::point> range = pk::range(target_base.pos, 1, ((target_base.facility == 시설_도시) ? 14 : 14 ) );
			for (int i = 0; i < int(range.length); i++)
			{
                pk::point pos = range[i];
				pk::unit@ unit = pk::get_unit(pos);
				if (pk::is_alive(unit))
				{
					int distance = pk::get_distance(target_base.get_pos(), pos);
					if (pk::is_enemy(target_base, unit) and unit.type == 부대종류_전투 and ( unit.weapon == 병기_주가 or unit.weapon == 병기_누선 or unit.weapon == 병기_투함 ) )
					{
						if (distance <= 1)
						{
							Sea_weapon_units1++;
						}
						if (distance <= 9)
						{
							Sea_weapon_units2++;
							Sea_weapon_troops2 += unit.troops;
						}
                                                 if (distance <= 14)
						{
							Sea_weapon_units3++;
                                                        Sea_weapon_troops3 += unit.troops;
						}
					}
					else if (target_base.get_force_id() == unit.get_force_id() and unit.type == 부대종류_전투 and ( unit.weapon == 병기_주가 or unit.weapon == 병기_누선 or unit.weapon == 병기_투함 ) )
					{
                                             if (distance <= 7)
						{
							enemy_units3++;
						}
					}
					else if (pk::is_enemy(target_base, unit) and unit.type == 부대종류_전투 and ( unit.weapon == 병기_군마 or unit.weapon == 병기_창 or unit.weapon == 병기_극 or unit.weapon == 병기_노 or unit.weapon == 병기_검))
					{
                                             if (distance <= 14)
						{
							normal_weapon_units3++;
						}
					}
				}
			}
            

                    if ( pk::is_alive(unit) and pk::is_alive(target_base) and ( ( Sea_weapon_units1 >= 1 and Sea_weapon_units2 >= 13 and enemy_units3 == 0 and ( unit.weapon == 병기_주가 or unit.weapon == 병기_누선 or unit.weapon == 병기_투함 ) and 건물_항구시작 <= target_base.get_id() and target_base.get_id() < 건물_항구끝 and pk::get_troops (target_base) >= 3000 and 5 <= pk::get_distance(target_base.get_pos(), unit.pos) and pk::get_distance(target_base.get_pos(), unit.pos) <= 10 )  ) )
                    {
                        // 목표 재설정 정보 저장
                        arr_target_base_id[unit_id] = target_id;
                        // 적지이면 적거점 공격 재설정
                    if ( unit.troops <= 2500)						
                    {						
                        pk::set_order(unit, 부대임무_공격, pk::get_building(target).get_pos());
                        // 목표변경 메시지
                        if (대화표시설정 and pk::is_in_screen(unit.pos))
                        {
                            string target_name = pk::decode(pk::get_name(pk::get_building(target)));
                            switch(pk::rand(3))
                            {
                                case 0: pk::say(pk::encode(pk::format("수상전에선 단호한 결정이 중요!\n우리는 \x1b[2x{}\x1b[0x(으)로 돌아가자.", target_name)), leader); break;
                                case 1: pk::say(pk::encode(pk::format("수상전에선 단호한 결정이 중요!\n우리는 \x1b[2x{}\x1b[0x(으)로 돌아가자.", target_name)), leader); break;
                                case 2: pk::say(pk::encode(pk::format("수상전에선 단호한 결정이 중요!\n우리는 \x1b[2x{}\x1b[0x(으)로 돌아가자.", target_name)), leader); break;
                            }
                        }
                    }						


			// 다른 항구로 진격 (2022.06. 일송정 추가)
			int EnemyPort = getEnemyPort(unit);
			if (EnemyPort == -1) return false;
			
                    if (target_id != pk::get_building(EnemyPort).get_id() and unit.troops >= 4000 )
                      {
                        pk::set_order(unit, 부대임무_공격, pk::get_building(EnemyPort).pos);
                        // 목표변경 메시지
                        if (대화표시설정 and pk::is_in_screen(unit.pos))
                        {
                            string target_name = pk::decode(pk::get_name(pk::get_building(EnemyPort)));
                            switch(pk::rand(3))
                            {
                                case 0: pk::say(pk::encode(pk::format("수상전에선 단호한 결정이 중요!\n우리는 \x1b[2x{}\x1b[0x(으)로 진격한다.", target_name)), leader); break;
                                case 1: pk::say(pk::encode(pk::format("수상전에선 단호한 결정이 중요!\n우리는 \x1b[2x{}\x1b[0x(으)로 진격한다.", target_name)), leader); break;
                                case 2: pk::say(pk::encode(pk::format("수상전에선 단호한 결정이 중요!\n우리는 \x1b[2x{}\x1b[0x(으)로 진격한다", target_name)), leader); break;
                            }
                        }
                      }	                      
                         return true;    
                    }

                  }	


                //  수비 쪽의 수성전시 수성부대가 너무 많으면 퇴각
                if ( target_base.get_force_id() == unit.get_force_id() )
                {
                    pk::person@ leader = pk::get_person(unit.leader);
                    pk::building@ service_base = pk::get_building(pk::get_service(unit));

			int enemy_units1 = 0;
			int enemy_units2 = 0;
			int enemy_units3 = 0;
			int enemy_troops1 = 0;
			int enemy_troops2 = 0;
			int enemy_troops3 = 0;
			int force_units1 = 0;			
			int force_units3 = 0;

            // 적군검색범위
			pk::array<pk::point> range = pk::range(target_base.pos, 1, ((target_base.facility == 시설_도시) ? 14 : 14 ) );
			for (int i = 0; i < int(range.length); i++)
			{
                pk::point pos = range[i];
				pk::unit@ unit = pk::get_unit(pos);
				if (pk::is_alive(unit))
				{
					int distance = pk::get_distance(target_base.get_pos(), pos);
					if (pk::is_enemy(target_base, unit) and unit.type == 부대종류_전투 and ( unit.weapon == 병기_충차 or unit.weapon == 병기_정란 or unit.weapon == 병기_투석 or unit.weapon == 병기_목수 or unit.weapon == 병기_주가 or unit.weapon == 병기_누선 or unit.weapon == 병기_투함) )
					{
						if (distance <= 4)
						{
							enemy_units1++;
						}
						if (distance <= 9)
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
					else if (target_base.get_force_id() == unit.get_force_id() and unit.type == 부대종류_전투)
					{
                                             if (distance <= 1)
						{
							force_units1++;
						}						
                                             if (distance <= 10)
						{
							force_units3++;
						}
					}
				}
			}
            

                    if ( pk::is_alive(unit) and pk::is_alive(target_base) and ( ( force_units1 >= 1 and force_units3 >= 8 and enemy_units1 >= 3   and (unit.weapon == 병기_군마 or unit.weapon == 병기_창 or unit.weapon == 병기_극 or unit.weapon == 병기_노 or unit.weapon == 병기_검) and 건물_관문시작 <= target_base.get_id() and target_base.get_id() < 건물_항구끝 and pk::get_troops (target_base) >= 10000 and 3 <= pk::get_distance(target_base.get_pos(), unit.pos) and pk::get_distance(target_base.get_pos(), unit.pos) <= 6 )  ) )
                    {
                        // 목표 재설정 정보 저장
                        arr_target_base_id[unit_id] = target_id;
                        // 적지이면 적거점 공격 재설정
                        pk::set_order(unit, 부대임무_공격, pk::get_building(target).get_pos());
                        // 목표변경 메시지
                        if (대화표시설정 and pk::is_in_screen(unit.pos))
                        {
                            string target_name = pk::decode(pk::get_name(pk::get_building(target)));
                            switch(pk::rand(3))
                            {
                                case 0: pk::say(pk::encode(pk::format("부디 성을 지켜주길...\n우리는 \x1b[2x{}\x1b[0x(으)로 돌아가자.", target_name)), leader); break;
                                case 1: pk::say(pk::encode(pk::format("부디 성을 지켜주길...\n우리는 \x1b[2x{}\x1b[0x(으)로 돌아가자.", target_name)), leader); break;
                                case 2: pk::say(pk::encode(pk::format("부디 성을 지켜주길...\n우리는 \x1b[2x{}\x1b[0x(으)로 돌아가자.", target_name)), leader); break;
                            }
                        }
                        
                         return true;    
                    }

                  }	



				  
            }
            return false;            
        }






        // 부대들 대치 상태 길어지면 후퇴  (2022.06.18 일송정 추가 )
        bool unit_jam(pk::unit@ unit)
        {
            if (!pk::is_alive(unit)) return false;
            if (unit.type != 부대종류_전투) return false;
            if (pk::is_player_controlled(unit)) return false;			
            
            if (status_neighbor_enemy_unit(unit)) return false;  
            
            pk::building@ service_base = pk::get_building(pk::get_service(unit));
            pk::building@ target_base = pk::get_building(pk::get_building_id(unit.pos));
            if (pk::is_alive(service_base) and pk::is_alive(target_base))
            {
                int unit_id    = unit.get_id();
                int service_id = service_base.get_id();
                int target_id  = target_base.get_id();
                pk::person@ leader = pk::get_person(unit.leader);
 
			// 전방 거점 여부 확인.
			int target = getAdjacentBase(unit);
			if (target == -1) return false; 

			if (pk::is_enemy(unit, target_base) and enemy_approach(target_base)) return false;   
			
                    if ( pk::is_alive(unit) and pk::is_alive(target_base) and jam_f_units_around(unit) >= 14 and jam_e_units_around(unit) == 0)
                    {
                        // 목표 재설정 정보 저장
                        arr_target_base_id[unit_id] = target_id;
                        // 적지이면 적거점 공격 재설정
                        pk::set_order(unit, 부대임무_공격, pk::get_building(target).get_pos());
                        // 목표변경 메시지
                        if (대화표시설정 and pk::is_in_screen(unit.pos))
                        {
                            string target_name = pk::decode(pk::get_name(pk::get_building(target)));
                            switch(pk::rand(3))
                            {
                                case 0: pk::say(pk::encode(pk::format("대치 상태가 너무 길어지는군.\n우리는 \x1b[2x{}\x1b[0x(으)로 돌아가자.", target_name)), leader); break;
                                case 1: pk::say(pk::encode(pk::format("대치 상태가 너무 길어지는군.\n우리는 \x1b[2x{}\x1b[0x(으)로 돌아가자.", target_name)), leader); break;
                                case 2: pk::say(pk::encode(pk::format("대치 상태가 너무 길어지는군.\n우리는 \x1b[2x{}\x1b[0x(으)로 돌아가자.", target_name)), leader); break;
                            }
                        }
                        
                         return true;    
                    }




				  
            }
            return false;            
        }




        
		/** 인근 아군 거점 찾기 */


        pk::unit@ unit_k;
		int getAdjacentBase(pk::unit@ unit)
		{
			int best_dst = -1;
			int best_distance = 0;


            int unit_id = unit.get_id();
            pk::list<pk::building@> dst_list; 
            @unit_k = @unit;
																              
            pk::force@ force = pk::get_force(unit.get_force_id());
            
  for (int f = 0; f < 건물_거점끝; f++)
   {

                    pk::building@ adjacent_base = pk::get_building(f);																				 																				 
            pk::building@ service_base = pk::get_building(pk::get_service(unit));
			
                int unit_id    = unit.get_id();
                int service_id = service_base.get_id();
                int adjacent_base_id = adjacent_base.get_id();	
            pk::building@ unit_base = pk::get_building(pk::get_building_id(unit.pos));
            int unit_base_id = unit_base.get_id();				

                pk::person@ Home_taishu = pk::get_person(pk::get_taishu_id(service_base));	
                int a = pk::get_person(pk::get_kunshu_id(service_base)).character;				

                    
             if ( 건물_도시시작 <= adjacent_base.get_id() and adjacent_base.get_id() < 건물_거점끝)
	{

                if (service_base.get_force_id() == adjacent_base.get_force_id())
                 {            


                        int enemy_weight = countNeighborEnemyBase(adjacent_base);	
                        int enemy_weight_service = countNeighborEnemyBase(service_base);

                    
		/** 적의 거점으로부터 떨어진 후방거점들 */


                    if (unit.get_force_id() == adjacent_base.get_force_id())
                       {
                           best_dst = adjacent_base_id;
                           dst_list.add(adjacent_base);  // 전방 리스트 추가
                        }


                    }
                }
		
	  
   }	  

       

            // 출진가능 거점리스트 정렬 (거점 거리 오름차순, 좌표거리 오름차순)
            if (dst_list.count == 0)
                best_dst = -1;
            else if (int(main.unit_k.troops) >= 극소병력부대_복귀병력기준 and main.unit_k.food >= float (부대복귀_병량기준_비율 * main.unit_k.troops ))
            {
                dst_list.sort(function(a, b)
                {
                bool city_a = (건물_도시시작 <= a.get_id() and a.get_id() < 건물_도시끝);
                bool city_b = (건물_도시시작 <= b.get_id() and b.get_id() < 건물_도시끝);
                if ( city_a and !city_b) return true;
                if (!city_a and  city_b) return false;

            pk::building@ unit_base = pk::get_building(pk::get_building_id(main.unit_k.pos));
            int unit_base_id = unit_base.get_id();

                    int build_dist_a = pk::get_building_distance(a.get_id(), unit_base.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), unit_base.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.unit_k.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.unit_k.pos);

                    if (build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);
                    
                    return (pos_dist_a < pos_dist_b);

                    return (pk::get_max_troops(a) - pk::get_troops(a) > pk::get_max_troops(b) - pk::get_troops(b));
                });
                best_dst = dst_list[0].get_id();
            }
                
            else if (int(main.unit_k.troops) < 극소병력부대_복귀병력기준 or main.unit_k.food < float (부대복귀_병량기준_비율 * main.unit_k.troops ))
            {
                dst_list.sort(function(a, b)
                {

            pk::building@ unit_base = pk::get_building(pk::get_building_id(main.unit_k.pos));
            int unit_base_id = unit_base.get_id();

                    int build_dist_a = pk::get_building_distance(a.get_id(), unit_base.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), unit_base.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.unit_k.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.unit_k.pos);


                    return (pos_dist_a < pos_dist_b);

                    return (pk::get_max_troops(a) - pk::get_troops(a) > pk::get_max_troops(b) - pk::get_troops(b));
                });
                best_dst = dst_list[0].get_id();
            }
                           
            
			return best_dst;
		}





           // 부대 거리 4 내 아군부대수 2022.06.18 일송정 추가
		   
	 int jam_f_units_around(pk::unit@ unit)
		{

			int enemy_units1 = 0;
			int force_units1 = 0;

            // 적군검색범위
			pk::array<pk::point> range = pk::range(unit.pos, 1, 5 );
			for (int i = 0; i < int(range.length); i++)
			{
				auto unit_around = pk::get_unit(range[i]);
				if (pk::is_alive(unit) and pk::is_alive(unit_around))
				{
                                  int unit_id    = unit.get_id();
                                  int unit_around_id    = unit_around.get_id();
					int distance = pk::get_distance(unit.pos, unit_around.pos);
					if (pk::is_enemy(unit, unit_around) and unit.type == 부대종류_전투 and unit_id != unit_around_id)
					{
						if (distance <= 4)
						{
							enemy_units1++;						
						}

					}
					else if (unit.get_force_id() == unit_around.get_force_id() and unit.type == 부대종류_전투 and unit_id != unit_around_id)
					{
                                             if (distance <= 4)
						{
							force_units1++;
						}
					}
				}
			}
            
			return force_units1;

		}






           // 부대 거리 4 내 적부대수 2022.06.18 일송정 추가
		   
	 int jam_e_units_around(pk::unit@ unit)
		{

			int enemy_units1 = 0;
			int force_units1 = 0;

            // 적군검색범위
			pk::array<pk::point> range = pk::range(unit.pos, 1, 5 );
			for (int i = 0; i < int(range.length); i++)
			{
				auto unit_around = pk::get_unit(range[i]);
				if (pk::is_alive(unit) and pk::is_alive(unit_around))
				{
                                  int unit_id    = unit.get_id();
                                  int unit_around_id    = unit_around.get_id();
					int distance = pk::get_distance(unit.pos, unit_around.pos);
					if (pk::is_enemy(unit, unit_around) and unit.type == 부대종류_전투 and unit_id != unit_around_id)
					{
						if (distance <= 4)
						{
							enemy_units1++;						
						}

					}
					else if (unit.get_force_id() == unit_around.get_force_id() and unit.type == 부대종류_전투 and unit_id != unit_around_id)
					{
                                             if (distance <= 4)
						{
							force_units1++;
						}
					}
				}
			}
            
			return enemy_units1;

		}






        
           // 이미 출진한 부대 숫자 체크,  masterpiecek님의 AI도시물자수송을 참조했습니다. 2021.01.15 일송정 수정
		   
	 int func_already(pk::building@ building)
		{
			int already = 0;
			for (int unit_id = 0; unit_id < 부대_끝; unit_id++)
			{
				pk::unit@ unit = pk::get_unit(unit_id);
			if (building.get_force_id() == -1) continue;
			if (unit.get_force_id() == -1) continue;
				if ( pk::is_alive(unit) and 3000 <= unit.troops  and unit.get_force_id() != building.get_force_id() and unit.target == building.get_id()) 

				already++;
			}

			return already;
		}										  
  


           // 해당 거점을 향해 이미 출진한 상태인 그 거점 근처 병력 3천 이상의 부대 숫자 체크,  masterpiecek님의 AI도시물자수송을 참조했습니다. 2021.09.02 일송정 추가
		   
	 int func_already_base(pk::building@ building)
		{
			int already = 0;
			for (int unit_id = 0; unit_id < 부대_끝; unit_id++)
			{
				pk::unit@ unit = pk::get_unit(unit_id);
			if (building.get_force_id() == -1) continue;
			if (unit.get_force_id() == -1) continue;
				if ( pk::is_alive(unit) and 3000 <= unit.troops  and unit.get_force_id() == building.get_force_id() and unit.target == building.get_id() and pk::get_distance(building.get_pos(), unit.pos) <= 8 ) 

				already++;
			}

			return already;
		}



         // 목표 거점으로 이미 출발한 지원군 병력 합산, masterpiecek님의 AI_도시물자수송.cpp를 참조했습니다. (2022.06. 일송정 추가)

																																			  
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

        //---------------------------------------------------------------------------------------

        // 해당 거점 근처의 아군 부대수. 2022.07.02 일송정 추가
																																			  
	 int friendlies_around_base(pk::force@ force, pk::building@ building, int distance)
		{
			int units = 0;
			for (int unit_id = 0; unit_id < 부대_끝; unit_id++)
			{
				pk::unit@ unit = pk::get_unit(unit_id);
			int force_id = force.get_id();
			if (unit.get_force_id() == -1) continue;
				if ( pk::is_alive(unit) and unit.get_force_id() == force_id and pk::get_distance(building.pos, unit.pos) <= distance) 

				units++;
			}

			return units;
		}

        //---------------------------------------------------------------------------------------
        // 해당 거점의 방어 부대수. 2022.07.02 일송정 추가																				   
																																			  
	 int defensive_around_base(pk::building@ building, int distance)
		{
			int units = 0;
			for (int unit_id = 0; unit_id < 부대_끝; unit_id++)
			{
				pk::unit@ unit = pk::get_unit(unit_id);

			if (unit.get_force_id() == -1) continue;
			if (unit.get_force_id() != building.get_force_id()) continue;
				if ( pk::is_alive(unit) and unit.get_force_id() == building.get_force_id() and pk::get_distance(building.pos, unit.pos) <= distance) 

				units++;
			}

			return units;
		}


        //---------------------------------------------------------------------------------------

        //---------------------------------------------------------------------------------------

        // ***** 거점 근처에서 적과 아군이 간격 없이 직접적으로 교전중인가? (2022.06. 일송정 추가)***** //
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

        // ***** 적이 아군 거점에 다가오는가? (2022.06. 일송정 추가)***** //
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
        // 적부대가 우리 거점 경계 범위 까지 올 수 있는 상황 (2022.06. 일송정 추가)
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
        //---------------------------------------------------------------------------------------

        // ***** 적이 아군 거점에 다가오는가? (항관이 있어서 바로 못오는 경우까지 감안) (2022.06. 일송정 추가)***** //
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
        // 적부대가 우리 거점 경계 범위 까지 올 수 있는 상황 (항관이 있어서 바로 못오는 경우까지 감안) (2022.06. 일송정 추가)
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

        //---------------------------------------------------------------------------
        // ----- 아군거점_수성지원 
        // 방어부대 : 주변의 병력부족한 교전거점으로 이동
        bool def_force_base_nearby(pk::unit@ unit)
        {
            if (!pk::is_alive(unit)) return false;
            if (unit.type != 부대종류_전투) return false;    // 전투 병과 아니면 제외
            
            pk::building@ service = pk::get_building(pk::get_service(unit));
            if (!pk::is_alive(service)) return false;
            
            int candidate_count = list_candidate_unit.count;
            if (candidate_count > 1) return false;
            
            // 주변의 목표거점 검색
            pk::list<pk::building@> list_target_base;
            pk::array<pk::point> arr = pk::get_movable_pos(unit);
            for (int i = 0; i < int(arr.length); i++)
            {
                pk::building@ base = pk::get_building(arr[i]);
                if (pk::is_alive(base))
                {
                    int base_id = base.get_id();
                    bool is_force_base = (unit.get_force_id() == base.get_force_id());
                    bool is_force_city = (도시거점_수성지원 and is_force_base and (건물_도시시작 <= base_id and base_id < 건물_도시끝));
                    bool is_force_gate = (관문항구_수성지원 and is_force_base and (건물_관문시작 <= base_id and base_id < 건물_항구끝));
                    if (is_force_base and pk::enemies_around(base))
                    {
                        if (is_force_gate and is_weak_base(base)) list_target_base.add(base);
                        if (is_force_city and is_weak_base(base)) list_target_base.add(base);
                    }
                }
            }
            
            if (list_target_base.count == 0) return false;
            
            // 목표 거점이 다수인 경우 우선순위 정렬 (도시가 관문항구보다 우선, 병력 부족 거점 우선, 병력 충분 시 내구도 부족 거점 우선
            list_target_base.sort(function(a, b)
            {
                bool city_a = (건물_도시시작 <= a.get_id() and a.get_id() < 건물_도시끝);
                bool city_b = (건물_도시시작 <= b.get_id() and b.get_id() < 건물_도시끝);
                if ( city_a and !city_b) return true;
                if (!city_a and  city_b) return false;
                int troops_a = pk::get_troops(a);
                int troops_b = pk::get_troops(b);
                if (troops_a > 3000 and troops_b > 3000) return (int(a.hp) < int(b.hp));
                return (troops_a < troops_b);
            });
            
            pk::building@ target_base = list_target_base[0];
            pk::person@ leader = pk::get_person(unit.leader);

            // 내구도 450 이하라 붕괴되기 쉬운 거점 제외 (2022.02.11 일송정 추가)  
            if (pk::enemies_around(target_base) and target_base.hp <= 450)
            return false;
		            
            if (pk::is_alive(target_base) and pk::is_alive(leader))
            {
                string leader_name = pk::decode(pk::get_name(leader));
                string target_name = pk::decode(pk::get_name(target_base));
                int target_id  = target_base.get_id();
                int unit_id    = unit.get_id();
                int max_atk_range   = get_atk_range(unit).second;
                pk::array<int> num_unit_around = count_unit_around(unit, target_base);  //[0]근접, [1]간접
                
                // 아군 거점으로 이동
                if (arr_target_base_id[unit_id] != target_id)
                {   
                    // 근접전투부대 이거나, 간접전투부대면서 주변에 지원가능한 근접전투부대가 없는 경우
                    if (max_atk_range <= 1 or (max_atk_range > 1 and num_unit_around[0] < 1))
                    {
                        // 목표 재설정 정보 저장
                        arr_target_base_id[unit_id] = target_id;
                        // 아군 거점 이동 재설정
                        pk::set_order(unit, 부대임무_공격, target_base.pos);  // 부대임무_이동 → 부대임무_공격 으로 수정 ('20.9.13)
                        // 목표변경 메시지
                        if (대화표시설정 and pk::is_in_screen(unit.pos))
                        {
                            switch(pk::rand(3))
                            {
                                case 0: pk::say(pk::encode(pk::format("\x1b[2x{}\x1b[0x을(를) 지원하라", target_name)), leader); break;
                                case 1: pk::say(pk::encode(pk::format("우리는 \x1b[2x{}\x1b[0x을(를) 지원한다", target_name)), leader); break;
                                case 2: pk::say(pk::encode(pk::format("\x1b[2x{}\x1b[0x(으)로 향하라", target_name)), leader); break;
                            }
                        }
                        
                        if (디버그모드)
                            pk::info( pk::format("{} 임무목표:{}", leader_name, target_name) );
                        
                        return true;
                    }
                }
            }
            return false;
        }
        
        // 부대주변의 자세력 근접/간접 공격 부대수 확인
        pk::array<int> count_unit_around(pk::unit@ unit, pk::building@ target_base)
        {
            pk::array<int> count_unit(2, 0);    // [0]근접, [1]간접
            pk::array<pk::point> arr = pk::get_movable_pos(unit, target_base.pos, (unit.attr.stat[부대능력_이동] / 2));
            for (int i = 0; i < int(arr.length); i++)
            {
                pk::unit@ unit_t = pk::get_unit(arr[i]);
                if (pk::is_alive(unit_t) and unit_t.type == 부대종류_전투)
                    if (unit.get_id() != unit_t.get_id() and unit.get_force_id() == unit_t.get_force_id())
                    {
                        if (get_atk_range(unit_t).second > 1)
                             count_unit[1]++;
                        else count_unit[0]++;
                    }
            }
            return count_unit;
        }
        
        // 취약 거점 판단 조건
        bool is_weak_base(pk::building@ base)
        {
            if (!pk::is_alive(base)) return false;
            int base_id = base.get_id();
            if (base_id < 0 or base_id >= 건물_거점끝) return false;
            bool is_city = (건물_도시시작 <= base_id and base_id < 건물_도시끝);
            int base_troops = pk::get_troops(base);
            int base_hp     = int(base.hp);
            int base_max_hp = int(pk::get_max_hp(base));

            if (base_troops < 500 or base_hp < 700) return true;
            else if (!is_city and (base_troops <= 1000 and base_hp <= pk::max(1500, int(base_max_hp * 0.75f)))) return true;
            else if (!is_city and (base_troops <= 2000 and base_hp <= pk::max(1000, int(base_max_hp * 0.50f)))) return true;
            else if ( is_city and (base_troops <= 3000 and base_hp <= pk::max(2000, int(base_max_hp * 0.50f)))) return true;
            else if ( is_city and (base_troops <= 5000 and base_hp <= pk::max(1500, int(base_max_hp * 0.25f)))) return true;
            
            return false;
        }
        
        //---------------------------------------------------------------------------
        // ----- 교전 후 거점 부대 진입 시 초과병력/병기 부대 귀환 설정
        // 교전부대 : 현재 좌표구역의 거점 세력 확인 : true=원정 또는 원군 / false=요격 판단
        bool retreat_exceed_unit(pk::unit@ unit)
        {
            if (!pk::is_alive(unit)) return false;
            int unit_id   = unit.get_id();
            int leader_id = unit.leader;
            pk::person@ leader = pk::get_person(leader_id);
            string unit_name = pk::decode(pk::get_name(leader));
            
            int candidate_count = list_candidate_unit.count;
            if (candidate_count > 0) return false;
            
            pk::building@ service_base = pk::get_building(pk::get_service(unit));
            pk::building@ pos_area_base = pk::get_building(pk::get_building_id(unit.pos));
            if (!pk::is_alive(service_base)) return false;
            if (!pk::is_alive(pos_area_base)) return false;
            int service_id = service_base.get_id();
            int pos_area_id  = pos_area_base.get_id();
            
            if (!pk::enemies_around(pos_area_base))
            {
                // 거점 진입 시 부대+거점 병력 한도 설정
                bool is_service_base = (service_id == pos_area_id);
                bool is_force_base   = (unit.get_force_id() == pos_area_base.get_force_id());
                bool is_exceed_unit  = (is_force_base and !is_service_base and check_exceed_unit(pos_area_base, unit, true));
                
                // 병력 한도 초과하는 경우 소속 거점으로 퇴각
                if (is_exceed_unit and (arr_target_base_id[unit_id] == pos_area_id and arr_target_unit_id[unit_id] != -1))
                {
                    // 목표 재설정 정보 저장
                    arr_target_base_id[unit_id] = service_id;
                    // 소속 거점으로 돌아감
                    pk::set_order(unit, 부대임무_공격, service_base.pos);
                    // 목표변경 메시지
                    if (대화표시설정 and pk::is_in_screen(unit.pos))
                    {
                        string old_order = pk::format("\x1b[2x{}\x1b[0x은 가지 않아도 된다\n", pk::decode(pk::get_name(pos_area_base)));
                        string target_name = pk::decode(pk::get_name(service_base));
                        switch(pk::rand(3))
                        {
                            case 0: pk::say(pk::encode(pk::format("{}\x1b[2x{}\x1b[0x을(를) 퇴각하라", old_order, target_name)), leader); break;
                            case 1: pk::say(pk::encode(pk::format("{}우리는 \x1b[2x{}\x1b[0x(으)로 돌아간다", old_order, target_name)), leader); break;
                            case 2: pk::say(pk::encode(pk::format("{}\x1b[2x{}\x1b[0x(으)로 향한다", old_order, target_name)), leader); break;
                        }
                    }
                    if (디버그모드) pk::info(pk::format("부대귀환 목표거점: {}", pk::decode(pk::get_name(service_base))) );
                }
            }
            
            // 부대임무 정보 조회
            bool is_order_retreat = (unit.order == 부대임무_퇴각 or (unit.order == 부대임무_물림 and candidate_count == 0));
                
            // 부대임무 목표거점 병력 한도 초과하는 경우 인근의 병력부족 거점으로 퇴각
            if (is_order_retreat or unit.target_type == 부대임무대상_거점)
            {
                pk::building@ base_t = (is_order_retreat)? service_base : pk::get_building(unit.target);
                if (pk::is_alive(base_t) and base_t.get_id() < 건물_거점끝)
                {
                    // 거점진입 대상 거점의 부대진입 시 병력 한도 확인
                    string base_t_name     = pk::decode(pk::get_name(base_t));
                    int target_id          = base_t.get_id();
                    bool is_in_movable_pos = check_base_in_movable_range(unit, base_t); // 부대 이동거리 내에 목표거점이 존재하는 경우
                    bool is_in_city_area   = (pk::get_city_id(base_t.pos) == pk::get_city_id(unit.pos));  // 부대위치가 목표거점과 같은 도시영역인 경우
                    bool is_force_base     = (unit.get_force_id() == base_t.get_force_id());
                    bool is_exceed_unit    = (is_force_base and (is_in_city_area or is_in_movable_pos) and check_exceed_unit(base_t, unit, true));
                    if (디버그모드) pk::info(pk::format("---{}대 {}:{}", unit_name, get_order_info(unit.order), base_t_name));
                    
                    // 병력 한도 초과하는 경우 병력 적은 인근 거점으로 퇴각
                    if (is_exceed_unit)
                    { 
                        // 거점 검색 함수
                        int dst_id = get_neighbor_base_retreat(base_t, unit);
                        pk::building@ dst_base = pk::get_building(dst_id);
                        if (!pk::is_alive(dst_base)) return false;
                        
                         // 목표 재설정 정보 저장
                        arr_target_base_id[unit_id] = dst_id;
                        // 부대임무 재설정 : 새로운 목표 거점으로 이동
                        pk::set_order(unit, 부대임무_공격, dst_base.pos);
                        // 목표변경 메시지
                        if (대화표시설정 and pk::is_in_screen(unit.pos))
                        {
                            string old_order = pk::format("\x1b[2x{}\x1b[0x은 복잡하군\n", pk::decode(pk::get_name(base_t)));
                            string target_name = pk::decode(pk::get_name(dst_base));
                            switch(pk::rand(3))
                            {
                                case 0: pk::say(pk::encode(pk::format("{}\x1b[2x{}\x1b[0x(으)로 진군하라", old_order, target_name)), leader); break;
                                case 1: pk::say(pk::encode(pk::format("{}우리는 \x1b[2x{}\x1b[0x(으)로 들어가자", old_order, target_name)), leader); break;
                                case 2: pk::say(pk::encode(pk::format("{}\x1b[2x{}\x1b[0x(으)로 진로를 변경한다", old_order, target_name)), leader); break;
                            }
                        }
                        if (디버그모드) pk::info(pk::format("부대귀환 목표거점: {}", pk::decode(pk::get_name(dst_base))) );
                    }
                }
            }
            
            return false;            
        }
        
        // 가까운 병력 부족 거점을 얻음
        pk::building@ src_t;
        int get_neighbor_base_retreat(pk::building@ src_base, pk::unit@ unit)
        {
            if (!pk::is_alive(unit) or !pk::is_alive(src_base)) return -1;
            int dst_id = -1;
            int best_dst = -1;
			int best_distance = 0;
            int src_id = src_base.get_id();
            pk::list<pk::building@> dst_list; 
            @src_t = @src_base;
            pk::force@ force = pk::get_force(src_base.get_force_id());
            
			// 철수 거점 검색
            if (pk::get_city_list(force).count <= 1 and src_id < 건물_도시끝)
                return -1;      // 마지막 도시인 경우 철수 불가
            else
            {
                for (int i = 0; i < 건물_거점끝; i++)
                {
                    pk::building@ dst = pk::get_building(i);
                    int dst_id = dst.get_id();
                    bool is_exceed_unit = check_exceed_unit(dst, unit, true);
                    if (!is_exceed_unit and src_id != dst_id and src_base.get_force_id() == dst.get_force_id())
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
                    if (build_dist_a != build_dist_b) return (build_dist_a < build_dist_b);
                    return (pos_dist_a < pos_dist_b);
                });
                best_dst = dst_list[0].get_id();
            }
			return best_dst;
        }
        
        
        // 거점+부대 병력/병기 한도 초과 여부 확인
        //항구, 관문의 경우 별도 설정 추가. 그리고 물자, 병기들은 진입부대_초과한도기준 영향 안받도록 수정. 2021.01.15 일송정 수정			
        bool check_exceed_unit(pk::building@ base, pk::unit@ unit, bool isforce=true)
        {
            if (!pk::is_alive(base) or !pk::is_alive(unit)) return false;
            if (base.get_id() >= 건물_거점끝) return false;
            if ( isforce and base.get_force_id() != unit.get_force_id()) return false;
            if (!isforce and !pk::is_enemy(base, unit)) return false;
            
            float exceed_limit  = pk::max(0.0f, pk::min(1.0f, 진입부대_초과한도기준));
			float exceed_limit2  = pk::max(0.0f, pk::min(1.0f, 항관진입_초과한도기준));				
            float weapon_ignore = pk::max(0.0f, pk::min(1.0f, 진입부대_초과병기_거점병력기준));
            bool is_ignore = (float(pk::get_troops(base))/float(pk::get_max_troops(base)) <= weapon_ignore);
            
            bool is_exceed_troops = false;
            bool is_exceed_weapon = false;
            if (unit.type == 부대종류_전투)
            {
                if (진입부대_초과병력귀환 and base.get_id() < 건물_도시끝)
                {
                    int base_limit = int(float(pk::get_max_troops(base)) * exceed_limit);
                    int exceed_troops = pk::max(0, ((pk::get_troops(base) + unit.troops) - base_limit));
                    is_exceed_troops = (exceed_troops > 0);
                }
                if (진입부대_초과병력귀환 and base.get_id() >=  건물_도시끝)
                {

                    int base_limit = int(float(pk::get_max_troops(base)) * exceed_limit2);
                    int exceed_troops = pk::max(0, ((pk::get_troops(base) + unit.troops) - base_limit));
                    is_exceed_troops = (exceed_troops > 0);


                }					
                if (진입부대_초과병기귀환 and !is_ignore)
                {
                    int gnd_wpn_id = pk::get_ground_weapon_id(unit);
                    int sea_wpn_id = pk::get_sea_weapon_id(unit);
                    int unit_gnd_wpn_amt = (is_siege_weapon(gnd_wpn_id))? 1 : unit.troops;
                    int unit_sea_wpn_amt = (sea_wpn_id == 병기_주가)? 0 : 1;
                    int base_gnd_wpn_amt = pk::get_weapon_amount(base, gnd_wpn_id);
                    int base_sea_wpn_amt = pk::get_weapon_amount(base, sea_wpn_id);
                    int exceed_gnd_wpn_amt = pk::max(0, (base_gnd_wpn_amt + unit_gnd_wpn_amt) - int(float(pk::get_max_weapon_amount(base, gnd_wpn_id))) );
                    int exceed_sea_wpn_amt = pk::max(0, (base_sea_wpn_amt + unit_sea_wpn_amt) - int(float(pk::get_max_weapon_amount(base, sea_wpn_id))) );
                    is_exceed_weapon = (exceed_gnd_wpn_amt > 0 or exceed_sea_wpn_amt > 0);
                }
            }
            else if (unit.type == 부대종류_수송)
            {
                if (진입부대_초과병력귀환)
                {
                    int exceed_troops = pk::max(0, ((pk::get_troops(base) + unit.troops) - pk::get_max_troops(base)) );
                    is_exceed_troops = (exceed_troops >= 1);  // 부대병력 1 이상 증발 시 
                }
                if (진입부대_초과병기귀환 and !is_ignore)
                {
                    pk::array<int> arr_exceed_wpn_amt(병기_끝, 0);
                    for (int i = 0; i < 병기_끝; i++)
                    {
                        if (!is_exceed_weapon and !is_ignore)
                        {
                            int unit_wpn_amt = unit.stock[i].amount;
                            int base_wpn_amt = pk::get_weapon_amount(base, i);
                            arr_exceed_wpn_amt[i] = pk::max(0, (unit_wpn_amt + unit_wpn_amt) - int(float(pk::get_max_weapon_amount(base, i))) );
                            if (arr_exceed_wpn_amt[i] >= ((is_siege_weapon(i) or is_ship_weapon(i))? 1 : 2000))
                                is_exceed_weapon = true;  // 공성/함선병기 1이상 또는 전투병기 2000 이상 증발 시
                        }
                    }
                }
            }
            
            if (디버그모드)
            {
                string unit_name = pk::decode(pk::get_name(pk::get_person(unit.leader)));
                string base_name = pk::decode(pk::get_name(base));
                if (is_exceed_troops or is_exceed_weapon)
                    pk::info(pk::format("---{}/{}대 진입시 재고초과", base_name, unit_name));
            }
            bool is_exceed_unit = (is_exceed_troops or is_exceed_weapon);
            return is_exceed_unit;
        }
        
        // 부대의 이동범위 내에 목표거점이 위치하는지 확인
        bool check_base_in_movable_range(pk::unit@ unit, pk::building@ base)
        {
            if (!pk::is_alive(unit) or !pk::is_alive(base)) return false;
            
            pk::array<pk::point> arr_range = pk::get_movable_pos(unit);;
            for (int i = 0; i < int(arr_range.length); i++)
            {
                if (base.pos == arr_range[i]) return true;
            }
            return false;
        }
        
        bool is_siege_weapon(int weapon_id) { return (병기_충차 <= weapon_id and weapon_id <= 병기_목수); }
        bool is_ship_weapon(int weapon_id) { return (병기_누선 == weapon_id or weapon_id == 병기_투함); }
        
        
        //---------------------------------------------------------------------------
        //---------------------------------------------------------------------------
        
        // 정상적인 부대인지 확인
        bool check_valid_unit(pk::unit@ unit_t)
        {
            if (!pk::is_alive(unit_t))      return false;
			if (unit_t.type != 부대종류_전투)	return false;	// 수송 부대 제외
            
            int force_id = unit_t.get_force_id();
            pk::force@ force = pk::get_force(force_id);
			if (!pk::is_alive(force) or !pk::is_normal_force(force_id)) return false;  // 소속 세력 확인  
			if (!pk::is_alive(pk::get_building(pk::get_service(unit_t))))	return false;	// 소속거점 확인불가 제외
            
            int leader_id = unit_t.leader;
            if ((leader_id >= 670 and leader_id < 800) or (leader_id >= 1000 and leader_id < 1100)) return false;
            
            return true;
        }
        
        
        // 세력 확인 함수
        bool check_force_option(pk::unit@ unit_t)
        {
            // 플레이어 군단 미적용 (유저의 임무지정 무시하면서 목표재설정하므로 미적용 권장)
            if (!pk::is_alive(unit_t)) return false;
            if (pk::is_player_controlled(unit_t)) 
            {
                if (부대목표변경_유저군단적용) return true;
                else return false;   
            }
            
            // 0: 컴퓨터AI 와 플레이어_위임군단 모두,  1: 플레이어_위임군단만, 2: 컴퓨터AI만,  3: 모두 미적용
            if      (부대목표변경_세력조건 == 0 and !pk::is_player_controlled(unit_t)) return true;
            else if (부대목표변경_세력조건 == 1 and unit_t.is_player() and !pk::is_player_controlled(unit_t)) return true;
            else if (부대목표변경_세력조건 == 2 and !unit_t.is_player()) return true;
            else if (부대목표변경_세력조건 == 3) return false;
            
            return false;
        }
        
        // 건설편제 여부 판단 함수
        bool check_construction_unit(pk::unit@ unit)
        {
            if (!pk::is_alive(unit)) return false;
            if (pk::is_player_controlled(unit)) return false; // 유저군단은 무조건 제외
            if (unit.has_skill(특기_축성) and unit.gold >= 건설편제_기준소지금) return true;  // 축성 특기
            if (unit.type == 부대종류_전투 and pk::get_member_count(unit) <= 1)   // 1인대
            {
                if (unit.gold >= 건설편제_기준소지금 and unit.troops <= 건설편제_기준병력) 
                    return true; 
            }
            if (건설편제_임무우대 and unit.order == 부대임무_설치 and unit.target_type == 부대임무대상_좌표)
            {
                int facility_id = unit.target;
                pk::facility@ facility = pk::get_facility(facility_id);
                if (pk::is_alive(facility) and int(unit.gold) >= int(facility.gold_cost))
                {
                    if (시설_진 <= facility_id and facility_id <= 시설_석병팔진)
                        return true;
                }
            }
            
            return false;
        }
        
        // 계략부대 여부 판단 함수
        int func_strategy_unit_type(pk::unit@ unit)
        {
            if (!pk::is_alive(unit)) return -1;
            if (pk::is_player_controlled(unit)) return -1; // 유저군단은 무조건 제외
            
            // 무조건 우대 특기
            if (unit.has_skill(특기_신산) or unit.has_skill(특기_허실) or unit.has_skill(특기_백출) 
                or unit.has_skill(특기_귀모) or unit.has_skill(특기_연환))
                return 3;
            
            // 보유 특기 확인
            for (int i = 0; i < 3; i++)
            {
                pk::person@ member = pk::get_person(unit.member[i]);
                if (pk::is_alive(member))
                {
                    int skill_id = member.skill;
                    pk::skill@ skill = pk::get_skill(skill_id);
                    
                    // 신/장 계열 공격특기인 경우 계략부대 아닌 것으로 판정 (지력공방비 무시)
                    if (skill_id >= 특기_창장 and skill_id <= 특기_맹장) return 0;   
                    
                    // 계략특기 우대
                    if (계략부대_특기우대 and pk::is_alive(skill))
                    {
                        if (skill.type == 특기종류_계략) return 2;    
                    }
                }
            }
            
            // 지력 대 공방 비율 판단 (일반부대)
            float stat_ratio = float(2.0f * unit.attr.stat[부대능력_지력] / (unit.attr.stat[부대능력_공격] + unit.attr.stat[부대능력_방어]));
            if (stat_ratio >= 계략부대_지력공방비) return 1;
            
            return 0;
        }
        
        
        //---------------------------------------------------------------------------
        
        // 부대 공격 최소,최대 사거리 함수 -- 신규 추가, 사용가능한 전법의 세팅조건에 따라 계산 ('20.9.13)
        pk::int_int get_atk_range(pk::unit@ unit)
        {
            pk::int_int atk_range = pk::int_int(1, 1);
            if (!pk::is_alive(unit) or unit.weapon == 병기_검) return atk_range;
        
            int weapon_id = unit.weapon;
            pk::equipment@ epq = pk::get_equipment(unit.weapon);
            string eqp_name = pk::decode(pk::get_name(epq));
            string info = pk::format("{}", eqp_name);
            
            int min_range = 5;
            int max_range = 1;
            
            for (int j = 0; j < 전법_끝; j++)
            {
                if (epq.tactics[j])
                {
                    pk::tactics@ tts = pk::get_tactics(j);
                    string tts_name = pk::decode(pk::get_name(tts));
                    info += pk::format(" {}({},{})", tts_name, tts.min_range, tts.max_range);
                    min_range = pk::min(min_range, tts.min_range);
                    max_range = pk::max(max_range, tts.max_range);
                }
            }
            if (weapon_id == 병기_노 and unit.has_tech(기교_강노)) max_range += 1;
            if (weapon_id == 병기_군마 and (unit.has_tech(기교_기사) or unit.has_skill(특기_백마))) max_range = pk::max(2, max_range);
            if ((weapon_id == 병기_정란 or weapon_id == 병기_투석) and unit.has_skill(특기_사정)) max_range += 1;
            
            atk_range = pk::int_int(min_range, max_range);
            info += pk::format(": 최소({}),최대({})", min_range, max_range);
            
            //if (디버그모드) pk::info(info);
            
            return atk_range;
        }
        
        // 부대 공격 최대 사거리 함수
        int get_max_atk_range(pk::unit@ unit)
        {
            if (!pk::is_alive(unit)) return 1;
            
            int weapon_id = unit.weapon;
            int max_range = 0;
            
            if      (weapon_id == 병기_노)     max_range = (unit.has_tech(기교_강노))? 3 : 2;
            else if (weapon_id == 병기_군마)   max_range = (unit.has_tech(기교_기사) or unit.has_skill(특기_백마))? 2 : 1;
            else if (weapon_id == 병기_정란)   max_range = ((unit.has_skill(특기_사정))? 1 : 0) + (pk::get_tactics(전법_공성화시).max_range);
            else if (weapon_id == 병기_투석)   max_range = ((unit.has_skill(특기_사정))? 1 : 0) + (pk::get_tactics(전법_공성투석).max_range);
            else if (weapon_id >= 병기_주가)   max_range = 2;
            else                             max_range = 1;     // 검, 창, 극, 목수 등
            
            return max_range;
        }
        
        // 목표부대 가중치 계산 함수 (상성, 적성, 방어력, 신분 고려)
        float get_attr_weight(pk::unit@ unit)
        {
            if (!pk::is_alive(unit)) return 0.0f;
            int weapon_id  = unit.weapon;
            int heishu_id  = pk::equipment_id_to_heishu(weapon_id);
            int tekisei    = pk::min(적성_S, pk::get_tekisei(unit));
            int unit_atk   = unit.attr.stat[부대능력_공격];
            int unit_def   = unit.attr.stat[부대능력_방어];
            int unit_skill = func_strategy_unit_type(unit);
            
            if (heishu_id < 0 or heishu_id >= 6) return 0.0f;
            
            float relative_stat = 0.0f;
            float weight  = main.heishu_weight[heishu_id] ;
            
            // 상성, 적성 가중치 적용
            relative_stat = pk::max(0.f, weight) + float(적성_끝 - tekisei)/float(적성_끝) ;
            
            // 공격력 가중치 적용
            if (부대목표변경_공격가중치적용) relative_stat += float(unit_atk)/128.0f;
            // 방여력 가중치 적용
            if (부대목표변경_방어가중치적용) relative_stat += float(unit_def)/128.0f;
                        
            // 군주/도독 신분 가중치 적용
            if (부대목표변경_신분가중치적용)
            {
                if      (unit.leader == pk::get_kunshu_id(unit)) relative_stat += 0.50f;
                else if (unit.leader == pk::get_totoku_id(unit)) relative_stat += 0.25f;
            }
            
            // 병력 가중치 적용 ('19.3.1)
            if (부대목표변경_병력가중치적용)
            {
                if (int(unit.troops) <= 5000)
                    relative_stat += float(5000 - unit.troops)/10000.f;
            }
            
            // 계략우대 특기 보유 가중치 적용 ('20.8.30)
            if (부대목표변경_계략가중치적용 and (unit_skill > 1)) relative_stat += 0.4f * float(unit_skill);
            
            return relative_stat;
        }
        
        // 병종상성 설정함수
        void set_heishu_weight(int weapon_id)
        {
            int heishu_id = pk::equipment_id_to_heishu(weapon_id);
            
            if (heishu_id == 병종_창병)
            {
                heishu_weight[병종_창병] = heishu_normal;
                heishu_weight[병종_극병] = heishu_weak  ;
                heishu_weight[병종_노병] = heishu_normal;
                heishu_weight[병종_기병] = heishu_strong;
                heishu_weight[병종_병기] = heishu_strong;
                heishu_weight[병종_수군] = heishu_null  ;
            }
            else if (heishu_id == 병종_극병)
            {        
                heishu_weight[병종_창병] = heishu_strong;
                heishu_weight[병종_극병] = heishu_normal;
                heishu_weight[병종_노병] = heishu_normal;
                heishu_weight[병종_기병] = heishu_weak  ;
                heishu_weight[병종_병기] = heishu_strong;
                heishu_weight[병종_수군] = heishu_null  ;
            }
            else if (heishu_id == 병종_노병)
            {  
                heishu_weight[병종_창병] = heishu_normal;
                heishu_weight[병종_극병] = heishu_weak  ;
                heishu_weight[병종_노병] = heishu_normal;
                heishu_weight[병종_기병] = heishu_strong;
                heishu_weight[병종_병기] = heishu_strong;
                heishu_weight[병종_수군] = heishu_normal;
            }
            else if (heishu_id == 병종_기병)
            { 
                heishu_weight[병종_창병] = heishu_weak  ;
                heishu_weight[병종_극병] = heishu_strong;
                heishu_weight[병종_노병] = heishu_strong;
                heishu_weight[병종_기병] = heishu_normal;
                heishu_weight[병종_병기] = heishu_strong;
                heishu_weight[병종_수군] = heishu_null  ;
            }
            else if (heishu_id == 병종_병기)
            { 
                heishu_weight[병종_창병] = heishu_normal;
                heishu_weight[병종_극병] = heishu_normal;
                heishu_weight[병종_노병] = heishu_normal;
                heishu_weight[병종_기병] = heishu_normal;
                heishu_weight[병종_병기] = heishu_normal;
                heishu_weight[병종_수군] = heishu_null  ;
            }
            else if (heishu_id == 병종_수군)
            { 
                heishu_weight[병종_창병] = heishu_normal;
                heishu_weight[병종_극병] = heishu_normal;
                heishu_weight[병종_노병] = heishu_normal;
                heishu_weight[병종_기병] = heishu_normal;
                heishu_weight[병종_병기] = heishu_weak  ;
                heishu_weight[병종_수군] = heishu_strong;
            }
            else
            { 
                heishu_weight[병종_창병] = heishu_weak  ;
                heishu_weight[병종_극병] = heishu_weak  ;
                heishu_weight[병종_노병] = heishu_weak  ;
                heishu_weight[병종_기병] = heishu_weak  ;
                heishu_weight[병종_병기] = heishu_normal;
                heishu_weight[병종_수군] = heishu_null  ;
            }
        }
        
        
        //---------------------------------------------------------------------------
        //---------------------------------------------------------------------------
        
        int get_weapon_type (int weapon_id)
        {
            int weapon_type = -1;
            if      (weapon_id == 병기_검)                          weapon_type = 0;
            else if (weapon_id >= 병기_창 and weapon_id <= 병기_군마)  weapon_type = 1;
            else if (weapon_id == 병기_충차)                         weapon_type = 2;
            else if (weapon_id >= 병기_정란 and weapon_id <= 병기_목수) weapon_type = 3;
            else if (weapon_id == 병기_주가)                         weapon_type = 4;
            else if (weapon_id >  병기_주가)                         weapon_type = 5;
            
            return weapon_type;
        }
        
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
                default     : weapon_name = "??"; break;
            }
            return weapon_name;
        }
        
        
        string get_tekisei_name(int tekisei)
        {
            string tekisei_name;
            switch(tekisei)
            {
                case 적성_C  : tekisei_name = "C"; break;
                case 적성_B  : tekisei_name = "B"; break;
                case 적성_A  : tekisei_name = "A"; break;
                case 적성_S  : tekisei_name = "S"; break;
                default    : tekisei_name = "?"; break;
            }
            return tekisei_name;
        }
        
        
        string get_heishu_color(int weapon_id)
        {
            string text_color;
            float weight  = main.heishu_weight[pk::equipment_id_to_heishu(weapon_id)];
            
            if      (weapon_id == 병기_검)      text_color = "\x1b[2x"; // 녹색
            else if (weight == heishu_null  ) text_color = "\x1b[29x"; // 빨강
            else if (weight == heishu_weak  ) text_color = "\x1b[16x"; // 주황
            else if (weight == heishu_normal) text_color = "\x1b[17x"; // 노랑
            else if (weight == heishu_strong) text_color = "\x1b[2x"; // 녹색
            else                              text_color = "\x1b[0x"; // 흰색
                
            return text_color;
        }
        
        //---------------------------------------------------------------------------
        
        void clear_target_info()
        {
            for (int i = 0; i < 부대_끝; i++)
            {
                arr_target_unit_id[i] = -1;
                arr_target_base_id[i] = -1;
            }
        }
        
        //---------------------------------------------------------------------------------------
        
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

