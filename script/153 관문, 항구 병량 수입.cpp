/*
@������ : �⸶å��
@Update : '18.10.15  / ���泻�� : ���� �������� 1.5�� ����
@Update : '19.2.26   / ���泻�� : ���� �� ��ü������ x0.2�� ����Ǵ� ������ ��ũ��Ʈ���� x0.2�� ���� ����.
@Update: '20.8.29   / ���泻��: ���� ���ü� �г�Ƽ �߰�, ķ���ο����� Ŀ���� ���� ��� �Ұ�

*/

namespace ����_����_����
{
    //---------------------------------------------------------------------------------------
    // ���� ���� (true = on, false = off)
    const bool  ����_���ü�_�г�Ƽ = true;     // �������¿� ���ؼ� ���ü��� ����Ͽ� ���� ����� (���ô� 5% ����)
    
    //---------------------------------------------------------------------------------------
    
    
	class Main
	{
		Main()
		{
			pk::set_func(153, pk::func153_t(callback));
		}

		int callback(pk::building@ building, int city_harvest)
		{
			//int n = int(city_harvest * 0.2f);
            
			int n = int(city_harvest);  // '19.2.16
            
            // ������ ��� �������� 1.5�� ���� ('18.10.15)
            if ( (pk::get_hex_object_id(building) >= �ǹ�_��������) and (pk::get_hex_object_id(building) < �ǹ�_������) )
                n = int(n * 0.8f);
            
             
            // ����_���ü�_�г�Ƽ ('20.8.29)
            if (����_���ü�_�г�Ƽ and building.is_player() and !pk::is_campaign())
            {
                pk::force@ force = pk::get_force(building.get_force_id());
                float force_city_count = float(pk::get_city_list(force).count);
                n = int(n * (1.f - (force_city_count * 0.05f)));
            }
            
            return n;
		}
	}

	Main main;
}