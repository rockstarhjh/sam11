/*  
@������: �⸶å��
@Update: '18.12.24  / ��������: ���� ������ �溮 �ü��Ǽ�
@Update: '19.1.20   / ���泻��: ������ ȸ��

*/

namespace ���ù溮�Ǽ�
{
	
	// ================ CUSTOMIZE ================
    
    const int �溮�Ǽ��Ÿ� = 3;              // ���÷κ��� ������ �Ÿ� (�ּҰŸ�=3)
    const int ����_ACTION_COST_�溮 = 5  ;  // �溮 1���� �ൿ�� �ʿ䷮
    const int ����_TP_COST_�溮     = 30 ;  // �溮 1���� �ⱳ �ʿ䷮
		
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
        
        int GOLD_COST_�溮;
        int ACTION_COST_�溮;
        int TP_COST_�溮;

		Main()
		{

			pk::menu_item item;
			item.menu = 100;        // ���ø޴�
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
            
            if (pk::has_tech(force, �ⱳ_��������))
                facility_id = �ü�_����;
            else
                facility_id = �ü�_���;
            
            // �ü� ��� ��������
            int facility_gold = pk::get_facility(facility_id).gold_cost;
            
            // ��� (��ġ ������ ���� ����)
            build_defence_wall(false);
            GOLD_COST_�溮   = count_hex * facility_gold;
            ACTION_COST_�溮 = count_hex * ����_ACTION_COST_�溮;
            TP_COST_�溮     = count_hex * ����_TP_COST_�溮;
            
		}

		string getText()
		{
			return pk::encode("�溮�Ǽ�");
		}

		string getDesc()
		{
            if (!pk::is_alive(taishu) or taishu.action_done)
                return pk::encode("�¼��� ���ų� �̹� �¼��� �ൿ�� �Ϸ��߽��ϴ�");
            else if (count_hex <= 0)
                return pk::encode("�Ǽ� ������ ������ �����ϴ�");
            else if (int(force.tp) < TP_COST_�溮)
				return pk::encode(pk::format("�ⱳP�� �����մϴ�.(�ⱳP {})", TP_COST_�溮));
            else if (int(pk::get_district(pk::get_district_id(force, 1)).ap) < ACTION_COST_�溮) 
                return pk::encode(pk::format("�ൿ���� �����մϴ� (�ൿ�� {} �ʿ�)", ACTION_COST_�溮));
			else if (building_gold < GOLD_COST_�溮)
				return pk::encode(pk::format("���� �����մϴ� (��{} �ʿ�)", GOLD_COST_�溮));
            return pk::encode(pk::format("�ֺ��� �溮 �Ǽ� (�ⱳ{}, �ൿ��{}, ��{} �Ҹ�)", TP_COST_�溮, ACTION_COST_�溮, GOLD_COST_�溮));
		}
        
        bool isVisible()
		{ 
            if (pk::is_campaign()) return false;
            else if (building_id >= �ǹ�_���ó�) return false;
            return true;
		}
        
        
		bool isEnabled()
		{ 
            if (!pk::is_alive(taishu) or taishu.action_done) return false;
            else if (count_hex <= 0) return false;
            else if (int(force.tp) < TP_COST_�溮)  return false;
            else if (int(pk::get_district(pk::get_district_id(force, 1)).ap) < ACTION_COST_�溮) return false;
			else if (building_gold < GOLD_COST_�溮) return false;
			return true;
		}

		bool handler()
		{
            if (force.is_player())
            {
                pk::scene(pk::scene_t(scene_�溮));
                if (answer == 1) return false;
            }
            
            // ����ȿ��
            if (pk::is_in_screen(building_pos))
            {
                switch(pk::rand(2))
                {
                    case 0 : pk::play_voice(0x39, taishu); break;   // ���� : ��ġ
                    case 1 : pk::play_voice(0x3a, taishu); break;   // ���� : ��ġ
                }
            }
            // ��ȭǥ��
            string facility_name = pk::decode( pk::get_facility(facility_id).name );
            pk::say(pk::encode(pk::format("�� ������ \x1b[1x{}\x1b[0x��(��) �Ǽ��϶�", facility_name)), taishu);
            taishu.action_done = true;
           
            // �Ǽ� ���ǿ� �´� ������ ��ġ
            build_defence_wall(true);
            
            // ���� ���� �� �Һ�
            pk::add_gold(city, -GOLD_COST_�溮, true);
            
            // �ൿ�� ����
            auto district = pk::get_district(pk::get_district_id(force, 1));
            district.ap -= ACTION_COST_�溮;
            
            // �ⱳ ����
            pk::add_tp(force, -TP_COST_�溮, force.get_pos());
            
			return true;
			
		}
        
        // �Ǽ� ���ȭ�� ȣ��
        void scene_�溮()
        {
            pk::background(8);
            
            string city_name = pk::decode( pk::get_name(city) );
            string facility_name = pk::decode( pk::get_facility(facility_id).name );
            answer = pk::choose({ pk::encode("��"), pk::encode("�ƴϿ�") }, 
                                  pk::encode(pk::format("\x1b[2x{}\x1b[0x ������ \x1b[1x{} {}��\x1b[0x�� �Ǽ��մϱ�?\n(�ⱳ{}, �ൿ��{}, ��{} �Ҹ�)", city_name, facility_name, count_hex, TP_COST_�溮, ACTION_COST_�溮, GOLD_COST_�溮)),
                                  taishu );
                             
            pk::background(-1);
        }
        
        // �溮 ���� ī��Ʈ �� ��ġ ���� �Լ�
        void build_defence_wall(bool build_wall)
        {
            count_hex = 0;
            int range = pk::max(3, �溮�Ǽ��Ÿ�) + ((building_id < �ǹ�_���ó�)? 1 : 0);
            arr = pk::ring(building_pos, range);
            for (int i = 0; i < int(arr.length); i++)
            {
                pk::point pos = arr[i];
                pk::hex@ hex = pk::get_hex(pos);
                
                // 6�� ���� ����
                bool enabled_pos = true;
                for (int dir = 0; dir < ����_��; dir++)
                {
                    pk::point chk_pos = pk::get_neighbor_pos(building_pos, dir, range);
                    if (chk_pos == pos)
                        enabled_pos = false;
                }
                
                if (!hex.has_building and !hex.has_unit and pk::is_enabled_terrain(hex.terrain) and enabled_pos and !check_develop_pos(pos)
                    and building_id < �ǹ�_���ó� and (hex.terrain <= ����_���� or hex.terrain == ����_Ȳ����) )
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