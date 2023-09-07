/*    
@제작자: HoneyBee      
@설명: 이민족 특기를 보유한 무장이 소속된 도시에서 이민족을 용병으로 고용 가능 (50% 확률로 고용 가능)   

     -> 이민족 고용에 실패하면 대신에 병량을 획득하고 금은 소비되지 않습니다. 

*/

namespace 이민족_용병
{
	
	// ================ CUSTOMIZE ================
	
		const bool 강족_활성화 = true;        // true = on, false = off
		const bool 오환족_활성화 = true;       // true = on, false = off
		const bool 산월족_활성화 = true;       // true = on, false = off
		const bool 남만족_활성화 = true;       // true = on, false = off
		
		const bool 이름자동 = false;	       // 무장 이름을 자동으로 생성	[이름자동 true일시, 이름수동 false로 지정]
		const bool 이름수동 = true;           // 무장 이름을 수동(배열 작성)으로 생성 [이름수동 true일시, 이름자동 false로 지정]
	
		const int TP_COST = 500; 		   // 기교P 수치 결정
		const int ACTION_COST = 70;        // 행동력 필요량
		const int GOLD_COST = 3000;        // 금 필요량
		const int ADD_FOOD = 10000;        // 이민족 용병 대신에 획득하는 병량
		
		const int 고용실패확률 = 50;    		   // 이민족 용병 고용이 실패할 확률 (기본 설정 - 50%)
		
		/* 
		   이민족 용병은 4가지 中 한 가지 TYPE이 결정됩니다.
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
		const int min_stat_매력 = 30;   	   // 이민족 용병의 최소 매력 능력치를 설정 (기본 설정 - 30)
		const int max_stat_매력 = 90;        // 이민족 용병의 최대 매력 능력치를 설정 (기본 설정 - 90)
		
		const int min_distance = 1;        // 용병 부대 생성 최소 위치
        const int max_distance = 8;        // 용병 부대 생성 최대 위치
		const int troops = 5000;		   // 용병 부대 병력 설정 (최대 5000)
		
		
		
		// === 이민족 용병 SLOT 지정 관련 (중요) === ▼
		
		/* 
		   - 무장의 SLOT을 지정 (반드시 2가지 中 한 가지만 true, 나머지는 false로 설정해야됨)
		   - slot_신무장은 Gold Edition Patch에서 제작한 신무장의 갯수에 따라서 기본으로 적용함
		   - Gold Edition Patch 기준 등록된 신무장이 850 ~ 934 이므로, 935부터 이민족 용병을 작성하도록 기본 설정
		*/
		
		// 신무장 SLOT을 사용하여 이민족 용병 추가 (단점: 신무장의 SLOT을 사용하므로, 신무장을 많이 생성했을 경우 비추천)
		const bool slot_신무장 = true;
		
		// 일반무장(이미 사망하거나 신분없는 무장) SLOT을 사용하여 이민족 용병 추가 (단점: 사망한 무장이 적으면, SLOT의 제약이 큼)
		const bool slot_일반무장 = false;   
		
		// 미사용 고대무장 SLOT을 사용하여 발탁무장 추가 (단점: SLOT의 제약이 큼, 최대 18人)
		const bool slot_고대무장 = false;

		// ================================ ▲	
		
		
		/* 
		
			이민족 무장 이름을 ARRAY로 미리 SETTING 하시기 바랍니다. (아래는 임시로 넣은 성명입니다.)
			아래 성명에서 RANDOM으로 출력하여 이민족 무장의 이름이 정해집니다.
			
			EX) 조조, 조비, 조견, 유비, 유견, 유탁, 손견, 손탁, 손포 등..
		
		*/
		
		// 이민족 무장 [성] (임시로 40개 설정)
		array<string> sei_ = { "조", "유", "손", "동", "여", "공손", "화", "이", "문", "현",
                               "장", "왕", "주", "제갈", "전", "허", "안", "서", "엄", "임",
							   "백", "신", "정", "양", "배", "강", "화", "간", "미", "황",
							   "마", "후", "송", "위", "감", "한", "관", "악", "하후", "사마" }; 	 

