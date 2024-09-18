/*  
@제작자: 기마책사
@Update: '18.12.3  / 최초적용: 폐위된 후한황제를 복위시키고 옹립함
@Update: '19.7.8   / 변경내용: 폐황제 붕어메시지 오류 수정
@Update: '20.8.29  / 변경내용: 캠페인에서는 스크립트 비활성화

*/

namespace 폐황제옹립
{
	
	// ================ CUSTOMIZE ================
    
		const int TP_COST_옹립 = 3000; 	   // 기교P 필요량
		const int ACTION_COST_옹립 = 100;   // 행동력 필요량
		
    
	// ===========================================
	
	class Main
	{
		
		pk::building@ building;
		pk::building@ kunshu_building;
		
		pk::city@ kunshu_city;
		pk::city@ emperor_city;
        pk::point emeperor_pos;
		
		pk::force@ force;
		
		pk::person@ kunshu;
		pk::person@ emperor; 
		pk::person@ support; 

		Main()
		{

			pk::menu_item item;
			item.menu = 105;        
			item.init = pk::building_menu_item_init_t(init_옹립);
			item.is_visible = pk::menu_item_is_visible_t(isVisible_옹립);
			item.is_enabled = pk::menu_item_is_enabled_t(isEnabled_옹립);
			item.get_text = pk::menu_item_get_text_t(getText_옹립);
			item.get_desc = pk::menu_item_get_desc_t(getDesc_옹립);
			item.handler = pk::menu_item_handler_t(handler_옹립);
			pk::add_menu_item(item);
            
		}

		
        void init_옹립(pk::building@ building_t)
		{
			
			@building = @building_t;
			@force = pk::get_force(building.get_force_id());
			@kunshu = pk::get_person(pk::get_kunshu_id(building));
            @kunshu_building = pk::get_building(kunshu.service);
			@kunshu_city = pk::building_to_city(kunshu_building);
            @emperor = pk::get_person(pk::get_scenario().emperor);
			@support = pk::get_person(무장_환관);
		}

		string getText_옹립()
		{
			return pk::encode("옹립");
		}

		string getDesc_옹립()
		{
            if (emperor !is null and emperor.mibun != 신분_사망)
                return pk::encode("후한 황제가 폐위되지 않았습니다");
            else if (kunshu.kanshitsu != 한실_중시)
                return pk::encode("한실 중시의 군주만 실행 가능합니다");
            else if (pk::is_protecting_the_emperor(force) or force.title == 작위_황제)
                return pk::encode("후한 황제를 옹립하고 있거나 군주가 이미 황제입니다.");
            else if (kunshu_city.get_id() != kunshu.service)
                return pk::encode("군주가 있는 도시만 실행 가능합니다.");
            else if (pk::is_absent(kunshu) or pk::is_unitize(kunshu) or kunshu.action_done)
                return pk::encode("군주가 행동을 완료했거나 부재 중 입니다.");
            else if (force.tp < TP_COST_옹립)
				return pk::encode(pk::format("기교P가 부족합니다.(기교P {})", TP_COST_옹립));
            else if (pk::get_district(pk::get_district_id(force, 1)).ap < ACTION_COST_옹립) 
                return pk::encode(pk::format("행동력이 부족합니다. (행동력 {} 필요)", ACTION_COST_옹립));
            else
				return pk::encode(pk::format("후한 황제를 복위하여 옹립합니다. (기교P {} 사용)", TP_COST_옹립));
            
		}
        
        bool isVisible_옹립()
		{ 
            if (pk::is_campaign()) return false;
            if (emperor !is null and emperor.mibun != 신분_사망) return false;
            else if (kunshu.kanshitsu != 한실_중시) return false;
            return true;
		}
        
		bool isEnabled_옹립()
		{ 
            if (emperor !is null and emperor.mibun != 신분_사망) return false;
            else if (kunshu.kanshitsu != 한실_중시) return false;
            else if (pk::is_protecting_the_emperor(force) or force.title == 작위_황제) return false;
            else if (kunshu_city.get_id() != kunshu.service) return false;
            else if (pk::is_absent(kunshu) or pk::is_unitize(kunshu) or kunshu.action_done) return false;
            else if (force.tp < TP_COST_옹립) return false;
            else if (pk::get_district(pk::get_district_id(force, 1)).ap < ACTION_COST_옹립) return false;
            else
			return true;
		}

