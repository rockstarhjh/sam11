/*
@만든이: 크래픽스
@Update: 2023.9.4,최초배포
@Update: 2023.9.5,컷인시 특수병과 표시 보이지 않도록 수정,다중 특수병과 겹치지 않도록 수정,특수병과위치 전법근처이
@Update: 2023.9.6,기병전법사망추가, 전법일기토추가, 경험치획득 추가, 공적추가
@Update: 2023.9.7,세이브,로드 버그수정, AI중복 병과지정 버그수정
*/
namespace 특수병과
{
	///////////유저 옵션 시작//////////////////////////////////////////////////////////////////////////
	const bool AI전법_사용 = false; //자꾸 다운될경우에 끄고 해보세요.AI전법사용이 좀 불안합니다.
	
	//기장인 하후돈에 기병병과외에는 주지 않는 기능입니다.
	//기마책사님 출진무장최적화의 재고무시를 사용하는 경우, 하후돈은 거의 기병으로만 나옵니다.
	//기병으로만 나오는데, 다른병과를 주면 낭비가 되는 꼴이지요. 그렇지 않은 경우는 false를 사용하세요.
	const bool AI특수병과배정_특기배제 = true;
	const int 전법_기력 = 25;
	const int 특수병과_배정_개수 = 3;
	const int 특수병과_추가_공격력 = 15;
	const int 특수병과_추가_방어력 = 15;
	const int 사마휘_병과_획득_확률 = 1;
	const int 전법_일기토_확률 = 5;
	
	const int 전법실패시_일반공격_확률 = 30;
	const int 전법실패시_일반공격_무데미지_확률 = 30;
	const int 전법실패시_반격만_확률 = 40;

	const int 저격_부상_확률 = 30;
	const int 대화시_화시_확률 = 60;
	const int 역습_혼란_확률 = 50;
	const int 폭풍시_확률 = 70;
	const int 무당비군_지원공격_확률 = 80;
	const int 청주병_추가공격_확률 = 30;
	const int 투척_화계_확률 = 60;
	const int 화염주_화계_확률 = 60;
	const int 도참_혼란_확률 = 70;
	const int 난도_혼란_확률 = 70;

	const int 멸파_공격_증가량 = 10; //1거리당 10%
	const int 멸파_공격_최대적용거리 = 5;//50% 까지
	const int 광폭_전법_증가량 = 5; //1거리당 5%

	const int 해번군_전법방어_추가 = 50;
	const int 등갑군_반격_추가 = 50;

	const int 연노전차_방어_디버프 = 20;
	const int 연노전차_이동력_추가 = 3;

	const int AI저격_실행확률 = 30;
	const int AI역습_실행확률 = 30;


	const bool 전체_전법_사용_테스트 = false;//전법확인용으로 필요한 경우 사용하시기 바랍니다.
	const bool 특수병과_전투중_변경_테스트 = false;
	const bool 콘솔_로그_표시 = true; //문제 대응시 대응할 수 있게 켜두세요.AI전법사용 로그가 콘솔창에 표시되는데, 많이 표시되지 않습니다.
	const bool 콘솔_로그_표시_세이브_로드 = true; //문제 대응시 대응할 수 있게 켜두세요.AI전법사용 로그가 콘솔창에 표시되는데, 많이 표시되지 않습니다.

	array<SpecialForceItem> 특수병과리스트 =
	{
		//특수병과 순서 바꾸시면 안됩니다.
		//특수병과아이디,아이템리스트,무장리스트,작위,최초소유자
		SpecialForceItem(특수병과_기병_백마의종,{}, {무장_공손찬}, 작위_없음,무장없음),
		SpecialForceItem(특수병과_기병_서량철기,{}, {무장_마등,무장_마초}, 작위_없음,무장없음),
		SpecialForceItem(특수병과_기병_호표기,{}, {무장_조휴,무장_조순,무장_조진}, 작위_없음,무장없음),
		SpecialForceItem(특수병과_기병_비웅경기,{}, {}, 작위_없음,무장_동탁),

		SpecialForceItem(특수병과_창병_청주병,{보물_의천검}, {}, 작위_없음,무장없음),
		SpecialForceItem(특수병과_창병_백이병,{보물_자웅일대검}, {}, 작위_없음,무장없음),
		SpecialForceItem(특수병과_창병_대극사,{}, {무장_원소}, 작위_주자사,무장없음),
		SpecialForceItem(특수병과_창병_선등열사,{}, {}, 작위_주목,무장없음),

		SpecialForceItem(특수병과_극병_단양병,{}, {}, 작위_없음,무장_원술),
		SpecialForceItem(특수병과_극병_해번군,{}, {}, 작위_없음,무장_한당),
		//SpecialForceItem(특수병과_극병_등갑군,{}, {}, 작위_없음,무장_고순),
		SpecialForceItem(특수병과_극병_등갑군,{}, {}, 작위_없음,무장_올돌골),
		SpecialForceItem(특수병과_극병_함진영,{}, {}, 작위_없음,무장_고순),

		SpecialForceItem(특수병과_노병_강노병,{}, {}, 작위_없음,무장_국의),
		SpecialForceItem(특수병과_노병_무당비군,{}, {}, 작위_없음,무장_왕평),
		SpecialForceItem(특수병과_노병_연노병,{보물_양유기의활}, {}, 작위_없음,무장없음),
		SpecialForceItem(특수병과_노병_오계만병,{}, {}, 작위_주자사,무장없음),
		SpecialForceItem(특수병과_노병_연노전차,{보물_이광의활}, {무장_황충}, 작위_주목,무장없음)
	};

	///////수정하지 마세요///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	const int 무장없음 = -1;
	int _elapsedDay = 0;
	array<ForceInfo> 세력리스트;


	const int 유닛_전법_근접공격 = 0;
	const int 유닛_전법_활공격 = 1;
	const int 유닛_전법_돌출 = 2;
	const int 유닛_전법_나선첨 = 3;
	const int 유닛_전법_이단첨 = 4;
	const int 유닛_전법_갈퀴 = 5;
	const int 유닛_전법_횡치 = 6;
	const int 유닛_전법_선풍 = 7;
	const int 유닛_전법_화시 = 8;
	const int 유닛_전법_관시 = 9;
	const int 유닛_전법_난사 = 10;
	const int 유닛_전법_돌격 = 11;
	const int 유닛_전법_돌파 = 12;
	const int 유닛_전법_돌진 = 13;
	const int 유닛_전법_화시_병기 = 14;
	const int 유닛_전법_파쇄_병기 = 15;
	const int 유닛_전법_방사_병기 = 16;
	const int 유닛_전법_투석_병기 = 17;
	const int 유닛_전법_근접공격_함선 = 18;
	const int 유닛_전법_활공격_함선 = 19;
	const int 유닛_전법_화시_함선 = 20;
	const int 유닛_전법_투석_함선 = 21;
	const int 유닛_전법_격돌_함선 = 22;
	const int 유닛_전법_나선첨당함 = 23;
	const int 유닛_전법_근접공격당함 = 24;
	const int 유닛_전법_일제공격당함 = 25;
	const int 유닛_전법_활공격당함 = 26;
	const int 유닛_전법_돌출_이단첨당함 = 27;
	const int 유닛_전법_돌격_돌진당함 = 28;
	const int 유닛_전법_돌격_돌출당함_1타겟 = 29;
	const int 유닛_전법_돌격_갈퀴당함 = 30;
	const int 유닛_전법_돌격_돌파당함 = 31;
	const int 유닛_전법_돌격_투석당함 = 32;

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


	const bool 크리티컬_원거리 = true;
	const bool 크리티컬_근접 = false;

	const int KEY = pk::hash("특수병과전쟁");

	class ForceInfo
	{
		array<SpecialForceApply@> applies;
		pk::force@ force;
		int numPersons = 0;
		int numApply = 0;

		void remove(SpecialForceItem@ it)
		{
			int index = -1;
			for (int i = 0; i < applies.length; i++)
			{
				SpecialForceApply@ sa = applies[i];
				if(sa.item.id != it.id)
					continue;
				index = i;
				break;
			}
			if(index!=-1)
				applies.removeAt(index);
		}
		void add(SpecialForceItem@ it)
		{
			SpecialForceApply sa;
			@sa.item = it;
			@sa.force = force;
			applies.insertLast(sa);
		}
	};

	class SpecialForceApply
	{
		SpecialForceItem@ item;
		pk::force@ force;
		pk::list<pk::person@> persons;
	};

	class SpecialForceItem
	{
		pk::list<pk::item@> items;
		pk::list<pk::person@> persons;
		pk::title@ title;
		int id;
		string name;
		int 병종;
		pk::person@ owner = null;
		pk::person@ firstOwner = null;
		pk::point ownerPos;

		array<ForceInfo@> currentForces;

		SpecialForceItem(){}
		SpecialForceItem(int id0, array<int> items0, array<int> persons0, int titleID,int owner0)
		{
			id = id0;
			for (int i = 0; i < items0.length; i++)
			{
				pk::item@ it = pk::get_item(items0[i]);
				if(it==null)
					continue;
				items.add(it);
			}
			for (int i = 0; i < persons0.length; i++)
			{
				pk::person@ it = pk::get_person(persons0[i]);
				if (it == null)
					continue;
				persons.add(it);
			}
			@title = titleID != 작위_없음 ? pk::get_title(titleID) : null;
			if (items0.length == 0 && persons0.length == 0 && titleID == 작위_없음 && owner0 != 무장없음)
			{
				@firstOwner = pk::get_person(owner0);
			}

			switch (id0)
			{
			case 특수병과_노병_강노병:		name = "강노병"; ;	병종 = 병종_노병; break;
			case 특수병과_노병_무당비군:	name = "무당비군"; 병종 = 병종_노병; break;
			case 특수병과_노병_연노병:		name = "연노병"; 병종 = 병종_노병; break;
			case 특수병과_노병_오계만병:	name = "오계만병"; 병종 = 병종_노병;break;
			case 특수병과_노병_연노전차:	name = "연노전차"; 병종 = 병종_노병;break;

			case 특수병과_창병_청주병:		name = "청주병"; 병종 = 병종_창병; break;
			case 특수병과_창병_백이병:		name = "백이병"; 병종 = 병종_창병; break;
			case 특수병과_창병_대극사:		name = "대극사"; 병종 = 병종_창병; break;
			case 특수병과_창병_선등열사:	name = "선등열사"; 병종 = 병종_창병; break;

			case 특수병과_극병_단양병:		name = "단양병"; 병종 = 병종_극병; break;
			case 특수병과_극병_해번군:		name = "해번군"; 병종 = 병종_극병; break;
			case 특수병과_극병_등갑군:		name = "등갑군"; 병종 = 병종_극병; break;
			case 특수병과_극병_함진영:		name = "함진영"; 병종 = 병종_극병; break;

			case 특수병과_기병_백마의종:		name = "백마의종"; 병종 = 병종_기병; break;
			case 특수병과_기병_서량철기:		name = "서량철기"; 병종 = 병종_기병; break;
			case 특수병과_기병_호표기:			name = "호표기"; 병종 = 병종_기병; break;
			case 특수병과_기병_비웅경기:		name = "비웅경기"; 병종 = 병종_기병; break;

			default:
				break;
			}
		}
	};



	class Main
	{
		pk::func209_t@ prev_callback_209부대공격;
		pk::func201_t@ prev_callback_201;
		pk::func202_t@ prev_callback_202전법성공;
		pk::func200_t@ prev_callback_200지원공격;
		pk::func210_t@ prev_callback_210;
		pk::func221_t@ prev_callback_221;
		pk::func222_t@ prev_callback_222;
		pk::func163_t@ prev_callback_163부대능력치;
		pk::func203_t@ prev_callback_203기병전법사망;

		
		Main()
		{
			@prev_callback_210 = cast<pk::func210_t@>(pk::get_func(210));
			@prev_callback_221 = cast<pk::func221_t@>(pk::get_func(221));
			@prev_callback_222 = cast<pk::func222_t@>(pk::get_func(222));
			@prev_callback_203기병전법사망 = cast<pk::func203_t@>(pk::get_func(203));


			@prev_callback_163부대능력치 = cast<pk::func163_t@>(pk::get_func(163));
			pk::reset_func(163);
			pk::set_func(163, pk::func163_t(callback163));

			@prev_callback_209부대공격 = cast<pk::func209_t@>(pk::get_func(209));
			pk::reset_func(209);
			pk::set_func(209, pk::func209_t(callback209));


			@prev_callback_200지원공격 = cast<pk::func200_t@>(pk::get_func(200));
			pk::reset_func(200);
			pk::set_func(200, pk::func200_t(callback200));

			@prev_callback_202전법성공 = cast<pk::func202_t@>(pk::get_func(202));
			pk::reset_func(202);
			pk::set_func(202, pk::func202_t(callback202));

			@prev_callback_201 = cast<pk::func201_t@>(pk::get_func(201));
			pk::reset_func(201);
			pk::set_func(201, pk::func201_t(callback201));


			pk::bind(102, pk::trigger102_t(onInit));
			pk::bind(105, pk::trigger105_t(saveData));
			pk::bind(107, pk::trigger107_t(onNewDay));
			pk::bind(174, pk::trigger174_t(부대행동완료));
			pk::bind(173, pk::trigger173_t(부대경험치));
			pk::bind(120, pk::trigger120_t(UpdatePerFrame));
			pk::bind(111, pk::trigger111_t(onTurn));


			int pos = 4;
			int pos2= 3;

			pk::menu_item item저격;
			item저격.menu = 1;
			item저격.pos = pos;
			item저격.init = pk::unit_menu_item_init_t(init);
			item저격.get_text = pk::menu_item_get_text_t(Get저격Text);
			item저격.get_desc = pk::menu_item_get_desc_t(Get저격Desc);
			item저격.is_visible = pk::menu_item_is_visible_t(IsVisible저격);
			item저격.get_targets = pk::unit_menu_item_get_targets_t(GetTargets저격);
			item저격.get_chance = pk::unit_menu_item_get_chance_t(GetChance저격);
			item저격.handler = pk::unit_menu_item_handler_t(저격Handler);
			pk::add_menu_item(item저격);
			

			pk::menu_item item대화시;
			item대화시.menu = 1;
			item대화시.pos = pos;
			item대화시.init = pk::unit_menu_item_init_t(init);
			item대화시.get_text = pk::menu_item_get_text_t(Get대화시Text);
			item대화시.get_desc = pk::menu_item_get_desc_t(Get대화시Desc);
			item대화시.is_visible = pk::menu_item_is_visible_t(IsVisible대화시);
			item대화시.get_targets = pk::unit_menu_item_get_targets_t(GetTargets대화시);
			item대화시.get_chance = pk::unit_menu_item_get_chance_t(GetChance대화시);
			item대화시.handler = pk::unit_menu_item_handler_t(대화시Handler);
			pk::add_menu_item(item대화시);

			pk::menu_item item역습;
			item역습.menu = 1;
			item역습.pos = pos;
			item역습.init = pk::unit_menu_item_init_t(init);
			item역습.get_text = pk::menu_item_get_text_t(Get역습Text);
			item역습.get_desc = pk::menu_item_get_desc_t(Get역습Desc);
			item역습.is_visible = pk::menu_item_is_visible_t(IsVisible역습);
			item역습.get_targets = pk::unit_menu_item_get_targets_t(GetTargets역습);
			item역습.get_chance = pk::unit_menu_item_get_chance_t(GetChance역습);
			item역습.handler = pk::unit_menu_item_handler_t(역습Handler);
			pk::add_menu_item(item역습);

			pk::menu_item item폭풍시;
			item폭풍시.menu = 1;
			item폭풍시.pos = pos2;
			item폭풍시.init = pk::unit_menu_item_init_t(init);
			item폭풍시.get_text = pk::menu_item_get_text_t(Get폭풍시Text);
			item폭풍시.get_desc = pk::menu_item_get_desc_t(Get폭풍시Desc);
			item폭풍시.is_visible = pk::menu_item_is_visible_t(IsVisible폭풍시);
			item폭풍시.get_targets = pk::unit_menu_item_get_targets_t(GetTargets폭풍시);
			item폭풍시.get_chance = pk::unit_menu_item_get_chance_t(GetChance폭풍시);
			item폭풍시.handler = pk::unit_menu_item_handler_t(폭풍시Handler);
			pk::add_menu_item(item폭풍시);

			pk::menu_item item극나선첨;
			item극나선첨.menu = 1;
			item극나선첨.pos = pos;
			item극나선첨.init = pk::unit_menu_item_init_t(init);
			item극나선첨.get_text = pk::menu_item_get_text_t(Get극나선첨Text);
			item극나선첨.get_desc = pk::menu_item_get_desc_t(Get극나선첨Desc);
			item극나선첨.is_visible = pk::menu_item_is_visible_t(IsVisible극나선첨);
			item극나선첨.get_targets = pk::unit_menu_item_get_targets_t(GetTargets극나선첨);
			item극나선첨.get_chance = pk::unit_menu_item_get_chance_t(GetChance극나선첨);
			item극나선첨.handler = pk::unit_menu_item_handler_t(극나선첨Handler);
			pk::add_menu_item(item극나선첨);

			pk::menu_item item무영참;
			item무영참.menu = 1;
			item무영참.pos = pos;
			item무영참.init = pk::unit_menu_item_init_t(init);
			item무영참.get_text = pk::menu_item_get_text_t(Get무영참Text);
			item무영참.get_desc = pk::menu_item_get_desc_t(Get무영참Desc);
			item무영참.is_visible = pk::menu_item_is_visible_t(IsVisible무영참);
			item무영참.get_targets = pk::unit_menu_item_get_targets_t(GetTargets무영참);
			item무영참.get_chance = pk::unit_menu_item_get_chance_t(GetChance무영참);
			item무영참.handler = pk::unit_menu_item_handler_t(무영참Handler);
			pk::add_menu_item(item무영참);

			pk::menu_item item화염주;
			item화염주.menu = 1;
			item화염주.pos = pos2;
			item화염주.init = pk::unit_menu_item_init_t(init);
			item화염주.get_text = pk::menu_item_get_text_t(Get화염주Text);
			item화염주.get_desc = pk::menu_item_get_desc_t(Get화염주Desc);
			item화염주.is_visible = pk::menu_item_is_visible_t(IsVisible화염주);
			item화염주.get_targets = pk::unit_menu_item_get_targets_t(GetTargets화염주);
			item화염주.get_chance = pk::unit_menu_item_get_chance_t(GetChance화염주);
			item화염주.handler = pk::unit_menu_item_handler_t(화염주Handler);
			pk::add_menu_item(item화염주);


			pk::menu_item item투척;
			item투척.menu = 1;
			item투척.pos = pos2;
			item투척.init = pk::unit_menu_item_init_t(init);
			item투척.get_text = pk::menu_item_get_text_t(Get투척Text);
			item투척.get_desc = pk::menu_item_get_desc_t(Get투척Desc);
			item투척.is_visible = pk::menu_item_is_visible_t(IsVisible투척);
			item투척.get_targets = pk::unit_menu_item_get_targets_t(GetTargets투척);
			item투척.get_chance = pk::unit_menu_item_get_chance_t(GetChance투척);
			item투척.handler = pk::unit_menu_item_handler_t(투척Handler);
			pk::add_menu_item(item투척);

			pk::menu_item item도참;
			item도참.menu = 1;
			item도참.pos = pos;
			item도참.init = pk::unit_menu_item_init_t(init);
			item도참.get_text = pk::menu_item_get_text_t(Get도참Text);
			item도참.get_desc = pk::menu_item_get_desc_t(Get도참Desc);
			item도참.is_visible = pk::menu_item_is_visible_t(IsVisible도참);
			item도참.get_targets = pk::unit_menu_item_get_targets_t(GetTargets도참);
			item도참.get_chance = pk::unit_menu_item_get_chance_t(GetChance도참);
			item도참.handler = pk::unit_menu_item_handler_t(도참Handler);
			pk::add_menu_item(item도참);


			pk::menu_item item멸파;
			item멸파.menu = 1;
			item멸파.pos = pos;
			item멸파.init = pk::unit_menu_item_init_t(init);
			item멸파.get_text = pk::menu_item_get_text_t(Get멸파Text);
			item멸파.get_desc = pk::menu_item_get_desc_t(Get멸파Desc);
			item멸파.is_visible = pk::menu_item_is_visible_t(IsVisible멸파);
			item멸파.get_targets = pk::unit_menu_item_get_targets_t(GetTargets멸파);
			item멸파.get_chance = pk::unit_menu_item_get_chance_t(GetChance멸파);
			item멸파.handler = pk::unit_menu_item_handler_t(멸파Handler);
			pk::add_menu_item(item멸파);


			pk::menu_item item난도;
			item난도.menu = 1;
			item난도.pos = pos;
			item난도.init = pk::unit_menu_item_init_t(init);
			item난도.get_text = pk::menu_item_get_text_t(Get난도Text);
			item난도.get_desc = pk::menu_item_get_desc_t(Get난도Desc);
			item난도.is_visible = pk::menu_item_is_visible_t(IsVisible난도);
			item난도.get_targets = pk::unit_menu_item_get_targets_t(GetTargets난도);
			item난도.get_chance = pk::unit_menu_item_get_chance_t(GetChance난도);
			item난도.handler = pk::unit_menu_item_handler_t(난도Handler);
			pk::add_menu_item(item난도);


			pk::menu_item item백마시;
			item백마시.menu = 1;
			item백마시.pos = pos;
			item백마시.init = pk::unit_menu_item_init_t(init);
			item백마시.get_text = pk::menu_item_get_text_t(Get백마시Text);
			item백마시.get_desc = pk::menu_item_get_desc_t(Get백마시Desc);
			item백마시.is_visible = pk::menu_item_is_visible_t(IsVisible백마시);
			item백마시.get_targets = pk::unit_menu_item_get_targets_t(GetTargets백마시);
			item백마시.get_chance = pk::unit_menu_item_get_chance_t(GetChance백마시);
			item백마시.handler = pk::unit_menu_item_handler_t(백마시Handler);
			pk::add_menu_item(item백마시);

			pk::menu_item item광폭;
			item광폭.menu = 1;
			item광폭.pos = pos;
			item광폭.init = pk::unit_menu_item_init_t(init);
			item광폭.get_text = pk::menu_item_get_text_t(Get광폭Text);
			item광폭.get_desc = pk::menu_item_get_desc_t(Get광폭Desc);
			item광폭.is_visible = pk::menu_item_is_visible_t(IsVisible광폭);
			item광폭.get_targets = pk::unit_menu_item_get_targets_t(GetTargets광폭);
			item광폭.get_chance = pk::unit_menu_item_get_chance_t(GetChance광폭);
			item광폭.handler = pk::unit_menu_item_handler_t(광폭Handler);
			pk::add_menu_item(item광폭);


			pk::menu_item item특수병과설정;
			item특수병과설정.menu = 101;
			item특수병과설정.pos = 18;
			item특수병과설정.init = pk::building_menu_item_init_t(특수병과설정Init);
			item특수병과설정.is_enabled = pk::menu_item_is_enabled_t(Is특수병과설정Enabled);
			item특수병과설정.get_text = pk::menu_item_get_text_t(Get특수병과설정Text);
			item특수병과설정.get_desc = pk::menu_item_get_desc_t(Get특수병과설정Desc);
			item특수병과설정.handler = pk::menu_item_handler_t(특수병과설정Handler);
			pk::add_menu_item(item특수병과설정);
		}
		bool loadData_old()
		{
			_elapsedDay = int(pk::load(KEY, 0, 0));
			int li = 1;
			int count = int(pk::load(KEY, li++, 0));
			pk::printf("sf old count0 : {}\n", count);
			for (int i = 0; i < count; i++)
			{
				SpecialForceItem@ sf = 특수병과리스트[i];
				int oid = int(pk::load(KEY, li++, -1));
				@sf.owner = oid != -1 ? pk::get_person(oid) : null;
				sf.ownerPos.x = int(pk::load(KEY, li++, 0));
				sf.ownerPos.y = int(pk::load(KEY, li++, 0));
				int count2 = int(pk::load(KEY, li++, 0));
				for (int j = 0; j < count2; j++)
				{
					int fid = int(pk::load(KEY, li++, 0));
					ForceInfo@ fi = getForce(fid);
					if (fi == null)
						continue;
					sf.currentForces.insertLast(fi);
				}
			}
			count = int(pk::load(KEY, li++, 0));
			pk::printf("fi old count1 : {}\n", count);
			for (int i = 0; i < count; i++)
			{
				ForceInfo@ fi = 세력리스트[i];
				if (콘솔_로그_표시_세이브_로드)
					pk::printf("fi {}\n", getName(fi.force));
				fi.numPersons = int(pk::load(KEY, li++, 0));
				fi.numApply = int(pk::load(KEY, li++, 0));
				for (int j = 0; j < fi.numApply; j++)
				{
					int id = int(pk::load(KEY, li++, -1));
					if (콘솔_로그_표시_세이브_로드)
						pk::printf("id li{},id{}\n", li - 1, id);
					SpecialForceItem@ sf = 특수병과리스트[id];

					SpecialForceApply sa;
					@sa.force = fi.force;
					@sa.item = sf;
					int count2 = int(pk::load(KEY, li++, -1));

					if (콘솔_로그_표시_세이브_로드)
						pk::printf("pcount li{},{}\n", li - 1, count2);
					for (int k = 0; k < count2; k++)
					{
						int mid = int(pk::load(KEY, li++, -1));
						pk::person@ p = mid != -1 ? pk::get_person(mid) : null;
						if (p == null)
							continue;

						sa.persons.add(p);
						if (콘솔_로그_표시_세이브_로드)
							pk::printf("pcount li{},{}", li - 1, getName(p));
						if (k == count2 - 1 && 콘솔_로그_표시_세이브_로드)
							pk::printf("\n");

					}
					fi.applies.insertLast(sa);
				}
			}

			return count > 0;
		}

