/*    
@������: HoneyBee      
@����: �̹��� Ư�⸦ ������ ������ �Ҽӵ� ���ÿ��� �̹����� �뺴���� ��� ���� (50% Ȯ���� ��� ����)   

     -> �̹��� ��뿡 �����ϸ� ��ſ� ������ ȹ���ϰ� ���� �Һ���� �ʽ��ϴ�. 

*/

namespace �̹���_�뺴
{
	
	// ================ CUSTOMIZE ================
	
		const bool ����_Ȱ��ȭ = true;        // true = on, false = off
		const bool ��ȯ��_Ȱ��ȭ = true;       // true = on, false = off
		const bool �����_Ȱ��ȭ = true;       // true = on, false = off
		const bool ������_Ȱ��ȭ = true;       // true = on, false = off
		
		const bool �̸��ڵ� = false;	       // ���� �̸��� �ڵ����� ����	[�̸��ڵ� true�Ͻ�, �̸����� false�� ����]
		const bool �̸����� = true;           // ���� �̸��� ����(�迭 �ۼ�)���� ���� [�̸����� true�Ͻ�, �̸��ڵ� false�� ����]
	
		const int TP_COST = 500; 		   // �ⱳP ��ġ ����
		const int ACTION_COST = 70;        // �ൿ�� �ʿ䷮
		const int GOLD_COST = 3000;        // �� �ʿ䷮
		const int ADD_FOOD = 10000;        // �̹��� �뺴 ��ſ� ȹ���ϴ� ����
		
		const int ������Ȯ�� = 50;    		   // �̹��� �뺴 ����� ������ Ȯ�� (�⺻ ���� - 50%)
		
		/* 
		   �̹��� �뺴�� 4���� �� �� ���� TYPE�� �����˴ϴ�.
		   0-������, 1-������, 2-������, 3-RANDOM 
		*/

		// ������ �ɷ�ġ ���� (���, ����)
		const int min_stat_������_��� = 70;   // ������ ��Ź ������ �ּ� ��� �ɷ�ġ�� ���� (�⺻ ���� - 70)
		const int max_stat_������_��� = 97;   // ������ ��Ź ������ �ִ� ��� �ɷ�ġ�� ���� (�⺻ ���� - 90)
		
		const int min_stat_������_���� = 70;   // ������ ��Ź ������ �ּ� ���� �ɷ�ġ�� ���� (�⺻ ���� - 70)
		const int max_stat_������_���� = 97;   // ������ ��Ź ������ �ִ� ���� �ɷ�ġ�� ���� (�⺻ ���� - 90)
		
		const int min_stat_������_���� = 10;   // ������ ��Ź ������ �ּ� ���� �ɷ�ġ�� ���� (�⺻ ���� - 10)
		const int max_stat_������_���� = 65;   // ������ ��Ź ������ �ִ� ���� �ɷ�ġ�� ���� (�⺻ ���� - 60)
		
		const int min_stat_������_��ġ = 10;   // ������ ��Ź ������ �ּ� ��ġ �ɷ�ġ�� ���� (�⺻ ���� - 10)
		const int max_stat_������_��ġ = 65;   // ������ ��Ź ������ �ִ� ��ġ �ɷ�ġ�� ���� (�⺻ ���� - 60)


		// ������ �ɷ�ġ ���� (����, ��ġ)
		const int min_stat_������_��� = 10;   // ������ ��Ź ������ �ּ� ��� �ɷ�ġ�� ���� (�⺻ ���� - 10)
		const int max_stat_������_��� = 65;   // ������ ��Ź ������ �ִ� ��� �ɷ�ġ�� ���� (�⺻ ���� - 60)
		
		const int min_stat_������_���� = 10;   // ������ ��Ź ������ �ּ� ���� �ɷ�ġ�� ���� (�⺻ ���� - 10)
		const int max_stat_������_���� = 65;   // ������ ��Ź ������ �ִ� ���� �ɷ�ġ�� ���� (�⺻ ���� - 60)
		
		const int min_stat_������_���� = 70;   // ������ ��Ź ������ �ּ� ���� �ɷ�ġ�� ���� (�⺻ ���� - 70)
		const int max_stat_������_���� = 97;   // ������ ��Ź ������ �ִ� ���� �ɷ�ġ�� ���� (�⺻ ���� - 90)
		