	    // 이민족 무장 [이름] (임시로 40개로 설정)
		array<string> mei_ = { "조", "비", "견", "탁", "포", "찬", "웅", "전", "앙", "빈", 
		                       "료", "평", "창", "량", "위", "저", "명", "황", "여", "기",
							   "사", "영", "홍", "수", "구", "성", "신", "손", "소", "제",
							   "초", "성", "헌", "속", "녕", "당", "우", "진", "돈", "의" }; 
		
		
		// EX) { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ... 39 } <- TOTAL 40개 (ARRAY에서 [성], [이름]을 늘릴 때마다 동일한 갯수로 설정하시면 됩니다.)
		int i = 0;   // 배열의 FIRST NUMBER 
		int j = 39;  // 배열의 LAST NUMBER
		

		const int KEY = pk::hash("용병고용");
	
	// ===========================================
	
	
	class Main
	{
		pk::random random(pk::rand());
		pk::building@ building_;
		pk::building@ taishu_building;
		pk::force@ force;
		pk::person@ taishu;
		pk::city@ city;
		uint16 building_gold;
		
		bool 강족생성 = false;
		bool 오환족생성 = false;
		bool 산월족생성 = false;
		bool 남만족생성 = false;
		
		// 건물 메뉴 도시
		int menu_city_id_;
		
		// 건물 메뉴 세력
		int menu_force_id_;
		
		Main()
		{
			
			pk::menu_item item;
			int parent;
			
			item.menu = 0;
			item.get_text = cast<pk::menu_item_get_text_t@>(function() { return pk::encode("용병고용"); });
            item.init = pk::building_menu_item_init_t(init);
            item.is_visible = pk::menu_item_is_visible_t(isMenuVisible);
			parent = pk::add_menu_item(item);
			
			if (강족_활성화)
			{	
				item.menu = parent;
				item.init = pk::building_menu_item_init_t(init);
				item.is_visible = pk::menu_item_is_visible_t(isMenuVisible);
				item.is_enabled = pk::menu_item_is_enabled_t(isEnabled_강족);
				item.get_text = pk::menu_item_get_text_t(getText_강족);
				item.get_desc = pk::menu_item_get_desc_t(getDesc_강족);
				item.handler = pk::menu_item_handler_t(handler_강족);
				pk::add_menu_item(item);
			}
			
			if (오환족_활성화)
			{	
				item.menu = parent;
				item.init = pk::building_menu_item_init_t(init);
				item.is_visible = pk::menu_item_is_visible_t(isMenuVisible);
				item.is_enabled = pk::menu_item_is_enabled_t(isEnabled_오환족);
				item.get_text = pk::menu_item_get_text_t(getText_오환족);
				item.get_desc = pk::menu_item_get_desc_t(getDesc_오환족);
				item.handler = pk::menu_item_handler_t(handler_오환족);
				pk::add_menu_item(item);
			}
			
			if (산월족_활성화)
			{	
				item.menu = parent;
				item.init = pk::building_menu_item_init_t(init);
				item.is_visible = pk::menu_item_is_visible_t(isMenuVisible);
				item.is_enabled = pk::menu_item_is_enabled_t(isEnabled_산월족);
				item.get_text = pk::menu_item_get_text_t(getText_산월족);
				item.get_desc = pk::menu_item_get_desc_t(getDesc_산월족);
				item.handler = pk::menu_item_handler_t(handler_산월족);
				pk::add_menu_item(item);
			}
			
			if (남만족_활성화)
			{	
				item.menu = parent;
				item.init = pk::building_menu_item_init_t(init);
				item.is_visible = pk::menu_item_is_visible_t(isMenuVisible);
				item.is_enabled = pk::menu_item_is_enabled_t(isEnabled_남만족);
				item.get_text = pk::menu_item_get_text_t(getText_남만족);
				item.get_desc = pk::menu_item_get_desc_t(getDesc_남만족);
				item.handler = pk::menu_item_handler_t(handler_남만족);
				pk::add_menu_item(item);
			}
	

		}

		void init(pk::building@ building)	
		{
			
			@building_ = @building;
			@force = pk::get_force(building.get_force_id());
			@taishu = pk::get_person(pk::get_taishu_id(building));
			@city = pk::building_to_city(building);
			building_gold = pk::get_gold(building);
			
            if (pk::is_alive(taishu))
                @taishu_building = pk::get_building(taishu.service);
            
			menu_city_id_ = -1;
			
			if (city !is null)
				menu_city_id_ = city.get_id();
			menu_force_id_ = building.get_force_id();
			
		}
		
        bool isMenuVisible()
		{
            if (building_.get_id() >= 건물_거점끝) return false;
			return menu_city_id_ != -1 and menu_force_id_ == pk::get_current_turn_force_id();
		}
		
