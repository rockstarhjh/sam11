namespace �׺��ǰ�_Ȯ��
{
	class Main
	{
		Main()
		{
			pk::set_func(113, pk::func113_t(callback));
		}

		pk::int_bool callback(const pk::solicit_cmd_info &in info)
		{
			bool accurate = true;

			// 1��1 ��Ȳ�� ��� �׻� ����
			if (pk::get_force_list().count <= 2) return pk::int_bool(2, accurate);

			pk::force@ actor_force = pk::get_force(info.actor.get_force_id());

			if (!pk::is_alive(actor_force)) return pk::int_bool(2, accurate);

			// �ó����� ���� 1�� �̸��� ��� �׻� ����
			if (pk::get_elapsed_years() < 1) return pk::int_bool(2, accurate);

			// ���� ���� ������ ���ü��� ��ǥ ���� ���ü��� 4�� �̸��� ��� �׻� ����
			if (pk::get_city_count(actor_force) < pk::get_city_count(info.target) * 4) return pk::int_bool(2, accurate);

			// ���� ���� ������ ���¼��� ��ǥ ���� ���¼��� 3�� �̸��� ��� �׻� ����
			if (pk::get_troops(actor_force) < pk::get_troops(info.target) * 3) return pk::int_bool(2, accurate);

			// ��ǥ ������ ���ð� 5�� �̻��� ��� �׻� ����
			if (pk::get_city_count(info.target) >= 5) return pk::int_bool(2, accurate);

			pk::person@ target_kunshu = pk::get_person(info.target.kunshu);

			if (!pk::is_alive(target_kunshu)) return pk::int_bool(2, accurate);

			// ������ ���ð� ���ٸ� �׻� ����
			if (!pk::is_neighbor_force(actor_force, info.target)) return pk::int_bool(2, accurate);

			// ��ǥ ���� ���ְ� ���� ������ ���ָ� �����Ѵٸ� �׻� ����
			if (pk::is_dislike(target_kunshu, pk::get_kunshu_id(info.actor))) return pk::int_bool(2, accurate);

			// ��ǥ ���� ���ְ� ���� ������ �����Ѵٸ� �׻� ����
			if (pk::is_dislike(target_kunshu, info.actor.get_id())) return pk::int_bool(2, accurate);

			int k = info.target.kunshu;

			// ���� �׺����� �ʴ� ����
			if (k == ����_���� or k == ����_��Ź or k == ����_�尢 or k == ����_���� or k == ����_���� or k == ����_��� or k == ����_�հ� or k == ����_��å or k == ����_����) return pk::int_bool(2, true);

			if (pk::get_city_count(info.target) <= 0) return pk::int_bool(2, accurate);

			int n = 0;
			int g = 0;
			int difficulty = pk::get_scenario().difficulty;

			n += (pk::get_city_count(actor_force) / pk::get_city_count(info.target)) / 2;
			n += (pk::get_city_count(actor_force) - pk::get_city_count(info.target)) / 5;
			n -= pk::get_aishou_distance(target_kunshu, info.actor.get_id()) / 7;
			n += pk::is_protecting_the_emperor(actor_force) ? 10 : 0;
			n += func_5b3f40(info.actor, target_kunshu, 0, 10, 20);
			n += info.actor.stat[����ɷ�_�ŷ�];
			if (difficulty == ���̵�_���)
				n = int(n * 0.8f);
			else if (difficulty == ���̵�_Ư��)
				n = int(n * 0.7f);
			n /= 2;
			n += pk::rand(n, info.gold, info.target.get_id(), info.actor.get_id(), info.actor.service, 0, 0, 0);

			g = target_kunshu.character * 7 - info.target.relations[actor_force.get_id()] / 4;

			if (n * 2 >= g + 100) accurate = false;

			if (n >= g + 100) return pk::int_bool(0, accurate);

			if (n >= g + 95) return pk::int_bool(1, accurate);

			return pk::int_bool(2, accurate);
		}

		/**
			���๫��� ��ǥ���� ������ ���迡 ���� ���ʽ�
		*/
		int func_5b3f40(pk::person@ actor, pk::person@ target_kunshu, int bad, int good, int best)
		{
			int actor_id = actor.get_id();
			if (pk::is_gikyoudai(target_kunshu, actor_id) or pk::is_fuufu(target_kunshu, actor_id)) return best;
			if (pk::is_like(target_kunshu, actor_id)) return good;
			if (pk::is_dislike(target_kunshu, actor_id)) return bad;
			return 0;
		}
	}

	Main main;
}