		bool loadData_new()
		{
			_elapsedDay = int(pk::load(KEY, 1, 0));
			int li = 2;
			int count = int(pk::load(KEY, li++, 0));
			pk::printf("sf new count0 : {}\n", count);
			for (int i = 0; i < count; i++)
			{
				SpecialForceItem@ sf = 특수병과리스트[i];
				int oid = int(pk::load(KEY, li++, -1));
				@sf.owner = oid != -1 ? pk::get_person(oid) : null;
				sf.ownerPos.x = int(pk::load(KEY, li++, 0));
				sf.ownerPos.y = int(pk::load(KEY, li++, 0));
				int count2 = int(pk::load(KEY, li++, 0));
				for (int j = 0; j < count2; j++)
				{
					int fid = int(pk::load(KEY, li++, 0));
					ForceInfo@ fi = getForce(fid);
					if (fi == null)
						continue;
					sf.currentForces.insertLast(fi);
				}
			}
			count = int(pk::load(KEY, li++, 0));
			pk::printf("fi new count1 : {}\n", count);
			for (int i = 0; i < count; i++)
			{
				int fid = int(pk::load(KEY, li++, 0));
				ForceInfo@ fi = getForce(fid);
				if (fi == null) 
					@fi = ForceInfo();
				if (콘솔_로그_표시_세이브_로드)
					pk::printf("fi {}\n", getName(fi.force));
				fi.numPersons = int(pk::load(KEY, li++, 0));
				fi.numApply = int(pk::load(KEY, li++, 0));
				for (int j = 0; j < fi.numApply; j++)
				{
					int id = int(pk::load(KEY, li++, -1));
					if (콘솔_로그_표시_세이브_로드)
						pk::printf("id li{},id{}\n", li - 1, id);
					SpecialForceItem@ sf = 특수병과리스트[id];

					SpecialForceApply sa;
					@sa.force = fi.force;
					@sa.item = sf;
					int count2 = int(pk::load(KEY, li++, -1));

					if (콘솔_로그_표시_세이브_로드)
						pk::printf("pcount li{},{}\n", li - 1, count2);
					for (int k = 0; k < count2; k++)
					{
						int mid = int(pk::load(KEY, li++, -1));
						pk::person@ p = mid != -1 ? pk::get_person(mid) : null;
						if (p == null)
							continue;

						sa.persons.add(p);
						if (콘솔_로그_표시_세이브_로드)
							pk::printf("pcount li{},{}", li - 1, getName(p));
						if (k == count2 - 1 && 콘솔_로그_표시_세이브_로드)
							pk::printf("\n");

					}
					fi.applies.insertLast(sa);
				}
			}

			return count > 0;
		}

		bool loadData()
		{
			if (int(pk::load(KEY, 0, 0)) >= 0)
			{
				return loadData_old();
			}
			else
			{
				return loadData_new();
			}

		}
		void saveData(int file_id)
		{
			pk::store(KEY, 0, -1);
			pk::store(KEY, 1, _elapsedDay);
			int si = 2;
			
			pk::store(KEY, si++, 특수병과리스트.length);
			for (int i = 0; i < 특수병과리스트.length; i++)
			{
				SpecialForceItem@ sf = 특수병과리스트[i];
				pk::store(KEY, si++, sf.owner!=null ? sf.owner.get_id() : -1);
				pk::store(KEY, si++, int(sf.ownerPos.x));
				pk::store(KEY, si++, int(sf.ownerPos.y));

				int count2 = sf.currentForces.length;
				pk::store(KEY, si++, count2);
				for (int j = 0; j < count2; j++)
				{
					ForceInfo@ fi = sf.currentForces[j];
					pk::store(KEY, si++, fi!=null && fi.force!=null ? fi.force.get_id() : -1);
				}
			}
			pk::store(KEY, si++, 세력리스트.length);
			for (int i = 0; i < 세력리스트.length; i++)
			{
				ForceInfo@ fi = 세력리스트[i];
				pk::store(KEY, si++, fi.force!=null ? fi.force.get_id() : -1);
				if (fi != null)
				{
					pk::store(KEY, si++, fi.numPersons);
					pk::store(KEY, si++, fi.numApply);
				}
				else
				{
					pk::store(KEY, si++, 0);
					pk::store(KEY, si++, 0);
				}
				if(콘솔_로그_표시_세이브_로드)
					pk::printf("fi {}\n", getName(fi.force));

				for (int j = 0; j < fi.applies.length; j++)
				{
					SpecialForceApply@ sa = fi.applies[j];
					if (sa != null)
					{
						pk::store(KEY, si++, sa.item.id);
						pk::store(KEY, si++, sa.persons.count);
					}
					else 
					{
						pk::store(KEY, si++, -1);
						pk::store(KEY, si++, 0);
					}

					if (콘솔_로그_표시_세이브_로드)
						pk::printf("save si{},{},{}\n", si - 2, sa.item.id, sa.persons.count);
					for (int k = 0; k < sa.persons.count; k++)
					{
						if (콘솔_로그_표시_세이브_로드)
							pk::printf("save si{},{}", si, getName(sa.persons[k]));
						pk::store(KEY, si++, sa.persons[k]!=null ? sa.persons[k].get_id() : -1);
						if(k==sa.persons.count-1 && 콘솔_로그_표시_세이브_로드)
							pk::printf("\n");
					}
					
				}
			}
		}

		bool isSkill(pk::person@ f)
		{
			for (int i = 0; i < 특수병과리스트.length; i++)
			{
				SpecialForceItem@ sf = 특수병과리스트[i];
				if (isSkill(f, sf.id))
					return true;
			}
			return false;
		}

