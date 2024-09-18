/*
@만든이: 크래픽스
@Update: 2023.8.26,최초배포
@Update: 2023.8.27,항구에서 훈련시 기력올라가지 않는문제 수정
@Update: 2023.8.31,AI가 일정확률로 관짐을 구매, AI가 관직공격명령을 내림, 
@Update: 2023.9.1,AI출진시 군주가 우선순위가 낮아지는 버그를 수정.
@Update: 2024.1.31,작위공격명령시 정전시간을 1로 수정
@Update: 2024.3.6,작위구매, 작위공격명령 옵션 추가.
@Update: 2024.5.13,IsAlready 버그수정
@Update: 2024.5.22, 무장편성순서 잘못되는 버그수정
@Update: 2024.5.27, 돈없어도 작위 구매되는 버그수정
@Update: 2024.6.6, 작위 공격명령 행동력 감소
*/

namespace 황제효과_Emperor
{
	

	const int 행동력 = 20;
	const bool 황제_구매_가능 = false;
	const bool 왕_구매_가능 = false;

	const bool 작위구매 = true;
	const bool 작위공격명령 = true;

	const float AI_작위_구매_금_비율 = 0.3; //AI금의 30% 이하로 작위를 구매할수 있을때 구매함.
	const int 유저_작위공격명령_기간 = 360; //1년
	const int AI_작위공격명령_확률 = 5; //5%, 1년에 1~2회 시도

	const int 글씨사이즈 = FONT_BIG;
	//const int 글씨사이즈 = FONT_SMALL;        
	const int 시작위치_가로 = 200;
	const int 시작위치_세로 = 600;

	const bool 음영 = true;
	const int 음영컬러 = 0x40000000;
	const int 음영간격 = 10;



	const bool 황제_추가_금_획득 = true;
	float 황제_추가_금_비율 = 0.5;

	const bool 황제_추가_병량_획득 = true;
	float 황제_추가_병량_비율 = 0.5;

	const bool 황제_추가_기교_획득 = true;
	int 황제_추가_기교 = 100;

	const bool 황제_추가_행동력_획득 = true;
	float 황제_추가_행동력_비율 = 0.5;

	const bool 황제_추가_충성도감소_획득 = true;
	float 황제_추가_충성도감소_비율 = 0.5;

	const bool 황제_추가_치안증가_획득 = true;
	float 황제_추가_치안증가_비율 = 0.5;

	const bool 황제_추가_징병치안증가_획득 = true;
	float 황제_추가_징병치안증가_비율 = 0.5;

	const bool 황제_추가_징병증가_획득 = false;
	float 황제_추가_징병증가_비율 = 0.2;

	const bool 황제_추가_본거지확률_획득 = true;
	float 황제_추가_본거지확률_비율 = 0.5;

	const bool 황제_추가_기력_획득 = true;
	float 황제_추가_기력_비율 = 0.5;


	const bool AI_출진_병기_재고_무시 = true;
	int AI_출진_후_최소병력 = 10000;
	int AI_출진_후_최소병량 = 20000;

	int AI_출진_후_최소병력_관문_항구 = 5000;
	int AI_출진_후_최소병량_관문_항구 = 10000;


	int AI_출진_인접1_병량일수 = 200; //바로인접한 출진시 병량일수
	int AI_출진_인접2_병량일수 = 260; //한단계 건너뛰어서 인접한 경우 출진시 병량 일수
	int AI_출진_인접3_병량일수 = 320; //두단계 건너뛰어서 인접한 경우 출진시 병량 일수


	const array<int> 작위비용 =
	{
		300000,//황제
		250000,//왕
		200000,//공
		150000,//대사마
		100000,//대장군
		60000,//오관중랑장
		40000,//우림중랑장
		20000,//주목
		10000//주자사
	};

	array<int> 누선생산도시 =
	{
		도시_업, 도시_북해, 도시_복양, 도시_평원, 도시_진류, 도시_무릉, 도시_강릉, 도시_강하, 도시_장사, 도시_시상, 도시_여강, 도시_영안, 도시_신야, 도시_수춘,도시_건업, 도시_양양,도시_상용,도시_낙양
	};

	const int KEY = pk::hash("황제효과");

	class ForceInfo
	{
		pk::force@ force;
		int startDay;
		pk::city@ city;
	};

	class AllyInfo
	{
		pk::force@ force0;
		pk::force@ force1;
		int troops0;
		int troops1;
	};

	class AttackInfo
	{
		array<pk::person@> members = { null,null,null };
		int food;
		int troops;
		int money = 0;
		int 병종;
		bool b누선=false;
		bool b투함=false;

	};

	class Main
	{

		pk::func100_t@ prev_callback_100;
		pk::func101_t@ prev_callback_101;
		pk::func104_t@ prev_callback_104;
		pk::func105_t@ prev_callback_105;
		pk::func150_t@ prev_callback_150;
		pk::func151_t@ prev_callback_151;
		pk::func152_t@ prev_callback_152;
		pk::func153_t@ prev_callback_153;
		pk::func155_t@ prev_callback_155;
		pk::func158_t@ prev_callback_158;
		pk::func162_t@ prev_callback_162;

		Main()
		{
			if (작위구매)
			{
				pk::menu_item item;
				item.menu = 105;
				item.pos = 13;
				item.init = pk::building_menu_item_init_t(BuyTitleInit);
				item.is_enabled = pk::menu_item_is_enabled_t(IsBuyTitleEnabled);
				item.get_text = pk::menu_item_get_text_t(GetBuyTitleText);
				item.get_desc = pk::menu_item_get_desc_t(GetBuyTitleDesc);
				item.handler = pk::menu_item_handler_t(BuyTitleHandler);
				pk::add_menu_item(item);
			}

			if (작위공격명령)
			{
				pk::menu_item item관직공격명령;
				item관직공격명령.menu = 103;
				item관직공격명령.pos = 13;
				item관직공격명령.init = pk::building_menu_item_init_t(TitleAttackCommandInit);
				item관직공격명령.is_enabled = pk::menu_item_is_enabled_t(IsTitleAttackCommandEnabled);
				item관직공격명령.get_text = pk::menu_item_get_text_t(GetTitleAttackCommandText);
				item관직공격명령.get_desc = pk::menu_item_get_desc_t(GetTitleAttackCommandDesc);
				item관직공격명령.handler = pk::menu_item_handler_t(TitleAttackCommandHandler);
				pk::add_menu_item(item관직공격명령);
			}



			@prev_callback_100 = cast<pk::func100_t@>(pk::get_func(100));
			pk::reset_func(100);
			pk::set_func(100, pk::func100_t(func100));                // 150 금 수입


			@prev_callback_101 = cast<pk::func101_t@>(pk::get_func(101));
			pk::reset_func(101);
			pk::set_func(101, pk::func101_t(func101));                // 150 금 수입


			@prev_callback_104 = cast<pk::func104_t@>(pk::get_func(104));
			pk::reset_func(104);
			pk::set_func(104, pk::func104_t(func104));                // 150 금 수입

			@prev_callback_105 = cast<pk::func105_t@>(pk::get_func(105));
			pk::reset_func(105);
			pk::set_func(105, pk::func105_t(func105));                // 150 금 수입

			@prev_callback_150 = cast<pk::func150_t@>(pk::get_func(150));
			pk::reset_func(150);
			pk::set_func(150, pk::func150_t(func150));                // 150 금 수입

			@prev_callback_151 = cast<pk::func151_t@>(pk::get_func(151));
			pk::reset_func(151);
			pk::set_func(151, pk::func151_t(func151));                // 151 병량 수입

			@prev_callback_152 = cast<pk::func152_t@>(pk::get_func(152));
			pk::reset_func(152);
			pk::set_func(152, pk::func152_t(func152));                // 152 관문,항구, 금 수입

			@prev_callback_153 = cast<pk::func153_t@>(pk::get_func(153));
			pk::reset_func(153);
			pk::set_func(153, pk::func153_t(func153));                // 153 관문,항구, 병량 수입


			@prev_callback_155 = cast<pk::func155_t@>(pk::get_func(155));
			pk::reset_func(155);
			pk::set_func(155, pk::func155_t(func155));                // 153 관문,항구, 병량 수입

			@prev_callback_158 = cast<pk::func158_t@>(pk::get_func(158));
			pk::reset_func(158);
			pk::set_func(158, pk::func158_t(func158));                // 153 관문,항구, 병량 수입

			@prev_callback_162 = cast<pk::func162_t@>(pk::get_func(162));
			pk::reset_func(162);
			pk::set_func(162, pk::func162_t(func162));                // 행동력

			pk::bind(107, pk::trigger107_t(onNewDay));
			pk::bind(102, pk::trigger102_t(Init));
			pk::bind(105, pk::trigger105_t(SaveData));

			pk::bind(120, pk::trigger120_t(UpdatePerFrame));


		}
		void Init()
		{
			LoadData();
		}