		const int min_stat_������_��ġ = 70;   // ������ ��Ź ������ �ּ� ��ġ �ɷ�ġ�� ���� (�⺻ ���� - 70)
		const int max_stat_������_��ġ = 97;   // ������ ��Ź ������ �ִ� ��ġ �ɷ�ġ�� ���� (�⺻ ���� - 90)
		
		
		// ������ �ɷ�ġ ���� (���, ����, ����, ��ġ)
		const int min_stat_������_��� = 60;   // ������ ��Ź ������ �ּ� ��� �ɷ�ġ�� ���� (�⺻ ���� - 70)
		const int max_stat_������_��� = 92;   // ������ ��Ź ������ �ִ� ��� �ɷ�ġ�� ���� (�⺻ ���� - 90)
		
		const int min_stat_������_���� = 60;   // ������ ��Ź ������ �ּ� ���� �ɷ�ġ�� ���� (�⺻ ���� - 70)
		const int max_stat_������_���� = 92;   // ������ ��Ź ������ �ִ� ���� �ɷ�ġ�� ���� (�⺻ ���� - 90)
		
		const int min_stat_������_���� = 65;   // ������ ��Ź ������ �ּ� ���� �ɷ�ġ�� ���� (�⺻ ���� - 70)
		const int max_stat_������_���� = 92;   // ������ ��Ź ������ �ִ� ���� �ɷ�ġ�� ���� (�⺻ ���� - 90)
		
		const int min_stat_������_��ġ = 65;   // ������ ��Ź ������ �ּ� ��ġ �ɷ�ġ�� ���� (�⺻ ���� - 70)
		const int max_stat_������_��ġ = 92;   // ������ ��Ź ������ �ִ� ��ġ �ɷ�ġ�� ���� (�⺻ ���� - 90)
		
		
		// ������, ������, ������ �ŷ� ���� 
		const int min_stat_�ŷ� = 30;   	   // �̹��� �뺴�� �ּ� �ŷ� �ɷ�ġ�� ���� (�⺻ ���� - 30)
		const int max_stat_�ŷ� = 90;        // �̹��� �뺴�� �ִ� �ŷ� �ɷ�ġ�� ���� (�⺻ ���� - 90)
		
		const int min_distance = 1;        // �뺴 �δ� ���� �ּ� ��ġ
        const int max_distance = 8;        // �뺴 �δ� ���� �ִ� ��ġ
		const int troops = 5000;		   // �뺴 �δ� ���� ���� (�ִ� 5000)
		
		
		
		// === �̹��� �뺴 SLOT ���� ���� (�߿�) === ��
		
		/* 
		   - ������ SLOT�� ���� (�ݵ�� 2���� �� �� ������ true, �������� false�� �����ؾߵ�)
		   - slot_�Ź����� Gold Edition Patch���� ������ �Ź����� ������ ���� �⺻���� ������
		   - Gold Edition Patch ���� ��ϵ� �Ź����� 850 ~ 934 �̹Ƿ�, 935���� �̹��� �뺴�� �ۼ��ϵ��� �⺻ ����
		*/
		
		// �Ź��� SLOT�� ����Ͽ� �̹��� �뺴 �߰� (����: �Ź����� SLOT�� ����ϹǷ�, �Ź����� ���� �������� ��� ����õ)
		const bool slot_�Ź��� = true;
		
		// �Ϲݹ���(�̹� ����ϰų� �źо��� ����) SLOT�� ����Ͽ� �̹��� �뺴 �߰� (����: ����� ������ ������, SLOT�� ������ ŭ)
		const bool slot_�Ϲݹ��� = false;   
		
		// �̻�� ��빫�� SLOT�� ����Ͽ� ��Ź���� �߰� (����: SLOT�� ������ ŭ, �ִ� 18��)
		const bool slot_��빫�� = false;

		// ================================ ��	
		
		
		/* 
		
			�̹��� ���� �̸��� ARRAY�� �̸� SETTING �Ͻñ� �ٶ��ϴ�. (�Ʒ��� �ӽ÷� ���� �����Դϴ�.)
			�Ʒ� ������ RANDOM���� ����Ͽ� �̹��� ������ �̸��� �������ϴ�.
			
			EX) ����, ����, ����, ����, ����, ��Ź, �հ�, ��Ź, ���� ��..
		
		*/
		
		// �̹��� ���� [��] (�ӽ÷� 40�� ����)
		array<string> sei_ = { "��", "��", "��", "��", "��", "����", "ȭ", "��", "��", "��",
                               "��", "��", "��", "����", "��", "��", "��", "��", "��", "��",
							   "��", "��", "��", "��", "��", "��", "ȭ", "��", "��", "Ȳ",
							   "��", "��", "��", "��", "��", "��", "��", "��", "����", "�縶" }; 	 

