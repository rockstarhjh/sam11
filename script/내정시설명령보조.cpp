/*  
@������: �⸶å��
@Update: '19.11.25  / ��������: �����ü� �Ǽ��ӹ�����ǥ��, ����պ��޴�, ���ü��Ǽ��޴�, �߾ӽü��Ǽ��޴�
@Update: '20.8.8    / ��������: ���ü��Ǽ��޴� ��������, �߾ӽü��Ǽ��޴� ����(������ ����/��â ���� �˻� �߰�)
@Update: '20.8.21   / ��������: �Ǽ��ӹ� �ܿ��Ⱓ ǥ�ü��� ���� (��ġ ���� ���忡 ���� �ּ�ġ ������ �ݿ�)
@Update: '20.9.2    / ��������: �����ü����������� ��� �߰�, ����/��ǥ �ڵ����� ��� �߰�, �ִ� �Ǽ��Ⱓ 100�� ���ѿ� ���� ���弱�� ���� ����
@Update: '20.9.20   / ��������: �����ֺ��� ���δ� Ȯ��
*/

namespace �����ü���ɺ���
{
    //=======================================================================================
    
    // �����ü� ��¸޴� ���� ���� (true = on, false = off)
	const bool  �Ǽ��ӹ�����_�ٷ�ǥ��  = false;    // �����ü� �Ǽ��ӹ����� ǥ�� (true: �ٷ� ��ǳ��ǥ�� / false: �޴�Ŭ��Ȯ��)
    const bool  ������_����_�˻�����  = true;     // �󰳹��� �Ǽ���ġ �Ǵ� ����պ���� ���� �˻���� ON/OFF (true ����)
    const bool  ������_��ġ_�ڵ�����  = true;     // �Ǽ� �� ����պ� �����ġ �ټ��� ��� (true: �ڵ����� / false: ��ǥ �������� Ȯ��â)
    const bool  ������_����_�ڵ�����  = true;     // �Ǽ� �� ����պ� ���๫�� �ټ��� ��� (true: �ڵ����� / false: ���� �������� Ȯ��â)
	const bool  ���߽���_�����_����  = true;     // �����ü� ���� ����� ���� ON/OFF (true : ���ൿ ����� ����Ͽ� ���๫�� ���� / false : ���ൿ ����� ������� �ִ� 3����� ����)
    
    //---------------------------------------------------------------------------------------
    // �����ü� ������ ���� ���� ���� (true = on, false = off)
    const bool  �����ü�_�ʱ⳻��_�߰���� = false;   // ���� ���� �� �⺻ �ʱ⳻������ �߰��� ������ �߰� ����
    const bool  �����ü�_�ʱ⳻��_AI��   = false;    // true =AI�� ȿ������, false =������ AI ��� ȿ�� ����
    const float �����ü�_�ʱ⳻��_�߰����� = 0.25f;   // ���� ���� �� �⺻ �ʱ⳻���� 25%�� �߰��� ���� ������ ���� (0.0f~0.75f)
    
    const bool  �����ü�_�պ�����_�߰���� = false;   // ����պ� �� �ʱ⳻������ �߰��� ������ �߰� ����
    const bool  �����ü�_�պ�����_AI��   = false;    // true =AI�� ȿ������, false =������ AI ��� ȿ�� ����
    const float �����ü�_�պ�����_�߰����� = 0.50f;   // ���� ���� �� �⺻ �ʱ⳻���� 25%�� �߰��� ���� ������ ���� (0.0f~0.9f)
    
    const bool  �����ü�_���ϳ���_������� = false;   // �Ǽ����� �����ü��� ���� �ʱ⳻���� ��º��� ����
    const bool  �����ü�_���ϳ���_AI��   = false;    // true =AI�� ȿ������, false =������ AI ��� ȿ�� ����
    const int   �����ü�_���ϳ���_�ű԰��� = 100;     // �����Ǽ� �� ���� ������ ������
    const int   �����ü�_���ϳ���_����պ� = 100;     // ����պ� �� ���� ������ ������
    
    //=======================================================================================
    
    
	class Main
	{
		
		Main()
		{
            //---------------------------------------------------------------------------------------
            // �����ü� ������ ����
            pk::bind(160, pk::trigger160_t(onBuildingCreate));
            pk::bind(112, pk::trigger112_t(onTurnEnd));
            
            //---------------------------------------------------------------------------------------
            // �����ü� ��¸޴� �߰�
			pk::menu_item item_����պ�;
			item_����պ�.menu = 0;        // �����޴�
			item_����պ�.pos = 0;         // �޴���ġ
			item_����պ�.init = pk::building_menu_item_init_t(init_�����޴�);
            item_����պ�.get_image_id = pk::menu_item_get_image_id_t(getImageID_green);     // ��� �޴�
			item_����պ�.is_visible = pk::menu_item_is_visible_t(isVisible_����պ�);
			item_����պ�.is_enabled = pk::menu_item_is_enabled_t(isEnabled_����պ�);
			item_����պ�.get_text = pk::menu_item_get_text_t(getText_����պ�);
			item_����պ�.get_desc = pk::menu_item_get_desc_t(getDesc_����պ�);
			item_����պ�.handler = pk::menu_item_handler_t(handler_����պ�);
			pk::add_menu_item(item_����պ�);
            
            pk::menu_item item_���Ǽ�;
			item_���Ǽ�.menu = 0;        // �����޴�
			item_���Ǽ�.pos = 1;         // �޴���ġ
			item_���Ǽ�.init = pk::building_menu_item_init_t(init_�����޴�);
            item_���Ǽ�.get_image_id = pk::menu_item_get_image_id_t(getImageID_green);     // ��� �޴�
			item_���Ǽ�.is_visible = pk::menu_item_is_visible_t(isVisible_���Ǽ�);
			item_���Ǽ�.is_enabled = pk::menu_item_is_enabled_t(isEnabled_���Ǽ�);
			item_���Ǽ�.get_text = pk::menu_item_get_text_t(getText_���Ǽ�);
			item_���Ǽ�.get_desc = pk::menu_item_get_desc_t(getDesc_���Ǽ�);
			item_���Ǽ�.handler = pk::menu_item_handler_t(handler_���Ǽ�);
			pk::add_menu_item(item_���Ǽ�);
            
            pk::menu_item item_�߾ӰǼ�;
			item_�߾ӰǼ�.menu = 0;        // �����޴�
			item_�߾ӰǼ�.pos = 2;         // �޴���ġ
			item_�߾ӰǼ�.init = pk::building_menu_item_init_t(init_�����޴�);
            item_�߾ӰǼ�.get_image_id = pk::menu_item_get_image_id_t(getImageID_green);     // ��� �޴�
			item_�߾ӰǼ�.is_visible = pk::menu_item_is_visible_t(isVisible_�߾ӰǼ�);
			item_�߾ӰǼ�.is_enabled = pk::menu_item_is_enabled_t(isEnabled_�߾ӰǼ�);
			item_�߾ӰǼ�.get_text = pk::menu_item_get_text_t(getText_�߾ӰǼ�);
			item_�߾ӰǼ�.get_desc = pk::menu_item_get_desc_t(getDesc_�߾ӰǼ�);
			item_�߾ӰǼ�.handler = pk::menu_item_handler_t(handler_�߾ӰǼ�);
			pk::add_menu_item(item_�߾ӰǼ�);
            
            pk::menu_item item_�ӹ�����;
			item_�ӹ�����.menu = 0;        // �����޴�
			item_�ӹ�����.pos = 2;         // �޴���ġ
			item_�ӹ�����.init = pk::building_menu_item_init_t(init_�����޴�);
            item_�ӹ�����.get_image_id = pk::menu_item_get_image_id_t(getImageID_orange);     // ��Ȳ�� �޴�
			item_�ӹ�����.is_visible = pk::menu_item_is_visible_t(isVisible_�ӹ�����);
			item_�ӹ�����.is_enabled = pk::menu_item_is_enabled_t(isEnabled_�ӹ�����);
			item_�ӹ�����.get_text = pk::menu_item_get_text_t(getText_�ӹ�����);
			item_�ӹ�����.get_desc = pk::menu_item_get_desc_t(getDesc_�ӹ�����);
			item_�ӹ�����.handler = pk::menu_item_handler_t(handler_�ӹ�����);
			pk::add_menu_item(item_�ӹ�����);
            
		}

