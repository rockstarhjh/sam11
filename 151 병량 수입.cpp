/*
@수정자: 기마책사
@Update: '20.8.29   / 변경내용: 유저 도시수 패널티 추가, 캠페인에서는 커스텀 설정 사용 불가
*/


namespace 병량_수입
{
    
    //---------------------------------------------------------------------------------------
    // 유저 설정 (true = on, false = off)
    const bool  유저_도시수_패널티 = true;     // 유저세력에 대해서 도시수에 비례하여 수입 디버프 (도시당 5% 감소)
    
    //---------------------------------------------------------------------------------------
    
    
	class Main
	{
		Main()
		{
			pk::set_func(151, pk::func151_t(callback));
		}

		int callback(pk::city@ city)
		{
			if (city is null or !pk::is_valid_force_id(city.get_force_id()))
				return 0;

			// 기본 병량 수입
			int n = city.harvest;

			for (auto i = 0; i < city.max_devs; i++)
			{
				pk::building@ building = city.dev[i].building;
				int facility_id = -1;

				if (pk::is_alive(building))
				{
					facility_id = building.facility;
					switch (facility_id)
					{
					case 시설_농장:
					case 시설_군둔농:
						if (!building.completed)
							continue;
						break;
					case 시설_농장2단:
						if (!building.completed)
							facility_id = 시설_농장;
						break;
					case 시설_농장3단:
						if (!building.completed)
							facility_id = 시설_농장2단;
						break;
					default:
						continue;
					}
				}

				// 내정시설 별 생산력을 더함.
				pk::facility@ facility = pk::get_facility(facility_id);
				if (pk::is_alive(facility))
				{
					int y = facility.yield;
					// 농장은 곡창과 인접한 경우 1.5배.
					if (facility_id == 시설_농장 or facility_id == 시설_농장2단 or facility_id == 시설_농장3단)
					{
						if (func_49ed70(building.get_pos(), 시설_곡창))
							y = int(y * 1.5f);
					}
					// 군둔농일 경우 병력수에 비례하여 생산력 조정.
					else if (facility_id == 시설_군둔농)
					{
						y = int(pk::max(city.troops, 15000) * y / 15000);
					}
					n = n + y;
				}
			}

			switch (pk::get_scenario().difficulty)
			{
			case 난이도_특급:
				// 특급일 경우 플레이어 0.75배, 컴퓨터 1.25배.
				if (city.is_player())
					n = int(n * 0.75f);
				else
					n = int(n * 1.25f);
				break;

			case 난이도_초급:
				// 초급일 경우 플레이어, 컴퓨터 모두 1.25배.
				n = int(n * 1.25f);
				break;
			}

			// 도시 치안값을 백분율로 곱.
			n = int(n * pk::max(city.public_order, 50) / 100);
			
            /* 버프 삭제
			// 군주가 [조조]인 경우에 1.25배
			if (pk::get_kunshu_id(city) == 무장_조조)
				n *= 1.25f;
			
			// 군주가 [장로]인 경우에 1.45배
			if (pk::get_kunshu_id(city) == 무장_장노)
				n *= 1.45f;
            */
            

            // 유저_도시수_패널티 ('20.8.29)
            if (유저_도시수_패널티 and city.is_player() and !pk::is_campaign())
            {
                pk::force@ force = pk::get_force(city.get_force_id());
                float force_city_count = float(pk::get_city_list(force).count);
                n = int(n * (1.f - (force_city_count * 0.05f)));
            }
            
			return n;
		}

		/**
			인접 시설 검색.
		*/
		bool func_49ed70(pk::point pos, int facility_id)
		{
			for (int i = 0; i < 방향_끝; i++)
			{
				pk::point neighbor_pos = pk::get_neighbor_pos(pos, i);
				if (pk::is_valid_pos(neighbor_pos))
				{
					pk::building@ building = pk::get_building(neighbor_pos);
					if (pk::is_alive(building) and building.facility == facility_id and building.completed)
						return true;
				}
			}
			return false;
		}
	}

	Main main;
}