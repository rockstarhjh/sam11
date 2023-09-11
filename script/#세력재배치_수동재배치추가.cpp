/*
	@���� : �������ġ.cpp (PK2.1 �⺻ ���� ����)
	@���� : masterpiecek
	@���� : ������


	�� '�������ġ.cpp' (PK2.1 �⺻ ���� ����) �� �ڵ� ���ġ ��ɿ� ���� ���ġ ��� �߰�
	 - ��ġ ���� �� ������ '�������ġ.cpp' ������ ��Ȱ��ȭ �Ͻñ� �ٶ��ϴ�.


	[ �������ġ ������ �� ���ġ ����׸� ���� ]

	1. ���ġ ���� ���
	 1) 'shift + ��Ŭ��' �޴� ����
	  - �������� base_menu_�������ġ_2.0.cpp' ���� ����� ������ ( https://cafe.naver.com/rtkbank/17 )
	  - Ʃ�丮��, ��������, �̼� �� �޴� ���� �Ұ�
	  - �ó����� ���� ���� �� ù ���� ����Ǹ� ���� �Ұ� (ù ���� �������� �ʰ� �����ߴٰ� �ҷ����� �� ���� ����)
	 2) '�ó����� ����' �� �ڵ� ����
	  - '�������ġ.cpp'�� ���� ���� ����� ������ (PK2.1 �⺻ ���� ����)
	  - ���� �������� Ȱ��ȭ ���� ���� ���� (���� �⺻�� : ��Ȱ��ȭ)
	  - Ʃ�丮��, ��������, �̼� �߿��� ������� ����

	2. ���ġ ���� �׸�
	 1) ��� ������ ���ø� �ڵ� ���ġ (PK2.1���� �⺻���� �����ϴ� '�������ġ.cpp'�� ���� ���� �׸�)
	 2) Ȳ���� �Ҽ� ���ø� �ڵ� ���ġ (�߰� ���)
	 3) Ư�� ���º��� �ش� ���� ������ ���� �Ǵ� �Ϻ� ���� ���ġ (�߰� ���)
	 4) Ȳ���� �Ҽ� ���ø� ���� ���ġ (�߰� ���)
*/

namespace �������ġ_�������ġ�߰�
{

///	=========================  < ���� ���� >  =================================

	const bool �ó��������۽�_���ġ�޴�_���� = false;

///	===========================================================================

	class Main
	{

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		Main()
		{
			relocation_menu_add();
			pk::bind(102, pk::trigger102_t(�ó���������_���ġ�޴�_����));
		}

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		void relocation_menu_add()
		{
			pk::menu_item item;
			item.menu = 2;
			item.is_enabled = cast<pk::menu_item_is_enabled_t@>(function(){return main.is_enabled_relocation();});
			item.get_text = cast<pk::menu_item_get_text_t@>(function(){return pk::encode("���� ���ġ");});
			item.get_desc = cast<pk::menu_item_get_desc_t@>(function()
			{
				if (pk::is_campaign()) return pk::encode("Ʃ�丮��, �������� �߿��� ������ ���ġ�� �� �����ϴ�.");
				if (pk::is_mission_running()) return pk::encode("�̼� �߿��� ������ ���ġ�� �� �����ϴ�.");
				if (pk::get_scenario().turn_counter > 0) return pk::encode("������ ����Ǿ� �� �̻� ������ ���ġ�� �� �����ϴ�.");
				return pk::encode("���� �� Ȳ���� ��ġ�� ���ġ�մϴ�.");
			});
			item.handler = cast<pk::menu_item_handler_t@>(function(){main.relocation_menu(); return true;});
			pk::add_menu_item(item);
		}

		void �ó���������_���ġ�޴�_����()
		{
			if (!�ó��������۽�_���ġ�޴�_����) return;
			if (pk::get_scenario().loaded) return;
			relocation_menu();
		}

