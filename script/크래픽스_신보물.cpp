/*
@만든이: 크래픽스
@Update: 2024.1.27,최초배포
@Update: 2024.1.28,일기토 포박관련 처리
@Update: 2024.1.28,보물 종류, 서책,동작,옥새의 경우 빌려오지 않음,
@Update: 2024.1.28,보물추가.
@Update: 2024.1.30,보물발견시 에러처리
@Update: 2024.2.1,예외처리
@Update: 2024.2.7,강운특기자 부상당하지 않도록 수정
@Update: 2024.2.8,혼돈,메테오,수계,방어특기공유,부상유발 추가
@Update: 2024.2.9,보물탐색 에러처리,get_unit에러 수정
@Update: 2024.2.11,화계방어시 화신특기 적용안되는 문제수정
@Update: 2024.2.12,오타 및 로그 일부 수정
@Update: 2024.2.13,AI의 패시브 효과들이 중복실행되지 않도록 수정
@Update: 2024.2.17,중복으로 보물빌려오는문제수정
@Update: 2024.2.18,세이브로드시 최초소유자 버그문제 수정
@Update: 2024.5.2, 전능0이하일때 처리
@Update: 2024.5.3, 진정효과시, 행동회복
@Update: 2024.5.6, 에러수정
@Update: 2024.5.7, 혼돈,원킬 로그표시, AI보물강탈 표시 수정
@Update: 2024.5.11, 신보물 화신특기 불지형에서 병력감소 없도록 수정
@Update: 2024.5.11, 진정효과시, 행동회복
@Update: 2024.5.15, AI신보물 이벤트 무장에게 하사하지 않도록 수정
@Update: 2024.5.22, 출진중인 아군끼리 공유하지 않도록 수정
@Update: 2024.5.30, 보물빌려준 무장이 출진시 보물회수, 보물특기 관통추가, TurnEnd일기토와 연계위해 TunrStart에서 RentBack
@Update: 2024.6.1, 전투하고 있는 세력으로부터 보물을 빌려오지 않음, 일기토 포박후 해방인 경우 인식하도록 수정
@Update: 2024.6.1, 인접회복특기, 대불굴특기 추가
@Update: 2024.6.2, 보물특기 추가, 답파 구현
@Update: 2024.7.20, 보물특기,전법성공확율, 계략성공확률, 지원공격확률추가



*/
namespace 신보물_Items
{
	const int 무장없음 = -1;//수정하지 마세요
	const int 보물없음 = -1;//수정하지 마세요


	const bool 보물_빌려오기 = false;
	const bool 보물_빌려오기_로그표시 = false;

	const int 아이템_공유_거리 = 30;//30칸
	const int 아이템_공유_거리_공격 = 10;//10칸
	const int 보물확률_역수 = 1000; //모든 부대의 행동완료마다,전장에서, 신보물탐색 시도, 1/1000;

	/* 지원특기리스트
		
		백마: 공격력은 증가되나, 기병으로 활쏘는것이 안됨.
		궁신: 전법크리터컬은 적용되나 궁신으로써 아군을 안쏘는것 적용안됨
		기신: 전법크리티컬은 적용,
		비장: ZOC무시안됨
		강운: 부상방지 안됨
		철벽: 일제공격방어안됨
		친강,친오,친만,친월 : 적군발생 방어 안됨.


		둔전,명성,능리,번식,발명,조선,부호,미도,인정
		포박,강운(일부),혈로,주악,
		질주,난전,신장,구축,패왕,기신(일부),용장,비장(일부),기장,창신,투신,창장,극신,극장,궁신(일부),궁장,공신,공성,수신,수장
		백마(일부),급습,강습,위풍,소탕,친강(일부),친오(일부),친만(일부),친월(일부)
		백출,보좌,화신,등갑,불굴,금강,철벽(일부)
		신산,허실,경국,기략,언독,궤계,화공,묘계,비책,통찰,반계,간파,명경,침착,규율,심모,묘계,비책
	*/

	const int 보물특기_모든공격_화계발생 = 0; //모든공격에 화계가 발생합니다.
	const int 보물특기_인접_화계_소화 = 1; //턴종료, 턴시작시 인접아군의 불을 끕니다.
	const int 보물특기_인접_혼란_위보_진정 = 2;//턴종료, 턴시작시에 인접아군의 혼란,위보 상태를 진정합니다.
	const int 보물특기_인접_낙뢰 = 3;//인접적군에게 락뢰를 떨어트립니다.
	const int 보물특기_인접_스플래쉬_데미지 = 4;//공격한 적군의 인접적군에게도 데미지가 발생합니다.
	const int 보물특기_모든공격_추가데미지 = 5;//공격한 적군에게 추가데미지가 발생합니다.
	const int 보물특기_주악 = 6;//무한전법 사용할수 있게 30의 기력이 매턴에 추가됩니다.
	const int 보물특기_모든공격_충성도_저하 = 7;//공격한 적군의 충성도를 저하시킵니다.
	const int 보물특기_위풍 = 8;//공격한 적군의 기력을 크게 감소시킵니다.
	const int 보물특기_심공 = 9;//공격한 적군에 입힌 데미지의 비율로 회복합니다. 원거리 공격도 적용됩니다.
	const int 보물특기_원킬 = 10;//낮은 확률로 적군을 전병력을 날립니다.
	const int 보물특기_병량탈취 = 11;//공격한 데미지의 1.5배로 병량을 탈취합니다.
	const int 보물특기_혼란_유발 = 12;//공격한 적군이 혼란이 유발됩니다.
	const int 보물특기_위보_유발 = 13;//공격한 적군이 위보가 유발됩니다.
	const int 보물특기_동토_유발 = 14;//공격한 적군이 동토가 유발됩니다.
	const int 보물특기_일기토_유발 = 15;//턴종료후, 인접 적군과 일기토가 유발됩니다.
	const int 보물특기_인접부대_건물데미지_추가 = 16;//자신 및 인접부대의 건물데미지가 2배가 됩니다.
	const int 보물특기_기교포인트_획득 = 17;//매턴 기교포인트가 증가합니다.
	const int 보물특기_능력연구속도향상 = 18;//능력연구속도가 2배 빠릅니다.
	const int 보물특기_메테오 = 19;//인접적군에 메테오가 떨어집니다.
	const int 보물특기_부상유발 = 20;//공격시 부상이 유발됩니다.
	const int 보물특기_방어특기공유 = 21;//인접아군에 방어특기를 공유합니다.(등갑,철벽,불굴,금강)
	const int 보물특기_혼돈 = 22;//랜덤특기발생,ex){보물특기_혼돈,보물특기_인접_낙뢰,보물특기_수계} 락뢰와 수계중 랜덤으로 한가지 발생
	const int 보물특기_수계 = 23;//인접적군에 수계가 발생합니다.
	const int 보물특기_관통공격 = 24;//활공격시 목표점과의 사이의 적에게 스플래쉬 데미지를 발생시킵니다.
	const int 보물특기_인접_회복 = 25;//인접아군의 부대가 회복됩니다.
	const int 보물특기_대불굴 = 26;//불굴의 상위버전입니다.소병력일때도 혼란에 걸리지 않습니다. 2000병력이하일때, 90확률로 막습니다.
	const int 보물특기_전법성공확률 = 27;//전법성공확률이 추가됩니다.
	const int 보물특기_지원공격확률 = 28;//지원공격확률이 추가됩니다.
	const int 보물특기_계략성공확률 = 29;//계략성공확럴이 추가됩니다.

	const int 화계_확률 = 100;

	const int 낙뢰_확률 = 100;
	const int 낙뢰_기본_데미지 = 500;
	const int 낙뢰_랜덤_데미지 = 500;
	const int 낙뢰_부상_확률 = 10;

	const int 메테오_확률 = 100;
	const int 메테오_기본_데미지 = 300;
	const int 메테오_랜덤_데미지 = 300;
	const int 메테오_화계_확률 = 100;

	const int 수계_데미지 = 1000;//x^2으로 보간, 낮은 확률로 높은데미지
	const int 수계_확률 = 100;

	const int 인접_소화_범위 = 2;
	const int 인접_혼란_위보_회복_범위 = 2;
	const int 인접_회복_범위 = 1;

	const int 인접_병력_회복량 = 500;

	const int 대불굴_병력기준 = 2000;
	const int 대불굴_확률 = 90;

	const float 스플레시_데미지_비율 = 0.5;
	const float 추가_데미지_비율 = 0.15;
	const float 심공_비율 = 0.25;
	const float 건물데미지_비율 = 2.0;
	const float 지도_비율 = 2.0;

	const float 주악_기력 = 30; //무한전법사용가능하도록
	const float 위풍_기력 = 50;
	const int 충성도_저하량 = 3;

	const int 원킬_확률 = 2;

	const float 병량_데미지_비율 = 1.5;
	const int 혼란_확률 = 30;
	const int 위보_확률 = 30;
	const int 동토_확률 = 30;

	const int 일기토_회피_무력_차 = 10; //무력이 10이상 높은경우 일기토를 하지 않습니다.
	const int 일기토_유발_확률 = 20;

	const int 턴당_기교포인트 = 100;
	const int 부상유발_확률 = 30;

	const int 전법성공확률 = 15;
	const int 계략성공확률 = 15;
	const int 지원공격확률 = 30;




	const int 세이_RAND = 3;
	
	array<CustomItem@> 커스텀아이템스 =
	{
		//신보물ID,신보물이름,신보물이미지경로,보물특기리스트,특기리스트, 통무지정매,보물타입,가치, 원본보물, 최초보유무장
		CustomItem(0,"화룡도","신보물\\화용도2.png",{보물특기_모든공격_화계발생}, {특기_패왕,특기_화신},0,6,0,0,0,보물종류_검,40,보물없음, 무장없음),
		CustomItem(1,"복마화령검","신보물\\복마화령검.png",{보물특기_인접_화계_소화,보물특기_인접_혼란_위보_진정}, {특기_금강,특기_불굴,특기_철벽},3,3,0,0,0,보물종류_검,40,보물없음, 무장없음),
		CustomItem(2,"진마강용검","신보물\\진마강용검.png", {보물특기_모든공격_추가데미지}, {특기_패왕},0,6,0,0,0,보물종류_검,40,보물없음, 무장없음),
		CustomItem(3,"드래곤슬레이어","신보물\\가츠검1.png", {보물특기_인접_스플래쉬_데미지}, {특기_패왕},0,6,0,0,0,보물종류_검,40,보물없음, 무장없음),
		
		
		CustomItem(6,"청동마수검","신보물\\청동마수검.png",{}, {},0,2,0,0,0,보물종류_검,20,보물없음, 무장없음),
		CustomItem(7,"승리기원부","신보물\\승리의부적.png",{보물특기_기교포인트_획득}, {},0,0,0,0,0,보물종류_서책,10,보물없음, 무장없음),
		CustomItem(11,"텐잉즈","신보물\\텐링즈.png",{보물특기_부상유발}, {},0,2,0,0,0,보물종류_암기,20,보물없음, 무장없음),
		CustomItem(12,"대장방패","신보물\\캡틴방패.png",{보물특기_방어특기공유}, {특기_금강,특기_불굴,특기_철벽,특기_등갑},5,0,0,0,0,보물종류_서책,40,보물없음, 무장없음),
		
		CustomItem(14,"동마차","신보물\\동마차.png",{보물특기_능력연구속도향상}, {},0,0,0,0,0,보물종류_서책,10,보물없음, 무장없음),
		CustomItem(15,"페보니우스활","신보물\\페보니우스활.png",{보물특기_관통공격}, {특기_패왕},0,6,0,0,0,보물종류_활,40,보물없음, 무장없음),

		CustomItem(16,"임로","신보물\\임로.png",{보물특기_인접_회복}, {},0,0,0,0,0,보물종류_서책,20,보물없음, 무장없음)
		


		//맨마지막줄 컴마(,) 있으면 에러날수 있음.
	};

	const array<string> 보물이미지 =
	{
		"Ebony_보물\\적토마.png",
		"Ebony_보물\\적로.png",
		"Ebony_보물\\조황비전.png",
		"Ebony_보물\\절영.png",
		"Ebony_보물\\대완마.png",
		"Ebony_보물\\대완마.png",
		"Ebony_보물\\대완마.png",
		"Ebony_보물\\칠성보도.png",
		"Ebony_보물\\의천검.png",
		"Ebony_보물\\청강검.png",

		"Ebony_보물\\쌍고검.png",
		"Ebony_보물\\방천화극.png",
		"Ebony_보물\\청룡언월도.png",
		"Ebony_보물\\장팔사모.png",
		"Ebony_보물\\유청추.png",
		"Ebony_보물\\비도.png",
		"Ebony_보물\\비도.png",
		"Ebony_보물\\단극.png",
		"Ebony_보물\\단극.png",
		"Ebony_보물\\수극.png",

		"Ebony_보물\\수극.png",
		"Ebony_보물\\철쇄.png",
		"Ebony_보물\\양유기의-궁.png",
		"Ebony_보물\\이광의-궁.png",
		"Ebony_보물\\단궁.png",
		"Ebony_보물\\단궁.png",
		"Ebony_보물\\동호비궁.png",
		"Ebony_보물\\동호비궁.png",
		"Ebony_보물\\맥궁.png",
		"Ebony_보물\\맥궁.png",

		"Ebony_보물\\손자병법.png",
		"Ebony_보물\\병법24편.png",
		"Ebony_보물\\맹덕신서.png",
		"Ebony_보물\\육도.png",
		"Ebony_보물\\삼략.png",
		"Ebony_보물\\오자.png",
		"Ebony_보물\\위료자.png",
		"Ebony_보물\\전국책.png",
		"Ebony_보물\\사마법.png",
		"Ebony_보물\\묵자.png",

		"Ebony_보물\\태평요술서.png",
		"Ebony_보물\\옥새.png",
		"Ebony_보물\\동작.png",
		"",
		"",
		"",
		"",
		"",
		"",
		"",

		"Ebony_보물\\옥란백용구.png",
		"Ebony_보물\\권모적토마.png",
		"Ebony_보물\\서량백마.png",
		"Ebony_보물\\백마.png",
		"Ebony_보물\\사륜거.png",
		"Ebony_보물\\오환마.png",
		"Ebony_보물\\흉노마.png",
		"Ebony_보물\\적모우.png",
		"Ebony_보물\\백상.png",
		"Ebony_보물\\참사검.png",

		"Ebony_보물\\간장.png",
		"Ebony_보물\\막야.png",
		"Ebony_보물\\고정도.png",
		"Ebony_보물\\백피도.png",
		"Ebony_보물\\신도.png",
		"Ebony_보물\\오구도.png",
		"Ebony_보물\\거치도.png",
		"Ebony_보물\\환수도.png",
		"Ebony_보물\\쌍철극.png",
		"Ebony_보물\\삼부도.png",

		"Ebony_보물\\봉취도.png",
		"Ebony_보물\\미부도.png",
		"Ebony_보물\\대간도.png",
		"Ebony_보물\\치우부.png",
		"Ebony_보물\\대부.png",
		"Ebony_보물\\철척사모.png",
		"Ebony_보물\\금마삭.png",
		"Ebony_보물\\삼장모.png",
		"Ebony_보물\\철편.png",
		"Ebony_보물\\철칠여골타.png",

		"Ebony_보물\\철과추.png",
		"Ebony_보물\\질려봉.png",
		"Ebony_보물\\매화수전.png",
		"Ebony_보물\\수전.png",
		"Ebony_보물\\철추.png",
		"Ebony_보물\\비추.png",
		"Ebony_보물\\보조궁.png",
		"Ebony_보물\\논어.png",
		"Ebony_보물\\전론.png",
		"Ebony_보물\\박혁론.png",

		"Ebony_보물\\시요론.png",
		"Ebony_보물\\치론.png",
		"Ebony_보물\\춘추좌씨전.png",
		"Ebony_보물\\한비자.png",
		"Ebony_보물\\관자.png",
		"Ebony_보물\\둔갑천서.png",
		"Ebony_보물\\서촉지형도.png",
		"Ebony_보물\\평만지장도.png",
		"Ebony_보물\\오추마.png",
		""
	};


	const int KEY = pk::hash("신보물");
	const int KEY_EXPORT = pk::hash("신보물_Export");

	class CustomItem
	{
		pk::person@ owner = null;
		pk::person@ fowner = null;
		string name = "";
		string path = "";
		int id = -1;

		array<int> skills보물;
		array<int> skills;

		array<int> 능력 = { 0,0,0,0,0 };

		int srcItem = -1;
		int value = 0;
		int type;

		array<int> skills혼돈 = {};


		CustomItem(){}
		CustomItem(int id0, string str,string path0,array<int> 보물스킬0, array<int> skills0, int 통솔,int 무력,int 지력,int 정치력,int 매력,int type0, int value0, int 원본보물, int 소유무장)
		{
			id = id0;
			path = path0;
			name = str;
			value = value0;
			skills = skills0;
			
			if (보물스킬0.length > 1 && 보물스킬0[0] == 보물특기_혼돈)
			{
				skills보물 = { 보물특기_혼돈 };
				for (int i = 1; i < 보물스킬0.length; i++)
				{
					skills혼돈.insertLast(보물스킬0[i]);
				}
			}
			else 
			{
				skills보물 = 보물스킬0;
			}

			능력 = { 통솔,무력,지력,정치력,매력 };
			srcItem = 원본보물;
			type = type0;
			if (소유무장 >= 0)
			{
				@fowner = pk::get_person(소유무장);
			}
		}

		void updateOwner(pk::person@ newOwner)
		{
			if (owner != null && newOwner != null && owner.get_id() == newOwner.get_id())
				return;

			if (owner != null)
			{
				if (능력[0] != 0) apply무장능력(owner, 무장능력_통솔, -능력[0]);
				if (능력[1] != 0) apply무장능력(owner, 무장능력_무력, -능력[1]);
				if (능력[2] != 0) apply무장능력(owner, 무장능력_지력, -능력[2]);
				if (능력[3] != 0) apply무장능력(owner, 무장능력_정치, -능력[3]);
				if (능력[4] != 0) apply무장능력(owner, 무장능력_매력, -능력[4]);
			}
			
			@owner = newOwner;
			if (newOwner != null)
			{
				if (능력[0] != 0) apply무장능력(newOwner, 무장능력_통솔, 능력[0]);
				if (능력[1] != 0) apply무장능력(newOwner, 무장능력_무력, 능력[1]);
				if (능력[2] != 0) apply무장능력(newOwner, 무장능력_지력, 능력[2]);
				if (능력[3] != 0) apply무장능력(newOwner, 무장능력_정치, 능력[3]);
				if (능력[4] != 0) apply무장능력(newOwner, 무장능력_매력, 능력[4]);
			}
		}

		void transfer(pk::person@ p0, pk::person@ p1, pk::item@ item)
		{
			array<pk::item@> arr;
			if (p0 != null)
			{
				for (int i = 0; i < 보물_끝; i++)
				{
					pk::item@ it = pk::get_item(i);
					if (it == null)
						continue;

					if (it.owner == p0.get_id() && it.id != item.id)
					{
						it.owner = -1;
						it.update();
						arr.insertLast(it);
					}
				}
			}
			if (p0 == null)
			{
				item.owner = p1.get_id();
				item.location = p1.service;
			}
			pk::transfer_item(p0!=null ? p0 : p1, p1);
			
			if (p0 != null)
			{
				for (int i = 0; i < arr.length; i++)
				{
					pk::item@ it = arr[i];
					it.owner = p0.get_id();
					it.update();
				}
				pk::transfer_item(p0, p0);
			}
		}

