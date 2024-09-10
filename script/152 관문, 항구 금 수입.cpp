namespace 관문_금_수입
{
	
    //=======================================================================================

    const int  컴퓨터세력_병력유지비_비율 = 0.9f;  // 높을 수록 비용 증가, 유저 세력과 똑같이 하려면 1.0f.

    const int  거점_병력유지비_비율 = 0.02f;  // 거점 내 병력들 유지비용 비율. 높을 수록 비용 증가   
    const int  부대_병력유지비_비율 = 0.03f;  // 출진한 부대 병력들 유지비용 비율. 높을 수록 비용 증가    
    
    //=======================================================================================		
	
	class Main
	{
		Main()
		{
			pk::set_func(152, pk::func152_t(callback));
		}


        // 병력유지비 함수 (인구 개념)
        int func_troops_pay(pk::building@ building)
        {
          int sum_unit_troops = 0;
          pk::force@ force = pk::get_force(building.get_force_id()); // 거점의 세력
          array<pk::unit@> unit_arr = pk::list_to_array(pk::get_unit_list(force)); // 거점 세력의 부대 목록
          for (int i = 0; i < int(unit_arr.length); i++)
          {
           pk::unit@ unit = unit_arr[i];
           if (building.get_id() == pk::get_service(unit)) // 거점 세력 부대의 소속이 해당 거점이라면
           sum_unit_troops += int(unit.troops); // 해당 부대의 병사수 더함
           }

            // 거점 병력 유지비 + 부대 병력 유지비
           return int(pk::get_troops(building) * 거점_병력유지비_비율 + sum_unit_troops * 부대_병력유지비_비율 ); // 최종적으로 원하는 비용의 비율을 곱해 반환
           }


		int callback(pk::building@ building, int city_revenue)
		{
			

       // 병력 유지비 차감된 금 수입 예상 (인구 개념) 
          
          
	 if (!building.is_player())                        
              {

                    if ( pk::get_gold(building) >= 300 ) 
                      {
                       city_revenue = pk::max ( city_revenue - (func_troops_pay(building) * 컴퓨터세력_병력유지비_비율) , - 150);        //  컴퓨터 세력은 다음 금 수입이 마이너스 150 이하로 안떨어짐  
                      }

                    else if ( pk::get_gold(building) < 300 ) 
                      {
                       city_revenue = pk::max ( city_revenue - (func_troops_pay(building) * 컴퓨터세력_병력유지비_비율) ,  500);        // 컴퓨터 세력 현재 보유금이 300 미만이면 다음 달 금 수입은 최소 500 이상 보장
                      }             

              }
              else
              {
                  city_revenue = city_revenue - func_troops_pay(building);     // 플레이어는 정상적
              }  			
			
			return city_revenue * 0.50f;
		}
	}

	Main main;
}