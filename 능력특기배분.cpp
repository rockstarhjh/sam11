namespace 능력특기배분
{
// AI의 능력연구 활용 안할 시 true -> false로 변경
bool 특기분배활용 = true;
bool 능력연구활용 = true;

bool 기초능력육성제한 = false; // 능력치가 20 이상 상승한 경우 육성을 금지합니다

bool 특기_로그_화면_표시 = true; // 화면 작은 창에 특기 분배 로그를 표시합니다.
bool 능력연구_로그_화면_표시 = true; // 화면 작은 창에 능력연구 분배 로그를 표시합니다.

int 회차당_최대특기분배 = 1;  // ai가 한 회차에 분배할 수 있는 최대 특기 숫자입니다.
int 회차당_최대능력분배 = 1;  // ai가 한 회차에 분배할 수 있는 최대 능력 숫자입니다.

int 특기분배_텀 = 3;		// ai의 특기분배 주기(개월)를 설정합니다. 해당값은 0보다 커야 합니다.
int 능력분배_텀 = 3;		// ai의 능력분배 주기(개월)를 설정합니다. 해당값은 0보다 커야 합니다.

int 능력연구_고_능력치_상한선 = 95;		// 능력연구(고)의 상승치 상한선. 기본은 95
int 능력연구_고_부여횟수 = 3;				// 능력연구(고)의 부여횟수. 기본은 3
int 능력연구_중_부여횟수 = 5;				// 능력연구(중)의 부여횟수. 기본은 5
int 능력연구_저_부여횟수 = 5;				// 능력연구(저)의 부여횟수. 기본은 5
/* 로직 확인
1. 월 시작시마다 적용
2. 0~47 까지의 능력연구 중 활성화 된 것을 확인
2-1. 횟수 제한이 무제한인 특기는 따로 배제
3. 활성화 및 특기 값이 있고 횟수가 남았으면 조건에 맞는 무장을 탐색
4. 행동중이지 않는 무장, 특기별 조건을 만족하면 해당 장수의 특기를 변경하고 횟수 차감
5. 0~10 까지의 숨겨진 능력연구 중 활성화 된 것을 확인
6. 숨겨진 능력연구의 능력번호(48~97)를 확인해 해당 능력의 제한횟수를 확인하고 횟수가 남았으면 조건맞는 무장 탐색
7. 4번과 비슷하게 특기 변경하고 횟수 차감
8. 2-1때 빼놨던 횟수 제한이 무제한인 특기를 조건에 맞게 부여
*/

int 점수_난수 = 200;
int 최소점수 = -100000;
int 무제한특기수 = 0;

/*특기가치*/
/*
무장들이 기본적으로 가진 특기와 능력연구에서 나온 특기의 가치를 비교하기 위한 값입니다
기본적으로 0~10 까지 작동하도록 구상했으므로 11 이상의 값을 사용하시려면 스크립트를 그에 맞게 수정하셔야 합니다

디폴트값을 쓴다면 0은 무특기와 같은 취급을 받으며 9~10은 어떤 특기가 연구에서 나오더라도 교체하지 않습니다

해당 장수가 갖고 있는 특기의 가치보다 능력연구로 나온 특기의 가치가 2 이상 더 높을 때 교환이 가능해집니다
가령 비장의 가치가 5이고 현재 장수가 가진 특기의 가치가 4나 8이면 비장을 부여해주지 않지만
3 이하면 비장을 부여해줄 수 있는 장수 목록에 추가됩니다

특기에 따른 자세한 조건에 대해서는 아래 특기조건 부분을 참조 바랍니다

다만 유저 패치를 적용시킬 경우 백출, 포박 같은건 너프를 먹고 안력, 철벽, 금강 같은 특기는 상향을 받는 경향이 있으며
친월 친만같은 무쓸모 특기는 아예 다른 특기로 변경되는 경우도 있는데 이 경우 특기가치를 직접 조정하셔야 합니다
이름이 바뀐 특기라고 해서 번호가 바뀌지는 않으니 친월, 친만같은 이름은 그대로 둔 채 가치만 변경하셔야 합니다
다중특기의 경우 고려하지 않고 있으니 사용에 주의 바랍니다
*/

array<array<int>> 특기가치 =
{
	{ 특기_비장, 10 },
	{ 특기_도주, 7 },
	{ 특기_강행, 6 },
	{ 특기_행군, 4 },
	{ 특기_추진, 3 },
	{ 특기_조타, 3 },
	{ 특기_답파, 5 },
	{ 특기_운반, 2 },
	{ 특기_해독, 2 },
	{ 특기_소탕, 3 },
	{ 특기_위풍, 7 },
	{ 특기_앙양, 3 },
	{ 특기_연전, 6 },
	{ 특기_급습, 5 },
	{ 특기_강습, 3 },
	{ 특기_난전, 6 },
	{ 특기_매복, 3 },
	{ 특기_공성, 6 },
	{ 특기_기각, 5 },
	{ 특기_포박, 10 },
	{ 특기_정묘, 2 },
	{ 특기_강탈, 2 },
	{ 특기_심공, 6 },
	{ 특기_구축, 6 },
	{ 특기_사정, 6 },
	{ 특기_백마, 6 },
	{ 특기_보좌, 5 },
	{ 특기_불굴, 5 },
	{ 특기_금강, 4 },
	{ 특기_철벽, 3 },
	{ 특기_노발, 3 },
	{ 특기_등갑, 6 },
	{ 특기_강운, 6 },
	{ 특기_혈로, 5 },
	{ 특기_창장, 7 },
	{ 특기_극장, 7 },
	{ 특기_궁장, 7 },
	{ 특기_기장, 7 },
	{ 특기_수장, 5 },
	{ 특기_용장, 10 },
	{ 특기_신장, 10 },
	{ 특기_투신, 10 },
	{ 특기_창신, 9 },
	{ 특기_극신, 9 },
	{ 특기_궁신, 9 },
	{ 특기_기신, 9 },
	{ 특기_공신, 7 },
	{ 특기_수신, 7 },
	{ 특기_패왕, 10 },
	{ 특기_질주, 8 },
	{ 특기_사수, 5 },
	{ 특기_맹장, 8 },
	{ 특기_호위, 6 },
	{ 특기_화공, 3 },
	{ 특기_언독, 7 },
	{ 특기_기략, 7 },
	{ 특기_궤계, 6 },
	{ 특기_허실, 9 },
	{ 특기_묘계, 7 },
	{ 특기_비책, 5 },
	{ 특기_간파, 3 },
	{ 특기_통찰, 8 },
	{ 특기_화신, 10 },
	{ 특기_신산, 10 },
	{ 특기_백출, 10 },
	{ 특기_귀모, 9 },
	{ 특기_연환, 9 },
	{ 특기_심모, 8 },
	{ 특기_반계, 3 },
	{ 특기_경국, 8 },
	{ 특기_요술, 6 },
	{ 특기_귀문, 10 },
	{ 특기_규율, 5 },
	{ 특기_침착, 5 },
	{ 특기_명경, 7 },
	{ 특기_주악, 8 },
	{ 특기_시상, 4 },
	{ 특기_축성, 4 },
	{ 특기_둔전, 4 },
	{ 특기_명성, 6 },
	{ 특기_능리, 6 },
	{ 특기_번식, 6 },
	{ 특기_발명, 4 },
	{ 특기_조선, 4 },
	{ 특기_지도, 4 },
	{ 특기_안력, 2 },
	{ 특기_논객, 8 },
	{ 특기_부호, 7 },
	{ 특기_미도, 7 },
	{ 특기_징세, 7 },
	{ 특기_징수, 7 },
	{ 특기_친오, 1 },
	{ 특기_친강, 1 },
	{ 특기_친월, 1 },
	{ 특기_친만, 1 },
	{ 특기_위압, 2 },
	{ 특기_인정, 6 },
	{ 특기_풍수, 2 },
	{ 특기_기원, 2 },
	{ 특기_내조, 4 }
};

/*특기조건*/
/*
각 특기별로 설정된 부여 조건입니다
해당 특기는 장수가 기존에 가진 특기가 아닌 능력연구시 부여될 특기 기준입니다

각 조건마다 설정된 가중치에 따라 무장별로 점수가 계산되고
그 중 가장 높은 점수를 가진 무장에게 특기가 배분됩니다

드문 경우이지만 두 무장의 점수가 완전히 같을 경우 먼저 선정된 무장에게 특기가 우선 배분됩니다

미리 설정된 조건들은 능력치 최대치가 100일 때를 가정하고 만든 것이라 능력치 최대치가 100이 아니라면 원치 않게 작동할 수 있습니다

	===== 각 조건별 설명 ====
	
	최소 통솔/무력/지력/정치/매력 : 해당 능력치 이상에서만 특기를 부여합니다
	
	가중치 : 해당 능력치 * 가중치 값으로 점수를 계산합니다
	ex) 무력가중치 10에 나머지 가중치가 0이고 해당 장수의 무력이 70이면 추가되는 점수는 700점
	
	최소보유적성 : 수군과 병기를 제외하고 최소 해당 적성을 보유하고 있어야 합니다. 0일 경우 자동으로 최소적성은 C가 됩니다
	
	최소 창병/극병/노병/기병/병기/수군적성 : 동일하지만 최소보유적성과 별개로 해당 병과의 해당 적성을 가지고 있어야 합니다.
	
	적성가중치 : 수군과 병기를 제외한 모든 적성에 대한 가중치입니다 연산은 능력치와 마찬가지로 곱한 다음 더하는 방식입니다
	(C = 0, B = 1, A = 2, S = 3)
	ex) 적성가중치 20에 기병, 창병이 S고 나머지 적성이 C인 무장에 추가되는 점수는 120점
	
	S적성병과 : 아래 S적성 추가점수를 부여하기 위한 조건입니다. 10으로 하면 수군, 병기를 제외한 모든 병과 중 하나만 S여도 추가점수가 적용됩니다
	S적성 추가점수 : 적성 S를 보유하고 있을 때의 추가점수입니다
	
	특기가치 가중치 : 해당 장수가 보유하고 있는 특기가 부여될 특기보다 가치가 낮으면 그 차이만큼 가중치를 곱하고 더합니다
	무특기는 특기가치가 0으로 취급됩니다
	ex) 특기가중치가 50이고 무특기 장수에 특기가치 10인 특기를 부여할 때의 점수는 500점
*/

array<array<int>> 특기조건 = 
{
	/*
	                                   범례

	특기 이름, 최소 통솔, 최소 무력, 최소 지력, 최소 정치, 최소 매력, 통솔가중치, 무력가중치, 지력가중치, 정치가중치, 매력가중치,
	최소보유적성, 최소병과, 최소병과적성, 적성가중치, S적성병과, S적성 추가점수, 특기가치 가중치,
	*/

	{ 특기_비장, 70, 75, 0, 0, 0, 10, 15, 0, 0, 0,
		적성_A, 0, 0, 20, 10, 150, 50 },
	{ 특기_도주, 70, 70, 0, 0, 0, 10, 10, 0, 0, 0,
		적성_A, 0, 0, 10, 0, 0, 50 },
	{ 특기_강행, 50, 50, 0, 0, 0, 5, 5, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_행군, 50, 50, 0, 0, 0, 5, 5, 0, 0, 0,
		0, 병종_기병, 적성_A, 0, 0, 0, 50 },
	{ 특기_추진, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_조타, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_답파, 50, 50, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_운반, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_해독, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_소탕, 50, 50, 0, 0, 0, 5, 5, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_위풍, 70, 70, 0, 0, 0, 10, 10, 0, 0, 0,
		적성_A, 0, 0, 10, 0, 0, 50 },
	{ 특기_앙양, 50, 50, 0, 0, 0, 5, 5, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_연전, 60, 60, 0, 0, 0, 10, 10, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_급습, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_강습, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_난전, 60, 60, 0, 0, 0, 0, 0, 0, 0, 0,
		적성_A, 0, 0, 0, 0, 0, 50 },
	{ 특기_매복, 0, 0, 50, 0, 0, 0, 0, 5, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_공성, 60, 60, 0, 0, 0, 10, 10, 0, 0, 0,
		0, 병종_병기, 적성_A, 0, 병종_병기, 100, 50 },
	{ 특기_기각, 50, 50, 0, 0, 0, 8, 8, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_포박, 60, 60, 0, 0, 0, 5, 5, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_정묘, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_강탈, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_심공, 60, 60, 0, 0, 0, 10, 10, 0, 0, 0,
		0, 0, 0, 10, 0, 0, 50 },
	{ 특기_구축, 60, 70, 0, 0, 0, 10, 15, 0, 0, 0,
		0, 0, 0, 10, 0, 0, 50 },
	{ 특기_사정, 10, 10, 10, 0, 0, 5, 5, 5, 0, 0,
		0, 병종_병기, 적성_A, 0, 병종_병기, 100, 50 },
	{ 특기_백마, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_보좌, 50, 50, 0, 0, 0, 5, 10, 0, 0, 0,
		0, 0, 0, 0, 병종_노병, 100, 50 },
	{ 특기_불굴, 50, 50, 0, 0, 0, 5, 5, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_금강, 50, 50, 0, 0, 0, 5, 5, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_철벽, 50, 50, 0, 0, 0, 5, 5, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_노발, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_등갑, 60, 60, 0, 0, 0, 10, 10, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_강운, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_혈로, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_창장, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_극장, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_궁장, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_기장, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_수장, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_용장, 70, 75, 0, 0, 0, 10, 15, 0, 0, 0,
		적성_A, 0, 0, 20, 10, 150, 50 },
	{ 특기_신장, 70, 75, 0, 0, 0, 10, 15, 0, 0, 0,
		적성_A, 0, 0, 20, 10, 150, 50 },
	{ 특기_투신, 70, 75, 0, 0, 0, 12, 12, 0, 0, 0,
		적성_A, 병종_창병, 적성_A, 0, 병종_극병, 150, 50 },
	{ 특기_창신, 70, 75, 0, 0, 0, 12, 12, 0, 0, 0,
		0, 병종_창병, 적성_A, 0, 병종_창병, 150, 50 },
	{ 특기_극신, 70, 75, 0, 0, 0, 12, 12, 0, 0, 0,
		0, 병종_극병, 적성_A, 0, 병종_극병, 150, 50 },
	{ 특기_궁신, 70, 75, 0, 0, 0, 12, 12, 0, 0, 0,
		0, 병종_노병, 적성_A, 0, 병종_노병, 150, 50 },
	{ 특기_기신, 70, 75, 0, 0, 0, 12, 12, 0, 0, 0,
		0, 병종_기병, 적성_A, 0, 병종_기병, 150, 50 },
	{ 특기_공신, 70, 0, 0, 0, 0, 8, 8, 8, 0, 0,
		0, 병종_병기, 적성_A, 0, 병종_병기, 150, 50 },
	{ 특기_수신, 70, 75, 0, 0, 0, 12, 12, 0, 0, 0,
		0, 병종_수군, 적성_A, 0, 병종_수군, 150, 50 },
	{ 특기_패왕, 75, 75, 0, 0, 0, 12, 12, 0, 0, 0,
		적성_S, 0, 0, 20, 0, 0, 50 },
	{ 특기_질주, 70, 70, 0, 0, 0, 10, 10, 0, 0, 0,
		0, 병종_기병, 적성_A, 0, 병종_기병, 150, 50 },
	{ 특기_사수, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_맹장, 60, 60, 0, 0, 0, 10, 10, 0, 0, 0,
		적성_A, 0, 0, 10, 10, 100, 50 },
	{ 특기_호위, 50, 50, 0, 0, 0, 5, 5, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_화공, 0, 0, 50, 0, 0, 0, 0, 10, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_언독, 0, 0, 70, 0, 0, 0, 0, 10, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_기략, 0, 0, 70, 0, 0, 0, 0, 10, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_궤계, 0, 0, 65, 0, 0, 0, 0, 8, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_허실, 0, 0, 80, 0, 0, 0, 0, 15, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_묘계, 0, 0, 70, 0, 0, 0, 0, 15, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_비책, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_간파, 0, 0, 70, 0, 0, 0, 0, 10, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_통찰, 60, 60, 0, 0, 0, 5, 5, -2, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_화신, 0, 0, 75, 0, 0, 0, 0, 15, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_신산, 0, 0, 80, 0, 0, 0, 0, 15, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_백출, 0, 0, 70, 0, 0, 0, 0, 10, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_귀모, 0, 0, 70, 0, 0, 0, 0, 15, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_연환, 0, 0, 75, 0, 0, 0, 0, 15, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_심모, 0, 0, 65, 0, 0, 0, 0, 15, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_반계, 0, 0, 60, 0, 0, 0, 0, 5, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_경국, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_요술, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_귀문, 0, 0, 75, 0, 0, 0, 0, 15, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_규율, 50, 50, 0, 0, 0, 5, 5, -2, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_침착, 50, 50, 0, 0, 0, 5, 5, -2, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_명경, 50, 50, 0, 0, 0, 5, 5, -2, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_주악, 0, 0, 50, 0, 50, 0, 0, 5, 0, 5,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_시상, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_축성, 0, 0, 0, 60, 0, 0, 0, 0, 5, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_둔전, 0, 0, 0, 60, 0, 0, 0, 0, 7, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_명성, 0, 0, 0, 0, 60, 0, 0, 0, 0, 7,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_능리, 0, 0, 60, 0, 0, 0, 0, 10, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_번식, 0, 0, 60, 0, 0, 0, 0, 10, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_발명, 0, 0, 50, 0, 0, 0, 0, 5, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_조선, 0, 0, 50, 0, 0, 0, 0, 5, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_지도, 0, 0, 50, 50, 0, 0, 0, 5, 5, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_안력, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_논객, 0, 0, 75, 70, 0, 0, 0, 10, 5, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_부호, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_미도, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_징세, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_징수, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_친오, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_친강, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_친월, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_친만, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_위압, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_인정, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_풍수, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_기원, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 },
	{ 특기_내조, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 50 }
};

int 능력연구_통솔_저 = 0;
int 능력연구_통솔_중 = 1;
int 능력연구_통솔_고 = 2;
int 능력연구_무력_저 = 3;
int 능력연구_무력_중 = 4;
int 능력연구_무력_고 = 5;
int 능력연구_지력_저 = 6;
int 능력연구_지력_중 = 7;
int 능력연구_지력_고 = 8;
int 능력연구_정치_저 = 9;
int 능력연구_정치_중 = 10;
int 능력연구_정치_고 = 11;
int 능력연구_매력_저 = 12;
int 능력연구_매력_중 = 13;
int 능력연구_매력_고 = 14;
int 능력연구_창병_B = 15;
int 능력연구_창병_A = 16;
int 능력연구_극병_B = 17;
int 능력연구_극병_A = 18;
int 능력연구_노병_B = 19;
int 능력연구_노병_A = 20;
int 능력연구_기병_B = 21;
int 능력연구_기병_A = 22;
int 능력연구_병기_B = 23;
int 능력연구_병기_A = 24;
int 능력연구_수군_B = 25;
int 능력연구_수군_A = 26;

// 능력분배 점수 난수를 높일수록 능력치 좋은 무장들이 낮은 분배 우선순위가 될 확률이 높아집니다
// 능력분배의 로직 또한 특기 분배로직과 유사합니다.

int 능력분배_점수_난수 = 500;
int 능력분배_통솔_가중치 = 3;
int 능력분배_무력_가중치 = 2;
int 능력분배_지력_가중치 = 2;
int 능력분배_정치_가중치 = 1;
int 능력분배_매력_가중치 = 1;
int 능력분배_특기가치_가중치 = 10;

array<array<int>> 능력조건 =
{
	// AI가 알아서 부여하는 능력들은 따로 조건을 세팅하지 않았습니다(알아서 미리 거름)
	// 
	// 능력이름, 최대 통솔, 최소 통솔, 최대 무력, 최소 무력, 최대 지력, 최소 지력, 최대 정치, 최소 정치, 최대 매력, 최소 매력, 최소 통무합, 최소 통무지합
	// 
	// 대상이 되는 장수는 0을 제외한 모든 조건을 만족시켜야 합니다
	{ 능력연구_통솔_저, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 능력연구_통솔_중, 76, 70, 0, 0, 0, 0, 0, 0, 0, 0, 146, 0},
	{ 능력연구_통솔_고, 91, 83, 0, 0, 0, 0, 0, 0, 0, 0, 172, 212},
	{ 능력연구_무력_저, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 능력연구_무력_중, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 능력연구_무력_고, 0, 0, 91, 83, 0, 0, 0, 0, 0, 0, 165, 0},
	{ 능력연구_지력_저, 0, 70, 0, 70, 66, 50, 0, 0, 0, 0, 150, 0},
	{ 능력연구_지력_중, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 능력연구_지력_고, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 능력연구_정치_저, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 능력연구_정치_중, 0, 0, 0, 0, 0, 60, 76, 70, 0, 0, 0, 0},
	{ 능력연구_정치_고, 0, 0, 0, 0, 0, 70, 91, 80, 0, 0, 0, 0},
	{ 능력연구_매력_저, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 능력연구_매력_중, 0, 0, 0, 0, 0, 0, 0, 0, 76, 70, 0, 210},
	{ 능력연구_매력_고, 0, 0, 0, 0, 0, 0, 0, 0, 91, 80, 0, 240}
};

array<string> 능력이름 = { "통솔_저", "통솔_중", "통솔_고", "무력_저", "무력_중", "무력_고", "지력_저", "지력_중", "지력_고", "정치_저", "정치_중", "정치_고", "매력_저", "매력_중", "매력_고" };


/* 무제한 특기 배제
부여 횟수가 무제한인 특기가 있을 경우 그냥 로직에 포함시키면 해당 특기만 계속 부여하는 문제가 생길 수 있으므로
횟수가 있는 것부터 부여한 다음 가장 마지막에 부여하는 식으로 구성해야 합니다

무제한 특기가 여러개일 경우 부여할 때는 그 중 랜덤하게 하나를 선택해서 부여합니다

특기의 이름이 아닌 해당 능력연구 위치의 번호를 지정하셔야 합니다. 번호는 반에디터로 scenario.s11 파일을 열어 확인할 수 있습니다
*/

array<int> 무제한특기배제 =
{
	
};

/* 무제한 특기 배제
부여 횟수가 무제한인 특기가 있을 경우 그냥 로직에 포함시키면 해당 특기만 계속 부여하는 문제가 생길 수 있으므로
횟수가 있는 것부터 부여한 다음 가장 마지막에 부여하는 식으로 구성해야 합니다

무제한 특기가 여러개일 경우 부여할 때는 그 중 랜덤하게 하나를 선택해서 부여합니다

특기의 이름이 아닌 해당 능력연구 위치의 번호를 지정하셔야 합니다. 번호는 반에디터로 scenario.s11 파일을 열어 확인할 수 있습니다
*/

class Main
{
	
	Main()
	{
		pk::bind(108, pk::trigger108_t(onNewMonth));
	}
	
	void onNewMonth()
	{
		
		pk::list<pk::force@> forces;
		forces.clear();
		forces = pk::get_force_list();
		
		for (auto i = 0; i<forces.count; i++)
		{
			pk::force@ force = forces[i];
			if (pk::is_alive(force) and pk::is_normal_force(force)
				and pk::is_alive(pk::get_person(force.kunshu)) and !force.is_player())
			{
				if (true == 특기분배활용)
				{
					if (pk::get_month() % 특기분배_텀 == 1 || 특기분배_텀 == 1)
					{
						특기배분(force);
					}
				}
				if (true == 능력연구활용)
				{
					if (pk::get_month() % 능력분배_텀 == 1 || 능력분배_텀 == 1)
					{
						능력배분(force);
					}
				}
			}
		}
		
	}

/*
	세력별로 무장을 확인해 특기 부여
*/

void 특기배분( pk::force@ force )
{
	pk::person@ kun = pk::get_person(force.kunshu);
	int force_id = kun.get_force_id();
	int counter_limit = 0;
	
	pk::list<pk::person@> officers;
	officers.clear();

	for (int i = 0; i < 무장_끝; i++)
	{
		pk::person@ person = pk::get_person(i);
		if (pk::is_alive(person))
		{
			if (person.get_force_id() == force_id && person.mibun != 신분_포로)
			{
				officers.add(person);
			}
		}
	}

	// 각 능력연구에 대한 확인(일반)
	for (int i = 0; i < 21; i++)
	{
		int conabil = 27; //26번까지는 능력치 및 병종적성이고 27번부터 특기 부여이므로 상수 설정
		int abil = conabil + i;
		int best_value = 최소점수;
		int best_moo = -1;
		
		//연구되지 않았으면 패스
		if (!force.ability_researched[abil])
			continue;

		//부여 횟수가 무제한이면 패스
		if (무제한특기확인(abil))
			continue;

		// 한도 내로 특기를 부여했으면 패스
		if (counter_limit >= 회차당_최대특기분배)
			continue;
		
		//능력연구 정보 호출
		pk::ability@ aab = pk::get_ability(abil);
		
		int abil_skill = -1;    //능력연구의 특기

		abil_skill = aab.skill;

		//부여할 특기가 없으면 패스
		if (aab.skill == -1)
			continue;

		//해당 세력이 해당 연구의 특기를 부여한 횟수가 제한횟수 이상이면 패스
		if (int(force.training_counter[abil]) >= aab.limit)
			continue;

		//해당 연구의 부여 횟수가 비활성화 상태면 패스
		if (force.training_counter[abil] == 255)
			continue;

		//각 무장들에 대해 조건을 확인하고 가장 최선의 장수에게 특기 배분
		for (auto officer = 0; officer < officers.count; officer++)
		{
			//일반~군주 상태가 아닌 무장은 패스
			if( !( officers[officer].mibun >= 신분_군주 and officers[officer].mibun <= 신분_일반 ) )
				continue;

			//부대에 출진중인 무장은 패스
			if (officers[officer].location > 86)
				continue;

			//이미 행동을 완료한 무장이면 패스
			if (officers[officer].action_done)
				continue;
			
			//현재 장수가 보유한 특기의 가치가 부여할 특기의 가치보다 큰 차이가 나지 않거나 더 높으면 패스
			if (특기가치확인(abil_skill, officers[officer]))
				continue;

			//특기별로 설정된 최소조건을 만족하지 못하는 무장일 경우 패스
			if (최소조건확인(abil_skill, officers[officer]))
				continue;

			//모든 조건을 만족했으면 점수 계산
			int moo_value = 점수계산(abil_skill, officers[officer]);

			if (moo_value > best_value)
			{
				best_moo = officers[officer].get_id();
				best_value = moo_value;
			}
		}
		
		//조건에 맞는 무장에게 특기 부여
		if (best_moo != -1)
		{
			pk::person@ boomoo = pk::get_person(best_moo);
			boomoo.skill = abil_skill;

			//부여했으면 횟수 증가
			if (force.training_counter[abil] == 0)
			{	force.training_counter[abil] = 1;	}
			else if (force.training_counter[abil] == 1)
			{	force.training_counter[abil] = 2;	}
			else if (force.training_counter[abil] == 2)
			{	force.training_counter[abil] = 3;	}
			else if (force.training_counter[abil] == 3)
			{	force.training_counter[abil] = 4;	}
			else if (force.training_counter[abil] == 4)
			{	force.training_counter[abil] = 5;	}
			
			counter_limit += 1;
		}
	}

	//숨겨진 능력연구 특기 부여하기
	for (int i = 0; i < 10; i++)
	{
		//숨겨진 능력연구의 번호 찾기
		int abil = force.sp_ability[i];
		int best_value = 최소점수;
		int best_moo = -1;

		if (!force.sp_ability_researched[i])
			continue;

		// 한도 내로 특기를 부여했으면 패스
		if (counter_limit >= 회차당_최대특기분배)
			continue;

		if (무제한특기확인(abil))
			continue;

		pk::ability@ aab = pk::get_ability(abil);
		int abil_skill = -1;
		abil_skill = aab.skill;

		if (aab.skill == -1)
			continue;

		if (int(force.sp_training_counter[i]) >= aab.limit)
			continue;

		if (force.sp_training_counter[i] == 255)
			continue;

		for (auto officer = 0; officer < officers.count; officer++)
		{
			if( !( officers[officer].mibun >= 신분_군주 and officers[officer].mibun <= 신분_일반 ) )
				continue;

			if (officers[officer].location > 86)
				continue;

			if (officers[officer].action_done)
				continue;
			
			if (특기가치확인(abil_skill, officers[officer]))
				continue;

			if (최소조건확인(abil_skill, officers[officer]))
				continue;

			int moo_value = 점수계산(abil_skill, officers[officer]);

			if (moo_value > best_value)
			{
				best_moo = officers[officer].get_id();
				best_value = moo_value;
			}
		}
		
		//조건에 맞는 무장에게 특기 부여
		if (best_moo != -1)
		{
			pk::person@ boomoo = pk::get_person(best_moo);
			boomoo.skill = abil_skill;

			string s = "\x1b[2x" + pk::u8decode(pk::get_name(kun)) + "군\x1b[0x의 \x1b[1x" + pk::u8decode(pk::get_name(boomoo)) + "\x1b[0x, 특기「" + pk::u8decode(aab.name) + "」습득";
			if (true == 특기_로그_화면_표시)
			{
				pk::history_log(pk::get_building(boomoo.service).pos, force.color, pk::u8encode(s));
			}


			//부여했으면 횟수 증가
			if (force.sp_training_counter[i] == 0)
			{	force.sp_training_counter[i] = 1;	}
			else if (force.sp_training_counter[i] == 1)
			{	force.sp_training_counter[i] = 2;	}
			else if (force.sp_training_counter[i] == 2)
			{	force.sp_training_counter[i] = 3;	}
			else if (force.sp_training_counter[i] == 3)
			{	force.sp_training_counter[i] = 4;	}
			else if (force.sp_training_counter[i] == 4)
			{	force.sp_training_counter[i] = 5;	}
			
			counter_limit += 1;
		}
	}

	int n = 무제한특기수;

	//무제한 특기 부여하기
	if (n > 0)
	{
		int nansu = pk::rand(n);
	for (int i = 0; i < n; i++)
	{
		if (i != nansu)
			continue;

		// 한도 내로 특기를 부여했으면 패스
		if (counter_limit >= 회차당_최대특기분배)
			continue;

		int abil = 무제한특기배제[i];
		int best_value = 최소점수;
		int best_moo = -1;

		pk::ability@ aab = pk::get_ability(abil);
		int abil_skill = -1;
		abil_skill = aab.skill;

		if (aab.skill == -1)
			continue;

		if (abil < 48)
		{
			if (!force.ability_researched[abil])
				continue;

			if (force.training_counter[abil] == 255)
				continue;
		}
		else if (abil < 53)
		{
			if (!force.sp_ability_researched[0])
				continue;

			if (force.sp_training_counter[0] == 255)
				continue;
		}
		else if (abil < 58)
		{
			if (!force.sp_ability_researched[1])
				continue;

			if (force.sp_training_counter[1] == 255)
				continue;
		}
		else if (abil < 63)
		{
			if (!force.sp_ability_researched[2])
				continue;

			if (force.sp_training_counter[2] == 255)
				continue;
		}
		else if (abil < 68)
		{
			if (!force.sp_ability_researched[3])
				continue;

			if (force.sp_training_counter[3] == 255)
				continue;
		}
		else if (abil < 73)
		{
			if (!force.sp_ability_researched[4])
				continue;

			if (force.sp_training_counter[4] == 255)
				continue;
		}
		else if (abil < 78)
		{
			if (!force.sp_ability_researched[5])
				continue;

			if (force.sp_training_counter[5] == 255)
				continue;
		}
		else if (abil < 83)
		{
			if (!force.sp_ability_researched[6])
				continue;

			if (force.sp_training_counter[6] == 255)
				continue;
		}
		else if (abil < 88)
		{
			if (!force.sp_ability_researched[7])
				continue;

			if (force.sp_training_counter[7] == 255)
				continue;
		}
		else if (abil < 93)
		{
			if (!force.sp_ability_researched[8])
				continue;

			if (force.sp_training_counter[8] == 255)
				continue;
		}
		else
		{
			if (!force.sp_ability_researched[9])
				continue;

			if (force.sp_training_counter[9] == 255)
				continue;
		}

		for (auto officer = 0; officer < officers.count; officer++)
		{
			if( !( officers[officer].mibun >= 신분_군주 and officers[officer].mibun <= 신분_일반 ) )
				continue;

			if (officers[officer].location > 86)
				continue;

			if (officers[officer].action_done)
				continue;
			
			if (특기가치확인(abil_skill, officers[officer]))
				continue;

			if (최소조건확인(abil_skill, officers[officer]))
				continue;

			int moo_value = 점수계산(abil_skill, officers[officer]);

			if (moo_value > best_value)
			{
				best_moo = officers[officer].get_id();
				best_value = moo_value;
			}
		}
		
		//조건에 맞는 무장에게 특기 부여
		if (best_moo != -1)
		{
			pk::person@ boomoo = pk::get_person(best_moo);
			boomoo.skill = abil_skill;
			
			string s = "\x1b[2x" + pk::u8decode(pk::get_name(kun)) + "군\x1b[0x의 \x1b[1x" + pk::u8decode(pk::get_name(boomoo)) + "\x1b[0x, 특기「" + pk::u8decode(aab.name) + "」습득";

			if (true == 특기_로그_화면_표시)
			{
				pk::history_log(pk::get_building(boomoo.service).pos, force.color, pk::u8encode(s));
			}
			counter_limit += 1;
		}
	}
	}
}

//세력별로 무장을 확인해 능력연구 부여

void 능력배분(pk::force@ force)
{
	pk::person@ kun = pk::get_person(force.kunshu);
	int force_id = kun.get_force_id();

	pk::list<pk::person@> officers;
	officers.clear();
	int counter_limit = 0;

	for (int i = 0; i < 무장_끝; i++)
	{
		pk::person@ person = pk::get_person(i);
		if (pk::is_alive(person))
		{
			if (person.get_force_id() == force_id && person.mibun != 신분_포로)
			{
				officers.add(person);
			}
		}
	}

	// 각 능력연구에 대한 확인
	for (int i = 14; i >= 0; i--)
	{
		// 알아서 쓰는 능력연구는 패스
		if(i == 능력연구_통솔_저 || i == 능력연구_무력_중 || i == 능력연구_무력_저 || i == 능력연구_지력_고 || i == 능력연구_지력_중 || i == 능력연구_정치_저 || i == 능력연구_매력_저)
		{
			continue;
		}

		int abil = i;
		int best_value = 최소점수;
		int best_moo = -1;
		int abil_type = i / 3;
		// 한도 내로 능력을 부여했으면 패스
		if (counter_limit >= 회차당_최대능력분배)
			continue;

		//연구되지 않았으면 패스
		if (!force.ability_researched[abil])
			continue;

		//능력연구 정보 호출
		pk::ability@ aab = pk::get_ability(abil);

		//해당 세력이 해당 연구의 능력을 부여한 횟수가 제한횟수 이상이면 패스
		//if (int(force.training_counter[abil]) >= aab.limit)
		//	continue;

		// 능력연구 고 부여횟수 검사
		if (abil == 능력연구_통솔_고 || abil == 능력연구_무력_고 || abil == 능력연구_정치_고 || abil == 능력연구_매력_고)
		{
			if (int(force.training_counter[abil]) >= 능력연구_고_부여횟수)
			{
				continue;
			}
		}

		if (abil == 능력연구_통솔_중 || abil == 능력연구_정치_중 || abil == 능력연구_매력_중)
		{
			if (int(force.training_counter[abil]) >= 능력연구_중_부여횟수)
			{
				continue;
			}
		}

		if (abil == 능력연구_지력_저)
		{
			if (int(force.training_counter[abil]) >= 능력연구_저_부여횟수)
			{
				continue;
			}
		}

		//해당 연구의 부여 횟수가 비활성화 상태면 패스
		if (force.training_counter[abil] == 255)
			continue;

		//각 무장들에 대해 조건을 확인하고 가장 최선의 장수에게 특기 배분
		for (auto officer = 0; officer < officers.count; officer++)
		{
			//일반~군주 상태가 아닌 무장은 패스
			if (!(officers[officer].mibun >= 신분_군주 and officers[officer].mibun <= 신분_일반))
				continue;

			//부대에 출진중인 무장은 패스
			if (officers[officer].location > 86)
				continue;

			//이미 행동을 완료한 무장이면 패스
			if (officers[officer].action_done)
				continue;

			//능력연구별로 설정된 최대조건을 만족하지 못하는 무장일 경우 패스
			if (능력최대조건확인(abil, officers[officer]))
				continue;

			//능력연구별로 설정된 최소조건을 만족하지 못하는 무장일 경우 패스
			if (능력최소조건확인(abil, officers[officer]))
				continue;

			// 능력치가 20 이상 상승한 경우 육성을 금지합니다
			if (true == 기초능력육성제한)
			{
				if (기초능력육성제한확인(abil_type, officers[officer]))
				{
					continue;
				}
			}

			//모든 조건을 만족했으면 점수 계산
			int moo_value = 능력점수계산(officers[officer]);

			if (moo_value > best_value)
			{
				best_moo = officers[officer].get_id();
				best_value = moo_value;
			}
		}

		//조건에 맞는 무장에게 능력연구 부여
		if (best_moo != -1)
		{
			pk::person@ boomoo = pk::get_person(best_moo);

			//for (int j = 0; j < 5; ++j)
			//{
			//	임시능력치[j] = int(boomoo.base_stat[j]);
			//}
			int temp = int(boomoo.base_stat[abil_type]);
			능력적용(abil, boomoo);
			string s = "\x1b[2x" + pk::u8decode(pk::get_name(kun)) + "군\x1b[0x의 \x1b[1x" + pk::u8decode(pk::get_name(boomoo)) + "\x1b[0x, 능력연구「" + 능력이름[abil] + "」수행완료";

			if (true == 능력연구_로그_화면_표시)
			{
				pk::history_log(pk::get_building(boomoo.service).pos, force.color, pk::u8encode(s));
			}

			force.training_counter[abil] = force.training_counter[abil] + 1;

			counter_limit += 1;
		}
	}
}


bool 무제한특기확인( int abil )
{
	if (무제한특기수 == 0)
	{	return false;	}

	int n = 무제한특기수;

	for (int i = 0; i < n; i++)
	{
		if (abil == 무제한특기배제[i])
		{
			return true;
		}
	}
	
	return false;
}


bool 특기가치확인(int abil_skill, pk::person@ p)
{
	int moo_skill = p.skill;
	int k = 특기가치[abil_skill][1] - 1;
	int m = 0;

	if (p.skill == -1) //무특기일 경우 0점
	{
		m = 0;
	}
	else
	{
		if (moo_skill < 100)
		{
			m = 특기가치[moo_skill][1];
		}
		else
		{
			m = 5;
		}
	}

	if (m >= k)
		return true;

	return false;
}

bool 최소조건확인(int abil_skill, pk::person@ p)
{
	int moo_skill = int(p.skill);
	int abil_condition = 0;

	//능력치 조건 확인
	for (int i = 0; i < 5; i++)
	{
		if (특기조건[abil_skill][i+1] == 0)
			continue;
		if (특기조건[abil_skill][i+1] > int(p.stat[i]))
			return true;
	}

	//최소적성(수군, 병기 제외) 조건 확인
	for (int i = 0; i < 4; i++)
	{
		if (int(p.tekisei[i]) >= 특기조건[abil_skill][i+11])
			abil_condition = 1;
	}
	
	if (abil_condition == 0)
		return true;
	else
		abil_condition = 0;

	//최소특정병과 적성 조건 확인
	if (특기조건[abil_skill][13] > 0)
	{
		abil_condition = 특기조건[abil_skill][12];
		if (int(p.tekisei[abil_condition]) < 특기조건[abil_skill][13])
			return true;
	}

	return false;
}


bool 능력최대조건확인(int abil_skill, pk::person@ p)
{
	//능력치 조건 확인
	for (int i = 0; i < 5; i++)
	{
		if (능력조건[abil_skill][i*2 + 1] == 0)
			continue;
		if (능력조건[abil_skill][i*2 + 1] < int(p.base_stat[i]))
			return true;
	}

	return false;
}

bool 능력최소조건확인(int abil_skill, pk::person@ p)
{
	//능력치 조건 확인
	for (int i = 0; i < 5; i++)
	{
		if (능력조건[abil_skill][i*2 + 2] == 0)
			continue;
		if (능력조건[abil_skill][i*2 + 2] > int(p.base_stat[i]))
			return true;
	}
	
	// 통무합 최소 조건 확인
	if (능력조건[abil_skill][11] != 0)
	{
		if (능력조건[abil_skill][11] > (int(p.base_stat[무장능력_통솔]) + int(p.base_stat[무장능력_무력])))
		{
			return true;
		}
	}
	
	// 통무지합 최소 조건 확인
	if (능력조건[abil_skill][12] != 0)
	{
		if (능력조건[abil_skill][12] > (int(p.base_stat[무장능력_통솔]) + int(p.base_stat[무장능력_무력]) + int(p.base_stat[무장능력_지력])))
		{
			return true;
		}
	}

	return false;
}

bool 기초능력육성제한확인(int abil_skill, pk::person@ p)
{
	int index;


	if (int(p.base_stat[abil_skill]) >= int(p.max_stat[abil_skill]) + 20)
	{
		return true;
	}

	return false;
}

void 능력적용(int abil, pk::person@ p)
{
	if (abil == 능력연구_통솔_고)
	{
		p.base_stat[무장능력_통솔] = p.base_stat[무장능력_통솔] + 5;
		p.stat[무장능력_통솔] = p.stat[무장능력_통솔] + 5;

		if (p.base_stat[무장능력_통솔] > 능력연구_고_능력치_상한선)
		{
			p.base_stat[무장능력_통솔] = 능력연구_고_능력치_상한선;
		}
	}

	if (abil == 능력연구_통솔_중)
	{
		p.base_stat[무장능력_통솔] = p.base_stat[무장능력_통솔] + 5;
		p.stat[무장능력_통솔] = p.stat[무장능력_통솔] + 5;

		if (p.base_stat[무장능력_통솔] > 80)
		{
			p.base_stat[무장능력_통솔] = 80;
		}
	}

	if (abil == 능력연구_무력_고)
	{
		p.base_stat[무장능력_무력] = p.base_stat[무장능력_무력] + 5;
		p.stat[무장능력_무력] = p.stat[무장능력_무력] + 5;

		if (p.base_stat[무장능력_무력] > 능력연구_고_능력치_상한선)
		{
			p.base_stat[무장능력_무력] = 능력연구_고_능력치_상한선;
		}
	}

	if (abil == 능력연구_지력_저)
	{
		//string s = pk::format("성장 전 베이스 {}", int(p.base_stat[무장능력_지력]));
		//pk::history_log(pk::get_building(p.service).pos, -1, pk::u8encode(s));
		p.base_stat[무장능력_지력] = p.base_stat[무장능력_지력] + 5;
		p.stat[무장능력_지력] = p.stat[무장능력_지력] + 5;
		if (p.base_stat[무장능력_지력] > 70)
		{
			p.base_stat[무장능력_지력] = 70;
		}
	}

	if (abil == 능력연구_정치_고)
	{
		p.base_stat[무장능력_정치] = p.base_stat[무장능력_정치] + 5;
		p.stat[무장능력_정치] = p.stat[무장능력_정치] + 5;
		if (p.base_stat[무장능력_정치] > 능력연구_고_능력치_상한선)
		{
			p.base_stat[무장능력_정치] = 능력연구_고_능력치_상한선;
		}
	}

	if (abil == 능력연구_정치_중)
	{
		p.base_stat[무장능력_정치] = p.base_stat[무장능력_정치] + 5;
		p.stat[무장능력_정치] = p.stat[무장능력_정치] + 5;
		if (p.base_stat[무장능력_정치] > 80)
		{
			p.base_stat[무장능력_정치] = 80;
		}
	}

	if (abil == 능력연구_매력_고)
	{
		p.base_stat[무장능력_매력] = p.base_stat[무장능력_매력] + 5;
		p.stat[무장능력_매력] = p.stat[무장능력_매력] + 5;
		if (p.base_stat[무장능력_매력] > 능력연구_고_능력치_상한선)
		{
			p.base_stat[무장능력_매력] = 능력연구_고_능력치_상한선;
		}
	}

	if (abil == 능력연구_매력_중)
	{
		p.base_stat[무장능력_매력] = p.base_stat[무장능력_매력] + 5;
		p.stat[무장능력_매력] = p.stat[무장능력_매력] + 5;
		if (p.base_stat[무장능력_매력] > 80)
		{
			p.base_stat[무장능력_매력] = 80;
		}
	}
}

int 점수계산(int abil_skill, pk::person@ p)
{
	int moo_value = pk::rand(점수_난수);
	moo_value += int(p.stat[무장능력_통솔]) * 특기조건[abil_skill][6] + int(p.stat[무장능력_무력]) * 특기조건[abil_skill][7] + int(p.stat[무장능력_지력]) * 특기조건[abil_skill][8] + int(p.stat[무장능력_정치]) * 특기조건[abil_skill][9] + int(p.stat[무장능력_매력]) * 특기조건[abil_skill][10];

	int moo_skill = p.skill;
	int m = 0;

	if (p.skill == -1)
	{
		m = 0;
	}
	else
	{
		if (moo_skill < 100)
		{
			m = 특기가치[moo_skill][1];
		}
		else
		{
			m = 5;
		}
	}

	moo_value += (특기가치[abil_skill][1] - m) * 특기조건[abil_skill][17];

	if (특기조건[abil_skill][14] > 0)
	{
		moo_value += (int(p.tekisei[0]) + int(p.tekisei[1]) + int(p.tekisei[2]) + int(p.tekisei[3])) * 특기조건[abil_skill][14];
	}

	if (특기조건[abil_skill][16] > 0)
	{
		int moo_teki = 특기조건[abil_skill][15];
		if (moo_teki == 10)
		{
			for (int k = 0; k < 4; k++)
			{
				if (p.tekisei[k] >= 적성_S)
				{
					moo_value += 특기조건[abil_skill][16];
					continue;
				}
			}
		}
		else if (p.tekisei[moo_teki] >= 적성_S)
		{
			moo_value += 특기조건[abil_skill][16];
		}
	}

	return moo_value;
}

int 능력점수계산(pk::person@ p)
{
	int moo_value = pk::rand(능력분배_점수_난수);
	moo_value += int(p.stat[무장능력_통솔]) * 능력분배_통솔_가중치 + int(p.stat[무장능력_무력]) * 능력분배_무력_가중치 + int(p.stat[무장능력_지력]) * 능력분배_지력_가중치 + int(p.stat[무장능력_정치]) * 능력분배_정치_가중치 + int(p.stat[무장능력_매력]) * 능력분배_매력_가중치;
			
	int moo_skill = p.skill;
	int m = 0;

	if (p.skill == -1)
	{
		m = 0;
	}
	else
	{
		if (moo_skill < 100)
		{
			m = 특기가치[moo_skill][1] * 10;
		}
		else
		{
			m = 50;
		}
	}

	moo_value += m;

	return moo_value;
}
}
	Main main;
}