		bool isSkill(pk::person@ f, int type)
		{
			if (f == null)
				return false;
			SpecialForceItem@ sf = getForceItem(type);
			if (sf == null)
				return false;

			for (int i = 0; i < sf.currentForces.length; i++)
			{
				ForceInfo@ fi = sf.currentForces[i];
				if(fi==null)
					continue;
				if (fi.force.get_id() != f.get_force_id())
					continue;



				for (int j = 0; j < fi.applies.length; j++)
				{
					SpecialForceApply@ sa = fi.applies[j];
					if (sa.item.id != type)
						continue;
					//if (f.get_id() == 무장_여포)
					//	pk::printf("lubu {}\n", sa.item.id);
					for (int k = 0; k < sa.persons.count; k++)
					{
						//if (f.get_id() == 무장_여포)
						//	pk::printf("lubu {}\n", getName(sa.persons[k]));

						if (sa.persons[k].get_id() == f.get_id())
							return true;
						//if (sa.persons.contains(f))
							//return true;
					}
				}
			}
			return false;
		}
		bool isSkill(pk::force@ f, int type)
		{
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
		bool isSkill(pk::unit@ u)
		{
			for (int i = 0; i < 특수병과리스트.length; i++)
			{
				SpecialForceItem@ sf = 특수병과리스트[i];
				if (isSkill(u, sf.id))
					return true;
			}
			return false;
		}

		int getSkill(pk::unit@ u)
		{
			for (int i = 0; i < 특수병과리스트.length; i++)
			{
				SpecialForceItem@ sf = 특수병과리스트[i];
				if (isSkill(u, sf.id))
					return sf.id;
			}
			return -1;
		}
		

		SpecialForceItem@ getForceItem(int type)
		{
			return 특수병과리스트[type];
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
		int callback200(pk::unit@ assister, pk::unit@ attacker, pk::unit@ target)
		{
			if (isSkill(assister, 특수병과_노병_무당비군))
				return 무당비군_지원공격_확률;
			return prev_callback_200지원공격(assister, attacker, target);
		}
		void callback209(pk::damage_info& info, pk::unit@ attacker, int tactics_id, const pk::point& in target_pos, int type, int critical, bool ambush)
		{
			prev_callback_209부대공격(info,attacker, tactics_id, target_pos,type,critical,ambush);
			pk::unit@ u = getUnit(target_pos);
			if ((type ==1 || type ==2) && u != null && isSkill(u, 특수병과_극병_등갑군))
				info.troops_damage = info.troops_damage + info.troops_damage * 등갑군_반격_추가 / 100.0;

			if (isSkill(attacker)) 
				info.troops_damage = info.troops_damage + info.troops_damage * 특수병과_추가_공격력 / 100.0;
			if(u!=null && isSkill(u))
				info.troops_damage = info.troops_damage - info.troops_damage * 특수병과_추가_방어력 / 100.0;
		}
		int callback202(pk::unit@ attacker, const pk::point& in pos, pk::hex_object@ target, int tactics_id)
		{
			int n=prev_callback_202전법성공(attacker, pos, target, tactics_id);
			pk::unit@ u = getUnit(target.get_pos());
			if (u != null && isSkill(u, 특수병과_극병_해번군))
				n = pk::max(0,n - 해번군_전법방어_추가);
			return n;
		}

		bool _bCritical = false;
		bool callback201(pk::unit@ attacker, pk::hex_object@ target, int tactics_id, bool ranged)
		{
			bool b = prev_callback_201(attacker, target, tactics_id, ranged);
			_bCritical = b;
			return b;
		}
		void callback163(pk::unit_attr& attr, const pk::detail::arrayptr<pk::person@>& in member, int weapon_id, uint troops, int type, int status, bool navy, bool shoubyou)
		{
			prev_callback_163부대능력치(attr, member, weapon_id, troops, type, status, navy, shoubyou);

			pk::person@ leader = member[0];
			if (!pk::is_alive(leader))
				return;

			if (isSkill(leader, 특수병과_노병_연노전차) || isSkill(member[1], 특수병과_노병_연노전차) || isSkill(member[2], 특수병과_노병_연노전차))
			{
				attr.stat[부대능력_방어] = pk::max(0, attr.stat[부대능력_방어] - attr.stat[부대능력_방어] * 연노전차_방어_디버프 / 100.0);
				attr.stat[부대능력_이동] = attr.stat[부대능력_이동] + 연노전차_이동력_추가;
			}
		}

		void 부대경험치(pk::unit@ unit, int type)
		{
			//pk::person@ leader = pk::get_person(unit.leader);
			//pk::printf("exp {},type{},moo{},tong{},ki{},no{},kuk{}\n"
			//	, getNameLeader(unit), type, leader.stat_exp[무장능력_무력], leader.stat_exp[무장능력_통솔], leader.heishu_exp[병종_기병], leader.heishu_exp[병종_노병], leader.heishu_exp[병종_극병]);
		}

		void 부대행동완료(pk::unit@ unit)
		{
			_bCritical = false;
			if (!isSkill(unit, 특수병과_창병_청주병))
				return;

			for (int i = 0; i < 방향_끝; i++)
			{
				pk::point pt = pk::get_neighbor_pos(unit.get_pos(), i, 1);
				pk::unit@ u = getUnit(pt);
				if(u==null)
					continue;
				if(!pk::rand_bool(청주병_추가공격_확률))
					continue;
				if(!pk::is_enemy(unit,u))
					continue;
				
				//pk::say(pk::encode("이것이 청주병이다"), pk::get_person(unit.leader), unit);
				pk::damage_info di;
				di.src_pos = unit.get_pos();
				di.dst_pos = pt;
				callback209(di, unit, 전법_돌출, pt, 0, 0, false);
				bool bCri = callback201(unit, u, 전법_돌출, 크리티컬_근접);
				pk::unit_anim(unit, 유닛_전법_근접공격, {di}, pt, 0, getString("청주병"), 0);
				if (!금강불굴(di, u))
				{
					addTroops(u, di);
					updateAfter(unit, u);
					update(unit, pt, { di },false, bCri);
				}
			}
		}

		ForceInfo@ getForce(int id)
		{
			for (int i = 0; i < 세력리스트.length; i++)
			{
				ForceInfo@ fi = 세력리스트[i];
				if (fi.force.get_id()  == id)
					return fi;
			}
			return null;
		}

		ForceInfo@ getItemOwner(SpecialForceItem@ sf)
		{
			ForceInfo@ fi = null;
			for (int j = 0; j < sf.items.count; j++)
			{
				pk::item@ it = sf.items[j];
				if(it==null)
					continue;;
				pk::person@ p = pk::get_person(it.owner);
				if (p == null)
					continue;
				ForceInfo@ fi2 = getForce(p.get_force_id());
				if(fi2==null)
					continue;
				if (fi != null && fi.force.get_id() != fi2.force.get_id())
					return null;

				@fi = fi2;
			}
			return fi;
		}
		array<ForceInfo@> getPersonsOwner(SpecialForceItem@ sf)
		{
			array<ForceInfo@> arr;
			for (int i = 0; i < sf.persons.count; i++)
			{
				pk::person@ p = sf.persons[i];
				if(p==null)
					continue;

				ForceInfo@ fi2 = getForce(p.get_force_id());
				if(fi2==null)
					continue;
				
				if (arr.findByRef(fi2) == -1)
					arr.insertLast(fi2);
			}
			return arr;
		}
		array<ForceInfo@> getTitleOwner(SpecialForceItem@ sf)
		{
			array<ForceInfo@> arr;
			if (sf.title == null)
				return arr;

			pk::list<pk::force@> forces = pk::get_force_list();
			for (int i = 0; i < forces.count; i++)
			{
				pk::force@ f = forces[i];
				if (f.title <= sf.title.get_id()) 
				{
					ForceInfo@ fi = getForce(f.get_id());
					if(fi==null)
						continue;
					arr.insertLast(fi);
				}
			}
			return arr;
		}
		bool checkItem(SpecialForceItem@ sf, ForceInfo@ itemForce)
		{
			if (itemForce == null)
				return false;
			if (sf.items.count == 0)
				return true;
			return itemForce != null;
		}
		bool checkItem(SpecialForceItem@ sf, ForceInfo@ itemForce,ForceInfo@ other)
		{
			if (sf.items.count == 0)
				return true;

			if (itemForce != null && other != null && itemForce.force!=null && other.force!=null && itemForce.force.get_id() == other.force.get_id())
				return true;
			else if (itemForce == null && other != null)
				return true;
			else if (itemForce != null && other == null)
				return false;
			else 
				return false;
		}
		bool checkPersons(SpecialForceItem@ sf,array<ForceInfo@> arr, ForceInfo@ fi0)
		{
			if (sf.persons.count == 0)
				return true;

			return arr.findByRef(fi0) >= 0;
		}
		bool checkTitle(SpecialForceItem@ sf,array<ForceInfo@> arr,ForceInfo@ fi0)
		{
			if (sf.title == null)
				return true;

			for (int i = 0; i < arr.length; i++)
			{
				ForceInfo@ fi = arr[i];
				if (fi.force.get_id() == fi0.force.get_id())
					return true;
			}
			return false;
		}
		bool checkTitle(SpecialForceItem@ sf, array<ForceInfo@> arr, array<ForceInfo@> arrPersons)
		{
			if (sf.title == null)
				return true;
			if (arr.length == 0)
				return false;

			for (int i = 0; i < arrPersons.length; i++)
			{
				ForceInfo@ fi = arrPersons[i];
				if (arr.findByRef(fi) >= 0)
					return true;
			}
			return false;
		}
		void create세력리스트()
		{
			while (세력리스트.length > 0)
				세력리스트.removeLast();
			pk::list<pk::force@> forces = pk::get_force_list();
			for (int i = 0; i < forces.count; i++)
			{
				pk::force@ f = forces[i];

				ForceInfo fi;
				@fi.force = f;
				세력리스트.insertLast(fi);
			}
		}
		void update특수병과()
		{
			if (_elapsedDay == 0)
			{
				for (int i = 0; i < 특수병과리스트.length; i++)
				{
					SpecialForceItem@ sf = 특수병과리스트[i];
					@sf.owner = sf.firstOwner;
				}
				_elapsedDay++;
			}
			
			for (int i = 0; i < 특수병과리스트.length; i++)
			{
				SpecialForceItem@ sf = 특수병과리스트[i];
				array<ForceInfo@> currentForces;

				ForceInfo@ forceItem = getItemOwner(sf);
				array<ForceInfo@> forcePersosns = getPersonsOwner(sf);
				array<ForceInfo@> forceTitles = getTitleOwner(sf);
				if (checkItem(sf,forceItem) && checkPersons(sf,forcePersosns, forceItem) && checkTitle(sf, forceTitles, forceItem))
				{
					currentForces.insertLast(forceItem);
				}
				for (int j = 0; j < forcePersosns.length; j++)
				{
					ForceInfo@ fi = forcePersosns[j];
					if(fi==null)
						continue;
					if (checkItem(sf, forceItem, fi) && checkTitle(sf, forceTitles, fi)) 
					{
						if (currentForces.findByRef(fi) == -1)
							currentForces.insertLast(fi);
					}
				}
				for (int j = 0; j < forceTitles.length; j++)
				{
					ForceInfo@ fi = forceTitles[j];
					if (fi == null)
						continue;

					if (checkItem(sf, forceItem, fi) && checkPersons(sf, forcePersosns, fi))
					{
						if (currentForces.findByRef(fi) == -1)
							currentForces.insertLast(fi);
					}
				}
				if (sf.owner != null && forceItem==null && forcePersosns.length == 0 && forceTitles.length == 0)  
				{
					ForceInfo@ fi = getForce(sf.owner.get_force_id());
					if (currentForces.findByRef(fi) == -1)
						currentForces.insertLast(fi);
				}

				if (currentForces.length > 0)
				{
					currentForces.sort(function(a, b) 
					{
						return a.force.get_id() < b.force.get_id();
					});
				}
				if (sf.currentForces.length > 0)
				{
					sf.currentForces.sort(function(a, b)
					{
						return a.force.get_id() < b.force.get_id();
					});
				}

				for (int j = 0; j < sf.currentForces.length; j++)
				{
					ForceInfo@ fi0 = sf.currentForces[j];
					if(fi0==null)
						continue;
					bool bFound = false;
					for (int k = 0; k < currentForces.length; k++)
					{
						ForceInfo@ fi1 = currentForces[k];
						if(fi1==null)
							continue;
						if(fi0.force==null || fi1.force==null || fi0.force.get_id() != fi1.force.get_id())
							continue;
						bFound = true;
						break;
					}
					if (!bFound) 
					{
						pk::person@ kunshu = pk::get_person(fi0.force.kunshu);
						string str = pk::format("\x1b[2x{}군\x1b[0x, \x1b[29x{}\x1b[0x 상실", getName(kunshu), sf.name);
						pk::history_log(kunshu !=null ? kunshu.get_pos() : pk::point(0,0), fi0.force.color, pk::encode(str));
						fi0.remove(sf);
					}
				}

				for (int j = 0; j < currentForces.length; j++)
				{
					ForceInfo@ fi0 = currentForces[j];
					if(fi0 == null)
						continue;
					bool bFound = false;
					for (int k = 0; k < sf.currentForces.length; k++)
					{
						ForceInfo@ fi1 = sf.currentForces[k];
						if(fi1 == null)
							continue;
						if (fi0.force.get_id() != fi1.force.get_id())
							continue;
						bFound = true;
						break;
					}
					if (!bFound)
					{
						pk::person@ kunshu = pk::get_person(fi0.force.kunshu);
						string str = pk::format("\x1b[2x{}군\x1b[0x,\x1b[1x{}\x1b[0x 획득", getName(kunshu), sf.name);
						pk::history_log(kunshu!=null ? kunshu.get_pos() : pk::point(), fi0.force.color, pk::encode(str));
						fi0.add(sf);
					}
				}
				if (sf.owner != null)
					sf.ownerPos = sf.owner.get_pos();
				sf.currentForces = currentForces;
			}

		}

		bool 특기체크(pk::person@ p, array<int> arr)
		{
			for (int i = 0; i < arr.length; i++)
			{
				if (pk::has_skill(p, arr[i]))
					return true;
			}
			return false;
		}

		bool 특기제외(SpecialForceApply@ sa,pk::person@ p)
		{
			switch (sa.item.병종)
			{
			case 병종_노병:
				if (특기체크(p, { 특기_신장,특기_용장,특기_패왕,특기_궁신,특기_궁장 }))
					return true;
				if (특기체크(p, { 특기_기신,특기_기장,특기_창신,특기_창장,특기_극신,특기_극장,특기_공성,특기_공신,
					특기_투신,특기_도주,특기_비장,특기_질주,특기_맹장,특기_심공,특기_백마,특기_행군}))
					return false;
				return true;
			case 병종_기병:
				if (특기체크(p, { 특기_신장,특기_용장,특기_패왕,특기_질주,특기_백마,특기_기신,특기_기장 }))
					return true;
				if (특기체크(p, { 특기_궁신,특기_궁장,특기_창신,특기_창장,특기_극신,특기_극장,특기_공성,특기_공신,특기_투신}))
					return false;
				return true;
			case 병종_극병:
				if (특기체크(p, { 특기_신장,특기_용장,특기_극신,특기_극장,특기_비장,특기_도주,특기_패왕,특기_투신 }))
					return true;
				if (특기체크(p, { 특기_궁신,특기_궁장,특기_창신,특기_창장,특기_기신,특기_기장,특기_공성,특기_공신,특기_백마,특기_질주,특기_행군,특기_사수}))
					return false;
				return true;
			case 병종_창병:
				if (특기체크(p, { 특기_신장,특기_용장,특기_패왕,특기_투신 ,특기_창신,특기_창장}))
					return true;
				if (특기체크(p, { 특기_궁신,특기_궁장,특기_극신,특기_창장,특기_기신,특기_기장,특기_공성,특기_공신,특기_백마,특기_질주,특기_행군,특기_사수 }))
					return false;
				return true;

			default:
				break;
			}
			return true;
		}

		pk::list<pk::person@> AI특수병과배정Sort(SpecialForceApply@ sa, pk::list<pk::person@> persons0)
		{
			pk::list<pk::person@> persons;
			if (AI특수병과배정_특기배제)
			{
				for (int i = 0; i < persons0.count; i++)
				{
					if (!특기제외(sa, persons0[i]))
						continue;
					persons.add(persons0[i]);
				}
			}
			else 
			{
				persons = persons0;
			}
			
			switch (sa.item.병종)
			{
			case 병종_노병:
				persons.sort(function(a, b)
				{
					if (a.tekisei[병종_노병] != b.tekisei[병종_노병])
						return a.tekisei[병종_노병] > b.tekisei[병종_노병];
					if (a.stat[무장능력_통솔] + a.stat[무장능력_무력] != b.stat[무장능력_통솔] + b.stat[무장능력_무력])
						return a.stat[무장능력_통솔] + a.stat[무장능력_무력] > b.stat[무장능력_통솔] + b.stat[무장능력_무력];
					return true;
				});
				break;
			case 병종_창병:
				persons.sort(function(a, b)
				{
					if (a.tekisei[병종_창병] != b.tekisei[병종_창병])
						return a.tekisei[병종_창병] > b.tekisei[병종_창병];
					if (a.stat[무장능력_통솔] + a.stat[무장능력_무력] != b.stat[무장능력_통솔] + b.stat[무장능력_무력])
						return a.stat[무장능력_통솔] + a.stat[무장능력_무력] > b.stat[무장능력_통솔] + b.stat[무장능력_무력];
					return true;
				});
				break;
			case 병종_극병:
				persons.sort(function(a, b)
				{
					if (a.tekisei[병종_극병] != b.tekisei[병종_극병])
						return a.tekisei[병종_극병] > b.tekisei[병종_극병];
					if (a.stat[무장능력_통솔] + a.stat[무장능력_무력] != b.stat[무장능력_통솔] + b.stat[무장능력_무력])
						return a.stat[무장능력_통솔] + a.stat[무장능력_무력] > b.stat[무장능력_통솔] + b.stat[무장능력_무력];
					return true;
				});
				break;
			case 병종_기병:
				persons.sort(function(a, b)
				{
					if (a.tekisei[병종_기병] != b.tekisei[병종_기병])
						return a.tekisei[병종_기병] > b.tekisei[병종_기병];
					if (a.stat[무장능력_통솔] + a.stat[무장능력_무력] != b.stat[무장능력_통솔] + b.stat[무장능력_무력])
						return a.stat[무장능력_통솔] + a.stat[무장능력_무력] > b.stat[무장능력_통솔] + b.stat[무장능력_무력];
					return true;
				});
				break;

			default:
				break;
			}

			return persons;
		}

		void AI특수병과배정(SpecialForceApply@ sa, pk::list<pk::person@> persons, int count)
		{
			persons=AI특수병과배정Sort(sa, persons);

			pk::list<pk::person@> personsNew;
			for (int i = 0; i < persons.count; i++)
			{
				pk::person@ p = persons[i];
				if(isSkill(p,sa.item.id))
					continue;

				personsNew.add(p);
				if (personsNew.count >= count)
					break;
			}
			sa.persons = personsNew;
		}
		void AI특수병과배정Add(SpecialForceApply@ sa, pk::list<pk::person@> persons, int count)
		{
			persons=AI특수병과배정Sort(sa, persons);

			pk::list<pk::person@> personsNew;
			for (int i = 0; i < persons.count; i++)
			{
				pk::person@ p = persons[i];
				if(isSkill(p))
					continue;

				personsNew.add(p);
				if (personsNew.count >= count)
					break;
			}

			for (int i = 0; i < personsNew.count; i++)
			{
				sa.persons.add(personsNew[i]);
			}
		}

		void AI특수병과배정()
		{
			for (int i = 0; i < 세력리스트.length; i++)
			{
				ForceInfo@ fi = 세력리스트[i];
				if (fi.applies.length == 0 || fi.force.is_player()) 
				{
					fi.numApply = fi.applies.length;
					continue;
				}
					

				pk::list<pk::person@> persons = pk::get_person_list(fi.force, pk::mibun_flags(신분_군주,신분_도독,신분_태수,신분_일반));
				if(fi.numPersons == persons.count && fi.numApply == fi.applies.length)
					continue;
				fi.numPersons = persons.count;
				fi.numApply = fi.applies.length;
				//pk::printf("apply {}\n", getName(fi.force));
				for (int j = 0;  j < fi.applies.length;  j++)
				{
					SpecialForceApply@ sa = fi.applies[j];
					AI특수병과배정(sa, persons, 특수병과_배정_개수);
				}
			}
		}
		void AI특수병과배정2()
		{
			for (int i = 0; i < 세력리스트.length; i++)
			{
				ForceInfo@ fi = 세력리스트[i];
				if (fi.applies.length == 0 || fi.force.is_player())
				{
					fi.numApply = fi.applies.length;
					continue;
				}


				pk::list<pk::person@> persons = pk::get_person_list(fi.force, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반));
				//if (fi.numPersons == persons.count && fi.numApply == fi.applies.length)
				//	continue;
				fi.numPersons = persons.count;
				fi.numApply = fi.applies.length;

				for (int j = 0; j < fi.applies.length; j++)
				{
					SpecialForceApply@ sa = fi.applies[j];
					//sa.persons = {};
					sa.persons.clear();
				}
				
				for (int k = 0; k < 특수병과_배정_개수; k++)
				{
					for (int j = 0; j < fi.applies.length; j++)
					{
						SpecialForceApply@ sa = fi.applies[j];
						AI특수병과배정Add(sa, persons,1);
					}
				}

			}
		}

		void 포로처리()
		{
			for (int i = 0; i < 특수병과리스트.length; i++)
			{
				SpecialForceItem@ sf = 특수병과리스트[i];
				if (sf.owner == null) 
					continue;
				if (sf.owner.mibun != 신분_포로) 
					continue;

				pk::unit@ obj= getUnit(sf.owner.get_pos());
				if(obj==null)
					continue;
				pk::force@ force = pk::get_force(obj.get_force_id());
				if(force == null)
					continue;
				pk::person@ person = pk::get_person(force.kunshu);
				if(person==null)
					continue;
				//pk::printf("poro {}->{}\n", getName(sf.owner), getName(person));
				@sf.owner = person;
			}
		}
		void 사망처리()
		{
			for (int i = 0; i < 특수병과리스트.length; i++)
			{
				SpecialForceItem@ sf = 특수병과리스트[i];
				if (sf.owner == null)
					continue;
				if (sf.owner.mibun != 신분_사망)
					continue;

				int minDistance = 10000;
				pk::force@ minForce = null;
				for (int j = 0; j < 무장_끝; j++)
				{
					pk::person@ p = pk::get_person(j);
					if(p==null)
						continue;
					pk::force@ force = pk::get_force(p.get_force_id());
					if(force==null || force.get_id () == sf.owner.get_force_id())
						continue;

					int dist = pk::get_distance(p.get_pos(), sf.ownerPos);
					if (dist < minDistance)
					{
						minDistance = dist;
						@minForce = force;
					}
				}

				if(minForce == null)
					continue;
				pk::person@ person = pk::get_person(minForce.kunshu);
				if (person == null)
					continue;
				//pk::printf("die {}->{}\n", getName(sf.owner), getName(person));
				@sf.owner = person;
			}
		}

		void onInit()
		{
			create세력리스트();
			for (int i = 0; i < 특수병과리스트.length; i++)
			{
				특수병과리스트[i].currentForces = {};
				@특수병과리스트[i].owner = null;
			}
			if (!loadData())
			{
				update특수병과();
				AI특수병과배정2();
			}
		}
		void onNewDay()
		{
			포로처리();
			사망처리();
			사마휘병과획득();
			update특수병과();
			AI특수병과배정2();
			_elapsedDay++;
		}
		void onTurn(pk::force@ force)
		{
			AI전법사용(force);
		}

		void UpdatePerFrame()
		{
			if (_bCritical)
				return;
			for (int i = 0; i < 세력리스트.length; i++)
			{
				ForceInfo@ fi = 세력리스트[i];

				array<pk::unit@> units;
				for (int j = 0; j < fi.applies.length; j++)
				{
					SpecialForceApply@ sa = fi.applies[j];
					if(sa==null)
						continue;
					for (int k = 0; k < sa.persons.count; k++)
					{
						pk::person@ p = sa.persons[k];
						pk::unit@ u = getUnit(p.get_pos());
						if (u == null)
							continue;
						if (!check병종(u, sa.item.병종))
							continue;

						if(units.findByRef(u)==-1)
							units.insertLast(u);
					}//k
				}//j

				for (int j = 0; j < units.length; j++)
				{
					pk::unit@ u = units[j];
					string str = "";
					for (int k = 0; k < 특수병과리스트.length; k++)
					{
						SpecialForceItem sf = 특수병과리스트[k];
						if (!isSkill(u, k)) 
						{
							//pk::printf("isskill return{}\n", getNameLeader(u));
							continue;
						}
							
						if(str == "")
							str = str + pk::format("\x1b[1x{}\x1b[0x", sf.name);
						else
							str = str + pk::format("\x1b[1x {}\x1b[0x", sf.name);
					}
					pk::point point = pk::hex_pos_to_screen_pos(u.get_pos());
					pk::draw_text(pk::encode(str), point);
					pk::size size0 = pk::get_size(FONT_SMALL, str);
					pk::rectangle r0(point, size0);
					pk::draw_filled_rect(r0, 0x40000000);
				}

			}//i
		}
		void 사마휘병과획득()
		{
			SpecialForceItem@ item = null;
			for (int i = 0; i < 특수병과리스트.length; i++)
			{
				SpecialForceItem@ sf = 특수병과리스트[i];
				//pk::printf("sf {},len{},item{},persons{},title{},onwer:{}\n", sf.name, sf.currentForces.length, sf.items.count, sf.persons.count,getName(sf.title),getName(sf.owner));
				if(sf.currentForces.length != 0)
					continue;
				if(sf.items.count!=0 || sf.persons.count!=0 || sf.title!=null || sf.owner!=null)
					continue;
				if(!pk::rand_bool(사마휘_병과_획득_확률))
					continue;
				@item = sf;
				break;
			}
			if (item == null)
				return;

			pk::list<pk::force@> forces = pk::get_force_list();
			forces.shuffle();
			while (!forces[0].is_player())
				forces.remove_at(0);

			pk::person@ kunshu = pk::get_person(forces[0].kunshu);
			if (kunshu == null)
				return;
			@item.owner = kunshu;
			if (forces[0].is_player())
			{
				string str = pk::format("\x1b[2x{}\x1b[0x를 주겠네. 백성들을 이롭게 하는데 사용하게나.",item.name);
				pk::message_box(pk::encode(str), pk::get_person(무장_사마휘));
			}

			string str2 = pk::format("\x1b[2x{}군\x1b[0x,\x1b[2x{}\x1b[0x 사마휘로부터 획득",getName(forces[0]), item.name);
			pk::history_log(kunshu.get_pos(), forces[0].color, pk::encode(str2));
		}
		/////////////////////////특수병과설정 메뉴


		pk::force@ _force;
		pk::building@ _building;
		pk::district@ _district;
		void 특수병과설정Init(pk::building@ building)
		{
			@_force = pk::get_force(building.get_force_id());
			@_building = building;
		}
		bool Is특수병과설정Enabled()
		{
			return true;
		}
		string Get특수병과설정Text()
		{
			return pk::encode("특수병과설정");
		}
		string Get특수병과설정Desc()
		{
			return pk::encode("특수병과를 설정합니다.");
		}


		void select(SpecialForceApply@ sa)
		{
			pk::list<pk::person@> persons0 = pk::get_person_list(_force, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반));
			pk::list<pk::person@> persons;
			for (int i = 0; i < persons0.count; i++)
			{
				pk::person@ p = persons0[i];
				for (int j = 0; j < sa.persons.count; j++)
				{
					if (p.get_id() == sa.persons[j].get_id())
					{
						persons.add(p);
						break;
					}
				}
			}

			ForceInfo@ fi = getForce(sa.force.get_id());
			for (int i = 0; i < persons0.count; i++)
			{
				pk::person@ p = persons0[i];
				bool bFound = false;
				for (int j = 0; j < persons.count; j++)
				{
					if (p.get_id() == persons[j].get_id())
					{
						bFound = true;
						break;
					}
				}
				if(bFound)
					continue;

				for (int i = 0; i < fi.applies.length; i++)
				{
					SpecialForceApply@ sa2 = fi.applies[i];
					if (sa2.item.id == sa.item.id)
						continue;
					if (sa2.persons.contains(p))
					{
						bFound = true;
						break;
					}
				}
				if (bFound)
					continue;
				if(!특수병과_전투중_변경_테스트 && pk::is_unitize(p))
					continue;

				persons.add(p);
			}

			pk::list<pk::person@> newPersons = pk::person_selector(pk::encode("무장 선택"), pk::encode("특수병과를 배정할 무장을 선택하십시오"), persons, 0, 특수병과_배정_개수, sa.persons);
			sa.persons = newPersons;
		}

