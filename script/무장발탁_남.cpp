/*     
@������: HoneyBee    
@����: [�ﱹ��9PK, �ﱹ��12PK]���� ������ ��Ź�ϴ� �ý����� �����Ͽ� ������ SCRIPT (50% Ȯ���� ���� ��Ź ����)   

      -> ���� ��Ź�� �����ϸ� ��ſ� ������ ȹ���ϰ� ���� �Һ���� �ʽ��ϴ�. 
	 
*/
 
namespace �����Ź_������
{
	
	// ========================== CUSTOMIZE ===============================
	
		const int TP_COST = 500; 		// �ⱳP ��ġ ����
		const int ACTION_COST = 50;     // �ൿ�� �ʿ䷮
		const int GOLD_COST = 3000;     // �� �ʿ䷮
		const int ADD_FOOD = 10000;     // ��Ź ���� ��ſ� ȹ���ϴ� ����
		
		const int ��Ź����Ȯ�� = 50;    		// �����Ź�� ������ Ȯ�� (�⺻ ���� - 50%)
		
		
		/* 
		   ��Ź ������ 4���� �� �� ���� TYPE�� �����˴ϴ�.
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
		const int min_stat_�ŷ� = 30;   	   // ��Ź ������ �ּ� �ŷ� �ɷ�ġ�� ���� (�⺻ ���� - 30)
		const int max_stat_�ŷ� = 90;        // ��Ź ������ �ִ� �ŷ� �ɷ�ġ�� ���� (�⺻ ���� - 90)
		
		
		const bool �̸��ڵ� = false;	       // ���� �̸��� �ڵ����� ����	[�̸��ڵ� true�Ͻ�, �̸����� false�� ����]
		const bool �̸����� = true;           // ���� �̸��� ����(�迭 �ۼ�)���� ���� [�̸����� true�Ͻ�, �̸��ڵ� false�� ����]
		

		// === ��Ź���� SLOT ���� ���� (�߿�) === ��
		
		/* 
		   - ������ SLOT�� ���� (�ݵ�� 2���� �� �� ������ true, �������� false�� �����ؾߵ�)
		   - slot_�Ź����� Gold Edition Patch���� ������ �Ź����� ������ ���� �⺻���� ������
		   - Gold Edition Patch ���� ��ϵ� �Ź����� 850 ~ 934 �̹Ƿ�, 935���� ��Ź ������ �ۼ��ϵ��� �⺻ ���� (���� 935 ~ 967���� ������)
		   - Gold Edition Patch ���� ��ϵ� �Ź����� 850 ~ 934 �̹Ƿ�, 935���� ��Ź ������ �ۼ��ϵ��� �⺻ ���� (ҳ�� 968 ~ 999���� ������)
		
		*/
		
		// �Ź��� SLOT�� ����Ͽ� ��Ź���� �߰� (����: �Ź����� SLOT�� ����ϹǷ�, �Ź����� ���� �������� ��� ����õ)
		const bool slot_�Ź��� = true;
		
		// �Ϲݹ���(�̹� ����ϰų� �źо��� ����) SLOT�� ����Ͽ� ��Ź���� �߰� (����: ����� ������ ���ٸ�, SLOT�� ������ ŭ)
		const bool slot_�Ϲݹ��� = false;
		
		// �̻�� ��빫�� SLOT�� ����Ͽ� ��Ź���� �߰� (����: SLOT�� ������ ŭ, �ִ� 18��)
		const bool slot_��빫�� = false;

		// ============================== ��		
	
	
		/* 
		
			��Ź ���� �̸��� ARRAY�� �̸� SETTING �Ͻñ� �ٶ��ϴ�. (�Ʒ��� �ӽ÷� ���� �����Դϴ�.)
			�Ʒ� ������ RANDOM���� ����Ͽ� ��Ź ������ �̸��� �������ϴ�.
			
			EX) ����, ����, ����, ����, ����, ��Ź, �հ�, ��Ź, ���� ��..
		
		*/
		
		// ��Ź ���� [��] (�ӽ÷� 40�� ����)
		array<string> sei_ = { "��", "��", "��", "��", "��", "����", "ȭ", "��", "��", "��",
                               "��", "��", "��", "����", "��", "��", "��", "��", "��", "��",
							   "��", "��", "��", "��", "��", "��", "ȭ", "��", "��", "Ȳ",
							   "��", "��", "��", "��", "��", "��", "��", "��", "����", "�縶" }; 	 

