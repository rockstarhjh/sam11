/*
@ 수정자: 기마책사
@ Update: '18.10.21  / 변경내용: 무력통솔력수식변경, 이동력_병력설정, 이동력_적성설정, 이동력_통솔설정, 이동력_기력설정, 이동력_계절설정, 세력효과설정 기능 반영
@ Update: '18.11.6   / 변경내용: 유저옵션 추가 (기능변경 없음)
@ Update: '18.12.1   / 변경내용: 수송부대 이동력 조정 (병력효과 조정, 적성효과 제외)
@ Update: '18.12.27  / 변경내용: 이동력_영토설정 기능 추가
@ Update: '20.8.29   / 변경내용: 무력/통솔/지력/정치/매력 계산식에 overflow 방지 추가, 부대 공격/방어력 계산방식 선택옵션 추가, 이동력_최대제한 추가
*/

namespace 부대_능력치
{
    
    //---------------------------------------------------------------------------------------
    // 유저 설정 (true = on, false = off)
    const bool 무력통솔력_수식변경 = true;   // true: 부장능력 포함하는 신규 수식 적용, false: 기존 방식 적용
    
    const bool  공격력_수식변경 = true;   // true: 공격력 (무력+통솔 비율합산), false: 기존 방식 적용 (공격력 = 무력만 반영)
    const float 공격력_통솔비율 = 0.20f;  // 공격력에 합산할 통솔력 비율 (0.0f~1.0f)
    
    const bool  방어력_수식변경 = true;   // true: 방어력 (통솔+무력 비율합산), false: 기존 방식 적용 (방어력 = 통솔만 반영)
    const float 방어력_무력비율 = 0.20f;  // 방어력에 합산할 통솔력 비율 (0.0f~1.0f)
    
    const bool 이동력_병력설정 = true;   // 병력수에 따라 이동력 증감
    const bool 이동력_적성설정 = true;   // 적성에 따라 이동력 증감
    const bool 이동력_통솔설정 = true;   // 통솔력에 따라 이동력 증감
    const bool 이동력_기력설정 = true;   // 기력에 따라 이동력 증감
    const bool 이동력_계절설정 = true;   // 계절에 따라 이동력 증감
    const bool 이동력_영토설정 = true;   // 자국/타국 여부에 따라 이동력 증감
    
    const bool 이동력_최대제한 = true;   // true: 이동력 max=40, false: 이동력 max 제한없음
    
    const bool 세력효과설정 = true;   // 세력별 군령 효과 적용
    
    //---------------------------------------------------------------------------------------
    
	class Main
	{
		Main()
		{
			pk::set_func(163, pk::func163_t(callback));
		}

