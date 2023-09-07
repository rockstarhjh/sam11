/*   
@ 제작자: HoneyBee / 수정 : MUSSO
@ 내용: 기존세력 및 신세력을 배치(재배치)할 수 있는 SCRIPT    

@ HoneyBee님의 스크립트를 에보니 패키지 신무장에 맞게 일부 수정하였습니다.

*/


namespace 세력배치_설정
{
	
	
	// ================ CUSTOMIZE ================
			
			
		/// *** 세력 배치를 원하지 않는 세력은 false로 지정하시면 됩니다. ***	
		const bool 유방_활성화 = true;    // 전한
		const bool 항적_활성화 = true;    // 서초
		const bool 히미코_활성화 = true;   // 왜
		const bool 철리길_활성화 = true;   // 서강
		const bool 구력거_활성화 = true;   // 오환
		const bool 어부라_활성화 = true;   // 흉노
		const bool 가비능_활성화 = true;   // 선비
		const bool 영정_활성화 = true;   // 전국칠웅 [진]
		const bool 조옹_활성화 = true;   // 전국칠웅 [조]
		const bool 희평_활성화 = true;   // 전국칠웅 [연]
		const bool 전인제_활성화 = true;   // 전국칠웅 [제]
		const bool 웅의_활성화 = true;   // 전국칠웅 [초]
		const bool 한무_활성화 = true;   // 전국칠웅 [한]
		const bool 위앵_활성화 = true;   // 전국칠웅 [위]
		const bool 악비_활성화 = true;   // 악비 세력 [송]
		const bool 이세민_활성화 = true;   // 이세민 세력 [당]
		const bool 테무친_활성화 = true;   // 테무친 세력 [몽골]
		const bool 임충_활성화 = true;   // 수호전 세력 [몽골]
		
		
		/// *** 나이 제한에 걸리지 않도록 고대무장 및 신무장의 생년/몰년을 재설정하여 모든 시나리오에서 원활하게 등장할 수 있도록 함 ***
		/// 다만 의형제 설정이 된 무장들의 나이가 뒤바뀔 수도 있다는 점을 주의하세요. 
		/// (즉, 가능하면 세력과 시나리오 연도를 확인하고 설정 여부를 결정하시는 것을 권장)
		const bool 나이_재설정_유방세력 = true;   // 해당 세력 무장들의 생년/몰년을 시나리오 연도에 따라 재설정합니다. (true = on, false = off)
		const bool 나이_재설정_항적세력 = true;   
		const bool 나이_재설정_히미코세력 = true;   
		const bool 나이_재설정_철리길세력 = true;   
		const bool 나이_재설정_구력거세력 = true;
		const bool 나이_재설정_어부라세력 = true;
		const bool 나이_재설정_가비능세력 = true;   		
		const bool 나이_재설정_영정세력 = true;
		const bool 나이_재설정_조옹세력 = true;
		const bool 나이_재설정_희평세력 = true;
		const bool 나이_재설정_전인제세력 = true;
		const bool 나이_재설정_웅의세력 = true;
		const bool 나이_재설정_한무세력 = true;
		const bool 나이_재설정_위앵세력 = true;
		const bool 나이_재설정_악비세력 = true;
		const bool 나이_재설정_이세민세력 = true;
		const bool 나이_재설정_테무친세력 = true;
		const bool 나이_재설정_임충세력 = true;

				
		/// *** 각 세력의 군주를 제외한 무장을 입력하세요. ***	
		
		//역사무장 자동 임관
		array<pk::int> 위_세력 = { 무장_조절, 무장_조화, 무장_최씨, 무장_환씨, 무장_혜강, 무장_조헌, 무장_마륭 };
		array<pk::int> 촉_세력 = { 무장_번궁, 무장_이명 };
		array<pk::int> 오_세력 = { 무장_도황, 무장_수칙, 무장_반씨 };
		array<pk::int> 후한_세력 = { 무장_하씨, 무장_채옹 };		
		array<pk::int> 종회_세력 = { 무장_장창포 };
		array<pk::int> 유장_세력 = { 무장_비관 };
		array<pk::int> 공손찬_세력 = { 무장_후씨 };
		array<pk::int> 원술_세력 = { 무장_풍씨 };
		array<pk::int> 맹획_세력 = { 무장_토안, 무장_해니 };
		
		
		//신세력
		//전한
		array<pk::int> 유방_세력 = { 무장_장량_자방, 무장_한신, 무장_팽월, 무장_소하, 무장_번쾌, 무장_하후영, 무장_진평, 무장_조참, 무장_관영, 무장_왕릉_고대 };
		//서초
		array<pk::int> 항적_세력 = { 무장_범증, 무장_영포, 무장_종리말, 무장_계포, 무장_환초, 무장_용저, 무장_우희 };
		//진
		array<pk::int> 영정_세력 = { 무장_백기, 무장_이사, 무장_왕전, 무장_몽념, 무장_장의, 무장_여불위, 무장_이신 };
		//송
		array<pk::int> 악비_세력 = { 무장_한세충, 무장_양홍옥 };
		
		//왜
		array<pk::int> 히미코_세력 = { 무장_나시메, 무장_츠시고리 };
		//서강
		array<pk::int> 철리길_세력 = { 무장_아단, 무장_월길, 무장_강단, 무장_미당대왕, 무장_아하소과 };
		//오환
		array<pk::int> 구력거_세력 = { 무장_누반, 무장_답돈 };
		//흉노
		array<pk::int> 어부라_세력 = { 무장_유표2, 무장_호주천 };
		//선비
		array<pk::int> 가비능_세력 = { 무장_보도근 };
		//산월
		array<pk::int> 반림_세력 = { 무장_비잔, 무장_황란 };
		//조
		array<pk::int> 조옹_세력 = { 무장_조승, 무장_소진, 무장_염파, 무장_이목 };
		//연
		array<pk::int> 희평_세력 = { 무장_극신, 무장_곽외, 무장_악의 };
		//제
		array<pk::int> 전인제_세력 = { 무장_전문, 무장_추기, 무장_전기_고대, 무장_전단_고대 };
		//초 (전국)
		array<pk::int> 웅의_세력 = { 무장_굴원, 무장_공수반, 무장_항연, 무장_황헐 };
		//한
		array<pk::int> 한무_세력 = { 무장_한비 };
		//위
		array<pk::int> 위앵_세력 = { 무장_위무기, 무장_방연 };
		//당
		array<pk::int> 이세민_세력 = { 무장_화목란, 무장_양옥환, 무장_무조, 무장_장손무기, 무장_이정 };
		//몽골
		array<pk::int> 테무친_세력 = { 무장_야율초재, 무장_쿠빌라이, 무장_라찌, 무장_보르테, 무장_자무카 };
		//수호전
		array<pk::int> 임충_세력 = { 무장_호연작, 무장_화영, 무장_오용, 무장_이규, 무장_연청 };
		
		
	// ===========================================

	
	class Main
	{
		Main()
		{
			pk::bind(102, pk::trigger102_t(callback));
		}
		
