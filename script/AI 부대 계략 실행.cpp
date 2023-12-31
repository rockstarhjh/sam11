/*
	@제작 : masterpiecek
	@내용 : AI부대가 근처에 일정조건을 충족하는 대상부대 존재 시 해당부대를 상대로 계략 교란 및 위보를 실행합니다.


	[ AI부대 계략실행 ]

	1. 계략 실행부대가 계략을 실행하기 위해 충족해야할 조건들 (괄호 안의 내용은 설정 기본값)
	 1) 실행부대로부터 기준거리(8칸) 이내에 적부대 존재
	 2) 실행부대의 부대기력이 기준값(30) 이상
	 3) 실행부대의 특정 부대능력이 기준값(70) 미만
	 4) 실행부대의 부대적성이 기준값(적성A) 미만
	 5) 실행부대가 병기별로 특정 특기를 미보유 (유저설정 참고)

	2. 계략 실행부대가 계략을 걸 대상부대 검색
	 1) 계략 대상부대의 조건 확인 (괄호 안의 내용은 설정 기본값)
	  (1) 대상부대의 부대병력이 기준값(1500) 이상
	  (2) 대상부대의 부대기력이 기준값(20) 이상
	  (3) 대상부대의 특정 부대능력이 기준값(40) 이상
	  (4) 대상부대의 부대적성이 기준값(적성C) 초과
	  (5) 실행부대의 대상부대에 대한 계략 성공확률 조건을 충족 (유저설정 참고)
	   - 모드별로 조건이 달라짐 : 모드1(성공이 보장되는 대상에게 시도), 모드2(확률이 보장되는 대상에게 시도)
	 2) 대상부대 간 비교
	  - 상위조건부터 비교하며, 동일한 경우 하위조건을 비교
	  (1) 대상부대의 공성전 방어조건 : 공성전 방어조건을 충족하는 대상부대를 우선
	    - 도시의 내구 및 병력 조건 충족 시 도시와 근접한 공성병기 부대를 우선
	  (2) 대상부대의 인접부대 : 실행부대가 연환특기 보유 시 대상부대의 인접좌표에 실행부대의 적부대가 존재하는 경우를 우선
	  (3) 대상부대의 부대능력(공격력) : 높을수록 우선
	  (4) 대상부대의 부대능력(지력) : 높을수록 우선
	  (5) 대상부대의 부대병력 : 많을수록 우선
	  (6) 실행부대와 대상부대의 거리 : 가까울수록 우선
	  (7) 대상부대의 부대적성 : 높을수록 우선
	  (8) 대상부대의 부대기력 : 클수록 우선
	  (9) 실행부대의 대상부대에 대한 계략성공확률 : 높을수록 우선 (단, 확률보장대상 모드에 한함)
	  (10) 대상부대의 부대구성원 : 많을수록 우선
	  (11) 대상부대 주변에 존재하는 실행부대의 적군 부대수(5칸 이내) : 적을수록 우선
	  (12) 대상부대 주변에 존재하는 실행부대의 적군 병사수(5칸 이내) : 적을수록 우선
	  (13) 대상부대 주변에 존재하는 실행부대의 아군 부대수(5칸 이내) : 많을수록 우선
	  (14) 대상부대 주변에 존재하는 실행부대의 아군 병사수(5칸 이내) : 많을수록 우선

	3. 실행부대가 계략 실행조건을 충족하고 대상부대가 존재하는 경우 계략 실행부대가 이동이 필요한지 확인
	 1) 대상부대가 실행부대의 계략범위 밖에 존재하는 경우
	 2) 실행부대가 불지형 위에 존재하는 경우
	 3) 실행부대가 특정시설의 범위 안에 위치하는 경우
	  - 시설의 자동공격 및 함정의 범위 확인
	 4) 실행부대가 출진부대인 경우

	4. 계략 실행부대가 이동이 필요한 경우 이동 후보좌표 검색
	 1) 이동 후보좌표의 조건 확인
	  (1) 지형피해(난소행군 미연구 시)를 입지 않는 좌표
	  (2) 불지형이 아닌 좌표
	  (3) 시설범위 밖의 좌표
	   - 시설의 자동공격 및 함정의 범위 확인
	 2) 후보좌표 간 비교
	  - 대상부대로부터 먼 좌표 우선

	5. 위의 모든 조건들을 충족한 경우 실행부대가 대상부대를 상대로 계략 시전
	 - 조건에 걸린 경우에는 해당 AI부대의 기존 임무를 수행
	 1) 이동이 필요한 경우에는 이동 가능한 좌표가 존재하는 경우 이동 후 계략 시전
	 2) 이동이 필요없는 경우에는 본래 위치에서 계략 실행
*/

namespace AI부대_계략실행
{

/// ============================================ < 유저 설정 > ============================================


/// [ 일반 설정 ]


	/// AI부대의 계략실행 기능 적용여부 설정
	const array<bool> AI부대_계략실행_야전부대_적용 = {/*플레이어 위임군단*/true, /*컴퓨터*/true};
	const array<bool> AI부대_계략실행_출진부대_적용 = {/*플레이어 위임군단*/true, /*컴퓨터*/true};


	/// 적장세력 부대 적용여부 설정
	const bool 적장세력_적용 = true;


	/// 컴퓨터 세력 부대의 경우 플레이어 세력의 부대만을 대상으로 계략을 실행하도록 할지 여부 설정
	const bool 컴퓨터부대_계략실행대상_플레이어한정 = false;


	/// 실행부대가 실행할 계략 목록
	// 입력된 항목의 순서대로 계략을 시도 (계략 항목의 순서 수정 및 삭제만 가능, 새로운 항목 추가 금지)
	const array<int> 실행계략_일람 = {계략_교란, 계략_위보};


	/// 실행부대가 계략을 실행하기 위해 대상부대를 검색할 실행부대로부터의 기준거리 (기준거리 이내의 대상부대만을 검색)
	const int 계략실행_기준거리 = 8;


	/// 실행부대의 대상부대에 대한 계략 성공확률 관련 설정 모드

	// 모드 1 : 성공보장대상 (성공확률을 충족하여 성공이 확실한 부대를 대상으로만 계략 시전, 실패할 부대를 대상으로는 시도하지 않음)
	// 모드 2 : 확률보장대상 (성공확률이 설정한 기준확률보다 높은 부대만을 대상으로 계략 시전, 따라서 실패할 수도 있음)
	const array<int> 성공확률_적용모드 = {/*플레이어 위임군단*/2, /*컴퓨터*/2};

	// 모드2 관련설정 : 대상부대에 대한 계략의 성공확률이 설정값 미만인 경우 시도하지 않음 ('모드2' 설정에만 적용)
	const array<int> 실행기준_성공확률 = {/*플레이어 위임군단*/75, /*컴퓨터*/75};


	/// 대상부대 근처의 실행부대가 이동할 후보좌표 검색 시 설정

	// 후보 이동좌표가 독천 피해, 벼랑길 피해를 입는 지형인 경우 후보좌표에서 제외킬지 여부
	const array<bool> 후보이동좌표_검색시_지형피해좌표_제외 = {/*플레이어 위임군단*/true, /*컴퓨터*/true};

	// 후보 이동좌표가 불지형인 경우 후보좌표에서 제외킬지 여부
	const array<bool> 후보이동좌표_검색시_불지형좌표_제외 = {/*플레이어 위임군단*/true, /*컴퓨터*/true};

	// 후보 이동좌표가 특정시설의 범위 내에 있는 경우 후보좌표에서 제외킬지 여부
	const array<bool> 후보이동좌표_검색시_시설범위좌표_제외 = {/*플레이어 위임군단*/true, /*컴퓨터*/true};


	/// 실행부대가 회피할 대상시설 설정
	// 1. 현재 위치에서의 실행부대 이동 필요여부 확인 시 
	// 2. 후보 이동좌표에서의 시설범위 확인 시
	const array<array<int>> 회피대상_시설 =
	{
		/*고정시설*/ {시설_도시, 시설_관문, 시설_항구},
		/*군사시설*/ {시설_진, 시설_요새, 시설_성채, 시설_궁노, 시설_연노로, 시설_투석대, 시설_석병팔진, 시설_본거지1, 시설_본거지2},
		/* 장애물 */ {},
		/*  함정  */ {시설_불씨, 시설_화염종, 시설_업화종, 시설_화선, 시설_화구, 시설_화염구, 시설_업화구, 시설_낙석},
		/*내정시설*/ {}
	};


/// -------------------------------------------------------------------------------------------------------


/// [ 실행부대 관련 조건 ]


	/// 실행부대의 부대종류가 수송부대인 경우 계략을 실행할지 여부
	const array<bool> 실행부대_수송부대_적용 = {/*플레이어 위임군단*/false, /*컴퓨터*/false};


	/// 실행부대의 기력이 기준값 미만인 경우 계략을 실행하지 않음 (기력이 계략 소비기력 미만인 경우는 당연히 불가능)
	const array<bool> 실행부대_기력조건_적용 = {/*플레이어 위임군단*/true, /*컴퓨터*/true};
	const array<int> 실행부대_기준기력 = {/*플레이어 위임군단*/30, /*컴퓨터*/30};


