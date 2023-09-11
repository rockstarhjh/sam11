namespace �δ�_ȥ��_Ȯ��
{
	class Main
	{
		Main()
		{
			pk::set_func(164, pk::func164_t(callback));
		}

		int callback(pk::unit@ unit)
		{
			int troops = unit.troops;

			// ���� ���� 1000 �̻��� ��� ȸ��
			if (troops >= 1000)
				return 0;

			// �δ밡 ��� ���°� �ƴ� ��� ȸ��
			if (unit.status != �δ����_���)
				return 0;

			// ���� �� 8% + 10 Ȯ���� ȸ��
			if (pk::rand_bool(pk::min(90, pk::max(10, troops * 8 / 100 + 10))))
				return 0;

			// ��� 20% + 20 Ȯ���� ȸ��
			if (pk::rand_bool(unit.attr.stat[�δ�ɷ�_���] / 5 + 20))
				return 0;

			pk::int_int_int tuple = func_59b130(unit);
			int sum_own_troops = tuple.first;
			int sum_enemy_troops = tuple.second;
			int max_enemy_troops = tuple.third;

			// �� �δ� �� �ִ� ���� ���� 500 �̸��� ��� ȸ��
			if (max_enemy_troops < 500)
				return 0;

			// �� �δ� ���� ���� �ڼ��� �δ� ���� ���� 20% �̸��� ��� 60% Ȯ���� ȸ��
			if (sum_enemy_troops < sum_own_troops / 5)
			{
				if (pk::rand_bool(60))
					return 0;
			}
			// �� �δ� ���� ���� �ڼ��� �δ� ���� ���� 50% �̸��� ��� 40% Ȯ���� ȸ��
			else if (sum_enemy_troops < sum_own_troops / 2)
			{
				if (pk::rand_bool(40))
					return 0;
			}

			// ���� ���� 20���� ���� �� �δ� �� �ִ� ���� ������ ����, ���� ���� 40���� ���� �� �δ� ���� �պ��� ���ٸ� ȸ��
			if (troops * 20 >= max_enemy_troops and troops * 40 >= sum_enemy_troops)
				return 0;

			return 100;
		}

		pk::int_int_int func_59b130(pk::unit@ src)
		{
			// ���� �ڼ��� �δ� ���� ��
			int sum_own_troops = 0;
			// 3ĭ ���� �� �δ� ���� ��
			int sum_enemy_troops = 0;
			// 3ĭ ���� �� �δ� �� �ִ� ����
			int max_enemy_troops = 0;

			array<pk::point> arr = pk::range(src.get_pos(), 1, 3);
			for (int i = 0; i < int(arr.length); i++)
			{
				pk::unit@ dst = pk::get_unit(arr[i]);
				if (dst is null or dst.status != �δ����_���)
					continue;

				if (pk::is_enemy(src, dst))
				{
					int troops = dst.troops;
					sum_enemy_troops = sum_enemy_troops + troops;
					max_enemy_troops = pk::max(max_enemy_troops, troops);
				}
				else if (pk::is_own(src, dst))
				{
					if (pk::is_neighbor_pos(src.get_pos(), dst.get_pos()))
						sum_own_troops = sum_own_troops + dst.troops;
				}
			}

			return pk::int_int_int(sum_own_troops, sum_enemy_troops, max_enemy_troops);
		}
	}

	Main main;
}