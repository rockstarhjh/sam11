/*
@만든이: 크래픽스
@Update: 2024.5.25최초배포
@Update: 2024.5.28 위임관련버그수정
@Update: 2024.6.1 불지형 관련 예외처리
@Update: 2024.6.17 에러수정
@Update: 2024.8.17 공석투석 데미지 옵션 추가.
@Update: 2024.8.19 공석투석 거점내구도 중첩 방지,기교_벽력처리
*/
namespace AI강제전법사용_AIForceAttack
{
	const int 전법실패시_일반공격_확률 = 30;
	const int 전법실패시_일반공격_무데미지_확률 = 30;
	const int 전법실패시_반격만_확률 = 40;


	const int 자동공격_화시_부상확률 = 5;
	const bool 자동공격_전법교차사용 = true; //기마책사님 야전부대전법확장 연계
	const bool 사거리_패치 = true;
	const int 연전_딜레이 = 1000;//ms
	const int 전법_일기토_확률 = 5;

	const int 자동공격_확률 = 60; //20%는 기존 AI한테 맡깁니다. 

	const int 자동공격_나선첨_확률 = 50;
	const int 자동공격_이단첨_확률 = 50; //실제 25%

	const int 자동공격_돌격_확률 = 50; 
	const int 자동공격_돌파_확률 = 50; //실제 25%
	const int 자동공격_돌진_확률 = 50; //실제 12.5%

	const int 자동공격_함선_화시 = 70;

	const float 공성투석_내구도_데미지_비율 = 1.5;
	const float 공석투석_병력_데미지_비율 = 1.5;

	const bool 콘솔_로그_표시 = true; //문제 대응시 대응할 수 있게 켜두세요.



	//수정하지 마세요 //////////////////////////////////////////////////////

	const int 유닛_전법_근접공격 = 0;
	const int 유닛_전법_활공격 = 1;
	const int 유닛_전법_돌출 = 2;
	const int 유닛_전법_나선첨 = 3;
	const int 유닛_전법_이단첨 = 4;
	const int 유닛_전법_갈퀴 = 5;
	const int 유닛_전법_횡치 = 6;
	const int 유닛_전법_선풍 = 7;
	const int 유닛_전법_화시 = 8;
	const int 유닛_전법_관시 = 9;
	const int 유닛_전법_난사 = 10;
	const int 유닛_전법_돌격 = 11;
	const int 유닛_전법_돌파 = 12;
	const int 유닛_전법_돌진 = 13;
	const int 유닛_전법_화시_병기 = 14;
	const int 유닛_전법_파쇄_병기 = 15;
	const int 유닛_전법_방사_병기 = 16;
	const int 유닛_전법_투석_병기 = 17;
	const int 유닛_전법_근접공격_함선 = 18;
	const int 유닛_전법_활공격_함선 = 19;
	const int 유닛_전법_화시_함선 = 20;
	const int 유닛_전법_투석_함선 = 21;
	const int 유닛_전법_격돌_함선 = 22;
	const int 유닛_전법_나선첨당함 = 23;
	const int 유닛_전법_근접공격당함 = 24;
	const int 유닛_전법_일제공격당함 = 25;
	const int 유닛_전법_활공격당함 = 26;
	const int 유닛_전법_돌출_이단첨당함 = 27;
	const int 유닛_전법_돌격_돌진당함 = 28;
	const int 유닛_전법_돌격_돌출당함_1타겟 = 29;
	const int 유닛_전법_돌격_갈퀴당함 = 30;
	const int 유닛_전법_돌격_돌파당함 = 31;
	const int 유닛_전법_돌격_투석당함 = 32;

	const bool 크리티컬_원거리 = true;
	const bool 크리티컬_근접 = false;


	class Main
	{

		pk::func203_t@ prev_callback_203기병전법사망;
		pk::func210_t@ prev_callback_210;
		pk::func202_t@ callback202;
		pk::func201_t@ callback201;
		pk::func209_t@ callback209;
		pk::func222_t@ prev_callback_222;
		pk::func221_t@ prev_callback_221;
		pk::func200_t@ callback200;

		pk::func262_t@ prev_callback_262;


		Main()
		{
			pk::bind(111, pk::trigger111_t(onTurn));
			pk::bind(112, pk::trigger112_t(onTurnEnd));


			@prev_callback_203기병전법사망 = cast<pk::func203_t@>(pk::get_func(203));
			@prev_callback_210 = cast<pk::func210_t@>(pk::get_func(210));
			@callback202 = cast<pk::func202_t@>(pk::get_func(202));
			@callback201 = cast<pk::func201_t@>(pk::get_func(201));
			@callback209 = cast<pk::func209_t@>(pk::get_func(209));
			@callback200 = cast<pk::func200_t@>(pk::get_func(200));
			@prev_callback_222 = cast<pk::func222_t@>(pk::get_func(222));
			@prev_callback_221 = cast<pk::func221_t@>(pk::get_func(221));


			//pk::menu_item item자동공격;
			//item자동공격.menu = 1;
			//item자동공격.pos = 10;
			//item자동공격.init = pk::unit_menu_item_init_t(init);
			//item자동공격.get_text = pk::menu_item_get_text_t(Get자동공격Text);
			//item자동공격.get_desc = pk::menu_item_get_desc_t(Get자동공격Desc);
			//item자동공격.is_visible = pk::menu_item_is_visible_t(IsVisible자동공격);
			//item자동공격.get_targets = pk::unit_menu_item_get_targets_t(GetTargets자동공격);
			//item자동공격.get_chance = pk::unit_menu_item_get_chance_t(GetChance자동공격);
			//item자동공격.handler = pk::unit_menu_item_handler_t(자동공격Handler);
			//pk::add_menu_item(item자동공격);

		}

		int _count = 0;
		bool callback262(pk::unit@ u)
		{
			if (!pk::is_player_controlled(u) && 자동공격Handler(u)) 
			{
				_count++;
				return true;
			}
			return false;
		}

		void onTurn(pk::force@ force)
		{
			if (force.is_player())
				return;

			@prev_callback_262 = cast<pk::func262_t@>(pk::get_func(262));
			pk::reset_func(262);
			pk::set_func(262, pk::func262_t(callback262));

			pk::list<pk::unit@> us = pk::get_unit_list(force);
			for (int i = 0; i < us.count; i++)
			{
				if(!us[i].action_done && us[i].status == 부대상태_통상)
					pk::run_order(us[i]);
				//if (자동공격Handler(us[i]))
				//{
				//	count++;
				//	_완료리스트.add(us[i]);
				//}
			}

			pk::reset_func(262);
			if(prev_callback_262!=null)
				pk::set_func(262, prev_callback_262);


			if(콘솔_로그_표시 && us.count > 0)
				pk::printf("자동:{},{}/{}\n", getName(force != null ? pk::get_person(force.kunshu) : null), _count, us.count);
		}

		void onTurnEnd(pk::force@ force)
		{
			_count = 0;
			for (int i = 0; i < _scene_attackerUnits.count; i++)
			{
				@_scene_attackerUnit = _scene_attackerUnits[i];
				@_scene_targetUnit = _scene_targetUnits[i];
				@_scene_attacker = _scene_attackers[i];
				@_scene_target = _scene_targets[i];

				if (_scene_attackerUnit != null && pk::is_alive(_scene_targetUnit) && pk::is_alive(_scene_attackerUnit) && pk::is_alive(_scene_attacker) && pk::is_alive(_scene_target) &&
					pk::is_unitize(_scene_attacker) && pk::is_unitize(_scene_target))
				{
					if (force.is_player())
					{
						pk::message_box(pk::encode("적장을 찾았다"), _scene_attacker);
						pk::message_box(pk::encode("좋다 후회하게 될것이다"), _scene_target);
					}
					pk::scene(pk::scene_t(scene_일기토));
					@_scene_attackerUnit = null;
					@_scene_targetUnit = null;
					@_scene_attacker = null;
					@_scene_target = null;
				}
			}
			while (_scene_targets.count > 0)
				_scene_targets.remove_at(0);
			while (_scene_attackers.count > 0)
				_scene_attackers.remove_at(0);
			while (_scene_attackerUnits.count > 0)
				_scene_attackerUnits.remove_at(0);
			while (_scene_targetUnits.count > 0)
				_scene_targetUnits.remove_at(0);
		}

		pk::unit@ _unit;
		pk::point _src_pos;
		pk::point _src_pos0;
		pk::force@ _force;
		void init(pk::unit@ unit, pk::point src_pos)
		{
			@_unit = unit;
			_src_pos = src_pos;
			_src_pos0 = unit.get_pos();
			@_force = pk::get_force(_unit.get_force_id());
		}

		bool IsVisible자동공격()
		{
			return true;
		}
		string Get자동공격Text()
		{
			return pk::encode("자동공격 테스트");
		}
		string Get자동공격Desc()
		{
			return pk::encode("자동으로 공격합니다.");
		}
		pk::array<pk::point_int> GetTargets자동공격()
		{
			pk::array<pk::point_int> targets;

			pk::force@ f = pk::get_force(_unit.get_force_id());

			auto range = pk::range(_src_pos, 1, 10);
			for (int i = 0; i < range.length; i++)
			{
				pk::hex_object@ obj = pk::get_hex_object(range[i]);
				if (obj == null)
					continue;
				if (_force != null && _force.get_id() == obj.get_force_id())
					continue;

				targets.insertLast(pk::point_int(range[i], 0));
			}
			return targets;
		}
		int GetChance자동공격(pk::point dst_pos)
		{
			return 100;
		}
		bool 자동공격Handler(pk::point dst_pos)
		{
			//자동공격_함선화시(_unit);
			//자동공격_함선격돌(_unit);
			자동공격Handler_공성(_unit);
			return true;
		}



