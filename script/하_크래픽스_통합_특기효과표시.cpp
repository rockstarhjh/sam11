/*
@만든이: 크래픽스
@Update: 2024.5.9,최초배포
@update: 2024.5.17,발롱도르 가로사이즈 제한 옵션 추가
@update: 2024.5.28,발롱도르 이름 표시 간략화
@update: 2024.5.30,신보물 보물 추가 연계
*/

namespace 통합_United
{
	const bool 무장별특기표시 = true;
	const bool 가로_표시 = true;

	const int 발롱도르_표시컬러 = 0xffffbf00;
	const int 신보물_표시컬러 = 0xffff0000;
	const int 인연효과_표시컬러 = 0xff00ff00;

	const int 발롱도르_가로사이즈 = 80;


	const int 무장없음 = -1;//수정하지 마세요
	const int 보물없음 = -1;//수정하지 마세요

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

	array<GroupInfo> 인연리스트 =
	{
		GroupInfo("오호대장군",{효과_전능상승_대},{무장_관우,무장_장비,무장_조운,무장_마초,무장_황충}),
		GroupInfo("오자양장",{효과_전능상승_중,효과_전법_공격_중,효과_전법_방어_중},{무장_장료,무장_장합,무장_서황,무장_악진,무장_우금}),
		GroupInfo("관중십장",{효과_전능상승_소,효과_공격상승_소,효과_방어상승_소},{무장_마등,무장_한수,무장_양추,무장_마완,무장_성의,무장_정은,무장_장횡,무장_이감,무장_양흥,무장_후선}),
		GroupInfo("강동십이호신",{효과_전능상승_중,효과_전적성상승},{무장_정보,무장_황개,무장_한당,무장_장흠,무장_주태,무장_진무,무장_동습,무장_감녕,무장_능통,무장_서성,무장_반장,무장_정봉}),
		GroupInfo("강동이교",{효과_주악_대},{무장_소교, 무장_대교}),
		GroupInfo("도원결의",{효과_보좌_중},{무장_유비, 무장_관우,무장_장비}),
		GroupInfo("황제의상",{효과_세력인정효과},{무장_유비, 무장_손권,무장_조비}),
		GroupInfo("오대도독",{효과_전적성상승,효과_전법_공격_중,효과_전법_방어_중},{무장_주유, 무장_육손,무장_노숙,무장_육항,무장_여몽}),
		GroupInfo("천하무쌍",{효과_인접기력감소,효과_인접병사감소},{무장_항적}),
		GroupInfo("천하무쌍",{효과_인접기력감소,효과_인접병사감소},{무장_여포}),
		GroupInfo("천하기재",{효과_계략_대},{무장_제갈량, 무장_사마의}),
		GroupInfo("복룡봉추",{효과_계략_중},{무장_제갈량, 무장_방통}),
		GroupInfo("수경문하",{효과_계략_소,효과_계략방어_소},{무장_제갈량, 무장_방통,무장_서서}),
		GroupInfo("궁신",{효과_전법반드시성공},{무장_황충, 무장_하후연,무장_여포,무장_국의,무장_장흠}),
		GroupInfo("원소쌍벽",{효과_공격상승_중},{무장_안량, 무장_문추}),
		GroupInfo("왕좌지재",{효과_전능상승_대},{무장_순욱,무장_저수, 무장_장소 ,무장_장완}),
		GroupInfo("묘령여인",{효과_경국,효과_전능상승_중},{무장_여영기,무장_마운,무장_황월영,무장_포삼랑}),
		GroupInfo("이민족",{효과_전능상승_소,효과_공격상승_소,효과_방어상승_소},{무장_맹획,무장_축융,무장_사마가,무장_올돌골}),
		GroupInfo("의형제",{효과_보좌_중},{무장_손책, 무장_주유}),
		GroupInfo("관장지용",{효과_인접기력감소,효과_인접병사감소},{무장_관우, 무장_장비}),
		GroupInfo("수어지교",{효과_보좌_중,효과_매력_상승_중},{무장_유비, 무장_제갈량}),
		GroupInfo("사마팔달",{효과_명성_중},{무장_사마랑,무장_사마의, 무장_사마부}),
		GroupInfo("충렬일로",{효과_전법_공격_중,효과_무력_상승_소,효과_공격상승_소},{무장_유비, 무장_조운}),
		GroupInfo("영천책사",{효과_계략_중,효과_지력_상승_소},{무장_순욱, 무장_순유, 무장_곽가, 무장_정욱, 무장_유엽}),
		GroupInfo("화북책사",{효과_계략_중,효과_계략방어_소,효과_지력_상승_소},{무장_전풍, 무장_저수, 무장_봉기, 무장_곽도, 무장_순심, 무장_신평, 무장_심배}),
		GroupInfo("익주책사",{효과_계략_중,효과_계략방어_소,효과_지력_상승_소},{무장_황권, 무장_장송, 무장_법정}),
		GroupInfo("촉한책사",{효과_계략_중,효과_계략방어_소,효과_계략_기력_감소},{무장_제갈량, 무장_방통, 무장_법정, 무장_서서, 무장_황권}),
		GroupInfo("강동책사",{효과_계략_중,효과_계략방어_소,효과_지력_상승_소},{무장_장소, 무장_고옹, 무장_우번, 무장_보즐, 무장_감택}),
		GroupInfo("담소자약",{효과_공격상승_중,효과_인접기력감소,효과_인접병사감소,효과_주악_중},{무장_손권,무장_감녕}),
		GroupInfo("강동2통",{효과_공격상승_중,효과_인접기력감소,효과_인접병사감소,효과_주악_중},{무장_손책,무장_태사자}),
		GroupInfo("마씨오상",{효과_명성_중,효과_정치_상승_중,효과_지력_상승_소},{무장_마량,무장_마속}),
		GroupInfo("육출기산",{효과_전능상승_소,효과_전법_공격_중,효과_전법_방어_중,효과_계략_크리티컬_항상성공},{무장_유선,무장_제갈량}),
		GroupInfo("촉과",{효과_부호_중,효과_미도_중,효과_지력_상승_소,효과_정치_상승_대},{무장_제갈량,무장_법정,무장_유파,무장_이엄,무장_이적}),
		GroupInfo("호표기",{효과_전능상승_소,효과_전법_공격_소},{무장_조휴,무장_조진}),
		GroupInfo("화북쌍벽",{효과_공격상승_중},{무장_안량, 무장_문추}),
		GroupInfo("묘령여인",{효과_경국,효과_전능상승_중},{무장_여영기,무장_마운,무장_황월영,무장_포삼랑}),
		GroupInfo("강동이장",{효과_정치_상승_대,효과_부호_중,효과_미도_중},{무장_장소,무장_장굉})
		//GroupInfo("테스트",{효과_계략_기력_감소,효과_계략_크리티컬_항상성공,효과_인접_교란,효과_인접_위보,효과_인접_화계},{무장_장료,무장_진궁})


	};


	class GroupInfo
	{
		array<int> idsApply;
		array<int> ids;
		pk::list<pk::person@> members;
		pk::list<pk::person@> membersApply;
		string name;
		bool b = false;
		pk::force@ force = null;

		GroupInfo() {}
		GroupInfo(string name0, array<int> arrIds, array<int> arrMember)
		{
			name = name0;
			ids = arrIds;
			for (int i = 0; i < arrMember.length; i++)
			{
				pk::person@ p = pk::get_person(arrMember[i]);
				if (p == null)
					continue;
				members.add(p);
			}
		}
	};
	class ForceInfo
	{
		array<SpecialForceApply@> applies;
		pk::force@ force;
		int numApply = 0;
	};

	class SpecialForceApply
	{
		SpecialForceItem@ item;
		pk::force@ force;
		pk::list<pk::person@> persons;
	};

	class SpecialForceItem
	{
		int id;
		bool bUse;
		int 병종;
		int color;

		array<int> fids;
		array<ForceInfo@> currentForces;

		SpecialForceItem() {}
	};

	const int 특수병과_기병_백마의종 = 0;
	const int 특수병과_기병_서량철기 = 1;
	const int 특수병과_기병_호표기 = 2;
	const int 특수병과_기병_비웅경기 = 3;

	const int 특수병과_창병_청주병 = 4;
	const int 특수병과_창병_백이병 = 5;
	const int 특수병과_창병_대극사 = 6;
	const int 특수병과_창병_선등열사 = 7;

	const int 특수병과_극병_단양병 = 8;
	const int 특수병과_극병_해번군 = 9;
	const int 특수병과_극병_등갑군 = 10;
	const int 특수병과_극병_함진영 = 11;

