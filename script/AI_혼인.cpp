namespace AI_혼인
{
	class Main
	{
		Main()
		{
			pk::bind(111, pk::trigger111_t(callbackTurnStart));
		}

		int best_woman_id;
		int best_woman_score;
		int best_man_id;
		int best_man_score;

		void callbackTurnStart(pk::force@ force)
		{
			best_woman_id = -1;
			best_man_id = -1;	
			best_woman_score = 0;
			best_man_score = 0;		

			if(pk::is_iminzoku(pk::get_person(force.kunshu)) or pk::is_bandit(pk::get_person(force.kunshu)))
				return;
			if(force.player >= 0)
				return;

			pk::person@ kunshu = pk::get_person(force.kunshu);

			for (int i = 0; i < 무장_끝; i++)
			{
				pk::person@ person = pk::get_person(i);
				
				if(person.sex == 1 && person.get_force_id() == force.get_id() && person.spouse < 0)
				{
					if(pk::is_oyako(kunshu, person.get_id()) && kunshu.birth > person.birth)
						continue;;

					if(best_woman_id < 0) 
						best_woman_id = person.get_id();

					if( checkBest(force.kunshu, person.get_id(), true) )
						best_woman_id = person.get_id();
				}
			}

			if(best_woman_id >=0)
			{
				for (int j=0; j<무장_끝; j++)
				{
					pk::person@ person = pk::get_person(j);
					if(person.get_force_id() == force.get_id() && person.sex == 0 && person.spouse < 0)
					{
						if(best_man_id < 0) 
							best_man_id = person.get_id();

						if( checkBest(force.kunshu, person.get_id(), false) )
							best_man_id = person.get_id();
					}
				}  
			}

			int random1 = pk::rand(1000);	
			int random2 = pk::rand(200);		

			if(pk::get_month() != 1 && pk::get_month() != 7)
				return;

			if(best_woman_id >= 0 && best_man_id >= 0 && force.tp >= 500 && (kunshu.stat[무장능력_지력] + kunshu.stat[무장능력_정치]) + kunshu.giri * 50 > random1 && best_man_score > random2 ) 
			{
				pk::person@ final_woman = pk::get_person(best_woman_id);
				pk::person@ final_man = pk::get_person(best_man_id); 	

				if(final_woman.mibun == 신분_포로 || final_man.mibun == 신분_포로)
					return;

				pk::play_se(10);
				pk::set_spouse(final_man, final_woman.get_id());
				pk::set_spouse(final_woman, final_man.get_id());
				pk::history_log(pk::get_current_turn_force_id(), force.color, pk::encode(pk::format("\x1b[2x{}\x1b[0x군의 \x1b[1x{}\x1b[0x, \x1b[1x{}\x1b[0x 두사람이 결혼" , pk::decode(pk::get_name(kunshu)), pk::decode(pk::get_name(final_man)) , pk::decode(pk::get_name(final_woman) ) ) ) );
			}
		}

		//무장 수치비교값 계산공식 = 능력 + 충성 + 공적 + 혈연 + 의형제 + 친애무장 + 랜덤
		bool checkBest(int kunshu_id, int person_id, bool is_woman)
		{
			bool result = false;

			pk::person@ kunshu = pk::get_person(kunshu_id);
			pk::person@ person = pk::get_person(person_id);
			
			int score = 0;
			int max_stat = 0;
			int avg_stat = 0;

			for (int i = 0; i < 무장능력_끝; i++)
			{
				int s = person.stat[i];
				max_stat = pk::max(max_stat, s);
				avg_stat = avg_stat + s;
			}
			avg_stat = avg_stat / 무장능력_끝;

			score += (person.stat[무장능력_매력] * 2) + (max_stat * 2) + (avg_stat * 2);
			score += (person.kouseki / 100) + person.loyalty;

			if(pk::is_oyako(kunshu, person_id)) score += 500;
			else if(pk::is_ketsuen(kunshu, person_id)) score += 300;

			if(person.mibun == 신분_군주) score += (is_woman? person.ambition * 100 : person.ambition * 50);
			if(pk::is_gikyoudai(kunshu, person_id)) score += 250;
			if(pk::is_like(kunshu, person_id)) score += 200;

			if(is_woman)
			{
				score += pk::rand(500);

				if(max_stat >= 90)
					score += 100;
				else if(max_stat >= 80)
					score += 50;
				if(avg_stat >= 90)
					score += 100;
				else if(avg_stat >= 80)
					score += 50;
				if(person.stat[무장능력_매력] >= 90)
					score += 200;
				else if(person.stat[무장능력_매력] >= 80)
					score += 100;

				if(pk::get_month() == 1)
				{
					if(best_woman_score == 0)
						best_woman_score = score + 1;

					result = score < best_woman_score;
					best_woman_score = score < best_woman_score ? score : best_woman_score;
				}
				else if(pk::get_month() == 7)
				{
					if(best_woman_score == 0)
						best_woman_score = score - 1;

					result = score > best_woman_score;
					best_woman_score = score > best_woman_score ? score : best_woman_score;
				}
			}
			else if(best_woman_id >= 0)
			{
				score += pk::rand(200);

				pk::person@ best_woman_person = pk::get_person(best_woman_id);

				int n = score;
				int g = best_woman_score + 250;
				
				if(person.birth - best_woman_person.birth >= 10)
					g+= 500;
				if(person.birth - best_woman_person.birth <= -20)
					g+= 500;

				if(best_woman_person.stat[무장능력_무력] > person.stat[무장능력_무력] + 10)
					g+= 300;
				else if(best_woman_person.stat[무장능력_무력] > person.stat[무장능력_무력] + 5)
					g+= 100;

				g-= 75 - (pk::get_aishou_distance(best_woman_person, person_id) * 15);
				g-= pk::rand(100);

				if(pk::is_like(best_woman_person, person_id))
					g-= 150 * best_woman_person.giri;
				if(pk::is_like(person, best_woman_id))
					g-= 50 * kunshu.giri;
				if(person.character == best_woman_person.character)
					g-= 100;
				if(person.kanshitsu == best_woman_person.kanshitsu)
					g-= 100;	

				result =  n > g && (n-g) > best_man_score;

				if(pk::is_dislike(best_woman_person, person_id))
					result = false;
				if(pk::is_oyako(person, best_woman_person.get_id()) or pk::is_ketsuen(person, best_woman_person.get_id()) )
					result = false;
				if( abs(person.birth - best_woman_person.birth) >= 40)
					result = false;
				if(pk::is_oyako(kunshu, best_woman_id) && kunshu.birth > best_woman_person.birth)
					result = false;

				if(best_man_id == person_id && result == false)
					best_man_id = -1; 

				if(result) best_man_score = (n-g);
			}			

			return result;
		}
	}

	Main main;
}