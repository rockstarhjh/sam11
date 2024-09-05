/*     
@제작자: 한솥도시락   
@내용: Honeybee님의 무장발탁 스크립트를 기반으로 한 무장가챠뽑기 스크립트
*/
 
namespace 무장가챠
{
	
	// CUSTOMIZE =======================================================================================================================
	
		const int TP_COST = 1000; 		               // 획득 기교P 수치 결정         (기본 설정 - 1000)
		int 일반특별전환 = 1;                               // 일반발탁과 특별발탁 전환        (1 - 특별, 0 - 일반)
		int 필요행동력 = 2;                                // 행동력 필요량              (기본 설정 - 20)
		int 필요금 = 2;                                  // 금 필요량                 (기본 설정 - 500)
		int 발탁실패확률 = 75;    		                   // 무장발탁이 실패할 확률         (기본 설정 - 75%)
		int 성별비율 = 50;    		                       // 남성무장이 발탁될 확률         (기본 설정 - 50%)
		int 이벤트실행여부 = 1;                             // 일기토 설전 이벤트 실행여부     (1 - 실행, 0 - 실행안함)
		int v;                                         // 전역변수
		
	// 자원설정 ===========================================================================================================================
	
		int 소모행동력;
		int 소모금;
		int 행동력1 = 0;
		int 행동력2 = 10;
		int 행동력3 = 20;
		int 행동력4 = 30;
		int 금1 = 0;
		int 금2 = 100;
		int 금3 = 500;
		int 금4 = 1000;
		
	// 무장능력치 설정 =======================================================================================================================

		/* 
		   발탁 무장은 8가지 中 한 가지 TYPE이 결정됩니다.
		   0-EX등급_무관형,  총합 능력치 400 이상, 통솔 무력 90이상, 최대 능력치 100
		   1-EX등급_문관형,  총합 능력치 400 이상, 지력 정치 90이상, 최대 능력치 100
		   2-SSR등급_무관형, 총합 능력치 300 이상, 통솔 무력 80이상, 최대 능력치 99
		   3-SSR등급_문관형, 총합 능력치 300 이상, 지력 정치 80이상, 최대 능력치 99
		   4-SR등급_무관형,  총합 능력치 200 이상, 통솔 무력 60이상, 최대 능력치 95
		   5-SR등급_문관형,  총합 능력치 200 이상, 지력 정치 60이상, 최대 능력치 95
		   6-R등급_무관형,   총합 능력치 100 이상, 통솔 무력 40이상, 최대 능력치 90
		   7-R등급_문관형,   총합 능력치 100 이상, 지력 정치 40이상, 최대 능력치 90
		   8-N등급_올랜덤,   랜덤
		   9-F등급_폐급,    최대 능력치 75
		*/ 

	    // 0-EX등급_무관형 능력치 설정
		const int min_stat_EX등급_무관형_통솔 = 90;    // EX등급_무관형 발탁 무장의 최소 통솔 능력치를 설정 (기본 설정 - 90)
		const int max_stat_EX등급_무관형_통솔 = 100;   // EX등급_무관형 발탁 무장의 최대 통솔 능력치를 설정 (기본 설정 - 100)
		
		const int min_stat_EX등급_무관형_무력 = 90;    // EX등급_무관형 발탁 무장의 최소 무력 능력치를 설정 (기본 설정 - 90)
		const int max_stat_EX등급_무관형_무력 = 100;   // EX등급_무관형 발탁 무장의 최대 무력 능력치를 설정 (기본 설정 - 100)
		
		const int min_stat_EX등급_무관형_지력 = 70;    // EX등급_무관형 발탁 무장의 최소 지력 능력치를 설정 (기본 설정 - 70)
		const int max_stat_EX등급_무관형_지력 = 100;   // EX등급_무관형 발탁 무장의 최대 지력 능력치를 설정 (기본 설정 - 100)
		
		const int min_stat_EX등급_무관형_정치 = 70;    // EX등급_무관형 발탁 무장의 최소 정치 능력치를 설정 (기본 설정 - 70)
		const int max_stat_EX등급_무관형_정치 = 100;   // EX등급_무관형 발탁 무장의 최대 정치 능력치를 설정 (기본 설정 - 100)

        const int min_stat_EX등급_무관형_매력 = 80;    // EX등급_무관형 발탁 무장의 최소 매력 능력치를 설정 (기본 설정 - 80)
		const int max_stat_EX등급_무관형_매력 = 100;   // EX등급_무관형 발탁 무장의 최대 매력 능력치를 설정 (기본 설정 - 100)

        // 1-EX등급_문관형 능력치 설정
		const int min_stat_EX등급_문관형_통솔 = 70;    // EX등급_문관형 발탁 무장의 최소 통솔 능력치를 설정 (기본 설정 - 70)
		const int max_stat_EX등급_문관형_통솔 = 100;   // EX등급_문관형 발탁 무장의 최대 통솔 능력치를 설정 (기본 설정 - 100)
		
		const int min_stat_EX등급_문관형_무력 = 70;    // EX등급_문관형 발탁 무장의 최소 무력 능력치를 설정 (기본 설정 - 70)
		const int max_stat_EX등급_문관형_무력 = 100;   // EX등급_문관형 발탁 무장의 최대 무력 능력치를 설정 (기본 설정 - 100)
		
		const int min_stat_EX등급_문관형_지력 = 90;    // EX등급_문관형 발탁 무장의 최소 지력 능력치를 설정 (기본 설정 - 90)
		const int max_stat_EX등급_문관형_지력 = 100;   // EX등급_문관형 발탁 무장의 최대 지력 능력치를 설정 (기본 설정 - 100)
		
		const int min_stat_EX등급_문관형_정치 = 90;    // EX등급_문관형 발탁 무장의 최소 정치 능력치를 설정 (기본 설정 - 90)
		const int max_stat_EX등급_문관형_정치 = 100;   // EX등급_문관형 발탁 무장의 최대 정치 능력치를 설정 (기본 설정 - 100)

        const int min_stat_EX등급_문관형_매력 = 80;    // EX등급_문관형 발탁 무장의 최소 매력 능력치를 설정 (기본 설정 - 80)
		const int max_stat_EX등급_문관형_매력 = 100;   // EX등급_문관형 발탁 무장의 최대 매력 능력치를 설정 (기본 설정 - 100)

		// 2-SSR등급_무관형 능력치 설정
		const int min_stat_SSR등급_무관형_통솔 = 80;   // SSR등급_무관형 발탁 무장의 최소 통솔 능력치를 설정 (기본 설정 - 80)
		const int max_stat_SSR등급_무관형_통솔 = 99;   // SSR등급_무관형 발탁 무장의 최대 통솔 능력치를 설정 (기본 설정 - 99)
		
		const int min_stat_SSR등급_무관형_무력 = 80;   // SSR등급_무관형 발탁 무장의 최소 무력 능력치를 설정 (기본 설정 - 80)
		const int max_stat_SSR등급_무관형_무력 = 99;   // SSR등급_무관형 발탁 무장의 최대 무력 능력치를 설정 (기본 설정 - 99)
		
		const int min_stat_SSR등급_무관형_지력 = 40;   // SSR등급_무관형 발탁 무장의 최소 지력 능력치를 설정 (기본 설정 - 40)
		const int max_stat_SSR등급_무관형_지력 = 99;   // SSR등급_무관형 발탁 무장의 최대 지력 능력치를 설정 (기본 설정 - 99)
		
		const int min_stat_SSR등급_무관형_정치 = 40;   // SSR등급_무관형 발탁 무장의 최소 정치 능력치를 설정 (기본 설정 - 40)
		const int max_stat_SSR등급_무관형_정치 = 99;   // SSR등급_무관형 발탁 무장의 최대 정치 능력치를 설정 (기본 설정 - 99)

        const int min_stat_SSR등급_무관형_매력 = 60;   // SSR등급_무관형 발탁 무장의 최소 매력 능력치를 설정 (기본 설정 - 60)
		const int max_stat_SSR등급_무관형_매력 = 99;   // SSR등급_무관형 발탁 무장의 최대 매력 능력치를 설정 (기본 설정 - 99)
		
		// 3-SSR등급_문관형 능력치 설정
		const int min_stat_SSR등급_문관형_통솔 = 40;   // SSR등급_문관형 발탁 무장의 최소 통솔 능력치를 설정 (기본 설정 - 40)
		const int max_stat_SSR등급_문관형_통솔 = 99;   // SSR등급_문관형 발탁 무장의 최대 통솔 능력치를 설정 (기본 설정 - 99)
		
		const int min_stat_SSR등급_문관형_무력 = 40;   // SSR등급_문관형 발탁 무장의 최소 무력 능력치를 설정 (기본 설정 - 40)
		const int max_stat_SSR등급_문관형_무력 = 99;   // SSR등급_문관형 발탁 무장의 최대 무력 능력치를 설정 (기본 설정 - 99)
		
		const int min_stat_SSR등급_문관형_지력 = 80;   // SSR등급_문관형 발탁 무장의 최소 지력 능력치를 설정 (기본 설정 - 80)
		const int max_stat_SSR등급_문관형_지력 = 99;   // SSR등급_문관형 발탁 무장의 최대 지력 능력치를 설정 (기본 설정 - 99)
		
		const int min_stat_SSR등급_문관형_정치 = 80;   // SSR등급_문관형 발탁 무장의 최소 정치 능력치를 설정 (기본 설정 - 80)
		const int max_stat_SSR등급_문관형_정치 = 99;   // SSR등급_문관형 발탁 무장의 최대 정치 능력치를 설정 (기본 설정 - 99)

        const int min_stat_SSR등급_문관형_매력 = 60;   // SSR등급_문관형 발탁 무장의 최소 매력 능력치를 설정 (기본 설정 - 60)
		const int max_stat_SSR등급_문관형_매력 = 99;   // SSR등급_문관형 발탁 무장의 최대 매력 능력치를 설정 (기본 설정 - 99)
		
		// 4-SR등급_무관형 능력치 설정
		const int min_stat_SR등급_무관형_통솔 = 60;   // SR등급_무관형 발탁 무장의 최소 통솔 능력치를 설정 (기본 설정 - 60)
		const int max_stat_SR등급_무관형_통솔 = 95;   // SR등급_무관형 발탁 무장의 최대 통솔 능력치를 설정 (기본 설정 - 95)
		
		const int min_stat_SR등급_무관형_무력 = 60;   // SR등급_무관형 발탁 무장의 최소 무력 능력치를 설정 (기본 설정 - 60)
		const int max_stat_SR등급_무관형_무력 = 95;   // SR등급_무관형 발탁 무장의 최대 무력 능력치를 설정 (기본 설정 - 95)
		
		const int min_stat_SR등급_무관형_지력 = 20;   // SR등급_무관형 발탁 무장의 최소 지력 능력치를 설정 (기본 설정 - 20)
		const int max_stat_SR등급_무관형_지력 = 80;   // SR등급_무관형 발탁 무장의 최대 지력 능력치를 설정 (기본 설정 - 80)
		
		const int min_stat_SR등급_무관형_정치 = 20;   // SR등급_무관형 발탁 무장의 최소 정치 능력치를 설정 (기본 설정 - 20)
		const int max_stat_SR등급_무관형_정치 = 80;   // SR등급_무관형 발탁 무장의 최대 정치 능력치를 설정 (기본 설정 - 80)

        const int min_stat_SR등급_무관형_매력 = 40;   // SR등급_무관형 발탁 무장의 최소 매력 능력치를 설정 (기본 설정 - 40)
		const int max_stat_SR등급_무관형_매력 = 95;   // SR등급_무관형 발탁 무장의 최대 매력 능력치를 설정 (기본 설정 - 95)
		
		// 5-SR등급_문관형 능력치 설정
		const int min_stat_SR등급_문관형_통솔 = 20;   // SR등급_문관형 발탁 무장의 최소 통솔 능력치를 설정 (기본 설정 - 20)
		const int max_stat_SR등급_문관형_통솔 = 80;   // SR등급_문관형 발탁 무장의 최대 통솔 능력치를 설정 (기본 설정 - 80)
		
		const int min_stat_SR등급_문관형_무력 = 20;   // SR등급_문관형 발탁 무장의 최소 무력 능력치를 설정 (기본 설정 - 20)
		const int max_stat_SR등급_문관형_무력 = 80;   // SR등급_문관형 발탁 무장의 최대 무력 능력치를 설정 (기본 설정 - 80)
		
		const int min_stat_SR등급_문관형_지력 = 60;   // SR등급_문관형 발탁 무장의 최소 지력 능력치를 설정 (기본 설정 - 60)
		const int max_stat_SR등급_문관형_지력 = 95;   // SR등급_문관형 발탁 무장의 최대 지력 능력치를 설정 (기본 설정 - 95)
		
		const int min_stat_SR등급_문관형_정치 = 60;   // SR등급_문관형 발탁 무장의 최소 정치 능력치를 설정 (기본 설정 - 60)
		const int max_stat_SR등급_문관형_정치 = 95;   // SR등급_문관형 발탁 무장의 최대 정치 능력치를 설정 (기본 설정 - 95)

        const int min_stat_SR등급_문관형_매력 = 40;   // SR등급_문관형 발탁 무장의 최소 매력 능력치를 설정 (기본 설정 - 40)
		const int max_stat_SR등급_문관형_매력 = 95;   // SR등급_문관형 발탁 무장의 최대 매력 능력치를 설정 (기본 설정 - 95)
		
		// 6-R등급_무관형 능력치 설정
		const int min_stat_R등급_무관형_통솔 = 40;   // R등급_무관형 발탁 무장의 최소 통솔 능력치를 설정 (기본 설정 - 40)
		const int max_stat_R등급_무관형_통솔 = 90;   // R등급_무관형 발탁 무장의 최대 통솔 능력치를 설정 (기본 설정 - 90)
		
		const int min_stat_R등급_무관형_무력 = 40;   // R등급_무관형 발탁 무장의 최소 무력 능력치를 설정 (기본 설정 - 40)
		const int max_stat_R등급_무관형_무력 = 90;   // R등급_무관형 발탁 무장의 최대 무력 능력치를 설정 (기본 설정 - 90)
		
