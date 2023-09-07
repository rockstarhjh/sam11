/*
@������: �⸶å��
@Update: '20.8.29   / ���泻��: ���� ���ü� �г�Ƽ �߰�, ķ���ο����� Ŀ���� ���� ��� �Ұ�
*/


namespace ����_����
{
    
    //---------------------------------------------------------------------------------------
    // ���� ���� (true = on, false = off)
    const bool  ����_���ü�_�г�Ƽ = true;     // �������¿� ���ؼ� ���ü��� ����Ͽ� ���� ����� (���ô� 5% ����)
    
    //---------------------------------------------------------------------------------------
    
    
	class Main
	{
		Main()
		{
			pk::set_func(151, pk::func151_t(callback));
		}

		int callback(pk::city@ city)
		{
			if (city is null or !pk::is_valid_force_id(city.get_force_id()))
				return 0;

			// �⺻ ���� ����
			int n = city.harvest;

			for (auto i = 0; i < city.max_devs; i++)
			{
				pk::building@ building = city.dev[i].building;
				int facility_id = -1;

				if (pk::is_alive(building))
				{
					facility_id = building.facility;
					switch (facility_id)
					{
					case �ü�_����:
					case �ü�_���г�:
						if (!building.completed)
							continue;
						break;
					case �ü�_����2��:
						if (!building.completed)
							facility_id = �ü�_����;
						break;
					case �ü�_����3��:
						if (!building.completed)
							facility_id = �ü�_����2��;
						break;
					default:
						continue;
					}
				}

				// �����ü� �� ������� ����.
				pk::facility@ facility = pk::get_facility(facility_id);
				if (pk::is_alive(facility))
				{
					int y = facility.yield;
					// ������ ��â�� ������ ��� 1.5��.
					if (facility_id == �ü�_���� or facility_id == �ü�_����2�� or facility_id == �ü�_����3��)
					{
						if (func_49ed70(building.get_pos(), �ü�_��â))
							y = int(y * 1.5f);
					}
					// ���г��� ��� ���¼��� ����Ͽ� ����� ����.
					else if (facility_id == �ü�_���г�)
					{
						y = int(pk::max(city.troops, 15000) * y / 15000);
					}
					n = n + y;
				}
			}

			switch (pk::get_scenario().difficulty)
			{
			case ���̵�_Ư��:
				// Ư���� ��� �÷��̾� 0.75��, ��ǻ�� 1.25��.
				if (city.is_player())
					n = int(n * 0.75f);
				else
					n = int(n * 1.25f);
				break;

			case ���̵�_�ʱ�:
				// �ʱ��� ��� �÷��̾�, ��ǻ�� ��� 1.25��.
				n = int(n * 1.25f);
				break;
			}

			// ���� ġ�Ȱ��� ������� ��.
			n = int(n * pk::max(city.public_order, 50) / 100);
			
            /* ���� ����
			// ���ְ� [����]�� ��쿡 1.25��
			if (pk::get_kunshu_id(city) == ����_����)
				n *= 1.25f;
			
			// ���ְ� [���]�� ��쿡 1.45��
			if (pk::get_kunshu_id(city) == ����_���)
				n *= 1.45f;
            */
            

            // ����_���ü�_�г�Ƽ ('20.8.29)
            if (����_���ü�_�г�Ƽ and city.is_player() and !pk::is_campaign())
            {
                pk::force@ force = pk::get_force(city.get_force_id());
                float force_city_count = float(pk::get_city_list(force).count);
                n = int(n * (1.f - (force_city_count * 0.05f)));
            }
            
			return n;
		}

		/**
			���� �ü� �˻�.
		*/
		bool func_49ed70(pk::point pos, int facility_id)
		{
			for (int i = 0; i < ����_��; i++)
			{
				pk::point neighbor_pos = pk::get_neighbor_pos(pos, i);
				if (pk::is_valid_pos(neighbor_pos))
				{
					pk::building@ building = pk::get_building(neighbor_pos);
					if (pk::is_alive(building) and building.facility == facility_id and building.completed)
						return true;
				}
			}
			return false;
		}
	}

	Main main;
}