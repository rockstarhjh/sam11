/*
@만든이: 크래픽스
@Update: 2024.6.6최초배포
*/
namespace 복병_HiddenAttack
{
	const int 행동력 = 20;
	
	const bool 특기표시 = true;

	const int 복병_전세_판단_범위 = 4;//각 유닛에서의 전세 판단거립이니다.
	const int 복병_혼란_위보_적용_범위 = 2;//투입되는 병력인접으로 혼란/위보/기력감소가 발생되는 범위입니다.
	const int 기력감소치 = 50;//복병으로 인한 기력감소치입니다. 혼란/위보/기력감소 중 기력감소가 발생할때 적용됩니다.

	const int 복병_전세_판단_부대_수 = 2;//유닛의 주변범위내 유닛수의 차이가 2이상일때 열세로 판단.
	const int 복병_전세_판단_병력_차 = 10000;//병력차가 10000이상일때

	const bool 복병_병력감소 = true;//복병 실행시 적군의 병력이 감소합니다.
	const int 복병_최소데미지 = 700;
	const int 복병_최대데미지 = 1500;

	const bool 연속_복병_제한 = true;//복병이 매턴 발생하지 못하도록 합니다.
	const int 연속_복병_제한_일 = 60;//두달


	const float 복병확률_지력비중 = 0.7; //지력과 통솔을 7:3로
	const int 복병확률_최대지력차 = 30;//지력차가 30이 되면 50% 확률이 됩니다.
	const int 복병확률_최대통솔차 = 90;//통솔차가 90(3명합산)이 되면 50% 확률이 됩니다.

	const int AI_복병활률_실행_최소치 = 50;//60% 확률이 되야 AI가 복병을 실행합니다.


	const int 복병_일기토_확률 = 30;//복병 실행시 일기토 발생확률입니다.
	const int 복병_일기토_무력차 = 10;// 플러스 마이너스 10 차이
	const int 복병_일기토_체력감소 = 15;//복병일기토시 체력을 깍고 시작함.


	const int KEY = pk::hash("복병");
	const int KEY_최근출진부대선택 = pk::hash("최근출진부대선택_Export");


	class UnitInfo
	{
		pk::list<pk::person@> members;
		int weapon = -1;
		int weaponWater = -1;
	};

	class FieldInfo
	{
		pk::unit@ u;
		pk::list<pk::unit@> enemies;
		pk::list<pk::person@> persons;
		pk::person@ person지력;
		pk::list<pk::person@> persons통솔;

		int percent = 0;
	};

	class Main
	{
		pk::func166_t@ prev_callback_166;

		Main()
		{
			pk::menu_item item;
			item.menu = 101;
			item.pos = 13;
			item.init = pk::building_menu_item_init_t(복병Init);
			item.is_enabled = pk::menu_item_is_enabled_t(Is복병Enabled);
			item.get_text = pk::menu_item_get_text_t(복병Text);
			item.get_desc = pk::menu_item_get_desc_t(복병Desc);
			item.handler = pk::menu_item_handler_t(복병Handler);
			pk::add_menu_item(item);

			pk::bind(111, pk::trigger111_t(onTurnStart));

			pk::bind(102, pk::trigger102_t(Init));
			pk::bind(105, pk::trigger105_t(SaveData));


			@prev_callback_166 = cast<pk::func166_t@>(pk::get_func(166));

		}

		void Init()
		{
			_연속복병제한턴 = {};
			int count = int(pk::load(KEY, 0, 0));
			if (count > 0)
			{
				int li = 1;
				for (int i = 0; i < count; i++)
				{
					int a = int(pk::load(KEY, li++, 0));
					_연속복병제한턴.insertLast(a);
				}
			}
			else 
			{
				for (int i = 0; i < 도시_끝; i++)
				{
					_연속복병제한턴.insertLast(0);
				}
			}
		}

		void SaveData(int fd)
		{
			pk::store(KEY, 0, _연속복병제한턴.length);
			int si = 1;
			for (int i = 0; i < _연속복병제한턴.length; i++)
			{
				pk::store(KEY, si++, _연속복병제한턴[i]);
			}
		}

		array<int> _연속복병제한턴(도시_끝);

		pk::force@ _force;
		pk::building@ _building;
		pk::city@ _city;
		pk::gate@ _gate;
		pk::port@ _port;

		pk::district@ _district;
		void 복병Init(pk::building@ building)
		{
			@_force = pk::get_force(building.get_force_id());
			@_building = building;
			@_city = pk::building_to_city(building);
			@_port = pk::building_to_port(building);
			@_gate = pk::building_to_gate(building);
			@_district = pk::get_district(building.get_district_id());

		}
		bool Is복병Enabled()
		{
			if (_building.get_id() >= 도시_끝)
				return false;

			if (연속_복병_제한 && pk::get_elapsed_days() < (_연속복병제한턴[_building.get_id()] + 연속_복병_제한_일))
				return false;
			return _district.ap >= 행동력;
		}
		string 복병Text()
		{
			return pk::encode("복병");
		}
		string 복병Desc()
		{
			if (_building.get_id() >= 도시_끝)
				return pk::encode("도시에서만 가능합니다.");
			if (_district.ap < 행동력)
				return pk::encode("행동력이 부족합니다.");
			else if (연속_복병_제한 && pk::get_elapsed_days() < (_연속복병제한턴[_building.get_id()] + 연속_복병_제한_일))
				return pk::encode(pk::format("{}일후에 사용가능합니다.", _연속복병제한턴[_building.get_id()] + 연속_복병_제한_일- pk::get_elapsed_days()));
			else
				return pk::encode(pk::format("열세전장에 복병을 투입합니다.(행동력{})", 행동력));
		}



		bool 복병실행(pk::list<pk::person@> src, pk::person@ 지력장수, FieldInfo@ fi)
		{
			int a = 복병확률(src, 지력장수, fi);
			return pk::rand_bool(a);
		}

		int 복병확률(pk::list<pk::person@> src,pk::person@ 지력장수, FieldInfo@ fi)
		{
			int max지력0 = 지력장수.stat[무장능력_지력];
			int 통솔합0 = 0;
			for (int i = 0; i < src.count; i++)
			{
				pk::person@ p = src[i];
				통솔합0 += p.stat[무장능력_통솔];
			}

			int max지력1 = fi.person지력.stat[무장능력_지력];
			int 통솔합1= 0;
			for (int i = 0; i < fi.persons통솔.count; i++)
			{
				pk::person@ p = src[i];
				통솔합1 += p.stat[무장능력_통솔];
			}



			max지력0 = pk::min(max지력0, 130);
			max지력1 = pk::min(max지력1, 130);

			통솔합0 = pk::min(통솔합0, 390);
			통솔합1 = pk::min(통솔합1, 390);

			int off지력 = (max지력0 - max지력1);
			int off통솔 = (통솔합0 - 통솔합1);

			if (off지력 > 복병확률_최대지력차)
				off지력 = 복병확률_최대지력차;
			if( off지력 < -복병확률_최대지력차)
				off지력 = -복병확률_최대지력차;

			if (off통솔 > 복병확률_최대통솔차)
				off통솔 = 복병확률_최대통솔차;
			if (off통솔 < -복병확률_최대통솔차)
				off통솔 = -복병확률_최대통솔차;

			

			int 지력확률 = 50 + (off지력 / float(복병확률_최대지력차)) * 50;
			int 통솔확률 = 50 + (off통솔 / float(복병확률_최대통솔차)) * 50;

			int nn = 지력확률 * 복병확률_지력비중 + 통솔확률 * (1-복병확률_지력비중);
			//pk::printf("off지력:{}, off통솔:{}, {}\n", off지력, off통솔, nn);
			return nn;
		}

