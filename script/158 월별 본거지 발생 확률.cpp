namespace ����_������_�߻�_Ȯ��
{
	class Main
	{
		Main()
		{
			pk::set_func(158, pk::func158_t(callback));
		}

		int callback(pk::city@ city)
		{
			// ���� ���� �� 6�������� �߻����� ����.
			if (pk::get_elapsed_months() <= 6)
				return 0;

			// �ߺ� �߻� ����
			int city_id = city.get_id();
			// �� �ݹ��� ���� ���� ȣ��Ǳ� ������ �� �� �ǹ��� ���� ���� ����Ʈ�� �����ϸ� �ӵ��� �������Ƿ� �迭�� ��ȯ.
			array<pk::building@> arr = pk::list_to_array(pk::get_building_list());
			for (int i = 0; i < int(arr.length); i++)
			{
				pk::building@ building = arr[i];
				if (pk::get_city_id(building.get_pos()) == city_id and (building.facility == �ü�_������1 or building.facility == �ü�_������2))
					return 0;
			}

			// ġ���� ����ġ �̻��� ��� �߻����� ����
			if (int(city.public_order) >= 80 - (pk::city_to_building(city).has_skill(Ư��_����) ? 20 : 0))
				return 0;

			// ����ġ �̸��� ��� Ȯ�� ���
			return (100 - city.public_order) / 3;
		}
	}

	Main main;
}