/*
@만든이: 크래픽스
@Update: 2023.9.8,최초배포
@Update: 2023.9.9,소속이 없는경우에 잘못판단하는 버그수정
@Update: 2023.9.10,인덱스에러수정
@Update: 2023.9.13,주악에러수정
@Update: 2023.9.15,v2,명성,미도,부호등 효과추가.
@Update: 2023.9.18,유저세력에 있는 무장만 컬러표시.
@Update: 2024.5.2, 전능0이하일때 처리
@Update: 2024.5.17, 건물데미지도 방어력 적용
*/

namespace 인연효과_Story
{
	const int 효과_주악_소_값 = 5;
	const int 효과_주악_중_값 = 10;
	const int 효과_주악_대_값 = 15;
	
	const int 효과_전능상승_소_값 = 1;
	const int 효과_전능상승_중_값 = 2;
	const int 효과_전능상승_대_값 = 3;

	const int 효과_공적상승_소_값 = 10000;
	const int 효과_공적상승_중_값 = 20000;
	const int 효과_공적상승_대_값 = 30000;

	const int 효과_전법_공격_소_값 = 10;
	const int 효과_전법_공격_중_값 = 15;
	const int 효과_전법_공격_대_값 = 20;

	const int 효과_전법_방어_소_값 = 10;
	const int 효과_전법_방어_중_값 = 15;
	const int 효과_전법_방어_대_값 = 20;

	const int 효과_공격상승_소_값 = 10;
	const int 효과_공격상승_중_값 = 15;
	const int 효과_공격상승_대_값 = 20;
	const int 효과_방어상승_소_값 = 10;
	const int 효과_방어상승_중_값 = 15;
	const int 효과_방어상승_대_값 = 20;

	const int 효과_보좌_소_값 = 20;
	const int 효과_보좌_중_값 = 40;
	const int 효과_보좌_대_값 = 60;

	const int 효과_계략_소_값 = 10;
	const int 효과_계략_중_값 = 15;
	const int 효과_계략_대_값 = 20;

	const int 효과_계략방어_소_값 = 10;
	const int 효과_계략방어_중_값 = 15;
	const int 효과_계략방어_대_값 = 20;

	const int 효과_인접기력감소_값 = 5;
	const int 효과_인접병사감소_값 = 3;

	const float 효과_부호_소_값 = 1.2;
	const float 효과_부호_중_값 = 1.35;
	const float 효과_부호_대_값 = 1.5;

	const float 효과_미도_소_값 = 1.2;
	const float 효과_미도_중_값 = 1.35;
	const float 효과_미도_대_값 = 1.5;

	const float 효과_명성_소_값 = 1.2;
	const float 효과_명성_중_값 = 1.35;
	const float 효과_명성_대_값 = 1.5;

	const float 효과_계략_기력_감소_값 = 0.5;

	const int 효과_인접_교란_값 = 5;
	const int 효과_인접_위보_값 = 5;
	const int 효과_인접_화계_값 = 5;

	const int 효과_통솔_상승_소_값 = 3;
	const int 효과_통솔_상승_중_값 = 6;
	const int 효과_통솔_상승_대_값 = 10;
	const int 효과_무력_상승_소_값 = 3;
	const int 효과_무력_상승_중_값 = 6;
	const int 효과_무력_상승_대_값 = 10;
	const int 효과_지력_상승_소_값 = 3;
	const int 효과_지력_상승_중_값 = 6;
	const int 효과_지력_상승_대_값 = 10;
	const int 효과_정치_상승_소_값 = 3;
	const int 효과_정치_상승_중_값 = 6;
	const int 효과_정치_상승_대_값 = 10;
	const int 효과_매력_상승_소_값 = 3;
	const int 효과_매력_상승_중_값 = 6;
	const int 효과_매력_상승_대_값 = 10;

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

	const int KEY = pk::hash("인연효과");
	const int KEY_EXPORT = pk::hash("인연효과_Export");
	
	class Main
	{
		pk::func100_t@ prev_callback_100;
		pk::func200_t@ prev_callback_200;
		pk::func209_t@ prev_callback_209;
		pk::func202_t@ prev_callback_202;
		pk::func206_t@ prev_callback_206;
		pk::func155_t@ prev_callback_155;
		pk::func150_t@ prev_callback_150;
		pk::func151_t@ prev_callback_151;
		pk::func205_t@ prev_callback_205;
		pk::func207_t@ prev_callback_207;
		pk::func201_t@ prev_callback_201;
		pk::func222_t@ prev_callback_222;
		pk::func220_t@ prev_callback_220;
		pk::func203_t@ prev_callback_203;
		pk::func164_t@ prev_callback_164;
		pk::func211_t@ prev_callback_211;



