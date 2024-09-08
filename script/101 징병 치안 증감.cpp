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

			// 능력연구를 위한 문장
			bool research = false;
			pk::force@ force = pk::get_force(city.get_force_id());

			for (int i = 0; i < actors.length; i++)
			{
				pk::person@ actor = actors[i];
				if (pk::is_alive(actor))
				{
					n = n + actor.stat[int(pk::core["징병.능력"])];

					if (pk::has_skill(actor, 특기_명성))
						research = true;
				}
			}

			// 명성 연구시 치안감소량이 추가로 증가하지 않음
			if (force.ability_researched[39] and research)
				n = n * 1.5f;

			// 법령정비 기교가 치안 저하를 줄임
			if (pk::has_tech(city, 기교_법령정비))
				n *= 1.2f;

			return -troops / n;
		}
	}

	Main main;
}