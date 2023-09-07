/*
@ 수정이 : 기마책사
@ UPDATE : '18.10.21  / 변경내용: 데미지 보정효과 적용
@ UPDATE : '18.11.8   / 변경내용: 유저설정 옵션 추가, 전략거점 크리티컬보정추가, 거점방어버프추가
@ UPDATE : '18.11.27  / 변경내용: 교전면향에 대미지보정 추가
@ UPDATE : '19.2.16   / 변경내용: 전법에 대한 불굴/금강 발동 시 전법실패 처리 + 방어막 이팩트 표시 + 반격대미지 적용되게 수정
@ UPDATE : '19.2.21   / 변경내용: 커스텀 대화표시가 교전 이후에 표시되도록 경험치획득트리거 방식으로 변경, 나선첨혼란확률 강제적용 옵션 추가
@ UPDATE : '19.3.3    / 변경내용: 후방피격시 혼란효과 기능 추가
@ UPDATE : '19.6.17   / 변경내용: 후방피격시 혼란효과 반격적용 버그 수정
@ UPDATE : '19.11.21  / 변경내용: 초특기연전 활성화 시 근접전법의 원거리발동 버그 수정, AI부대 전법최적화 옵션 추가
@ UPDATE : '20.4.11   / 변경내용: 전투병과의 공성파쇄 데미지 감소
@ UPDATE : '20.8.25   / 변경내용: 나선첨혼란확률 옵션OFF 처리 (pk2.1 신버젼에서 버그 수정됨)
@ UPDATE : '20.8.29   / 변경내용: 캠페인에서는 커스텀 세팅 사용 불가하도록 수정
@ UPDATE : '20.10.6   / 변경내용: 초특기연전 사거리 확인조건 수정, 전법최적화 확인조건 수정 (노병만제외)
@ UPDATE : '20.10.17  / 변경내용: 초특기연전 발동함수 오류 수정 (특기_사수, 숲에서 전법취소 현상), AI부대_노병화시전법 추가 (통상활공격을 화시로 변경)
@ UPDATE : '20.11.9   / 변경내용: 위풍/소탕 기력데미지 수식 오류 수정
*/

namespace 부대의_공격_대미지
{
    //---------------------------------------------------------------------------------------
    // 유저 설정 (true = on, false = off)
    const bool 대화표시설정 = true;   // 커스텀 효과 발동 시 대화표시 여부 (false 권장)
    
	const bool 사기효과설정 = true;   // 기력에 비례하여 데미지 증감 보정 효과
    const bool 기력증감설정 = true;   // 교전 시 데미지에 따라 공격부대 기력증가, 피격부대 기력감소
    const bool 지형효과설정 = true;   // 교전 시 지형종류 및 지형고저 영향 반영여부
    const bool 주변부대설정 = true;   // 주변 아군부대가 군주 또는 도독이거나, 특기_신산, 특기_허실 보유 시 보정효과
    const bool 교전방향설정 = true;   // 교전 시 부대 공격 방향에 따른 데미지 보정효과 적용
    const bool 거점방어특기 = true;   // 거점 내 장수의 방어특기(철벽,불굴,금강) 효과 적용
    const bool 전략거점설정 = true;   // 병과별 특정한 전략거점 점유한 세력의 부대는 크리티컬 공격력 증가 
    
    const bool 세력효과설정 = true;   // 세력별 군령 효과 적용
    const bool 병과특기설정 = true;   // 병과별 특기에 따른 데미지 보정 효과 적용
    const bool 거점능력합산 = true;   // true: 거점 내 무장들의 능력치 합산 기능 적용, false: 기존처럼 태수 능력만 적용
    const bool 거점방어버프 = true;   // 거점(도시,관문,항구)에 인접한 부대의 데미지 방어 버프 설정
    
    const float 대미지조절 = 0.8f;   // 전체적인 대미지량을 비율로 조절
    
    //---------------------------------------------------------------------------------------
    // 나선첨혼란확률 강제적용 (204 나선첨 혼란 확률.cpp 미동작 보완) --- pk2.1 신버젼에서 버그 수정되어 OFF 처리함
    const bool 나선첨혼란확률_강제적용 = false;   // 적용 시 참고사항 : 혼란→통상으로 상태 강제처리 시 애니메이션 어색할 수 있음
    const int  나선첨_크리티컬혼란확률 = 100;    // 기본값=100, 크리티컬일 때 혼란확률값
    const int  나선첨_전법성공혼란확률 = 30;     // 기본값=30, 크리티컬 아닐 때 혼란확률값 
    
    // 부대 후방피격시 혼란효과 : 교전방향설정=true 시 활성화되는 추가 옵션
    const bool 후방피격시_혼란적용 = true;   // 부대 후방피격시 일정확률로 혼란효과 (true=적용, false=미적용)
    const int  후방피격시_혼란확률 = 10;     // 후방피격시_혼란적용=true 시 혼란 확률값 (0~100)
    
    // 초특기연전 활성화 시 근접전법이 원거리에서 발동되는 버그 수정 (true 권장)
    const bool 초특기연전_발동설정 = true;     // 초특기연전 활성화 시 근접전법의 원거리발동 버그 수정
    
    // AI부대 전법 옵션
    const bool AI부대_전법최적화 = false;    // AI부대 교전 시 효과적인 전법을 선택
    const bool AI부대_노병화시전법 = true;   // AI부대 교전 시 노병 통상간접 공격을 화시로 변경
    
    //---------------------------------------------------------------------------------------
    
    
    class Main
	{
        
		Main()
		{
			pk::set_func(209, pk::func209_t(callback));
            
            pk::bind(173, pk::trigger173_t(onUnitExpAdd));
		}
        
