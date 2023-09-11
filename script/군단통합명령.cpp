/*
@ 만든이: 기마책사
@ UPDATE: '19.3.3    / 최초적용 : 거점통합내정 메뉴 (거점내정, 군단징병, 군단순찰, 군단훈련, 군단생산(단야/구사/공방/조선))
@ UPDATE: '19.3.13   / 변경내용 : 패치명 변경, 군단생산 메뉴통합, 군단공략 메뉴추가, 메뉴 확장/축소 기능 추가
@ UPDATE: '19.3.20   / 변경내용 : 출진실행 후 메시지 오류수정, 군단장 화면이동 메뉴 추가
@ UPDATE: '19.4.5    / 변경내용 : 출병부대 군량비율 옵션 추가
@ UPDATE: '19.7.3    / 변경내용 : 출병부대 좌표오류 시 출진 취소 추가
@ UPDATE: '20.2.26   / 변경내용 : 군단생산 시 정란 선택 텍스트 오류 수정, 군단생산 거점리스트 추출방식 수정
*/

namespace 군단통합명령
{
	//=======================================================================================
    // ***** 군단명령 메뉴설명 *****
    // 군단장  : 선택한 군단의 군단장 소속 도시로 화면 이동
    // 군단공략 : 소속군단 내 실행조건을 만족하는 거점들을 선택하여 [출진] 일괄실행 (적 거점 공략)
    // 군단원군 : 소속군단 내 실행조건을 만족하는 거점들을 선택하여 [출진] 일괄실행 (아군 거점 구원)
    
    // 거점내정 : 해당거점의 [징병],[순찰],[훈련] 군단명령 연속실행
    // 군단징병 : 소속군단 내 실행조건을 만족하는 도시들을 선택하여 [징병] 일괄실행
    // 군단순찰 : 소속군단 내 실행조건을 만족하는 도시들을 선택하여 [순찰] 일괄실행
    // 군단훈련 : 소속군단 내 실행조건을 만족하는 거점들을 선택하여 [훈련] 일괄실행
    
    // 군단생산 : 소속군단 내 실행조건을 만족하는 도시들을 선택하여 [단야/구사/공방/조선] 일괄실행
	//---------------------------------------------------------------------------------------
    
    // 유저 설정
    const bool  군단명령_군단거점출병 = true;    // 출진조건 만족하는 거점들을 일괄출진 메뉴 활성화
    const bool  군단명령_징병순찰훈련 = true;    // 징병,순찰,훈련 등을 일괄실행 하는 메뉴군 활성화
    const bool  군단명령_군단병장생산 = true;    // 병장생산(단야,구사,공방,조선)을 일괄실행하는 메뉴 활성화
    const bool  군단명령_군단선택메뉴 = true;    // [군단장] 메뉴 사용여부 : 군단장 소속 거점으로 화면이동
    
    const bool  군단명령_위임군단적용 = true;   // 위임군단 군단메뉴 활성화 여부 (true=활성화, false=비활성화)
    const bool  군단명령_도시실행확인 = false;   // true설정 시 도시마다 확인메시지 실행 (간소화 플레이 시 false 권장)
    
    //---------------------------------------------------------------------------------------
    // 군단 내정
    const float 군단명령_징병최대비율 = 0.9f;  // 현재병력/최대병력 기준값 미만인 도시만 징병 실행 (0.0f ~ 1.0f 사이)
    const int   군단명령_징병최소치안 = 80;    // 치안 기준값 이상인 도시만 징병 실행 (0~100 사이)
    const int   군단명령_순찰최대치안 = 90;    // 치안 기준값 미만인 도시만 순찰 실행 (0~100 사이)
    const int   군단명령_훈련최소병력 = 1000;  // 병력 기준값 이상인 거점만 훈련 실행 (1 이상)
    const int   군단명령_훈련기력기준 = 115;   // 기력 기준값 미만인 거점만 훈련 실행 (1~120 사이)

    //---------------------------------------------------------------------------------------
    // 군단 생산
    const float 군단명령_생산최대비율 = 0.9f;  // 최대기준값 미만인 도시만 생산 실행 (0.0f ~ 1.0f 사이)
    
    //---------------------------------------------------------------------------------------
    // 군단 출병
    const int   군단명령_출병최소병력 = 4000;   // 군단 출진 시 부대병력 최소기준
    const int   군단명령_출병최대병력 = 8000;   // 군단 출진 시 부대병력 최대기준 (보유 병력, 무기, 지휘상한 이내 시)
    const int   군단명령_출병거점병력 = 20000;  // 출병거점의 최소병력 기준 (연속출진 시 기준병력 미만이 되면 출진불가)
    const float 군단명령_출병군량비율 = 1.5f;  // 부대병력 대비 군량 비율
    
    //=======================================================================================
    
	
	class Main
	{
		
