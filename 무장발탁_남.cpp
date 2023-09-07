/*     
@제작자: HoneyBee    
@내용: [삼국지9PK, 삼국지12PK]에서 무장을 발탁하는 시스템을 참고하여 제작한 SCRIPT (50% 확률로 무장 발탁 가능)   

      -> 무장 발탁에 실패하면 대신에 병량을 획득하고 금은 소비되지 않습니다. 
	 
*/
 
namespace 무장발탁_남무장
{
	
	// ========================== CUSTOMIZE ===============================
	
		const int TP_COST = 500; 		// 기교P 수치 결정
		const int ACTION_COST = 50;     // 행동력 필요량
		const int GOLD_COST = 3000;     // 금 필요량
		const int ADD_FOOD = 10000;     // 발탁 무장 대신에 획득하는 병량
		
		const int 발탁실패확률 = 50;    		// 무장발탁이 실패할 확률 (기본 설정 - 50%)
		
		
		/* 
		   발탁 무장은 4가지 中 한 가지 TYPE이 결정됩니다.
		   0-무관형, 1-문관형, 2-만능형, 3-RANDOM 
		*/

		// 무관형 능력치 설정 (통솔, 무력)
		const int min_stat_무관형_통솔 = 70;   // 무관형 발탁 무장의 최소 통솔 능력치를 설정 (기본 설정 - 70)
		const int max_stat_무관형_통솔 = 97;   // 무관형 발탁 무장의 최대 통솔 능력치를 설정 (기본 설정 - 90)
		
		const int min_stat_무관형_무력 = 70;   // 무관형 발탁 무장의 최소 무력 능력치를 설정 (기본 설정 - 70)
		const int max_stat_무관형_무력 = 97;   // 무관형 발탁 무장의 최대 무력 능력치를 설정 (기본 설정 - 90)
		
		const int min_stat_무관형_지력 = 10;   // 무관형 발탁 무장의 최소 지력 능력치를 설정 (기본 설정 - 10)
		const int max_stat_무관형_지력 = 65;   // 무관형 발탁 무장의 최대 지력 능력치를 설정 (기본 설정 - 60)
		
		const int min_stat_무관형_정치 = 10;   // 무관형 발탁 무장의 최소 정치 능력치를 설정 (기본 설정 - 10)
		const int max_stat_무관형_정치 = 65;   // 무관형 발탁 무장의 최대 정치 능력치를 설정 (기본 설정 - 60)


		// 문관형 능력치 설정 (지력, 정치)
		const int min_stat_문관형_통솔 = 10;   // 문관형 발탁 무장의 최소 통솔 능력치를 설정 (기본 설정 - 10)
		const int max_stat_문관형_통솔 = 65;   // 문관형 발탁 무장의 최대 통솔 능력치를 설정 (기본 설정 - 60)
		
		const int min_stat_문관형_무력 = 10;   // 문관형 발탁 무장의 최소 무력 능력치를 설정 (기본 설정 - 10)
		const int max_stat_문관형_무력 = 65;   // 문관형 발탁 무장의 최대 무력 능력치를 설정 (기본 설정 - 60)
		
		const int min_stat_문관형_지력 = 70;   // 문관형 발탁 무장의 최소 지력 능력치를 설정 (기본 설정 - 70)
		const int max_stat_문관형_지력 = 97;   // 문관형 발탁 무장의 최대 지력 능력치를 설정 (기본 설정 - 90)
		
		const int min_stat_문관형_정치 = 70;   // 문관형 발탁 무장의 최소 정치 능력치를 설정 (기본 설정 - 70)
		const int max_stat_문관형_정치 = 97;   // 문관형 발탁 무장의 최대 정치 능력치를 설정 (기본 설정 - 90)
		
		
		// 만능형 능력치 설정 (통솔, 무력, 지력, 정치)
		const int min_stat_만능형_통솔 = 60;   // 만능형 발탁 무장의 최소 통솔 능력치를 설정 (기본 설정 - 70)
		const int max_stat_만능형_통솔 = 92;   // 만능형 발탁 무장의 최대 통솔 능력치를 설정 (기본 설정 - 90)
		