        /*----------------------------------------
            공격 피해량을 계산합니다.
            @param[out] damage	대미지 정보
            @param unit			부대
            @param tactics_id	#전법Id
            @param target_pos	목표 좌표
            @param type			0 공격, 1 반격, 2 반격
            @param critical		0 치명타 확률 계산, 1 치명타 성공 강제, 2 치명타 실패 강제
            @param ambush		0 통상, 1 복병
        ----------------------------------------*/
		void callback(pk::damage_info& info, pk::unit@ attacker, int tactics_id, const pk::point &in target_pos, int type, int critical, bool ambush)
		{
			int force_id = attacker.get_force_id();
			pk::force@ force = pk::get_force(force_id);
			int weapon_id = attacker.weapon;
			int command = func_5aee10(attacker);
			pk::unit@ target_unit = pk::get_unit(target_pos);
			pk::building@ target_building = pk::get_building(target_pos);
            pk::hex_object@ target_obj = pk::get_hex_object(target_pos);
			int atk = 0;
			int troops_atk = 0;
			int buffed = 0;
            
            //---------------------------------------------------------------------------------------
            // 경험치획득 처리용 변수 초기화 ('19.2.21)
            @msg_unit = null;
            @msg_person = null;
            msg_string = "";
            
            @nasun_unit = null;
            나선첨_크리티컬 = false;
            
            @back_unit = null;
            //---------------------------------------------------------------------------------------

			// 공격 능력치
			if (ambush)
				atk = pk::max(attacker.attr.stat[부대능력_지력] - 5, 1);
			else
				atk = attacker.attr.stat[부대능력_공격];

            
            // AI부대 전법최적화 ('20.10.13)
            if (!pk::is_campaign() and !pk::is_player_controlled(attacker) and !ambush and type == 0)
            {
                if (AI부대_노병화시전법 and attacker.weapon == 병기_노 )    // 노병 간접통상 → 전법화시로 최적화
                    tactics_id = func_fire_on_arrow(attacker, target_obj, tactics_id);
                
                if (AI부대_전법최적화 and target_unit !is null)     // 근접 전법 최적화
                    tactics_id = func_dir_tactics_opt(attacker, target_unit, tactics_id);
            }
            
            
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
					info.debuffer = facility_id;
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

			// 부대간 전투 (병력)
            if (target_unit !is null)
			{
				info.dst_troops = target_unit.troops;

				float troops_damage = func_5aee60(atk, command, troops_atk, buffed, target_unit.attr.stat[부대능력_방어], func_5aee10(target_unit));
				
                /* 앙양 특기 버프 삭제 : 다수 부대에 반격 시 지나친 기력 회복 문제
				int 부대_기력회복 = 5;
				if (attacker.has_skill(특기_앙양))
					info.energy_heal = 부대_기력회복;
                */
                
                
				switch (weapon_id)
				{
				case 병기_창:
					if (pk::is_valid_tactics_id(tactics_id))
					{
						if (target_unit.weapon == 병기_극)
                        {
							troops_damage *= 병기상성_약;
                            
                            if (target_unit.has_tech(기교_큰방패))  // 극병 대상 기교효과 추가적용 ('18.10.5)
                                troops_damage *= 병기상성_약;
                        }
						else if (target_unit.weapon == 병기_군마)
							troops_damage *= 병기상성_강;
                        else if (target_unit.weapon == 병기_노)
							troops_damage *= 병기상성_강;
					}
                    
					if (pk::has_tech(force, 기교_정예창병))
                        troops_damage *= 정예기교_공격력; // 1.15f
					else if (pk::has_tech(force, 기교_창병단련))
                        troops_damage *= 단련기교_공격력; // 1.10f;
                    
                    // 위압 특기 (위압)
					if (병과특기설정 and attacker.has_skill(특기_위압) and !pk::is_campaign())
                    {
						troops_damage *= 1.15f;
                        
                        if (대화표시설정 and pk::is_player_controlled(attacker))
                        {
                            //pk::say(pk::encode("날카로운 창끝을 받아라"), pk::get_person(attacker.leader));
                            @msg_unit = @attacker;
                            @msg_person = pk::get_person(attacker.leader);
                            msg_string = "날카로운 창끝을 받아라";
                        }
                    }
                    
                    // 세력별 단련기교 어드밴티지 [원소, 조조, 조비, 조예, 손견, 손책]이 군주인 경우 ('18.9.30)
                    if (세력효과설정 and pk::has_tech(force, 기교_창병단련) and !pk::is_campaign())
                    {
                        
                        if (pk::get_kunshu_id(attacker) == 무장_원소)
                            troops_damage *= 1.1f;
                        else if (pk::get_kunshu_id(attacker) == 무장_조조)
                            troops_damage *= 1.1f;
                        else if (pk::get_kunshu_id(attacker) == 무장_조비)
                            troops_damage *= 1.1f;
                        else if (pk::get_kunshu_id(attacker) == 무장_조예)
                            troops_damage *= 1.1f;
                        else if (pk::get_kunshu_id(attacker) == 무장_손견)
                            troops_damage *= 1.1f;
                        
                        else 	
                            troops_damage *= 1.0f; 
                    }
					
					break;

				case 병기_극:
					if (pk::is_valid_tactics_id(tactics_id))
					{
						if (target_unit.weapon == 병기_군마)
							troops_damage *= 병기상성_약;
						else if (target_unit.weapon == 병기_창)
							troops_damage *= 병기상성_강;
                        else if (target_unit.weapon == 병기_노)    //노병 상성 추가 ('18.10.1)
							troops_damage *= 병기상성_강;
					}
                    
                    if (pk::has_tech(force, 기교_정예극병))
                        troops_damage *= 정예기교_공격력; // 1.15f
                    else if (pk::has_tech(force, 기교_극병단련))
                        troops_damage *= 단련기교_공격력; // 1.10f;
                    
					// 이민족 특기 (친만, 친월)
					if (병과특기설정 and (attacker.has_skill(특기_친만) or attacker.has_skill(특기_친월)) and !pk::is_campaign())
                    {
						troops_damage *= 1.15f;
                        
                        if (대화표시설정 and pk::is_player_controlled(attacker))
                        {
                            if (attacker.has_skill(특기_친만))
                            {
                                //pk::say(pk::encode("이것이 남만병의 위력이다"), pk::get_person(attacker.leader));
                                @msg_unit = @attacker;
                                @msg_person = pk::get_person(attacker.leader);
                                msg_string = "이것이 남만병의 위력이다";
                            }
                            else if (attacker.has_skill(특기_친월))
                            {
                                //pk::say(pk::encode("이것이 산월병의 위력이다"), pk::get_person(attacker.leader));
                                @msg_unit = @attacker;
                                @msg_person = pk::get_person(attacker.leader);
                                msg_string = "이것이 산월병의 위력이다";
                            }
                        }
                    }
                    
                    // 세력별 단련기교 어드밴티지 [유비, 유선, 유언, 유장, 맹획]이 군주인 경우 ('18.9.30)
                    if (세력효과설정 and pk::has_tech(force, 기교_극병단련) and !pk::is_campaign())
                    {
                        
                        if (pk::get_kunshu_id(attacker) == 무장_유비)
                            troops_damage *= 1.1f;
                        else if (pk::get_kunshu_id(attacker) == 무장_유선)
                            troops_damage *= 1.1f;
                        else if (pk::get_kunshu_id(attacker) == 무장_유언)
                            troops_damage *= 1.1f;
                        else if (pk::get_kunshu_id(attacker) == 무장_유장)
                            troops_damage *= 1.1f;
                        else if (pk::get_kunshu_id(attacker) == 무장_맹획)
                            troops_damage *= 1.2f;
                        
                        else 	
                            troops_damage *= 1.0f;
                    }
                    
					break;

				case 병기_노:
					if (pk::is_valid_tactics_id(tactics_id) and pk::equipment_id_to_heishu(target_unit.weapon) == 병종_병기)
						troops_damage *= 병기상성_약;
                    
                    if (pk::is_valid_tactics_id(tactics_id) and !pk::is_campaign())    
					{
                        // 기병 대상 상성 강화 ('18.10.1), 원거리 공격 한정 추가 ('18.11.13)
						if (target_unit.weapon == 병기_군마 and pk::get_distance(attacker.pos, target_unit.pos) >= 2)
                        {
							troops_damage *= 병기상성_강;
                            
                            if (pk::has_tech(force, 기교_강노)) // 강노 기교 시 기병 대상 상성 추가 ('18.10.5)
                                troops_damage *= 병기상성_강;
                        }
                        else if ((target_unit.weapon == 병기_극) and (target_unit.has_tech(기교_화살방패)))  // 극병 상성 기교효과 적용 ('18.10.5)
							troops_damage *= 병기상성_약;
					}
                    
                    if (pk::has_tech(force, 기교_정예노병))
                        troops_damage *= 정예기교_공격력; // 1.15f
                    else if (pk::has_tech(force, 기교_노병단련))
                        troops_damage *= 단련기교_공격력; // 1.10f;
                    
                    
                    // 해독 특기자 독화살 효과 ( ('18.10.14)
					if (병과특기설정 and attacker.has_skill(특기_해독) and !pk::is_campaign())
                    {   
                        if (!target_unit.has_skill(특기_해독))
                        {
                            troops_damage *= 1.15f;
                            
                            if (대화표시설정 and pk::is_player_controlled(attacker))
                            {
                                //pk::say(pk::encode("이것이 독화살의 위력이다"), pk::get_person(attacker.leader));
                                @msg_unit = @attacker;
                                @msg_person = pk::get_person(attacker.leader);
                                msg_string = "이것이 독화살의 위력이다";
                            }
                        }
                    }
                    
                    // 세력별 단련기교 어드밴티지[손권, 손책, 유표, 원술]이 군주인 경우 ('18.9.30)
                    if (세력효과설정 and pk::has_tech(force, 기교_노병단련) and !pk::is_campaign())
                    {
                        
                        if (pk::get_kunshu_id(attacker) == 무장_손권)
                            troops_damage *= 1.2f;
                        else if (pk::get_kunshu_id(attacker) == 무장_손책)
                            troops_damage *= 1.2f;
                        else if (pk::get_kunshu_id(attacker) == 무장_유표)
                            troops_damage *= 1.1f;
                        else if (pk::get_kunshu_id(attacker) == 무장_원술)
                            troops_damage *= 1.1f;
                        
                        else 	
                            troops_damage *= 1.0f;
                    }
                    
					break;

				case 병기_군마:
					if (pk::is_valid_tactics_id(tactics_id))
					{
						if (target_unit.weapon == 병기_창)
							troops_damage *= 병기상성_약;
						else if (target_unit.weapon == 병기_극)
							troops_damage *= 병기상성_강;
                        //노병 대상 상성 강화('18.10), 근접 공격 한정 ('18.11.13)
                        else if (target_unit.weapon == 병기_노 and (pk::get_distance(attacker.pos, target_unit.pos) <= 1)  and !pk::is_campaign())    
							troops_damage *= 병기상성_강;
					}
					
                    if (pk::has_tech(force, 기교_정예기병))
                        troops_damage *= 정예기교_공격력; // 1.15f
                    else if (pk::has_tech(force, 기교_기병단련))
                        troops_damage *= 단련기교_공격력; // 1.10f;
                    
					// 이민족 특기 (친강, 친오) : 근접 기병공격만 적용 ('18.10.28)
                    if (!pk::is_campaign())
                    {
                        if (병과특기설정 and (attacker.has_skill(특기_친강) or attacker.has_skill(특기_친오)) and (pk::get_distance(attacker.pos, target_unit.pos) <= 1) )
                        {
                            troops_damage *= 1.15f;
                            
                            if (대화표시설정 and pk::is_player_controlled(attacker))
                            {
                                if (attacker.has_skill(특기_친강))
                                {
                                    //pk::say(pk::encode("이것이 강족기병의 위력이다"), pk::get_person(attacker.leader));
                                    @msg_unit = @attacker;
                                    @msg_person = pk::get_person(attacker.leader);
                                    msg_string = "이것이 강족기병의 위력이다";
                                }
                                else if (attacker.has_skill(특기_친오))
                                {
                                    //pk::say(pk::encode("이것이 오환기병의 위력이다"), pk::get_person(attacker.leader));
                                    @msg_unit = @attacker;
                                    @msg_person = pk::get_person(attacker.leader);
                                    msg_string = "이것이 오환기병의 위력이다";
                                }
                            }
                        }
                    }
                    // 백마_특기 : 화살공격력 상향 ('18.10.28), 반격에 미적용 ('18.11.18)
                    if (!pk::is_campaign())
                    {
                        if (병과특기설정 and attacker.has_skill(특기_백마) and !target_unit.has_skill(특기_백마) and (pk::get_distance(attacker.pos, target_unit.pos) > 1) and type == 0)
                        {
                            if (pk::has_tech(force, 기교_기사))  // 기교_기사 개발 시 데미지 증가
                                troops_damage *= 1.4f;
                            else 
                                troops_damage *= 1.2f;
                            
                            if (대화표시설정 and pk::is_player_controlled(attacker))
                            {
                                //pk::say(pk::encode("이것이 백마기병진의 위력이다"), pk::get_person(attacker.leader));
                                @msg_unit = @attacker;
                                @msg_person = pk::get_person(attacker.leader);
                                msg_string = "이것이 백마기병진의 위력이다";
                                
                            }
                        }
                    }
                    // 세력별 단련기교 어드밴티지 [장수, 공손찬, 마등, 마초, 동탁, 여포]가 군주인 경우 ('18.9.30)
                    if (세력효과설정 and pk::has_tech(force, 기교_기병단련) and !pk::is_campaign())
                    {
                        
                        if (pk::get_kunshu_id(attacker) == 무장_공손찬)
                            troops_damage *= 1.2f;
                        else if (pk::get_kunshu_id(attacker) == 무장_마등)
                            troops_damage *= 1.2f;
                        else if (pk::get_kunshu_id(attacker) == 무장_마초)
                            troops_damage *= 1.2f;
                        else if (pk::get_kunshu_id(attacker) == 무장_여포)
                            troops_damage *= 1.2f;
                        else if (pk::get_kunshu_id(attacker) == 무장_동탁)
                            troops_damage *= 1.1f;
                        else if (pk::get_kunshu_id(attacker) == 무장_장수)
                            troops_damage *= 1.1f;
                        
                        else 	
                            troops_damage *= 1.0f;
                    }
                    
						
					break;

				case 병기_정란:
                    if (pk::is_valid_tactics_id(tactics_id) and !pk::is_campaign())    
					{
						if (target_unit.weapon == 병기_군마)    // 기병 대상 상성 강화 ('18.10.1)
                        {
							troops_damage *= 병기상성_강;
                            
                            if (pk::has_tech(force, 기교_강노)) // 강노 기교 시 기병 대상 상성 추가 ('18.10.5)
                                troops_damage *= 병기상성_강;
                        }
                        else if ((target_unit.weapon == 병기_극) and (target_unit.has_tech(기교_화살방패)))  // 극병 대상 기교효과 적용 ('18.10.5)
							troops_damage *= 병기상성_약;
					}
                    
                    // 해독 특기자 독화살 효과 ('18.10.14)
					if (병과특기설정 and attacker.has_skill(특기_해독) and !pk::is_campaign())
                    {   
                        if (!target_unit.has_skill(특기_해독))
                        {
                            troops_damage *= 1.15f;
                            
                            if (대화표시설정 and pk::is_player_controlled(attacker))
                            {
                                //pk::say(pk::encode("이것이 독화살의 위력이다"), pk::get_person(attacker.leader));
                                @msg_unit = @attacker;
                                @msg_person = pk::get_person(attacker.leader);
                                msg_string = "이것이 독화살의 위력이다";
                            }
                        }
                    }
                    
                    break;
				
				case 병기_주가:
				
					// 수군 관련 특기 (조타, 추진)
                    if(!pk::is_campaign())
                    {
                        if (attacker.has_skill(특기_조타) or attacker.has_skill(특기_추진))
                            troops_damage *= 1.05f;
                    }
                    break;
                    
				case 병기_누선:
				
					// 수군 관련 특기 (조타, 추진)
                    if(!pk::is_campaign())
                    {
                        if (attacker.has_skill(특기_조타) or attacker.has_skill(특기_추진))
                            troops_damage *= 1.10f;
                    }                    
					break;
                    
				case 병기_투함:
					if (pk::is_valid_tactics_id(tactics_id) and pk::equipment_id_to_heishu(target_unit.weapon) == 병종_병기)
						troops_damage *= 0.8f;
					
					// 수군 관련 특기 (조타, 추진)
                    if(!pk::is_campaign())
                    {
                        if (attacker.has_skill(특기_조타) or attacker.has_skill(특기_추진))
                            troops_damage *= 1.15;
                    }
					
					break;
				}
                
                // 수군의 육상부대에 대한 화시 전법상성 추가 ('18.10.21)
                // 수군 : 손오, 유표 세력 관련 인물들이 군주일 경우 - 숙련병 기교 어드밴티지 ('18.10.21)
                if (pk::is_in_water(attacker) and (attacker.type == 부대종류_전투) and !pk::is_campaign())
                {
                    if (pk::is_valid_tactics_id(tactics_id) and (tactics_id == 전법_화시 or tactics_id == 전법_공성화시 or tactics_id == 전법_함선화시) )    
					{
						if (!pk::is_in_water(target_unit) and target_unit.weapon == 병기_군마)    // 기병 대상 상성 강화 ('18.10.1)
                        {
							troops_damage *= 병기상성_강;
                            
                            if (pk::has_tech(force, 기교_강노)) // 강노 기교 시 기병 대상 상성 추가 ('18.10.5)
                                troops_damage *= 병기상성_강;
                        }
                        else if (!pk::is_in_water(target_unit) and (target_unit.weapon == 병기_극) and (target_unit.has_tech(기교_화살방패)))  // 극병 대상 기교효과 적용 ('18.10.5)
							troops_damage *= 병기상성_약;
                        
					}
                    
                    if (세력효과설정 and pk::has_tech(force, 기교_숙련병))
                    {
                        
                        if (pk::get_kunshu_id(attacker) == 무장_손견)
                            troops_damage *= 1.2f;
                        else if (pk::get_kunshu_id(attacker) == 무장_손책)
                            troops_damage *= 1.2f;
                        else if (pk::get_kunshu_id(attacker) == 무장_손권)
                            troops_damage *= 1.15f;
                        else if (pk::get_kunshu_id(attacker) == pk::get_kunshu_id(pk::get_person(무장_주유)))
                            troops_damage *= 1.15f;
                        else if (pk::get_kunshu_id(attacker) == pk::get_kunshu_id(pk::get_person(무장_육손)))
                            troops_damage *= 1.15f;
                        else if (pk::get_kunshu_id(attacker) == 무장_유표)
                            troops_damage *= 1.1f;
                        else if (pk::get_kunshu_id(attacker) == pk::get_kunshu_id(pk::get_person(무장_채모)))
                            troops_damage *= 1.1f;
                        
                        else
                            troops_damage *= 1.1f;
                        
                    }
                }
                
                

				if (attacker.is_player())
					troops_damage *= float(pk::core["대미지패널티"][pk::get_scenario().difficulty]);

                // 전략거점 점유 세력은 크리티컬 공격력 버프 적용 ('18.11.5)
                if (전략거점설정 and !pk::is_campaign())
                {
                    if (func_tactics_city(attacker, weapon_id))
                        크리티컬_공격력 += 0.05f;
                }
                        
				if (type == 0)
				{
					if (info.critical)
						troops_damage *= 크리티컬_공격력; // 1.15f;

					info.troops_damage = int(troops_damage);
					if (func_5af230(info, attacker, target_unit, tactics_id))
						troops_damage = 0;
					
                    info.energy_damage = 0;
					if (attacker.has_skill(특기_소탕))
						info.energy_damage += pk::max(0, int(pk::core::skill_constant(attacker, 특기_소탕))); // 5

                    if (attacker.has_skill(특기_위풍))      // 소탕+위풍 중첩 효과로 조정 ('18.10.9)
						info.energy_damage += pk::max(0, int(pk::core::skill_constant(attacker, 특기_위풍))); // 20

                    if (attacker.has_skill(특기_앙양))      // 특기 앙양 효과 반영, 반격에는 적용 안됨 ('18.10.21)
                        info.energy_heal = 5;
                    
                    // 창병 병량 습격
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
						if (target_unit.has_skill(특기_급습) and 
                            (pk::get_hex(target_unit.pos).terrain == 지형_숲 or pk::rand_bool(int(pk::core::skill_constant(target_unit, 특기_급습))) ) )
						{
							troops_damage = 0;
							info.def_skill = 특기_급습;
						}
					}
				}

				if (target_unit.has_skill(특기_등갑))
                {
					troops_damage = troops_damage / 2;
                    if (대화표시설정 and pk::is_player_controlled(attacker))
                    {
                        @msg_unit = @attacker;
                        @msg_person = pk::get_person(target_unit.leader);
                        msg_string = "우리 등갑부대에 맞서다니. 훗.";
                    }
                }

				if (info.debuffer == 시설_진)
					troops_damage *= 0.85f;
				else if (info.debuffer == 시설_요새)
					troops_damage *= 0.75f;
				if (info.debuffer == 시설_성채)
					troops_damage *= 0.65f;
                
                if (!pk::is_campaign())
                {
                    // 부대 간 전투 시 부대방향에 따른 데미지 보정 ('18.11.27)
                    if (교전방향설정)
                    {
                        int damage_dir = func_unit_direction(attacker, target_unit);
                        troops_damage = troops_damage * func_dir_weight(damage_dir);
                        
                        // 후방피격시 혼란효과 적용
                        if (후방피격시_혼란적용 and type == 0 and damage_dir == 3 and int(troops_damage) > 0)
                            @back_unit = target_unit;
                    }
                    
                    // 부대 간 전투 시 주변부대 영향력 추가 ('18.10.28)
                    if (주변부대설정)
                    {
                        troops_damage = troops_damage * (1.f + func_neighbor_buf(attacker, true)) * (1.f - func_neighbor_buf(target_unit, false));
                    }

                    // 부대 간 전투 시 병종별 지형 효과 추가 ('18.10.11)
                    if (지형효과설정)
                    {
                        troops_damage = troops_damage * (1.f + func_terrain_buf(attacker)) * (1.f - func_terrain_buf(target_unit)); //지형 유형
                        troops_damage = troops_damage * (1.f + 0.01f * get_height_diff(attacker.get_pos(), target_unit.get_pos())); //지형 높이차
                    }
                    
                    
                    // 부대간 교전 시 상호 기력 조건 반영됨 ('18.10.6)
                    if (사기효과설정)
                    {
                        // ㄴ공격부대 기력에 따라 피격부대 피해 85% ~ 115% 적용 : 부대 사기 효과 ('18.10.6)
                        troops_damage = troops_damage * (0.85f + 0.30f * (attacker.energy/120.f)) ;
                        // ㄴ피격부대 기력에 따라 피격부대 피해 85% ~ 115% 적용 : 부대 사기 효과 ('18.10.6)
                        troops_damage = troops_damage * (0.85f + 0.30f * ((120 - target_unit.energy)/120.f)) ;
                    }
                    
                    // 전체적인 기본 대미지량 조절 ('18.11.08)
                    troops_damage *= 대미지조절;
                }
                
                // 병력 피해량에 따라 피격대상 기력감소, 공격부대 기력상승 효과 발생, 반격도 적용됨 ('18.10.6)
                if (기력증감설정 and !pk::is_campaign())
                {
                    if (pk::is_enemy(attacker, target_unit))  // 서로 다른 세력인 부대간 교전 시에만 기력회복 : 동토 계략 시 기력회복 방지 ('18.10.22)
                    {
                        info.energy_heal = info.energy_heal + int(pk::min(5.f, (troops_damage / 200.f)));   //광역 전법데미지에 의한 기력 과도상승 리미터 적용
                    
                        if (troops_damage >= 500)
                        {
                            info.energy_damage = info.energy_damage + int((troops_damage - 500) / 100.f);
                        
                            if (target_unit.has_skill(특기_호위))  // 특기_호위 보유 부대는 병력피해 있어도 기력 감소 없음 ('18.10.14)
                                info.energy_damage = 0;
                        }
                    }
                    else    // 동토(아군끼리 교전) 시 기력회복 없고, 데미지량에 비례하여 기력 데미지 발생 ('18.10.25)
                    {
                        info.energy_damage = info.energy_damage + int(troops_damage / 100.f);
                    }
                }
                
				info.troops_damage = int(troops_damage);
                
                // 부대공격 실패 시 메시지 추가 ('19.2.17)
                if (type == 0 and info.troops_damage == 0 and !pk::is_campaign())
                {
                    @msg_unit = @attacker;
                    @msg_person = pk::get_person(attacker.leader);
                    msg_string = "공격이 통하지 않는가";
                }
                
                // 특기 발동 시 전법 유효 사거리 및 지형조건 확인, 초특기연전 전법사용 패치용 ('19.11.10)
                if (초특기연전_발동설정 and attacker.has_skill(특기_연전) and pk::is_valid_tactics_id(tactics_id) and !pk::is_campaign())
                {
                    if (pk::is_alive(target_unit) and !func_tactics_valid_target(attacker, target_unit, tactics_id))
                    {
                        info.critical = false;      // 통상공격
                        info.tactics_hit = false;   // 전법실패
                        info.troops_damage = 0;     // 데미지무효
                        info.energy_damage = 0;     // 데미지무효
                        info.food_damage = 0;       // 데미지무효
                        info.energy_heal = 0;       // 데미지무효
                        info.food_heal = 0;         // 데미지무효
                    }
                }
                
                //---------------------------------------------------------------------------------------
                
			}
            // 공성 공격 (병력)
			else if (target_building !is null and pk::is_general_type(target_building))
			{
				info.dst_troops = pk::get_troops(target_building);

				int facility_id = target_building.facility;
				int troops_atk, dst_atk, dst_def, dst_troops;
                
                // 농성 태수 능력치                
				func_5af0e0(troops_atk, dst_atk, dst_def, dst_troops, target_building);
				// 병력 피해량 기본
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
                    // 거점 병력 피해량 재설정
					troops_damage = func_5aee60(atk, int(pk::max(command * 0.75f, 1.f)), troops_atk, buffed, dst_def, dst_troops);
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
                    
                    // 불굴/금강 특기 장수가 성내에 있을 시 특기 발동하여 수성병력 피해 경감 ('18.10.9)
                    if (거점방어특기 and !pk::is_campaign())
                    {
                        int siege_type = 1;     // 1:공성 병력, 2:공성 내구도
                        int defskill_rate = 30;    // 확률 30%로 설정
                        if (func_citydef_skill(info, target_building, siege_type, defskill_rate) == 1)       // 0: 방어특기 없음, 1:불굴/금강, 2:철벽
                        {
                            troops_damage *= (defskill_rate/100.f);   // 피해 0 으로 설정 시 문제될 수 있음
                            
                            if (대화표시설정 and pk::is_player_controlled(attacker))
                            {
                                //pk::say(pk::encode("난공불락의 요새군"), pk::get_person(attacker.leader));
                                @msg_unit = @attacker;
                                @msg_person = pk::get_person(attacker.leader);
                                msg_string = "난공불락의 요새군";
                            }
                        }
                    }
                    
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
						if (target_unit.has_skill(특기_급습) and 
                            (pk::get_hex(target_unit.pos).terrain == 지형_숲 or pk::rand_bool(int(pk::core::skill_constant(target_unit, 특기_급습))) ) )
						{
							troops_damage = 0;
							info.def_skill = 특기_급습;
						}
					}
				}
                
