/*
@만든이: 크래픽스
@Update: 2023.8.29, 최초배포
@Update: 2023.9.2, 테스트 코드추가
*/

namespace 능력연구횟수구매
{
	const int 행동력 = 20;
	
	const int 스탯_하 = 1000;
	const int 스탯_중 = 2000;
	const int 스탯_상 = 3000;
	const int 적성_B = 1000;
	const int 적성_A = 2000;
	const int 특기_하 = 1000;
	const int 특기_중 = 2000;
	const int 특기_상 = 3000;

	const array<int> 능력연구_기교 =
	{
		스탯_하,스탯_중,스탯_상,스탯_하,스탯_중,
		스탯_상,스탯_하,스탯_중,스탯_상,스탯_하,
		
		스탯_중,스탯_상,스탯_하,스탯_중,스탯_상,
		적성_B,적성_A,적성_B,적성_A,적성_B,
		
		적성_A,적성_B,적성_A,적성_B,적성_A,
		적성_B,적성_A,특기_중,특기_하,특기_상,
		
		특기_중,특기_상,특기_하,특기_중,특기_상,
		특기_중,특기_하,특기_중,특기_중,특기_상,
		
		특기_상,특기_중,특기_하,특기_하,특기_하,
		특기_상,특기_상,특기_상,특기_상,특기_상,
		
		특기_상,특기_상,특기_상,특기_중,특기_하,
		특기_하,특기_하,특기_중,특기_중,특기_하,

		특기_상,특기_하,특기_하,특기_중,특기_상,
		특기_상,특기_상,특기_중,특기_중,특기_중,

		특기_상,특기_상,특기_상,특기_중,특기_상,
		특기_상,특기_상,특기_중,특기_상,특기_상,

		특기_중,특기_중,특기_중,특기_중,특기_중,
		특기_중,특기_중,특기_중,특기_중,특기_중,

		특기_중,특기_중,특기_중,특기_상,특기_상,
		특기_상,특기_상,특기_상,
	};
	const array<int> 능력연구_최대부여수 =
	{
		5,5,3,5,5,
		3,5,5,3,5,
		5,3,5,5,3,
		5,5,5,5,5,
		5,5,5,5,5,
		5,5,3,3,3,
		3,1,3,3,1,
		3,3,3,3,3,
		1,3,3,3,3,
		3,3,1,5,3,
		3,3,3,5,5,
		5,5,3,5,5,
		3,5,5,3,3,
		3,3,3,5,5,
		5,5,5,5,5,
		5,5,5,3,3,
		3,3,5,5,5,
		5,5,5,5,5,
		5,5,5,3,3,
		3,3,3
	};
	
	const array<string> 능력연구_이름 =
	{
		"통저","통중","통고","무저","무중",
		"무고","지저","지중","지고","정저",
		"정중","정고","매저","매중","매고",
		"창병B","창병A","극병B","극병A","노병B",
		"노병A","기병B","기병A","병기B","병기A",
		"수군B","수군A","사정","소탕","연전",
		"보좌","패왕","매복","명경","심모",
		"불굴","축성","금강","철벽","명성",
		"포박","위압","운반","조선","발명",
		"번식","능리","논객","심공","창신",
		"극신","궁신","수신","행군","답파",
		"혈로","호위","주악","지도","안력",
		"징세","풍수","기원","간파","화신",
		"귀모","연환","반계","난전","기각",
		"용장","투신","질주","공성","신장",
		"기신","공신","맹장","비장","도주",
		"강행","등갑","강운","미도","미도",
		"징수","징수","징수","둔전","둔전",
		"둔전","인정","인정","허실","통찰",
		"신산","백출","귀문",
		
	};

	class ResearchInfo
	{
		string name;
		int count;
		int id;
		int tp;
		int maxCount;
		int index;
	};



	class Main
	{

		Main()
		{
			pk::menu_item item;
			item.menu = 105;
			item.pos = 13;
			item.init = pk::building_menu_item_init_t(AbilityResearchInit);
			item.is_enabled = pk::menu_item_is_enabled_t(IsAbilityResearchEnabled);
			item.get_text = pk::menu_item_get_text_t(GetAbilityResearchText);
			item.get_desc = pk::menu_item_get_desc_t(GetAbilityResearchDesc);
			item.handler = pk::menu_item_handler_t(AbilityResearchHandler);
			pk::add_menu_item(item);
		}

		pk::force@ _force;
		pk::building@ _building;
		pk::city@ _city;
		pk::district@ _district;
		void AbilityResearchInit(pk::building@ building)
		{
			@_force = pk::get_force(building.get_force_id());
			@_building = building;
			@_city = pk::building_to_city(building);
			@_district = pk::get_district(building.get_district_id());
		}
		bool IsAbilityResearchEnabled()
		{
			return _district.ap >= 행동력;
		}
		string GetAbilityResearchText()
		{
			return pk::encode("능력연구횟수구매");
		}
		string GetAbilityResearchDesc()
		{
			if (_district.ap < 행동력)
				return pk::encode(pk::format("행동력이 부족합니다.(행동력{})", 행동력));
			else
				return pk::encode(pk::format("능력연구횟수를 구매합니다.(행동력{})", 행동력));
		}