		bool handler_옹립()
		{
			if (pk::choose({ pk::encode("예"), pk::encode("아니오")}, pk::encode(pk::format("폐황제를 복위시키겠습니까?\n(기교 {} 사용)", TP_COST_옹립)), kunshu) == 1)
				return false;
			            
			// 후한 황제와의 대화
            pk::scene(pk::scene_t(scene_옹립));
            
            // 후한 황제 복원 및 이동
            emperor.mibun = 신분_없음;
            emperor.update();
            pk::move(emperor, kunshu_building, false);
            
			// 행동력 감소
			auto district = pk::get_district(pk::get_district_id(force, 1));
			district.ap -= ACTION_COST_옹립;
			
			// 기교 감소
			pk::add_tp(force, -TP_COST_옹립, force.get_pos());
			
            string kunshu_name = pk::decode(pk::get_name(kunshu));
			pk::message_box(pk::encode(pk::format("\x1b[1x{}군\x1b[0x이(가) 후한황제를 옹립하였습니다.", kunshu_name)));
			pk::create_effect(0x51, kunshu_building.pos);   //이펙트효과
            
            kunshu.action_done = true;
            
			return true;
			
		}
        
        
        void scene_옹립()
		{
			int pause = int(pk::option["MessagePause"]);
			pk::option["MessagePause"] = 100;
            pk::message_box(pk::encode("폐위된 황제께서는 어디 계시느냐. 어서 모셔와야 한다."), kunshu);
            pk::cutin(12);  // 컷인: 말발굽
			pk::move_screen(kunshu_city.get_pos(), 2000);
            
            // 재야 황제 알현
			scene_옹립_1();
            
            pk::move_screen(kunshu_city.get_pos(), 2000);
            
			pk::say(pk::encode("어서 황제 폐하를 모셔라"), kunshu, kunshu_city);
			pk::cutin(21);  // 컷인: 병사환호
			
            pk::option["MessagePause"] = pause;
			
		}
        
        void scene_옹립_1()
		{
            string kunshu_name = pk::decode(pk::get_name(kunshu));
			string kunshu_title = pk::decode(pk::get_name(pk::get_title(force.title)));
			string kunshu_city_name = pk::decode(pk::get_name(kunshu_city));
            
            pk::fade(0);
			pk::sleep();
            
			pk::background(9);  //배경: 농장
			pk::fade(255);
            pk::message_box(pk::encode("여봐라 여기 이렇게 생기신 분을 본 적 없느냐"), kunshu);
            pk::message_box(pk::encode("글쎄요...잘 모르겠습니다..."), pk::get_person(무장_농민));
            pk::message_box(pk::encode("시장에 본 것 같기도 하고..."), pk::get_person(무장_청년));
            pk::message_box(pk::encode("어저 시장으로 가보자. 단서가 있을지도 모른다."), kunshu);
            pk::message_box(pk::encode("예, 주군. 이쪽입니다"), pk::get_person(무장_문관));
            pk::fade(0);
            pk::background(-1);
            
            pk::background(4);  //배경: 시장
			pk::fade(255);
            pk::message_box(pk::encode("혹시 이런 분을 본 적 없느냐"), kunshu);
            pk::message_box(pk::encode("아. 이 분. 저 쪽에 있는 집으로 가시면 됩니다. 그런데 어쩐 일로..."), pk::get_person(무장_부호));
            pk::message_box(pk::encode("고맙소. \n서둘러라. 어서."), kunshu);
            pk::message_box(pk::encode("예."), pk::get_person(무장_무관));
            pk::message_box(pk::encode("무슨 일이길래 저리 급한고."), pk::get_person(무장_부호));
            pk::fade(0);
            pk::background(-1);
            
            pk::background(7);  //배경: 집앞
			pk::fade(255);
            pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x님이 아니십니까? 여기를 어떻게 찾으셨습니까? 흑흑.", kunshu_name)), support);
            pk::message_box(pk::encode("폐하를 모시러 비밀리에 찾아왔소. 폐하는 어디 계시오?"), kunshu);
            pk::message_box(pk::encode("이쪽입니다. 따라 오시지요."), support);
            pk::fade(0);
            pk::background(-1);
            
            pk::background(5);  //배경: 집
            pk::fade(255);
            
            
            if (emperor is null)
            {
                pk::get_scenario().emperor = 무장_헌제;
                @emperor = pk::get_person(pk::get_scenario().emperor);
            }
            
            pk::message_box(pk::encode(pk::format("아니! 폐하가 아니십니까? \x1b[1x{}\x1b[0x이(가) 폐하를 알현합니다", kunshu_name)), kunshu);
            pk::message_box(pk::encode(pk::format("내 폐위되고 너무나 힘들었는데, \x1b[1x{}\x1b[0x 그대를 만나 다행이구려. ", kunshu_name)), emperor);
            pk::message_box(pk::encode("황송합니다"), kunshu);
            pk::message_box(pk::encode(pk::format("신 \x1b[1x{}\x1b[0x이(가) 폐하를 모시겠습니다.", kunshu_name)), kunshu);
            pk::message_box(pk::encode("그저 고맙소. 그대야말로 진정한 충신이오"), emperor);
            pk::message_box(pk::encode(pk::format("폐하. 어서 채비를 하시지요. 신이 \x1b[1x{}\x1b[0x(으)로 폐하를 모시겠습니다.", kunshu_city_name)), kunshu);
            pk::background(-1);
        }
		

	}
   
	Main main;
}