	    // ��Ź ���� [�̸�] (�ӽ÷� 40���� ����)
		array<string> mei_ = { "��", "��", "��", "Ź", "��", "��", "��", "��", "��", "��", 
		                       "��", "��", "â", "��", "��", "��", "��", "Ȳ", "��", "��",
							   "��", "��", "ȫ", "��", "��", "��", "��", "��", "��", "��",
							   "��", "��", "��", "��", "��", "��", "��", "��", "��", "��" }; 
		
		
		// EX) { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ... 39 } <- TOTAL 40�� (ARRAY���� [��], [�̸�]�� �ø� ������ ������ ������ �����Ͻø� �˴ϴ�.)
		int i = 0;   // �迭�� FIRST NUMBER 
		int j = 39;  // �迭�� LAST NUMBER
		
	
	// ====================================================================
	
	
	const int KEY = pk::hash("��Ź(��)");
	
	
	class Main
	{
		pk::building@ building_;
		pk::person@ kunshu_;
		pk::force@ force_;
		pk::city@ city_;
		uint16 building_gold;
		uint16 building_food;
		
		Main()
		{
			pk::menu_item item;
			item.menu = 102;
			item.pos = 6;
			item.shortcut = "6";
			item.init = pk::building_menu_item_init_t(init);
			item.is_enabled = pk::menu_item_is_enabled_t(isEnabled);
			item.get_text = pk::menu_item_get_text_t(getText);
			item.get_desc = pk::menu_item_get_desc_t(getDesc);
			item.handler = pk::menu_item_handler_t(handler);
			pk::add_menu_item(item);
		}

		void init(pk::building@ building)
		{
			@building_ = @building;
			@force_ = pk::get_force(building.get_force_id());
			@kunshu_ = pk::get_person(force_.kunshu);
			@city_ = pk::building_to_city(building_);
			building_gold = pk::get_gold(building);
		}


		bool isEnabled()
		{
			if (building_gold < GOLD_COST) return false;
            else if (force_.tp < TP_COST) return false;
            else if (pk::get_district(pk::get_district_id(force_, 1)).ap < ACTION_COST) return false;
			return true;
		}
		
		string getText()
		{
			return pk::encode("��Ź(��)");
		}
		
		string getDesc()
		{
			if (building_gold < GOLD_COST)
                return pk::encode(pk::format("���� �����մϴ�.(�� {} �ʿ�)", GOLD_COST));
			else if (force_.tp < TP_COST)
                return pk::encode(pk::format("�ⱳP�� �����մϴ�.(�ⱳP {})", TP_COST));
            else if (pk::get_district(pk::get_district_id(force_, 1)).ap < ACTION_COST)
                return pk::encode(pk::format("�ൿ���� �����մϴ�.(�ൿ�� {} �ʿ�)", ACTION_COST));
			else
				return pk::encode(pk::format("������ ��Ź�մϴ�.(�ⱳP {} ���)", TP_COST));
		}