		pk::person@ person_조조 = pk::get_person(무장_조조);
		pk::person@ person_조비 = pk::get_person(무장_조비);
		pk::person@ person_유비 = pk::get_person(무장_유비);
		pk::person@ person_유선 = pk::get_person(무장_유선);
		pk::person@ person_손견 = pk::get_person(무장_손견);
		pk::person@ person_손책 = pk::get_person(무장_손책);
		pk::person@ person_손권 = pk::get_person(무장_손권);
		pk::person@ person_하진 = pk::get_person(무장_하진);
		pk::person@ person_동탁 = pk::get_person(무장_동탁);
		pk::person@ person_원술 = pk::get_person(무장_원술);
		pk::person@ person_공손찬 = pk::get_person(무장_공손찬);
		pk::person@ person_종회 = pk::get_person(무장_종회);
		pk::person@ person_유장 = pk::get_person(무장_유장);
		pk::person@ person_맹획 = pk::get_person(무장_맹획);
		
		pk::person@ person_초선 = pk::get_person(무장_초선);
		
		
		pk::person@ person_유방 = pk::get_person(무장_유방);
		pk::person@ person_항적 = pk::get_person(무장_항적);
		pk::person@ person_영정 = pk::get_person(무장_리정);
		pk::person@ person_악비 = pk::get_person(무장_악비);
		
		pk::person@ person_히미코 = pk::get_person(무장_히미코);
		pk::person@ person_철리길 = pk::get_person(무장_철리길);
		pk::person@ person_구력거 = pk::get_person(무장_구력거);
		pk::person@ person_어부라 = pk::get_person(무장_어부라);
		pk::person@ person_가비능 = pk::get_person(무장_가비능);
		pk::person@ person_반림 = pk::get_person(무장_반림);		
		pk::person@ person_조옹 = pk::get_person(무장_조옹);
		pk::person@ person_희평 = pk::get_person(무장_희평);
		pk::person@ person_전인제 = pk::get_person(무장_전인제);
		pk::person@ person_웅의 = pk::get_person(무장_웅의);
		pk::person@ person_한무 = pk::get_person(무장_한무);
		pk::person@ person_위앵 = pk::get_person(무장_위앵);
		pk::person@ person_이세민 = pk::get_person(무장_이세민);
		pk::person@ person_테무친 = pk::get_person(무장_테무친);
		pk::person@ person_임충 = pk::get_person(무장_임충);
		