		const int min_stat_R등급_무관형_지력 = 1;    // R등급_무관형 발탁 무장의 최소 지력 능력치를 설정 (기본 설정 - 1)
		const int max_stat_R등급_무관형_지력 = 60;   // R등급_무관형 발탁 무장의 최대 지력 능력치를 설정 (기본 설정 - 60)
		
		const int min_stat_R등급_무관형_정치 = 1;    // R등급_무관형 발탁 무장의 최소 정치 능력치를 설정 (기본 설정 - 1)
		const int max_stat_R등급_무관형_정치 = 60;   // R등급_무관형 발탁 무장의 최대 정치 능력치를 설정 (기본 설정 - 60)

        const int min_stat_R등급_무관형_매력 = 20;   // R등급_무관형 발탁 무장의 최소 매력 능력치를 설정 (기본 설정 - 20)
		const int max_stat_R등급_무관형_매력 = 90;   // R등급_무관형 발탁 무장의 최대 매력 능력치를 설정 (기본 설정 - 90)
		
		// 7-R등급_문관형 능력치 설정
		const int min_stat_R등급_문관형_통솔 = 1;    // R등급_문관형 발탁 무장의 최소 통솔 능력치를 설정 (기본 설정 - 1)
		const int max_stat_R등급_문관형_통솔 = 60;   // R등급_문관형 발탁 무장의 최대 통솔 능력치를 설정 (기본 설정 - 60)
		
		const int min_stat_R등급_문관형_무력 = 1;    // R등급_문관형 발탁 무장의 최소 무력 능력치를 설정 (기본 설정 - 1)
		const int max_stat_R등급_문관형_무력 = 60;   // R등급_문관형 발탁 무장의 최대 무력 능력치를 설정 (기본 설정 - 60)
		
		const int min_stat_R등급_문관형_지력 = 40;   // R등급_문관형 발탁 무장의 최소 지력 능력치를 설정 (기본 설정 - 40)
		const int max_stat_R등급_문관형_지력 = 90;   // R등급_문관형 발탁 무장의 최대 지력 능력치를 설정 (기본 설정 - 90)
		
		const int min_stat_R등급_문관형_정치 = 40;   // R등급_문관형 발탁 무장의 최소 정치 능력치를 설정 (기본 설정 - 40)
		const int max_stat_R등급_문관형_정치 = 90;   // R등급_문관형 발탁 무장의 최대 정치 능력치를 설정 (기본 설정 - 90)

        const int min_stat_R등급_문관형_매력 = 20;   // R등급_문관형 발탁 무장의 최소 매력 능력치를 설정 (기본 설정 - 20)
		const int max_stat_R등급_문관형_매력 = 90;   // R등급_문관형 발탁 무장의 최대 매력 능력치를 설정 (기본 설정 - 90)
		
		// 8-N등급_올랜덤 능력치 설정
		const int min_stat_N등급_올랜덤_통솔 = 1;    // N등급_올랜덤 발탁 무장의 최소 통솔 능력치를 설정 (기본 설정 - 1)
		const int max_stat_N등급_올랜덤_통솔 = 90;   // N등급_올랜덤 발탁 무장의 최대 통솔 능력치를 설정 (기본 설정 - 90)
		
		const int min_stat_N등급_올랜덤_무력 = 1;    // N등급_올랜덤 발탁 무장의 최소 무력 능력치를 설정 (기본 설정 - 1)
		const int max_stat_N등급_올랜덤_무력 = 90;   // N등급_올랜덤 발탁 무장의 최대 무력 능력치를 설정 (기본 설정 - 90)
		
		const int min_stat_N등급_올랜덤_지력 = 1;    // N등급_올랜덤 발탁 무장의 최소 지력 능력치를 설정 (기본 설정 - 1)
		const int max_stat_N등급_올랜덤_지력 = 90;   // N등급_올랜덤 발탁 무장의 최대 지력 능력치를 설정 (기본 설정 - 90)
		
		const int min_stat_N등급_올랜덤_정치 = 1;    // N등급_올랜덤 발탁 무장의 최소 정치 능력치를 설정 (기본 설정 - 1)
		const int max_stat_N등급_올랜덤_정치 = 90;   // N등급_올랜덤 발탁 무장의 최대 정치 능력치를 설정 (기본 설정 - 90)

        const int min_stat_N등급_올랜덤_매력 = 1;    // N등급_올랜덤 발탁 무장의 최소 매력 능력치를 설정 (기본 설정 - 1)
		const int max_stat_N등급_올랜덤_매력 = 90;   // N등급_올랜덤 발탁 무장의 최대 매력 능력치를 설정 (기본 설정 - 90)
		
		// 9-F등급_폐급 능력치 설정
		const int min_stat_F등급_폐급_통솔 = 1;    // F등급_폐급 발탁 무장의 최소 통솔 능력치를 설정 (기본 설정 - 1)
		const int max_stat_F등급_폐급_통솔 = 75;   // F등급_폐급 발탁 무장의 최대 통솔 능력치를 설정 (기본 설정 - 75)
		
		const int min_stat_F등급_폐급_무력 = 1;    // F등급_폐급 발탁 무장의 최소 무력 능력치를 설정 (기본 설정 - 1)
		const int max_stat_F등급_폐급_무력 = 75;   // F등급_폐급 발탁 무장의 최대 무력 능력치를 설정 (기본 설정 - 75)
		
		const int min_stat_F등급_폐급_지력 = 1;    // F등급_폐급 발탁 무장의 최소 지력 능력치를 설정 (기본 설정 - 1)
		const int max_stat_F등급_폐급_지력 = 75;   // F등급_폐급 발탁 무장의 최대 지력 능력치를 설정 (기본 설정 - 75)
		
		const int min_stat_F등급_폐급_정치 = 1;    // F등급_폐급 발탁 무장의 최소 정치 능력치를 설정 (기본 설정 - 1)
		const int max_stat_F등급_폐급_정치 = 75;   // F등급_폐급 발탁 무장의 최대 정치 능력치를 설정 (기본 설정 - 75)

        const int min_stat_F등급_폐급_매력 = 1;    // F등급_폐급 발탁 무장의 최소 매력 능력치를 설정 (기본 설정 - 1)
		const int max_stat_F등급_폐급_매력 = 75;   // F등급_폐급 발탁 무장의 최대 매력 능력치를 설정 (기본 설정 - 75)
						
				
		const bool 이름자동 = false;	    // 무장 이름을 자동으로 생성	[이름자동 true일시, 이름수동 false로 지정]
		const bool 이름수동 = true;        // 무장 이름을 수동(배열 작성)으로 생성 [이름수동 true일시, 이름자동 false로 지정]
				
		
		// 특기 관련 =======================================================================================================================
		
        const array<int> 사기특기_무관 = { 특기_패왕, 특기_신장, 특기_비장, 특기_투신, 특기_포박 };                                         //EX등급_무관형
		
		const array<int> 사기특기_문관 = { 특기_귀문, 특기_신산, 특기_백출, 특기_화신, 특기_논객 };                                         //EX등급_문관형
				
		const array<int> 고급특기_무관 = { 특기_용장, 특기_창신, 특기_극신, 특기_기신, 특기_궁신, 특기_공신, 특기_수신, 특기_질주, 특기_맹장, 특기_연전,    //SSR등급_무관형
		                              특기_심공, 특기_위풍, 특기_도주, 특기_강행, 특기_보좌 };
									  
		const array<int> 고급특기_문관 = { 특기_허실, 특기_연환, 특기_귀모, 특기_심모, 특기_통찰, 특기_경국, 특기_요술, 특기_명성, 특기_능리, 특기_번식,  	//SSR등급_문관형
		                              특기_발명, 특기_조선, 특기_부호, 특기_미도, 특기_인정 };
									  
	    const array<int> 중급특기_무관 = { 특기_구축, 특기_창장, 특기_극장, 특기_기장, 특기_궁장, 특기_공성, 특기_수장, 특기_앙양, 특기_사수, 특기_사정,    //SR등급, R등급_무관형
		                              특기_난전, 특기_강운, 특기_호위, 특기_금강, 특기_불굴 };   		
									  
		const array<int> 중급특기_문관 = { 특기_기략, 특기_언독, 특기_궤계, 특기_묘계, 특기_간파, 특기_명경, 특기_매복, 특기_화공, 특기_시상, 특기_주악,    //SR등급, R등급_문관형  
		                              특기_축성, 특기_둔전, 특기_징세, 특기_징수, 특기_지도 };   
									  
		const array<int> 하급특기_범용 = { 특기_강습, 특기_강탈, 특기_급습, 특기_기각, 특기_백마, 특기_소탕, 특기_노발, 특기_등갑, 특기_철벽, 특기_혈로,    //F등급
		                              특기_규율, 특기_침착, 특기_비책, 특기_반계, 특기_답파, 특기_조타, 특기_운반, 특기_추진, 특기_해독, 특기_행군,   
		                              특기_친강, 특기_친월, 특기_친오, 특기_친만, 특기_안력, 특기_풍수, 특기_기원, 특기_내조, 특기_위압, 특기_정묘 }; 
		        

		// 발탁무장 SLOT 지정 관련 (중요) ========================================================================================================
		
		/* 
		   - 무장의 SLOT을 지정 (반드시 3가지 中 한 가지만 true, 나머지는 false로 설정해야됨)
		   - slot_신무장은 Gold Edition Patch에서 제작한 신무장의 갯수에 따라서 기본으로 적용함
		   - Evony 패치 기준 등록된 신무장이 850 ~ 960 이므로, 961부터 발탁 무장을 작성하도록 기본 설정 (961 ~ 999까지 설정함)
		*/
		
		// 신무장 SLOT을 사용하여 발탁무장 추가 (단점: 신무장의 SLOT을 사용하므로, 신무장을 많이 생성했을 경우 비추천)
		const bool slot_신무장 = true;
		
		// 일반무장(이미 사망하거나 신분없는 무장) SLOT을 사용하여 발탁무장 추가 (단점: 사망한 무장이 적다면, SLOT의 제약이 큼)
		const bool slot_일반무장 = false;
		
		// 미사용 고대무장 SLOT을 사용하여 발탁무장 추가 (단점: SLOT의 제약이 큼, 최대 18人)
		const bool slot_고대무장 = false;

		// ===============================================================================================================================
		
		/* 
		    발탁 무장 이름을 ARRAY로 미리 SETTING 하시기 바랍니다. (아래는 임시로 넣은 성명입니다.)
			아래 성명에서 RANDOM으로 출력하여 발탁 무장의 이름이 정해집니다.
			
			EX) 조조, 조비, 조견, 유비, 유견, 유탁, 손견, 손탁, 손포 등..
		
		*/
		
		// 발탁 무장 [성] (임시로 132개 설정)
		array<string> sei_ = { "가", "간", "감", "강", "견", "곽", "관", "고", "공", "구", 
		                       "국", "교", "나", "노", "뇌", "능", "단", "담", "당", "대", 
							   "도", "동", "두", "등", "마", "만", "매", "맹", "모", "목", 
							   "몽", "무", "문", "미", "민", "반", "방", "번", "범", "배", 
							   "백", "변", "봉", "부", "비", "사", "상", "서", "석", "선", 
							   "설", "성", "소", "손", "송", "순", "신", "심", "악", "안", 
							   "양", "언", "엄", "여", "연", "염", "엽", "영", "왕", "오", 
							   "요", "용", "우", "위", "유", "육", "윤", "원", "은", "이", 
							   "임", "장", "전", "정", "제", "종", "조", "주", "증", "진", 
							   "천", "청", "채", "초", "최", "추", "팽", "포", "풍", "하", 
							   "학", "한", "함", "항", "허", "현", "화", "황", "호", "후", 
							   "공손", "제갈", "남궁", "하후", "사마", "독고", "황보", "모용", "단목", "서문", 
							   "관구", "혁련", "태사", "순우", "선우", "구양", "상관", "종리", "사공", "위지",
							   "호연", "동방"
							  };

	    // 발탁 무장 [이름(남)] (임시로 160개로 설정)
		array<string> mei_남 = { "가", "각", "강", "개", "거", "건", "검", "견", "겸", "경",  
		                        "계", "고", "곤", "공", "관", "광", "굉", "구", "군", "궁",    
		                        "규", "균", "권", "극", "근", "금", "기", "녕", "노", "능",    
							    "단", "담", "당", "대", "도", "돈", "동", "두", "란", "랑",         
							    "량", "로", "료", "루", "만", "막", "맹", "명", "모", "몽",        
							    "무", "문", "반", "방", "배", "백", "범", "벽", "보", "복", 
							    "봉", "부", "비", "빈", "사", "상", "서", "선", "석", "섬", 
							    "성", "소", "속", "손", "송", "수", "숙", "순", "술", "숭", 
							    "습", "승", "시", "식", "신", "악", "앙", "양", "억", "언", 
							    "엄", "여", "연", "염", "영", "옹", "요", "완", "우", "월", 
							    "욱", "운", "웅", "유", "윤", "원", "위", "의", "익", "인", 
								"작", "장", "재", "저", "적", "전", "정", "제", "조", "종", 
							    "주", "준", "중", "증", "지", "진", "찬", "창", "책", "천", 
								"첨", "초", "추", "축", "춘", "충", "칙", "침", "탁", "탄", 
								"태", "패", "평", "포", "풍", "학", "항", "황", "헌", "현", 
								"호", "홍", "화", "환", "회", "후", "훈", "휘", "흥", "희"
							  }; 
		
