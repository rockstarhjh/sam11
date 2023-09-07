/*
@������ : �⸶å��
@Update: '19.5.4   // ��������: ����_���ü�_�г�Ƽ �߰�
@Update: '20.8.29  // ��������: ķ���ο����� Ŀ���� ���� ��� �Ұ��ϵ��� ����
*/

namespace ������귮
{
    //---------------------------------------------------------------------------
        
    const bool ����_���ü�_�г�Ƽ = true;   // �������¿� ���ؼ� ���ü��� ����Ͽ� ���귮 ����� (���ô� 1% ����)
    
    //---------------------------------------------------------------------------
        
	class Main
	{
    
		Main()
		{
			pk::set_func(102, pk::func102_t(callback));
		}

		int callback(pk::city@ city, const pk::detail::arrayptr<pk::person@> &in actors, int weapon_id)
		{
			if (!pk::is_valid_equipment_id(weapon_id))
				return 0;
			if (weapon_id >= ����_����)
				return 1;

			int n = 0, sum = 0, max = 0, skill_id = -1;
			bool has_skill = false;

			if (weapon_id <= ����_��)
				skill_id = int(pk::core["�������.���尣Ư��"]);
			else if (weapon_id == ����_����)
				skill_id = int(pk::core["�������.������Ư��"]);

			for (int i = 0; i < int(actors.length); i++)
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

			n = (sum + max + 200) * 5;

			// ���� Ư�⸦ ������ �ִٸ� 2��
			if (has_skill)
				n = n * 2;

			n = int(n * func_5c7040(city, weapon_id));

			// ��ǻ���� ��� Ư�� ���̵����� 2��
			if (pk::get_scenario().difficulty == ���̵�_Ư�� and !city.is_player())
				n = n * 2;
            
            
            // ����_���ü�_�г�Ƽ ('19.5.4)
            if (����_���ü�_�г�Ƽ and city.is_player() and !pk::is_campaign())
            {
                pk::force@ force = pk::get_force(city.get_force_id());
                float force_city_count = float(pk::get_city_list(force).count);
                n = int(n * (1.f - (force_city_count * 0.01f)));
            }
            

			return n;
		}

		float func_5c7040(pk::city@ city, int weapon_id)
		{
			int level1 = 0, level2 = 0;
			if (weapon_id == ����_â or weapon_id == ����_�� or weapon_id == ����_��)
			{
				for (int i = 0; i < city.max_devs; i++)
				{
					pk::building@ building = city.dev[i].building;
					if (pk::is_alive(building))
					{
						switch (building.facility)
						{
						case �ü�_���尣: building.completed ? level1++ : 0; break;
						case �ü�_���尣2��: building.completed ? level2++ : level1++; break;
						case �ü�_���尣3��: building.completed ? 0 : level2++; break;
						}
					}
				}
				if (int(city.blacksmith_counter) > level1 + level2)
					return 1.5f;
				if (int(city.blacksmith_counter) > level1)
					return 1.2f;
			}
			else if (weapon_id == ����_����)
			{
				for (int i = 0; i < int(city.max_devs); i++)
				{
					pk::building@ building = city.dev[i].building;
					if (pk::is_alive(building))
					{
						switch (building.facility)
						{
						case �ü�_������: building.completed ? level1++ : 0; break;
						case �ü�_������2��: building.completed ? level2++ : level1++; break;
						case �ü�_������3��: building.completed ? 0 : level2++; break;
						}
					}
				}
				if (int(city.stable_counter) > level1 + level2)
					return 1.5f;
				if (int(city.stable_counter) > level1)
					return 1.2f;
			}
			return 1.f;
		}
	}

	Main main;
}