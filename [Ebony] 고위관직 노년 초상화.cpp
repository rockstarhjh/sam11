/* 
@제작자: HoneyBee  
@설명: 무장의 공적이 일정 수준이상이 되었을 경우에 [군주/도독] 신분이거나 [평북장군] 이상의 관직이면 고위 일러스트로 자동 변경되는 SCRIPT 


※ 무장들의 老年은 50세로 통일 (각 무장마다 취향에 맞게 변경하셔도 됩니다.)
※ 조조, 유비, 손권, 원소, 원술은 군주 신분이면서 세력의 작위가 王 이상이어야 변경됨
※ GOLD EDITION PATCH에 동봉된 FACE DATA를 활용하셔야 정상적으로 반영됩니다. (중요)

@수정자: MUSSO
※ Ebony 그래픽 패키지 초상화 인덱스에 대응
※ 황제와 고위 관직 초상화 분리
※ 일반, 고위, 노년, 고위 노년 분리
※ 조예 황제 초상화 추가
※ 유비, 손권, 조조 청년시절 초상화 추가
※ 조운의 경우 청년, 중년, 노년으로 세분화
*/

namespace Ebony_고위관직_얼굴변경
{
	
	// ================ CUSTOMIZE ================
		
		const int 공적비교		 = 30000; 		// 고위 초상화 변경 기준
		const int 관직조건		 = 관직_토역장군; 	// 고위 초상화 변경 기준
		const int 노년_초상화	 = 1000; 		// 노년 초상화 추가 인덱스
		const int 고위_초상화	 = 1200; 		// 고위관직 초상화 추가 인덱스
		const int 고위노년_초상화	 = 1400; 		// 고위관직 + 노년 초상화 추가 인덱스
		//실제로는 게임에서 아래 설정나이에서 +1 한 나이에 초상화가 바뀝니다.
		const int 청년나이		 = 34;			// 유비, 손권, 조조 등에 사용
		const int 노년나이_여	 = 41;			// 여무장 노년
		const int 나이_하후돈독안	 = 39;			// 하후돈 애꾸눈
		const int 중년나이		 = 41;			//
		const int 노년나이		 = 49;			//
		const int 노년나이_조운	 = 59;			//
		
	// ===========================================

	
	class Main
	{
        
        Main()
		{
            pk::bind(102, pk::trigger102_t(onGameInit));
            pk::bind(111, pk::trigger111_t(onTurnStart));
        }
        
     
        void onGameInit()
        {character_multiple_portrait();}
        void onTurnStart(pk::force@ force)
		{character_multiple_portrait();}
        

