/*
@������: ũ���Ƚ�
@Update: 2024.5.25���ʹ���
@Update: 2024.5.28 ���Ӱ��ù��׼���
@Update: 2024.6.1 ������ ���� ����ó��
@Update: 2024.6.17 ��������
@Update: 2024.8.17 �������� ������ �ɼ� �߰�.
@Update: 2024.8.19 �������� ���������� ��ø ����,�ⱳ_����ó��
*/
namespace AI�����������_AIForceAttack
{
	const int �������н�_�Ϲݰ���_Ȯ�� = 30;
	const int �������н�_�Ϲݰ���_��������_Ȯ�� = 30;
	const int �������н�_�ݰݸ�_Ȯ�� = 40;


	const int �ڵ�����_ȭ��_�λ�Ȯ�� = 5;
	const bool �ڵ�����_����������� = true; //�⸶å��� �����δ�����Ȯ�� ����
	const bool ��Ÿ�_��ġ = true;
	const int ����_������ = 1000;//ms
	const int ����_�ϱ���_Ȯ�� = 5;

	const int �ڵ�����_Ȯ�� = 80; //20%�� ���� AI���� �ñ�ϴ�. 

	const int �ڵ�����_����÷_Ȯ�� = 50;
	const int �ڵ�����_�̴�÷_Ȯ�� = 50; //���� 25%

	const int �ڵ�����_����_Ȯ�� = 50; 
	const int �ڵ�����_����_Ȯ�� = 50; //���� 25%
	const int �ڵ�����_����_Ȯ�� = 50; //���� 12.5%

	const int �ڵ�����_�Լ�_ȭ�� = 70;

	const float ��������_������_������_���� = 1.5;
	const float ��������_����_������_���� = 1.5;

	const bool �ܼ�_�α�_ǥ�� = true; //���� ������ ������ �� �ְ� �ѵμ���.



	//�������� ������ //////////////////////////////////////////////////////

	const int ����_����_�������� = 0;
	const int ����_����_Ȱ���� = 1;
	const int ����_����_���� = 2;
	const int ����_����_����÷ = 3;
	const int ����_����_�̴�÷ = 4;
	const int ����_����_���� = 5;
	const int ����_����_Ⱦġ = 6;
	const int ����_����_��ǳ = 7;
	const int ����_����_ȭ�� = 8;
	const int ����_����_���� = 9;
	const int ����_����_���� = 10;
	const int ����_����_���� = 11;
	const int ����_����_���� = 12;
	const int ����_����_���� = 13;
	const int ����_����_ȭ��_���� = 14;
	const int ����_����_�ļ�_���� = 15;
	const int ����_����_���_���� = 16;
	const int ����_����_����_���� = 17;
	const int ����_����_��������_�Լ� = 18;
	const int ����_����_Ȱ����_�Լ� = 19;
	const int ����_����_ȭ��_�Լ� = 20;
	const int ����_����_����_�Լ� = 21;
	const int ����_����_�ݵ�_�Լ� = 22;
	const int ����_����_����÷���� = 23;
	const int ����_����_�������ݴ��� = 24;
	const int ����_����_�������ݴ��� = 25;
	const int ����_����_Ȱ���ݴ��� = 26;
	const int ����_����_����_�̴�÷���� = 27;
	const int ����_����_����_�������� = 28;
	const int ����_����_����_�������_1Ÿ�� = 29;
	const int ����_����_����_�������� = 30;
	const int ����_����_����_���Ĵ��� = 31;
	const int ����_����_����_�������� = 32;

	const bool ũ��Ƽ��_���Ÿ� = true;
	const bool ũ��Ƽ��_���� = false;


	class Main
	{

		pk::func203_t@ prev_callback_203�⺴�������;
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


			@prev_callback_203�⺴������� = cast<pk::func203_t@>(pk::get_func(203));
			@prev_callback_210 = cast<pk::func210_t@>(pk::get_func(210));
			@callback202 = cast<pk::func202_t@>(pk::get_func(202));
			@callback201 = cast<pk::func201_t@>(pk::get_func(201));
			@callback209 = cast<pk::func209_t@>(pk::get_func(209));
			@callback200 = cast<pk::func200_t@>(pk::get_func(200));
			@prev_callback_222 = cast<pk::func222_t@>(pk::get_func(222));
			@prev_callback_221 = cast<pk::func221_t@>(pk::get_func(221));


			//pk::menu_item item�ڵ�����;
			//item�ڵ�����.menu = 1;
			//item�ڵ�����.pos = 10;
			//item�ڵ�����.init = pk::unit_menu_item_init_t(init);
			//item�ڵ�����.get_text = pk::menu_item_get_text_t(Get�ڵ�����Text);
			//item�ڵ�����.get_desc = pk::menu_item_get_desc_t(Get�ڵ�����Desc);
			//item�ڵ�����.is_visible = pk::menu_item_is_visible_t(IsVisible�ڵ�����);
			//item�ڵ�����.get_targets = pk::unit_menu_item_get_targets_t(GetTargets�ڵ�����);
			//item�ڵ�����.get_chance = pk::unit_menu_item_get_chance_t(GetChance�ڵ�����);
			//item�ڵ�����.handler = pk::unit_menu_item_handler_t(�ڵ�����Handler);
			//pk::add_menu_item(item�ڵ�����);

		}

		int _count = 0;
		bool callback262(pk::unit@ u)
		{
			if (!pk::is_player_controlled(u) && �ڵ�����Handler(u)) 
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
				if(!us[i].action_done && us[i].status == �δ����_���)
					pk::run_order(us[i]);
				//if (�ڵ�����Handler(us[i]))
				//{
				//	count++;
				//	_�ϷḮ��Ʈ.add(us[i]);
				//}
			}

			pk::reset_func(262);
			if(prev_callback_262!=null)
				pk::set_func(262, prev_callback_262);