		bool handler()
		{
			
			pk::random random(pk::rand());
			
			if (pk::choose(pk::encode("������ ��Ź�Ͻðڽ��ϱ�?"), { pk::encode("��"), pk::encode("�ƴϿ�") }) == 1)
				return false;
			
			string kunshu_name = pk::decode(pk::get_name(kunshu_));			
			pk::person@ person_2 = pk::get_person(����_����);


			if (pk::rand_bool(��Ź����Ȯ��) or getEmptyPerson() is null)
			{
				pk::message_box(pk::encode("�ְ�, �� �������� �ҹ��� ���縦 ã�ư����� �̹� �ٸ� �������� �����ٰ� �մϴ�."), person_2);
				pk::message_box(pk::encode("��.. �װ� �� �ƽ��� �Ǿ���.\n�ƹ�ư �����߳�."), kunshu_);
				pk::message_box(pk::encode("��ſ� �� ���� ������� ��� �ְ��� ������ �����ϰ��� ������ ���½��ϴ�."), person_2);
				pk::message_box(pk::encode("����, �׷��� �ڳװ� ������� ������ ���� ���̱�."), kunshu_);

				pk::message_box(pk::encode("���� ��Ź�� �����Ͽ����ϴ�."));
				
				// �ⱳ ���� �� ���� ����
				pk::message_box(pk::encode(pk::format("�ⱳ ����Ʈ�� \x1b[1x{}\x1b[0x��ŭ �����߽��ϴ�.", TP_COST)));
				pk::add_tp(force_, -TP_COST, force_.get_pos());
				pk::message_box(pk::encode(pk::format("������ \x1b[1x{}\x1b[0x��ŭ �����߽��ϴ�.", ADD_FOOD)));
				pk::add_food(city_, ADD_FOOD, true);
				
				// �ൿ�� ����.
				auto district = pk::get_district(pk::get_district_id(force_, 1));
				district.ap -= ACTION_COST;	
				
			}
			
			else 
			{
				
				pk::person@ new_face = getEmptyPerson();
				
				new_face.sex = ����_��;
				
				if (�̸��ڵ�)
				{
					new_face.sei = pk::get_family_name(random(����_�� - 1)).name; // ��
					new_face.mei = pk::get_family_name(random(����_�� - 1)).name; // ��
				}
				
				if (�̸�����)
				{
					new_face.sei = pk::encode(sei_[random(i, j)]); // ��
					new_face.mei = pk::encode(mei_[random(i, j)]); // ��
				}
		
				new_face.face = random(2000, 2099);
				new_face.appearance = pk::get_year();
				new_face.birth = pk::get_year() - 17 - random(4);
				new_face.death = pk::min(353, new_face.birth + 70 + random(20));
				new_face.ketsuen = new_face.get_id();
				new_face.aishou = random(0, 150);
				new_face.mibun = �ź�_�Ϲ�;
				new_face.loyalty = 100;
				
				// ģ�ֹ���, �������� �ʱ�ȭ
				for (int i = 0; i < 5; i++)
				{
					new_face.liked[i] = -1;
					new_face.disliked[i] = -1;
				}
				
				new_face.liked[0] = force_.kunshu;
				
				// ���� ����.
				new_face.tekisei[����_�⺴] = random(0, 2);
				new_face.tekisei[����_â��] = random(0, 2);
				new_face.tekisei[����_�غ�] = random(0, 2);
				new_face.tekisei[����_�뺴] = random(0, 2);
				new_face.tekisei[����_����] = random(0, 2);
				new_face.tekisei[����_����] = random(0, 2);
				
				int random_n = pk::rand(4); // 0, 1, 2, 3
				
				for (int i = 0; i < ����ɷ�_��; i++)
				{
					
					// 0-������, 1-������, 2-������, 3-RANDOM 
					
					// 0-������
					if (random_n == 0)
					{
						
						if (i == ����ɷ�_���)
						{
							new_face.base_stat[i] = random(min_stat_������_���, max_stat_������_���);
						}
						
						else if (i == ����ɷ�_����)
						{
							new_face.base_stat[i] = random(min_stat_������_����, max_stat_������_����);
						}
						
						else if (i == ����ɷ�_����)
						{
							new_face.base_stat[i] = random(min_stat_������_����, max_stat_������_����);
						}
						
						else if (i == ����ɷ�_��ġ)
						{
							new_face.base_stat[i] = random(min_stat_������_��ġ, max_stat_������_��ġ);
						}
						
						else
						{
							new_face.base_stat[i] = random(min_stat_�ŷ�, max_stat_�ŷ�);
						}

					} // if (random_n == 0)

					// 1-������
					else if (random_n == 1)
					{
						
						if (i == ����ɷ�_���)
						{
							new_face.base_stat[i] = random(min_stat_������_���, max_stat_������_���);
						}
						
						else if (i == ����ɷ�_����)
						{
							new_face.base_stat[i] = random(min_stat_������_����, max_stat_������_����);
						}
						
						else if (i == ����ɷ�_����)
						{
							new_face.base_stat[i] = random(min_stat_������_����, max_stat_������_����);
						}
						
						else if (i == ����ɷ�_��ġ)
						{
							new_face.base_stat[i] = random(min_stat_������_��ġ, max_stat_������_��ġ);
						}
						
						else
						{
							new_face.base_stat[i] = random(min_stat_�ŷ�, max_stat_�ŷ�);
						}
						
					} // else if (random_n == 1)
					
					// 2-������
					else if (random_n == 2)
					{
						
						if (i == ����ɷ�_���)
						{
							new_face.base_stat[i] = random(min_stat_������_���, max_stat_������_���);
						}
						
						else if (i == ����ɷ�_����)
						{
							new_face.base_stat[i] = random(min_stat_������_����, max_stat_������_����);
						}
						
						else if (i == ����ɷ�_����)
						{
							new_face.base_stat[i] = random(min_stat_������_����, max_stat_������_����);
						}
						
						else if (i == ����ɷ�_��ġ)
						{
							new_face.base_stat[i] = random(min_stat_������_��ġ, max_stat_������_��ġ);
						}
						
						else
						{
							new_face.base_stat[i] = random(min_stat_�ŷ�, max_stat_�ŷ�);
						}
						
					} // else if (random_n == 2)
						
					// 3-RANDOM
					else if (random_n == 3)
					{
						new_face.base_stat[i] = random(1, 100);
					} 
					
					new_face.stat_aging[i] = random(�ɷ¼���_��������, �ɷ¼���_�����);
				}
				
				new_face.birthplace = random(��_����, ��_����);
				new_face.skill = random(Ư��_����, Ư��_����);
				new_face.wadai = random(ȭ��_���, ȭ��_����);
				new_face.giri = random(�Ǹ�_�ſ쳷��, �Ǹ�_�ſ����);
				new_face.ambition = random(�߸�_�ſ쳷��, �߸�_�ſ����);
				new_face.promotion = random(���_�ɷ�, ���_����);
				new_face.character = random(����_�ҽ�, ����_����);
				new_face.voice = random(����_�ҽɳ�, ����_������);
				new_face.tone = random(����_���, ����_���볲);
				new_face.kanshitsu = random(�ѽ�_����, �ѽ�_�߽�);
				new_face.strategic_tendency = random(��������_��ȭ����, ��������_��������);
				new_face.local_affiliation = random(��������_�����߽�, ��������_��������);
				
				// ������ ���� ����
				if (random_n == 0)
				{
					new_face.body[0] = 102; // ����
					new_face.body[1] = 84;  // ��
					new_face.body[2] = 85;  // ��ü
					new_face.body[3] = 85;  // ����
					new_face.body[4] = 85;  // ��
					new_face.body[5] = 85;  // �ٸ� 
				}
				
				// ������ ���� ����
				else if (random_n == 1)
				{
					new_face.body[0] = 92; // ����
					new_face.body[1] = 93;  // ��
					new_face.body[2] = 97;  // ��ü
					new_face.body[3] = -1;  // ����
					new_face.body[4] = 97;  // ��
					new_face.body[5] = 97;  // �ٸ�
				}
				
				else 
				{
					new_face.body[0] = 102; // ����
					new_face.body[1] = 84;  // ��
					new_face.body[2] = 85;  // ��ü
					new_face.body[3] = 85;  // ����
					new_face.body[4] = 85;  // ��
					new_face.body[5] = 85;  // �ٸ� 
				}

				// ȭ�� ȹ�� Ȯ��
				int wajutsu_daikatsu_0 = 30;
				int wajutsu_kiben_0 = 30;
				int wajutsu_mushi_0 = 30;
				int wajutsu_chinsei_0 = 30;
				int wajutsu_gyakujou_0 = 30;
						
				if (pk::rand_bool(wajutsu_daikatsu_0))
				{
					new_face.wajutsu_daikatsu = true;
				}
				
				if (pk::rand_bool(wajutsu_kiben_0))
				{
					new_face.wajutsu_kiben = true;
				}
				
				if (pk::rand_bool(wajutsu_mushi_0))
				{
					new_face.wajutsu_mushi = true;
				}
				
				if (pk::rand_bool(wajutsu_chinsei_0))
				{
					new_face.wajutsu_chinsei = true;
				}
				
				if (pk::rand_bool(wajutsu_gyakujou_0))
				{
					new_face.wajutsu_gyakujou = true;
				}
				
				pk::set_district(new_face, building_.get_district_id()); 
				new_face.update();
				
				string newface_name = pk::decode(pk::get_name(new_face));	
				
				pk::message_box(pk::encode(pk::format("�ְ�, �� �������� ������ ������ \x1b[1x{}\x1b[0x���� ��ſԽ��ϴ�.", newface_name)), person_2);
				pk::message_box(pk::encode("��, �׷� �����߳�. ��, ����ÿ�."), kunshu_);
				pk::message_box(pk::encode(pk::format("�ȳ��Ͻʴϱ�. \x1b[1x{}\x1b[0x���� �˰� �Ǿ� �����Դϴ�.", kunshu_name)), new_face);
				pk::message_box(pk::encode("�״뿡 ���� �ҹ��� ���ۺ��� ��� �־���. ������ ���� �����ֽðڼ�?"), kunshu_);
				pk::message_box(pk::encode(pk::format("��, ���� �ɷ��� �˾ƺ��ֽ� \x1b[1x{}\x1b[0x���� ���ؼ� �Ÿ��� ��ġ�ڽ��ϴ�.", kunshu_name)), new_face);
				pk::message_box(pk::encode("��, �׸��� �̰��� ��������� �״뿡�� �ִ� ���ǿ�."), kunshu_);
				pk::message_box(pk::encode("�̷��� ���� ���� �ֽôٴ� �����մϴ�."), new_face);
				pk::message_box(pk::encode("���߸��� �״밡 �츮���� �շ����شٴ� ����. ������ �״븦 �߿��ϰڼ�."), kunshu_);
				
				pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x(��)�� �Ʊ����� �շ��߽��ϴ�.", newface_name)));
				
				// �ⱳ �� �� ����
				pk::message_box(pk::encode(pk::format("�ⱳ ����Ʈ�� \x1b[1x{}\x1b[0x��ŭ �����߽��ϴ�.", TP_COST)));
				pk::add_tp(force_, -TP_COST, force_.get_pos());
				pk::message_box(pk::encode(pk::format("������ ���� \x1b[1x{}\x1b[0x��ŭ �����߽��ϴ�.", GOLD_COST)));
				pk::add_gold(city_, -GOLD_COST, true);
				
				// �ൿ�� ����.
				auto district = pk::get_district(pk::get_district_id(force_, 1));
				district.ap -= ACTION_COST;	
				
				pk::sort(pk::person::type_id);
				pk::move(new_face, building_);
				
			}	

			return true;
		}
		
		
		/**
		@details
			�� ����ĭ�� �Ʒ��� ������� Ȯ���� ���� ������.
			1.  850 ~  999(�Ź���)
			2.  832 ~  849(������� �ʴ� ��� ����)
			3.  670 ~  699(������� �ʴ� ��� ����)
			4.  800 ~  831(��� ����)
			5.    0 ~  670(���� ����)
			6. 1000 ~ 1099(����). pk::create_bandit �Լ����� ����ϴ� ������.
			7.  700 ~  799(�̺�Ʈ ����). �źп� ������� pk::is_alive �Լ��� �׻� true�� �����ϴ� ������.

			����� ������ ��Ȱ��Ű�� ��ũ��Ʈ�� �ִٸ� "case �ź�_���:" �κ��� ����.
		*/
		