		void relocation_menu()
		{
			if (!is_enabled_relocation()) return;

			string menu_desc = "���ġ�� ��� �� ����� �����Ͻʽÿ�.\n1. ���ġ ��� : \x1b[1x����\x1b[0x, \x1b[1xȲ��\x1b[0x\n2. ���ġ ��� : \x1b[1x�ڵ�\x1b[0x, \x1b[1x����\x1b[0x";
			array<string> answer_arr = {pk::encode("\x1b[1x���� �ڵ� ���ġ"), pk::encode("\x1b[1xȲ�� �ڵ� ���ġ"), pk::encode("\x1b[1x���� ���� ���ġ"), pk::encode("\x1b[1xȲ�� ���� ���ġ"), pk::encode("���� Ȯ��"), pk::encode("����")};
			int answer = pk::choose(pk::encode(menu_desc), answer_arr);
			if      (answer == /*���� �ڵ� ���ġ*/0) relocate_city_automatically();
			else if (answer == /*Ȳ�� �ڵ� ���ġ*/1) relocate_emperor_automatically();
			else if (answer == /*���� ���� ���ġ*/2) relocate_city_manually();
			else if (answer == /*Ȳ�� ���� ���ġ*/3) relocate_emperor_manually();
			else if (answer == /*���� Ȯ��*/4)        show_map();
			else if (answer == /*����*/5)             return;
		}

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		void relocate_city_automatically()
		{
			string desc = "��� ������ ���ø� �������� ���ġ�մϴ�.";
			if (pk::choose(pk::encode(desc), {pk::encode("\x1b[1x����"), pk::encode("���")}) == /*����*/0)
			{
				pk::list<pk::force@> force_list = pk::get_force_list();
				force_list.shuffle();

				array<int> city_count, index;
				for (int i = 0; i < force_list.count; i++) city_count.insertLast(pk::get_city_list(force_list[i]).count);
				index = Partitioner(pk::get_scenario().seed).partition(city_count);

				for (int i = 0; i < force_list.count; i++)
				{
					pk::list<pk::city@> a = pk::get_city_list(force_list[i]);
					pk::list<pk::city@> b;

					for (int city_id = 0; city_id < ����_��; city_id++)
					{
						if (index[city_id] != i) continue;

						pk::city@ city = pk::get_city(city_id);
						int k = a.index_of(city);
						if (k >= 0) a.remove_at(k);
						else		b.add(city);
					}

					a.shuffle();
					b.shuffle();

					for (int j = 0; j < a.count; j++)
					{
						pk::building@ c = pk::city_to_building(a[j]);
						pk::building@ d = pk::city_to_building(b[j]);

						swap(c, d);
					}

					resetting_of_port_and_gate();
				}
			}

			relocation_menu();
		}

		void relocate_emperor_automatically()
		{
			int emperor_id = pk::get_scenario().emperor;
			if (!pk::is_valid_person_id(emperor_id)) pk::message_box(pk::encode("���� �ó��������� Ȳ���� �������� �ʽ��ϴ�."));
			else
			{
				pk::person@ emperor = pk::get_person(emperor_id);
				string emperor_name = "\x1b[1x"+pk::decode(pk::get_name(emperor))+"\x1b[0x";
				string emperor_city_name = "\x1b[1x"+pk::decode(pk::get_name(pk::get_city(emperor.service)))+"\x1b[0x";
				string desc = "Ȳ���� �Ҽ� ���ø� �������� ���ġ�մϴ�.\n(�ó����� Ȳ�� : "+emperor_name+")\n(���� �Ҽ� ���� : "+emperor_city_name+")";
				if (pk::choose(pk::encode(desc), {pk::encode("\x1b[1x����"), pk::encode("���")}) == /*����*/0)
				{
					pk::list<pk::city@> selectable_city_list = selectable_city_list_for_emperor(emperor);
					pk::city@ relocated_city = selectable_city_list[pk::rand(int(selectable_city_list.count))];
					int building_id = pk::city_to_building(relocated_city).get_id();
					pk::set_service(emperor, building_id);
					emperor.location = building_id;
					string relocated_city_name = "\x1b[1x"+pk::decode(pk::get_name(relocated_city))+"\x1b[0x";
					pk::message_box(pk::encode("Ȳ��("+emperor_name+")�� �Ҽ� ���ø� "+emperor_city_name+"���� "+relocated_city_name+"(��)�� �����߽��ϴ�."));
				}
			}

			relocation_menu();
		}

