/*
@������: ũ���Ƚ�
@Update: 2024.6.6���ʹ���
*/
namespace ����_HiddenAttack
{
	const int �ൿ�� = 20;
	
	const bool Ư��ǥ�� = true;

	const int ����_����_�Ǵ�_���� = 4;//�� ���ֿ����� ���� �ǴܰŸ��̴ϴ�.
	const int ����_ȥ��_����_����_���� = 2;//���ԵǴ� ������������ ȥ��/����/��°��Ұ� �߻��Ǵ� �����Դϴ�.
	const int ��°���ġ = 50;//�������� ���� ��°���ġ�Դϴ�. ȥ��/����/��°��� �� ��°��Ұ� �߻��Ҷ� ����˴ϴ�.

	const int ����_����_�Ǵ�_�δ�_�� = 2;//������ �ֺ������� ���ּ��� ���̰� 2�̻��϶� ������ �Ǵ�.
	const int ����_����_�Ǵ�_����_�� = 10000;//�������� 10000�̻��϶�

	const bool ����_���°��� = true;//���� ����� ������ ������ �����մϴ�.
	const int ����_�ּҵ����� = 700;
	const int ����_�ִ뵥���� = 1500;

	const bool ����_����_���� = true;//������ ���� �߻����� ���ϵ��� �մϴ�.
	const int ����_����_����_�� = 60;//�δ�


	const float ����Ȯ��_���º��� = 0.7; //���°� ����� 7:3��
	const int ����Ȯ��_�ִ������� = 30;//�������� 30�� �Ǹ� 50% Ȯ���� �˴ϴ�.
	const int ����Ȯ��_�ִ������ = 90;//������� 90(3���ջ�)�� �Ǹ� 50% Ȯ���� �˴ϴ�.

	const int AI_����Ȱ��_����_�ּ�ġ = 50;//60% Ȯ���� �Ǿ� AI�� ������ �����մϴ�.


	const int ����_�ϱ���_Ȯ�� = 30;//���� ����� �ϱ��� �߻�Ȯ���Դϴ�.
	const int ����_�ϱ���_������ = 10;// �÷��� ���̳ʽ� 10 ����
	const int ����_�ϱ���_ü�°��� = 15;//�����ϱ���� ü���� ��� ������.


	const int KEY = pk::hash("����");
	const int KEY_�ֱ������δ뼱�� = pk::hash("�ֱ������δ뼱��_Export");


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
		pk::person@ person����;
		pk::list<pk::person@> persons���;

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
			item.init = pk::building_menu_item_init_t(����Init);
			item.is_enabled = pk::menu_item_is_enabled_t(Is����Enabled);
			item.get_text = pk::menu_item_get_text_t(����Text);
			item.get_desc = pk::menu_item_get_desc_t(����Desc);
			item.handler = pk::menu_item_handler_t(����Handler);
			pk::add_menu_item(item);

			pk::bind(111, pk::trigger111_t(onTurnStart));

			pk::bind(102, pk::trigger102_t(Init));
			pk::bind(105, pk::trigger105_t(SaveData));


