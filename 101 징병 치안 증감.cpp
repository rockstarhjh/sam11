/*
@������ : �⸶å��
@Update: '19.5.4   // ��������: ����_���ü�_�г�Ƽ �߰�
@Update: '20.8.29  // ��������: ķ���ο����� Ŀ���� ���� ��� �Ұ��ϵ��� ����
*/

namespace ¡��_ġ��_����
{
    //---------------------------------------------------------------------------
    
    const bool ����_���ü�_�г�Ƽ = true;   // �������¿� ���ؼ� ���ü��� ����Ͽ� ġ�Ȱ��� �г�Ƽ (���ô� 1% ����)

    //---------------------------------------------------------------------------

    class Main
	{
		Main()
		{
			pk::set_func(101, pk::func101_t(callback));
		}

		int callback(pk::city@ city, const pk::detail::arrayptr<pk::person@> &in actors, int troops)
		{		
			int n = 100;
			for (int i = 0; i < actors.length; i++)
			{
				pk::person@ actor = actors[i];
				
				if (pk::is_alive(actor))
					n = n + actor.stat[int(pk::core["¡��.�ɷ�"])];
			}
			n = -troops / n;
			
			/*
			// ���ְ� [����]�� ��쿡 1/2 ����
				if (pk::get_kunshu_id(actors[0]) == ����_����)
					n /= 2;
				
			// ���ְ� [����]�� ��쿡 1/2 ����
				if (pk::get_kunshu_id(actors[0]) == ����_����)
					n /= 2;
            */
            
            
            // ����_���ü�_�г�Ƽ ('19.5.4)
            if (����_���ü�_�г�Ƽ and city.is_player() and !pk::is_campaign())
            {
                pk::force@ force = pk::get_force(city.get_force_id());
                float force_city_count = float(pk::get_city_list(force).count);
                n = int(n / (1.f - (force_city_count * 0.01f)));
            }
				
			return n; 
		}
	}

	Main main;
}