		// 발탁 무장 [이름(여)] (임시로 120개로 설정)
		array<string> mei_여 = { "가", "경", "교", "금", "단", "란", "랑", "려", "련", "린", 
		                        "림", "매", "명", "몽", "문", "미", "민", "반", "방", "백", 
							    "벽", "보", "봉", "비", "빈", "빙", "사", "산", "서", "선", 
							    "설", "성", "생", "소", "손", "송", "수", "숙", "순", "시", 
							    "신", "씨", "아", "안", "약", "양", "언", "연", "염", "영", 
							    "예", "옥", "요", "용", "우", "운", "원", "월", "유", "윤", 
							    "율", "은", "을", "음", "이", "인", "정", "주", "진", "청", 
							    "채", "초", "춘", "하", "향", "혜", "홍", "후", "화", "희",  
		                        "리리", "미미", "보보", "빙빙", "산산", "소소", "영영", "가연", "보연", "수연", 
							    "옥연", "유연", "서아", "월아", "주아", "초아", "백란", "설란", "단하", "설하", 
							    "청하", "소희", "연희", "소민", "연화", "천화", "서련", "수련", "초련", "예린", 
							    "혜린", "예령", "하령", "채경", "지약", "용녀", "설옥", "소옥", "사월", "유월"  
							  };
		
		
		// EX) { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ... 39 } <- TOTAL 40개 (ARRAY에서 [성], [이름]을 늘릴 때마다 동일한 갯수로 설정하시면 됩니다.)
		int 성명_시작 = 0;   // 배열의 FIRST NUMBER [성, 이름 시작]
		int 성_끝 = 131;  // 배열의 LAST NUMBER [성]
		
		int 명_남 = 159;  // 배열의 LAST NUMBER [이름]
        int 명_여 = 119;  // 배열의 LAST NUMBER [이름]

	// ===================================================================================================================================
		
	const int KEY = pk::hash("무장가차");
		
	class Main
	{
		pk::building@ building_;
		pk::district@ district_;
		pk::person@ kunshu_;
		pk::person@ new_face_;
		pk::person@ Opponent_;
		pk::person@ person_2 = pk::get_person(무장_문관);
		pk::force@ force_;
		pk::city@ city_;
		uint16 building_gold;
		string kunshu_name;
		string newface_name;
		string Opponent_name;
		array<pk::person@> person_array;
		pk::random random(pk::rand());          // random 함수

		Main()
		{
			pk::menu_item item;
			item.menu = 102;
			item.pos = 7;
			item.shortcut = "7";
			item.init = pk::building_menu_item_init_t(init);
			item.is_enabled = pk::menu_item_is_enabled_t(isEnabled);
			item.get_text = pk::menu_item_get_text_t(getText);
			item.get_desc = pk::menu_item_get_desc_t(getDesc);
			item.handler = pk::menu_item_handler_t(handler);
			pk::add_menu_item(item);
			add_menu_Gachasetting();                        //쉬프트우클릭설정메뉴
			pk::bind(102, pk::trigger102_t(시나리오시작_설정));   //시나리오시작시 설정메뉴불러오기
		}
		
		// 시나리오시작시 설정메뉴
		void 시나리오시작_설정()
		{
			if (pk::get_scenario().loaded) return;
			if (pk::choose(pk::encode("무장가차 스크립트를 설정하시겠습니까?"), { pk::encode("예"), pk::encode("아니오") }) == 0)
            {
                handler_GachaSetting();
            }
		}

		void init(pk::building@ building)
		{
			@building_ = @building;
			@force_ = pk::get_force(building.get_force_id());
			@kunshu_ = pk::get_person(force_.kunshu);
			@city_ = pk::building_to_city(building_);
			building_gold = pk::get_gold(building);
		}

		bool isEnabled()
		{
			if (building_gold < 소모금) return false;
            else if (pk::get_district(pk::get_district_id(force_, 1)).ap < 소모행동력) return false;
			return true;
		}
		
		string getText()
		{
			return pk::encode("무장가차");
		}
		
		string getDesc()
		{
			if (building_gold < 소모금)
                return pk::encode(pk::format("금이 부족합니다.(금 {} 필요)", 소모금));
			else if (pk::get_district(pk::get_district_id(force_, 1)).ap < 소모행동력)
                return pk::encode(pk::format("행동력이 부족합니다.(행동력 {} 필요)", 소모행동력));
			else
				return pk::encode("무장을 발탁합니다.");
		}

		bool handler()
		{
			if (pk::choose(pk::encode(pk::format("무장가차를 실행하시겠습니까? \n(금 \x1b[1x{}\x1b[0x 행동력 \x1b[1x{}\x1b[0x 필요)\n", 소모금, 소모행동력)), { pk::encode("예"), pk::encode("아니오") }) == 1)
				return false;
			
			// 금 감소
				pk::play_se(27); //효과음_소모
				pk::add_gold(city_, -소모금, true);
			
			kunshu_name = pk::decode(pk::get_name(kunshu_));			
			

			if (pk::rand_bool(발탁실패확률) or getEmptyPerson() is null)
			{
				pk::message_box(pk::encode("주공, 인재를 수소문 했지만 아무도 찾지 못했습니다."), person_2);
				pk::play_se(3); //효과음_실패1
				pk::message_box(pk::encode("무장 발탁에 실패했습니다."));
				
				// 행동력 감소.
				auto district = pk::get_district(pk::get_district_id(force_, 1));
				district.ap -= 소모행동력;	
			}
			
			else 
			{
				// 난수 ===================================================================================================================
				v = pk::rand(100); // 0-100
				
				// EX등급 \x1b[17x 노란색
				// SSR등급 \x1b[29x 빨간색 	
				// SR등급 \x1b[27x 주황색
				// R등급 \x1b[32x 파란색
				// N등급 \x1b[28x 녹색
				// F등급 \x1b[25x 회색
								
				@new_face_ = getEmptyPerson();
				
				// 성별비율
				if(pk::rand_bool(성별비율)) new_face_.sex = 성별_남;
			    else new_face_.sex = 성별_여;

				if (이름자동)
				{
					new_face_.sei = pk::get_family_name(random(성씨_끝 - 1)).name; // 성
					new_face_.mei = pk::get_family_name(random(성씨_끝 - 1)).name; // 명
				}
								
				// 남녀 이름 ================================================================================================================
				if (이름수동)
				{
					new_face_.sei = pk::encode(sei_[random(성명_시작, 성_끝)]); // 성
					
					if (new_face_.sex == 성별_남)
					new_face_.mei = pk::encode(mei_남[random(성명_시작, 명_남)]);  // 남성 명 
				    
					else
					new_face_.mei = pk::encode(mei_여[random(성명_시작, 명_여)]);  // 여성 명 
				}
				
				// 남녀 초상화 음성 말투 ========================================================================================================
				if (new_face_.sex == 성별_남)
			    {
				    new_face_.face = random(2000, 2088);                 // 남성 초상화 에보니패치 기준
				    new_face_.tone = random(말투_장비, 말투_보통남); 
			        new_face_.voice = random(음성_소심남, 음성_저돌남);
                }
                
                else
 				{
			        new_face_.face = random(2100, 2164);	                 // 여성 초상화 에보니패치 기준
				    new_face_.tone = random(말투_고대만족, 말투_보통녀);
			        new_face_.voice = random(음성_냉정녀, 음성_대담녀);
				}
				
				// 친애무장, 혐오무장 초기화 ======================================================================================================
				for (int i = 0; i < 5; i++)
				{
					new_face_.liked[i] = -1;
					new_face_.disliked[i] = -1;
				}
				
				// 남녀 공통 기본정보 ==========================================================================================================
				new_face_.appearance = pk::get_year();
				new_face_.birth = pk::get_year() - 15 - random(15);                    //나이 (15~30살)
				new_face_.death = pk::min(353, new_face_.birth + 30 + random(60));      //수명 (30~90살)
				new_face_.ketsuen = new_face_.get_id();                                 //혈연
				new_face_.aishou = random(0, 150);                                     //상성
				new_face_.mibun = 신분_일반;                                              //신분
				new_face_.birthplace = random(주_유주, 주_남중);
				new_face_.wadai = random(화제_고사, 화제_시절);
				new_face_.giri = random(의리_매우낮음, 의리_매우높음);
				new_face_.ambition = random(야망_매우낮음, 야망_매우높음);
				new_face_.promotion = random(기용_능력, 기용_임의);
				new_face_.character = random(성격_소심, 성격_저돌);
				new_face_.kanshitsu = random(한실_무시, 한실_중시);
				new_face_.strategic_tendency = random(전략경향_중화통일, 전략경향_현상유지);
				new_face_.local_affiliation = random(지역집착_지역중시, 지역집착_지역무시);
				
				// 화술 획득 확률 =============================================================================================================
				int wajutsu_daikatsu_0 = 50;
				int wajutsu_kiben_0 = 50;
				int wajutsu_mushi_0 = 50;
				int wajutsu_chinsei_0 = 50;
				int wajutsu_gyakujou_0 = 50;
						
				if (pk::rand_bool(wajutsu_daikatsu_0))
				{
					new_face_.wajutsu_daikatsu = true;
				}
				
				if (pk::rand_bool(wajutsu_kiben_0))
				{
					new_face_.wajutsu_kiben = true;
				}
				
				if (pk::rand_bool(wajutsu_mushi_0))
				{
					new_face_.wajutsu_mushi = true;
				}
				
				if (pk::rand_bool(wajutsu_chinsei_0))
				{
					new_face_.wajutsu_chinsei = true;
				}
				
				if (pk::rand_bool(wajutsu_gyakujou_0))
				{
					new_face_.wajutsu_gyakujou = true;
				}
				
				// 발탁 이벤트 ==============================================================================================================
				/**
				    기본설정 v값 = 4, 12, 24, 40, 64  
				**/
				
				if (일반특별전환 == 1)
				{
				    특별발탁();  // 특별발탁
					
					newface_name = pk::decode(pk::get_name(new_face_));	
				    new_face_.update();
					
					if (이벤트실행여부 == 1)
					{
					    pk::scene(pk::scene_t(Event_특별발탁1)); // 일기토설전이벤트 실행
					}
					
					else
					{	
			            pk::scene(pk::scene_t(Event_특별발탁2)); // 일기토설전이벤트 없음
					}
				}
				
				else
				{
				    일반발탁();  // 일반발탁
					
					newface_name = pk::decode(pk::get_name(new_face_));	
				    new_face_.update();
					
					if (이벤트실행여부 == 1)
					{
					    pk::scene(pk::scene_t(Event_일반발탁1)); // 일기토설전이벤트 실행
					}
					
					else
					{	
			            pk::scene(pk::scene_t(Event_일반발탁2)); // 일기토설전이벤트 없음
					}
					
				}
			}	

			return true;
		}
		