	/// 실행부대의 특정 부대능력이 기준값 이상인 경우 계략을 실행하지 않음
	const array<bool> 실행부대_능력조건_적용 = {/*플레이어 위임군단*/true, /*컴퓨터*/true};
	const int 실행부대_적용능력 = 부대능력_공격;
	const array<int> 실행부대_기준능력 = {/*플레이어 위임군단*/70, /*컴퓨터*/70};


	/// 실행부대의 적성이 기준값 이상인 경우 계략을 실행하지 않음
	// 참고 : 적성 S 이후의 적성을 사용하는 경우 번호로 입력해야 함 (적성 C의 번호가 0이고 이후 적성 한 단계 상승 시마다 번호 +1)
	const array<bool> 실행부대_적성조건_적용 = {/*플레이어 위임군단*/true, /*컴퓨터*/true};
	const array<int> 실행부대_기준적성 = {/*플레이어 위임군단*/적성_A, /*컴퓨터*/적성_A};


	/// 실행부대가 병기별로 설정된 특정 특기를 보유한 경우 계략을 실행하지 않음

	// 특기조건 적용여부 설정
	const array<bool> 실행부대_특기조건_적용 = {/*플레이어 위임군단*/true, /*컴퓨터*/true};

	// 특기별 특기조건 적용여부 설정
	const bool 실행부대_귀문특기_적용 = true;	// 모든 병기에 적용
	const bool 실행부대_요술특기_적용 = false;	// 모든 병기에 적용
	const bool 실행부대_연전특기_적용 = false;	// 검을 제외한 모든 병기에 적용
	const bool 실행부대_패왕특기_적용 = true;	// 검을 제외한 모든 병기에 적용
	const bool 실행부대_용장특기_적용 = true;	// 검을 제외한 모든 병기에 적용
	const bool 실행부대_포박특기_적용 = true;	// 검을 제외한 모든 병기에 적용

	// 병기별로 특기조건을 적용할 특기 설정
	const array<array<int>> 실행부대_병기별_적용특기 =
	{
		/* 검 */ {},
		/* 창 */ {특기_신장, 특기_비장, 특기_투신, 특기_창신, 특기_창장, 특기_맹장},
		/* 극 */ {특기_신장, 특기_비장, 특기_투신, 특기_극신, 특기_극장, 특기_맹장, 특기_심공, 특기_위풍},
		/* 노 */ {특기_신장, 특기_비장, 특기_궁신, 특기_궁장},
		/*군마*/ {특기_신장, 특기_비장, 특기_기신, 특기_기장, 특기_질주},
		/*충차*/ {특기_공신, 특기_공성},
		/*정란*/ {특기_공신, 특기_공성, 특기_사정},
		/*투석*/ {특기_공신, 특기_공성, 특기_사정},
		/*목수*/ {특기_공신, 특기_공성},
		/*주가*/ {특기_수신, 특기_수장},
		/*누선*/ {특기_수신, 특기_수장},
		/*투함*/ {특기_수신, 특기_수장}
	};


/// -------------------------------------------------------------------------------------------------------


/// [ 대상부대 관련 조건 ]


	/// 대상부대의 병력이 기준값 미만인 경우 계략 실행대상에서 제외
	const array<bool> 대상부대_병력조건_적용 = {/*플레이어 위임군단*/true, /*컴퓨터*/true};
	const array<int> 대상부대_기준병력 = {/*플레이어 위임군단*/1500, /*컴퓨터*/1500};


	/// 대상부대의 기력이 기준값 미만인 경우 계략 실행대상에서 제외
	const array<bool> 대상부대_기력조건_적용 = {/*플레이어 위임군단*/true, /*컴퓨터*/true};
	const array<int> 대상부대_기준기력 = {/*플레이어 위임군단*/20, /*컴퓨터*/20};


	/// 대상부대의 특정 부대능력이 기준값 미만인 경우 계략 실행대상에서 제외
	const array<bool> 대상부대_능력조건_적용 = {/*플레이어 위임군단*/true, /*컴퓨터*/true};
	const array<int> 대상부대_기준능력 = {/*플레이어 위임군단*/40, /*컴퓨터*/40};
	const int 대상부대_적용능력 = 부대능력_공격;


	/// 대상부대의 부대적성이 기준값 이하인 경우 계략 실행대상에서 제외
	// 참고 : 적성 S 이후의 적성을 사용하는 경우 번호로 입력해야 함 (적성 C의 번호가 0이고 이후 적성 한 단계 상승 시마다 번호 +1)
	const array<bool> 대상부대_적성조건_적용 = {/*플레이어 위임군단*/true, /*컴퓨터*/true};
	const array<int> 대상부대_기준적성 = {/*플레이어 위임군단*/적성_C, /*컴퓨터*/적성_C};


	/// 계략을 실행하기 위한 조건들을 통과한 대상부대들 정렬 시 설정

	// 도시 근처에서 공성전 방어조건을 충족하는 대상부대에게 우선적으로 계략을 실행
	const array<bool> 공성전_방어조건_적용 = {/*플레이어 위임군단*/true, /*컴퓨터*/true};
	const int 공성전_방어조건_기준거리 = 6;
	const int 공성전_방어조건_기준내구비율 = 30;
	const int 공성전_방어조건_기준병력 = 5000;

	// 실행부대가 연환특기를 보유한 경우 인접부대가 있는 대상부대에게 우선적으로 계략을 실행
	const array<bool> 연환특기_인접부대_우선 = {/*플레이어 위임군단*/true, /*컴퓨터*/true};


/// =========================================================================================

	// 디버깅 설정
	const bool 디버깅_func261_prev_handler_check = false;
	const bool 디버깅_func262_prev_handler_check = false;
	const bool 디버깅_serach_pos_to_move = false;
	const bool 디버깅_strategy_success_info = false;
	const bool 디버깅_dst_unit_sort_info = false;

	class Main
	{

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		// AI 스크립트 함수 체인을 위한 이전 핸들러 저장용
		pk::func261_t@ prev_callback_261;

		// 부대 임무 핸들러 함수 체인을 위한 이전 핸들러 저장용
		pk::func262_t@ prev_callback_262;

		// 실행부대가 계략을 시전할 대상부대 검색 시 해당 대상부대 근처의 이동가능한 후보좌표 저장용
		array<pk::point> 대상부대별_이동후보좌표(부대_끝, -1);

		// 후보 이동좌표 검색 함수 디버깅용
		pk::point range_pos_;

		// 후보 대상부대 배열 정렬용
		int strategy_id_;
		pk::unit@ src_unit_;

		// 직선형 함정의 시설범위 확인 시 참고용
		array<array<int>> 방향별_일직선_좌표색인 =
		{
			/*북서*/ {4, 15, 32, 55, 84, 119, 160, 207},	/* 북 */ {5, 17, 35, 59, 89, 125, 167, 215},
			/*북동*/ {0,  7, 20, 39, 64,  95, 132, 175},	/*남서*/ {3, 13, 29, 51, 79, 113, 153, 199},
			/* 남 */ {2, 11, 26, 47, 74, 107, 146, 191},	/*남동*/ {1,  9, 23, 43, 69, 101, 139, 183}
		};

	/**
		[ 추가 고려사항 ]

		지형피해 및 시설범위 조건의 경우, 실행부대가 이동할 후보좌표를 검색하는데 있어서 나머지 조건을 다 충족했는데
		해당 조건들이 만족되지 못해 이동가능한 좌표가 없는 경우에는 무시하고 계략을 실행할 것인지 여부
	*/

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		Main()
		{
			// 261함수 이전 핸들러 저장, 함수 초기화, 함수 재정의
			@prev_callback_261 = cast<pk::func261_t@>(pk::get_func(261));
			pk::reset_func(261);
			pk::set_func(261, pk::func261_t(func261));

			// 262함수 이전 핸들러 저장, 함수 초기화, 함수 재정의
			@prev_callback_262 = cast<pk::func262_t@>(pk::get_func(262));
			pk::reset_func(262);
			pk::set_func(262, pk::func262_t(func262));
		}

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		/**
		@param  force : AI 세력
		@return 자신이 처리했다면 true. 컴퓨터에게 맡기려면 false.
		*/
		/// 참고 : AI 스크립트 함수(261)를 사용하는 경우에는 플레이어 1군단이 이미 배제된 상태임
		/// 참고 : 261함수는 전체 AI 스크립트이기 때문에 부대가 계략을 실행한 후 이전 핸들러를 무조건 체인해주어야 함
		bool func261(pk::force@ force)
		{
			if (디버깅_func261_prev_handler_check)
			{
				string force_name = pk::decode(pk::get_name(force));
				pk::info(force_name+" 세력 - 261함수 이전 핸들러 존재여부 : "+(prev_callback_261 is null ? "없음" : "있음"));
			}

			for (int unit_id = 0; unit_id < 부대_끝; unit_id++)
			{
				pk::unit@ unit = pk::get_unit(unit_id);
				if (!pk::is_alive(unit)) continue;
				if (unit.get_force_id() != force.get_id()) continue;

				// 실행부대가 출진부대인 경우 제외 (부대 좌표와 부대 소속거점 좌표가 동일한 경우 제외)
				pk::building@ building = pk::get_building(pk::get_service(unit));
				if (pk::is_alive(building) and unit.pos == building.pos) continue;

				strategy_action_of_AI_unit(unit, force, /*is_deployed*/false);
			}

			if (prev_callback_261 is null) return false;
			return prev_callback_261(force);
		}

