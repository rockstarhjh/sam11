namespace 부대의_공격_대미지
{
	class Main
	{
		Main()
		{
			pk::set_func(209, pk::func209_t(callback));
		}

		void callback(pk::damage_info& info, pk::unit@ attacker, int tactics_id, const pk::point &in target_pos, int type, int critical, bool ambush)
		{
			int force_id = attacker.get_force_id();
			pk::force@ force = pk::get_force(force_id);
			int weapon_id = attacker.weapon;
			int command = func_5aee10(attacker);
			pk::unit@ target_unit = pk::get_unit(target_pos);
			pk::building@ target_building = pk::get_building(target_pos);
			int atk = 0;
			int troops_atk = 0;
			int buffed = 0;

			// 공격 능력치
			if (ambush)
				atk = pk::max(attacker.attr.stat[부대능력_지력] - 5, 1);
			else
				atk = attacker.attr.stat[부대능력_공격];

			// 사정 연구시 투석 전법에서 지력으로 공격력 대체 가능
			if (attacker.has_skill(특기_사정) and (tactics_id == 전법_공성투석 or tactics_id == 전법_함선투석) and force.ability_researched[27])
				atk = pk::max(attacker.attr.stat[부대능력_지력] - 5, attacker.attr.stat[부대능력_공격]);

			// 병력 공격력, 전법 결과
			if (pk::is_valid_tactics_id(tactics_id))
			{
				troops_atk = pk::get_tactics(tactics_id).troops_atk;
				info.tactics_hit = pk::rand_bool(cast<pk::func202_t>(pk::get_func(202))(attacker, attacker.get_pos(), pk::get_hex_object(target_pos), tactics_id));
			}
			else if (pk::is_neighbor_pos(attacker.get_pos(), target_pos))
			{
				troops_atk = 10;
			}

			// 공격력 상승 버프
			if (func_5aed80(attacker.get_pos(), force_id))
			{
				buffed = 1;
				info.buffed = true;
				// 투신 특기가 태고대 버프를 2배로 받음 
				if (attacker.has_skill(특기_투신))
					buffed *= 2;
			}

			// 디버프
			if (target_unit !is null)
			{
				pk::force@ target_force = pk::get_force(target_unit.get_force_id());
				int facility_id = 시설_진;
				if (pk::has_tech(target_force, 기교_시설강화))
					facility_id = 시설_요새;
				if (pk::has_tech(target_force, 기교_성벽강화))
					facility_id = 시설_성채;
				if (func_5aedc0(target_unit.get_pos(), 1, pk::get_facility(facility_id).max_range, target_unit.get_force_id()))
				{
					if (!attacker.has_skill(특기_공성) or !force.sp_ability_researched[5] or pk::get_ability(force.sp_ability[5]).skill != 특기_공성)
						info.debuffer = facility_id;
				}
			}

			// 크리티컬
			info.critical = false;
			if (critical == 0)
			{
				if (pk::is_valid_tactics_id(tactics_id) and not info.tactics_hit)
					info.critical = false;
				else if (type == 0)
					info.critical = cast<pk::func201_t@>(pk::get_func(201))(attacker, pk::get_hex_object(target_pos), tactics_id, !pk::is_neighbor_pos(attacker.get_pos(), target_pos));
			}
			else if (critical == 1)
			{
				info.critical = true;
			}

			float 병기상성_강 = float(pk::core["병기상성.강"]); // 1.15f
			float 병기상성_약 = float(pk::core["병기상성.약"]); // 0.85f
			float 정예기교_공격력 = 1.15f;
			float 단련기교_공격력 = 1.10f;
			float 크리티컬_공격력 = 1.15f;

			if (target_unit !is null)
			{
				info.dst_troops = target_unit.troops;

				float troops_damage = func_5aee60(atk, command, troops_atk, buffed, target_unit.attr.stat[부대능력_방어], func_5aee10(target_unit));

				switch (weapon_id)
				{
				case 병기_창:
					if (pk::is_valid_tactics_id(tactics_id))
					{
						if (target_unit.weapon == 병기_극)
							troops_damage *= 병기상성_약;
						else if (target_unit.weapon == 병기_군마)
							troops_damage *= 병기상성_강;
					}

					if (pk::has_tech(force, 기교_정예창병))
						troops_damage *= 정예기교_공격력;
					else if (pk::has_tech(force, 기교_창병단련))
						troops_damage *= 단련기교_공격력;
					break;

				case 병기_극:
					if (pk::is_valid_tactics_id(tactics_id))
					{
						if (target_unit.weapon == 병기_창)
							troops_damage *= 병기상성_강;
						else if (target_unit.weapon == 병기_군마)
							troops_damage *= 병기상성_약;
					}

					if (pk::has_tech(force, 기교_정예극병))
						troops_damage *= 정예기교_공격력;
					else if (pk::has_tech(force, 기교_극병단련))
						troops_damage *= 단련기교_공격력;
					break;

				case 병기_노:
					if (pk::is_valid_tactics_id(tactics_id) and pk::equipment_id_to_heishu(target_unit.weapon) == 병종_병기)
						troops_damage *= 병기상성_약;

					if (pk::has_tech(force, 기교_정예노병))
						troops_damage *= 정예기교_공격력;
					else if (pk::has_tech(force, 기교_노병단련))
						troops_damage *= 단련기교_공격력;
					break;

				case 병기_군마:
					if (pk::is_valid_tactics_id(tactics_id))
					{
						if (target_unit.weapon == 병기_창)
							troops_damage *= 병기상성_약;
						else if (target_unit.weapon == 병기_극)
							troops_damage *= 병기상성_강;
					}

					if (pk::has_tech(force, 기교_정예기병))
						troops_damage *= 정예기교_공격력;
					else if (pk::has_tech(force, 기교_기병단련))
						troops_damage *= 단련기교_공격력;
					break;

				case 병기_정란:
				case 병기_주가:
				case 병기_누선:
				case 병기_투함:
					if (pk::is_valid_tactics_id(tactics_id) and pk::equipment_id_to_heishu(target_unit.weapon) == 병종_병기)
						troops_damage *= 0.8f;
					break;
				}

				if (attacker.is_player())
					troops_damage *= float(pk::core["대미지패널티"][pk::get_scenario().difficulty]);

				if (type == 0)
				{
					if (info.critical)
						troops_damage *= 크리티컬_공격력;

					if (pk::is_valid_tactics_id(tactics_id))
					{
						// 패왕 연구시 모든전법 피해량 10% 증가
						if (attacker.has_skill(특기_패왕) and force.ability_researched[31])
							troops_damage *= 1.10f;

						// 질주가 이동력 차이 %만큼 기병전법 피해 증가
						if (attacker.has_skill(특기_질주) and pk::get_weapon_id(attacker) == 병기_군마)
						{
							if (attacker.attr.stat[부대능력_이동] > target_unit.attr.stat[부대능력_이동])
							{
								troops_damage *= 1 + (attacker.attr.stat[부대능력_이동] - target_unit.attr.stat[부대능력_이동]) * 0.01f;
							}
						}
					}
					else
					{
						if (ambush)
						{
							// 기습 기교 복병 피해량 10% 증가
							if (pk::has_tech(force, 기교_기습) and attacker.weapon == 병기_창)
								troops_damage *= 1.10f;
						}
						else
						{
							// 연전 연구시 통상공격 피해량 10% 증가
							if (attacker.has_skill(특기_연전) and force.ability_researched[29])
								troops_damage *= 1.10f;

							// 백마가 이동력 차이 %만큼 기사 피해 증가
							if (attacker.has_skill(특기_백마) and !pk::is_neighbor_pos(attacker.get_pos(), target_unit.get_pos()) and pk::get_weapon_id(attacker) == 병기_군마)
							{
								if (attacker.attr.stat[부대능력_이동] > target_unit.attr.stat[부대능력_이동])
								{
									troops_damage *= 1 + (attacker.attr.stat[부대능력_이동] - target_unit.attr.stat[부대능력_이동]) * 0.01f;
								}
							}
						}
					}

					// 위풍, 소탕 특기가 기력 떨어진 부대에 10% 추가 피해 (특기종합패치)
					if (target_unit.energy == 0)
					{
						if (attacker.has_skill(특기_위풍) or attacker.has_skill(특기_소탕))
							troops_damage *= 1.10f;
					}

					// 급습, 강습 특기가 상태이상 부대에 10% 추가 피해 (특기종합패치)
					if (target_unit.status != 부대상태_통상)
					{
						if (pk::is_in_water(attacker))
						{
							if (attacker.has_skill(특기_강습))
								troops_damage *= 1.10f;
						}
						else
						{
							if (attacker.has_skill(특기_급습))
								troops_damage *= 1.10f;
						}
					}

					info.troops_damage = troops_damage;
					if (func_5af230(info, attacker, target_unit, tactics_id))
						troops_damage = 0;

					if (attacker.has_skill(특기_소탕))
						info.energy_damage = pk::max(info.energy_damage, int(pk::core::skill_constant(attacker, 특기_소탕))); // 5

					// 소탕 연구시 기력감소량 3 추가
					if (attacker.has_skill(특기_소탕) and force.ability_researched[28])
						info.energy_damage += 3;

					if (attacker.has_skill(특기_위풍))
						info.energy_damage = pk::max(info.energy_damage, int(pk::core::skill_constant(attacker, 특기_위풍))); // 20

					// 심공 연구시 기력 피해의 절반을 흡수 (복병도 적용)
					if (attacker.has_skill(특기_심공) and force.sp_ability_researched[0] and pk::get_ability(force.sp_ability[0]).skill == 특기_심공)
					{
						if (ambush)
						{
							if (info.critical)
								info.energy_heal = pk::min(10, target_unit.energy);
							else
								info.energy_heal = pk::min(5, target_unit.energy);
						}
						else
							info.energy_heal = pk::min(info.energy_damage * 0.5f, target_unit.energy);
					}

					info.food_damage = func_5aecc0(attacker, target_unit);
					info.food_heal = info.food_damage;
				}
				else
				{
					if (type == 1)
						troops_damage *= 0.9f;
					else if (type == 2)
						troops_damage *= 0.4f;

					// 반격이기 때문에 target_unit은 공격을 실행한 부대를 뜻함.
					if (pk::is_in_water(target_unit))
					{
						if (target_unit.has_skill(특기_강습) and pk::rand_bool(int(pk::core::skill_constant(target_unit, 특기_강습))))
						{
							troops_damage = 0;
							info.def_skill = 특기_강습;
						}
					}
					else
					{
						if (target_unit.has_skill(특기_급습) and pk::rand_bool(int(pk::core::skill_constant(target_unit, 특기_급습))))
						{
							troops_damage = 0;
							info.def_skill = 특기_급습;
						}
					}
				}

				// 등갑이 방사 공격은 반으로 줄이지 않도록 변경
				if (target_unit.has_skill(특기_등갑) and tactics_id != 전법_공성방사)
					troops_damage = troops_damage / 2;

				// 철벽 연구시 진, 요새, 성채 범위에서 추가 방어
				pk::force@ target_force = pk::get_force(target_unit.get_force_id());
				if (info.debuffer == 시설_성채)
				{
					if (target_unit.has_skill(특기_철벽) and target_force.ability_researched[38])
					troops_damage *= 0.50f;
					else
					troops_damage *= 0.65f;
				}
				else if (info.debuffer == 시설_요새)
				{
					if (target_unit.has_skill(특기_철벽) and target_force.ability_researched[38])
					troops_damage *= 0.60f;
					else
					troops_damage *= 0.75f;
				}
				else if (info.debuffer == 시설_진)
				{
					if (target_unit.has_skill(특기_철벽) and target_force.ability_researched[38])
					troops_damage *= 0.70f;
					else
					troops_damage *= 0.85f;
				}

				info.troops_damage = troops_damage;
			}
			else if (target_building !is null and pk::is_general_type(target_building))
			{
				info.dst_troops = pk::get_troops(target_building);

				int facility_id = target_building.facility;
				int troops_atk, dst_atk, dst_def, dst_troops;
				func_5af0e0(troops_atk, dst_atk, dst_def, dst_troops, target_building);
				float troops_damage = func_5aee60(atk, command, troops_atk, buffed, dst_def, dst_troops);

				if (attacker.weapon == 병기_정란)
				{
					troops_damage *= 1.8f;
				}
				else if (attacker.weapon == 병기_투석)
				{
					troops_damage *= 1.2f;
				}
				else
				{
					troops_damage = func_5aee60(atk, pk::max(command * 0.75f, 1.f), troops_atk, buffed, dst_def, dst_troops);
					if (facility_id == 시설_도시)
						troops_damage *= 0.55f;
					else if (facility_id == 시설_관문)
						troops_damage *= 0.45f;
					else if (facility_id == 시설_항구)
						troops_damage *= 0.60f;
				}

				if (attacker.is_player())
					troops_damage *= float(pk::core["대미지패널티"][pk::get_scenario().difficulty]);

				if (type == 0)
				{
					if (info.critical)
						troops_damage *= 크리티컬_공격력;
				}
				else
				{
					if (type == 1)
						troops_damage *= 0.9f;
					else if (type == 2)
						troops_damage *= 0.4f;

					// 반격이기 때문에 target_unit은 공격을 실행한 부대를 뜻함.
					if (pk::is_in_water(target_unit))
					{
						if (target_unit.has_skill(특기_강습) and pk::rand_bool(int(pk::core::skill_constant(target_unit, 특기_강습))))
						{
							troops_damage = 0;
							info.def_skill = 특기_강습;
						}
					}
					else
					{
						if (target_unit.has_skill(특기_급습) and pk::rand_bool(int(pk::core::skill_constant(target_unit, 특기_급습))))
						{
							troops_damage = 0;
							info.def_skill = 특기_급습;
						}
					}
				}

				info.troops_damage = troops_damage;
			}

			if (target_building !is null)
			{
				int facility_id = target_building.facility;
				int hp_atk = 0;
				float hp_damage = 0;

				hp_atk = 5;
				if (pk::is_valid_tactics_id(tactics_id))
					hp_atk = pk::get_tactics(tactics_id).hp_atk;
				else if (pk::is_neighbor_pos(attacker.get_pos(), target_pos))
					hp_atk = 15;

				if (attacker.weapon == 병기_충차 or attacker.weapon == 병기_목수)
					hp_damage = func_5af050(atk, command, hp_atk, buffed);
				else
					hp_damage = func_5aeff0(atk, command, hp_atk, buffed);

				if (info.critical)
					hp_damage *= 크리티컬_공격력;

				if (facility_id >= 시설_불씨 and facility_id <= 시설_업화종)
				{
					hp_damage *= 1.6f;
				}
				else if (facility_id >= 시설_시장 and facility_id <= 시설_조선3단)
				{
					hp_damage *= 1.1f;
				}
				else if (facility_id == 시설_제방)
				{
					hp_damage *= 0.7f;
			
					// 추진 특기는 제방을 2배 속도로 파괴
					if (attacker.has_skill(특기_추진))
						hp_damage *= 2;
				}
				else if (attacker.weapon != 병기_충차 and attacker.weapon != 병기_목수)
				{
					switch (facility_id)
					{
					case 시설_도시:
					case 시설_요새:
					case 시설_연노로:
					case 시설_석벽:
						hp_damage *= 0.7f;
						break;
					case 시설_항구:
					case 시설_진:
						hp_damage *= 0.8f;
						break;
					case 시설_토루:
						hp_damage *= 0.9f;
						break;
					case 시설_관문:
					case 시설_성채:
						hp_damage *= 0.6f;
						break;
					}
				}

				if (facility_id == 시설_제방 and not target_building.completed)
					hp_damage = 0;

				if (attacker.has_tech(기교_운제))
				{
					if (attacker.weapon >= 병기_검 and attacker.weapon <= 병기_군마)
					{
						info.troops_damage *= 1.4f;
						hp_damage *= 1.4f;
					}
					else
					{
						info.troops_damage *= 1.2f;
						hp_damage *= 1.2f;
					}
				}

				if (attacker.is_player())
					hp_damage *= float(pk::core["대미지패널티"][pk::get_scenario().difficulty]);

				info.hp_damage = hp_damage;
			}

			info.tactics = tactics_id;
			info.src_pos = attacker.get_pos();
			info.dst_pos = target_pos;
		}

		/**
			획득 병량 계산
		*/
		int func_5aecc0(pk::unit@ attacker, pk::unit@ target)
		{
			if (pk::is_alive(attacker) and pk::is_alive(target) and attacker.weapon == 병기_창 and attacker.has_tech(기교_병량습격))
			{
				// 습격량이 지력에도 비례 (기교패치)
				int a = pk::rand(attacker.attr.stat[부대능력_공격] + attacker.attr.stat[부대능력_지력]) + attacker.attr.stat[부대능력_공격] + attacker.attr.stat[부대능력_지력];
				int b = pk::max(attacker.troops / 2, 1);
				int c = target.food;
				int d = pk::get_max_food(attacker) - attacker.food;
				return pk::min(a, b, c, d);
			}
			return 0;
		}

		/**
			공격력 상승 효과를 가진 시설 검색
		*/
		bool func_5aed80(const pk::point &in pos, int force_id)
		{
			/*
			array<pk::point> range = pk::range(pos, 1, 3);
			for (int i = 0; i < range.length; i++)
			{
				pk::building@ building = pk::get_building(range[i]);
				if (pk::is_alive(building) and building.facility == 시설_태고대 and building.completed and building.get_force_id() == force_id)
					return true;
			}
			return false;
			*/

			array<pk::point> range = pk::range(pos, 1, int(pk::core["시설.최대범위"]));
			for (int i = 0; i < range.length; i++)
			{
				pk::building@ building = pk::get_building(range[i]);
				if (pk::is_alive(building) and building.completed and building.get_force_id() == force_id)
				{
					if (bool(pk::core["시설"][building.facility]["공격력상승"]) and pk::get_distance(pos, range[i]) <= pk::get_facility(building.facility).max_range)
						return true;
				}
			}
			return false;
		}

		/**
			진, 요새, 성채 검색
		*/
		bool func_5aedc0(const pk::point &in pos, int min, int max, int force_id)
		{
			array<pk::point> range = pk::range(pos, min, max);
			for (int i = 0; i < range.length; i++)
			{
				pk::building@ building = pk::get_building(range[i]);
				if (pk::is_alive(building) and (building.facility == 시설_진 or building.facility == 시설_요새 or building.facility == 시설_성채) and building.completed and building.get_force_id() == force_id)
					return true;
			}
			return false;
		}

		/**
			지휘 가능한 병력 수
		*/
		int func_5aee10(pk::unit@ unit)
		{
			pk::person@ leader = pk::get_person(unit.leader);
			if (pk::is_alive(leader))
				return pk::min(pk::get_command(leader), unit.troops);
			return unit.troops;
		}

		/***/
		float func_5aee60(int src_atk, int src_troops, int tactics_atk, int buffed, int dst_def, int dst_troops)
		{
			float n = 0;
			int a = 0;
			int b = 0;
			int c = 0;

			a = pk::max(src_atk, 40);
			a = a * a;

			b = pk::max(dst_def, 40);
			b = b * b;

			n = sqrt(tactics_atk * 64);
			n = n + pk::max((src_troops - dst_troops) / 2000, 0);
			n = n + pk::max((a - b) / 300, 0);
			n = n + 50;
			n = n * (buffed + 10);

			a = (src_troops / 100 + 300) * (src_atk + 50) * (src_atk + 50) / 100;
			b = (dst_troops / 100 + 300) * (dst_def + 50) * (dst_def + 50) / 100;
			c = a + b;
			if (a >= b)
				c = a * 100 / c;
			else
				c = pk::max(100 - (b * 100 / c), 1);
			n = n * c;

			a = pk::max(src_troops / 4, 1);
			n = n * pk::min(sqrt(a), 40.f);

			n = n / 2100;
			n = n + src_troops / 200;

			return n;
		}

		/***/
		float func_5aeff0(int src_atk, int src_troops, int tactics_atk, int buffed)
		{
			src_troops = pk::max(src_troops, 1);
			float a = sqrt(src_atk * src_atk / 15.f);
			float b = sqrt(src_troops);
			float c = tactics_atk * 4 + 100;
			float d = buffed + 10;
			return a * b * c * d / 10000;
		}

		/***/
		float func_5af050(int src_atk, int src_troops, int tactics_atk, int buffed)
		{
			src_troops = pk::max(src_troops, 1);
			float a = sqrt(src_atk * src_atk / 15.f);
			float b = sqrt(src_troops);
			float c = tactics_atk * 4 + 100;
			float d = buffed + 10;
			return a * pk::min(b, 40.f) * c * d / 10000 + (src_troops / 25) + b;
		}

		/***/
		void func_5af0e0(int &out src_atk, int &out dst_atk, int &out dst_def, int &out dst_troops, pk::building@ building)
		{
			src_atk = 10;
			pk::person@ taishu = pk::get_person(pk::get_taishu_id(building));
			if (pk::is_alive(taishu))
			{
				dst_atk = pk::max(taishu.stat[무장능력_무력] - 25, 40);
				dst_def = pk::max(taishu.stat[무장능력_통솔] - 25, 40);
				dst_troops = pk::min(pk::get_troops(building), pk::get_command(taishu));
			}
			else
			{
				dst_atk = 30;
				dst_def = 30;
				dst_troops = pk::min(pk::get_troops(building), 7000);
				if (dst_troops != 0)
					dst_troops = pk::max(dst_troops, 500);
			}
		}

		/***/
		bool func_5af230(pk::damage_info& info, pk::unit@ attacker, pk::unit@ target, int tactics_id)
		{
			if (pk::is_valid_tactics_id(tactics_id))
				return false;

			pk::point attacker_pos = attacker.get_pos();
			pk::point target_pos = target.get_pos();
			pk::force@ target_force = pk::get_force(target.get_force_id());

			if (target.weapon == 병기_극)
			{
				if (target.has_tech(기교_화살방패))
				{
					if (!pk::is_neighbor_pos(attacker_pos, target_pos) and pk::rand_bool(30))
					{
						info.def_tech = 기교_화살방패;
						return true;
					}
				}
				if (target.has_tech(기교_큰방패))
				{
					if (pk::is_neighbor_pos(attacker_pos, target_pos) and pk::rand_bool(30))
					{
						info.def_tech = 기교_큰방패;
						return true;
					}
				}
			}

			if (target.has_skill(특기_불굴))
			{
				// 불굴 연구시 병력기준 1000명 증가
				if (target_force.ability_researched[35] and (target.troops < int(pk::core::skill_constant(target, 특기_불굴)) + 1000) and pk::rand_bool(int(pk::core::skill_constant(target, 특기_불굴, 1))))
				{
					info.def_skill = 특기_불굴;
					return true;
				}
				else if (target.troops < int(pk::core::skill_constant(target, 특기_불굴)) and pk::rand_bool(int(pk::core::skill_constant(target, 특기_불굴, 1))))
				{
					info.def_skill = 특기_불굴;
					return true;
				}
			}

			if (target.has_skill(특기_금강))
			{
				// 금강 연구시 확률 25% 증가
				if (target_force.ability_researched[37] and info.troops_damage < int(pk::core::skill_constant(target, 특기_금강)) and pk::rand_bool(25 + int(pk::core::skill_constant(target, 특기_금강, 1))))
				{
					info.def_skill = 특기_금강;
					return true;
				}
				else if (info.troops_damage < int(pk::core::skill_constant(target, 특기_금강)) and pk::rand_bool(int(pk::core::skill_constant(target, 특기_금강, 1))))
				{
					info.def_skill = 특기_금강;
					return true;
				}
			}

			return false;
		}
	}

	Main main;
}