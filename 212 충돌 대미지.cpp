namespace �浹_�����
{
	class Main
	{
		Main()
		{
			pk::set_func(212, pk::func212_t(callback));
		}

		void callback(pk::damage_info& info, pk::unit@ attacker, pk::hex_object@ sub_target)
		{
			int n = 0;

			// ?
			n = pk::rand(attacker.attr.stat[�δ�ɷ�_����]) + attacker.attr.stat[�δ�ɷ�_����] / 2;
			info._20 = -pk::max(n, 1);

			if (sub_target.is_instance(pk::unit::type_id))
			{
				n = attacker.attr.stat[�δ�ɷ�_����] * 2 - pk::hex_object_to_unit(sub_target).attr.stat[�δ�ɷ�_���];
				if (n < 20) n = 20;
				info.troops_damage = pk::max(n + pk::rand(n), 1);
                
                // ����/�ǰݺδ� ���� ���� ���� �߰� ȿ�� : �������� 5% �̳� ���� ('18.10.14)
                if (attacker.troops >= pk::hex_object_to_unit(sub_target).troops)
                    info.troops_damage += pk::max(pk::rand( (attacker.troops - pk::hex_object_to_unit(sub_target).troops)/20 ), 0);
                    
			}
			else
			{
				pk::building@ building = pk::hex_object_to_building(sub_target);
				if (!pk::is_trap_type(building))
				{
					n = attacker.attr.stat[�δ�ɷ�_����] + pk::rand(attacker.attr.stat[�δ�ɷ�_����] / 2);
					n = n / 2;
					info.hp_damage = pk::max(n, 1);
				}
				else if (building.facility == �ü�_���� and !building.completed)
				{
					info.hp_damage = 0;
				}
			}

			info.tactics = -1;
			info.src_pos = attacker.get_pos();
			info.dst_pos = sub_target.get_pos();
		}
	}

	Main main;
}