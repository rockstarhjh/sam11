/*
@만든이: 유령기
@설명: 보물 관리 2017/12/09

@수정자: 기마책사
@설명: PK2.1용으로 언어변환 '18.12.22

@수정자: Gistar
@설명: 소유주 대입 방식에서 cmd를 사용하도록 변경
*/

/* 
	옥새나 동작은 고려하지 않았으므로 고유 보물로 지정하지 말것....
*/

bool 유령기_고유_보물_적용여부 = true; // 고유보물을 적용할지 여부
bool 유령기_군주_보물_랜덤여부 = true; // 군주 본인이 가질 보물 선택시 랜덤하게 선정할지 여부, false면 종류별로 가치가 가장 높은 보물들을 가진다.
bool 유령기_고유_보물_몰수여부 = true; // 고유장수가 세력 내에 있고 고유보물을 세력내 타 무장이 가지고 있을때, 몰수해서 고유장수에게 줄건지의 여부
bool 유령기_사용자_조건_사용여부 = false; // 조건 체크시 사용자가 만든 조건을 사용할 것인지 여부
bool 유령기_로그_파일_표시 = false; // core.log에 보물 분배 로그를 표시합니다.
bool 유령기_로그_화면_표시 = true; // 화면 작은 창에 보물 분배 로그를 표시합니다.
bool 유령기_로그_메세지표시 = false; // 화면 메세지 창에 보물 분배 로그를 표시합니다.

int 유령기_군주_창극_최소 = 80;
int 유령기_군주_검_무력_최소 = 50;
int 유령기_군주_검_통무_최소 = 80;
int 유령기_군주_활_최소 = 70;
int 유령기_군주_암기_최소 = 70;
int 유령기_군주_서책_최소 = 70;
int 유령기_군주_명마_무력_최소 = 0;
int 유령기_군주_명마_통무지매_최소 = 0;

int 유령기_무장_창극_최소 = 80;
int 유령기_무장_검_무력_최소 = 80;
int 유령기_무장_검_통무_최소 = 150;
int 유령기_무장_암기_최소 = 70;
int 유령기_무장_활_최소 = 70;
int 유령기_무장_서책_최소 = 75;
int 유령기_무장_명마_무력_최소 = 85;
int 유령기_무장_명마_통무지매_최소 = 300;

int 유령기_창극_가산_계수 = 1;
int 유령기_검_무력_가산_계수 = 2;
int 유령기_검_통무_가산_계수 = 4;
int 유령기_암기_가산_계수 = 3;
int 유령기_활_가산_계수 = 2;
int 유령기_서책_가산_계수 = 3;
int 유령기_명마_무력_가산_계수 = 1;
int 유령기_명마_통무지매_가산_계수 = 5;
int 유령기_적성S_가산점 = 6;

int 능력가산기준_최대 = 100;
int 군주관계_가산점 = 12;

int 가산점_난수 = 160;

int 유령기_비교_최소수치 = -100000000;


/*
	사용자 조건 기준
	
	1. 군주조건여부 - 0 일경우 군주조건, 1일경우 일반조건
	2. 보물종류 - 보물종류 번호. (pk_enums.h 보물종류Id 참조), 보물종류를 설정하지 않으려면 -1로 입력.
	3. 보물번호 - 보물 번호.  (pk_enums.h 보물Id 참조), 보물번호를 설정하지 않으려면 -1로 입력.
	4. 능력최대치
	5. 통솔최소기준 
	6. 통솔가중치 - 수치 계산시 통솔가중치
	7. 무력최소기준 
	8. 무력가중치 - 수치 계산시 무력가중치
	9. 지력최소기준
	10. 지력가중치 - 수치 계산시 지력가중치
	11. 정치최소기준
	12. 정치가중치 - 수치 계산시 정치가중치
	13. 매력최소기준
	14. 매력가중치 - 수치 계산시 매력가중치
	15. 적성최대치
	16. 창병적성최소기준 - (pk_enums.h 적성Id 참조)
	17. 창병적성가중치
	18. 극병적성최소기준 - (pk_enums.h 적성Id 참조)
	19. 극병적성가중치
	20. 노병적성최소기준 - (pk_enums.h 적성Id 참조)
	21. 노병적성가중치
	22. 기병적성최소기준 - (pk_enums.h 적성Id 참조)
	23. 기병적성가중치
	24. 병기적성최소기준 - (pk_enums.h 적성Id 참조)
	25. 병기적성가중치
	26. 수군적성최소기준 - (pk_enums.h 적성Id 참조)
	27. 수군적성가중치
	28. 충성최대치
	29. 충성최소기준
	30. 충성도가중치
	31. 공적최대치
	32. 공적최소기준
	33. 공적가중치
	34. 부모자식가중치
	35. 배우자가중치
	36. 혈연가중치
	37. 의형제가중치
	38. 군주친애가중치
	39. 가산점난수

	
	무장별 수치비교값 계산공식 =
		(능력*능력가중치)의 합 + (적성*적성가중치)의 합 + 충성*충성가중치 + 공적*공적가중치 + 부모자식가중치 + 배우자가중치 + 혈연가중치 + 의형제가중치 + 군주친애가중치 + 랜덤(가산점난수)

	우선권 계산시 각 능력들은 능력최대치를 넘으면 능력최대치로 계산합니다 다른 수치들의 최대치들도 마찬가지.
	각 최소치를 만족시키는 대상자중 수치계산결과가 가장 높게 나오는 사람에게 보물을 준다. 군주의 경우 최소치만 만족시키면 됨. 물론 고유보물은 이 조건들과 상관 없다.
	
	첫번째로 컴퓨터는 개별 보물번호에 대해서 조건을 검색하고 보물번호와 일치하는 조건이 있을 경우 조건공식을 적용해 대상자들의 수치를 계산해서 보물을 수여한다.
	두번째로 컴퓨터는 보물종류별로 맞는 조건이 있는지 검색해서 일치하는 조건이 있을경우 조건공식을 적용해 대상자들의 수치를 계산해서 보물을 수여한다.
	세번째로 사용자 조건이 없을 경우 기본조건으로 계산해서 수여한다.
	
	계산되는 수치를 비교할때 젤 처음에 최고수치를 가진 무장이 없을 경우 유령기_비교_최소수치와 비교하므로 유령기_비교_최소수치보다 낮은 값이 나온다면 보물을 분배받을수 없다.

*/

array<array<int>> 사용자_조건_기준 =
{
	// 예제수치의 줄바꿈은 알아보기 쉽게 10단위로 나눴습니다.
		
	// 예제 1. 암기를 통솔 80, 지력 90 이상인 무장들을 대상으로, 무력가중치 -1에, 난수 300을 줘서 통솔 지력은 높지만 무력이 낮은 제갈량같은 사람들 위주로 주게 해보자....
	{ 1, 보물종류_암기, -1, 100, 80, 0, 0, -1, 90, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 300},
		
	// 예제 2. 손자병법서를 최소조건없이 군주의 친애장수는 가중치를 30을 주고 난수 200으로 줘보자.
	{ 1, -1, 보물_손자병법, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 30, 200},	

	// 예제 3. 군주의 활 최소조건을 노병 적성 B로 만들어보자.
	{ 0, 보물종류_활, -1, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 적성_B, 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 0},
		
	// 예제 4. 서책을 통솔력 70 이상의 무장에 통솔 가중치 1과 난수 300을 줘서 통솔력 높은 무장 위주로 받게 해보자....
	{ 1, 보물종류_서책, -1, 100, 70, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 300},
		
	// 예제 5. 긴무기들을 무력 85 이상의 무장에 지력 가중치 -1과 난수 300을 줘서 무력은 높지만 돌대가리인 넘들 위주로 받게 해보자....
	{ 1, 보물종류_긴무기, -1, 100, 0, 0, 85, 0, 0, -1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 300}
};

