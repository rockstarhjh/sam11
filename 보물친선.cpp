/*
@������: ũ���Ƚ�
@Update: 2023.9.1, ���ʹ���
*/
namespace ����ģ��
{
	//������, ���̺�/�ε峪 �����Ѿ� �ΰ������� ����˴ϴ�.
	//���� ��� ��õȭ�ؿ� ������3 �پ� �ִµ� �ٷ� �ݿ����� �ʽ��ϴ�.
	class ItemGiveInfo
	{
		pk::person@ person;
		pk::item@ item;
	}
	
	//��ο� ������ ������ �����̹����� �ȳ��û� �������� �ʽ��ϴ�.
	const array<string> �����̹��� =
	{
		"Ebony_����\\���丶.png",
		"Ebony_����\\����.png",
		"Ebony_����\\��Ȳ����.png",
		"Ebony_����\\����.png",
		"Ebony_����\\��ϸ�.png",
		"Ebony_����\\��ϸ�.png",
		"Ebony_����\\��ϸ�.png",
		"Ebony_����\\ĥ������.png",
		"Ebony_����\\��õ��.png",
		"Ebony_����\\û����.png",
		
		"Ebony_����\\�ְ��.png",
		"Ebony_����\\��õȭ��.png",
		"Ebony_����\\û������.png",
		"Ebony_����\\���Ȼ��.png",
		"Ebony_����\\��û��.png",
		"Ebony_����\\��.png",
		"Ebony_����\\��.png",
		"Ebony_����\\�ܱ�.png",
		"Ebony_����\\�ܱ�.png",
		"Ebony_����\\����.png",
		
		"Ebony_����\\����.png",
		"Ebony_����\\ö��.png",
		"Ebony_����\\��������-��.png",
		"Ebony_����\\�̱���-��.png",
		"Ebony_����\\�ܱ�.png",
		"Ebony_����\\�ܱ�.png",
		"Ebony_����\\��ȣ���.png",
		"Ebony_����\\��ȣ���.png",
		"Ebony_����\\�Ʊ�.png",
		"Ebony_����\\�Ʊ�.png",
		
		"Ebony_����\\���ں���.png",
		"Ebony_����\\����24��.png",
		"Ebony_����\\�ʹ��ż�.png",
		"Ebony_����\\����.png",
		"Ebony_����\\�﷫.png",
		"Ebony_����\\����.png",
		"Ebony_����\\������.png",
		"Ebony_����\\����å.png",
		"Ebony_����\\�縶��.png",
		"Ebony_����\\����.png",

		"Ebony_����\\��������.png",
		"Ebony_����\\����.png",
		"Ebony_����\\����.png",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		
		"Ebony_����\\������뱸.png",
		"Ebony_����\\�Ǹ����丶.png",
		"Ebony_����\\�����鸶.png",
		"Ebony_����\\�鸶.png",
		"Ebony_����\\�����.png",
		"Ebony_����\\��ȯ��.png",
		"Ebony_����\\��븶.png",
		"Ebony_����\\�����.png",
		"Ebony_����\\���.png",
		"Ebony_����\\�����.png",

		"Ebony_����\\����.png",
		"Ebony_����\\����.png",
		"Ebony_����\\������.png",
		"Ebony_����\\���ǵ�.png",
		"Ebony_����\\�ŵ�.png",
		"Ebony_����\\������.png",
		"Ebony_����\\��ġ��.png",
		"Ebony_����\\ȯ����.png",
		"Ebony_����\\��ö��.png",
		"Ebony_����\\��ε�.png",

		"Ebony_����\\���뵵.png",
		"Ebony_����\\�̺ε�.png",
		"Ebony_����\\�밣��.png",
		"Ebony_����\\ġ���.png",
		"Ebony_����\\���.png",
		"Ebony_����\\öô���.png",
		"Ebony_����\\�ݸ���.png",
		"Ebony_����\\�����.png",
		"Ebony_����\\ö��.png",
		"Ebony_����\\öĥ����Ÿ.png",
		
		"Ebony_����\\ö����.png",
		"Ebony_����\\������.png",
		"Ebony_����\\��ȭ����.png",
		"Ebony_����\\����.png",
		"Ebony_����\\ö��.png",
		"Ebony_����\\����.png",
		"Ebony_����\\������.png",
		"Ebony_����\\���.png",
		"Ebony_����\\����.png",
		"Ebony_����\\������.png",

		"Ebony_����\\�ÿ��.png",
		"Ebony_����\\ġ��.png",
		"Ebony_����\\�����¾���.png",
		"Ebony_����\\�Ѻ���.png",
		"Ebony_����\\����.png",
		"Ebony_����\\�а�õ��.png",
		"Ebony_����\\����������.png",
		"Ebony_����\\�����嵵.png",
		"Ebony_����\\���߸�.png"
	};	

