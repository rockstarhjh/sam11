/*
@만든이: 크래픽스
@Update: 2024.5.26
@Update: 2024.5.31, 지력요구치관련 계략특기에 백출,연환,귀모도 추가
@Update: 2024.6.1, 스킬적용시 에러수정
@Update: 2024.6.4, 전투무장중 무력이 요구치보다 높으면 계략특기 배제
@Update: 2024.6.5, 적성이 모두 -1인 에러무장 처리
*/
namespace AI특기최적화_SkillOptimization
{
	//돌려보고, 좀 유니크한 무장들은 제외했습니다.
	array<int> 특기최적화_제외무장 = 
	{ 
		무장_동탁,무장_원소,무장_손권,무장_한호,무장_제갈근,무장_노숙,무장_전문,무장_정보,무장_비의,무장_등지,무장_공구,무장_한무,무장_희평,
		무장_왕창,무장_종요,무장_장패,무장_양습,무장_노식,무장_굴원,무장_여불위,무장_전인제,무장_선우보,무장_염행,무장_웅의,무장_사마유,무장_마등
	};

	const int 전투무장_무력_요구치 = 70; //통솔이나 무력이 70보다 높으면 전투무장으로 판단합니다.
	const int 전투무장_통솔_요구치 = 70;
	const int 계략특기_지력_요구치 = 70; //지력니 낮은데 계략특기를 받지 않도록 합니다.

	const bool 군주무장_제외 = true; //군주무장의 경우 내정 특기를 가진경우가 많아 추가했습니다.
	
	const bool 신급특기_최적화 = true; //신급특기간의 교환을 합니다.
	const bool 장급특기_최적화 = true; //장급특기간의 교환을 합니다.
	const bool 병종특기_최적화 = true; //공성특기,궁병특기,근접특기,기병특기,창병특기,극병특기,육군특기,수군특기간의 교환을 합니다.
	
	const bool 내정특기_교환_사용 = true; //전투무장이 내정특기를 가진경우 교환합니다.
	const bool 내정특기_논객_인정_교환_사용 = true;//전투무장이 내정특기를 가진경우 교환합니다.
	const bool 내정특기_명성_능리_번식_교환_사용 = true;//전투무장이 내정특기를 가진경우 교환합니다.
	const bool 내정특기_부호_미도_징세_징수_교환_사용 = true;//전투무장이 내정특기를 가진경우 교환합니다.
	const bool 내정특기_재해_교환_사용 = true;//전투무장이 내정특기를 가진경우 교환합니다.


	array<int> 신급특기 = { 특기_기신, 특기_극신, 특기_궁신, 특기_공신,특기_수신, 특기_창신,특기_투신};
	array<int> 장급특기 = { 특기_기장, 특기_극장, 특기_궁장, 특기_공성,특기_수장, 특기_창장};

	//내정특기와 교환하시면 연쇄적으로 특기교환 일어납니다. 적성이 맞지 않는 경우
	array<int> 공성특기 = { 특기_사정 };
	array<int> 궁병특기 = { 특기_사수 };
	array<int> 근접특기 = { 특기_맹장, 특기_심공 };
	array<int> 기병특기 = { 특기_질주 ,특기_백마 ,특기_행군};
	array<int> 창병특기 = { };
	array<int> 극병특기 = { };
	array<int> 육군특기 = { 특기_강행,특기_도주 ,특기_급습,특기_난전};
	array<int> 수군특기 = { 특기_추진, 특기_조타 ,특기_강습};
	/// /////////////////////////////////////////////////////////////////////////////////////////
	

	array<int> 신장급특기 = { 특기_용장,특기_신장,특기_구축,특기_비장,특기_패왕 };

	array<int> 전체특기 = { 특기_소탕,특기_앙양,특기_정묘,특기_강탈,특기_노발,특기_혈로,특기_호위,특기_주악,특기_지도 };
	array<int> 전체특기2= { 특기_연전,특기_포박,특기_위풍 ,특기_보좌,특기_강운 };

