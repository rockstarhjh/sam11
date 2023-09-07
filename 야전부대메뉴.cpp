/*
@ 만든이: 기마책사
@ UPDATE: '18.11.4   /  최초적용: 계략_공작/도발/고무/대고무/회귀, 부대해산/병합
@ UPDATE: '18.11.8   /  변경내용: 계략_욕설 추가, 계략사용 특기조건 반영
@ UPDATE: '18.11.14  /  변경내용: 게략_기습 추가, 강행군추가
@ UPDATE: '18.11.24  /  변경내용: 계략_도발 통합(욕설삭제)+설전추가, 계략_기습 수상 추가, 부대해산/병합 실행가능 병력기준 변경, NPC부대 지력차계산 추가
@ UPDATE: '18.11.25  /  변경내용: 스크립트 구조변경, 부대설전 버그개선을 위하여 trigger 방식채용
@ UPDATE: '18.11.30  /  변경내용: 계략_기습 버그방지조건 추가, 부대_해산 기준값 오류수정
@ UPDATE: '18.12.3   /  변경내용: 계략_기습 빈칸없는 목표부대 검색 오류수정, 계략_도발 발동오류 개선 및 불러오기 실행 시 초기화 추가
@ UPDATE: '18.12.12  /  변경내용: 계략_기습 기력소모 수정, shift+우클릭 메뉴 무한행동 사용시 오류 수정, 부대_해산/병합 주변적군 확인조건 추가
@ UPDATE: '18.12.21  /  변경내용: 부대_병합 설명수정, 계략_낙석 추가
@ UPDATE: '18.12.23  /  변경내용: 부대_해산/병합 주위의적 검색함수 오류 수정
@ UPDATE: '18.12.30  /  변경내용: 계략_도발 특기_논객 우대 적용, 부대_재편 추가 (주장변경기능), 계략_공작 적시설 탈취 기능 추가
*/

namespace 야전부대메뉴
{
    
    //---------------------------------------------------------------------------------------
    // 유저 설정 (true = on, false = off)
    
    // 계략 메뉴 추가여부 설정
    const bool 메뉴_계략_사용  = true;    // Custom 계략 에 대한 Master 설정 (false 시 모든 계략 off)
    const bool 계략_기습_사용  = true;    // 육상부대의 인근 적 부대 기습 : 특기_급습 우대 ('18.11.13)
    
    const bool 계략_도발_사용  = true;    // 적 태수 도발하여 출성 유도, 도발된 부대의 사기 저하 및 공격 유도 ('18.11.9)
    const bool 계략_도발_설전설정 = true;  //  발도/도발된 부대 간 설전을 벌임 ('18.11.24)
    const bool 계략_도발_설전보기 = true;  //  발도/도발된 부대 간 설전을 볼지 여부를 확인하기
    
    const bool 계략_공작_사용  = true;    // 적 건물 내구도 감소 ('18.11.9)
    const bool 계략_공작_탈취  = true;    // 적 시설에 대해 공작 성공 시 시설 탈취 ('18.12.26)
    
    const bool 계략_낙석_사용  = true;    // 산악지형에서 낙석 실행 ('18.12.21)
    
    const bool 계략_고무_사용  = true;    // 아군 1부대 기력 회복 ('18.11.6)
    const bool 계략_대고무_사용 = true;    // 아군 복수부대 기력 회복 ('18.11.6)
    const bool 계략_회귀_사용  = true;    // 아군 부대 재행동 : 군주 또는 도독 사용 가능 ('18.11.6)
    
    // 부대 메뉴 추가여부 설정
    const bool 메뉴_부대_사용  = true;    // Custom 부대메뉴에 대한 Master 설정 (false 시 모든 부대메뉴 off)
    const bool 부대_해산_사용  = true;    // 2천명 이상 부대 강제 해산 ('18.11.9)
    const bool 부대_병합_사용  = true;    // 동일 병과부대 인접 시 병력 인계 ('18.11.6)
    const bool 부대_회복_사용  = true;    // 금을 소비하여 병력 회복 ('18.11.6)
    const bool 부대_재편_사용  = true;    // 부대의 주장 변경 ('18.12.26)
    
    // 강행군 메뉴 설정
    const bool 메뉴_강행군_사용  = true;   // 기력 추가 소비하여 추가 이동 실시 ('18.11.13)
    
    // 계략에 대한 특기 옵션
    const bool 계략_특기_설정  = true;        // 계략에 대한 특기 설정 사용
    const bool 백출_반감_설정  = true;        // true= 50% 소비, false = 무조건 1 소비
    const bool 계략_병력_차등  = true;        // 병력수에 따른 계략 소비기력 차등 적용
    
    // 강행군 실행 조건
    const int ENERGY_MIN_강행군 = 50;       // 강행군을 실행하기 위한 최소 기력
    const float MOVEMENT_강행군  = 0.6f;    // [강행군_이동력]/[부대_이동력] 비율 
    
    // 계략 실행 조건
	const int ENERGY_COST_기습 = 15;        
	const int ENERGY_COST_낙석 = 40;        
	const int ENERGY_COST_도발 = 15;
	const int ENERGY_COST_도발설전 = 15;
	const int ENERGY_COST_파괴공작 = 15;
	const int CHANCE_공작탈취확률 = 20;    // 적의 시설에 대해 공작 성공 시 시설 탈취 확률 (0 ~ 100 설정)
	const int ENERGY_COST_고무  = 10;
	const int ENERGY_COST_대고무 = 20;
	const int ENERGY_COST_회귀 = 30;
    // 부대 실행 조건
	const int GOLD_COST_병합  = 500;   // 아직 사용안하는 조건    
	const int GOLD_COST_회복  = 300;
    
    //---------------------------------------------------------------------------------------

    
	class Main
	{
		Main()
		{
            // 부대 경험치 획득 트리거
            unit_debate_list.clear();
            pk::bind(173, pk::trigger173_t(onUnitExpAdd)); 
            pk::bind(111, pk::trigger111_t(onTurnStart)); 
            pk::bind(112, pk::trigger112_t(onTurnEnd)); 
            pk::bind(102, pk::trigger102_t(onGameInit));
            
            // 계략 메뉴 추가
            add_menu_stragety();
            
            // 부대 메뉴 추가
            add_menu_unit_order();
            
        }
        
        pk::unit@ src_unit;
        pk::unit@ dst_unit;
        pk::point src_pos_;
        pk::point dst_pos_;
        
        pk::unit@ src_unit_debate;
        pk::unit@ dst_unit_debate;
        
        pk::list<pk::unit@> unit_debate_list;
        int debate_result;
    
        void add_menu_stragety()
        {
            //-------------------------------------------------------------
            if (메뉴_계략_사용)
            {
                // 낙석 : 산악지형에서 낙석 실행
                if (계략_낙석_사용)
                {
                    pk::menu_item 계략_낙석;
                    계략_낙석.menu = 115;
                    계략_낙석.init = pk::unit_menu_item_init_t(init);
                    계략_낙석.get_text = pk::menu_item_get_text_t(getText_계략_낙석);
                    계략_낙석.get_desc = pk::menu_item_get_desc_t(getDesc_계략_낙석);
                    계략_낙석.is_visible = pk::menu_item_is_visible_t(isVisible_계략_낙석);
                    계략_낙석.is_enabled = pk::menu_item_is_enabled_t(isEnabled_계략_낙석);
                    계략_낙석.get_targets = pk::unit_menu_item_get_targets_t(getTargets_계략_낙석);
                    계략_낙석.get_chance = pk::unit_menu_item_get_chance_t(getChance_낙석);
                    계략_낙석.handler = pk::unit_menu_item_handler_t(handler_계략_낙석);
                    pk::add_menu_item(계략_낙석);
                }
                
                // 기습 : 근처의 적부대를 기습 공격
                if (계략_기습_사용)
                {
                    pk::menu_item 계략_기습;
                    계략_기습.menu = 115;
                    계략_기습.init = pk::unit_menu_item_init_t(init);
                    계략_기습.get_text = pk::menu_item_get_text_t(getText_계략_기습);
                    계략_기습.get_desc = pk::menu_item_get_desc_t(getDesc_계략_기습);
                    계략_기습.is_visible = pk::menu_item_is_visible_t(isVisible_계략_기습);
                    계략_기습.is_enabled = pk::menu_item_is_enabled_t(isEnabled_계략_기습);
                    계략_기습.get_targets = pk::unit_menu_item_get_targets_t(getTargets_계략_기습);
                    계략_기습.get_chance = pk::unit_menu_item_get_chance_t(getChance_100);
                    계략_기습.handler = pk::unit_menu_item_handler_t(handler_계략_기습);
                    pk::add_menu_item(계략_기습);
                }
                
                // 도발 : 적 거점 태수의 출성을 유도
                if (계략_도발_사용)
                {
                    pk::menu_item 계략_도발;
                    계략_도발.menu = 115;
                    계략_도발.init = pk::unit_menu_item_init_t(init);
                    계략_도발.get_text = pk::menu_item_get_text_t(getText_계략_도발);
                    계략_도발.get_desc = pk::menu_item_get_desc_t(getDesc_계략_도발);
                    계략_도발.is_visible = pk::menu_item_is_visible_t(isVisible_계략_도발);
                    계략_도발.is_enabled = pk::menu_item_is_enabled_t(isEnabled_계략_도발);
                    계략_도발.get_targets = pk::unit_menu_item_get_targets_t(getTargets_계략_도발);
                    계략_도발.get_chance = pk::unit_menu_item_get_chance_t(getChance_도발);
                    계략_도발.handler = pk::unit_menu_item_handler_t(handler_계략_도발);
                    pk::add_menu_item(계략_도발);
                }
                
                // 파괴 : 적 거점 내구도 파괴
                if (계략_공작_사용)
                {
                    pk::menu_item 계략_파괴공작;
                    계략_파괴공작.menu = 115;
                    계략_파괴공작.init = pk::unit_menu_item_init_t(init);
                    계략_파괴공작.get_text = pk::menu_item_get_text_t(getText_계략_파괴공작);
                    계략_파괴공작.get_desc = pk::menu_item_get_desc_t(getDesc_계략_파괴공작);
                    계략_파괴공작.is_visible = pk::menu_item_is_visible_t(isVisible_계략_파괴공작);
                    계략_파괴공작.is_enabled = pk::menu_item_is_enabled_t(isEnabled_계략_파괴공작);
                    계략_파괴공작.get_targets = pk::unit_menu_item_get_targets_t(getTargets_계략_파괴공작);
                    계략_파괴공작.get_chance = pk::unit_menu_item_get_chance_t(getChance_파괴공작);
                    계략_파괴공작.handler = pk::unit_menu_item_handler_t(handler_계략_파괴공작);
                    pk::add_menu_item(계략_파괴공작);
                }
                
                // 고무 : 1부대 기력 회복
                if (계략_고무_사용)
                {
                    pk::menu_item 계략_고무;
                    계략_고무.menu = 115;
                    계략_고무.init = pk::unit_menu_item_init_t(init);
                    계략_고무.get_text = pk::menu_item_get_text_t(getText_계략_고무);
                    계략_고무.get_desc = pk::menu_item_get_desc_t(getDesc_계략_고무);
                    계략_고무.is_visible = pk::menu_item_is_visible_t(isVisible_계략_고무);
                    계략_고무.is_enabled = pk::menu_item_is_enabled_t(isEnabled_계략_고무);
                    계략_고무.get_targets = pk::unit_menu_item_get_targets_t(getTargets_계략_고무);
                    계략_고무.get_chance = pk::unit_menu_item_get_chance_t(getChance_100);
                    계략_고무.handler = pk::unit_menu_item_handler_t(handler_계략_고무);
                    pk::add_menu_item(계략_고무);
                }
                
                // 대고무 : 대상+주위부대 기력 회복
                if (계략_대고무_사용)
                {
                    pk::menu_item 계략_대고무;
                    계략_대고무.menu = 115;
                    계략_대고무.init = pk::unit_menu_item_init_t(init);
                    계략_대고무.get_text = pk::menu_item_get_text_t(getText_계략_대고무);
                    계략_대고무.get_desc = pk::menu_item_get_desc_t(getDesc_계략_대고무);
                    계략_대고무.is_visible = pk::menu_item_is_visible_t(isVisible_계략_대고무);
                    계략_대고무.is_enabled = pk::menu_item_is_enabled_t(isEnabled_계략_대고무);
                    계략_대고무.get_targets = pk::unit_menu_item_get_targets_t(getTargets_계략_대고무);
                    계략_대고무.get_chance = pk::unit_menu_item_get_chance_t(getChance_100);
                    계략_대고무.handler = pk::unit_menu_item_handler_t(handler_계략_대고무);
                    pk::add_menu_item(계략_대고무);
                }
                  
                // 회귀 : 기력 대폭 사용하여 행동완료 아군부대 재행동
                if (계략_회귀_사용)
                {
                    pk::menu_item 계략_회귀;
                    계략_회귀.menu = 115;
                    계략_회귀.init = pk::unit_menu_item_init_t(init);
                    계략_회귀.get_text = pk::menu_item_get_text_t(getText_계략_회귀);
                    계략_회귀.get_desc = pk::menu_item_get_desc_t(getDesc_계략_회귀);
                    계략_회귀.is_visible = pk::menu_item_is_visible_t(isVisible_계략_회귀);
                    계략_회귀.is_enabled = pk::menu_item_is_enabled_t(isEnabled_계략_회귀);
                    계략_회귀.get_targets = pk::unit_menu_item_get_targets_t(getTargets_계략_회귀);
                    계략_회귀.get_chance = pk::unit_menu_item_get_chance_t(getChance_100);
                    계략_회귀.handler = pk::unit_menu_item_handler_t(handler_계략_회귀);
                    pk::add_menu_item(계략_회귀);
                }
            }
        }
            
