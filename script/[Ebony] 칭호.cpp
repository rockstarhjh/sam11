namespace Ebony_칭호

/*
칭호기능 by MUSSO
기마책사님 '19.12.9 버전 읽기수정_패시브특기 추가
*/

{

	// ================ CUSTOMIZE ================


		const bool 고유칭호_사용 = true;
		const int 획득공적_0 = 15000;	// 1차 고유칭호 요구 공적
		const int 획득공적_1 = 30000;	// 2차 고유칭호 요구 공적
		// const bool 자_공백_추가 = false;	// 항상 읽기란을 사용하기 위해 모든 무장 자에 빈칸을 강제로 추가.
		const bool Ebony_신무장_패키지_사용여부 = true;	// 에보니 신무장 패키지 사용하지 않으시면 false로 놓고 사용하세요.


	// ===========================================


	class Main
	{

        Main()
		{
            pk::bind(102, pk::trigger102_t(onGameInit));
            pk::bind(111, pk::trigger111_t(onTurnStart));
			add_menu();
			xml();
        }
        int mode = 0;
		int 추가특기_표시 = 0;

        void onGameInit()
        {character_title();}
        void onTurnStart(pk::force@ force)
		{character_title();}

		void add_menu()
		{
			pk::menu_item item;
			item.menu = 2;
			item.is_enabled = pk::menu_item_is_enabled_t(isEnabled);
			item.get_text = pk::menu_item_get_text_t(getText);
			item.get_desc = pk::menu_item_get_desc_t(getDesc);
			item.handler = pk::menu_item_handler_t(handler);
			pk::add_menu_item(item);
		}

		bool isEnabled()
		{
			return true;
		}

		string getText()
		{
			if (추가특기_표시 == 0) return pk::u8encode("특기표시");
			return pk::u8encode("칭호표시");
		}

		string getDesc()
		{
			if (추가특기_표시 == 0) return pk::u8encode("선택하면 성명, 자읽기 란에 \x1b[1x추가 특기\x1b[0x를 표시합니다.");
			return pk::u8encode("선택하면 성명, 자읽기 란에 \x1b[1x칭호\x1b[0x를 표시합니다.");
		}

		bool handler()
		{

			if(추가특기_표시 == 0) 추가특기_표시 = 1;
			else if(추가특기_표시 == 1) 추가특기_표시 = 0;

			character_title();
			return true;
		}


        void character_title()
        {
			for (int person_id = 0; person_id < 무장_끝; person_id++)
			{
				if (추가특기_표시 == 0)
				{

					pk::person@ person_t = pk::get_person(person_id);

					string grade_color;
					string grade_name;
					string character_title;

					if (person_t !is null)
					{

						// 하급 \x1b[25x 회색
						// 우수 \x1b[28x 녹색
						// 영웅 \x1b[32x 파란색
						// 전설 \x1b[27x 주황색
						// 전설+ \x1b[29x 빨간색

						int 무장능력_최고_매력제외 = 0;
						int 무장능력_최저_매력제외= 0;
						int 무장능력_최고 = 0;
						int 무장능력_최저 = 0;
						int 무장능력_최고_통무 = 0;
						int 무장능력_최고_통지 = 0;
						int 무장능력_최고_지정 = 0;
						int 무장능력_평균_통무지정 = 0;
						int 무장능력_평균_통지정매 = 0;
						int 무장능력_평균_통지정 = 0;
						int 무장능력_평균_통무 = 0;
						int 무장능력_평균_통지 = 0;
						int 무장능력_평균_지정 = 0;
						int 무장능력_평균_정매 = 0;
						int 무장능력_최고_평균_통무통지지정 = 0;

						무장능력_최고_매력제외 += int (pk::max(person_t.stat[무장능력_통솔], person_t.stat[무장능력_무력], person_t.stat[무장능력_지력], person_t.stat[무장능력_정치]));
						무장능력_최저_매력제외 += int (pk::min(person_t.stat[무장능력_통솔], person_t.stat[무장능력_무력], person_t.stat[무장능력_지력], person_t.stat[무장능력_정치]));
						무장능력_최고 += int (pk::max(무장능력_최고_매력제외, person_t.stat[무장능력_매력]));
						무장능력_최저 += int (pk::min(무장능력_최저_매력제외, person_t.stat[무장능력_매력]));
						무장능력_최고_통무 += int (pk::max(person_t.stat[무장능력_통솔], person_t.stat[무장능력_무력]));
						무장능력_최고_통지 += int (pk::max(person_t.stat[무장능력_통솔], person_t.stat[무장능력_지력]));
						무장능력_최고_지정 += int (pk::max(person_t.stat[무장능력_지력], person_t.stat[무장능력_정치]));
						무장능력_평균_통무지정 += int ((person_t.stat[무장능력_통솔] + person_t.stat[무장능력_무력] + person_t.stat[무장능력_지력] + person_t.stat[무장능력_정치]) * 0.25f);
						무장능력_평균_통지정매 += int ((person_t.stat[무장능력_통솔] + person_t.stat[무장능력_지력] + person_t.stat[무장능력_정치] + person_t.stat[무장능력_매력]) * 0.25f);
						무장능력_평균_통지정 += int ((person_t.stat[무장능력_통솔] + person_t.stat[무장능력_지력] + person_t.stat[무장능력_정치]) * 0.333f);
						무장능력_평균_통무 += int ((person_t.stat[무장능력_통솔] + person_t.stat[무장능력_무력]) * 0.5f);
						무장능력_평균_통지 += int ((person_t.stat[무장능력_통솔] + person_t.stat[무장능력_지력]) * 0.5f);
						무장능력_평균_지정 += int ((person_t.stat[무장능력_지력] + person_t.stat[무장능력_정치]) * 0.5f);
						무장능력_평균_정매 += int ((person_t.stat[무장능력_정치] + person_t.stat[무장능력_매력]) * 0.5f);
						무장능력_최고_평균_통무통지지정 += int (pk::max(무장능력_평균_통무, 무장능력_평균_통지, 무장능력_평균_지정));

						// 등급 분류 시작
						if (무장능력_최고 >= 100 or 무장능력_평균_통무지정 >= 92 or 무장능력_최고_평균_통무통지지정 >= 97)
						{
							grade_color = "\x1b[29x";
							grade_name = "전설+";
						}

						else if (무장능력_최고 >= 97 or 무장능력_평균_통무지정 >= 89 or 무장능력_최고_평균_통무통지지정 >= 92)
						{
							grade_color = "\x1b[27x";
							grade_name = "전설";
						}

						else if (무장능력_최고 >= 85 or 무장능력_평균_통무지정 >= 77 or 무장능력_최고_평균_통무통지지정 >= 82)
						{
							grade_color = "\x1b[32x";
							grade_name = "영웅";
						}

						else if (무장능력_최고 >= 73 or 무장능력_평균_통무지정 >= 65 or 무장능력_최고_평균_통무통지지정 >= 70)
						{
							grade_color = "\x1b[28x";
							grade_name = "우수";
						}

						else if (무장능력_최고 < 60)
						{
							grade_color = "\x1b[25x";
							grade_name = "하급";
						}

						else
						{
							grade_name = "일반";
						}
						// 등급 분류 끝

						// 칭호 시작
						// 특정 스탯 70이상
						//명사

						//무관
						if (pk::max(무장능력_평균_통무,무장능력_평균_통지) * 1.1f > 무장능력_최고_지정)
						{character_title = "무관";}

						//문관
						if (pk::max(무장능력_평균_통무,무장능력_평균_통지) * 1.1f <= 무장능력_최고_지정)
						{character_title = "문관";}

						if (무장능력_최고 >= 70)
						{
							//맹장
							if (person_t.stat[무장능력_무력] == 무장능력_최고 and 무장능력_평균_통무 >= 무장능력_평균_지정 and person_t.stat[무장능력_무력] > person_t.stat[무장능력_통솔] * 1.1f)
							{character_title = "맹장";}

							//용장
							else if (무장능력_평균_통무 >= 무장능력_평균_지정 and person_t.stat[무장능력_무력] <= person_t.stat[무장능력_통솔] * 1.1f)
							{character_title = "용장";}

							//재상
							else if (무장능력_최고_통무 * 1.5f < person_t.stat[무장능력_정치] and person_t.stat[무장능력_지력] * 1.1f < person_t.stat[무장능력_정치])
							{character_title = "재상";}

							//모사
							else if (무장능력_최고_통무 * 1.5f < person_t.stat[무장능력_지력])
							{character_title = "모사";}

						}

						if (무장능력_최고 >= 80 and person_t.stat[무장능력_무력] < 70)
						{

							//군사
							if (person_t.stat[무장능력_통솔] >= 80 and person_t.stat[무장능력_지력] >= 80 and 무장능력_평균_통지 > 무장능력_평균_통무)
							{character_title = "군사";}

							//재상
							else if (person_t.stat[무장능력_통솔] < 80 and person_t.stat[무장능력_지력] * 1.08f < person_t.stat[무장능력_정치])
							{character_title = "재상";}

							//책사
							else if (person_t.stat[무장능력_통솔] < 80 and person_t.stat[무장능력_정치] * 1.08f < person_t.stat[무장능력_지력])
							{character_title = "책사";}

							//능신
							else if (person_t.stat[무장능력_통솔] < 80 and 무장능력_최고_지정 < 무장능력_평균_지정 * 1.08f)
							{character_title = "능신";}


						}

						if (무장능력_최고 >= 90 and person_t.stat[무장능력_무력] < 70)
						{

							//군사
							if (person_t.stat[무장능력_통솔] >= 80 and person_t.stat[무장능력_지력] >= 80 and 무장능력_평균_통지 > 무장능력_평균_통무)
							{character_title = "군사";}

							//책사
							else if (person_t.stat[무장능력_통솔] < 80 and person_t.stat[무장능력_정치] < person_t.stat[무장능력_지력])
							{character_title = "책사";}

							//능신
							else if (person_t.stat[무장능력_통솔] < 80 and 무장능력_최고_지정 < 무장능력_평균_지정 * 1.05f)
							{character_title = "능신";}

							//재상
							else if (person_t.stat[무장능력_통솔] < 80 and person_t.stat[무장능력_지력] * 1.05f < person_t.stat[무장능력_정치])
							{character_title = "재상";}


						}

						//만능형
						if (무장능력_최저 >= 80)
						{character_title = "기재";}

						//군신
						if (person_t.stat[무장능력_무력] >= 84 and 무장능력_평균_통무지정 >= 84)
						{character_title = "군신";}


						//군웅
						if (person_t.stat[무장능력_무력] < 80 and person_t.stat[무장능력_무력] >= 65 and 무장능력_평균_통지정매 >= 80)
						{character_title = "군웅";}

						//명사
						if (person_t.stat[무장능력_무력] < 80 and person_t.stat[무장능력_통솔] < 80 and 무장능력_최고_매력제외 < 85 and 무장능력_최고_평균_통무통지지정 * 1.1f < person_t.stat[무장능력_매력])
						{character_title = "명사";}
						//일반칭호 끝

						// 고유 칭호
						// 魏
						if (고유칭호_사용)
						{

							if (person_t.get_id() == 무장_조조)
							{
								if ((person_t.kouseki >= 획득공적_0) and (person_t.kouseki < 획득공적_1))
								{character_title = "아만";}
								else if (person_t.kouseki >= 획득공적_1)
								{character_title = "난세의 간웅";}
							}

							if (person_t.get_id() == 무장_조인)
							{	if (person_t.kouseki >= 획득공적_1)
								{character_title = "신장";}
							}

							if (person_t.get_id() == 무장_조홍)
							{
								if (person_t.kouseki >= 획득공적_1)
								{character_title = "황금투구";}
							}

							if (person_t.get_id() == 무장_하후돈)
							{
								if ( (person_t.face != 7))
								{character_title = "맹하후";}
							}

							if (person_t.get_id() == 무장_하후연)
							{
								if ((person_t.kouseki >= 획득공적_0) and (person_t.kouseki < 획득공적_1))
								{character_title = "백지장군";}
								else if (person_t.kouseki >= 획득공적_1)
								{character_title = "귀속장군";}
							}

							if (person_t.get_id() == 무장_장료)
							{
								if (person_t.kouseki >= 획득공적_1)
								{character_title = "료라이라이";}
							}

							if (person_t.get_id() == 무장_허저)
							{
								if ((person_t.kouseki >= 획득공적_0) and (person_t.kouseki < 획득공적_1))
								{character_title = "호치";}
								else if (person_t.kouseki >= 획득공적_1)
								{character_title = "호후";}
							}

							if (person_t.get_id() == 무장_전위)
							{
								if (person_t.kouseki >= 획득공적_1)
								{character_title = "악래";}
							}

							if (person_t.get_id() == 무장_순욱)
							{
								if (person_t.kouseki >= 획득공적_1)
								{character_title = "왕좌지재";}
							}

							if (person_t.get_id() == 무장_조창)
							{
								if (person_t.kouseki >= 획득공적_1)
								{character_title = "황수아";}
							}

							if (person_t.get_id() == 무장_조식)
							{
								if (person_t.kouseki >= 획득공적_1)
								{character_title = "칠보지재";}
							}

							if (person_t.get_id() == 무장_조휴)
							{
								if (person_t.kouseki >= 획득공적_1)
								{character_title = "천리구";}
							}

							if (person_t.get_id() == 무장_서황)
							{
								if (person_t.kouseki >= 획득공적_1)
								{character_title = "무패장군";}
							}

							if (person_t.get_id() == 무장_방덕)
							{
								if (person_t.kouseki >= 획득공적_1)
								{character_title = "백마장군";}
							}

							if (person_t.get_id() == 무장_누규)
							{
								if (person_t.kouseki >= 획득공적_1)
								{character_title = "몽매거사";}
							}

							// 蜀漢
							if (person_t.get_id() == 무장_유비)
							{
								if (person_t.kouseki >= 획득공적_1)
								{character_title = "황숙";}
							}

							if (person_t.get_id() == 무장_관우)
							{
								if (person_t.kouseki >= 획득공적_0)
								{character_title = "미염공";}
								if (person_t.kouseki >= 획득공적_1)
								{character_title = "한수정후";}
							}

							if (person_t.get_id() == 무장_장비)
							{
								if ((person_t.kouseki >= 획득공적_0) and (person_t.kouseki < 획득공적_1))
								{character_title = "팔백팔시";}
								else if (person_t.kouseki >= 획득공적_1)
								{character_title = "호염공";}
							}

							if (person_t.get_id() == 무장_조운)
							{
								if ((person_t.kouseki >= 획득공적_0) and (person_t.kouseki < 획득공적_1))
								{character_title = "상산의 호랑이";}
								else if (person_t.kouseki >= 획득공적_1)
								{character_title = "호위장군";}
							}

							if (person_t.get_id() == 무장_마초)
							{
								if ((person_t.kouseki >= 획득공적_0) and (person_t.kouseki < 획득공적_1))
								{character_title = "금마초";}
								else if (person_t.kouseki >= 획득공적_1)
								{character_title = "신위천장군";}
							}

							if (person_t.get_id() == 무장_황충)
							{
								if ((person_t.kouseki >= 획득공적_1) and (pk::get_year() < person_t.birth + 50))
								{character_title = "노익장";}
							}

							if (person_t.get_id() == 무장_제갈량)
							{
								if (person_t.kouseki >= 획득공적_1)
								{character_title = "와룡";}
							}

							if (person_t.get_id() == 무장_방통)
							{
								if (person_t.kouseki >= 획득공적_1)
								{character_title = "봉추";}
							}

							if (person_t.get_id() == 무장_강유)
							{
								if (person_t.kouseki >= 획득공적_1)
								{character_title = "기린아";}
							}

							if (person_t.get_id() == 무장_마량)
							{
								if (person_t.kouseki >= 획득공적_1)
								{character_title = "백미";}
							}


							// 吳
							if (person_t.get_id() == 무장_손견)
							{
								if (person_t.kouseki >= 획득공적_1)
								{character_title = "강동의 범";}
							}

							if (person_t.get_id() == 무장_손책)
							{
								if (person_t.kouseki >= 획득공적_1)
								{character_title = "소패왕";}
							}

							if (person_t.get_id() == 무장_손권)
							{
								if (person_t.kouseki >= 획득공적_1)
								{character_title = "벽안자염";}
							}

							if (person_t.get_id() == 무장_주유)
							{
								if (person_t.kouseki >= 획득공적_1)
								{character_title = "미주랑";}
							}

							if (person_t.get_id() == 무장_감녕)
							{
								if ((person_t.kouseki >= 획득공적_0) and (person_t.kouseki < 획득공적_1))
								{character_title = "금범적";}
								else if (person_t.kouseki >= 획득공적_1)
								{character_title = "강좌호신";}
							}

							if (person_t.get_id() == 무장_대교)
							{
								if (person_t.kouseki >= 획득공적_1)
								{character_title = "강동 이교";}
							}

							if (person_t.get_id() == 무장_소교)
							{
								if (person_t.kouseki >= 획득공적_1)
								{character_title = "강동 이교";}
							}

							if (person_t.get_id() == 무장_태사자)
							{
								if ((person_t.kouseki >= 획득공적_1) and (person_t.tekisei[병종_노병] >= 적성_S))
								{character_title = "신궁";}
							}


							// 기타 (西晉 포함)
							if (person_t.get_id() == 무장_동탁)
							{
								if (person_t.kouseki >= 획득공적_1)
								{character_title = "상국";}
							}
							if (person_t.get_id() == 무장_엄백호)
							{
								if (person_t.kouseki >= 획득공적_1)
								{character_title = "동오의 덕왕";}
							}

							if (person_t.get_id() == 무장_원소)
							{
								if ((person_t.kouseki >= 획득공적_0) and (person_t.kouseki < 획득공적_1))
								{character_title = "북방효웅";}
								else if (person_t.kouseki >= 획득공적_1)
								{character_title = "사세삼공";}
							}

							if (person_t.get_id() == 무장_안량)
							{
								if (person_t.kouseki >= 획득공적_1)
								{character_title = "하북쌍벽";}
							}

							if (person_t.get_id() == 무장_문추)
							{
								if (person_t.kouseki >= 획득공적_1)
								{character_title = "하북쌍벽";}
							}

							if (person_t.get_id() == 무장_원술)
							{
								if (person_t.kouseki >= 획득공적_1)
								{character_title = "꿀물황제";}
							}

							if (person_t.get_id() == 무장_여포)
							{
								if ((person_t.kouseki >= 획득공적_0) and (person_t.kouseki < 획득공적_1))
								{character_title = "비장";}
								else if (person_t.kouseki >= 획득공적_1)
								{character_title = "인중여포";}
							}

							if (person_t.get_id() == 무장_여영기)
							{
								if (person_t.kouseki >= 획득공적_1)
								{character_title = "비장의 딸";}
							}

							if (person_t.get_id() == 무장_두예)
							{
								if ((person_t.kouseki >= 획득공적_0) and (person_t.kouseki < 획득공적_1))
								{character_title = "두무고";}
								else if (person_t.kouseki >= 획득공적_1)
								{character_title = "좌전벽";}
							}

							if (person_t.get_id() == 무장_고순)
							{
								if (person_t.kouseki >= 획득공적_1)
								{character_title = "함진영";}
							}

							if (person_t.get_id() == 무장_초선)
							{
								if ((person_t.kouseki >= 획득공적_0) and (person_t.kouseki < 획득공적_1))
								{character_title = "폐월";}
								else if (person_t.kouseki >= 획득공적_1)
								{character_title = "경국지색";}
							}

							if (person_t.get_id() == 무장_공손찬)
							{
								if (person_t.kouseki >= 획득공적_1)
								{character_title = "백마장사";}
							}

							if (person_t.get_id() == 무장_장각)
							{
								if (person_t.kouseki >= 획득공적_1)
								{character_title = "대현량사";}
							}

							if (person_t.get_id() == 무장_장보)
							{
								if (person_t.kouseki >= 획득공적_1)
								{character_title = "지공장군";}
							}

							if (person_t.get_id() == 무장_장량)
							{
								if (person_t.kouseki >= 획득공적_1)
								{character_title = "인공장군";}
							}

							if (person_t.get_id() == 무장_유방)
							{
								if (person_t.kouseki >= 획득공적_1)
								{character_title = "한고조";}
							}

							if (person_t.get_id() == 무장_항적)
							{
								if ((person_t.kouseki >= 획득공적_0) and (person_t.kouseki < 획득공적_1))
								{character_title = "역발산";}
								else if (person_t.kouseki >= 획득공적_1)
								{character_title = "초패왕";}
							}

							if (person_t.get_id() == 무장_범증)
							{
								if (person_t.kouseki >= 획득공적_1)
								{character_title = "아보";}
							}

							//태공망
							if (person_t.get_id() == 829)
							{
								if (person_t.kouseki >= 획득공적_1)
								{character_title = "태공망";}
							}

							//진시황
							if (person_t.get_id() == 806)
							{
								if (person_t.kouseki >= 획득공적_1)
								{character_title = "시황";}
							}

							//고장공
							if (person_t.get_id() == 무장_고장공)
							{
								if (person_t.kouseki >= 획득공적_1)
								{character_title = "난릉왕";}
							}

							//백기
							if (person_t.get_id() == 무장_백기)
							{
								if (person_t.kouseki >= 획득공적_1)
								{character_title = "무안군";}
							}

							//에보니 신무장 패키지

							if (Ebony_신무장_패키지_사용여부)
							{
								//양옥환
								if (person_t.get_id() == 941)
								{
									if ((person_t.kouseki >= 획득공적_0) and (person_t.kouseki < 획득공적_1))
									{character_title = "수화";}
									else if (person_t.kouseki >= 획득공적_1)
									{character_title = "양귀비";}
								}
								//이세민
								if (person_t.get_id() == 937)
								{
									if (person_t.kouseki >= 획득공적_1)
									{character_title = "천가한";}
								}
								//한세충
								if (person_t.get_id() == 889)
								{
									if (person_t.kouseki >= 획득공적_1)
									{character_title = "만부부당";}
								}

								//칭기즈칸
								if (person_t.get_id() == 945)
								{
									if (person_t.kouseki >= 획득공적_1)
									{character_title = "칭기즈칸";}
								}

								//자무카
								if (person_t.get_id() == 946)
								{
									if (person_t.kouseki >= 획득공적_1)
									{character_title = "구르칸";}
								}

								//쿠빌라이
								if (person_t.get_id() == 949)
								{
									if (person_t.kouseki >= 획득공적_1)
									{character_title = "칸";}
								}

								//임충
								if (person_t.get_id() == 951)
								{
									if (person_t.kouseki >= 획득공적_0)
									{character_title = "표자두";}
									else if (person_t.kouseki >= 획득공적_1)
									{character_title = "천웅성";}
								}

								//호연작
								if (person_t.get_id() == 952)
								{
									if (person_t.kouseki >= 획득공적_0)
									{character_title = "쌍편";}
									else if (person_t.kouseki >= 획득공적_1)
									{character_title = "천위성";}
								}

								//화영
								if (person_t.get_id() == 953)
								{
									if (person_t.kouseki >= 획득공적_0)
									{character_title = "소이광";}
									else if (person_t.kouseki >= 획득공적_1)
									{character_title = "천영성";}
								}

								//오용
								if (person_t.get_id() == 954)
								{
									if (person_t.kouseki >= 획득공적_0)
									{character_title = "지다성";}
									else if (person_t.kouseki >= 획득공적_1)
									{character_title = "천기성";}
								}

								//이규
								if (person_t.get_id() == 955)
								{
									if (person_t.kouseki >= 획득공적_0)
									{character_title = "철우";}
									else if (person_t.kouseki >= 획득공적_1)
									{character_title = "천살성";}
								}

								//연청
								if (person_t.get_id() == 956)
								{
									if (person_t.kouseki >= 획득공적_0)
									{character_title = "낭자";}
									else if (person_t.kouseki >= 획득공적_1)
									{character_title = "천교성";}
								}
							} //에보니 신무장 패키지 끝
						}// 고유 칭호 끝

						// if (자_공백_추가)
						// {person_t.azana += pk::u8encode(" ");}

						//성명 읽기
						person_t.name_read = pk::u8encode(grade_color+character_title);

						//자 읽기
						person_t.azana_read = pk::u8encode(grade_name);



					}
				}


				else if (추가특기_표시 == 1)
				{

					if (person_id <= 무장_사실30 or person_id >= 무장_공구)
					{
						int skill_count = 0;
						string skill_names;
						pk::person@ person_t = pk::get_person(person_id);

						if (person_t !is null)
						{
							for (int skill_id = 0; skill_id < 특기_끝; skill_id++)
							{
								pk::skill@ skill_t = pk::get_skill(skill_id);
								if (pk::has_skill(person_t, skill_id) and person_t.skill != skill_id)
								{
									skill_count++;
									if (skill_count <= 3)
										skill_names += pk::u8decode(skill_t.name);
								}
							}
						}

						// if (자_공백_추가)
						// {person_t.azana += pk::u8encode(" ");}

						person_t.name_read  = pk::u8encode(skill_names);
						person_t.azana_read = (skill_count > 3)? pk::u8encode(pk::format("+{}개", skill_count - 3)) : " ";
					}
				}
			}
		}
		
		void xml()
		{
			// 무장컷인
			pk::load_xml("""
			<pk utf8="true" trace="true">
				<kr k="ee6d" v="맥"/>
			</pk>
			""");
		}
    }
	Main main;
}