		Main()
		{
			@prev_callback_209 = cast<pk::func209_t@>(pk::get_func(209));
			pk::reset_func(209);
			pk::set_func(209, pk::func209_t(callback209부대공격));                // 202 전법 성공 확률

			@prev_callback_202 = cast<pk::func202_t@>(pk::get_func(202));
			pk::reset_func(202);
			pk::set_func(202, pk::func202_t(callback202전법성공확률));

			@prev_callback_200 = cast<pk::func200_t@>(pk::get_func(200));
			pk::reset_func(200);
			pk::set_func(200, pk::func200_t(callback200지원공격확률));

			@prev_callback_206 = cast<pk::func206_t@>(pk::get_func(206));
			pk::reset_func(206);
			pk::set_func(206, pk::func206_t(callback206계략성공확률));                // 202 전법 성공 확률

			@prev_callback_155 = cast<pk::func155_t@>(pk::get_func(155));
			pk::reset_func(155);
			pk::set_func(155, pk::func155_t(callback155월별충성도));                // 202 전법 성공 확률

			@prev_callback_150 = cast<pk::func150_t@>(pk::get_func(150));
			pk::reset_func(150);
			pk::set_func(150, pk::func150_t(callback150금수입));                // 150 금 수입

			@prev_callback_151 = cast<pk::func151_t@>(pk::get_func(151));
			pk::reset_func(151);
			pk::set_func(151, pk::func151_t(callback151병량수입));                // 151 병량 수입

			@prev_callback_100 = cast<pk::func100_t@>(pk::get_func(100));
			pk::reset_func(100);
			pk::set_func(100, pk::func100_t(callback100징병));                // 150 금 수입

			@prev_callback_205 = cast<pk::func205_t@>(pk::get_func(205));
			pk::reset_func(205);
			pk::set_func(205, pk::func205_t(callback205계략소비기력));                

			@prev_callback_207 = cast<pk::func207_t@>(pk::get_func(207));
			pk::reset_func(207);
			pk::set_func(207, pk::func207_t(callback207계략크리티컬));

			@prev_callback_201 = cast<pk::func201_t@>(pk::get_func(201));
			pk::reset_func(201);
			pk::set_func(201, pk::func201_t(callback201공격크리티컬));

			//@prev_callback_222 = cast<pk::func222_t@>(pk::get_func(222));
			//pk::reset_func(222);
			//pk::set_func(222, pk::func222_t(callback222질주혼란확률));

			@prev_callback_220 = cast<pk::func220_t@>(pk::get_func(220));
			pk::reset_func(220);
			pk::set_func(220, pk::func220_t(callback220포박확률));

			@prev_callback_203 = cast<pk::func203_t@>(pk::get_func(203));
			pk::reset_func(203);
			pk::set_func(203, pk::func203_t(callback203기병전법사망));

			@prev_callback_164 = cast<pk::func164_t@>(pk::get_func(164));
			pk::reset_func(164);
			pk::set_func(164, pk::func164_t(callback164부대혼란효과));

			@prev_callback_211 = cast<pk::func211_t@>(pk::get_func(211));
			pk::reset_func(211);
			pk::set_func(211, pk::func211_t(callback211));


			
			pk::bind(174, pk::trigger174_t(부대행동완료));
			pk::bind(107, pk::trigger107_t(onNewDay));
			pk::bind(111, pk::trigger111_t(onTurnStart));
			pk::bind(102, pk::trigger102_t(Init));
			pk::bind(105, pk::trigger105_t(SaveData));


			
			pk::menu_item item인연효과;
			item인연효과.menu = 2;
			item인연효과.is_enabled = pk::menu_item_is_enabled_t(Is인연효과Enabled);
			item인연효과.get_text = pk::menu_item_get_text_t(Get인연효과Text);
			item인연효과.get_desc = pk::menu_item_get_desc_t(Get인연효과Desc);
			item인연효과.handler = pk::menu_item_handler_t(인연효과Handler);
			pk::add_menu_item(item인연효과);

			
		}
		void Init()
		{
			LoadData();
			bool b = false;

			for (int i = 0; i < 인연리스트.length; i++)
			{
				GroupInfo@ gi = 인연리스트[i];
				if (gi.b) 
				{
					b = true;
					break;
				}
			}
			if (!b)
				onNewDay();

			exportData();
		}