		void relocate_city_manually()
		{
			string desc_1 = "Ư�� ������ �����Ͽ� �ش� ���� ������\n���� �Ǵ� �Ϻθ� ���� ���ġ�մϴ�.";
			if (pk::choose(pk::encode(desc_1), {pk::encode("\x1b[1x����"), pk::encode("���")}) == /*����*/0)
			{
				pk::message_box(pk::encode("���ø� ���ġ�� ������ �����Ͻʽÿ�."));
				pk::list<pk::force@> selected_force_list = pk::force_selector(pk::encode("���� ����"), "", pk::get_force_list(), 1, 1);
				if (int(selected_force_list.count) > 0)
				{
					pk::force@ selected_force = selected_force_list[0];
					string selected_force_name = "\x1b[1x"+pk::decode(pk::get_name(selected_force))+"\x1b[0x";
					pk::message_box(pk::encode("���ġ�� ������ ���ø� �����Ͻʽÿ�.\n(���õ� ���� : "+selected_force_name+")"));
					pk::list<pk::city@> force_city_list = pk::get_city_list(selected_force);
					int force_city_count = pk::get_city_count(selected_force);
					array<pk::building@> building_from_arr = pk::list_to_array(pk::city_selector(pk::encode("���� ����"), "", force_city_list, 1, force_city_count));
					if (int(building_from_arr.length) > 0)
					{
						string building_from_names = get_building_names_by_building_arr(building_from_arr);
						string building_from_count_info = (int(building_from_arr.length) > 1) ? "����" : "��";
						pk::message_box(pk::encode(building_from_names+"(��)�� ��ġ�� ��ü�� ����"+building_from_count_info+" �����Ͻʽÿ�."));
						pk::list<pk::city@> selectable_city_list = selectable_city_list_for_city_relocation(selected_force);
						array<pk::building@> building_to_arr = pk::list_to_array(pk::city_selector(pk::encode("���� ����"), "", selectable_city_list, int(building_from_arr.length), int(building_from_arr.length)));
						if (int(building_to_arr.length) == int(building_from_arr.length))
						{
							string building_to_names = get_building_names_by_building_arr(building_to_arr);
							string desc_2 = building_from_names+"(��)�� "+building_to_names+"�� ��ġ�� ���� ��ü�մϴ�.";
							if (pk::choose(pk::encode(desc_2), {pk::encode("\x1b[1x����"), pk::encode("���")}) == /*����*/0)
							{
								for (int i = 0; i < int(building_from_arr.length); i++)
								{
									pk::building@ building_from = pk::city_to_building(pk::get_city(building_from_arr[i].get_id()));
									pk::building@ building_to = pk::city_to_building(pk::get_city(building_to_arr[i].get_id()));
									swap(building_from, building_to);
								}

								resetting_of_port_and_gate();
							}
						}
					}
				}
			}

			relocation_menu();
		}

