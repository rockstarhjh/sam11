/*
@만든이: Tester
@설명: 외교 인공지능
@버전: 2.5.0

@수정 : 크래픽스
2023.8.20,연합군 결성시, 군주병력과, 숙련병이 적용되지 않던문제를 수정
2023.8.26,연합군 결성시, 군주병력과, 숙련병이 아니고 군제개혁임

*/

			
namespace 외교전쟁
{
	///////////////////////////////////////////////////////////////////////////////
	/////////////////////////////				///////////////////////////////////
	/////////////////////////////	CUSTOMIZE	///////////////////////////////////
	/////////////////////////////				///////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	const float 우호도증감기준 = 10.0;	
	const bool 연합적과세력비교 = true;	
	const int 연합결성소비타입 = 1; // 0 = 기교포인트, 1 = 행동력
	const int 추가연합성공률 = 0;		
	const bool 항상최대병력출진 = false;
	const bool 출진_도시병력내 = true;
	const int 최소출진병력수 = 2500;
	const int 한도시최대출진부대수 = 15;
	const float 유저_추가연합성공률 = 0.2;
	const float 군주최소배신계수 = 0.5;

	///////////////////////////////////////////////////////////////////////////////
	
	const int8 속성_도시수 = 0;
	const int8 속성_무장수 = 1;
	const int8 속성_병력 = 2;
	const int8 속성_탑10 = 3;
	const int8 속성_세력순위 = 4; // 사용안함
	const int8 속성_인접적수 = 5;
	const int8 속성_금 = 6;
	const int8 속성_병량 = 7;	
	const int8 속성_끝 = 8; // 세력 속성 갯수
             
	const int8 판단_판단주체 = 0;
	const int8 판단_판단대상 = 1;
	const int8 판단_군주 = 2;
	const int8 판단_인접여부 = 3;
	const int8 판단_도시수 = 4;
	const int8 판단_무장수 = 5;
	const int8 판단_병력	= 6;
	const int8 판단_황제보호여부 = 7;
	const int8 판단_우호도 = 8;
	const int8 판단_궁합	= 9;
	const int8 판단_탑10 = 10;
	const int8 판단_적여부 = 11;
	const int8 판단_인접허용적수 = 12;
	const int8 판단_전쟁중여부	= 13;
	const int8 판단_적의적 = 14;
	const int8 판단_동맹의적 = 15;
	const int8 판단_친애여부 = 16;
	const int8 판단_혐오여부 = 17;
	const int8 판단_배신	= 18;
	const int8 판단_인접적도시수합 = 19;
	const int8 판단_인접적무장수합 = 20;
	const int8 판단_인접적병력합 = 21;
	const int8 판단_군사능력 = 22;
	const int8 판단_결과	= 23;
	const int8 판단_끝 = 24;
	
	const int8 인접적합_도시수 = 0;
	const int8 인접적합_무장수 = 1;
	const int8 인접적합_병력 = 2;
	const int8 인접적합_끝 = 3;
	
	const int8 디버깅 = 1;
	const int KEY = pk::hash("연합결성");

	class Main
	{
		
		
		// 변수			
		array<array<float>> 판단가중치(세력_끝, array<float>(판단_끝+1, -1.f));
		array<array<bool>> 판단호불호(세력_끝, array<bool>(판단_끝+1, true));		
		array<array<int>> 세력부가속성(세력_끝, array<int>(속성_끝, -1)); // 추가 세력 속성 값 저장			
		array<float> 판단(판단_끝, -1.f);
		array<array<float>> 세력대판단(세력_끝 * 세력_끝, 판단);
		array<array<float>> 세력대판단결과(세력_끝, array<float>(세력_끝, 0.f));
		array<array<int8>> 세력외교대상(세력_끝, array<int8>(세력_끝, -1)); // 세력외교거리 중복체크용
		array<array<int8>> 세력대전쟁여부(세력_끝, array<int8>(세력_끝, -1)); // 1: 전쟁중
		array<int8> 전쟁중여부(세력_끝, -1); // 1: 전쟁중
		array<int8> 건물전쟁여부(건물_끝, -1); // 1: 전쟁중
		array<int8> 도시경계여부(건물_끝, -1); // 1: 적부대가 아군영역에 있을 때
		array<array<int8>> 세력적의적(세력_끝, array<int8>(세력_끝, -1));
		array<array<int8>> 세력동맹의적(세력_끝, array<int8>(세력_끝, -1));
		dictionary 배신거점착발지연;
		dictionary 부대출진후_경과;
		array<array<int>> 인접적합모두(세력_끝, array<int>(인접적합_끝, -1));
		array<array<int8>> 세력대세력거리(세력_끝, array<int8>(세력_끝, 3)); // 값이 클 수록 멀다
		
		float 연합적확정계수 = 0.6; /// 0.7	
		int8 거점전쟁판단_범위 = 6;
		int8 부대전쟁판단_범위 = 4;
		int8 배신공격_지연 = 6; // *10일
		float 기준_칸이동력 = 4.0; // 이동력 20 기준
		bool is_세력금병량검색 = false;
		
		int index_세력대판단 = 0;								
		int8 daysOfMonth = 0;		
		int8 외교전쟁시작 = 0;
		
				
		// 연합공격		
		// 연합확률 요소: 전쟁중인 세력 중 병력이 가장 많은 세력, 적이 많은 세력, 군사 능력
		// 연합세력은 set_세력대판단() 후에 세력적의적 변수로 정한다.
		// isBetray() 에서 연합세력이 공격할 인접한 도시(공격대상세력의 도시)  저장.
		array<float> prob_연합적(세력_끝, -2.f);
		array<pk::int_int> prob_연합적_desc(); // 연합적확률이 높은 순으로 동적 배열
		array<int8> rank_세력병사(47, -1);
		array<int8> rank_인접적수(47, -1);
		int8 연합공격적 = 0;
		array<int8> 연합시도(세력_끝, -1); // 연합 시도한 연맹주 세력 중복방지		
		int8 연합시도지연_일수 = 12;
		array<int8> 연합성공지연(세력_끝, -1); // 연합 성공한 연합군 세력 연합시도 방지
		int8 연합성공지연_일수 = 40;
		array<array<int>> 진행중인연합세력();
		int8 조공여부 = 1;
		array<int8> 조공패스(세력_끝, 0);
		
		// 연합공격 커맨드
		// 건물 메뉴 도시
		int menu_city_id_;
		// 건물 메뉴 세력
		int menu_force_id_;
		// 메뉴 활성화 여부
		int8 메뉴기능활성화 = -1;
		int8 플레이어연합적 = -1;
		// array<int8> 유저연합결성중복시도(세력_끝, -1);		
		string 연합공작말 = "";		
		array<int8> 유저_연합성공(세력_끝, -1);	
		int8 유저_연합성공지연_일수 = 10;
		// 동맹 결과 잡기
		array<int> 동맹정보인자(2, -1);		
		int 동맹결과딜레이 = 0;
		bool 동맹화면시작 = false;
		
		int 필요행동력 = 100;    // (행동력 필요량: 기본  설정)
		int 필요기교포인트 = 1000; 	   // (기교P 필요량: 기본  설정)
				
		int 부대생성_금 = 2000;
		float 부대생성_병량비율 = 2.0;
		array<int> 세력출진병력(세력_끝, 0); // 연합결성시 세력별 출진병력
		float 군주배수_player = 4.0; // 연합군 병력비교시 적 대비 플레이어 최대 배수
		array<int8> 사신보내기(세력_끝, -1);	
		int8 사신보내기_일수 = 10;		
		
		int line_bigO = 0;
		
		pk::func112_t@ prev_func112_;
		
		
		Main()
		{
			init();
		}
		
		
		// 초기화
		void init()
		{			
			TestLOG();
		
			pk::bind(104, pk::trigger104_t(onScenarioEnd));
			pk::bind(107, pk::trigger107_t(onNewDay));
			pk::bind(108, pk::trigger108_t(onNewMonth));
			pk::bind(109, pk::trigger109_t(onNewSeason));
			pk::bind(110, pk::trigger110_t(onNewYear));
			pk::bind(111, pk::trigger111_t(onTurnStart));
			pk::bind(112, pk::trigger112_t(onTurnEnd));
			pk::bind(120, pk::trigger120_t(onDrawGame));
			
			@prev_func112_ = cast<pk::func112_t@>(pk::get_func(112));
			pk::reset_func(112);
			pk::set_func(112, pk::func112_t(func112));
			
			initMenuItem();
		}	
		
		void TestLOG()
		{
			// util.prnt("string to int ["+parseInt("2.0")+"]");
			// array<string> arr = "asdfsf|sdfsdf|sdfsdf|".split("|");
			// util.prnt("splited string count=["+arr.length+"] [3]=["+arr[2]+"]");
			// util.prnt("neighborMap length yangpyeong=["+neighborMap.인접건물[건물_양평].length+"] bukpyeong=["+neighborMap.인접건물[건물_북평].length+"]");

		}
		
		void initMenuItem()
		{
			
			// 메뉴 생성			
			pk::menu_item item;
			item.menu = 103;
			item.init = pk::building_menu_item_init_t(initMenu);
			item.is_visible = pk::menu_item_is_visible_t(isMenuVisible);
			item.get_text = pk::menu_item_get_text_t(getMenuText);
			item.is_enabled = pk::menu_item_is_enabled_t(isEnabled);
			item.get_desc = pk::menu_item_get_desc_t(getMenuDesc);
			// item.get_image_id = pk::menu_item_get_image_id_t(getMenuImageID);
			item.handler = pk::menu_item_handler_t(menuHandler);
			pk::add_menu_item(item);
			
		}
		
		pk::int_bool func112(const pk::alliance_cmd_info &in info)
		{
			// util.prnt("reset func112 info actor=["+info.actor.get_force_id()+"] target=["+info.target.get_id()+"]");
			
			// AI 가 플레이어에게 동맹요청시
			if(!pk::get_force(info.actor.get_force_id()).is_player() and info.target.is_player()){
				동맹정보인자[0] = info.actor.get_force_id();
				동맹정보인자[1] = info.target.get_id();
				동맹화면시작 = true;
			}
			
			// 이전 핸들러가 있다면 체인.
			if (prev_func112_ !is null){
				return prev_func112_(info);
			}
			return cast<pk::func112_t@>(pk::get_func(112, true))(info);	
		}
		
		void onDrawGame()
		{
			// cursorOnCity();
			onAllianceCommandCallback();			
				
		}
		
		void onAllianceCommandCallback(){
			if(!동맹화면시작)return;
			// pk::printf(pk::encode("delay=["+동맹결과딜레이+"] \n"));
			
			동맹결과딜레이 += 1;
			if(동맹결과딜레이 > 3){						
				동맹화면시작 = false;
				동맹결과딜레이 = 0;
				// 여기서 동맹 결과 처리
				bool 동맹성공여부 = !pk::is_enemy(동맹정보인자[0], 동맹정보인자[1]);
				
				if(!동맹성공여부){
					pk::add_relations(pk::get_force(동맹정보인자[0]), 동맹정보인자[1], -40);	
				}				
			}			
			
		}
		
		// 도시 중복 포인트 방지
		int cursor_city_id = -1; 
		
		void cursorOnCity()
		{		
			pk::point cursor_pos = pk::get_cursor_hex_pos();
			if(!pk::is_valid_pos(cursor_pos)) return;
			pk::hex@ hex = pk::get_hex(cursor_pos);
			int terrain_id = hex.terrain;
			if(terrain_id != 지형_도시){cursor_city_id = -1; return;} // 도시 지형인가?
			int city_id = pk::get_city_id(cursor_pos);
			if(!pk::is_valid_city_id(city_id))return; 
			if(cursor_city_id == city_id)return; // 중복 포인트 도시 인가?									
			pk::city@ city_cursor = pk::get_city(city_id);
			if(city_cursor.is_player())return; // 플레이어 도시인가?
			
			cursor_city_id = city_id;
			// util.prnt("cursor city_id=["+city_id+"]");
			
			string city_cursor_name = pk::decode(pk::get_name(city_cursor));
			pk::say(pk::encode("여기는 "+city_cursor_name+" 입니다"), pk::get_person(city_cursor.taishu), city_cursor);
		}
		
		
		
		void initializeOnNewSeason(){
			
		}
		
		void initializeOnNewMonth()
		{			
			세력외교대상 = array<array<int8>>(세력_끝, array<int8>(세력_끝, -1));
			세력부가속성 = array<array<int>>(세력_끝, array<int>(속성_끝, -1.f));	
			rank_세력병사 = array<int8>(47, -1);		
		}
		
		void initializeOnNewDay()
		{			
				
			rank_인접적수 = array<int8>(47, -1);	
			prob_연합적 = array<float>(세력_끝, -2.f);		
			전쟁중여부 = array<int8> (세력_끝, -1);
			건물전쟁여부 = array<int8>(건물_끝, -1);
			도시경계여부 = array<int8>(건물_끝, -1);
			세력대전쟁여부 = array<array<int8>>(세력_끝, array<int8>(세력_끝, -1));			
			세력적의적 = array<array<int8>>(세력_끝, array<int8>(세력_끝, -1));
			세력동맹의적 = array<array<int8>>(세력_끝, array<int8>(세력_끝, -1));
			인접적합모두 = array<array<int>>(세력_끝, array<int>(인접적합_끝, -1));			
		}

		// bind
		/*
		달 마다 수집해야할 데이터와 날 마다 수집할 데이터로 구분
		*/
		
		void onNewYear()
		{
			// if(외교전쟁시작 == 0)return;
			//pk::printf(pk::encode("onNewYear get_month=["+pk::get_month()+"]\n"));
			//pk::printf(pk::encode("Start! AnnualTribute \n"));
		}	
		
		void onNewSeason()
		{
			// if(외교전쟁시작 == 0)return;
			
			//pk::printf(pk::encode("Start! AllianceAttack \n"));			
			
			// 반년에 한번
			if(pk::get_month() == 1 or pk::get_month() == 7)조공여부 = 0;
			
			// 시즌 단위 초기화
			initializeOnNewSeason();
		}	

		
		void onNewMonth()
		{
			외교전쟁시작 = 1;
			// pk::printf(pk::encode("onNewMonth \n"));
			
			is_세력금병량검색	= false;		
			
			// 초기화
			initializeOnNewMonth();
			
			setForceAttributes();
					
			
		}
		
		void onNewDay()
		{					
			if(외교전쟁시작 == 0)return;
			
			// pk::printf(pk::encode("onNewDay \n"));
			line_bigO = 0;			
			
			initializeOnNewDay();
			
			decrease_배신거점발착딜레이();
			decrease_부대출진후_경과();
			if(!is_세력금병량검색)setForceGoldFood();
			setIsAtWar();
			// util.prnt("bigO line=["+line_bigO+"] setIsAtWar");
			
			index_세력대판단 = 0;
			set_세력대판단();			
			set_세력대판단_weight();
			// util.prnt("bigO line=["+line_bigO+"] index_forcejudge=["+index_세력대판단+"]  set_forcejudge");
			AddRelationValue();
			// util.prnt("bigO line=["+line_bigO+"] AddRelationValue");
			
			// AnnualTribute
				
			set_rank_인접적수();
			set_prob_연합적();				
			// util.prnt("bigO line=["+line_bigO+"] allianceAttack_Probability");
			search_연합적();
			// util.prnt("bigO line=["+line_bigO+"] search_alliance_enemy");
			
			
		}
		
		void onTurnStart(pk::force@ force){
			if(외교전쟁시작 == 0)return;				
			if(isIminzoku(force))return; //이민족 제외	
			
			// util.prnt("onTurnStart kunshu=["+force.kunshu+"]");
			
			// 메뉴 주인 세팅
			if (force.is_player()){				
				pk::list<pk::city@> cityList = pk::get_city_list(force);
				pk::building@ building0 = pk::city_to_building(cityList[0]);
				initMenu(building0);
			}
			decrease_유저연합시도지연(force.get_id());		
			decrease_연합시도지연(force.get_id());
			decrease_연합성공지연(force.get_id());
			decrease_사신보내기(force.get_id());
			
			if(조공여부 != 1)AnnualTribute(force);			
			if (force.is_player()){
				메뉴기능활성화 = 1;
				// decrease_유저연합결성중복시도();
			}		
			BetrayalAttack(force);// 배신공격
			
		}
		
		void onTurnEnd(pk::force@ force)
		{
			// util.prnt("onTurnEnd kunshu=["+force.kunshu+"]");
			if (force.is_player())메뉴기능활성화 = 0;
			
		}
		
		
		
		
		
		
		
		
		
		
		void onScenarioEnd()
		{
			// util.prnt("Scenario End.");
			DeinitLoop();
			메뉴기능활성화 = -1;
			외교전쟁시작 = 0;
			
		}
		
		void DeinitLoop()
		{
			배신거점착발지연.deleteAll();
			부대출진후_경과.deleteAll();
			연합시도 = array<int8>(세력_끝, -1);
			연합성공지연 = array<int8>(세력_끝, -1);	
			유저_연합성공 = array<int8>(세력_끝, -1);
			사신보내기 = array<int8>(세력_끝, -1);
			진행중인연합세력 = array<array<int>>();	
			조공패스 = array<int8>(세력_끝, 0);
			
		}
		
		void decrease_배신거점발착딜레이(){			
			for (int i=0; i<배신거점착발지연.getKeys().length; i++)
			{
				// line_bigO++;
				string key = 배신거점착발지연.getKeys()[i];
				int delay = int(배신거점착발지연[key]);
				배신거점착발지연[key] = delay - 1;	
				// util.prnt("delay mod key=["+key+"] val=["+int(배신거점착발지연[key])+"]");
				if(delay <= 1)배신거점착발지연.delete(key);				
			}
			
		}
		void decrease_부대출진후_경과(){			
			for (int i=0; i<부대출진후_경과.getKeys().length; i++)
			{
				// line_bigO++;
				string key = 부대출진후_경과.getKeys()[i];
				int days = int(부대출진후_경과[key]);
				부대출진후_경과[key] = days - 1;	
				// util.prnt("days mod key=["+key+"] val=["+int(부대출진후_경과[key])+"]");
				if(days <= 1){
					// util.prnt("days del key=["+key+"] val=["+int(부대출진후_경과[key])+"]");	
					부대출진후_경과.delete(key);					
				}			
			}
			
		}
		
		void decrease_연합성공지연(int force_id){
			
			
			// 연합성공지연 +한달
			if(연합성공지연[force_id] <= 0 ){
				연합성공지연[force_id] = -1;  
				// util.prnt("alliance_being_forces count=" + 진행중인연합세력.length);
				if(contain_진행중인연합세력(force_id)){					
					진행중인연합세력.removeAt(0);
					// util.prnt("remove alliance_being_forces count=" + 진행중인연합세력.length);
				}
			}
			else if(연합성공지연[force_id] > 0){
				연합성공지연[force_id] -= 1; 
				// util.prnt("allianceAttackDelay force_kunshu=["+pk::get_force(force_id).kunshu+"] delay=["+연합성공지연[force_id]+"] ");
				
			}
			
		}
		
		void decrease_연합시도지연(int force_id){			
			if(연합시도[force_id] >= 0){
				연합시도[force_id] -= 1; 
				// util.prnt("try_allianceAttack force_kunshu=["+pk::get_force(force_id).kunshu+"] delay=["+연합시도[force_id]+"] ");
			}
		}
		void decrease_유저연합시도지연(int force_id){			
			if(유저_연합성공[force_id] >= 0){
				유저_연합성공[force_id] -= 1; 
				// util.prnt("UserAllianceAttack force_kunshu=["+pk::get_force(force_id).kunshu+"] delay=["+유저_연합성공[force_id]+"] ");
			}
		}
		void decrease_사신보내기(int force_id){			
			if(사신보내기[force_id] >= 0){
				사신보내기[force_id] -= 1; 
				// util.prnt("Send_Sasin force_kunshu=["+pk::get_force(force_id).kunshu+"] delay=["+사신보내기[force_id]+"] ");
			}
		}
		