		array<ResearchInfo> makeList()
		{
			array<ResearchInfo> ris;

			int count = 48;
			//for (int i = 0; i < _force.ability_researched.length; i++)
			for (int i = 0; i < count; i++)
			{
				//_force.ability_researched[i] = true;
				//_force.training_counter[i] = 3;
				//pk::printf("abil i{},count{}\n",i,_force.training_counter[i]);
			}

			for (int i = 0; i < count; i++)
			{
				if(!_force.ability_researched[i])
					continue;
				ResearchInfo ri;
				ri.count = _force.training_counter[i];
				ri.id = i;
				ri.maxCount = 능력연구_최대부여수[i];
				ri.name = pk::format("{}",능력연구_이름[i]);
				ri.tp = 능력연구_기교[i];
				ris.insertLast(ri);
			}
			
			int count2 = 10;
			for (int i = 0; i < count2; i++)
			{
				if (!_force.sp_ability_researched[i])
					continue;
				int index = _force.sp_ability[i];
				ResearchInfo ri;
				ri.count = _force.sp_training_counter[i];
				ri.maxCount = 능력연구_최대부여수[index];
				ri.name = 능력연구_이름[index];
				ri.id = index;
				ri.index = i;
				ri.tp = 능력연구_기교[index];
				ris.insertLast(ri);
			}


			return ris;
		}

		bool AbilityResearchHandler()
		{
			
			while (true)
			{
				int si=0;
				array<ResearchInfo> ris = makeList();
				ResearchInfo@ chooseItem;
				while (true)
				{
					array<string> itemArr;
					array<ResearchInfo> itemArr2;
					int count = pk::min(ris.length, si + 4);
					if (si == 0)
						itemArr.insertLast(pk::encode("종료"));
					else
						itemArr.insertLast(pk::encode("뒤로"));

					for (int i = si; i < count; i++)
					{
						ResearchInfo@ ri = ris[i];
						string str;
						str = pk::format("{},{}/{},기교{}", ri.name, ri.count,ri.maxCount, ri.tp);
						itemArr.insertLast(pk::encode(str));
						itemArr2.insertLast(ri);
					}
					if (si + 4 >= ris.length)
						itemArr.insertLast(pk::encode("종료"));
					else
						itemArr.insertLast(pk::encode("다음"));

					int choose2 = pk::choose(pk::encode("능력을 선택해주십시오"), itemArr);
					if (choose2 == itemArr.length - 1)
					{
						si = si + 4;
						if (si >= ris.length)
							return true;
					}
					else if (choose2 == 0)
					{
						si = si - 4;
						if (si < 0)
							return true;
					}
					else
					{
						@chooseItem = itemArr2[choose2 - 1];
						break;
					}
				}

				if(chooseItem == null)
					continue;

				if (_force.tp < chooseItem.tp) 
				{
					pk::message_box(pk::encode("기교가 부족합니다."));
					continue;
				}
				if(_district.ap < 행동력)
				{
					pk::message_box(pk::encode("행동력이 부족합니다."));
					continue;
				}
				int value = chooseItem.id < 48 ? _force.training_counter[chooseItem.id] : _force.training_counter[chooseItem.index];
				if (!pk::yes_no(pk::encode(pk::format("{} {}/{}구매합니까?", chooseItem.name, chooseItem.count, value))))
					continue;

				//if (chooseItem.id < 48)
				//{
				//	if (_force.training_counter[chooseItem.id] == 0)
				//	{
				//		pk::message_box(pk::encode("현재 최대 횟수 입니다."));
				//		continue;
				//	}
				//}
				//else 
				//{
				//	if (_force.sp_training_counter[chooseItem.index] == 0)
				//	{
				//		pk::message_box(pk::encode("현재 최대 횟수 입니다."));
				//		continue;
				//	}
				//}
					
				
				//if(!pk::yes_no(pk::encode(pk::format("{}의 회수를 구매합니까?",chooseItem.name))))
				//	continue;

				if(chooseItem.id < 48)
					_force.training_counter[chooseItem.id]=pk::max(0, _force.training_counter[chooseItem.id]-1);
				else
					_force.sp_training_counter[chooseItem.index]=pk::max(0,_force.sp_training_counter[chooseItem.index]-1);

				
				pk::play_se(10);
				_force.tp -= chooseItem.tp;
				_district.ap -=행동력;
				_force.update();
				
				si = 0;
				@chooseItem = null;
			}//while
			return true;

		}//funcio


	}

	Main main;
}