        //---------------------------------------------------------------------------------------
        // ���� ����
		pk::building@ building;
		pk::building@ base;
        pk::city@ city;
        string city_name;
        pk::list<pk::person@> list_base_person;
        pk::list<pk::person@> list_idle_person;
        pk::list<pk::building@> target_merge_list;
        pk::array<pk::point> target_dev_pos;
        pk::person@ kunshu;
        pk::person@ taishu;
        pk::district@ district;
        pk::force@ force;
        
        bool ai_force_ctrl;
        bool district_ctrl; 
        bool merge_disable; 
        bool center_facility_nearby; 
        bool building_hp_full;
        bool enemies_around;
        int city_gold;
        int facility_id;
        int upgrade_id;
        int upgrade_cost;
        int develop_id;
        int develop_cost;
        int center_id;
        int center_cost;
        
        int ACTION_COST_����պ� = 10;
        int ACTION_COST_�������� = 20;
        //---------------------------------------------------------------------------------------
        
        int getImageID_blue()    // �Ķ���
		{ return 856; }
        int getImageID_green()    // ���
		{ return 889; }
        int getImageID_orange()   // ��Ȳ��
		{ return 1249; }
        
        //---------------------------------------------------------------------------------------
		
        void init_�����޴�(pk::building@ building_t)
		{
			@building = @building_t;
            @city = pk::get_city(pk::get_city_id(building.pos));
            @base = pk::city_to_building(city);
            city_name = pk::decode(pk::get_name(city));
            city_gold = pk::get_gold(base);
            list_base_person = pk::get_person_list(base, pk::mibun_flags(�ź�_����, �ź�_����, �ź�_�¼�, �ź�_�Ϲ�));
            list_idle_person = pk::get_idle_person_list(base);
            
            @kunshu = pk::get_person(pk::get_kunshu_id(base));
            @taishu = pk::get_person(pk::get_taishu_id(base));
            @district = pk::get_district(base.get_district_id());
            @force = pk::get_force(building.get_force_id());
            
            facility_id = building.facility;
            building_hp_full = (building.hp >= pk::get_facility(facility_id).hp)? true : false;
            
            get_upgrade_gold_cost();
            get_merge_target_merge_list();
            get_develop_gold_cost();
            get_center_gold_cost();
            get_dev_pos_nearby();
            check_center_nearby();

            ai_force_ctrl  = (int(pk::option["San11Option.FreeOperate"]) == 1)? true : false;
            district_ctrl  = bool(pk::core["���ӱ�������"]);
            merge_disable  = bool(pk::core["����պ�����"]);
            enemies_around = pk::enemies_around(base);
            
            if (�Ǽ��ӹ�����_�ٷ�ǥ��) report_construct(); // �Ǽ� ���� ���� ǥ��
		}

        //---------------------------------------------------------------------------------------
        //  �����ü�_������ ���� (�Ǽ�����)
        //---------------------------------------------------------------------------------------
        
        void onBuildingCreate(pk::building@ building, int type)
        {
            if (pk::is_campaign()) return;
            
            int facility_id = building.facility;
            if (facility_id < �ü�_���۴� or facility_id > �ü�_������3��) return; // �����ü� �ƴϸ� ����
            if (building.completed) return; // �ϼ��� �ü��̸� ����
            
            pk::facility@ facility = pk::get_facility(facility_id);
            uint16 hp_before = building.hp;
            uint16 hp_after  = building.hp;
            
            // �����ü�_�ʱ⳻��_�߰����
            if (�����ü�_�ʱ⳻��_�߰���� and !(�����ü�_�ʱ⳻��_AI�� and building.is_player())) 
            {
                if (�ü�_���۴� <= facility_id and facility_id <= �ü�_���г�)    // 1�� �ü��� ���
                {
                    float hp_add_ratio = pk::min(pk::max(0.f, �����ü�_�ʱ⳻��_�߰�����), 0.75f);  // �Է¹������� : 0%~75%
                    uint16 hp_add_value = uint16(float(facility.hp) * hp_add_ratio);
                    hp_after = hp_before + hp_add_value;
                    building.hp = hp_after;
                }                    
            }
            
            // �����ü�_����պ�����_�߰����
            if (�����ü�_�պ�����_�߰���� and !(�����ü�_�պ�����_AI�� and building.is_player())) 
            {
                int downgrade_id = get_downgrade_id(facility_id);
                if (downgrade_id != -1)    // 2��, 3�� �ü��� ���
                {
                    float hp_add_ratio = pk::min(pk::max(0.f, �����ü�_�պ�����_�߰�����), 0.9f);  // �Է¹������� : 0%~90%
                    uint16 hp_delta = facility.hp - pk::get_facility(downgrade_id).hp;
                    uint16 hp_add_value = uint16(float(hp_delta) * hp_add_ratio);
                    hp_after = hp_before + hp_add_value;
                    building.hp = hp_after;
                }                    
            }
            
            
            if (����׸�� and (hp_before < hp_after))
            {
                string facility_name = pk::decode(pk::get_name(facility));
                pk::point pos = building.pos;
                pk::info(pk::format("{}({},{}) �������߰� {} �� {}", facility_name, pos.x, pos.y, hp_before, hp_after));
            }

        }
        
        //---------------------------------------------------------------------------------------
        //  �����ü�_������ ���� (����)
        //---------------------------------------------------------------------------------------
        
        void onTurnEnd(pk::force@ force)
		{
            if (pk::is_campaign()) return;
            if (!�����ü�_���ϳ���_�������) return;
            
            //pk::force@ force = pk::get_force(pk::get_current_turn_force_id());
            if (!pk::is_normal_force(force)) return;
            if (�����ü�_���ϳ���_AI�� and force.is_player()) return;
            
            uint16 hp_add_develop = pk::max(0, �����ü�_���ϳ���_�ű԰���);
            uint16 hp_add_merge   = pk::max(0, �����ü�_���ϳ���_����պ�);
            
            array<pk::city@> arr_city_list = pk::list_to_array(pk::get_city_list(force));
            for (int i = 0; i < int(arr_city_list.length); i++)
            {
                pk::city@ city = arr_city_list[i];
                for (int j = 0; j < city.max_devs; j++)
                {
                    int facility_id = -1;
                    pk::building@ building = city.dev[j].building;
                    if (pk::is_alive(building) and !building.completed)
                    {
                        facility_id = building.facility;
                        pk::facility@ facility = pk::get_facility(facility_id);
                        uint16 hp_add_turn = 0;
                        
                        if (get_downgrade_id(facility_id) != -1)    // 2��, 3�� �ü��� ���
                            hp_add_turn = hp_add_merge;
                        else
                            hp_add_turn = hp_add_develop;
                        
                        pk::add_hp(building, pk::min(hp_add_turn, (facility.hp - building.hp - 1)), true);
                    }
                }
            }
            
        }
        
        //---------------------------------------------------------------------------------------
        //---------------------------------------------------------------------------------------
        
