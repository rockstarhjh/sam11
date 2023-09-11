/*
@만든이: 크래픽스
@Update: 2023.9.1, 최초배포
*/
namespace 보물친선
{
	//수여후, 세이브/로드나 껏다켜야 부가스탯이 적용됩니다.
	//예를 들어 방천화극에 무력이3 붙어 있는데 바로 반영되지 않습니다.
	class ItemGiveInfo
	{
		pk::person@ person;
		pk::item@ item;
	}
	
	//경로에 파일이 없으면 보물이미지만 안나올뿐 에러나지 않습니다.
	const array<string> 보물이미지 =
	{
		"Ebony_보물\\적토마.png",
		"Ebony_보물\\적로.png",
		"Ebony_보물\\조황비전.png",
		"Ebony_보물\\절영.png",
		"Ebony_보물\\대완마.png",
		"Ebony_보물\\대완마.png",
		"Ebony_보물\\대완마.png",
		"Ebony_보물\\칠성보도.png",
		"Ebony_보물\\의천검.png",
		"Ebony_보물\\청강검.png",
		
		"Ebony_보물\\쌍고검.png",
		"Ebony_보물\\방천화극.png",
		"Ebony_보물\\청룡언월도.png",
		"Ebony_보물\\장팔사모.png",
		"Ebony_보물\\유청추.png",
		"Ebony_보물\\비도.png",
		"Ebony_보물\\비도.png",
		"Ebony_보물\\단극.png",
		"Ebony_보물\\단극.png",
		"Ebony_보물\\수극.png",
		
		"Ebony_보물\\수극.png",
		"Ebony_보물\\철쇄.png",
		"Ebony_보물\\양유기의-궁.png",
		"Ebony_보물\\이광의-궁.png",
		"Ebony_보물\\단궁.png",
		"Ebony_보물\\단궁.png",
		"Ebony_보물\\동호비궁.png",
		"Ebony_보물\\동호비궁.png",
		"Ebony_보물\\맥궁.png",
		"Ebony_보물\\맥궁.png",
		
		"Ebony_보물\\손자병법.png",
		"Ebony_보물\\병법24편.png",
		"Ebony_보물\\맹덕신서.png",
		"Ebony_보물\\육도.png",
		"Ebony_보물\\삼략.png",
		"Ebony_보물\\오자.png",
		"Ebony_보물\\위료자.png",
		"Ebony_보물\\전국책.png",
		"Ebony_보물\\사마법.png",
		"Ebony_보물\\묵자.png",

		"Ebony_보물\\태평요술서.png",
		"Ebony_보물\\옥새.png",
		"Ebony_보물\\동작.png",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		
		"Ebony_보물\\옥란백용구.png",
		"Ebony_보물\\권모적토마.png",
		"Ebony_보물\\서량백마.png",
		"Ebony_보물\\백마.png",
		"Ebony_보물\\사륜거.png",
		"Ebony_보물\\오환마.png",
		"Ebony_보물\\흉노마.png",
		"Ebony_보물\\적모우.png",
		"Ebony_보물\\백상.png",
		"Ebony_보물\\참사검.png",

		"Ebony_보물\\간장.png",
		"Ebony_보물\\막야.png",
		"Ebony_보물\\고정도.png",
		"Ebony_보물\\백피도.png",
		"Ebony_보물\\신도.png",
		"Ebony_보물\\오구도.png",
		"Ebony_보물\\거치도.png",
		"Ebony_보물\\환수도.png",
		"Ebony_보물\\쌍철극.png",
		"Ebony_보물\\삼부도.png",

		"Ebony_보물\\봉취도.png",
		"Ebony_보물\\미부도.png",
		"Ebony_보물\\대간도.png",
		"Ebony_보물\\치우부.png",
		"Ebony_보물\\대부.png",
		"Ebony_보물\\철척사모.png",
		"Ebony_보물\\금마삭.png",
		"Ebony_보물\\삼장모.png",
		"Ebony_보물\\철편.png",
		"Ebony_보물\\철칠여골타.png",
		
		"Ebony_보물\\철과추.png",
		"Ebony_보물\\질려봉.png",
		"Ebony_보물\\매화수전.png",
		"Ebony_보물\\수전.png",
		"Ebony_보물\\철추.png",
		"Ebony_보물\\비추.png",
		"Ebony_보물\\보조궁.png",
		"Ebony_보물\\논어.png",
		"Ebony_보물\\전론.png",
		"Ebony_보물\\박혁론.png",

		"Ebony_보물\\시요론.png",
		"Ebony_보물\\치론.png",
		"Ebony_보물\\춘추좌씨전.png",
		"Ebony_보물\\한비자.png",
		"Ebony_보물\\관자.png",
		"Ebony_보물\\둔갑천서.png",
		"Ebony_보물\\서촉지형도.png",
		"Ebony_보물\\평만지장도.png",
		"Ebony_보물\\오추마.png"
	};	