		void 특별발탁()
		{
			// 자(등급표시) ==============================================================================================================
			/**  
				기본설정 v값 = 4, 12, 24, 40, 64  
			**/
				
			if (v < 4)
			{
				new_face_.azana = pk::u8encode("EX");
			}
				
			else if (v < 12)
			{
				new_face_.azana = pk::u8encode("SSR");
			}
				
			else if (v < 24)
			{
			new_face_.azana = pk::u8encode("SR");
			}
				
			else if (v < 40)
			{
				new_face_.azana = pk::u8encode("R");
			}
			
			else if (v < 64)
			{
				new_face_.azana = pk::u8encode("N");
			}
			
			else 
			{
				new_face_.azana = pk::u8encode("F");
			}
					
			// 병종 적성 ================================================================================================================
			/**  
			    기본설정 v값 = 12, 64  
			**/
			
			// 0-EX등급_무관형, 1-EX등급_문관형, 2-SSR등급_무관형, 3-SSR등급_문관형
			if (v < 12)
			{
			    new_face_.tekisei[병종_기병] = random(1, 3);
			    new_face_.tekisei[병종_창병] = random(1, 3);
			    new_face_.tekisei[병종_극병] = random(1, 3);
			    new_face_.tekisei[병종_노병] = random(1, 3);
				new_face_.tekisei[병종_병기] = random(1, 3);
				new_face_.tekisei[병종_수군] = random(1, 3);
			}				
				
			// 4-SR등급_무관형, 5-SR등급_문관형, 6-R등급_무관형, 7-R등급_문관형, 8-N등급_올랜덤
			else if (v < 64)
			{
				new_face_.tekisei[병종_기병] = random(0, 2);
				new_face_.tekisei[병종_창병] = random(0, 2);
				new_face_.tekisei[병종_극병] = random(0, 2);
				new_face_.tekisei[병종_노병] = random(0, 2);
				new_face_.tekisei[병종_병기] = random(0, 2);
				new_face_.tekisei[병종_수군] = random(0, 2);
			}		
				
			// 9-F등급_폐급
			else
			{
				new_face_.tekisei[병종_기병] = random(0, 1);
				new_face_.tekisei[병종_창병] = random(0, 1);
				new_face_.tekisei[병종_극병] = random(0, 1);
				new_face_.tekisei[병종_노병] = random(0, 1);
				new_face_.tekisei[병종_병기] = random(0, 1);
				new_face_.tekisei[병종_수군] = random(0, 1);
			}		
				
			// 특기 설정 ================================================================================================================
			/**  
			    기본설정 v값 = 2, 4, 8, 12, 18, 24, 32, 40, 64  
			**/
				
			// 0-EX등급_무관형			
			if (v < 2)
			{
				new_face_.skill = 사기특기_무관[pk::rand(사기특기_무관.length)];
			}
				
			// 1-EX등급_문관형
			else if (v < 4)
			{
				new_face_.skill = 사기특기_문관[pk::rand(사기특기_문관.length)];
			}
				
			// 2-SSR등급_무관형
			else if (v < 8)
			{
				new_face_.skill = 고급특기_무관[pk::rand(고급특기_무관.length)];
			}
				
			// 3-SSR등급_문관형	
			else if (v < 12)
			{
				new_face_.skill = 고급특기_문관[pk::rand(고급특기_문관.length)];
			}
				
			// 4-SR등급_무관형
			else if (v < 18)
			{
				new_face_.skill = 중급특기_무관[pk::rand(중급특기_무관.length)];
			}
				
			// 5-SR등급_문관형
			else if (v < 24)
			{
				new_face_.skill = 중급특기_문관[pk::rand(중급특기_문관.length)];
			}
				
			// 6-R등급_무관형
			else if (v < 32)
			{
				new_face_.skill = 중급특기_무관[pk::rand(중급특기_무관.length)];
			}
				
			// 7-R등급_문관형
			else if (v < 40)
			{
				new_face_.skill = 중급특기_문관[pk::rand(중급특기_문관.length)];
			}
				
			// 8-N등급_올랜덤	
			else if (v < 64)
			{
				new_face_.skill = random(특기_비장, 특기_내조);
			}
				
			// 9-F등급_폐급
			else
			{
				new_face_.skill = 하급특기_범용[pk::rand(하급특기_범용.length)];
			}
								
			// 무장 능력 ===============================================================================================================
			/**  
			    기본설정 v값 = 2, 4, 8, 12, 18, 24, 32, 40, 64  
			**/
				
			for (int i = 0; i < 무장능력_끝; i++)
			{
				// 0-EX등급_무관형, 1-EX등급_문관형, 2-SSR등급_무관형, 3-SSR등급_문관형, 4-SR등급_무관형, 5-SR등급_문관형, 6-R등급_무관형, 7-R등급_문관형, 8-N등급_올랜덤, 9-F등급_폐급 
				
				// 0-EX등급_무관형
				if (v < 2)
				{
					if (i == 무장능력_통솔)
					{
						new_face_.base_stat[i] = random(min_stat_EX등급_무관형_통솔, max_stat_EX등급_무관형_통솔);
					}
						
					else if (i == 무장능력_무력)
					{
						new_face_.base_stat[i] = random(min_stat_EX등급_무관형_무력, max_stat_EX등급_무관형_무력);
					}
					
					else if (i == 무장능력_지력)
					{
						new_face_.base_stat[i] = random(min_stat_EX등급_무관형_지력, max_stat_EX등급_무관형_지력);
					}
						
					else if (i == 무장능력_정치)
					{
						new_face_.base_stat[i] = random(min_stat_EX등급_무관형_정치, max_stat_EX등급_무관형_정치);
					}
					
					else if (i == 무장능력_매력)
					{
						new_face_.base_stat[i] = random(min_stat_EX등급_무관형_매력, max_stat_EX등급_무관형_매력);
					}
				}

                // 1-EX등급_문관형
                else if (v < 4)
				{
					if (i == 무장능력_통솔)
					{
						new_face_.base_stat[i] = random(min_stat_EX등급_문관형_통솔, max_stat_EX등급_문관형_통솔);
					}
					
					else if (i == 무장능력_무력)
					{
						new_face_.base_stat[i] = random(min_stat_EX등급_문관형_무력, max_stat_EX등급_문관형_무력);
					}
				
					else if (i == 무장능력_지력)
					{
						new_face_.base_stat[i] = random(min_stat_EX등급_문관형_지력, max_stat_EX등급_문관형_지력);
					}
						
					else if (i == 무장능력_정치)
					{
						new_face_.base_stat[i] = random(min_stat_EX등급_문관형_정치, max_stat_EX등급_문관형_정치);
					}
						
					else if (i == 무장능력_매력)
					{
						new_face_.base_stat[i] = random(min_stat_EX등급_문관형_매력, max_stat_EX등급_문관형_매력);
					}
				}

				// 2-SSR등급_무관형
				else if (v < 8)
				{
					if (i == 무장능력_통솔)
					{
						new_face_.base_stat[i] = random(min_stat_SSR등급_무관형_통솔, max_stat_SSR등급_무관형_통솔);
					}
					
					else if (i == 무장능력_무력)
					{
						new_face_.base_stat[i] = random(min_stat_SSR등급_무관형_무력, max_stat_SSR등급_무관형_무력);
					}
					
					else if (i == 무장능력_지력)
					{
						new_face_.base_stat[i] = random(min_stat_SSR등급_무관형_지력, max_stat_SSR등급_무관형_지력);
					}
						
					else if (i == 무장능력_정치)
					{
						new_face_.base_stat[i] = random(min_stat_SSR등급_무관형_정치, max_stat_SSR등급_무관형_정치);
					}
						
					else if (i == 무장능력_매력)
					{
						new_face_.base_stat[i] = random(min_stat_SSR등급_무관형_매력, max_stat_SSR등급_무관형_매력);
					}
				} 
					
				// 3-SSR등급_문관형
				else if (v < 12)
				{
					if (i == 무장능력_통솔)
					{
						new_face_.base_stat[i] = random(min_stat_SSR등급_문관형_통솔, max_stat_SSR등급_문관형_통솔);
					}
					
					else if (i == 무장능력_무력)
					{
						new_face_.base_stat[i] = random(min_stat_SSR등급_문관형_무력, max_stat_SSR등급_문관형_무력);
					}
					
					else if (i == 무장능력_지력)
					{
						new_face_.base_stat[i] = random(min_stat_SSR등급_문관형_지력, max_stat_SSR등급_문관형_지력);
					}
					
					else if (i == 무장능력_정치)
					{
						new_face_.base_stat[i] = random(min_stat_SSR등급_문관형_정치, max_stat_SSR등급_문관형_정치);
					}
					
					else if (i == 무장능력_매력)
					{
						new_face_.base_stat[i] = random(min_stat_SSR등급_문관형_매력, max_stat_SSR등급_문관형_매력);
					}
				} 
					
                // 4-SR등급_무관형
				else if (v < 18)
				{
					if (i == 무장능력_통솔)
					{
						new_face_.base_stat[i] = random(min_stat_SR등급_무관형_통솔, max_stat_SR등급_무관형_통솔);
					}
						
					else if (i == 무장능력_무력)
					{
						new_face_.base_stat[i] = random(min_stat_SR등급_무관형_무력, max_stat_SR등급_무관형_무력);
					}
					
					else if (i == 무장능력_지력)
					{
						new_face_.base_stat[i] = random(min_stat_SR등급_무관형_지력, max_stat_SR등급_무관형_지력);
					}
					
					else if (i == 무장능력_정치)
					{
						new_face_.base_stat[i] = random(min_stat_SR등급_무관형_정치, max_stat_SR등급_무관형_정치);
					}
					
					else if (i == 무장능력_매력)
					{
						new_face_.base_stat[i] = random(min_stat_SR등급_무관형_매력, max_stat_SR등급_무관형_매력);
					}
				} 

				// 5-SR등급_문관형
				else if (v < 24)
				{
					if (i == 무장능력_통솔)
					{
						new_face_.base_stat[i] = random(min_stat_SR등급_문관형_통솔, max_stat_SR등급_문관형_통솔);
					}
					
					else if (i == 무장능력_무력)
					{
						new_face_.base_stat[i] = random(min_stat_SR등급_문관형_무력, max_stat_SR등급_문관형_무력);
					}
					
					else if (i == 무장능력_지력)
					{
						new_face_.base_stat[i] = random(min_stat_SR등급_문관형_지력, max_stat_SR등급_문관형_지력);
					}
					
					else if (i == 무장능력_정치)
					{
						new_face_.base_stat[i] = random(min_stat_SR등급_문관형_정치, max_stat_SR등급_문관형_정치);
					}
						
					else if (i == 무장능력_매력)
					{
						new_face_.base_stat[i] = random(min_stat_SR등급_문관형_매력, max_stat_SR등급_문관형_매력);
					}
				} 
					
				// 6-R등급_무관형
				else if (v < 32)
				{
					if (i == 무장능력_통솔)
					{
						new_face_.base_stat[i] = random(min_stat_R등급_무관형_통솔, max_stat_R등급_무관형_통솔);
					}
						
					else if (i == 무장능력_무력)
					{
						new_face_.base_stat[i] = random(min_stat_R등급_무관형_무력, max_stat_R등급_무관형_무력);
					}
					
					else if (i == 무장능력_지력)
					{
						new_face_.base_stat[i] = random(min_stat_R등급_무관형_지력, max_stat_R등급_무관형_지력);
					}
					
					else if (i == 무장능력_정치)
					{
						new_face_.base_stat[i] = random(min_stat_R등급_무관형_정치, max_stat_R등급_무관형_정치);
					}
					
					else if (i == 무장능력_매력)
					{
						new_face_.base_stat[i] = random(min_stat_R등급_무관형_매력, max_stat_R등급_무관형_매력);
					}
				} 
					
				// 7-R등급_문관형
				else if (v < 40)
				{
					if (i == 무장능력_통솔)
					{
						new_face_.base_stat[i] = random(min_stat_R등급_문관형_통솔, max_stat_R등급_문관형_통솔);
					}
					
					else if (i == 무장능력_무력)
					{
						new_face_.base_stat[i] = random(min_stat_R등급_문관형_무력, max_stat_R등급_문관형_무력);
					}
					
					else if (i == 무장능력_지력)
					{
						new_face_.base_stat[i] = random(min_stat_R등급_문관형_지력, max_stat_R등급_문관형_지력);
					}
					
					else if (i == 무장능력_정치)
					{
						new_face_.base_stat[i] = random(min_stat_R등급_문관형_정치, max_stat_R등급_문관형_정치);
					}
					
					else if (i == 무장능력_매력)
					{
						new_face_.base_stat[i] = random(min_stat_R등급_문관형_매력, max_stat_R등급_문관형_매력);
					}
				} 
					
				// 8-N등급_올랜덤
				else if (v < 64)
				{
					if (i == 무장능력_통솔)
					{
						new_face_.base_stat[i] = random(min_stat_N등급_올랜덤_통솔, max_stat_N등급_올랜덤_통솔);
					}
					
					else if (i == 무장능력_무력)
					{
						new_face_.base_stat[i] = random(min_stat_N등급_올랜덤_무력, max_stat_N등급_올랜덤_무력);
					}
					
					else if (i == 무장능력_지력)
					{
						new_face_.base_stat[i] = random(min_stat_N등급_올랜덤_지력, max_stat_N등급_올랜덤_지력);
					}
					
					else if (i == 무장능력_정치)
					{
						new_face_.base_stat[i] = random(min_stat_N등급_올랜덤_정치, max_stat_N등급_올랜덤_정치);
					}
					
					else if (i == 무장능력_매력)
					{
						new_face_.base_stat[i] = random(min_stat_N등급_올랜덤_매력, max_stat_N등급_올랜덤_매력);
					}
				} 
				
				// 9-F등급_폐급
				else
				{
					if (i == 무장능력_통솔)
					{
						new_face_.base_stat[i] = random(min_stat_F등급_폐급_통솔, max_stat_F등급_폐급_통솔);
					}
					
					else if (i == 무장능력_무력)
					{
						new_face_.base_stat[i] = random(min_stat_F등급_폐급_무력, max_stat_F등급_폐급_무력);
					}
					
					else if (i == 무장능력_지력)
					{
						new_face_.base_stat[i] = random(min_stat_F등급_폐급_지력, max_stat_F등급_폐급_지력);
					}
					
					else if (i == 무장능력_정치)
					{
						new_face_.base_stat[i] = random(min_stat_F등급_폐급_정치, max_stat_F등급_폐급_정치);
					}
					
					else if (i == 무장능력_매력)
					{
						new_face_.base_stat[i] = random(min_stat_F등급_폐급_매력, max_stat_F등급_폐급_매력);
					}
				} 
					
					new_face_.stat_aging[i] = random(능력성장_초지속형, 능력성장_장비형);
			}
				
				// 남녀 조형 ===============================================================================================================
				/**  
				    기본설정 v값 = 2, 4, 8, 12, 18, 24, 32, 40, 64  
				**/
				
				// 남성 조형
				if (new_face_.sex == 성별_남)
				{
				    // 0-EX등급_무관형 (백)
				    if (v < 2)
				    {
					    new_face_.skeleton = 1;
					    new_face_.body[0] = random(110,112); // 투구
					    new_face_.body[1] = random(110,112); // 얼굴
					    new_face_.body[2] = random(110,112); // 상체
					    new_face_.body[3] = random(110,112); // 망토
					    new_face_.body[4] = random(110,112); // 팔
					    new_face_.body[5] = random(110,112); // 다리
				    }
				
				    // 1-EX등급_문관형 (백)
				    else if (v < 4)
				    {
					    new_face_.skeleton = 1;
					    new_face_.body[0] = random(115,116); // 투구
					    new_face_.body[1] = random(115,116); // 얼굴
					    new_face_.body[2] = random(115,116); // 상체
					    new_face_.body[3] = random(115,116); // 망토
					    new_face_.body[4] = random(115,116); // 팔
					    new_face_.body[5] = random(115,116); // 다리
				    }
				
				    // 2-SSR등급_무관형 (흑)
				    else if (v < 8)
				    {
					    new_face_.skeleton = 1;
					    new_face_.body[0] = random(92,94);  // 투구
					    new_face_.body[1] = random(92,94);  // 얼굴
					    new_face_.body[2] = random(92,94);  // 상체
					    new_face_.body[3] = random(92,94);  // 망토
					    new_face_.body[4] = random(92,94);  // 팔
					    new_face_.body[5] = random(92,94);  // 다리
				    }
				
				   // 3-SSR등급_문관형 (흑)
				    else if (v < 12)
				    {
					    new_face_.skeleton = 1;
					    new_face_.body[0] = random(97,98);  // 투구
					    new_face_.body[1] = random(97,98);  // 얼굴
				    	new_face_.body[2] = random(97,98);  // 상체
					    new_face_.body[3] = random(97,98);  // 망토
					    new_face_.body[4] = random(97,98);  // 팔
					    new_face_.body[5] = random(97,98);  // 다리
			    	}
				
				    // 4-SR등급_무관형 (적)
				    else if (v < 18)
				    {
				    	new_face_.skeleton = 1;
				    	new_face_.body[0] = random(74,76);  // 투구
				    	new_face_.body[1] = random(74,76);  // 얼굴
				    	new_face_.body[2] = random(74,76);  // 상체
				    	new_face_.body[3] = random(74,76);  // 망토
				    	new_face_.body[4] = random(74,76);  // 팔
				    	new_face_.body[5] = random(74,76);  // 다리
			    	}
				
				    // 5-SR등급_문관형 (적)
				    else if (v < 24)
				    {
				    	new_face_.skeleton = 1;
				    	new_face_.body[0] = random(79,80);  // 투구
				    	new_face_.body[1] = random(79,80);  // 얼굴
				    	new_face_.body[2] = random(79,80);  // 상체
				    	new_face_.body[3] = random(79,80);  // 망토
				    	new_face_.body[4] = random(79,80);  // 팔
				    	new_face_.body[5] = random(79,80);  // 다리
				    }
				
				    // 6-R등급_무관형 (청)
				    else if (v < 32)
				    {
				    	new_face_.skeleton = 1;
				    	new_face_.body[0] = random(83,85);  // 투구
				    	new_face_.body[1] = random(83,85);  // 얼굴
				    	new_face_.body[2] = random(83,85);  // 상체
				    	new_face_.body[3] = random(83,85);  // 망토
				    	new_face_.body[4] = random(83,85);  // 팔
				    	new_face_.body[5] = random(83,85);  // 다리
				    }
				
				    // 7-R등급_문관형 (청)
				    else if (v < 40)
				    {
				    	new_face_.skeleton = 1;
				    	new_face_.body[0] = random(88,89);  // 투구
				     	new_face_.body[1] = random(88,89);  // 얼굴
				    	new_face_.body[2] = random(88,89);  // 상체
				    	new_face_.body[3] = random(88,89);  // 망토
				    	new_face_.body[4] = random(88,89);  // 팔
				    	new_face_.body[5] = random(88,89);  // 다리
				    }
				
				    // 8-N등급_올랜덤 (녹)
				    else if (v < 64)
				    {
				    	new_face_.skeleton = 1;
				    	new_face_.body[0] = random(119,121);  // 투구
				      	new_face_.body[1] = random(119,121);  // 얼굴
					    new_face_.body[2] = random(119,121);  // 상체
				    	new_face_.body[3] = random(119,121);  // 망토
				    	new_face_.body[4] = random(119,121);  // 팔
					    new_face_.body[5] = random(119,121);  // 다리
				    }
				
				    // 9-F등급_폐급 (황)
				    else 
				    {
				    	new_face_.skeleton = 1;
				    	new_face_.body[0] = random(101,103); // 투구
				    	new_face_.body[1] = random(101,103); // 얼굴
				    	new_face_.body[2] = random(101,103); // 상체
				    	new_face_.body[3] = random(101,103); // 망토
				    	new_face_.body[4] = random(101,103); // 팔
				    	new_face_.body[5] = random(101,103); // 다리
				    }
				}
				
				// 여성 조형
				else
				{
				// 여성 조형
				    // 0-EX등급_무관형 (백)
				    if (v < 2)
				    {
					    new_face_.skeleton = 1;
					    new_face_.body[0] = random(113,114); // 투구
					    new_face_.body[1] = random(113,114); // 얼굴
					    new_face_.body[2] = random(113,114); // 상체
					    new_face_.body[3] = random(113,114); // 망토
					    new_face_.body[4] = random(113,114); // 팔
					    new_face_.body[5] = random(113,114); // 다리
				    }
				
				    // 1-EX등급_문관형 (백)
				    else if (v < 4)
				    {
					    new_face_.skeleton = 1;
					    new_face_.body[0] = random(117,118); // 투구
					    new_face_.body[1] = random(117,118); // 얼굴
					    new_face_.body[2] = random(117,118); // 상체
					    new_face_.body[3] = random(117,118); // 망토
					    new_face_.body[4] = random(117,118); // 팔
					    new_face_.body[5] = random(117,118); // 다리
				    }
				
				    // 2-SSR등급_무관형 (흑)
				    else if (v < 8)
				    {
					    new_face_.skeleton = 1;
					    new_face_.body[0] = random(95,96);  // 투구
					    new_face_.body[1] = random(95,96);  // 얼굴
					    new_face_.body[2] = random(95,96);  // 상체
					    new_face_.body[3] = random(95,96);  // 망토
					    new_face_.body[4] = random(95,96);  // 팔
					    new_face_.body[5] = random(95,96);  // 다리
				    }
				
				   // 3-SSR등급_문관형 (흑)
				    else if (v < 12)
				    {
					    new_face_.skeleton = 1;
					    new_face_.body[0] = random(99,100);  // 투구
					    new_face_.body[1] = random(99,100);  // 얼굴
				    	new_face_.body[2] = random(99,100);  // 상체
					    new_face_.body[3] = random(99,100);  // 망토
					    new_face_.body[4] = random(99,100);  // 팔
					    new_face_.body[5] = random(99,100);  // 다리
			    	}
				
				    // 4-SR등급_무관형 (적)
				    else if (v < 18)
				    {
				    	new_face_.skeleton = 1;
				    	new_face_.body[0] = random(77,78);  // 투구
				    	new_face_.body[1] = random(77,78);  // 얼굴
				    	new_face_.body[2] = random(77,78);  // 상체
				    	new_face_.body[3] = random(77,78);  // 망토
				    	new_face_.body[4] = random(77,78);  // 팔
				    	new_face_.body[5] = random(77,78);  // 다리
			    	}
				
				    // 5-SR등급_문관형 (적)
				    else if (v < 24)
				    {
				    	new_face_.skeleton = 1;
				    	new_face_.body[0] = random(81,82);  // 투구
				    	new_face_.body[1] = random(81,82);  // 얼굴
				    	new_face_.body[2] = random(81,82);  // 상체
				    	new_face_.body[3] = random(81,82);  // 망토
				    	new_face_.body[4] = random(81,82);  // 팔
				    	new_face_.body[5] = random(81,82);  // 다리
				    }
				
				    // 6-R등급_무관형 (청)
				    else if (v < 32)
				    {
				    	new_face_.skeleton = 1;
				    	new_face_.body[0] = random(86,87);  // 투구
				    	new_face_.body[1] = random(86,87);  // 얼굴
				    	new_face_.body[2] = random(86,87);  // 상체
				    	new_face_.body[3] = random(86,87);  // 망토
				    	new_face_.body[4] = random(86,87);  // 팔
				    	new_face_.body[5] = random(86,87);  // 다리
				    }
				
				    // 7-R등급_문관형 (청)
				    else if (v < 40)
				    {
				    	new_face_.skeleton = 1;
				    	new_face_.body[0] = random(90,91);  // 투구
				     	new_face_.body[1] = random(90,91);  // 얼굴
				    	new_face_.body[2] = random(90,91);  // 상체
				    	new_face_.body[3] = random(90,91);  // 망토
				    	new_face_.body[4] = random(90,91);  // 팔
				    	new_face_.body[5] = random(90,91);  // 다리
				    }
				
				    // 8-N등급_올랜덤 (녹)
				    else if (v < 64)
				    {
				    	new_face_.skeleton = 1;
				    	new_face_.body[0] = random(126,127);  // 투구
				      	new_face_.body[1] = random(126,127);  // 얼굴
					    new_face_.body[2] = random(126,127);  // 상체
				    	new_face_.body[3] = random(126,127);  // 망토
				    	new_face_.body[4] = random(126,127);  // 팔
					    new_face_.body[5] = random(126,127);  // 다리
				    }
				
				    // 9-F등급_폐급 (황)
				    else 
				    {
				    	new_face_.skeleton = 1;
				    	new_face_.body[0] = random(104,105); // 투구
				    	new_face_.body[1] = random(104,105); // 얼굴
				    	new_face_.body[2] = random(104,105); // 상체
				    	new_face_.body[3] = random(104,105); // 망토
				    	new_face_.body[4] = random(104,105); // 팔
				    	new_face_.body[5] = random(104,105); // 다리
				    }
				}
		    	
		}
        
