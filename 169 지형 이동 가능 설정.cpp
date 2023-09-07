/*
@ ��������: �⸶å��
@ UPDATE: '18.11.5
*/

namespace ����_�̵�_����_����
{
    // �ⱳ�ʿ俩�μ��� Customize ('18.11.5)
    const bool �����ⱳ�ʿ� = true;  // �����ⱳ�ʿ� = true, ���ʿ� = false 
    
    
	class Main
	{
		Main()
		{
			pk::set_func(169, pk::func169_t(callback));
		}

		bool callback(pk::unit@ unit, int terrain_id)
		{
			if (bool(pk::core["����"][terrain_id]["�̵�����"]) == false)
				return false;
            
			int weapon_id = pk::is_water_terrain(terrain_id) ? pk::get_sea_weapon_id(unit) : pk::get_ground_weapon_id(unit);
			pk::equipment@ equipment = pk::get_equipment(weapon_id);
			if (equipment !is null and equipment.movement_cost[terrain_id] == 255)
				return false;
            
			if (bool(pk::core["����"][terrain_id]["�����౺�ʿ�"]) and !unit.has_tech(�ⱳ_�����౺))
				return false;
            
            
            
            // ��� ���� �̵��� ���ؼ� �δ�� �����౺ �ʿ� ('18.11.5)
            // ���������� ��� ���� �̵��� ���ؼ� �����ⱳ �ʿ俩�� ���� ���� ('18.11.5)
            // ���ۺδ�� �����౺+������� ���� �� ��� �̵� ����
            // �����౺ ���� �� Ư��_���� �Ǵ� ����_��ִ� �δ����� ������� ��� �̵� ����
            if (bool(pk::core["����"][terrain_id]["�����౺�ʿ�"]) and unit.has_tech(�ⱳ_�����౺) and equipment !is null)
            {
                if ((terrain_id == ����_��) and (equipment.movement_cost[����_��] != 255) and (!pk::is_in_water(unit)) )
                {
                    if ( (pk::get_ground_weapon_id(unit) == ����_��) and (unit.type == �δ�����_����) )
                        return true;
                    
                    else if ( (pk::get_ground_weapon_id(unit) == ����_â) )
                        if (!�����ⱳ�ʿ�)
                            return true;
                        else if (�����ⱳ�ʿ� and unit.has_tech(�ⱳ_����â��))
                            return true;
                        else
                            return false;
                        
                    else if ( (pk::get_ground_weapon_id(unit) == ����_��) )
                        if (!�����ⱳ�ʿ�)
                            return true;
                        else if (�����ⱳ�ʿ� and unit.has_tech(�ⱳ_�����غ�))
                            return true;
                        else
                            return false;
                        
                    else if ( (pk::get_ground_weapon_id(unit) == ����_��) )
                        if (!�����ⱳ�ʿ�)
                            return true;
                        else if (�����ⱳ�ʿ� and unit.has_tech(�ⱳ_�����뺴))
                            return true;
                        else
                            return false;
                        
                    else if ( (pk::get_ground_weapon_id(unit) == ����_����) and pk::get_tekisei(unit) >= ����_S )
                        if (!�����ⱳ�ʿ�)
                            return true;
                        else if (�����ⱳ�ʿ� and unit.has_tech(�ⱳ_�����⺴))
                            return true;
                        else
                            return false;
                    
                    else if ((unit.type == �δ�����_����) and pk::has_tech(pk::get_force(unit.get_force_id()), �ⱳ_�������) )
                        return true;
                    else if ( unit.has_skill(Ư��_����) )
                        return true;
                    else if ( unit.leader == ����_��� or unit.member[1] == ����_��� or unit.member[2] == ����_��� )
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