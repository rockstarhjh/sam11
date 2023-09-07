namespace 거점_병량_소비
{
	class Main
	{
		Main()
		{
			pk::set_func(167, pk::func167_t(callback));
		}

		int callback(pk::building@ building)
		{
			if (!pk::is_alive(building) or !pk::is_valid_force_id(building.get_force_id()))
				return 0;

			float n = 0;

			if (building.is_on_fire())
			{
				pk::person@ taishu = pk::get_person(pk::get_taishu_id(building));
				int pol = taishu !is null ? taishu.stat[무장능력_정치] : 0;
				n = n + (6.f - (pol / 20.f)) * pk::get_food(building) / 100.f;
			}
            
            //주변에 적이 있을 시 병량 소비량 2배 증가 ('18.10.14)
            if (pk::enemies_around(building))
                n = n + pk::get_troops(building) / 20.f;    // 전투부대 수준으로 병량 소비
            else
                n = n + pk::get_troops(building) / 40.f;

            
            
			if (n <= 0 and pk::get_troops(building) > 0)
				return 1;
			return int(n);
		}
	}

	Main main;
}