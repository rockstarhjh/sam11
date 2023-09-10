/*
@만든이: 크래픽스
@Update: 2023.8.20,최초배포
*/

namespace 보물교환
{
	class Main
	{
		Main()
		{
			pk::menu_item item;
			item.menu = 102;
			item.pos = 5;
			item.init = pk::building_menu_item_init_t(보물교환Init);
			item.is_enabled = pk::menu_item_is_enabled_t(Is보물교환Enabled);
			item.get_text = pk::menu_item_get_text_t(보물교환Text);
			item.get_desc = pk::menu_item_get_desc_t(보물교환Desc);
			item.handler = pk::menu_item_handler_t(보물교환Handler);
			pk::add_menu_item(item);
        }

		pk::force@ _force;
		pk::building@ _building;
		pk::city@ _city;
		pk::district@ _district;
		void 보물교환Init(pk::building@ building)
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

		bool Is보물교환Enabled()
		{
			return _district.ap >= GetAP();
		}
		string 보물교환Text()
		{
			return pk::encode("보물교환");
		}
		string 보물교환Desc()
		{
			if (_district.ap < GetAP())
				return pk::encode("행동력이 부족합니다.");
			else
				return pk::encode(pk::format("모든 무장(출진무장포함)에 대해  보물교환합니다.(행동력{})",GetAP()));
		}

		pk::item@ GetSelectedItem(array<array<pk::item@>> items, int index)
		{
			while (true)
			{
				array<string> itemTypeArr =
				{
					pk::encode(pk::format("\x1b[1x명마\x1b[0x({})",items[0].length)),
					pk::encode(pk::format("\x1b[2x검\x1b[0x({})",items[1].length)),
					pk::encode(pk::format("\x1b[24x긴무기\x1b[0x({})",items[2].length)),
					pk::encode(pk::format("\x1b[26x암기/활\x1b[0x({})",items[3].length)),
					pk::encode(pk::format("\x1b[26x서책\x1b[0x({})",items[4].length)),
					pk::encode("뒤로")
				};

				int choose = pk::choose(pk::encode(pk::format("{0} 보물종류를 선택해주십시오.",index==0 ? "첫번째" : "두번째")), itemTypeArr);
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
						itemArr.insertLast(pk::encode(pk::format("{},가치{},{}", pk::decode(items[choose][i].name),items[choose][i].value, owner)));
					}
					itemArr.insertLast(pk::encode("다음"));

					int choose2 = pk::choose(pk::encode("보물을 선택해주십시오."), itemArr);
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

		bool 보물교환Handler()
		{
			const int 명마 = 0;
			const int 검 = 1;
			const int 긴무기 = 2;
			const int 암기_활 = 3;
			const int 서책 = 4;
			array<array<pk::item@>> items;
			items.insertLast(array<pk::item@>());
			items.insertLast(array<pk::item@>());
			items.insertLast(array<pk::item@>());
			items.insertLast(array<pk::item@>());
			items.insertLast(array<pk::item@>());

			for (int i = 0; i < 보물_끝; i++)
			{
				pk::item@ it = pk::get_item(i);
				if (it == null or !it.is_alive() or it.status != 보물상태_등장)
					continue;
				pk::person@ p = pk::get_person(it.owner);
				if (p == null)
					continue;
				if (p.get_force_id() != _force.get_id())
					continue;

				//옥쇄,동작은 제외
				switch (it.type)
				{
				case 보물종류_명마:
					items[명마].insertLast(it);
					break;
				case 보물종류_검:
					items[검].insertLast(it);
					break;
				case 보물종류_긴무기:
					items[긴무기].insertLast(it);
					break;
				case 보물종류_암기:
				case 보물종류_활:
					items[암기_활].insertLast(it);
					break;
				case 보물종류_서책:
					items[서책].insertLast(it);
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
				pk::message_box(pk::encode("같은 보물입니다."));
				return true;
			}

			string str = pk::format("{}의 {} 와 {}의 {}를 교환합니까?", 
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

