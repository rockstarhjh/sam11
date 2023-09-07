/*
@수정자 : 기마책사
@Update: '19.5.4   // 수정내용: 유저_도시수_패널티 추가
@Update: '20.8.29  // 수정내용: 캠페인에서는 커스텀 세팅 사용 불가하도록 수정
*/

namespace 징병_치안_증감
{
    //---------------------------------------------------------------------------
    
    const bool 유저_도시수_패널티 = true;   // 유저세력에 대해서 도시수에 비례하여 치안감소 패널티 (도시당 1% 증가)

    //---------------------------------------------------------------------------

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
			n = -troops / n;
			
			/*
			// 군주가 [유비]인 경우에 1/2 감소
				if (pk::get_kunshu_id(actors[0]) == 무장_유비)
					n /= 2;
				
			// 군주가 [유우]인 경우에 1/2 감소
				if (pk::get_kunshu_id(actors[0]) == 무장_유우)
					n /= 2;
            */
            
            
            // 유저_도시수_패널티 ('19.5.4)
            if (유저_도시수_패널티 and city.is_player() and !pk::is_campaign())
            {
                pk::force@ force = pk::get_force(city.get_force_id());
                float force_city_count = float(pk::get_city_list(force).count);
                n = int(n / (1.f - (force_city_count * 0.01f)));
            }
				
			return n; 
		}
	}

	Main main;
}