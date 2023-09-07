/*  
@제작자: 기마책사
@Update: '18.12.24  / 최초적용: 도시 주위에 방벽 시설건설
@Update: '19.1.20   / 변경내용: 개발지 회피

*/

namespace 도시방벽건설
{
	
	// ================ CUSTOMIZE ================
    
    const int 방벽건설거리 = 3;              // 도시로부터 떨어진 거리 (최소거리=3)
    const int 단위_ACTION_COST_방벽 = 5  ;  // 방벽 1개당 행동력 필요량
    const int 단위_TP_COST_방벽     = 30 ;  // 방벽 1개당 기교 필요량
		
	// ===========================================
	
	class Main
	{
		
		pk::building@ building;
		pk::city@ city;
        pk::point building_pos;
        pk::person@ taishu;
        int building_gold;
        int building_id;
        int force_id;
        pk::force@ force;
        array<pk::point> arr;
        
        int count_hex;
        int facility_id;
        int answer;
        
        int GOLD_COST_방벽;
        int ACTION_COST_방벽;
        int TP_COST_방벽;

		Main()
		{

			pk::menu_item item;
			item.menu = 100;        // 도시메뉴
			item.init = pk::building_menu_item_init_t(init);
			item.is_visible = pk::menu_item_is_visible_t(isVisible);
			item.is_enabled = pk::menu_item_is_enabled_t(isEnabled);
			item.get_text = pk::menu_item_get_text_t(getText);
			item.get_desc = pk::menu_item_get_desc_t(getDesc);
			item.handler = pk::menu_item_handler_t(handler);
			pk::add_menu_item(item);
            
		}

		
        void init(pk::building@ building_t)
		{
			
			@building = @building_t;
            @city = pk::building_to_city(building);
            building_gold = pk::get_gold(building);
            building_id = building.get_id();
            building_pos = building.pos;
            
            force_id = building.get_force_id();
            @force = pk::get_force(force_id);
            
            @taishu = pk::get_person(pk::get_taishu_id(building));
            
            if (pk::has_tech(force, 기교_석조건축))
                facility_id = 시설_석벽;
            else
                facility_id = 시설_토루;
            
            // 시설 비용 가져오기
            int facility_gold = pk::get_facility(facility_id).gold_cost;
            
            // 계산 (설치 갯수에 따라 가변)
            build_defence_wall(false);
            GOLD_COST_방벽   = count_hex * facility_gold;
            ACTION_COST_방벽 = count_hex * 단위_ACTION_COST_방벽;
            TP_COST_방벽     = count_hex * 단위_TP_COST_방벽;
            
		}

		string getText()
		{
			return pk::encode("방벽건설");
		}

		string getDesc()
		{
            if (!pk::is_alive(taishu) or taishu.action_done)
                return pk::encode("태수가 없거나 이미 태수의 행동을 완료했습니다");
            else if (count_hex <= 0)
                return pk::encode("건설 가능한 지형이 없습니다");
            else if (int(force.tp) < TP_COST_방벽)
				return pk::encode(pk::format("기교P가 부족합니다.(기교P {})", TP_COST_방벽));
            else if (int(pk::get_district(pk::get_district_id(force, 1)).ap) < ACTION_COST_방벽) 
                return pk::encode(pk::format("행동력이 부족합니다 (행동력 {} 필요)", ACTION_COST_방벽));
			else if (building_gold < GOLD_COST_방벽)
				return pk::encode(pk::format("금이 부족합니다 (금{} 필요)", GOLD_COST_방벽));
            return pk::encode(pk::format("주변에 방벽 건설 (기교{}, 행동력{}, 금{} 소모)", TP_COST_방벽, ACTION_COST_방벽, GOLD_COST_방벽));
		}
        