		void relocate_emperor_manually()
		{
			int emperor_id = pk::get_scenario().emperor;
			if (!pk::is_valid_person_id(emperor_id)) pk::message_box(pk::encode("���� �ó��������� Ȳ���� �������� �ʽ��ϴ�."));
			else
			{
				pk::person@ emperor = pk::get_person(emperor_id);
				string emperor_name = "\x1b[1x"+pk::decode(pk::get_name(emperor))+"\x1b[0x";
				string emperor_city_name = "\x1b[1x"+pk::decode(pk::get_name(pk::get_city(emperor.service)))+"\x1b[0x";
				string desc_1 = "Ȳ���� �Ҽ� ���ø� ���� ���ġ�մϴ�.\n(�ó����� Ȳ�� : "+emperor_name+")\n(���� �Ҽ� ���� : "+emperor_city_name+")";
				if (pk::choose(pk::encode(desc_1), {pk::encode("\x1b[1x����"), pk::encode("���")}) == /*����*/0)
				{
					pk::message_box(pk::encode("Ȳ��("+emperor_name+")�� �Ҽӵ� ���ø� �����Ͻʽÿ�."));
					pk::list<pk::city@> selectable_city_list = selectable_city_list_for_emperor(emperor);
					pk::list<pk::building@> selected_building_list = pk::city_selector(pk::encode("���� ����"), "", selectable_city_list, 1, 1);
					if (int(selected_building_list.count) > 0)
					{
						pk::building@ selected_building = pk::city_to_building(pk::get_city(selected_building_list[0].get_id()));
						string selected_building_name = "\x1b[1x"+pk::decode(pk::get_name(selected_building))+"\x1b[0x";
						string desc_2 = "Ȳ��("+emperor_name+")�� �Ҽ� ���ø� "+emperor_city_name+"���� "+selected_building_name+"(��)�� �����մϴ�.";
						if (pk::choose(pk::encode(desc_2), {pk::encode("\x1b[1x����"), pk::encode("���")}) == /*����*/0)
						{
							pk::set_service(emperor, selected_building.get_id());
							emperor.location = selected_building.get_id();
						}
					}
				}
			}

			relocation_menu();
		}

		void show_map()
		{
			pk::city_selector(pk::encode("���� Ȯ��"), "", pk::get_city_list(), 0, 0);

			relocation_menu();
		}

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		bool is_enabled_relocation()
		{
			return (!pk::is_campaign() and !pk::is_mission_running() and pk::get_scenario().turn_counter == 0);
		}

		pk::list<pk::city@> selectable_city_list_for_city_relocation(pk::force@ selected_force)
		{
			pk::list<pk::city@> selectable_city_list;
			for (int city_id = 0; city_id < ����_��; city_id++)
			{
				pk::city@ city = pk::get_city(city_id);
				if (city.get_force_id() != selected_force.get_id()) selectable_city_list.add(city);
			}

			return selectable_city_list;
		}

		pk::list<pk::city@> selectable_city_list_for_emperor(pk::person@ emperor)
		{
			pk::list<pk::city@> selectable_city_list;
			for (int city_id = 0; city_id < ����_��; city_id++)
			{
				pk::city@ city = pk::get_city(city_id);
				if (city_id != emperor.service) selectable_city_list.add(city);
			}
			return selectable_city_list;
		}

		string get_building_names_by_building_arr(array<pk::building@> building_arr)
		{
			array<string> building_name_arr(0);
			for (int i = 0; i < int(building_arr.length); i++)
			{
				string building_name = "\x1b[1x"+pk::decode(pk::get_name(building_arr[i]))+"\x1b[0x";
				building_name_arr.insertLast(building_name);
			}

			return join(building_name_arr, "\x1b[0x, ");
		}