	array<int> 수비특기 = { 특기_금강,특기_불굴 ,특기_철벽 ,특기_등갑 };
	array<int> 계략방어특기 = { 특기_규율 ,특기_침착 ,특기_명경 ,특기_통찰};
	array<int> 화계특기 = { 특기_화공 ,특기_화신 };
	array<int> 계략특기 = { 특기_매복 ,특기_언독 ,특기_기략,특기_궤계,특기_묘계 ,특기_비책,특기_간파,특기_반계 };
	array<int> 계략특기_허실_신산_심모 = { 특기_허실, 특기_신산 ,특기_심모};
	array<int> 계략특기_백출_귀모_연환 = {특기_백출 ,특기_귀모 ,특기_연환};
	array<int> 요술_귀문 = { 특기_요술 ,특기_귀문};
	array<int> 여성특기 = {특기_경국,특기_내조};
	
	array<int> 내정특기 = { 특기_둔전,특기_발명,특기_조선 ,특기_지도 ,특기_안력,특기_위압 ,특기_운반 };
	array<int> 내정특기_논객_인정 = {특기_논객,특기_인정};
	array<int> 내정특기_명성_능리_번식 = { 특기_명성 ,특기_능리,특기_번식 };
	array<int> 내정특기_부호_미도_징세_징수 = { 특기_부호 ,특기_미도,특기_징세, 특기_징수 };
	array<int> 내정특기_재해 = { 특기_친오 ,특기_친강,특기_친월 ,특기_친만 ,특기_풍수,특기_기원 };

	//내정특기와 교환 가능 특기 설정///////////////////////////////////////////////////////////////////////////////////////
	array<array<int>> 내정특기_교환 = { 전체특기,계략특기 };
	array<array<int>> 내정특기_논객_인정_교환 = { 전체특기2,계략특기_백출_귀모_연환 ,신장급특기,계략특기_허실_신산_심모 };
	array<array<int>> 내정특기_명성_능리_번식_교환 = { 계략방어특기 };
	array<array<int>> 내정특기_부호_미도_징세_징수_교환 = { 계략방어특기,수비특기 };
	array<array<int>> 내정특기_재해_교환 = { 수비특기, 계략특기 };


	class Main
	{
		Main()
		{
			pk::bind(102, pk::trigger102_t(Init));
			pk::bind(111, pk::trigger111_t(onTurn));
		}
		void Init()
		{

			for (int i = 0; i < 무장_끝; i++)
			{
				pk::person@ p = pk::get_person(i);
				if(p.is_player())
					continue;
				if ((p.get_id() >= 무장_영제 && p.get_id() <= 무장_이벤트A0) || p.get_id() >= 적장_시작)
					continue;

				pk::force@ f = pk::get_force(p.get_force_id());
				if(f==null)
					continue;
				if(특기최적화_제외무장.find(p.get_id()) >=0)
					continue;
				if(군주무장_제외 && p.mibun == 신분_군주)
					continue;

				update신급특기(p, f);
				update장급특기(p, f);
				update병종특기(p, f);
				update내정특기(p, f);
			}
		}
		void onTurn(pk::force@ f)
		{
			if (f.is_player())
				return;
			pk::list<pk::person@> ps = pk::get_person_list(f, pk::mibun_flags(신분_군주,신분_도독,신분_태수,신분_일반,신분_포로));
			for (int i = 0; i < ps.count; i++)
			{
				pk::person@ p = ps[i];
				if ((p.get_id() >= 무장_영제 && p.get_id() <= 무장_이벤트A0) || p.get_id() >= 적장_시작)
					continue;
				if (특기최적화_제외무장.find(p.get_id()) >= 0)
					continue;
				if (군주무장_제외 && p.mibun == 신분_군주)
					continue;


				update신급특기(p, f);
				update장급특기(p, f);
				update병종특기(p, f);
				update내정특기(p, f);
			}
		}

		bool check전투무장(pk::person@ p)
		{
			return p.max_stat[무장능력_무력] >= 전투무장_무력_요구치 || p.max_stat[무장능력_통솔] >= 전투무장_통솔_요구치;
		}

		int get적성(int weapon, pk::person@ p)
		{
			if (weapon == -1)
				return 0;
			return p.tekisei[weapon];
		}
		int get최대적성병종(pk::person@ p)
		{
			int max = -1;
			int maxIndex = -1;
			for (int i = 0; i < 병종_끝; i++)
			{
				if (p.tekisei[i] > max)
				{
					maxIndex = i;
					max = p.tekisei[i];
				}
			}
			return maxIndex;
		}