		bool contain_진행중인연합세력(int force0_id){
			if(진행중인연합세력.length == 0)return false;
			string str = "force0_id= ["+force0_id+"] ";
			for (int i = 0; i < 진행중인연합세력[0].length; i++){
				str += 진행중인연합세력[0][i] + ", ";
				// util.prnt("allianceBeingForces0 force0_id=["+force0_id+"] value=["+진행중인연합세력[0][i]+"] kunshu=["+pk::get_force(진행중인연합세력[0][i]).kunshu+"] ");
				if(진행중인연합세력[0][i] == force0_id)return true;
			}
			// util.prnt(str);
			return false;
		}
		
		
		
		
		
		// 조공 요구
		void AnnualTribute(pk::force@ force0)
		{
			if(!force0.is_player())return;
			
			int force0_id = force0.get_id();
			
			// 조공 요구 세력 찾기
			int force_threat_id = -1;
			int troops_temp = -1;
			float dislike = 0.f; // 음수
			for (int i = 0; i < index_세력대판단; i++){
				// 상대방
				int force_u_id = int(세력대판단[i][판단_판단주체]);
				// 나
				int force_i_id = int(세력대판단[i][판단_판단대상]);					
				if(force0_id != force_i_id)continue;
				if(pk::get_force(force_u_id).is_player())continue;
				if(세력대판단[i][판단_적여부] == 1)continue;				
				if(세력대판단[i][판단_도시수] > 0)continue; //상대 세력이 나보다 약할 경우 패스
				
				// 상대방이 나를 원함정도.
				float want = 세력대판단[i][판단_결과];

				//pk::person@ kunshu = pk::get_person(pk::get_force(force_u_id).kunshu);
				//pk::printf(pk::encode("AnnualTribute() force_u_id=["+force_u_id+"] force_u_kunshu=["+kunshu.get_id()+"] force_u_want_me=["+want+"] \n"));
				
				
				if(want > 0)continue;
				
				// 조공 요구 세력 정하기
				if(want < dislike){
					force_threat_id = force_u_id;				
					dislike = want;
				}
				
				/*
				// 동맹 중 병력이 제일 많은 세력
				int troops_u = 세력부가속성[force_u_id][속성_병력];
				if(troops_temp < troops_u){
					force_threat_id = force_u_id;				
					dislike = want;
				}
				troops_temp = pk::max(troops_u, troops_temp);
				*/
				
				
			} // end - for
			
			//pk::printf(pk::encode("AnnualTribute force_threat_id=["+force_threat_id+"] pass_tribute=["+조공패스[force_threat_id]+"] \n"));
			
			if(force_threat_id == -1){ 조공여부 = 1; return; }			
			if(조공패스[force_threat_id] > 0){ 조공패스[force_threat_id] -= 1; 조공여부 = 1; return; }  
			
			
			pk::force@ force_threat = pk::get_force(force_threat_id); // 요구세력
			
			float quantity0 = dislike / ( pk::max(세력부가속성[force0_id][속성_도시수], 2) );	
			
			// 거리에 따라 
			quantity0 = quantity0 / float(세력대세력거리[force0_id][force_threat_id] + 1);
			
			float multiplier_quantity = quantity0;
			
			
			
			// 조공 양 정하기
			int tribute_quantity_troops = abs(int(세력부가속성[force0_id][속성_병력] * multiplier_quantity));;
			int tribute_quantity_food = abs(int(세력부가속성[force0_id][속성_병량] * multiplier_quantity));;
			int tribute_quantity_gold = abs(int(세력부가속성[force0_id][속성_금]	* multiplier_quantity));;
						
			
			// 조공 이벤트 씬
			s_pat_force1_id = force_threat_id;
			s_pat_force0_id = force0_id;
			s_pat_tribute_troops = tribute_quantity_troops;
			s_pat_tribute_food = tribute_quantity_food;
			s_pat_tribute_gold = tribute_quantity_gold;
			
			pk::scene(pk::scene_t(Scene_AnnualTribute));	
			
			
			// 0: 동맹유지(조공헌상), 1: 설전, 2: 동맹파기, 3: 설전성공, 4: 설전패배
			int result_scene = s_pat_result;	
			
			if(result_scene == 0){		
			
				pk::add_relations(force0, force_threat_id, 50 );	
				
				// 조공 양만큼 플레이어 자원 소모. 도시에서 마이너스
				ModifySupplyForTribute(force0, force_threat, multiplier_quantity);
			}
			else if(result_scene == 2){
				// 파기
				pk::set_relations(force0, force_threat_id, 0);
				pk::unally(force0, force_threat_id);
				pk::add_relations(force0, force_threat_id, -100);
				
			}
			else if(result_scene == 3){
				조공패스[force_threat_id] += 2;
			}
			else if(result_scene == 4){
				ModifySupplyForTribute(force0, force_threat, multiplier_quantity);
			}
			
			// if(디버깅 > 0)pk::printf(pk::encode("---------------------------------------------------------------------------\n"));
			
			
			조공여부 = 1;
			
		}
		
		void ModifySupplyForTribute(pk::force@ force, pk::force@ force_threat, float multiplier_negative)
		{
			int gold = 0;
			int food = 0;
			int troops = 0;
			
			//log
			//pk::printf(pk::encode("ModifySupplyForTribute multiplier_negative=["+multiplier_negative+"]"));
			
			// 조공 헌상
			pk::list<pk::city@> city_list = pk::get_city_list(force);			
			
			for (int i = 0; i < city_list.count; i++)
			{				
				auto building = pk::city_to_building(city_list[i]);
				if (!pk::is_alive(building) or !pk::is_valid_force_id(building.get_force_id()))continue;
				
				int aGold, aFood, aTroops;
				
				pk::add_troops(building, aGold = int(pk::get_troops(building) * multiplier_negative), true);
				pk::add_food(building, aFood = int(pk::get_food(building) * multiplier_negative), true);
				pk::add_gold(building, aTroops = int(pk::get_gold(building) * multiplier_negative), true);
				
				gold += aGold;
				food += aFood;
				troops += aTroops;
				
				
				
				//pk::printf(pk::encode("present troops building=["+building.get_id()+"] get_troops=["+pk::get_troops(building)+"] add_troops=["+int(pk::get_troops(building) * multiplier_negative)+"]\n"));
				
			}
			
			
			// 조공 수혜
			pk::list<pk::city@> city_threat_list = pk::get_city_list(force_threat);			
			
			for (int j = 0; j < city_threat_list.count; j++)
			{				
				auto building = pk::city_to_building(city_threat_list[j]);
				if (!pk::is_alive(building) or !pk::is_valid_force_id(building.get_force_id()))continue;
				
				pk::add_troops(building, int(abs(troops) / city_threat_list.count), true);
				pk::add_food(building, int(abs(food) / city_threat_list.count), true);
				pk::add_gold(building, int(abs(gold) / city_threat_list.count), true);
				
				//pk::printf(pk::encode("benefit troops building=["+building.get_id()+"] get_troops=["+pk::get_troops(building)+"] add_troops=["+int(abs(troops) / city_threat_list.count)+"]\n"));
				
			}
			
			//pk::printf(pk::encode("-----------------------------------------------------------------------\n"));
		}
		
		
		
		int s_pat_force1_id = -1;
		int s_pat_force0_id = -1;
		int s_pat_tribute_troops = -1;
		int s_pat_tribute_food = -1;
		int s_pat_tribute_gold = -1;
		int s_pat_result = 0; // 0: 동맹유지, 1: 설전, 2: 동맹파기, 3: 설전성공, 4: 설전패배
		
		void Scene_AnnualTribute()
		{
			
			pk::fade(0);
			pk::sleep();
			pk::background(2);
			pk::fade(255);
			
			pk::force@ force1 = pk::get_force(s_pat_force1_id);
			pk::force@ force0 = pk::get_force(s_pat_force0_id);
			
			pk::person@ force0_kunshu = pk::get_person(force0.kunshu);
			pk::person@ force0_gunshi = pk::get_person(force0.gunshi);
			pk::person@ force0_teller = pk::is_alive(force0_gunshi) ? force0_gunshi : force0_kunshu;
									
			pk::person@ force1_kunshu = pk::get_person(force1.kunshu);
			pk::person@ force1_gunshi = pk::get_person(force1.gunshi);
			pk::person@ force1_emissary = pk::get_person(무장_사자);
			pk::person@ force1_teller = pk::is_alive(force1_gunshi) ? force1_gunshi : force1_emissary;

			string force0_kunshu_name = pk::decode(pk::get_name(force0_kunshu));			
			string force1_kunshu_name = pk::decode(pk::get_name(force1_kunshu));
			
			string force1_talk0 = "\x1b[1x"+force1_kunshu_name+"\x1b[0x님께서는, \n귀공이 세력을 돌볼 수 있도록 비호하여 그 곤란을 구제하셨다. 단지 사사로운 마음으로 은의를 잊고 호의를 저버린다면, 어찌 한 나라를 다스리는 군주라 할 수 있겠는가. ";
			pk::message_box(pk::encode(force1_talk0), force1_teller);
			
			
			pk::cutin(20);
			
			string force0_talk0 = "우리 \x1b[1x"+force0_kunshu_name+"\x1b[0x군은, \n일선에서 최우선으로 영토를 지켜왔소. 이제와 피 땀 흘려 지킨 것을 내놓으라 하니, 도적과 무엇이 다릅니까?";
			pk::message_box(pk::encode(force0_talk0), force0_teller);
			
			s_pat_result = pk::choose(
			pk::encode("조공 요구: \x1b[16x금 \x1b[18x"+s_pat_tribute_gold+" \x1b[16x병량 \x1b[18x"+s_pat_tribute_food+" \x1b[16x병력 \x1b[18x"+s_pat_tribute_troops), 
			{ pk::encode("조공 헌상"), pk::encode("설     전"), pk::encode("동맹 파기") }
			);
			
			if( s_pat_result == 0){
				string force1_talk1 = "\x1b[1x"+force1_kunshu_name+" "+force0_kunshu_name+" \x1b[0x동맹은 굳건하오.";
				pk::message_box(pk::encode(force1_talk1), force1_teller);
			}
			else if( s_pat_result == 2){
				string strFormated = "\x1b[1x{}\x1b[0x"+hanFix.return_chosa(force1_kunshu_name,3)+" \x1b[1x{}\x1b[0x"+hanFix.return_chosa(force0_kunshu_name,2)+" 동맹을 \x1b[16x파기\x1b[0x했습니다";				
				pk::message_box(pk::encode(pk::format(strFormated, force1_kunshu_name, force0_kunshu_name )), pk::get_person(무장_전령));
			}
			
			if(s_pat_result != 1){ pk::background(-1); return; }
			
			// 설전 시작 
			// 이기면 3, 지면 4
			s_pat_result = pk::debate(force0_teller, force1_teller, true, false).first + 3;
			
			if( s_pat_result == 3){
				string force0_talk1 = "한 동안 사신이 다시 올 일은 없을 것입니다.";
				pk::message_box(pk::encode(force0_talk1), force0_teller);
			}
			else if( s_pat_result == 4){
				string force1_talk1 = "다음에는 이정도로 끝나지 않을 것이다";
				pk::message_box(pk::encode(force1_talk1), force1_teller);
			}
			
			pk::background(-1);
			
		}
		
		
		
		void setJudgeWeight(pk::force@ force0)
		{
			
			int force0_id = force0.get_id();
			int force0_kunshu_id = force0.kunshu;
			if(판단가중치[force0_id][판단_군주] == force0_kunshu_id)return;
			
			pk::person@ person_kunshu = pk::get_person(force0_kunshu_id);
			
			// 0 은 사용 안함.
			판단가중치[force0_id][판단_군주] = force0_kunshu_id;
			판단가중치[force0_id][판단_판단주체] = 0.f;
			판단가중치[force0_id][판단_판단대상] = 0.f;
			판단가중치[force0_id][판단_인접여부] = 1.f * (지역집착_끝 - person_kunshu.local_affiliation - 1);
			판단가중치[force0_id][판단_도시수] = 1.f;
			판단가중치[force0_id][판단_무장수] = 1.f;
			판단가중치[force0_id][판단_병력] = 1.f;
			판단가중치[force0_id][판단_황제보호여부] = 1.f;
			판단가중치[force0_id][판단_우호도] = 1.f;
			판단가중치[force0_id][판단_궁합] = 2.f;
			판단가중치[force0_id][판단_탑10] = 1.f;
			판단가중치[force0_id][판단_적여부] = 1.f;
			판단가중치[force0_id][판단_인접허용적수] = 0.f;
			판단가중치[force0_id][판단_전쟁중여부] = 2.f;
			판단가중치[force0_id][판단_적의적] = 1.f * person_kunshu.ambition;
			판단가중치[force0_id][판단_동맹의적] = 1.f * person_kunshu.giri;
			판단가중치[force0_id][판단_친애여부] = 3.f;
			판단가중치[force0_id][판단_혐오여부] = 3.f;
			판단가중치[force0_id][판단_배신] = 0.f;
			판단가중치[force0_id][판단_인접적도시수합] = 1.f;
			판단가중치[force0_id][판단_인접적무장수합] = 1.f;
			판단가중치[force0_id][판단_인접적병력합] = 1.f;
			판단가중치[force0_id][판단_군사능력] = 0.f;
			판단가중치[force0_id][판단_결과] = 0.f;
			판단가중치[force0_id][판단_끝] = 0.f;
			
			
			판단호불호[force0_id][판단_군주] = true;
			판단호불호[force0_id][판단_판단주체] = true;
			판단호불호[force0_id][판단_판단대상] = true;
			판단호불호[force0_id][판단_인접여부] = false;
			// 판단호불호[force0_id][판단_도시수] = true;
			// 판단호불호[force0_id][판단_무장수] = true;
			// 판단호불호[force0_id][판단_병력] = true;
			판단호불호[force0_id][판단_황제보호여부] = true;
			판단호불호[force0_id][판단_우호도] = true;
			판단호불호[force0_id][판단_궁합] = false;
			// 판단호불호[force0_id][판단_탑10] = true;
			판단호불호[force0_id][판단_적여부] = false;
			판단호불호[force0_id][판단_인접허용적수] = true;
			판단호불호[force0_id][판단_전쟁중여부] = false;
			판단호불호[force0_id][판단_적의적] = true;
			판단호불호[force0_id][판단_동맹의적] = false;
			판단호불호[force0_id][판단_친애여부] = true;
			판단호불호[force0_id][판단_혐오여부] = false;
			판단호불호[force0_id][판단_배신] = false;
			// 판단호불호[force0_id][판단_인접적도시수합] = true;
			// 판단호불호[force0_id][판단_인접적무장수합] = true;
			// 판단호불호[force0_id][판단_인접적병력합] = true;
			판단호불호[force0_id][판단_군사능력] = true;
			판단호불호[force0_id][판단_결과] = false;
			판단호불호[force0_id][판단_끝] = false;
			
			
		}
		
		
		// 우호도 증감
		void AddRelationValue()
		{
			
			pk::list<pk::force@> force_list = pk::get_force_list(false);
			
			for (int i = 0; i < force_list.count; i++){
				if(isIminzoku(force_list[i]))continue;	
				int force0_id = force_list[i].get_id();
				for (int j = i+1; j < force_list.count; j++){
					if(isIminzoku(force_list[j]))continue;				
					int force2_id = force_list[j].get_id();
					if(force0_id == force2_id)continue;
					// line_bigO++;
					
					float force0_wantAlly = 세력대판단결과[force0_id][force2_id];
					float force2_wantAlly = 세력대판단결과[force2_id][force0_id];
					
					float wantSum = force0_wantAlly + force2_wantAlly;
					int add = wantSum * 우호도증감기준;
					add = int( add / float(세력대세력거리[force0_id][force2_id]) );
					
					// util.prnt("AddRelation kunshu0=["+pk::get_force(force0_id).kunshu+"] kunshu2=["+pk::get_force(force2_id).kunshu+"] wantSum=["+wantSum+"] how_far=["+세력대세력거리[force0_id][force2_id]+"] add_relation=["+add+"] ");
					
					// 우호도 증감							
					pk::add_relations(force0_id, force2_id, add);
					
					
					if(force_list[i].is_player() and force_list[j].is_player())continue; // 플레이어 끼리는 자동동맹 혹은 파기 하지 않는다.
					
					allyUnally(force_list[i], force_list[j], wantSum, force0_wantAlly, force2_wantAlly);
					
					
				}
			}
			// util.prnt("---------------------------------------------------------------------------------");
			
		}
		
		
		
		/*
		/// 주위 적 도시 병력 평균 비교
		int getAverageEnemyCityTroopsAround(pk::force@ force0, pk::building@ building0){
			
			int sumTroops = 0;
			int count = 0;
			pk::city@ city0 = pk::building_to_city(building0);
			array<int> neighbor_cities = neighborMap.인접도시[city0.get_id()];
			for (int i = 0; i < neighbor_cities.length; i++){
				pk::city@ neighbor_city = pk::get_city(neighbor_cities[i]);	
				int force_id = neighbor_city.get_force_id();
				if(!pk::is_alive(neighbor_city) or !pk::is_valid_force_id(force_id))continue;
				// 적인가?
				if(!pk::is_enemy(force0, pk::get_force(force_id)))continue;
				sumTroops += pk::get_troops(neighbor_city);
				count++;
			}
			return int( sumTroops / float(pk::max(count, 1.0)) );
		}
		*/
		/// 두 세력이 현재 진행중인 연합군 일원인가?
		bool isBeingAllianceForces(int force0_id, int force2_id){
			if(진행중인연합세력.length == 0)return false;
			for (int i = 0; i < 진행중인연합세력.length; i++){		
				bool isforce0 = false;
				bool isforce2 = false;
				for (int j = 0; j < 진행중인연합세력[i].length; j++){
					if(진행중인연합세력[i][j] == force0_id)isforce0 = true;
					if(진행중인연합세력[i][j] == force2_id)isforce2 = true;					
					if(isforce0 and isforce2)return true;
				}
			}
			return false;
		}
		
		/// 출진한 부대들이 없는가?
		bool isUnitsAround(pk::force@ force0, pk::city@ city2)
		{
			string key = force0.get_id()+"|"+city2.get_force_id()+"|"+city2.get_id(); // 공격세력|목표세력|목표도시
			
			
			array<pk::point> arr = pk::range(city2.get_pos(), 1, 8);
			for (int j = 0; j < arr.length; j++)
			{
				pk::unit@ dst = pk::get_unit(arr[j]);					
				if (dst is null)continue;

				부대출진후_경과.set(key, 2);
				// util.prnt("days set key=["+key+"] val=["+int(부대출진후_경과[key])+"]");
				return true;
				
			}
			
			if(부대출진후_경과.exists(key) and int(부대출진후_경과[key]) > 0){
				// util.prnt("days chk key=["+key+"] val=["+int(부대출진후_경과[key])+"]");
				return true;
			}
			else
				return false;
			
		}
		
