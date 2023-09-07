/*
@수정자: 기마책사
@Update: '18.12.22  / 변경내용: 병기차감 스크립트 분리
@Update: '19.2.23   / 변경내용: 게임 내에서 x0.2 자동적용되어서 스크립트에서 제외
@Update: '20.8.25   / 변경내용: 병기유지비설정과 병기차감설정 옵션분리
@Update: '20.8.29   / 변경내용: 유저 도시수 패널티 추가, 캠페인에서는 커스텀 설정 사용 불가
*/


namespace 관문_금_수입
{
    
    
    //---------------------------------------------------------------------------------------
    // 유저 설정 (true = on, false = off)
    const bool  병기유지비설정 = false;         // 병기 보유량에 비례하여 금 소비, 금 없을 시 병기 차감
    const int   병기차감시기 = 1;               // 병기차감모드1 또는 모드2 사용 시 (0: 매턴,  1: 매월 1일 )
    
    const bool  비용대신_병기차감_모드 = true;    // 병기차감모드1 (유지비 true 모드 시 활성화 : 금부족 시 병기를 대신 차감)
    const float 비용대신_병기차감_비율 = 2.5f;    // 병기차감모드1 활성화 시 병기 차감비율
    
    const bool  병력초과_병기차감_모드 = true;    // 병기차감모드2 (유지비 false 모드 시 활성화 : 금 소비 없이 병력보다 많은 병기에 대해서 일정 비율 차감)
    const float 병력초과_병기차감_비율 = 0.01f;   // 병기차감모드2 활성화 시 병기 차감비율
    
    const bool  유저_도시수_패널티 = true;     // 유저세력에 대해서 도시수에 비례하여 수입 디버프 (도시당 5% 감소)
    
    //---------------------------------------------------------------------------------------
    
    
	class Main
	{
		Main()
		{
			pk::set_func(152, pk::func152_t(callback));
            
            
            pk::bind(111, pk::trigger111_t(onTurnStart));
		}

		int callback(pk::building@ building, int city_revenue)
		{
            // int n = int(city_revenue * 0.2f);
            int n = int(city_revenue);      // 게임 내에서 x0.2 자동적용되어서 스크립트에서 제외 ('19.2.23)
            
            
            
            // 항구인 경우 금수입 1.5배 적용 ('18.10.15)
            if ( (pk::get_hex_object_id(building) >= 건물_항구시작) and (pk::get_hex_object_id(building) < 건물_항구끝) )
                n = int(n * 1.5f);
            
            
            // 유저_도시수_패널티 ('20.8.29)
            if (유저_도시수_패널티 and building.is_player() and !pk::is_campaign())
            {
                pk::force@ force = pk::get_force(building.get_force_id());
                float force_city_count = float(pk::get_city_list(force).count);
                n = int(n * (1.f - (force_city_count * 0.05f)));
            }
            
            // ------------------------------------------------------------------
            // 도시 내 병기 보유량에 따른 금수입 감소 적용 : 병기 유지비 개념 ('18.10.14)
            
            if (병기유지비설정 and !pk::is_campaign())
            {
            
                n = int(n * 1.5f); // 병기 보유량에 의한 수입 감소를 감안하여 기본 수입 50% 상향 조정 : 도시수입의 20%에서 30%로 변경
                
                float rich_rate = pk::is_valid_person_id(building.who_has_skill(특기_부호))? 1.5f : 1.0f;  // 일반=1.0  특기부호=1.5 반환
                
                // 일반병기 유지비 차감, 병기 부족 시 수입 대신 병기 보유량 감소
                int weapon_qty1 = pk::get_weapon_amount(building, 병기_창);
                int weapon_qty2 = pk::get_weapon_amount(building, 병기_극);
                int weapon_qty3 = pk::get_weapon_amount(building, 병기_노);
                int weapon_qty4 = pk::get_weapon_amount(building, 병기_군마);
                int weapon_sum = pk::max(1, weapon_qty1 + weapon_qty2 + weapon_qty3 + weapon_qty4);   // 병기 0 일 경우 error 발생 방지용 ('18.10.21)
                
                int weapon_pay = int(0.010f * weapon_sum / rich_rate);
                int gold_estimate = pk::get_gold(building) + n;
                
                n = n - weapon_pay;
                
                /*
                if (gold_estimate > weapon_pay) // 보유금 + 수입 여유 시 유지비 지출
                    n = n - weapon_pay;
                else                            // 보유금 + 수입 부족 시 부족 차액에 비례하여 보유 병기 균등 감소
                {
                    n = -pk::get_gold(building);
                    
                    pk::add_weapon_amount(building, 병기_창,  int((gold_estimate - weapon_pay)* 2.5f * weapon_qty1 / weapon_sum), true);
                    pk::add_weapon_amount(building, 병기_극,  int((gold_estimate - weapon_pay)* 2.5f * weapon_qty2 / weapon_sum), true);
                    pk::add_weapon_amount(building, 병기_노,  int((gold_estimate - weapon_pay)* 2.5f * weapon_qty3 / weapon_sum), true);
                    pk::add_weapon_amount(building, 병기_군마, int((gold_estimate - weapon_pay)* 2.5f * weapon_qty4 / weapon_sum), true);
                }
                */
                
                // 공성병기 및 전함은 유지비 차감만 적용 
                n = n - int(15.f*(pk::get_weapon_amount(building, 병기_충차)));
                n = n - int(15.f*(pk::get_weapon_amount(building, 병기_정란)));
                n = n - int(20.f*(pk::get_weapon_amount(building, 병기_목수)));
                n = n - int(25.f*(pk::get_weapon_amount(building, 병기_투석)));
                n = n - int(20.f*(pk::get_weapon_amount(building, 병기_누선)));
                n = n - int(25.f*(pk::get_weapon_amount(building, 병기_투함)));
            
                // ------------------------------------------------------------------
            
            }
            
            
            
			return n;
		}
        
        
        //---------------------------------------------------------------------------------------
        
