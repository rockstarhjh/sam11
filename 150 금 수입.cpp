/*
@������: �⸶å��
@Update: '18.12.22  / ���泻��: �������� ��ũ��Ʈ �и�
@Update: '20.8.25   / ���泻��: �������������� ������������ �ɼǺи�
@Update: '20.8.29   / ���泻��: ���� ���ü� �г�Ƽ �߰�, ķ���ο����� Ŀ���� ���� ��� �Ұ�
*/


namespace ��_����
{
    
    //---------------------------------------------------------------------------------------
    // ���� ���� (true = on, false = off)
    const bool  ������������ = false;         // ���� �������� ����Ͽ� �� �Һ�, �� ���� �� ���� ����
    const int   ���������ñ� = 1;               // �����������1 �Ǵ� ���2 ��� �� (0: ����,  1: �ſ� 1�� )
    
    const bool  �����_��������_��� = true;    // �����������1 (������ true ��� �� Ȱ��ȭ : �ݺ��� �� ���⸦ ��� ����)
    const float �����_��������_���� = 2.5f;    // �����������1 Ȱ��ȭ �� ���� ��������
    
    const bool  �����ʰ�_��������_��� = true;    // �����������2 (������ false ��� �� Ȱ��ȭ : �� �Һ� ���� ���º��� ���� ���⿡ ���ؼ� ���� ���� ����)
    const float �����ʰ�_��������_���� = 0.01f;   // �����������2 Ȱ��ȭ �� ���� ��������
    
    const bool  ����_���ü�_�г�Ƽ = true;     // �������¿� ���ؼ� ���ü��� ����Ͽ� ���� ����� (���ô� 5% ����)
    
    //---------------------------------------------------------------------------------------
    
	class Main
	{
		Main()
		{
			pk::set_func(150, pk::func150_t(callback));
            
            pk::bind(111, pk::trigger111_t(onTurnStart));
		}

