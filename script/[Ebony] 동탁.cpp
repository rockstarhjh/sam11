// 동탁


namespace Ebony_동탁
{
	class Main
	{
		
		pk::person@ 동탁 = pk::get_person(무장_동탁);
		
		
		
		Main()
		{
			pk::bind(102, pk::trigger102_t(onGameInit));
            pk::bind(111, pk::trigger111_t(onTurnStart));
		}
		
		void onGameInit()
        {character_dongzhuo();}
        void onTurnStart(pk::force@ force)
		{character_dongzhuo();}
		
		
		void character_dongzhuo()
        {
			if (pk::get_year() < (동탁.birth + 51))
			{
				동탁.skill = 특기_백마;
				동탁.stat[무장능력_통솔] = 78;
				동탁.stat[무장능력_무력] = 91;
				동탁.stat[무장능력_매력] = 67;
				동탁.tekisei[병종_기병] = 적성_A;
			}
			if (pk::get_year() >= (동탁.birth + 51) and pk::get_year() < (동탁.birth + 54))
			{
				동탁.skill = 특기_징세;
				동탁.stat[무장능력_통솔] = 76;
				동탁.stat[무장능력_무력] = 89;
				동탁.stat[무장능력_매력] = 52;
				동탁.tekisei[병종_기병] = 적성_A;
			}			
			if (pk::get_year() >= (동탁.birth + 54))
			{
				동탁.stat[무장능력_통솔] = 74;
				동탁.stat[무장능력_무력] = 87;
				동탁.stat[무장능력_매력] = 37;
				동탁.tekisei[병종_기병] = 적성_B;
			}
		}			
	}

	Main main;
}