namespace 징병_치안_증감
{
	class Main
	{
		Main()
		{
			pk::set_func(101, pk::func101_t(callback));
		}

		int callback(pk::city@ city, const pk::detail::arrayptr<pk::person@> &in actors, int troops)
		{
			int n = 100;
			for (int i = 0; i < actors.length; i++)
			{
				pk::person@ actor = actors[i];
				if (pk::is_alive(actor))
					n = n + actor.stat[int(pk::core["징병.능력"])];
			}

			// 인심장악 기교가 치안 저하를 줄임
			if (pk::has_tech(city, 기교_인심장악))
				n *= 1.25f;

			// 특기 위압이 치안 70 이하를 막음 (특기종합패치)
			pk::building@ building = pk::city_to_building(city);
			if (building.has_skill(특기_위압))
				return pk::max(-troops / n, -pk::max(0, city.public_order - 70));

			return -troops / n;
		}
	}

	Main main;
}