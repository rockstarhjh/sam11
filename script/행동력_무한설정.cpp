/*
// 만든이: 기마책사
// UPDATE: '20.10.22    / 최초적용
*/

namespace 행동력_무한설정
{
	//---------------------------------------------------------------------------------------
    // 유저 설정 (true = on, false = off)
    const bool 플레이어_무한행동력_설정  = true;   // (기본값 false) true 로 설정 시 플레이어 1군단 및 위임군단 행동력 무한
    const bool 컴퓨터세력_무한행동력_설정 = true;  // (기본값 false) true 로 설정 시 컴퓨터세력 행동력 무한
    
    //---------------------------------------------------------------------------------------
    
	
	class Main
	{
		
        
		Main()
		{
			pk::menu_item item;
			item.menu = 0;
			item.init = pk::building_menu_item_init_t(init);
			item.is_visible = pk::menu_item_is_visible_t(isVisible);
			item.is_enabled = pk::menu_item_is_enabled_t(isEnabled);
			item.get_text = pk::menu_item_get_text_t(getText);
			item.get_desc = pk::menu_item_get_desc_t(getDesc);
			item.handler = pk::menu_item_handler_t(handler);
			pk::add_menu_item(item);
            
            
            @prev_callback_256 = cast<pk::func256_t@>(pk::get_func(256));
			pk::reset_func(256);
			pk::set_func(256, pk::func256_t(callback_256));
            
		}
        
        pk::func256_t@ prev_callback_256;
        
        
        //------------------------------------------------------------
        // 건물메뉴 클릭 시 행동력 255로 설정
        void init(pk::building@ building)
		{
            if (building.get_id() < 건물_거점끝)
            {
                pk::district@ district = pk::get_district(building.get_district_id());
                
                if ((컴퓨터세력_무한행동력_설정 and !building.is_player()) or (플레이어_무한행동력_설정 and building.is_player()))
                    district.ap = 255;
                    
            }
		}
		string getText() { return pk::encode("무한행동력"); }
		string getDesc() { return pk::encode("무한행동력 설정"); }
		bool isVisible() { return false; }
        bool isEnabled() { return true; }
        bool handler()   { return true; }
        
        //------------------------------------------------------------

        
		// 컴퓨터 행동력 최대 : 명령 실행 전 최대치로..
		void callback_256(pk::ai_context@ context, pk::building@ building, int cmd)
		{
			if ((컴퓨터세력_무한행동력_설정 and!building.is_player()) or (플레이어_무한행동력_설정 and building.is_player()))
			{
				if (pk::get_scenario().ai_table.force[building.get_force_id()].troops_rank > 49)
				{
                    if (context.ap != 0)
                    {
                        pk::district@ district = pk::get_district(building.get_district_id());
                        district.ap = 255;
                        context.ap = 255;
                    }
				}
			}
			if (prev_callback_256 !is null)
				prev_callback_256(context, building, cmd);
		}

        
	}

	Main main;
}