		void LoadData()
		{
			for (int i = 0; i < 인연리스트.length; i++)
			{
				GroupInfo@ gi = 인연리스트[i];
				gi.idsApply = {};
				gi.membersApply.clear();
				@gi.force = null;
				gi.b = false;
			}


			int count = int(pk::load(KEY, 0, 0));
			int li = 1;
			for (int i = 0; i < count; i++)
			{
				GroupInfo@ gi = 인연리스트[i];
				int bi = int(pk::load(KEY, li++, 0));
				gi.b = bi == 1;
				@gi.force = pk::get_force(int(pk::load(KEY, li++, 0)));
				int count2 = int(pk::load(KEY, li++, 0));
				for (int k = 0; k < count2; k++)
				{
					gi.idsApply.insertLast(int(pk::load(KEY, li++, 0)));
				}
				int count3 = int(pk::load(KEY, li++, 0));
				for (int k = 0; k < count3; k++)
				{
					pk::person@ p = pk::get_person(int(pk::load(KEY, li++, 0)));
					if(p==null)
						continue;
					gi.membersApply.add(p);
				}
			}
		}
		void SaveData(int file_id)
		{
			pk::store(KEY, 0, 인연리스트.length);
			int si = 1;
			for (int i = 0; i < 인연리스트.length; i++)
			{
				GroupInfo@ gi = 인연리스트[i];
				pk::store(KEY, si++, gi.b ? 1 : 0);
				pk::store(KEY, si++, gi.force!=null ? gi.force.get_id() : -1);
				pk::store(KEY, si++, gi.idsApply.length);
				for (int k = 0; k < gi.idsApply.length; k++)
				{
					pk::store(KEY, si++, gi.idsApply[k]);
				}
				pk::store(KEY, si++, gi.membersApply.count);
				for (int k = 0; k < gi.membersApply.count; k++)
				{
					pk::store(KEY, si++, gi.membersApply[k].get_id());
				}
			}
		}
		void exportData()
		{
			pk::store(KEY_EXPORT, 0, 인연리스트.length);
			int si = 1;
			for (int i = 0; i < 인연리스트.length; i++)
			{
				GroupInfo@ gi = 인연리스트[i];
				pk::store(KEY_EXPORT, si++, gi.b ? 1 : 0);
				pk::store(KEY_EXPORT, si++, gi.force != null ? gi.force.get_id() : -1);
				pk::store(KEY_EXPORT, si++, gi.idsApply.length);
				for (int k = 0; k < gi.idsApply.length; k++)
				{
					pk::store(KEY_EXPORT, si++, gi.idsApply[k]);
				}
				pk::store(KEY_EXPORT, si++, gi.membersApply.count);
				for (int k = 0; k < gi.membersApply.count; k++)
				{
					pk::store(KEY_EXPORT, si++, gi.membersApply[k].get_id());
				}
			}

		}