	const int 특수병과_노병_강노병 = 12;
	const int 특수병과_노병_무당비군 = 13;
	const int 특수병과_노병_연노병 = 14;
	const int 특수병과_노병_오계만병 = 15;
	const int 특수병과_노병_연노전차 = 16;

	const int 특수병과_기병_오환돌기 = 17;
	const int 특수병과_창병_동주병 = 18;
	const int 특수병과_창병_산월병 = 19;
	const int 특수병과_노병_흉노병 = 20;
	const int 특수병과_극병_천금군병 = 21;

	const int 특수병과_기병_상병 = 22;
	const int 특수병과_창병_호사 = 23;
	const int 특수병과_기병_맹수대 = 24;
	const int 특수병과_노병_회복병 = 25;
	const int 특수병과_극병_철차대 = 26;
	const int 특수병과_극병_청건병 = 27;

	const int 효과_전능상승_소 = 0;
	const int 효과_전능상승_중 = 1;
	const int 효과_전능상승_대 = 2;
	const int 효과_공격상승_소 = 3;
	const int 효과_공격상승_중 = 4;
	const int 효과_공격상승_대 = 5;
	const int 효과_방어상승_소 = 6;
	const int 효과_방어상승_중 = 7;
	const int 효과_방어상승_대 = 8;
	const int 효과_보좌_소 = 9;
	const int 효과_보좌_중 = 10;
	const int 효과_보좌_대 = 11;
	const int 효과_주악_소 = 12;
	const int 효과_주악_중 = 13;
	const int 효과_주악_대 = 14;
	const int 효과_전법_공격_소 = 15;
	const int 효과_전법_공격_중 = 16;
	const int 효과_전법_공격_대 = 17;
	const int 효과_전법_방어_소 = 18;
	const int 효과_전법_방어_중 = 19;
	const int 효과_전법_방어_대 = 20;
	const int 효과_계략_소 = 21;
	const int 효과_계략_중 = 22;
	const int 효과_계략_대 = 23;
	const int 효과_계략방어_소 = 24;
	const int 효과_계략방어_중 = 25;
	const int 효과_계략방어_대 = 26;
	const int 효과_인접기력감소 = 27;
	const int 효과_인접병사감소 = 28;
	const int 효과_전적성상승 = 29;
	const int 효과_전법반드시성공 = 30;
	const int 효과_명경 = 31;
	const int 효과_통찰 = 32;
	const int 효과_경국 = 33;
	const int 효과_세력인정효과 = 34;
	const int 효과_공적상승_소 = 35;
	const int 효과_공적상승_중 = 36;
	const int 효과_공적상승_대 = 37;
	const int 효과_부호_소 = 38;
	const int 효과_부호_중 = 39;
	const int 효과_부호_대 = 40;
	const int 효과_미도_소 = 41;
	const int 효과_미도_중 = 42;
	const int 효과_미도_대 = 43;
	const int 효과_명성_소 = 44;
	const int 효과_명성_중 = 45;
	const int 효과_명성_대 = 46;
	const int 효과_계략_기력_감소 = 47;
	const int 효과_계략_크리티컬_항상성공 = 48;
	const int 효과_공격_크리티컬_항상성공 = 49;
	const int 효과_포박_불가 = 50;
	const int 효과_기병_전법_사망_불가 = 51;
	const int 효과_소병력_혼란_불가 = 52;
	const int 효과_인접_교란 = 53;
	const int 효과_인접_위보 = 54;
	const int 효과_인접_화계 = 55;
	const int 효과_통솔_상승_소 = 56;
	const int 효과_통솔_상승_중 = 57;
	const int 효과_통솔_상승_대 = 58;
	const int 효과_무력_상승_소 = 59;
	const int 효과_무력_상승_중 = 60;
	const int 효과_무력_상승_대 = 61;
	const int 효과_지력_상승_소 = 62;
	const int 효과_지력_상승_중 = 63;
	const int 효과_지력_상승_대 = 64;
	const int 효과_정치_상승_소 = 65;
	const int 효과_정치_상승_중 = 66;
	const int 효과_정치_상승_대 = 67;
	const int 효과_매력_상승_소 = 68;
	const int 효과_매력_상승_중 = 69;
	const int 효과_매력_상승_대 = 70;
	const int 효과_끝 = 71;


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
	const int 보물특기_대불굴 = 26;//불굴의 상위버전입니다. 2000병력이하일때, 90확률로 막습니다.


	class CustomItem
	{
		pk::person@ owner = null;
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