        void character_multiple_portrait()
        {
			// 공식 시나리오에서 배정된 조조, 유비, 손권, 원소, 원술의 세력 번호를 입력
			pk::force@ 세력_조조 = pk::get_force(0);
			pk::force@ 세력_조비 = pk::get_force(0);
			pk::force@ 세력_조예 = pk::get_force(0);
			pk::force@ 세력_유비 = pk::get_force(1);
			pk::force@ 세력_유선 = pk::get_force(1);
			pk::force@ 세력_손권 = pk::get_force(2);
			pk::force@ 세력_원소 = pk::get_force(7);
			pk::force@ 세력_원술 = pk::get_force(8);						
			
            for (int person_id = 0; person_id < 무장_끝; person_id++)
            {                    
				pk::person@ person_p = pk::get_person(person_id);
				
				string grade_color;
				string grade_name;
				string character_title;
				
				if (person_p !is null)
				{
							
					// 장수정보 시작												
												
					// 가후
					if (person_p.get_id() == 무장_가후) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
								person_p.face = 초상화_가후;
								// 고위
								if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
								{person_p.face = 초상화_가후 + 고위_초상화;}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
								// 일반
								if (pk::get_year() < (person_p.birth + 노년나이))
								{person_p.face = 초상화_가후;}

								// 일반 노년
								if (pk::get_year() >= (person_p.birth + 노년나이))
								{person_p.face = 초상화_가후 + 노년_초상화;}

								if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
								{
									// 고위
									if (pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_가후 + 고위_초상화;}
									// 고위 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_가후 + 고위노년_초상화;}
								}
							}
					}
					// 감녕
					if (person_p.get_id() == 무장_감녕) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_감녕;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_감녕 + 고위_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_감녕;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_감녕 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_감녕 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_감녕 + 고위노년_초상화;}
									}
							}
					}
					// 강유
					if (person_p.get_id() == 무장_강유) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_강유;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_강유 + 고위_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_강유;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_강유 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_강유 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_강유 + 고위노년_초상화;}
									}
							}
					}
					// 곽가
					if (person_p.get_id() == 무장_곽가) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_곽가;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_곽가 + 고위_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_곽가;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_곽가 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_곽가 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_곽가 + 고위노년_초상화;}
									}
							}
					}
					// 관우
					if (person_p.get_id() == 무장_관우) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_관우;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_관우 + 고위_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_관우;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_관우 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_관우 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_관우 + 고위노년_초상화;}
									}
							}
					}
					// 노숙
					if (person_p.get_id() == 무장_노숙) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_노숙;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_노숙 + 고위_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_노숙;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_노숙 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_노숙 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_노숙 + 고위노년_초상화;}
									}
							}
					}
					// 능통
					if (person_p.get_id() == 무장_능통) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_능통;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_능통 + 고위_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_능통;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_능통 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_능통 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_능통 + 고위노년_초상화;}
									}
							}
					}
					// 동탁
					if (person_p.get_id() == 무장_동탁) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_동탁;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_동탁 + 고위_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 젊었을 때
									if (pk::get_year() < (person_p.birth + 51))
									{person_p.face = 1607;}
									
									// 일반
									if (pk::get_year() >= (person_p.birth + 51) and pk::get_year() < (person_p.birth + 51))
									{person_p.face = 초상화_동탁;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 54))
									{person_p.face = 초상화_동탁 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() >= (person_p.birth + 51) and pk::get_year() < (person_p.birth + 51))
									{person_p.face = 초상화_동탁;}
											{person_p.face = 초상화_동탁 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_동탁 + 고위노년_초상화;}
									}
							}
					}
					// 등애
					if (person_p.get_id() == 무장_등애) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_등애;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_등애 + 고위_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_등애;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_등애 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_등애 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_등애 + 고위노년_초상화;}
									}
							}
					}
					// 마대
					if (person_p.get_id() == 무장_마대) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_마대;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_마대 + 고위_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_마대;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_마대 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_마대 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_마대 + 고위노년_초상화;}
									}
							}
					}
					// 마초
					if (person_p.get_id() == 무장_마초) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_마초;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_마초 + 고위_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_마초;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_마초 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_마초 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_마초 + 고위노년_초상화;}
									}
							}
					}
					// 맹획
					if (person_p.get_id() == 무장_맹획) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_맹획;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_맹획 + 고위_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_맹획;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_맹획 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_맹획 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_맹획 + 고위노년_초상화;}
									}
							}
					}
					// 문추
					if (person_p.get_id() == 무장_문추) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_문추;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_문추 + 고위_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_문추;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_문추 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_문추 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_문추 + 고위노년_초상화;}
									}
							}
					}
					// 방덕
					if (person_p.get_id() == 무장_방덕) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)	
							{
							person_p.face = 초상화_방덕;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_방덕 + 고위_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_방덕;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_방덕 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_방덕 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_방덕 + 고위노년_초상화;}
									}
							}
					}
					// 방통
					if (person_p.get_id() == 무장_방통) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_방통;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_방통 + 고위_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_방통;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_방통 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_방통 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_방통 + 고위노년_초상화;}
									}
							}
					}
					// 사마의
					if (person_p.get_id() == 무장_사마의) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_사마의;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_사마의 + 고위_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_사마의;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_사마의 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_사마의 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_사마의 + 고위노년_초상화;}
									}
							}
					}
					// 서서
					if (person_p.get_id() == 무장_서서) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_서서;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_서서 + 고위_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_서서;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_서서 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_서서 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_서서 + 고위노년_초상화;}
									}
							}
					}
					// 서황
					if (person_p.get_id() == 무장_서황) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_서황;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_서황 + 고위_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_서황;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_서황 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_서황 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_서황 + 고위노년_초상화;}
									}
							}
					}
					// 손견
					if (person_p.get_id() == 무장_손견) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_손견;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_손견 + 고위_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_손견;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_손견 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_손견 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_손견 + 고위노년_초상화;}
									}
							}
					}
					// 손상향
					if (person_p.get_id() == 무장_손상향) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_손상향;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_손상향 + 고위_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 노년나이_여))
									{person_p.face = 초상화_손상향;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 노년나이_여))
									{person_p.face = 초상화_손상향 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이_여))
											{person_p.face = 초상화_손상향 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이_여))
											{person_p.face = 초상화_손상향 + 고위노년_초상화;}
									}
							}
					}
					// 손책
					if (person_p.get_id() == 무장_손책) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_손책;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_손책 + 고위_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 청년나이))
									{person_p.face = 초상화_손책;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 청년나이))
									{person_p.face = 초상화_손책 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 청년나이))
											{person_p.face = 초상화_손책 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 청년나이))
											{person_p.face = 초상화_손책 + 고위노년_초상화;}
									}
							}
					}
					// 순욱
					if (person_p.get_id() == 무장_순욱) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_순욱;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_순욱 + 고위_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_순욱;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_순욱 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_순욱 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_순욱 + 고위노년_초상화;}
									}
							}
					}
					// 순유
					if (person_p.get_id() == 무장_순유) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_순유;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_순유 + 고위_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_순유;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_순유 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_순유 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_순유 + 고위노년_초상화;}
									}
							}
					}
					// 악진
					if (person_p.get_id() == 무장_악진) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_악진;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_악진 + 고위_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_악진;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_악진 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_악진 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_악진 + 고위노년_초상화;}
									}
							}
					}
					// 안량
					if (person_p.get_id() == 무장_안량) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_안량;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_안량 + 고위_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_안량;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_안량 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_안량 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_안량 + 고위노년_초상화;}
									}
							}
					}
					// 여몽
					if (person_p.get_id() == 무장_여몽) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_여몽 + 노년_초상화;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_여몽 + 고위노년_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 중년나이))
									{person_p.face = 초상화_여몽;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 중년나이))
									{person_p.face = 초상화_여몽 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 중년나이))
											{person_p.face = 초상화_여몽 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 중년나이))
											{person_p.face = 초상화_여몽 + 고위노년_초상화;}
									}
							}
					}
					// 여포
					if (person_p.get_id() == 무장_여포) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_여포;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_여포 + 고위_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_여포;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_여포 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_여포 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_여포 + 고위노년_초상화;}
									}
							}
					}
					// 원소
					if (person_p.get_id() == 무장_원소) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_원소;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_원소 + 고위_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_원소;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_원소 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_원소 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_원소 + 고위노년_초상화;}
									}
							}
					}
					// 위연
					if (person_p.get_id() == 무장_위연) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_위연;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_위연 + 고위_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_위연;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_위연 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_위연 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_위연 + 고위노년_초상화;}
									}
							}
					}
					// 육손
					if (person_p.get_id() == 무장_육손) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_육손;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_육손 + 고위_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 중년나이))
									{person_p.face = 초상화_육손;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 중년나이))
									{person_p.face = 초상화_육손 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 중년나이))
											{person_p.face = 초상화_육손 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 중년나이))
											{person_p.face = 초상화_육손 + 고위노년_초상화;}
									}
							}
					}
					// 장료
					if (person_p.get_id() == 무장_장료) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_장료;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_장료 + 고위_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_장료;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_장료 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_장료 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_장료 + 고위노년_초상화;}
									}
							}
					}
					// 장비
					if (person_p.get_id() == 무장_장비) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_장비;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_장비 + 고위_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_장비;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_장비 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_장비 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_장비 + 고위노년_초상화;}
									}
							}
					}
					// 장합
					if (person_p.get_id() == 무장_장합) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_장합;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_장합 + 고위_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_장합;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_장합 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_장합 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_장합 + 고위노년_초상화;}
									}
							}
					}
					// 전위
					if (person_p.get_id() == 무장_전위) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_전위;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_전위 + 고위_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_전위;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_전위 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_전위 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_전위 + 고위노년_초상화;}
									}
							}
					}
					// 정욱
					if (person_p.get_id() == 무장_정욱) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_정욱;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_정욱 + 고위_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_정욱;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_정욱 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_정욱 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_정욱 + 고위노년_초상화;}
									}
							}
					}
					// 제갈량
					if (person_p.get_id() == 무장_제갈량) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_제갈량 + 고위_초상화;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_제갈량 + 고위_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_제갈량;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_제갈량 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_제갈량 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_제갈량 + 고위노년_초상화;}
									}
							}
					}
					// 조운
					if (person_p.get_id() == 무장_조운) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_조운;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_조운 + 고위_초상화;
									}
							}
							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									
											// 일반
											if (pk::get_year() < (person_p.birth + 중년나이))
											{person_p.face = 초상화_조운;}
											// 일반 노년
											if (pk::get_year() >= (person_p.birth + 중년나이) and pk::get_year() < (person_p.birth + 노년나이_조운))
											{person_p.face = 초상화_조운 + 노년_초상화;}
											// 조운 특수 노년
											if (pk::get_year() >= (person_p.birth + 노년나이_조운))
											{person_p.face = 1605;}
											
									
									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 중년나이))
											{person_p.face = 초상화_조운 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 중년나이) and pk::get_year() < (person_p.birth + 노년나이_조운))
											{person_p.face = 초상화_조운 + 고위노년_초상화;}
											// 조운 특수 노년
											if (pk::get_year() >= (person_p.birth + 노년나이_조운))
											{person_p.face = 1605;}
									}
							}
					}
					// 조인
					if (person_p.get_id() == 무장_조인) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_조인;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_조인 + 고위_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_조인;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_조인 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_조인 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_조인 + 고위노년_초상화;}
									}
							}
					}
					// 조홍
					if (person_p.get_id() == 무장_조홍) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_조홍;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_조홍 + 고위_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_조홍;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_조홍 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_조홍 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_조홍 + 고위노년_초상화;}
									}
							}
					}
					// 주유
					if (person_p.get_id() == 무장_주유) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_주유;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_주유 + 고위_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_주유;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_주유 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_주유 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_주유 + 고위노년_초상화;}
									}
							}
					}
					// 태사자
					if (person_p.get_id() == 무장_태사자) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_태사자;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_태사자 + 고위_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_태사자;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_태사자 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_태사자 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_태사자 + 고위노년_초상화;}
									}
							}
					}
					
					// 하후돈
					if (person_p.get_id() == 무장_하후돈) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							// person_p.face = 초상화_하후돈;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_하후돈 + 고위_초상화;
									}
							}
							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									
											// 하후돈 양안
											if (pk::get_year() < (person_p.birth + 나이_하후돈독안))
											{person_p.face = 초상화_하후돈;}
											// 하후돈 독안
											if (pk::get_year() >= (person_p.birth + 나이_하후돈독안))
											{person_p.face = 초상화_하후돈 + 노년_초상화;}
											// 하후돈 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 1606;}
											
									
									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_하후돈 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_하후돈 + 고위노년_초상화;}
									}
							}
					}							
				
					// 하후연
					if (person_p.get_id() == 무장_하후연) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_하후연;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_하후연 + 고위_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_하후연;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_하후연 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_하후연 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_하후연 + 고위노년_초상화;}
									}
							}
					}
					// 허저
					if (person_p.get_id() == 무장_허저) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_허저;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_허저 + 고위_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_허저;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_허저 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_허저 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_허저 + 고위노년_초상화;}
									}
							}
					}
					// 황개
					if (person_p.get_id() == 무장_황개) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_황개 + 노년_초상화;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_황개 + 고위노년_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_황개;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_황개 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_황개 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_황개 + 고위노년_초상화;}
									}
							}
					}
					// 황충
					if (person_p.get_id() == 무장_황충) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_황충 + 노년_초상화;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_황충 + 고위노년_초상화;
									}
							}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_황충;}

									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_황충 + 노년_초상화;}

									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_황충 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_황충 + 고위노년_초상화;}
									}
							}
					}
					// 손권
					if (person_p.get_id() == 무장_손권) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
								{person_p.face = 초상화_손권;
								if ((person_p.mibun == 신분_군주) and (세력_손권.title <= 작위_왕))
									{person_p.face = 초상화_손권 + 고위_초상화;}
								}
							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 청년나이) and person_p.mibun != 신분_군주)
									{person_p.face = 1604;}
									// 손권 중년
									if (pk::get_year() >= (person_p.birth + 청년나이) and pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_손권;}
									else if (person_p.mibun == 신분_군주 and pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_손권;}
									// 손권 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_손권 + 노년_초상화;}
									if ((person_p.mibun == 신분_군주) and (세력_손권.title <= 작위_왕))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_손권 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_손권 + 고위노년_초상화;}
									}
							}
					}
					// 원술
					if (person_p.get_id() == 무장_원술) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
								{person_p.face = 초상화_원술;
								if ((person_p.mibun == 신분_군주) and (세력_원술.title <= 작위_왕))
									{person_p.face = 초상화_원술 + 고위_초상화;}
								}
							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_원술;}
									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_원술 + 노년_초상화;}
									if ((person_p.mibun == 신분_군주) and (세력_원술.title <= 작위_왕))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_원술 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_원술 + 고위노년_초상화;}
									}
							}
					}
					// 유비
					if (person_p.get_id() == 무장_유비) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{person_p.face = 초상화_유비;
							if ((person_p.mibun == 신분_군주) and (세력_유비.title <= 작위_왕))
								{person_p.face = 초상화_유비 + 고위_초상화;}
							}
							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 청년
									if (pk::get_year() < (person_p.birth + 청년나이))
									{person_p.face = 1600;}
								
									// 중년
									if (pk::get_year() >= (person_p.birth + 청년나이) and pk::get_year() < (person_p.birth + 노년나이))
									{
										if (person_p.mibun == 신분_일반)
										{
											if ((person_p.kouseki < 10000) and (person_p.rank > 64))
											{person_p.face = 1600;}
										
											if ((person_p.kouseki >= 10000) and (person_p.rank <= 64))
											{person_p.face = 초상화_유비;}
										}
										
										if (person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독)
										{
											
											if (세력_유비.title > 작위_주자사)
											{person_p.face = 1600;}
										
											if ((세력_유비.title <= 작위_주자사) and (세력_유비.title > 작위_왕))
											{person_p.face = 초상화_유비;}
										
											if (세력_유비.title <= 작위_왕)
											{person_p.face = 초상화_유비 + 고위_초상화;}
										}
									}					
								
									// 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{
										if (person_p.mibun == 신분_일반)
										{
											if ((person_p.kouseki < 10000) and (person_p.rank > 64))
											{person_p.face = 1601;}
										
											if ((person_p.kouseki >= 10000) and (person_p.rank <= 64))
											{person_p.face = 초상화_유비 + 노년_초상화;}
										}
										
										if (person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독)
										{
											
											if (세력_유비.title > 작위_주자사)
												{person_p.face = 1601;}
											
											if ((세력_유비.title <= 작위_주자사) and (세력_유비.title > 작위_왕))
												{person_p.face = 초상화_유비 + 노년_초상화;}
											
											if (세력_유비.title <= 작위_왕)
											{person_p.face = 초상화_유비 + 고위노년_초상화;}
										}
										
									}
							}
					}
					// 조비
					if (person_p.get_id() == 무장_조비) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
								{person_p.face = 초상화_조비;
								if ((person_p.mibun == 신분_군주) and (세력_조비.title <= 작위_왕))
									{person_p.face = 초상화_조비 + 고위_초상화;}
								}
							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 일반
									if (pk::get_year() < (person_p.birth + 노년나이))
									{person_p.face = 초상화_조비;}
									// 일반 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{person_p.face = 초상화_조비 + 노년_초상화;}
									if ((person_p.mibun == 신분_군주) and (세력_조비.title <= 작위_왕))
									{
											// 고위
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_조비 + 고위_초상화;}
											// 고위 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_조비 + 고위노년_초상화;}
									}
							}
					}
					// 조조
					if (person_p.get_id() == 무장_조조) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
								{person_p.face = 초상화_조조;
								if ((person_p.mibun == 신분_군주) and (세력_조조.title <= 작위_왕))
									{person_p.face = 초상화_조조 + 고위_초상화;}
								}
							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									// 청년
									if (pk::get_year() < (person_p.birth + 청년나이))
									{person_p.face = 1602;}
								
									// 중년
									if (pk::get_year() >= (person_p.birth + 청년나이) and pk::get_year() < (person_p.birth + 노년나이))
									{
										if (person_p.mibun == 신분_일반)
										{
											{person_p.face = 초상화_조조;}
										}
										
										if (person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독)
										{
											if ((세력_조조.title <= 작위_주자사) and (세력_조조.title > 작위_왕))
											{person_p.face = 초상화_조조;}
										
											if (세력_조조.title <= 작위_왕)
											{person_p.face = 초상화_조조 + 고위_초상화;}
										}
									}					
								
									// 노년
									if (pk::get_year() >= (person_p.birth + 노년나이))
									{
										if (person_p.mibun == 신분_일반)
										{
											if ((person_p.kouseki < 10000) and (person_p.rank > 64))
											{person_p.face = 1603;}
										
											if ((person_p.kouseki >= 10000) and (person_p.rank <= 64))
											{person_p.face = 초상화_조조 + 노년_초상화;}
										}
										
										if (person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독)
										{
											
											if (세력_조조.title > 작위_주자사)
												{person_p.face = 1603;}
											
											if ((세력_조조.title <= 작위_주자사) and (세력_조조.title > 작위_왕))
												{person_p.face = 초상화_조조 + 노년_초상화;}
											
											if (세력_조조.title <= 작위_왕)
											{person_p.face = 초상화_조조 + 고위노년_초상화;}
										}
										
									}
							}
					}
					// 조예
					if (person_p.get_id() == 무장_조예) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
								{	person_p.face = 초상화_조예;
									if ((person_p.mibun == 신분_군주) and (세력_조예.title <= 작위_왕))
									{person_p.face = 초상화_조예 + 고위_초상화;}
								}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									person_p.face = 초상화_조예;

									if ((person_p.mibun == 신분_군주) and (세력_조예.title <= 작위_왕))
									{
											// 고위
											{person_p.face = 초상화_조예 + 고위_초상화;}
									}
							}
					}
					// 유선
					if (person_p.get_id() == 무장_유선) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{	person_p.face = 초상화_유선;
								if ((person_p.mibun == 신분_군주) and (세력_유선.title <= 작위_왕))
									{person_p.face = 초상화_유선 + 고위_초상화;}
							}
							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									person_p.face = 초상화_유선;

									if ((person_p.mibun == 신분_군주) and (세력_유선.title <= 작위_왕))
									{
											// 고위
											{person_p.face = 초상화_유선 + 고위_초상화;}
									}
							}
					}
					// 관평
					if (person_p.get_id() == 무장_관평) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_관평;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_관평 + 고위_초상화;
									}
					}
							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									person_p.face = 초상화_관평;


									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											{person_p.face = 초상화_관평 + 고위_초상화;}
									}
							}
					}
					// 이전
					if (person_p.get_id() == 무장_이전) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_이전;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_이전 + 고위_초상화;
									}
					}
							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									person_p.face = 초상화_이전;


									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											{person_p.face = 초상화_이전 + 고위_초상화;}
									}
							}
					}
					// 축융
					if (person_p.get_id() == 무장_축융) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{
							person_p.face = 초상화_축융;
							if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											person_p.face = 초상화_축융 + 고위_초상화;
									}
					}
							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									person_p.face = 초상화_축융;


									if ((person_p.kouseki >= 공적비교) and (person_p.rank <= 관직조건 or person_p.mibun == 신분_군주 or person_p.mibun == 신분_도독))
									{
											// 고위
											{person_p.face = 초상화_축융 + 고위_초상화;}
									}
							}
					}
					// 공손찬
					if (person_p.get_id() == 무장_공손찬) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{person_p.face = 초상화_공손찬;}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									
											// 일반
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_공손찬;}
											// 일반 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_공손찬 + 노년_초상화;}
											
									
							}
					}
					// 견씨
					if (person_p.get_id() == 무장_견씨) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{person_p.face = 초상화_견씨;}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									
											// 일반
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_견씨;}
											// 일반 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_견씨 + 노년_초상화;}
											
									
							}
					}
					// 마등
					if (person_p.get_id() == 무장_마등) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{person_p.face = 초상화_마등;}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									
											// 일반
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_마등;}
											// 일반 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_마등 + 노년_초상화;}
											
									
							}
					}
					// 유표
					if (person_p.get_id() == 무장_유표) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{person_p.face = 초상화_유표;}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									
											// 일반
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_유표;}
											// 일반 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_유표 + 노년_초상화;}
											
									
							}
					}
					// 장각
					if (person_p.get_id() == 무장_장각) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{person_p.face = 초상화_장각;}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									
											// 일반
											if (pk::get_year() < (person_p.birth + 노년나이))
											{person_p.face = 초상화_장각;}
											// 일반 노년
											if (pk::get_year() >= (person_p.birth + 노년나이))
											{person_p.face = 초상화_장각 + 노년_초상화;}
											
									
							}
					}
					// 초선
					if (person_p.get_id() == 무장_초선) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{person_p.face = 초상화_초선;}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									
											// 일반
											if (pk::get_year() < (person_p.birth + 노년나이_여))
											{person_p.face = 초상화_초선;}
											// 일반 노년
											if (pk::get_year() >= (person_p.birth + 노년나이_여))
											{person_p.face = 초상화_초선 + 노년_초상화;}
											
									
							}
					}
					// 서씨
					if (person_p.get_id() == 무장_서씨) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{person_p.face = 초상화_서씨;}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									
											// 일반
											if (pk::get_year() < (person_p.birth + 노년나이_여))
											{person_p.face = 초상화_서씨;}
											// 일반 노년
											if (pk::get_year() >= (person_p.birth + 노년나이_여))
											{person_p.face = 초상화_서씨 + 노년_초상화;}
											
									
							}
					}
					// 견씨
					if (person_p.get_id() == 무장_견씨) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{person_p.face = 초상화_견씨;}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									
											// 일반
											if (pk::get_year() < (person_p.birth + 노년나이_여))
											{person_p.face = 초상화_견씨;}
											// 일반 노년
											if (pk::get_year() >= (person_p.birth + 노년나이_여))
											{person_p.face = 초상화_견씨 + 노년_초상화;}
											
									
							}
					}
					// 변씨
					if (person_p.get_id() == 무장_변씨) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{person_p.face = 초상화_변씨;}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									
											// 일반
											if (pk::get_year() < (person_p.birth + 노년나이_여))
											{person_p.face = 초상화_변씨;}
											// 일반 노년
											if (pk::get_year() >= (person_p.birth + 노년나이_여))
											{person_p.face = 초상화_변씨 + 노년_초상화;}
											
									
							}
					}
					// 왕원희
					if (person_p.get_id() == 무장_왕원희) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{person_p.face = 초상화_왕원희;}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									
											// 일반
											if (pk::get_year() < (person_p.birth + 노년나이_여))
											{person_p.face = 초상화_왕원희;}
											// 일반 노년
											if (pk::get_year() >= (person_p.birth + 노년나이_여))
											{person_p.face = 초상화_왕원희 + 노년_초상화;}
											
									
							}
					}
					// 장씨
					if (person_p.get_id() == 무장_장씨) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{person_p.face = 초상화_장씨;}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									
											// 일반
											if (pk::get_year() < (person_p.birth + 노년나이_여))
											{person_p.face = 초상화_장씨;}
											// 일반 노년
											if (pk::get_year() >= (person_p.birth + 노년나이_여))
											{person_p.face = 초상화_장씨 + 노년_초상화;}
											
									
							}
					}
					// 마운록
					if (person_p.get_id() == 무장_마운) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{person_p.face = 초상화_마운;}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									
											// 일반
											if (pk::get_year() < (person_p.birth + 노년나이_여))
											{person_p.face = 초상화_마운;}
											// 일반 노년
											if (pk::get_year() >= (person_p.birth + 노년나이_여))
											{person_p.face = 초상화_마운 + 노년_초상화;}
											
									
							}
					}
					// 오국태
					if (person_p.get_id() == 무장_오국태) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{person_p.face = 초상화_오국태;}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									
											// 일반
											if (pk::get_year() < (person_p.birth + 노년나이_여))
											{person_p.face = 초상화_오국태;}
											// 일반 노년
											if (pk::get_year() >= (person_p.birth + 노년나이_여))
											{person_p.face = 초상화_오국태 + 노년_초상화;}
											
									
							}
					}								
					// 황월영
					if (person_p.get_id() == 무장_황월영) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{person_p.face = 초상화_황월영;}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									
											// 일반
											if (pk::get_year() < (person_p.birth + 노년나이_여))
											{person_p.face = 초상화_황월영;}
											// 일반 노년
											if (pk::get_year() >= (person_p.birth + 노년나이_여))
											{person_p.face = 초상화_황월영 + 노년_초상화;}
											
									
							}
					}
					// 관은병
					if (person_p.get_id() == 무장_관은병) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{person_p.face = 초상화_관은병;}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									
											// 일반
											if (pk::get_year() < (person_p.birth + 노년나이_여))
											{person_p.face = 초상화_관은병;}
											// 일반 노년
											if (pk::get_year() >= (person_p.birth + 노년나이_여))
											{person_p.face = 초상화_관은병 + 노년_초상화;}
											
									
							}
					}	
					// 여령기
					if (person_p.get_id() == 무장_여영기) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{person_p.face = 초상화_여영기;}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									
											// 일반
											if (pk::get_year() < (person_p.birth + 노년나이_여))
											{person_p.face = 초상화_여영기;}
											// 일반 노년
											if (pk::get_year() >= (person_p.birth + 노년나이_여))
											{person_p.face = 초상화_여영기 + 노년_초상화;}
											
									
							}
					}
					// 대교
					if (person_p.get_id() == 무장_대교) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{person_p.face = 초상화_대교;}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									
											// 일반
											if (pk::get_year() < (person_p.birth + 노년나이_여))
											{person_p.face = 초상화_대교;}
											// 일반 노년
											if (pk::get_year() >= (person_p.birth + 노년나이_여))
											{person_p.face = 초상화_대교 + 노년_초상화;}
											
									
							}
					}
					// 소교
					if (person_p.get_id() == 무장_소교) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{person_p.face = 초상화_소교;}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									
											// 일반
											if (pk::get_year() < (person_p.birth + 노년나이_여))
											{person_p.face = 초상화_소교;}
											// 일반 노년
											if (pk::get_year() >= (person_p.birth + 노년나이_여))
											{person_p.face = 초상화_소교 + 노년_초상화;}
											
									
							}
					}
					// 추씨
					if (person_p.get_id() == 무장_추씨) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{person_p.face = 초상화_추씨;}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									
											// 일반
											if (pk::get_year() < (person_p.birth + 노년나이_여))
											{person_p.face = 초상화_추씨;}
											// 일반 노년
											if (pk::get_year() >= (person_p.birth + 노년나이_여))
											{person_p.face = 초상화_추씨 + 노년_초상화;}
											
									
							}
					}
					// 채염
					if (person_p.get_id() == 무장_채염) 
					{
							// 집결류 시나리오 고정 초상화 (나이무시)
							if (pk::get_scenario().no == 7 or pk::get_scenario().no == 13)
							{person_p.face = 초상화_채염;}

							else if (pk::get_scenario().no != 7 and pk::get_scenario().no != 13)
							{
									
											// 일반
											if (pk::get_year() < (person_p.birth + 노년나이_여))
											{person_p.face = 초상화_채염;}
											// 일반 노년
											if (pk::get_year() >= (person_p.birth + 노년나이_여))
											{person_p.face = 초상화_채염 + 노년_초상화;}
											
									
							}
					}					
					// 장수정보 끝

							

				}
			}
		}
    }
	Main main;
}