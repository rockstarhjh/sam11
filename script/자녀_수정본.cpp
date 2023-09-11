namespace 자녀_수정 {
	class Main {
		Main() {
			pk::bind(111, pk::trigger111_t(callback));
		}

		pk::person@ father;
		pk::person@ mother;

		// 남성이름 예시(54개)
		array<string> mei_m = {"율", "준", "윤", "건", "현", "산", "찬", "진", "원", "결", "환", "강", "훈", "단", "한", "선", "호", "담", "수", "유", "신", "휘", "정", "온", "훤", "안", "비", "영", "도", "인", "후", "운", "헌", "랑", "성", "주", "우", "경", "승", "란", "송", "웅", "본", "석", "명", "탄", "해", "상", "금", "이", "규", "서", "류", "지"};
		// 여성이름 예시(17개)
		array<string> mei_w = {"솔", "민", "설", "은", "린", "빈", "연", "희", "비", "홍", "서", "선", "이", "정", "주", "영", "교"};
		
		// 무장 출현에 걸리는 시간 설정(최솟값 : 1)
		int 무장출현 = 15;  //원본 15년

		void callback(pk::force@ force){
			for (int i = 0; i < 무장_끝; i++) {
				pk::person@ person = pk::get_person(i);
				if (person.sex == 성별_여) {
					if (!pk::is_alive(person) || pk::is_mitoujou(person)) continue;
					if (person.get_force_id() != force.get_id()) continue;
					if (!check_fuufu(person)) continue;
					if (father.get_force_id() != mother.get_force_id()) continue;
					if (check_child()) continue;     //원본: if(check_child()) continue;
					if (!(getEmptyPerson() is null)) {
						make_child();
					}
				}
			}
		}

		bool check_fuufu(pk::person@ person) {
			for (int i = 0; i < 무장_끝; i++) {
				if (pk::is_fuufu(person, i)) {
					@father = pk::get_person(i);
					@mother = person;
					return true;
				}
			}
			return false;
		}




		bool check_child()
		{
			pk::list<pk::person@> list_oyako;
			for (int k = 0; k < 무장_끝; k++)
			{
				pk::person@ 자녀 = pk::get_person(k);
				if (pk::is_oyako(father, k))
					list_oyako.add(자녀);
			}
			{
				if (list_oyako.count <= 1) //최대 2명 - 3명으로 하면 너무 많은 무장 생성
					return false;
			}
			return true;
		}

		//원본
		/* bool check_child() {

			for (int i = 0; i < 무장_끝; i++)
			{
				pk::person@ 자녀 = pk::get_person(i);
			    if (pk::is_oyako(father, i) && (father.generation == 자녀.generation - 1)) return true;
				if (pk::is_oyako(mother, i) && (mother.generation == 자녀.generation - 1)) return true;
			}
			return false;
		}
		*/

		void make_child() {
			pk::person@ child = getEmptyPerson();

			if(pk::rand_bool(50)) child.sex = 성별_남;
			else child.sex = 성별_여;

			child.sei = father.sei;
			if (child.sex == 성별_남) {
				child.mei = pk::u8encode(mei_m[pk::rand(54)]);
				child.face = pk::rand(100) + 2000;
				child.tone = pk::rand(11) + 5;
				child.voice = pk::rand(4);
			}
			else {
				child.mei = pk::u8encode(mei_w[pk::rand(17)]);
				child.face = pk::rand(65) + 2100;
				child.tone = pk::rand(4) + 1;
				child.voice = pk::rand(2) + 4;
			}

			child.birth = pk::get_year() - 15;
			child.appearance = pk::get_year() + 무장출현; //자녀들이 동시에 나오는게 싫으면 + rand(x) 값을 넣으면 됨
			child.death = pk::min(353, child.birth + 70 + pk::rand(20));
			child.birthplace = pk::rand(father.get_district_id());
			child.wadai = pk::rand(화제_끝);
			child.giri = pk::rand(의리_끝);
			child.ambition = pk::rand(야망_끝);
			child.promotion = pk::rand(기용_끝);
			child.character = pk::rand(성격_끝);
			child.kanshitsu = pk::rand(한실_끝);
			child.strategic_tendency = pk::rand(전략경향_끝);
			child.local_affiliation = pk::rand(지역집착_끝);

			child.ketsuen = father.ketsuen;
			child.father = father.get_id();
			child.mother = mother.get_id();
			child.generation = father.generation + 1;
			child.aishou = (father.aishou + mother.aishou) / 2 + pk::rand(11) - 5;
			child.mibun = 신분_미등장;
			child.flags = 184;
			child.loyalty = 120;
			child.spouse = -1;
			child.gikyoudai = -1;

			for (int i = 0; i < 5; i++) {
				child.liked[i] = -1;
				child.disliked[i] = -1;
			}
			child.liked[0] = father.get_id();
			child.liked[1] = mother.get_id();

			if (father.tekisei[병종_기병] > 2 || mother.tekisei[병종_기병] > 2) child.tekisei[병종_기병] = pk::rand(3) + 1;
			else child.tekisei[병종_기병] = pk::rand(3);
			if (father.tekisei[병종_창병] > 2 || mother.tekisei[병종_창병] > 2) child.tekisei[병종_창병] = pk::rand(3) + 1;
			else child.tekisei[병종_창병] = pk::rand(3);
			if (father.tekisei[병종_극병] > 2 || mother.tekisei[병종_극병] > 2) child.tekisei[병종_극병] = pk::rand(3) + 1;
			else child.tekisei[병종_극병] = pk::rand(3);
			if (father.tekisei[병종_노병] > 2 || mother.tekisei[병종_노병] > 2) child.tekisei[병종_노병] = pk::rand(3) + 1;
			else child.tekisei[병종_노병] = pk::rand(3);
			if (father.tekisei[병종_병기] > 2 || mother.tekisei[병종_병기] > 2) child.tekisei[병종_병기] = pk::rand(3) + 1;
			else child.tekisei[병종_병기] = pk::rand(3);
			if (father.tekisei[병종_수군] > 2 || mother.tekisei[병종_수군] > 2) child.tekisei[병종_수군] = pk::rand(3) + 1;
			else child.tekisei[병종_수군] = pk::rand(3);

			int father_best_stat = get_best_stat(father);
			int mother_best_stat = get_best_stat(mother);
			for (int i = 0; i < 무장능력_끝; i++) {
				if (father_best_stat == i && mother_best_stat == i) child.base_stat[i] = pk::max(pk::min(pk::max(father.base_stat[i], mother.base_stat[i]) + pk::rand(15), 100), 0);
				else if (father_best_stat == i) child.base_stat[i] = pk::max(pk::min(father.base_stat[i] + pk::rand(22) - 10, 100), 0);
				else if (mother_best_stat == i) child.base_stat[i] = pk::max(pk::min(mother.base_stat[i] + pk::rand(22) - 10, 100), 0);
				else child.base_stat[i] = pk::max(pk::min((father.base_stat[i] + mother.base_stat[i]) / 2 + pk::rand(22) - 10, 100), 0);
			}

			if(pk::max(child.base_stat[무장능력_통솔], child.base_stat[무장능력_무력]) > pk::max(child.base_stat[무장능력_지력], child.base_stat[무장능력_정치])) child.skill = pk::rand(53);
			else child.skill = pk::rand(46) + 53;

			if (pk::rand_bool(child.base_stat[무장능력_지력])) child.wajutsu_daikatsu = true;
			if (pk::rand_bool(child.base_stat[무장능력_지력])) child.wajutsu_kiben = true;
			if (pk::rand_bool(child.base_stat[무장능력_지력])) child.wajutsu_mushi = true;
			if (pk::rand_bool(child.base_stat[무장능력_지력])) child.wajutsu_chinsei = true;
			if (pk::rand_bool(child.base_stat[무장능력_지력])) child.wajutsu_gyakujou = true;
			
			if (child.sex == 성별_남) {
				if(pk::max(child.base_stat[무장능력_통솔], child.base_stat[무장능력_무력]) > pk::max(child.base_stat[무장능력_지력], child.base_stat[무장능력_정치])) {
					child.body[0] = 102;
					child.body[1] = 84;
					child.body[2] = 85;
					child.body[3] = 85;
					child.body[4] = 85;
					child.body[5] = 85;
				}
				else {
					child.body[0] = 92;
					child.body[1] = 93;
					child.body[2] = 97;
					child.body[3] = -1;
					child.body[4] = 97;
					child.body[5] = 97;
				}
			}
			else {
				if(pk::max(child.base_stat[무장능력_통솔], child.base_stat[무장능력_무력]) > pk::max(child.base_stat[무장능력_지력], child.base_stat[무장능력_정치])) {
					child.skeleton = 1;
					child.body[0] = 77;
					child.body[1] = 77;
					child.body[2] = 77;
					child.body[3] = 77;
					child.body[4] = 77;
					child.body[5] = 77;
				}
				else {
					child.skeleton = 1;
					child.body[0] = 90;
					child.body[1] = 90;
					child.body[2] = 90;
					child.body[3] = 90;
					child.body[4] = 90;
					child.body[5] = 90;
				}
			}
			
			child.update();
		}

		int get_best_stat(pk::person@ person) {
			int best_stat = 0;
			for (int i = 1; i < 무장능력_끝; i++) {
				if (person.base_stat[best_stat] < person.base_stat[i]) best_stat = i;
			}
			return best_stat;
		}

		pk::person@ getEmptyPerson() {
			for (int i = 1; i < 700; i++) {
				pk::person@ child = pk::get_person(i);
				switch (child.mibun) {
					case 신분_없음:
					case 신분_사망:
						return child;
				}
			}
			return null;
		} 
	}

	Main main;
}