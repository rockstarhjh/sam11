/*
@ ������: �⸶å��
@ UPDATE: '19.3.3    / �������� : �������ճ��� �޴� (��������, ����¡��, ���ܼ���, �����Ʒ�, ���ܻ���(�ܾ�/����/����/����))
@ UPDATE: '19.3.13   / ���泻�� : ��ġ�� ����, ���ܻ��� �޴�����, ���ܰ��� �޴��߰�, �޴� Ȯ��/��� ��� �߰�
@ UPDATE: '19.3.20   / ���泻�� : �������� �� �޽��� ��������, ������ ȭ���̵� �޴� �߰�
@ UPDATE: '19.4.5    / ���泻�� : �⺴�δ� �������� �ɼ� �߰�
@ UPDATE: '19.7.3    / ���泻�� : �⺴�δ� ��ǥ���� �� ���� ��� �߰�
@ UPDATE: '20.2.26   / ���泻�� : ���ܻ��� �� ���� ���� �ؽ�Ʈ ���� ����, ���ܻ��� ��������Ʈ ������ ����
*/

namespace �������ո��
{
	//=======================================================================================
    // ***** ���ܸ�� �޴����� *****
    // ������  : ������ ������ ������ �Ҽ� ���÷� ȭ�� �̵�
    // ���ܰ��� : �Ҽӱ��� �� ���������� �����ϴ� �������� �����Ͽ� [����] �ϰ����� (�� ���� ����)
    // ���ܿ��� : �Ҽӱ��� �� ���������� �����ϴ� �������� �����Ͽ� [����] �ϰ����� (�Ʊ� ���� ����)
    
    // �������� : �ش������ [¡��],[����],[�Ʒ�] ���ܸ�� ���ӽ���
    // ����¡�� : �Ҽӱ��� �� ���������� �����ϴ� ���õ��� �����Ͽ� [¡��] �ϰ�����
    // ���ܼ��� : �Ҽӱ��� �� ���������� �����ϴ� ���õ��� �����Ͽ� [����] �ϰ�����
    // �����Ʒ� : �Ҽӱ��� �� ���������� �����ϴ� �������� �����Ͽ� [�Ʒ�] �ϰ�����
    
    // ���ܻ��� : �Ҽӱ��� �� ���������� �����ϴ� ���õ��� �����Ͽ� [�ܾ�/����/����/����] �ϰ�����
	//---------------------------------------------------------------------------------------
    
    // ���� ����
    const bool  ���ܸ��_���ܰ����⺴ = true;    // �������� �����ϴ� �������� �ϰ����� �޴� Ȱ��ȭ
    const bool  ���ܸ��_¡�������Ʒ� = true;    // ¡��,����,�Ʒ� ���� �ϰ����� �ϴ� �޴��� Ȱ��ȭ
    const bool  ���ܸ��_���ܺ������ = true;    // �������(�ܾ�,����,����,����)�� �ϰ������ϴ� �޴� Ȱ��ȭ
    const bool  ���ܸ��_���ܼ��ø޴� = true;    // [������] �޴� ��뿩�� : ������ �Ҽ� �������� ȭ���̵�
    
    const bool  ���ܸ��_���ӱ������� = true;   // ���ӱ��� ���ܸ޴� Ȱ��ȭ ���� (true=Ȱ��ȭ, false=��Ȱ��ȭ)
    const bool  ���ܸ��_���ý���Ȯ�� = false;   // true���� �� ���ø��� Ȯ�θ޽��� ���� (����ȭ �÷��� �� false ����)
    
    //---------------------------------------------------------------------------------------
    // ���� ����
    const float ���ܸ��_¡���ִ���� = 0.9f;  // ���纴��/�ִ뺴�� ���ذ� �̸��� ���ø� ¡�� ���� (0.0f ~ 1.0f ����)
    const int   ���ܸ��_¡���ּ�ġ�� = 80;    // ġ�� ���ذ� �̻��� ���ø� ¡�� ���� (0~100 ����)
    const int   ���ܸ��_�����ִ�ġ�� = 90;    // ġ�� ���ذ� �̸��� ���ø� ���� ���� (0~100 ����)
    const int   ���ܸ��_�Ʒ��ּҺ��� = 1000;  // ���� ���ذ� �̻��� ������ �Ʒ� ���� (1 �̻�)
    const int   ���ܸ��_�Ʒñ�±��� = 115;   // ��� ���ذ� �̸��� ������ �Ʒ� ���� (1~120 ����)

    //---------------------------------------------------------------------------------------
    // ���� ����
    const float ���ܸ��_�����ִ���� = 0.9f;  // �ִ���ذ� �̸��� ���ø� ���� ���� (0.0f ~ 1.0f ����)
    
    //---------------------------------------------------------------------------------------
    // ���� �⺴
    const int   ���ܸ��_�⺴�ּҺ��� = 4000;   // ���� ���� �� �δ뺴�� �ּұ���
    const int   ���ܸ��_�⺴�ִ뺴�� = 8000;   // ���� ���� �� �δ뺴�� �ִ���� (���� ����, ����, ���ֻ��� �̳� ��)
    const int   ���ܸ��_�⺴�������� = 20000;  // �⺴������ �ּҺ��� ���� (�������� �� ���غ��� �̸��� �Ǹ� �����Ұ�)
    const float ���ܸ��_�⺴�������� = 1.5f;  // �δ뺴�� ��� ���� ����
    
    //=======================================================================================
    
	
	class Main
	{
		