/*
	각 보물의 고유무장 목록. 휘하에 해당 보물과 무장들이 존재하면 몰수해서라도 고유장수에게 분배해준다. 단 군주의 혐오장수일 경우엔 안준다.
*/
array<array<int>> 유령기_고유_보물 =
{
	
	{ 보물_적토마, 무장_여포, 무장_관우 },
	{ 보물_적로, 무장_유비 },
	{ 보물_조황비전, 무장_조조 },
	{ 보물_절영, 무장_조조 },
	{ 보물_대완마1, 무장_왕쌍 },
	{ 보물_대완마2 },
	{ 보물_대완마3 },
	{ 보물_칠성보도 },
	{ 보물_의천검, 무장_조조 },
	{ 보물_청강검, 무장_조운 },
	{ 보물_자웅일대검, 무장_유비 },
	{ 보물_방천화극, 무장_여포 },
	{ 보물_청룡언월도, 무장_관우 },
	{ 보물_사모, 무장_장비 },
	{ 보물_유성추, 무장_왕쌍 },
	{ 보물_비도1 },
	{ 보물_비도2, 무장_축융 },
	{ 보물_단극1, 무장_전위 },
	{ 보물_단극2 },
	{ 보물_수극1, 무장_태사자 },
	{ 보물_수극2, 무장_손책 },
	{ 보물_철쇄, 무장_감녕 },
	{ 보물_양유기의활 },
	{ 보물_이광의활 },
	{ 보물_단궁1 },
	{ 보물_단궁2 },
	{ 보물_동호비궁1 },
	{ 보물_동호비궁2 },
	{ 보물_맥궁1 },
	{ 보물_맥궁2 },
	{ 보물_손자병법, 무장_손견, 무장_손책, 무장_손권, 무장_손상향 },
	{ 보물_병법24편, 무장_제갈량 },
	{ 보물_맹덕신서, 무장_조조 },
	{ 보물_육도, 무장_여상_태공망 },
	{ 보물_삼략, 무장_여상_태공망 },
	{ 보물_오자, 무장_오기 },
	{ 보물_위료자 },
	{ 보물_전국책 },
	{ 보물_사마법 },
	{ 보물_묵자 },
	{ 보물_태평요술서, 무장_장각 }
};

/*
	각 보물의 고유보조무장 목록. 특별히 해당 무장들에게 보물을 주진 않지만, 이미 보물을 가지고 있다면 고유무장이 뒤늦게 들어와도 몰수당하지 않는다.
*/
array<array<int>> 유령기_고유_보물_보조 =
{
	
	{ 보물_적토마, 무장_여영기, 무장_관흥 },
	{ 보물_적로, 무장_유선 },
	{ 보물_조황비전, 무장_조비 },
	{ 보물_절영, 무장_조비 },
	{ 보물_칠성보도, 무장_왕윤 },
	{ 보물_의천검, 무장_조비 },
	{ 보물_청강검, 무장_하후은, 무장_조비 },
	{ 보물_자웅일대검, 무장_유선 },
	{ 보물_방천화극, 무장_송헌, 무장_여영기 },
	{ 보물_청룡언월도, 무장_관흥 },
	{ 보물_사모, 무장_장포 },
	{ 보물_맹덕신서, 무장_조비, 무장_조식 },
	{ 보물_태평요술서, 무장_장보 }
};


유령기_보물관리 item_manage;	// 보물 소유기록

class 유령기_보물관리
{
	
	유령기_보물관리()
	{
		if( !유령기_고유_보물_적용여부 )
		{
			유령기_고유_보물.resize(0);
			유령기_고유_보물_보조.resize(0);
		}
	
		pk::bind(108, pk::trigger108_t(onNewday));
		pk::bind(111, pk::trigger111_t(onTurnEnd));
		pk::bind(111, pk::trigger111_t(onTurnstart));
		pk::bind(112, pk::trigger112_t(onTurnEnd));

	}

	void onNewday()
	{
		if (pk::get_month() % 2 == 1)
			유령기_잉여보물몰수();
	}
	
	void onTurnstart(pk::force@ force)
	{
		if (pk::is_campaign()) return;
		if (!pk::is_alive(force)) return;
		if (!pk::is_normal_force(force)) return;
		if (force.is_player()) return;

		int kunshu_id = force.kunshu;
		int force_id = force.get_id();

		//군주가 가지고 있을 보물 배열 생성
		array<int> kunshu_item_id = 유령기_군주보물선정(kunshu_id);

/*		
		for (int i = 보물종류_명마; i < 보물종류_서책; i++)
		{
			kunshu_item_id[i] = 유령기_군주보물선정(kunshu_id);
		}
*/

		for (int i = 0; i < 보물_끝; i++)
		{
			pk::item@ item = pk::get_item(i);
			pk::person@ kunshu = pk::get_person(force.kunshu);

			if (!pk::is_alive(item)) continue;

			int select = -1;

			//세력 내에 보물이 없으면 패스
			if (!보물보유확인(force_id, item))
				continue;

			pk::person@ person = pk::get_person(item.owner);
			pk::building@ build = pk::get_building(person.service);

			//원 보물 소유자가 부대에 출진 중일 경우 패스
			if (person.location > 86)
				continue;

			//보물의 소유자가 해당 보물을 보유하기 적합할 경우 패스(군주일 경우 해당 보물이 고유보물, 고유보물보조여야 이 조건에 맞음)
			if (유령기_보물_소유자적합(person, item))
				continue;

			// 보물이 군주 걸로 찜되어 있는거면 넘어감.
			bool kunshu_flag = false;
			for( uint j=0; j<kunshu_item_id.length; j++)
			{
				if(kunshu_item_id[j] == item.get_id())
					kunshu_flag = true;
			}
		
			if( kunshu_flag ) continue;

			select = 유령기_보물분배( kunshu_id, item );		//기존 알고리즘대로 수여자 선정

			if (select == -1) 					//선정된 수여자가 없을 경우 패스
			{	
				string s = "보물 <"+pk::decode(item.name)+">, <"+pk::decode(pk::get_name(kunshu))+"> 세력에선 대상자 없음.";

            			if( 유령기_로그_파일_표시) pk::info(s);
            			if( 유령기_로그_화면_표시) pk::history_log(pk::get_building(pk::get_person(item.owner).service).pos, -1, pk::encode(s));
            
            			if( 유령기_로그_메세지표시) pk::message_box(pk::encode(s));
				continue;
			}

			if (person.get_id() == select)			//선정된 수여자가 기존 보유자와 같을 경우 패스
			{
				continue;
			}

			pk::person@ person2 = pk::get_person(select);
			pk::award_cmd_info cmd;		//수여정보 명령 생성
			@cmd.item = item;
			@cmd.base = build;
			@cmd.target = person2;
			int loy1 = 0;
			int loy2 = 0;

			if (person.mibun != 신분_군주)
				loy1 = person.loyalty;
			if (person2.mibun != 신분_군주)
				loy2 = person2.loyalty;

			pk::command(cmd);		//아이템 수여

			if (person.mibun != 신분_군주)
				person.loyalty = loy1;
			if (person2.mibun != 신분_군주)
				person2.loyalty = loy2;

			string s = "무장 <"+pk::decode(pk::get_name(pk::get_person(select)))+">, <"+pk::decode(pk::get_name(person))+">에게서 보물 <"+pk::decode(item.name)+"> 받음";
                
                		if( 유령기_로그_파일_표시) pk::info(s);
                		if( 유령기_로그_화면_표시) pk::history_log(pk::get_building(pk::get_person(item.owner).service).pos, -1, pk::encode(s));
                
               	 	if( 유령기_로그_메세지표시) pk::message_box(pk::encode(s));
		}
	}

