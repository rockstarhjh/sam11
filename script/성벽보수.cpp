/*
@ 만든이: 기마책사
@ UPDATE: '18.11.6    / 최초적용
@ UPDATE: '18.11.16   / 변경내용: 효과음 최적화
@ UPDATE: '18.11.22   / 변경내용: AI가 성벽보수 실행할 알고리즘 추가, 성벽보수 턴별 1회로 제한
@ UPDATE: '18.12.3    / 변경내용: 실행1회 제한 오류 수정
@ UPDATE: '19.1.4     / 변경내용: 행동력 관련 함수 수정 (거점별 군단)
*/

namespace 성벽보수
{
	//---------------------------------------------------------------------------------------
    
	const int ACTION_COST_성벽보수 = 20;
	const int ENERGY_COST_성벽보수 = 30;
	const int GOLD_COST_성벽보수 = 300;
    
	const int KEY = pk::hash("보수");
    
    
    const bool 성벽보수_AI실행 = true;
    
    //---------------------------------------------------------------------------------------
    
    
	
	class Main
	{
		
		pk::building@ building;
		pk::force@ force;
		pk::city@ city;
        pk::district@ district;
		pk::person@ taishu;
        pk::point building_pos;
        uint16 building_gold;
		int building_energy;
        

		Main()
		{
            // 성벽보수 메뉴 (유저용)
			pk::menu_item 성벽보수;
			성벽보수.menu = 100;        // 도시메뉴
			성벽보수.pos = 8;
			성벽보수.shortcut = "8";
			성벽보수.init = pk::building_menu_item_init_t(init);
			성벽보수.is_visible = pk::menu_item_is_visible_t(isVisible_성벽보수);
			성벽보수.is_enabled = pk::menu_item_is_enabled_t(isEnabled_성벽보수);
			성벽보수.get_text = pk::menu_item_get_text_t(getText_성벽보수);
			성벽보수.get_desc = pk::menu_item_get_desc_t(getDesc_성벽보수);
			성벽보수.handler = pk::menu_item_handler_t(handler_성벽보수);
			pk::add_menu_item(성벽보수);
            
            // AI용
            pk::bind(111, pk::trigger111_t(onTurnStart));
            
		}

        
        //---------------------------------------------------------------------------------------
        
		void init(pk::building@ building_t)
		{
			@building = @building_t;
			@force = pk::get_force(building.get_force_id());
            @city = pk::building_to_city(building);
            @taishu = pk::get_person(pk::get_taishu_id(building));
            @district = pk::get_district(building.get_district_id());
            
            building_gold = pk::get_gold(building);
            building_energy = pk::get_energy(building);
            
            building_pos = building.pos;
		}

		string getText_성벽보수()
		{
			return pk::encode("성벽보수");
		}

		string getDesc_성벽보수()
		{
            if (!pk::is_alive(taishu) or taishu.action_done)
                return pk::encode("태수가 없거나 이미 태수의 행동을 완료했습니다");
            else if (int(district.ap) < ACTION_COST_성벽보수)
                return pk::encode(pk::format("행동력이 부족합니다 (행동력{} 필요)", ACTION_COST_성벽보수));
            else if (pk::get_hp(city) >= pk::get_max_hp(city))
                return pk::encode("내구도가 최대입니다");
            else if (building_energy < ENERGY_COST_성벽보수)
				return pk::encode(pk::format("기력이 부족합니다 (기력{} 필요)", ENERGY_COST_성벽보수));
			else if (building_gold < GOLD_COST_성벽보수)
				return pk::encode(pk::format("금이 부족합니다 (금{} 필요)", GOLD_COST_성벽보수));
			else
				return pk::encode(pk::format("성벽보수를 실행합니다 (기력{}, 금{} 사용)", ENERGY_COST_성벽보수, GOLD_COST_성벽보수));
		}

		bool isEnabled_성벽보수()
		{ 
            if (!pk::is_alive(taishu) or taishu.action_done) return false;
            else if (int(district.ap) < ACTION_COST_성벽보수) return false;
            else if (pk::get_hp(city) >= pk::get_max_hp(city)) return false;
            else if (building_energy < ENERGY_COST_성벽보수) return false;
            else if (building_gold < GOLD_COST_성벽보수) return false;
			return true;
		}
        
        bool isVisible_성벽보수()
        {
            if (pk::is_campaign()) return false;
            if (!pk::is_alive(city)) return false;
            return true;
        }

		bool handler_성벽보수()
		{
			if (force.is_player())
            {
                if (pk::choose({ pk::encode("예"), pk::encode("아니오") }, pk::encode(pk::format("성벽을 보수하시겠습니까? \n (기력{}, 금{} 사용)", ENERGY_COST_성벽보수, GOLD_COST_성벽보수)), taishu ) == 1)
                    return false;
            }
           
            if (pk::is_in_screen(building_pos))
            {
                switch(pk::rand(2))
                {
                    case 0 : pk::play_voice(0x39, taishu); break;   // 음성 : 설치
                    case 1 : pk::play_voice(0x3a, taishu); break;   // 음성 : 설치
                }
            }
			
            int hp_heal = 5 * taishu.stat[무장능력_정치];
            pk::say(pk::encode("어서 성벽을 보수하라"), taishu);
            taishu.action_done = true;
            
			pk::add_tp(force, 30, force.get_pos());
			pk::add_hp(city, hp_heal, true);
			pk::add_energy(city, -ENERGY_COST_성벽보수, true);
			pk::add_gold(city, -GOLD_COST_성벽보수, true);
            
            if (force.is_player())
            {
                district.ap -= ACTION_COST_성벽보수;
			}
            
			return true;
			
		}
        
        
        //---------------------------------------------------------------------------------------
        
        void onTurnStart(pk::force@ AI_force)
        {
            if (pk::is_campaign()) return;
            
            @force = @AI_force;
            // player 세력인 경우 skip
            if (force.is_player()) return;
            
            if (성벽보수_AI실행) 
                AI_repair_wall();
            
        }
        
        void AI_repair_wall()
        {
            // Player와 교전 중인 AI세력의 모든 도시에 대해서 보수 실행
            auto city_list = pk::list_to_array(pk::get_city_list(force));
            for (int i = 0; i < int(city_list.length); i++)
            {
                @city = city_list[i];
                @building = pk::city_to_building(city);
                @district = pk::get_district(building.get_district_id());
                @taishu = pk::get_person(pk::get_taishu_id(building));
                building_gold = pk::get_gold(building);
                building_energy = pk::get_energy(building);
                
                // 성벽보수 가능 조건 확인 
                bool repair_enable = isEnabled_성벽보수();
                
                // 주위 5칸 이내 교전 중인 Player 부대 있는지 확인 : AI끼리 교전 시에는 보수 안함!!!
                bool engage_player_unit = false;
                auto range = pk::range(building.pos, 1, 5);
                for (int j = 0; j < int(range.length); j++)
                {
                    pk::unit@ unit = pk::get_unit(range[j]);
                    if (unit !is null and unit.is_player() and pk::is_enemy(building, unit))
                        engage_player_unit = true;
                }            
                
                //성벽보수 필요 상황인지 판단 (내구도 30% 이하)
                bool repair_needed = false;
                if (pk::get_hp(city) <= (0.3f * pk::get_max_hp(city)))
                    repair_needed = true;
                
                // 성벽보수 실행
                if (repair_enable and repair_needed and engage_player_unit) 
                {
                    bool handler = handler_성벽보수();
                }
                
            }
            
        }
        

	}

	Main main;
}