		bool Is인연효과Enabled()
		{
			return true;
		}
		string Get인연효과Text()
		{
			return pk::encode("인연효과확인");
		}
		string Get인연효과Desc()
		{
			return pk::encode("세력별 인연효과 적용 상황을 확인합니다.");
		}
		bool 인연효과Handler()
		{
			pk::force@ force = pk::get_force(pk::get_current_turn_force_id());
			int si = 0;
			GroupInfo@ selected = null;
			while (true)
			{
				array<string> itemArr;
				array<GroupInfo@> itemArr2;
				int count = pk::min(인연리스트.length, si + 4);
				if (si == 0)
					itemArr.insertLast(pk::encode("종료"));
				else
					itemArr.insertLast(pk::encode("뒤로"));
				for (int i = si; i < count; i++)
				{
					GroupInfo@ gi = 인연리스트[i];
					string str2 = gi.b ? "\x1b[1x{}\x1b[0x" : "{}";
					string str = pk::format(str2, gi.name) + ",";
					str = str + (gi.force != null ? (getNameForce(gi.force) + "군") : "없음");
					for (int k = 0; k < gi.members.count; k++)
					{
						bool b = gi.members[k].get_force_id() == force.id;
						if(b)
							str = str + ","+pk::format("\x1b[1x{}\x1b[0x", getName(gi.members[k]));
						else
							str = str + "," + pk::format("{}", getName(gi.members[k]));

					}
					itemArr.insertLast(pk::encode(str));
					itemArr2.insertLast(gi);
				}
				if (si + 4 >= 인연리스트.length)
					itemArr.insertLast(pk::encode("종료"));
				else
					itemArr.insertLast(pk::encode("다음"));

				int choose = pk::choose(pk::encode("확인하십시오"), itemArr);
				if (choose == itemArr.length - 1)
				{
					si = si + 4;
					if (si >= 인연리스트.length)
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
			}
			return true;
		}

		string getNameForce(pk::force@ f)
		{
			pk::person@ kunshu = pk::get_person(f.kunshu);
			return getName(kunshu);
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

		int callback150금수입(pk::city@ city)
		{
			int gold = prev_callback_150(city);
			pk::force@ force = pk::get_force(city.get_force_id());
			if (force == null)
				return gold;

			float maxRatio = 1.0;
			pk::list<pk::person@> persons = pk::get_person_list(pk::city_to_building(city),pk::mibun_flags(신분_군주,신분_태수,신분_도독,신분_일반));
			for (int i = 0; i < persons.count; i++)
			{
				pk::person@ p = persons[i];
				if (checkGroup(p, 효과_부호_소))
					maxRatio = 효과_부호_소_값;
				if (checkGroup(p, 효과_부호_중))
					maxRatio = 효과_부호_중_값;
				if (checkGroup(p, 효과_부호_대))
					maxRatio = 효과_부호_대_값;
			}
			return maxRatio * gold;
		}
		int callback151병량수입(pk::city@ city)
		{
			int food = prev_callback_151(city);
			pk::force@ force = pk::get_force(city.get_force_id());
			if (force == null)
				return food;

			float maxRatio = 1.0;
			pk::list<pk::person@> persons = pk::get_person_list(pk::city_to_building(city), pk::mibun_flags(신분_군주, 신분_태수, 신분_도독, 신분_일반));
			for (int i = 0; i < persons.count; i++)
			{
				pk::person@ p = persons[i];
				if (checkGroup(p, 효과_미도_소))
					maxRatio = 효과_미도_소_값;
				if (checkGroup(p, 효과_미도_중))
					maxRatio = 효과_미도_중_값;
				if (checkGroup(p, 효과_미도_대))
					maxRatio = 효과_미도_대_값;
			}
			return maxRatio * food;

		}
		int callback100징병(pk::building@ building, const pk::detail::arrayptr<pk::person@>& in actors)
		{
			int amount = prev_callback_100(building, actors);
			pk::force@ force = pk::get_force(building.get_force_id());
			if (force == null)
				return amount;

			
			float maxRatio = 1.0;
			for (int i = 0; i < actors.length; i++)
			{
				pk::person@ p = actors[i];
				if (checkGroup(p, 효과_명성_소))
					maxRatio = 효과_명성_소_값;
				if (checkGroup(p, 효과_명성_중))
					maxRatio = 효과_명성_중_값;
				if (checkGroup(p, 효과_명성_대))
					maxRatio = 효과_명성_대_값;
			}
			return maxRatio * amount;
		}

		int callback205계략소비기력(pk::unit@ src, int strategy_id)
		{
			int n = prev_callback_205(src, strategy_id);
			if (checkGroup(src, 효과_계략_기력_감소))
				n = n * 효과_계략_기력_감소_값;
			return n;
		}
		int callback207계략크리티컬(pk::unit@ src, const pk::point& in src_pos, const pk::point& in dst_pos, int strategy_id)
		{
			int n = prev_callback_207(src, src_pos, dst_pos, strategy_id);
			if (checkGroup(src, 효과_계략_크리티컬_항상성공))
				n = 100;
			return n;
		}
		bool callback201공격크리티컬(pk::unit@ attacker, pk::hex_object@ target, int tactics_id, bool ranged)
		{
			bool b=prev_callback_201(attacker,target,tactics_id,ranged);
			if (checkGroup(attacker, 효과_공격_크리티컬_항상성공))
				b = true;
			return b;
		}
		int callback222질주혼란확률(pk::unit@ attacker, pk::unit@ target)
		{
			int n = prev_callback_222(attacker, target);
			if (n > 0)
				return n;

			//if (checkGroup(attacker, 효과_질주_대) && pk::rand_bool(효과_질주_대_값))
			//	return 2;
			//if (checkGroup(attacker, 효과_질주_중) && pk::rand_bool(효과_질주_중_값))
			//	return 2;
			//if (checkGroup(attacker, 효과_질주_소) && pk::rand_bool(효과_질주_소_값))
			//	return 2;

			return 0;
		}

		void callback220포박확률(const pk::destroy_info& in info, pk::list<pk::person@>& captured, pk::list<pk::person@>& escaped, bool tactics_bonus)
		{
			prev_callback_220(info, captured, escaped, tactics_bonus);
			if (captured.count == 0)
				return;
			if (!info.releasable)
				return;


			int index = -1;
			for (int i = 0; i < captured.count; i++)
			{
				pk::person@ p = captured[i];
				if (!checkGroup(p, 효과_포박_불가))
					continue;

				index = i;
				break;
			}
			if (index != -1)
				captured.remove_at(index);
		}
		int callback203기병전법사망(pk::person@ attacker, pk::person@ target, int tactics_id, bool critical)
		{
			int n = prev_callback_203(attacker, target, tactics_id, critical);
			if (checkGroup(target, 효과_기병_전법_사망_불가))
				n = 0;
			return n;
		}
		int callback164부대혼란효과(pk::unit@ unit)
		{
			int n = prev_callback_164(unit);
			if (checkGroup(unit, 효과_소병력_혼란_불가))
			{
				n = 0;
			}
			return n;
		}
		int callback155월별충성도(pk::building@ building, pk::person@ person)
		{
			int n = prev_callback_155(building, person);


			pk::force@ force = pk::get_force(person.get_force_id());

			array<GroupInfo@> arr = getForces(force, { 효과_세력인정효과 });
			if (arr.length > 0)
				n = 0;


			return n;
		}
		int callback200지원공격확률(pk::unit@ assister, pk::unit@ attacker, pk::unit@ target)
		{
			int n = prev_callback_200(assister,attacker,target);
			if (checkGroup(assister, 효과_보좌_대)) 
				n = pk::min(n + 효과_보좌_대_값, 100);
			else if (checkGroup(assister, 효과_보좌_중))
				n = pk::min(n + 효과_보좌_중_값, 100);
			else if (checkGroup(assister, 효과_보좌_소))
				n = pk::min(n + 효과_보좌_소_값, 100);

			return n;
		}
		pk::int_bool callback206계략성공확률(pk::unit@ src, const pk::point& in src_pos, const pk::point& in dst_pos, int strategy_id)
		{
			pk::int_bool re = prev_callback_206(src,src_pos,dst_pos,strategy_id);

			if (checkGroup(src, 효과_계략_대) && re.second == false) 
			{
				re.first = pk::min(re.first + 효과_계략_대_값, 100);
				pk::printf("consipracy {}\n", re.first);

			}
				
			else if (checkGroup(src, 효과_계략_중) && re.second == false)
				re.first = pk::min(re.first + 효과_계략_중_값, 100);
			else if (checkGroup(src, 효과_계략_소) && re.second == false)
				re.first = pk::min(re.first + 효과_계략_소_값, 100);

			if (checkGroup(src, 효과_경국) && src.has_skill(특기_경국) && re.second == false)
				re.first = pk::min(re.first * 2,100);


			pk::unit@ u = pk::get_unit(dst_pos);
			if (u != null && re.second == false) 
			{
				if (checkGroup(u, 효과_명경) && (strategy_id == 계략_교란 || strategy_id == 계략_위보) ||
					checkGroup(u, 효과_통찰))
				{
					re.first = 0;
					re.second = true;
				}
				else if (checkGroup(u, 효과_계략방어_대))
					re.first = pk::max(re.first - 효과_계략방어_대_값, 0);
				else if (checkGroup(u, 효과_계략방어_중))
					re.first = pk::max(re.first - 효과_계략방어_중_값, 0);
				else if (checkGroup(u, 효과_계략방어_소))
					re.first = pk::max(re.first - 효과_계략방어_소_값, 0);
			}

			return re;

		}
		int callback202전법성공확률(pk::unit@ attacker, const pk::point& in pos, pk::hex_object@ target, int tactics_id)
		{
			int n = prev_callback_202(attacker, pos, target, tactics_id);

			if (checkGroup(attacker, 효과_전법반드시성공))
				return 100;
			if (checkGroup(attacker, 효과_전법_공격_대)) 
				n = pk::min(n + 효과_전법_공격_대_값, 100);
			else if (checkGroup(attacker, 효과_전법_공격_중))
				n = pk::min(n + 효과_전법_공격_중_값, 100);
			else if (checkGroup(attacker, 효과_전법_공격_소))
				n = pk::min(n + 효과_전법_공격_소_값, 100);

			if (checkGroup(attacker, 효과_전법_방어_대))
				n = pk::max(n - 효과_전법_방어_대_값, 0);
			else if (checkGroup(attacker, 효과_전법_방어_중))
				n = pk::max(n - 효과_전법_방어_중_값, 0);
			else if (checkGroup(attacker, 효과_전법_방어_소))
				n = pk::max(n - 효과_전법_방어_소_값, 0);

			return n;
		}
		void callback209부대공격(pk::damage_info& info, pk::unit@ attacker, int tactics_id, const pk::point& in target_pos, int type, int critical, bool ambush)
		{
			prev_callback_209(info, attacker, tactics_id, target_pos, type, critical, ambush);

			if (checkGroup(attacker, 효과_공격상승_대)) 
				info.troops_damage = info.troops_damage + info.troops_damage * 효과_공격상승_대_값 / 100.0;
			else if (checkGroup(attacker, 효과_공격상승_중))
				info.troops_damage = info.troops_damage + info.troops_damage * 효과_공격상승_중_값 / 100.0;
			else if (checkGroup(attacker, 효과_공격상승_소))
				info.troops_damage = info.troops_damage + info.troops_damage * 효과_공격상승_소_값 / 100.0;

			pk::unit@ u = pk::get_unit(target_pos);
			if (u != null)
			{
				if (checkGroup(u, 효과_방어상승_대))
					info.troops_damage = info.troops_damage - info.troops_damage * 효과_방어상승_대_값 / 100.0;
				else if (checkGroup(u, 효과_방어상승_중))
					info.troops_damage = info.troops_damage - info.troops_damage * 효과_방어상승_중_값 / 100.0;
				else if (checkGroup(u, 효과_방어상승_소))
					info.troops_damage = info.troops_damage - info.troops_damage * 효과_방어상승_소_값 / 100.0;
			}

		}

		void callback211(pk::damage_info& info, pk::building@ attacker, pk::hex_object@ target)
		{
			prev_callback_211(info, attacker, target);
			pk::unit@ u = pk::is_valid_pos(target.get_pos()) ? pk::get_unit(target.get_pos()) : null;
			if (u != null)
			{
				if (checkGroup(u, 효과_방어상승_대))
					info.troops_damage = info.troops_damage - info.troops_damage * 효과_방어상승_대_값 / 100.0;
				else if (checkGroup(u, 효과_방어상승_중))
					info.troops_damage = info.troops_damage - info.troops_damage * 효과_방어상승_중_값 / 100.0;
				else if (checkGroup(u, 효과_방어상승_소))
					info.troops_damage = info.troops_damage - info.troops_damage * 효과_방어상승_소_값 / 100.0;
			}
		}




		void 부대행동완료(pk::unit@ unit)
		{
			if (unit == null)
				return;

			if (checkGroup(unit, 효과_인접기력감소)) 
			{
				for (int i = 0; i < 방향_끝; i++)
				{
					pk::point pt = pk::get_neighbor_pos(unit.get_pos(), i, 1);
					pk::unit@ u = pk::get_unit(pt);
					if(u==null || !pk::is_enemy(unit,u))
						continue;

					pk::add_energy(u, -효과_인접기력감소_값, true);
				}
			}
			if (checkGroup(unit, 효과_인접병사감소))
			{
				for (int i = 0; i < 방향_끝; i++)
				{
					pk::point pt = pk::get_neighbor_pos(unit.get_pos(), i, 1);
					pk::unit@ u = pk::get_unit(pt);
					if (u == null || !pk::is_enemy(unit, u))
						continue;

					pk::add_troops(u, - u.troops*효과_인접병사감소_값/100.0, true);
					if (u.troops == 0)
						pk::kill(u, unit, true, unit.weapon == 병기_극);

				}
			}
			if (checkGroup(unit, 효과_인접_교란) && pk::rand_bool(효과_인접_교란_값))
			{
				for (int i = 0; i < 방향_끝; i++)
				{
					pk::point pt = pk::get_neighbor_pos(unit.get_pos(), i, 1);
					pk::unit@ u = pk::get_unit(pt);
					if (u == null || !pk::is_enemy(unit, u))
						continue;
					if(u.status != 부대상태_통상)
						continue;

					pk::set_status(u, unit,부대상태_혼란,pk::rand(3)+1);
					break;
				}
			}
			if (checkGroup(unit, 효과_인접_위보) && pk::rand_bool(효과_인접_위보_값))
			{
				for (int i = 0; i < 방향_끝; i++)
				{
					pk::point pt = pk::get_neighbor_pos(unit.get_pos(), i, 1);
					pk::unit@ u = pk::get_unit(pt);
					if (u == null || !pk::is_enemy(unit, u))
						continue;
					if (u.status != 부대상태_통상)
						continue;

					pk::set_status(u, unit, 부대상태_위보, pk::rand(3) + 1);
					break;
				}
			}
			if (checkGroup(unit, 효과_인접_화계))
			{
				for (int i = 0; i < 방향_끝; i++)
				{
					pk::point pt = pk::get_neighbor_pos(unit.get_pos(), i, 1);
					pk::unit@ u = pk::get_unit(pt);
					if (u == null || !pk::is_enemy(unit, u))
						continue;
					if(!pk::rand_bool(효과_인접_화계_값))
						continue;
					if(pk::is_on_fire(pt))
						continue;
					pk::create_fire(pt, pk::rand(3) + 1, unit);
				}
			}

		}

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
		GroupInfo@ getGroup(string name)
		{
			for (int i = 0; i < 인연리스트.length; i++)
			{
				GroupInfo@ gi = 인연리스트[i];
				if (gi.name == name)
					return gi;
			}
			return null;
		}

		array<GroupInfo@> getForces(pk::unit@ unit, array<int> ids)
		{
			pk::force@ f = pk::get_force(unit.get_force_id());
			array<GroupInfo@> arr = getForces(f, ids);
			if (arr.length == 0)
				return arr;


			array<GroupInfo@> arr2;
			for (int i = 0; i < arr.length; i++)
			{
				GroupInfo@ gi = arr[i];
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
					arr2.insertLast(gi);
			}
			return arr2;
		}

		array<GroupInfo@> getForces(pk::force@ force,array<int> ids)
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
					if(bFound)
						gis.insertLast(gi);
				}
			}
			return gis;
		}