	void onTurnEnd(pk::force@ force)
	{
		if (pk::is_campaign()) return;
		if (!pk::is_alive(force)) return;
		if (!pk::is_normal_force(force)) return;
		if (force.is_player()) return;

		int kunshu_id = force.kunshu;
		pk::item@ item;
            	
		if( pk::is_alive(force) and pk::is_normal_force(force) and pk::is_alive(pk::get_person(force.kunshu)) and ( kunshu_id == 660 or kunshu_id == 98 or kunshu_id == 432 or kunshu_id == 289 or kunshu_id == 403 or kunshu_id == 370 ) )
            	{
			int item_user = AI_repair_item_user( kunshu_id );
			if (kunshu_id == 660)
			{
				int bang = 11;
				@item = pk::get_item(bang);
			}
			else if (kunshu_id == 98)
			{
				int chung = 12;
				@item = pk::get_item(chung);
			}
			else if (kunshu_id == 432)
			{
				int samo = 13;
				@item = pk::get_item(samo);
			}
			else if (kunshu_id == 289)
			{
				int bub = 31;
				@item = pk::get_item(bub);
			}
			else if (kunshu_id == 403)
			{
				int tae = 40;
				@item = pk::get_item(tae);
			}
			else if (kunshu_id == 370)
			{
				int suu = 20;
				@item = pk::get_item(suu);
			}

			if (item_user != -1)
			{
				pk::person@ person = pk::get_person(item.owner);
				pk::person@ person2 = pk::get_person(kunshu_id);
				pk::building@ build = pk::get_building(person.service);

				pk::award_cmd_info cmd;
				@cmd.item = item;
				@cmd.base = build;
				@cmd.target = person2;
				int loy1 = 0;
				int loy2 = 0;

				if (person.mibun != 신분_군주)
					loy1 = person.loyalty;
				if (person2.mibun != 신분_군주)
					loy2 = person2.loyalty;

				pk::command(cmd);

				if (person.mibun != 신분_군주)
					person.loyalty = loy1;
				if (person2.mibun != 신분_군주)
					person2.loyalty = loy2;
			}
       		}
	}
}

bool 보물보유확인(int force_id, pk::item@ item)
{
	//파기 보물이나 미등장 보물은 미보유로 리턴
	if (item.status == 보물상태_파기 or item.status == 보물상태_미등장)
		return false;

	pk::person@ person = pk::get_person(item.owner);

	if (person.get_force_id() != force_id)
		return false;
	else
		return true;

	return false;
}

int AI_repair_item_user( int kunshu_id )
{
	pk::person@ kunshu = pk::get_person(kunshu_id);

	//방천화극, 병법24편, 청룡언월도, 장팔사모의 강제 소유자 변경(버그수정)
	if (kunshu_id == 660)
	{
		int bang = 11;
		pk::item@ item = pk::get_item(bang);

		if (item.owner != kunshu_id and (pk::get_person(item.owner).get_force_id() == kunshu.get_force_id()) and item.status == 보물상태_등장)
			return kunshu_id;
	}

	if (kunshu_id == 98)
	{
		int chung = 12;
		pk::item@ item = pk::get_item(chung);

		if (item.owner != kunshu_id and (pk::get_person(item.owner).get_force_id() == kunshu.get_force_id()) and item.status == 보물상태_등장)
			return kunshu_id;
	}

	if (kunshu_id == 432)
	{
		int samo = 13;
		pk::item@ item = pk::get_item(samo);

		if (item.owner != kunshu_id and (pk::get_person(item.owner).get_force_id() == kunshu.get_force_id()) and item.status == 보물상태_등장)
			return kunshu_id;
	}

	if (kunshu_id == 289)
	{
		int bub = 31;
		pk::item@ item = pk::get_item(bub);

		if (item.owner != kunshu_id and (pk::get_person(item.owner).get_force_id() == kunshu.get_force_id()) and item.status == 보물상태_등장)
			return kunshu_id;
	}

	if (kunshu_id == 403)
	{
		int tae = 40;
		pk::item@ item = pk::get_item(tae);

		if (item.owner != kunshu_id and (pk::get_person(item.owner).get_force_id() == kunshu.get_force_id()) and item.status == 보물상태_등장)
			return kunshu_id;
	}

	if (kunshu_id == 370)
	{
		int suu = 20;
		pk::item@ item = pk::get_item(suu);

		if (item.owner != kunshu_id and (pk::get_person(item.owner).get_force_id() == kunshu.get_force_id()) and item.status == 보물상태_등장)
			return kunshu_id;
	}

	return -1;
}



/*
	군주의 보물 선정하기
*/

