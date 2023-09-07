
	/// 내정 자동화 항목 (도시별 허용/금지 설정 가능)
	//	- 각 항목별로 모든 도시에 대하여 일괄적으로 허용/금지 여부 설정 가능
	// 1. 순찰 (초기 설정 : 금지)
	// 2. 훈련 (초기 설정 : 금지)
	// 3. 징병 (초기 설정 : 금지)
	// 4. 포상 (초기 설정 : 금지)
	// 5. 수송 (초기 설정 : 금지)

	/// 내정 자동화 명령 실행
	// 1. 플레이어 1군단 도시만 적용
	// 2. 턴종료 시 명령 실행
	// 3. 내정 명령 실행을 위한 기존의 기본 조건을 충족해야 실행 (행동력, 금, 행동가능 무장, 필요 시설 등)
	//	- 단, 행동력의 경우에는 소모 여부 유저설정 가능
	// 4. '허용'으로 설정된 내정 항목에 대해서만 실행
	// 5. 설정한 내정 자동화 기준을 충족하는 경우에만 실행
	// 6. 내정 명령 실행 시 메시지 표시 (메시지 박스, 로그 메시지 - 표시형태 유저 설정 가능)

	/// 내정 자동화 기준 (도시별 기준 설정 가능)
	//	- 각 항목별로 모든 도시에 대하여 일괄적으로 기준 설정 가능
	// 1. 순찰기준_치안		(초기 설정 : 90)	- 도시의 치안이 설정된 순찰기준 치안 이하일 경우 순찰 
	// 2. 훈련기준_기력비율	(초기 설정 : 95(%))	- 도시의 최대 기력 대비 현재 기력의 비율이 설정된 훈련비율 이하일 경우 훈련
	// 3. 징병기준_치안		(초기 설정 : 95)	- 도시의 치안이 설정된 징병기준 치안 이상일 경우 징병
	// 4. 징병기준_금		(초기 설정 : 2000)	- 도시의 금이 설정된 징병기준 금 이상일 경우 징병
	// 5. 징병기준_병량비율	(초기 설정 : 150(%))- 도시의 현재 병력 대비 현재 병량의 비율이 설정된 징병기준 병량비율 이상일 경우 징병
	// 6. 포상기준_충성도	(초기 설정 : 90)	- 무장의 충성도가 설정된 포상기준 충성도 이하일 경우 포상

	/// 내정 자동화 순서 모드 (포상, 수송은 순서 고정)
	//  - 모든 도시에 대하여 일괄적으로 내정 순서 모드 설정 가능
	// 모드 1 : 순찰 - 훈련 - 징병 - 포상 - 수송 (초기 설정)
	// 모드 2 : 순찰 - 징병 - 훈련 - 포상 - 수송
	// 모드 3 : 징병 - 순찰 - 훈련 - 포상 - 수송
	// 모드 4 : 징병 - 훈련 - 순찰 - 포상 - 수송
	// 모드 5 : 훈련 - 징병 - 순찰 - 포상 - 수송
	// 모드 6 : 훈련 - 순찰 - 징병 - 포상 - 수송

	/// 참고 사항
	// 1. 기존에 플레이하던 세이브 파일을 로드한 경우에는 항목별로 초기 설정이 다르게 설정되어 있을 수 있습니다.
	//	- 세이브 파일을 이동하시는 경우 PK2.1 패치 내 SaveData 폴더의 저장파일도 함께 옮겨 보관하셔야 설정이 유지됩니다.
	//	(설정 변경 값들은 해당 폴더의 세이브 파일에 저장되는 것으로 보입니다. '철거금지.cpp' 관련 설정도 마찬가지입니다.)
	// 2. 자세력 도시를 빼앗긴 경우 설정별 초기화 여부
	//	- 내정 자동화 순서 설정값 : 초기화됨 (이후 재탈환 시 초기 설정으로 초기화)
	//	- 내정 자동화 항목별 허용/금지 설정값 : 초기화됨 (이후 재탈환 시 초기 설정으로 초기화)
	//	- 내정 자동화 기준 설정값 : 초기화되지 않음 (이후 재탈환 시 기존 설정값이 반영됨)
	// 3. 도시에 커서를 가져가면 화면 우측 상단에 내정 자동화 관련 정보가 표시됩니다.
	//	- 내정 자동화 순서, 내정 자동화 항목별 허용/금지 여부, 내정 자동화 기준값의 설정이 반영되어 표시됩니다.
	// 4. 수송 자동화는 전방 도시(적 도시와 인접)끼리는 이루어지지 않습니다.
	// 5. 나머지 내용은 아래 CUSTOMIZE 부분을 참고하시기 바랍니다.
	// 6. "철거금지" 해시 값의 KEY 인덱스 번호(uint16)는 50~650 정도까지 사용했습니다.
	//	- 기존 '철거금지.cpp' 파일에서는 0~47 사용하고 있습니다.

namespace 도시내정자동화
{

/// ================================== CUSTOMIZE ============================================


	/// 내정 자동화 수행 시 행동력 소모 여부 설정
	const bool 내정자동화_행동력소모_적용 = true;	// true = 행동력 소모, 행동력 부족 시 미수행

	/// 내정 자동화 수행 시 메시지 박스 표시 설정
	const bool 내정자동화_메시지박스_표시 = true;	// true = 메시지 박스 표시, false = 로그 메시지 표시

	/// 커서를 자세력 1군단 도시에 갖다 대는 경우 화면 우측 상단에 내정 자동화 설정상태를 표시
	const bool 내정자동화_설정상태표시 = true;

///	-----------------------------------------------------------------------------------------

	/// 단축키 설정

	// 순서 모드 설정 메뉴
	const string 상위메뉴_순서 = "Z";
	const string 하위메뉴_순서_일괄설정 = "1";
	const string 하위메뉴_순서 = "2";

	// 허용/금지 설정 메뉴
	const string 상위메뉴_허용금지 = "X";
	const string 하위메뉴_허용금지_일괄설정_간소화 = "Q";
	const string 하위메뉴_허용금지_일괄설정 = "1";
	const string 하위메뉴_허용금지_순찰 = "2";
	const string 하위메뉴_허용금지_훈련 = "3";
	const string 하위메뉴_허용금지_징병 = "4";
	const string 하위메뉴_허용금지_포상 = "5";
	const string 하위메뉴_허용금지_수송 = "6";

	// 내정 기준 설정 메뉴
	const string 상위메뉴_기준 = "C";
	const string 하위메뉴_기준_일괄설정 = "1";
	const string 하위메뉴_기준_순찰_치안 = "2";
	const string 하위메뉴_기준_훈련_기력비율 = "3";
	const string 하위메뉴_기준_징병_치안 = "4";
	const string 하위메뉴_기준_징병_금 = "5";
	const string 하위메뉴_기준_징병_병량비율 = "6";
	const string 하위메뉴_기준_포상_충성도 = "7";

///	-----------------------------------------------------------------------------------------

	/// 수송 내정 자동화 관련 설정

	// 수송부대가 출진할 도시의 현재 병력 대비 수송할 병력 비율
	const float 수송병력비율 = 0.5f;

	// true = 후방 도시로부터 경계 도시까지 수송 (경계 도시 = 적 도시와 거리 2)
	// false = 후방, 경계 도시로부터 경계, 전방 도시까지 수송 (전방 도시 = 적 도시와 거리 1)
	const bool 수송한계설정_경계도시까지 = true;

	// 수송부대가 출진할 도시의 최대 병력 대비 현재 병력의 비율
	// 기본값 설명 : 현재 병력이 최대 병력의 0.5배 이상인 경우 수송
	const float 수송가능조건_병력조건 = 0.5f;

	// 수송부대가 출진할 도시의 현재 병력 대비 현재 병량의 비율
	// 기본값 설명 : 현재 병량이 현재 병력의 1.5배 이상인 경우 수송
	const float 수송가능조건_병량조건 = 1.5f;

	// 수송 후보 도시의 최대 병력 대비 현재 병력의 비율
	// 기본값 설명 : 수송 후보 도시의 현재 병력이 최대 병력의 0.5배 이하인 경우 수송
	const float 수송필요조건_병력조건1 = 0.5f;

	// 수송부대가 출진할 도시의 병력 대비 수송 후보 도시의 병력 비율
	// 기본값 설명 : 수송 후보 도시의 현재 병력이 수송부대가 출진할 도시 현재 병력의 0.5배 이하인 경우 수송
	const float 수송필요조건_병력조건2 = 0.5f;


/// =========================================================================================


	const bool 디버깅 = false;

	/// 정보 저장용 해시 값
	// 테스트 결과 pk::hash 함수가 "철거금지" 말고 다른 문장의 해시 값을 지원하지 않는 것으로 추정됨
	// 부득이하게 "철거금지" 문장의 해시 값을 사용하되 인덱스 값이 기존의 '철거금지.cpp' 파일과 충돌하지 않도록 적용
	const int KEY = pk::hash("철거금지");

	/// 항목별 KEY index 값 (uint16)
	// 참고 : '철거금지.cpp'에서 사용하는 KEY 인덱스 값 범위 : 0 <= i < 47 (전체 세력 수 = 47)
	const int KEY_인덱스값_추가_순서 = 50;					//  50	<= i <	 92 (전체 도시 수 = 42)
	const int KEY_인덱스값_추가_순찰 = 100;					// 100	<= i <	147 (전체 세력 수 = 47)
	const int KEY_인덱스값_추가_훈련 = 150;					// 150	<= i <	197 (전체 세력 수 = 47)
	const int KEY_인덱스값_추가_징병 = 200;					// 200	<= i <	247 (전체 세력 수 = 47)
	const int KEY_인덱스값_추가_포상 = 250;					// 250	<= i <	297 (전체 세력 수 = 47)
	const int KEY_인덱스값_추가_포상기준_충성도 = 300;		// 300	<= i <	342 (전체 도시 수 = 42)
	const int KEY_인덱스값_추가_수송 = 350;					// 350	<= i <	397 (전체 세력 수 = 47)
	const int KEY_인덱스값_추가_순찰기준_치안 = 400;		// 400	<= i <	442 (전체 도시 수 = 42)
	const int KEY_인덱스값_추가_훈련기준_기력비율 = 450;	// 450	<= i <	492 (전체 도시 수 = 42)
	const int KEY_인덱스값_추가_징병기준_치안 = 500;		// 500	<= i <	542 (전체 도시 수 = 42)
	const int KEY_인덱스값_추가_징병기준_금 = 550;			// 550	<= i <	592 (전체 도시 수 = 42)
	const int KEY_인덱스값_추가_징병기준_병량비율 = 600;	// 600	<= i <	642 (전체 도시 수 = 42)

	/// 내정 자동화 인덱스용 항목
	const int 내정자동화_순찰 = 0;
	const int 내정자동화_훈련 = 1;
	const int 내정자동화_징병 = 2;
	const int 내정자동화_포상 = 3;
	const int 내정자동화_수송 = 4;

	/// 참고 : 도시 메뉴
	// 도시 : 개발, 징병(적용), 순찰(적용), 생산, 거래
	// 군사 : 훈련(적용), 수송(적용)
	// 인재 : 탐색, 등용, 포상(적용)
	// 외교 : 이호경식, 구호탄랑, 유언비어


	class Main
	{
		/// 도시별 내정 자동화 순서 정보, 포상기준 충성도 저장용 목록
		// 저장 방법 : 도시별로 순서 값 저장 (초기화 없이 고정된 순서 값 저장)
		array<int> 내정자동화_순서정보(도시_끝, 1);	// 초기 설정 : 순서 모드 1
		array<int> 포상기준_충성도(도시_끝, 90);	// 초기 설정 : 90
		array<int> 순찰기준_치안(도시_끝, 90);		// 초기 설정 : 90
		array<int> 훈련기준_기력비율(도시_끝, 95);	// 초기 설정 : 95(%)
		array<int> 징병기준_치안(도시_끝, 95);		// 초기 설정 : 95
		array<int> 징병기준_금(도시_끝, 2000);		// 초기 설정 : 2000
		array<int> 징병기준_병량비율(도시_끝, 150);	// 초기 설정 : 150(%)

