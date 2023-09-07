/*
@ ������: �⸶å�� 
@ UPDATE: '19.1.27    / ��������
@ UPDATE: '19.2.13    / ���泻��: ����/������ �������� ����Ʈ ����, ����/�ϱ��� �̺�Ʈ �߰�

@ ������: HoneyBee ('19.2.15)
@ ��������: �¼��� <����>�� ��� Message �߰� �ݿ�, <����>���� ���� ȭ�� �߰�, <������>���� ���� �߰� 

@ ������: �⸶å��
@ UPDATE: '19.5.4    / ���泻��: ���� ����� ���� ����ġ, �� ���� ����

*/

namespace ���ú�������
{
	//---------------------------------------------------------------------------------------
    // ���� ����
	const int ACTION_COST_�������� = 20;        // ���������� �ʿ��� �ൿ��
	const int GOLD_COST_�������� = 300;         // ���������� �ʿ��� ��
    
    const int ����������_�߰�Ȯ�� = 20;            // ���� ���� ���ÿ��� ���� �� ���� �߰� Ȯ��
    const float Ư��ȷ�_�߰�Ȯ������ġ = 2.0f;     // Ư��_�ȷ� ������ ���ÿ� ���� �� �߰� Ȯ�� ����
    
    //---------------------------------------------------------------------------------------
    
    
	
	class Main
	{
		
		pk::building@ building;
		pk::force@ force;
		pk::city@ city;
        pk::district@ district;
		pk::person@ kunshu;
		pk::person@ taishu;
        pk::point building_pos;
        uint16 building_gold;
		int building_energy;
        int item_id_found;
        int challange_result;
        array<int> arr_stat = {70, 75, 80, 85, 90};

		Main()
		{
            // �������� �޴� (������)
			pk::menu_item ��������;
			��������.menu = 102;        // ����޴�
			��������.init = pk::building_menu_item_init_t(init);
			��������.is_visible = pk::menu_item_is_visible_t(isVisible_��������);
			��������.is_enabled = pk::menu_item_is_enabled_t(isEnabled_��������);
			��������.get_text = pk::menu_item_get_text_t(getText_��������);
			��������.get_desc = pk::menu_item_get_desc_t(getDesc_��������);
			��������.handler = pk::menu_item_handler_t(handler_��������);
			pk::add_menu_item(��������);
            
		}

        
        //---------------------------------------------------------------------------------------
        
		void init(pk::building@ building_t)
		{
			@building = @building_t;
			@force = pk::get_force(building.get_force_id());
            @city = pk::building_to_city(building);
            @kunshu = pk::get_person(pk::get_kunshu_id(building));
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
			else if (building_gold < GOLD_COST_��������)
				return pk::encode(pk::format("���� �����մϴ� (��{} �ʿ�)", GOLD_COST_��������));
			else
				return pk::encode(pk::format("���������� �����մϴ� (��{} ���)", GOLD_COST_��������));
		}

		bool isEnabled_��������()
		{ 
            if (!pk::is_alive(taishu) or taishu.action_done) return false;
            else if (int(district.ap) < ACTION_COST_��������) return false;
            else if (building_gold < GOLD_COST_��������) return false;
			return true;
		}
        
        bool isVisible_��������()
        {
            if (pk::is_campaign()) return false;
            if (!pk::is_alive(city)) return false;
            return true;
        }
        
        //---------------------------------------------------------------------------------------