	const int 보물가치_상_명마 = 90;
	const int 보물가치_중_명마 = 60;
	const int 보물가치_하_명마 = 30;
	const int 보물가치_상_검 = 90;
	const int 보물가치_중_검 = 60;
	const int 보물가치_하_검 = 30;
	const int 보물가치_상_긴무기 = 90;
	const int 보물가치_중_긴무기 = 60;
	const int 보물가치_하_긴무기 = 30;
	const int 보물가치_상_암기 = 90;
	const int 보물가치_중_암기 = 60;
	const int 보물가치_하_암기 = 30;
	const int 보물가치_상_활 = 90;
	const int 보물가치_중_활 = 60;
	const int 보물가치_하_활 = 30;
	const int 보물가치_상_서책 = 90;
	const int 보물가치_중_서책 = 60;
	const int 보물가치_하_서책 = 30;


	const array<int> 보물가치 = 
	{
		보물가치_상_명마,
		보물가치_중_명마,
		보물가치_중_명마,
		보물가치_중_명마,
		보물가치_하_명마,
		보물가치_하_명마,
		보물가치_하_명마,
		보물가치_상_검,
		보물가치_상_검,
		보물가치_상_검,

		보물가치_중_검,
		보물가치_상_긴무기,
		보물가치_상_긴무기,
		보물가치_상_긴무기,
		보물가치_상_암기,
		보물가치_중_암기,
		보물가치_중_암기,
		보물가치_하_암기,
		보물가치_하_암기,
		보물가치_하_암기,

		보물가치_하_암기,
		보물가치_중_암기,
		보물가치_상_활,
		보물가치_상_활,
		보물가치_하_활,
		보물가치_하_활,
		보물가치_중_활,
		보물가치_중_활,
		보물가치_하_활,
		보물가치_하_활,

		보물가치_상_서책,
		보물가치_하_서책,
		보물가치_중_서책,
		보물가치_상_서책,
		보물가치_상_서책,
		보물가치_중_서책,
		보물가치_하_서책,
		보물가치_하_서책,
		보물가치_중_서책,
		보물가치_중_서책,

		보물가치_상_서책,
		-1,//옥새
		-1,//동작
		-1,-1,-1,-1,-1,-1,-1,

		보물가치_중_명마, //보물51,
		보물가치_중_명마,
		보물가치_중_명마,
		보물가치_하_명마,
		보물가치_중_명마,
		보물가치_중_명마,
		보물가치_중_명마,
		보물가치_중_명마,
		보물가치_중_명마,
		보물가치_하_검,

		보물가치_상_검,
		보물가치_상_검,
		보물가치_중_검,
		보물가치_하_검,
		보물가치_하_검,
		보물가치_하_검,
		보물가치_하_검,
		보물가치_하_검,
		보물가치_중_긴무기,
		보물가치_중_긴무기,

		보물가치_하_긴무기,
		보물가치_하_긴무기,
		보물가치_하_긴무기,
		보물가치_상_긴무기,
		보물가치_중_긴무기,
		보물가치_중_긴무기,
		보물가치_중_긴무기,
		보물가치_중_긴무기,
		보물가치_중_긴무기,
		보물가치_중_긴무기,

		보물가치_중_긴무기,
		보물가치_중_긴무기,
		보물가치_상_암기,
		보물가치_상_암기,
		보물가치_하_긴무기,
		보물가치_하_암기,
		보물가치_중_활,
		보물가치_하_서책,
		보물가치_하_서책,
		보물가치_하_서책,

		보물가치_하_서책,
		보물가치_하_서책,
		보물가치_하_서책,
		보물가치_중_서책,
		보물가치_하_서책,
		보물가치_상_서책,
		보물가치_하_서책,
		보물가치_하_서책,
		보물가치_상_명마,
		보물가치_상_명마, //보물99,

	};