		array<int> updateRent(pk::item@ item)
		{
			pk::person@ powner = pk::get_person(item.owner);

			//item.owner = owner.get_id();
			//item.location = owner.service;
			//item.update();
			//if (powner != null) powner.update();
			//owner.update();



			array<int> bbb = { owner.max_stat[무장능력_통솔],owner.max_stat[무장능력_무력],owner.max_stat[무장능력_지력] ,owner.max_stat[무장능력_정치] ,owner.max_stat[무장능력_매력] };

			//pk::printf("base:{},{}\n", owner.base_stat[무장능력_통솔], owner.base_stat[무장능력_무력]);
			//pk::printf("max:{},{}\n", owner.max_stat[무장능력_통솔], owner.max_stat[무장능력_무력]);
			//pk::printf("cur:{},{}\n", owner.stat[무장능력_통솔], owner.stat[무장능력_무력]);

			transfer(powner, owner, item);

			//pk::printf("base2:{},{}\n", owner.base_stat[무장능력_통솔], owner.base_stat[무장능력_무력]);
			//pk::printf("max2:{},{}\n", owner.max_stat[무장능력_통솔], owner.max_stat[무장능력_무력]);
			//pk::printf("cur2:{},{}\n", owner.stat[무장능력_통솔], owner.stat[무장능력_무력]);

			array<int> rented(5, 0);
			for (int i = 0; i < bbb.length; i++)
				rented[i] = owner.max_stat[i] - bbb[i];
			for (int i = 0; i < bbb.length; i++)
				owner.base_stat[i] = owner.base_stat[i] - rented[i];
			owner.update();

			//pk::printf("base3:{},{}\n", owner.base_stat[무장능력_통솔], owner.base_stat[무장능력_무력]);
			//pk::printf("max3:{},{}\n", owner.max_stat[무장능력_통솔], owner.max_stat[무장능력_무력]);
			//pk::printf("cur3:{},{}\n", owner.stat[무장능력_통솔], owner.stat[무장능력_무력]);



			if (powner != null)
			{
				//array<int> bbb2 = { powner.max_stat[무장능력_통솔],powner.max_stat[무장능력_무력],powner.max_stat[무장능력_지력] ,powner.max_stat[무장능력_정치] ,powner.max_stat[무장능력_매력] };
				//array<int> bbb2 = { powner.base_stat[무장능력_통솔],powner.base_stat[무장능력_무력],powner.base_stat[무장능력_지력] ,powner.base_stat[무장능력_정치] ,powner.base_stat[무장능력_매력] };
				for (int i = 0; i < rented.length; i++)
					powner.base_stat[i] = powner.base_stat[i] + rented[i];
				powner.update();
			}

			return rented;
		}
		void removeRent(pk::item@ item,pk::person@ newOwner)
		{
			//item.owner = newOwner!=null ? newOwner.get_id() : -1;
			//item.location = newOwner != null ? newOwner.service : item.location;
			//item.update();
			//owner.update();
			//if (newOwner != null) newOwner.update();

			//if (newOwner != null)
			//{
			//	//array<int> bbb2 = { newOwner.max_stat[무장능력_통솔],newOwner.max_stat[무장능력_무력],newOwner.max_stat[무장능력_지력] ,newOwner.max_stat[무장능력_정치] ,newOwner.max_stat[무장능력_매력] };
			//	array<int> bbb2 = { newOwner.base_stat[무장능력_통솔],newOwner.base_stat[무장능력_무력],newOwner.base_stat[무장능력_지력] ,newOwner.base_stat[무장능력_정치] ,newOwner.base_stat[무장능력_매력] };
			//	pk::transfer_item(newOwner, newOwner);
			//	for (int i = 0; i < bbb2.length; i++)
			//		newOwner.base_stat[i] = bbb2[i];
			//	newOwner.update();
			//}


			array<int> bbb = { owner.max_stat[무장능력_통솔],owner.max_stat[무장능력_무력],owner.max_stat[무장능력_지력] ,owner.max_stat[무장능력_정치] ,owner.max_stat[무장능력_매력] };
			//array<int> bbb = { owner.base_stat[무장능력_통솔],owner.base_stat[무장능력_무력],owner.base_stat[무장능력_지력] ,owner.base_stat[무장능력_정치] ,owner.base_stat[무장능력_매력] };
			//pk::transfer_item(owner, owner);
			//owner.update();

			transfer(owner, newOwner, item);

			array<int> rented(5, 0);
			for (int i = 0; i < bbb.length; i++)
				rented[i] = bbb[i] - owner.max_stat[i];
			for (int i = 0; i < rented.length; i++)
			{
				owner.base_stat[i] = owner.base_stat[i] + rented[i];
				newOwner.base_stat[i] = newOwner.base_stat[i] - rented[i];
			}
			newOwner.update();
			owner.update();

			//pk::printf("{},base4:{},{}\n", getName(owner), owner.base_stat[무장능력_통솔], owner.base_stat[무장능력_무력]);
			//pk::printf("{},max4:{},{}\n", getName(owner),owner.max_stat[무장능력_통솔], owner.max_stat[무장능력_무력]);
			//pk::printf("{},cur4:{},{}\n", getName(owner),owner.stat[무장능력_통솔], owner.stat[무장능력_무력]);
			//
			//pk::printf("{},base4:{},{}\n", getName(newOwner), newOwner.base_stat[무장능력_통솔], newOwner.base_stat[무장능력_무력]);
			//pk::printf("{},max4:{},{}\n", getName(newOwner), newOwner.max_stat[무장능력_통솔], newOwner.max_stat[무장능력_무력]);
			//pk::printf("{},cur4:{},{}\n", getName(newOwner), newOwner.stat[무장능력_통솔], newOwner.stat[무장능력_무력]);

		}

		void removeRent(pk::item@ item, pk::person@ pOwner, pk::person@ newOwner)
		{
			array<int> bbb = { newOwner.max_stat[무장능력_통솔],newOwner.max_stat[무장능력_무력],newOwner.max_stat[무장능력_지력] ,newOwner.max_stat[무장능력_정치] ,newOwner.max_stat[무장능력_매력] };

			transfer(pOwner, newOwner, item);

			array<int> rented(5, 0);
			for (int i = 0; i < bbb.length; i++)
				rented[i] = newOwner.max_stat[i] - bbb[i];
			for (int i = 0; i < rented.length; i++)
			{
				newOwner.base_stat[i] = newOwner.base_stat[i] - rented[i];
			}
			newOwner.update();

			//pk::printf("{},base4:{},{}\n", getName(newOwner), newOwner.base_stat[무장능력_통솔], newOwner.base_stat[무장능력_무력]);
			//pk::printf("{},max4:{},{}\n", getName(newOwner), newOwner.max_stat[무장능력_통솔], newOwner.max_stat[무장능력_무력]);
			//pk::printf("{},cur4:{},{}\n", getName(newOwner), newOwner.stat[무장능력_통솔], newOwner.stat[무장능력_무력]);

		}

		string getName(pk::object@ obj)
		{
			return obj != null ? pk::decode(pk::get_name(obj)) : "null";
		}


		bool hasSkill(int skill)
		{
			for (int i = 0; i < skills.length; i++)
			{
				if (skills[i] == skill)
					return true;
			}
			return false;
		}

		void apply무장능력(pk::person@ p, int type, int value)
		{
			p.base_stat[type] = p.base_stat[type] + value;
			p.update();
		}

	};

	class ItemRent
	{
		CustomItem@ citem = null;
		pk::item@ item;
		pk::person@ owner0;
		pk::person@ owner;
		array<int> rented;

		void rent()
		{
			//pk::printf("rent:{},{}\n", citem.name, getName(item));
			rented = citem.updateRent(item);
			//pk::printf("rented:{},{},{},{},{}\n", rented[0], rented[1], rented[2], rented[3], rented[4]);

			if (보물_빌려오기_로그표시)
			{
				pk::force@ force = pk::get_force(owner.get_force_id());
				pk::person@ kunshu = pk::get_person(force.kunshu);

				string str = pk::format("\x1b[2x{}\x1b[0x,\x1b[2x{}\x1b[0x의 \x1b[29x{}\x1b[0x 대여", getName(owner), getName(owner0), getName(item));
				pk::history_log(kunshu.get_pos(), force.color, pk::encode(str));
			}

		}
		void rentBack()
		{

			//강제죽음당해서, 아이템 뺏긴상황으로, rented만큼 회복시켜준다.
			if ((owner.mibun == 신분_사망 || owner.mibun ==신분_포로) && item.owner != owner.get_id())
			{
				//pk::printf("사망:{}, rentBack:{},newOwner:{}\n",getName(owner), citem.name,getName(pk::get_person(item.owner)));
				for (int i = 0; i < rented.length; i++)
				{
					owner.base_stat[i] = owner.base_stat[i] + rented[i];
				}
				owner.update();
				citem.removeRent(item,pk::get_person(item.owner), owner0);
				//pk::printf("rentBack:{}\n", getName(pk::get_person(item.owner)));
			}
			else 
			{
				//pk::printf("rentBack:{},{}\n", citem.name, getName(item));
				citem.removeRent(item, owner0);
				//pk::printf("rentBack:{}\n", getName(pk::get_person(item.owner)));
			}

			if (보물_빌려오기_로그표시)
			{
				pk::force@ force = pk::get_force(owner.get_force_id());
				pk::person@ kunshu = force!=null ? pk::get_person(force.kunshu) : null;
				string str = pk::format("\x1b[2x{}\x1b[0x,\x1b[2x{}\x1b[0x의 \x1b[29x{}\x1b[0x 반납", getName(owner), getName(owner0), getName(item));
				pk::history_log(kunshu!=null ? kunshu.get_pos() : pk::point(0,0), force != null ? force.color : 0, pk::encode(str));
			}
		}
		string getName(pk::object@ obj)
		{
			return obj != null ? pk::decode(pk::get_name(obj)) : "null";
		}


	}
	class ItemDisplay
	{
		CustomItem@ citem = null;
		pk::item@ item = null;
		pk::person@ owner = null;
		int itemCount = 0;
		string name;
		int value;
		string path;
	};


	class Main
	{
		pk::func203_t@ prev_callback_203기병전법사망;
		pk::func110_t@ prev_callback_110보물발견확률;
		pk::func258_t@ prev_callback_258;
		pk::func202_t@ prev_callback_202;

		pk::func201_t@ prev_callback_201;
		pk::func209_t@ prev_callback_209;
		pk::func206_t@ prev_callback_206;

		pk::func200_t@ prev_callback_200;
		pk::func220_t@ prev_callback_220;

		pk::func214_t@ prev_callback_214;

		pk::func205_t@ prev_callback_205;
		pk::func207_t@ prev_callback_207;
		pk::func216_t@ prev_callback_216;


		pk::func164_t@ prev_callback_164;
		pk::func167_t@ prev_callback_167;
		pk::func100_t@ prev_callback_100;
		pk::func102_t@ prev_callback_102;
		pk::func103_t@ prev_callback_103;
		pk::func150_t@ prev_callback_150;
		pk::func152_t@ prev_callback_152;
		pk::func151_t@ prev_callback_151;
		pk::func153_t@ prev_callback_153;
		pk::func155_t@ prev_callback_155;

		Main()
		{
			@prev_callback_203기병전법사망 = cast<pk::func203_t@>(pk::get_func(203));
			pk::reset_func(203);
			pk::set_func(203, pk::func203_t(callback203기병전법사망));

			@prev_callback_110보물발견확률 = cast<pk::func110_t@>(pk::get_func(110));
			pk::reset_func(110);
			pk::set_func(110, pk::func110_t(callback110보물발견확률));

			@prev_callback_258 = cast<pk::func258_t@>(pk::get_func(258));
			pk::reset_func(258);
			pk::set_func(258, pk::func258_t(callback258));

			@prev_callback_202 = cast<pk::func202_t@>(pk::get_func(202));
			pk::reset_func(202);
			pk::set_func(202, pk::func202_t(callback202));

			@prev_callback_205 = cast<pk::func205_t@>(pk::get_func(205));
			pk::reset_func(205);
			pk::set_func(205, pk::func205_t(callback205));

			@prev_callback_200 = cast<pk::func200_t@>(pk::get_func(200));
			pk::reset_func(200);
			pk::set_func(200, pk::func200_t(callback200));

			@prev_callback_214 = cast<pk::func214_t@>(pk::get_func(214));
			pk::reset_func(214);
			pk::set_func(214, pk::func214_t(callback214));

			@prev_callback_206 = cast<pk::func206_t@>(pk::get_func(206));
			pk::reset_func(206);
			pk::set_func(206, pk::func206_t(callback206));

			@prev_callback_207 = cast<pk::func207_t@>(pk::get_func(207));
			pk::reset_func(207);
			pk::set_func(207, pk::func207_t(callback207));

			@prev_callback_209 = cast<pk::func209_t@>(pk::get_func(209));
			pk::reset_func(209);
			pk::set_func(209, pk::func209_t(callback209));

			@prev_callback_201 = cast<pk::func201_t@>(pk::get_func(201));
			pk::reset_func(201);
			pk::set_func(201, pk::func201_t(callback201));

			@prev_callback_220 = cast<pk::func220_t@>(pk::get_func(220));
			pk::reset_func(220);
			pk::set_func(220, pk::func220_t(callback220));


			@prev_callback_167 = cast<pk::func167_t@>(pk::get_func(167));
			pk::reset_func(167);
			pk::set_func(167, pk::func167_t(callback167));

			@prev_callback_100 = cast<pk::func100_t@>(pk::get_func(100));
			pk::reset_func(100);
			pk::set_func(100, pk::func100_t(callback100));

			@prev_callback_102 = cast<pk::func102_t@>(pk::get_func(102));
			pk::reset_func(102);
			pk::set_func(102, pk::func102_t(callback102));

			@prev_callback_103 = cast<pk::func103_t@>(pk::get_func(103));
			pk::reset_func(103);
			pk::set_func(103, pk::func103_t(callback103));

			@prev_callback_150 = cast<pk::func150_t@>(pk::get_func(150));
			pk::reset_func(150);
			pk::set_func(150, pk::func150_t(callback150));

			@prev_callback_152 = cast<pk::func152_t@>(pk::get_func(152));
			pk::reset_func(152);
			pk::set_func(152, pk::func152_t(callback152));

			@prev_callback_151 = cast<pk::func151_t@>(pk::get_func(151));
			pk::reset_func(151);
			pk::set_func(151, pk::func151_t(callback151));

			@prev_callback_153 = cast<pk::func153_t@>(pk::get_func(153));
			pk::reset_func(153);
			pk::set_func(153, pk::func153_t(callback153));

			@prev_callback_155 = cast<pk::func155_t@>(pk::get_func(155));
			pk::reset_func(155);
			pk::set_func(155, pk::func155_t(callback155));

			@prev_callback_216 = cast<pk::func216_t@>(pk::get_func(216));
			pk::reset_func(216);
			pk::set_func(216, pk::func216_t(callback216));

			@prev_callback_164 = cast<pk::func164_t@>(pk::get_func(164));
			pk::reset_func(164);
			pk::set_func(164, pk::func164_t(callback164));


			pk::bind(102, pk::trigger102_t(onInit));
			pk::bind(105, pk::trigger105_t(saveData));
			pk::bind(107, pk::trigger107_t(onNewDay));
			pk::bind(174, pk::trigger174_t(onUnitEnd));
			//pk::bind(173, pk::trigger174_t(onUnitExp));
			pk::bind(111, pk::trigger111_t(onTurnStart));
			pk::bind(112, pk::trigger112_t(onTurnEnd));
			pk::bind(170, pk::trigger170_t(onUnitCreate));



			pk::menu_item 신보물일람;
			신보물일람.menu = 2;
			신보물일람.is_enabled = pk::menu_item_is_enabled_t(isEnabled);
			신보물일람.get_desc = pk::menu_item_get_desc_t(getDesc_신보물일람);
			신보물일람.get_text = pk::menu_item_get_text_t(getText_신보물일람);
			신보물일람.handler = pk::menu_item_handler_t(handler_신보물일람);
			pk::add_menu_item(신보물일람);


			pk::menu_item 신보물수여;
			신보물수여.menu = 102;
			신보물수여.pos = 5;
			신보물수여.init = pk::building_menu_item_init_t(신보물수여Init);
			신보물수여.is_enabled = pk::menu_item_is_enabled_t(Is신보물수여Enabled);
			신보물수여.get_text = pk::menu_item_get_text_t(신보물수여Text);
			신보물수여.get_desc = pk::menu_item_get_desc_t(신보물수여Desc);
			신보물수여.handler = pk::menu_item_handler_t(신보물수여Handler);
			pk::add_menu_item(신보물수여);


		}

		array<ItemRent@> _rent;
		pk::list<pk::person@> 사망자리스트;
		array<pk::person@> _attackers;
		array<pk::person@> _defenders;