		void LoadData()
		{
			while (_fis.length > 0)
				_fis.removeLast();

			int count = int(pk::load(KEY, 0, 0));
			int loadIndex = 1;
			for (int i = 0; i < count; i++)
			{
				ForceInfo fi;
				@fi.force = pk::get_force(int(pk::load(KEY, loadIndex++, -1)));
				fi.startDay = int(pk::load(KEY, loadIndex++, -1));
				@fi.city= pk::get_city(int(pk::load(KEY, loadIndex++, -1)));
				_fis.insertLast(fi);
			}

			//pk::u8printf("load count {}\n",_moveInfo.length);
		}

		void SaveData(int file_id)
		{
			pk::store(KEY, 0, _fis.length);
			int saveIndex = 1;
			for (int i = 0; i < _fis.length; i++)
			{
				ForceInfo@ mi = _fis[i];
				pk::store(KEY, saveIndex++, mi.force.get_id());
				pk::store(KEY, saveIndex++, mi.startDay);
				pk::store(KEY, saveIndex++, mi.city.get_id());
			}
		}

		void UpdatePerFrame()
		{
			if (_fis.length == 0)
				return;

			int w = 시작위치_가로;
			int h = 시작위치_세로;
			int xMax = -1;

			for (int i = 0; i < _fis.length; i++)
			{
				ForceInfo@ fi = _fis[i];
				string str = pk::format("거점공략:\x1b[2x{}\x1b[0x턴,{}", (fi.startDay + 유저_작위공격명령_기간 - pk::get_elapsed_days()) / 10, pk::decode(pk::get_name(fi.city)));
				int offset = (글씨사이즈 == FONT_BIG ? 30 : 20);


				pk::point point;
				point.x = w;
				point.y = h; h += offset;
				pk::draw_text(pk::encode(str), point, -1, 글씨사이즈, 0x00000000);

				pk::size size0 = pk::get_size(글씨사이즈, pk::encode(str));
				if (size0.width > xMax)
					xMax = size0.width;
			}
			if (음영)
			{
				int off = 음영간격;
				pk::point pt(시작위치_가로 - off, 시작위치_세로 - off);
				pk::rectangle r1(pt, pk::size(xMax + off * 2, h - 시작위치_세로 + off * 2));
				pk::draw_filled_rect(r1, 음영컬러);
			}




		}


		void 황제추가기교()
		{
			if (!황제_추가_기교_획득)
				return;

			pk::list<pk::force@> forces = pk::get_force_list();
			for (int i = 0; i < forces.count; i++)
			{
				pk::force@ force = forces[i];
				if (!pk::is_protecting_the_emperor(force))
					continue;

				force.tp = pk::min(force.tp + 황제_추가_기교, 10000);
				break;
			}
		}
		void AI작위구매()
		{
			if (!작위구매)
				return;
			pk::list<pk::force@> forces = pk::get_force_list();
			for (int i = 0; i < forces.count; i++)
			{
				pk::force@ force = forces[i];
				if (!pk::is_protecting_the_emperor(force))
					continue;
				if(force.is_player())
					continue;

				if (force.title == 작위_황제 || force.title == 작위_왕 || force.title == 작위_공)
					continue;

				int tgold = 작위비용[force.title - 1];
				if(GetGold(force) * AI_작위_구매_금_비율 < tgold)
					continue;

				BuyTitle(force, force.title - 1);

				force.title = force.title - 1;

				pk::person@ kunshu = pk::get_person(force.kunshu);
				pk::title@ title = pk::get_title(force.title);

				string str = pk::format("\x1b[2x{}\x1b[0x, \x1b[2x{}\x1b[0x 작위구매",pk::decode(pk::get_name(kunshu)),pk::decode(pk::get_name(title)));
				pk::history_log(kunshu.get_pos(), force.color, pk::encode(str));
				break;
			}
		}

		array<pk::force@> neighborForces(pk::force@ forceMy)
		{
			array<pk::force@> arr;
			pk::list<pk::force@> forces = pk::get_force_list();
			for (int i = 0; i < forces.count; i++)
			{
				pk::force@ force = forces[i];
				if(forceMy.get_id() == force.get_id())
					continue;

				if (!pk::is_neighbor_force(forceMy, force))
					continue;

				arr.insertLast(force);
			}
			return arr;
		}


		int getTroops(pk::force@ force)
		{
			int troops = 0;
			pk::list<pk::building@> blist = pk::get_building_list();
			for (int i = 0; i < blist.count; i++)
			{
				pk::building@ b = blist[i];
				if (b.get_force_id() != force.get_id())
					continue;

				pk::city@ city = pk::building_to_city(b);
				if (city != null)
				{
					troops += city.troops;
				}
				pk::gate@ gate = pk::building_to_gate(b);
				if (gate != null)
				{
					troops += gate.troops;
				}
				pk::port@ port = pk::building_to_port(b);
				if (port != null)
				{
					troops += port.troops;
				}
			}
			return troops;
		}

		bool isAlready(pk::force@ force)
		{
			for (int i = 0; i < _fis.length; i++)
			{
				pk::force@ force2 = _fis[i].force;
				if (force2.get_id() == force.get_id())
					return true;
			}
			return false;
		}
		
		array<pk::force@> findTargets(pk::force@ forceMy)
		{
			array<pk::force@> forces = neighborForces(forceMy);

			AllyInfo@ maxAlly = null;
			int maxTroops = 0;

			for (int i = 0; i < forces.length-1; i++)
			{
				pk::force@ force0 = forces[i];
				if(!isAlready(force0))
					continue;

				for (int j = i; j < forces.length; j++)
				{
					pk::force@ force1 = forces[j];
					if(!force0.ally[force1.get_id()])
						continue;
					if(!isAlready(force1))
						continue;

					AllyInfo ai;
					@ai.force0 = force0;
					@ai.force1 = force1;
					ai.troops0 = getTroops(force0);
					ai.troops1 = getTroops(force1);

					if (ai.troops0 + ai.troops1 > maxTroops)
					{
						maxTroops = ai.troops0 + ai.troops1;
						@maxAlly = ai;
					}
				}
			}
			return maxAlly != null ? {maxAlly.force0, maxAlly.force1} : array<pk::force@>();
		}

