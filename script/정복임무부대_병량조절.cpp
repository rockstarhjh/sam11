
namespace 정복임무부대_병량조절
{
	
	// ================ CUSTOMIZE ================

    const float minimum_food = 2.2f;    // 부대가 가져나갈 최소 군량 기준 (병력 대비 군량 비율)
    
	// ===========================================	
    
    
	class Main
	{
		
		Main()
		{
            pk::bind(172, pk::trigger172_t(정복_병량));
		}
		

        void 정복_병량(pk::unit@ unit, const pk::point &in pos)
        {
            if (pk::is_campaign()) return;
            if (!pk::is_alive(unit)) return;	
            if (unit.order != 부대임무_정복) return;			

            pk::building@ base = pk::get_building(pk::get_service(unit));
			if (!pk::is_alive(base)) return;
			if (pk::is_player_controlled(base)) return;
			if (pk::is_player_controlled(unit)) return;			

            // 부대의 이동 전 위치가 소속 거점과 다르면 아웃           
            if (base.pos != unit.pos) return;
            string base_name = pk::decode(pk::get_name(base));	
            string unit_name = pk::decode(pk::get_name(pk::get_person(unit.leader)));

		    float ratio = pk::max(minimum_food, pk::get_food(base) / float(pk::get_troops(base) + 1));

            // 전투부대고 부대임무가 정복인데 병량이 일정 비율 넘어가면 반환
            if (unit.type == 부대종류_전투 and unit.order == 부대임무_정복 and unit.food > unit.troops * ratio)
            {
                // 부대 병량 감소, 감소분을 거점에 되돌림
                int food_amount = unit.food - (unit.troops * ratio);
                pk::add_food(unit, -food_amount, false);        
                pk::add_food(base, +food_amount, false);        	

                if (디버그모드)
                pk::info(pk::format("--- {}대, {}에 군량반환! ({}→{})", unit_name, base_name, unit.food + food_amount, unit.food));		
            }
			
        }

            bool 디버그모드 = false;        
	} 

	Main main;
	
} 