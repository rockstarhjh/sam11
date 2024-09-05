/*
@만든이: 기마책사
@Update: '19.11.26  / 최초적용: 특기 설명을 pk2.1 특기.xml 세팅값에 맞춰서 표기
@Update: '19.12.5   / 변경적용: 무장.xml 설정값 반영안되도록 수정

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
            
            id_sel = set_person_skill(특기_강행);
            if (id_sel >= 0) 
            {
                val1 = int(pk::core::skill_constant(id_sel, 특기_강행, 0));
                pk::get_skill(특기_강행).desc = pk::u8encode(pk::format("병기, 수송 부대를 제외한 육상부대 이동력 \x1b[23x+{}\x1b[0x", val1) );
            }            
            id_sel = set_person_skill(특기_행군);
            if (id_sel >= 0) 
            {
                val1 = int(pk::core::skill_constant(id_sel, 특기_행군, 0));
                pk::get_skill(특기_행군).desc = pk::u8encode(pk::format("기병 부대 이동력 \x1b[23x+{}\x1b[0x", val1) );
            }            
            id_sel = set_person_skill(특기_조타);
            if (id_sel >= 0)
            {
                val1 = int(pk::core::skill_constant(id_sel, 특기_조타, 0));
                pk::get_skill(특기_조타).desc = pk::u8encode(pk::format("수상에서 이동력 \x1b[23x+{}\x1b[0x", val1) );
            }
            
            id_sel = set_person_skill(특기_운반);
            if (id_sel >= 0) 
            {
                val1 = int(pk::core::skill_constant(id_sel, 특기_운반, 0));
                pk::get_skill(특기_운반).desc = pk::u8encode(pk::format("수송 부대 이동력 \x1b[23x+{}\x1b[0x", val1) );
            }
            
            id_sel = set_person_skill(특기_소탕);
            if (id_sel >= 0) 
            {
                val1 = int(pk::core::skill_constant(id_sel, 특기_소탕, 0));
                pk::get_skill(특기_소탕).desc = pk::u8encode(pk::format("공격한 적부대 기력 \x1b[22x-{}\x1b[0x", val1) );
            }
            
            id_sel = set_person_skill(특기_위풍);
            if (id_sel >= 0) 
            {
                val1 = int(pk::core::skill_constant(id_sel, 특기_위풍, 0));
                pk::get_skill(특기_위풍).desc = pk::u8encode(pk::format("공격한 적부대 기력 \x1b[22x-{}\x1b[0x", val1) );
            }
            
            id_sel = set_person_skill(특기_앙양);
            if (id_sel >= 0) 
            {
                val1 = int(pk::core::skill_constant(id_sel, 특기_앙양, 0));
                pk::get_skill(특기_앙양).desc = pk::u8encode(pk::format("적부대 격파시 기력 \x1b[23x+{}\x1b[0x", val1) );
            }
            
            id_sel = set_person_skill(특기_연전);
            if (id_sel >= 0) 
            {
                val1 = pk::min(100, pk::max(0, int(pk::core::skill_constant(id_sel, 특기_연전, 0))));
                pk::get_skill(특기_연전).desc = pk::u8encode(pk::format("공격할 때 \x1b[23x{}%\x1b[0x의 확률로 1번 더 공격", val1) );
            }
            
            id_sel = set_person_skill(특기_급습);
            if (id_sel >= 0) 
            {
                val1 = pk::min(100, pk::max(0, int(pk::core::skill_constant(id_sel, 특기_급습, 0))));
                pk::get_skill(특기_급습).desc = pk::u8encode(pk::format("육상에서 공격시 \x1b[23x{}%\x1b[0x의 확률로 피해를 받지 않음", val1) );
            }
            
            id_sel = set_person_skill(특기_강습);
            if (id_sel >= 0) 
            {
                val1 = pk::min(100, pk::max(0, int(pk::core::skill_constant(id_sel, 특기_강습, 0))));
                pk::get_skill(특기_강습).desc = pk::u8encode(pk::format("수상에서 공격시 \x1b[23x{}%\x1b[0x의 확률로 피해를 받지 않음", val1) );
            }
            
            id_sel = set_person_skill(특기_기각);
            if (id_sel >= 0) 
            {   
                val1 = pk::min(100, pk::max(0, int(pk::core::skill_constant(id_sel, 특기_기각, 0))));
                pk::get_skill(특기_기각).desc = pk::u8encode(pk::format("일제공격시 상대를 \x1b[23x{}%\x1b[0x의 확률로 혼란", val1) );
            }
            
            id_sel = set_person_skill(특기_포박);
            if (id_sel >= 0) 
            {
                val1 = pk::min(100, pk::max(0, int(pk::core::skill_constant(id_sel, 특기_포박, 0))));
                pk::get_skill(특기_포박).desc = pk::u8encode(pk::format("적부대 격파시 적장을 \x1b[23x{}%\x1b[0x의 확률로 포획", val1) );
            }
            
            id_sel = set_person_skill(특기_강탈);
            if (id_sel >= 0) 
            {
                val1 = pk::min(100, pk::max(0, int(pk::core::skill_constant(id_sel, 특기_강탈, 0))));
                pk::get_skill(특기_강탈).desc = pk::u8encode(pk::format("적부대 격파시 \x1b[23x{}%\x1b[0x의 확률로 보물 탈취", val1) );
            }
            
            id_sel = set_person_skill(특기_심공);
            if (id_sel >= 0) 
            {
                rate = pk::min(100.f, pk::max(0.f, float(pk::core::skill_constant(id_sel, 특기_심공, 0))));
                val1 = int(100.f * rate);
                pk::get_skill(특기_심공).desc = pk::u8encode(pk::format("공격시 적부대 피해병력의 \x1b[23x{}%\x1b[0x를 자신의 부대에 흡수", val1) );
            }
            
            id_sel = set_person_skill(특기_불굴);
            if (id_sel >= 0) 
            {
                val1 = int(pk::core::skill_constant(id_sel, 특기_불굴, 0));
                val2 = pk::min(100, pk::max(0, int(pk::core::skill_constant(id_sel, 특기_불굴, 1))));
                pk::get_skill(특기_불굴).desc = pk::u8encode(pk::format("병력 \x1b[23x{}\x1b[0x 미만시 공격을 {}% 확률로 회피. 수성시 우세", val1, val2) );
            }
            
            id_sel = set_person_skill(특기_금강);
            if (id_sel >= 0) 
            {
                val1 = int(pk::core::skill_constant(id_sel, 특기_금강, 0));
                val2 = pk::min(100, pk::max(0, int(pk::core::skill_constant(id_sel, 특기_금강, 1))));
                pk::get_skill(특기_금강).desc = pk::u8encode(pk::format("받은 피해가 \x1b[23x{}\x1b[0x 미만시 {}% 확률로 회피. 수성시 우세", val1, val2) );
            }
            
            id_sel = set_person_skill(특기_노발);
            if (id_sel >= 0) 
            {
                val1 = pk::min(100, pk::max(0, int(pk::core::skill_constant(id_sel, 특기_노발, 0))));
                pk::get_skill(특기_노발).desc = pk::u8encode(pk::format("전법으로 공격받았을 때 기력 \x1b[23x+{}\x1b[0x 회복", val1) );
            }
            
            id_sel = set_person_skill(특기_질주);
            if (id_sel >= 0) 
            {
                val1 = pk::min(100, pk::max(0, int(pk::core::skill_constant(id_sel, 특기_질주, 0))));
                pk::get_skill(특기_질주).desc = pk::u8encode(pk::format("무력 우위시 기병전법 \x1b[23x{}%\x1b[0x 혼란", val1) );
            }
            
            id_sel = set_person_skill(특기_맹장);
            if (id_sel >= 0)
            {
                val1 = pk::min(100, pk::max(0, int(pk::core::skill_constant(id_sel, 특기_맹장, 0))));
                pk::get_skill(특기_맹장).desc = pk::u8encode(pk::format("전법으로 적부대를 이동시키면 \x1b[23x{}%\x1b[0x 확률로 적장이 부상", val1) );
            }
            
            id_sel = set_person_skill(특기_주악);
            if (id_sel >= 0) 
            {
                val1 = int(pk::core::skill_constant(id_sel, 특기_주악, 0));
                pk::get_skill(특기_주악).desc = pk::u8encode(pk::format("매턴 자신의 부대나 거점의 기력 \x1b[23x+{}\x1b[0x", val1) );
            }
            
            id_sel = set_person_skill(특기_논객);
            if (id_sel >= 0)
            {
                val1 = pk::min(100, pk::max(0, int(pk::core::skill_constant(id_sel, 특기_논객, pk::get_scenario().difficulty))));
                pk::get_skill(특기_논객).desc = pk::u8encode(pk::format("동맹, 정전협정, 포로교환 실패시 난이도에 따른 확률로 설전발생", val1) );
            }
            
            id_sel = set_person_skill(특기_내조);
            if (id_sel >= 0)
            {
                val1 = pk::min(100, pk::max(0, int(pk::core::skill_constant(id_sel, 특기_내조, 0))));
                pk::get_skill(특기_내조).desc = pk::u8encode(pk::format("부부의 능력치가 \x1b[23x+{}\x1b[0x 증가. 한 부대에 편성시 경험치 추가상승", val1) );
            }
            
			pk::get_skill(특기_비장).desc = pk::u8encode("육상의 적부대 사이를 돌파. 무력 우위시 적중한 전법 크리티컬");
			pk::get_skill(특기_도주).desc = pk::u8encode("육상의 적부대 사이를 돌파");
			// pk::get_skill(특기_강행).desc = pk::u8encode("");
			// pk::get_skill(특기_행군).desc = pk::u8encode("");
			pk::get_skill(특기_추진).desc = pk::u8encode("수상에서 적부대 사이를 돌파");
			// pk::get_skill(특기_조타).desc = pk::u8encode("");
			pk::get_skill(특기_답파).desc = pk::u8encode("벼랑길 이동시 피해 없음. 함정 피해 경감. 험지와 독천에서 우세");
			// pk::get_skill(특기_운반).desc = pk::u8encode("");
			pk::get_skill(특기_해독).desc = pk::u8encode("독천의 피해 없음. 활로 공격시 독화살 사용. 독천에서 우세");	
			// pk::get_skill(특기_소탕).desc = pk::u8encode("");
			// pk::get_skill(특기_위풍).desc = pk::u8encode("");
			// pk::get_skill(특기_앙양).desc = pk::u8encode("");
			// pk::get_skill(특기_연전).desc = pk::u8encode("");
			// pk::get_skill(특기_급습).desc = pk::u8encode("");
			// pk::get_skill(특기_강습).desc = pk::u8encode("");
			pk::get_skill(특기_난전).desc = pk::u8encode("숲에서 공격시 크리티컬");
			pk::get_skill(특기_매복).desc = pk::u8encode("복병 사용시 기력 경감, 성공시 크리티컬. 험지에서 우세");
			pk::get_skill(특기_공성).desc = pk::u8encode("거점, 시설, 건설물에 전법 공격시 크리티컬");
			// pk::get_skill(특기_기각).desc = pk::u8encode("");
			// pk::get_skill(특기_포박).desc = pk::u8encode("");
			pk::get_skill(특기_정묘).desc = pk::u8encode("전법성공률 \x1b[23x+10%\x1b[0x. 계략 소모기력 -3. 적부대 격파시 기교 2배");
			// pk::get_skill(특기_강탈).desc = pk::u8encode("");
			// pk::get_skill(특기_심공).desc = pk::u8encode("");
			pk::get_skill(특기_구축).desc = pk::u8encode("무력 우위시 통상 공격 크리티컬");
			pk::get_skill(특기_사정).desc = pk::u8encode("정란, 투석의 사정거리 \x1b[23x+1칸\x1b[0x");
			pk::get_skill(특기_백마).desc = pk::u8encode("기사연구없이 기사 가능. 기사시 추가 피해량, 크리티컬");
			pk::get_skill(특기_보좌).desc = pk::u8encode("아군부대 공격시 \x1b[23x30%\x1b[0x 확률로 지원. 단, 혐오무장은 제외");
			// pk::get_skill(특기_불굴).desc = pk::u8encode("");
			// pk::get_skill(특기_금강).desc = pk::u8encode("");)
			pk::get_skill(특기_철벽).desc = pk::u8encode("적의 일제공격을 파훼. \x1b[23x30%\x1b[0x 확률로 전법 파훼. 수성시 우세");
			// pk::get_skill(특기_노발).desc = pk::u8encode("");
			pk::get_skill(특기_등갑).desc = pk::u8encode("피해 \x1b[23x-50%\x1b[0x. 불로 인한 피해 \x1b[22x+100%\x1b[0x");
			pk::get_skill(특기_강운).desc = pk::u8encode("전법이 대부분 성공. 전사나 포박, 부상을 당하지 않음");
			pk::get_skill(특기_혈로).desc = pk::u8encode("부대가 궤멸되어도 동료 무장은 포로가 되지 않음");
			pk::get_skill(특기_창장).desc = pk::u8encode("무력 우위시 적중한 창병 전법 크리티컬");
			pk::get_skill(특기_극장).desc = pk::u8encode("무력 우위시 적중한 극병 전법 크리티컬");
			pk::get_skill(특기_궁장).desc = pk::u8encode("무력 우위시 적중한 노병 전법 크리티컬");
			pk::get_skill(특기_기장).desc = pk::u8encode("무력 우위시 적중한 기병 전법 크리티컬");
			pk::get_skill(특기_수장).desc = pk::u8encode("무력 우위시 적중한 수군 전법 크리티컬");
			pk::get_skill(특기_용장).desc = pk::u8encode("무력 우위시 적중한 모든 전법 크리티컬");
			pk::get_skill(특기_신장).desc = pk::u8encode("무력 우위시 지상에서 통상 공격 및 적중한 전법 크리티컬");
			pk::get_skill(특기_투신).desc = pk::u8encode("창병 전법과 극병 전법 크리티컬");
			pk::get_skill(특기_창신).desc = pk::u8encode("적중한 창병 전법 크리티컬");
			pk::get_skill(특기_극신).desc = pk::u8encode("적중한 극병 전법 크리티컬");
			pk::get_skill(특기_궁신).desc = pk::u8encode("적중한 노병 전법 크리티컬. 난사시 아군 부대 피해없음");
			pk::get_skill(특기_기신).desc = pk::u8encode("적중한 기병 전법 크리티컬");
			pk::get_skill(특기_공신).desc = pk::u8encode("적중한 병기 전법 크리티컬");
			pk::get_skill(특기_수신).desc = pk::u8encode("적중한 수군 전법 크리티컬");
			pk::get_skill(특기_패왕).desc = pk::u8encode("적중한 모든 전법 크리티컬");
			// pk::get_skill(특기_질주).desc = pk::u8encode("");
			pk::get_skill(특기_사수).desc = pk::u8encode("노병으로 숲에 통상 공격 및 전법 사용가능");
			// pk::get_skill(특기_맹장).desc = pk::u8encode("");
			pk::get_skill(특기_호위).desc = pk::u8encode("동료 무장이 전사나 부상당하지 않음. 전투로 인한 기력소모 감소");
			pk::get_skill(특기_화공).desc = pk::u8encode("지력 우위시 화계 항상 성공 및 피해 반감. 소모기력 \x1b[23x-50%\x1b[0x");
			pk::get_skill(특기_언독).desc = pk::u8encode("지력 우위시 위보 항상 성공. 소모기력 \x1b[23x-50%\x1b[0x");
			pk::get_skill(특기_기략).desc = pk::u8encode("지력 우위시 교란 항상 성공. 소모기력 \x1b[23x-50%\x1b[0x");
			pk::get_skill(특기_궤계).desc = pk::u8encode("지력 우위시 동토 항상 성공. 소모기력 \x1b[23x-50%\x1b[0x");
			pk::get_skill(특기_허실).desc = pk::u8encode("지력 우위시 계략 항상 성공");
			pk::get_skill(특기_묘계).desc = pk::u8encode("지력 우위시 적중한 계략 크리티컬");
			pk::get_skill(특기_비책).desc = pk::u8encode("지력 열세시 적중한 계략 크리티컬. 계략 소모기력 \x1b[23x-5\x1b[0x");
			pk::get_skill(특기_간파).desc = pk::u8encode("지력 우위시 적의 계략 간파"); 
			pk::get_skill(특기_통찰).desc = pk::u8encode("적의 모든 계략 간파. \x1b[23x50%\x1b[0x 확률로 적의 전법 파훼");
			pk::get_skill(특기_화신).desc = pk::u8encode("지력 우위시 화계 성공, 피해 증가. 소모기력 \x1b[23x-50%\x1b[0x. 불에 우대");
			pk::get_skill(특기_신산).desc = pk::u8encode("지력 우위시 모든 계략이 성공하고 크리티컬. 계략에 우대");
			pk::get_skill(특기_백출).desc = pk::u8encode("모든 계략 소모기력 \x1b[23x-50%\x1b[0x");
			pk::get_skill(특기_귀모).desc = pk::u8encode("계략 사용범위 \x1b[23x+1칸\x1b[0x");
			pk::get_skill(특기_연환).desc = pk::u8encode("적중한 계략이 대상의 인접 부대에도 계략이 파급");
			pk::get_skill(특기_심모).desc = pk::u8encode("적중한 계략 크리티컬");
			pk::get_skill(특기_반계).desc = pk::u8encode("간파한 계략과 같은 계략을 상대에게 되돌림");
			pk::get_skill(특기_경국).desc = pk::u8encode("여성이 없는 부대에 부대 계략 성공률 \x1b[23x2배\x1b[0x");
			pk::get_skill(특기_요술).desc = pk::u8encode("계략 요술을 사용가능");
			pk::get_skill(특기_귀문).desc = pk::u8encode("계략 요술, 낙뢰를 사용가능");
			pk::get_skill(특기_규율).desc = pk::u8encode("계략 위보를 간파. 진정 소모기력 \x1b[23x-50%\x1b[0x");
			pk::get_skill(특기_침착).desc = pk::u8encode("계략 교란을 간파. 진정 소모기력 \x1b[23x-50%\x1b[0x");
			pk::get_skill(특기_명경).desc = pk::u8encode("계략 위보, 교란을 간파. 진정 소모기력 \x1b[23x-50%\x1b[0x");
			// pk::get_skill(특기_주악).desc = pk::u8encode("");
			pk::get_skill(특기_시상).desc = pk::u8encode("군악대 회복 기력 +\x1b[23x100%\x1b[0x");
			pk::get_skill(특기_축성).desc = pk::u8encode("군사 시설 내구도 상승량 +\x1b[23x100\x1b[0x%. 매턴 소속거점 내구도 회복");
			pk::get_skill(특기_둔전).desc = pk::u8encode("관문, 항구 소속시 병량소모 없음. 출전 부대의 병량소모 -\x1b[23x50\x1b[0x%");
			pk::get_skill(특기_명성).desc = pk::u8encode("징병으로 모집하는 병사가 늘어나고, 매분기 소속거점 병사 증가");
			pk::get_skill(특기_능리).desc = pk::u8encode("창, 극, 노 병기의 생산량이 증가");
			pk::get_skill(특기_번식).desc = pk::u8encode("군마의 생산량이 증가");
			pk::get_skill(특기_발명).desc = pk::u8encode("병기의 생산 기간이 \x1b[23x2배\x1b[0x 단축");
			pk::get_skill(특기_조선).desc = pk::u8encode("함선의 생산 기간이 \x1b[23x2배\x1b[0x 단축");
			pk::get_skill(특기_지도).desc = pk::u8encode("소속부대 획득 경험치 증가. 기교 연구시 필요 비용이 \x1b[23x-50%\x1b[0x");
			pk::get_skill(특기_안력).desc = pk::u8encode("발견하지 못한 재야의 인재를 항상 발굴");
			// pk::get_skill(특기_논객).desc = pk::u8encode("");
			pk::get_skill(특기_부호).desc = pk::u8encode("소속도시 금 수입 \x1b[23x+50%\x1b[0x");
			pk::get_skill(특기_미도).desc = pk::u8encode("소속도시 병량 수입 \x1b[23x+50%\x1b[0x");
			pk::get_skill(특기_징세).desc = pk::u8encode("소속도시 금수입 매턴 발생. 금수입 \x1b[22x-50%\x1b[0x");
			pk::get_skill(특기_징수).desc = pk::u8encode("소속도시 병량수입 매분기 발생. 병량수입 \x1b[22x-50%\x1b[0x");
			pk::get_skill(특기_친오).desc = pk::u8encode("소속영내 오환족 침략없음. 기병 출전시 공격력 \x1b[23x+15%\x1b[0x");
			pk::get_skill(특기_친강).desc = pk::u8encode("소속영내 강족 침략없음. 기병 출전시 공격력 \x1b[23x+15%\x1b[0x");
			pk::get_skill(특기_친월).desc = pk::u8encode("소속영내 산월족 침략없음. 극병 출전시 공격력 \x1b[23x+15%\x1b[0x");
			pk::get_skill(특기_친만).desc = pk::u8encode("소속영내 남만족 침략없음. 극병 출전시 공격력 \x1b[23x+15%\x1b[0x");
			pk::get_skill(특기_위압).desc = pk::u8encode("소속영내 도적, 이민족 침략감소. 창병 출전시 공격력 \x1b[23x+15%\x1b[0x");
			pk::get_skill(특기_인정).desc = pk::u8encode("소속도시 다른 무장의 충성도가 하락하지 않음");
			pk::get_skill(특기_풍수).desc = pk::u8encode("소속도시 메뚜기 떼, 역병이 발생하지 않음");
			pk::get_skill(특기_기원).desc = pk::u8encode("소속도시 풍작 확률 증가");			
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
                pk::get_skill(특기_논객).desc = pk::u8encode(pk::format("동맹, 정전협정, 포로교환 실패시 \x1b[23x{}%\x1b[0x의 확률로 설전발생", val1) );
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

