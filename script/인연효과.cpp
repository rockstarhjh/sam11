/*
@만든이: 크래픽스
@Update: 2023.9.8,최초배포
@Update: 2023.9.9,소속이 없는경우에 잘못판단하는 버그수정
@Update: 2023.9.10,인덱스에러수정
*/

namespace 인연효과
{
	const int 효과_주악_소_값 = 5;
	const int 효과_주악_중_값 = 10;
	const int 효과_주악_대_값 = 15;
	
	const int 효과_전능상승_소_값 = 1;
	const int 효과_전능상승_중_값 = 2;
	const int 효과_전능상승_대_값 = 3;

	const int 효과_공적상승_소_값 = 10000;
	const int 효과_공적상승_중_값 = 20000;
	const int 효과_공적상승_대_값 = 30000;

	const int 효과_전법_공격_소_값 = 10;
	const int 효과_전법_공격_중_값 = 15;
	const int 효과_전법_공격_대_값 = 20;

	const int 효과_전법_방어_소_값 = 10;
	const int 효과_전법_방어_중_값 = 15;
	const int 효과_전법_방어_대_값 = 20;

	const int 효과_공격상승_소_값 = 10;
	const int 효과_공격상승_중_값 = 15;
	const int 효과_공격상승_대_값 = 20;
	const int 효과_방어상승_소_값 = 10;
	const int 효과_방어상승_중_값 = 15;
	const int 효과_방어상승_대_값 = 20;

	const int 효과_보좌_소_값 = 20;
	const int 효과_보좌_중_값 = 40;
	const int 효과_보좌_대_값 = 60;

	const int 효과_계략_소_값 = 10;
	const int 효과_계략_중_값 = 15;
	const int 효과_계략_대_값 = 20;

	const int 효과_계략방어_소_값 = 10;
	const int 효과_계략방어_중_값 = 15;
	const int 효과_계략방어_대_값 = 20;

	const int 효과_인접기력감소_값 = 5;
	const int 효과_인접병사감소_값 = 3;


	const int 효과_전능상승_소 = 0;
	const int 효과_전능상승_중 = 1;
	const int 효과_전능상승_대 = 2;
	const int 효과_공격상승_소 = 3;
	const int 효과_공격상승_중 = 4;
	const int 효과_공격상승_대 = 5;
	const int 효과_방어상승_소 = 6;
	const int 효과_방어상승_중 = 7;
	const int 효과_방어상승_대 = 8;
	const int 효과_보좌_소 = 9;
	const int 효과_보좌_중 = 10;
	const int 효과_보좌_대 = 11;
	const int 효과_주악_소 = 12;
	const int 효과_주악_중 = 13;
	const int 효과_주악_대 = 14;
	const int 효과_전법_공격_소 = 15;
	const int 효과_전법_공격_중 = 16;
	const int 효과_전법_공격_대 = 17;
	const int 효과_전법_방어_소 = 18;
	const int 효과_전법_방어_중 = 19;
	const int 효과_전법_방어_대 = 20;
	const int 효과_계략_소 = 21;
	const int 효과_계략_중 = 22;
	const int 효과_계략_대 = 23;
	const int 효과_계략방어_소 = 24;
	const int 효과_계략방어_중 = 25;
	const int 효과_계략방어_대 = 26;
	const int 효과_인접기력감소 = 27;
	const int 효과_인접병사감소 = 28;
	const int 효과_전적성상승 = 29;
	const int 효과_전법반드시성공 = 30;
	const int 효과_명경 = 31;
	const int 효과_통찰 = 32;
	const int 효과_경국 = 33;
	const int 효과_세력인정효과 = 34;
	const int 효과_공적상승_소 = 35;
	const int 효과_공적상승_중 = 36;
	const int 효과_공적상승_대 = 37;



