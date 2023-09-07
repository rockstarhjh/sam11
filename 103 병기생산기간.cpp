/*
@수정자 : 기마책사
@Update: '20.8.29  // 수정내용: 유저_도시수_패널티 추가, 캠페인에서는 커스텀 세팅 사용 불가하도록 수정
*/

namespace 병기생산기간
{
    
    //---------------------------------------------------------------------------
        
    const bool 유저_도시수_패널티 = true;     // 유저세력에 대해서 도시수에 비례하여 생산기간 디버프 (도시당 5% 감소)
    
    //---------------------------------------------------------------------------
     
     
     
	class Main
	{
		Main()
		{
			pk::set_func(103, pk::func103_t(callback));
		}

		int callback(const pk::detail::arrayptr<pk::person@> &in actors, int weapon_id)
		{
			if (!pk::is_valid_equipment_id(weapon_id))
				return 0;
			if (weapon_id < 병기_충차)
				return 0;

			int n = 0, sum = 0, max = 0, skill_id = -1;
			bool has_skill = false;

			if (weapon_id == 병기_충차 or weapon_id == 병기_정란 or weapon_id == 병기_투석 or weapon_id == 병기_목수)
				skill_id = int(pk::core["병기생산.공방특기"]);
			else if (weapon_id == 병기_누선 or weapon_id == 병기_투함)
				skill_id = int(pk::core["병기생산.조선특기"]);

			for (int i = 0; i < actors.length; i++)
			{
				pk::person@ actor = actors[i];
				if (pk::is_alive(actor))
				{
					int s = actor.stat[int(pk::core["병기생산.능력"])];
					sum = sum + s;
					max = pk::max(max, s);
					if (pk::has_skill(actor, skill_id))
						has_skill = true;
				}
			}

			n = 10 - pk::max(sum + max - 200, 24) / 24;
            
            n = pk::max(n, 2);      // overflow 방지용 ('18.11.17)
			
            if (weapon_id >= 병기_주가)
			{
				pk::person@ actor = actors[0];
				if (pk::is_alive(actor))
				{
					pk::building@ building = pk::get_building(actor.service);
					if (pk::is_alive(building))
					{
						pk::city@ city = pk::building_to_city(building);
						if (pk::has_facility(city, 시설_연병소))
						{
							n = 8 - pk::max(sum + max - 200, 24) / 24;
							n = pk::max(n, 2);
						}
					}
				}
			}

            // 유저_도시수_패널티 ('20.8.29)
            pk::person@ actor = actors[0];
            if (유저_도시수_패널티 and actor.is_player() and !pk::is_campaign())
            {
                pk::force@ force = pk::get_force(actor.get_force_id());
                float force_city_count = float(pk::get_city_list(force).count);
                n = n + int(0.05f * force_city_count);
            }
            
            
            if (n < 2) n = 2;
            
			// 관련 특기를 가지고 있다면 반감
			if (has_skill)
				n = n / 2;
			return n;
		}
	}

	Main main;
}