		/*
		bool getEmptyPerson()
		{
			for (int i = 1000; i < 1099; i++)
			{
				pk::person@ new_face = pk::get_person(i);

				switch (new_face.mibun)
				{
					case �ź�_����	:
					case �ź�_�̵���:
					case �ź�_�̹߰�:
					case �ź�_���	:
						return true;
				}

			}
			return false;
		}
		*/
		
		pk::person@ getEmptyPerson()
		{
			if (slot_�Ϲݹ���)
			{
				for (int i = 0; i < 700; i++)
				{
					
					pk::person@ new_face = pk::get_person(i);
					
					switch (new_face.mibun)
					{
					case �ź�_����:
					case �ź�_���:
						return new_face;
					}

				}
			}
			
			if (slot_�Ź���)
			{
				for (int i = 960; i < 979; i++)
				{
					pk::person@ new_face = pk::get_person(i);
					switch (new_face.mibun)
					{
					case �ź�_����:
					case �ź�_�̵���:
					case �ź�_���:
						return new_face;
					}
				}
			}
			
			if (slot_��빫��)
			{
				for (int i = 832; i < 850; i++)
				{
					pk::person@ new_face = pk::get_person(i);
					switch (new_face.mibun)
					{
					case �ź�_����:
					case �ź�_�̵���:
					case �ź�_���:
						return new_face;
					}
				}
			}
			
			return null;
			
		} // pk::person@ getEmptyPerson()
		
	}

	Main main;
}