/*
@ ������: �⸶å��
@ UPDATE: '18.11.17  / ��������: ����Ȳ�� õ��
@ UPDATE: '18.11.23  / ���泻��: Ȳ�� �ڵ����� ����, Ȳ�� �� Ȳ�� ���� ���ֿ� ���缭 ���� ����, �����ൿ�Ϸ� �ݿ�
                               ����Ȳ������ �̺�Ʈ �߰�
@ UPDATE: '18.11.25  / ���泻��: ����Ȳ������ �� �������±��� ����, ��� ���� ��¿��� ����
@ UPDATE: '18.12.3   / ���泻��: Ȳ������ �� �޴� �ʱ�ȭ ���� ���� �߰�
@ UPDATE: '20.8.29   / ���泻��: ķ���ο����� ��ũ��Ʈ ��Ȱ��ȭ
*/

namespace ����Ȳ��õ��
{
	//---------------------------------------------------------------------------------------
    
    const bool ����Ȳ��õ��_��� = true;
    const int TP_COST_õ�� = 1000; 	// �ⱳP �ʿ䷮
    const int ACTION_COST_õ�� = 50;
    const int GOLD_COST_õ��  = 5000;
    
	const int KEY = pk::hash("õ��");
    
    //---------------------------------------------------------------------------------------
    
    const bool ����Ȳ������_��� = true;
    const int ����Ȳ������_����ġ��  = 65;    // ����Ȳ�� ���� �̺�Ʈ �߻� ���� ġ��
    const int ����Ȳ������_���ص��ü�  = 1;   // ����Ȳ�� ���� �̺�Ʈ �߻� ���� ���ü�
    const int ����Ȳ������_�߻�Ȯ��  = 100;    // ���ְ� �ѽ�_������ ��� ���� Ȯ�� (�ѽ�_�߽ô� ���� �̹߻�, �ѽ�_���ô� ������ ����)
    
    //---------------------------------------------------------------------------------------
    
	
	class Main
	{
		
		pk::building@ building;
		pk::building@ kunshu_building;
		pk::city@ kunshu_city;
		pk::city@ emperor_city;
		pk::force@ force;
		pk::person@ kunshu;
		pk::person@ emperor; 
		pk::person@ support; 
		pk::person@ reporter; 
        pk::force@ new_force;
        pk::person@ new_kunshu;
        pk::building@ new_building;
		pk::city@ new_city;
        uint16 building_gold;
        bool kunshu_building_check;
        bool emperor_city_check;
        int debate_result;
        
		Main()
		{
            if (����Ȳ��õ��_���)
            {
                pk::menu_item õ��;
                õ��.menu = 105;        // ���ָ޴�
                õ��.init = pk::building_menu_item_init_t(init);
                õ��.is_visible = pk::menu_item_is_visible_t(isVisible_õ��);
                õ��.is_enabled = pk::menu_item_is_enabled_t(isEnabled_õ��);
                õ��.get_text = pk::menu_item_get_text_t(getText_õ��);
                õ��.get_desc = pk::menu_item_get_desc_t(getDesc_õ��);
                õ��.handler = pk::menu_item_handler_t(handler_õ��);
                pk::add_menu_item(õ��);
            }
            
            // �� ���� �̺�Ʈ
            pk::bind(111, pk::trigger111_t(onTurnStart));
            
		}
        
        
        void onTurnStart(pk::force@ force_turn)
        {
            if (����Ȳ������_���)
                event_Emperor_Escape(force_turn);
        }
        
        
        
        //---------------------------------------------------------------------------------------
        