		Main()
		{
            if (군단명령_징병순찰훈련 or 군단명령_군단병장생산 or 군단명령_군단거점출병)
            {
                pk::menu_item 군단명령;
                군단명령.menu = 0;        // 상위메뉴
                군단명령.pos = 0;
                군단명령.init = pk::building_menu_item_init_t(init);
                군단명령.is_visible = pk::menu_item_is_visible_t(isVisible);
                군단명령.is_enabled = pk::menu_item_is_enabled_t(isEnabled);
                군단명령.get_text = pk::menu_item_get_text_t(getText_군단명령);
                군단명령.get_desc = pk::menu_item_get_desc_t(getDesc_군단명령);
                menu_top = pk::add_menu_item(군단명령);
                
                // 군단장 소속거점으로 화면이동
                if (군단명령_군단선택메뉴)
                {
                    pk::menu_item 군단장;
                    군단장.menu = menu_top;   // 군단명령메뉴
                    군단장.init = pk::building_menu_item_init_t(init);
                    군단장.get_image_id = pk::menu_item_get_image_id_t(getImageID_orange);     // 주황색 메뉴
                    군단장.is_visible = pk::menu_item_is_visible_t(isVisible);
                    군단장.is_enabled = pk::menu_item_is_enabled_t(isEnabled);
                    군단장.get_text = pk::menu_item_get_text_t(getText_군단장);
                    군단장.get_desc = pk::menu_item_get_desc_t(getDesc_군단장);
                    군단장.handler = pk::menu_item_handler_t(handler_군단장);
                    pk::add_menu_item(군단장);
                }
                
                // 명령 메뉴 그룹
                if (군단명령_군단거점출병) add_menu_group_attack();   // 출진 하위메뉴 추가
                if (군단명령_징병순찰훈련) add_menu_group_govern();   // 내정 하위메뉴 추가
                if (군단명령_군단병장생산) add_menu_group_weapon();   // 생산 하위메뉴 추가
                
            }
		}
        
        
        void add_menu_group_attack()
        {

            // 군단출진 (확장/축소용 메뉴)
            pk::menu_item 군단출진;
			군단출진.menu = menu_top;   // 군단명령메뉴
			군단출진.init = pk::building_menu_item_init_t(init);
            군단출진.get_image_id = pk::menu_item_get_image_id_t(getImageID_orange);     // 주황색 메뉴
            군단출진.is_visible = pk::menu_item_is_visible_t(isVisible);
			군단출진.is_enabled = pk::menu_item_is_enabled_t(isEnabled_군단출진);
			군단출진.get_text = pk::menu_item_get_text_t(getText_군단출진);
			군단출진.get_desc = pk::menu_item_get_desc_t(getDesc_군단출진);
            군단출진.handler = pk::menu_item_handler_t(handler_군단출진);
			pk::add_menu_item(군단출진);
            
            
            // 군단공략
            pk::menu_item 군단공략;
			군단공략.menu = menu_top;   // 군단명령메뉴
			군단공략.init = pk::building_menu_item_init_t(init);
            군단공략.is_visible = pk::menu_item_is_visible_t(isVisible_군단출진);
			군단공략.is_enabled = pk::menu_item_is_enabled_t(isEnabled_군단공략);
			군단공략.get_text = pk::menu_item_get_text_t(getText_군단공략);
			군단공략.get_desc = pk::menu_item_get_desc_t(getDesc_군단공략);
            군단공략.handler = pk::menu_item_handler_t(handler_군단공략);
			pk::add_menu_item(군단공략);
            
            // 군단원군
            pk::menu_item 군단원군;
			군단원군.menu = menu_top;   // 군단명령메뉴
			군단원군.init = pk::building_menu_item_init_t(init);
            군단원군.is_visible = pk::menu_item_is_visible_t(isVisible_군단출진);
			군단원군.is_enabled = pk::menu_item_is_enabled_t(isEnabled_군단공략);
			군단원군.get_text = pk::menu_item_get_text_t(getText_군단원군);
			군단원군.get_desc = pk::menu_item_get_desc_t(getDesc_군단원군);
            군단원군.handler = pk::menu_item_handler_t(handler_군단원군);
			pk::add_menu_item(군단원군);
        }
        
        
        void add_menu_group_govern()
        {
        
            // 거점내정
            pk::menu_item 거점내정;
			거점내정.menu = menu_top;   // 군단명령메뉴
			거점내정.init = pk::building_menu_item_init_t(init);
            거점내정.get_image_id = pk::menu_item_get_image_id_t(getImageID_orange);     // 주황색 메뉴
            거점내정.is_visible = pk::menu_item_is_visible_t(isVisible);
			거점내정.is_enabled = pk::menu_item_is_enabled_t(isEnabled_거점내정);
			거점내정.get_text = pk::menu_item_get_text_t(getText_거점내정);
			거점내정.get_desc = pk::menu_item_get_desc_t(getDesc_거점내정);
            거점내정.handler = pk::menu_item_handler_t(handler_거점내정);
			pk::add_menu_item(거점내정);
            
            
            // 군단내정 (확장/축소용 메뉴)
            pk::menu_item 군단내정;
			군단내정.menu = menu_top;   // 군단명령메뉴
			군단내정.init = pk::building_menu_item_init_t(init);
            군단내정.get_image_id = pk::menu_item_get_image_id_t(getImageID_orange);     // 주황색 메뉴
            군단내정.is_visible = pk::menu_item_is_visible_t(isVisible);
			군단내정.is_enabled = pk::menu_item_is_enabled_t(isEnabled_군단내정);
			군단내정.get_text = pk::menu_item_get_text_t(getText_군단내정);
			군단내정.get_desc = pk::menu_item_get_desc_t(getDesc_군단내정);
            군단내정.handler = pk::menu_item_handler_t(handler_군단내정);
			pk::add_menu_item(군단내정);
            
            // 군단내정 (징병)
            pk::menu_item 군단징병;
			군단징병.menu = menu_top;   // 군단명령메뉴
			군단징병.init = pk::building_menu_item_init_t(init);
            군단징병.is_visible = pk::menu_item_is_visible_t(isVisible_군단내정);
			군단징병.is_enabled = pk::menu_item_is_enabled_t(isEnabled_군단징병);
			군단징병.get_text = pk::menu_item_get_text_t(getText_군단징병);
			군단징병.get_desc = pk::menu_item_get_desc_t(getDesc_군단징병);
            군단징병.handler = pk::menu_item_handler_t(handler_군단징병);
			pk::add_menu_item(군단징병);
            
            // 군단내정 (순찰)
            pk::menu_item 군단순찰;
			군단순찰.menu = menu_top;   // 군단명령메뉴
			군단순찰.init = pk::building_menu_item_init_t(init);
            군단순찰.is_visible = pk::menu_item_is_visible_t(isVisible_군단내정);
			군단순찰.is_enabled = pk::menu_item_is_enabled_t(isEnabled_군단순찰);
			군단순찰.get_text = pk::menu_item_get_text_t(getText_군단순찰);
			군단순찰.get_desc = pk::menu_item_get_desc_t(getDesc_군단순찰);
            군단순찰.handler = pk::menu_item_handler_t(handler_군단순찰);
			pk::add_menu_item(군단순찰);
            
            // 군단내정 (훈련)
            pk::menu_item 군단훈련;
			군단훈련.menu = menu_top;   // 군단명령메뉴
			군단훈련.init = pk::building_menu_item_init_t(init);
            군단훈련.is_visible = pk::menu_item_is_visible_t(isVisible_군단내정);
			군단훈련.is_enabled = pk::menu_item_is_enabled_t(isEnabled_군단훈련);
			군단훈련.get_text = pk::menu_item_get_text_t(getText_군단훈련);
			군단훈련.get_desc = pk::menu_item_get_desc_t(getDesc_군단훈련);
            군단훈련.handler = pk::menu_item_handler_t(handler_군단훈련);
			pk::add_menu_item(군단훈련);
            
        }
        
        
        void add_menu_group_weapon()
        {
            // 군단생산 (확장/축소용 메뉴)
            pk::menu_item 군단생산;
			군단생산.menu = menu_top;   // 군단명령메뉴
			군단생산.init = pk::building_menu_item_init_t(init);
			군단생산.get_image_id = pk::menu_item_get_image_id_t(getImageID_orange);     // 주황색 메뉴
            군단생산.is_visible = pk::menu_item_is_visible_t(isVisible);
			군단생산.is_enabled = pk::menu_item_is_enabled_t(isEnabled_군단생산);
			군단생산.get_text = pk::menu_item_get_text_t(getText_군단생산);
			군단생산.get_desc = pk::menu_item_get_desc_t(getDesc_군단생산);
            군단생산.handler = pk::menu_item_handler_t(handler_군단생산);
			pk::add_menu_item(군단생산);
            
            // 군단생산 (단야)
            pk::menu_item 군단단야;
			군단단야.menu = menu_top;   // 군단명령메뉴
			군단단야.init = pk::building_menu_item_init_t(init);
            군단단야.is_visible = pk::menu_item_is_visible_t(isVisible_군단생산);
			군단단야.is_enabled = pk::menu_item_is_enabled_t(isEnabled_군단단야);
			군단단야.get_text = pk::menu_item_get_text_t(getText_군단단야);
			군단단야.get_desc = pk::menu_item_get_desc_t(getDesc_군단단야);
            군단단야.handler = pk::menu_item_handler_t(handler_군단단야);
			pk::add_menu_item(군단단야);
            
            // 군단생산 (구사)
            pk::menu_item 군단구사;
			군단구사.menu = menu_top;   // 군단명령메뉴
			군단구사.init = pk::building_menu_item_init_t(init);
            군단구사.is_visible = pk::menu_item_is_visible_t(isVisible_군단생산);
			군단구사.is_enabled = pk::menu_item_is_enabled_t(isEnabled_군단구사);
			군단구사.get_text = pk::menu_item_get_text_t(getText_군단구사);
			군단구사.get_desc = pk::menu_item_get_desc_t(getDesc_군단구사);
            군단구사.handler = pk::menu_item_handler_t(handler_군단구사);
			pk::add_menu_item(군단구사);
            
            // 군단생산 (공방)
            pk::menu_item 군단공방;
			군단공방.menu = menu_top;   // 군단명령메뉴
			군단공방.init = pk::building_menu_item_init_t(init);
            군단공방.is_visible = pk::menu_item_is_visible_t(isVisible_군단생산);
			군단공방.is_enabled = pk::menu_item_is_enabled_t(isEnabled_군단공방);
			군단공방.get_text = pk::menu_item_get_text_t(getText_군단공방);
			군단공방.get_desc = pk::menu_item_get_desc_t(getDesc_군단공방);
            군단공방.handler = pk::menu_item_handler_t(handler_군단공방);
			pk::add_menu_item(군단공방);
            
            // 군단생산 (조선)
            pk::menu_item 군단조선;
			군단조선.menu = menu_top;   // 군단명령메뉴
			군단조선.init = pk::building_menu_item_init_t(init);
            군단조선.is_visible = pk::menu_item_is_visible_t(isVisible_군단생산);
			군단조선.is_enabled = pk::menu_item_is_enabled_t(isEnabled_군단조선);
			군단조선.get_text = pk::menu_item_get_text_t(getText_군단조선);
			군단조선.get_desc = pk::menu_item_get_desc_t(getDesc_군단조선);
            군단조선.handler = pk::menu_item_handler_t(handler_군단조선);
			pk::add_menu_item(군단조선);
            
            
        }
        

        //---------------------------------------------------------------------------------------
        // 스크립트 동작용 변수 (절대 수정 금지)
        int menu_top;
        
        int menu_extend;    // 메뉴 확장코드
        int menu_attack = 1;
        int menu_govern = 2;
        int menu_outfit = 3;
        
        int delay = 300;
        
		pk::building@ building;
		pk::force@ force;
        pk::district@ district;
        pk::person@ kunshu;
        pk::person@ totoku;
        pk::list<pk::district@> district_list;
        
        pk::list<pk::building@> list_drafts;  // 징병가능 거점
        pk::list<pk::building@> list_patrol;  // 순찰가능 거점
        pk::list<pk::building@> list_drills;  // 훈련가능 거점
        
        pk::array<bool> arr_available(4, false);
        string cmd_names;
         
        int ap_drafts = 20;
        int ap_patrol = 20;
        int ap_drills = 20;
        float ref_troops_ratio = pk::min(1.0f, pk::max(0.0f, 군단명령_징병최대비율));
        int ref_order_drafts = pk::min(100, pk::max(1, 군단명령_징병최소치안));
        int ref_order_patrol = pk::min(100, pk::max(1, 군단명령_순찰최대치안));
        int ref_min_troops = pk::max(1, 군단명령_훈련최소병력);
        int ref_energy = pk::min(120, pk::max(1, 군단명령_훈련기력기준));
        
        pk::list<pk::building@> list_outfit0;   // 대장간가능 거점
        pk::list<pk::building@> list_outfit1;   // 마구간가능 거점
        pk::list<pk::building@> list_outfit2;   // 공방가능 거점
        pk::list<pk::building@> list_outfit3;   // 조선가능 거점
        
        int ap_outfit = 20;
        float ref_weapon_ratio = pk::min(1.0f, pk::max(0.0f, 군단명령_생산최대비율));
        
        int weapon_siege0; 
        int weapon_siege1;
        int weapon_warship;
        pk::array<int> weapon_cost(병기_끝, 0);
        pk::array<int> weapon_cost_max(4, -1);
        pk::array<int> weapon_outfit(4, -1);
        pk::array<string> arr_weapon_name = {"검", "창", "극", "노", "군마", "충차", "정란", "투석", "목수", "주가", "누선", "투함", "??"};
        
        pk::list<pk::building@> list_src_base;
        pk::list<pk::building@> list_dst_base;
        pk::list<pk::building@> list_district_base;    // 군단공략가능 거점
        pk::list<pk::building@> list_force_base;       // 아군 거점
        pk::list<pk::building@> list_enemy_base;       // 적 거점
        pk::array<int> arr_tekisei(병종_끝, 적성_C);
        int ap_march = 10;
        
        
        //---------------------------------------------------------------------------------------
        // 군단 명령 상위 메뉴
        //---------------------------------------------------------------------------------------
        
