/*
@만든이: 크래픽스
@Update: 2023.8.14,최초배포
@Update: 2023.8.24,전쟁시에는 인재탐색과 재야등용을하지 않음.
@Update: 2023.9.10, 인재탐색, 재야등용 주기옵션 추가.
@Update: 2024.5.27 사관등용, 포로자동등용, 재야자동탐색, 인재등용_AI유리, AI간의세력멸망시모든무장포박 기능 추가.
*/
namespace AI인재등용_AI_Recuite_v2
{
	const bool AI_인재탐색 = true;//무장행동을 소모해서, 인재탐색을 합니다.
	const int AI_인재탐색_주기 = 30; //10단위로 입력하세요. 20일에 한번
	
	const bool AI_재야등용 = true;//무장행동을 소모해서, 재야무장를 등용합니다.
	const int AI_재야등용_주기 = 10; //10일에 한번

	const bool AI_사관등용 = false;// 2달연속으로 같은도시에 있는경우, 자동으로 해당도시에 등용됨.(무장행동 소모 없음)
	const int AI_사관등용_금지기간 = 360; //시작후 1년동안 사관등용을 하지 않습니다.

	const bool AI_포로자동등용 = true;//포로가 충성도가 90미만이 되면 자동으로 등용됩니다.(무장행동 소모 없음)
	const int AI_포로자동등용_충성도 = 80;//AI간의 포로일때,80미만인경우 자동등용됨.
	const int AI_포로자동등용_충성도_유저 = 90;//유저무장이 AI의 포로일때, 90미만인경우 자동등용됨.
	const int AI_포로자동등용_확률 = 20;//멸망세력의 AI간 포로등용 확률입니다.(20%이니깐 5턴이면 대충 모든 멸망세력 포로가 등용되는셈)

	const bool AI_포로자동등용_의형제 = false; //의형제가 같은세력에 있는경우 포로자동등용하지 않습니다.
	const bool AI_포로자동등용_부부 = false; //부부가 같은 세력에 있는경우 포로자동등용하지 않습니다.
	const bool AI_포로자동등용_부친 = false;//부친이 같은 세력에 있는경우 포로자동등용하지 않습니다.
	const bool AI_포로자동등용_모친 = false;//모친이 같은 세력에 있는경우 포로자동등용하지 않습니다.

	const bool AI_재야자동탐색 = true;//AI재야탐색을 하지 않아도 랜덤으로 탐색됩니다.(무장행동 소모 없음)
	const int AI_재야자동탐색_확률 = 20;
	const int AI_재야자동탐색_금지기간 = 360;//시작후 1년동안 재야자동탐색을 하지 않습니다.


	//재야인재에는 적용되지 않음, 유저가 AI세력 등용시에는 더 어렵게, AI가 유저세려 등용시에는 더쉽게
	//40일때 80정도에 포로등용할수 있언던 서황이 66에 등용가능, 상성이 맞거나 그러면 80대에도 등용가능하긴합니다.
	const bool 인재등용_AI유리 = true;
	const int 유저_인재등용_부가수치 = -15;//유저가 AI무장 등용할때,30%확률을 더 뺌(어렵게) 
	const int AI_인재등용_부가수치 = 15;//AI가 유저 무장 등용할때 30%확률을 더함(쉽게)


	//지역이점 적용시, 기본설정으로 세력멸망시 확률적으로 장수를 포박하는데, AI간의 세력멸망시에는 확률이 아닌 100%로 포박하도록
	//유저의 경우 지역이점 포박설정 그대로 적용, 기본적으로 확률적으로 포박
	const bool AI간의_세력멸망시_모든무장포박 = true;

	const bool AI간의_세력멸망시_포로처우_포로 = true;//AI가 세력멸망시 포로를 풀어주는경우를 제한합니다.


	class Info
	{
		pk::person@ p;
		pk::city@ city;
	};

