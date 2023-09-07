namespace ����_����_Ȯ��
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
			pk::person@ assister_deputy1 = pk::get_person(assister.member[1]);
			pk::person@ assister_deputy2 = pk::get_person(assister.member[2]);
			
			int attacker_leader = attacker.leader;
			
			// ����.xml ������
			int bonus = pk::core::assist_chance(assister.leader);

			// ����ڳ� �������� ��� 50%
			if (pk::is_fuufu(assister_leader, attacker_leader) or pk::is_gikyoudai(assister_leader, attacker_leader))
				return 50 + bonus;

			
			/* 
				[����] ���� Ư���� ��� �������常 �ƴϸ� 30% (����)
				if (pk::has_skill(assister_leader, Ư��_����) and !pk::is_dislike(assister_leader, attacker_leader))
				{
					return 30 + bonus;
				}
			*/
			
			// ���� Ư���� ��� �������常 �ƴϸ� 30% (���� or ����) 
			if (assister.has_skill(Ư��_����))
			{
				if (!pk::is_dislike(pk::get_person(assister.who_has_skill(Ư��_����)), attacker_leader))
				{	
					return 30 + bonus;
				}
			}


			// ģ�ֹ����� ��� 30%
			if (pk::is_like(assister_leader, attacker_leader))
				return 30 + bonus;

			// �����̰� ���������� �ƴҰ�� 20%
			if (pk::is_ketsuen(assister_leader, attacker_leader) and !pk::is_dislike(assister_leader, attacker_leader))
				return 20 + bonus;

			return 0 + bonus;
		}
	}

	Main main;
}