        void add_menu_unit_order()
        {
            //-------------------------------------------------------------
            // 강행군 : 기력을 소비하여 추가 이동
            if (메뉴_강행군_사용)
            {
                pk::menu_item 메뉴_강행군;
                메뉴_강행군.menu = 1;
                메뉴_강행군.init = pk::unit_menu_item_init_t(init);
                메뉴_강행군.get_text = pk::menu_item_get_text_t(getText_메뉴_강행군);
                메뉴_강행군.get_desc = pk::menu_item_get_desc_t(getDesc_메뉴_강행군);
                메뉴_강행군.is_visible = pk::menu_item_is_visible_t(isVisible_메뉴_강행군);
                메뉴_강행군.is_enabled = pk::menu_item_is_enabled_t(isEnabled_메뉴_강행군);
                메뉴_강행군.get_targets = pk::unit_menu_item_get_targets_t(getTargets_메뉴_강행군);
                메뉴_강행군.get_chance = pk::unit_menu_item_get_chance_t(getChance_100);
                메뉴_강행군.handler = pk::unit_menu_item_handler_t(handler_메뉴_강행군);
                pk::add_menu_item(메뉴_강행군);
            }
            
            
            //-------------------------------------------------------------
            if (메뉴_부대_사용)
            {
                pk::menu_item 부대;
                int 부대_상위;

                부대.menu = 1;
                부대.get_text = cast<pk::menu_item_get_text_t@>(function() { return pk::encode("부대"); });
                부대_상위 = pk::add_menu_item(부대);
                
                // 부대메뉴 : 해산
                if (부대_해산_사용)
                {
                    pk::menu_item 부대_해산;
                    부대_해산.menu = 부대_상위;
                    부대_해산.init = pk::unit_menu_item_init_t(init);
                    부대_해산.get_text = pk::menu_item_get_text_t(getText_부대_해산);
                    부대_해산.get_desc = pk::menu_item_get_desc_t(getDesc_부대_해산);
                    부대_해산.is_visible = pk::menu_item_is_visible_t(isVisible_부대_해산);
                    부대_해산.is_enabled = pk::menu_item_is_enabled_t(isEnabled_부대_해산);
                    부대_해산.get_targets = pk::unit_menu_item_get_targets_t(getTargets_부대_해산);
                    부대_해산.get_chance = pk::unit_menu_item_get_chance_t(getChance_100);
                    부대_해산.handler = pk::unit_menu_item_handler_t(handler_부대_해산);
                    pk::add_menu_item(부대_해산);
                }
                
                // 부대메뉴 : 병합
                if (부대_병합_사용)
                {
                    pk::menu_item 부대_병합;
                    부대_병합.menu = 부대_상위;
                    부대_병합.init = pk::unit_menu_item_init_t(init);
                    부대_병합.get_text = pk::menu_item_get_text_t(getText_부대_병합);
                    부대_병합.get_desc = pk::menu_item_get_desc_t(getDesc_부대_병합);
                    부대_병합.is_visible = pk::menu_item_is_visible_t(isVisible_부대_병합);
                    부대_병합.is_enabled = pk::menu_item_is_enabled_t(isEnabled_부대_병합);
                    부대_병합.get_targets = pk::unit_menu_item_get_targets_t(getTargets_부대_병합);
                    부대_병합.get_chance = pk::unit_menu_item_get_chance_t(getChance_100);
                    부대_병합.handler = pk::unit_menu_item_handler_t(handler_부대_병합);
                    pk::add_menu_item(부대_병합);
                }
                
                // 회복 : 소지금 사용하여 1부대 병력 회복
                if (부대_회복_사용)
                {
                    pk::menu_item 부대_회복;
                    부대_회복.menu = 부대_상위;
                    부대_회복.init = pk::unit_menu_item_init_t(init);
                    부대_회복.get_text = pk::menu_item_get_text_t(getText_부대_회복);
                    부대_회복.get_desc = pk::menu_item_get_desc_t(getDesc_부대_회복);
                    부대_회복.is_visible = pk::menu_item_is_visible_t(isVisible_부대_회복);
                    부대_회복.is_enabled = pk::menu_item_is_enabled_t(isEnabled_부대_회복);
                    부대_회복.get_targets = pk::unit_menu_item_get_targets_t(getTargets_부대_회복);
                    부대_회복.get_chance = pk::unit_menu_item_get_chance_t(getChance_100);
                    부대_회복.handler = pk::unit_menu_item_handler_t(handler_부대_회복);
                    pk::add_menu_item(부대_회복);
                }
                
                // 재편 : 부대 주장을 변경
                if (부대_재편_사용)
                {
                    pk::menu_item 부대_재편;
                    부대_재편.menu = 부대_상위;
                    부대_재편.init = pk::unit_menu_item_init_t(init);
                    부대_재편.get_text = pk::menu_item_get_text_t(getText_부대_재편);
                    부대_재편.get_desc = pk::menu_item_get_desc_t(getDesc_부대_재편);
                    부대_재편.is_visible = pk::menu_item_is_visible_t(isVisible_부대_재편);
                    부대_재편.is_enabled = pk::menu_item_is_enabled_t(isEnabled_부대_재편);
                    부대_재편.get_targets = pk::unit_menu_item_get_targets_t(getTargets_부대_재편);
                    부대_재편.get_chance = pk::unit_menu_item_get_chance_t(getChance_100);
                    부대_재편.handler = pk::unit_menu_item_handler_t(handler_부대_재편);
                    pk::add_menu_item(부대_재편);
                }
                
                
            }
            
            
		}

        //---------------------------------------------------------------------------
        
        void onUnitExpAdd(pk::unit@ unit, int type)
        {
            if (pk::is_campaign()) return;
            
            // 부대가 경험치 획득했을 때, 설전할 부대리스트에 있을 시 설전 발동
            if (unit_debate_list.contains(unit))
            {
                pk::scene(pk::scene_t(scene_도발설전)); // 설전 애니메이션 불러오기
                func_debate_result();                 // 부대설전 결과 반영
                
                unit_debate_list.clear();               // 리스트 초기화
            }
            
        }
        void onTurnStart(pk::force@ force) 
        {
            if (pk::is_campaign()) return;
            unit_debate_list.clear();               // 리스트 초기화
        }
        void onTurnEnd(pk::force@ force)
        {
            if (pk::is_campaign()) return;
            unit_debate_list.clear();               // 리스트 초기화
        }
        void onGameInit()
        {
            if (pk::is_campaign()) return;
            unit_debate_list.clear();               // 리스트 초기화
        }
        
        
        //---------------------------------------------------------------------------
        //---------------------------------------------------------------------------
        
		void init(pk::unit@ unit, pk::point src_pos)
		{
			@src_unit = @unit;
			src_pos_ = src_pos;
		}
        
		int getChance_100(pk::point dst_pos)
		{
			return 100;
		}
        
        //---------------------------------------------------------------------------
        // 계략 설정 관련 함수
        //---------------------------------------------------------------------------
        uint8 func_stragety_cost(int energy_cost)
        {
            if (!계략_특기_설정) return energy_cost;
            
            uint8 n = uint8(energy_cost);
            if (src_unit.has_skill(특기_백출))
            {
                if (백출_반감_설정)
                    n /= 2; // 기력 소모량 절반 감소
                else
                    n = 1;  // 기력 소모량 무조건 1로
            }
            
            //병력수에 따른 기력 소모량 차등 - 소부대 기력 소모 증가, 대부대 기력 소모 감소
            if (계략_병력_차등)
            {
                if (src_unit.troops <= 2000)
                    n = uint8(n * pk::min(10.f, 2000.f/src_unit.troops));         // 최대 10배 소모
                else if (src_unit.troops >= 10000)
                    n = uint8(n * pk::max(0.5f, (2-src_unit.troops/10000.f)));    // 최소 50% 소모
            }
            
            return n;
        }
        
        bool func_priority(pk::point dst_pos)
		{
            if (!계략_특기_설정) return false;
            
            if (src_unit.has_skill(특기_신산))
                return true;
            
			pk::unit@ dst_unit = pk::get_unit(dst_pos);
            if (pk::is_alive(dst_unit))
            {
                if (src_unit.has_skill(특기_허실) and (src_unit.attr.stat[부대능력_지력] > dst_unit.attr.stat[부대능력_지력]))
                    return true;
            }
            else if (!pk::is_alive(dst_unit) and pk::get_building(dst_pos) is null and src_unit.has_skill(특기_허실))
                return true;
        
            return false;
        }
        