		/**
		@param  unit : 부대 임무 실행부대
		@return 자신이 처리했다면 true. 컴퓨터에게 맡기려면 false.
		*/
		/// 참고 : pk::run_order 함수가 실행될 경우 이 스크립트가 실행됩니다. (262 함수 내에서 pk::run_order 함수 사용 시 무한루프 발생)
		/// 참고 : 262함수는 부대 임무 핸들러에 한정된 스크립트이므로 해당 부대가 계략을 실행했다면 행동완료되므로 이전 핸들러를 체인하지 않음
		bool func262(pk::unit@ unit)
		{
			if (디버깅_func262_prev_handler_check)
			{
				string unit_name = pk::decode(pk::get_name(unit));
				pk::info(unit_name+" - 262함수 이전 핸들러 존재여부 : "+(prev_callback_262 is null ? "없음" : "있음"));
			}

			// 실행부대가 출진부대인 경우에만 실행 (부대 좌표와 부대 소속거점 좌표가 동일한 경우 실행)
			pk::building@ building = pk::get_building(pk::get_service(unit));
			if (pk::is_alive(building) and unit.pos == building.pos)
			{
				pk::force@ force = pk::get_force(unit.get_force_id());
				strategy_action_of_AI_unit(unit, force, /*is_deployed*/true);

				// 계략을 실행된 경우 이전 핸들러를 체인하지 않음
				if (unit.pos != building.pos) return true;
			}

			if (prev_callback_262 is null) return false;
			return prev_callback_262(unit);
		}

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		void strategy_action_of_AI_unit(pk::unit@ unit, pk::force@ force, bool is_deployed)
		{
			// 기본조건 : 플레이어 1군단 부대 제외
			if (pk::is_player_controlled(unit)) return;

			// 기본조건 : 일반게임 여부 확인 (결전제패, 튜토리얼, 미션 진행 중이 아닐 것)
			if (!is_normal_game()) return;

			// 기본조건 : 적장세력 적용여부 확인
			if (!pk::is_normal_force(force) and !적장세력_적용) return;

			// 설정조건 : 실행부대의 조작주체별(플레이어 위임군단, 컴퓨터) 적용여부 확인
			int controller_index = get_controller_index(unit);
			if (is_deployed)
			{
				// 실행부대가 출진부대인 경우 적용여부 확인
				if (!AI부대_계략실행_출진부대_적용[controller_index]) return;
			}
			else
			{
				// 실행부대가 야전부대인 경우 적용여부 확인
				if (!AI부대_계략실행_야전부대_적용[controller_index]) return;
			}

			for (int arr_index = 0; arr_index < int(실행계략_일람.length); arr_index++)
			{
				int strategy_id = 실행계략_일람[arr_index];
				func_계략진행(unit, force, strategy_id, controller_index, is_deployed);
			}
		}

		// 실행부대가 계략 대상부대가 존재하는 경우 계략실행 (계략실행을 위해 실행부대의 이동이 필요한 경우 이동 후 실행)
		void func_계략진행(pk::unit@ src_unit, pk::force@ src_force, int strategy_id, int controller_index, bool is_deployed)
		{
			// 후보 대상부대 배열 정렬용 변수 저장
			@src_unit_ = @src_unit;
			strategy_id_ = strategy_id;

			// 계략 실행부대가 계략실행을 위한 조건을 충족하는지 확인
			int energy_cost = get_energy_cost(src_unit, strategy_id);
			if (!func_실행부대_조건충족(src_unit, strategy_id, energy_cost, controller_index)) return;

			// 계략범위 내의 후보대상부대 검색 (대상부대 조건 및 이동후보좌표 확인)
			int strategy_range = src_unit.has_skill(특기_귀모) ? 3 : 2;
			pk::unit@ dst_unit = get_dst_unit(src_unit, src_force, strategy_id, strategy_range, controller_index, is_deployed);
			if (!pk::is_alive(dst_unit)) return;

			// 대상부대 검색 시 저장했던 실행부대의 이동후보좌표 반환 : 이동이 필요한 경우에만 저장된 상태
			pk::point pos_to_move = 대상부대별_이동후보좌표[dst_unit.get_id()];
			if (pk::is_valid_pos(pos_to_move))
			{
				// 이동후보좌표가 유효한(저장된) 경우 실행부대 이동후보좌표로 이동 : 부대 이동명령 실행
				/// 참고 : pk::get_path(unit, unit.pos, pos) 함수 사용 시 강제종료 현상 발생
				if (is_deployed)
				{
					/// 참고 : 262함수를 사용하는 출진부대의 경우 pk::run_order 함수를 사용하면 무한루프 발생
				//	array<pk::point> unit_path = pk::get_path(src_unit, src_unit.pos, pos_to_move);
					array<pk::point> unit_path = {src_unit.pos, pos_to_move};	// 임시방편 but 이동 애니메이션 부자연스러움
					pk::move(src_unit, unit_path);
				}
				else
				{
					pk::set_order(src_unit, 부대임무_이동, pos_to_move);
					pk::run_order(src_unit);
				}
			}

			// 실행부대 계략 실행 (연환 특기, 반계 특기 반영)
			func_계략실행(src_unit, src_force, dst_unit, strategy_id, energy_cost, controller_index, is_deployed);
		}

		// 계략 실행부대가 계략실행을 위한 조건을 충족하는지 확인
		bool func_실행부대_조건충족(pk::unit@ src_unit, int strategy_id, int energy_cost, int controller_index)
		{
			// 기본조건 : 실행부대로부터 대상부대를 검색할 기준거리 이내에 적부대가 존재하는지 확인
			if (func_부대근처_적부대수(src_unit, 계략실행_기준거리) == 0) return false;

			// 기본조건 : 실행부대의 부대임무가 퇴각인 경우 제외
			if (src_unit.order == 부대임무_퇴각) return false;

			// 기본조건 : 실행부대가 행동완료 상태인 경우 제외
			if (src_unit.action_done) return false;

			// 기본조건 : 실행부대의 부대기력이 계략의 소비기력 미만인 경우 제외
			if (int(src_unit.energy) < energy_cost) return false;

			// 설정조건 : 실행부대의 부대종류가 수송부대인 경우 적용여부 확인
			if (!실행부대_수송부대_적용[controller_index] and src_unit.type == 부대종류_수송) return false;

			// 설정조건 : 실행부대의 부대기력이 기준기력 미만인 경우 제외
			if (실행부대_기력조건_적용[controller_index])
			{
				if (int(src_unit.energy) < 실행부대_기준기력[controller_index]) return false;
			}

			// 설정조건 : 실행부대의 특정 부대능력이 기준능력 이상인 경우 제외
			if (실행부대_능력조건_적용[controller_index])
			{
				if (int(src_unit.attr.stat[실행부대_적용능력]) >= 실행부대_기준능력[controller_index]) return false;
			}

			// 설정조건 : 실행부대의 부대적성이 기준적성 이상인 경우 제외
			int weapon_id = src_unit.weapon;
			if (실행부대_적성조건_적용[controller_index])
			{
				int src_tekisei = (weapon_id == 병기_검) ? 0 : pk::get_tekisei(src_unit, weapon_id);
				if (src_tekisei >= 실행부대_기준적성[controller_index]) return false;
			}

			// 설정조건 : 실행부대가 병과별로 설정된 특정 특기를 보유한 경우 제외
			if (실행부대_특기조건_적용[controller_index])
			{
				if (src_unit.has_skill(특기_귀문) and 실행부대_귀문특기_적용) return false;
				if (src_unit.has_skill(특기_요술) and 실행부대_요술특기_적용) return false;

				if (weapon_id != 병기_검)
				{
					if (src_unit.has_skill(특기_패왕) and 실행부대_패왕특기_적용) return false;
					if (src_unit.has_skill(특기_용장) and 실행부대_용장특기_적용) return false;
					if (src_unit.has_skill(특기_포박) and 실행부대_포박특기_적용) return false;

					/// 참고 : '기타.xml'의 '초특기연전' 값을 'true'로 설정 시 전법에도 연전 특기가 적용됨
					if (src_unit.has_skill(특기_연전) and 실행부대_연전특기_적용) return false;
				}

				for (int arr_index = 0; arr_index < int(실행부대_병기별_적용특기[weapon_id].length); arr_index++)
				{
					int skill_id = 실행부대_병기별_적용특기[weapon_id][arr_index];
					if (src_unit.has_skill(skill_id)) return false;
				}
			}

			return true;
		}

