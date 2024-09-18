/*
@ 만든이: 기마책사
@ UPDATE: '19.5.3    / 최초적용 : 인재탐색 연속실행 메뉴
@ UPDATE: '19.5.8    / 변경내용 : 설전 옵션 체크 기능 추가 (설전OFF 시에만 연속탐색 사용가능)
*/

namespace 연속인재탐색
{
	//---------------------------------------------------------------------------------------
    
	
	class Main
	{
		int debate_opt;
		pk::building@ building;
		pk::force@ force;
		pk::city@ city;
        pk::person@ taishu;
        pk::district@ district;
        pk::list<pk::person@> person_list;
        int ACTION_COST_탐색;

		Main()
		{
            
            // 탐색메뉴
			pk::menu_item 연속탐색;
			연속탐색.menu = 102;    //인재메뉴
            연속탐색.init = pk::building_menu_item_init_t(init);
			연속탐색.is_visible = pk::menu_item_is_visible_t(isVisible_연속탐색);
			연속탐색.is_enabled = pk::menu_item_is_enabled_t(isEnabled_연속탐색);
			연속탐색.get_text = pk::menu_item_get_text_t(getText_연속탐색);
			연속탐색.get_desc = pk::menu_item_get_desc_t(getDesc_연속탐색);
			연속탐색.handler = pk::menu_item_handler_t(handler_연속탐색);
			pk::add_menu_item(연속탐색);
            
		}

        
        //---------------------------------------------------------------------------------------
        // 인재 상위 메뉴
        //---------------------------------------------------------------------------------------
        
		void init(pk::building@ building_t)
		{
            debate_opt = int(pk::option["Debate"]);
            
			@building = @building_t;
			@force = pk::get_force(building.get_force_id());
            @city = pk::building_to_city(building);
            @taishu = pk::get_person(pk::get_taishu_id(building));
            @district = pk::get_district(building.get_district_id());
            
            person_list = pk::get_idle_person_list(building);   // 실행 거점의 미행동 무장 리스트
            
            ACTION_COST_탐색 = get_hrcmd_ap(city);
            
		}
        
        
        // 인재부 검색하여 행동력 반환
        int get_hrcmd_ap(pk::city@ city_t)
        {
            int hrcmd_ap = 20;
            if (pk::is_alive(city_t))
            {
                if (pk::has_facility(city, 시설_인재부))
                    return hrcmd_ap / 2;
            }
            return hrcmd_ap;
        }
        
        
        //---------------------------------------------------------------------------------------

		string getText_연속탐색()
		{
			return pk::encode("연속탐색");
		}

		string getDesc_연속탐색()
		{
            if (debate_opt < 2)
                return pk::encode("연속탐색을 사용하려면 설전 옵션을\x1b[17x'안본다'\x1b[0x로 설정하십시오.");
            
            else if (person_list.count == 0)
                return pk::encode("실행 가능한 무장이 없습니다");
            else if (int(district.ap) < ACTION_COST_탐색)
                return pk::encode(pk::format("행동력이 부족합니다 (행동력{} 필요)", ACTION_COST_탐색));
			else
				return pk::encode(pk::format("도시를 탐색합니다 (행동력{})", ACTION_COST_탐색));
		}

		bool isEnabled_연속탐색()
		{ 
            if (debate_opt < 2) return false;
            
            else if (person_list.count == 0) return false;
            else if (int(district.ap) < ACTION_COST_탐색) return false;
			return true;
		}

        bool isVisible_연속탐색()
        {
            if (pk::is_campaign()) return false;   // 튜토리얼이나 결전제패 비활성화
            
            if (!pk::is_alive(city)) return false;
            else if (!building.is_player()) return false;   // 컴퓨터 AI 세력
            else if (!pk::is_player_controlled(building)) return false;  // 플레이어 위임군단
            return true;
        }
        
		bool handler_연속탐색()
		{
            // 현재 설전 옵션 체크('19.5.8)
            if (debate_opt < 2) 
            {
                pk::message_box(pk::encode("연속탐색을 사용하려면 설전 옵션을\n\x1b[17x'안본다'\x1b[0x로 설정하십시오."));
                return false;
            }
            
            
            // 실행가능 무장리스트 확인
			if (person_list.count == 0) return false;
            
            int max = district.ap / ACTION_COST_탐색;
            if (max == 0) return false;
            
            // 실행무장 선택하기
            pk::list<pk::person@> actors;
            string person_name;
            bool confirm = false;
            while (!confirm)
            {
                actors = pk::person_selector(pk::encode("탐색 무장 선택"), pk::encode("탐색할 무장을 선택합니다."), person_list, 1, pk::min(max, person_list.count), actors, 26);
                int count = int(actors.count);
                if (count == 0) return false; // 미선택 시 취소 종료
                
                person_name = pk::decode( pk::get_name(pk::get_person(actors[0].get_id())) );
                if (count > 1)
                    person_name = pk::format("{} 외 {}명", person_name, count-1);
            
                confirm = pk::yes_no(pk::encode(pk::format("\x1b[1x{}\x1b[0x에게 탐색을 시키겠습니까?", person_name)));
            }
            
            
            
            // 연속 탐색 실행
            for (int i = 0; i < actors.count; i++)
            {    
                pk::person@ actor = pk::get_person(actors[i].get_id());

                // 탐색 명령
                pk::search_cmd_info cmd_search;
                @cmd_search.base  = building;
                @cmd_search.actor = actor;
                pk::command(cmd_search);
            }
            
            
			return true;
		}
        
        //---------------------------------------------------------------------------------------
        
        bool 디버그모드 = true;

	}

	Main main;
}