		/// 세력별 내정 자동화 허용여부 정보 저장용 목록
		// 저장 방법 : 세력별로 모든 도시에 대해 정보를 저장(비트 연산 활용)
		array<uint64> 순찰_허용여부(세력_끝, uint64(0));	// 초기 설정 : 금지
		array<uint64> 훈련_허용여부(세력_끝, uint64(0));	// 초기 설정 : 금지
		array<uint64> 징병_허용여부(세력_끝, uint64(0));	// 초기 설정 : 금지
		array<uint64> 포상_허용여부(세력_끝, uint64(0));	// 초기 설정 : 금지
		array<uint64> 수송_허용여부(세력_끝, uint64(0));	// 초기 설정 : 금지

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		Main()
		{
			/// 내정 자동화 설정 메뉴
			add_menu_도시내정자동화();

			/// 내정 자동화 설정 표시
			// 거점에 커서를 갖다 대는 경우 해당 거점의 내정 자동화 설정 정보 표시
			pk::bind(120, pk::trigger120_t(게임화면그리기_도시내정자동화_정보표시));

			/// 내정 자동화 실행 트리거
			pk::bind(112, pk::trigger112_t(턴종료_도시내정자동화));

			/// 정보 관리용 트리거
			pk::bind(102, pk::trigger102_t(시나리오초기화_도시내정자동화_정보불러오기));
			pk::bind(105, pk::trigger105_t(저장_도시내정자동화_정보저장));
			pk::bind(111, pk::trigger111_t(턴시작_도시내정자동화_정보초기화));
		}

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		void add_menu_도시내정자동화()
		{
			pk::menu_item 내정자동화_상위메뉴_순서;
			int parent_순서;
			내정자동화_상위메뉴_순서.menu = 0;
			내정자동화_상위메뉴_순서.shortcut = 상위메뉴_순서;
			내정자동화_상위메뉴_순서.init = pk::building_menu_item_init_t(init);
			내정자동화_상위메뉴_순서.is_visible = pk::menu_item_is_visible_t(isVisible);
			내정자동화_상위메뉴_순서.get_text = cast<pk::menu_item_get_text_t@>(function(){return pk::encode("자동내정 순서");});
			parent_순서 = pk::add_menu_item(내정자동화_상위메뉴_순서);

			pk::menu_item 내정자동화_상위메뉴_허용금지;
			int parent_허용금지;
			내정자동화_상위메뉴_허용금지.menu = 0;
			내정자동화_상위메뉴_허용금지.shortcut = 상위메뉴_허용금지;
			내정자동화_상위메뉴_허용금지.init = pk::building_menu_item_init_t(init);
			내정자동화_상위메뉴_허용금지.is_visible = pk::menu_item_is_visible_t(isVisible);
			내정자동화_상위메뉴_허용금지.get_text = cast<pk::menu_item_get_text_t@>(function(){return pk::encode("자동내정 토글");});
			parent_허용금지 = pk::add_menu_item(내정자동화_상위메뉴_허용금지);

			pk::menu_item 내정자동화_상위메뉴_기준;
			int parent_기준;
			내정자동화_상위메뉴_기준.menu = 0;
			내정자동화_상위메뉴_기준.shortcut = 상위메뉴_기준;
			내정자동화_상위메뉴_기준.init = pk::building_menu_item_init_t(init);
			내정자동화_상위메뉴_기준.is_visible = pk::menu_item_is_visible_t(isVisible);
			내정자동화_상위메뉴_기준.get_text = cast<pk::menu_item_get_text_t@>(function(){return pk::encode("자동내정 기준");});
			parent_기준 = pk::add_menu_item(내정자동화_상위메뉴_기준);

			pk::menu_item 내정자동화_메뉴_일괄변경_순서;
			내정자동화_메뉴_일괄변경_순서.menu = parent_순서;
			내정자동화_메뉴_일괄변경_순서.shortcut = 하위메뉴_순서_일괄설정;
			내정자동화_메뉴_일괄변경_순서.get_text = pk::menu_item_get_text_t(getText_일괄변경_순서);
			내정자동화_메뉴_일괄변경_순서.get_desc = pk::menu_item_get_desc_t(getDesc_일괄변경_순서);
			내정자동화_메뉴_일괄변경_순서.handler = pk::menu_item_handler_t(handler_일괄변경_순서);
			pk::add_menu_item(내정자동화_메뉴_일괄변경_순서);

			pk::menu_item 내정자동화_메뉴_순서;
			내정자동화_메뉴_순서.menu = parent_순서;
			내정자동화_메뉴_순서.shortcut = 하위메뉴_순서;
			내정자동화_메뉴_순서.get_text = pk::menu_item_get_text_t(getText_순서);
			내정자동화_메뉴_순서.get_desc = pk::menu_item_get_desc_t(getDesc_순서);
			내정자동화_메뉴_순서.handler = pk::menu_item_handler_t(handler_순서);
			pk::add_menu_item(내정자동화_메뉴_순서);

			pk::menu_item 내정자동화_메뉴_일괄변경_허용여부_간소화;
			내정자동화_메뉴_일괄변경_허용여부_간소화.menu = parent_허용금지;
			내정자동화_메뉴_일괄변경_허용여부_간소화.shortcut = 하위메뉴_허용금지_일괄설정_간소화;
			내정자동화_메뉴_일괄변경_허용여부_간소화.get_text = pk::menu_item_get_text_t(getText_일괄변경_허용여부_간소화);
			내정자동화_메뉴_일괄변경_허용여부_간소화.get_desc = pk::menu_item_get_desc_t(getDesc_일괄변경_허용여부_간소화);
			내정자동화_메뉴_일괄변경_허용여부_간소화.handler = pk::menu_item_handler_t(handler_일괄변경_허용여부_간소화);
			pk::add_menu_item(내정자동화_메뉴_일괄변경_허용여부_간소화);

			pk::menu_item 내정자동화_메뉴_일괄변경_허용여부;
			내정자동화_메뉴_일괄변경_허용여부.menu = parent_허용금지;
			내정자동화_메뉴_일괄변경_허용여부.shortcut = 하위메뉴_허용금지_일괄설정;
			내정자동화_메뉴_일괄변경_허용여부.get_text = pk::menu_item_get_text_t(getText_일괄변경_허용여부);
			내정자동화_메뉴_일괄변경_허용여부.get_desc = pk::menu_item_get_desc_t(getDesc_일괄변경_허용여부);
			내정자동화_메뉴_일괄변경_허용여부.handler = pk::menu_item_handler_t(handler_일괄변경_허용여부);
			pk::add_menu_item(내정자동화_메뉴_일괄변경_허용여부);

			pk::menu_item 내정자동화_메뉴_순찰_허용여부;
			내정자동화_메뉴_순찰_허용여부.menu = parent_허용금지;
			내정자동화_메뉴_순찰_허용여부.shortcut = 하위메뉴_허용금지_순찰;
			내정자동화_메뉴_순찰_허용여부.get_text = pk::menu_item_get_text_t(getText_순찰);
			내정자동화_메뉴_순찰_허용여부.get_desc = pk::menu_item_get_desc_t(getDesc_순찰);
			내정자동화_메뉴_순찰_허용여부.handler = pk::menu_item_handler_t(handler_순찰);
			pk::add_menu_item(내정자동화_메뉴_순찰_허용여부);

			pk::menu_item 내정자동화_메뉴_훈련_허용여부;
			내정자동화_메뉴_훈련_허용여부.menu = parent_허용금지;
			내정자동화_메뉴_훈련_허용여부.shortcut = 하위메뉴_허용금지_훈련;
			내정자동화_메뉴_훈련_허용여부.get_text = pk::menu_item_get_text_t(getText_훈련);
			내정자동화_메뉴_훈련_허용여부.get_desc = pk::menu_item_get_desc_t(getDesc_훈련);
			내정자동화_메뉴_훈련_허용여부.handler = pk::menu_item_handler_t(handler_훈련);
			pk::add_menu_item(내정자동화_메뉴_훈련_허용여부);

			pk::menu_item 내정자동화_메뉴_징병_허용여부;
			내정자동화_메뉴_징병_허용여부.menu = parent_허용금지;
			내정자동화_메뉴_징병_허용여부.shortcut = 하위메뉴_허용금지_징병;
			내정자동화_메뉴_징병_허용여부.get_text = pk::menu_item_get_text_t(getText_징병);
			내정자동화_메뉴_징병_허용여부.get_desc = pk::menu_item_get_desc_t(getDesc_징병);
			내정자동화_메뉴_징병_허용여부.handler = pk::menu_item_handler_t(handler_징병);
			pk::add_menu_item(내정자동화_메뉴_징병_허용여부);

			pk::menu_item 내정자동화_메뉴_포상_허용여부;
			내정자동화_메뉴_포상_허용여부.menu = parent_허용금지;
			내정자동화_메뉴_포상_허용여부.shortcut = 하위메뉴_허용금지_포상;
			내정자동화_메뉴_포상_허용여부.get_text = pk::menu_item_get_text_t(getText_포상);
			내정자동화_메뉴_포상_허용여부.get_desc = pk::menu_item_get_desc_t(getDesc_포상);
			내정자동화_메뉴_포상_허용여부.handler = pk::menu_item_handler_t(handler_포상);
			pk::add_menu_item(내정자동화_메뉴_포상_허용여부);

			pk::menu_item 내정자동화_메뉴_수송_허용여부;
			내정자동화_메뉴_수송_허용여부.menu = parent_허용금지;
			내정자동화_메뉴_수송_허용여부.shortcut = 하위메뉴_허용금지_수송;
			내정자동화_메뉴_수송_허용여부.get_text = pk::menu_item_get_text_t(getText_수송);
			내정자동화_메뉴_수송_허용여부.get_desc = pk::menu_item_get_desc_t(getDesc_수송);
			내정자동화_메뉴_수송_허용여부.handler = pk::menu_item_handler_t(handler_수송);
			pk::add_menu_item(내정자동화_메뉴_수송_허용여부);

			pk::menu_item 내정자동화_메뉴_일괄변경_기준;
			내정자동화_메뉴_일괄변경_기준.menu = parent_기준;
			내정자동화_메뉴_일괄변경_기준.shortcut = 하위메뉴_기준_일괄설정;
			내정자동화_메뉴_일괄변경_기준.get_text = pk::menu_item_get_text_t(getText_일괄변경_기준);
			내정자동화_메뉴_일괄변경_기준.get_desc = pk::menu_item_get_desc_t(getDesc_일괄변경_기준);
			내정자동화_메뉴_일괄변경_기준.handler = pk::menu_item_handler_t(handler_일괄변경_기준);
			pk::add_menu_item(내정자동화_메뉴_일괄변경_기준);

			pk::menu_item 내정자동화_메뉴_순찰기준_치안;
			내정자동화_메뉴_순찰기준_치안.menu = parent_기준;
			내정자동화_메뉴_순찰기준_치안.shortcut = 하위메뉴_기준_순찰_치안;
			내정자동화_메뉴_순찰기준_치안.get_text = pk::menu_item_get_text_t(getText_순찰기준_치안);
			내정자동화_메뉴_순찰기준_치안.get_desc = pk::menu_item_get_desc_t(getDesc_순찰기준_치안);
			내정자동화_메뉴_순찰기준_치안.handler = pk::menu_item_handler_t(handler_순찰기준_치안);
			pk::add_menu_item(내정자동화_메뉴_순찰기준_치안);

			pk::menu_item 내정자동화_메뉴_훈련기준_기력비율;
			내정자동화_메뉴_훈련기준_기력비율.menu = parent_기준;
			내정자동화_메뉴_훈련기준_기력비율.shortcut = 하위메뉴_기준_훈련_기력비율;
			내정자동화_메뉴_훈련기준_기력비율.get_text = pk::menu_item_get_text_t(getText_훈련기준_기력비율);
			내정자동화_메뉴_훈련기준_기력비율.get_desc = pk::menu_item_get_desc_t(getDesc_훈련기준_기력비율);
			내정자동화_메뉴_훈련기준_기력비율.handler = pk::menu_item_handler_t(handler_훈련기준_기력비율);
			pk::add_menu_item(내정자동화_메뉴_훈련기준_기력비율);

			pk::menu_item 내정자동화_메뉴_징병기준_치안;
			내정자동화_메뉴_징병기준_치안.menu = parent_기준;
			내정자동화_메뉴_징병기준_치안.shortcut = 하위메뉴_기준_징병_치안;
			내정자동화_메뉴_징병기준_치안.get_text = pk::menu_item_get_text_t(getText_징병기준_치안);
			내정자동화_메뉴_징병기준_치안.get_desc = pk::menu_item_get_desc_t(getDesc_징병기준_치안);
			내정자동화_메뉴_징병기준_치안.handler = pk::menu_item_handler_t(handler_징병기준_치안);
			pk::add_menu_item(내정자동화_메뉴_징병기준_치안);

			pk::menu_item 내정자동화_메뉴_징병기준_금;
			내정자동화_메뉴_징병기준_금.menu = parent_기준;
			내정자동화_메뉴_징병기준_금.shortcut = 하위메뉴_기준_징병_금;
			내정자동화_메뉴_징병기준_금.get_text = pk::menu_item_get_text_t(getText_징병기준_금);
			내정자동화_메뉴_징병기준_금.get_desc = pk::menu_item_get_desc_t(getDesc_징병기준_금);
			내정자동화_메뉴_징병기준_금.handler = pk::menu_item_handler_t(handler_징병기준_금);
			pk::add_menu_item(내정자동화_메뉴_징병기준_금);

			pk::menu_item 내정자동화_메뉴_징병기준_병량비율;
			내정자동화_메뉴_징병기준_병량비율.menu = parent_기준;
			내정자동화_메뉴_징병기준_병량비율.shortcut = 하위메뉴_기준_징병_병량비율;
			내정자동화_메뉴_징병기준_병량비율.get_text = pk::menu_item_get_text_t(getText_징병기준_병량비율);
			내정자동화_메뉴_징병기준_병량비율.get_desc = pk::menu_item_get_desc_t(getDesc_징병기준_병량비율);
			내정자동화_메뉴_징병기준_병량비율.handler = pk::menu_item_handler_t(handler_징병기준_병량비율);
			pk::add_menu_item(내정자동화_메뉴_징병기준_병량비율);

			pk::menu_item 내정자동화_메뉴_포상기준_충성도;
			내정자동화_메뉴_포상기준_충성도.menu = parent_기준;
			내정자동화_메뉴_포상기준_충성도.shortcut = 하위메뉴_기준_포상_충성도;
			내정자동화_메뉴_포상기준_충성도.get_text = pk::menu_item_get_text_t(getText_포상기준_충성도);
			내정자동화_메뉴_포상기준_충성도.get_desc = pk::menu_item_get_desc_t(getDesc_포상기준_충성도);
			내정자동화_메뉴_포상기준_충성도.handler = pk::menu_item_handler_t(handler_포상기준_충성도);
			pk::add_menu_item(내정자동화_메뉴_포상기준_충성도);
		}