        void 일반발탁()
		{
			// 자(등급표시) ==============================================================================================================
			/**  
				기본설정 v값 = 4, 20, 52
			**/
			
			if (v < 4)
			{
			new_face_.azana = pk::u8encode("SR");
			}
				
			else if (v < 20)
			{
				new_face_.azana = pk::u8encode("R");
			}
			
			else if (v < 52)
			{
				new_face_.azana = pk::u8encode("N");
			}
			
			else 
			{
				new_face_.azana = pk::u8encode("F");
			}
					
			// 병종 적성 ================================================================================================================
			/**  
			    기본설정 v값 = 52 
			**/
			
			// 4-SR등급_무관형, 5-SR등급_문관형, 6-R등급_무관형, 7-R등급_문관형, 8-N등급_올랜덤
			if (v < 52)
			{
				new_face_.tekisei[병종_기병] = random(0, 2);
				new_face_.tekisei[병종_창병] = random(0, 2);
				new_face_.tekisei[병종_극병] = random(0, 2);
				new_face_.tekisei[병종_노병] = random(0, 2);
				new_face_.tekisei[병종_병기] = random(0, 2);
				new_face_.tekisei[병종_수군] = random(0, 2);
			}		
				
			// 9-F등급_폐급
			else
			{
				new_face_.tekisei[병종_기병] = random(0, 1);
				new_face_.tekisei[병종_창병] = random(0, 1);
				new_face_.tekisei[병종_극병] = random(0, 1);
				new_face_.tekisei[병종_노병] = random(0, 1);
				new_face_.tekisei[병종_병기] = random(0, 1);
				new_face_.tekisei[병종_수군] = random(0, 1);
			}		
				
			// 특기 설정 ================================================================================================================
			/**  
			    기본설정 v값 = 2, 4, 12, 20, 52
			**/
				
			// 4-SR등급_무관형
			if (v < 2)
			{
				new_face_.skill = 중급특기_무관[pk::rand(중급특기_무관.length)];
			}
				
			// 5-SR등급_문관형
			else if (v < 4)
			{
				new_face_.skill = 중급특기_문관[pk::rand(중급특기_문관.length)];
			}
				
			// 6-R등급_무관형
			else if (v < 12)
			{
				new_face_.skill = 중급특기_무관[pk::rand(중급특기_무관.length)];
			}
				
			// 7-R등급_문관형
			else if (v < 20)
			{
				new_face_.skill = 중급특기_문관[pk::rand(중급특기_문관.length)];
			}
				
			// 8-N등급_올랜덤	
			else if (v < 52)
			{
				new_face_.skill = random(특기_비장, 특기_내조);
			}
				
			// 9-F등급_폐급
			else
			{
				new_face_.skill = 하급특기_범용[pk::rand(하급특기_범용.length)];
			}
								
			// 무장 능력 ===============================================================================================================
			/**  
			    기본설정 v값 = 2, 4, 12, 20, 52
			**/
				
			for (int i = 0; i < 무장능력_끝; i++)
			{
				// 0-EX등급_무관형, 1-EX등급_문관형, 2-SSR등급_무관형, 3-SSR등급_문관형, 4-SR등급_무관형, 5-SR등급_문관형, 6-R등급_무관형, 7-R등급_문관형, 8-N등급_올랜덤, 9-F등급_폐급 
					
                // 4-SR등급_무관형
				if (v < 2)
				{
					if (i == 무장능력_통솔)
					{
						new_face_.base_stat[i] = random(min_stat_SR등급_무관형_통솔, max_stat_SR등급_무관형_통솔);
					}
						
					else if (i == 무장능력_무력)
					{
						new_face_.base_stat[i] = random(min_stat_SR등급_무관형_무력, max_stat_SR등급_무관형_무력);
					}
					
					else if (i == 무장능력_지력)
					{
						new_face_.base_stat[i] = random(min_stat_SR등급_무관형_지력, max_stat_SR등급_무관형_지력);
					}
					
					else if (i == 무장능력_정치)
					{
						new_face_.base_stat[i] = random(min_stat_SR등급_무관형_정치, max_stat_SR등급_무관형_정치);
					}
					
					else if (i == 무장능력_매력)
					{
						new_face_.base_stat[i] = random(min_stat_SR등급_무관형_매력, max_stat_SR등급_무관형_매력);
					}
				} 

				// 5-SR등급_문관형
				else if (v < 4)
				{
					if (i == 무장능력_통솔)
					{
						new_face_.base_stat[i] = random(min_stat_SR등급_문관형_통솔, max_stat_SR등급_문관형_통솔);
					}
					
					else if (i == 무장능력_무력)
					{
						new_face_.base_stat[i] = random(min_stat_SR등급_문관형_무력, max_stat_SR등급_문관형_무력);
					}
					
					else if (i == 무장능력_지력)
					{
						new_face_.base_stat[i] = random(min_stat_SR등급_문관형_지력, max_stat_SR등급_문관형_지력);
					}
					
					else if (i == 무장능력_정치)
					{
						new_face_.base_stat[i] = random(min_stat_SR등급_문관형_정치, max_stat_SR등급_문관형_정치);
					}
						
					else if (i == 무장능력_매력)
					{
						new_face_.base_stat[i] = random(min_stat_SR등급_문관형_매력, max_stat_SR등급_문관형_매력);
					}
				} 
					
				// 6-R등급_무관형
				else if (v < 12)
				{
					if (i == 무장능력_통솔)
					{
						new_face_.base_stat[i] = random(min_stat_R등급_무관형_통솔, max_stat_R등급_무관형_통솔);
					}
						
					else if (i == 무장능력_무력)
					{
						new_face_.base_stat[i] = random(min_stat_R등급_무관형_무력, max_stat_R등급_무관형_무력);
					}
					
					else if (i == 무장능력_지력)
					{
						new_face_.base_stat[i] = random(min_stat_R등급_무관형_지력, max_stat_R등급_무관형_지력);
					}
					
					else if (i == 무장능력_정치)
					{
						new_face_.base_stat[i] = random(min_stat_R등급_무관형_정치, max_stat_R등급_무관형_정치);
					}
					
					else if (i == 무장능력_매력)
					{
						new_face_.base_stat[i] = random(min_stat_R등급_무관형_매력, max_stat_R등급_무관형_매력);
					}
				} 
					
				// 7-R등급_문관형
				else if (v < 20)
				{
					if (i == 무장능력_통솔)
					{
						new_face_.base_stat[i] = random(min_stat_R등급_문관형_통솔, max_stat_R등급_문관형_통솔);
					}
					
					else if (i == 무장능력_무력)
					{
						new_face_.base_stat[i] = random(min_stat_R등급_문관형_무력, max_stat_R등급_문관형_무력);
					}
					
					else if (i == 무장능력_지력)
					{
						new_face_.base_stat[i] = random(min_stat_R등급_문관형_지력, max_stat_R등급_문관형_지력);
					}
					
					else if (i == 무장능력_정치)
					{
						new_face_.base_stat[i] = random(min_stat_R등급_문관형_정치, max_stat_R등급_문관형_정치);
					}
					
					else if (i == 무장능력_매력)
					{
						new_face_.base_stat[i] = random(min_stat_R등급_문관형_매력, max_stat_R등급_문관형_매력);
					}
				} 
					
				// 8-N등급_올랜덤
				else if (v < 52)
				{
					if (i == 무장능력_통솔)
					{
						new_face_.base_stat[i] = random(min_stat_N등급_올랜덤_통솔, max_stat_N등급_올랜덤_통솔);
					}
					
					else if (i == 무장능력_무력)
					{
						new_face_.base_stat[i] = random(min_stat_N등급_올랜덤_무력, max_stat_N등급_올랜덤_무력);
					}
					
					else if (i == 무장능력_지력)
					{
						new_face_.base_stat[i] = random(min_stat_N등급_올랜덤_지력, max_stat_N등급_올랜덤_지력);
					}
					
					else if (i == 무장능력_정치)
					{
						new_face_.base_stat[i] = random(min_stat_N등급_올랜덤_정치, max_stat_N등급_올랜덤_정치);
					}
					
					else if (i == 무장능력_매력)
					{
						new_face_.base_stat[i] = random(min_stat_N등급_올랜덤_매력, max_stat_N등급_올랜덤_매력);
					}
				} 
				
				// 9-F등급_폐급
				else
				{
					if (i == 무장능력_통솔)
					{
						new_face_.base_stat[i] = random(min_stat_F등급_폐급_통솔, max_stat_F등급_폐급_통솔);
					}
					
					else if (i == 무장능력_무력)
					{
						new_face_.base_stat[i] = random(min_stat_F등급_폐급_무력, max_stat_F등급_폐급_무력);
					}
					
					else if (i == 무장능력_지력)
					{
						new_face_.base_stat[i] = random(min_stat_F등급_폐급_지력, max_stat_F등급_폐급_지력);
					}
					
					else if (i == 무장능력_정치)
					{
						new_face_.base_stat[i] = random(min_stat_F등급_폐급_정치, max_stat_F등급_폐급_정치);
					}
					
					else if (i == 무장능력_매력)
					{
						new_face_.base_stat[i] = random(min_stat_F등급_폐급_매력, max_stat_F등급_폐급_매력);
					}
				} 
					
					new_face_.stat_aging[i] = random(능력성장_초지속형, 능력성장_장비형);
			}
				
				// 남녀 조형 ===============================================================================================================
				/**  
				    기본설정 v값 = 2, 4, 12, 20, 52
				**/
				
				// 남성 조형
				if (new_face_.sex == 성별_남)
				{
				    // 4-SR등급_무관형 (적)
				    if (v < 2)
				    {
				    	new_face_.skeleton = 1;
				    	new_face_.body[0] = random(74,76);  // 투구
				    	new_face_.body[1] = random(74,76);  // 얼굴
				    	new_face_.body[2] = random(74,76);  // 상체
				    	new_face_.body[3] = random(74,76);  // 망토
				    	new_face_.body[4] = random(74,76);  // 팔
				    	new_face_.body[5] = random(74,76);  // 다리
			    	}
				
				    // 5-SR등급_문관형 (적)
				    else if (v < 4)
				    {
				    	new_face_.skeleton = 1;
				    	new_face_.body[0] = random(79,80);  // 투구
				    	new_face_.body[1] = random(79,80);  // 얼굴
				    	new_face_.body[2] = random(79,80);  // 상체
				    	new_face_.body[3] = random(79,80);  // 망토
				    	new_face_.body[4] = random(79,80);  // 팔
				    	new_face_.body[5] = random(79,80);  // 다리
				    }
				
				    // 6-R등급_무관형 (청)
				    else if (v < 12)
				    {
				    	new_face_.skeleton = 1;
				    	new_face_.body[0] = random(83,85);  // 투구
				    	new_face_.body[1] = random(83,85);  // 얼굴
				    	new_face_.body[2] = random(83,85);  // 상체
				    	new_face_.body[3] = random(83,85);  // 망토
				    	new_face_.body[4] = random(83,85);  // 팔
				    	new_face_.body[5] = random(83,85);  // 다리
				    }
				
				    // 7-R등급_문관형 (청)
				    else if (v < 20)
				    {
				    	new_face_.skeleton = 1;
				    	new_face_.body[0] = random(88,89);  // 투구
				     	new_face_.body[1] = random(88,89);  // 얼굴
				    	new_face_.body[2] = random(88,89);  // 상체
				    	new_face_.body[3] = random(88,89);  // 망토
				    	new_face_.body[4] = random(88,89);  // 팔
				    	new_face_.body[5] = random(88,89);  // 다리
				    }
				
				    // 8-N등급_올랜덤 (녹)
				    else if (v < 52)
				    {
				    	new_face_.skeleton = 1;
				    	new_face_.body[0] = random(119,121);  // 투구
				      	new_face_.body[1] = random(119,121);  // 얼굴
					    new_face_.body[2] = random(119,121);  // 상체
				    	new_face_.body[3] = random(119,121);  // 망토
				    	new_face_.body[4] = random(119,121);  // 팔
					    new_face_.body[5] = random(119,121);  // 다리
				    }
				
				    // 9-F등급_폐급 (황)
				    else 
				    {
				    	new_face_.skeleton = 1;
				    	new_face_.body[0] = random(101,103); // 투구
				    	new_face_.body[1] = random(101,103); // 얼굴
				    	new_face_.body[2] = random(101,103); // 상체
				    	new_face_.body[3] = random(101,103); // 망토
				    	new_face_.body[4] = random(101,103); // 팔
				    	new_face_.body[5] = random(101,103); // 다리
				    }
				}
				
				// 여성 조형
				else
				{
				// 여성 조형
				    
				    // 4-SR등급_무관형 (적)
				    if (v < 2)
				    {
				    	new_face_.skeleton = 1;
				    	new_face_.body[0] = random(77,78);  // 투구
				    	new_face_.body[1] = random(77,78);  // 얼굴
				    	new_face_.body[2] = random(77,78);  // 상체
				    	new_face_.body[3] = random(77,78);  // 망토
				    	new_face_.body[4] = random(77,78);  // 팔
				    	new_face_.body[5] = random(77,78);  // 다리
			    	}
				
				    // 5-SR등급_문관형 (적)
				    else if (v < 4)
				    {
				    	new_face_.skeleton = 1;
				    	new_face_.body[0] = random(81,82);  // 투구
				    	new_face_.body[1] = random(81,82);  // 얼굴
				    	new_face_.body[2] = random(81,82);  // 상체
				    	new_face_.body[3] = random(81,82);  // 망토
				    	new_face_.body[4] = random(81,82);  // 팔
				    	new_face_.body[5] = random(81,82);  // 다리
				    }
				
				    // 6-R등급_무관형 (청)
				    else if (v < 12)
				    {
				    	new_face_.skeleton = 1;
				    	new_face_.body[0] = random(86,87);  // 투구
				    	new_face_.body[1] = random(86,87);  // 얼굴
				    	new_face_.body[2] = random(86,87);  // 상체
				    	new_face_.body[3] = random(86,87);  // 망토
				    	new_face_.body[4] = random(86,87);  // 팔
				    	new_face_.body[5] = random(86,87);  // 다리
				    }
				
				    // 7-R등급_문관형 (청)
				    else if (v < 20)
				    {
				    	new_face_.skeleton = 1;
				    	new_face_.body[0] = random(90,91);  // 투구
				     	new_face_.body[1] = random(90,91);  // 얼굴
				    	new_face_.body[2] = random(90,91);  // 상체
				    	new_face_.body[3] = random(90,91);  // 망토
				    	new_face_.body[4] = random(90,91);  // 팔
				    	new_face_.body[5] = random(90,91);  // 다리
				    }
				
				    // 8-N등급_올랜덤 (녹)
				    else if (v < 52)
				    {
				    	new_face_.skeleton = 1;
				    	new_face_.body[0] = random(126,127);  // 투구
				      	new_face_.body[1] = random(126,127);  // 얼굴
					    new_face_.body[2] = random(126,127);  // 상체
				    	new_face_.body[3] = random(126,127);  // 망토
				    	new_face_.body[4] = random(126,127);  // 팔
					    new_face_.body[5] = random(126,127);  // 다리
				    }
				
				    // 9-F등급_폐급 (황)
				    else 
				    {
				    	new_face_.skeleton = 1;
				    	new_face_.body[0] = random(104,105); // 투구
				    	new_face_.body[1] = random(104,105); // 얼굴
				    	new_face_.body[2] = random(104,105); // 상체
				    	new_face_.body[3] = random(104,105); // 망토
				    	new_face_.body[4] = random(104,105); // 팔
				    	new_face_.body[5] = random(104,105); // 다리
				    }
				}
		    	
		}		
			