		array<FieldInfo@> makeField(pk::force@ force, pk::building@ building)
		{
			pk::list<pk::unit@> units0 = pk::get_unit_list(force);
			pk::list<pk::unit@> units;

			for (int i = 0; i < units0.count; i++)
			{
				pk::unit@ u = units0[i];
				pk::person@ leader = pk::get_person(u.leader);
				if(leader == null)
					continue;
				if(leader.service != building.get_id())
					continue;
				if(pk::is_in_water(u))
					continue;
				units.add(u);
			}

			array<FieldInfo@> fis;
			for (int i = 0; i < units.count; i++)
			{
				pk::unit@ u = units[i];
				FieldInfo fi;
				@fi.u = u;
				array<pk::point> arr = pk::range(u.get_pos(), 0, 복병_전세_판단_범위);
				int ucount = 0;
				int troops0 = 0;
				int troops1 = 0;
				for (int j = 0; j < arr.length; j++)
				{
					pk::point pt = arr[j];
					pk::unit@ u2= pk::is_valid_pos(pt) ? pk::get_unit(pt) : null;
					if (u2 == null || !pk::is_enemy(u, u2))
					{
						if (u2 != null) 
						{
							ucount++;
							troops0 += u2.troops;
						}
							
						continue;
					}
					if(u2.status != 부대상태_통상)
						continue;

					troops1 += u2.troops;
					fi.enemies.add(u2);

					pk::person@ p0 = pk::is_valid_person_id(u2.member[0]) ? pk::get_person(u2.member[0]) : null;
					pk::person@ p1 = pk::is_valid_person_id(u2.member[1]) ? pk::get_person(u2.member[1]) : null;
					pk::person@ p2 = pk::is_valid_person_id(u2.member[2]) ? pk::get_person(u2.member[2]) : null;

					if(p0!=null)
						fi.persons.add(p0);
					if (p1 != null)
						fi.persons.add(p1);
					if (p2 != null)
						fi.persons.add(p2);

				}
				//pk::printf("{},enemyCount:{},아군:{}\n", getNameLeader(u), fi.enemies.count, ucount);
				if(fi.enemies.count - ucount >= 복병_전세_판단_부대_수 && (troops1 - troops0) >= 복병_전세_판단_병력_차)
					fis.insertLast(fi);

			}

			for (int i = 0; i < fis.length; i++)
			{
				FieldInfo@ fi = fis[i];
				if (fi.persons.count > 1) 
				{
					fi.persons.sort(function(a, b) 
					{
						return a.stat[무장능력_지력] > b.stat[무장능력_지력];
					});
				}
				@fi.person지력 = fi.persons[0];


				if (fi.persons.count > 1)
				{
					fi.persons.sort(function(a, b)
					{
						return a.stat[무장능력_통솔] > b.stat[무장능력_통솔];
					});
				}

				fi.persons통솔 = fi.persons;
				if (fi.persons.count > 3)
				{
					pk::list<pk::person@> nps;
					for (int i = 0; i < 3; i++)
						nps.add(fi.persons[i]);
					fi.persons통솔 = nps;
				}
			}
			return fis;
		}

		bool isMarch(pk::person@ p, pk::building@ b)
		{
			return p != null && !pk::is_absent(p) && !p.action_done && !pk::is_unitize(p) && p.service == b.get_id() && p.get_force_id() == b.get_force_id() &&
				p.mibun != 신분_사망 && p.mibun != 신분_포로;
		}