        void init(pk::building@ building_t)
		{
			@building = @building_t;
			@force = pk::get_force(building.get_force_id());
			@kunshu = pk::get_person(pk::get_kunshu_id(building));
            @kunshu_building = pk::get_building(kunshu.service);
			@kunshu_city = pk::building_to_city(kunshu_building);
            building_gold = pk::get_gold(building);
            
            @emperor = pk::get_person(pk::get_scenario().emperor);
            
            if (emperor is null) return;
            else if (emperor.mibun != �ź�_���)
            {
                if (emperor.get_id() == ����_����)
                    @support = pk::get_person(����_Ȳ��);
                else if (emperor.get_id() == ����_����)
                    @support = pk::get_person(����_ȯ��);
                else if (emperor.get_id() == ����_����)
                {
                    switch(pk::rand(2))
                    {
                    case 0: @support = pk::get_person(����_���_�ʻ��); break;
                    case 1: @support = pk::get_person(����_�Ǽ�_�ʻ��); break;
                    }
                }
                
                @emperor_city = pk::building_to_city(pk::hex_object_to_building(pk::get_hex_object(emperor.location)));
                kunshu_building_check = (building.get_id() == kunshu.service);
                emperor_city_check = (emperor_city.get_id() == kunshu.service);
            
                
                // Ȳ�� �� Ȳ�� ���� ���� ���� ('18.11.18)
                support.base_stat[����ɷ�_����] = pk::max(1, kunshu.base_stat[����ɷ�_����] - 15);
                support.update();
                emperor.base_stat[����ɷ�_����] = pk::max(1, kunshu.base_stat[����ɷ�_����] - 5);
                emperor.update();
            }
            
		}

		string getText_õ��()
		{
			return pk::encode("õ��");
		}

		string getDesc_õ��()
		{
            if (emperor is null)
                return pk::encode("������ ����߽��ϴ�");
            else if (!pk::is_protecting_the_emperor(force) or force.title == ����_Ȳ�� or emperor.mibun == �ź�_���)
                return pk::encode("���� Ȳ���� �˸��ϰ� ���� �ʽ��ϴ�");
            else if (emperor_city_check)
                return pk::encode("���ֿ� ���� Ȳ���� ���� ���ÿ� �־� õ���� �� �� �����ϴ�");
            else if (!kunshu_building_check)
                return pk::encode("���ְ� �ִ� ���ø� ���� �����մϴ�");
            else if (pk::is_absent(kunshu) or pk::is_unitize(kunshu) or kunshu.action_done)
                return pk::encode("���ְ� �ൿ�� �Ϸ��߰ų� ���� �� �Դϴ�.");
            else if (force.tp < TP_COST_õ��)
				return pk::encode(pk::format("�ⱳP�� �����մϴ�.(�ⱳP {})", TP_COST_õ��));
            else if (pk::get_district(pk::get_district_id(force, 1)).ap < ACTION_COST_õ��) 
                return pk::encode(pk::format("�ൿ���� �����մϴ� (�ൿ�� {} �ʿ�)", ACTION_COST_õ��));
			else if (building_gold < GOLD_COST_õ��)
				return pk::encode(pk::format("���� �����մϴ� (��{} �ʿ�)", GOLD_COST_õ��));
			else
				return pk::encode(pk::format("õ���� �����մϴ� (�ⱳ{}, ��{} ���)", TP_COST_õ��, GOLD_COST_õ��));
		}
        
        bool isVisible_õ��()
		{ 
            if (pk::is_campaign()) return false;
            if (emperor is null) return false;
            if (!pk::is_protecting_the_emperor(force) or force.title == ����_Ȳ�� or emperor.mibun == �ź�_���) return false;
			return true;
		}
        
		bool isEnabled_õ��()
		{ 
            if (emperor is null) return false;
            else if (!pk::is_protecting_the_emperor(force) or force.title == ����_Ȳ�� or emperor.mibun == �ź�_���) return false;
            else if (emperor_city_check) return false;
            else if (!kunshu_building_check) return false;
            else if (pk::is_absent(kunshu) or pk::is_unitize(kunshu) or kunshu.action_done) return false;
            else if (force.tp < TP_COST_õ��) return false;
            else if (pk::get_district(pk::get_district_id(force, 1)).ap < ACTION_COST_õ��) return false;
            else if (building_gold < GOLD_COST_õ��) return false;
			return true;
		}
        

