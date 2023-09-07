/**********************************************************************************
Reference : [PK2.1] 205 계략 소비 기력.cpp
Updated by 윤돌

23.1.15
	Added		mult - 지력 80이상일때 6% - 60% 까지 소비 기력 감소 factor로 소비 기력 return 값에 적용
	
**********************************************************************************/


namespace 계략_소비_기력
{
	class Main
	{
		Main()
		{
			pk::set_func(205, pk::func205_t(callback));
		}

		int callback(pk::unit@ src, int strategy_id)
		{
			float mult = 1.0f;
			int src_int = src.attr.stat[부대능력_지력];
			
			if (src_int >= 80)		// 지력 80 이상일 때 지력 100 기준 최대 60%까지 소비 기력 감소
			{
				mult = 1.0f - (src_int * src_int - 6000) * 0.6f / 4000;
			}		

			if (src.has_skill(특기_백출))
				return 1;

			switch (strategy_id)
			{
			case 계략_화계: return int(10 * mult);		// 10 -> 최소 4
			case 계략_소화: return int(10 * mult);		// 10 -> 최소 4
			case 계략_위보: return int(15 * mult);		// 15 -> 최소 6
			case 계략_교란: return int(15 * mult);		// 15 -> 최소 6
			case 계략_진정: return int(10 * mult);		// 10 -> 최소 4
			case 계략_복병: return int(10 * mult);		// 10 -> 최소 4
			case 계략_동토: return int(20 * mult);		// 20 -> 최소 8
			case 계략_요술: return int(50 * mult);		// 50 -> 최소 20
			case 계략_낙뢰: return int(50 * mult);		// 50 -> 최소 20
			}

			return 0;
		}
	}

	Main main;
}