		string getStrWeapon(int weapon)
		{
			string str = "";
			switch (weapon)
			{
			case 병기_검:str = "검병"; break;
			case 병기_창:str = "창병"; break;
			case 병기_극:str = "극병"; break;
			case 병기_노:str = "노병"; break;
			case 병기_군마:str = "기병"; break;
			case 병기_정란:str = "정란"; break;
			case 병기_충차:str = "충차"; break;
			case 병기_목수:str = "목수"; break;
			case 병기_투석:str = "투석"; break;
			case 병기_주가:str = "주가"; break;
			case 병기_누선:str = "누선"; break;
			case 병기_투함:str = "투함"; break;

			default:
				break;
			}
			return str;
		}
		string getStrWeapon(int weapon, pk::person@ p)
		{
			int weapon2 = pk::equipment_id_to_heishu(weapon);
			if (weapon2 < 0 || weapon2 >= 6)
				return "?";

			string str;
			switch (p.tekisei[weapon2])
			{
			case 0:str = "C"; break;
			case 1:str = "B"; break;
			case 2:str = "A"; break;
			case 3:str = "S"; break;
			case 4:str = "S1"; break;
			case 5:str = "S2"; break;
			case 6:str = "S3"; break;
			case 7:str = "S4"; break;
			case 8:str = "S5"; break;
			case 9:str = "S6"; break;
			case 10:str = "S7"; break;
			case 11:str = "S8"; break;
			case 12:str = "S9"; break;
			case 13:str = "X"; break;
			default:
				break;
			};
			return str;
		}
		string getStrSkill(int weapon, pk::person@ p)
		{
			string str = "";
			if (p == null)
				return str;
			if (pk::has_skill(p, 특기_패왕))
				str = str + (str == "" ? "패왕" : " 패왕");
			if (pk::has_skill(p, 특기_신장))
				str = str + (str == "" ? "신장" : " 신장");
			if (pk::has_skill(p, 특기_용장))
				str = str + (str == "" ? "용장" : " 용장");
			if (pk::has_skill(p, 특기_구축))
				str = str + (str == "" ? "구축" : " 구축");
			if (pk::has_skill(p, 특기_비장))
				str = str + (str == "" ? "비장" : " 비장");
			if (pk::has_skill(p, 특기_도주))
				str = str + (str == "" ? "도주" : " 도주");
			if (pk::has_skill(p, 특기_강행))
				str = str + (str == "" ? "강행" : " 강행");
			if (pk::has_skill(p, 특기_금강))
				str = str + (str == "" ? "금강" : " 금강");
			if (pk::has_skill(p, 특기_불굴))
				str = str + (str == "" ? "불굴" : " 불굴");
			if (pk::has_skill(p, 특기_철벽))
				str = str + (str == "" ? "철벽" : " 철벽");
			if (pk::has_skill(p, 특기_연전))
				str = str + (str == "" ? "연전" : " 연전");
			if (pk::has_skill(p, 특기_난전))
				str = str + (str == "" ? "난전" : " 난전");
			if (pk::has_skill(p, 특기_답파))
				str = str + (str == "" ? "답파" : " 답파");
			if (pk::has_skill(p, 특기_추진))
				str = str + (str == "" ? "추진" : " 추진");
			if (pk::has_skill(p, 특기_조타))
				str = str + (str == "" ? "조타" : " 조타");
			if (pk::has_skill(p, 특기_강습))
				str = str + (str == "" ? "강습" : " 강습");
			if (pk::has_skill(p, 특기_매복))
				str = str + (str == "" ? "매복" : " 매복");
			if (pk::has_skill(p, 특기_공성))
				str = str + (str == "" ? "공성" : " 공성");
			if (pk::has_skill(p, 특기_공신))
				str = str + (str == "" ? "공신" : " 공신");
			if (pk::has_skill(p, 특기_노발))
				str = str + (str == "" ? "노발" : " 노발");
			if (pk::has_skill(p, 특기_등갑))
				str = str + (str == "" ? "등갑" : " 등갑");
			if (pk::has_skill(p, 특기_강운))
				str = str + (str == "" ? "강운" : " 강운");
			if (pk::has_skill(p, 특기_혈로))
				str = str + (str == "" ? "혈로" : " 혈로");
			if (pk::has_skill(p, 특기_수장))
				str = str + (str == "" ? "수장" : " 수장");
			if (pk::has_skill(p, 특기_수신))
				str = str + (str == "" ? "수신" : " 수신");
			if (pk::has_skill(p, 특기_호위))
				str = str + (str == "" ? "호위" : " 호위");

			for (int i = 특기_화공; i <= 특기_축성; i++)
			{
				pk::skill@ s = pk::get_skill(i);
				if (pk::has_skill(p, i))
					str = str + (str == "" ? pk::decode(s.name) : (" " + pk::decode(s.name)));
			}
			if (pk::has_skill(p, 특기_지도))
				str = str + (str == "" ? "지도" : " 지도");
			if (pk::has_skill(p, 특기_친오))
				str = str + (str == "" ? "친오" : " 친오");
			if (pk::has_skill(p, 특기_친강))
				str = str + (str == "" ? "친강" : " 친강");
			if (pk::has_skill(p, 특기_친월))
				str = str + (str == "" ? "친월" : " 친얼");
			if (pk::has_skill(p, 특기_친만))
				str = str + (str == "" ? "친만" : " 친만");

			for (int i = 특기_끝; i < 255; i++)
			{
				pk::skill@ s = pk::get_skill(i);
				if (pk::has_skill(p, i))
					str = str + (str == "" ? pk::decode(s.name) : (" " + pk::decode(s.name)));
			}



			if (weapon == 병기_창 || weapon == 병기_극 || weapon == 병기_노 || weapon == 병기_군마)
			{
				if (pk::has_skill(p, 특기_위풍))
					str = str + (str == "" ? "위풍" : " 위풍");
				if (pk::has_skill(p, 특기_소탕))
					str = str + (str == "" ? "소탕" : " 소탕");
				if (pk::has_skill(p, 특기_급습))
					str = str + (str == "" ? "급습" : " 급습");
				if (pk::has_skill(p, 특기_기각))
					str = str + (str == "" ? "기각" : " 기각");
				if (pk::has_skill(p, 특기_포박))
					str = str + (str == "" ? "포박" : " 포박");
				if (pk::has_skill(p, 특기_정묘))
					str = str + (str == "" ? "정묘" : " 정묘");
				if (pk::has_skill(p, 특기_강탈))
					str = str + (str == "" ? "강탈" : " 강탈");
				if (pk::has_skill(p, 특기_보좌))
					str = str + (str == "" ? "보좌" : " 보좌");
			}
			if (weapon == 병기_창 || weapon == 병기_극 || weapon == 병기_군마)
			{
				if (pk::has_skill(p, 특기_심공))
					str = str + (str == "" ? "심공" : " 심공");
				if (pk::has_skill(p, 특기_맹장))
					str = str + (str == "" ? "맹장" : " 맹장");
			}

			if (weapon == 병기_창)
			{
				if (pk::has_skill(p, 특기_투신))
					str = str + (str == "" ? "투신" : " 투신");
				if (pk::has_skill(p, 특기_창신))
					str = str + (str == "" ? "창신" : " 창신");
				if (pk::has_skill(p, 특기_창장))
					str = str + (str == "" ? "창장" : " 창장");
			}
			if (weapon == 병기_극)
			{
				if (pk::has_skill(p, 특기_투신))
					str = str + (str == "" ? "투신" : " 투신");
				if (pk::has_skill(p, 특기_극신))
					str = str + (str == "" ? "극신" : " 극신");
				if (pk::has_skill(p, 특기_극장))
					str = str + (str == "" ? "극장" : " 극장");
			}
			if (weapon == 병기_노)
			{
				if (pk::has_skill(p, 특기_궁신))
					str = str + (str == "" ? "궁신" : " 궁신");
				if (pk::has_skill(p, 특기_궁장))
					str = str + (str == "" ? "궁장" : " 궁장");
				if (pk::has_skill(p, 특기_사수))
					str = str + (str == "" ? "사수" : " 사수");
			}
			if (weapon == 병기_군마)
			{
				if (pk::has_skill(p, 특기_기신))
					str = str + (str == "" ? "기신" : " 기신");
				if (pk::has_skill(p, 특기_기장))
					str = str + (str == "" ? "기장" : " 기장");
				if (pk::has_skill(p, 특기_백마))
					str = str + (str == "" ? "백마" : " 백마");
				if (pk::has_skill(p, 특기_질주))
					str = str + (str == "" ? "질주" : " 질주");
				if (pk::has_skill(p, 특기_사수))
					str = str + (str == "" ? "사수" : " 사수");
			}

			if (weapon == 병기_정란 || weapon == 병기_투석)
			{
				if (pk::has_skill(p, 특기_사정))
					str = str + (str == "" ? "사정" : " 사정");
			}

			return str;
		}



