namespace 지원_공격_확률
{
	class Main
	{
		Main()
		{
			pk::set_func(200, pk::func200_t(callback));
		}

		int callback(pk::unit@ assister, pk::unit@ attacker, pk::unit@ target)
		{
			pk::person@ assister_leader = pk::get_person(assister.leader);
			int attacker_leader = attacker.leader;
			// 무장.xml 설정값
			int bonus = pk::core::assist_chance(assister.leader);

			// 내조 배우자는 100% 지원공격
			if (pk::is_fuufu(assister_leader, attacker_leader) and pk::has_skill(assister_leader, 특기_내조))
				return 100;

			// 배우자나 의형제일 경우 50%
			if (pk::is_fuufu(assister_leader, attacker_leader) or pk::is_gikyoudai(assister_leader, attacker_leader))
				return 50 + bonus;

			// 경국이 공격하고 여성, 혐오무장이 아니면 50%
			if (pk::has_skill(pk::get_person(attacker.leader), 특기_경국) and (pk::get_person(assister.leader).sex != 성별_여) and !pk::is_dislike(assister_leader, attacker_leader))
				return 50 + bonus;

			// 혐오무장일 경우 0%
			if (pk::is_dislike(assister_leader, attacker_leader))
				return 0;

			// 보좌 특기일 경우 관계 상승
			if (pk::has_skill(assister_leader, 특기_보좌))
			{
				// 친애무장이거나 혈연이면 50%
				if (pk::is_like(assister_leader, attacker_leader) or pk::is_ketsuen(assister_leader, attacker_leader))
					return 50 + bonus;

				// 특별한 관계가 없으면 30%
					return 30 + bonus;
			}
			// 보좌 특기가 아닌 경우
			else
			{
				// 친애무장이면 30%
				if (pk::is_like(assister_leader, attacker_leader))
					return 30 + bonus;

				// 혈연이면 20%
				if (pk::is_ketsuen(assister_leader, attacker_leader))
					return 20 + bonus;
			}

			return 0 + bonus;
		}
	}

	Main main;
}