		int get특기_병종(int 특기)
		{
			switch (특기)
			{
			case 특기_창장:	case 특기_창신: return 병종_창병;
			case 특기_극장: case 특기_극신: return 병종_극병;
			case 특기_궁장: case 특기_궁신: return 병종_노병;
			case 특기_기장: case 특기_기신: return 병종_기병;
			case 특기_공성: case 특기_공신: return 병종_병기;
			case 특기_수장: case 특기_수신: return 병종_수군;
			default:
				break;
			}
			return -1;
		}
		int get병종_특기_신급(int 병종)
		{
			switch (병종)
			{
			case 병종_창병: return 특기_창신;
			case 병종_극병: return 특기_극신;
			case 병종_노병: return 특기_궁신;
			case 병종_기병: return 특기_기신;
			case 병종_병기: return 특기_공신;
			case 병종_수군: return 특기_수신;
			default:
				break;
			}
			return -1;
		}
		int get병종_특기_장급(int 병종)
		{
			switch (병종)
			{
			case 병종_창병: return 특기_창장;
			case 병종_극병: return 특기_극장;
			case 병종_노병: return 특기_궁장;
			case 병종_기병: return 특기_기장;
			case 병종_병기: return 특기_공성;
			case 병종_수군: return 특기_수장;
			default:
				break;
			}
			return -1;
		}

		string get최대적성str(int 적성)
		{
			switch (적성)
			{
			case 0: return "C";
			case 1: return "B";
			case 2: return "A";
			case 3: return "S";
			case 4: return "S1";
			case 5: return "S2";
			case 6: return "S3";
			case 7: return "S4";
			case 8: return "S5";
			case 9: return "S6";
			case 10: return "S7";
			case 11: return "S8";
			case 12: return "S9";
				
			default:return "SX";
				break;
			}
			return "";
		}