                if(!pk::is_campaign())
                {
                    // 부대→건물 공격 시에만 반영됨, 건물 반격은 "건물의 공격 대미지.cpp" 수정해야 됨 ('18.10.7)
                    if (사기효과설정)
                    {
                        // ㄴ공격부대 기력에 따라 피격대상 피해 85% ~ 115% 적용 : 부대 사기 효과 ('18.10.6)
                        troops_damage = troops_damage * (0.85f + 0.30f * (attacker.energy/120.f)) ;
                        // ㄴ피격대상 기력에 따라 피격대상 피해 85% ~ 115% 적용 : 부대 사기 효과 ('18.10.6)
                        troops_damage = troops_damage * (0.85f + 0.30f * ((120 - target_building.energy)/120.f)) ;
                    }
                    
                    // 전체적인 대미지량 조절 ('18.11.08)
                    troops_damage *= 대미지조절;
                    
                    // 병력 피해량에 따라 피격대상 기력감소, 공격부대 기력상승 효과 발생, 건물반격 적용안됨 ('18.10.6)
                    if (기력증감설정)
                    {
                        info.energy_heal = int(pk::min(5.f, (troops_damage / 200.f)));      //광역 전법데미지에 의한 기력 과도상승 리미터 적용
                        if (troops_damage >= 200)
                            info.energy_damage = int((troops_damage - 200) / 100.f);
                    }
                }
                