		void BetrayalAttack(pk::force@ force0){
			
			if(force0.is_player())return; // 플레이어 패스
			if(전쟁중여부[force0.get_id()] == 1)return; // 아군 도시가 전쟁중이면		
			
			
			// 군주 야망 체크
			pk::person@ kunshu0 = pk::get_person(force0.kunshu);
			if(kunshu0.ambition == 야망_매우낮음)return;			
			
			pk::list<pk::city@> force0_city_list = pk::get_city_list(force0);		
				
			array<pk::int_int> targetcity_prob; // 타겟후보도시들_타겟가능성
			
			// 목표도시 탐색
			// 아군 도시들과 인접한 도시 탐색
			for (int i = 0; i < force0_city_list.count; i++)
			{				
				auto force0_city = force0_city_list[i]; // 출발도시
				if (!pk::is_alive(force0_city) or !pk::is_valid_force_id(force0_city.get_force_id()))continue;
				
				array<int> neighbor_city2s = neighborMap.인접도시[force0_city.get_id()];
				for (int j = 0; j < neighbor_city2s.length; j++){
					pk::city@ city2 = pk::get_city(neighbor_city2s[j]); // 타겟후보도시
					if(!pk::is_alive(city2) or !pk::is_valid_force_id(city2.get_force_id()))continue;
					
					// 아군도시 제외
					if(city2.get_force_id() == force0.get_id())continue;
					
					// 연합군세력인가?
					if(isBeingAllianceForces(force0.get_id(), city2.get_force_id())){
						// util.prnt("isBeingAllianceForces force0_kunshu=["+force0.kunshu+"] force2_kunshu=["+pk::get_force(city2.get_force_id()).kunshu+"]");
						continue;
					}
					
					// 주위에 출진한 부대들이 없는가?
					if(isUnitsAround(force0, city2))continue;
					
					// 중복 공격 방지
					string key = force0.get_id()+"|"+city2.get_id(); // 세력|타겟도시
					// util.prnt("delay chk key=["+key+"] val=["+int(배신거점착발지연[key])+"]");
					if(배신거점착발지연.exists(key) and int(배신거점착발지연[key]) > 0)continue;
					
					float prob_타겟 = isBetrayForCities(force0_city.get_id(), city2.get_id(), kunshu0);					
					if(prob_타겟 <= 1.0)continue;
					targetcity_prob.insertLast(pk::int_int(city2.get_id(), int(prob_타겟 * 100) ));
					
				}
			}
			
			if(targetcity_prob.length == 0)return;
			// 도시 병력차가 가장 많이 나는 곳 
			targetcity_prob.sort(function(a,b) { 				
				return a.second > b.second; 
			});
			pk::city@ target_city = pk::get_city(targetcity_prob[0].first); // 목표도시

			
			pk::force@ force2 = pk::get_force(target_city.get_force_id());
			pk::person@ kunshu2 = pk::get_person(force2.kunshu);			
			// util.prnt("target_city=["+target_city.get_id()+"] target_troops=["+pk::get_troops(target_city)+"] target_force_kunshu=["+force2.kunshu+"] key=["+(force0.get_id()+"|"+target_city.get_force_id()+"|"+target_city.get_id())+"] ");			
			
			// 친애여부			
			if(pk::is_like(kunshu0, kunshu2.get_id()))return;
			
			// 우호도
			// if(force0.relations[force2.get_id()] >= 배신우호도기준)return;
			if(!pk::rand_bool(100 - force0.relations[force2.get_id()]))return;
						
			
			// 타겟 인접 아군 도시 탐색
			pk::list<pk::city@> city1_list; // 출진할 도시들
			array<int> neighbor_city1s = neighborMap.인접도시[target_city.get_id()];
			for (int k = 0; k < neighbor_city1s.length; k++){
				pk::city@ city1 = pk::get_city(neighbor_city1s[k]);	
				if(!pk::is_alive(city1))continue;				
				// 아군도시인가?
				if(city1.get_force_id() != force0.get_id())continue;
												
				// 거리 제한
				int 순_distance = ceil(pk::get_distance(city1.get_pos(), target_city.get_pos()) / 기준_칸이동력);
				if(순_distance > 6)continue;
				
				// 성 내구도가 낮은가?
				if(pk::get_hp(city1) <= pk::get_max_hp(city1) / 2.0)continue;
				
				if(도시경계여부[city1.get_id()] == 1)continue;
								
				// 주위에 위협적인 적이 있는가?
				if(isAroundEnemyThreat(city1))continue;
				
				pk::building@ depart_building = pk::city_to_building(city1);
				// 부대 출진 횟수 set						
				auto person_list = pk::get_idle_person_list(depart_building);
				if (person_list.count == 0)continue; // 출진할 부대가 없다
				auto total_person_list = pk::get_person_list(depart_building, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반));
				// 명령 가능한 무장이 있는지 확인.
				if (total_person_list.count - person_list.count >= 2)continue;
				
				city1_list.add(city1);				
			}
			if(city1_list.count == 0)return;
			
			// 동맹파기
			string force0_kunshu_name = pk::decode(pk::get_name(pk::get_person(force0.kunshu)));
			string force2_kunshu_name = pk::decode(pk::get_name(pk::get_person(force2.kunshu)));
			
			if(!pk::is_enemy(force0, force2)){
				
				pk::unally(force0, force2.get_id());
				pk::add_relations(force0, force2.get_id(), -100);
				pk::message_box(pk::encode("\x1b[1x"+force0_kunshu_name+"\x1b[0x"+hanFix.return_chosa(force0_kunshu_name,3)+" \x1b[1x"+force2_kunshu_name+"\x1b[0x"+hanFix.return_chosa(force2_kunshu_name,2)+" 동맹을 \x1b[16x파기\x1b[0x했습니다"), pk::get_person(무장_전령));	
			}
			else
				pk::add_relations(force0.get_id(), force2.get_id(), -50);
			
			
			// 출진메세지			
			string city2_name = pk::decode(pk::get_name(target_city));
			messageBetrayalAttack(kunshu0, force2_kunshu_name, city2_name);
			
			
			//출진
			pk::building@ target_building = pk::city_to_building(target_city);
			// int 한부대기준병력수 = 5000;
			for (int l = 0; l < city1_list.count; l++){
				pk::building@ depart_building = pk::city_to_building(city1_list[l]);
				// 부대 출진 횟수 set						
				auto person_list = pk::get_idle_person_list(depart_building);
				// 명령 가능한 무장이 있는지 확인.
				if (person_list.count == 0)continue; // 출진할 부대가 없다
								
				// 통솔+무력이 높은 순으로 정렬.
				person_list.sort(function(a, b)
				{
					return a.stat[무장능력_통솔] + a.stat[무장능력_무력] > b.stat[무장능력_통솔] + b.stat[무장능력_무력];
				});
				
				// 출진부대수 결정							
				// int numUnit = pk::min(getBetrayalAttackUnitNumber(한부대기준병력수, target_building), person_list.count);
				// util.prnt("numUnit=["+numUnit+"] target_troops=["+pk::get_troops(target_building)+"] person_list=["+person_list.count+"]");
				
				bool isWarAt = intToBoolean(건물전쟁여부[depart_building.get_id()]); 
				for (int o = 0; o < person_list.count; o++){
					CreateAUnit(person_list[o], depart_building, target_building, 1.0, isWarAt, o, false, {});
				}				
			}
			
			
			string key = force0.get_id()+"|"+target_city.get_id();
			배신거점착발지연.set(key, 배신공격_지연);			
			// util.prnt("delay set key=["+key+"] val=["+int(배신거점착발지연[key])+"]");
			
			
		}
		
		void messageBetrayalAttack(pk::person@ kunshu, string kunshu_name, string city_name){
			
			switch (kunshu.character)
			{
			case 성격_소심:				
				pk::message_box(pk::encode("\x1b[1x"+kunshu_name+"\x1b[0x의 도시 \x1b[16x"+city_name+"\x1b[0x"+hanFix.return_chosa(city_name,1)+" 취하는 것 외에는 방법이없다 출진하세요."), kunshu);
				break;
			case 성격_냉정: 
				pk::message_box(pk::encode("적은 \x1b[1x"+kunshu_name+"\x1b[0x의 도시 \x1b[16x"+city_name+"\x1b[0x에 있다"), kunshu);	
				break;
			case 성격_대담: 
				pk::message_box(pk::encode("\x1b[1x"+kunshu_name+"\x1b[0x의 도시 \x1b[16x"+city_name+"\x1b[0x"+hanFix.return_chosa(city_name,1)+" 친다!"), kunshu);
				break;
			case 성격_저돌: 
				pk::message_box(pk::encode("\x1b[1x"+kunshu_name+"\x1b[0x의 도시 \x1b[16x"+city_name+"\x1b[0x"+hanFix.return_chosa(city_name,1)+" 불바다로 만들어 버려라 전진!"), kunshu);
				break;
			}
			
		}
		
		int getBetrayalAttackUnitNumber(int 한부대기준병력수, pk::building@ building2)
		{			
			int troops2 = pk::get_troops(building2);
			int 증가병력 = 10000;
			return ceil((troops2 + 증가병력) / float(한부대기준병력수));			
		}
		/*
		int getBetrayalAttackUnitNumber(pk::person@ kunshu0, int 한부대기준병력수, pk::building@ building2)
		{
			
			int troops2 = pk::get_troops(building2);
			
			switch (kunshu0.character)
			{
			case 성격_소심: 
				return 1;
			case 성격_냉정: 
				return ceil((troops2 * 2.0) / float(한부대기준병력수));
			case 성격_대담: 
				return ceil((troops2 * 2.0) / float(한부대기준병력수 * 1.5));
			case 성격_저돌: 
				return ceil((troops2 * 2.0) / float(한부대기준병력수 * 2));
			}
			
			return 1;
			
		}
		*/
		
		float isBetrayForCities(int city0_id, int city2_id, pk::person@ kunshu0)
		{
			
			int city0_troops = pk::max(pk::get_troops(pk::get_city(city0_id)),1);
			int city2_troops = pk::max(pk::get_troops(pk::get_city(city2_id)),1);
						
			
			float result = (float(city0_troops) / float(city2_troops)) / float(야망_끝 - kunshu0.ambition + 2);
			
			//pk::printf(pk::encode("isBetrayForCities result=["+result+"] \n"));
					
			
			// return result >= 1.0 ? true : false;
			
			return result;
		}
		
		bool areWeAtWar(int force0_id)
		{
			for (int i = 0; i < 세력_끝; i++){	
				if(세력대전쟁여부[force0_id][i] == 1)return true;
			}
			
			return false;
		}
		
		// 동맹 체결
		void allyUnally(pk::force@ force0, pk::force@ force2, float wantSum, float force0_wantAlly, float force2_wantAlly)
		{
			int force0_id = force0.get_id();
			int force2_id = force2.get_id();
			int relations = force0.relations[force2_id];
						
			// 플레이어가 자동으로 동맹요청하지 않는다.
			bool force0_want_more = force0_wantAlly > force2_wantAlly;
			bool will_동맹 = (relations >= 100 and pk::is_enemy(force0, force2));
			bool will_파기 = (relations <= 0 and !pk::is_enemy(force0, force2));
			if(will_파기)force0_want_more = !force0_want_more;
			pk::force@ force_reqs = force0_want_more ? force0 : force2;
			pk::force@ force_recv = force0_want_more ? force2 : force0;					
			if(force0.is_player()){@force_recv=force0;@force_reqs=force2;}
			if(force2.is_player()){@force_recv=force2;@force_reqs=force0;}
			
			// util.prnt("force_reqs=["+force_reqs.kunshu+"] force_recv=["+force_recv.kunshu+"] force0_want_more=["+force0_want_more+"]");
			
			if(will_동맹 or will_파기)cmd_AllyUnAlly(force_reqs, force_recv, wantSum, (will_동맹 ? true : false) );
			
		}
		
		
		void cmd_AllyUnAlly(pk::force@ force0, pk::force@ force2, float wantSum, bool willAlly)
		{
			if(사신보내기[force0.get_id()] >= 0)return;
			
			// 사신 정하기
			pk::list<pk::city@> cityList = pk::get_city_list(force0);
			pk::building@ building0 = pk::city_to_building(cityList[0]);
			auto person_list = pk::get_idle_person_list(building0);
			if (person_list.count == 0)return;
			pk::person@ sasin = pk::get_person(person_list[0].get_id());
			
			int force0_id = force0.get_id();	
			int force2_id = force2.get_id();	
			
			if(willAlly){
				
				pk::alliance_cmd_info info;
							
				@info.actor = sasin;
				
				// 액수 정하기		
				// 요청세력이 강할 수록 많게 마이너스, 약할 수록 적게 플러스
				int diff = 세력부가속성[force0_id][속성_병력] - 세력부가속성[force2_id][속성_병력];
				float rate = float(세력부가속성[force0_id][속성_병력]) / float(pk::max((세력부가속성[force0_id][속성_병력] + 세력부가속성[force2_id][속성_병력]), 1));				
				int gold_force2_per_city = int(float(세력부가속성[force2_id][속성_금]) / float(pk::max(세력부가속성[force2_id][속성_도시수], 2)) );
				int gold_force0_per_city = int(float(세력부가속성[force0_id][속성_금]) / float(세력부가속성[force0_id][속성_도시수]));	
				
				// 요청세력이 더 강하면 -
				int gold0 = diff > 0 ? -int(rate * gold_force2_per_city) : int(rate * gold_force0_per_city);
				
				// 거리에 따라 
				gold0 = int( gold0 / float(세력대세력거리[force0_id][force2_id] + 1) );
			
				info.gold = gold0;
				
				// pk::printf(pk::encode("ALLY force0=["+force0.kunshu+"] force2=["+force2.kunshu+"] diff=["+diff+"] rate=["+rate+"] gold_force2_per_city=["+gold_force2_per_city+"] gold_force0_per_city=["+gold_force0_per_city+"] info.gold=["+info.gold+"] \n"));
				// util.prnt("ALLY force0=["+force0.kunshu+"] force2=["+force2.kunshu+"] info.gold=["+info.gold+"]");
				
				@info.target = force2;
				
				pk::command(info);				
				
			}
			else{
				
				pk::annul_alliance_cmd_info info; // 파기
							
				@info.actor = person_list[0];
				@info.target = force2;
				// util.prnt("UNALLY force0=["+force0.kunshu+"] force2=["+force2.kunshu+"]");
				pk::command(info);
				
			}
			사신보내기[force0_id] = 사신보내기_일수;
		}
		
		
		
		void set_세력대판단(){
			
			
			pk::list<pk::force@> force_list = pk::get_force_list(false);
			
			
			for (int i = 0; i < force_list.count; i++){
				if(isIminzoku(force_list[i]))continue;				
				set_세력대판단_force(force_list[i]);
			}
			
		}
		
		
		// 세력 대 전세력		
		void set_세력대판단_force(pk::force@ force0)
		{
			int force0_id = force0.get_id();			
			pk::list<pk::force@> force_list = pk::get_force_list(false);						
					
			
			// 인접 적 찾기 변수			
			세력부가속성[force0_id][속성_인접적수] = 0;
						
			
			for (int i = 0; i < force_list.count; i++){				
				if(isIminzoku(force_list[i]))continue;
				int force1_id = force_list[i].get_id();
				if(세력외교대상[force0_id][force1_id] != 1)continue;				
				
								
				// 자기자신 제외
				if(force1_id == force0_id)continue;			
				
				// 인접 적 찾기				
				if(pk::is_neighbor_force(force0, force_list[i]) and pk::is_enemy(force0, force_list[i])){
					세력부가속성[force0_id][속성_인접적수] += 1;
					인접적합모두[force0_id][인접적합_도시수] += 세력부가속성[force1_id][속성_도시수];
					인접적합모두[force0_id][인접적합_무장수] += 세력부가속성[force1_id][속성_무장수];
					인접적합모두[force0_id][인접적합_병력] += 세력부가속성[force1_id][속성_병력];
				}
								
				// 세력 판단 세팅
				세력대판단[index_세력대판단] = make_판단(force0, force_list[i]);
				
				// 전쟁 중인 적의 적 찾기 and 동맹의 전쟁중인 적 찾기
				set_적의적_동맹의적(force0_id, force1_id, 세력대판단[index_세력대판단]);
				
				
				index_세력대판단++;
				
			}
			
			
		}
		
		
		// 세력 판단
		array<float> make_판단(pk::force@ force0, pk::force@ force2)
		{
			int force0_id = force0.get_id();
			int force2_id = force2.get_id();
			array<int> force0_부가속성 = 세력부가속성[force0_id];
			array<int> force2_부가속성 = 세력부가속성[force2_id];
			
			판단[판단_판단주체] = force0_id;
			
			판단[판단_판단대상] = force2_id;
			
			판단[판단_인접여부] = BooleanToFloat(pk::is_neighbor_force(force0, force2));			
			
			판단[판단_도시수] = get_판단_도시무장병력(force0_id, force2_id, force0_부가속성[속성_도시수], force2_부가속성[속성_도시수]);	
			
			판단[판단_무장수] = get_판단_도시무장병력(force0_id, force2_id, force0_부가속성[속성_무장수], force2_부가속성[속성_무장수]);	
			
			판단[판단_병력] = get_판단_도시무장병력(force0_id, force2_id, force0_부가속성[속성_병력], force2_부가속성[속성_병력]);	
			
			판단[판단_황제보호여부] = isProtectHan(force0, force2, pk::is_protecting_the_emperor(force2));
					
			판단[판단_우호도] = force0.relations[force2_id];			
			
			판단[판단_궁합] = pk::get_aishou_distance(pk::get_person(force0.kunshu), (pk::get_person(force2.kunshu)).get_id());
				
			판단[판단_탑10] = get_판단_도시무장병력(force0_id, force2_id, force0_부가속성[속성_탑10], force2_부가속성[속성_탑10]);	
			
			판단[판단_적여부] = BooleanToFloat(pk::is_enemy(force0, force2));
			
			판단[판단_전쟁중여부] = BooleanToFloat(세력대전쟁여부[force0_id][force2_id] == 1 ? true : false);
			
			//판단[판단_적의적] = BooleanToFloat(세력적의적[force0_id][force2_id] == 1 ? true : false);
			
			판단[판단_친애여부] = BooleanToFloat(pk::is_like(pk::get_person(force0.kunshu), force2.kunshu));
			
			판단[판단_혐오여부] = BooleanToFloat(pk::is_dislike(pk::get_person(force0.kunshu), force2.kunshu));
				
			
			
			return 판단;
			
		}
		
		float get_판단_도시무장병력(int force0_id, int force2_id, int 수_force0, int 수_force2){
			bool 호불호 = (수_force2 > 수_force0);
			float 합_병력 = float(pk::max(수_force0+수_force2, 1));
			// util.prnt("kunshu0=["+pk::get_force(force0_id).kunshu+"] kunshu2=["+pk::get_force(force2_id).kunshu+"] num_force0=["+수_force0+"] num_force2=["+수_force2+"]");
			return 호불호 ? 수_force2 / 합_병력 : -(수_force0 / 합_병력);
		}
		
		
		float isProtectHan(pk::force@ force0, pk::force@ force1, bool isProtectingTheEmperor)
		{
			
			pk::person@ kunshu1 = pk::get_person(force1.kunshu);
			pk::person@ kunshu0 = pk::get_person(force0.kunshu);
			
			float result = 0;
			
			/*
			const int 한실_무시 = 0;
			const int 한실_보통 = 1;
			const int 한실_중시 = 2;
			*/
			
			int8 kanshitsu0 = kunshu0.kanshitsu -1;
			int8 kanshitsu1 = kunshu1.kanshitsu -1;
			
			if(kanshitsu0 == 1 and kanshitsu1 == 1 )result = 1;
			else if(kanshitsu0 * kanshitsu1 == -1)result = -1;			
			else result = 0;
			
			//보너스
			if(kanshitsu0 == 1 and isProtectingTheEmperor)result += 1;
			
			
			return result;
		}
		
		void set_적의적_동맹의적(int force0_id, int force1_id, array<float> a_세력대판단 )
		{
			bool isEnemyOfEnemy = false;
			bool isAllianceOfEnemy = false;
			if(세력대전쟁여부[force0_id][force1_id] == 1)isEnemyOfEnemy = true;
			if(isAlly(a_세력대판단[판단_우호도], a_세력대판단[판단_적여부] ))isAllianceOfEnemy = true;
						
			for (int i = 0; i < 세력_끝; i++){	
				// line_bigO++;
				if(pk::is_enemy(force1_id, i) and isEnemyOfEnemy){
					세력적의적[force0_id][i] = 1;
				}
				if((세력대전쟁여부[force1_id][i] == 1 ? true : false) and isAllianceOfEnemy){
					세력동맹의적[force0_id][i] = 1;
				}
			}			
			
		}
		
		bool isAlly(float relations, float isEnemy)
		{
			return relations >= 50.f and isEnemy == 0.f ? true : false;
		}
		
		
		
