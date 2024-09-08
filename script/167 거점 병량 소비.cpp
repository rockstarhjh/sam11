﻿namespace 거점_병량_소비
{
	class Main
	{
		Main()
		{
			pk::set_func(167, pk::func167_t(callback));
		}

		int callback(pk::building@ building)
		{
			if (!pk::is_alive(building) or !pk::is_valid_force_id(building.get_force_id()))
				return 0;

			// 능력연구를 위한 문장
			pk::force@ force = pk::get_force(building.get_force_id());

			float n = 0;

			if (building.is_on_fire())
			{
				pk::person@ taishu = pk::get_person(pk::get_taishu_id(building));
				int pol = taishu !is null ? taishu.stat[무장능력_정치] : 0;
				n = n + (6.f - (pol / 20.f)) * pk::get_food(building) / 100.f;
			}

			// 미도 연구시 병량소비량 50% 감소
			if (building.has_skill(특기_미도) and force.sp_ability_researched[7] and pk::get_ability(force.sp_ability[7]).skill == 특기_미도)
				n = n + pk::get_troops(building) / 80;
			else
				n = n + pk::get_troops(building) / 40;

			if (n <= 0 and pk::get_troops(building) > 0)
				return 1;
			return n;
		}
	}

	Main main;
}