        void onTurnStart(pk::force@ force)
		{
            if(pk::is_campaign()) return;
            
            float maintenance_period = -1.0f;
            if (병기차감시기 == 0)   
                maintenance_period = 1/3.f;  // 매턴
            else if (병기차감시기 == 1 and (pk::get_day() == 1))    
                maintenance_period = 1.0f;   // 매월 1일
            
            
            if ((비용대신_병기차감_모드 or 병력초과_병기차감_모드) and maintenance_period > 0.f)
            {
                for (int i = 건물_도시시작; i < 건물_도시끝; i++)
                {
                    pk::building@ building = pk::get_building(i);
                    
                    if (force.get_id() == building.get_force_id())
                    {
                        weapon_maintenance(building, maintenance_period);
                    }
                }
            }
            
        }
        
        void weapon_maintenance(pk::building@ building, float ratio)
        {
            int rich_rate = 1;
            
            // 일반병기 유지비 차감, 병기 부족 시 수입 대신 병기 보유량 감소
            int weapon_qty1 = pk::get_weapon_amount(building, 병기_창);
            int weapon_qty2 = pk::get_weapon_amount(building, 병기_극);
            int weapon_qty3 = pk::get_weapon_amount(building, 병기_노);
            int weapon_qty4 = pk::get_weapon_amount(building, 병기_군마);
            int weapon_sum = pk::max(1, weapon_qty1 + weapon_qty2 + weapon_qty3 + weapon_qty4);
            
            int weapon_pay = int(0.010f * weapon_sum / rich_rate);
            int gold_estimate = pk::get_gold(building);
            int troops = pk::get_troops(building);
            
            if ((병기유지비설정 and 비용대신_병기차감_모드) and gold_estimate <= weapon_pay) // 보유금 + 수입 여유 시 유지비 지출
            {
                pk::add_weapon_amount(building, 병기_창,  int((gold_estimate - weapon_pay)* 비용대신_병기차감_비율 * weapon_qty1 / weapon_sum * ratio), true );
                pk::add_weapon_amount(building, 병기_극,  int((gold_estimate - weapon_pay)* 비용대신_병기차감_비율 * weapon_qty2 / weapon_sum * ratio), true );
                pk::add_weapon_amount(building, 병기_노,  int((gold_estimate - weapon_pay)* 비용대신_병기차감_비율 * weapon_qty3 / weapon_sum * ratio), true );
                pk::add_weapon_amount(building, 병기_군마, int((gold_estimate - weapon_pay)* 비용대신_병기차감_비율 * weapon_qty4 / weapon_sum * ratio), true );
            }
            else if ((!병기유지비설정 and 병력초과_병기차감_모드) and troops <= weapon_sum) // 병력보다 많은 무기에 대해서 일정비율 병기 차감
            {
                pk::add_weapon_amount(building, 병기_창,  int((troops - weapon_sum)* 병력초과_병기차감_비율 * weapon_qty1 / weapon_sum * ratio), true );
                pk::add_weapon_amount(building, 병기_극,  int((troops - weapon_sum)* 병력초과_병기차감_비율 * weapon_qty2 / weapon_sum * ratio), true );
                pk::add_weapon_amount(building, 병기_노,  int((troops - weapon_sum)* 병력초과_병기차감_비율 * weapon_qty3 / weapon_sum * ratio), true );
                pk::add_weapon_amount(building, 병기_군마, int((troops - weapon_sum)* 병력초과_병기차감_비율 * weapon_qty4 / weapon_sum * ratio), true );
            }
              
                
            return ;
        }
        
        
        
	}

	Main main;
}