/*
@ 만든이: 기마책사
@ UPDATE: '18.11.17  / 최초적용: 후한황제 천도
@ UPDATE: '18.11.23  / 변경내용: 황제 자동선택 수정, 황후 및 황제 지력 군주에 맞춰서 강제 조정, 군주행동완료 반영
                               후한황제도주 이벤트 추가
@ UPDATE: '18.11.25  / 변경내용: 후한황제도주 시 작위없는군주 제외, 대사 작위 출력오류 수정
@ UPDATE: '18.12.3   / 변경내용: 황제폐위 후 메뉴 초기화 오류 방지 추가
@ UPDATE: '20.8.29   / 변경내용: 캠페인에서는 스크립트 비활성화
*/

namespace 후한황제천도
{
	//---------------------------------------------------------------------------------------
    
    const bool 후한황제천도_사용 = true;
    const int TP_COST_천도 = 1000; 	// 기교P 필요량
    const int ACTION_COST_천도 = 50;
    const int GOLD_COST_천도  = 5000;
    
	const int KEY = pk::hash("천도");
    
    //---------------------------------------------------------------------------------------
    
    const bool 후한황제도주_사용 = true;
    const int 후한황제도주_기준치안  = 65;    // 후한황제 도주 이벤트 발생 기준 치안
    const int 후한황제도주_기준도시수  = 1;   // 후한황제 도주 이벤트 발생 기준 도시수
    const int 후한황제도주_발생확률  = 100;    // 군주가 한실_보통인 경우 도주 확률 (한실_중시는 도주 미발생, 한실_무시는 무조건 도주)
    
    //---------------------------------------------------------------------------------------
    
	
	class Main
	{
		
		pk::building@ building;
		pk::building@ kunshu_building;
		pk::city@ kunshu_city;
		pk::city@ emperor_city;
		pk::force@ force;
		pk::person@ kunshu;
		pk::person@ emperor; 
		pk::person@ support; 
		pk::person@ reporter; 
        pk::force@ new_force;
        pk::person@ new_kunshu;
        pk::building@ new_building;
		pk::city@ new_city;
        uint16 building_gold;
        bool kunshu_building_check;
        bool emperor_city_check;
        int debate_result;
        
		Main()
		{
            if (후한황제천도_사용)
            {
                pk::menu_item 천도;
                천도.menu = 105;        // 군주메뉴
                천도.init = pk::building_menu_item_init_t(init);
                천도.is_visible = pk::menu_item_is_visible_t(isVisible_천도);
                천도.is_enabled = pk::menu_item_is_enabled_t(isEnabled_천도);
                천도.get_text = pk::menu_item_get_text_t(getText_천도);
                천도.get_desc = pk::menu_item_get_desc_t(getDesc_천도);
                천도.handler = pk::menu_item_handler_t(handler_천도);
                pk::add_menu_item(천도);
            }
            
            // 턴 시작 이벤트
            pk::bind(111, pk::trigger111_t(onTurnStart));
            
		}
        
        
        void onTurnStart(pk::force@ force_turn)
        {
            if (후한황제도주_사용)
                event_Emperor_Escape(force_turn);
        }
        
        
        
        //---------------------------------------------------------------------------------------
        
        void init(pk::building@ building_t)
		{
			@building = @building_t;
			@force = pk::get_force(building.get_force_id());
			@kunshu = pk::get_person(pk::get_kunshu_id(building));
            @kunshu_building = pk::get_building(kunshu.service);
			@kunshu_city = pk::building_to_city(kunshu_building);
            building_gold = pk::get_gold(building);
            
            @emperor = pk::get_person(pk::get_scenario().emperor);
            
            if (emperor is null) return;
            else if (emperor.mibun != 신분_사망)
            {
                if (emperor.get_id() == 무장_헌제)
                    @support = pk::get_person(무장_황후);
                else if (emperor.get_id() == 무장_소제)
                    @support = pk::get_person(무장_환관);
                else if (emperor.get_id() == 무장_영제)
                {
                    switch(pk::rand(2))
                    {
                    case 0: @support = pk::get_person(무장_장양_십상시); break;
                    case 1: @support = pk::get_person(무장_건석_십상시); break;
                    }
                }
                
                @emperor_city = pk::building_to_city(pk::hex_object_to_building(pk::get_hex_object(emperor.location)));
                kunshu_building_check = (building.get_id() == kunshu.service);
                emperor_city_check = (emperor_city.get_id() == kunshu.service);
            
                
                // 황후 및 황제 지력 강제 변경 ('18.11.18)
                support.base_stat[무장능력_지력] = pk::max(1, kunshu.base_stat[무장능력_지력] - 15);
                support.update();
                emperor.base_stat[무장능력_지력] = pk::max(1, kunshu.base_stat[무장능력_지력] - 5);
                emperor.update();
            }
            
		}

