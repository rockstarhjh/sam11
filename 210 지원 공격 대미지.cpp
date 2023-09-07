namespace ����_����_�����
{
    //---------------------------------------------------------------------------------------
    // ���� ���� (true = on, false = off)
	const bool ���ȿ������ = true;   // ��¿� ����Ͽ� ������ ���� ���� ȿ��
    const bool ����������� = true;   // ���� �� �������� ���� ���ݺδ� �������, �ǰݺδ� ��°���
    const bool ����ȿ������ = true;   // ���� �� �������� �� �������� ���� �ݿ�����
    
    //---------------------------------------------------------------------------------------
    
	class Main
	{
		Main()
		{
			pk::set_func(210, pk::func210_t(callback));
		}
        /*----------------------------------------
            ���� ���ط��� ����մϴ�.
            @param[out] damage	����� ����
            @param unit			�δ�
            @param tactics_id	#����Id
            @param target_pos	��ǥ ��ǥ
        ----------------------------------------*/
		void callback(pk::damage_info& info, pk::unit@ attacker, const pk::point &in target_pos)
		{
			int force_id = attacker.get_force_id();
			pk::force@ force = pk::get_force(force_id);
			int weapon_id = attacker.weapon;
			int command = func_5aee10(attacker);
			pk::unit@ target_unit = pk::get_unit(target_pos);
			pk::building@ target_building = pk::get_building(target_pos);
			int atk = attacker.attr.stat[�δ�ɷ�_����];
			int troops_atk = 0;
			int buffed = 0;

			if (pk::is_neighbor_pos(attacker.get_pos(), target_pos))
				troops_atk = 10;

			// ���ݷ� ��� ����
			if (func_5aed80(attacker.get_pos(), force_id))
			{
				buffed = 1;
				info.buffed = true;
			}

			// �����
			if (target_unit !is null)
			{
				pk::force@ target_force = pk::get_force(target_unit.get_force_id());
				int facility_id = �ü�_��;
				if (pk::has_tech(target_force, �ⱳ_�ü���ȭ))
					facility_id = �ü�_���;
				if (pk::has_tech(target_force, �ⱳ_������ȭ))
					facility_id = �ü�_��ä;
				if (func_5aedc0(target_unit.get_pos(), 1, pk::get_facility(facility_id).range, target_unit.get_force_id()))
					info.debuffer = facility_id;
			}

			float �����ⱳ_���ݷ� = 1.15f;
			float �ܷñⱳ_���ݷ� = 1.10f;

			// ũ��Ƽ��
			info.critical = false;

			if (target_unit !is null)
			{
				float troops_damage = func_5aee60(atk, command, troops_atk, buffed, target_unit.attr.stat[�δ�ɷ�_���], func_5aee10(target_unit));

				switch (weapon_id)
				{
				case ����_â:
					if (pk::has_tech(force, �ⱳ_����â��))
						troops_damage *= �����ⱳ_���ݷ�;
					else if (pk::has_tech(force, �ⱳ_â���ܷ�))
						troops_damage *= �ܷñⱳ_���ݷ�;
					break;

				case ����_��:
					if (pk::has_tech(force, �ⱳ_�����غ�))
						troops_damage *= �����ⱳ_���ݷ�;
					else if (pk::has_tech(force, �ⱳ_�غ��ܷ�))
						troops_damage *= �ܷñⱳ_���ݷ�;
					break;

				case ����_��:
					if (pk::has_tech(force, �ⱳ_�����뺴))
						troops_damage *= �����ⱳ_���ݷ�;
					else if (pk::has_tech(force, �ⱳ_�뺴�ܷ�))
						troops_damage *= �ܷñⱳ_���ݷ�;
					break;

				case ����_����:
					if (pk::has_tech(force, �ⱳ_�����⺴))
						troops_damage *= �����ⱳ_���ݷ�;
					else if (pk::has_tech(force, �ⱳ_�⺴�ܷ�))
						troops_damage *= �ܷñⱳ_���ݷ�;
					break;
				}

				info.troops_damage = int(troops_damage);
				if (func_5af230(info, attacker, target_unit, -1))
					troops_damage = 0;

                info.energy_damage = 0;
				if (attacker.has_skill(Ư��_����))
					info.energy_damage += pk::max(0, int(pk::core::skill_constant(attacker, Ư��_����))); // 5

				if (attacker.has_skill(Ư��_��ǳ))
					info.energy_damage += pk::max(0, int(pk::core::skill_constant(attacker, Ư��_��ǳ))); // 20

				info.food_damage = func_5aecc0(attacker, target_unit);  // â�� ���� ����
				info.food_heal = info.food_damage;

				if (attacker.is_player())
					troops_damage *= float(pk::core["������г�Ƽ"][pk::get_scenario().difficulty]);

				if (target_unit.has_skill(Ư��_�))
					troops_damage = troops_damage / 2;

				if (info.debuffer == �ü�_��)
					troops_damage *= 0.85f;
				else if (info.debuffer == �ü�_���)
					troops_damage *= 0.75f;
				else if (info.debuffer == �ü�_��ä)
					troops_damage *= 0.65f;
                
                
                if (!pk::is_campaign())
                {
                    // �δ� �� ���� �� ������ ���� ȿ�� �߰� ('18.10.11)
                    if (����ȿ������)
                    {
                        troops_damage = troops_damage * (1.f + func_terrain_buf(attacker)) * (1.f - func_terrain_buf(target_unit)); //���� ����
                        troops_damage = troops_damage * (1.f + 0.01f * get_height_diff(attacker.get_pos(), target_unit.get_pos())); //���� ������
                    }
                    
                    
                    // �δ밣 ���� �� ��ȣ ��� ���� �ݿ��� ('18.10.6)
                    if (���ȿ������)
                    {
                        // ���ݺδ� ��¿� ���� �ǰݺδ� ���� 85% ~ 115% ���� : �δ� ��� ȿ�� ('18.10.6)
                        troops_damage = troops_damage * (0.85f + 0.30f * (attacker.energy/120.f)) ;
                        // �ǰݺδ� ��¿� ���� �ǰݺδ� ���� 85% ~ 115% ���� : �δ� ��� ȿ�� ('18.10.6)
                        troops_damage = troops_damage * (0.85f + 0.30f * ((120 - target_unit.energy)/120.f)) ;
                    }
                    
                    
                    // ���� ���ط��� ���� �ǰݴ�� ��°���, ���ݺδ� ��»�� ȿ�� �߻�, �ݰݵ� ����� ('18.10.6)
                    if (�����������)
                    {
                        if (pk::is_enemy(attacker, target_unit))  // ���� �ٸ� ������ �δ밣 ���� �ÿ��� ���ȸ�� : ���� �跫 �� ���ȸ�� ���� ('18.10.22)
                        {
                            info.energy_heal = info.energy_heal + int(pk::min(15.f, (troops_damage / 200.f)));   //���� ������������ ���� ��� ������� ������ ����
                            
                            if (troops_damage >= 500)
                            {
                                info.energy_damage = info.energy_damage + int((troops_damage - 500) / 100.f);
                            
                                if (target_unit.has_skill(Ư��_ȣ��))  // Ư��_ȣ�� ���� �δ�� �������� �־ ��� ���� ���� ('18.10.14)
                                    info.energy_damage = 0;
                            }
                        }
                        else    // ����(�Ʊ����� ����) �� ���ȸ�� ����, ���������� ����Ͽ� ��� ������ �߻� ('18.10.25)
                        {
                            info.energy_damage = info.energy_damage + int((troops_damage / 100.f));
                        }
                    }
                }
                
				info.troops_damage = int(troops_damage);
                
			}
			else if (target_building !is null and pk::is_general_type(target_building))
			{
				pk::assert(false);
			}

			if (target_building !is null)
			{
				pk::assert(false);
			}

			// �ּ� ���� �����
			if (info.troops_damage != 0)
				info.troops_damage = int(pk::max(info.troops_damage / 2, pk::rand(100) + 200));

			// �ּ� ���� �����
			if (info.hp_damage != 0)
				info.hp_damage = int(pk::max(info.hp_damage / 2, pk::rand(10) + 20));

			info.src_pos = attacker.get_pos();
			info.dst_pos = target_pos;
			info.type = 3; // ?
		}

		/**
			ȹ�� ���� ���
		*/
		int func_5aecc0(pk::unit@ attacker, pk::unit@ target)
		{
			if (pk::is_alive(attacker) and pk::is_alive(target) and attacker.weapon == ����_â and attacker.has_tech(�ⱳ_��������))
			{
				int a = pk::rand(attacker.attr.stat[�δ�ɷ�_����]) + attacker.attr.stat[�δ�ɷ�_����];
				int b = pk::max(attacker.troops / 2, 1);
				int c = target.food;
				int d = pk::get_max_food(attacker) - attacker.food;
				return pk::min(a, b, c, d);
			}
			return 0;
		}

		/**
			���ݷ� ��� ȿ���� ���� �ü� �˻�
		*/
		bool func_5aed80(const pk::point &in pos, int force_id)
		{
			/*
			array<pk::point> range = pk::range(pos, 1, 3);
			for (int i = 0; i < range.length; i++)
			{
				pk::building@ building = pk::get_building(range[i]);
				if (pk::is_alive(building) and building.facility == �ü�_�°�� and building.completed and building.get_force_id() == force_id)
					return true;
			}
			return false;
			*/

			array<pk::point> range = pk::range(pos, 1, int(pk::core["�ü�.�ִ����"]));
			for (int i = 0; i < int(range.length); i++)
			{
				pk::building@ building = pk::get_building(range[i]);
				if (pk::is_alive(building) and building.completed and building.get_force_id() == force_id)
				{
					if (bool(pk::core["�ü�"][building.facility]["���ݷ»��"]) and pk::get_distance(pos, range[i]) <= int(pk::get_facility(building.facility).max_range))
						return true;
				}
			}
			return false;
		}

		/**
			��, ���, ��ä �˻�
		*/
		bool func_5aedc0(pk::point pos, int min, int max, int force_id)
		{
			auto range = pk::range(pos, min, max);
			for (int i = 0; i < int(range.length); i++)
			{
				pk::building@ building = pk::get_building(range[i]);
				if (pk::is_alive(building) and (building.facility == �ü�_�� or building.facility == �ü�_��� or building.facility == �ü�_��ä) and building.completed and building.get_force_id() == force_id)
					return true;
			}
			return false;
		}

		/**
			���� ������ ���� ��
		*/
		int func_5aee10(pk::unit@ unit)
		{
			pk::person@ leader = pk::get_person(unit.leader);
			if (pk::is_alive(leader))
				return pk::min(pk::get_command(leader), unit.troops);
			return unit.troops;
		}

		/** �δ�/���� ���� ���� ��� **/
		float func_5aee60(int src_atk, int src_troops, int tactics_atk, int buffed, int dst_def, int dst_troops)
		{
			float n = 0;
			int a = 0;
			int b = 0;
			int c = 0;

			a = pk::max(src_atk, 40);
			a = a * a;

			b = pk::max(dst_def, 40);
			b = b * b;

			//n = pk::sqrt(tactics_atk * 64);
			n = sqrt(tactics_atk * 64);
			n = n + pk::max((src_troops - dst_troops) / 2000, 0);
			n = n + pk::max((a - b) / 300, 0);
			n = n + 50;
			n = n * (buffed + 10);

			a = (src_troops / 100 + 300) * (src_atk + 50) * (src_atk + 50) / 100;
			b = (dst_troops / 100 + 300) * (dst_def + 50) * (dst_def + 50) / 100;
			c = a + b;
			if (a >= b)
				c = a * 100 / c;
			else
				c = pk::max(100 - (b * 100 / c), 1);
			n = n * c;

			a = pk::max(src_troops / 4, 1);
			n = n * pk::min(sqrt(a), 40.f);

			n = n / 2100;
			n = n + src_troops / 200;

			return n;
		}

		/** �δ� ���ⱳ �� ���Ư�� ȿ�� �ݿ� **/
		bool func_5af230(pk::damage_info& info, pk::unit@ attacker, pk::unit@ target, int tactics_id)
		{
			if (pk::is_valid_tactics_id(tactics_id))
				return false;

			pk::point attacker_pos = attacker.get_pos();
			pk::point target_pos = target.get_pos();

			if (target.weapon == ����_��)
			{
				if (target.has_tech(�ⱳ_ȭ�����))
				{
					if (!pk::is_neighbor_pos(attacker_pos, target_pos) and pk::rand_bool(30))
					{
						info.def_tech = �ⱳ_ȭ�����;
						return true;
					}
				}
				if (target.has_tech(�ⱳ_ū����))
				{
					if (pk::is_neighbor_pos(attacker_pos, target_pos) and pk::rand_bool(30))
					{
						info.def_tech = �ⱳ_ū����;
						return true;
					}
				}
			}

			if (target.has_skill(Ư��_�ұ�))
			{
				if (int(target.troops) < int(pk::core::skill_constant(target, Ư��_�ұ�)) and pk::rand_bool(int(pk::core::skill_constant(target, Ư��_�ұ�, 1))))
				{
					info.def_skill = Ư��_�ұ�;
					return true;
				}
			}

			if (target.has_skill(Ư��_�ݰ�))
			{
				if (info.troops_damage < int(pk::core::skill_constant(target, Ư��_�ݰ�)) and pk::rand_bool(int(pk::core::skill_constant(target, Ư��_�ݰ�, 1))))
				{
					info.def_skill = Ư��_�ݰ�;
					return true;
				}
			}

			return false;
		}
        
        
        
        // --------------------------------------------------------
        
        
        // --------------------------------------------------------
        // �δ� �� ���� �� ������ ���� ������ ����Ƽ�� �߰� ('18.10.11)
        float func_terrain_buf(pk::unit @ unit)
        {
            int weapon_id = unit.weapon;
            float terrain_buf = 0.f;
            pk::hex@ unit_hex = pk::get_hex(unit.get_pos());    // �δ��� ��ǥ
            switch (unit_hex.terrain)                           // ��ǥ�� ����
            {
                case ����_�ʿ�  : 
                                if (weapon_id == ����_â)
                                    terrain_buf = 0.05f;
                                else if (weapon_id == ����_����)
                                    terrain_buf = 0.10f;
                                break;
                case ����_��  :    
                                if (weapon_id == ����_â)
                                    terrain_buf = 0.05f;
                                else if (weapon_id == ����_��)
                                    terrain_buf = 0.05f;
                                else if (weapon_id == ����_����)
                                    terrain_buf = 0.05f;
                                break;
                case ����_��  : 
                                if (weapon_id == ����_â)
                                    terrain_buf = 0.05f;
                                else if (weapon_id == ����_����)
                                    terrain_buf = 0.05f;
                                break;
                case ����_����  : 
                                if (weapon_id == ����_â)
                                    terrain_buf = -0.05f;
                                else if (weapon_id == ����_��)
                                    terrain_buf = 0.10f;
                                else if (weapon_id == ����_��)
                                    terrain_buf = -0.05f;
                                else if (weapon_id == ����_����)
                                    terrain_buf = -0.10f;
                                break;
                case ����_��õ  : 
                                if (weapon_id == ����_â)
                                    terrain_buf = -0.10f;
                                else if (weapon_id == ����_��)
                                    terrain_buf = 0.05f;
                                else if (weapon_id == ����_��)
                                    terrain_buf = -0.10f;
                                else if (weapon_id == ����_����)
                                    terrain_buf = -0.15f;
                                break;
                case ����_��   : 
                                if (weapon_id == ����_â)
                                    terrain_buf = 0.10f;
                                else if (weapon_id == ����_��)
                                    terrain_buf = 0.05f;
                                else if (weapon_id == ����_��)
                                    terrain_buf = 0.15f;
                                else if (weapon_id == ����_����)
                                    terrain_buf = -0.10f;
                                break;
                case ����_Ȳ����:  
                                if (weapon_id == ����_â)
                                    terrain_buf = -0.05f;
                                else if (weapon_id == ����_����)
                                    terrain_buf = 0.05f;
                                break;
                case ����_���  : 
                                if (weapon_id == ����_â)
                                    terrain_buf = 0.05f;
                                else if (weapon_id == ����_��)
                                    terrain_buf = 0.05f;
                                else if (weapon_id == ����_��)
                                    terrain_buf = 0.05f;
                                else if (weapon_id == ����_����)
                                    terrain_buf = 0.05f;
                                break;
            }
            
            // Ư��_�ź� �����δ�� ���� ������� ��/��/���濡�� 15% �߰� ����Ƽ�� ('18.10.14)
            if (unit.has_skill(Ư��_�ź�) and (unit_hex.terrain == ����_�� or unit_hex.terrain == ����_�� or unit_hex.terrain == ����_���� ) )
                terrain_buf += 0.15f;
            // Ư��_�ص� �����δ�� ���� ������� ��õ���� 15% �߰� ����Ƽ�� ('18.10.17)
            else if (unit.has_skill(Ư��_�ص�) and (unit_hex.terrain == ����_��õ) )
                terrain_buf += 0.15f;
            // Ư��_���� �����δ�� ���� ������� ��õ���� 15% �߰� ����Ƽ�� ('18.10.17)
            else if (unit.has_skill(Ư��_����) and (unit_hex.terrain == ����_������ or unit_hex.terrain == ����_�� or unit_hex.terrain == ����_����) )
                terrain_buf += 0.15f;
            
            return terrain_buf;
        }
        
        
        // �δ밣 ���� ������ ('18.10.14)
        int get_height_diff(const pk::point &in src, const pk::point &in dst)
		{
			return pk::get_height_map(pk::hex_pos_to_height_map_pos(src) + 2).height - pk::get_height_map(pk::hex_pos_to_height_map_pos(dst) + 2).height;
		}
        
        
        
	}

	Main main;
}