		Main()
		{
            if (���ܸ��_¡�������Ʒ� or ���ܸ��_���ܺ������ or ���ܸ��_���ܰ����⺴)
            {
                pk::menu_item ���ܸ��;
                ���ܸ��.menu = 0;        // �����޴�
                ���ܸ��.pos = 0;
                ���ܸ��.init = pk::building_menu_item_init_t(init);
                ���ܸ��.is_visible = pk::menu_item_is_visible_t(isVisible);
                ���ܸ��.is_enabled = pk::menu_item_is_enabled_t(isEnabled);
                ���ܸ��.get_text = pk::menu_item_get_text_t(getText_���ܸ��);
                ���ܸ��.get_desc = pk::menu_item_get_desc_t(getDesc_���ܸ��);
                menu_top = pk::add_menu_item(���ܸ��);
                
                // ������ �ҼӰ������� ȭ���̵�
                if (���ܸ��_���ܼ��ø޴�)
                {
                    pk::menu_item ������;
                    ������.menu = menu_top;   // ���ܸ�ɸ޴�
                    ������.init = pk::building_menu_item_init_t(init);
                    ������.get_image_id = pk::menu_item_get_image_id_t(getImageID_orange);     // ��Ȳ�� �޴�
                    ������.is_visible = pk::menu_item_is_visible_t(isVisible);
                    ������.is_enabled = pk::menu_item_is_enabled_t(isEnabled);
                    ������.get_text = pk::menu_item_get_text_t(getText_������);
                    ������.get_desc = pk::menu_item_get_desc_t(getDesc_������);
                    ������.handler = pk::menu_item_handler_t(handler_������);
                    pk::add_menu_item(������);
                }
                
                // ��� �޴� �׷�
                if (���ܸ��_���ܰ����⺴) add_menu_group_attack();   // ���� �����޴� �߰�
                if (���ܸ��_¡�������Ʒ�) add_menu_group_govern();   // ���� �����޴� �߰�
                if (���ܸ��_���ܺ������) add_menu_group_weapon();   // ���� �����޴� �߰�
                
            }
		}
        
        
        void add_menu_group_attack()
        {

            // �������� (Ȯ��/��ҿ� �޴�)
            pk::menu_item ��������;
			��������.menu = menu_top;   // ���ܸ�ɸ޴�
			��������.init = pk::building_menu_item_init_t(init);
            ��������.get_image_id = pk::menu_item_get_image_id_t(getImageID_orange);     // ��Ȳ�� �޴�
            ��������.is_visible = pk::menu_item_is_visible_t(isVisible);
			��������.is_enabled = pk::menu_item_is_enabled_t(isEnabled_��������);
			��������.get_text = pk::menu_item_get_text_t(getText_��������);
			��������.get_desc = pk::menu_item_get_desc_t(getDesc_��������);
            ��������.handler = pk::menu_item_handler_t(handler_��������);
			pk::add_menu_item(��������);
            
            
            // ���ܰ���
            pk::menu_item ���ܰ���;
			���ܰ���.menu = menu_top;   // ���ܸ�ɸ޴�
			���ܰ���.init = pk::building_menu_item_init_t(init);
            ���ܰ���.is_visible = pk::menu_item_is_visible_t(isVisible_��������);
			���ܰ���.is_enabled = pk::menu_item_is_enabled_t(isEnabled_���ܰ���);
			���ܰ���.get_text = pk::menu_item_get_text_t(getText_���ܰ���);
			���ܰ���.get_desc = pk::menu_item_get_desc_t(getDesc_���ܰ���);
            ���ܰ���.handler = pk::menu_item_handler_t(handler_���ܰ���);
			pk::add_menu_item(���ܰ���);
            
            // ���ܿ���
            pk::menu_item ���ܿ���;
			���ܿ���.menu = menu_top;   // ���ܸ�ɸ޴�
			���ܿ���.init = pk::building_menu_item_init_t(init);
            ���ܿ���.is_visible = pk::menu_item_is_visible_t(isVisible_��������);
			���ܿ���.is_enabled = pk::menu_item_is_enabled_t(isEnabled_���ܰ���);
			���ܿ���.get_text = pk::menu_item_get_text_t(getText_���ܿ���);
			���ܿ���.get_desc = pk::menu_item_get_desc_t(getDesc_���ܿ���);
            ���ܿ���.handler = pk::menu_item_handler_t(handler_���ܿ���);
			pk::add_menu_item(���ܿ���);
        }
        
        
        void add_menu_group_govern()
        {
        
            // ��������
            pk::menu_item ��������;
			��������.menu = menu_top;   // ���ܸ�ɸ޴�
			��������.init = pk::building_menu_item_init_t(init);
            ��������.get_image_id = pk::menu_item_get_image_id_t(getImageID_orange);     // ��Ȳ�� �޴�
            ��������.is_visible = pk::menu_item_is_visible_t(isVisible);
			��������.is_enabled = pk::menu_item_is_enabled_t(isEnabled_��������);
			��������.get_text = pk::menu_item_get_text_t(getText_��������);
			��������.get_desc = pk::menu_item_get_desc_t(getDesc_��������);
            ��������.handler = pk::menu_item_handler_t(handler_��������);
			pk::add_menu_item(��������);
            
            
            // ���ܳ��� (Ȯ��/��ҿ� �޴�)
            pk::menu_item ���ܳ���;
			���ܳ���.menu = menu_top;   // ���ܸ�ɸ޴�
			���ܳ���.init = pk::building_menu_item_init_t(init);
            ���ܳ���.get_image_id = pk::menu_item_get_image_id_t(getImageID_orange);     // ��Ȳ�� �޴�
            ���ܳ���.is_visible = pk::menu_item_is_visible_t(isVisible);
			���ܳ���.is_enabled = pk::menu_item_is_enabled_t(isEnabled_���ܳ���);
			���ܳ���.get_text = pk::menu_item_get_text_t(getText_���ܳ���);
			���ܳ���.get_desc = pk::menu_item_get_desc_t(getDesc_���ܳ���);
            ���ܳ���.handler = pk::menu_item_handler_t(handler_���ܳ���);
			pk::add_menu_item(���ܳ���);
            
            // ���ܳ��� (¡��)
            pk::menu_item ����¡��;
			����¡��.menu = menu_top;   // ���ܸ�ɸ޴�
			����¡��.init = pk::building_menu_item_init_t(init);
            ����¡��.is_visible = pk::menu_item_is_visible_t(isVisible_���ܳ���);
			����¡��.is_enabled = pk::menu_item_is_enabled_t(isEnabled_����¡��);
			����¡��.get_text = pk::menu_item_get_text_t(getText_����¡��);
			����¡��.get_desc = pk::menu_item_get_desc_t(getDesc_����¡��);
            ����¡��.handler = pk::menu_item_handler_t(handler_����¡��);
			pk::add_menu_item(����¡��);
            
            // ���ܳ��� (����)
            pk::menu_item ���ܼ���;
			���ܼ���.menu = menu_top;   // ���ܸ�ɸ޴�
			���ܼ���.init = pk::building_menu_item_init_t(init);
            ���ܼ���.is_visible = pk::menu_item_is_visible_t(isVisible_���ܳ���);
			���ܼ���.is_enabled = pk::menu_item_is_enabled_t(isEnabled_���ܼ���);
			���ܼ���.get_text = pk::menu_item_get_text_t(getText_���ܼ���);
			���ܼ���.get_desc = pk::menu_item_get_desc_t(getDesc_���ܼ���);
            ���ܼ���.handler = pk::menu_item_handler_t(handler_���ܼ���);
			pk::add_menu_item(���ܼ���);
            
            // ���ܳ��� (�Ʒ�)
            pk::menu_item �����Ʒ�;
			�����Ʒ�.menu = menu_top;   // ���ܸ�ɸ޴�
			�����Ʒ�.init = pk::building_menu_item_init_t(init);
            �����Ʒ�.is_visible = pk::menu_item_is_visible_t(isVisible_���ܳ���);
			�����Ʒ�.is_enabled = pk::menu_item_is_enabled_t(isEnabled_�����Ʒ�);
			�����Ʒ�.get_text = pk::menu_item_get_text_t(getText_�����Ʒ�);
			�����Ʒ�.get_desc = pk::menu_item_get_desc_t(getDesc_�����Ʒ�);
            �����Ʒ�.handler = pk::menu_item_handler_t(handler_�����Ʒ�);
			pk::add_menu_item(�����Ʒ�);
            
        }
        
        
        void add_menu_group_weapon()
        {
            // ���ܻ��� (Ȯ��/��ҿ� �޴�)
            pk::menu_item ���ܻ���;
			���ܻ���.menu = menu_top;   // ���ܸ�ɸ޴�
			���ܻ���.init = pk::building_menu_item_init_t(init);
			���ܻ���.get_image_id = pk::menu_item_get_image_id_t(getImageID_orange);     // ��Ȳ�� �޴�
            ���ܻ���.is_visible = pk::menu_item_is_visible_t(isVisible);
			���ܻ���.is_enabled = pk::menu_item_is_enabled_t(isEnabled_���ܻ���);
			���ܻ���.get_text = pk::menu_item_get_text_t(getText_���ܻ���);
			���ܻ���.get_desc = pk::menu_item_get_desc_t(getDesc_���ܻ���);
            ���ܻ���.handler = pk::menu_item_handler_t(handler_���ܻ���);
			pk::add_menu_item(���ܻ���);
            
            // ���ܻ��� (�ܾ�)
            pk::menu_item ���ܴܾ�;
			���ܴܾ�.menu = menu_top;   // ���ܸ�ɸ޴�
			���ܴܾ�.init = pk::building_menu_item_init_t(init);
            ���ܴܾ�.is_visible = pk::menu_item_is_visible_t(isVisible_���ܻ���);
			���ܴܾ�.is_enabled = pk::menu_item_is_enabled_t(isEnabled_���ܴܾ�);
			���ܴܾ�.get_text = pk::menu_item_get_text_t(getText_���ܴܾ�);
			���ܴܾ�.get_desc = pk::menu_item_get_desc_t(getDesc_���ܴܾ�);
            ���ܴܾ�.handler = pk::menu_item_handler_t(handler_���ܴܾ�);
			pk::add_menu_item(���ܴܾ�);
            
            // ���ܻ��� (����)
            pk::menu_item ���ܱ���;
			���ܱ���.menu = menu_top;   // ���ܸ�ɸ޴�
			���ܱ���.init = pk::building_menu_item_init_t(init);
            ���ܱ���.is_visible = pk::menu_item_is_visible_t(isVisible_���ܻ���);
			���ܱ���.is_enabled = pk::menu_item_is_enabled_t(isEnabled_���ܱ���);
			���ܱ���.get_text = pk::menu_item_get_text_t(getText_���ܱ���);
			���ܱ���.get_desc = pk::menu_item_get_desc_t(getDesc_���ܱ���);
            ���ܱ���.handler = pk::menu_item_handler_t(handler_���ܱ���);
			pk::add_menu_item(���ܱ���);
            
            // ���ܻ��� (����)
            pk::menu_item ���ܰ���;
			���ܰ���.menu = menu_top;   // ���ܸ�ɸ޴�
			���ܰ���.init = pk::building_menu_item_init_t(init);
            ���ܰ���.is_visible = pk::menu_item_is_visible_t(isVisible_���ܻ���);
			���ܰ���.is_enabled = pk::menu_item_is_enabled_t(isEnabled_���ܰ���);
			���ܰ���.get_text = pk::menu_item_get_text_t(getText_���ܰ���);
			���ܰ���.get_desc = pk::menu_item_get_desc_t(getDesc_���ܰ���);
            ���ܰ���.handler = pk::menu_item_handler_t(handler_���ܰ���);
			pk::add_menu_item(���ܰ���);
            
            // ���ܻ��� (����)
            pk::menu_item ��������;
			��������.menu = menu_top;   // ���ܸ�ɸ޴�
			��������.init = pk::building_menu_item_init_t(init);
            ��������.is_visible = pk::menu_item_is_visible_t(isVisible_���ܻ���);
			��������.is_enabled = pk::menu_item_is_enabled_t(isEnabled_��������);
			��������.get_text = pk::menu_item_get_text_t(getText_��������);
			��������.get_desc = pk::menu_item_get_desc_t(getDesc_��������);
            ��������.handler = pk::menu_item_handler_t(handler_��������);
			pk::add_menu_item(��������);
            
            
        }
        

        //---------------------------------------------------------------------------------------
        // ��ũ��Ʈ ���ۿ� ���� (���� ���� ����)
        int menu_top;
        
        int menu_extend;    // �޴� Ȯ���ڵ�
        int menu_attack = 1;
        int menu_govern = 2;
        int menu_outfit = 3;
        
        int delay = 300;
        
		pk::building@ building;
		pk::force@ force;
        pk::district@ district;
        pk::person@ kunshu;
        pk::person@ totoku;
        pk::list<pk::district@> district_list;
        
        pk::list<pk::building@> list_drafts;  // ¡������ ����
        pk::list<pk::building@> list_patrol;  // �������� ����
        pk::list<pk::building@> list_drills;  // �Ʒð��� ����
        
        pk::array<bool> arr_available(4, false);
        string cmd_names;
         
        int ap_drafts = 20;
        int ap_patrol = 20;
        int ap_drills = 20;
        float ref_troops_ratio = pk::min(1.0f, pk::max(0.0f, ���ܸ��_¡���ִ����));
        int ref_order_drafts = pk::min(100, pk::max(1, ���ܸ��_¡���ּ�ġ��));
        int ref_order_patrol = pk::min(100, pk::max(1, ���ܸ��_�����ִ�ġ��));
        int ref_min_troops = pk::max(1, ���ܸ��_�Ʒ��ּҺ���);
        int ref_energy = pk::min(120, pk::max(1, ���ܸ��_�Ʒñ�±���));
        
        pk::list<pk::building@> list_outfit0;   // ���尣���� ����
        pk::list<pk::building@> list_outfit1;   // ���������� ����
        pk::list<pk::building@> list_outfit2;   // ���氡�� ����
        pk::list<pk::building@> list_outfit3;   // �������� ����
        
        int ap_outfit = 20;
        float ref_weapon_ratio = pk::min(1.0f, pk::max(0.0f, ���ܸ��_�����ִ����));
        