		bool handler_õ��()
		{
			
			if (pk::choose({ pk::encode("��"), pk::encode("�ƴϿ�") }, pk::encode(pk::format("������ ���÷� õ���Ͻðڽ��ϱ�? \n(�ⱳ{}, ��{} ���)", TP_COST_õ��, GOLD_COST_õ��)), kunshu ) == 1)
				return false;
            
            
            //-----------------------------------------------------------------
            // ���� Ȳ������ ��ȭ
            pk::scene(pk::scene_t(scene_õ��));
            
            //-----------------------------------------------------------------
            
            if (debate_result ==0)
            {
                // ���� Ȳ�� �̵�
                pk::move(emperor, kunshu_building, false);
                
                // ���� ���� �� �Һ�
                pk::add_gold(kunshu_city, -GOLD_COST_õ��, true);
                
                // �ൿ�� ����
                auto district = pk::get_district(pk::get_district_id(force, 1));
                district.ap -= ACTION_COST_õ��;
                
                // �ⱳ ����
                pk::add_tp(force, -TP_COST_õ��, force.get_pos());
                
                pk::say(pk::encode("� Ȳ�� ���ϸ� ��Ŷ�"), kunshu, kunshu_city);
                pk::create_effect(0x51, kunshu_building.pos);   //����Ʈȿ��
            }
            else
            {
                // �ൿ�� ����
                auto district = pk::get_district(pk::get_district_id(force, 1));
                district.ap -= ACTION_COST_õ��;
                
                pk::say(pk::encode("���ϸ� �����ϴ� �� �����߱�"), kunshu, kunshu_city);
            }
            
            // ���� �ൿ�Ϸ� ('18.11.18)
            kunshu.action_done = true;
            
			return true;
			
		}
        
        
        void scene_õ��()
		{
			int pause = int(pk::option["MessagePause"]);
			pk::option["MessagePause"] = 100;
            pk::message_box(pk::encode("���ϸ� �����Ͽ� õ���� �ؾ߰ڱ�"), kunshu);
            pk::cutin(18);  // ����: ��������
			pk::move_screen(emperor_city.get_pos(), 2000);
			pk::diplomacy(emperor, support, kunshu, pk::diplomacy_t(scene_õ��_1));
            pk::move_screen(kunshu_city.get_pos(), 2000);
            
            if (debate_result == 0)
                pk::cutin(21);  // ����: ����ȯȣ
			
            pk::option["MessagePause"] = pause;
		}
        
        void scene_õ��_1()
		{
            string kunshu_name = pk::decode(pk::get_name(kunshu));
            string city1_name = pk::decode(pk::get_name(emperor_city));
            string city2_name = pk::decode(pk::get_name(kunshu_city));
            
            pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x��, ���� �Ϸ� �̷��� ã�ƿ��̼�?", kunshu_name)), emperor);
            pk::message_box(pk::encode(pk::format("����, ���� �������� �⼼�� ���� �������� �־� ���� \x1b[1x{}\x1b[0x��(��) ��ñ⿡ �����մϴ�.", city1_name)), kunshu);
            pk::message_box(pk::encode("�״�� �׷��� �����ϸ� ���ڴ°�?"), emperor);
            pk::message_box(pk::encode(pk::format("���� �����ϰ� \x1b[1x{}\x1b[0x�� ��ðڽ��ϴ�. õ���� �Ͻ�����.", city2_name)), kunshu);
            pk::message_box(pk::encode("õ���� ���ڴ� ���̿�?"), emperor);
            
            // ���ֿ� Ȳ�Ŀ��� ����
            pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x��, ���� �����ϱ⿣ �����Դϴ�.", kunshu_name)), support);
            debate_result = pk::debate(kunshu, support, true, false, false, true).first;
            
            if (debate_result ==0)  // ���ְ� ���� �̱�� ����Ȳ���� �缳��
            {
                pk::message_box(pk::encode("�׷��ٰ� �ص�..."), support);
                pk::message_box(pk::encode("�ٽ� �ѹ� �����غ��� �ȵǰڼ�?"), emperor);
                debate_result = pk::debate(kunshu, emperor, true, false, false, true).first;
            }
            
            if (debate_result ==0)  // ���ְ� ���� �̱�
            {
                pk::message_box(pk::encode("�׷����ϴ�. � ä�� �Ͻ�����."), kunshu);
                pk::message_box(pk::encode("������...�˰ڼ�.\n���� �ǰ��� �����ڼ�."), emperor);
            }
            else    // ����Ȳ���� ���� �̱�
            {
                pk::message_box(pk::encode("õ���� �ƴϵǿ�."), emperor);
                pk::message_box(pk::encode("�˰ڽ��ϴ�."), kunshu);
            }
        }
        
        
        