		void breakAlly(pk::force@ force0, pk::force@ force1)
		{
			force0.ally[force1.get_id()] = false;
			force0.relations[force1.get_id()] = 0;
			force0.ceasefire_timer[force1.get_id()] = 1;
			force1.ally[force0.get_id()] = false;
			force1.relations[force0.get_id()] = 0;
			force1.ceasefire_timer[force0.get_id()] = 1;
			force0.update();
			force1.update();
		}

		void AI공격명령()
		{
			if (!작위공격명령)
				return;
			pk::list<pk::force@> forces = pk::get_force_list();
			for (int i = 0; i < forces.count; i++)
			{
				pk::force@ force = forces[i];
				if (!pk::is_protecting_the_emperor(force))
					continue;
				if (force.is_player())
					continue;
				if(!pk::rand_bool(AI_작위공격명령_확률))
					continue;


				array<pk::force@> arr=findTargets(force);
				if(arr.length != 2)
					continue;

				//pk::force@ tmp = arr[0];
				//@arr[0] = arr[1];
				//@arr[1] = tmp;

				pk::city@ city = null;
				@city=GetTargetCity(arr[0], arr[1]);
				if(city == null)
					continue;

				if (arr.length == 2 && !arr[0].is_player() && !arr[1].is_player())
				{
					//공격
					arr[0].title = arr[0].title - 1;
					//외교 동맹이면 동맹 깨고, 친밀도 0으로 수정
					breakAlly(arr[0], arr[1]);
					Attack(arr[0], arr[1]);
				}
				else if (arr.length == 2 && !arr[0].is_player() && arr[1].is_player())
				{
					arr[0].title = arr[0].title - 1;
					//외교 동맹이면 동맹 깨고, 친밀도 0으로 수정

					breakAlly(arr[0], arr[1]);
					Attack(arr[0], arr[1]);

					
					pk::person@ kunshi = pk::get_person(arr[1].gunshi);
					if (kunshi != null) 
					{
						pk::title@ title = pk::get_title(arr[0].title);
						string str = pk::format("\x1b[2x{}\x1b[0x군이 \x1b[2x{}\x1b[0x를 받고 우리를 공격합니다. 동맹도 깨졌습니다.",pk::decode(pk::get_name(arr[0])),pk::decode(pk::get_name(title)));
						pk::message_box(pk::encode(str), kunshi);
					}
				}
				else if (arr.length == 2 && arr[0].is_player())
				{
					@_scene_person = pk::get_person(무장_문관);
					@_scene_attacker = arr[0];
					@_scene_target = arr[1];
					@_scene_city = city;

					pk::scene(pk::scene_t(Scene외교AI));
					if (_scene_result)
					{
						ForceInfo fi;
						@fi.force = arr[0];
						@fi.city = city;
						fi.startDay = pk::get_elapsed_days();
						_fis.insertLast(fi);
						
						
						breakAlly(arr[0], arr[1]);
						string str = pk::format("\x1b[2x{}\x1b[0x 와 \x1b[2x{}\x1b[0x가 동맹이 파기되었습니다.", pk::decode(pk::get_name(pk::get_person(arr[0].kunshu))), pk::decode(pk::get_name(pk::get_person(arr[1].kunshu))));
						pk::message_box(pk::encode(str));
						pk::play_se(10);

						doMerite(arr[0]);
					}
				}
				break;
			}

		}

		void doMerite(pk::force@ force)
		{
			pk::list<pk::person@> persons = pk::get_person_list(force, pk::mibun_flags(신분_태수, 신분_도독, 신분_일반, 신분_포로));
			for (int i = 0; i < persons.count; i++)
			{
				pk::person@ p = persons[i];
				p.loyalty += pk::rand(5);
			}

			force.title = force.title - 1;
			pk::title@ title = pk::get_title(force.title);
			string str = pk::format("\x1b[2x{}\x1b[0x 가 되었습니다.. 모든 무장의 충성도가 증가했습니다.", pk::decode(pk::get_name(title)));

			pk::message_box(pk::encode(str));

		}

		void doPenalty(pk::force@ force)
		{
			pk::list<pk::person@> persons = pk::get_person_list(force, pk::mibun_flags(신분_태수, 신분_도독, 신분_일반, 신분_포로));
			for (int i = 0; i < persons.count; i++)
			{
				pk::person@ p = persons[i];
				p.loyalty -= (pk::rand(5)+5);
			}

			force.title = force.title + 1;
			pk::title@ title = pk::get_title(force.title);
			if (title.get_id() == 작위_없음)
			{
				string str = pk::format("작위가 박탈당했습니다. 모든 무장의 충성도가 하락했습니다.", pk::decode(pk::get_name(title)));
				pk::message_box(pk::encode(str));
			}
			else 
			{
				string str = pk::format("\x1b[2x{}\x1b[0x 로 강등되었습다. 모든 무장의 충성도가 하락했습니다.", pk::decode(pk::get_name(title)));
				pk::message_box(pk::encode(str));
			}

		}

		array<ForceInfo> _fis;
		void 유저거점공략확인()
		{
			array<ForceInfo> removes;
			for (int i = 0; i < _fis.length; i++)
			{
				ForceInfo@ fi = _fis[i];
				if (pk::get_elapsed_days() < fi.startDay + 유저_작위공격명령_기간)
					continue;

				pk::person@ emp = pk::get_person(무장_헌제);
				if (fi.city.get_force_id() == fi.force.get_id())
				{
					pk::message_box(pk::encode("자네가 해낼줄 알았네"), emp);
					doMerite(fi.force);
				}
				else 
				{
					pk::message_box(pk::encode("실망스럽네"), emp);
					doPenalty(fi.force);
				}
				removes.insertLast(fi);
				break;
			}

			for (int i = 0; i < removes.length; i++)
			{
				int index = -1;
				for (int j = 0; j < _fis.length; j++)
				{
					if (removes[i].force.get_id() == _fis[j].force.get_id())
					{
						index = j;
						break;
					}
				}
				if (index != -1)
				{
					//pk::u8printf("remove {},count {}\n",_moveInfo[index].moo.get_id(),_moveInfo.length-1);
					_fis.removeAt(index);
				}
			}
		}

		void onNewDay()
		{
			황제추가기교();
			AI작위구매();
			AI공격명령();
			유저거점공략확인();
		}

		int func100(pk::building@ building, const pk::detail::arrayptr<pk::person@>& in actors)
		{
			int amount = prev_callback_100(building, actors);
			pk::force@ force = pk::get_force(building.get_force_id());
			if (force == null)
				return amount;

			if (황제_추가_징병증가_획득 and pk::is_protecting_the_emperor(force))
				amount = amount + amount * 황제_추가_징병증가_비율;
			return amount;

		}
		int func101(pk::city@ city, const pk::detail::arrayptr<pk::person@>& in actors, int troops)
		{
			int amount = prev_callback_101(city, actors,troops);
			pk::force@ force = pk::get_force(city.get_force_id());
			if (force == null)
				return amount;

			if (황제_추가_징병치안증가_획득 and pk::is_protecting_the_emperor(force))
				amount = amount - amount * 황제_추가_징병치안증가_비율;
			return amount;
		}

