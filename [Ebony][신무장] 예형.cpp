// 예형
namespace Ebony_신무장_예형
{
	const int 예형_신무장번호 = 959;	// 예형 신무장 번호 입력
	const int tp = 150;	// 예형 설전승리 기교포인트
	const bool 포상금지 = true; // 포상가능 true false
	const bool 충성도변화 = true; // 충성도변화 true false
	
	class Main
	{

		int debate_result;

		pk::person@ 예형 = pk::get_person(예형_신무장번호);

		Main()
		{
            pk::bind(111, pk::trigger111_t(character_miheng));
			pk::bind(112, pk::trigger112_t(callback));
		}

		pk::force@ 예형_세력 = pk::get_force(예형.force_id);
		pk::person@ 군주;
		pk::person@ 군사;
		pk::city@ 도시;

		void character_miheng(pk::force@ force)
        {
			예형.banned_kunshu = -1;
			예형.ban_timer = 0;
			
			if (예형_세력 !is null)
			{
				@군주 = pk::get_person(예형_세력.kunshu);
				@군사 = pk::get_person(예형_세력.gunshi);
				@도시 = pk::building_to_city(pk::get_building(군주.service));
				
				if (force.get_id() == 예형_세력.get_id())
				{
					if (충성도변화)
					{					
						예형.giri = 의리_매우높음;
						예형.aishou = 군주.aishou;
						
						if (예형.loyalty >= 70)
						{예형.loyalty -= pk::rand(6);}
						else if (예형.loyalty < 70)
						{예형.loyalty -= pk::rand(3);}
					}
					if (포상금지)
					{예형.reward_done = true;}
				
					
					switch (pk::rand(14))
					{
						case 0 : pk::say(pk::u8encode("술만 쳐마시니 술통이오!"), 예형);break;
						case 1 : pk::say(pk::u8encode("할 수 있는게 없으니\n시렁의 옷걸이요!"), 예형);break;
						case 2 : pk::say(pk::u8encode("고기만 퍼먹으니 고기자루요!"), 예형);break;
						case 3 : pk::say(pk::u8encode("밥만 축내니 밥주머니요!"), 예형);break;
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


		void callback(pk::force@ force)
		{
			if (예형_세력 !is null)
			{
				@군주 = pk::get_person(예형_세력.kunshu);
				@군사 = pk::get_person(예형_세력.gunshi);
				@도시 = pk::building_to_city(pk::get_building(군주.service));
				
				if (force.get_id() == 예형_세력.get_id() and 예형_세력.is_player() and pk::rand_bool(100 - 예형.loyalty) and 예형.loyalty < 90 and 예형.mibun != 신분_사망)
				{
					pk::scene(pk::scene_t(scene));
				}
				
				if (force.get_id() == 예형_세력.get_id() and !예형_세력.is_player())
				{
					if (pk::rand_bool(100 - 예형.loyalty) and 예형.loyalty < 90 and 예형.mibun != 신분_사망)
					{			
						switch (pk::rand(3))
						{
							case 0 :
								예형.loyalty = 120;
								pk::add_tp(예형_세력, tp, 도시.get_pos());
								pk::history_log(pk::get_building(예형.service).pos, 예형_세력.color, pk::u8encode(pk::format("\x1b[2x" + pk::u8decode(pk::get_name(군주)) + "군\x1b[0x, \x1b[1x" + pk::u8decode(pk::get_name(예형)) + "\x1b[0x과의 설전 승리로 기교점수 \x1b[1x{}\x1b[0x 획득", tp)));
								break;
							case 1 :
								if (예형.loyalty >= 70)
								{예형.loyalty -= pk::rand(3);}
								else if (예형.loyalty < 70)
								{예형.loyalty -= pk::rand(2);}
								pk::history_log(pk::get_building(예형.service).pos, 예형_세력.color, pk::u8encode("\x1b[2x" + pk::u8decode(pk::get_name(군주)) + "군\x1b[0x, \x1b[1x" + pk::u8decode(pk::get_name(예형)) + "\x1b[0x과의 설전 패배"));
								break;
							case 2 :
								if (pk::rand_bool(10))
								{
									pk::history_log(pk::get_building(예형.service).pos, 예형_세력.color, pk::u8encode("\x1b[2x" + pk::u8decode(pk::get_name(군주)) + "군\x1b[0x, 모욕을 일삼던 \x1b[1x" + pk::u8decode(pk::get_name(예형)) + "\x1b[0x을 처형"));	
									예형.mibun = 신분_사망;
								}
								break;
						}
						
					}
				}
			}
			else return;
		}

		void scene()
		{			
			@군주 = pk::get_person(예형_세력.kunshu);
			@군사 = pk::get_person(예형_세력.gunshi);
			@도시 = pk::building_to_city(pk::get_building(군주.service));
			
			string 군주_이름 = pk::u8decode(pk::get_name(군주));
			string 군사_이름 = pk::u8decode(pk::get_name(군사));
			string 군사_자 = pk::u8decode(군사.sei+군사.azana);
			string 군주_작위 = pk::u8decode(pk::get_name(pk::get_title(예형_세력.title)));

			pk::person@ 전령 = pk::get_person(무장_전령);
			pk::person@ 문관 = pk::get_person(무장_문관);
			pk::person@ 무관 = pk::get_person(무장_무관);
			pk::person@ 위병 = pk::get_person(무장_위병);
			pk::person@ 병사 = pk::get_person(무장_병사);
			
			//예형 등장
			pk::move_screen(도시.get_pos());
			pk::fade(0);
			pk::sleep();


			switch (pk::rand(5))
			{
				case 0 :
					//집무
					pk::background(2);
					pk::fade(255);
					pk::message_box(pk::u8encode("자, 모두 모였으면 평정을 시작하겠.."), 군주);
					pk::cutin(17);
					pk::message_box(pk::u8encode("쥐새끼들만 모여서 무얼 하겠다고?"), 예형);
					pk::play_sfx(3,100);
					pk::message_box(pk::u8encode("예형, 자네가 여기 어인 일인가?"), 군주);
					break;
				case 1 :
					//자택
					pk::background(5);
					pk::fade(255);
					pk::message_box(pk::u8encode("오늘은 간만에 시간이 좀 남는군."), 군주);
					pk::cutin(18);
					pk::message_box(pk::u8encode(pk::format("{}님! 계시옵니까?", 군주_이름)), 문관);
					pk::message_box(pk::u8encode("무슨 일이냐?"), 군주);
					pk::play_sfx(3,100);
					pk::message_box(pk::u8encode(pk::format("{}님! 예형이 또 난리를 피우고 있습니다!", 군주_이름)), 문관);
					pk::message_box(pk::u8encode("쉴 틈이 없군.. 얼른 가겠다."), 군주);
					pk::fade(0);
					pk::background(2);
					pk::fade(255);
					break;
				case 2 :
					//시장
					pk::background(4);
					pk::fade(255);
					pk::message_box(pk::u8encode("내정에도 신경을 많이 써야겠어.."), 군주);
					pk::cutin(18);
					pk::message_box(pk::u8encode(pk::format("{}님!", 군주_이름)), 전령);
					pk::message_box(pk::u8encode("무슨 일이냐?"), 군주);
					pk::message_box(pk::u8encode(pk::format("{}님! 예형이 또 난리를 피우고 있습니다!", 군주_이름)), 전령);
					pk::play_sfx(3,100);
					pk::message_box(pk::u8encode("참으로 골치아픈 친구로다.. 곧 가겠다."), 군주);
					pk::fade(0);
					pk::background(2);
					pk::fade(255);
					break;
				case 3 :
					//연못
					pk::background(6);
					pk::fade(255);
					pk::message_box(pk::u8encode("참 맑은 날과 물이로다."), 군주);
					pk::cutin(18);
					pk::message_box(pk::u8encode(pk::format("{}님!", 군주_이름)), 전령);
					pk::message_box(pk::u8encode("무슨 일로 나를 찾느냐?"), 군주);
					pk::message_box(pk::u8encode(pk::format("{}님! 예형이 주변에 막말을 늘어놓아 다들 곤란해 하고 있습니다.", 군주_이름)), 전령);
					pk::play_sfx(3,100);
					pk::message_box(pk::u8encode("흠. 알겠다. 내 곧 가마."), 군주);
					pk::fade(0);
					pk::background(2);
					pk::fade(255);
					break;
				case 4 :
					//숲속
					pk::background(3);
					pk::fade(255);
					pk::message_box(pk::u8encode("하하하. 즐거운 사냥이었구나."), 군주);
					pk::message_box(pk::u8encode("거기 누구냐?!"), 위병);
					pk::cutin(18);
					pk::message_box(pk::u8encode(pk::format("{}님! 헉헉", 군주_이름)), 무관);
					pk::message_box(pk::u8encode("무슨 일이냐?"), 군주);
					pk::message_box(pk::u8encode(pk::format("{}님! 지금 밑에서 예형 나으리 때문에 소란이 크게 났습니다!", 군주_이름)), 무관);
					pk::play_sfx(3,100);
					pk::message_box(pk::u8encode("하.. 그 서생이 사람을 참 피곤하게 하는구나. 곧 가겠다."), 군주);
					pk::fade(0);
					pk::background(2);
					pk::fade(255);
					break;						
			}



			pk::play_sfx(10,100);
			pk::force@ 군주_세력 = pk::get_force(군주.get_force_id());

			pk::person@ 관우 = pk::get_person(무장_관우);
			pk::person@ 장비 = pk::get_person(무장_장비);
			pk::person@ 제갈량 = pk::get_person(무장_제갈량);
			pk::person@ 조운 = pk::get_person(무장_조운);
			pk::person@ 황충 = pk::get_person(무장_황충);


			string grade_color;
			string grade_name;
			string character_title;


			switch (0)
			{
				case 0 :
					for (int person_id = 0; person_id < 무장_끝; person_id++)
					{
						pk::person@ person_t = pk::get_person(pk::rand(1100));

						//관우
						if (person_t.get_id() == 무장_관우 and person_t.mibun != 신분_재야 and person_t.mibun != 신분_포로 and person_t.mibun != 신분_미등장 and person_t.mibun != 신분_미발견 and person_t.mibun != 신분_사망 and person_t.mibun != 신분_없음 and person_t.location == 군주.location and person_t.service == 군주.service)
						{
								pk::message_box(pk::u8encode("그 긴 수염으로는 마당이나 쓸면 딱이렷다!"), 예형);
								pk::message_box(pk::u8encode(pk::format("흠?!", 군주_이름)), person_t);
								break;
						}

						//제갈량
						else if (person_t.get_id() == 무장_제갈량 and person_t.mibun != 신분_재야 and person_t.mibun != 신분_포로 and person_t.mibun != 신분_미등장 and person_t.mibun != 신분_미발견 and person_t.mibun != 신분_사망 and person_t.mibun != 신분_없음 and person_t.location == 군주.location and person_t.service == 군주.service)
						{
								pk::message_box(pk::u8encode("닭털로 만든 그 부채를 흔들 때마다 그 똥가루가 날리는구나!"), 예형);
								pk::message_box(pk::u8encode(pk::format("하하하", 군주_이름)), person_t);
								break;
						}

						//하후돈
						else if (person_t.get_id() == 무장_하후돈 and person_t.mibun != 신분_재야 and person_t.mibun != 신분_포로 and person_t.mibun != 신분_미등장 and person_t.mibun != 신분_미발견 and person_t.mibun != 신분_사망 and person_t.mibun != 신분_없음 and person_t.location == 군주.location and person_t.service == 군주.service)
						{
								pk::message_box(pk::u8encode("아니, 우리 완체장군 아니시오?"), 예형);
								pk::message_box(pk::u8encode(pk::format("이, 이 놈이!", 군주_이름)), person_t);
								break;
						}
						//여포
						else if (person_t.get_id() == 무장_여포 and person_t.mibun != 신분_재야 and person_t.mibun != 신분_포로 and person_t.mibun != 신분_미등장 and person_t.mibun != 신분_미발견 and person_t.mibun != 신분_사망 and person_t.mibun != 신분_없음 and person_t.location == 군주.location and person_t.service == 군주.service)
						{
								pk::message_box(pk::u8encode("..!\n(예형이 봉선의 눈을 슬쩍 피한다.)"), 예형);
								pk::message_box(pk::u8encode(pk::format("(여포가 예형을 노려보고 있다.)", 군주_이름)), person_t);
								break;
						}
						//순욱
						else if ((person_t.get_id() == 무장_순욱 or person_t.get_id() == 무장_조운 or person_t.get_id() == 무장_주유 or person_t.get_id() == 무장_마속 or person_t.get_id() == 무장_육손)
						and person_t.mibun != 신분_재야 and person_t.mibun != 신분_포로 and person_t.mibun != 신분_미등장 and person_t.mibun != 신분_미발견 and person_t.mibun != 신분_사망 and person_t.mibun != 신분_없음 and person_t.location == 군주.location and person_t.service == 군주.service)
						{
								pk::message_box(pk::u8encode("댁은 얼굴이 반반하니 초상집에 조문이나 가면 딱이겠군!"), 예형);
								pk::message_box(pk::u8encode(pk::format("뭣이오?", 군주_이름)), person_t);
								break;
						}
						//정욱
						else if ((person_t.get_id() == 무장_정욱 or person_t.get_id() == 무장_호거아 or person_t.get_id() == 무장_올돌골 or person_t.get_id() == 무장_사마가)
						and person_t.mibun != 신분_재야 and person_t.mibun != 신분_포로 and person_t.mibun != 신분_미등장 and person_t.mibun != 신분_미발견 and person_t.mibun != 신분_사망 and person_t.mibun != 신분_없음 and person_t.location == 군주.location and person_t.service == 군주.service)
						{
								pk::message_box(pk::u8encode("당신은 키가 크니 문이나 여닫는 문지기에 어울리겠군!"), 예형);
								pk::message_box(pk::u8encode(pk::format("뭐라?", 군주_이름)), person_t);
								break;
						}
						//장료
						else if ((person_t.get_id() == 무장_장료 or person_t.get_id() == 무장_주창 or person_t.get_id() == 무장_고순 or person_t.get_id() == 무장_관평 or person_t.get_id() == 무장_관흥 or person_t.get_id() == 무장_감녕) and person_t.mibun != 신분_재야 and person_t.mibun != 신분_포로 and person_t.mibun != 신분_미등장 and person_t.mibun != 신분_미발견 and person_t.mibun != 신분_사망 and person_t.mibun != 신분_없음 and person_t.location == 군주.location and person_t.service == 군주.service)
						{
								pk::message_box(pk::u8encode("당신은 북이나 징을 치면 딱이겠소!"), 예형);
								pk::message_box(pk::u8encode(pk::format("네 이놈을!", 군주_이름)), person_t);
								break;
						}
						//이전
						else if ((person_t.get_id() == 무장_이전 or person_t.get_id() == 무장_맹달 or person_t.get_id() == 무장_진궁 or person_t.get_id() == 무장_전풍 or person_t.get_id() == 무장_저수) and person_t.mibun != 신분_재야 and person_t.mibun != 신분_포로 and person_t.mibun != 신분_미등장 and person_t.mibun != 신분_미발견 and person_t.mibun != 신분_사망 and person_t.mibun != 신분_없음 and person_t.location == 군주.location and person_t.service == 군주.service)
						{
								pk::message_box(pk::u8encode("사방팔방 격문이나 전달할 인물이오!"), 예형);
								pk::message_box(pk::u8encode(pk::format("!!!", 군주_이름)), person_t);
								break;
						}
						//여건
						else if ((person_t.get_id() == 무장_여건 or person_t.get_id() == 무장_황개 or person_t.get_id() == 무장_손책 or person_t.get_id() == 무장_하후연 or person_t.get_id() == 무장_장포 or person_t.get_id() == 무장_기령) and person_t.mibun != 신분_재야 and person_t.mibun != 신분_포로 and person_t.mibun != 신분_미등장 and person_t.mibun != 신분_미발견 and person_t.mibun != 신분_사망 and person_t.mibun != 신분_없음 and person_t.location == 군주.location and person_t.service == 군주.service)
						{
								pk::message_box(pk::u8encode("대장간에서 칼이나 갈면 딱이겠군!"), 예형);
								pk::message_box(pk::u8encode(pk::format("뭐랏!!", 군주_이름)), person_t);
								break;
						}
						//만총
						else if ((person_t.get_id() == 무장_만총 or person_t.get_id() == 무장_축융 or person_t.get_id() == 무장_손상향 or person_t.get_id() == 무장_초선 or person_t.get_id() == 무장_봉기) and person_t.mibun != 신분_재야 and person_t.mibun != 신분_포로 and person_t.mibun != 신분_미등장 and person_t.mibun != 신분_미발견 and person_t.mibun != 신분_사망 and person_t.mibun != 신분_없음 and person_t.location == 군주.location and person_t.service == 군주.service)
						{
								pk::message_box(pk::u8encode("술상에 올릴 안주나 만드시오!"), 예형);
								pk::message_box(pk::u8encode(pk::format("뭐라고?!", 군주_이름)), person_t);
								break;
						}
						//서황
						else if ((person_t.get_id() == 무장_서황 or person_t.get_id() == 무장_주태 or person_t.get_id() == 무장_전위 or person_t.get_id() == 무장_호거아 or person_t.get_id() == 무장_문추 or person_t.get_id() == 무장_화웅) and person_t.mibun != 신분_재야 and person_t.mibun != 신분_포로 and person_t.mibun != 신분_미등장 and person_t.mibun != 신분_미발견 and person_t.mibun != 신분_사망 and person_t.mibun != 신분_없음 and person_t.location == 군주.location and person_t.service == 군주.service)
						{
								pk::message_box(pk::u8encode("과연 푸줏간에서 돼지나 도살 할 상이로다!"), 예형);
								pk::message_box(pk::u8encode(pk::format("으으!!", 군주_이름)), person_t);
								break;
						}
						//
						else if ((person_t.get_id() == 무장_장굉 or person_t.get_id() == 무장_간옹 or person_t.get_id() == 무장_미축 or person_t.get_id() == 무장_장송 or person_t.get_id() == 무장_원상) and person_t.mibun != 신분_재야 and person_t.mibun != 신분_포로 and person_t.mibun != 신분_미등장 and person_t.mibun != 신분_미발견 and person_t.mibun != 신분_사망 and person_t.mibun != 신분_없음 and person_t.location == 군주.location and person_t.service == 군주.service)
						{
								pk::message_box(pk::u8encode("할 수 있는게 없으니 시렁의 옷걸이요!"), 예형);
								pk::message_box(pk::u8encode(pk::format("하..", 군주_이름)), person_t);
								break;
						}
						

						//
						else if ((person_t.skill == 특기_명성 or person_t.skill == 특기_경국 or person_t.skill == 특기_시상 or person_t.skill == 특기_명경 or person_t.skill == 특기_주악 or person_t.skill == 특기_통찰) and person_t.mibun != 신분_재야 and person_t.mibun != 신분_포로 and person_t.mibun != 신분_미등장 and person_t.mibun != 신분_미발견 and person_t.mibun != 신분_사망 and person_t.mibun != 신분_없음 and person_t.location == 군주.location and person_t.service == 군주.service)
						{
								pk::message_box(pk::u8encode("얼굴이 반반하니 초상집에 조문이나 가면 딱이겠군!"), 예형);
								pk::message_box(pk::u8encode(pk::format("뭣이오?", 군주_이름)), person_t);
								break;
						}
						//
						else if ((person_t.skill == 특기_창장 or person_t.skill == 특기_극장 or person_t.skill == 특기_궁장 or person_t.skill == 특기_기장 or person_t.skill == 특기_수장 or person_t.skill == 특기_용장 or person_t.skill == 특기_신장) and person_t.mibun != 신분_재야 and person_t.mibun != 신분_포로 and person_t.mibun != 신분_미등장 and person_t.mibun != 신분_미발견 and person_t.mibun != 신분_사망 and person_t.mibun != 신분_없음 and person_t.location == 군주.location and person_t.service == 군주.service)
						{
								pk::message_box(pk::u8encode("당신은 북이나 징을 치면 딱이겠소!"), 예형);
								pk::message_box(pk::u8encode(pk::format("네 이놈을!", 군주_이름)), person_t);
								break;
						}
						//
						else if ((person_t.skill == 특기_규율 or person_t.skill == 특기_침착 or person_t.skill == 특기_공성 or person_t.skill == 특기_기각 or person_t.skill == 특기_운반 or person_t.skill == 특기_도주 or person_t.skill == 특기_비장 or person_t.skill == 특기_강행 or person_t.skill == 특기_행군 or person_t.skill == 특기_추진 or person_t.skill == 특기_조타 or person_t.skill == 특기_답파 or person_t.skill == 특기_신산 or person_t.skill == 특기_백출 or person_t.skill == 특기_귀모 or person_t.skill == 특기_연환 or person_t.skill == 특기_심모 or person_t.skill == 특기_반계 or person_t.skill == 특기_화공 or person_t.skill == 특기_언독 or person_t.skill == 특기_기략 or person_t.skill == 특기_궤계 or person_t.skill == 특기_허실 or person_t.skill == 특기_묘계 or person_t.skill == 특기_비책 or person_t.skill == 특기_간파 or person_t.skill == 특기_화신)and person_t.mibun != 신분_재야 and person_t.mibun != 신분_포로 and person_t.mibun != 신분_미등장 and person_t.mibun != 신분_미발견 and person_t.mibun != 신분_사망 and person_t.mibun != 신분_없음 and person_t.location == 군주.location and person_t.service == 군주.service)
						{
								pk::message_box(pk::u8encode("사방팔방 격문이나 전달할 인물이오!"), 예형);
								pk::message_box(pk::u8encode(pk::format("!!!", 군주_이름)), person_t);
								break;
						}
						//
						else if ((person_t.skill == 특기_소탕 or person_t.skill == 특기_위풍 or person_t.skill == 특기_앙양 or person_t.skill == 특기_연전 or person_t.skill == 특기_급습 or person_t.skill == 특기_강습 or person_t.skill == 특기_난전 or person_t.skill == 특기_매복)and person_t.mibun != 신분_재야 and person_t.mibun != 신분_포로 and person_t.mibun != 신분_미등장 and person_t.mibun != 신분_미발견 and person_t.mibun != 신분_사망 and person_t.mibun != 신분_없음 and person_t.location == 군주.location and person_t.service == 군주.service)
						{
								pk::message_box(pk::u8encode("대장간에서 칼이나 갈면 딱이겠군!"), 예형);
								pk::message_box(pk::u8encode(pk::format("뭐랏!!", 군주_이름)), person_t);
								break;
						}
						//
						else if ((person_t.skill == 특기_발명 or person_t.skill == 특기_조선 or person_t.skill == 특기_지도 or person_t.skill == 특기_안력 or person_t.skill == 특기_논객 or person_t.skill == 특기_부호 or person_t.skill == 특기_미도 or person_t.skill == 특기_징세 or person_t.skill == 특기_징수 or person_t.skill == 특기_내조) and person_t.mibun != 신분_재야 and person_t.mibun != 신분_포로 and person_t.mibun != 신분_미등장 and person_t.mibun != 신분_미발견 and person_t.mibun != 신분_사망 and person_t.mibun != 신분_없음 and person_t.location == 군주.location and person_t.service == 군주.service)
						{
								pk::message_box(pk::u8encode("술상에 올릴 안주나 만드시오!"), 예형);
								pk::message_box(pk::u8encode(pk::format("뭐라고?!", 군주_이름)), person_t);
								break;
						}
						//
						else if ((person_t.skill == 특기_해독 or person_t.skill == 특기_철벽 or person_t.skill == 특기_노발 or person_t.skill == 특기_등갑 or person_t.skill == 특기_강운 or person_t.skill == 특기_혈로 or person_t.skill == 특기_축성 or person_t.skill == 특기_둔전 or person_t.skill == 특기_능리 or person_t.skill == 특기_번식 or person_t.skill == 특기_투신 or person_t.skill == 특기_창신 or person_t.skill == 특기_극신 or person_t.skill == 특기_궁신 or person_t.skill == 특기_기신 or person_t.skill == 특기_공신 or person_t.skill == 특기_수신 or person_t.skill == 특기_패왕 or person_t.skill == 특기_질주 or person_t.skill == 특기_사수 or person_t.skill == 특기_맹장 or person_t.skill == 특기_호위) and person_t.mibun != 신분_재야 and person_t.mibun != 신분_포로 and person_t.mibun != 신분_미등장 and person_t.mibun != 신분_미발견 and person_t.mibun != 신분_사망 and person_t.mibun != 신분_없음 and person_t.location == 군주.location and person_t.service == 군주.service)
						{
								pk::message_box(pk::u8encode("과연 푸줏간에서 돼지나 도살 할 상이로다!"), 예형);
								pk::message_box(pk::u8encode(pk::format("으으!!", 군주_이름)), person_t);
								break;
						}
						//
						else if ((person_t.skill == 특기_요술 or person_t.skill == 특기_귀문 or person_t.skill == 특기_포박 or person_t.skill == 특기_정묘 or person_t.skill == 특기_강탈 or person_t.skill == 특기_심공 or person_t.skill == 특기_구축 or person_t.skill == 특기_사정 or person_t.skill == 특기_백마 or person_t.skill == 특기_보좌 or person_t.skill == 특기_불굴 or person_t.skill == 특기_금강 or person_t.skill == 특기_친오 or person_t.skill == 특기_친강 or person_t.skill == 특기_친월 or person_t.skill == 특기_친만 or person_t.skill == 특기_위압 or person_t.skill == 특기_인정 or person_t.skill == 특기_풍수 or person_t.skill == 특기_기원) and person_t.mibun != 신분_재야 and person_t.mibun != 신분_포로 and person_t.mibun != 신분_미등장 and person_t.mibun != 신분_미발견 and person_t.mibun != 신분_사망 and person_t.mibun != 신분_없음 and person_t.location == 군주.location and person_t.service == 군주.service)
						{
								pk::message_box(pk::u8encode("술만 쳐마시니 술통이오!"), 예형);
								pk::message_box(pk::u8encode(pk::format("뭐, 뭐라는거야!", 군주_이름)), person_t);
								break;
						}
						//
						else if (person_t.mibun != 신분_재야 and person_t.mibun != 신분_포로 and person_t.mibun != 신분_미등장 and person_t.mibun != 신분_미발견 and person_t.mibun != 신분_사망 and person_t.mibun != 신분_없음 and person_t.location == 군주.location and person_t.service == 군주.service)
						{
								pk::message_box(pk::u8encode("할 수 있는게 없으니 시렁의 옷걸이요!"), 예형);
								pk::message_box(pk::u8encode(pk::format("하..", 군주_이름)), person_t);
								break;
						}

					}

			}

			//신하 2
			switch (0)
			{

				case 0 :
					for (int person_id = 0; person_id < 무장_끝; person_id++)
					{
						pk::person@ person_t = pk::get_person(pk::rand(1100));

						//무장_장비
						if (person_t.get_id() == 무장_장비 and person_t.mibun != 신분_재야 and person_t.mibun != 신분_포로 and person_t.mibun != 신분_미등장 and person_t.mibun != 신분_미발견 and person_t.mibun != 신분_사망 and person_t.mibun != 신분_없음 and person_t.location == 군주.location and person_t.service == 군주.service)
						{
								pk::message_box(pk::u8encode("나는? 나는 뭐라 그럴건데?"), person_t);
								pk::message_box(pk::u8encode(pk::format("(예형이 장비를 무시한다.)", 군주_이름)), 예형);
								pk::message_box(pk::u8encode("아니, 나는 왜 무시하는건데?!"), person_t);
								break;
						}
						//강유
						else if (person_t.get_id() == 무장_강유 and person_t.mibun != 신분_재야 and person_t.mibun != 신분_포로 and person_t.mibun != 신분_미등장 and person_t.mibun != 신분_미발견 and person_t.mibun != 신분_사망 and person_t.mibun != 신분_없음 and person_t.location == 군주.location and person_t.service == 군주.service)
						{
								pk::message_box(pk::u8encode("당신은 융통성이 없으니 징수원이나 하면 그만이다!"), 예형);
								pk::message_box(pk::u8encode(pk::format("뭐랏?", 군주_이름)), person_t);
								break;
						}

						//항적
						else if (person_t.get_id() == 무장_항적 and person_t.mibun != 신분_재야 and person_t.mibun != 신분_포로 and person_t.mibun != 신분_미등장 and person_t.mibun != 신분_미발견 and person_t.mibun != 신분_사망 and person_t.mibun != 신분_없음 and person_t.location == 군주.location and person_t.service == 군주.service)
						{
								pk::message_box(pk::u8encode("!!!\n(예형이 항적의 눈을 슬쩍 피한다.)"), 예형);
								pk::message_box(pk::u8encode(pk::format("(항적이 예형을 향해 엄청난 살기를 뿜어내고 있다.)", 군주_이름)), person_t);
								break;
						}
						//순유
						else if ((person_t.get_id() == 무장_순유 or person_t.get_id() == 무장_황충 or person_t.get_id() == 무장_서서 or person_t.get_id() == 무장_법정 or person_t.get_id() == 무장_장소) and person_t.mibun != 신분_재야 and person_t.mibun != 신분_포로 and person_t.mibun != 신분_미등장 and person_t.mibun != 신분_미발견 and person_t.mibun != 신분_사망 and person_t.mibun != 신분_없음 and person_t.location == 군주.location and person_t.service == 군주.service)
						{
								pk::message_box(pk::u8encode("그리고 댁은 답답하니 분묘나 지키는 일에 합당하오!"), 예형);
								pk::message_box(pk::u8encode(pk::format("?!!", 군주_이름)), person_t);
								break;
						}
						//곽가
						else if ((person_t.get_id() == 무장_곽가 or person_t.get_id() == 무장_방통 or person_t.get_id() == 무장_소교 or person_t.get_id() == 무장_노숙 or person_t.get_id() == 무장_서서 or person_t.get_id() == 무장_유표 or person_t.get_id() == 무장_심배) and person_t.mibun != 신분_재야 and person_t.mibun != 신분_포로 and person_t.mibun != 신분_미등장 and person_t.mibun != 신분_미발견 and person_t.mibun != 신분_사망 and person_t.mibun != 신분_없음 and person_t.location == 군주.location and person_t.service == 군주.service)
						{
								pk::message_box(pk::u8encode("그리고 당신은 유행가 가사나 쓰면 딱이겠네!"), 예형);
								pk::message_box(pk::u8encode(pk::format("으으..", 군주_이름)), person_t);
								break;
						}
						//허저
						else if ((person_t.get_id() == 무장_허저 or person_t.get_id() == 무장_마초 or person_t.get_id() == 무장_마대 or person_t.get_id() == 무장_공손찬 or person_t.get_id() == 무장_마등 or person_t.get_id() == 무장_동탁 or person_t.get_id() == 무장_안량)
						and person_t.mibun != 신분_재야 and person_t.mibun != 신분_포로 and person_t.mibun != 신분_미등장 and person_t.mibun != 신분_미발견 and person_t.mibun != 신분_사망 and person_t.mibun != 신분_없음 and person_t.location == 군주.location and person_t.service == 군주.service)
						{
								pk::message_box(pk::u8encode("또한 댁은 소나 말의 똥이나 치우시게!"), 예형);
								pk::message_box(pk::u8encode(pk::format("뚫린 입이라고!", 군주_이름)), person_t);
								break;
						}
						//악진
						else if ((person_t.get_id() == 무장_악진 or person_t.get_id() == 무장_마량 or person_t.get_id() == 무장_진군 or person_t.get_id() == 무장_대교 or person_t.get_id() == 무장_태사자) and person_t.mibun != 신분_재야 and person_t.mibun != 신분_포로 and person_t.mibun != 신분_미등장 and person_t.mibun != 신분_미발견 and person_t.mibun != 신분_사망 and person_t.mibun != 신분_없음 and person_t.location == 군주.location and person_t.service == 군주.service)
						{
								pk::message_box(pk::u8encode("또한 댁은 문서철을 뒤적이며 조서나 읽으시오!"), 예형);
								pk::message_box(pk::u8encode(pk::format("이, 이 녀석!", 군주_이름)), person_t);
								break;
						}
						//우금
						else if ((person_t.get_id() == 무장_우금 or person_t.get_id() == 무장_여몽 or person_t.get_id() == 무장_관평 or person_t.get_id() == 무장_관색 or person_t.get_id() == 무장_유봉) and person_t.mibun != 신분_재야 and person_t.mibun != 신분_포로 and person_t.mibun != 신분_미등장 and person_t.mibun != 신분_미발견 and person_t.mibun != 신분_사망 and person_t.mibun != 신분_없음 and person_t.location == 군주.location and person_t.service == 군주.service)
						{
								pk::message_box(pk::u8encode("그리고 댁은 판자로 담이나 쌓을 인물이지!"), 예형);
								pk::message_box(pk::u8encode(pk::format("허허..", 군주_이름)), person_t);
								break;
						}
						//조인
						else if ((person_t.get_id() == 무장_조인 or person_t.get_id() == 무장_위연 or person_t.get_id() == 무장_장소 or person_t.get_id() == 무장_원소 or person_t.get_id() == 무장_원술 or person_t.get_id() == 무장_장보)
						and person_t.mibun != 신분_재야 and person_t.mibun != 신분_포로 and person_t.mibun != 신분_미등장 and person_t.mibun != 신분_미발견 and person_t.mibun != 신분_사망 and person_t.mibun != 신분_없음 and person_t.location == 군주.location and person_t.service == 군주.service)
						{
								pk::message_box(pk::u8encode("그리고 당신은 금만 밝히니 요전태수로 불리면 딱이오!"), 예형);
								pk::message_box(pk::u8encode(pk::format("뭐라고?!", 군주_이름)), person_t);
								break;
						}

						//
						else if ((person_t.get_id() == 무장_제갈근 or person_t.get_id() == 무장_장굉 or person_t.get_id() == 무장_손권 or person_t.get_id() == 무장_타사대왕 or person_t.get_id() == 무장_유선 or grade_name == "하급")
						 and person_t.mibun != 신분_재야 and person_t.mibun != 신분_포로 and person_t.mibun != 신분_미등장 and person_t.mibun != 신분_미발견 and person_t.mibun != 신분_사망 and person_t.mibun != 신분_없음 and person_t.location == 군주.location and person_t.service == 군주.service)
						{
								pk::message_box(pk::u8encode("또한 당신은 밥만 축내니 밥주머니요!"), 예형);
								pk::message_box(pk::u8encode(pk::format("뭐, 뭐라고?", 군주_이름)), person_t);
								break;
						}
						//
						else if ((person_t.get_id() == 무장_화웅 or person_t.get_id() == 무장_맹획 or person_t.get_id() == 무장_대래동주 or person_t.get_id() == 무장_원담)
						 and person_t.mibun != 신분_재야 and person_t.mibun != 신분_포로 and person_t.mibun != 신분_미등장 and person_t.mibun != 신분_미발견 and person_t.mibun != 신분_사망 and person_t.mibun != 신분_없음 and person_t.location == 군주.location and person_t.service == 군주.service)
						{
								pk::message_box(pk::u8encode("그리고 당신은 고기만 퍼먹으니 고기자루에 불과하오!"), 예형);
								pk::message_box(pk::u8encode(pk::format("이 자식이!", 군주_이름)), person_t);
								break;
						}
						
						//
						else if ((person_t.skill == 특기_규율 or person_t.skill == 특기_침착 or person_t.skill == 특기_공성 or person_t.skill == 특기_기각 or person_t.skill == 특기_운반 or person_t.skill == 특기_도주 or person_t.skill == 특기_비장 or person_t.skill == 특기_강행 or person_t.skill == 특기_행군 or person_t.skill == 특기_추진 or person_t.skill == 특기_조타 or person_t.skill == 특기_답파 or person_t.skill == 특기_신산 or person_t.skill == 특기_백출 or person_t.skill == 특기_귀모 or person_t.skill == 특기_연환 or person_t.skill == 특기_심모 or person_t.skill == 특기_반계 or person_t.skill == 특기_화공 or person_t.skill == 특기_언독 or person_t.skill == 특기_기략 or person_t.skill == 특기_궤계 or person_t.skill == 특기_허실 or person_t.skill == 특기_묘계 or person_t.skill == 특기_비책 or person_t.skill == 특기_간파 or person_t.skill == 특기_통찰 or person_t.skill == 특기_화신)and person_t.mibun != 신분_재야 and person_t.mibun != 신분_포로 and person_t.mibun != 신분_미등장 and person_t.mibun != 신분_미발견 and person_t.mibun != 신분_사망 and person_t.mibun != 신분_없음 and person_t.location == 군주.location and person_t.service == 군주.service)
						{
								pk::message_box(pk::u8encode("당신은 융통성이 없으니 징수원이나 하면 그만이다!"), 예형);
								pk::message_box(pk::u8encode(pk::format("뭐랏?", 군주_이름)), person_t);
								break;
						}
						//
						else if ((person_t.skill == 특기_창장 or person_t.skill == 특기_극장 or person_t.skill == 특기_궁장 or person_t.skill == 특기_기장 or person_t.skill == 특기_수장 or person_t.skill == 특기_용장 or person_t.skill == 특기_신장) and person_t.mibun != 신분_재야 and person_t.mibun != 신분_포로 and person_t.mibun != 신분_미등장 and person_t.mibun != 신분_미발견 and person_t.mibun != 신분_사망 and person_t.mibun != 신분_없음 and person_t.location == 군주.location and person_t.service == 군주.service)
						{
								pk::message_box(pk::u8encode("그리고 댁은 답답하니 분묘나 지키는 일에 합당하오!"), 예형);
								pk::message_box(pk::u8encode(pk::format("?!!", 군주_이름)), person_t);
								break;
						}
						//
						else if ((person_t.skill == 특기_명성 or person_t.skill == 특기_경국 or person_t.skill == 특기_시상 or person_t.skill == 특기_명경 or person_t.skill == 특기_주악) and person_t.mibun != 신분_재야 and person_t.mibun != 신분_포로 and person_t.mibun != 신분_미등장 and person_t.mibun != 신분_미발견 and person_t.mibun != 신분_사망 and person_t.mibun != 신분_없음 and person_t.location == 군주.location and person_t.service == 군주.service)
						{
								pk::message_box(pk::u8encode("그리고 당신은 유행가 가사나 쓰면 딱이겠네!"), 예형);
								pk::message_box(pk::u8encode(pk::format("으으..", 군주_이름)), person_t);
								break;
						}
						//
						else if ((person_t.skill == 특기_소탕 or person_t.skill == 특기_위풍 or person_t.skill == 특기_앙양 or person_t.skill == 특기_연전 or person_t.skill == 특기_급습 or person_t.skill == 특기_강습 or person_t.skill == 특기_난전 or person_t.skill == 특기_매복 or person_t.skill == 특기_번식)and person_t.mibun != 신분_재야 and person_t.mibun != 신분_포로 and person_t.mibun != 신분_미등장 and person_t.mibun != 신분_미발견 and person_t.mibun != 신분_사망 and person_t.mibun != 신분_없음 and person_t.location == 군주.location and person_t.service == 군주.service)
						{
								pk::message_box(pk::u8encode("또한 댁은 소나 말의 똥이나 치우시게!"), 예형);
								pk::message_box(pk::u8encode(pk::format("뚫린 입이라고!", 군주_이름)), person_t);
								break;
						}
						//
						else if ((person_t.skill == 특기_발명 or person_t.skill == 특기_조선 or person_t.skill == 특기_지도 or person_t.skill == 특기_안력 or person_t.skill == 특기_논객 or person_t.skill == 특기_부호 or person_t.skill == 특기_미도 or person_t.skill == 특기_징세 or person_t.skill == 특기_징수 or person_t.skill == 특기_내조) and person_t.mibun != 신분_재야 and person_t.mibun != 신분_포로 and person_t.mibun != 신분_미등장 and person_t.mibun != 신분_미발견 and person_t.mibun != 신분_사망 and person_t.mibun != 신분_없음 and person_t.location == 군주.location and person_t.service == 군주.service)
						{
								pk::message_box(pk::u8encode("또한 댁은 문서철을 뒤적이며 조서나 읽으시오!"), 예형);
								pk::message_box(pk::u8encode(pk::format("이, 이 녀석!", 군주_이름)), person_t);
								break;
						}
						//
						else if ((person_t.skill == 특기_해독 or person_t.skill == 특기_철벽 or person_t.skill == 특기_노발 or person_t.skill == 특기_등갑 or person_t.skill == 특기_강운 or person_t.skill == 특기_혈로 or person_t.skill == 특기_축성 or person_t.skill == 특기_투신 or person_t.skill == 특기_창신 or person_t.skill == 특기_극신 or person_t.skill == 특기_궁신 or person_t.skill == 특기_기신 or person_t.skill == 특기_공신 or person_t.skill == 특기_수신 or person_t.skill == 특기_패왕 or person_t.skill == 특기_질주 or person_t.skill == 특기_사수 or person_t.skill == 특기_맹장 or person_t.skill == 특기_호위) and person_t.mibun != 신분_재야 and person_t.mibun != 신분_포로 and person_t.mibun != 신분_미등장 and person_t.mibun != 신분_미발견 and person_t.mibun != 신분_사망 and person_t.mibun != 신분_없음 and person_t.location == 군주.location and person_t.service == 군주.service)
						{
								pk::message_box(pk::u8encode("그리고 댁은 판자로 담이나 쌓을 인물이지!"), 예형);
								pk::message_box(pk::u8encode(pk::format("허허..", 군주_이름)), person_t);
								break;
						}
						//
						else if ((person_t.skill == 특기_둔전 or person_t.skill == 특기_능리 or person_t.skill == 특기_요술 or person_t.skill == 특기_귀문 or person_t.skill == 특기_풍수 or person_t.skill == 특기_기원) and person_t.mibun != 신분_재야 and person_t.mibun != 신분_포로 and person_t.mibun != 신분_미등장 and person_t.mibun != 신분_미발견 and person_t.mibun != 신분_사망 and person_t.mibun != 신분_없음 and person_t.location == 군주.location and person_t.service == 군주.service)
						{
								pk::message_box(pk::u8encode("그리고 당신은 금만 밝히니 요전태수로 불리면 딱이오!"), 예형);
								pk::message_box(pk::u8encode(pk::format("뭐라고?!", 군주_이름)), person_t);
								break;
						}
						//
						else if ((person_t.skill == 특기_포박 or person_t.skill == 특기_정묘 or person_t.skill == 특기_강탈 or person_t.skill == 특기_심공 or person_t.skill == 특기_구축 or person_t.skill == 특기_사정 or person_t.skill == 특기_백마 or person_t.skill == 특기_보좌 or person_t.skill == 특기_불굴 or person_t.skill == 특기_금강 or person_t.skill == 특기_위압 or person_t.skill == 특기_인정 or person_t.skill == 특기_친오 or person_t.skill == 특기_친강 or person_t.skill == 특기_친월 or person_t.skill == 특기_친만) and person_t.mibun != 신분_재야 and person_t.mibun != 신분_포로 and person_t.mibun != 신분_미등장 and person_t.mibun != 신분_미발견 and person_t.mibun != 신분_사망 and person_t.mibun != 신분_없음 and person_t.location == 군주.location and person_t.service == 군주.service)
						{
								pk::message_box(pk::u8encode("그리고 당신은 고기만 퍼먹으니 고기자루에 불과하오!"), 예형);
								pk::message_box(pk::u8encode(pk::format("이 자식이!", 군주_이름)), person_t);
								break;
						}
						else if (person_t.mibun != 신분_재야 and person_t.mibun != 신분_포로 and person_t.mibun != 신분_미등장 and person_t.mibun != 신분_미발견 and person_t.mibun != 신분_사망 and person_t.mibun != 신분_없음 and person_t.location == 군주.location and person_t.service == 군주.service)
						{
								pk::message_box(pk::u8encode("또한 당신은 밥만 축내니 밥주머니요!"), 예형);
								pk::message_box(pk::u8encode(pk::format("뭐, 뭐라고?", 군주_이름)), person_t);
								break;
						}
						
						



					}
			}

			int q = pk::rand(3);

			//군주 조조 유비 손권 엄백호

			//유비
			if (군주.get_id() == 무장_유비 and q == 1)
			{
				pk::message_box(pk::u8encode("탁현의 시장바닥에서 짚신이나 만들것이지\n\n어찌 그대는 군을 일으켜\n한조를 능멸하려 하는가?"), 예형);
				pk::message_box(pk::u8encode("예형, 이 불초 유비는 중산정왕 유승의 먼 후손으로.."), 군주);
				pk::cutin(20);
				pk::message_box(pk::u8encode("갈! 이 세상에 널린 게 유씨거늘!"), 예형);
				pk::message_box(pk::u8encode("?!"), 군주);
			}

			//조조
			else if ((군주.get_id() == 무장_조조 or 군주.get_id() == 무장_조비) and q == 1)
			{
				pk::message_box(pk::u8encode("다들 가만히 있거라."), 군주);
				pk::message_box(pk::u8encode("아이고.. 아이고.."), 예형);
				pk::message_box(pk::u8encode("흠. 정평. 이번엔 왜 또 갑자기 우는 것이오?"), 군주);
				pk::cutin(20);
				pk::message_box(pk::u8encode("곧 목이 달아날 시체 사이에 있는\n내 처지가 딱해서 그렇소이다!"), 예형);
				pk::message_box(pk::u8encode("?!"), 군주);
			}


			//손권
			else if (군주.get_id() == 무장_손권 and q == 1)
			{
				pk::message_box(pk::u8encode("(...이 자를 대체 어떻게 해야할까?)"), 군주);
				pk::message_box(pk::u8encode("이 몸을 어떻게 해야 할까?"), 예형);
				pk::message_box(pk::u8encode("?!"), 군주);
				pk::cutin(20);
				pk::message_box(pk::u8encode("얼굴에 다 드러난다, 이 쥐같은 놈아!"), 예형);
			}
			
			//엄백호
			else if (군주.get_id() == 무장_엄백호 and q == 1)
			{
				pk::message_box(pk::u8encode("덕왕이라니.. 너무 웃겨서 참칭이라고 할 수도 없다!"), 예형);
				pk::message_box(pk::u8encode("아, 아니 나는!"), 군주);
				pk::cutin(20);
				pk::message_box(pk::u8encode("하하하!"), 예형);
			}				

			else
			{
				pk::message_box(pk::u8encode("아무리 좋게 말을 해주려 해도, 너희들은 결국 역적 무리들 뿐이다!"), 예형);
				pk::message_box(pk::u8encode("아니다! 우, 우리는!!"), 군주);
				pk::cutin(20);
				pk::message_box(pk::u8encode("그럼 무엇이냐?"), 예형);
			}


			array<string> 예형_확인창 = {
				pk::u8encode("설전을 벌인다."),
				pk::u8encode("무시한다."),
				pk::u8encode("처형한다.")
			};

			int n = pk::choose(pk::u8encode("예형과 설전을 벌이겠습니까?"), 예형_확인창);

			switch (n)
			{
			case 0:

				if (군사.get_id() == -1)
				{
					pk::message_box(pk::u8encode("'..군사가 없으니 나라도 나서야겠어'"), 군주);
					debate_result = pk::debate(군주, 예형, pk::is_player_controlled(군주), false, false, true).first;
				}			
				else
				{
					if (군사.get_id() == 예형_신무장번호)
					{
						pk::message_box(pk::u8encode("'..내가 왜 이런 치를 군사로 임명하였을까'"), 군주);
						debate_result = pk::debate(군주, 예형, pk::is_player_controlled(군주), false, false, true).first;
					}
					else if (군사.get_id() == 무장_제갈량)
					{
						pk::message_box(pk::u8encode("길평, 당신은 이 공명이 상대하도록 하겠습니다."), 군사);
						pk::message_box(pk::u8encode("오.. 와룡이신가?"), 예형);
						debate_result = pk::debate(군사, 예형, pk::is_player_controlled(군사), false, false, true).first;							
					}
					else if (군사.get_id() == 무장_방통)
					{
						pk::message_box(pk::u8encode("예 선생, 방통입니다."), 군사);
						pk::message_box(pk::u8encode("봉추가 나오시겠다?"), 예형);
						debate_result = pk::debate(군사, 예형, pk::is_player_controlled(군사), false, false, true).first;							
					}
					else if (군사.get_id() == 무장_사마의)
					{
						pk::message_box(pk::u8encode("제가 이것을 치우도록 하겠습니다."), 군사);
						pk::message_box(pk::u8encode("하하하하"), 예형);
						debate_result = pk::debate(군사, 예형, pk::is_player_controlled(군사), false, false, true).first;							
					}
					else if (군사.get_id() == 무장_순욱)
					{
						pk::message_box(pk::u8encode("소생, 순 문약입니다."), 군사);
						pk::message_box(pk::u8encode("상가에 조문 아직 안 갔소?"), 예형);
						debate_result = pk::debate(군사, 예형, pk::is_player_controlled(군사), false, false, true).first;							
					}
					else if (군사.get_id() == 무장_공융)
					{
						pk::message_box(pk::u8encode("아우."), 군사);
						pk::message_box(pk::u8encode("형님도 똑같소!"), 예형);
						debate_result = pk::debate(군사, 예형, pk::is_player_controlled(군사), false, false, true).first;							
					}
					else if (군사.get_id() == 무장_양수)
					{
						pk::message_box(pk::u8encode("형님! 그만하십시오!"), 군사);
						pk::message_box(pk::u8encode("싫다!"), 예형);
						debate_result = pk::debate(군사, 예형, pk::is_player_controlled(군사), false, false, true).first;							
					}
					else
					{
						pk::message_box(pk::u8encode(pk::format("길평, 군사 {}입니다. 어찌 그런 말들을 하십니까?", 군사_이름)), 군사);
						pk::message_box(pk::u8encode("흥! 천하의 역적 무리들 같으니!!"), 예형);
						debate_result = pk::debate(군사, 예형, pk::is_player_controlled(군사), false, false, true).first;
					}
				}



				if (debate_result == 0)
						{
							pk::play_sfx(13,100);
							switch (pk::rand(3))
							{
								case 0	:	pk::message_box(pk::u8encode("할 말은 이제 다 한건가?"), 군주); break;
								case 1	:	pk::message_box(pk::u8encode("이제 돌아가시게."), 군주); break;
								case 2	:	pk::message_box(pk::u8encode("잘 알아들었으면 이제 언행을 주의하도록 하게."), 군주); break;
								case 3	:	pk::message_box(pk::u8encode("이번엔 이 정도로 해 주겠네."), 군주); break;

							}
							switch (pk::rand(14))
							{
								case 0	:	pk::message_box(pk::u8encode("흠.. 과연."), 예형); break;
								case 1	:	pk::message_box(pk::u8encode("쳇.. 방심해버렸군."), 예형); break;
								case 2	:	pk::message_box(pk::u8encode("오늘은 여기까지 하겠소!"), 예형); break;
								case 3	:	pk::message_box(pk::u8encode("에이이잇!"), 예형); break;
								case 4	:	pk::message_box(pk::u8encode("으으윽.."), 예형); break;
								case 5	:	pk::message_box(pk::u8encode("...흥!"), 예형); break;
								case 6	:	pk::message_box(pk::u8encode("...오늘은 여기서 물러나야겠군."), 예형); break;
								case 7	:	pk::message_box(pk::u8encode("흠.."), 예형); break;
								case 8	:	pk::message_box(pk::u8encode("..으으"), 예형); break;
								case 9	:	pk::message_box(pk::u8encode("...에잇!"), 예형); break;
								case 10	:	pk::message_box(pk::u8encode("..오늘은 그만 물러가주지!"), 예형); break;
								case 11	:	pk::message_box(pk::u8encode("빨래를 하다 와서 이만!"), 예형); break;
								case 12	:	pk::message_box(pk::u8encode("..아차차! 밥을 짓다 와서 이만 실례하겠네!"), 예형); break;
								case 13	:	pk::message_box(pk::u8encode("..만만치 않구만!"), 예형); break;
							}
							pk::play_sfx(2,100);
							예형.loyalty = 120;
							pk::message_box(pk::u8encode(pk::format("예형의 충성도가 \x1b[1x100\x1b[0x이 되었습니다.", 예형.loyalty)));
							pk::message_box(pk::u8encode(pk::format("기교 포인트가 \x1b[1x{}\x1b[0x만큼 증가했습니다.", tp)));
							pk::add_tp(예형_세력, tp, 도시.get_pos());
						}
				else //설전 패배
				{
					pk::play_sfx(14,100);
					if (군사.get_id() == -1)
					{
						switch (pk::rand(3))
						{
							case 0	:	pk::message_box(pk::u8encode("으으.. 분하다!"), 군주); break;
							case 1	:	pk::message_box(pk::u8encode("..왜 내가 이런 부하를"), 군주); break;
							case 2	:	pk::message_box(pk::u8encode("져버렸다.."), 군주); break;
						}
					}
					else
					{
						switch (pk::rand(3))
						{
							case 0	:	pk::message_box(pk::u8encode("면목이 없습니다.."), 군사); break;
							case 1	:	pk::message_box(pk::u8encode("죄송합니다, 주군."), 군사); break;
							case 2	:	pk::message_box(pk::u8encode("..."), 군사); break;
						}
					}
					switch (pk::rand(14))
					{
						case 0	:	pk::message_box(pk::u8encode(pk::format("왜 설전을 건 거야?", 군주_이름)), 예형); break;
						case 1	:	pk::message_box(pk::u8encode(pk::format("말 솜씨도 정말 형편없군!", 군주_이름)), 예형); break;
						case 2	:	pk::message_box(pk::u8encode(pk::format("옷걸이.. 고기자루.. 밥주머니.. 술독..", 군주_이름)), 예형); break;
						case 3	:	pk::message_box(pk::u8encode(pk::format("흥!", 군주_이름)), 예형); break;
						case 4	:	pk::message_box(pk::u8encode(pk::format("푸하하하", 군주_이름)), 예형); break;
						case 5	:	pk::message_box(pk::u8encode(pk::format("쯧쯧..", 군주_이름)), 예형); break;
						case 6	:	pk::message_box(pk::u8encode(pk::format("하던 일이나 계속 하시게!", 군주_이름)), 예형); break;
						case 7	:	pk::message_box(pk::u8encode(pk::format("흥. 이 몸은 이만!", 군주_이름)), 예형); break;
						case 8	:	pk::message_box(pk::u8encode(pk::format("이제 내 말을 이해하겠는가?", 군주_이름)), 예형); break;
						case 9	:	pk::message_box(pk::u8encode(pk::format("훗!", 군주_이름)), 예형); break;
						case 10	:	pk::message_box(pk::u8encode(pk::format("술이나 먹으러 갈까나?", 군주_이름)), 예형); break;
						case 11	:	pk::message_box(pk::u8encode(pk::format("오늘 저녁은 고기나 먹어야겠군!", 군주_이름)), 예형); break;
						case 12	:	pk::message_box(pk::u8encode(pk::format("하아암", 군주_이름)), 예형); break;
						case 13	:	pk::message_box(pk::u8encode(pk::format("이딴 말솜씨로 싸움걸지 말라고!", 군주_이름)), 예형); break;

					}
					if (예형.loyalty >= 70)
					{예형.loyalty -= pk::rand(3);}
					else if (예형.loyalty < 70)
					{예형.loyalty -= pk::rand(2);}

					pk::message_box(pk::u8encode(pk::format("예형의 충성도가 \x1b[24x{}\x1b[0x(이)가 되었습니다.", 예형.loyalty)));
				}
				break;

			case 1: //설전 거절
				pk::play_sfx(10,100);
				switch (pk::rand(10))
				{
					case 0	:	pk::message_box(pk::u8encode(pk::format("흥. 딱히 할 말도 없을테지.", 군주_이름)), 예형); break;
					case 1	:	pk::message_box(pk::u8encode(pk::format("옷걸이.. 고기자루.. 밥주머니.. 술독..", 군주_이름)), 예형); break;
					case 2	:	pk::message_box(pk::u8encode(pk::format("흥!", 군주_이름)), 예형); break;
					case 3	:	pk::message_box(pk::u8encode(pk::format("푸하하하", 군주_이름)), 예형); break;
					case 4	:	pk::message_box(pk::u8encode(pk::format("쯧..", 군주_이름)), 예형); break;
					case 5	:	pk::message_box(pk::u8encode(pk::format("하던 일이나 계속 하시게!", 군주_이름)), 예형); break;
					case 6	:	pk::message_box(pk::u8encode(pk::format("흥. 이 몸은 이만!", 군주_이름)), 예형); break;
					case 7	:	pk::message_box(pk::u8encode(pk::format("쯧쯧쯧!", 군주_이름)), 예형); break;
					case 8	:	pk::message_box(pk::u8encode(pk::format("술이나 먹으러 갈까나?", 군주_이름)), 예형); break;
					case 9	:	pk::message_box(pk::u8encode(pk::format("오늘 저녁은 고기나 먹어야겠군!", 군주_이름)), 예형); break;

				}

				if (예형.loyalty >= 70)
				{예형.loyalty -= pk::rand(3);}
				else if (예형.loyalty < 70)
				{예형.loyalty -= pk::rand(2);}

				pk::message_box(pk::u8encode(pk::format("예형의 충성도가 \x1b[24x{}\x1b[0x(이)가 되었습니다.", 예형.loyalty)));
				break;

			case 2: //예형 처형
				pk::message_box(pk::u8encode(pk::format(".. 도저히 못 참겠군.", 군주_이름)), 군주);
				switch (pk::rand(3))
				{
					case 0	:	pk::message_box(pk::u8encode(pk::format("하하하하.. \x1b[1x{}\x1b[0x놈들아! 너희들은 모두 한조의 역적들이다!!", 군주_이름)), 예형); break;
					case 1	:	pk::message_box(pk::u8encode(pk::format("나는 비록 쥐새끼지만, 너네들은 모두\n똥통 속 구더기가 아닌가!", 군주_이름)), 예형); break;
					case 2	:	pk::message_box(pk::u8encode(pk::format("나조차 감당을 못 하면서\n어찌 천하를 논할 것인가!", 군주_이름)), 예형); break;

				}
				pk::message_box(pk::u8encode(pk::format("여봐라! 오늘이 예 선생의 마지막 날이니라!", 군주_이름)), 군주);
				pk::cutin(15);
				예형.mibun = 신분_사망;
				pk::play_sfx(5,100);
				pk::message_box(pk::u8encode(pk::format("군주 \x1b[1x{}\x1b[0x, 예형을 처형했습니다.", 군주_이름)));
				break;
			}
			pk::fade(0);
			pk::sleep();
			pk::background(-1);
			pk::fade(255);			
		}
	}

	Main main;
}