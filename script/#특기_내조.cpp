/*
	@제작 : masterpiecek
	@내용 : PK2.1에서 내조 특기를 보유한 무장이 혼인 시 능력치가 상승하지 않던 버그 개선
*/

namespace 특기_내조
{
	class Main
	{

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		bool 디버깅 = false;
		array<bool> 무장별_혼인여부(무장_끝);

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		Main()
		{
			pk::bind(102, pk::trigger102_t(시나리오초기화));
			pk::bind(111, pk::trigger111_t(턴시작));
			pk::bind(112, pk::trigger112_t(턴종료));
			pk::bind(120, pk::trigger120_t(게임화면그리기));
		}

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		void 시나리오초기화()         { update_info_of_person(); }
		void 턴시작(pk::force@ force) { update_info_of_person(); }
		void 턴종료(pk::force@ force) { update_info_of_person(); }
		void 게임화면그리기()         { action_of_spousal_support(); }

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		void update_info_of_person()
		{
			for (int person_id = 0; person_id < 무장_끝; person_id++)
			{
				pk::person@ person = pk::get_person(person_id);
				if (!pk::is_alive(person)) continue;

				무장별_혼인여부[person_id] = (person.spouse == -1) ? false : true;
			}
		}

		void action_of_spousal_support()
		{
			for (int person_id = 0; person_id < 무장_끝; person_id++)
			{
				pk::person@ person = pk::get_person(person_id);
				if (!pk::is_alive(person)) continue;
				if (무장별_혼인여부[person_id]) continue;

				int spouse_id = person.spouse;
				if (spouse_id == -1) continue;
				if (!pk::is_fuufu(person, spouse_id)) continue;

				pk::person@ spouse = pk::get_person(spouse_id);

				if (디버깅)
				{
					string person_name = pk::decode(pk::get_name(person));
					string spouse_name = pk::decode(pk::get_name(spouse));
					pk::info("무장 간 혼인 이벤트 확인 : "+person_name+", "+spouse_name);
				}

				무장별_혼인여부[person_id] = true;
				무장별_혼인여부[spouse_id] = true;

				if (pk::has_skill(person, 특기_내조) or pk::has_skill(spouse, 특기_내조))
				{
					add_base_stat(person, person_id, spouse, spouse_id);
				}
			}
		}

		void add_base_stat(pk::person@ person, int person_id, pk::person@ spouse, int spouse_id)
		{
			int person_constant = int(pk::core::skill_constant(person_id, 특기_내조, 0));
			int spouse_constant = int(pk::core::skill_constant(spouse_id, 특기_내조, 0));
			int skill_constant = pk::max(person_constant, spouse_constant);

			if (디버깅)
			{
				string person_name = pk::decode(pk::get_name(person));
				string spouse_name = pk::decode(pk::get_name(spouse));
				pk::info("내조 특기상수 : "+person_name+"("+person_constant+"), "+spouse_name+"("+spouse_constant+"), 최종("+skill_constant+")");
			}

			for (int stat_id = 0; stat_id < 무장능력_끝; stat_id++)
			{
			/// 참고 : int pk::add_base_stat(person@ self, int type, int value) - 해당 함수 사용 시 강제종료 발생
				person.base_stat[stat_id] = person.base_stat[stat_id] + skill_constant;
				spouse.base_stat[stat_id] = spouse.base_stat[stat_id] + skill_constant;
			}

			person.update();
			spouse.update();
		}

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	}

	Main main;
}