	array<GroupInfo> 인연리스트 =
	{
		GroupInfo("오호대장군",{효과_전능상승_대},{무장_관우,무장_장비,무장_조운,무장_마초,무장_황충}),
		GroupInfo("오자양장",{효과_전능상승_중,효과_전법_공격_중,효과_전법_방어_중},{무장_장료,무장_장합,무장_서황,무장_악진,무장_우금}),
		GroupInfo("관중십장",{효과_전능상승_소,효과_공격상승_소,효과_방어상승_소},{무장_마등,무장_한수,무장_양추,무장_마완,무장_성의,무장_정은,무장_장횡,무장_이감,무장_양흥,무장_후선}),
		GroupInfo("강동십이호신",{효과_전능상승_중,효과_전적성상승},{무장_정보,무장_황개,무장_한당,무장_장흠,무장_주태,무장_진무,무장_동습,무장_감녕,무장_능통,무장_서성,무장_반장,무장_정봉}),
		GroupInfo("강동이교",{효과_주악_대},{무장_소교, 무장_대교}),
		GroupInfo("의형제",{효과_보좌_중},{무장_유비, 무장_관우,무장_장비}),
		GroupInfo("황제의상",{효과_세력인정효과},{무장_유비, 무장_손권,무장_조비}),
		GroupInfo("오대도독",{효과_전적성상승,효과_전법_공격_중,효과_전법_방어_중},{무장_주유, 무장_육손,무장_노숙,무장_육항,무장_여몽}),
		GroupInfo("천하무쌍",{효과_인접기력감소,효과_인접병사감소},{무장_여포, 무장_항적}),
		GroupInfo("천하기재",{효과_계략_대,효과_계략방어_대},{무장_제갈량, 무장_사마의}),
		GroupInfo("복룡봉추",{효과_계략_중,효과_계략방어_중},{무장_제갈량, 무장_방통}),
		GroupInfo("수경문하",{효과_계략_소,효과_계략방어_소},{무장_제갈량, 무장_방통,무장_서서}),
		GroupInfo("궁신",{효과_전법반드시성공},{무장_황충, 무장_하후연,무장_여포,무장_국의,무장_장흠}),
		GroupInfo("원소쌍벽",{효과_공격상승_중},{무장_안량, 무장_문추}),
		GroupInfo("왕좌지재",{효과_전능상승_대},{무장_순욱,무장_저수, 무장_장소 ,무장_장완}),
		GroupInfo("묘령여인",{효과_경국,효과_전능상승_중},{무장_여영기,무장_마운,무장_황월영,무장_포삼랑}),
		GroupInfo("이민족",{효과_전능상승_소,효과_공격상승_소,효과_방어상승_소},{무장_맹획,무장_축융,무장_사마가,무장_올돌골})
		//GroupInfo("테스트",{효과_전능상승_대,효과_계략_대,효과_전적성상승,효과_공적상승_대},{무장_장료,무장_진궁})
	};
	

	class GroupInfo
	{
		array<int> idsApply;
		array<int> ids;
		pk::list<pk::person@> members;
		pk::list<pk::person@> membersApply;
		string name;
		bool b = false;
		pk::force@ force = null;

		GroupInfo() {}
		GroupInfo(string name0, array<int> arrIds, array<int> arrMember)
		{
			name = name0;
			ids = arrIds;
			for (int i = 0; i < arrMember.length; i++)
			{
				pk::person@ p = pk::get_person(arrMember[i]);
				if (p == null) 
					continue;
				members.add(p);
			}
		}
	};

	const int KEY = pk::hash("인연효과");
	
	class Main
	{
		pk::func200_t@ prev_callback_200;
		pk::func209_t@ prev_callback_209;
		pk::func202_t@ prev_callback_202;
		pk::func206_t@ prev_callback_206;
		pk::func155_t@ prev_callback_155;