		void set_세력대판단_weight()
		{
			
			for (int i = 0; i < index_세력대판단; i++){						
				
				int force0_id = int(세력대판단[i][판단_판단주체]);
				int force1_id = int(세력대판단[i][판단_판단대상]);
				
				if (!pk::is_alive(pk::get_force(force0_id)) or !pk::is_valid_force_id(force0_id))continue;	
				if (!pk::is_alive(pk::get_force(force1_id)) or !pk::is_valid_force_id(force1_id))continue;	
				
				if(force0_id == -1)continue;		
				
				
				setJudgeWeight(pk::get_force(force0_id));
				
				float dec_wantally = getWantSum(세력대판단[i], 판단호불호[force0_id], 판단가중치[force0_id]);								
					
				세력대판단[i][판단_결과] = dec_wantally;			
				세력대판단결과[force0_id][force1_id] = dec_wantally;
			
			}
				
		}
				
		
		float getWantSum(array<float> a_세력대판단, array<bool> a_판단호불호, array<float> a_판단가중치)
		{
			
			float n = 0.f;
			int8 cnt_나누기 = 0;
			int8 idx_판단 = 0;
			
			int force0_id = int(a_세력대판단[판단_판단주체]);
			int force2_id = int(a_세력대판단[판단_판단대상]);
			pk::person@ kunshu0 = pk::get_person(pk::get_force(force0_id).kunshu);
			pk::person@ kunshu2 = pk::get_person(pk::get_force(force2_id).kunshu);
			
			array<float> 판단값(20, -1.f);
			
			// util.prnt("***********************************************************************************************");
			// util.prnt("---------------------------------- kunshu0=["+kunshu0.get_id()+"] kunshu2=["+kunshu2.get_id()+"] ");
			
			float v = getVal_호불_1(a_세력대판단[판단_인접여부], a_판단호불호[판단_인접여부]) * a_판단가중치[판단_인접여부];	
			// util.prnt("is_Neighbor=["+v+"]  ");
			판단값[idx_판단++] = v; n += v;	
			cnt_나누기++;
			
			v = a_세력대판단[판단_도시수] * a_판단가중치[판단_도시수];
			// util.prnt("City2By=["+v+"]");
			판단값[idx_판단++] = v; n += v;	
			cnt_나누기++;
			
			v = a_세력대판단[판단_무장수] * a_판단가중치[판단_무장수];
			// util.prnt("Mujang2By=["+v+"]");
			판단값[idx_판단++] = v; n += v;	
			cnt_나누기++;
						
			v = a_세력대판단[판단_병력] * a_판단가중치[판단_병력];		
			// util.prnt("Troops2By=["+v+"]");			
			판단값[idx_판단++] = v; n += v;	
			cnt_나누기++;
						
			v = getVal_호불_0(a_세력대판단[판단_황제보호여부], a_판단호불호[판단_황제보호여부]) * a_판단가중치[판단_황제보호여부];		
			// util.prnt("is_protect_Han=["+v+"] ");			
			판단값[idx_판단++] = v; n += v;	
			if(v != 0)cnt_나누기++;
						
			v = (a_세력대판단[판단_우호도] / 100.f) * a_판단가중치[판단_우호도];	
			// util.prnt("Relation=["+v+"] ");			
			판단값[idx_판단++] = v; n += v;	
			cnt_나누기++;
					
			v = (-(a_세력대판단[판단_궁합]) / 100.f) * a_판단가중치[판단_궁합];		
			// util.prnt("GungHab=["+v+"] ");
			판단값[idx_판단++] = v; n += v;	
			cnt_나누기++;
			
			v = a_세력대판단[판단_탑10] * a_판단가중치[판단_탑10];
			// util.prnt("Top10By=["+v+"]");
			판단값[idx_판단++] = v; n += v;	
			cnt_나누기++;
			
			v = getVal_호불_0(a_세력대판단[판단_적여부], a_판단호불호[판단_적여부]) * a_판단가중치[판단_적여부];
			// util.prnt("is_enemy=["+v+"] ");
			판단값[idx_판단++] = v; n += v;	
			if(v != 0)cnt_나누기++;
			
			v = getVal_호불_0(a_세력대판단[판단_전쟁중여부], a_판단호불호[판단_전쟁중여부]) * a_판단가중치[판단_전쟁중여부];
			// util.prnt("is_atWar=["+v+"] ");
			판단값[idx_판단++] = v; n += v;	
			if(v != 0)cnt_나누기++;
						
			v = getVal_호불_0(a_세력대판단[판단_적의적] = BooleanToFloat(세력적의적[force0_id][force2_id] == 1 ? true : false), a_판단호불호[판단_적의적]) * a_판단가중치[판단_적의적];
			// util.prnt("is_EnemyOfEnemy=["+v+"] ");
			판단값[idx_판단++] = v; n += v;	
			if(v != 0)cnt_나누기++;
			
			v = getVal_호불_0(a_세력대판단[판단_동맹의적] = BooleanToFloat(세력동맹의적[force0_id][force2_id] == 1 ? true : false), a_판단호불호[판단_동맹의적]) * a_판단가중치[판단_동맹의적];
			// util.prnt("is_EnemyOfAlly=["+v+"] ");
			판단값[idx_판단++] = v; n += v;	
			if(v != 0)cnt_나누기++;
			
			v = getVal_호불_0(a_세력대판단[판단_친애여부], a_판단호불호[판단_친애여부]) * a_판단가중치[판단_친애여부];
			// util.prnt("is_Like=["+v+"] ");
			판단값[idx_판단++] = v; n += v;	
			if(v != 0)cnt_나누기++;
			
			v = getVal_호불_0(a_세력대판단[판단_혐오여부], a_판단호불호[판단_혐오여부]) * a_판단가중치[판단_혐오여부];
			// util.prnt("is_Dislike=["+v+"] ");
			판단값[idx_판단++] = v; n += v;	
			if(v != 0)cnt_나누기++;
			
			// 인접 적 세력합과 자신을 비교해 동맹 친화 정도 결정				
			v = (a_세력대판단[판단_인접적도시수합] = getVal_호불_성격( 세력부가속성[force0_id][속성_도시수], 인접적합모두[force0_id][인접적합_도시수], kunshu0.character )) * a_판단가중치[판단_인접적도시수합];	
			// util.prnt("sum_nearEnemyCity=["+v+"] ");
			판단값[idx_판단++] = v; n += v;			
			cnt_나누기++;
			
			v = (a_세력대판단[판단_인접적무장수합] = getVal_호불_성격( 세력부가속성[force0_id][속성_무장수], 인접적합모두[force0_id][인접적합_무장수], kunshu0.character )) * a_판단가중치[판단_인접적무장수합];
			// util.prnt("sum_nearEnemyMujang=["+v+"] ");
			판단값[idx_판단++] = v; n += v;			
			cnt_나누기++;
			
			v = (a_세력대판단[판단_인접적병력합] = getVal_호불_성격( 세력부가속성[force0_id][속성_병력], 인접적합모두[force0_id][인접적합_병력], kunshu0.character )) * a_판단가중치[판단_인접적병력합];
			// util.prnt("sum_nearEnemyTroops=["+v+"] ");
			판단값[idx_판단++] = v; n += v;			
			cnt_나누기++;
			
			
			
			n /= (cnt_나누기);
			
			
			// util.prnt("---------------------------------- want_ally=["+n+"] ");
			// // util.prnt("kunshu0=["+kunshu0.get_id()+"] kunshu2=["+kunshu2.get_id()+"] want_ally=["+n+"]");
			
			
			return n;
			
		}
		
		
		// 군사의 버프
		float getGunshiHelp(pk::person@ personGunshi ,float n)
		{
			if(!pk::is_alive(personGunshi))return 0;
			
			float add = (personGunshi.stat[무장능력_통솔]
				 + personGunshi.stat[무장능력_무력]
				 + personGunshi.stat[무장능력_지력]
				 + personGunshi.stat[무장능력_정치]
				 + personGunshi.stat[무장능력_매력]
			) / (무장능력_끝 * 100.f);
			
			return n > 0 ? add : -add;
		}
		
		float getVal_호불_0(float val, bool isLike)
		{
			if(val > 0){
				return isLike ? 1 : -1;
			}
			else if(val == 0){
				return 0;
			}
			else{
				return isLike ? -1 : 1;
			}					
		}
		float getVal_호불_1(float val, bool isLike)
		{
			if(val > 0){
				return isLike ? 1 : -1;
			}
			else{
				return isLike ? -1 : 1;
			}					
		}
		float getVal_호불_성격(float me, float youSum, int character)
		{
			float me_성격곱 = me * (character + 1);
			float by = me_성격곱 + youSum;
			if(by == 0)return 0;
			float val = youSum / by;
			return val;
									
		}
		
		
		
		
		
		void set_rank_인접적수(){
			
			
			pk::list<pk::force@> force_list = pk::get_force_list(false);
			
			
			for (int i = 0; i < force_list.count; i++){
				if(isIminzoku(force_list[i]))continue;				
				int force_id = force_list[i].get_id();
				
				// 인접적세력수 순위 매기기
				set_a_rank_인접적수(force_id);
				
			}
			
			//if(rank_인접적수[k] == -1)break;
			//pk::printf(pk::encode(pk::format("{} = {}\n", 세력부가속성[rank_인접적수[k]][속성_인접적수], rank_인접적수[k] )));
			
		}
		
		
		void set_a_rank_인접적수(int force_id)
		{
							
			// 세력 순위 정하기
			for (int j = 0; j < 47; j++){
				int 적세력수 = rank_인접적수[j] == -1 ? 0 : 세력부가속성[rank_인접적수[j]][속성_인접적수];
				
				if( 적세력수 < 세력부가속성[force_id][속성_인접적수]){	
				
					int8 tmpForceId = -1;
					int8 tmp2ForceId = -1;
					
					for (int l = j; l < 47; l++){	
						// line_bigO++;
						if(l > j){
							if(tmpForceId == -1)break;
							tmp2ForceId = rank_인접적수[l];
							rank_인접적수[l] = tmpForceId;
							tmpForceId = tmp2ForceId;
						}	
						else {
							tmpForceId = rank_인접적수[l];
							rank_인접적수[j] = force_id;								
						}							
					}						
					break;
				}									
			} // end - for			
			
		} // end - function
		
		
		
		
		
		
		
		// 연합결성 커맨드
		
		void initMenu(pk::building@ building)
		{
			menu_city_id_ = -1;
			pk::city@ city = pk::building_to_city(building);
			if (city !is null)
				menu_city_id_ = city.get_id();
			menu_force_id_ = building.get_force_id();
		}
		
		
		bool isEnabled()
		{
			pk::force@ force_menu = pk::get_force(menu_force_id_);
			
			if( 연합결성소비타입 == 0 )
			{
				if (force_menu.tp < 필요기교포인트){return false;}
			}
			else if( 연합결성소비타입 == 1 )
			{
				if (pk::get_district(pk::get_district_id(force_menu, 1)).ap < 필요행동력){return false;}
			}
			
			return true;
		}
		
		string getMenuDesc()
		{	
			pk::force@ force_menu = pk::get_force(menu_force_id_);
			
			string desc = "";
			
			if( 연합결성소비타입 == 0 )
			{
				desc = "연합군 결성을 시도합니다. (기교P : "+필요기교포인트+"소비)";
				if (force_menu.tp < 필요기교포인트){desc = "기교P가 부족합니다.(기교P "+필요기교포인트+")";}
			}
			else if( 연합결성소비타입 == 1 )
			{
				desc = "연합군 결성을 시도합니다. (행동력 : "+필요행동력+"소비)";
				if (pk::get_district(pk::get_district_id(force_menu, 1)).ap < 필요행동력){desc = "행동력이 부족합니다.(행동력 "+필요행동력+")";}
			}
			
			return pk::encode(desc);
		}
		
		
		

		bool isMenuVisible()
		{
			return menu_city_id_ != -1 and menu_force_id_ == pk::get_current_turn_force_id();
		}
		string getMenuText()
		{
			return pk::encode("연합결성");
		}

		int getMenuImageID()
		{
			return 889;
		}

		bool menuHandler()
		{
			
			pk::force@ force_menu = pk::get_force(menu_force_id_);
			
			if(
				메뉴기능활성화 != 1 
				or 연합시도[menu_force_id_] >= 0 
				// or 유저연합결성중복시도[force_menu.get_id()] != 0
				or ( 연합결성소비타입 == 0 and force_menu.tp < 필요기교포인트 )
				or ( 연합결성소비타입 == 1 and pk::get_district(pk::get_district_id(force_menu, 1)).ap < 필요행동력 )
				or 유저_연합성공[force_menu.get_id()] >= 0
			){
				
				string talk = "연합군 결성 공작 중 입니다. ";
				
				SelectionAllianceEnemies(true);
				
				if(연합공작말 != ""){ talk = "현재\x1b[1x"+연합공작말+"\x1b[0x"+hanFix.return_chosa(연합공작말,1)+" 상대로 연합 공작 중입니다. "; }			
				
				if(연합시도[menu_force_id_] >= 0)talk += "공작 진행 중 입니다.";
				// else if(유저연합결성중복시도[force_menu.get_id()] != 0)talk += "하순 즈음 노려보겠습니다.";
				else if( 연합결성소비타입 == 0 and force_menu.tp < 필요기교포인트 )talk = "기교 포인트가 부족합니다";
				else if( 연합결성소비타입 == 1 and pk::get_district(pk::get_district_id(force_menu, 1)).ap < 필요행동력 )talk = "행동력이 부족합니다";
				else if(유저_연합성공[force_menu.get_id()] >= 0)talk = "현재 연합전쟁 중 입니다. ";
				
				// 말할 인물 정하기		
				pk::person@ teller = getGunshiOrMunkwan(force_menu);			
				pk::message_box(pk::encode(talk), teller);	
			}
			else{
				
				
				// 연합적 정하기
				int allianceEnemyForceId = SelectionAllianceEnemies(false);
				if(allianceEnemyForceId < 0)return true;
				// 유저연합결성중복시도[force_menu.get_id()] == 1;
				// 연합군 결성 진행								
				doAlliancingAttack(allianceEnemyForceId);
				// 결과
				
			}
			
			return true;
			
		}

		
		// 연합적 force_id 반환
		int SelectionAllianceEnemies(bool 탐색만){
			
			// 가능한 연합적 목록
			pk::list<pk::force@> 연합적후보;
			
			pk::force@ force0 = pk::get_force(menu_force_id_);
			
			// 연합목표가 될 확률이 높은 순으로 나온다.
			for (int j = 0; j < 세력_끝; j++){
				pk::force@ force_willEnemy = pk::get_force(j);
				if(!pk::is_alive(force_willEnemy) or !pk::is_valid_force_id(j))continue;
								
				// 타겟후보와 적이고,
				if(!pk::is_enemy(menu_force_id_, j))continue;
				
				// 인접국이고,
				if(!pk::is_neighbor_force(force0, force_willEnemy))continue;
				
				//pk::printf(pk::encode("SelectionAllianceEnemies force_willEnemy=["+force_willEnemy.kunshu+"]  \n"));
						
				연합적후보.add(force_willEnemy);
				
				
			} // end - for
			
			string string_연합공작세력 = "";
			array<int> answerForceId; // force_id 저장
			for (int k = 0; k < 연합적후보.count; k++){
				string kunshu_name = pk::decode(pk::get_name(pk::get_person(연합적후보[k].kunshu)));
				answerForceId.insertLast(연합적후보[k].get_id());
				string_연합공작세력 += " " + kunshu_name;
			}
			
			if(탐색만)return 0;
			
			pk::person@ teller = getGunshiOrMunkwan(force0);
			
			// 선택 2 단계					
			if(answerForceId.length == 0){pk::message_box(pk::encode("연합군을 일으킬만한 적이 없습니다"), teller);return -1;}	
			
			// string talk = "";			
			// if(string_연합공작세력 != ""){ talk = "현재\x1b[1x"+string_연합공작세력+"\x1b[0x"+hanFix.return_chosa(string_연합공작세력,1)+" 상대로 연합 공작을 펼치고 있습니다. "; }	
			
						
			// int n = pk::choose(pk::encode("어느 세력을 상대로 연합군을 일으키시겠습니까?"), answers);
			string selector_desc = pk::encode("토벌할 세력을 선택하세요.");
			pk::list<pk::force@> selected_enemy = pk::force_selector(pk::encode("세력 선택"), selector_desc, 연합적후보, 1, 1);
			if (int(selected_enemy.count) == 0) return -2;
			string selected_kunshu_name = pk::decode(pk::get_name(pk::get_person(selected_enemy[0].kunshu)));
			if(pk::choose(pk::encode("\x1b[16x"+selected_kunshu_name+"\x1b[0x"+hanFix.return_chosa(selected_kunshu_name,1)+" 상대로 연합군을 일으키시겠습니까?"), { pk::encode("예"), pk::encode("아니오") }) == 1)return -2;
			
			return selected_enemy[0].get_id();
		}
		
		
		
		
		
		
		void doAlliancingAttack(int force_id_target ){
			
			플레이어연합적 = force_id_target;
			
			pk::force@ force_player = pk::get_force(menu_force_id_);
			// util.prnt("doAlliancingAttack force_player_id=["+menu_force_id_+"] force_kunshu=["+force_player.kunshu+"] gunshi=["+force_player.gunshi+"]");
			
			// 군사가 없다면 군주의 능력치 반영
			pk::person@ represent = getGunshiOrKunshu(force_player);
			pk::person@ teller_fail = getGunshiOrMunkwan(force_player);
			
			float promoterEffect = getDistinctEffect(represent.stat[무장능력_지력]+represent.stat[무장능력_정치], 200.0, 3);			
			
			float minPossible = prob_연합적[force_id_target] <= 0 ? 유저_추가연합성공률 : prob_연합적[force_id_target] + 유저_추가연합성공률;				
			int chosenPossibility = int((minPossible * promoterEffect * 연합적확정계수) * 100);
			
			
			// util.prnt("doAlliancingAttack enemy_kunshu=["+pk::get_force(force_id_target).kunshu+"] enemyProb=["+prob_연합적[force_id_target]+"]  promoterEff=["+promoterEffect+"] chosenPossibility=["+chosenPossibility+"]  ");
			
			if( pk::rand_bool(chosenPossibility) ){	
				
				int result = AllianceAttack(force_player, force_id_target);
				if(result == -1){ // 성공!					
					
				}
				else{
					
					doAlliancingAttackFaleMessage(teller_fail, result);// 연합공격실패
				}
				
			}
			else{ // 연합적 확정 실패
				doAlliancingAttackFaleMessage(teller_fail, 10);
				
			}
			
			/// 연합결성 행동력 소비
			if(연합결성소비타입 == 0){ pk::add_tp(force_player, -필요기교포인트, force_player.get_pos()); }
			else if(연합결성소비타입 == 1){ 
				auto district = pk::get_district(pk::get_district_id(force_player, 1));
				district.ap -= 필요행동력;	
			}
			
			연합시도[menu_force_id_] = 연합시도지연_일수;
				
			// 초기화	
			플레이어연합적 = -1;
			
		}
		
		void doAlliancingAttackFaleMessage(pk::person@ speaker, int result){
			
			pk::scene(pk::scene_t(Scene_ResultDoAlliancingAttack));		
			
			string talk = "연합군 결성에 실패했습니다. ";				
			switch (result)
			{
			case 1: 
				talk += "보급문제로 군사 내기를 꺼리고 있습니다.";
				break;
			case 2: 
				talk += "저희와 동조하는 세력이 없습니다.";
				break;
			case 3: 				
				break;
			case 4: 
				break;
			case 5: 
				talk += "병력이 부족합니다.";
				break;
			case 10:
				talk += "운이 따르지 않았습니다.";
				break;
			}
			
			pk::message_box(pk::encode(talk), speaker);
		}
		
		void Scene_ResultDoAlliancingAttack(){
			pk::fade(0);
			pk::sleep();
			pk::fade(255);
			
		}
		
		// 말할 사람: 군주 혹은 군사
		pk::person@ getGunshiOrKunshu(pk::force@ force){
			// util.prnt("getGunshiOrKunshu menu_force_id_=["+menu_force_id_+"] force_id=["+force.get_id()+"] kunshu_id=["+force.kunshu+"] gunshi_id=["+force.gunshi+"]");
			pk::person@ gunshi = pk::get_person(force.gunshi);
			pk::person@ kunshu = pk::get_person(force.kunshu);
			pk::person@ speaker = pk::is_alive(gunshi) ? gunshi : kunshu;
			return speaker;
		}
		// 말할 사람: 군사 혹은 문관
		pk::person@ getGunshiOrMunkwan(pk::force@ force){
			// util.prnt("getGunshiOrMunkwan gunshi=["+force.gunshi+"]");
			pk::person@ gunshi = pk::get_person(force.gunshi);
			pk::person@ speaker = pk::is_alive(gunshi) ? gunshi : pk::get_person(무장_문관);
			return speaker;
		}
		