	class Main
	{
		pk::func111_t@ prev_callback_111 = null;
		pk::func220_t@ prev_callback_220 = null;
		pk::func258_t@ prev_callback_258 = null;
		Main()
		{
			pk::bind(102, pk::trigger102_t(onInit));
			pk::bind(107, pk::trigger108_t(onNewDay));

			@prev_callback_258 = cast<pk::func258_t@>(pk::get_func(258));
			pk::reset_func(258);
			pk::set_func(258, pk::func258_t(callback258));

		}
		int callback258(pk::person@ prisoner, const pk::prisoner_info& in info)
		{
			int n = prev_callback_258(prisoner, info);
			if (n != 포로처우_해방 || !AI간의_세력멸망시_포로처우_포로)
				return n;
			if (prisoner.mibun == 신분_군주)
				return 포로처우_해방;


			pk::person@ attacker;
			pk::building@ service;
			if (info.attacker.is_instance(pk::unit::type_id))
				@attacker = pk::get_person(pk::hex_object_to_unit(info.attacker).leader);
			else if (info.attacker.is_instance(pk::building::type_id))
				@attacker = pk::get_person(pk::get_taishu_id(pk::hex_object_to_building(info.attacker)));
			else
				@attacker = pk::get_person(pk::get_kunshu_id(info.attacker));

			if (pk::is_alive(attacker))
				@service = pk::get_building(attacker.service);

			// 포로를 잡은 무장의 소속이 없다면 해방
			if (!pk::is_alive(service)) return 포로처우_해방;


			pk::printf("포로처우 해방 -> 포로:{}\n",getName(prisoner));
			return 포로처우_포로;
		}

		void onInit()
		{
			_재야리스트 = {};

			pk::list<pk::person@> ps = get재야리스트();
			for (int i = 0; i < ps.count; i++)
			{
				pk::person@ p = ps[i];
				Info ifo;
				@ifo.p = p;
				@ifo.city = pk::get_city(p.location);
				_재야리스트.insertLast(ifo);
			}

			if (prev_callback_111 == null)
			{
				@prev_callback_111 = cast<pk::func111_t@>(pk::get_func(111));
				pk::reset_func(111);
				pk::set_func(111, pk::func111_t(callback111));
			}
			if (prev_callback_220 == null)
			{
				@prev_callback_220 = cast<pk::func220_t@>(pk::get_func(220));
				pk::reset_func(220);
				pk::set_func(220, pk::func220_t(callback220));
			}

		}

		void onNewDay()
		{


			update사관등용();
			update인재탐색();
			update재야등용();
			update포로등용();
			update재야자동탐색();

			_재야리스트 = {};

			pk::list<pk::person@> ps = get재야리스트();
			for (int i = 0; i < ps.count; i++)
			{
				pk::person@ p = ps[i];
				Info ifo;
				@ifo.p = p;
				@ifo.city = pk::get_city(p.location);
				_재야리스트.insertLast(ifo);
			}
		}
		
		int 미발견무장수반환(pk::list<pk::person@> targets)
		{
			int count=0;
			for(int iPerson=0;iPerson < targets.count;iPerson++)
			{
				pk::person@ person = targets[iPerson];
				if(person.mibun == 신분_미발견)
					count++;
			}
			return count;
		}
		
		pk::list<pk::item@> getKunshuItem(pk::force@ force)
		{	
			pk::list<pk::item@> items;
			for(int iItem=0;iItem<보물_끝;iItem++)
			{
				pk::item@ item = pk::get_item(iItem);
				if(item == null)
					continue;
				if(item.owner != force.kunshu)
					continue;
				items.add(item);
			}
			return items;
		}
		
		pk::item@ getNewItem(pk::list<pk::item@> oldItems,pk::list<pk::item@> newItems)
		{
			for(int i=0;i<newItems.count;i++)
			{
				pk::item@ item = newItems[i];
				bool bFound = false;
				for(int j=0;j<oldItems.count;j++)
				{
					pk::item@ item2 = oldItems[j];
					if(item.get_id() == item2.get_id())
					{
						bFound = true;
						break;
					}
				}
				if(!bFound)
					return item;
			}
			return null;
		}
		
