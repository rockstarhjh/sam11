﻿namespace 석병팔진_확률
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