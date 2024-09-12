namespace 거점_AI_행동_순서
{
	class Main
	{
		Main()
		{
			pk::set_func(255, pk::func255_t(callback));
		}

		void callback(pk::ai_context@ context, pk::building@ building)
		{
			int building_id = building.get_id();
			pk::ai_context_base@ base = context.base[building_id];
			int a = pk::get_person(pk::get_kunshu_id(building)).character;			

			// 거점 주변 3칸 안에 적 있음
			if (base.enemies_around3)
			{
			 if (building_id < 건물_도시끝 and 6000 < pk::get_troops(building)  )
			      {																			 
				context.push_cmd(거점AI_방어);
				  }

            else if (building_id >= 건물_도시시작 and 10000 < pk::get_troops(building)  )
			      {																			 		  																												  
				context.push_cmd(거점AI_방어);

			      }

				if (building_id >= 건물_도시시작 and building_id < 건물_도시끝)
				{
					// 플레이어가 공격중일 때만 방어 강화
					if (base.num_player_units > 0)
					{
			          if (base.enemies_around5)							
						context.push_cmd(거점AI_징병);
			          if (base.enemies_around5)							
						context.push_cmd(거점AI_생산);							
						context.push_cmd(거점AI_순찰);
			          if (base.enemies_around5)								
						context.push_cmd(거점AI_징병);
						context.push_cmd(거점AI_순찰);
			          if (base.enemies_around5)								
						context.push_cmd(거점AI_징병);
						context.push_cmd(거점AI_순찰);
			          if (base.enemies_around5)								
						context.push_cmd(거점AI_생산);
			          if (base.enemies_around5)								
						context.push_cmd(거점AI_생산);
						
					}
					else
					{
			          if (base.enemies_around5)								
						context.push_cmd(거점AI_징병);
			          if (base.enemies_around5)								
						context.push_cmd(거점AI_생산);	
			          if (base.enemies_around5)								
						context.push_cmd(거점AI_징병);						
						context.push_cmd(거점AI_순찰);
			          if (base.enemies_around5)								
						context.push_cmd(거점AI_생산);
						
					}

				}
				return;

			}
			// 명령 가능한 무장 없음
			if (base.num_idle_officers == 0)
				return;

			// 도시
			if (building_id >= 건물_도시시작 and building_id < 건물_도시끝)
			{
				uint gold = pk::get_gold(building);
				uint officers_needed = pk::max(base.officers_needed, 10);
				uint total_weapons = 0;
				for (int i = 병기_창; i <= 병기_군마; i++)
					total_weapons = total_weapons + pk::get_weapon_amount(building, i);
				
				pk::city@ my_city = pk::building_to_city(building);
				
				switch (base.status)
				{
				case 거점상태_후방:

			    if ( my_city.num_devs < my_city.max_devs and pk::get_elapsed_months() > 3)
			    {
					context.push_cmd(거점AI_개발);					
					context.push_cmd(거점AI_개발);	
					context.push_cmd(거점AI_개발);					
					context.push_cmd(거점AI_개발);						
				
			    }					

			          if (base.enemies_around5)		
						context.push_cmd(거점AI_징병);
			          if (base.enemies_around5)							
						context.push_cmd(거점AI_생산);						  
					context.push_cmd(거점AI_순찰);
					context.push_cmd(거점AI_포상);
					context.push_cmd(거점AI_최소인재탐색);
					
					context.push_cmd(거점AI_개발);					
					context.push_cmd(거점AI_개발);						
					context.push_cmd(거점AI_최소무장등용);
					context.push_cmd(거점AI_최소타세력무장등용);
					context.push_cmd(거점AI_포상);
					context.push_cmd(거점AI_거래);
					context.push_cmd(거점AI_계략);
			          if (base.enemies_around5)							
					context.push_cmd(거점AI_생산);
					context.push_cmd(거점AI_거래2);
			          if (base.enemies_around5)							
					context.push_cmd(거점AI_징병);
					context.push_cmd(거점AI_훈련);

					
					context.push_cmd(거점AI_개발);
					context.push_cmd(거점AI_흡수합병);

					context.push_cmd(거점AI_인재탐색);
					context.push_cmd(거점AI_무장등용);
					context.push_cmd(거점AI_타세력무장등용);
					context.push_cmd(거점AI_포상);
					context.push_cmd(거점AI_계략);
       				
					break;

				case 거점상태_경계:

			    if ( my_city.num_devs < my_city.max_devs and pk::get_elapsed_months() > 3)
			    {
					context.push_cmd(거점AI_개발);					
					context.push_cmd(거점AI_개발);	
					context.push_cmd(거점AI_개발);					
					context.push_cmd(거점AI_개발);						
				
			    }	

			          if (base.enemies_around5)			
						context.push_cmd(거점AI_징병);
			          if (base.enemies_around5)							
						context.push_cmd(거점AI_생산);										   
					context.push_cmd(거점AI_최소인재탐색);
					context.push_cmd(거점AI_최소무장등용);
					context.push_cmd(거점AI_최소타세력무장등용);
					context.push_cmd(거점AI_포상);
			          if (base.enemies_around5)							
					context.push_cmd(거점AI_징병);
					context.push_cmd(거점AI_순찰);

					context.push_cmd(거점AI_개발);					
					context.push_cmd(거점AI_개발);									   
					context.push_cmd(거점AI_계략);
					context.push_cmd(거점AI_거래2);
					context.push_cmd(거점AI_거래);
			          if (base.enemies_around5)							
					context.push_cmd(거점AI_생산);
					context.push_cmd(거점AI_훈련);
					
					context.push_cmd(거점AI_개발);
					context.push_cmd(거점AI_흡수합병);

									   
											 
					context.push_cmd(거점AI_인재탐색);
					context.push_cmd(거점AI_무장등용);
					context.push_cmd(거점AI_타세력무장등용);
					context.push_cmd(거점AI_포상);
					context.push_cmd(거점AI_계략);		

											
					break;

				case 거점상태_전방:

			    if ( my_city.num_devs < my_city.max_devs and pk::get_elapsed_months() > 3)
			    {
					context.push_cmd(거점AI_개발);					
					context.push_cmd(거점AI_개발);	
					context.push_cmd(거점AI_개발);					
					context.push_cmd(거점AI_개발);						
				
			    }	

			          if (base.enemies_around5)		
						context.push_cmd(거점AI_징병);
			          if (base.enemies_around5)							
						context.push_cmd(거점AI_생산);						
					context.push_cmd(거점AI_설치);

					context.push_cmd(거점AI_포상);
					context.push_cmd(거점AI_최소인재탐색);
					context.push_cmd(거점AI_최소무장등용);
					context.push_cmd(거점AI_최소타세력무장등용);
					context.push_cmd(거점AI_포상);
					
					context.push_cmd(거점AI_흡수합병);
					context.push_cmd(거점AI_개발);
					// 무장과 금이 충분한 경우 내정시설 2개씩 건설
					if (base.num_officers >= officers_needed and gold > 1500)
						context.push_cmd(거점AI_개발);
					// 병기가 병력보다 모자르다면 병기생산 우선
					if (base.enemies_around5 and total_weapons < pk::get_troops(building) - 5000)
						context.push_cmd(거점AI_생산);
			          if (base.enemies_around5)							
					context.push_cmd(거점AI_징병);
					context.push_cmd(거점AI_순찰);
					context.push_cmd(거점AI_훈련);
					context.push_cmd(거점AI_거래2);
					context.push_cmd(거점AI_거래);
			          if (base.enemies_around5 and total_weapons < pk::get_troops(building) - 5000)							
					context.push_cmd(거점AI_생산);

					context.push_cmd(거점AI_인재탐색);
					context.push_cmd(거점AI_무장등용);
					context.push_cmd(거점AI_타세력무장등용);
					context.push_cmd(거점AI_포상);
					context.push_cmd(거점AI_계략);
					context.push_cmd(거점AI_계략);
					context.push_cmd(거점AI_계략);

					break;

				case 거점상태_전투:
			 if ( pk::get_troops(building) <= 10000 )
			    {									   
					// 적 군사시설만 있음
					if (base.num_enemy_units == 0)
					{
						context.push_cmd(거점AI_흡수합병);
						context.push_cmd(거점AI_개발);
						if (base.num_officers >= officers_needed and gold > 1500)
							context.push_cmd(거점AI_개발);
					}
					// 적 부대 있음
					else
					{
						// 자세력 부대 수와 남아 있는 무장 수의 합이 적 세력 부대 수보다 적을 때만 철거
						if (base.num_own_units + base.num_idle_officers < base.num_enemy_units)
						{
							
									   
						}
						else if (base.num_own_units > base.num_enemy_units and pk::get_troops(building) > 15000)
						{
							context.push_cmd(거점AI_흡수합병);
							context.push_cmd(거점AI_개발);
						}
					}
					// 병기가 병력보다 모자르다면 병기생산 우선
					if (base.enemies_around5 and total_weapons < pk::get_troops(building) - 5000)
						context.push_cmd(거점AI_생산);
			       if (base.enemies_around5)					
					context.push_cmd(거점AI_징병);
			       if (base.enemies_around5)				
						context.push_cmd(거점AI_징병);
					if (base.enemies_around5 and total_weapons < pk::get_troops(building) - 5000)					
						context.push_cmd(거점AI_생산);						
					context.push_cmd(거점AI_훈련);
					context.push_cmd(거점AI_거래);
					context.push_cmd(거점AI_순찰);
					if (base.enemies_around5 and total_weapons < pk::get_troops(building) - 5000)					
					context.push_cmd(거점AI_생산);
					context.push_cmd(거점AI_거래2);
					context.push_cmd(거점AI_포상);
					context.push_cmd(거점AI_인재탐색);
					context.push_cmd(거점AI_무장등용);
					context.push_cmd(거점AI_타세력무장등용);
					context.push_cmd(거점AI_포상);
					context.push_cmd(거점AI_계략);
					context.push_cmd(거점AI_계략);
					context.push_cmd(거점AI_계략);
   
			   }

			else if (10000 < pk::get_troops(building))
			  {

					
					context.push_cmd(거점AI_방어);
					// 적 군사시설만 있음
					if (base.num_enemy_units == 0)
					{
						context.push_cmd(거점AI_흡수합병);
						context.push_cmd(거점AI_개발);
						if (base.num_officers >= officers_needed and gold > 1500)
							context.push_cmd(거점AI_개발);
					}
					// 적 부대 있음
					else
					{
						// 자세력 부대 수와 남아 있는 무장 수의 합이 적 세력 부대 수보다 적을 때만 철거
						if (base.num_own_units + base.num_idle_officers < base.num_enemy_units)
						{
							
						}
						else if (base.num_own_units > base.num_enemy_units and pk::get_troops(building) > 15000)
						{
							context.push_cmd(거점AI_흡수합병);
							context.push_cmd(거점AI_개발);
						}
					}
					// 병기가 병력보다 모자르다면 병기생산 우선
					if (base.enemies_around5 and total_weapons < pk::get_troops(building) - 5000)
						context.push_cmd(거점AI_생산);
			       if (base.enemies_around5)					
					context.push_cmd(거점AI_징병);
			       if (base.enemies_around5)				
						context.push_cmd(거점AI_징병);
					if (base.enemies_around5 and total_weapons < pk::get_troops(building) - 5000)					
						context.push_cmd(거점AI_생산);						
					context.push_cmd(거점AI_훈련);
					context.push_cmd(거점AI_거래);
					context.push_cmd(거점AI_순찰);
					if (base.enemies_around5 and total_weapons < pk::get_troops(building) - 5000)					
					context.push_cmd(거점AI_생산);
					context.push_cmd(거점AI_거래2);
					context.push_cmd(거점AI_포상);
					context.push_cmd(거점AI_인재탐색);
					context.push_cmd(거점AI_무장등용);
					context.push_cmd(거점AI_타세력무장등용);
					context.push_cmd(거점AI_포상);
					context.push_cmd(거점AI_계략);
					context.push_cmd(거점AI_계략);
					context.push_cmd(거점AI_계략);
       				   }											 
					break;
				}
			}
			// 관문, 항구
			else
			{
				switch (base.status)
				{
				case 거점상태_후방:

			    if ( pk::get_troops(building) <= 10000 )
			         {				
					context.push_cmd(거점AI_포상);									   
					context.push_cmd(거점AI_훈련);
					context.push_cmd(거점AI_계략);
					context.push_cmd(거점AI_인재탐색);
					context.push_cmd(거점AI_무장등용);
					context.push_cmd(거점AI_타세력무장등용);
					context.push_cmd(거점AI_포상);
					context.push_cmd(거점AI_계략);
				      }

	 else if (10000 < pk::get_troops(building))
			{
					
					context.push_cmd(거점AI_포상);
					context.push_cmd(거점AI_훈련);
					context.push_cmd(거점AI_계략);
					context.push_cmd(거점AI_인재탐색);
					context.push_cmd(거점AI_무장등용);
					context.push_cmd(거점AI_타세력무장등용);
					context.push_cmd(거점AI_포상);
					context.push_cmd(거점AI_계략);
					
				 }

					break;


				case 거점상태_경계:
		if ( pk::get_troops(building) <= 10000 )
			 {													
									  									   
					context.push_cmd(거점AI_포상);
					context.push_cmd(거점AI_훈련);
					context.push_cmd(거점AI_계략);
					context.push_cmd(거점AI_인재탐색);
					context.push_cmd(거점AI_무장등용);
					context.push_cmd(거점AI_타세력무장등용);
					context.push_cmd(거점AI_포상);
					context.push_cmd(거점AI_계략);
		      }

	 else if (10000 < pk::get_troops(building))
		{
								   
					context.push_cmd(거점AI_포상);
					context.push_cmd(거점AI_훈련);
					context.push_cmd(거점AI_계략);
					context.push_cmd(거점AI_인재탐색);
					context.push_cmd(거점AI_무장등용);
					context.push_cmd(거점AI_타세력무장등용);
					context.push_cmd(거점AI_포상);
					context.push_cmd(거점AI_계략);
					
             	}		   


					break;

				case 거점상태_전방:
		if ( pk::get_troops(building) <= 10000 )
			 {		
					context.push_cmd(거점AI_포상);	   
					context.push_cmd(거점AI_설치);
					context.push_cmd(거점AI_훈련);

					context.push_cmd(거점AI_계략);
					context.push_cmd(거점AI_인재탐색);
					context.push_cmd(거점AI_무장등용);
					context.push_cmd(거점AI_타세력무장등용);
					context.push_cmd(거점AI_포상);
					context.push_cmd(거점AI_계략);	

			  }

		else if (10000 < pk::get_troops(building))
			 {
					
					context.push_cmd(거점AI_포상);

					context.push_cmd(거점AI_설치);
					context.push_cmd(거점AI_훈련);

									   
											 
					context.push_cmd(거점AI_계략);
					context.push_cmd(거점AI_인재탐색);
					context.push_cmd(거점AI_무장등용);
					context.push_cmd(거점AI_타세력무장등용);
					context.push_cmd(거점AI_포상);
					context.push_cmd(거점AI_계략);
				 }
					break;

				case 거점상태_전투:

		if ( pk::get_troops(building) <= 10000 )
			  {			   									   
								   
					context.push_cmd(거점AI_훈련);
					context.push_cmd(거점AI_포상);
					context.push_cmd(거점AI_계략);
				}

	else if (10000 < pk::get_troops(building))
			{

					context.push_cmd(거점AI_방어);									   
					context.push_cmd(거점AI_훈련);
											 
									   
											 
					context.push_cmd(거점AI_포상);
					context.push_cmd(거점AI_계략);
       				   }																																																																																																	 
					break;
				}
			}
		}


        // ***** 거점에서 공격 나가기전 다른 아군 거점 공격 당하는 지 ***** //
        bool front_base(pk::building@ building)
        {
            for (int f = 0; f < 건물_거점끝; f++)
			{
				
                pk::force@ force = pk::get_force(building.get_force_id());				
				if (pk::get_city_count(force) <= 1) return false;	
							
                    pk::building@ front_base = pk::get_building(f);
                int building_id = building.get_id();					
                int front_base_id = front_base.get_id();	
                    int city_dist = pk::get_city_distance(pk::get_city_id(building.pos), pk::get_city_id(front_base.pos));
				
			int front_enemy_units3 = 0;
			int front_enemy_troops3 = 0;

			int front_force_units3 = 0;
			int front_force_troops3 = 0;

            // 적군검색범위
			pk::array<pk::point> front_range = pk::range(front_base.pos, 1, ((front_base.facility == 시설_도시) ? 11 : 11 ) );
			for (int i = 0; i < int(front_range.length); i++)
			{
                pk::point pos = front_range[i];
				pk::unit@ unit = pk::get_unit(pos);
				if (pk::is_alive(unit))
				{
					int distance = pk::get_distance(front_base.get_pos(), pos);
					if (pk::is_enemy(front_base, unit) and unit.type == 부대종류_전투 )
					{
						if (distance <= 10)
						{
							front_enemy_units3++;
							front_enemy_troops3 += unit.troops;
						}
					}
					else if (front_base.get_force_id() == unit.get_force_id() and unit.type == 부대종류_전투)
					{
                                             if (distance <= 10)
						{
							front_force_units3++;
							front_force_troops3 += unit.troops;		
						}
					}
				}
			}

                int a = pk::get_person(pk::get_kunshu_id(building)).character;
				
      if (pk::is_alive(front_base) and building_id != front_base_id and building.get_force_id() == front_base.get_force_id() and ((0 <= city_dist and city_dist <= 2) or building.get_district_id() == front_base.get_district_id() ) 
	  and ((front_base_id < 건물_도시끝 and front_force_troops3 + pk::get_troops(front_base) + troops_already(front_base) + (( a - 1 ) * 6000) <= front_enemy_troops3) or (front_base_id >= 건물_도시끝 and front_force_troops3 + pk::get_troops(front_base) + troops_already(front_base) + (Friendly_base(front_base) * 0.5f) <= front_enemy_troops3)
      or (front_base_id < 건물_도시끝 and pk::get_troops(front_base) + front_force_troops3 < 10000) or (front_base_id >= 건물_도시끝 and pk::get_troops(front_base) + front_force_troops3 < 4000)  ))
		  
	return true;
            }
            
	return false;
        }
		

	
         // 목표 거점으로 이미 출발한 지원군 병력 합산, masterpiecek님의 AI_도시물자수송.cpp?를 참조했습니다.
																																			  
	 int troops_already(pk::building@ building)
		{
			int already = 0;
			for (int unit_id = 0; unit_id < 부대_끝; unit_id++)
			{
				pk::unit@ unit = pk::get_unit(unit_id);
			if (building.get_force_id() == -1) continue;
			if (unit.get_force_id() == -1) continue;
				if ( pk::is_alive(unit) and 1 <= unit.troops  and unit.get_force_id() == building.get_force_id() and unit.target == building.get_id()) 

				already += unit.troops;
			}

			return already;
		}


        // ***** 주변 아군 거점 병력 수 확인 ***** //
        int Friendly_base(pk::building@ src)
        {
            int troops = 0;
            for (int i = 0; i < 건물_거점끝; i++)
			{
                pk::building@ dst = pk::get_building(i);
                int src_id = src.get_id();
                int dst_id = dst.get_id();
                
                if (src_id != dst_id and pk::is_neighbor_base(src_id, dst_id) and src.get_force_id() == dst.get_force_id() )
                    troops += pk::get_troops(dst);
            }
            
            return troops;
        }

        //---------------------------------------------------------------------------------------

	}

	Main main;
}