		CustomItem() {}
		CustomItem(int id0, string str, string path0, array<int> 보물스킬0, array<int> skills0, int 통솔, int 무력, int 지력, int 정치력, int 매력, int type0, int value0, int 원본보물, int 소유무장)
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
				@owner = pk::get_person(소유무장);
			}
		}

		void updateOwner(pk::person@ newOwner)
		{
			@owner = newOwner;
		}

	}
	const int KEY_발롱도르 = pk::hash("발롱도르_Export");
	const int KEY_신보물 = pk::hash("신보물_Export");
	const int KEY_특수병과 = pk::hash("특수병과전쟁_Export");
	const int KEY_인연효과 = pk::hash("인연효과_Export");

	class UnitInfo
	{
		pk::unit@ unit;
		int y;
	};
	class Main
	{
		pk::func201_t@ prev_callback_201;
		pk::func207_t@ prev_callback_207;
		
		bool _bCritical = false;
		Main()
		{
			
			@prev_callback_201 = cast<pk::func201_t@>(pk::get_func(201));
			pk::reset_func(201);
			pk::set_func(201, pk::func201_t(callback201));                // 202 전법 성공 확률


			@prev_callback_207 = cast<pk::func207_t@>(pk::get_func(207));
			pk::reset_func(207);
			pk::set_func(207, pk::func207_t(callback207));                // 202 전법 성공 확률

			pk::menu_item 다중특기;
			다중특기.menu = 2;
			다중특기.is_enabled = pk::menu_item_is_enabled_t(isEnabled);
			다중특기.get_desc = pk::menu_item_get_desc_t(getDesc_다중특기);
			다중특기.get_text = pk::menu_item_get_text_t(getText_다중특기);
			다중특기.handler = pk::menu_item_handler_t(handler_다중특기);
			pk::add_menu_item(다중특기);
			
			pk::bind(120, pk::trigger120_t(UpdatePerFrame));
			pk::bind(174, pk::trigger174_t(부대행동완료));
			pk::bind(107, pk::trigger107_t(onDay));
			pk::bind(102, pk::trigger102_t(onInit));
			pk::bind(111, pk::trigger111_t(onTurnStart));


		}
		void onDay()
		{
			onDay발롱도르();
			load특수병과();
			load인연효과();
		}
		void onInit()
		{
			onDay발롱도르();
			load신보물();
			load특수병과();
			load인연효과();
		}
		void onTurnStart(pk::force@ f)
		{
			load신보물();
		}

		bool callback201(pk::unit@ attacker, pk::hex_object@ target, int tactics_id, bool ranged)
		{
			bool b = prev_callback_201(attacker,target,tactics_id,ranged);
			_bCritical = b;
			return b;
		}
		int callback207(pk::unit@ src, const pk::point& in src_pos, const pk::point& in dst_pos, int strategy_id)
		{
			_bCritical = true;
			return prev_callback_207(src, src_pos, dst_pos, strategy_id);
		}
		
		void 부대행동완료(pk::unit@ unit)
		{
			_bCritical = false;
		}
		pk::force@ _force;
		pk::building@ _building;
		pk::city@ _city;
		pk::district@ _district;
		bool isEnabled()
		{
			return true;
		}

		string getDesc_다중특기()
		{
			return pk::encode("무장의 다중 특기를 확인합니다.");
		}
		string getText_다중특기()
		{
			return pk::encode("다중특기확인");
		}
		bool handler_다중특기()
		{
			pk::list<pk::person@> moos;
			for (int i = 0; i < 무장_끝; i++)
			{
				pk::person@ person = pk::get_person(i);
				if (person == null)
					continue;

				moos.add(person);
			}

			pk::list<pk::person@> person_sel2 = pk::person_selector(pk::encode("무장 선택"), pk::encode("무장을 선택합니다."), moos, 1, 1);
			if (person_sel2.count == 0)
				return false;

			string str = "";
			pk::person@ moo = person_sel2[0];
			for (int i = 0; i < 255; i++)
			{
				if (pk::has_skill(moo, i))
				{
					str = str + pk::decode(pk::get_skill(i).get_name()) + " ";
				}
			}
			if (str == "")
			{
				pk::message_box(pk::encode("특기가 없습니다."));
				return true;
			}

			pk::message_box(pk::encode(str), moo);
			return true;
		}
		
		void UpdatePerFrame특기()
		{
			pk::point pt = pk::get_cursor_hex_pos();
			auto obj = pk::get_hex_object(pt);
			if (obj == null or obj.get_type_id() != 11)
				return;

			pk::unit@ unit = pk::get_unit(pt);
			if (가로_표시)
				가로표시(unit);
			else
				세로표시(unit);
		}

		array<UnitInfo@> _units = {};
		void UpdatePerFrame이름()
		{
			_units = {};
			//UpdatePerFrame이름_특수병과();
			//UpdatePerFrame이름_인연효과();
			//UpdatePerFrame이름_신보물();
			//UpdatePerFrame이름_발롱도르();

		}

		UnitInfo@ getUnit(pk::unit@ u)
		{
			if (u == null)
				return null;
			for (int i = 0; i < _units.length; i++)
			{
				UnitInfo@ ui = _units[i];
				if (ui.unit.get_id() == u.get_id())
					return ui;
			}
			return null;
		}

		void UpdatePerFrame()
		{
			//pk::unit@ unit = pk::get_selected_unit();
			//if (unit == null)
			//	return;

			if (_bCritical)
				return;
			UpdatePerFrame특기();
			UpdatePerFrame이름();
		}
		void 가로표시(pk::unit@ unit)
		{
			string str;
			if (!무장별특기표시)
			{
				array<int> arr;
				for (int i = 0; i < 255; i++)
				{
					pk::person@ p0 = pk::get_person(unit.member[0]);
					pk::person@ p1 = pk::get_person(unit.member[1]);
					pk::person@ p2 = pk::get_person(unit.member[2]);
					if ((p0 != null and pk::has_skill(p0, i)) or
						(p1 != null and pk::has_skill(p1, i)) or
						(p2 != null and pk::has_skill(p2, i)))
					{
						arr.insertLast(i);
					}
				}
				if (arr.length == 0)
					return;

				arr.sort(function(a, b)
				{
					pk::skill@ s0 = pk::get_skill(a);
					pk::skill@ s1 = pk::get_skill(b);
					return s0.type <= s1.type;
				});


				for (int i = 0; i < arr.length; i++)
				{
					if (i != arr.length - 1)
						str = str + pk::decode(pk::get_skill(arr[i]).name) + " ";
					else
						str = str + pk::decode(pk::get_skill(arr[i]).name);
				}
			}
			else
			{
				array<array<int>> arrs = { array<int>(),array<int>() ,array<int>() };
				if (unit.member[0] >= 0 and unit.member[0] < 무장_끝)
				{
					for (int i = 0; i < 255; i++)
					{
						pk::person@ p0 = pk::get_person(unit.member[0]);
						if (p0 != null and pk::has_skill(p0, i))
							arrs[0].insertLast(i);
					}
				}
				if (unit.member[1] >= 0 and unit.member[1] < 무장_끝)
				{
					for (int i = 0; i < 255; i++)
					{
						pk::person@ p0 = pk::get_person(unit.member[1]);
						if (p0 != null and pk::has_skill(p0, i))
							arrs[1].insertLast(i);
					}
				}
				if (unit.member[2] >= 0 and unit.member[2] < 무장_끝)
				{
					array<int> arr;
					for (int i = 0; i < 255; i++)
					{
						pk::person@ p0 = pk::get_person(unit.member[2]);
						if (p0 != null and pk::has_skill(p0, i))
							arrs[2].insertLast(i);
					}
				}

				str = "";
				for (int i = 0; i < arrs.length; i++)
				{
					if (i != 0)
						str = str + ",";
					if (unit.member[i] >= 0 and unit.member[i] < 무장_끝)
					{
						str = str + pk::format("\x1b[1x{}\x1b[0x", pk::decode(pk::get_name(pk::get_person(unit.member[i])))) + ":";
						if (arrs[i].length == 0)
							str = str + "없음";
						else
						{
							for (int j = 0; j < arrs[i].length; j++)
							{
								if (j != arrs[i].length - 1)
									str = str + pk::decode(pk::get_skill(arrs[i][j]).name) + " ";
								else
									str = str + pk::decode(pk::get_skill(arrs[i][j]).name);
							}
						}
					}
				}
			}

			string str2 = pk::format("공:{},방:{},통:{},무:{},지:{},정:{}"
				, unit.attr.stat[부대능력_공격], unit.attr.stat[부대능력_방어], unit.attr.stat[부대능력_통솔],
				unit.attr.stat[부대능력_무력], unit.attr.stat[부대능력_지력], unit.attr.stat[부대능력_정치]);


			pk::point point3 = pk::get_neighbor_pos(unit.get_pos(), 방향_남동, 1);
			pk::point point4 = pk::hex_pos_to_screen_pos(point3);

			pk::point point2 = point4;
			point2.y += 40;


			pk::size size0 = pk::get_size(FONT_SMALL, pk::encode(str2));
			pk::size size1 = pk::get_size(FONT_SMALL, pk::encode(str));

			size0.width += 5;
			size0.height *= 1.25;
			size1.width += 5;
			size1.height *= 1.25;


			point4.x = (point2.x + point4.x) * 0.5;
			point4.y = (point2.y + point4.y) * 0.5;

			pk::draw_text(pk::encode(str), point2);
			pk::draw_text(pk::encode(str2), point4);

			pk::rectangle r0(point4, size0);
			pk::rectangle r1(point2, size1);

			pk::draw_filled_rect(r0, 0x40000000);
			pk::draw_filled_rect(r1, 0x40000000);

			int offY = 60;

			string str발롱도르 = UpdateFrame확인_발롱도르_가로(unit);
			if (str발롱도르 != "")
			{
				point3 = pk::get_neighbor_pos(unit.get_pos(), 방향_남동, 1);
				point4 = pk::hex_pos_to_screen_pos(point3);
				point2 = point4;
				point2.y += offY;
				offY += 20;

				pk::draw_text(pk::encode(str발롱도르), point2, 발롱도르_표시컬러);
			}
			
			string str발롱도르2 = get발롱도르이름(unit, false);
			if (str발롱도르2 != "")
			{
				point3 = pk::get_neighbor_pos(unit.get_pos(), 방향_남동, 1);
				point4 = pk::hex_pos_to_screen_pos(point3);
				point2 = point4;
				point2.y += offY;
				offY += 20;

				pk::draw_text(pk::encode(str발롱도르2), point2, 발롱도르_표시컬러);
			}

			string str신보물 = UpdateFrame확인_신보물(unit);
			if(str신보물 != "")
			{
				point3 = pk::get_neighbor_pos(unit.get_pos(), 방향_남동, 1);
				point4 = pk::hex_pos_to_screen_pos(point3);
				point2 = point4;
				point2.y += offY;
				offY += 20;

				pk::draw_text(pk::encode(str신보물), point2, 신보물_표시컬러);
			}
			string str인연효과 = UpdateFrame확인_인연효과(unit);
			if (str인연효과 != "")
			{
				point3 = pk::get_neighbor_pos(unit.get_pos(), 방향_남동, 1);
				point4 = pk::hex_pos_to_screen_pos(point3);
				point2 = point4;
				point2.y += offY;
				offY += 20;

				pk::draw_text(pk::encode(str인연효과), point2, 인연효과_표시컬러);
			}

		}
		void 세로표시(pk::unit@ unit)
		{
			array<array<int>> arrs = { array<int>(),array<int>() ,array<int>() };
			if (unit.member[0] >= 0 and unit.member[0] < 무장_끝)
			{
				for (int i = 0; i < 255; i++)
				{
					pk::person@ p0 = pk::get_person(unit.member[0]);
					if (p0 != null and pk::has_skill(p0, i))
						arrs[0].insertLast(i);
				}
			}
			if (unit.member[1] >= 0 and unit.member[1] < 무장_끝)
			{
				for (int i = 0; i < 255; i++)
				{
					pk::person@ p0 = pk::get_person(unit.member[1]);
					if (p0 != null and pk::has_skill(p0, i))
						arrs[1].insertLast(i);
				}
			}
			if (unit.member[2] >= 0 and unit.member[2] < 무장_끝)
			{
				array<int> arr;
				for (int i = 0; i < 255; i++)
				{
					pk::person@ p0 = pk::get_person(unit.member[2]);
					if (p0 != null and pk::has_skill(p0, i))
						arrs[2].insertLast(i);
				}
			}

			string str = "";
			str= pk::format("공:{},방:{},통:{},무:{},지:{},정:{}"
				, unit.attr.stat[부대능력_공격], unit.attr.stat[부대능력_방어], unit.attr.stat[부대능력_통솔],
				unit.attr.stat[부대능력_무력], unit.attr.stat[부대능력_지력], unit.attr.stat[부대능력_정치]);

			pk::point point1 = pk::get_neighbor_pos(unit.get_pos(), 방향_남, 1);
			pk::point point2 = pk::hex_pos_to_screen_pos(point1);

			pk::size size0 = pk::get_size(FONT_SMALL, str);
			size0.width += 5;
			size0.height *= 1.25;

			pk::draw_text(pk::encode(str), point2);
			pk::rectangle r0(point2, size0);
			pk::draw_filled_rect(r0, 0x40000000);

			int h = 20;
			str = "";
			for (int i = 0; i < arrs.length; i++)
			{
				if (unit.member[i] <0 || unit.member[i] >= 무장_끝)
					continue;

				str = "";
				str = str + pk::format("\x1b[1x{}\x1b[0x", pk::decode(pk::get_name(pk::get_person(unit.member[i])))) + ":";
				if (arrs[i].length == 0)
					str = str + "없음";
				else
				{
					for (int j = 0; j < arrs[i].length; j++)
					{
						if (j != arrs[i].length - 1)
							str = str + pk::decode(pk::get_skill(arrs[i][j]).name) + " ";
						else
							str = str + pk::decode(pk::get_skill(arrs[i][j]).name);
					}
				}

				pk::point point3 = pk::get_neighbor_pos(unit.get_pos(), 방향_남, 1);
				pk::point point4 = pk::hex_pos_to_screen_pos(point3);
				point4.y += h;

				pk::size size1 = pk::get_size(FONT_SMALL, pk::encode(str));
				size1.width += 5;
				size1.height *= 1.25;

				pk::draw_text(pk::encode(str), point4);
				pk::rectangle r1(point4, size1);
				pk::draw_filled_rect(r1, 0x40000000);

				h += 20;
			}
		}

		///발롱도르////////////////////
		array<pk::person@> _발롱도르리스트;
		array < array<pk::person@>> _발롱도르랭킹리스트;
		array<array<array<int>>> _발롱도르특기리스트;
		int _발롱도르_특기_개수 = 0;

		bool check발롱도르(pk::person@ p, int type)
		{
			if (p == null)
				return false;
			if (_발롱도르리스트.length == 0)
				return false;
			for (int i = 0; i < _발롱도르리스트.length; i++)
			{
				pk::person@ pi = _발롱도르리스트[i];
				if (pi.get_id() == p.get_id())
				{
					array<int> arr = _발롱도르특기리스트[0][i];
					if (arr.find(type) >= 0)
						return true;
				}
			}

			for (int i = 0; i < _발롱도르랭킹리스트.length; i++)//i종료
			{
				array<pk::person@> pis = _발롱도르랭킹리스트[i];
				for (int j = 0; j < pis.length; j++)//j순위
				{
					pk::person@ pi = pis[j];
					if (pi.get_id() == p.get_id())
					{
						array<array<int>> arr = _발롱도르특기리스트[i + 1];
						if (j >= arr.length)
							continue;
						if (arr[j].find(type) >= 0)
							return true;
					}
				}
			}

			return false;
		}
		int onDay발롱도르_특기(int li)
		{
			int count = int(pk::load(KEY_발롱도르, li++, 0));
			array<array<int>> arr;

			for (int i = 0; i < count; i++)
			{
				array<int> arr0;
				int count2 = int(pk::load(KEY_발롱도르, li++, 0));
				for (int j = 0; j < count2; j++)
				{
					int a=int(pk::load(KEY_발롱도르, li++, 0));
					arr0.insertLast(a);
				}
				arr.insertLast(arr0);
			}
			_발롱도르특기리스트.insertLast(arr);
			return li;
		}
		void onDay발롱도르()
		{
			_발롱도르리스트 = {};
			_발롱도르랭킹리스트 = {};
			_발롱도르특기리스트 = {};
			int count = int(pk::load(KEY_발롱도르, 0, 0));
			if (count == 0)
				return;

			int li = 1;
			for (int i = 0; i < count; i++)
			{
				pk::person@ p = pk::get_person(int(pk::load(KEY_발롱도르, li++, 0)));
				//pk::printf("발롱도르 {} ,{}\n", i, getName(p));
				_발롱도르리스트.insertLast(p);
			}

			int count2 = int(pk::load(KEY_발롱도르, li++, 0));
			for (int i = 0; i < count2; i++)
			{

				array<pk::person@> arr;
				int count3 = int(pk::load(KEY_발롱도르, li++, 0));
				for (int j = 0; j < count3; j++)
				{
					pk::person@ p = pk::get_person(int(pk::load(KEY_발롱도르, li++, 0)));
					arr.insertLast(p);
				}
				_발롱도르랭킹리스트.insertLast(arr);
			}

			for (int i = 0; i < 25; i++)
			{
				li=onDay발롱도르_특기(li);
			}

			_발롱도르_특기_개수 = int(pk::load(KEY_발롱도르, li++, 0));

		}

		string UpdateFrame확인_발롱도르_가로(pk::unit@ unit)
		{
			if (_발롱도르리스트.length == 0)
				return "";

			array<array<int>> arrs = { array<int>(),array<int>() ,array<int>() };
			if (unit.member[0] >= 0 and unit.member[0] < 무장_끝)
			{
				for (int i = 0; i < _발롱도르_특기_개수; i++)
				{
					pk::person@ p0 = pk::get_person(unit.member[0]);
					if (p0 != null and check발롱도르(p0, i))
						arrs[0].insertLast(i);
				}
			}
			if (unit.member[1] >= 0 and unit.member[1] < 무장_끝)
			{
				for (int i = 0; i < _발롱도르_특기_개수; i++)
				{
					pk::person@ p0 = pk::get_person(unit.member[1]);
					if (p0 != null and check발롱도르(p0, i))
						arrs[1].insertLast(i);
				}
			}
			if (unit.member[2] >= 0 and unit.member[2] < 무장_끝)
			{
				array<int> arr;
				for (int i = 0; i < _발롱도르_특기_개수; i++)
				{
					pk::person@ p0 = pk::get_person(unit.member[2]);
					if (p0 != null and check발롱도르(p0, i))
						arrs[2].insertLast(i);
				}
			}

			string str = "";
			for (int i = 0; i < arrs.length; i++)
			{
				if (arrs[i].length == 0)
					continue;
				if (unit.member[i] >= 0 and unit.member[i] < 무장_끝)
				{
					if (str != "")
						str = str + ",";

					str = str + pk::format("\x1b[1x{}\x1b[0x", pk::decode(pk::get_name(pk::get_person(unit.member[i])))) + ":";
					for (int j = 0; j < arrs[i].length; j++)
					{
						string strName;
						switch (arrs[i][j])
						{
						case 0:strName = "연속행동"; break;
						case 1:strName = "심공(소)"; break; case  2:strName = "심공(중)"; break; case 3:strName = "심공(대)"; break;
						case 4:strName = "주악(소)"; break; case  5:strName = "주악(중)"; break; case 6:strName = "주악(대)"; break;
						case 7:strName = "위풍(소)"; break; case  8:strName = "위풍(중)"; break; case 9:strName = "위풍(대)"; break;
						case 10:strName = "금강"; break; case  11:strName = "불굴"; break; case 12:strName = "철벽"; break;
						case 13:strName = "등갑"; break;	case 14:strName = "명경"; break;	case 15:strName = "통찰"; break;
						case 16:strName = "질주(소)"; break; case  17:strName = "질주(중)"; break; case 18:strName = "질주(대)"; break;
						case 19:strName = "전법(소)"; break; case  20:strName = "전법(중)"; break; case 21:strName = "전법(대)"; break;
						case 22:strName = "크리티컬"; break; case 23:strName = "궁신"; break;
						case 24:strName = "스플래시(소)"; break; case 25:strName = "스플래시(중)"; break; case 26:strName = "스플래시(대)"; break;
						case 27:strName = "공격력(소)"; break; case 28:strName = "공격력(중)"; break; case 29:strName = "공격력(대)"; break;
						case 30:strName = "방어력(소)"; break; case 31:strName = "방어력(중)"; break; case 32:strName = "방어력(대)"; break;
						case 33:strName = "일기토(소)"; break; case 34:strName = "일기토(중)"; break; case 35:strName = "일기토(대)"; break;
						case 36:strName = "명성(소)"; break; case 37:strName = "명성(중)"; break; case 38:strName = "명성(대)"; break;
						case 39:strName = "능리(소)"; break; case 40:strName = "능리(중)"; break; case 41:strName = "능리(대)"; break;
						case 42:strName = "신산"; break; case 43:strName = "허실"; break; case 44:strName = "심모"; break;
						case 45:strName = "연환"; break; case 49:strName = "포박안됨"; break;
						case 46:strName = "기병사망(소)"; break; case 47:strName = "기병사망(중)"; break; case 48:strName = "기병사망(대)"; break;
						case 50:strName = "소병력(소)"; break; case 51:strName = "소병력(중)"; break; case 52:strName = "소병력(대)"; break;
						case 53:strName = "공성(소)"; break; case 54:strName = "공성(중)"; break; case 55:strName = "공성(대)"; break;
						case 56:strName = "계략(소)"; break; case 57:strName = "계략(중)"; break; case 58:strName = "계략(대)"; break;
						case 59:strName = "이속(소)"; break; case 60:strName = "이속(중)"; break; case 61:strName = "이속(대)"; break;
						case 62:strName = "맹장(소)"; break; case 63:strName = "맹장(중)"; break; case 64:strName = "맹장(대)"; break;
						default:
							break;
						}
						if (j != arrs[i].length - 1)
							str = str + pk::format("{} ", strName);
						else
							str = str + pk::format("{}", strName);
					}
				}
			}
			return str;
		}


		void UpdatePerFrame이름_발롱도르()
		{
			if (_발롱도르리스트.length == 0)
				return;

			array<pk::unit@> arr;
			for (int i = 0; i < _발롱도르리스트.length; i++)
			{
				pk::person@ pi = _발롱도르리스트[i];
				pk::unit@ u = pk::is_valid_pos(pi.get_pos()) ? pk::get_unit(pi.get_pos()) : null;
				if (u == null)
					continue;
				if (arr.findByRef(u) == -1)
					arr.insertLast(u);
			}

			for (int i = 0; i < _발롱도르랭킹리스트.length; i++)
			{
				array<pk::person@> arr2 = _발롱도르랭킹리스트[i];
				for (int j = 0; j < arr2.length; j++)
				{
					pk::person@ pi = arr2[j];
					pk::unit@ u = pk::is_valid_pos(pi.get_pos()) ? pk::get_unit(pi.get_pos()) : null;
					if (u == null)
						continue;
					if (arr.findByRef(u) == -1)
						arr.insertLast(u);
				}
			}


			_UpdateFrameName(arr);
		}

		string get발롱도르이름(pk::unit@ u,bool b이름)
		{
			array<string> strs;
			string str = "";
			int br = getBallonRank(u);
			if (br == 1)
				str = str + "발롱도르";
			else if (br <= 10)
				str = str + pk::format("발롱도르{}위", br);

			int minBR = 100;
			string str2 = "";
			for (int j = 0; j < 22; j++)
			{
				br = getRank(u, j);
				if (br <= 3)
				{
					string strType = "";
					switch (j)
					{
					case 0: strType = "통솔"; break;
					case 1: strType = "무력"; break;
					case 2: strType = "지력"; break;
					case 3: strType = "정치"; break;
					case 4: strType = "매력"; break;
					case 5: strType = "창병"; break;
					case 6: strType = "극병"; break;
					case 7: strType = "노병"; break;
					case 8: strType = "기병"; break;
					case 9: strType = "병기"; break;
					case 10: strType = "수군"; break;
					case 11: strType = "공적"; break;
					case 12: strType = "포박"; break;
					case 13: strType = "포박점수"; break;
					case 14: strType = "궤멸"; break;
					case 15: strType = "도시"; break;
					case 16: strType = "거점"; break;
					case 17: strType = "Damage"; break;
					case 18: strType = "사망";  break;
					case 19: strType = "사망점수";  break;
					case 20: strType = "일기승";  break;
					case 21: strType = "일기점수";  break;
					case 22: strType = "계략"; break;
					case 23: strType = "계략점수";  break;
					default:
						break;
					}

					if (br < minBR)
					{
						minBR = br;
						if (minBR == 1)
							str2 = pk::format("{}왕", strType);
						else
							str2 = pk::format("{}{}위", strType, br);
					}
					if (!b이름)
					{
						if (br == 1)
						{
							if (str == "")
								str = str + pk::format("{}왕", strType);
							else
								str = str + pk::format(",{}왕", strType);
						}
						else
						{
							if (str == "")
								str = str + pk::format("{}{}위", strType, br);
							else
								str = str + pk::format(",{}{}위", strType, br);
						}

						//pk::size sz = pk::get_size(FONT_SMALL, pk::encode(str));
						//if (sz.width > 발롱도르_가로사이즈)
						//{
						//	strs.insertLast(str);
						//	str = "";
						//}
					}
					strs.insertLast("");
				}
			}
			if (strs.length == 0 && str == "")
				return "";

			if (!b이름)
				return str;
			if (str != "")
			{
				if (strs.length > 0)
					str = pk::format("{}({})", str, strs.length + 1);
				else
					str = pk::format("{}", str);
			}
			else
			{
				if (strs.length > 1)
					str = pk::format("{}({})", str2, strs.length);
				else
					str = pk::format("{}", str2);
			}

			return str;
		}

		void _UpdateFrameName(array<pk::unit@> units)
		{
			for (int i = 0; i < units.length; i++)
			{
				pk::unit@ u = units[i];
				if (!pk::is_in_screen(u.get_pos()))
					continue;
				string str = get발롱도르이름(u,true);
				if(str=="")
					continue;

				array<string> strs2;
				strs2.insertLast(str);

				for (int j = 0; j < strs2.length; j++)
				{
					pk::point point = pk::hex_pos_to_screen_pos(u.get_pos());

					str = strs2[j];
					UnitInfo@ ui = getUnit(u);
					if (ui == null)
					{
						@ui = UnitInfo();
						ui.y = 0;
						@ui.unit = u;
						_units.insertLast(ui);
					}
					point.y += ui.y;
					ui.y += 20;
					pk::draw_text(pk::encode(str), point, 발롱도르_표시컬러);
					if (true)
					{
						pk::size size0 = pk::get_size(FONT_SMALL, pk::encode(str));
						pk::rectangle r0(point, size0);
						pk::draw_filled_rect(r0, 0x40000000);
					}
				}
			}
		}

		int getBallonRank(pk::unit@ u)
		{
			int a = getBallonRank(pk::get_person(u.member[0]));
			int b = getBallonRank(pk::get_person(u.member[1]));
			int c = getBallonRank(pk::get_person(u.member[2]));
			return pk::min(pk::min(a, b), c);
		}
		int getRank(pk::unit@ u, int type)
		{
			int a = getRank(pk::get_person(u.member[0]), type);
			int b = getRank(pk::get_person(u.member[1]), type);
			int c = getRank(pk::get_person(u.member[2]), type);
			return pk::min(pk::min(a, b), c);
		}

		int getBallonRank(pk::person@ p)
		{
			if (p == null)
				return 100;
			if (_발롱도르리스트.length == 0)
				return 100;
			for (int i = 0; i < _발롱도르리스트.length; i++)
			{
				pk::person@ pi = _발롱도르리스트[i];
				if (pi.get_id() == p.get_id())
				{
					return i + 1;
				}
			}
			return 100;
		}
		int getRank(pk::person@ p, int type)
		{
			if (p == null)
				return 100;
			if (_발롱도르랭킹리스트.length == 0)
				return 100;
			array<pk::person@> pis = _발롱도르랭킹리스트[type];
			for (int j = 0; j < pis.length; j++)//j순위
			{
				pk::person@ pi = pis[j];
				if (pi.get_id() == p.get_id())
				{
					return j + 1;
				}
			}
			return 100;
		}
		///신보물////////////////////////////////////////////////////////////////

		void load신보물()
		{
			for (int i = 0; i < 커스텀아이템스.length; i++)
			{
				CustomItem@ ci = 커스텀아이템스[i];
				@ci.owner = null;
			}
			int count = int(pk::load(KEY_신보물, 0, 0));
			int li = 1;
			if (count == 0)
			{
				return;
			}
			for (int i = 0; i < count; i++)
			{
				CustomItem@ ci = 커스텀아이템스[i];
				int oid = int(pk::load(KEY_신보물, li++, -1));
				if (ci != null)
					@ci.owner = pk::get_person(oid);
			}
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
				if (ci == null)
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

		void UpdatePerFrame이름_신보물()
		{
			array<pk::unit@> us;
			for (int i = 0; i < 커스텀아이템스.length; i++)
			{
				CustomItem@ ci = 커스텀아이템스[i];
				if (ci.owner == null)
					continue;
				pk::unit@ u = getUnit(ci.owner.get_pos());
				if (u == null)
					continue;
				if (!pk::is_in_screen(ci.owner.get_pos()))
					continue;

				if(us.findByRef(u)==-1)
					us.insertLast(u);
			}
			
			for (int i = 0; i < us.length; i++)
			{
				pk::unit@ u = us[i];
				array<CustomItem@> arr=getCustomItem(u);
				string str;
				for (int j = 0; j < arr.length; j++)
				{
					CustomItem@ ci = arr[j];
					if (j == 0)
						str = str + ci.name;
					else
						str = str + " " + ci.name;
				}
				UnitInfo@ ui = getUnit(u);
				if (ui == null)
				{
					@ui = UnitInfo();
					ui.y = 0;
					@ui.unit = u;
					_units.insertLast(ui);
				}
				pk::point point = pk::hex_pos_to_screen_pos(u.get_pos());
				point.y += ui.y;
				ui.y += 20;
				pk::draw_text(pk::encode(str), point, 신보물_표시컬러);
				if (true)
				{
					pk::size size0 = pk::get_size(FONT_SMALL, pk::encode(str));
					pk::rectangle r0(point, size0);
					pk::draw_filled_rect(r0, 0x40000000);
				}
			}

		}

		string UpdateFrame확인_신보물(pk::unit@ unit)
		{
			array<array<CustomItem@>> arrs = { array<CustomItem@>(),array<CustomItem@>() ,array<CustomItem@>() };
			if (unit.member[0] >= 0 and unit.member[0] < 무장_끝)
			{
				pk::person@ p0 = pk::get_person(unit.member[0]);
				array<CustomItem@> arr=getCustomItem(p0);
				arrs[0] = arr;
			}
			if (unit.member[1] >= 0 and unit.member[1] < 무장_끝)
			{
				pk::person@ p0 = pk::get_person(unit.member[1]);
				array<CustomItem@> arr = getCustomItem(p0);
				arrs[1] = arr;
			}
			if (unit.member[2] >= 0 and unit.member[2] < 무장_끝)
			{
				pk::person@ p0 = pk::get_person(unit.member[2]);
				array<CustomItem@> arr = getCustomItem(p0);
				arrs[2] = arr;
			}
			string str = "";
			for (int i = 0; i < arrs.length; i++)
			{
				array<CustomItem@> arr = arrs[i];
				if(arr.length ==0)
					continue;

				pk::person@ p = pk::get_person(unit.member[i]);
				str = str + pk::format("\x1b[1x{}\x1b[0x", pk::decode(pk::get_name(pk::get_person(unit.member[i])))) + ":";
				string str2 = "";
				for (int j = 0; j < arr.length; j++)
				{
					CustomItem@ ci = arr[j];
					for (int k = 0; k < ci.skills보물.length; k++)
					{
						string strType = "";
						switch (ci.skills보물[k])
						{
						case 보물특기_모든공격_화계발생: strType = "화계공격"; break;
						case 보물특기_인접_혼란_위보_진정: strType = "인접진정"; break;
						case 보물특기_인접_화계_소화: strType = "인접소화"; break;
						case 보물특기_인접_낙뢰: strType = "인접낙뢰"; break;
						case 보물특기_인접_스플래쉬_데미지: strType = "스플래쉬"; break;
						case 보물특기_모든공격_추가데미지: strType = "추가데미지"; break;
						case 보물특기_주악: strType = "보물주악"; break;
						case 보물특기_모든공격_충성도_저하: strType = "충성도저하"; break;
						case 보물특기_위풍: strType = "보물위풍"; break;
						case 보물특기_심공: strType = "보물심공"; break;
						case 보물특기_원킬: strType = "원킬"; break;
						case 보물특기_병량탈취: strType = "병량탈취"; break;
						case 보물특기_혼란_유발: strType = "혼란"; break;
						case 보물특기_위보_유발: strType = "위보"; break;
						case 보물특기_동토_유발: strType = "동토"; break;
						case 보물특기_일기토_유발: strType = "일기토"; break;
						case 보물특기_인접부대_건물데미지_추가: strType = "건물데미지"; break;
						case 보물특기_기교포인트_획득: strType = "기교포인트"; break;
						case 보물특기_능력연구속도향상: strType = "능력연구속도"; break;
						case 보물특기_메테오: strType = "메테오"; break;
						case 보물특기_부상유발: strType = "보물맹장"; break;
						case 보물특기_방어특기공유: strType = "방어특기공유"; break;
						case 보물특기_혼돈: strType = "혼돈"; break;
						case 보물특기_수계: strType = "수계"; break;
						case 보물특기_관통공격: strType = "관통공격"; break;
						case 보물특기_인접_회복: strType = "인접회복"; break;
						case 보물특기_대불굴:	strType = "대불굴"; break;
						default:
							break;
						}
						if(strType=="")
							continue;
						if(str2=="")
							str2 = strType;
						else
							str2 = str2 + " " + strType;
					}
					for (int k = 0; k < ci.skills.length; k++)
					{
						pk::skill@ s = pk::get_skill(ci.skills[k]);
						if(str2=="")
							str2 = pk::decode(s.name);
						else
							str2 = str2 + " " + pk::decode(s.name);
					}
				}
				str = str + str2;
			}
			return str;

		}
		//특수병과////////////////////////////////////////////////

		array<SpecialForceItem@> 특수병과리스트;
		array<ForceInfo@> 세력리스트;

		void load특수병과()
		{
			특수병과리스트 = {};
			세력리스트 = {};

			int count = int(pk::load(KEY_특수병과, 0, 0));
			if (count == 0)
				return;

			int li = 1;
			for (int i = 0; i < count; i++)
			{
				SpecialForceItem sf;
				sf.id = int(pk::load(KEY_특수병과, li++, 0));
				sf.bUse = int(pk::load(KEY_특수병과, li++, 0)) == 1 ? true : false;
				sf.병종 = int(pk::load(KEY_특수병과, li++, 0));
				sf.color = int(pk::load(KEY_특수병과, li++, 0));

				int count22 = int(pk::load(KEY_특수병과, li++, 0));
				sf.currentForces = {};
				sf.fids = {};
				for (int j = 0; j < count22; j++)
				{
					int fid = int(pk::load(KEY_특수병과, li++, 0));
					sf.fids.insertLast(fid);
				}
				특수병과리스트.insertLast(sf);
			}


			int count2 = int(pk::load(KEY_특수병과, li++, 0));
			for (int i = 0; i < count2; i++)
			{
				ForceInfo fi;
				int fid = int(pk::load(KEY_특수병과, li++, -1));
				@fi.force = fid >= 0 ? pk::get_force(fid) : null;
				fi.numApply = int(pk::load(KEY_특수병과, li++, 0));
				for (int j = 0; j < fi.numApply; j++)
				{
					SpecialForceApply sfa;
					@sfa.force = fi.force;
					int fid2 = int(pk::load(KEY_특수병과, li++, -1));
					@sfa.item = 특수병과리스트[fid2];

					int count22 = int(pk::load(KEY_특수병과, li++, -1));
					for (int k = 0; k < count22; k++)
					{
						int pid = int(pk::load(KEY_특수병과, li++, -1));
						pk::person@ p = pk::get_person(pid);
						sfa.persons.add(p);
					}

					fi.applies.insertLast(sfa);
				}


				세력리스트.insertLast(fi);
			}


			for (int i = 0; i < 특수병과리스트.length; i++)
			{
				SpecialForceItem@ sf = 특수병과리스트[i];
				for (int j = 0; j < sf.fids.length; j++)
				{
					int fid = sf.fids[j];
					ForceInfo@ fi = null;
					for (int k = 0; k < 세력리스트.length; k++)
					{
						ForceInfo@ fi0 = 세력리스트[k];
						if (fi0.force.get_id() == fid)
						{
							@fi = fi0;
							break;
						}
					}
					if(fi==null)
						continue;
					
					sf.currentForces.insertLast(fi);
				}
			}

		}

		bool check병종(pk::unit@ u, int type)
		{
			int 병종 = -1;
			switch (u.weapon)
			{
			case 병기_노:병종 = 병종_노병; break;
			case 병기_창:병종 = 병종_창병; break;
			case 병기_극:병종 = 병종_극병; break;
			case 병기_군마:병종 = 병종_기병; break;
			}
			return 병종 == type;
		}
		bool isSkill(pk::person@ f, int type)
		{
			if (f == null)
				return false;
			SpecialForceItem@ sf = getForceItem(type);
			if (sf == null)
				return false;

			if (!sf.bUse)
				return false;
			for (int i = 0; i < sf.currentForces.length; i++)
			{
				ForceInfo@ fi = sf.currentForces[i];
				if (fi == null)
					continue;
				if (fi.force.get_id() != f.get_force_id())
					continue;

				for (int j = 0; j < fi.applies.length; j++)
				{
					SpecialForceApply@ sa = fi.applies[j];
					if (sa.item.id != type)
						continue;
					for (int k = 0; k < sa.persons.count; k++)
					{
						if (sa.persons[k].get_id() == f.get_id())
							return true;
						//if (sa.persons.contains(f))
							//return true;
					}
				}
			}
			return false;
		}

		bool isSkill(pk::unit@ u, int type)
		{
			SpecialForceItem@ sf = getForceItem(type);
			if (sf == null)
				return false;

			if (!check병종(u, sf.병종))
				return false;

			pk::person@ p0 = u.member[0] >= 0 && u.member[0] < 무장_끝 ? pk::get_person(u.member[0]) : null;
			pk::person@ p1 = u.member[1] >= 0 && u.member[1] < 무장_끝 ? pk::get_person(u.member[1]) : null;
			pk::person@ p2 = u.member[2] >= 0 && u.member[2] < 무장_끝 ? pk::get_person(u.member[2]) : null;
			return isSkill(p0, type) || isSkill(p1, type) || isSkill(p2, type);
		}
		SpecialForceItem@ getForceItem(int type)
		{
			return 특수병과리스트[type];
		}
		pk::unit@ getUnit(pk::point pos)
		{
			return pk::is_valid_pos(pos) ? pk::get_unit(pos) : null;
		}

		void UpdatePerFrame이름_특수병과()
		{
			for (int i = 0; i < 세력리스트.length; i++)
			{
				ForceInfo@ fi = 세력리스트[i];

				array<pk::unit@> units;
				for (int j = 0; j < fi.applies.length; j++)
				{
					SpecialForceApply@ sa = fi.applies[j];
					if (sa == null)
						continue;
					for (int k = 0; k < sa.persons.count; k++)
					{
						pk::person@ p = sa.persons[k];
						if (!pk::is_in_screen(p.get_pos()))
							continue;
						pk::unit@ u = getUnit(p.get_pos());
						if (u == null)
							continue;
						if (!check병종(u, sa.item.병종))
							continue;
						if (units.findByRef(u) == -1)
							units.insertLast(u);
					}//k
				}//j

				for (int j = 0; j < units.length; j++)
				{
					pk::unit@ u = units[j];
					string str = "";

					int color = 0;
					for (int k = 0; k < 특수병과리스트.length; k++)
					{
						SpecialForceItem sf = 특수병과리스트[k];
						if (!sf.bUse)
							continue;
						if (!isSkill(u, k))
						{
							continue;
						}

						string name = "";
						switch (sf.id)
						{
						case 특수병과_기병_백마의종: name = "백마의종"; break;
						case 특수병과_기병_서량철기: name = "서량철기"; break;
						case 특수병과_기병_호표기: name = "호표기"; break;
						case 특수병과_기병_비웅경기: name = "비웅경기"; break;
						case 특수병과_창병_청주병: name = "청주병"; break;
						case 특수병과_창병_백이병: name = "백이병"; break;
						case 특수병과_창병_대극사: name = "대극사"; break;
						case 특수병과_창병_선등열사: name = "선등열사"; break;
						case 특수병과_극병_단양병: name = "단양병"; break;
						case 특수병과_극병_해번군: name = "해번군"; break;
						case 특수병과_극병_등갑군: name = "등갑군"; break;
						case 특수병과_극병_함진영: name = "함진영"; break;
						case 특수병과_노병_강노병: name = "강노병"; break;
						case 특수병과_노병_무당비군: name = "무당비군"; break;
						case 특수병과_노병_연노병: name = "연노병"; break;
						case 특수병과_노병_오계만병: name = "오계만병"; break;
						case 특수병과_노병_연노전차: name = "연노전차"; break;
						case 특수병과_기병_오환돌기: name = "오환돌기"; break;
						case 특수병과_창병_동주병: name = "동주병"; break;
						case 특수병과_창병_산월병: name = "산월병"; break;
						case 특수병과_노병_흉노병: name = "흉노병"; break;
						case 특수병과_극병_천금군병: name = "천금군병"; break;
						case 특수병과_기병_상병: name = "상병"; break;
						case 특수병과_창병_호사: name = "호사"; break;
						case 특수병과_기병_맹수대: name = "맹수대"; break;
						case 특수병과_노병_회복병: name = "회복병"; break;
						case 특수병과_극병_철차대: name = "철차대"; break;
						case 특수병과_극병_청건병: name = "청건병"; break;
						default:
							break;
						}


						if (str == "")
							str = str + pk::format("{}", name);
						else
							str = str + pk::format(" {}", name);

						color = sf.color;
					}
					if (str == "")
						continue;


					pk::point point = pk::hex_pos_to_screen_pos(u.get_pos());

					UnitInfo@ ui = getUnit(u);
					if (ui == null)
					{
						@ui = UnitInfo();
						ui.y = 0;
						@ui.unit = u;
						_units.insertLast(ui);
					}
					point.y += ui.y;
					ui.y += 20;

					pk::draw_text(pk::encode(str), point, color);
					if (true)
					{
						pk::size size0 = pk::get_size(FONT_SMALL, pk::encode(str));
						pk::rectangle r0(point, size0);
						pk::draw_filled_rect(r0, 0x40000000);
					}
				}

			}//세력

		}

		//인연효과///////////////////////////////////////////////////////
		bool checkGroup(pk::unit@ u, int id)
		{
			return getGroup(u, id) != null;
		}
		bool checkGroup(pk::person@ p, int id)
		{
			return getGroup(p, id) != null;
		}

		GroupInfo@ getGroup(pk::unit@ u, int id)
		{
			pk::person@ p0 = u.member[0] >= 0 and u.member[0] < 무장_끝 ? pk::get_person(u.member[0]) : null;
			GroupInfo@ gi = getGroup(p0, id);
			if (gi != null)
				return gi;
			pk::person@ p1 = u.member[1] >= 0 and u.member[1] < 무장_끝 ? pk::get_person(u.member[1]) : null;
			GroupInfo@ gi1 = getGroup(p1, id);
			if (gi1 != null)
				return gi1;
			pk::person@ p2 = u.member[2] >= 0 and u.member[2] < 무장_끝 ? pk::get_person(u.member[2]) : null;
			GroupInfo@ gi2 = getGroup(p2, id);
			return gi2;
		}
		GroupInfo@ getGroup(pk::person@ p, int id)
		{
			if (p == null)
				return null;
			pk::force@ force = pk::get_force(p.get_force_id());
			array<GroupInfo@> arr = getForces(force, { id });
			if (arr.length == 0)
				return null;

			for (int i = 0; i < arr.length; i++)
			{
				GroupInfo@ gi = arr[i];
				for (int k = 0; k < gi.members.count; k++)
				{
					pk::person@ pp = gi.members[k];
					if (pp.get_id() == p.get_id())
						return gi;
				}

			}
			return null;
		}
		array<GroupInfo@> getForces(pk::force@ force, array<int> ids)
		{
			array<GroupInfo@> gis;
			if (force == null)
				return gis;

			for (int i = 0; i < 인연리스트.length; i++)
			{
				GroupInfo@ gi = 인연리스트[i];
				if (gi.force != null && gi.force.get_id() == force.get_id())
				{
					bool bFound = false;
					for (int k = 0; k < ids.length; k++)
					{
						int id = ids[k];
						for (int j = 0; j < gi.ids.length; j++)
						{
							if (id == gi.ids[j])
							{
								bFound = true;
								break;
							}
						}
						if (bFound)
							break;
					}
					if (bFound)
						gis.insertLast(gi);
				}
			}
			return gis;
		}

		bool checkGroupType(pk::unit@ u, int id)
		{
			if (u == null)
				return false;
			return checkGroupType(pk::get_person(u.member[0]),id) || checkGroupType(pk::get_person(u.member[1]),id) || checkGroupType(pk::get_person(u.member[2]),id);
		}

		bool checkGroupType(pk::person@ p, int id)
		{
			if (p == null)
				return false;
			GroupInfo@ gi = 인연리스트[id];
			if (!gi.b)
				return false;
			if (gi.members.count == 0)
				return false;

			for (int j = 0; j < gi.members.count; j++)
			{
				pk::person@ pp = gi.members[j];
				if (pp.get_id() == p.get_id())
					return true;
			}
			return false;
		}


		void load인연효과()
		{
			for (int i = 0; i < 인연리스트.length; i++)
			{
				GroupInfo@ gi = 인연리스트[i];
				gi.idsApply = {};
				gi.membersApply.clear();
				@gi.force = null;
				gi.b = false;
			}

			int count = int(pk::load(KEY_인연효과, 0, 0));
			if (count == 0)
				return;

			int li = 1;
			for (int i = 0; i < count; i++)
			{
				GroupInfo@ gi = 인연리스트[i];
				int bi = int(pk::load(KEY_인연효과, li++, 0));
				gi.b = bi == 1;
				@gi.force = pk::get_force(int(pk::load(KEY_인연효과, li++, 0)));
				int count2 = int(pk::load(KEY_인연효과, li++, 0));
				for (int k = 0; k < count2; k++)
				{
					gi.idsApply.insertLast(int(pk::load(KEY_인연효과, li++, 0)));
				}
				int count3 = int(pk::load(KEY_인연효과, li++, 0));
				for (int k = 0; k < count3; k++)
				{
					pk::person@ p = pk::get_person(int(pk::load(KEY_인연효과, li++, 0)));
					if (p == null)
						continue;
					gi.membersApply.add(p);
				}
			}


		}

		void UpdatePerFrame이름_인연효과()
		{
			array<pk::unit@> units;
			for (int i = 0; i < 인연리스트.length; i++)
			{
				GroupInfo@ gi = 인연리스트[i];
				if(!gi.b)
					continue;
				if(gi.members.count == 0)
					continue;

				for (int j = 0; j < gi.members.count; j++)
				{
					pk::person@ p = gi.members[j];
					if(!pk::is_in_screen(p.get_pos()))
						continue;

					pk::unit@ u = getUnit(p.get_pos());
					if(u==null)
						continue;
					if (units.findByRef(u) == -1)
						units.insertLast(u);
				}
			}

			for (int i = 0; i < units.length; i++)
			{
				pk::unit@ u = units[i];
				string str = "";
				for (int j = 0; j < 인연리스트.length; j++)
				{
					if (checkGroupType(u, j)) 
					{
						if(str=="")
							str = str + 인연리스트[j].name;
						else
							str = str + " "+인연리스트[j].name;
					}
				}
				if(str == "")
					continue;

				pk::point point = pk::hex_pos_to_screen_pos(u.get_pos());

				UnitInfo@ ui = getUnit(u);
				if (ui == null)
				{
					@ui = UnitInfo();
					ui.y = 0;
					@ui.unit = u;
					_units.insertLast(ui);
				}
				point.y += ui.y;
				ui.y += 20;

				pk::draw_text(pk::encode(str), point, 인연효과_표시컬러);
				if (true)
				{
					pk::size size0 = pk::get_size(FONT_SMALL, pk::encode(str));
					pk::rectangle r0(point, size0);
					pk::draw_filled_rect(r0, 0x40000000);
				}
			}
		}


		string UpdateFrame확인_인연효과(pk::unit@ unit)
		{
			array<array<int>> arr = { array<int>(),array<int>() ,array<int>() };

			if (unit.member[0] >= 0 and unit.member[0] < 무장_끝)
			{
				pk::person@ p0 = pk::get_person(unit.member[0]);
				array<int> arr0;
				for (int i = 0; i < 효과_끝; i++)
				{
					if (checkGroup(p0, i))
						arr0.insertLast(i);
				}
				arr[0] = arr0;
			}
			if (unit.member[1] >= 0 and unit.member[1] < 무장_끝)
			{
				pk::person@ p0 = pk::get_person(unit.member[1]);
				array<int> arr0;
				for (int i = 0; i < 효과_끝; i++)
				{
					if (checkGroup(p0, i))
						arr0.insertLast(i);
				}
				arr[1] = arr0;
			}
			if (unit.member[2] >= 0 and unit.member[2] < 무장_끝)
			{
				pk::person@ p0 = pk::get_person(unit.member[2]);
				array<int> arr0;
				for (int i = 0; i < 효과_끝; i++)
				{
					if (checkGroup(p0, i))
						arr0.insertLast(i);
				}
				arr[2] = arr0;
			}

			string str = "";
			for (int i = 0; i < arr.length; i++)
			{
				if(arr[i].length == 0)
					continue;
				pk::person@ p = pk::get_person(unit.member[i]);
				str = str + pk::format("\x1b[1x{}\x1b[0x", pk::decode(pk::get_name(pk::get_person(unit.member[i])))) + ":";
				string str2 = "";
				for (int j = 0; j < arr[i].length; j++)
				{
					string strType;
					switch (arr[i][j])
					{
					case 효과_전능상승_소: strType = "전능(소)"; break; case 효과_전능상승_중: strType = "전능(중)"; break; case 효과_전능상승_대: strType = "전능(대)"; break;
					case 효과_공격상승_소: strType = "공격력(소)"; break; case 효과_공격상승_중: strType = "공격력(중)"; break; case 효과_공격상승_대: strType = "공격력(대)"; break;
					case 효과_방어상승_소: strType = "방어력(소)"; break; case 효과_방어상승_중: strType = "방어력(중)"; break; case 효과_방어상승_대: strType = "방어력(대)"; break;
					case 효과_보좌_소: strType = "보좌(소)"; break; case 효과_보좌_중: strType = "보좌(중)"; break; case 효과_보좌_대: strType = "보좌(대)"; break;
					case 효과_주악_소: strType = "주악(소)"; break; case 효과_주악_중: strType = "주악(중)"; break; case 효과_주악_대: strType = "주악(대)"; break;
					case 효과_전법_공격_소: strType = "전법성공(소)"; break; case 효과_전법_공격_중: strType = "전법성공(중)"; break; case 효과_전법_공격_대: strType = "전법성공(대)"; break;
					case 효과_전법_방어_소: strType = "전법방어(소)"; break; case 효과_전법_방어_중: strType = "전법방어(중)"; break; case 효과_전법_방어_대: strType = "전법방어(대)"; break;
					case 효과_계략_소: strType = "계략(소)"; break; case 효과_계략_중: strType = "계략(중)"; break; case 효과_계략_대: strType = "계략(대)"; break;
					case 효과_계략방어_소: strType = "계략방어(소)"; break; case 효과_계략방어_중: strType = "계략방어(중)"; break; case 효과_계략방어_대: strType = "계략방어(대)"; break;
					case 효과_인접기력감소: strType = "인접기력감소"; break;	case 효과_인접병사감소: strType = "인접병사감소"; break;
					case 효과_전적성상승: strType = "전적성"; break;	case 효과_전법반드시성공: strType = "전법항상성공"; break;
					case 효과_명경: strType = "명경"; break; case 효과_통찰: strType = "통찰"; break; case 효과_경국: strType = "경국"; break; case 효과_세력인정효과: strType = "세력인정"; break;
					case 효과_공적상승_소: strType = "공적(소)"; break; case 효과_공적상승_중: strType = "공적(중)"; break; case 효과_공적상승_대: strType = "공적(대)"; break;
					case 효과_부호_소: strType = "부호(소)"; break; case 효과_부호_중: strType = "부호(중)"; break; case 효과_부호_대: strType = "부호(대)"; break;
					case 효과_미도_소: strType = "미도(소)"; break; case 효과_미도_중: strType = "미도(중)"; break; case 효과_미도_대: strType = "미도(대)"; break;
					case 효과_명성_소: strType = "명성(소)"; break; case 효과_명성_중: strType = "명성(중)"; break; case 효과_명성_대: strType = "명성(대)"; break;
					case 효과_계략_기력_감소: strType = "계략기력감소"; break; case 효과_계략_크리티컬_항상성공: strType = "계략항상크리"; break; case 효과_공격_크리티컬_항상성공: strType = "공격항상크리"; break;
					case 효과_포박_불가: strType = "포박불가"; break; case 효과_기병_전법_사망_불가: strType = "전법사망불가"; break; case 효과_소병력_혼란_불가: strType = "소병력혼란불가"; break;
					case 효과_인접_교란: strType = "인접교란"; break; case 효과_인접_위보: strType = "인접위보"; break; case 효과_인접_화계: strType = "인접화계"; break;
					case 효과_통솔_상승_소: strType = "통솔(소)"; break; case 효과_통솔_상승_중: strType = "통솔(중)"; break; case 효과_통솔_상승_대: strType = "통솔(대)"; break;
					case 효과_무력_상승_소: strType = "무력(소)"; break; case 효과_무력_상승_중: strType = "무력(중)"; break; case 효과_무력_상승_대: strType = "무력(대)"; break;
					case 효과_지력_상승_소: strType = "지력(소)"; break; case 효과_지력_상승_중: strType = "지력(중)"; break; case 효과_지력_상승_대: strType = "지력(대)"; break;
					case 효과_정치_상승_소: strType = "정치(소)"; break; case 효과_정치_상승_중: strType = "정치(중)"; break; case 효과_정치_상승_대: strType = "정치(대)"; break;
					case 효과_매력_상승_소: strType = "매력(소)"; break; case 효과_매력_상승_중: strType = "매력(중)"; break; case 효과_매력_상승_대: strType = "매력(대)"; break;

					default:
						break;
					}
					if (str2 == "")
						str2 = strType;
					else
						str2 = str2 + " " + strType;

				}
				str = str + str2;
			}
			

			return str;
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


		///////////////////////////////////////////////
	}
	Main main;
}