			@prev_callback_166 = cast<pk::func166_t@>(pk::get_func(166));

		}

		void Init()
		{
			_���Ӻ��������� = {};
			int count = int(pk::load(KEY, 0, 0));
			if (count > 0)
			{
				int li = 1;
				for (int i = 0; i < count; i++)
				{
					int a = int(pk::load(KEY, li++, 0));
					_���Ӻ���������.insertLast(a);
				}
			}
			else 
			{
				for (int i = 0; i < ����_��; i++)
				{
					_���Ӻ���������.insertLast(0);
				}
			}
		}

		void SaveData(int fd)
		{
			pk::store(KEY, 0, _���Ӻ���������.length);
			int si = 1;
			for (int i = 0; i < _���Ӻ���������.length; i++)
			{
				pk::store(KEY, si++, _���Ӻ���������[i]);
			}
		}

		array<int> _���Ӻ���������(����_��);

		pk::force@ _force;
		pk::building@ _building;
		pk::city@ _city;
		pk::gate@ _gate;
		pk::port@ _port;

		pk::district@ _district;
		void ����Init(pk::building@ building)
		{
			@_force = pk::get_force(building.get_force_id());
			@_building = building;
			@_city = pk::building_to_city(building);
			@_port = pk::building_to_port(building);
			@_gate = pk::building_to_gate(building);
			@_district = pk::get_district(building.get_district_id());

		}
		bool Is����Enabled()
		{
			if (_building.get_id() >= ����_��)
				return false;

			if (����_����_���� && pk::get_elapsed_days() < (_���Ӻ���������[_building.get_id()] + ����_����_����_��))
				return false;
			return _district.ap >= �ൿ��;
		}
		string ����Text()
		{
			return pk::encode("����");
		}
		string ����Desc()
		{
			if (_building.get_id() >= ����_��)
				return pk::encode("���ÿ����� �����մϴ�.");
			if (_district.ap < �ൿ��)
				return pk::encode("�ൿ���� �����մϴ�.");
			else if (����_����_���� && pk::get_elapsed_days() < (_���Ӻ���������[_building.get_id()] + ����_����_����_��))
				return pk::encode(pk::format("{}���Ŀ� ��밡���մϴ�.", _���Ӻ���������[_building.get_id()] + ����_����_����_��- pk::get_elapsed_days()));
			else
				return pk::encode(pk::format("�������忡 ������ �����մϴ�.(�ൿ��{})", �ൿ��));
		}



		bool ��������(pk::list<pk::person@> src, pk::person@ �������, FieldInfo@ fi)
		{
			int a = ����Ȯ��(src, �������, fi);
			return pk::rand_bool(a);
		}

		int ����Ȯ��(pk::list<pk::person@> src,pk::person@ �������, FieldInfo@ fi)
		{
			int max����0 = �������.stat[����ɷ�_����];
			int �����0 = 0;
			for (int i = 0; i < src.count; i++)
			{
				pk::person@ p = src[i];
				�����0 += p.stat[����ɷ�_���];
			}

			int max����1 = fi.person����.stat[����ɷ�_����];
			int �����1= 0;
			for (int i = 0; i < fi.persons���.count; i++)
			{
				pk::person@ p = src[i];
				�����1 += p.stat[����ɷ�_���];
			}



			max����0 = pk::min(max����0, 130);
			max����1 = pk::min(max����1, 130);

			�����0 = pk::min(�����0, 390);
			�����1 = pk::min(�����1, 390);

			int off���� = (max����0 - max����1);
			int off��� = (�����0 - �����1);

			if (off���� > ����Ȯ��_�ִ�������)
				off���� = ����Ȯ��_�ִ�������;
			if( off���� < -����Ȯ��_�ִ�������)
				off���� = -����Ȯ��_�ִ�������;

			if (off��� > ����Ȯ��_�ִ������)
				off��� = ����Ȯ��_�ִ������;
			if (off��� < -����Ȯ��_�ִ������)
				off��� = -����Ȯ��_�ִ������;

			

			int ����Ȯ�� = 50 + (off���� / float(����Ȯ��_�ִ�������)) * 50;
			int ���Ȯ�� = 50 + (off��� / float(����Ȯ��_�ִ������)) * 50;

			int nn = ����Ȯ�� * ����Ȯ��_���º��� + ���Ȯ�� * (1-����Ȯ��_���º���);
			//pk::printf("off����:{}, off���:{}, {}\n", off����, off���, nn);
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
				array<pk::point> arr = pk::range(u.get_pos(), 0, ����_����_�Ǵ�_����);
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
					if(u2.status != �δ����_���)
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
				//pk::printf("{},enemyCount:{},�Ʊ�:{}\n", getNameLeader(u), fi.enemies.count, ucount);
				if(fi.enemies.count - ucount >= ����_����_�Ǵ�_�δ�_�� && (troops1 - troops0) >= ����_����_�Ǵ�_����_��)
					fis.insertLast(fi);

			}

			for (int i = 0; i < fis.length; i++)
			{
				FieldInfo@ fi = fis[i];
				if (fi.persons.count > 1) 
				{
					fi.persons.sort(function(a, b) 
					{
						return a.stat[����ɷ�_����] > b.stat[����ɷ�_����];
					});
				}
				@fi.person���� = fi.persons[0];


				if (fi.persons.count > 1)
				{
					fi.persons.sort(function(a, b)
					{
						return a.stat[����ɷ�_���] > b.stat[����ɷ�_���];
					});
				}

				fi.persons��� = fi.persons;
				if (fi.persons.count > 3)
				{
					pk::list<pk::person@> nps;
					for (int i = 0; i < 3; i++)
						nps.add(fi.persons[i]);
					fi.persons��� = nps;
				}
			}
			return fis;
		}

		bool isMarch(pk::person@ p, pk::building@ b)
		{
			return p != null && !pk::is_absent(p) && !p.action_done && !pk::is_unitize(p) && p.service == b.get_id() && p.get_force_id() == b.get_force_id() &&
				p.mibun != �ź�_��� && p.mibun != �ź�_����;
		}

		string getStrWeapon(int weapon)
		{
			string str = "";
			switch (weapon)
			{
			case ����_��:str = "�˺�"; break;
			case ����_â:str = "â��"; break;
			case ����_��:str = "�غ�"; break;
			case ����_��:str = "�뺴"; break;
			case ����_����:str = "�⺴"; break;
			case ����_����:str = "����"; break;
			case ����_����:str = "����"; break;
			case ����_���:str = "���"; break;
			case ����_����:str = "����"; break;
			case ����_�ְ�:str = "�ְ�"; break;
			case ����_����:str = "����"; break;
			case ����_����:str = "����"; break;

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
			if (pk::has_skill(p, Ư��_�п�))
				str = str + (str == "" ? "�п�" : " �п�");
			if (pk::has_skill(p, Ư��_����))
				str = str + (str == "" ? "����" : " ����");
			if (pk::has_skill(p, Ư��_����))
				str = str + (str == "" ? "����" : " ����");
			if (pk::has_skill(p, Ư��_����))
				str = str + (str == "" ? "����" : " ����");
			if (pk::has_skill(p, Ư��_����))
				str = str + (str == "" ? "����" : " ����");
			if (pk::has_skill(p, Ư��_����))
				str = str + (str == "" ? "����" : " ����");
			if (pk::has_skill(p, Ư��_����))
				str = str + (str == "" ? "����" : " ����");
			if (pk::has_skill(p, Ư��_�ݰ�))
				str = str + (str == "" ? "�ݰ�" : " �ݰ�");
			if (pk::has_skill(p, Ư��_�ұ�))
				str = str + (str == "" ? "�ұ�" : " �ұ�");
			if (pk::has_skill(p, Ư��_ö��))
				str = str + (str == "" ? "ö��" : " ö��");
			if (pk::has_skill(p, Ư��_����))
				str = str + (str == "" ? "����" : " ����");
			if (pk::has_skill(p, Ư��_����))
				str = str + (str == "" ? "����" : " ����");
			if (pk::has_skill(p, Ư��_����))
				str = str + (str == "" ? "����" : " ����");
			if (pk::has_skill(p, Ư��_����))
				str = str + (str == "" ? "����" : " ����");
			if (pk::has_skill(p, Ư��_��Ÿ))
				str = str + (str == "" ? "��Ÿ" : " ��Ÿ");
			if (pk::has_skill(p, Ư��_����))
				str = str + (str == "" ? "����" : " ����");
			if (pk::has_skill(p, Ư��_�ź�))
				str = str + (str == "" ? "�ź�" : " �ź�");
			if (pk::has_skill(p, Ư��_����))
				str = str + (str == "" ? "����" : " ����");
			if (pk::has_skill(p, Ư��_����))
				str = str + (str == "" ? "����" : " ����");
			if (pk::has_skill(p, Ư��_���))
				str = str + (str == "" ? "���" : " ���");
			if (pk::has_skill(p, Ư��_�))
				str = str + (str == "" ? "�" : " �");
			if (pk::has_skill(p, Ư��_����))
				str = str + (str == "" ? "����" : " ����");
			if (pk::has_skill(p, Ư��_����))
				str = str + (str == "" ? "����" : " ����");
			if (pk::has_skill(p, Ư��_����))
				str = str + (str == "" ? "����" : " ����");
			if (pk::has_skill(p, Ư��_����))
				str = str + (str == "" ? "����" : " ����");
			if (pk::has_skill(p, Ư��_ȣ��))
				str = str + (str == "" ? "ȣ��" : " ȣ��");

			for (int i = Ư��_ȭ��; i <= Ư��_�༺; i++)
			{
				pk::skill@ s = pk::get_skill(i);
				if (pk::has_skill(p, i))
					str = str + (str == "" ? pk::decode(s.name) : (" " + pk::decode(s.name)));
			}
			if (pk::has_skill(p, Ư��_����))
				str = str + (str == "" ? "����" : " ����");
			if (pk::has_skill(p, Ư��_ģ��))
				str = str + (str == "" ? "ģ��" : " ģ��");
			if (pk::has_skill(p, Ư��_ģ��))
				str = str + (str == "" ? "ģ��" : " ģ��");
			if (pk::has_skill(p, Ư��_ģ��))
				str = str + (str == "" ? "ģ��" : " ģ��");
			if (pk::has_skill(p, Ư��_ģ��))
				str = str + (str == "" ? "ģ��" : " ģ��");

			for (int i = Ư��_��; i < 255; i++)
			{
				pk::skill@ s = pk::get_skill(i);
				if (pk::has_skill(p, i))
					str = str + (str == "" ? pk::decode(s.name) : (" " + pk::decode(s.name)));
			}



			if (weapon == ����_â || weapon == ����_�� || weapon == ����_�� || weapon == ����_����)
			{
				if (pk::has_skill(p, Ư��_��ǳ))
					str = str + (str == "" ? "��ǳ" : " ��ǳ");
				if (pk::has_skill(p, Ư��_����))
					str = str + (str == "" ? "����" : " ����");
				if (pk::has_skill(p, Ư��_�޽�))
					str = str + (str == "" ? "�޽�" : " �޽�");
				if (pk::has_skill(p, Ư��_�Ⱒ))
					str = str + (str == "" ? "�Ⱒ" : " �Ⱒ");
				if (pk::has_skill(p, Ư��_����))
					str = str + (str == "" ? "����" : " ����");
				if (pk::has_skill(p, Ư��_����))
					str = str + (str == "" ? "����" : " ����");
				if (pk::has_skill(p, Ư��_��Ż))
					str = str + (str == "" ? "��Ż" : " ��Ż");
				if (pk::has_skill(p, Ư��_����))
					str = str + (str == "" ? "����" : " ����");
			}
			if (weapon == ����_â || weapon == ����_�� || weapon == ����_����)
			{
				if (pk::has_skill(p, Ư��_�ɰ�))
					str = str + (str == "" ? "�ɰ�" : " �ɰ�");
				if (pk::has_skill(p, Ư��_����))
					str = str + (str == "" ? "����" : " ����");
			}

			if (weapon == ����_â)
			{
				if (pk::has_skill(p, Ư��_����))
					str = str + (str == "" ? "����" : " ����");
				if (pk::has_skill(p, Ư��_â��))
					str = str + (str == "" ? "â��" : " â��");
				if (pk::has_skill(p, Ư��_â��))
					str = str + (str == "" ? "â��" : " â��");
			}
			if (weapon == ����_��)
			{
				if (pk::has_skill(p, Ư��_����))
					str = str + (str == "" ? "����" : " ����");
				if (pk::has_skill(p, Ư��_�ؽ�))
					str = str + (str == "" ? "�ؽ�" : " �ؽ�");
				if (pk::has_skill(p, Ư��_����))
					str = str + (str == "" ? "����" : " ����");
			}
			if (weapon == ����_��)
			{
				if (pk::has_skill(p, Ư��_�ý�))
					str = str + (str == "" ? "�ý�" : " �ý�");
				if (pk::has_skill(p, Ư��_����))
					str = str + (str == "" ? "����" : " ����");
				if (pk::has_skill(p, Ư��_���))
					str = str + (str == "" ? "���" : " ���");
			}
			if (weapon == ����_����)
			{
				if (pk::has_skill(p, Ư��_���))
					str = str + (str == "" ? "���" : " ���");
				if (pk::has_skill(p, Ư��_����))
					str = str + (str == "" ? "����" : " ����");
				if (pk::has_skill(p, Ư��_�鸶))
					str = str + (str == "" ? "�鸶" : " �鸶");
				if (pk::has_skill(p, Ư��_����))
					str = str + (str == "" ? "����" : " ����");
				if (pk::has_skill(p, Ư��_���))
					str = str + (str == "" ? "���" : " ���");
			}

			if (weapon == ����_���� || weapon == ����_����)
			{
				if (pk::has_skill(p, Ư��_����))
					str = str + (str == "" ? "����" : " ����");
			}

			return str;
		}



		UnitInfo@ getUnitInfo�ֱ������δ뼱��()
		{
			int count = int(pk::load(KEY_�ֱ������δ뼱��, 0, 0));
			if (count == 0)
				return null;

			int li = 1;

			array<UnitInfo@> uis;
			for (int i = 0; i < count; i++)
			{
				UnitInfo ui;
				int m0 = int(pk::load(KEY_�ֱ������δ뼱��, li++, -1));
				int m1 = int(pk::load(KEY_�ֱ������δ뼱��, li++, -1));
				int m2 = int(pk::load(KEY_�ֱ������δ뼱��, li++, -1));
				pk::person@ p0 = m0 != -1 ? pk::get_person(m0) : null;
				pk::person@ p1 = m1 != -1 ? pk::get_person(m1) : null;
				pk::person@ p2 = m2 != -1 ? pk::get_person(m2) : null;
				if (p0 != null)
					ui.members.add(p0);
				if (p1 != null)
					ui.members.add(p1);
				if (p2 != null)
					ui.members.add(p2);
				ui.weapon = int(pk::load(KEY_�ֱ������δ뼱��, li++, -1));
				ui.weaponWater = int(pk::load(KEY_�ֱ������δ뼱��, li++, -1));
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
					itemArr.insertLast(pk::encode("����"));
				else
					itemArr.insertLast(pk::encode("�ڷ�"));

				for (int i = si; i < count; i++)
				{
					UnitInfo@ ui = uis[i];
					string strWeapon = getStrWeapon(ui.weapon);
					string strWeaponWater = getStrWeapon(ui.weaponWater);

					string str0 = Ư��ǥ�� && ui.members.count > 0 ? getStrSkill(ui.weapon, ui.members[0]) : "";
					string str1 = Ư��ǥ�� && ui.members.count > 1 ? getStrSkill(ui.weapon, ui.members[1]) : "";
					string str2 = Ư��ǥ�� && ui.members.count > 2 ? getStrSkill(ui.weapon, ui.members[2]) : "";
					string str0Weapon = ui.members.count > 0 ? getStrWeapon(ui.weapon, ui.members[0]) : "";
					string str1Weapon = ui.members.count > 1 ? getStrWeapon(ui.weapon, ui.members[1]) : "";
					string str2Weapon = ui.members.count > 2 ? getStrWeapon(ui.weapon, ui.members[2]) : "";

					bool bMarch0 = ui.members.count > 0 ? isMarch(ui.members[0], _building) : false;
					bool bMarch1 = ui.members.count > 1 ? isMarch(ui.members[1], _building) : false;
					bool bMarch2 = ui.members.count > 2 ? isMarch(ui.members[2], _building) : false;

					string str;
					str = pk::format("{},{},{}", strWeapon, (strWeaponWater != "" && strWeaponWater != "�˺�") ? strWeaponWater : "�ְ�", pk::get_command(ui.members[0]));
					if (Ư��ǥ��)
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
						itemArr.insertLast(pk::encode("����"));
					else
						itemArr.insertLast(pk::encode("����"));
				}

				int choose2 = pk::choose(pk::encode("�δ븦 �������ֽʽÿ�"), itemArr);
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
				pk::message_box(pk::encode(pk::format("{} �����Ұ�", getName(selectedItem.members[0]))));
				return null;
			}
			if (selectedItem.members.count > 1 && selectedItem.members[1] != null && !isMarch(selectedItem.members[1], _building))
			{
				pk::message_box(pk::encode(pk::format("{} �����Ұ�", getName(selectedItem.members[1]))));
				return null;
			}
			if (selectedItem.members.count > 2 && selectedItem.members[2] != null && !isMarch(selectedItem.members[2], _building))
			{
				pk::message_box(pk::encode(pk::format("{} �����Ұ�", getName(selectedItem.members[2]))));
				return null;
			}

			return selectedItem;
		}

		UnitInfo@ getUnitInfo()
		{
			UnitInfo@ ui = getUnitInfo�ֱ������δ뼱��();
			if (ui != null)
				return ui;

			pk::list<pk::person@> ps0 = pk::get_idle_person_list(_building);
			if (ps0.count == 0)
			{
				pk::message_box(pk::encode("���������� ������ �����ϴ�."));
				return null;
			}

			pk::list<pk::person@> ps = pk::person_selector(pk::encode("���弱��"), pk::encode("������ ������ �����Ͻʽÿ�"), ps0, 1, 3);
			if (ps.count == 0)
				return null;

			UnitInfo ui2;
			if (ps.count > 1)
			{
				ps.sort(function(a, b)
				{
					if ((a.mibun == �ź�_���� and b.mibun != �ź�_����) or (a.mibun != �ź�_���� and b.mibun == �ź�_����))
						return a.mibun == �ź�_����;


					if (a.rank == b.rank)
					{
						for (int i = 0; i < ����ɷ�_��; i++)
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
			return pk::encode("���� �ϼ� �Է�");
		}


		pk::unit@ ����(UnitInfo@ ui,bool b����,pk::point targetPos)
		{
			pk::city@ city = pk::building_to_city(_building);

			int maxCommnd = pk::get_command(ui.members[0]);
			if (maxCommnd > GetCityTroops())
			{
				pk::message_box(pk::encode("���ÿ� ������ �����մϴ�"));
				return null;
			}

			int weaponType = ui.weapon;
			int mount = 0;
			switch (ui.weapon)
			{
			case ����_â:
			case ����_��:
			case ����_��:
			case ����_����:
				mount = maxCommnd; break;
			case ����_����:
			case ����_����:
			case ����_����:
			case ����_���:
				mount = 1;
			}
			if (mount > 0 && GetCityWeaponAmount(ui.weapon) < mount)
			{
				string str = "����";
				switch (ui.weapon)
				{
				case ����_â: str = "â"; break;
				case ����_��: str = "��"; break;
				case ����_��: str = "��"; break;
				case ����_����: str = "����"; break;
				case ����_����: str = "����"; break;
				case ����_����: str = "����"; break;
				case ����_����: str = "����"; break;
				case ����_���: str = "���"; break;
				}
				pk::message_box(pk::encode(pk::format("{}�� �����մϴ�", str)));
				return null;
			}
			if (mount == 0)
			{
				weaponType = ����_��;
				mount = maxCommnd;
			}

			auto result = pk::numberpad(pk::encode("���� �ϼ� �Է�"), 10, 500, 100, pk::numberpad_t(pad_callback));
			if (!result.second)
				return null;


			int foodA = prev_callback_166(10000, 10000);
			int food = maxCommnd * (float(result.first) / foodA);

			if (food > GetCityFood())
			{
				pk::message_box(pk::encode("���ÿ� ������ �����մϴ�"));
				return null;
			}
			int ����Ÿ�� = ����_�ְ�;
			if (ui.weapon == ����_���� || ui.weapon == ����_����)
				����Ÿ�� = ui.weapon;
			if (ui.weaponWater == ����_���� || ui.weaponWater == ����_����)
				����Ÿ�� = ui.weaponWater;

			if (����Ÿ�� == ����_���� || ����Ÿ�� == ����_����)
			{
				if (GetCityWeaponAmount(����Ÿ��) == 0)
				{
					pk::message_box(pk::encode(pk::format("���ÿ� {}�� �����մϴ�.", ����Ÿ�� == ����_���� ? "����" : "����")));
					return null;
				}
			}

			int gold = 0;
			pk::march_cmd_info mi;
			@mi.base = _building;
			mi.type = �δ�����_����;
			mi.gold = gold;
			mi.food = food;
			mi.troops = maxCommnd;

			for (int i = 0; i < 12; i++)
			{
				mi.weapon_amount[i] = 0;
			}
			mi.weapon_id[0] = weaponType;
			mi.weapon_amount[0] = mount;
			mi.weapon_id[1] = ����Ÿ��;
			mi.weapon_amount[1] = 1;

			if (ui.members.count > 1)
			{
				ui.members.sort(function(a, b)
				{
					if ((a.mibun == �ź�_���� and b.mibun != �ź�_����) or (a.mibun != �ź�_���� and b.mibun == �ź�_����))
						return a.mibun == �ź�_����;


					if (a.rank == b.rank)
					{
						for (int i = 0; i < ����ɷ�_��; i++)
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
				string str = get����String(b����);
				if (!b����)
				{
					pk::set_status(unit,null, �δ����_ȥ��, pk::rand(2) + 1);
					unit.action_done = true;
				}
				pk::message_box(pk::encode(str), pk::get_person(unit.leader));
				if (b����)
				{
					_���Ӻ���������[_building.get_id()] = pk::get_elapsed_days();
				}
				return unit;
			}
			return null;
		}

		string get����String(bool b����)
		{
			if (b����)
			{
				switch (pk::rand(5))
				{
				case 0: return "������ ��ٸ��� �־���";
				case 1: return "�̰���~";
				case 2: return "��� �� �����ְڴ�";
				case 3: return "�����̴�~";
				case 4: return "�ź��̴�~";
				default:
					break;
				}
			}
			else 
			{
				switch (pk::rand(5))
				{
				case 0: return "������ �ʴ°�";
				case 1: return "��¼�� ���̳�";
				case 2: return "�����ڰ� �ִ°�";
				case 3: return "�ƻԻ�";
				case 4: return "ħ���϶�~";
				default:
					break;
				}
			}
			return "";
		}

		pk::unit@ ����AI(UnitInfo@ ui, bool b����, pk::point targetPos,pk::building@ building,bool bPlayerWidth)
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
			case ����_â:
			case ����_��:
			case ����_��:
			case ����_����:
				mount = maxCommnd; break;
			case ����_����:
			case ����_����:
			case ����_����:
			case ����_���:
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
			int ����Ÿ�� = ����_�ְ�;
			int gold = 0;

			pk::march_cmd_info mi;
			@mi.base = building;
			mi.type = �δ�����_����;
			mi.gold = gold;
			mi.food = food;
			mi.troops = maxCommnd;

			for (int i = 0; i < 12; i++)
			{
				mi.weapon_amount[i] = 0;
			}
			mi.weapon_id[0] = weaponType;
			mi.weapon_amount[0] = mount;
			mi.weapon_id[1] = ����Ÿ��;
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
				string str = get����String(b����);
				if (!b����)
				{
					pk::set_status(unit,null, �δ����_ȥ��, pk::rand(2) + 1);
				}
				
				if(bPlayerWidth)
					pk::message_box(pk::encode(str), pk::get_person(unit.leader));
				else
					pk::say(pk::encode(str), pk::get_person(unit.leader), unit);

				pk::printf("AI����:{}\n", getNameLeader(unit));
				if (b����)
				{
					_���Ӻ���������[building.get_id()] = pk::get_elapsed_days();
				}

				return unit;
			}
			return null;


		}

		pk::point get����������ġ(pk::unit@ u)
		{
			array<pk::point> arr = pk::range(u.get_pos(), 0, ����_����_�Ǵ�_����);
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
		pk::point get����������ġ(pk::unit@ u)
		{
			array<pk::point> arr = pk::range(u.get_pos(), 0, ����_����_�Ǵ�_����);
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

		void update����(pk::unit@ u, pk::point pt)
		{
			array<pk::point> arr = pk::range(pt, 0, ����_ȥ��_����_����_����);

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
				case 0: str = "�̺δ�� ��� ��Ÿ�� ���̳�"; break;
				case 1: str = "�����̴�~"; break;
				case 2: str = "�ʹ� ��� ��� �Դ���"; break;
				default:
					break;
				}

				switch (pk::rand(3))
				{
				case 0: pk::set_status(u2, null, �δ����_ȥ��, pk::rand(3) + 1, true); break;
				case 1: pk::set_status(u2, null, �δ����_����, pk::rand(3) + 1, true); break;
				case 2: pk::add_energy(u2, -��°���ġ, true); break;
				default:
					break;
				}

				
				int ��� = pk::get_best_member_stat(u2, ����ɷ�_���);
				if (��� > 100)
					��� = 100;
				
				int dam = ����_�ּҵ����� + (����_�ִ뵥���� - ����_�ּҵ�����) * (1 - ��� / float(100.0));
				if (dam > u2.troops - 3)
					dam = u2.troops - 3;

				if(����_���°��� &&  dam>0)
					pk::add_troops(u2, -dam, true);

				updateAfter(u, u2);


				@u2 = pk::get_unit(u2.get_pos());
				if(u2==null)
					continue;

				pk::say(pk::encode(str), pk::get_person(u2.leader), u2);
				if (u2.troops == 3)
				{
					str = "������� �� ���������";
					pk::say(pk::encode(str), pk::get_person(u2.leader), u2);
				}

				units.add(u2);

			}

			if (pk::rand_bool(����_�ϱ���_Ȯ��))
			{
				pk::person@ maxP = null;
				int max = -1;
				for (int i = 0; i < 3; i++)
				{
					pk::person@ p = pk::get_person(u.member[i]);
					if(p==null)
						continue;

					if (p.stat[����ɷ�_����] > max)
					{
						max = p.stat[����ɷ�_����];
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

							if (p2.stat[����ɷ�_����] < max+����_�ϱ���_������ && p2.stat[����ɷ�_����] > max-����_�ϱ���_������)
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
						maxP2.hp = pk::max(maxP2.hp - ����_�ϱ���_ü�°���, 1);
						if (u.is_player() || maxP2.is_player())
						{
							string str0;
							switch (pk::rand(3))
							{
							case 0: str0 = "������ ������ ã�Ҵ�~";	break;
							case 1: str0 = "�̶���!!!";	break;
							case 2: str0 = "��ٸ��� �־���~";	break;
							default:
								break;
							}
							pk::message_box(pk::encode(str0), maxP);

							string str1;
							switch (pk::rand(3))
							{
							case 0: str1 = "���� �̶�...";	break;
							case 1: str1 = "���~";	break;
							case 2: str1 = "���Ҽ� ����..";	break;
							default:
								break;
							}
							pk::message_box(pk::encode(str1), maxP2);
						}

						@_scene_attackerUnit = u;
						@_scene_targetUnit = maxU;
						@_scene_attacker = maxP;
						@_scene_target = maxP2;
						
						pk::scene(pk::scene_t(scene_�ϱ���));

						@_scene_attackerUnit = null;
						@_scene_targetUnit = null;
						@_scene_attacker = null;
						@_scene_target = null;
					}
				}

			}
		}

		void scene_�ϱ���()
		{
			//pk::printf("tatical 1:1 {},{}------------------\n",getName(_scene_attacker), getName(_scene_target));
			bool b0 = pk::is_player_controlled(_scene_attackerUnit);
			bool b1 = pk::is_player_controlled(_scene_targetUnit);

			pk::duel(_scene_attackerUnit, _scene_targetUnit, _scene_attacker, null, null, _scene_target, null, null, b0, b1, 0, b0 || b1);
		}


		pk::person@ getMax����(pk::list<pk::unit@> units)
		{
			int max = -1;
			pk::person@ max���� = null;
			for (int i = 0; i < units.count; i++)
			{
				pk::unit@ u = units[i];
				pk::person@ p0 = pk::is_valid_person_id(u.member[0]) ? pk::get_person(u.member[0]) : null;
				pk::person@ p1 = pk::is_valid_person_id(u.member[1]) ? pk::get_person(u.member[1]) : null;
				pk::person@ p2 = pk::is_valid_person_id(u.member[2]) ? pk::get_person(u.member[2]) : null;

				if (p0 != null && p0.stat[����ɷ�_����] > max)
				{
					max = p0.stat[����ɷ�_����];
					@max���� = p0;
				}
				if (p1 != null && p1.stat[����ɷ�_����] > max)
				{
					max = p1.stat[����ɷ�_����];
					@max���� = p1;
				}
				if (p2 != null && p2.stat[����ɷ�_����] > max)
				{
					max = p2.stat[����ɷ�_����];
					@max���� = p2;
				}
			}

			return max����;
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
				pk::kill(targetU, attacker, dist == 1, attacker.weapon == ����_��);

				//if (dist == 1)
				//{
				//	if(gold * 0.5 >0)
				//		pk::add_gold(attacker, gold * 0.5, true);
				//	if(food * 0.5 >0)
				//		pk::add_food(attacker, food * 0.25, true);
				//}

				//pk::printf("kill end\n");
				if (attacker.has_skill(Ư��_�Ӿ�))
					pk::add_energy(attacker, int(pk::core::skill_constant(attacker, Ư��_�Ӿ�)), true);

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
							if (b.facility == �ü�_���г� || b.facility == �ü�_���� || b.facility == �ü�_����2�� || b.facility == �ü�_����2��)
							{
								if (b2 != null)
								{
									int a = pk::get_food(b2) * 0.025;
									pk::add_food(attacker, a, true);

									int a2 = pk::get_food(b2) * 0.125;
									pk::add_food(b2, -a2, true);
								}
							}
							if (b.facility == �ü�_���� || b.facility == �ü�_����2�� || b.facility == �ü�_����3�� || b.facility == �ü�_����� || b.facility == �ü�_����� ||
								b.facility == �ü�_������ || b.facility == �ü�_����� || b.facility == �ü�_�ܱ��� || b.facility == �ü�_�跫�� || b.facility == �ü�_�Ͻ���)
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

		bool ����Handler()
		{
			array<FieldInfo@> fis = makeField(_force, _building);
			if (fis.length == 0)
			{
				pk::message_box(pk::encode("������ �Ҹ��Ѱ��� �����ϴ�."));
				return true;
			}

			UnitInfo@ ui = getUnitInfo();
			if (ui == null)
				return  true;



			pk::list<pk::person@> ps0 = pk::get_idle_person_list(_building);
			if(ps0.count>1)
				ps0.sort(function(a, b) 
				{
					return a.stat[����ɷ�_����] > b.stat[����ɷ�_����];
				});

			pk::list<pk::person@> ps;
			for (int i = 0; i < ui.members.count; i++)
			{
				ps.add(ui.members[i]);
			}

			pk::person@ ������� = null;
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
					@������� = p;
					break;
				}
			}
			if (bFound0)
			{
				pk::message_box(pk::encode("���¹����� �����ϴ�."));
				return true;
			}

			for (int i = 0; i < fis.length; i++)
			{
				FieldInfo@ fi = fis[i];
				fi.percent = ����Ȯ��(ps, �������, fi);
			}

			if (fis.length > 1)
			{
				fis.sort(function(a, b) 
				{
					return a.percent >= b.percent;
				});
			}

			string str = pk::format("����:\x1b[2x{}\x1b[0x,����:\x1b[2x{}\x1b[0x\nȮ��:\x1b[2x{}\x1b[0x,�������:\x1b[2x{}({})\x1b[0x VS \x1b[2x{}({})\x1b[0x",
				getNameLeader(fis[0].u), getName(ui.members[0]), fis[0].percent, getName(�������), �������.stat[����ɷ�_����], getName(fis[0].person����), fis[0].person����.stat[����ɷ�_����]);
			if (!pk::yes_no(pk::encode(str)))
				return true;


			if (ui.weapon == -1)
			{
				array<string> sarr = { pk::encode("â��"),pk::encode("�غ�"),pk::encode("�뺴"),pk::encode("�⺴"),pk::encode("����/���"),pk::encode("����/����") };
				int choose = pk::choose(sarr);
				switch (choose)
				{
				case 0: ui.weapon = ����_â; break;
				case 1: ui.weapon = ����_��; break;
				case 2: ui.weapon = ����_��; break;
				case 3: ui.weapon = ����_����; break;
				case 4:
					if (pk::has_tech(fis[0].u, �ⱳ_�������))
						ui.weapon = ����_���;
					else
						ui.weapon = ����_����;
					break;
				case 5:
					if (pk::has_tech(fis[0].u, �ⱳ_��������))
						ui.weapon = ����_����;
					else
						ui.weapon = ����_����;
					break;

				default:
					break;
				}
			}

			
			bool b���� = ��������(ps, �������,fis[0]);
			if (!b����)
			{
				pk::point pt = get����������ġ(fis[0].u);
				if (pt.x == -1)
				{
					pk::message_box(pk::encode("������ ������ ��ġ�� �����ϴ�."));
					return true;
				}
				
				pk::unit@ u = ����(ui, b����, pt);
				if (u!=null)
				{
					pk::play_se(13);
					_district.ap = _district.ap - �ൿ��;
					ps[ps.count - 1].action_done = true;

					string str = "";
					switch (pk::rand(3))
					{
					case 0: str = "������ �������� ����ϰ� �ִ�"; break;
					case 1: str = "�׷��� �˾Ҵ� ������"; break;
					case 2: str = "�� �չٴ� ���̴� ����"; break;
					default:
						break;
					}
					pk::message_box(pk::encode(str), getMax����(fis[0].enemies));
				}
			}
			else 
			{
				pk::point maxPT = get����������ġ(fis[0].u);
				if (maxPT.x == -1)
				{
					pk::message_box(pk::encode("������ ������ ��ġ�� �����ϴ�."));
					return true;
				}
				pk::unit@ u = ����(ui, b����, maxPT);
				if (u!=null)
				{
					string str = "";
					switch (pk::rand(3))
					{
					case 0: str = "���ߴ�.."; break;
					case 1: str = "���⼭ ������.."; break;
					case 2: str = "�̷����� ���µ�.."; break;
					default:
						break;
					}
					pk::message_box(pk::encode(str), getMax����(fis[0].enemies));

					
					pk::play_se(10);
					_district.ap = _district.ap - �ൿ��;
					update����(u,maxPT);
					ps[ps.count - 1].action_done = true;
				}
			}
			
			
			return true;
		}

		//AI ����////////////////////////////////////////////////////////////////////////////////////


		int getWeapon(pk::list<pk::person@> ps)
		{
			int max = -1;
			int max���� = -1;

			for (int i = 0; i < ps.count; i++)
			{
				pk::person@ p0 = ps[i];
				if(p0 == null)
					continue;

				for (int j = 0;  j < 6;  j++)
				{
					if(j == ����_���� || j == ����_����)
						continue;

					if (p0.tekisei[j] > max)
					{
						max = p0.tekisei[j];
						max���� = j;
					}
				}
			}
			return max����;
		}

		void onTurnStart����(array<FieldInfo@> fis, pk::list<pk::person@> ps0,pk::building@ building)
		{
			if (ps0.count > 1)
			{
				ps0.sort(function(a, b)
				{
					return a.stat[����ɷ�_���] > b.stat[����ɷ�_���];
				});
			}

			pk::list<pk::person@> ps���;
			pk::list<pk::person@> ps;

			int count = pk::min(ps0.count, 3);
			for (int i = 0; i < count; i++)
			{
				ps���.add(ps0[i]);
			}

			bool b�������� = true;
			pk::person@ ������� = ps0[0];
			if (ps0.count > 1)
			{
				ps0.sort(function(a, b)
				{
					return a.stat[����ɷ�_����] > b.stat[����ɷ�_����];
				});

				@������� = ps0[0];

				for (int i = 0; i < ps0.count; i++)
				{
					pk::person@ p = ps0[i];
					bool bFound = false;
				
					for (int j = 0; j < ps���.count; j++)
					{
						pk::person@ p2 = ps���[j];
						if (p.get_id() == p2.get_id())
						{
							bFound = true;
							break;
						}
					}
					b��������=bFound = true;
				}
			}
			if (������� == null)
			{
				return;
			}
				

			for (int i = 0; i < ps���.count; i++)
			{
				ps.add(ps���[i]);
			}
			

			for (int i = 0; i < fis.length; i++)
			{
				FieldInfo@ fi = fis[i];
				fi.percent = ����Ȯ��(ps,�������, fi);
			}

			if (fis.length > 1)
			{
				fis.sort(function(a, b)
				{
					return a.percent >= b.percent;
				});
			}

			pk::printf("AI����Ȯ��:{},{},�������:{}({}),�������:{}({})\n", getNameLeader(fis[0].u), fis[0].percent, getName(�������), �������.stat[����ɷ�_����], getName(fis[0].person����), fis[0].person����.stat[����ɷ�_����]);
			if (fis[0].percent < AI_����Ȱ��_����_�ּ�ġ)
				return;


			UnitInfo ui;
			if (ps���.count > 1)
			{
				ps���.sort(function(a, b)
				{
					if ((a.mibun == �ź�_���� and b.mibun != �ź�_����) or (a.mibun != �ź�_���� and b.mibun == �ź�_����))
						return a.mibun == �ź�_����;


					if (a.rank == b.rank)
					{
						for (int i = 0; i < ����ɷ�_��; i++)
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

			ui.members = ps���;
			ui.weapon = getWeapon(ps���);
			if (ui.weapon == -1)
				return;
			bool b���� = ��������(ps,�������,fis[0]);
			pk::point pt;
			if (b����)
				pt = get����������ġ(fis[0].u);
			else
				pt = get����������ġ(fis[0].u);
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

			pk::unit@ u = ����AI(ui, b����, pt, building, bPlayerWith);

			if (u!=null)
			{
				if (bPlayerWith)
				{
					if (b����)
					{
						string str = "";
						switch (pk::rand(5))
						{
						case 0: str = "���ߴ�.."; break;
						case 1: str = "���⼭ ������.."; break;
						case 2: str = "�̷����� ���µ�.."; break;
						case 3: str = "�ʹ� ��� ���Ա���.."; break;
						case 4: str = "�̷��� �������� ����.."; break;
						default:
							break;
						}
						pk::message_box(pk::encode(str), getMax����(fis[0].enemies));
					}
					else 
					{
						string str = "";
						switch (pk::rand(4))
						{
						case 0: str = "������ �������� ����ϰ� �ִ�"; break;
						case 1: str = "�׷��� �˾Ҵ� ������"; break;
						case 2: str = "�� �չٴ� ���̴� ����"; break;
						case 3: str = "������ ��������~"; break;
						default:
							break;
						}
						pk::message_box(pk::encode(str), getMax����(fis[0].enemies));
					}
				}
				if (b����)
					update����(u, pt);

				if(!b��������)
					�������.action_done = true;
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

				if(����_����_���� && pk::get_elapsed_days() < _���Ӻ���������[b.get_id()]+ ����_����_����_��)
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
					

				onTurnStart����(fis, ps,b);
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