		string getText_천도()
		{
			return pk::encode("천도");
		}

		string getDesc_천도()
		{
            if (emperor is null)
                return pk::encode("후한이 멸망했습니다");
            else if (!pk::is_protecting_the_emperor(force) or force.title == 작위_황제 or emperor.mibun == 신분_사망)
                return pk::encode("후한 황제를 옹립하고 있지 않습니다");
            else if (emperor_city_check)
                return pk::encode("군주와 후한 황제가 같은 도시에 있어 천도를 할 수 없습니다");
            else if (!kunshu_building_check)
                return pk::encode("군주가 있는 도시만 실행 가능합니다");
            else if (pk::is_absent(kunshu) or pk::is_unitize(kunshu) or kunshu.action_done)
                return pk::encode("군주가 행동을 완료했거나 부재 중 입니다.");
            else if (force.tp < TP_COST_천도)
				return pk::encode(pk::format("기교P가 부족합니다.(기교P {})", TP_COST_천도));
            else if (pk::get_district(pk::get_district_id(force, 1)).ap < ACTION_COST_천도) 
                return pk::encode(pk::format("행동력이 부족합니다 (행동력 {} 필요)", ACTION_COST_천도));
			else if (building_gold < GOLD_COST_천도)
				return pk::encode(pk::format("금이 부족합니다 (금{} 필요)", GOLD_COST_천도));
			else
				return pk::encode(pk::format("천도를 실행합니다 (기교{}, 금{} 사용)", TP_COST_천도, GOLD_COST_천도));
		}
        
        bool isVisible_천도()
		{ 
            if (pk::is_campaign()) return false;
            if (emperor is null) return false;
            if (!pk::is_protecting_the_emperor(force) or force.title == 작위_황제 or emperor.mibun == 신분_사망) return false;
			return true;
		}
        
		bool isEnabled_천도()
		{ 
            if (emperor is null) return false;
            else if (!pk::is_protecting_the_emperor(force) or force.title == 작위_황제 or emperor.mibun == 신분_사망) return false;
            else if (emperor_city_check) return false;
            else if (!kunshu_building_check) return false;
            else if (pk::is_absent(kunshu) or pk::is_unitize(kunshu) or kunshu.action_done) return false;
            else if (force.tp < TP_COST_천도) return false;
            else if (pk::get_district(pk::get_district_id(force, 1)).ap < ACTION_COST_천도) return false;
            else if (building_gold < GOLD_COST_천도) return false;
			return true;
		}
        

		bool handler_천도()
		{
			
			if (pk::choose({ pk::encode("예"), pk::encode("아니오") }, pk::encode(pk::format("군주의 도시로 천도하시겠습니까? \n(기교{}, 금{} 사용)", TP_COST_천도, GOLD_COST_천도)), kunshu ) == 1)
				return false;
            
            
            //-----------------------------------------------------------------
            // 후한 황제와의 대화
            pk::scene(pk::scene_t(scene_천도));
            
            //-----------------------------------------------------------------
            
            if (debate_result ==0)
            {
                // 후한 황제 이동
                pk::move(emperor, kunshu_building, false);
                
                // 실행 도시 금 소비
                pk::add_gold(kunshu_city, -GOLD_COST_천도, true);
                
                // 행동력 감소
                auto district = pk::get_district(pk::get_district_id(force, 1));
                district.ap -= ACTION_COST_천도;
                
                // 기교 감소
                pk::add_tp(force, -TP_COST_천도, force.get_pos());
                
                pk::say(pk::encode("어서 황제 폐하를 모셔라"), kunshu, kunshu_city);
                pk::create_effect(0x51, kunshu_building.pos);   //이펙트효과
            }
            else
            {
                // 행동력 감소
                auto district = pk::get_district(pk::get_district_id(force, 1));
                district.ap -= ACTION_COST_천도;
                
                pk::say(pk::encode("폐하를 설득하는 데 실패했군"), kunshu, kunshu_city);
            }
            
            // 군주 행동완료 ('18.11.18)
            kunshu.action_done = true;
            
			return true;
			
		}
        
        
        void scene_천도()
		{
			int pause = int(pk::option["MessagePause"]);
			pk::option["MessagePause"] = 100;
            pk::message_box(pk::encode("폐하를 설득하여 천도를 해야겠군"), kunshu);
            pk::cutin(18);  // 컷인: 걸음걸이
			pk::move_screen(emperor_city.get_pos(), 2000);
			pk::diplomacy(emperor, support, kunshu, pk::diplomacy_t(scene_천도_1));
            pk::move_screen(kunshu_city.get_pos(), 2000);
            
            if (debate_result == 0)
                pk::cutin(21);  // 컷인: 병사환호
			
            pk::option["MessagePause"] = pause;
		}
        