		void set_prob_연합적()
		{
			prob_연합적_desc = array<pk::int_int>(); // 세력id_확률백분위
			
			float grade_top_세력병사 = 1.f;
			float grade_top_인접적수 = 0.5f;
			float cut = 0.f;
			// 10 등 세력까지만. 이하는 음수 이므로 체크 안함.
			for (int i = 0; i < 10; i++){				
				if(rank_세력병사[i] == -1 or rank_인접적수[i] == -1)break; // 음수값 이하는 등수에 없는 세력들.				
				// line_bigO++;
				float grade_세력병사 = grade_top_세력병사 + cut;
				float grade_인접적수 = grade_top_인접적수 + cut;
				
				if(grade_세력병사 >= 0){
					if(prob_연합적[rank_세력병사[i]] == -2.f)prob_연합적[rank_세력병사[i]] = grade_세력병사;
					else{prob_연합적[rank_세력병사[i]] += grade_세력병사;}
				}							
				
				if(grade_인접적수 >= 0){
					if(prob_연합적[rank_인접적수[i]] == -2.f)prob_연합적[rank_인접적수[i]] = grade_인접적수;
					else{prob_연합적[rank_인접적수[i]] += grade_인접적수;}	
				}
				
				
				pk::int_int prob = pk::int_int(rank_세력병사[i], (prob_연합적[rank_세력병사[i]]) * 100);
				int find_idx = prob_연합적_desc.findByRef(prob);
				if(find_idx < 0)prob_연합적_desc.insertLast(prob);
				else { prob_연합적_desc[find_idx] = prob; }
				
								
				// util.prnt("i=["+i+"] troops_top_force["+pk::get_force(rank_세력병사[i]).kunshu+"]=["+prob_연합적[rank_세력병사[i]]+"] neighbor_enemy_top["+pk::get_force(rank_인접적수[i]).kunshu+"]=["+prob_연합적[rank_인접적수[i]]+"] ");
								
				cut -= 0.1f;
			}
			// util.prnt("prob length=["+prob_연합적_desc.length+"]");
			if(prob_연합적_desc.length > 0){
				prob_연합적_desc.sort(function(a,b) { 				
					return a.second > b.second; 
				});
			}
			
			
			/*
			// log
			for (int j = 0; j < prob_연합적_desc.length; j++){
				pk::int_int prob = prob_연합적_desc[j];
				// util.prnt("prob_enemy_desc force_id=["+prob.first+"] force_kushu=["+pk::get_force(prob.first).kunshu+"] prob=["+prob.second+"] ");
			}
			*/
			
			// util.prnt("--------------------------------------------------------------------------------------------------");
		}
		
		void search_연합적(){
			
			
			pk::list<pk::force@> force0_list = pk::get_force_list(false); // 연맹주 후보
			
			
			for (int i = 0; i < force0_list.count; i++){
				if(isIminzoku(force0_list[i]))continue;				
				// 연맹주 세력
				int force0_id = force0_list[i].get_id();
				pk::force@ force0 = force0_list[i];				
				if(force0.is_player())continue;
				if(연합시도[force0_id] >= 0)continue;
				if(연합성공지연[force0_id] >= 1)continue;				
				
				// 군사가 없다면 군주의 능력치 반영				
				pk::person@ leader = getGunshiOrKunshu(force0);
				
				float leaderEffect = getDistinctEffect(leader.stat[무장능력_지력]+leader.stat[무장능력_정치], 200.0, 3);
				
				// 연합목표가 될 확률이 높은 순으로 나온다.
				for (int j = 0; j < prob_연합적_desc.length; j++){
					
					pk::int_int prob = prob_연합적_desc[j];
					int force2_id = prob.first;
					pk::force@ force2 = pk::get_force(force2_id);
					
					if(!pk::is_alive(force2) or !pk::is_valid_force_id(force2_id))continue;		
					
					if(force2_id == force0_id)continue;	// 자기자신 제외						
					
					if(세력대전쟁여부[force0_id][force2_id] != 1)continue;	// 연합적과 전쟁중인가
					
					if(!pk::is_neighbor_force(force0, force2))continue; // 인접국인가
					
					// line_bigO++;
					
					// 나 보다 얼마나 강한가? 
					float 맹주세력대비강함정도 = 
						세력부가속성[force2.get_id()][속성_병력] / float(pk::max((세력부가속성[force0_id][속성_병력] + 세력부가속성[force2.get_id()][속성_병력]), 1));						
					맹주세력대비강함정도 = 연합적과세력비교 ? 맹주세력대비강함정도 : 1.0;
					
					// 우호도
					float relations = pk::max(((100 - force0.relations[force2_id]) / 100.f), 0.1f);					
					
					float 연합적확률 = 연합적확정계수 * prob_연합적[force2_id] * 맹주세력대비강함정도 * (relations * relations * relations);						
					int chosenPossibility = int(( 연합적확률 * leaderEffect ) * 100);
					
					
					if( getRandom(chosenPossibility, 11) ){	
						
						연합공격적 = force2_id;
						int result = AllianceAttack(force0, force2_id);	
						
						연합시도[force0_id] = 연합시도지연_일수;
						
						// util.prnt("Alliance leader=["+force0.kunshu+"] enemy=["+force2.kunshu+"] enemyProb=["+prob_연합적[force2_id]+"]  leaderEff=["+leaderEffect+"] enemyTroopsRate=["+floor(맹주세력대비강함정도*100)/100+"] relations=["+relations+"] chosenPossibility=["+chosenPossibility+"] result=["+result+"]");
						// pk::printf(pk::encode("----------------------------------------- success? ["+result+"] -------------------------------------------\n"));
						
						return;
					}	
					
				} // end - for				
			} // end - for
			
			
			// pk::printf(pk::encode("-------------------------------------------- fail -----------------------------------------------\n"));
			
			
		}
		
		// cnt 는 홀수
		bool getRandom(float prob, int8 cnt){
			
			int8 t = 0;
			int8 f = 0;
			
			while (cnt > 0){
				cnt -= 1;
				if( pk::rand_bool(prob) ){t+=1;}else{f+=1;}
			}
			// util.prnt("prob=["+prob+"] t=["+t+"] f=["+f+"]");			
			return t > f ? true : false;
		}
		
		/// 연합군 출진 도시 주변 출진도시 검색
		void addAllianceCities(int city0_id, int city2_id, array<AllianceInfo@> &연합군정보, array<int> &출진횟수, array<int> arr_연합군세력){
			
			array<int> neighbor_cities = neighborMap.인접도시[city0_id];
			for (int i = 0; i < neighbor_cities.length; i++){
				pk::city@ neighbor_city = pk::get_city(neighbor_cities[i]);
				int force_id = neighbor_city.get_force_id();
				if(!pk::is_alive(neighbor_city) or !pk::is_valid_force_id(force_id))continue;			
				// 연합군 일원 인가?
				if(!isAllianceForce(force_id, arr_연합군세력))continue;			
				
				// 출진도시 추가
				// util.prnt("addAllianceCities force=["+force_id+"] city=["+neighbor_city.get_id()+"] city2=["+city2_id+"] num_go=["+출진횟수[neighbor_city.get_id()]+"]");
				연합군정보.insertLast(AllianceInfo(force_id, neighbor_city.get_id(), city2_id, false));
				출진횟수[neighbor_city.get_id()] += 1; // 출발도시 기준 출진횟수
			}
			
		}
				
		void set_연합군_도착도시(array<AllianceInfo@> &연합군정보){
			dictionary dic;
			for (int i = 0; i < 연합군정보.length; i++){
				pk::city@ city0 = pk::get_city( 연합군정보[i].출발도시);
				pk::city@ city2 = pk::get_city( 연합군정보[i].도착도시);			
				string key = city0.get_id() + "";
				if(dic.exists(key)){
					auto arr = cast<array<int>>(dic[key]);	
					arr.insertLast(city2.get_id());					
				}					
				else{
					array<int> arr = {city2.get_id()};
					dic.set(key, arr);
				}					
			}
			for (int i=0; i<dic.getKeys().length; i++){
				string key = dic.getKeys()[i];
				auto arr = cast<array<int>>(dic[key]);	
				arr.sort(function(a,b) {
					pk::city@ city0 = pk::get_city(a);
					pk::city@ city2 = pk::get_city(b);					
					return pk::get_troops(city0) < pk::get_troops(city2); 
				});				
			}
			for (int i = 0; i < 연합군정보.length; i++){
				string key = 연합군정보[i].출발도시 + "";
				auto arr = cast<array<int>>(dic[key]);
				연합군정보[i].도착도시 = arr[0];
			}
		}
		
		int AllianceAttack(pk::force@ force_leader, int target_force_id){
			
			// 플레이어연합군메뉴를 활성화 했으면 return
			if(force_leader.is_player() and 플레이어연합적 == -1 )return 3;	
			
			pk::force@ target_force = pk::get_force(target_force_id);
			if (!pk::is_alive(target_force) or !pk::is_valid_force_id(target_force_id))return 0;	
			
			
			string force_leader_kunshu_name = pk::decode(pk::get_name(pk::get_person(force_leader.kunshu)));
			string target_kunshu_name = pk::decode(pk::get_name(pk::get_person(pk::get_force(target_force_id).kunshu)));
			
			// 연합군 정보 배열
			array<AllianceInfo@> 연합군정보;
			array<int> 출진횟수(도시_끝, 0);		
			
			string last_kunshu_name = "";
			
			// 플레이어 상태 			
			array<pk::bool_bool> alliancePlayers(세력_끝, pk::bool_bool(false, false));// 연합군여부, 참전여부			
			array<int> 연합군세력_distinct; // 연합 가능한 모든 세력
			
			// 연합군 군주 이름들
			string msg1 = "";
			
			// 연합군 찾기
			// 적 도시 와 인접한 도시 탐색
			pk::list<pk::city@> target_city_list = pk::get_city_list(target_force);
			for (int i = 0; i < target_city_list.count; i++)
			{				
				auto target_city = target_city_list[i];
				if (!pk::is_alive(target_city) or !pk::is_valid_force_id(target_city.get_force_id()))continue;
				
				array<int> neighbor_cities = neighborMap.인접도시[target_city.get_id()];
				for (int j = 0; j < neighbor_cities.length; j++){
					
					pk::city@ neighbor_city = pk::get_city(neighbor_cities[j]);					
					if(!pk::is_alive(neighbor_city) or !pk::is_valid_force_id(neighbor_city.get_force_id()))continue;
					// 연합적 거점이 아닌가?
					if(neighbor_city.get_force_id() == target_force_id)continue;
					
					// line_bigO++;
					
														
					int ally_force_id = neighbor_city.get_force_id();	
					pk::force@ ally_force = pk::get_force(ally_force_id);
					
					// 연합군 세력이 유효한가?
					if (!pk::is_alive(ally_force) or !pk::is_valid_force_id(ally_force_id))continue;	
								
					// 연합적과 적 관계인가?
					// if(!pk::is_enemy(ally_force_id, target_force_id))continue;
					
					// 플레이어도 연합국인가?
					bool is_player_alliance = ally_force.is_player();					
					if(is_player_alliance)alliancePlayers[ally_force_id].first = true;
					
					// 리더세력과의 우호도
					// 연합적도 싫지만 너도 싫어
					if( !is_player_alliance and (force_leader.relations[ally_force_id] < 30) )continue;
										
					연합군정보.insertLast(AllianceInfo(ally_force_id, neighbor_city.get_id(), target_city.get_id(), false));
					출진횟수[neighbor_city.get_id()] += 1; // 출발도시 기준 출진횟수
					
					
					// 중복제거 
					if(연합군세력_distinct.find(ally_force_id) < 0){
						연합군세력_distinct.insertLast(ally_force_id);
						// 연합수장 세력 배제
						// if(ally_force_id != force_leader.get_id())연합할세력수_리더제외++;
						
					}
					
				}
				
			}
			
			
			pk::person@ kunshu_target = pk::get_person(target_force.kunshu);
			pk::person@ kunshu_leader = pk::get_person(force_leader.kunshu);
			pk::person@ leader_represent = getGunshiOrKunshu(force_leader);	
			float leaderEff = getDistinctEffect(leader_represent.stat[무장능력_지력], 100.0, 4);	// 비용절감
			
			
			// 인접한 연합군이 없을 경우
			if(연합군정보.length == 0)return 1;
			
			// 연합군이 자신의 세력만 있을 경우. 연합 가능한 세력이 없다.
			// util.prnt("cnt_alliance_distinct=["+연합군세력_distinct.length+"] ");
			if(연합군세력_distinct.length <= 1)return 2;
			
			set_연합군_도착도시(연합군정보);
			
			/// 추가 출진도시
			int length_연합군정보 = 연합군정보.length;
			for (int p = 0; p < length_연합군정보; p++){
				// util.prnt("addAllianceCities AllianceInfoList=["+연합군정보.length+"]");
				addAllianceCities( 연합군정보[p].출발도시,  연합군정보[p].도착도시, 연합군정보, 출진횟수, 연합군세력_distinct);					
			}
			
			/// 원군 출진 정보
			array<int8> 원군도시중복여부(건물_거점끝, -1);
			int length_연합군정보3 = 연합군정보.length;
			for (int p = 0; p < length_연합군정보3; p++){
				pk::city@ city0 = pk::get_city( 연합군정보[p].출발도시);				
				pk::building@ building0 = pk::city_to_building(city0);
				bool isWarAt = intToBoolean(건물전쟁여부[building0.get_id()]); 									
				/// 전쟁중인 도시에는 원군 출전.
				if(!isWarAt or 원군도시중복여부[building0.get_id()] == 1)continue;
				원군도시중복여부[building0.get_id()] = 1;
				prepareReinforcement(building0, 연합군정보, 출진횟수, 연합군세력_distinct, leaderEff);					
			}
			
			
			/// 공격 준비			
			
			int 병력_연합군 = 0;
			array<int8> 병력_연합적중복(건물_거점끝, -1);
			int 병력_연합적 = 0;
			array<array<pk::person@>> 기출진무장(건물_거점끝, {});
			array<UnitInfo@> 출진정보;	
			array<int> 출진도시병력(건물_거점끝, -1);
			array<int> 출진도시병량(건물_거점끝, -1);			
			세력출진병력 = array<int>(세력_끝, 0);
			
			for (int m = 0; m < 연합군정보.length; m++){
				// if(연합군세력[m] == -1 or 출발도시[m] == -1 or 도착도시[m] == -1)continue;	
				// pk::force@ force_ally = pk::get_force(연합군정보[m].연합군세력);
				// util.prnt("force kunshu=["+force_ally.kunshu+"] from=["+연합군정보[m].출발도시+"] to=["+연합군정보[m].도착도시+"] is_player=["+force_ally.is_player()+"] ");
				
				/// 플레이어 세력은 자동으로 부대를 출전하지 않는다
				if(pk::get_force(연합군정보[m].연합군세력).is_player())continue;				
				// line_bigO++;
				
				pk::city@ city0 = pk::get_city( 연합군정보[m].출발도시);				
				pk::building@ building0 = pk::city_to_building(city0);
				pk::building@ building2 = pk::city_to_building(pk::get_city( 연합군정보[m].도착도시));
				bool isWarAt = intToBoolean(건물전쟁여부[building0.get_id()]); 
					
				/// 거리가 최대출진거리 이상이면 취소
				int 순_distance = ceil(pk::get_distance(building0.get_pos(), building2.get_pos()) / 기준_칸이동력);
				if(순_distance > 13)continue;
					
				/// 연합적 병력 구하기 
				if(병력_연합적중복[building2.get_id()] == -1){
					병력_연합적 += pk::get_troops(building2);
					병력_연합적중복[building2.get_id()] = 1;
				}
				
				if(isWarAt)continue; // 도시가 전쟁중이면 pass		
				
				if(isAroundEnemyThreat(city0))continue; // 주위에 위협적인 적이 있는가?
					
				
				/// 출진 병력 구하기
				/// 출진 가능한 무장 구하기
				auto person_list = pk::get_idle_person_list(building0);
				if (person_list.count == 0)continue;
				person_list.sort(function(a, b){ return a.stat[무장능력_통솔] + a.stat[무장능력_무력] > b.stat[무장능력_통솔] + b.stat[무장능력_무력]; });				
				/// 한 도시에서 출진횟수로 나눈 출진부대수
				int numUnit = pk::min(int( person_list.count ), 한도시최대출진부대수);		
				if(출진횟수[city0.get_id()] > 0) numUnit = int(numUnit / float(출진횟수[city0.get_id()]));	
				// util.prnt("remove_person_1 building=["+building0.get_id()+"] person_list=["+person_list.count+"] person_gone=["+기출진무장[building0.get_id()].length+"]");								
				// util.prnt("-------------------------------------------------------------------------");
				auto person_array = remove_중복_persons(get_personIds(person_list), 기출진무장[building0.get_id()]); //이전 출진무장 제외
				numUnit = pk::min(numUnit, person_array.length);
				// get_personIds(person_array); // for Debug
				array<int> 출진무장;
				int 출진부대병력 = 0;
				int 도시_병력 = 출진도시병력[building0.get_id()];
				출진도시병력[building0.get_id()] = 도시_병력 == -1 ? pk::get_troops(building0) : 도시_병력;
				int 도시_병량 = 출진도시병량[building0.get_id()];
				출진도시병량[building0.get_id()] = 도시_병량 == -1 ? pk::get_food(building0) : 도시_병량;
				// util.prnt("building0["+building0.get_id()+"] troops=["+출진도시병력[building0.get_id()]+"] food=["+출진도시병량[building0.get_id()]+"]");
				for (int o = 0; o < numUnit; o++){
					pk::person@ p = pk::get_person(person_array[o]); 
					int rank_troops = pk::get_rank( p.rank).command;
					rank_troops = GetTroops(p);
					int troops = rank_troops;
					int food = int(troops * 부대생성_병량비율);
					bool isLackingTroops = false;
					bool isLackingFood = false;
					if(출진도시병력[building0.get_id()] < troops){ 
						isLackingTroops = true;
						if(!항상최대병력출진)troops = 최소출진병력수;
					}					
					int cost_food = int(food * leaderEff);
					if(출진도시병량[building0.get_id()] <= food){isLackingFood = true;}						
					if(isLackingFood)continue;
					if(출진_도시병력내 and isLackingTroops)continue;						
					
					출진부대병력 += troops;	
					출진무장.insertLast( p.get_id());
					기출진무장[building0.get_id()].insertLast(p);
					세력출진병력[p.get_force_id()] += troops;
					// util.prnt("Unit_to_Go person=["+p.get_id()+"]");
					
					// 도시 물자 차감			
					if(!isLackingTroops)출진도시병력[building0.get_id()] -= troops;
					if(!isLackingFood)출진도시병량[building0.get_id()] -= cost_food;						
				}
				병력_연합군 += 출진부대병력;
				// get_personIds(기출진무장[building0.get_id()]); // for Debug
				// util.prnt("Get_Troops building=["+building0.get_id()+"] person_array=["+person_array.length+"] person_gone=["+기출진무장[building0.get_id()].length+"]");				
				
				출진정보.insertLast(UnitInfo(출진무장, building0.get_id(), building2.get_id(), isWarAt, numUnit, 연합군정보[m].isReinforcement));				
				출진횟수[city0.get_id()] -= 1;
				
				
			} // end - for
			
			
			/// 동맹이더라도 병력차가 압도적이면 군주에 따라 동맹을 파기하고 연합에 참가한다.
			/// 참전병력이 많은 순으로 정렬. 
			array<int> 동맹파기세력;
			연합군세력_distinct.sort(function(a,b) { 			
				return main.세력출진병력[a] > main.세력출진병력[b]; 
			});
			int 병력_연합군_파기반영 = 병력_연합군; // 연합적과 동맹여부가 반영된.
			for (int i = 0; i < 연합군세력_distinct.length; i++){	
				pk::force@ force = pk::get_force(연합군세력_distinct[i]);
				pk::person@ kunshu = pk::get_person(force.kunshu);				
				if(pk::is_enemy(force, target_force))continue; // 연합적과 동맹관계가 아니면 해당하지 않는다.
				if(pk::is_like(kunshu, target_force.kunshu))continue; // 연합적과 친애 관계면 파기하지 않는다.
				
				/// 동맹파기 조건
				if(!is_연합병력비교(kunshu, 병력_연합군_파기반영, 병력_연합적, get_군주배신배수(kunshu, force.relations[target_force_id])))
				{ // 연합적과 동맹유지.
					병력_연합군_파기반영-=세력출진병력[force.get_id()]; 
					// util.prnt("remove_from_alliance ["+force.kunshu+"]");
					continue; 
				}
				// util.prnt("betray_alliance ["+force.kunshu+"]");
				동맹파기세력.insertLast(force.get_id());
							
			}
			
			

			/// 연합군병력수 VS 연합적병력수 비교			
			float 군주배수 = force_leader.is_player() ? 군주배수_player : get_군주배수_연합병력차(kunshu_leader);
			if(병력_연합군_파기반영 <= 0 or !is_연합병력비교(kunshu_leader, 병력_연합군_파기반영, 병력_연합적, 군주배수 ))return 5;				
			
			
			
			if(연합군세력_distinct.length > 1){ // 연맹주를 제외한 연합세력이 있을 경우(플레이어세력포함)
				
				연합군세력_distinct.sort(function(a,b) { 					
					if(pk::get_force(a).is_player())return false;
					if(pk::get_force(b).is_player())return true;
					return main.세력부가속성[a][속성_병력] > main.세력부가속성[b][속성_병력]; 
				});
				
				// get_forceIds(연합군세력_distinct); // for Debug
						
				int alliance_top_force_id = 연합군세력_distinct[0];
				int alliance_top2_force_id = 연합군세력_distinct[1];	
				
				// 설전: 리더 세력은 연합군 최강세력과 대결을 한다	
				// 연합군 최고 세력
				pk::force@ force_topAlly = pk::get_force(alliance_top_force_id);					
				if(force_leader.get_id() == alliance_top_force_id)@force_topAlly = pk::get_force(alliance_top2_force_id);	
				
				pk::person@ topAlly_represent = getGunshiOrKunshu(force_topAlly);
				
				// pk::printf(pk::encode("Alliance Leader_kunshu=["+force_leader.kunshu+"] target_kunshu=["+target_force.kunshu+"] top1=["+alliance_top_force_id+"] top2=["+alliance_top2_force_id+"]  \n"));					

				if(DebateForAllyVSAlly(연합군세력_distinct, kunshu_target, leader_represent, topAlly_represent) == 1)return 4;
				
			}
			
			
			
			/// SCENE: Player 연합여부	
			
			s_fa_unAlly_forces = 동맹파기세력;
			s_fa_alliancePlayers = alliancePlayers;
			s_fa_leader_force_id = force_leader.get_id();
			s_fa_target_force_id = target_force_id;
			s_fa_alliance_force = 연합군세력_distinct;
			pk::scene(pk::scene_t(Scene_FormingAlliance));
			alliancePlayers = s_fa_alliancePlayers;
			
			/// 플레이어세력 선택후에도 연합군이 연맹주 혼자일 경우
			// util.prnt("is_alliance_toSay=["+is_언급할연합세력+"] is_player_involved=["+is_플레이어_참전(alliancePlayers)+"] ");
			if(!is_언급할연합세력 and !is_플레이어_참전(alliancePlayers) )return 2;
			
			
			
			
			// 연합 도시 간 정전협정 & 우호도 증가
			// 세력간 한 번 씩만 만나도록
			array<array<int8>> 연합세력대세력간한번(세력_끝, array<int8>(세력_끝, -1));
			array<int> 참여연합세력;
			for (int k = 0; k < 연합군정보.length; k++){	
				pk::force@ force0 = pk::get_force(연합군정보[k].연합군세력);
				int ally0_id = force0.get_id();
				for (int l = k; l < 연합군정보.length; l++){					
					pk::force@ force1 = pk::get_force(연합군정보[l].연합군세력);										
					int ally1_id = force1.get_id();		
					
					if(연합군정보[l].연합군세력 == 연합군정보[k].연합군세력){setAllianceAttackFlag(alliancePlayers, ally0_id, ally1_id, 참여연합세력); continue;}
					
					// 연합적과 적 관계인가?
					if(!pk::is_enemy(ally0_id, target_force_id))continue;
					if(!pk::is_enemy(ally1_id, target_force_id))continue;
					
					if(연합세력대세력간한번[ally0_id][ally1_id] == 1)continue;
					if(연합세력대세력간한번[ally1_id][ally0_id] == 1)continue;		
					// line_bigO++;
					연합세력대세력간한번[ally0_id][ally1_id] = 1;
					연합세력대세력간한번[ally1_id][ally0_id] = 1;
					
					
					// 플레이어가 연합을 거절했을 경우,	
					if(	(alliancePlayers[ally0_id].first and !alliancePlayers[ally0_id].second) or
						(alliancePlayers[ally1_id].first and !alliancePlayers[ally1_id].second)
					){						
						pk::add_relations(ally0_id, ally1_id, -30);	
						continue;
					}
					
					// pk::printf(pk::encode("ceasefire ally0_kunshu=["+force0.kunshu+"] ally1_kunshu=["+force1.kunshu+"] \n"));
					
					pk::add_relations(ally0_id, ally1_id, 20);					
					pk::set_ceasefire_timer(force0, force1, 20);
					
					setAllianceAttackFlag(alliancePlayers, ally0_id, ally1_id, 참여연합세력);
					
				}
			}
			진행중인연합세력.insertLast(참여연합세력);
			// util.prnt("insert alliance_being_forces count=" + 진행중인연합세력.length);
			
			
			// 출진
			// util.prnt("AllianceInfos length=["+연합군정보.length+"]");
			for (int i = 0; i < 출진정보.length; i++){
				UnitInfo info = 출진정보[i];
				pk::building@ 출진건물 = pk::get_building(info.출진_도시);
				if(!pk::is_enemy(출진건물.get_force_id(), target_force_id))continue;
				pk::building@ building2 = pk::get_building(info.출진_목표);
				
				// util.prnt("UnitInfos i=["+i+"] num_unit=["+info.출진_부대수+"] city0=["+info.출진_도시+"] city2=["+info.출진_목표+"]");				
				for (int j = 0; j < info.출진_무장.length; j++){					
					CreateAUnit(pk::get_person(info.출진_무장[j]), 출진건물, pk::get_building(info.출진_목표), leaderEff, info.출진_전쟁여부, j, info.isReinforcement, {});					
				}
			}
			
			
			//pk::printf(pk::encode("------------------------------------------------------ \n"));
			
			
			return -1;
			
		} // end - AllianceAttack
		