        int getImageID_blue()    // 파란색
		{ return 856; }
        int getImageID_green()    // 녹색
		{ return 889; }
        int getImageID_orange()   // 주황색
		{ return 1249; }
        
        //---------------------------------------------------------------------------------------
        
		void init(pk::building@ building_t)
		{
            @building = @building_t;
            @force = pk::get_force(building.get_force_id());
            district_list = pk::get_district_list(force);
            
            if (building.facility <= 시설_항구)
            {
                @district = pk::get_district(building.get_district_id());
                @kunshu = pk::get_person(pk::get_kunshu_id(building));
                @totoku = pk::get_person(pk::get_totoku_id(building));
                
                get_weapon_expense();     // 무기 관련 정보 초기화
                
                get_cmd_available();   // 거점의 명령별 실행가능여부 초기화
                get_base_available();  // 명령별 실행 가능한 소속군단 거점리스트 초기화
                
                if (menu_extend == menu_govern 
                    and list_drafts.count == 0 and list_patrol.count == 0 and list_drills.count == 0)
                    menu_extend = -1;
                
                else if (menu_extend == menu_outfit 
                    and list_outfit0.count == 0 and list_outfit1.count == 0 and list_outfit2.count == 0 and list_outfit3.count == 0)
                    menu_extend = -1;
            }
		}

        bool isVisible()
        {
            if (pk::is_campaign()) return false;
            if (building.get_id() >= 건물_거점끝) return false;
            if (building.facility > 시설_항구) return false;
            if (!군단명령_위임군단적용 and district.no > 1) return false;
            return true;
        }
        
		bool isEnabled()
		{ 
            if (building.get_id() >= 건물_거점끝) return false;
			return true;
		}
        
		string getText_군단명령()
		{
			return pk::encode("군단명령");
		}

		string getDesc_군단명령()
		{
            return pk::encode("군단 단위 명령를 실행합니다");
		}

        
        //---------------------------------------------------------------------------------------
        //  군단장 화면이동 메뉴
        //---------------------------------------------------------------------------------------
        
		string getText_군단장()
		{
			return pk::encode("군단장");
		}

		string getDesc_군단장()
		{
            return pk::encode("군단장 소속 거점으로 화면을 이동합니다");
		}

        bool handler_군단장()
        {
            pk::district@ district_t;
            
            if (!군단명령_위임군단적용 or district_list.count <= 1)
            {
                @district_t = @district;
            }
            else
            {
                pk::list<pk::district@> district_sel = pk::district_selector(pk::encode("군단 선택"), pk::encode("군단을 선택하세요"), district_list, 1, 1); 
                if (district_sel.count == 0) return false;
                @district_t = district_sel[0];
            }
            pk::person@ totoku_t = pk::get_person(pk::get_totoku_id(district_t));
            if (!pk::is_alive(totoku_t)) return false;
            @base_t = pk::get_building(totoku_t.service);
            if (!pk::is_alive(base_t)) return false;
            
            delay = 1;
            pk::scene(pk::scene_t(goto_base));  // 거점으로 화면 이동
            delay = 300;
            
            if (totoku_t.get_id() == kunshu.get_id())
            {
                pk::say(pk::encode(pk::format("\x1b[2x{}군단\x1b[0x에 명령을 하달하겠다", district_t.no)), kunshu);
                pk::play_voice(0x3E, kunshu);
            }
            else
            {
                string kunshu_name = pk::decode(pk::get_name(kunshu));
                pk::say(pk::encode(pk::format("\x1b[1x{}\x1b[0x님, \x1b[2x{}군단\x1b[0x에 명령을!!", kunshu_name, district_t.no)), totoku_t);
                pk::play_voice(0x3C, totoku_t);
            }
        
            return true;
        }
        
        
        
        
        //---------------------------------------------------------------------------------------
        // 군단명령 초기화용 리스트 업데이트 함수
        //---------------------------------------------------------------------------------------
        
        // 무기정보 초기화
        void get_weapon_expense()
        {
            weapon_siege0  = (pk::has_tech(building, 기교_목수개발))? 병기_목수 : 병기_충차;
            weapon_siege1  = (pk::has_tech(building, 기교_투석개발))? 병기_투석 : 병기_정란;
            weapon_warship = (pk::has_tech(building, 기교_투석개발))? 병기_투함 : 병기_누선;
            
            for (int id = 0; id < 병기_끝; id++)
            {
                if (id != 병기_검 and id != 병기_주가)
                    weapon_cost[id] = pk::get_equipment(id).gold_cost;
            }
            
            // 시설별 가장 비싼 무기 검색
            int cost = 0;
            cost = pk::max(weapon_cost[병기_창], weapon_cost[병기_극], weapon_cost[병기_노]);
            if      (cost == weapon_cost[병기_창]) weapon_cost_max[0] = 병기_창;
            else if (cost == weapon_cost[병기_극]) weapon_cost_max[0] = 병기_극;
            else if (cost == weapon_cost[병기_노]) weapon_cost_max[0] = 병기_노;
            
            cost = pk::max(weapon_cost[weapon_siege0], weapon_cost[weapon_siege1]);
            if      (cost == weapon_cost[weapon_siege0]) weapon_cost_max[2] = weapon_siege0;
            else if (cost == weapon_cost[weapon_siege1]) weapon_cost_max[2] = weapon_siege1;
            
            weapon_cost_max[1] = 병기_군마;
            weapon_cost_max[3] = weapon_warship;
           
        }
        
        // 보유량 가장 적은 무기ID 검색
        void get_min_amount_weapon(pk::building@ base)
        {
            int amount = 0;
            amount = pk::min(int(pk::get_weapon_amount(base, 병기_창)), int(pk::get_weapon_amount(base, 병기_극)), int(pk::get_weapon_amount(base, 병기_노)));
            if      (amount == int(pk::get_weapon_amount(base, 병기_창))) weapon_outfit[0] = 병기_창;
            else if (amount == int(pk::get_weapon_amount(base, 병기_극))) weapon_outfit[0] = 병기_극;
            else if (amount == int(pk::get_weapon_amount(base, 병기_노))) weapon_outfit[0] = 병기_노;
            
            amount = pk::min(int(pk::get_weapon_amount(base, weapon_siege0)), int(pk::get_weapon_amount(base, weapon_siege1)));
            if      (amount == int(pk::get_weapon_amount(base, weapon_siege0))) weapon_outfit[2] = weapon_siege0;
            else if (amount == int(pk::get_weapon_amount(base, weapon_siege1))) weapon_outfit[2] = weapon_siege1;
            
            weapon_outfit[1] = 병기_군마;
            weapon_outfit[3] = weapon_warship;
        }
        
        
        // 거점의 내정가능 여부 체크
        void get_cmd_available()
        {
            pk::building@ base = @building;
            arr_available[1] = func_base_drafts(base, false); // 징병가능여부
            arr_available[2] = func_base_patrol(base, false); // 순찰가능여부
            arr_available[3] = func_base_drills(base, false); // 훈련가능여부
            
            // 실행가능 내정 유무
            arr_available[0] = (arr_available[1] or arr_available[2] or arr_available[3]);  
            
            // 실행가능한 내정
            cmd_names = "";
            if (arr_available[1]) cmd_names += ((cmd_names == "")? "" : ",") + "징병";
            if (arr_available[2]) cmd_names += ((cmd_names == "")? "" : ",") + "순찰";
            if (arr_available[3]) cmd_names += ((cmd_names == "")? "" : ",") + "훈련";
        }
        
        
        // 징병/순찰/훈련 가능한 군단 내 도시 리스트
        void get_base_available()
        {
            // 리스트 초기화
            list_drafts.clear();
            list_patrol.clear();
            list_drills.clear();
            
            list_outfit0.clear();
            list_outfit1.clear();
            list_outfit2.clear();
            list_outfit3.clear();
            
            list_district_base.clear();
            list_force_base.clear();
            list_enemy_base.clear();
            
            // 군단 도시 리스트에서 조건 확인
            for (int base_id = 0; base_id < 건물_거점끝; base_id++)
            {
                pk::building@ base = pk::get_building(base_id);
                if (district.get_id() == base.get_district_id())
                {
                    // 군단내정
                    if (func_base_drafts(base, false) and !list_drafts.contains(base))  list_drafts.add(base);
                    if (func_base_patrol(base, false) and !list_patrol.contains(base))  list_patrol.add(base);
                    if (func_base_drills(base, false) and !list_drills.contains(base))  list_drills.add(base);
                    
                    // 군단생산
                    get_min_amount_weapon(base);
                    if (check_outfit_cost(base, weapon_cost_max[0]) and func_base_outfit(base, weapon_outfit[0], false) and !list_outfit0.contains(base))  list_outfit0.add(base);
                    if (check_outfit_cost(base, weapon_cost_max[1]) and func_base_outfit(base, weapon_outfit[1], false) and !list_outfit1.contains(base))  list_outfit1.add(base);
                    if (check_outfit_cost(base, weapon_cost_max[2]) and func_base_outfit(base, weapon_outfit[2], false) and !list_outfit2.contains(base))  list_outfit2.add(base);
                    if (check_outfit_cost(base, weapon_cost_max[3]) and func_base_outfit(base, weapon_outfit[3], false) and !list_outfit3.contains(base))  list_outfit3.add(base);
                    
                    // 군단공략
                    if (func_unit_march(base, null, false) and !list_district_base.contains(base)) list_district_base.add(base);
                }
            }
            
            for (int target_id = 0; target_id < 건물_거점끝; target_id++)
            {
                pk::building@ target = pk::get_building(target_id);
                if (building.get_force_id() == target.get_force_id() and !list_force_base.contains(target))
                    list_force_base.add(target);
            }
            
            for (int target_id = 0; target_id < 건물_거점끝; target_id++)
            {
                pk::building@ target = pk::get_building(target_id);
                if (pk::is_enemy(building, target))
                {
                    pk::array<pk::building@> arr_force_base = pk::list_to_array(list_force_base);
                    for (int i = 0; i < int(arr_force_base.length); i++)
                    {
                        pk::building@ base = arr_force_base[i];
                        if (pk::is_neighbor_base(base.get_id(), target.get_id()) and !list_enemy_base.contains(target))
                            list_enemy_base.add(target);
                    }
                }
            }
            
        }
        
        
        //---------------------------------------------------------------------------------------
        // 거점내정 메뉴
        //---------------------------------------------------------------------------------------
        