        void scene_천도_1()
		{
            string kunshu_name = pk::decode(pk::get_name(kunshu));
            string city1_name = pk::decode(pk::get_name(emperor_city));
            string city2_name = pk::decode(pk::get_name(kunshu_city));
            
            pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x여, 무슨 일로 이렇게 찾아오셨소?", kunshu_name)), emperor);
            pk::message_box(pk::encode(pk::format("폐하, 요즘 역적들의 기세가 날로 강해지고 있어 여기 \x1b[1x{}\x1b[0x은(는) 계시기에 위험합니다.", city1_name)), kunshu);
            pk::message_box(pk::encode("그대는 그러면 어찌하면 좋겠는가?"), emperor);
            pk::message_box(pk::encode(pk::format("신이 안전하게 \x1b[1x{}\x1b[0x로 모시겠습니다. 천도를 하시지요.", city2_name)), kunshu);
            pk::message_box(pk::encode("천도를 하자는 말이오?"), emperor);
            
            // 군주와 황후와의 설전
            pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x님, 제가 생각하기엔 무리입니다.", kunshu_name)), support);
            debate_result = pk::debate(kunshu, support, true, false, false, true).first;
            
            if (debate_result ==0)  // 군주가 설전 이기면 후한황제와 재설전
            {
                pk::message_box(pk::encode("그렇다고 해도..."), support);
                pk::message_box(pk::encode("다시 한번 생각해보면 안되겠소?"), emperor);
                debate_result = pk::debate(kunshu, emperor, true, false, false, true).first;
            }
            
            if (debate_result ==0)  // 군주가 설전 이김
            {
                pk::message_box(pk::encode("그렇습니다. 어서 채비를 하시지요."), kunshu);
                pk::message_box(pk::encode("으으음...알겠소.\n경의 의견을 따르겠소."), emperor);
            }
            else    // 후한황제가 설전 이김
            {
                pk::message_box(pk::encode("천도는 아니되오."), emperor);
                pk::message_box(pk::encode("알겠습니다."), kunshu);
            }
        }
        
        
        
        //---------------------------------------------------------------------------------------
        
        void event_Emperor_Escape(pk::force@ force_turn)
        {
            @force = @force_turn;
            
            if (force.is_player() and pk::is_protecting_the_emperor(force) and force.title != 작위_황제)
            {
                @kunshu = pk::get_person(pk::get_kunshu_id(force));
                @kunshu_building = pk::get_building(kunshu.service);
                @kunshu_city = pk::building_to_city(kunshu_building);
                @emperor = pk::get_person(pk::get_scenario().emperor);
                @emperor_city = pk::building_to_city(pk::hex_object_to_building(pk::get_hex_object(emperor.location)));
                
                if (emperor.get_id() == 무장_헌제)
                    @support = pk::get_person(무장_황후);
                else
                    @support = pk::get_person(무장_환관);
                
                @ reporter = pk::get_person(무장_문관);
                
                if (emperor_city.public_order < 후한황제도주_기준치안 and pk::get_city_count(force) >= 후한황제도주_기준도시수 and
                   ((kunshu.kanshitsu == 한실_무시) or (kunshu.kanshitsu == 한실_보통 and pk::rand_bool(후한황제도주_발생확률)) ) )
                {
                    // 가장 강한 세력 검색
                    int force_num = EnemyForceSel(emperor_city);
                    if (force_num > -1)
                    {
                        @ new_force = pk::get_force(force_num);
                        @ new_kunshu = pk::get_person(pk::get_kunshu_id(new_force));
                        @ new_building = pk::get_building(new_kunshu.service);
                        @ new_city = pk::building_to_city(new_building);
                        
                        // 후한 황제 도주씬
                        pk::scene(pk::scene_t(scene_도주));
                        
                        // 후한 황제 이동
                        pk::move(emperor, new_building, false);
                    }
                }
            }

        }
        
        void scene_도주()
		{
            // 후한황제 밀담
			pk::move_screen(emperor_city.get_pos(), 2000);
			pk::diplomacy(emperor, support, reporter, pk::diplomacy_t(scene_도주_1));
            
            // 배경 궁성
            scene_도주_2();
            
            // 도시 이동
            pk::move_screen(new_city.get_pos(), 2000);
            scene_도주_3();
            
            string emperor_name = pk::decode(pk::get_name(emperor));
            string kunshu_name = pk::decode(pk::get_name(kunshu));
            string new_kunshu_name = pk::decode(pk::get_name(new_kunshu));
            pk::message_box(pk::encode(pk::format("\x1b[1x{}군\x1b[0x이 후한황제를 옹립하였습니다.", new_kunshu_name)));
            pk::option["MessagePause"] = 100;
		}
        