	    // �̹��� ���� [�̸�] (�ӽ÷� 40���� ����)
		array<string> mei_ = { "��", "��", "��", "Ź", "��", "��", "��", "��", "��", "��", 
		                       "��", "��", "â", "��", "��", "��", "��", "Ȳ", "��", "��",
							   "��", "��", "ȫ", "��", "��", "��", "��", "��", "��", "��",
							   "��", "��", "��", "��", "��", "��", "��", "��", "��", "��" }; 
		
		
		// EX) { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ... 39 } <- TOTAL 40�� (ARRAY���� [��], [�̸�]�� �ø� ������ ������ ������ �����Ͻø� �˴ϴ�.)
		int i = 0;   // �迭�� FIRST NUMBER 
		int j = 39;  // �迭�� LAST NUMBER
		

		const int KEY = pk::hash("�뺴���");
	
	// ===========================================
	
	
	class Main
	{
		pk::random random(pk::rand());
		pk::building@ building_;
		pk::building@ taishu_building;
		pk::force@ force;
		pk::person@ taishu;
		pk::city@ city;
		uint16 building_gold;
		
		bool �������� = false;
		bool ��ȯ������ = false;
		bool ��������� = false;
		bool ���������� = false;
		
		// �ǹ� �޴� ����
		int menu_city_id_;
		
		// �ǹ� �޴� ����
		int menu_force_id_;
		
		Main()
		{
			
			pk::menu_item item;
			int parent;
			
			item.menu = 0;
			item.get_text = cast<pk::menu_item_get_text_t@>(function() { return pk::encode("�뺴���"); });
            item.init = pk::building_menu_item_init_t(init);
            item.is_visible = pk::menu_item_is_visible_t(isMenuVisible);
			parent = pk::add_menu_item(item);
			
			if (����_Ȱ��ȭ)
			{	
				item.menu = parent;
				item.init = pk::building_menu_item_init_t(init);
				item.is_visible = pk::menu_item_is_visible_t(isMenuVisible);
				item.is_enabled = pk::menu_item_is_enabled_t(isEnabled_����);
				item.get_text = pk::menu_item_get_text_t(getText_����);
				item.get_desc = pk::menu_item_get_desc_t(getDesc_����);
				item.handler = pk::menu_item_handler_t(handler_����);
				pk::add_menu_item(item);
			}
			
			if (��ȯ��_Ȱ��ȭ)
			{	
				item.menu = parent;
				item.init = pk::building_menu_item_init_t(init);
				item.is_visible = pk::menu_item_is_visible_t(isMenuVisible);
				item.is_enabled = pk::menu_item_is_enabled_t(isEnabled_��ȯ��);
				item.get_text = pk::menu_item_get_text_t(getText_��ȯ��);
				item.get_desc = pk::menu_item_get_desc_t(getDesc_��ȯ��);
				item.handler = pk::menu_item_handler_t(handler_��ȯ��);
				pk::add_menu_item(item);
			}
			
			if (�����_Ȱ��ȭ)
			{	
				item.menu = parent;
				item.init = pk::building_menu_item_init_t(init);
				item.is_visible = pk::menu_item_is_visible_t(isMenuVisible);
				item.is_enabled = pk::menu_item_is_enabled_t(isEnabled_�����);
				item.get_text = pk::menu_item_get_text_t(getText_�����);
				item.get_desc = pk::menu_item_get_desc_t(getDesc_�����);
				item.handler = pk::menu_item_handler_t(handler_�����);
				pk::add_menu_item(item);
			}
			
			if (������_Ȱ��ȭ)
			{	
				item.menu = parent;
				item.init = pk::building_menu_item_init_t(init);
				item.is_visible = pk::menu_item_is_visible_t(isMenuVisible);
				item.is_enabled = pk::menu_item_is_enabled_t(isEnabled_������);
				item.get_text = pk::menu_item_get_text_t(getText_������);
				item.get_desc = pk::menu_item_get_desc_t(getDesc_������);
				item.handler = pk::menu_item_handler_t(handler_������);
				pk::add_menu_item(item);
			}
	

		}

		void init(pk::building@ building)	
		{
			
			@building_ = @building;
			@force = pk::get_force(building.get_force_id());
			@taishu = pk::get_person(pk::get_taishu_id(building));
			@city = pk::building_to_city(building);
			building_gold = pk::get_gold(building);
			
            if (pk::is_alive(taishu))
                @taishu_building = pk::get_building(taishu.service);
            
			menu_city_id_ = -1;
			
			if (city !is null)
				menu_city_id_ = city.get_id();
			menu_force_id_ = building.get_force_id();
			
		}
		
