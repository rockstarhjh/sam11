namespace �Ϻ�_����_����
{
	class Main
	{
		Main()
		{
			pk::set_func(156, pk::func156_t(callback));
		}

		int callback(pk::building@ building)
		{
			int n = pk::max(building.get_troops(), 100);
			n = pk::rand(50) - sqrt(n / 100) * -30;
            
            
            //�ֺ��� ���� ���� �� ���� ���� 2�� ���� ('18.10.12)
            if (pk::enemies_around(building))
            {
                n *= 2;  
                pk::add_energy(building, -3);               // ����ȿ���� ��� 3 ����
            }
            
			return -n;
		}
	}

	Main main;
}