        int func_range_add()
		{
            if (!계략_특기_설정) return 0;
            
            if (src_unit.has_skill(특기_귀모))
                return 1;
            
            return 0;
        }
        
        //---------------------------------------------------------------------------
        
        bool call_stragety_chance(pk::point dst_pos, int strategy_id)
        {
            int chance = (pk::int_bool(cast<pk::func206_t>(pk::get_func(206))(src_unit, src_pos_, dst_pos, strategy_id))).first;
            return pk::rand_bool(chance);
        }
        
        
        //---------------------------------------------------------------------------
        // 계략_고무 (삼국지 조조전 오마쥬)
        //---------------------------------------------------------------------------

		string getText_계략_고무()
		{
			return pk::encode(pk::format("고무 ({})", func_stragety_cost(ENERGY_COST_고무)));
		}

		string getDesc_계략_고무()
		{
            if (pk::get_person(src_unit.leader).rank >= 관직_없음 and pk::get_person(src_unit.leader).mibun == 신분_일반 )
                return pk::encode("관직이 없는 장수는 실행할 수 없습니다");
			else if (src_unit.energy < func_stragety_cost(ENERGY_COST_고무))
				return pk::encode("기력이 부족합니다");
			else if (getTargets_계략_고무().length == 0)
				return pk::encode("범위내에 아군부대가 없습니다");
			else
				return pk::encode("기력을 소모하여 다른 아군부대의 기력을 회복합니다");
		}
        
        bool isVisible_계략_고무()
		{
            if (pk::is_campaign()) return false;
            if (pk::get_person(src_unit.leader).rank >= 관직_없음 and pk::get_person(src_unit.leader).mibun == 신분_일반) return false;
            return true;
        }
        
		bool isEnabled_계략_고무()
		{
            if (pk::get_person(src_unit.leader).rank >= 관직_없음 and pk::get_person(src_unit.leader).mibun == 신분_일반) return false;
			else if (src_unit.energy < func_stragety_cost(ENERGY_COST_고무)) return false;
			return getTargets_계략_고무().length > 0;
		}
        
		pk::array<pk::point_int> getTargets_계략_고무()
		{
			pk::array<pk::point_int> target_units;
			auto range = pk::range(src_pos_, 1, 1 + func_range_add());
			for (int i = 0; i < int(range.length); i++)
			{
				auto dst_unit = pk::get_unit(range[i]);
				if (dst_unit !is null and src_unit.pos != dst_unit.pos and src_unit.get_force_id() == dst_unit.get_force_id())
					target_units.insertLast(pk::point_int(range[i], 1));
			}
			return target_units;
		}

		bool handler_계략_고무(pk::point dst_pos)
		{
			pk::unit@ target_unit = pk::get_unit(dst_pos);
			
			// 실행 부대 계략 실행 음성 효과, 실행/대상부대 대화
			if (pk::is_in_screen(src_pos_))
			{
                pk::play_voice(0x31, pk::get_person(src_unit.leader));  // 음성 : 계략2
				pk::play_se(0x39, src_pos_);
                pk::create_effect(0x3a, src_pos_);
			}
            // 실행 부대 기력 감소
			pk::add_energy(src_unit, -func_stragety_cost(ENERGY_COST_고무), true);
            pk::say(pk::encode("아군 부대를 응원하라"), pk::get_person(src_unit.leader));
            
			// 대상부대 기력 회복 적용
			pk::add_energy(target_unit, (ENERGY_COST_고무/2), true);
            
            pk::say(pk::encode("고맙소. 힘이 쏟구치는 군"), pk::get_person(target_unit.leader));
            
            // 효과 : 기력상승 효과
            if (pk::is_in_screen(target_unit.pos))
                pk::create_effect(0x3d, target_unit.pos);

			// 기교점수
			pk::add_tp(pk::get_force(src_unit.get_force_id()), 30, dst_pos);
			// 능력경험치
			pk::add_stat_exp(src_unit, 무장능력_지력, 4);
			// 공적
			pk::add_kouseki(src_unit, 100);
            
			// 행동완료
            src_unit.action_done = true;
			if (int(pk::option["San11Option.EnableInfiniteAction"]) != 0)
				src_unit.action_done = false;

			return true;
		}
        
        //---------------------------------------------------------------------------
        // 계략_대고무 (삼국지 조조전 오마쥬)
        //---------------------------------------------------------------------------

		string getText_계략_대고무()
		{
			return pk::encode(pk::format("대고무 ({})", func_stragety_cost(ENERGY_COST_대고무)));
		}

		string getDesc_계략_대고무()
		{
            if (pk::get_person(src_unit.leader).rank >= 관직_없음 and pk::get_person(src_unit.leader).mibun == 신분_일반)
                return pk::encode("관직이 없는 장수는 실행할 수 없습니다");
			else if (src_unit.energy < func_stragety_cost(ENERGY_COST_대고무))
				return pk::encode("기력이 부족합니다");
			else if (getTargets_계략_대고무().length == 0)
				return pk::encode("범위내에 아군부대가 없습니다");
			else
				return pk::encode("기력을 소모하여 선택한 아군부대와 주위부대의 기력을 회복합니다");
		}
        
        bool isVisible_계략_대고무()
		{
            if (pk::is_campaign()) return false;
            if (pk::get_person(src_unit.leader).rank >= 관직_없음 and pk::get_person(src_unit.leader).mibun == 신분_일반) return false;
            return true;
        }

		bool isEnabled_계략_대고무()
		{
			if (pk::get_person(src_unit.leader).rank >= 관직_없음 and pk::get_person(src_unit.leader).mibun == 신분_일반) return false;
			else if (src_unit.energy < func_stragety_cost(ENERGY_COST_대고무)) return false;
			return getTargets_계략_대고무().length > 0;
		}
        
		pk::array<pk::point_int> getTargets_계략_대고무()
		{
			pk::array<pk::point_int> target_units;
			auto range = pk::range(src_pos_, 1, 2 + func_range_add());
			for (int i = 0; i < int(range.length); i++)
			{
				auto dst_unit = pk::get_unit(range[i]);
				if (dst_unit !is null and src_unit.pos != dst_unit.pos and src_unit.get_force_id() == dst_unit.get_force_id())
					target_units.insertLast(pk::point_int(range[i], 1));
			}
			return target_units;
		}

		bool handler_계략_대고무(pk::point dst_pos)
		{
			pk::unit@ target_unit = pk::get_unit(dst_pos);
			
			// 실행 부대 계략 실행 음성 효과, 실행/대상부대 대화
			if (pk::is_in_screen(src_pos_))
			{
                pk::play_voice(0x31, pk::get_person(src_unit.leader));  // 음성 : 계략2
				pk::play_se(0x39, src_pos_);
                pk::create_effect(0x3a, src_pos_);
			}
            // 실행 부대 기력 감소
			pk::add_energy(src_unit, -func_stragety_cost(ENERGY_COST_대고무), true);
            pk::say(pk::encode("아군 부대들을 응원하라"), pk::get_person(src_unit.leader));
            
			// 대상부대 기력 회복 적용
			pk::add_energy(target_unit, (ENERGY_COST_대고무/4), true);
            // 대상부대 주위 부대들의 기력 회복 적용
            auto range = pk::range(target_unit.pos, 1, 1);
			for (int i = 0; i < int(range.length); i++)
			{
				auto dst_unit = pk::get_unit(range[i]);
				if (dst_unit !is null and src_unit.pos != dst_unit.pos and src_unit.get_force_id() == dst_unit.get_force_id())
                {
					pk::add_energy(dst_unit, (ENERGY_COST_대고무/4), true);
                    
                    if (pk::is_in_screen(dst_unit.pos))
                    {
                        pk::say(pk::encode("고맙소"), pk::get_person(dst_unit.leader));
                        // 효과 : 기력상승 효과
                        if (pk::is_in_screen(dst_unit.pos))
                            pk::create_effect(0x3d, dst_unit.pos);
                    }
                }
			}
            
			// 기교점수
			pk::add_tp(pk::get_force(src_unit.get_force_id()), 50, dst_pos);
			// 능력경험치
			pk::add_stat_exp(src_unit, 무장능력_지력, 6);
			// 공적
			pk::add_kouseki(src_unit, 150);
            
			// 행동완료
			src_unit.action_done = true;
			if (int(pk::option["San11Option.EnableInfiniteAction"]) != 0)
				src_unit.action_done = false;

			return true;
		}
        
        
        //---------------------------------------------------------------------------
        // 계략_공작
        //---------------------------------------------------------------------------
        
		int getChance_파괴공작(pk::point dst_pos)
		{
			return 100;
		}
        
		string getText_계략_파괴공작()
		{
			return pk::encode(pk::format("공작 ({})", func_stragety_cost(ENERGY_COST_파괴공작)));
		}

		string getDesc_계략_파괴공작()
		{
			if (src_unit.energy < func_stragety_cost(ENERGY_COST_파괴공작))
				return pk::encode("기력이 부족합니다");
            else if (getTargets_계략_파괴공작().length == 0)
				return pk::encode("범위내에 적 건물이 없습니다");
			else
				return pk::encode("기력을 사용하여 적의 건물을 파괴합니다");
		}
        
        bool isVisible_계략_파괴공작()
        {
            if (pk::is_campaign()) return false;
            return true;
        }
        
		bool isEnabled_계략_파괴공작()
		{
			if (src_unit.energy < func_stragety_cost(ENERGY_COST_파괴공작)) return false;
			return getTargets_계략_파괴공작().length > 0;
		}
        