		void 게임화면그리기_도시내정자동화_정보표시()
		{
			if (!내정자동화_설정상태표시) return;

			// 커서가 가리키는 좌표
			pk::point cursor_pos = pk::get_cursor_hex_pos();
			if (!pk::is_valid_pos(cursor_pos)) return;

			// 커서가 가리키는 좌표 상의 건물
			pk::building@ building = pk::get_building(cursor_pos);
			if (building is null) return;

			// 커서가 가리키는 좌표 상의 도시
			pk::city@ city = pk::building_to_city(building);
			if (city is null) return;

			// 도시의 좌표 조건 확인
			pk::point city_pos = city.get_pos();
			if (!pk::is_valid_pos(city_pos))return;

			// 도시의 세력 및 군단 조건 확인
			if (!city.is_player()) return;
			if (!pk::is_player_controlled(city)) return;
			if (city.get_force_id() != pk::get_current_turn_force_id()) return;

			// 내정 자동화 설정 정보 표시
			func_내정자동화_정보표시(building, pk::get_current_turn_force_id(), city.get_id(), 내정자동화_순서정보[city.get_id()]);
		}

		void 턴종료_도시내정자동화(pk::force@ force)
		{
			if (!force.is_player()) return;	// 컴퓨터 세력 제외

			array<pk::city@> city_list = pk::list_to_array(pk::get_city_list(force));	// 세력 도시 목록
			for (int i = 0; i < int(city_list.length); i++)
			{
				pk::city@ city = city_list[i];
				pk::building@ building = pk::city_to_building(city);

				if (디버깅)
				{
					string city_name = pk::format("도시 \x1b[1x{}\x1b[0x", pk::decode(pk::get_name(city)));
					pk::message_box(pk::encode(pk::format("{} 확인됨", city_name)));
				}

				if (!pk::is_player_controlled(building))			continue;	// 플레이어 위임군단 도시인 경우 제외
				if (pk::get_idle_person_list(building).count == 0)	continue;	// 행동가능 무장이 없는 경우 제외

				/// 참고 사항
				// cmd 구조체를 사용하여 내정 명령을 실행하는 경우 실행이 불가능한 상황이면 알아서 실행하지 않음 (무장 포상 제외)
				// 따로 실행이 불가능한 경우를 조건으로 추가하지 않아도 됨 (행동력 소비량, 요구 시설, 행동가능 무장 존재, 금 소비량 등)
				func_내정자동화(force, city, 내정자동화_순서정보[city.get_id()]);
			}
		}

		void 시나리오초기화_도시내정자동화_정보불러오기()
		{
			for (int i = 0; i < 도시_끝; i++)
			{
				내정자동화_순서정보[i] = int(pk::load(KEY, (i + KEY_인덱스값_추가_순서), 1));
				포상기준_충성도[i] = int(pk::load(KEY, (i + KEY_인덱스값_추가_포상기준_충성도), 90));
				순찰기준_치안[i] = int(pk::load(KEY, (i + KEY_인덱스값_추가_순찰기준_치안), 90));
				훈련기준_기력비율[i] = int(pk::load(KEY, (i + KEY_인덱스값_추가_훈련기준_기력비율), 95));
				징병기준_치안[i] = int(pk::load(KEY, (i + KEY_인덱스값_추가_징병기준_치안), 95));
				징병기준_금[i] = int(pk::load(KEY, (i + KEY_인덱스값_추가_징병기준_금), 2000));
				징병기준_병량비율[i] = int(pk::load(KEY, (i + KEY_인덱스값_추가_징병기준_병량비율), 150));

				// 로드된 항목별 값이 인덱스 범위를 벗어나는 경우 초기화
				if (내정자동화_순서정보[i] < 1 or 내정자동화_순서정보[i] > 6) 내정자동화_순서정보[i] = 1;
				if (포상기준_충성도[i] < 0 or 포상기준_충성도[i] > 99) 포상기준_충성도[i] = 90;
				if (순찰기준_치안[i] < 0 or 순찰기준_치안[i] > 100) 순찰기준_치안[i] = 90;
				if (훈련기준_기력비율[i] < 0 or 훈련기준_기력비율[i] > 100) 훈련기준_기력비율[i] = 95;
				if (징병기준_치안[i] < 0 or 징병기준_치안[i] > 100) 징병기준_치안[i] = 95;
				if (징병기준_금[i] < 0 or 징병기준_금[i] > 100000) 징병기준_금[i] = 2000;
				if (징병기준_병량비율[i] < 0 or 징병기준_병량비율[i] > 1000) 징병기준_병량비율[i] = 150;
			}
			for (int i = 0; i < 세력_끝; i++)
			{
				순찰_허용여부[i] = uint64(pk::load(KEY, (i + KEY_인덱스값_추가_순찰), uint64(0)));
				훈련_허용여부[i] = uint64(pk::load(KEY, (i + KEY_인덱스값_추가_훈련), uint64(0)));
				징병_허용여부[i] = uint64(pk::load(KEY, (i + KEY_인덱스값_추가_징병), uint64(0)));
				포상_허용여부[i] = uint64(pk::load(KEY, (i + KEY_인덱스값_추가_포상), uint64(0)));
				수송_허용여부[i] = uint64(pk::load(KEY, (i + KEY_인덱스값_추가_수송), uint64(0)));
			}
		}

		void 저장_도시내정자동화_정보저장(int file_id)
		{
			for (int i = 0; i < 도시_끝; i++)
			{
				pk::store(KEY, (i + KEY_인덱스값_추가_순서), 내정자동화_순서정보[i]);
				pk::store(KEY, (i + KEY_인덱스값_추가_포상기준_충성도), 포상기준_충성도[i]);
				pk::store(KEY, (i + KEY_인덱스값_추가_순찰기준_치안), 순찰기준_치안[i]);
				pk::store(KEY, (i + KEY_인덱스값_추가_훈련기준_기력비율), 훈련기준_기력비율[i]);
				pk::store(KEY, (i + KEY_인덱스값_추가_징병기준_치안), 징병기준_치안[i]);
				pk::store(KEY, (i + KEY_인덱스값_추가_징병기준_금), 징병기준_금[i]);
				pk::store(KEY, (i + KEY_인덱스값_추가_징병기준_병량비율), 징병기준_병량비율[i]);
			}
			for (int i = 0; i < 세력_끝; i++)
			{
				pk::store(KEY, (i + KEY_인덱스값_추가_순찰), 순찰_허용여부[i]);
				pk::store(KEY, (i + KEY_인덱스값_추가_훈련), 훈련_허용여부[i]);
				pk::store(KEY, (i + KEY_인덱스값_추가_징병), 징병_허용여부[i]);
				pk::store(KEY, (i + KEY_인덱스값_추가_포상), 포상_허용여부[i]);
				pk::store(KEY, (i + KEY_인덱스값_추가_수송), 수송_허용여부[i]);
			}
		}