        //---------------------------------------------------------------------------------------
        
        void event_Emperor_Escape(pk::force@ force_turn)
        {
            @force = @force_turn;
            
            if (force.is_player() and pk::is_protecting_the_emperor(force) and force.title != ����_Ȳ��)
            {
                @kunshu = pk::get_person(pk::get_kunshu_id(force));
                @kunshu_building = pk::get_building(kunshu.service);
                @kunshu_city = pk::building_to_city(kunshu_building);
                @emperor = pk::get_person(pk::get_scenario().emperor);
                @emperor_city = pk::building_to_city(pk::hex_object_to_building(pk::get_hex_object(emperor.location)));
                
                if (emperor.get_id() == ����_����)
                    @support = pk::get_person(����_Ȳ��);
                else
                    @support = pk::get_person(����_ȯ��);
                
                @ reporter = pk::get_person(����_����);
                
                if (emperor_city.public_order < ����Ȳ������_����ġ�� and pk::get_city_count(force) >= ����Ȳ������_���ص��ü� and
                   ((kunshu.kanshitsu == �ѽ�_����) or (kunshu.kanshitsu == �ѽ�_���� and pk::rand_bool(����Ȳ������_�߻�Ȯ��)) ) )
                {
                    // ���� ���� ���� �˻�
                    int force_num = EnemyForceSel(emperor_city);
                    if (force_num > -1)
                    {
                        @ new_force = pk::get_force(force_num);
                        @ new_kunshu = pk::get_person(pk::get_kunshu_id(new_force));
                        @ new_building = pk::get_building(new_kunshu.service);
                        @ new_city = pk::building_to_city(new_building);
                        
                        // ���� Ȳ�� ���־�
                        pk::scene(pk::scene_t(scene_����));
                        
                        // ���� Ȳ�� �̵�
                        pk::move(emperor, new_building, false);
                    }
                }
            }

        }
        
        void scene_����()
		{
            // ����Ȳ�� �д�
			pk::move_screen(emperor_city.get_pos(), 2000);
			pk::diplomacy(emperor, support, reporter, pk::diplomacy_t(scene_����_1));
            
            // ��� �ü�
            scene_����_2();
            
            // ���� �̵�
            pk::move_screen(new_city.get_pos(), 2000);
            scene_����_3();
            
            string emperor_name = pk::decode(pk::get_name(emperor));
            string kunshu_name = pk::decode(pk::get_name(kunshu));
            string new_kunshu_name = pk::decode(pk::get_name(new_kunshu));
            pk::message_box(pk::encode(pk::format("\x1b[1x{}��\x1b[0x�� ����Ȳ���� �˸��Ͽ����ϴ�.", new_kunshu_name)));
            pk::option["MessagePause"] = 100;
		}
        