		UnitInfo@ getUnitInfo최근출진부대선택()
		{
			int count = int(pk::load(KEY_최근출진부대선택, 0, 0));
			if (count == 0)
				return null;

			int li = 1;

			array<UnitInfo@> uis;
			for (int i = 0; i < count; i++)
			{
				UnitInfo ui;
				int m0 = int(pk::load(KEY_최근출진부대선택, li++, -1));
				int m1 = int(pk::load(KEY_최근출진부대선택, li++, -1));
				int m2 = int(pk::load(KEY_최근출진부대선택, li++, -1));
				pk::person@ p0 = m0 != -1 ? pk::get_person(m0) : null;
				pk::person@ p1 = m1 != -1 ? pk::get_person(m1) : null;
				pk::person@ p2 = m2 != -1 ? pk::get_person(m2) : null;
				if (p0 != null)
					ui.members.add(p0);
				if (p1 != null)
					ui.members.add(p1);
				if (p2 != null)
					ui.members.add(p2);
				ui.weapon = int(pk::load(KEY_최근출진부대선택, li++, -1));
				ui.weaponWater = int(pk::load(KEY_최근출진부대선택, li++, -1));
				uis.insertLast(ui);
			}

			if (uis.length == 0)
				return null;


			int si = 0;
			UnitInfo@ selectedItem = null;
			while (true)
			{
				array<string> itemArr;
				int count = pk::min(uis.length, si + 4);
				if (si == 0)
					itemArr.insertLast(pk::encode("종료"));
				else
					itemArr.insertLast(pk::encode("뒤로"));

				for (int i = si; i < count; i++)
				{
					UnitInfo@ ui = uis[i];
					string strWeapon = getStrWeapon(ui.weapon);
					string strWeaponWater = getStrWeapon(ui.weaponWater);

					string str0 = 특기표시 && ui.members.count > 0 ? getStrSkill(ui.weapon, ui.members[0]) : "";
					string str1 = 특기표시 && ui.members.count > 1 ? getStrSkill(ui.weapon, ui.members[1]) : "";
					string str2 = 특기표시 && ui.members.count > 2 ? getStrSkill(ui.weapon, ui.members[2]) : "";
					string str0Weapon = ui.members.count > 0 ? getStrWeapon(ui.weapon, ui.members[0]) : "";
					string str1Weapon = ui.members.count > 1 ? getStrWeapon(ui.weapon, ui.members[1]) : "";
					string str2Weapon = ui.members.count > 2 ? getStrWeapon(ui.weapon, ui.members[2]) : "";

					bool bMarch0 = ui.members.count > 0 ? isMarch(ui.members[0], _building) : false;
					bool bMarch1 = ui.members.count > 1 ? isMarch(ui.members[1], _building) : false;
					bool bMarch2 = ui.members.count > 2 ? isMarch(ui.members[2], _building) : false;

					string str;
					str = pk::format("{},{},{}", strWeapon, (strWeaponWater != "" && strWeaponWater != "검병") ? strWeaponWater : "주가", pk::get_command(ui.members[0]));
					if (특기표시)
					{
						str = str + "," + pk::format(bMarch0 ? "\x1b[2x{}\x1b[0x({},{})" : "\x1b[29x{}\x1b[0x({},{})", getName(ui.members[0]), str0Weapon, str0);
						if (ui.members.count > 1 && ui.members[1] != null)
							str = str + "," + pk::format(bMarch1 ? "\x1b[2x{}\x1b[0x({},{})" : "\x1b[29x{}\x1b[0x({},{})", getName(ui.members[1]), str1Weapon, str1);
						if (ui.members.count > 2 && ui.members[2] != null)
							str = str + "," + pk::format(bMarch2 ? "\x1b[2x{}\x1b[0x({},{})" : "\x1b[29x{}\x1b[0x({},{})", getName(ui.members[2]), str2Weapon, str2);
					}
					else
					{
						str = str + "," + pk::format(bMarch0 ? "\x1b[2x{}\x1b[0x({})" : "\x1b[29x{}\x1b[0x({})", getName(ui.members[0]), str0Weapon);
						if (ui.members.count > 1 && ui.members[1] != null)
							str = str + "," + pk::format(bMarch1 ? "\x1b[2x{}\x1b[0x({})" : "\x1b[29x{}\x1b[0x({})", getName(ui.members[1]), str1Weapon);
						if (ui.members.count > 2 && ui.members[2] != null)
							str = str + "," + pk::format(bMarch2 ? "\x1b[2x{}\x1b[0x({})" : "\x1b[29x{}\x1b[0x({})", getName(ui.members[2]), str2Weapon);
					}
					itemArr.insertLast(pk::encode(str));
				}

				if (uis.length > 4)
				{
					if (si + 4 >= uis.length)
						itemArr.insertLast(pk::encode("종료"));
					else
						itemArr.insertLast(pk::encode("다음"));
				}

				int choose2 = pk::choose(pk::encode("부대를 선택해주십시오"), itemArr);
				if (uis.length > 4 && choose2 == itemArr.length - 1)
				{
					si = si + 4;
					if (si >= uis.length)
						return null;
				}
				else if (choose2 == 0)
				{
					si = si - 4;
					if (si < 0)
						return null;
				}
				else
				{
					@selectedItem = uis[si + choose2 - 1];
					break;
				}

			}

			if (selectedItem == null)
				return null;

			if (selectedItem.members[0] != null && !isMarch(selectedItem.members[0], _building))
			{
				pk::message_box(pk::encode(pk::format("{} 출진불가", getName(selectedItem.members[0]))));
				return null;
			}
			if (selectedItem.members.count > 1 && selectedItem.members[1] != null && !isMarch(selectedItem.members[1], _building))
			{
				pk::message_box(pk::encode(pk::format("{} 출진불가", getName(selectedItem.members[1]))));
				return null;
			}
			if (selectedItem.members.count > 2 && selectedItem.members[2] != null && !isMarch(selectedItem.members[2], _building))
			{
				pk::message_box(pk::encode(pk::format("{} 출진불가", getName(selectedItem.members[2]))));
				return null;
			}

			return selectedItem;
		}

		UnitInfo@ getUnitInfo()
		{
			UnitInfo@ ui = getUnitInfo최근출진부대선택();
			if (ui != null)
				return ui;

			pk::list<pk::person@> ps0 = pk::get_idle_person_list(_building);
			if (ps0.count == 0)
			{
				pk::message_box(pk::encode("출진가능한 무장이 없습니다."));
				return null;
			}

			pk::list<pk::person@> ps = pk::person_selector(pk::encode("무장선택"), pk::encode("출진할 무장을 선택하십시오"), ps0, 1, 3);
			if (ps.count == 0)
				return null;

			UnitInfo ui2;
			if (ps.count > 1)
			{
				ps.sort(function(a, b)
				{
					if ((a.mibun == 신분_군주 and b.mibun != 신분_군주) or (a.mibun != 신분_군주 and b.mibun == 신분_군주))
						return a.mibun == 신분_군주;


					if (a.rank == b.rank)
					{
						for (int i = 0; i < 무장능력_끝; i++)
						{
							if (a.max_stat[i] == b.max_stat[i])
								continue;
							return a.max_stat[i] > b.max_stat[i];
						}
						return true;
					}
					else if (a.rank < 0)
						return false;
					else if (b.rank < 0)
						return true;
					else
						return a.rank < b.rank;

				});
			}
			ui2.members = ps;
			return ui2;
		}

		int GetCityGold()
		{
			if (_city != null)
				return _city.gold;
			if (_gate != null)
				return _gate.gold;
			return _port.gold;
		}
		int GetCityTroops()
		{
			if (_city != null)
				return _city.troops;
			if (_gate != null)
				return _gate.troops;
			return _port.troops;
		}
		int GetCityFood()
		{
			if (_city != null)
				return _city.food;
			if (_gate != null)
				return _gate.food;
			return _port.food;
		}
		int GetCityWeaponAmount(int index)
		{
			if (_city != null)
				return _city.weapon_amount[index];
			if (_gate != null)
				return _gate.weapon_amount[index];
			return _port.weapon_amount[index];
		}

		string pad_callback(int line, int original_value, int current_value)
		{
			return pk::encode("병량 일수 입력");
		}