		void 턴시작_도시내정자동화_정보초기화(pk::force@ force)
		{
			if (force.is_player())
			{
				int force_id = force.get_id();
				for (int city_id = 0; city_id < 도시_끝; city_id++)
				{
					pk::city@ city = pk::get_city(city_id);

					// 해당 세력의 도시가 아닌 경우 : '금지'로 초기화
					if (city.get_force_id() != force_id)
					{
						// value = false : 허용 -> 금지
						set(force_id, city_id, false, 내정자동화_순찰);
						set(force_id, city_id, false, 내정자동화_훈련);
						set(force_id, city_id, false, 내정자동화_징병);
						set(force_id, city_id, false, 내정자동화_포상);
						set(force_id, city_id, false, 내정자동화_수송);
					}
				}
			}
		}

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		void func_내정자동화_정보표시(pk::building@ building, int force_id, int city_id, int 내정자동화_순서)
		{
			string building_name = pk::decode(pk::get_name(building));

			string title = pk::format("내정 자동화 (\x1b[1x{}\x1b[0x)", building_name);

			string order_info = pk::format("(순서 모드 : \x1b[1x{}\x1b[0x)", 내정자동화_순서);

			string inspections_enabled = "※ 순찰 : " + ((isEnabled(force_id, city_id, 내정자동화_순찰)) ? "\x1b[1x허용": "\x1b[1x금지");
			string drills_enabled = "※ 훈련 : " + ((isEnabled(force_id, city_id, 내정자동화_훈련)) ? "\x1b[1x허용": "\x1b[1x금지");
			string recruit_enabled = "※ 징병 : " + ((isEnabled(force_id, city_id, 내정자동화_징병)) ? "\x1b[1x허용": "\x1b[1x금지");
			string reward_enabled = "※ 포상 : " + ((isEnabled(force_id, city_id, 내정자동화_포상)) ? "\x1b[1x허용": "\x1b[1x금지");
			string deploy_enabled = "※ 수송 : " + ((isEnabled(force_id, city_id, 내정자동화_수송)) ? "\x1b[1x허용": "\x1b[1x금지");

			string std_inspections = pk::format("(순찰기준 치안 : \x1b[1x{}\x1b[0x)", 순찰기준_치안[city_id]);
			string std_drills = pk::format("(훈련기준 기력비율 : \x1b[1x{}\x1b[0x%)", 훈련기준_기력비율[city_id]);
			string std_recruit_order = pk::format("(징병기준 치안 : \x1b[1x{}\x1b[0x)", 징병기준_치안[city_id]);
			string std_recruit_gold = pk::format("(징병기준 금 : \x1b[1x{}\x1b[0x)", 징병기준_금[city_id]);
			string std_recruit_food = pk::format("(징병기준 병량비율 : \x1b[1x{}\x1b[0x%)", 징병기준_병량비율[city_id]);
			string std_reward = pk::format("(포상기준 충성도 : \x1b[1x{}\x1b[0x)", 포상기준_충성도[city_id]);

			array<string> str_내정자동화_순서(0);
			if		(내정자동화_순서 == 1)	str_내정자동화_순서 = {inspections_enabled, drills_enabled, recruit_enabled, reward_enabled, deploy_enabled};
			else if (내정자동화_순서 == 2)	str_내정자동화_순서 = {inspections_enabled, recruit_enabled, drills_enabled, reward_enabled, deploy_enabled};
			else if (내정자동화_순서 == 3)	str_내정자동화_순서 = {recruit_enabled, inspections_enabled, drills_enabled, reward_enabled, deploy_enabled};
			else if (내정자동화_순서 == 4)	str_내정자동화_순서 = {recruit_enabled, drills_enabled, inspections_enabled, reward_enabled, deploy_enabled};
			else if (내정자동화_순서 == 5)	str_내정자동화_순서 = {drills_enabled, recruit_enabled, inspections_enabled, reward_enabled, deploy_enabled};
			else if (내정자동화_순서 == 6)	str_내정자동화_순서 = {drills_enabled, inspections_enabled, recruit_enabled, reward_enabled, deploy_enabled};

			array<string> str_내정기준_순서(0);
			if		(내정자동화_순서 == 1)	str_내정기준_순서 = {std_inspections, std_drills, std_recruit_order, std_recruit_gold, std_recruit_food, std_reward};
			else if (내정자동화_순서 == 2)	str_내정기준_순서 = {std_inspections, std_recruit_order, std_recruit_gold, std_recruit_food, std_drills, std_reward};
			else if (내정자동화_순서 == 3)	str_내정기준_순서 = {std_recruit_order, std_recruit_gold, std_recruit_food, std_inspections, std_drills, std_reward};
			else if (내정자동화_순서 == 4)	str_내정기준_순서 = {std_recruit_order, std_recruit_gold, std_recruit_food, std_drills, std_inspections, std_reward};
			else if (내정자동화_순서 == 5)	str_내정기준_순서 = {std_drills, std_recruit_order, std_recruit_gold, std_recruit_food, std_inspections, std_reward};
			else if (내정자동화_순서 == 6)	str_내정기준_순서 = {std_drills, std_inspections, std_recruit_order, std_recruit_gold, std_recruit_food, std_reward};

			int width = int(pk::get_resolution().width) - 230;

			pk::draw_text(pk::encode(title), pk::point(width, 20), 0xffffffff, FONT_BIG, 0xff000000);
			pk::draw_text(pk::encode(order_info), pk::point(width, 55), 0xffffffff, FONT_SMALL, 0xff000000);

			int end = int(str_내정자동화_순서.length);
			for (int i = 0; i < end; i++)
			{
				pk::draw_text(pk::encode(str_내정자동화_순서[i]), pk::point(width, 75+i*20), 0xffffffff, FONT_SMALL, 0xff000000);
			}
			for (int i = 0; i < int(str_내정기준_순서.length); i++)
			{
				pk::draw_text(pk::encode(str_내정기준_순서[i]), pk::point(width, 75+(i+end)*20), 0xffffffff, FONT_SMALL, 0xff000000);
			}
		}

		void func_내정자동화(pk::force@ force, pk::city@ city, int 내정자동화_순서)
		{
			if		(내정자동화_순서 == 1)	{func_내정자동화_순찰(force, city);	func_내정자동화_훈련(force, city);	func_내정자동화_징병(force, city);}
			else if (내정자동화_순서 == 2)	{func_내정자동화_순찰(force, city);	func_내정자동화_징병(force, city);	func_내정자동화_훈련(force, city);}
			else if (내정자동화_순서 == 3)	{func_내정자동화_징병(force, city);	func_내정자동화_순찰(force, city);	func_내정자동화_훈련(force, city);}
			else if (내정자동화_순서 == 4)	{func_내정자동화_징병(force, city);	func_내정자동화_훈련(force, city);	func_내정자동화_순찰(force, city);}
			else if (내정자동화_순서 == 5)	{func_내정자동화_훈련(force, city);	func_내정자동화_징병(force, city);	func_내정자동화_순찰(force, city);}
			else if (내정자동화_순서 == 6)	{func_내정자동화_훈련(force, city);	func_내정자동화_순찰(force, city);	func_내정자동화_징병(force, city);}

			func_내정자동화_포상(force, city);
			func_내정자동화_수송(force, city);
		}

		void func_내정자동화_순찰(pk::force@ force, pk::city@ city)
		{
			pk::building@ building = pk::city_to_building(city);
			pk::district@ district = pk::get_district(building.get_district_id());
			pk::list<pk::person@> person_list = pk::get_idle_person_list(building);

			string city_name = pk::format("도시 \x1b[1x{}\x1b[0x", pk::decode(pk::get_name(city)));

			if (디버깅) pk::message_box(pk::encode(pk::format("{}의 순찰 실행조건 확인 시작", city_name)));

			// 기본 조건 확인
			if (내정자동화_행동력소모_적용 and int(district.ap) < 20)	return;	// 행동력 조건
			if (int(person_list.count) == 0)							return;	// 행동가능 무장 조건
			if (int(city.gold) < 100)									return;	// 도시 금 확인
			if (int(city.public_order) == 100)							return;	// 도시 치안 확인

			// 설정 조건 확인
			if (!isEnabled(force.get_id(), city.get_id(), 내정자동화_순찰))	return;	// 허용/금지 여부
			if (int(city.public_order) > 순찰기준_치안[city.get_id()])		return;	// 치안 기준

			if (디버깅) pk::message_box(pk::encode(pk::format("{}가 순찰 실행조건 통과", city_name)));

			/// 순찰 명령 정보
			pk::inspections_cmd_info cmd;

			// 순찰 실행 거점
			@cmd.base = @building;

			// 순찰 실행 무장
			person_list.sort(function(a, b){return a.stat[int(pk::core["순찰.능력"])] > b.stat[int(pk::core["순찰.능력"])];});
			pk::list<pk::person@> actors;
			actors.add(person_list[0]);
			if (int(city.public_order) + func_순찰치안증감_계산(city, building, actors) < 100)
			{
				if (int(person_list.count) > 1)
				{
					actors.add(person_list[1]);

					if (int(city.public_order) + func_순찰치안증감_계산(city, building, actors) < 100)
					{
						if (int(person_list.count) > 2) actors.add(person_list[2]);
					}
				}
			}
			int end = int(actors.count);
			array<string> person_name_list(0);
			for (int i = 0; i < end; i++)
			{
				@cmd.actors[i] = @actors[i];
				person_name_list.insertLast(pk::format("\x1b[1x{}\x1b[0x", pk::decode(pk::get_name(actors[i]))));
			}

			// 순찰 명령 실행
			if (!내정자동화_행동력소모_적용) district.ap += 20;
			bool is_inspections_ended = pk::command(cmd);

			// 순찰 실행 메시지
			if (is_inspections_ended)
			{
				string building_name = pk::format("\x1b[1x{}\x1b[0x에서 ", pk::decode(pk::get_name(building)));
				string person_names = join(person_name_list, ", ");
				string person_count_info = (end > 1) ? " 등": "";
				string action_info = pk::format(" {}명이\n순찰을 실행", end);
				string action_message = building_name + person_names + person_count_info + action_info;

				if (내정자동화_메시지박스_표시) pk::message_box(pk::encode(action_message));
				else							pk::history_log(building.pos, force.color, pk::encode(action_message));
			}
		}

		// '104 순찰 치안 증감.cpp' 참고 (PK2.1 기본 제공 파일 기준)
		int func_순찰치안증감_계산(pk::city@ city, pk::building@ building, pk::list<pk::person@> actors)
		{
			int n = 0;

			for (int i = 0; i < int(actors.count); i++) n = n + actors[i].stat[int(pk::core["순찰.능력"])];

			n = n / 28 + 2;

			if (pk::enemies_around(building)) n = n / 2;

			return n;
		}

		void func_내정자동화_훈련(pk::force@ force, pk::city@ city)
		{
			pk::building@ building = pk::city_to_building(city);
			pk::district@ district = pk::get_district(building.get_district_id());
			pk::list<pk::person@> person_list = pk::get_idle_person_list(building);
			int city_max_energy = (pk::has_tech(city, 기교_숙련병)) ? 120 : 100;

			string city_name = pk::format("도시 \x1b[1x{}\x1b[0x", pk::decode(pk::get_name(city)));

			if (디버깅) pk::message_box(pk::encode(pk::format("{} 훈련 실행조건 확인 시작", city_name)));

			// 기본 조건 확인
			if (내정자동화_행동력소모_적용 and int(district.ap) < 20)	return;	// 행동력 조건
			if (int(person_list.count) == 0)							return;	// 행동가능 무장 조건
			if (int(city.energy) == city_max_energy)					return;	// 도시 기력 확인

			// 설정 조건 확인
			if (!isEnabled(force.get_id(), city.get_id(), 내정자동화_훈련))	return;	// 허용/금지 여부
			if (디버깅)
			{
				pk::message_box(pk::encode(pk::format("최대 기력 대비 현재 기력 비율 : {}", float(city.energy) / float(city_max_energy))));
				pk::message_box(pk::encode(pk::format("훈련기준 기력비율 : {}", float(훈련기준_기력비율[city.get_id()]) / 100.0f)));
			}
			if (float(city.energy) / float(city_max_energy) > float(훈련기준_기력비율[city.get_id()]) / 100.0f) return;	// 기력비율 기준
		
			if (디버깅) pk::message_box(pk::encode(pk::format("{} 훈련 실행조건 통과", city_name)));

			/// 훈련 명령 정보
			pk::drill_cmd_info cmd;

			// 훈련 실행 거점
			@cmd.base = @building;

			// 훈련 실행 무장
			person_list.sort(function(a, b){return a.stat[int(pk::core["훈련.능력"])] > b.stat[int(pk::core["훈련.능력"])];});
			pk::list<pk::person@> actors;
			actors.add(person_list[0]);
			if (int(city.energy) + func_훈련기력증감_계산(city, building, actors) < city_max_energy)
			{
				if (int(person_list.count) > 1)
				{
					actors.add(person_list[1]);

					if (int(city.energy) + func_훈련기력증감_계산(city, building, actors) < city_max_energy)
					{
						if (int(person_list.count) > 2) actors.add(person_list[2]);
					}
				}
			}
			int end = int(actors.count);
			array<string> person_name_list(0);
			for (int i = 0; i < end; i++)
			{
				@cmd.actors[i] = @actors[i];
				person_name_list.insertLast(pk::format("\x1b[1x{}\x1b[0x", pk::decode(pk::get_name(actors[i]))));
			}

			// 훈련 명령 실행
			if (!내정자동화_행동력소모_적용) district.ap += 20;
			bool is_drills_ended = pk::command(cmd);

			// 훈련 실행 메시지
			if (is_drills_ended)
			{
				string building_name = pk::format("\x1b[1x{}\x1b[0x에서 ", pk::decode(pk::get_name(building)));
				string person_names = join(person_name_list, ", ");
				string person_count_info = (end > 1) ? " 등": "";
				string action_info = pk::format(" {}명이\n훈련을 실행", end);
				string action_message = building_name + person_names + person_count_info + action_info;

				if (내정자동화_메시지박스_표시)	pk::message_box(pk::encode(action_message));
				else							pk::history_log(building.pos, force.color, pk::encode(action_message));
			}
		}