	const int ������ġ_��_�� = 90;
	const int ������ġ_��_�� = 60;
	const int ������ġ_��_�� = 30;
	const int ������ġ_��_�� = 90;
	const int ������ġ_��_�� = 60;
	const int ������ġ_��_�� = 30;
	const int ������ġ_��_�乫�� = 90;
	const int ������ġ_��_�乫�� = 60;
	const int ������ġ_��_�乫�� = 30;
	const int ������ġ_��_�ϱ� = 90;
	const int ������ġ_��_�ϱ� = 60;
	const int ������ġ_��_�ϱ� = 30;
	const int ������ġ_��_Ȱ = 90;
	const int ������ġ_��_Ȱ = 60;
	const int ������ġ_��_Ȱ = 30;
	const int ������ġ_��_��å = 90;
	const int ������ġ_��_��å = 60;
	const int ������ġ_��_��å = 30;


	const array<int> ������ġ = 
	{
		������ġ_��_��,
		������ġ_��_��,
		������ġ_��_��,
		������ġ_��_��,
		������ġ_��_��,
		������ġ_��_��,
		������ġ_��_��,
		������ġ_��_��,
		������ġ_��_��,
		������ġ_��_��,

		������ġ_��_��,
		������ġ_��_�乫��,
		������ġ_��_�乫��,
		������ġ_��_�乫��,
		������ġ_��_�ϱ�,
		������ġ_��_�ϱ�,
		������ġ_��_�ϱ�,
		������ġ_��_�ϱ�,
		������ġ_��_�ϱ�,
		������ġ_��_�ϱ�,

		������ġ_��_�ϱ�,
		������ġ_��_�ϱ�,
		������ġ_��_Ȱ,
		������ġ_��_Ȱ,
		������ġ_��_Ȱ,
		������ġ_��_Ȱ,
		������ġ_��_Ȱ,
		������ġ_��_Ȱ,
		������ġ_��_Ȱ,
		������ġ_��_Ȱ,

		������ġ_��_��å,
		������ġ_��_��å,
		������ġ_��_��å,
		������ġ_��_��å,
		������ġ_��_��å,
		������ġ_��_��å,
		������ġ_��_��å,
		������ġ_��_��å,
		������ġ_��_��å,
		������ġ_��_��å,

		������ġ_��_��å,
		-1,//����
		-1,//����
		-1,-1,-1,-1,-1,-1,-1,

		������ġ_��_��, //����51,
		������ġ_��_��,
		������ġ_��_��,
		������ġ_��_��,
		������ġ_��_��,
		������ġ_��_��,
		������ġ_��_��,
		������ġ_��_��,
		������ġ_��_��,
		������ġ_��_��,

		������ġ_��_��,
		������ġ_��_��,
		������ġ_��_��,
		������ġ_��_��,
		������ġ_��_��,
		������ġ_��_��,
		������ġ_��_��,
		������ġ_��_��,
		������ġ_��_�乫��,
		������ġ_��_�乫��,

		������ġ_��_�乫��,
		������ġ_��_�乫��,
		������ġ_��_�乫��,
		������ġ_��_�乫��,
		������ġ_��_�乫��,
		������ġ_��_�乫��,
		������ġ_��_�乫��,
		������ġ_��_�乫��,
		������ġ_��_�乫��,
		������ġ_��_�乫��,

		������ġ_��_�乫��,
		������ġ_��_�乫��,
		������ġ_��_�ϱ�,
		������ġ_��_�ϱ�,
		������ġ_��_�乫��,
		������ġ_��_�ϱ�,
		������ġ_��_Ȱ,
		������ġ_��_��å,
		������ġ_��_��å,
		������ġ_��_��å,

		������ġ_��_��å,
		������ġ_��_��å,
		������ġ_��_��å,
		������ġ_��_��å,
		������ġ_��_��å,
		������ġ_��_��å,
		������ġ_��_��å,
		������ġ_��_��å,
		������ġ_��_��,
		������ġ_��_��, //����99,

	};