		// 특별발탁 이벤트=================================================================================================================
		
		void Event_특별발탁1()  // 일기토설전이벤트 실행
		{
			int result;
			
			pk::message_box(pk::encode(pk::format("주공, \x1b[1x{}\x1b[0x님을 모셔왔습니다.", newface_name)), person_2);
			pk::message_box(pk::encode(pk::format("안녕하십니까. \x1b[1x{}\x1b[0x님을 뵙게 되어 영광입니다.", kunshu_name)), new_face_);
			pk::message_box(pk::encode("이렇게 찾아줘서 고맙네. 앞으로 나를 도와주겠는가?"), kunshu_);
			
			if (v <24)
			{
			    pk::play_se(25); //효과음_기회
		    	pk::fade(255);
		    	pk::background(35); // 전령 보고
			
		    	pk::message_box(pk::encode("그전에 한가지 청을 드려도 되겠습니까?"), new_face_);
		    	pk::message_box(pk::encode("그래 말해보게나."), kunshu_);
				
				// 일기토 설전 선택			
	    		if (new_face_.base_stat[무장능력_무력] >= new_face_.base_stat[무장능력_지력])
			    	{
				    pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x님의 신하들 중 한 분과 일기토로 겨뤄보고 싶습니다.", kunshu_name)), new_face_);
				    pk::message_box(pk::encode(pk::format("저를 꺾으신다면 \x1b[1x{}\x1b[0x님께 충성을 바치도록 하겠습니다.", kunshu_name)), new_face_);
				}
			
				else
				{
			        pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x님의 신하들 중 한 분과 설전으로 겨뤄보고 싶습니다.", kunshu_name)), new_face_);
					pk::message_box(pk::encode(pk::format("저를 꺾으신다면 \x1b[1x{}\x1b[0x님께 충성을 바치도록 하겠습니다.", kunshu_name)), new_face_);
				}
			
				pk::list<pk::person@> Opponent_list = pk::get_person_list(force_, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반));
			
				if (new_face_.base_stat[무장능력_무력] >= new_face_.base_stat[무장능력_지력])
				{   
				    person_array = pk::list_to_array(pk::person_selector(pk::encode("일기토 무장선택"), pk::encode("무장을 선택해 주십시오."), Opponent_list, 1, 1));
				}
			
				else
				{	
				    person_array = pk::list_to_array(pk::person_selector(pk::encode("설전 무장선택"), pk::encode("무장을 선택해 주십시오."), Opponent_list, 1, 1));
				}
			
				@Opponent_ = person_array[0];
				Opponent_name = pk::decode(pk::get_name(Opponent_));
				
				if (kunshu_.get_id() == Opponent_.get_id()) 
				{	
			        pk::message_box(pk::encode("좋다. 내가 직접 상대해주도록 하지."), kunshu_);
				    pk::message_box(pk::encode("직접 상대해주시다니 영광입니다."), new_face_);
				}
			
				else
				{	
			        pk::message_box(pk::encode(pk::format("좋다. \x1b[1x{}\x1b[0x 있는가.", Opponent_name)), kunshu_);
				    pk::message_box(pk::encode("예 주공."), Opponent_);
					pk::message_box(pk::encode("자네가 상대해주도록 하게."), kunshu_);
					pk::message_box(pk::encode("명을 받듭니다."), Opponent_);
				}
			
				if (new_face_.base_stat[무장능력_무력] >= new_face_.base_stat[무장능력_지력]) 
				{
					if (kunshu_.get_id() == Opponent_.get_id()) 
						result = pk::duel(null, null, kunshu_, null, null, new_face_, null, null, pk::is_player_controlled(kunshu_), false, 0, true).first;
					else 
						result = pk::duel(null, null, Opponent_, null, null, new_face_, null, null, pk::is_player_controlled(kunshu_), false, 0, true).first;
				}
				else 
				{
					if (kunshu_.get_id() == Opponent_.get_id()) 
						result = pk::debate(kunshu_, new_face_, pk::is_player_controlled(kunshu_), false, false, true).first;
					else 
						result = pk::debate(Opponent_, new_face_, pk::is_player_controlled(kunshu_), false, false, true).first;
				}
			
				if (result == 0) 
				{
					pk::play_se(12); //효과음_성공4
					pk::background(30); // 충성 맹세
					// EX등급
				    if (v <4)
				    {
					    pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x님을 위해서 충성을 바치겠습니다.", kunshu_name)), new_face_);
					    pk::play_se(22); //효과음_성공3
				        pk::message_box(pk::encode(pk::format("\x1b[17x[EX등급]\x1b[0x 무장 \x1b[17x{}\x1b[0x(이)가 아군으로 합류했습니다.", newface_name)));
				        pk::message_box(pk::encode(pk::format("기교 포인트를 \x1b[17x{}\x1b[0x만큼 획득했습니다.", TP_COST)));
				        pk::add_tp(force_, TP_COST * 2, force_.get_pos());
				    }
					
				    // SSR등급
				    else if (v <12)
				    {
				    	pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x님을 위해서 충성을 바치겠습니다.", kunshu_name)), new_face_);
				    	pk::play_se(10); //효과음_성공2
				        pk::message_box(pk::encode(pk::format("\x1b[29x[SSR등급]\x1b[0x 무장 \x1b[29x{}\x1b[0x(이)가 아군으로 합류했습니다.", newface_name)));
				    }

				    // SR등급
				    else
				    {
			    		pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x님을 위해서 충성을 바치겠습니다.", kunshu_name)), new_face_);
			    		pk::play_se(10); //효과음_성공2
			    	    pk::message_box(pk::encode(pk::format("\x1b[27x[SR등급]\x1b[0x 무장 \x1b[27x{}\x1b[0x(이)가 아군으로 합류했습니다.", newface_name)));	
				    }
				
						auto district = pk::get_district(pk::get_district_id(force_, 1));
				        district.ap -= 소모행동력;	
				        pk::sort(pk::person::type_id);
				        pk::move(new_face_, building_);
					
						new_face_.mibun = 신분_일반;
						new_face_.loyalty = 100;
						new_face_.district = building_.get_district_id();
				}
				
			    // 패배 이벤트
				else 
				{
					pk::play_se(9); //효과음_실패3
					pk::background(33); // 떠나기
					pk::message_box(pk::encode("자네가 이겼군... 이제 어떻게 할 셈인가?"), kunshu_);
					pk::message_box(pk::encode("만나뵈어 영광이었습니다만, 저는 다른 곳으로 떠나려 합니다."), new_face_);
					pk::message_box(pk::encode("아쉽지만 알겠네. 행운을 비네."), kunshu_);
					pk::play_se(3); //효과음_실패1
					pk::message_box(pk::encode("무장 발탁에 실패했습니다."));
					pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x(이)가 다른 도시로 떠났습니다.", newface_name)));
				
				
					auto district = pk::get_district(pk::get_district_id(force_, 1));
				    district.ap -= 소모행동력;	
				
					int move = Quit();
					new_face_.mibun = 신분_재야;
					new_face_.service = move;
					new_face_.location = move;
				}
			}
			
