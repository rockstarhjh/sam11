
namespace ��Ư�⿪��_�δ뷣��ȿ��
{
	const int ��Ư�⿪��_Ȯ�� = 5;
	const float ��Ư�⿪��_���ݷ�_���� = 2.0;

	const int �ൿ�Ϸ�_ȸ��_Ȯ�� = 3;
	const int ����_ȿ�� = 3;
	const int ����_ȿ�� = 3;
	const int ����_ȿ�� = 3;
	const int ���ȸ��_Ȯ�� = 3;
	const int ���ȸ��_�� = 50;


	class Main
	{
		
		Main()
		{
			pk::bind(174, pk::trigger174_t(�δ��ൿ�Ϸ�));
			
			@prev_callback_209 = cast<pk::func209_t@>(pk::get_func(209));
			pk::reset_func(209);
			pk::set_func(209, pk::func209_t(callback));                // 202 ���� ���� Ȯ��
		}
		
		pk::func209_t@ prev_callback_209;

		void callback(pk::damage_info& info, pk::unit@ attacker, int tactics_id, const pk::point& in target_pos, int type, int critical, bool ambush)
		{
			prev_callback_209(info, attacker, tactics_id, target_pos, type, critical, ambush);
			if (!pk::rand_bool(��Ư�⿪��_Ȯ��))
				return;
			
			pk::person@ u0 = pk::get_person(attacker.member[0]);
			pk::person@ u1 = pk::get_person(attacker.member[1]);
			pk::person@ u2 = pk::get_person(attacker.member[2]);
			if (u0.skill < 0 and (u1==null || u1.skill<0) and (u2 == null || u2.skill < 0))
			//if (true)
			{
				info.troops_damage *= ��Ư�⿪��_���ݷ�_����;
				string str;
				int r = pk::rand(3);
				if (r == 0) 
				{
					str = pk::encode("�ٽô� ��Ư�⸦ ������������!!");
				}
				else if (r == 1)
				{
					str = pk::encode("Ư�Ⱑ ���°��� �������̴�!!");
				}
				else 
				{
					str = pk::encode("��Ư�⵵ Ư���ΰ��� �𸣴°�??");
				}
			
				pk::say(str, u0, attacker);
			}
		}

		pk::unit@ getUnit(pk::point pos)
		{
			return pk::is_valid_pos(pos) ? pk::get_unit(pos) : null;
		}