		// '105 훈련 기력 증감.cpp' 참고 (PK2.1 기본 제공 파일 기준)
		int func_훈련기력증감_계산(pk::city@ city, pk::building@ building, pk::list<pk::person@> actors)
		{
			int n = 0, max = pk::INT32_MIN;

			for (int i = 0; i < int(actors.count); i++)
			{
				int s = actors[i].stat[int(pk::core["훈련.능력"])];
				n += s;
				max = pk::max(max, s);
			}

			n = (n + max) / pk::min(building.get_troops() / 2000 + 20, 100) + 3;

			if (building.facility == 시설_도시 and pk::has_facility(city, 시설_연병소)) n = int(n * 1.5f);

			return n;
		}

		void func_내정자동화_징병(pk::force@ force, pk::city@ city)
		{
			pk::building@ building = pk::city_to_building(city);
			pk::district@ district = pk::get_district(building.get_district_id());
			pk::list<pk::person@> person_list = pk::get_idle_person_list(building);

			string city_name = pk::format("도시 \x1b[1x{}\x1b[0x", pk::decode(pk::get_name(city)));

			if (디버깅) pk::message_box(pk::encode(pk::format("{} 징병 실행조건 확인 시작", city_name)));


			// 기본 조건 확인
			if (내정자동화_행동력소모_적용 and int(district.ap) < 20)	return;	// 행동력 조건
			if (int(person_list.count) == 0)							return;	// 행동가능 무장 조건
			if (int(city.gold) < 300)									return;	// 도시 금 확인
			if (!pk::has_facility(city, 시설_병영) and !pk::has_facility(city, 시설_병영2단) and !pk::has_facility(city, 시설_병영3단)) return;	// 도시 시설 확인

			// 설정 조건 확인
			if (!isEnabled(force.get_id(), city.get_id(), 내정자동화_징병))	return;	// 허용/금지 여부
			if (int(city.public_order) < 징병기준_치안[city.get_id()])		return;	// 치안 기준
			if (int(city.gold) < 징병기준_금[city.get_id()])				return;	// 금 기준
			if (디버깅)
			{
				pk::message_box(pk::encode(pk::format("현재 병력 대비 현재 병량 비율 : {}", float(city.food) / float(city.troops))));
				pk::message_box(pk::encode(pk::format("징병기준 병량비율 : {}", float(징병기준_병량비율[city.get_id()]) / 100.0f)));
			}
			if (float(city.food) / float(city.troops) < float(징병기준_병량비율[city.get_id()]) / 100.0f) return;	// 병량비율 기준

			if (디버깅) pk::message_box(pk::encode(pk::format("{} 징병 실행조건 통과", city_name)));

			/// 징병 명령 정보
			pk::recruit_cmd_info cmd;

			// 징병 실행 거점
			@cmd.base = @building;

			// 징병 실행 무장
			pk::person@ 징병특기_보유무장 = null;
			int 징병특기_보유무장_번호 = -1;
			int 징병특기_보유무장_징병능력 = 0;
			for (int i = 0; i < int(person_list.count); i++)
			{
				pk::person@ person_candidate = person_list[i];
				if (!pk::has_skill(person_candidate, int(pk::core["징병.특기"])))							continue;
				if (int(person_candidate.stat[int(pk::core["징병.능력"])]) < 징병특기_보유무장_징병능력)	continue;

				징병특기_보유무장_징병능력 = person_candidate.stat[int(pk::core["징병.능력"])];
				징병특기_보유무장_번호 = i;
				@징병특기_보유무장 = @person_candidate;
			}
			pk::list<pk::person@> actors;
			if (징병특기_보유무장 is null)
			{
				person_list.sort(function(a, b){return a.stat[int(pk::core["징병.능력"])] > b.stat[int(pk::core["징병.능력"])];});
				actors.add(person_list[0]);
				if (int(city.troops) + func_징병병력증감_계산(city, building, actors) < int(city.max_troops))
				{
					if (int(person_list.count) > 1)
					{
						actors.add(person_list[1]);

						if (int(city.troops) + func_징병병력증감_계산(city, building, actors) < int(city.max_troops))
						{
							if (int(person_list.count) > 2) actors.add(person_list[2]);
						}
					}
				}
			}
			else
			{
				person_list.remove_at(징병특기_보유무장_번호);
				person_list.sort(function(a, b){return a.stat[int(pk::core["징병.능력"])] > b.stat[int(pk::core["징병.능력"])];});
				actors.add(징병특기_보유무장);
				if (int(city.troops) + func_징병병력증감_계산(city, building, actors) < int(city.max_troops))
				{
					if (int(person_list.count) > 1)
					{
						actors.add(person_list[0]);

						if (int(city.troops) + func_징병병력증감_계산(city, building, actors) < int(city.max_troops))
						{
							if (int(person_list.count) > 2) actors.add(person_list[1]);
						}
					}
				}
			}
			int end = int(actors.count);
			array<string> person_name_list(0);
			for (int i = 0; i < end; i++)
			{
				@cmd.actors[i] = @actors[i];
				person_name_list.insertLast(pk::format("\x1b[1x{}\x1b[0x", pk::decode(pk::get_name(actors[i]))));
			}

			// 징병 명령 실행
			if (!내정자동화_행동력소모_적용) district.ap += 20;
			bool is_recruit_ended = pk::command(cmd);

			// 징병 실행 메시지
			if (is_recruit_ended)
			{
				string building_name = pk::format("\x1b[1x{}\x1b[0x에서 ", pk::decode(pk::get_name(building)));
				string person_names = join(person_name_list, ", ");
				string person_count_info = (end > 1) ? " 등": "";
				string action_info = pk::format(" {}명이\n징병을 실행", end);
				string action_message = building_name + person_names + person_count_info + action_info;

				if (내정자동화_메시지박스_표시)	pk::message_box(pk::encode(action_message));
				else							pk::history_log(building.pos, force.color, pk::encode(action_message));
			}
		}

		// '100 징병 병력 증감.cpp' 참고 (PK2.1 기본 제공 파일 기준)
		int func_징병병력증감_계산(pk::city@ city, pk::building@ building, pk::list<pk::person@> actors)
		{
			int n = 0, sum = 0, mul = 100;

			for (int i = 0; i < int(actors.count); i++)
			{
				sum += actors[i].stat[int(pk::core["징병.능력"])];
				if (pk::has_skill(actors[i], int(pk::core["징병.특기"]))) mul = 150;
			}

			n = int((1000 + (int(city.public_order) + 20) * sum * 5 / 100) * mul / 100 * func_5c4600(city));

			if (pk::get_scenario().difficulty == 난이도_특급 and !city.is_player()) n *= 2;

			if (pk::enemies_around(building)) n /= 2;

			return n;
		}

		float func_5c4600(pk::city@ city)
		{
			int level1 = 0, level2 = 0;

			for (int i = 0; i < city.max_devs; i++)
			{
				pk::building@ building = city.dev[i].building;
				if (pk::is_alive(building))
				{
					switch (building.facility)
					{
						case 시설_병영		: building.completed ? level1++	: 0;		break;
						case 시설_병영2단	: building.completed ? level2++	: level1++;	break;
						case 시설_병영3단	: building.completed ? 0		: level2++;	break;
					}
				}
			}

			if (int(city.barracks_counter) > level1 + level2)	return 1.5f;
			if (int(city.barracks_counter) > level1)			return 1.2f;
			return 1.f;
		}

		void func_내정자동화_포상(pk::force@ force, pk::city@ city)
		{
			pk::building@ building = pk::city_to_building(city);
			pk::district@ district = pk::get_district(building.get_district_id());

			// 설정 조건 확인
			if (!isEnabled(force.get_id(), city.get_id(), 내정자동화_포상)) return;	// 허용/금지 여부

			/// 포상 명령 정보
			pk::reward_cmd_info cmd;

			// 포상 실행 거점
			@cmd.base = @building;

			// 포상 무장
			int recover_ap = 0;
			uint mibun_flags = pk::mibun_flags(신분_도독, 신분_태수, 신분_일반);
			array<pk::person@> person_list = pk::list_to_array(pk::get_person_list(force, mibun_flags));
			for (int i = 0; i < int(person_list.length); i++)
			{
				pk::person@ person = person_list[i];

				// 기본 조건 확인
				if (내정자동화_행동력소모_적용 and int(district.ap) < (5 * (1 + int((cmd.actors).count))))	break;	// 행동력 조건
				if (city.gold < (100 * (1 + int((cmd.actors).count))))										break;	// 도시 금 확인

				// 설정 조건 확인
				if (int(person.loyalty) > 포상기준_충성도[city.get_id()]) continue;	// 충성도 기준

				if (!내정자동화_행동력소모_적용) recover_ap += 5;

				cmd.actors.add(person);
			}

			// 포상 명령 실행
			if (!내정자동화_행동력소모_적용) district.ap += recover_ap;
			bool is_reward_ended = pk::command(cmd);

			// 포상 실행 메시지
			if (is_reward_ended)
			{
				int reward_count = int((cmd.actors).count);
				string building_name = pk::decode(pk::get_name(building));
				string action_info = pk::format("\x1b[1x{}\x1b[0x에서 \x1b[1x{}\x1b[0x명에게 포상", building_name, reward_count);

				if (내정자동화_메시지박스_표시)	pk::message_box(pk::encode(action_info));
				else							pk::history_log(building.pos, force.color, pk::encode(action_info));
			}
		}