		void callback()
		{
			
			
			if (pk::get_scenario().loaded) return;
			
			//사실무장 자동배치 시작
			
			int district_id = -1;
			
			//조조
			if (person_조조.mibun == 신분_군주)
			{	
				pk::building@ kunshu_building = pk::get_building(person_조조.service);

				for (int j = 0; j < 위_세력.length; j++)
				{
					pk::person@ person_0 = pk::get_person(위_세력[j]);
					
					if ( pk::get_year() >= person_0.appearance )
					{
						district_id = kunshu_building.get_district_id();
						
						person_0.loyalty = 100;
						person_0.kouseki = 5000;
						person_0.mibun = 신분_일반;					

						pk::set_district(person_0, district_id); 	
						person_0.update();
						
						pk::sort(pk::person::type_id);
						pk::move(person_0, kunshu_building);
					}
					
				}
			}
			//조조
			//조비
			if (person_조비.mibun == 신분_군주)
			{	
				pk::building@ kunshu_building = pk::get_building(person_조비.service);

				for (int j = 0; j < 위_세력.length; j++)
				{
					pk::person@ person_0 = pk::get_person(위_세력[j]);
					
					if ( pk::get_year() >= person_0.appearance )
					{
						district_id = kunshu_building.get_district_id();
						
						person_0.loyalty = 100;
						person_0.kouseki = 5000;
						person_0.mibun = 신분_일반;					

						pk::set_district(person_0, district_id); 	
						person_0.update();
						
						pk::sort(pk::person::type_id);
						pk::move(person_0, kunshu_building);
					}
					
				}
			}
			//조비
			//유비
			if (person_유비.mibun == 신분_군주)
			{	
				pk::building@ kunshu_building = pk::get_building(person_유비.service);

				for (int j = 0; j < 촉_세력.length; j++)
				{
					pk::person@ person_0 = pk::get_person(촉_세력[j]);
					
					if ( pk::get_year() >= person_0.appearance )
					{
						district_id = kunshu_building.get_district_id();
						
						person_0.loyalty = 100;
						person_0.kouseki = 5000;
						person_0.mibun = 신분_일반;					

						pk::set_district(person_0, district_id); 	
						person_0.update();
						
						pk::sort(pk::person::type_id);
						pk::move(person_0, kunshu_building);
					}
					
				}
			}
			//유비
			//유선
			if (person_유선.mibun == 신분_군주)
			{	
				pk::building@ kunshu_building = pk::get_building(person_유선.service);

				for (int j = 0; j < 촉_세력.length; j++)
				{
					pk::person@ person_0 = pk::get_person(촉_세력[j]);
					
					if ( pk::get_year() >= person_0.appearance )
					{
						district_id = kunshu_building.get_district_id();
						
						person_0.loyalty = 100;
						person_0.kouseki = 5000;
						person_0.mibun = 신분_일반;					

						pk::set_district(person_0, district_id); 	
						person_0.update();
						
						pk::sort(pk::person::type_id);
						pk::move(person_0, kunshu_building);
					}
					
				}
			}
			//유선
			//손견
			if (person_손견.mibun == 신분_군주)
			{	
				pk::building@ kunshu_building = pk::get_building(person_손견.service);

				for (int j = 0; j < 오_세력.length; j++)
				{
					pk::person@ person_0 = pk::get_person(오_세력[j]);
					
					if ( pk::get_year() >= person_0.appearance )
					{
						district_id = kunshu_building.get_district_id();
						
						person_0.loyalty = 100;
						person_0.kouseki = 5000;
						person_0.mibun = 신분_일반;					

						pk::set_district(person_0, district_id); 	
						person_0.update();
						
						pk::sort(pk::person::type_id);
						pk::move(person_0, kunshu_building);
					}
					
				}
			}
			//손견
			//손책
			if (person_손책.mibun == 신분_군주)
			{	
				pk::building@ kunshu_building = pk::get_building(person_손책.service);

				for (int j = 0; j < 오_세력.length; j++)
				{
					pk::person@ person_0 = pk::get_person(오_세력[j]);
					
					if ( pk::get_year() >= person_0.appearance )
					{
						district_id = kunshu_building.get_district_id();
						
						person_0.loyalty = 100;
						person_0.kouseki = 5000;
						person_0.mibun = 신분_일반;					

						pk::set_district(person_0, district_id); 	
						person_0.update();
						
						pk::sort(pk::person::type_id);
						pk::move(person_0, kunshu_building);
					}
					
				}
			}
			//손책
			//손권
			if (person_손권.mibun == 신분_군주)
			{	
				pk::building@ kunshu_building = pk::get_building(person_손권.service);

				for (int j = 0; j < 오_세력.length; j++)
				{
					pk::person@ person_0 = pk::get_person(오_세력[j]);
					
					if ( pk::get_year() >= person_0.appearance )
					{
						district_id = kunshu_building.get_district_id();
						
						person_0.loyalty = 100;
						person_0.kouseki = 5000;
						person_0.mibun = 신분_일반;					

						pk::set_district(person_0, district_id); 	
						person_0.update();
						
						pk::sort(pk::person::type_id);
						pk::move(person_0, kunshu_building);
					}
					
				}
			}
			//손권
			//하진
			if (person_하진.mibun == 신분_군주)
			{	
				pk::building@ kunshu_building = pk::get_building(person_하진.service);

				for (int j = 0; j < 후한_세력.length; j++)
				{
					pk::person@ person_0 = pk::get_person(후한_세력[j]);
					
					if ( pk::get_year() >= person_0.appearance )
					{
						district_id = kunshu_building.get_district_id();
						
						person_0.loyalty = 100;
						person_0.kouseki = 5000;
						person_0.mibun = 신분_일반;					

						pk::set_district(person_0, district_id); 	
						person_0.update();
						
						pk::sort(pk::person::type_id);
						pk::move(person_0, kunshu_building);
					}
					
				}
			}
			//하진
			//동탁
			if (person_동탁.mibun == 신분_군주)
			{	
				pk::building@ kunshu_building = pk::get_building(person_동탁.service);

				for (int j = 0; j < 후한_세력.length; j++)
				{
					pk::person@ person_0 = pk::get_person(후한_세력[j]);
					
					if ( pk::get_year() >= person_0.appearance )
					{
						district_id = kunshu_building.get_district_id();
						
						person_0.loyalty = 100;
						person_0.kouseki = 5000;
						person_0.mibun = 신분_일반;					

						pk::set_district(person_0, district_id); 	
						person_0.update();
						
						pk::sort(pk::person::type_id);
						pk::move(person_0, kunshu_building);
					}
					
				}
			}
			//동탁
			//종회
			if (person_종회.mibun == 신분_군주)
			{	
				pk::building@ kunshu_building = pk::get_building(person_종회.service);

				for (int j = 0; j < 종회_세력.length; j++)
				{
					pk::person@ person_0 = pk::get_person(종회_세력[j]);
					
					if ( pk::get_year() >= person_0.appearance )
					{
						district_id = kunshu_building.get_district_id();
						
						person_0.loyalty = 100;
						person_0.kouseki = 5000;
						person_0.mibun = 신분_일반;					

						pk::set_district(person_0, district_id); 	
						person_0.update();
						
						pk::sort(pk::person::type_id);
						pk::move(person_0, kunshu_building);
					}
					
				}
			}
			//종회
			//종회
			if (person_종회.mibun != 신분_군주 and person_조비.mibun == 신분_군주 )
			{	
				pk::building@ kunshu_building = pk::get_building(person_조비.service);

				for (int j = 0; j < 종회_세력.length; j++)
				{
					pk::person@ person_0 = pk::get_person(종회_세력[j]);
					
					if ( pk::get_year() >= person_0.appearance )
					{
						district_id = kunshu_building.get_district_id();
						
						person_0.loyalty = 100;
						person_0.kouseki = 5000;
						person_0.mibun = 신분_일반;					

						pk::set_district(person_0, district_id); 	
						person_0.update();
						
						pk::sort(pk::person::type_id);
						pk::move(person_0, kunshu_building);
					}
					
				}
			}
			//종회
			//종회
			if (person_종회.mibun != 신분_군주 and person_조조.mibun == 신분_군주 )
			{	
				pk::building@ kunshu_building = pk::get_building(person_조조.service);

				for (int j = 0; j < 종회_세력.length; j++)
				{
					pk::person@ person_0 = pk::get_person(종회_세력[j]);
					
					if ( pk::get_year() >= person_0.appearance )
					{
						district_id = kunshu_building.get_district_id();
						
						person_0.loyalty = 100;
						person_0.kouseki = 5000;
						person_0.mibun = 신분_일반;					

						pk::set_district(person_0, district_id); 	
						person_0.update();
						
						pk::sort(pk::person::type_id);
						pk::move(person_0, kunshu_building);
					}
					
				}
			}
			//종회	
			//유장
			if (person_유장.mibun == 신분_군주 and person_유비.mibun == 신분_군주 )
			{	
				pk::building@ kunshu_building = pk::get_building(person_유장.service);

				for (int j = 0; j < 유장_세력.length; j++)
				{
					pk::person@ person_0 = pk::get_person(유장_세력[j]);
					
					if ( pk::get_year() >= person_0.appearance )
					{
						district_id = kunshu_building.get_district_id();
						
						person_0.loyalty = 100;
						person_0.kouseki = 5000;
						person_0.mibun = 신분_일반;					

						pk::set_district(person_0, district_id); 	
						person_0.update();
						
						pk::sort(pk::person::type_id);
						pk::move(person_0, kunshu_building);
					}
					
				}
			}
			//유장
			//유장 멸망 후
			if (person_유장.mibun != 신분_군주 and person_유비.mibun == 신분_군주 )
			{	
				pk::building@ kunshu_building = pk::get_building(person_유비.service);

				for (int j = 0; j < 유장_세력.length; j++)
				{
					pk::person@ person_0 = pk::get_person(유장_세력[j]);
					
					if ( pk::get_year() >= person_0.appearance )
					{
						district_id = kunshu_building.get_district_id();
						
						person_0.loyalty = 100;
						person_0.kouseki = 5000;
						person_0.mibun = 신분_일반;					

						pk::set_district(person_0, district_id); 	
						person_0.update();
						
						pk::sort(pk::person::type_id);
						pk::move(person_0, kunshu_building);
					}
					
				}
			}
			//유장
			//유장 멸망 후 2
			if (person_유장.mibun != 신분_군주 and person_유선.mibun == 신분_군주 )
			{	
				pk::building@ kunshu_building = pk::get_building(person_유선.service);

				for (int j = 0; j < 유장_세력.length; j++)
				{
					pk::person@ person_0 = pk::get_person(유장_세력[j]);
					
					if ( pk::get_year() >= person_0.appearance )
					{
						district_id = kunshu_building.get_district_id();
						
						person_0.loyalty = 100;
						person_0.kouseki = 5000;
						person_0.mibun = 신분_일반;					

						pk::set_district(person_0, district_id); 	
						person_0.update();
						
						pk::sort(pk::person::type_id);
						pk::move(person_0, kunshu_building);
					}
					
				}
			}
			//유장			
			//공손찬
			if (person_공손찬.mibun == 신분_군주)
			{	
				pk::building@ kunshu_building = pk::get_building(person_공손찬.service);

				for (int j = 0; j < 공손찬_세력.length; j++)
				{
					pk::person@ person_0 = pk::get_person(공손찬_세력[j]);
					
					if ( pk::get_year() >= person_0.appearance )
					{
						district_id = kunshu_building.get_district_id();
						
						person_0.loyalty = 100;
						person_0.kouseki = 5000;
						person_0.mibun = 신분_일반;					

						pk::set_district(person_0, district_id); 	
						person_0.update();
						
						pk::sort(pk::person::type_id);
						pk::move(person_0, kunshu_building);
					}
					
				}
			}
			//공손찬
			//원술
			if (person_원술.mibun == 신분_군주)
			{	
				pk::building@ kunshu_building = pk::get_building(person_원술.service);

				for (int j = 0; j < 원술_세력.length; j++)
				{
					pk::person@ person_0 = pk::get_person(원술_세력[j]);
					
					if ( pk::get_year() >= person_0.appearance )
					{
						district_id = kunshu_building.get_district_id();
						
						person_0.loyalty = 100;
						person_0.kouseki = 5000;
						person_0.mibun = 신분_일반;					

						pk::set_district(person_0, district_id); 	
						person_0.update();
						
						pk::sort(pk::person::type_id);
						pk::move(person_0, kunshu_building);
					}
					
				}
			}
			//원술
			//맹획
			if (person_맹획.mibun == 신분_군주)
			{	
				pk::building@ kunshu_building = pk::get_building(person_맹획.service);

				for (int j = 0; j < 맹획_세력.length; j++)
				{
					pk::person@ person_0 = pk::get_person(맹획_세력[j]);
					
					if ( pk::get_year() >= person_0.appearance )
					{
						district_id = kunshu_building.get_district_id();
						
						person_0.loyalty = 100;
						person_0.kouseki = 5000;
						person_0.mibun = 신분_일반;					

						pk::set_district(person_0, district_id); 	
						person_0.update();
						
						pk::sort(pk::person::type_id);
						pk::move(person_0, kunshu_building);
					}
					
				}
			}
			//맹획			
			//사실무장 자동배치 끝
			
						
			
			
			
			array<string> relocation_list =
			{
				pk::u8encode("시나리오 시작"),
				pk::u8encode("신세력 무장배치"),
				pk::u8encode("기존세력 재배치")
			};
			
			
			pk::play_se(1);
			int n = pk::choose(relocation_list, pk::u8encode("군주님!\n시작 전에 재배치할 세력이 있나요?"), person_초선);

			if (n == 0)
			{
				return;
			}
			
			if (n == 1)
			{
				int n = pk::choose({ pk::u8encode("예"), pk::u8encode("아니오")}, pk::u8encode("신세력에 알맞은 무장들을 자동으로 소속시킬까요?"), person_초선);
				if (n == 0) {pk::play_se(15);relocation_신세력배치();}				
				if (n == 1) {pk::play_se(16);callback();}
			}
			
			if (n == 2)
			{
				int n = pk::choose({ pk::u8encode("예"), pk::u8encode("아니오")}, pk::u8encode("기존세력을 재배치할까요?"), person_초선);
				if (n == 0) {pk::play_se(15);relocation_세력재배치();}
				if (n == 1) {pk::play_se(16);callback();}
			}
			
		}
		
		
		void relocation_신세력배치()
		{
			
			pk::random random(pk::rand());
			int district_id = -1;
			
			if (유방_활성화 and (person_유방.mibun == 신분_군주))
			{	
				pk::building@ kunshu_building = pk::get_building(person_유방.service);

				for (int j = 0; j < 유방_세력.length; j++)
				{
					pk::person@ person_0 = pk::get_person(유방_세력[j]);
					
					district_id = kunshu_building.get_district_id();
					
					if (나이_재설정_유방세력)
					{
						person_유방.birth = pk::get_year() - 17 - random(4);
						person_유방.death = pk::min(353, person_0.birth + 70 + random(20));
						person_0.birth = pk::get_year() - 17 - random(4);
						person_0.death = pk::min(353, person_0.birth + 70 + random(20));
					}
					
					person_0.loyalty = 100;
					person_0.kouseki = 5000;
					person_0.mibun = 신분_일반;					

					pk::set_district(person_0, district_id); 	
					person_0.update();
					
					pk::sort(pk::person::type_id);
					pk::move(person_0, kunshu_building);
					
				}
			}
			
			if (항적_활성화 and (person_항적.mibun == 신분_군주))
			{	
				pk::building@ kunshu_building = pk::get_building(person_항적.service);

				for (int j = 0; j < 항적_세력.length; j++)
				{
					pk::person@ person_0 = pk::get_person(항적_세력[j]);
					
					district_id = kunshu_building.get_district_id();

					if (나이_재설정_항적세력)
					{
						person_항적.birth = pk::get_year() - 17 - random(4);
						person_항적.death = pk::min(353, person_0.birth + 70 + random(20));
						person_0.birth = pk::get_year() - 17 - random(4);
						person_0.death = pk::min(353, person_0.birth + 70 + random(20));
					}
					
					person_0.loyalty = 100;
					person_0.kouseki = 5000;
					person_0.mibun = 신분_일반;		
					
					pk::set_district(person_0, district_id); 	
					person_0.update();
					
					pk::sort(pk::person::type_id);
					pk::move(person_0, kunshu_building);
					
				}
			}
			
			if (히미코_활성화 and (person_히미코.mibun == 신분_군주))
			{	
				pk::building@ kunshu_building = pk::get_building(person_히미코.service);

				for (int j = 0; j < 히미코_세력.length; j++)
				{
					pk::person@ person_0 = pk::get_person(히미코_세력[j]);
					
					district_id = kunshu_building.get_district_id();

					if (나이_재설정_히미코세력)
					{
						person_히미코.birth = pk::get_year() - 17 - random(4);
						person_히미코.death = pk::min(353, person_0.birth + 70 + random(20));
						person_0.birth = pk::get_year() - 17 - random(4);
						person_0.death = pk::min(353, person_0.birth + 70 + random(20));
					}
					
					person_0.loyalty = 100;
					person_0.kouseki = 5000;
					person_0.mibun = 신분_일반;		
					
					pk::set_district(person_0, district_id); 	
					person_0.update();
					
					pk::sort(pk::person::type_id);
					pk::move(person_0, kunshu_building);
					
				}
			}
			
			if (철리길_활성화 and (person_철리길.mibun == 신분_군주))
			{	
				pk::building@ kunshu_building = pk::get_building(person_철리길.service);

				for (int j = 0; j < 철리길_세력.length; j++)
				{
					pk::person@ person_0 = pk::get_person(철리길_세력[j]);
					
					district_id = kunshu_building.get_district_id();

					if (나이_재설정_철리길세력)
					{
						person_철리길.birth = pk::get_year() - 17 - random(4);
						person_철리길.death = pk::min(353, person_0.birth + 70 + random(20));
						person_0.birth = pk::get_year() - 17 - random(4);
						person_0.death = pk::min(353, person_0.birth + 70 + random(20));
					}
					
					person_0.loyalty = 100;
					person_0.kouseki = 5000;
					person_0.mibun = 신분_일반;		
					
					pk::set_district(person_0, district_id); 	
					person_0.update();
					
					pk::sort(pk::person::type_id);
					pk::move(person_0, kunshu_building);
					
				}
			}
			
			if (구력거_활성화 and (person_구력거.mibun == 신분_군주))
			{	
				pk::building@ kunshu_building = pk::get_building(person_구력거.service);

				for (int j = 0; j < 구력거_세력.length; j++)
				{
					pk::person@ person_0 = pk::get_person(구력거_세력[j]);
					
					district_id = kunshu_building.get_district_id();

					if (나이_재설정_구력거세력)
					{
						person_구력거.birth = pk::get_year() - 17 - random(4);
						person_구력거.death = pk::min(353, person_0.birth + 70 + random(20));
						person_0.birth = pk::get_year() - 17 - random(4);
						person_0.death = pk::min(353, person_0.birth + 70 + random(20));
					}
					
					person_0.loyalty = 100;
					person_0.kouseki = 5000;
					person_0.mibun = 신분_일반;		
					
					pk::set_district(person_0, district_id); 	
					person_0.update();
					
					pk::sort(pk::person::type_id);
					pk::move(person_0, kunshu_building);
					
				}
			}
			
			if (어부라_활성화 and (person_어부라.mibun == 신분_군주))
			{	
				pk::building@ kunshu_building = pk::get_building(person_어부라.service);

				for (int j = 0; j < 어부라_세력.length; j++)
				{
					pk::person@ person_0 = pk::get_person(어부라_세력[j]);
					
					district_id = kunshu_building.get_district_id();

					if (나이_재설정_어부라세력)
					{
						person_어부라.birth = pk::get_year() - 17 - random(4);
						person_어부라.death = pk::min(353, person_0.birth + 70 + random(20));
						person_0.birth = pk::get_year() - 17 - random(4);
						person_0.death = pk::min(353, person_0.birth + 70 + random(20));
					}
					
					person_0.loyalty = 100;
					person_0.kouseki = 5000;
					person_0.mibun = 신분_일반;		
					
					pk::set_district(person_0, district_id); 	
					person_0.update();
					
					pk::sort(pk::person::type_id);
					pk::move(person_0, kunshu_building);
					
				}
			}
			
			if (가비능_활성화 and (person_가비능.mibun == 신분_군주))
			{	
				pk::building@ kunshu_building = pk::get_building(person_가비능.service);

				for (int j = 0; j < 가비능_세력.length; j++)
				{
					pk::person@ person_0 = pk::get_person(가비능_세력[j]);
					
					district_id = kunshu_building.get_district_id();

					if (나이_재설정_가비능세력)
					{
						person_가비능.birth = pk::get_year() - 17 - random(4);
						person_가비능.death = pk::min(353, person_0.birth + 70 + random(20));
						person_0.birth = pk::get_year() - 17 - random(4);
						person_0.death = pk::min(353, person_0.birth + 70 + random(20));
					}
					
					person_0.loyalty = 100;
					person_0.kouseki = 5000;
					person_0.mibun = 신분_일반;		
					
					pk::set_district(person_0, district_id); 	
					person_0.update();
					
					pk::sort(pk::person::type_id);
					pk::move(person_0, kunshu_building);
					
				}
			}
			
			if (영정_활성화 and (person_영정.mibun == 신분_군주))
			{	
				pk::building@ kunshu_building = pk::get_building(person_영정.service);

				for (int j = 0; j < 영정_세력.length; j++)
				{
					pk::person@ person_0 = pk::get_person(영정_세력[j]);
					
					district_id = kunshu_building.get_district_id();

					if (나이_재설정_영정세력)
					{
						person_영정.birth = pk::get_year() - 17 - random(4);
						person_영정.death = pk::min(353, person_0.birth + 70 + random(20));
						person_0.birth = pk::get_year() - 17 - random(4);
						person_0.death = pk::min(353, person_0.birth + 70 + random(20));
					}
					
					person_0.loyalty = 100;
					person_0.kouseki = 5000;
					person_0.mibun = 신분_일반;		
					
					pk::set_district(person_0, district_id); 	
					person_0.update();
					
					pk::sort(pk::person::type_id);
					pk::move(person_0, kunshu_building);
					
				}
			}
			
			if (조옹_활성화 and (person_조옹.mibun == 신분_군주))
			{	
				pk::building@ kunshu_building = pk::get_building(person_조옹.service);

				for (int j = 0; j < 조옹_세력.length; j++)
				{
					pk::person@ person_0 = pk::get_person(조옹_세력[j]);
					
					district_id = kunshu_building.get_district_id();

					if (나이_재설정_조옹세력)
					{
						person_조옹.birth = pk::get_year() - 17 - random(4);
						person_조옹.death = pk::min(353, person_0.birth + 70 + random(20));
						person_0.birth = pk::get_year() - 17 - random(4);
						person_0.death = pk::min(353, person_0.birth + 70 + random(20));
					}
					
					person_0.loyalty = 100;
					person_0.kouseki = 5000;
					person_0.mibun = 신분_일반;		
					
					pk::set_district(person_0, district_id); 	
					person_0.update();
					
					pk::sort(pk::person::type_id);
					pk::move(person_0, kunshu_building);
					
				}
			}
			
			if (희평_활성화 and (person_희평.mibun == 신분_군주))
			{	
				pk::building@ kunshu_building = pk::get_building(person_희평.service);

				for (int j = 0; j < 희평_세력.length; j++)
				{
					pk::person@ person_0 = pk::get_person(희평_세력[j]);
					
					district_id = kunshu_building.get_district_id();

					if (나이_재설정_희평세력)
					{
						person_희평.birth = pk::get_year() - 17 - random(4);
						person_희평.death = pk::min(353, person_0.birth + 70 + random(20));
						person_0.birth = pk::get_year() - 17 - random(4);
						person_0.death = pk::min(353, person_0.birth + 70 + random(20));
					}
					
					person_0.loyalty = 100;
					person_0.kouseki = 5000;
					person_0.mibun = 신분_일반;		
					
					pk::set_district(person_0, district_id); 	
					person_0.update();
					
					pk::sort(pk::person::type_id);
					pk::move(person_0, kunshu_building);
					
				}
			}
			
			if (전인제_활성화 and (person_전인제.mibun == 신분_군주))
			{	
				pk::building@ kunshu_building = pk::get_building(person_전인제.service);

				for (int j = 0; j < 전인제_세력.length; j++)
				{
					pk::person@ person_0 = pk::get_person(전인제_세력[j]);
					
					district_id = kunshu_building.get_district_id();

					if (나이_재설정_전인제세력)
					{
						person_전인제.birth = pk::get_year() - 17 - random(4);
						person_전인제.death = pk::min(353, person_0.birth + 70 + random(20));
						person_0.birth = pk::get_year() - 17 - random(4);
						person_0.death = pk::min(353, person_0.birth + 70 + random(20));
					}
					
					person_0.loyalty = 100;
					person_0.kouseki = 5000;
					person_0.mibun = 신분_일반;		
					
					pk::set_district(person_0, district_id); 	
					person_0.update();
					
					pk::sort(pk::person::type_id);
					pk::move(person_0, kunshu_building);
					
				}
			}
			
			if (웅의_활성화 and (person_웅의.mibun == 신분_군주))
			{	
				pk::building@ kunshu_building = pk::get_building(person_웅의.service);

				for (int j = 0; j < 웅의_세력.length; j++)
				{
					pk::person@ person_0 = pk::get_person(웅의_세력[j]);
					
					district_id = kunshu_building.get_district_id();

					if (나이_재설정_웅의세력)
					{
						person_웅의.birth = pk::get_year() - 17 - random(4);
						person_웅의.death = pk::min(353, person_0.birth + 70 + random(20));
						person_0.birth = pk::get_year() - 17 - random(4);
						person_0.death = pk::min(353, person_0.birth + 70 + random(20));
					}
					
					person_0.loyalty = 100;
					person_0.kouseki = 5000;
					person_0.mibun = 신분_일반;		
					
					pk::set_district(person_0, district_id); 	
					person_0.update();
					
					pk::sort(pk::person::type_id);
					pk::move(person_0, kunshu_building);
					
				}
			}
			
			if (한무_활성화 and (person_한무.mibun == 신분_군주))
			{	
				pk::building@ kunshu_building = pk::get_building(person_한무.service);

				for (int j = 0; j < 한무_세력.length; j++)
				{
					pk::person@ person_0 = pk::get_person(한무_세력[j]);
					
					district_id = kunshu_building.get_district_id();

					if (나이_재설정_한무세력)
					{
						person_한무.birth = pk::get_year() - 17 - random(4);
						person_한무.death = pk::min(353, person_0.birth + 70 + random(20));
						person_0.birth = pk::get_year() - 17 - random(4);
						person_0.death = pk::min(353, person_0.birth + 70 + random(20));
					}
					
					person_0.loyalty = 100;
					person_0.kouseki = 5000;
					person_0.mibun = 신분_일반;		
					
					pk::set_district(person_0, district_id); 	
					person_0.update();
					
					pk::sort(pk::person::type_id);
					pk::move(person_0, kunshu_building);
					
				}
			}
			
			if (위앵_활성화 and (person_위앵.mibun == 신분_군주))
			{	
				pk::building@ kunshu_building = pk::get_building(person_위앵.service);

				for (int j = 0; j < 위앵_세력.length; j++)
				{
					pk::person@ person_0 = pk::get_person(위앵_세력[j]);
					
					district_id = kunshu_building.get_district_id();

					if (나이_재설정_위앵세력)
					{
						person_위앵.birth = pk::get_year() - 17 - random(4);
						person_위앵.death = pk::min(353, person_0.birth + 70 + random(20));
						person_0.birth = pk::get_year() - 17 - random(4);
						person_0.death = pk::min(353, person_0.birth + 70 + random(20));
					}
					
					person_0.loyalty = 100;
					person_0.kouseki = 5000;
					person_0.mibun = 신분_일반;		
					
					pk::set_district(person_0, district_id); 	
					person_0.update();
					
					pk::sort(pk::person::type_id);
					pk::move(person_0, kunshu_building);
					
				}
			}
			
			if (악비_활성화 and (person_악비.mibun == 신분_군주))
			{	
				pk::building@ kunshu_building = pk::get_building(person_악비.service);

				for (int j = 0; j < 악비_세력.length; j++)
				{
					pk::person@ person_0 = pk::get_person(악비_세력[j]);
					
					district_id = kunshu_building.get_district_id();

					if (나이_재설정_악비세력)
					{
						person_악비.birth = pk::get_year() - 17 - random(4);
						person_악비.death = pk::min(353, person_0.birth + 70 + random(20));
						person_0.birth = pk::get_year() - 17 - random(4);
						person_0.death = pk::min(353, person_0.birth + 70 + random(20));
					}
					
					person_0.loyalty = 100;
					person_0.kouseki = 5000;
					person_0.mibun = 신분_일반;		
					
					pk::set_district(person_0, district_id); 	
					person_0.update();
					
					pk::sort(pk::person::type_id);
					pk::move(person_0, kunshu_building);
					
				}
			}
			if (이세민_활성화 and (person_이세민.mibun == 신분_군주))
			{	
				pk::building@ kunshu_building = pk::get_building(person_이세민.service);

				for (int j = 0; j < 이세민_세력.length; j++)
				{
					pk::person@ person_0 = pk::get_person(이세민_세력[j]);
					
					district_id = kunshu_building.get_district_id();

					if (나이_재설정_이세민세력)
					{
						person_이세민.birth = pk::get_year() - 17 - random(4);
						person_이세민.death = pk::min(353, person_0.birth + 70 + random(20));
						person_0.birth = pk::get_year() - 17 - random(4);
						person_0.death = pk::min(353, person_0.birth + 70 + random(20));
					}
					
					person_0.loyalty = 100;
					person_0.kouseki = 5000;
					person_0.mibun = 신분_일반;		
					
					pk::set_district(person_0, district_id); 	
					person_0.update();
					
					pk::sort(pk::person::type_id);
					pk::move(person_0, kunshu_building);
					
				}
			}
			
			if (테무친_활성화 and (person_테무친.mibun == 신분_군주))
			{	
				pk::building@ kunshu_building = pk::get_building(person_테무친.service);

				for (int j = 0; j < 테무친_세력.length; j++)
				{
					pk::person@ person_0 = pk::get_person(테무친_세력[j]);
					
					district_id = kunshu_building.get_district_id();

					if (나이_재설정_테무친세력)
					{
						person_테무친.birth = pk::get_year() - 17 - random(4);
						person_테무친.death = pk::min(353, person_0.birth + 70 + random(20));
						person_0.birth = pk::get_year() - 17 - random(4);
						person_0.death = pk::min(353, person_0.birth + 70 + random(20));
					}
					
					person_0.loyalty = 100;
					person_0.kouseki = 5000;
					person_0.mibun = 신분_일반;		
					
					pk::set_district(person_0, district_id); 	
					person_0.update();
					
					pk::sort(pk::person::type_id);
					pk::move(person_0, kunshu_building);
					
				}
			}
			
			if (임충_활성화 and (person_임충.mibun == 신분_군주))
			{	
				pk::building@ kunshu_building = pk::get_building(person_임충.service);

				for (int j = 0; j < 임충_세력.length; j++)
				{
					pk::person@ person_0 = pk::get_person(임충_세력[j]);
					
					district_id = kunshu_building.get_district_id();

					if (나이_재설정_임충세력)
					{
						person_임충.birth = pk::get_year() - 17 - random(4);
						person_임충.death = pk::min(353, person_0.birth + 70 + random(20));
						person_0.birth = pk::get_year() - 17 - random(4);
						person_0.death = pk::min(353, person_0.birth + 70 + random(20));
					}
					
					person_0.loyalty = 100;
					person_0.kouseki = 5000;
					person_0.mibun = 신분_일반;		
					
					pk::set_district(person_0, district_id); 	
					person_0.update();
					
					pk::sort(pk::person::type_id);
					pk::move(person_0, kunshu_building);
					
				}
			}
			
			array<string> relocation_list =
			{
				pk::u8encode("시나리오 시작"),
				pk::u8encode("신세력 무장배치"),
				pk::u8encode("기존세력 재배치")
			};
			
			pk::play_se(1);
			pk::message_box(pk::u8encode("신세력에 무장 배치가 완료되었어요!"), person_초선);
			
			pk::play_se(1);
			int n = pk::choose(relocation_list, pk::u8encode("군주님!\n이제 시나리오를 시작해 볼까요?"), person_초선);

			if (n == 0)
			{
				return;
			}
			
			if (n == 1)
			{
				int n = pk::choose({ pk::u8encode("예"), pk::u8encode("아니오")}, pk::u8encode("신세력에 무장들을 자동으로 소속시킬까요?"), person_초선);
				if (n == 0) {pk::play_se(15);relocation_신세력배치();}				
				if (n == 1) {pk::play_se(16);callback();}
			}
			
			if (n == 2)
			{
				int n = pk::choose({ pk::u8encode("예"), pk::u8encode("아니오")}, pk::u8encode("기존세력을 재배치할까요?"), person_초선);
				if (n == 0) {pk::play_se(15);relocation_세력재배치();}
				if (n == 1) {pk::play_se(16);callback();}
			}		

		}
		
		
		void relocation_세력재배치()
		{
			
			pk::list<pk::force@> force_list = pk::get_force_list();
			array<int> city_count;
			array<int> index;

			force_list.shuffle();
			for (int i = 0; i < force_list.count; i++)
				city_count.insertLast(pk::get_city_list(force_list[i]).count);

			index = Partitioner(pk::get_scenario().seed).partition(city_count);

			// 도시 재설정
			for (int i = 0; i < force_list.count; i++)
			{
				pk::list<pk::city@> a = pk::get_city_list(force_list[i]); // 불필요한 도시
				pk::list<pk::city@> b; // 필요한 도시

				for (int j = 0; j < 도시_끝; j++)
				{
					if (index[j] == i)
					{
						pk::city@ city = pk::get_city(j);
						int k = a.index_of(city);
						if (k >= 0)
							a.remove_at(k);
						else
							b.add(city);
					}
				}

				a.shuffle();
				b.shuffle();

				for (int j = 0; j < a.count; j++)
				{
					pk::building@ c = pk::city_to_building(a[j]);
					pk::building@ d = pk::city_to_building(b[j]);

					// 황제 재설정(영웅집결 시나리오만 적용)
					if (j == 0 and i == 0 and pk::get_scenario().no == 7)
					{
						int building_id = d.get_id();
						array<int> emperors = { 무장_영제, 무장_소제, 무장_헌제 };
						for (int k = 0; k < emperors.length; k++)
						{
							pk::person@ emperor = pk::get_person(emperors[k]);
							pk::set_service(emperor, building_id);
							emperor.location = building_id;
							emperor.mibun = 신분_사망;
						}
						int n = pk::rand(3);
						pk::get_person(emperors[n]).mibun = -1;
						pk::get_scenario().emperor = emperors[n];
					}

					swap(c, d);
				}
			}

			// 항구, 관문 재설정
			for (int i = 0; i < 도시_끝; i++)
			{
				pk::city@ city = pk::get_city(i);
				int force_id = city.get_force_id();
				for (int j = 0; j < 5; j++)
				{
					if (city.gate[j] != -1)
					{
						pk::building@ building = pk::get_building(city.gate[j]);
						if (force_id == -1)
						{
							pk::neutralize(building);
						}
						else
						{
							pk::set_district(building, city.get_district_id());
							pk::set_gold(building, city.gold / 10);
							pk::set_food(building, city.food / 10);
							pk::set_troops(building, city.troops / 10);
							pk::set_energy(building, city.energy);
							pk::reset_weapon_amount(building);
							pk::set_weapon_amount(building, pk::rand(병기_군마) + 1, city.troops / 10);
						}
					}
				}
			}			
			
			array<string> relocation_list =
			{
				pk::u8encode("시나리오 시작"),
				pk::u8encode("신세력 무장배치"),
				pk::u8encode("기존세력 재배치")
			};
			
			pk::play_se(1);
			pk::message_box(pk::u8encode("기존세력의 위치가 전부 변경되었어요!"), person_초선);
			
			pk::play_se(1);
			int n = pk::choose(relocation_list, pk::u8encode("군주님!\n이제 시나리오를 시작해 볼까요?"), person_초선);

			if (n == 0)
			{
				return;
			}
			
			if (n == 1)
			{
				int n = pk::choose({ pk::u8encode("예"), pk::u8encode("아니오")}, pk::u8encode("신세력에 무장들을 자동으로 배치할까요?"), person_초선);
				if (n == 0) {pk::play_se(15);relocation_신세력배치();}				
				if (n == 1) {pk::play_se(16);callback();}
			}
			
			if (n == 2)
			{
				int n = pk::choose({ pk::u8encode("예"), pk::u8encode("아니오")}, pk::u8encode("기존세력을 재배치할까요?"), person_초선);
				if (n == 0) {pk::play_se(15);relocation_세력재배치();}
				if (n == 1) {pk::play_se(16);callback();}
			}
			
		} // relocation_세력
		
	}; // class Main

	
	class Partitioner
	{
		array<int> result_(도시_끝);
		array<int> start_;
		pk::random random_;

