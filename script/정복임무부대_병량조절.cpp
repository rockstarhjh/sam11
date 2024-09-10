
namespace �����ӹ��δ�_��������
{
	
	// ================ CUSTOMIZE ================

    const float minimum_food = 2.2f;    // �δ밡 �������� �ּ� ���� ���� (���� ��� ���� ����)
    
	// ===========================================	
    
    
	class Main
	{
		
		Main()
		{
            pk::bind(172, pk::trigger172_t(����_����));
		}
		

        void ����_����(pk::unit@ unit, const pk::point &in pos)
        {
            if (pk::is_campaign()) return;
            if (!pk::is_alive(unit)) return;	
            if (unit.order != �δ��ӹ�_����) return;			

            pk::building@ base = pk::get_building(pk::get_service(unit));
			if (!pk::is_alive(base)) return;
			if (pk::is_player_controlled(base)) return;
			if (pk::is_player_controlled(unit)) return;			

            // �δ��� �̵� �� ��ġ�� �Ҽ� ������ �ٸ��� �ƿ�           
            if (base.pos != unit.pos) return;
            string base_name = pk::decode(pk::get_name(base));	
            string unit_name = pk::decode(pk::get_name(pk::get_person(unit.leader)));

		    float ratio = pk::max(minimum_food, pk::get_food(base) / float(pk::get_troops(base) + 1));

            // �����δ�� �δ��ӹ��� �����ε� ������ ���� ���� �Ѿ�� ��ȯ
            if (unit.type == �δ�����_���� and unit.order == �δ��ӹ�_���� and unit.food > unit.troops * ratio)
            {
                // �δ� ���� ����, ���Һ��� ������ �ǵ���
                int food_amount = unit.food - (unit.troops * ratio);
                pk::add_food(unit, -food_amount, false);        
                pk::add_food(base, +food_amount, false);        	

                if (����׸��)
                pk::info(pk::format("--- {}��, {}�� ������ȯ! ({}��{})", unit_name, base_name, unit.food + food_amount, unit.food));		
            }
			
        }

            bool ����׸�� = false;        
	} 

	Main main;
	
} 