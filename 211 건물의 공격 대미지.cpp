namespace �ǹ���_����_�����
{
    
    //---------------------------------------------------------------------------------------
    // ���� ���� (true = on, false = off)
    const bool ���ȿ������ = true;   // ��¿� ����Ͽ� ������ ���� ���� ȿ��
    const bool ����������� = true;   // ���� �� �������� ���� ���ݺδ� �������, �ǰݺδ� ��°���
    const bool �����ɷ��ջ� = true;   // true: ���� �� ������� �ɷ�ġ �ջ� ��� ����, false: ����ó�� �¼� �ɷ¸� ����
    
    const float ��������� = 0.8f;   // ��ü���� ��������� ������ ����
    
    //---------------------------------------------------------------------------------------
    
    
	class Main
	{
        
		Main()
		{
			pk::set_func(211, pk::func211_t(callback));
            
		}
        /*----------------------------------------
            �ǹ��� ����(�ݰ�) �� ���� ������� ����մϴ�.
            @param[out] damage	����� ����
            @param building		�ǹ�
            @param target		��ǥ
        ----------------------------------------*/
		void callback(pk::damage_info& info, pk::building@ attacker, pk::hex_object@ target)
		{
			// ������� ����
			if (target.is_instance(pk::building::type_id))
				pk::assert(false);

			int facility_id = attacker.facility;
			pk::unit@ target_unit = pk::hex_object_to_unit(target);
			int troops_atk = 0, atk = 0, def = 0, troops = 0;

			switch (facility_id)
			{
			case �ü�_����:
			case �ü�_����:
			case �ü�_�ױ�:
				func_5af0e0(troops_atk, atk, def, troops, attacker);
				info.troops_damage = int(func_5aee60(atk, troops, troops_atk, 0, target_unit.attr.stat[�δ�ɷ�_���], func_5aee10(target_unit)) * 0.8f);
				if (pk::equipment_id_to_heishu(target_unit.weapon) == ����_����)
					info.troops_damage = int(info.troops_damage * 0.8f);
				break;

			case �ü�_��:
			case �ü�_���:
			case �ü�_��ä:
			case �ü�_�ó�:
			case �ü�_�����:
			case �ü�_������:
				info.troops_damage = func_5af370(attacker, target_unit);
				if (pk::equipment_id_to_heishu(target_unit.weapon) == ����_���� and attacker.facility != �ü�_������)
					info.troops_damage = int(info.troops_damage * 0.8f);
				break;

			default:
				// �ü�.�ڵ����� �����
				info.troops_damage = func_5af370(attacker, target_unit);
				if (pk::equipment_id_to_heishu(target_unit.weapon) == ����_����)
					info.troops_damage = int(info.troops_damage * 0.8f);
				break;
			}

			if (attacker.is_player())
				info.troops_damage = int(info.troops_damage * float(pk::core["������г�Ƽ"][pk::get_scenario().difficulty]));

			// ��ȭ �ⱳ ���� �� ��, ����, �ױ�, ��, ���, ��ä�� ���ݷ� 2��
			if (attacker.has_tech(�ⱳ_��ȭ) and attacker.facility >= �ü�_���� and attacker.facility <= �ü�_��ä)
				info.troops_damage *= 2;
            
            
            if (!pk::is_campaign())
            {
                // �ǹ���δ� �� ��ȣ ��� ���� �ݿ��� ('18.10.7)
                if (���ȿ������)
                {
                    // ���ݺδ� ��¿� ���� �ǰݴ�� ���� 85% ~ 115% ���� : �δ� ��� ȿ�� ('18.10.7)
                    info.troops_damage = int(info.troops_damage * (0.85f + 0.30f * (attacker.energy/120.f))) ;
                    // �ǰݴ�� ��¿� ���� �ǰݴ�� ���� 85% ~ 115% ���� : �δ� ��� ȿ�� ('18.10.7)
                    info.troops_damage = int(info.troops_damage * (0.85f + 0.30f * ((120 - target_unit.energy)/120.f))) ;
                }
                
                // ��ü���� �⺻ ������� ���� ���� ('18.12.15)
                info.troops_damage = int(info.troops_damage * ���������);
                
                // ���� ���ط��� ���� �ǰݴ�� ��°���, ������ ��»�� ȿ�� �߻� ('18.10.7) 
                if (�����������)
                {
                    int energy_heal = int(info.troops_damage / 200);
                    //pk::add_energy(attacker, +energy_heal, true );   // �뷱�� �׽�Ʈ �ʿ�
                
                    if (info.troops_damage >= 300)
                        info.energy_damage = int((info.troops_damage - 300) / 100);
                }
            }
            
			info.src_pos = attacker.get_pos();
			info.dst_pos = target.get_pos();
            
            
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

		/** �¼��� ����鿡 ���� ������ �����ɷ� **/
		void func_5af0e0(int &out src_atk, int &out dst_atk, int &out dst_def, int &out dst_troops, pk::building@ building)
		{
			src_atk = 10;
			pk::person@ taishu = pk::get_person(pk::get_taishu_id(building));
			if (pk::is_alive(taishu))
			{
                //�¼� �ɷ� �ݿ� (�⺻)
				dst_atk = pk::max(taishu.stat[����ɷ�_����] - 25, 40);
				dst_def = pk::max(taishu.stat[����ɷ�_���] - 25, 40);
				dst_troops = pk::min(pk::get_troops(building), pk::get_command(taishu));
                
                //���� �� "�ź�_�Ϲ�" �� ���� �ɷ� �ݿ� (�� ������ ����, ���, ���� �κ� �ջ�) ('18.10.7)
                if (�����ɷ��ջ�)
                {
                    float ilban_help = 5;    // �¼� �� ���� �ɷ� ġ �ջ� ������ : ���庰 5%
                    auto ilban_list = pk::list_to_array(pk::get_person_list(building, pk::mibun_flags(�ź�_�Ϲ�) ) );
                    if (0 < int(ilban_list.length))
                    {
                        for (int i = 0; i < int(ilban_list.length); i++)
                        {
                            pk::person@ ilban = ilban_list[i];
                            //���� �Ǵ� ������ ���°� �ƴ� ����̸�, �¼��� ���� ���谡 �ƴ� ����� �ɷ� ġ �ջ�
                            if (!pk::is_unitize(ilban) and !pk::is_absent(ilban) and !pk::is_dislike(taishu, ilban.get_id()) and !pk::is_dislike(ilban, taishu.get_id()) )
                            {
                                dst_atk += int((pk::max(ilban.stat[����ɷ�_����] - 25, 20)) * (ilban_help / 100.f));
                                dst_def += int((pk::max(ilban.stat[����ɷ�_���] - 25, 20)) * (ilban_help / 100.f));
                                dst_troops += int((pk::min(pk::get_troops(building), pk::get_command(ilban))) * (ilban_help / 100.f));
                            }
                        }
                    }
                }
			}
			else
			{
				dst_atk = 30;
				dst_def = 30;
				//dst_troops = pk::min(pk::get_troops(building), 7000);
				dst_troops = pk::min(pk::get_troops(building), 5000);  // ���ֺ��� ����ġ ����
				if (dst_troops != 0)
					dst_troops = pk::max(dst_troops, 500);
			}
		}

		/**
			����ü��� ���ݷ� ���
		*/
		int func_5af370(pk::building@ attacker, pk::unit@ target)
		{
			int atk = 0;
			int bonus = 0;

			switch (attacker.facility)
			{
			case �ü�_����:     // ������ ���� : ���� �������� ���� ('18.10.14)
                atk = 200;
				bonus = 200;
				break;
			case �ü�_����:     // ����� ���� : ���� �������� ���� ('18.10.14)
                atk = 400;
				bonus = 400;
				break;
			case �ü�_�ױ�:     // ������ ���� : ���� �������� ���� ('18.10.14)
                atk = 200;
				bonus = 200;
				break;
            case �ü�_��:
				atk = 400;
				bonus = 300;
				break;
			case �ü�_���:
				atk = 600;
				bonus = 300;
				break;
			case �ü�_��ä:
				atk = 800;
				bonus = 300;
				break;
			case �ü�_�ó�:
				atk = 300;
				bonus = 300;
				break;
			case �ü�_�����:
				atk = 500;
				bonus = 400;
				break;
			case �ü�_������:
				atk = 900;
				bonus = 600;
				break;
			default:
				// ��Ÿ�ü�.�ڵ����� �����
				atk = 300;
				bonus = 300;
				break;
			}
			
			float max_hp = pk::max(pk::get_max_hp(attacker), 1);
			float hp = pk::max(attacker.hp, max_hp / 2);

			return int(hp / max_hp * (152 - int(target.attr.stat[�δ�ɷ�_���])) * atk / 132 + pk::rand(bonus));
		}
        
        
	}

	Main main;
}