		void resetting_of_port_and_gate()
		{
			// �ױ�, ���� �缳��
			for (int city_id = 0; city_id < ����_��; city_id++)
			{
				pk::city@ city = pk::get_city(city_id);
				for (int i = 0; i < 5; i++)
				{
					if (city.gate[i] == -1) continue;

					pk::building@ building = pk::get_building(city.gate[i]);
					if (city.get_force_id() == -1) pk::neutralize(building);
					else
					{
						pk::set_district(building, city.get_district_id());
						pk::set_gold(building, city.gold / 10);
						pk::set_food(building, city.food / 10);
						pk::set_troops(building, city.troops / 10);
						pk::set_energy(building, city.energy);
						pk::reset_weapon_amount(building);
						pk::set_weapon_amount(building, pk::rand(����_����) + 1, city.troops / 10);
					}
				}
			}
		}

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	}	// class main





///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	class Partitioner
	{
		array<int> start_, result_(����_��);
		pk::random random_;

		Partitioner(int seed) { random_.seed = seed; }

		/**
		@param count ���� �� �迭
		@return      ���� ���̵� ���� city_count Ű(�ε���) ���� ��
		*/
		array<int> partition(const array<int> &in city_count)
		{
			bool retry = true;

			while (retry)
			{
				start_.resize(����_��);
				for (int i = 0; i < ����_��; i++)
				{
					result_[i] = -1;
					start_[i] = i;
				}
				shuffle(start_);

				retry = false;
				for (int i = 0; i < int(city_count.length); i++)
				{
					if (spread(start_[0], city_count[i], i) == 0) continue;

					retry = true;
					break;
				}
			}

			return result_;
		}

		/**
		city_id ���ø� �������� n ���� ���ø�ŭ ����
		@return ���� ����
		*/
		int spread(int city_id, int n, int index)
		{
			// �����ų� �̹� �ٸ� ������ ������ ��� ����.
			if (n <= 0 or result_[city_id] != -1) return n;

			result_[city_id] = index;
			n -= 1;

			int p = start_.find(city_id);
			if (p >= 0) start_.removeAt(p);

			// �̿����� ����.
			pk::city@ city = pk::get_city(city_id);
			array<int> neighbor_city_id(6);
			for (int i = 0; i < 6; i++) neighbor_city_id[i] = city.neighbor[i];
			shuffle(neighbor_city_id);

			for (int i = 0; i < 6; i++)
			{
				if (neighbor_city_id[i] != -1 and result_[neighbor_city_id[i]] == -1) n = spread(neighbor_city_id[i], n, index);
				if (n == 0) break;
			}

			// ���� ���� ���� ����
			return n;
		}

		void shuffle(array<int>& arr)
		{
			int n = arr.length();
			for (int i = 0; i < n; i++)
			{
				int j = random_(n - 1);
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	};

	void swap(pk::building@ a, pk::building@ b)
	{
		SwapContext ctx_a, ctx_b;
		ctx_a.load(a);
		ctx_b.load(b);
		ctx_a.save(b);
		ctx_b.save(a);
		if (a.get_force_id() == -1) pk::neutralize(a);
		if (b.get_force_id() == -1) pk::neutralize(b);
	}

	class SwapContext
	{
		int district_id = -1, gold = 0, food = 0, public_order = 0, troops = 0, energy = 0;
		pk::list<pk::person@> person_list;
		array<int> weapon_amount(����_��, 0);

		void load(pk::building@ building)
		{
			pk::city@ city = pk::building_to_city(building);
			district_id = building.get_district_id();
			person_list = pk::get_person_list(building, pk::mibun_flags(�ź�_����, �ź�_����, �ź�_�¼�, �ź�_�Ϲ�));
			gold = pk::get_gold(building);
			food = pk::get_food(building);
			public_order = city !is null ? city.public_order : 0;
			troops = pk::get_troops(building);
			energy = pk::get_energy(building);
			for (int i = 0; i < ����_��; i++) weapon_amount[i] = pk::get_weapon_amount(building, i);
		}

		void save(pk::building@ building)
		{
			pk::city@ city = pk::building_to_city(building);
			pk::set_district(building, district_id);
			for (int i = 0; i < person_list.count; i++) pk::move(person_list[i], building);
			pk::set_gold(building, gold);
			pk::set_food(building, food);
			if (city !is null) pk::set_public_order(city, public_order);
			pk::set_troops(building, troops);
			pk::set_energy(building, energy);
			for (int i = 0; i < ����_��; i++) pk::set_weapon_amount(building, i, weapon_amount[i]);
		}
	};

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	Main main;
}