		int callback(pk::city@ city)
		{
			if (city is null or !pk::is_valid_force_id(city.get_force_id()))
				return 0;

			// �⺻ �� ����
			int n = city.revenue;

			for (int i = 0; i < city.max_devs; i++)
			{
				pk::building@ building = city.dev[i].building;
				int facility_id = -1;

				if (pk::is_alive(building))
				{
					facility_id = building.facility;
					switch (facility_id)
					{
					case �ü�_����:
					case �ü�_�����:
					case �ü�_�����:
					case �ü�_�Ͻ���:
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
					// ������ ����� ������ ��� 1.5��.
					if (facility_id == �ü�_���� or facility_id == �ü�_����2�� or facility_id == �ü�_����3��)
					{
						if (func_49ed70(building.get_pos(), �ü�_����))
							y = int(y * 1.5f);
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
			n = n * pk::max(city.public_order, 50) / 100;
            
            // ����_���ü�_�г�Ƽ ('20.8.29)
            if (����_���ü�_�г�Ƽ and city.is_player() and !pk::is_campaign())
            {
                pk::force@ force = pk::get_force(city.get_force_id());
                float force_city_count = float(pk::get_city_list(force).count);
                n = int(n * (1.f - (force_city_count * 0.05f)));
            }
            
            //-------------------------------------------------------------------
            // ���� �� ���� �������� ���� �ݼ��� ���� ���� : ���� ������ ���� ('18.10.14)
            
            if (������������ and !pk::is_campaign())
            {
                
                n = int(n * 1.2f); // ���� �������� ���� ���� ���Ҹ� �����Ͽ� �⺻ ���� 20% ���� ����
                
                pk::building @ m_city = pk::city_to_building(city);
                
                float rich_rate = pk::is_valid_person_id(m_city.who_has_skill(Ư��_��ȣ))? 1.5f : 1.0f;  // �Ϲ�=1.0  Ư���ȣ=1.5 ��ȯ
                
                // �Ϲݺ��� ������ ����, ���� ���� �� ���� ��� ���� ������ ����
                int weapon_qty1 = pk::get_weapon_amount(m_city, ����_â);
                int weapon_qty2 = pk::get_weapon_amount(m_city, ����_��);
                int weapon_qty3 = pk::get_weapon_amount(m_city, ����_��);
                int weapon_qty4 = pk::get_weapon_amount(m_city, ����_����);
                int weapon_sum = pk::max(1, weapon_qty1 + weapon_qty2 + weapon_qty3 + weapon_qty4);
                
                int weapon_pay = int(0.010f * weapon_sum / rich_rate);
                int gold_estimate = pk::get_gold(m_city) + n;
                
                n = n - weapon_pay;
                
                /*
                if (gold_estimate > weapon_pay) // ������ + ���� ���� �� ������ ����
                    n = n - weapon_pay;
                else                            // ������ + ���� ���� �� ���׿� ����Ͽ� ���� ���� �յ� ����
                {
                    n = -pk::get_gold(m_city);
                    
                    pk::add_weapon_amount(m_city, ����_â,  int((gold_estimate - weapon_pay)* 2.5f * weapon_qty1 / weapon_sum), true );
                    pk::add_weapon_amount(m_city, ����_��,  int((gold_estimate - weapon_pay)* 2.5f * weapon_qty2 / weapon_sum), true );
                    pk::add_weapon_amount(m_city, ����_��,  int((gold_estimate - weapon_pay)* 2.5f * weapon_qty3 / weapon_sum), true );
                    pk::add_weapon_amount(m_city, ����_����, int((gold_estimate - weapon_pay)* 2.5f * weapon_qty4 / weapon_sum), true );
                }
                */
                
                // �������� �� ������ ������ ������ ���� 
                n = n - int(15.f*(pk::get_weapon_amount(m_city, ����_����))/rich_rate);
                n = n - int(15.f*(pk::get_weapon_amount(m_city, ����_����))/rich_rate);
                n = n - int(20.f*(pk::get_weapon_amount(m_city, ����_���))/rich_rate);
                n = n - int(25.f*(pk::get_weapon_amount(m_city, ����_����))/rich_rate);
                n = n - int(20.f*(pk::get_weapon_amount(m_city, ����_����))/rich_rate);
                n = n - int(25.f*(pk::get_weapon_amount(m_city, ����_����))/rich_rate);
                
            }
            
            //-------------------------------------------------------------------
            
            
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
        
        
        
        
        
        //---------------------------------------------------------------------------------------
        
        void onTurnStart(pk::force@ force)
		{
            if(pk::is_campaign()) return;
            
            float maintenance_period = -1.0f;
            if (���������ñ� == 0)   
                maintenance_period = 1/3.f;  // ����
            else if (���������ñ� == 1 and (pk::get_day() == 1))    
                maintenance_period = 1.0f;   // �ſ� 1��
            
            
            if ((�����_��������_��� or �����ʰ�_��������_���) and maintenance_period > 0.f)
            {
                for (int i = �ǹ�_���ý���; i < �ǹ�_���ó�; i++)
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
            
            // �Ϲݺ��� ������ ����, ���� ���� �� ���� ��� ���� ������ ����
            int weapon_qty1 = pk::get_weapon_amount(building, ����_â);
            int weapon_qty2 = pk::get_weapon_amount(building, ����_��);
            int weapon_qty3 = pk::get_weapon_amount(building, ����_��);
            int weapon_qty4 = pk::get_weapon_amount(building, ����_����);
            int weapon_sum = pk::max(1, weapon_qty1 + weapon_qty2 + weapon_qty3 + weapon_qty4);
            
            int weapon_pay = int(0.010f * weapon_sum / rich_rate);
            int gold_estimate = pk::get_gold(building);
            int troops = pk::get_troops(building);
            
            if ((������������ and �����_��������_���) and gold_estimate <= weapon_pay) // ������ + ���� ���� �� ������ ����
            {
                pk::add_weapon_amount(building, ����_â,  int((gold_estimate - weapon_pay)* �����_��������_���� * weapon_qty1 / weapon_sum * ratio), true );
                pk::add_weapon_amount(building, ����_��,  int((gold_estimate - weapon_pay)* �����_��������_���� * weapon_qty2 / weapon_sum * ratio), true );
                pk::add_weapon_amount(building, ����_��,  int((gold_estimate - weapon_pay)* �����_��������_���� * weapon_qty3 / weapon_sum * ratio), true );
                pk::add_weapon_amount(building, ����_����, int((gold_estimate - weapon_pay)* �����_��������_���� * weapon_qty4 / weapon_sum * ratio), true );
            }
            else if ((!������������ and �����ʰ�_��������_���) and troops <= weapon_sum) // ���º��� ���� ���⿡ ���ؼ� �������� ���� ����
            {
                pk::add_weapon_amount(building, ����_â,  int((troops - weapon_sum)* �����ʰ�_��������_���� * weapon_qty1 / weapon_sum * ratio), true );
                pk::add_weapon_amount(building, ����_��,  int((troops - weapon_sum)* �����ʰ�_��������_���� * weapon_qty2 / weapon_sum * ratio), true );
                pk::add_weapon_amount(building, ����_��,  int((troops - weapon_sum)* �����ʰ�_��������_���� * weapon_qty3 / weapon_sum * ratio), true );
                pk::add_weapon_amount(building, ����_����, int((troops - weapon_sum)* �����ʰ�_��������_���� * weapon_qty4 / weapon_sum * ratio), true );
            }
              
                
            return ;
        }
        
        
        
	}

	Main main;
}