		//---------------------------------------------------------------------------
        // 강족
        //---------------------------------------------------------------------------

		string getText_강족()
		{
			return pk::encode("(강족)고용");
		}
		
		string getDesc_강족()
		{
            if (building_gold < GOLD_COST)
                return pk::encode(pk::format("금이 부족합니다.(금 {} 필요)", GOLD_COST));
			else if (!taishu_building.has_skill(특기_친강))
                return pk::encode("도시에 친강 특기를 소유한 무장이 없습니다.");
            else if (getEmptyPos(taishu_building) == -1)
                return pk::encode("용병을 생성할 장소가 없습니다.");
			else if (force.tp < TP_COST)
                return pk::encode(pk::format("기교P가 부족합니다.(기교P {})", TP_COST));
            else if (pk::get_district(pk::get_district_id(force, 1)).ap < ACTION_COST)
                return pk::encode(pk::format("행동력이 부족합니다.(행동력 {} 필요)", ACTION_COST));
			else
				return pk::encode(pk::format("이민족 용병을 고용합니다.(기교P {} 사용)", TP_COST));
		}

		bool isEnabled_강족()
		{
			if (building_gold < GOLD_COST) return false;
			else if (!taishu_building.has_skill(특기_친강)) return false;
            else if (getEmptyPos(taishu_building) == -1) return false;
            else if (force.tp < TP_COST) return false;
            else if (pk::get_district(pk::get_district_id(force, 1)).ap < ACTION_COST) return false;
			return true;
		}

		bool handler_강족()
		{
			
			if (pk::choose(pk::encode("이민족을 고용하시겠습니까?"), { pk::encode("예"), pk::encode("아니오") }) == 1)
				return false;
			
			if (pk::rand_bool(고용실패확률) or getEmptyPerson() is null)
			{
				int iminzoku_id = 무장_강두목;
				int face_no = 681;
				failOrNull_iminzoku(iminzoku_id, face_no);
			} 
			
			else 
			{ 
				강족생성 = true;
				set_iminzoku(); 
			}

			return true;
		}
		
		
		
		//---------------------------------------------------------------------------
        // 오환족
        //---------------------------------------------------------------------------

		string getText_오환족()
		{
			return pk::encode("(오환족)고용");
		}
		
		string getDesc_오환족()
		{
            if (building_gold < GOLD_COST)
                return pk::encode(pk::format("금이 부족합니다.(금 {} 필요)", GOLD_COST));
			else if (!taishu_building.has_skill(특기_친오))
                return pk::encode("도시에 친오 특기를 소유한 무장이 없습니다.");
            else if (getEmptyPos(taishu_building) == -1)
                return pk::encode("용병을 생성할 장소가 없습니다.");
			else if (force.tp < TP_COST)
                return pk::encode(pk::format("기교P가 부족합니다.(기교P {})", TP_COST));
            else if (pk::get_district(pk::get_district_id(force, 1)).ap < ACTION_COST)
                return pk::encode(pk::format("행동력이 부족합니다.(행동력 {} 필요)", ACTION_COST));
			else
				return pk::encode(pk::format("이민족 용병을 고용합니다.(기교P {} 사용)", TP_COST));
		}

		bool isEnabled_오환족()
		{
			if (building_gold < GOLD_COST) return false;
			else if (!taishu_building.has_skill(특기_친오)) return false;
            else if (getEmptyPos(taishu_building) == -1) return false;
            else if (force.tp < TP_COST) return false;
            else if (pk::get_district(pk::get_district_id(force, 1)).ap < ACTION_COST) return false;
			return true;
		}

		bool handler_오환족()
		{
			
			if (pk::choose(pk::encode("이민족을 고용하시겠습니까?"), { pk::encode("예"), pk::encode("아니오") }) == 1)
				return false;
			
			if (pk::rand_bool(고용실패확률) or getEmptyPerson() is null)
			{
				int iminzoku_id = 무장_오환두목;
				int face_no = 679;
				failOrNull_iminzoku(iminzoku_id, face_no);
			} 
			
			else 
			{ 
				오환족생성 = true;
				set_iminzoku(); 
			}

			return true;
		}
		

		
		//---------------------------------------------------------------------------
        // 산월족
        //---------------------------------------------------------------------------

		string getText_산월족()
		{
			return pk::encode("(산월족)고용");
		}
		