		pk::array<pk::point_int> getTargets_계략_파괴공작()
		{
			pk::array<pk::point_int> target_building;
            auto range = pk::range(src_pos_, 1, 1 + func_range_add());
			for (int i = 0; i < int(range.length); i++)
			{
				auto dst_building = pk::get_building(range[i]);
				if (dst_building !is null and pk::is_enemy(src_unit, dst_building))
					target_building.insertLast(pk::point_int(range[i], 1));
			}
			return target_building;
		}

        
		bool handler_계략_파괴공작(pk::point dst_pos)
		{
            int hp_damage = int(100 + 2.0 * pk::rand(src_unit.attr.stat[부대능력_공격]));
            
			pk::building@ target_building = pk::get_building(dst_pos);
			
			// 실행 부대 계략 실행 음성 효과, 실행/대상부대 대화
			if (pk::is_in_screen(src_pos_))
			{
				pk::play_se(0x39, src_pos_);
                pk::create_effect(0x3a, src_pos_);
                switch(pk::rand(2))
                {
                    case 0: pk::play_voice(0x1E, pk::get_person(src_unit.leader)); break;  // 음성 : 전투_시설공격1
                    case 1: pk::play_voice(0x1F, pk::get_person(src_unit.leader)); break;  // 음성 : 전투_시설공격2
                }
			}
            
            // 실행 부대 기력 감소, 대상 거점 내구도 감소
			pk::add_energy(src_unit, -func_stragety_cost(ENERGY_COST_파괴공작), true);
            
            pk::person@ taishu = pk::get_person(pk::get_taishu_id(target_building));
            if (!pk::is_alive(taishu) or func_priority(dst_pos) or (pk::rand_bool(pk::min(100, 40 + pk::max(0, src_unit.attr.stat[부대능력_지력] - taishu.stat[무장능력_지력]))) ))
            {
                pk::say(pk::encode("벽을 허물어 버려라"), pk::get_person(src_unit.leader));
                
                int effect_mode = 0;
                
                // 공격부대 애니메이션 효과 ('18.11.10)
                if (pk::is_in_screen(src_pos_))
                {
                    pk::damage_info info;
                    info.src_pos = src_pos_;
                    info.dst_pos = dst_pos;
                    pk::unit_anim(src_unit, 15, { info });
                    pk::wait(1);
                    pk::stop_unit_anim();
                }
                
                // 내구도 대미지
                pk::add_hp(target_building, -hp_damage, true);
                
                if (target_building.get_id() >= 건물_거점끝 and target_building.hp <= 0)
                {
                    if (pk::is_in_screen(src_pos_))
                    {
                        pk::play_se(0x71, target_building.pos);         //임팩트사운드
                        pk::create_effect(0x5c, target_building.pos);   //임팩트효과
                    }
                    
                    pk::kill(target_building, true);
                }
                
                // 일정 확률로 적 시설 탈취 : 논객 우대 ('18.12.26)
                if (계략_공작_탈취 and pk::is_alive(target_building))
                {
                    if ((src_unit.has_skill(특기_논객) or pk::rand_bool(CHANCE_공작탈취확률)) and target_building.facility >= 시설_진 and target_building.facility <= 시설_성채)
                    {
                        int force_id = src_unit.get_force_id();
                        target_building.init_force = force_id;
                        string force_name = pk::decode(pk::get_name(pk::get_force(force_id)));
                        pk::say(pk::encode(pk::format("이제부터 \x1b[1x{}\x1b[0x군을 따르겠습니다", force_name)), pk::get_person(무장_무관), target_building);
                    }
                }
                
                // 임팩트효과
                if (pk::is_in_screen(src_pos_) and pk::is_alive(target_building))
                {
                    if (pk::is_enemy(target_building, src_unit))    // 공작 일반 성공
                    {
                        pk::play_se(0x71, target_building.pos);         //임팩트사운드
                        pk::create_effect(0x21, target_building.pos);   //임팩트효과
                    }
                    else    // 탈취성공
                    {
                        pk::play_se(6);            //임팩트사운드   
                    }
                }
                
                // 기교점수
                pk::add_tp(pk::get_force(src_unit.get_force_id()), 30, dst_pos);
                // 능력경험치
                pk::add_stat_exp(src_unit, 무장능력_무력, 5);
                // 공적
                pk::add_kouseki(src_unit, 100);
            }
            else
            {
                pk::say(pk::encode("쳇. 실패했나"), pk::get_person(src_unit.leader));
            }
            
			// 행동완료
			src_unit.action_done = true;
			if (int(pk::option["San11Option.EnableInfiniteAction"]) != 0)
				src_unit.action_done = false;

			return true;
		}
        
        
        //---------------------------------------------------------------------------
        // 계략_도발 (삼국지 조조전 오마쥬)
        //---------------------------------------------------------------------------
        
		int getChance_도발(pk::point dst_pos)
		{
			return 100;
		}
        
		string getText_계략_도발()
		{
			return pk::encode(pk::format("도발 ({})", func_stragety_cost(ENERGY_COST_도발)));
		}

		string getDesc_계략_도발()
		{
			if (src_unit.energy < func_stragety_cost(ENERGY_COST_도발))
				return pk::encode("기력이 부족합니다");
            else if (getTargets_계략_도발().length == 0)
				return pk::encode("범위내에 태수가 있는 적 거점이 없습니다");
			else
				return pk::encode("기력을 사용하여 적 태수의 출성을 도발합니다");
		}
        
        bool isVisible_계략_도발()
        {
            if (pk::is_campaign()) return false;
            return true;
        }
        
		bool isEnabled_계략_도발()
		{
			if (src_unit.energy < func_stragety_cost(ENERGY_COST_도발)) return false;
			return getTargets_계략_도발().length > 0;
		}
        
		pk::array<pk::point_int> getTargets_계략_도발()
		{
			pk::array<pk::point_int> targets;
            auto range = pk::range(src_pos_, 1, 2 + func_range_add());
			for (int i = 0; i < int(range.length); i++)
			{
				auto dst_building = pk::get_building(range[i]);
				if (dst_building !is null and pk::is_enemy(src_unit, dst_building))
                {
                    pk::person@ taishu = pk::get_person(pk::get_taishu_id(dst_building));
                    
                    if (pk::is_alive(taishu))
                        targets.insertLast(pk::point_int(range[i], 1));
                }
                
                auto enemy_unit = pk::get_unit(range[i]);
				if (enemy_unit !is null and pk::is_enemy(src_unit, enemy_unit))
					targets.insertLast(pk::point_int(range[i], 1));
			}
			return targets;
		}

        
        
		bool handler_계략_도발(pk::point dst_pos)
		{
            
            // 거점 대상 도발
			pk::building@ target_building = pk::get_building(dst_pos);
            if (pk::is_alive(target_building))
            {
                // 실행 부대 계략 실행 음성 효과, 실행/대상부대 대화
                if (pk::is_in_screen(src_pos_))
                {
                    pk::play_voice(0x32, pk::get_person(src_unit.leader));  // 음성 : 계략1
                    pk::play_se(0x39, src_pos_);
                    pk::create_effect(0x3a, src_pos_);
                }
                
                // 실행 부대 기력 감소, 적 거점 태수 부대 생성
                pk::add_energy(src_unit, -func_stragety_cost(ENERGY_COST_도발), true);
                
                pk::person@ taishu = pk::get_person(pk::get_taishu_id(target_building));
                if (pk::is_alive(taishu) and (func_priority(dst_pos) or src_unit.has_skill(특기_논객) or (pk::rand_bool(pk::min(100, pk::max(0, src_unit.attr.stat[부대능력_지력] - taishu.stat[무장능력_지력]))) )))
                {
                    pk::say(pk::encode("쥐새끼처럼 숨지 말고 나와라"), pk::get_person(src_unit.leader));
                    
                    pk::point NearEmptyPos = func_EmptyPos(target_building);
                    if(pk::is_valid_pos(NearEmptyPos))
                    {
                        int weapon_id = 병기_검;
                        int default_troops = pk::min(5000, int(pk::get_troops(target_building)/5) );    // 기본 출진 병력수 설정
                        int target_troops = default_troops;
                        
                        func_weapon_select(target_building, default_troops, weapon_id, target_troops);  // 병기 선택 함수 호출
                        
                        // 출진 병력에 따른 병량 설정
                        int target_food = pk::min( int(target_troops * 1.5f), int(pk::get_food(target_building)/2) );
                        
                        // 부대 출진에 따른 거점 병력,병량,무기 감소
                        pk::add_troops(target_building, -target_troops, false);
                        pk::add_food(target_building, -target_food, false);
                        
                        if (weapon_id != 병기_검)
                            pk::add_weapon_amount(target_building, weapon_id, -target_troops, false);
                        
                        // 도발된 부대 생성
                        @dst_unit = pk::create_unit(target_building, taishu, null, null, target_troops, weapon_id, 병기_주가, 0, target_food, NearEmptyPos);
                        pk::say(pk::encode("소원대로 상대해주마"), pk::get_person(dst_unit.leader));
                        
                        pk::set_order(dst_unit, 부대임무_공격, src_unit.get_pos());
                        
                        if (계략_도발_설전설정)
                        {
                            // 거리가 인접하면 공격 실행, 노병이면 원거리 공격 실행
                            func_fuck_atk(src_unit, dst_unit, 계략_도발_설전설정);

                            // 부대 주장 간 설전
                            if (pk::is_alive(src_unit) and pk::is_alive(dst_unit))
                            {
                                @dst_unit_debate = @dst_unit;
                                @src_unit_debate = @src_unit;
                            
                                unit_debate_list.clear();
                                unit_debate_list.add(dst_unit);
                            }
                        }
                    
                        // 기교점수
                        pk::add_tp(pk::get_force(src_unit.get_force_id()), 30, dst_pos);
                        // 능력경험치
                        pk::add_stat_exp(src_unit, 무장능력_지력, 5);
                        // 공적
                        pk::add_kouseki(src_unit, 100);
                    }
                }
                else
                {
                    pk::say(pk::encode("도발이 안 통하는 군"), pk::get_person(src_unit.leader));
                }
                
            } // 거점 대상 도발
            
            // 부대 대상 도발
            @ dst_unit = pk::get_unit(dst_pos);
            if (pk::is_alive(dst_unit))
            {
                // 실행 부대 계략 실행 음성 효과, 실행/대상부대 대화
                if (pk::is_in_screen(src_pos_))
                {
                    pk::play_voice(0x32, pk::get_person(src_unit.leader));  // 음성 : 계략1
                    pk::play_se(0x39, src_pos_);
                    pk::create_effect(0x3a, src_pos_);
                }
                
                // 실행 부대 기력 감소, 적부대 기력 감소
                pk::add_energy(src_unit, -func_stragety_cost(ENERGY_COST_도발), true);
                func_fuck_msg(src_unit, 0);     // 메세지_발동부대
                
                // 지력차 계산
                int stat_delta = 100;
                if (dst_unit.leader < 무장_영제 or dst_unit.leader > 무장_학자)
                    stat_delta = pk::max(0, src_unit.attr.stat[부대능력_지력] - dst_unit.attr.stat[부대능력_지력]);
                
                if (func_priority(dst_pos) or src_unit.has_skill(특기_논객) or (pk::rand_bool(pk::min(100, 40 + pk::max(0, stat_delta))) ) )
                {
                    func_fuck_msg(dst_unit, 1);  // 메세지_성공_목표부대
                    
                    pk::add_energy(dst_unit, -(src_unit.attr.stat[부대능력_지력]/5), true);
                    pk::set_order(dst_unit, 부대임무_공격, src_unit.get_pos());    // 발동부대를 공격 목표로 설정
                    
                    if (계략_도발_설전설정)
                    {
                        // 거리가 인접하면 공격 실행, 노병이면 원거리 공격 실행
                        func_fuck_atk(src_unit, dst_unit, 계략_도발_설전설정);

                        // 부대 주장 간 설전
                        if (pk::is_alive(src_unit) and pk::is_alive(dst_unit))
                        {
                            @dst_unit_debate = @dst_unit;
                            @src_unit_debate = @src_unit;
                            
                            unit_debate_list.clear();
                            unit_debate_list.add(dst_unit);
                        }
                    }
                    
                    
                    // 기교점수
                    pk::add_tp(pk::get_force(src_unit.get_force_id()), 30, dst_pos);
                    // 능력경험치
                    pk::add_stat_exp(src_unit, 무장능력_지력, 5);
                    // 공적
                    pk::add_kouseki(src_unit, 100);
                }
                else
                {
                    func_fuck_msg(dst_unit, 2);  // 메세지_실패_목표부대
                }
            }
            
			// 행동완료
			src_unit.action_done = true;
			if (int(pk::option["San11Option.EnableInfiniteAction"]) != 0)
				src_unit.action_done = false;

			return true;
		}
        
        
        void func_fuck_atk (pk::unit@ attacker, pk::unit@ target, bool 효과적용)
        {
            if (효과적용)
            {
                if (pk::get_distance(target.pos, attacker.pos) == 1)
                    pk::attack(target, attacker);
                else if (pk::get_distance(target.pos, attacker.pos) == 2 and target.weapon == 병기_노)
                    pk::attack(target, attacker);
            }
        }
        