		void update인재탐색()
		{
			if (!AI_인재탐색)
				return;
			//인재탐색은 2번의 한번만 , idle 인 무장들로, 재야등용을 해야되기때문에
			if((pk::get_elapsed_days() % AI_인재탐색_주기)!=0)
			{
				//pk::u8printf("search days return{}\n",pk::get_elapsed_days());
				return;
			}
				
			
			pk::list<pk::person@> 미발견리스트;
			for(int i=0;i<무장_끝;i++)
			{
				pk::person@ person = pk::get_person(i);
				if(person.mibun != 신분_미발견)
					continue;
				미발견리스트.add(person);
			}
			
			for(int i=0;i<50;i++)
			{
				pk::force@ force = pk::get_force(i);
				if (force==null or !pk::is_alive(force) or !pk::is_normal_force(force) or !pk::is_alive(pk::get_person(force.kunshu)) or force.is_player())
						continue;
				
				pk::list<pk::item@> items0 = getKunshuItem(force);
				
				pk::list<pk::city@> cities = pk::get_city_list(force);
				for(int iCity=0;iCity<cities.count;iCity++)
				{
					pk::city@ city = cities[iCity];
					pk::building@ building = pk::city_to_building(city);
					if(pk::enemies_around(building))
						continue;
					pk::list<pk::person@> plist = pk::get_idle_person_list(building);
					
					pk::list<pk::person@> targets;
					for(int iPerson=0;iPerson < 미발견리스트.count;iPerson++)
					{
						pk::person@ person = 미발견리스트[iPerson];
						if(person.location != building.get_id())
							continue;
						
						targets.add(person);
					}
					//pk::u8printf("mibun count {}\n",targets.count);
					if(targets.count==0)
						continue;
					
					int preCount = targets.count;
					
					for(int iPerson=0;iPerson < plist.count;iPerson++)
					{
						pk::person@ person = plist[iPerson];
						
						pk::search_cmd_info  ei;
						@ei.base = building;
						@ei.actor = person;
						if(pk::command(ei))
						{
							//한명 발견하면 그만한다, idle 무장을 등용에 사용해야되기 때문.
							if(preCount == 미발견무장수반환(targets))
							{
								//test
								//pk::person@ kunshu = pk::get_person(force.kunshu);
								//string s = pk::format("\x1b[2x{}군\x1b[0x,인재발견",pk::decode(pk::get_name(kunshu)));
								//pk::history_log(kunshu.pos, force.color, pk::encode(s));
								break;
							}
							else
							{
								pk::list<pk::item@> items = getKunshuItem(force);
								if(items0.count != items.count) //아이템 발견.
								{
									pk::item@ item=getNewItem(items0, items);
									if(item!=null) 
									{	
										pk::person@ kunshu = pk::get_person(force.kunshu);
										string s = pk::format("\x1b[2x{}군\x1b[0x,보물 \x1b[2x{}\x1b[0x 발견",pk::decode(pk::get_name(kunshu)),pk::decode(item.name));
										pk::history_log(kunshu.pos, force.color, pk::encode(s));
										items0 = items;
									}
								}
							}
						}
					}//iPerson
				}//icity
			}//iForce			
		}
		
		void update재야등용()
		{
			if (!AI_재야등용)
				return;
			if ((pk::get_elapsed_days() % AI_재야등용_주기) != 0)
			{
				//pk::u8printf("join day return{}\n",pk::get_elapsed_days());
				return;
			}

			pk::list<pk::person@> 재야리스트 = get재야리스트();
			for(int i=0;i<50;i++)
			{
				pk::force@ force = pk::get_force(i);
				if (force==null or !pk::is_alive(force) or !pk::is_normal_force(force) or !pk::is_alive(pk::get_person(force.kunshu)) or force.is_player())
						continue;
				
				pk::list<pk::city@> cities = pk::get_city_list(force);
				for(int iCity=0;iCity<cities.count;iCity++)
				{
					pk::city@ city = cities[iCity];
					pk::building@ building = pk::city_to_building(city);
					if(pk::enemies_around(building))
						continue;

					pk::list<pk::person@> plist = pk::get_idle_person_list(building);
					
					//스탯총합이 가장높은순으로 등용시도
					pk::list<pk::person@> targets;
					for(int iPerson=0;iPerson < 재야리스트.count;iPerson++)
					{
						pk::person@ person = 재야리스트[iPerson];
						if(person.location != building.get_id())
							continue;
						
						targets.add(person);
					}
					if(targets.count==0)
						continue;
					
					
					for(int iPerson=0;iPerson < plist.count;iPerson++)
					{
						pk::person@ person = plist[iPerson];
						
						pk::employ_cmd_info ei;
						@ei.base = building;
						@ei.actor = person;
						@ei.target = targets[0];
						if(pk::command(ei))
						{
							if(targets[0].mibun != 신분_재야)
							{
								pk::person@ kunshu = pk::get_person(force.kunshu);
								string s = pk::format("\x1b[2x{}군\x1b[0x,\x1b[2x{}\x1b[0x 등용",pk::decode(pk::get_name(kunshu)),pk::decode(pk::get_name(targets[0])));
								pk::history_log(kunshu.pos, force.color, pk::encode(s));
								
								targets.remove_at(0);
								if(targets.count == 0)
									break;
							}
						}
					}
				}//icity
			}//iForce
		}//재야등용