		pk::unit@ 출진(UnitInfo@ ui,bool b복병,pk::point targetPos)
		{
			pk::city@ city = pk::building_to_city(_building);

			int maxCommnd = pk::get_command(ui.members[0]);
			if (maxCommnd > GetCityTroops())
			{
				pk::message_box(pk::encode("도시에 병력이 부족합니다"));
				return null;
			}

			int weaponType = ui.weapon;
			int mount = 0;
			switch (ui.weapon)
			{
			case 병기_창:
			case 병기_극:
			case 병기_노:
			case 병기_군마:
				mount = maxCommnd; break;
			case 병기_충차:
			case 병기_정란:
			case 병기_투석:
			case 병기_목수:
				mount = 1;
			}
			if (mount > 0 && GetCityWeaponAmount(ui.weapon) < mount)
			{
				string str = "병종";
				switch (ui.weapon)
				{
				case 병기_창: str = "창"; break;
				case 병기_극: str = "극"; break;
				case 병기_노: str = "노"; break;
				case 병기_군마: str = "군마"; break;
				case 병기_충차: str = "충차"; break;
				case 병기_정란: str = "정란"; break;
				case 병기_투석: str = "투석"; break;
				case 병기_목수: str = "목수"; break;
				}
				pk::message_box(pk::encode(pk::format("{}이 부족합니다", str)));
				return null;
			}
			if (mount == 0)
			{
				weaponType = 병기_검;
				mount = maxCommnd;
			}

			auto result = pk::numberpad(pk::encode("병량 일수 입력"), 10, 500, 100, pk::numberpad_t(pad_callback));
			if (!result.second)
				return null;


			int foodA = prev_callback_166(10000, 10000);
			int food = maxCommnd * (float(result.first) / foodA);

			if (food > GetCityFood())
			{
				pk::message_box(pk::encode("도시에 병량이 부족합니다"));
				return null;
			}
			int 수군타입 = 병기_주가;
			if (ui.weapon == 병기_누선 || ui.weapon == 병기_투함)
				수군타입 = ui.weapon;
			if (ui.weaponWater == 병기_누선 || ui.weaponWater == 병기_투함)
				수군타입 = ui.weaponWater;

			if (수군타입 == 병기_누선 || 수군타입 == 병기_투함)
			{
				if (GetCityWeaponAmount(수군타입) == 0)
				{
					pk::message_box(pk::encode(pk::format("도시에 {}가 부족합니다.", 수군타입 == 병기_누선 ? "누선" : "투함")));
					return null;
				}
			}

			int gold = 0;
			pk::march_cmd_info mi;
			@mi.base = _building;
			mi.type = 부대종류_전투;
			mi.gold = gold;
			mi.food = food;
			mi.troops = maxCommnd;

			for (int i = 0; i < 12; i++)
			{
				mi.weapon_amount[i] = 0;
			}
			mi.weapon_id[0] = weaponType;
			mi.weapon_amount[0] = mount;
			mi.weapon_id[1] = 수군타입;
			mi.weapon_amount[1] = 1;

			if (ui.members.count > 1)
			{
				ui.members.sort(function(a, b)
				{
					if ((a.mibun == 신분_군주 and b.mibun != 신분_군주) or (a.mibun != 신분_군주 and b.mibun == 신분_군주))
						return a.mibun == 신분_군주;


					if (a.rank == b.rank)
					{
						for (int i = 0; i < 무장능력_끝; i++)
						{
							if (a.max_stat[i] == b.max_stat[i])
								continue;
							return a.max_stat[i] > b.max_stat[i];
						}
						return true;
					}
					else if (a.rank < 0)
						return false;
					else if (b.rank < 0)
						return true;
					else
						return a.rank < b.rank;

				});
			}

			mi.member[0] = ui.members[0].get_id();
			if (ui.members.count > 1 && ui.members[1] != null)
				mi.member[1] = ui.members[1].get_id();
			if (ui.members.count > 2 && ui.members[2] != null)
				mi.member[2] = ui.members[2].get_id();



			int uid = pk::command(mi);
			if (uid >= 0)
			{
				array<pk::point> arr = { targetPos };
				pk::unit@ unit = pk::get_unit(uid);
				pk::move(unit, arr);
				string str = get복병String(b복병);
				if (!b복병)
				{
					pk::set_status(unit,null, 부대상태_혼란, pk::rand(2) + 1);
					unit.action_done = true;
				}
				pk::message_box(pk::encode(str), pk::get_person(unit.leader));
				if (b복병)
				{
					_연속복병제한턴[_building.get_id()] = pk::get_elapsed_days();
				}
				return unit;
			}
			return null;
		}

		string get복병String(bool b복병)
		{
			if (b복병)
			{
				switch (pk::rand(5))
				{
				case 0: return "하하핫 기다리고 있었다";
				case 1: return "이거지~";
				case 2: return "어떠냐 다 쓸어주겠다";
				case 3: return "복병이다~";
				case 4: return "매복이다~";
				default:
					break;
				}
			}
			else 
			{
				switch (pk::rand(5))
				{
				case 0: return "통하지 않는가";
				case 1: return "어쩌된 일이냐";
				case 2: return "내통자가 있는가";
				case 3: return "아뿔사";
				case 4: return "침착하라~";
				default:
					break;
				}
			}
			return "";
		}

		pk::unit@ 출진AI(UnitInfo@ ui, bool b복병, pk::point targetPos,pk::building@ building,bool bPlayerWidth)
		{
			int maxCommnd = pk::get_command(ui.members[0]);
			if (maxCommnd > pk::get_troops(building))
			{
				return null;
			}

			int weaponType = ui.weapon;
			int mount = 0;
			switch (ui.weapon)
			{
			case 병기_창:
			case 병기_극:
			case 병기_노:
			case 병기_군마:
				mount = maxCommnd; break;
			case 병기_충차:
			case 병기_정란:
			case 병기_투석:
			case 병기_목수:
				mount = 1;
			}

			if (mount > 0 && pk::get_weapon_amount(building,ui.weapon) < mount)
			{
				return null;
			}

			int foodA = prev_callback_166(10000, 10000);
			int food = maxCommnd * (float(100) / foodA);

			if (food > pk::get_food(building))
			{
				return null;
			}
			int 수군타입 = 병기_주가;
			int gold = 0;

			pk::march_cmd_info mi;
			@mi.base = building;
			mi.type = 부대종류_전투;
			mi.gold = gold;
			mi.food = food;
			mi.troops = maxCommnd;

			for (int i = 0; i < 12; i++)
			{
				mi.weapon_amount[i] = 0;
			}
			mi.weapon_id[0] = weaponType;
			mi.weapon_amount[0] = mount;
			mi.weapon_id[1] = 수군타입;
			mi.weapon_amount[1] = 1;

			mi.member[0] = ui.members[0].get_id();
			if (ui.members.count > 1 && ui.members[1] != null)
				mi.member[1] = ui.members[1].get_id();
			if (ui.members.count > 2 && ui.members[2] != null)
				mi.member[2] = ui.members[2].get_id();

			int uid = pk::command(mi);
			if (uid >= 0)
			{
				array<pk::point> arr = { targetPos };
				pk::unit@ unit = pk::get_unit(uid);
				pk::move(unit, arr);
				string str = get복병String(b복병);
				if (!b복병)
				{
					pk::set_status(unit,null, 부대상태_혼란, pk::rand(2) + 1);
				}
				
				if(bPlayerWidth)
					pk::message_box(pk::encode(str), pk::get_person(unit.leader));
				else
					pk::say(pk::encode(str), pk::get_person(unit.leader), unit);

				pk::printf("AI복병:{}\n", getNameLeader(unit));
				if (b복병)
				{
					_연속복병제한턴[building.get_id()] = pk::get_elapsed_days();
				}

				return unit;
			}
			return null;


		}