		bool 특수병과설정Handler()
		{
			array<SpecialForceApply@> sfs;
			for (int i = 0; i < 세력리스트.length; i++)
			{
				ForceInfo@ fi = 세력리스트[i];
				for (int j = 0; j < fi.applies.length; j++)
					sfs.insertLast(fi.applies[j]);
			}

			if (sfs.length > 1) 
			{
				sfs.sort(function(a, b)
				{
					bool b0 = a.force.is_player();
					bool b1 = b.force.is_player();
					if (b0 == b1)
						return true;
					else if (b0 && !b1)
						return true;
					else if (!b0 && b0)
						return false;
					else
						return false;
				});
			}

			int si = 0;
			SpecialForceApply@ selected = null;
			while (true)
			{
				array<string> itemArr;
				array<SpecialForceApply@> itemArr2;
				int count = pk::min(sfs.length, si + 4);
				if (si == 0)
					itemArr.insertLast(pk::encode("종료"));
				else
					itemArr.insertLast(pk::encode("뒤로"));
				for (int i = si; i < count; i++)
				{
					SpecialForceApply@ sa = sfs[i];
					string str = "";
					if (sa.persons.count == 0) 
					{
						str = pk::format("{},{}군,없음", sa.item.name, getName(sa.force));
					}
					else 
					{
						string str0 = "";
						for (int j = 0; j < sa.persons.count; j++)
						{
							if (j != sa.persons.count - 1)
								str0 = str0 + pk::format("{}", getName(sa.persons[j])) + ",";
							else
								str0 = str0 + pk::format("{}", getName(sa.persons[j]));
						}
						str = pk::format("{},{}군,{}", sa.item.name, getName(sa.force), str0);
					}
					
					itemArr.insertLast(pk::encode(str));
					itemArr2.insertLast(sa);
				}
				if (si + 4 >= sfs.length)
					itemArr.insertLast(pk::encode("종료"));
				else
					itemArr.insertLast(pk::encode("다음"));

				int choose = pk::choose(pk::encode("선택해주십시오"), itemArr);
				if (choose == itemArr.length - 1)
				{
					si = si + 4;
					if (si >= sfs.length)
						break;
				}
				else if (choose == 0)
				{
					si = si - 4;
					if (si < 0)
						break;
				}
				else
				{
					@selected = itemArr2[choose - 1];
				}
				if (selected == null)
					continue;

				if (selected.force.get_id() != _force.get_id()) 
				{
					pk::message_box(pk::encode("타세력은 설정할 수 없습니다."));
					@selected = null;
					continue;
				}
				select(selected);
				@selected = null;
			}


			return true;
		}
		///////////////////////////////////AI전법사용

		bool AI전법사용_강노병_저격(pk::unit@ u)
		{
			//강력한적을 찾아 발사
			if (!pk::rand_bool(AI저격_실행확률))
				return false;
			
			int dist = getMaxAttackDistance(u)+1;
			//int dist = 3;
			int minDist = 2;
			int curDist = 2;

			int maxAttack = 0;
			pk::unit@ maxUnit = null;
			pk::point maxPos;

			array<pk::point> arr = pk::get_movable_pos(u);
			for (int i0 = 0; i0 < arr.length; i0++)
			{
				pk::point pt0 = arr[i0];
				if (!pk::is_in_screen(pt0))
					continue;

				while (curDist <= dist)
				{
					for (int i = 0; i < 방향_끝; i++)
					{
						pk::point pt = pk::get_neighbor_pos(pt0, i, curDist);
						pk::unit@ unit = getUnit(pt);
						if (unit == null || !pk::is_enemy(u, unit))
							continue;
						if (!checkHex노병(u, pt))
							continue;

						if (unit.attr.stat[부대능력_공격] > maxAttack)
						{
							maxAttack = unit.attr.stat[부대능력_공격];
							@maxUnit = unit;
							maxPos = pt0;
						}
					}
					curDist++;
				}
			}

			if (maxUnit == null)
				return false;

			if(콘솔_로그_표시)
				pk::printf("sniper start{}->{}\n",getNameLeader(u), getNameLeader(maxUnit));
			pk::move(u, { maxPos });
			execute저격(u, maxUnit.get_pos());
			if (콘솔_로그_표시)
				pk::printf("sniper end{}->{}\n", getNameLeader(u), getNameLeader(maxUnit));

			return true;
		}
		bool AI전법사용_연노병_대화시(pk::unit@ u)
		{
			//3명이상되면 발사
			int dist = getMaxAttackDistance(u);
			//int dist = 2;
			int minDist = 2;
			int curDist = 2;
			bool b궁신 = u.has_skill(특기_궁신);
			
			array<pk::point> arr = pk::get_movable_pos(u);
			for (int i0 = 0; i0 < arr.length; i0++)
			{
				pk::point pt0 = arr[i0];
				if (!pk::is_in_screen(pt0))
					continue;

				while (curDist <= dist)
				{
					for (int i = 0; i < 방향_끝; i++)
					{
						pk::point pt = pk::get_neighbor_pos(pt0, i, curDist);
						pk::unit@ unit = getUnit(pt);
						if (unit == null || !pk::is_enemy(u, unit))
							continue;
						if (!checkHex노병(u, pt))
							continue;

						int acount = 0;
						bool bMine = false;
						array<pk::point> arr = pk::range(pt, 1, 1);
						for (int j = 0; j < arr.length; j++)
						{
							pk::point pt2 = arr[j];
							pk::unit@ unit2 = getUnit(pt2);
							if (unit2 == null)
								continue;
							if (!checkHex노병(u, pt2))
								continue;

							if (!b궁신 && !pk::is_enemy(u, unit2))
							{
								bMine = true;
								break;
							}
							acount++;
						}
						if (bMine || acount < 3)
							continue;

						if (콘솔_로그_표시)
							pk::printf("greate fire start{} -> {}\n", getNameLeader(u), getNameLeader(unit));
						pk::move(u, { pt0 });
						execute대화시(u, pt);
						if (콘솔_로그_표시)
							pk::printf("greate fire end{} -> {}\n", getNameLeader(u), getNameLeader(unit));
						return true;

					}
					curDist++;
				}
			}


			return false;
		}
		bool AI전법사용_오계만병_역습(pk::unit@ u)
		{
			if (!pk::rand_bool(AI역습_실행확률))
				return false;

			int maxAttack = 0;
			pk::unit@ maxUnit = null;
			pk::point maxPos;

			array<pk::point> arr = pk::get_movable_pos(u);
			for (int i0 = 0; i0 < arr.length; i0++)
			{
				pk::point pt0 = arr[i0];
				if (!pk::is_in_screen(pt0))
					continue;

				for (int i = 0; i < 방향_끝; i++)
				{
					pk::point pt = pk::get_neighbor_pos(pt0, i, 1);
					pk::unit@ unit = getUnit(pt);
					if (unit == null || !pk::is_enemy(u, unit))
						continue;

					if (unit.attr.stat[부대능력_공격] > maxAttack)
					{
						maxPos = pt0;
						maxAttack = unit.attr.stat[부대능력_공격];
						@maxUnit = unit;
					}
				}
			}

			if (maxUnit == null)
				return false;

			if (콘솔_로그_표시)
				pk::printf("counter attack start {} -> {}\n", getNameLeader(u), getNameLeader(maxUnit));
			pk::move(u, { maxPos });
			execute역습(u, maxUnit.get_pos());
			if (콘솔_로그_표시)
				pk::printf("counter attack end {} -> {}\n", getNameLeader(u), getNameLeader(maxUnit));
			return true;
		}
		bool AI전법사용_연노전차_폭풍시(pk::unit@ u)
		{
			int dist = getMaxAttackDistance(u);
			bool b궁신 = u.has_skill(특기_궁신);

			array<pk::point> arr = pk::get_movable_pos(u);
			for (int i0 = 0; i0 < arr.length; i0++)
			{
				pk::point pt0 = arr[i0];
				if (!pk::is_in_screen(pt0))
					continue;

				array<pk::point> range = pk::range(pt0, 2, dist);
				for (int i = 0; i < range.length; i++)
				{
					pk::point pt = range[i];
					array<pk::point> range2 = pk::range(pt, 0, 2);
					int acount = 0;
					bool bMine = false;

					pk::unit@ unit = pk::get_unit(pt);
					if (unit == null)
						continue;
					if (!pk::is_enemy(u, unit))
						continue;
					if (!checkHex노병(u, pt))
						continue;

					for (int j = 0; j < range2.length; j++)
					{
						pk::point pt2 = range2[j];
						pk::unit@ unit2 = getUnit(pt2);
						if (unit2 == null)
							continue;
						if (!checkHex노병(u, pt2))
							continue;

						if (!b궁신 && !pk::is_enemy(u, unit2))
						{
							bMine = true;
							break;
						}
						acount++;
					}

					if (bMine || acount < 3)
						continue;

					if(콘솔_로그_표시)
						pk::printf("storm start {}->{}\n", getNameLeader(u), getNameLeader(unit));
					pk::move(u, { pt0 });
					execute폭풍시(u, pt);
					if (콘솔_로그_표시)
						pk::printf("storm end {}->{}\n", getNameLeader(u), getNameLeader(unit));
					return true;
				}
			}



			
			return false;
		}
		bool AI전법사용_백이병_극나선첨(pk::unit@ u)
		{
			int dist = 2;

			int maxAttack = 0;
			pk::unit@ maxUnit = null;
			pk::point maxPos;

			array<pk::point> arr = pk::get_movable_pos(u);
			for (int i0 = 0; i0 < arr.length; i0++)
			{
				pk::point pt0 = arr[i0];
				if (!pk::is_in_screen(pt0))
					continue;

				array<pk::point> range = pk::range(pt0, 2, 2);
				for (int i = 0; i < range.length; i++)
				{
					pk::point pt = range[i];
					pk::unit@ unit = getUnit(pt);
					if (unit == null || !pk::is_enemy(u, unit))
						continue;
					if (!checkHex창병(pt))
						continue;

					int dist = pk::get_distance(u.get_pos(), pt);
					if (dist == 2)
					{
						int dir = pk::get_direction(u.get_pos(), pt);
						pk::point ptCenter = pk::get_neighbor_pos(u.get_pos(), dir, 1);
						//ptCenter.x = (u.get_pos().x + pt.x) * 0.5;
						//ptCenter.y = (u.get_pos().y + pt.y) * 0.5;
						pk::hex_object@ obj = pk::get_hex_object(ptCenter);
						//pk::printf("pos x{},y{}\n", ptCenter.x, ptCenter.y);
						//if (obj != null)
						//	pk::printf("obj type {},x{},y{}\n", obj.get_type_id(), ptCenter.x, ptCenter.y);
						//else
						//{
						//	pk::printf("obj null x{},y{}\n", ptCenter.x, ptCenter.y);
						//}

						if (obj != null && obj.get_type_id() != 11)
						{
							pk::printf("length return {}\n", getNameLeader(u));
							continue;
						}
						if (obj == null && pk::get_hex(ptCenter).terrain == 지형_관문)
						{
							pk::printf("length return {}\n", getNameLeader(u));
							continue;
						}

					}

					if (unit.attr.stat[부대능력_공격] > maxAttack)
					{
						maxPos = pt0;
						maxAttack = unit.attr.stat[부대능력_공격];
						@maxUnit = unit;
					}
				}
			}



			if (maxUnit == null)
				return false;

			if(콘솔_로그_표시)
				pk::printf("nasunchum start {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			pk::move(u, { maxPos });
			execute극나선첨(u, maxUnit.get_pos());
			if (콘솔_로그_표시)
				pk::printf("nasunchum end {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			return true;
		}

		bool AI전법사용_대극사_무영참(pk::unit@ u)
		{
			array<pk::point> arr = pk::get_movable_pos(u);
			for (int i0 = 0; i0 < arr.length; i0++)
			{
				pk::point pt0 = arr[i0];
				if (!pk::is_in_screen(pt0))
					continue;

				for (int i = 0; i < 방향_끝; i++)
				{
					pk::point pt = pk::get_neighbor_pos(pt0, i, 1);
					pk::unit@ unit = getUnit(pt);
					if (unit == null || !pk::is_enemy(u, unit))
						continue;
					if (!checkHex창병(pt))
						continue;

					pk::point pt1 = pk::get_neighbor_pos(pt0, i, 2);
					pk::point pt2 = pk::get_neighbor_pos(pt0, i, 3);
					pk::unit@ unit1 = getUnit(pt1);
					pk::unit@ unit2 = getUnit(pt2);
					if (unit1 != null && pk::is_enemy(u, unit1) || 
						(unit1 ==null &&  unit2 != null && pk::is_enemy(u, unit2)))
					{
						
						if (콘솔_로그_표시)
							pk::printf("noShadow start {}->{}\n", getNameLeader(u), getNameLeader(unit));
						pk::move(u, { pt0 });
						execute무영참(u, pt);
						if (콘솔_로그_표시)
							pk::printf("noShadow no {}->{}\n", getNameLeader(u), getNameLeader(unit));
						return true;
					}
				}
			}
			return true;
		}
		bool AI전법사용_선등열사_화염주(pk::unit@ u)
		{
			array<pk::point> arr = pk::get_movable_pos(u);
			for (int i0 = 0; i0 < arr.length; i0++)
			{
				pk::point pt0 = arr[i0];
				if (!pk::is_in_screen(pt0))
					continue;

				for (int i = 0; i < 방향_끝; i++)
				{
					pk::point pt = pk::get_neighbor_pos(pt0, i, 1);
					pk::unit@ unit = getUnit(pt);
					if (unit == null || !pk::is_enemy(u, unit))
						continue;
					if (!checkHex창병(pt))
						continue;

					pk::point pt1 = pk::get_neighbor_pos(pt0, i, 2);
					pk::point pt2 = pk::get_neighbor_pos(pt0, i, 3);
					pk::unit@ unit1 = getUnit(pt1);
					pk::unit@ unit2 = getUnit(pt2);
					if (unit1 != null && pk::is_enemy(u, unit1) || 
						(unit1 ==null && unit2 != null && pk::is_enemy(u, unit2)))
					{

						if (콘솔_로그_표시)
							pk::printf("fireball start {}->{}\n", getNameLeader(u), getNameLeader(unit));
						pk::move(u, { pt0 });
						execute화염주(u, pt);
						if (콘솔_로그_표시)
							pk::printf("fireball end {}->{}\n", getNameLeader(u), getNameLeader(unit));
						return true;
					}
				}
			}
			return false;
		}
		bool AI전법사용_단양병_투척(pk::unit@ u)
		{
			int maxRatio = 0;
			pk::unit@ maxUnit = null;
			pk::point maxPos;
			int acount = 0;

			array<pk::point> arr = pk::get_movable_pos(u);
			for (int i0 = 0; i0 < arr.length; i0++)
			{
				pk::point pt0 = arr[i0];
				if (!pk::is_in_screen(pt0))
					continue;

				array<pk::point> arr = pk::range(pt0, 1, 1);
				for (int i = 0; i < arr.length; i++)
				{
					pk::point pt = arr[i];
					pk::unit@ unit = getUnit(pt);
					if (unit == null || !pk::is_enemy(u, unit))
						continue;

					acount++;
					int nTactics = callback202(u, pt, unit, 전법_선풍);
					if (nTactics > maxRatio)
					{
						@maxUnit = unit;
						maxRatio = nTactics;
						maxPos = pt0;
					}
				}
			}
			
			if (acount >= 2 && maxUnit!=null)
			{
				if (콘솔_로그_표시)
					pk::printf("fireAll start {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
				pk::move(u, { maxPos });
				execute투척(u, maxUnit.get_pos());
				if (콘솔_로그_표시)
					pk::printf("fireAll end {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
				return true;
			}
			return false;
		}

		bool AI전법사용_함진영_도참(pk::unit@ u)
		{
			//2명이상되면 발사
			int dist = getMaxAttackDistance(u);

			array<pk::point> arr = pk::get_movable_pos(u);
			for (int i0 = 0; i0 < arr.length; i0++)
			{
				pk::point pt0 = arr[i0];
				if (!pk::is_in_screen(pt0))
					continue;

				for (int i = 0; i < 방향_끝; i++)
				{
					pk::point pt = pk::get_neighbor_pos(pt0, i, dist);
					pk::unit@ unit = getUnit(pt);
					if (unit == null || !pk::is_enemy(u, unit))
						continue;
					if (!checkHex극병(pt))
						continue;

					array<pk::point> arr = get횡치pos(pt0, pt);
					pk::unit@ u0 = getUnit(arr[0]);
					pk::unit@ u1 = getUnit(arr[1]);
					if (u0 != null && pk::is_enemy(u, u0) || u1 != null && pk::is_enemy(u, u1))
					{
						if (콘솔_로그_표시)
							pk::printf("doCharm start {}->{}\n", getNameLeader(u), getNameLeader(unit));
						pk::move(u, { pt0 });
						execute도참(u, pt);
						if (콘솔_로그_표시)
							pk::printf("doCharm end {}->{}\n", getNameLeader(u), getNameLeader(unit));
						return true;
					}
				}
			}

			return false;
		}
		bool AI전법사용_서량철기_멸파(pk::unit@ u,bool bMulpa)
		{
			array<pk::point> arr = pk::get_movable_pos(u);

			int maxDist = 0;
			pk::unit@ maxUnit = null;
			pk::point maxPt;
			for (int i = 0; i < arr.length; i++)
			{
				pk::point pt = arr[i];
				if (!pk::is_in_screen(pt))
					continue;

				int dist = pk::get_distance(pt, u.get_pos());
				if(dist<2)
					continue;

				for (int j = 0; j < 방향_끝; j++)
				{
					pk::point pt2 = pk::get_neighbor_pos(pt, j, 1);
					int dist2 = pk::get_distance(u.get_pos(), pt2);
					if(dist2<3)
						continue;
					pk::unit@ unit = getUnit(pt2);
					if (unit == null || !pk::is_enemy(u, unit))
						continue;
					if(!checkHex기병(pt2))
						continue;
					if (dist2 > maxDist)
					{
						maxDist = dist2;
						@maxUnit = unit;
						maxPt = pt;
					}
				}
			}
			if (maxUnit == null)
				return false;

			if(콘솔_로그_표시)
				pk::printf("{} start {}->{}\n", bMulpa ? "moveAttackerPower":"moveAttackEnergy", getNameLeader(u), getNameLeader(maxUnit));
			pk::move(u, {maxPt});
			if (bMulpa)
				execute멸파(u, maxUnit.get_pos());
			else
				execute광폭(u, maxUnit.get_pos());
			if (콘솔_로그_표시)
				pk::printf("{} end {}->{}\n", bMulpa ? "moveAttackerPower" : "moveAttackEnergy", getNameLeader(u), getNameLeader(maxUnit));
			return true;
		}

		bool AI전법사용_호표기_난도(pk::unit@ u)
		{
			array<pk::point> arr = pk::get_movable_pos(u);
			for (int i = 0; i < arr.length; i++)
			{
				pk::point pt = arr[i];
				if (!pk::is_in_screen(pt))
					continue;

				for (int j = 0; j < 방향_끝; j++)
				{
					pk::point pt2 = pk::get_neighbor_pos(pt, j, 1);
					pk::unit@ unit = getUnit(pt2);
					if (unit == null || !pk::is_enemy(u, unit))
						continue;
					if(!checkHex기병(pt2))
						continue;

					array<pk::point> arr = get횡치pos(pt, pt2);
					pk::unit@ u0 = checkHex기병(arr[0]) ? getUnit(arr[0]) : null;
					pk::unit@ u1 = checkHex기병(arr[1]) ? getUnit(arr[1]) : null;
					if (u0 != null && pk::is_enemy(u, u0) || u1 != null && pk::is_enemy(u, u1))
					{
						if (콘솔_로그_표시)
							pk::printf("nando start {}->{}\n", getNameLeader(u), getNameLeader(unit));
						pk::move(u, { pt });
						execute난도(u, pt2);
						if (콘솔_로그_표시)
							pk::printf("nando end {}->{}\n", getNameLeader(u), getNameLeader(unit));
						return true;
					}
				}
			}
			return false;
		}
		bool AI전법사용_백마의종_백마시(pk::unit@ u)
		{
			int maxDist = getMaxAttackDistance(u);
			maxDist = 2;
			
			bool b궁신 = u.has_skill(특기_궁신);
			array<pk::point> arr = pk::get_movable_pos(u);
			for (int i = 0; i < arr.length; i++)
			{
				pk::point pt = arr[i];
				if(!pk::is_in_screen(pt))
					continue;
				array<pk::point> arr2 = pk::range(pt, 1, maxDist);
				for (int j = 0; j < arr2.length; j++)
				{
					pk::point pt2 = arr2[j];
					pk::unit@ unit = getUnit(pt2);
					if (unit == null || !pk::is_enemy(u, unit))
						continue;
					if (!checkHex기병(pt2))
						continue;
					int acount = 0;
					array<pk::point> arr3 = pk::range(pt2, 0, 1);
					bool bMine = false;
					for (int k = 0; k < arr3.length; k++)
					{
						pk::point pt3 = arr3[k];
						pk::unit@ unit2 = getUnit(pt3);
						if (unit2 == null || !pk::is_enemy(u, unit2))
							continue;
						if (!checkHex기병(pt3))
							continue;
						if (!b궁신 && !pk::is_enemy(u, unit2))
						{
							bMine = true;
							break;
						}
						acount++;
					}
					if (bMine || acount < 3) 
						continue;
						
					if (콘솔_로그_표시)
						pk::printf("white horse start {}->{}\n", getNameLeader(u), getNameLeader(unit));
					pk::move(u, { pt });
					execute백마시(u, pt2);
					if (콘솔_로그_표시)
						pk::printf("white horse end {}->{}\n", getNameLeader(u), getNameLeader(unit));
					return true;
				}
			}
			return false;

		}

		void AI전법사용(pk::force@ force)
		{
			if (force.is_player() || !AI전법_사용)
				return;

			pk::list<pk::unit@> units = pk::get_unit_list(force);
			for (int i = 0; i < units.count; i++)
			{
				pk::unit@ u = units[i];
				if(!pk::is_in_screen(u.get_pos()))
					continue;

				int n = 0;
				try
				{
					n = int(pk::core["적성"][pk::get_tekisei(u)]["전법성공확률"]) + pk::core::tactics_chance(u.leader);
				}
				catch
				{
					pk::printf("try catch return {}\n", getNameLeader(u));
					continue;
				}
				
					

				if(u.energy < 전법_기력)
					continue;
				//AI전법사용_오계만병_역습(u);
				//continue;
				int skill = getSkill(u);
				if(skill == -1)
					continue;

				//pk::printf("ai tacticks {}\n", getNameLeader(u));
				bool b = false;
				
				switch (skill)
				{
				case 특수병과_노병_강노병:b=AI전법사용_강노병_저격(u); break;
				case 특수병과_노병_연노병:b=AI전법사용_연노병_대화시(u); break;
				case 특수병과_노병_오계만병:b = AI전법사용_오계만병_역습(u); break;
				case 특수병과_노병_연노전차:b = AI전법사용_연노전차_폭풍시(u); break;
				case 특수병과_창병_백이병:b = AI전법사용_백이병_극나선첨(u); break;
				case 특수병과_창병_대극사:b = AI전법사용_대극사_무영참(u); break;
				case 특수병과_창병_선등열사:b = AI전법사용_선등열사_화염주(u); break;
				case 특수병과_극병_단양병:b = AI전법사용_단양병_투척(u); break;
				case 특수병과_극병_함진영:b = AI전법사용_함진영_도참(u); break;
				case 특수병과_기병_서량철기:b = AI전법사용_서량철기_멸파(u,true); break;
				case 특수병과_기병_비웅경기:b = AI전법사용_서량철기_멸파(u, false); break;
				case 특수병과_기병_호표기:b = AI전법사용_호표기_난도(u); break;
				case 특수병과_기병_백마의종:b = AI전법사용_백마의종_백마시(u); break;
				
				default:
					break;
				}
			}
		}

		/////////////////////////////////전법
		pk::unit@ _unit;
		pk::point _src_pos;
		pk::point _src_pos0;
		void init(pk::unit@ unit, pk::point src_pos)
		{
			@_unit = unit;
			_src_pos = src_pos;
			_src_pos0 = unit.get_pos();
			@_force = pk::get_force(_unit.get_force_id());
		}
		bool IsVisible저격()
		{
			return 전체_전법_사용_테스트 || isSkill(_unit, 특수병과_노병_강노병);
		}
		string Get저격Text()
		{
			return pk::encode("저격");
		}
		string Get저격Desc()
		{
			return pk::encode("장거리에서 활을 쏘면 부상확률이 증가합니다.");
		}
		pk::array<pk::point_int> GetTargets저격()
		{
			pk::array<pk::point_int> targets;

			pk::force@ f = pk::get_force(_unit.get_force_id());
			
			auto range=pk::range(_src_pos,2,pk::has_tech(f,기교_강노) ? 4 : 3);
			for(int i=0;i<range.length;i++)
			{
				pk::hex_object@ obj=pk::get_hex_object(range[i]);
				if (obj == null)
					continue;
				if(_force!=null && _force.get_id() == obj.get_force_id())
					continue;
				if(!checkHex노병(_unit,range[i]))
					continue;

				targets.insertLast(pk::point_int(range[i], 0));
			}
			return targets;
		}
		int GetChance저격(pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return 0;

			return callback202(_unit, dst_pos, target, 전법_관시);
		}

		void execute저격(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			int nTactics = callback202(unit0, dst_pos, target, 전법_관시);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), 전법_관시, 크리티컬_원거리);

			//bTactics = false;
			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, 유닛_전법_활공격, bCri);
			}
			else
			{
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, 전법_관시, dst_pos, 0, bCri ? 1 : 0, false);
				if (!금강불굴(di, target))
				{
					pk::unit_anim(unit0, 유닛_전법_관시, { di }, pk::point(-1, -1), 0, "", 0);
					if (bCri)
						cutin(unit0);
					addTroops(target, di.troops_damage);

					pk::unit@ u = getUnit(di.dst_pos);
					if (u != null && !u.has_skill(특기_호위))
					{
						if (u.member[0] >= 0 && u.member[0] < 무장_끝 && pk::rand_bool(저격_부상_확률))
							injury(pk::get_person(u.member[0]));
						if (u.member[1] >= 0 && u.member[1] < 무장_끝 && pk::rand_bool(저격_부상_확률))
							injury(pk::get_person(u.member[1]));
						if (u.member[2] >= 0 && u.member[2] < 무장_끝 && pk::rand_bool(저격_부상_확률))
							injury(pk::get_person(u.member[2]));
					}
					bool re=update(unit0, dst_pos, { di }, 크리티컬_원거리,bCri);
					re=updateAfter(unit0, target);
					if (re && 연전(unit0))
					{
						pk::unit_anim(unit0, 유닛_전법_관시, { di }, pk::point(-1, -1), 0, "", 0);
						if (bCri)
							cutin(unit0);
						addTroops(target, di.troops_damage);

						@u = getUnit(di.dst_pos);
						if (u != null && !u.has_skill(특기_호위))
						{
							if (u.member[0] >= 0 && u.member[0] < 무장_끝 && pk::rand_bool(저격_부상_확률))
								injury(pk::get_person(u.member[0]));
							if (u.member[1] >= 0 && u.member[1] < 무장_끝 && pk::rand_bool(저격_부상_확률))
								injury(pk::get_person(u.member[1]));
							if (u.member[2] >= 0 && u.member[2] < 무장_끝 && pk::rand_bool(저격_부상_확률))
								injury(pk::get_person(u.member[2]));
						}
						update(unit0, dst_pos, { di }, 크리티컬_원거리,bCri);
						updateAfter(unit0, target);
					}
				}
			}
			update(unit0, target, dst_pos, dst_pos);
		}

