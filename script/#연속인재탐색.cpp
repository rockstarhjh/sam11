/*
@ ������: �⸶å��
@ UPDATE: '19.5.3    / �������� : ����Ž�� ���ӽ��� �޴�
@ UPDATE: '19.5.8    / ���泻�� : ���� �ɼ� üũ ��� �߰� (����OFF �ÿ��� ����Ž�� ��밡��)
*/

namespace ��������Ž��
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
        int ACTION_COST_Ž��;

		Main()
		{
            
            // Ž���޴�
			pk::menu_item ����Ž��;
			����Ž��.menu = 102;    //����޴�
            ����Ž��.init = pk::building_menu_item_init_t(init);
			����Ž��.is_visible = pk::menu_item_is_visible_t(isVisible_����Ž��);
			����Ž��.is_enabled = pk::menu_item_is_enabled_t(isEnabled_����Ž��);
			����Ž��.get_text = pk::menu_item_get_text_t(getText_����Ž��);
			����Ž��.get_desc = pk::menu_item_get_desc_t(getDesc_����Ž��);
			����Ž��.handler = pk::menu_item_handler_t(handler_����Ž��);
			pk::add_menu_item(����Ž��);
            
		}

        
        //---------------------------------------------------------------------------------------
        // ���� ���� �޴�
        //---------------------------------------------------------------------------------------
        
		void init(pk::building@ building_t)
		{
            debate_opt = int(pk::option["Debate"]);
            
			@building = @building_t;
			@force = pk::get_force(building.get_force_id());
            @city = pk::building_to_city(building);
            @taishu = pk::get_person(pk::get_taishu_id(building));
            @district = pk::get_district(building.get_district_id());
            
            person_list = pk::get_idle_person_list(building);   // ���� ������ ���ൿ ���� ����Ʈ
            
            ACTION_COST_Ž�� = get_hrcmd_ap(city);
            
		}
        
        
        // ����� �˻��Ͽ� �ൿ�� ��ȯ
        int get_hrcmd_ap(pk::city@ city_t)
        {
            int hrcmd_ap = 20;
            if (pk::is_alive(city_t))
            {
                if (pk::has_facility(city, �ü�_�����))
                    return hrcmd_ap / 2;
            }
            return hrcmd_ap;
        }
        
        
        //---------------------------------------------------------------------------------------

		string getText_����Ž��()
		{
			return pk::encode("����Ž��");
		}

		string getDesc_����Ž��()
		{
            if (debate_opt < 2)
                return pk::encode("����Ž���� ����Ϸ��� ���� �ɼ���\x1b[17x'�Ⱥ���'\x1b[0x�� �����Ͻʽÿ�.");
            
            else if (person_list.count == 0)
                return pk::encode("���� ������ ������ �����ϴ�");
            else if (int(district.ap) < ACTION_COST_Ž��)
                return pk::encode(pk::format("�ൿ���� �����մϴ� (�ൿ��{} �ʿ�)", ACTION_COST_Ž��));
			else
				return pk::encode(pk::format("���ø� Ž���մϴ� (�ൿ��{})", ACTION_COST_Ž��));
		}

		bool isEnabled_����Ž��()
		{ 
            if (debate_opt < 2) return false;
            
            else if (person_list.count == 0) return false;
            else if (int(district.ap) < ACTION_COST_Ž��) return false;
			return true;
		}

        bool isVisible_����Ž��()
        {
            if (pk::is_campaign()) return false;   // Ʃ�丮���̳� �������� ��Ȱ��ȭ
            
            if (!pk::is_alive(city)) return false;
            else if (!building.is_player()) return false;   // ��ǻ�� AI ����
            else if (!pk::is_player_controlled(building)) return false;  // �÷��̾� ���ӱ���
            return true;
        }
        
		bool handler_����Ž��()
		{
            // ���� ���� �ɼ� üũ('19.5.8)
            if (debate_opt < 2) 
            {
                pk::message_box(pk::encode("����Ž���� ����Ϸ��� ���� �ɼ���\n\x1b[17x'�Ⱥ���'\x1b[0x�� �����Ͻʽÿ�."));
                return false;
            }
            
            
            // ���డ�� ���帮��Ʈ Ȯ��
			if (person_list.count == 0) return false;
            
            int max = district.ap / ACTION_COST_Ž��;
            if (max == 0) return false;
            
            // ���๫�� �����ϱ�
            pk::list<pk::person@> actors;
            string person_name;
            bool confirm = false;
            while (!confirm)
            {
                actors = pk::person_selector(pk::encode("Ž�� ���� ����"), pk::encode("Ž���� ������ �����մϴ�."), person_list, 1, pk::min(max, person_list.count), actors, 26);
                int count = int(actors.count);
                if (count == 0) return false; // �̼��� �� ��� ����
                
                person_name = pk::decode( pk::get_name(pk::get_person(actors[0].get_id())) );
                if (count > 1)
                    person_name = pk::format("{} �� {}��", person_name, count-1);
            
                confirm = pk::yes_no(pk::encode(pk::format("\x1b[1x{}\x1b[0x���� Ž���� ��Ű�ڽ��ϱ�?", person_name)));
            }
            
            
            
            // ���� Ž�� ����
            for (int i = 0; i < actors.count; i++)
            {    
                pk::person@ actor = pk::get_person(actors[i].get_id());

                // Ž�� ���
                pk::search_cmd_info cmd_search;
                @cmd_search.base  = building;
                @cmd_search.actor = actor;
                pk::command(cmd_search);
            }
            
            
			return true;
		}
        
        //---------------------------------------------------------------------------------------
        
        bool ����׸�� = true;

	}

	Main main;
}