		string getText_거점내정()
		{
            return pk::encode("거점내정");
		}

		string getDesc_거점내정()
		{
            if (!arr_available[0]) 
                return pk::encode("실행가능한 군단명령이 없습니다");
            
            return pk::encode(pk::format("\x1b[1x{}\x1b[0x에서 \x1b[2x{}\x1b[0x 군단명령을 실행합니다.", pk::decode(pk::get_name(building)), cmd_names));
		}

		bool isEnabled_거점내정()
		{
            if (!arr_available[0]) return false;
            if (building.get_id() >= 건물_거점끝) return false;
			return true;
		}
        
        bool handler_거점내정()
        {
            pk::building@ base = @building;
            
            // 군단명령 실행 확인 메시지
            string base_name = pk::decode(pk::get_name(base));
            bool confirm = pk::yes_no(pk::encode(pk::format("\x1b[1x{}\x1b[0x에서 \x1b[2x{}\x1b[0x을 실행할까요?", base_name, cmd_names)));
            if (!confirm) return false; // 취소 종료
            
            // 통합 내정 순차 실행
            pk::array<bool> arr_done(4, false);
            arr_done[1] = func_base_drafts(base, true);
            arr_done[2] = func_base_patrol(base, true);
            arr_done[3] = func_base_drills(base, true);
            
            // 실행 완료한 내정명
            cmd_names = "";
            if (arr_done[1]) cmd_names += ((cmd_names == "")? "" : ",") + "징병";
            if (arr_done[2]) cmd_names += ((cmd_names == "")? "" : ",") + "순찰";
            if (arr_done[3]) cmd_names += ((cmd_names == "")? "" : ",") + "훈련";
            
            // 실행 거점 결과 메시지 함수 호출
            message_base_cmd(base, cmd_names);

            return true;
        }
        
        
        //---------------------------------------------------------------------------------------
        // 군단 내정 중간 메뉴
        //---------------------------------------------------------------------------------------
        
		string getText_군단내정()
		{
			return pk::encode("군단내정");
		}

		string getDesc_군단내정()
		{
            if (list_drafts.count == 0 and list_patrol.count == 0 and list_drills.count == 0)
                return pk::encode("실행가능한 도시가 없습니다");
            
            return pk::encode("군단 내정 메뉴를 확장/축소합니다");
		}
        
		bool isEnabled_군단내정()
		{ 
            if (list_drafts.count == 0 and list_patrol.count == 0 and list_drills.count == 0) 
                return false;
            if (building.get_id() >= 건물_거점끝) return false;
			return true;
		}
        
        bool isVisible_군단내정()
        {
            if (menu_extend != menu_govern) return false;
            return true;
        }
        
        bool handler_군단내정()
        {
            menu_extend = (menu_extend == menu_govern)? -1 : menu_govern;
            
            return false;
        }
        
        
        //---------------------------------------------------------------------------------------
        // 군단징병 메뉴
        //---------------------------------------------------------------------------------------
        
		string getText_군단징병()
		{
			return pk::encode("군단징병");
		}

		string getDesc_군단징병()
		{
            if (list_drafts.count == 0) 
                return pk::encode("실행가능한 도시가 없습니다");
            
            return pk::encode("군단 내 도시들의 징병을 실행합니다");
		}

		bool isEnabled_군단징병()
		{ 
            if (list_drafts.count == 0) return false;
            
            if (building.get_id() >= 건물_거점끝) return false;
			return true;
		}
        
        bool handler_군단징병()
        {
            // 실행가능한 최대 도시 수
            int max = int(int(district.ap) / ap_drafts);
            if (max < 1) return false;
            
            // 도시 선택
            pk::list<pk::building@> list_base_sel;
            list_base_sel = pk::building_selector(pk::encode("징병 도시 선택"), 
                                                  pk::encode(pk::format("징병을 실행할 도시를 선택하세요. (최대 {}개 선택 가능)", pk::min(max, list_drafts.count) )), 
                                                  list_drafts, 1, max, list_base_sel);
            if (list_base_sel.count == 0) return false; // 취소 종료
            
            // 징병 실행
            pk::array<pk::building@> arr_base_cmd;
            pk::array<pk::building@> arr_base_sel = pk::list_to_array(list_base_sel);
            for (int i = 0; i < int(arr_base_sel.length); i++)
            {
                pk::building@ base = arr_base_sel[i];
                
                // 거점별 실행여부 확인
                bool cmd_confirm = false;
                if (!군단명령_도시실행확인) cmd_confirm = true;
                else cmd_confirm = get_cmd_confirm(base, "징병");
                
                // 도시 징병 실행 함수 호출
                if (cmd_confirm)
                {
                    bool action_done = func_base_drafts(base, true);
                    if (action_done) 
                        arr_base_cmd.insertLast(base);
                }
            }
            
            // 실행 도시 결과 메시지 함수 호출
            message_district_cmd(arr_base_cmd, "징병");
            
            return true;
        }
        
        
        //---------------------------------------------------------------------------------------
        // 군단순찰 메뉴
        //---------------------------------------------------------------------------------------
        
		string getText_군단순찰()
		{
			return pk::encode("군단순찰");
		}

		string getDesc_군단순찰()
		{
            if (list_patrol.count == 0) 
                return pk::encode("실행가능한 도시가 없습니다");
            
            return pk::encode("군단 내 도시들의 순찰을 실행합니다");
		}

		bool isEnabled_군단순찰()
		{ 
            if (list_patrol.count == 0) return false;
            
            if (building.get_id() >= 건물_거점끝) return false;
			return true;
		}

        bool handler_군단순찰()
        {
            // 실행가능한 최대 도시 수
            int max = int(int(district.ap) / ap_patrol);
            if (max < 1) return false;
            
            // 도시 선택
            pk::list<pk::building@> list_base_sel;
            list_base_sel = pk::building_selector(pk::encode("순찰 도시 선택"), 
                                                  pk::encode(pk::format("순찰을 실행할 도시를 선택하세요. (최대 {}개 선택 가능)", pk::min(max, list_patrol.count) )), 
                                                  list_patrol, 1, max, list_base_sel);
            if (list_base_sel.count == 0) return false; // 취소 종료
            
            // 순찰 실행
            pk::array<pk::building@> arr_base_cmd;
            pk::array<pk::building@> arr_base_sel = pk::list_to_array(list_base_sel);
            for (int i = 0; i < int(arr_base_sel.length); i++)
            {
                pk::building@ base = arr_base_sel[i];
                
                // 거점별 실행여부 확인
                bool cmd_confirm = false;
                if (!군단명령_도시실행확인) cmd_confirm = true;
                else cmd_confirm = get_cmd_confirm(base, "순찰");
                
                // 도시 순찰 실행 함수 호출
                if (cmd_confirm)
                {
                    bool action_done = func_base_patrol(base, true);
                    if (action_done) 
                        arr_base_cmd.insertLast(base);
                }
            }
            
            // 실행 도시 결과 메시지 함수 호출
            message_district_cmd(arr_base_cmd, "순찰");
            
            return true;
        }
        
        
        //---------------------------------------------------------------------------------------
        // 군단훈련 메뉴
        //---------------------------------------------------------------------------------------
        
		string getText_군단훈련()
		{
			return pk::encode("군단훈련");
		}

		string getDesc_군단훈련()
		{
            if (list_drills.count == 0) 
                return pk::encode("실행가능한 거점이 없습니다");
            
            return pk::encode("군단 내 거점들의 훈련을 실행합니다");
		}

		bool isEnabled_군단훈련()
		{ 
            if (list_drills.count == 0) return false;
            
            if (building.get_id() >= 건물_거점끝) return false;
			return true;
		}
        