        // ����պ� ���� �ü��� �����ܰ� �ü�ID ��ȯ
        int get_downgrade_id(int facility_id)
        {
            int downgrade_id = -1;
            switch (facility_id)
            {
                case �ü�_����2��  :  downgrade_id = �ü�_����; break;
                case �ü�_����3��  :  downgrade_id = �ü�_����2��; break;
                case �ü�_����2��  :  downgrade_id = �ü�_����; break;
                case �ü�_����3��  :  downgrade_id = �ü�_����2��; break;
                
                case �ü�_����2��  :  downgrade_id = �ü�_����; break;
                case �ü�_����3��  :  downgrade_id = �ü�_����2��; break;
                case �ü�_���尣2�� :  downgrade_id = �ü�_���尣; break;
                case �ü�_���尣3�� :  downgrade_id = �ü�_���尣2��; break;
                case �ü�_������2�� :  downgrade_id = �ü�_������; break;
                case �ü�_������3�� :  downgrade_id = �ü�_������2��; break;
            }
            
            return downgrade_id;
        }
        
        
        bool check_facility_upgrade(int facility_id)
        {
            if (facility_id == �ü�_����  or facility_id == �ü�_����2�� or 
                facility_id == �ü�_����  or facility_id == �ü�_����2�� or
                facility_id == �ü�_����  or facility_id == �ü�_����2�� or
                facility_id == �ü�_���尣 or facility_id == �ü�_���尣2�� or
                facility_id == �ü�_������ or facility_id == �ü�_������2�� )
                return true;
            
            return false;
        }
        
        // ����պ� ���
        void get_upgrade_gold_cost()
        {
            upgrade_id = -1;
            switch (facility_id)
            {
                case �ü�_����   :  upgrade_id = �ü�_����2��; break;
                case �ü�_����2�� :  upgrade_id = �ü�_����3��; break;
                case �ü�_����   :  upgrade_id = �ü�_����2��; break;
                case �ü�_����2�� :  upgrade_id = �ü�_����3��; break;
                
                case �ü�_����    :  upgrade_id = �ü�_����2��; break;
                case �ü�_����2��  :  upgrade_id = �ü�_����3��; break;
                case �ü�_���尣   :  upgrade_id = �ü�_���尣2��; break;
                case �ü�_���尣2�� :  upgrade_id = �ü�_���尣3��; break;
                case �ü�_������   :  upgrade_id = �ü�_������2��; break;
                case �ü�_������2�� :  upgrade_id = �ü�_������3��; break;
            }
            
            if (upgrade_id >= 0) upgrade_cost = int(pk::get_facility(upgrade_id).gold_cost);
            else upgrade_cost = -1;
        }
        
        // �ֺ��� ����պ� ��� �˻�
        void get_merge_target_merge_list()
        {
            target_merge_list.clear();
            
            if (!check_facility_upgrade(facility_id)) return;
            
            for (int i = 0; i < ����_��; i++)
            {
                pk::point neighbor_pos = pk::get_neighbor_pos(building.pos, i);
                if (pk::is_valid_pos(neighbor_pos))
                {
                    pk::building@ target_building = pk::get_building(neighbor_pos);
                    if (pk::is_alive(target_building) and target_building.completed)
                    {
                        if      ((facility_id == �ü�_����  or facility_id == �ü�_����2��)  and target_building.facility == �ü�_����)    target_merge_list.add(target_building);
                        else if ((facility_id == �ü�_����  or facility_id == �ü�_����2��)  and target_building.facility == �ü�_����)    target_merge_list.add(target_building);
                        else if ((facility_id == �ü�_����  or facility_id == �ü�_����2��)  and target_building.facility == �ü�_����)    target_merge_list.add(target_building);
                        else if ((facility_id == �ü�_���尣 or facility_id == �ü�_���尣2��) and target_building.facility == �ü�_���尣)  target_merge_list.add(target_building);
                        else if ((facility_id == �ü�_������ or facility_id == �ü�_������2��) and target_building.facility == �ü�_������)  target_merge_list.add(target_building);
                    }
                }
            }       
        }
        
        // ���Ǽ� ���
        void get_develop_gold_cost()
        {
            develop_id = -1;
            switch (facility_id)
            {
                case �ü�_�Ͻ���   :  develop_id = �ü�_�Ͻ���; break;
                
                case �ü�_����   :  develop_id = �ü�_����; break;
                case �ü�_����2�� :  develop_id = �ü�_����; break;
                case �ü�_����3�� :  develop_id = �ü�_����; break;
                case �ü�_����   :  develop_id = �ü�_����; break;
                case �ü�_����   :  develop_id = �ü�_����; break;
                case �ü�_����2�� :  develop_id = �ü�_����; break;
                case �ü�_����3�� :  develop_id = �ü�_����; break;
                case �ü�_��â   :  develop_id = �ü�_����; break;
                
                case �ü�_����    :  develop_id = �ü�_����; break;
                case �ü�_����2��  :  develop_id = �ü�_����; break;
                case �ü�_���尣   :  develop_id = �ü�_���尣; break;
                case �ü�_���尣2�� :  develop_id = �ü�_���尣; break;
                case �ü�_������   :  develop_id = �ü�_������; break;
                case �ü�_������2�� :  develop_id = �ü�_������; break;
            }
            
            if (develop_id >= 0) develop_cost = int(pk::get_facility(develop_id).gold_cost);
            else develop_cost = -1;
        }
        
        
        // �߾ӰǼ� ���
        void get_center_gold_cost()
        {
            center_id = -1;
            switch (facility_id)
            {
                case �ü�_����   :  center_id = �ü�_����; break;
                case �ü�_����2�� :  center_id = �ü�_����; break;
                case �ü�_����3�� :  center_id = �ü�_����; break;
                case �ü�_����   :  center_id = �ü�_��â; break;
                case �ü�_����2�� :  center_id = �ü�_��â; break;
                case �ü�_����3�� :  center_id = �ü�_��â; break;
            }
            
            if (center_id >= 0) center_cost = int(pk::get_facility(center_id).gold_cost);
            else center_cost = -1;
        }
        
        // �ֺ��� ����/��â�� �ִ��� Ȯ��
        void check_center_nearby()
        {
            center_facility_nearby = false;
            for (int i = 0; i < ����_��; i++)
            {
                pk::point neighbor_pos = pk::get_neighbor_pos(building.pos, i);
                if (pk::is_valid_pos(neighbor_pos))
                {
                    pk::building@ building_t = pk::get_building(neighbor_pos);
                    if (pk::is_alive(building_t) and building_t.completed)
                    {
                        if      ((facility_id == �ü�_���� or facility_id == �ü�_����2�� or facility_id == �ü�_����3��) and building_t.facility == �ü�_����)  center_facility_nearby = true;
                        else if ((facility_id == �ü�_���� or facility_id == �ü�_����2�� or facility_id == �ü�_����3��) and building_t.facility == �ü�_��â)  center_facility_nearby = true;
                    }
                }
            }            
        }
        
        // �ֺ��� �� �Ǽ��� Ȯ��
        void get_dev_pos_nearby()
        {
            pk::array<pk::point> empty_pos;
            for (int i = 0; i < ����_��; i++)
            {
                pk::point neighbor_pos = pk::get_neighbor_pos(building.pos, i);
                if (pk::is_valid_pos(neighbor_pos))
                {
                    pk::hex@ hex = pk::get_hex(neighbor_pos);
                    if (!hex.has_building and !hex.has_unit)
                    {
                        for (int j = 0; j < int(city.max_devs); j++)
                        {
                            if (city.dev[j].pos == neighbor_pos)
                                empty_pos.insertLast(neighbor_pos);
                        }
                    }
                }
            }
            target_dev_pos = empty_pos;
            
        }
        
        
        //---------------------------------------------------------------------------------------
        