		void func_내정자동화_수송(pk::force@ force, pk::city@ city)
		{
			pk::building@ building = pk::city_to_building(city);
			pk::district@ district = pk::get_district(building.get_district_id());

			// 기본 조건 확인
			if (내정자동화_행동력소모_적용 and int(district.ap) < 10)	return;	// 행동력 조건
			if (pk::get_idle_person_list(building).count == 0)			return;	// 행동가능 무장 조건

			// 설정 조건 확인
			if (!isEnabled(force.get_id(), city.get_id(), 내정자동화_수송)) return;	// 허용/금지 여부

			// 수송 한계 도시 조건 (수송하는 도시)
			if (수송한계설정_경계도시까지)
			{
				if (func_근처_적도시수(city, 2) > 0) return;
			}
			else
			{
				if (func_근처_적도시수(city, 1) > 0) return;
			}

			// 인접 도시 확인
			for (int i = 0; i < 6; i++)
			{
				pk::city@ neighbor_city = pk::get_city(city.neighbor[i]);
				if (neighbor_city is null)							continue;	// 비어 있는 인접 도시 번호인 경우 제외
				if (!pk::is_alive(neighbor_city))					continue;
				if (neighbor_city.get_force_id() != force.get_id()) continue;	// 인접 도시가 해당 세력이 아닌 경우 제외

				pk::building@ neighbor_building = pk::city_to_building(neighbor_city);

				// 기본 조건 확인
				if (내정자동화_행동력소모_적용 and int(district.ap) < 10)	return;	// 행동력 조건
				if (pk::get_idle_person_list(building).count == 0)			return;	// 행동가능 무장 조건

				// 병력 조건 (수송하는 도시)
				if (city.troops < int(city.max_troops * 수송가능조건_병력조건)) return;

				// 병량 조건 (수송하는 도시)
				if (city.food < int(city.troops * 수송가능조건_병량조건)) return;

				// 수송 한계 도시 조건 (수송받는 도시)
				if (수송한계설정_경계도시까지)
				{
					if (func_근처_적도시수(neighbor_city, 1) > 0) continue;
				}

				// 플레이어 위임군단 도시 제외 (수송받는 도시)
				if (neighbor_building.is_player() and !pk::is_player_controlled(neighbor_building)) continue;

				// 병력 조건 (수송받는 도시)
				if (neighbor_city.troops > int(neighbor_city.max_troops * 수송필요조건_병력조건1)) continue;

				// 병력 조건 (수송하는 도시 vs 수송받는 도시)
				if (neighbor_city.troops > int(city.troops * 수송필요조건_병력조건2)) continue;

				// 근처 적 도시수 조건  (수송하는 도시 vs 수송받는 도시)
				if (!func_근처_적도시수_조건_충족여부(city, neighbor_city)) continue;

				if (!내정자동화_행동력소모_적용) district.ap += 10;

				func_수송부대출진(building, neighbor_building);
			}
		}

		void func_수송부대출진(pk::building@ building, pk::building@ neighbor_building)
		{
			/// 출진 명령 정보
			pk::com_deploy_cmd_info cmd;

			// 출진 거점
			@cmd.base = @building;

			// 출진 부대 종류
			cmd.type = 부대종류_수송;

			// 출진 부대 주장
            pk::list<pk::person@> person_list = pk::get_idle_person_list(building);
			person_list.sort(function(a, b){return a.stat[무장능력_정치] > b.stat[무장능력_정치];});
			cmd.member[0] = person_list[0].get_id();

			// 출진 부대 금
			int 수송량_금_최대치 = pk::min(pk::get_gold(building), pk::get_max_gold(neighbor_building) - pk::get_gold(neighbor_building));
			cmd.gold = (pk::get_gold(building) >= 10000) ? pk::min(수송량_금_최대치, (pk::get_gold(building) / 2)) : (pk::get_gold(building) / 4);

			// 출진 부대 병력
			int 수송량_병력_최대치 = pk::min(pk::get_troops(building), pk::get_max_troops(neighbor_building) - pk::get_troops(neighbor_building));
			수송량_병력_최대치 = pk::min(60000, 수송량_병력_최대치);
			int 수송량_병력 = pk::min(수송량_병력_최대치, int(pk::get_troops(building) * 수송병력비율));
			cmd.troops = 수송량_병력;

			// 출진 부대 병량
			float 병량계수 = (pk::get_food(building) >= int(pk::get_troops(building) * 2.0f)) ? 3.0f : 1.5f;
			int 수송량_병량_최대치 = pk::min(pk::get_food(building), pk::get_max_food(neighbor_building) - pk::get_food(neighbor_building));
			cmd.food = (pk::get_food(building) >= 100000) ? pk::max((pk::get_food(building) / 2), pk::min(수송량_병량_최대치, int(수송량_병력 * 병량계수))) : (pk::get_food(building) / 2);

            // 출진 부대 병기(수송량)
			// 참고 : 0검, 1창, 2극, 3노, 4군마, 5충차, 6정란, 7투석, 8목수, 9주가, 10누선, 11투함
			array<int> 수송량_병기(12, 0);
            for (int i = 0; i < 병기_끝; i++)
			{
				int 수송량_병기_최대치 = pk::get_max_weapon_amount(neighbor_building, i) - pk::get_weapon_amount(neighbor_building, i);
				수송량_병기[i] = pk::min(수송량_병기_최대치, pk::get_weapon_amount(building, i) / 2);
				cmd.weapon_id[i] = i;
				cmd.weapon_amount[i] = 수송량_병기[i];
			}

			// 출진 부대 임무
			cmd.order = 부대임무_이동;

			// 출진 부대 목표 좌표
			cmd.target_pos = neighbor_building.pos;

			// 출진 명령 실행
			int unit_id = pk::command(cmd);

			// 출진 실행 메시지
			if (unit_id != -1)
			{
				pk::unit@ unit = pk::get_unit(unit_id);
				string unit_name = pk::format("\x1b[1x{}\x1b[0x", pk::decode(pk::get_name(unit)));
				string building_name = pk::format("\x1b[1x{}\x1b[0x", pk::decode(pk::get_name(building)));
				string neighbor_building_name = pk::format("\x1b[1x{}\x1b[0x", pk::decode(pk::get_name(neighbor_building)));
				string action_message = pk::format("{}가 {}에 수송을 위해 {}에서 출진", unit_name, neighbor_building_name, building_name);
				pk::force@ force = pk::get_force(building.get_force_id());

				if (내정자동화_메시지박스_표시)	pk::message_box(pk::encode(action_message));
				else							pk::history_log(building.pos, force.color, pk::encode(action_message));

				// 출진 부대 행동 완료
				unit.action_done = true;
			}
		}

		bool func_근처_적도시수_조건_충족여부(pk::city@ city, pk::city@ neighbor_city)
		{
			if		(func_근처_적도시수(city, 1) < func_근처_적도시수(neighbor_city, 1)) return true;
			else if (func_근처_적도시수(city, 1) > func_근처_적도시수(neighbor_city, 1)) return false;
			else
			{
				if		(func_근처_적도시수(city, 2) < func_근처_적도시수(neighbor_city, 2)) return true;
				else if (func_근처_적도시수(city, 2) > func_근처_적도시수(neighbor_city, 2)) return false;
				else
				{
					if		(func_근처_적도시수(city, 3) < func_근처_적도시수(neighbor_city, 3)) return true;
					else if (func_근처_적도시수(city, 3) > func_근처_적도시수(neighbor_city, 3)) return false;
					else
					{
						if		(func_근처_적도시수(city, 4) < func_근처_적도시수(neighbor_city, 4)) return true;
						else if (func_근처_적도시수(city, 4) > func_근처_적도시수(neighbor_city, 4)) return false;
						else
						{
							if		(func_근처_적도시수(city, 5) < func_근처_적도시수(neighbor_city, 5)) return true;
							else if (func_근처_적도시수(city, 5) > func_근처_적도시수(neighbor_city, 5)) return false;
							else
							{
								if		(func_근처_적도시수(city, 6) < func_근처_적도시수(neighbor_city, 6)) return true;
								else if (func_근처_적도시수(city, 6) > func_근처_적도시수(neighbor_city, 6)) return false;
								else
								{
									if		(func_근처_적도시수(city, 7) < func_근처_적도시수(neighbor_city, 7)) return true;
									else if (func_근처_적도시수(city, 7) > func_근처_적도시수(neighbor_city, 7)) return false;
									else
									{
										if (func_근처_적도시수(city, 8) < func_근처_적도시수(neighbor_city, 8)) return true;
										else																	return false;
									}
								}
							}
						}
					}
				}
			}
		}

		int func_근처_적도시수(pk::city@ city, int 도시거리)
		{
			int enemy_city_count = 0;

			array<pk::city@> cities = pk::list_to_array(pk::get_city_list());
			for (int i = 0; i < int(cities.length); i++)
			{
				pk::city@ neighbor_city = cities[i];

				// 도시 간 무장의 이동 소요일수 기준
				int distance = pk::get_city_distance(city.get_id(), neighbor_city.get_id());

				if (distance > 도시거리)				continue;
				if (!pk::is_enemy(city, neighbor_city))	continue;

				enemy_city_count++;
			}

			return enemy_city_count;
		}

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		int menu_city_id_;	// 건물 메뉴 도시
		int menu_force_id_;	// 건물 메뉴 세력
		pk::building@ building_;

		void init(pk::building@ building)
		{
			@building_ = @building;
			pk::city@ city = pk::building_to_city(building);

			menu_city_id_ = (city !is null) ? city.get_id() : -1;
			menu_force_id_ = building.get_force_id();
		}

		bool isVisible()
		{
			if (building_.get_id() >= 도시_끝) return false;
			if (!pk::is_player_controlled(pk::get_city(menu_city_id_))) return false;	// 플레이어 위임군단 도시인 경우 제외

			return menu_city_id_ != -1 and menu_force_id_ == pk::get_current_turn_force_id();
		}

		string getText_일괄변경_순서()
		{
			return pk::encode("일괄 변경    ");
		}
		string getDesc_일괄변경_순서()
		{
			return pk::encode("전체 도시 중 선택한 도시의 내정 순서 모드를 일괄적으로 변경합니다.");
		}
		bool handler_일괄변경_순서()
		{
			func_일괄변경_순서(); return true;
		}
		void func_일괄변경_순서()
		{
			pk::district@ district = pk::get_district(pk::get_district_id(pk::get_force(menu_force_id_), 1));
			array<pk::building@> selected_cities_arr;
			pk::list<pk::city@> city_list = pk::get_city_list(district);
			string desc_순서 = pk::encode("내정 자동화 순서 모드를 변경할 도시를 선택하십시오.");
			selected_cities_arr = pk::list_to_array(pk::city_selector(pk::encode("도시 선택"), desc_순서, city_list, 1, int(city_list.count)));
			if (int(selected_cities_arr.length) == 0) return;
			array<string> str_order = {"모드 1 : 순찰 - 훈련 - 징병 - 포상 - 수송", "모드 2 : 순찰 - 징병 - 훈련 - 포상 - 수송", "모드 3 : 징병 - 순찰 - 훈련 - 포상 - 수송", "모드 4 : 징병 - 훈련 - 순찰 - 포상 - 수송", "모드 5 : 훈련 - 징병 - 순찰 - 포상 - 수송", "모드 6 : 훈련 - 순찰 - 징병 - 포상 - 수송"};
			pk::message_box(pk::encode(str_order[0] + "\n" + str_order[1] + "\n" + str_order[2] + "\n" + str_order[3] + "\n" + str_order[4] + "\n" + str_order[5]));
			pk::int_bool set_order = pk::numberpad(pk::encode("순서모드"), 1, 6, 1, pk::numberpad_t(numberpad_t));
			array<string> city_name_list(0);
			for (int i = 0; i < int(selected_cities_arr.length); i++)
			{
			//	pk::city@ city = pk::building_to_city(selected_cities_arr[i]);	// pk::building_to_city 함수 지원하지 않음
				pk::city@ city = pk::get_city(selected_cities_arr[i].get_id());
				city_name_list.insertLast(pk::format("\x1b[1x{}\x1b[0x", pk::decode(pk::get_name(city))));
				if (set_order.second) 내정자동화_순서정보[city.get_id()] = set_order.first;
			}
			string city_names = join(city_name_list, ", ");
			string city_count_info = (int(selected_cities_arr.length) > 1) ? " 등": "";
			pk::message_box(pk::encode(pk::format("{}{} {}개 도시의 내정 자동화 순서 모드를 변경\n{}", city_names, city_count_info, int(selected_cities_arr.length), str_order[int(set_order.first) - 1])));
		}

		string getText_순서()
		{
			switch(내정자동화_순서정보[menu_city_id_])
			{
				case 1	: return pk::encode("순서 모드 : 1");
				case 2	: return pk::encode("순서 모드 : 2");
				case 3	: return pk::encode("순서 모드 : 3");
				case 4	: return pk::encode("순서 모드 : 4");
				case 5	: return pk::encode("순서 모드 : 5");
				case 6	: return pk::encode("순서 모드 : 6");
			}

			return pk::encode("");
		}