		int func104(pk::building@ building, const pk::detail::arrayptr<pk::person@>& in actors)
		{
			int amount = prev_callback_104(building,actors);
			pk::force@ force = pk::get_force(building.get_force_id());
			if (force == null)
				return amount;

			if (황제_추가_치안증가_획득 and pk::is_protecting_the_emperor(force))
				amount = amount + amount * 황제_추가_치안증가_비율;
			return amount;
		}
		int func105(pk::building@ building, const pk::detail::arrayptr<pk::person@>& in actors)
		{
			int amount = prev_callback_105(building, actors);
			pk::force@ force = pk::get_force(building.get_force_id());
			if (force == null)
				return amount;

			if (황제_추가_기력_획득 and pk::is_protecting_the_emperor(force))
				amount = amount + amount * 황제_추가_기력_비율;
			return amount;

		}
		int func150(pk::city@ city)
		{
			int gold = prev_callback_150(city);
			pk::force@ force = pk::get_force(city.get_force_id());
			if (force == null)
				return gold;


			if (황제_추가_금_획득 and pk::is_protecting_the_emperor(force))
				gold = gold + gold * 황제_추가_금_비율;
			return gold;
		}
		int func151(pk::city@ city)
		{
			int food = prev_callback_151(city);
			pk::force@ force = pk::get_force(city.get_force_id());
			if (force == null)
				return food;

			if (황제_추가_병량_획득 and pk::is_protecting_the_emperor(force))
				food = food + food * 황제_추가_병량_비율;
			return food;
		}
		int func152(pk::building@ building, int city_revenue)
		{
			int gold = prev_callback_152(building,city_revenue);
			pk::force@ force = pk::get_force(building.get_force_id());
			if (force == null)
				return gold;

			if (황제_추가_금_획득 and pk::is_protecting_the_emperor(force))
				gold = gold + gold * 황제_추가_금_비율;
			return gold;
		}
		int func153(pk::building@ building, int city_harvest)
		{
			int food = prev_callback_153(building, city_harvest);
			pk::force@ force = pk::get_force(building.get_force_id());
			if (force == null)
				return food;

			if (황제_추가_병량_획득 and pk::is_protecting_the_emperor(force))
				food = food + food * 황제_추가_병량_비율;
			return food;
		}
		int func155(pk::building@ building, pk::person@ person)
		{
			int loyalty = prev_callback_155(building, person);
			pk::force@ force = pk::get_force(building.get_force_id());
			if (force == null)
				return loyalty;

			if (황제_추가_충성도감소_획득 and pk::is_protecting_the_emperor(force) and force.get_id() == person.get_force_id())
			{
				if (person.kanshitsu == 한실_중시)
					loyalty = 0;
				else
					loyalty = pk::max(0.0, loyalty - loyalty * 황제_추가_충성도감소_비율);
			}
			return loyalty;
		}
		int func158(pk::city@ city)
		{
			int ratio = prev_callback_158(city);
			pk::force@ force = pk::get_force(city.get_force_id());
			if (force == null)
				return ratio;

			if (황제_추가_본거지확률_획득 and pk::is_protecting_the_emperor(force))
				ratio = ratio - ratio * 황제_추가_본거지확률_비율;
			return ratio;
		}

		int func162(pk::district@ district)
		{
			int ap = prev_callback_162(district);
			pk::force@ force = pk::get_force(district.get_force_id());
			if (force == null)
				return ap;

			if (황제_추가_행동력_획득 and pk::is_protecting_the_emperor(force))
				ap = ap + ap * 황제_추가_행동력_비율;
			return ap;
		}




		void TitleAttackCommandInit(pk::building@ building)
		{
			@_force = pk::get_force(building.get_force_id());
			@_building = building;
			@_city = pk::building_to_city(building);
			@_district = pk::get_district(building.get_district_id());
		}
		bool IsTitleAttackCommandEnabled()
		{
			return _district.ap >= 행동력 and pk::is_protecting_the_emperor(_force);
		}
		string GetTitleAttackCommandText()
		{
			return pk::encode("작위공격명령");
		}
		string GetTitleAttackCommandDesc()
		{
			if(!pk::is_protecting_the_emperor(_force))
				return pk::encode("황제를 옹립해야 합니다.");
			else if (_district.ap < 행동력)
				return pk::encode(pk::format("행동력이 부족합니다.(행동력{})", 행동력));
			else
				return pk::encode(pk::format("한세력에게 작위를 부여하고 다른세력을 공격하도록 합니다. 행동력{},황제옹립)", 행동력));
		}

		pk::city@ GetTargetCity(pk::force@ attacker, pk::force@ target)
		{
			//인접이 없는세력간의 전투는 없다, 없으면 외교레벨에서 거절한다.

			int maxNeighborCount = -1;
			int maxTroops = -1;
			pk::city@ maxCity = null;

			pk::list<pk::city@> attackerCities = pk::get_city_list(attacker);
			pk::list<pk::city@> targetCities = pk::get_city_list(target);
			for (int i = 0; i < targetCities.count; i++)
			{
				pk::city@ c = targetCities[i];

				int ncount = 0;

				for (int j = 0; j < attackerCities.count; j++)
				{
					pk::city@ c2 = attackerCities[j];
					int dist = pk::get_city_distance(c.get_id(), c2.get_id());
					if (dist == 1)
						ncount++;
				}

				if (ncount > maxNeighborCount or (ncount == maxNeighborCount and c.troops < maxTroops ))
				{
					maxNeighborCount = ncount;
					maxTroops = c.troops;
					@maxCity = c;
				}
			}

			return maxCity;
		}

