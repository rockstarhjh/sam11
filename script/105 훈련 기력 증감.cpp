namespace �Ʒ�_���_����
{
	class Main
	{
		Main()
		{
			pk::set_func(105, pk::func105_t(callback));
		}

		int callback(pk::building@ building, const pk::detail::arrayptr<pk::person@> &in actors)
		{
			if (!pk::is_alive(building) or actors[0] is null)
				return 0;

			int n = 0;
			int max = pk::INT32_MIN;

			for (int i = 0; i < int(actors.length); i++)
			{
				pk::person@ actor = actors[i];
				if (pk::is_alive(actor))
				{
					int s = actor.stat[int(pk::core["�Ʒ�.�ɷ�"])];
					n += s;
					max = pk::max(max, s);
				}
			}
			n = (n + max) / pk::min(building.get_troops() / 2000 + 20, 100) + 3;
			// �����Ұ� �ִٸ� 1.5��
			if (building.facility == �ü�_���� and pk::has_facility(pk::building_to_city(building), �ü�_������))
				n = int(n * 1.5f);
			return n;
		}
	}

	Main main;
}