        // ������ ��ġ �켱���� ����
        void sort_dev_pos(int city_dev_id)
        {
            // �Ǽ� ���� ������ ���� Ȯ��
            if (int(target_dev_pos.length) < 2) return;
            
            if (city_dev_id == develop_id)  // ���ü�
            {
                target_dev_pos.sort(function(a, b)
                {
                    int count_pos_a = main.count_dev_pos(a);
                    int count_pos_b = main.count_dev_pos(b);
                    
                    // �ֺ��� ���ϰ迭�� �ü��� �ִ� �Ǽ����� �켱 ������� ���� (����պ��ϱ� ������ ��ġ)
                    // �ֺ��� ���ϰ迭�� �ü��� �ټ��� ���� ���� (����/��â �Ǽ����� ���ɼ�)
                    if ( count_pos_a == 1 and count_pos_b == 0 ) return true;
                    if ( count_pos_a == 0 and count_pos_b == 1 ) return false;
                    // �ֺ��� ������ �ƴ� ��ǥ�� ���� �Ǽ����� �켱 ������� ���� (�ܰ� ��ġ�� ���ɼ�)
                    return main.count_norm_pos(a) > main.count_norm_pos(b);
                } );
            }
            else if (city_dev_id == center_id)  // ����, ��â
            {
                target_dev_pos.sort(function(a, b)
                {
                    int count_pos_a = main.count_center_pos(a);
                    int count_pos_b = main.count_center_pos(b);
                    
                    // �ֺ��� ���ü��� ���� �Ǽ����� �켱 ������� ���� (����պ��ϱ� ������ ��ġ)
                    if ( count_pos_a > count_pos_b ) return true;
                    if ( count_pos_a < count_pos_b ) return false;
                    // �ֺ��� ������ �ƴ� ��ǥ�� ���� �Ǽ����� �켱 ������� ���� (���� ��ġ�� ���ɼ�)
                    return main.count_norm_pos(a) < main.count_norm_pos(b);
                } );
            }
        }
        
        // ����պ� �ü� �켱���� ����
        void sort_merge_list()
        {
            // ����պ� ��� ���� Ȯ��
            if (int(target_merge_list.count) < 2) return;

            target_merge_list.sort(function(a, b)
            {
                // �ֺ��� ������ �ƴ� ��ǥ�� ���� �Ǽ����� �켱 ������� ���� (���� ��ġ�� ���ɼ�)
                return main.count_norm_pos(a.pos) < main.count_norm_pos(b.pos);
            } );
            
        }
        
        // �ֺ��� ������ �ƴ� ��ǥ�� ���
        int count_norm_pos(pk::point pos_t)
        {
            int count_pos = 0;
            for (int i = 0; i < ����_��; i++)
            {
                bool check_dev_pos = false;
                pk::point neighbor_pos = pk::get_neighbor_pos(pos_t, i);
                if (pk::is_valid_pos(neighbor_pos))
                {
                    int j = 0;
                    while (!check_dev_pos and (j < int(city.max_devs)))
                    {
                        if (city.dev[j].pos == neighbor_pos) check_dev_pos = true;
                        j++;
                    }
                }
                if (!check_dev_pos) count_pos++;
            }
            return count_pos;
        }
        
        // �ֺ��� upgrade ���� ���ϰ迭 �ü��� ���
        int count_dev_pos(pk::point pos_t)
        {
            int count_pos = 0;
            for (int i = 0; i < ����_��; i++)
            {
                pk::point neighbor_pos = pk::get_neighbor_pos(pos_t, i);
                if (pk::is_valid_pos(neighbor_pos))
                {
                    pk::building@ building_t = pk::get_building(neighbor_pos);
                    if (pk::is_alive(building_t) and building_t.pos != building.pos)
                    {
                        int f_id_t = building_t.facility;
                        if      ((f_id_t == �ü�_����  or f_id_t == �ü�_����2��)   and develop_id == �ü�_����) count_pos++;    
                        else if ((f_id_t == �ü�_����  or f_id_t == �ü�_����2��)   and develop_id == �ü�_����) count_pos++;    
                        else if ((f_id_t == �ü�_����  or f_id_t == �ü�_����2��)   and develop_id == �ü�_����) count_pos++;    
                        else if ((f_id_t == �ü�_���尣 or f_id_t == �ü�_���尣2��) and develop_id == �ü�_���尣) count_pos++; 
                        else if ((f_id_t == �ü�_������ or f_id_t == �ü�_������2��) and develop_id == �ü�_������) count_pos++; 
                    }
                }
            }
            return count_pos;
        }
        
        // �ֺ��� ���� ������ �ü��� ���
        int count_center_pos(pk::point pos_t)
        {
            int count_pos = 0;
            for (int i = 0; i < ����_��; i++)
            {
                pk::point neighbor_pos = pk::get_neighbor_pos(pos_t, i);
                if (pk::is_valid_pos(neighbor_pos))
                {
                    pk::building@ building_t = pk::get_building(neighbor_pos);
                    if (pk::is_alive(building_t))
                    {
                        int f_id_t = building_t.facility;
                        if      ((f_id_t == �ü�_���� or f_id_t == �ü�_����2��  or f_id_t == �ü�_����3��) and center_id == �ü�_����) count_pos++;    
                        else if ((f_id_t == �ü�_���� or f_id_t == �ü�_����2��  or f_id_t == �ü�_����3��) and center_id == �ü�_��â) count_pos++;    
                    }
                }
            }
            return count_pos;
        }
        
        
        //---------------------------------------------------------------------------------------
        //---------------------------------------------------------------------------------------
        pk::point target_pos_t;
        
        void goto_facility()
        {
            pk::point pos = target_pos_t;
            for (int i = 0; i < 4; i++)
            {
                pk::point pos_t;
                pos_t.x = pos.x + 1;
                pos_t.y = pos.y;
                if (pk::is_valid_pos(pos_t))
                    pos.x = pos.x + 1;
            }
            
            if (!pk::is_in_screen(pos))
                pk::move_screen(pos, 1);
            
            pk::highlight(target_pos_t, true);  
        }
        void remove_highlights()
        {
            pk::remove_all_highlights();
        }
        
        
        //---------------------------------------------------------------------------------------
        // �ش� �ü����� �Ǽ� ���� ���� �ӹ�����
        //---------------------------------------------------------------------------------------
        void report_construct()
        {
            if (building.completed) return;     // �Ǽ��Ϸ� �ǹ��� ǥ�� ����
            if (list_base_person.count == 0) return;    // �Ҽ� ������ �Ҽ� ���� ���� ��� ����
            if (building.facility < �ü�_���۴� or building.facility > �ü�_������3��) return;
            
            pk::facility@ facility = pk::get_facility(building.facility);
            
            string actor_name;
            pk::person@ actor;
            int order = -1;
            float stat_sum = 0.0f;
            pk::array<pk::person@> arr_actors;
            pk::array<pk::person@> arr_base_person = pk::list_to_array(list_base_person);
            for (int i = 0; i < int(arr_base_person.length); i++)
            {
                pk::person@ person_t = arr_base_person[i];
                if (person_t.target[0] == building.get_id())
                {
                    order = person_t.order;
                    if (order == �����ӹ�_����պ�)    // ����պ�
                    {
                        @actor = person_t;
                        actor_name = pk::decode(pk::get_name(actor));
                        stat_sum = float(person_t.stat[����ɷ�_��ġ]) * (4.0f/3.0f + 0.1f);
                    }
                    else if (order == �����ӹ�_����)   // �Ϲݰ���
                    {
                        arr_actors.insertLast(person_t);
                        @actor = pk::get_person(person_t.target[1]);
                        
                        if (person_t.get_id() == actor.get_id())
                            stat_sum += float(person_t.stat[����ɷ�_��ġ]) * 1.5f;
                        else 
                            stat_sum += float(person_t.stat[����ɷ�_��ġ]) * 0.5f;
                        
                        if (actor_name == "") actor_name = pk::decode(pk::get_name(person_t));
                        else actor_name += "," + pk::decode(pk::get_name(person_t));
                        
                        stat_sum = pk::max(stat_sum, float(int(facility.hp * 0.75f / 9.f)));    // ���� ���� �ݿ��� �ִ�Ǽ��Ⱓ ���Ѱ�
                    }
                }
            }
            
            // �ӹ���� �ü��� �ܿ� �Ǽ������� Ȯ��
            uint16 hp_delta = uint16(facility.hp - building.hp);
            int remain_turn = int(calc_remain_turn(hp_delta, order, stat_sum));
            
            // �ӹ�����
            if (pk::is_alive(actor))
            {   
                // ����
                if (kunshu.get_id() == actor.get_id()) pk::play_voice(0x3E, actor);
                else                                   pk::play_voice(0x3C, actor);
            
                // ��ǳ��
                int remain_period = 10 + 10 * remain_turn;
                string msg_actor = (kunshu.get_id() == actor.get_id())? "(��)�� ���� ���̱�" : "(��)�� ���� ���Դϴ�";
                pk::say(pk::encode(pk::format("\x1b[1x{}\x1b[0x{}\n�ܿ� �ӹ��Ⱓ \x1b[1x{}��\x1b[0x", actor_name, msg_actor, remain_period)), actor, building);
            }
            
            return;
        }
        
