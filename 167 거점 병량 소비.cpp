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

			float n = 0;

			if (building.is_on_fire())
			{
				pk::person@ taishu = pk::get_person(pk::get_taishu_id(building));
				int pol = taishu !is null ? taishu.stat[무장능력_정치] : 0;
				n = n + (6.f - (pol / 20.f)) * pk::get_food(building) / 100.f;
			}

			// 특기 둔전이 도시에서 병사 3만명의 병량 소모 절감 (특기종합패치)
			int m = 0;
			if (pk::is_valid_person_id(building.who_has_skill(특기_둔전)))
				m = 30000;
			n = n + pk::max(0, (pk::get_troops(building) - m)) / 40;

			if (n <= 0 and pk::get_troops(building) > 0)
				return 0;
			return n;
		}
	}

	Main main;
}