array<int> 유령기_군주보물선정(int kunshu_id)
{
	pk::person@ kunshu = pk::get_person(kunshu_id);

	array<int> kunshu_item_id = { -1, -1, -1, -1, -1, -1 };
	array<int> kunshu_item_value = { -1, -1, -1, -1, -1, -1 };

	for( int i=0 ; i < 보물_끝 ; i++ )
	{
		pk::item@ item = pk::get_item(i);
		
		// 보물종류가 옥새 이상이면 넘어감
		if( item.type >= 보물종류_옥새 )
			continue;
		
		if( !pk::is_alive(item) or item.status != 보물상태_등장 or !pk::is_alive(pk::get_person(item.owner)) )
			continue;
		
		//  보물이 군주의 것이 아니라면 넘어감.
		if( item.owner != kunshu_id )
			continue;
		
		// 보물이 군주의 소유일 경우.
		
		// 보물이 자세력 내 무장의 고유보물일 경우에는 어차피 나중에 고유장수에게 줄 보물이므로 넘어간다.
		if( 유령기_고유보물_세력체크( item.get_id(), kunshu.get_force_id() ) != -1 )
			continue;
		
		// 군주 본인이 이 보물의 고유무장(or 보조)라면 나중에 처리하게 될 테니 넘어간다.
		if (유령기_고유보물_체크(item.get_id(), kunshu_id))
			continue;
		else if (유령기_고유보물보조_체크(item.get_id(), kunshu_id))
			continue;
		
		int item_value = 유령기_군주_보물_랜덤여부 ? pk::rand(50) : item.value;

		// 1. 개별보물에 대한 군주의 사용자 조건을 체크
		if( 유령기_사용자_조건_사용여부 and 유령기_사용자_조건_체크( item, 0, true ) >= 0 )
		{
			int cond_index = 유령기_사용자_조건_체크( item, 0, true );
			
			//MessageBox().talk(" 군주조건 체크 " + kunshu.name + " " + item.name + " 개별보물 조건 index =" + 유령기_사용자_조건_체크( item, 0, true ));
			
			// 군주가 사용자조건을 만족하고, 보물 가치가 더 높다면....
			if( 유령기_사용자_조건_무장_체크( kunshu, cond_index ) and item_value > kunshu_item_value[item.type] )
			{
				kunshu_item_id[item.type] = item.get_id(); kunshu_item_value[item.type] = item_value;
			}
			continue;	// 우선순위가 낮은 조건들은 넘어간다.
		}
		
		// 2. 보물종류에 대한 군주의 사용자 조건을 체크
		if( 유령기_사용자_조건_사용여부 and 유령기_사용자_조건_체크( item, 1, true ) >= 0 )
		{
			int cond_index = 유령기_사용자_조건_체크( item, 1, true );
			
			//MessageBox().talk(" 군주조건 체크 " + kunshu.name + " " + item.name + " 보물종류 조건 index =" + 유령기_사용자_조건_체크( item, 1, true ));
			
			// 군주가 사용자조건을 만족하고, 보물 가치가 더 높다면....
			if( 유령기_사용자_조건_무장_체크( kunshu, cond_index ) and item_value > kunshu_item_value[item.type] )
			{
				kunshu_item_id[item.type] = item.get_id(); kunshu_item_value[item.type] = item_value;
			}
			
			continue;	// 우선순위가 낮은 조건들은 넘어간다.
		}

		// 3. 기본조건을 체크
		if( item.type == 보물종류_긴무기 and item_value > kunshu_item_value[보물종류_긴무기] and 유령기_보물_창극_조건( kunshu, 유령기_군주_창극_최소, 적성_A ) )
		{
			kunshu_item_id[보물종류_긴무기] = item.get_id(); kunshu_item_value[보물종류_긴무기] = item_value;
		}
	
		// 검류
		if( item.type == 보물종류_검 and item_value > kunshu_item_value[보물종류_검] and 유령기_보물_검_조건( kunshu, 유령기_군주_검_무력_최소, 유령기_군주_검_통무_최소 ) )
		{
			kunshu_item_id[보물종류_검] = item.get_id(); kunshu_item_value[보물종류_검] = item_value;
		}
		
		// 암기류
		if( item.type == 보물종류_암기 and item_value > kunshu_item_value[보물종류_암기] and int(kunshu.stat[무장능력_무력]) >= 유령기_군주_암기_최소 )
		{
			kunshu_item_id[보물종류_암기] = item.get_id(); kunshu_item_value[보물종류_암기] = item_value;
		}
		
		// 활류 ( 군주 본인의 무력 유령기_군주_활_최소 이상에 노병적성 A 이상 or 궁병 계열 특기일 경우 )
		if( item.type == 보물종류_활 and item_value > kunshu_item_value[보물종류_활] and 유령기_보물_활_조건( kunshu, 유령기_군주_활_최소, 적성_A ) )
		{
			kunshu_item_id[보물종류_활] = item.get_id(); kunshu_item_value[보물종류_활] = item_value;
		}
		
		// 서책류 ( 군주 본인의 지력이 유령기_군주_지력_최소 이상인 경우 )
		if( item.type == 보물종류_서책 and item_value > kunshu_item_value[보물종류_서책] and int(kunshu.stat[무장능력_지력]) >= 유령기_군주_서책_최소 )
		{
			kunshu_item_id[보물종류_서책] = item.get_id(); kunshu_item_value[보물종류_서책] = item_value;
		}
		
		//명마류
		if( item.type == 보물종류_명마 and item_value > kunshu_item_value[보물종류_명마] and  유령기_보물_명마_조건( kunshu, kunshu, 유령기_군주_명마_무력_최소, 유령기_군주_명마_통무지매_최소) ) 
		{
			kunshu_item_id[보물종류_명마] = item.get_id(); kunshu_item_value[보물종류_명마] = item_value;
		}
	}

	// 군주의 고유보물을 선정하는 작업.
	for( int i=0 ; i < 보물_끝 ; i++ )
	{
		pk::item@ item = pk::get_item(i);
		
		// 보물종류가 옥새 이상이면 넘어감
		if( item.type >= 보물종류_옥새 )
			continue;
		
		if( !pk::is_alive(item) or item.status != 보물상태_등장 or !pk::is_alive(pk::get_person(item.owner)) )
			continue;
		
		// 보물소유 무장이 일반적인 상태가 아니면 넘어감.
		if( !( pk::get_person(item.owner).mibun >= 신분_군주 and pk::get_person(item.owner).mibun <= 신분_일반 ) )
			continue;
		
		//  보물이 군주 세력장수의 것이 아니라면 넘어감.
		if( !( pk::get_person(item.owner).get_force_id() == kunshu.get_force_id() and item.type < 보물종류_옥새) )
			continue;
		
		// 군주 고유보물일 경우 체크
		if( 유령기_고유보물_체크( item.get_id(), kunshu_id ) and item.owner == kunshu_id )
		{
			kunshu_item_id[item.type] = item.get_id();
			kunshu_item_value[item.type] = item.value;
		}

		if( 유령기_고유보물보조_체크( item.get_id(), kunshu_id ) and item.owner == kunshu_id )
		{
			kunshu_item_id[item.type] = item.get_id();
			kunshu_item_value[item.type] = item.value;
		}
	}

	return kunshu_item_id;
}

/*
	군주가 보물을 분배하는 함수
*/