		bool 특기체크(pk::person@ p, int 병종)
		{
			//구축,용장,패왕,연전,심공등 모든 병종에 관여하는

			if (pk::has_skill(p, 특기_구축) or pk::has_skill(p, 특기_용장) or pk::has_skill(p, 특기_패왕) or pk::has_skill(p, 특기_신장) or
				pk::has_skill(p, 특기_연전) or pk::has_skill(p, 특기_위풍) or pk::has_skill(p, 특기_급습) or pk::has_skill(p, 특기_난전) or
				pk::has_skill(p, 특기_기각) or pk::has_skill(p, 특기_포박) or pk::has_skill(p, 특기_정묘) or pk::has_skill(p, 특기_보좌) or
				pk::has_skill(p, 특기_불굴) or pk::has_skill(p, 특기_금강) or pk::has_skill(p, 특기_철벽) or pk::has_skill(p, 특기_노발) or
				pk::has_skill(p, 특기_강운) or pk::has_skill(p, 특기_혈로) or pk::has_skill(p, 특기_호위) or pk::has_skill(p, 특기_화공) or
				pk::has_skill(p, 특기_언독) or pk::has_skill(p, 특기_기략) or pk::has_skill(p, 특기_궤계) or pk::has_skill(p, 특기_허실) or
				pk::has_skill(p, 특기_묘계) or pk::has_skill(p, 특기_비책) or pk::has_skill(p, 특기_간파) or pk::has_skill(p, 특기_통찰) or
				pk::has_skill(p, 특기_화신) or pk::has_skill(p, 특기_신산) or pk::has_skill(p, 특기_백출) or pk::has_skill(p, 특기_귀모) or
				pk::has_skill(p, 특기_연환) or pk::has_skill(p, 특기_심모) or pk::has_skill(p, 특기_반계) or pk::has_skill(p, 특기_경국) or
				pk::has_skill(p, 특기_요술) or pk::has_skill(p, 특기_귀문) or pk::has_skill(p, 특기_규율) or pk::has_skill(p, 특기_침착) or
				pk::has_skill(p, 특기_명경) or pk::has_skill(p, 특기_주악) or pk::has_skill(p, 특기_시상) or pk::has_skill(p, 특기_축성))
			{
				return true;
			}

			if (병종 == 병종_기병)
			{
				if (pk::has_skill(p, 특기_비장) or pk::has_skill(p, 특기_도주) or pk::has_skill(p, 특기_질주) or pk::has_skill(p, 특기_행군) or
					pk::has_skill(p, 특기_기장) or pk::has_skill(p, 특기_백마) or pk::has_skill(p, 특기_맹장) or pk::has_skill(p, 특기_기신))
				{
					return true;
				}
			}
			else if (병종 == 병종_창병)
			{
				if (pk::has_skill(p, 특기_비장) or pk::has_skill(p, 특기_도주) or pk::has_skill(p, 특기_강행) or pk::has_skill(p, 특기_맹장) or
					pk::has_skill(p, 특기_창장) or pk::has_skill(p, 특기_투신))
				{
					return true;
				}
			}
			else if (병종 == 병종_극병)
			{
				if (pk::has_skill(p, 특기_비장) or pk::has_skill(p, 특기_도주) or pk::has_skill(p, 특기_강행) or pk::has_skill(p, 특기_맹장) or
					pk::has_skill(p, 특기_극장) or pk::has_skill(p, 특기_극신) or pk::has_skill(p, 특기_투신))
				{
					return true;
				}
			}
			else if (병종 == 병종_노병)
			{
				if (pk::has_skill(p, 특기_비장) or pk::has_skill(p, 특기_도주) or pk::has_skill(p, 특기_강행) or pk::has_skill(p, 특기_사수) or
					pk::has_skill(p, 특기_궁장) or pk::has_skill(p, 특기_궁신))
				{
					return true;
				}
			}
			else if (병종 == 병종_병기)
			{
				if (pk::has_skill(p, 특기_비장) or pk::has_skill(p, 특기_도주) or pk::has_skill(p, 특기_강행) or pk::has_skill(p, 특기_사정) or
					pk::has_skill(p, 특기_공성) or pk::has_skill(p, 특기_공신))
				{
					return true;
				}
			}
			//수군은 일단 물이면 무조건 수군처리되니
			//else if (병종 == 병종_수군)
			//{
			//	if (pk::has_skill(p, 특기_추진) or pk::has_skill(p, 특기_조타) or pk::has_skill(p, 특기_수장) or pk::has_skill(p, 특기_수신))
			//	{
			//		return true;
			//	}
			//}
			return false;
		}

		bool Is수군도시(pk::city@ city)
		{
			for (int i = 0; i < 누선생산도시.length; i++)
			{
				if (누선생산도시[i] == city.get_id())
					return true;
			}
			return false;
		}

		bool 병기체크(AttackInfo@ ai, pk::city@ city, int 병종)
		{
			if (!AI_출진_병기_재고_무시 and 병종 == 병종_기병 and city.weapon_amount[병기_군마] < ai.troops)
				return false;
			if (!AI_출진_병기_재고_무시 and 병종 == 병종_창병 and city.weapon_amount[병기_창] < ai.troops)
				return false;
			if (!AI_출진_병기_재고_무시 and 병종 == 병종_극병 and city.weapon_amount[병기_극] < ai.troops)
				return false;
			if (!AI_출진_병기_재고_무시 and 병종 == 병종_노병 and city.weapon_amount[병기_노] < ai.troops)
				return false;

			if (!AI_출진_병기_재고_무시 and 병종 == 병종_병기)
			{
				pk::force@ force = pk::get_force(city.get_force_id());
				if ((pk::has_tech(force, 기교_목수개발) and city.weapon_amount[병기_목수] >= 1) or city.weapon_amount[병기_충차] >= 1 or
					(pk::has_tech(force, 기교_투석개발) and city.weapon_amount[병기_투석] >= 1) or city.weapon_amount[병기_정란] >= 1)
					return true;
				else
					return false;

			}
			//수군은 항상 출진가능하기때문에 return true;
			return true;

		}

		void makeMax병종(AttackInfo@ ai,pk::city@ city,pk::city@ target)
		{
			int max병종 = -1;
			int max적성 = -1;

			//주장 특기,적성과, 부장들의 특기적성으로 인한 , 최대 적성이 같은경우, 마지막것으로 한다
			//부장부터 역순으로 해서, 주장의 적성이 반영되도록, 주장인경우, 통무가 높아서, 일반적으로 특기도 유리할것이다.

			if (ai.members[2] != null)
			{
				pk::person@ p = ai.members[2];
				for (int i = 0; i < 병종_끝; i++)
				{
					//수군도 육상을 선택해야함
					if(i == 병종_수군)
						continue;

					if (p.tekisei[i] > max적성 and 병기체크(ai, city, i))
					{
						max병종 = i;
						max적성 = p.tekisei[i];
					}
					else if (p.tekisei[i] == max적성 and 병기체크(ai, city, i))
					{
						if (특기체크(p, i))
						{
							max병종 = i;
							max적성 = p.tekisei[i];
						}
					}
				}
			}
			if (ai.members[1] != null)
			{
				pk::person@ p = ai.members[1];
				for (int i = 0; i < 병종_끝; i++)
				{
					//수군도 육상을 선택해야함
					if(i == 병종_수군)
						continue;

					if (p.tekisei[i] > max적성 and 병기체크(ai, city, i))
					{
						max병종 = i;
						max적성 = p.tekisei[i];
					}
					else if (p.tekisei[i] == max적성 and 병기체크(ai, city, i))
					{
						if (특기체크(p, i))
						{
							max병종 = i;
							max적성 = p.tekisei[i];
						}
					}
				}
			}
			for (int i = 0; i < 병종_끝; i++)
			{
				//수군도 육상을 선택해야함
				if(i == 병종_수군)
					continue;

				if (ai.members[0].tekisei[i] > max적성 and 병기체크(ai, city, i))
				{
					max병종 = i;
					max적성 = ai.members[0].tekisei[i];
				}
				else if (ai.members[0].tekisei[i] == max적성 and 병기체크(ai, city, i))
				{
					if (특기체크(ai.members[0], i))
					{
						max병종 = i;
						max적성 = ai.members[0].tekisei[i];
					}
				}
			}


			//pk::printf("max 병종 before {}\n",max병종);
			pk::force@ force = pk::get_force(city.get_force_id());
			switch (max병종)
			{
			case 병종_기병:ai.병종 = 병기_군마; break;
			case 병종_노병:ai.병종 = 병기_노; break;
			case 병종_창병:ai.병종 = 병기_창; break;
			case 병종_극병:ai.병종 = 병기_극; break;
			case 병종_병기:
				//사정없든 있든 정란 우선
				if (pk::has_tech(force, 기교_투석개발) and (AI_출진_병기_재고_무시 or city.weapon_amount[병기_투석] >= 1))
					ai.병종 = 병기_투석;
				else if (AI_출진_병기_재고_무시 or city.weapon_amount[병기_정란] >= 1)
					ai.병종 = 병기_정란;
				else if (pk::has_tech(force, 기교_목수개발) and (AI_출진_병기_재고_무시 or city.weapon_amount[병기_목수] >= 1))
					ai.병종 = 병기_목수;
				else if (AI_출진_병기_재고_무시 or city.weapon_amount[병기_충차] >= 1)
					ai.병종 = 병기_충차;
				else
					ai.병종 = 병기_검;
				break;
			default:
				break;
			}

			if (Is수군도시(city) and Is수군도시(target))
			{
				if (pk::has_tech(force, 기교_투석개발) and (AI_출진_병기_재고_무시 or city.weapon_amount[병기_투함] >= 1))
					ai.b투함 = true;
				else if (AI_출진_병기_재고_무시 or city.weapon_amount[병기_누선] >= 1)
					ai.b누선 = true;

			}
			return;
		}
		bool Has사정(AttackInfo@ ai)
		{
			if (pk::has_skill(ai.members[0], 특기_사정))
				return true;
			if (ai.members[1] != null and pk::has_skill(ai.members[1], 특기_사정))
				return true;
			if (ai.members[2] != null and pk::has_skill(ai.members[2], 특기_사정))
				return true;
			return false;
		}