			if(�ܼ�_�α�_ǥ�� && us.count > 0)
				pk::printf("�ڵ�:{},{}/{}\n", getName(force != null ? pk::get_person(force.kunshu) : null), _count, us.count);
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
						pk::message_box(pk::encode("������ ã�Ҵ�"), _scene_attacker);
						pk::message_box(pk::encode("���� ��ȸ�ϰ� �ɰ��̴�"), _scene_target);
					}
					pk::scene(pk::scene_t(scene_�ϱ���));
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

		bool IsVisible�ڵ�����()
		{
			return true;
		}
		string Get�ڵ�����Text()
		{
			return pk::encode("�ڵ����� �׽�Ʈ");
		}
		string Get�ڵ�����Desc()
		{
			return pk::encode("�ڵ����� �����մϴ�.");
		}
		pk::array<pk::point_int> GetTargets�ڵ�����()
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
		int GetChance�ڵ�����(pk::point dst_pos)
		{
			return 100;
		}
		bool �ڵ�����Handler(pk::point dst_pos)
		{
			//�ڵ�����_�Լ�ȭ��(_unit);
			//�ڵ�����_�Լ��ݵ�(_unit);
			�ڵ�����Handler_����(_unit);
			return true;
		}



		void execute����(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;


			pk::point dst_pos2 = dst_pos;
			int nTactics = callback202(unit0, dst_pos, target, ����_����);

			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), ����_����, ũ��Ƽ��_����);


			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, ����_����_��������, bCri);
			}
			else
			{

				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, ����_����, dst_pos, 0, bCri ? 1 : 0, false);
				if (!�ݰ��ұ�(di, target))
				{
					int dir = pk::get_direction(unit0.get_pos(), dst_pos);
					pk::point ptA = pk::get_neighbor_pos(unit0.get_pos(), dir, 2);
					pk::point ptT = pk::get_neighbor_pos(dst_pos, dir, 2);
					di.src_move_pos = MoveThrough(unit0.get_pos(), ptA);

					anim(unit0, ����_����_����, { di }, dst_pos, 0, "", 0);
					if (bCri)
						cutin(unit0);


					pk::unit@ u = getUnit(di.dst_pos);
					if (u != null)
					{
						if (unit0.has_skill(Ư��_����) && prev_callback_222(unit0, u) > 0)
							updateChaos(u, unit0);
					}

					move(unit0, MoveThrough(unit0.get_pos(), ptA));


					addTroops(target, di);
					updateAfter(unit0, target);
					bool re = update(unit0, dst_pos, { di }, ũ��Ƽ��_����, bCri);


					//dst_pos2 = di.dst_move_pos;
					if (re && ����(unit0))
					{
						sleep();
						dir = pk::get_direction(unit0.get_pos(), dst_pos);
						pk::point ptA2 = pk::get_neighbor_pos(unit0.get_pos(), dir, 2);
						pk::point ptT2 = pk::get_neighbor_pos(dst_pos, dir, 2);
						di.src_move_pos = MoveThrough(unit0.get_pos(), ptA2);
						di.src_pos = unit0.get_pos();
						anim(unit0, ����_����_����, { di }, dst_pos, 0, "", 0);
						if (bCri)
							cutin(unit0);

						pk::unit@ u2 = getUnit(di.dst_pos);
						if (u2 != null)
						{
							//pk::move(u, { MovePoint(dst_pos, ptT) });
							if (unit0.has_skill(Ư��_����) && prev_callback_222(unit0, u2) > 0)
								updateChaos(u2, unit0);
						}

						move(unit0, MoveThrough(unit0.get_pos(), ptA));

						addTroops(target, di);
						updateAfter(unit0, target);
						update(unit0, dst_pos, { di }, ũ��Ƽ��_����, bCri);
					}
				}
			}

			update(unit0, target, dst_pos, dst_pos2, pk::get_tactics(����_����).energy_cost);
		}

		void execute����(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			pk::point dst_pos2 = dst_pos;
			int nTactics = callback202(unit0, dst_pos, target, ����_����);

			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), ����_����, ũ��Ƽ��_����);


			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, ����_����_��������, bCri);
			}
			else 
			{
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, ����_����, dst_pos, 0, bCri ? 1 : 0, false);
				if (!�ݰ��ұ�(di, target))
				{
					int dir = pk::get_direction(unit0.get_pos(), dst_pos);
					pk::point ptA = pk::get_neighbor_pos(dst_pos, dir, 1);
					di.dst_move_pos = MovePoint(dst_pos, ptA);
					di.src_move_pos = unit0.get_pos();
					if (di.dst_move_pos.x != dst_pos.x || di.dst_move_pos.y != dst_pos.y)
						di.src_move_pos = dst_pos;

					anim(unit0, ����_����_����, { di }, dst_pos, 0, "", 0);
					if (bCri)
						cutin(unit0);

					pk::unit@ u = getUnit(di.dst_pos);
					if (u != null)
					{
						if (unit0.has_skill(Ư��_����) && prev_callback_222(unit0, u) > 0)
							updateChaos(u, unit0);
						
						int dir2 = u.direction;
						move(u, di.dst_move_pos);
						u.direction = dir2;
					}
					move(unit0, di.src_move_pos);
					

					addTroops(target, di);
					updateAfter(unit0, target);
					bool re = update(unit0, di.dst_move_pos, { di }, ũ��Ƽ��_����, bCri);

					dst_pos2 = di.dst_move_pos;
					if (re && ����(unit0))
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

						anim(unit0, ����_����_����, { di }, dst_pos2, 0, "", 0);
						if (bCri)
							cutin(unit0);

						@u = getUnit(di.dst_pos);
						if (u != null)
						{
							if (unit0.has_skill(Ư��_����) && prev_callback_222(unit0, u) > 0)
								updateChaos(u, unit0);

							int dir2 = u.direction;
							move(u, di.dst_move_pos);
							u.direction = dir2;
						}
						move(unit0, di.src_move_pos);


						addTroops(target, di);
						updateAfter(unit0, target);
						update(unit0, di.dst_move_pos, { di }, ũ��Ƽ��_����, bCri);
						dst_pos2 = di.dst_move_pos;
					}
				}
			}
			update(unit0, target, dst_pos, dst_pos2, pk::get_tactics(����_����).energy_cost);
		}

		void execute����(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			pk::point dst_pos2 = dst_pos;
			int nTactics = callback202(unit0, dst_pos, target, ����_����);

			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), ����_����, ũ��Ƽ��_����);


			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, ����_����_��������, bCri);
			}
			else 
			{
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, ����_����, dst_pos, 0, bCri ? 1 : 0, false);
				if (!�ݰ��ұ�(di, target))
				{
					int dir = pk::get_direction(unit0.get_pos(), dst_pos);
					int dir2 = pk::get_direction(dst_pos, unit0.get_pos());

					pk::point ptA = pk::get_neighbor_pos(dst_pos, dir, 2);
					di.dst_move_pos = MovePoint(dst_pos, ptA);
					di.src_move_pos = pk::get_neighbor_pos(di.dst_move_pos, dir2, 1);
					anim(unit0, ����_����_����, { di }, dst_pos, 0, "", 0);
					if (bCri)
						cutin(unit0);

					pk::unit@ u = getUnit(di.dst_pos);
					if (u != null)
					{
						if (unit0.has_skill(Ư��_����) && prev_callback_222(unit0, u) > 0)
							updateChaos(u, unit0);
						int dir2 = u.direction;
						move(u, di.dst_move_pos);
						u.direction = dir2;
					}
					move(unit0, di.src_move_pos);

					addTroops(target, di);
					updateAfter(unit0, target);
					bool re = update(unit0, di.dst_move_pos, { di }, ũ��Ƽ��_����, bCri);

					dst_pos2 = di.dst_move_pos;
					if (re && ����(unit0))
					{
						sleep();
						dir = pk::get_direction(unit0.get_pos(), dst_pos2);
						dir2 = pk::get_direction(dst_pos2, unit0.get_pos());

						ptA = pk::get_neighbor_pos(dst_pos2, dir, 2);
						di.src_pos = unit0.get_pos();
						di.dst_pos = dst_pos2;
						di.dst_move_pos = MovePoint(dst_pos2, ptA);
						di.src_move_pos = pk::get_neighbor_pos(di.dst_move_pos, dir2, 1);

						anim(unit0, ����_����_����, { di }, dst_pos2, 0, "", 0);
						if (bCri)
							cutin(unit0);

						@u = getUnit(di.dst_pos);
						if (u != null)
						{
							if (unit0.has_skill(Ư��_����) && prev_callback_222(unit0, u) > 0)
								updateChaos(u, unit0);
							int dir2 = u.direction;
							move(u, di.dst_move_pos);
							u.direction = dir2;
						}
						move(unit0, di.src_move_pos);

						addTroops(target, di);
						updateAfter(unit0, target);
						update(unit0, di.dst_move_pos, { di }, ũ��Ƽ��_����, bCri);
						dst_pos2 = di.dst_move_pos;
					}
				}
			}
			update(unit0, target, dst_pos, dst_pos2, pk::get_tactics(����_����).energy_cost);
		}


		void execute����(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			pk::point dst_pos2 = dst_pos;
			int nTactics = callback202(unit0, dst_pos, target, ����_����);

			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), ����_����, ũ��Ƽ��_����);
			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, ����_����_��������, bCri);
			}
			else
			{
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, ����_����, dst_pos, 0, bCri ? 1 : 0, false);
				if (!�ݰ��ұ�(di, target))
				{
					int dir = pk::get_direction(dst_pos, unit0.get_pos());
					pk::point ptA = pk::get_neighbor_pos(dst_pos, dir, 2);
					//di.src_move_pos = MoveThrough(unit0.get_pos(), ptA);
					di.src_move_pos = MovePoint(unit0.get_pos(), ptA);
					di.dst_move_pos = di.src_move_pos.x == ptA.x && di.src_move_pos.y == ptA.y ? unit0.get_pos() : dst_pos;

					anim(unit0, ����_����_����, { di }, dst_pos, 0, "", 0);
					if (bCri)
						cutin(unit0);

					pk::point bpt = unit0.get_pos();
					move(unit0, MovePoint(unit0.get_pos(), di.src_move_pos));
					pk::unit@ u = getUnit(dst_pos);
					if (u != null)
						move(u, MovePoint(dst_pos, bpt));


					addTroops(target, di);
					updateAfter(unit0, target);
					bool re = update(unit0, di.dst_move_pos, { di }, ũ��Ƽ��_����, bCri);
					if (re && ����(unit0))
					{
						sleep();
						dst_pos = di.dst_move_pos;

						pk::point ptA2 = pk::get_neighbor_pos(dst_pos, dir, 2);
						di.src_move_pos = MovePoint(unit0.get_pos(), ptA2);
						di.dst_move_pos = di.src_move_pos.x == ptA2.x && di.src_move_pos.y == ptA2.y ? unit0.get_pos() : dst_pos;


						anim(unit0, ����_����_����, { di }, dst_pos, 0, "", 0);
						if (bCri)
							cutin(unit0);

						bpt = unit0.get_pos();
						move(unit0, MovePoint(unit0.get_pos(), di.src_move_pos));
						if (u != null)
							move(u, MovePoint(dst_pos, bpt));
						addTroops(target, di);
						updateAfter(unit0, target);
						update(unit0, di.dst_move_pos, { di }, ũ��Ƽ��_����, bCri);
						dst_pos2 = MovePoint(dst_pos, bpt);
					}

				}

			}
			update(unit0, target, dst_pos, dst_pos2, pk::get_tactics(����_����).energy_cost);
		}
		void execute��ǳ(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;


			int nTactics = callback202(unit0, dst_pos, target, ����_��ǳ);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), ����_��ǳ, ũ��Ƽ��_����);
			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, ����_����_��������, bCri);
			}
			else
			{

				pk::damage_info di0;
				di0.src_pos = unit0.get_pos();
				di0.dst_pos = dst_pos;
				callback209(di0, unit0, ����_��ǳ, dst_pos, 0, bCri ? 1 : 0, false);
				if (!�ݰ��ұ�(di0, target))
				{
					array<pk::damage_info> dis;
					for (int i = 0; i < 6; i++)
					{
						pk::point pt = pk::get_neighbor_pos(unit0.get_pos(), i, 1);
						pk::unit@ uuu = getUnit(pt);
						if (uuu == null)
							continue;
						if (!pk::is_enemy(unit0, uuu) || !checkHex�غ�(pt))
							continue;

						pk::damage_info di2;
						di2.src_pos = unit0.get_pos();
						di2.dst_pos = pt;

						callback209(di2, unit0, ����_��ǳ, pt, 0, bCri ? 1 : 0, false);
						dis.insertLast(di2);
					}
					anim(unit0, ����_����_��ǳ, dis, dst_pos, 0, "", 0);
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
					bool re = update(unit0, dst_pos, dis, ũ��Ƽ��_����, bCri);
					if (re && ����(unit0))
					{
						sleep();
						anim(unit0, ����_����_��ǳ, dis, dst_pos, 0, "", 0);
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
						update(unit0, dst_pos, dis, ũ��Ƽ��_����, bCri);
					}
				}
			}

			update(unit0, target, dst_pos, dst_pos, pk::get_tactics(����_��ǳ).energy_cost);
		}
		void executeȭ��(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			int nTactics = callback202(unit0, dst_pos, target, ����_ȭ��);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), ����_ȭ��, ũ��Ƽ��_���Ÿ�);

			//bTactics = false;
			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, ����_����_Ȱ����, bCri);
			}
			else
			{
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, ����_ȭ��, dst_pos, 0, bCri ? 1 : 0, false);
				if (!�ݰ��ұ�(di, target))
				{
					anim(unit0, ����_����_ȭ��, { di }, dst_pos, 0, "", 0);
					if (bCri)
						cutin(unit0);
					addTroops(target, di);

					pk::unit@ u = getUnit(di.dst_pos);
					if (u != null && !u.has_skill(Ư��_ȣ��))
					{
						if (u.member[0] >= 0 && u.member[0] < ����_�� && pk::rand_bool(�ڵ�����_ȭ��_�λ�Ȯ��))
							injury(pk::get_person(u.member[0]));
						if (u.member[1] >= 0 && u.member[1] < ����_�� && pk::rand_bool(�ڵ�����_ȭ��_�λ�Ȯ��))
							injury(pk::get_person(u.member[1]));
						if (u.member[2] >= 0 && u.member[2] < ����_�� && pk::rand_bool(�ڵ�����_ȭ��_�λ�Ȯ��))
							injury(pk::get_person(u.member[2]));
					}
					bool re = update(unit0, dst_pos, { di }, ũ��Ƽ��_���Ÿ�, bCri);
					re = updateAfter(unit0, target);
					if (re && ����(unit0))
					{
						sleep();
						anim(unit0, ����_����_ȭ��, { di }, dst_pos, 0, "", 0);
						if (bCri)
							cutin(unit0);
						addTroops(target, di);

						@u = getUnit(di.dst_pos);
						if (u != null && !u.has_skill(Ư��_ȣ��))
						{
							if (u.member[0] >= 0 && u.member[0] < ����_�� && pk::rand_bool(�ڵ�����_ȭ��_�λ�Ȯ��))
								injury(pk::get_person(u.member[0]));
							if (u.member[1] >= 0 && u.member[1] < ����_�� && pk::rand_bool(�ڵ�����_ȭ��_�λ�Ȯ��))
								injury(pk::get_person(u.member[1]));
							if (u.member[2] >= 0 && u.member[2] < ����_�� && pk::rand_bool(�ڵ�����_ȭ��_�λ�Ȯ��))
								injury(pk::get_person(u.member[2]));
						}
						update(unit0, dst_pos, { di }, ũ��Ƽ��_���Ÿ�, bCri);
						updateAfter(unit0, target);
					}
				}
			}
			update(unit0, target, dst_pos, dst_pos, pk::get_tactics(����_ȭ��).energy_cost);
		}
		void executeȾġ(pk::unit@ unit0, pk::point dst_pos)
		{

			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			int nTactics = callback202(unit0, dst_pos, target, ����_Ⱦġ);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), ����_Ⱦġ, ũ��Ƽ��_����);

			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, ����_����_��������, bCri);
			}
			else
			{
				array<pk::damage_info> dis;
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, ����_Ⱦġ, dst_pos, 0, bCri ? 1 : 0, false);
				if (!�ݰ��ұ�(di, target))
				{
					dis.insertLast(di);

					array<pk::point> arr = getȾġpos(unit0.get_pos(), dst_pos);
					pk::unit@ u0 = getUnit(arr[0]);
					if (u0 != null && pk::is_enemy(unit0, u0) && checkHex�غ�(arr[0]))
					{
						pk::damage_info di1;
						di1.src_pos = unit0.get_pos();
						di1.dst_pos = arr[0];
						callback209(di1, unit0, ����_Ⱦġ, arr[0], 0, bCri ? 1 : 0, false);
						dis.insertLast(di1);
					}
					pk::unit@ u1 = getUnit(arr[1]);
					if (u1 != null && pk::is_enemy(unit0, u1) && checkHex�غ�(arr[1]))
					{
						pk::damage_info di1;
						di1.src_pos = unit0.get_pos();
						di1.dst_pos = arr[1];
						callback209(di1, unit0, ����_Ⱦġ, arr[1], 0, bCri ? 1 : 0, false);
						dis.insertLast(di1);
					}

					anim(unit0, ����_����_Ⱦġ, { di }, dst_pos, 0, "", 0);
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
					bool re = update(unit0, dst_pos, dis, ũ��Ƽ��_����, bCri);
					if (re && ����(unit0))
					{
						sleep();
						anim(unit0, ����_����_Ⱦġ, { di }, dst_pos, 0, "", 0);
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
					update(unit0, dst_pos, dis, ũ��Ƽ��_����, bCri);
				}
			}
			update(unit0, target, dst_pos, dst_pos, pk::get_tactics(����_Ⱦġ).energy_cost);
		}
		void execute����÷(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			int nTactics = callback202(unit0, dst_pos, target, ����_����÷);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), ����_����÷, ũ��Ƽ��_����);


			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, ����_����_��������, bCri);
			}
			else
			{
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, ����_ȭ��, dst_pos, 0, bCri ? 1 : 0, false);
				if (!�ݰ��ұ�(di, target))
				{
					anim(unit0, ����_����_��������, { di }, dst_pos, 0, "", 0);
					if (bCri)
						cutin(unit0);

					addTroops(target, di);
					updateAfter(unit0, target);
					pk::unit@ u = pk::is_valid_pos(target.get_pos()) ? getUnit(target.get_pos()) : null;
					if (u != null && prev_callback_221(unit0, u, bCri) > 0)
						updateChaos(u, unit0);

					bool re = update(unit0, dst_pos, { di }, ũ��Ƽ��_����, bCri);
					if (re && ����(unit0))
					{
						sleep();
						anim(unit0, ����_����_��������, { di }, dst_pos, 0, "", 0);
						if (bCri)
							cutin(unit0);

						addTroops(target, di);
						updateAfter(unit0, target);
						pk::unit@ u2 = pk::is_valid_pos(target.get_pos()) ? getUnit(target.get_pos()) : null;
						if (u2 != null && prev_callback_221(unit0, u2, bCri) > 0)
							updateChaos(u2, unit0);

						update(unit0, dst_pos, { di }, ũ��Ƽ��_����, bCri);
					}
				}
			}

			update(unit0, target, dst_pos, dst_pos, pk::get_tactics(����_����÷).energy_cost);
			return;
		}
		void execute�̴�÷(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			pk::point dst_pos0 = dst_pos;

			int nTactics = callback202(unit0, dst_pos, target, ����_�̴�÷);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), ����_�̴�÷, ũ��Ƽ��_����);
			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, 1, bCri);
			}
			else
			{
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, ����_�̴�÷, dst_pos, 0, bCri ? 1 : 0, false);
				if (!�ݰ��ұ�(di, target))
				{
					int dir = pk::get_direction(unit0.get_pos(), dst_pos);
					pk::point ptA = pk::get_neighbor_pos(dst_pos, dir, 2);
					di.src_move_pos = unit0.get_pos();
					di.dst_move_pos = MovePoint(dst_pos, ptA);
					anim(unit0, ����_����_�̴�÷, { di }, dst_pos, 0, "", 0);
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
					bool re = update(unit0, di.dst_move_pos, { di }, ũ��Ƽ��_����, bCri);
					pk::point dst_pos2 = di.dst_move_pos;
					dst_pos0 = dst_pos2;
					if (re && ����(unit0))
					{
						sleep();
						pk::point ptA2 = pk::get_neighbor_pos(dst_pos2, dir, 2);
						di.src_pos = unit0.get_pos();
						di.dst_pos = dst_pos2;
						di.src_move_pos = unit0.get_pos();
						di.dst_move_pos = MovePoint(dst_pos2, ptA2);
						anim(unit0, ����_����_�̴�÷, { di }, dst_pos2, 0, "", 0);
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
						update(unit0, di.dst_move_pos, { di }, ũ��Ƽ��_����, bCri);
						dst_pos0 = di.dst_move_pos;
					}
				}

			}//bTatics
			update(unit0, target, dst_pos, dst_pos0, pk::get_tactics(����_�̴�÷).energy_cost);
		}
		void execute����(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			pk::point dst_pos0 = dst_pos;

			int nTactics = callback202(unit0, dst_pos, target, ����_����);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), ����_����, ũ��Ƽ��_����);
			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, ����_����_��������, bCri);
			}
			else
			{
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, ����_����, dst_pos, 0, bCri ? 1 : 0, false);
				if (!�ݰ��ұ�(di, target))
				{
					int dir = pk::get_direction(unit0.get_pos(), dst_pos);
					pk::point ptA = pk::get_neighbor_pos(dst_pos, dir, 1);
					di.src_move_pos = unit0.get_pos();
					di.dst_move_pos = MovePoint(dst_pos, ptA);
					anim(unit0, ����_����_����, { di }, dst_pos, 0, "", 0);
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
					bool re = update(unit0, di.dst_move_pos, { di }, ũ��Ƽ��_����, bCri);
					pk::point dst_pos2 = di.dst_move_pos;
					dst_pos0 = di.dst_move_pos;
					if (re && ����(unit0))
					{
						sleep();
						pk::point ptA2 = pk::get_neighbor_pos(dst_pos2, dir, 1);
						di.src_pos = unit0.get_pos();
						di.dst_pos = dst_pos2;
						di.src_move_pos = unit0.get_pos();
						di.dst_move_pos = MovePoint(dst_pos2, ptA2);
						anim(unit0, ����_����_����, { di }, dst_pos2, 0, "", 0);
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
						update(unit0, di.dst_move_pos, { di }, ũ��Ƽ��_����, bCri);
						dst_pos0 = di.dst_move_pos;
					}
				}

			}//bTatics
			update(unit0, target, dst_pos, dst_pos0, pk::get_tactics(����_����).energy_cost);
		}
		void execute����(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			int nTactics = callback202(unit0, dst_pos, target, ����_����);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), ����_����, ũ��Ƽ��_���Ÿ�);
			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, ����_����_Ȱ����, bCri);
			}
			else
			{
				pk::tactics@ tactics_t = pk::get_tactics(����_����);
				int  max_range = tactics_t.max_range;
				int  min_range = tactics_t.min_range;
				if (��Ÿ�_��ġ)
				{
					tactics_t.min_range = 1;
					tactics_t.max_range = 5;
				}



				array<pk::damage_info> dis;
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, ����_����, dst_pos, 0, bCri ? 1 : 0, false);
				if (!�ݰ��ұ�(di, target))
				{
					pk::building@ b = pk::get_building(dst_pos);
					bool b���� = false;
					if (b != null && (b.facility == �ü�_���� || b.facility == �ü�_���� || b.facility == �ü�_�ױ�))
					{
						di.troops_damage *= 1.5;
						b���� = true;
					}
					dis.insertLast(di);

					for (int i = 0; i < 6; i++)
					{
						pk::point pt = pk::get_neighbor_pos(dst_pos, i, 1);
						pk::hex_object@ obj = pk::get_hex_object(pt);
						if (obj == null)
							continue;
						if (unit0.has_skill(Ư��_�ý�) && !pk::is_enemy(unit0, obj))
							continue;
						if (!checkHex�뺴(unit0, pt))
							continue;

						pk::damage_info di2;
						di2.src_pos = unit0.get_pos();
						di2.dst_pos = pt;

						callback209(di2, unit0, ����_����, pt, 0, bCri ? 1 : 0, false);
						if (b����) 
						{
							di2.troops_damage = 1;
							di2.hp_damage = 0;
						}
							
						dis.insertLast(di2);
					}
					anim(unit0, ����_����_����, dis, dst_pos, 0, "", 0);
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
					bool re = update(unit0, dst_pos, dis, ũ��Ƽ��_���Ÿ�, bCri);
					if (re && ����(unit0))
					{
						sleep();
						anim(unit0, ����_����_����, dis, dst_pos, 0, "", 0);
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
						update(unit0, dst_pos, dis, ũ��Ƽ��_���Ÿ�, bCri);
					}
				}
				if (��Ÿ�_��ġ)
				{
					tactics_t.min_range = min_range;
					tactics_t.max_range = max_range;
				}
			}
			update(unit0, target, dst_pos, dst_pos, pk::get_tactics(����_����).energy_cost);
		}
		void execute����(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			int nTactics = callback202(unit0, dst_pos, target, ����_����);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), ����_����, ũ��Ƽ��_���Ÿ�);
			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, ����_����_Ȱ����, bCri);
			}
			else
			{
				pk::tactics@ tactics_t = pk::get_tactics(����_����);
				int  max_range = tactics_t.max_range;
				int  min_range = tactics_t.min_range;
				if (��Ÿ�_��ġ)
				{
					tactics_t.min_range = 1;
					tactics_t.max_range = 5;
				}

				array<pk::damage_info> dis;
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, ����_����, dst_pos, 0, bCri ? 1 : 0, false);
				if (!�ݰ��ұ�(di, target))
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
						if (!checkHex�뺴(unit0, pt))
							continue;

						pk::damage_info di2;
						di2.src_pos = unit0.get_pos();
						di2.dst_pos = pt;

						callback209(di2, unit0, ����_����, pt, 0, bCri ? 1 : 0, false);
						dis.insertLast(di2);
					}
					anim(unit0, ����_����_����, dis, dst_pos, 0, "", 0);
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
					bool re = update(unit0, dst_pos, dis, ũ��Ƽ��_���Ÿ�, bCri);
					if (re && ����(unit0))
					{
						sleep();
						anim(unit0, ����_����_����, dis, dst_pos, 0, "", 0);
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
					update(unit0, dst_pos, dis, ũ��Ƽ��_���Ÿ�, bCri);
				}

				if (��Ÿ�_��ġ)
				{
					tactics_t.min_range = min_range;
					tactics_t.max_range = max_range;
				}
			}
			update(unit0, target, dst_pos, dst_pos, pk::get_tactics(����_����).energy_cost);
		}


		void execute�Լ�ȭ��(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			int nTactics = callback202(unit0, dst_pos, target, ����_�Լ�ȭ��);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), ����_�Լ�ȭ��, ũ��Ƽ��_���Ÿ�);

			//bTactics = false;
			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, ����_����_Ȱ����, bCri);
			}
			else
			{
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, ����_�Լ�ȭ��, dst_pos, 0, bCri ? 1 : 0, false);
				if (!�ݰ��ұ�(di, target))
				{
					anim(unit0, ����_����_ȭ��_�Լ�, { di }, dst_pos, 0, "", 0);
					if (bCri)
						cutin(unit0);
					addTroops(target, di);

					pk::unit@ u = getUnit(di.dst_pos);
					if (u != null && !u.has_skill(Ư��_ȣ��))
					{
						if (u.member[0] >= 0 && u.member[0] < ����_�� && pk::rand_bool(�ڵ�����_ȭ��_�λ�Ȯ��))
							injury(pk::get_person(u.member[0]));
						if (u.member[1] >= 0 && u.member[1] < ����_�� && pk::rand_bool(�ڵ�����_ȭ��_�λ�Ȯ��))
							injury(pk::get_person(u.member[1]));
						if (u.member[2] >= 0 && u.member[2] < ����_�� && pk::rand_bool(�ڵ�����_ȭ��_�λ�Ȯ��))
							injury(pk::get_person(u.member[2]));
					}
					bool re = update(unit0, dst_pos, { di }, ũ��Ƽ��_���Ÿ�, bCri);
					re = updateAfter(unit0, target);
					if (re && ����(unit0))
					{
						sleep();
						anim(unit0, ����_����_ȭ��_�Լ�, { di }, dst_pos, 0, "", 0);
						if (bCri)
							cutin(unit0);
						addTroops(target, di);

						@u = getUnit(di.dst_pos);
						if (u != null && !u.has_skill(Ư��_ȣ��))
						{
							if (u.member[0] >= 0 && u.member[0] < ����_�� && pk::rand_bool(�ڵ�����_ȭ��_�λ�Ȯ��))
								injury(pk::get_person(u.member[0]));
							if (u.member[1] >= 0 && u.member[1] < ����_�� && pk::rand_bool(�ڵ�����_ȭ��_�λ�Ȯ��))
								injury(pk::get_person(u.member[1]));
							if (u.member[2] >= 0 && u.member[2] < ����_�� && pk::rand_bool(�ڵ�����_ȭ��_�λ�Ȯ��))
								injury(pk::get_person(u.member[2]));
						}
						update(unit0, dst_pos, { di }, ũ��Ƽ��_���Ÿ�, bCri);
						updateAfter(unit0, target);
					}
				}
			}
			update(unit0, target, dst_pos, dst_pos, pk::get_tactics(����_�Լ�ȭ��).energy_cost);
		}
		void execute�Լ��ݵ�(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			pk::point dst_pos0 = dst_pos;

			int nTactics = callback202(unit0, dst_pos, target, ����_�Լ��ݵ�);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), ����_�Լ��ݵ�, ũ��Ƽ��_����);
			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, ����_����_��������_�Լ�, bCri);
			}
			else
			{
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, ����_�Լ��ݵ�, dst_pos, 0, bCri ? 1 : 0, false);
				if (!�ݰ��ұ�(di, target))
				{
					int dir = pk::get_direction(unit0.get_pos(), dst_pos);
					pk::point ptA = pk::get_neighbor_pos(dst_pos, dir, 1);
					di.src_move_pos = unit0.get_pos();
					di.dst_move_pos = MovePoint(dst_pos, ptA,true);
					anim(unit0, ����_����_�ݵ�_�Լ�, { di }, dst_pos, 0, "", 0);
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
					bool re = update(unit0, di.dst_move_pos, { di }, ũ��Ƽ��_����, bCri);
					pk::point dst_pos2 = di.dst_move_pos;
					dst_pos0 = di.dst_move_pos;
					if (re && ����(unit0))
					{
						sleep();
						pk::point ptA2 = pk::get_neighbor_pos(dst_pos2, dir, 1);
						di.src_pos = unit0.get_pos();
						di.dst_pos = dst_pos2;
						di.src_move_pos = unit0.get_pos();
						di.dst_move_pos = MovePoint(dst_pos2, ptA2,true);
						anim(unit0, ����_����_�ݵ�_�Լ�, { di }, dst_pos2, 0, "", 0);
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
						update(unit0, di.dst_move_pos, { di }, ũ��Ƽ��_����, bCri);
						dst_pos0 = di.dst_move_pos;
					}
				}

			}//bTatics
			update(unit0, target, dst_pos, dst_pos0, pk::get_tactics(����_�Լ��ݵ�).energy_cost);
		}
		void execute�Լ�����(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			int nTactics = callback202(unit0, dst_pos, target, ����_�Լ�����);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), ����_�Լ�����, ũ��Ƽ��_���Ÿ�);
			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, ����_����_Ȱ����, bCri);
			}
			else
			{
				pk::tactics@ tactics_t = pk::get_tactics(����_�Լ�����);
				int  max_range = tactics_t.max_range;
				int  min_range = tactics_t.min_range;
				if (��Ÿ�_��ġ)
				{
					tactics_t.min_range = 1;
					tactics_t.max_range = 5;
				}



				array<pk::damage_info> dis;
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, ����_�Լ�����, dst_pos, 0, bCri ? 1 : 0, false);

				if (!�ݰ��ұ�(di, target))
				{
					pk::building@ b = pk::get_building(dst_pos);
					bool b���� = false;
					if (b != null && (b.facility == �ü�_���� || b.facility == �ü�_���� || b.facility == �ü�_�ױ�))
					{
						if (pk::has_tech(unit0, �ⱳ_����))
						{
							di.troops_damage *= ��������_����_������_����;
							di.hp_damage *= ��������_������_������_����;
							b���� = true;
						}
					}
					dis.insertLast(di);

					if (pk::has_tech(unit0, �ⱳ_����))
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

							callback209(di2, unit0, ����_�Լ�����, pt, 0, bCri ? 1 : 0, false);
							if (b����)
							{
								di2.troops_damage = 1;
								di2.hp_damage = 0;
							}

							dis.insertLast(di2);
						}
					}

					anim(unit0, ����_����_����_�Լ�, dis, dst_pos, 0, "", 0);
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
					bool re = update(unit0, dst_pos, dis, ũ��Ƽ��_���Ÿ�, bCri);
					if (re && ����(unit0))
					{
						sleep();
						anim(unit0, ����_����_����_�Լ�, dis, dst_pos, 0, "", 0);
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
						update(unit0, dst_pos, dis, ũ��Ƽ��_���Ÿ�, bCri);
					}
				}
				if (��Ÿ�_��ġ)
				{
					tactics_t.min_range = min_range;
					tactics_t.max_range = max_range;
				}
			}
			update(unit0, target, dst_pos, dst_pos, pk::get_tactics(����_�Լ�����).energy_cost);
		}

		void execute��������(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			int nTactics = callback202(unit0, dst_pos, target, ����_��������);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), ����_��������, ũ��Ƽ��_���Ÿ�);
			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, ����_����_Ȱ����, bCri);
			}
			else
			{
				pk::tactics@ tactics_t = pk::get_tactics(����_��������);
				int  max_range = tactics_t.max_range;
				int  min_range = tactics_t.min_range;
				if (��Ÿ�_��ġ)
				{
					tactics_t.min_range = 1;
					tactics_t.max_range = 5;
				}



				array<pk::damage_info> dis;
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, ����_��������, dst_pos, 0, bCri ? 1 : 0, false);

				if (!�ݰ��ұ�(di, target))
				{
					pk::building@ b = pk::get_building(dst_pos);
					bool b���� = false;
					if (b != null && (b.facility == �ü�_���� || b.facility == �ü�_���� || b.facility == �ü�_�ױ�))
					{
						if (pk::has_tech(unit0, �ⱳ_����))
						{
							di.troops_damage *= ��������_����_������_����;
							di.hp_damage *= ��������_������_������_����;
							b���� = true;
						}
					}
					dis.insertLast(di);

					if (pk::has_tech(unit0, �ⱳ_����))
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

							callback209(di2, unit0, ����_��������, pt, 0, bCri ? 1 : 0, false);
							if (b����)
							{
								di2.troops_damage = 0;
								di2.hp_damage = 0;
							}

							dis.insertLast(di2);
						}
					}


					anim(unit0, ����_����_����_����, dis, dst_pos, 0, "", 0);
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
					bool re = update(unit0, dst_pos, dis, ũ��Ƽ��_���Ÿ�, bCri);
					if (re && ����(unit0))
					{
						sleep();
						anim(unit0, ����_����_����_����, dis, dst_pos, 0, "", 0);
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
						update(unit0, dst_pos, dis, ũ��Ƽ��_���Ÿ�, bCri);
					}
				}
				if (��Ÿ�_��ġ)
				{
					tactics_t.min_range = min_range;
					tactics_t.max_range = max_range;
				}
			}
			update(unit0, target, dst_pos, dst_pos, pk::get_tactics(����_��������).energy_cost);
		}

		bool �ڵ�����_�⺴_����(pk::unit@ u)
		{
			if (u.energy < pk::get_tactics(����_����).energy_cost)
				return false;
			if (getMax����(u, ����_�⺴) < ����_A)
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

				for (int j = 0; j < ����_��; j++)
				{
					pk::point pt2 = pk::get_neighbor_pos(pt, j, 1);
					pk::unit@ unit = getUnit(pt2);
					if (unit == null || !pk::is_enemy(u, unit))
						continue;
					if (!checkHex�⺴(pt2))
						continue;
					pk::point pt3 = pk::get_neighbor_pos(pt, j, 2);
					if (isOnFire(pt3))
						continue;

					int nTactics = callback202(u, pt2, unit, ����_����);
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

			if (�ܼ�_�α�_ǥ��)
				pk::printf("����:���Ľ��� {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			move(u, maxPt);
			execute����(u, maxUnit.get_pos());
			if (�ܼ�_�α�_ǥ��)
				pk::printf("����:���ĳ� {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));


			return true;
		}
		bool �ڵ�����_�⺴_����(pk::unit@ u)
		{
			if (u.energy < pk::get_tactics(����_����).energy_cost)
				return false;
			if (getMax����(u, ����_�⺴) < ����_B)
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

				for (int j = 0; j < ����_��; j++)
				{
					pk::point pt2 = pk::get_neighbor_pos(pt, j, 1);
					pk::unit@ unit = getUnit(pt2);
					if (unit == null || !pk::is_enemy(u, unit))
						continue;
					if (!checkHex�⺴(pt2))
						continue;

					int nTactics = callback202(u, pt2, unit, ����_����);
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

			if (�ܼ�_�α�_ǥ��)
				pk::printf("����:���ݽ��� {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			move(u, maxPt);
			execute����(u, maxUnit.get_pos());
			if (�ܼ�_�α�_ǥ��)
				pk::printf("����:���ݳ� {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));


			return true;


		}
		bool �ڵ�����_�⺴_����(pk::unit@ u)
		{
			if (u.energy < pk::get_tactics(����_����).energy_cost)
				return false;
			if (getMax����(u, ����_�⺴) < ����_S)
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

				for (int j = 0; j < ����_��; j++)
				{
					pk::point pt2 = pk::get_neighbor_pos(pt, j, 1);
					pk::unit@ unit = getUnit(pt2);
					if (unit == null || !pk::is_enemy(u, unit))
						continue;
					if (!checkHex�⺴(pt2))
						continue;
					pk::point pt3 = pk::get_neighbor_pos(pt, j, 2);
					if (isOnFire(pt3) && isMovable(pt3))
						continue;

					int nTactics = callback202(u, pt2, unit, ����_����);
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

			if (�ܼ�_�α�_ǥ��)
				pk::printf("����:���� ���� {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			move(u, maxPt);
			execute����(u, maxUnit.get_pos());
			if (�ܼ�_�α�_ǥ��)
				pk::printf("����:���� �� {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));


			return true;
		}

		bool �ڵ�����_�⺴_ȭ��(pk::unit@ u)
		{
			if (u.energy < pk::get_tactics(����_ȭ��).energy_cost)
				return false;
			if (!pk::has_tech(u, �ⱳ_�����⺴))
				return false;
			if (u.weapon == ����_���� && getMax����(u, ����_�⺴) < ����_B)
				return false;
			if (u.weapon == ����_�� && getMax����(u, ����_�뺴) < ����_B)
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
					if (!checkHex�뺴(u, pt))
						continue;


					int nTactics = callback202(u, pt, unit, ����_ȭ��);
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

			if (�ܼ�_�α�_ǥ��)
				pk::printf("����:ȭ�ý��� {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			move(u, maxPos);
			executeȭ��(u, maxUnit.get_pos());
			if (�ܼ�_�α�_ǥ��)
				pk::printf("����:ȭ�ó� {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));

			return true;
		}

		bool �ڵ�����_â��_�غ�_Ⱦġ(pk::unit@ u, bool bChang)
		{
			if (u.energy < pk::get_tactics(����_Ⱦġ).energy_cost)
				return false;
			if (bChang)
			{
				if (!pk::has_tech(u, �ⱳ_����â��))
					return false;
			}
			if (u.weapon == ����_�� && getMax����(u, ����_�غ�) < ����_A)
				return false;
			if (u.weapon == ����_â && getMax����(u, ����_â��) < ����_A)
				return false;


			//2���̻�Ǹ� �߻�
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

				for (int i = 0; i < ����_��; i++)
				{
					pk::point pt = pk::get_neighbor_pos(pt0, i, dist);
					pk::unit@ unit = getUnit(pt);
					if (unit == null || !pk::is_enemy(u, unit))
						continue;
					if (bChang && !checkHexâ��(pt))
						continue;
					if (!bChang && !checkHex�غ�(pt))
						continue;

					int acount = 1;
					array<pk::point> arr2 = getȾġpos(pt0, pt);
					pk::unit@ u0 = getUnit(arr2[0]);
					pk::unit@ u1 = getUnit(arr2[1]);
					if (u0 != null && pk::is_enemy(u, u0) && (bChang && checkHexâ��(arr2[0]) || !bChang && checkHex�غ�(arr2[0])))
						acount++;
					if (u1 != null && pk::is_enemy(u, u1) && (bChang && checkHexâ��(arr2[1]) || !bChang && checkHex�غ�(arr2[1])))
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

			if (�ܼ�_�α�_ǥ��)
				pk::printf("����:Ⱦġ���� {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			move(u, maxPT);
			executeȾġ(u, maxUnit.get_pos());
			if (�ܼ�_�α�_ǥ��)
				pk::printf("����:Ⱦġ�� {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			return true;



			return false;
		}

		
		bool �ڵ�����_��ǳ(pk::unit@ u, int rcount)
		{
			if (u.energy < pk::get_tactics(����_��ǳ).energy_cost)
				return false;
			if (getMax����(u, ����_�غ�) < ����_S)
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
					if (unit == null || !pk::is_enemy(u, unit) || !checkHex�غ�(pt))
						continue;

					acount++;
					int nTactics = callback202(u, pt, unit, ����_��ǳ);
					if (unit.has_skill(Ư��_ö��) || unit.has_skill(Ư��_�ұ�) || unit.has_skill(Ư��_�ݰ�))
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
				if (�ܼ�_�α�_ǥ��)
					pk::printf("����:��ǳ���� {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
				move(u, maxPos);
				execute��ǳ(u, maxUnit.get_pos());
				if (�ܼ�_�α�_ǥ��)
					pk::printf("����:��ǳ�� {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
				return true;
			}
			return false;
		}

		bool �ڵ�����_â��_�غ�_����÷(pk::unit@ u, bool bChang)
		{
			if (u.energy < pk::get_tactics(����_����÷).energy_cost)
				return false;
			if (!bChang && pk::has_tech(u, �ⱳ_�����غ�))
				return false;
			if (u.weapon == ����_�� && getMax����(u, ����_�غ�) < ����_A)
				return false;
			if (u.weapon == ����_â && getMax����(u, ����_â��) < ����_A)
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

				for (int i = 0; i < ����_��; i++)
				{
					pk::point pt = pk::get_neighbor_pos(pt0, i, 1);
					pk::unit@ unit = getUnit(pt);
					if (unit == null || !pk::is_enemy(u, unit))
						continue;
					if (bChang && !checkHexâ��(pt))
						continue;
					if (!bChang && !checkHex�غ�(pt))
						continue;

					if (u.attr.stat[�δ�ɷ�_����] > unit.attr.stat[�δ�ɷ�_����] && unit.attr.stat[�δ�ɷ�_����] > maxAttack)
					{
						maxPos = pt0;
						maxAttack = unit.attr.stat[�δ�ɷ�_����];
						@maxUnit = unit;
					}
				}
			}

			if (maxUnit == null)
				return false;

			if (�ܼ�_�α�_ǥ��)
				pk::printf("����:����÷���� {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			move(u, maxPos);
			execute����÷(u, maxUnit.get_pos());
			if (�ܼ�_�α�_ǥ��)
				pk::printf("����:����÷�� {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));

			return true;
		}
		bool �ڵ�����_â��_�̴�÷(pk::unit@ u)
		{
			if (u.energy < pk::get_tactics(����_�̴�÷).energy_cost)
				return false;
			if (getMax����(u, ����_â��) < ����_S)
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

				for (int j = 0; j < ����_��; j++)
				{
					pk::point pt2 = pk::get_neighbor_pos(pt, j, 1);
					pk::unit@ unit = getUnit(pt2);
					if (unit == null || !pk::is_enemy(u, unit))
						continue;
					if (!checkHexâ��(pt2))
						continue;

					int nTactics = callback202(u, pt2, unit, ����_�̴�÷);
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

			if (�ܼ�_�α�_ǥ��)
				pk::printf("����:�̴�÷ ���� {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			move(u, maxPt);
			execute�̴�÷(u, maxUnit.get_pos());
			if (�ܼ�_�α�_ǥ��)
				pk::printf("����:�̴�÷ �� {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));

			return true;
		}

		bool �ڵ�����_â��_����(pk::unit@ u)
		{
			if (u.energy < pk::get_tactics(����_����).energy_cost)
				return false;
			if (getMax����(u, ����_â��) < ����_B)
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

				for (int j = 0; j < ����_��; j++)
				{
					pk::point pt2 = pk::get_neighbor_pos(pt, j, 1);
					pk::unit@ unit = getUnit(pt2);
					if (unit == null || !pk::is_enemy(u, unit))
						continue;
					if (!checkHexâ��(pt2))
						continue;

					int nTactics = callback202(u, pt2, unit, ����_����);
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

			if (�ܼ�_�α�_ǥ��)
				pk::printf("����:���� ���� {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			move(u, maxPt);
			execute����(u, maxUnit.get_pos());
			if (�ܼ�_�α�_ǥ��)
				pk::printf("����:���� �� {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));

			return true;
		}

		bool �ڵ�����_�غ�_����(pk::unit@ u)
		{
			if (u.energy < pk::get_tactics(����_����).energy_cost)
				return false;
			if (getMax����(u, ����_�غ�) < ����_B)
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

				for (int j = 0; j < ����_��; j++)
				{
					pk::point pt2 = pk::get_neighbor_pos(pt, j, 1);
					pk::unit@ unit = getUnit(pt2);
					if (unit == null || !pk::is_enemy(u, unit))
						continue;
					if (!checkHex�غ�(pt2))
						continue;
					pk::point pt3 = get����pos(pt, pt2);
					if (isOnFire(pt3))
						continue;

					int nTactics = callback202(u, pt2, unit, ����_����);
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

			if (�ܼ�_�α�_ǥ��)
				pk::printf("����:�������� {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			move(u, maxPt);
			execute����(u, maxUnit.get_pos());
			if (�ܼ�_�α�_ǥ��)
				pk::printf("����:������ {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));

			return true;
		}

		bool �ڵ�����_����(pk::unit@ u)
		{
			if (u.energy < pk::get_tactics(����_����).energy_cost)
				return false;
			if (getMax����(u, ����_�뺴) < ����_S)
				return false;


			//3���̻�Ǹ� �߻�
			int dist = getMaxAttackDistance(u);
			//int dist = 2;
			int minDist = 2;
			int curDist = 2;
			bool b�ý� = u.has_skill(Ư��_�ý�);

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
					if (!checkHex�뺴(u, pt))
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
						if (!checkHex�뺴(u, pt2))
							continue;

						if (!b�ý� && ((unit2 != null && !pk::is_enemy(u, unit2)) || (b2 != null && !pk::is_enemy(u, b2))))
						{
							bMine = true;
							break;
						}
						if ((unit2 != null && !pk::is_enemy(u, unit2)) || (b2 != null && !pk::is_enemy(u, b2)))
							continue;
						acount++;
					}

					if (b != null && ((b.facility == �ü�_����) || b.facility == �ü�_���� || b.facility == �ü�_�ױ�))
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

			if (�ܼ�_�α�_ǥ��)
				pk::printf("����:������� {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			move(u, maxPT);
			execute����(u, maxUnit != null ? maxUnit.get_pos() : maxBuilding.get_pos());
			if (�ܼ�_�α�_ǥ��)
				pk::printf("����:���糡 {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			return true;
		}
		bool �ڵ�����_����(pk::unit@ u)
		{
			if (u.energy < pk::get_tactics(����_����).energy_cost)
				return false;
			if (getMax����(u, ����_�뺴) < ����_A)
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
					if (!checkHex�뺴(u, pt))
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
						if (!checkHex�뺴(u, pt2))
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

			if (�ܼ�_�α�_ǥ��)
				pk::printf("����:���ý��� {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			move(u, maxPT);
			execute����(u, maxUnit != null ? maxUnit.get_pos() : maxBuilding.get_pos());
			if (�ܼ�_�α�_ǥ��)
				pk::printf("����:���ó� {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			return true;

		}

		bool �ڵ�����_�Լ�ȭ��(pk::unit@ u)
		{
			if (u.energy < pk::get_tactics(����_�Լ�ȭ��).energy_cost)
				return false;
			if (getMax����(u, ����_����) < ����_B)
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

			if (�ܼ�_�α�_ǥ��)
				pk::printf("����:�Լ�ȭ�ý��� {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			move(u, maxPT);
			execute�Լ�ȭ��(u, maxUnit != null ? maxUnit.get_pos() : maxBuilding.get_pos());
			if (�ܼ�_�α�_ǥ��)
				pk::printf("����:�Լ�ȭ�ó� {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			return true;

		}
		bool �ڵ�����_�Լ��ݵ�(pk::unit@ u)
		{
			if (u.energy < pk::get_tactics(����_�Լ��ݵ�).energy_cost)
				return false;
			if (getMax����(u, ����_����) < ����_A)
				return false;
			if (u.weapon != ����_���� && u.weapon != ����_����)
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

				for (int j = 0; j < ����_��; j++)
				{
					pk::point pt2 = pk::get_neighbor_pos(pt, j, 1);
					pk::unit@ unit = getUnit(pt2);
					if (unit == null || !pk::is_enemy(u, unit))
						continue;
					int nTactics = callback202(u, pt2, unit, ����_�Լ��ݵ�);
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

			if (�ܼ�_�α�_ǥ��)
				pk::printf("����:�Լ��ݵ� ���� {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			move(u, maxPt);
			execute�Լ��ݵ�(u, maxUnit.get_pos());
			if (�ܼ�_�α�_ǥ��)
				pk::printf("����:�Լ��ݵ� �� {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));

			return true;
		}
		bool �ڵ�����_�Լ�����(pk::unit@ u)
		{
			if (u.energy < pk::get_tactics(����_�Լ�����).energy_cost)
				return false;
			if (getMax����(u, ����_����) < ����_S)
				return false;
			if (u.weapon != ����_����)
				return false;


			//3���̻�Ǹ� �߻�
			int dist = getMaxAttackDistance(u,true,true);
			if (u.has_skill(Ư��_����))
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
					if (b != null && ((b.facility == �ü�_����) || b.facility == �ü�_���� || b.facility == �ü�_�ױ�))
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

			if (�ܼ�_�α�_ǥ��)
				pk::printf("����:�Լ����� {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			move(u, maxPT);
			execute�Լ�����(u, maxUnit != null ? maxUnit.get_pos() : maxBuilding.get_pos());
			if (�ܼ�_�α�_ǥ��)
				pk::printf("����:�Լ������� {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			return true;
		}

		bool �ڵ�����_��������(pk::unit@ u)
		{
			if (u.energy < pk::get_tactics(����_��������).energy_cost)
				return false;

			//3���̻�Ǹ� �߻�
			int dist = getMaxAttackDistance(u,true,true);
			if (u.has_skill(Ư��_����))
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
					if (!checkHex����(u, pt))
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
						if (!checkHex����(u, pt2))
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

			if (�ܼ�_�α�_ǥ��)
				pk::printf("����:������������ {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			move(u, maxPT);
			execute��������(u, maxUnit != null ? maxUnit.get_pos() : maxBuilding.get_pos());
			if (�ܼ�_�α�_ǥ��)
				pk::printf("����:���������� {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			return true;
		}

		bool �ڵ�����Handler_�غ�(pk::unit@ u)
		{
			if (�ڵ�����_��ǳ(u, 3))
				return true;
			if (�ڵ�����_��ǳ(u, 2))
				return true;
			if (�ڵ�����_â��_�غ�_Ⱦġ(u, false))
				return true;
			if (�ڵ�����_����������� && pk::rand_bool(�ڵ�����_����÷_Ȯ��) && �ڵ�����_â��_�غ�_����÷(u, false))
				return true;
			if (�ڵ�����_�غ�_����(u))
				return true;
			return false;
		}
		bool �ڵ�����Handler_â��(pk::unit@ u)
		{
			if (�ڵ�����_����������� && �ڵ�����_â��_�غ�_Ⱦġ(u, true))
				return true;
			if (pk::rand_bool(�ڵ�����_����÷_Ȯ��) && �ڵ�����_â��_�غ�_����÷(u, true))
				return true;
			if (pk::rand_bool(�ڵ�����_�̴�÷_Ȯ��) && �ڵ�����_â��_�̴�÷(u))
				return true;
			return �ڵ�����_â��_����(u);
		}
		bool �ڵ�����Handler_�뺴(pk::unit@ u)
		{
			if (�ڵ�����_����(u))
				return true;
			if (�ڵ�����_����(u))
				return true;
			if (�ڵ�����_�⺴_ȭ��(u))
				return true;
			return false;
		}
		bool �ڵ�����Handler_�⺴(pk::unit@ u)
		{
			if (pk::rand_bool(�ڵ�����_����_Ȯ��) && �ڵ�����_�⺴_����(u))
				return true;
			if (pk::rand_bool(�ڵ�����_����_Ȯ��) && �ڵ�����_�⺴_����(u))
				return true;
			if (pk::rand_bool(�ڵ�����_����_Ȯ��) && �ڵ�����_�⺴_����(u))
				return true;
			if (�ڵ�����_����������� && �ڵ�����_�⺴_ȭ��(u))
				return true;
			return false;
		}
		bool �ڵ�����Handler_����(pk::unit@ u)
		{
			if (�ڵ�����_�Լ�����(u))
				return true;
			if (u.weapon == ����_���� || u.weapon == ����_����)
			{
				if (pk::rand_bool(�ڵ�����_�Լ�_ȭ��) && �ڵ�����_�Լ�ȭ��(u))
					return true;
			}
			else 
			{
				return �ڵ�����_�Լ�ȭ��(u);
			}
			return �ڵ�����_�Լ��ݵ�(u);
		}
		bool �ڵ�����Handler_����(pk::unit@ u)
		{
			return �ڵ�����_��������(u);
		}

		bool �ڵ�����Handler(pk::unit@ u)
		{
			//pk::printf("�ڵ�:{}\n", getNameLeader(u));
			if (u.status != �δ����_��� || u.action_done)
				return false;
			if (u.order == �δ��ӹ�_����) 
			{
				pk::building@ b = pk::is_valid_pos(u.target_pos) ? pk::get_building(u.target_pos) : null;
				if (b != null && (b.facility == �ü�_���� || b.facility == �ü�_����2�� || b.facility == �ü�_����3��))
				{
					pk::printf("{},�����н�!!!!!!!!!!!!!!!!!\n", getNameLeader(u));
					return false;
				}
			}
			if (!pk::rand_bool(�ڵ�����_Ȯ��))
				return false;

			bool b = false;
			switch (u.weapon)
			{
			case ����_â: b=�ڵ�����Handler_â��(u); break;
			case ����_��: b=�ڵ�����Handler_�غ�(u); break;
			case ����_��: b=�ڵ�����Handler_�뺴(u); break;
			case ����_����: b=�ڵ�����Handler_�⺴(u); break;
			case ����_�ְ�: case ����_����: case ����_����:
				b = �ڵ�����Handler_����(u);
				break;
			case ����_����:
				b = �ڵ�����Handler_����(u);
			default:
				break;
			}
			return b;
		}

		////////////////////////////////////////////////////////////////////////////////////

		int get�ϱ��乫��Attacker(pk::unit@ u)
		{
			int max���� = -1;
			int max���� = -1;
			for (int i = 0; i < 3; i++)
			{
				pk::person@ p = pk::get_person(u.member[i]);
				if (p == null)
					continue;

				if (p.max_stat[����ɷ�_����] > max����)
				{
					max���� = p.max_stat[����ɷ�_����];
					max���� = p.get_id();
				}
			}
			return max����;
		}
		int get�ϱ��乫��Target(pk::unit@ u)
		{
			int max���� = -1;
			int min���� = 1000;
			for (int i = 0; i < 3; i++)
			{
				pk::person@ p = pk::get_person(u.member[i]);
				if (p == null)
					continue;

				if (p.max_stat[����ɷ�_����] > max����)
				{
					max���� = p.max_stat[����ɷ�_����];
				}
				if (p.max_stat[����ɷ�_����] < min����)
				{
					min���� = p.max_stat[����ɷ�_����];
				}
			}

			int sum = 0;
			for (int i = 0; i < 3; i++)
			{
				pk::person@ p = pk::get_person(u.member[i]);
				if (p == null)
					continue;

				sum += (p.max_stat[����ɷ�_����] - (min���� * 0.5));
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

				int ���� = (p.max_stat[����ɷ�_����] - (min���� * 0.5));
				if (i == 0)
					���� += 20;

				int ����2 = ���� / float(sum) * 100 + pos;
				pos += (���� / float(sum) * 100);
				arr.insertLast(����2);
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

		void scene_�ϱ���()
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
				return pk::encode(pk::format("�̰��� {}��", str));
			case 1:
				return pk::encode(pk::format("{} ���� �����ָ�", str));
			case 2:
				return pk::encode(pk::format("���� ��� {} ������", str));
			case 3:
				return pk::encode(pk::format("{} ���� �¼��� ����", str));
			default:
				break;
			}
			return "";
		}

		array<pk::point> getȾġpos(pk::point spos, pk::point dpos)
		{
			array<pk::point> pts;
			int dir = pk::get_direction(spos, dpos);
			switch (dir)
			{
			case ����_��:
				pts.insertLast(pk::get_neighbor_pos(spos, ����_����, 1));
				pts.insertLast(pk::get_neighbor_pos(spos, ����_����, 1));
				break;
			case ����_����:
				pts.insertLast(pk::get_neighbor_pos(spos, ����_�ϵ�, 1));
				pts.insertLast(pk::get_neighbor_pos(spos, ����_��, 1));
				break;
			case ����_�ϵ�:
				pts.insertLast(pk::get_neighbor_pos(spos, ����_��, 1));
				pts.insertLast(pk::get_neighbor_pos(spos, ����_����, 1));
				break;
			case ����_��:
				pts.insertLast(pk::get_neighbor_pos(spos, ����_�ϼ�, 1));
				pts.insertLast(pk::get_neighbor_pos(spos, ����_�ϵ�, 1));
				break;
			case ����_�ϼ�:
				pts.insertLast(pk::get_neighbor_pos(spos, ����_����, 1));
				pts.insertLast(pk::get_neighbor_pos(spos, ����_��, 1));
				break;
			case ����_����:
				pts.insertLast(pk::get_neighbor_pos(spos, ����_�ϼ�, 1));
				pts.insertLast(pk::get_neighbor_pos(spos, ����_��, 1));
				break;
			default:
				break;
			}
			return pts;
		}
		pk::point get����pos(pk::point src, pk::point dst)
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
				return pk::is_enabled_terrain(h) && (h==����_�� || h==����_�ٴ�);
			}
			else
			{
				bool b = pk::get_hex_object(pt) != null || h == ����_�� || h == ����_�ٴ� || h == ����_���� || h == ����_��
					|| h == ����_���� || h == ����_�ױ� || h == ����_�� || h == ����_���� || !pk::is_enabled_terrain(h);
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
			int max = pk::max(u.attr.stat[�δ�ɷ�_���], u.attr.stat[�δ�ɷ�_����]);
			int time = pk::max((1 - (max - 50) / 40.0), 0.0) * 2 + 2;
			return time;
		}
		int getMaxAttackDistance(pk::unit@ u, bool bTactics = true,bool b��������=false)
		{
			pk::tactics@ tactics_t_ȭ�� = pk::get_tactics(����_ȭ��);

			pk::force@ f = pk::get_force(u.get_force_id());
			switch (u.weapon)
			{
			case ����_����:
				if (pk::has_tech(f, �ⱳ_���) || u.has_skill(Ư��_�鸶))
				{
					return bTactics ? tactics_t_ȭ��.max_range : 2;
				}

				return  1;
			case ����_â:
			case ����_��:
				return  1;
			case ����_��:

				return tactics_t_ȭ��.max_range;
				//return pk::has_tech(f, �ⱳ_����) ? 3 : 2;
			case ����_�ְ�:case ����_����:case ����_����:
				if(b��������)
					return pk::get_tactics(����_�Լ�����).max_range;
				else
					return pk::get_tactics(����_�Լ�ȭ��).max_range;
			case ����_����:
				return pk::get_tactics(����_��������).max_range;
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
				if (u.status != �δ����_���)
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
				case 0:str = "�̰͵� �޾ƶ�"; break;
				case 1:str = "�̰� ���"; break;
				case 2:str = "���� ������ �ʾҴ�"; break;
				}
				anim(u, dist > 1 ? 1 : 0, { di }, dst_pos, 0, pk::encode(str), 0);

				string str2 = "";
				switch (pk::rand(3))
				{
				case 0:str = pk::format("���� {} ��", pk::decode(pk::get_name(pk::get_person(u.leader)))); break;
				case 1:str = "���� ����"; break;
				case 2:str = "�̰���~"; break;
				}
				pk::say(str2, pk::get_person(attacker.leader), attacker);

				addTroops(targetu, di);

				updateAfter(u, target);


			}
		}
		void attack(pk::unit@ attacker, pk::hex_object@ target, pk::point dst_pos, int type, bool bCri)
		{
			bool bCri2 = type == ����_����_Ȱ���� ? ũ��Ƽ��_���Ÿ� : ũ��Ƽ��_����;
			pk::damage_info di;
			di.src_pos = attacker.get_pos();
			di.dst_pos = dst_pos;
			callback209(di, attacker, 0, dst_pos, 0, bCri ? 1 : 0, false);
			anim(attacker, type, { di }, dst_pos, 0, pk::encode("�޾ƶ�!"), 0);

			pk::unit@ targetU = getUnit(dst_pos);

			if (!�ݰ��ұ�(di, target) && !ȭ�����_ū����(attacker, targetU, type == ����_����_��������))
			{
				addTroops(target, di);
				updateAfter(attacker, target);
				update(attacker, dst_pos, { di }, bCri2, false);

				int aa = int(pk::core::skill_constant(attacker, Ư��_�޽�));
				if (targetU != null && (!attacker.has_skill(Ư��_�޽�) || !pk::rand_bool(aa)))
				{
					pk::damage_info di2;
					di2.src_pos = dst_pos;
					di2.dst_pos = attacker.get_pos();
					callback209(di2, attacker, 0, dst_pos, 0, bCri ? 1 : 0, false);
					anim(targetU, type, { di2 }, attacker.get_pos(), 0, pk::encode("�ݰ��̴�!"), 0);
					if (!�ݰ��ұ�(di2, attacker) && !ȭ�����_ū����(targetU, attacker, type == ����_����_��������))
					{
						addTroops(attacker, di2);
						updateAfter(targetU, attacker);
						update(targetU, attacker.get_pos(), { di2 }, bCri2, true);
					}
				}
			}
			if (����(attacker))
			{
				sleep();
				if (!�ݰ��ұ�(di, target) && !ȭ�����_ū����(attacker, targetU, type == ����_����_��������))
				{
					addTroops(target, di);
					updateAfter(attacker, target);
					update(attacker, dst_pos, { di }, bCri2, false);

					int aa = int(pk::core::skill_constant(attacker, Ư��_�޽�));
					if (targetU != null && (!attacker.has_skill(Ư��_�޽�) || !pk::rand_bool(aa)))
					{
						pk::damage_info di2;
						di2.src_pos = dst_pos;
						di2.dst_pos = attacker.get_pos();
						callback209(di2, attacker, 0, dst_pos, 0, bCri ? 1 : 0, false);
						anim(targetU, type, { di2 }, attacker.get_pos(), 0, pk::encode("�ݰ��̴�!"), 0);
						if (!�ݰ��ұ�(di2, attacker) && !ȭ�����_ū����(targetU, attacker, type == ����_����_��������))
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
			bool bCri2 = type == ����_����_Ȱ���� ? ũ��Ƽ��_���Ÿ� : ũ��Ƽ��_����;
			int r = pk::rand(100);
			if (r <= �������н�_�Ϲݰ���_Ȯ��)
			{
				pk::damage_info di;
				di.src_pos = attacker.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, attacker, 0, dst_pos, 0, bCri ? 1 : 0, false);
				anim(attacker, type, { di }, dst_pos, 0, pk::encode("ĩ �̰͹ۿ�.."), 0);
				if (!�ݰ��ұ�(di, target))
				{
					addTroops(target, di);
					updateAfter(attacker, target);
					update(attacker, dst_pos, { di }, bCri2, false);
					if (����(attacker))
					{
						sleep();
						anim(attacker, type, { di }, dst_pos, 0, pk::encode("ĩ �̰͹ۿ�.."), 0);
						addTroops(target, di);
						updateAfter(attacker, target);
						update(attacker, dst_pos, { di }, bCri2, false);
					}
				}

			}
			else if (r > �������н�_�Ϲݰ���_Ȯ�� and r < �������н�_�Ϲݰ���_Ȯ�� + �������н�_�Ϲݰ���_��������_Ȯ��)
			{
				pk::damage_info di;
				di.src_pos = attacker.get_pos();
				di.dst_pos = dst_pos;
				di.troops_damage = 0;
				//prev_callback_202��������(di, attacker, type, dst_pos, 0, bCri ? 1 : 0, false);

				anim(attacker, type, { di }, dst_pos, 0, pk::encode("������ �ʴ°�.."), 0);
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

				anim(target, type, { di }, attacker.get_pos(), 1, pk::encode("�ݰ��̴�"), 0);
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
				pk::kill(targetU, attacker, dist == 1, attacker.weapon == ����_��);

				//if (dist == 1)
				//{
				//	if (gold * 0.5 > 0)
				//		pk::add_gold(attacker, gold * 0.5, true);
				//	if (food * 0.5 > 0)
				//		pk::add_food(attacker, food * 0.25, true);
				//}

				//pk::printf("kill end\n");
				if (attacker.has_skill(Ư��_�Ӿ�))
					pk::add_energy(attacker, int(pk::core::skill_constant(attacker, Ư��_�Ӿ�)), true);

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

		void update����(pk::unit@ attacker, pk::hex_object@ target, pk::point dest0)
		{
			pk::unit@ u = target != null ? getUnit(target.get_pos()) : null;
			if (u == null || !attacker.has_skill(Ư��_����) || u.has_skill(Ư��_ȣ��))
				return;
			if (target.get_pos().x == dest0.x && target.get_pos().y == dest0.y)
				return;

			int maxValue = int(pk::core::skill_constant(attacker, Ư��_����));
			if (u.member[0] >= 0 && u.member[0] < ����_�� && pk::rand_bool(maxValue))
				injury(pk::get_person(u.member[0]));
			if (u.member[1] >= 0 && u.member[1] < ����_�� && pk::rand_bool(maxValue))
				injury(pk::get_person(u.member[1]));
			if (u.member[2] >= 0 && u.member[2] < ����_�� && pk::rand_bool(maxValue))
				injury(pk::get_person(u.member[2]));
		}
		void injury(pk::person@ p)
		{
			if (pk::has_skill(p, Ư��_����))
				return;
			string strType = "";
			switch (p.shoubyou)
			{
			case ��_�ǰ�:p.shoubyou = ��_����; strType = "����"; break;
			case ��_����:p.shoubyou = ��_����; strType = "����"; break;
			case ��_����:p.shoubyou = ��_���; strType = "���"; break;

			default:
				break;
			}
			p.update();

			switch (pk::rand(3))
			{
			case 0: pk::say(pk::encode("����.."), p, getUnit(p.get_pos())); break;
			case 1: pk::say(pk::encode("���⼱ �λ���.."), p, getUnit(p.get_pos())); break;
			case 2: pk::say(pk::encode("�ƾ�..�̷���"), p, getUnit(p.get_pos())); break;
			default:
				break;
			}

			pk::force@ force = pk::get_force(p.get_force_id());
			pk::person@ kunshu = force != null ? pk::get_person(force.kunshu) : null;
			if (kunshu != null)
			{
				string str = pk::format("\x1b[2x{}\x1b[0x�� \x1b[2x{}\x1b[0x,\x1b[29x{}\x1b[0x ����", getName(kunshu), getName(p), strType);
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
			pk::set_status(u, u2, �δ����_ȥ��, getChaosTime(u), true);
		}
		bool update(pk::unit@ u, pk::point dst_pos, array<pk::damage_info>@ dis, bool bRanged, bool bCri, bool success = true, bool bCounter = false)
		{
			bool b���� = u.has_skill(Ư��_����);

			pk::unit@ attacker = u;
			pk::add_stat_exp(attacker, ����ɷ�_����, (success ? 4 : 1) * (b���� ? 2 : 1));
			pk::add_kouseki(attacker, success ? 100 : 10);

			int type = -1;
			switch (attacker.weapon)
			{
			case ����_â:type = ����_â��; break;
			case ����_��:type = ����_�뺴; break;
			case ����_��:type = ����_�غ�; break;
			case ����_����:type = ����_�⺴; break;
			default:
				break;
			}
			if (type != -1)
			{

				if (attacker.leader >= 0 && attacker.leader < ����_��)
				{
					pk::person@ p0 = pk::get_person(attacker.leader);
					pk::add_heishu_exp(p0, type, (success ? 4 : 1) * (b���� ? 2 : 1));
				}
				if (attacker.member[1] >= 0 && attacker.member[1] < ����_��)
				{
					pk::person@ p0 = pk::get_person(attacker.member[1]);
					pk::add_heishu_exp(p0, type, (success ? 4 : 1) * (b���� ? 2 : 1));
				}
				if (attacker.member[2] >= 0 && attacker.member[2] < ����_��)
				{
					pk::person@ p0 = pk::get_person(attacker.member[2]);
					pk::add_heishu_exp(p0, type, (success ? 4 : 1) * (b���� ? 2 : 1));
				}
			}
			pk::unit@ targetU = getUnit(dst_pos);
			if (targetU != null)
			{
				pk::add_stat_exp(targetU, ����ɷ�_���, b���� ? 2 : 1);

				int type2 = -1;
				switch (targetU.weapon)
				{
				case ����_â:type2 = ����_â��; break;
				case ����_��:type2 = ����_�뺴; break;
				case ����_��:type2 = ����_�غ�; break;
				case ����_����:type2 = ����_�⺴; break;
				case ����_����:case ����_����:case ����_����:case ����_���:type2 = ����_����; break;
				case ����_�ְ�:case ����_����:case ����_����:type2 = ����_����; break;
				default:
					break;
				}
				if (type2 != -1)
				{
					if (targetU.leader >= 0 && targetU.leader < ����_��)
					{
						pk::person@ p0 = pk::get_person(targetU.leader);
						pk::add_heishu_exp(p0, type, b���� ? 2 : 1);
					}
					if (targetU.member[1] >= 0 && targetU.member[1] < ����_��)
					{
						pk::person@ p0 = pk::get_person(targetU.member[1]);
						pk::add_heishu_exp(p0, type, b���� ? 2 : 1);
					}
					if (targetU.member[2] >= 0 && targetU.member[2] < ����_��)
					{
						pk::person@ p0 = pk::get_person(targetU.member[2]);
						pk::add_heishu_exp(p0, type, b���� ? 2 : 1);
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
					if (u.has_skill(Ư��_����))
						pk::add_energy(dstU, -int(pk::core::skill_constant(u, Ư��_����)), true);
					if (u.has_skill(Ư��_��ǳ))
						pk::add_energy(dstU, -int(pk::core::skill_constant(u, Ư��_��ǳ)), true);

					sum += di.troops_damage;
				}
				if (!bRanged && u.has_skill(Ư��_�ɰ�))
					pk::add_troops(u, float(pk::core::skill_constant(u, Ư��_�ɰ�)) * sum, true);
			}


			@targetU = getUnit(dst_pos);
			if (success && targetU != null && u.weapon == ����_���� && !bRanged && pk::get_scenario().battle_death != ����_����)
			{
				pk::person@ l = pk::get_person(u.leader);
				bool bDie = false;
				if (targetU.leader >= 0 && targetU.leader < ����_��)
				{
					pk::person@ p0 = pk::get_person(targetU.leader);
					int n = prev_callback_203�⺴�������(l, p0, (dis.length > 0 ? dis[0].tactics : ����_����), bCri);
					if (n > 0 && pk::rand_bool(n))
					{
						pk::message_box(pk::encode("���ϴ�.."), p0);
						pk::kill(p0, l, targetU, null, 0);
						bDie = true;
					}
				}
				if (!bDie && targetU.member[1] >= 0 && targetU.member[1] < ����_��)
				{
					pk::person@ p0 = pk::get_person(targetU.member[1]);
					int n = prev_callback_203�⺴�������(l, p0, (dis.length > 0 ? dis[0].tactics : ����_����), bCri);
					if (n > 0 && pk::rand_bool(n))
					{
						pk::kill(p0, l, targetU, null, 0);
						pk::message_box(pk::encode("���ϴ�.."), p0);
						bDie = true;
					}
				}
				if (!bDie && targetU.member[2] >= 0 && targetU.member[2] < ����_��)
				{
					pk::person@ p0 = pk::get_person(targetU.member[2]);
					int n = prev_callback_203�⺴�������(l, p0, (dis.length > 0 ? dis[0].tactics : ����_����), bCri);
					if (n > 0 && pk::rand_bool(n))
					{
						pk::kill(p0, l, targetU, null, 0);
						pk::message_box(pk::encode("���ϴ�.."), p0);
						bDie = true;
					}
				}
			}

			@targetU = getUnit(dst_pos);
			if (success && targetU != null && ����_�ϱ���_Ȯ�� > 0 && pk::rand_bool(����_�ϱ���_Ȯ��))
			{
				//@_scene_attackerUnit = attacker;
				//@_scene_targetUnit = targetU;
				//@_scene_attacker = pk::get_person(attacker.leader);
				//@_scene_target = pk::get_person(targetU.leader);
				//pk::wait(3000);
				//pk::message_box(pk::encode("������ ã�Ҵ�"), _scene_attacker);
				//pk::message_box(pk::encode("���� ��ȸ�ϰ� �ɰ��̴�"), _scene_target);
				//pk::scene(pk::scene_t(scene_�ϱ���));

				int attacker���� = get�ϱ��乫��Attacker(attacker);
				if (attacker���� == -1)
					attacker���� = attacker.leader;

				int target���� = get�ϱ��乫��Target(targetU);
				if (target���� == -1)
					target���� = targetU.leader;


				_scene_attackers.add(pk::get_person(attacker����));
				_scene_targets.add(pk::get_person(target����));
				_scene_attackerUnits.add(attacker);
				_scene_targetUnits.add(targetU);
			}


			return getUnit(dst_pos) != null;
		}


		void update(pk::unit@ u, pk::hex_object@ target, pk::point dst_pos, pk::point dst_pos2, int energy)
		{
			updateAssist(u, target, dst_pos2);
			update����(u, target, dst_pos);
			pk::add_energy(u, -energy, true);
			pk::set_action_done(u, true);
			pk::action_done(u, u.get_pos());
			u.action_done = true;
			u.update();
		}
		bool �ݰ��ұ�(pk::damage_info di, pk::hex_object@ target)
		{
			pk::unit@ u = target != null ? getUnit(target.get_pos()) : null;
			if (u == null)
				return false;
			if (u.status != �δ����_���)
				return false;

			if (u.has_skill(Ư��_�ݰ�))
			{
				int val = int(pk::core::skill_constant(u, Ư��_�ݰ�, 0));
				int ratio = int(pk::core::skill_constant(u, Ư��_�ݰ�, 1));
				if (di.troops_damage < val && pk::rand_bool(ratio))
				{
					pk::create_effect(82, target.get_pos());
					pk::play_se(7);
					return true;
				}
			}
			if (u.has_skill(Ư��_�ұ�))
			{
				int val = int(pk::core::skill_constant(u, Ư��_�ұ�, 0));
				int ratio = int(pk::core::skill_constant(u, Ư��_�ұ�, 1));
				if (u.troops < val && pk::rand_bool(ratio))
				{
					pk::create_effect(82, target.get_pos());
					pk::play_se(7);
					return true;
				}
			}
			return false;
		}
		bool ȭ�����_ū����(pk::unit@ attacker, pk::unit@ target, bool b����)
		{
			if (target == null || target.weapon != ����_��)
				return false;
			if (target.status != �δ����_���)
				return false;

			if (b���� && pk::has_tech(target, �ⱳ_ū����) && pk::rand_bool(30))
				return true;
			if (!b���� && pk::has_tech(target, �ⱳ_ȭ�����) && pk::rand_bool(30))
				return true;

			return false;
		}

		bool ����(pk::unit@ u)
		{
			int val = int(pk::core::skill_constant(u, Ư��_����));
			bool b = bool(pk::core["��Ư�⿬��"]);
			return b && u.has_skill(Ư��_����) && pk::rand_bool(val);
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

		bool checkHex�뺴(pk::unit@ u, pk::point pt)
		{
			pk::tactics@ t = pk::get_tactics(����_ȭ��);
			if (t.terrain[pk::get_hex(pt).terrain])
				return true;
			if (!u.has_skill(Ư��_���) && pk::get_hex(pt).terrain == ����_��)
				return false;
			int h = pk::get_hex(pt).terrain;
			//if (h == ����_�� || h == ����_�ٴ� || h == ����_��)
			//	return false;
			return true;
		}
		bool checkHex����(pk::unit@ u, pk::point pt)
		{
			pk::tactics@ t = pk::get_tactics(����_��������);
			return (t.terrain[pk::get_hex(pt).terrain]);
		}

		bool checkHexâ��(pk::point pt)
		{
			int h = pk::get_hex(pt).terrain;
			if (h == ����_�� || h == ����_�ٴ� || h == ����_�� || h == ����_��)
				return false;
			return true;
		}
		bool checkHex�غ�(pk::point pt)
		{
			int h = pk::get_hex(pt).terrain;
			if (h == ����_�� || h == ����_�ٴ� || h == ����_��)
				return false;
			return true;
		}
		bool checkHex�⺴(pk::point pt)
		{
			pk::tactics@ tactics_t_���� = pk::get_tactics(����_����);
			return tactics_t_����.terrain[pk::get_hex(pt).terrain];

			switch (pk::get_hex(pt).terrain)
			{
			case ����_Ȳ����:
			case ����_���:
			case ����_�ʿ�:
			case ����_��:
			case ����_��:
			case ����_����:
			case ����_�ٸ�:
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
			pk::wait(����_������);
		}

		int getMax����(pk::unit@ u, int type)
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