		Main()
		{
			@prev_callback_209 = cast<pk::func209_t@>(pk::get_func(209));
			pk::reset_func(209);
			pk::set_func(209, pk::func209_t(callback209부대공격));                // 202 전법 성공 확률

			@prev_callback_202 = cast<pk::func202_t@>(pk::get_func(202));
			pk::reset_func(202);
			pk::set_func(202, pk::func202_t(callback202전법성공확률));

			@prev_callback_200 = cast<pk::func200_t@>(pk::get_func(200));
			pk::reset_func(200);
			pk::set_func(200, pk::func200_t(callback200지원공격확률));

			@prev_callback_206 = cast<pk::func206_t@>(pk::get_func(206));
			pk::reset_func(206);
			pk::set_func(206, pk::func206_t(callback206계략성공확률));                // 202 전법 성공 확률

			@prev_callback_155 = cast<pk::func155_t@>(pk::get_func(155));
			pk::reset_func(155);
			pk::set_func(155, pk::func155_t(callback155월별충성도));                // 202 전법 성공 확률



			
			pk::bind(174, pk::trigger174_t(부대행동완료));
			pk::bind(107, pk::trigger107_t(onNewDay));
			pk::bind(111, pk::trigger111_t(onTurnStart));
			pk::bind(102, pk::trigger102_t(Init));
			pk::bind(105, pk::trigger105_t(SaveData));


			
			pk::menu_item item인연효과;
			item인연효과.menu = 2;
			item인연효과.is_enabled = pk::menu_item_is_enabled_t(Is인연효과Enabled);
			item인연효과.get_text = pk::menu_item_get_text_t(Get인연효과Text);
			item인연효과.get_desc = pk::menu_item_get_desc_t(Get인연효과Desc);
			item인연효과.handler = pk::menu_item_handler_t(인연효과Handler);
			pk::add_menu_item(item인연효과);

			
		}
		void Init()
		{
			LoadData();
			bool b = false;

			for (int i = 0; i < 인연리스트.length; i++)
			{
				GroupInfo@ gi = 인연리스트[i];
				if (gi.b) 
				{
					b = true;
					break;
				}
			}
			if (!b)
				onNewDay();
		}

		void LoadData()
		{
			for (int i = 0; i < 인연리스트.length; i++)
			{
				GroupInfo@ gi = 인연리스트[i];
				gi.idsApply = {};
				gi.membersApply.clear();
				@gi.force = null;
				gi.b = false;
			}


			int count = int(pk::load(KEY, 0, 0));
			int li = 1;
			for (int i = 0; i < count; i++)
			{
				GroupInfo@ gi = 인연리스트[i];
				int bi = int(pk::load(KEY, li++, 0));
				gi.b = bi == 1;
				@gi.force = pk::get_force(int(pk::load(KEY, li++, 0)));
				int count2 = int(pk::load(KEY, li++, 0));
				for (int k = 0; k < count2; k++)
				{
					gi.idsApply.insertLast(int(pk::load(KEY, li++, 0)));
				}
				int count3 = int(pk::load(KEY, li++, 0));
				for (int k = 0; k < count3; k++)
				{
					pk::person@ p = pk::get_person(int(pk::load(KEY, li++, 0)));
					if(p==null)
						continue;
					gi.membersApply.add(p);
				}
			}
		}
		void SaveData(int file_id)
		{
			pk::store(KEY, 0, 인연리스트.length);
			int si = 1;
			for (int i = 0; i < 인연리스트.length; i++)
			{
				GroupInfo@ gi = 인연리스트[i];
				pk::store(KEY, si++, gi.b ? 1 : 0);
				pk::store(KEY, si++, gi.force!=null ? gi.force.get_id() : -1);
				pk::store(KEY, si++, gi.idsApply.length);
				for (int k = 0; k < gi.idsApply.length; k++)
				{
					pk::store(KEY, si++, gi.idsApply[k]);
				}
				pk::store(KEY, si++, gi.membersApply.count);
				for (int k = 0; k < gi.membersApply.count; k++)
				{
					pk::store(KEY, si++, gi.membersApply[k].get_id());
				}
			}
		}