		bool handler_��������()
		{
			if (force.is_player())
            {
                if (pk::choose({ pk::encode("��"), pk::encode("�ƴϿ�") }, pk::encode(pk::format("�̹߰ߵ� ������ ã�ƺ��ڽ��ϱ�? \n (��{} ���)", GOLD_COST_��������)), taishu ) == 1)
                    return false;
            }
           
            taishu.action_done = true;
            
			pk::add_tp(force, 30, force.get_pos());
			pk::add_gold(city, -GOLD_COST_��������, true);
            
            if (force.is_player())
            {
                district.ap -= ACTION_COST_��������;
			}
            
            
            // ��������
            int item_id = -1; 
            item_id = get_hidden_item_id(true); // ���³� �̹߰� �����˻�
            string kunshu_name = pk::decode(pk::get_name(kunshu));
            if (pk::is_valid_item_id(item_id))  // ���³� �̹߰� ���� ��ȿ
            {
                pk::item@ item = pk::get_item(item_id);
                pk::building@ location = pk::get_building(item.location);
                
                string item_name = pk::decode(pk::get_name(item));
                string item_location = pk::decode(pk::get_name(location));
                
                // �̹߰� ������ �ִ� ���ÿ��� ���� Ȯ���� �߰�
                if (building.get_id() == item.location and pk::rand_bool(get_chance_item_found(building)))
                {
                    // ������ ����/�ϱ��� ���� ('19.2.13)
                    item_id_found = item_id;
                    pk::scene(pk::scene_t(scene_challange));
                    
                    // ���� ȹ�� ����
                    if (challange_result == 0)
                    {
                        // ���� �߰� ó��
                        set_item_found(item);
                        pk::play_se(6);

                        // ���� �߰� �޽���
                        if (kunshu.get_id() == taishu.get_id())
                            pk::message_box(pk::encode(pk::format("��. \x1b[2x{}\x1b[0x���� \x1b[1x{}\x1b[0x��(��) �����", item_location, item_name)), taishu);
                        else
                            pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x��, \x1b[2x{}\x1b[0x���� \x1b[1x{}\x1b[0x��(��) ������ϴ�", kunshu_name, item_location, item_name)), taishu);
                    }
                    // ���� ȹ�� ����
                    else if (challange_result == 1)
                    {
                        pk::play_se(7);
						
						if (kunshu.get_id() == taishu.get_id())
                            pk::message_box(pk::encode(pk::format("\x1b[2x{}\x1b[0x���� \x1b[1x{}\x1b[0x��(��) ���� �ִ� �ڸ� ã������ ��µ� �����Ͽ���", item_location, item_name)), taishu);
                        else
							pk::message_box(pk::encode(pk::format("\x1b[2x{}\x1b[0x���� \x1b[1x{}\x1b[0x��(��) ���� �ִ� �ڸ� ã������ ��µ� �����߽��ϴ�", item_location, item_name)), taishu);
                    }
                }
                else    // �̹߰� ������ ���� ����
                {
                    pk::play_se(6);
                    
                    if (pk::rand_bool(10))       // ���� Ȯ���� ����+������ ǥ��
						if (kunshu.get_id() == taishu.get_id())
							pk::message_box(pk::encode(pk::format("\x1b[2x{}\x1b[0x���� \x1b[1x{}\x1b[0x��(��) �� �� ���ٴ� �ҹ��̷α�.", item_location, item_name)), taishu);
						else
							pk::message_box(pk::encode(pk::format("\x1b[2x{}\x1b[0x���� \x1b[1x{}\x1b[0x��(��) �� �� ���ٴ� �ҹ��̱���.", item_location, item_name)), taishu);
                    else 
                    {
                        if (pk::rand_bool(50))  // ���� Ȯ���� ���縸 ǥ��
						{
                            if (kunshu.get_id() == taishu.get_id())
								pk::message_box(pk::encode(pk::format("�ڱ� �� ��򰡿� \x1b[1x{}\x1b[0x��(��) �ִ� �� �ϱ�.", item_name)), taishu);
							else
								pk::message_box(pk::encode(pk::format("�ڱ� �� ��򰡿� \x1b[1x{}\x1b[0x��(��) �ִ� �� �մϴ�.", item_name)), taishu);
                        }
						else                         // ���� �� ���� ���翩�θ� ǥ��
                        {	
							if (kunshu.get_id() == taishu.get_id())
								pk::message_box(pk::encode("������ ������ ������ �ִ� �� ����."), taishu);
							else
								pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x�� ������ ������ ������ �ִ� �� �����ϴ�.", kunshu_name)), taishu);
						}
					}
                }
            }
            else
            {
                pk::play_se(7);
                
                item_id = get_hidden_item_id(false); // Ÿ���� �̹߰� �����˻�
                if (pk::is_valid_item_id(item_id) and pk::rand_bool(50))
				{
					if (kunshu.get_id() == taishu.get_id())
						pk::message_box(pk::encode("�̰����� ������ ���� ����. �׷��ٸ� �ٸ� ���� ã�ƺ��� ���� ������."), taishu);
					else
						pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x�� �������� ������ ���� ���ϴ�. �ٸ� ���� ã�ƺ��ô� �� ��ڽ��ϱ�?.", kunshu_name)), taishu);
                }
				else
				{
					if (kunshu.get_id() == taishu.get_id())
						pk::message_box(pk::encode("�ƹ����� �̹߰ߵ� ������ ���� �� ����."), taishu);
					else
						pk::message_box(pk::encode("�ƹ����� �̹߰ߵ� ������ ���� �� �����ϴ�."), taishu);
				}
            }
            
			return true;
			
		}
        
        //---------------------------------------------------------------------------------------
        
        // �̹߰� ���� ID ��ȯ �Լ�
        // in_force =true  : �ڼ��� �˻�
        // in_force =false : Ÿ���� �˻�
        int get_hidden_item_id(bool in_force)
        {
            int item_id = -1;
            
            for (int i = 0; i < ����_��; i++)
            {
                pk::item@ item = pk::get_item(i);
                if (pk::is_alive(item) and item.status == ��������_�̵��� and (i != ����_���� and i != ����_����))
                {
                    pk::building@ location = pk::get_building(item.location);
                    
                    if (in_force and location.get_force_id() == force.get_id())
                    {
                        item_id = i;
                        return item_id;
                    }
                    else if (!in_force and location.get_force_id() != force.get_id())
                    {
                        item_id = i;
                        return item_id;
                    }
                }
            }
            
            return item_id;
        }
        
        // ���� �߰� Ȯ��
        int get_chance_item_found(pk::building@ building_t)
        {
            int chance = ����������_�߰�Ȯ��;
            
            if (!pk::is_alive(building_t)) return 0;
            if (pk::is_valid_person_id(building_t.who_has_skill(Ư��_�ȷ�)))
                chance = pk::min(100, int(Ư��ȷ�_�߰�Ȯ������ġ * chance));
            
            return chance;
        }
        
        //---------------------------------------------------------------------------------------
        
        // ����/�ϱ���
        void scene_challange()
        {
            int mode;
            pk::item@ item = pk::get_item(item_id_found);
            if (item.type == 5) mode = 0;   // ��å: ���� ���
            else                mode = 1;   // ����: �ϱ��� ���
            
            pk::fade(0);
            pk::background(4);  //���: ����
			pk::fade(255);
            
			// ����
            if (mode == 0)
            {
                pk::person@ person = pk::get_person(����_����);
                person.base_stat[����ɷ�_����] = arr_stat[pk::rand(5)];
				
				// ȭ�� �߰�
				person.wajutsu_daikatsu = true;
				person.wajutsu_kiben = true;
				person.wajutsu_mushi = true;
				person.wajutsu_chinsei = true;
				person.wajutsu_gyakujou = true;
			
                person.update();
                
                scene_message(person, mode);
                pk::background(-1);
				challange_result = pk::debate(taishu, person, pk::is_player_controlled(taishu), false, true, true).first;
            }
            // �ϱ���
			else if (mode == 1)
            {
                pk::unit@ dummy_unit;
                pk::person@ person = pk::get_person(����_������);
                person.base_stat[����ɷ�_����] = arr_stat[pk::rand(5)];
				
				// ���� ����
				person.body[0] = 74;
				person.body[1] = 74;
				person.body[2] = 74;
				person.body[3] = 74;
				person.body[4] = 74;
				person.body[5] = 74;
				
                person.update();
                
                scene_message(person, mode);
                pk::background(-1);
				challange_result = pk::duel(dummy_unit, dummy_unit, taishu, null, null, person, null, null, pk::is_player_controlled(taishu), false, 0, true).first;
            }
        }
        
        void scene_message(pk::person@ person, int mode)
        {
            pk::item@ item = pk::get_item(item_id_found);
            string item_name = pk::decode(pk::get_name(item));
            string mode_name = (mode == 0)? "����" : "�ϱ���";
            
            pk::message_box(pk::encode("�̺���. �ڳװ� ������ ������ ���� �ִٴ��� ������ �ǳ��� �� �ְڴ°�. ���� ��ʸ� �ϰڳ�."), taishu);
            pk::message_box(pk::encode(pk::format("�� \x1b[2x{}\x1b[0x ���Դϱ�. ���� \x1b[1x{}\x1b[0x��(��) �ܷＭ �̱�� �帮�ڽ��ϴ�", item_name, mode_name)), person);
        }
        
        // ���� �߰� ó��
        void set_item_found(pk::item@ item)
        {
            if (!pk::is_valid_item_id(item.get_id())) return;
            
            item.status   = ��������_����;
            item.location = kunshu.location;
            item.owner    = kunshu.get_id();
            item.update();
        }
        
        
        //---------------------------------------------------------------------------------------
	}

	Main main;
}