// 우길
namespace Ebony_신무장_우길
{
	const int 우길_신무장번호 = 958;	// 우길 신무장 번호 입력
	const bool 포상금지 = true;
	const bool 충성도변화 = true; // 충성도변화 true false
	
	class Main
	{
		
		pk::person@ 우길 = pk::get_person(우길_신무장번호);		
		
		Main()
		{
            pk::bind(111, pk::trigger111_t(character_yuji));
			
			if (!pk::NDEBUG)
				return;
			xml();			 
		}
		
		pk::force@ 우길_세력 = pk::get_force(우길.force_id);
		pk::person@ 군주;
		pk::city@ 도시;		

		void character_yuji(pk::force@ force)
        {
			우길.banned_kunshu = -1;
			우길.ban_timer = 0;

			if (우길_세력 !is null)
			{
				@군주 = pk::get_person(우길_세력.kunshu);
				
				if (force.get_id() == 우길_세력.get_id())
				{			
					if (충성도변화)
					{
						우길.aishou = 군주.aishou;
						switch (pk::rand(2))
						{
						case 0: 우길.loyalty += pk::rand(10); break;
						case 1: 우길.loyalty -= pk::rand(8); break;
						}
					}
				}
					
				if (포상금지)
				{우길.reward_done = true;}			
				
				switch (pk::rand(14))
				{
					case 0 : pk::say(pk::u8encode("이제 곧 비가 내릴 것이오"), 우길);break;
					case 1 : pk::say(pk::u8encode("저것은 길성인가.."), 우길);break;
					case 2 : pk::say(pk::u8encode("맑은 날이로군.."), 우길);break;
					case 3 : break;
					case 4 : break;
					case 5 : break;
					case 6 : break;
					case 7 : break;
					case 8 : break;
					case 9 : break;
					case 10 : break;
					case 11 : break;
					case 12 : break;
					case 13 : break;
				}
			}
		}

		void xml()
		{
			// 우길 무장번호가 바뀌면 이 아래도 바꿔주셔야 합니다.
			pk::load_xml("""
			<pk utf8="true" trace="true">
			<!--우길--><무장 번호="958"><특기 값="기원, 풍수, 요술"/></무장>
			</pk>							
			""");			
		}
	}

	Main main;
}