		void update사관등용()
		{
			if (!AI_사관등용)
				return;
			if (pk::get_day() != 1)
				return;
			if (pk::get_elapsed_days() < AI_사관등용_금지기간)
				return;

			pk::list<pk::person@> ps = get재야리스트();
			for (int i = 0; i < ps.count; i++)
			{
				pk::person@ p = ps[i];
				Info@ ifo = get재야Info(p);
				if(ifo==null)
					continue;
				if(ifo.city==null || p.location != ifo.city.get_id())
					continue;

				pk::force@ f = ifo.city.get_force_id() != -1 ? pk::get_force(ifo.city.get_force_id()) : null;
				if(f == null)
					continue;
				if(f.is_player())
					continue;

				p.mibun = 신분_일반;
				p.location = ifo.city.get_id();
				p.service = ifo.city.get_id();
				p.district = pk::city_to_building(ifo.city).get_district_id();
				p.loyalty = 100;
				p.update();

				string str = pk::format("\x1b[2x{}군\x1b[0x,\x1b[1x{}\x1b[0x,\x1b[24x{}\x1b[0x 에서 사관등용", getName(f), getName(ifo.p), getName(pk::get_building(ifo.p.service)));
				pk::history_log(ifo.p.get_pos(), f != null ? f.color : 0, pk::encode(str));
			}
		}

		void update포로등용()
		{
			if (!AI_포로자동등용)
				return;
			for (int i = 0; i < 무장_끝; i++)
			{
				pk::person@ person = pk::get_person(i);
				if (person.mibun != 신분_포로)
					continue;
				//멸망세력 포로는 확률로
				if(person.get_force_id() == -1 && !pk::rand_bool(AI_포로자동등용_확률))
					continue;
				if (person.loyalty >= (person.is_player() ? AI_포로자동등용_충성도_유저 : AI_포로자동등용_충성도))
					continue;

				bool b의형제 = false;
				pk::list<pk::person@> 의형제 = pk::get_gikyoudai_list(person);
				if (의형제.count > 0)
				{
					for (int j = 0; j < 의형제.count; j++)
					{
						pk::person@ p = 의형제[j];
						if(p.get_id() == person.get_id())
							continue;
						if(p.get_force_id() != person.get_force_id())
							continue;
						b의형제 = true;
						break;
					}
				}
				if(!AI_포로자동등용_의형제 && b의형제)
					continue;

				bool b부부 = false;
				if (person.spouse >= 0)
				{
					pk::person@ p = pk::get_person(person.spouse);
					if (p != null && p.get_force_id() == person.get_force_id())
						b부부 = true;
				}
				if(!AI_포로자동등용_부부 && b부부)
					continue;

				bool b아버지 = false;
				if (person.father >= 0)
				{
					pk::person@ p = pk::get_person(person.father);
					if (p != null && p.get_force_id() == person.get_force_id())
						b아버지 = true;
				}
				if (!AI_포로자동등용_부친 && b아버지)
					continue;

				bool b어머니 = false;
				if (person.mother >= 0)
				{
					pk::person@ p = pk::get_person(person.mother);
					if (p != null && p.get_force_id() == person.get_force_id())
						b어머니 = true;
				}
				if (!AI_포로자동등용_모친 && b어머니)
					continue;


				pk::building@ b = null;
				if (person.location < 건물_거점끝)
				{
					@b = pk::get_building(person.location);
				}
				else 
				{
					pk::unit@ u = pk::get_unit(person.get_pos());
					@b = u!=null ? pk::get_building(pk::get_person(u.leader).service) : null;
					//pk::printf("포로:{},{},{}\n", getName(person), getNameLeader(u),getName(b));
				}
				if (b == null || (b.facility != 시설_도시 && b.facility != 시설_관문 && b.facility != 시설_항구))
					continue;
				if(b.is_player())
					continue;

				pk::force@ f = pk::get_force(b.get_force_id());
				if(f==null)
					continue;

				bool bPlayer = person.is_player();

				person.mibun = 신분_일반;
				person.service = b.get_id();
				person.location = b.get_id();
				person.district = b.get_district_id();
				person.loyalty = 100;
				person.update();

				string str = pk::format("\x1b[2x{}군\x1b[0x,\x1b[1x{}\x1b[0x,\x1b[24x{}\x1b[0x 에서 포로등용", getName(f), getName(person), getName(b));
				pk::history_log(person.get_pos(), f != null ? f.color : 0, pk::encode(str));
				if (bPlayer)
				{
					str = pk::format("\x1b[1x{}\x1b[0x가 \x1b[2x{}군\x1b[0x으로 배반했습니다.",getName(person),getName(f));
					pk::message_box(pk::encode(str),pk::get_person(무장_문관));
				}
			}
		}

