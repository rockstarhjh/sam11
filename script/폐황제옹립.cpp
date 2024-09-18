/*  
@������: �⸶å��
@Update: '18.12.3  / ��������: ������ ����Ȳ���� ������Ű�� �˸���
@Update: '19.7.8   / ���泻��: ��Ȳ�� �ؾ�޽��� ���� ����
@Update: '20.8.29  / ���泻��: ķ���ο����� ��ũ��Ʈ ��Ȱ��ȭ

*/

namespace ��Ȳ���˸�
{
	
	// ================ CUSTOMIZE ================
    
		const int TP_COST_�˸� = 3000; 	   // �ⱳP �ʿ䷮
		const int ACTION_COST_�˸� = 100;   // �ൿ�� �ʿ䷮
		
    
	// ===========================================
	
	class Main
	{
		
		pk::building@ building;
		pk::building@ kunshu_building;
		
		pk::city@ kunshu_city;
		pk::city@ emperor_city;
        pk::point emeperor_pos;
		
		pk::force@ force;
		
		pk::person@ kunshu;
		pk::person@ emperor; 
		pk::person@ support; 

		Main()
		{

			pk::menu_item item;
			item.menu = 105;        
			item.init = pk::building_menu_item_init_t(init_�˸�);
			item.is_visible = pk::menu_item_is_visible_t(isVisible_�˸�);
			item.is_enabled = pk::menu_item_is_enabled_t(isEnabled_�˸�);
			item.get_text = pk::menu_item_get_text_t(getText_�˸�);
			item.get_desc = pk::menu_item_get_desc_t(getDesc_�˸�);
			item.handler = pk::menu_item_handler_t(handler_�˸�);
			pk::add_menu_item(item);
            
		}

		
        void init_�˸�(pk::building@ building_t)
		{
			
			@building = @building_t;
			@force = pk::get_force(building.get_force_id());
			@kunshu = pk::get_person(pk::get_kunshu_id(building));
            @kunshu_building = pk::get_building(kunshu.service);
			@kunshu_city = pk::building_to_city(kunshu_building);
            @emperor = pk::get_person(pk::get_scenario().emperor);
			@support = pk::get_person(����_ȯ��);
		}

		string getText_�˸�()
		{
			return pk::encode("�˸�");
		}

		string getDesc_�˸�()
		{
            if (emperor !is null and emperor.mibun != �ź�_���)
                return pk::encode("���� Ȳ���� �������� �ʾҽ��ϴ�");
            else if (kunshu.kanshitsu != �ѽ�_�߽�)
                return pk::encode("�ѽ� �߽��� ���ָ� ���� �����մϴ�");
            else if (pk::is_protecting_the_emperor(force) or force.title == ����_Ȳ��)
                return pk::encode("���� Ȳ���� �˸��ϰ� �ְų� ���ְ� �̹� Ȳ���Դϴ�.");
            else if (kunshu_city.get_id() != kunshu.service)
                return pk::encode("���ְ� �ִ� ���ø� ���� �����մϴ�.");
            else if (pk::is_absent(kunshu) or pk::is_unitize(kunshu) or kunshu.action_done)
                return pk::encode("���ְ� �ൿ�� �Ϸ��߰ų� ���� �� �Դϴ�.");
            else if (force.tp < TP_COST_�˸�)
				return pk::encode(pk::format("�ⱳP�� �����մϴ�.(�ⱳP {})", TP_COST_�˸�));
            else if (pk::get_district(pk::get_district_id(force, 1)).ap < ACTION_COST_�˸�) 
                return pk::encode(pk::format("�ൿ���� �����մϴ�. (�ൿ�� {} �ʿ�)", ACTION_COST_�˸�));
            else
				return pk::encode(pk::format("���� Ȳ���� �����Ͽ� �˸��մϴ�. (�ⱳP {} ���)", TP_COST_�˸�));
            
		}
        
        bool isVisible_�˸�()
		{ 
            if (pk::is_campaign()) return false;
            if (emperor !is null and emperor.mibun != �ź�_���) return false;
            else if (kunshu.kanshitsu != �ѽ�_�߽�) return false;
            return true;
		}
        
		bool isEnabled_�˸�()
		{ 
            if (emperor !is null and emperor.mibun != �ź�_���) return false;
            else if (kunshu.kanshitsu != �ѽ�_�߽�) return false;
            else if (pk::is_protecting_the_emperor(force) or force.title == ����_Ȳ��) return false;
            else if (kunshu_city.get_id() != kunshu.service) return false;
            else if (pk::is_absent(kunshu) or pk::is_unitize(kunshu) or kunshu.action_done) return false;
            else if (force.tp < TP_COST_�˸�) return false;
            else if (pk::get_district(pk::get_district_id(force, 1)).ap < ACTION_COST_�˸�) return false;
            else
			return true;
		}