		string getDesc_순서()
		{
			switch(내정자동화_순서정보[menu_city_id_])
			{
				case 1	: return pk::encode("순서 : 순찰 - 훈련 - 징병 - 포상 - 수송");
				case 2	: return pk::encode("순서 : 순찰 - 징병 - 훈련 - 포상 - 수송");
				case 3	: return pk::encode("순서 : 징병 - 순찰 - 훈련 - 포상 - 수송");
				case 4	: return pk::encode("순서 : 징병 - 훈련 - 순찰 - 포상 - 수송");
				case 5	: return pk::encode("순서 : 훈련 - 징병 - 순찰 - 포상 - 수송");
				case 6	: return pk::encode("순서 : 훈련 - 순찰 - 징병 - 포상 - 수송");
			}

			return pk::encode("");
		}

		bool handler_순서()
		{
			if		(내정자동화_순서정보[menu_city_id_] == 1)	내정자동화_순서정보[menu_city_id_] = 2;
			else if (내정자동화_순서정보[menu_city_id_] == 2)	내정자동화_순서정보[menu_city_id_] = 3;
			else if (내정자동화_순서정보[menu_city_id_] == 3)	내정자동화_순서정보[menu_city_id_] = 4;
			else if (내정자동화_순서정보[menu_city_id_] == 4)	내정자동화_순서정보[menu_city_id_] = 5;
			else if (내정자동화_순서정보[menu_city_id_] == 5)	내정자동화_순서정보[menu_city_id_] = 6;
			else if (내정자동화_순서정보[menu_city_id_] == 6)	내정자동화_순서정보[menu_city_id_] = 1;
			else												내정자동화_순서정보[menu_city_id_] = 1;

			if (menu_force_id_ == pk::get_current_turn_force_id())
			{
				string city_name = pk::decode(pk::get_name(pk::city_to_building(pk::get_city(menu_city_id_))));
				string toggle_msg = pk::encode(pk::format("\x1b[1x{}\x1b[0x에서 내정 자동화 순서 변경(모드 \x1b[1x{}\x1b[0x)\n", city_name, 내정자동화_순서정보[menu_city_id_]));
				string order_info = getDesc_순서();
				pk::message_box(toggle_msg + order_info);
			}

			return true;
		}

		//MUSSO
		string getText_일괄변경_허용여부_간소화()
		{
			return pk::encode("전체 일괄변경");
		}

		string getText_일괄변경_허용여부()
		{
			return pk::encode("개별 일괄변경");
		}
		string getDesc_일괄변경_허용여부_간소화()
		{
			return pk::encode("선택한 세력도시에서 순찰, 훈련, 포상의 자동내정 사용 여부를 결정합니다.");
		}		
		string getDesc_일괄변경_허용여부()
		{
			return pk::encode("선택한 세력도시에서 항목별 자동내정 사용 여부를 결정합니다.");
		}
		
		//MUSSO
		bool handler_일괄변경_허용여부_간소화()
		{
			func_일괄변경_허용여부_간소화(); return true;
		}
		void func_일괄변경_허용여부_간소화()
		{
			pk::district@ district = pk::get_district(pk::get_district_id(pk::get_force(menu_force_id_), 1));
			array<pk::building@> selected_cities_arr;
			pk::list<pk::city@> city_list = pk::get_city_list(district);
			// array<string> answers_항목_arr = {pk::encode("순찰"), pk::encode("훈련"), pk::encode("징병"), pk::encode("포상"), pk::encode("수송"), pk::encode("취소")};
			array<string> answers_허용금지_arr = {pk::encode("일괄 허용"), pk::encode("일괄 금지"), pk::encode("뒤로")};
			array<string> desc_허용금지_arr = {"허용", "금지"};
			string desc_허용금지 = "";
			// int n = pk::choose(pk::encode("일괄적으로 변경할 항목을 선택하십시오."), answers_항목_arr);
			for (int i = 0; i < 5; i++)
			{
				// if (n != i) continue;

				int m = pk::choose(pk::encode("선택한 도시의 순찰, 훈련, 포상의 자동내정을 허용/금지합니다."), answers_허용금지_arr);
				for (int j = 0; j < 2; j++)
				{
					if (m != j) continue;

					// desc_허용금지 = pk::format("{}을 {}할 도시를 선택하십시오.", pk::decode(answers_항목_arr[n]), desc_허용금지_arr[m]);
					selected_cities_arr = pk::list_to_array(pk::city_selector(pk::encode("도시 선택"), pk::encode(desc_허용금지), city_list, 1, int(city_list.count)));
					if (int(selected_cities_arr.length) == 0) return;
					array<string> city_name_list(0);
					for (int k = 0; k < int(selected_cities_arr.length); k++)
					{
						// pk::city@ city = pk::building_to_city(selected_cities_arr[k]);	// pk::building_to_city 함수 지원하지 않음
						pk::city@ city = pk::get_city(selected_cities_arr[k].get_id());
						city_name_list.insertLast(pk::format("\x1b[1x{}\x1b[0x", pk::decode(pk::get_name(city))));
						bool 허용금지여부 = (m == 0) ? true : false;
						set(menu_force_id_, city.get_id(), 허용금지여부, 0);	//순찰
						set(menu_force_id_, city.get_id(), 허용금지여부, 1);	//훈련
						// set(menu_force_id_, city.get_id(), 허용금지여부, 2);	//징병
						set(menu_force_id_, city.get_id(), 허용금지여부, 3);	//포상
					}
					string city_names = join(city_name_list, ", ");
					string city_count_info = (int(selected_cities_arr.length) > 1) ? " 등": "";
					pk::message_box(pk::encode(pk::format("{}{} {}개 도시의 내정을 \x1b[1x{}\x1b[0x", city_names, city_count_info, int(selected_cities_arr.length), desc_허용금지_arr[m])));
					return;
					
				}
				if (m == 2) return;
			}
			// if (n == 5) return;
			
		}
		
		
		
		bool handler_일괄변경_허용여부()
		{
			func_일괄변경_허용여부(); return true;
		}
		void func_일괄변경_허용여부()
		{
			pk::district@ district = pk::get_district(pk::get_district_id(pk::get_force(menu_force_id_), 1));
			array<pk::building@> selected_cities_arr;
			pk::list<pk::city@> city_list = pk::get_city_list(district);
			array<string> answers_항목_arr = {pk::encode("순찰"), pk::encode("훈련"), pk::encode("징병"), pk::encode("포상"), pk::encode("수송"), pk::encode("취소")};
			array<string> answers_허용금지_arr = {pk::encode("일괄 허용"), pk::encode("일괄 금지"), pk::encode("뒤로")};
			array<string> desc_허용금지_arr = {"허용", "금지"};
			string desc_허용금지 = "";
			int n = pk::choose(pk::encode("일괄적으로 변경할 항목을 선택하십시오."), answers_항목_arr);
			for (int i = 0; i < 5; i++)
			{
				if (n != i) continue;

				int m = pk::choose(pk::encode("허용/금지 여부를 선택하십시오."), answers_허용금지_arr);
				for (int j = 0; j < 2; j++)
				{
					if (m != j) continue;

					desc_허용금지 = pk::format("{}을 {}할 도시를 선택하십시오.", pk::decode(answers_항목_arr[n]), desc_허용금지_arr[m]);
					selected_cities_arr = pk::list_to_array(pk::city_selector(pk::encode("도시 선택"), pk::encode(desc_허용금지), city_list, 1, int(city_list.count)));
					if (int(selected_cities_arr.length) == 0) return;
					array<string> city_name_list(0);
					for (int k = 0; k < int(selected_cities_arr.length); k++)
					{
					//	pk::city@ city = pk::building_to_city(selected_cities_arr[k]);	// pk::building_to_city 함수 지원하지 않음
						pk::city@ city = pk::get_city(selected_cities_arr[k].get_id());
						city_name_list.insertLast(pk::format("\x1b[1x{}\x1b[0x", pk::decode(pk::get_name(city))));
						bool 허용금지여부 = (m == 0) ? true : false;
						set(menu_force_id_, city.get_id(), 허용금지여부, n);	// true : 금지 -> 허용, false : 허용 -> 금지
					}
					string city_names = join(city_name_list, ", ");
					string city_count_info = (int(selected_cities_arr.length) > 1) ? " 등": "";
					pk::message_box(pk::encode(pk::format("{}{} {}개 도시의 \x1b[1x{}\x1b[0x을 \x1b[1x{}\x1b[0x", city_names, city_count_info, int(selected_cities_arr.length), pk::decode(answers_항목_arr[n]), desc_허용금지_arr[m])));
				}
				if (m == 2)	func_일괄변경_허용여부();
			}
			if (n == 5) return;
		}

		string getText_순찰()
		{
			return isEnabled(menu_force_id_, menu_city_id_, 내정자동화_순찰) ? pk::encode("순찰 허용") : pk::encode("순찰 금지");
		}
		string getDesc_순찰()
		{
			return isEnabled(menu_force_id_, menu_city_id_, 내정자동화_순찰) ? pk::encode("순찰이 허용된 도시입니다.") : pk::encode("순찰이 금지된 도시입니다.");
		}
		bool handler_순찰()
		{
			toggle(menu_force_id_, menu_city_id_, 내정자동화_순찰);	return true;
		}

		string getText_훈련()
		{
			return isEnabled(menu_force_id_, menu_city_id_, 내정자동화_훈련) ? pk::encode("훈련 허용") : pk::encode("훈련 금지");
		}
		string getDesc_훈련()
		{
			return isEnabled(menu_force_id_, menu_city_id_, 내정자동화_훈련) ? pk::encode("훈련이 허용된 도시입니다.") : pk::encode("훈련이 금지된 도시입니다.");
		}
		bool handler_훈련()
		{
			toggle(menu_force_id_, menu_city_id_, 내정자동화_훈련);	return true;
		}

		string getText_징병()
		{
			return isEnabled(menu_force_id_, menu_city_id_, 내정자동화_징병) ? pk::encode("징병 허용") : pk::encode("징병 금지");
		}
		string getDesc_징병()
		{
			return isEnabled(menu_force_id_, menu_city_id_, 내정자동화_징병) ? pk::encode("징병이 허용된 도시입니다.") : pk::encode("징병이 금지된 도시입니다.");
		}
		bool handler_징병()
		{
			toggle(menu_force_id_, menu_city_id_, 내정자동화_징병);	return true;
		}

		string getText_포상()
		{
			return isEnabled(menu_force_id_, menu_city_id_, 내정자동화_포상) ? pk::encode("포상 허용") : pk::encode("포상 금지");
		}
		string getDesc_포상()
		{
			return isEnabled(menu_force_id_, menu_city_id_, 내정자동화_포상) ? pk::encode("포상이 허용된 도시입니다.") : pk::encode("포상이 금지된 도시입니다.");
		}
		bool handler_포상()
		{
			toggle(menu_force_id_, menu_city_id_, 내정자동화_포상);	return true;
		}

		string getText_수송()
		{
			return isEnabled(menu_force_id_, menu_city_id_, 내정자동화_수송) ? pk::encode("수송 허용") : pk::encode("수송 금지");
		}
		string getDesc_수송()
		{
			return isEnabled(menu_force_id_, menu_city_id_, 내정자동화_수송) ? pk::encode("수송이 허용된 도시입니다.") : pk::encode("수송이 금지된 도시입니다.");
		}
		bool handler_수송()
		{
			toggle(menu_force_id_, menu_city_id_, 내정자동화_수송);	return true;
		}

