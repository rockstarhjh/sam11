/*
@ 수정한이: 기마책사
@ UPDATE: '18.11.5
*/

namespace 지형_이동_가능_설정
{
    // 기교필요여부설정 Customize ('18.11.5)
    const bool 정예기교필요 = true;  // 정예기교필요 = true, 불필요 = false 
    
    
	class Main
	{
		Main()
		{
			pk::set_func(169, pk::func169_t(callback));
		}

		bool callback(pk::unit@ unit, int terrain_id)
		{
			if (bool(pk::core["지형"][terrain_id]["이동가능"]) == false)
				return false;
            
			int weapon_id = pk::is_water_terrain(terrain_id) ? pk::get_sea_weapon_id(unit) : pk::get_ground_weapon_id(unit);
			pk::equipment@ equipment = pk::get_equipment(weapon_id);
			if (equipment !is null and equipment.movement_cost[terrain_id] == 255)
				return false;
            
			if (bool(pk::core["지형"][terrain_id]["난소행군필요"]) and !unit.has_tech(기교_난소행군))
				return false;
            
            
            
            // 산악 지형 이동에 대해서 부대는 난소행군 필요 ('18.11.5)
            // 전투병과의 산악 지형 이동에 대해서 정예기교 필요여부 설정 가능 ('18.11.5)
            // 수송부대는 난소행군+목우유마 연구 시 산악 이동 가능
            // 난소행군 연구 시 특기_답파 또는 무장_등애는 부대유형 관계없이 산악 이동 가능
            if (bool(pk::core["지형"][terrain_id]["난소행군필요"]) and unit.has_tech(기교_난소행군) and equipment !is null)
            {
                if ((terrain_id == 지형_산) and (equipment.movement_cost[지형_산] != 255) and (!pk::is_in_water(unit)) )
                {
                    if ( (pk::get_ground_weapon_id(unit) == 병기_검) and (unit.type == 부대종류_전투) )
                        return true;
                    
                    else if ( (pk::get_ground_weapon_id(unit) == 병기_창) )
                        if (!정예기교필요)
                            return true;
                        else if (정예기교필요 and unit.has_tech(기교_정예창병))
                            return true;
                        else
                            return false;
                        
                    else if ( (pk::get_ground_weapon_id(unit) == 병기_극) )
                        if (!정예기교필요)
                            return true;
                        else if (정예기교필요 and unit.has_tech(기교_정예극병))
                            return true;
                        else
                            return false;
                        
                    else if ( (pk::get_ground_weapon_id(unit) == 병기_노) )
                        if (!정예기교필요)
                            return true;
                        else if (정예기교필요 and unit.has_tech(기교_정예노병))
                            return true;
                        else
                            return false;
                        
                    else if ( (pk::get_ground_weapon_id(unit) == 병기_군마) and pk::get_tekisei(unit) >= 적성_S )
                        if (!정예기교필요)
                            return true;
                        else if (정예기교필요 and unit.has_tech(기교_정예기병))
                            return true;
                        else
                            return false;
                    
                    else if ((unit.type == 부대종류_수송) and pk::has_tech(pk::get_force(unit.get_force_id()), 기교_목우유마) )
                        return true;
                    else if ( unit.has_skill(특기_답파) )
                        return true;
                    else if ( unit.leader == 무장_등애 or unit.member[1] == 무장_등애 or unit.member[2] == 무장_등애 )
                        return true;
                    else
                        return false;
                }
            }
            
            
			return true;
		}
        
        
	}

	Main main;
}