		bool Is인연효과Enabled()
		{
			return true;
		}
		string Get인연효과Text()
		{
			return pk::encode("인연효과확인");
		}
		string Get인연효과Desc()
		{
			return pk::encode("세력별 인연효과 적용 상황을 확인합니다.");
		}
		bool 인연효과Handler()
		{
			int si = 0;
			GroupInfo@ selected = null;
			while (true)
			{
				array<string> itemArr;
				array<GroupInfo@> itemArr2;
				int count = pk::min(인연리스트.length, si + 4);
				if (si == 0)
					itemArr.insertLast(pk::encode("종료"));
				else
					itemArr.insertLast(pk::encode("뒤로"));
				for (int i = si; i < count; i++)
				{
					GroupInfo@ gi = 인연리스트[i];
					string str = gi.name + ",";
					str = str + (gi.force != null ? getNameForce(gi.force) : "없음");
					for (int k = 0; k < gi.members.count; k++)
					{
						if(gi.b)
							str = str + ","+pk::format("\x1b[1x{}\x1b[0x", getName(gi.members[k]));
						else
							str = str + "," + pk::format("{}", getName(gi.members[k]));

					}
					itemArr.insertLast(pk::encode(str));
					itemArr2.insertLast(gi);
				}
				if (si + 4 >= 인연리스트.length)
					itemArr.insertLast(pk::encode("종료"));
				else
					itemArr.insertLast(pk::encode("다음"));

				int choose = pk::choose(pk::encode("확인하십시오"), itemArr);
				if (choose == itemArr.length - 1)
				{
					si = si + 4;
					if (si >= 인연리스트.length)
						break;
				}
				else if (choose == 0)
				{
					si = si - 4;
					if (si < 0)
						break;
				}
				else
				{
					@selected = itemArr2[choose - 1];
				}
				if (selected == null)
					continue;
			}
			return true;
		}