		void apply전능(pk::list<pk::person@> persons, int value)
		{
			for (int i = 0; i < persons.count; i++)
			{
				pk::person@ p = persons[i];
				for (int k = 0; k < 무장능력_끝; k++)
				{
					int a = p.stat_exp[k] + value * int(pk::core["무장.능력상승필요경험치"]);
					if (a < 0)
						a = 0;
					p.stat_exp[k] = a;
				}
				p.update();
			}
		}
		void apply무장능력(pk::list<pk::person@> persons, int type,int value)
		{
			for (int i = 0; i < persons.count; i++)
			{
				pk::person@ p = persons[i];
				int a = p.stat_exp[type] + value * int(pk::core["무장.능력상승필요경험치"]);
				if (a < 0)
					a = 0;
				p.stat_exp[type] = a;
				p.update();
			}
		}

		void apply공적(pk::list<pk::person@> persons, int value)
		{
			for (int i = 0; i < persons.count; i++)
			{
				pk::person@ p = persons[i];
				p.kouseki += value;
			}

		}
		void apply적성(pk::list<pk::person@> persons, int value)
		{
			for (int i = 0; i < persons.count; i++)
			{
				pk::person@ p = persons[i];
				for (int k = 0; k < 병종_끝; k++)
				{
					p.tekisei[k] = p.tekisei[k] + value;
				}
			}
		}