        void scene_����_1()
		{
            string kunshu_name = pk::decode(pk::get_name(kunshu));
            string new_kunshu_name = pk::decode(pk::get_name(new_kunshu));
            string city1_name = pk::decode(pk::get_name(emperor_city));
            string city2_name = pk::decode(pk::get_name(new_city));
            
            pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x�� �������� ���� �������� �ֵ���", kunshu_name)), emperor);
            pk::message_box(pk::encode(pk::format("���� \x1b[1x{}\x1b[0x�� ��� ����� �� �ϴ� ���� ��ó�� �ű�ô� �� �������?", city1_name)), support);
            pk::message_box(pk::encode("��ü ���� ���� ���̳�?"), emperor);
            pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x���� �����ϴ� �� ��Ű���? \x1b[1x{}\x1b[0x�� ��������.", new_kunshu_name, city2_name)), support);
            pk::message_box(pk::encode("���� �����̴�. � ���⸦ ����������"), emperor);
            pk::message_box(pk::encode("��. �ҽ��� ��ðڽ��ϴ�"), reporter);
        }
        void scene_����_2()
		{
            pk::person@ gaurd = pk::get_person(����_����);

            pk::background(1);  
            pk::message_box(pk::encode("���� ���ô� ���Դϱ�?"), gaurd);
            pk::cutin(20);  // ����: �������
            pk::message_box(pk::encode("��å ���� ���̴�. ���� ���Ѷ� �!"), reporter);
            pk::message_box(pk::encode("��..��..�ƹ��� ���� ���� ���߽��ϴ�"), gaurd);
            pk::message_box(pk::encode("�����ϱ���"), support);
            pk::message_box(pk::encode("�˼��մϴ�. � ���ʽÿ�."), gaurd);
            pk::background(-1);
            pk::fade(100);
        }
        void scene_����_3()
		{
            string kunshu_name = pk::decode(pk::get_name(kunshu));
            string new_kunshu_name = pk::decode(pk::get_name(new_kunshu));
            string new_kunshu_title = pk::decode(pk::get_name(pk::get_title(new_force.title)));
            
            pk::background(3);
            pk::fade(255);
            pk::message_box(pk::encode(pk::format("��.��.������. ���� \x1b[1x{}\x1b[0x�� ������ �־��°�?", new_kunshu_name)), emperor);
            pk::message_box(pk::encode(pk::format("�ƴմϴ�. \x1b[1x{}\x1b[0x�� ������ ��ó�̴� ���ݸ� �� ���ø� �˴ϴ�.", new_kunshu_name)), reporter);
            pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x��(��) ���� ���� �� �ִ� ������....", new_kunshu_name)), emperor);
            pk::cutin(12);  // ����: ���߱�
            pk::message_box(pk::encode(pk::format("�� �Ҹ��� �����̳�. \x1b[1x{}��\x1b[0x�� ������� �ѾƿԴ°�?", kunshu_name)), emperor);
            pk::fade(0);
			pk::sleep();
			pk::background(-1);
            
            pk::background(11);
			pk::fade(255);
            pk::play_bgm(17);
            
            if (new_force.title <= ����_���ڻ�)
                pk::message_box(pk::encode(pk::format("�ƴ�! ���ϰ� �ƴϽʴϱ�? \x1b[1x{} {}\x1b[0x��(��) ���ϸ� �����մϴ�", new_kunshu_title, new_kunshu_name)), new_kunshu);
            else
                pk::message_box(pk::encode(pk::format("�ƴ�! ���ϰ� �ƴϽʴϱ�? \x1b[1x{}\x1b[0x��(��) ���ϸ� �����մϴ�", new_kunshu_name)), new_kunshu);
            
            pk::message_box(pk::encode(pk::format("�״븦 ���� �����̱���. �� \x1b[1x{}\x1b[0x���� �����Ϸ� ����� ������� �Գ��.", new_kunshu_name, kunshu_name)), emperor);
            pk::message_box(pk::encode("Ȳ���մϴ�"), new_kunshu);
            pk::message_box(pk::encode("� ���ϲ��� ��� ��ó�� �ȳ��Ͻÿ�"), support);
            pk::message_box(pk::encode("��. �����Դϴ�. � ���ϸ� ��Ŷ�."), new_kunshu);
            
            pk::cutin(21);  // ����: ����ȯȣ
        }
        
        //--------------------------------------------------------------------------------
        // �ְ� ������ �˻� �Լ�
        int EnemyForceSel(pk::city @ city)
        {
            int force_sel = -1;
            int force_city_cnt = 0;
            
            auto force_list = pk::list_to_array(pk::get_force_list());
            for (int k = 0; k < int(force_list.length); k++)
            {
                if (force_list[k].title <= ����_���ڻ� and force_list[k].get_force_id() != city.get_force_id() and force_city_cnt < pk::get_city_count(force_list[k]))
                {
                    force_city_cnt = pk::get_city_count(force_list[k]);
                    force_sel = force_list[k].get_force_id();
                }
            }
            
            return force_sel;
        }
        //--------------------------------------------------------------------------------

	}
   
	Main main;
}