		Partitioner(int seed)
		{
			random_.seed = seed;
		}

		/**
		@param count
			도시 수 배열
		@return
			도시 아이디 별로 city_count 키(인덱스) 값이 들어감
		*/
		array<int> partition(const array<int> &in city_count)
		{
			bool retry = true;

			while (retry)
			{
				start_.resize(도시_끝);
				for (int i = 0; i < 도시_끝; i++)
				{
					result_[i] = -1;
					start_[i] = i;
				}

				shuffle(start_);

				retry = false;
				for (int i = 0; i < city_count.length; i++)
				{
					if (spread(start_[0], city_count[i], i) != 0)
					{
						retry = true;
						break;
					}
				}
			}

			return result_;
		}

		/** city_id 도시를 기준으로 n 개의 도시만큼 선택
		@return
			남은 개수
		*/
		int spread(int city_id, int n, int index)
		{
			// 끝났거나 이미 다른 세력의 도시인 경우 리턴.
			if (n <= 0 or result_[city_id] != -1)
				return n;

			result_[city_id] = index;
			n -= 1;

			int p = start_.find(city_id);
			if (p >= 0)
				start_.removeAt(p);

			// 이웃도시 섞기.
			pk::city@ city = pk::get_city(city_id);
			array<int> neighbor_city_id(6);
			for (int i = 0; i < 6; i++)
				neighbor_city_id[i] = city.neighbor[i];
			shuffle(neighbor_city_id);

			for (int i = 0; i < 6; i++)
			{
				if (neighbor_city_id[i] != -1 && result_[neighbor_city_id[i]] == -1)
					n = spread(neighbor_city_id[i], n, index);
				if (n == 0)
					break;
			}

			// 남은 도시 수를 리턴
			return n;
		}