		string getText_일괄변경_기준()
		{
			return pk::encode("일괄 변경        ");
		}
		string getDesc_일괄변경_기준()
		{
			return pk::encode("전체 도시 중 선택한 도시의 내정 실행기준을 일괄적으로 변경합니다.");
		}
		bool handler_일괄변경_기준()
		{
			func_일괄변경_기준(); return true;
		}
		void func_일괄변경_기준()
		{
			pk::district@ district = pk::get_district(pk::get_district_id(pk::get_force(menu_force_id_), 1));
			array<pk::building@> selected_cities_arr;
			pk::list<pk::city@> city_list = pk::get_city_list(district);
			array<string> answers_항목_arr = {pk::encode("순찰기준 치안"), pk::encode("훈련기준 기력비율"), pk::encode("징병기준 치안"), pk::encode("징병기준 금"), pk::encode("징병기준 병량비율"), pk::encode("포상기준 충성도")};
			string desc_기준 = "";
			int n = pk::choose(pk::encode("일괄적으로 변경할 항목을 선택하십시오."), answers_항목_arr);	// @items 선택지 최대 6개
			for (int i = 0; i < 6; i++)
			{
				if (n != i) continue;

				desc_기준 = pk::format("기준을 변경할 도시를 선택하십시오. ({})", pk::decode(answers_항목_arr[n]));
				selected_cities_arr = pk::list_to_array(pk::city_selector(pk::encode("도시 선택"), pk::encode(desc_기준), city_list, 1, int(city_list.count)));
				if (int(selected_cities_arr.length) == 0) return;

				array<int> max_num = {99, 99, 100, 100000, 1000, 99};
				array<int> def_num = {90, 95, 95, 2000, 150, 90};
				pk::int_bool set_standard = pk::numberpad(pk::encode("내정기준"), 0, max_num[n], def_num[n], pk::numberpad_t(numberpad_t));
				if (set_standard.second)
				{
					array<string> city_name_list(0);
					for (int k = 0; k < int(selected_cities_arr.length); k++)
					{
					//	pk::city@ city = pk::building_to_city(selected_cities_arr[k]);	// pk::building_to_city 함수 지원하지 않음
						pk::city@ city = pk::get_city(selected_cities_arr[k].get_id());
						city_name_list.insertLast(pk::format("\x1b[1x{}\x1b[0x", pk::decode(pk::get_name(city))));

						if		(n == 0) 순찰기준_치안[city.get_id()] = set_standard.first;
						else if (n == 1) 훈련기준_기력비율[city.get_id()] = set_standard.first;
						else if (n == 2) 징병기준_치안[city.get_id()] = set_standard.first;
						else if (n == 3) 징병기준_금[city.get_id()] = set_standard.first;
						else if (n == 4) 징병기준_병량비율[city.get_id()] = set_standard.first;
						else if (n == 5) 포상기준_충성도[city.get_id()] = set_standard.first;
					}
					string city_names = join(city_name_list, ", ");
					string city_count_info_1 = (int(selected_cities_arr.length) > 1) ? " 등": "";
					string city_count_info_2 = (int(selected_cities_arr.length) > 1) ? "일괄 ": "";
					pk::message_box(pk::encode(pk::format("{}{} {}개 도시의 \x1b[1x{}\x1b[0x {}변경 (\x1b[1x{}\x1b[0x)", city_names, city_count_info_1, int(selected_cities_arr.length), pk::decode(answers_항목_arr[n]), city_count_info_2, set_standard.first)));
				}
			}
		}

		string getText_순찰기준_치안()
		{
			return pk::encode("순찰기준 치안    ");
		}
		string getDesc_순찰기준_치안()
		{
			return pk::encode(pk::format("도시의 치안이 {} 이하인 경우 순찰합니다.", 순찰기준_치안[menu_city_id_]));
		}
		bool handler_순찰기준_치안()
		{
			// 순찰기준 치안 설정
			pk::int_bool set_public_order = pk::numberpad(pk::encode("내정기준"), 0, 99, 순찰기준_치안[menu_city_id_], pk::numberpad_t(numberpad_t));

			if (set_public_order.second) 순찰기준_치안[menu_city_id_] = set_public_order.first;

			return true;
		}

		string getText_훈련기준_기력비율()
		{
			return pk::encode("훈련기준 기력비율");
		}
		string getDesc_훈련기준_기력비율()
		{
			return pk::encode(pk::format("도시의 최대 기력 대비 현재 기력이 {}% 이하인 경우 순찰합니다.", 훈련기준_기력비율[menu_city_id_]));
		}
		bool handler_훈련기준_기력비율()
		{
			// 훈련기준 기력비율 설정
			pk::int_bool set_drills = pk::numberpad(pk::encode("내정기준"), 0, 99, 훈련기준_기력비율[menu_city_id_], pk::numberpad_t(numberpad_t));

			if (set_drills.second) 훈련기준_기력비율[menu_city_id_] = set_drills.first;

			return true;
		}

		string getText_징병기준_치안()
		{
			return pk::encode("징병기준 치안    ");
		}
		string getDesc_징병기준_치안()
		{
			return pk::encode(pk::format("도시의 치안이 {} 이상인 경우 징병합니다.", 징병기준_치안[menu_city_id_]));
		}
		bool handler_징병기준_치안()
		{
			// 징병기준 치안 설정
			pk::int_bool set_recruit_order = pk::numberpad(pk::encode("내정기준"), 0, 100, 징병기준_치안[menu_city_id_], pk::numberpad_t(numberpad_t));

			if (set_recruit_order.second) 징병기준_치안[menu_city_id_] = set_recruit_order.first;

			return true;
		}

		string getText_징병기준_금()
		{
			return pk::encode("징병기준 금      ");
		}
		string getDesc_징병기준_금()
		{
			return pk::encode(pk::format("도시의 금이 {} 이상인 경우 징병합니다.", 징병기준_금[menu_city_id_]));
		}
		bool handler_징병기준_금()
		{
			// 징병기준 금 설정
			pk::int_bool set_recruit_gold = pk::numberpad(pk::encode("내정기준"), 0, 100000, 징병기준_금[menu_city_id_], pk::numberpad_t(numberpad_t));

			if (set_recruit_gold.second) 징병기준_금[menu_city_id_] = set_recruit_gold.first;

			return true;
		}

		string getText_징병기준_병량비율()
		{
			return pk::encode("징병기준 병량비율");
		}
		string getDesc_징병기준_병량비율()
		{
			return pk::encode(pk::format("도시의 현재 병력 대비 현재 병량 비율이 {}% 이상인 경우 징병합니다.", 징병기준_병량비율[menu_city_id_]));
		}
		bool handler_징병기준_병량비율()
		{
			// 징병기준 병량비율 설정
			pk::int_bool set_recruit_food = pk::numberpad(pk::encode("내정기준"), 0, 1000, 징병기준_병량비율[menu_city_id_], pk::numberpad_t(numberpad_t));

			if (set_recruit_food.second) 징병기준_병량비율[menu_city_id_] = set_recruit_food.first;

			return true;
		}

		string getText_포상기준_충성도()
		{
			return pk::encode("포상기준 충성도  ");
		}
		string getDesc_포상기준_충성도()
		{
			return pk::encode(pk::format("무장의 충성도가 {} 이하인 경우 포상합니다.", 포상기준_충성도[menu_city_id_]));
		}
		bool handler_포상기준_충성도()
		{
			// 포상기준 충성도 설정
			pk::int_bool set_loyaty = pk::numberpad(pk::encode("내정기준"), 0, 99, 포상기준_충성도[menu_city_id_], pk::numberpad_t(numberpad_t));

			if (set_loyaty.second) 포상기준_충성도[menu_city_id_] = set_loyaty.first;

			return true;
		}

		string numberpad_t(int line, int original_value, int current_value)
		{
			return pk::encode("");
		}

		bool isEnabled(int force_id, int city_id, int 내정자동화_항목)
		{
			if		(내정자동화_항목 == 내정자동화_순찰) return (순찰_허용여부[force_id] & (uint64(1) << city_id)) != 0;
			else if (내정자동화_항목 == 내정자동화_훈련) return (훈련_허용여부[force_id] & (uint64(1) << city_id)) != 0;
			else if (내정자동화_항목 == 내정자동화_징병) return (징병_허용여부[force_id] & (uint64(1) << city_id)) != 0;
			else if (내정자동화_항목 == 내정자동화_포상) return (포상_허용여부[force_id] & (uint64(1) << city_id)) != 0;
			else if (내정자동화_항목 == 내정자동화_수송) return (수송_허용여부[force_id] & (uint64(1) << city_id)) != 0;

			return false;
		}

		void toggle(int force_id, int city_id, int 내정자동화_항목)
		{
			bool 허용여부 = false;
			string 항목이름 = "";
			array<string> 항목이름_목록 = {"\x1b[1x순찰\x1b[0x", "\x1b[1x훈련\x1b[0x", "\x1b[1x징병\x1b[0x", "\x1b[1x포상\x1b[0x", "\x1b[1x수송\x1b[0x"};
			for (int i = 0; i < 5; i++)
			{
				if (내정자동화_항목 == i)
				{
					허용여부 = isEnabled(force_id, city_id, i);
					항목이름 = 항목이름_목록[i];
				}
			}
			string str_허용여부 = (!허용여부) ? "\x1b[1x허용\x1b[0x" : "\x1b[1x금지\x1b[0x";	// bool값이 바뀔 예정이므로 반대로 적용

			if (허용여부)	set(force_id, city_id, false, 내정자동화_항목);	// value = false : 허용 -> 금지
			else			set(force_id, city_id, true, 내정자동화_항목);	// value = true : 금지 -> 허용

			if (force_id == pk::get_current_turn_force_id())
			{
				string city_name = pk::decode(pk::get_name(pk::city_to_building(pk::get_city(city_id))));
				string toggle_msg = pk::format("\x1b[1x{}\x1b[0x에서 {} 내정 자동화를 {}", city_name, 항목이름, str_허용여부);
				pk::message_box(pk::encode(toggle_msg));
			}
		}

		void set(int force_id, int city_id, bool value, int 내정자동화_항목)
		{
			if (value)
			{
				// value = true : 금지 -> 허용
				if		(내정자동화_항목 == 내정자동화_순찰) 순찰_허용여부[force_id] = 순찰_허용여부[force_id] | uint64(1) << city_id;
				else if (내정자동화_항목 == 내정자동화_훈련) 훈련_허용여부[force_id] = 훈련_허용여부[force_id] | uint64(1) << city_id;
				else if (내정자동화_항목 == 내정자동화_징병) 징병_허용여부[force_id] = 징병_허용여부[force_id] | uint64(1) << city_id;
				else if (내정자동화_항목 == 내정자동화_포상) 포상_허용여부[force_id] = 포상_허용여부[force_id] | uint64(1) << city_id;
				else if (내정자동화_항목 == 내정자동화_수송) 수송_허용여부[force_id] = 수송_허용여부[force_id] | uint64(1) << city_id;
			}
			else
			{
				// value = false : 허용 -> 금지
				if		(내정자동화_항목 == 내정자동화_순찰) 순찰_허용여부[force_id] = 순찰_허용여부[force_id] & ~(uint64(1) << city_id);
				else if (내정자동화_항목 == 내정자동화_훈련) 훈련_허용여부[force_id] = 훈련_허용여부[force_id] & ~(uint64(1) << city_id);
				else if (내정자동화_항목 == 내정자동화_징병) 징병_허용여부[force_id] = 징병_허용여부[force_id] & ~(uint64(1) << city_id);
				else if (내정자동화_항목 == 내정자동화_포상) 포상_허용여부[force_id] = 포상_허용여부[force_id] & ~(uint64(1) << city_id);
				else if (내정자동화_항목 == 내정자동화_수송) 수송_허용여부[force_id] = 수송_허용여부[force_id] & ~(uint64(1) << city_id);
			}
		}

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	}

	Main main;
}