int 유령기_보물분배( int kunshu_id, pk::item@ item )
{
	pk::person@ kunshu = pk::get_person(kunshu_id);
	
	if( 유령기_고유보물_체크(item.get_id(), item.owner) )
		return -1;
	else if (유령기_고유보물보조_체크(item.get_id(), item.owner))
		return -1;
		
	// 세력내 현재 보물의 소유자가 아닌 고유무장이 있는지 체크
	int unique_id = 유령기_고유보물_세력체크( item.get_id(), kunshu.get_force_id() );
	pk::person@ unique_p = pk::get_person(unique_id);
		
	// 고유무장이 없거나 일반적인 상태가 아니면 넘어감.
	if( unique_id != -1 and pk::is_alive(unique_p) and ( unique_p.mibun >= 신분_군주 and unique_p.mibun <= 신분_일반 ) and unique_p.location <= 86)
	{
		if( !pk::is_dislike(kunshu, unique_id) and 유령기_고유_보물_몰수여부 and item.owner != kunshu_id )
			return unique_id;
		else if ( !pk::is_dislike(kunshu, unique_id) and item.owner == kunshu_id )
			return unique_id;
	}
		
		// 고유보물을 받은 장수가 같은 종류의 보물을 가지고 있다면 군주에게 반납.
		//유령기_보물_반납( unique_id, kunshu_id, item.type );

	
	pk::force@ kunshu_force = pk::get_force(kunshu.get_force_id() ) ;
	pk::array<pk::person@> officers = pk::list_to_array(pk::get_person_list(kunshu_force, pk::mibun_flags(신분_도독, 신분_태수, 신분_일반)));

	int force_id = kunshu.get_force_id();

/*
	for (int i = 0; i < 무장_끝; i++)
	{
		pk::person@ person = pk::get_person(i);
		if (pk::is_alive(person))
		{
			if (person.get_force_id() == force_id && person.mibun != 신분_포로 && person.mibun != 신분_군주)
			{
				officers.add(person);
			}
		}
	}
*/

	int best_person_id = -1;
	int best_person_value = 유령기_비교_최소수치;
		
	//  무장들에 대한 조건 체크.
	for (auto officer = 0; officer < officers.length; officer++)
	{
		if( officers[officer].get_id() == kunshu_id or pk::is_dislike(kunshu, officers[officer].get_id()) ) // 군주 본인이거나 군주의 혐오장수일 경우 넘어감.
			continue;
				
		// 대상 무장이 일반적인 상태가 아니면 넘어감.
		if( !( officers[officer].mibun >= 신분_군주 and officers[officer].mibun <= 신분_일반 ) )
			continue;
		
		if ( officers[officer].location > 86 )
			continue;

		if( 유령기_고유보물_체크(item.get_id(), officers[officer].get_id()) )
			return officers[officer].get_id();

		// 1. 개별보물에 대한 무장의 사용자 조건을 체크
		if( 유령기_사용자_조건_사용여부 and 유령기_사용자_조건_체크( item, 0, false ) >= 0 )
		{
			int cond_index = 유령기_사용자_조건_체크( item, 0, false );
			int officer_value = 유령기_사용자_조건_무장_수치( officers[officer], cond_index );
				
			// 무장이 사용자조건을 만족하고 무장의 사용자조건 수치결과가 현재까지 다른 무장들의 최고수치보다 높다면....
			if( 유령기_사용자_조건_무장_체크( officers[officer], cond_index ) and officer_value > best_person_value )
				{ best_person_id = officers[officer].get_id(); best_person_value = officer_value;}
				
			continue;	// 우선순위가 낮은 조건들은 넘어간다.
		}
			
		// 2. 보물종류에 대한 무장의 사용자 조건을 체크
		if( 유령기_사용자_조건_사용여부 and 유령기_사용자_조건_체크( item, 1, false ) >= 0 )
		{
			int cond_index = 유령기_사용자_조건_체크( item, 1, false );
			int officer_value = 유령기_사용자_조건_무장_수치( officers[officer], cond_index );
				
			// 무장이 사용자조건을 만족하고 무장의 사용자조건 수치결과가 현재까지 다른 무장들의 최고수치보다 높다면....
			if( 유령기_사용자_조건_무장_체크( officers[officer], cond_index ) and officer_value > best_person_value )
				{ best_person_id = officers[officer].get_id(); best_person_value = officer_value;}
				
			continue;	// 우선순위가 낮은 조건들은 넘어간다.
		}
			
		// 3. 기본조건을 체크
		if( 
			( item.type == 보물종류_긴무기 and 유령기_보물_창극_조건( officers[officer], 유령기_무장_창극_최소, 적성_A ) ) 
			or ( item.type == 보물종류_검 and 유령기_보물_검_조건( officers[officer], 유령기_무장_검_무력_최소, 유령기_무장_검_통무_최소 ) ) 
			or ( item.type == 보물종류_암기 and int(officers[officer].stat[무장능력_무력]) >= 유령기_무장_암기_최소 )
			or ( item.type == 보물종류_활 and 유령기_보물_활_조건( officers[officer], 유령기_무장_활_최소, 적성_A ) )
			or ( item.type == 보물종류_서책 and int(officers[officer].stat[무장능력_지력]) >= 유령기_무장_서책_최소 )
			or ( item.type == 보물종류_명마 and 유령기_보물_명마_조건( officers[officer], kunshu, 유령기_무장_명마_무력_최소, 유령기_무장_명마_통무지매_최소) )
		)
		{
			int officer_value = pk::rand(가산점_난수);
				
			// 군주의 혈연, 의형제이거나 친애장수일 경우에는 군주관계_가산점.
			if( pk::is_ketsuen(kunshu, officers[officer].get_id()) or pk::is_gikyoudai(kunshu, officers[officer].get_id()) or pk::is_like(kunshu, officers[officer].get_id()) )
				officer_value += 군주관계_가산점;
				
			// 창,극일 경우 무력(최대 능력가산기준_최대)-유령기_무장_창극_최소만큼 가산점.
			if( item.type == 보물종류_긴무기 )
			{
				officer_value +=  pk::max( pk::min( officers[officer].stat[무장능력_무력], 능력가산기준_최대 )-유령기_무장_창극_최소, 0 )/유령기_창극_가산_계수;
					
				if( officers[officer].tekisei[병종_창병] >= 적성_S or officers[officer].tekisei[병종_극병] >= 적성_S )
					officer_value += 유령기_적성S_가산점;
			}
			
			// 검일 경우 (무력(최대 능력가산기준_최대)-유령기_무장_검_최소)/2 or (통무합계(최대 능력가산기준_최대*2)-유령기_무장_검_통무_최소)/2 중 높은 것으로 가산점.
			if( item.type == 보물종류_검 )
				officer_value +=  pk::max( pk::max( pk::min( officers[officer].stat[무장능력_무력], 능력가산기준_최대 )-유령기_무장_검_무력_최소, 0 )/유령기_검_무력_가산_계수, pk::max( pk::min( officers[officer].stat[무장능력_통솔] + officers[officer].stat[무장능력_무력], 능력가산기준_최대*2 )-유령기_무장_검_통무_최소, 0)/유령기_검_통무_가산_계수) ;
				
			// 암기일 경우 (무력(최대 능력가산기준_최대)-유령기_무장_암기_최소)/2만큼 가산점.
			if( item.type == 보물종류_암기 )
				officer_value +=  pk::max( pk::min( officers[officer].stat[무장능력_무력], 능력가산기준_최대 )-유령기_무장_암기_최소, 0 )/유령기_암기_가산_계수;
				
			// 활일 경우 (무력(최대 능력가산기준_최대)-유령기_무장_활_최소)/2만큼 가산점.
			if( item.type == 보물종류_활 )
			{
				officer_value +=  pk::max( pk::min( officers[officer].stat[무장능력_무력], 능력가산기준_최대 )-유령기_무장_활_최소, 0 )/유령기_활_가산_계수;
				if( officers[officer].tekisei[병종_노병] >= 적성_S or ( officers[officer].skill == 특기_궁장 or officers[officer].skill == 특기_궁신 ) )
					officer_value += 유령기_적성S_가산점;
			}
				
			// 서책일 경우 (지력(최대 능력가산기준_최대)-유령기_무장_서책_최소)/2만큼 가산점.
			if( item.type == 보물종류_서책  )
				officer_value +=  pk::max( pk::min( officers[officer].stat[무장능력_지력], 능력가산기준_최대 )-유령기_무장_서책_최소, 0 )/유령기_서책_가산_계수;
				
			// 명마일 경우 무력(최대 능력가산기준_최대)-유령기_무장_명마_무력_최소/2 or (통무지매 합계(최대 능력가산기준_최대*4)-유령기_무장_명마_통무지매_최소)/4 중 높은 것으로 가산점
			if( item.type == 보물종류_명마 )
				officer_value +=  pk::max( pk::max( pk::min( officers[officer].stat[무장능력_무력], 능력가산기준_최대 )-유령기_무장_명마_무력_최소, 0 )/유령기_명마_무력_가산_계수, pk::max( pk::min( officers[officer].stat[무장능력_통솔] + officers[officer].stat[무장능력_무력] + officers[officer].stat[무장능력_지력] + officers[officer].stat[무장능력_매력], 능력가산기준_최대*4)-유령기_무장_명마_통무지매_최소, 0)/유령기_명마_통무지매_가산_계수 ) ;
				
			if( officer_value > best_person_value )
				{ best_person_id = officers[officer].get_id(); best_person_value = officer_value;}
		}
	}
		
	// 간택된 무장이 같은 종류의 다른 무기가 있는지 확인
	if( best_person_id != -1 )
	{
		if( !유령기_보물종류_소유_체크( best_person_id, item.type ) )
		{
			return best_person_id;
		}
	}

	return -1;
}