        bool isMenuVisible()
		{
            if (building_.get_id() >= �ǹ�_������) return false;
			return menu_city_id_ != -1 and menu_force_id_ == pk::get_current_turn_force_id();
		}
		
		//---------------------------------------------------------------------------
        // ����
        //---------------------------------------------------------------------------

		string getText_����()
		{
			return pk::encode("(����)���");
		}
		
		string getDesc_����()
		{
            if (building_gold < GOLD_COST)
                return pk::encode(pk::format("���� �����մϴ�.(�� {} �ʿ�)", GOLD_COST));
			else if (!taishu_building.has_skill(Ư��_ģ��))
                return pk::encode("���ÿ� ģ�� Ư�⸦ ������ ������ �����ϴ�.");
            else if (getEmptyPos(taishu_building) == -1)
                return pk::encode("�뺴�� ������ ��Ұ� �����ϴ�.");
			else if (force.tp < TP_COST)
                return pk::encode(pk::format("�ⱳP�� �����մϴ�.(�ⱳP {})", TP_COST));
            else if (pk::get_district(pk::get_district_id(force, 1)).ap < ACTION_COST)
                return pk::encode(pk::format("�ൿ���� �����մϴ�.(�ൿ�� {} �ʿ�)", ACTION_COST));
			else
				return pk::encode(pk::format("�̹��� �뺴�� ����մϴ�.(�ⱳP {} ���)", TP_COST));
		}

		bool isEnabled_����()
		{
			if (building_gold < GOLD_COST) return false;
			else if (!taishu_building.has_skill(Ư��_ģ��)) return false;
            else if (getEmptyPos(taishu_building) == -1) return false;
            else if (force.tp < TP_COST) return false;
            else if (pk::get_district(pk::get_district_id(force, 1)).ap < ACTION_COST) return false;
			return true;
		}

		bool handler_����()
		{
			
			if (pk::choose(pk::encode("�̹����� ����Ͻðڽ��ϱ�?"), { pk::encode("��"), pk::encode("�ƴϿ�") }) == 1)
				return false;
			
			if (pk::rand_bool(������Ȯ��) or getEmptyPerson() is null)
			{
				int iminzoku_id = ����_���θ�;
				int face_no = 681;
				failOrNull_iminzoku(iminzoku_id, face_no);
			} 
			
			else 
			{ 
				�������� = true;
				set_iminzoku(); 
			}

			return true;
		}
		
		
		
		//---------------------------------------------------------------------------
        // ��ȯ��
        //---------------------------------------------------------------------------

		string getText_��ȯ��()
		{
			return pk::encode("(��ȯ��)���");
		}
		
		string getDesc_��ȯ��()
		{
            if (building_gold < GOLD_COST)
                return pk::encode(pk::format("���� �����մϴ�.(�� {} �ʿ�)", GOLD_COST));
			else if (!taishu_building.has_skill(Ư��_ģ��))
                return pk::encode("���ÿ� ģ�� Ư�⸦ ������ ������ �����ϴ�.");
            else if (getEmptyPos(taishu_building) == -1)
                return pk::encode("�뺴�� ������ ��Ұ� �����ϴ�.");
			else if (force.tp < TP_COST)
                return pk::encode(pk::format("�ⱳP�� �����մϴ�.(�ⱳP {})", TP_COST));
            else if (pk::get_district(pk::get_district_id(force, 1)).ap < ACTION_COST)
                return pk::encode(pk::format("�ൿ���� �����մϴ�.(�ൿ�� {} �ʿ�)", ACTION_COST));
			else
				return pk::encode(pk::format("�̹��� �뺴�� ����մϴ�.(�ⱳP {} ���)", TP_COST));
		}

		bool isEnabled_��ȯ��()
		{
			if (building_gold < GOLD_COST) return false;
			else if (!taishu_building.has_skill(Ư��_ģ��)) return false;
            else if (getEmptyPos(taishu_building) == -1) return false;
            else if (force.tp < TP_COST) return false;
            else if (pk::get_district(pk::get_district_id(force, 1)).ap < ACTION_COST) return false;
			return true;
		}

		bool handler_��ȯ��()
		{
			
			if (pk::choose(pk::encode("�̹����� ����Ͻðڽ��ϱ�?"), { pk::encode("��"), pk::encode("�ƴϿ�") }) == 1)
				return false;
			
			if (pk::rand_bool(������Ȯ��) or getEmptyPerson() is null)
			{
				int iminzoku_id = ����_��ȯ�θ�;
				int face_no = 679;
				failOrNull_iminzoku(iminzoku_id, face_no);
			} 
			
			else 
			{ 
				��ȯ������ = true;
				set_iminzoku(); 
			}

			return true;
		}
		

		
		//---------------------------------------------------------------------------
        // �����
        //---------------------------------------------------------------------------