		void execute돌파(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;


			pk::point dst_pos2 = dst_pos;
			int nTactics = callback202(unit0, dst_pos, target, 전법_돌파);

			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), 전법_돌파, 크리티컬_근접);


			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, 유닛_전법_근접공격, bCri);
			}
			else
			{

				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, 전법_돌파, dst_pos, 0, bCri ? 1 : 0, false);
				if (!금강불굴(di, target))
				{
					int dir = pk::get_direction(unit0.get_pos(), dst_pos);
					pk::point ptA = pk::get_neighbor_pos(unit0.get_pos(), dir, 2);
					pk::point ptT = pk::get_neighbor_pos(dst_pos, dir, 2);
					di.src_move_pos = MoveThrough(unit0.get_pos(), ptA);

					anim(unit0, 유닛_전법_돌파, { di }, dst_pos, 0, "", 0);
					if (bCri)
						cutin(unit0);


					pk::unit@ u = getUnit(di.dst_pos);
					if (u != null)
					{
						if (unit0.has_skill(특기_질주) && prev_callback_222(unit0, u) > 0)
							updateChaos(u, unit0);
					}

					move(unit0, MoveThrough(unit0.get_pos(), ptA));


					addTroops(target, di);
					updateAfter(unit0, target);
					bool re = update(unit0, dst_pos, { di }, 크리티컬_근접, bCri);


					//dst_pos2 = di.dst_move_pos;
					if (re && 연전(unit0))
					{
						sleep();
						dir = pk::get_direction(unit0.get_pos(), dst_pos);
						pk::point ptA2 = pk::get_neighbor_pos(unit0.get_pos(), dir, 2);
						pk::point ptT2 = pk::get_neighbor_pos(dst_pos, dir, 2);
						di.src_move_pos = MoveThrough(unit0.get_pos(), ptA2);
						di.src_pos = unit0.get_pos();
						anim(unit0, 유닛_전법_돌파, { di }, dst_pos, 0, "", 0);
						if (bCri)
							cutin(unit0);

						pk::unit@ u2 = getUnit(di.dst_pos);
						if (u2 != null)
						{
							//pk::move(u, { MovePoint(dst_pos, ptT) });
							if (unit0.has_skill(특기_질주) && prev_callback_222(unit0, u2) > 0)
								updateChaos(u2, unit0);
						}

						move(unit0, MoveThrough(unit0.get_pos(), ptA));

						addTroops(target, di);
						updateAfter(unit0, target);
						update(unit0, dst_pos, { di }, 크리티컬_근접, bCri);
					}
				}
			}

			update(unit0, target, dst_pos, dst_pos2, pk::get_tactics(전법_돌파).energy_cost);
		}

		void execute돌격(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			pk::point dst_pos2 = dst_pos;
			int nTactics = callback202(unit0, dst_pos, target, 전법_돌격);

			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), 전법_돌격, 크리티컬_근접);


			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, 유닛_전법_근접공격, bCri);
			}
			else 
			{
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, 전법_돌격, dst_pos, 0, bCri ? 1 : 0, false);
				if (!금강불굴(di, target))
				{
					int dir = pk::get_direction(unit0.get_pos(), dst_pos);
					pk::point ptA = pk::get_neighbor_pos(dst_pos, dir, 1);
					di.dst_move_pos = MovePoint(dst_pos, ptA);
					di.src_move_pos = unit0.get_pos();
					if (di.dst_move_pos.x != dst_pos.x || di.dst_move_pos.y != dst_pos.y)
						di.src_move_pos = dst_pos;

					anim(unit0, 유닛_전법_돌격, { di }, dst_pos, 0, "", 0);
					if (bCri)
						cutin(unit0);

					pk::unit@ u = getUnit(di.dst_pos);
					if (u != null)
					{
						if (unit0.has_skill(특기_질주) && prev_callback_222(unit0, u) > 0)
							updateChaos(u, unit0);
						
						int dir2 = u.direction;
						move(u, di.dst_move_pos);
						u.direction = dir2;
					}
					move(unit0, di.src_move_pos);
					

					addTroops(target, di);
					updateAfter(unit0, target);
					bool re = update(unit0, di.dst_move_pos, { di }, 크리티컬_근접, bCri);

					dst_pos2 = di.dst_move_pos;
					if (re && 연전(unit0))
					{
						sleep();
						dir = pk::get_direction(unit0.get_pos(), dst_pos2);
						ptA = pk::get_neighbor_pos(dst_pos2, dir, 1);
						di.src_pos = unit0.get_pos();
						di.dst_pos = dst_pos2;
						di.src_move_pos = unit0.get_pos();
						di.dst_move_pos = MovePoint(dst_pos2, ptA);
						if (di.dst_move_pos.x != dst_pos.x || di.dst_move_pos.y != dst_pos.y)
							di.src_move_pos = dst_pos2;

						anim(unit0, 유닛_전법_돌격, { di }, dst_pos2, 0, "", 0);
						if (bCri)
							cutin(unit0);

						@u = getUnit(di.dst_pos);
						if (u != null)
						{
							if (unit0.has_skill(특기_질주) && prev_callback_222(unit0, u) > 0)
								updateChaos(u, unit0);

							int dir2 = u.direction;
							move(u, di.dst_move_pos);
							u.direction = dir2;
						}
						move(unit0, di.src_move_pos);


						addTroops(target, di);
						updateAfter(unit0, target);
						update(unit0, di.dst_move_pos, { di }, 크리티컬_근접, bCri);
						dst_pos2 = di.dst_move_pos;
					}
				}
			}
			update(unit0, target, dst_pos, dst_pos2, pk::get_tactics(전법_돌격).energy_cost);
		}

		void execute돌진(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			pk::point dst_pos2 = dst_pos;
			int nTactics = callback202(unit0, dst_pos, target, 전법_돌진);

			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), 전법_돌진, 크리티컬_근접);


			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, 유닛_전법_근접공격, bCri);
			}
			else 
			{
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, 전법_돌진, dst_pos, 0, bCri ? 1 : 0, false);
				if (!금강불굴(di, target))
				{
					int dir = pk::get_direction(unit0.get_pos(), dst_pos);
					int dir2 = pk::get_direction(dst_pos, unit0.get_pos());

					pk::point ptA = pk::get_neighbor_pos(dst_pos, dir, 2);
					di.dst_move_pos = MovePoint(dst_pos, ptA);
					di.src_move_pos = pk::get_neighbor_pos(di.dst_move_pos, dir2, 1);
					anim(unit0, 유닛_전법_돌진, { di }, dst_pos, 0, "", 0);
					if (bCri)
						cutin(unit0);

					pk::unit@ u = getUnit(di.dst_pos);
					if (u != null)
					{
						if (unit0.has_skill(특기_질주) && prev_callback_222(unit0, u) > 0)
							updateChaos(u, unit0);
						int dir2 = u.direction;
						move(u, di.dst_move_pos);
						u.direction = dir2;
					}
					move(unit0, di.src_move_pos);

					addTroops(target, di);
					updateAfter(unit0, target);
					bool re = update(unit0, di.dst_move_pos, { di }, 크리티컬_근접, bCri);

					dst_pos2 = di.dst_move_pos;
					if (re && 연전(unit0))
					{
						sleep();
						dir = pk::get_direction(unit0.get_pos(), dst_pos2);
						dir2 = pk::get_direction(dst_pos2, unit0.get_pos());

						ptA = pk::get_neighbor_pos(dst_pos2, dir, 2);
						di.src_pos = unit0.get_pos();
						di.dst_pos = dst_pos2;
						di.dst_move_pos = MovePoint(dst_pos2, ptA);
						di.src_move_pos = pk::get_neighbor_pos(di.dst_move_pos, dir2, 1);

						anim(unit0, 유닛_전법_돌진, { di }, dst_pos2, 0, "", 0);
						if (bCri)
							cutin(unit0);

						@u = getUnit(di.dst_pos);
						if (u != null)
						{
							if (unit0.has_skill(특기_질주) && prev_callback_222(unit0, u) > 0)
								updateChaos(u, unit0);
							int dir2 = u.direction;
							move(u, di.dst_move_pos);
							u.direction = dir2;
						}
						move(unit0, di.src_move_pos);

						addTroops(target, di);
						updateAfter(unit0, target);
						update(unit0, di.dst_move_pos, { di }, 크리티컬_근접, bCri);
						dst_pos2 = di.dst_move_pos;
					}
				}
			}
			update(unit0, target, dst_pos, dst_pos2, pk::get_tactics(전법_돌진).energy_cost);
		}


		void execute갈퀴(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			pk::point dst_pos2 = dst_pos;
			int nTactics = callback202(unit0, dst_pos, target, 전법_갈퀴);

			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), 전법_갈퀴, 크리티컬_근접);
			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, 유닛_전법_근접공격, bCri);
			}
			else
			{
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, 전법_갈퀴, dst_pos, 0, bCri ? 1 : 0, false);
				if (!금강불굴(di, target))
				{
					int dir = pk::get_direction(dst_pos, unit0.get_pos());
					pk::point ptA = pk::get_neighbor_pos(dst_pos, dir, 2);
					//di.src_move_pos = MoveThrough(unit0.get_pos(), ptA);
					di.src_move_pos = MovePoint(unit0.get_pos(), ptA);
					di.dst_move_pos = di.src_move_pos.x == ptA.x && di.src_move_pos.y == ptA.y ? unit0.get_pos() : dst_pos;

					anim(unit0, 유닛_전법_갈퀴, { di }, dst_pos, 0, "", 0);
					if (bCri)
						cutin(unit0);

					pk::point bpt = unit0.get_pos();
					move(unit0, MovePoint(unit0.get_pos(), di.src_move_pos));
					pk::unit@ u = getUnit(dst_pos);
					if (u != null)
						move(u, MovePoint(dst_pos, bpt));


					addTroops(target, di);
					updateAfter(unit0, target);
					bool re = update(unit0, di.dst_move_pos, { di }, 크리티컬_근접, bCri);
					if (re && 연전(unit0))
					{
						sleep();
						dst_pos = di.dst_move_pos;

						pk::point ptA2 = pk::get_neighbor_pos(dst_pos, dir, 2);
						di.src_move_pos = MovePoint(unit0.get_pos(), ptA2);
						di.dst_move_pos = di.src_move_pos.x == ptA2.x && di.src_move_pos.y == ptA2.y ? unit0.get_pos() : dst_pos;


						anim(unit0, 유닛_전법_갈퀴, { di }, dst_pos, 0, "", 0);
						if (bCri)
							cutin(unit0);

						bpt = unit0.get_pos();
						move(unit0, MovePoint(unit0.get_pos(), di.src_move_pos));
						if (u != null)
							move(u, MovePoint(dst_pos, bpt));
						addTroops(target, di);
						updateAfter(unit0, target);
						update(unit0, di.dst_move_pos, { di }, 크리티컬_근접, bCri);
						dst_pos2 = MovePoint(dst_pos, bpt);
					}

				}

			}
			update(unit0, target, dst_pos, dst_pos2, pk::get_tactics(전법_갈퀴).energy_cost);
		}
		void execute선풍(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;


			int nTactics = callback202(unit0, dst_pos, target, 전법_선풍);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), 전법_선풍, 크리티컬_근접);
			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, 유닛_전법_근접공격, bCri);
			}
			else
			{

				pk::damage_info di0;
				di0.src_pos = unit0.get_pos();
				di0.dst_pos = dst_pos;
				callback209(di0, unit0, 전법_선풍, dst_pos, 0, bCri ? 1 : 0, false);
				if (!금강불굴(di0, target))
				{
					array<pk::damage_info> dis;
					for (int i = 0; i < 6; i++)
					{
						pk::point pt = pk::get_neighbor_pos(unit0.get_pos(), i, 1);
						pk::unit@ uuu = getUnit(pt);
						if (uuu == null)
							continue;
						if (!pk::is_enemy(unit0, uuu) || !checkHex극병(pt))
							continue;

						pk::damage_info di2;
						di2.src_pos = unit0.get_pos();
						di2.dst_pos = pt;

						callback209(di2, unit0, 전법_선풍, pt, 0, bCri ? 1 : 0, false);
						dis.insertLast(di2);
					}
					anim(unit0, 유닛_전법_선풍, dis, dst_pos, 0, "", 0);
					if (bCri)
						cutin(unit0);

					for (int i = 0; i < dis.length; i++)
					{
						pk::damage_info di = dis[i];
						pk::unit@ uuu = getUnit(di.dst_pos);
						if (uuu == null)
							continue;
						addTroops(uuu, di);
						updateAfter(unit0, uuu);
					}
					bool re = update(unit0, dst_pos, dis, 크리티컬_근접, bCri);
					if (re && 연전(unit0))
					{
						sleep();
						anim(unit0, 유닛_전법_선풍, dis, dst_pos, 0, "", 0);
						if (bCri)
							cutin(unit0);

						for (int i = 0; i < dis.length; i++)
						{
							pk::damage_info di = dis[i];
							pk::unit@ uuu = getUnit(di.dst_pos);
							if (uuu == null)
								continue;
							addTroops(uuu, di);
							updateAfter(unit0, uuu);
						}
						update(unit0, dst_pos, dis, 크리티컬_근접, bCri);
					}
				}
			}

			update(unit0, target, dst_pos, dst_pos, pk::get_tactics(전법_선풍).energy_cost);
		}
		void execute화시(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			int nTactics = callback202(unit0, dst_pos, target, 전법_화시);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), 전법_화시, 크리티컬_원거리);

			//bTactics = false;
			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, 유닛_전법_활공격, bCri);
			}
			else
			{
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, 전법_화시, dst_pos, 0, bCri ? 1 : 0, false);
				if (!금강불굴(di, target))
				{
					anim(unit0, 유닛_전법_화시, { di }, dst_pos, 0, "", 0);
					if (bCri)
						cutin(unit0);
					addTroops(target, di);

					pk::unit@ u = getUnit(di.dst_pos);
					if (u != null && !u.has_skill(특기_호위))
					{
						if (u.member[0] >= 0 && u.member[0] < 무장_끝 && pk::rand_bool(자동공격_화시_부상확률))
							injury(pk::get_person(u.member[0]));
						if (u.member[1] >= 0 && u.member[1] < 무장_끝 && pk::rand_bool(자동공격_화시_부상확률))
							injury(pk::get_person(u.member[1]));
						if (u.member[2] >= 0 && u.member[2] < 무장_끝 && pk::rand_bool(자동공격_화시_부상확률))
							injury(pk::get_person(u.member[2]));
					}
					bool re = update(unit0, dst_pos, { di }, 크리티컬_원거리, bCri);
					re = updateAfter(unit0, target);
					if (re && 연전(unit0))
					{
						sleep();
						anim(unit0, 유닛_전법_화시, { di }, dst_pos, 0, "", 0);
						if (bCri)
							cutin(unit0);
						addTroops(target, di);

						@u = getUnit(di.dst_pos);
						if (u != null && !u.has_skill(특기_호위))
						{
							if (u.member[0] >= 0 && u.member[0] < 무장_끝 && pk::rand_bool(자동공격_화시_부상확률))
								injury(pk::get_person(u.member[0]));
							if (u.member[1] >= 0 && u.member[1] < 무장_끝 && pk::rand_bool(자동공격_화시_부상확률))
								injury(pk::get_person(u.member[1]));
							if (u.member[2] >= 0 && u.member[2] < 무장_끝 && pk::rand_bool(자동공격_화시_부상확률))
								injury(pk::get_person(u.member[2]));
						}
						update(unit0, dst_pos, { di }, 크리티컬_원거리, bCri);
						updateAfter(unit0, target);
					}
				}
			}
			update(unit0, target, dst_pos, dst_pos, pk::get_tactics(전법_화시).energy_cost);
		}
		void execute횡치(pk::unit@ unit0, pk::point dst_pos)
		{

			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			int nTactics = callback202(unit0, dst_pos, target, 전법_횡치);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), 전법_횡치, 크리티컬_근접);

			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, 유닛_전법_근접공격, bCri);
			}
			else
			{
				array<pk::damage_info> dis;
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, 전법_횡치, dst_pos, 0, bCri ? 1 : 0, false);
				if (!금강불굴(di, target))
				{
					dis.insertLast(di);

					array<pk::point> arr = get횡치pos(unit0.get_pos(), dst_pos);
					pk::unit@ u0 = getUnit(arr[0]);
					if (u0 != null && pk::is_enemy(unit0, u0) && checkHex극병(arr[0]))
					{
						pk::damage_info di1;
						di1.src_pos = unit0.get_pos();
						di1.dst_pos = arr[0];
						callback209(di1, unit0, 전법_횡치, arr[0], 0, bCri ? 1 : 0, false);
						dis.insertLast(di1);
					}
					pk::unit@ u1 = getUnit(arr[1]);
					if (u1 != null && pk::is_enemy(unit0, u1) && checkHex극병(arr[1]))
					{
						pk::damage_info di1;
						di1.src_pos = unit0.get_pos();
						di1.dst_pos = arr[1];
						callback209(di1, unit0, 전법_횡치, arr[1], 0, bCri ? 1 : 0, false);
						dis.insertLast(di1);
					}

					anim(unit0, 유닛_전법_횡치, { di }, dst_pos, 0, "", 0);
					if (bCri)
						cutin(unit0);

					for (int i = 0; i < dis.length; i++)
					{
						pk::damage_info ddi = dis[i];
						pk::unit@ u = getUnit(ddi.dst_pos);
						if (u == null)
							continue;

						addTroops(u, ddi);
						updateAfter(unit0, u);
					}
					bool re = update(unit0, dst_pos, dis, 크리티컬_근접, bCri);
					if (re && 연전(unit0))
					{
						sleep();
						anim(unit0, 유닛_전법_횡치, { di }, dst_pos, 0, "", 0);
						if (bCri)
							cutin(unit0);

						for (int i = 0; i < dis.length; i++)
						{
							pk::damage_info ddi = dis[i];
							pk::unit@ u = getUnit(ddi.dst_pos);
							if (u == null)
								continue;

							addTroops(u, ddi);
							updateAfter(unit0, u);
						}
					}
					update(unit0, dst_pos, dis, 크리티컬_근접, bCri);
				}
			}
			update(unit0, target, dst_pos, dst_pos, pk::get_tactics(전법_횡치).energy_cost);
		}
		void execute나선첨(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			int nTactics = callback202(unit0, dst_pos, target, 전법_나선첨);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), 전법_나선첨, 크리티컬_근접);


			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, 유닛_전법_근접공격, bCri);
			}
			else
			{
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, 전법_화시, dst_pos, 0, bCri ? 1 : 0, false);
				if (!금강불굴(di, target))
				{
					anim(unit0, 유닛_전법_근접공격, { di }, dst_pos, 0, "", 0);
					if (bCri)
						cutin(unit0);

					addTroops(target, di);
					updateAfter(unit0, target);
					pk::unit@ u = pk::is_valid_pos(target.get_pos()) ? getUnit(target.get_pos()) : null;
					if (u != null && prev_callback_221(unit0, u, bCri) > 0)
						updateChaos(u, unit0);

					bool re = update(unit0, dst_pos, { di }, 크리티컬_근접, bCri);
					if (re && 연전(unit0))
					{
						sleep();
						anim(unit0, 유닛_전법_근접공격, { di }, dst_pos, 0, "", 0);
						if (bCri)
							cutin(unit0);

						addTroops(target, di);
						updateAfter(unit0, target);
						pk::unit@ u2 = pk::is_valid_pos(target.get_pos()) ? getUnit(target.get_pos()) : null;
						if (u2 != null && prev_callback_221(unit0, u2, bCri) > 0)
							updateChaos(u2, unit0);

						update(unit0, dst_pos, { di }, 크리티컬_근접, bCri);
					}
				}
			}

			update(unit0, target, dst_pos, dst_pos, pk::get_tactics(전법_나선첨).energy_cost);
			return;
		}
		void execute이단첨(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			pk::point dst_pos0 = dst_pos;

			int nTactics = callback202(unit0, dst_pos, target, 전법_이단첨);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), 전법_이단첨, 크리티컬_근접);
			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, 1, bCri);
			}
			else
			{
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, 전법_이단첨, dst_pos, 0, bCri ? 1 : 0, false);
				if (!금강불굴(di, target))
				{
					int dir = pk::get_direction(unit0.get_pos(), dst_pos);
					pk::point ptA = pk::get_neighbor_pos(dst_pos, dir, 2);
					di.src_move_pos = unit0.get_pos();
					di.dst_move_pos = MovePoint(dst_pos, ptA);
					anim(unit0, 유닛_전법_이단첨, { di }, dst_pos, 0, "", 0);
					if (bCri)
						cutin(unit0);
					pk::unit@ u = getUnit(di.dst_pos);
					if (u != null)
					{
						int dir2 = u.direction;
						move(u, di.dst_move_pos);
						u.direction = dir2;
					}
						

					addTroops(target, di);
					updateAfter(unit0, target);
					bool re = update(unit0, di.dst_move_pos, { di }, 크리티컬_근접, bCri);
					pk::point dst_pos2 = di.dst_move_pos;
					dst_pos0 = dst_pos2;
					if (re && 연전(unit0))
					{
						sleep();
						pk::point ptA2 = pk::get_neighbor_pos(dst_pos2, dir, 2);
						di.src_pos = unit0.get_pos();
						di.dst_pos = dst_pos2;
						di.src_move_pos = unit0.get_pos();
						di.dst_move_pos = MovePoint(dst_pos2, ptA2);
						anim(unit0, 유닛_전법_이단첨, { di }, dst_pos2, 0, "", 0);
						if (bCri)
							cutin(unit0);

						@u = getUnit(di.dst_pos);
						if (u != null)
						{
							int dir2 = u.direction;
							move(u, di.dst_move_pos);
							u.direction = dir2;
						}
							


						addTroops(target, di);
						updateAfter(unit0, target);
						update(unit0, di.dst_move_pos, { di }, 크리티컬_근접, bCri);
						dst_pos0 = di.dst_move_pos;
					}
				}

			}//bTatics
			update(unit0, target, dst_pos, dst_pos0, pk::get_tactics(전법_이단첨).energy_cost);
		}
		void execute돌출(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			pk::point dst_pos0 = dst_pos;

			int nTactics = callback202(unit0, dst_pos, target, 전법_돌출);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), 전법_돌출, 크리티컬_근접);
			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, 유닛_전법_근접공격, bCri);
			}
			else
			{
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, 전법_돌출, dst_pos, 0, bCri ? 1 : 0, false);
				if (!금강불굴(di, target))
				{
					int dir = pk::get_direction(unit0.get_pos(), dst_pos);
					pk::point ptA = pk::get_neighbor_pos(dst_pos, dir, 1);
					di.src_move_pos = unit0.get_pos();
					di.dst_move_pos = MovePoint(dst_pos, ptA);
					anim(unit0, 유닛_전법_돌출, { di }, dst_pos, 0, "", 0);
					if (bCri)
						cutin(unit0);
					pk::unit@ u = getUnit(di.dst_pos);
					if (u != null)
					{
						int dir2 = u.direction;
						move(u, di.dst_move_pos);
						u.direction = dir2;
					}
						


					addTroops(target, di);
					updateAfter(unit0, target);
					bool re = update(unit0, di.dst_move_pos, { di }, 크리티컬_근접, bCri);
					pk::point dst_pos2 = di.dst_move_pos;
					dst_pos0 = di.dst_move_pos;
					if (re && 연전(unit0))
					{
						sleep();
						pk::point ptA2 = pk::get_neighbor_pos(dst_pos2, dir, 1);
						di.src_pos = unit0.get_pos();
						di.dst_pos = dst_pos2;
						di.src_move_pos = unit0.get_pos();
						di.dst_move_pos = MovePoint(dst_pos2, ptA2);
						anim(unit0, 유닛_전법_돌출, { di }, dst_pos2, 0, "", 0);
						if (bCri)
							cutin(unit0);

						@u = getUnit(di.dst_pos);
						if (u != null)
						{
							int dir2 = u.direction;
							move(u, di.dst_move_pos);
							u.direction = dir2;
						}
							

						addTroops(target, di);
						updateAfter(unit0, target);
						update(unit0, di.dst_move_pos, { di }, 크리티컬_근접, bCri);
						dst_pos0 = di.dst_move_pos;
					}
				}

			}//bTatics
			update(unit0, target, dst_pos, dst_pos0, pk::get_tactics(전법_돌출).energy_cost);
		}
		void execute난사(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			int nTactics = callback202(unit0, dst_pos, target, 전법_난사);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), 전법_난사, 크리티컬_원거리);
			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, 유닛_전법_활공격, bCri);
			}
			else
			{
				pk::tactics@ tactics_t = pk::get_tactics(전법_난사);
				int  max_range = tactics_t.max_range;
				int  min_range = tactics_t.min_range;
				if (사거리_패치)
				{
					tactics_t.min_range = 1;
					tactics_t.max_range = 5;
				}



				array<pk::damage_info> dis;
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, 전법_난사, dst_pos, 0, bCri ? 1 : 0, false);
				if (!금강불굴(di, target))
				{
					pk::building@ b = pk::get_building(dst_pos);
					bool b거점 = false;
					if (b != null && (b.facility == 시설_도시 || b.facility == 시설_관문 || b.facility == 시설_항구))
					{
						di.troops_damage *= 1.5;
						b거점 = true;
					}
					dis.insertLast(di);

					for (int i = 0; i < 6; i++)
					{
						pk::point pt = pk::get_neighbor_pos(dst_pos, i, 1);
						pk::hex_object@ obj = pk::get_hex_object(pt);
						if (obj == null)
							continue;
						if (unit0.has_skill(특기_궁신) && !pk::is_enemy(unit0, obj))
							continue;
						if (!checkHex노병(unit0, pt))
							continue;

						pk::damage_info di2;
						di2.src_pos = unit0.get_pos();
						di2.dst_pos = pt;

						callback209(di2, unit0, 전법_난사, pt, 0, bCri ? 1 : 0, false);
						if (b거점) 
						{
							di2.troops_damage = 1;
							di2.hp_damage = 0;
						}
							
						dis.insertLast(di2);
					}
					anim(unit0, 유닛_전법_난사, dis, dst_pos, 0, "", 0);
					if (bCri)
						cutin(unit0);

					for (int i = 0; i < dis.length; i++)
					{
						pk::damage_info di2 = dis[i];
						pk::hex_object@ u = pk::get_hex_object(di2.dst_pos);
						if (u == null)
							continue;
						addTroops(u, di2);
						updateAfter(unit0, u);
					}
					bool re = update(unit0, dst_pos, dis, 크리티컬_원거리, bCri);
					if (re && 연전(unit0))
					{
						sleep();
						anim(unit0, 유닛_전법_난사, dis, dst_pos, 0, "", 0);
						if (bCri)
							cutin(unit0);

						for (int i = 0; i < dis.length; i++)
						{
							pk::damage_info di2 = dis[i];
							pk::hex_object@ u = pk::get_hex_object(di2.dst_pos);
							if (u == null)
								continue;
							addTroops(u, di2);
							updateAfter(unit0, u);
						}
						update(unit0, dst_pos, dis, 크리티컬_원거리, bCri);
					}
				}
				if (사거리_패치)
				{
					tactics_t.min_range = min_range;
					tactics_t.max_range = max_range;
				}
			}
			update(unit0, target, dst_pos, dst_pos, pk::get_tactics(전법_난사).energy_cost);
		}
		void execute관시(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			int nTactics = callback202(unit0, dst_pos, target, 전법_관시);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), 전법_관시, 크리티컬_원거리);
			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, 유닛_전법_활공격, bCri);
			}
			else
			{
				pk::tactics@ tactics_t = pk::get_tactics(전법_관시);
				int  max_range = tactics_t.max_range;
				int  min_range = tactics_t.min_range;
				if (사거리_패치)
				{
					tactics_t.min_range = 1;
					tactics_t.max_range = 5;
				}

				array<pk::damage_info> dis;
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, 전법_관시, dst_pos, 0, bCri ? 1 : 0, false);
				if (!금강불굴(di, target))
				{
					dis.insertLast(di);
					int diff = pk::get_distance(di.dst_pos, di.src_pos);
					int dir = pk::get_direction(di.src_pos, di.dst_pos);

					for (int i = 1; i < diff; i++)
					{
						pk::point pt = pk::get_neighbor_pos(di.src_pos, dir, i);
						pk::hex_object@ obj = pk::get_hex_object(pt);
						if (obj == null || !pk::is_enemy(unit0,obj))
							continue;
						if (!checkHex노병(unit0, pt))
							continue;

						pk::damage_info di2;
						di2.src_pos = unit0.get_pos();
						di2.dst_pos = pt;

						callback209(di2, unit0, 전법_관시, pt, 0, bCri ? 1 : 0, false);
						dis.insertLast(di2);
					}
					anim(unit0, 유닛_전법_관시, dis, dst_pos, 0, "", 0);
					if (bCri)
						cutin(unit0);

					for (int i = 0; i < dis.length; i++)
					{
						pk::damage_info di2 = dis[i];
						pk::hex_object@ u = pk::get_hex_object(di2.dst_pos);
						if (u == null)
							continue;
						addTroops(u, di2);
						updateAfter(unit0, u);
					}
					bool re = update(unit0, dst_pos, dis, 크리티컬_원거리, bCri);
					if (re && 연전(unit0))
					{
						sleep();
						anim(unit0, 유닛_전법_관시, dis, dst_pos, 0, "", 0);
						if (bCri)
							cutin(unit0);
						for (int i = 0; i < dis.length; i++)
						{
							pk::damage_info di2 = dis[i];
							pk::hex_object@ u = pk::get_hex_object(di2.dst_pos);
							if (u == null)
								continue;
							addTroops(u, di2);
							updateAfter(unit0, u);
						}
					}
					update(unit0, dst_pos, dis, 크리티컬_원거리, bCri);
				}

				if (사거리_패치)
				{
					tactics_t.min_range = min_range;
					tactics_t.max_range = max_range;
				}
			}
			update(unit0, target, dst_pos, dst_pos, pk::get_tactics(전법_관시).energy_cost);
		}


		void execute함선화시(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			int nTactics = callback202(unit0, dst_pos, target, 전법_함선화시);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), 전법_함선화시, 크리티컬_원거리);

			//bTactics = false;
			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, 유닛_전법_활공격, bCri);
			}
			else
			{
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, 전법_함선화시, dst_pos, 0, bCri ? 1 : 0, false);
				if (!금강불굴(di, target))
				{
					anim(unit0, 유닛_전법_화시_함선, { di }, dst_pos, 0, "", 0);
					if (bCri)
						cutin(unit0);
					addTroops(target, di);

					pk::unit@ u = getUnit(di.dst_pos);
					if (u != null && !u.has_skill(특기_호위))
					{
						if (u.member[0] >= 0 && u.member[0] < 무장_끝 && pk::rand_bool(자동공격_화시_부상확률))
							injury(pk::get_person(u.member[0]));
						if (u.member[1] >= 0 && u.member[1] < 무장_끝 && pk::rand_bool(자동공격_화시_부상확률))
							injury(pk::get_person(u.member[1]));
						if (u.member[2] >= 0 && u.member[2] < 무장_끝 && pk::rand_bool(자동공격_화시_부상확률))
							injury(pk::get_person(u.member[2]));
					}
					bool re = update(unit0, dst_pos, { di }, 크리티컬_원거리, bCri);
					re = updateAfter(unit0, target);
					if (re && 연전(unit0))
					{
						sleep();
						anim(unit0, 유닛_전법_화시_함선, { di }, dst_pos, 0, "", 0);
						if (bCri)
							cutin(unit0);
						addTroops(target, di);

						@u = getUnit(di.dst_pos);
						if (u != null && !u.has_skill(특기_호위))
						{
							if (u.member[0] >= 0 && u.member[0] < 무장_끝 && pk::rand_bool(자동공격_화시_부상확률))
								injury(pk::get_person(u.member[0]));
							if (u.member[1] >= 0 && u.member[1] < 무장_끝 && pk::rand_bool(자동공격_화시_부상확률))
								injury(pk::get_person(u.member[1]));
							if (u.member[2] >= 0 && u.member[2] < 무장_끝 && pk::rand_bool(자동공격_화시_부상확률))
								injury(pk::get_person(u.member[2]));
						}
						update(unit0, dst_pos, { di }, 크리티컬_원거리, bCri);
						updateAfter(unit0, target);
					}
				}
			}
			update(unit0, target, dst_pos, dst_pos, pk::get_tactics(전법_함선화시).energy_cost);
		}
		void execute함선격돌(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			pk::point dst_pos0 = dst_pos;

			int nTactics = callback202(unit0, dst_pos, target, 전법_함선격돌);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), 전법_함선격돌, 크리티컬_근접);
			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, 유닛_전법_근접공격_함선, bCri);
			}
			else
			{
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, 전법_함선격돌, dst_pos, 0, bCri ? 1 : 0, false);
				if (!금강불굴(di, target))
				{
					int dir = pk::get_direction(unit0.get_pos(), dst_pos);
					pk::point ptA = pk::get_neighbor_pos(dst_pos, dir, 1);
					di.src_move_pos = unit0.get_pos();
					di.dst_move_pos = MovePoint(dst_pos, ptA,true);
					anim(unit0, 유닛_전법_격돌_함선, { di }, dst_pos, 0, "", 0);
					if (bCri)
						cutin(unit0);
					pk::unit@ u = getUnit(di.dst_pos);
					if (u != null)
					{
						int dir2 = u.direction;
						move(u, di.dst_move_pos);
						u.direction = dir2;
						u.update();
					}
						
					addTroops(target, di);
					updateAfter(unit0, target);
					bool re = update(unit0, di.dst_move_pos, { di }, 크리티컬_근접, bCri);
					pk::point dst_pos2 = di.dst_move_pos;
					dst_pos0 = di.dst_move_pos;
					if (re && 연전(unit0))
					{
						sleep();
						pk::point ptA2 = pk::get_neighbor_pos(dst_pos2, dir, 1);
						di.src_pos = unit0.get_pos();
						di.dst_pos = dst_pos2;
						di.src_move_pos = unit0.get_pos();
						di.dst_move_pos = MovePoint(dst_pos2, ptA2,true);
						anim(unit0, 유닛_전법_격돌_함선, { di }, dst_pos2, 0, "", 0);
						if (bCri)
							cutin(unit0);

						@u = getUnit(di.dst_pos);
						if (u != null)
						{
							int dir2 = u.direction;
							move(u, di.dst_move_pos);
							u.direction = dir2;
							u.update();
						}
							

						addTroops(target, di);
						updateAfter(unit0, target);
						update(unit0, di.dst_move_pos, { di }, 크리티컬_근접, bCri);
						dst_pos0 = di.dst_move_pos;
					}
				}

			}//bTatics
			update(unit0, target, dst_pos, dst_pos0, pk::get_tactics(전법_함선격돌).energy_cost);
		}
		void execute함선투석(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			int nTactics = callback202(unit0, dst_pos, target, 전법_함선투석);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), 전법_함선투석, 크리티컬_원거리);
			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, 유닛_전법_활공격, bCri);
			}
			else
			{
				pk::tactics@ tactics_t = pk::get_tactics(전법_함선투석);
				int  max_range = tactics_t.max_range;
				int  min_range = tactics_t.min_range;
				if (사거리_패치)
				{
					tactics_t.min_range = 1;
					tactics_t.max_range = 5;
				}



				array<pk::damage_info> dis;
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, 전법_함선투석, dst_pos, 0, bCri ? 1 : 0, false);

				if (!금강불굴(di, target))
				{
					pk::building@ b = pk::get_building(dst_pos);
					bool b거점 = false;
					if (b != null && (b.facility == 시설_도시 || b.facility == 시설_관문 || b.facility == 시설_항구))
					{
						if (pk::has_tech(unit0, 기교_벽력))
						{
							di.troops_damage *= 공석투석_병력_데미지_비율;
							di.hp_damage *= 공성투석_내구도_데미지_비율;
							b거점 = true;
						}
					}
					dis.insertLast(di);

					if (pk::has_tech(unit0, 기교_벽력))
					{
						for (int i = 0; i < 6; i++)
						{
							pk::point pt = pk::get_neighbor_pos(dst_pos, i, 1);
							pk::hex_object@ obj = pk::get_hex_object(pt);
							if (obj == null)
								continue;

							pk::damage_info di2;
							di2.src_pos = unit0.get_pos();
							di2.dst_pos = pt;

							callback209(di2, unit0, 전법_함선투석, pt, 0, bCri ? 1 : 0, false);
							if (b거점)
							{
								di2.troops_damage = 1;
								di2.hp_damage = 0;
							}

							dis.insertLast(di2);
						}
					}

					anim(unit0, 유닛_전법_투석_함선, dis, dst_pos, 0, "", 0);
					if (bCri)
						cutin(unit0);

					for (int i = 0; i < dis.length; i++)
					{
						pk::damage_info di2 = dis[i];
						pk::hex_object@ u = pk::get_hex_object(di2.dst_pos);
						if (u == null)
							continue;
						addTroops(u, di2);
						updateAfter(unit0, u);
					}
					bool re = update(unit0, dst_pos, dis, 크리티컬_원거리, bCri);
					if (re && 연전(unit0))
					{
						sleep();
						anim(unit0, 유닛_전법_투석_함선, dis, dst_pos, 0, "", 0);
						if (bCri)
							cutin(unit0);

						for (int i = 0; i < dis.length; i++)
						{
							pk::damage_info di2 = dis[i];
							pk::hex_object@ u = pk::get_hex_object(di2.dst_pos);
							if (u == null)
								continue;
							addTroops(u, di2);
							updateAfter(unit0, u);
						}
						update(unit0, dst_pos, dis, 크리티컬_원거리, bCri);
					}
				}
				if (사거리_패치)
				{
					tactics_t.min_range = min_range;
					tactics_t.max_range = max_range;
				}
			}
			update(unit0, target, dst_pos, dst_pos, pk::get_tactics(전법_함선투석).energy_cost);
		}

		void execute공성투석(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			int nTactics = callback202(unit0, dst_pos, target, 전법_공성투석);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), 전법_공성투석, 크리티컬_원거리);
			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, 유닛_전법_활공격, bCri);
			}
			else
			{
				pk::tactics@ tactics_t = pk::get_tactics(전법_공성투석);
				int  max_range = tactics_t.max_range;
				int  min_range = tactics_t.min_range;
				if (사거리_패치)
				{
					tactics_t.min_range = 1;
					tactics_t.max_range = 5;
				}



				array<pk::damage_info> dis;
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, 전법_공성투석, dst_pos, 0, bCri ? 1 : 0, false);

				if (!금강불굴(di, target))
				{
					pk::building@ b = pk::get_building(dst_pos);
					bool b거점 = false;
					if (b != null && (b.facility == 시설_도시 || b.facility == 시설_관문 || b.facility == 시설_항구))
					{
						if (pk::has_tech(unit0, 기교_벽력))
						{
							di.troops_damage *= 공석투석_병력_데미지_비율;
							di.hp_damage *= 공성투석_내구도_데미지_비율;
							b거점 = true;
						}
					}
					dis.insertLast(di);

					if (pk::has_tech(unit0, 기교_벽력))
					{
						for (int i = 0; i < 6; i++)
						{
							pk::point pt = pk::get_neighbor_pos(dst_pos, i, 1);
							pk::hex_object@ obj = pk::get_hex_object(pt);
							if (obj == null)
								continue;

							pk::damage_info di2;
							di2.src_pos = unit0.get_pos();
							di2.dst_pos = pt;

							callback209(di2, unit0, 전법_공성투석, pt, 0, bCri ? 1 : 0, false);
							if (b거점)
							{
								di2.troops_damage = 0;
								di2.hp_damage = 0;
							}

							dis.insertLast(di2);
						}
					}


					anim(unit0, 유닛_전법_투석_병기, dis, dst_pos, 0, "", 0);
					if (bCri)
						cutin(unit0);

					for (int i = 0; i < dis.length; i++)
					{
						pk::damage_info di2 = dis[i];
						pk::hex_object@ u = pk::get_hex_object(di2.dst_pos);
						if (u == null)
							continue;
						addTroops(u, di2);
						updateAfter(unit0, u);
					}
					bool re = update(unit0, dst_pos, dis, 크리티컬_원거리, bCri);
					if (re && 연전(unit0))
					{
						sleep();
						anim(unit0, 유닛_전법_투석_병기, dis, dst_pos, 0, "", 0);
						if (bCri)
							cutin(unit0);

						for (int i = 0; i < dis.length; i++)
						{
							pk::damage_info di2 = dis[i];
							pk::hex_object@ u = pk::get_hex_object(di2.dst_pos);
							if (u == null)
								continue;
							addTroops(u, di2);
							updateAfter(unit0, u);
						}
						update(unit0, dst_pos, dis, 크리티컬_원거리, bCri);
					}
				}
				if (사거리_패치)
				{
					tactics_t.min_range = min_range;
					tactics_t.max_range = max_range;
				}
			}
			update(unit0, target, dst_pos, dst_pos, pk::get_tactics(전법_공성투석).energy_cost);
		}

		bool 자동공격_기병_돌파(pk::unit@ u)
		{
			if (u.energy < pk::get_tactics(전법_돌파).energy_cost)
				return false;
			if (getMax적성(u, 병종_기병) < 적성_A)
				return false;


			array<pk::point> arr = pk::get_movable_pos(u);
			arr.insertAt(0, u.get_pos());

			int maxTact = 0;
			pk::unit@ maxUnit = null;
			pk::point maxPt;
			for (int i = 0; i < arr.length; i++)
			{
				pk::point pt = arr[i];
				if (isOnFire(pt))
					continue;
				if (pk::get_building(pt) != null)
					continue;

				for (int j = 0; j < 방향_끝; j++)
				{
					pk::point pt2 = pk::get_neighbor_pos(pt, j, 1);
					pk::unit@ unit = getUnit(pt2);
					if (unit == null || !pk::is_enemy(u, unit))
						continue;
					if (!checkHex기병(pt2))
						continue;
					pk::point pt3 = pk::get_neighbor_pos(pt, j, 2);
					if (isOnFire(pt3))
						continue;

					int nTactics = callback202(u, pt2, unit, 전법_돌파);
					if (nTactics > maxTact)
					{
						maxTact = nTactics;
						@maxUnit = unit;
						maxPt = pt;
					}
				}
			}
			if (maxUnit == null)
				return false;

			if (콘솔_로그_표시)
				pk::printf("전법:돌파시작 {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			move(u, maxPt);
			execute돌파(u, maxUnit.get_pos());
			if (콘솔_로그_표시)
				pk::printf("전법:돌파끝 {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));


			return true;
		}
		bool 자동공격_기병_돌격(pk::unit@ u)
		{
			if (u.energy < pk::get_tactics(전법_돌격).energy_cost)
				return false;
			if (getMax적성(u, 병종_기병) < 적성_B)
				return false;


			array<pk::point> arr = pk::get_movable_pos(u);
			arr.insertAt(0, u.get_pos());

			int maxTact = 0;
			pk::unit@ maxUnit = null;
			pk::point maxPt;
			for (int i = 0; i < arr.length; i++)
			{
				pk::point pt = arr[i];
				if (isOnFire(pt))
					continue;
				if (pk::get_building(pt) != null)
					continue;

				for (int j = 0; j < 방향_끝; j++)
				{
					pk::point pt2 = pk::get_neighbor_pos(pt, j, 1);
					pk::unit@ unit = getUnit(pt2);
					if (unit == null || !pk::is_enemy(u, unit))
						continue;
					if (!checkHex기병(pt2))
						continue;

					int nTactics = callback202(u, pt2, unit, 전법_돌격);
					if (nTactics > maxTact)
					{
						maxTact = nTactics;
						@maxUnit = unit;
						maxPt = pt;
					}
				}
			}//i

			if (maxUnit == null)
				return false;

			if (콘솔_로그_표시)
				pk::printf("전법:돌격시작 {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			move(u, maxPt);
			execute돌격(u, maxUnit.get_pos());
			if (콘솔_로그_표시)
				pk::printf("전법:돌격끝 {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));


			return true;


		}
		bool 자동공격_기병_돌진(pk::unit@ u)
		{
			if (u.energy < pk::get_tactics(전법_돌진).energy_cost)
				return false;
			if (getMax적성(u, 병종_기병) < 적성_S)
				return false;


			array<pk::point> arr = pk::get_movable_pos(u);
			arr.insertAt(0, u.get_pos());

			int maxTact = 0;
			pk::unit@ maxUnit = null;
			pk::point maxPt;
			for (int i = 0; i < arr.length; i++)
			{
				pk::point pt = arr[i];
				if (isOnFire(pt))
					continue;
				if (pk::get_building(pt) != null)
					continue;

				for (int j = 0; j < 방향_끝; j++)
				{
					pk::point pt2 = pk::get_neighbor_pos(pt, j, 1);
					pk::unit@ unit = getUnit(pt2);
					if (unit == null || !pk::is_enemy(u, unit))
						continue;
					if (!checkHex기병(pt2))
						continue;
					pk::point pt3 = pk::get_neighbor_pos(pt, j, 2);
					if (isOnFire(pt3) && isMovable(pt3))
						continue;

					int nTactics = callback202(u, pt2, unit, 전법_돌진);
					if (nTactics > maxTact)
					{
						maxTact = nTactics;
						@maxUnit = unit;
						maxPt = pt;
					}
				}
			}
			if (maxUnit == null)
				return false;

			if (콘솔_로그_표시)
				pk::printf("전법:돌진 시작 {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			move(u, maxPt);
			execute돌진(u, maxUnit.get_pos());
			if (콘솔_로그_표시)
				pk::printf("전법:돌진 끝 {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));


			return true;
		}

		bool 자동공격_기병_화시(pk::unit@ u)
		{
			if (u.energy < pk::get_tactics(전법_화시).energy_cost)
				return false;
			if (!pk::has_tech(u, 기교_정예기병))
				return false;
			if (u.weapon == 병기_군마 && getMax적성(u, 병종_기병) < 적성_B)
				return false;
			if (u.weapon == 병기_노 && getMax적성(u, 병종_노병) < 적성_B)
				return false;

			int dist = getMaxAttackDistance(u);
			int minDist = 2;
			int curDist = 2;

			int maxTact = 0;
			pk::unit@ maxUnit = null;
			pk::point maxPos;

			array<pk::point> arr = pk::get_movable_pos(u);
			arr.insertAt(0, u.get_pos());

			for (int i0 = 0; i0 < arr.length; i0++)
			{
				pk::point pt0 = arr[i0];
				if (isOnFire(pt0))
					continue;
				if (pk::get_building(pt0) != null)
					continue;


				array<pk::point> arr2 = pk::range(pt0, curDist, dist);
				for (int i = 0; i < arr2.length; i++)
				{
					pk::point pt = arr2[i];
					pk::unit@ unit = getUnit(pt);
					if (unit == null || !pk::is_enemy(u, unit))
						continue;
					if (!checkHex노병(u, pt))
						continue;


					int nTactics = callback202(u, pt, unit, 전법_화시);
					if (nTactics > maxTact)
					{
						maxTact = nTactics;
						@maxUnit = unit;
						maxPos = pt0;
					}
				}
			}

			if (maxUnit == null)
				return false;

			if (콘솔_로그_표시)
				pk::printf("전법:화시시작 {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			move(u, maxPos);
			execute화시(u, maxUnit.get_pos());
			if (콘솔_로그_표시)
				pk::printf("전법:화시끝 {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));

			return true;
		}

		bool 자동공격_창병_극병_횡치(pk::unit@ u, bool bChang)
		{
			if (u.energy < pk::get_tactics(전법_횡치).energy_cost)
				return false;
			if (bChang)
			{
				if (!pk::has_tech(u, 기교_정예창병))
					return false;
			}
			if (u.weapon == 병기_극 && getMax적성(u, 병종_극병) < 적성_A)
				return false;
			if (u.weapon == 병기_창 && getMax적성(u, 병종_창병) < 적성_A)
				return false;


			//2명이상되면 발사
			int dist = getMaxAttackDistance(u);

			int maxCount = 0;
			pk::unit@ maxUnit = null;
			pk::point maxPT;


			array<pk::point> arr = pk::get_movable_pos(u);
			arr.insertAt(0, u.get_pos());

			for (int i0 = 0; i0 < arr.length; i0++)
			{
				pk::point pt0 = arr[i0];
				if (isOnFire(pt0))
					continue;
				if (pk::get_building(pt0) != null)
					continue;

				for (int i = 0; i < 방향_끝; i++)
				{
					pk::point pt = pk::get_neighbor_pos(pt0, i, dist);
					pk::unit@ unit = getUnit(pt);
					if (unit == null || !pk::is_enemy(u, unit))
						continue;
					if (bChang && !checkHex창병(pt))
						continue;
					if (!bChang && !checkHex극병(pt))
						continue;

					int acount = 1;
					array<pk::point> arr2 = get횡치pos(pt0, pt);
					pk::unit@ u0 = getUnit(arr2[0]);
					pk::unit@ u1 = getUnit(arr2[1]);
					if (u0 != null && pk::is_enemy(u, u0) && (bChang && checkHex창병(arr2[0]) || !bChang && checkHex극병(arr2[0])))
						acount++;
					if (u1 != null && pk::is_enemy(u, u1) && (bChang && checkHex창병(arr2[1]) || !bChang && checkHex극병(arr2[1])))
						acount++;
					if (acount > maxCount)
					{
						maxCount = acount;
						@maxUnit = unit;
						maxPT = pt0;
					}


				}
			}

			if (maxCount < 2)
				return false;

			if (콘솔_로그_표시)
				pk::printf("전법:횡치시작 {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			move(u, maxPT);
			execute횡치(u, maxUnit.get_pos());
			if (콘솔_로그_표시)
				pk::printf("전법:횡치끝 {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			return true;



			return false;
		}

		
		bool 자동공격_선풍(pk::unit@ u, int rcount)
		{
			if (u.energy < pk::get_tactics(전법_선풍).energy_cost)
				return false;
			if (getMax적성(u, 병종_극병) < 적성_S)
				return false;


			int maxRatio = -1;
			pk::unit@ maxUnit = null;
			pk::point maxPos;
			int acount = 0;
			int maxCount = 0;

			array<pk::point> arr = pk::get_movable_pos(u);
			arr.insertAt(0, u.get_pos());
			for (int i0 = 0; i0 < arr.length; i0++)
			{
				pk::point pt0 = arr[i0];
				if (isOnFire(pt0))
					continue;
				if (pk::get_building(pt0) != null)
					continue;

				acount = 0;
				maxRatio = 0;
				pk::unit@ maxunit2 = null;
				pk::point maxpt2;
				array<pk::point> arr2 = pk::range(pt0, 1, 1);
				for (int i = 0; i < arr2.length; i++)
				{
					pk::point pt = arr2[i];
					pk::unit@ unit = getUnit(pt);
					if (unit == null || !pk::is_enemy(u, unit) || !checkHex극병(pt))
						continue;

					acount++;
					int nTactics = callback202(u, pt, unit, 전법_선풍);
					if (unit.has_skill(특기_철벽) || unit.has_skill(특기_불굴) || unit.has_skill(특기_금강))
						nTactics = 0;
					if (nTactics >= maxRatio)
					{
						@maxunit2 = unit;
						maxpt2 = pt0;
						maxRatio = nTactics;
					}
				}
				if (acount > maxCount)
				{
					@maxUnit = maxunit2;
					maxPos = maxpt2;
					maxCount = acount;
				}
			}

			if (maxCount >= rcount && maxUnit != null)
			{
				if (콘솔_로그_표시)
					pk::printf("전법:선풍시작 {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
				move(u, maxPos);
				execute선풍(u, maxUnit.get_pos());
				if (콘솔_로그_표시)
					pk::printf("전법:선풍끝 {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
				return true;
			}
			return false;
		}

		bool 자동공격_창병_극병_나선첨(pk::unit@ u, bool bChang)
		{
			if (u.energy < pk::get_tactics(전법_나선첨).energy_cost)
				return false;
			if (!bChang && pk::has_tech(u, 기교_정예극병))
				return false;
			if (u.weapon == 병기_극 && getMax적성(u, 병종_극병) < 적성_A)
				return false;
			if (u.weapon == 병기_창 && getMax적성(u, 병종_창병) < 적성_A)
				return false;

			int maxAttack = 0;
			pk::unit@ maxUnit = null;
			pk::point maxPos;

			array<pk::point> arr = pk::get_movable_pos(u);
			arr.insertAt(0, u.get_pos());

			for (int i0 = 0; i0 < arr.length; i0++)
			{
				pk::point pt0 = arr[i0];
				if (isOnFire(pt0))
					continue;
				if (pk::get_building(pt0) != null)
					continue;

				for (int i = 0; i < 방향_끝; i++)
				{
					pk::point pt = pk::get_neighbor_pos(pt0, i, 1);
					pk::unit@ unit = getUnit(pt);
					if (unit == null || !pk::is_enemy(u, unit))
						continue;
					if (bChang && !checkHex창병(pt))
						continue;
					if (!bChang && !checkHex극병(pt))
						continue;

					if (u.attr.stat[부대능력_무력] > unit.attr.stat[부대능력_무력] && unit.attr.stat[부대능력_공격] > maxAttack)
					{
						maxPos = pt0;
						maxAttack = unit.attr.stat[부대능력_공격];
						@maxUnit = unit;
					}
				}
			}

			if (maxUnit == null)
				return false;

			if (콘솔_로그_표시)
				pk::printf("전법:나선첨시작 {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			move(u, maxPos);
			execute나선첨(u, maxUnit.get_pos());
			if (콘솔_로그_표시)
				pk::printf("전법:나선첨끝 {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));

			return true;
		}
		bool 자동공격_창병_이단첨(pk::unit@ u)
		{
			if (u.energy < pk::get_tactics(전법_이단첨).energy_cost)
				return false;
			if (getMax적성(u, 병종_창병) < 적성_S)
				return false;


			array<pk::point> arr = pk::get_movable_pos(u);
			arr.insertAt(0, u.get_pos());

			int maxTact = 0;
			pk::unit@ maxUnit = null;
			pk::point maxPt;
			for (int i = 0; i < arr.length; i++)
			{
				pk::point pt = arr[i];
				if (isOnFire(pt))
					continue;
				if (pk::get_building(pt) != null)
					continue;

				for (int j = 0; j < 방향_끝; j++)
				{
					pk::point pt2 = pk::get_neighbor_pos(pt, j, 1);
					pk::unit@ unit = getUnit(pt2);
					if (unit == null || !pk::is_enemy(u, unit))
						continue;
					if (!checkHex창병(pt2))
						continue;

					int nTactics = callback202(u, pt2, unit, 전법_이단첨);
					if (nTactics > maxTact)
					{
						maxTact = nTactics;
						@maxUnit = unit;
						maxPt = pt;
					}
				}//j
			}//i

			if (maxUnit == null)
				return false;

			if (콘솔_로그_표시)
				pk::printf("전법:이단첨 시작 {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			move(u, maxPt);
			execute이단첨(u, maxUnit.get_pos());
			if (콘솔_로그_표시)
				pk::printf("전법:이단첨 끝 {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));

			return true;
		}

		bool 자동공격_창병_돌출(pk::unit@ u)
		{
			if (u.energy < pk::get_tactics(전법_돌출).energy_cost)
				return false;
			if (getMax적성(u, 병종_창병) < 적성_B)
				return false;

			array<pk::point> arr = pk::get_movable_pos(u);
			arr.insertAt(0, u.get_pos());

			int maxTact = 0;
			pk::unit@ maxUnit = null;
			pk::point maxPt;
			for (int i = 0; i < arr.length; i++)
			{
				pk::point pt = arr[i];
				if (isOnFire(pt))
					continue;
				if (pk::get_building(pt) != null)
					continue;

				for (int j = 0; j < 방향_끝; j++)
				{
					pk::point pt2 = pk::get_neighbor_pos(pt, j, 1);
					pk::unit@ unit = getUnit(pt2);
					if (unit == null || !pk::is_enemy(u, unit))
						continue;
					if (!checkHex창병(pt2))
						continue;

					int nTactics = callback202(u, pt2, unit, 전법_돌출);
					if (nTactics > maxTact)
					{
						maxTact = nTactics;
						@maxUnit = unit;
						maxPt = pt;
					}
				}//j
			}//i

			if (maxUnit == null)
				return false;

			if (콘솔_로그_표시)
				pk::printf("전법:돌출 시작 {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			move(u, maxPt);
			execute돌출(u, maxUnit.get_pos());
			if (콘솔_로그_표시)
				pk::printf("전법:돌출 끝 {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));

			return true;
		}

		bool 자동공격_극병_갈퀴(pk::unit@ u)
		{
			if (u.energy < pk::get_tactics(전법_갈퀴).energy_cost)
				return false;
			if (getMax적성(u, 병종_극병) < 적성_B)
				return false;


			array<pk::point> arr = pk::get_movable_pos(u);
			arr.insertAt(0, u.get_pos());

			int maxTact = 0;
			pk::unit@ maxUnit = null;
			pk::point maxPt;
			for (int i = 0; i < arr.length; i++)
			{
				pk::point pt = arr[i];
				if (isOnFire(pt))
					continue;
				if (pk::get_building(pt) != null)
					continue;

				for (int j = 0; j < 방향_끝; j++)
				{
					pk::point pt2 = pk::get_neighbor_pos(pt, j, 1);
					pk::unit@ unit = getUnit(pt2);
					if (unit == null || !pk::is_enemy(u, unit))
						continue;
					if (!checkHex극병(pt2))
						continue;
					pk::point pt3 = get갈퀴pos(pt, pt2);
					if (isOnFire(pt3))
						continue;

					int nTactics = callback202(u, pt2, unit, 전법_갈퀴);
					if (nTactics > maxTact)
					{
						maxTact = nTactics;
						@maxUnit = unit;
						maxPt = pt;
					}
				}
			}
			if (maxUnit == null)
				return false;

			if (콘솔_로그_표시)
				pk::printf("전법:갈퀴시작 {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			move(u, maxPt);
			execute갈퀴(u, maxUnit.get_pos());
			if (콘솔_로그_표시)
				pk::printf("전법:갈퀴끝 {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));

			return true;
		}

		bool 자동공격_난사(pk::unit@ u)
		{
			if (u.energy < pk::get_tactics(전법_난사).energy_cost)
				return false;
			if (getMax적성(u, 병종_노병) < 적성_S)
				return false;


			//3명이상되면 발사
			int dist = getMaxAttackDistance(u);
			//int dist = 2;
			int minDist = 2;
			int curDist = 2;
			bool b궁신 = u.has_skill(특기_궁신);

			int maxCount = 0;
			pk::unit@ maxUnit = null;
			pk::building@ maxBuilding = null;
			pk::point maxPT;

			array<pk::point> arr = pk::get_movable_pos(u);
			arr.insertAt(0, u.get_pos());
			for (int i0 = 0; i0 < arr.length; i0++)
			{
				pk::point pt0 = arr[i0];
				if (isOnFire(pt0))
					continue;
				if (pk::get_building(pt0) != null)
					continue;

				array<pk::point> arr2 = pk::range(pt0, curDist, dist);
				for (int i = 0; i < arr2.length; i++)
				{
					pk::point pt = arr2[i];
					pk::unit@ unit = getUnit(pt);
					pk::building@ b = getBuilding(pt);
					if ((unit == null || !pk::is_enemy(u, unit)) && (b == null || !pk::is_enemy(u, b)))
						continue;
					if (!checkHex노병(u, pt))
						continue;

					int acount = 0;
					bool bMine = false;
					array<pk::point> arr3 = pk::range(pt, 0, 1);
					for (int j = 0; j < arr3.length; j++)
					{
						pk::point pt2 = arr3[j];
						pk::unit@ unit2 = getUnit(pt2);
						pk::building@ b2 = getBuilding(pt2);
						if (unit2 == null && b2 == null)
							continue;
						if (!checkHex노병(u, pt2))
							continue;

						if (!b궁신 && ((unit2 != null && !pk::is_enemy(u, unit2)) || (b2 != null && !pk::is_enemy(u, b2))))
						{
							bMine = true;
							break;
						}
						if ((unit2 != null && !pk::is_enemy(u, unit2)) || (b2 != null && !pk::is_enemy(u, b2)))
							continue;
						acount++;
					}

					if (b != null && ((b.facility == 시설_도시) || b.facility == 시설_관문 || b.facility == 시설_항구))
						acount = 3;
					if (bMine || acount < 3)
						continue;


					if (acount > maxCount)
					{
						maxCount = acount;
						@maxUnit = unit;
						@maxBuilding = b;
						maxPT = pt0;
					}
					else if (acount == maxCount)
					{
						if (unit != null && maxBuilding != null)
						{
							maxCount = acount;
							@maxUnit = unit;
							@maxBuilding = b;
							maxPT = pt0;
						}
					}
				}
			}
			if (maxUnit == null && maxBuilding == null)
				return false;

			if (콘솔_로그_표시)
				pk::printf("전법:난사시작 {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			move(u, maxPT);
			execute난사(u, maxUnit != null ? maxUnit.get_pos() : maxBuilding.get_pos());
			if (콘솔_로그_표시)
				pk::printf("전법:난사끝 {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			return true;
		}
		bool 자동공격_관시(pk::unit@ u)
		{
			if (u.energy < pk::get_tactics(전법_관시).energy_cost)
				return false;
			if (getMax적성(u, 병종_노병) < 적성_A)
				return false;

			int dist = getMaxAttackDistance(u);
			int curDist = 2;

			int maxCount = 0;
			pk::unit@ maxUnit = null;
			pk::building@ maxBuilding = null;
			pk::point maxPT;

			array<pk::point> arr = pk::get_movable_pos(u);
			arr.insertAt(0, u.get_pos());
			for (int i0 = 0; i0 < arr.length; i0++)
			{
				pk::point pt0 = arr[i0];
				if (isOnFire(pt0))
					continue;
				if (pk::get_building(pt0) != null)
					continue;

				array<pk::point> arr2 = pk::range(pt0, curDist, dist);
				for (int i = 0; i < arr2.length; i++)
				{
					pk::point pt = arr2[i];
					pk::unit@ unit = getUnit(pt);
					pk::building@ b = getBuilding(pt);
					if ((unit == null || !pk::is_enemy(u, unit)) && (b == null || !pk::is_enemy(u, b)))
						continue;
					if (!checkHex노병(u, pt))
						continue;

					array<pk::point> arr3;
					int diff = pk::get_distance(pt0, pt);
					int dir = pk::get_direction(pt0,pt);
					for (int k = 1; k <= diff; k++)
					{
						pk::point pt2 = pk::get_neighbor_pos(pt0, dir, k);
						arr3.insertLast(pt2);
					}

					int acount = 0;
					for (int j = 0; j < arr3.length; j++)
					{
						pk::point pt2 = arr3[j];
						pk::unit@ unit2 = getUnit(pt2);
						pk::building@ b2 = getBuilding(pt2);
						if (unit2 == null && b2 == null)
							continue;
						if (!checkHex노병(u, pt2))
							continue;
						if ((unit2 != null && !pk::is_enemy(u, unit2)) || (b2 != null && !pk::is_enemy(u, b2)))
							continue;
						acount++;
					}
					if (acount < 2)
						continue;

					if (acount > maxCount)
					{
						maxCount = acount;
						@maxUnit = unit;
						@maxBuilding = b;
						maxPT = pt0;
					}
				}
			}

			if (maxUnit == null && maxBuilding == null)
				return false;

			if (콘솔_로그_표시)
				pk::printf("전법:관시시작 {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			move(u, maxPT);
			execute관시(u, maxUnit != null ? maxUnit.get_pos() : maxBuilding.get_pos());
			if (콘솔_로그_표시)
				pk::printf("전법:관시끝 {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			return true;

		}

		bool 자동공격_함선화시(pk::unit@ u)
		{
			if (u.energy < pk::get_tactics(전법_함선화시).energy_cost)
				return false;
			if (getMax적성(u, 병종_수군) < 적성_B)
				return false;

			int dist = getMaxAttackDistance(u);
			int curDist = 2;

			int maxCount = 0;
			pk::unit@ maxUnit = null;
			pk::building@ maxBuilding = null;
			pk::point maxPT;

			array<pk::point> arr = pk::get_movable_pos(u);
			arr.insertAt(0, u.get_pos());
			for (int i0 = 0; i0 < arr.length; i0++)
			{
				pk::point pt0 = arr[i0];
				if (isOnFire(pt0))
					continue;
				if (pk::get_building(pt0) != null)
					continue;

				array<pk::point> arr2 = pk::range(pt0, curDist, dist);
				for (int i = 0; i < arr2.length; i++)
				{
					pk::point pt = arr2[i];
					pk::unit@ unit = getUnit(pt);
					pk::building@ b = getBuilding(pt);
					if ((unit == null || !pk::is_enemy(u, unit)) && (b == null || !pk::is_enemy(u, b)))
						continue;

					array<pk::point> arr3;
					int diff = pk::get_distance(pt0, pt);
					int dir = pk::get_direction(pt0, pt);
					for (int k = 1; k <= diff; k++)
					{
						pk::point pt2 = pk::get_neighbor_pos(pt0, dir, k);
						arr3.insertLast(pt2);
					}

					int acount = 0;
					for (int j = 0; j < arr3.length; j++)
					{
						pk::point pt2 = arr3[j];
						pk::unit@ unit2 = getUnit(pt2);
						pk::building@ b2 = getBuilding(pt2);
						if (unit2 == null && b2 == null)
							continue;
						if ((unit2 != null && !pk::is_enemy(u, unit2)) || (b2 != null && !pk::is_enemy(u, b2)))
							continue;
						acount++;
					}
					if (acount < 2)
						continue;

					if (acount > maxCount)
					{
						maxCount = acount;
						@maxUnit = unit;
						@maxBuilding = b;
						maxPT = pt0;
					}
				}
			}

			if (maxUnit == null && maxBuilding == null)
				return false;

			if (콘솔_로그_표시)
				pk::printf("전법:함선화시시작 {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			move(u, maxPT);
			execute함선화시(u, maxUnit != null ? maxUnit.get_pos() : maxBuilding.get_pos());
			if (콘솔_로그_표시)
				pk::printf("전법:함선화시끝 {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			return true;

		}
		bool 자동공격_함선격돌(pk::unit@ u)
		{
			if (u.energy < pk::get_tactics(전법_함선격돌).energy_cost)
				return false;
			if (getMax적성(u, 병종_수군) < 적성_A)
				return false;
			if (u.weapon != 병기_누선 && u.weapon != 병기_투함)
				return false;

			array<pk::point> arr = pk::get_movable_pos(u);
			arr.insertAt(0, u.get_pos());

			int maxTact = 0;
			pk::unit@ maxUnit = null;
			pk::point maxPt;
			for (int i = 0; i < arr.length; i++)
			{
				pk::point pt = arr[i];
				if (isOnFire(pt))
					continue;
				if (pk::get_building(pt) != null)
					continue;

				for (int j = 0; j < 방향_끝; j++)
				{
					pk::point pt2 = pk::get_neighbor_pos(pt, j, 1);
					pk::unit@ unit = getUnit(pt2);
					if (unit == null || !pk::is_enemy(u, unit))
						continue;
					int nTactics = callback202(u, pt2, unit, 전법_함선격돌);
					if (nTactics > maxTact)
					{
						maxTact = nTactics;
						@maxUnit = unit;
						maxPt = pt;
					}
				}//j
			}//i

			if (maxUnit == null)
				return false;

			if (콘솔_로그_표시)
				pk::printf("전법:함선격돌 시작 {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			move(u, maxPt);
			execute함선격돌(u, maxUnit.get_pos());
			if (콘솔_로그_표시)
				pk::printf("전법:함선격돌 끝 {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));

			return true;
		}
		bool 자동공격_함선투석(pk::unit@ u)
		{
			if (u.energy < pk::get_tactics(전법_함선투석).energy_cost)
				return false;
			if (getMax적성(u, 병종_수군) < 적성_S)
				return false;
			if (u.weapon != 병기_투함)
				return false;


			//3명이상되면 발사
			int dist = getMaxAttackDistance(u,true,true);
			if (u.has_skill(특기_사정))
				dist++;
			//int dist = 2;
			int minDist = 2;
			int curDist = 2;

			int maxCount = 0;
			pk::unit@ maxUnit = null;
			pk::building@ maxBuilding = null;
			pk::point maxPT;

			array<pk::point> arr = pk::get_movable_pos(u);
			arr.insertAt(0, u.get_pos());
			for (int i0 = 0; i0 < arr.length; i0++)
			{
				pk::point pt0 = arr[i0];
				if (isOnFire(pt0))
					continue;
				if (pk::get_building(pt0) != null)
					continue;

				array<pk::point> arr2 = pk::range(pt0, curDist, dist);
				for (int i = 0; i < arr2.length; i++)
				{
					pk::point pt = arr2[i];
					pk::unit@ unit = getUnit(pt);
					pk::building@ b = getBuilding(pt);
					if ((unit == null || !pk::is_enemy(u, unit)) && (b == null || !pk::is_enemy(u, b)))
						continue;

					int acount = 0;
					bool bMine = false;
					array<pk::point> arr3 = pk::range(pt, 0, 1);
					for (int j = 0; j < arr3.length; j++)
					{
						pk::point pt2 = arr3[j];
						pk::unit@ unit2 = getUnit(pt2);
						pk::building@ b2 = getBuilding(pt2);
						if (unit2 == null && b2 == null)
							continue;
						if (((unit2 != null && !pk::is_enemy(u, unit2)) || (b2 != null && !pk::is_enemy(u, b2))))
						{
							bMine = true;
							break;
						}
						acount++;
					}
					if (b != null && ((b.facility == 시설_도시) || b.facility == 시설_관문 || b.facility == 시설_항구))
						acount = 3;
					if (bMine || acount < 3)
						continue;

					if (acount > maxCount)
					{
						maxCount = acount;
						@maxUnit = unit;
						@maxBuilding = b;
						maxPT = pt0;
					}
					else if (acount == maxCount)
					{
						if (unit != null && maxBuilding != null)
						{
							maxCount = acount;
							@maxUnit = unit;
							@maxBuilding = b;
							maxPT = pt0;
						}
					}
				}
			}
			if (maxUnit == null && maxBuilding == null)
				return false;

			if (콘솔_로그_표시)
				pk::printf("전법:함선투석 {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			move(u, maxPT);
			execute함선투석(u, maxUnit != null ? maxUnit.get_pos() : maxBuilding.get_pos());
			if (콘솔_로그_표시)
				pk::printf("전법:함선투석끝 {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			return true;
		}

		bool 자동공격_공성투석(pk::unit@ u)
		{
			if (u.energy < pk::get_tactics(전법_공성투석).energy_cost)
				return false;

			//3명이상되면 발사
			int dist = getMaxAttackDistance(u,true,true);
			if (u.has_skill(특기_사정))
				dist++;

			int minDist = 2;
			int curDist = 2;

			int maxCount = 0;
			pk::unit@ maxUnit = null;
			pk::building@ maxBuilding = null;
			pk::point maxPT;

			array<pk::point> arr = pk::get_movable_pos(u);
			arr.insertAt(0, u.get_pos());
			for (int i0 = 0; i0 < arr.length; i0++)
			{
				pk::point pt0 = arr[i0];
				if (isOnFire(pt0))
					continue;
				if (pk::get_building(pt0) != null)
					continue;

				array<pk::point> arr2 = pk::range(pt0, curDist, dist);
				for (int i = 0; i < arr2.length; i++)
				{
					pk::point pt = arr2[i];
					pk::unit@ unit = getUnit(pt);
					pk::building@ b = getBuilding(pt);
					if ((unit == null || !pk::is_enemy(u, unit)) && (b == null || !pk::is_enemy(u, b)))
						continue;
					if (!checkHex공성(u, pt))
						continue;

					int acount = 0;
					bool bMine = false;
					array<pk::point> arr3 = pk::range(pt, 0, 1);
					for (int j = 0; j < arr3.length; j++)
					{
						pk::point pt2 = arr3[j];
						pk::unit@ unit2 = getUnit(pt2);
						pk::building@ b2 = getBuilding(pt2);
						if (unit2 == null && b2 == null)
							continue;
						if (!checkHex공성(u, pt2))
							continue;

						if (((unit2 != null && !pk::is_enemy(u, unit2)) || (b2 != null && !pk::is_enemy(u, b2))))
						{
							bMine = true;
							break;
						}
						acount++;
					}
					if (bMine || acount < 3)
						continue;

					if (acount > maxCount)
					{
						maxCount = acount;
						@maxUnit = unit;
						@maxBuilding = b;
						maxPT = pt0;
					}
				}
			}
			if (maxUnit == null && maxBuilding == null)
				return false;

			if (콘솔_로그_표시)
				pk::printf("전법:공성투석시작 {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			move(u, maxPT);
			execute공성투석(u, maxUnit != null ? maxUnit.get_pos() : maxBuilding.get_pos());
			if (콘솔_로그_표시)
				pk::printf("전법:공성투석끝 {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			return true;
		}

		bool 자동공격Handler_극병(pk::unit@ u)
		{
			if (자동공격_선풍(u, 3))
				return true;
			if (자동공격_선풍(u, 2))
				return true;
			if (자동공격_창병_극병_횡치(u, false))
				return true;
			if (자동공격_전법교차사용 && pk::rand_bool(자동공격_나선첨_확률) && 자동공격_창병_극병_나선첨(u, false))
				return true;
			if (자동공격_극병_갈퀴(u))
				return true;
			return false;
		}
		bool 자동공격Handler_창병(pk::unit@ u)
		{
			if (자동공격_전법교차사용 && 자동공격_창병_극병_횡치(u, true))
				return true;
			if (pk::rand_bool(자동공격_나선첨_확률) && 자동공격_창병_극병_나선첨(u, true))
				return true;
			if (pk::rand_bool(자동공격_이단첨_확률) && 자동공격_창병_이단첨(u))
				return true;
			return 자동공격_창병_돌출(u);
		}
		bool 자동공격Handler_노병(pk::unit@ u)
		{
			if (자동공격_난사(u))
				return true;
			if (자동공격_관시(u))
				return true;
			if (자동공격_기병_화시(u))
				return true;
			return false;
		}
		bool 자동공격Handler_기병(pk::unit@ u)
		{
			if (pk::rand_bool(자동공격_돌격_확률) && 자동공격_기병_돌격(u))
				return true;
			if (pk::rand_bool(자동공격_돌파_확률) && 자동공격_기병_돌파(u))
				return true;
			if (pk::rand_bool(자동공격_돌진_확률) && 자동공격_기병_돌진(u))
				return true;
			if (자동공격_전법교차사용 && 자동공격_기병_화시(u))
				return true;
			return false;
		}
		bool 자동공격Handler_수군(pk::unit@ u)
		{
			if (자동공격_함선투석(u))
				return true;
			if (u.weapon == 병기_투함 || u.weapon == 병기_누선)
			{
				if (pk::rand_bool(자동공격_함선_화시) && 자동공격_함선화시(u))
					return true;
			}
			else 
			{
				return 자동공격_함선화시(u);
			}
			return 자동공격_함선격돌(u);
		}
		bool 자동공격Handler_공성(pk::unit@ u)
		{
			return 자동공격_공성투석(u);
		}

		bool 자동공격Handler(pk::unit@ u)
		{
			//pk::printf("자동:{}\n", getNameLeader(u));
			if (u.status != 부대상태_통상 || u.action_done)
				return false;
			if (u.order == 부대임무_공격) 
			{
				pk::building@ b = pk::is_valid_pos(u.target_pos) ? pk::get_building(u.target_pos) : null;
				if (b != null && (b.facility == 시설_병영 || b.facility == 시설_병영2단 || b.facility == 시설_병영3단))
				{
					pk::printf("{},병영패스!!!!!!!!!!!!!!!!!\n", getNameLeader(u));
					return false;
				}
			}
			if (!pk::rand_bool(자동공격_확률))
				return false;

			bool b = false;
			switch (u.weapon)
			{
			case 병기_창: b=자동공격Handler_창병(u); break;
			case 병기_극: b=자동공격Handler_극병(u); break;
			case 병기_노: b=자동공격Handler_노병(u); break;
			case 병기_군마: b=자동공격Handler_기병(u); break;
			case 병기_주가: case 병기_누선: case 병기_투함:
				b = 자동공격Handler_수군(u);
				break;
			case 병기_투석:
				b = 자동공격Handler_공성(u);
			default:
				break;
			}
			return b;
		}

		////////////////////////////////////////////////////////////////////////////////////

		int get일기토무장Attacker(pk::unit@ u)
		{
			int max무력 = -1;
			int max무장 = -1;
			for (int i = 0; i < 3; i++)
			{
				pk::person@ p = pk::get_person(u.member[i]);
				if (p == null)
					continue;

				if (p.max_stat[무장능력_무력] > max무력)
				{
					max무력 = p.max_stat[무장능력_무력];
					max무장 = p.get_id();
				}
			}
			return max무장;
		}
		int get일기토무장Target(pk::unit@ u)
		{
			int max무력 = -1;
			int min무력 = 1000;
			for (int i = 0; i < 3; i++)
			{
				pk::person@ p = pk::get_person(u.member[i]);
				if (p == null)
					continue;

				if (p.max_stat[무장능력_무력] > max무력)
				{
					max무력 = p.max_stat[무장능력_무력];
				}
				if (p.max_stat[무장능력_무력] < min무력)
				{
					min무력 = p.max_stat[무장능력_무력];
				}
			}

			int sum = 0;
			for (int i = 0; i < 3; i++)
			{
				pk::person@ p = pk::get_person(u.member[i]);
				if (p == null)
					continue;

				sum += (p.max_stat[무장능력_무력] - (min무력 * 0.5));
				if (i == 0)
					sum += 20;
			}
			array<int> arr;
			int pos = 0;
			for (int i = 0; i < 3; i++)
			{
				pk::person@ p = pk::get_person(u.member[i]);
				if (p == null)
					continue;

				int 무력 = (p.max_stat[무장능력_무력] - (min무력 * 0.5));
				if (i == 0)
					무력 += 20;

				int 무력2 = 무력 / float(sum) * 100 + pos;
				pos += (무력 / float(sum) * 100);
				arr.insertLast(무력2);
			}

			int r = pk::rand(100);

			for (int i = 0; i < arr.length; i++)
			{
				if (r <= arr[i])
				{
					return u.member[i];
				}
			}
			return u.member[0];
		}



		pk::list<pk::person@> _scene_attackers;
		pk::list<pk::person@> _scene_targets;
		pk::list<pk::unit@> _scene_attackerUnits;
		pk::list<pk::unit@> _scene_targetUnits;

		int _duel_result = 0;
		pk::person@ _scene_attacker = null;
		pk::person@ _scene_target = null;
		pk::unit@ _scene_attackerUnit = null;
		pk::unit@ _scene_targetUnit = null;

		void scene_일기토()
		{
			//pk::printf("tatical 1:1 {},{}------------------\n",getName(_scene_attacker), getName(_scene_target));
			bool b0 = pk::is_player_controlled(_scene_attackerUnit);
			bool b1 = pk::is_player_controlled(_scene_targetUnit);

			//pk::sleep(2000);
			_duel_result = pk::duel(_scene_attackerUnit, _scene_targetUnit, _scene_attacker, null, null, _scene_target, null, null, b0, b1, 0, b0 || b1).first;

			@_scene_attackerUnit = null;
		}



		string getString(string str)
		{
			switch (pk::rand(4))
			{
			case 0:
				return pk::encode(pk::format("이것이 {}다", str));
			case 1:
				return pk::encode(pk::format("{} 힘을 보여주마", str));
			case 2:
				return pk::encode(pk::format("하핫 어떠냐 {} 위력이", str));
			case 3:
				return pk::encode(pk::format("{} 에는 맞설수 없다", str));
			default:
				break;
			}
			return "";
		}

		array<pk::point> get횡치pos(pk::point spos, pk::point dpos)
		{
			array<pk::point> pts;
			int dir = pk::get_direction(spos, dpos);
			switch (dir)
			{
			case 방향_남:
				pts.insertLast(pk::get_neighbor_pos(spos, 방향_남동, 1));
				pts.insertLast(pk::get_neighbor_pos(spos, 방향_남서, 1));
				break;
			case 방향_남동:
				pts.insertLast(pk::get_neighbor_pos(spos, 방향_북동, 1));
				pts.insertLast(pk::get_neighbor_pos(spos, 방향_남, 1));
				break;
			case 방향_북동:
				pts.insertLast(pk::get_neighbor_pos(spos, 방향_북, 1));
				pts.insertLast(pk::get_neighbor_pos(spos, 방향_남동, 1));
				break;
			case 방향_북:
				pts.insertLast(pk::get_neighbor_pos(spos, 방향_북서, 1));
				pts.insertLast(pk::get_neighbor_pos(spos, 방향_북동, 1));
				break;
			case 방향_북서:
				pts.insertLast(pk::get_neighbor_pos(spos, 방향_남서, 1));
				pts.insertLast(pk::get_neighbor_pos(spos, 방향_북, 1));
				break;
			case 방향_남서:
				pts.insertLast(pk::get_neighbor_pos(spos, 방향_북서, 1));
				pts.insertLast(pk::get_neighbor_pos(spos, 방향_남, 1));
				break;
			default:
				break;
			}
			return pts;
		}
		pk::point get갈퀴pos(pk::point src, pk::point dst)
		{
			int dir = pk::get_direction(dst, src);
			return pk::get_neighbor_pos(dst, dir, 2);
		}

		bool isMovable(pk::point pt,bool bWater=false)
		{
			int h = pk::get_hex(pt).terrain;
			//pk::printf("isMovable,{}\n", h);

			if (bWater)
			{
				return pk::is_enabled_terrain(h) && (h==지형_강 || h==지형_바다);
			}
			else
			{
				bool b = pk::get_hex_object(pt) != null || h == 지형_강 || h == 지형_바다 || h == 지형_관문 || h == 지형_산
					|| h == 지형_도시 || h == 지형_항구 || h == 지형_내 || h == 지형_물가 || !pk::is_enabled_terrain(h);
				return !b;
			}
		}

		pk::point MoveThrough(pk::point pos0, pk::point pos)
		{
			if (!isMovable(pos))
				return pos0;
			else
				return pos;
		}
		pk::point MovePoint(pk::point pos0, pk::point pos,bool bWater=false)
		{
			int dir = pk::get_direction(pos0, pos);

			pk::point pt0 = pk::get_neighbor_pos(pos0, dir, 1);
			if (!isMovable(pt0,bWater))
				return pos0;
			if (pt0.x == pos.x && pt0.y == pos.y)
			{
				return pt0;
			}
			pk::point pt1 = pk::get_neighbor_pos(pos0, dir, 2);
			if (!isMovable(pt1, bWater))
			{
				return pt0;
			}
			else
			{
				return pt1;
			}
		}
		void Move(pk::unit@ u, pk::point pos)
		{
			int dir = pk::get_direction(u.get_pos(), pos);

			pk::point pt0 = pk::get_neighbor_pos(u.get_pos(), dir, 1);
			if (!isMovable(pt0))
				return;

			if (pt0.x == pos.x && pt0.y == pos.y)
			{
				pk::set_pos(u, pt0);
				pk::move(u, { pt0 });
				return;
			}

			pk::point pt1 = pk::get_neighbor_pos(u.get_pos(), dir, 2);
			if (!isMovable(pt1))
			{
				pk::set_pos(u, pt0);
				pk::move(u, { pt0 });
			}
			else
			{
				pk::set_pos(u, pt1);
				pk::move(u, { pt1 });
			}
		}

		int getChaosTime(pk::unit@ u)
		{
			int max = pk::max(u.attr.stat[부대능력_통솔], u.attr.stat[부대능력_지력]);
			int time = pk::max((1 - (max - 50) / 40.0), 0.0) * 2 + 2;
			return time;
		}
		int getMaxAttackDistance(pk::unit@ u, bool bTactics = true,bool b투석정란=false)
		{
			pk::tactics@ tactics_t_화시 = pk::get_tactics(전법_화시);

			pk::force@ f = pk::get_force(u.get_force_id());
			switch (u.weapon)
			{
			case 병기_군마:
				if (pk::has_tech(f, 기교_기사) || u.has_skill(특기_백마))
				{
					return bTactics ? tactics_t_화시.max_range : 2;
				}

				return  1;
			case 병기_창:
			case 병기_극:
				return  1;
			case 병기_노:

				return tactics_t_화시.max_range;
				//return pk::has_tech(f, 기교_강노) ? 3 : 2;
			case 병기_주가:case 병기_누선:case 병기_투함:
				if(b투석정란)
					return pk::get_tactics(전법_함선투석).max_range;
				else
					return pk::get_tactics(전법_함선화시).max_range;
			case 병기_투석:
				return pk::get_tactics(전법_공성투석).max_range;
			default:
				break;
			}
			return 0;
		}

		void updateAssist(pk::unit@ attacker, pk::hex_object@ target, pk::point dst_pos)
		{
			pk::unit@ targetu = target != null ? getUnit(target.get_pos()) : null;
			if (targetu == null)
				return;

			array<pk::point> arr = pk::range(dst_pos, 1, 5);
			for (int i = 0; i < arr.length; i++)
			{
				pk::point pt = arr[i];
				pk::unit@ u = getUnit(pt);
				if (u == null)
					continue;
				if (u.get_id() == attacker.get_id())
					continue;
				if (u.get_force_id() != attacker.get_force_id())
					continue;
				if (u.status != 부대상태_통상)
					continue;


				int dist = pk::get_distance(u.get_pos(), dst_pos);
				if (getMaxAttackDistance(u, false) < dist)
					continue;

				int n = callback200(u, attacker, target);
				if (!pk::rand_bool(n))
					continue;

				pk::damage_info di;
				di.src_pos = u.get_pos();
				di.dst_pos = dst_pos;
				prev_callback_210(di, u, dst_pos);


				string str = "";
				switch (pk::rand(3))
				{
				case 0:str = "이것도 받아라"; break;
				case 1:str = "이건 어떠냐"; break;
				case 2:str = "아직 끝나지 않았다"; break;
				}
				anim(u, dist > 1 ? 1 : 0, { di }, dst_pos, 0, pk::encode(str), 0);

				string str2 = "";
				switch (pk::rand(3))
				{
				case 0:str = pk::format("역시 {} 님", pk::decode(pk::get_name(pk::get_person(u.leader)))); break;
				case 1:str = "하핫 고맙소"; break;
				case 2:str = "이거지~"; break;
				}
				pk::say(str2, pk::get_person(attacker.leader), attacker);

				addTroops(targetu, di);

				updateAfter(u, target);


			}
		}
		void attack(pk::unit@ attacker, pk::hex_object@ target, pk::point dst_pos, int type, bool bCri)
		{
			bool bCri2 = type == 유닛_전법_활공격 ? 크리티컬_원거리 : 크리티컬_근접;
			pk::damage_info di;
			di.src_pos = attacker.get_pos();
			di.dst_pos = dst_pos;
			callback209(di, attacker, 0, dst_pos, 0, bCri ? 1 : 0, false);
			anim(attacker, type, { di }, dst_pos, 0, pk::encode("받아라!"), 0);

			pk::unit@ targetU = getUnit(dst_pos);

			if (!금강불굴(di, target) && !화살방패_큰방패(attacker, targetU, type == 유닛_전법_근접공격))
			{
				addTroops(target, di);
				updateAfter(attacker, target);
				update(attacker, dst_pos, { di }, bCri2, false);

				int aa = int(pk::core::skill_constant(attacker, 특기_급습));
				if (targetU != null && (!attacker.has_skill(특기_급습) || !pk::rand_bool(aa)))
				{
					pk::damage_info di2;
					di2.src_pos = dst_pos;
					di2.dst_pos = attacker.get_pos();
					callback209(di2, attacker, 0, dst_pos, 0, bCri ? 1 : 0, false);
					anim(targetU, type, { di2 }, attacker.get_pos(), 0, pk::encode("반격이다!"), 0);
					if (!금강불굴(di2, attacker) && !화살방패_큰방패(targetU, attacker, type == 유닛_전법_근접공격))
					{
						addTroops(attacker, di2);
						updateAfter(targetU, attacker);
						update(targetU, attacker.get_pos(), { di2 }, bCri2, true);
					}
				}
			}
			if (연전(attacker))
			{
				sleep();
				if (!금강불굴(di, target) && !화살방패_큰방패(attacker, targetU, type == 유닛_전법_근접공격))
				{
					addTroops(target, di);
					updateAfter(attacker, target);
					update(attacker, dst_pos, { di }, bCri2, false);

					int aa = int(pk::core::skill_constant(attacker, 특기_급습));
					if (targetU != null && (!attacker.has_skill(특기_급습) || !pk::rand_bool(aa)))
					{
						pk::damage_info di2;
						di2.src_pos = dst_pos;
						di2.dst_pos = attacker.get_pos();
						callback209(di2, attacker, 0, dst_pos, 0, bCri ? 1 : 0, false);
						anim(targetU, type, { di2 }, attacker.get_pos(), 0, pk::encode("반격이다!"), 0);
						if (!금강불굴(di2, attacker) && !화살방패_큰방패(targetU, attacker, type == 유닛_전법_근접공격))
						{
							addTroops(attacker, di2);
							updateAfter(targetU, attacker);
							update(targetU, attacker.get_pos(), { di2 }, bCri2, true);
						}
					}
				}
			}

		}

		void attackFail(pk::unit@ attacker, pk::hex_object@ target, pk::point dst_pos, int type, bool bCri)
		{
			bool bCri2 = type == 유닛_전법_활공격 ? 크리티컬_원거리 : 크리티컬_근접;
			int r = pk::rand(100);
			if (r <= 전법실패시_일반공격_확률)
			{
				pk::damage_info di;
				di.src_pos = attacker.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, attacker, 0, dst_pos, 0, bCri ? 1 : 0, false);
				anim(attacker, type, { di }, dst_pos, 0, pk::encode("칫 이것밖엔.."), 0);
				if (!금강불굴(di, target))
				{
					addTroops(target, di);
					updateAfter(attacker, target);
					update(attacker, dst_pos, { di }, bCri2, false);
					if (연전(attacker))
					{
						sleep();
						anim(attacker, type, { di }, dst_pos, 0, pk::encode("칫 이것밖엔.."), 0);
						addTroops(target, di);
						updateAfter(attacker, target);
						update(attacker, dst_pos, { di }, bCri2, false);
					}
				}

			}
			else if (r > 전법실패시_일반공격_확률 and r < 전법실패시_일반공격_확률 + 전법실패시_일반공격_무데미지_확률)
			{
				pk::damage_info di;
				di.src_pos = attacker.get_pos();
				di.dst_pos = dst_pos;
				di.troops_damage = 0;
				//prev_callback_202전법성공(di, attacker, type, dst_pos, 0, bCri ? 1 : 0, false);

				anim(attacker, type, { di }, dst_pos, 0, pk::encode("통하지 않는가.."), 0);
				addTroops(target, di);
				updateAfter(attacker, target);
				update(attacker, dst_pos, { di }, bCri2, false);
			}
			else
			{
				int dist = pk::get_distance(attacker.get_pos(), dst_pos);
				if (getMaxAttackDistance(target, false) < dist)
					return;

				pk::damage_info di;
				di.src_pos = dst_pos;
				di.dst_pos = attacker.get_pos();
				callback209(di, target, 1, attacker.get_pos(), 0, bCri ? 1 : 0, false);

				anim(target, type, { di }, attacker.get_pos(), 1, pk::encode("반격이다"), 0);
				addTroops(attacker, di);
				updateAfter(target, attacker);
				update(attacker, dst_pos, { di }, bCri2, false, true);
			}
		}
		bool updateAfter(pk::unit@ attacker, pk::hex_object@ target)
		{
			if (target == null)
				return false;

			pk::unit@ targetU = getUnit(target.get_pos());
			if (targetU != null && targetU.troops == 0)
			{
				int dist = pk::get_distance(attacker.get_pos(), target.get_pos());
				//pk::printf("kill start\n");
				int gold = targetU.gold;
				int food = targetU.food;

				pk::create_death_effect(targetU, attacker, target.get_pos());
				pk::kill(targetU, attacker, dist == 1, attacker.weapon == 병기_극);

				//if (dist == 1)
				//{
				//	if (gold * 0.5 > 0)
				//		pk::add_gold(attacker, gold * 0.5, true);
				//	if (food * 0.5 > 0)
				//		pk::add_food(attacker, food * 0.25, true);
				//}

				//pk::printf("kill end\n");
				if (attacker.has_skill(특기_앙양))
					pk::add_energy(attacker, int(pk::core::skill_constant(attacker, 특기_앙양)), true);

				return false;
			}
			else
			{
				pk::building@ b = pk::hex_object_to_building(target);
				if (b != null)
				{
					if (b.hp <= 0)
					{
						pk::city@ city = pk::building_to_city(b);
						pk::gate@ gate = pk::building_to_gate(b);
						pk::port@ port = pk::building_to_port(b);

						if (city != null || gate != null || port != null)
						{
							pk::set_hp(b, 1);
						}
						else
						{
							pk::destroy_cmd_info di;
							@di.building = b;
							pk::command(di);
							return false;
						}
					}
				}
			}
			return true;

		}

		void update맹장(pk::unit@ attacker, pk::hex_object@ target, pk::point dest0)
		{
			pk::unit@ u = target != null ? getUnit(target.get_pos()) : null;
			if (u == null || !attacker.has_skill(특기_맹장) || u.has_skill(특기_호위))
				return;
			if (target.get_pos().x == dest0.x && target.get_pos().y == dest0.y)
				return;

			int maxValue = int(pk::core::skill_constant(attacker, 특기_맹장));
			if (u.member[0] >= 0 && u.member[0] < 무장_끝 && pk::rand_bool(maxValue))
				injury(pk::get_person(u.member[0]));
			if (u.member[1] >= 0 && u.member[1] < 무장_끝 && pk::rand_bool(maxValue))
				injury(pk::get_person(u.member[1]));
			if (u.member[2] >= 0 && u.member[2] < 무장_끝 && pk::rand_bool(maxValue))
				injury(pk::get_person(u.member[2]));
		}
		void injury(pk::person@ p)
		{
			if (pk::has_skill(p, 특기_강운))
				return;
			string strType = "";
			switch (p.shoubyou)
			{
			case 상병_건강:p.shoubyou = 상병_경증; strType = "경증"; break;
			case 상병_경증:p.shoubyou = 상병_중증; strType = "중증"; break;
			case 상병_중증:p.shoubyou = 상병_빈사; strType = "빈사"; break;

			default:
				break;
			}
			p.update();

			switch (pk::rand(3))
			{
			case 0: pk::say(pk::encode("팔이.."), p, getUnit(p.get_pos())); break;
			case 1: pk::say(pk::encode("여기선 부상을.."), p, getUnit(p.get_pos())); break;
			case 2: pk::say(pk::encode("아악..이러면"), p, getUnit(p.get_pos())); break;
			default:
				break;
			}

			pk::force@ force = pk::get_force(p.get_force_id());
			pk::person@ kunshu = force != null ? pk::get_person(force.kunshu) : null;
			if (kunshu != null)
			{
				string str = pk::format("\x1b[2x{}\x1b[0x군 \x1b[2x{}\x1b[0x,\x1b[29x{}\x1b[0x 상태", getName(kunshu), getName(p), strType);
				pk::history_log(p.get_pos(), force != null ? force.color : -1, pk::encode(str));
			}
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

		void addTroops(pk::hex_object@ obj, pk::damage_info di, bool bEffect = true)
		{
			addTroops(obj, di.troops_damage, di.hp_damage, bEffect);
		}
		void addTroops(pk::hex_object@ obj, int value, int value2, bool bEffect = true)
		{
			pk::unit@ u;
			pk::building@ b;
			pk::city@ c;
			//pk::printf("addTroops:{},{},{}\n", obj.get_type_id(), value, value2);
			switch (obj.get_type_id())
			{
			case 11:
				@u = pk::hex_object_to_unit(obj);
				if (value == 0)
				{
					pk::create_effect(82, u.get_pos());
					pk::play_se(7);
					return;
				}
				pk::add_troops(u, -value, bEffect);
				break;
			case 5: case 6:case 7: case 8:
				@b = pk::hex_object_to_building(obj);
				pk::add_troops(b, -value, bEffect);
				pk::add_hp(b, -value2, bEffect);
				break;
			default:
				break;
			}
		}


		void updateChaos(pk::unit@ u, pk::unit@ u2)
		{
			pk::set_status(u, u2, 부대상태_혼란, getChaosTime(u), true);
		}
		bool update(pk::unit@ u, pk::point dst_pos, array<pk::damage_info>@ dis, bool bRanged, bool bCri, bool success = true, bool bCounter = false)
		{
			bool b지도 = u.has_skill(특기_지도);

			pk::unit@ attacker = u;
			pk::add_stat_exp(attacker, 무장능력_무력, (success ? 4 : 1) * (b지도 ? 2 : 1));
			pk::add_kouseki(attacker, success ? 100 : 10);

			int type = -1;
			switch (attacker.weapon)
			{
			case 병기_창:type = 병종_창병; break;
			case 병기_노:type = 병종_노병; break;
			case 병기_극:type = 병종_극병; break;
			case 병기_군마:type = 병종_기병; break;
			default:
				break;
			}
			if (type != -1)
			{

				if (attacker.leader >= 0 && attacker.leader < 무장_끝)
				{
					pk::person@ p0 = pk::get_person(attacker.leader);
					pk::add_heishu_exp(p0, type, (success ? 4 : 1) * (b지도 ? 2 : 1));
				}
				if (attacker.member[1] >= 0 && attacker.member[1] < 무장_끝)
				{
					pk::person@ p0 = pk::get_person(attacker.member[1]);
					pk::add_heishu_exp(p0, type, (success ? 4 : 1) * (b지도 ? 2 : 1));
				}
				if (attacker.member[2] >= 0 && attacker.member[2] < 무장_끝)
				{
					pk::person@ p0 = pk::get_person(attacker.member[2]);
					pk::add_heishu_exp(p0, type, (success ? 4 : 1) * (b지도 ? 2 : 1));
				}
			}
			pk::unit@ targetU = getUnit(dst_pos);
			if (targetU != null)
			{
				pk::add_stat_exp(targetU, 무장능력_통솔, b지도 ? 2 : 1);

				int type2 = -1;
				switch (targetU.weapon)
				{
				case 병기_창:type2 = 병종_창병; break;
				case 병기_노:type2 = 병종_노병; break;
				case 병기_극:type2 = 병종_극병; break;
				case 병기_군마:type2 = 병종_기병; break;
				case 병기_정란:case 병기_투석:case 병기_충차:case 병기_목수:type2 = 병종_병기; break;
				case 병기_주가:case 병기_누선:case 병기_투함:type2 = 병종_수군; break;
				default:
					break;
				}
				if (type2 != -1)
				{
					if (targetU.leader >= 0 && targetU.leader < 무장_끝)
					{
						pk::person@ p0 = pk::get_person(targetU.leader);
						pk::add_heishu_exp(p0, type, b지도 ? 2 : 1);
					}
					if (targetU.member[1] >= 0 && targetU.member[1] < 무장_끝)
					{
						pk::person@ p0 = pk::get_person(targetU.member[1]);
						pk::add_heishu_exp(p0, type, b지도 ? 2 : 1);
					}
					if (targetU.member[2] >= 0 && targetU.member[2] < 무장_끝)
					{
						pk::person@ p0 = pk::get_person(targetU.member[2]);
						pk::add_heishu_exp(p0, type, b지도 ? 2 : 1);
					}
				}
			}

			if (!bCounter)
			{
				int sum = 0;
				for (int i = 0; i < dis.length; i++)
				{
					pk::damage_info di = dis[i];
					pk::point ptDst = di.dst_move_pos;
					if (ptDst.x == -1 && ptDst.y == -1)
						ptDst = di.dst_pos;

					pk::unit@ dstU = getUnit(ptDst);
					if (dstU == null)
						continue;
					if (u.has_skill(특기_소탕))
						pk::add_energy(dstU, -int(pk::core::skill_constant(u, 특기_소탕)), true);
					if (u.has_skill(특기_위풍))
						pk::add_energy(dstU, -int(pk::core::skill_constant(u, 특기_위풍)), true);

					sum += di.troops_damage;
				}
				if (!bRanged && u.has_skill(특기_심공))
					pk::add_troops(u, float(pk::core::skill_constant(u, 특기_심공)) * sum, true);
			}


			@targetU = getUnit(dst_pos);
			if (success && targetU != null && u.weapon == 병기_군마 && !bRanged && pk::get_scenario().battle_death != 전사_없음)
			{
				pk::person@ l = pk::get_person(u.leader);
				bool bDie = false;
				if (targetU.leader >= 0 && targetU.leader < 무장_끝)
				{
					pk::person@ p0 = pk::get_person(targetU.leader);
					int n = prev_callback_203기병전법사망(l, p0, (dis.length > 0 ? dis[0].tactics : 전법_돌격), bCri);
					if (n > 0 && pk::rand_bool(n))
					{
						pk::message_box(pk::encode("분하다.."), p0);
						pk::kill(p0, l, targetU, null, 0);
						bDie = true;
					}
				}
				if (!bDie && targetU.member[1] >= 0 && targetU.member[1] < 무장_끝)
				{
					pk::person@ p0 = pk::get_person(targetU.member[1]);
					int n = prev_callback_203기병전법사망(l, p0, (dis.length > 0 ? dis[0].tactics : 전법_돌격), bCri);
					if (n > 0 && pk::rand_bool(n))
					{
						pk::kill(p0, l, targetU, null, 0);
						pk::message_box(pk::encode("분하다.."), p0);
						bDie = true;
					}
				}
				if (!bDie && targetU.member[2] >= 0 && targetU.member[2] < 무장_끝)
				{
					pk::person@ p0 = pk::get_person(targetU.member[2]);
					int n = prev_callback_203기병전법사망(l, p0, (dis.length > 0 ? dis[0].tactics : 전법_돌격), bCri);
					if (n > 0 && pk::rand_bool(n))
					{
						pk::kill(p0, l, targetU, null, 0);
						pk::message_box(pk::encode("분하다.."), p0);
						bDie = true;
					}
				}
			}

			@targetU = getUnit(dst_pos);
			if (success && targetU != null && 전법_일기토_확률 > 0 && pk::rand_bool(전법_일기토_확률))
			{
				//@_scene_attackerUnit = attacker;
				//@_scene_targetUnit = targetU;
				//@_scene_attacker = pk::get_person(attacker.leader);
				//@_scene_target = pk::get_person(targetU.leader);
				//pk::wait(3000);
				//pk::message_box(pk::encode("적장을 찾았다"), _scene_attacker);
				//pk::message_box(pk::encode("좋다 후회하게 될것이다"), _scene_target);
				//pk::scene(pk::scene_t(scene_일기토));

				int attacker무장 = get일기토무장Attacker(attacker);
				if (attacker무장 == -1)
					attacker무장 = attacker.leader;

				int target무장 = get일기토무장Target(targetU);
				if (target무장 == -1)
					target무장 = targetU.leader;


				_scene_attackers.add(pk::get_person(attacker무장));
				_scene_targets.add(pk::get_person(target무장));
				_scene_attackerUnits.add(attacker);
				_scene_targetUnits.add(targetU);
			}


			return getUnit(dst_pos) != null;
		}


		void update(pk::unit@ u, pk::hex_object@ target, pk::point dst_pos, pk::point dst_pos2, int energy)
		{
			updateAssist(u, target, dst_pos2);
			update맹장(u, target, dst_pos);
			pk::add_energy(u, -energy, true);
			pk::set_action_done(u, true);
			pk::action_done(u, u.get_pos());
			u.action_done = true;
			u.update();
		}
		bool 금강불굴(pk::damage_info di, pk::hex_object@ target)
		{
			pk::unit@ u = target != null ? getUnit(target.get_pos()) : null;
			if (u == null)
				return false;
			if (u.status != 부대상태_통상)
				return false;

			if (u.has_skill(특기_금강))
			{
				int val = int(pk::core::skill_constant(u, 특기_금강, 0));
				int ratio = int(pk::core::skill_constant(u, 특기_금강, 1));
				if (di.troops_damage < val && pk::rand_bool(ratio))
				{
					pk::create_effect(82, target.get_pos());
					pk::play_se(7);
					return true;
				}
			}
			if (u.has_skill(특기_불굴))
			{
				int val = int(pk::core::skill_constant(u, 특기_불굴, 0));
				int ratio = int(pk::core::skill_constant(u, 특기_불굴, 1));
				if (u.troops < val && pk::rand_bool(ratio))
				{
					pk::create_effect(82, target.get_pos());
					pk::play_se(7);
					return true;
				}
			}
			return false;
		}
		bool 화살방패_큰방패(pk::unit@ attacker, pk::unit@ target, bool b근접)
		{
			if (target == null || target.weapon != 병기_극)
				return false;
			if (target.status != 부대상태_통상)
				return false;

			if (b근접 && pk::has_tech(target, 기교_큰방패) && pk::rand_bool(30))
				return true;
			if (!b근접 && pk::has_tech(target, 기교_화살방패) && pk::rand_bool(30))
				return true;

			return false;
		}

		bool 연전(pk::unit@ u)
		{
			int val = int(pk::core::skill_constant(u, 특기_연전));
			bool b = bool(pk::core["초특기연전"]);
			return b && u.has_skill(특기_연전) && pk::rand_bool(val);
		}
		void cutin(pk::unit@ u)
		{
			if (!pk::is_player_controlled(u))
				return;
			pk::face_cutin(u);
		}
		pk::unit@ getUnit(pk::point pos)
		{
			return pk::is_valid_pos(pos) ? pk::get_unit(pos) : null;
		}
		pk::building@ getBuilding(pk::point pos)
		{
			return pk::is_valid_pos(pos) ? pk::get_building(pos) : null;
		}

		bool checkHex노병(pk::unit@ u, pk::point pt)
		{
			pk::tactics@ t = pk::get_tactics(전법_화시);
			if (t.terrain[pk::get_hex(pt).terrain])
				return true;
			if (!u.has_skill(특기_사수) && pk::get_hex(pt).terrain == 지형_숲)
				return false;
			int h = pk::get_hex(pt).terrain;
			//if (h == 지형_강 || h == 지형_바다 || h == 지형_산)
			//	return false;
			return true;
		}
		bool checkHex공성(pk::unit@ u, pk::point pt)
		{
			pk::tactics@ t = pk::get_tactics(전법_공성투석);
			return (t.terrain[pk::get_hex(pt).terrain]);
		}

		bool checkHex창병(pk::point pt)
		{
			int h = pk::get_hex(pt).terrain;
			if (h == 지형_강 || h == 지형_바다 || h == 지형_산 || h == 지형_모래)
				return false;
			return true;
		}
		bool checkHex극병(pk::point pt)
		{
			int h = pk::get_hex(pt).terrain;
			if (h == 지형_강 || h == 지형_바다 || h == 지형_산)
				return false;
			return true;
		}
		bool checkHex기병(pk::point pt)
		{
			pk::tactics@ tactics_t_돌격 = pk::get_tactics(전법_돌격);
			return tactics_t_돌격.terrain[pk::get_hex(pt).terrain];

			switch (pk::get_hex(pt).terrain)
			{
			case 지형_황무지:
			case 지형_대로:
			case 지형_초원:
			case 지형_땅:
			case 지형_모래:
			case 지형_샛길:
			case 지형_다리:
				return true;
			}
			return false;
		}
		void anim(pk::unit@ unit, int id, const array<pk::damage_info>& params, const pk::point& col_pos, int delay, string say, int say_delay)
		{
			if (pk::is_in_screen(unit.get_pos()) && pk::is_in_screen(col_pos))
				pk::unit_anim(unit, id, params, col_pos, delay, say, say_delay);
		}
		void move(pk::unit@ u, pk::point pt)
		{
			pk::point pt0 = u.get_pos();
			if (pt0.x == pt.x && pt0.y == pt.y)
				return;
			pk::move(u, { pt });
		}

		void sleep()
		{
			pk::wait(연전_딜레이);
		}

		int getMax적성(pk::unit@ u, int type)
		{
			int max = -1;
			for (int i = 0; i < 3; i++)
			{
				pk::person@ p = pk::is_valid_person_id(u.member[i]) ? pk::get_person(u.member[i]) : null;
				if (p == null)
					continue;

				if (p.tekisei[type] > max)
				{
					max = p.tekisei[type];
				}
			}
			return max;
		}
		bool isOnFire(pk::point pt)
		{
			return pk::is_valid_pos(pt) ? pk::is_on_fire(pt) : true;
		}


	}

	Main main;
}