		void update재야자동탐색()
		{
			if (!AI_재야자동탐색)
				return;
			if (pk::get_elapsed_days() < AI_재야자동탐색_금지기간)
				return;

			for (int i = 0; i < 무장_끝; i++)
			{
				pk::person@ person = pk::get_person(i);
				if (person.mibun != 신분_미발견)
					continue;

				pk::building@ b = pk::get_building(person.location);
				if(b == null || b.is_player())
					continue;
				if(!pk::rand_bool(AI_재야자동탐색_확률))
					continue;

				person.mibun = 신분_재야;
				person.update();


				string str = pk::format("\x1b[1x{}\x1b[0x,\x1b[24x{}\x1b[0x 에서 스스로 등장", getName(person), getName(b));
				pk::history_log(person.get_pos(), 0, pk::encode(str));
			}
		}

		Info@ get재야Info(pk::person@ p)
		{
			for (int i = 0; i < _재야리스트.length; i++)
			{
				Info@ ifo = _재야리스트[i];
				if (ifo.p.get_id() == p.get_id())
					return ifo;
			}
			return null;
		}

		array<Info> _재야리스트;
		pk::list<pk::person@> get재야리스트()
		{
			pk::list<pk::person@> 재야리스트;
			for (int i = 0; i < 무장_끝; i++)
			{
				pk::person@ person = pk::get_person(i);
				if (person.mibun != 신분_재야)
					continue;
				재야리스트.add(person);
			}
			재야리스트.sort(function(a, b) {
				int sumA = 0;
				for (int i = 0; i < 무장능력_끝; i++)
					sumA += a.base_stat[i];
				int sumB = 0;
				for (int i = 0; i < 무장능력_끝; i++)
					sumB += b.base_stat[i];

				return sumA > sumB;
			});

			return 재야리스트;
		}


		void callback220(const pk::destroy_info& in info, pk::list<pk::person@>& captured, pk::list<pk::person@>& escaped, bool tactics_bonus)
		{
			prev_callback_220(info, captured, escaped, tactics_bonus);
			if (!AI간의_세력멸망시_모든무장포박)
				return;

			pk::hex_object@ attacker = info.attacker;
			pk::hex_object@ target = info.target;

			int attacker_force_id = attacker.get_force_id();
			int target_force_id = target.get_force_id();
			pk::building@ attacker_building = attacker.get_type_id() == pk::building::type_id ? attacker : null;
			pk::unit@ attacker_unit = attacker.get_type_id() == pk::unit::type_id ? attacker : null;
			pk::building@ target_building = target.get_type_id() == pk::building::type_id ? target : null;
			pk::unit@ target_unit = target.get_type_id() == pk::unit::type_id ? target : null;
			int target_border_radius = pk::is_alive(target_building) and target_building.facility == 시설_도시 ? 2 : 1;
			pk::point attacker_pos = attacker.get_pos();
			pk::point target_pos = target.get_pos();
			bool in_border = pk::is_in_range(target_pos, target_border_radius, attacker_pos);
			bool cant_capture = !pk::is_valid_normal_force_id(attacker_force_id) or !pk::is_valid_normal_force_id(target_force_id);
			bool penalty = pk::get_scenario().difficulty == 난이도_특급 and attacker.is_player() and not target.is_player();
			bool has_hobaku_skill = false;
			int hobaku_chance = 0;

			if (pk::is_alive(target_building) && !info.releasable && !attacker.is_player())
			{
				pk::printf("escaped:{},captured:{}\n",escaped.count,captured.count);

				pk::list<pk::person@> ps = pk::get_person_list(target_building, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반));
				captured.clear();
				for (int i = 0; i < ps.count; i++)
				{
					pk::person@ p = ps[i];
					pk::printf("도망 -> 포박:{}\n", getName(p));
					captured.add(p);
				}
				escaped.clear();
			}
		}