		const int min_stat_만능형_무력 = 60;   // 만능형 발탁 무장의 최소 무력 능력치를 설정 (기본 설정 - 70)
		const int max_stat_만능형_무력 = 92;   // 만능형 발탁 무장의 최대 무력 능력치를 설정 (기본 설정 - 90)
		
		const int min_stat_만능형_지력 = 65;   // 만능형 발탁 무장의 최소 지력 능력치를 설정 (기본 설정 - 70)
		const int max_stat_만능형_지력 = 92;   // 만능형 발탁 무장의 최대 지력 능력치를 설정 (기본 설정 - 90)
		
		const int min_stat_만능형_정치 = 65;   // 만능형 발탁 무장의 최소 정치 능력치를 설정 (기본 설정 - 70)
		const int max_stat_만능형_정치 = 92;   // 만능형 발탁 무장의 최대 정치 능력치를 설정 (기본 설정 - 90)
		
		
		// 무관형, 문관형, 만능형 매력 설정 
		const int min_stat_매력 = 30;   	   // 발탁 무장의 최소 매력 능력치를 설정 (기본 설정 - 30)
		const int max_stat_매력 = 90;        // 발탁 무장의 최대 매력 능력치를 설정 (기본 설정 - 90)
		
		
		const bool 이름자동 = false;	       // 무장 이름을 자동으로 생성	[이름자동 true일시, 이름수동 false로 지정]
		const bool 이름수동 = true;           // 무장 이름을 수동(배열 작성)으로 생성 [이름수동 true일시, 이름자동 false로 지정]
		

		// === 발탁무장 SLOT 지정 관련 (중요) === ▼
		
		/* 
		   - 무장의 SLOT을 지정 (반드시 2가지 中 한 가지만 true, 나머지는 false로 설정해야됨)
		   - slot_신무장은 Gold Edition Patch에서 제작한 신무장의 갯수에 따라서 기본으로 적용함
		   - Gold Edition Patch 기준 등록된 신무장이 850 ~ 934 이므로, 935부터 발탁 무장을 작성하도록 기본 설정 (男은 935 ~ 967까지 설정함)
		   - Gold Edition Patch 기준 등록된 신무장이 850 ~ 934 이므로, 935부터 발탁 무장을 작성하도록 기본 설정 (女는 968 ~ 999까지 설정함)
		
		*/
		
		// 신무장 SLOT을 사용하여 발탁무장 추가 (단점: 신무장의 SLOT을 사용하므로, 신무장을 많이 생성했을 경우 비추천)
		const bool slot_신무장 = true;
		
		// 일반무장(이미 사망하거나 신분없는 무장) SLOT을 사용하여 발탁무장 추가 (단점: 사망한 무장이 적다면, SLOT의 제약이 큼)
		const bool slot_일반무장 = false;
		
		// 미사용 고대무장 SLOT을 사용하여 발탁무장 추가 (단점: SLOT의 제약이 큼, 최대 18人)
		const bool slot_고대무장 = false;

		// ============================== ▲		
	
	
		/* 
		
			발탁 무장 이름을 ARRAY로 미리 SETTING 하시기 바랍니다. (아래는 임시로 넣은 성명입니다.)
			아래 성명에서 RANDOM으로 출력하여 발탁 무장의 이름이 정해집니다.
			
			EX) 조조, 조비, 조견, 유비, 유견, 유탁, 손견, 손탁, 손포 등..
		
		*/
		
		// 발탁 무장 [성] (임시로 40개 설정)
		array<string> sei_ = { "조", "유", "손", "동", "여", "공손", "화", "이", "문", "현",
                               "장", "왕", "주", "제갈", "전", "허", "안", "서", "엄", "임",
							   "백", "신", "정", "양", "배", "강", "화", "간", "미", "황",
							   "마", "후", "송", "위", "감", "한", "관", "악", "하후", "사마" }; 	 