		// 조건을 만족하는 대상부대들 중 기준에 따라 정렬 후 최우선 순위의 대상부대를 반환
		pk::unit@ get_dst_unit(pk::unit@ src_unit, pk::force@ src_force, int strategy_id, int strategy_range, int controller_index, bool is_deployed)
		{
			array<pk::unit@> dst_unit_arr = get_dst_unit_arr(src_unit, src_force, strategy_id, strategy_range, controller_index, is_deployed);
			if (int(dst_unit_arr.length) == 0) return null;

			if (디버깅_dst_unit_sort_info)
			{
				pk::message_box(pk::encode("대상부대배열 정렬 전"));
				for (int i = 0; i < int(dst_unit_arr.length); i++)
				{
					pk::unit@ unit = dst_unit_arr[i];
					string unit_name = pk::decode(pk::get_name(unit));
					pk::message_box(pk::encode("대상부대배열 색인 "+i+" : "+unit_name+"\n부대공격력 : "+int(unit.attr.stat[부대능력_공격])+"\n부대적성 : "+int(pk::get_tekisei(unit))));
				}
			}
		/**
			[ 참고 ] 대상부대 간 정렬 우선순위

			1. 대상부대의 공성전 방어조건 : 공성전 방어조건을 충족하는 대상부대를 우선 (단, 공성전 방어조건 적용 시)
			2. 대상부대의 인접부대 : 실행부대가 연환특기 보유 시 대상부대의 인접좌표에 실행부대의 적부대가 존재하는 경우를 우선 (단, 설정 적용 시)
			3. 대상부대의 부대능력(공격력) : 클수록 우선
			4. 대상부대의 부대능력(지력) : 클수록 우선
			5. 대상부대의 부대병력 : 많을수록 우선
			6. 실행부대와 대상부대의 거리 : 가까울수록 우선
			7. 대상부대의 부대적성 : 높을수록 우선
			8. 대상부대의 부대기력 : 클수록 우선
			9. 실행부대의 대상부대에 대한 계략성공확률 : 높을수록 우선 (단, 확률보장대상 모드에 한함)
			10. 대상부대의 부대구성원 : 많을수록 우선
			11. 대상부대 주변에 존재하는 실행부대의 적군 부대수(5칸 이내) : 적을수록 우선
			12. 대상부대 주변에 존재하는 실행부대의 적군 병사수(5칸 이내) : 적을수록 우선
			13. 대상부대 주변에 존재하는 실행부대의 아군 부대수(5칸 이내) : 많을수록 우선
			14. 대상부대 주변에 존재하는 실행부대의 아군 병사수(5칸 이내) : 많을수록 우선
		*/
		/**
			[ 참고 ]

			1. 만약 부대 간 조건 비교 시 차이값이 매우 작은 경우와 같은 애매한 상황까지 반영하고 싶은 경우 정렬 조건을 범위로 부여할 수도 있으나
			   그러나 조건이 두개 이상이고 정렬을 하려는 배열의 항목이 3개 이상인 경우에는 항목 간의 비교가 불가능한 상황이 발생할 수 있음
			2. 배열이나 리스트를 정렬할 때에는 설정한 조건에 대하여 예외가 생기는 경우를 주의할 것
			   예컨대 특정 조건에 대하여 정렬을 원하는 모든 경우의 수를 처리하지 않게 되면 처리되지 못한 경우의 수가 다음 조건에서 처리되어 
			   원하는 방향과 다르게 정렬이 되어버릴 수 있음
		*/
			// 대상부대의 항목 배열을 조건에 따라 정렬
			dst_unit_arr.sort(function(a, b)
			{
				// 대상부대의 공성전 방어조건 : 공성전 방어조건을 충족하는 대상부대를 우선 (단, 공성전 방어조건 적용 시)
				int controller_index = main.get_controller_index(main.src_unit_);
				if (공성전_방어조건_적용[controller_index])
				{
					bool a_is_siege_warfare = main.func_공성전_방어조건_충족여부(main.src_unit_, a);
					bool b_is_siege_warfare = main.func_공성전_방어조건_충족여부(main.src_unit_, b);
					if (a_is_siege_warfare and !b_is_siege_warfare) return true;
					else if (!a_is_siege_warfare and b_is_siege_warfare) return false;
				}

				// 대상부대의 인접부대 : 실행부대가 연환특기 보유 시 대상부대의 인접좌표에 실행부대의 적부대가 존재하는 경우를 우선 (단, 설정 적용 시)
				if (연환특기_인접부대_우선[controller_index] and main.src_unit_.has_skill(특기_연환))
				{
					pk::unit@ a_neighbor_unit = main.get_dst_neighbor_unit(main.src_unit_, a);
					pk::unit@ b_neighbor_unit = main.get_dst_neighbor_unit(main.src_unit_, b);
					if (pk::is_alive(a_neighbor_unit) and !pk::is_alive(b_neighbor_unit)) return true;
					else if (!pk::is_alive(a_neighbor_unit) and pk::is_alive(b_neighbor_unit)) return false;
				}

				// 대상부대의 부대능력(공격력) : 클수록 우선
				int a_atk_stat = a.attr.stat[부대능력_공격];
				int b_atk_stat = b.attr.stat[부대능력_공격];
				if (a_atk_stat != b_atk_stat) return a_atk_stat > b_atk_stat;

				// 대상부대의 부대능력(지력) : 클수록 우선
				int a_int_stat = a.attr.stat[부대능력_지력];
				int b_int_stat = b.attr.stat[부대능력_지력];
				if (a_int_stat != b_int_stat) return a_int_stat > b_int_stat;

				// 대상부대의 부대병력 : 많을수록 우선
				if (a.troops != b.troops) return a.troops > b.troops;

				// 실행부대와 대상부대의 거리 : 가까울수록 우선
				int a_distance = pk::get_distance(main.src_unit_.pos, a.pos);
				int b_distance = pk::get_distance(main.src_unit_.pos, b.pos);
				if (a_distance != b_distance) return a_distance < b_distance;

				// 대상부대의 부대적성 : 높을수록 우선
				int a_tekisei = (a.weapon != 병기_검) ? pk::get_tekisei(a, a.weapon) : 0;
				int b_tekisei = (b.weapon != 병기_검) ? pk::get_tekisei(b, b.weapon) : 0;
				if (a_tekisei != b_tekisei) return a_tekisei > b_tekisei;

				// 대상부대의 부대기력 : 클수록 우선
				if (a.energy != b.energy) return a.energy > b.energy;

				// 실행부대의 대상부대에 대한 계략성공확률 : 높을수록 우선 (단, 확률보장대상 모드에 한함)
				if (성공확률_적용모드[controller_index] == /*확률보장대상*/2)
				{
					int a_chance = main.get_success_chance(main.src_unit_, a.pos, main.strategy_id_);
					int b_chance = main.get_success_chance(main.src_unit_, b.pos, main.strategy_id_);
					if (a_chance != b_chance) return a_chance > b_chance;
				}

				// 대상부대의 부대구성원 : 많을수록 우선
				int a_member_count = pk::get_member_count(a);
				int b_member_count = pk::get_member_count(b);
				if (a_member_count != b_member_count) a_member_count > b_member_count;

				array<int> a_around_info = main.func_대상부대_근처부대_관련정보_배열(main.src_unit_, a, /*distance*/5);
				array<int> b_around_info = main.func_대상부대_근처부대_관련정보_배열(main.src_unit_, b, /*distance*/5);

				// 대상부대 주변에 존재하는 실행부대의 적군 부대수(5칸 이내) : 적을수록 우선
				if (a_around_info[0] != b_around_info[0]) return a_around_info[0] < b_around_info[0];

				// 대상부대 주변에 존재하는 실행부대의 적군 병사수(5칸 이내) : 적을수록 우선
				if (a_around_info[1] != b_around_info[1]) return a_around_info[1] < b_around_info[1];

				// 대상부대 주변에 존재하는 실행부대의 아군 부대수(5칸 이내) : 많을수록 우선
				if (a_around_info[2] != b_around_info[2]) return a_around_info[2] > b_around_info[2];

				// 대상부대 주변에 존재하는 실행부대의 아군 병사수(5칸 이내) : 많을수록 우선
				if (a_around_info[3] != b_around_info[3]) return a_around_info[3] > b_around_info[3];

				return true;
			});

			if (디버깅_dst_unit_sort_info)
			{
				pk::message_box(pk::encode("대상부대배열 정렬 후"));
				for (int i = 0; i < int(dst_unit_arr.length); i++)
				{
					pk::unit@ unit = dst_unit_arr[i];
					string unit_name = pk::decode(pk::get_name(unit));
					pk::message_box(pk::encode("대상부대배열 색인 "+i+" : "+unit_name));
				}
			}

			return dst_unit_arr[0];
		}

		// 대상부대 조건을 충족하고 실행부대가 이동이 필요한 경우 후보 이동좌표가 존재하는 대상부대 후보들 반환
		array<pk::unit@> get_dst_unit_arr(pk::unit@ src_unit, pk::force@ src_force, int strategy_id, int strategy_range, int controller_index, bool is_deployed)
		{
			for (int i = 0; i < 부대_끝; i++) 대상부대별_이동후보좌표[i] = -1;
			array<pk::unit@> dst_unit_arr(0);
			array<pk::point> range_arr = pk::range(src_unit.pos, 1, 계략실행_기준거리);
			for (int i = 0; i < int(range_arr.length); i++)
			{
				pk::point dst_pos = range_arr[i];
				pk::unit@ dst_unit = pk::get_unit(dst_pos);
				if (!pk::is_alive(dst_unit)) continue;

				// 컴퓨터 세력 부대의 경우 플레이어 세력의 부대만을 대상으로 계략을 실행하도록 할지 여부 확인
				if (컴퓨터부대_계략실행대상_플레이어한정 and !src_unit.is_player())
				{
					if (!dst_unit.is_player()) continue;
				}

				// 계략의 대상부대가 계략실행을 위한 조건을 충족하는지 확인
				if (!func_대상부대_조건충족(src_unit, dst_unit, strategy_id, controller_index)) continue;

			/**
				[ 참고 ] 실행부대가 이동할 필요가 있는 경우

				1. 대상부대가 실행부대의 계략범위 밖에 존재하는 경우
				2. 실행부대가 불지형 위에 존재하는 경우
				3. 실행부대가 특정시설의 범위 안에 위치하는 경우
				4. 실행부대가 출진부대인 경우
			*/
				// 실행부대가 현재 좌표에서 이동할 필요가 있는 경우 미리 대상부대 근처의 이동가능좌표 존재여부 확인
				int curr_distance = pk::get_distance(src_unit.pos, dst_pos);
				if (curr_distance > strategy_range or pk::is_on_fire(src_unit.pos) or is_in_facility_range(src_unit, src_unit.pos) or is_deployed)
				{
					// 대상부대 근처에 실행부대가 이동할 후보좌표 검색
					pk::point pos_to_move = get_pos_to_move(src_unit, src_force, dst_unit, strategy_range, controller_index);

					// 이동가능한 후보좌표가 없는 경우 제외
					if (!pk::is_valid_pos(pos_to_move)) continue;

					// 대상부대 근처의 실행부대가 이동 가능한 좌표를 저장
					대상부대별_이동후보좌표[dst_unit.get_id()] = pos_to_move;
				}

				// 조건을 통과한 대상부대를 저장
				dst_unit_arr.insertLast(dst_unit);
			}

			return dst_unit_arr;
		}

