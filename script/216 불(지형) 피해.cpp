namespace ��_����
{
	class Main
	{
		Main()
		{
			pk::set_func(216, pk::func216_t(callback));
		}

		int callback(pk::unit@ unit, const pk::point &in pos)
		{
            // ��ũ��Ʈ ��� ����, "Ư��_ȭ��" ���� �߰� ('18.10.7)
            int n = 200 + pk::rand(200);
			if (unit.has_skill(Ư��_ȭ��))
				n = 0;
			else if (unit.has_skill(Ư��_ȭ��))
                n = n / 2; 
			if (unit.has_skill(Ư��_�))
				n = n * 2;
            
            //���� ������ 1% ��ŭ ��°��� ('18.10.11)
            pk::add_energy(unit, -n/100);
            
			return n;
		}
	}

	Main main;
}