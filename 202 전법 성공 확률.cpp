namespace ����_����_Ȯ��
{
	class Main
	{
		Main()
		{
			pk::set_func(202, pk::func202_t(callback));
		}

		int callback(pk::unit@ attacker, const pk::point &in pos, pk::hex_object@ target, int tactics_id)
		{
            pk::unit @ target_unit = pk::hex_object_to_unit(target);
            
			if (target.is_instance(pk::unit::type_id) and target_unit.status != �δ����_���)
				return 100;
            
			int n = 0;
			pk::point temp;

			// if (pk::get_tekisei(attacker) == ����_A) n = 5; else if (pk::get_tekisei(attacker) == ����_S) n = 10;
			n = int(pk::core["����"][pk::get_tekisei(attacker)]["��������Ȯ��"]) + pk::core::tactics_chance(attacker.leader);
            
            
            
			switch (tactics_id)
			{
			case ����_����:
                n = n + push_bonus(get_height_diff(attacker.get_pos(), target.get_pos())) + 70;
				break;
            case ����_�̴�÷:
                n = n + push_bonus(get_height_diff(attacker.get_pos(), target.get_pos())) + 65;
				temp = pk::get_neighbor_pos(target.get_pos(), pk::get_direction(attacker.get_pos(), target.get_pos()));
				n = n + cutoff_diff(get_height_diff(target.get_pos(), temp));
				break;
			case ����_����÷:
				n = n + push_bonus(get_height_diff(attacker.get_pos(), target.get_pos())) + 60;
				break;

                
			case ����_����:
				n = n + pull_bonus(get_height_diff(attacker.get_pos(), target.get_pos())) + 70;
				temp = pk::get_neighbor_pos(attacker.get_pos(), pk::get_direction(target.get_pos(), attacker.get_pos()));
				n = n + cutoff_diff(get_height_diff(attacker.get_pos(), temp));
				break;
			case ����_Ⱦġ:
            case ����_��ǳ:
            
            
			case ����_ȭ��:
				n = n + hiya_terrain_bonus(pk::get_hex(target.get_pos()).terrain) + 75;
				break;
			case ����_����:
				n = n + 70;
				break;
            case ����_����:
                
                
            case ����_����:
				n = n + push_bonus(get_height_diff(attacker.get_pos(), target.get_pos())) + 70;
				break;
			case ����_����:
				n = n + push_bonus(get_height_diff(attacker.get_pos(), target.get_pos())) + 65;
				temp = pk::get_neighbor_pos(target.get_pos(), pk::get_direction(attacker.get_pos(), target.get_pos()));
				n = n + cutoff_diff(get_height_diff(target.get_pos(), temp));
				break;
			case ����_����:
				n = n + push_bonus(get_height_diff(attacker.get_pos(), target.get_pos())) + 60;
				break;
			
			
			case ����_�Լ��ݵ�:
				n = n + 65;
				break;

			default:        // ���� ���� ���� ������ = 100%
				return 100;
			}
            
            // ���ݺδ� ���¼��� ���� ���� ������ ���� ('18.10.13)
            if (attacker.troops <= 1000)
                n = int(n * pk::max(0.1f, attacker.troops/1000.f));         // �Һδ� �� ���������� 1/10�� ���� ����
            
            
            // ����/�ǰ� �δ��� Ư�� ������ ���� ���� ������ ���� ('18.10.18)
            if (target.is_instance(pk::unit::type_id) and target_unit.status == �δ����_��� and pk::is_valid_tactics_id(tactics_id))
            {
                // ���ݺδ밡 ���� Ư�� ���� �� ���� ������ �ּ� 80% 
                if (attacker.has_skill(Ư��_����) )
                    return pk::max(80, n);  
                // �ǰݺδ밡 ���� Ư�� ���� �� ���� ������ �ִ� 50% : �������� ���� �� �������� �Ǳ� ?���� �ұ�/�ݰ�ó�� ���� Ȯ���� ȸ���ϴ� �Ͱ��� �ٸ� 
                if (target_unit.has_skill(Ư��_����) )
                    return pk::min(50, n);
                // ���ݺδ밡 ���� Ư�� ���� �� ���� ������ 10% �߰�
                if (attacker.has_skill(Ư��_����) )
                    return pk::min(100, n + 10); 
            }
            
                
			return n;
		}

        
        
        
        
		// 5af5b0
		int get_height_diff(const pk::point &in src, const pk::point &in dst)
		{
			return pk::get_height_map(pk::hex_pos_to_height_map_pos(src) + 2).height - pk::get_height_map(pk::hex_pos_to_height_map_pos(dst) + 2).height;
		}

		// 5af6b0
		int push_bonus(int n)
		{
			return cutoff_diff(n) + 5;
		}

		// 5af6f0
		int pull_bonus(int n)
		{
			return 5 - cutoff_diff(n);
		}
        

		// 5af680
		int cutoff_diff(int n)
		{
			// ��뺸�� ����
			if (n >= 10)
				return 10;
			// ��뺸�� ����
			else if (n >= 5)
				return 5;
			// ����
			else if (n >= -5)
				return 0;
			// ��뺸�� ����
			else if (n >= -10)
				return -5;
			// ��뺸�� ����
			else
				return -10;
		}
        

		// 849ae0 ������ ���� ȭ�� Ȯ�� ���ʽ�
		int hiya_terrain_bonus(int terrain)
		{
			switch (terrain)
			{
			case ����_��: return -5;
			case ����_��: return -5;
			case ����_����: return -15;
			case ����_��õ: return -15;
			case ����_��: return 10;
			case ����_��: return -10;
			case ����_��: return -10;
			case ����_�ٴ�: return -10;
			case ����_����: return -10;
			case ����_����: return -5;
			}
			return 0;
		}
        
        
	}

	Main main;
}