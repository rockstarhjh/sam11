/*
@만든이: 크래픽스
@Update: 2023.9.4,최초배포
@Update: 2024.5.17, 건물데미지도 방어력 적용
@Update: 2024.5.19, 잘보이도록 표시 개선

*/
namespace 신의가호_Gods
{
	const int 신의가호_확률 = 2;
	const float 신의가호_데미지_비율 = 1.5;
	const float 신의가호_방어_비율 = 0.5;
	const int 신의가호_지속턴 = 3;



	const int KEY = pk::hash("신의가호");

	class UnitInfo
	{
		pk::unit@ unit;
		int startDay = -1;
		int startTick = -1;
	};

	class Main
	{
	
		pk::func209_t@ prev_callback_209;
		pk::func211_t@ prev_callback_211;


		Main()
		{
			pk::bind(120, pk::trigger120_t(UpdatePerFrame));
			pk::bind(107, pk::trigger107_t(onNewDay));
			pk::bind(171, pk::trigger171_t(부대제거));

			@prev_callback_209 = cast<pk::func209_t@>(pk::get_func(209));
			pk::reset_func(209);
			pk::set_func(209, pk::func209_t(callback));

			@prev_callback_211 = cast<pk::func211_t@>(pk::get_func(211));
			pk::reset_func(211);
			pk::set_func(211, pk::func211_t(callback211));

			pk::bind(102, pk::trigger102_t(Init));
			pk::bind(105, pk::trigger105_t(SaveData));


		}

		void Init()
		{
			LoadData();
		}

		void LoadData()
		{
			while (_unitInfos.length > 0)
				_unitInfos.removeLast();

			int count = int(pk::load(KEY, 0, 0));
			int li = 1;
			for (int i = 0; i < count; i++)
			{
				UnitInfo ui;
				@ui.unit = pk::get_unit(int(pk::load(KEY, li++, 0)));
				ui.startTick = -1;
				ui.startDay = int(pk::load(KEY, li++, 0));
				_unitInfos.insertLast(ui);
			}
		}
		void SaveData(int file_id)
		{
			pk::store(KEY, 0, _unitInfos.length);
			int si = 1;
			for (int i = 0; i < _unitInfos.length; i++)
			{
				UnitInfo@ ui = _unitInfos[i];
				pk::store(KEY, si++, ui.unit.get_id());
				pk::store(KEY, si++, ui.startDay);
			}
		}


		array<UnitInfo> _unitInfos;

		bool isGod(pk::unit@ u)
		{
			for (int i = 0; i < _unitInfos.length; i++)
			{
				UnitInfo@ ui = _unitInfos[i];
				if (ui.unit.get_id() == u.get_id())
					return true;
			}
			return false;
		}
		void 부대제거(pk::unit@ unit, int type)
		{
			if (isGod(unit))
			{
				int index = -1;
				for (int i = 0; i < _unitInfos.length; i++)
				{
					UnitInfo@ ui = _unitInfos[i];
					if (ui.unit.get_id() == unit.get_id()) 
					{
						index = i;
						break;
					}
				}
				if (index != -1)
					_unitInfos.removeAt(index);

				pk::say(pk::encode("앗 신이시여..."), pk::get_person(unit.leader), unit);
			}
		}

		void callback(pk::damage_info& info, pk::unit@ attacker, int tactics_id, const pk::point& in target_pos, int type, int critical, bool ambush)
		{
			prev_callback_209(info, attacker, tactics_id, target_pos,type, critical, ambush);
			if (isGod(attacker)) 
			{
				info.troops_damage *= 신의가호_데미지_비율;
				pk::say(pk::encode("이것의 신의힘이다!!"),pk::get_person(attacker.leader),attacker);
			}
				
			pk::unit@ target = pk::get_unit(target_pos);
			if (target != null and isGod(target)) 
			{
				info.troops_damage *= 신의가호_방어_비율;
				pk::say(pk::encode("신의힘에 맞서다니.."), pk::get_person(target.leader), target);
			}
				
		}

		void callback211(pk::damage_info& info, pk::building@ attacker, pk::hex_object@ target)
		{
			prev_callback_211(info, attacker, target);
			pk::unit@ u = pk::is_valid_pos(target.get_pos()) ? pk::get_unit(target.get_pos()) : null;
			if (u != null && isGod(u))
			{
				info.troops_damage *= 신의가호_방어_비율;
			}
		}

