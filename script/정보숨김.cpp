namespace 정보숨김
{
	// 건물 정보
	const uint open_building_info_flags = -1;
	const uint closed_building_info_flags = -1;
	// 군단 정보
	const uint open_district_info_flags = -1;
	const uint closed_district_info_flags = -1;
	// 세력 정보
	const uint open_force_info_flags = -1;
	const uint closed_force_info_flags = -1;
	// 무장 정보(충성도는 정렬하면 금방 알 수 있기 때문에 자세력이나 적세력 무장 모두 숨김)
	const uint open_person_info_flags = -1;
	const uint closed_person_info_flags = -1;
	// 부대 정보
	const uint open_unit_info_flags = -1;
	const uint closed_unit_info_flags = -1;

	class Main
	{
		dictionary visible_pos_;

		Main()
		{
			// 이 파일의 시나리오 초기화 이벤트는 세력 재배치 이후에 발생해야함.
			pk::bind(102, -1, pk::trigger102_t(onGameInit));
			pk::bind(111, pk::trigger111_t(onTurnStart));
			pk::bind(112, pk::trigger112_t(onTurnEnd));
			pk::bind(132, pk::trigger132_t(onForceLeaveControl));
			pk::bind(140, pk::trigger140_t(onDistrictCreate));
			pk::bind(152, pk::trigger152_t(onPersonForceChange));
			pk::bind(160, pk::trigger160_t(onBuildingCreate));
			pk::bind(170, pk::trigger170_t(onUnitCreate));
			pk::bind(172, pk::trigger172_t(onUnitPosChange));
		}

		/** 시야 범위
		@return
			최소, 최대 범위
		*/
		pk::int_int getSightRange(pk::object@ obj)
		{
			if (obj.is_instance(pk::unit::type_id))
			{
				return pk::int_int(1, 2);
			}
			else if (obj.is_instance(pk::building::type_id))
			{
				// pk::hex_object 타입으로 들어온 경우가 있을 수 있으므로 한번 변환
				auto building = pk::hex_object_to_building(obj);
				auto facility = pk::get_facility(building.facility);
				if (facility !is null)
					return pk::int_int(facility.min_range, facility.max_range + (building.facility == 시설_도시 ? 1 : 0));
			}
			return pk::int_int(0, 0);
		}

		/** 좌표를 키로 변환(visible_pos 테이블의 키로 사용됨) */
		string makeKey(const pk::point &in pos)
		{
			return pk::format("{}_{}", pos.x, pos.y);
		}

		/** 업데이트가 필요한 상황인지 판단
		@details
			난이도가 특급이고 플레이어턴인 경우
		*/
		bool needUpdate()
		{
			if (pk::get_scenario().difficulty != 난이도_특급) return false;
			auto force = pk::get_force(pk::get_current_turn_force_id());
			return force !is null and force.is_player();
		}

		/** 시야를 밝힘 */
		void update(int force_id, const pk::point &in pos, int min, int max)
		{
			visible_pos_[makeKey(pos)] = 0;
			auto range = pk::range(pos, min, max);
			for (int i = 0; i < range.length; i++)
			{
				visible_pos_[makeKey(range[i])] = 0;
				auto obj = pk::get_hex_object(range[i]);
				if (obj !is null and obj.get_force_id() != force_id)
				{
					pk::core::info(obj, -1, obj.is_instance(pk::unit::type_id) ? open_unit_info_flags : open_building_info_flags);
					auto person_list = pk::get_person_list(pk::get_hex_object_id(obj), -1);
					for (int j = 0; j < person_list.count; j++)
						pk::core::info(person_list[j], -1, open_person_info_flags);
				}
			}
		}

		/***/
		void onTurnStart(pk::force@ force)
		{
			// 시야 초기화
			visible_pos_.deleteAll();

			if (!needUpdate())
				return;

			// 모든 정보를 숨김 상태로 초기화
			pk::core::info(pk::building::type_id, -1);
			pk::core::info(pk::district::type_id, -1);
			pk::core::info(pk::force::type_id, -1);
			pk::core::info(pk::person::type_id, -1);
			pk::core::info(pk::unit::type_id, -1);

			int force_id = force.get_id();

			for (int i = 0; i < 건물_끝; i++)
			{
				auto building = pk::get_building(i);
				if (building.get_force_id() == force_id)
				{
					pk::core::info(building, -1, open_building_info_flags);
					auto range = getSightRange(building);
					update(force_id, building.get_pos(), range.first, range.second);
				}
			}

			for (int i = 0; i < 군단_끝; i++)
			{
				auto district = pk::get_district(i);
				if (district.get_force_id() == force_id)
					pk::core::info(district, -1, open_district_info_flags);
			}

			for (int i = 0; i < 세력_끝; i++)
			{
				auto force = pk::get_force(i);
				if (force.get_force_id() == force_id)
					pk::core::info(force, -1, open_force_info_flags);
			}

			for (int i = 0; i < 무장_끝; i++)
			{
				auto person = pk::get_person(i);
				if (person.get_force_id() == force_id)
					pk::core::info(person, -1, open_person_info_flags);
			}

			for (int i = 0; i < 부대_끝; i++)
			{
				auto unit = pk::get_unit(i);
				if (unit.get_force_id() == force_id)
				{
					pk::core::info(unit, -1, open_unit_info_flags);
					auto range = getSightRange(unit);
					update(force_id, unit.get_pos(), range.first, range.second);
				}
			}
		}

		/***/
		void onTurnEnd(pk::force@ force)
		{
			if (!needUpdate())
				return;

			// 세력, 군단, 무장은 컴퓨터 턴에서 확인할 수 없으므로 초기화 시키지 않음.
			for (int i = 0; i < 건물_끝; i++)
			{
				auto building = pk::get_building(i);
				pk::core::info(building, -1, -1);
			}

			for (int i = 0; i < 부대_끝; i++)
			{
				auto unit = pk::get_unit(i);
				pk::core::info(unit, 0, -1);
			}
		}

		/***/
		void onGameInit()
		{
			if (pk::get_scenario().loaded)
                                    onTurnStart(pk::get_force(pk::get_current_turn_force_id()));
                                    pk::core::info(-1, 1);
                                    pk::core::info(-2, 1);
                                    pk::core::info(-3, 1);
		}

		/***/
		void onUnitCreate(pk::unit@ unit, int type)
		{
			if (!needUpdate())
				return;

			pk::core::info(unit, -1, unit.get_force_id() == pk::get_current_turn_force_id() ? open_unit_info_flags : closed_unit_info_flags);
		}

		/***/
		void onUnitPosChange(pk::unit@ unit, const pk::point &in pos)
		{
			if (!needUpdate())
				return;

			auto range = getSightRange(unit);
			if (unit.get_force_id() == pk::get_current_turn_force_id())
				update(unit.get_force_id(), pos, range.first, range.second);
			else
				pk::core::info(unit, -1, visible_pos_.exists(makeKey(pos)) ? open_unit_info_flags : closed_unit_info_flags);
		}

		/***/
		void onBuildingCreate(pk::building@ building, int type)
		{
			if (!needUpdate())
				return;

			auto range = getSightRange(building);
			if (building.get_force_id() == pk::get_current_turn_force_id())
				update(building.get_force_id(), building.get_pos(), range.first, range.second);
			else
				pk::core::info(building, -1, visible_pos_.exists(makeKey(building.get_pos())) ? open_building_info_flags : closed_building_info_flags);
		}

		/***/
		void onDistrictCreate(pk::district@ district, int type)
		{
			if (!needUpdate())
				return;

			pk::core::info(district, -1, district.get_force_id() == pk::get_current_turn_force_id() ? open_district_info_flags : closed_district_info_flags);
		}

		/***/
		void onPersonForceChange(pk::person@ person, pk::force@ force)
		{
			if (!needUpdate())
				return;

			pk::core::info(person, -1, force.get_force_id() == pk::get_current_turn_force_id() ? open_person_info_flags : closed_person_info_flags);
		}

		/***/
		void onForceLeaveControl(pk::force@ force)
		{
			// 모든 세력을 위임한 경우
			if (pk::get_player_count() == 1)
			{
				// 모든 정보를 보이는 상태로 초기화
				pk::core::info(pk::building::type_id, -1);
				pk::core::info(pk::district::type_id, -1);
				pk::core::info(pk::force::type_id, -1);
				pk::core::info(pk::person::type_id, -1);
				pk::core::info(pk::unit::type_id, -1);
			}
			else
			{
				onTurnEnd(force);
			}
		}
	}

	Main main;
}