		int GetFood(pk::building@ building)
		{
			pk::city@ c = pk::building_to_city(building);
			if(c!=null)
				return c.food;
			pk::gate@ g = pk::building_to_gate(building);
			if (g != null)
				return g.food;
			pk::port@ p = pk::building_to_port(building);
			if (p != null)
				return p.food;
			return 0;
		}
		int GetTroops(pk::building@ building)
		{
			pk::city@ c = pk::building_to_city(building);
			if (c != null)
				return c.troops;
			pk::gate@ g = pk::building_to_gate(building);
			if (g != null)
				return g.troops;
			pk::port@ p = pk::building_to_port(building);
			if (p != null)
				return p.troops;
			return 0;
		}
		int GetGold(pk::force@ force)
		{
			int gold = 0;
			pk::list<pk::building@> blist = pk::get_building_list();
			for (int i = 0; i < blist.count; i++)
			{
				pk::building@ b = blist[i];
				if (b.get_force_id() != force.get_id())
					continue;

				pk::city@ city = pk::building_to_city(b);
				if (city != null)
				{
					gold += city.gold;
				}
				pk::gate@ gate = pk::building_to_gate(b);
				if (gate != null)
				{
					gold += gate.gold;
				}
				pk::port@ port = pk::building_to_port(b);
				if (port != null)
				{
					gold += port.gold;
				}
			}
			return gold;
		}

		array<AttackInfo> Attack1Neighbor(pk::building@ attacker, pk::city@ target)
		{
			return Attack(attacker, target, AI_출진_인접1_병량일수);
		}
		array<AttackInfo> Attack2Neighbor(pk::building@ attacker, pk::city@ target)
		{
			return Attack(attacker, target, AI_출진_인접2_병량일수);
		}
		array<AttackInfo> Attack(pk::building@ attacker, pk::city@ target, int foodDay)
		{
			//아이들 무장으로 하면, 혹시 없거나
			pk::list<pk::person@> persons = pk::get_idle_person_list(attacker);
			if (persons.count == 0)
				return array<AttackInfo>();


			//주장급선출
			persons.sort(function(a, b) {
				if (a.mibun == 신분_군주)
					return true;
				if (b.mibun == 신분_군주)
					return false;
				if (a.rank != b.rank)
					return a.rank < b.rank;
				if (a.max_stat[무장능력_통솔] != b.max_stat[무장능력_통솔])
					return a.max_stat[무장능력_통솔] > b.max_stat[무장능력_통솔];
				return a.max_stat[무장능력_무력] >= b.max_stat[무장능력_무력];
			});

			int minFood = AI_출진_후_최소병량;
			if (attacker.get_type_id() == 7 || attacker.get_type_id() == 8)
				minFood = AI_출진_후_최소병량_관문_항구;

			int minTroops = AI_출진_후_최소병력;
			if (attacker.get_type_id() == 7 || attacker.get_type_id() == 8)
				minTroops = AI_출진_후_최소병력_관문_항구;

			//주장선출
			array<AttackInfo> infos;
			int foods = GetFood(attacker);
			int troops = GetTroops(attacker);
			do
			{
				AttackInfo ai;

				int troop = pk::get_command(persons[0]);
				int food = troop / 100.0 * foodDay;
				if (food > foods or foods - food < minFood)
					break;
				if (troop > troops or troops - troop < minTroops)
					break;

				//pk::printf("tr {}/{}, food {}/{}\n",troop,troops,food,foods);

				troops -= troop;
				foods -= food;
				@ai.members[0] = persons[0];
				ai.troops = troop;
				ai.food = food;
				persons.remove_at(0);
				infos.insertLast(ai);

			} while (persons.count > 0);

			//두번째 무장선출,세번째 무장선출
			//전투특기가 있으면 일단 무특기보다 우선한다.
			if (persons.count >= 2)
				persons.sort(function(a, b) {

				bool aSkill = false;
				for (int i = 0; i < 특기_시상; i++)
				{
					if (pk::has_skill(a, i))
					{
						aSkill = true;
						break;
					}
				}
				bool bSkill = false;
				for (int i = 0; i < 특기_시상; i++)
				{
					if (pk::has_skill(b, i))
					{
						bSkill = true;
						break;
					}
				}

				if (aSkill != bSkill)
					return aSkill ? true : false;
				if (a.stat[무장능력_무력] != b.stat[무장능력_무력])
					return a.stat[무장능력_무력] >= b.stat[무장능력_무력];
				return a.stat[무장능력_통솔] >= b.stat[무장능력_통솔];

			});

			int index = 0;
			while (persons.count > 0 and index < infos.length)
			{
				AttackInfo@ ai = infos[index++];
				@ai.members[1] = persons[0];
				persons.remove_at(0);
			}

			index = 0;
			while (persons.count > 0 and index < infos.length)
			{
				AttackInfo@ ai = infos[index++];
				@ai.members[2] = persons[0];
				persons.remove_at(0);
			}

			return infos;
		}

		pk::unit@ CreateUnit(AttackInfo ai,pk::point pt)
		{


			//ai.food = 20000;



			//pk::march_cmd_info mi;
			//@mi.base = pk::get_building(ai.members[0].service);
			//mi.type = 부대종류_전투;
			//mi.gold = 0;
			//mi.food = ai.food;
			//mi.troops = ai.troops;
			//for(int i=0;i<12;i++)
			//{
			//	mi.weapon_amount[i] = 0;
			//}
			//mi.weapon_id[0] = ai.병종;
			int mount = ai.troops;
			//ai.병종 = 병기_창;
			//switch(ai.병종)
			//{
			//	case 병기_검:
			//	case 병기_창:
			//	case 병기_극:
			//	case 병기_노:
			//	case 병기_군마:
			//		mount =	ai.troops ;break;
			//	case 병기_충차:
			//	case 병기_정란:
			//	case 병기_투석:
			//	case 병기_목수:
			//		mount = 1;
			//}

			//mi.weapon_amount[0] = mount;
			//
			//mi.member[0] = ai.members[0].get_id();
			//if(ai.members[1]!=null)
			//	mi.member[1] =	ai.members[1].get_id();
			//else
			//	mi.member[1] = -1;
			//if(ai.members[2]!=null)
			//	mi.member[2] =	ai.members[2].get_id();
			//else
			//	mi.member[2] = -1;
			//
			//pk::printf("before command {} {}\n",ai.병종,mount);
			//int uid = pk::command(mi);
			//pk::printf("after command {} {}\n",ai.병종,mount);
			//return pk::get_unit(uid);

			int 수군 = 병기_주가;
			if(ai.b투함)
				수군 = 병기_투함;
			else if(ai.b누선)
				수군 = 병기_누선;


			return pk::create_unit(pk::get_building(ai.members[0].service), ai.members[0], ai.members[1], ai.members[2],mount,ai.병종,수군,0,ai.food, pt);
			//return pk::create_unit(pk::get_building(ai.members[0].service), ai.members[0], null, null,mount,ai.병종,-1,0,ai.food, pk::get_building(ai.members[0].service).get_pos());
			//return pk::create_unit(pk::get_building(ai.members[0].service), ai.members[0], null, null,mount,ai.병종,수군,0,ai.food, pt);
		}

