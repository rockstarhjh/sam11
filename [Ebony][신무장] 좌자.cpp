// 좌자
namespace Ebony_신무장_좌자
{
	const int 좌자_신무장번호 = 957;	// 좌자 신무장 번호 입력
	const bool 포상금지 = true; // 포상가능 true false
	const bool 충성도변화 = true; // 충성도변화 true false
	
	class Main
	{
		
		pk::person@ 좌자 = pk::get_person(좌자_신무장번호);		
		
		Main()
		{
            pk::bind(111, pk::trigger111_t(character_zuoci));
			 
			if (!pk::NDEBUG)
				return;
			xml();			 
		}
		
		pk::force@ 좌자_세력 = pk::get_force(좌자.force_id);
		pk::person@ 군주;
		pk::person@ 군사;
		pk::city@ 도시;
		
		void character_zuoci(pk::force@ force)
        {			
			좌자.banned_kunshu = -1;
			좌자.ban_timer = 0;
			
			if (좌자_세력 !is null)
			{
				@군주 = pk::get_person(좌자_세력.kunshu);
				
				if (force.get_id() == 좌자_세력.get_id())
				{
					좌자.aishou = 군주.aishou;
					
					if (충성도변화)
					{좌자.loyalty = pk::rand(100)+30;}
					
					if (포상금지)
					{좌자.reward_done = true;}	
				
					
					switch (pk::rand(14))
					{
						case 0 : pk::say(pk::u8encode("흙쥐가 금호랑이를 따라가면\n간웅이 끝나리라!"), 좌자);break;
						case 1 : pk::say(pk::u8encode("하루에 양 천마리는 거뜬하다구!"), 좌자);break;
						case 2 : pk::say(pk::u8encode("둔갑천서를 어디에 뒀더라.."), 좌자);break;
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
		}
		
		void xml()
		{
			// 좌자 무장번호가 바뀌면 이 아래도 바꿔주셔야 합니다.
			pk::load_xml("""
			<pk utf8="true" trace="true">
			<!--좌자--><무장 번호="957"><계략성공확률보너스 값="3"/><특기 값="귀문,강운,혈로"/></무장>
			</pk>							
			""");			
		}
	}

	Main main;
}