        // 계략_도발용 함수 : 건물과 발동부대 주변 빈 칸 찾기
        pk::point func_EmptyPos(pk::building@ building)
		{
            int max_range = 3;
			auto range = pk::range(building.get_pos(), 1, max_range);
            
            for (int j = 1; j <= int(max_range); j++)     // 발동부대와의 거리, 가까이부터 멀리
            {
                for (int i = 0; i < int(range.length); i++) // 거점과의 거리, 가까이부터 멀리
                {
                    pk::hex@ hex = pk::get_hex(range[i]);
                    if (!hex.has_building and !hex.has_unit and (pk::get_distance(range[i], src_unit.pos) <= j) )
                        return range[i];    // 조건 만족 시 해당 위치 반환
                }
            }
			return -1;
		}
        
        // 계략_도발용 함수 : 무기 선택 (최적화 아님, 가장 많이 보유한 무기로 설정)
        void func_weapon_select(pk::building@ building, int troops, int &out weapon_sel, int &out troops_sel)
        {
            int weapon_max = 0;
            
            weapon_sel = 0;
            troops_sel = 0;
            
            for (int i = 병기_창; i <= 병기_군마; i++)
            {
                int weapon_t = pk::get_weapon_amount(building, i);
                if (2000 <= weapon_t and weapon_max <= weapon_t)
                {
                    weapon_max = weapon_t;
                    weapon_sel = i;
                    troops_sel = pk::min(troops, weapon_max);
                }
            }
            
            if (weapon_sel == 0)
            {
                troops_sel = troops;
            }
        }
        
        // 계략_도발 욕설용 함수 : 랜덤 메세지 세트
        void func_fuck_msg(pk::unit@ msg_unit, int msg_case)
        {
            pk::person@ leader = pk::get_person(msg_unit.leader);
            
            if (msg_case == 0)  // 성공_발동부대
            {
                switch (pk::rand(4))
                {
                    case 0 : pk::say(pk::encode("모가지는 장식으로 달았냐"), leader); break;
                    case 1 : pk::say(pk::encode("버러지 같은 놈"), leader); break;
                    case 2 : pk::say(pk::encode("야 이 자식아"), leader); break;
                    case 3 : pk::say(pk::encode("애미애비도 없는 놈"), leader); break;
                }
            }
            else if (msg_case == 1)  // 성공_목표부대
            {
                switch (pk::rand(4))
                {
                    case 0 : pk::say(pk::encode("네 놈의 목을 따주겠다"), leader); break;
                    case 1 : pk::say(pk::encode("거기 기다리고 있어라"), leader); break;
                    case 2 : pk::say(pk::encode("당장 죽여주지"), leader); break;
                    case 3 : pk::say(pk::encode("죽으려고 환장했구만"), leader); break;
                }
            }
            else if (msg_case == 2)  // 실패_목표부대
            {
                switch (pk::rand(4))
                {
                    case 0 : pk::say(pk::encode("그냥 무시해라"), leader); break;
                    case 1 : pk::say(pk::encode("상대할 것 없다"), leader); break;
                    case 2 : pk::say(pk::encode("가사롭군"), leader); break;
                    case 3 : pk::say(pk::encode("....."), leader); break;
                }
            }
        }
        
        void scene_도발설전()
		{
            pk::person@ p0 = pk::get_person(src_unit_debate.leader);
            pk::person@ p1 = pk::get_person(dst_unit_debate.leader);
            string p0_name = pk::decode(pk::get_name(p0));
            string p1_name = pk::decode(pk::get_name(p1));
            
            pk::cutin(20);  // 컷인: 노려보기
            pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x 님이 나의 상대가 될 것 같소이까", p1_name)), p0);
            pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x 님야말로 나의 상대가 되지 않소", p0_name)), p1);
            debate_result = pk::debate(p0, p1, p0.is_player(), p1.is_player(), false, 계략_도발_설전보기).first;
        }
        
        void func_debate_result()
        {
            // 설전 결과 반영
            if (debate_result == 0)     // 거는 쪽이 이긴 경우
            {
                func_debate_msg(src_unit_debate, 0);   // 메세지_승리
                func_debate_msg(dst_unit_debate, 1);  // 메세지_패전
                
                pk::add_energy(src_unit_debate, +2*ENERGY_COST_도발설전, true);
                pk::add_energy(dst_unit_debate, -2*ENERGY_COST_도발설전, true);
                
                pk::add_loyalty(pk::get_person(dst_unit_debate.leader), -5);   // 목표부대 주장의 충성도를 낮춤
                
            }
            else if (debate_result == 1)    // 받는 쪽이 이긴 경우
            {
                func_debate_msg(dst_unit_debate, 0);   // 메세지_승리
                func_debate_msg(src_unit_debate, 1);  // 메세지_패전

                pk::add_energy(dst_unit_debate, +2*ENERGY_COST_도발설전, true);
                pk::add_energy(src_unit_debate, -2*ENERGY_COST_도발설전, true);
                
                pk::add_loyalty(pk::get_person(src_unit_debate.leader), -5);   // 발동부대 주장의 충성도를 낮춤
            }
        }
        
        // 야전_설전용 함수 : 랜덤 메세지 세트
        void func_debate_msg(pk::unit@ msg_unit, int msg_case)
        {
            pk::person@ leader = pk::get_person(msg_unit.leader);
            
            if (msg_case == 0)  // 승리부대
            {
                switch (pk::rand(4))
                {
                    case 0 : pk::say(pk::encode("이겼다"), leader); break;
                    case 1 : pk::say(pk::encode("조금 만 더 밀어붙이자"), leader); break;
                    case 2 : pk::say(pk::encode("어려울 게 없군"), leader); break;
                    case 3 : pk::say(pk::encode("나의 논리가 우세하군"), leader); break;
                }
            }
            else if (msg_case == 1)  // 패전부대
            {
                switch (pk::rand(4))
                {
                    case 0 : pk::say(pk::encode("졌는가"), leader); break;
                    case 1 : pk::say(pk::encode("설득 당했군"), leader); break;
                    case 2 : pk::say(pk::encode("안되겠는 걸"), leader); break;
                    case 3 : pk::say(pk::encode("이런 상황이면.."), leader); break;
                }
            }
            else if (msg_case == 2)  // 실패상황
            {
                switch (pk::rand(4))
                {
                    case 0 : pk::say(pk::encode("그냥 무시해라"), leader); break;
                    case 1 : pk::say(pk::encode("상대할 것 없다"), leader); break;
                    case 2 : pk::say(pk::encode("가사롭군"), leader); break;
                    case 3 : pk::say(pk::encode("개가 짓는 소리지"), leader); break;
                }
            }
        }
        
        //---------------------------------------------------------------------------
        // 계략_회귀 (삼국지 조조전 오마쥬)
        //---------------------------------------------------------------------------

		string getText_계략_회귀()
		{
			return pk::encode(pk::format("회귀 ({})", func_stragety_cost(ENERGY_COST_회귀)));
		}

		string getDesc_계략_회귀()
		{
			if (pk::get_person(src_unit.leader).mibun == 신분_일반 and !src_unit.has_skill(특기_지도))
                return pk::encode("신분이 군주 또는 도독이 아니거나, 특기_지도를 갖고 있지 않습니다");
            else if (src_unit.energy < func_stragety_cost(ENERGY_COST_회귀))
				return pk::encode("기력이 부족합니다");
			else if (getTargets_계략_회귀().length == 0)
				return pk::encode("범위내에 행동을 완료한 아군부대가 없습니다");
			else
				return pk::encode("기력을 대폭 소모하여 아군 부대 행동을 재개합니다");
		}
        
        bool isVisible_계략_회귀()
		{
            if (pk::is_campaign()) return false;
            if (pk::get_person(src_unit.leader).mibun == 신분_일반 and !src_unit.has_skill(특기_지도)) return false;
			return true;
        }
        
		bool isEnabled_계략_회귀()
		{
			if (pk::get_person(src_unit.leader).mibun == 신분_일반 and !src_unit.has_skill(특기_지도)) return false;
            else if (src_unit.energy < func_stragety_cost(ENERGY_COST_회귀)) return false;
			return getTargets_계략_회귀().length > 0;
		}
        
		pk::array<pk::point_int> getTargets_계략_회귀()
		{
			pk::array<pk::point_int> target_units;
			auto range = pk::range(src_pos_, 1, 1 + func_range_add());
			for (int i = 0; i < int(range.length); i++)
			{
				auto dst_unit = pk::get_unit(range[i]);
				if (dst_unit !is null and src_unit.pos != dst_unit.pos and src_unit.get_force_id() == dst_unit.get_force_id() and dst_unit.action_done == true and dst_unit.status == 부대상태_통상)
					target_units.insertLast(pk::point_int(range[i], 1));
			}
			return target_units;
		}

		bool handler_계략_회귀(pk::point dst_pos)
		{
			pk::unit@ target_unit = pk::get_unit(dst_pos);
			
			// 실행 부대 계략 실행 음성 효과, 실행/대상부대 대화
			if (pk::is_in_screen(src_pos_))
			{
                pk::play_voice(0x37, pk::get_person(src_unit.leader));  // 음성 : 전투_진정
				pk::play_se(0x39, src_pos_);
                pk::create_effect(0x3a, src_pos_);
			}
            // 실행 부대 기력 감소
			pk::add_energy(src_unit, -func_stragety_cost(ENERGY_COST_회귀), true);
            pk::say(pk::encode("부대에 다시 명령을!!"), pk::get_person(src_unit.leader));
            
            // 재행동 설정
            pk::say(pk::encode("꾸물대지 말고 빨리빨리 움직여라"), pk::get_person(target_unit.leader));
            target_unit.action_done = false;    // 대상부대 행동재개
            
            // 효과 : 
            if (pk::is_in_screen(target_unit.pos))
                pk::create_effect(0x3a, target_unit.pos);

			// 기교점수
			pk::add_tp(pk::get_force(src_unit.get_force_id()), 30, dst_pos);
			// 능력경험치
			pk::add_stat_exp(src_unit, 무장능력_지력, 4);
			// 공적
			pk::add_kouseki(src_unit, 100);
            
			// 행동완료
			src_unit.action_done = true;
			if (int(pk::option["San11Option.EnableInfiniteAction"]) != 0)
				src_unit.action_done = false;
            
			return true;
		}
        
        
        //---------------------------------------------------------------------------
        // 부대_해산
        //---------------------------------------------------------------------------