		string getText_�����()
		{
			return pk::encode("(�����)���");
		}
		
		string getDesc_�����()
		{
            if (building_gold < GOLD_COST)
                return pk::encode(pk::format("���� �����մϴ�.(�� {} �ʿ�)", GOLD_COST));
			else if (!taishu_building.has_skill(Ư��_ģ��))
                return pk::encode("���ÿ� ģ�� Ư�⸦ ������ ������ �����ϴ�.");
            else if (getEmptyPos(taishu_building) == -1)
                return pk::encode("�뺴�� ������ ��Ұ� �����ϴ�.");
			else if (force.tp < TP_COST)
                return pk::encode(pk::format("�ⱳP�� �����մϴ�.(�ⱳP {})", TP_COST));
            else if (pk::get_district(pk::get_district_id(force, 1)).ap < ACTION_COST)
                return pk::encode(pk::format("�ൿ���� �����մϴ�.(�ൿ�� {} �ʿ�)", ACTION_COST));
			else
				return pk::encode(pk::format("�̹��� �뺴�� ����մϴ�.(�ⱳP {} ���)", TP_COST));
		}

		bool isEnabled_�����()
		{
			if (building_gold < GOLD_COST) return false;
			else if (!taishu_building.has_skill(Ư��_ģ��)) return false;
            else if (getEmptyPos(taishu_building) == -1) return false;
            else if (force.tp < TP_COST) return false;
            else if (pk::get_district(pk::get_district_id(force, 1)).ap < ACTION_COST) return false;
			return true;
		}

		bool handler_�����()
		{
			
			if (pk::choose(pk::encode("�̹����� ����Ͻðڽ��ϱ�?"), { pk::encode("��"), pk::encode("�ƴϿ�") }) == 1)
				return false;

			if (pk::rand_bool(������Ȯ��) or getEmptyPerson() is null)
			{
				int iminzoku_id = ����_����θ�;
				int face_no = 683;
				failOrNull_iminzoku(iminzoku_id, face_no);		
			}
			
			else 
			{ 
				��������� = true;
				set_iminzoku(); 
			}

			return true;
		}
		
		
		
		//---------------------------------------------------------------------------
        // ������
        //---------------------------------------------------------------------------

		string getText_������()
		{
			return pk::encode("(������)���");
		}
		
		string getDesc_������()
		{
            if (building_gold < GOLD_COST)
                return pk::encode(pk::format("���� �����մϴ�.(�� {} �ʿ�)", GOLD_COST));
			else if (!taishu_building.has_skill(Ư��_ģ��))
                return pk::encode("���ÿ� ģ�� Ư�⸦ ������ ������ �����ϴ�.");
            else if (getEmptyPos(taishu_building) == -1)
                return pk::encode("�뺴�� ������ ��Ұ� �����ϴ�.");
			else if (force.tp < TP_COST)
                return pk::encode(pk::format("�ⱳP�� �����մϴ�.(�ⱳP {})", TP_COST));
            else if (pk::get_district(pk::get_district_id(force, 1)).ap < ACTION_COST)
                return pk::encode(pk::format("�ൿ���� �����մϴ�.(�ൿ�� {} �ʿ�)", ACTION_COST));
			else
				return pk::encode(pk::format("�̹��� �뺴�� ����մϴ�.(�ⱳP {} ���)", TP_COST));
		}

		bool isEnabled_������()
		{
			if (building_gold < GOLD_COST) return false;
			else if (!taishu_building.has_skill(Ư��_ģ��)) return false;
            else if (getEmptyPos(taishu_building) == -1) return false;
            else if (force.tp < TP_COST) return false;
            else if (pk::get_district(pk::get_district_id(force, 1)).ap < ACTION_COST) return false;
			return true;
		}

