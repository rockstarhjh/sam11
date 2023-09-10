/*
@만든이: 기마책사
@Update: '19.11.26  / 최초적용: 특기 설명을 pk2.1 특기.xml 세팅값에 맞춰서 표기
@Update: '19.12.5   / 변경적용: 무장.xml 설정값 반영안되도록 수정

에보니 패치에서 특기 종합패치에 맞게 설명 수정 / unno
*/

namespace 설명수정특기_Ebony
{
	class Main
	{
        
        Main()
		{
            pk::bind(100, pk::trigger100_t(onGameTitle));   // 특기 설명 수정을 위해 추가
			pk::bind(102, pk::trigger102_t(onGameInit));   // 논객은 난이도마다 확률이 다르므로 따로 지정
        }
        
        //---------------------------------------------------------------------------------------
        
        void onGameTitle()
        {
            backup_person_skill();

            change_pk_skill_desc();  // 특기 설명 수정
            
            reset_person_skill();
        }
        void onGameInit()
        {
            backup_person_skill2();
            
            change_pk_skill_desc2();  // 특기 설명 수정
            
            reset_person_skill2();
        }		
        
        //---------------------------------------------------------------------------------------
        // pk2.1 특기.xml 설정값을 특기 설명에 반영

        void change_pk_skill_desc()
        {
            int id_sel;
            int val1;
            int val2;
            float rate;
            
	pk::get_skill(특기_비장).desc = pk::u8encode("지상에서 \x1b[20xＺＯＣ\x1b[0x 무시、적보다 무력이 높으면 전법 크리티컬");
	pk::get_skill(특기_도주).desc = pk::u8encode("지상에서 \x1b[20xＺＯＣ\x1b[0x 무시");

            id_sel = set_person_skill(특기_강행);
            if (id_sel >= 0) 
            {
                val1 = int(pk::core::skill_constant(id_sel, 특기_강행, 0));
                pk::get_skill(특기_강행).desc = pk::u8encode(pk::format("지상에서 이동력 \x1b[23x{}\x1b[0x、거점 아군은 \x1b[23x2\x1b[0x 증가", val1) );
            }
            
            id_sel = set_person_skill(특기_행군);
            if (id_sel >= 0) 
            {
                val1 = int(pk::core::skill_constant(id_sel, 특기_행군, 0));
                pk::get_skill(특기_행군).desc = pk::u8encode(pk::format("기병 부대의 이동력 \x1b[23x{}\x1b[0x 증가", val1) );
            }
            
	pk::get_skill(특기_추진).desc = pk::u8encode("수상에서 \x1b[20xＺＯＣ\x1b[0x 무시");

            id_sel = set_person_skill(특기_조타);
            if (id_sel >= 0)
            {
                val1 = int(pk::core::skill_constant(id_sel, 특기_조타, 0));
                pk::get_skill(특기_조타).desc = pk::u8encode(pk::format("수상에서 이동력 \x1b[23x{}\x1b[0x 증가", val1) );
            }
            
	pk::get_skill(특기_답파).desc = pk::u8encode("잔도 통행시 피해 없음(낙석、투석、불함정 피해 감소)");

            id_sel = set_person_skill(특기_운반);
            if (id_sel >= 0) 
            {
                val1 = int(pk::core::skill_constant(id_sel, 특기_운반, 0));
                pk::get_skill(특기_운반).desc = pk::u8encode(pk::format("수송 부대의 이동력 \x1b[23x{}\x1b[0x 증가", val1) );
            }
            
	pk::get_skill(특기_해독).desc = pk::u8encode("독천 통행시 피해 없음");

            id_sel = set_person_skill(특기_소탕);
            if (id_sel >= 0) 
            {
                val1 = int(pk::core::skill_constant(id_sel, 특기_소탕, 0));
                pk::get_skill(특기_소탕).desc = pk::u8encode(pk::format("공격시 적부대의 기력 \x1b[22x{}\x1b[0x 감소、모두 소진시 피해 증가", val1) );
            }
            
            id_sel = set_person_skill(특기_위풍);
            if (id_sel >= 0) 
            {
                val1 = int(pk::core::skill_constant(id_sel, 특기_위풍, 0));
                pk::get_skill(특기_위풍).desc = pk::u8encode(pk::format("공격시 적부대의 기력 \x1b[22x{}\x1b[0x 감소、모두 소진시 피해 증가", val1) );
            }
            
            id_sel = set_person_skill(특기_앙양);
            if (id_sel >= 0) 
            {
                val1 = int(pk::core::skill_constant(id_sel, 특기_앙양, 0));
                pk::get_skill(특기_앙양).desc = pk::u8encode(pk::format("적부대 격파시 기력 \x1b[23x{}\x1b[0x、전법 성공시 \x1b[23x5\x1b[0x 회복", val1) );
            }
            
            id_sel = set_person_skill(특기_연전);
            if (id_sel >= 0) 
            {
                val1 = pk::min(100, pk::max(0, int(pk::core::skill_constant(id_sel, 특기_연전, 0))));
                pk::get_skill(특기_연전).desc = pk::u8encode(pk::format("일반 공격시 \x1b[21x{}％\x1b[0x 확률로 추가 공격", val1) );
            }
            
            id_sel = set_person_skill(특기_급습);
            if (id_sel >= 0) 
            {
                val1 = pk::min(100, pk::max(0, int(pk::core::skill_constant(id_sel, 특기_급습, 0))));
                pk::get_skill(특기_급습).desc = pk::u8encode(pk::format("지상에서 \x1b[21x{}％\x1b[0x 확률로 무반격、상태이상 부대에 추가 피해", val1) );
            }
            
            id_sel = set_person_skill(특기_강습);
            if (id_sel >= 0) 
            {
                val1 = pk::min(100, pk::max(0, int(pk::core::skill_constant(id_sel, 특기_강습, 0))));
                pk::get_skill(특기_강습).desc = pk::u8encode(pk::format("수상에서 \x1b[21x{}％\x1b[0x 확률로 무반격、상태이상 부대에 추가 피해", val1) );
            }
            
	pk::get_skill(특기_난전).desc = pk::u8encode("숲에서 공격시 크리티컬");
	pk::get_skill(특기_공성).desc = pk::u8encode("거점、시설물 공격시 크리티컬");

            id_sel = set_person_skill(특기_기각);
            if (id_sel >= 0) 
            {   
                val1 = pk::min(100, pk::max(0, int(pk::core::skill_constant(id_sel, 특기_기각, 0))));
                pk::get_skill(특기_기각).desc = pk::u8encode(pk::format("일제 공격시 \x1b[21x{}％\x1b[0x 확률로 적을 교란", val1) );
            }
            
            id_sel = set_person_skill(특기_포박);
            if (id_sel >= 0) 
            {
                val1 = pk::min(100, pk::max(0, int(pk::core::skill_constant(id_sel, 특기_포박, 0))));
                pk::get_skill(특기_포박).desc = pk::u8encode(pk::format("적부대 격파시 통솔、무력이 더 높으면 \x1b[21x{}％\x1b[0x 확률로 포박", val1) );
            }
            
	pk::get_skill(특기_정묘).desc = pk::u8encode("적부대 격파시 기교 점수 추가、전법 성공률 \x1b[21x10％\x1b[0x 증가");

            id_sel = set_person_skill(특기_강탈);
            if (id_sel >= 0) 
            {
                val1 = pk::min(100, pk::max(0, int(pk::core::skill_constant(id_sel, 특기_강탈, 0))));
                pk::get_skill(특기_강탈).desc = pk::u8encode(pk::format("적부대 격파시 \x1b[21x{}％\x1b[0x 확률로 보물 탈취", val1) );
            }
            
            id_sel = set_person_skill(특기_심공);
            if (id_sel >= 0) 
            {
                rate = pk::min(100.f, pk::max(0.f, float(pk::core::skill_constant(id_sel, 특기_심공, 0))));
                val1 = int(100.f * rate);
                pk::get_skill(특기_심공).desc = pk::u8encode(pk::format("적부대에 입힌 피해의 \x1b[21x{}％\x1b[0x를 자부대로 흡수", val1) );
            }

	pk::get_skill(특기_구축).desc = pk::u8encode("일반 공격시 크리티컬");
	pk::get_skill(특기_사정).desc = pk::u8encode("정란、투석의 사거리 한 칸 증가");
	pk::get_skill(특기_백마).desc = pk::u8encode("기병 부대가 크리티컬 사격 가능");
	pk::get_skill(특기_보좌).desc = pk::u8encode("지원공격과 부대능력 기여에서 인간 관계가 향상");
	pk::get_skill(특기_창장).desc = pk::u8encode("적보다 무력이 높으면 창병 전법 크리티컬");
	pk::get_skill(특기_극장).desc = pk::u8encode("적보다 무력이 높으면 극병 전법 크리티컬");
	pk::get_skill(특기_궁장).desc = pk::u8encode("적보다 무력이 높으면 궁병 전법 크리티컬");
	pk::get_skill(특기_기장).desc = pk::u8encode("적보다 무력이 높으면 기병 전법 크리티컬");
	pk::get_skill(특기_수장).desc = pk::u8encode("적보다 무력이 높으면 수군 전법 크리티컬");
	pk::get_skill(특기_용장).desc = pk::u8encode("적보다 무력이 높으면 모든 전법 크리티컬");
	pk::get_skill(특기_신장).desc = pk::u8encode("적보다 무력이 높으면 일반 공격과 지상 전법 크리티컬");
	pk::get_skill(특기_투신).desc = pk::u8encode("창병 전법과 극병 전법 크리티컬");
	pk::get_skill(특기_창신).desc = pk::u8encode("창병 전법 크리티컬");
	pk::get_skill(특기_극신).desc = pk::u8encode("극병 전법 크리티컬");
	pk::get_skill(특기_궁신).desc = pk::u8encode("궁병 전법 크리티컬");
	pk::get_skill(특기_기신).desc = pk::u8encode("기병 전법 크리티컬");
	pk::get_skill(특기_공신).desc = pk::u8encode("병기 전법 크리티컬");
	pk::get_skill(특기_수신).desc = pk::u8encode("수군 전법 크리티컬");
	pk::get_skill(특기_패왕).desc = pk::u8encode("모든 전법 크리티컬");
            
            id_sel = set_person_skill(특기_질주);
            if (id_sel >= 0) 
            {
                val1 = pk::min(100, pk::max(0, int(pk::core::skill_constant(id_sel, 특기_질주, 0))));
                pk::get_skill(특기_질주).desc = pk::u8encode(pk::format("적보다 공격력이 높으면 기병 전법으로 적을 \x1b[21x{}％\x1b[0x 교란", val1) );
            }

	pk::get_skill(특기_사수).desc = pk::u8encode("숲으로 적을 사격 가능");

            id_sel = set_person_skill(특기_맹장);
            if (id_sel >= 0)
            {
                val1 = pk::min(100, pk::max(0, int(pk::core::skill_constant(id_sel, 특기_맹장, 0))));
                pk::get_skill(특기_맹장).desc = pk::u8encode(pk::format("적부대를 전법으로 이동시키면 무장을 \x1b[21x{}％\x1b[0x 확률로 부상", val1) );
            }

            id_sel = set_person_skill(특기_불굴);
            if (id_sel >= 0) 
            {
                val1 = int(pk::core::skill_constant(id_sel, 특기_불굴, 0));
                val2 = pk::min(100, pk::max(0, int(pk::core::skill_constant(id_sel, 특기_불굴, 1))));
                pk::get_skill(특기_불굴).desc = pk::u8encode(pk::format("병력이 \x1b[23x{}\x1b[0x 미만시 \x1b[21x{}％\x1b[0x 확률로 일반 공격을 막음", val1, val2) );
            }
            
            id_sel = set_person_skill(특기_금강);
            if (id_sel >= 0) 
            {
                val1 = int(pk::core::skill_constant(id_sel, 특기_금강, 0));
                val2 = pk::min(100, pk::max(0, int(pk::core::skill_constant(id_sel, 특기_금강, 1))));
                pk::get_skill(특기_금강).desc = pk::u8encode(pk::format("피해량이 \x1b[23x{}\x1b[0x 미만시 \x1b[21x{}％\x1b[0x 확률로 일반 공격을 막음", val1, val2) );
            }
            
	pk::get_skill(특기_철벽).desc = pk::u8encode("일제 공격을 당하지 않음、요새 주변에서 방어력 증가");

            id_sel = set_person_skill(특기_노발);
            if (id_sel >= 0) 
            {
                val1 = pk::min(100, pk::max(0, int(pk::core::skill_constant(id_sel, 특기_노발, 0))));
                pk::get_skill(특기_노발).desc = pk::u8encode(pk::format("전법 피격시 기력 \x1b[23x{}\x1b[0x、전법 실패시 \x1b[23x10\x1b[0x 회복", val1) );
            }
            
	pk::get_skill(특기_등갑).desc = pk::u8encode("불을 제외한 모든 피해를 반감、불 피해를 \x1b[22x2\x1b[0x 배로 받음");
	pk::get_skill(특기_강운).desc = pk::u8encode("전사、포박、부상을 당하지 않음");
	pk::get_skill(특기_혈로).desc = pk::u8encode("부대의 무장이 포박을 당하지 않음");
	pk::get_skill(특기_호위).desc = pk::u8encode("부대의 무장이 전사、부상을 당하지 않음");
	pk::get_skill(특기_매복).desc = pk::u8encode("적보다 지력이 높으면\x1b[19x「복병」\x1b[0x을 반드시 성공");
	pk::get_skill(특기_화공).desc = pk::u8encode("적보다 지력이 높으면\x1b[19x「화계」\x1b[0x를 반드시 성공、불 피해 증가");
	pk::get_skill(특기_언독).desc = pk::u8encode("적보다 지력이 높으면\x1b[19x「위보」\x1b[0x를 반드시 성공");
	pk::get_skill(특기_기략).desc = pk::u8encode("적보다 지력이 높으면\x1b[19x「교란」\x1b[0x을 반드시 성공");
	pk::get_skill(특기_궤계).desc = pk::u8encode("적보다 지력이 높으면\x1b[19x「동토」\x1b[0x를 반드시 성공");
	pk::get_skill(특기_허실).desc = pk::u8encode("적보다 지력이 높으면 모든 계략을 반드시 성공");
	pk::get_skill(특기_묘계).desc = pk::u8encode("자신과 먼 부대에 모든 계략 성공시 크리티컬");
	pk::get_skill(특기_비책).desc = pk::u8encode("자신과 가까운 부대에 모든 계략 성공시 크리티컬");
	pk::get_skill(특기_간파).desc = pk::u8encode("적보다 지력이 높으면 모든 계략 간파、적의 계략 성공률 반감");
	pk::get_skill(특기_통찰).desc = pk::u8encode("적의 계략에 당하지 않음");
	pk::get_skill(특기_화신).desc = pk::u8encode("적보다 지력이 높으면\x1b[19x「화계」\x1b[0x를 반드시 성공、불에 우대");
	pk::get_skill(특기_신산).desc = pk::u8encode("적보다 지력이 높으면 모든 계략을 반드시 성공、계략에 우대");
	pk::get_skill(특기_백출).desc = pk::u8encode("계략의 소비 기력이 \x1b[23x1\x1b[0x 로 감소");
	pk::get_skill(특기_귀모).desc = pk::u8encode("계략 범위 한 칸 증가、먼 부대에 계략 성공률 \x1b[23x2\x1b[0x 배");
	pk::get_skill(특기_연환).desc = pk::u8encode("계략 성공시 옆 칸에 반복、가까운 부대에 계략 성공률 \x1b[23x2\x1b[0x 배");
	pk::get_skill(특기_심모).desc = pk::u8encode("모든 계략 성공시 크리티컬");
	pk::get_skill(특기_반계).desc = pk::u8encode("간파한 계략을 반사、적의 계략 특기를 무시(통찰 제외)");
	pk::get_skill(특기_경국).desc = pk::u8encode("여성 무장이 없는 부대에 계략 성공률 \x1b[23x2\x1b[0x 배、지원공격 유도");
	pk::get_skill(특기_요술).desc = pk::u8encode("\x1b[19x「요술」\x1b[0x실행 가능");
	pk::get_skill(특기_귀문).desc = pk::u8encode("\x1b[19x「요술、낙뢰」\x1b[0x실행 가능");
	pk::get_skill(특기_규율).desc = pk::u8encode("\x1b[19x「위보、동토」\x1b[0x에 당하지 않음");
	pk::get_skill(특기_침착).desc = pk::u8encode("\x1b[19x「교란、복병」\x1b[0x에 당하지 않음");
	pk::get_skill(특기_명경).desc = pk::u8encode("\x1b[19x「위보、교란」\x1b[0x에 당하지 않음");
            
            id_sel = set_person_skill(특기_주악);
            if (id_sel >= 0) 
            {
                val1 = int(pk::core::skill_constant(id_sel, 특기_주악, 0));
                pk::get_skill(특기_주악).desc = pk::u8encode(pk::format("매 차례 자부대 기력 \x1b[23x{}\x1b[0x 회복", val1) );
            }
            
	pk::get_skill(특기_시상).desc = pk::u8encode("군악대에서 기력을 \x1b[23x2\x1b[0x 배 회복");
	pk::get_skill(특기_축성).desc = pk::u8encode("군사시설 건설 속도 \x1b[23x2\x1b[0x 배");
	pk::get_skill(특기_둔전).desc = pk::u8encode("거점에서 병사 \x1b[23x３\x1b[0x만(관、항구는 모두)의 병량 소모를 절감");
	pk::get_skill(특기_명성).desc = pk::u8encode("징병 모집량 \x1b[21x50％\x1b[0x 증가");
	pk::get_skill(특기_능리).desc = pk::u8encode("창、극、노 생산량 \x1b[21x100％\x1b[0x 증가");
	pk::get_skill(특기_번식).desc = pk::u8encode("군마 생산량 \x1b[21x100％\x1b[0x 증가");
	pk::get_skill(특기_발명).desc = pk::u8encode("공성병기 생산 기간 반감");
	pk::get_skill(특기_조선).desc = pk::u8encode("함선 생산 기간 반감");
	pk::get_skill(특기_지도).desc = pk::u8encode("기교 연구시 금 비용 반감");
	pk::get_skill(특기_안력).desc = pk::u8encode("인재 탐색시 재야 무장을 반드시 발견");
	pk::get_skill(특기_논객).desc = pk::u8encode("동맹 협정시 지력、정치 최대가 군사보다 높으면 반드시 설전");

/*
            id_sel = set_person_skill(특기_논객);
            if (id_sel >= 0)
            {
                val1 = pk::min(100, pk::max(0, int(pk::core::skill_constant(id_sel, 특기_논객, pk::get_scenario().difficulty))));
                pk::get_skill(특기_논객).desc = pk::u8encode(pk::format("동맹,정전협정,포로교환시 \x1b[18x{}％\x1b[0x의 확률로 설전을 이끔", val1) );
            }
*/            

	pk::get_skill(특기_부호).desc = pk::u8encode("도시의 금 수입 \x1b[21x50％\x1b[0x 증가");
	pk::get_skill(특기_미도).desc = pk::u8encode("도시의 병량 수입 \x1b[21x50％\x1b[0x 증가");
	pk::get_skill(특기_징세).desc = pk::u8encode("도시의 금 수입 \x1b[22x50％\x1b[0x 감소、매 차례 수입 발생");
	pk::get_skill(특기_징수).desc = pk::u8encode("도시의 병량 수입 \x1b[22x50％\x1b[0x 감소、매 월 수입 발생");
	pk::get_skill(특기_친오).desc = pk::u8encode("「양평、북평、계」에서\x1b[24x「오환」\x1b[0x출현과 계절 치안 하락 없음");
	pk::get_skill(특기_친강).desc = pk::u8encode("「무위、안정、천수」에서\x1b[24x「강」\x1b[0x출현과 계절 치안 하락 없음");
	pk::get_skill(특기_친월).desc = pk::u8encode("「회계、오、시상」에서\x1b[24x「산월」\x1b[0x출현과 계절 치안 하락 없음");
	pk::get_skill(특기_친만).desc = pk::u8encode("「운남、건녕、강주」에서\x1b[24x「남만」\x1b[0x출현과 계절 치안 하락 없음");
	pk::get_skill(특기_위압).desc = pk::u8encode("거점 치안이 \x1b[23x70\x1b[0x 이하로 내려가지 않음(계략、재해 제외)");
	pk::get_skill(특기_인정).desc = pk::u8encode("거점 무장의 충성도가 내려가지 않음");
	pk::get_skill(특기_풍수).desc = pk::u8encode("거점에서 메뚜기、역병이 발생하지 않음");
	pk::get_skill(특기_기원).desc = pk::u8encode("거점에서 풍작이 자주 일어남");

            id_sel = set_person_skill(특기_내조);
            if (id_sel >= 0)
            {
                val1 = pk::min(100, pk::max(0, int(pk::core::skill_constant(id_sel, 특기_내조, 0))));
                pk::get_skill(특기_내조).desc = pk::u8encode(pk::format("결혼하면 자신과 배우자의 모든 능력치 \x1b[23x{}\x1b[0x 증가", val1) );
            }

        }

