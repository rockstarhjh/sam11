/*
@만든이: 크래픽스
@Update: 2023.8.23,최초배포
*/

namespace 인재등용표시
{
	const int 글씨사이즈 = FONT_BIG;        
	//const int 글씨사이즈 = FONT_SMALL;        
	const int 시작위치_가로 = 500;
	const int 시작위치_세로 = 50;
	const int 인재표시_개수 = 5;
	
	const int 표시최대_충성도 = 90;
	const bool 포로_표시 = false;
	
	class  ManInfo
	{
		pk::building@ building;
		pk::person@ person;
		int dist;
	}
	
	pk::func157_t@ prev_callback_157;
	class Main
	{
		Main()
		{
			@prev_callback_157 = cast<pk::func157_t@>(pk::get_func(157));
			
			pk::bind(120, pk::trigger120_t(UpdatePerFrame));
		}
		void UpdatePerFrame()
		{
			int force_id = pk::get_current_turn_force_id();
            pk::force@ force = pk::get_force(force_id);
            if (null == force or !force.is_player())
                return;

			pk::building@ capital = pk::get_building(pk::get_person(force.kunshu).service);

			pk::list<pk::city@> cities = pk::get_city_list(force);
			array<ManInfo> mans;
			pk::list<pk::person@> persons = pk::get_person_list(pk::mibun_flags(신분_일반, 신분_태수, 신분_도독, 신분_재야, 신분_포로));
			for(int i=0;i<persons.count;i++)
			{
				pk::person@ p = persons[i];
				if(!포로_표시 and p.mibun == 신분_포로)
					continue;

				if (p.mibun == 신분_재야 or p.mibun == 신분_포로)
				{
					bool bFound = false;
					for (int j = 0; j < cities.count; j++)
					{
						if (cities[j].get_id() != p.location)
							continue;
						bFound = true;
						break;
					}
					if(!bFound)
						continue;
				}

				if(p.loyalty >= 표시최대_충성도)
					continue;


				ManInfo mi;
				@mi.person = p;
				@mi.building = pk::get_building(p.service);
				mi.dist = pk::get_building_distance(capital.get_id(), mi.building.get_id()) * 10;
				mans.insertLast(mi);
			}

			if(mans.length >1)
				mans.sort(function(a, b) { return a.person.loyalty < b.person.loyalty; });

			int w = 시작위치_가로;
			int h = 시작위치_세로;

			int count = pk::min(인재표시_개수, mans.length);
			for (int i = 0; i < count; i++)
			{
				ManInfo mi = mans[i];

				int offset = (글씨사이즈 == FONT_BIG ? 30 : 20);
				string strMibun = "일반";
				switch (mi.person.mibun)
				{
				case 신분_태수:strMibun = "태수"; break;
				case 신분_도독:strMibun = "도독"; break;
				case 신분_재야:strMibun = "재야"; break;
				case 신분_포로:strMibun = "포로"; break;
				default:
					break;
				}
				string str = pk::format("인재:\x1b[2x{}\x1b[0x,{},{},{}일,{}", pk::decode(pk::get_name(mi.person)),mi.person.loyalty, strMibun,mi.dist, pk::decode(pk::get_name(mi.building)));

				pk::point point;
				point.x = w;
				point.y = h; h += offset;
				pk::draw_text(pk::encode(str), point, -1, 글씨사이즈, 0x00000000);
			}
		}
	}

	Main main;
}