        bool handler_군단훈련()
        {
            // 실행가능한 최대 거점 수
            int max = int(int(district.ap) / ap_drills);
            if (max < 1) return false;
            
            // 거점 선택
            pk::list<pk::building@> list_base_sel;
            list_base_sel = pk::building_selector(pk::encode("훈련 거점 선택"), 
                                                  pk::encode(pk::format("훈련을 실행할 거점을 선택하세요. (최대 {}개 선택 가능)", pk::min(max, list_drills.count) )), 
                                                  list_drills, 1, max, list_base_sel);
            if (list_base_sel.count == 0) return false; // 취소 종료
            
            // 훈련 실행
            pk::array<pk::building@> arr_base_cmd;
            pk::array<pk::building@> arr_base_sel = pk::list_to_array(list_base_sel);
            for (int i = 0; i < int(arr_base_sel.length); i++)
            {
                pk::building@ base = arr_base_sel[i];
                
                // 거점별 실행여부 확인
                bool cmd_confirm = false;
                if (!군단명령_도시실행확인) cmd_confirm = true;
                else cmd_confirm = get_cmd_confirm(base, "훈련");
                
                // 거점 훈련 실행 함수 호출
                if (cmd_confirm)
                {
                    bool action_done = func_base_drills(base, true);
                    if (action_done)
                        arr_base_cmd.insertLast(base);
                }
            }
            
            // 실행 거점 결과 메시지 함수 호출
            message_district_cmd(arr_base_cmd, "훈련");
            
            return true;
        }
        
        
        
        //---------------------------------------------------------------------------------------
        // 명령 처리 함수
        //---------------------------------------------------------------------------------------
        
        // 유저 확인 시 거점으로 화면 이동
        pk::building@ base_t;
        void goto_base()
        {
            pk::point pos = base_t.pos;
            for (int i = 0; i < 2; i++)
            {
                pk::point pos_t;
                pos_t.x = pos.x + 1;
                pos_t.y = pos.y;
                if (pk::is_valid_pos(pos_t))
                    pos.x = pos.x + 1;
            }
            pk::wait(delay);
            pk::move_screen(pos, 1);
        }
        
        // 거점별 화면이동 후 실행여부 반환
        bool get_cmd_confirm(pk::building@ base, string cmd_name)
        {
            @base_t = @base;
            pk::scene(pk::scene_t(goto_base));  // 거점으로 화면 이동
            
            // 거점별 실행여부 확인
            string base_name = pk::decode(pk::get_name(base));
            bool cmd_confirm = pk::yes_no(pk::encode(pk::format("\x1b[1x{}\x1b[0x에서 \x1b[2x{}\x1b[0x을 실행할까요?", base_name, cmd_name))); 
        
            return cmd_confirm;
        }
        