		void update신급특기(pk::person@ p,pk::force@ f)
		{
			if (!신급특기_최적화)
				return;
			if (신급특기.find(p.skill) == -1)
				return;

			if (p.tekisei[0] < 0 && p.tekisei[1] < 0 && p.tekisei[2] < 0 && p.tekisei[3] < 0 && p.tekisei[4] < 0 && p.tekisei[5] < 0)
			{
				int 병종 = get특기_병종(p.skill);
				for (int i = 0; i < 6; i++)
				{
					p.tekisei[i] = 적성_B;
				}
				p.tekisei[병종] = 적성_S;
				string strType = "";
				switch (병종)
				{
				case 병종_창병: strType = "창병"; break;
				case 병종_극병: strType = "극병"; break;
				case 병종_노병: strType = "노병"; break;
				case 병종_기병: strType = "기병"; break;
				case 병종_병기: strType = "병기"; break;
				case 병종_수군: strType = "수군"; break;
				default:
					break;
				}

				string str = pk::format("\x1b[2x{}군\x1b[0x,\x1b[1x{}\x1b[0x,{},S 최적화", getName(f), getName(p), strType);
				pk::history_log(p.get_pos(), f != null ? f.color : 0, pk::encode(str));
				return;
			}

			int bskill = p.skill;
			if (p.skill != 특기_투신)
			{
				int a = get적성(get특기_병종(p.skill), p);
				if (a < 적성_S) 
				{
					int 최대적성병종 = get최대적성병종(p);
					int 최대적성 = get적성(최대적성병종,p);
					//pk::printf("최대적성:{},{}\n", getName(p), get최대적성str(최대적성));
					if (최대적성 > a) 
					{
						int s = get병종_특기_신급(최대적성병종);
						if(!pk::has_skill(p,s))
							p.skill = s;
					}
				}
			}
			else 
			{
				int a = get적성(병종_극병,p);
				int b = get적성(병종_창병,p);
				if (a < 적성_S && b < 적성_S)
				{
					int 최대적성병종 = get최대적성병종(p);
					int 최대적성 = get적성(최대적성병종,p);
					if (최대적성병종 != 병종_극병 && 최대적성병종 != 병종_창병 && (최대적성 > a && 최대적성 > b))
					{
						int s = get병종_특기_신급(최대적성병종);
						if (!pk::has_skill(p, s))
							p.skill = s;
					}
				}
			}
			if (bskill == p.skill)
				return;

			string str = pk::format("\x1b[2x{}군\x1b[0x,\x1b[1x{}\x1b[0x,{}->{} 최적화", getName(f), getName(p),getNameSkill(bskill),getNameSkill(p.skill));
			pk::history_log(p.get_pos(), f != null ? f.color : 0, pk::encode(str));
		}
		void update장급특기(pk::person@ p, pk::force@ f)
		{
			if (!장급특기_최적화)
				return;
			if (장급특기.find(p.skill) == -1)
				return;


			if (p.tekisei[0] < 0 && p.tekisei[1] < 0 && p.tekisei[2] < 0 && p.tekisei[3] < 0 && p.tekisei[4] < 0 && p.tekisei[5] < 0)
			{
				int 병종 = get특기_병종(p.skill);
				for (int i = 0; i < 6; i++)
				{
					p.tekisei[i] = 적성_B;
				}
				p.tekisei[병종] = 적성_S;
				string strType = "";
				switch (병종)
				{
				case 병종_창병: strType = "창병"; break;
				case 병종_극병: strType = "극병"; break;
				case 병종_노병: strType = "노병"; break;
				case 병종_기병: strType = "기병"; break;
				case 병종_병기: strType = "병기"; break;
				case 병종_수군: strType = "수군"; break;
				default:
					break;
				}

				string str = pk::format("\x1b[2x{}군\x1b[0x,\x1b[1x{}\x1b[0x,{},S 최적화", getName(f), getName(p), strType);
				pk::history_log(p.get_pos(), f != null ? f.color : 0, pk::encode(str));
				return;
			}


			int bskill = p.skill;


			int a = get적성(get특기_병종(p.skill), p);
			if (a < 적성_S)
			{
				int 최대적성병종 = get최대적성병종(p);
				int 최대적성 = get적성(최대적성병종,p);
				if (최대적성 > a) 
				{
					int s = get병종_특기_장급(최대적성병종);
					if (!pk::has_skill(p, s))
						p.skill = s;
				}
			}
			if (bskill == p.skill)
				return;

			string str = pk::format("\x1b[2x{}군\x1b[0x,\x1b[1x{}\x1b[0x,{}->{} 최적화", getName(f), getName(p), getNameSkill(bskill), getNameSkill(p.skill));
			pk::history_log(p.get_pos(), f != null ? f.color : 0, pk::encode(str));
		}

		array<int> get병종특기(int 병종)
		{
			switch (병종)
			{
			case 병종_창병: return 창병특기;
			case 병종_극병: return 극병특기;
			case 병종_노병: return 궁병특기;
			case 병종_기병: return 기병특기;
			case 병종_병기: return 공성특기;
			case 병종_수군: return 수군특기;
			default:
				break;
			}
			array<int> arr;
			return arr;
		}

		void updateSkill(pk::person@ p, array<int> arr)
		{
			array<int> arr2 = arr;
			while (arr2.length > 0)
			{
				int r = pk::rand(arr2.length);
				int s = arr2[r];
				if (!pk::has_skill(p, s))
				{
					p.skill = s;
					return;
				}

				arr2.removeAt(r);
			}
		}

		void updateSkill(pk::person@ p, array<array<int>> arr)
		{
			array<int> arr2;
			for (int i = 0; i < arr.length; i++)
			{
				for (int j = 0; j < arr[i].length; j++)
				{
					int s = arr[i][j];
					if (p.max_stat[무장능력_지력] < 계략특기_지력_요구치 || p.max_stat[무장능력_무력] > 전투무장_무력_요구치)
					{
						if (계략특기.find(s) >= 0 || 계략특기_허실_신산_심모.find(s) >= 0 || 계략특기_백출_귀모_연환.find(s) >= 0)
						{
							continue;
						}
					}
					arr2.insertLast(s);
				}
			}
			updateSkill(p, arr2);
		}