		void shuffle(array<int>& arr)
		{
			int n = arr.length();
			for (int i = 0; i < n; i++)
			{
				int j = random_(n - 1);
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	};

	void swap(pk::building@ a, pk::building@ b)
	{
		SwapContext ctx_a;
		SwapContext ctx_b;
		ctx_a.load(a);
		ctx_b.load(b);
		ctx_a.save(b);
		ctx_b.save(a);
		if (a.get_force_id() == -1)
			pk::neutralize(a);
		if (b.get_force_id() == -1)
			pk::neutralize(b);
	}

	class SwapContext
	{
		int district_id = -1;
		pk::list<pk::person@> person_list;
		int gold = 0;
		int food = 0;
		int public_order = 0;
		int troops = 0;
		int energy = 0;
		array<int> weapon_amount(병기_끝, 0);

		void load(pk::building@ building)
		{
			pk::city@ city = pk::building_to_city(building);
			district_id = building.get_district_id();
			person_list = pk::get_person_list(building, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반));
			gold = pk::get_gold(building);
			food = pk::get_food(building);
			public_order = city !is null ? city.public_order : 0;
			troops = pk::get_troops(building);
			energy = pk::get_energy(building);
			for (int i = 0; i < 병기_끝; i++)
				weapon_amount[i] = pk::get_weapon_amount(building, i);
		}

		void save(pk::building@ building)
		{
			pk::city@ city = pk::building_to_city(building);
			pk::set_district(building, district_id);
			for (int i = 0; i < person_list.count; i++)
				pk::move(person_list[i], building);
			pk::set_gold(building, gold);
			pk::set_food(building, food);
			if (city !is null)
				pk::set_public_order(city, public_order);
			pk::set_troops(building, troops);
			pk::set_energy(building, energy);
			for (int i = 0; i < 병기_끝; i++)
				pk::set_weapon_amount(building, i, weapon_amount[i]);
		}
	};

	Main main;
}