        // 실행 거점 결과 메시지 함수 : 군단내정
        void message_district_cmd(pk::array<pk::building@> arr_base_sel, string cmd_name)
        {
            // 실행 거점 없음
            if (int(arr_base_sel.length) == 0) 
            {
                if (kunshu.get_id() == totoku.get_id())
                    pk::message_box(pk::encode("명령을 실행한 거점이 없군"), totoku);
                else
                    pk::message_box(pk::encode("명령을 실행한 거점이 없습니다"), totoku);
                
                return; // 종료
            }
            
            string base_name = pk::decode(pk::get_name(arr_base_sel[0]));
            string base_names;
            if (int(arr_base_sel.length) == 1) base_names = base_name;
            else base_names = pk::format("{} 외 {}개 거점", base_name, (int(arr_base_sel.length)-1) );
            
            if (kunshu.get_id() == totoku.get_id())
                pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x에서 \x1b[2x{}\x1b[0x을 실행하였군", base_names, cmd_name)), totoku);
            else
                pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x에서 \x1b[2x{}\x1b[0x을 실행하였습니다", base_names, cmd_name)), totoku);
        }
        
        // 실행 거점 결과 메시지 함수 : 거점내정
        void message_base_cmd(pk::building@ base, string cmd_name)
        {
            // 실행 거점 없음
            if (!pk::is_alive(base)) 
            {
                if (kunshu.get_id() == totoku.get_id())
                    pk::message_box(pk::encode("실행가능한 명령이 없군"), totoku);
                else
                    pk::message_box(pk::encode("실행가능한 명령이 없습니다"), totoku);
                
                return; // 종료
            }
            
            string base_name = pk::decode(pk::get_name(base));
            
            if (kunshu.get_id() == totoku.get_id())
                pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x에서 \x1b[2x{}\x1b[0x을 실행하였군", base_name, cmd_name)), totoku);
            else
                pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x에서 \x1b[2x{}\x1b[0x을 실행하였습니다", base_name, cmd_name)), totoku);
        }
        
        
        //---------------------------------------------------------------------------------------
        
        // 도시 징병 실행 함수
        bool func_base_drafts(pk::building@ base, bool do_cmd = true)
        {
            int base_id = base.get_id();
            if (base_id < 건물_도시시작 or base_id >= 건물_도시끝) return false; // 도시가 아니면 종료
            
            // 실행가능 무장수 확인
            bool enough_men = (pk::get_idle_person_list(base).count > 0);
            if (!enough_men) return false;    // 실행무장 없으면 종료
            
            // 징병가능여부 확인
            pk::city@ city = pk::building_to_city(base);
            bool enough_barrack = (int(city.barracks_counter) > 0);    
            bool enough_order = (int(city.public_order) >= ref_order_drafts);
            bool need_troops = (int(pk::get_troops(base)) < int(ref_troops_ratio * float(pk::get_max_troops(base))));
            
            // 징병 가능한 도시인지 확인
            if (int(district.ap) >= ap_drafts and enough_men and city.gold >= 300 and enough_barrack and enough_order and need_troops)
            {
                if (do_cmd) // 명령 실행
                {
                    // 명령 실행 무장
                    int stat  = int(pk::core["징병.능력"]);
                    int skill = int(pk::core["징병.특기"]);
                    pk::array<pk::person@> actors = get_cmd_actors(base, stat, skill);
                    
                    // 명령 정보
                    pk::recruit_cmd_info cmd_draft;
                    @cmd_draft.base = base;
                    for(int i = 0; i < int(actors.length); i++)
                    {
                        @cmd_draft.actors[i] = actors[i];
                    }
                    // 명령 실행
                    pk::command(cmd_draft);
                }
                return true;
            }
            return false;
        }        
        
        //---------------------------------------------------------------------------------------
        
        // 도시 순찰 실행 함수
        bool func_base_patrol(pk::building@ base, bool do_cmd = true)
        {
            int base_id = base.get_id();
            if (base_id < 건물_도시시작 or base_id >= 건물_도시끝) return false; // 도시가 아니면 종료
            
            // 실행가능 무장수 확인
            bool enough_men = (pk::get_idle_person_list(base).count > 0);  
            if (!enough_men) return false;    // 실행무장 없으면 종료
            
            // 순찰가능여부 확인
            pk::city@ city = pk::building_to_city(base);
            bool need_patrol = (int(city.public_order) < ref_order_patrol);    
            
            // 순찰 가능한 도시인지 확인
            if (int(district.ap) >= ap_patrol and enough_men and city.gold >= 100 and !city.inspections_ended and need_patrol)
            {
                if (do_cmd) // 명령 실행
                {
                    int stat  = int(pk::core["순찰.능력"]);
                    pk::array<pk::person@> actors = get_cmd_actors(base, stat, -1);
                    
                    // 명령 정보
                    pk::inspections_cmd_info cmd_patrol;
                    @cmd_patrol.base = base;
                    for(int i = 0; i < int(actors.length); i++)
                    {
                        @cmd_patrol.actors[i] = actors[i];
                    }
                    // 명령 실행
                    pk::command(cmd_patrol);
                }
                return true;
            }              
            return false;            
        }        
        
        //---------------------------------------------------------------------------------------
        
        // 거점 훈련 실행 함수
        bool func_base_drills(pk::building@ base, bool do_cmd = true)
        {
            int base_id = base.get_id();
            if (base_id < 0 or base_id >= 건물_거점끝) return false; // 거점이 아니면 종료
            
            // 실행가능 무장수 확인
            bool enough_men = (pk::get_idle_person_list(base).count > 0);  
            if (!enough_men) return false;    // 실행무장 없으면 종료
            
            // 병력 기준 확인
            bool enough_troops = (pk::get_troops(base) >= ref_min_troops);    
            // 훈련 완료 확인
            bool drills_ended = false;      
            if (건물_도시시작 <= base_id and base_id < 건물_도시끝)
                drills_ended = pk::building_to_city(base).drills_ended;
            if (건물_관문시작 <= base_id and base_id < 건물_관문끝)
                drills_ended = pk::building_to_gate(base).drills_ended;
            if (건물_항구시작 <= base_id and base_id < 건물_항구끝)
                drills_ended = pk::building_to_port(base).drills_ended;
            
            // 훈련필요여부 확인
           bool need_drill = (pk::get_energy(base) < ref_energy);
                    
            // 훈련 가능한 거점인지 확인
            if (int(district.ap) >= get_ap_cmd(base, ap_drills, 시설_군사부) and enough_men and enough_troops and !drills_ended and need_drill)
            {
                if (do_cmd) // 명령 실행
                {
                    int stat  = int(pk::core["훈련.능력"]);
                    pk::array<pk::person@> actors = get_cmd_actors(base, stat, -1);
                    
                    // 명령 정보
                    pk::drill_cmd_info cmd_drill;
                    @cmd_drill.base = base;
                    for(int i = 0; i < int(actors.length); i++)
                    {
                        @cmd_drill.actors[i] = actors[i];
                    }
                    // 명령 실행
                    pk::command(cmd_drill);  
                }
                return true;
            }  
            return false;
        }        
        
        //---------------------------------------------------------------------------------------
        
        // 실행 무장 리스트 추출 함수
        int cmd_stat;
        int cmd_skill;
        pk::array<pk::person@> get_cmd_actors(pk::building@ base, int stat, int skill)
        {
            cmd_stat  = stat;
            cmd_skill = skill;
            pk::array<pk::person@> actors(3, null);
            
            // 실행가능 무장 확인
            pk::list<pk::person@> list_idle_person = pk::get_idle_person_list(base);
            if (list_idle_person.count == 0) return actors;
            
            // 능력 높은 순으로 정렬, 특기 우대
            list_idle_person.sort(function(a, b)
            {
                if (main.cmd_skill >= 0)    // 특기 보유 시
                {
                    bool a_skill = pk::has_skill(a, main.cmd_skill);
                    bool b_skill = pk::has_skill(b, main.cmd_skill);
                    if ( a_skill and !b_skill) return true;
                    if (!a_skill and  b_skill) return false;

                    return a.stat[main.cmd_stat] > b.stat[main.cmd_stat];
                }                    
                
                return a.stat[main.cmd_stat] > b.stat[main.cmd_stat];
            } );
            
            // 최대 3명까지
            pk::array<pk::person@> arr_idle_person = pk::list_to_array(list_idle_person);
            int min_actors = pk::min(3, pk::max(1, int(arr_idle_person.length)/2));
            int sum_stat = 0;
            for (int i = 0; i < min_actors; i++)
            {
                @actors[i] = arr_idle_person[i];
            }
            
            return actors;
        }
        
        //---------------------------------------------------------------------------------------
        
        // 보조시설에 유무에 따른 내정 행동력 계산 함수
        int get_ap_cmd(pk::building@ base, int ref_ap, int facility_id)
        {
            pk::city@ city = pk::building_to_city(base);
            if (!pk::is_alive(city)) return ref_ap;
            
            int ap_cmd = ref_ap;
            if (pk::has_facility(city, facility_id))
                ap_cmd = ref_ap / 2;
            
            return ap_cmd;
        }
        
        
        
        
        //---------------------------------------------------------------------------------------
        // 군단생산 중간 메뉴
        //---------------------------------------------------------------------------------------
        
		string getText_군단생산()
		{
			return pk::encode("군단생산");
		}

		string getDesc_군단생산()
		{
            if (list_outfit0.count == 0 and list_outfit1.count == 0 and list_outfit2.count == 0 and list_outfit3.count == 0) 
                return pk::encode("실행가능한 도시가 없습니다");
            
            return pk::encode("군단 생산 메뉴를 확장/축소합니다");
		}

		bool isEnabled_군단생산()
		{ 
            if (list_outfit0.count == 0 and list_outfit1.count == 0 and list_outfit2.count == 0 and list_outfit3.count == 0)
                return false;
            
            if (building.get_id() >= 건물_거점끝) return false;
			return true;
		}

        bool isVisible_군단생산()
        {
            if (menu_extend != menu_outfit) return false;
            return true;
        }
        
        
        bool handler_군단생산()
        {
            menu_extend = (menu_extend == menu_outfit)? -1 : menu_outfit;
            
            return false;
        }
        
        
        //---------------------------------------------------------------------------------------
        // 군단생산 하위 메뉴
        //---------------------------------------------------------------------------------------
        
        
		string getText_군단단야()
		{
			return pk::encode("군단단야");
		}

		string getDesc_군단단야()
		{
            if (list_outfit0.count == 0) 
                return pk::encode("실행가능한 도시가 없습니다");
            
            return pk::encode("군단 내 도시들의 대장간 생산를 실행합니다");
		}

		bool isEnabled_군단단야()
		{ 
            if (list_outfit0.count == 0) return false;
            
            if (building.get_id() >= 건물_거점끝) return false;
			return true;
		}
        
        bool handler_군단단야()
        {
            bool handler_result = sub_handler_군단생산(0, list_outfit0);
            return handler_result;
        }
        
        //---------------------------------------------------------------------------------------
        
        string getText_군단구사()
		{
			return pk::encode("군단구사");
		}

		string getDesc_군단구사()
		{
            if (list_outfit1.count == 0) 
                return pk::encode("실행가능한 도시가 없습니다");
            
            return pk::encode("군단 내 도시들의 마구간 생산를 실행합니다");
		}

		bool isEnabled_군단구사()
		{ 
            if (list_outfit1.count == 0) return false;
            
            if (building.get_id() >= 건물_거점끝) return false;
			return true;
		}
        
        bool handler_군단구사()
        {
            bool handler_result = sub_handler_군단생산(1, list_outfit1);
            return handler_result;
        }
        
        //---------------------------------------------------------------------------------------
        
        string getText_군단공방()
		{
			return pk::encode("군단공방");
		}

		string getDesc_군단공방()
		{
            if (list_outfit2.count == 0) 
                return pk::encode("실행가능한 도시가 없습니다");
            
            return pk::encode("군단 내 도시들의 공방 생산를 실행합니다");
		}

		bool isEnabled_군단공방()
		{ 
            if (list_outfit2.count == 0) return false;
            
            if (building.get_id() >= 건물_거점끝) return false;
			return true;
		}
        
        bool handler_군단공방()
        {
            bool handler_result = sub_handler_군단생산(2, list_outfit2);
            return handler_result;
        }
        
        //---------------------------------------------------------------------------------------
        
        string getText_군단조선()
		{
			return pk::encode("군단조선");
		}

		string getDesc_군단조선()
		{
            if (list_outfit3.count == 0) 
                return pk::encode("실행가능한 도시가 없습니다");
            
            return pk::encode("군단 내 도시들의 생산를 실행합니다");
		}

		bool isEnabled_군단조선()
		{ 
            if (list_outfit3.count == 0) return false;
            
            if (building.get_id() >= 건물_거점끝) return false;
			return true;
		}
        
        bool handler_군단조선()
        {
            bool handler_result = sub_handler_군단생산(3, list_outfit3);
            return handler_result;
        }
        
       //---------------------------------------------------------------------------------------
       
        bool sub_handler_군단생산(int facility_select, pk::list<pk::building@> list_outfit_sel)
        {
            // 생산 타입에 따른 생산가능 거점리스트
            if (list_outfit_sel.count == 0) return false; // 취소 종료
            
            // 실행가능한 최대 도시 수
            int max = int(int(district.ap) / ap_outfit);
            if (max < 1) return false;
            
            // 도시 선택
            pk::list<pk::building@> list_base_sel;
            list_base_sel = pk::building_selector(pk::encode("생산 도시 선택"), 
                                                  pk::encode(pk::format("생산을 실행할 도시를 선택하세요. (최대 {}개 선택 가능)", pk::min(max, list_outfit_sel.count) )), 
                                                  list_outfit_sel, 1, max, list_base_sel);
            if (list_base_sel.count == 0) return false; // 취소 종료
            
            // 생산 무기 선택 (생산 메뉴별 핸들러에서 매개변수로 전달)
            int weapon_id = get_outfit_weapon_id(facility_select);    // 병장기 선택 확인 메시지
            
            if (weapon_id <= 병기_검 or weapon_id == 병기_주가 or weapon_id >= 병기_끝) return false;
            string weapon_name = arr_weapon_name[weapon_id];
            
            // 생산 실행
            pk::array<pk::building@> arr_base_cmd;
            pk::array<pk::building@> arr_base_sel = pk::list_to_array(list_base_sel);
            for (int i = 0; i < int(arr_base_sel.length); i++)
            {
                pk::building@ base = arr_base_sel[i];
                
                // 거점별 실행여부 확인
                bool cmd_confirm = false;
                if (!군단명령_도시실행확인) cmd_confirm = true;
                else cmd_confirm = get_cmd_confirm(base, pk::format("{} 생산", weapon_name));
                
                // 도시 생산 실행 함수 호출
                if (cmd_confirm)
                {
                    bool action_done = func_base_outfit(base, weapon_id, true);
                    if (action_done) 
                        arr_base_cmd.insertLast(base);
                }
            }
            
            // 실행 도시 결과 메시지 함수 호출
            message_district_cmd(arr_base_cmd, pk::format("{} 생산", weapon_name));
            
            
            return true;
        }
        
        
        //---------------------------------------------------------------------------------------
        
        // 도시 생산 실행 함수
        bool func_base_outfit(pk::building@ base, int weapon_id, bool do_cmd = true)
        {
            int base_id = base.get_id();
            if (base_id < 건물_도시시작 or base_id >= 건물_도시끝) return false; // 도시가 아니면 종료
            
            // 실행가능 무장수 확인
            bool enough_men = (pk::get_idle_person_list(base).count > 0);
            if (!enough_men) return false;    // 실행무장 없으면 종료
            
            // 생산필요여부 확인
            pk::city@ city = pk::building_to_city(base);
            if (weapon_id <= 병기_검 or weapon_id == 병기_주가 or weapon_id >= 병기_끝) return false;
            bool need_weapon = (int(pk::get_weapon_amount(base, weapon_id)) < int(ref_weapon_ratio * float(pk::get_max_weapon_amount(base, weapon_id))));
            
            // 생산타입별 생산시설 카운트 확인
            int outfit_type = get_outfit_type(weapon_id);
            bool enough_outfit = false;
            switch(outfit_type)
            {
                case 0: enough_outfit = (int(city.blacksmith_counter) > 0);  break;
                case 1: enough_outfit = (int(city.stable_counter) > 0);      break;
                case 2: enough_outfit = (int(city.workshop_counter) > 0);    break;
                case 3: enough_outfit = (int(city.shipyard_counter) > 0);    break;
            }
            
            pk::equipment@ eqp = pk::get_equipment(weapon_id);
            
            // 생산 가능한 도시인지 확인
            if (int(district.ap) >= ap_outfit and enough_men and int(city.gold) >= int(eqp.gold_cost) and enough_outfit and need_weapon)
            {
                if (do_cmd) // 명령 실행
                {
                    // 명령 실행 무장
                    int stat = int(pk::core["병기생산.능력"]);
                    int skill = -1;
                    switch(outfit_type)
                    {
                        case  0: skill = int(pk::core["병기생산.대장간특기"]);  break;
                        case  1: skill = int(pk::core["병기생산.마구간특기"]);  break;
                        case  2: skill = int(pk::core["병기생산.공방특기"]);  break;
                        case  3: skill = int(pk::core["병기생산.조선특기"]);  break;
                        default: skill = -1; break;
                    }
                    pk::array<pk::person@> actors = get_cmd_actors(base, stat, skill);
                    
                    // 명령 정보
                    pk::outfit_cmd_info cmd_outfit;
                    @cmd_outfit.base   = base;
                    cmd_outfit.weapon = weapon_id;
                    for(int i = 0; i < int(actors.length); i++)
                    {
                        @cmd_outfit.actors[i] = actors[i];
                    }
                    // 명령 실행
                    pk::command(cmd_outfit);
                }
                return true;
            }
            return false;
        }        
        
        //---------------------------------------------------------------------------------------
        
        int get_outfit_weapon_id(int outfit_type)
        {
            int weapon_id = -1;
            
            // 단야
            if (outfit_type == 0)
            {
                int answer = pk::choose({ pk::encode("창"), pk::encode("극"), pk::encode("노"), pk::encode("취소") }, 
                                          pk::encode("어떤 무기를 생산하겠습니까?"), totoku );
                // 병기 선택 결과 처리
                if      (answer == 0) weapon_id = 병기_창;
                else if (answer == 1) weapon_id = 병기_극;
                else if (answer == 2) weapon_id = 병기_노;
                else return -1;
            }
            
            // 구사
            else if (outfit_type == 1)
            {
                weapon_id = 병기_군마;
            }
            
            // 공방
            else if (outfit_type == 2)
            {
                string s0 = arr_weapon_name[weapon_siege0];
                string s1 = arr_weapon_name[weapon_siege1];
                
                int answer = pk::choose({ pk::encode(s0), pk::encode(s1), pk::encode("취소") }, 
                                          pk::encode("어떤 무기를 생산하겠습니까?"), totoku );
                // 병기 선택 결과 처리
                if      (answer == 0) weapon_id = weapon_siege0;
                else if (answer == 1) weapon_id = weapon_siege1;
                else return -1;
            }
            
            // 조선
            else if (outfit_type == 3)
            {
                weapon_id = weapon_warship;
            }
            
            return weapon_id;
        }
        
        //---------------------------------------------------------------------------------------
        
        int get_outfit_type(int weapon_id)
        {
            int outfit_type = -1;
            
            if (weapon_id >= 병기_창 and weapon_id <= 병기_노)         outfit_type = 0;
            else if (weapon_id == 병기_군마)                          outfit_type = 1;
            else if (weapon_id >= 병기_충차 and weapon_id <= 병기_목수) outfit_type = 2;          
            else if (weapon_id >= 병기_누선 and weapon_id <= 병기_투함) outfit_type = 3;     

            return outfit_type;
        }
        
        //---------------------------------------------------------------------------------------
        
        bool check_outfit_cost(pk::building@ base, int weapon_id)
        {
            int base_id = base.get_id();
            if (base_id < 건물_도시시작 or base_id >= 건물_도시끝) return false; // 도시가 아니면 종료
            
            pk::city@ city = pk::building_to_city(base);
            if (weapon_id <= 병기_검 or weapon_id == 병기_주가 or weapon_id >= 병기_끝) return false;
            
            pk::equipment@ eqp = pk::get_equipment(weapon_id);
            
            return (int(city.gold) >= int(eqp.gold_cost));
        }
        
        
        //---------------------------------------------------------------------------------------
        // 군단 출진 중간 메뉴
        //---------------------------------------------------------------------------------------
        
		string getText_군단출진()
		{
			return pk::encode("군단출진");
		}

		string getDesc_군단출진()
		{
            if (list_district_base.count == 0) 
                return pk::encode("실행가능한 도시가 없습니다");
            
            return pk::encode("군단 내정 메뉴를 확장/축소합니다");
		}
        
		bool isEnabled_군단출진()
		{ 
            if (list_district_base.count == 0) return false;
            if (building.get_id() >= 건물_거점끝) return false;
			return true;
		}
        
        bool isVisible_군단출진()
        {
            if (menu_extend != menu_attack) return false;
            return true;
        }
        
        bool handler_군단출진()
        {
            menu_extend = (menu_extend == menu_attack)? -1 : menu_attack;
            
            return false;
        }
        
        
        
        //---------------------------------------------------------------------------------------
        // 군단공략 메뉴
        //---------------------------------------------------------------------------------------
        
        bool isEnabled_군단공략()
		{ 
            if (list_district_base.count == 0) return false;
        
            if (building.get_id() >= 건물_거점끝) return false;
			return true;
        }
        
		string getText_군단공략()
		{
			return pk::encode("군단공략");
		}

		string getDesc_군단공략()
		{
            if (list_district_base.count == 0) 
                return pk::encode("실행 가능한 거점이 없습니다");
            
            return pk::encode("선택한 적 거점을 향해 군단 내 거점들로부터 부대를 일괄 출진시킵니다");
		}
        
        bool handler_군단공략()
        {
            list_src_base.clear();
            list_dst_base.clear();
            
            // 목표 적 거점
            list_dst_base = list_enemy_base;
            
            // 목표 거점 선택
            pk::list<pk::building@> list_target = pk::building_selector(pk::encode("목표 거점 선택"), pk::encode("목표 거점을 선택합니다."), list_dst_base, 1, 1);
            if(list_target.count == 0) return false; // 미선택 시 취소 종료
            pk::building@ target = pk::get_building(list_target[0].get_id());
            
            // 출진 거점 리스트 
            list_src_base = list_district_base;
            
            // 거점 출진 명령
            bool handler_result = func_base_march(target);
            
            return handler_result;
        }
        
        //---------------------------------------------------------------------------------------
        
		string getText_군단원군()
		{
			return pk::encode("군단원군");
		}

		string getDesc_군단원군()
		{
            if (list_district_base.count == 0) 
                return pk::encode("실행 가능한 거점이 없습니다");
            
            return pk::encode("선택한 아군 거점을 향해 군단 내 거점들로부터 부대를 일괄 출진시킵니다");
		}
        
        
        bool handler_군단원군()
        {
            list_src_base.clear();
            list_dst_base.clear();
            
            // 목표 아군 거점
            list_dst_base = list_force_base;

            // 목표 거점 선택
            pk::list<pk::building@> list_target = pk::building_selector(pk::encode("목표 거점 선택"), pk::encode("목표 거점을 선택합니다."), list_dst_base, 1, 1);
            if(list_target.count == 0) return false; // 미선택 시 취소 종료
            pk::building@ target = pk::get_building(list_target[0].get_id());
            
            // 출진 거점 리스트 업데이트
            pk::array<pk::building@> arr_district_base = pk::list_to_array(list_district_base);
            for (int i = 0; i < int(arr_district_base.length); i++)
            {
               if (target.get_id() != arr_district_base[i].get_id())
                    list_src_base.add(arr_district_base[i]);    // 목표 거점은 제외
            }
            
            // 거점 출진 명령
            bool handler_result = func_base_march(target);
            
            return handler_result;
        }
        
        //---------------------------------------------------------------------------------------
        
        bool func_base_march(pk::building@ target)
        {
            // 실행가능한 최대 거점 수
            int max = int(int(district.ap) / ap_march);
            if (max < 1) return false;
            
            // 출진 거점 선택
            pk::list<pk::building@> list_base_sel;
            list_base_sel = pk::building_selector(pk::encode("출진 거점 선택"), 
                                                  pk::encode(pk::format("출진을 실행할 거점을 선택하세요. (최대 {}개 선택 가능)", pk::min(max, list_src_base.count) )), 
                                                  list_src_base, 1, max, list_base_sel);
            if (list_base_sel.count == 0) return false; // 취소 종료
            
            // 출진 실행
            pk::array<pk::building@> arr_base_cmd;
            pk::array<pk::building@> arr_base_sel = pk::list_to_array(list_base_sel);
            for (int i = 0; i < int(arr_base_sel.length); i++)
            {
                pk::building@ base = arr_base_sel[i];
                
                // 거점별 실행여부 확인
                bool cmd_confirm = false;
                if (!군단명령_도시실행확인) cmd_confirm = true;
                else cmd_confirm = get_cmd_confirm(base, "출진");
                
                // 도시 출진 실행 함수 호출
                if (cmd_confirm)
                {
                    bool action_done = func_unit_march(base, pk::get_hex_object(target.pos), true);
                    if (action_done) 
                        arr_base_cmd.insertLast(base);
                }
            }
            
            // 실행 도시 결과 메시지 함수 호출
            message_district_cmd(arr_base_cmd, "출진");
            
            
            
            return true;
        }
        
        //---------------------------------------------------------------------------------------
        
        bool func_unit_march(pk::building@ base, pk::hex_object@ target, bool do_cmd = true)
        {
            // 명령 가능한 무장이 있는지 확인
            pk::list<pk::person@> person_list = pk::get_idle_person_list(base);
			if (person_list.count == 0) return false;   // 무장 부족
            
            if (pk::get_troops(base) < (군단명령_출병최소병력 + 군단명령_출병거점병력)) return false;  // 병력 부족
            
            int max = int(int(district.ap) / get_ap_cmd(base, ap_march, 시설_군사부));
            if (max < 1) return false;      // 행동력 부족
            
            int weapon_id = 병기_검;
            int unit_troops;
            func_weapon_select(base, 군단명령_출병최소병력, pk::get_troops(base), weapon_id, unit_troops);    // 최적 병과의 최소 병력 반환
            if (weapon_id == 0) return false;    // 육상 무기 또는 병력 부족
            
            
            if (do_cmd)
            {
                // 무장 정렬.
                person_list.sort(function(a, b)
                {
                    int cmd_a = pk::get_command(a);
                    int cmd_b = pk::get_command(b);
                    int stat_a = a.stat[무장능력_무력] + a.stat[무장능력_통솔];
                    int stat_b = a.stat[무장능력_무력] + b.stat[무장능력_통솔];
                    return ((cmd_a == cmd_b)? (stat_a > stat_b) : (cmd_a > cmd_b)) ;     // 지휘-능력순
                });
                
                // 출병할 무장 선택 (최소1, 최대8)
                pk::list<pk::person@> person_sel = pk::person_selector(pk::encode("출병 무장 선택"), pk::encode("출병할 무장을 선택합니다."), person_list, 1, pk::min(8, max, person_list.count));
                if (person_sel.count == 0) return false;
                
                
                for (int id = 0; id < person_sel.count; id++)
                {
                    if (int(district.ap) < get_ap_cmd(base, ap_march, 시설_군사부)) continue;
                    if (pk::get_troops(base) < (군단명령_출병최소병력 + 군단명령_출병거점병력)) continue;

                    // 출병할 장수 설정
                    pk::person@ member0 = pk::get_person(person_sel[id].get_id());
                    pk::person@ member1 = null;
                    pk::person@ member2 = null;
                    
                    // 적성 업데이트
                    func_get_tekisei(member0, member1, member2);
                    
                    // 육상 무기 병력 설정
                    int gnd_weapon_id = 병기_검;
                    int unit_command = pk::min(pk::get_command(member0), pk::get_troops(base));     // 지휘가능 최대병력 (지휘값, 도시병력 중 최소)
                    func_weapon_select(base, 군단명령_출병최소병력, unit_command, gnd_weapon_id, unit_troops);    // 최적 병과의 최소 병력 반환
                    if (gnd_weapon_id == 0) return false;    // 육상 무기 또는 병력 부족
                    
                    unit_command = pk::min(군단명령_출병최대병력, unit_command, pk::get_weapon_amount(base, gnd_weapon_id));   // 해당 병과의 최대병력 재계산 (지휘가능 병력, 무기보유량 중 최소)
                    unit_troops = pk::max(unit_troops, unit_command);
                    int unit_food = pk::min( int(unit_troops * 군단명령_출병군량비율), int(pk::get_food(base)) );    // 병량 설정
                    
                    // 수상 무기 선택
                    int sea_weapon_id = 병기_주가;
                    if (arr_tekisei[병종_수군] == 적성_C)
                        sea_weapon_id = 병기_주가;
                    else
                    {
                        if      (pk::get_weapon_amount(base, 병기_누선) > 0) sea_weapon_id = 병기_누선;
                        else if (pk::get_weapon_amount(base, 병기_투함) > 0) sea_weapon_id = 병기_투함;
                    }
                    
                    // 부대 출진
                    pk::march_cmd_info march_cmd;
                    if (pk::is_alive(member0)) march_cmd.member[0] = member0.get_id();
                    if (pk::is_alive(member1)) march_cmd.member[1] = member1.get_id();
                    if (pk::is_alive(member2)) march_cmd.member[2] = member2.get_id();
                    @march_cmd.base  = @base;
                    march_cmd.type   = 부대종류_전투;
                    march_cmd.food   = unit_food;
                    march_cmd.gold   = 0;
                    march_cmd.troops = unit_troops;
                    march_cmd.weapon_id[0] = gnd_weapon_id;
                    march_cmd.weapon_id[1] = sea_weapon_id;
                    march_cmd.weapon_amount[0] = unit_troops;
                    march_cmd.weapon_amount[1] = (sea_weapon_id == 병기_주가)? 0 : 1;
                    int unit_id = pk::command(march_cmd);
                    pk::unit@ unit = pk::get_unit(unit_id);
                    
                    
                    // 출병부대 이동
                    pk::set_order(unit, 부대임무_공격, target.get_pos());
                    pk::run_order(unit);
                    
                    // 출진불가 시 부대 강제 제거 및 물자 반환 ('19.7.3)
                    pk::building@ base_check = pk::get_building(unit.pos);
                    if (pk::is_alive(base_check) and base_check.get_id() == base.get_id())
                    {
                        pk::kill(unit);
                        pk::add_food(base, unit_food, false);
                        pk::add_gold(base, 0, false);
                        pk::add_troops(base, unit_troops);
                        pk::add_weapon_amount(base, gnd_weapon_id, unit_troops);
                        if (sea_weapon_id != 병기_주가) 
                            pk::add_weapon_amount(base, sea_weapon_id, unit_troops);
                        
                        if (pk::is_alive(member0)) member0.action_done = false;
                        if (pk::is_alive(member1)) member1.action_done = false;
                        if (pk::is_alive(member2)) member2.action_done = false;
                    }
                    
                    // 부대 출진 불가로 행동력 반환
                    if (!pk::is_alive(unit))
                    {
                        district.ap += get_ap_cmd(base, ap_march, 시설_군사부);
                    }
                    // 부대 행동 종료 설정
                    else
                    {
                        if (pk::is_in_screen(unit.pos))
                        {
                            string target_name = pk::decode(pk::get_name(target));
                            switch(pk::rand(2))
                            {
                                case 0: pk::play_voice(0x1A, pk::get_person(unit.leader)); break; // 음성 : 전투_이동
                                case 1: pk::play_voice(0x1B, pk::get_person(unit.leader)); break; // 음성 : 전투_이동
                            }
                            switch(pk::rand(4))
                            {
                                case 0: pk::say(pk::encode(pk::format("\x1b[2x{}\x1b[0x을 향해 출병하라", target_name)), member0, unit); break;
                                case 1: pk::say(pk::encode(pk::format("\x1b[2x{}\x1b[0x으로 진군하라", target_name)), member0, unit); break;
                                case 2: pk::say(pk::encode(pk::format("\x1b[2x{}\x1b[0x으로 향하겠습니다", target_name)), member0, unit); break;
                                case 3: pk::say(pk::encode(pk::format("\x1b[2x{}\x1b[0x을 공격하라", target_name)), member0, unit); break;
                            }
                        }
                        
                        if (unit.get_id() != -1)
                            unit.action_done = true;
                        if (int(pk::option["San11Option.EnableInfiniteAction"]) != 0)
                            unit.action_done = false;
                    }
                }
            }

			return true;
        }
        
        
        // 무기 선택 함수
        void func_weapon_select(pk::building@ building_t, int troops, int troops_max, int &out weapon_sel, int &out troops_sel)
        {
            int weapon_max = 0;
            int best_tekisei = 적성_C;
            
            weapon_sel = 병기_검;
            troops_sel = 0;
            
            // 출병병력 이상 보유한 무기 중 최고 적성 확인
            for (int id = 병기_창; id <= 병기_군마; id++)
            {
                int tekisei = arr_tekisei[pk::equipment_id_to_heishu(id)];
                int weapon_t = pk::get_weapon_amount(building_t, id);
                if (군단명령_출병최소병력 <= weapon_t and best_tekisei <= tekisei)
                    best_tekisei = tekisei;
            }
            
            // 최고 적성 이상의 병과 중 무기 가장 많은 병과 선택
            for (int id = 병기_창; id <= 병기_군마; id++)
            {
                int tekisei = arr_tekisei[pk::equipment_id_to_heishu(id)];
                int weapon_t = pk::get_weapon_amount(building_t, id);
                if (군단명령_출병최소병력 <= weapon_t and weapon_max <= weapon_t and best_tekisei <= tekisei)
                {
                    best_tekisei = tekisei;
                    weapon_max = weapon_t;
                    weapon_sel = id;
                    troops_sel = pk::min(troops, weapon_max, troops_max);
                }
            }
            
            if (weapon_sel == 0)
            {
                troops_sel = troops;
            }
        }
        
        void func_get_tekisei(pk::person@ p0, pk::person@ p1, pk::person@ p2)
        {
            for (int i = 0; i < 6; i++)
            {
                if (!pk::is_alive(p0) and !pk::is_alive(p1) and !pk::is_alive(p2))
                    arr_tekisei[i] = 적성_C;
                else if (pk::is_alive(p0) and !pk::is_alive(p1) and !pk::is_alive(p2))
                    arr_tekisei[i] = p0.tekisei[i];
                else if (pk::is_alive(p0) and pk::is_alive(p1) and !pk::is_alive(p2))
                    arr_tekisei[i] = pk::max(p0.tekisei[i], p1.tekisei[i]);
                else if (pk::is_alive(p0) and pk::is_alive(p1) and pk::is_alive(p2))
                    arr_tekisei[i] = pk::max(p0.tekisei[i], p1.tekisei[i], p2.tekisei[i]);
            }
        }
        
        
	}

	Main main;
}