	class Main
	{
		Main()
		{
			pk::menu_item item;
			item.menu = 103;
			item.pos = 1;
			item.init = pk::building_menu_item_init_t(보물친선Init);
			item.is_enabled = pk::menu_item_is_enabled_t(Is보물친선Enabled);
			item.get_text = pk::menu_item_get_text_t(보물친선Text);
			item.get_desc = pk::menu_item_get_desc_t(보물친선Desc);
			item.handler = pk::menu_item_handler_t(보물친선Handler);
			pk::add_menu_item(item);
        }

		array<ItemGiveInfo> _items;

		pk::force@ _force;
		pk::building@ _building;
		pk::city@ _city;
		pk::district@ _district;
		void 보물친선Init(pk::building@ building)
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

		bool Is보물친선Enabled()
		{
			return _district.ap >= GetAP();
		}
		string 보물친선Text()
		{
			return pk::encode("보물친선");
		}
		string 보물친선Desc()
		{
			if (_district.ap < GetAP())
				return pk::encode("행동력이 부족합니다.");
			else
				return pk::encode(pk::format("타세력에 보물을 주고 친선을 도모합니다.(행동력{})",GetAP()));
		}
		

		pk::item@ _scene_chooItem = null;	
		pk::person@ _scene_person = null;
		pk::force@ _scene_force= null;
		bool _scene_bool = false;
		


		void Scene_보물수여()
		{
			pk::background(pk::format("{}",보물이미지[_scene_chooItem.get_id()]));
			_scene_bool=pk::yes_no(pk::encode(pk::format("\x1b[2x{}\x1b[0x 을 {} 에게 조공합니까??", pk::decode(_scene_chooItem.name), pk::decode(pk::get_name(_scene_force)))));
			pk::background("");
		}
		void Scene_외교()
		{
			pk::person@ kunshu = pk::get_person(_scene_force.kunshu);
			pk::person@ gunshi = pk::get_person(_scene_force.gunshi);
			pk::diplomacy(_scene_person, kunshu, gunshi, pk::diplomacy_t(외교));
		}

		void 외교()
		{
			string str = pk::format("\x1b[2x{}\x1b[0x 을 준비했습니다. 받아주십시오", pk::decode(pk::get_name(_scene_chooItem)));
			pk::message_box(pk::encode(str),_scene_person);


			pk::person@ kunshu = pk::get_person(_scene_force.kunshu);
			string str2 = "잘 받겠네.";
			pk::message_box(pk::encode(str2),kunshu);
		}


		
		bool 보물친선Handler()
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

				int choose = pk::choose(pk::encode("보물종류를 선택해주십시오."), itemTypeArr);
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
						itemArr.insertLast(pk::encode(pk::format("{},가치{},외교가치\x1b[2x{}\x1b[0x,{}"
							, pk::decode(items[choose][i].name), items[choose][i].value, 보물가치[items[choose][i].get_id()], owner)));
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

				pk::list<pk::force@> selectedForce = pk::force_selector("세력 선택", "보물을 조공할 세력을 선택하세요", forces,1, 1);
				if (selectedForce.count == 0)
					continue;

				pk::list<pk::person@> selected = pk::person_selector("무장 선택", "외교를 수행할 무장을 선택하세요.", pk::get_idle_person_list(_building), 1, 1);
				if (selected.count == 0)
					continue;

				@_scene_person = selected[0];
				@_scene_chooItem = chooseItem;
				@_scene_force = selectedForce[0];
				pk::scene(pk::scene_t(Scene_보물수여));
				if (!_scene_bool)
					return true;

				pk::scene(pk::scene_t(Scene_외교));


				int back = _force.relations[selectedForce[0].get_id()];
				_force.relations[selectedForce[0].get_id()] = pk::min(100, _force.relations[selectedForce[0].get_id()] + 보물가치[chooseItem.get_id()]);

				pk::message_box(pk::encode(pk::format("관계 : {} -> {}",back, _force.relations[selectedForce[0].get_id()])));

				selected[0].action_done = true;
				pk::play_se(10);

			}




			return true;
		}
	}

	Main main;
}