		void March(pk::city@ city,pk::city@ target, array<AttackInfo> infos)
		{
			array<AttackInfo> infos2;
			for (int i = 0; i < infos.length; i++)
			{
				infos2.insertLast(infos[i]);
			}

			pk::force@ force = pk::get_force(city.get_force_id());
			int dist = 1;
			while (infos2.length > 0)
			{
				for (int i = 0; i < 방향_끝; i++)
				{
					pk::point pt = pk::get_neighbor_pos(city.get_pos(), i, dist);

					if (pk::get_hex_object(pt) == null)
					{
						AttackInfo@ ai = infos2[0];
						city.food -= ai.food;
						city.troops -= ai.troops;
						makeMax병종(ai,city, target);
						if (!AI_출진_병기_재고_무시 and ai.병종 != 병기_검)
						{
							if (ai.병종 != 병기_충차 and ai.병종 != 병기_정란 and ai.병종 != 병기_목수 and ai.병종 != 병기_투석 and ai.병종 != 병기_누선 and ai.병종 != 병기_투함)
								city.weapon_amount[ai.병종] = city.weapon_amount[ai.병종]-ai.troops;
							else
								city.weapon_amount[ai.병종]=city.weapon_amount[ai.병종]-1;
						}
						if (!AI_출진_병기_재고_무시 and Is수군도시(city) and Is수군도시(target))
						{
							if (pk::has_tech(force, 기교_투석개발) and city.weapon_amount[병기_투석] >= 1)
								city.weapon_amount[병기_투석]=city.weapon_amount[병기_투석]-1;
							else if(city.weapon_amount[병기_누선] >= 1)
								city.weapon_amount[병기_누선]=city.weapon_amount[병기_누선]-1;
						}



						pk::unit@ unit=CreateUnit(infos2[0],pt);
						pk::set_order(unit, 부대임무_정복, target.get_pos());
						infos2.removeAt(0);

						array<pk::point> tmp = {pt};
						pk::set_pos(unit, pt);
						if (infos2.length == 0)
							break;
					}

				}
				dist++;
			}
		}

		void Attack(pk::force@ attacker, pk::force@ target)
		{
			//타겟도시중 공격도시와 인접이 가장 많고, 약한 순으로 공격,1인접도시는 공격,  2인접 도시는 원군 보냄. 3인접이상 도시부터는 암것두 안함

			pk::city@ targetCity = GetTargetCity(attacker, target);

			pk::list<pk::building@> buildings = pk::get_building_list();

			array<AttackInfo> infos;

			int totalTroops = 0;
			for (int i = 0; i < buildings.count; i++)
			{
				pk::building@ b = buildings[i];
				pk::city@ c = pk::building_to_city(b);
				if(c==null)
					continue;
				if(c.get_force_id() != attacker.get_id())
					continue;

				pk::building@ b2 = pk::city_to_building(targetCity);
				int dist = pk::get_building_distance(b.get_id(), b2.get_id());
				pk::printf("dist {},{}->{}\n",dist, pk::decode(pk::get_name(b)),pk::decode(pk::get_name(b2)));
				if (dist == 1)
				{
					array<AttackInfo> infos2 = Attack1Neighbor(b, targetCity);
					for (int j = 0; j < infos2.length; j++)
					{
						infos.insertLast(infos2[j]);
					}

					March(c, targetCity,infos2);
				}
				else if (dist == 2 || dist == 3)
				{
					//array<AttackInfo> infos2 = Attack2Neighbor(b, targetCity);
					array<AttackInfo> infos2 = Attack(b, targetCity, dist == 2 ? AI_출진_인접2_병량일수 : AI_출진_인접3_병량일수);
					for (int j = 0; j < infos2.length; j++)
					{
						infos.insertLast(infos2[j]);
					}

					March(c,targetCity, infos2);
				}
			}

		}
		pk::person@ _scene_person = null;
		pk::force@ _scene_attacker = null;
		pk::force@ _scene_target = null;
		pk::city@ _scene_city = null;
		bool _scene_result = false;
		void Scene외교()
		{
			pk::person@ kunshu = pk::get_person(_scene_attacker.kunshu);
			pk::person@ gunshi = pk::get_person(_scene_attacker.gunshi);
			pk::diplomacy(_scene_person,kunshu, gunshi,pk::diplomacy_t(외교));
		}
		void 외교()
		{
			pk::person@ kunshu = pk::get_person(_scene_attacker.kunshu);
			pk::person@ kunshu2 = pk::get_person(_scene_target.kunshu);

			pk::title@ title = pk::get_title(_scene_attacker.title - 1);

			pk::message_box(pk::encode(pk::format("\x1b[2x{}\x1b[0x를 \x1b[2x{}\x1b[0x에 임명하노라. 역적 \x1b[2x{}\x1b[0x를 토벌하라",pk::decode(pk::get_name(kunshu)),pk::decode(title.name),pk::decode(pk::get_name(kunshu2)))), _scene_person);

			if (pk::is_neighbor_force(_scene_attacker, _scene_target))
			{
				pk::message_box(pk::encode("알겠습니다."), kunshu);
				_scene_result = true;
			}
			else
			{
				pk::message_box(pk::encode("국경을 접하지 않아 어렵소"),kunshu);
				_scene_result = false;
			}
		}


		void Scene외교AI()
		{
			pk::person@ kunshu = pk::get_person(_scene_attacker.kunshu);
			pk::person@ gunshi = pk::get_person(_scene_attacker.gunshi);
			pk::diplomacy(_scene_person, kunshu, gunshi, pk::diplomacy_t(외교AI));
		}
		void 외교AI()
		{
			pk::person@ kunshu = pk::get_person(_scene_attacker.kunshu);
			pk::person@ kunshu2 = pk::get_person(_scene_target.kunshu);

			pk::title@ title = pk::get_title(_scene_attacker.title - 1);


			string str = pk::format("\x1b[2x{}\x1b[0x를 \x1b[2x{}\x1b[0x에 임명하노라. 역적 \x1b[2x{}\x1b[0x의 도시 \x1b[2x{}\x1b[0x를 \x1b[2x{}\x1b[0x개월내에 토벌하라\n", 
				pk::decode(pk::get_name(kunshu)), pk::decode(title.name), pk::decode(pk::get_name(kunshu2)),pk::decode(pk::get_name(_scene_city)), 유저_작위공격명령_기간 / 30);
			if (pk::yes_no(pk::encode(str)))
			{
				pk::message_box(pk::encode("알겠습니다."), kunshu);
				_scene_result = true;
			}
			else 
			{
				pk::message_box(pk::encode("거절하겠습니다."), kunshu);
				_scene_result = false;
			}
		}