	    // 발탁 무장 [이름] (임시로 40개로 설정)
		array<string> mei_ = { "조", "비", "견", "탁", "포", "찬", "웅", "전", "앙", "빈", 
		                       "료", "평", "창", "량", "위", "저", "명", "황", "여", "기",
							   "사", "영", "홍", "수", "구", "성", "신", "손", "소", "제",
							   "초", "성", "헌", "속", "녕", "당", "우", "진", "돈", "의" }; 
		
		
		// EX) { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ... 39 } <- TOTAL 40개 (ARRAY에서 [성], [이름]을 늘릴 때마다 동일한 갯수로 설정하시면 됩니다.)
		int i = 0;   // 배열의 FIRST NUMBER 
		int j = 39;  // 배열의 LAST NUMBER
		
	
	// ====================================================================
	
	
	const int KEY = pk::hash("발탁(남)");
	
	
	class Main
	{
		pk::building@ building_;
		pk::person@ kunshu_;
		pk::force@ force_;
		pk::city@ city_;
		uint16 building_gold;
		uint16 building_food;
		
		Main()
		{
			pk::menu_item item;
			item.menu = 102;
			item.pos = 6;
			item.shortcut = "6";
			item.init = pk::building_menu_item_init_t(init);
			item.is_enabled = pk::menu_item_is_enabled_t(isEnabled);
			item.get_text = pk::menu_item_get_text_t(getText);
			item.get_desc = pk::menu_item_get_desc_t(getDesc);
			item.handler = pk::menu_item_handler_t(handler);
			pk::add_menu_item(item);
		}

		void init(pk::building@ building)
		{
			@building_ = @building;
			@force_ = pk::get_force(building.get_force_id());
			@kunshu_ = pk::get_person(force_.kunshu);
			@city_ = pk::building_to_city(building_);
			building_gold = pk::get_gold(building);
		}


		bool isEnabled()
		{
			if (building_gold < GOLD_COST) return false;
            else if (force_.tp < TP_COST) return false;
            else if (pk::get_district(pk::get_district_id(force_, 1)).ap < ACTION_COST) return false;
			return true;
		}
		
		string getText()
		{
			return pk::encode("발탁(남)");
		}
		
		string getDesc()
		{
			if (building_gold < GOLD_COST)
                return pk::encode(pk::format("금이 부족합니다.(금 {} 필요)", GOLD_COST));
			else if (force_.tp < TP_COST)
                return pk::encode(pk::format("기교P가 부족합니다.(기교P {})", TP_COST));
            else if (pk::get_district(pk::get_district_id(force_, 1)).ap < ACTION_COST)
                return pk::encode(pk::format("행동력이 부족합니다.(행동력 {} 필요)", ACTION_COST));
			else
				return pk::encode(pk::format("무장을 밭탁합니다.(기교P {} 사용)", TP_COST));
		}