        void scene_도주_1()
		{
            string kunshu_name = pk::decode(pk::get_name(kunshu));
            string new_kunshu_name = pk::decode(pk::get_name(new_kunshu));
            string city1_name = pk::decode(pk::get_name(emperor_city));
            string city2_name = pk::decode(pk::get_name(new_city));
            
            pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x의 무례함이 날로 심해지고 있도다", kunshu_name)), emperor);
            pk::message_box(pk::encode(pk::format("여기 \x1b[1x{}\x1b[0x의 방비가 허술한 듯 하니 몰래 거처를 옮기시는 게 어떨런지요?", city1_name)), support);
            pk::message_box(pk::encode("대체 어디로 간단 말이냐?"), emperor);
            pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x에게 의지하는 게 어떠신가요? \x1b[1x{}\x1b[0x로 가시지요.", new_kunshu_name, city2_name)), support);
            pk::message_box(pk::encode("좋은 생각이다. 어서 여기를 빠져나가자"), emperor);
            pk::message_box(pk::encode("예. 소신이 모시겠습니다"), reporter);
        }
        void scene_도주_2()
		{
            pk::person@ gaurd = pk::get_person(무장_위병);

            pk::background(1);  
            pk::message_box(pk::encode("어디로 가시는 길입니까?"), gaurd);
            pk::cutin(20);  // 컷인: 노려보기
            pk::message_box(pk::encode("산책 가는 길이다. 길을 비켜라 어서!"), reporter);
            pk::message_box(pk::encode("아..아..아무런 보고도 듣지 못했습니다"), gaurd);
            pk::message_box(pk::encode("무엄하구나"), support);
            pk::message_box(pk::encode("죄송합니다. 어서 가십시오."), gaurd);
            pk::background(-1);
            pk::fade(100);
        }
        void scene_도주_3()
		{
            string kunshu_name = pk::decode(pk::get_name(kunshu));
            string new_kunshu_name = pk::decode(pk::get_name(new_kunshu));
            string new_kunshu_title = pk::decode(pk::get_name(pk::get_title(new_force.title)));
            
            pk::background(3);
            pk::fade(255);
            pk::message_box(pk::encode(pk::format("헉.헉.여봐라. 아직 \x1b[1x{}\x1b[0x의 영지는 멀었는가?", new_kunshu_name)), emperor);
            pk::message_box(pk::encode(pk::format("아닙니다. \x1b[1x{}\x1b[0x의 영지는 근처이니 조금만 더 가시면 됩니다.", new_kunshu_name)), reporter);
            pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x은(는) 과연 믿을 수 있는 자인지....", new_kunshu_name)), emperor);
            pk::cutin(12);  // 컷인: 말발굽
            pk::message_box(pk::encode(pk::format("이 소리는 무엇이냐. \x1b[1x{}군\x1b[0x이 여기까지 쫓아왔는가?", kunshu_name)), emperor);
            pk::fade(0);
			pk::sleep();
			pk::background(-1);
            
            pk::background(11);
			pk::fade(255);
            pk::play_bgm(17);
            
            if (new_force.title <= 작위_주자사)
                pk::message_box(pk::encode(pk::format("아니! 폐하가 아니십니까? \x1b[1x{} {}\x1b[0x이(가) 폐하를 알현합니다", new_kunshu_title, new_kunshu_name)), new_kunshu);
            else
                pk::message_box(pk::encode(pk::format("아니! 폐하가 아니십니까? \x1b[1x{}\x1b[0x이(가) 폐하를 알현합니다", new_kunshu_name)), new_kunshu);
            
            pk::message_box(pk::encode(pk::format("그대를 만나 다행이구려. 내 \x1b[1x{}\x1b[0x에게 의지하러 힘들게 여기까지 왔노라.", new_kunshu_name, kunshu_name)), emperor);
            pk::message_box(pk::encode("황송합니다"), new_kunshu);
            pk::message_box(pk::encode("어서 폐하께서 계실 거처를 안내하시오"), support);
            pk::message_box(pk::encode("예. 이쪽입니다. 어서 폐하를 모셔라."), new_kunshu);
            
            pk::cutin(21);  // 컷인: 병사환호
        }
        
        //--------------------------------------------------------------------------------
        // 최강 적세력 검색 함수
        int EnemyForceSel(pk::city @ city)
        {
            int force_sel = -1;
            int force_city_cnt = 0;
            
            auto force_list = pk::list_to_array(pk::get_force_list());
            for (int k = 0; k < int(force_list.length); k++)
            {
                if (force_list[k].title <= 작위_주자사 and force_list[k].get_force_id() != city.get_force_id() and force_city_cnt < pk::get_city_count(force_list[k]))
                {
                    force_city_cnt = pk::get_city_count(force_list[k]);
                    force_sel = force_list[k].get_force_id();
                }
            }
            
            return force_sel;
        }
        //--------------------------------------------------------------------------------

	}
   
	Main main;
}