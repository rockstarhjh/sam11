/*
@������: �⸶å��
@Update: '18.12.22  / ���泻��: �������� ��ũ��Ʈ �и�
@Update: '19.2.23   / ���泻��: ���� ������ x0.2 �ڵ�����Ǿ ��ũ��Ʈ���� ����
@Update: '20.8.25   / ���泻��: �������������� ������������ �ɼǺи�
@Update: '20.8.29   / ���泻��: ���� ���ü� �г�Ƽ �߰�, ķ���ο����� Ŀ���� ���� ��� �Ұ�
*/


namespace ����_��_����
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
			pk::set_func(152, pk::func152_t(callback));
            
            
            pk::bind(111, pk::trigger111_t(onTurnStart));
		}

		int callback(pk::building@ building, int city_revenue)
		{
            // int n = int(city_revenue * 0.2f);
            int n = int(city_revenue);      // ���� ������ x0.2 �ڵ�����Ǿ ��ũ��Ʈ���� ���� ('19.2.23)
            
            
            
            // �ױ��� ��� �ݼ��� 1.5�� ���� ('18.10.15)
            if ( (pk::get_hex_object_id(building) >= �ǹ�_�ױ�����) and (pk::get_hex_object_id(building) < �ǹ�_�ױ���) )
                n = int(n * 1.5f);
            
            
            // ����_���ü�_�г�Ƽ ('20.8.29)
            if (����_���ü�_�г�Ƽ and building.is_player() and !pk::is_campaign())
            {
                pk::force@ force = pk::get_force(building.get_force_id());
                float force_city_count = float(pk::get_city_list(force).count);
                n = int(n * (1.f - (force_city_count * 0.05f)));
            }
            
            // ------------------------------------------------------------------
            // ���� �� ���� �������� ���� �ݼ��� ���� ���� : ���� ������ ���� ('18.10.14)
            
            if (������������ and !pk::is_campaign())
            {
            
                n = int(n * 1.5f); // ���� �������� ���� ���� ���Ҹ� �����Ͽ� �⺻ ���� 50% ���� ���� : ���ü����� 20%���� 30%�� ����
                
                float rich_rate = pk::is_valid_person_id(building.who_has_skill(Ư��_��ȣ))? 1.5f : 1.0f;  // �Ϲ�=1.0  Ư���ȣ=1.5 ��ȯ
                
                // �Ϲݺ��� ������ ����, ���� ���� �� ���� ��� ���� ������ ����
                int weapon_qty1 = pk::get_weapon_amount(building, ����_â);
                int weapon_qty2 = pk::get_weapon_amount(building, ����_��);
                int weapon_qty3 = pk::get_weapon_amount(building, ����_��);
                int weapon_qty4 = pk::get_weapon_amount(building, ����_����);
                int weapon_sum = pk::max(1, weapon_qty1 + weapon_qty2 + weapon_qty3 + weapon_qty4);   // ���� 0 �� ��� error �߻� ������ ('18.10.21)
                
                int weapon_pay = int(0.010f * weapon_sum / rich_rate);
                int gold_estimate = pk::get_gold(building) + n;
                
                n = n - weapon_pay;
                
                /*
                if (gold_estimate > weapon_pay) // ������ + ���� ���� �� ������ ����
                    n = n - weapon_pay;
                else                            // ������ + ���� ���� �� ���� ���׿� ����Ͽ� ���� ���� �յ� ����
                {
                    n = -pk::get_gold(building);
                    
                    pk::add_weapon_amount(building, ����_â,  int((gold_estimate - weapon_pay)* 2.5f * weapon_qty1 / weapon_sum), true);
                    pk::add_weapon_amount(building, ����_��,  int((gold_estimate - weapon_pay)* 2.5f * weapon_qty2 / weapon_sum), true);
                    pk::add_weapon_amount(building, ����_��,  int((gold_estimate - weapon_pay)* 2.5f * weapon_qty3 / weapon_sum), true);
                    pk::add_weapon_amount(building, ����_����, int((gold_estimate - weapon_pay)* 2.5f * weapon_qty4 / weapon_sum), true);
                }
                */
                
                // �������� �� ������ ������ ������ ���� 
                n = n - int(15.f*(pk::get_weapon_amount(building, ����_����)));
                n = n - int(15.f*(pk::get_weapon_amount(building, ����_����)));
                n = n - int(20.f*(pk::get_weapon_amount(building, ����_���)));
                n = n - int(25.f*(pk::get_weapon_amount(building, ����_����)));
                n = n - int(20.f*(pk::get_weapon_amount(building, ����_����)));
                n = n - int(25.f*(pk::get_weapon_amount(building, ����_����)));
            
                // ------------------------------------------------------------------
            
            }
            
            
            
			return n;
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