		string getDesc_산월족()
		{
            if (building_gold < GOLD_COST)
                return pk::encode(pk::format("금이 부족합니다.(금 {} 필요)", GOLD_COST));
			else if (!taishu_building.has_skill(특기_친월))
                return pk::encode("도시에 친월 특기를 소유한 무장이 없습니다.");
            else if (getEmptyPos(taishu_building) == -1)
                return pk::encode("용병을 생성할 장소가 없습니다.");
			else if (force.tp < TP_COST)
                return pk::encode(pk::format("기교P가 부족합니다.(기교P {})", TP_COST));
            else if (pk::get_district(pk::get_district_id(force, 1)).ap < ACTION_COST)
                return pk::encode(pk::format("행동력이 부족합니다.(행동력 {} 필요)", ACTION_COST));
			else
				return pk::encode(pk::format("이민족 용병을 고용합니다.(기교P {} 사용)", TP_COST));
		}

		bool isEnabled_산월족()
		{
			if (building_gold < GOLD_COST) return false;
			else if (!taishu_building.has_skill(특기_친월)) return false;
            else if (getEmptyPos(taishu_building) == -1) return false;
            else if (force.tp < TP_COST) return false;
            else if (pk::get_district(pk::get_district_id(force, 1)).ap < ACTION_COST) return false;
			return true;
		}

		bool handler_산월족()
		{
			
			if (pk::choose(pk::encode("이민족을 고용하시겠습니까?"), { pk::encode("예"), pk::encode("아니오") }) == 1)
				return false;

			if (pk::rand_bool(고용실패확률) or getEmptyPerson() is null)
			{
				int iminzoku_id = 무장_산월두목;
				int face_no = 683;
				failOrNull_iminzoku(iminzoku_id, face_no);		
			}
			
			else 
			{ 
				산월족생성 = true;
				set_iminzoku(); 
			}

			return true;
		}
		
		
		
		//---------------------------------------------------------------------------
        // 남만족
        //---------------------------------------------------------------------------

		string getText_남만족()
		{
			return pk::encode("(남만족)고용");
		}
		
		string getDesc_남만족()
		{
            if (building_gold < GOLD_COST)
                return pk::encode(pk::format("금이 부족합니다.(금 {} 필요)", GOLD_COST));
			else if (!taishu_building.has_skill(특기_친만))
                return pk::encode("도시에 친만 특기를 소유한 무장이 없습니다.");
            else if (getEmptyPos(taishu_building) == -1)
                return pk::encode("용병을 생성할 장소가 없습니다.");
			else if (force.tp < TP_COST)
                return pk::encode(pk::format("기교P가 부족합니다.(기교P {})", TP_COST));
            else if (pk::get_district(pk::get_district_id(force, 1)).ap < ACTION_COST)
                return pk::encode(pk::format("행동력이 부족합니다.(행동력 {} 필요)", ACTION_COST));
			else
				return pk::encode(pk::format("이민족 용병을 고용합니다.(기교P {} 사용)", TP_COST));
		}

		bool isEnabled_남만족()
		{
			if (building_gold < GOLD_COST) return false;
			else if (!taishu_building.has_skill(특기_친만)) return false;
            else if (getEmptyPos(taishu_building) == -1) return false;
            else if (force.tp < TP_COST) return false;
            else if (pk::get_district(pk::get_district_id(force, 1)).ap < ACTION_COST) return false;
			return true;
		}

