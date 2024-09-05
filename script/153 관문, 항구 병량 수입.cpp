/*
@수정자 : 기마책사
@Update : '18.10.15  / 변경내용 : 관문 병량수입 1.5배 적용
@Update : '19.2.26   / 변경내용 : 게임 내 자체적으로 x0.2배 적용되는 문제로 스크립트에서 x0.2배 적용 제외.
@Update: '20.8.29   / 변경내용: 유저 도시수 패널티 추가, 캠페인에서는 커스텀 설정 사용 불가

*/

namespace 관문_병량_수입
{
    //---------------------------------------------------------------------------------------
    // 유저 설정 (true = on, false = off)
    const bool  유저_도시수_패널티 = true;     // 유저세력에 대해서 도시수에 비례하여 수입 디버프 (도시당 5% 감소)
    
    //---------------------------------------------------------------------------------------
    
    
	class Main
	{
		Main()
		{
			pk::set_func(153, pk::func153_t(callback));
		}

		int callback(pk::building@ building, int city_harvest)
		{
			//int n = int(city_harvest * 0.2f);
            
			int n = int(city_harvest);  // '19.2.16
            
            // 관문인 경우 병량수입 1.5배 적용 ('18.10.15)
            if ( (pk::get_hex_object_id(building) >= 건물_관문시작) and (pk::get_hex_object_id(building) < 건물_관문끝) )
                n = int(n * 0.8f);
            
             
            // 유저_도시수_패널티 ('20.8.29)
            if (유저_도시수_패널티 and building.is_player() and !pk::is_campaign())
            {
                pk::force@ force = pk::get_force(building.get_force_id());
                float force_city_count = float(pk::get_city_list(force).count);
                n = int(n * (1.f - (force_city_count * 0.05f)));
            }
            
            return n;
		}
	}

	Main main;
}