        bool isVisible()
		{ 
            if (pk::is_campaign()) return false;
            else if (building_id >= 건물_도시끝) return false;
            return true;
		}
        
        
		bool isEnabled()
		{ 
            if (!pk::is_alive(taishu) or taishu.action_done) return false;
            else if (count_hex <= 0) return false;
            else if (int(force.tp) < TP_COST_방벽)  return false;
            else if (int(pk::get_district(pk::get_district_id(force, 1)).ap) < ACTION_COST_방벽) return false;
			else if (building_gold < GOLD_COST_방벽) return false;
			return true;
		}

		bool handler()
		{
            if (force.is_player())
            {
                pk::scene(pk::scene_t(scene_방벽));
                if (answer == 1) return false;
            }
            
            // 음성효과
            if (pk::is_in_screen(building_pos))
            {
                switch(pk::rand(2))
                {
                    case 0 : pk::play_voice(0x39, taishu); break;   // 음성 : 설치
                    case 1 : pk::play_voice(0x3a, taishu); break;   // 음성 : 설치
                }
            }
            // 대화표시
            string facility_name = pk::decode( pk::get_facility(facility_id).name );
            pk::say(pk::encode(pk::format("성 주위에 \x1b[1x{}\x1b[0x을(를) 건설하라", facility_name)), taishu);
            taishu.action_done = true;
           
            // 건설 조건에 맞는 지형에 설치
            build_defence_wall(true);
            
            // 실행 도시 금 소비
            pk::add_gold(city, -GOLD_COST_방벽, true);
            
            // 행동력 감소
            auto district = pk::get_district(pk::get_district_id(force, 1));
            district.ap -= ACTION_COST_방벽;
            
            // 기교 감소
            pk::add_tp(force, -TP_COST_방벽, force.get_pos());
            
			return true;
			
		}
        
        // 건설 배경화면 호출
        void scene_방벽()
        {
            pk::background(8);
            
            string city_name = pk::decode( pk::get_name(city) );
            string facility_name = pk::decode( pk::get_facility(facility_id).name );
            answer = pk::choose({ pk::encode("예"), pk::encode("아니오") }, 
                                  pk::encode(pk::format("\x1b[2x{}\x1b[0x 주위로 \x1b[1x{} {}개\x1b[0x를 건설합니까?\n(기교{}, 행동력{}, 금{} 소모)", city_name, facility_name, count_hex, TP_COST_방벽, ACTION_COST_방벽, GOLD_COST_방벽)),
                                  taishu );
                             
            pk::background(-1);
        }
        
        // 방벽 갯수 카운트 및 설치 실행 함수
        void build_defence_wall(bool build_wall)
        {
            count_hex = 0;
            int range = pk::max(3, 방벽건설거리) + ((building_id < 건물_도시끝)? 1 : 0);
            arr = pk::ring(building_pos, range);
            for (int i = 0; i < int(arr.length); i++)
            {
                pk::point pos = arr[i];
                pk::hex@ hex = pk::get_hex(pos);
                
                // 6개 방향 비우기
                bool enabled_pos = true;
                for (int dir = 0; dir < 방향_끝; dir++)
                {
                    pk::point chk_pos = pk::get_neighbor_pos(building_pos, dir, range);
                    if (chk_pos == pos)
                        enabled_pos = false;
                }
                
                if (!hex.has_building and !hex.has_unit and pk::is_enabled_terrain(hex.terrain) and enabled_pos and !check_develop_pos(pos)
                    and building_id < 건물_도시끝 and (hex.terrain <= 지형_습지 or hex.terrain == 지형_황무지) )
                {
                    count_hex += 1;
                    
                    if (build_wall)
                    {
                        pk::create_building(pk::get_facility(facility_id), pos, force_id);
                        pk::building@ facility = pk::get_building(pos);
                        pk::complete(facility);
                    }
                }
            }
        }
        
        bool check_develop_pos(pk::point pos_t)
        {
            for (int i = 0; i < int(city.max_devs); i++)
            {
                if (city.dev[i].pos == pos_t)
                    return true;
            }
            return false;
        }

	}
   
	Main main;
}