		array<int> get_personIds(pk::list<pk::person@> lst){
			array<int> ids;
			string str = "";
			for (int i = 0; i < lst.count; i++){
				ids.insertLast(lst[i].get_id());
				str += lst[i].get_id() + ", ";
			}
			// util.prnt(str);
			return ids;
		}
		array<int> get_personIds(array<pk::person@> arr){
			array<int> ids;
			string str = "";
			for (int i = 0; i < arr.length; i++){
				ids.insertLast(arr[i].get_id());
				str += arr[i].get_id() + ", ";
			}
			// util.prnt(str);
			return ids;
		}
		array<int> get_personIds(array<int> arr){
			array<int> ids;
			string str = "";
			for (int i = 0; i < arr.length; i++){
				ids.insertLast(arr[i]);
				str += arr[i] + ", ";
			}
			// util.prnt(str);
			return ids;
		}
		
		array<int> get_forceIds(array<int> arr){
			array<int> ids;
			string str = "";
			for (int i = 0; i < arr.length; i++){
				ids.insertLast(arr[i]);
				str += arr[i] + "("+세력부가속성[arr[i]][속성_병력] +"), ";
			}
			// util.prnt(str);
			return ids;
		}
		///  중복 무장 빼기. 
		///  arr0 : 대상 목록
		///  arr1 : 제거 목록	
		array<int> remove_중복_persons(array<int> arr0, array<pk::person@> arr1){			
			array<int> arr2;
			for (int j = 0; j < arr1.length; j++){
				pk::person@ p1 = arr1[j];				
				int idx_p1 = arr0.find(p1.get_id());
				// util.prnt("p1=["+p1.get_id()+"] index=["+idx_p1+"]");
				if(idx_p1 >= 0){
					// util.prnt("REMOVE double_person=["+p1.get_id()+"] index=["+idx_p1+"]");
					arr0.removeAt(idx_p1); 
				}
			}
			
			return arr0;
		}
		
		/// 주위의 한 거점이 내병력 대비 x배 위험이 되는지 
		bool isAroundEnemyThreat(pk::city@ city0){
			int troops0 = pk::get_troops(city0);
			pk::force@ force0 = pk::get_force(city0.get_force_id());
			array<int> neighbor_cities = neighborMap.인접도시[city0.get_id()];
			for (int i = 0; i < neighbor_cities.length; i++){
				pk::city@ neighbor_city = pk::get_city(neighbor_cities[i]);
				int force_id = neighbor_city.get_force_id();
				if(!pk::is_alive(neighbor_city) or !pk::is_valid_force_id(force_id))continue;				
				if(!pk::is_enemy(force0, pk::get_force(force_id)))continue;	// 적이 아닌가?			
				int troops2 = pk::get_troops(neighbor_city);
				// 군주의 성격에 따라 무모한 정도 판단
				if(isEnemyThreat(pk::get_person(force0.kunshu), troops0, troops2)){
					// util.prnt("EnemyThreat TRUE  city0_troops=["+pk::get_troops(city0)+"] enemy_city_troops=["+troops+"] ");
					return true;
				}
			}
			return false;
		}
		
		/// 연맹주 성격에 따라 연합 일으킬지 여부를 정한다. 
		bool is_연합병력비교(pk::person@ kunshu0, int 병력_연합군, int 병력_연합적, float 군주배수)
		{
			// util.prnt("kunshu=["+kunshu0.get_id()+"] Character=["+kunshu0.character+"] Alliance=["+병력_연합군+"] Enemy=["+병력_연합적+"] return: "+(병력_연합적 / float(pk::max(병력_연합군, 1)))+" <= "+군주배수+" ");	
			if( (병력_연합적 / float(pk::max(병력_연합군, 1))) <= 군주배수)
				return true; // 연합성공			
			return false; // 연합실패						
		}
		
		/// 적 병력 위험한 정도 판단
		bool isEnemyThreat(pk::person@ kunshu0, int troops0, int troops2)
		{			
			float 군주배수 = get_군주배수_위험감수(kunshu0);
			float 병력비율 = troops2 / float(pk::max(troops0, 1));
			// util.prnt("isEnemyThreat kunhsu_val=["+군주배수+"] troops_val=["+병력비율+"]");
			if(병력비율 < 군주배수)return false;
			return true;
		}
		
		/// 주위도시병력이 현재도시병력 대비 몇배까지 인가?
		float get_군주배수_위험감수(pk::person@ kunshu){
			switch (kunshu.character)
			{
			case 성격_소심:				
				return 1.5;
			case 성격_냉정: 	
				return 2.0;
			case 성격_대담: 
				return 2.5;
			case 성격_저돌: 
				return 3.0;
			}
			return 2.0;
		}
		
		/// 연합군병력 대비 연합적병력 몇배까지 연합을 일으킬 수 있는가?
		float get_군주배수_연합병력차(pk::person@ kunshu){
			switch (kunshu.character)
			{
			case 성격_소심:				
				return 1.5;
			case 성격_냉정: 	
				return 2.0;
			case 성격_대담: 
				return 2.5;
			case 성격_저돌: 
				return 3.0;
			}
			return 1.5;
		}	
		
		/// 연합군병력 대비 연합적병력 몇배까지 배신범위에 드는가?		
		/// relations: 군주와 연합적과의 우호도
		float get_군주배신배수(pk::person@ kunshu, int relations){
			float rel = pk::max(((100 - relations) / 100.f), 군주최소배신계수);		
			// util.prnt("kunshu.character="+kunshu.character+" relations="+relations+" rel="+rel+"");			
			switch (kunshu.character)
			{
			case 성격_소심:					
				return 1.5 * rel;
			case 성격_냉정: 	
				return 2.0 * rel;
			case 성격_대담: 
				return 2.5 * rel;
			case 성격_저돌: 
				return 3.5 * rel;
			}
			return 1.0 * rel;
		}
		
		
		bool is_플레이어_참전(array<pk::bool_bool> arr){			
			for (int i = 0; i < arr.length; i++){
				if(!arr[i].first)continue; // 연합군 후보인가?
				if(arr[i].second)return true; // 연합군 승인했는가?
			}
			return false;
		}
		
		void setAllianceAttackFlag(array<pk::bool_bool> alliancePlayers, int ally0_id, int ally1_id, array<int> &참여연합세력){
			
			// 연합 참여 세력들이 시즌내에 중복 연합 발생 방지
			연합성공지연[ally0_id] = 연합성공지연_일수;
			연합성공지연[ally1_id] = 연합성공지연_일수;					
			
			if(참여연합세력.find(ally0_id) < 0)참여연합세력.insertLast(ally0_id);
			if(참여연합세력.find(ally1_id) < 0)참여연합세력.insertLast(ally1_id);
			
			// 플레이어 세력인가?
			if(alliancePlayers[ally0_id].first)유저_연합성공[ally0_id] = 유저_연합성공지연_일수;
			if(alliancePlayers[ally1_id].first)유저_연합성공[ally1_id] = 유저_연합성공지연_일수;
		}
		
		array<int> s_fa_unAlly_forces;
		pk::array<pk::bool_bool> s_fa_alliancePlayers;
		int s_fa_leader_force_id = -1;
		int s_fa_target_force_id = -1;
		array<int> s_fa_alliance_force; // 플레이어 선택여부가 반영된 실제 참여 연합군세력.
		bool is_언급할연합세력 = true;
		
		void Scene_FormingAlliance()
		{
			
			pk::force@ force_leader = pk::get_force(s_fa_leader_force_id);
			pk::force@ force_target = pk::get_force(s_fa_target_force_id);
			string leader_kunshu_name = pk::decode(pk::get_name(pk::get_person(force_leader.kunshu)));	
			string target_kunshu_name = pk::decode(pk::get_name(pk::get_person(force_target.kunshu)));				
						
								
			// 연합군 플레이어 수만큼 루프
			bool is_read = false;
			for (int i = 0; i < s_fa_alliancePlayers.length; i++){					
				if(s_fa_alliancePlayers[i].first == false)continue;
				
				pk::force@ force_player = pk::get_force(i);	// i 가 force_id 인가? +1 해야 force_id 인가			
				bool isPlayerAllianceLeader = (force_player.get_id() == s_fa_leader_force_id);
				string player_kunshu_name = pk::decode(pk::get_name(pk::get_person(force_player.kunshu)));				
				// pk::person@ speaker = getGunshiOrMunkwan(force_player);	
				
				/// 플레이어에게 명분 읊기. 한 번.
				if(!is_read and !isPlayerAllianceLeader){
					pk::fade(0);
					pk::sleep();
					pk::background(85);
					pk::fade(255);
					pk::play_se(16);
					
					pk::message_box(pk::encode(
						"역적 \x1b[16x"+target_kunshu_name+"\x1b[0x"+hanFix.return_chosa(target_kunshu_name,0)+" 선왕의 도를 무시하고, 외력으로 사복을 채우며, 국법을 범하고 농민을 약탈했다. \x1b[1x"+leader_kunshu_name+"\x1b[0x"+hanFix.return_chosa(leader_kunshu_name,0)+" 힘을 모아 역적을 토벌하라."
					));
					is_read = true;
				}
				
				
				if(isPlayerAllianceLeader){ 
					s_fa_alliancePlayers[i].second = true;
				}
				else{
					/// 연합적과 동맹이었다가 파기하는 경우
					string str_파기참가 = "";
					bool is_동맹중 = !pk::is_enemy(force_player, force_target);
					if(is_동맹중)str_파기참가 = "동맹을 파기하고 ";						
						
					if(pk::choose(pk::encode("\x1b[2x"+player_kunshu_name+"\x1b[0x님, "+str_파기참가+"\x1b[16x반"+target_kunshu_name+"연합\x1b[0x군에 참가합니까?"), { pk::encode("예"), pk::encode("아니오") }) != 1){ // 예
						s_fa_alliancePlayers[i].second = true;						
						if(is_동맹중)s_fa_unAlly_forces.insertLast(i);
					}						
					else{  // 아니오					
						s_fa_alliance_force.removeAt(s_fa_alliance_force.find(i));		
						int idx_unAlly = s_fa_unAlly_forces.find(i);						
						if(idx_unAlly >= 0)s_fa_unAlly_forces.removeAt(idx_unAlly);
					}						
				}
			}			
			
			// 연합적과 동맹이었다가 파기하는 세력 메세지
			for (int i = 0; i < s_fa_unAlly_forces.length; i++){	
				pk::force@ force = pk::get_force(s_fa_unAlly_forces[i]);
				pk::person@ kunshu = pk::get_person(force.kunshu);
				string kunshu_name0 = pk::decode(pk::get_name(pk::get_person(force.kunshu)));
				string kunshu_name2 = pk::decode(pk::get_name(pk::get_person(force_target.kunshu)));	
				pk::unally(force, force_target.get_id());
				pk::add_relations(force, force_target.get_id(), -100);
				pk::message_box(pk::encode("\x1b[1x"+kunshu_name0+"\x1b[0x"+hanFix.return_chosa(kunshu_name0,3)+" \x1b[1x"+kunshu_name2+"\x1b[0x"+hanFix.return_chosa(kunshu_name2,2)+" 동맹을 \x1b[16x파기\x1b[0x했습니다"), pk::get_person(무장_전령));	
			
			}
			
			auto allyForces_say = s_fa_alliance_force;
			allyForces_say.removeAt(allyForces_say.find(s_fa_leader_force_id));//언급대상 -> 리더 제외		
			string msg_연합군주이름 = getAllianceKunshuNames(allyForces_say, s_fa_target_force_id);
			is_언급할연합세력 = (msg_연합군주이름 != "");
			
			if(is_언급할연합세력){
				pk::background(11);
				pk::play_se(10); //25?
				pk::message_box(pk::encode("맹주 \x1b[1x"+leader_kunshu_name+"\x1b[0x"+hanFix.return_chosa(leader_kunshu_name,2)+" \x1b[16x반"+target_kunshu_name+"연합\x1b[0x을 결성했습니다\n연합군으로 \x1b[1x"+msg_연합군주이름+"\x1b[0x"+hanFix.return_chosa(msg_연합군주이름,2)+" 가세했습니다."));					
			}
			
			// 상황3: 연합적이 플레이어인 경우.
			if(force_target.is_player() and is_언급할연합세력){				
				pk::person@ player_is_target_speaker = getGunshiOrMunkwan(force_target);
				
				pk::background(11);
				pk::play_se(11);
				pk::message_box(pk::encode("\x1b[2x"+target_kunshu_name+"\x1b[0x님, \x1b[16x"+leader_kunshu_name+" 연합군\x1b[0x이 우리 영토로 처들어오고 있습니다"), player_is_target_speaker);
			}
			
			pk::background(-1);
			
		}
		
		string getAllianceKunshuNames(array<int> force_ids, int force_target_id){
			string msg = "";
			for (int i = 0; i < force_ids.length; i++){				
				if(!pk::is_enemy(force_ids[i], force_target_id))continue;
				// util.prnt("is_Enemy ["+pk::get_force(force_ids[i]).kunshu+"] with ["+pk::get_force(force_target_id).kunshu+"]");
				
				string kunshu_name = pk::decode(pk::get_name(pk::get_person(pk::get_force(force_ids[i]).kunshu)));				
				if(i == force_ids.length - 1)msg += kunshu_name;
				else msg += kunshu_name + " ";
				
			}
			return msg;
		}
		
		bool isPort(int building_id){
			for (int i = 건물_항구시작; i <= 건물_항구끝; i++){
				if(i == building_id)return true;
			}
			return false;
		}
		