        int weapon_siege0; 
        int weapon_siege1;
        int weapon_warship;
        pk::array<int> weapon_cost(����_��, 0);
        pk::array<int> weapon_cost_max(4, -1);
        pk::array<int> weapon_outfit(4, -1);
        pk::array<string> arr_weapon_name = {"��", "â", "��", "��", "����", "����", "����", "����", "���", "�ְ�", "����", "����", "??"};
        
        pk::list<pk::building@> list_src_base;
        pk::list<pk::building@> list_dst_base;
        pk::list<pk::building@> list_district_base;    // ���ܰ������� ����
        pk::list<pk::building@> list_force_base;       // �Ʊ� ����
        pk::list<pk::building@> list_enemy_base;       // �� ����
        pk::array<int> arr_tekisei(����_��, ����_C);
        int ap_march = 10;
        
        
        //---------------------------------------------------------------------------------------
        // ���� ��� ���� �޴�
        //---------------------------------------------------------------------------------------
        
        int getImageID_blue()    // �Ķ���
		{ return 856; }
        int getImageID_green()    // ���
		{ return 889; }
        int getImageID_orange()   // ��Ȳ��
		{ return 1249; }
        
        //---------------------------------------------------------------------------------------
        
		void init(pk::building@ building_t)
		{
            @building = @building_t;
            @force = pk::get_force(building.get_force_id());
            district_list = pk::get_district_list(force);
            
            if (building.facility <= �ü�_�ױ�)
            {
                @district = pk::get_district(building.get_district_id());
                @kunshu = pk::get_person(pk::get_kunshu_id(building));
                @totoku = pk::get_person(pk::get_totoku_id(building));
                
                get_weapon_expense();     // ���� ���� ���� �ʱ�ȭ
                
                get_cmd_available();   // ������ ��ɺ� ���డ�ɿ��� �ʱ�ȭ
                get_base_available();  // ��ɺ� ���� ������ �Ҽӱ��� ��������Ʈ �ʱ�ȭ
                
                if (menu_extend == menu_govern 
                    and list_drafts.count == 0 and list_patrol.count == 0 and list_drills.count == 0)
                    menu_extend = -1;
                
                else if (menu_extend == menu_outfit 
                    and list_outfit0.count == 0 and list_outfit1.count == 0 and list_outfit2.count == 0 and list_outfit3.count == 0)
                    menu_extend = -1;
            }
		}

        bool isVisible()
        {
            if (pk::is_campaign()) return false;
            if (building.get_id() >= �ǹ�_������) return false;
            if (building.facility > �ü�_�ױ�) return false;
            if (!���ܸ��_���ӱ������� and district.no > 1) return false;
            return true;
        }
        
		bool isEnabled()
		{ 
            if (building.get_id() >= �ǹ�_������) return false;
			return true;
		}
        
		string getText_���ܸ��()
		{
			return pk::encode("���ܸ��");
		}

		string getDesc_���ܸ��()
		{
            return pk::encode("���� ���� ��ɸ� �����մϴ�");
		}

        
        //---------------------------------------------------------------------------------------
        //  ������ ȭ���̵� �޴�
        //---------------------------------------------------------------------------------------
        
		string getText_������()
		{
			return pk::encode("������");
		}

		string getDesc_������()
		{
            return pk::encode("������ �Ҽ� �������� ȭ���� �̵��մϴ�");
		}

        bool handler_������()
        {
            pk::district@ district_t;
            
            if (!���ܸ��_���ӱ������� or district_list.count <= 1)
            {
                @district_t = @district;
            }
            else
            {
                pk::list<pk::district@> district_sel = pk::district_selector(pk::encode("���� ����"), pk::encode("������ �����ϼ���"), district_list, 1, 1); 
                if (district_sel.count == 0) return false;
                @district_t = district_sel[0];
            }
            pk::person@ totoku_t = pk::get_person(pk::get_totoku_id(district_t));
            if (!pk::is_alive(totoku_t)) return false;
            @base_t = pk::get_building(totoku_t.service);
            if (!pk::is_alive(base_t)) return false;
            
            delay = 1;
            pk::scene(pk::scene_t(goto_base));  // �������� ȭ�� �̵�
            delay = 300;
            
            if (totoku_t.get_id() == kunshu.get_id())
            {
                pk::say(pk::encode(pk::format("\x1b[2x{}����\x1b[0x�� ����� �ϴ��ϰڴ�", district_t.no)), kunshu);
                pk::play_voice(0x3E, kunshu);
            }
            else
            {
                string kunshu_name = pk::decode(pk::get_name(kunshu));
                pk::say(pk::encode(pk::format("\x1b[1x{}\x1b[0x��, \x1b[2x{}����\x1b[0x�� �����!!", kunshu_name, district_t.no)), totoku_t);
                pk::play_voice(0x3C, totoku_t);
            }
        
            return true;
        }
        
        
        
        
        //---------------------------------------------------------------------------------------
        // ���ܸ�� �ʱ�ȭ�� ����Ʈ ������Ʈ �Լ�
        //---------------------------------------------------------------------------------------
        
        // �������� �ʱ�ȭ
        void get_weapon_expense()
        {
            weapon_siege0  = (pk::has_tech(building, �ⱳ_�������))? ����_��� : ����_����;
            weapon_siege1  = (pk::has_tech(building, �ⱳ_��������))? ����_���� : ����_����;
            weapon_warship = (pk::has_tech(building, �ⱳ_��������))? ����_���� : ����_����;
            
            for (int id = 0; id < ����_��; id++)
            {
                if (id != ����_�� and id != ����_�ְ�)
                    weapon_cost[id] = pk::get_equipment(id).gold_cost;
            }
            
            // �ü��� ���� ��� ���� �˻�
            int cost = 0;
            cost = pk::max(weapon_cost[����_â], weapon_cost[����_��], weapon_cost[����_��]);
            if      (cost == weapon_cost[����_â]) weapon_cost_max[0] = ����_â;
            else if (cost == weapon_cost[����_��]) weapon_cost_max[0] = ����_��;
            else if (cost == weapon_cost[����_��]) weapon_cost_max[0] = ����_��;
            
            cost = pk::max(weapon_cost[weapon_siege0], weapon_cost[weapon_siege1]);
            if      (cost == weapon_cost[weapon_siege0]) weapon_cost_max[2] = weapon_siege0;
            else if (cost == weapon_cost[weapon_siege1]) weapon_cost_max[2] = weapon_siege1;
            
            weapon_cost_max[1] = ����_����;
            weapon_cost_max[3] = weapon_warship;
           
        }
        
        // ������ ���� ���� ����ID �˻�
        void get_min_amount_weapon(pk::building@ base)
        {
            int amount = 0;
            amount = pk::min(int(pk::get_weapon_amount(base, ����_â)), int(pk::get_weapon_amount(base, ����_��)), int(pk::get_weapon_amount(base, ����_��)));
            if      (amount == int(pk::get_weapon_amount(base, ����_â))) weapon_outfit[0] = ����_â;
            else if (amount == int(pk::get_weapon_amount(base, ����_��))) weapon_outfit[0] = ����_��;
            else if (amount == int(pk::get_weapon_amount(base, ����_��))) weapon_outfit[0] = ����_��;
            
            amount = pk::min(int(pk::get_weapon_amount(base, weapon_siege0)), int(pk::get_weapon_amount(base, weapon_siege1)));
            if      (amount == int(pk::get_weapon_amount(base, weapon_siege0))) weapon_outfit[2] = weapon_siege0;
            else if (amount == int(pk::get_weapon_amount(base, weapon_siege1))) weapon_outfit[2] = weapon_siege1;
            
            weapon_outfit[1] = ����_����;
            weapon_outfit[3] = weapon_warship;
        }
        
        
        // ������ �������� ���� üũ
        void get_cmd_available()
        {
            pk::building@ base = @building;
            arr_available[1] = func_base_drafts(base, false); // ¡�����ɿ���
            arr_available[2] = func_base_patrol(base, false); // �������ɿ���
            arr_available[3] = func_base_drills(base, false); // �Ʒð��ɿ���
            
            // ���డ�� ���� ����
            arr_available[0] = (arr_available[1] or arr_available[2] or arr_available[3]);  
            
            // ���డ���� ����
            cmd_names = "";
            if (arr_available[1]) cmd_names += ((cmd_names == "")? "" : ",") + "¡��";
            if (arr_available[2]) cmd_names += ((cmd_names == "")? "" : ",") + "����";
            if (arr_available[3]) cmd_names += ((cmd_names == "")? "" : ",") + "�Ʒ�";
        }
        
        
        // ¡��/����/�Ʒ� ������ ���� �� ���� ����Ʈ
        void get_base_available()
        {
            // ����Ʈ �ʱ�ȭ
            list_drafts.clear();
            list_patrol.clear();
            list_drills.clear();
            
            list_outfit0.clear();
            list_outfit1.clear();
            list_outfit2.clear();
            list_outfit3.clear();
            
            list_district_base.clear();
            list_force_base.clear();
            list_enemy_base.clear();
            
            // ���� ���� ����Ʈ���� ���� Ȯ��
            for (int base_id = 0; base_id < �ǹ�_������; base_id++)
            {
                pk::building@ base = pk::get_building(base_id);
                if (district.get_id() == base.get_district_id())
                {
                    // ���ܳ���
                    if (func_base_drafts(base, false) and !list_drafts.contains(base))  list_drafts.add(base);
                    if (func_base_patrol(base, false) and !list_patrol.contains(base))  list_patrol.add(base);
                    if (func_base_drills(base, false) and !list_drills.contains(base))  list_drills.add(base);
                    
                    // ���ܻ���
                    get_min_amount_weapon(base);
                    if (check_outfit_cost(base, weapon_cost_max[0]) and func_base_outfit(base, weapon_outfit[0], false) and !list_outfit0.contains(base))  list_outfit0.add(base);
                    if (check_outfit_cost(base, weapon_cost_max[1]) and func_base_outfit(base, weapon_outfit[1], false) and !list_outfit1.contains(base))  list_outfit1.add(base);
                    if (check_outfit_cost(base, weapon_cost_max[2]) and func_base_outfit(base, weapon_outfit[2], false) and !list_outfit2.contains(base))  list_outfit2.add(base);
                    if (check_outfit_cost(base, weapon_cost_max[3]) and func_base_outfit(base, weapon_outfit[3], false) and !list_outfit3.contains(base))  list_outfit3.add(base);
                    
                    // ���ܰ���
                    if (func_unit_march(base, null, false) and !list_district_base.contains(base)) list_district_base.add(base);
                }
            }
            
            for (int target_id = 0; target_id < �ǹ�_������; target_id++)
            {
                pk::building@ target = pk::get_building(target_id);
                if (building.get_force_id() == target.get_force_id() and !list_force_base.contains(target))
                    list_force_base.add(target);
            }
            
            for (int target_id = 0; target_id < �ǹ�_������; target_id++)
            {
                pk::building@ target = pk::get_building(target_id);
                if (pk::is_enemy(building, target))
                {
                    pk::array<pk::building@> arr_force_base = pk::list_to_array(list_force_base);
                    for (int i = 0; i < int(arr_force_base.length); i++)
                    {
                        pk::building@ base = arr_force_base[i];
                        if (pk::is_neighbor_base(base.get_id(), target.get_id()) and !list_enemy_base.contains(target))
                            list_enemy_base.add(target);
                    }
                }
            }
            
        }
        
        
        //---------------------------------------------------------------------------------------
        // �������� �޴�
        //---------------------------------------------------------------------------------------
        
