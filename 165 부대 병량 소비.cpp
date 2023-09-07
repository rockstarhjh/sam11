namespace 부대_병량_소비
{
	class Main
	{
		Main()
		{
			pk::set_func(165, pk::func165_t(callback));
		}

		int callback(pk::unit@ unit)
		{
			if (!pk::is_alive(unit))
				return 0;

			int n = 0;
            float m = 1.f;
			float burn = 0.f;

			if (unit.type == 부대종류_전투)
			{
				int facility_id = func_49d8e0(unit);
				if (facility_id == 시설_성채)
					m = 1.f;
				else if (facility_id == 시설_요새)
					m = 4.f / 3; // 1.333...
				else if (facility_id == 시설_진)
					m = 5.f / 3; // 1.666...
				else
					m = 2.f;
			}
            
			if (unit.is_on_fire())
				burn = (6.f - unit.attr.stat[부대능력_정치] / 20.f) * unit.food / 100;
            
            
            n = int(unit.troops * m / 20.f);   // 기본 병량 소비
            
            if (pk::get_season() == 계절_겨울)      // 겨울철 병량 소비 1.2배 ('18.10.10)
                n = int(n * 1.2f);
            
            if (pk::get_hex(unit.get_pos()).terrain == 지형_산) 
                n = int(n * 1.2f);               // 부대가 산악 행군 시 병량 소비 1.2배 ('18.10.18)
            
            if (unit.has_skill(특기_둔전))    //둔전 특기 : 부대 병량 소비 반감 ('18.10.5)
                n = int(n / 2.f);


            n = int(n + burn);
            
            
			if (n <= 0 and unit.troops > 0)
				return 1;
			return n;
		}

		/***/
		int func_49d8e0(pk::unit@ unit)
		{
			int force_id = unit.get_force_id();
			pk::force@ force = pk::get_force(force_id);

			if (!pk::is_alive(force))
				return -1;

			int facility_id = 시설_진;

			if (pk::has_tech(force, 기교_성벽강화))
				facility_id = 시설_성채;
			else if (pk::has_tech(force, 기교_시설강화))
				facility_id = 시설_요새;

			array<pk::point> arr = pk::range(unit.get_pos(), 1, pk::get_facility(facility_id).max_range);

			for (int i = 0; i < int(arr.length); i++)
			{
				pk::building@ building = pk::get_building(arr[i]);
				if (pk::is_alive(building) and building.facility == facility_id and building.completed and building.get_force_id() == force_id)
					return facility_id;
			}

			return -1;
		}
	}

	Main main;
} 