namespace ����_ġ��_����
{
	class Main
	{
		Main()
		{
			pk::set_func(154, pk::func154_t(callback));
		}

		int callback(pk::city@ city)
		{
			if (!pk::is_first_month_of_quarter(pk::get_month()))
				return 0;
			pk::force@ force = pk::get_force(city.get_force_id());
			if (force is null)
				return 0;
			// �������� ���� �� 50% Ȯ���� �������� ����
			if (pk::has_tech(force, �ⱳ_��������) and pk::rand_bool(50))
				return 0;
			int n = 90;
			pk::person@ taishu = pk::get_person(city.get_taishu_id());
			if (pk::is_alive(taishu))
				n = n - taishu.stat[����ɷ�_�ŷ�];
			n = pk::max(n, 1) / 10 + pk::rand(3);
			n = pk::min(n, 5);
            
            // ��Ź�� �����̸� ���� ȿ�� ���� ('18.10.4)
            if (pk::get_kunshu_id(force) == ����_��Ź)
                n = int(n * 2.f);
            
			return -n;
		}
	}

	Main main;
}