        // �ܿ� �Ǽ��Ⱓ ���
        float calc_remain_turn(uint16 hp_delta, int order, float stat_sum)
        {
            // �����ü�_������_���Ϻ��� ��� ��� ��
            uint16 hp_add_turn = 0;
            if (�����ü�_���ϳ���_������� and !(�����ü�_���ϳ���_AI�� and building.is_player()))
            {
                if   (order == �����ӹ�_����պ�) hp_add_turn = uint16(pk::max(0, �����ü�_���ϳ���_����պ�));
                else if (order == �����ӹ�_����) hp_add_turn = uint16(pk::max(0, �����ü�_���ϳ���_�ű԰���));
                
                stat_sum += float(hp_add_turn); // ������ ������ �߰�
            }
            
            // �ܿ� �ӹ��Ⱓ ���
            float remain_turn = float(hp_delta) / stat_sum;
            
            return remain_turn;
        }
                
        
        //---------------------------------------------------------------------------------------
        //     �Ǽ��ӹ����� ǥ�� �޴�
        //---------------------------------------------------------------------------------------
        
		string getText_�ӹ�����()
		{
			return pk::encode("�ӹ�Ȯ��");
		}

        bool isVisible_�ӹ�����()
		{ 
            if (pk::is_campaign()) return false;
            else if (building.get_id() < �ǹ�_������ or building.completed) return false;
            else if (!ai_force_ctrl and !building.is_player()) return false;   // ��ǻ�� AI ����
            else if (!district_ctrl and district.no > 1) return false;
            else if (building.facility < �ü�_���۴� or building.facility > �ü�_������3��) return false;
            else if (�Ǽ��ӹ�����_�ٷ�ǥ��) return false;
            return true;
		}
        
		bool isEnabled_�ӹ�����()
		{ 
            if (pk::is_campaign()) return false;
            else if (building.get_id() < �ǹ�_������ or building.completed) return false;
            else if (building.facility < �ü�_���۴� or building.facility > �ü�_������3��) return false;
			return true;
		}
        
		string getDesc_�ӹ�����()
		{
            if (building.get_id() < �ǹ�_������ or building.completed)
                return pk::encode("���� ���� �����ü��� �ƴմϴ�");
            else if (building.facility < �ü�_���۴� or building.facility > �ü�_������3��) 
                return pk::encode("�����ü��� �ƴմϴ�");
            return pk::encode("�����ü��� ���� ���� ������� �ӹ��� ǥ���մϴ�");
        }
        
		bool handler_�ӹ�����()
		{
            report_construct();
            return true;
        }
        

        //---------------------------------------------------------------------------------------
        //     ����պ� �޴�
        //---------------------------------------------------------------------------------------
        
		string getText_����պ�()
		{
			return pk::encode("����պ�");
		}

        bool isVisible_����պ�()
		{ 
            if (pk::is_campaign()) return false;
            else if (building.get_id() < �ǹ�_������ or upgrade_id < 0) return false;
            else if (!ai_force_ctrl and !building.is_player()) return false;   // ��ǻ�� AI ����
            else if (!district_ctrl and district.no > 1) return false;
            return true;
		}
        
		bool isEnabled_����պ�()
		{ 
            if (pk::is_campaign()) return false;
            else if (building.get_id() < �ǹ�_������ or upgrade_id < 0) return false;
            else if (merge_disable) return false;
            else if (!building.completed) return false;
            else if (target_merge_list.count == 0) return false;
            else if (list_idle_person.count < 1) return false;
            else if (int(district.ap) < ACTION_COST_����պ�)  return false;
			else if (city_gold < upgrade_cost or upgrade_cost < 0) return false;
            else if (!building_hp_full) return false;
            else if (enemies_around) return false;
			return true;
		}
        
		string getDesc_����պ�()
		{
            if (building.get_id() < �ǹ�_������ or upgrade_id < 0)
                return pk::encode("����պ� ���� ������ �ü��� �ƴմϴ�.");
            else if (merge_disable) 
                return pk::encode("����պ��� �����Ǿ����ϴ�. ���Ӽ����� Ȯ���ϼ���");
            else if (!building.completed)
                return pk::encode("���� ���� ���� �ü��Դϴ�");
            else if (target_merge_list.count == 0)
                return pk::encode("����պ� ������ ��ᰡ �ֺ��� �����ϴ�");
            else if (list_idle_person.count < 1)
                return pk::encode("���� ������ ������ �����ϴ�.");
            else if (int(district.ap) < ACTION_COST_����պ�) 
                return pk::encode(pk::format("�ൿ���� �����մϴ� (�ൿ�� {} �ʿ�)", ACTION_COST_����պ�));
			else if (city_gold < upgrade_cost or upgrade_cost < 0)
				return pk::encode(pk::format("���� �����մϴ� (��{} �ʿ�)", upgrade_cost));
            else if (!building_hp_full)
                return pk::encode("�������� �����մϴ�");
            else if (enemies_around)
                return pk::encode("�ֺ��� ���δ밡 �ֽ��ϴ�");
            return pk::encode(pk::format("�ü��� ����պ� �մϴ� (�ൿ��{}, ��{} �Ҹ�)", ACTION_COST_����պ�, upgrade_cost));
        }
        