		void update병종특기(pk::person@ p, pk::force@ f)
		{
			if (!병종특기_최적화)
				return;
			if (p.skill == -1)
				return;
			if (공성특기.find(p.skill) == -1 && 궁병특기.find(p.skill) == -1 && 기병특기.find(p.skill) == -1 && 창병특기.find(p.skill) == -1 && 극병특기.find(p.skill) == -1 &&
				육군특기.find(p.skill) == -1 && 수군특기.find(p.skill) == -1)
				return;

		
			int bskill = p.skill;

			if (육군특기.find(p.skill) >= 0)
			{
				int 최대병종 = get최대적성병종(p);
				if (최대병종 == 병종_수군)
				{
					updateSkill(p, 수군특기);
				}
				else if (최대병종 == 병종_병기)
				{
					updateSkill(p, 공성특기);
				}
				else 
				{
					return;
				}
			}
			else 
			{
				int a = -1;
				if (공성특기.find(p.skill) >= 0)
					a = get적성(병종_병기,p);
				if (a == -1 && 궁병특기.find(p.skill) >= 0)
					a = get적성(병종_노병,p);
				if (a == -1 && 수군특기.find(p.skill) >= 0)
					a = get적성(병종_수군, p);
				if (a == -1 && 기병특기.find(p.skill) >= 0)
					a = get적성(병종_기병,p);
				if (a==-1 && 근접특기.find(p.skill) >= 0)
				{
					int a0 = get적성(병종_창병, p);
					int a1 = get적성(병종_극병, p);
					int a2 = get적성(병종_기병, p);
					a = pk::max(pk::max(a0, a1), a2);
				}
				if (a == -1 && 창병특기.find(p.skill) >= 0)
					a = get적성(병종_창병,p);
				if (a == -1 && 극병특기.find(p.skill) >= 0)
					a = get적성(병종_극병,p);

				if (a < 적성_S)
				{
					int 최대적성병종 = get최대적성병종(p);
					int 최대적성 = get적성(최대적성병종,p);
					if (최대적성 > a)
					{
						array<int> arr = get병종특기(최대적성병종);
						updateSkill(p, arr);
					}
				}
			}

			if (bskill == p.skill)
				return;

			string str = pk::format("\x1b[2x{}군\x1b[0x,\x1b[1x{}\x1b[0x,{}->{} 최적화", getName(f), getName(p), getNameSkill(bskill), getNameSkill(p.skill));
			pk::history_log(p.get_pos(), f != null ? f.color : 0, pk::encode(str));
		}

		void update내정특기(pk::person@ p, pk::force@ f)
		{
			if (!check전투무장(p))
				return;

			array<array<int>> arrs;
			if (내정특기_교환_사용 && 내정특기.find(p.skill) >= 0)
			{
				arrs = 내정특기_교환;
			}
			else if (내정특기_논객_인정_교환_사용 && 내정특기_논객_인정.find(p.skill) >= 0)
			{
				arrs = 내정특기_논객_인정_교환;
			}
			else if (내정특기_명성_능리_번식_교환_사용 && 내정특기_명성_능리_번식.find(p.skill) >= 0)
			{
				arrs = 내정특기_명성_능리_번식_교환;
			}
			else if (내정특기_부호_미도_징세_징수_교환_사용 && 내정특기_부호_미도_징세_징수.find(p.skill) >= 0)
			{
				arrs = 내정특기_부호_미도_징세_징수_교환;
			}
			else if(내정특기_재해_교환_사용 && 내정특기_재해.find(p.skill) >= 0)
			{
				arrs = 내정특기_재해_교환;
			}
			if (arrs.length == 0)
				return;

			int bskill = p.skill;
			updateSkill(p, arrs);

			if (bskill == p.skill)
				return;

			string str = pk::format("\x1b[2x{}군\x1b[0x,\x1b[1x{}\x1b[0x,{}->{} 최적화", getName(f), getName(p), getNameSkill(bskill), getNameSkill(p.skill));
			pk::history_log(p.get_pos(), f != null ? f.color : 0, pk::encode(str));
		}

		string getNameSkill(int skill)
		{
			return getName(pk::get_skill(skill));
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

	}

	Main main;
}

