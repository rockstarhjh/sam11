/*
@������: ũ���Ƚ�
@Update: 2023.9.8,���ʹ���
@Update: 2023.9.9,�Ҽ��� ���°�쿡 �߸��Ǵ��ϴ� ���׼���
@Update: 2023.9.10,�ε�����������
*/

namespace �ο�ȿ��
{
	const int ȿ��_�־�_��_�� = 5;
	const int ȿ��_�־�_��_�� = 10;
	const int ȿ��_�־�_��_�� = 15;
	
	const int ȿ��_���ɻ��_��_�� = 1;
	const int ȿ��_���ɻ��_��_�� = 2;
	const int ȿ��_���ɻ��_��_�� = 3;

	const int ȿ��_�������_��_�� = 10000;
	const int ȿ��_�������_��_�� = 20000;
	const int ȿ��_�������_��_�� = 30000;

	const int ȿ��_����_����_��_�� = 10;
	const int ȿ��_����_����_��_�� = 15;
	const int ȿ��_����_����_��_�� = 20;

	const int ȿ��_����_���_��_�� = 10;
	const int ȿ��_����_���_��_�� = 15;
	const int ȿ��_����_���_��_�� = 20;

	const int ȿ��_���ݻ��_��_�� = 10;
	const int ȿ��_���ݻ��_��_�� = 15;
	const int ȿ��_���ݻ��_��_�� = 20;
	const int ȿ��_�����_��_�� = 10;
	const int ȿ��_�����_��_�� = 15;
	const int ȿ��_�����_��_�� = 20;

	const int ȿ��_����_��_�� = 20;
	const int ȿ��_����_��_�� = 40;
	const int ȿ��_����_��_�� = 60;

	const int ȿ��_�跫_��_�� = 10;
	const int ȿ��_�跫_��_�� = 15;
	const int ȿ��_�跫_��_�� = 20;

	const int ȿ��_�跫���_��_�� = 10;
	const int ȿ��_�跫���_��_�� = 15;
	const int ȿ��_�跫���_��_�� = 20;

	const int ȿ��_������°���_�� = 5;
	const int ȿ��_�������簨��_�� = 3;


	const int ȿ��_���ɻ��_�� = 0;
	const int ȿ��_���ɻ��_�� = 1;
	const int ȿ��_���ɻ��_�� = 2;
	const int ȿ��_���ݻ��_�� = 3;
	const int ȿ��_���ݻ��_�� = 4;
	const int ȿ��_���ݻ��_�� = 5;
	const int ȿ��_�����_�� = 6;
	const int ȿ��_�����_�� = 7;
	const int ȿ��_�����_�� = 8;
	const int ȿ��_����_�� = 9;
	const int ȿ��_����_�� = 10;
	const int ȿ��_����_�� = 11;
	const int ȿ��_�־�_�� = 12;
	const int ȿ��_�־�_�� = 13;
	const int ȿ��_�־�_�� = 14;
	const int ȿ��_����_����_�� = 15;
	const int ȿ��_����_����_�� = 16;
	const int ȿ��_����_����_�� = 17;
	const int ȿ��_����_���_�� = 18;
	const int ȿ��_����_���_�� = 19;
	const int ȿ��_����_���_�� = 20;
	const int ȿ��_�跫_�� = 21;
	const int ȿ��_�跫_�� = 22;
	const int ȿ��_�跫_�� = 23;
	const int ȿ��_�跫���_�� = 24;
	const int ȿ��_�跫���_�� = 25;
	const int ȿ��_�跫���_�� = 26;
	const int ȿ��_������°��� = 27;
	const int ȿ��_�������簨�� = 28;
	const int ȿ��_��������� = 29;
	const int ȿ��_�����ݵ�ü��� = 30;
	const int ȿ��_��� = 31;
	const int ȿ��_���� = 32;
	const int ȿ��_�汹 = 33;
	const int ȿ��_��������ȿ�� = 34;
	const int ȿ��_�������_�� = 35;
	const int ȿ��_�������_�� = 36;
	const int ȿ��_�������_�� = 37;



