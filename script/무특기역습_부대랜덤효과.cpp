
namespace 무특기역습_부대랜덤효과
{
	const int 무특기역습_확률 = 5;
	const float 무특기역습_공격력_비율 = 2.0;

	const int 행동완료_회복_확률 = 3;
	const int 교란_효과 = 3;
	const int 위보_효과 = 3;
	const int 동토_효과 = 3;
	const int 기력회복_확률 = 3;
	const int 기력회복_양 = 50;


	class Main
	{
		
		Main()
		{
			pk::bind(174, pk::trigger174_t(부대행동완료));
			
			@prev_callback_209 = cast<pk::func209_t@>(pk::get_func(209));
			pk::reset_func(209);
			pk::set_func(209, pk::func209_t(callback));                // 202 전법 성공 확률
		}
		
		pk::func209_t@ prev_callback_209;

		void callback(pk::damage_info& info, pk::unit@ attacker, int tactics_id, const pk::point& in target_pos, int type, int critical, bool ambush)
		{
			prev_callback_209(info, attacker, tactics_id, target_pos, type, critical, ambush);
			if (!pk::rand_bool(무특기역습_확률))
				return;
			
			pk::person@ u0 = pk::get_person(attacker.member[0]);
			pk::person@ u1 = pk::get_person(attacker.member[1]);
			pk::person@ u2 = pk::get_person(attacker.member[2]);
			if (u0.skill < 0 and (u1==null || u1.skill<0) and (u2 == null || u2.skill < 0))
			//if (true)
			{
				info.troops_damage *= 무특기역습_공격력_비율;
				string str;
				int r = pk::rand(3);
				if (r == 0) 
				{
					str = pk::encode("다시는 무특기를 무시하지마라!!");
				}
				else if (r == 1)
				{
					str = pk::encode("특기가 없는것이 나을것이다!!");
				}
				else 
				{
					str = pk::encode("무특기도 특기인것을 모르는가??");
				}
			
				pk::say(str, u0, attacker);
			}
		}

		pk::unit@ getUnit(pk::point pos)
		{
			return pk::is_valid_pos(pos) ? pk::get_unit(pos) : null;
		}

		void 행동회복(pk::unit@ unit)
		{
			if (pk::rand_bool(행동완료_회복_확률))
			{
				if (unit.leader < 0 || unit.leader >= 무장_끝)
					return;
				unit.action_done = false;
				pk::say(pk::encode("한번더~"), pk::get_person(unit.leader), unit);
			}
		}
		void 기력회복(pk::unit@ unit)
		{
			if (pk::rand_bool(기력회복_확률))
			{
				if (unit.leader < 0 || unit.leader >= 무장_끝)
					return;
				pk::add_energy(unit, 기력회복_양, true);
				pk::say(pk::encode("헛 갑자기 힘이난다."), pk::get_person(unit.leader), unit);
			}
		}
		void 교란효과(pk::unit@ unit)
		{
			if (pk::rand_bool(교란_효과))
			{
				pk::list<pk::unit@> units;
				for (int i = 0; i < 방향_끝; i++)
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
					pk::set_status(units[0],unit, 부대상태_혼란, pk::rand(2) + 1);
					pk::say(pk::encode("???"), pk::get_person(unit.leader), unit);
					pk::say(pk::encode("???"), pk::get_person(units[0].leader), units[0]);
				}
			}
		}
		void 위보효과(pk::unit@ unit)
		{
			if (pk::rand_bool(위보_효과))
			{
				pk::list<pk::unit@> units;
				for (int i = 0; i < 방향_끝; i++)
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
					pk::set_status(units[0],unit, 부대상태_위보, pk::rand(2) + 1);
					pk::say(pk::encode("???"), pk::get_person(unit.leader), unit);
					pk::say(pk::encode("???"), pk::get_person(units[0].leader), units[0]);
				}
			}
		}
		void 동토효과(pk::unit@ unit)
		{
			if (pk::rand_bool(동토_효과))
			{
				pk::list<pk::unit@> units;
				for (int i = 0; i < 방향_끝; i++)
				{
					pk::point pt = pk::get_neighbor_pos(unit.get_pos(), i, 1);
					pk::unit@ u = getUnit(pt);
					if (u == null || !pk::is_enemy(unit, u))
						continue;

					pk::unit@ u0 = null;
					pk::unit@ u1 = null;
					switch (i)
					{
					case 방향_북:
						@u0 = getUnit(pk::get_neighbor_pos(unit.get_pos(), 방향_북동, 1));
						@u1 = getUnit(pk::get_neighbor_pos(unit.get_pos(), 방향_북서, 1));
						break;
					case 방향_북동:
						@u0 = getUnit(pk::get_neighbor_pos(unit.get_pos(), 방향_북, 1));
						@u1 = getUnit(pk::get_neighbor_pos(unit.get_pos(), 방향_남동, 1));
						break;
					case 방향_남동:
						@u0 = getUnit(pk::get_neighbor_pos(unit.get_pos(), 방향_북동, 1));
						@u1 = getUnit(pk::get_neighbor_pos(unit.get_pos(), 방향_남, 1));
						break;
					case 방향_남:
						@u0 = getUnit(pk::get_neighbor_pos(unit.get_pos(), 방향_남동, 1));
						@u1 = getUnit(pk::get_neighbor_pos(unit.get_pos(), 방향_남서, 1));
						break;
					case 방향_남서:
						@u0 = getUnit(pk::get_neighbor_pos(unit.get_pos(), 방향_북서, 1));
						@u1 = getUnit(pk::get_neighbor_pos(unit.get_pos(), 방향_남, 1));
						break;
					case 방향_북서:
						@u0 = getUnit(pk::get_neighbor_pos(unit.get_pos(), 방향_북, 1));
						@u1 = getUnit(pk::get_neighbor_pos(unit.get_pos(), 방향_남서, 1));
						break;
					default:
						break;
					}
					if (u0 != null)
					{
						pk::attack(u, u0);
						pk::say(pk::encode("그만 같은 편이다"), pk::get_person(u.leader), u);
						pk::say(pk::encode("미쳤소?"), pk::get_person(u0.leader), u0);
						break;
					}
					else if (u1 != null)
					{
						pk::attack(u, u1);
						pk::say(pk::encode("그만 같은 편이다"), pk::get_person(u.leader), u);
						pk::say(pk::encode("미쳤소?"), pk::get_person(u1.leader), u1);
						break;
					}
				}
			}
		}

		void 부대행동완료(pk::unit@ unit)
		{
			switch (pk::rand(5))
			{
			case 0: 행동회복(unit); break;
			case 1: 기력회복(unit); break;
			case 2: 교란효과(unit); break;
			case 3: 위보효과(unit); break;
			case 4: 동토효과(unit); break;
			default:
				break;
			}
		}

	}
	Main main;
}
