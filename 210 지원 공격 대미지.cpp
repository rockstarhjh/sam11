namespace 지원_공격_대미지
{
    //---------------------------------------------------------------------------------------
    // 유저 설정 (true = on, false = off)
	const bool 사기효과설정 = true;   // 기력에 비례하여 데미지 증감 보정 효과
    const bool 기력증감설정 = true;   // 교전 시 데미지에 따라 공격부대 기력증가, 피격부대 기력감소
    const bool 지형효과설정 = true;   // 교전 시 지형종류 및 지형고저 영향 반영여부
    
    //---------------------------------------------------------------------------------------
    
	class Main
	{
		Main()
		{
			pk::set_func(210, pk::func210_t(callback));
		}
        /*----------------------------------------
            공격 피해량을 계산합니다.
            @param[out] damage	대미지 정보
            @param unit			부대
            @param tactics_id	#전법Id
            @param target_pos	목표 좌표
        ----------------------------------------*/
		void callback(pk::damage_info& info, pk::unit@ attacker, const pk::point &in target_pos)
		{
			int force_id = attacker.get_force_id();
			pk::force@ force = pk::get_force(force_id);
			int weapon_id = attacker.weapon;
			int command = func_5aee10(attacker);
			pk::unit@ target_unit = pk::get_unit(target_pos);
			pk::building@ target_building = pk::get_building(target_pos);
			int atk = attacker.attr.stat[부대능력_공격];
			int troops_atk = 0;
			int buffed = 0;

			if (pk::is_neighbor_pos(attacker.get_pos(), target_pos))
				troops_atk = 10;

			// 공격력 상승 버프
			if (func_5aed80(attacker.get_pos(), force_id))
			{
				buffed = 1;
				info.buffed = true;
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
				if (func_5aedc0(target_unit.get_pos(), 1, pk::get_facility(facility_id).range, target_unit.get_force_id()))
					info.debuffer = facility_id;
			}

			float 정예기교_공격력 = 1.15f;
			float 단련기교_공격력 = 1.10f;

			// 크리티컬
			info.critical = false;

			if (target_unit !is null)
			{
				float troops_damage = func_5aee60(atk, command, troops_atk, buffed, target_unit.attr.stat[부대능력_방어], func_5aee10(target_unit));

				switch (weapon_id)
				{
				case 병기_창:
					if (pk::has_tech(force, 기교_정예창병))
						troops_damage *= 정예기교_공격력;
					else if (pk::has_tech(force, 기교_창병단련))
						troops_damage *= 단련기교_공격력;
					break;

				case 병기_극:
					if (pk::has_tech(force, 기교_정예극병))
						troops_damage *= 정예기교_공격력;
					else if (pk::has_tech(force, 기교_극병단련))
						troops_damage *= 단련기교_공격력;
					break;

				case 병기_노:
					if (pk::has_tech(force, 기교_정예노병))
						troops_damage *= 정예기교_공격력;
					else if (pk::has_tech(force, 기교_노병단련))
						troops_damage *= 단련기교_공격력;
					break;

				case 병기_군마:
					if (pk::has_tech(force, 기교_정예기병))
						troops_damage *= 정예기교_공격력;
					else if (pk::has_tech(force, 기교_기병단련))
						troops_damage *= 단련기교_공격력;
					break;
				}

				info.troops_damage = int(troops_damage);
				if (func_5af230(info, attacker, target_unit, -1))
					troops_damage = 0;

                info.energy_damage = 0;
				if (attacker.has_skill(특기_소탕))
					info.energy_damage += pk::max(0, int(pk::core::skill_constant(attacker, 특기_소탕))); // 5

				if (attacker.has_skill(특기_위풍))
					info.energy_damage += pk::max(0, int(pk::core::skill_constant(attacker, 특기_위풍))); // 20

				info.food_damage = func_5aecc0(attacker, target_unit);  // 창병 병량 습격
				info.food_heal = info.food_damage;

				if (attacker.is_player())
					troops_damage *= float(pk::core["대미지패널티"][pk::get_scenario().difficulty]);

				if (target_unit.has_skill(특기_등갑))
					troops_damage = troops_damage / 2;

				if (info.debuffer == 시설_진)
					troops_damage *= 0.85f;
				else if (info.debuffer == 시설_요새)
					troops_damage *= 0.75f;
				else if (info.debuffer == 시설_성채)
					troops_damage *= 0.65f;
                
                
                if (!pk::is_campaign())
                {
                    // 부대 간 전투 시 병종별 지형 효과 추가 ('18.10.11)
                    if (지형효과설정)
                    {
                        troops_damage = troops_damage * (1.f + func_terrain_buf(attacker)) * (1.f - func_terrain_buf(target_unit)); //지형 유형
                        troops_damage = troops_damage * (1.f + 0.01f * get_height_diff(attacker.get_pos(), target_unit.get_pos())); //지형 높이차
                    }
                    
                    
                    // 부대간 교전 시 상호 기력 조건 반영됨 ('18.10.6)
                    if (사기효과설정)
                    {
                        // 공격부대 기력에 따라 피격부대 피해 85% ~ 115% 적용 : 부대 사기 효과 ('18.10.6)
                        troops_damage = troops_damage * (0.85f + 0.30f * (attacker.energy/120.f)) ;
                        // 피격부대 기력에 따라 피격부대 피해 85% ~ 115% 적용 : 부대 사기 효과 ('18.10.6)
                        troops_damage = troops_damage * (0.85f + 0.30f * ((120 - target_unit.energy)/120.f)) ;
                    }
                    
                    
                    // 병력 피해량에 따라 피격대상 기력감소, 공격부대 기력상승 효과 발생, 반격도 적용됨 ('18.10.6)
                    if (기력증감설정)
                    {
                        if (pk::is_enemy(attacker, target_unit))  // 서로 다른 세력인 부대간 교전 시에만 기력회복 : 동토 계략 시 기력회복 방지 ('18.10.22)
                        {
                            info.energy_heal = info.energy_heal + int(pk::min(15.f, (troops_damage / 200.f)));   //광역 전법데미지에 의한 기력 과도상승 리미터 적용
                            
                            if (troops_damage >= 500)
                            {
                                info.energy_damage = info.energy_damage + int((troops_damage - 500) / 100.f);
                            
                                if (target_unit.has_skill(특기_호위))  // 특기_호위 보유 부대는 병력피해 있어도 기력 감소 없음 ('18.10.14)
                                    info.energy_damage = 0;
                            }
                        }
                        else    // 동토(아군끼리 교전) 시 기력회복 없고, 데미지량에 비례하여 기력 데미지 발생 ('18.10.25)
                        {
                            info.energy_damage = info.energy_damage + int((troops_damage / 100.f));
                        }
                    }
                }
                
				info.troops_damage = int(troops_damage);
                
			}
			else if (target_building !is null and pk::is_general_type(target_building))
			{
				pk::assert(false);
			}

			if (target_building !is null)
			{
				pk::assert(false);
			}

			// 최소 병력 대미지
			if (info.troops_damage != 0)
				info.troops_damage = int(pk::max(info.troops_damage / 2, pk::rand(100) + 200));

			// 최소 내구 대미지
			if (info.hp_damage != 0)
				info.hp_damage = int(pk::max(info.hp_damage / 2, pk::rand(10) + 20));

			info.src_pos = attacker.get_pos();
			info.dst_pos = target_pos;
			info.type = 3; // ?
		}

		/**
			획득 병량 계산
		*/
		int func_5aecc0(pk::unit@ attacker, pk::unit@ target)
		{
			if (pk::is_alive(attacker) and pk::is_alive(target) and attacker.weapon == 병기_창 and attacker.has_tech(기교_병량습격))
			{
				int a = pk::rand(attacker.attr.stat[부대능력_공격]) + attacker.attr.stat[부대능력_공격];
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
			for (int i = 0; i < int(range.length); i++)
			{
				pk::building@ building = pk::get_building(range[i]);
				if (pk::is_alive(building) and building.completed and building.get_force_id() == force_id)
				{
					if (bool(pk::core["시설"][building.facility]["공격력상승"]) and pk::get_distance(pos, range[i]) <= int(pk::get_facility(building.facility).max_range))
						return true;
				}
			}
			return false;
		}

		/**
			진, 요새, 성채 검색
		*/
		bool func_5aedc0(pk::point pos, int min, int max, int force_id)
		{
			auto range = pk::range(pos, min, max);
			for (int i = 0; i < int(range.length); i++)
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

		/** 부대/거점 병력 피해 계산 **/
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

			//n = pk::sqrt(tactics_atk * 64);
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

		/** 부대 방어기교 및 방어특기 효과 반영 **/
		bool func_5af230(pk::damage_info& info, pk::unit@ attacker, pk::unit@ target, int tactics_id)
		{
			if (pk::is_valid_tactics_id(tactics_id))
				return false;

			pk::point attacker_pos = attacker.get_pos();
			pk::point target_pos = target.get_pos();

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
				if (int(target.troops) < int(pk::core::skill_constant(target, 특기_불굴)) and pk::rand_bool(int(pk::core::skill_constant(target, 특기_불굴, 1))))
				{
					info.def_skill = 특기_불굴;
					return true;
				}
			}

			if (target.has_skill(특기_금강))
			{
				if (info.troops_damage < int(pk::core::skill_constant(target, 특기_금강)) and pk::rand_bool(int(pk::core::skill_constant(target, 특기_금강, 1))))
				{
					info.def_skill = 특기_금강;
					return true;
				}
			}

			return false;
		}
        
        
        
        // --------------------------------------------------------
        
        
        // --------------------------------------------------------
        // 부대 간 전투 시 지형에 따른 병종별 어드밴티지 추가 ('18.10.11)
        float func_terrain_buf(pk::unit @ unit)
        {
            int weapon_id = unit.weapon;
            float terrain_buf = 0.f;
            pk::hex@ unit_hex = pk::get_hex(unit.get_pos());    // 부대의 좌표
            switch (unit_hex.terrain)                           // 좌표의 지형
            {
                case 지형_초원  : 
                                if (weapon_id == 병기_창)
                                    terrain_buf = 0.05f;
                                else if (weapon_id == 병기_군마)
                                    terrain_buf = 0.10f;
                                break;
                case 지형_땅  :    
                                if (weapon_id == 병기_창)
                                    terrain_buf = 0.05f;
                                else if (weapon_id == 병기_노)
                                    terrain_buf = 0.05f;
                                else if (weapon_id == 병기_군마)
                                    terrain_buf = 0.05f;
                                break;
                case 지형_모래  : 
                                if (weapon_id == 병기_창)
                                    terrain_buf = 0.05f;
                                else if (weapon_id == 병기_군마)
                                    terrain_buf = 0.05f;
                                break;
                case 지형_습지  : 
                                if (weapon_id == 병기_창)
                                    terrain_buf = -0.05f;
                                else if (weapon_id == 병기_극)
                                    terrain_buf = 0.10f;
                                else if (weapon_id == 병기_노)
                                    terrain_buf = -0.05f;
                                else if (weapon_id == 병기_군마)
                                    terrain_buf = -0.10f;
                                break;
                case 지형_독천  : 
                                if (weapon_id == 병기_창)
                                    terrain_buf = -0.10f;
                                else if (weapon_id == 병기_극)
                                    terrain_buf = 0.05f;
                                else if (weapon_id == 병기_노)
                                    terrain_buf = -0.10f;
                                else if (weapon_id == 병기_군마)
                                    terrain_buf = -0.15f;
                                break;
                case 지형_숲   : 
                                if (weapon_id == 병기_창)
                                    terrain_buf = 0.10f;
                                else if (weapon_id == 병기_극)
                                    terrain_buf = 0.05f;
                                else if (weapon_id == 병기_노)
                                    terrain_buf = 0.15f;
                                else if (weapon_id == 병기_군마)
                                    terrain_buf = -0.10f;
                                break;
                case 지형_황무지:  
                                if (weapon_id == 병기_창)
                                    terrain_buf = -0.05f;
                                else if (weapon_id == 병기_군마)
                                    terrain_buf = 0.05f;
                                break;
                case 지형_대로  : 
                                if (weapon_id == 병기_창)
                                    terrain_buf = 0.05f;
                                else if (weapon_id == 병기_극)
                                    terrain_buf = 0.05f;
                                else if (weapon_id == 병기_노)
                                    terrain_buf = 0.05f;
                                else if (weapon_id == 병기_군마)
                                    terrain_buf = 0.05f;
                                break;
            }
            
            // 특기_매복 보유부대는 병종 관계없이 숲/산/샛길에서 15% 추가 어드밴티지 ('18.10.14)
            if (unit.has_skill(특기_매복) and (unit_hex.terrain == 지형_숲 or unit_hex.terrain == 지형_산 or unit_hex.terrain == 지형_샛길 ) )
                terrain_buf += 0.15f;
            // 특기_해독 보유부대는 병종 관계없이 독천에서 15% 추가 어드밴티지 ('18.10.17)
            else if (unit.has_skill(특기_해독) and (unit_hex.terrain == 지형_독천) )
                terrain_buf += 0.15f;
            // 특기_답파 보유부대는 병종 관계없이 독천에서 15% 추가 어드밴티지 ('18.10.17)
            else if (unit.has_skill(특기_답파) and (unit_hex.terrain == 지형_벼랑길 or unit_hex.terrain == 지형_산 or unit_hex.terrain == 지형_샛길) )
                terrain_buf += 0.15f;
            
            return terrain_buf;
        }
        
        
        // 부대간 지형 높이차 ('18.10.14)
        int get_height_diff(const pk::point &in src, const pk::point &in dst)
		{
			return pk::get_height_map(pk::hex_pos_to_height_map_pos(src) + 2).height - pk::get_height_map(pk::hex_pos_to_height_map_pos(dst) + 2).height;
		}
        
        
        
	}

	Main main;
}