	array<GroupInfo> �ο�����Ʈ =
	{
		GroupInfo("��ȣ���屺",{ȿ��_���ɻ��_��},{����_����,����_���,����_����,����_����,����_Ȳ��}),
		GroupInfo("���ھ���",{ȿ��_���ɻ��_��,ȿ��_����_����_��,ȿ��_����_���_��},{����_���,����_����,����_��Ȳ,����_����,����_���}),
		GroupInfo("���߽���",{ȿ��_���ɻ��_��,ȿ��_���ݻ��_��,ȿ��_�����_��},{����_����,����_�Ѽ�,����_����,����_����,����_����,����_����,����_��Ⱦ,����_�̰�,����_����,����_�ļ�}),
		GroupInfo("��������ȣ��",{ȿ��_���ɻ��_��,ȿ��_���������},{����_����,����_Ȳ��,����_�Ѵ�,����_����,����_����,����_����,����_����,����_����,����_����,����_����,����_����,����_����}),
		GroupInfo("�����̱�",{ȿ��_�־�_��},{����_�ұ�, ����_�뱳}),
		GroupInfo("������",{ȿ��_����_��},{����_����, ����_����,����_���}),
		GroupInfo("Ȳ���ǻ�",{ȿ��_��������ȿ��},{����_����, ����_�ձ�,����_����}),
		GroupInfo("���뵵��",{ȿ��_���������,ȿ��_����_����_��,ȿ��_����_���_��},{����_����, ����_����,����_���,����_����,����_����}),
		GroupInfo("õ�Ϲ���",{ȿ��_������°���,ȿ��_�������簨��},{����_����, ����_����}),
		GroupInfo("õ�ϱ���",{ȿ��_�跫_��,ȿ��_�跫���_��},{����_������, ����_�縶��}),
		GroupInfo("�������",{ȿ��_�跫_��,ȿ��_�跫���_��},{����_������, ����_����}),
		GroupInfo("���湮��",{ȿ��_�跫_��,ȿ��_�跫���_��},{����_������, ����_����,����_����}),
		GroupInfo("�ý�",{ȿ��_�����ݵ�ü���},{����_Ȳ��, ����_���Ŀ�,����_����,����_����,����_����}),
		GroupInfo("���ҽֺ�",{ȿ��_���ݻ��_��},{����_�ȷ�, ����_����}),
		GroupInfo("��������",{ȿ��_���ɻ��_��},{����_����,����_����, ����_��� ,����_���}),
		GroupInfo("���ɿ���",{ȿ��_�汹,ȿ��_���ɻ��_��},{����_������,����_����,����_Ȳ����,����_�����}),
		GroupInfo("�̹���",{ȿ��_���ɻ��_��,ȿ��_���ݻ��_��,ȿ��_�����_��},{����_��ȹ,����_����,����_�縶��,����_�õ���})
		//GroupInfo("�׽�Ʈ",{ȿ��_���ɻ��_��,ȿ��_�跫_��,ȿ��_���������,ȿ��_�������_��},{����_���,����_����})
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

	const int KEY = pk::hash("�ο�ȿ��");
	
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
			pk::set_func(209, pk::func209_t(callback209�δ����));                // 202 ���� ���� Ȯ��

			@prev_callback_202 = cast<pk::func202_t@>(pk::get_func(202));
			pk::reset_func(202);
			pk::set_func(202, pk::func202_t(callback202��������Ȯ��));

			@prev_callback_200 = cast<pk::func200_t@>(pk::get_func(200));
			pk::reset_func(200);
			pk::set_func(200, pk::func200_t(callback200��������Ȯ��));

			@prev_callback_206 = cast<pk::func206_t@>(pk::get_func(206));
			pk::reset_func(206);
			pk::set_func(206, pk::func206_t(callback206�跫����Ȯ��));                // 202 ���� ���� Ȯ��

			@prev_callback_155 = cast<pk::func155_t@>(pk::get_func(155));
			pk::reset_func(155);
			pk::set_func(155, pk::func155_t(callback155�����漺��));                // 202 ���� ���� Ȯ��



			
			pk::bind(174, pk::trigger174_t(�δ��ൿ�Ϸ�));
			pk::bind(107, pk::trigger107_t(onNewDay));
			pk::bind(111, pk::trigger111_t(onTurnStart));
			pk::bind(102, pk::trigger102_t(Init));
			pk::bind(105, pk::trigger105_t(SaveData));


			
			pk::menu_item item�ο�ȿ��;
			item�ο�ȿ��.menu = 2;
			item�ο�ȿ��.is_enabled = pk::menu_item_is_enabled_t(Is�ο�ȿ��Enabled);
			item�ο�ȿ��.get_text = pk::menu_item_get_text_t(Get�ο�ȿ��Text);
			item�ο�ȿ��.get_desc = pk::menu_item_get_desc_t(Get�ο�ȿ��Desc);
			item�ο�ȿ��.handler = pk::menu_item_handler_t(�ο�ȿ��Handler);
			pk::add_menu_item(item�ο�ȿ��);

			
		}
		void Init()
		{
			LoadData();
			bool b = false;

			for (int i = 0; i < �ο�����Ʈ.length; i++)
			{
				GroupInfo@ gi = �ο�����Ʈ[i];
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
			for (int i = 0; i < �ο�����Ʈ.length; i++)
			{
				GroupInfo@ gi = �ο�����Ʈ[i];
				gi.idsApply = {};
				gi.membersApply.clear();
				@gi.force = null;
				gi.b = false;
			}


			int count = int(pk::load(KEY, 0, 0));
			int li = 1;
			for (int i = 0; i < count; i++)
			{
				GroupInfo@ gi = �ο�����Ʈ[i];
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
			pk::store(KEY, 0, �ο�����Ʈ.length);
			int si = 1;
			for (int i = 0; i < �ο�����Ʈ.length; i++)
			{
				GroupInfo@ gi = �ο�����Ʈ[i];
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

		bool Is�ο�ȿ��Enabled()
		{
			return true;
		}
		string Get�ο�ȿ��Text()
		{
			return pk::encode("�ο�ȿ��Ȯ��");
		}
		string Get�ο�ȿ��Desc()
		{
			return pk::encode("���º� �ο�ȿ�� ���� ��Ȳ�� Ȯ���մϴ�.");
		}
		bool �ο�ȿ��Handler()
		{
			int si = 0;
			GroupInfo@ selected = null;
			while (true)
			{
				array<string> itemArr;
				array<GroupInfo@> itemArr2;
				int count = pk::min(�ο�����Ʈ.length, si + 4);
				if (si == 0)
					itemArr.insertLast(pk::encode("����"));
				else
					itemArr.insertLast(pk::encode("�ڷ�"));
				for (int i = si; i < count; i++)
				{
					GroupInfo@ gi = �ο�����Ʈ[i];
					string str = gi.name + ",";
					str = str + (gi.force != null ? getNameForce(gi.force) : "����");
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
				if (si + 4 >= �ο�����Ʈ.length)
					itemArr.insertLast(pk::encode("����"));
				else
					itemArr.insertLast(pk::encode("����"));

				int choose = pk::choose(pk::encode("Ȯ���Ͻʽÿ�"), itemArr);
				if (choose == itemArr.length - 1)
				{
					si = si + 4;
					if (si >= �ο�����Ʈ.length)
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


		int callback155�����漺��(pk::building@ building, pk::person@ person)
		{
			int n = prev_callback_155(building, person);


			pk::force@ force = pk::get_force(person.get_force_id());

			array<GroupInfo@> arr = getForces(force, { ȿ��_��������ȿ�� });
			if (arr.length > 0)
				n = 0;


			return n;
		}


		int callback200��������Ȯ��(pk::unit@ assister, pk::unit@ attacker, pk::unit@ target)
		{
			int n = prev_callback_200(assister,attacker,target);
			if (checkGroup(assister, ȿ��_����_��)) 
				n = pk::min(n + ȿ��_����_��_��, 100);
			else if (checkGroup(assister, ȿ��_����_��))
				n = pk::min(n + ȿ��_����_��_��, 100);
			else if (checkGroup(assister, ȿ��_����_��))
				n = pk::min(n + ȿ��_����_��_��, 100);

			return n;
		}
		pk::int_bool callback206�跫����Ȯ��(pk::unit@ src, const pk::point& in src_pos, const pk::point& in dst_pos, int strategy_id)
		{
			pk::int_bool re = prev_callback_206(src,src_pos,dst_pos,strategy_id);

			if (checkGroup(src, ȿ��_�跫_��) && re.second == false) 
			{
				re.first = pk::min(re.first + ȿ��_�跫_��_��, 100);
				pk::printf("consipracy {}\n", re.first);

			}
				
			else if (checkGroup(src, ȿ��_�跫_��) && re.second == false)
				re.first = pk::min(re.first + ȿ��_�跫_��_��, 100);
			else if (checkGroup(src, ȿ��_�跫_��) && re.second == false)
				re.first = pk::min(re.first + ȿ��_�跫_��_��, 100);

			if (checkGroup(src, ȿ��_�汹) && src.has_skill(Ư��_�汹) && re.second == false)
				re.first = pk::min(re.first * 2,100);


			pk::unit@ u = pk::get_unit(dst_pos);
			if (u != null && re.second == false) 
			{
				if (checkGroup(u, ȿ��_���) && (strategy_id == �跫_���� || strategy_id == �跫_����) ||
					checkGroup(u, ȿ��_����))
				{
					re.first = 0;
					re.second = true;
				}
				else if (checkGroup(u, ȿ��_�跫���_��))
					re.first = pk::max(re.first - ȿ��_�跫���_��_��, 0);
				else if (checkGroup(u, ȿ��_�跫���_��))
					re.first = pk::max(re.first - ȿ��_�跫���_��_��, 0);
				else if (checkGroup(u, ȿ��_�跫���_��))
					re.first = pk::max(re.first - ȿ��_�跫���_��_��, 0);
			}

			return re;

		}

		int callback202��������Ȯ��(pk::unit@ attacker, const pk::point& in pos, pk::hex_object@ target, int tactics_id)
		{
			int n = prev_callback_202(attacker, pos, target, tactics_id);

			if (checkGroup(attacker, ȿ��_�����ݵ�ü���))
				return 100;
			if (checkGroup(attacker, ȿ��_����_����_��)) 
				n = pk::min(n + ȿ��_����_����_��_��, 100);
			else if (checkGroup(attacker, ȿ��_����_����_��))
				n = pk::min(n + ȿ��_����_����_��_��, 100);
			else if (checkGroup(attacker, ȿ��_����_����_��))
				n = pk::min(n + ȿ��_����_����_��_��, 100);

			if (checkGroup(attacker, ȿ��_����_���_��))
				n = pk::max(n - ȿ��_����_���_��_��, 0);
			else if (checkGroup(attacker, ȿ��_����_���_��))
				n = pk::max(n - ȿ��_����_���_��_��, 0);
			else if (checkGroup(attacker, ȿ��_����_���_��))
				n = pk::max(n - ȿ��_����_���_��_��, 0);

			return n;
		}
		void callback209�δ����(pk::damage_info& info, pk::unit@ attacker, int tactics_id, const pk::point& in target_pos, int type, int critical, bool ambush)
		{
			prev_callback_209(info, attacker, tactics_id, target_pos, type, critical, ambush);

			if (checkGroup(attacker, ȿ��_���ݻ��_��)) 
				info.troops_damage = info.troops_damage + info.troops_damage * ȿ��_���ݻ��_��_�� / 100.0;
			else if (checkGroup(attacker, ȿ��_���ݻ��_��))
				info.troops_damage = info.troops_damage + info.troops_damage * ȿ��_���ݻ��_��_�� / 100.0;
			else if (checkGroup(attacker, ȿ��_���ݻ��_��))
				info.troops_damage = info.troops_damage + info.troops_damage * ȿ��_���ݻ��_��_�� / 100.0;

			pk::unit@ u = pk::get_unit(target_pos);
			if (u != null)
			{
				if (checkGroup(u, ȿ��_�����_��))
					info.troops_damage = info.troops_damage - info.troops_damage * ȿ��_�����_��_�� / 100.0;
				else if (checkGroup(u, ȿ��_�����_��))
					info.troops_damage = info.troops_damage - info.troops_damage * ȿ��_�����_��_�� / 100.0;
				else if (checkGroup(u, ȿ��_�����_��))
					info.troops_damage = info.troops_damage - info.troops_damage * ȿ��_�����_��_�� / 100.0;
			}

		}

		void �δ��ൿ�Ϸ�(pk::unit@ unit)
		{
			if (unit == null)
				return;

			if (checkGroup(unit, ȿ��_������°���)) 
			{
				for (int i = 0; i < ����_��; i++)
				{
					pk::point pt = pk::get_neighbor_pos(unit.get_pos(), i, 1);
					pk::unit@ u = pk::get_unit(pt);
					if(u==null || !pk::is_enemy(unit,u))
						continue;

					pk::add_energy(u, -ȿ��_������°���_��, true);
				}
			}
			if (checkGroup(unit, ȿ��_�������簨��))
			{
				for (int i = 0; i < ����_��; i++)
				{
					pk::point pt = pk::get_neighbor_pos(unit.get_pos(), i, 1);
					pk::unit@ u = pk::get_unit(pt);
					if (u == null || !pk::is_enemy(unit, u))
						continue;

					pk::add_troops(u, - u.troops*ȿ��_�������簨��_��/100.0, true);
					if (u.troops == 0)
						pk::kill(u, unit, true, unit.weapon == ����_��);

				}
			}
		}

		bool checkGroup(pk::unit@ u, int id)
		{
			return getGroup(u, id) != null;
		}

		GroupInfo@ getGroup(pk::unit@ u, int id)
		{
			pk::person@ p0 = u.member[0] >= 0 and u.member[0] < ����_�� ? pk::get_person(u.member[0]) : null;
			GroupInfo@ gi = getGroup(p0, id);
			if (gi != null)
				return gi;
			pk::person@ p1 = u.member[1] >= 0 and u.member[1] < ����_�� ? pk::get_person(u.member[1]) : null;
			GroupInfo@ gi1 = getGroup(p1, id);
			if (gi1 != null)
				return gi1;
			pk::person@ p2 = u.member[2] >= 0 and u.member[2] < ����_�� ? pk::get_person(u.member[2]) : null;
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

			for (int i = 0; i < �ο�����Ʈ.length; i++)
			{
				GroupInfo@ gi = �ο�����Ʈ[i];
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

		void apply����(pk::list<pk::person@> persons, int value)
		{
			for (int i = 0; i < persons.count; i++)
			{
				pk::person@ p = persons[i];
				for (int k = 0; k < ����ɷ�_��; k++)
				{
					//p.stat[k] = p.stat[k] + value;
					p.stat_exp[k] = p.stat_exp[k] + value * int(pk::core["����.�ɷ»���ʿ����ġ"]);
					//pk::add_stat_exp(p, k, value * int(pk::core["����.�ɷ»���ʿ����ġ"]));
					//pk::add_base_stat(p, k, value);
					
				}
				p.update();
			}
		}
		void apply����(pk::list<pk::person@> persons, int value)
		{
			for (int i = 0; i < persons.count; i++)
			{
				pk::person@ p = persons[i];
				p.kouseki += value;
			}

		}
		void apply����(pk::list<pk::person@> persons, int value)
		{
			for (int i = 0; i < persons.count; i++)
			{
				pk::person@ p = persons[i];
				for (int k = 0; k < ����_��; k++)
				{
					p.tekisei[k] = p.tekisei[k] + value;
				}
			}
		}

		void onNewDay()
		{
			for (int i = 0; i < �ο�����Ʈ.length; i++)
			{
				GroupInfo@ gi = �ο�����Ʈ[i];
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
						case ȿ��_���ɻ��_��:apply����(gi.membersApply, -ȿ��_���ɻ��_��_��); break;
						case ȿ��_���ɻ��_��:apply����(gi.membersApply, -ȿ��_���ɻ��_��_��); break;
						case ȿ��_���ɻ��_��:apply����(gi.membersApply, -ȿ��_���ɻ��_��_��); break;
						case ȿ��_�������_��:apply����(gi.membersApply, -ȿ��_�������_��_��); break;
						case ȿ��_�������_��:apply����(gi.membersApply, -ȿ��_�������_��_��); break;
						case ȿ��_�������_��:apply����(gi.membersApply, -ȿ��_�������_��_��); break;
						case ȿ��_���������:apply����(gi.membersApply, -1); break;

						default:
							break;
						}
					}
					string str2 = "";
					for (int j = 0; j < gi.membersApply.count; j++)
						str2 = str2 + "," + pk::format("\x1b[1x{}\x1b[0x", getName(gi.membersApply[j]));

					gi.membersApply.clear();
					string str = pk::format("\x1b[2x{}��\x1b[0x, \x1b[29x{}\x1b[0x ���{}",getNameForce(gi.force),gi.name,str2);
					pk::history_log(pk::point(), gi.force.color, pk::encode(str));
				}
				
				if ((force != null && !gi.b) || (gi.force!=null && force!=null && force.get_id() != gi.force.get_id()))
				{
					for (int k = 0; k < gi.ids.length; k++)
					{
						int id = gi.ids[k];
						switch (id)
						{
						case ȿ��_���ɻ��_��:apply����(gi.members, ȿ��_���ɻ��_��_��); break;
						case ȿ��_���ɻ��_��:apply����(gi.members, ȿ��_���ɻ��_��_��); break;
						case ȿ��_���ɻ��_��:apply����(gi.members, ȿ��_���ɻ��_��_��); break;
						case ȿ��_�������_��:apply����(gi.members, ȿ��_�������_��_��); break;
						case ȿ��_�������_��:apply����(gi.members, ȿ��_�������_��_��); break;
						case ȿ��_�������_��:apply����(gi.members, ȿ��_�������_��_��); break;
						case ȿ��_���������:apply����(gi.members, 1); break;

						default:
							break;
						}
					}
					gi.idsApply = gi.ids;
					gi.membersApply = gi.members;

					string str2 = "";
					for (int j = 0; j < gi.members.count; j++)
						str2 = str2 + "," + pk::format("\x1b[1x{}\x1b[0x", getName(gi.members[j]));

					string str = pk::format("\x1b[2x{}��\x1b[0x, \x1b[1x{}\x1b[0x ȹ��{}", getNameForce(force), gi.name,str2);
					pk::history_log(pk::point(), force.color, pk::encode(str));
				}

				@gi.force = force;
				gi.b = force != null;

			}
		}
		void onTurnStart(pk::force@ force)
		{
			array<GroupInfo@> gis = getForces(force, { ȿ��_�־�_��,ȿ��_�־�_��, ȿ��_�־�_��});
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
					if(id != ȿ��_�־�_�� && id != ȿ��_�־�_�� && id != ȿ��_�־�_��)
						continue;

					int value = id == ȿ��_�־�_�� ? ȿ��_�־�_��_�� : id == ȿ��_�־�_�� ? ȿ��_�־�_��_�� : ȿ��_�־�_��_��;
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