/*
	보물의 소유자가 적합한지 테스트
*/
bool 유령기_보물_소유자적합(pk::person@ p, pk::item@ item)
{
	pk::person@ kunshu = pk::get_person(pk::get_kunshu_id(p)); // 군주
	int force_id = p.get_force_id();
		
	// 보물종류가 옥새 이상이면 넘어감
	if( item.type >= 보물종류_옥새 )
		return true;
		
	// 고유무장이거나 고유보조무장이면 넘어감
	if( 유령기_고유보물_체크( item.get_id(), p.get_id() ) or 유령기_고유보물보조_체크( item.get_id(), p.get_id() ) )
		return true;
		
	// 대상 무장이 일반적인 상태가 아니면 넘어감. 부상 중인 상태라면 저평가되어서 억울하게 몰수당하니 건강한 무장만 대상으로 함.
	if( !( p.mibun >= 신분_군주 and p.mibun <= 신분_일반 ) or p.shoubyou != 상병_건강 )
		return true;

	if ( p.mibun == 신분_군주 )
		return false;

	for(uint i=0; i<유령기_고유_보물.length; i++)
	{
		for (uint j = 1; j<유령기_고유_보물[i].length; j++)
		{
			pk::person@ p2 = pk::get_person(유령기_고유_보물[i][j]);
			
			if( 유령기_고유_보물[i][0] == item.get_id() and pk::is_alive(p2) and p2.get_id() != item.owner and p2.get_force_id() == force_id and p2.mibun >= 신분_군주 and p2.mibun <= 신분_일반)
			{
				if (p2.location <= 86)
					return false;
			}
		}
	}
		
	// 1. 개별보물에 대한 무장의 사용자 조건을 체크
	if( 유령기_사용자_조건_사용여부 and 유령기_사용자_조건_체크( item, 0, false ) >= 0 )
	{
		int cond_index = 유령기_사용자_조건_체크( item, 0, false );
			
		// 무장이 사용자조건을 만족한다면.....
		if( 유령기_사용자_조건_무장_체크( p, cond_index ) )
		{
			return true;
		}
	} 
	// 2. 보물종류에 대한 무장의 사용자 조건을 체크
	else if( 유령기_사용자_조건_사용여부 and 유령기_사용자_조건_체크( item, 1, false ) >= 0 )
	{
		int cond_index = 유령기_사용자_조건_체크( item, 1, false );
			
		// 무장이 사용자조건을 만족한다면.....
		if( 유령기_사용자_조건_무장_체크( p, cond_index ) )
		{
			return true;
		}
	}
		// 3. 기본조건 체크 후 기준에 맞으면 넘어감
	else if( 
			( item.type == 보물종류_긴무기 and 유령기_보물_창극_조건( p, 유령기_무장_창극_최소, 적성_A ) ) 
			or ( item.type == 보물종류_검 and 유령기_보물_검_조건( p, 유령기_무장_검_무력_최소, 유령기_무장_검_통무_최소 ) ) 
			or ( item.type == 보물종류_암기 and int(p.stat[무장능력_무력]) >= 유령기_무장_암기_최소 )
			or ( item.type == 보물종류_활 and 유령기_보물_활_조건( p, 유령기_무장_활_최소, 적성_A ) )
			or ( item.type == 보물종류_서책 and int(p.stat[무장능력_지력]) >= 유령기_무장_서책_최소 )
			or ( item.type == 보물종류_명마 and 유령기_보물_명마_조건( p, kunshu, 유령기_무장_명마_무력_최소, 유령기_무장_명마_통무지매_최소) )
		)
	{
		return true;
	}
		
        	return false;

}

void 유령기_잉여보물몰수( )
{
	array<ItemBest@> item_best_list;
	
	// 군주를 제외한 일반장수들 중 보물 1개 이상 가진 무장들을 조사
	for( int i=0 ; i < 보물_끝 ; i++ )
	{
		pk::item@ item = pk::get_item(i);
		pk::person@ p = pk::get_person(item.owner);
		
		// 보물종류가 옥새 이상이면 넘어감
		if( item.type >= 보물종류_옥새 )
			continue;
		
		if( !pk::is_alive(item) or item.status != 보물상태_등장 or !pk::is_alive(p)
			or !pk::is_alive(pk::get_force(p.get_force_id())) or !pk::is_alive(pk::get_person(pk::get_kunshu_id(p))) )
			continue;
		
		// 군주면 넘어감.
		if( p.mibun == 신분_군주 )
			continue;
		
		// 플레이어 무장이면 넘어감.
		if( p.is_player() )
			continue;		
		
		// 대상 무장이 일반적인 상태가 아니면 넘어감.
		if( !( p.mibun >= 신분_군주 and p.mibun <= 신분_일반 ) )
			continue;
		
		ItemBest temp(p.get_id());
		int index_temp = item_best_list.find(temp);
		
		// array에 정보가 없으면 보물 정보를 추가한후 array에 추가
		if( index_temp < 0 )
		{
			bool is_unique = ( 유령기_고유보물_체크( item.get_id(), p.get_id() ) or 유령기_고유보물보조_체크( item.get_id(), p.get_id() ) ) ? true : false;
			temp.setValue( item.type, item.get_id(), item.value, is_unique);
			item_best_list.insertLast(temp);
		}
		else // 이미 있는 정보라면 기존정보와 비교 후 보물 정보를 추가 ( 고유 혹은 보조 보물이 있을 경우 가치 비교 안 함 )
		{
			// 현재 보물이 고유보물이면 그 보물의 정보를 입력
			bool is_unique = ( 유령기_고유보물_체크( item.get_id(), p.get_id() ) or 유령기_고유보물보조_체크( item.get_id(), p.get_id() ) ) ? true : false;
			if( is_unique )
				item_best_list[index_temp].setValue( item.type, item.get_id(), item.value, is_unique);
			
			// (고유보물 정보가 있거나 기존 가치가 높은 경우)가 아닐 경우엔 새로운 아이템 정보를 입력
			if( !(item_best_list[index_temp].is_unique[item.type] or item_best_list[index_temp].item_value[item.type] >= item.value) )
				item_best_list[index_temp].setValue( item.type, item.get_id(), item.value, is_unique);
		}
	}
	

	// 보물 1개 이상 가지고 있는 장수들 대상으로 종류별 최고의 보물만 남기고 몰수. 
	for( int i=0 ; i < 보물_끝 ; i++ )
	{
		pk::item@ item = pk::get_item(i);
		pk::person@ p = pk::get_person(item.owner);
		
		// 보물종류가 옥새 이상이면 넘어감
		if( item.type >= 보물종류_옥새 )
			continue;
		
		if( !pk::is_alive(item) or item.status != 보물상태_등장 or !pk::is_alive(p)
			or !pk::is_alive(pk::get_force(p.get_force_id())) or !pk::is_alive(pk::get_person(pk::get_force(p.get_force_id()).kunshu)) )
			continue;
			
		pk::person@ kunshu = pk::get_person(pk::get_force(p.get_force_id()).kunshu); // 군주
		
		// 군주면 넘어감.
		if( p.mibun == 신분_군주 )
			continue;
		
		// 플레이어 무장이면 넘어감.
		if( p.is_player() )
			continue;
		
		// 대상 무장이 일반적인 상태가 아니면 넘어감.
		if( !( p.mibun >= 신분_군주 and p.mibun <= 신분_일반 ) )
			continue;
		
		for( uint j=0; j<item_best_list.length; j++)
		{
			// 현재보물의 소유장수와 다르면 넘어감.
			if( item_best_list[j].person_id != p.get_id() )
				continue;
			
			// 해당 장수의 고유(or 보조) 보물이면 넘어감
			if( 유령기_고유보물_체크( item.get_id(), p.get_id() ) or 유령기_고유보물보조_체크( item.get_id(), p.get_id() ) )
				continue;
			
			// 현재 장수가 소유한 종류별 최고의 보물이면 넘어감
			if( item_best_list[j].item_id[item.type] == item.get_id() )
				continue;
			
			// 해당사항 없는 보물이라면 군주가 몰수
			string s = "군주 <"+pk::decode(pk::get_name(kunshu))+">, <"+pk::decode(pk::get_name(pk::get_person(item.owner)))+"> 잉여보물로 보물 <"+pk::decode(item.name)+"> 몰수";
			item.owner = kunshu.get_id();		
                      
            		if( 유령기_로그_파일_표시) pk::info(s);
            		if( 유령기_로그_화면_표시) pk::history_log(pk::get_building(pk::get_person(item.owner).service).pos, -1, pk::encode(s));
            
            		if( 유령기_로그_메세지표시) pk::message_box(pk::encode(s));
		}
	}
	
}

/*
	해당 무장 최고의 보물 저장용 클래스
*/
class ItemBest
{
	int person_id = -1; // 무장 번호
	array<int> item_id = { -1, -1, -1, -1, -1, -1, -1, -1 }; // 종류별 보물번호
	array<int> item_value = { -1, -1, -1, -1, -1, -1, -1, -1 }; // 종류별 보물가치
	array<bool> is_unique = { false, false, false, false, false, false, false, false }; // 종류별 고유보물 여부

