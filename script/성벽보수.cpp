/*
@ ������: �⸶å��
@ UPDATE: '18.11.6    / ��������
@ UPDATE: '18.11.16   / ���泻��: ȿ���� ����ȭ
@ UPDATE: '18.11.22   / ���泻��: AI�� �������� ������ �˰��� �߰�, �������� �Ϻ� 1ȸ�� ����
@ UPDATE: '18.12.3    / ���泻��: ����1ȸ ���� ���� ����
@ UPDATE: '19.1.4     / ���泻��: �ൿ�� ���� �Լ� ���� (������ ����)
*/

namespace ��������
{
	//---------------------------------------------------------------------------------------
    
	const int ACTION_COST_�������� = 20;
	const int ENERGY_COST_�������� = 30;
	const int GOLD_COST_�������� = 300;
    
	const int KEY = pk::hash("����");
    
    
    const bool ��������_AI���� = true;
    
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
            // �������� �޴� (������)
			pk::menu_item ��������;
			��������.menu = 100;        // ���ø޴�
			��������.pos = 8;
			��������.shortcut = "8";
			��������.init = pk::building_menu_item_init_t(init);
			��������.is_visible = pk::menu_item_is_visible_t(isVisible_��������);
			��������.is_enabled = pk::menu_item_is_enabled_t(isEnabled_��������);
			��������.get_text = pk::menu_item_get_text_t(getText_��������);
			��������.get_desc = pk::menu_item_get_desc_t(getDesc_��������);
			��������.handler = pk::menu_item_handler_t(handler_��������);
			pk::add_menu_item(��������);
            
            // AI��
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

		string getText_��������()
		{
			return pk::encode("��������");
		}

		string getDesc_��������()
		{
            if (!pk::is_alive(taishu) or taishu.action_done)
                return pk::encode("�¼��� ���ų� �̹� �¼��� �ൿ�� �Ϸ��߽��ϴ�");
            else if (int(district.ap) < ACTION_COST_��������)
                return pk::encode(pk::format("�ൿ���� �����մϴ� (�ൿ��{} �ʿ�)", ACTION_COST_��������));
            else if (pk::get_hp(city) >= pk::get_max_hp(city))
                return pk::encode("�������� �ִ��Դϴ�");
            else if (building_energy < ENERGY_COST_��������)
				return pk::encode(pk::format("����� �����մϴ� (���{} �ʿ�)", ENERGY_COST_��������));
			else if (building_gold < GOLD_COST_��������)
				return pk::encode(pk::format("���� �����մϴ� (��{} �ʿ�)", GOLD_COST_��������));
			else
				return pk::encode(pk::format("���������� �����մϴ� (���{}, ��{} ���)", ENERGY_COST_��������, GOLD_COST_��������));
		}

		bool isEnabled_��������()
		{ 
            if (!pk::is_alive(taishu) or taishu.action_done) return false;
            else if (int(district.ap) < ACTION_COST_��������) return false;
            else if (pk::get_hp(city) >= pk::get_max_hp(city)) return false;
            else if (building_energy < ENERGY_COST_��������) return false;
            else if (building_gold < GOLD_COST_��������) return false;
			return true;
		}
        
        bool isVisible_��������()
        {
            if (pk::is_campaign()) return false;
            if (!pk::is_alive(city)) return false;
            return true;
        }

		bool handler_��������()
		{
			if (force.is_player())
            {
                if (pk::choose({ pk::encode("��"), pk::encode("�ƴϿ�") }, pk::encode(pk::format("������ �����Ͻðڽ��ϱ�? \n (���{}, ��{} ���)", ENERGY_COST_��������, GOLD_COST_��������)), taishu ) == 1)
                    return false;
            }
           
            if (pk::is_in_screen(building_pos))
            {
                switch(pk::rand(2))
                {
                    case 0 : pk::play_voice(0x39, taishu); break;   // ���� : ��ġ
                    case 1 : pk::play_voice(0x3a, taishu); break;   // ���� : ��ġ
                }
            }
			
            int hp_heal = 5 * taishu.stat[����ɷ�_��ġ];
            pk::say(pk::encode("� ������ �����϶�"), taishu);
            taishu.action_done = true;
            
			pk::add_tp(force, 30, force.get_pos());
			pk::add_hp(city, hp_heal, true);
			pk::add_energy(city, -ENERGY_COST_��������, true);
			pk::add_gold(city, -GOLD_COST_��������, true);
            
            if (force.is_player())
            {
                district.ap -= ACTION_COST_��������;
			}
            
			return true;
			
		}
        
        
        //---------------------------------------------------------------------------------------
        
        void onTurnStart(pk::force@ AI_force)
        {
            if (pk::is_campaign()) return;
            
            @force = @AI_force;
            // player ������ ��� skip
            if (force.is_player()) return;
            
            if (��������_AI����) 
                AI_repair_wall();
            
        }
        
        void AI_repair_wall()
        {
            // Player�� ���� ���� AI������ ��� ���ÿ� ���ؼ� ���� ����
            auto city_list = pk::list_to_array(pk::get_city_list(force));
            for (int i = 0; i < int(city_list.length); i++)
            {
                @city = city_list[i];
                @building = pk::city_to_building(city);
                @district = pk::get_district(building.get_district_id());
                @taishu = pk::get_person(pk::get_taishu_id(building));
                building_gold = pk::get_gold(building);
                building_energy = pk::get_energy(building);
                
                // �������� ���� ���� Ȯ�� 
                bool repair_enable = isEnabled_��������();
                
                // ���� 5ĭ �̳� ���� ���� Player �δ� �ִ��� Ȯ�� : AI���� ���� �ÿ��� ���� ����!!!
                bool engage_player_unit = false;
                auto range = pk::range(building.pos, 1, 5);
                for (int j = 0; j < int(range.length); j++)
                {
                    pk::unit@ unit = pk::get_unit(range[j]);
                    if (unit !is null and unit.is_player() and pk::is_enemy(building, unit))
                        engage_player_unit = true;
                }            
                
                //�������� �ʿ� ��Ȳ���� �Ǵ� (������ 30% ����)
                bool repair_needed = false;
                if (pk::get_hp(city) <= (0.3f * pk::get_max_hp(city)))
                    repair_needed = true;
                
                // �������� ����
                if (repair_enable and repair_needed and engage_player_unit) 
                {
                    bool handler = handler_��������();
                }
                
            }
            
        }
        

	}

	Main main;
}