		//강노병
		bool 저격Handler(pk::point dst_pos)
		{
			execute저격(_unit, dst_pos);
			return true;
		}
		bool IsVisible대화시()
		{
			return 전체_전법_사용_테스트 || isSkill(_unit, 특수병과_노병_연노병);
		}
		string Get대화시Text()
		{
			return pk::encode("대화시");
		}
		string Get대화시Desc()
		{
			return pk::encode("화시 난사입니다.");
		}
		pk::array<pk::point_int> GetTargets대화시()
		{
			pk::array<pk::point_int> targets;

			pk::force@ f = pk::get_force(_unit.get_force_id());

			auto range = pk::range(_src_pos, 2, pk::has_tech(f, 기교_강노) ? 3 : 2);
			for (int i = 0; i < range.length; i++)
			{
				pk::hex_object@ obj = pk::get_hex_object(range[i]);
				if (obj == null)
					continue;
				if (_force != null && _force.get_id() == obj.get_force_id())
					continue;
				if(!checkHex노병(_unit,range[i]))
					continue;

				targets.insertLast(pk::point_int(range[i], 0));
			}
			return targets;
		}
		int GetChance대화시(pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return 0;

			return callback202(_unit, dst_pos, target, 전법_난사);
		}

		void execute대화시(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			int nTactics = callback202(unit0, dst_pos, target, 전법_난사);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), 전법_난사, 크리티컬_원거리);
			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, 유닛_전법_활공격, bCri);
			}
			else
			{
				array<pk::damage_info> dis;
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, 전법_난사, dst_pos, 0, bCri ? 1 : 0, false);

				if (!금강불굴(di, target))
				{
					dis.insertLast(di);

					for (int i = 0; i < 6; i++)
					{
						pk::point pt = pk::get_neighbor_pos(dst_pos, i, 1);
						pk::hex_object@ obj = pk::get_hex_object(pt);
						if (obj == null)
							continue;
						if (unit0.has_skill(특기_궁신) && !pk::is_enemy(unit0, obj))
							continue;

						pk::damage_info di2;
						di2.src_pos = unit0.get_pos();
						di2.dst_pos = pt;

						callback209(di2, unit0, 전법_난사, pt, 0, bCri ? 1 : 0, false);
						dis.insertLast(di2);
					}
					pk::unit_anim(unit0, 유닛_전법_난사, dis, pk::point(-1), 0, getString("대화시"), 0);
					if (bCri) 
						cutin(unit0);
						
					for (int i = 0; i < dis.length; i++)
					{
						pk::damage_info di = dis[i];
						pk::hex_object@ u = pk::get_hex_object(di.dst_pos);
						if (u == null)
							continue;
						addTroops(u, di);
						updateAfter(unit0, u);
						if (pk::rand_bool(대화시_화시_확률)) 
							pk::create_fire(u.get_pos(), pk::rand(3) + 1, unit0, false);
					}
					bool re=update(unit0, dst_pos, dis, 크리티컬_원거리,bCri);
					if (re && 연전(unit0))
					{
						pk::unit_anim(unit0, 유닛_전법_난사, dis, pk::point(-1), 0, getString("대화시"), 0);
						if (bCri)
							cutin(unit0);

						for (int i = 0; i < dis.length; i++)
						{
							pk::damage_info di = dis[i];
							pk::hex_object@ u = pk::get_hex_object(di.dst_pos);
							if (u == null)
								continue;
							addTroops(u, di);
							updateAfter(unit0, u);
							if (pk::rand_bool(대화시_화시_확률))
								pk::create_fire(u.get_pos(), pk::rand(3) + 1, unit0, false);
						}
						update(unit0, dst_pos, dis, 크리티컬_원거리, bCri);
					}
				}
			}
			update(unit0, target, dst_pos, dst_pos);
		}

		//연노병
		bool 대화시Handler(pk::point dst_pos)
		{
			execute대화시(_unit, dst_pos);
			return true;
		}
		bool IsVisible역습()
		{
			return 전체_전법_사용_테스트 || isSkill(_unit, 특수병과_노병_오계만병);
		}
		string Get역습Text()
		{
			return pk::encode("역습");
		}
		string Get역습Desc()
		{
			return pk::encode("근접공격으로 간혹 혼란을 유발합니다.");
		}
		pk::array<pk::point_int> GetTargets역습()
		{
			pk::array<pk::point_int> targets;

			pk::force@ f = pk::get_force(_unit.get_force_id());

			auto range = pk::range(_src_pos, 1,1);
			for (int i = 0; i < range.length; i++)
			{
				pk::hex_object@ obj = pk::get_hex_object(range[i]);
				if (obj == null)
					continue;
				if (_force != null && _force.get_id() == obj.get_force_id())
					continue;

				targets.insertLast(pk::point_int(range[i], 0));
			}
			return targets;

		}
		int GetChance역습(pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return 0;

			return callback202(_unit, dst_pos, target, 전법_화시);
		}
		void execute역습(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			int nTactics = callback202(unit0, dst_pos, target, 전법_화시);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), 전법_화시, 크리티컬_원거리);


			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, 유닛_전법_근접공격, bCri);
			}
			else
			{
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, 전법_화시, dst_pos, 0, bCri ? 1 : 0, false);
				if (!금강불굴(di, target))
				{
					pk::unit_anim(unit0, 유닛_전법_근접공격, { di }, dst_pos, 0, getString("역습"), 0);
					if (bCri)
						cutin(unit0);

					addTroops(target, di);
					updateAfter(unit0, target);
					pk::unit@ u = pk::is_valid_pos(target.get_pos()) ? getUnit(target.get_pos()) : null;
					if (u != null && pk::rand_bool(역습_혼란_확률))
						updateChaos(u, unit0);

					bool re=update(unit0, dst_pos, { di }, 크리티컬_근접, bCri);
					if (re && 연전(unit0))
					{
						pk::unit_anim(unit0, 유닛_전법_근접공격, { di }, dst_pos, 0, getString("역습"), 0);
						if (bCri)
							cutin(unit0);

						addTroops(target, di);
						updateAfter(unit0, target);
						pk::unit@ u = pk::is_valid_pos(target.get_pos()) ? getUnit(target.get_pos()) : null;
						if (u != null && pk::rand_bool(역습_혼란_확률))
							updateChaos(u, unit0);

						update(unit0, dst_pos, { di }, 크리티컬_근접, bCri);
					}
				}
			}

			update(unit0, target, dst_pos, dst_pos);
			return;
		}

		//오계만병
		bool 역습Handler(pk::point dst_pos)
		{
			execute역습(_unit, dst_pos);
			return true;
		}

		bool IsVisible폭풍시()
		{
			return 전체_전법_사용_테스트 || isSkill(_unit, 특수병과_노병_연노전차);
		}
		string Get폭풍시Text()
		{
			return pk::encode("폭풍시");
		}
		string Get폭풍시Desc()
		{
			return pk::encode("주위 2칸 사이의 적에 모두 사격합니다.");
		}
		pk::array<pk::point_int> GetTargets폭풍시()
		{
			return GetTargets대화시();
		}
		int GetChance폭풍시(pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return 0;

			return callback202(_unit, dst_pos, target, 전법_난사);
		}
		
		void execute폭풍시(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;


			int nTactics = callback202(unit0, dst_pos, target, 전법_난사);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), 전법_난사, 크리티컬_원거리);

			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, 유닛_전법_활공격, bCri);
			}
			else
			{

				array<pk::damage_info> dis;
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, 전법_난사, dst_pos, 0, bCri ? 1 : 0, false);

				if (!금강불굴(di, target))
				{
					dis.insertLast(di);

					array<pk::point> range = pk::range(dst_pos, 1, 2);
					for (int i = 0; i < range.length; i++)
					{
						pk::point pt = range[i];
						if (pk::get_hex_object(pt) != null && pk::rand_bool(폭풍시_확률))
						{
							pk::damage_info di2;
							di2.src_pos = unit0.get_pos();
							di2.dst_pos = pt;
							callback209(di2, unit0, 전법_난사, pt, 0, bCri ? 1 : 0, false);
							dis.insertLast(di2);
						}
					}
					pk::unit_anim(unit0, 유닛_전법_난사, dis, dst_pos, 0);
					if (bCri)
						cutin(unit0);


					for (int i = 0; i < dis.length; i++)
					{
						pk::damage_info di = dis[i];
						pk::hex_object@ obj = getUnit(di.dst_pos);
						if (obj == null)
							continue;
						if (unit0.has_skill(특기_궁신) && unit0.get_force_id() == obj.get_force_id())
							continue;
						if (unit0.get_id() == obj.get_id())
							continue;

						addTroops(obj, di);
						updateAfter(unit0, obj);
					}
					bool re=update(unit0, dst_pos, dis, 크리티컬_원거리, bCri);
					if (re && 연전(unit0))
					{
						pk::unit_anim(unit0, 유닛_전법_난사, dis, dst_pos, 0);
						if (bCri)
							cutin(unit0);

						for (int i = 0; i < dis.length; i++)
						{
							pk::damage_info di = dis[i];
							pk::hex_object@ obj = getUnit(di.dst_pos);
							if (obj == null)
								continue;
							if (unit0.has_skill(특기_궁신) && unit0.get_force_id() == obj.get_force_id())
								continue;
							if (unit0.get_id() == obj.get_id())
								continue;

							addTroops(obj, di);
							updateAfter(unit0, obj);
						}
						update(unit0, dst_pos, dis, 크리티컬_원거리, bCri);
					}
				}

			}

			update(unit0, target, dst_pos, dst_pos);
		}

		//연노전차
		bool 폭풍시Handler(pk::point dst_pos)
		{
			execute폭풍시(_unit, dst_pos);
			return true;
		}

		bool IsVisible극나선첨()
		{
			return 전체_전법_사용_테스트 || isSkill(_unit, 특수병과_창병_백이병);
		}
		string Get극나선첨Text()
		{
			return pk::encode("극나선첨");
		}
		string Get극나선첨Desc()
		{
			return pk::encode("주위 2칸 까지 나선첨을 사용할 수 있습니다.");
		}
		pk::array<pk::point_int> GetTargets극나선첨()
		{
			pk::array<pk::point_int> targets;
			pk::force@ f = pk::get_force(_unit.get_force_id());
			auto range = pk::range(_src_pos, 1, 2);
			for (int i = 0; i < range.length; i++)
			{
				pk::hex_object@ obj = pk::get_hex_object(range[i]);
				if (obj == null)
					continue;
				if (_force != null && _force.get_id() == obj.get_force_id())
					continue;

				//중간에 건물있는경우
				int dist = pk::get_distance(_src_pos, range[i]);
				if (dist == 2) 
				{
					pk::point ptCenter;
					ptCenter.x = (_src_pos.x + range[i].x) * 0.5;
					ptCenter.y = (_src_pos.y + range[i].y) * 0.5;
					pk::hex_object@ obj = pk::get_hex_object(ptCenter);
					if(obj!=null && obj.get_type_id()!=11)
						continue;
				}

				if(!checkHex창병(range[i]))
					continue;
				targets.insertLast(pk::point_int(range[i], 0));
			}
			return targets;

		}
		int GetChance극나선첨(pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return 0;

			return callback202(_unit, dst_pos, target, 전법_나선첨);
		}

		void execute극나선첨(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			int nTactics = callback202(unit0, dst_pos, target, 전법_나선첨);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), 전법_나선첨, 크리티컬_근접);


			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, 유닛_전법_근접공격, bCri);
			}
			else
			{
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, 전법_나선첨, dst_pos, 0, bCri ? 1 : 0, false);
				if (!금강불굴(di, target))
				{
					pk::unit_anim(unit0, 유닛_전법_나선첨, { di }, dst_pos, 0, getString("극나선첨"), 0);
					if (bCri)
						cutin(unit0);

					addTroops(target, di);
					updateAfter(unit0, target);


					pk::unit@ u = getUnit(di.dst_pos);
					if (u != null && prev_callback_221(unit0, u, bCri) > 0)
						updateChaos(u, unit0);
					bool re=update(unit0, dst_pos, { di }, 크리티컬_근접, bCri);
					if (re && 연전(unit0))
					{
						pk::unit_anim(unit0, 유닛_전법_나선첨, { di }, dst_pos, 0, getString("극나선첨"), 0);
						if (bCri)
							cutin(unit0);

						addTroops(target, di);
						updateAfter(unit0, target);


						pk::unit@ u = getUnit(di.dst_pos);
						if (u != null && prev_callback_221(unit0, u, bCri) > 0)
							updateChaos(u, unit0);
						update(unit0, dst_pos, { di }, 크리티컬_근접, bCri);
					}
				}

			}

			update(unit0, target, dst_pos, dst_pos);
		}

		//백이병
		bool 극나선첨Handler(pk::point dst_pos) //백이병
		{
			execute극나선첨(_unit, dst_pos);
			return true;
		}


		bool IsVisible무영참()
		{
			return 전체_전법_사용_테스트 || isSkill(_unit, 특수병과_창병_대극사);
		}
		string Get무영참Text()
		{
			return pk::encode("무영참");
		}
		string Get무영참Desc()
		{
			return pk::encode("이단첨을 사용하면 일정확률로 혼란효과가 발생합니다.");
		}
		pk::array<pk::point_int> GetTargets무영참()
		{
			pk::array<pk::point_int> targets;
			pk::force@ f = pk::get_force(_unit.get_force_id());
			auto range = pk::range(_src_pos, 1, 1);
			for (int i = 0; i < range.length; i++)
			{
				pk::hex_object@ obj = pk::get_hex_object(range[i]);
				if (obj == null)
					continue;
				if (_force != null && _force.get_id() == obj.get_force_id())
					continue;
				if(!checkHex창병(range[i]))
					continue;
				targets.insertLast(pk::point_int(range[i], 0));
			}
			return targets;

		}
		int GetChance무영참(pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return 0;

			return callback202(_unit, dst_pos, target, 전법_이단첨);
		}

		void execute무영참(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			pk::point dst_pos2 = dst_pos;

			int nTactics = callback202(unit0, dst_pos, target, 전법_이단첨);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), 전법_이단첨, 크리티컬_근접);
			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, 1, bCri);
			}
			else
			{
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, 전법_이단첨, dst_pos, 0, bCri ? 1 : 0, false);
				if (!금강불굴(di, target))
				{
					int dir = pk::get_direction(unit0.get_pos(), dst_pos);
					pk::point ptA = pk::get_neighbor_pos(dst_pos, dir, 2);
					di.src_move_pos = unit0.get_pos();
					di.dst_move_pos = MovePoint(dst_pos, ptA);
					pk::unit_anim(unit0, 유닛_전법_이단첨, { di }, dst_pos, 0, getString("무영참"), 0);
					if (bCri)
						cutin(unit0);

					pk::unit@ u = getUnit(di.dst_pos);
					if (u != null && (prev_callback_221(unit0, u, bCri) > 0))
					{
						updateChaos(u, unit0);
						pk::move(u, { MovePoint(dst_pos, ptA) });
					}
					if (ptA.x != di.dst_move_pos.x || ptA.y != di.dst_move_pos.y)
					{
						int dir2 = pk::get_direction(di.dst_move_pos, ptA);
						int dist2 = pk::get_distance(di.dst_move_pos, ptA);
						for (int i = 0; i < dist2; i++)
						{
							pk::point pt = pk::get_neighbor_pos(di.dst_move_pos, dir2, i);
							pk::unit@ ptu = pk::get_unit(pt);
							if (ptu != null && pk::is_enemy(unit0, ptu) && (prev_callback_221(unit0, ptu, bCri) > 0))
								updateChaos(ptu, unit0);
						}
					}

					addTroops(target, di);
					updateAfter(unit0, target);
					bool re=update(unit0, dst_pos, { di }, 크리티컬_근접, bCri);
					pk::point dst_pos2 = di.dst_move_pos;
					if (re && 연전(unit0))
					{
						pk::point ptA = pk::get_neighbor_pos(dst_pos2, dir, 2);
						di.src_move_pos = unit0.get_pos();
						di.dst_move_pos = MovePoint(dst_pos2, ptA);
						pk::unit_anim(unit0, 유닛_전법_이단첨, { di }, dst_pos2, 0, getString("무영참"), 0);
						if (bCri)
							cutin(unit0);

						pk::unit@ u = getUnit(dst_pos2);
						if (u != null && (prev_callback_221(unit0, u, bCri) > 0))
						{
							updateChaos(u, unit0);
							pk::move(u, { MovePoint(dst_pos, ptA) });
						}
						if (ptA.x != di.dst_move_pos.x || ptA.y != di.dst_move_pos.y)
						{
							int dir2 = pk::get_direction(di.dst_move_pos, ptA);
							int dist2 = pk::get_distance(di.dst_move_pos, ptA);
							for (int i = 0; i < dist2; i++)
							{
								pk::point pt = pk::get_neighbor_pos(di.dst_move_pos, dir2, i);
								pk::unit@ ptu = pk::get_unit(pt);
								if (ptu != null && pk::is_enemy(unit0, ptu) && (prev_callback_221(unit0, ptu, bCri) > 0))
									updateChaos(ptu, unit0);
							}
						}


						addTroops(target, di);
						updateAfter(unit0, target);
						update(unit0, dst_pos2, { di }, 크리티컬_근접, bCri);
						dst_pos2 = di.dst_move_pos;

					}
				}

			}//bTatics
			update(unit0, target, dst_pos, dst_pos2);
		}
		//대극사
		bool 무영참Handler(pk::point dst_pos)
		{
			execute무영참(_unit, dst_pos);
			return true;
		}

		bool IsVisible화염주()
		{
			return 전체_전법_사용_테스트 || isSkill(_unit, 특수병과_창병_선등열사);
		}
		string Get화염주Text()
		{
			return pk::encode("화염주");
		}
		string Get화염주Desc()
		{
			return pk::encode("3칸까지 이단첨을 사용하고 일정확률로 화계가 발생합니다.");
		}
		pk::array<pk::point_int> GetTargets화염주()
		{
			return GetTargets무영참();
		}
		int GetChance화염주(pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return 0;

			return callback202(_unit, dst_pos, target, 전법_이단첨);
		}

		void execute화염주(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			int nTactics = callback202(unit0, dst_pos, target, 전법_이단첨);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), 전법_이단첨, 크리티컬_근접);
			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, 유닛_전법_근접공격, bCri);
			}
			else
			{
				pk::damage_info di0;
				di0.src_pos = unit0.get_pos();
				di0.dst_pos = dst_pos;
				callback209(di0, unit0, 전법_이단첨, dst_pos, 0, bCri ? 1 : 0, false);
				if (!금강불굴(di0, target))
				{
					array<pk::damage_info> dis;
					int dir = pk::get_direction(unit0.get_pos(), dst_pos);
					for (int i = 0; i < 3; i++)
					{
						pk::point pt = pk::get_neighbor_pos(unit0.get_pos(), dir, i + 1);
						pk::hex_object@ obj = pk::get_hex_object(pt);
						if (obj == null)
							continue;
						if (!pk::is_enemy(unit0, obj))
							continue;
						if (!checkHex창병(pt))
							continue;

						pk::damage_info di2;
						di2.src_pos = unit0.get_pos();
						di2.dst_pos = pt;

						callback209(di2, unit0, 전법_이단첨, pt, 0, bCri ? 1 : 0, false);
						dis.insertLast(di2);
					}
					pk::unit_anim(unit0, 유닛_전법_이단첨, dis, dst_pos, 0, getString("화염주"), 0);
					if (bCri)
						cutin(unit0);

					for (int i = 0; i < dis.length; i++)
					{
						pk::damage_info di = dis[i];
						pk::hex_object@ hex = pk::get_hex_object(di.dst_pos);
						if (hex == null)
							continue;
						addTroops(hex, di);
						if (pk::rand_bool(화염주_화계_확률))
							pk::create_fire(hex.get_pos(), pk::rand(3) + 1, unit0, false);
						updateAfter(unit0, hex);
					}
					bool re=update(unit0, dst_pos, dis, 크리티컬_근접, bCri);
					if (re && 연전(unit0))
					{
						pk::unit_anim(unit0, 유닛_전법_이단첨, dis, dst_pos, 0, getString("화염주"), 0);
						if (bCri)
							cutin(unit0);

						for (int i = 0; i < dis.length; i++)
						{
							pk::damage_info di = dis[i];
							pk::hex_object@ hex = pk::get_hex_object(di.dst_pos);
							if (hex == null)
								continue;
							addTroops(hex, di);
							if (pk::rand_bool(화염주_화계_확률))
								pk::create_fire(hex.get_pos(), pk::rand(3) + 1, unit0, false);
							updateAfter(unit0, hex);
						}
						update(unit0, dst_pos, dis, 크리티컬_근접, bCri);
					}
				}
			}
			update(unit0, target, dst_pos, dst_pos);
		}

		//선등열사
		bool 화염주Handler(pk::point dst_pos)
		{
			execute화염주(_unit, dst_pos);
			return true;
		}

		bool IsVisible투척()
		{
			return 전체_전법_사용_테스트 || isSkill(_unit, 특수병과_극병_단양병);
		}
		string Get투척Text()
		{
			return pk::encode("투척");
		}
		string Get투척Desc()
		{
			return pk::encode("화계가 일정확률로 발생하는 선풍을 사용합니다.");
		}
		pk::array<pk::point_int> GetTargets투척()
		{
			pk::array<pk::point_int> targets;
			pk::force@ f = pk::get_force(_unit.get_force_id());
			auto range = pk::range(_src_pos, 1, 1);
			for (int i = 0; i < range.length; i++)
			{
				pk::hex_object@ obj = pk::get_hex_object(range[i]);
				if (obj == null)
					continue;
				if (_force != null && _force.get_id() == obj.get_force_id())
					continue;
				if(!checkHex극병(range[i]))
					continue;

				targets.insertLast(pk::point_int(range[i], 0));
			}
			return targets;

		}
		int GetChance투척(pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return 0;

			return callback202(_unit, dst_pos, target, 전법_선풍);
		}

		void execute투척(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;


			int nTactics = callback202(unit0, dst_pos, target, 전법_선풍);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), 전법_선풍, 크리티컬_근접);
			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, 유닛_전법_근접공격, bCri);
			}
			else
			{

				pk::damage_info di0;
				di0.src_pos = unit0.get_pos();
				di0.dst_pos = dst_pos;
				callback209(di0, unit0, 전법_선풍, dst_pos, 0, bCri ? 1 : 0, false);
				if (!금강불굴(di0, target))
				{
					array<pk::damage_info> dis;
					for (int i = 0; i < 6; i++)
					{
						pk::point pt = pk::get_neighbor_pos(unit0.get_pos(), i, 1);
						pk::hex_object@ obj = pk::get_hex_object(pt);
						if (obj == null)
							continue;
						if (!pk::is_enemy(unit0, obj))
							continue;

						pk::damage_info di2;
						di2.src_pos = unit0.get_pos();
						di2.dst_pos = pt;

						callback209(di2, unit0, 전법_선풍, pt, 0, bCri ? 1 : 0, false);
						dis.insertLast(di2);
					}
					pk::unit_anim(unit0, 유닛_전법_선풍, dis, dst_pos, 0, getString("투척"), 0);
					if (bCri)
						cutin(unit0);

					for (int i = 0; i < dis.length; i++)
					{
						pk::damage_info di = dis[i];
						pk::hex_object@ hex = pk::get_hex_object(di.dst_pos);
						if (hex == null)
							continue;
						addTroops(hex, di);
						if (pk::rand_bool(투척_화계_확률))
							pk::create_fire(hex.get_pos(), pk::rand(3) + 1, unit0, false);
						updateAfter(unit0, hex);
					}
					bool re=update(unit0, dst_pos, dis, 크리티컬_근접, bCri);
					if (re && 연전(unit0))
					{
						pk::unit_anim(unit0, 유닛_전법_선풍, dis, dst_pos, 0, getString("투척"), 0);
						if (bCri)
							cutin(unit0);

						for (int i = 0; i < dis.length; i++)
						{
							pk::damage_info di = dis[i];
							pk::hex_object@ hex = pk::get_hex_object(di.dst_pos);
							if (hex == null)
								continue;
							addTroops(hex, di);
							if (pk::rand_bool(투척_화계_확률))
								pk::create_fire(hex.get_pos(), pk::rand(3) + 1, unit0, false);
							updateAfter(unit0, hex);
						}
						update(unit0, dst_pos, dis, 크리티컬_근접, bCri);
					}
				}
			}

			update(unit0, target, dst_pos, dst_pos);
		}
		//단양병
		bool 투척Handler(pk::point dst_pos)
		{
			execute투척(_unit, dst_pos);
			return true;
		}


		bool IsVisible도참()
		{
			return 전체_전법_사용_테스트 || isSkill(_unit, 특수병과_극병_함진영);
		}
		string Get도참Text()
		{
			return pk::encode("도참");
		}
		string Get도참Desc()
		{
			return pk::encode("혼란이 일정확률로 발생하는 횡치를 사용합니다.");
		}
		pk::array<pk::point_int> GetTargets도참()
		{
			return GetTargets투척();
		}
		int GetChance도참(pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return 0;

			return callback202(_unit, dst_pos, target, 전법_횡치);
		}

		void execute도참(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			int nTactics = callback202(unit0, dst_pos, target, 전법_횡치);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), 전법_횡치, 크리티컬_근접);

			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, 유닛_전법_근접공격, bCri);
			}
			else
			{
				array<pk::damage_info> dis;
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, 전법_횡치, dst_pos, 0, bCri ? 1 : 0, false);
				if (!금강불굴(di, target))
				{
					dis.insertLast(di);

					array<pk::point> arr = get횡치pos(unit0.get_pos(), dst_pos);
					pk::unit@ u0 = getUnit(arr[0]);
					if (u0 != null && pk::is_enemy(unit0, u0))
					{
						pk::damage_info di1;
						di1.src_pos = unit0.get_pos();
						di1.dst_pos = arr[0];
						callback209(di1, unit0, 전법_횡치, arr[0], 0, bCri ? 1 : 0, false);
						dis.insertLast(di1);
					}
					pk::unit@ u1 = getUnit(arr[1]);
					if (u1 != null && pk::is_enemy(unit0, u1))
					{
						pk::damage_info di1;
						di1.src_pos = unit0.get_pos();
						di1.dst_pos = arr[1];
						callback209(di1, unit0, 전법_횡치, arr[1], 0, bCri ? 1 : 0, false);
						dis.insertLast(di1);
					}

					pk::unit_anim(unit0, 유닛_전법_횡치, { di }, dst_pos, 0, getString("도참"), 0);
					if (bCri)
						cutin(unit0);

					for (int i = 0; i < dis.length; i++)
					{
						pk::damage_info ddi = dis[i];
						pk::unit@ u = getUnit(ddi.dst_pos);
						if (u == null)
							continue;

						addTroops(u, ddi);
						updateAfter(unit0, u);
						pk::unit@ uu = getUnit(ddi.dst_pos);
						if (uu != null && prev_callback_221(unit0, u, bCri) > 0 && pk::rand_bool(도참_혼란_확률))
							updateChaos(uu, unit0);
					}
					bool re=update(unit0, dst_pos, dis, 크리티컬_근접, bCri);
					if (re && 연전(unit0))
					{
						pk::unit_anim(unit0, 유닛_전법_횡치, { di }, dst_pos, 0, getString("도참"), 0);
						if (bCri)
							cutin(unit0);

						for (int i = 0; i < dis.length; i++)
						{
							pk::damage_info ddi = dis[i];
							pk::unit@ u = getUnit(ddi.dst_pos);
							if (u == null)
								continue;

							addTroops(u, ddi);
							updateAfter(unit0, u);
							pk::unit@ uu = getUnit(ddi.dst_pos);
							if (uu != null && prev_callback_221(unit0, u, bCri) > 0 && pk::rand_bool(도참_혼란_확률))
								updateChaos(uu, unit0);
						}
					}
					update(unit0, dst_pos, dis, 크리티컬_근접, bCri);
				}
			}
			update(unit0, target, dst_pos, dst_pos);
		}

		//함진영
		bool 도참Handler(pk::point dst_pos)
		{
			execute도참(_unit, dst_pos);
			return true;
		}

		
		bool IsVisible멸파()
		{
			return 전체_전법_사용_테스트 || isSkill(_unit, 특수병과_기병_서량철기);
		}
		string Get멸파Text()
		{
			return pk::encode("멸파");
		}
		string Get멸파Desc()
		{
			return pk::encode("이동공격시 이동거리만큼 공격력이 증가합니다.");
		}
		pk::array<pk::point_int> GetTargets멸파()
		{
			pk::array<pk::point_int> targets;

			pk::force@ f = pk::get_force(_unit.get_force_id());

			auto range = pk::range(_src_pos, 1, 1);
			for (int i = 0; i < range.length; i++)
			{
				pk::hex_object@ obj = pk::get_hex_object(range[i]);
				if (obj == null)
					continue;
				if (_force != null && _force.get_id() == obj.get_force_id())
					continue;
				if(!checkHex기병(range[i]))
					continue;
				targets.insertLast(pk::point_int(range[i], 0));
			}
			return targets;

		}
		int GetChance멸파(pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return 0;

			return callback202(_unit, dst_pos, target, 전법_돌진);
		}

		void execute멸파(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			pk::point dst_pos2 = dst_pos;
			int nTactics = callback202(unit0, dst_pos, target, 전법_돌진);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), 전법_돌진, 크리티컬_근접);


			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, 유닛_전법_근접공격, bCri);
			}
			else
			{
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, 전법_돌진, dst_pos, 0, bCri ? 1 : 0, false);

				int dist = pk::min(멸파_공격_최대적용거리, pk::get_distance(unit0.get_pos(), _src_pos0));
				//pk::printf("dist {} x{},y{},x{},y{}\n", dist, unit0.get_pos().x, unit0.get_pos().y, _src_pos2.x, _src_pos2.y);
				di.troops_damage = di.troops_damage + float(di.troops_damage) * float(dist) * float(멸파_공격_증가량) / 100.0;

				if (!금강불굴(di, target))
				{
					int dir = pk::get_direction(unit0.get_pos(), dst_pos);
					pk::point ptA = pk::get_neighbor_pos(unit0.get_pos(), dir, 2);
					pk::point ptT = pk::get_neighbor_pos(dst_pos, dir, 2);
					di.src_move_pos = MoveThrough(unit0.get_pos(), ptA);
					//di.dst_move_pos = MovePoint(dst_pos, ptT);

					pk::unit_anim(unit0, 유닛_전법_돌진, { di }, dst_pos, 0, getString("멸파"), 0);
					if (bCri)
						cutin(unit0);

					pk::unit@ u = getUnit(di.dst_pos);
					if (u != null)
					{
						//pk::move(u, { MovePoint(dst_pos, ptT) });
						if (unit0.has_skill(특기_질주) && prev_callback_222(unit0, u) > 0)
							updateChaos(u, unit0);
					}

					pk::move(unit0, { MoveThrough(unit0.get_pos(), ptA) });

					addTroops(target, di);
					updateAfter(unit0, target);
					bool re=update(unit0, dst_pos, { di }, 크리티컬_근접, bCri);
					//dst_pos2 = di.dst_move_pos;
					if (re && 연전(unit0))
					{
						dir = pk::get_direction(unit0.get_pos(), dst_pos);
						pk::point ptA = pk::get_neighbor_pos(unit0.get_pos(), dir, 2);
						pk::point ptT = pk::get_neighbor_pos(dst_pos, dir, 2);
						di.src_move_pos = MoveThrough(unit0.get_pos(), ptA);
						//di.dst_move_pos = MovePoint(dst_pos, ptT);

						pk::unit_anim(unit0, 유닛_전법_돌진, { di }, dst_pos, 0, getString("멸파"), 0);
						if (bCri)
							cutin(unit0);

						pk::unit@ u = getUnit(di.dst_pos);
						if (u != null)
						{
							//pk::move(u, { MovePoint(dst_pos, ptT) });
							if (unit0.has_skill(특기_질주) && prev_callback_222(unit0, u) > 0)
								updateChaos(u, unit0);
						}

						pk::move(unit0, { MoveThrough(unit0.get_pos(), ptA) });

						addTroops(target, di);
						updateAfter(unit0, target);
						update(unit0, dst_pos, { di }, 크리티컬_근접, bCri);
					}
				}
			}

			update(unit0, target, dst_pos, dst_pos2);
		}

		//서량철기
		bool 멸파Handler(pk::point dst_pos)
		{
			execute멸파(_unit, dst_pos);
			return true;
		}


		bool IsVisible난도()
		{
			return 전체_전법_사용_테스트 || isSkill(_unit, 특수병과_기병_호표기);
		}
		string Get난도Text()
		{
			return pk::encode("난도");
		}
		string Get난도Desc()
		{
			return pk::encode("돌진 횡치를 사용합니다.");
		}
		pk::array<pk::point_int> GetTargets난도()
		{
			return GetTargets멸파();

		}
		int GetChance난도(pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return 0;

			return callback202(_unit, dst_pos, target, 전법_돌진);
		}

		void execute난도(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			int nTactics = callback202(unit0, dst_pos, target, 전법_돌진);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), 전법_돌진, 크리티컬_근접);


			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, 유닛_전법_근접공격, bCri);
			}
			else
			{
				array<pk::damage_info> dis;
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, 전법_돌진, dst_pos, 0, bCri ? 1 : 0, false);
				dis.insertLast(di);
				if (!금강불굴(di, target))
				{
					array<pk::point> arr = get횡치pos(unit0.get_pos(), dst_pos);
					pk::unit@ u0 = getUnit(arr[0]);
					if (u0 != null && pk::is_enemy(unit0, u0))
					{
						pk::damage_info di1;
						di1.src_pos = unit0.get_pos();
						di1.dst_pos = arr[0];
						callback209(di1, unit0, 전법_돌진, arr[0], 0, bCri ? 1 : 0, false);
						dis.insertLast(di1);
					}
					pk::unit@ u1 = getUnit(arr[1]);
					if (u1 != null && pk::is_enemy(unit0, u1))
					{
						pk::damage_info di1;
						di1.src_pos = unit0.get_pos();
						di1.dst_pos = arr[1];
						callback209(di1, unit0, 전법_돌진, arr[1], 0, bCri ? 1 : 0, false);
						dis.insertLast(di1);
					}

					pk::unit_anim(unit0, 유닛_전법_횡치, { di }, dst_pos, 0, getString("난도"), 0);
					if (bCri)
						cutin(unit0);

					for (int i = 0; i < dis.length; i++)
					{
						pk::damage_info ddi = dis[i];
						pk::unit@ u = getUnit(ddi.dst_pos);
						if (u == null)
							continue;

						addTroops(u, ddi);
						updateAfter(unit0, u);
						pk::unit@ uu = getUnit(ddi.dst_pos);
						if (uu != null)
						{
							if (i == 0)
							{
								if (unit0.has_skill(특기_질주) && prev_callback_222(unit0, uu) > 0)
									updateChaos(uu, unit0);
							}
							else
							{
								if (unit0.has_skill(특기_질주) && prev_callback_222(unit0, uu) > 0 && pk::rand_bool(난도_혼란_확률))
									updateChaos(uu, unit0);
							}
						}
					}
					bool re=update(unit0, dst_pos, dis, 크리티컬_근접, bCri);
					if (re && 연전(unit0))
					{
						pk::unit_anim(unit0, 유닛_전법_횡치, { di }, dst_pos, 0, getString("난도"), 0);
						if (bCri)
							cutin(unit0);

						for (int i = 0; i < dis.length; i++)
						{
							pk::damage_info ddi = dis[i];
							pk::unit@ u = getUnit(ddi.dst_pos);
							if (u == null)
								continue;

							addTroops(u, ddi);
							updateAfter(unit0, u);
							pk::unit@ uu = getUnit(ddi.dst_pos);
							if (uu != null)
							{
								if (i == 0)
								{
									if (unit0.has_skill(특기_질주) && prev_callback_222(unit0, uu) > 0)
										updateChaos(uu, unit0);
								}
								else
								{
									if (unit0.has_skill(특기_질주) && prev_callback_222(unit0, uu) > 0 && pk::rand_bool(난도_혼란_확률))
										updateChaos(uu, unit0);
								}
							}
						}
						update(unit0, dst_pos, dis, 크리티컬_근접, bCri);
					}
				}
			}
			update(unit0, target, dst_pos, dst_pos);
		}

		//호표기
		bool 난도Handler(pk::point dst_pos)
		{
			execute난도(_unit, dst_pos);
			return true;
		}


		bool IsVisible백마시()
		{
			return 전체_전법_사용_테스트 || isSkill(_unit, 특수병과_기병_백마의종);
		}
		string Get백마시Text()
		{
			return pk::encode("백마시");
		}
		string Get백마시Desc()
		{
			return pk::encode("난사를 사용합니다.");
		}
		pk::array<pk::point_int> GetTargets백마시()
		{
			return GetTargets대화시();

		}
		int GetChance백마시(pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return 0;

			return callback202(_unit, dst_pos, target, 전법_난사);
		}

		void execute백마시(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			int nTactics = callback202(unit0, dst_pos, target, 전법_난사);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), 전법_난사, 크리티컬_원거리);


			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, 유닛_전법_활공격, bCri);
			}
			else
			{
				array<pk::damage_info> dis;
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, 전법_난사, dst_pos, 0, bCri ? 1 : 0, false);
				dis.insertLast(di);


				if (!금강불굴(di, target))
				{
					for (int i = 0; i < 6; i++)
					{
						pk::point pt = pk::get_neighbor_pos(dst_pos, i, 1);
						pk::hex_object@ obj = pk::get_hex_object(pt);
						if (obj == null)
							continue;
						if (unit0.has_skill(특기_궁신) && !pk::is_enemy(unit0, obj))
							continue;


						pk::damage_info di2;
						di2.src_pos = unit0.get_pos();
						di2.dst_pos = pt;

						callback209(di2, unit0, 전법_난사, pt, 0, bCri ? 1 : 0, false);
						dis.insertLast(di2);
					}
					pk::unit_anim(unit0, 유닛_전법_난사, dis, dst_pos, 0, getString("백마시"), 0);
					//pk::unit_anim(unit0, 유닛_전법_난사, dis, dst_pos, 0, "", 0);
					if (bCri)
						cutin(unit0);

					for (int i = 0; i < dis.length; i++)
					{
						pk::damage_info di = dis[i];
						pk::unit@ obj = getUnit(di.dst_pos);
						if (obj == null)
							continue;
						addTroops(obj, di);
						updateAfter(unit0, obj);
					}

					bool re=update(unit0, dst_pos, dis, 크리티컬_원거리, bCri);
					if (re && 연전(unit0))
					{
						pk::unit_anim(unit0, 유닛_전법_난사, dis, dst_pos, 0, getString("백마시"), 0);
						if (bCri)
							cutin(unit0);

						for (int i = 0; i < dis.length; i++)
						{
							pk::damage_info di = dis[i];
							pk::unit@ obj = getUnit(di.dst_pos);
							if (obj == null)
								continue;
							addTroops(obj, di);
							updateAfter(unit0, obj);
						}
						update(unit0, dst_pos, dis, 크리티컬_원거리, bCri);
					}
				}
			}

			update(unit0, target, dst_pos, dst_pos);
		}

		//백마의종
		bool 백마시Handler(pk::point dst_pos)
		{
			execute백마시(_unit, dst_pos);
			return true;
		}

		bool IsVisible광폭()
		{
			return 전체_전법_사용_테스트 || isSkill(_unit, 특수병과_기병_비웅경기);
		}
		string Get광폭Text()
		{
			return pk::encode("광폭");
		}
		string Get광폭Desc()
		{
			return pk::encode("이동공격시 이동거리만큼 전법성공율이 증가합니다.");
		}
		pk::array<pk::point_int> GetTargets광폭()
		{
			return GetTargets멸파();

		}
		int GetChance광폭(pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return 0;

			int dist = pk::get_distance(_unit.get_pos(), dst_pos) - 1;
			int n = dist * 광폭_전법_증가량;
			int nTactics = callback202(_unit, dst_pos, target, 전법_돌진);
			return pk::min(100, nTactics + n);
		}


		void execute광폭(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			pk::point dst_pos2 = dst_pos;

			int dist = pk::get_distance(unit0.get_pos(), _src_pos0);
			int n = dist * 광폭_전법_증가량;

			int nTactics = callback202(unit0, dst_pos, target, 전법_돌진);
			bool bTactics = pk::rand_bool(pk::min(100, nTactics + n));
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), 전법_돌진, 크리티컬_근접);

			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, 유닛_전법_근접공격, bCri);
			}
			else
			{
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, 전법_돌진, dst_pos, 0, bCri ? 1 : 0, false);

				if (!금강불굴(di, target))
				{
					int dir = pk::get_direction(unit0.get_pos(), dst_pos);
					pk::point ptA = pk::get_neighbor_pos(unit0.get_pos(), dir, 2);
					pk::point ptT = pk::get_neighbor_pos(dst_pos, dir, 2);
					di.src_move_pos = MoveThrough(unit0.get_pos(), ptA);
					//di.dst_move_pos = MovePoint(dst_pos, ptT);
					pk::unit_anim(unit0, 유닛_전법_돌진, { di }, dst_pos, 0, getString("광폭"), 0);
					if (bCri)
						cutin(unit0);

					pk::unit@ u = getUnit(di.dst_pos);
					if (u != null)
					{
						//pk::move(u, { MovePoint(dst_pos, ptT) });
						if (unit0.has_skill(특기_질주) && prev_callback_222(unit0, u) > 0)
							updateChaos(u, unit0);
					}
					pk::move(unit0, { MoveThrough(unit0.get_pos(), ptA) });

					addTroops(target, di);
					updateAfter(unit0, target);
					bool re=update(unit0, dst_pos, { di }, 크리티컬_근접, bCri);
					//dst_pos2 = di.dst_move_pos;
					if (re && 연전(unit0))
					{
						dir = pk::get_direction(unit0.get_pos(), dst_pos);
						pk::point ptA = pk::get_neighbor_pos(unit0.get_pos(), dir, 2);
						pk::point ptT = pk::get_neighbor_pos(dst_pos, dir, 2);
						di.src_move_pos = MoveThrough(unit0.get_pos(), ptA);
						//di.dst_move_pos = MovePoint(dst_pos, ptT);
						pk::unit_anim(unit0, 유닛_전법_돌진, { di }, dst_pos, 0, getString("광폭"), 0);
						if (bCri)
							cutin(unit0);

						pk::unit@ u = getUnit(di.dst_pos);
						if (u != null)
						{
							//pk::move(u, { MovePoint(dst_pos, ptT) });
							if (unit0.has_skill(특기_질주) && prev_callback_222(unit0, u) > 0)
								updateChaos(u, unit0);
						}
						pk::move(unit0, { MoveThrough(unit0.get_pos(), ptA) });

						addTroops(target, di);
						updateAfter(unit0, target);
						update(unit0, dst_pos, { di }, 크리티컬_근접, bCri);
					}
				}
			}

			update(unit0, target, dst_pos, dst_pos2);
		}
		//비웅경기 
		bool 광폭Handler(pk::point dst_pos)
		{
			execute광폭(_unit, dst_pos);
			return true;
		}


		string getString(string str)
		{
			switch (pk::rand(4))
			{
			case 0:
				return pk::encode(pk::format("이것이 {}다",str));
			case 1:
				return pk::encode(pk::format("{} 힘을 보여주마", str));
			case 2:
				return pk::encode(pk::format("하핫 어떠냐 {} 위력이", str));
			case 3:
				return pk::encode(pk::format("{} 에는 맞설수 없다", str));
			default:
				break;
			}
			return "";
		}

		array<pk::point> get횡치pos(pk::point spos, pk::point dpos)
		{
			array<pk::point> pts;
			int dir = pk::get_direction(spos, dpos);
			switch (dir)
			{
			case 방향_남:
				pts.insertLast(pk::get_neighbor_pos(spos, 방향_남동, 1));
				pts.insertLast(pk::get_neighbor_pos(spos, 방향_남서, 1));
				break;
			case 방향_남동:
				pts.insertLast(pk::get_neighbor_pos(spos, 방향_북동, 1));
				pts.insertLast(pk::get_neighbor_pos(spos, 방향_남, 1));
				break;
			case 방향_북동:
				pts.insertLast(pk::get_neighbor_pos(spos, 방향_북, 1));
				pts.insertLast(pk::get_neighbor_pos(spos, 방향_남동, 1));
				break;
			case 방향_북:
				pts.insertLast(pk::get_neighbor_pos(spos, 방향_북서, 1));
				pts.insertLast(pk::get_neighbor_pos(spos, 방향_북동, 1));
				break;
			case 방향_북서:
				pts.insertLast(pk::get_neighbor_pos(spos, 방향_남서, 1));
				pts.insertLast(pk::get_neighbor_pos(spos, 방향_북, 1));
				break;
			case 방향_남서:
				pts.insertLast(pk::get_neighbor_pos(spos, 방향_북서, 1));
				pts.insertLast(pk::get_neighbor_pos(spos, 방향_남, 1));
				break;
			default:
				break;
			}
			return pts;
		}

		pk::point MoveThrough(pk::point pos0, pk::point pos)
		{
			if (pk::get_hex_object(pos) != null)
				return pos0;
			else
				return pos;
		}
		pk::point MovePoint(pk::point pos0, pk::point pos)
		{
			int dir = pk::get_direction(pos0, pos);

			pk::point pt0 = pk::get_neighbor_pos(pos0, dir, 1);
			if (pk::get_hex_object(pt0) != null)
				return pos0;
			if (pt0.x == pos.x && pt0.y == pos.y)
			{
				return pt0;
			}
			pk::point pt1 = pk::get_neighbor_pos(pos0, dir, 2);
			if (pk::get_hex_object(pt1) != null)
			{
				return pt0;
			}
			else
			{
				return pt1;
			}


		}
		void Move(pk::unit@ u, pk::point pos)
		{
			int dir = pk::get_direction(u.get_pos(), pos);

			pk::point pt0 = pk::get_neighbor_pos(u.get_pos(), dir, 1);
			if (pk::get_hex_object(pt0) != null)
				return;

			if (pt0.x == pos.x && pt0.y == pos.y)
			{
				pk::set_pos(u,  pt0);
				pk::move(u, { pt0 });
				return;
			}

			pk::point pt1 = pk::get_neighbor_pos(u.get_pos(), dir, 2);
			if (pk::get_hex_object(pt1) != null)
			{
				pk::set_pos(u, pt0);
				pk::move(u, { pt0 });
			}
			else
			{
				pk::set_pos(u, pt1);
				pk::move(u, { pt1 });
			}
				
		}

		int getChaosTime(pk::unit@ u)
		{
			int max = pk::max(u.attr.stat[부대능력_통솔], u.attr.stat[부대능력_지력]);
			int time = pk::max((1 - (max - 50) / 40.0), 0.0) * 2 + 2;
			return time;
		}
		int getMaxAttackDistance(pk::unit@ u)
		{
			pk::force@ f = pk::get_force(u.get_force_id());
			switch (u.weapon)
			{
			case 병기_창:
			case 병기_극:
			case 병기_군마:
				if (pk::has_tech(f, 기교_기사) || u.has_skill(특기_백마))
					return 2;
				return  1;
			case 병기_노:
				return pk::has_tech(f, 기교_강노) ? 3 : 2;
			default:
				break;
			}
			return 0;
		}

		void updateAssist(pk::unit@ attacker, pk::hex_object@ target, pk::point dst_pos)
		{
			pk::unit@ targetu = target!=null ? getUnit(target.get_pos()) : null;
			if (targetu == null)
				return;

			array<pk::point> arr = pk::range(dst_pos, 1, 4);
			for (int i = 0; i < arr.length; i++)
			{
				pk::point pt = arr[i];
				pk::unit@ u = getUnit(pt);
				if(u==null)
					continue;
				if(u.get_id() == attacker.get_id())
					continue;
				if(u.get_force_id()!=attacker.get_force_id())
					continue;

				int dist = pk::get_distance(u.get_pos(), dst_pos);
				if (getMaxAttackDistance(u) < dist)
					continue;

				int n = callback200(u, attacker, target);
				if(!pk::rand_bool(n))
					continue;

				pk::damage_info di;
				di.src_pos = u.get_pos();
				di.dst_pos = dst_pos;
				prev_callback_210(di, u, dst_pos);


				string str = "";
				switch (pk::rand(3))
				{
				case 0:str = "이것도 받아라";break;
				case 1:str = "이건 어떠냐";break;
				case 2:str = "아직 끝나지 않았다";break;
				}
				pk::unit_anim(u, dist > 1 ? 1 : 0, {di}, dst_pos, 0, pk::encode(str), 0);

				string str2 = "";
				switch (pk::rand(3))
				{
				case 0:str = pk::format("역시 {} 님",pk::decode(pk::get_name(pk::get_person(u.leader))));break;
				case 1:str = "하핫 고맙소";break;
				case 2:str = "이거지~";break;
				}
				pk::say(str2, pk::get_person(attacker.leader), attacker);

				addTroops(targetu, di.troops_damage);
				updateAfter(u, target);
			}
		}

		void attackFail(pk::unit@ attacker, pk::hex_object@ target, pk::point dst_pos,int type,bool bCri)
		{
			bool bCri2 = type == 유닛_전법_활공격 ? 크리티컬_원거리 : 크리티컬_근접;
			int r = pk::rand(100);
			if (r <= 전법실패시_일반공격_확률)
			{
				pk::damage_info di;
				di.src_pos = attacker.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, attacker, 0, dst_pos, 0, bCri ? 1 : 0, false);
				pk::unit_anim(attacker, type, { di }, dst_pos, 0, pk::encode("칫 이것밖엔.."), 0);
				if (!금강불굴(di, target))
				{
					addTroops(target, di);
					updateAfter(attacker, target);
					update(attacker, dst_pos, { di }, bCri2,false);
					if (연전(attacker))
					{
						pk::unit_anim(attacker, type, { di }, dst_pos, 0, pk::encode("칫 이것밖엔.."), 0);
						addTroops(target, di);
						updateAfter(attacker, target);
						update(attacker, dst_pos, { di }, bCri2,false);
					}
				}
				
			}
			else if (r > 전법실패시_일반공격_확률 and r < 전법실패시_일반공격_확률 + 전법실패시_일반공격_무데미지_확률)
			{
				pk::damage_info di;
				di.src_pos = attacker.get_pos();
				di.dst_pos = dst_pos;
				di.troops_damage = 0;
				//prev_callback_202전법성공(di, attacker, type, dst_pos, 0, bCri ? 1 : 0, false);

				pk::unit_anim(attacker, type, { di }, dst_pos, 0, pk::encode("통하지 않는가.."), 0);
				addTroops(target, di);
				updateAfter(attacker, target);
				update(attacker, dst_pos, { di }, bCri2, false);
			}
			else
			{
				int dist = pk::get_distance(attacker.get_pos(), dst_pos);
				if (getMaxAttackDistance(target) < dist)
					return;
				
				pk::damage_info di;
				di.src_pos = dst_pos;
				di.dst_pos = attacker.get_pos();
				callback209(di, target, 1, attacker.get_pos(), 0, bCri ? 1 : 0, false);

				pk::unit_anim(target, type, { di }, attacker.get_pos(), 1, pk::encode("반격이다"), 0);
				addTroops(attacker, di);
				updateAfter(target, attacker);
				update(attacker, dst_pos, { di }, bCri2,false,true);
			}
		}
		bool updateAfter(pk::unit@ attacker, pk::hex_object@ target)
		{
			if (target == null)
				return false;

			pk::unit@ targetU = getUnit(target.get_pos());
			if(targetU!=null && targetU.troops == 0)
			{
				int dist = pk::get_distance(attacker.get_pos(), target.get_pos());
				//pk::printf("kill start\n");
				pk::kill(targetU, attacker, dist == 1, attacker.weapon == 병기_극);
				//pk::printf("kill end\n");
				if (attacker.has_skill(특기_앙양)) 
					pk::add_energy(attacker, int(pk::core::skill_constant(attacker, 특기_앙양)), true);
				return false;
			}
			else 
			{
				pk::building@ b = target;
				if(b.hp==0)
					pk::kill(b);
				return false;
			}
			return true;

		}

		void update맹장(pk::unit@ attacker, pk::hex_object@ target, pk::point dest0)
		{
			pk::unit@ u = target!=null ? getUnit(target.get_pos()) : null;
			if (u == null || !attacker.has_skill(특기_맹장) || u.has_skill(특기_호위))
				return;
			if (target.get_pos().x == dest0.x && target.get_pos().y == dest0.y)
				return;

			int maxValue = int(pk::core::skill_constant(attacker, 특기_맹장));
			if (u.member[0] >= 0 && u.member[0] < 무장_끝 && pk::rand_bool(maxValue))
				injury(pk::get_person(u.member[0]));
			if (u.member[1] >= 0 && u.member[1] < 무장_끝 && pk::rand_bool(maxValue))
				injury(pk::get_person(u.member[1]));
			if (u.member[2] >= 0 && u.member[2] < 무장_끝 && pk::rand_bool(maxValue))
				injury(pk::get_person(u.member[2]));
		}
		void injury(pk::person@ p)
		{
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
			pk::person@ kunshu = force!=null ? pk::get_person(force.kunshu) : null;
			if (kunshu != null)
			{
				string str = pk::format("\x1b[2x{}\x1b[0x군 \x1b[2x{}\x1b[0x,\x1b[29x{}\x1b[0x 상태",getName(kunshu),getName(p) ,strType);
				pk::history_log(p.get_pos(), force != null ? force.color : -1, pk::encode(str));
			}
		}


		string getName(pk::force@ f)
		{
			if (f == null)
				return "null";
			return getName(pk::get_person(f.kunshu));
		}
		string getName(pk::object@ obj)
		{
			return obj!=null ? pk::decode(pk::get_name(obj)) : "null";
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

		void addTroops(pk::hex_object@ obj, pk::damage_info di, bool bEffect = true)
		{
			addTroops(obj, di.troops_damage, bEffect);
		}
		void addTroops(pk::hex_object@ obj,int value,bool bEffect = true)
		{
			pk::unit@ u;
			pk::building@ b;
			pk::city@ c;
			switch (obj.get_type_id())
			{
			case 11: @u = obj;pk::add_troops(u, -value, bEffect);break;
			case 5: case 6:case 7: case 8:
				@b = obj; pk::add_troops(b, -value, bEffect); break;
			default:
				break;
			}
		}


		void updateChaos(pk::unit@ u, pk::unit@ u2)
		{
			//u.status = 부대상태_혼란;
			//u.status_timer = getChaosTime(u);
			//pk::play_se(2);

			pk::set_status(u, u2, 부대상태_혼란, getChaosTime(u),true);
		}
		bool update(pk::unit@ u, pk::point dst_pos, array<pk::damage_info>@ dis,bool bRanged,bool bCri,bool success = true, bool bCounter = false)
		{
			pk::unit@ attacker = u;
			pk::add_stat_exp(attacker, 무장능력_무력, success ? 4 : 1);
			pk::add_kouseki(attacker, success ? 100 : 10);
			
			int type = -1;
			switch (attacker.weapon)
			{
			case 병기_창:type = 병종_창병; break;
			case 병기_노:type = 병종_노병; break;
			case 병기_극:type = 병종_극병; break;
			case 병기_군마:type = 병종_기병; break;
			default:
				break;
			}
			if (type != -1)
			{
				
				if (attacker.leader >= 0 && attacker.leader < 무장_끝)
				{
					pk::person@ p0 = pk::get_person(attacker.leader);
					pk::add_heishu_exp(p0, type, success ? 4 : 1);
				}
				if (attacker.member[1] >= 0 && attacker.member[1] < 무장_끝)
				{
					pk::person@ p0 = pk::get_person(attacker.member[1]);
					pk::add_heishu_exp(p0, type, success ? 4 : 1);
				}
				if (attacker.member[2] >= 0 && attacker.member[2] < 무장_끝)
				{
					pk::person@ p0 = pk::get_person(attacker.member[2]);
					pk::add_heishu_exp(p0, type, success ? 4 : 1);
				}
			}
			pk::unit@ targetU = getUnit(dst_pos);
			if (targetU != null)
			{
				pk::add_stat_exp(targetU, 무장능력_통솔, 1);
				
				int type2 = -1;
				switch (targetU.weapon)
				{
				case 병기_창:type2 = 병종_창병; break;
				case 병기_노:type2 = 병종_노병; break;
				case 병기_극:type2 = 병종_극병; break;
				case 병기_군마:type2 = 병종_기병; break;
				case 병기_정란:case 병기_투석:case 병기_충차:case 병기_목수:type2 = 병종_병기; break;
				case 병기_주가:case 병기_누선:case 병기_투함:type2 = 병종_수군;break;
				default:
					break;
				}
				if (type2 != -1)
				{
					if (targetU.leader >= 0 && targetU.leader < 무장_끝)
					{
						pk::person@ p0 = pk::get_person(targetU.leader);
						pk::add_heishu_exp(p0, type, 1);
					}
					if (targetU.member[1] >= 0 && targetU.member[1] < 무장_끝)
					{
						pk::person@ p0 = pk::get_person(targetU.member[1]);
						pk::add_heishu_exp(p0, type, 1);
					}
					if (targetU.member[2] >= 0 && targetU.member[2] < 무장_끝)
					{
						pk::person@ p0 = pk::get_person(targetU.member[2]);
						pk::add_heishu_exp(p0, type, 1);
					}
				}
			}

			if (!bCounter)
			{
				int sum = 0;
				for (int i = 0; i < dis.length; i++)
				{
					pk::damage_info di = dis[i];
					pk::point ptDst = di.dst_move_pos;
					if (ptDst.x == -1 && ptDst.y == -1)
						ptDst = di.dst_pos;

					pk::unit@ dstU = getUnit(ptDst);
					if (dstU == null)
						continue;
					if (u.has_skill(특기_소탕))
						pk::add_energy(dstU, -int(pk::core::skill_constant(u, 특기_소탕)), true);
					if (u.has_skill(특기_위풍))
						pk::add_energy(dstU, -int(pk::core::skill_constant(u, 특기_위풍)), true);

					sum += di.troops_damage;
				}
				if (!bRanged && u.has_skill(특기_심공))
					pk::add_troops(u, float(pk::core::skill_constant(u, 특기_심공)) * sum, true);
			}

			if (success && targetU!=null && pk::rand_bool(전법_일기토_확률))
			{
				@_scene_attackerUnit = attacker;
				@_scene_targetUnit = targetU;
				@_scene_attacker = pk::get_person(attacker.leader);
				@_scene_target = pk::get_person(targetU.leader);
				pk::message_box(pk::encode("적장을 찾았다"), _scene_attacker);
				pk::message_box(pk::encode("좋다 후회하게 될것이다"), _scene_target);
				pk::scene(pk::scene_t(scene_일기토));
			}

			@targetU = getUnit(dst_pos);
			if (success && targetU != null && u.weapon == 병기_군마)
			{
				pk::person@ l = pk::get_person(u.leader);
				bool bDie = false;
				if (targetU.leader >= 0 && targetU.leader < 무장_끝)
				{
					pk::person@ p0 = pk::get_person(targetU.leader);
					int n=prev_callback_203기병전법사망(l, p0, 전법_돌진, bCri);
					if (pk::rand_bool(n)) 
					{
						pk::message_box(pk::encode("분하다.."), p0);
						pk::kill(p0, l, targetU, null, 0);
						bDie = true;
					}
				}
				if (!bDie && targetU.member[1] >= 0 && targetU.member[1] < 무장_끝)
				{
					pk::person@ p0 = pk::get_person(targetU.member[1]);
					int n=prev_callback_203기병전법사망(l, p0, 전법_돌진, bCri);
					if (pk::rand_bool(n))
					{
						pk::kill(p0, l, targetU, null, 0);
						pk::message_box(pk::encode("분하다.."), p0);
						bDie = true;
					}
				}
				if (!bDie && targetU.member[2] >= 0 && targetU.member[2] < 무장_끝)
				{
					pk::person@ p0 = pk::get_person(targetU.member[2]);
					int n = prev_callback_203기병전법사망(l, p0, 전법_돌진, bCri);
					if (pk::rand_bool(n))
					{
						pk::kill(p0, l, targetU, null, 0);
						pk::message_box(pk::encode("분하다.."), p0);
						bDie = true;
					}
				}
			}

			return getUnit(dst_pos) != null;
		}

		int _duel_result = 0;
		pk::person@ _scene_attacker = null;
		pk::person@ _scene_target = null;
		pk::unit@ _scene_attackerUnit = null;
		pk::unit@ _scene_targetUnit = null;

		void scene_일기토()
		{
			//pk::printf("tatical 1:1 {},{}------------------\n",getName(_scene_attacker), getName(_scene_target));
			bool b0 = pk::is_player_controlled(_scene_attackerUnit);
			bool b1 = pk::is_player_controlled(_scene_targetUnit);
			_duel_result = pk::duel(_scene_attackerUnit, _scene_targetUnit, _scene_attacker, null, null, _scene_target, null, null, b0,b1, 0, b0 || b1).first;
		}

		void update(pk::unit@ u, pk::hex_object@ target, pk::point dst_pos,pk::point dst_pos2)
		{
			updateAssist(u, target, dst_pos2);
			update맹장(u, target, dst_pos);
			pk::add_energy(u, -전법_기력, true);
			u.action_done = true;
		}
		bool 금강불굴(pk::damage_info di,pk::hex_object@ target)
		{
			pk::unit@ u = target!=null ? getUnit(target.get_pos()) : null;
			if (u == null)
				return false;

			if (u.has_skill(특기_금강))
			{
				int val = int(pk::core::skill_constant(u, 특기_금강, 0));
				int ratio = int(pk::core::skill_constant(u, 특기_금강, 1));
				if (di.troops_damage < val && pk::rand_bool(ratio))
				{
					pk::play_se(7);
					return true;
				}
			}
			if (u.has_skill(특기_불굴))
			{
				int val = int(pk::core::skill_constant(u, 특기_금강, 0));
				int ratio = int(pk::core::skill_constant(u, 특기_금강, 1));
				if (u.troops < val && pk::rand_bool(ratio))
				{
					pk::play_se(7);
					return true;
				}
			}
			return false;
		}
		bool 연전(pk::unit@ u)
		{
			int val = int(pk::core::skill_constant(u, 특기_연전));
			bool b = bool(pk::core["초특기연전"]);
			return b && u.has_skill(특기_연전) && pk::rand_bool(val);
		}
		void cutin(pk::unit@ u)
		{
			if (!pk::is_player_controlled(u))
				return;
			pk::face_cutin(u);
		}
		pk::unit@ getUnit(pk::point pos)
		{
			return pk::is_valid_pos(pos) ? pk::get_unit(pos) : null;
		}
		bool checkHex노병(pk::unit@ u, pk::point pt)
		{
			if (!u.has_skill(특기_사수) && pk::get_hex(pt).terrain == 지형_숲)
				return false;
			int h = pk::get_hex(pt).terrain;
			if (h == 지형_강 || h == 지형_바다 || h == 지형_산)
				return false;
			return true;
		}
		bool checkHex창병(pk::point pt)
		{
			int h = pk::get_hex(pt).terrain;
			if (h == 지형_강 || h == 지형_바다 || h == 지형_산 || h == 지형_모래)
				return false;
			return true;
		}
		bool checkHex극병(pk::point pt)
		{
			int h = pk::get_hex(pt).terrain;
			if (h == 지형_강 || h == 지형_바다 || h == 지형_산)
				return false;
			return true;
		}
		bool checkHex기병(pk::point pt)
		{
			switch (pk::get_hex(pt).terrain)
			{
			case 지형_대로:
			case 지형_초원:
			case 지형_땅:
			case 지형_모래:
				return true;
			}
			return false;
		}


	}//Main
	Main main;
}

