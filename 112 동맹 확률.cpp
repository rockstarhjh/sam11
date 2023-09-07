namespace ����_Ȯ��
{
	class Main
	{
		Main()
		{
			pk::set_func(112, pk::func112_t(callback));
		}

		pk::int_bool callback(const pk::alliance_cmd_info &in info)
		{
			bool accurate = true;
			pk::person@ target_kunshu = pk::get_person(info.target.kunshu);

			if (!pk::is_alive(target_kunshu)) return pk::int_bool(2, accurate);

			int actor_force_id = info.actor.get_force_id();
			int target_force_id = info.target.get_id();

			// ���ΰ� �ִٸ� �׻� ����
			if (func_5be0e0(actor_force_id, target_force_id) or func_5be0e0(target_force_id, actor_force_id)) return pk::int_bool(2, accurate);

			// ���� ������ �� Ư�⸦ �����ϰ� ���� �ʰ� ��ǥ ���� ���ְ� ���� ���� ���ָ� �����Ѵٸ� �׻� ����
			if (!pk::has_skill(info.actor, Ư��_��) and pk::is_dislike(target_kunshu, pk::get_kunshu_id(info.actor))) return pk::int_bool(2, accurate);

			int n = 0;
			int g = 0;
			int difficulty = pk::get_scenario().difficulty;

			n += int(func_5b3130(info.actor, target_kunshu, -1, 1, 1.5) * 10);
			n += int(info.gold / 150);
			n -= int(pk::get_aishou_distance(target_kunshu, info.actor.get_id()) / 5);
			n += int(info.actor.stat[����ɷ�_��ġ]);
			if (difficulty == ���̵�_���)
				n = int(n * 0.8f);
			else if (difficulty == ���̵�_Ư��)
				n = int(n * 0.7f);

			g = (110 - info.target.relations[actor_force_id]) * 2;

			if (n * 2 > g) accurate = false;

			if (n > g) return pk::int_bool(0, accurate);

			// ���� ������ �� Ư�⸦ �����ϰ� ����
			if (pk::has_skill(info.actor, Ư��_��))
			{
				// Ư�� ��� �÷��̾��� ��쿡�� 20%, ������ 100% ����
				// if (difficulty != ���̵�_Ư�� or !info.actor.is_player() or pk::randbool(20)) return pk::int_bool(1, accurate);
				if (!info.actor.is_player() or pk::rand_bool(int(pk::core::skill_constant(info.actor.get_id(), Ư��_��, difficulty)))) return pk::int_bool(1, accurate);
			}

			g = (100 - info.target.relations[actor_force_id]) * 2;

			if (n > g) return pk::int_bool(1, accurate);

			return pk::int_bool(2, accurate);
		}

		/**
			���๫��� ��ǥ���� ������ ���迡 ���� ���ʽ�
		*/
		float func_5b3130(pk::person@ actor, pk::person@ target_kunshu, float bad, float good, float best)
		{
			int actor_id = actor.get_id();
			if (pk::is_gikyoudai(target_kunshu, actor_id) or pk::is_fuufu(target_kunshu, actor_id)) return best;
			if (pk::is_like(target_kunshu, actor_id)) return good;
			if (pk::is_dislike(target_kunshu, actor_id)) return bad;
			return 0;
		}

		/**
			src ������ dst ���� ������ ���η� ��� �ִ��� Ȯ��
		*/
		bool func_5be0e0(int src, int dst)
		{
			pk::list<pk::person@> list = pk::get_person_list(pk::mibun_flags(�ź�_����));
			for (int i = 0; i < list.count; i++)
			{
				pk::person@ person = list[i];
				if (person.former_force == dst)
				{
					pk::hex_object@ hexobj = pk::get_hex_object(person.location);
					if (pk::is_alive(hexobj) and hexobj.get_force_id() == src)
						return true;
				}
			}
			return false;
		}
	}

	Main main;
}