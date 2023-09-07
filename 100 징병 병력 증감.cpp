/*
@������ : �⸶å��
@Update: '18.10.14  // ��������: ������ ���� Ư�� �Ǵ� Ȳ���� ��� ¡���� ����
@Update: '19.4.26   // ��������: �뵵�� ¡���� ���� �߰�
@Update: '19.5.4    // ��������: ����_���ü�_�г�Ƽ �߰�
@Update: '20.8.25   // ��������: null point error ���� ����
@Update: '20.8.29  // ��������: ķ���ο����� Ŀ���� ���� ��� �Ұ��ϵ��� ����
*/

namespace ¡��_����_����
{
    //---------------------------------------------------------------------------
    
    const bool  ����Ư��_������ = true;   // ����,����,�¼��� �� Ư�� ���� �� ����
    const float ����Ư��_���ָ� = 1.10f;   // ���� ���� ���
    const float ����Ư��_������ = 1.15f;  // ���� ���� ���
    const float ����Ư��_�¼��� = 1.20f;  // �¼� ���� ���
    
    const bool  Ȳ������_ȿ������ = true;   // ���� Ȳ�� �˸� ���� �Ǵ� ���ְ� Ȳ���� ��� ����
    const float Ȳ������_��ȿ�� = 1.10f;  // Ȳ�� ���� ���
    
    const bool  �뵵��_¡������ = true;   // �뵵�� ¡���� ���� ����
    const float �뵵��_¡����� = 1.2f;   // �뵵�� ¡���� ���� ���
    
    const bool ����_���ü�_�г�Ƽ = true;   // �������¿� ���ؼ� ���ü��� ����Ͽ� ¡���� ����� (���ô� 1% ����)
    
    //---------------------------------------------------------------------------
    
	class Main
	{
		Main()
		{
			pk::set_func(100, pk::func100_t(callback));
		}

		int callback(pk::building@ building, const pk::detail::arrayptr<pk::person@> &in actors)
		{
			if (pk::is_alive(building) and actors[0] !is null)
			{
				pk::city@ city = pk::building_to_city(building);
				if (pk::is_alive(city))
				{
					int n = 0;
					int sum = 0;
					int mul = 100;
					for (int i = 0; i < actors.length; i++)
					{
						pk::person@ actor = actors[i];
						if (pk::is_alive(actor))
						{
							sum += actor.stat[int(pk::core["¡��.�ɷ�"])];
							// �� Ư�⸦ �����ϰ� ���� ��� 50% ���
							if (pk::has_skill(actor, int(pk::core["¡��.Ư��"])))
								mul = 150;
						}
					}
					n = int((1000 + (city.public_order + 20) * sum * 5 / 100) * mul / 100 * func_5c4600(city));
					// Ư�� ���̵� ��ǻ���� ��� 2��
					if (pk::get_scenario().difficulty == ���̵�_Ư�� and !city.is_player())
						n *= 2;
					// �ֺ��� �� �δ밡 ������ ��� �ݰ�
					if (pk::enemies_around(building))
						n /= 2;
					
                    
                    // -----------------------------------------------------------------------------
                    
                    // ����
                    pk::force@ force = pk::get_force(building.get_force_id());
                    
                    // ������ ���� Ư�� ('18.10.14)
                    if (����Ư��_������ and !pk::is_campaign())
                    {
                        // ���ְ� Ư��_�� ���� �� ¡���� ����
                        pk::person@ p1 = pk::get_person(pk::get_kunshu_id(building));
                        if (pk::is_alive(p1))
                        {
                            if (pk::has_skill(p1, Ư��_��))
                                n = int(n * ����Ư��_���ָ�);
                        }
                        // ������ Ư��_�� ���� �� ¡���� ����
                        pk::person@ p2 = pk::get_person(pk::get_totoku_id(building));
                        if (pk::is_alive(p2))
                        {
                            if (pk::has_skill(p2, Ư��_��))
                                n = int(n * ����Ư��_������);
                        }
                        // �¼��� Ư��_�� ���� �� ¡���� ����
                        pk::person@ p3 = pk::get_person(pk::get_taishu_id(building));
                        if (pk::is_alive(p3))
                        {
                            if (pk::has_skill(p3, Ư��_��))
                                n = int(n * ����Ư��_�¼���);
                        }
                    }
                    
                    // ����Ȳ�� ��ȣ���� �Ǵ� ���ְ� Ȳ���� ���� ¡���� ���� ('18.10.14)
                    if (Ȳ������_ȿ������ and !pk::is_campaign())
                    {
                        if ( pk::is_protecting_the_emperor(force) )
                            n = int(n * Ȳ������_��ȿ��);
                        else if (force.title == ����_Ȳ�� ) 
                            n = int(n * Ȳ������_��ȿ��);
                    }
                    
                    // �뵵�� ¡���� ���� ('19.4.26)
                    if (�뵵��_¡������ and pk::is_large_city(city) and !pk::is_campaign())
                        n = int(n * �뵵��_¡�����);
                    
                    // ����_���ü�_�г�Ƽ ('19.5.4)
                    if (����_���ü�_�г�Ƽ and building.is_player() and !pk::is_campaign())
                    {
                        float force_city_count = float(pk::get_city_list(force).count);
                        n = int(n * (1.f - (force_city_count * 0.01f)));
                    }
                    
                    
                    // -----------------------------------------------------------------------------
                    
					return n;
				}
			}
			return 0;
		}

		float func_5c4600(pk::city@ city)
		{
			int level1 = 0, level2 = 0;
			for (int i = 0; i < int(city.max_devs); i++)
			{
				pk::building@ building = city.dev[i].building;
				if (pk::is_alive(building))
				{
					switch (building.facility)
					{
					case �ü�_����: building.completed ? level1++ : 0; break;
					case �ü�_����2��: building.completed ? level2++ : level1++; break;
					case �ü�_����3��: building.completed ? 0 : level2++; break;
					}
				}
			}
			if (int(city.barracks_counter) > level1 + level2)
				return 1.5f;
			if (int(city.barracks_counter) > level1)
				return 1.2f;
			return 1.f;
		}
	}

	Main main;
}