		// 계략의 대상부대가 계략실행을 위한 조건을 충족하는지 확인
		bool func_대상부대_조건충족(pk::unit@ src_unit, pk::unit@ dst_unit, int strategy_id, int controller_index)
		{
			// 기본조건 : 실행부대와 대상부대 후보가 적이 아닌 경우 제외
			if (!pk::is_enemy(src_unit, dst_unit)) return false;

			// 기본조건 : 대상부대의 부대상태가 통상상태가 아닌 경우 제외
			if (dst_unit.status != 부대상태_통상) return false;

			// 설정조건 : 대상부대의 병력이 기준병력 미만인 경우 제외
			if (대상부대_병력조건_적용[controller_index])
			{
				if (int(dst_unit.troops) < 대상부대_기준병력[controller_index]) return false;
			}

			// 설정조건 : 대상부대의 기력이 기준기력 미만인 경우 제외
			if (대상부대_기력조건_적용[controller_index])
			{
				if (int(dst_unit.energy) < 대상부대_기준기력[controller_index]) return false;
			}

			// 설정조건 : 대상부대의 특정 부대능력이 기준능력 미만인 경우 제외
			if (대상부대_능력조건_적용[controller_index])
			{
				if (int(dst_unit.attr.stat[대상부대_적용능력]) < 대상부대_기준능력[controller_index]) return false;
			}

			// 설정조건 : 대상부대의 부대적성이 기준적성 이하인 경우 제외
			if (대상부대_적성조건_적용[controller_index])
			{
				int weapon_id = dst_unit.weapon;
				int dst_tekisei = (weapon_id == 병기_검) ? 0 : pk::get_tekisei(dst_unit, weapon_id);
				if (dst_tekisei <= 대상부대_기준적성[controller_index]) return false;
			}

			// 설정조건 : 모드별 실행부대의 대상부대에 대한 계략의 성공확률 확인
			int success_chance = get_success_chance(src_unit, dst_unit.pos, strategy_id);
			if (성공확률_적용모드[controller_index] == /*성공보장대상*/1)
			{
				// 모드 1 : 성공확률을 충족하지 못한 경우 제외
				/// 참고 : '모드1'의 경우 성공이 보장되는 대상부대에게만 시전
				if (!pk::rand_bool(success_chance)) return false;

			/**
				[ 참고 ]

				'206 계략 성공 확률.cpp' 파일의 원본 내용 상으로는 계략이 간파되는 경우 무조건 성공확률은 0이 반환되므로
				계략의 성공여부 자체는 성공확률 충족여부(is_success)만 판단하면 충분함
				그러나 '206 계략 성공 확률.cpp'를 수정하는 경우 등의 만약을 대비해 확인조건을 추가
			*/
				// 대상부대의 실행부대에 대한 계략이 간파되는 경우 제외
				bool is_detected = strategy_is_detected(src_unit, dst_unit.pos, strategy_id);
				if (is_detected) return false;
			}
			else if (성공확률_적용모드[controller_index] == /*확률보장대상*/2)
			{
				// 모드 2 : 성공확률이 기준확률 미만인 경우 제외
				/// 참고 : '모드2'의 경우 확률이 보장되는 대상부대에게만 시전
				if (success_chance < 실행기준_성공확률[controller_index]) return false;
			}

			return true;
		}

		// 실행부대가 이동할 대상부대 근처의 후보좌표 반환 (단, 이동이 필요한 경우 검색)
		pk::point get_pos_to_move(pk::unit@ src_unit, pk::force@ src_force, pk::unit@ dst_unit, int strategy_range, int controller_index)
		{
			if (디버깅_serach_pos_to_move)
			{
				string src_unit_name = pk::decode(pk::get_name(src_unit));
				pk::message_box(pk::encode("이동가능좌표 확인시작 : "+src_unit_name));
			}

			// 계략 대상부대 근처의 실행부대가 이동할 후보좌표 검색 (먼 거리부터 검색)
			array<pk::point> pos_to_move_arr(0);
			int longest_distance = 0;
			array<pk::point> range_arr = pk::range(dst_unit.pos, 1, strategy_range);
			for (int i = int(range_arr.length) - 1; i >= 0; i--)
			{
				pk::point pos_to_move = range_arr[i];
				if (!pk::is_valid_pos(pos_to_move)) continue;

				// 기본조건 : 실행부대가 이동할 후보좌표가 실행부대의 좌표와 동일한 경우 제외
				if (pos_to_move == src_unit.pos) continue;

				// 기본조건 : 실행부대가 이동할 후보좌표가 건물 또는 부대가 존재하는 칸인 경우 제외
				pk::hex@ hex = pk::get_hex(pos_to_move);
				if (hex.has_building) continue;
				if (hex.has_unit) continue;

				// 기본조건 : 실행부대가 이동할 후보좌표의 지형이 유효하지 않거나 선택이 불가능한 지형인 경우 제외
				int terrain_id = hex.terrain;
				if (!pk::is_valid_terrain_id(terrain_id)) continue;
				if (!pk::is_enabled_terrain(terrain_id)) continue;

				// 기본조건 : 실행부대가 이동할 후보좌표가 이동이 불가능한 좌표인 경우 제외
				/// 참고 : pk::get_movable_pos() 함수에는 '지형.xml', '169 지형 이동 가능 설정.cpp'의 이동가능 여부 관련 설정이 모두 반영된 상태
				array<pk::point> movable_pos_arr = pk::get_movable_pos(src_unit);
				if (movable_pos_arr.find(pos_to_move) < 0) continue;

				if (디버깅_serach_pos_to_move)
				{
					string terrain_damage_type_name = "없음";
					int terrain_damage_type = int(pk::core["지형"][terrain_id]["피해종류"]);
					if      (terrain_damage_type == 1) terrain_damage_type_name = "독천";
					else if (terrain_damage_type == 2) terrain_damage_type_name = "벼랑길";
					range_pos_ = pos_to_move;
					pk::scene(cast<pk::scene_t@>(function(){pk::highlight(main.range_pos_, true);}));
					pk::message_box(pk::encode("피해종류 : "+terrain_damage_type_name));
					pk::scene(cast<pk::scene_t@>(function(){pk::remove_all_highlights();}));
				}

			/**
				[ 참고 ] 지형피해 관련

				1. 지형피해는 난소행군 기교연구가 되어 있지 않은 경우에 입음
				2. 지형의 피해종류 값 - 없음(0), 독천(1), 벼랑길(2) ('지형.xml' 참고)
			*/
				// 설정조건 : 실행부대가 이동할 후보좌표의 지형이 지형피해를 입는 지형인 경우 이동을 허용할지 확인
				if (후보이동좌표_검색시_지형피해좌표_제외[controller_index])
				{
					// 실행부대가 이동할 후보좌표의 지형이 지형피해를 입는 지형인 경우 제외
					int terrain_damage_type = int(pk::core["지형"][terrain_id]["피해종류"]);
					if (!pk::has_tech(src_force, 기교_난소행군) and terrain_damage_type != /*피해종류 값 : 없음*/0) continue;
				}

				// 설정조건 : 실행부대가 이동할 후보좌표가 불지형인 경우 제외
				if (후보이동좌표_검색시_불지형좌표_제외[controller_index])
				{
					if (pk::is_on_fire(pos_to_move)) continue;
				}

				// 설정조건 : 실행부대가 이동할 후보좌표가 특정시설의 범위 안에 위치하는 경우 제외
				if (후보이동좌표_검색시_시설범위좌표_제외[controller_index])
				{
					if (is_in_facility_range(src_unit, pos_to_move)) continue;
				}

				// 비교조건 : 실행부대의 좌표와 실행부대가 이동할 후보좌표 간 거리에 따른 비교 (먼 거리 우선)
				int curr_distance = pk::get_distance(src_unit.pos, pos_to_move);
				if (curr_distance < longest_distance) continue;

				pos_to_move_arr.insertLast(pos_to_move);
				longest_distance = curr_distance;
			}

			if (int(pos_to_move_arr.length) == 0) return -1;
			return pos_to_move_arr[pk::rand(int(pos_to_move_arr.length))];
		}

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	/**
		[ 참고 ] 계략실행 기본구조

		1. 실행부대 소비기력 처리
		2. 계략효과
		 1) 실행부대 계략시전효과
		 2) 계략성공 시 실행부대 및 대상목표(건물, 부대) 계략성공효과
		 3) 계략실패 시 실행부대 및 대상목표(건물, 부대) 계략실패효과
		 4) 실행부대 계략시전보상
		  (1) 기교 포인트
		  (2) 능력 경험치(지력)
		  (3) 공적
		3. 실행부대 행동완료 처리
		4. 실행부대 연환 특기 처리
		5. 대상부대 반계 특기 처리
	*/
		void func_계략실행(pk::unit@ src_unit, pk::force@ src_force, pk::unit@ dst_unit, int strategy_id, int energy_cost, int controller_index, bool is_deployed)
		{
			// 실해부대 계략 소비기력 차감
			pk::add_energy(src_unit, -energy_cost, false);

			// 계략 실행 (일반시전)
			bool is_success = func_계략효과(src_unit, src_force, dst_unit, strategy_id, /*is_chain_reaction*/false, /*is_counter_plan*/false, controller_index, is_deployed);

		/**
			[ 참고 ] 연환 특기 관련

			1. 연환 특기는 최초 계략 시전 대상에게 계략이 성공해야 인접부대에 발동됨
			2. 연환 특기가 적용되는 계략 - 화계, 소화, 위보, 교란, 진정 (복병, 동토, 요술, 낙뢰 미적용)
			3. 계략 화계 시전 시 최초 대상별로 인접대상에 연환 특기가 발동되는 경우 (인접대상이 복수인 경우 무작위 선택)
			 1) 부대 성공 시 인접부대 발동
			 2) 건물 성공 시 인접건물 미발동(단, 도시의 경우는 발동)
			 3) 부대 성공 시 인접건물 미발동
			 4) 건물 성공 시 인접부대 발동
			4. 계략 화계의 연환 발동 시에는 연환특기 보유무장의 연환 발동 대사가 출력되지 않음
		*/
			// 일반시전 계략이 성공했고 실행부대가 연환특기를 보유한 경우 추가 계략 실행 (연환발동)
			if (is_success and src_unit.has_skill(특기_연환))
			{
				// 대상부대의 인접부대 검색
				pk::unit@ dst_neighbor_unit = get_dst_neighbor_unit(src_unit, dst_unit);
				if (pk::is_alive(dst_neighbor_unit))
				{
					func_계략효과(src_unit, src_force, dst_neighbor_unit, strategy_id, /*is_chain_reaction*/true, /*is_counter_plan*/false, controller_index, is_deployed);
				}
			}

			// 일반시전 계략이 실패했고 대상부대가 반계특기를 보유한 경우 추가 계략 실행 (반계발동)
		/**
			[ 참고 ] 반계 특기 관련

			1. 실행부대 연환 특기 발동 시 대상부대 반계 특기가 발동되지 않음 (연환에 대한 반계 받아치기 안됨)
			2. 대상부대 반계 특기 발동 시 실행부대 반계 특기가 발동되지 않음 (반계에 대한 반계 받아치기 안됨)
			3. 반계 특기 발동 시 계략 실행부대에 계략을 돌려주므로 기존의 대상부대가 실행부대가 됨 (변수 사용에 유의)
			4. 반계 특기 발동 시 실행부대로부터 시도 당했던 계략을 대상부대에게 동일하게 돌려주기는 하지만 계략 시전 효과가 기본 효과와 다름
			 - 계략 실행부대의 계략시전효과 중 대사, 효과음, 효과가 다름 (음성은 동일)
		*/
			if (!is_success and dst_unit.has_skill(특기_반계))
			{
				// 대상부대가 실행부대에게 받았던 계략을 반대로 시전
				func_계략효과(dst_unit, src_force, src_unit, strategy_id, /*is_chain_reaction*/false, /*is_counter_plan*/true, controller_index, is_deployed);
			}

			// 실행부대 행동완료
			src_unit.action_done = true;
		}

