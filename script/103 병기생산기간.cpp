/*
@������ : �⸶å��
@Update: '20.8.29  // ��������: ����_���ü�_�г�Ƽ �߰�, ķ���ο����� Ŀ���� ���� ��� �Ұ��ϵ��� ����
*/

namespace �������Ⱓ
{
    
    //---------------------------------------------------------------------------
        
    const bool ����_���ü�_�г�Ƽ = true;     // �������¿� ���ؼ� ���ü��� ����Ͽ� ����Ⱓ ����� (���ô� 5% ����)
    
    //---------------------------------------------------------------------------
     
     
     
	class Main
	{
		Main()
		{
			pk::set_func(103, pk::func103_t(callback));
		}

		int callback(const pk::detail::arrayptr<pk::person@> &in actors, int weapon_id)
		{
			if (!pk::is_valid_equipment_id(weapon_id))
				return 0;
			if (weapon_id < ����_����)
				return 0;

			int n = 0, sum = 0, max = 0, skill_id = -1;
			bool has_skill = false;

			if (weapon_id == ����_���� or weapon_id == ����_���� or weapon_id == ����_���� or weapon_id == ����_���)
				skill_id = int(pk::core["�������.����Ư��"]);
			else if (weapon_id == ����_���� or weapon_id == ����_����)
				skill_id = int(pk::core["�������.����Ư��"]);

			for (int i = 0; i < actors.length; i++)
			{
				pk::person@ actor = actors[i];
				if (pk::is_alive(actor))
				{
					int s = actor.stat[int(pk::core["�������.�ɷ�"])];
					sum = sum + s;
					max = pk::max(max, s);
					if (pk::has_skill(actor, skill_id))
						has_skill = true;
				}
			}

			n = 10 - pk::max(sum + max - 200, 24) / 24;
            
            n = pk::max(n, 2);      // overflow ������ ('18.11.17)
			
            if (weapon_id >= ����_�ְ�)
			{
				pk::person@ actor = actors[0];
				if (pk::is_alive(actor))
				{
					pk::building@ building = pk::get_building(actor.service);
					if (pk::is_alive(building))
					{
						pk::city@ city = pk::building_to_city(building);
						if (pk::has_facility(city, �ü�_������))
						{
							n = 8 - pk::max(sum + max - 200, 24) / 24;
							n = pk::max(n, 2);
						}
					}
				}
			}

            // ����_���ü�_�г�Ƽ ('20.8.29)
            pk::person@ actor = actors[0];
            if (����_���ü�_�г�Ƽ and actor.is_player() and !pk::is_campaign())
            {
                pk::force@ force = pk::get_force(actor.get_force_id());
                float force_city_count = float(pk::get_city_list(force).count);
                n = n + int(0.05f * force_city_count);
            }
            
            
            if (n < 2) n = 2;
            
			// ���� Ư�⸦ ������ �ִٸ� �ݰ�
			if (has_skill)
				n = n / 2;
			return n;
		}
	}

	Main main;
}