		void �ൿȸ��(pk::unit@ unit)
		{
			if (pk::rand_bool(�ൿ�Ϸ�_ȸ��_Ȯ��))
			{
				if (unit.leader < 0 || unit.leader >= ����_��)
					return;
				unit.action_done = false;
				pk::say(pk::encode("�ѹ���~"), pk::get_person(unit.leader), unit);
			}
		}
		void ���ȸ��(pk::unit@ unit)
		{
			if (pk::rand_bool(���ȸ��_Ȯ��))
			{
				if (unit.leader < 0 || unit.leader >= ����_��)
					return;
				pk::add_energy(unit, ���ȸ��_��, true);
				pk::say(pk::encode("�� ���ڱ� ���̳���."), pk::get_person(unit.leader), unit);
			}
		}
		void ����ȿ��(pk::unit@ unit)
		{
			if (pk::rand_bool(����_ȿ��))
			{
				pk::list<pk::unit@> units;
				for (int i = 0; i < ����_��; i++)
				{
					pk::point pt = pk::get_neighbor_pos(unit.get_pos(), i, 1);
					pk::unit@ u = getUnit(pt);
					if (u == null || !pk::is_enemy(unit, u))
						continue;

					units.add(u);
				}
				if (units.count > 0)
				{
					units.shuffle();
					pk::set_status(units[0],unit, �δ����_ȥ��, pk::rand(2) + 1);
					pk::say(pk::encode("???"), pk::get_person(unit.leader), unit);
					pk::say(pk::encode("???"), pk::get_person(units[0].leader), units[0]);
				}
			}
		}
		void ����ȿ��(pk::unit@ unit)
		{
			if (pk::rand_bool(����_ȿ��))
			{
				pk::list<pk::unit@> units;
				for (int i = 0; i < ����_��; i++)
				{
					pk::point pt = pk::get_neighbor_pos(unit.get_pos(), i, 1);
					pk::unit@ u = getUnit(pt);
					if (u == null || !pk::is_enemy(unit, u))
						continue;

					units.add(u);
				}
				if (units.count > 0)
				{
					units.shuffle();
					pk::set_status(units[0],unit, �δ����_����, pk::rand(2) + 1);
					pk::say(pk::encode("???"), pk::get_person(unit.leader), unit);
					pk::say(pk::encode("???"), pk::get_person(units[0].leader), units[0]);
				}
			}
		}
		void ����ȿ��(pk::unit@ unit)
		{
			if (pk::rand_bool(����_ȿ��))
			{
				pk::list<pk::unit@> units;
				for (int i = 0; i < ����_��; i++)
				{
					pk::point pt = pk::get_neighbor_pos(unit.get_pos(), i, 1);
					pk::unit@ u = getUnit(pt);
					if (u == null || !pk::is_enemy(unit, u))
						continue;

					pk::unit@ u0 = null;
					pk::unit@ u1 = null;
					switch (i)
					{
					case ����_��:
						@u0 = getUnit(pk::get_neighbor_pos(unit.get_pos(), ����_�ϵ�, 1));
						@u1 = getUnit(pk::get_neighbor_pos(unit.get_pos(), ����_�ϼ�, 1));
						break;
					case ����_�ϵ�:
						@u0 = getUnit(pk::get_neighbor_pos(unit.get_pos(), ����_��, 1));
						@u1 = getUnit(pk::get_neighbor_pos(unit.get_pos(), ����_����, 1));
						break;
					case ����_����:
						@u0 = getUnit(pk::get_neighbor_pos(unit.get_pos(), ����_�ϵ�, 1));
						@u1 = getUnit(pk::get_neighbor_pos(unit.get_pos(), ����_��, 1));
						break;
					case ����_��:
						@u0 = getUnit(pk::get_neighbor_pos(unit.get_pos(), ����_����, 1));
						@u1 = getUnit(pk::get_neighbor_pos(unit.get_pos(), ����_����, 1));
						break;
					case ����_����:
						@u0 = getUnit(pk::get_neighbor_pos(unit.get_pos(), ����_�ϼ�, 1));
						@u1 = getUnit(pk::get_neighbor_pos(unit.get_pos(), ����_��, 1));
						break;
					case ����_�ϼ�:
						@u0 = getUnit(pk::get_neighbor_pos(unit.get_pos(), ����_��, 1));
						@u1 = getUnit(pk::get_neighbor_pos(unit.get_pos(), ����_����, 1));
						break;
					default:
						break;
					}
					if (u0 != null)
					{
						pk::attack(u, u0);
						pk::say(pk::encode("�׸� ���� ���̴�"), pk::get_person(u.leader), u);
						pk::say(pk::encode("���Ƽ�?"), pk::get_person(u0.leader), u0);
						break;
					}
					else if (u1 != null)
					{
						pk::attack(u, u1);
						pk::say(pk::encode("�׸� ���� ���̴�"), pk::get_person(u.leader), u);
						pk::say(pk::encode("���Ƽ�?"), pk::get_person(u1.leader), u1);
						break;
					}
				}
			}
		}

		void �δ��ൿ�Ϸ�(pk::unit@ unit)
		{
			switch (pk::rand(5))
			{
			case 0: �ൿȸ��(unit); break;
			case 1: ���ȸ��(unit); break;
			case 2: ����ȿ��(unit); break;
			case 3: ����ȿ��(unit); break;
			case 4: ����ȿ��(unit); break;
			default:
				break;
			}
		}

	}
	Main main;
}
