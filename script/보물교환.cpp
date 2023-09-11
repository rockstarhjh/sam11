/*
@������: ũ���Ƚ�
@Update: 2023.8.20,���ʹ���
*/

namespace ������ȯ
{
	class Main
	{
		Main()
		{
			pk::menu_item item;
			item.menu = 102;
			item.pos = 5;
			item.init = pk::building_menu_item_init_t(������ȯInit);
			item.is_enabled = pk::menu_item_is_enabled_t(Is������ȯEnabled);
			item.get_text = pk::menu_item_get_text_t(������ȯText);
			item.get_desc = pk::menu_item_get_desc_t(������ȯDesc);
			item.handler = pk::menu_item_handler_t(������ȯHandler);
			pk::add_menu_item(item);
        }

		pk::force@ _force;
		pk::building@ _building;
		pk::city@ _city;
		pk::district@ _district;
		void ������ȯInit(pk::building@ building)
		{
			@_force = pk::get_force(building.get_force_id());
			@_building = building;
			@_city = pk::building_to_city(building);
			@_district = pk::get_district(building.get_district_id());
		}
		int GetAP()
		{
			return 10;
		}

		bool Is������ȯEnabled()
		{
			return _district.ap >= GetAP();
		}
		string ������ȯText()
		{
			return pk::encode("������ȯ");
		}
		string ������ȯDesc()
		{
			if (_district.ap < GetAP())
				return pk::encode("�ൿ���� �����մϴ�.");
			else
				return pk::encode(pk::format("��� ����(������������)�� ����  ������ȯ�մϴ�.(�ൿ��{})",GetAP()));
		}

		pk::item@ GetSelectedItem(array<array<pk::item@>> items, int index)
		{
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

				int choose = pk::choose(pk::encode(pk::format("{0} ���������� �������ֽʽÿ�.",index==0 ? "ù��°" : "�ι�°")), itemTypeArr);
				if (choose == 5)
					return null;

				pk::item@ chooseItem = null;
				int si = 0;
				while (true)
				{
					array<string> itemArr;
					int count = pk::min(items[choose].length, si + 5);
					for (int i = si; i < count; i++)
					{
						string owner = pk::decode(pk::get_name(pk::get_person(items[choose][i].owner)));
						itemArr.insertLast(pk::encode(pk::format("{},��ġ{},{}", pk::decode(items[choose][i].name),items[choose][i].value, owner)));
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

				return chooseItem;
			}
			return null;
		}

		bool ������ȯHandler()
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

			pk::item@ item0 = GetSelectedItem(items,0);
			if (item0 == null)
				return true;
			pk::item@ item1 = GetSelectedItem(items,1);
			if (item1 == null)
				return true;
			if (item0.get_id() == item1.get_id()) 
			{
				pk::message_box(pk::encode("���� �����Դϴ�."));
				return true;
			}

			string str = pk::format("{}�� {} �� {}�� {}�� ��ȯ�մϱ�?", 
				pk::decode(pk::get_name(pk::get_person((item0.owner)))),
				pk::decode(pk::get_name(item0)),
				pk::decode(pk::get_name(pk::get_person((item1.owner)))),
				pk::decode(pk::get_name(item1)));

			if (pk::yes_no(pk::encode(str)))
			{
				int tmp = item0.owner;
				int tmpLoc = item0.location;
				item0.owner = item1.owner;
				item0.location = item1.location;
				item1.owner = tmp;
				item1.location = tmpLoc;

				_district.ap = pk::max(_district.ap - GetAP(), 0);
				pk::play_se(10);
			}

			return true;
		}
	}

	Main main;
}