		string getText_부대_해산()
        {
			return pk::encode("해산");
        }
        
		string getDesc_부대_해산()
        {
            if (src_unit.troops < 2000)
                return pk::encode("병력 2천명 이상만 실행할 수 있습니다");
            else if (count_enemies_around(src_pos_) >= 1) 
                return pk::encode("주변에 적군이 있어 실행할 수 없습니다");
            else
                return pk::encode("부대를 해산합니다 (병력 전부 소실 후 장수만 귀환)");
        }
        
        
        bool isVisible_부대_해산()
		{
            if (pk::is_campaign()) return false;
			return true;
        }
        
		bool isEnabled_부대_해산()
		{
            if (src_unit.troops < 2000) return false;
            else if (count_enemies_around(src_pos_) >= 1) return false;
            return getTargets_부대_해산().length > 0;
        }
        
		pk::array<pk::point_int> getTargets_부대_해산()
		{
            pk::array<pk::point_int> target_units;
            
            if (count_enemies_around(src_pos_) < 1)
            {
                target_units.insertLast(pk::point_int(src_pos_, 1));
			}
            return target_units;
		}

		bool handler_부대_해산(pk::point dst_pos)
		{
			pk::unit@ target_unit = pk::get_unit(dst_pos);

			// 행동완료
			src_unit.action_done = true;
			if (int(pk::option["San11Option.EnableInfiniteAction"]) != 0)
				src_unit.action_done = false;
            
            // 부대 해산
            pk::say(pk::encode("부대를 해산하겠소"), pk::get_person(target_unit.leader));
            
            pk::add_troops(target_unit, -target_unit.troops, false);
            if (target_unit.troops <= 0)
                pk::kill(target_unit);

			return true;
		}
        
        // 주위의 적부대, 적건물 수 검색
        int count_enemies_around(pk::point pos)
        {
            int count_enemy = 0;
            int max_range = 5;
            
            pk::array<pk::point> range = pk::range(pos, 1, max_range);
            for (int i = 0; i < int(range.length); i++)
            {
                pk::unit@ unit_around = pk::get_unit(range[i]);
                if (unit_around !is null and pk::is_enemy(src_unit, unit_around))
                    count_enemy += 1;
                
                pk::building@ building_around = pk::get_building(range[i]);
                if (building_around !is null and pk::is_enemy(src_unit, building_around))
                    count_enemy += 1;
            }
            
            return count_enemy;
        }
        
        
        //---------------------------------------------------------------------------
        // 부대_병합 (삼국지13 오마쥬)
        //---------------------------------------------------------------------------

		string getText_부대_병합()
        {
			return pk::encode("병합");
        }
            
		string getDesc_부대_병합()
		{
            if (pk::get_person(src_unit.leader).rank >= 관직_없음 and pk::get_person(src_unit.leader).mibun == 신분_일반)
                return pk::encode("관직이 없는 장수는 실행할 수 없습니다");
            else if (src_unit.troops < 2000)
                return pk::encode("병력 2천명 이상만 실행할 수 있습니다");
            else if (count_enemies_around(src_pos_) >= 1) 
                return pk::encode("주변에 적군이 있어 실행할 수 없습니다");
			else if (getTargets_부대_병합().length == 0)
				return pk::encode("범위내에 동일 병과의 아군부대가 없습니다");
			else
				return pk::encode("대상부대에 병력을 병합합니다");
		}
        
		bool isVisible_부대_병합()
        {
            if (pk::is_campaign()) return false;
            return true;
        }
        
		
		bool isEnabled_부대_병합()
		{
            if (pk::get_person(src_unit.leader).rank >= 관직_없음 and pk::get_person(src_unit.leader).mibun == 신분_일반) return false;
            else if (src_unit.troops < 2000) return false;
            else if (count_enemies_around(src_pos_) >= 1) return false;
			return getTargets_부대_병합().length > 0;
		}
        
		pk::array<pk::point_int> getTargets_부대_병합()
		{
			pk::array<pk::point_int> target_units;
            
            if (count_enemies_around(src_pos_) < 1) 
            {
                auto range = pk::range(src_pos_, 1, 1);
                for (int i = 0; i < int(range.length); i++)
                {
                    auto dst_unit = pk::get_unit(range[i]);
                    if (dst_unit !is null and src_unit.pos != dst_unit.pos and src_unit.get_force_id() == dst_unit.get_force_id() and pk::get_ground_weapon_id(src_unit) ==  pk::get_ground_weapon_id(dst_unit))
                        target_units.insertLast(pk::point_int(range[i], 1));
                }
            }
			return target_units;
		}

		bool handler_부대_병합(pk::point dst_pos)
		{
			pk::unit@ target_unit = pk::get_unit(dst_pos);
			
			// 실행 부대 계략 실행 음성 효과, 실행/대상부대 대화
			if (pk::is_in_screen(src_pos_))
			{
				pk::play_se(0x39, src_pos_);
				//pk::wait(1, 1000);
			}
            
            int troops_re_org = pk::min(src_unit.troops, (pk::get_max_troops(target_unit) - target_unit.troops));
            int energy_re_org = ((troops_re_org * src_unit.energy) + (target_unit.troops * target_unit.energy)) / (troops_re_org + target_unit.troops);
            
            int food_re_org = pk::min(src_unit.food, (2*troops_re_org));
            
            
            // 실행부대 병력감소, 병량감소
            pk::add_troops(src_unit, -troops_re_org, true);
            pk::add_food(src_unit, -food_re_org, true);
            
            if (src_unit.troops == 0)
            {
                pk::say(pk::encode("우리 부대는 해산한다"), pk::get_person(src_unit.leader));
                pk::kill(src_unit);
            }
            else
            {
                pk::say(pk::encode("병력을 넘기겠소"), pk::get_person(src_unit.leader));
            }

            
            // 대상부대 병력증가
            pk::add_troops(target_unit, troops_re_org, true);
            pk::say(pk::encode("너희는 이제부터 나를 따른다"), pk::get_person(target_unit.leader));
            // 대상부대 병량증가
            pk::add_food(target_unit, food_re_org, true);
            // 대상부대 기력조정
            pk::add_energy(target_unit, (energy_re_org - target_unit.energy), true);
            
            // 효과 : 기력상승(보라)
            if (pk::is_in_screen(target_unit.pos))
                pk::create_effect(0x4c, target_unit.pos);
            
			// 행동완료
			src_unit.action_done = true;
			if (int(pk::option["San11Option.EnableInfiniteAction"]) != 0)
				src_unit.action_done = false;

			return true;
		}
        
        
        
        //---------------------------------------------------------------------------
        // 부대_회복
        //---------------------------------------------------------------------------
        
		string getText_부대_회복()
		{
			return pk::encode(pk::format("회복 금{}", GOLD_COST_회복));
		}

		string getDesc_부대_회복()
		{
			if (pk::get_person(src_unit.leader).rank >= 관직_없음 and pk::get_person(src_unit.leader).mibun == 신분_일반)
                return pk::encode("관직이 없는 장수는 실행할 수 없습니다");
			else if (src_unit.gold < GOLD_COST_회복)
				return pk::encode("소지금이 부족합니다");
            else if (count_enemies_around(src_pos_) >= 1) 
                return pk::encode("주변에 적군이 있어 실행할 수 없습니다");
			else
				return pk::encode("소지금을 사용하여 병력을 회복합니다");
		}
        
        bool isVisible_부대_회복()
		{
            if (pk::is_campaign()) return false;
			return true;
        }
        
		bool isEnabled_부대_회복()
		{
			if (pk::get_person(src_unit.leader).rank >= 관직_없음 and pk::get_person(src_unit.leader).mibun == 신분_일반) return false;
            else if (src_unit.gold < GOLD_COST_회복) return false;
            else if (count_enemies_around(src_pos_) >= 1) return false;
			return getTargets_부대_회복().length > 0;
		}
        
		pk::array<pk::point_int> getTargets_부대_회복()
		{
			pk::array<pk::point_int> target_units;
            target_units.insertLast(pk::point_int(src_pos_, 1));
            
            auto range = pk::range(src_pos_, 1, 2 + func_range_add());
			for (int i = 0; i < int(range.length); i++)
			{
				auto dst_unit = pk::get_unit(range[i]);
				if (dst_unit !is null and src_unit.pos != dst_unit.pos and src_unit.get_force_id() == dst_unit.get_force_id())
					target_units.insertLast(pk::point_int(range[i], 1));
			}
            
			return target_units;
		}

        
		bool handler_부대_회복(pk::point dst_pos)
		{
			pk::unit@ target_unit = pk::get_unit(dst_pos);
			
			// 실행 부대 계략 실행 음성 효과, 실행/대상부대 대화
			if (pk::is_in_screen(src_pos_))
			{
                pk::play_voice(0x37, pk::get_person(src_unit.leader));  // 음성 : 진정
				pk::play_se(0x39, src_pos_);
                pk::create_effect(0x4a, src_pos_);  // 효과: 기력상승(빨강)
			}
            // 실행 부대 소지금 감소, 병력 회복
            pk::say(pk::encode("부상병들을 치료하라"), pk::get_person(src_unit.leader));
			pk::add_gold(src_unit, -GOLD_COST_회복, true);
			pk::add_troops(target_unit, (GOLD_COST_회복/40 * src_unit.attr.stat[부대능력_통솔]), true);
            
			// 기교점수
			pk::add_tp(pk::get_force(src_unit.get_force_id()), 20, dst_pos);
			// 능력경험치
			pk::add_stat_exp(src_unit, 무장능력_통솔, 4);
			// 공적
			pk::add_kouseki(src_unit, 100);
            
			// 행동완료
			src_unit.action_done = true;
			if (int(pk::option["San11Option.EnableInfiniteAction"]) != 0)
				src_unit.action_done = false;

			return true;
		}
        
        
        
        //---------------------------------------------------------------------------
        // 부대_재편
        //---------------------------------------------------------------------------
        
		string getText_부대_재편()
		{
			return pk::encode("재편");
		}

		string getDesc_부대_재편()
		{
            if (!pk::is_alive(pk::get_person(src_unit.member[1]))) 
                return pk::encode("부장이 없습니다");
            else if (count_enemies_around(src_pos_) >= 1) 
                return pk::encode("주변에 적군이 있어 실행할 수 없습니다");
            return pk::encode("부대의 주장을 재편성합니다");
		}
        
        bool isVisible_부대_재편()
		{
            if (pk::is_campaign()) return false;
            return true;
		}
                
		bool isEnabled_부대_재편()
		{
            if (!pk::is_alive(pk::get_person(src_unit.member[1]))) return false;
            else if (count_enemies_around(src_pos_) >= 1) return false;
			return getTargets_부대_재편().length > 0;
		}
        