		void UpdatePerFrame()
		{
			uint tick = pk::get_tick_count();
			for (int i = 0; i < _unitInfos.length; i++)
			{
				UnitInfo@ ui = _unitInfos[i];
				
				//pk::printf("{}\n",pk::decode(pk::get_name(pk::get_person(ui.unit.leader))));


				if (ui.startTick == -1)
					ui.startTick = tick;

				uint off = tick - ui.startTick;
				if (off > 1000) 
					ui.startTick = tick;

					
				float dt = pk::min(1.0, float(off) / 1000.0);
				//pk::printf("dt {}, off{} \n",dt,off);
				
				dt = sin(dt * 3.141592);

				int color2 = int(dt * 0x80) * 0x1000000 + 0x000000ff;
				
				//color2 = 0xffff0000;
				
				int w2 = 16;
				int h2 = 4;

				{
					pk::point point = pk::hex_pos_to_screen_pos(ui.unit.get_pos());
					//point.x = 300; point.y=100;
					point.y += h2;
					pk::size size0(w2, h2);
					pk::rectangle r0(point, size0);
					pk::draw_filled_rect(r0, color2);


					pk::point point2 = pk::hex_pos_to_screen_pos(ui.unit.get_pos());
					point2.x += (w2 * 0.5 - h2 * 0.5);
					pk::size size2(h2, w2);
					pk::rectangle r2(point2, size2);
					pk::draw_filled_rect(r2, color2);

				}

				{
					pk::point pt = pk::get_neighbor_pos(ui.unit.get_pos(), 방향_남, 1);
					pk::point point = pk::hex_pos_to_screen_pos(pt);
					point.y += h2;
					pk::size size0(w2, h2);
					pk::rectangle r0(point, size0);
					pk::draw_filled_rect(r0, color2);



					pk::point point2 = pk::hex_pos_to_screen_pos(pt);
					point2.x += (w2 * 0.5 - h2 * 0.5);
					pk::size size2(h2, w2);
					pk::rectangle r2(point2, size2);
					pk::draw_filled_rect(r2, color2);

				}


				{
					pk::point pt = pk::hex_pos_to_screen_pos(ui.unit.get_pos());
					pk::point pt2 = pk::hex_pos_to_screen_pos(pk::get_neighbor_pos(ui.unit.get_pos(), 방향_남, 1));
					pk::point point = pk::point(pt2.x + pt2.y - pt.y, pt2.y);
					point.y += h2;
					pk::size size0(w2, h2);
					pk::rectangle r0(point, size0);
					pk::draw_filled_rect(r0, color2);


					pk::point point2 = pk::point(pt2.x + pt2.y - pt.y, pt2.y);
					point2.x += (w2 * 0.5 - h2 * 0.5);
					pk::size size2(h2, w2);
					pk::rectangle r2(point2, size2);
					pk::draw_filled_rect(r2, color2);
				}

				{
					pk::point pt = pk::hex_pos_to_screen_pos(ui.unit.get_pos());
					pk::point pt2 = pk::hex_pos_to_screen_pos(pk::get_neighbor_pos(ui.unit.get_pos(), 방향_남, 1));
					pk::point point = pk::point(pt.x + pt2.y - pt.y, pt.y);
					point.y += h2;
					pk::size size0(w2, h2);
					pk::rectangle r0(point, size0);
					pk::draw_filled_rect(r0, color2);


					pk::point point2 = pk::point(pt.x + pt2.y - pt.y, pt.y);
					point2.x += (w2 * 0.5 - h2 * 0.5);
					pk::size size2(h2, w2);
					pk::rectangle r2(point2, size2);
					pk::draw_filled_rect(r2, color2);
				}


			}
		}

		bool Check(pk::unit@ unit)
		{
			//주위 두칸에 있는 unit 확인, 플레이어/유저간 인경우만 처리
			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < 6; j++)
				{
					pk::point pt = pk::get_neighbor_pos(unit.get_pos(), j, i+1);
					auto obj = pk::get_hex_object(pt);
					if (obj!=null and obj.get_type_id() == 11)
					{
						if(obj.is_player() != unit.is_player())
								return true;
					}
				}
			}
			return false;
		}

		void onNewDay()
		{
			array<int> removes;
			for (int i = 0; i < _unitInfos.length; i++)
			{
				UnitInfo@ ui = _unitInfos[i];
				if (!ui.unit.is_alive() || pk::get_elapsed_days() - ui.startDay >= 신의가호_지속턴 * 10)
				{
					removes.insertLast(ui.unit.get_id());
				}
			}
			while (removes.length > 0)
			{
				int index = -1;
				for (int i = 0; i < _unitInfos.length; i++)
				{
					UnitInfo ui = _unitInfos[i];
					if (ui.unit.get_id() == removes[0]) 
					{
						index = i;
						break;
					}
				}
				if (index >= 0)
					_unitInfos.removeAt(index);
				removes.removeAt(0);
			}



			//if (_unitInfos.length > 0)
			//	return;
			
			
			pk::list<pk::force@> forces;
			forces.clear();
			forces = pk::get_force_list();
			for (auto i = 0; i < forces.count; i++)
			{
				pk::force@ force = forces[i];
				if (!pk::is_alive(force) or !pk::is_normal_force(force) or
					!pk::is_alive(pk::get_person(force.kunshu)))
					continue;

				pk::list<pk::unit@> units = pk::get_unit_list(force);
				for (int iUnit = 0; iUnit < units.count; iUnit++)
				{
					pk::unit@ unit = units[iUnit];
					if(!Check(unit))
						continue;
					
					if (!pk::rand_bool(신의가호_확률))
						continue;

					UnitInfo ui;
					@ui.unit = unit;
					ui.startDay = pk::get_elapsed_days();
					_unitInfos.insertLast(ui);
				}
			}
		}
	}
	Main main;
}