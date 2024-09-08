namespace 석병팔진_확률
{
	class Main
	{
		Main()
		{
			pk::set_func(208, pk::func208_t(callback));
		}

		int callback(pk::unit@ unit)
		{
			pk::person@ leader = pk::get_person(unit.leader);
			int n = unit.attr.stat[부대능력_지력];

			pk::point unit_pos = unit.get_pos();
			array<pk::point>@ range = pk::range(unit_pos, 0, 1);
			for (int i = 1; i < range.length; i++)
			{
				pk::unit@ assister = pk::get_unit(range[i]);
				pk::force@ assister_force = pk::get_force(assister.get_force_id());

				// 기각 연구시 지력이 높은 기각 부대와 인접한 채로 석병팔진에 붙으면 반드시 혼란
				if (pk::is_alive(assister) and assister.has_skill(특기_기각) and assister.get_force_id() != unit.get_force_id())
				{
					if (assister.attr.stat[부대능력_지력] > n and assister_force.sp_ability_researched[4] and pk::get_ability(assister_force.sp_ability[4]).skill == 특기_기각)
						return 100;
				}
			}

			return (10000 - n * n) / 100 + hachijin_character_bonus(leader.character);
		}

		/** 849770 성격에 따른 확률 보너스 */
		int hachijin_character_bonus(int character)
		{
			switch (character)
			{
			case 성격_소심: return 20;
			case 성격_냉정: return 10;
			case 성격_대담: return 5;
			case 성격_저돌: return 0;
			}
			return 0;
		}
	}

	Main main;
}