		pk::point get복병실패위치(pk::unit@ u)
		{
			array<pk::point> arr = pk::range(u.get_pos(), 0, 복병_전세_판단_범위);
			array<pk::point> arr2;
			for (int i = 0; i < arr.length; i++)
			{
				pk::point pt = arr[i];
				if (!pk::is_valid_pos(pt))
					continue;
				if (pk::get_hex_object(pt) != null)
					continue;
				if (pk::is_on_fire(pt))
					continue;
				pk::hex@ h=pk::get_hex(pt);
				if (pk::is_water_terrain(h.terrain))
					continue;
				if(!pk::is_enabled_terrain(h.terrain))
					continue;

				arr2.insertLast(pt);
			}

			if (arr2.length == 0)
			{
				return pk::point(-1, -1);
			}

			return arr2[pk::rand(arr2.length)];
		}
		pk::point get복병성공위치(pk::unit@ u)
		{
			array<pk::point> arr = pk::range(u.get_pos(), 0, 복병_전세_판단_범위);
			pk::point maxPT(-1, -1);
			int maxAcount = -1;
			for (int i = 0; i < arr.length; i++)
			{
				pk::point pt = arr[i];
				if (!pk::is_valid_pos(pt))
					continue;
				if (pk::get_hex_object(pt) != null)
					continue;
				if (pk::is_on_fire(pt))
					continue;
				pk::hex@ h = pk::get_hex(pt);
				if (pk::is_water_terrain(h.terrain))
					continue;
				if (!pk::is_enabled_terrain(h.terrain))
					continue;


				int acount = 0;
				for (int j = 0; j < 6; j++)
				{
					pk::point pt2 = pk::get_neighbor_pos(pt, j, 1);
					if (!pk::is_valid_pos(pt2))
						continue;

					pk::unit@ u2 = pk::get_unit(pt2);
					if (u2 == null || !pk::is_enemy(u2, u))
						continue;

					acount++;
				}

				if (acount > maxAcount)
				{
					maxAcount = acount;
					maxPT = pt;
				}
			}
			return maxPT;
		}

		pk::unit@ _scene_attackerUnit = null;
		pk::unit@ _scene_targetUnit = null;
		pk::person@ _scene_attacker = null;
		pk::person@ _scene_target = null;

		void update인접(pk::unit@ u, pk::point pt)
		{
			array<pk::point> arr = pk::range(pt, 0, 복병_혼란_위보_적용_범위);

			pk::list<pk::unit@> units;

			for (int i = 0; i < arr.length; i++)
			{
				pk::point pt0 = arr[i];
				if(!pk::is_valid_pos(pt0))
					continue;

				pk::unit@ u2 = pk::get_unit(pt0);
				if(u2 == null || !pk::is_enemy(u,u2))
					continue;


				string str;
				switch (pk::rand(3))
				{
				case 0: str = "이부대는 어디서 나타난 것이냐"; break;
				case 1: str = "함정이다~"; break;
				case 2: str = "너무 깊게 들어 왔던가"; break;
				default:
					break;
				}

				switch (pk::rand(3))
				{
				case 0: pk::set_status(u2, null, 부대상태_혼란, pk::rand(3) + 1, true); break;
				case 1: pk::set_status(u2, null, 부대상태_위보, pk::rand(3) + 1, true); break;
				case 2: pk::add_energy(u2, -기력감소치, true); break;
				default:
					break;
				}

				
				int 통솔 = pk::get_best_member_stat(u2, 무장능력_통솔);
				if (통솔 > 100)
					통솔 = 100;
				
				int dam = 복병_최소데미지 + (복병_최대데미지 - 복병_최소데미지) * (1 - 통솔 / float(100.0));
				if (dam > u2.troops - 3)
					dam = u2.troops - 3;

				if(복병_병력감소 &&  dam>0)
					pk::add_troops(u2, -dam, true);

				updateAfter(u, u2);


				@u2 = pk::get_unit(u2.get_pos());
				if(u2==null)
					continue;

				pk::say(pk::encode(str), pk::get_person(u2.leader), u2);
				if (u2.troops == 3)
				{
					str = "병사들이 다 어딜갔느냐";
					pk::say(pk::encode(str), pk::get_person(u2.leader), u2);
				}

				units.add(u2);

			}

			if (pk::rand_bool(복병_일기토_확률))
			{
				pk::person@ maxP = null;
				int max = -1;
				for (int i = 0; i < 3; i++)
				{
					pk::person@ p = pk::get_person(u.member[i]);
					if(p==null)
						continue;

					if (p.stat[무장능력_무력] > max)
					{
						max = p.stat[무장능력_무력];
						@maxP = p;
					}
				}
				
				if (maxP != null)
				{
					pk::person@ maxP2 = null;
					pk::unit@ maxU = null;
					for (int i = 0; i < units.count; i++)
					{
						pk::unit@ u2 = units[i];
						for (int j = 0; j < 3; j++)
						{
							pk::person@ p2 = pk::get_person(u2.member[j]);
							if (p2 == null)
								continue;

							if (p2.stat[무장능력_무력] < max+복병_일기토_무력차 && p2.stat[무장능력_무력] > max-복병_일기토_무력차)
							{
								@maxP2 = p2;
								@maxU = u2;
								break;
							}
						}
						if (maxU != null)
							break;
					}

					if (maxU != null)
					{
						maxP2.hp = pk::max(maxP2.hp - 복병_일기토_체력감소, 1);
						if (u.is_player() || maxP2.is_player())
						{
							string str0;
							switch (pk::rand(3))
							{
							case 0: str0 = "흐흐흐 적장을 찾았다~";	break;
							case 1: str0 = "이때다!!!";	break;
							case 2: str0 = "기다리고 있었다~";	break;
							default:
								break;
							}
							pk::message_box(pk::encode(str0), maxP);

							string str1;
							switch (pk::rand(3))
							{
							case 0: str1 = "하필 이때...";	break;
							case 1: str1 = "허걱~";	break;
							case 2: str1 = "피할수 없군..";	break;
							default:
								break;
							}
							pk::message_box(pk::encode(str1), maxP2);
						}

						@_scene_attackerUnit = u;
						@_scene_targetUnit = maxU;
						@_scene_attacker = maxP;
						@_scene_target = maxP2;
						
						pk::scene(pk::scene_t(scene_일기토));

						@_scene_attackerUnit = null;
						@_scene_targetUnit = null;
						@_scene_attacker = null;
						@_scene_target = null;
					}
				}

			}
		}

		void scene_일기토()
		{
			//pk::printf("tatical 1:1 {},{}------------------\n",getName(_scene_attacker), getName(_scene_target));
			bool b0 = pk::is_player_controlled(_scene_attackerUnit);
			bool b1 = pk::is_player_controlled(_scene_targetUnit);

			pk::duel(_scene_attackerUnit, _scene_targetUnit, _scene_attacker, null, null, _scene_target, null, null, b0, b1, 0, b0 || b1);
		}


		pk::person@ getMax지력(pk::list<pk::unit@> units)
		{
			int max = -1;
			pk::person@ max지력 = null;
			for (int i = 0; i < units.count; i++)
			{
				pk::unit@ u = units[i];
				pk::person@ p0 = pk::is_valid_person_id(u.member[0]) ? pk::get_person(u.member[0]) : null;
				pk::person@ p1 = pk::is_valid_person_id(u.member[1]) ? pk::get_person(u.member[1]) : null;
				pk::person@ p2 = pk::is_valid_person_id(u.member[2]) ? pk::get_person(u.member[2]) : null;

				if (p0 != null && p0.stat[무장능력_지력] > max)
				{
					max = p0.stat[무장능력_지력];
					@max지력 = p0;
				}
				if (p1 != null && p1.stat[무장능력_지력] > max)
				{
					max = p1.stat[무장능력_지력];
					@max지력 = p1;
				}
				if (p2 != null && p2.stat[무장능력_지력] > max)
				{
					max = p2.stat[무장능력_지력];
					@max지력 = p2;
				}
			}

			return max지력;
		}