		void callback(pk::unit_attr& attr, const pk::detail::arrayptr<pk::person@> &in member, int weapon_id, uint troops, int type, int status, bool navy, bool shoubyou)
		{
			pk::person@ leader = member[0];
            

			if (!pk::is_alive(leader))
				return;

			pk::force@ force = pk::get_force(leader.get_force_id());
            
            // 주장이 소속된 부대 또는 건물 반환 ('18.10.10)
            int unit_energy = 0;
            pk::building@ building = pk::hex_object_to_building(pk::get_hex_object(leader.location));
            pk::unit@ unit;
            if (!pk::is_alive(building))    // 주장이 건물에 소속되어 있지 않으면 부대 기력값 사용
            {
                @unit = pk::get_unit(pk::get_unit_id(leader));
                unit_energy = unit.energy;
            }
            else                            // 주장이 건물 소속되어 출진 부대 편성 중이면 거점 기력값 사용
            {
                unit_energy = pk::get_energy(building);
            }
            
            

			if (!pk::is_alive(force))
				return;
			if (!pk::is_valid_equipment_id(weapon_id) or !pk::is_valid_unit_type(type) or !pk::is_valid_unit_status(status))
				return;

			
            
			// 부장이 없다면	
            if ((member[1] is null) and (member[2] is null))
			{
				for (int i = 0; i < 무장능력_끝; i++)	// 주장 능력치 그대로 사용
					attr.stat[i] =  pk::min(255, (shoubyou ? leader.stat[i] : leader.max_stat[i]));
			}
            // 부장이 있다면
			else
			{
				// 혐오 관계가 있다면 보정하지 않음
				if (func_4960d0(leader, member[1]) or func_4960d0(leader, member[2]) or func_4960d0(member[1], member[2]))
				{
					for (int i = 0; i < 무장능력_끝; i++)
						attr.stat[i] =  pk::min(255, (shoubyou ? leader.stat[i] : leader.max_stat[i]));
				}
				// 혐오 관계가 없다면 보정
				else
				{
					for (int i = 0; i < 무장능력_끝; i++)
					{
						int a = 0, b = 0;
						int leader_stat =  pk::min(255, (shoubyou ? leader.stat[i] : leader.max_stat[i]));

						// 통솔, 무력은 무장 관계에 따라 보정
						if (i <= 무장능력_무력)
						{
                            if (무력통솔력_수식변경)
                            {
                                // 신규 보정 수식 : 주장 + 부장1보조 + 부장2보조   ('18.10.9)
                                if (member[1] !is null)     // 신규 함수 : 부장1 보조량
                                    a = func_sub_stat(leader, leader_stat, member[1], (shoubyou ? member[1].stat[i] : member[1].max_stat[i]) ); 
                                if (member[2] !is null)     // 신규 함수 : 부장2 보조량
                                    b = func_sub_stat(leader, leader_stat, member[2], (shoubyou ? member[2].stat[i] : member[2].max_stat[i]) );
                                
                                attr.stat[i] = pk::min(255, (leader_stat + a + b));   // 255 이하로 합산
                            }
                            else
                            {
                                // 기존 보정 방법 : MAX[(주장&부장1),(주장&부장2)]
                                if (member[1] !is null)
                                    a = func_495ff0(leader, leader_stat, member[1], shoubyou ? member[1].stat[i] : member[1].max_stat[i]);
                                if (member[2] !is null)
                                    b = func_495ff0(leader, leader_stat, member[2], shoubyou ? member[2].stat[i] : member[2].max_stat[i]);
                                attr.stat[i] = pk::min(255, pk::max(a, b));   // 최대값
                            }
                            
						}
						// 지력, 정치, 매력은 최대값
						else
						{
							if (member[1] !is null)
								a = pk::max(leader_stat, shoubyou ? member[1].stat[i] : member[1].max_stat[i]);
							if (member[2] !is null)
								b = pk::max(leader_stat, shoubyou ? member[2].stat[i] : member[2].max_stat[i]);
                            
                            attr.stat[i] = pk::min(255, pk::max(a, b));   // 최대값
						}

					}
				}
			}

            
			// 적성은 최대값
			for (int i = 0; i < 병종_끝; i++)
			{
				int n = 0;
				for (int j = 0; j < member.length; j++)
				{
					if (member[j] !is null)
						n = pk::max(n, member[j].tekisei[i]);
				}
				attr.tekisei[i] = n;
			}

			pk::equipment@ equipment = pk::get_equipment(weapon_id);

			float apt = float(pk::core["적성"][attr.tekisei[pk::equipment_id_to_heishu(weapon_id)]]["부대능력치"]); // (attr.tekisei[pk::equipment_id_to_heishu(weapon_id)] + 7) * 0.1;
			float sts = 1.f;
			float str = 1.f;
			float ldr = 1.f;
			int atk = equipment.stat[병기능력_공격];
			int def = equipment.stat[병기능력_방어];
			int mov = equipment.stat[병기능력_이동];
            
			
			int defskill_불굴 = 특기_불굴;	
			int defskill_금강 = 특기_금강;	
			int defskill_철벽 = 특기_철벽;

			if (weapon_id == 병기_검 or (weapon_id == 병기_주가 and type == 부대종류_수송))	
				apt = 0.6f;

			if (status == 부대상태_혼란)
				sts = 0.8f;

			if (type == 부대종류_수송)
			{
				str = 0.4f;
				ldr = 1.f / 3.f;
			}

			if (weapon_id <= 병기_군마)
			{
				int tech_id = -1;	
				
				if (weapon_id == 병기_창)
				{
					tech_id = 기교_정예창병;
				}
				if (weapon_id == 병기_극)
				{
					tech_id = 기교_정예극병;
				}
				if (weapon_id == 병기_노)
				{
					tech_id = 기교_정예노병;
				}
				if (weapon_id == 병기_군마)
				{
					tech_id = 기교_정예기병;
				}

				if (pk::has_tech(force, tech_id))
				{
					atk = atk + 10;
					def = def + 10;
				}
				
			}
            
            // ------------------------------- //
            // 공격/방어력 추가 효과 적용 시 작성할 위치 //
            // ------------------------------- //
            
            
            /* 버프 적용 안함
            // 방어 특기자의 방어력 버프 : 종류별로 중첩 가능
            if (pk::has_skill(member, defskill_불굴))
                def = def + 10;
            if (pk::has_skill(member, defskill_금강))
                def = def + 10;
            if (pk::has_skill(member, defskill_철벽))
                def = def + 15;
            */
            
            
			/* 
				[원본] 부대 능력을 결정하는 요소들 < 공격(무력), 방어(통솔), 건설(정치) > 
				attr.stat[부대능력_공격] = pk::min(255.f, pk::max(1.f, (attr.stat[부대능력_무력] * atk * apt * 0.01f) * str * sts));
				attr.stat[부대능력_방어] = pk::min(255.f, pk::max(1.f, (attr.stat[부대능력_통솔] * def * apt * 0.01f) * ldr * sts));
				attr.stat[부대능력_건설] = pk::min(255.f, pk::max(1.f, (attr.stat[부대능력_정치] * 2.f / 3 + 50) * ldr * sts));
			*/
            float atk_stat_ratio = 0.0f;
            float def_stat_ratio = 0.0f;
            
			if  (공격력_수식변경)
                atk_stat_ratio = pk::min(1.0f, pk::max(0.0f, 공격력_통솔비율));
            else
                atk_stat_ratio = 0.0f;
            
            if  (방어력_수식변경)
                def_stat_ratio = pk::min(1.0f, pk::max(0.0f, 방어력_무력비율));
            else
                def_stat_ratio = 0.0f;
                        
            
			// 부대 공격력 = (주)무력, (부)통솔이 함께 관여 (합산)
			attr.stat[부대능력_공격] = int(pk::min(255.f, pk::max(1.f, (((1.f-atk_stat_ratio)*attr.stat[부대능력_무력]+atk_stat_ratio*attr.stat[부대능력_통솔])/ 1.0f * atk * apt * 0.01f ) * str * sts)));
			// 부대 방어력 = (주)통솔, (부)무력이 함께 관여 (합산)
			attr.stat[부대능력_방어] = int(pk::min(255.f, pk::max(1.f, (((1.f-def_stat_ratio)*attr.stat[부대능력_통솔]+def_stat_ratio*attr.stat[부대능력_무력])/ 1.0f * def * apt * 0.01f ) * ldr * sts)));
            
			// 부대 지력 = 지력
			attr.stat[부대능력_지력] = int(pk::min(255.f,(attr.stat[부대능력_지력] ) / 1.f));
			// 부대 건설 (원본과 동일)
			attr.stat[부대능력_건설] = int(pk::min(255.f, pk::max(1.f, (attr.stat[부대능력_정치] * 2.f / 3.f + 50) * ldr * sts)));
			
            
            //--------------------------------------------------------------------------------
            // 부대 조건에 따른 이동력 가변 효과
            
            // 부대별 기력, 통솔력, 적성, 병력수 효과 이동력 계산용 변수 추가 ('18.10.7)
            float mov_var = mov;  
            
            // 병력수에 따른 이동력 보정 : 기본 이동력 +1, 3000명 증가 시마다 이동력 감소 ('18.10.9)
            if (이동력_병력설정)
            {
                if (type == 부대종류_수송)
                    mov_var = mov_var + 1 - pk::min(5,(troops / 6000));    // 수송부대 이동력 감소 리미터 ('18.11.24)
                else
                    mov_var = mov_var + 1 - pk::min(10,(troops / 3000));    // 전투부대 이동력 감소 리미터
            }
            
            // 병과 적성에 따른 이동력 보정 S급=+10%, C급=-20%('18.10.8)
            if (이동력_적성설정)
            {
                if (type == 부대종류_전투)    // 전투부대에 한하여 적성 고려 추가 ('18.11.26)
                    mov_var = mov_var * (1.f + 0.1f * pk::min(2, (attr.tekisei[pk::equipment_id_to_heishu(weapon_id)] - 적성_A))); 
            }
            
            // 부대별 통솔력에 따른 이동력 변동 85% ~ 105% 변동 : 통솔력 75일 때 ±0% ('18.10.7)
            if (이동력_통솔설정)
                mov_var = mov_var * (0.85f + 0.20f * (attr.stat[부대능력_통솔] / 100.f));
            
            // 부대별 기력에 따른 이동력 80% ~ 110% 변동 : 기력 80일 때 100% ('18.10.10)
            if (이동력_기력설정)
                mov_var = mov_var * (0.80f + 0.30f * (unit_energy / 120.f));
            
            // 계절에 따른 이동력 증감 효과 ('18.10.9)
            if (이동력_계절설정)
            {
                switch(pk::get_season())            // pk::get_season()= 0:봄, 1:여름, 2:가을, 3:겨울
                {
                    case 계절_여름: mov_var -= 2; break;    // 여름에 이동력 -2
                    case 계절_겨울: mov_var -= 4; break;    // 겨율에 이동력 -4
                }
            }
            
            // 부대의 좌표 영토에 따른 이동력 효과 : 아군영토에서 이동력 상승, 적군영토에서 이동력 감소 ('18.12.27)
            if (이동력_영토설정 and pk::is_alive(unit))
            {
                pk::building@ area_building = pk::get_building(pk::get_building_id(unit.pos));
                if (pk::is_alive(area_building))
                {
                    if (unit.get_force_id() == area_building.get_force_id())
                        mov_var = mov_var * 1.1f;   // 아군영토에서 이동력 10%증가 
                    else if (pk::is_enemy(unit, area_building))
                        mov_var = mov_var * 0.9f;   // 적군영토에서 이동력 10% 감소 
                }
            }
            
            // 부대별 최종 가변 이동력
            mov = int(mov_var);
            
            //--------------------------------------------------------------------------------
            // 기존 스크립트 수정 : 기교 및 세력/장수별 특징 반영
            
			if (type == 부대종류_전투)
			{
				switch (weapon_id)
				{
				case 병기_창:
                    if (pk::has_tech(force, 기교_정예창병))
						mov = mov + 6;
					break;
                    
				case 병기_극:
                    if (pk::has_tech(force, 기교_정예극병))
						mov = mov + 6;
					break;
                    
				case 병기_노:
                    if (pk::has_tech(force, 기교_정예노병))
						mov = mov + 6;
					break;
                    
				case 병기_군마:
                    if (pk::has_tech(force, 기교_양마산출))
						mov = mov + 2;
                    if (pk::has_tech(force, 기교_정예기병))   // 정예기병 이동력 하향 ('18.10.5)
						mov = mov + 4;
					break;
                    
				case 병기_충차:
                    if (pk::has_tech(force, 기교_차축강화))   // 차축강화 이동력 상향 ('18.10.5)
						mov = mov + 4;
					break;
                    
				case 병기_정란:
                    if (pk::has_tech(force, 기교_차축강화))    // 차축강화 이동력 상향 ('18.10.5)
						mov = mov + 4;
					break;
                    
				case 병기_투석:
                    if (pk::has_tech(force, 기교_차축강화))    // 차축강화 이동력 상향 ('18.10.5)
						mov = mov + 4;
					break;
                    
				case 병기_목수:
					if (pk::has_tech(force, 기교_차축강화))
						mov = mov + 4;
					break;
				}

                
				if (weapon_id <= 병기_노)
				{
					mov = mov + int(pk::core::skill_constant(member, 특기_강행)); // 5
				}
				else if (weapon_id == 병기_군마)
				{
					if (pk::has_skill(member, 특기_강행))
						mov = mov + int(pk::core::skill_constant(member, 특기_강행)); // 5
					else if (pk::has_skill(member, 특기_행군))
						mov = mov + int(pk::core::skill_constant(member, 특기_행군)); // 3
                    
                    // 세력별 육상 이동력 보정 ('18.10.1) - 기병 세력 양마산출 효과 +2
                    if (세력효과설정 and pk::has_tech(force, 기교_양마산출))
                    {
                        if (pk::get_kunshu_id(force) == 무장_공손찬)
                            mov = mov + 2;
                        else if (pk::get_kunshu_id(force) == 무장_마등)
                            mov = mov + 2;
                        else if (pk::get_kunshu_id(force) == pk::get_kunshu_id(pk::get_person(무장_마초)))
                            mov = mov + 2;
                        else if (pk::get_kunshu_id(force) == 무장_동탁)
                            mov = mov + 2;
                        else if (pk::get_kunshu_id(force) == 무장_여포)
                            mov = mov + 2;
                    }
				}
                else if (weapon_id <= 병기_목수)
                {
                    // 세력별 육상 이동력 보정 ('18.10.1) - 조조 또는 유엽의 세력인 육상 차축강화 효과 +4
                    if (세력효과설정 and pk::has_tech(force, 기교_차축강화))
                    {
                        if (pk::get_kunshu_id(force) == 무장_조조)
                            mov = mov + 2;
                        else if (pk::get_kunshu_id(force) == pk::get_kunshu_id(pk::get_person(무장_유엽)))
                            mov = mov + 2;
                    }
                }
                
			}
			else if (type == 부대종류_수송)   // 수송부대
			{
				if (pk::has_tech(force, 기교_목우유마))
                    mov = mov + 3;
                
                mov = mov + 5;
				mov = mov + int(pk::core::skill_constant(member, 특기_운반)); // 5
               
               
                if (세력효과설정 and pk::has_tech(force, 기교_목우유마))
				{
                    if (weapon_id == 병기_주가) //수상에 있을 경우
                    {
                        // 세력별 운송력 보정 ('18.10.4) - 동오 군주 또는 주유/노숙의 세력인 경우 목우유마 수상 효과 +4
                        if (pk::get_kunshu_id(force) == 무장_손견)
                            mov = mov + 4;
                        else if (pk::get_kunshu_id(force) == 무장_손책)
                            mov = mov + 4;
                        else if (pk::get_kunshu_id(force) == 무장_손권)
                            mov = mov + 4;
                        else if (pk::get_kunshu_id(force) == pk::get_kunshu_id(pk::get_person(무장_주유)))
                            mov = mov + 4;
                        else if (pk::get_kunshu_id(force) == pk::get_kunshu_id(pk::get_person(무장_노숙)))
                            mov = mov + 4;
                    }
                     
                    else    //육상에 있을 경우
                    {
                        // 세력별 운송력 보정 ('18.10.4) - 촉한 군주 또는 제갈량/황월영의 세력인 경우 목우유마 육상 효과 +3
                        if (pk::get_kunshu_id(force) == 무장_유비)
                            mov = mov + 3;
                        else if (pk::get_kunshu_id(force) == 무장_유선)
                            mov = mov + 3;
                        else if (pk::get_kunshu_id(force) == pk::get_kunshu_id(pk::get_person(무장_제갈량)))
                            mov = mov + 3;
                        else if (pk::get_kunshu_id(force) == pk::get_kunshu_id(pk::get_person(무장_황월영)))
                            mov = mov + 3;
                    }
                }
			}
            
			if (navy)   //수상 부대인 경우
            {
				mov = mov + int(pk::core::skill_constant(member, 특기_조타)); // 4
                
                if (세력효과설정)
                {
                    mov += 4; // 부대조건의 수상이동력 반영에 따른 저하로 기본 이동력 보정
                    // 세력별 수상 이동력 보정 ('18.10.1) - 동오/형주 세력 수상전투부대 이동강화 - 차축강화 기교개발 시 적용됨
                    if (pk::has_tech(force, 기교_차축강화) and (type != 부대종류_수송)) //수송병과가 아님
                    {
                        if (pk::get_kunshu_id(force) == 무장_손견)
                            mov = mov + 4;
                        else if (pk::get_kunshu_id(force) == 무장_손책)
                            mov = mov + 4;
                        else if (pk::get_kunshu_id(force) == 무장_손권)
                            mov = mov + 4;
                        else if (pk::get_kunshu_id(force) == pk::get_kunshu_id(pk::get_person(무장_주유)))
                            mov = mov + 4;
                        else if (pk::get_kunshu_id(force) == pk::get_kunshu_id(pk::get_person(무장_여몽)))
                            mov = mov + 4;
                        else if (pk::get_kunshu_id(force) == pk::get_kunshu_id(pk::get_person(무장_육손)))
                            mov = mov + 4;
                            
                        else if (pk::get_kunshu_id(force) == 무장_유표)
                            mov = mov + 4;
                        else if (pk::get_kunshu_id(force) == pk::get_kunshu_id(pk::get_person(무장_채모)))
                            mov = mov + 4;
                    }
                }
            }
            
            // '20.8.29, 이동력 최대값 제한 설정 추가
            if (이동력_최대제한)
                mov = pk::min(40, mov);
            
			attr.stat[부대능력_이동] = pk::max(1, mov);   // '20.8.29, 이동력 최소값 제한 추가 (0 이하로 될 경우 게임 튕길 수 있음)
		}

        
        
