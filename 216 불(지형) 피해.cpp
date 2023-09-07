namespace 불_피해
{
	class Main
	{
		Main()
		{
			pk::set_func(216, pk::func216_t(callback));
		}

		int callback(pk::unit@ unit, const pk::point &in pos)
		{
            // 스크립트 방식 수정, "특기_화공" 조건 추가 ('18.10.7)
            int n = 200 + pk::rand(200);
			if (unit.has_skill(특기_화신))
				n = 0;
			else if (unit.has_skill(특기_화공))
                n = n / 2; 
			if (unit.has_skill(특기_등갑))
				n = n * 2;
            
            //병력 피해의 1% 만큼 기력감소 ('18.10.11)
            pk::add_energy(unit, -n/100);
            
			return n;
		}
	}

	Main main;
}