		bool handler_������()
		{
			
			if (pk::choose(pk::encode("�̹����� ����Ͻðڽ��ϱ�?"), { pk::encode("��"), pk::encode("�ƴϿ�") }) == 1)
				return false;

			if (pk::rand_bool(������Ȯ��) or getEmptyPerson() is null)
			{
				int iminzoku_id = ����_�����θ�;
				int face_no = 685;
				failOrNull_iminzoku(iminzoku_id, face_no);	
			} 
			
			else 
			{ 
				���������� = true;
				set_iminzoku(); 
			}

			return true;
		}
		
		
		void failOrNull_iminzoku(int iminzoku_id, int face_no)
		{
			
			string taishu_name = pk::decode(pk::get_name(taishu));
			pk::person@ iminzoku = pk::get_person(iminzoku_id);
			
			iminzoku.face = face_no;
			iminzoku.update();

			pk::message_box(pk::encode(pk::format("�̾������� ������ �츮�� \x1b[1x{}\x1b[0x���� ���� ������ ����.", taishu_name)), iminzoku);
			pk::message_box(pk::encode("��.. �׷��ٸ� ��¿ �� ������."), taishu);
			pk::message_box(pk::encode(pk::format("��� ��� \x1b[1x{}\x1b[0x������ ���Ǹ� �����Ͽ� ������ �����ְڼ�.", taishu_name)), iminzoku);
			pk::message_box(pk::encode("����, �׷��� ���� ������� ������ ���� ���̱���."), taishu);
			
			pk::message_box(pk::encode("�̹��� �뺴 ��뿡 �����Ͽ����ϴ�."));
			
			// �ⱳ ���� �� ���� ����
			pk::message_box(pk::encode(pk::format("�ⱳ ����Ʈ�� \x1b[1x{}\x1b[0x��ŭ �����߽��ϴ�.", TP_COST)));
			pk::add_tp(force, -TP_COST, force.get_pos());
			pk::message_box(pk::encode(pk::format("������ \x1b[1x{}\x1b[0x��ŭ �����߽��ϴ�.", ADD_FOOD)));
			pk::add_food(city, ADD_FOOD, true);

			
			// �ൿ�� ����.
			auto district = pk::get_district(pk::get_district_id(force, 1));
			district.ap -= ACTION_COST;
			
		} // void failOrNull_iminzoku(pk::person@ iminzoku)