		bool handler_�˸�()
		{
			if (pk::choose({ pk::encode("��"), pk::encode("�ƴϿ�")}, pk::encode(pk::format("��Ȳ���� ������Ű�ڽ��ϱ�?\n(�ⱳ {} ���)", TP_COST_�˸�)), kunshu) == 1)
				return false;
			            
			// ���� Ȳ������ ��ȭ
            pk::scene(pk::scene_t(scene_�˸�));
            
            // ���� Ȳ�� ���� �� �̵�
            emperor.mibun = �ź�_����;
            emperor.update();
            pk::move(emperor, kunshu_building, false);
            
			// �ൿ�� ����
			auto district = pk::get_district(pk::get_district_id(force, 1));
			district.ap -= ACTION_COST_�˸�;
			
			// �ⱳ ����
			pk::add_tp(force, -TP_COST_�˸�, force.get_pos());
			
            string kunshu_name = pk::decode(pk::get_name(kunshu));
			pk::message_box(pk::encode(pk::format("\x1b[1x{}��\x1b[0x��(��) ����Ȳ���� �˸��Ͽ����ϴ�.", kunshu_name)));
			pk::create_effect(0x51, kunshu_building.pos);   //����Ʈȿ��
            
            kunshu.action_done = true;
            
			return true;
			
		}
        
        
        void scene_�˸�()
		{
			int pause = int(pk::option["MessagePause"]);
			pk::option["MessagePause"] = 100;
            pk::message_box(pk::encode("������ Ȳ�������� ��� ��ô���. � ��ſ;� �Ѵ�."), kunshu);
            pk::cutin(12);  // ����: ���߱�
			pk::move_screen(kunshu_city.get_pos(), 2000);
            
            // ��� Ȳ�� ����
			scene_�˸�_1();
            
            pk::move_screen(kunshu_city.get_pos(), 2000);
            
			pk::say(pk::encode("� Ȳ�� ���ϸ� ��Ŷ�"), kunshu, kunshu_city);
			pk::cutin(21);  // ����: ����ȯȣ
			
            pk::option["MessagePause"] = pause;
			
		}
        
        void scene_�˸�_1()
		{
            string kunshu_name = pk::decode(pk::get_name(kunshu));
			string kunshu_title = pk::decode(pk::get_name(pk::get_title(force.title)));
			string kunshu_city_name = pk::decode(pk::get_name(kunshu_city));
            
            pk::fade(0);
			pk::sleep();
            
			pk::background(9);  //���: ����
			pk::fade(255);
            pk::message_box(pk::encode("������ ���� �̷��� ����� ���� �� �� ������"), kunshu);
            pk::message_box(pk::encode("�۽��...�� �𸣰ڽ��ϴ�..."), pk::get_person(����_���));
            pk::message_box(pk::encode("���忡 �� �� ���⵵ �ϰ�..."), pk::get_person(����_û��));
            pk::message_box(pk::encode("���� �������� ������. �ܼ��� �������� �𸥴�."), kunshu);
            pk::message_box(pk::encode("��, �ֱ�. �����Դϴ�"), pk::get_person(����_����));
            pk::fade(0);
            pk::background(-1);
            
            pk::background(4);  //���: ����
			pk::fade(255);
            pk::message_box(pk::encode("Ȥ�� �̷� ���� �� �� ������"), kunshu);
            pk::message_box(pk::encode("��. �� ��. �� �ʿ� �ִ� ������ ���ø� �˴ϴ�. �׷��� ��¾ �Ϸ�..."), pk::get_person(����_��ȣ));
            pk::message_box(pk::encode("����. \n���ѷ���. �."), kunshu);
            pk::message_box(pk::encode("��."), pk::get_person(����_����));
            pk::message_box(pk::encode("���� ���̱淡 ���� ���Ѱ�."), pk::get_person(����_��ȣ));
            pk::fade(0);
            pk::background(-1);
            
            pk::background(7);  //���: ����
			pk::fade(255);
            pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x���� �ƴϽʴϱ�? ���⸦ ��� ã���̽��ϱ�? ����.", kunshu_name)), support);
            pk::message_box(pk::encode("���ϸ� ��÷� ��и��� ã�ƿԼ�. ���ϴ� ��� ��ÿ�?"), kunshu);
            pk::message_box(pk::encode("�����Դϴ�. ���� ��������."), support);
            pk::fade(0);
            pk::background(-1);
            
            pk::background(5);  //���: ��
            pk::fade(255);
            
            
            if (emperor is null)
            {
                pk::get_scenario().emperor = ����_����;
                @emperor = pk::get_person(pk::get_scenario().emperor);
            }
            
            pk::message_box(pk::encode(pk::format("�ƴ�! ���ϰ� �ƴϽʴϱ�? \x1b[1x{}\x1b[0x��(��) ���ϸ� �����մϴ�", kunshu_name)), kunshu);
            pk::message_box(pk::encode(pk::format("�� �����ǰ� �ʹ��� ������µ�, \x1b[1x{}\x1b[0x �״븦 ���� �����̱���. ", kunshu_name)), emperor);
            pk::message_box(pk::encode("Ȳ���մϴ�"), kunshu);
            pk::message_box(pk::encode(pk::format("�� \x1b[1x{}\x1b[0x��(��) ���ϸ� ��ðڽ��ϴ�.", kunshu_name)), kunshu);
            pk::message_box(pk::encode("���� ����. �״�߸��� ������ ����̿�"), emperor);
            pk::message_box(pk::encode(pk::format("����. � ä�� �Ͻ�����. ���� \x1b[1x{}\x1b[0x(��)�� ���ϸ� ��ðڽ��ϴ�.", kunshu_city_name)), kunshu);
            pk::background(-1);
        }
		

	}
   
	Main main;
}