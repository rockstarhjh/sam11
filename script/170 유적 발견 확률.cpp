﻿namespace 유적_발견_확률
{
	class Main
	{
		Main()
		{
			pk::set_func(170, pk::func170_t(callback));
		}

		int callback(pk::unit@ unit, int facility_id)
		{
			pk::person@ leader = pk::get_person(unit.leader);
			pk::force@ force = pk::get_force(unit.get_force_id());

			// 강운 연구시 유적 100% 발견
			if (unit.has_skill(특기_강운) and force.sp_ability_researched[6] and pk::get_ability(force.sp_ability[6]).skill == 특기_강운)
				return 100;

			if (leader.kouseki < 10000 or unit.attr.stat[부대능력_매력] < 80)
				return 0;
			else if (facility_id == 시설_유적 and pk::has_member(unit, 무장_이적))
				return 100;
			else
				return unit.attr.stat[부대능력_매력] / 2;
		}
	}

	Main main;
}