		string getNameForce(pk::force@ f)
		{
			pk::person@ kunshu = pk::get_person(f.kunshu);
			return getName(kunshu);
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


		int callback155월별충성도(pk::building@ building, pk::person@ person)
		{
			int n = prev_callback_155(building, person);


			pk::force@ force = pk::get_force(person.get_force_id());

			array<GroupInfo@> arr = getForces(force, { 효과_세력인정효과 });
			if (arr.length > 0)
				n = 0;


			return n;
		}


		int callback200지원공격확률(pk::unit@ assister, pk::unit@ attacker, pk::unit@ target)
		{
			int n = prev_callback_200(assister,attacker,target);
			if (checkGroup(assister, 효과_보좌_대)) 
				n = pk::min(n + 효과_보좌_대_값, 100);
			else if (checkGroup(assister, 효과_보좌_중))
				n = pk::min(n + 효과_보좌_중_값, 100);
			else if (checkGroup(assister, 효과_보좌_소))
				n = pk::min(n + 효과_보좌_소_값, 100);

			return n;
		}
		pk::int_bool callback206계략성공확률(pk::unit@ src, const pk::point& in src_pos, const pk::point& in dst_pos, int strategy_id)
		{
			pk::int_bool re = prev_callback_206(src,src_pos,dst_pos,strategy_id);

			if (checkGroup(src, 효과_계략_대) && re.second == false) 
			{
				re.first = pk::min(re.first + 효과_계략_대_값, 100);
				pk::printf("consipracy {}\n", re.first);

			}
				
			else if (checkGroup(src, 효과_계략_중) && re.second == false)
				re.first = pk::min(re.first + 효과_계략_중_값, 100);
			else if (checkGroup(src, 효과_계략_소) && re.second == false)
				re.first = pk::min(re.first + 효과_계략_소_값, 100);

			if (checkGroup(src, 효과_경국) && src.has_skill(특기_경국) && re.second == false)
				re.first = pk::min(re.first * 2,100);


			pk::unit@ u = pk::get_unit(dst_pos);
			if (u != null && re.second == false) 
			{
				if (checkGroup(u, 효과_명경) && (strategy_id == 계략_교란 || strategy_id == 계략_위보) ||
					checkGroup(u, 효과_통찰))
				{
					re.first = 0;
					re.second = true;
				}
				else if (checkGroup(u, 효과_계략방어_대))
					re.first = pk::max(re.first - 효과_계략방어_대_값, 0);
				else if (checkGroup(u, 효과_계략방어_중))
					re.first = pk::max(re.first - 효과_계략방어_중_값, 0);
				else if (checkGroup(u, 효과_계략방어_소))
					re.first = pk::max(re.first - 효과_계략방어_소_값, 0);
			}

			return re;

		}

		int callback202전법성공확률(pk::unit@ attacker, const pk::point& in pos, pk::hex_object@ target, int tactics_id)
		{
			int n = prev_callback_202(attacker, pos, target, tactics_id);

			if (checkGroup(attacker, 효과_전법반드시성공))
				return 100;
			if (checkGroup(attacker, 효과_전법_공격_대)) 
				n = pk::min(n + 효과_전법_공격_대_값, 100);
			else if (checkGroup(attacker, 효과_전법_공격_중))
				n = pk::min(n + 효과_전법_공격_중_값, 100);
			else if (checkGroup(attacker, 효과_전법_공격_소))
				n = pk::min(n + 효과_전법_공격_소_값, 100);

			if (checkGroup(attacker, 효과_전법_방어_대))
				n = pk::max(n - 효과_전법_방어_대_값, 0);
			else if (checkGroup(attacker, 효과_전법_방어_중))
				n = pk::max(n - 효과_전법_방어_중_값, 0);
			else if (checkGroup(attacker, 효과_전법_방어_소))
				n = pk::max(n - 효과_전법_방어_소_값, 0);

			return n;
		}
		void callback209부대공격(pk::damage_info& info, pk::unit@ attacker, int tactics_id, const pk::point& in target_pos, int type, int critical, bool ambush)
		{
			prev_callback_209(info, attacker, tactics_id, target_pos, type, critical, ambush);

			if (checkGroup(attacker, 효과_공격상승_대)) 
				info.troops_damage = info.troops_damage + info.troops_damage * 효과_공격상승_대_값 / 100.0;
			else if (checkGroup(attacker, 효과_공격상승_중))
				info.troops_damage = info.troops_damage + info.troops_damage * 효과_공격상승_중_값 / 100.0;
			else if (checkGroup(attacker, 효과_공격상승_소))
				info.troops_damage = info.troops_damage + info.troops_damage * 효과_공격상승_소_값 / 100.0;

			pk::unit@ u = pk::get_unit(target_pos);
			if (u != null)
			{
				if (checkGroup(u, 효과_방어상승_대))
					info.troops_damage = info.troops_damage - info.troops_damage * 효과_방어상승_대_값 / 100.0;
				else if (checkGroup(u, 효과_방어상승_중))
					info.troops_damage = info.troops_damage - info.troops_damage * 효과_방어상승_중_값 / 100.0;
				else if (checkGroup(u, 효과_방어상승_소))
					info.troops_damage = info.troops_damage - info.troops_damage * 효과_방어상승_소_값 / 100.0;
			}

		}

		void 부대행동완료(pk::unit@ unit)
		{
			if (unit == null)
				return;

			if (checkGroup(unit, 효과_인접기력감소)) 
			{
				for (int i = 0; i < 방향_끝; i++)
				{
					pk::point pt = pk::get_neighbor_pos(unit.get_pos(), i, 1);
					pk::unit@ u = pk::get_unit(pt);
					if(u==null || !pk::is_enemy(unit,u))
						continue;

					pk::add_energy(u, -효과_인접기력감소_값, true);
				}
			}
			if (checkGroup(unit, 효과_인접병사감소))
			{
				for (int i = 0; i < 방향_끝; i++)
				{
					pk::point pt = pk::get_neighbor_pos(unit.get_pos(), i, 1);
					pk::unit@ u = pk::get_unit(pt);
					if (u == null || !pk::is_enemy(unit, u))
						continue;

					pk::add_troops(u, - u.troops*효과_인접병사감소_값/100.0, true);
					if (u.troops == 0)
						pk::kill(u, unit, true, unit.weapon == 병기_극);

				}
			}
		}

		bool checkGroup(pk::unit@ u, int id)
		{
			return getGroup(u, id) != null;
		}

		GroupInfo@ getGroup(pk::unit@ u, int id)
		{
			pk::person@ p0 = u.member[0] >= 0 and u.member[0] < 무장_끝 ? pk::get_person(u.member[0]) : null;
			GroupInfo@ gi = getGroup(p0, id);
			if (gi != null)
				return gi;
			pk::person@ p1 = u.member[1] >= 0 and u.member[1] < 무장_끝 ? pk::get_person(u.member[1]) : null;
			GroupInfo@ gi1 = getGroup(p1, id);
			if (gi1 != null)
				return gi1;
			pk::person@ p2 = u.member[2] >= 0 and u.member[2] < 무장_끝 ? pk::get_person(u.member[2]) : null;
			GroupInfo@ gi2 = getGroup(p2, id);
			return gi2;
		}

		GroupInfo@ getGroup(pk::person@ p, int id)
		{
			if (p == null)
				return null;
			pk::force@ force = pk::get_force(p.get_force_id());
			array<GroupInfo@> arr = getForces(force, { id });
			if (arr.length == 0)
				return null;

			for (int i = 0; i < arr.length; i++)
			{
				GroupInfo@ gi = arr[i];
				for (int k = 0; k < gi.members.count; k++)
				{
					pk::person@ pp = gi.members[k];
					if (pp.get_id() == p.get_id())
						return gi;
				}

			}
			return null;
		}

		array<GroupInfo@> getForces(pk::unit@ unit, array<int> ids)
		{
			pk::force@ f = pk::get_force(unit.get_force_id());
			array<GroupInfo@> arr = getForces(f, ids);
			if (arr.length == 0)
				return arr;


			array<GroupInfo@> arr2;
			for (int i = 0; i < arr.length; i++)
			{
				GroupInfo@ gi = arr[i];
				bool bFound = false;
				for (int k = 0; k < ids.length; k++)
				{
					int id = ids[k];
					for (int j = 0; j < gi.ids.length; j++)
					{
						if (id == gi.ids[j])
						{
							bFound = true;
							break;
						}
					}
					if (bFound)
						break;
				}
				if (bFound)
					arr2.insertLast(gi);
			}
			return arr2;
		}

		array<GroupInfo@> getForces(pk::force@ force,array<int> ids)
		{
			array<GroupInfo@> gis;
			if (force == null)
				return gis;

			for (int i = 0; i < 인연리스트.length; i++)
			{
				GroupInfo@ gi = 인연리스트[i];
				if (gi.force != null && gi.force.get_id() == force.get_id())
				{
					bool bFound = false;
					for (int k = 0; k < ids.length; k++)
					{
						int id = ids[k];
						for (int j = 0; j < gi.ids.length; j++)
						{
							if (id == gi.ids[j])
							{
								bFound = true;
								break;
							}
						}
						if (bFound)
							break;
					}
					if(bFound)
						gis.insertLast(gi);
				}
			}
			return gis;
		}

		void apply전능(pk::list<pk::person@> persons, int value)
		{
			for (int i = 0; i < persons.count; i++)
			{
				pk::person@ p = persons[i];
				for (int k = 0; k < 무장능력_끝; k++)
				{
					//p.stat[k] = p.stat[k] + value;
					p.stat_exp[k] = p.stat_exp[k] + value * int(pk::core["무장.능력상승필요경험치"]);
					//pk::add_stat_exp(p, k, value * int(pk::core["무장.능력상승필요경험치"]));
					//pk::add_base_stat(p, k, value);
					
				}
				p.update();
			}
		}
		void apply공적(pk::list<pk::person@> persons, int value)
		{
			for (int i = 0; i < persons.count; i++)
			{
				pk::person@ p = persons[i];
				p.kouseki += value;
			}

		}
		void apply적성(pk::list<pk::person@> persons, int value)
		{
			for (int i = 0; i < persons.count; i++)
			{
				pk::person@ p = persons[i];
				for (int k = 0; k < 병종_끝; k++)
				{
					p.tekisei[k] = p.tekisei[k] + value;
				}
			}
		}

		void onNewDay()
		{
			for (int i = 0; i < 인연리스트.length; i++)
			{
				GroupInfo@ gi = 인연리스트[i];
				pk::force@ force = null;
				for (int k = 0; k < gi.members.count; k++)
				{
					pk::person@ p = gi.members[k];
					if (force != null && force.get_id() != p.get_force_id()) 
					{
						@force = null;
						break;
					}
					pk::force@ f = pk::get_force(p.get_force_id());
					if (f == null)
					{
						@force = null;
						break;
					}
					@force = f;
				}
				if ((force == null || (gi.force!=null && force.get_id() != gi.force.get_id())) && gi.b)
				{
					for (int k = 0; k < gi.idsApply.length; k++)
					{
						int id = gi.idsApply[k];
						switch (id)
						{
						case 효과_전능상승_소:apply전능(gi.membersApply, -효과_전능상승_소_값); break;
						case 효과_전능상승_중:apply전능(gi.membersApply, -효과_전능상승_중_값); break;
						case 효과_전능상승_대:apply전능(gi.membersApply, -효과_전능상승_대_값); break;
						case 효과_공적상승_소:apply공적(gi.membersApply, -효과_공적상승_소_값); break;
						case 효과_공적상승_중:apply공적(gi.membersApply, -효과_공적상승_중_값); break;
						case 효과_공적상승_대:apply공적(gi.membersApply, -효과_공적상승_대_값); break;
						case 효과_전적성상승:apply적성(gi.membersApply, -1); break;

						default:
							break;
						}
					}
					string str2 = "";
					for (int j = 0; j < gi.membersApply.count; j++)
						str2 = str2 + "," + pk::format("\x1b[1x{}\x1b[0x", getName(gi.membersApply[j]));

					gi.membersApply.clear();
					string str = pk::format("\x1b[2x{}군\x1b[0x, \x1b[29x{}\x1b[0x 상실{}",getNameForce(gi.force),gi.name,str2);
					pk::history_log(pk::point(), gi.force.color, pk::encode(str));
				}
				
				if ((force != null && !gi.b) || (gi.force!=null && force!=null && force.get_id() != gi.force.get_id()))
				{
					for (int k = 0; k < gi.ids.length; k++)
					{
						int id = gi.ids[k];
						switch (id)
						{
						case 효과_전능상승_소:apply전능(gi.members, 효과_전능상승_소_값); break;
						case 효과_전능상승_중:apply전능(gi.members, 효과_전능상승_중_값); break;
						case 효과_전능상승_대:apply전능(gi.members, 효과_전능상승_대_값); break;
						case 효과_공적상승_소:apply공적(gi.members, 효과_공적상승_소_값); break;
						case 효과_공적상승_중:apply공적(gi.members, 효과_공적상승_중_값); break;
						case 효과_공적상승_대:apply공적(gi.members, 효과_공적상승_대_값); break;
						case 효과_전적성상승:apply적성(gi.members, 1); break;

						default:
							break;
						}
					}
					gi.idsApply = gi.ids;
					gi.membersApply = gi.members;

					string str2 = "";
					for (int j = 0; j < gi.members.count; j++)
						str2 = str2 + "," + pk::format("\x1b[1x{}\x1b[0x", getName(gi.members[j]));

					string str = pk::format("\x1b[2x{}군\x1b[0x, \x1b[1x{}\x1b[0x 획득{}", getNameForce(force), gi.name,str2);
					pk::history_log(pk::point(), force.color, pk::encode(str));
				}

				@gi.force = force;
				gi.b = force != null;

			}
		}
		void onTurnStart(pk::force@ force)
		{
			array<GroupInfo@> gis = getForces(force, { 효과_주악_대,효과_주악_중, 효과_주악_소});
			if (gis.length == 0)
				return;

			for (int i = 0; i < gis.length; i++)
			{
				GroupInfo@ gi = gis[i];
				array<pk::unit@> units;
				for (int k = 0; k < gi.members.count; k++)
				{
					pk::person@ p = gi.members[i];
					pk::unit@ u = pk::get_unit(p.get_pos());
					if(u==null)
						continue;
					if (units.findByRef(u) == -1)
						units.insertLast(u);
				}

				for (int k = 0; k < gi.ids.length; k++)
				{
					int id = gi.ids[k];
					if(id != 효과_주악_소 && id != 효과_주악_중 && id != 효과_주악_대)
						continue;

					int value = id == 효과_주악_소 ? 효과_주악_소_값 : id == 효과_주악_중 ? 효과_주악_중_값 : 효과_주악_대_값;
					for (int j = 0; j < units.length; j++)
					{
						pk::unit@ u = units[j];
						pk::add_energy(u, value, true);
					}
				}
			}
		}
		
	}
	Main main;
}