		pk::array<pk::point_int> getTargets_부대_재편()
		{
            pk::array<pk::point_int> target_units;
            
            if (count_enemies_around(src_pos_) < 1)
            {
                target_units.insertLast(pk::point_int(src_pos_, 1));
			}
            return target_units;
		}
        
		bool handler_부대_재편(pk::point dst_pos)
		{
			pk::unit@ target_unit = pk::get_unit(dst_pos);
			
            // 주장/부장 리스트
			pk::person@ p0 = pk::get_person(target_unit.member[0]);
			pk::person@ p1 = pk::get_person(target_unit.member[1]);
			pk::person@ p2 = pk::get_person(target_unit.member[2]);
            
            pk::list<pk::person@> member_list;
            if (pk::is_alive(p0)) member_list.add(p0);
            if (pk::is_alive(p1)) member_list.add(p1);
            if (pk::is_alive(p2)) member_list.add(p2);
            
            // 지휘병력 확인
            int cmd_old = pk::get_command(p0);
            int cmd_new;
            
            // 무장 선택
            bool confirm = false;
            pk::list<pk::person@> leader_sel;
            int leader_id;
            pk::person@ leader;
            string leader_name;
            while (!confirm)
            {
                leader_sel = pk::person_selector(pk::encode("주장 선택"), pk::encode("부대의 주장을 선택합니다."), member_list, 1, 1);
                if (leader_sel.count == 0) return false; // 취소 종료
               
                leader_id = leader_sel[0].get_id();      // 선택한 무장번호
                if (leader_id == target_unit.member[0])
                {
                    pk::message_box(pk::encode("주장을 변경하지 않았습니다"));
                }
                else
                {       
                    @leader = pk::get_person(leader_id);
                    leader_name = pk::decode(pk::get_name(leader));
                    cmd_new = pk::get_command(leader);
                    confirm = pk::yes_no(pk::encode(pk::format("\x1b[1x{}\x1b[0x을(를) 새 주장으로 지정하시겠습니까?\n(지휘병력 {} → \x1b[1x{}\x1b[0x)", leader_name, cmd_old, cmd_new)));
                }
            }
            
            // 주장/부장 무장ID swap
            if (leader_id == target_unit.member[2])
            {
                target_unit.member[2] = target_unit.member[0];
                target_unit.member[0] = leader_id;
            }
            else if (leader_id == target_unit.member[1])
            {
                target_unit.member[1] = target_unit.member[0];
                target_unit.member[0] = leader_id;
            }
            else if (leader_id == target_unit.member[0])
            {
                target_unit.member[0] = leader_id;
            }
            target_unit.update();
            
            // 새로운 주장의 대화표시
            if (pk::is_in_screen(src_pos_))
            {
                pk::say(pk::encode(pk::format("지금부터 이 \x1b[1x{}\x1b[0x이(가)\n부대의 지휘를 맡겠소", leader_name)), leader);
            }
            
            // 지휘병력 초과 시 부대 병력 조정
            if (int(target_unit.troops) > int(cmd_new))
                pk::add_troops(target_unit, int(target_unit.troops - cmd_new), true);
            
			// 행동완료
			src_unit.action_done = true;
			if (int(pk::option["San11Option.EnableInfiniteAction"]) != 0)
				src_unit.action_done = false;

			return true;
		}
        
        
        
        //---------------------------------------------------------------------------
        // 메뉴_강행군 (삼국지7 오마쥬)
        //---------------------------------------------------------------------------

		string getText_메뉴_강행군()
        {
			return pk::encode("강행군");
        }
        
		string getDesc_메뉴_강행군()
		{
			if (pk::get_person(src_unit.leader).rank >= 관직_없음 and pk::get_person(src_unit.leader).mibun == 신분_일반)
                return pk::encode("관직이 없는 장수는 실행할 수 없습니다");
			else if (src_unit.energy < ENERGY_MIN_강행군)
				return pk::encode("최소 실행 기력이 부족합니다");
			else
				return pk::encode(pk::format("기력을 사용하여 추가 이동합니다 (최소기력 {} 이상필요)", ENERGY_MIN_강행군));
		}
        
		bool isVisible_메뉴_강행군()
        {
            if (pk::is_campaign()) return false;
            return true;
        }
        
		bool isEnabled_메뉴_강행군()
		{
			if (pk::get_person(src_unit.leader).rank >= 관직_없음 and pk::get_person(src_unit.leader).mibun == 신분_일반) return false;
            else if (src_unit.energy < ENERGY_MIN_강행군) return false;
			return getTargets_메뉴_강행군().length > 0;
		}
        
		pk::array<pk::point_int> getTargets_메뉴_강행군()
		{
            int movement = int(MOVEMENT_강행군 * src_unit.attr.stat[부대능력_이동]);
            
            // 이동 목표 지점 획득
            pk::array<pk::point_int> target_pos;
			auto range = pk::get_movable_pos(src_unit, src_pos_, movement); // 이동가능한 경로만 획득
            for (int i = 0; i < int(range.length); i++)
			{
                pk::hex@ hex = pk::get_hex(range[i]);
                target_pos.insertLast(pk::point_int(range[i], 1));
			}
            return target_pos;
		}

		bool handler_메뉴_강행군(pk::point dst_pos)
		{
            // 추가 이동력 설정
            int movement = int(MOVEMENT_강행군 * src_unit.attr.stat[부대능력_이동]);
            int cost_sum = 0;   // 총 이동 cost 더하기
            int cost_next = 0;
            
            // 부대 위치 지형
            pk::hex@ hex = pk::get_hex(src_unit.pos);
            int terrain_id = hex.terrain;
            // 부대 병과
            int weapon_id = pk::is_water_terrain(terrain_id) ? pk::get_sea_weapon_id(src_unit) : pk::get_ground_weapon_id(src_unit);
			pk::equipment@ equipment = pk::get_equipment(weapon_id);
            
            
            // 목표지점까지 이동 경로 획득
            array<pk::point> steps;
            // 중간이동지점
            auto paths = pk::get_path(src_unit, src_unit.pos, dst_pos);
            
            // 중간이동지점
            for (int i = 0; i < int(paths.length); i++)
            {
                @hex = pk::get_hex(paths[i]);
                terrain_id = hex.terrain;
                weapon_id = pk::is_water_terrain(terrain_id) ? pk::get_sea_weapon_id(src_unit) : pk::get_ground_weapon_id(src_unit);
                @ equipment = pk::get_equipment(weapon_id);

                steps.insertLast(paths[i]); //중간이동지점 추가
                if (i > 0)
                    cost_sum += equipment.movement_cost[terrain_id];
                
            }
            
            // 최종이동지점
            @hex = pk::get_hex(dst_pos);
            terrain_id = hex.terrain;
            weapon_id = pk::is_water_terrain(terrain_id) ? pk::get_sea_weapon_id(src_unit) : pk::get_ground_weapon_id(src_unit);
            @ equipment = pk::get_equipment(weapon_id);

            steps.insertLast(dst_pos);  //최종이동지점 추가
            cost_sum += equipment.movement_cost[terrain_id];
        
            // 부대 강행군 실행
            if (steps.length != 0)
            {
                // 실행 부대 계략 실행 음성 효과
                if (pk::is_in_screen(src_pos_))
                {
                    //pk::play_se(0x39, src_pos_);
                    //pk::create_effect(0x3a, src_pos_);
                    switch(pk::rand(2))
                    {
                        case 0: pk::play_voice(0x1A, pk::get_person(src_unit.leader)); break; // 음성 : 전투_이동
                        case 1: pk::play_voice(0x1B, pk::get_person(src_unit.leader)); break; // 음성 : 전투_이동
                    }
                }
                
                pk::say(pk::encode("어서 걸음을 재촉하라"), pk::get_person(src_unit.leader));
                pk::move(src_unit, steps); // 전체경로 일괄이동
                
                // [이동경로상 이동 cost] x 50%] 만큼 기력 소모
                pk::add_energy(src_unit, -int(0.50f * cost_sum), true);
                // 병력의 5% x [이동경로상 이동 cost]/[총 이동력] 만큼 병력 이탈
                pk::add_troops(src_unit, -int(0.05f * src_unit.troops * cost_sum / movement), true);
                
            }
            
            // 행동완료
			src_unit.action_done = true;
			if (int(pk::option["San11Option.EnableInfiniteAction"]) != 0)
				src_unit.action_done = false;
            

			return true;
		}
        
        
        
        
        //---------------------------------------------------------------------------
        // 계략_기습 (삼국지10 오마쥬)
        //---------------------------------------------------------------------------

		string getText_계략_기습()
        {
			return pk::encode(pk::format("기습 ({})", func_stragety_cost(ENERGY_COST_기습)));
        }
        
		string getDesc_계략_기습()
		{
            if (src_unit.weapon > 병기_군마 and !pk::is_in_water(src_unit))
                return pk::encode("전투 병과만 실행할 수 있습니다");
			else if (src_unit.weapon == 병기_주가 and pk::is_in_water(src_unit))
                return pk::encode("주가는 실행할 수 없습니다");
			else if (src_unit.energy < ENERGY_COST_기습)
				return pk::encode("기력이 부족합니다");
			else
				return pk::encode(pk::format("기력을 사용하여 적을 기습합니다 (기력 {} 소모)", ENERGY_COST_기습));
		}
        
        bool isVisible_계략_기습()
		{
            if (pk::is_campaign()) return false;
            //if (src_unit.weapon > 병기_군마 and !pk::is_in_water(src_unit)) return false;
            //else if (src_unit.weapon == 병기_주가 and pk::is_in_water(src_unit)) return false;
            return true;
        }

		bool isEnabled_계략_기습()
		{
            if (src_unit.weapon > 병기_군마 and !pk::is_in_water(src_unit)) return false;
            else if (src_unit.weapon == 병기_주가 and pk::is_in_water(src_unit)) return false;
            return getTargets_계략_기습().length > 0;
		}
        
		pk::array<pk::point_int> getTargets_계략_기습()
		{
            int movement = int(MOVEMENT_강행군 * src_unit.attr.stat[부대능력_이동]);
            
            // 이동 목표 지점 획득
            pk::array<pk::point_int> target_pos;
			auto range = pk::get_movable_pos(src_unit, src_pos_, movement); // 이동가능한 경로만 획득
            for (int i = 0; i < int(range.length); i++)
			{
                auto arr = pk::range(range[i], 1, 1);
                for (int j = 0; j < int(arr.length); j++)
                {
                    pk::unit@ target_unit = pk::get_unit(arr[j]);
                    if (target_unit !is null and pk::is_enemy(src_unit, target_unit) and pk::is_valid_pos(getEmptyPos(arr[j])))
                        target_pos.insertLast(pk::point_int(arr[j], 0));
                }
			}
            return target_pos;
		}
        
		pk::point getEmptyPos(pk::point dst_pos)
		{
            pk::point EmptyPos = -1;
            int pos_range = 0;
            
			auto arr = pk::range(dst_pos, 1, 1);
			for (int i = 0; i < int(arr.length); i++)
			{
				pk::hex@ hex = pk::get_hex(arr[i]);
				if (pk::is_enabled_terrain(hex.terrain) and !hex.has_building and !hex.has_unit and pos_range <= pk::get_distance(src_pos_, arr[i]) )
                {
                    pos_range = pk::get_distance(src_pos_, arr[i]);
                    EmptyPos = arr[i];
                }
			}
			return EmptyPos;
		}
        