		void onInit()
		{
			for (int i = 0; i < 커스텀아이템스.length; i++)
			{
				CustomItem@ ci = 커스텀아이템스[i];
				@ci.owner = null;
			}

			if (!loadData())
			{
				for (int i = 0; i < 커스텀아이템스.length; i++)
				{
					CustomItem@ ci = 커스텀아이템스[i];
					if(ci==null || ci.fowner ==null)
						continue;

					pk::person@ o = ci.fowner;
					@ci.owner = null;
					ci.updateOwner(o);
				}
			}

			//for (int i = 0; i < 커스텀아이템스.length; i++)
			//{
			//	CustomItem@ ci = 커스텀아이템스[i];
			//	pk::printf("신보물:{}\n", getName(ci.owner));
			//}

			exportItem();
		}
		bool loadData()
		{
			사망자리스트.clear();
			_attackers = {};
			_defenders = {};

			int count = int(pk::load(KEY, 0, 0));
			int li = 1;
			if (count == 0)
				return false;



			for (int i = 0; i < count; i++)
			{
				CustomItem@ ci = 커스텀아이템스[i];
				int oid = int(pk::load(KEY, li++, -1));
				if(ci!=null)
					@ci.owner = pk::get_person(oid);
			}

			int count2 = int(pk::load(KEY, li++, 0));
			_rent = {};
			
			for (int i = 0; i < count2; i++)
			{
				int cid = int(pk::load(KEY, li++, -1));
				int iid = int(pk::load(KEY, li++, -1));
				int oid0 = int(pk::load(KEY, li++, -1));
				int oid1 = int(pk::load(KEY, li++, -1));

				int len = int(pk::load(KEY, li++, -1));
				array<int> rented(len, 0);
				for (int j = 0; j < len; j++)
					rented[j] = int(pk::load(KEY, li++, 0));

				ItemRent ir;
				@ir.citem = 커스텀아이템스[cid];
				@ir.item = pk::get_item(iid);
				@ir.owner0 = pk::get_person(oid0);
				@ir.owner = pk::get_person(oid1);
				ir.rented = rented;
				_rent.insertLast(ir);
			}

			int count3 = int(pk::load(KEY, li++, 0));
			for (int i = 0; i < count3; i++)
			{
				int pp = int(pk::load(KEY, li++, -1));
				pk::person@ p = pp >= 0 ? pk::get_person(pp) : null;
				if (p == null)
					continue;
				사망자리스트.add(p);
			}
			int count5 = int(pk::load(KEY, li++, 0));
			for (int i = 0; i < count5; i++)
			{
				int p0 = int(pk::load(KEY, li++, -1));
				int p1 = int(pk::load(KEY, li++, -1));
				if (p0 < 0 || p1 < 0)
					continue;
				pk::person@ pp0 = p0 >= 0 ? pk::get_person(p0) : null;
				pk::person@ pp1 = p1 >= 0 ? pk::get_person(p1) : null;
				if (pp0 == null || pp1 == null)
					continue;

				_attackers.insertLast(pp0);
				_defenders.insertLast(pp1);
			}

			_turnCount = int(pk::load(KEY, li++, 0));
			return true;
		}
		void saveData(int fd)
		{
			pk::store(KEY, 0, 커스텀아이템스.length);
			int si = 1;
			for (int i = 0; i < 커스텀아이템스.length; i++)
			{
				CustomItem@ ci = 커스텀아이템스[i];
				pk::store(KEY, si++, (ci!=null && ci.owner!=null) ? ci.owner.get_id() : -1);
			}

			pk::store(KEY, si++, _rent.length);
			for (int i = 0; i < _rent.length; i++)
			{
				ItemRent@ ir = _rent[i];
				pk::store(KEY, si++, ir.citem.id);
				pk::store(KEY, si++, ir.item.get_id());
				pk::store(KEY, si++, ir.owner0 != null ? ir.owner0.get_id() : -1);
				pk::store(KEY, si++, ir.owner != null ? ir.owner.get_id() : -1);
				pk::store(KEY, si++, ir.rented.length);
				for (int j = 0; j < ir.rented.length; j++)
				{
					pk::store(KEY, si++, ir.rented[j]);
				}
			}

			pk::store(KEY, si++, 사망자리스트.count);
			for (int i = 0; i < 사망자리스트.count; i++)
			{
				pk::store(KEY, si++, 사망자리스트[i].get_id());
			}
			pk::store(KEY, si++, _attackers.length);
			for (int i = 0; i < _attackers.length; i++)
			{
				pk::store(KEY, si++, _attackers[i].get_id());
				pk::store(KEY, si++, _defenders[i].get_id());
			}

			pk::store(KEY, si++, _turnCount);
		}
		void exportItem()
		{
			pk::store(KEY_EXPORT, 0, 커스텀아이템스.length);
			int si = 1;
			for (int i = 0; i < 커스텀아이템스.length; i++)
			{
				CustomItem@ ci = 커스텀아이템스[i];
				pk::store(KEY_EXPORT, si++, (ci != null && ci.owner != null) ? ci.owner.get_id() : -1);
			}
		}

		void giveItems_서책(CustomItem@ item, pk::force@ force)
		{
			pk::list<pk::person@> persons0 = pk::get_person_list(force, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반));
			pk::list<pk::person@> persons;

			for (int i = 0; i < persons0.count; i++)
			{
				pk::person@ p = persons0[i];
				if (p.mibun != 신분_군주 && (hasCustomItemType(p, item.type) || hasItemType(p, item.type)))
					continue;
				if (p.get_id() >= 무장_영제 && p.get_id() <= 무장_이벤트A0 || p.get_id() >= 적장_시작)
					continue;

				if (p.mibun == 신분_군주)
				{
					int count0 = hasCustomItemTypeCount(p, item.type);
					int count1 = hasItemTypeCount(p, item.type);
					if (count0 + count1 > 1)
						continue;
				}

				persons.add(p);
			}

			if (persons.count > 0)
			{
				persons.sort(function(x, y) {
					int sumX = x.stat[무장능력_지력] + x.stat[무장능력_정치];
					int sumY = y.stat[무장능력_지력] + y.stat[무장능력_정치];
					return sumX >= sumY;
				});
			}

			//군주가 최종3인에 있으면 무조건 군주에게.
			pk::person@ target = null;
			if (persons.count > 0 && persons[0].mibun == 신분_군주)
				@target = persons[0];
			if (target == null && persons.count > 1 && persons[1].mibun == 신분_군주)
				@target = persons[1];
			if (target == null && persons.count > 2 && persons[2].mibun == 신분_군주)
				@target = persons[2];


			pk::list<pk::person@> person2;

			if (target == null)
			{
				if (persons.count > 0)
					person2.add(persons[0]);
				if (persons.count > 1)
					person2.add(persons[1]);
				if (persons.count > 2)
					person2.add(persons[2]);
				person2.shuffle();
				@target = person2[0];
			}

			if (target.mibun == 신분_군주)
				return;

			pk::person@ kunshu = pk::get_person(force.kunshu);
			string str = pk::format("\x1b[2x{}군\x1b[0x,신보물 \x1b[29x{}\x1b[0x ,\x1b[2x{}\x1b[0x 에게 하사", getName(kunshu), item.name, getName(target));
			pk::history_log(kunshu != null ? kunshu.get_pos() : pk::point(0, 0), force.color, pk::encode(str));

			item.updateOwner(target);
		}

		void giveItems_검_창_활_암기_말(CustomItem@ item, pk::force@ force)
		{
			pk::list<pk::person@> persons0 = pk::get_person_list(force, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반));
			pk::list<pk::person@> persons;

			for (int i = 0; i < persons0.count; i++)
			{
				pk::person@ p = persons0[i];
				if(p.mibun != 신분_군주 && (hasCustomItemType(p,item.type) || hasItemType(p,item.type)))
					continue;
				if (p.get_id() >= 무장_영제 && p.get_id() <= 무장_이벤트A0 || p.get_id() >= 적장_시작)
					continue;

				if (p.mibun == 신분_군주)
				{
					int count0 = hasCustomItemTypeCount(p, item.type);
					int count1 = hasItemTypeCount(p, item.type);
					if(count0 + count1 > 1)
						continue;
				}

				persons.add(p);
			}

			if (persons.count > 0)
			{
				persons.sort(function(x, y) {
					int sumX = x.stat[무장능력_무력] + x.stat[무장능력_통솔];
					int sumY = y.stat[무장능력_무력] + y.stat[무장능력_통솔];
					return sumX >= sumY;
				});
			}

			//군주가 최종3인에 있으면 무조건 군주에게.
			pk::person@ target = null;
			if (persons.count > 0 && persons[0].mibun == 신분_군주)
				@target = persons[0];
			if (target==null && persons.count > 1 && persons[1].mibun == 신분_군주)
				@target = persons[1];
			if (target == null && persons.count > 2 && persons[2].mibun == 신분_군주)
				@target = persons[2];


			pk::list<pk::person@> person2;

			if (target == null)
			{
				if (persons.count > 0)
					person2.add(persons[0]);
				if (persons.count > 1)
					person2.add(persons[1]);
				if (persons.count > 2)
					person2.add(persons[2]);
				person2.shuffle();
				@target = person2[0];
			}

			if (target.mibun == 신분_군주)
				return;

			pk::person@ kunshu = pk::get_person(force.kunshu);
			string str = pk::format("\x1b[2x{}군\x1b[0x,신보물 \x1b[29x{}\x1b[0x ,\x1b[2x{}\x1b[0x 에게 하사", getName(kunshu), item.name, getName(target));
			pk::history_log(kunshu != null ? kunshu.get_pos() : pk::point(0, 0), force.color, pk::encode(str));
			
