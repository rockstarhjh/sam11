/*
// ������: �⸶å��
// UPDATE: '20.10.22    / ��������
*/

namespace �ൿ��_���Ѽ���
{
	//---------------------------------------------------------------------------------------
    // ���� ���� (true = on, false = off)
    const bool �÷��̾�_�����ൿ��_����  = true;   // (�⺻�� false) true �� ���� �� �÷��̾� 1���� �� ���ӱ��� �ൿ�� ����
    const bool ��ǻ�ͼ���_�����ൿ��_���� = true;  // (�⺻�� false) true �� ���� �� ��ǻ�ͼ��� �ൿ�� ����
    
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
        // �ǹ��޴� Ŭ�� �� �ൿ�� 255�� ����
        void init(pk::building@ building)
		{
            if (building.get_id() < �ǹ�_������)
            {
                pk::district@ district = pk::get_district(building.get_district_id());
                
                if ((��ǻ�ͼ���_�����ൿ��_���� and !building.is_player()) or (�÷��̾�_�����ൿ��_���� and building.is_player()))
                    district.ap = 255;
                    
            }
		}
		string getText() { return pk::encode("�����ൿ��"); }
		string getDesc() { return pk::encode("�����ൿ�� ����"); }
		bool isVisible() { return false; }
        bool isEnabled() { return true; }
        bool handler()   { return true; }
        
        //------------------------------------------------------------

        
		// ��ǻ�� �ൿ�� �ִ� : ��� ���� �� �ִ�ġ��..
		void callback_256(pk::ai_context@ context, pk::building@ building, int cmd)
		{
			if ((��ǻ�ͼ���_�����ൿ��_���� and!building.is_player()) or (�÷��̾�_�����ൿ��_���� and building.is_player()))
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