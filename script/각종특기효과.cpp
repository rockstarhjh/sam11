namespace 각종특기효과
{
	class Main
	{
		Main()
		{
			pk::bind(107, pk::trigger107_t(NewDay));
			pk::bind(110, pk::trigger110_t(NewYear));
			pk::bind(173, pk::trigger173_t(get_exp));
			pk::bind(174, pk::trigger174_t(action_done));
		}

		void NewDay()
		{
			for (int i = 0; i < 도시_끝; i++)
			{
				pk::city@ city = pk::get_city(i);

				if (city is null or !pk::is_valid_force_id(city.get_force_id()))
					continue;

				pk::building@ building = pk::city_to_building(city);
				pk::force@ force = pk::get_force(city.get_force_id());

				if (pk::is_valid_person_id(building.who_has_skill(특기_안력)) and pk::is_valid_person_id(building.who_has_skill(특기_지도)) and force.sp_ability_researched[2] and pk::get_ability(force.sp_ability[2]).skill == 특기_안력)
					pk::add_tp(force, pk::get_person_list(building, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반)).size, building.get_pos());

				if (pk::is_valid_person_id(building.who_has_skill(특기_지도)) and pk::is_valid_person_id(building.who_has_skill(특기_안력)) and force.sp_ability_researched[2] and pk::get_ability(force.sp_ability[2]).skill == 특기_지도)
					pk::add_tp(force, pk::get_person_list(building, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반)).size, building.get_pos());
			}
		}

		void NewYear()
		{
			for (int i = 0; i < 도시_끝; i++)
			{
				pk::city@ city = pk::get_city(i);

				if (city is null or !pk::is_valid_force_id(city.get_force_id()))
					continue;

				pk::building@ building = pk::city_to_building(city);
				pk::force@ force = pk::get_force(city.get_force_id());

				// 풍수 연구시 기원과 한 도시에서 새해를 맞으면 반드시 풍작
				if (pk::is_valid_person_id(building.who_has_skill(특기_풍수)) and pk::is_valid_person_id(building.who_has_skill(특기_기원)) and force.sp_ability_researched[2] and pk::get_ability(force.sp_ability[2]).skill == 특기_풍수)
					city.next_housaku = true;

				// 기원 연구시 풍수와 한 도시에서 새해를 맞으면 반드시 풍작
				if (pk::is_valid_person_id(building.who_has_skill(특기_기원)) and pk::is_valid_person_id(building.who_has_skill(특기_풍수)) and force.sp_ability_researched[2] and pk::get_ability(force.sp_ability[2]).skill == 특기_기원)
					city.next_housaku = true;
			}
		}

		void get_exp(pk::unit@ unit, int type)
		{
			if (!pk::is_alive(unit))
				return;

			pk::force@ force = pk::get_force(unit.get_force_id());

			// 창극노기 전법 성공시
			if ((type == 6) or (type == 7) or (type == 9) or (type == 10) or (type == 12) or (type == 13) or (type == 15) or (type == 16) or (type == 18) or (type == 19) or (type == 21) or (type == 22) or ((type == 24 or type == 25) and unit.weapon == 병기_노) or (type == 27) or (type == 28) or (type == 30) or (type == 31) or (type == 33) or (type == 34) or (type == 36) or (type == 37) or (type == 39) or (type == 40))
			{
				// 앙양 특기 기력 5 회복
				if (unit.has_skill(특기_앙양))
					pk::add_energy(unit, 5, true);

				// 비장 연구시 50% 확률로 재행동
				if (unit.has_skill(특기_비장) and force.sp_ability_researched[6] and pk::get_ability(force.sp_ability[6]).skill == 특기_비장 and pk::rand_bool(50))
					pk::set_status(unit, unit, 부대상태_폭주, 0, true);

				// 용장 연구시 25% 확률로 재행동
				if (unit.has_skill(특기_용장) and force.sp_ability_researched[4] and pk::get_ability(force.sp_ability[4]).skill == 특기_용장 and pk::rand_bool(25))
					pk::set_status(unit, unit, 부대상태_폭주, 0, true);
			}

			// 공성, 수군 전법 성공시
			if (((type == 24 or type == 25) and unit.weapon != 병기_노) or (type == 42) or (type == 43) or (type == 45) or (type == 46) or (type == 48) or (type == 49) or (type == 51) or (type == 52))
			{
				// 앙양 특기 기력 5 회복
				if (unit.has_skill(특기_앙양))
					pk::add_energy(unit, 5, true);

				// 용장 연구시 25% 확률로 재행동
				if (unit.has_skill(특기_용장) and force.sp_ability_researched[4] and pk::get_ability(force.sp_ability[4]).skill == 특기_용장 and pk::rand_bool(25))
					pk::set_status(unit, unit, 부대상태_폭주, 0, true);
			}

			// 전법 실패시
			if ((type == 8) or (type == 11) or (type == 14) or (type == 17) or (type == 20) or (type == 23) or (type == 26) or (type == 29) or (type == 32) or (type == 35) or (type == 38) or (type == 41) or (type == 44) or (type == 47) or (type == 50) or (type == 53))
			{
				// 노발 특기 기력 10 회복
				if (unit.has_skill(특기_노발))
					pk::add_energy(unit, 10, true);

				// 신장 연구시 100% 재행동
				if (unit.has_skill(특기_신장) and force.sp_ability_researched[5] and pk::get_ability(force.sp_ability[5]).skill == 특기_신장)
					pk::set_status(unit, unit, 부대상태_폭주, 0, true);
			}

			// 화계 성공시
			if ((type == 54) or (type == 55))
			{
				// 백출 연구시 기력을 100 회복
				if (unit.has_skill(특기_백출) and force.sp_ability_researched[9] and pk::get_ability(force.sp_ability[9]).skill == 특기_백출)
					pk::add_energy(unit, 100, false);
				// 백출 특기가 기력 10 회복
				else if (unit.has_skill(특기_백출))
					pk::add_energy(unit, 10, false);

				// 허실 연구시 25% 재행동
				if (unit.has_skill(특기_허실) and force.sp_ability_researched[9] and pk::get_ability(force.sp_ability[9]).skill == 특기_허실 and pk::rand_bool(25))
					pk::set_status(unit, unit, 부대상태_폭주, 0, true);
			}

			// 소화 성공시
			if ((type == 57) or (type == 58))
			{
				// 백출 연구시 기력을 100 회복
				if (unit.has_skill(특기_백출) and force.sp_ability_researched[9] and pk::get_ability(force.sp_ability[9]).skill == 특기_백출)
					pk::add_energy(unit, 100, false);
				// 백출 특기가 기력 10 회복
				else if (unit.has_skill(특기_백출))
					pk::add_energy(unit, 10, false);

				// 허실 연구시 25% 재행동
				if (unit.has_skill(특기_허실) and force.sp_ability_researched[9] and pk::get_ability(force.sp_ability[9]).skill == 특기_허실 and pk::rand_bool(25))
					pk::set_status(unit, unit, 부대상태_폭주, 0, true);
			}

			// 위보 성공시
			if ((type == 60) or (type == 61))
			{
				// 백출 연구시 기력을 100 회복
				if (unit.has_skill(특기_백출) and force.sp_ability_researched[9] and pk::get_ability(force.sp_ability[9]).skill == 특기_백출)
					pk::add_energy(unit, 100, false);
				// 백출 특기가 기력 10 회복
				else if (unit.has_skill(특기_백출))
					pk::add_energy(unit, 10, false);

				// 귀모 연구시 50% 재행동
				if (unit.has_skill(특기_귀모) and force.sp_ability_researched[3] and pk::get_ability(force.sp_ability[3]).skill == 특기_귀모 and pk::rand_bool(50))
					pk::set_status(unit, unit, 부대상태_폭주, 0, true);

				// 허실 연구시 25% 재행동
				if (unit.has_skill(특기_허실) and force.sp_ability_researched[9] and pk::get_ability(force.sp_ability[9]).skill == 특기_허실 and pk::rand_bool(25))
					pk::set_status(unit, unit, 부대상태_폭주, 0, true);
			}

			// 교란 성공시
			if ((type == 63) or (type == 64))
			{
				// 백출 연구시 기력을 100 회복
				if (unit.has_skill(특기_백출) and force.sp_ability_researched[9] and pk::get_ability(force.sp_ability[9]).skill == 특기_백출)
					pk::add_energy(unit, 100, false);
				// 백출 특기가 기력 10 회복
				else if (unit.has_skill(특기_백출))
					pk::add_energy(unit, 10, false);

				// 연환 연구시 50% 재행동
				if (unit.has_skill(특기_연환) and force.sp_ability_researched[3] and pk::get_ability(force.sp_ability[3]).skill == 특기_연환 and pk::rand_bool(50))
					pk::set_status(unit, unit, 부대상태_폭주, 0, true);

				// 허실 연구시 25% 재행동
				if (unit.has_skill(특기_허실) and force.sp_ability_researched[9] and pk::get_ability(force.sp_ability[9]).skill == 특기_허실 and pk::rand_bool(25))
					pk::set_status(unit, unit, 부대상태_폭주, 0, true);
			}

			// 진정 성공시
			if ((type == 66) or (type == 67))
			{
				// 백출 연구시 기력을 100 회복
				if (unit.has_skill(특기_백출) and force.sp_ability_researched[9] and pk::get_ability(force.sp_ability[9]).skill == 특기_백출)
					pk::add_energy(unit, 100, false);
				// 백출 특기가 기력 10 회복
				else if (unit.has_skill(특기_백출))
					pk::add_energy(unit, 10, false);

				// 통찰 연구시 재행동
				if (unit.has_skill(특기_통찰) and force.sp_ability_researched[9] and pk::get_ability(force.sp_ability[9]).skill == 특기_통찰)
					pk::set_status(unit, unit, 부대상태_폭주, 0, true);

				// 허실 연구시 25% 재행동
				if (unit.has_skill(특기_허실) and force.sp_ability_researched[9] and pk::get_ability(force.sp_ability[9]).skill == 특기_허실 and pk::rand_bool(25))
					pk::set_status(unit, unit, 부대상태_폭주, 0, true);
			}

			// 복병 성공시
			if ((type == 69) or (type == 70))
			{
				// 백출 연구시 기력을 100 회복
				if (unit.has_skill(특기_백출) and force.sp_ability_researched[9] and pk::get_ability(force.sp_ability[9]).skill == 특기_백출)
					pk::add_energy(unit, 100, false);
				// 백출 특기가 기력 10 회복
				else if (unit.has_skill(특기_백출))
					pk::add_energy(unit, 10, false);

				// 귀모 연구시 50% 재행동
				if (unit.has_skill(특기_귀모) and force.sp_ability_researched[3] and pk::get_ability(force.sp_ability[3]).skill == 특기_귀모 and pk::rand_bool(50))
					pk::set_status(unit, unit, 부대상태_폭주, 0, true);

				// 허실 연구시 25% 재행동
				if (unit.has_skill(특기_허실) and force.sp_ability_researched[9] and pk::get_ability(force.sp_ability[9]).skill == 특기_허실 and pk::rand_bool(25))
					pk::set_status(unit, unit, 부대상태_폭주, 0, true);
			}

			// 동토 성공시
			if ((type == 72) or (type == 73))
			{
				// 백출 연구시 기력을 100 회복
				if (unit.has_skill(특기_백출) and force.sp_ability_researched[9] and pk::get_ability(force.sp_ability[9]).skill == 특기_백출)
					pk::add_energy(unit, 100, false);
				// 백출 특기가 기력 10 회복
				else if (unit.has_skill(특기_백출))
					pk::add_energy(unit, 10, false);

				// 연환 연구시 50% 재행동
				if (unit.has_skill(특기_연환) and force.sp_ability_researched[3] and pk::get_ability(force.sp_ability[3]).skill == 특기_연환 and pk::rand_bool(50))
					pk::set_status(unit, unit, 부대상태_폭주, 0, true);

				// 허실 연구시 25% 재행동
				if (unit.has_skill(특기_허실) and force.sp_ability_researched[9] and pk::get_ability(force.sp_ability[9]).skill == 특기_허실 and pk::rand_bool(25))
					pk::set_status(unit, unit, 부대상태_폭주, 0, true);
			}

			// 일반 계략 실패시
			if ((type == 56) or (type == 59) or (type == 62) or (type == 65) or (type == 68) or (type == 71) or (type == 74))
			{
				// 명경 연구시 기력 20 회복
				if (unit.has_skill(특기_명경) and force.ability_researched[33])
					pk::add_energy(unit, 20, true);

				// 반계 연구시 75% 재행동
				if (unit.has_skill(특기_반계) and force.sp_ability_researched[3] and pk::get_ability(force.sp_ability[3]).skill == 특기_반계 and pk::rand_bool(100))
					pk::set_status(unit, unit, 부대상태_폭주, 0, true);
			}

			// 요술 성공시
			if ((type == 75) or (type == 76))
			{
				// 백출 연구시 기력을 100 회복
				if (unit.has_skill(특기_백출) and force.sp_ability_researched[9] and pk::get_ability(force.sp_ability[9]).skill == 특기_백출)
					pk::add_energy(unit, 100, false);
				// 백출 특기가 기력 10 회복
				else if (unit.has_skill(특기_백출))
					pk::add_energy(unit, 10, false);

				// 귀문 연구시 재행동
				if (unit.has_skill(특기_귀문) and force.sp_ability_researched[9] and pk::get_ability(force.sp_ability[9]).skill == 특기_귀문)
					pk::set_status(unit, unit, 부대상태_폭주, 0, true);
			}

			// 낙뢰 성공시
			if ((type == 78) or (type == 79))
			{
				// 백출 연구시 기력을 100 회복
				if (unit.has_skill(특기_백출) and force.sp_ability_researched[9] and pk::get_ability(force.sp_ability[9]).skill == 특기_백출)
					pk::add_energy(unit, 100, false);
				// 백출 특기가 기력 10 회복
				else if (unit.has_skill(특기_백출))
					pk::add_energy(unit, 10, false);

				// 귀문 연구시 재행동
				if (unit.has_skill(특기_귀문) and force.sp_ability_researched[9] and pk::get_ability(force.sp_ability[9]).skill == 특기_귀문)
					pk::set_status(unit, unit, 부대상태_폭주, 0, true);
			}

			// 축성 연구시 함정, 시설 건설하면 금 100 반환
			if ((type == 81 or type == 84) and unit.has_skill(특기_축성) and force.ability_researched[36])
				pk::add_gold(unit, 100, true);

			// 화신 연구시 계략으로 함정발동하면 재행동
			if (type == 88 and unit.has_skill(특기_화신) and force.sp_ability_researched[3] and pk::get_ability(force.sp_ability[3]).skill == 특기_화신)
				pk::set_status(unit, unit, 부대상태_폭주, 0, true);
		}

		void action_done(pk::unit@ unit)
		{
			if (!pk::is_alive(unit))
				return;

			// 능력연구를 위한 문장
			pk::force@ force = pk::get_force(unit.get_force_id());

			// 주악 연구시 행동을 마칠 때마다 기력 5 회복
			if (unit.has_skill(특기_주악) and force.sp_ability_researched[1] and pk::get_ability(force.sp_ability[1]).skill == 특기_주악)
				pk::add_energy(unit, 5, true);

			// 폭주 상태를 연속행동으로 전환
			if (unit.status == 부대상태_폭주)
			{
				pk::set_status(unit, unit, 부대상태_통상, 0, true);
				pk::set_action_done(unit, false);
				if (!pk::is_player_controlled(unit))
				{
					if (unit.order != -1)
						pk::run_order(unit);
					else
						pk::set_order(unit, 부대임무_대기, -1, -1);
				}
			}
		}
	}

	Main main;
}