		bool handler_남만족()
		{
			
			if (pk::choose(pk::encode("이민족을 고용하시겠습니까?"), { pk::encode("예"), pk::encode("아니오") }) == 1)
				return false;

			if (pk::rand_bool(고용실패확률) or getEmptyPerson() is null)
			{
				int iminzoku_id = 무장_남만두목;
				int face_no = 685;
				failOrNull_iminzoku(iminzoku_id, face_no);	
			} 
			
			else 
			{ 
				남만족생성 = true;
				set_iminzoku(); 
			}

			return true;
		}
		
		
		void failOrNull_iminzoku(int iminzoku_id, int face_no)
		{
			
			string taishu_name = pk::decode(pk::get_name(taishu));
			pk::person@ iminzoku = pk::get_person(iminzoku_id);
			
			iminzoku.face = face_no;
			iminzoku.update();

			pk::message_box(pk::encode(pk::format("미안하지만 지금은 우리도 \x1b[1x{}\x1b[0x공을 도울 여유가 없소.", taishu_name)), iminzoku);
			pk::message_box(pk::encode("음.. 그렇다면 어쩔 수 없지요."), taishu);
			pk::message_box(pk::encode(pk::format("대신 평소 \x1b[1x{}\x1b[0x공과의 우의를 생각하여 군량을 내어주겠소.", taishu_name)), iminzoku);
			pk::message_box(pk::encode("허허, 그래도 내가 헛걸음을 하지는 않은 셈이군요."), taishu);
			
			pk::message_box(pk::encode("이민족 용병 고용에 실패하였습니다."));
			
			// 기교 감소 및 병량 증가
			pk::message_box(pk::encode(pk::format("기교 포인트가 \x1b[1x{}\x1b[0x만큼 감소했습니다.", TP_COST)));
			pk::add_tp(force, -TP_COST, force.get_pos());
			pk::message_box(pk::encode(pk::format("병량이 \x1b[1x{}\x1b[0x만큼 증가했습니다.", ADD_FOOD)));
			pk::add_food(city, ADD_FOOD, true);

			
			// 행동력 감소.
			auto district = pk::get_district(pk::get_district_id(force, 1));
			district.ap -= ACTION_COST;
			
		} // void failOrNull_iminzoku(pk::person@ iminzoku)