		bool handler_����պ�()
		{
            if (list_idle_person.count == 0) return true;
            if (target_merge_list.count == 0) return true;
            
            if (������_����_�˻�����) sort_merge_list();
            
            // ����պ� ��� ���Ǽ���
            pk::array<pk::building@> arr_target = pk::list_to_array(target_merge_list);
            pk::building@ target = arr_target[0];
            
            // ����պ��� ���� ������ ���� ���
            pk::facility@ facility_default = pk::get_facility(facility_id);
            pk::facility@ facility_upgrade = pk::get_facility(upgrade_id);
            uint16 hp_delta = uint16(facility_upgrade.hp - facility_default.hp);
            
            // �����ü�_����պ�����_�߰���� ��� �� : �ܿ� ������ ���� ���
            if (�����ü�_�պ�����_�߰���� and !(�����ü�_�պ�����_AI�� and building.is_player())) 
            {
                if (upgrade_id != -1)    // 2��, 3�� �ü��� ���
                {
                    float hp_add_ratio = pk::min(pk::max(0.f, �����ü�_�պ�����_�߰�����), 0.9f);  // �Է¹������� : 0%~90%
                    hp_delta -= uint16(float(hp_delta) * hp_add_ratio);
                }                    
            }
            
            // ��ġ���� ���� ������ ����
            list_idle_person.sort(function(a, b)
            {
                return a.stat[����ɷ�_��ġ] > b.stat[����ɷ�_��ġ];
            } );
            
            // ���� �۾��ϼ� �� �ּҴɷ�ġ ���
            pk::array<pk::person@> arr_idle_person = pk::list_to_array(list_idle_person);
            float stat_weight = (4.0f/3.0f + 0.1f);
            float max_stat = float(arr_idle_person[0].stat[����ɷ�_��ġ]) * stat_weight;  
            
            if (�����ü�_���ϳ���_������� and !(�����ü�_���ϳ���_AI�� and building.is_player()))
                max_stat += float(pk::max(0, �����ü�_���ϳ���_����պ�));  // ���� ������ ������ �߰�
            
            int   ref_per = int(float(hp_delta) / max_stat) + (((float(hp_delta) % max_stat) > 0)? 1 : 0); // �Ǽ��Ⱓ ���� (�ø�)
            float ref_stat = float(hp_delta) / float(ref_per);                                      // ���� �ջ�ɷ�ġ
            
            
            // ���๫�� �ڵ�����
            pk::person@ actor;
            float sum_stat = 0.0f;
            
            if (�����ü�_���ϳ���_������� and !(�����ü�_���ϳ���_AI�� and building.is_player()))
                sum_stat += float(pk::max(0, �����ü�_���ϳ���_����պ�));  // ���� ������ ������ �߰�

            for (int j = (int(arr_idle_person.length) - 1); j >= 0; j--)
            {
                @actor = arr_idle_person[j];
                if ((float(actor.stat[����ɷ�_��ġ]) * stat_weight + sum_stat) > ref_stat) break;
            }
            
            string facility_name = pk::decode(pk::get_name(facility_upgrade));
            
            // ���๫�� ����â
            pk::list<pk::person@> person_sel;
            person_sel.add(actor);
            
            bool confirm = false;
            while(!confirm)
            {
                // ����Ⱓ
                @actor = person_sel[0];
                float est_stat = float(actor.stat[����ɷ�_��ġ]) * stat_weight;
                int est_turn = int(calc_remain_turn(hp_delta, �����ӹ�_����պ�, est_stat));
                int est_period = 10 + 10 * est_turn;
                int est_gold = city_gold - upgrade_cost;
                
                // ����պ� ��ᰡ 1�� �Ǵ� ������_�ڵ�_���ø�� ��� ���̶���Ʈ ǥ��
                if (������_��ġ_�ڵ����� or int(arr_target.length) == 1)
                {
                    target_pos_t = arr_target[0].pos;
                    pk::scene(pk::scene_t(goto_facility));
                }
                
                if (������_����_�ڵ����� or int(arr_idle_person.length) == 1)
                {
                    string actor_name = pk::decode(pk::get_name(actor));
                    bool answer = pk::yes_no(pk::encode(pk::format("\x1b[1x{}\x1b[0x���� ����պ��� ����ұ��?\n(\x1b[1x{}��\x1b[0x �ҿ�, \x1b[2x{}\x1b[0x �� {}��\x1b[17x{}\x1b[0x)", actor_name, est_period, city_name, city_gold, est_gold)));
                    
                    // ����պ� ��ᰡ 1�� �Ǵ� ������_�ڵ�_���ø�� ��� ���̶���Ʈ ����
                    if (������_��ġ_�ڵ����� or int(arr_target.length) == 1)
                        pk::scene(pk::scene_t(remove_highlights)); 
                    
                    confirm = true;
                    if (!answer) return true;     // ��� ����
                }
                else if (!������_����_�ڵ����� and int(arr_idle_person.length) > 1)
                {
                    string msg_est = (kunshu.get_id() == actor.get_id())? pk::format("\x1b[1x{}��\x1b[0x �ɸ��ڱ�. ���� �ұ�?", est_period) : pk::format("\x1b[1x{}��\x1b[0x �ɸ��ڱ���. ���� �ұ��?", est_period);                
                    int answer = pk::choose({ pk::encode("����"), pk::encode("����"), pk::encode("���") }, 
                                              pk::encode(msg_est), actor );
                    
                    // ����պ� ��ᰡ 1�� �Ǵ� ������_�ڵ�_���ø�� ��� ���̶���Ʈ ����
                    if (������_��ġ_�ڵ����� or int(arr_target.length) == 1)
                        pk::scene(pk::scene_t(remove_highlights));                                         
                    
                    if      (answer == 0)
                        confirm = true;
                    else if (answer == 1)
                    {
                        confirm = false;
                        person_sel = pk::person_selector(pk::encode("���๫�弱��"), pk::encode("����պ��� ������ ������ �����մϴ�."), list_idle_person, 1, 1, person_sel, 1);
                        if (person_sel.count == 0) return true;
                    }
                    else return true;
                }
                
                @actor = person_sel[0];
            }
            
            
            // ����պ� ��� ��Ȯ�� (��ᰡ �������� ���)
            if (int(arr_target.length) > 1 and !������_��ġ_�ڵ�����)
            {
                int sel = 0;
                int max = int(arr_target.length);
                string msg_confirm = (kunshu.get_id() == actor.get_id())? "� ���ü��� �պ��ұ�?" : "� ���ü��� �պ��ұ��?";
                
                bool _confirm = false;
                while(!_confirm)
                {
                    target_pos_t = arr_target[sel].pos;
                    pk::scene(pk::scene_t(goto_facility));
                    
                    int answer = pk::choose({ pk::encode("����"), pk::encode("����"), pk::encode("����"), pk::encode("���") }, 
                                              pk::encode(msg_confirm), actor );
                    
                    pk::scene(pk::scene_t(remove_highlights));
                    
                    // ���� ��� ó��
                    if      (answer == 0) _confirm = true;
                    else if (answer == 1)
                    {
                        if (sel >= (max - 1)) sel = 0;
                        else sel++;
                        _confirm = false;
                    }
                    else if (answer == 2)
                    {
                        if (sel <= 0) sel = (max - 1);
                        else sel--;
                        _confirm = false;
                    }
                    else return true;   // ��� ����
                    
                    @target = @arr_target[sel]; // �ü�����
                }
            }            
            
            // ��ǳ��
            string msg_merge = (kunshu.get_id() == actor.get_id())? "���� �պ��Ѵ�" : "���� �պ��ϰڽ��ϴ�";
            pk::say(pk::encode(pk::format("\x1b[2x{}\x1b[0x{}", facility_name, msg_merge)), actor, building);
            
            // ����պ� �������
            pk::merge_cmd_info cmd_merge;
            @cmd_merge.base  = @base;
            @cmd_merge.actor = @actor;
            @cmd_merge.src   = @target;
            @cmd_merge.dst   = @building;
            // ����պ� ��ɽ���
            pk::command(cmd_merge);
            
            pk::combat_text(-upgrade_cost, 3, base.pos); // ����պ� ���࿡ ���� �� ���� ǥ��
            
			return true;
			
		}
        

        //---------------------------------------------------------------------------------------
        //     ���Ǽ� �޴�
        //---------------------------------------------------------------------------------------
        
		string getText_���Ǽ�()
		{
			return pk::encode(pk::decode(pk::get_name(pk::get_facility(develop_id))) + " �Ǽ�");
		}

        bool isVisible_���Ǽ�()
		{ 
            if (pk::is_campaign()) return false;
            else if (building.get_id() < �ǹ�_������ or develop_id < 0) return false;
            else if (!ai_force_ctrl and !building.is_player()) return false;   // ��ǻ�� AI ����
            else if (!district_ctrl and district.no > 1) return false;
            return true;
		}
        
		bool isEnabled_���Ǽ�()
		{ 
            if (pk::is_campaign()) return false;
            else if (building.get_id() < �ǹ�_������ or develop_id < 0) return false;
            else if (city.num_devs == city.max_devs) return false;
            else if (target_dev_pos.length == 0) return false;
            else if (list_idle_person.count < 1) return false;
            else if (int(district.ap) < ACTION_COST_��������)  return false;
			else if (city_gold < develop_cost or develop_cost < 0) return false;
            else if (enemies_around) return false;
			return true;
		}
        