				info.troops_damage = int(troops_damage);
                
			}
            // 공성 공격 (내구도 & 병력)
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
                
                // 병기별 내구도 데미지
				if (attacker.weapon == 병기_충차 or attacker.weapon == 병기_목수)
					hp_damage = func_5af050(atk, command, hp_atk, buffed);
				else
					hp_damage = func_5aeff0(atk, command, hp_atk, buffed);

                // 크리티컬
				if (info.critical)
					hp_damage *= 크리티컬_공격력;

                // 조건별 보정
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
				}
				else if (attacker.weapon != 병기_충차 and attacker.weapon != 병기_목수)
				{
					switch (facility_id)
					{
					case 시설_도시:
                    case 시설_관문:
                    case 시설_항구:
					case 시설_연노로:
					case 시설_토루:
						hp_damage *= 0.9f;
						break;
					case 시설_석벽:
						hp_damage *= 0.7f;
						break;
					case 시설_진:
						hp_damage *= 0.8f;
						break;
					case 시설_요새:
                        hp_damage *= 0.7f;
						break;
					case 시설_성채:
						hp_damage *= 0.6f;
						break;
					}
				}
                
                // 전투병과의 공성파쇄 데미지 보정 ('20.4.11)
                if (attacker.weapon <= 병기_군마 and tactics_id == 전법_공성파쇄)
                    hp_damage *= 0.3f;
                
                
                // 거점 방어세력 기교에 따라 거점의 병기공격에 대한 내구 데미지 보정 ('18.10.28)
                if (facility_id <= 시설_항구 and (attacker.weapon >= 병기_충차 and attacker.weapon <= 병기_목수) )
                {
                    if (target_building.has_tech(기교_성벽강화))
                        hp_damage *= 0.70f;
                    else if (target_building.has_tech(기교_시설강화))
                        hp_damage *= 0.85f;
                    else
                        hp_damage *= 1.00f;
                }
                    
                

				if (facility_id == 시설_제방 and not target_building.completed)
					hp_damage = 0;

				if (attacker.has_tech(기교_운제))
				{
					if (attacker.weapon >= 병기_검 and attacker.weapon <= 병기_군마)
					{
						info.troops_damage = int(info.troops_damage * 1.4f);
						hp_damage *= 1.4f;
					}
					else
					{
						info.troops_damage = int(info.troops_damage * 1.2f);
						hp_damage *= 1.2f;
					}
				}

				if (attacker.is_player())
					hp_damage *= float(pk::core["대미지패널티"][pk::get_scenario().difficulty]);
                
                if (!pk::is_campaign())
                {                    
                    // 철벽 특기 장수가 성내에 있을 시 특기 발동하여 내구도 피해 경감 ('18.10.11)
                    if (거점방어특기)
                    {
                        int siege_type = 2;     // 1:공성 병력, 2:공성 내구도
                        int defskill_rate = 30;    // 확률 30%로 설정
                        if (func_citydef_skill(info, target_building, siege_type, defskill_rate) == 2)       // 0: 방어특기 없음, 1:불굴/금강, 2:철벽
                        {
                            hp_damage *= (defskill_rate/100.f);   // 피해 0 으로 설정 시 밸런스 문제될 수 있음
                            
                            if (대화표시설정 and pk::is_player_controlled(attacker))
                            {
                                //pk::say(pk::encode("성벽이 튼튼한가"), pk::get_person(attacker.leader));
                                @msg_unit = @attacker;
                                @msg_person = pk::get_person(attacker.leader);
                                msg_string = "성벽이 튼튼한가";
                            }
                        }
                    }
                    
                    // 부대→건물 공격 시 내구도 피해량 가변 ('18.10.7)
                    if (사기효과설정)
                    {
                        // 공격부대 기력에 따라 피격대상 피해 85% ~ 115% 적용 : 부대 사기 효과 ('18.10.6)
                        hp_damage = hp_damage * (0.85f + 0.30f * (attacker.energy/120.f)) ;
                        // 피격대상 기력에 따라 피격대상 피해 85% ~ 115% 적용 : 부대 사기 효과 ('18.10.6)
                        hp_damage = hp_damage * (0.85f + 0.30f * ((120 - target_building.energy)/120.f)) ;
                    }
                    
                    // 전체적인 대미지량 조절 ('18.11.08)
                    hp_damage *= 대미지조절;
                }
                
				info.hp_damage = int(hp_damage);
			}		

			info.tactics = tactics_id;
			info.src_pos = attacker.get_pos();
			info.dst_pos = target_pos;
            
            
            // 나선첨혼란확률_강제적용('19.2.21)
            if (나선첨혼란확률_강제적용 and (tactics_id == 전법_나선첨) and info.tactics_hit and !pk::is_campaign())
            {
                @nasun_unit = @target_unit;
                나선첨_크리티컬 = info.critical;
                나선첨_피격행동 = target_unit.action_done;
                나선첨_피격상태 = target_unit.status;
                나선첨_피격타이머 = target_unit.status_timer;
            }
            
            
		}

		/**
			창병 병량습격 획득 병량 계산
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
            도시, 관문, 항구 검색 추가 ('18.10.28)
		*/
		bool func_5aedc0(const pk::point &in pos, int min, int max, int force_id)
		{
			array<pk::point> range = pk::range(pos, min, max);
			for (int i = 0; i < int(range.length); i++)
			{
				pk::building@ building = pk::get_building(range[i]);
				if (pk::is_alive(building) and (building.facility == 시설_진 or building.facility == 시설_요새 or building.facility == 시설_성채) and building.completed and building.get_force_id() == force_id)
					return true;
                
                if (거점방어버프)
                {
                    if (pk::is_alive(building) and (building.facility == 시설_도시 or building.facility == 시설_관문 or building.facility == 시설_항구) and building.get_force_id() == force_id)
                        return true;
                }
                
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

		/** 태수와 무장들에 의한 방어거점 전투능력 **/
        //도시 내 "신분_일반" 인 무장 능력 반영 (각 무장의 무력, 통솔, 지휘 부분 합산) ('18.10.7)
		void func_5af0e0(int &out src_atk, int &out dst_atk, int &out dst_def, int &out dst_troops, pk::building@ building)
		{
			src_atk = 10;
            
			pk::person@ taishu = pk::get_person(pk::get_taishu_id(building));
			if (pk::is_alive(taishu))
			{
                //태수 능력 반영 (기본)
				dst_atk = pk::max(taishu.stat[무장능력_무력] - 25, 40);
				dst_def = pk::max(taishu.stat[무장능력_통솔] - 25, 40);
				dst_troops = pk::min(pk::get_troops(building), pk::get_command(taishu));
                
                //도시 내 "신분_일반" 인 무장 능력 반영 (각 무장의 무력, 통솔, 지휘 부분 합산) ('18.10.7)
                if (거점능력합산)
                {
                    float ilban_support = 5;    // 태수 외 무장 능력 치 합산 보조율 : 무장별 5%
                    auto ilban_list = pk::list_to_array(pk::get_person_list(building, pk::mibun_flags(신분_일반) ) );
                    if (0 < ilban_list.length)
                    {
                        for (int i = 0; i < int(ilban_list.length); i++)
                        {
                            pk::person@ ilban = ilban_list[i];
                            //출진 또는 부재중 상태가 아닌 장수이며, 태수와 혐오 관계가 아닌 장수만 능력 치 합산
                            if (!pk::is_unitize(ilban) and !pk::is_absent(ilban) and !pk::is_dislike(taishu, ilban.get_id()) and !pk::is_dislike(ilban, taishu.get_id()) )
                            {
                                dst_atk += int((pk::max(ilban.stat[무장능력_무력] - 25, 20)) * (ilban_support / 100.f));
                                dst_def += int((pk::max(ilban.stat[무장능력_통솔] - 25, 20)) * (ilban_support / 100.f));
                                dst_troops += int((pk::min(pk::get_troops(building), pk::get_command(ilban))) * (ilban_support / 100.f));
                            }
                        }
                    }
                }
            }
			else
			{
				dst_atk = 30;
				dst_def = 30;
				//dst_troops = pk::min(pk::get_troops(building), 7000);
				dst_troops = pk::min(pk::get_troops(building), 5000); //지휘병력 상한치 하향
				if (dst_troops != 0)
					dst_troops = pk::max(dst_troops, 500);
			}
		}

		/** 도시 내구도 피해 계산 (기타) **/
		float func_5aeff0(int src_atk, int src_troops, int tactics_atk, int buffed)
		{
			src_troops = pk::max(src_troops, 1);
			float a = sqrt(src_atk * src_atk / 15.f);
			float b = sqrt(src_troops);
			float c = tactics_atk * 4 + 100;
			float d = buffed + 10;
			return a * b * c * d / 10000;
		}

		/** 도시 내구도 피해 계산 (충차/목수) **/
		float func_5af050(int src_atk, int src_troops, int tactics_atk, int buffed)
		{
			src_troops = pk::max(src_troops, 1);
			float a = sqrt(src_atk * src_atk / 15.f);
			float b = sqrt(src_troops);
			float c = tactics_atk * 4 + 100;
			float d = buffed + 10;
			return a * pk::min(b, 40.f) * c * d / 10000 + (src_troops / 25) + b;
		}

		/** 부대 방어기교 및 방어특기 효과 반영 **/
        // 방어특기 효과 기존에는 통상공격에만 적용, 전법공격에도 작용하도록 스크립트 수정
		bool func_5af230(pk::damage_info& info, pk::unit@ attacker, pk::unit@ target, int tactics_id)
		{
            // 전법여부 판정 부분 위로 스크립트 이동 : 통상공격/전법공격 구분 없이 방어 특기 발동 ('18.10.9)
            if (target.status == 부대상태_통상)
            {
                if (target.has_skill(특기_불굴))
                {
                    if (int(target.troops) < int(pk::core::skill_constant(target, 특기_불굴)) and pk::rand_bool(int(pk::core::skill_constant(target, 특기_불굴, 1))))
                    {
                        info.def_skill = 특기_불굴;
                        
                        if (pk::is_valid_tactics_id(tactics_id))
                            info.tactics_hit = false;
                        
                        return true;
                    }
                }
                float buf_rate = 1.f;
                if (target.has_skill(특기_금강))
                {
                    if (pk::is_valid_tactics_id(tactics_id))    // 공격자 전법인 경우 특기_발동 피해량 기준 x1.5배 적용
                        buf_rate = 1.5f;
                    
                    if (info.troops_damage < (int(pk::core::skill_constant(target, 특기_금강))*buf_rate) and pk::rand_bool(int(pk::core::skill_constant(target, 특기_금강, 1))))
                    {
                        info.def_skill = 특기_금강;
                        
                        if (pk::is_valid_tactics_id(tactics_id))
                            info.tactics_hit = false;

                        return true;
                    }
                }
                
                if (target.has_skill(특기_철벽))    // 철벽 특기 전법 30% 확률로 무효화 ('19.6.19)
                {
                    if (pk::is_valid_tactics_id(tactics_id) and pk::rand_bool(30))
                    {
                        info.def_skill = 특기_철벽;
                        info.tactics_hit = false;
                        
                        return true;
                    }
                }
            }
            
            // 방어특기 없을 경우 공격자 전법여부 확인 : 전법인 경우 false 반환 후 함수 종료, 평타인 경우 방어자 극병 기교효과 적용
            else if (!pk::is_valid_tactics_id(tactics_id))
            {
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
            }

			return false;
		}
        // --------------------------------------------------------
        
        // --------------------------------------------------------
        // 불굴/금강 특기 장수가 성내에 있을 시 특기 발동 ('18.10.9)
        int func_citydef_skill(pk::damage_info& info, pk::building@ building, int siege_type, int defskill_rate)
		{
            auto defender_list = pk::list_to_array(pk::get_person_list(building, pk::mibun_flags(신분_군주,신분_도독,신분_태수,신분_일반) ) );
            if (0 < defender_list.length)
            {
                for (int i = 0; i < int(defender_list.length); i++)
                {
                    pk::person@ defender = defender_list[i];
                    
                    //출진 또는 부재중 상태가 아닌 장수만 !!!!
                    if (!pk::is_unitize(defender) and !pk::is_absent(defender))
                    {
                        // 거점에 특기_불굴 장수 있을 경우 발동 ('18.10.9)
                        if ((siege_type == 1) and pk::has_skill(defender, 특기_불굴) and (building.troops < 3000) and pk::rand_bool(defskill_rate))
                            return 1;       // 병력 방어 효과

                        // 거점에 특기_금강 장수 있을 경우 발동 ('18.10.9)
                        if ((siege_type == 1) and pk::has_skill(defender, 특기_금강) and (info.troops_damage < 500) and pk::rand_bool(defskill_rate))
                            return 1;       // 병력 방어 효과
                        
                        // 거점에 특기_철벽 장수 있을 경우 발동 ('18.10.11)
                        if ((siege_type == 2) and pk::has_skill(defender, 특기_철벽) and pk::rand_bool(defskill_rate))
                            return 2;       // 내구도 방어 효과
                    }
                }
            }
            return 0;
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
                                if      (weapon_id == 병기_창)   terrain_buf = 0.05f;
                                else if (weapon_id == 병기_군마)  terrain_buf = 0.10f;
                                break;
                case 지형_땅  :    
                                if      (weapon_id == 병기_창)   terrain_buf = 0.05f;
                                else if (weapon_id == 병기_노)   terrain_buf = 0.05f;
                                else if (weapon_id == 병기_군마)  terrain_buf = 0.05f;
                                break;
                case 지형_모래  : 
                                if      (weapon_id == 병기_창)   terrain_buf = 0.05f;
                                else if (weapon_id == 병기_군마)  terrain_buf = 0.05f;
                                break;
                case 지형_습지  : 
                                if      (weapon_id == 병기_창)   terrain_buf = -0.05f;
                                else if (weapon_id == 병기_극)   terrain_buf = 0.10f;
                                else if (weapon_id == 병기_노)   terrain_buf = -0.05f;
                                else if (weapon_id == 병기_군마)  terrain_buf = -0.10f;
                                break;
                case 지형_독천  : 
                                if      (weapon_id == 병기_창)   terrain_buf = -0.10f;
                                else if (weapon_id == 병기_극)   terrain_buf = 0.05f;
                                else if (weapon_id == 병기_노)   terrain_buf = -0.10f;
                                else if (weapon_id == 병기_군마)  terrain_buf = -0.15f;
                                break;
                case 지형_숲   : 
                                if      (weapon_id == 병기_창)   terrain_buf = 0.10f;
                                else if (weapon_id == 병기_극)   terrain_buf = 0.05f;
                                else if (weapon_id == 병기_노)   terrain_buf = 0.15f;
                                else if (weapon_id == 병기_군마)  terrain_buf = -0.10f;
                                break;
                case 지형_황무지:  
                                if      (weapon_id == 병기_창)   terrain_buf = -0.05f;
                                else if (weapon_id == 병기_군마)  terrain_buf = 0.05f;
                                break;
                case 지형_대로  : 
                                if      (weapon_id == 병기_창)   terrain_buf = 0.05f;
                                else if (weapon_id == 병기_극)   terrain_buf = 0.05f;
                                else if (weapon_id == 병기_노)   terrain_buf = 0.05f;
                                else if (weapon_id == 병기_군마)  terrain_buf = 0.05f;
                                break;
                case 지형_산  : 
                                if      (weapon_id == 병기_창)   terrain_buf = 0.15f;
                                else if (weapon_id == 병기_극)   terrain_buf = 0.15f;
                                else if (weapon_id == 병기_노)   terrain_buf = 0.15f;
                                else if (weapon_id == 병기_군마)  terrain_buf = 0.10f;
                                break;
            }
            
            // 특기_매복 보유부대는 병종 관계없이 숲/산/샛길에서 15% 추가 어드밴티지 ('18.10.14)
            if (unit.has_skill(특기_매복) and (unit_hex.terrain == 지형_숲 or unit_hex.terrain == 지형_산 or unit_hex.terrain == 지형_샛길 ) )
                terrain_buf += 0.15f;
            // 특기_해독 보유부대는 병종 관계없이 독천에서 15% 추가 어드밴티지 ('18.10.17)
            else if (unit.has_skill(특기_해독) and (unit_hex.terrain == 지형_독천) )
                terrain_buf += 0.15f;
            // 특기_답파 보유부대는 병종 관계없이 벼랑길/산/샛길에서 15% 추가 어드밴티지 ('18.10.17)
            else if (unit.has_skill(특기_답파) and (unit_hex.terrain == 지형_벼랑길 or unit_hex.terrain == 지형_산 or unit_hex.terrain == 지형_샛길) )
                terrain_buf += 0.15f;
            
            return terrain_buf;
        }
        
        
        // 부대간 지형 높이차 ('18.10.14)
        int get_height_diff(const pk::point &in src, const pk::point &in dst)
		{
			return pk::get_height_map(pk::hex_pos_to_height_map_pos(src) + 2).height - pk::get_height_map(pk::hex_pos_to_height_map_pos(dst) + 2).height;
		}
        
        
        // --------------------------------------------------------
        // 부대 간 전투 시 주변 부대에 의한 데미지 보정 계수 ('18.10.28)
        float func_neighbor_buf(pk::unit @ unit, bool 개별대화)
        {
            float neighbor_buf = 0.f;
            int neighbor_range = 1;
            
            pk::point pos = unit.get_pos();
            
            array<pk::point> arr = pk::range(pos, 1, neighbor_range);
            for (int j = 0; j < int(arr.length); j++)
            {
                pk::unit@ search_unit = pk::get_unit(arr[j]);
                if (search_unit !is null and !pk::is_enemy(unit, search_unit))  // 주변부대가 아군인 경우
                {
                    // 아군부대장의 신분에 따른 버프 
                    if (search_unit.leader == pk::get_kunshu_id(unit))  // 아군부대가 군주이면 : 작위에 따라 버프량 및 대화 다르게 ('18.10.28)
                    {
                        switch (pk::get_force(unit.get_force_id()).title)
                        {
                        case 작위_황제:
                            neighbor_buf += 0.15f;   // 15% 버프
                            
                            if (대화표시설정 and 개별대화 and pk::is_player_controlled(unit))
                            {
                                //pk::say(pk::encode("폐하와 함께 하겠습니다"), pk::get_person(unit.leader));
                                @msg_unit = @unit;
                                @msg_person = pk::get_person(unit.leader);
                                msg_string = "폐하와 함께 하겠습니다";
                            }
                            break;
                            
                        case 작위_왕:
                            neighbor_buf += 0.10f;   // 10% 버프
                            
                            if (대화표시설정 and 개별대화 and pk::is_player_controlled(unit))
                            {
                                //pk::say(pk::encode("전하와 함께 하겠습니다"), pk::get_person(unit.leader));
                                @msg_unit = @unit;
                                @msg_person = pk::get_person(unit.leader);
                                msg_string = "전하와 함께 하겠습니다";
                            }
                            break;
                            
                        case 작위_공:
                            neighbor_buf += 0.05f;   // 5% 버프
                            
                            if (대화표시설정 and 개별대화 and pk::is_player_controlled(unit))
                            {
                                //pk::say(pk::encode("공과 함께 하겠소"), pk::get_person(unit.leader));
                                @msg_unit = @unit;
                                @msg_person = pk::get_person(unit.leader);
                                msg_string = "공과 함께 하겠습니다";
                            }
                            break;
                            
                        default:
                            neighbor_buf += 0.05f;   // 5% 버프
                            
                            if (대화표시설정 and 개별대화 and pk::is_player_controlled(unit))
                            {
                                //pk::say(pk::encode("주군과 함께 하겠소"), pk::get_person(unit.leader));
                                @msg_unit = @unit;
                                @msg_person = pk::get_person(unit.leader);
                                msg_string = "주군과 함께 하겠습니다";
                            }
                            break;
                        }
                    }
                    else if (search_unit.leader == pk::get_totoku_id(unit))  // 아군부대가 같은 군단 도독이면 ('18.10.28)
                    {
                        neighbor_buf += 0.05f;   // 5% 버프
                        
                        if (대화표시설정 and 개별대화 and pk::is_player_controlled(unit))
                        {
                            //pk::say(pk::encode("도독과 함께 한다"), pk::get_person(unit.leader));
                            @msg_unit = @unit;
                            @msg_person = pk::get_person(unit.leader);
                            msg_string = "도독과 함께 한다";
                        }
                    }                        
                    
                    
                    // 아군부대장의 특기에 따른 버프
                    if (search_unit.has_skill(특기_신산))  // 아군부대가 특기_신산 보유 시 버프 ('18.10.28)
                    {
                        neighbor_buf += 0.10f;   // 10% 버프
                        
                        if (대화표시설정 and 개별대화 and pk::is_player_controlled(unit))
                        {
                            //pk::say(pk::encode("신산진법을 발동하라"), pk::get_person(search_unit.leader));
                            @msg_unit = @unit;
                            @msg_person = pk::get_person(search_unit.leader);
                            msg_string = "신산진법을 발동하라";
                        }
                        
                    }
                    if (search_unit.has_skill(특기_허실))  // 아군부대가 특기_허실 보유 시 버프 ('18.10.28)
                    {
                        neighbor_buf += 0.05f;   // 5% 버프
                        
                        if (대화표시설정 and 개별대화 and pk::is_player_controlled(unit))
                        {
                            //pk::say(pk::encode("허허실실 전략을 펼쳐라"), pk::get_person(search_unit.leader));
                            @msg_unit = @unit;
                            @msg_person = pk::get_person(search_unit.leader);
                            msg_string = "허허실실 전략을 펼쳐라";
                        }
                    }
                    
                }
            }
                
            return neighbor_buf;
        }
        
        // --------------------------------------------------------
        // 전략 도시 보유 세력 여부 ('18.11.5)
        bool func_tactics_city(pk::unit@ attacker, int weapon_id)
        {
            int kunshu_id = pk::get_kunshu_id(attacker);
            switch (weapon_id)
            {
                case 병기_창:
                    if (kunshu_id == pk::get_kunshu_id(pk::get_building(도시_복양)))
                        return true;
                    else if (kunshu_id == pk::get_kunshu_id(pk::get_building(도시_완)))
                        return true;
                    break;
                    
                case 병기_극:
                    if (kunshu_id == pk::get_kunshu_id(pk::get_building(도시_운남)))
                        return true;
                    else if (kunshu_id == pk::get_kunshu_id(pk::get_building(도시_장사)))
                        return true;
                    break;
                    
                case 병기_노:
                    if (kunshu_id == pk::get_kunshu_id(pk::get_building(도시_강릉)))
                        return true;
                    else if (kunshu_id == pk::get_kunshu_id(pk::get_building(도시_회계)))
                        return true;
                    break;
                    
                case 병기_군마:
                    if (kunshu_id == pk::get_kunshu_id(pk::get_building(도시_양평)))
                        return true;
                    else if (kunshu_id == pk::get_kunshu_id(pk::get_building(도시_무위)))
                        return true;
                    break;
            }
            return false;
        }
        
        
        // --------------------------------------------------------
        // 부대 간 전투 시 피격부대 방향에 따른 대미지 보정 ('18.11.27)
        int func_unit_direction(pk::unit@ attacker, pk::unit@ target_unit)
        {
            int dir_unit = target_unit.direction;    // 피격부대의 현재방향
            int dir_atk = pk::get_direction(target_unit.pos, attacker.pos);  // 교전시 피격방향
            
            int damage_dir = -1;
            
            switch (dir_unit)
            {
                case 방향_북서:  
                    if      (dir_atk == 방향_북서)                      damage_dir = 0;   // 전면
                    else if (dir_atk == 방향_북 or dir_atk == 방향_남서)  damage_dir = 1;   // 전측
                    else if (dir_atk == 방향_북동 or dir_atk == 방향_남)  damage_dir = 2;   // 후측
                    else if (dir_atk == 방향_남동)                      damage_dir = 3;   // 후면
                    break;
                    
                case 방향_북 :  
                    if      (dir_atk == 방향_북)                        damage_dir = 0;   // 전면
                    else if (dir_atk == 방향_북서 or dir_atk == 방향_북동) damage_dir = 1;   // 전측 
                    else if (dir_atk == 방향_남서 or dir_atk == 방향_남동) damage_dir = 2;   // 후측 
                    else if (dir_atk == 방향_남)                        damage_dir = 3;   // 후면
                    break;
                    
                case 방향_북동: 
                    if      (dir_atk == 방향_북동)                      damage_dir = 0;   // 전면
                    else if (dir_atk == 방향_북 or dir_atk == 방향_남동)  damage_dir = 1;   // 전측
                    else if (dir_atk == 방향_북서 or dir_atk == 방향_남)  damage_dir = 2;   // 후측
                    else if (dir_atk == 방향_남서)                      damage_dir = 3;   // 후면
                    break;
                    
                case 방향_남서:  
                    if      (dir_atk == 방향_남서)                      damage_dir = 0;   // 전면   
                    else if (dir_atk == 방향_북서 or dir_atk == 방향_남)  damage_dir = 1;   // 전측
                    else if (dir_atk == 방향_북 or dir_atk == 방향_남동)  damage_dir = 2;   // 후측
                    else if (dir_atk == 방향_북동)                      damage_dir = 3;   // 후면
                    break;
                    
                case 방향_남 :
                    if      (dir_atk == 방향_남)                        damage_dir = 0;   // 전면
                    else if (dir_atk == 방향_남서 or dir_atk == 방향_남동) damage_dir = 1;   // 전측
                    else if (dir_atk == 방향_북서 or dir_atk == 방향_북동) damage_dir = 2;   // 후측
                    else if (dir_atk == 방향_북)                        damage_dir = 3;   // 후면
                    break;
                    
                case 방향_남동:  
                    if      (dir_atk == 방향_남동)                      damage_dir = 0;   // 전면
                    else if (dir_atk == 방향_남 or dir_atk == 방향_북동)  damage_dir = 1;   // 전측
                    else if (dir_atk == 방향_남서 or dir_atk == 방향_북)  damage_dir = 2;   // 후측
                    else if (dir_atk == 방향_북서)                      damage_dir = 3;   // 후면
                    break;
                    
            }
            
            return damage_dir;
            
        }
        
        // 가중치 반환함수와 방향반환 함수로 분리 ('19.2.26)
        float func_dir_weight(int damage_dir)
        {
            float 방향가중치_전면 = 0.95f;
            float 방향가중치_전측 = 1.00f;
            float 방향가중치_후측 = 1.05f;
            float 방향가중치_후면 = 1.10f;
            
            float damage_buf = 1.f;
            
            switch (damage_dir)
            {
                case 0: damage_buf = 방향가중치_전면; break;  // 전면 대미지 가중치
                case 1: damage_buf = 방향가중치_전측; break;  // 전측 대미지 가중치
                case 2: damage_buf = 방향가중치_후측; break;  // 후측 대미지 가중치
                case 3: damage_buf = 방향가중치_후면; break;  // 후면 대미지 가중치
            }
            
            return damage_buf;
        }
        
        //------------------------------------------------------------------------------------------
        // 전법 발동 시 사거리/지형 유효 조건인지 확인 ('19.11.10)
        bool func_tactics_valid_target(pk::unit@ attacker, pk::unit@ target_unit, int tactics_id)
        {
            int combat_range = pk::get_distance(attacker.pos, target_unit.pos);
            int terrain_id = pk::get_hex(target_unit.pos).terrain;
            
            pk::tactics@ tactics_t = pk::get_tactics(tactics_id);
            int  max_range = tactics_t.max_range;
            int  min_range = tactics_t.min_range;
            if (max_range == 1 and combat_range > max_range) return false;
            /*
            bool terrain_valid;
            if (terrain_id == 지형_숲 and attacker.has_skill(특기_사수) 
                and ((전법_화시 <= tactics_id and tactics_id <= 전법_난사) or tactics_id == 전법_공성화시 or tactics_id == 전법_함선화시))
                terrain_valid = true;
            else
                terrain_valid = tactics_t.terrain[terrain_id];
            if (!terrain_valid) return false;
            */
            return true;
        }
        
        //------------------------------------------------------------------------------------------
        // AI부대 전법 변경 함수 ('19.11.21)
        int func_dir_tactics_opt(pk::unit@ attacker, pk::unit@ target_unit, int tactics_id)
        {
            int tactics_opt = tactics_id;   // 기본값은 입력값
            if (!pk::is_alive(target_unit)) return tactics_id;
            if (attacker.weapon > 병기_군마 or attacker.weapon == 병기_노) return tactics_id;
            if (pk::get_current_turn_force_id() != attacker.get_force_id()) return tactics_id;
            
            int atk_dist = pk::get_distance(attacker.pos, target_unit.pos); // 교전거리
            int atk_dir = pk::get_direction(attacker.pos, target_unit.pos); // 공격방향
            int def_dir = pk::get_direction(target_unit.pos, attacker.pos); // 피격방향
            
            pk::point pos_b1 = pk::get_neighbor_pos(attacker.pos, def_dir, 1);
            pk::point pos_n1 = pk::get_neighbor_pos(target_unit.pos, atk_dir, 1);
            pk::point pos_n2 = pk::get_neighbor_pos(target_unit.pos, atk_dir, 2);
            
            pk::unit@ unit_n1 = (pk::is_valid_pos(pos_n1))? pk::get_unit(pos_n1) : null;
            pk::unit@ unit_n2 = (pk::is_valid_pos(pos_n2))? pk::get_unit(pos_n2) : null;
            bool enemy_n1 = (pk::is_alive(unit_n1))? pk::is_enemy(attacker, unit_n1) : false;
            bool enemy_n2 = (pk::is_alive(unit_n2))? pk::is_enemy(attacker, unit_n2) : false;
            
            pk::hex@ hex_n1 = (pk::is_valid_pos(pos_n1))? pk::get_hex(pos_n1) : null;
            pk::hex@ hex_n2 = (pk::is_valid_pos(pos_n2))? pk::get_hex(pos_n2) : null;
            bool empty_n1 = (hex_n1 !is null)? (!hex_n1.has_unit and !hex_n1.has_building) : false;
            bool empty_n2 = (hex_n2 !is null)? (!hex_n2.has_unit and !hex_n2.has_building) : false;
            
            bool fire_n0 = pk::is_on_fire(target_unit.pos);
            bool fire_n1 = (pk::is_valid_pos(pos_n1))? pk::is_on_fire(pos_n1) : false;
            bool fire_n2 = (pk::is_valid_pos(pos_n2))? pk::is_on_fire(pos_n2) : false;
            bool fire_b1 = (pk::is_valid_pos(pos_b1))? pk::is_on_fire(pos_b1) : false;
            
            if (pk::is_valid_tactics_id(tactics_id) and (atk_dist == 1))    // 근접공격, 통상/일제공격 제외
            {
                //----- 창병 전법 (나선첨, 이단첨, 돌출)
                // 전법_나선첨 조건 확인 (전법사용가능, 기력충족, 근접, 대상부대가 통상상태)
                if (check_tactics_enable(attacker, target_unit, 전법_나선첨) and target_unit.status == 부대상태_통상)
                    tactics_opt = 전법_나선첨;
                
                // 전법_이단첨 조건 확인 (전법사용가능, 기력충족, 근접, 충돌대상부대 유효)
                else if (check_tactics_enable(attacker, target_unit, 전법_이단첨) and empty_n1 and (enemy_n2 or fire_n2))
                    tactics_opt = 전법_이단첨;
                
                // 전법_돌출 조건 확인 (전법사용가능, 기력충족, 근접, 충돌대상부대 유효)
                else if (check_tactics_enable(attacker, target_unit, 전법_돌출) and (empty_n1 or enemy_n1 or fire_n1))
                    tactics_opt = 전법_돌출;
                
                //----- 기병 전법 (돌파, 돌진, 돌격)
                // 전법_돌파 조건 확인 (전법사용가능, 기력충족, 근접, 돌파후 위치 빈칸)
                else if (check_tactics_enable(attacker, target_unit, 전법_돌파) and empty_n1 and !enemy_n2 and !fire_n1)
                    tactics_opt = 전법_돌파;
                
                // 전법_돌진 조건 확인 (전법사용가능, 기력충족, 근접, 돌진후 위치 빈칸)
                else if (check_tactics_enable(attacker, target_unit, 전법_돌진) and empty_n1 and !fire_n1 and (empty_n2 or fire_n2))
                    tactics_opt = 전법_돌진;
                
                // 전법_돌격 조건 확인 (전법사용가능, 기력충족, 근접)
                else if (check_tactics_enable(attacker, target_unit, 전법_돌격) and !fire_n0)
                    tactics_opt = 전법_돌격;
                
                //----- 극병 전법 (횡치, 선풍, 갈퀴)
                // 전법_횡치 조건 확인 (전법사용가능, 기력충족, 근접, 인접한 적부대 확인)
                else if (check_tactics_enable(attacker, target_unit, 전법_횡치) and (count_neighbor_enemies(attacker, target_unit, 전법_횡치) >= 1))
                    tactics_opt = 전법_횡치;

                // 전법_선풍 조건 확인 (전법사용가능, 기력충족, 근접, 인접한 적부대 확인)
                else if (check_tactics_enable(attacker, target_unit, 전법_선풍) and (count_neighbor_enemies(attacker, target_unit, 전법_선풍) >= 3))
                    tactics_opt = 전법_선풍;
                
                // 전법_갈퀴 조건 확인 (전법사용가능, 기력충족, 근접)
                else if (check_tactics_enable(attacker, target_unit, 전법_갈퀴) and !fire_b1)
                    tactics_opt = 전법_갈퀴;
                
            }
            
            // 로그창에 표시
            if (디버그모드 and (tactics_id != tactics_opt))
            {
                string leader_name = pk::decode(pk::get_name(pk::get_person(attacker.leader)));
                pk::info(pk::format("{}부대전법: {} → {}", leader_name, get_tactics_name(tactics_id), get_tactics_name(tactics_opt)));
            }
            
            return tactics_opt;
        }
        
        // 노병 통상활공격 → 화시 최적화
        int func_fire_on_arrow(pk::unit@ attacker, pk::hex_object@ target_obj, int tactics_id)
        {
            int tactics_opt = tactics_id;   // 기본값은 입력값
            if (!pk::is_alive(target_obj)) return tactics_id;
            if (attacker.weapon != 병기_노) return tactics_id;
            if (pk::get_current_turn_force_id() != attacker.get_force_id()) return tactics_id;
            int atk_dist = pk::get_distance(attacker.pos, target_obj.pos); // 교전거리
            
            if (atk_dist > 1 and !pk::is_valid_tactics_id(tactics_id))
            {
                int tekisei = pk::get_tekisei(attacker, attacker.weapon);
                pk::equipment@ atk_eqp  = pk::get_equipment(attacker.weapon);
                pk::tactics@ fire_arrow = pk::get_tactics(전법_화시);
                pk::hex@ hex_dst = pk::get_hex(target_obj.pos);
                
                // 화시전법사용가능여부 : 병과, 기력, 적성, 지형 체크
                bool chk_eqp = atk_eqp.tactics[전법_화시];
                bool chk_tekisei = tekisei >= fire_arrow.tekisei;
                bool chk_energy = (attacker.energy >= fire_arrow.energy_cost);
                bool chk_range = (fire_arrow.min_range <= atk_dist and atk_dist <= fire_arrow.max_range);
                bool chk_terrain = fire_arrow.terrain[hex_dst.terrain];
                if (chk_eqp and chk_tekisei and chk_energy and chk_range and chk_terrain)
                    tactics_opt = 전법_화시;
            }            
            return tactics_opt;
        }
        
        
        bool check_tactics_enable(pk::unit@ src, pk::unit@ dst, int tactics_id)
        {
            bool tactics_en = false;
            int tekisei = pk::get_tekisei(src, src.weapon);
            pk::equipment@ atk_eqp  = pk::get_equipment(src.weapon);
            pk::tactics@ tactics = pk::get_tactics(tactics_id);
            pk::hex@ hex_dst = pk::get_hex(dst.pos);
            
            // 전법사용가능여부 : 병과, 기력, 적성, 지형 체크
            tactics_en = (atk_eqp.tactics[tactics_id] and (src.energy >= tactics.energy_cost) and (tekisei >= tactics.tekisei) and tactics.terrain[hex_dst.terrain]);
                
            return tactics_en;
        }
        
        int count_neighbor_enemies(pk::unit@ src, pk::unit@ dst, int tactics_id)
        {
            int count = 0;
            for (int i = 0; i < 방향_끝; i++)
            {
                pk::point pos_t = pk::get_neighbor_pos(src.pos, i);
                pk::unit@ unit_t = (pk::is_valid_pos(pos_t))? pk::get_unit(pos_t) : null;
                if (pk::is_valid_pos(pos_t) and pk::is_alive(unit_t) and pk::is_enemy(src, unit_t) and unit_t.get_id() != dst.get_id())
                {
                    if (tactics_id == 전법_횡치 and pk::get_distance(dst.pos, unit_t.pos) == 1)
                        count++;
                    else if (tactics_id == 전법_선풍)
                        count++;
                }
            }
            return count;
        }

        bool check_splash_valid(pk::unit@ src, pk::unit@ dst)
        {
            int count_force = 0;
            int count_enemy = 0;
            for (int i = 0; i < 방향_끝; i++)
            {
                pk::point pos_t = pk::get_neighbor_pos(dst.pos, i);
                pk::unit@ unit_t = (pk::is_valid_pos(pos_t))? pk::get_unit(pos_t) : null;
                pk::hex@ hex_t = pk::get_hex(pos_t);
                if (pk::is_valid_pos(pos_t) and pk::is_alive(unit_t) and unit_t.get_id() != dst.get_id())
                {
                    if (!pk::is_enemy(src, unit_t)) count_force++;
                    if ( pk::is_enemy(src, unit_t)) 
                    {
                        if (hex_t.terrain != 지형_숲) count_enemy++;
                        if (hex_t.terrain == 지형_숲 and src.has_skill(특기_사수)) count_enemy++;
                    }
                }
            }
            if (count_enemy >= pk::max(2, (count_force + 1))) return true;
            return false;
        }
        
        string get_tactics_name(int tactics_id)
        {
            pk::array<string> str_tactics = {"돌출", "나선첨", "이단첨", "갈퀴", "횡치", "선풍", "화시", "관시", "난사", "돌격", "돌파", "돌진", "공성화시", "공성파쇄", "공성방사", "공성투석", "함선화시", "함선격돌", "함선투석"};
            if (tactics_id < 0 or tactics_id >= 전법_끝) return "통상";
            return str_tactics[tactics_id];
        }
        
        //------------------------------------------------------------------------------------------
        // 부대 경험치 획득 시 추가처리 
        //------------------------------------------------------------------------------------------
        
        // 전용 메시지 처리용 변수
        pk::unit@   msg_unit;
        pk::person@ msg_person;
        string      msg_string = "";
        
        // 나선첨 처리용 변수
        pk::unit@ unit;
        pk::unit@ nasun_unit;
        bool 나선첨_크리티컬;  // 나선첨 성공 시 크리티컬 정보
        bool 나선첨_피격행동;  // 나선첨 피격부대의 행동완료 정보
        int  나선첨_피격상태;  // 나선첨 피격부대의 부대상태 정보
        int  나선첨_피격타이머;  // 나선첨 피격부대의 부대상태 타이머
        
        // 후방피격 혼란처리용 변수
        pk::unit@ back_unit;
        
        
        // 경험치 획득 시 처리 함수
        void onUnitExpAdd(pk::unit@ unit, int type)
        {
            // 커스텀 대화표시
            if (대화표시설정 and pk::is_alive(unit) and pk::is_alive(msg_unit) and unit.get_id() == msg_unit.get_id())
            {
                pk::say(pk::encode(msg_string), msg_person);
            }
            @msg_unit = null;
            @msg_person = null;
            msg_string = "";
            
            // 나선첨혼란확률_강제적용
            if (나선첨혼란확률_강제적용 and pk::is_alive(unit) and pk::is_alive(nasun_unit))
            {
                pk::person@ def_leader = pk::get_person(nasun_unit.leader);
                int 나선첨혼란확률 = (나선첨_크리티컬)? 나선첨_크리티컬혼란확률 : 나선첨_전법성공혼란확률;
                int 나선첨혼란시간 = (나선첨_크리티컬)? 2 : 1;
                
                if (pk::rand_bool(나선첨혼란확률))
                {
                    pk::set_status(nasun_unit, unit, 부대상태_혼란, 나선첨혼란시간, true);
                }
                else
                {
                    pk::set_status(nasun_unit, unit, 나선첨_피격상태, 나선첨_피격타이머, false);  // 혼란상태를 강제로 피격 당시 부대상태로 변경
                    nasun_unit.action_done = 나선첨_피격행동;                       // 피격 당시 행동상태로 재설정
                    
                    if (나선첨_피격상태 == 부대상태_통상)
                        pk::say(pk::encode("다행히 부대혼란은 면했군"), def_leader);
                }
            }
            @nasun_unit = null;
            나선첨_크리티컬 = false;
            
            // 후방피격 혼란처리
            if (교전방향설정 and 후방피격시_혼란적용 and pk::is_alive(unit) and pk::is_alive(back_unit))
            {
                if (pk::rand_bool(후방피격시_혼란확률) and back_unit.status == 부대상태_통상)
                {
                    pk::set_status(back_unit, unit, 부대상태_혼란, 1, true);
                    pk::say(pk::encode("훗. 후방 교란에 성공했군.."), pk::get_person(unit.leader));
                }
            }
            @back_unit = null;
            
        }
        //------------------------------------------------------------------------------------------
        
        bool 디버그모드 = false;
        
	}

	Main main;
}