		bool handler()
		{
			
			pk::random random(pk::rand());
			
			if (pk::choose(pk::encode("무장을 발탁하시겠습니까?"), { pk::encode("예"), pk::encode("아니오") }) == 1)
				return false;
			
			string kunshu_name = pk::decode(pk::get_name(kunshu_));			
			pk::person@ person_2 = pk::get_person(무장_문관);


			if (pk::rand_bool(발탁실패확률) or getEmptyPerson() is null)
			{
				pk::message_box(pk::encode("주공, 이 지역에서 소문난 인재를 찾아갔지만 이미 다른 지역으로 떠났다고 합니다."), person_2);
				pk::message_box(pk::encode("음.. 그거 참 아쉽게 되었군.\n아무튼 수고했네."), kunshu_);
				pk::message_box(pk::encode("대신에 이 지역 사람들이 평소 주공의 은덕에 보답하고자 군량을 보냈습니다."), person_2);
				pk::message_box(pk::encode("허허, 그래도 자네가 헛걸음을 하지는 않은 셈이군."), kunshu_);

				pk::message_box(pk::encode("무장 발탁에 실패하였습니다."));
				
				// 기교 감소 및 병량 증가
				pk::message_box(pk::encode(pk::format("기교 포인트가 \x1b[1x{}\x1b[0x만큼 감소했습니다.", TP_COST)));
				pk::add_tp(force_, -TP_COST, force_.get_pos());
				pk::message_box(pk::encode(pk::format("병량이 \x1b[1x{}\x1b[0x만큼 증가했습니다.", ADD_FOOD)));
				pk::add_food(city_, ADD_FOOD, true);
				
				// 행동력 감소.
				auto district = pk::get_district(pk::get_district_id(force_, 1));
				district.ap -= ACTION_COST;	
				
			}
			
			else 
			{
				
				pk::person@ new_face = getEmptyPerson();
				
				new_face.sex = 성별_남;
				
				if (이름자동)
				{
					new_face.sei = pk::get_family_name(random(성씨_끝 - 1)).name; // 성
					new_face.mei = pk::get_family_name(random(성씨_끝 - 1)).name; // 명
				}
				
				if (이름수동)
				{
					new_face.sei = pk::encode(sei_[random(i, j)]); // 성
					new_face.mei = pk::encode(mei_[random(i, j)]); // 명
				}
		
				new_face.face = random(2000, 2099);
				new_face.appearance = pk::get_year();
				new_face.birth = pk::get_year() - 17 - random(4);
				new_face.death = pk::min(353, new_face.birth + 70 + random(20));
				new_face.ketsuen = new_face.get_id();
				new_face.aishou = random(0, 150);
				new_face.mibun = 신분_일반;
				new_face.loyalty = 100;
				
				// 친애무장, 혐오무장 초기화
				for (int i = 0; i < 5; i++)
				{
					new_face.liked[i] = -1;
					new_face.disliked[i] = -1;
				}
				
				new_face.liked[0] = force_.kunshu;
				
				// 병종 설정.
				new_face.tekisei[병종_기병] = random(0, 2);
				new_face.tekisei[병종_창병] = random(0, 2);
				new_face.tekisei[병종_극병] = random(0, 2);
				new_face.tekisei[병종_노병] = random(0, 2);
				new_face.tekisei[병종_병기] = random(0, 2);
				new_face.tekisei[병종_수군] = random(0, 2);
				
				int random_n = pk::rand(4); // 0, 1, 2, 3
				
				for (int i = 0; i < 무장능력_끝; i++)
				{
					
					// 0-무관형, 1-문관형, 2-만능형, 3-RANDOM 
					
					// 0-무관형
					if (random_n == 0)
					{
						
						if (i == 무장능력_통솔)
						{
							new_face.base_stat[i] = random(min_stat_무관형_통솔, max_stat_무관형_통솔);
						}
						
						else if (i == 무장능력_무력)
						{
							new_face.base_stat[i] = random(min_stat_무관형_무력, max_stat_무관형_무력);
						}
						
						else if (i == 무장능력_지력)
						{
							new_face.base_stat[i] = random(min_stat_무관형_지력, max_stat_무관형_지력);
						}
						
						else if (i == 무장능력_정치)
						{
							new_face.base_stat[i] = random(min_stat_무관형_정치, max_stat_무관형_정치);
						}
						
						else
						{
							new_face.base_stat[i] = random(min_stat_매력, max_stat_매력);
						}

					} // if (random_n == 0)

					// 1-문관형
					else if (random_n == 1)
					{
						
						if (i == 무장능력_통솔)
						{
							new_face.base_stat[i] = random(min_stat_문관형_통솔, max_stat_문관형_통솔);
						}
						
						else if (i == 무장능력_무력)
						{
							new_face.base_stat[i] = random(min_stat_문관형_무력, max_stat_문관형_무력);
						}
						
						else if (i == 무장능력_지력)
						{
							new_face.base_stat[i] = random(min_stat_문관형_지력, max_stat_문관형_지력);
						}
						
						else if (i == 무장능력_정치)
						{
							new_face.base_stat[i] = random(min_stat_문관형_정치, max_stat_문관형_정치);
						}
						
						else
						{
							new_face.base_stat[i] = random(min_stat_매력, max_stat_매력);
						}
						
					} // else if (random_n == 1)
					
					// 2-만능형
					else if (random_n == 2)
					{
						
						if (i == 무장능력_통솔)
						{
							new_face.base_stat[i] = random(min_stat_만능형_통솔, max_stat_만능형_통솔);
						}
						
						else if (i == 무장능력_무력)
						{
							new_face.base_stat[i] = random(min_stat_만능형_무력, max_stat_만능형_무력);
						}
						
						else if (i == 무장능력_지력)
						{
							new_face.base_stat[i] = random(min_stat_만능형_지력, max_stat_만능형_지력);
						}
						
						else if (i == 무장능력_정치)
						{
							new_face.base_stat[i] = random(min_stat_만능형_정치, max_stat_만능형_정치);
						}
						
						else
						{
							new_face.base_stat[i] = random(min_stat_매력, max_stat_매력);
						}
						
					} // else if (random_n == 2)
						
					// 3-RANDOM
					else if (random_n == 3)
					{
						new_face.base_stat[i] = random(1, 100);
					} 
					
					new_face.stat_aging[i] = random(능력성장_초지속형, 능력성장_장비형);
				}
				
				new_face.birthplace = random(주_유주, 주_남중);
				new_face.skill = random(특기_비장, 특기_내조);
				new_face.wadai = random(화제_고사, 화제_시절);
				new_face.giri = random(의리_매우낮음, 의리_매우높음);
				new_face.ambition = random(야망_매우낮음, 야망_매우높음);
				new_face.promotion = random(기용_능력, 기용_임의);
				new_face.character = random(성격_소심, 성격_저돌);
				new_face.voice = random(음성_소심남, 음성_저돌남);
				new_face.tone = random(말투_장비, 말투_보통남);
				new_face.kanshitsu = random(한실_무시, 한실_중시);
				new_face.strategic_tendency = random(전략경향_중화통일, 전략경향_현상유지);
				new_face.local_affiliation = random(지역집착_지역중시, 지역집착_지역무시);
				
				// 무관형 무장 조형
				if (random_n == 0)
				{
					new_face.body[0] = 102; // 투구
					new_face.body[1] = 84;  // 얼굴
					new_face.body[2] = 85;  // 상체
					new_face.body[3] = 85;  // 망토
					new_face.body[4] = 85;  // 팔
					new_face.body[5] = 85;  // 다리 
				}
				
				// 문관형 무장 조형
				else if (random_n == 1)
				{
					new_face.body[0] = 92; // 투구
					new_face.body[1] = 93;  // 얼굴
					new_face.body[2] = 97;  // 상체
					new_face.body[3] = -1;  // 망토
					new_face.body[4] = 97;  // 팔
					new_face.body[5] = 97;  // 다리
				}
				
				else 
				{
					new_face.body[0] = 102; // 투구
					new_face.body[1] = 84;  // 얼굴
					new_face.body[2] = 85;  // 상체
					new_face.body[3] = 85;  // 망토
					new_face.body[4] = 85;  // 팔
					new_face.body[5] = 85;  // 다리 
				}

				// 화술 획득 확률
				int wajutsu_daikatsu_0 = 30;
				int wajutsu_kiben_0 = 30;
				int wajutsu_mushi_0 = 30;
				int wajutsu_chinsei_0 = 30;
				int wajutsu_gyakujou_0 = 30;
						
				if (pk::rand_bool(wajutsu_daikatsu_0))
				{
					new_face.wajutsu_daikatsu = true;
				}
				
				if (pk::rand_bool(wajutsu_kiben_0))
				{
					new_face.wajutsu_kiben = true;
				}
				
				if (pk::rand_bool(wajutsu_mushi_0))
				{
					new_face.wajutsu_mushi = true;
				}
				
				if (pk::rand_bool(wajutsu_chinsei_0))
				{
					new_face.wajutsu_chinsei = true;
				}
				
				if (pk::rand_bool(wajutsu_gyakujou_0))
				{
					new_face.wajutsu_gyakujou = true;
				}
				
				pk::set_district(new_face, building_.get_district_id()); 
				new_face.update();
				
				string newface_name = pk::decode(pk::get_name(new_face));	
				
				pk::message_box(pk::encode(pk::format("주공, 이 지역에서 유명한 인재인 \x1b[1x{}\x1b[0x님을 모셔왔습니다.", newface_name)), person_2);
				pk::message_box(pk::encode("오, 그래 수고했네. 자, 어서오시오."), kunshu_);
				pk::message_box(pk::encode(pk::format("안녕하십니까. \x1b[1x{}\x1b[0x님을 뵙게 되어 영광입니다.", kunshu_name)), new_face);
				pk::message_box(pk::encode("그대에 대한 소문은 진작부터 듣고 있었소. 앞으로 나를 도와주시겠소?"), kunshu_);
				pk::message_box(pk::encode(pk::format("네, 저의 능력을 알아봐주신 \x1b[1x{}\x1b[0x님을 위해서 신명을 바치겠습니다.", kunshu_name)), new_face);
				pk::message_box(pk::encode("자, 그리고 이것은 약소하지만 그대에게 주는 성의요."), kunshu_);
				pk::message_box(pk::encode("이렇게 많은 금을 주시다니 감사합니다."), new_face);
				pk::message_box(pk::encode("나야말로 그대가 우리군에 합류해준다니 고맙소. 앞으로 그대를 중용하겠소."), kunshu_);
				
				pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x(이)가 아군으로 합류했습니다.", newface_name)));
				
				// 기교 및 금 감소
				pk::message_box(pk::encode(pk::format("기교 포인트가 \x1b[1x{}\x1b[0x만큼 감소했습니다.", TP_COST)));
				pk::add_tp(force_, -TP_COST, force_.get_pos());
				pk::message_box(pk::encode(pk::format("도시의 금이 \x1b[1x{}\x1b[0x만큼 감소했습니다.", GOLD_COST)));
				pk::add_gold(city_, -GOLD_COST, true);
				
				// 행동력 감소.
				auto district = pk::get_district(pk::get_district_id(force_, 1));
				district.ap -= ACTION_COST;	
				
				pk::sort(pk::person::type_id);
				pk::move(new_face, building_);
				
			}	

			return true;
		}
		
		
		/**
		@details
			빈 무장칸은 아래의 순서대로 확인할 것을 권장함.
			1.  850 ~  999(신무장)
			2.  832 ~  849(사용하지 않는 고대 무장)
			3.  670 ~  699(사용하지 않는 사실 무장)
			4.  800 ~  831(고대 무장)
			5.    0 ~  670(역사 무장)
			6. 1000 ~ 1099(적장). pk::create_bandit 함수에서 사용하는 영역임.
			7.  700 ~  799(이벤트 무장). 신분에 상관없이 pk::is_alive 함수가 항상 true를 리턴하는 영역임.

			사망한 무장을 부활시키는 스크립트가 있다면 "case 신분_사망:" 부분은 제외.
		*/
		