		string getDesc_���Ǽ�()
		{
            if (building.get_id() < �ǹ�_������ or develop_id < 0)
                return pk::encode("���ü� �Ǽ��� ������ �ü��� �ƴմϴ�.");
            else if (city.num_devs == city.max_devs)
                return pk::encode("�ֺ��� �� �������� �����ϴ�");
            else if (target_dev_pos.length == 0)
                return pk::encode("�ֺ��� �� �������� �����ϴ�");
            else if (list_idle_person.count < 1)
                return pk::encode("���� ������ ������ �����ϴ�.");
            else if (int(district.ap) < ACTION_COST_��������) 
                return pk::encode(pk::format("�ൿ���� �����մϴ� (�ൿ�� {} �ʿ�)", ACTION_COST_��������));
			else if (city_gold < develop_cost or develop_cost < 0)
				return pk::encode(pk::format("���� �����մϴ� (��{} �ʿ�)", develop_cost));
            else if (enemies_around)
                return pk::encode("�ֺ��� ���δ밡 �ֽ��ϴ�");
            return pk::encode(pk::format("�ֺ��� ���ü��� �Ǽ��մϴ� (�ൿ��{}, ��{} �Ҹ�)", ACTION_COST_��������, develop_cost));
        }
        

		bool handler_���Ǽ�()
		{
            return handler_��������(develop_id);
        }
        
        
        //---------------------------------------------------------------------------------------
        //     ����/��â�Ǽ� �޴�
        //---------------------------------------------------------------------------------------
        
		string getText_�߾ӰǼ�()
		{
			return pk::encode(pk::decode(pk::get_name(pk::get_facility(center_id))) + " �Ǽ�");
		}

        bool isVisible_�߾ӰǼ�()
		{ 
            if (pk::is_campaign()) return false;
            else if (building.get_id() < �ǹ�_������ or center_id < 0) return false;
            else if (!ai_force_ctrl and !building.is_player()) return false;   // ��ǻ�� AI ����
            else if (!district_ctrl and district.no > 1) return false;
            return true;
		}
        
		bool isEnabled_�߾ӰǼ�()
		{ 
            if (pk::is_campaign()) return false;
            else if (building.get_id() < �ǹ�_������ or center_id < 0) return false;
            else if (city.num_devs == city.max_devs) return false;
            else if (target_dev_pos.length == 0) return false;
            else if (list_idle_person.count < 1) return false;
            else if (int(district.ap) < ACTION_COST_��������)  return false;
            else if (center_facility_nearby) return false;
			else if (city_gold < center_cost or center_cost < 0) return false;
            else if (enemies_around) return false;
			return true;
		}
        
		string getDesc_�߾ӰǼ�()
		{
            if (building.get_id() < �ǹ�_������ or center_id < 0)
                return pk::encode("�����̳� ���� �ֺ����� ���߰����մϴ�");
            else if (city.num_devs == city.max_devs)
                return pk::encode("�ֺ��� �� �������� �����ϴ�");
            else if (target_dev_pos.length == 0)
                return pk::encode("�ֺ��� �� �������� �����ϴ�");
            else if (list_idle_person.count < 1)
                return pk::encode("���� ������ ������ �����ϴ�.");
            else if (int(district.ap) < ACTION_COST_��������) 
                return pk::encode(pk::format("�ൿ���� �����մϴ� (�ൿ�� {} �ʿ�)", ACTION_COST_��������));
			else if (city_gold < center_cost or center_cost < 0)
				return pk::encode(pk::format("���� �����մϴ� (��{} �ʿ�)", center_cost));
            else if (center_facility_nearby)
                return pk::encode(pk::format("�̹� {}(��)�� �ֺ��� �ֽ��ϴ�", pk::decode(pk::get_name(pk::get_facility(center_id)))));
            else if (enemies_around)
                return pk::encode("�ֺ��� ���δ밡 �ֽ��ϴ�");
            return pk::encode(pk::format("�ֺ��� {}(��)�� �Ǽ��մϴ� (�ൿ��{}, ��{} �Ҹ�)", pk::decode(pk::get_name(pk::get_facility(center_id))), ACTION_COST_��������, center_cost));
        }
        
        bool handler_�߾ӰǼ�()
		{
            return handler_��������(center_id);
        }
            