		string getText_��������()
		{
            return pk::encode("��������");
		}

		string getDesc_��������()
		{
            if (!arr_available[0]) 
                return pk::encode("���డ���� ���ܸ���� �����ϴ�");
            
            return pk::encode(pk::format("\x1b[1x{}\x1b[0x���� \x1b[2x{}\x1b[0x ���ܸ���� �����մϴ�.", pk::decode(pk::get_name(building)), cmd_names));
		}

		bool isEnabled_��������()
		{
            if (!arr_available[0]) return false;
            if (building.get_id() >= �ǹ�_������) return false;
			return true;
		}
        
        bool handler_��������()
        {
            pk::building@ base = @building;
            
            // ���ܸ�� ���� Ȯ�� �޽���
            string base_name = pk::decode(pk::get_name(base));
            bool confirm = pk::yes_no(pk::encode(pk::format("\x1b[1x{}\x1b[0x���� \x1b[2x{}\x1b[0x�� �����ұ��?", base_name, cmd_names)));
            if (!confirm) return false; // ��� ����
            
            // ���� ���� ���� ����
            pk::array<bool> arr_done(4, false);
            arr_done[1] = func_base_drafts(base, true);
            arr_done[2] = func_base_patrol(base, true);
            arr_done[3] = func_base_drills(base, true);
            
            // ���� �Ϸ��� ������
            cmd_names = "";
            if (arr_done[1]) cmd_names += ((cmd_names == "")? "" : ",") + "¡��";
            if (arr_done[2]) cmd_names += ((cmd_names == "")? "" : ",") + "����";
            if (arr_done[3]) cmd_names += ((cmd_names == "")? "" : ",") + "�Ʒ�";
            
            // ���� ���� ��� �޽��� �Լ� ȣ��
            message_base_cmd(base, cmd_names);

            return true;
        }
        
        
        //---------------------------------------------------------------------------------------
        // ���� ���� �߰� �޴�
        //---------------------------------------------------------------------------------------
        
		string getText_���ܳ���()
		{
			return pk::encode("���ܳ���");
		}

		string getDesc_���ܳ���()
		{
            if (list_drafts.count == 0 and list_patrol.count == 0 and list_drills.count == 0)
                return pk::encode("���డ���� ���ð� �����ϴ�");
            
            return pk::encode("���� ���� �޴��� Ȯ��/����մϴ�");
		}
        
		bool isEnabled_���ܳ���()
		{ 
            if (list_drafts.count == 0 and list_patrol.count == 0 and list_drills.count == 0) 
                return false;
            if (building.get_id() >= �ǹ�_������) return false;
			return true;
		}
        
        bool isVisible_���ܳ���()
        {
            if (menu_extend != menu_govern) return false;
            return true;
        }
        
        bool handler_���ܳ���()
        {
            menu_extend = (menu_extend == menu_govern)? -1 : menu_govern;
            
            return false;
        }
        
        
        //---------------------------------------------------------------------------------------
        // ����¡�� �޴�
        //---------------------------------------------------------------------------------------
        
		string getText_����¡��()
		{
			return pk::encode("����¡��");
		}

		string getDesc_����¡��()
		{
            if (list_drafts.count == 0) 
                return pk::encode("���డ���� ���ð� �����ϴ�");
            
            return pk::encode("���� �� ���õ��� ¡���� �����մϴ�");
		}

		bool isEnabled_����¡��()
		{ 
            if (list_drafts.count == 0) return false;
            
            if (building.get_id() >= �ǹ�_������) return false;
			return true;
		}
        
        bool handler_����¡��()
        {
            // ���డ���� �ִ� ���� ��
            int max = int(int(district.ap) / ap_drafts);
            if (max < 1) return false;
            
            // ���� ����
            pk::list<pk::building@> list_base_sel;
            list_base_sel = pk::building_selector(pk::encode("¡�� ���� ����"), 
                                                  pk::encode(pk::format("¡���� ������ ���ø� �����ϼ���. (�ִ� {}�� ���� ����)", pk::min(max, list_drafts.count) )), 
                                                  list_drafts, 1, max, list_base_sel);
            if (list_base_sel.count == 0) return false; // ��� ����
            
            // ¡�� ����
            pk::array<pk::building@> arr_base_cmd;
            pk::array<pk::building@> arr_base_sel = pk::list_to_array(list_base_sel);
            for (int i = 0; i < int(arr_base_sel.length); i++)
            {
                pk::building@ base = arr_base_sel[i];
                
                // ������ ���࿩�� Ȯ��
                bool cmd_confirm = false;
                if (!���ܸ��_���ý���Ȯ��) cmd_confirm = true;
                else cmd_confirm = get_cmd_confirm(base, "¡��");
                
                // ���� ¡�� ���� �Լ� ȣ��
                if (cmd_confirm)
                {
                    bool action_done = func_base_drafts(base, true);
                    if (action_done) 
                        arr_base_cmd.insertLast(base);
                }
            }
            
            // ���� ���� ��� �޽��� �Լ� ȣ��
            message_district_cmd(arr_base_cmd, "¡��");
            
            return true;
        }
        
        
        //---------------------------------------------------------------------------------------
        // ���ܼ��� �޴�
        //---------------------------------------------------------------------------------------
        
		string getText_���ܼ���()
		{
			return pk::encode("���ܼ���");
		}

		string getDesc_���ܼ���()
		{
            if (list_patrol.count == 0) 
                return pk::encode("���డ���� ���ð� �����ϴ�");
            
            return pk::encode("���� �� ���õ��� ������ �����մϴ�");
		}

		bool isEnabled_���ܼ���()
		{ 
            if (list_patrol.count == 0) return false;
            
            if (building.get_id() >= �ǹ�_������) return false;
			return true;
		}

        bool handler_���ܼ���()
        {
            // ���డ���� �ִ� ���� ��
            int max = int(int(district.ap) / ap_patrol);
            if (max < 1) return false;
            
            // ���� ����
            pk::list<pk::building@> list_base_sel;
            list_base_sel = pk::building_selector(pk::encode("���� ���� ����"), 
                                                  pk::encode(pk::format("������ ������ ���ø� �����ϼ���. (�ִ� {}�� ���� ����)", pk::min(max, list_patrol.count) )), 
                                                  list_patrol, 1, max, list_base_sel);
            if (list_base_sel.count == 0) return false; // ��� ����
            
            // ���� ����
            pk::array<pk::building@> arr_base_cmd;
            pk::array<pk::building@> arr_base_sel = pk::list_to_array(list_base_sel);
            for (int i = 0; i < int(arr_base_sel.length); i++)
            {
                pk::building@ base = arr_base_sel[i];
                
                // ������ ���࿩�� Ȯ��
                bool cmd_confirm = false;
                if (!���ܸ��_���ý���Ȯ��) cmd_confirm = true;
                else cmd_confirm = get_cmd_confirm(base, "����");
                
                // ���� ���� ���� �Լ� ȣ��
                if (cmd_confirm)
                {
                    bool action_done = func_base_patrol(base, true);
                    if (action_done) 
                        arr_base_cmd.insertLast(base);
                }
            }
            
            // ���� ���� ��� �޽��� �Լ� ȣ��
            message_district_cmd(arr_base_cmd, "����");
            
            return true;
        }
        
        
        //---------------------------------------------------------------------------------------
        // �����Ʒ� �޴�
        //---------------------------------------------------------------------------------------
        
		string getText_�����Ʒ�()
		{
			return pk::encode("�����Ʒ�");
		}

		string getDesc_�����Ʒ�()
		{
            if (list_drills.count == 0) 
                return pk::encode("���డ���� ������ �����ϴ�");
            
            return pk::encode("���� �� �������� �Ʒ��� �����մϴ�");
		}

		bool isEnabled_�����Ʒ�()
		{ 
            if (list_drills.count == 0) return false;
            
            if (building.get_id() >= �ǹ�_������) return false;
			return true;
		}
        
