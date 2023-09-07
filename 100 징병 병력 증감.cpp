/*
@수정자 : 기마책사
@Update: '18.10.14  // 수정내용: 세력의 보유 특기 또는 황군인 경우 징병량 버프
@Update: '19.4.26   // 수정내용: 대도시 징병량 버프 추가
@Update: '19.5.4    // 수정내용: 유저_도시수_패널티 추가
@Update: '20.8.25   // 수정내용: null point error 오류 수정
@Update: '20.8.29  // 수정내용: 캠페인에서는 커스텀 세팅 사용 불가하도록 수정
*/

namespace 징병_병력_증감
{
    //---------------------------------------------------------------------------
    
    const bool  세력특기_명성적용 = true;   // 군주,도독,태수가 명성 특기 보유 시 버프
    const float 세력특기_군주명성 = 1.10f;   // 군주 버프 계수
    const float 세력특기_도독명성 = 1.15f;  // 도독 버프 계수
    const float 세력특기_태수명성 = 1.20f;  // 태수 버프 계수
    
    const bool  황제세력_효과적용 = true;   // 후한 황제 옹립 세력 또는 군주가 황제인 경우 버프
    const float 황제세력_명성효과 = 1.10f;  // 황제 버프 계수
    
    const bool  대도시_징병적용 = true;   // 대도시 징병량 버프 설정
    const float 대도시_징병계수 = 1.2f;   // 대도시 징병량 버프 배수
    
    const bool 유저_도시수_패널티 = true;   // 유저세력에 대해서 도시수에 비례하여 징병량 디버프 (도시당 1% 감소)
    
    //---------------------------------------------------------------------------
    
	class Main
	{
		Main()
		{
			pk::set_func(100, pk::func100_t(callback));
		}

		int callback(pk::building@ building, const pk::detail::arrayptr<pk::person@> &in actors)
		{
			if (pk::is_alive(building) and actors[0] !is null)
			{
				pk::city@ city = pk::building_to_city(building);
				if (pk::is_alive(city))
				{
					int n = 0;
					int sum = 0;
					int mul = 100;
					for (int i = 0; i < actors.length; i++)
					{
						pk::person@ actor = actors[i];
						if (pk::is_alive(actor))
						{
							sum += actor.stat[int(pk::core["징병.능력"])];
							// 명성 특기를 보유하고 있을 경우 50% 상승
							if (pk::has_skill(actor, int(pk::core["징병.특기"])))
								mul = 150;
						}
					}
					n = int((1000 + (city.public_order + 20) * sum * 5 / 100) * mul / 100 * func_5c4600(city));
					// 특급 난이도 컴퓨터일 경우 2배
					if (pk::get_scenario().difficulty == 난이도_특급 and !city.is_player())
						n *= 2;
					// 주변에 적 부대가 존재할 경우 반감
					if (pk::enemies_around(building))
						n /= 2;
					
                    
                    // -----------------------------------------------------------------------------
                    
                    // 세력
                    pk::force@ force = pk::get_force(building.get_force_id());
                    
                    // 세력의 보유 특기 ('18.10.14)
                    if (세력특기_명성적용 and !pk::is_campaign())
                    {
                        // 군주가 특기_명성 보유 시 징병량 증가
                        pk::person@ p1 = pk::get_person(pk::get_kunshu_id(building));
                        if (pk::is_alive(p1))
                        {
                            if (pk::has_skill(p1, 특기_명성))
                                n = int(n * 세력특기_군주명성);
                        }
                        // 도독이 특기_명성 보유 시 징병량 증가
                        pk::person@ p2 = pk::get_person(pk::get_totoku_id(building));
                        if (pk::is_alive(p2))
                        {
                            if (pk::has_skill(p2, 특기_명성))
                                n = int(n * 세력특기_도독명성);
                        }
                        // 태수가 특기_명성 보유 시 징병량 증가
                        pk::person@ p3 = pk::get_person(pk::get_taishu_id(building));
                        if (pk::is_alive(p3))
                        {
                            if (pk::has_skill(p3, 특기_명성))
                                n = int(n * 세력특기_태수명성);
                        }
                    }
                    
                    // 후한황제 보호세력 또는 군주가 황제인 세력 징병량 증가 ('18.10.14)
                    if (황제세력_효과적용 and !pk::is_campaign())
                    {
                        if ( pk::is_protecting_the_emperor(force) )
                            n = int(n * 황제세력_명성효과);
                        else if (force.title == 작위_황제 ) 
                            n = int(n * 황제세력_명성효과);
                    }
                    
                    // 대도시 징병량 버프 ('19.4.26)
                    if (대도시_징병적용 and pk::is_large_city(city) and !pk::is_campaign())
                        n = int(n * 대도시_징병계수);
                    
                    // 유저_도시수_패널티 ('19.5.4)
                    if (유저_도시수_패널티 and building.is_player() and !pk::is_campaign())
                    {
                        float force_city_count = float(pk::get_city_list(force).count);
                        n = int(n * (1.f - (force_city_count * 0.01f)));
                    }
                    
                    
                    // -----------------------------------------------------------------------------
                    
					return n;
				}
			}
			return 0;
		}

		float func_5c4600(pk::city@ city)
		{
			int level1 = 0, level2 = 0;
			for (int i = 0; i < int(city.max_devs); i++)
			{
				pk::building@ building = city.dev[i].building;
				if (pk::is_alive(building))
				{
					switch (building.facility)
					{
					case 시설_병영: building.completed ? level1++ : 0; break;
					case 시설_병영2단: building.completed ? level2++ : level1++; break;
					case 시설_병영3단: building.completed ? 0 : level2++; break;
					}
				}
			}
			if (int(city.barracks_counter) > level1 + level2)
				return 1.5f;
			if (int(city.barracks_counter) > level1)
				return 1.2f;
			return 1.f;
		}
	}

	Main main;
}