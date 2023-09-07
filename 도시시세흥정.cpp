/*
@ 만든이: 기마책사
@ UPDATE: '19.1.19    / 최초적용 : 상인과 설전하여 시세를 흥정
@ UPDATE: '19.5.1     / 변경내용 : 결과에 따른 경험치, 상병 등을 적용
*/

namespace 도시시세흥정
{
	//---------------------------------------------------------------------------------------
    
	const int ACTION_COST_시세흥정 = 20;
    
    
    //---------------------------------------------------------------------------------------
    
    
	
	class Main
	{
		
		pk::building@ building;
		pk::force@ force;
		pk::city@ city;
        pk::district@ district;
        pk::point building_pos;
		pk::person@ taishu;
		pk::person@ actor;
		pk::person@ merchant;
        uint16 building_gold;
        uint8 currency;
        int debate_result;
        array<int> arr_stat = {65, 70, 75, 80, 85};

		Main()
		{
            // 시세흥정 메뉴 (유저용)
			pk::menu_item 시세흥정;
			시세흥정.menu = 100;        // 도시메뉴
			시세흥정.pos = 6;
			시세흥정.init = pk::building_menu_item_init_t(init);
			시세흥정.is_visible = pk::menu_item_is_visible_t(isVisible_시세흥정);
			시세흥정.is_enabled = pk::menu_item_is_enabled_t(isEnabled_시세흥정);
			시세흥정.get_text = pk::menu_item_get_text_t(getText_시세흥정);
			시세흥정.get_desc = pk::menu_item_get_desc_t(getDesc_시세흥정);
			시세흥정.handler = pk::menu_item_handler_t(handler_시세흥정);
			pk::add_menu_item(시세흥정);
            
		}

        
        //---------------------------------------------------------------------------------------
        
		void init(pk::building@ building_t)
		{
			@building = @building_t;
			@force = pk::get_force(building.get_force_id());
            @city = pk::building_to_city(building);
            @taishu = pk::get_person(pk::get_taishu_id(building));
            @district = pk::get_district(building.get_district_id());
            
            building_gold = pk::get_gold(building);
            building_pos = building.pos;
            currency = city.rate/10;
            
            @merchant = pk::get_person(무장_상인);
            merchant.base_stat[무장능력_지력] = arr_stat[pk::rand(5)];
            merchant.update();
		}

		string getText_시세흥정()
		{
			return pk::encode("시세흥정");
		}

		string getDesc_시세흥정()
		{
            if (pk::enemies_around(building))
                return pk::encode("주변에 적군이 있어 실행할 수 없습니다");
            else if (city.merchant_done) 
                return pk::encode("이미 거래를 완료하였습니다");
            else if (pk::get_idle_person_list(building).count == 0)
                return pk::encode("실행 가능한 무장이 없습니다");
            else if (int(district.ap) < ACTION_COST_시세흥정)
                return pk::encode(pk::format("행동력이 부족합니다 (행동력{} 필요)", ACTION_COST_시세흥정));
			else
				return pk::encode(pk::format("상인과 시세흥정을 합니다 (행동력{} 소모)", ACTION_COST_시세흥정));
		}

		bool isEnabled_시세흥정()
		{ 
            if (pk::enemies_around(building)) return false;
            else if (city.merchant_done) return false;
            else if (pk::get_idle_person_list(building).count == 0) return false;
            else if (int(district.ap) < ACTION_COST_시세흥정) return false;
			return true;
		}
        
        bool isVisible_시세흥정()
        {
            if (pk::is_campaign()) return false;
            if (!pk::is_alive(city)) return false;
            return true;
        }

		bool handler_시세흥정()
		{
            // 실행가능 무장리스트
            pk::list<pk::person@> person_list = pk::get_idle_person_list(building);
			if (person_list.count == 0) return false;
            
            bool deal = false;
            int answer = -1;
			if (pk::is_player_controlled(building))
            {
                while(!deal)
                {
                    answer = pk::choose({ pk::encode("예(시세증가)"), pk::encode("예(시세감소)"), pk::encode("아니오") }, 
                                          pk::encode(pk::format("상인과 시세를 흥정하시겠습니까? \n(현재시세 병량{}=금1)", currency)),
                                          taishu );
                    
                    if (answer == 2) return false;  // 취소 종료
                    
                    else if (answer == 1 and currency <= 1)
                    {
                        pk::message_box(pk::encode("더 이상 시세를 낮출 수 없습니다"), taishu);
                        deal = false;
                    }
                    else if (answer == 0 and currency >= 9)
                    {
                        pk::message_box(pk::encode("더 이상 시세를 올릴 수 없습니다"), taishu);
                        deal = false;
                    }
                    else
                        deal = true;
                }
            }
            
            // 실행무장 선택하기
            if (pk::is_player_controlled(building))
            {
               pk::list<pk::person@> person_sel = pk::person_selector(pk::encode("무장 선택"), pk::encode("흥정할 무장을 선택합니다."), person_list, 1, 1);
               if (person_sel.count == 0) return false; // 미선택 시 취소 종료
               @actor = pk::get_person(person_sel[0].get_id());
            }
            else
            {
                person_list.sort(function(a, b)
                {
                    return (a.stat[무장능력_지력] > b.stat[무장능력_지력]) ; // 무장 정렬 (지력순)
                });
                @actor = pk::get_person(person_list[0].get_id());
            }
            
            // 상인과 흥정
            pk::scene(pk::scene_t(scene_시세흥정));

            // 행동력 차감
            if (force.is_player())
                district.ap -= ACTION_COST_시세흥정;
            
            // 실행무장 행동완료 및 도시거래 완료
            city.merchant_done = true;
            actor.action_done = true;
           
            // 설전 승리한 경우 시세 변경
            if (debate_result == 0)
            {
                if (answer == 0)
                {
                    city.rate = city.rate + 10;
                    pk::say(pk::encode("시세를 올리기로 합의했습니다."), actor, city);
                }
                else if (answer == 1)
                {
                    city.rate = city.rate - 10;
                    pk::say(pk::encode("시세를 내리기로 합의했습니다."), actor, city);
                }
            }
            else
            {
                pk::say(pk::encode("죄송합니다. 흥정에 실패했습니다."), actor, city);
            }
            
			return true;
		}
        
        
        void scene_시세흥정()
		{
			debate_result = pk::debate(actor, merchant, pk::is_player_controlled(actor), false, true, true).first;
		}
        
        

	}

	Main main;
}