	/**
		[ 참고 ] 계략 효과(함수)

		1. 컷인 : pk::face_cutin(int id) / pk::face_cutin(unit@ unit)
		 - 크리티컬 발동 시 출력
		 - 플레이어 세력 부대인 경우에만 출력
		 - '기타.xml'의 '계략컷인' 설정이 'true'인 경우에만 출력
		2. 대사   : pk::msg_param 구조체 속성들 활용
		 - msg 폴더의 s11 파일 대사 소환 가능 (계략관련 내용 - S11MSG01.s11 파일)
		3. 음성 : pk::play_voice(person@ person)
		4. 효과음 : pk::play_se(int id, pk::point pos) / pk::play_se(int id)
		5. 효과 : pk::create_effect(int id, pk::point pos)
		6. 처리 : 구조체 속성이나 함수 사용
		 - 계략별로 추가로 필요해서 사용하는 함수에 따라 대사, 효과음, 효과 등이 포함되는 경우가 있음
		7. 대기   : pk::wait(int min, int max)
		 - 효과 애니메이션의 원활한 진행을 위해 사용
		 - pk::is_in_screen() 함수 안에서 사용하지 않으면 강제종료 현상 발생 가능
		 - pk::scene() 함수 내에서 사용하지 않으면 버퍼링 발생 : pk::scene(cast<pk::scene_t@>(function(){pk::wait(1, 1000);}));
	*/
	/**
		[ 참고 ] 계략별 처리 관련 함수

		1. 화계, 소화, 낙뢰 : pk::create_fire(pk::point pos, int timer(턴수), unit@ by = null, bool critical = false)
		 - 포함효과 : 효과(불 생성 및 제거), 효과음(불 소리)
		2. 위보, 교란, 진정 : pk::set_status(unit@ self, unit@ by, int status, int time, bool sound = true)
		 - 매개변수 : self(상태적용부대), by(상태유발부대), status(부대상태), time(상태카운터), sound(효과음출력여부)
		 - 포함효과 : 로그메시지(대상부대 상태변화), 대사(대상부대 상태변화), 효과음(대상부대 상태변화), 효과(대상부대 상태변화)
		3. 복병, 동토 : pk::attack(unit@ unit, hex_object@ target)
		4. 요술 : 
		5. 낙뢰 : 
	*/
		bool func_계략효과(pk::unit@ src_unit, pk::force@ src_force, pk::unit@ dst_unit, int strategy_id, bool is_chain_reaction, bool is_counter_plan, int controller_index, bool is_deployed)
		{
			// 실행부대 및 대상부대의 계략관련 무장 확인 (컷인, 대사, 음성 관련)
			/// 참고 : 연환 및 반계 특기 발동 시 기본적으로는 해당특기 보유무장이 계략효과와 관련된 주체가 됨 (컷인의 경우 예외 있음)
			pk::person@ src_person = pk::get_person(src_unit.leader);
			pk::person@ dst_leader = pk::get_person(dst_unit.leader);
			if      (is_chain_reaction) @src_person = pk::get_person(src_unit.who_has_skill(특기_연환));
			else if (is_counter_plan)   @src_person = pk::get_person(src_unit.who_has_skill(특기_반계));

			// 계략 크리티컬 여부 확인
			bool is_critical = pk::rand_bool(get_critical_chance(src_unit, dst_unit.pos, strategy_id));

			// 실행부대의 계략시전효과 : 컷인, 대사, 음성, 효과음, 효과
			func_계략시전효과_실행부대(src_unit, src_person, dst_leader, strategy_id, is_critical, is_chain_reaction, is_counter_plan);

			// 모드별 계략 성공확률 및 간파여부 적용
			bool is_success = pk::rand_bool(get_success_chance(src_unit, dst_unit.pos, strategy_id));
			bool is_detected = strategy_is_detected(src_unit, dst_unit.pos, strategy_id);
			if (!is_chain_reaction and !is_counter_plan and 성공확률_적용모드[controller_index] == /*성공보장대상*/1)
			{
				/// 참고 : '모드1'의 경우 대상부대를 검색할 때 성공확률을 충족하는 경우만 저장했기 때문에 여기서는 무조건 성공하는 것으로 설정
				///        (단, '모드1'이라고 해도 연환이나 반계 특기로 인해 계략을 시전할 때는 달라진 대상에 대해 성공확률을 다시 확인함)
				is_success = true;
				is_detected = false;
			}

			/// 참고 : 계략이 간파되면 무조건 성공하지 못하므로 계략의 성공여부 자체는 성공확률 충족여부(is_success)만 판단하면 됨
			if (is_success)
			{
				// 대상부대의 계략성공효과 : 대사, 음성, 효과음, 효과, 처리
				func_계략성공효과_대상부대(src_unit, dst_unit, dst_leader, strategy_id, is_critical);
			}
			else
			{
				// 대상부대의 계략실패효과 : 대사, 음성, 효과음, 효과
				func_계략실패효과_대상부대(dst_unit, dst_leader, is_detected);
			}

			// 실행부대의 계략시전보상 : 기교포인트, 능력경험치, 공적
			/// 참고 : 기교, 경험치, 공적 등은 기본적으로는 계략을 시전한 실행부대만 획득함 (연환, 반계에 의한 계략 시전 시에도 동일)
			func_계략시전보상_실행부대(src_unit, src_force, dst_unit, is_success, is_critical, strategy_id);

			if (디버깅_strategy_success_info)
			{
				string src_force_name = pk::decode(pk::get_name(src_force));
				string src_unit_name = pk::decode(pk::get_name(src_unit));
				pk::building@ building = pk::get_building(pk::get_service(src_unit));
				string src_building_name = pk::is_alive(building) ? pk::decode(pk::get_name(building)) : "없음";
				string dst_unit_name = pk::decode(pk::get_name(dst_unit));
				string src_person_name = pk::decode(pk::get_name(src_person));
				string strategy_info = (strategy_id == 계략_교란) ? "교란" : "위보";
				string success_info = (is_success) ? "성공" : "실패";
				string skill_info = (is_chain_reaction) ? "연환발동" : (is_counter_plan ? "반계발동" : "일반시전");
				pk::info(skill_info+" : "+src_force_name+"군 "+src_person_name+"("+(is_deployed ? "출진부대("+src_building_name+")" : "야전부대")+")");
				pk::info(src_unit_name+"가 "+dst_unit_name+"에게 "+strategy_info+" "+success_info+" ("+skill_info+")");
			}

			return is_success;
		}