		bool isGate(int building_id){
			for (int i = 건물_관문시작; i <= 건물_관문끝; i++){
				if(i == building_id)return true;
			}
			return false;
		}
		
		
		
		
		// 목표 건물과 인접한 연합군 도시 탐색해서 원군
		void prepareReinforcement(
			pk::building@ building2, 
			array<AllianceInfo@> &연합군정보, 
			array<int> &출진횟수, 
			array<int> arr_연합군세력, 
			float leaderEff){
					
			pk::city@ city2 = pk::building_to_city(building2);
			array<int> neighbor_cities = neighborMap.인접도시[city2.get_id()]; // city_ids
			for (int i = 0; i < neighbor_cities.length; i++){
				pk::city@ neighbor_city = pk::get_city(neighbor_cities[i]);					
				if(!pk::is_alive(neighbor_city) or !pk::is_valid_force_id(neighbor_city.get_force_id()))continue;
				int reinforce_id = neighbor_city.get_force_id();	
				pk::force@ reinforce = pk::get_force(reinforce_id);				
				// 원군 세력이 유효한가?
				if (!pk::is_alive(reinforce) or !pk::is_valid_force_id(reinforce_id))continue;								
				// 연합군 일원 인가?
				if(!isAllianceForce(reinforce_id, arr_연합군세력))continue;
				
				// util.prnt("Reinforcement kunshu=["+reinforce.kunshu+"] city=["+neighbor_city.get_id()+"] city2=["+city2.get_id()+"] num_go=["+출진횟수[neighbor_city.get_id()]+"]");
				연합군정보.insertLast(AllianceInfo(reinforce_id, neighbor_city.get_id(), city2.get_id(), true));
				출진횟수[neighbor_city.get_id()] += 1; // 출발도시 기준 출진횟수
					
			}
				
		}
		
		bool isAllianceForce(int force_id, array<int> arr_연합군세력){
			for (int i = 0; i < arr_연합군세력.length; i++){	
				
				if(force_id == arr_연합군세력[i])return true;
			}
			return false;
		}
		
		
		
		// 연합군 리더 군사 VS 연합군최대세력 군사
		// 이기면 0, 지면 1
		int DebateForAllyVSAlly(array<int> 연합군세력_distinct, pk::person@ target_kunshu, pk::person@ promoter0, pk::person@ counterpartner)
		{
			int result = 1;
			
			// 연맹주가 플레이어면 설전
			if(promoter0.is_player()){
				s_pvsp_target_kunshu_id = target_kunshu.get_id();
				s_pvsp_promoter0_id = promoter0.get_id();
				s_pvsp_counterpartner_id = counterpartner.get_id();
				
				pk::scene(pk::scene_t(Scene_PromoterVSPromoter));					
				result = s_pvsp_result;
				
			}
			else{
				
				// if(!발생바람값적용)return 0;
				
				result = WishDecSumForDebate(연합군세력_distinct, target_kunshu);
				
			}
			
			return result;
			
		}
		
		/// 연합세력배열 얻기
		array<int> get_연합군세력배열(array<AllianceInfo@> 연합군정보){
			array<int> arr_연합군세력;
			for (int i = 0; i < 연합군정보.length; i++){
				arr_연합군세력.insertLast(연합군정보[i].연합군세력);
			}
			return arr_연합군세력;
		}
		
		
		int WishDecSumForDebate(array<int> 연합군세력_distinct, pk::person@ target_kunshu){
			
			pk::force@ force_target = pk::get_force(target_kunshu.get_force_id());
			
			// 연합군의 공통적에 대한 바람수 합 확률
			
			array<int> force_ids_sorted = util.bubble_sort_desc(연합군세력_distinct, 연합군세력_distinct.length);		
			
			
			float likeDec = 0.f;
			float disLikeDec = 0.f;
			
			// int tmp = -1; // For Distinct
			for (int i = 0; i < force_ids_sorted.length; i++){				
				// if(force_ids_sorted[i] == -1)break;
				// 중복 거르기
				// if(tmp == force_ids_sorted[i])continue;
				// tmp = force_ids_sorted[i];
				int force_id_alliance = force_ids_sorted[i];;
				
				float valJudge = floor(세력대판단결과[force_id_alliance][force_target.get_id()] * 100) / 100.f;
				valJudge = pk::get_force(force_id_alliance).relations[force_target.get_id()] <= 0 ? -1 : valJudge; // 우호도가 0이면. 연합적과 친해질 기미가 아예없는것으로 판단.
				
				// pk::printf(pk::encode("kunshu=["+pk::get_force(force_id_alliance).kunshu+"] valJudge=["+valJudge+"] \n"));
				
				if(valJudge < 0){ disLikeDec += -valJudge; }
				else { likeDec += valJudge; }
				
			}
			float 합_like = likeDec + disLikeDec == 0 ? 1 : likeDec + disLikeDec;
			float sumWishDec = disLikeDec / 합_like;
			
			
			bool isSuccess = getRandom((sumWishDec * 100) + 추가연합성공률, 11);
			
			// pk::printf(pk::encode("WishDecSumForDebate isSuccess=["+isSuccess+"] sumWishDecPerc=["+(sumWishDec * 100)+"] \n"));
			
			return isSuccess ? 0 : 1;
			
			
		}
		
		
		int s_pvsp_target_kunshu_id = -1;
		int s_pvsp_promoter0_id = -1;
		int s_pvsp_counterpartner_id = -1;
		int s_pvsp_result = 1;
		
		void Scene_PromoterVSPromoter()
		{
			
			pk::fade(0);
			pk::sleep();
			pk::background(53);
			pk::fade(255);
						
			pk::person@ promoter0 = pk::get_person(s_pvsp_promoter0_id);
			pk::person@ promoter1 = pk::get_person(s_pvsp_counterpartner_id);
			pk::person@ target_kunshu = pk::get_person(s_pvsp_target_kunshu_id);
			
			string target_kunshu_name = pk::decode(pk::get_name(target_kunshu));
			string promoter1_talk1 = "지금 천하의 대세는 \x1b[2x"+target_kunshu_name+"\x1b[0x"+hanFix.return_chosa(target_kunshu_name,5)+" 넘어갔소. 한나라의 명운이 다하고, 민심도 기울어져 있거늘 어찌 천하의 흐름을 거스르고 난을 일으킨단 말이오?";
			pk::message_box(pk::encode(promoter1_talk1), promoter1);	
			pk::message_box(pk::encode("닥쳐라!"), promoter0);
			s_pvsp_result = pk::debate(promoter0, promoter1, true, false).first;
			
			pk::background(-1);
			
		}
		
		
		
		
		bool is_beingAtWar(pk::building@ building)
		{
			
			array<pk::point> arr = pk::range(building.get_pos(), 1, 거점전쟁판단_범위);
			for (int j = 0; j < arr.length; j++)
			{
				auto obj = pk::get_hex_object(arr[j]);
				if(obj is null or obj.get_force_id() < 0)continue;
				
				if (pk::is_enemy(building, obj))return true;
				
				
			}
			// util.prnt("isAtWar building=["+building.get_id()+"] [false]");
			return false;
		}
		
		
		array<int> isAtWarEnemies(pk::building@ building)
		{
			int 적들아이디인덱스 = 0;
			array<int> 적들아이디((pk::get_unit_list()).count, -1); // 인덱스0 에는 갯수값 저장
			array<pk::point> arr = pk::range(building.get_pos(), 1, 거점전쟁판단_범위);
			for (int j = 0; j < arr.length; j++)
			{
				pk::unit@ dst = pk::get_unit(arr[j]);					
				if (dst is null)continue;

				if (pk::is_enemy(building, dst)){
					
					적들아이디[적들아이디인덱스+=1] = dst.get_id();
					
				}
				
			}
			적들아이디[0] = 적들아이디인덱스;
			return 적들아이디;
		}
		
		
		
		
		int GetTroops(pk::person@ mem0)
		{
			int maxCommnd = pk::get_rank(mem0.rank).command;	
			pk::force@ force= pk::get_force(mem0.force_id);

			if(force.kokugou == 국호_황건)
			{
				maxCommnd = 15000;
			}
			else if(mem0.mibun == 신분_군주)
			{
				switch(force.title)
				{
					case 작위_황제:maxCommnd=15000;break;
					case 작위_왕:
					case 작위_공:maxCommnd=14000;break;
					case 작위_대사마:
					case 작위_대장군:maxCommnd=13000;break;
					case 작위_오관중랑장:
					case 작위_우림중랑장:maxCommnd=12000;break;
					case 작위_주목:
					case 작위_주자사:maxCommnd=11000;break;
					default: maxCommnd=10000; break;
				}
			}
			
			if(pk::has_tech(force, 기교_군제개혁))
				maxCommnd += 3000;
			
			return maxCommnd;
		}
		
		
		
		void CreateAUnit(pk::person@ mem0, pk::building@ base, pk::building@ base2, float costPercentage, bool isAtWar, int idxNumUnit, bool isReinforcement, array<int> 적들아이디 )
		{
						
			if(!pk::is_valid_person_id(mem0.get_id()) or !pk::is_alive(mem0))return;
			
			int rank_troops = pk::get_rank(mem0.rank).command;	
			rank_troops = GetTroops(mem0);
			// int distance = pk::get_distance(base.get_pos(), base2.get_pos()); /// 칸 수 
			// int 순_distance = ceil(distance / 기준_칸이동력); /// 걸리는 시간. x순
			
			// int building_distance = pk::get_building_distance(base.get_id(), base2.get_id(), base.get_force_id());
			// int city_distance = pk::get_city_distance(pk::building_to_city(base).get_id(), pk::building_to_city(base2).get_id());
			// int point_distance = pk::get_distance(base.get_pos(), base2.get_pos()); // 평균이동소모 5 25칸이면 소모 이동력 75 이동력 25인 기마병이 도착하는데에 3순이 걸린다.
			// util.prnt("base=["+base.get_id()+"] base2=["+base2.get_id()+"] get_distance=["+point_distance+"] get_city_distance=["+city_distance+"] get_building_distance=["+distance+"] distance_x10=["+순_distance+"] ");			
			
			int troops = rank_troops;
			
			
			
			
			
			
			int gold = 부대생성_금;
			// int food = int((troops / 10.0) * 순_distance * 2.0);
			int food = int(troops * 부대생성_병량비율);
						
			// 병력 조정
			bool isLackingTroops = false;
			bool isLackingGold = false;
			bool isLackingFood = false;			
			
			if( pk::get_troops(base) < troops ){ 
				isLackingTroops = true;
				if(!항상최대병력출진)troops = 최소출진병력수;
			}			
			int cost_gold = int(gold * costPercentage);
			int cost_food = int(food * costPercentage);				
			if( pk::get_gold(base) <= gold ){isLackingGold = true;}
			if( pk::get_food(base) <= food ){isLackingFood = true;}
			
			if(isLackingFood)return;
			if(출진_도시병력내 and isLackingTroops)return;
			
			// 생성될 부대 포지션이 문제 있으면 부대를 생성하지 않는다.		
			pk::point emptyPos = getEmptyPos(base);
			if(!pk::is_valid_pos(emptyPos))return;
			
			// 있는 병기 중에 선택
			int best_weapon_id = getBestWeaponId(base, mem0);
			int cost_weapon = int(troops * costPercentage);				
			pk::unit@ unit = pk::create_unit(base, mem0, null, null, troops, best_weapon_id, 병기_주가, gold, food, emptyPos);
			
			
			// 부대 생성이 실패한 경우 무장 삭제
			if (!pk::is_alive(unit)){ pk::remove(unit);return; }

			// 기력 설정(pk::create_unit 함수의 첫 번째 파라미터로 결정했다면 필요없음.)
			//unit.energy = 100;

			// int enemy_leader_id = -1; // for Debug
			
			// if(isReinforcement){
				// pk::set_order(unit, 부대임무_물림, base2.get_pos());				
			// }
			// else{				
				// if(isAtWar){
					// pk::set_order(unit, 부대임무_물림, base2.get_pos());
				// }
				// else{
					// pk::set_order(unit, 부대임무_공격, base2.get_pos());
				// }				
			// }
			pk::set_order(unit, 부대임무_정복, base2.get_pos());
			
			// 도시 물자 차감			
			if(!isLackingTroops)pk::add_troops(base, -int(unit.troops));
			if(!isLackingGold)pk::add_gold(base, -cost_gold);
			if(!isLackingFood)pk::add_food(base, -cost_food);
			int weapon_count = isSiegeWeapon(best_weapon_id) ? 1 : cost_weapon;
			pk::add_weapon_amount(base, best_weapon_id, -weapon_count);
			
			// util.prnt("leader=["+unit.leader+"] force_kunshu=["+pk::get_force(unit.get_force_id()).kunshu+"] base0=["+base.get_id()+"] base2=["+base2.get_id()+"] troops=["+unit.troops+"] order=["+unit.order+"] isReinforcement=["+isReinforcement+"] ");
			
			
		}
		
		pk::point getEmptyPos(pk::building@ building_)
		{
			auto arr = pk::range(building_.get_pos(), 1, 3);
			for (int i = 0; i < arr.length; i++)
			{
				pk::hex@ hex = pk::get_hex(arr[i]);
				int terrain_id = hex.terrain;
				
				//pk::printf(pk::encode("terrain id=["+terrain_id+"] is_enabled_terrain=["+pk::is_enabled_terrain(terrain_id)+"] is_valid_terrain_id=["+pk::is_valid_terrain_id(terrain_id)+"] is_water_terrain=["+pk::is_water_terrain(terrain_id)+"] \n"));
				
				if (!hex.has_building 
					and !hex.has_unit 
					and pk::is_valid_terrain_id(terrain_id) 
					and pk::is_enabled_terrain(terrain_id)
					and terrain_id != 지형_산
					and terrain_id != 지형_내
				)return arr[i];
				
			}
			return -1;
		}
		
		
		int getBestWeaponId(pk::building@ base, pk::person@ person)
		{
			pk::force@ force = pk::get_force(person.get_force_id());
			pk::city@ city = pk::building_to_city(base);			
			
			// 최고 적성
			int best_tekisei = 적성_C;
			int best_weapon_id = 병기_검;
			for (int i = 0; i < 병기_끝; i++)
			{
				if(출진_도시병력내 and pk::get_weapon_amount(base, i) <= 0)continue;
				if(isSeaWeapon(i))continue;				
				if(i == 병기_목수 and !pk::has_tech(force, 기교_목수개발))continue;
				
				int tekisei = i == 병기_검 ? 0 : person.tekisei[pk::equipment_id_to_heishu(i)];
				if(best_tekisei < tekisei)best_weapon_id = i;
				
				// pk::printf(pk::encode(pk::format("getBestWeaponId i={} person.tekisei={} best_tekisei={} \n",i, tekisei, best_tekisei )));
				
				best_tekisei = pk::max(tekisei, best_tekisei);
				
			}
			
			return best_weapon_id;
		}
		
		bool isSeaWeapon(int weapon_id){return (weapon_id >= 병기_주가);}
		
		bool isSiegeWeapon(int weapon) { return (weapon >= 병기_충차 && weapon <= 병기_목수); }
		
		float getPersonEffect(pk::person@ person_)
		{
			
			float person_effect = 0.1f;
			
			if(pk::is_alive(person_)){
				person_effect = (person_.stat[무장능력_통솔]
					 + person_.stat[무장능력_무력]
					 + person_.stat[무장능력_지력]
					 + person_.stat[무장능력_정치]
					 + person_.stat[무장능력_매력]
				) / float(무장능력_끝 * 100.f);
			}
			
			return person_effect;
			
		}
		
		float getDistinctEffect(int stat, float divisor, int8 diff)
		{
			if(stat >= divisor)return 0.9f;		
			//return (stat / divisor) * (stat/ divisor) * (stat/ divisor);
			
			float stat1 = (stat / divisor);
			
			while (diff > 0){
				diff -= 1;
				float val = stat1 * (stat / divisor);
				stat1 = floor(val * 100) / 100.0f;	// 버림			
			}
			
			return stat1;
			
		}
		
		
		// 속성 값 세팅
		
		void setForceAttributes()
		{			
			
			
			// 세력당 저장할 필요한 값은 여기서 정의한다.
			// 하나 늘어날 때마다 '속성값_끝' +1
			
			
			pk::list<pk::force@> force_list = pk::get_force_list(false);
			
			
			for (int i = 0; i < force_list.count; i++){
				if(isIminzoku(force_list[i]))continue;
				
				int force_id = force_list[i].get_id();				
				
				setDistrictAttrSum(force_list[i]);
				
				setForceTroopsRanking(force_id);
				
				// 외교 대상 찾기
				setNegotiationTarget(force_list[i]);
				
			}
			
			
			setTop10MujangAttrSum();
			
		}
		
		void setForceTroopsRanking(int force_id)
		{
							
			// 세력 순위 정하기
			for (int j = 0; j < 47; j++){
				double 연합적세력병력 = rank_세력병사[j] == -1 ? 0 : 세력부가속성[rank_세력병사[j]][속성_병력];
				
				if( 연합적세력병력 < 세력부가속성[force_id][속성_병력]){	
				
					int8 tmpForceId = -1;
					int8 tmp2ForceId = -1;
					
					for (int l = j; l < 47; l++){		
						if(l > j){
							if(tmpForceId == -1)break;
							tmp2ForceId = rank_세력병사[l];
							rank_세력병사[l] = tmpForceId;
							tmpForceId = tmp2ForceId;
						}	
						else {
							tmpForceId = rank_세력병사[l];
							rank_세력병사[j] = force_id;								
						}							
					}						
					break;
				}					
				
			}
			
		}
		
		// 주의: 이웃한 나라가 없으면 외교하지 않는다.
		void setNegotiationTarget(pk::force@ force0)
		{
			int force0_id = force0.get_id();
			int strategic = pk::get_person(force0.kunshu).strategic_tendency;
			
			int depth = 0;
			if(strategic == 전략경향_중화통일){
				depth = 3;
			}
			else if(strategic == 전략경향_주통일){ 
				depth = 1;
			}
			else if(strategic == 전략경향_현상유지){	
				depth = 0;
			}
			else { // 지방
				depth = 2;
			}
			
			
			FindNegoTarget(force0_id, -1, force0, depth);
			
		}
		
		
		void FindNegoTarget(int root, int force0_id_prev, pk::force@ force0, int depth)
		{
			if(depth < 1)return;
			
			int force0_id = force0.get_id();
			if(force0_id_prev != force0_id)depth -= 1;
			
			pk::list<pk::force@> force_list = pk::get_force_list(false);
			for (int i = 0; i < force_list.count; i++){				
				
				if(isIminzoku(force_list[i]))continue;					
				int force1_id = force_list[i].get_id();	
				if(force1_id == root)continue;	
				if(force1_id == force0_id)continue;	
				// if(세력외교대상[root][force1_id] == 1)continue;
				
				
				if(pk::is_neighbor_force(force0, force_list[i]))
				{
					세력외교대상[root][force1_id] = 1;	
					
					// 값이 클 수록 멀게
					세력대세력거리[root][force1_id] = pk::min(3 - depth, 세력대세력거리[root][force1_id]); // depth = 0, 1, 2
									
					// util.prnt("FindNegoTarget root=["+pk::get_force(root).kunshu+"] force0_id=["+pk::get_force(force0_id).kunshu+"] force1_id=["+pk::get_force(force1_id).kunshu+"] depth=["+depth+"] distance=["+(3 - depth)+"]");
					
					FindNegoTarget(root, force0_id, pk::get_force(force1_id), depth);
					
				}
			}
			
		}
		
		// 세력 하나 군단들 속성별 합
		void setDistrictAttrSum(pk::force@ force)
		{			
			int force_id = force.get_id();	
			
			pk::list<pk::district@> force_district_list = pk::get_district_list(force);
			
			//초기화
			세력부가속성[force_id][속성_도시수]	= 0;
			세력부가속성[force_id][속성_무장수]	= 0;
			세력부가속성[force_id][속성_병력]	= 0;
			
			for (int i = 0; i < force_district_list.count; i++)
			{				
				auto district = force_district_list[i];
				if (!pk::is_alive(district))continue;
				
				세력부가속성[force_id][속성_도시수] += district.query_value(군단속성_도시수);
				세력부가속성[force_id][속성_무장수] += district.query_value(군단속성_무장수);
				세력부가속성[force_id][속성_병력] 	+= district.query_value(군단속성_병력);
			}
			
				
		}
		
		void setTop10MujangAttrSum()
		{
			
			// 세력별 탑10 무장수 세기
			array<int> 세력탑10(세력_끝, 0);
			pk::list<pk::person@> mujang_list = pk::get_person_list(pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반));
			
			
			// 무장 통무 내림차순
			mujang_list.sort(function(a, b)
			{
				int sum_a = a.stat[무장능력_통솔] + a.stat[무장능력_무력];
				int sum_b = b.stat[무장능력_통솔] + b.stat[무장능력_무력];
				return sum_a > sum_b;
			});
			