		bool callback111(pk::person@ target, pk::person@ actor, int type, int seed)
		{
			bool b = prev_callback_111(target, actor, type, seed);
			if (!인재등용_AI유리)
				return b;

			bool bPlayer0 = actor != null && actor.is_player();
			bool bPlayer1 = target != null && target.is_player();
			if (!bPlayer0 && !bPlayer1)
				return b;
			if (target != null && target.mibun == 신분_재야)
				return b;
			if (target.mibun == 신분_포로 && target.get_force_id() == -1)
				return b;

			if (bPlayer0 && !bPlayer1) //유저가 등용
			{
				//실패했으면 진행
				if (!b)
					return b;

				//어렵게해서 등용
				return _callback111(target, actor, type, seed, 유저_인재등용_부가수치);
			}
			else if (!bPlayer0 && bPlayer1) //AI가 등용
			{
				//성공했으면 진행
				if (b)
					return b;
				//쉽게해서 등용
				return _callback111(target, actor, type, seed, AI_인재등용_부가수치);
			}

			return b;


		}

		bool _callback111(pk::person@ target, pk::person@ actor, int type, int seed,int off)
		{
			if (!pk::is_alive(target) or !pk::is_alive(actor)) return false;

			// 실행 무장의 군주가 없다면 항상 실패
			pk::person@ actor_kunshu = pk::get_person(pk::get_kunshu_id(actor));
			if (!pk::is_alive(actor_kunshu)) return false;

			// 특별한 관계가 있는지 확인
			pk::bool_bool tuple = func_4b0040(target, actor, type);
			if (tuple.first) return tuple.second;

			int giri = 10;
			if (type != 0) giri = pk::min(15 - target.giri * 2, 10);
			int n = pk::min(func_5c6030(target, actor, type, seed) * giri / 10, 100);

			// 포로처우인 경우
			if (type != 0) return pk::rand_bool(n);

			return (n + off)> pk::rand(100, seed, target.get_id(), actor.get_id(), target.loyalty, actor.stat[무장능력_매력], pk::get_aishou_distance(actor, target.get_id()), 0);
		}