		bool TitleAttackCommandHandler()
		{
			pk::list<pk::force@> forceAttack = pk::force_selector(pk::encode("세력선택"), pk::encode("작위를 부여할 세력을 선택합니다."),pk::get_force_list(), 1, 1);
			if (forceAttack.count == 0)
				return true;
			if (forceAttack[0].kokugou == 국호_황건)
			{
				pk::message_box(pk::encode("황건 세력은 관직을 부여할 수 없습니다."));
				return true;
			}
			pk::list<pk::force@> forceTarget= pk::force_selector(pk::encode("세력선택"), pk::encode("토벌할 세력을 선택합니다."),pk::get_force_list(), 1, 1);
			if (forceTarget.count == 0)
				return true;
			if(forceAttack[0].get_id() == forceTarget[0].get_id())
			{
				pk::message_box(pk::encode("같은 세력입니다."));
				return true;
			}

			pk::list<pk::person@> persons= pk::person_selector(pk::encode("무장선택"), pk::encode("외교를 수행할 무장을 선택합니다."), pk::get_idle_person_list(_building), 1, 1);
			if (persons.count == 0)
				return true;

			pk::string str = pk::format("\x1b[2x{}\x1b[0x 에게 \x1b[2x{}\x1b[0x를 토벌하라고 명령합니까?", pk::decode(pk::get_name(forceAttack[0])), pk::decode(pk::get_name(forceTarget[0])));
			if (!pk::yes_no(pk::encode(str)))
				return true;

			persons[0].action_done = true;
			@_scene_person = persons[0];
			@_scene_attacker = forceAttack[0];
			@_scene_target = forceTarget[0];

			_district.ap = pk::max(_district.ap - 행동력, 0);

			pk::scene(pk::scene_t(Scene외교));
			if (_scene_result)
			{
				int newTitle = forceAttack[0].title - 1;

				//공격
				forceAttack[0].title = newTitle;
				//외교 동맹이면 동맹 깨고, 친밀도 0으로 수정

				breakAlly(forceAttack[0], forceTarget[0]);


				Attack(forceAttack[0], forceTarget[0]);

				string str22 = pk::format("\x1b[2x{}\x1b[0x 와 \x1b[2x{}\x1b[0x가 동맹이 파기되었습니다.", pk::decode(pk::get_name(pk::get_person(forceAttack[0].kunshu))), pk::decode(pk::get_name(pk::get_person(forceTarget[0].kunshu))));
				pk::message_box(pk::encode(str));
				pk::play_se(10);
				return true;
			}
			else
			{
				pk::play_se(13);
				return true;
			}

		}


		pk::force@ _force;
		pk::building@ _building;
		pk::city@ _city;
		pk::district@ _district;
		void BuyTitleInit(pk::building@ building)
		{
			@_force = pk::get_force(building.get_force_id());
			@_building = building;
			@_city = pk::building_to_city(building);
			@_district = pk::get_district(building.get_district_id());
		}
		bool IsBuyTitleEnabled()
		{
			return _district.ap >= 행동력 and pk::is_protecting_the_emperor(_force);
		}
		string GetBuyTitleText()
		{
			return pk::encode("작위구매");
		}
		string GetBuyTitleDesc()
		{
			if(!pk::is_protecting_the_emperor(_force))
				return pk::encode("황제를 옹립해야 합니다.");
			else if (_district.ap < 행동력)
				return pk::encode(pk::format("행동력이 부족합니다.(행동력{})", 행동력));
			else
				return pk::encode(pk::format("작위를 구매합니다.(행동력{},황제옹립)", 행동력));
		}

		string GetTitleName(int i)
		{
			string strTitle;
			switch (i)
			{
			case 작위_황제:strTitle = "황제"; break;
			case 작위_왕:strTitle = "왕"; break;
			case 작위_공:strTitle = "공"; break;
			case 작위_대사마:strTitle = "대사마"; break;
			case 작위_대장군:strTitle = "대장군"; break;
			case 작위_오관중랑장:strTitle = "오관중랑장"; break;
			case 작위_우림중랑장:strTitle = "우림중랑장"; break;
			case 작위_주목:strTitle = "주목"; break;
			case 작위_주자사:strTitle = "주자사"; break;
			default:
				break;
			}

			return strTitle;
		}

		

		bool BuyTitle(pk::force@ force, int title)
		{
			int titleGold = 작위비용[title];

			int gold = GetGold(force);
			if (gold < titleGold)
			{
				pk::message_box(pk::encode("금이 부족합니다."));
				return false;
			}

			pk::list<pk::building@> blist = pk::get_building_list();
			int gold2 = 0;
			for (int i = 0; i < blist.count; i++)
			{
				pk::building@ b = blist[i];
				if(force.get_id() != b.get_force_id())
					continue;

				pk::city@ c = pk::building_to_city(b);
				if (c != null)
				{
					int m0 = titleGold * float(c.gold) / float(gold);
					c.gold -= m0;
					gold2 += m0;
				}
				pk::gate@ g = pk::building_to_gate(b);
				if (g != null)
				{
					int m0 = titleGold * float(g.gold) / float(gold);
					g.gold -= m0;
					gold2 += m0;
				}
				pk::port@ p = pk::building_to_port(b);
				if (p != null)
				{
					int m0 = titleGold * float(p.gold) / float(gold);
					p.gold -= m0;
					gold2 += m0;
				}
			}

			//pk::printf("{}/{} ,{}/{}, {}/{}\n",gold2,item.gold,food2,item.food,troops2,item.troops);
			return true;
		}

		bool BuyTitleHandler()
		{

			while(true)
			{
				int si = 0;
				int title_index = -1;
				int gold = GetGold(_force);
				while (true)
				{
					array<string> itemArr;
					int count = pk::min(작위비용.length, si + 4);
					if (si == 0)
						itemArr.insertLast(pk::encode("종료"));
					else
						itemArr.insertLast(pk::encode("뒤로"));

					for (int i = si; i < count; i++)
					{
						string str;
						string strTitle = GetTitleName(i);
						str = pk::format("{},금{}", strTitle, 작위비용[i]);
						itemArr.insertLast(pk::encode(str));
					}

					if (si + 4 >= 작위비용.length)
						itemArr.insertLast(pk::encode("종료"));
					else
						itemArr.insertLast(pk::encode("다음"));


					int choose2 = pk::choose(pk::encode(pk::format("작위를 선택해주십시오. 현재 금{}",gold)), itemArr);
					if (choose2 == itemArr.length - 1)
					{
						si = si + 4;
						if (si >= 작위비용.length)
							return true;
					}
					else if (choose2 == 0)
					{
						si = si - 4;
						if (si < 0)
							return true;
					}
					else
					{
						title_index = si + choose2 - 1;
						break;
					}
				}

				if (title_index == -1)
					continue;
				if (!황제_구매_가능 and title_index == 작위_황제)
				{
					pk::message_box(pk::encode("황제는 구매할 수 없습니다."));
					continue;
				}
				if (!왕_구매_가능 and title_index == 작위_왕)
				{
					pk::message_box(pk::encode("왕은 구매할 수 없습니다."));
					continue;
				}

				if (title_index >= _force.title)
				{
					pk::message_box(pk::encode("이미 획득한 작위입니다."));
					continue;
				}
				if (_force.title - title_index > 1)
				{
					pk::message_box(pk::encode(pk::format("{} 만 가능합니다.",GetTitleName(_force.title - 1))));
					continue;
				}

				string str = pk::format("금 {} -> {}, 진행합니까?", gold, gold - 작위비용[title_index]);
				if(!pk::yes_no(pk::encode(str)))
					continue;

				if (BuyTitle(_force, title_index))
				{
					_force.title = title_index;
					pk::play_se(10);
				}
				
			}


			return true;
		}
	}
	Main main;
}