	ItemBest(int person_id)
	{
		this.person_id = person_id;
	}
	
	void setValue( int item_type, int item_id, int item_value, bool is_unique)
	{
		this.item_id[item_type] = item_id;
		this.item_value[item_type] = item_value;
		this.is_unique[item_type] = is_unique;
	}
	
	bool opEquals( ItemBest& in_ )
	{
		return this.person_id == in_.person_id;
	}
	
}

/* 
	해당 무장이 보물을 고유장수인지 체크
*/
bool 유령기_고유보물_체크( int item_id, int player_id )
{

	for(uint i=0; i<유령기_고유_보물.length; i++)
	{
		for(uint j=1; j<유령기_고유_보물[i].length; j++)
		{
			if( 유령기_고유_보물[i][0] == item_id and 유령기_고유_보물[i][j] == player_id )
				return true;
		}
	}		
	
	return false;
}

/* 
	해당 무장이 보물을 고유보조장수인지 체크
*/
bool 유령기_고유보물보조_체크( int item_id, int player_id )
{

	for(uint i=0; i<유령기_고유_보물_보조.length; i++)
	{
		for(uint j=1; j<유령기_고유_보물_보조[i].length; j++)
		{
			if( 유령기_고유_보물_보조[i][0] == item_id and 유령기_고유_보물_보조[i][j] == player_id )
				return true;
		}
	}		
	
	return false;
}

/*
	해당 보물의 고유장수가 세력 내에 있는지 체크 ( 복수일경우 Array에서 제일 처음 발견되는 무장 리턴 )
	단, 현재 보물의 소유자일 경우 체크하지 않고 다음 고유장수를 찾는다.
	따라서 보물의 현재 소유자가 고유무장일 경우 이 함수로는 찾을수가 없다.
*/
int 유령기_고유보물_세력체크( int item_id, int force_id )
{
	
	for(uint i=0; i<유령기_고유_보물.length; i++)
	{
		for(uint j=1; j<유령기_고유_보물[i].length; j++)
		{
			pk::person@ p = pk::get_person(유령기_고유_보물[i][j]);
			
			if( 유령기_고유_보물[i][0] == item_id and pk::is_alive(p) and p.get_id() != pk::get_item(item_id).owner
				and p.get_force_id() == force_id and p.mibun >= 신분_군주 and p.mibun <= 신분_일반 )
				return 유령기_고유_보물[i][j];
		}
	}		
	
	return -1;
}

/*
	해당 종류의 보물 있는지 확인
*/
bool 유령기_보물종류_소유_체크( int person_id, int item_type )
{
	for( int i=0 ; i < 보물_끝 ; i++ )
	{
		pk::item@ item= pk::get_item(i);
		
		if( !pk::is_alive(item) or item.status != 보물상태_등장 )
			continue;
		
		if ( item.owner == person_id and item.type == item_type )
		{
			
			string s = "무장 <"+pk::decode(pk::get_name(pk::get_person(person_id)))+">, 같은 종류의 다른 일반보물 <"+pk::decode(item.name)+"> 존재....";
			
            		if( 유령기_로그_파일_표시) pk::info(s);
           	 		if( 유령기_로그_화면_표시) pk::history_log(pk::get_building(pk::get_person(item.owner).service).pos, -1, pk::encode(s));
            
            		if( 유령기_로그_메세지표시) pk::message_box(pk::encode(s));
			
			return true;
		}
	}
	
	return false;
}

/*
	보물 반납
*/
void 유령기_보물_반납( int person_id, int kunshu_id, int item_type )
{
	for( int i=0 ; i < 보물_끝 ; i++ )
	{
		pk::item@ item = pk::get_item(i);
		
		if( !pk::is_alive(item) or item.status != 보물상태_등장 )
			continue;
		
		if ( item.owner == person_id and item.type == item_type 
			and !유령기_고유보물_체크( item.get_id(), person_id ) and !유령기_고유보물보조_체크( item.get_id(), person_id ) )
		{
			string s = "무장 <"+pk::decode(pk::get_name(pk::get_person(person_id)))+">, <"+pk::decode(pk::get_name(pk::get_person(kunshu_id)))+">에게 일반보물 <"+pk::decode(item.name)+"> 반납";
			
			item.owner = kunshu_id;

            /*
			if( 유령기_로그_파일_표시) Logger().trace(s);
			if( 유령기_로그_화면_표시) MessageBox().historylog( Point(), -1, s);
            */
            if( 유령기_로그_파일_표시) pk::info(s);
            if( 유령기_로그_화면_표시) pk::history_log(pk::get_building(pk::get_person(item.owner).service).pos, -1, pk::encode(s));
            
            if( 유령기_로그_메세지표시) pk::message_box(pk::encode(s));
		}
	}
}


/*
	무장이 창, 극을 소유할 수 있는지 조건 체크
*/
bool 유령기_보물_창극_조건( pk::person@ p, int power, int apt )
{
	
	if(  ( int(p.stat[무장능력_무력]) >= power and ( int(p.tekisei[병종_창병]) >= apt or int(p.tekisei[병종_극병]) >= apt) ) or 
		 ( int(p.skill) == 특기_창장 or int(p.skill) == 특기_극장 or int(p.skill) == 특기_창신 
		 or int(p.skill) == 특기_극신 or int(p.skill) == 특기_투신 or int(p.skill) == 특기_비장
		 or int(p.skill) == 특기_신장 or int(p.skill) == 특기_용장 or int(p.skill) == 특기_패왕 ) )
		 return true;
		 
	return false;
}

/*
	무장이 검을 소유할 수 있는지 조건 체크
	
	@param overall 통 무 합계 체크 기준
*/
bool 유령기_보물_검_조건( pk::person@ p, int power, int overall )
{
	
	if( int(p.stat[무장능력_무력]) >= power or int(p.stat[무장능력_무력] + p.stat[무장능력_통솔] ) >= overall )
		return true;
	
	return false;
}

/*
	무장이 활을 소유할 수 있는지 조건 체크
*/
bool 유령기_보물_활_조건( pk::person@ p, int power, int apt )
{
	
	if(  ( int(p.stat[무장능력_무력]) >= power and int(p.tekisei[병종_노병]) >= apt ) or 
		 ( int(p.skill) == 특기_궁장 or int(p.skill) == 특기_궁신 or int(p.skill) == 특기_사수 or int(p.skill) == 특기_비장
		 or int(p.skill) == 특기_신장 or int(p.skill) == 특기_용장 or int(p.skill) == 특기_패왕 ) ) 
		 return true;
		 
	return false;
}

/*
	무장이 명마를 소유할 수 있는지 조건 체크
	
	@param overall 통 무 지 매 합계 체크 기준
*/
bool 유령기_보물_명마_조건( pk::person@ p, pk::person@ kunshu, int power, int overall )
{
	// 군주 본인이거나 혈연, 의형제거나 군주의 친애장수일 경우 각 능력별 커트라인 10씩 하락.
	if( kunshu.get_id() == p.get_id() or pk::is_like(kunshu, p.get_id()) or pk::is_ketsuen(kunshu, p.get_id()) or pk::is_gikyoudai(kunshu, p.get_id()) )
	{
		power -= 10;
		overall -= 40;
	}

	if( int(p.stat[무장능력_무력]) >= power or int( p.stat[무장능력_무력] + p.stat[무장능력_통솔] + p.stat[무장능력_지력] + p.stat[무장능력_매력] ) >= overall )
		return true;
	
	return false;
}

