namespace ����_�����
{
	class Main
	{
		Main()
		{
			pk::set_func(215, pk::func215_t(callback));
		}

		void callback(pk::damage_info& info, pk::unit@ attacker, pk::hex_object@ target, bool critical)
		{
			if (target.is_instance(pk::unit::type_id))
			{
				info.troops_damage = 1500 + pk::rand(1000);
                
                //���� ������ 2% ��ŭ ��°��� ('18.10.11)
                info.energy_damage = info.troops_damage / 50;
			}
			else
			{
				info.hp_damage = 700 + pk::rand(300);
				// ȸ������ ������ ��� ��ȿ
				pk::building@ building = pk::hex_object_to_building(target);
				if (building.facility == �ü�_���� and !building.completed)
					info.hp_damage = 0;
			}

			info.tactics = -1;
			info.src_pos = attacker.get_pos();
			info.dst_pos = target.get_pos();
		}
	}

	Main main;
}