		void onNewDay()
		{
			for (int i = 0; i < 인연리스트.length; i++)
			{
				GroupInfo@ gi = 인연리스트[i];
				pk::force@ force = null;
				for (int k = 0; k < gi.members.count; k++)
				{
					pk::person@ p = gi.members[k];
					if (force != null && force.get_id() != p.get_force_id()) 
					{
						@force = null;
						break;
					}
					pk::force@ f = pk::get_force(p.get_force_id());
					if (f == null)
					{
						@force = null;
						break;
					}
					@force = f;
				}
				if ((force == null || (gi.force!=null && force.get_id() != gi.force.get_id())) && gi.b)
				{
					for (int k = 0; k < gi.idsApply.length; k++)
					{
						int id = gi.idsApply[k];
						switch (id)
						{
						case 효과_전능상승_소:apply전능(gi.membersApply, -효과_전능상승_소_값); break;
						case 효과_전능상승_중:apply전능(gi.membersApply, -효과_전능상승_중_값); break;
						case 효과_전능상승_대:apply전능(gi.membersApply, -효과_전능상승_대_값); break;
						case 효과_공적상승_소:apply공적(gi.membersApply, -효과_공적상승_소_값); break;
						case 효과_공적상승_중:apply공적(gi.membersApply, -효과_공적상승_중_값); break;
						case 효과_공적상승_대:apply공적(gi.membersApply, -효과_공적상승_대_값); break;
						case 효과_전적성상승:apply적성(gi.membersApply, -1); break;
						case 효과_통솔_상승_소:apply무장능력(gi.membersApply, 무장능력_통솔, -효과_통솔_상승_소_값); break;
						case 효과_통솔_상승_중:apply무장능력(gi.membersApply, 무장능력_통솔, -효과_통솔_상승_중_값); break;
						case 효과_통솔_상승_대:apply무장능력(gi.membersApply, 무장능력_통솔, -효과_통솔_상승_대_값); break;
						case 효과_무력_상승_소:apply무장능력(gi.membersApply, 무장능력_무력, -효과_무력_상승_소_값); break;
						case 효과_무력_상승_중:apply무장능력(gi.membersApply, 무장능력_무력, -효과_무력_상승_중_값); break;
						case 효과_무력_상승_대:apply무장능력(gi.membersApply, 무장능력_무력, -효과_무력_상승_대_값); break;
						case 효과_지력_상승_소:apply무장능력(gi.membersApply, 무장능력_지력, -효과_지력_상승_소_값); break;
						case 효과_지력_상승_중:apply무장능력(gi.membersApply, 무장능력_지력, -효과_지력_상승_중_값); break;
						case 효과_지력_상승_대:apply무장능력(gi.membersApply, 무장능력_지력, -효과_지력_상승_대_값); break;
						case 효과_정치_상승_소:apply무장능력(gi.membersApply, 무장능력_정치, -효과_정치_상승_소_값); break;
						case 효과_정치_상승_중:apply무장능력(gi.membersApply, 무장능력_정치, -효과_정치_상승_중_값); break;
						case 효과_정치_상승_대:apply무장능력(gi.membersApply, 무장능력_정치, -효과_정치_상승_대_값); break;
						case 효과_매력_상승_소:apply무장능력(gi.membersApply, 무장능력_매력, -효과_매력_상승_소_값); break;
						case 효과_매력_상승_중:apply무장능력(gi.membersApply, 무장능력_매력, -효과_매력_상승_중_값); break;
						case 효과_매력_상승_대:apply무장능력(gi.membersApply, 무장능력_매력, -효과_매력_상승_대_값); break;
						default:
							break;
						}
					}
					string str2 = "";
					for (int j = 0; j < gi.membersApply.count; j++)
						str2 = str2 + "," + pk::format("\x1b[1x{}\x1b[0x", getName(gi.membersApply[j]));

					gi.membersApply.clear();
					string str = pk::format("\x1b[2x{}군\x1b[0x, \x1b[29x{}\x1b[0x 상실{}",getNameForce(gi.force),gi.name,str2);
					pk::history_log(pk::point(), gi.force.color, pk::encode(str));
				}
				
				if ((force != null && !gi.b) || (gi.force!=null && force!=null && force.get_id() != gi.force.get_id()))
				{
					for (int k = 0; k < gi.ids.length; k++)
					{
						int id = gi.ids[k];
						switch (id)
						{
						case 효과_전능상승_소:apply전능(gi.members, 효과_전능상승_소_값); break;
						case 효과_전능상승_중:apply전능(gi.members, 효과_전능상승_중_값); break;
						case 효과_전능상승_대:apply전능(gi.members, 효과_전능상승_대_값); break;
						case 효과_공적상승_소:apply공적(gi.members, 효과_공적상승_소_값); break;
						case 효과_공적상승_중:apply공적(gi.members, 효과_공적상승_중_값); break;
						case 효과_공적상승_대:apply공적(gi.members, 효과_공적상승_대_값); break;
						case 효과_전적성상승:apply적성(gi.members, 1); break;
						case 효과_통솔_상승_소:apply무장능력(gi.members, 무장능력_통솔, 효과_통솔_상승_소_값); break;
						case 효과_통솔_상승_중:apply무장능력(gi.members, 무장능력_통솔, 효과_통솔_상승_중_값); break;
						case 효과_통솔_상승_대:apply무장능력(gi.members, 무장능력_통솔, 효과_통솔_상승_대_값); break;
						case 효과_무력_상승_소:apply무장능력(gi.members, 무장능력_무력, 효과_무력_상승_소_값); break;
						case 효과_무력_상승_중:apply무장능력(gi.members, 무장능력_무력, 효과_무력_상승_중_값); break;
						case 효과_무력_상승_대:apply무장능력(gi.members, 무장능력_무력, 효과_무력_상승_대_값); break;
						case 효과_지력_상승_소:apply무장능력(gi.members, 무장능력_지력, 효과_지력_상승_소_값); break;
						case 효과_지력_상승_중:apply무장능력(gi.members, 무장능력_지력, 효과_지력_상승_중_값); break;
						case 효과_지력_상승_대:apply무장능력(gi.members, 무장능력_지력, 효과_지력_상승_대_값); break;
						case 효과_정치_상승_소:apply무장능력(gi.members, 무장능력_정치, 효과_정치_상승_소_값); break;
						case 효과_정치_상승_중:apply무장능력(gi.members, 무장능력_정치, 효과_정치_상승_중_값); break;
						case 효과_정치_상승_대:apply무장능력(gi.members, 무장능력_정치, 효과_정치_상승_대_값); break;
						case 효과_매력_상승_소:apply무장능력(gi.members, 무장능력_매력, 효과_매력_상승_소_값); break;
						case 효과_매력_상승_중:apply무장능력(gi.members, 무장능력_매력, 효과_매력_상승_중_값); break;
						case 효과_매력_상승_대:apply무장능력(gi.members, 무장능력_매력, 효과_매력_상승_대_값); break;
						default:
							break;
						}
					}
					gi.idsApply = gi.ids;
					gi.membersApply = gi.members;

					string str2 = "";
					for (int j = 0; j < gi.members.count; j++)
						str2 = str2 + "," + pk::format("\x1b[1x{}\x1b[0x", getName(gi.members[j]));

					string str = pk::format("\x1b[2x{}군\x1b[0x, \x1b[1x{}\x1b[0x 획득{}", getNameForce(force), gi.name,str2);
					pk::history_log(pk::point(), force.color, pk::encode(str));
				}

				@gi.force = force;
				gi.b = force != null;

			}

			exportData();
		}
		void onTurnStart(pk::force@ force)
		{
			array<GroupInfo@> gis = getForces(force, { 효과_주악_대,효과_주악_중, 효과_주악_소});
			if (gis.length == 0)
				return;

			for (int i = 0; i < gis.length; i++)
			{
				GroupInfo@ gi = gis[i];
				array<pk::unit@> units;
				for (int k = 0; k < gi.members.count; k++)
				{
					pk::person@ p = gi.members[k];
					pk::unit@ u = pk::get_unit(p.get_pos());
					if(u==null)
						continue;
					if (units.findByRef(u) == -1)
						units.insertLast(u);
				}

				for (int k = 0; k < gi.ids.length; k++)
				{
					int id = gi.ids[k];
					if(id != 효과_주악_소 && id != 효과_주악_중 && id != 효과_주악_대)
						continue;

					int value = id == 효과_주악_소 ? 효과_주악_소_값 : id == 효과_주악_중 ? 효과_주악_중_값 : 효과_주악_대_값;
					for (int j = 0; j < units.length; j++)
					{
						pk::unit@ u = units[j];
						pk::add_energy(u, value, true);
					}
				}
			}
		}
		
	}
	Main main;
}