        //---------------------------------------------------------------------------------------
        // pk2.1 특기.xml 설정값을 특기 설명에 반영2
        void change_pk_skill_desc2()
        {
            int id_sel;
            int val1;
            int val2;
            float rate;
			
            id_sel = set_person_skill(특기_논객);
            if (id_sel >= 0)
            {
                val1 = pk::min(100, pk::max(0, int(pk::core::skill_constant(id_sel, 특기_논객, pk::get_scenario().difficulty))));
                pk::get_skill(특기_논객).desc = pk::u8encode(pk::format("동맹 협정시 지력、정치 상한이 군사보다 높으면 반드시 설전", val1) );
            }			
            

        }
                
        //-----------------------------------
        // 특기를 가진 무장 검색 (미사용)
        int find_person_skill(int skill_id)
        {
            int person_id = -1;
            for (int i = 0; i <= 무장_노식; i++)
            {
                pk::person@ person = pk::get_person(i);
                if (person !is null and person.skill == skill_id)
                {
                    person_id = i;
                    break;
                }
            }
            return person_id;
        }
        
        //-----------------------------------
        int skill_id_backup;
        int person_id_t = 무장_무관;
                
        // NPC 무장 특기 임의 지정
        int set_person_skill(int skill_id)
        {
            pk::person@ person = pk::get_person(person_id_t);
            if (person !is null) person.skill = skill_id;
            return person_id_t;
        }
        
        // NPC 무장 특기 백업
        void backup_person_skill()
        {
            pk::person@ person = pk::get_person(person_id_t);
            if (person !is null) skill_id_backup = person.skill;
            return;
        }
        
        // NPC 무장 특기 삭제
        void reset_person_skill()
        {
            pk::person@ person = pk::get_person(person_id_t);
            if (person !is null) person.skill = skill_id_backup;
            return;
        }
        
		// NPC 무장 특기 백업2
        void backup_person_skill2()
        {
            pk::person@ person = pk::get_person(person_id_t);
            if (person !is null) skill_id_backup = person.skill;
            return;
        }
        
        // NPC 무장 특기 삭제2
        void reset_person_skill2()
        {
            pk::person@ person = pk::get_person(person_id_t);
            if (person !is null) person.skill = skill_id_backup;
            return;
        }		
    }
    
	Main main;
}

