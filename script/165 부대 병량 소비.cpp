namespace �δ�_����_�Һ�
{
	class Main
	{
		Main()
		{
			pk::set_func(165, pk::func165_t(callback));
		}

		int callback(pk::unit@ unit)
		{
			if (!pk::is_alive(unit))
				return 0;

			int n = 0;
            float m = 1.f;
			float burn = 0.f;

			if (unit.type == �δ�����_����)
			{
				int facility_id = func_49d8e0(unit);
				if (facility_id == �ü�_��ä)
					m = 1.f;
				else if (facility_id == �ü�_���)
					m = 4.f / 3; // 1.333...
				else if (facility_id == �ü�_��)
					m = 5.f / 3; // 1.666...
				else
					m = 2.f;
			}
            
			if (unit.is_on_fire())
				burn = (6.f - unit.attr.stat[�δ�ɷ�_��ġ] / 20.f) * unit.food / 100;
            
            
            n = int(unit.troops * m / 20.f);   // �⺻ ���� �Һ�
            
            if (pk::get_season() == ����_�ܿ�)      // �ܿ�ö ���� �Һ� 1.2�� ('18.10.10)
                n = int(n * 1.2f);
            
            if (pk::get_hex(unit.get_pos()).terrain == ����_��) 
                n = int(n * 1.2f);               // �δ밡 ��� �౺ �� ���� �Һ� 1.2�� ('18.10.18)
            
            if (unit.has_skill(Ư��_����))    //���� Ư�� : �δ� ���� �Һ� �ݰ� ('18.10.5)
                n = int(n / 2.f);


            n = int(n + burn);
            
            
			if (n <= 0 and unit.troops > 0)
				return 1;
			return n;
		}

		/***/
		int func_49d8e0(pk::unit@ unit)
		{
			int force_id = unit.get_force_id();
			pk::force@ force = pk::get_force(force_id);

			if (!pk::is_alive(force))
				return -1;

			int facility_id = �ü�_��;

			if (pk::has_tech(force, �ⱳ_������ȭ))
				facility_id = �ü�_��ä;
			else if (pk::has_tech(force, �ⱳ_�ü���ȭ))
				facility_id = �ü�_���;

			array<pk::point> arr = pk::range(unit.get_pos(), 1, pk::get_facility(facility_id).max_range);

			for (int i = 0; i < int(arr.length); i++)
			{
				pk::building@ building = pk::get_building(arr[i]);
				if (pk::is_alive(building) and building.facility == facility_id and building.completed and building.get_force_id() == force_id)
					return facility_id;
			}

			return -1;
		}
	}

	Main main;
} 