		bool updateAfter(pk::unit@ attacker, pk::hex_object@ target)
		{
			if (target == null)
				return false;

			pk::unit@ targetU = getUnit(target.get_pos());
			if (targetU != null && targetU.troops == 0)
			{
				int dist = pk::get_distance(attacker.get_pos(), target.get_pos());
				//pk::printf("kill start\n");
				pk::create_death_effect(targetU, attacker, target.get_pos());
				int gold = targetU.gold;
				int food = targetU.food;
				pk::kill(targetU, attacker, dist == 1, attacker.weapon == 병기_극);

				//if (dist == 1)
				//{
				//	if(gold * 0.5 >0)
				//		pk::add_gold(attacker, gold * 0.5, true);
				//	if(food * 0.5 >0)
				//		pk::add_food(attacker, food * 0.25, true);
				//}

				//pk::printf("kill end\n");
				if (attacker.has_skill(특기_앙양))
					pk::add_energy(attacker, int(pk::core::skill_constant(attacker, 특기_앙양)), true);

				return false;
			}
			else
			{
				pk::building@ b = pk::hex_object_to_building(target);
				if (b != null)
				{
					if (b.hp <= 0)
					{
						pk::city@ city = pk::building_to_city(b);
						pk::gate@ gate = pk::building_to_gate(b);
						pk::port@ port = pk::building_to_port(b);

						if (city != null || gate != null || port != null)
						{
							pk::set_hp(b, 1);
						}
						else
						{
							int cid = pk::is_valid_pos(b.get_pos()) ? pk::get_city_id(b.get_pos()) : -1;
							pk::building@ b2 = cid >= 0 ? pk::get_building(cid) : null;
							if (b.facility == 시설_군둔농 || b.facility == 시설_농장 || b.facility == 시설_농장2단 || b.facility == 시설_농장2단)
							{
								if (b2 != null)
								{
									int a = pk::get_food(b2) * 0.025;
									pk::add_food(attacker, a, true);

									int a2 = pk::get_food(b2) * 0.125;
									pk::add_food(b2, -a2, true);
								}
							}
							if (b.facility == 시설_시장 || b.facility == 시설_시장2단 || b.facility == 시설_시장3단 || b.facility == 시설_대시장 || b.facility == 시설_어시장 ||
								b.facility == 시설_부절태 || b.facility == 시설_인재부 || b.facility == 시설_외교부 || b.facility == 시설_계략부 || b.facility == 시설_암시장)
							{
								if (b2 != null)
								{
									int a = pk::get_gold(b2) * 0.03;
									pk::add_gold(attacker, a, true);

									int a2 = pk::get_gold(b2) * 0.125;
									pk::add_gold(b2, -a2, true);
								}
							}

							pk::destroy_cmd_info di;
							@di.building = b;
							pk::command(di);
							return false;
						}
					}
				}
			}
			return true;

		}

		bool 복병Handler()
		{
			array<FieldInfo@> fis = makeField(_force, _building);
			if (fis.length == 0)
			{
				pk::message_box(pk::encode("전세가 불리한곳이 없습니다."));
				return true;
			}

			UnitInfo@ ui = getUnitInfo();
			if (ui == null)
				return  true;



			pk::list<pk::person@> ps0 = pk::get_idle_person_list(_building);
			if(ps0.count>1)
				ps0.sort(function(a, b) 
				{
					return a.stat[무장능력_지력] > b.stat[무장능력_지력];
				});

			pk::list<pk::person@> ps;
			for (int i = 0; i < ui.members.count; i++)
			{
				ps.add(ui.members[i]);
			}

			pk::person@ 지력장수 = null;
			bool bFound0 = true;
			for (int i = 0; i < ps0.count; i++)
			{
				pk::person@ p = ps0[i];
				bool bFound = false;
				for (int j = 0; j < ps.count; j++)
				{
					pk::person@ p2 = ps[j];
					if (p2.get_id() == p.get_id())
					{
						bFound = true;
						break;
					}
				}
				if (!bFound)
				{
					bFound0 = false;
					@지력장수 = p;
					break;
				}
			}
			if (bFound0)
			{
				pk::message_box(pk::encode("지력무장이 없습니다."));
				return true;
			}

			for (int i = 0; i < fis.length; i++)
			{
				FieldInfo@ fi = fis[i];
				fi.percent = 복병확률(ps, 지력장수, fi);
			}

			if (fis.length > 1)
			{
				fis.sort(function(a, b) 
				{
					return a.percent >= b.percent;
				});
			}

			string str = pk::format("전장:\x1b[2x{}\x1b[0x,출진:\x1b[2x{}\x1b[0x\n확률:\x1b[2x{}\x1b[0x,지력장수:\x1b[2x{}({})\x1b[0x VS \x1b[2x{}({})\x1b[0x",
				getNameLeader(fis[0].u), getName(ui.members[0]), fis[0].percent, getName(지력장수), 지력장수.stat[무장능력_지력], getName(fis[0].person지력), fis[0].person지력.stat[무장능력_지력]);
			if (!pk::yes_no(pk::encode(str)))
				return true;


			if (ui.weapon == -1)
			{
				array<string> sarr = { pk::encode("창병"),pk::encode("극병"),pk::encode("노병"),pk::encode("기병"),pk::encode("충차/목수"),pk::encode("정란/투석") };
				int choose = pk::choose(sarr);
				switch (choose)
				{
				case 0: ui.weapon = 병기_창; break;
				case 1: ui.weapon = 병기_극; break;
				case 2: ui.weapon = 병기_노; break;
				case 3: ui.weapon = 병기_군마; break;
				case 4:
					if (pk::has_tech(fis[0].u, 기교_목수개발))
						ui.weapon = 병기_목수;
					else
						ui.weapon = 병기_충차;
					break;
				case 5:
					if (pk::has_tech(fis[0].u, 기교_투석개발))
						ui.weapon = 병기_투석;
					else
						ui.weapon = 병기_정란;
					break;

				default:
					break;
				}
			}

			
			bool b복병 = 복병실행(ps, 지력장수,fis[0]);
			if (!b복병)
			{
				pk::point pt = get복병실패위치(fis[0].u);
				if (pt.x == -1)
				{
					pk::message_box(pk::encode("복병을 출진할 위치가 없습니다."));
					return true;
				}
				
				pk::unit@ u = 출진(ui, b복병, pt);
				if (u!=null)
				{
					pk::play_se(13);
					_district.ap = _district.ap - 행동력;
					ps[ps.count - 1].action_done = true;

					string str = "";
					switch (pk::rand(3))
					{
					case 0: str = "하하핫 그정도는 대비하고 있다"; break;
					case 1: str = "그럴줄 알았다 와하핫"; break;
					case 2: str = "내 손바닥 안이다 핫핫"; break;
					default:
						break;
					}
					pk::message_box(pk::encode(str), getMax지력(fis[0].enemies));
				}
			}
			else 
			{
				pk::point maxPT = get복병성공위치(fis[0].u);
				if (maxPT.x == -1)
				{
					pk::message_box(pk::encode("복병을 출진할 위치가 없습니다."));
					return true;
				}
				pk::unit@ u = 출진(ui, b복병, maxPT);
				if (u!=null)
				{
					string str = "";
					switch (pk::rand(3))
					{
					case 0: str = "당했다.."; break;
					case 1: str = "여기서 복병이.."; break;
					case 2: str = "이럴리가 없는데.."; break;
					default:
						break;
					}
					pk::message_box(pk::encode(str), getMax지력(fis[0].enemies));

					
					pk::play_se(10);
					_district.ap = _district.ap - 행동력;
					update인접(u,maxPT);
					ps[ps.count - 1].action_done = true;
				}
			}
			
			
			return true;
		}