		void set_iminzoku()
		{
			
			string taishu_name = pk::decode(pk::get_name(taishu));
			pk::person@ iminzoku = getEmptyPerson();
					
			int district_num = pk::get_district_id(force, 1);
		
			pk::set_district(iminzoku, district_num);

			iminzoku.sex = 성별_남;
			
			if (이름자동)
			{
				iminzoku.sei = pk::get_family_name(random(성씨_끝 - 1)).name; // 성
				iminzoku.mei = pk::get_family_name(random(성씨_끝 - 1)).name; // 명
			}
			
			if (이름수동)
			{
				iminzoku.sei = pk::encode(sei_[random(i, j)]); // 성
				iminzoku.mei = pk::encode(mei_[random(i, j)]); // 명
			}
			
			
			if (강족생성) { iminzoku.face = 681; } // 오환족 얼굴 설정
			if (오환족생성) { iminzoku.face = 679; } // 오환족 얼굴 설정
			if (산월족생성) { iminzoku.face = 683; } // 산월족 얼굴 설정
			if (남만족생성) { iminzoku.face = 685; } // 남만족 얼굴 설정
			
			// 강족/오환족 무장 조형, 병종 설정
			if (강족생성 or 오환족생성)
			{
				// 무장 조형
				iminzoku.skeleton = 0;
				iminzoku.body[0] = 71;
				iminzoku.body[1] = 71;
				iminzoku.body[2] = 71;
				iminzoku.body[3] = 71;
				iminzoku.body[4] = 71;
				iminzoku.body[5] = 71;
				
				// 병종 설정.
				iminzoku.tekisei[병종_기병] = 적성_S;
				iminzoku.tekisei[병종_창병] = random(0, 2);
				iminzoku.tekisei[병종_극병] = random(0, 2);
				iminzoku.tekisei[병종_노병] = random(0, 2);
				iminzoku.tekisei[병종_병기] = random(0, 2);
				iminzoku.tekisei[병종_수군] = random(0, 2);
			}

			// 산월족/남만족 무장 조형, 병종 설정
			if (산월족생성 or 남만족생성)
			{
				// 무장 조형
				iminzoku.skeleton = 2;
				iminzoku.body[0] = 72;
				iminzoku.body[1] = 72;
				iminzoku.body[2] = 72;
				iminzoku.body[3] = 72;
				iminzoku.body[4] = 72;
				iminzoku.body[5] = 72;
				
				// 병종 설정.
				iminzoku.tekisei[병종_극병] = 적성_S;
				iminzoku.tekisei[병종_기병] = random(0, 2);
				iminzoku.tekisei[병종_창병] = random(0, 2);
				iminzoku.tekisei[병종_노병] = random(0, 2);
				iminzoku.tekisei[병종_병기] = random(0, 2);
				iminzoku.tekisei[병종_수군] = random(0, 2);	
			}

			iminzoku.mibun = 신분_일반;
			iminzoku.loyalty = 100;
			iminzoku.rank = -1;
			iminzoku.birth = pk::get_year() - 30;
			iminzoku.death = pk::min(353, iminzoku.birth + 99);
			iminzoku.appearance = pk::get_year() - 10;
			iminzoku.kouseki = 1000;
			
			// 친애무장, 혐오무장 초기화
			for (int i = 0; i < 5; i++)
			{
				iminzoku.liked[i] = -1;
				iminzoku.disliked[i] = -1;
			}
			
			iminzoku.liked[0] = force.kunshu;
			
			iminzoku.birthplace = random(주_끝 - 1);
			iminzoku.skill = random(특기_끝) - 1;
			iminzoku.wadai = random(화제_끝 - 1);
			iminzoku.giri = random(의리_끝 - 1);
			iminzoku.ambition = random(야망_끝 - 1);
			iminzoku.promotion = random(기용_끝 - 1);
			iminzoku.character = random(성격_끝 - 1);
			iminzoku.voice = iminzoku.sex == 성별_남 ? random(음성_소심남, 음성_저돌남) : random(음성_냉정녀, 음성_대담녀);
			iminzoku.tone = iminzoku.sex == 성별_남 ? random(말투_장비, 말투_보통남) : random(말투_고대만족, 말투_보통녀);
			iminzoku.kanshitsu = random(한실_끝 - 1);
			iminzoku.strategic_tendency = random(전략경향_끝 - 1);
			iminzoku.local_affiliation = random(지역집착_끝 - 1);
			
			int random_n = pk::rand(4); // 0, 1, 2, 3
				
			for (int i = 0; i < 무장능력_끝; i++)
			{
				
				// 0-무관형, 1-문관형, 2-만능형, 3-RANDOM 
				
				// 0-무관형
				if (random_n == 0)
				{
					
					if (i == 무장능력_통솔)
					{
						iminzoku.base_stat[i] = random(min_stat_무관형_통솔, max_stat_무관형_통솔);
					}
					
					else if (i == 무장능력_무력)
					{
						iminzoku.base_stat[i] = random(min_stat_무관형_무력, max_stat_무관형_무력);
					}
					
					else if (i == 무장능력_지력)
					{
						iminzoku.base_stat[i] = random(min_stat_무관형_지력, max_stat_무관형_지력);
					}
					
					else if (i == 무장능력_정치)
					{
						iminzoku.base_stat[i] = random(min_stat_무관형_정치, max_stat_무관형_정치);
					}
					
					else
					{
						iminzoku.base_stat[i] = random(min_stat_매력, max_stat_매력);
					}

				} // if (random_n == 0)

				// 1-문관형
				else if (random_n == 1)
				{
					
					if (i == 무장능력_통솔)
					{
						iminzoku.base_stat[i] = random(min_stat_문관형_통솔, max_stat_문관형_통솔);
					}
					
					else if (i == 무장능력_무력)
					{
						iminzoku.base_stat[i] = random(min_stat_문관형_무력, max_stat_문관형_무력);
					}
					
					else if (i == 무장능력_지력)
					{
						iminzoku.base_stat[i] = random(min_stat_문관형_지력, max_stat_문관형_지력);
					}
					
					else if (i == 무장능력_정치)
					{
						iminzoku.base_stat[i] = random(min_stat_문관형_정치, max_stat_문관형_정치);
					}
					
					else
					{
						iminzoku.base_stat[i] = random(min_stat_매력, max_stat_매력);
					}
					
				} // else if (random_n == 1)
				
				// 2-만능형
				else if (random_n == 2)
				{
					
					if (i == 무장능력_통솔)
					{
						iminzoku.base_stat[i] = random(min_stat_만능형_통솔, max_stat_만능형_통솔);
					}
					
					else if (i == 무장능력_무력)
					{
						iminzoku.base_stat[i] = random(min_stat_만능형_무력, max_stat_만능형_무력);
					}
					
					else if (i == 무장능력_지력)
					{
						iminzoku.base_stat[i] = random(min_stat_만능형_지력, max_stat_만능형_지력);
					}
					
					else if (i == 무장능력_정치)
					{
						iminzoku.base_stat[i] = random(min_stat_만능형_정치, max_stat_만능형_정치);
					}
					
					else
					{
						iminzoku.base_stat[i] = random(min_stat_매력, max_stat_매력);
					}
					
				} // else if (random_n == 2)
					
				// 3-RANDOM
				else if (random_n == 3)
				{
					iminzoku.base_stat[i] = random(1, 100);
				} 
				
				iminzoku.stat_aging[i] = random(능력성장_초지속형, 능력성장_장비형);
			}
			
			// 능력치 반영.
			iminzoku.update();
			
			int gold = 1000;
			int food = int(troops * 1.3f);
			
			
			// 생성될 부대 포지션이 문제 있으면 부대를 생성하지 않는다.		
			pk::point emptyPos = getEmptyPos(taishu_building);
			
			if (!pk::is_valid_pos(emptyPos)) return;
				
			pk::unit@ unit = pk::create_unit(taishu_building, iminzoku, null, null, troops, 병기_극, 병기_주가, gold, food, emptyPos);

			// 기력 설정(pk::create_unit 함수의 첫 번째 파라미터로 결정했다면 필요없음.)
			unit.energy = 100;
			
			// 부대 이동 불가 시 부대 및 무장 삭제 후 중단
			if (pk::get_movable_pos(unit).length == 0) {pk::kill(unit);	pk::reset(iminzoku);	return;}

			// 부대 생성 실패 시 부대 및 무장 삭제 후 중단
			if (!pk::is_alive(unit)) {pk::kill(unit); pk::reset(iminzoku);}
			
			string iminzoku_name = pk::decode(pk::get_name(iminzoku));
			
			pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x공, 이곳까지 오느라 수고가 많으셨소.", iminzoku_name)), taishu);
			pk::message_box(pk::encode(pk::format("하하하! \x1b[1x{}\x1b[0x님을 위해서 싸울 준비가 되어 있으니 염려마십시오!", taishu_name)), iminzoku);
			pk::message_box(pk::encode("이것은 나를 도와준 대가로 주는 보답이오."), taishu);
			pk::message_box(pk::encode("오! 이렇게나 많은 금을 주시다니 감사합니다."), iminzoku);
			pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x공의 은혜는 내 잊지 않겠소.", iminzoku_name)), taishu);
			
			pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x(이)가 아군으로 합류하였습니다.", iminzoku_name)));
				
			// 기교 및 금 감소
			pk::message_box(pk::encode(pk::format("기교 포인트가 \x1b[1x{}\x1b[0x만큼 감소했습니다.", TP_COST)));
			pk::add_tp(force, -TP_COST, force.get_pos());
			pk::message_box(pk::encode(pk::format("도시의 금이 \x1b[1x{}\x1b[0x만큼 감소했습니다.", GOLD_COST)));
			pk::add_gold(city, -GOLD_COST, true);
			
			// 행동력 감소.
			auto district = pk::get_district(pk::get_district_id(force, 1));
			district.ap -= ACTION_COST;
			
			강족생성 = false;
			오환족생성 = false;
			산월족생성 = false;
			남만족생성 = false;
			
		} // set_iminzoku()
		
		
		pk::point getEmptyPos(pk::building@ building)
		{
			auto arr = pk::range(building.get_pos(), min_distance, max_distance);
			for (int i = 0; i < arr.length; i++)
			{
				pk::hex@ hex = pk::get_hex(arr[i]);
				int terrain_id = hex.terrain;
				
				if (!hex.has_building and !hex.has_unit
					and pk::is_valid_terrain_id(terrain_id) 
					and pk::is_enabled_terrain(terrain_id)
					and terrain_id != 지형_산)
					return arr[i];
				
			}
			return -1;
		}
		
		
		pk::person@ getEmptyPerson()
		{
			if (slot_일반무장)
			{
				for (int i = 0; i < 700; i++)
				{
					
					pk::person@ iminzoku = pk::get_person(i);
					
					switch (iminzoku.mibun)
					{
					case 신분_없음:
					case 신분_사망:
						return iminzoku;
					}

				}
			}
			
			if (slot_신무장)
			{
				for (int i = 960; i < 신무장_끝; i++)
				{
					pk::person@ iminzoku = pk::get_person(i);
					switch (iminzoku.mibun)
					{
					case 신분_없음:
					case 신분_미등장:
					case 신분_사망:
						return iminzoku;
					}
				}
			}
			
			if (slot_고대무장)
			{
				for (int i = 832; i < 850; i++)
				{
					pk::person@ iminzoku = pk::get_person(i);
					switch (iminzoku.mibun)
					{
					case 신분_없음:
					case 신분_미등장:
					case 신분_사망:
						return iminzoku;
					}
				}
			}
			
			return null;
			
		} // pk::person@ getEmptyPerson()
		

	}

	Main main;
}