        bool handler_�����Ʒ�()
        {
            // ���డ���� �ִ� ���� ��
            int max = int(int(district.ap) / ap_drills);
            if (max < 1) return false;
            
            // ���� ����
            pk::list<pk::building@> list_base_sel;
            list_base_sel = pk::building_selector(pk::encode("�Ʒ� ���� ����"), 
                                                  pk::encode(pk::format("�Ʒ��� ������ ������ �����ϼ���. (�ִ� {}�� ���� ����)", pk::min(max, list_drills.count) )), 
                                                  list_drills, 1, max, list_base_sel);
            if (list_base_sel.count == 0) return false; // ��� ����
            
            // �Ʒ� ����
            pk::array<pk::building@> arr_base_cmd;
            pk::array<pk::building@> arr_base_sel = pk::list_to_array(list_base_sel);
            for (int i = 0; i < int(arr_base_sel.length); i++)
            {
                pk::building@ base = arr_base_sel[i];
                
                // ������ ���࿩�� Ȯ��
                bool cmd_confirm = false;
                if (!���ܸ��_���ý���Ȯ��) cmd_confirm = true;
                else cmd_confirm = get_cmd_confirm(base, "�Ʒ�");
                
                // ���� �Ʒ� ���� �Լ� ȣ��
                if (cmd_confirm)
                {
                    bool action_done = func_base_drills(base, true);
                    if (action_done)
                        arr_base_cmd.insertLast(base);
                }
            }
            
            // ���� ���� ��� �޽��� �Լ� ȣ��
            message_district_cmd(arr_base_cmd, "�Ʒ�");
            
            return true;
        }
        
        
        
        //---------------------------------------------------------------------------------------
        // ��� ó�� �Լ�
        //---------------------------------------------------------------------------------------
        
        // ���� Ȯ�� �� �������� ȭ�� �̵�
        pk::building@ base_t;
        void goto_base()
        {
            pk::point pos = base_t.pos;
            for (int i = 0; i < 2; i++)
            {
                pk::point pos_t;
                pos_t.x = pos.x + 1;
                pos_t.y = pos.y;
                if (pk::is_valid_pos(pos_t))
                    pos.x = pos.x + 1;
            }
            pk::wait(delay);
            pk::move_screen(pos, 1);
        }
        
        // ������ ȭ���̵� �� ���࿩�� ��ȯ
        bool get_cmd_confirm(pk::building@ base, string cmd_name)
        {
            @base_t = @base;
            pk::scene(pk::scene_t(goto_base));  // �������� ȭ�� �̵�
            
            // ������ ���࿩�� Ȯ��
            string base_name = pk::decode(pk::get_name(base));
            bool cmd_confirm = pk::yes_no(pk::encode(pk::format("\x1b[1x{}\x1b[0x���� \x1b[2x{}\x1b[0x�� �����ұ��?", base_name, cmd_name))); 
        
            return cmd_confirm;
        }
        