		/**
			목표 무장과 실행 무장 사이에 특별한 관계가 있는지 판단합니다.
			@return 특별한 관계 여부, 등용 성공 여부
		*/
		pk::bool_bool func_4b0040(pk::person@ target, pk::person@ actor, int type)
		{
			int target_force_id = target.get_force_id();
			// 귀환 가능함을 나타냄
			bool is_valid_target_force_id = pk::is_valid_force_id(target_force_id);

			// 목표 무장의 세력이 멸망
			if (type == 2) is_valid_target_force_id = false;

			if (!pk::is_alive(target) or !pk::is_alive(actor)) return pk::bool_bool(true, false);

			int actor_kunshu_id = pk::get_kunshu_id(actor);
			pk::person@ actor_kunshu = pk::get_person(actor_kunshu_id);

			// 실행 무장의 세력에 군주가 없는 경우 항상 실패
			if (!pk::is_alive(actor_kunshu)) return pk::bool_bool(true, false);

			// 목표 무장의 사관 금지 군주가 실행 무장의 군주인 경우 항상 실패
			if (target.banned_kunshu == actor_kunshu_id) return pk::bool_bool(true, false);

			// 목표 무장이 군주인 경우 항상 실패
			if (target.mibun == 신분_군주 and is_valid_target_force_id) return pk::bool_bool(true, false);

			pk::person@ target_gikyoudai = pk::get_person(target.gikyoudai);

			// 목표 무장이 의형제 있음(2인)
			if (pk::is_alive(target_gikyoudai) and @target_gikyoudai != @target)
			{
				// 목표 무장이 의형제와 같은 세력인 경우 항상 실패
				if (is_valid_target_force_id and pk::is_valid_force_id(target_force_id) and target_gikyoudai.get_force_id() == target_force_id) return pk::bool_bool(true, false);
				// 목표 무장이 실행 무장 세력의 군주나 실행 무장과 의형제인 경우 항상 성공
				if (@target_gikyoudai == @actor_kunshu or @target_gikyoudai == @actor) return pk::bool_bool(true, true);
			}

			pk::person@ target_spouse = pk::get_person(target.spouse);

			// 목표 무장이 배우자와 같은 세력인 경우 항상 실패
			if (pk::is_alive(target_spouse))
			{
				if (is_valid_target_force_id and pk::is_valid_force_id(target_force_id) and target_spouse.get_force_id() == target_force_id)
					return pk::bool_bool(true, false);
			}

			pk::list<pk::person@> target_gikyoudai_list = pk::get_gikyoudai_list(target);

			// 목표 무장이 의형제와 같은 세력인 경우 항상 실패
			if (is_valid_target_force_id and pk::is_alive(target_gikyoudai) and pk::is_valid_force_id(target_force_id))
			{
				for (int i = 0; i < target_gikyoudai_list.size; i++)
				{
					if (target_gikyoudai_list[i].get_force_id() == target_force_id)
						return pk::bool_bool(true, false);
				}
			}

			// 목표 무장의 의형제가 다른 세력에 소속되어 있다면 항상 실패
			if (pk::is_alive(target_gikyoudai) and @target_gikyoudai != @target)
			{
				int gikyoudai_force_id = target_gikyoudai.get_force_id();
				if (is_valid_target_force_id or target_force_id != gikyoudai_force_id)
				{
					if (pk::is_valid_force_id(gikyoudai_force_id) and actor_kunshu.get_force_id() != gikyoudai_force_id)
						return pk::bool_bool(true, false);
				}
			}

			// 목표 무장의 배우자가 다른 세력에 소속되어 있다면 항상 실패
			if (pk::is_alive(target_spouse))
			{
				int spouse_force_id = target_spouse.get_force_id();
				if (is_valid_target_force_id or target_force_id != spouse_force_id)
				{
					if (pk::is_valid_force_id(spouse_force_id) and actor_kunshu.get_force_id() != spouse_force_id)
						return pk::bool_bool(true, false);
				}
			}

			// 목표 무장의 배우자가 실행 무장이거나 실행 무장의 군주인 경우 항상 성공
			if (pk::is_alive(target_spouse))
			{
				if (@target_spouse == @actor_kunshu or @target_spouse == @actor)
					return pk::bool_bool(true, true);
			}

			// 목표 무장이 실행 무장의 군주를 혐오하는 경우 항상 실패
			if (pk::is_dislike(target, actor_kunshu_id)) return pk::bool_bool(true, false);

			int actor_id = actor.get_id();

			// 목표 무장이 실행 무장을 혐오하는 경우 항상 실패
			if (pk::is_dislike(target, actor_id)) return pk::bool_bool(true, false);

			int actor_force_id = actor.get_force_id();
			int target_kunshu_id = pk::get_kunshu_id(target);

			if (type == 0)
			{
				// 목표 무장이 실행 무장과 의형제나 부부이거나, 실행 무장의 군주와 의형제나 부부인경우 항상 성공
				if (pk::is_gikyoudai(target, actor_id) or pk::is_gikyoudai(target, actor_kunshu_id) or pk::is_fuufu(target, actor_id) or pk::is_fuufu(target, actor_kunshu_id)) return pk::bool_bool(true, true);

				// 목표 무장의 충성도, 의리 합이 96 이상인 경우 항상 실패
				if (target.loyalty + target.giri >= 96) return pk::bool_bool(true, false);

				// 목표 무장의 의형제가 실행 무장의 세력에 소속되어 있다면 항상 성공
				if (pk::is_alive(target_gikyoudai) and target_gikyoudai.get_force_id() == actor_force_id) return pk::bool_bool(true, true);

				// 목표 무장의 배우자가 실행 무장의 세력에 소속되어 있다면 항상 성공
				if (pk::is_alive(target_spouse) and target_spouse.get_force_id() == actor_force_id) return pk::bool_bool(true, true);

				// 목표 무장이 목표 무장의 군주를 친애한다면 항상 실패
				if (target.mibun != 신분_군주 and pk::is_valid_person_id(target_kunshu_id) and pk::is_like(target, target_kunshu_id)) return pk::bool_bool(true, false);

				// 목표 무장이 실행 무장이나 실행 무장의 군주를 친애한다면 항상 성공
				if (pk::is_like(target, actor_id) or pk::is_like(target, actor_kunshu_id)) return pk::bool_bool(true, true);
			}
			else
			{
				// 목표 무장의 의형제가 실행 무장의 세력에 소속되어 있다면 항상 성공
				for (int i = 0; i < target_gikyoudai_list.size; i++)
				{
					if (target_gikyoudai_list[i].get_force_id() == actor_force_id)
						return pk::bool_bool(true, true);
				}

				// 목표 무장의 배우자가 실행 무장의 세력에 소속되어 있다면 항상 성공
				if (pk::is_alive(target_spouse) and target_spouse.get_force_id() == actor_force_id) return pk::bool_bool(true, true);

				// 목표 무장이 목표 무장의 군주를 친애한다면 항상 실패
				if (is_valid_target_force_id and target.mibun != 신분_군주 and pk::is_valid_person_id(target_kunshu_id) and pk::is_like(target, target_kunshu_id)) return pk::bool_bool(true, false);

				// 목표 무장이 실행 무장의 군주를 친애한다면 항상 성공
				if (pk::is_like(target, actor_kunshu_id)) return pk::bool_bool(true, true);
			}

			return pk::bool_bool(false, false);
		}