		//AI 복병////////////////////////////////////////////////////////////////////////////////////


		int getWeapon(pk::list<pk::person@> ps)
		{
			int max = -1;
			int max병종 = -1;

			for (int i = 0; i < ps.count; i++)
			{
				pk::person@ p0 = ps[i];
				if(p0 == null)
					continue;

				for (int j = 0;  j < 6;  j++)
				{
					if(j == 병종_수군 || j == 병종_병기)
						continue;

					if (p0.tekisei[j] > max)
					{
						max = p0.tekisei[j];
						max병종 = j;
					}
				}
			}
			return max병종;
		}

		void onTurnStart복병(array<FieldInfo@> fis, pk::list<pk::person@> ps0,pk::building@ building)
		{
			if (ps0.count > 1)
			{
				ps0.sort(function(a, b)
				{
					return a.stat[무장능력_통솔] > b.stat[무장능력_통솔];
				});
			}

			pk::list<pk::person@> ps통솔;
			pk::list<pk::person@> ps;

			int count = pk::min(ps0.count, 3);
			for (int i = 0; i < count; i++)
			{
				ps통솔.add(ps0[i]);
			}

			bool b지력참가 = true;
			pk::person@ 지력장수 = ps0[0];
			if (ps0.count > 1)
			{
				ps0.sort(function(a, b)
				{
					return a.stat[무장능력_지력] > b.stat[무장능력_지력];
				});

				@지력장수 = ps0[0];

				for (int i = 0; i < ps0.count; i++)
				{
					pk::person@ p = ps0[i];
					bool bFound = false;
				
					for (int j = 0; j < ps통솔.count; j++)
					{
						pk::person@ p2 = ps통솔[j];
						if (p.get_id() == p2.get_id())
						{
							bFound = true;
							break;
						}
					}
					b지력참가=bFound = true;
				}
			}
			if (지력장수 == null)
			{
				return;
			}
				

			for (int i = 0; i < ps통솔.count; i++)
			{
				ps.add(ps통솔[i]);
			}
			

			for (int i = 0; i < fis.length; i++)
			{
				FieldInfo@ fi = fis[i];
				fi.percent = 복병확률(ps,지력장수, fi);
			}

			if (fis.length > 1)
			{
				fis.sort(function(a, b)
				{
					return a.percent >= b.percent;
				});
			}

			pk::printf("AI복병확률:{},{},지력장수:{}({}),상대지력:{}({})\n", getNameLeader(fis[0].u), fis[0].percent, getName(지력장수), 지력장수.stat[무장능력_지력], getName(fis[0].person지력), fis[0].person지력.stat[무장능력_지력]);
			if (fis[0].percent < AI_복병활률_실행_최소치)
				return;


			UnitInfo ui;
			if (ps통솔.count > 1)
			{
				ps통솔.sort(function(a, b)
				{
					if ((a.mibun == 신분_군주 and b.mibun != 신분_군주) or (a.mibun != 신분_군주 and b.mibun == 신분_군주))
						return a.mibun == 신분_군주;


					if (a.rank == b.rank)
					{
						for (int i = 0; i < 무장능력_끝; i++)
						{
							if (a.max_stat[i] == b.max_stat[i])
								continue;
							return a.max_stat[i] > b.max_stat[i];
						}
						return true;
					}
					else if (a.rank < 0)
						return false;
					else if (b.rank < 0)
						return true;
					else
						return a.rank < b.rank;

				});
			}

			ui.members = ps통솔;
			ui.weapon = getWeapon(ps통솔);
			if (ui.weapon == -1)
				return;
			bool b복병 = 복병실행(ps,지력장수,fis[0]);
			pk::point pt;
			if (b복병)
				pt = get복병성공위치(fis[0].u);
			else
				pt = get복병실패위치(fis[0].u);
			if (pt.x == -1)
				return;

			bool bPlayerWith = false;
			for (int i = 0; i < fis[0].enemies.count; i++)
			{
				pk::unit@ uu = fis[0].enemies[i];
				if (uu.is_player())
				{
					bPlayerWith = true;
					break;
				}
			}

			pk::unit@ u = 출진AI(ui, b복병, pt, building, bPlayerWith);

			if (u!=null)
			{
				if (bPlayerWith)
				{
					if (b복병)
					{
						string str = "";
						switch (pk::rand(5))
						{
						case 0: str = "당했다.."; break;
						case 1: str = "여기서 복병이.."; break;
						case 2: str = "이럴리가 없는데.."; break;
						case 3: str = "너무 깊게 들어왔구나.."; break;
						case 4: str = "이런건 있을수가 없다.."; break;
						default:
							break;
						}
						pk::message_box(pk::encode(str), getMax지력(fis[0].enemies));
					}
					else 
					{
						string str = "";
						switch (pk::rand(4))
						{
						case 0: str = "하하핫 그정도는 대비하고 있다"; break;
						case 1: str = "그럴줄 알았다 와하핫"; break;
						case 2: str = "내 손바닥 안이다 핫핫"; break;
						case 3: str = "낄낄낄 그정도냐~"; break;
						default:
							break;
						}
						pk::message_box(pk::encode(str), getMax지력(fis[0].enemies));
					}
				}
				if (b복병)
					update인접(u, pt);

				if(!b지력참가)
					지력장수.action_done = true;
			}
		}

		void onTurnStart(pk::force@ f)
		{
			if (f.is_player())
				return;

			pk::list<pk::city@> cities = pk::get_city_list(f);
			for (int i = 0; i < cities.count; i++)
			{
				pk::building@ b = pk::city_to_building(cities[i]);
				if (b == null)
				{
					//pk::printf("building return:{}\n", getName(f));
					continue;
				}

				if(연속_복병_제한 && pk::get_elapsed_days() < _연속복병제한턴[b.get_id()]+ 연속_복병_제한_일)
					continue;
					

				array<FieldInfo@> fis=makeField(f, b);
				if (fis.length == 0)
				{
					//pk::printf("fid return:{}\n", getName(b));
					continue;
				}
					

				pk::list<pk::person@> ps = pk::get_idle_person_list(b);
				if (ps.count < 4)
				{
					//pk::printf("idle return:{},{}\n", getName(b), ps.count);
					continue;
				}
					

				onTurnStart복병(fis, ps,b);
			}

		}


		string getName(pk::force@ f)
		{
			if (f == null)
				return "null";
			return getName(pk::get_person(f.kunshu));
		}
		string getName(pk::object@ obj)
		{
			return obj != null ? pk::decode(pk::get_name(obj)) : "null";
		}
		string getNameLeader(pk::unit@ obj)
		{
			if (obj == null)
				return "null";
			pk::person@ p = pk::get_person(obj.leader);
			if (p == null)
				return "null";
			return pk::decode(pk::get_name(p));
		}
		pk::unit@ getUnit(pk::point pos)
		{
			return pk::is_valid_pos(pos) ? pk::get_unit(pos) : null;
		}


	}

	Main main;
}