		void func_계략시전효과_실행부대(pk::unit@ src_unit, pk::person@ src_person, pk::person@ dst_leader, int strategy_id, bool is_critical, bool is_chain_reaction, bool is_counter_plan)
		{
			if (pk::is_in_screen(src_unit.pos))
			{
				// 실행부대 연환발동 시 추가 대사
				if (is_chain_reaction)
				{
					// 실행부대 연환발동 대사 (연환특기 보유무장)
					say_message(7574, /*p0*/src_person, /*p1*/null, /*u0*/null, /*p0_u*/src_unit);

					// 대기
					pk::scene(cast<pk::scene_t@>(function(){pk::wait(1, 500);}));
				}

				// 실행부대 계략시전 컷인
			/**
				[ 참고 ] 컷인 관련

				1. 플레이어 세력(위임군단 포함) 부대가 크리티컬 발동 시에만 출력됨
				2. 컷인 출력 시 출력되는 컷인의 무장
				 1) 일반시전 : 부대의 주장
				 2) 연환발동 : 부대 내 연환특기 보유무장
				 3) 반계발동 : 부대의 주장
			*/
				if (bool(pk::core["계략컷인"]) and is_critical and src_unit.is_player())
				{
					// 연환발동 시
					if (is_chain_reaction)
					{
						// 컷인 음성
						pk::play_voice(33, src_person);

						// 컷인 효과음
						pk::play_se(25);

						// 컷인 효과
						int cutin_id = pk::get_cutin_id(src_person);
						pk::face_cutin(cutin_id);
					}

					// 일반시전 및 반계발동 시
					else
					{
						// 컷인 효과
						pk::face_cutin(src_unit);	// 음성, 효과음 포함
					}
				}

				// 실행부대 계략시전 대사
				int msg_id = (is_counter_plan) ? 7575 : (strategy_id == 계략_교란 ? 7108 : 7095);
				pk::person@ person1 = (is_counter_plan) ? null : dst_leader;
				say_message(msg_id, /*p0*/src_person, /*p1*/person1, /*u0*/null, /*p0_u*/src_unit);

				// 실행부대 계략시전 음성
				pk::play_voice(50, src_person);

				// 실행부대 계략시전 효과음
				if      (is_counter_plan) pk::play_se(91, src_unit.pos);
				else if (is_critical)     pk::play_se(79);
				else                      pk::play_se(57, src_unit.pos);

				// 실행부대 계략시전 효과
				int effect_id = (is_counter_plan) ? 77 : (is_critical ? 79 : 58);
				pk::create_effect(effect_id, src_unit.pos);

				// 대기
				pk::scene(cast<pk::scene_t@>(function(){pk::wait(1, 1000);}));
			}
		}

		void func_계략성공효과_대상부대(pk::unit@ src_unit, pk::unit@ dst_unit, pk::person@ dst_leader, int strategy_id, bool is_critical)
		{
			if (pk::is_in_screen(dst_unit.pos))
			{
				// 대상부대 계략성공 대사
				int msg_id = (strategy_id == 계략_교란) ? 5846 : 5860;
				pk::unit@ unit0 = (strategy_id == 계략_교란) ? null : dst_unit;
				say_message(msg_id, /*p0*/dst_leader, /*p1*/null, /*u0*/unit0, /*p0_u*/dst_unit);	// pk::set_status() 함수에 포함된 대사

				// 대상부대 계략성공 음성
				int voice_id = pk::rand_bool(50) ? 66 : 68;
				pk::play_voice(voice_id, dst_leader);

				// 대상부대 계략성공 효과음1
				int sound1_id = dst_unit.is_player() ? 3 : 2;
				pk::play_se(sound1_id);	// pk::set_status() 함수에 포함된 효과음

				// 대상부대 계략성공 효과음2
				int sound2_id = (strategy_id == 계략_교란) ? 39 : 40;
				pk::play_se(sound2_id, dst_unit.pos);	// pk::set_status() 함수에 포함된 효과음
			}

			// 대상부대 계략성공 효과, 처리
			/// 참고 : 교란 및 위보 계략 성공으로 인한 상태카운터는 크리티컬 미발동시에는 확률에 따라 2, 1로 설정됨 (확률 미상)
			int status = (strategy_id == 계략_교란) ? 부대상태_혼란 : 부대상태_위보;
			int time = (is_critical) ? 5 : (pk::rand_bool(20) ? 2 : 1);
			bool sound = false;
			pk::set_status(dst_unit, src_unit, status, time, sound);	// 로그메시지, 대사(대상부대), 효과음(대상부대), 효과 포함

			if (pk::is_in_screen(dst_unit.pos))
			{
				// 대기
				pk::scene(cast<pk::scene_t@>(function(){pk::wait(1, 500);}));
			}
		}

		void func_계략실패효과_대상부대(pk::unit@ dst_unit, pk::person@ dst_leader, bool is_detected)
		{
			if (pk::is_in_screen(dst_unit.pos))
			{
				// 대상부대 계략실패 대사
				say_message(7206, /*p0*/dst_leader, /*p1*/null, /*u0*/null, /*p0_u*/dst_unit);

			/**
				[ 참고 ] 계략의 간파 관련 설명

				1. 계략이 간파되는 경우에는 계략방어 효과가 발동되므로 단순히 계략이 실패한 경우와는 다름
				2. 특기별 간파가 가능한 계략 (206 계략 성공 확률.cpp 기준)
				 - 신산 및 간파 특기의 경우에는 실행부대의 목표대상(부대)에 대한 지력우위 조건을 충족해야 간파 발동
				 1) 신산 : 화계, 위보, 교란, 복병, 동토
				 2) 간파 : 화계, 위보, 교란, 복병, 동토
				 3) 통찰 : 화계, 위보, 교란, 복병, 동토, 요술
				 4) 화신 : 화계
				 5) 명경 : 위보, 교란
				 6) 규율 : 위보
				 7) 침착 : 교란
			*/
				if (is_detected)
				{
					// 대상부대 계략실패(간파) 음성
					pk::play_voice(69, dst_leader);

					// 대상부대 계략실패(간파) 효과음
					pk::play_se(95, dst_unit.pos);

					// 대상부대 계략실패(간파) 효과
					pk::create_effect(84, dst_unit.pos);
				}
				else
				{
					// 대상부대 계략실패(단순실패) 음성
					pk::play_voice(70, dst_leader);

					// 대상부대 계략실패(단순실패) 효과음, 효과 : 없음
				}

				// 대기
				pk::scene(cast<pk::scene_t@>(function(){pk::wait(1, 500);}));
			}
		}

		void func_계략시전보상_실행부대(pk::unit@ src_unit, pk::force@ src_force, pk::unit@ dst_unit, bool is_success, bool is_critical, int strategy_id)
		{
			// 기교 포인트 획득
			int tech_point = (is_success) ? 10 : 0;
			pk::add_tp(src_force, tech_point, dst_unit.pos); // 효과, 효과음 포함

			// 능력 경험치 상승 : 지력
			int stat_exp = (is_success) ? 3 : 1;
			pk::add_stat_exp(src_unit, 무장능력_지력, stat_exp);

			// 공적 상승
			int kouseki_point = (is_success) ? (is_critical ? 200 : 100) : 20;
			pk::add_kouseki(src_unit, kouseki_point);
		}

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		// 일반게임여부 반환 : 결전제패, 튜토리얼, 미션 진행 중이 아닐 것
		bool is_normal_game()
		{
			return (!pk::is_campaign() and !pk::is_mission_running());
		}

		// 부대의 조작주체 색인 반환
		int get_controller_index(pk::unit@ unit)
		{
			return (unit.is_player() ? /*플레이어 위임군단*/0 : /*컴퓨터*/1);
		}

		// 특정 부대로부터 일정거리 이내에 존재하는 적군 부대수 반환
		int func_부대근처_적부대수(pk::unit@ unit, int distance)
		{
			int enemy_units = 0;
			array<pk::point> range = pk::range(unit.pos, 1, distance);
			for (int i = 0; i < int(range.length); i++)
			{
				pk::unit@ enemy_unit = pk::get_unit(range[i]);
				if (!pk::is_alive(enemy_unit)) continue;
				if (!pk::is_enemy(unit, enemy_unit)) continue;

				enemy_units++;
			}

			return enemy_units;
		}