			else
			{
				// R등급
	    	    if (v <40)
		    	{		
		    	    pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x님을 위해서 충성을 바치겠습니다.", kunshu_name)), new_face_);
	    			pk::play_se(6); //효과음_성공1
	    		    pk::message_box(pk::encode(pk::format("\x1b[32x[R등급]\x1b[0x 무장 \x1b[32x{}\x1b[0x(이)가 아군으로 합류했습니다.", newface_name)));
	    		}
				
	    		// N등급
	    		else if (v <64)
                {
		    	    pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x님을 위해서 충성을 바치겠습니다.", kunshu_name)), new_face_);
		    		pk::play_se(6); //효과음_성공1
		    	    pk::message_box(pk::encode(pk::format("\x1b[28x[N등급]\x1b[0x 무장 \x1b[28x{}\x1b[0x(이)가 아군으로 합류했습니다.", newface_name)));
		    	}	
				
                // F등급			
		    	else
		    	{
		    		pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x님을 위해서 충성을 바치겠습니다.", kunshu_name)), new_face_);
		    		pk::play_se(7); //효과음_실패2
		    	    pk::message_box(pk::encode(pk::format("\x1b[25x[F등급]\x1b[0x 무장 \x1b[25x{}\x1b[0x(이)가 아군으로 합류했습니다.", newface_name)));	
		    	}
			
			
		    	auto district = pk::get_district(pk::get_district_id(force_, 1));
		        district.ap -= 소모행동력;	
		        pk::sort(pk::person::type_id);
		        pk::move(new_face_, building_);
				
		    	new_face_.mibun = 신분_일반;
		    	new_face_.loyalty = 100;
		    	new_face_.district = building_.get_district_id();
		    }
			
			if (v <24)
			{
				pk::fade(0);
		    	pk::background(-1);	
			}
			else {}
		}
		
		void Event_특별발탁2() // 일기토설전이벤트 없음
		{
			pk::message_box(pk::encode(pk::format("주공, \x1b[1x{}\x1b[0x님을 모셔왔습니다.", newface_name)), person_2);
			pk::message_box(pk::encode(pk::format("안녕하십니까. \x1b[1x{}\x1b[0x님을 뵙게 되어 영광입니다.", kunshu_name)), new_face_);
			pk::message_box(pk::encode("이렇게 찾아줘서 고맙네. 앞으로 나를 도와주겠는가?"), kunshu_);
			
			if (v < 24)
			{
			    pk::play_se(25); //효과음_기회
			    pk::fade(255);
			    pk::background(35); // 전령 보고
			}
			else {}
			
			// EX등급
		    if (v <4)
		    {
			    pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x님을 위해서 충성을 바치겠습니다.", kunshu_name)), new_face_);
			    pk::play_se(22); //효과음_성공3
		        pk::message_box(pk::encode(pk::format("\x1b[17x[EX등급]\x1b[0x 무장 \x1b[17x{}\x1b[0x(이)가 아군으로 합류했습니다.", newface_name)));
		        pk::message_box(pk::encode(pk::format("기교 포인트를 \x1b[17x{}\x1b[0x만큼 획득했습니다.", TP_COST)));
		        pk::add_tp(force_, TP_COST * 2, force_.get_pos());
		    }
			
		    // SSR등급
		    else if (v <12)
		    {
		    	pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x님을 위해서 충성을 바치겠습니다.", kunshu_name)), new_face_);
		    	pk::play_se(10); //효과음_성공2
		        pk::message_box(pk::encode(pk::format("\x1b[29x[SSR등급]\x1b[0x 무장 \x1b[29x{}\x1b[0x(이)가 아군으로 합류했습니다.", newface_name)));
		    }

		    // SR등급
		    else if (v <24)
		    {
	    		pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x님을 위해서 충성을 바치겠습니다.", kunshu_name)), new_face_);
	    		pk::play_se(10); //효과음_성공2
	    	    pk::message_box(pk::encode(pk::format("\x1b[27x[SR등급]\x1b[0x 무장 \x1b[27x{}\x1b[0x(이)가 아군으로 합류했습니다.", newface_name)));	
		    }
			
			// R등급
		    else if (v <40)
			{		
			    pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x님을 위해서 충성을 바치겠습니다.", kunshu_name)), new_face_);
				pk::play_se(6); //효과음_성공1
			    pk::message_box(pk::encode(pk::format("\x1b[32x[R등급]\x1b[0x 무장 \x1b[32x{}\x1b[0x(이)가 아군으로 합류했습니다.", newface_name)));
			}
				
			// N등급
			else if (v <64)
            {
			    pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x님을 위해서 충성을 바치겠습니다.", kunshu_name)), new_face_);
				pk::play_se(6); //효과음_성공1
			    pk::message_box(pk::encode(pk::format("\x1b[28x[N등급]\x1b[0x 무장 \x1b[28x{}\x1b[0x(이)가 아군으로 합류했습니다.", newface_name)));
			}	
				
            // F등급			
			else
			{
				pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x님을 위해서 충성을 바치겠습니다.", kunshu_name)), new_face_);
				pk::play_se(7); //효과음_실패2
			    pk::message_box(pk::encode(pk::format("\x1b[25x[F등급]\x1b[0x 무장 \x1b[25x{}\x1b[0x(이)가 아군으로 합류했습니다.", newface_name)));	
			}
			
			
			auto district = pk::get_district(pk::get_district_id(force_, 1));
		    district.ap -= 소모행동력;	
		    pk::sort(pk::person::type_id);
		    pk::move(new_face_, building_);
				
			new_face_.mibun = 신분_일반;
			new_face_.loyalty = 100;
			new_face_.district = building_.get_district_id();
			
			if (v <24)
			{
				pk::fade(0);
		    	pk::background(-1);	
			}
			else {}
		}

		// 일반발탁 이벤트=================================================================================================================
        
		void Event_일반발탁1()  // 일기토설전이벤트 실행
		{
			int result;
			
			pk::message_box(pk::encode(pk::format("주공, \x1b[1x{}\x1b[0x님을 모셔왔습니다.", newface_name)), person_2);
			pk::message_box(pk::encode(pk::format("안녕하십니까. \x1b[1x{}\x1b[0x님을 뵙게 되어 영광입니다.", kunshu_name)), new_face_);
			pk::message_box(pk::encode("이렇게 찾아줘서 고맙네. 앞으로 나를 도와주겠는가?"), kunshu_);
			
			if (v <4)
			{
			    pk::play_se(25); //효과음_기회
		    	pk::fade(255);
		    	pk::background(35); // 전령 보고
			
		    	pk::message_box(pk::encode("그전에 한가지 청을 드려도 되겠습니까?"), new_face_);
		    	pk::message_box(pk::encode("그래 말해보게나."), kunshu_);
				
			    // 일기토 설전 선택
	    		if (new_face_.base_stat[무장능력_무력] >= new_face_.base_stat[무장능력_지력])
			    	{
				    pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x님의 신하들 중 한 분과 일기토로 겨뤄보고 싶습니다.", kunshu_name)), new_face_);
				    pk::message_box(pk::encode(pk::format("저를 꺾으신다면 \x1b[1x{}\x1b[0x님께 충성을 바치도록 하겠습니다.", kunshu_name)), new_face_);
				}
			
				else
				{
			        pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x님의 신하들 중 한 분과 설전으로 겨뤄보고 싶습니다.", kunshu_name)), new_face_);
					pk::message_box(pk::encode(pk::format("저를 꺾으신다면 \x1b[1x{}\x1b[0x님께 충성을 바치도록 하겠습니다.", kunshu_name)), new_face_);
				}
			
				pk::list<pk::person@> Opponent_list = pk::get_person_list(force_, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반));
			
				if (new_face_.base_stat[무장능력_무력] >= new_face_.base_stat[무장능력_지력])
				{   
				    person_array = pk::list_to_array(pk::person_selector(pk::encode("일기토 무장선택"), pk::encode("무장을 선택해 주십시오."), Opponent_list, 1, 1));
				}
			
				else
				{	
				    person_array = pk::list_to_array(pk::person_selector(pk::encode("설전 무장선택"), pk::encode("무장을 선택해 주십시오."), Opponent_list, 1, 1));
				}
			
				@Opponent_ = person_array[0];
				Opponent_name = pk::decode(pk::get_name(Opponent_));
				
				if (kunshu_.get_id() == Opponent_.get_id()) 
				{	
			        pk::message_box(pk::encode("좋다. 내가 직접 상대해주도록 하지."), kunshu_);
				    pk::message_box(pk::encode("직접 상대해주시다니 영광입니다."), new_face_);
				}
			
				else
				{	
			        pk::message_box(pk::encode(pk::format("좋다. \x1b[1x{}\x1b[0x 있는가.", Opponent_name)), kunshu_);
				    pk::message_box(pk::encode("예 주공."), Opponent_);
					pk::message_box(pk::encode("자네가 상대해주도록 하게."), kunshu_);
					pk::message_box(pk::encode("명을 받듭니다."), Opponent_);
				}
			
				if (new_face_.base_stat[무장능력_무력] >= new_face_.base_stat[무장능력_지력]) 
				{
					if (kunshu_.get_id() == Opponent_.get_id()) 
						result = pk::duel(null, null, kunshu_, null, null, new_face_, null, null, pk::is_player_controlled(kunshu_), false, 0, true).first;
					else 
						result = pk::duel(null, null, Opponent_, null, null, new_face_, null, null, pk::is_player_controlled(kunshu_), false, 0, true).first;
				}
				else 
				{
					if (kunshu_.get_id() == Opponent_.get_id()) 
						result = pk::debate(kunshu_, new_face_, pk::is_player_controlled(kunshu_), false, false, true).first;
					else 
						result = pk::debate(Opponent_, new_face_, pk::is_player_controlled(kunshu_), false, false, true).first;
				}
			
				if (result == 0) 
				{
					pk::play_se(12); //효과음_성공4
					pk::background(30); // 충성 맹세
					
				    // SR등급
			    	pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x님을 위해서 충성을 바치겠습니다.", kunshu_name)), new_face_);
			    	pk::play_se(10); //효과음_성공2
			    	pk::message_box(pk::encode(pk::format("\x1b[27x[SR등급]\x1b[0x 무장 \x1b[27x{}\x1b[0x(이)가 아군으로 합류했습니다.", newface_name)));	

					auto district = pk::get_district(pk::get_district_id(force_, 1));
				    district.ap -= 소모행동력;	
				    pk::sort(pk::person::type_id);
				    pk::move(new_face_, building_);
					
					new_face_.mibun = 신분_일반;
					new_face_.loyalty = 100;
					new_face_.district = building_.get_district_id();
				}
				
                // 패배 이벤트
				else 
				{
					pk::play_se(9); //효과음_실패3
					pk::background(33); // 떠나기
					pk::message_box(pk::encode("자네가 이겼군... 이제 어떻게 할 셈인가?"), kunshu_);
					pk::message_box(pk::encode("만나뵈어 영광이었습니다만, 저는 다른 곳으로 떠나려 합니다."), new_face_);
					pk::message_box(pk::encode("아쉽지만 알겠네. 행운을 비네."), kunshu_);
					pk::play_se(3); //효과음_실패1
					pk::message_box(pk::encode("무장 발탁에 실패했습니다."));
					pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x(이)가 다른 도시로 떠났습니다.", newface_name)));
				
				
					auto district = pk::get_district(pk::get_district_id(force_, 1));
				    district.ap -= 소모행동력;	
				
					int move = Quit();
					new_face_.mibun = 신분_재야;
					new_face_.service = move;
					new_face_.location = move;
				}
			}
			
