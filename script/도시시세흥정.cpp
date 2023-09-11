/*
@ ������: �⸶å��
@ UPDATE: '19.1.19    / �������� : ���ΰ� �����Ͽ� �ü��� ����
@ UPDATE: '19.5.1     / ���泻�� : ����� ���� ����ġ, �� ���� ����
*/

namespace ���ýü�����
{
	//---------------------------------------------------------------------------------------
    
	const int ACTION_COST_�ü����� = 20;
    
    
    //---------------------------------------------------------------------------------------
    
    
	
	class Main
	{
		
		pk::building@ building;
		pk::force@ force;
		pk::city@ city;
        pk::district@ district;
        pk::point building_pos;
		pk::person@ taishu;
		pk::person@ actor;
		pk::person@ merchant;
        uint16 building_gold;
        uint8 currency;
        int debate_result;
        array<int> arr_stat = {65, 70, 75, 80, 85};

		Main()
		{
            // �ü����� �޴� (������)
			pk::menu_item �ü�����;
			�ü�����.menu = 100;        // ���ø޴�
			�ü�����.pos = 6;
			�ü�����.init = pk::building_menu_item_init_t(init);
			�ü�����.is_visible = pk::menu_item_is_visible_t(isVisible_�ü�����);
			�ü�����.is_enabled = pk::menu_item_is_enabled_t(isEnabled_�ü�����);
			�ü�����.get_text = pk::menu_item_get_text_t(getText_�ü�����);
			�ü�����.get_desc = pk::menu_item_get_desc_t(getDesc_�ü�����);
			�ü�����.handler = pk::menu_item_handler_t(handler_�ü�����);
			pk::add_menu_item(�ü�����);
            
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
            building_pos = building.pos;
            currency = city.rate/10;
            
            @merchant = pk::get_person(����_����);
            merchant.base_stat[����ɷ�_����] = arr_stat[pk::rand(5)];
            merchant.update();
		}

		string getText_�ü�����()
		{
			return pk::encode("�ü�����");
		}

		string getDesc_�ü�����()
		{
            if (pk::enemies_around(building))
                return pk::encode("�ֺ��� ������ �־� ������ �� �����ϴ�");
            else if (city.merchant_done) 
                return pk::encode("�̹� �ŷ��� �Ϸ��Ͽ����ϴ�");
            else if (pk::get_idle_person_list(building).count == 0)
                return pk::encode("���� ������ ������ �����ϴ�");
            else if (int(district.ap) < ACTION_COST_�ü�����)
                return pk::encode(pk::format("�ൿ���� �����մϴ� (�ൿ��{} �ʿ�)", ACTION_COST_�ü�����));
			else
				return pk::encode(pk::format("���ΰ� �ü������� �մϴ� (�ൿ��{} �Ҹ�)", ACTION_COST_�ü�����));
		}

		bool isEnabled_�ü�����()
		{ 
            if (pk::enemies_around(building)) return false;
            else if (city.merchant_done) return false;
            else if (pk::get_idle_person_list(building).count == 0) return false;
            else if (int(district.ap) < ACTION_COST_�ü�����) return false;
			return true;
		}
        
        bool isVisible_�ü�����()
        {
            if (pk::is_campaign()) return false;
            if (!pk::is_alive(city)) return false;
            return true;
        }

		bool handler_�ü�����()
		{
            // ���డ�� ���帮��Ʈ
            pk::list<pk::person@> person_list = pk::get_idle_person_list(building);
			if (person_list.count == 0) return false;
            
            bool deal = false;
            int answer = -1;
			if (pk::is_player_controlled(building))
            {
                while(!deal)
                {
                    answer = pk::choose({ pk::encode("��(�ü�����)"), pk::encode("��(�ü�����)"), pk::encode("�ƴϿ�") }, 
                                          pk::encode(pk::format("���ΰ� �ü��� �����Ͻðڽ��ϱ�? \n(����ü� ����{}=��1)", currency)),
                                          taishu );
                    
                    if (answer == 2) return false;  // ��� ����
                    
                    else if (answer == 1 and currency <= 1)
                    {
                        pk::message_box(pk::encode("�� �̻� �ü��� ���� �� �����ϴ�"), taishu);
                        deal = false;
                    }
                    else if (answer == 0 and currency >= 9)
                    {
                        pk::message_box(pk::encode("�� �̻� �ü��� �ø� �� �����ϴ�"), taishu);
                        deal = false;
                    }
                    else
                        deal = true;
                }
            }
            
            // ���๫�� �����ϱ�
            if (pk::is_player_controlled(building))
            {
               pk::list<pk::person@> person_sel = pk::person_selector(pk::encode("���� ����"), pk::encode("������ ������ �����մϴ�."), person_list, 1, 1);
               if (person_sel.count == 0) return false; // �̼��� �� ��� ����
               @actor = pk::get_person(person_sel[0].get_id());
            }
            else
            {
                person_list.sort(function(a, b)
                {
                    return (a.stat[����ɷ�_����] > b.stat[����ɷ�_����]) ; // ���� ���� (���¼�)
                });
                @actor = pk::get_person(person_list[0].get_id());
            }
            
            // ���ΰ� ����
            pk::scene(pk::scene_t(scene_�ü�����));

            // �ൿ�� ����
            if (force.is_player())
                district.ap -= ACTION_COST_�ü�����;
            
            // ���๫�� �ൿ�Ϸ� �� ���ðŷ� �Ϸ�
            city.merchant_done = true;
            actor.action_done = true;
           
            // ���� �¸��� ��� �ü� ����
            if (debate_result == 0)
            {
                if (answer == 0)
                {
                    city.rate = city.rate + 10;
                    pk::say(pk::encode("�ü��� �ø���� �����߽��ϴ�."), actor, city);
                }
                else if (answer == 1)
                {
                    city.rate = city.rate - 10;
                    pk::say(pk::encode("�ü��� ������� �����߽��ϴ�."), actor, city);
                }
            }
            else
            {
                pk::say(pk::encode("�˼��մϴ�. ������ �����߽��ϴ�."), actor, city);
            }
            
			return true;
		}
        
        
        void scene_�ü�����()
		{
			debate_result = pk::debate(actor, merchant, pk::is_player_controlled(actor), false, true, true).first;
		}
        
        

	}

	Main main;
}