		/**
			관계에 따른 능력 보정  -- 기존 수식 : 주장과 부장1, 주장과 부장2 의 각 보정 결과 중 최대값 
		*/
		int func_495ff0(pk::person@ leader, int leader_stat, pk::person@ deputy, int deputy_stat)
		{
			if (leader_stat > deputy_stat)
				return leader_stat;

			int leader_id = leader.get_id();
			int deputy_id = deputy.get_id();

			if (pk::is_gikyoudai(leader, deputy_id) or pk::is_fuufu(leader, deputy_id))
				return deputy_stat;

			if (pk::is_like(leader, deputy_id) or pk::is_like(deputy, leader_id))
				return leader_stat + (deputy_stat - leader_stat) / 2;

			if (pk::is_ketsuen(leader, deputy_id))
				return leader_stat + (deputy_stat - leader_stat) / 3;

			if (pk::is_dislike(leader, deputy_id) or pk::is_dislike(deputy, leader_id))
				return leader_stat;

			return leader_stat + (deputy_stat - leader_stat) / 4;
		}

		/**
			서로 상대방을 혐오하는 관계가 있는지 확인
		*/
		bool func_4960d0(pk::person@ a, pk::person@ b)
		{
			if (a !is null and b !is null)
				return pk::is_dislike(a, b.get_id()) or pk::is_dislike(b, a.get_id());
			return false;
		}
        