			// Top 10 무장 통솔 + 무력
			for (int i = 0; i < mujang_list.count; i++)
			{
				
				auto person = mujang_list[i];
				int force_id = person.get_force_id();
				//pk::printf(pk::encode(pk::format("force_id = {}\n",force_id)));
				if(force_id == -1)continue;
				if(세력탑10[force_id] > 9)continue;
				
				세력부가속성[force_id][속성_탑10] 	+= person.stat[무장능력_통솔] + person.stat[무장능력_무력];
				세력탑10[force_id] += 1;
					
			}
			
		}
		
		void setIsAtWar()
		{			
		
			// 부대
			auto list = pk::list_to_array(pk::get_unit_list());
			for (int l = 0; l < list.length; l++)
			{
				pk::unit@ unit0 = list[l];
				set_경계여부_도시주변(unit0);
				// set_전쟁여부_부대주변(unit0);
			}
			
		}
		
		void setForceGoldFood(){
			array<pk::building@> arr = pk::list_to_array(pk::get_building_list());
			for (int i = 0; i < arr.length; i++)
			{
				pk::building@ building0 = arr[i];
				int force0_id = building0.get_force_id();
				if(!pk::is_alive(building0) or !pk::is_valid_force_id(force0_id))return;
				세력부가속성[force0_id][속성_금] += pk::get_gold(building0);
				세력부가속성[force0_id][속성_병량] += pk::get_food(building0);	
			}			
			is_세력금병량검색 = true;
		}

		void set_경계여부_도시주변(pk::unit@ unit0){
			pk::city@ city = pk::get_city(pk::get_city_id(unit0.pos));
			// util.prnt("unit_is_enemycity leader=["+unit0.leader+"] on_the_city=["+city.get_id()+"] is_warning=["+pk::is_enemy(city, unit0)+"] ");
			if(pk::is_enemy(city, unit0)){
				도시경계여부[city.get_id()] = 1;
				
				세력대전쟁여부[city.get_force_id()][unit0.get_force_id()] = 1;
				세력대전쟁여부[unit0.get_force_id()][city.get_force_id()] = 1;
				전쟁중여부[city.get_force_id()] = 1;
				전쟁중여부[unit0.get_force_id()] = 1;
				건물전쟁여부[pk::city_to_building(city).get_id()] = 1;
				
				
			}
		}

		
		
		bool isIminzoku(pk::force@ force)
		{
			if(
				force.kunshu == 무장_오환두목 
				or force.kunshu == 무장_강두목
				or force.kunshu == 무장_산월두목
				or force.kunshu == 무장_남만두목 
				or force.kunshu == 무장_적장
			)return true;
			return false;
		}
		float BooleanToFloat(pk::bool val)
		{
			if(val){
				return 1.f;
			}
			else{
				return 0.f;
			}
			
		}
		bool intToBoolean(int val){
			return (val == 1);
		}
		
	} // end - Main
	
	/*
	array<array<pk::person@>> 출진_무장;
			array<int> 출진_도시;
			array<int> 출진_목표;
			array<bool> 출진_전쟁여부;
			array<int> 출진_부대수;
	
	*/

	/// 부대출진정보
	class UnitInfo{
		
		UnitInfo(){}		
		UnitInfo(array<int> 출진_무장, int 출진_도시, int 출진_목표, bool 출진_전쟁여부, int 출진_부대수, bool isReinforcement) { 			
			this.출진_무장 = 출진_무장;
			this.출진_도시 = 출진_도시;
			this.출진_목표 = 출진_목표;
			this.출진_전쟁여부 = 출진_전쟁여부;
			this.출진_부대수 = 출진_부대수;
			this.isReinforcement = isReinforcement;
		}		
		/// property
		array<int> 출진_무장;
		int 출진_도시;
		int 출진_목표;
		bool 출진_전쟁여부;
		int 출진_부대수;
		bool isReinforcement;
	}
	
	/// 연합군정보
	class AllianceInfo{
		
		AllianceInfo(){}		
		AllianceInfo(int 연합군세력, int 출발도시, int 도착도시, bool isReinforcement) { 						
			this.연합군세력 = 연합군세력;
			this.출발도시 = 출발도시;
			this.도착도시 = 도착도시;
			this.isReinforcement = isReinforcement;
		}		
		/// property
		int 연합군세력;
		int 출발도시;
		int 도착도시;
		bool isReinforcement;
	}
	
	
	
	
	
	
		
	/*
	@만든이: 유령기
	@설명: 완성형 한글의 받침에 따라서 조사처리
	*/
	
	
	
	/**
		조사 타입
	*/
	enum 한글_조사Id {
		조사_은는	 = 0,
		조사_을를	 = 1,
		조사_이가	 = 2,
		조사_과와	 = 3,
		조사_이 = 4,
		조사_으로로  = 5
	}
		
	class  HanFix
	{
		
		HanFix()
		{
			
		}
		


		array<array<string>> 조사_배열 = { { "은", "는" }, { "을", "를" }, { "이", "가"}, {"과", "와"}, {"이",""}, {"으로", "로"} };	

		/**
			단어에 맞는 조사를 리턴합니다.
			
			@param s 조사를 붙일 단어 
			@param type 조사의 종류 한글_조사Id에 따라 분류합니다.
			@return 조사
		*/
		string return_chosa(string s, int type)
		{
			if( type < 0 || type > int(조사_배열.length()) ) return s;
			
			if(isJongSung(s))
				return (조사_배열[type][0]);
			else
				return (조사_배열[type][1]);
		}

		/**
			단어에 조사를 붙여서 리턴합니다. 
			
			@param s 조사를 붙일 단어 
			@param type 조사의 종류 한글_조사Id에 따라 분류합니다.
			@return 조사를 붙인 단어 
		*/
		string add_chosa(string s, int type)
		{
			
			if( type < 0 || type > int(조사_배열.length()) ) return s;
			
			if(isJongSung(s))
				return (s + 조사_배열[type][0]);
			else
				return (s + 조사_배열[type][1]);
			
		}

		/**
			단어(색상 지정)에 조사를 붙여서 리턴합니다. 
			
			@param s 조사를 붙일 단어 
			@param type 조사의 종류 한글_조사Id에 따라 분류합니다.
			@param color 색상 번호 
			@return 조사를 붙인 단어 
		*/
		string add_chosa_color(string s, int type, int color)
		{
			if( type < 0 || type > int(조사_배열.length()) ) return s;

			if(isJongSung(s))
				return (pk::format("\x1b[{}x{}\x1b[0x{}", color, s, 조사_배열[type][0]));
			else
				return (pk::format("\x1b[{}x{}\x1b[0x{}", color, s, 조사_배열[type][1]));
		}

		/**
			주어진 단어에 받침(종성)이 있는지를 검사한다.
			
			@param s 조사를 붙일 단어
			@return 받침여부
		*/

		bool isJongSung(string s)
		{			
			array<string> dictDoubleWord = {
				"가", "갸", "거", "겨", "고", "교", "구", "규", "그", "기", "개", "걔", "게", "계", "과", "괘", "궈", "궤", "괴", "귀", "긔",
				"까", "꺄", "꺼", "껴", "꼬", "꾜", "꾸", "뀨", "끄", "끼", "깨", "ㅤㄲㅒㅤ", "께", "꼐", "꽈", "꽤", "꿔", "꿰", "꾀", "뀌", "ㅤㄲㅢㅤ",
				"나", "냐", "너", "녀", "노", "뇨", "누", "뉴", "느", "니", "내", "ㅤㄴㅒㅤ", "네", "녜", "놔", "ㅤㄴㅙㅤ", "눠", "눼", "뇌", "뉘", "늬",
				"다", "댜", "더", "뎌", "도", "됴", "두", "듀", "드", "디", "대", "ㅤㄷㅒㅤ", "데", "뎨", "돠", "돼", "둬", "뒈", "되", "뒤", "듸",
				"따", "ㅤㄸㅑㅤ", "떠", "뗘", "또", "ㅤㄸㅛㅤ", "뚜", "ㅤㄸㅠㅤ", "뜨", "띠", "때", "ㅤㄸㅒㅤ", "떼", "ㅤㄸㅖㅤ", "똬", "뙈", "ㅤㄸㅝㅤ", "뛔", "뙤", "뛰", "띄",
				"라", "랴", "러", "려", "로", "료", "루", "류", "르", "리", "래", "ㅤㄹㅒㅤ", "레", "례", "롸", "ㅤㄹㅙㅤ", "뤄", "뤠", "뢰", "뤼", "ㅤㄹㅢㅤ",
				"마", "먀", "머", "며", "모", "묘", "무", "뮤", "므", "미", "매", "ㅤㅁㅒㅤ", "메", "몌", "뫄", "ㅤㅁㅙㅤ", "뭐", "뭬", "뫼", "뮈", "ㅤㅁㅢㅤ",
				"바", "뱌", "버", "벼", "보", "뵤", "부", "뷰", "브", "비", "배", "ㅤㅂㅒㅤ", "베", "볘", "봐", "봬", "붜", "붸", "뵈", "뷔", "ㅤㅂㅢㅤ",
				"빠", "뺘", "뻐", "뼈", "뽀", "뾰", "뿌", "쀼", "쁘", "삐", "빼", "ㅤㅃㅒㅤ", "뻬", "ㅤㅃㅖㅤ", "ㅤㅃㅘㅤ", "ㅤㅃㅙㅤ", "ㅤㅃㅝㅤ", "ㅤㅃㅞㅤ", "뾔", "ㅤㅃㅟㅤ", "ㅤㅃㅢㅤ",
				"사", "샤", "서", "셔", "소", "쇼", "수", "슈", "스", "시", "새", "섀", "세", "셰", "솨", "쇄", "숴", "쉐", "쇠", "쉬", "ㅤㅅㅢㅤ",
				"싸", "ㅤㅆㅑㅤ", "써", "ㅤㅆㅕㅤ", "쏘", "쑈", "쑤", "ㅤㅆㅠㅤ", "쓰", "씨", "쌔", "ㅤㅆㅒㅤ", "쎄", "ㅤㅆㅖㅤ", "쏴", "쐐", "쒀", "쒜", "쐬", "쒸", "씌",
				"아", "야", "어", "여", "오", "요", "우", "유", "으", "이", "애", "얘", "에", "예", "와", "왜", "워", "웨", "외", "위", "의",
				"자", "쟈", "저", "져", "조", "죠", "주", "쥬", "즈", "지", "재", "쟤", "제", "졔", "좌", "좨", "줘", "줴", "죄", "쥐", "ㅤㅈㅢㅤ",
				"짜", "쨔", "쩌", "쪄", "쪼", "ㅤㅉㅛㅤ", "쭈", "쮸", "쯔", "찌", "째", "ㅤㅉㅒㅤ", "쩨", "ㅤㅉㅖㅤ", "쫘", "쫴", "쭤", "ㅤㅉㅞㅤ", "쬐", "쮜", "ㅤㅉㅢㅤ",
				"차", "챠", "처", "쳐", "초", "쵸", "추", "츄", "츠", "치", "채", "ㅤㅊㅒㅤ", "체", "쳬", "촤", "ㅤㅊㅙㅤ", "춰", "췌", "최", "취", "ㅤㅊㅢㅤ",
				"카", "캬", "커", "켜", "코", "쿄", "쿠", "큐", "크", "키", "캐", "ㅤㅋㅒㅤ", "케", "켸", "콰", "쾌", "쿼", "퀘", "쾨", "퀴", "ㅤㅋㅢㅤ",
				"타", "탸", "터", "텨", "토", "툐", "투", "튜", "트", "티", "태", "ㅤㅌㅒㅤ", "테", "톄", "톼", "퇘", "퉈", "퉤", "퇴", "튀", "틔",
				"파", "퍄", "퍼", "펴", "포", "표", "푸", "퓨", "프", "피", "패", "ㅤㅍㅒㅤ", "페", "폐", "퐈", "ㅤㅍㅙㅤ", "풔", "ㅤㅍㅞㅤ", "푀", "퓌", "ㅤㅍㅢㅤ",
			"하", "햐", "허", "혀", "호", "효", "후", "휴", "흐", "히", "해", "ㅤㅎㅒㅤ", "헤", "혜", "화", "홰", "훠", "훼", "회", "휘", "희"};
			
			if( s.length() < 2 ) return false;
			
			string last = s.substr(s.length()-2,2);
			
			for(uint i=0; i<dictDoubleWord.length(); i++ )
			{
				if( last == dictDoubleWord[i] )
					return false;
			}
			
			return true;
		}
			
		
	} // end - class
	
	
	
	
	class  Util
	{
		
		
		Util()
		{
			
		}
		
		 
		void prnt(string str)
		{
			pk::printf(pk::encode(str + " \n"));			
		}
		
		array<int> bubble_sort_asce(array<int> list, int n)
		{
		  int c, d, t;
		 
		  for (c = 0 ; c < n - 1; c++)
		  {
			for (d = 0 ; d < n - c - 1; d++)
			{
			  if (list[d] > list[d+1])
			  {
				/* Swapping */
		 
				t         = list[d];
				list[d]   = list[d+1];
				list[d+1] = t;
			  }
			}
		  }
		  return list;
		}
		
		array<int> bubble_sort_desc(array<int> list, int n)
		{
		  int c, d, t;
		 
		  for (c = 0 ; c < n - 1; c++)
		  {
			for (d = 0 ; d < n - c - 1; d++)
			{
			  if (list[d] < list[d+1])
			  {
				/* Swapping */
		 
				t         = list[d];
				list[d]   = list[d+1];
				list[d+1] = t;
			  }
			}
		  }
		  return list;
		}
		
		
	
	}
	
	
	
	
	
	class  NeighborMap
	{		
		array<array<int>> 인접도시(도시_끝, array<int>(0, -1));
				
		NeighborMap(){
			init();
		}
		
		void init(){
			mapNeighborCity();
		}
		
		bool isNeighborCity(int building0_id, int building1_id)
		{
			array<int> neighbors = 인접도시[building0_id];
			for(int i=0; i < neighbors.length; i++ ){
				if(neighbors[i] == building1_id)return true;
			}
			return false;
		}
		
		void mapNeighborCity()
		{
			// 관,항을 거쳐 갈 수 있는 가장 인접한 도시
			
			인접도시[도시_양평 ] = {도시_북평, 도시_북해, 도시_하비, 도시_평원};
			인접도시[도시_북평 ] = {도시_계, 도시_남피, 도시_양평};
			인접도시[도시_계  ] = {도시_북평, 도시_남피, 도시_진양, 도시_평원, 도시_업};
			인접도시[도시_남피 ] = {도시_북평, 도시_계, 도시_평원, 도시_진양, 도시_업};
			인접도시[도시_평원 ] = {도시_남피, 도시_업, 도시_계, 도시_진양, 도시_복양, 도시_북해, 도시_낙양, 도시_진류, 도시_양평, 도시_장안};
			인접도시[도시_진양 ] = {도시_계, 도시_업, 도시_평원, 도시_장안, 도시_낙양, 도시_남피};
			인접도시[도시_업  ] = {도시_평원, 도시_계, 도시_진양, 도시_남피, 도시_복양, 도시_진류, 도시_낙양, 도시_장안};
			인접도시[도시_북해 ] = {도시_하비, 도시_양평, 도시_평원, 도시_복양};
			인접도시[도시_하비 ] = {도시_소패, 도시_양평, 도시_북해, 도시_수춘, 도시_건업, 도시_오, 도시_회계};
			인접도시[도시_소패 ] = {도시_하비, 도시_복양, 도시_진류, 도시_수춘, 도시_허창, 도시_여남};
			인접도시[도시_수춘 ] = {도시_허창, 도시_복양, 도시_하비, 도시_소패, 도시_여남, 도시_강하, 도시_여강, 도시_진류, 도시_건업};
			인접도시[도시_복양 ] = {도시_소패, 도시_진류, 도시_북해, 도시_허창, 도시_수춘, 도시_여남, 도시_업, 도시_평원};
			인접도시[도시_진류 ] = {도시_허창, 도시_복양, 도시_소패, 도시_완, 도시_수춘, 도시_여남, 도시_낙양, 도시_평원, 도시_업};
			인접도시[도시_허창 ] = {도시_낙양, 도시_진류, 도시_완, 도시_여남, 도시_신야, 도시_수춘, 도시_복양, 도시_소패, 도시_여강};
			인접도시[도시_여남 ] = {도시_허창, 도시_신야, 도시_수춘, 도시_강하, 도시_진류, 도시_복양, 도시_소패, 도시_여강};
			인접도시[도시_낙양 ] = {도시_장안, 도시_완, 도시_진류, 도시_허창, 도시_진양, 도시_업, 도시_평원};
			인접도시[도시_완  ] = {도시_낙양, 도시_장안, 도시_허창, 도시_진류, 도시_신야, 도시_상용, 도시_양양};
			인접도시[도시_장안 ] = {도시_안정, 도시_낙양, 도시_완, 도시_한중, 도시_천수, 도시_진양, 도시_업, 도시_평원};
			인접도시[도시_상용 ] = {도시_한중, 도시_완, 도시_신야, 도시_양양};
			인접도시[도시_안정 ] = {도시_무위, 도시_천수, 도시_장안};
			인접도시[도시_천수 ] = {도시_무위, 도시_안정, 도시_한중, 도시_자동, 도시_장안};
			인접도시[도시_무위 ] = {도시_안정, 도시_천수};
			인접도시[도시_건업 ] = {도시_하비, 도시_수춘, 도시_여강, 도시_오, 도시_회계, 도시_시상};
			인접도시[도시_오  ] = {도시_회계, 도시_건업, 도시_하비, 도시_시상};
			인접도시[도시_회계 ] = {도시_오, 도시_건업, 도시_시상, 도시_하비};
			인접도시[도시_여강 ] = {도시_수춘, 도시_건업, 도시_강하, 도시_여남, 도시_시상, 도시_허창};
			인접도시[도시_시상 ] = {도시_강하, 도시_여강, 도시_건업, 도시_장사, 도시_강릉, 도시_양양, 도시_신야, 도시_무릉, 도시_회계, 도시_오};
			인접도시[도시_강하 ] = {도시_신야, 도시_수춘, 도시_여남, 도시_여강, 도시_시상, 도시_양양, 도시_강릉, 도시_무릉, 도시_장사};
			인접도시[도시_신야 ] = {도시_완, 도시_상용, 도시_여남, 도시_허창, 도시_양양, 도시_강릉, 도시_강하, 도시_시상, 도시_장사};
			인접도시[도시_양양 ] = {도시_강릉, 도시_신야, 도시_상용, 도시_완, 도시_강하, 도시_시상, 도시_영안, 도시_장사};
			인접도시[도시_강릉 ] = {도시_양양, 도시_영안, 도시_무릉, 도시_신야, 도시_장사, 도시_시상, 도시_강하};
			인접도시[도시_장사 ] = {도시_계양, 도시_시상, 도시_무릉, 도시_영릉, 도시_강릉, 도시_강하, 도시_양양, 도시_신야};
			인접도시[도시_무릉 ] = {도시_강릉, 도시_영릉, 도시_장사, 도시_계양, 도시_영안, 도시_강하, 도시_시상};
			인접도시[도시_계양 ] = {도시_장사, 도시_영릉, 도시_무릉};
			인접도시[도시_영릉 ] = {도시_무릉, 도시_계양, 도시_장사};
			인접도시[도시_영안 ] = {도시_강주, 도시_한중, 도시_강릉, 도시_무릉, 도시_양양};
			인접도시[도시_한중 ] = {도시_자동, 도시_상용, 도시_천수, 도시_장안, 도시_영안, 도시_성도, 도시_강주};
			인접도시[도시_자동 ] = {도시_한중, 도시_성도, 도시_강주, 도시_천수};
			인접도시[도시_강주 ] = {도시_성도, 도시_자동, 도시_건녕, 도시_영안, 도시_한중, 도시_운남};
			인접도시[도시_성도 ] = {도시_자동, 도시_강주, 도시_건녕, 도시_운남, 도시_한중};
			인접도시[도시_건녕 ] = {도시_성도, 도시_강주, 도시_운남};
			인접도시[도시_운남 ] = {도시_건녕, 도시_성도, 도시_강주};
			
		}
		
	}
	
	
	Util util;
	HanFix hanFix;
	NeighborMap neighborMap;
	Main main;
	
} // end - namespacee