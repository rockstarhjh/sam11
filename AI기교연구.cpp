/*
@만든이: 크래픽스
@Update: 2023.8.12,최초배포
@Update: 2023.8.13,AI기교포인트가 증가하지 않아서 수정.
*/
namespace AI기교연구
{

	const int AI증가_기교 = 400;
	const int AI증가_주기 = 1;		// AI증가 주기(개월)를 설정합니다. 해당값은 0보다 커야 합니다.
	const int 최대연구제한 = 1; //최대연구된 단계가 1단계일때는 기교연구 안함,
	
const array<array<int>> 기교리스트 =
{
{기교_창병단련, 기교_병량습격, 기교_기습,기교_정예창병} ,
{기교_극병단련, 기교_화살방패, 기교_큰방패,기교_정예극병} ,
{기교_노병단련, 기교_응사, 기교_강노,기교_정예노병} ,
{기교_기병단련, 기교_양마산출, 기교_기사,기교_정예기병},
{기교_숙련병, 기교_난소행군, 기교_군제개혁,기교_운제},
{기교_차축강화, 기교_석조건축, 기교_투석개발,기교_벽력},
{기교_공병육성, 기교_시설강화, 기교_성벽강화,기교_방어강화},
{기교_목수개발, 기교_신화계, 기교_화약연성,기교_폭약연성},
{기교_목우유마, 기교_항관확장, 기교_법령정비,기교_인심장악}
};


	class Main
	{
        Main()
		{
			//test
			//pk::bind(111, pk::trigger111_t(onTurnStart));
			pk::bind(107, pk::trigger108_t(onNewDay));
			pk::bind(108, pk::trigger108_t(onNewMonth));
			
		}


		void onNewMonth()
		{
			pk::list<pk::force@> forces;
			forces.clear();
			forces = pk::get_force_list();
			for (auto i = 0; i < forces.count; i++)
			{
				if (pk::get_month() % AI증가_주기 == 1 || AI증가_주기 == 1)
				{
					pk::force@ force = forces[i];
					if (!pk::is_alive(force) or !pk::is_normal_force(force) or 
					!pk::is_alive(pk::get_person(force.kunshu)) or force.is_player())
						continue;

					//AI세력만 적용
					force.tp = pk::min(force.tp + AI증가_기교, 10000);
				}
			}
		}
		void onNewDay()
		{
			기교연구체크();
		}
		
		void onTurnStart(pk::force@ force)
		{
			if (!pk::is_alive(force) or !pk::is_normal_force(force) or
				!pk::is_alive(pk::get_person(force.kunshu)) or force.is_player())
				return;
			
			if (force.researching_tech > 0)
				return;
			
			기교연구(force);

		}
		void 기교연구체크()
		{
			pk::list<pk::force@> forces;
			forces.clear();
			forces = pk::get_force_list();

			for (auto i = 0; i < forces.count; i++)
			{
				pk::force@ force = forces[i];
				if (!pk::is_alive(force) or !pk::is_normal_force(force) or
					!pk::is_alive(pk::get_person(force.kunshu)) or force.is_player())
					continue;

				if(force.researching_tech > 0)
					continue;

				기교연구(force);
			}
		}
		void 기교연구(pk::force@ force)
		{
			int maxTechCount = 0;
			int maxTech = -1;

			//최대연구된 기교계산
			int maxSum = 0;
			int maxRank = 0;
			for (auto i = 0; i < 기교리스트.length; i++)
			{
				pk::tech@ tech0 = pk::get_tech(기교리스트[i][0]);
				pk::tech@ tech1 = pk::get_tech(기교리스트[i][1]);
				pk::tech@ tech2 = pk::get_tech(기교리스트[i][2]);
				pk::tech@ tech3 = pk::get_tech(기교리스트[i][3]);

				int sum = 0;
				int rank = 0;
				if (pk::has_tech(force, tech0.get_id()))
				{
					sum += tech0.tp_cost;
					rank=1;
				}
				if (pk::has_tech(force, tech1.get_id()))
				{
					sum += tech1.tp_cost;
					rank=2;
				}
				if (pk::has_tech(force, tech2.get_id()))
				{
					sum += tech2.tp_cost;
					rank=3;
				}
				if (pk::has_tech(force, tech3.get_id()))
				{
					sum += tech3.tp_cost;
					rank=4;
				}
					

				//완료된 테크는 제외
				if(sum >= tech0.tp_cost + tech1.tp_cost + tech2.tp_cost + tech3.tp_cost)
					continue;

				if (sum > maxSum) 
				{
					maxTechCount=1;
					maxTech = i;
					maxSum = sum;
					maxRank = rank;
				}
				else if (sum == maxSum) 
				{
					maxTechCount++;
				}
			}

			//여러개가 최대연구되었으면 패스
			if (maxTechCount > 1 || maxRank <= 최대연구제한)
			{
				//pk::u8printf("{},maxTechCount {}, maxRank {}\n",pk::decode(pk::get_name(force)),maxTechCount,maxRank);
				return;
			}
				

			for (auto i = 0; i < 4; i++)
			{
				pk::tech@ tech0 = pk::get_tech(기교리스트[maxTech][i]);
				if (pk::has_tech(force, tech0.get_id()))
					continue;

				if (force.tp < tech0.tp_cost)
					return;
				
				//돈이 일정이상되고, 무장이 3명이상,지도가 있으면 최우선,
				pk::list<pk::city@> cities = pk::get_city_list(force);
				cities.sort(function(a, b)
				{
					pk::building@ b0 = pk::city_to_building(a);
					pk::building@ b1 = pk::city_to_building(b);
					int count0 = pk::get_idle_person_list(b0).count;
					int count1 = pk::get_idle_person_list(b1).count;
					if (count0 < 3 and count1 < 3)
						return a.gold > b.gold;
					else if (count0 < 3)
						return false;
					else if (count1 < 3)
						return true;

					//지도특기 체크필요
					return a.gold > b.gold;
				});

				

				pk::building@ bb0 = pk::city_to_building(cities[0]);
				pk::list<pk::person@> moos = pk::get_idle_person_list(bb0);
				if (moos.count < 3)
					return;
				if (cities[0].gold < tech0.gold_cost * 1.3) //조금 여유있는 상황에서 연구
					return;

				//필요능력으로 정렬필요

				//기교연구 실행
				pk::research_tech_cmd_info ri;
				@ri.base = bb0;
				@ri.actors[0] = moos[0];
				@ri.actors[1] = moos[1];
				@ri.actors[2] = moos[2];
				ri.tech = tech0.get_id();
				if(pk::command(ri))
				{
					pk::person@ kunshu = pk::get_person(force.kunshu);
					string s = "\x1b[2x" + pk::encode(pk::decode(pk::get_name(kunshu)) + "군\x1b[0x \x1b[1x" + "\x1b[0x, 기교연구「" + pk::decode(tech0.name) + "」수행시작");
					pk::history_log(kunshu.pos, force.color, s);
					return;
				}
				//test
				//else
				//{
				//	pk::person@ kunshu = pk::get_person(force.kunshu);
				//	string s = "\x1b[2x" + pk::encode(pk::decode(pk::get_name(kunshu)) + "군\x1b[0x의 \x1b[1x" + "\x1b[0x, 기교연구「" + pk::decode(tech0.name) + "」수행실패");
				//	pk::history_log(kunshu.pos, force.color, s);
				//	return;
				//}
					
				


			}
		}

	}

	Main main;
}