        // ���� ���� ��� �޽��� �Լ� : ���ܳ���
        void message_district_cmd(pk::array<pk::building@> arr_base_sel, string cmd_name)
        {
            // ���� ���� ����
            if (int(arr_base_sel.length) == 0) 
            {
                if (kunshu.get_id() == totoku.get_id())
                    pk::message_box(pk::encode("����� ������ ������ ����"), totoku);
                else
                    pk::message_box(pk::encode("����� ������ ������ �����ϴ�"), totoku);
                
                return; // ����
            }
            
            string base_name = pk::decode(pk::get_name(arr_base_sel[0]));
            string base_names;
            if (int(arr_base_sel.length) == 1) base_names = base_name;
            else base_names = pk::format("{} �� {}�� ����", base_name, (int(arr_base_sel.length)-1) );
            
            if (kunshu.get_id() == totoku.get_id())
                pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x���� \x1b[2x{}\x1b[0x�� �����Ͽ���", base_names, cmd_name)), totoku);
            else
                pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x���� \x1b[2x{}\x1b[0x�� �����Ͽ����ϴ�", base_names, cmd_name)), totoku);
        }
        
        // ���� ���� ��� �޽��� �Լ� : ��������
        void message_base_cmd(pk::building@ base, string cmd_name)
        {
            // ���� ���� ����
            if (!pk::is_alive(base)) 
            {
                if (kunshu.get_id() == totoku.get_id())
                    pk::message_box(pk::encode("���డ���� ����� ����"), totoku);
                else
                    pk::message_box(pk::encode("���డ���� ����� �����ϴ�"), totoku);
                
                return; // ����
            }
            
            string base_name = pk::decode(pk::get_name(base));
            
            if (kunshu.get_id() == totoku.get_id())
                pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x���� \x1b[2x{}\x1b[0x�� �����Ͽ���", base_name, cmd_name)), totoku);
            else
                pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x���� \x1b[2x{}\x1b[0x�� �����Ͽ����ϴ�", base_name, cmd_name)), totoku);
        }
        
        
        //---------------------------------------------------------------------------------------
        
        // ���� ¡�� ���� �Լ�
        bool func_base_drafts(pk::building@ base, bool do_cmd = true)
        {
            int base_id = base.get_id();
            if (base_id < �ǹ�_���ý��� or base_id >= �ǹ�_���ó�) return false; // ���ð� �ƴϸ� ����
            
            // ���డ�� ����� Ȯ��
            bool enough_men = (pk::get_idle_person_list(base).count > 0);
            if (!enough_men) return false;    // ���๫�� ������ ����
            
            // ¡�����ɿ��� Ȯ��
            pk::city@ city = pk::building_to_city(base);
            bool enough_barrack = (int(city.barracks_counter) > 0);    
            bool enough_order = (int(city.public_order) >= ref_order_drafts);
            bool need_troops = (int(pk::get_troops(base)) < int(ref_troops_ratio * float(pk::get_max_troops(base))));
            
            // ¡�� ������ �������� Ȯ��
            if (int(district.ap) >= ap_drafts and enough_men and city.gold >= 300 and enough_barrack and enough_order and need_troops)
            {
                if (do_cmd) // ��� ����
                {
                    // ��� ���� ����
                    int stat  = int(pk::core["¡��.�ɷ�"]);
                    int skill = int(pk::core["¡��.Ư��"]);
                    pk::array<pk::person@> actors = get_cmd_actors(base, stat, skill);
                    
                    // ��� ����
                    pk::recruit_cmd_info cmd_draft;
                    @cmd_draft.base = base;
                    for(int i = 0; i < int(actors.length); i++)
                    {
                        @cmd_draft.actors[i] = actors[i];
                    }
                    // ��� ����
                    pk::command(cmd_draft);
                }
                return true;
            }
            return false;
        }        
        
        //---------------------------------------------------------------------------------------
        
        // ���� ���� ���� �Լ�
        bool func_base_patrol(pk::building@ base, bool do_cmd = true)
        {
            int base_id = base.get_id();
            if (base_id < �ǹ�_���ý��� or base_id >= �ǹ�_���ó�) return false; // ���ð� �ƴϸ� ����
            
            // ���డ�� ����� Ȯ��
            bool enough_men = (pk::get_idle_person_list(base).count > 0);  
            if (!enough_men) return false;    // ���๫�� ������ ����
            
            // �������ɿ��� Ȯ��
            pk::city@ city = pk::building_to_city(base);
            bool need_patrol = (int(city.public_order) < ref_order_patrol);    
            
            // ���� ������ �������� Ȯ��
            if (int(district.ap) >= ap_patrol and enough_men and city.gold >= 100 and !city.inspections_ended and need_patrol)
            {
                if (do_cmd) // ��� ����
                {
                    int stat  = int(pk::core["����.�ɷ�"]);
                    pk::array<pk::person@> actors = get_cmd_actors(base, stat, -1);
                    
                    // ��� ����
                    pk::inspections_cmd_info cmd_patrol;
                    @cmd_patrol.base = base;
                    for(int i = 0; i < int(actors.length); i++)
                    {
                        @cmd_patrol.actors[i] = actors[i];
                    }
                    // ��� ����
                    pk::command(cmd_patrol);
                }
                return true;
            }              
            return false;            
        }        
        
        //---------------------------------------------------------------------------------------
        
        // ���� �Ʒ� ���� �Լ�
        bool func_base_drills(pk::building@ base, bool do_cmd = true)
        {
            int base_id = base.get_id();
            if (base_id < 0 or base_id >= �ǹ�_������) return false; // ������ �ƴϸ� ����
            
            // ���డ�� ����� Ȯ��
            bool enough_men = (pk::get_idle_person_list(base).count > 0);  
            if (!enough_men) return false;    // ���๫�� ������ ����
            
            // ���� ���� Ȯ��
            bool enough_troops = (pk::get_troops(base) >= ref_min_troops);    
            // �Ʒ� �Ϸ� Ȯ��
            bool drills_ended = false;      
            if (�ǹ�_���ý��� <= base_id and base_id < �ǹ�_���ó�)
                drills_ended = pk::building_to_city(base).drills_ended;
            if (�ǹ�_�������� <= base_id and base_id < �ǹ�_������)
                drills_ended = pk::building_to_gate(base).drills_ended;
            if (�ǹ�_�ױ����� <= base_id and base_id < �ǹ�_�ױ���)
                drills_ended = pk::building_to_port(base).drills_ended;
            
            // �Ʒ��ʿ俩�� Ȯ��
           bool need_drill = (pk::get_energy(base) < ref_energy);
                    
            // �Ʒ� ������ �������� Ȯ��
            if (int(district.ap) >= get_ap_cmd(base, ap_drills, �ü�_�����) and enough_men and enough_troops and !drills_ended and need_drill)
            {
                if (do_cmd) // ��� ����
                {
                    int stat  = int(pk::core["�Ʒ�.�ɷ�"]);
                    pk::array<pk::person@> actors = get_cmd_actors(base, stat, -1);
                    
                    // ��� ����
                    pk::drill_cmd_info cmd_drill;
                    @cmd_drill.base = base;
                    for(int i = 0; i < int(actors.length); i++)
                    {
                        @cmd_drill.actors[i] = actors[i];
                    }
                    // ��� ����
                    pk::command(cmd_drill);  
                }
                return true;
            }  
            return false;
        }        
        
        //---------------------------------------------------------------------------------------
        
        // ���� ���� ����Ʈ ���� �Լ�
        int cmd_stat;
        int cmd_skill;
        pk::array<pk::person@> get_cmd_actors(pk::building@ base, int stat, int skill)
        {
            cmd_stat  = stat;
            cmd_skill = skill;
            pk::array<pk::person@> actors(3, null);
            
            // ���డ�� ���� Ȯ��
            pk::list<pk::person@> list_idle_person = pk::get_idle_person_list(base);
            if (list_idle_person.count == 0) return actors;
            
            // �ɷ� ���� ������ ����, Ư�� ���
            list_idle_person.sort(function(a, b)
            {
                if (main.cmd_skill >= 0)    // Ư�� ���� ��
                {
                    bool a_skill = pk::has_skill(a, main.cmd_skill);
                    bool b_skill = pk::has_skill(b, main.cmd_skill);
                    if ( a_skill and !b_skill) return true;
                    if (!a_skill and  b_skill) return false;

                    return a.stat[main.cmd_stat] > b.stat[main.cmd_stat];
                }                    
                
                return a.stat[main.cmd_stat] > b.stat[main.cmd_stat];
            } );
            
            // �ִ� 3�����
            pk::array<pk::person@> arr_idle_person = pk::list_to_array(list_idle_person);
            int min_actors = pk::min(3, pk::max(1, int(arr_idle_person.length)/2));
            int sum_stat = 0;
            for (int i = 0; i < min_actors; i++)
            {
                @actors[i] = arr_idle_person[i];
            }
            
            return actors;
        }
        
        //---------------------------------------------------------------------------------------
        
        // �����ü��� ������ ���� ���� �ൿ�� ��� �Լ�
        int get_ap_cmd(pk::building@ base, int ref_ap, int facility_id)
        {
            pk::city@ city = pk::building_to_city(base);
            if (!pk::is_alive(city)) return ref_ap;
            
            int ap_cmd = ref_ap;
            if (pk::has_facility(city, facility_id))
                ap_cmd = ref_ap / 2;
            
            return ap_cmd;
        }
        
        
        
        
        //---------------------------------------------------------------------------------------
        // ���ܻ��� �߰� �޴�
        //---------------------------------------------------------------------------------------
        
		string getText_���ܻ���()
		{
			return pk::encode("���ܻ���");
		}

		string getDesc_���ܻ���()
		{
            if (list_outfit0.count == 0 and list_outfit1.count == 0 and list_outfit2.count == 0 and list_outfit3.count == 0) 
                return pk::encode("���డ���� ���ð� �����ϴ�");
            
            return pk::encode("���� ���� �޴��� Ȯ��/����մϴ�");
		}

		bool isEnabled_���ܻ���()
		{ 
            if (list_outfit0.count == 0 and list_outfit1.count == 0 and list_outfit2.count == 0 and list_outfit3.count == 0)
                return false;
            
            if (building.get_id() >= �ǹ�_������) return false;
			return true;
		}

        bool isVisible_���ܻ���()
        {
            if (menu_extend != menu_outfit) return false;
            return true;
        }
        
        
        bool handler_���ܻ���()
        {
            menu_extend = (menu_extend == menu_outfit)? -1 : menu_outfit;
            
            return false;
        }
        
        
        //---------------------------------------------------------------------------------------
        // ���ܻ��� ���� �޴�
        //---------------------------------------------------------------------------------------
        
        
		string getText_���ܴܾ�()
		{
			return pk::encode("���ܴܾ�");
		}

		string getDesc_���ܴܾ�()
		{
            if (list_outfit0.count == 0) 
                return pk::encode("���డ���� ���ð� �����ϴ�");
            
            return pk::encode("���� �� ���õ��� ���尣 ���긦 �����մϴ�");
		}

		bool isEnabled_���ܴܾ�()
		{ 
            if (list_outfit0.count == 0) return false;
            
            if (building.get_id() >= �ǹ�_������) return false;
			return true;
		}
        
        bool handler_���ܴܾ�()
        {
            bool handler_result = sub_handler_���ܻ���(0, list_outfit0);
            return handler_result;
        }
        
        //---------------------------------------------------------------------------------------
        
        string getText_���ܱ���()
		{
			return pk::encode("���ܱ���");
		}

		string getDesc_���ܱ���()
		{
            if (list_outfit1.count == 0) 
                return pk::encode("���డ���� ���ð� �����ϴ�");
            
            return pk::encode("���� �� ���õ��� ������ ���긦 �����մϴ�");
		}

		bool isEnabled_���ܱ���()
		{ 
            if (list_outfit1.count == 0) return false;
            
            if (building.get_id() >= �ǹ�_������) return false;
			return true;
		}
        
        bool handler_���ܱ���()
        {
            bool handler_result = sub_handler_���ܻ���(1, list_outfit1);
            return handler_result;
        }
        
        //---------------------------------------------------------------------------------------
        
        string getText_���ܰ���()
		{
			return pk::encode("���ܰ���");
		}

		string getDesc_���ܰ���()
		{
            if (list_outfit2.count == 0) 
                return pk::encode("���డ���� ���ð� �����ϴ�");
            
            return pk::encode("���� �� ���õ��� ���� ���긦 �����մϴ�");
		}

		bool isEnabled_���ܰ���()
		{ 
            if (list_outfit2.count == 0) return false;
            
            if (building.get_id() >= �ǹ�_������) return false;
			return true;
		}
        
        bool handler_���ܰ���()
        {
            bool handler_result = sub_handler_���ܻ���(2, list_outfit2);
            return handler_result;
        }
        
        //---------------------------------------------------------------------------------------
        
        string getText_��������()
		{
			return pk::encode("��������");
		}

		string getDesc_��������()
		{
            if (list_outfit3.count == 0) 
                return pk::encode("���డ���� ���ð� �����ϴ�");
            
            return pk::encode("���� �� ���õ��� ���긦 �����մϴ�");
		}

		bool isEnabled_��������()
		{ 
            if (list_outfit3.count == 0) return false;
            
            if (building.get_id() >= �ǹ�_������) return false;
			return true;
		}
        
        bool handler_��������()
        {
            bool handler_result = sub_handler_���ܻ���(3, list_outfit3);
            return handler_result;
        }
        
       //---------------------------------------------------------------------------------------
       
        bool sub_handler_���ܻ���(int facility_select, pk::list<pk::building@> list_outfit_sel)
        {
            // ���� Ÿ�Կ� ���� ���갡�� ��������Ʈ
            if (list_outfit_sel.count == 0) return false; // ��� ����
            
            // ���డ���� �ִ� ���� ��
            int max = int(int(district.ap) / ap_outfit);
            if (max < 1) return false;
            
            // ���� ����
            pk::list<pk::building@> list_base_sel;
            list_base_sel = pk::building_selector(pk::encode("���� ���� ����"), 
                                                  pk::encode(pk::format("������ ������ ���ø� �����ϼ���. (�ִ� {}�� ���� ����)", pk::min(max, list_outfit_sel.count) )), 
                                                  list_outfit_sel, 1, max, list_base_sel);
            if (list_base_sel.count == 0) return false; // ��� ����
            
            // ���� ���� ���� (���� �޴��� �ڵ鷯���� �Ű������� ����)
            int weapon_id = get_outfit_weapon_id(facility_select);    // ����� ���� Ȯ�� �޽���
            
            if (weapon_id <= ����_�� or weapon_id == ����_�ְ� or weapon_id >= ����_��) return false;
            string weapon_name = arr_weapon_name[weapon_id];
            
            // ���� ����
            pk::array<pk::building@> arr_base_cmd;
            pk::array<pk::building@> arr_base_sel = pk::list_to_array(list_base_sel);
            for (int i = 0; i < int(arr_base_sel.length); i++)
            {
                pk::building@ base = arr_base_sel[i];
                
                // ������ ���࿩�� Ȯ��
                bool cmd_confirm = false;
                if (!���ܸ��_���ý���Ȯ��) cmd_confirm = true;
                else cmd_confirm = get_cmd_confirm(base, pk::format("{} ����", weapon_name));
                
                // ���� ���� ���� �Լ� ȣ��
                if (cmd_confirm)
                {
                    bool action_done = func_base_outfit(base, weapon_id, true);
                    if (action_done) 
                        arr_base_cmd.insertLast(base);
                }
            }
            
            // ���� ���� ��� �޽��� �Լ� ȣ��
            message_district_cmd(arr_base_cmd, pk::format("{} ����", weapon_name));
            
            
            return true;
        }
        
        
        //---------------------------------------------------------------------------------------
        
        // ���� ���� ���� �Լ�
        bool func_base_outfit(pk::building@ base, int weapon_id, bool do_cmd = true)
        {
            int base_id = base.get_id();
            if (base_id < �ǹ�_���ý��� or base_id >= �ǹ�_���ó�) return false; // ���ð� �ƴϸ� ����
            
            // ���డ�� ����� Ȯ��
            bool enough_men = (pk::get_idle_person_list(base).count > 0);
            if (!enough_men) return false;    // ���๫�� ������ ����
            
            // �����ʿ俩�� Ȯ��
            pk::city@ city = pk::building_to_city(base);
            if (weapon_id <= ����_�� or weapon_id == ����_�ְ� or weapon_id >= ����_��) return false;
            bool need_weapon = (int(pk::get_weapon_amount(base, weapon_id)) < int(ref_weapon_ratio * float(pk::get_max_weapon_amount(base, weapon_id))));
            
            // ����Ÿ�Ժ� ����ü� ī��Ʈ Ȯ��
            int outfit_type = get_outfit_type(weapon_id);
            bool enough_outfit = false;
            switch(outfit_type)
            {
                case 0: enough_outfit = (int(city.blacksmith_counter) > 0);  break;
                case 1: enough_outfit = (int(city.stable_counter) > 0);      break;
                case 2: enough_outfit = (int(city.workshop_counter) > 0);    break;
                case 3: enough_outfit = (int(city.shipyard_counter) > 0);    break;
            }
            
            pk::equipment@ eqp = pk::get_equipment(weapon_id);
            
            // ���� ������ �������� Ȯ��
            if (int(district.ap) >= ap_outfit and enough_men and int(city.gold) >= int(eqp.gold_cost) and enough_outfit and need_weapon)
            {
                if (do_cmd) // ��� ����
                {
                    // ��� ���� ����
                    int stat = int(pk::core["�������.�ɷ�"]);
                    int skill = -1;
                    switch(outfit_type)
                    {
                        case  0: skill = int(pk::core["�������.���尣Ư��"]);  break;
                        case  1: skill = int(pk::core["�������.������Ư��"]);  break;
                        case  2: skill = int(pk::core["�������.����Ư��"]);  break;
                        case  3: skill = int(pk::core["�������.����Ư��"]);  break;
                        default: skill = -1; break;
                    }
                    pk::array<pk::person@> actors = get_cmd_actors(base, stat, skill);
                    
                    // ��� ����
                    pk::outfit_cmd_info cmd_outfit;
                    @cmd_outfit.base   = base;
                    cmd_outfit.weapon = weapon_id;
                    for(int i = 0; i < int(actors.length); i++)
                    {
                        @cmd_outfit.actors[i] = actors[i];
                    }
                    // ��� ����
                    pk::command(cmd_outfit);
                }
                return true;
            }
            return false;
        }        
        
        //---------------------------------------------------------------------------------------
        
        int get_outfit_weapon_id(int outfit_type)
        {
            int weapon_id = -1;
            
            // �ܾ�
            if (outfit_type == 0)
            {
                int answer = pk::choose({ pk::encode("â"), pk::encode("��"), pk::encode("��"), pk::encode("���") }, 
                                          pk::encode("� ���⸦ �����ϰڽ��ϱ�?"), totoku );
                // ���� ���� ��� ó��
                if      (answer == 0) weapon_id = ����_â;
                else if (answer == 1) weapon_id = ����_��;
                else if (answer == 2) weapon_id = ����_��;
                else return -1;
            }
            
            // ����
            else if (outfit_type == 1)
            {
                weapon_id = ����_����;
            }
            
            // ����
            else if (outfit_type == 2)
            {
                string s0 = arr_weapon_name[weapon_siege0];
                string s1 = arr_weapon_name[weapon_siege1];
                
                int answer = pk::choose({ pk::encode(s0), pk::encode(s1), pk::encode("���") }, 
                                          pk::encode("� ���⸦ �����ϰڽ��ϱ�?"), totoku );
                // ���� ���� ��� ó��
                if      (answer == 0) weapon_id = weapon_siege0;
                else if (answer == 1) weapon_id = weapon_siege1;
                else return -1;
            }
            
            // ����
            else if (outfit_type == 3)
            {
                weapon_id = weapon_warship;
            }
            
            return weapon_id;
        }
        
        //---------------------------------------------------------------------------------------
        
        int get_outfit_type(int weapon_id)
        {
            int outfit_type = -1;
            
            if (weapon_id >= ����_â and weapon_id <= ����_��)         outfit_type = 0;
            else if (weapon_id == ����_����)                          outfit_type = 1;
            else if (weapon_id >= ����_���� and weapon_id <= ����_���) outfit_type = 2;          
            else if (weapon_id >= ����_���� and weapon_id <= ����_����) outfit_type = 3;     

            return outfit_type;
        }
        
        //---------------------------------------------------------------------------------------
        
        bool check_outfit_cost(pk::building@ base, int weapon_id)
        {
            int base_id = base.get_id();
            if (base_id < �ǹ�_���ý��� or base_id >= �ǹ�_���ó�) return false; // ���ð� �ƴϸ� ����
            
            pk::city@ city = pk::building_to_city(base);
            if (weapon_id <= ����_�� or weapon_id == ����_�ְ� or weapon_id >= ����_��) return false;
            
            pk::equipment@ eqp = pk::get_equipment(weapon_id);
            
            return (int(city.gold) >= int(eqp.gold_cost));
        }
        
        
        //---------------------------------------------------------------------------------------
        // ���� ���� �߰� �޴�
        //---------------------------------------------------------------------------------------
        
		string getText_��������()
		{
			return pk::encode("��������");
		}

		string getDesc_��������()
		{
            if (list_district_base.count == 0) 
                return pk::encode("���డ���� ���ð� �����ϴ�");
            
            return pk::encode("���� ���� �޴��� Ȯ��/����մϴ�");
		}
        
		bool isEnabled_��������()
		{ 
            if (list_district_base.count == 0) return false;
            if (building.get_id() >= �ǹ�_������) return false;
			return true;
		}
        
        bool isVisible_��������()
        {
            if (menu_extend != menu_attack) return false;
            return true;
        }
        
        bool handler_��������()
        {
            menu_extend = (menu_extend == menu_attack)? -1 : menu_attack;
            
            return false;
        }
        
        
        
        //---------------------------------------------------------------------------------------
        // ���ܰ��� �޴�
        //---------------------------------------------------------------------------------------
        
        bool isEnabled_���ܰ���()
		{ 
            if (list_district_base.count == 0) return false;
        
            if (building.get_id() >= �ǹ�_������) return false;
			return true;
        }
        
		string getText_���ܰ���()
		{
			return pk::encode("���ܰ���");
		}

		string getDesc_���ܰ���()
		{
            if (list_district_base.count == 0) 
                return pk::encode("���� ������ ������ �����ϴ�");
            
            return pk::encode("������ �� ������ ���� ���� �� ������κ��� �δ븦 �ϰ� ������ŵ�ϴ�");
		}
        
        bool handler_���ܰ���()
        {
            list_src_base.clear();
            list_dst_base.clear();
            
            // ��ǥ �� ����
            list_dst_base = list_enemy_base;
            
            // ��ǥ ���� ����
            pk::list<pk::building@> list_target = pk::building_selector(pk::encode("��ǥ ���� ����"), pk::encode("��ǥ ������ �����մϴ�."), list_dst_base, 1, 1);
            if(list_target.count == 0) return false; // �̼��� �� ��� ����
            pk::building@ target = pk::get_building(list_target[0].get_id());
            
            // ���� ���� ����Ʈ 
            list_src_base = list_district_base;
            
            // ���� ���� ���
            bool handler_result = func_base_march(target);
            
            return handler_result;
        }
        
        //---------------------------------------------------------------------------------------
        
		string getText_���ܿ���()
		{
			return pk::encode("���ܿ���");
		}

		string getDesc_���ܿ���()
		{
            if (list_district_base.count == 0) 
                return pk::encode("���� ������ ������ �����ϴ�");
            
            return pk::encode("������ �Ʊ� ������ ���� ���� �� ������κ��� �δ븦 �ϰ� ������ŵ�ϴ�");
		}
        
        
        bool handler_���ܿ���()
        {
            list_src_base.clear();
            list_dst_base.clear();
            
            // ��ǥ �Ʊ� ����
            list_dst_base = list_force_base;

            // ��ǥ ���� ����
            pk::list<pk::building@> list_target = pk::building_selector(pk::encode("��ǥ ���� ����"), pk::encode("��ǥ ������ �����մϴ�."), list_dst_base, 1, 1);
            if(list_target.count == 0) return false; // �̼��� �� ��� ����
            pk::building@ target = pk::get_building(list_target[0].get_id());
            
            // ���� ���� ����Ʈ ������Ʈ
            pk::array<pk::building@> arr_district_base = pk::list_to_array(list_district_base);
            for (int i = 0; i < int(arr_district_base.length); i++)
            {
               if (target.get_id() != arr_district_base[i].get_id())
                    list_src_base.add(arr_district_base[i]);    // ��ǥ ������ ����
            }
            
            // ���� ���� ���
            bool handler_result = func_base_march(target);
            
            return handler_result;
        }
        
        //---------------------------------------------------------------------------------------
        
        bool func_base_march(pk::building@ target)
        {
            // ���డ���� �ִ� ���� ��
            int max = int(int(district.ap) / ap_march);
            if (max < 1) return false;
            
            // ���� ���� ����
            pk::list<pk::building@> list_base_sel;
            list_base_sel = pk::building_selector(pk::encode("���� ���� ����"), 
                                                  pk::encode(pk::format("������ ������ ������ �����ϼ���. (�ִ� {}�� ���� ����)", pk::min(max, list_src_base.count) )), 
                                                  list_src_base, 1, max, list_base_sel);
            if (list_base_sel.count == 0) return false; // ��� ����
            
            // ���� ����
            pk::array<pk::building@> arr_base_cmd;
            pk::array<pk::building@> arr_base_sel = pk::list_to_array(list_base_sel);
            for (int i = 0; i < int(arr_base_sel.length); i++)
            {
                pk::building@ base = arr_base_sel[i];
                
                // ������ ���࿩�� Ȯ��
                bool cmd_confirm = false;
                if (!���ܸ��_���ý���Ȯ��) cmd_confirm = true;
                else cmd_confirm = get_cmd_confirm(base, "����");
                
                // ���� ���� ���� �Լ� ȣ��
                if (cmd_confirm)
                {
                    bool action_done = func_unit_march(base, pk::get_hex_object(target.pos), true);
                    if (action_done) 
                        arr_base_cmd.insertLast(base);
                }
            }
            
            // ���� ���� ��� �޽��� �Լ� ȣ��
            message_district_cmd(arr_base_cmd, "����");
            
            
            
            return true;
        }
        
        //---------------------------------------------------------------------------------------
        
        bool func_unit_march(pk::building@ base, pk::hex_object@ target, bool do_cmd = true)
        {
            // ��� ������ ������ �ִ��� Ȯ��
            pk::list<pk::person@> person_list = pk::get_idle_person_list(base);
			if (person_list.count == 0) return false;   // ���� ����
            
            if (pk::get_troops(base) < (���ܸ��_�⺴�ּҺ��� + ���ܸ��_�⺴��������)) return false;  // ���� ����
            
            int max = int(int(district.ap) / get_ap_cmd(base, ap_march, �ü�_�����));
            if (max < 1) return false;      // �ൿ�� ����
            
            int weapon_id = ����_��;
            int unit_troops;
            func_weapon_select(base, ���ܸ��_�⺴�ּҺ���, pk::get_troops(base), weapon_id, unit_troops);    // ���� ������ �ּ� ���� ��ȯ
            if (weapon_id == 0) return false;    // ���� ���� �Ǵ� ���� ����
            
            
            if (do_cmd)
            {
                // ���� ����.
                person_list.sort(function(a, b)
                {
                    int cmd_a = pk::get_command(a);
                    int cmd_b = pk::get_command(b);
                    int stat_a = a.stat[����ɷ�_����] + a.stat[����ɷ�_���];
                    int stat_b = a.stat[����ɷ�_����] + b.stat[����ɷ�_���];
                    return ((cmd_a == cmd_b)? (stat_a > stat_b) : (cmd_a > cmd_b)) ;     // ����-�ɷ¼�
                });
                
                // �⺴�� ���� ���� (�ּ�1, �ִ�8)
                pk::list<pk::person@> person_sel = pk::person_selector(pk::encode("�⺴ ���� ����"), pk::encode("�⺴�� ������ �����մϴ�."), person_list, 1, pk::min(8, max, person_list.count));
                if (person_sel.count == 0) return false;
                
                
                for (int id = 0; id < person_sel.count; id++)
                {
                    if (int(district.ap) < get_ap_cmd(base, ap_march, �ü�_�����)) continue;
                    if (pk::get_troops(base) < (���ܸ��_�⺴�ּҺ��� + ���ܸ��_�⺴��������)) continue;

                    // �⺴�� ��� ����
                    pk::person@ member0 = pk::get_person(person_sel[id].get_id());
                    pk::person@ member1 = null;
                    pk::person@ member2 = null;
                    
                    // ���� ������Ʈ
                    func_get_tekisei(member0, member1, member2);
                    
                    // ���� ���� ���� ����
                    int gnd_weapon_id = ����_��;
                    int unit_command = pk::min(pk::get_command(member0), pk::get_troops(base));     // ���ְ��� �ִ뺴�� (���ְ�, ���ú��� �� �ּ�)
                    func_weapon_select(base, ���ܸ��_�⺴�ּҺ���, unit_command, gnd_weapon_id, unit_troops);    // ���� ������ �ּ� ���� ��ȯ
                    if (gnd_weapon_id == 0) return false;    // ���� ���� �Ǵ� ���� ����
                    
                    unit_command = pk::min(���ܸ��_�⺴�ִ뺴��, unit_command, pk::get_weapon_amount(base, gnd_weapon_id));   // �ش� ������ �ִ뺴�� ���� (���ְ��� ����, ���⺸���� �� �ּ�)
                    unit_troops = pk::max(unit_troops, unit_command);
                    int unit_food = pk::min( int(unit_troops * ���ܸ��_�⺴��������), int(pk::get_food(base)) );    // ���� ����
                    
                    // ���� ���� ����
                    int sea_weapon_id = ����_�ְ�;
                    if (arr_tekisei[����_����] == ����_C)
                        sea_weapon_id = ����_�ְ�;
                    else
                    {
                        if      (pk::get_weapon_amount(base, ����_����) > 0) sea_weapon_id = ����_����;
                        else if (pk::get_weapon_amount(base, ����_����) > 0) sea_weapon_id = ����_����;
                    }
                    
                    // �δ� ����
                    pk::march_cmd_info march_cmd;
                    if (pk::is_alive(member0)) march_cmd.member[0] = member0.get_id();
                    if (pk::is_alive(member1)) march_cmd.member[1] = member1.get_id();
                    if (pk::is_alive(member2)) march_cmd.member[2] = member2.get_id();
                    @march_cmd.base  = @base;
                    march_cmd.type   = �δ�����_����;
                    march_cmd.food   = unit_food;
                    march_cmd.gold   = 0;
                    march_cmd.troops = unit_troops;
                    march_cmd.weapon_id[0] = gnd_weapon_id;
                    march_cmd.weapon_id[1] = sea_weapon_id;
                    march_cmd.weapon_amount[0] = unit_troops;
                    march_cmd.weapon_amount[1] = (sea_weapon_id == ����_�ְ�)? 0 : 1;
                    int unit_id = pk::command(march_cmd);
                    pk::unit@ unit = pk::get_unit(unit_id);
                    
                    
                    // �⺴�δ� �̵�
                    pk::set_order(unit, �δ��ӹ�_����, target.get_pos());
                    pk::run_order(unit);
                    
                    // �����Ұ� �� �δ� ���� ���� �� ���� ��ȯ ('19.7.3)
                    pk::building@ base_check = pk::get_building(unit.pos);
                    if (pk::is_alive(base_check) and base_check.get_id() == base.get_id())
                    {
                        pk::kill(unit);
                        pk::add_food(base, unit_food, false);
                        pk::add_gold(base, 0, false);
                        pk::add_troops(base, unit_troops);
                        pk::add_weapon_amount(base, gnd_weapon_id, unit_troops);
                        if (sea_weapon_id != ����_�ְ�) 
                            pk::add_weapon_amount(base, sea_weapon_id, unit_troops);
                        
                        if (pk::is_alive(member0)) member0.action_done = false;
                        if (pk::is_alive(member1)) member1.action_done = false;
                        if (pk::is_alive(member2)) member2.action_done = false;
                    }
                    
                    // �δ� ���� �Ұ��� �ൿ�� ��ȯ
                    if (!pk::is_alive(unit))
                    {
                        district.ap += get_ap_cmd(base, ap_march, �ü�_�����);
                    }
                    // �δ� �ൿ ���� ����
                    else
                    {
                        if (pk::is_in_screen(unit.pos))
                        {
                            string target_name = pk::decode(pk::get_name(target));
                            switch(pk::rand(2))
                            {
                                case 0: pk::play_voice(0x1A, pk::get_person(unit.leader)); break; // ���� : ����_�̵�
                                case 1: pk::play_voice(0x1B, pk::get_person(unit.leader)); break; // ���� : ����_�̵�
                            }
                            switch(pk::rand(4))
                            {
                                case 0: pk::say(pk::encode(pk::format("\x1b[2x{}\x1b[0x�� ���� �⺴�϶�", target_name)), member0, unit); break;
                                case 1: pk::say(pk::encode(pk::format("\x1b[2x{}\x1b[0x���� �����϶�", target_name)), member0, unit); break;
                                case 2: pk::say(pk::encode(pk::format("\x1b[2x{}\x1b[0x���� ���ϰڽ��ϴ�", target_name)), member0, unit); break;
                                case 3: pk::say(pk::encode(pk::format("\x1b[2x{}\x1b[0x�� �����϶�", target_name)), member0, unit); break;
                            }
                        }
                        
                        if (unit.get_id() != -1)
                            unit.action_done = true;
                        if (int(pk::option["San11Option.EnableInfiniteAction"]) != 0)
                            unit.action_done = false;
                    }
                }
            }

			return true;
        }
        
        
        // ���� ���� �Լ�
        void func_weapon_select(pk::building@ building_t, int troops, int troops_max, int &out weapon_sel, int &out troops_sel)
        {
            int weapon_max = 0;
            int best_tekisei = ����_C;
            
            weapon_sel = ����_��;
            troops_sel = 0;
            
            // �⺴���� �̻� ������ ���� �� �ְ� ���� Ȯ��
            for (int id = ����_â; id <= ����_����; id++)
            {
                int tekisei = arr_tekisei[pk::equipment_id_to_heishu(id)];
                int weapon_t = pk::get_weapon_amount(building_t, id);
                if (���ܸ��_�⺴�ּҺ��� <= weapon_t and best_tekisei <= tekisei)
                    best_tekisei = tekisei;
            }
            
            // �ְ� ���� �̻��� ���� �� ���� ���� ���� ���� ����
            for (int id = ����_â; id <= ����_����; id++)
            {
                int tekisei = arr_tekisei[pk::equipment_id_to_heishu(id)];
                int weapon_t = pk::get_weapon_amount(building_t, id);
                if (���ܸ��_�⺴�ּҺ��� <= weapon_t and weapon_max <= weapon_t and best_tekisei <= tekisei)
                {
                    best_tekisei = tekisei;
                    weapon_max = weapon_t;
                    weapon_sel = id;
                    troops_sel = pk::min(troops, weapon_max, troops_max);
                }
            }
            
            if (weapon_sel == 0)
            {
                troops_sel = troops;
            }
        }
        
        void func_get_tekisei(pk::person@ p0, pk::person@ p1, pk::person@ p2)
        {
            for (int i = 0; i < 6; i++)
            {
                if (!pk::is_alive(p0) and !pk::is_alive(p1) and !pk::is_alive(p2))
                    arr_tekisei[i] = ����_C;
                else if (pk::is_alive(p0) and !pk::is_alive(p1) and !pk::is_alive(p2))
                    arr_tekisei[i] = p0.tekisei[i];
                else if (pk::is_alive(p0) and pk::is_alive(p1) and !pk::is_alive(p2))
                    arr_tekisei[i] = pk::max(p0.tekisei[i], p1.tekisei[i]);
                else if (pk::is_alive(p0) and pk::is_alive(p1) and pk::is_alive(p2))
                    arr_tekisei[i] = pk::max(p0.tekisei[i], p1.tekisei[i], p2.tekisei[i]);
            }
        }
        
        
	}

	Main main;
}