        // --------------------------------------------------------------------------------------
        //**  관계에 따른 능력 보정  -- 신규 수식 : 각 부장의 능력 보조량만 계산 후 주장+부장1+부장2 최종 합산 **/
        int func_sub_stat(pk::person@ leader, int leader_stat, pk::person@ deputy, int deputy_stat)
		{
            
			int leader_id = leader.get_id();
			int deputy_id = deputy.get_id();
            
            int stat_add = 0;
            
            // 혐오 관계 무장인 경우 : 보조 없음
            if (pk::is_dislike(leader, deputy_id) or pk::is_dislike(deputy, leader_id))
				stat_add = 0;
            // 의형제 또는 부부 관계인 경우 : 부장 능력의 25% 보조
            else if (pk::is_gikyoudai(leader, deputy_id) or pk::is_fuufu(leader, deputy_id))
				stat_add = int(pk::max(0.25f*deputy_stat, 1.f*(deputy_stat-leader_stat)));
            // 혈연 관계인 경우 : 부장 능력의 20% 보조
			else if (pk::is_ketsuen(leader, deputy_id))
				stat_add = int(0.2f * deputy_stat);
            // 주장/부장이 친애 무장인 경우 : 부장 능력의 15% 보조
			else if (pk::is_like(leader, deputy_id) or pk::is_like(deputy, leader_id))
				stat_add = int(0.15f * deputy_stat);
            // 기타 관계 : 부장 능력의 10% 보조
			else
				stat_add = int(0.1f * deputy_stat);
            
            return stat_add;
        }
        // --------------------------------------------------------------------------------------
        
	}

	Main main;
}