        //---------------------------------------------------------------------------------------
        // ���� ���
		bool handler_��������(int city_dev_id)
		{
            if (list_idle_person.count == 0) return true;
            if (int(target_dev_pos.length) == 0) return true;
            
            if (������_����_�˻�����) sort_dev_pos(city_dev_id);
            
            // ������ġ ���Ǽ���
            pk::point target_pos = target_dev_pos[0];
            
            // �ü� ������
            pk::facility@ facility_dev = pk::get_facility(city_dev_id);
            string facility_name = pk::decode(pk::get_name(facility_dev));
            string city_name = pk::decode(pk::get_name(city));
            uint16 hp_delta = uint16(facility_dev.hp - facility_dev.hp / 4);      
            
            // �����ü�_�ʱ⳻��_�߰���� ��� �� : �ܿ� ������ ���̰� ���
            if (�����ü�_�ʱ⳻��_�߰���� and !(�����ü�_�ʱ⳻��_AI�� and building.is_player())) 
            {
                if (�ü�_���۴� <= city_dev_id and city_dev_id <= �ü�_���г�)    // 1�� �ü��� ���
                {
                    float hp_add_ratio = pk::min(pk::max(0.f, �����ü�_�ʱ⳻��_�߰�����), 0.75f);  // �Է¹������� : 0%~75%
                    hp_delta -= uint16(float(facility_dev.hp) * hp_add_ratio);
                }                    
            }
            
            // ��ġ���� ���� ������ ����
            list_idle_person.sort(function(a, b)
            {
                return a.stat[����ɷ�_��ġ] > b.stat[����ɷ�_��ġ];
            } );
            
            // ���� ����� ����
            pk::array<pk::person@> arr_idle_person = pk::list_to_array(list_idle_person);
            int idle_cnt = int(arr_idle_person.length);
            int act_mod = (���߽���_�����_����)? 2 : 1;
            int act_add = (city_dev_id == center_id)? 1 : 0;
            int min_actors = pk::min(3, pk::max(1, pk::min(idle_cnt, (act_add + idle_cnt/act_mod)) ));     // �����ο� �ڵ�����
                        
            // ���� �۾��ϼ� �� �ּҴɷ�ġ ���
            float max_stat = 0.0f;
            for (int i = 0; i < min_actors; i++)    //�ִ밡�� �ɷ�ġ�ջ�
            {
                float stat_weight = (i == 0)? 1.5f : 0.5f;
                max_stat += float(arr_idle_person[i].stat[����ɷ�_��ġ]) * stat_weight;  
            }
            if (�����ü�_���ϳ���_������� and !(�����ü�_���ϳ���_AI�� and building.is_player()))
                max_stat += float(pk::max(0, �����ü�_���ϳ���_�ű԰���));  // ���� ������ ������ �߰�
            
            int   ref_per = int(float(hp_delta) / max_stat) + (((float(hp_delta) % max_stat) > 0)? 1 : 0); // �Ǽ��Ⱓ ���� (�ø�)
            float ref_stat = float(hp_delta) / float(ref_per);                                      // ���� �ջ�ɷ�ġ
            float min_stat = float(hp_delta) / 9.f;     // �Ǽ��Ⱓ �ִ� 100�� ����
            
            bool single_actor_mode = false;  // �Ϲ� ����
            if (ref_stat < min_stat)         // �Ǽ��Ⱓ �ִ� 100�� 
            {
                single_actor_mode = true;    
                min_actors = 1;
            }
            
            // �����ο� ���๫�� �ڵ�����
            pk::list<pk::person@> person_sel;
            float sum_stat = 0.0f;

            if (�����ü�_���ϳ���_������� and !(�����ü�_���ϳ���_AI�� and building.is_player()))
                sum_stat += float(pk::max(0, �����ü�_���ϳ���_�ű԰���));  // ���� ������ ������ �߰�

            for (int i = 0; i < min_actors; i++)
            {   
                float stat_weight = (i == 0)? 1.5f : 0.5f; 
                pk::person@ actor_t;
                if (single_actor_mode)      // �Ǽ��Ⱓ �ִ� 100�� ����Ʈ �� ���弱��
                {
                    for (int j = 0 ; j < int(arr_idle_person.length); j++)
                    {
                        if (!person_sel.contains(arr_idle_person[j]))
                        {
                            @actor_t = arr_idle_person[j];
                            if ((float(actor_t.stat[����ɷ�_��ġ]) * stat_weight + sum_stat) > min_stat) break;
                        }
                    }
                }
                else    // �Ϲ����� ���弱��
                {
                    for (int j = (int(arr_idle_person.length) - 1); j >= 0; j--)
                    {
                        if (!person_sel.contains(arr_idle_person[j]))
                        {
                            @actor_t = arr_idle_person[j];
                            if ((float(actor_t.stat[����ɷ�_��ġ]) * stat_weight + sum_stat) > ref_stat) break;
                        }
                    }
                }
                if (pk::is_alive(actor_t))
                {
                    person_sel.add(actor_t);
                    sum_stat += actor_t.stat[����ɷ�_��ġ] * stat_weight;
                }
                if (sum_stat > ref_stat) break;
            }

            if (����׸��)
                pk::info(pk::format("{} ����, �ִ�{}��, �ּ�{}��, ���شɷ�{}, ����{}��", facility_name, min_actors, 10*ref_per, ref_stat, person_sel.count));

            
            // ���๫�� ������ Ȯ��â
            pk::array<pk::person@> actors = pk::list_to_array(person_sel);
            pk::person@ leader;
            bool confirm = false;
            while(!confirm)
            {
                // ���ù��� �ɷ�ġ �ջ�, �̸� ����
                sum_stat = 0.0f;
                string actor_name;
                for (int i = 0; i < int(actors.length); i++)
                {
                    pk::person@ actor_t = actors[i];
                    if (i == 0)
                    {
                        sum_stat += float(actor_t.stat[����ɷ�_��ġ]) * 1.5f;
                        actor_name = pk::decode(pk::get_name(actor_t));
                    }
                    else
                    {
                        sum_stat += float(actor_t.stat[����ɷ�_��ġ]) * 0.5f;
                        actor_name = actor_name + ", " + pk::decode(pk::get_name(actor_t));
                    }
                }
                
                // ��ǥ���� ����
                if (person_sel.contains(kunshu)) @leader = kunshu;
                else @leader = actors[0];
                string msg_sel = (kunshu.get_id() == leader.get_id())? "" : "��";
                
                // ����Ⱓ
                float est_stat = pk::max(sum_stat, float(int(facility_dev.hp * 0.75f / 9.f)));
                int est_turn = int(calc_remain_turn(hp_delta, �����ӹ�_����, est_stat));
                int est_period = 10 + 10 * est_turn;
                int est_gold = city_gold - ((city_dev_id == develop_id)? develop_cost : center_cost);
                
                // �������� 1�� �Ǵ� ������_�ڵ�_���ø�� �� ��� ���̶���Ʈ ǥ��
                if (������_��ġ_�ڵ����� or int(target_dev_pos.length) == 1)
                {
                    target_pos_t = target_dev_pos[0];
                    pk::scene(pk::scene_t(goto_facility));
                }
                
                if (������_����_�ڵ����� or int(arr_idle_person.length) == 1)
                {
                    bool answer = pk::yes_no(pk::encode(pk::format("\x1b[1x{}\x1b[0x���� \x1b[2x{}\x1b[0x ������\n����ұ��? (\x1b[1x{}\x1b[0x�� �ҿ�, \x1b[2x{}\x1b[0x �� {}��\x1b[17x{}\x1b[0x)",actor_name, facility_name, est_period, city_name, city_gold, est_gold)));
        
                    // �������� 1�� �Ǵ� ������_�ڵ�_���ø�� �� ��� ���̶���Ʈ ����
                    if (������_��ġ_�ڵ����� or int(target_dev_pos.length) == 1)
                        pk::scene(pk::scene_t(remove_highlights));

                    confirm = true;
                    if (!answer) return true;     // ��� ����
                }
                else if (!������_����_�ڵ����� and int(arr_idle_person.length) > 1)
                {
                    int answer = pk::choose({ pk::encode("����"), pk::encode("����"), pk::encode("���") }, 
                                              pk::encode(pk::format("\x1b[1x{}\x1b[0x���� \x1b[2x{}\x1b[0x ������\n����ұ�{}? (\x1b[1x{}\x1b[0x�� �ҿ�, \x1b[2x{}\x1b[0x �� {}��\x1b[17x{}\x1b[0x)",actor_name, facility_name, msg_sel, est_period, city_name, city_gold, est_gold)),
                                              leader);
                    // �������� 1�� �Ǵ� ������_�ڵ�_���ø�� �� ��� ���̶���Ʈ ����
                    if (������_��ġ_�ڵ����� or int(target_dev_pos.length) == 1)
                        pk::scene(pk::scene_t(remove_highlights));
                                  
                    if (answer == 0)
                        confirm = true;
                    else if (answer == 1) 
                    {
                        confirm = false;
                        
                        // ���๫�� ���ú���
                        person_sel = pk::person_selector(pk::encode("���๫�弱��"), pk::encode("���� �ü��� ������ ������ �����մϴ�."), list_idle_person, 1, pk::min(3, int(arr_idle_person.length)), person_sel, 0);
                        if (person_sel.count == 0) return true;
                        
                    }
                    else return true;
                }
                
                actors = pk::list_to_array(person_sel);
            }
            
            if (����׸��)
            {
                for (int i = 0; i < int(target_dev_pos.length); i++)
                {
                    pk::point dev_pos = target_dev_pos[i];
                    pk::info(pk::format("{} �Ǽ�����:: x��ǥ:{}, y��ǥ:{}", facility_name, dev_pos.x, dev_pos.y));
                }
            }
            
            // ������ ��Ȯ�� (�� �������� �������� ���)
            if (int(target_dev_pos.length) > 1 and !������_��ġ_�ڵ�����)
            {
                int sel = 0;
                int max = int(target_dev_pos.length);
                
                bool _confirm = false;
                while(!_confirm)
                {
                    target_pos_t = target_dev_pos[sel];
                    pk::scene(pk::scene_t(goto_facility));
                    
                    string msg_sel = (kunshu.get_id() == leader.get_id())? "" : "��";
                    int answer = pk::choose({ pk::encode("����"), pk::encode("����"), pk::encode("����"), pk::encode("���") }, 
                                              pk::encode(pk::format("���⿡ \x1b[1x{}\x1b[0x(��)�� ������{}?", facility_name, msg_sel)), 
                                              leader);
                    
                    pk::scene(pk::scene_t(remove_highlights));
                    
                    // ���� ��� ó��
                    if      (answer == 0) _confirm = true;
                    else if (answer == 1)
                    {
                        if (sel >= (max - 1)) sel = 0;
                        else sel++;
                        _confirm = false;
                    }
                    else if (answer == 2)
                    {
                        if (sel <= 0) sel = (max - 1);
                        else sel--;
                        _confirm = false;
                    }
                    else return true;   // ��� ����
                    
                    target_pos = target_pos_t; // �ü�����
                }
                
            }
            
            // ���� �������
            pk::develop_cmd_info cmd_develop;
            @cmd_develop.base = @base;
            for(int i = 0; i < int(actors.length); i++)
            {
                @cmd_develop.actors[i] = actors[i];
            }
            cmd_develop.facility = city_dev_id;
            cmd_develop.pos = target_pos;
            
            // ���� ��ɽ���
            pk::command(cmd_develop);
            
            pk::combat_text(-develop_cost, 3, base.pos); // ���� ���࿡ ���� �� ���� ǥ��
            
			return true;
			
		}
        
        //---------------------------------------------------------------------------------------
        
        bool ����׸�� = false;
        
	}
   
	Main main;
}