		// 계략 실행부대 및 대상부대의 대사 출력 : msg 폴더의 s11 파일 대사 소환 (계략관련 내용 - S11MSG01.s11 파일)
		void say_message(int msg_id, pk::person@ p0, pk::person@ p1, pk::unit@ u0, pk::unit@ p0_u)
		{
			pk::msg_param msg_param(msg_id, p0, p1);
			@msg_param.unit[0] = @u0;
			pk::say(pk::get_msg(msg_param), p0, p0_u);
		}

		// 계략 실행부대의 소비기력 반환
		int get_energy_cost(pk::unit@ src_unit, int strategy_id)
		{
			return cast<pk::func205_t>(pk::get_func(205))(src_unit, strategy_id);
		}

		// 계략 실행부대의 대상부대에 대한 성공확률 반환
		int get_success_chance(pk::unit@ src_unit, pk::point dst_pos, int strategy_id)
		{
			return cast<pk::func206_t>(pk::get_func(206))(src_unit, src_unit.pos, dst_pos, strategy_id).first;
		}

		// 계략 대상부대의 실행부대에 대한 간파여부 반환
		bool strategy_is_detected(pk::unit@ src_unit, pk::point dst_pos, int strategy_id)
		{
			return cast<pk::func206_t>(pk::get_func(206))(src_unit, src_unit.pos, dst_pos, strategy_id).second;
		}

		// 계략 실행부대의 크리티컬 확률 반환
		int get_critical_chance(pk::unit@ src_unit, pk::point dst_pos, int strategy_id)
		{
			return cast<pk::func207_t>(pk::get_func(207))(src_unit, src_unit.pos, dst_pos, strategy_id);
		}

		// 대상부대의 인접좌표에 존재하는 실행부대의 적부대 반환
		pk::unit@ get_dst_neighbor_unit(pk::unit@ src_unit, pk::unit@ dst_unit)
		{
			array<pk::unit@> dst_neighbor_unit_arr(0);
			array<pk::point> ring_arr = pk::ring(dst_unit.pos, 1);
			for (int i = 0; i < int(ring_arr.length); i++)
			{
				pk::point dst_neighbor_pos = ring_arr[i];
				pk::unit@ dst_neighbor_unit = pk::get_unit(dst_neighbor_pos);
				if (!pk::is_alive(dst_neighbor_unit)) continue;
				if (!pk::is_enemy(src_unit, dst_neighbor_unit)) continue;
				if (dst_neighbor_unit.status != 부대상태_통상) continue;

				dst_neighbor_unit_arr.insertLast(dst_neighbor_unit);
			}

			if (int(dst_neighbor_unit_arr.length) == 0) return null;
			return dst_neighbor_unit_arr[pk::rand(int(dst_neighbor_unit_arr.length))];
		}

		// 실행부대가 특정 좌표에서 시설범위 내에 존재하는지 여부 반환
		bool is_in_facility_range(pk::unit@ src_unit, pk::point pos)
		{
			array<int> 범위형_함정 = {시설_불씨, 시설_화염종, 시설_업화종, 시설_화선};
			array<int> 직선형_함정 = {시설_화구, 시설_화염구, 시설_업화구, 시설_낙석};

			/// 참고 : 시설의 최대범위는 0 이상 10 이하 ('시설.xml' 참고)
			array<pk::point> range_arr = pk::range(pos, 1, 10);
			for (int pos_index = 0; pos_index < int(range_arr.length); pos_index++)
			{
				pk::point range_pos = range_arr[pos_index];
				pk::building@ building = pk::get_building(range_pos);
				if (!pk::is_alive(building)) continue;

				// 지정한 회피대상 시설이 아니면 제외
				/// 참고 : 회피대상 시설 배열
				int facility_id = building.facility;
				pk::facility@ facility = pk::get_facility(facility_id);
				if (회피대상_시설[facility.type].find(facility_id) < 0) continue;

				// 함정이 아닌 시설의 세력이 아군인 경우 제외
				if (facility.type != 시설종류_함정 and !pk::is_enemy(src_unit, building)) continue;

				/// 참고 : 시설의 최대거리와 좌표거리를 비교하는 시 도시의 경우에는 '최대거리+1'과 비교해야 함(도시가 맵에서 두 칸의 범위를 차지하기 때문)
				int min_range = facility.min_range;
				int max_range = (facility_id == 시설_도시) ? facility.max_range + 1 : facility.max_range;
				int distance = pk::get_distance(pos, range_pos);
				bool auto_attack = bool(pk::core["시설"][facility_id]["자동공격"]);

				// 부대가 시설범위 내에 존재하는지 확인
				if (distance >= min_range and distance <= max_range)
				{
					// 부대가 시설범위 내에 있는지 확인 : 석병팔진, 범위형 함정(불씨, 화염종, 업화종, 화선)
					if (facility_id == 시설_석병팔진 or 범위형_함정.find(facility_id) >= 0) return true;

					// 부대가 시설범위 내에 있고 해당시설과 일직선상에 위치하는지 확인 : 직선형 함정(화구, 화염구, 업화구, 낙석)
					else if (직선형_함정.find(facility_id) >= 0)
					{
						// 5칸 이내만 확인
						int direction = pk::get_direction(pos, range_pos);
						if (distance <= 5 and 방향별_일직선_좌표색인[direction].find(pos_index) >= 0) return true;
					}

					// 부대가 시설범위 내에 있고 해당시설의 자동공격이 활성화되어 있는지 확인
					/// 참고 : 회피대상 시설 배열
					else if (auto_attack) return true;
				}
			}

			return false;
		}

		// 대상부대 주변에 존재하는 실행부대의 적군 부대수 및 병사수, 아군 부대수 및 병사수 반환
		array<int> func_대상부대_근처부대_관련정보_배열(pk::unit@ src_unit, pk::unit@ dst_unit, int distance)
		{
			array<int> units_and_troops_info(4, 0);
			array<pk::point> range = pk::range(dst_unit.pos, 1, distance);
			for (int i = 0; i < int(range.length); i++)
			{
				pk::unit@ unit = pk::get_unit(range[i]);
				if (!pk::is_alive(unit)) continue;
				if (@unit == @src_unit) continue;

				if (pk::is_enemy(src_unit, unit))
				{
					// 배열 색인 0 : 대상부대 주변에 존재하는 실행부대의 적군 부대수
					units_and_troops_info[0]++;

					// 배열 색인 1 : 대상부대 주변에 존재하는 실행부대의 적군 병사수
					units_and_troops_info[1] += unit.troops;
				}
				else
				{
					// 배열 색인 2 : 대상부대 주변에 존재하는 실행부대의 아군 부대수
					units_and_troops_info[2]++;

					// 배열 색인 3 : 대상부대 주변에 존재하는 실행부대의 아군 병사수
					units_and_troops_info[3] += unit.troops;
				}
			}

			return units_and_troops_info;
		}

	/**
		[ 참고 ] 도시 공성전 방어조건

		1. 공성전 방어조건을 충족하는 대상부대에게 우선적으로 계략을 실행
		2. 공성전 방어 판단조건
		 1) 세력조건 : 대상부대 좌표구역의 도시가 실행부대 세력의 아군 도시일 것
		 2) 거리조건 : 대상부대 좌표구역의 도시와 대상부대 사이의 거리가 일정거리 미만일 것
		 3) 병기조건 : 대상부대의 병종이 공성병기일 것
		 4) 내구조건 : 대상부대 좌표구역 도시의 내구도가 해당도시 최대내구의 일정비율 이하일 것
	*/
		bool func_공성전_방어조건_충족여부(pk::unit@ src_unit, pk::unit@ dst_unit)
		{
			pk::city@ area_city = pk::get_city(pk::get_city_id(dst_unit.pos));
			if (!pk::is_alive(area_city)) return false;

			// 세력조건 : 대상부대 좌표구역의 도시가 실행부대 세력의 적군 도시인 경우 제외
			if (pk::is_enemy(area_city, src_unit)) return false;

			// 거리조건 : 대상부대 좌표구역의 도시와 대상부대 사이의 거리가 일정거리 이상인 경우 제외
			/// 참고 : 도시가 맵에서 두 칸의 범위를 차지하기 때문에 실제 원하는 거리를 비교하기 위해서는 -1을 해주어야 함
			int distance = pk::get_distance(area_city.get_pos(), dst_unit.pos) - 1;
			if (distance >= 공성전_방어조건_기준거리) return false;

			// 병기조건 : 대상부대의 병종이 공성병기가 아닌 경우 제외
			/// 참고 : 물지형을 거쳐 공격해오는 경우가 있으므로 현재 지형에서의 병기가 아닌 육상병기로 반영
			int dst_ground_wpn_id = pk::get_ground_weapon_id(dst_unit);
			int dst_heishu = pk::equipment_id_to_heishu(dst_ground_wpn_id);
			if (dst_heishu != 병종_병기) return false;

			// 내구조건 : 대상부대 좌표구역 도시의 내구도가 해당도시 최대내구의 일정비율을 초과하는 경우 제외
			if (int(pk::get_hp(area_city)) > int(area_city.max_hp) * 공성전_방어조건_기준내구비율 / 100) return false;

			// 병력조건 : 대상부대 좌표구역 도시의 병력이 기준값을 초과하는 경우 제외
			if (int(area_city.troops) > 공성전_방어조건_기준병력) return false;

			return true;
		}

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	}

	Main main;
}