	class Main
	{
		Main()
		{
			pk::menu_item item;
			item.menu = 103;
			item.pos = 1;
			item.init = pk::building_menu_item_init_t(����ģ��Init);
			item.is_enabled = pk::menu_item_is_enabled_t(Is����ģ��Enabled);
			item.get_text = pk::menu_item_get_text_t(����ģ��Text);
			item.get_desc = pk::menu_item_get_desc_t(����ģ��Desc);
			item.handler = pk::menu_item_handler_t(����ģ��Handler);
			pk::add_menu_item(item);
        }

		array<ItemGiveInfo> _items;

		pk::force@ _force;
		pk::building@ _building;
		pk::city@ _city;
		pk::district@ _district;
		void ����ģ��Init(pk::building@ building)
		{
			@_force = pk::get_force(building.get_force_id());
			@_building = building;
			@_city = pk::building_to_city(building);
			@_district = pk::get_district(building.get_district_id());
		}
		int GetAP()
		{
			return 30;
		}

		bool Is����ģ��Enabled()
		{
			return _district.ap >= GetAP();
		}
		string ����ģ��Text()
		{
			return pk::encode("����ģ��");
		}
		string ����ģ��Desc()
		{
			if (_district.ap < GetAP())
				return pk::encode("�ൿ���� �����մϴ�.");
			else
				return pk::encode(pk::format("Ÿ���¿� ������ �ְ� ģ���� �����մϴ�.(�ൿ��{})",GetAP()));
		}
		

		pk::item@ _scene_chooItem = null;	
		pk::person@ _scene_person = null;
		pk::force@ _scene_force= null;
		bool _scene_bool = false;
		


		void Scene_��������()
		{
			pk::background(pk::format("{}",�����̹���[_scene_chooItem.get_id()]));
			_scene_bool=pk::yes_no(pk::encode(pk::format("\x1b[2x{}\x1b[0x �� {} ���� �����մϱ�??", pk::decode(_scene_chooItem.name), pk::decode(pk::get_name(_scene_force)))));
			pk::background("");
		}
		void Scene_�ܱ�()
		{
			pk::person@ kunshu = pk::get_person(_scene_force.kunshu);
			pk::person@ gunshi = pk::get_person(_scene_force.gunshi);
			pk::diplomacy(_scene_person, kunshu, gunshi, pk::diplomacy_t(�ܱ�));
		}