		/*
		bool getEmptyPerson()
		{
			for (int i = 1000; i < 1099; i++)
			{
				pk::person@ new_face = pk::get_person(i);

				switch (new_face.mibun)
				{
					case 신분_없음	:
					case 신분_미등장:
					case 신분_미발견:
					case 신분_사망	:
						return true;
				}

			}
			return false;
		}
		*/
		
		pk::person@ getEmptyPerson()
		{
			if (slot_일반무장)
			{
				for (int i = 0; i < 700; i++)
				{
					
					pk::person@ new_face = pk::get_person(i);
					
					switch (new_face.mibun)
					{
					case 신분_없음:
					case 신분_사망:
						return new_face;
					}

				}
			}
			
			if (slot_신무장)
			{
				for (int i = 960; i < 979; i++)
				{
					pk::person@ new_face = pk::get_person(i);
					switch (new_face.mibun)
					{
					case 신분_없음:
					case 신분_미등장:
					case 신분_사망:
						return new_face;
					}
				}
			}
			
			if (slot_고대무장)
			{
				for (int i = 832; i < 850; i++)
				{
					pk::person@ new_face = pk::get_person(i);
					switch (new_face.mibun)
					{
					case 신분_없음:
					case 신분_미등장:
					case 신분_사망:
						return new_face;
					}
				}
			}
			
			return null;
			
		} // pk::person@ getEmptyPerson()
		
	}

	Main main;
}