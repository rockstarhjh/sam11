namespace 턴별_병력_감소
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
            
            
            //주변에 적이 있을 시 병력 감소 2배 증가 ('18.10.12)
            if (pk::enemies_around(building))
            {
                n *= 2;  
                pk::add_energy(building, -3);               // 전시효과로 기력 3 감소
            }
            
			return -n;
		}
	}

	Main main;
}