		void �ܱ�()
		{
			string str = pk::format("\x1b[2x{}\x1b[0x �� �غ��߽��ϴ�. �޾��ֽʽÿ�", pk::decode(pk::get_name(_scene_chooItem)));
			pk::message_box(pk::encode(str),_scene_person);


			pk::person@ kunshu = pk::get_person(_scene_force.kunshu);
			string str2 = "�� �ްڳ�.";
			pk::message_box(pk::encode(str2),kunshu);
		}


		
		bool ����ģ��Handler()
		{
			const int �� = 0;
			const int �� = 1;
			const int �乫�� = 2;
			const int �ϱ�_Ȱ = 3;
			const int ��å = 4;
			array<array<pk::item@>> items;
			items.insertLast(array<pk::item@>());
			items.insertLast(array<pk::item@>());
			items.insertLast(array<pk::item@>());
			items.insertLast(array<pk::item@>());
			items.insertLast(array<pk::item@>());

			for (int i = 0; i < ����_��; i++)
			{
				pk::item@ it = pk::get_item(i);
				if (it == null or !it.is_alive() or it.status != ��������_����)
					continue;
				pk::person@ p = pk::get_person(it.owner);
				if (p == null)
					continue;
				if (p.get_force_id() != _force.get_id())
					continue;

				//����,������ ����
				switch (it.type)
				{
				case ��������_��:
					items[��].insertLast(it);
					break;
				case ��������_��:
					items[��].insertLast(it);
					break;
				case ��������_�乫��:
					items[�乫��].insertLast(it);
					break;
				case ��������_�ϱ�:
				case ��������_Ȱ:
					items[�ϱ�_Ȱ].insertLast(it);
					break;
				case ��������_��å:
					items[��å].insertLast(it);
					break;

				default:
					break;
				}
			}


			while (true)
			{
				array<string> itemTypeArr =
				{
					pk::encode(pk::format("\x1b[1x��\x1b[0x({})",items[0].length)),
					pk::encode(pk::format("\x1b[2x��\x1b[0x({})",items[1].length)),
					pk::encode(pk::format("\x1b[24x�乫��\x1b[0x({})",items[2].length)),
					pk::encode(pk::format("\x1b[26x�ϱ�/Ȱ\x1b[0x({})",items[3].length)),
					pk::encode(pk::format("\x1b[26x��å\x1b[0x({})",items[4].length)),
					pk::encode("�ڷ�")
				};

				int choose = pk::choose(pk::encode("���������� �������ֽʽÿ�."), itemTypeArr);
				if (choose == 5)
					return true;

				pk::item@ chooseItem = null;
				int si = 0;
				while (true)
				{
					array<string> itemArr;
					int count = pk::min(items[choose].length, si + 5);
					for (int i = si; i < count; i++)
					{
						string owner = pk::decode(pk::get_name(pk::get_person(items[choose][i].owner)));
						itemArr.insertLast(pk::encode(pk::format("{},��ġ{},�ܱ���ġ\x1b[2x{}\x1b[0x,{}"
							, pk::decode(items[choose][i].name), items[choose][i].value, ������ġ[items[choose][i].get_id()], owner)));
					}
					itemArr.insertLast(pk::encode("����"));

					int choose2 = pk::choose(pk::encode("������ �������ֽʽÿ�."), itemArr);
					if (choose2 == itemArr.length - 1)
					{
						si = si + itemArr.length - 1;
						if (si >= items[choose].length)
							break;
					}
					else
					{
						@chooseItem = items[choose][si + choose2];
						break;
					}
				}//while

				if (chooseItem == null)
					continue;

				pk::list<pk::force@> forces0 = pk::get_force_list();
				pk::list<pk::force@> forces;
				for (int i = 0; i < forces0.count; i++)
				{
					pk::force@ f = forces0[i];
					if(f.get_id() == _force.get_id())
						continue;
					forces.add(f);
				}

				pk::list<pk::force@> selectedForce = pk::force_selector("���� ����", "������ ������ ������ �����ϼ���", forces,1, 1);
				if (selectedForce.count == 0)
					continue;

				pk::list<pk::person@> selected = pk::person_selector("���� ����", "�ܱ��� ������ ������ �����ϼ���.", pk::get_idle_person_list(_building), 1, 1);
				if (selected.count == 0)
					continue;

				@_scene_person = selected[0];
				@_scene_chooItem = chooseItem;
				@_scene_force = selectedForce[0];
				pk::scene(pk::scene_t(Scene_��������));
				if (!_scene_bool)
					return true;

				pk::scene(pk::scene_t(Scene_�ܱ�));


				int back = _force.relations[selectedForce[0].get_id()];
				_force.relations[selectedForce[0].get_id()] = pk::min(100, _force.relations[selectedForce[0].get_id()] + ������ġ[chooseItem.get_id()]);

				pk::message_box(pk::encode(pk::format("���� : {} -> {}",back, _force.relations[selectedForce[0].get_id()])));

				selected[0].action_done = true;
				pk::play_se(10);

			}




			return true;
		}
	}

	Main main;
}