			item.updateOwner(target);

		}

		void 포로처리()
		{
			for (int i = 0; i < 무장_끝; i++)
			{
				pk::person@ p = pk::get_person(i);
				if (p == null)
					continue;
				if (p.mibun != 신분_포로)
					continue;
				array<CustomItem@> arr = getCustomItem(p);
				if (arr.length == 0)
					continue;

				pk::unit@ u = getUnit(p.get_pos());
				if(u==null)
					continue;
				for (int j = 0; j < arr.length; j++)
				{
					CustomItem@ ci = arr[j];
					pk::person@ kunshu = pk::get_person(pk::get_force(u.get_force_id()).kunshu);
					@_scene_citem_강탈 = ci;
					@_scene_kunshu_강탈 = kunshu;
					@_scene_item_강탈 = null;
					try
					{
						pk::scene(pk::scene_t(scene_보물_강탈));
					}
					catch
					{
					}
					ci.updateOwner(kunshu);
				}
			}
		}

		void 사망자처리()
		{
			for (int i = 0; i < 무장_끝; i++)
			{
				pk::person@ p = pk::get_person(i);
				if (p == null)
					continue;
				if (p.mibun != 신분_사망 || p.get_id() == 무장_적장 || getName(p) == "적장")
					continue;


				array<CustomItem@> arr=getCustomItem(p);
				if(arr.length == 0)
					continue;

				bool bFound = false;
				for (int k = 0; k < 사망자리스트.count; k++)
				{
					pk::person@ p2 = 사망자리스트[k];
					if (p.get_id() == p2.get_id())
					{
						bFound = true;
						break;
					}
				}
				if (bFound)
					continue;
				
				bFound = false;

				for (int j = _defenders.length - 1; j >= 0; j--)
				{
					pk::person@ p2 = _defenders[j];
					if (p.get_id() != p2.get_id())
						continue;


					for (int k = 0; k < arr.length; k++)
					{
						CustomItem@ ci = arr[k];
						pk::person@ kunshu = pk::get_person(pk::get_force(_attackers[j].get_force_id()).kunshu);
						@_scene_citem_강탈 = ci;
						@_scene_kunshu_강탈 = kunshu;
						@_scene_item_강탈 = null;
						try
						{
							pk::scene(pk::scene_t(scene_보물_강탈));
						}
						catch
						{

						}

						ci.updateOwner(kunshu);
						bFound = true;
					}

					break;
				}
				if (!bFound)
				{
					for (int k = 0; k < arr.length; k++)
					{
						CustomItem@ ci = arr[k];

						@_scene_citem_강탈 = ci;
						@_scene_item_강탈 = null;
						try
						{
							pk::scene(pk::scene_t(scene_보물_재야));
						}
						catch
						{
						}

						ci.updateOwner(null);
					}
				}
			}
		}

		void onNewDay()
		{
			_turnCount = 0;
			사망자처리();
			for (int i = 0; i < 커스텀아이템스.length; i++)
			{
				CustomItem@ item = 커스텀아이템스[i];
				if (item == null || item.owner == null)
					continue;
				if(item.owner.mibun != 신분_군주)
					continue;
				if(item.owner.is_player())
					continue;

				if(item.type == 보물종류_서책)
					giveItems_서책(item, pk::get_force(item.owner.get_force_id()));
				else
					giveItems_검_창_활_암기_말(item, pk::get_force(item.owner.get_force_id()));
			}

			while (_attackers.length > 0)
				_attackers.removeAt(0);
			while (_defenders.length > 0)
				_defenders.removeAt(0);


			사망자리스트.clear();
			for (int i = 0; i < 무장_끝; i++)
			{
				pk::person@ p = pk::get_person(i);
				if (p == null)
					continue;

				if (p.mibun != 신분_사망)
					continue;
				사망자리스트.add(p);
			}
		}

		bool updateRentArea(array<ItemRent@>@ arr, CustomItem@ it,pk::person@ p,pk::list<pk::force@> forces)
		{
			pk::list<pk::item@> items;
			for (int i = 0; i < 보물_끝; i++)
			{
				pk::item@ it0 = pk::get_item(i);
				if(it0==null)
					continue;
				if(it0.type==-1)
					continue;
				if(it0.type != it.type)
					continue;
				if(it0.status == 보물상태_미등장 || it0.status == 보물상태_파기)
					continue;

				bool bFound = false;
				for (int j = 0; j < arr.length; j++)
				{
					if (arr[j].item.get_id() == it0.get_id())
					{
						bFound = true;
						break;
					}
				}
				if (!bFound)
					items.add(it0);
			}

			for (int i = 0; i < items.count; i++)
			{
				pk::item@ it0 = items[i];
				if (it0.get_id() == it.srcItem)
				{
					pk::person@ owner = null;
					if (it0.owner != -1)
					{
						@owner = pk::get_person(it0.owner);
						if (pk::is_unitize(owner))
						{
							int dist = pk::get_distance(p.get_pos(), owner.get_pos());
							if(dist <= 아이템_공유_거리 || p.get_force_id() == owner.get_force_id())
								continue;
							bool bFound2 = false;
							for (int j = 0; j < forces.count; j++)
							{
								if (forces[j].get_id() == owner.get_force_id())
								{
									bFound2 = true;
									break;
								}
							}
							if(bFound2)
								continue;
						}
					}

					ItemRent ir0;
					@ir0.citem = it;
					@ir0.item = it0;
					@ir0.owner = p;
					@ir0.owner0 = owner;
					arr.insertLast(ir0);
					return true;
				}
			}


			int minOff = 1000;
			pk::item@ minItem = null;
			for (int i = 0; i < items.count; i++)
			{
				pk::item@ it0 = items[i];
				pk::person@ owner = pk::get_person(it0.owner);
				if (owner != null)
				{
					if (pk::is_unitize(owner))
					{
						int dist = pk::get_distance(p.get_pos(), owner.get_pos());
						if (dist <= 아이템_공유_거리 || p.get_force_id() == owner.get_force_id())
							continue;

						bool bFound2 = false;
						for (int j = 0; j < forces.count; j++)
						{
							if (forces[j].get_id() == owner.get_force_id())
							{
								bFound2 = true;
								break;
							}
						}
						if (bFound2)
							continue;

					}
				}


				int off1 = pk::abs(it0.value - it.value);
				if (off1 < minOff)
				{
					@minItem = it0;
					minOff = off1;
				}
			}

			if (minItem == null)
				return false;

			ItemRent ir;
			@ir.citem = it;
			@ir.item = minItem;
			@ir.owner = p;
			@ir.owner0 = pk::get_person(minItem.owner);
			arr.insertLast(ir);
			return true;
		}

		void updateRent(pk::person@ p, array<ItemRent@>@ rent,pk::list<pk::force@> forces)
		{
			if (p == null)
				return;
			array<CustomItem@> arr = getCustomItem(p);
			if (arr.length == 0)
				return;

			arr.sort(function(a, b) { return a.value >= b.value; });
			array<int> types;
			for (int i = 0; i < 보물_끝; i++)
			{
				pk::item@ it = pk::get_item(i);
				if(it==null)
					continue;
				if (it.owner == p.id)
				{
					if(types.find(it.type) == -1)
						types.insertLast(it.type);
				}
			}

			for (int j = 0; j < arr.length; j++)
			{
				CustomItem@ it = arr[j];
				if (types.find(it.type) != -1)
					continue;
				if (it.type == 보물종류_서책 || it.type == 보물종류_동작 || it.type == 보물종류_옥새)
					continue;

				bool bFound = false;
				for (int i = 0; i < rent.length; i++)
				{
					ItemRent@ ir = rent[i];
					if (ir.citem.id == it.id)
					{
						bFound = true;
					}
				}
				if(bFound)
					continue;

				if (updateRentArea(rent, it, p,forces))
					types.insertLast(it.type);
				
			}
		}

		ItemRent@ getRent(CustomItem@ ci)
		{
			for (int i = 0; i < _rent.length; i++)
			{
				ItemRent@ ir = _rent[i];
				if (ir.citem.id == ci.id)
					return ir;
			}
			return null;
		}
		void removeRent(ItemRent@ ir)
		{
			ir.rentBack();

			int a=_rent.findByRef(ir);
			_rent.removeAt(a);
			
		}

		void onTurnStart(pk::force@ f)
		{
			for (int i = 0; i < _rent.length; i++)
			{
				ItemRent@ ir = _rent[i];
				ir.rentBack();
			}
			_rent = {};

			도망자_처리();
			_attackersPerson보물 = {};
			_targetrsPerson보물 = {};


			//pk::printf("onTurnStart:{}\n", getName(f));
			exportItem();
			array<pk::person@> ps;
			array<ItemRent@> rent;
			pk::list<pk::person@> persons = pk::get_person_list(f,pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반));
			if (보물_빌려오기)
			{
				pk::list<pk::force@> fs2;
				fs2.add(f);
				pk::list<pk::force@> fs;
				pk::list<pk::unit@> us = pk::get_unit_list(f);
				for (int i = 0; i <us.count ; i++)
				{
					pk::unit@ u = us[i];
					array<pk::point> arr = pk::range(u.get_pos(), 1, 아이템_공유_거리_공격);
					for (int j = 0; j < arr.length; j++)
					{
						pk::point pt = arr[j];
						pk::unit@ u2 = getUnit(pt);
						if(u2 == null || !pk::is_enemy(u,u2))
							continue;

						pk::force@ f2 = pk::get_force(u2.get_force_id());
						if(f2==null)
							continue;

						bool bFound = false;
						for (int k = 0; k < fs.count; k++)
						{
							pk::force@ ff = fs[k];
							if (ff.get_id() == f2.get_id())
							{
								bFound = true;
								break;
							}
						}
						if (!bFound)
							fs.add(f2);
					}
				}
				
				
				for (int i = 0; i < persons.count; i++)
				{
					pk::person@ p = persons[i];
					pk::unit@ u = getUnit(p.get_pos());
					if (u == null)
						continue;

					updateRent(p, rent,fs);
					ps.insertLast(p);

					array<pk::point> pts = pk::range(u.get_pos(), 1, 아이템_공유_거리_공격);
					for (int j = 0; j < pts.length; j++)
					{
						pk::point pt = pts[j];
						pk::unit@ u2 = getUnit(pt);
						if (u2 == null || !pk::is_enemy(u, u2))
							continue;
						pk::person@ p0 = pk::get_person(u2.member[0]);
						pk::person@ p1 = pk::get_person(u2.member[1]);
						pk::person@ p2 = pk::get_person(u2.member[2]);
						if (p0 != null && ps.findByRef(p0) == -1)
						{
							updateRent(p0, rent,fs2);
							ps.insertLast(p0);
						}
						if (p1 != null && ps.findByRef(p1) == -1)
						{
							updateRent(p1, rent,fs2);
							ps.insertLast(p1);
						}
						if (p2 != null && ps.findByRef(p2) == -1)
						{
							updateRent(p2, rent,fs2);
							ps.insertLast(p2);
						}
					}
				}
			}
			for (int i = 0; i < rent.length; i++)
			{
				ItemRent@ ir = rent[i];
				ir.rent();
			}
			_rent = rent;


			pk::list<pk::unit@> units = pk::get_unit_list(f);
			for (int i = 0; i < units.count; i++)
			{
				pk::unit@ u = units[i];
				onTurn주악(u);
				onTurn주악_보물특기(u);
				onTurn진정_화계(u);
				onTurn인접_병력_회복(u);
				//onTurn진정_교란_위보(u);
			}
			onTurn기교포인트(f);
		}
		pk::person@ _scene_attacker = null;
		pk::person@ _scene_target = null;
		pk::unit@ _scene_attackerUnit = null;
		pk::unit@ _scene_targetUnit = null;

		void scene_일기토()
		{
			pk::message_box(pk::encode("적장을 찾았다"), _scene_attacker);
			pk::message_box(pk::encode("좋다 후회하게 될것이다"), _scene_target);

			bool b0 = pk::is_player_controlled(_scene_attackerUnit);
			bool b1 = pk::is_player_controlled(_scene_targetUnit);

			pk::duel(_scene_attackerUnit, _scene_targetUnit, _scene_attacker, null, null, _scene_target, null, null, b0, b1, 0, b0 || b1).first;
		}

		int _turnCount = 0;
		void onTurnEnd(pk::force@ f)
		{
			//pk::printf("onTurnEnd:{},{}\n", _turnCount++, getName(f));
			pk::list<pk::unit@> units = pk::get_unit_list(f);
			for (int i = 0; i < units.count; i++)
			{
				pk::unit@ unit = units[i];
				if(!has보물skill(unit, 보물특기_일기토_유발))
					continue;

				for (int j = 0; j < 6; j++)
				{
					pk::point pt = pk::get_neighbor_pos(unit.get_pos(), j, 1);
					pk::unit@ unit2 = getUnit(pt);
					if (unit2 == null || !pk::is_enemy(unit, unit2))
						continue;
					if (!pk::rand_bool(일기토_유발_확률))
						continue;
					if(pk::get_person(unit2.leader).stat[무장능력_무력] > pk::get_person(unit.leader).stat[무장능력_무력] + 일기토_회피_무력_차)
						continue;

					@_scene_attackerUnit = unit;
					@_scene_targetUnit = unit2;
					@_scene_attacker = pk::get_person(unit.leader);
					@_scene_target = pk::get_person(unit2.leader);
					pk::scene(pk::scene_t(scene_일기토));
					break;
				}
			}

			if (pk::get_force_list(true).count == _turnCount)
			{
				//pk::printf("onTurnEnd clear\n");
				for (int i = 0; i < _rent.length; i++)
				{
					ItemRent@ ir = _rent[i];
					ir.rentBack();
				}
				_rent = {};
			}

			_attackers보물 = {};
			_targets보물 = {};
			_damages보물 = {};
			_points보물 = {};

			for (int i = 0; i < units.count; i++)
			{
				pk::unit@ u = units[i];
				onTurn진정_화계(u);
				//onTurn진정_교란_위보(u);
			}

			onTurn진정_교란_위보AI(f);
			포로처리();
			//pk::printf("onTurnEnd:{}\n", getName(f));
		}

		void onTurn진정_교란_위보AI(pk::force@ f)
		{
			pk::list<pk::unit@> us = pk::get_unit_list(f);

			pk::list<pk::unit@> already;
			for (int i = 0; i < us.count; i++)
			{
				pk::unit@ u = us[i];
				if(!pk::is_valid_pos(u.get_pos()))
					continue;

				array<pk::point> arr = pk::range(u.get_pos(),1,5);
				for (int j = 0; j < arr.length; j++)
				{
					pk::point pt = arr[j];
					pk::unit@ u2 = pk::is_valid_pos(pt) ? pk::get_unit(pt) : null;
					if (u2 == null)
						continue;
					bool bFound = false;
					for (int k = 0; k < already.count; k++)
					{
						pk::unit@ uu = already[k];
						if(uu.get_id() != u2.get_id())
							continue;

						bFound = true;
						break;
					}
					if(bFound)
						continue;

					if(!onTurn진정_교란_위보(u2))
						continue;
					already.add(u2);
				}
			}
		}

		bool onTurn진정_교란_위보(pk::unit@ u)
		{
			if (!has보물skill(u, 보물특기_인접_혼란_위보_진정))
				return false;

			array<pk::point> pts = pk::range(u.get_pos(), 0, 인접_혼란_위보_회복_범위);
			for (int i = 0; i < pts.length; i++)
			{
				pk::point pt = pts[i];
				pk::unit@ unit = getUnit(pt);
				if(unit==null || pk::is_enemy(u,unit))
					continue;

				if (unit.status != 부대상태_통상)
				{
					//pk::create_effect(0x3c, unit.get_pos());
					create_effect(0x3c, unit.get_pos());
					pk::set_status(unit, u, 부대상태_통상, 0);
					pk::set_action_done(u, false);
					u.action_done = false;
					u.update();
					pk::say(pk::encode("휴 살았소"), pk::get_person(unit.leader), unit);
				}
			}
			return true;
		}
		void onTurn진정_화계(pk::unit@ u)
		{
			if (!has보물skill(u, 보물특기_인접_화계_소화))
				return;

			array<pk::point> pts = pk::range(u.get_pos(), 0, 인접_소화_범위);
			for (int i = 0; i < pts.length; i++)
			{
				pk::point pt = pts[i];
				pk::unit@ unit = getUnit(pt);
				if (unit == null || pk::is_enemy(u, unit))
					continue;
				if(!pk::is_on_fire(pt))
					continue;
				//pk::printf("{},화계0\n", getNameLeader(unit));
				create_effect(0x3b, pt);
				pk::get_hex(pt).fire_timer = 0;
			}
		}
		void onTurn인접_병력_회복(pk::unit@ u)
		{
			if (!has보물skill(u, 보물특기_인접_회복))
				return;


			array<pk::point> pts = pk::range(u.get_pos(), 0, 인접_회복_범위);
			for (int i = 0; i < pts.length; i++)
			{
				pk::point pt = pts[i];
				pk::unit@ unit = getUnit(pt);
				if (unit == null || pk::is_enemy(u, unit))
					continue;

				pk::add_troops(unit, 인접_병력_회복량, true);
			}
		}

		void onTurn기교포인트(pk::force@ f)
		{
			pk::list<pk::person@> persons = pk::get_person_list(f, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반));
			bool b = false;

			for (int i = 0; i < persons.count; i++)
			{
				pk::person@ p = persons[i];
				if (has보물skill(p, 보물특기_기교포인트_획득))
				{
					b = true;
					break;
				}
			}
			if (b)
			{
				pk::add_tp(f, 턴당_기교포인트, pk::get_person(f.kunshu).get_pos());
			}

			b = false;
			for (int i = 0; i < persons.count; i++)
			{
				pk::person@ p = persons[i];
				if (has보물skill(p, 보물특기_능력연구속도향상))
				{
					b = true;
					break;
				}
			}
			if (b)
			{
				if(f.researching_ability_timer >1)
					f.researching_ability_timer--;
			}

		}


		void onTurn주악(pk::unit@ u)
		{
			if (u.has_skill(특기_주악))
				return;
			if (!hasCustomItemSkill(u, 특기_주악))
				return;

			pk::person@ l = pk::get_person(u.leader);
			int bskill = l.skill;

			setSkill(l, 특기_주악);
			pk::add_energy(u, int(pk::core::skill_constant(l.get_id(), 특기_주악)), true);
			resetSkill(l, bskill);
		}


		void onTurn주악_보물특기(pk::unit@ u)
		{
			if (!has보물skill(u, 보물특기_주악))
				return;
			pk::add_energy(u, 주악_기력, true);
		}


		bool hasCustomItem(pk::person@ p)
		{
			for (int i = 0; i < 커스텀아이템스.length; i++)
			{
				CustomItem@ ci = 커스텀아이템스[i];
				if(ci!=null)
					continue;
				if (ci.owner == null)
					continue;
				if (ci.owner.get_id() == p.get_id())
					return true;
			}
			return false;
		}

		bool hasCustomItemType(pk::person@ p, int type)
		{
			for (int i = 0; i < 커스텀아이템스.length; i++)
			{
				CustomItem@ ci = 커스텀아이템스[i];
				if (ci != null)
					continue;
				if (ci.owner == null)
					continue;
				if (ci.owner.get_id() != p.get_id())
					continue;

				if (ci.type == type)
					return true;
			}
			return false;

		}
		int hasCustomItemTypeCount(pk::person@ p, int type)
		{
			int count = 0;
			for (int i = 0; i < 커스텀아이템스.length; i++)
			{
				CustomItem@ ci = 커스텀아이템스[i];
				if (ci != null)
					continue;
				if (ci.owner == null)
					continue;
				if (ci.owner.get_id() != p.get_id())
					continue;

				if (ci.type == type)
					count++;
			}
			return count;

		}

		bool hasItemType(pk::person@ p, int type)
		{
			for (int i = 0; i < 보물_끝; i++)
			{
				pk::item@ it = pk::get_item(i);
				if(it==null)
					continue;
				if(it.type==-1)
					continue;
				if(it==null || it.owner != p.get_id())
					continue;

				if (it.type == type)
					return true;
			}
			return false;
		}
		int hasItemTypeCount(pk::person@ p, int type)
		{
			int count = 0;
			for (int i = 0; i < 보물_끝; i++)
			{
				pk::item@ it = pk::get_item(i);
				if (it == null || it.owner != p.get_id())
					continue;
				if (it.type == -1)
					continue;

				if (it.type == type)
					count++;
			}
			return count;

		}

		bool hasCustomItemSkill(pk::unit@ u, int skill)
		{
			pk::person@ p0 = pk::get_person(u.member[0]);
			pk::person@ p1 = pk::get_person(u.member[1]);
			pk::person@ p2 = pk::get_person(u.member[2]);

			return hasCustomItemSkill(p0, skill) || hasCustomItemSkill(p1, skill) || hasCustomItemSkill(p2, skill);
		}

		bool hasCustomItemSkill(pk::person@ p,int skill)
		{
			if (p == null)
				return false;
			for (int i = 0; i < 커스텀아이템스.length; i++)
			{
				CustomItem@ ci = 커스텀아이템스[i];
				if(ci==null)
					continue;
				if (ci.owner == null)
					continue;
				if (ci.owner.get_id() != p.get_id())
					continue;

				for (int j = 0; j < ci.skills.length; j++)
				{
					if (skill == ci.skills[j])
						return true;
				}
			}
			return false;
		}



		array<CustomItem@> getCustomItem(pk::unit@ u)
		{
			array<CustomItem@> arr;
			for (int i = 0; i < 커스텀아이템스.length; i++)
			{
				CustomItem@ ci = 커스텀아이템스[i];
				if (ci == null)
					continue;
				if (ci.owner == null)
					continue;
				
				if (ci.owner.get_id() == u.member[0])
				{
					arr.insertLast(ci);
				}
				if (ci.owner.get_id() == u.member[1])
				{
					arr.insertLast(ci);
				}
				if (ci.owner.get_id() == u.member[2])
				{
					arr.insertLast(ci);
				}
			}
			return arr;
		}
		array<CustomItem@> getCustomItem(pk::person@ p)
		{
			array<CustomItem@> arr;
			for (int i = 0; i < 커스텀아이템스.length; i++)
			{
				CustomItem@ ci = 커스텀아이템스[i];
				if(ci==null)
					continue;
				if (ci.owner == null)
					continue;
				if (ci.owner.get_id() == p.get_id())
				{
					arr.insertLast(ci);
				}
			}
			return arr;
		}
		array<pk::item@> getItem(pk::person@ p)
		{
			array<pk::item@> arr;
			for (int i = 0; i < 보물_끝; i++)
			{
				pk::item@ ci = pk::get_item(i);
				if(ci==null)
					continue;
				if(ci.type == -1)
					continue;
				if (ci.owner == -1)
					continue;
				if (ci.owner == p.get_id())
				{
					arr.insertLast(ci);
				}
			}
			return arr;
		}


		void 도망자_처리(pk::person@ p, pk::force@ f)
		{
			if (p.hp != 1 || p.order != 무장임무_귀환 || p.mibun == 신분_포로 || p.mibun == 신분_사망)
				return;
			if (f == null)
				return;
			pk::person@ kunshu = pk::get_person(f.kunshu);
			if (kunshu == null)
				return;

			pk::printf("도망자:{},상대:{}\n", getName(p), getName(f));
			array<CustomItem@> arr = getCustomItem(p);
			if (arr.length == 0)
				return;

			for (int k = 0; k < arr.length; k++)
			{
				CustomItem@ ci = arr[k];
				ItemRent@ ir = getRent(ci);
				if (ir != null)
					removeRent(ir);

				pk::person@ kunshu = kunshu;
				@_scene_citem_강탈 = ci;
				@_scene_kunshu_강탈 = kunshu;
				@_scene_item_강탈 = null;
				try
				{
					pk::scene(pk::scene_t(scene_보물_강탈));
				}
				catch
				{
				}
				ci.updateOwner(kunshu);
			}
		}

		void 도망자_처리()
		{
			for (int i = 0; i < _attackersPerson보물.length; i++)
			{
				pk::list<pk::person@> ps0 = _attackersPerson보물[i];
				pk::list<pk::person@> ps1 = _targetrsPerson보물[i];
				if(ps0.count == 0 || ps1.count == 0)
					continue;
				for (int j = 0; j < ps0.count; j++)
				{
					도망자_처리(ps0[j], pk::get_force(ps1[0].get_force_id()));
				}

				for (int j = 0; j < ps1.count; j++)
				{
					도망자_처리(ps1[j], pk::get_force(ps0[0].get_force_id()));
				}
			}
		}

		CustomItem@ _scene_citem_강탈 = null;
		pk::item@ _scene_item_강탈 = null;
		pk::person@ _scene_kunshu_강탈 = null;

		void scene_보물_강탈()
		{
			string path;
			path = _scene_citem_강탈 != null ? _scene_citem_강탈.path : 보물이미지[_scene_item_강탈.get_id()];
			if (_scene_kunshu_강탈.is_player())
			{
				pk::background(pk::format("{}", path));
				if(_scene_citem_강탈 != null)
					pk::message_box(pk::encode(pk::format("신보물 \x1b[29x{}\x1b[0x 얻었습니다.", _scene_citem_강탈.name)));
				else
					pk::message_box(pk::encode(pk::format("보물 \x1b[29x{}\x1b[0x 얻었습니다.", getName(_scene_item_강탈))));

			}

			pk::force@ force = pk::get_force(_scene_kunshu_강탈.get_force_id());

			string str = "";
			if (_scene_citem_강탈 != null)
				str = pk::format("\x1b[2x{}군\x1b[0x,신보물 \x1b[29x{}\x1b[0x 획득", getName(_scene_kunshu_강탈), _scene_citem_강탈.name);
			else
				str = pk::format("\x1b[2x{}군\x1b[0x,보물 \x1b[29x{}\x1b[0x 획득", getName(_scene_kunshu_강탈), getName(_scene_item_강탈));

			pk::history_log(_scene_kunshu_강탈 != null ? _scene_kunshu_강탈.get_pos() : pk::point(0, 0), force.color, pk::encode(str));

			if(_scene_kunshu_강탈.is_player())
				pk::background(-1);
		}

		void scene_보물_재야()
		{
			string path;
			path = _scene_citem_강탈 != null ? _scene_citem_강탈.path : 보물이미지[_scene_item_강탈.get_id()];
			pk::background(pk::format("{}", path));
			if (_scene_citem_강탈 != null)
				pk::message_box(pk::encode(pk::format("신보물 \x1b[29x{}\x1b[0x 재야", _scene_citem_강탈.name)));
			else
				pk::message_box(pk::encode(pk::format("보물 \x1b[29x{}\x1b[0x 재야", getName(_scene_item_강탈))));

			string str = "";
			if (_scene_citem_강탈 != null)
				str = pk::format("신보물 \x1b[29x{}\x1b[0x 재야", _scene_citem_강탈.name);
			else
				str = pk::format("보물 \x1b[29x{}\x1b[0x 재야", getName(_scene_item_강탈));

			pk::history_log(pk::point(0, 0), 0, pk::encode(str));
			
			pk::background(-1);
		}

		void callback220포로(const pk::destroy_info& in info, pk::list<pk::person@>& captured, pk::list<pk::person@>& escaped, bool tactics_bonus)
		{
			if (captured.count == 0)
				return;

			pk::hex_object@ attacker = info.attacker;
			pk::person@ judge = pk::get_person(pk::get_force(attacker.get_force_id()).kunshu);
			if (judge == null)
				return;

			for (int i = 0; i < captured.count; i++)
			{
				pk::person@ p = captured[i];
				array<CustomItem@> arr = getCustomItem(p);
				if (arr.length > 0)
				{
					for (int j = 0; j < arr.length; j++)
					{
						CustomItem@ ci = arr[j];
						ItemRent@ ir = getRent(ci);
						if (ir != null)
							removeRent(ir);


						@_scene_citem_강탈 = ci;
						@_scene_kunshu_강탈 = judge;
						@_scene_item_강탈 = null;

						try
						{
							if (_scene_kunshu_강탈.is_player())
								pk::scene(pk::scene_t(scene_보물_강탈));
							else
								scene_보물_강탈();
						}
						catch
						{
							
						}

						ci.updateOwner(judge);
					}
				}
				array<pk::item@> arr2 = getItem(p);
				if (arr2.length > 0)
				{
					for (int j = 0; j < arr2.length; j++)
					{
						pk::item@ ci = arr2[j];

						@_scene_citem_강탈 = null;
						@_scene_kunshu_강탈 = judge;
						@_scene_item_강탈 = ci;

						try
						{
							if (_scene_kunshu_강탈.is_player())
								pk::scene(pk::scene_t(scene_보물_강탈));
							else
								scene_보물_강탈();
						}
						catch
						{
						}

						//ci.location = judge.service;
						//ci.owner = judge.get_id();
						//ci.update();
						//judge.update();
					}
					//pk::transfer_item(judge, judge);
				}
			}
		}


		int callback203기병전법사망(pk::person@ attacker, pk::person@ target, int tactics_id, bool critical)
		{
			bool bFound = false;
			for (int i = 0; i < _attackers.length; i++)
			{
				if (attacker.get_id() != _attackers[i].get_id())
					continue;
				if (target.get_id() != _defenders[i].get_id())
					continue;

				bFound = true;
				break;
			}

			if (!bFound)
			{
				_attackers.insertLast(attacker);
				_defenders.insertLast(target);
			}


			return prev_callback_203기병전법사망(attacker, target, tactics_id, critical);
		}

		int callback110보물발견확률(pk::building@ building, pk::person@ actor, pk::item@ item)
		{
			if (커스텀아이템스.length > 0)
			{
				array<CustomItem@> items;
				for (int i = 0; i < 커스텀아이템스.length; i++)
				{
					CustomItem@ ci0 = 커스텀아이템스[i];
					if(ci0==null || ci0.owner!=null)
						continue;
					//if(ci0.name != "대장방패")
					//	continue;


					items.insertLast(ci0);
				}
				
				if (items.length > 0)
				{
					int a = pk::rand(items.length);
					CustomItem@ ci = items[a];
					if (ci.owner == null)
					{
						int n = pk::max(pk::max((61 - ci.value), 0) / 20, 1);
						//if (actor.is_player())
						//	n = 0;
						//else
						//	n = 100;
						////n = 0;
						//n = 100;
						if (pk::rand_bool(n))
						{
							@_scene_item = ci;
							@_scene_actor = actor;
							pk::scene(pk::scene_t(scene_보물발견));
							return 0;
						}
					}
				}
			}
			return prev_callback_110보물발견확률(building, actor, item);
		}




		int callback205(pk::unit@ src, int strategy_id)
		{
			int bSkill = -2;
			pk::person@ leader = pk::get_person(src.leader);
			if (leader != null && !src.has_skill(특기_백출) && hasCustomItemSkill(src,특기_백출))
			{
				bSkill = leader.skill;
				setSkill(leader, 특기_백출);
			}

			int n = prev_callback_205(src, strategy_id);
			if (leader != null && bSkill != -2)
			{
				//leader.skill = bSkill;
				resetSkill(leader, bSkill);
			}

			return n;
		}
		int callback200(pk::unit@ assister, pk::unit@ attacker, pk::unit@ target)
		{
			int bSkill = -2;
			pk::person@ leader = pk::get_person(attacker.leader);
			if (leader != null && !assister.has_skill(특기_보좌) && hasCustomItemSkill(assister,특기_보좌))
			{
				bSkill = leader.skill;
				setSkill(leader, 특기_보좌);
			}

			int n = prev_callback_200(assister, attacker, target);
			if (has보물skill(assister, 보물특기_지원공격확률))
			{
				n = pk::min(100, n + 지원공격확률);
			}


			if (leader != null && bSkill != -2)
			{
				resetSkill(leader, bSkill);
			}

			return n;
		}

		void callback214(pk::damage_info& info, pk::unit@ attacker, pk::hex_object@ target0, bool critical)
		{
			int bSkill = -2;
			pk::person@ leader = attacker != null ? pk::get_person(attacker.leader) : null;
			if (leader != null && !attacker.has_skill(특기_화신) && hasCustomItemSkill(attacker,특기_화신))
			{
				bSkill = leader.skill;
				setSkill(leader, 특기_화신);
			}

			pk::unit@ target = pk::hex_object_to_unit(target0);

			int bSkillTarget = -2;
			pk::person@ leaderTarget = target != null ? pk::get_person(target.leader) : null;
			if (leaderTarget != null && !target.has_skill(특기_화신) && hasCustomItemSkill(leaderTarget, 특기_화신))
			{
				bSkillTarget = leaderTarget.skill;
				setSkill(leaderTarget, 특기_화신);
			}
			if (bSkillTarget == -2 && leaderTarget != null && !target.has_skill(특기_답파) && hasCustomItemSkill(leaderTarget, 특기_답파))
			{
				bSkillTarget = leaderTarget.skill;
				setSkill(leaderTarget, 특기_답파);
			}
			if (bSkillTarget==-2 && leaderTarget != null && !target.has_skill(특기_등갑) && hasCustomItemSkill(leaderTarget,특기_등갑))
			{
				bSkillTarget = leaderTarget.skill;
				setSkill(leaderTarget, 특기_등갑);
			}



			prev_callback_214(info, attacker, target0, critical);

			if (leader != null && bSkill != -2)
			{
				resetSkill(leader, bSkill);
			}
			if (leaderTarget != null && bSkillTarget != -2)
			{
				resetSkill(leaderTarget, bSkillTarget);
			}
		}

		int callback216(pk::unit@ unit, const pk::point& in pos)
		{
			int n = prev_callback_216(unit, pos);
			if (hasCustomItemSkill(unit, 특기_화신))
				n = 0;
			return n;
		}


		pk::int_bool callback206(pk::unit@ src, const pk::point& in src_pos, const pk::point& in dst_pos, int strategy_id)
		{
			pk::unit@ target_unit = getUnit(dst_pos);
			pk::unit@ attacker = src;


			int bSkill = -2;
			pk::person@ leader = pk::get_person(src.leader);
			if (leader != null)
			{
				int skill = -1;
				array<int> skills = { 특기_신산,특기_허실,특기_경국,특기_기략,특기_언독,특기_궤계,특기_화공,특기_묘계,특기_비책 };

				for (int i = 0; i < skills.length; i++)
				{
					int a = skills[i];
					if (strategy_id != 계략_화계 && a == 특기_화공)
						continue;
					if (strategy_id != 계략_위보 && a == 특기_언독)
						continue;
					if (strategy_id != 계략_동토 && a == 특기_궤계)
						continue;
					if (strategy_id != 계략_교란 && a == 특기_기략)
						continue;
					if (attacker.has_skill(a))
						break;
					if (hasCustomItemSkill(attacker,a))
					{
						skill = a;
						break;
					}
				}

				if (skill >= 0)
				{
					bSkill = leader.skill;
					setSkill(leader, skill);
				}
			}

			int bSkillTarget = -2;
			pk::person@ leaderTarget = target_unit != null ? pk::get_person(target_unit.leader) : null;
			if (leaderTarget != null)
			{
				int skill = -1;
				array<int> skills = { 특기_신산,특기_통찰,특기_화신,특기_반계,특기_간파,특기_명경,특기_침착,특기_규율 };

				for (int i = 0; i < skills.length; i++)
				{
					int a = skills[i];
					if (strategy_id != 계략_화계 && a == 특기_화신)
						continue;
					if (strategy_id != 계략_위보 && a == 특기_규율)
						continue;
					if (strategy_id != 계략_교란 && a == 특기_침착)
						continue;

					if (target_unit.has_skill(a))
						break;
					if (hasCustomItemSkill(target_unit, a))
					{
						skill = a;
						break;
					}
				}

				if (skill >= 0)
				{
					bSkillTarget = leaderTarget.skill;
					setSkill(leaderTarget, skill);
				}
			}

			auto arr = prev_callback_206(src, src_pos, dst_pos, strategy_id);
			if (has보물skill(src, 보물특기_계략성공확률))
			{
				arr.first = pk::min(100, arr.first + 계략성공확률);
			}

			if (bSkill != -2 && leader != null)
			{
				resetSkill(leader, bSkill);
			}
			if (bSkillTarget != -2 && leaderTarget != null)
			{
				resetSkill(leaderTarget, bSkillTarget);
			}


			return arr;
		}


		int callback207(pk::unit@ attacker, const pk::point& in src_pos, const pk::point& in dst_pos, int strategy_id)
		{

			int bSkill = -2;
			pk::person@ leader = pk::get_person(attacker.leader);
			if (leader != null)
			{
				int skill = -1;
				array<int> skills = { 특기_신산,특기_심모,특기_묘계,특기_비책 };

				for (int i = 0; i < skills.length; i++)
				{
					int a = skills[i];
					if (attacker.has_skill(a))
						break;
					if (hasCustomItemSkill(attacker, a))
					{
						skill = a;
						break;
					}
				}

				if (skill >= 0)
				{
					bSkill = leader.skill;
					setSkill(leader, skill);
				}

			}

			int n = prev_callback_207(attacker, src_pos, dst_pos, strategy_id);
			if (leader != null && bSkill != -2)
			{
				resetSkill(leader, bSkill);
			}



			return n;
		}

		void callback209(pk::damage_info& info, pk::unit@ attacker, int tactics_id, const pk::point& in target_pos, int type, int critical, bool ambush)
		{
			//소탕,위풍,강습,급습,등갑,백마,친오,친강,친만,친월
			pk::unit@ target_unit = getUnit(target_pos);
			array<int> skillsTarget = { -2,-2,-2 };
			pk::person@ leaderTarget = target_unit != null ? pk::get_person(target_unit.leader) : null;
			if (target_unit != null && leaderTarget != null)
			{
				array<int> targetSkills00 = { 특기_등갑, 특기_금강, 특기_불굴, 특기_철벽};
				array<int> targetSkills0;
				while (targetSkills00.length > 0)
				{
					int aa = pk::rand(targetSkills00.length);
					targetSkills0.insertLast(targetSkills00[aa]);
					targetSkills00.removeAt(aa);
				}

				array<int> targetSkills;
				for (int i = 0; i < targetSkills0.length; i++)
				{
					int a = targetSkills0[i];
					if (target_unit.has_skill(a))
						continue;
					if (!hasCustomItemSkill(target_unit, a))
					{
						bool bbb = false;
						array<pk::point> pts = pk::range(target_unit.get_pos(), 1, 1);
						for (int j = 0; j < pts.length; j++)
						{
							pk::point pt = pts[j];
							pk::unit@ uu = getUnit(pt);
							if(uu==null || pk::is_enemy(target_unit,uu))
								continue;

							if (has보물skill(uu, 보물특기_방어특기공유)) 
							{
								if (uu.has_skill(a) || hasCustomItemSkill(uu,a))
								{
									bbb = true;
									break;
								}
							}
						}
						if(!bbb)
							continue;
					}
						

					targetSkills.insertLast(a);
				}

				int j = 0;
				for (int i = 0; i < pk::get_member_count(target_unit); i++)
				{
					pk::person@ p = pk::get_person(target_unit.member[i]);
					if (p == null)
						continue;
					if (j == targetSkills.length)
						break;

					//철벽,금강,불굴,
					skillsTarget[i] = p.skill;
					setSkill(p, targetSkills[j]);
					j++;
					continue;
				}
			}

			array<int> skills = { -2,-2,-2 };
			if (target_unit != null)
			{
				array<int> targetSkills0 = { 특기_백마, 특기_급습, 특기_위풍,특기_친강,특기_친오,특기_친만,특기_친월,특기_강습,특기_소탕 };
				array<int> targetSkills;
				for (int i = 0; i < targetSkills0.length; i++)
				{
					int a = targetSkills0[i];
					if (attacker.has_skill(a))
						continue;
					if (!hasCustomItemSkill(attacker, a))
						continue;

					targetSkills.insertLast(a);
				}


				int j = 0;
				for (int i = 0; i < pk::get_member_count(attacker); i++)
				{
					pk::person@ p = pk::get_person(attacker.member[i]);
					if (p == null)
						continue;
					if (j == targetSkills.length)
						break;

					if (pk::get_distance(attacker.pos, target_unit.pos) > 1 && targetSkills[j] == 특기_백마 && attacker.weapon == 병기_군마)
					{
						skills[i] = p.skill;
						setSkill(p, 특기_백마);
						j++;
						continue;
					}
					if (pk::is_in_water(attacker) && targetSkills[j] == 특기_강습)
					{
						skills[i] = p.skill;
						setSkill(p, 특기_강습);
						j++;
						continue;
					}
					if (!pk::is_in_water(attacker) && targetSkills[j] == 특기_급습)
					{
						skills[i] = p.skill;
						setSkill(p, 특기_급습);
						j++;
						continue;
					}
					if (attacker.weapon == 병기_군마 && (targetSkills[j] == 특기_친강 || targetSkills[j] == 특기_친오))
					{
						skills[i] = p.skill;
						setSkill(p, targetSkills[j]);
						j++;
						continue;
					}
					if (attacker.weapon == 병기_극 && (targetSkills[j] == 특기_친만 || targetSkills[j] == 특기_친월))
					{
						skills[i] = p.skill;
						setSkill(p, targetSkills[j]);
						j++;
						continue;
					}

					//위풍,소탕
					skills[i] = p.skill;
					setSkill(p, targetSkills[j]);
					j++;
					continue;
				}
			}



			prev_callback_209(info, attacker, tactics_id, target_pos, type, critical, ambush);
			if (target_unit != null && has보물skill(target_unit, 보물특기_대불굴) && target_unit.troops <= 대불굴_병력기준 && pk::rand_bool(대불굴_확률))
			{
				info.troops_damage = 0;
				info.def_skill = 특기_불굴;
				info.tactics_hit = false;
				info.critical = false;
			}
			if (type == 0 && target_unit!=null && has보물skill(attacker, 보물특기_원킬) && pk::rand_bool(원킬_확률))
			{
				info.troops_damage = target_unit.troops + 1;
				string str = pk::encode(pk::format("신보물, 원킬효과 발생, {}대가 {}대의 병력을 {} 소모!!!!\n",getNameLeader(attacker),getNameLeader(target_unit), info.troops_damage));
				pk::history_log(attacker.get_pos(), pk::get_force(attacker.get_force_id()).color,str);
			}
			if (target_unit != null && has보물skill(attacker, 보물특기_병량탈취))
			{
				info.food_damage = info.food_heal = info.troops_damage * 병량_데미지_비율;
			}
			if (target_unit == null)
			{
				pk::building@ building = pk::hex_object_to_building(pk::get_hex_object(target_pos));
				if (building != null)
				{
					if (has보물skill(attacker, 보물특기_인접부대_건물데미지_추가))
					{
						info.troops_damage *= 건물데미지_비율;
						info.hp_damage *= 건물데미지_비율;
					}
					else
					{
						for (int j = 0; j < 6; j++)
						{
							pk::point pt = pk::get_neighbor_pos(attacker.get_pos(), j, 1);
							pk::unit@ unit2 = getUnit(pt);
							if (unit2 == null || pk::is_enemy(attacker, unit2))
								continue;

							if (has보물skill(unit2, 보물특기_인접부대_건물데미지_추가))
							{
								info.troops_damage *= 건물데미지_비율;
								info.hp_damage *= 건물데미지_비율;
								break;
							}
						}
					}
				}
			}

			if (target_unit != null)
			{
				for (int i = 0; i < pk::get_member_count(target_unit); i++)
				{
					int a = skillsTarget[i];
					if (a != -2)
					{
						resetSkill(pk::get_person(target_unit.member[i]), a);
					}
				}
			}
			if (attacker!=null)
			{
				for (int i = 0; i < pk::get_member_count(attacker); i++)
				{
					int a = skills[i];
					if (a != -2)
					{
						resetSkill(pk::get_person(attacker.member[i]), a);
					}
				}
			}

			pk::hex_object@ obj = pk::get_hex_object(target_pos);
			if (attacker != null && obj != null)
			{
				if (!IsAlready보물(attacker, obj, info.troops_damage))
				{
					_attackers보물.insertLast(attacker);
					_targets보물.insertLast(obj);
					_damages보물.insertLast(info);
					_points보물.insertLast(obj.get_pos());

					pk::list<pk::person@> l;
					pk::list<pk::person@> l2;

					if(pk::is_valid_person_id(attacker.member[0])) 
						l.add(pk::get_person(attacker.member[0]));
					if (pk::is_valid_person_id(attacker.member[1]))
						l.add(pk::get_person(attacker.member[1]));
					if (pk::is_valid_person_id(attacker.member[2]))
						l.add(pk::get_person(attacker.member[2]));

					if (target_unit != null) 
					{
						if (pk::is_valid_person_id(target_unit.member[0]))
							l2.add(pk::get_person(target_unit.member[0]));
						if (pk::is_valid_person_id(target_unit.member[1]))
							l2.add(pk::get_person(target_unit.member[1]));
						if (pk::is_valid_person_id(target_unit.member[2]))
							l2.add(pk::get_person(target_unit.member[2]));
					}

					_attackersPerson보물.insertLast(l);
					_targetrsPerson보물.insertLast(l2);
				}
			}
		}

		int callback164(pk::unit@ unit)
		{
			int n = prev_callback_164(unit);
			if (!has보물skill(unit, 보물특기_대불굴))
				return n;
			return 0;
		}


		bool IsAlready보물(pk::unit@ u, pk::hex_object@ obj, int damage)
		{
			for (int i = 0; i < _attackers보물.length; i++)
			{
				pk::unit@ u0 = _attackers보물[i];
				if (u0.get_id() == u.get_id() && obj.get_id() == _targets보물[i].get_id())
				{
					if (damage > _damages보물[i].troops_damage)
						_damages보물[i].troops_damage = damage;
					return true;
				}
			}
			return false;
		}

		array<pk::list<pk::person@>> _attackersPerson보물;
		array<pk::list<pk::person@>> _targetrsPerson보물;
		array<pk::unit@> _attackers보물;
		array<pk::hex_object@> _targets보물;
		array<pk::damage_info> _damages보물;
		array<pk::point> _points보물;
		bool has보물skill(pk::person@ p, int type)
		{
			if (p == null)
				return false;
			for (int i = 0; i < 커스텀아이템스.length; i++)
			{
				CustomItem@ ci = 커스텀아이템스[i];
				if (ci == null)
					continue;
				if(ci.owner == null)
					continue;
				if(ci.owner.get_id() != p.get_id())
					continue;

				for (int j = 0; j < ci.skills보물.length; j++)
				{
					if (ci.skills보물[j] == type)
						return true;
				}
			}
			return false;
		}
		bool has보물skill(pk::unit@ u, int type)
		{
			return has보물skill(pk::get_person(u.member[0]), type) || has보물skill(pk::get_person(u.member[1]), type) || has보물skill(pk::get_person(u.member[2]), type);
		}

		void clearAttacker보물(pk::unit@ u)
		{
			_attackers보물 = {};
			_targets보물 = {};
			_damages보물 = {};
			_points보물 = {};
			//_attackersPerson보물 = {};
			//_targetrsPerson보물 = {};
			return;
			while (true)
			{
				int a = _attackers보물.findByRef(u);
				if (a < 0)
					break;
				_attackers보물.removeAt(a);
				_targets보물.removeAt(a);
				_damages보물.removeAt(a);
				_points보물.removeAt(a);
			}
		}

		array<pk::hex_object@> getAttacker보물(pk::unit@ u)
		{
			array<pk::hex_object@> arr;
			for (int i = 0; i < _attackers보물.length; i++)
			{
				pk::unit@ u0 = _attackers보물[i];
				if (u0.get_id() == u.get_id())
				{
					arr.insertLast(_targets보물[i]);
				}
			}
			return arr;
		}
		array<pk::damage_info> getAttackerDamages보물(pk::unit@ u)
		{
			array<pk::damage_info> arr;
			for (int i = 0; i < _attackers보물.length; i++)
			{
				pk::unit@ u0 = _attackers보물[i];
				if (u0.get_id() == u.get_id())
				{
					arr.insertLast(_damages보물[i]);
				}
			}
			return arr;
		}
		array<pk::point> getAttackerPoints보물(pk::unit@ u)
		{
			array<pk::point> arr;
			for (int i = 0; i < _attackers보물.length; i++)
			{
				pk::unit@ u0 = _attackers보물[i];
				if (u0.get_id() == u.get_id())
				{
					arr.insertLast(_points보물[i]);
				}
			}
			return arr;
		}


		bool callback201(pk::unit@ attacker, pk::hex_object@ target, int tactics_id, bool ranged)
		{
			int bSkill = -2;
			pk::person@ leader = pk::get_person(attacker.leader);
			if (leader != null)
			{
				int skill = -1;
				pk::unit@ target_unit = pk::hex_object_to_unit(target);
				if ((target_unit !is null and (pk::get_hex(attacker.get_pos()).terrain != 지형_숲 or (pk::get_hex(attacker.get_pos()).terrain == 지형_숲 and !attacker.has_skill(특기_난전)))))
				{
					if (pk::get_hex(attacker.get_pos()).terrain == 지형_숲 && hasCustomItemSkill(attacker, 특기_난전))
						skill = 특기_난전;

					if (skill == -1 && !(pk::is_valid_tactics_id(tactics_id)))
					{
						if (!attacker.has_skill(특기_신장) && hasCustomItemSkill(attacker, 특기_신장))
							skill = 특기_신장;
						if (skill == -1 && !attacker.has_skill(특기_신장) && !attacker.has_skill(특기_구축) && hasCustomItemSkill(attacker, 특기_구축))
							skill = 특기_구축;
						if (skill == -1 && ranged && !attacker.has_skill(특기_신장) && !attacker.has_skill(특기_백마) && hasCustomItemSkill(attacker, 특기_백마) && attacker.weapon == 병기_군마)
							skill = 특기_백마;
					}
					else if (skill == -1)
					{
						switch (attacker.weapon)
						{
						case 병기_군마:
							if (!attacker.has_skill(특기_패왕) && !attacker.has_skill(특기_기신))
							{
								if (hasCustomItemSkill(attacker, 특기_패왕))
									skill = 특기_패왕;
								if (skill == -1 && hasCustomItemSkill(attacker, 특기_기신))
									skill = 특기_기신;

								if (skill == -1 && !attacker.has_skill(특기_용장) && !attacker.has_skill(특기_비장) && !attacker.has_skill(특기_기장))
								{
									if (skill == -1 && hasCustomItemSkill(attacker, 특기_용장))
										skill = 특기_용장;
									if (skill == -1 && hasCustomItemSkill(attacker, 특기_비장))
										skill = 특기_비장;
									if (skill == -1 && hasCustomItemSkill(attacker, 특기_기장))
										skill = 특기_기장;
								}
							}
							break;
						case 병기_창:
							if (!attacker.has_skill(특기_패왕) && !attacker.has_skill(특기_창신) && !attacker.has_skill(특기_투신))
							{
								if (hasCustomItemSkill(attacker, 특기_패왕))
									skill = 특기_패왕;
								if (skill == -1 && hasCustomItemSkill(attacker, 특기_창신))
									skill = 특기_창신;
								if (skill == -1 && hasCustomItemSkill(attacker, 특기_투신))
									skill = 특기_투신;

								if (skill == -1 && !attacker.has_skill(특기_용장) && !attacker.has_skill(특기_비장) && !attacker.has_skill(특기_창장))
								{
									if (skill == -1 && hasCustomItemSkill(attacker, 특기_용장))
										skill = 특기_용장;
									if (skill == -1 && hasCustomItemSkill(attacker, 특기_비장))
										skill = 특기_비장;
									if (skill == -1 && hasCustomItemSkill(attacker, 특기_창장))
										skill = 특기_창장;
								}
							}
							break;
						case 병기_극:
							if (!attacker.has_skill(특기_패왕) && !attacker.has_skill(특기_극신) && !attacker.has_skill(특기_투신))
							{
								if (hasCustomItemSkill(attacker, 특기_패왕))
									skill = 특기_패왕;
								if (skill == -1 && hasCustomItemSkill(attacker, 특기_극신))
									skill = 특기_극신;
								if (skill == -1 && hasCustomItemSkill(attacker, 특기_투신))
									skill = 특기_투신;

								if (skill == -1 && !attacker.has_skill(특기_용장) && !attacker.has_skill(특기_비장) && !attacker.has_skill(특기_극장))
								{
									if (skill == -1 && hasCustomItemSkill(attacker, 특기_용장))
										skill = 특기_용장;
									if (skill == -1 && hasCustomItemSkill(attacker, 특기_비장))
										skill = 특기_비장;
									if (skill == -1 && hasCustomItemSkill(attacker, 특기_극장))
										skill = 특기_극장;
								}
							}
							break;
						case 병기_노:
							if (!attacker.has_skill(특기_패왕) && !attacker.has_skill(특기_궁신))
							{
								if (hasCustomItemSkill(attacker, 특기_패왕))
									skill = 특기_패왕;
								if (skill == -1 && hasCustomItemSkill(attacker, 특기_궁신))
									skill = 특기_궁신;

								if (skill == -1 && !attacker.has_skill(특기_용장) && !attacker.has_skill(특기_비장) && !attacker.has_skill(특기_궁장))
								{
									if (skill == -1 && hasCustomItemSkill(attacker, 특기_용장))
										skill = 특기_용장;
									if (skill == -1 && hasCustomItemSkill(attacker, 특기_비장))
										skill = 특기_비장;
									if (skill == -1 && hasCustomItemSkill(attacker, 특기_궁장))
										skill = 특기_궁장;
								}
							}
							break;
						case 병기_정란:
						case 병기_투석:
						case 병기_목수:
							if (!attacker.has_skill(특기_패왕) && !attacker.has_skill(특기_공신))
							{
								if (hasCustomItemSkill(attacker, 특기_패왕))
									skill = 특기_패왕;
								if (skill == -1 && hasCustomItemSkill(attacker, 특기_공신))
									skill = 특기_공신;

								if (skill == -1 && !attacker.has_skill(특기_용장) && !attacker.has_skill(특기_비장) && !attacker.has_skill(특기_공성))
								{
									if (skill == -1 && hasCustomItemSkill(attacker, 특기_용장))
										skill = 특기_용장;
									if (skill == -1 && hasCustomItemSkill(attacker, 특기_비장))
										skill = 특기_비장;
									if (skill == -1 && hasCustomItemSkill(attacker, 특기_공성))
										skill = 특기_공성;
								}
							}
							break;
						case 병기_주가:
						case 병기_누선:
						case 병기_투함:
							if (!attacker.has_skill(특기_패왕) && !attacker.has_skill(특기_수신))
							{
								if (hasCustomItemSkill(attacker, 특기_패왕))
									skill = 특기_패왕;
								if (skill == -1 && hasCustomItemSkill(attacker, 특기_수신))
									skill = 특기_수신;

								if (skill == -1 && !attacker.has_skill(특기_용장) && !attacker.has_skill(특기_비장) && !attacker.has_skill(특기_수장))
								{
									if (skill == -1 && hasCustomItemSkill(attacker, 특기_용장))
										skill = 특기_용장;
									if (skill == -1 && hasCustomItemSkill(attacker, 특기_비장))
										skill = 특기_비장;
									if (skill == -1 && hasCustomItemSkill(attacker, 특기_수장))
										skill = 특기_수장;
								}
							}
							break;

						}//end of switch
					}//end of skill
				}



				if (skill >= 0)
				{
					bSkill = leader.skill;
					setSkill(leader, skill);
				}
			}


			bool bCri = prev_callback_201(attacker, target, tactics_id, ranged);
			if (leader != null)
			{
				if (bSkill != -2)
				{
					resetSkill(leader, bSkill);
				}
			}

			return bCri;
		}
		int callback258(pk::person@ prisoner, const pk::prisoner_info& in info)
		{
			pk::person@ p = prisoner;
			pk::person@ judge = pk::get_person(pk::get_kunshu_id(info.attacker));

			array<CustomItem@> arr = getCustomItem(p);
			if (arr.length > 0)
			{
				for (int i = 0; i < arr.length; i++)
				{
					CustomItem@ ci = arr[i];
					ItemRent@ ir = getRent(ci);
					if (ir != null)
						removeRent(ir);


					@_scene_citem_강탈 = ci;
					@_scene_kunshu_강탈 = judge;
					@_scene_item_강탈 = null;
					try
					{
						if (judge.is_player())
							pk::scene(pk::scene_t(scene_보물_강탈));
						else
							scene_보물_강탈();
					}
					catch
					{
					}

					ci.updateOwner(judge);
				}
			}
			array<pk::item@> arr2 = getItem(p);
			if (arr2.length > 0)
			{
				for (int i = 0; i < arr2.length; i++)
				{
					pk::item@ ci = arr2[i];

					@_scene_citem_강탈 = null;
					@_scene_kunshu_강탈 = judge;
					@_scene_item_강탈 = ci;

					try
					{
						if (judge.is_player())
							pk::scene(pk::scene_t(scene_보물_강탈));
						else
							scene_보물_강탈();
					}
					catch
					{
					}

				}
			}
			
			
			return prev_callback_258(prisoner, info);
		}

		void callback220(const pk::destroy_info& in info, pk::list<pk::person@>& captured, pk::list<pk::person@>& escaped, bool tactics_bonus)
		{
			pk::hex_object@ attacker0 = info.attacker;
			pk::hex_object@ target0 = info.target;

			pk::unit@ attacker = pk::hex_object_to_unit(attacker0);
			pk::unit@ target = getUnit(target0.get_pos());

			int bSkill = -2;
			pk::person@ leader = attacker != null ? pk::get_person(attacker.leader) : null;
			if (leader != null)
			{
				if (hasCustomItemSkill(attacker, 특기_포박))
				{
					bSkill = leader.skill;
					setSkill(leader, 특기_포박);
				}
			}

			int bSkillTarget = -2;
			pk::person@ leaderTarget = target != null ? pk::get_person(target.leader) : null;
			if (leaderTarget != null)
			{
				if (hasCustomItemSkill(leaderTarget, 특기_혈로))
				{
					bSkillTarget = leaderTarget.skill;
					setSkill(leaderTarget, 특기_혈로);
				}
				else if (hasCustomItemSkill(leaderTarget, 특기_강운))
				{
					bSkillTarget = leaderTarget.skill;
					setSkill(leaderTarget, 특기_강운);
				}
			}

			//pk::hex_object@ targetDebug = info.target;
			//if (targetDebug != null)
			//{
			//	pk::unit@ u = pk::hex_object_to_unit(targetDebug);
			//	if (u != null && pk::get_person(u.leader).mibun != 신분_군주)
			//	{
			//		pk::person@ p0 = pk::get_person(u.member[0]);
			//		pk::person@ p1 = pk::get_person(u.member[1]);
			//		pk::person@ p2 = pk::get_person(u.member[2]);
			//		if (p0 != null) captured.add(p0);
			//		if (p1 != null) captured.add(p1);
			//		if (p2 != null) captured.add(p2);
			//	}
			//}
			prev_callback_220(info, captured, escaped, tactics_bonus);

			if (leader != null && bSkill != -2)
			{
				resetSkill(leader, bSkill);
			}
			if (leaderTarget != null && bSkillTarget != -2)
			{
				resetSkill(leaderTarget, bSkillTarget);
			}

			callback220포로(info, captured, escaped, tactics_bonus);
		}
		
		int callback202(pk::unit@ attacker, const pk::point& in pos, pk::hex_object@ target, int tactics_id)
		{
			int n = prev_callback_202(attacker, pos, target, tactics_id);
			if (has보물skill(attacker, 보물특기_전법성공확률))
			{
				n = pk::min(100, n + 전법성공확률);
			}
			return n;
		}



		int callback167(pk::building@ building)
		{
			pk::list<pk::person@> persons = pk::get_person_list(building, pk::mibun_flags(신분_군주,신분_도독,신분_태수,신분_일반));
			pk::person@ tp = null;
			for (int i = 0; i < persons.count; i++)
			{
				pk::person@ p = persons[i];
				if (hasCustomItemSkill(p, 특기_둔전))
				{
					@tp = p;
					break;
				}
			}

			int bskill = -2;
			if (tp != null)
			{
				bskill = tp.skill;
				setSkill(tp, 특기_둔전);
			}

			int n = prev_callback_167(building);

			if (bskill != -2)
			{
				resetSkill(tp, bskill);
			}
			return n;
		}
		
		int callback100(pk::building@ building, const pk::detail::arrayptr<pk::person@>& in actors)
		{
			pk::person@ tp = null;
			for (int i = 0; i < actors.length; i++)
			{
				pk::person@ p = actors[i];
				if (hasCustomItemSkill(p, 특기_명성))
				{
					@tp = p;
					break;
				}
			}

			int bskill = -2;
			if (tp != null)
			{
				bskill = tp.skill;
				setSkill(tp, 특기_명성);
			}

			int n = prev_callback_100(building,actors);

			if (bskill != -2)
			{
				resetSkill(tp, bskill);
			}
			return n;
		}

		int callback102(pk::city@ city, const pk::detail::arrayptr<pk::person@>& in actors, int weapon_id)
		{
			int skill = -1;
			if (weapon_id == 병기_군마)
				skill = 특기_번식;
			if (weapon_id == 병기_노 || weapon_id == 병기_창 || weapon_id == 병기_극)
				skill = 특기_능리;
			if(skill == -1)
				return prev_callback_102(city, actors, weapon_id);


			pk::person@ tp = null;
			for (int i = 0; i < actors.length; i++)
			{
				pk::person@ p = actors[i];
				if (hasCustomItemSkill(p, skill))
				{
					@tp = p;
					break;
				}
			}

			int bskill = -2;
			if (tp != null)
			{
				bskill = tp.skill;
				setSkill(tp, skill);
			}

			int n = prev_callback_102(city, actors, weapon_id);

			if (bskill != -2)
			{
				resetSkill(tp, bskill);
			}
			return n;

		}

		int callback103(const pk::detail::arrayptr<pk::person@>& in actors, int weapon_id)
		{
			int skill = -1;
			if (weapon_id == 병기_충차 || weapon_id == 병기_정란 || weapon_id == 병기_투석 || weapon_id == 병기_목수)
				skill = 특기_발명;
			if (weapon_id == 병기_누선 || weapon_id == 병기_투함)
				skill = 특기_조선;
			if (skill == -1)
				return prev_callback_103(actors, weapon_id);


			pk::person@ tp = null;
			for (int i = 0; i < actors.length; i++)
			{
				pk::person@ p = actors[i];
				if (hasCustomItemSkill(p, skill))
				{
					@tp = p;
					break;
				}
			}

			int bskill = -2;
			if (tp != null)
			{
				bskill = tp.skill;
				setSkill(tp, skill);
			}

			int n = prev_callback_103(actors, weapon_id);

			if (bskill != -2)
			{
				resetSkill(tp, bskill);
			}
			return n;

		}

		int callback150(pk::city@ city)
		{
			pk::list<pk::person@> persons = pk::get_person_list(pk::city_to_building(city), pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반));
			pk::person@ tp = null;
			for (int i = 0; i < persons.count; i++)
			{
				pk::person@ p = persons[i];
				if (hasCustomItemSkill(p, 특기_부호))
				{
					@tp = p;
					break;
				}
			}

			int bskill = -2;
			if (tp != null)
			{
				bskill = tp.skill;
				setSkill(tp, 특기_부호);
			}

			int n = prev_callback_150(city);

			if (bskill != -2)
			{
				resetSkill(tp, bskill);
			}
			return n;

		}

		int callback152(pk::building@ building, int city_revenue)
		{
			pk::list<pk::person@> persons = pk::get_person_list(building, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반));
			pk::person@ tp = null;
			for (int i = 0; i < persons.count; i++)
			{
				pk::person@ p = persons[i];
				if (hasCustomItemSkill(p, 특기_부호))
				{
					@tp = p;
					break;
				}
			}

			int bskill = -2;
			if (tp != null)
			{
				bskill = tp.skill;
				setSkill(tp, 특기_부호);
			}

			int n = prev_callback_152(building,city_revenue);

			if (bskill != -2)
			{
				resetSkill(tp, bskill);
			}
			return n;
		}

		int callback151(pk::city@ city)
		{
			pk::list<pk::person@> persons = pk::get_person_list(pk::city_to_building(city), pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반));
			pk::person@ tp = null;
			for (int i = 0; i < persons.count; i++)
			{
				pk::person@ p = persons[i];
				if (hasCustomItemSkill(p, 특기_미도))
				{
					@tp = p;
					break;
				}
			}

			int bskill = -2;
			if (tp != null)
			{
				bskill = tp.skill;
				setSkill(tp, 특기_미도);
			}

			int n = prev_callback_151(city);

			if (bskill != -2)
			{
				resetSkill(tp, bskill);
			}
			return n;

		}

		int callback153(pk::building@ building, int city_harvest)
		{
			pk::list<pk::person@> persons = pk::get_person_list(building, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반));
			pk::person@ tp = null;
			for (int i = 0; i < persons.count; i++)
			{
				pk::person@ p = persons[i];
				if (hasCustomItemSkill(p, 특기_미도))
				{
					@tp = p;
					break;
				}
			}

			int bskill = -2;
			if (tp != null)
			{
				bskill = tp.skill;
				setSkill(tp, 특기_미도);
			}

			int n = prev_callback_153(building, city_harvest);

			if (bskill != -2)
			{
				resetSkill(tp, bskill);
			}
			return n;

		}

		int callback155(pk::building@ building, pk::person@ person)
		{
			pk::list<pk::person@> persons = pk::get_person_list(building, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반));
			pk::person@ tp = null;
			for (int i = 0; i < persons.count; i++)
			{
				pk::person@ p = persons[i];
				if (hasCustomItemSkill(p, 특기_인정))
				{
					@tp = p;
					break;
				}
			}

			int bskill = -2;
			if (tp != null)
			{
				bskill = tp.skill;
				setSkill(tp, 특기_인정);
			}

			int n = prev_callback_155(building, person);

			if (bskill != -2)
			{
				resetSkill(tp, bskill);
			}
			return n;
		}



		
		
		pk::person@ _scene_actor;
		CustomItem@ _scene_item;

		void scene_보물발견()
		{
			if (_scene_actor == null)
				return;
			CustomItem@ ci = _scene_item;
			pk::force@ force = pk::get_force(_scene_actor.get_force_id());
			pk::person@ kunshu = pk::get_person(force.kunshu);
			if (_scene_actor.is_player())
			{
				pk::background(pk::format("{}", ci.path));
				pk::message_box(pk::encode(pk::format("신보물 {} 발견했습니다.", ci.name)));
			}

			string str = pk::format("\x1b[2x{}군\x1b[0x,신보물 \x1b[29x{}\x1b[0x 발견", getName(kunshu), ci.name);
			pk::history_log(kunshu != null ? kunshu.get_pos() : pk::point(0, 0), force.color, pk::encode(str));

			ci.updateOwner(kunshu);
			//보물발견;

			if (_scene_actor.is_player())
				pk::background(-1);
		}

		void 보물발견(pk::unit@ unit)
		{
			if (pk::rand(보물확률_역수) == 0/* || unit.is_player()*/)
			{
				array<CustomItem@> arr;
				for (int i = 0; i < 커스텀아이템스.length; i++)
				{
					CustomItem@ ci = 커스텀아이템스[i];
					if (ci == null)
						continue;
					if (ci.owner == null)
						arr.insertLast(ci);
				}

				if (arr.length > 0)
				{
					int a = pk::rand(arr.length);

					@_scene_actor = pk::get_person(unit.leader);
					@_scene_item = arr[a];
					pk::scene(pk::scene_t(scene_보물발견));
				}
			}
		}

		void onUnitEnd연전(pk::unit@ unit)
		{
			array<pk::hex_object@> arr = getAttacker보물(unit);
			array<pk::damage_info> arrDemage = getAttackerDamages보물(unit);
			for (int i = 0; i < arr.length; i++)
			{
				pk::damage_info dem = arrDemage[i];
				pk::printf("연전:{},{}\n", getNameLeader(pk::hex_object_to_unit(arr[i])), dem.tactics);
			}

		}
		void onUnitCreate(pk::unit@ unit, int type)
		{
			array<ItemRent@> removes;
			for (int i = 0; i < _rent.length; i++)
			{
				ItemRent@ ir = _rent[i];
				if(ir.owner0 == null)
					continue;

				if (ir.owner0.get_id() == unit.member[0])
				{
					removes.insertLast(ir);
				}
				if (ir.owner0.get_id() == unit.member[1])
				{
					removes.insertLast(ir);
				}
				if (ir.owner0.get_id() == unit.member[2])
				{
					removes.insertLast(ir);
				}
			}

			while (removes.length>0)
			{
				removes[0].rentBack();
				removes.removeAt(0);
			}
		}
		void onUnitEnd(pk::unit@ unit)
		{
			보물발견(unit);

			int chaos = -1;
			if (has보물skill(unit, 보물특기_혼돈))
			{
				array<CustomItem@> items=getCustomItem(unit);
				for (int i = 0; i < items.length; i++)
				{
					CustomItem@ it = items[i];
					if (it.skills보물.length > 0 && it.skills보물[0] == 보물특기_혼돈)
					{
						chaos = it.skills혼돈[pk::rand(it.skills혼돈.length)];
						string strChaos = "";
						switch (chaos)
						{
						case 보물특기_모든공격_화계발생:strChaos = "모든공격화계"; break;
						case 보물특기_인접_낙뢰:strChaos = "인접낙뢰"; break;
						case 보물특기_인접_스플래쉬_데미지:strChaos = "인접스플래쉬"; break;
						case 보물특기_모든공격_추가데미지:strChaos = "추가데미지"; break;
						case 보물특기_모든공격_충성도_저하:strChaos = "충성도저하"; break;
						case 보물특기_위풍:strChaos = "위풍"; break;
						case 보물특기_심공:strChaos = "심공"; break;
						case 보물특기_원킬:strChaos = "원킬"; break;
						case 보물특기_병량탈취:strChaos = "병량탈취"; break;
						case 보물특기_혼란_유발:strChaos = "혼란_유발"; break;
						case 보물특기_위보_유발:strChaos = "위보_유발"; break;
						case 보물특기_동토_유발:strChaos = "동토_유발"; break;
						case 보물특기_일기토_유발:strChaos = "일기토_유발"; break;
						case 보물특기_메테오:strChaos = "메테오"; break;
						case 보물특기_부상유발:strChaos = "부상유발"; break;
						case 보물특기_수계:strChaos = "수계"; break;
						default:
							break;
						}
						string str = pk::encode(pk::format("신보물 혼돈효과 \x1b[29x{}\x1b[0x 발생 !!!!,",strChaos));
						pk::history_log(unit.get_pos(), pk::get_force(unit.get_force_id()).color, str);
						break;
					}
				}
			}

			//if (hasCustomItemSkill(unit, 특기_연전) && !unit.has_skill(특기_연전))
			//{
			//	onUnitEnd연전(unit);
			//}
			
			if (hasCustomItemSkill(unit, 특기_질주) && unit.weapon == 병기_군마)
			{
				pk::func222_t@ func = cast<pk::func222_t@>(pk::get_func(222));
				array<pk::hex_object@> arr = getAttacker보물(unit);
				for (int i = 0; i < arr.length; i++)
				{
					pk::hex_object@ obj = arr[i];
					if (obj == null || !obj.is_alive())
						continue;
					if (!pk::is_valid_pos(obj.get_pos()))
						continue;

					pk::unit@ unit2 = getUnit(obj.get_pos());
					if (unit2 == null || !pk::is_enemy(unit, unit2))
						continue;
					
					if (unit.attr.stat[부대능력_공격] > unit2.attr.stat[부대능력_공격])
					{
						pk::set_status(unit2, unit, 부대상태_혼란, pk::rand(2) + 1, true);
					}
				}
			}
			if (has보물skill(unit, 보물특기_부상유발) || chaos == 보물특기_부상유발)
			{
				array<pk::hex_object@> arr = getAttacker보물(unit);
				for (int i = 0; i < arr.length; i++)
				{
					pk::hex_object@ obj = arr[i];
					if (obj == null || !obj.is_alive())
						continue;
					if (!pk::is_valid_pos(obj.get_pos()))
						continue;

					pk::unit@ unit2 = pk::hex_object_to_unit(obj);
					if(unit2==null || !pk::is_enemy(unit,unit2))
						continue;

					if(pk::rand_bool(부상유발_확률)) injury(pk::get_person(unit2.member[0]));
					if(pk::rand_bool(부상유발_확률)) injury(pk::get_person(unit2.member[1]));
					if(pk::rand_bool(부상유발_확률)) injury(pk::get_person(unit2.member[2]));
				}
			}
			if (has보물skill(unit, 보물특기_모든공격_화계발생) || chaos == 보물특기_모든공격_화계발생)
			{
				array<pk::hex_object@> arr = getAttacker보물(unit);
				for (int i = 0; i < arr.length; i++)
				{
					pk::hex_object@ obj = arr[i];
					if(obj == null || !obj.is_alive())
						continue;
					if(!pk::rand_bool(화계_확률))
						continue;
					if(!pk::is_valid_pos(obj.get_pos()))
						continue;
					if(!pk::is_enemy(unit,obj))
						continue;

					pk::create_fire(obj.get_pos(), pk::rand(2) + 1, unit);
					pk::unit@ u = getUnit(obj.get_pos());
					if (u != null && pk::rand(세이_RAND) == 0)
					{
						pk::say(pk::encode("갑자기 불이 어디서..."), pk::get_person(u.leader), u);
					}
				}
			}
			if (has보물skill(unit, 보물특기_모든공격_충성도_저하) || chaos == 보물특기_모든공격_충성도_저하)
			{
				array<pk::hex_object@> arr = getAttacker보물(unit);
				for (int i = 0; i < arr.length; i++)
				{
					pk::hex_object@ obj = arr[i];
					if (obj == null || !obj.is_alive())
						continue;
					if (!pk::is_valid_pos(obj.get_pos()))
						continue;

					pk::unit@ unit2 = getUnit(obj.get_pos());
					if (unit2 == null || !pk::is_enemy(unit, unit2))
						continue;

					pk::person@ p0 = pk::get_person(unit2.member[0]);
					if (p0!=null) pk::add_loyalty(p0, -충성도_저하량);
					pk::person@ p1 = pk::get_person(unit2.member[1]);
					if (p1 != null) pk::add_loyalty(p1, -충성도_저하량);
					pk::person@ p2 = pk::get_person(unit2.member[2]);
					if (p2 != null) pk::add_loyalty(p2, -충성도_저하량);

					if (p0 != null && pk::rand(세이_RAND) == 0)
					{
						pk::say(pk::encode("주군은 나를 싫어하는것 같다."), p0, unit2);
					}
				}
			}
			if (has보물skill(unit, 보물특기_혼란_유발) || chaos == 보물특기_혼란_유발)
			{
				array<pk::hex_object@> arr = getAttacker보물(unit);
				for (int i = 0; i < arr.length; i++)
				{
					pk::hex_object@ obj = arr[i];
					if (obj == null || !obj.is_alive())
						continue;
					if (!pk::is_valid_pos(obj.get_pos()))
						continue;

					pk::unit@ unit2 = getUnit(obj.get_pos());
					if (unit2 == null || !pk::is_enemy(unit, unit2))
						continue;
					if(!pk::rand_bool(혼란_확률))
						continue;

					pk::set_status(unit2, unit, 부대상태_혼란, pk::rand(2) + 1, true);
					if (pk::rand(세이_RAND) == 0)
					{
						pk::say(pk::encode("이게 무슨일이냐???"), pk::get_person(unit2.leader), unit2);
					}

				}
			}
			if (has보물skill(unit, 보물특기_위보_유발) || chaos == 보물특기_위보_유발)
			{
				array<pk::hex_object@> arr = getAttacker보물(unit);
				for (int i = 0; i < arr.length; i++)
				{
					pk::hex_object@ obj = arr[i];
					if (obj == null || !obj.is_alive())
						continue;
					if (!pk::is_valid_pos(obj.get_pos()))
						continue;

					pk::unit@ unit2 = getUnit(obj.get_pos());
					if (unit2 == null || !pk::is_enemy(unit, unit2))
						continue;
					if (!pk::rand_bool(위보_확률))
						continue;

					pk::set_status(unit2, unit, 부대상태_위보, pk::rand(2) + 1, true);
					if (pk::rand(세이_RAND) == 0)
					{
						pk::say(pk::encode("퇴각이 맞나???"), pk::get_person(unit2.leader), unit2);
					}

				}
			}
			if (has보물skill(unit, 보물특기_동토_유발) || chaos == 보물특기_동토_유발)
			{
				array<pk::hex_object@> arr = getAttacker보물(unit);
				for (int i = 0; i < arr.length; i++)
				{
					pk::hex_object@ obj = arr[i];
					if (obj == null || !obj.is_alive())
						continue;
					if (!pk::is_valid_pos(obj.get_pos()))
						continue;

					pk::unit@ unit2 = getUnit(obj.get_pos());
					if (unit2 == null || !pk::is_enemy(unit, unit2))
						continue;
					if (!pk::rand_bool(동토_확률))
						continue;

					array<pk::unit@> units;
					for (int j = 0; j < 6; j++)
					{
						pk::point pt = pk::get_neighbor_pos(unit2.get_pos(), j, 1);
						pk::unit@ unit3 = getUnit(pt);
						if (unit3 == null || pk::is_enemy(unit3, unit2))
							continue;

						units.insertLast(unit3);
					}
					if(units.length == 0)
						continue;
					pk::unit@ target = units[pk::rand(units.length)];
					pk::attack(unit2, target);
					pk::say(pk::encode("미쳤소? 같은편이요"), pk::get_person(target.leader) ,target);
				}
			}
			if (has보물skill(unit, 보물특기_위풍) || chaos == 보물특기_위풍)
			{
				array<pk::hex_object@> arr = getAttacker보물(unit);
				for (int i = 0; i < arr.length; i++)
				{
					pk::hex_object@ obj = arr[i];
					if (obj == null || !obj.is_alive())
						continue;
					if (!pk::is_valid_pos(obj.get_pos()))
						continue;

					pk::unit@ unit2 = getUnit(obj.get_pos());
					if (unit2 == null || !pk::is_enemy(unit, unit2))
						continue;

					pk::add_energy(unit2, -위풍_기력, true);
				}
			}
			if (has보물skill(unit, 보물특기_모든공격_추가데미지) || chaos == 보물특기_모든공격_추가데미지)
			{
				array<pk::point> arr = getAttackerPoints보물(unit);
				array<pk::damage_info> arrDemage = getAttackerDamages보물(unit);
				for (int i = 0; i < arr.length; i++)
				{
					pk::hex_object@ obj = pk::get_hex_object(arr[i]);
					if(obj == null || !pk::is_enemy(unit,obj))
						continue;
					if (!pk::is_valid_pos(obj.get_pos()))
						continue;

					pk::damage_info di = arrDemage[i];
					if(di.troops_damage==0)
						continue;

					
					create_effect(0x4c, obj.get_pos());
					pk::unit@ u = pk::hex_object_to_unit(obj);
					if (u != null)
					{
						pk::add_troops(u, -(di.troops_damage * 추가_데미지_비율), true);
					}
					else 
					{
						pk::building@ b = pk::hex_object_to_building(obj);
						pk::add_troops(b, -(di.troops_damage * 추가_데미지_비율), true);
						pk::add_hp(b, -(di.hp_damage * 추가_데미지_비율), true);
					}
					updateAfter(unit, obj);
				}
			}
			if (has보물skill(unit, 보물특기_심공) || chaos == 보물특기_심공)
			{
				array<pk::point> arr = getAttackerPoints보물(unit);
				array<pk::damage_info> arrDemage = getAttackerDamages보물(unit);
				int sum = 0;
				for (int i = 0; i < arr.length; i++)
				{
					pk::hex_object@ obj = pk::get_hex_object(arr[i]);
					if (obj == null || !pk::is_enemy(unit, obj))
						continue;
					if (!pk::is_valid_pos(obj.get_pos()))
						continue;

					pk::damage_info di = arrDemage[i];
					if (di.troops_damage == 0)
						continue;

					pk::unit@ u = pk::hex_object_to_unit(obj);
					if (u == null)
						continue;

					sum += (di.troops_damage * 심공_비율);
				}
				if (sum > 0)
					pk::add_troops(unit, sum, true);
			}
			if (has보물skill(unit, 보물특기_인접_낙뢰) || chaos == 보물특기_인접_낙뢰)
			{
				array<pk::point> pts = pk::range(unit.get_pos(), 0, 1);
				for (int i = 0; i < pts.length; i++)
				{
					pk::point pt = pts[i];
					pk::unit@ unit2 = getUnit(pt);
					if (unit2 == null || !pk::is_enemy(unit, unit2))
						continue;
					if (!pk::rand_bool(낙뢰_확률))
						continue;

					play_se(121, unit2.get_pos());
					create_effect(0x40, unit2.get_pos());
					//create_effect(0x89, unit2.get_pos());
					pk::add_troops(unit2, -(낙뢰_기본_데미지+pk::rand(낙뢰_랜덤_데미지)), true);
					if (updateAfter(unit, unit2))
					{
						if (pk::rand_bool(낙뢰_부상_확률)) injury(pk::get_person(unit2.member[0]));
						if (pk::rand_bool(낙뢰_부상_확률)) injury(pk::get_person(unit2.member[1]));
						if (pk::rand_bool(낙뢰_부상_확률)) injury(pk::get_person(unit2.member[2]));

						if (pk::rand(세이_RAND) == 0)
						{
							pk::say(pk::encode("마른 하늘에 날벼락?"), pk::get_person(unit2.leader), unit2);
						}
					}
				}
			}
			if (has보물skill(unit, 보물특기_메테오) || chaos == 보물특기_메테오)
			{
				array<pk::point> pts = pk::range(unit.get_pos(), 0, 1);
				for (int i = 0; i < pts.length; i++)
				{
					pk::point pt = pts[i];
					pk::unit@ unit2 = getUnit(pt);
					if (unit2 == null || !pk::is_enemy(unit, unit2))
						continue;
					if (!pk::rand_bool(메테오_확률))
						continue;

					doMeteo(unit,unit2);
					updateAfter(unit, unit2);
					if (pk::rand(세이_RAND) == 0)
					{
						pk::say(pk::encode("삼국시대에 운석이??"), pk::get_person(unit2.leader), unit2);
					}
				}
			}
			if (has보물skill(unit, 보물특기_수계) || chaos == 보물특기_수계)
			{
				array<pk::point> pts = pk::range(unit.get_pos(), 0, 1);
				for (int i = 0; i < pts.length; i++)
				{
					pk::point pt = pts[i];
					pk::unit@ unit2 = getUnit(pt);
					if (unit2 == null || !pk::is_enemy(unit, unit2))
						continue;
					if (!pk::rand_bool(수계_확률))
						continue;

					float aa = pk::rand(100) / 99.0;
					int dem = aa * aa * 수계_데미지;

					play_se(119, unit2.get_pos());
					create_effect(0xb, unit2.get_pos());
					pk::add_troops(unit2, -dem, true);
					updateAfter(unit, unit2);
					if (pk::rand(세이_RAND) == 0)
					{
						pk::say(pk::encode("급류가??"), pk::get_person(unit2.leader), unit2);
					}
				}
			}

			if (has보물skill(unit, 보물특기_인접_스플래쉬_데미지) || chaos == 보물특기_인접_스플래쉬_데미지)
			{
				dictionary dict;
				array<pk::point> arr = getAttackerPoints보물(unit);
				array<pk::damage_info> arrDemage = getAttackerDamages보물(unit);

				for (int i = 0; i < arr.length; i++)
				{
					pk::unit@ u = getUnit(arr[i]);
					if (u == null)
						continue;

					if (dict.exists(pk::format("{}", u.get_id())))
						continue;
					dict[pk::format("{}", u.get_id())] = 3;
				}

				array<pk::unit@> arr2;
				array<pk::damage_info> arr2Demage;

				for (int i = 0; i < arr.length; i++)
				{
					pk::damage_info objDem = arrDemage[i];
					if(objDem.troops_damage == 0)
						continue;

					array<pk::point> pts = pk::range(arr[i], 0, 1);
					for (int j = 0; j < pts.length; j++)
					{
						pk::point pt = pts[j];
						pk::unit@ u2 = getUnit(pt);
						if(u2==null || !pk::is_enemy(unit,u2))
							continue;
						if(dict.exists(pk::format("{}",u2.get_id())))
							continue;
						dict[pk::format("{}", u2.get_id())] = 3;
						arr2.insertLast(u2);
						arr2Demage.insertLast(objDem);
					}
				}

				for (int i = 0; i < arr2.length; i++)
				{
					pk::unit@ u = arr2[i];
					pk::damage_info objDem = arr2Demage[i];
					create_effect(0x4a, u.get_pos());
					pk::add_troops(u, -objDem.troops_damage * 스플레시_데미지_비율, true);
					updateAfter(unit, u);

					if (pk::rand(세이_RAND) == 0)
					{
						pk::say(pk::encode("병사들이 왜죽는것이냐.."), pk::get_person(u.leader), u);
					}
				}
			}

			if (has보물skill(unit, 보물특기_관통공격) && unit.weapon == 병기_노)
			{
				array<pk::point> parr;
				array<int> parrDam;
				array<pk::point> arr = getAttackerPoints보물(unit);
				array<pk::damage_info> arrDemage = getAttackerDamages보물(unit);

				for (int i = 0; i < arr.length; i++)
				{
					array<pk::point> parr2 = get관통path(unit.get_pos(), arr[i]);
					for (int j = 0; j < parr2.length; j++)
					{
						pk::point ppp = parr2[j];
						bool bFound = false;
						for (int k = 0; k < parr.length; k++)
						{
							pk::point ppp2 = parr[k];
							if (ppp == ppp2)
							{
								bFound = true;
								break;
							}
						}
						if (!bFound)
						{
							for (int k = 0; k < arr.length; k++)
							{
								pk::point ppp2 = arr[k];
								if (ppp == ppp2)
								{
									bFound = true;
									break;
								}
							}
							if (!bFound)
							{
								parr.insertLast(ppp);
								parrDam.insertLast(arrDemage[i].troops_damage);
							}
						}
					}
				}



				for (int i = 0; i < parr.length; i++)
				{
					pk::point ppp = parr[i];
					pk::unit@ uu = getUnit(ppp);
					if (uu == null || !pk::is_enemy(uu,unit))
						continue;

					create_effect(0x4a, uu.get_pos());
					pk::add_troops(uu, -parrDam[i] * 스플레시_데미지_비율, true);
					//if(has보물skill(unit, 보물특기_모든공격_화계발생))
					//	pk::create_fire(uu.get_pos(), pk::rand(2) + 1, unit);
					updateAfter(unit, uu);
					if (pk::rand(세이_RAND) == 0)
					{
						pk::say(pk::encode("병사들이 왜죽는것이냐.."), pk::get_person(uu.leader), uu);
					}
				}
			}
			도망자_처리();
			clearAttacker보물(unit);
		}

		pk::point get관통center(pk::point pt0)
		{
			pk::point point = pk::hex_pos_to_screen_pos(pt0);

			pk::point pt = pk::get_neighbor_pos(pt0, 방향_남, 1);
			pk::point point1 = pk::hex_pos_to_screen_pos(pt);

			pt = pk::hex_pos_to_screen_pos(pt0);
			pk::point pt2 = pk::hex_pos_to_screen_pos(pk::get_neighbor_pos(pt0, 방향_남, 1));
			pk::point point2 = pk::point(pt2.x + pt2.y - pt.y, pt2.y);


			pt = pk::hex_pos_to_screen_pos(pt0);
			pt2 = pk::hex_pos_to_screen_pos(pk::get_neighbor_pos(pt0, 방향_남, 1));
			pk::point point3 = pk::point(pt.x + pt2.y - pt.y, pt.y);


			return pk::point((point.x + point1.x + point2.x + point3.x) / 4, (point.y + point1.y + point2.y + point3.y) / 4);
		}

		array<pk::point> get관통path(pk::point pos0, pk::point pos1)
		{
			pk::point cpos0 = get관통center(pos0);
			pk::point cpos1 = get관통center(pos1);

			array<pk::point> arr;
			for (int i = 0; i < 20; i++)
			{
				pk::point pt;
				pt.x = cpos0.x + (cpos1.x - cpos0.x) * (i / 19.0);
				pt.y = cpos0.y + (cpos1.y - cpos0.y) * (i / 19.0);

				pk::point hexPt = pk::screen_pos_to_hex_pos(pt);

				bool bFound = false;
				for (int j = 0; j < arr.length; j++)
				{
					if (hexPt == arr[j])
					{
						bFound = true;
						break;
					}
				}
				if (!bFound)
					arr.insertLast(hexPt);
			}
			return arr;
		}


		pk::point dst_pos_;
		void doMeteo(pk::unit@ unit, pk::unit@ target)
		{
			pk::point src_pos_ = unit.get_pos();
			pk::point dst_pos = target.get_pos();
			// 실행 부대 계략 실행 음성, 효과 생성
			if (pk::is_in_screen(src_pos_))
			{
				pk::play_voice(0x35, pk::get_person(unit.leader));
				pk::play_se(0x39, src_pos_);
				pk::create_effect(0x3a, src_pos_);
				pk::wait(1, 1000);
			}

			// 대미지 계산
			int troops_damage = (메테오_기본_데미지 + pk::rand(메테오_랜덤_데미지));

			// 목표 부대 애니메이션
			if (pk::is_in_screen(dst_pos))
			{
				dst_pos_ = dst_pos;
				// 운석 효과 생성
				auto handle = pk::create_effect(0x6b, dst_pos, function(handle, delta) {
					// 운석 떨어지는 소리
					if (delta == -1) {
						pk::play_se(0x56, main.dst_pos_);
					}
					// 애니메이션이 끝났다면 삭제
					else if (handle.elapsed > 500) {
						pk::create_effect(0xe, main.dst_pos_);
						pk::play_se(0x71, main.dst_pos_);
						return true;
					}

					auto v = pk::hex_pos_to_world_pos(main.dst_pos_);
					v.y = v.y + 120 - handle.elapsed / 500.f * 120;
					auto m = pk::matrix4();
					m.translate(v);
					handle.m = m;
					return false;
				});

				// 대미지 애니메이션
				pk::damage_info info;
				info.troops_damage = troops_damage;
				info.dst_pos = dst_pos;
				pk::unit_anim(target, 32, { info }, -1, 500, pk::encode("아악~"));

				// 부대 애니메이션이 끝나거나 클릭으로 생략할 때 까지 대기
				pk::wait(1);

				// 생략한경우를 위한 애니메이션 종료, 효과 삭제
				pk::stop_unit_anim();
				pk::remove(handle);
			}

			// 대미지 적용
			pk::add_troops(target, -troops_damage, true);
			if(pk::rand_bool(메테오_화계_확률))
				pk::create_fire(dst_pos, pk::rand(2) + 2, unit, true);
			return;
		}

		bool isEnabled()
		{
			return true;
		}

		string getDesc_신보물일람()
		{
			return pk::encode("신보물을 확인합니다.");
		}
		string getText_신보물일람()
		{
			return pk::encode("신보물일람");
		}

		array<string> 특기설명백업(255);
		array<string> 특기이름백업(255);
		array<int> 특기백업(무장_끝);
		void Save특기()
		{
			for (int i = 0; i < 255; i++)
			{
				pk::skill@ s = pk::get_skill(i);
				if (s == null)
					continue;
				특기설명백업[i] = s.desc;
				특기이름백업[i] = s.name;
			}

			for (int i = 0; i < 무장_끝; i++)
			{
				pk::person@ p = pk::get_person(i);
				if (p == null)
					continue;
				특기백업[i] = p.skill;
			}
		}
		void Load특기()
		{
			for (int i = 0; i < 255; i++)
			{
				pk::skill@ s = pk::get_skill(i);
				if (s == null)
					continue;
				s.desc = 특기설명백업[i];
				s.name = 특기이름백업[i];
			}
			for (int i = 0; i < 무장_끝; i++)
			{
				pk::person@ p = pk::get_person(i);
				if (p == null)
					continue;
				p.skill = 특기백업[i];
			}
		}


		bool isRented(pk::item@ it)
		{
			for (int i = 0; i < _rent.length; i++)
			{
				ItemRent@ ir = _rent[i];
				if (ir.item.get_id() == it.get_id())
				{
					return true;
				}
			}
			return false;
		}
		pk::person@ getRentedOwner(pk::item@ it)
		{
			for (int i = 0; i < _rent.length; i++)
			{
				ItemRent@ ir = _rent[i];
				if (ir.item.get_id() == it.get_id())
				{
					return ir.owner0;
				}
			}
			return null;
		}
		

		array<ItemDisplay@> compute(pk::force@ force=null)
		{
			dictionary dict;
			array<ItemDisplay@> arr;
			for (int i = 0; i < 보물_끝; i++)
			{
				pk::item@ it = pk::get_item(i);
				if(it==null)
					continue;
				if(it.type == -1)
					continue;


				//pk::printf("type:{},{},{}\n", i, it.type,it.status);
				pk::person@ owner = pk::get_person(it.owner);
				if (isRented(it))
				{
					@owner = getRentedOwner(it);
				}
				if(force!=null && (owner == null || owner.get_force_id() != force.get_id()))
					continue;

				ItemDisplay id;
				@id.item = it;
				@id.owner = owner;
				id.value = it.value;
				id.name = getName(it);
				id.path = 보물이미지[it.get_id()];
				arr.insertLast(id);

				if (owner != null)
				{
					string key = pk::format("{}", owner.get_id());
					int count = 0;
					if (dict.exists(key)) 
						count = int(dict[key]);
					count++;
					dict[key] = count;
				}
			}
			for (int i = 0; i < 커스텀아이템스.length; i++)
			{
				CustomItem@  it = 커스텀아이템스[i];
				if(it==null)
					continue;

				if (force != null && (it.owner == null || it.owner.get_force_id() != force.get_id()))
					continue;

				ItemDisplay id;
				@id.citem = it;
				@id.owner = it.owner;
				id.value = it.value;
				id.name = it.name;
				id.path = it.path;
				arr.insertLast(id);

				if (it.owner != null)
				{
					string key = pk::format("{}", it.owner.get_id());
					int count = 0;
					if (dict.exists(key))
						count = int(dict[key]);
					count++;
					dict[key] = count;
				}
			}

			for (int i = 0; i < arr.length; i++)
			{
				ItemDisplay@ id = arr[i];
				if(id.owner == null)
					continue;

				string key = pk::format("{}", id.owner.get_id());
				id.itemCount = int(dict[key]);
			}


			arr.sort(function(x, y)
			{
				if (x.itemCount != y.itemCount)
					return x.itemCount > y.itemCount;

				if (x.owner != null && y.owner != null)
					return x.owner.get_id() <= y.owner.get_id();
				else if (x.owner != null)
					return true;
				else if (y.owner != null)
					return false;
				return true;
			});
			return arr;
		}

		void handler_신보물일람2()
		{
			array<ItemDisplay@> arr = compute();
			while (true)
			{
				int count = pk::min(255, arr.length);
				pk::list<pk::person@> ris2;

				for (int i = 0; i < count; i++)
				{
					ItemDisplay@ di = arr[i];
					pk::skill@ s = pk::get_skill(i);
					if(di == null)
						continue;

					pk::person@ p = pk::get_person(i);
					p.skill = s.get_id();

					string str = ""; 
					if(di.citem!=null)
						str=pk::format("\x1b[2x{}\x1b[0x,\x1b[18x{}\x1b[0x,가치:{}", di.owner != null ? getName(di.owner) : "없음", di.name, di.value);
					else
						str = pk::format("\x1b[2x{}\x1b[0x,\x1b[1x{}\x1b[0x,가치:{}", di.owner != null ? getName(di.owner) : "없음", di.name, di.value);

					s.desc = pk::encode(str);
					if (s.name == "")
						s.name = pk::encode("설명");
					//s.name = pk::encode("아이템");

					ris2.add(p);
				}

				pk::list<pk::person@> persons = pk::person_selector(pk::encode("보물 선택"), pk::encode("보물을 선택해주십시오"), ris2, 1, 1);
				if (persons.count == 0)
					return;

				@_scene_item_display = arr[persons[0].get_id()];
				pk::scene(pk::scene_t(scene_보물표시));
			}
		}

		ItemDisplay@ _scene_item_display = null;
		void scene_보물표시()
		{
			ItemDisplay@ di = _scene_item_display;
			pk::background(_scene_item_display.path);
			

			string str;
			if (_scene_item_display.item != null)
			{
				str = pk::format("\x1b[1x{}\x1b[0x,\x1b[1x{}\x1b[0x,가치:{}", di.owner != null ? getName(di.owner) : "없음", di.name, di.value);
				str = str + "\n부가능력 조회불가";
			}
			else 
			{
				CustomItem@ ci = di.citem;
				pk::item@ src= pk::get_item(ci.srcItem);
				str = pk::format("\x1b[1x{}\x1b[0x,\x1b[1x{}\x1b[0x,가치:{},원본:{}\n", di.owner != null ? getName(di.owner) : "없음", di.name, di.value,getName(src));
				str = str+ pk::format("통:{},무:{},지:{},정:{},매:{}\n", ci.능력[0], ci.능력[1], ci.능력[2], ci.능력[3], ci.능력[4]);
				str = str + "특기:";
				for (int i = 0; i < ci.skills.length; i++)
				{
					if(i!=ci.skills.length-1)
						str = str + pk::format("\x1b[1x{}\x1b[0x ",getName(pk::get_skill(ci.skills[i])));
					else
						str = str + pk::format("\x1b[1x{}\x1b[0x", getName(pk::get_skill(ci.skills[i])));
				}
			}

			pk::message_box(pk::encode(str));
			pk::background(-1);
		}

		bool handler_신보물일람()
		{
			try
			{
				Save특기();
				handler_신보물일람2();
			}
			catch
			{
				Load특기();
			}

			Load특기();
			return true;
		}


		pk::force@ _force;
		pk::building@ _building;
		pk::city@ _city;
		pk::district@ _district;
		void 신보물수여Init(pk::building@ building)
		{
			@_force = pk::get_force(building.get_force_id());
			@_building = building;
			@_city = pk::building_to_city(building);
			@_district = pk::get_district(building.get_district_id());
		}

		bool Is신보물수여Enabled()
		{
			return compute(_force).length > 0 && _district.ap >= 10;
		}

		string 신보물수여Desc()
		{
			return pk::encode(pk::format("보물/신보물을 수여합니다(행동력{})",10));
		}
		string 신보물수여Text()
		{
			return pk::encode("신보물수여");
		}
		
		void 신보물수여Handler2()
		{
			array<ItemDisplay@> arr = compute(_force);

			while (_district.ap >= 10)
			{
				int count = pk::min(255, arr.length);
				pk::list<pk::person@> ris2;

				for (int i = 0; i < count; i++)
				{
					ItemDisplay@ di = arr[i];
					pk::skill@ s = pk::get_skill(i);
					if (di == null)
						continue;

					pk::person@ p = pk::get_person(i);
					p.skill = s.get_id();

					string str = "";
					if (di.citem != null)
						str = pk::format("\x1b[2x{}\x1b[0x,\x1b[18x{}\x1b[0x,가치:{}", di.owner != null ? getName(di.owner) : "없음", di.name, di.value);
					else
						str = pk::format("\x1b[2x{}\x1b[0x,\x1b[1x{}\x1b[0x,가치:{}", di.owner != null ? getName(di.owner) : "없음", di.name, di.value);

					s.desc = pk::encode(str);

					if(s.name == "")
						s.name = pk::encode("설명");

					ris2.add(p);
				}

				pk::list<pk::person@> persons = pk::person_selector(pk::encode("보물 선택"), pk::encode("보물을 선택해주십시오"), ris2, 1, 1);
				if (persons.count == 0)
					return;

				@_scene_item_display = arr[persons[0].get_id()];
				pk::scene(pk::scene_t(scene_보물수여));

				pk::message_box(pk::encode("보물을 수여할 무장을 선택하세요."));


				pk::list<pk::person@> persons0 = pk::get_person_list(_force, pk::mibun_flags(신분_군주,신분_태수,신분_도독,신분_일반));
				persons0.remove_at(persons0.index_of(_scene_item_display.owner));
				pk::list<pk::person@> persons1 = pk::person_selector(pk::encode("무장 선택"), pk::encode("무장을 선택해주십시오"), persons0, 1, 1);
				if(persons1.count == 0)
					continue;

				if (_scene_item_display.owner.mibun != 신분_군주)
				{
					pk::message_box(pk::encode("아오 개짜증!!!"), _scene_item_display.owner);
					_scene_item_display.owner.loyalty = pk::max(0,_scene_item_display.owner.loyalty -_scene_item_display.value);
					pk::message_box(pk::encode(pk::format("충성도가 {}로 하락했습니다", _scene_item_display.owner.loyalty)));
				}

				if (_scene_item_display.citem != null)
				{
					_scene_item_display.citem.updateOwner(persons1[0]);
				}
				else 
				{
					_scene_item_display.item.owner = persons1[0].get_id();
					_scene_item_display.item.update();
					persons1[0].update();
				}

				if (persons1[0].mibun != 신분_군주)
				{
					pk::message_box(pk::encode("감사합니다.!!!"), persons1[0]);
					persons1[0].loyalty = pk::min(255, persons1[0].loyalty + _scene_item_display.value);
					pk::message_box(pk::encode(pk::format("충성도가 {}로 상승했습니다", persons1[0].loyalty)));
				}

				_district.ap = pk::max(_district.ap - 10,0);
				arr = compute(_force);
			}
		}

		void scene_보물수여()
		{
			ItemDisplay@ di = _scene_item_display;
			pk::background(_scene_item_display.path);


			string str;
			if (_scene_item_display.item != null)
			{
				str = pk::format("\x1b[1x{}\x1b[0x,\x1b[1x{}\x1b[0x,가치:{}\n", di.owner != null ? getName(di.owner) : "없음", di.name, di.value);
				str = str + "부가능력 조회불가";
			}
			else
			{
				CustomItem@ ci = di.citem;
				pk::item@ src = pk::get_item(ci.srcItem);
				str = pk::format("\x1b[1x{}\x1b[0x,\x1b[1x{}\x1b[0x,가치:{},원본:{}\n", di.owner != null ? getName(di.owner) : "없음", di.name, di.value, getName(src));
				str = str + pk::format("통:{},무:{},지:{},정:{},매:{}\n", ci.능력[0], ci.능력[1], ci.능력[2], ci.능력[3], ci.능력[4]);
				str = str + "특기:";
				for (int i = 0; i < ci.skills.length; i++)
				{
					if (i != ci.skills.length - 1)
						str = str + pk::format("\x1b[1x{}\x1b[0x ", getName(pk::get_skill(ci.skills[i])));
					else
						str = str + pk::format("\x1b[1x{}\x1b[0x", getName(pk::get_skill(ci.skills[i])));
				}
			}

			pk::message_box(pk::encode(str));
			pk::background(-1);
		}

		bool 신보물수여Handler()
		{
			try
			{
				Save특기();
				신보물수여Handler2();
			}
			catch
			{
				Load특기();
			}

			Load특기();
			return true;

		}




		string getName(pk::force@ f)
		{
			if (f == null)
				return "null";
			return getName(pk::get_person(f.kunshu));
		}
		string getName(pk::object@ obj)
		{
			return obj != null ? pk::decode(pk::get_name(obj)) : "null";
		}
		string getNameLeader(pk::unit@ obj)
		{
			if (obj == null)
				return "null";
			pk::person@ p = pk::get_person(obj.leader);
			if (p == null)
				return "null";
			return pk::decode(pk::get_name(p));
		}
		void setSkill(pk::person@ p, int skill)
		{
			p.skill = skill;
			//pk::skill@ s = pk::get_skill(skill);
			//if (s == null)
			//	pk::printf("set {},null\n", pk::decode(pk::get_name(p)));
			//else
			//	pk::printf("set {},{}\n", pk::decode(pk::get_name(p)), pk::decode(pk::get_name(s)));

		}
		void resetSkill(pk::person@ p, int skill)
		{
			p.skill = skill;
			//pk::skill@ s = pk::get_skill(skill);
			//if (s == null)
			//	pk::printf("reset {},{}\n", pk::decode(pk::get_name(p)), skill);
			//else
			//	pk::printf("reset {},{}\n", pk::decode(pk::get_name(p)), pk::decode(pk::get_name(s)));
		}
		pk::unit@ getUnit(pk::point pos)
		{
			return pk::is_valid_pos(pos) ? pk::get_unit(pos) : null;
		}
		void injury(pk::person@ p)
		{
			if (p == null)
				return;
			if (pk::has_skill(p, 특기_강운))
				return;
			if (p.shoubyou == 상병_빈사)
				return;

			string strType = "";
			switch (p.shoubyou)
			{
			case 상병_건강:p.shoubyou = 상병_경증; strType = "경증"; break;
			case 상병_경증:p.shoubyou = 상병_중증; strType = "중증"; break;
			case 상병_중증:p.shoubyou = 상병_빈사; strType = "빈사"; break;

			default:
				break;
			}
			p.update();

			switch (pk::rand(3))
			{
			case 0: pk::say(pk::encode("팔이.."), p, getUnit(p.get_pos())); break;
			case 1: pk::say(pk::encode("여기선 부상을.."), p, getUnit(p.get_pos())); break;
			case 2: pk::say(pk::encode("아악..이러면"), p, getUnit(p.get_pos())); break;
			default:
				break;
			}

			pk::force@ force = pk::get_force(p.get_force_id());
			pk::person@ kunshu = force != null ? pk::get_person(force.kunshu) : null;
			if (kunshu != null)
			{
				string str = pk::format("\x1b[2x{}\x1b[0x군 \x1b[2x{}\x1b[0x,\x1b[29x{}\x1b[0x 상태", getName(kunshu), getName(p), strType);
				pk::history_log(p.get_pos(), force != null ? force.color : -1, pk::encode(str));
			}
		}

		bool updateAfter(pk::unit@ attacker, pk::hex_object@ target)
		{
			if (target == null)
				return false;

			pk::unit@ targetU = getUnit(target.get_pos());
			if (targetU != null && targetU.troops == 0)
			{
				int dist = pk::get_distance(attacker.get_pos(), target.get_pos());
				//pk::printf("kill start\n");
				pk::create_death_effect(targetU, attacker, target.get_pos());
				pk::kill(targetU, attacker, dist == 1, attacker.weapon == 병기_극);

				//pk::printf("kill end\n");
				return false;
			}
			else
			{
				pk::building@ b = pk::hex_object_to_building(target);
				if (b != null)
				{
					if (b.hp <= 0)
					{
						pk::city@ city = pk::building_to_city(b);
						pk::gate@ gate = pk::building_to_gate(b);
						pk::port@ port = pk::building_to_port(b);

						if (city != null || gate != null || port != null)
						{
							pk::set_hp(b, 1);
						}
						else
						{
							pk::destroy_cmd_info di;
							@di.building = b;
							pk::command(di);
							return false;
						}
					}
				}
			}
			return true;

		}

		void create_effect(int type, pk::point pt)
		{
			if (!pk::is_in_screen(pt))
				return;
			pk::create_effect(type, pt);
		}
		void play_se(int type, pk::point pt)
		{
			if (!pk::is_in_screen(pt))
				return;

			//pk::play_se(0x39, pt);
			//pk::play_se(type, pt);
			pk::play_se(type);
		}

	}//Main
	Main main;
}