			else
			{
				// R등급
	    	    if (v <20)
		    	{		
		    	    pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x님을 위해서 충성을 바치겠습니다.", kunshu_name)), new_face_);
	    			pk::play_se(6); //효과음_성공1
	    		    pk::message_box(pk::encode(pk::format("\x1b[32x[R등급]\x1b[0x 무장 \x1b[32x{}\x1b[0x(이)가 아군으로 합류했습니다.", newface_name)));
	    		}
				
	    		// N등급
	    		else if (v <52)
                {
		    	    pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x님을 위해서 충성을 바치겠습니다.", kunshu_name)), new_face_);
		    		pk::play_se(6); //효과음_성공1
		    	    pk::message_box(pk::encode(pk::format("\x1b[28x[N등급]\x1b[0x 무장 \x1b[28x{}\x1b[0x(이)가 아군으로 합류했습니다.", newface_name)));
		    	}	
				
                // F등급			
		    	else
		    	{
		    		pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x님을 위해서 충성을 바치겠습니다.", kunshu_name)), new_face_);
		    		pk::play_se(7); //효과음_실패2
		    	    pk::message_box(pk::encode(pk::format("\x1b[25x[F등급]\x1b[0x 무장 \x1b[25x{}\x1b[0x(이)가 아군으로 합류했습니다.", newface_name)));	
		    	}
			
			
		    	auto district = pk::get_district(pk::get_district_id(force_, 1));
		        district.ap -= 소모행동력;	
		        pk::sort(pk::person::type_id);
		        pk::move(new_face_, building_);
				
		    	new_face_.mibun = 신분_일반;
		    	new_face_.loyalty = 100;
		    	new_face_.district = building_.get_district_id();
		    }
			
			if (v <4)
			{
				pk::fade(0);
		    	pk::background(-1);	
			}
			else {}
		}
		
		void Event_일반발탁2() // 일기토설전이벤트 없음
		{
			pk::message_box(pk::encode(pk::format("주공, \x1b[1x{}\x1b[0x님을 모셔왔습니다.", newface_name)), person_2);
			pk::message_box(pk::encode(pk::format("안녕하십니까. \x1b[1x{}\x1b[0x님을 뵙게 되어 영광입니다.", kunshu_name)), new_face_);
			pk::message_box(pk::encode("이렇게 찾아줘서 고맙네. 앞으로 나를 도와주겠는가?"), kunshu_);
			
			if (v < 4)
			{
			    pk::play_se(25); //효과음_기회
			    pk::fade(255);
			    pk::background(35); // 전령 보고
			}
			else {}
			
		    // SR등급
		    if (v <4)
		    {
	    		pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x님을 위해서 충성을 바치겠습니다.", kunshu_name)), new_face_);
	    		pk::play_se(10); //효과음_성공2
	    	    pk::message_box(pk::encode(pk::format("\x1b[27x[SR등급]\x1b[0x 무장 \x1b[27x{}\x1b[0x(이)가 아군으로 합류했습니다.", newface_name)));	
		    }
			
			// R등급
		    else if (v <20)
			{		
			    pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x님을 위해서 충성을 바치겠습니다.", kunshu_name)), new_face_);
				pk::play_se(6); //효과음_성공1
			    pk::message_box(pk::encode(pk::format("\x1b[32x[R등급]\x1b[0x 무장 \x1b[32x{}\x1b[0x(이)가 아군으로 합류했습니다.", newface_name)));
			}
				
			// N등급
			else if (v <52)
            {
			    pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x님을 위해서 충성을 바치겠습니다.", kunshu_name)), new_face_);
				pk::play_se(6); //효과음_성공1
			    pk::message_box(pk::encode(pk::format("\x1b[28x[N등급]\x1b[0x 무장 \x1b[28x{}\x1b[0x(이)가 아군으로 합류했습니다.", newface_name)));
			}	
				
            // F등급			
			else
			{
				pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x님을 위해서 충성을 바치겠습니다.", kunshu_name)), new_face_);
				pk::play_se(7); //효과음_실패2
			    pk::message_box(pk::encode(pk::format("\x1b[25x[F등급]\x1b[0x 무장 \x1b[25x{}\x1b[0x(이)가 아군으로 합류했습니다.", newface_name)));	
			}
			
			
			auto district = pk::get_district(pk::get_district_id(force_, 1));
		    district.ap -= 소모행동력;	
		    pk::sort(pk::person::type_id);
		    pk::move(new_face_, building_);
				
			new_face_.mibun = 신분_일반;
			new_face_.loyalty = 100;
			new_face_.district = building_.get_district_id();
		
			if (v <4)
			{
				pk::fade(0);
		    	pk::background(-1);	
			}
			else {}
		}
		
		// 일기토 설전 패배 ===================================================================================================================
		
		int Quit() 
		{
			int city_id;
			while(true) 
			{
				city_id = pk::rand(도시_끝);
				if (pk::get_city(city_id).get_force_id() != force_.get_id()) break;
			}
			return city_id;
		}
		
		// 설정메뉴 관련 =====================================================================================================================
		
		void add_menu_Gachasetting()
		{
			pk::menu_item item;
			item.menu = 2;
			item.get_text = pk::menu_item_get_text_t(getText_GachaSetting);
			item.get_desc = pk::menu_item_get_desc_t(getDesc_GachaSetting);
			item.is_enabled = pk::menu_item_is_enabled_t(isEnabled_GachaSetting);
			item.handler = pk::menu_item_handler_t(handler_GachaSetting);
			pk::add_menu_item(item);
		}
		
		//======================================================================
		
		string pad_callback(int line, int original_value, int current_value)
        {
            return pk::encode("숫자입력");  // 텍스트 표시기능인 듯 하나, 사용방법 모르겠음
        }
		
		//======================================================================
		
		bool isEnabled_GachaSetting()
		{
			return true;
		}
		
		string getText_GachaSetting()
		{
			return pk::encode("무장가차설정");
		}

		string getDesc_GachaSetting()
		{
			return pk::encode("무장가차 스크립트의 설정을 변경합니다");
		}
		
        // 설정메뉴 ===========================================================================================================
        bool handler_GachaSetting()
		{
            array<string> GachaSetting =
            {
                pk::encode("일반특별전환 설정"),
                pk::encode("자원 설정"),
                pk::encode("확률 설정"),
                pk::encode("이벤트 설정"),
                pk::encode("뒤로가기")
            };
			
            int answer = pk::choose(GachaSetting, pk::encode("변경할 항목을 선택해 주십시오"), person_2);
			
			switch (answer)
            {
                case 0:
                return 가챠설정();

                case 1:
                return 자원설정();

                case 2:
                return 확률설정();

                case 3:
                return 이벤트설정();

                case 4:
                return false;
            }
			
            return false;
        }
		
		// 가챠설정 ===========================================================================================================
		bool 가챠설정()
		{
			string 일반특별전환_출력;
			
			if (일반특별전환 == 1)
            {
                일반특별전환_출력 = "\x1b[29x특별\x1b[0x 무장발탁 실행";
            }
            else
            {
                일반특별전환_출력 = "\x1b[2x일반\x1b[0x 무장발탁 실행";
            }
			
			array<string> GachaSetting_switch =
            {
                pk::encode(일반특별전환_출력),
                pk::encode("뒤로가기")
            };
			
			int answer = pk::choose(GachaSetting_switch, pk::encode("\x1b[29x특별\x1b[0x : \x1b[25x[F등급]\x1b[0x~\x1b[17x[EX등급]\x1b[0x \n\x1b[2x일반\x1b[0x : \x1b[25x[F등급]\x1b[0x~\x1b[27x[SR등급]\x1b[0x"), person_2);
			
			switch (answer)
            {
                case 0:
                일반특별전환 = (일반특별전환 + 1) % 2;
                break;

                case 1:
                return handler_GachaSetting();
            }
			
			return 가챠설정();
		}	
		
		// 자원설정 ===========================================================================================================
		bool 자원설정()
		{
			string 필요행동력_출력;
			string 필요금_출력;
			
			
			
			if (필요행동력 == 0)
            {
                필요행동력_출력 = "행동력 소모 : \x1b[29x0\x1b[0x";
				소모행동력 = 행동력1;
            }
			
			else if (필요행동력 == 1)
            {
                필요행동력_출력 = "행동력 소모 : \x1b[2x10\x1b[0x";
				소모행동력 = 행동력2;
			}
			
			else if (필요행동력 == 2)
            {
                필요행동력_출력 = "행동력 소모 : \x1b[2x20\x1b[0x";	
				소모행동력 = 행동력3;
			}
			
            else
            {
                필요행동력_출력 = "행동력 소모 : \x1b[2x30\x1b[0x";
				소모행동력 = 행동력4;
            }
			
			if (필요금 == 0)
            {
                필요금_출력 = "금 소모 : \x1b[29x0\x1b[0x";
				소모금 = 금1;
            }
			
			else if (필요금 == 1)
            {
                필요금_출력 = "금 소모 : \x1b[2x100\x1b[0x";
				소모금 = 금2;
			}
				
			else if (필요금 == 2)
            {
                필요금_출력 = "금 소모 : \x1b[2x500\x1b[0x";
				소모금 = 금3;
			}
			
            else
            {
                필요금_출력 = "금 소모 : \x1b[2x1000\x1b[0x";
				소모금 = 금4;
            }
			
			array<string> ResourceSetting =
            {
                pk::encode(필요행동력_출력),
				pk::encode(필요금_출력),
                pk::encode("뒤로가기")
            };
			
			int answer = pk::choose(ResourceSetting, pk::encode("\x1b[2x행동력\x1b[0x : (0, 10, 20, 30) \n  \x1b[2x금\x1b[0x   : (0, 100, 500, 1000)"), person_2);
			
			switch (answer)
            {
                case 0:
				필요행동력 = (필요행동력 + 1) % 4;
                break;
				
				case 1:
				필요금 = (필요금 + 1) % 4;
                break;

                case 2:
                return handler_GachaSetting();
            }
		
			return 자원설정();
		}
		
		// 확률설정 ===========================================================================================================
		bool 확률설정()
		{
			string 발탁실패확률_출력;
			string 성별비율_출력;
			
			발탁실패확률_출력 = pk::format("실패확률 : \x1b[2x{}\x1b[0x %", 발탁실패확률);
            성별비율_출력 = pk::format("남성비율 : \x1b[2x{}\x1b[0x %", 성별비율);
			
			array<string> ProbabilitySetting =
            {
                pk::encode(발탁실패확률_출력),
				pk::encode(성별비율_출력),
                pk::encode("뒤로가기")
            };
			
			int answer = pk::choose(ProbabilitySetting, pk::encode("\x1b[2x실패확률\x1b[0x : 기본설정 \x1b[2x75\x1b[0x % \n\x1b[2x성별비율\x1b[0x : 남성비율을 줄이면 여성비율이 늘어납니다."), person_2);
			
			switch (answer)
            {
                case 0:
                발탁실패확률 = pk::numberpad(pk::encode("실패확률"), 0, 100, 발탁실패확률, pk::numberpad_t(pad_callback)).first;
                break;
				
				case 1:
                성별비율 = pk::numberpad(pk::encode("남성비율"), 0, 100, 성별비율, pk::numberpad_t(pad_callback)).first;
                break;

                case 2:
                return handler_GachaSetting();
            }
			
			return 확률설정();
		}	
		
		// 이벤트 설정 =========================================================================================================
		bool 이벤트설정()
		{
			string 이벤트실행여부_출력;
			
			if (이벤트실행여부 == 1)
            {
                이벤트실행여부_출력 = "일기토 설전 이벤트 : \x1b[2xON\x1b[0x";
            }
            else
            {
                이벤트실행여부_출력 = "일기토 설전 이벤트 : \x1b[29xOFF\x1b[0x";
            }
			
			array<string> EventSetting_switch =
            {
                pk::encode(이벤트실행여부_출력),
                pk::encode("뒤로가기")
            };
			
			int answer = pk::choose(EventSetting_switch, pk::encode("일기토 설전 이벤트 실행여부를 선택해주십시오"), person_2);
			
			switch (answer)
            {
                case 0:
                이벤트실행여부 = (이벤트실행여부 + 1) % 2;
                break;

                case 1:
                return handler_GachaSetting();
            }
			
			return 이벤트설정();
		}	
				
		// 신무장 슬롯 관련 ==================================================================================================================
		
		/**
		@details
			빈 무장칸은 아래의 순서대로 확인할 것을 권장함.
			1.  850 ~  999(신무장)
			2.  832 ~  849(사용하지 않는 고대 무장)
			3.  670 ~  699(사용하지 않는 사실 무장)
			4.  800 ~  831(고대 무장)
			5.    0 ~  670(역사 무장)
			6. 1000 ~ 1099(적장). pk::create_bandit 함수에서 사용하는 영역임.
			7.  700 ~  799(이벤트 무장). 신분에 상관없이 pk::is_alive 함수가 항상 true를 리턴하는 영역임.

			사망한 무장을 부활시키는 스크립트가 있다면 "case 신분_사망:" 부분은 제외.
		*/
		
		/*
		bool getEmptyPerson()
		{
			for (int i = 1000; i < 1099; i++)
			{
				pk::person@ new_face = pk::get_person(i);

				switch (new_face.mibun)
				{
					case 신분_없음	:
					case 신분_미등장:
					case 신분_미발견:
					case 신분_사망	:
						return true;
				}
			}
			return false;
		}
		*/
		
		pk::person@ getEmptyPerson()
		{
			if (slot_일반무장)
			{
				for (int i = 0; i < 700; i++)
				{
					pk::person@ new_face_ = pk::get_person(i);
					
					switch (new_face_.mibun)
					{
					case 신분_없음:
					case 신분_사망:
						return new_face_;
					}
				}
			}
			
			if (slot_신무장)
			{
				for (int i = 963; i < 1000; i++)
				{
					pk::person@ new_face_ = pk::get_person(i);
					switch (new_face_.mibun)
					{
					case 신분_없음:
					case 신분_미등장:
					case 신분_사망:
						return new_face_;
					}
				}
			}
			
			if (slot_고대무장)
			{
				for (int i = 832; i < 850; i++)
				{
					pk::person@ new_face_ = pk::get_person(i);
					switch (new_face_.mibun)
					{
					case 신분_없음:
					case 신분_미등장:
					case 신분_사망:
						return new_face_;
					}
				}
			}
			return null;
		} // pk::person@ getEmptyPerson()
	}
	Main main;
}