        bool handler_계략_기습(pk::point dst_pos)
		{
            pk::unit@ target_unit = pk::get_unit(dst_pos);
            
            // 기습 대상부대 주변 멀리있는 빈 칸 획득
            pk::point emptyPos = getEmptyPos(dst_pos);
            
            array<pk::point> steps;
            if (pk::is_valid_pos(emptyPos))
            {
                // 실행부대 기력 감소
                pk::add_energy(src_unit, -func_stragety_cost(ENERGY_COST_기습), true);
                
                if (pk::is_in_screen(src_pos_))
                {
                    pk::play_se(0x39, src_pos_);
                    pk::create_effect(0x3a, src_pos_);
                }
                
                int stat_delta = 100;
                if (target_unit.leader < 무장_영제 or target_unit.leader > 무장_학자)
                    stat_delta = pk::max(0, src_unit.attr.stat[부대능력_지력] - target_unit.attr.stat[부대능력_지력]);
                
                if (func_priority(dst_pos) or pk::rand_bool(pk::min(100, 40 + pk::max(0, stat_delta)) )
                    or (src_unit.has_skill(특기_급습) and !pk::is_in_water(src_unit)) 
                    or (src_unit.has_skill(특기_강습) and pk::is_in_water(src_unit)) )
                {
                    if (pk::is_in_screen(src_pos_))
                    {
                        switch(pk::rand(2))
                        {
                            case 0: pk::play_voice(0x1C, pk::get_person(src_unit.leader)); break; // 음성 : 전투_공격
                            case 1: pk::play_voice(0x1D, pk::get_person(src_unit.leader)); break; // 음성 : 전투_공격
                        }
                    }
                    
                    //---------------------------------------------
                    // 분대 임시 생성하여 공격하는 방식
                    pk::person@ src_leader = pk::get_person(src_unit.leader);
                    pk::person@ attacker = pk::get_person(무장_무관);
                    
                    pk::force@ force = pk::get_force(src_unit.get_force_id());
                    int district_num = pk::get_district_id(force, 1);
                    
                    // 분대 군단 설정
                    pk::set_district(attacker, district_num); 
                    attacker.mibun = 신분_일반;
                    attacker.birth = pk::get_year() - 30;
                    attacker.death = pk::min(353, attacker.birth + 99);
                    attacker.appearance = pk::get_year() - 10;
                    // 능력치 : 본대의 80%
                    attacker.base_stat[무장능력_통솔] = int(1.0f * src_leader.stat[무장능력_통솔]);
                    attacker.base_stat[무장능력_무력] = int(1.0f * src_leader.stat[무장능력_무력]);
                    attacker.base_stat[무장능력_지력] = int(1.0f * src_leader.stat[무장능력_지력]);
                    attacker.base_stat[무장능력_정치] = int(1.0f * src_leader.stat[무장능력_정치]);
                    attacker.base_stat[무장능력_매력] = int(1.0f * src_leader.stat[무장능력_매력]);
                    
                    int ground_weapon = pk::get_ground_weapon_id(src_unit);
                    
                    // 능력치 반영.
                    attacker.update();
                    
                    int troops = src_unit.troops;
                    int gold = 0;
                    int food = troops;
                    
                    pk::unit@ atk_unit = pk::create_unit(pk::get_building(pk::get_service(src_unit)), attacker, null, null, troops, ground_weapon, 병기_주가, gold, food, emptyPos);
                    pk::set_energy(atk_unit, src_unit.energy);  // 본부대 기력값 반영
                    
                    if (pk::is_in_screen(emptyPos))
                        pk::create_effect(0x4b, emptyPos);
                    
                    pk::attack(atk_unit, target_unit);  // 적 부대에 공격 실행
                    
                    if(pk::rand_bool(30))       // 30% 확률로 적 부대 혼란
                        pk::set_status(target_unit, atk_unit, 부대상태_혼란, 2, true);
                    
                    pk::add_troops(src_unit, -(troops - atk_unit.troops)/2, true);  // 분대 병력 본대 귀환
                    
                    if (!pk::is_alive(atk_unit))
                        pk::reset(attacker);
                    
                    pk::add_troops(atk_unit, -atk_unit.troops, false);
                    if (atk_unit.troops <= 0)
                    {
                        pk::kill(atk_unit);                 // 분대 해산
                        pk::reset(attacker);
                    }
                    
                    //---------------------------------------------
                    
                    if (pk::is_in_screen(src_pos_))
                    {
                        switch(pk::rand(4))
                        {
                            case 0: pk::say(pk::encode("이런. 방심했다"), pk::get_person(target_unit.leader)); break;
                            case 1: pk::say(pk::encode("적의 기습인가"), pk::get_person(target_unit.leader)); break;
                            case 2: pk::say(pk::encode("대체 어디서 나타난 적이냐"), pk::get_person(target_unit.leader)); break;
                            case 3: pk::say(pk::encode("전열을 가다듬어라"), pk::get_person(target_unit.leader)); break;
                        }
                        switch(pk::rand(4))
                        {
                            case 0: pk::say(pk::encode("기습에 성공했군"), pk::get_person(src_unit.leader)); break;
                            case 1: pk::say(pk::encode("적의 후방을 교란하는 거다"), pk::get_person(src_unit.leader)); break;
                            case 2: pk::say(pk::encode("후후훗"), pk::get_person(src_unit.leader)); break;
                            case 3: pk::say(pk::encode("적의 전열이 무너지는군"), pk::get_person(src_unit.leader)); break;
                        }
                    }
                    
                    // 기교점수
                    pk::add_tp(pk::get_force(src_unit.get_force_id()), 20, dst_pos);
                    // 능력경험치
                    pk::add_stat_exp(src_unit, 무장능력_통솔, 4);
                    // 공적
                    pk::add_kouseki(src_unit, 100);
                }
                else
                {
                    if (pk::is_in_screen(src_pos_))
                    {
                        switch(pk::rand(2))
                        {
                            case 0: pk::play_voice(0x45, pk::get_person(src_unit.leader)); break; // 음성 : 전투_계략간파
                            case 1: pk::play_voice(0x46, pk::get_person(src_unit.leader)); break; // 음성 : 전투_계략간파
                        }
                        pk::say(pk::encode("기습 따위는 이미 간파했다"), pk::get_person(target_unit.leader));
                        pk::say(pk::encode("적이 눈치 채었는가"), pk::get_person(src_unit.leader));
                    }
                }
            }
            
            // 행동완료
			src_unit.action_done = true;
			if (int(pk::option["San11Option.EnableInfiniteAction"]) != 0)
				src_unit.action_done = false;
            
            return true;
        }
        
        
        
        
        //---------------------------------------------------------------------------
        // 계략_낙석
        //---------------------------------------------------------------------------
        
		int getChance_낙석(pk::point dst_pos)
		{
			return 100;
		}
        
		string getText_계략_낙석()
		{
			return pk::encode(pk::format("낙석 ({})", func_stragety_cost(ENERGY_COST_낙석)));
		}

		string getDesc_계략_낙석()
		{
			if (src_unit.energy < func_stragety_cost(ENERGY_COST_낙석))
				return pk::encode("기력이 부족합니다");
            else if (getTargets_계략_낙석().length == 0)
				return pk::encode("실행 가능한 지점이 없습니다");
			else
				return pk::encode("낙석 공격을 감행합니다");
		}
        
        
        bool isVisible_계략_낙석()
		{
            if (pk::is_campaign()) return false;
            return true;
		}
               
               
		bool isEnabled_계략_낙석()
		{
			if (src_unit.energy < func_stragety_cost(ENERGY_COST_낙석)) return false;
			return getTargets_계략_낙석().length > 0;
		}
        
		pk::array<pk::point_int> getTargets_계략_낙석()
		{
			pk::array<pk::point_int> targets;
            auto range = pk::range(src_pos_, 1, 1);
			for (int i = 0; i < int(range.length); i++)
			{
                pk::hex@ hex = pk::get_hex(range[i]);
				if (pk::is_enabled_terrain(hex.terrain) and hex.terrain == 지형_산 
                    and get_height_diff(src_pos_, range[i]) >= 0 
                    and !hex.has_building and (!hex.has_unit or src_unit.pos == range[i]))
                    {
                        targets.insertLast(pk::point_int(range[i], 1));
                    }
			}
			return targets;
		}
        
        bool handler_계략_낙석(pk::point dst_pos)
		{
            // 실행부대 기력 감소
            pk::add_energy(src_unit, -func_stragety_cost(ENERGY_COST_낙석), true);
            
            if (func_priority(dst_pos) or pk::rand_bool(pk::min(100, pk::max(0, src_unit.attr.stat[부대능력_지력]))) )
            {
                // 낙석 생성
                pk::create_building(pk::get_facility(시설_낙석), dst_pos, src_unit.get_force_id());    
                pk::building@ building = pk::get_building(dst_pos);
                pk::complete(building);
                
                // 낙석 공격
                pk::attack(src_unit, pk::get_hex_object(dst_pos)); 
                
                
                if (pk::is_in_screen(src_pos_))
                {
                    switch(pk::rand(4))
                    {
                        case 0: pk::say(pk::encode("낙석에 성공했군"), pk::get_person(src_unit.leader)); break;
                        case 1: pk::say(pk::encode("낙석이란 이런거지"), pk::get_person(src_unit.leader)); break;
                        case 2: pk::say(pk::encode("후후훗"), pk::get_person(src_unit.leader)); break;
                        case 3: pk::say(pk::encode("돌이 잘 굴러가는 군"), pk::get_person(src_unit.leader)); break;
                    }
                }
                
                // 기교점수
                pk::add_tp(pk::get_force(src_unit.get_force_id()), 10, dst_pos);
                // 능력경험치
                pk::add_stat_exp(src_unit, 무장능력_통솔, 4);
                // 공적
                pk::add_kouseki(src_unit, 100);
            }
            else
            {
                if (pk::is_in_screen(src_pos_))
                {
                    switch(pk::rand(2))
                    {
                        case 0: pk::say(pk::encode("낙석에 실패했는가"), pk::get_person(src_unit.leader)); break;
                        case 1: pk::say(pk::encode("쓸만한 돌이 없는가"), pk::get_person(src_unit.leader)); break;
                    }
                }
            }
            
            // 행동완료
			src_unit.action_done = true;
			if (int(pk::option["San11Option.EnableInfiniteAction"]) != 0)
				src_unit.action_done = false;
            
            return true;
        }

        int get_height_diff(const pk::point &in src, const pk::point &in dst)
		{
			return pk::get_height_map(pk::hex_pos_to_height_map_pos(src) + 2).height - pk::get_height_map(pk::hex_pos_to_height_map_pos(dst) + 2).height;
		}
        
	}

	Main main;
}