		/***/
		int func_5c6030(pk::person@ target, pk::person@ actor, int type, int seed)
		{
			if (!pk::is_alive(target) or !pk::is_alive(actor)) return 0;

			int loyalty = target.loyalty;
			int aishou = 25;
			int giri = target.giri;
			int target_kunshu_id = pk::get_kunshu_id(target);
			int actor_kunshu_id = pk::get_kunshu_id(actor);
			int n = 0;

			if (type == 2)
				loyalty = pk::min(loyalty, 70);

			// 목표 무장이 재야이거나 멸망한 세력의 포로인 경우
			if (target.mibun == 신분_재야 or (target.mibun == 신분_포로 and !pk::is_valid_force_id(target.get_force_id())))
				loyalty = pk::get_scenario().difficulty == 난이도_초급 ? 60 : 70;

			if (pk::is_valid_person_id(target_kunshu_id))
				aishou = pk::get_aishou_distance(target, target_kunshu_id);

			if (target.mibun == 신분_재야)
				giri = 의리_보통;

			n = (aishou - pk::get_aishou_distance(target, actor_kunshu_id)) / 5;
			n -= (giri + 18) * loyalty * 5 / 100;
			n += pk::max(actor.stat[무장능력_매력], 30) * 3 / 5;
			n -= pk::is_like(target, target_kunshu_id) ? 15 : 0;
			n -= pk::is_oyako(target, target_kunshu_id) ? 15 : 0;
			n += pk::is_dislike(target, target_kunshu_id) ? 15 : 0;
			n += pk::rand(의리_끝 - giri, actor.get_id(), target.get_id(), actor.stat[무장능력_매력], seed, actor_kunshu_id, 0, 0);
			n += target.mibun == 신분_포로 ? 15 : 0;
			n += 45;

			return pk::max(n, 0);
		}


		
		string getName(pk::force@ f)
		{
			if (f == null)
				return "null";
			return getName(pk::get_person(f.kunshu));
		}
		string getName(pk::object@ obj)
		{
			return obj != null ? pk::decode(pk::get_name(obj)) : "null";
		}
		string getNameLeader(pk::unit@ obj)
		{
			if (obj == null)
				return "null";
			pk::person@ p = pk::get_person(obj.leader);
			if (p == null)
				return "null";
			return pk::decode(pk::get_name(p));
		}


	}

	Main main;
}