		void set_iminzoku()
		{
			
			string taishu_name = pk::decode(pk::get_name(taishu));
			pk::person@ iminzoku = getEmptyPerson();
					
			int district_num = pk::get_district_id(force, 1);
		
			pk::set_district(iminzoku, district_num);

			iminzoku.sex = ����_��;
			
			if (�̸��ڵ�)
			{
				iminzoku.sei = pk::get_family_name(random(����_�� - 1)).name; // ��
				iminzoku.mei = pk::get_family_name(random(����_�� - 1)).name; // ��
			}
			
			if (�̸�����)
			{
				iminzoku.sei = pk::encode(sei_[random(i, j)]); // ��
				iminzoku.mei = pk::encode(mei_[random(i, j)]); // ��
			}
			
			
			if (��������) { iminzoku.face = 681; } // ��ȯ�� �� ����
			if (��ȯ������) { iminzoku.face = 679; } // ��ȯ�� �� ����
			if (���������) { iminzoku.face = 683; } // ����� �� ����
			if (����������) { iminzoku.face = 685; } // ������ �� ����
			
			// ����/��ȯ�� ���� ����, ���� ����
			if (�������� or ��ȯ������)
			{
				// ���� ����
				iminzoku.skeleton = 0;
				iminzoku.body[0] = 71;
				iminzoku.body[1] = 71;
				iminzoku.body[2] = 71;
				iminzoku.body[3] = 71;
				iminzoku.body[4] = 71;
				iminzoku.body[5] = 71;
				
				// ���� ����.
				iminzoku.tekisei[����_�⺴] = ����_S;
				iminzoku.tekisei[����_â��] = random(0, 2);
				iminzoku.tekisei[����_�غ�] = random(0, 2);
				iminzoku.tekisei[����_�뺴] = random(0, 2);
				iminzoku.tekisei[����_����] = random(0, 2);
				iminzoku.tekisei[����_����] = random(0, 2);
			}

			// �����/������ ���� ����, ���� ����
			if (��������� or ����������)
			{
				// ���� ����
				iminzoku.skeleton = 2;
				iminzoku.body[0] = 72;
				iminzoku.body[1] = 72;
				iminzoku.body[2] = 72;
				iminzoku.body[3] = 72;
				iminzoku.body[4] = 72;
				iminzoku.body[5] = 72;
				
				// ���� ����.
				iminzoku.tekisei[����_�غ�] = ����_S;
				iminzoku.tekisei[����_�⺴] = random(0, 2);
				iminzoku.tekisei[����_â��] = random(0, 2);
				iminzoku.tekisei[����_�뺴] = random(0, 2);
				iminzoku.tekisei[����_����] = random(0, 2);
				iminzoku.tekisei[����_����] = random(0, 2);	
			}

			iminzoku.mibun = �ź�_�Ϲ�;
			iminzoku.loyalty = 100;
			iminzoku.rank = -1;
			iminzoku.birth = pk::get_year() - 30;
			iminzoku.death = pk::min(353, iminzoku.birth + 99);
			iminzoku.appearance = pk::get_year() - 10;
			iminzoku.kouseki = 1000;
			
			// ģ�ֹ���, �������� �ʱ�ȭ
			for (int i = 0; i < 5; i++)
			{
				iminzoku.liked[i] = -1;
				iminzoku.disliked[i] = -1;
			}
			
			iminzoku.liked[0] = force.kunshu;
			
			iminzoku.birthplace = random(��_�� - 1);
			iminzoku.skill = random(Ư��_��) - 1;
			iminzoku.wadai = random(ȭ��_�� - 1);
			iminzoku.giri = random(�Ǹ�_�� - 1);
			iminzoku.ambition = random(�߸�_�� - 1);
			iminzoku.promotion = random(���_�� - 1);
			iminzoku.character = random(����_�� - 1);
			iminzoku.voice = iminzoku.sex == ����_�� ? random(����_�ҽɳ�, ����_������) : random(����_������, ����_����);
			iminzoku.tone = iminzoku.sex == ����_�� ? random(����_���, ����_���볲) : random(����_��븸��, ����_�����);
			iminzoku.kanshitsu = random(�ѽ�_�� - 1);
			iminzoku.strategic_tendency = random(��������_�� - 1);
			iminzoku.local_affiliation = random(��������_�� - 1);
			
			int random_n = pk::rand(4); // 0, 1, 2, 3
				
			for (int i = 0; i < ����ɷ�_��; i++)
			{
				
				// 0-������, 1-������, 2-������, 3-RANDOM 
				
				// 0-������
				if (random_n == 0)
				{
					
					if (i == ����ɷ�_���)
					{
						iminzoku.base_stat[i] = random(min_stat_������_���, max_stat_������_���);
					}
					
					else if (i == ����ɷ�_����)
					{
						iminzoku.base_stat[i] = random(min_stat_������_����, max_stat_������_����);
					}
					
					else if (i == ����ɷ�_����)
					{
						iminzoku.base_stat[i] = random(min_stat_������_����, max_stat_������_����);
					}
					
					else if (i == ����ɷ�_��ġ)
					{
						iminzoku.base_stat[i] = random(min_stat_������_��ġ, max_stat_������_��ġ);
					}
					
					else
					{
						iminzoku.base_stat[i] = random(min_stat_�ŷ�, max_stat_�ŷ�);
					}

				} // if (random_n == 0)

				// 1-������
				else if (random_n == 1)
				{
					
					if (i == ����ɷ�_���)
					{
						iminzoku.base_stat[i] = random(min_stat_������_���, max_stat_������_���);
					}
					
					else if (i == ����ɷ�_����)
					{
						iminzoku.base_stat[i] = random(min_stat_������_����, max_stat_������_����);
					}
					
					else if (i == ����ɷ�_����)
					{
						iminzoku.base_stat[i] = random(min_stat_������_����, max_stat_������_����);
					}
					
					else if (i == ����ɷ�_��ġ)
					{
						iminzoku.base_stat[i] = random(min_stat_������_��ġ, max_stat_������_��ġ);
					}
					
					else
					{
						iminzoku.base_stat[i] = random(min_stat_�ŷ�, max_stat_�ŷ�);
					}
					
				} // else if (random_n == 1)
				
				// 2-������
				else if (random_n == 2)
				{
					
					if (i == ����ɷ�_���)
					{
						iminzoku.base_stat[i] = random(min_stat_������_���, max_stat_������_���);
					}
					
					else if (i == ����ɷ�_����)
					{
						iminzoku.base_stat[i] = random(min_stat_������_����, max_stat_������_����);
					}
					
					else if (i == ����ɷ�_����)
					{
						iminzoku.base_stat[i] = random(min_stat_������_����, max_stat_������_����);
					}
					
					else if (i == ����ɷ�_��ġ)
					{
						iminzoku.base_stat[i] = random(min_stat_������_��ġ, max_stat_������_��ġ);
					}
					
					else
					{
						iminzoku.base_stat[i] = random(min_stat_�ŷ�, max_stat_�ŷ�);
					}
					
				} // else if (random_n == 2)
					
				// 3-RANDOM
				else if (random_n == 3)
				{
					iminzoku.base_stat[i] = random(1, 100);
				} 
				
				iminzoku.stat_aging[i] = random(�ɷ¼���_��������, �ɷ¼���_�����);
			}
			
			// �ɷ�ġ �ݿ�.
			iminzoku.update();
			
			int gold = 1000;
			int food = int(troops * 1.3f);
			
			
			// ������ �δ� �������� ���� ������ �δ븦 �������� �ʴ´�.		
			pk::point emptyPos = getEmptyPos(taishu_building);
			
			if (!pk::is_valid_pos(emptyPos)) return;
				
			pk::unit@ unit = pk::create_unit(taishu_building, iminzoku, null, null, troops, ����_��, ����_�ְ�, gold, food, emptyPos);

			// ��� ����(pk::create_unit �Լ��� ù ��° �Ķ���ͷ� �����ߴٸ� �ʿ����.)
			unit.energy = 100;
			
			// �δ� �̵� �Ұ� �� �δ� �� ���� ���� �� �ߴ�
			if (pk::get_movable_pos(unit).length == 0) {pk::kill(unit);	pk::reset(iminzoku);	return;}

			// �δ� ���� ���� �� �δ� �� ���� ���� �� �ߴ�
			if (!pk::is_alive(unit)) {pk::kill(unit); pk::reset(iminzoku);}
			
			string iminzoku_name = pk::decode(pk::get_name(iminzoku));
			
			pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x��, �̰����� ������ ���� �����̼�.", iminzoku_name)), taishu);
			pk::message_box(pk::encode(pk::format("������! \x1b[1x{}\x1b[0x���� ���ؼ� �ο� �غ� �Ǿ� ������ �������ʽÿ�!", taishu_name)), iminzoku);
			pk::message_box(pk::encode("�̰��� ���� ������ �밡�� �ִ� �����̿�."), taishu);
			pk::message_box(pk::encode("��! �̷��Գ� ���� ���� �ֽôٴ� �����մϴ�."), iminzoku);
			pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x���� ������ �� ���� �ʰڼ�.", iminzoku_name)), taishu);
			
			pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x(��)�� �Ʊ����� �շ��Ͽ����ϴ�.", iminzoku_name)));
				
			// �ⱳ �� �� ����
			pk::message_box(pk::encode(pk::format("�ⱳ ����Ʈ�� \x1b[1x{}\x1b[0x��ŭ �����߽��ϴ�.", TP_COST)));
			pk::add_tp(force, -TP_COST, force.get_pos());
			pk::message_box(pk::encode(pk::format("������ ���� \x1b[1x{}\x1b[0x��ŭ �����߽��ϴ�.", GOLD_COST)));
			pk::add_gold(city, -GOLD_COST, true);
			
			// �ൿ�� ����.
			auto district = pk::get_district(pk::get_district_id(force, 1));
			district.ap -= ACTION_COST;
			
			�������� = false;
			��ȯ������ = false;
			��������� = false;
			���������� = false;
			
		} // set_iminzoku()
		
		
		pk::point getEmptyPos(pk::building@ building)
		{
			auto arr = pk::range(building.get_pos(), min_distance, max_distance);
			for (int i = 0; i < arr.length; i++)
			{
				pk::hex@ hex = pk::get_hex(arr[i]);
				int terrain_id = hex.terrain;
				
				if (!hex.has_building and !hex.has_unit
					and pk::is_valid_terrain_id(terrain_id) 
					and pk::is_enabled_terrain(terrain_id)
					and terrain_id != ����_��)
					return arr[i];
				
			}
			return -1;
		}
		
		
		pk::person@ getEmptyPerson()
		{
			if (slot_�Ϲݹ���)
			{
				for (int i = 0; i < 700; i++)
				{
					
					pk::person@ iminzoku = pk::get_person(i);
					
					switch (iminzoku.mibun)
					{
					case �ź�_����:
					case �ź�_���:
						return iminzoku;
					}

				}
			}
			
			if (slot_�Ź���)
			{
				for (int i = 960; i < �Ź���_��; i++)
				{
					pk::person@ iminzoku = pk::get_person(i);
					switch (iminzoku.mibun)
					{
					case �ź�_����:
					case �ź�_�̵���:
					case �ź�_���:
						return iminzoku;
					}
				}
			}
			
			if (slot_��빫��)
			{
				for (int i = 832; i < 850; i++)
				{
					pk::person@ iminzoku = pk::get_person(i);
					switch (iminzoku.mibun)
					{
					case �ź�_����:
					case �ź�_�̵���:
					case �ź�_���:
						return iminzoku;
					}
				}
			}
			
			return null;
			
		} // pk::person@ getEmptyPerson()
		

	}

	Main main;
}