/*
	보물이 적용되는 사용자 조건이 있는지 체크한다
	
	@param pk::item@ 체크할 보물
	@param type 0 - 개별보물번호를 체크, 1 - 보물종류를 체크
	@param is_kunshu 군주 조건인지 여부
	@return 일치하는 조건이 있다면 조건의 index를 리턴, 없으면 -1 리턴
*/
int 유령기_사용자_조건_체크( pk::item@ item, int type, bool is_kunshu )
{
	int is_kunshu_num = is_kunshu ? 0 : 1;
	
	for( uint i=0; i<사용자_조건_기준.length; i++ )
	{
		if( type == 0 and 사용자_조건_기준[i][2] == item.get_id() and 사용자_조건_기준[i][0] == is_kunshu_num )
			return i;
		
		if( type == 1 and 사용자_조건_기준[i][1] == item.type and 사용자_조건_기준[i][0] == is_kunshu_num )
			return i;
	}

	return -1;
}

/*
	무장이 해당 index의 조건식의 조건을 만족시키는지 리턴
*/
bool 유령기_사용자_조건_무장_체크( pk::person@ p, int index )
{
	int min_leader = 사용자_조건_기준[index][4];
	int min_power = 사용자_조건_기준[index][6];
	int min_int = 사용자_조건_기준[index][8];
	int min_pol = 사용자_조건_기준[index][10];
	int min_char = 사용자_조건_기준[index][12];
	
	int min_spear = 사용자_조건_기준[index][15];
	int min_polearm = 사용자_조건_기준[index][17];
	int min_bow = 사용자_조건_기준[index][19];
	int min_horse = 사용자_조건_기준[index][21];
	int min_mecha = 사용자_조건_기준[index][23];
	int min_water = 사용자_조건_기준[index][25];
	
	int min_loyalty = 사용자_조건_기준[index][28];
	int min_exploit = 사용자_조건_기준[index][31];
	
	if( int(p.stat[무장능력_통솔]) >= min_leader and int(p.stat[무장능력_무력]) >= min_power and int(p.stat[무장능력_지력]) >= min_int and int(p.stat[무장능력_정치]) >= min_pol and int(p.stat[무장능력_매력]) >= min_char and
		int(p.tekisei[병종_창병]) >= min_spear and int(p.tekisei[병종_극병]) >= min_polearm and int(p.tekisei[병종_노병]) >= min_bow and 
		int(p.tekisei[병종_기병]) >= min_horse and int(p.tekisei[병종_병기]) >= min_mecha and int(p.tekisei[병종_수군]) >= min_water and 
		int(p.loyalty) >= min_loyalty and int(p.kouseki) >= min_exploit )
		return true;
		
	return false;
}

/*
	무장의 해당 index의 조건식에 따른 수치를 계산해서 리턴
*/
int 유령기_사용자_조건_무장_수치( pk::person@ p, int index )
{
	//pk::Random random(win32api::GetTickCount()+p.get_id()*p.get_id()+p.get_force_id());
    
	int value = 0;
	int kunshu_id = pk::get_force(p.get_force_id()).kunshu;
	
	int max_stat = 사용자_조건_기준[index][3];
	int mul_leader = 사용자_조건_기준[index][5];
	int mul_power = 사용자_조건_기준[index][7];
	int mul_int = 사용자_조건_기준[index][9];
	int mul_pol = 사용자_조건_기준[index][11];
	int mul_char = 사용자_조건_기준[index][13];
	int max_apt = 사용자_조건_기준[index][14];
	int mul_spear = 사용자_조건_기준[index][16];
	int mul_polearm = 사용자_조건_기준[index][18];
	int mul_bow = 사용자_조건_기준[index][20];
	int mul_horse = 사용자_조건_기준[index][22];
	int mul_mecha = 사용자_조건_기준[index][24];
	int mul_water = 사용자_조건_기준[index][26];
	int max_loyalty = 사용자_조건_기준[index][27];
	int mul_loyalty = 사용자_조건_기준[index][29];
	int max_exploit = 사용자_조건_기준[index][30];
	int mul_exploit = 사용자_조건_기준[index][32];
	int mul_parent_child = 사용자_조건_기준[index][33];
	int mul_spouse = 사용자_조건_기준[index][34];
	int mul_blood = 사용자_조건_기준[index][35];
	int mul_brother = 사용자_조건_기준[index][36];
	int mul_like = 사용자_조건_기준[index][37];
	int random_max = 사용자_조건_기준[index][38];
	
	value += pk::min(p.stat[무장능력_통솔], max_stat) * mul_leader;
	value += pk::min(p.stat[무장능력_무력], max_stat) * mul_power;
	value += pk::min(p.stat[무장능력_지력], max_stat) * mul_int;
	value += pk::min(p.stat[무장능력_정치], max_stat) * mul_pol;
	value += pk::min(p.stat[무장능력_매력], max_stat) * mul_char;
	
	value += pk::min(p.tekisei[병종_창병], max_apt) * mul_spear;
	value += pk::min(p.tekisei[병종_극병], max_apt) * mul_polearm;
	value += pk::min(p.tekisei[병종_노병], max_apt) * mul_bow;
	value += pk::min(p.tekisei[병종_기병], max_apt) * mul_horse;
	value += pk::min(p.tekisei[병종_병기], max_apt) * mul_mecha;
	value += pk::min(p.tekisei[병종_수군], max_apt) * mul_water;
	
	value += pk::min(p.loyalty, max_loyalty) * mul_loyalty;
	value += pk::min(p.kouseki, max_exploit) * mul_exploit;
	value += ( pk::is_oyako(p, kunshu_id) ? 1 : 0 )* mul_parent_child;
	value += ( pk::is_fuufu(p, kunshu_id) ? 1 : 0 )* mul_spouse;
	value += ( pk::is_ketsuen(p, kunshu_id) ? 1 : 0 )* mul_blood;
	value += ( pk::is_gikyoudai(p, kunshu_id) ? 1 : 0 )* mul_brother;
	value += ( pk::is_like(p, kunshu_id) ? 1 : 0 )* mul_like;
	
	//int temp = random(random_max);
	int temp = pk::rand(random_max);
	value += temp;
	
	// Logger().trace("<"+p.get_id()+"> 이름 : " + p.name + ", Tick="+win32api::GetTickCount()+" 난수="+temp+" 수치=" + value );
	
	return value;
}


/*
	임시로 보물의 소유정보를 다루는 클래스
	

	무장의 능력에 대한 조건을 비교할 때 이미 보물을 가지고 있는 무장은 
	보물의 능력치가 포함되어서 계산되는 문제가 발생해서, 그걸 막기 위해서
	무장의 능력을 체크하기 전에 이 array에 보물들의 소유주를 임시로 기록한 후
	보물들을 무장들에게서 전부 빼았은 후 능력치를 체크한다.
	능력치 체크가 끝난 후에는 이 Array에 있는 소유정보를 토대로 다시 보물들을 돌려준다.
	잘못 사용하면 보물정보가 완전히 엉망이 될수 있으므로 
	코딩 시 보물들을 임시로 빼았았다가 돌려주기 전까지는 함부로 보물의 소유정보에 관한 루틴을 집어넣으면 안된다. 
	기본은 모두 -1
*/

class TempItemHistory
{
	array<int> temp_item_array(보물_끝, -1); 	
	
	TempItemHistory(){}
	
	void save()
	{
		for( int i=0 ; i < 보물_끝 ; i++ )
		{		
			pk::item@ item= pk::get_item(i);
			
			temp_item_array[i] = item.owner;	
			item.owner = -1;
		}
	}
	
	void rollBack()
	{
		for( int i=0 ; i < 보물_끝 ; i++ )
		{		
			pk::item@ item= pk::get_item(i);

			item.owner = temp_item_array[i];			
			temp_item_array[i] = -1;
		}
	}
}