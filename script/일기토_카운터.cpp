/*
@만든이: 크래픽스
*/

namespace 일기토_카운터
{
	const int KEY = pk::hash("일기토_카운터");
	
	const int 결과_포박 = 0;
	const int 결과_사망 = 1;
	const int 결과_도망 = 2;
	class DuelInfo
	{
		pk::person@ winner;
		pk::person@ loser;
		int year =0 ;
		int month = 0;
		int day = 0;
		pk::city@ city;
		//
		int result;
	}
	
	class ResultInfo
	{
		pk::person@ person;
		int win;
		int lose;
		int 죽임카운트;
		int 죽음카운트;
		int 포박됨카운트;
		int 포박함카운트;
		int 놓침카운트;
		int 도망감카운트;
		
		array<DuelInfo> duels;
	}
	
	
	array<int> 무력경험치;
	array<int> 무장체력;
	array<pk::point> 무장위치;
	
	class Main
	{
		pk::func209_t@ prev_callback_209;
		pk::func258_t@ prev_callback_258;
		Main()
		{
			
			@prev_callback_209 = cast<pk::func209_t@>(pk::get_func(209));
			pk::reset_func(209);
			pk::set_func(209, pk::func209_t(callback209));                // 202 전법 성공 확률


			//@prev_callback_258 = cast<pk::func258_t@>(pk::get_func(258));
			//pk::reset_func(258);
			//pk::set_func(258, pk::func258_t(callback258));                // 202 전법 성공 확률


			pk::bind(171, pk::trigger171_t(부대제거));
			pk::bind(174, pk::trigger174_t(부대행동완료));
			pk::bind(172, pk::trigger172_t(부대좌표변경));
			pk::bind(173, pk::trigger173_t(부대경험치));
			//pk::bind(107, pk::trigger107_t(새날));
			pk::bind(111, pk::trigger111_t(onTurn));


			
			
			
			pk::menu_item 일기토카운터;
			일기토카운터.menu = 2;
			일기토카운터.is_enabled = pk::menu_item_is_enabled_t(isEnabled);
			일기토카운터.get_desc = pk::menu_item_get_desc_t(getDesc_일기토카운터);
			일기토카운터.get_text = pk::menu_item_get_text_t(getText_일기토카운터);
			일기토카운터.handler = pk::menu_item_handler_t(handler_일기토카운터2);
			pk::add_menu_item(일기토카운터);
			
			pk::bind(102, pk::trigger102_t(Init));
			pk::bind(105, pk::trigger105_t(SaveData));
			
		}
		void Init()
		{
			LoadData();
			if(무력경험치.length == 0)
			{

				for(int i =0;i<1100;i++)
				{
					pk::person@ p = pk::get_person(i);
					if(p==null)
						continue;
					무력경험치.insertLast(p.stat_exp[무장능력_무력]);
					//무력경험치[i] = p.stat_exp[무장능력_무력];
					//pk::printf("exp {}\n",무력경험치[i]);
					무장위치.insertLast(p.get_pos());
					무장체력.insertLast(p.hp);
				}
				pk::list<pk::person@> persons포로 = pk::get_person_list(pk::mibun_flags(신분_포로));
				_포로카운트 = persons포로.count;
				_포로리스트 = persons포로;
				pk::list<pk::person@> persons사망= pk::get_person_list(pk::mibun_flags(신분_사망));
				_사망카운트 = persons사망.count;
				_사망자리스트 = persons사망;
			}
		}

		void LoadData()
		{
			while(_duels.length > 0)
				_duels.removeAt(0);
			while(무력경험치.length > 0)
				무력경험치.removeAt(0);
			while(무장체력.length > 0)
				무장체력.removeAt(0);
			while(무장위치.length > 0)
				무장위치.removeAt(0);
			while (_사망자리스트.count > 0)
				_사망자리스트.remove_at(0);
			while (_포로리스트.count > 0)
				_포로리스트.remove_at(0);


			
			int count = int(pk::load(KEY,0,0));
			pk::printf("duel count : {}---------------\n",count);
			int si=1;	
			
			for(int i=0;i<count;i++)
			{
				DuelInfo di;
				int winner = int(pk::load(KEY,si++,-1));
				int loser= int(pk::load(KEY,si++,-1));
				@di.winner = pk::get_person(winner);
				@di.loser = pk::get_person(loser);
				di.year= int(pk::load(KEY,si++,-1));
				di.month= int(pk::load(KEY,si++,-1));
				di.day= int(pk::load(KEY,si++,-1));
				@di.city = pk::get_city(int(pk::load(KEY,si++,-1)));
				di.result= int(pk::load(KEY,si++,-1));
				_duels.insertLast(di);
			}
			
			count = int(pk::load(KEY,si++,0));
			for(int i=0;i<count;i++)			
			{
				int a=int(pk::load(KEY,si++,-1));
				무력경험치.insertLast(a);
			}
			count = int(pk::load(KEY,si++,0));
			for(int i=0;i<count;i++)			
			{
				int a=int(pk::load(KEY,si++,-1));
				무장체력.insertLast(a);
			}
			count = int(pk::load(KEY,si++,0));
			for(int i=0;i<count;i++)			
			{
				int x=int(pk::load(KEY,si++,-1));
				int y=int(pk::load(KEY,si++,-1));
				무장위치.insertLast(pk::point(x,y));
			}
			count = int(pk::load(KEY,si++,0));
			for(int i=0;i<count;i++)			
			{
				pk::person@ person= pk::get_person(int(pk::load(KEY,si++,-1)));
				_포로리스트.add(person);
			}
			_포로카운트=_포로리스트.count;

			count = int(pk::load(KEY,si++,0));
			for(int i=0;i<count;i++)			
			{
				pk::person@ person= pk::get_person(int(pk::load(KEY,si++,-1)));
				_사망자리스트.add(person);
			}
			_사망카운트=_사망자리스트.count;

		}
		void SaveData(int file_id)
		{
			pk::store(KEY,0,_duels.length);
			int li=1;
			for(int i=0;i<_duels.length;i++)
			{
				DuelInfo@ di = _duels[i];
				pk::store(KEY,li++,di.winner.get_id());
				pk::store(KEY,li++,di.loser.get_id());
				pk::store(KEY,li++,di.year);
				pk::store(KEY,li++,di.month);
				pk::store(KEY,li++,di.day);
				pk::store(KEY,li++,di.city.get_id());
				pk::store(KEY,li++,di.result);
			}
			
			pk::store(KEY,li++,무력경험치.length);
			for(int i=0;i<무력경험치.length;i++)
			{
				pk::store(KEY,li++,무력경험치[i]);
			}
			pk::store(KEY,li++,무장체력.length);
			for(int i=0;i<무장체력.length;i++)
			{
				pk::store(KEY,li++,무장체력[i]);
			}
			pk::store(KEY,li++,무장위치.length);
			for(int i=0;i<무장위치.length;i++)
			{
				pk::store(KEY,li++,int(무장위치[i].x));
				pk::store(KEY,li++,int(무장위치[i].y));
			}
			pk::store(KEY,li++,_포로카운트);
			for(int i=0;i<_포로리스트.count;i++)
			{
				pk::store(KEY,li++,_포로리스트[i].get_id());
			}
			pk::store(KEY,li++,_사망카운트);
			for(int i=0;i<_사망자리스트.count;i++)
			{
				pk::store(KEY,li++,_사망자리스트[i].get_id());
			}
			
		}		
		bool isEnabled()
		{
			return true;
		}

		string getDesc_일기토카운터()
		{
			return pk::encode("일기토 통계를 확인합니다.");
		}
		string getText_일기토카운터()
		{
			return pk::encode("일기토카운터");
		}
		
		array<string> 특기설명백업(255);
		array<string> 특기이름백업(255);
		array<int> 특기백업(무장_끝);
		
		
		void Save특기()
		{
			for(int i=0;i<255;i++)
			{
				pk::skill@ s = pk::get_skill(i);
				if(s==null)
					continue;
				특기설명백업[i] = s.desc;
				특기이름백업[i] = s.name;
			}
			
			for(int i=0;i<무장_끝;i++)
			{
				pk::person@ p = pk::get_person(i);
				if(p == null)
					continue;
				특기백업[i] = p.skill;
			}
		}
		void Load특기()
		{
			for(int i=0;i<255;i++)
			{
				pk::skill@ s = pk::get_skill(i);
				if(s==null)
					continue;
				s.desc = 특기설명백업[i];
				s.name = 특기이름백업[i];
			}
			for(int i=0;i<무장_끝;i++)
			{
				pk::person@ p = pk::get_person(i);
				if(p == null)
					continue;
				p.skill = 특기백업[i];
			}
		}
		
		void handler_일기토카운터3()
		{
			array<ResultInfo> ris = makeResult();
			
			while(true)
			{
				int count = pk::min(255, ris.length);
				pk::list<pk::person@> ris2;
				for(int i=0;i<count;i++)
				{
					ResultInfo@ ri0 = ris[i];
					pk::skill@ s = pk::get_skill(i);
					if(s==null)
						continue;
					
					int moo = ri0.person.mibun != 신분_사망 ? ri0.person.stat[무장능력_무력] : ri0.person.base_stat[무장능력_무력];
					
					ri0.person.skill = i;
					string str = pk::format("무력{},\x1b[2x{}\x1b[0x승,\x1b[29x{}\x1b[0x패,{}죽임,{}포박,{}놓침,{}죽음,{}포로,{}도망"
					,moo,ri0.win,ri0.lose,ri0.죽임카운트,ri0.포박함카운트,ri0.놓침카운트,ri0.죽음카운트,ri0.포박됨카운트,ri0.도망감카운트);
					s.desc = pk::encode(str);
					s.name = pk::encode("전적");
					ris2.add(ri0.person);
				}

				pk::list<pk::person@> persons = pk::person_selector(pk::encode("무장 선택"),pk::encode("무장을 선택해주십시오"),ris2,1,1);
				if(persons.count==0)
					return;
				
				ResultInfo@ selected = null;
				for(int i=0;i<count;i++)
				{
					ResultInfo@ ri = ris[i];
					if(ri.person.get_id() == persons[0].get_id())
					{
						@selected = ri;
						break;
					}
				}
				if(selected==null)
					continue;
				
				pk::list<pk::person@> ris3;
				int ii=0;
				int 특기i=0;
				for(int i=0;i<selected.duels.length;i++)
				{
					DuelInfo@ di = selected.duels[i];
					string str;
					string strResult;
					switch(di.result)
					{
						case 결과_포박:strResult="포박";break;
						case 결과_사망:strResult="사망";break;
						case 결과_도망:strResult="도망";break;
					}
					
					pk::person@ p =null;
					if(di.winner.get_id() == selected.person.get_id())
					{
						int moo0= selected.person.mibun != 신분_사망 ? selected.person.stat[무장능력_무력] : selected.person.base_stat[무장능력_무력];
						int moo1= di.loser.mibun != 신분_사망 ? di.loser.stat[무장능력_무력] : di.loser.base_stat[무장능력_무력];
						str=pk::format("\x1b[2x{}\x1b[0x({})VS\x1b[29x{}\x1b[0x({}),승,{},{}년,{}월,{}일,{}",pk::decode(pk::get_name(selected.person)),moo0,pk::decode(pk::get_name(di.loser)),moo1,strResult,di.year,di.month,di.day,pk::decode(pk::get_name(di.city)));
						@p = di.loser;
					}
					else
					{
						int moo0= selected.person.mibun != 신분_사망 ? selected.person.stat[무장능력_무력] : selected.person.base_stat[무장능력_무력];
						int moo1= di.winner.mibun != 신분_사망 ? di.winner.stat[무장능력_무력] : di.winner.base_stat[무장능력_무력];
						str=pk::format("\x1b[29x{}\x1b[0x({})VS\x1b[2x{}\x1b[0x({}),패,{},{}년,{}월,{}일,{}",pk::decode(pk::get_name(selected.person)),moo0,pk::decode(pk::get_name(di.winner)),moo1,strResult,di.year,di.month,di.day,pk::decode(pk::get_name(di.city)));
						@p = di.winner;
					}
	
					bool bFound = false;
					do
					{
						bFound = false;
						for(int j=0;j<ris3.count;j++)
						{
							if(ris3[j].get_id() != p.get_id())
								continue;
							
							@p = pk::get_person(ii++);
							bFound = true;
							break;
						}
					}
					while(bFound);
					p.skill = 특기i;
					pk::get_skill(특기i).name = pk::encode("전적");
					pk::get_skill(특기i).desc = pk::encode(str); 특기i++; 
					
					ris3.add(p);
				}
				
				pk::person_selector(pk::encode("무장 확인"),pk::encode("상세 전적을 확인하십시오"),ris3,0,0);			
			}

		}
		
		bool handler_일기토카운터2()
		{
			try
			{
				Save특기();
				handler_일기토카운터3();
			}
			catch
			{
				Load특기();
			}
			
			Load특기();
			return true;
		}
		
		bool handler_일기토카운터()
		{
			array<ResultInfo> ris = makeResult();

			int si=0;
			ResultInfo@ ri=null;
			while(true)
			{
				array<string> itemArr;
				int count = pk::min(ris.length, si + 4);
				if(si == 0)
					itemArr.insertLast(pk::encode("종료"));
				else
					itemArr.insertLast(pk::encode("뒤로"));
				for (int i = si; i < count; i++)
				{
					ResultInfo@ ri0 = ris[i];
					
					
					string str = pk::format("\x1b[2x{}\x1b[0x,{}승,{}패,{}죽임,{}포박,{}놓침,{}죽음,{}포박됨,{}도망"
					,pk::decode(pk::get_name(ri0.person)),ri0.win,ri0.lose,ri0.죽임카운트,ri0.포박함카운트,ri0.놓침카운트,ri0.죽음카운트,ri0.포박됨카운트,ri0.도망감카운트);
					itemArr.insertLast(pk::encode(str));
				}
				if(si+4 >= ris.length)
					itemArr.insertLast(pk::encode("종료"));
				else
					itemArr.insertLast(pk::encode("다음"));

				int choose = pk::choose(pk::encode("무장을 선택해주십시오"), itemArr);
				if (choose == itemArr.length - 1)
				{
					si = si + 4;
					if (si >= ris.length)
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
					@ri = ris[si+choose-1];
				}
				if(ri==null)
					continue;
				
				
				int si2=0;
				while(true)
				{
					array<string> itemArr2;
					int count = pk::min(ri.duels.length, si2 + 4);
					if(si2 == 0)
						itemArr2.insertLast(pk::encode("종료"));
					else
						itemArr2.insertLast(pk::encode("뒤로"));
					for (int i = si2; i < count; i++)
					{
						DuelInfo@ di = ri.duels[i];
						string str;
						string strResult;
						switch(di.result)
						{
							case 결과_포박:strResult="포박";break;
							case 결과_사망:strResult="사망";break;
							case 결과_도망:strResult="도망";break;
						}
						if(di.winner.get_id() == ri.person.get_id())
							str=pk::format("VS \x1b[2x{}\x1b[0x, 승,{},{}년,{}월,{}일,{}",pk::decode(pk::get_name(di.loser)),strResult,di.year,di.month,di.day,pk::decode(pk::get_name(di.city)));
						else
							str=pk::format("VS \x1b[29x{}\x1b[0x, 패,{},{}년,{}월,{}일,{}",pk::decode(pk::get_name(di.winner)),strResult,di.year,di.month,di.day,pk::decode(pk::get_name(di.city)));
						itemArr2.insertLast(pk::encode(str));
					}
					if(si2+4 >= ri.duels.length)
						itemArr2.insertLast(pk::encode("종료"));
					else
						itemArr2.insertLast(pk::encode("다음"));
					int choose2 = pk::choose(pk::encode("선택해주십시오"), itemArr2);
					if (choose2 == itemArr2.length - 1)
					{
						si2 = si2 + 4;
						if (si2 >= ri.duels.length)
							break;
					}
					else if (choose2 == 0)
					{
						si2 = si2 - 4;
						if (si2 < 0)
							break;
					}
				}
			}//ri
			
			
			return true;
		}
		
		array<ResultInfo> makeResult()
		{
			array<ResultInfo> ris(무장_끝);
			for(int i=0;i<_duels.length;i++)
			{
				DuelInfo@ di = _duels[i];
				
				ResultInfo@ riWinner = ris[di.winner.get_id()];
				ResultInfo@ riLoser= ris[di.loser.get_id()];
				
				
				@riWinner.person = di.winner;
				riWinner.win++;
				riWinner.duels.insertLast(di);
				@riLoser.person = di.loser;
				riLoser.lose++;
				riLoser.duels.insertLast(di);
				switch(di.result)
				{
					case 결과_포박:
					riWinner.포박함카운트++;
					riLoser.포박됨카운트++;
					break;
					case 결과_사망:
					riWinner.죽임카운트++;
					riLoser.죽음카운트++;
					break;
					case 결과_도망:
					riWinner.놓침카운트++;
					riLoser.도망감카운트++;
					break;
				}
			}
			
			array<ResultInfo> ris2;
			for(int i=0;i<ris.length;i++)
			{
				ResultInfo@ ri = ris[i];
				if(ri.person == null)
					continue;
				
				ris2.insertLast(ri);
			}
			
			if(ris2.length > 1)
			{
				ris2.sort(function(a,b){
					if(a.win != b.win)
						return a.win > b.win;
					if(a.lose != b.lose)
						return a.lose < b.lose;
					if(a.죽임카운트 != b.죽임카운트)
						return a.죽임카운트 > b.죽임카운트;
					if(a.포박함카운트 != b.포박함카운트)
						return a.포박함카운트 > b.포박함카운트;
					return a.놓침카운트 > b.놓침카운트;
				});
			}
			
			return ris2;
		}
		array<DuelInfo> _duels;
		
		void 세력변경(pk::person@ person, pk::force@ force)
		{
			//pk::printf("die {},{}\n", getName(person), getName(force));
		}

		void callback209(pk::damage_info& info, pk::unit@ attacker, int tactics_id, const pk::point &in target_pos, int type, int critical, bool ambush)
		{
			prev_callback_209(info,attacker,tactics_id,target_pos,type,critical,ambush);
		}
		
		int callback258(pk::person@ prisoner, const pk::prisoner_info& in info)
		{
			pk::unit@ unit = pk::get_unit(info.target.get_pos());
			if (unit != null && prisoner.hp <= 10)
			{
				pk::person@ p1 = pk::get_person(unit.member[0]);
				int maxExp = p1!=null ? p1.stat_exp[무장능력_무력] - 무력경험치[p1.get_id()] : 0;
				pk::person@ maxPerson = p1;


				pk::person@ p2 = pk::get_person(unit.member[1]);
				if (p2 != null)
				{
					int exp = p2.stat_exp[무장능력_무력] - 무력경험치[p2.get_id()];
					if (exp > maxExp)
					{
						maxExp = exp;
						@maxPerson = p2;
					}
				}
				pk::person@ p3 = pk::get_person(unit.member[2]);
				if (p3 != null)
				{
					int exp = p3.stat_exp[무장능력_무력] - 무력경험치[p3.get_id()];
					if (exp > maxExp)
					{
						maxExp = exp;
						@maxPerson = p3;
					}
				}

				if (체크일기토(maxPerson, prisoner, unit))
				{
					//pk::printf("1:1 simulation {},{}---------------\n", getName(maxPerson), getName(prisoner));
				}

			}

			return prev_callback_258(prisoner,info);
		}
		
		
		
		pk::person@ GetMinHP(pk::unit@ u)
		{
			int minHP = 100000;
			pk::person@ minPerson = null;
			pk::person@ p0 = pk::get_person(u.member[0]);
			if(p0!=null && p0.hp < minHP)
			{
				minHP = p0.hp;
				@minPerson = p0;
			}
			pk::person@ p1 = pk::get_person(u.member[1]);
			if(p1!=null && p1.hp < minHP)
			{
				minHP = p1.hp;
				@minPerson = p1;
			}
			pk::person@ p2 = pk::get_person(u.member[2]);
			if(p2!=null && p2.hp < minHP)
			{
				minHP = p2.hp;
				@minPerson = p2;
			}
			
			return minPerson;
		}
		
		int _포로카운트 = 0;
		int _사망카운트 = 0;
		
		void 새날_포로처리()
		{
			pk::list<pk::person@> persons포로 = pk::get_person_list(pk::mibun_flags(신분_포로));
			int 포로카운트 = persons포로.count;
			if(true or _포로카운트 != 포로카운트)
			{
				for(int i=0;i<persons포로.count;i++)
				{
					pk::person@ p = persons포로[i];
					//if(p.prisoner_timer<=1)
					//	pk::printf("caught timer {},{}\n",p.prisoner_timer,pk::decode(pk::get_name(p)));
					//if(p.prisoner_timer!=1)
					//continue;
					//pk::printf("timer {}\n",p.prisoner_timer);
					
					if(p.hp==100 || (!IsNewCaught(p) && p.prisoner_timer!=0))
						continue;
					if(p.hp > 10)
					{
						//pk::printf("new cahught hp {},{}\n",pk::decode(pk::get_name(p)),p.hp);
						continue;
					}
						
					if(IsAlready(p))
						continue;
						
						
					
					//pk::printf("new cahught {},{}\n",p.prisoner_timer,pk::decode(pk::get_name(p)));
					
					pk::unit@ unit = pk::get_unit(p.get_pos());
					if(unit == null)
					{
						//일기를 이기고 부대가 한턴에 괴멸되면?
						//pk::printf("unit null\n");
						continue;
					}
					pk::person@ p1=pk::get_person(unit.member[0]);
					if(p1==null)
					{
						//pk::printf("p1 null {} {} {} x{},y{}\n",unit.member[0],unit.member[1],unit.member[2],p.get_pos().x,p.get_pos().y);
						continue;
					}
						
					
					int maxExp =  p1.stat_exp[무장능력_무력] - 무력경험치[p1.get_id()];
					pk::person@ maxPerson = p1;
					
					
					pk::person@ p2 = pk::get_person(unit.member[1]);
					if(p2!=null)
					{
						int exp =  p2.stat_exp[무장능력_무력] - 무력경험치[p2.get_id()];
						if(exp > maxExp)
						{
							maxExp = exp;
							@maxPerson = p2;
						}
					}
					pk::person@ p3 = pk::get_person(unit.member[2]);
					if(p3!=null)
					{
						int exp =  p3.stat_exp[무장능력_무력] - 무력경험치[p3.get_id()];
						if(exp > maxExp)
						{
							maxExp = exp;
							@maxPerson = p3;
						}
					}
					
					//pk::printf("maxExp {},{}\n",pk::decode(pk::get_name(maxPerson)), maxExp);
					
					if(체크일기토(maxPerson,p,unit))
					{
						//pk::printf("1:1 {},{},hp{},hp{},{}--------------------\n",pk::decode(pk::get_name(maxPerson)),pk::decode(pk::get_name(p)),maxPerson.hp,p.hp,결과_포박);
						DuelInfo di;
						@di.winner= maxPerson;
						@di.loser = p;
						p.prisoner_timer = 1;//연속포박을 막기위해 이렇게 처리 부작용이 있을까?
						di.year = pk::get_year();
						di.month = pk::get_month();
						di.day = pk::get_day();
						int city = pk::get_city_id(p.get_pos());
						@di.city = pk::get_city(city);
						di.result = 결과_포박;
						_duels.insertLast(di);
						history(di);
					}
					else 
					{
						//일기토에서 도망갔는데 바로 다른무장에게 잡혔을때
						도망자처리(p, null);
					}
				}
			}

			_포로리스트 = persons포로;
			_포로카운트 = 포로카운트;
		}

		bool IsNewCaught(pk::person@ p)
		{
			//if(p.cause_of_death == 사인_자연사)
			//	return false;

			for(int i=0;i<_포로리스트.count;i++)
			{
				pk::person@ p2 = _포로리스트[i];
				if(p2.get_id() == p.get_id())
					return false;
			}
			return true;
		}

		
		bool IsNewDead(pk::person@ p)
		{
			//if(p.cause_of_death == 사인_자연사)
			//	return false;

			for(int i=0;i<_사망자리스트.count;i++)
			{
				pk::person@ p2 = _사망자리스트[i];
				if(p2.get_id() == p.get_id())
					return false;
			}
			return true;
		}
		
		pk::list<pk::person@> _사망자리스트;
		pk::list<pk::person@> _포로리스트;
		void 새날_사망처리()
		{
			pk::list<pk::person@> persons사망= pk::get_person_list(pk::mibun_flags(신분_사망));
			int 사망카운트 = persons사망.count;
			if(사망카운트 == _사망카운트)
				return;
			
				
			for(int i=0;i<persons사망.count;i++)
			{
				pk::person@ p = persons사망[i];
				if(!IsNewDead(p))
					continue;
				
				사망자_처리(p,결과_사망);
			}
			
			
			_사망카운트 = 사망카운트;
			_사망자리스트 = persons사망;

		
		}
		
		bool 체크일기토(pk::person@ winner, pk::person@ loser , pk::unit@ winnerUnit)
		{
			if(winner!=null && loser!=null && winner.get_force_id() == loser.get_force_id())
				return false;
			
			//pk::printf("check0 {},{}\n", winner.stat_exp[무장능력_무력] - 무력경험치[winner.get_id()], pk::decode(pk::get_name(winner)));

			//if (winner.stat_exp[무장능력_무력] - 무력경험치[winner.get_id()] < 1)
			if (winner.stat_exp[무장능력_무력] - 무력경험치[winner.get_id()] < 4)
			{
				return false;
			}
			if(winner.stat_exp[무장능력_무력] - 무력경험치[winner.get_id()] >= 10)
			{
				//pk::printf("1:1 ok {},{}\n",pk::decode(pk::get_name(winner)),winner.stat_exp[무장능력_무력] - 무력경험치[winner.get_id()]);
				return true;
			}
			//pk::printf("check {},{}\n", winner.stat_exp[무장능력_무력] - 무력경험치[winner.get_id()], pk::decode(pk::get_name(winner)));
			
			if(winnerUnit!=null && pk::get_member_count(winnerUnit) >=2)
			{
				pk::person@ p0 = (winnerUnit.member[0] >=0 && winnerUnit.member[0]<무력경험치.length) ? pk::get_person(winnerUnit.member[0]) : null;
				pk::person@ p1 = (winnerUnit.member[1] >=0 && winnerUnit.member[1]<무력경험치.length) ? pk::get_person(winnerUnit.member[1]) : null;
				pk::person@ p2 = (winnerUnit.member[2] >=0 && winnerUnit.member[2]<무력경험치.length) ? pk::get_person(winnerUnit.member[2]) : null;
				float exp0 = float(p0!=null ? p0.stat_exp[무장능력_무력] - 무력경험치[p0.get_id()] : -1);
				float exp1 = float(p1!=null ? p1.stat_exp[무장능력_무력] - 무력경험치[p1.get_id()] : -1);
				float exp2 = float(p2!=null ? p2.stat_exp[무장능력_무력] - 무력경험치[p2.get_id()] : -1);
				bool 지도0 = p0!=null ? pk::has_skill(p0,특기_지도) : false;
				bool 지도1 = p1!=null ? pk::has_skill(p1,특기_지도) : false;
				bool 지도2 = p2!=null ? pk::has_skill(p2,특기_지도) : false;
				if(지도0) 
				{
					exp1 = exp1 / 2.0;
					exp2 = exp2 / 2.0;
				}
				if(지도1)
				{
					exp0 = exp0 / 2.0;
					exp2 = exp2 / 2.0;
				}
				if(지도2)
				{
					exp0 = exp0 / 2.0;
					exp1 = exp1 / 2.0;
				}
				
				if(pk::get_member_count(winnerUnit) ==3)
				{
					if(exp0!=exp1 || exp1!=exp2 || exp0!=exp2)
					{
						//pk::printf("1:1 ok {},{},{},{}\n", pk::decode(pk::get_name(winner)),exp0,exp1,exp2);
						return true;
					}
					else
					{
						//pk::printf("failed exp3 {},{},{},{}\n", pk::decode(pk::get_name(winner)),exp0,exp1,exp2);
						return false;
					}
						
				}
				else 
				{
					if(exp0==-1 && exp1 != exp2)
					{
						//pk::printf("1:1 ok {},{},{},{}\n", pk::decode(pk::get_name(winner)),exp0,exp1,exp2);
						return true;
					}						
						
					else if(exp1==-1 && exp0 != exp2)
					{
						//pk::printf("1:1 ok {},{},{},{}\n", pk::decode(pk::get_name(winner)),exp0,exp1,exp2);
						return true;
					}
						
					else if(exp2==-1 && exp0 != exp1)
					{
						//pk::printf("1:1 ok {},{},{},{}\n", pk::decode(pk::get_name(winner)),exp0,exp1,exp2);
						return true;
					}
					else 
					{
						//pk::printf("failed exp2 {},{},{}\n", exp0,exp1,exp2);
						return false;
					}
						
				}
			}
			else
			{
				bool b=winner.hp != 100 || (loser!=null && loser.hp != 100);
				//if(!b)
				//	pk::printf("failed hp {},{},{}\n",pk::decode(pk::get_name(winner)),winner.hp, loser!=null ? loser.hp : -1);
				//else
				//	pk::printf("1:1 ok {},hp{},hp{}\n)",pk::decode(pk::get_name(winner)),winner.hp, loser!=null ? loser.hp : -1);
				return b;
			}
		}
		
		void 사망자_처리(pk::person@ p,int resultType)
		{
			//사망자는 본인이 확실.
			//pk::unit@ unit0 = pk::get_unit(pk::get_unit_id(p));
			//if(unit0 !=null && GetMinHP(unit0).get_id() != p.get_id())
			//	return;
		
			//hp가 이미 깍여있는상황에서 공격받고 죽으면, 좀 위험하다. 
			//일기토에서 져서 죽는 상황에서는 hp가 1이거나 10정도 이하일것같은데, 도망가다가 따라 잡히는 경우도 있고, 
			if(p.hp >= 10)
			{
				//pk::printf("dead return hp {}\n",pk::decode(pk::get_name(p)),p.hp);
				return;
			}

			//pk::printf("new dead{}\n", getName(p));
		
			array<DuelInfo> dis;
			for(int j=0;j<무력경험치.length;j++)
			{
				pk::person@ p2 = pk::get_person(j);
				pk::unit@ unit = pk::get_unit(pk::get_unit_id(p2));
					
				bool bRange = pk::is_in_range(무장위치[p.get_id()], 3, p2.get_pos());
				//bRange = true;
				if(bRange && 체크일기토(p2,p,unit)) 
				{
					bool bFound = IsAlready(p2);
					//직전 일기토 기록에 없고,
					if(!bFound) 
					{
						//pk::printf("1:1 {},{},{}---------------------------\n",pk::decode(pk::get_name(p2)),pk::decode(pk::get_name(p)),resultType);
						
						DuelInfo di;
						@di.winner= p2;
						@di.loser = p;
						di.year = pk::get_year();
						di.month = pk::get_month();
						di.day = pk::get_day();
						int city = pk::get_city_id(무장위치[p.get_id()]);
						@di.city = pk::get_city(city);
						di.result = resultType;
						dis.insertLast(di);
					}
				}
			}

			DuelInfo@ ndi = null;
			if(dis.length == 1)
			{
				_duels.insertLast(dis[0]);
				@ndi =dis[0];
				history(dis[0]);
			}
				
			else if(dis.length > 1)
			{
				int minDist = 10000;
				DuelInfo@ minDi=null;
				pk::unit@ minUnit = null;
				
				for(int i=0;i<dis.length;i++)
				{
					pk::unit@ unit2 = pk::get_unit(pk::get_unit_id(dis[i].winner)); //공격자가 괴멸될때를 대비해서	
					int dist = pk::get_distance(dis[i].winner.get_pos(),무장위치[p.get_id()]);
					if(dist == minDist)
					{
						if(minUnit!=null && unit2!=null && minUnit.get_id() == unit2.get_id())
						{
							int off0 = minDi.winner.stat_exp[무장능력_무력] - 무력경험치[minDi.winner.get_id()];
							int off1 = dis[i].winner.stat_exp[무장능력_무력] - 무력경험치[dis[i].winner.get_id()];
							if(off1 > off0) 
							{
								minDist = dist;
								@minDi = dis[i];
								@minUnit = unit2;
							}
						}
					}
					else if(dist<minDist)
					{
						minDist = dist;
						@minDi = dis[i];
						@minUnit = unit2;
					}
				}
				@ndi =minDi;
				_duels.insertLast(minDi);
				history(minDi);
			}
			//if(ndi!=null)
			//	pk::printf("1:1 {},{},hp{},hp{},{}---------------------------\n",pk::decode(pk::get_name(ndi.winner)),pk::decode(pk::get_name(p)),ndi.winner.hp,p.hp,resultType);
			
		}
		
		
		void history(DuelInfo@ di)
		{
			array<ResultInfo> ris=makeResult();
			
			ResultInfo@ riWinner = null;
			ResultInfo@ riLoser = null;
			
			string strType;
			switch(di.result)
			{
				case 결과_도망:strType="도망";break;
				case 결과_포박:strType="포박";break;
				case 결과_사망:strType="사망";break;
			}
			
			
			for(int i=0;i<ris.length;i++)
			{
				ResultInfo@ ri = ris[i];
				if(ri.person.get_id() == di.winner.get_id())
				{
					@riWinner = ri;
				}
				if(ri.person.get_id() == di.loser.get_id())
				{
					@riLoser = ri;
				}
			}
			
			//if(riWinner!=null)
			//	pk::printf("die winner\n",pk::decode(pk::get_name(riWinner.person)));
			//if(riLoser!=null)
			//	pk::printf("die loser\n");
			
			
			string str0 = pk::format("\x1b[2x{}\x1b[0x({}) VS \x1b[29x{}\x1b[0x({}),{},{}승{}패,{}승{}패",
			pk::decode(pk::get_name(di.winner)),di.winner.stat[무장능력_무력],pk::decode(pk::get_name(di.loser)),di.loser.stat[무장능력_무력],
			strType,riWinner.win,riWinner.lose,riLoser.win,riLoser.lose);
			pk::history_log(di.winner.get_pos(), pk::get_force(di.winner.get_force_id()).color, pk::encode(str0));
		}
	
		
		bool IsAlready(pk::person@ p2)
		{
			pk::unit@ unit = pk::get_unit(pk::get_unit_id(p2));
			for(int k=_duels.length-1;k>=0;k--)
			{
				DuelInfo di = _duels[k];
				if(pk::get_year() == di.year and pk::get_month() == di.month and pk::get_day() == di.day)
				{
					if(unit == null)
					{
						if(di.winner.get_id() == p2.get_id())
						{
							//pk::printf("winner found{}\n",pk::decode(pk::get_name(di.winner)));
							return true;
						}
						if(di.loser.get_id() == p2.get_id())
						{
							p2.prisoner_timer = 1;
							//pk::printf("loser found{}\n",pk::decode(pk::get_name(di.loser)));
							return true;
						}
					}
					else
					{
						if(di.winner.get_id() ==  unit.member[0] || di.winner.get_id() ==  unit.member[1] || di.winner.get_id() ==  unit.member[2])
						{
							//pk::printf("winner found{}\n",pk::decode(pk::get_name(di.winner)));
							return true;
						}
						if(di.loser.get_id() ==  unit.member[0] || di.loser.get_id() ==  unit.member[1] || di.loser.get_id() ==  unit.member[2])
						{
							p2.prisoner_timer = 1;
							//pk::printf("loser found{}\n",pk::decode(pk::get_name(di.loser)));
							return true;
						}
							
					}
				}
			}
			return false;
		}
		
		void 도망자처리(pk::person@ p, pk::unit@ unit)
		{
			if (IsAlready(p))
				return;

			//pk::printf("escaped {}\n", pk::decode(pk::get_name(p)));
			bool bFoundWinner = false;
			array<DuelInfo> dis;
			for (int j = 0; j < 무장체력.length; j++)
			{
				pk::person@ p2 = pk::get_person(j);
				pk::unit@ unit2 = pk::get_unit(pk::get_unit_id(p2)); //공격자가 괴멸될때를 대비해서

				bool bFound = IsAlready(p2);
				pk::point pt0 = unit != null ? unit.get_pos() : 무장위치[p.get_id()];
				//pk::point pt0 = 무장위치[p.get_id()];
				pk::point pt1 = unit2 != null ? unit2.get_pos() : 무장위치[p2.get_id()];
				bool bRange = pk::is_in_range(pt0, 4, pt1);
				//auto obj = pk::get_hex_object(pt0);
				//if(obj!=null && obj.get_type_id() == 5)
				//	bRange = true;

				//bRange = true;
				if (!bFound && bRange && 체크일기토(p2, p, pk::get_unit(pk::get_unit_id(p2))))
				{
					//pk::printf("hp {},{},{},{}\n", pk::decode(pk::get_name(p)), p.hp, pk::decode(pk::get_name(p2)), p2.hp);
					DuelInfo di;
					@di.winner = p2.hp > p.hp ? p2 : p;
					@di.loser = p.hp < p2.hp ? p : p2;
					di.year = pk::get_year();
					di.month = pk::get_month();
					di.day = pk::get_day();
					int city = pk::get_city_id(무장위치[p.get_id()]);
					@di.city = pk::get_city(city);
					di.result = 결과_도망;
					dis.insertLast(di);
					bFoundWinner = true;
				}
			}
			DuelInfo@ ndi = null;
			if (dis.length == 0) //조건을 약화해서 찾는다
			{
				//pk::printf("not found-----------------------\n");
			}
			else if (dis.length == 1)
			{
				_duels.insertLast(dis[0]);
				history(dis[0]);
				@ndi = dis[0];
			}
			else
			{
				int minDist = 10000;
				DuelInfo@ minDi = null;
				pk::unit@ minUnit = null;
				for (int i = 0; i < dis.length; i++)
				{
					pk::unit@ unit2 = pk::get_unit(pk::get_unit_id(dis[i].winner)); //공격자가 괴멸될때를 대비해서	
					pk::point pos = unit != null ? unit.get_pos() : 무장위치[p.get_id()];
					pk::point pos2 = unit2 != null ? unit2.get_pos() : 무장위치[dis[i].winner.get_id()];

					int dist = pk::get_distance(pos2, pos);

					//pk::printf("duel dist{},{} \n", pk::decode(pk::get_name(dis[i].winner)), dist);
					if (dist == minDist)
					{
						if (minUnit != null && unit2 != null && minUnit.get_id() == unit2.get_id())
						{
							int off0 = minDi.winner.stat_exp[무장능력_무력] - 무력경험치[minDi.winner.get_id()];
							int off1 = dis[i].winner.stat_exp[무장능력_무력] - 무력경험치[dis[i].winner.get_id()];
							if (off1 > off0)
							{
								minDist = dist;
								@minDi = dis[i];
								@minUnit = unit2;
							}
						}
					}
					else if (dist < minDist)
					{
						minDist = dist;
						@minDi = dis[i];
						@minUnit = unit2;
					}
				}
				@ndi = minDi;
				_duels.insertLast(minDi);
				history(minDi);

			}
			//if (ndi != null)
			//	pk::printf("1:1 {},{},hp{},hp{},{}---------------------------\n"
			//		, pk::decode(pk::get_name(ndi.winner)), pk::decode(pk::get_name(p)), ndi.winner.hp, p.hp, 결과_도망);
		}

		void 새날_도망자처리()
		{
			for(int i=0;i<무장체력.length;i++)
			{
				pk::person@ p=pk::get_person(i);
				if(p.mibun == 신분_사망)
					continue;
				
				pk::unit@ unit = pk::get_unit(pk::get_unit_id(p));
				
				//if(p.hp!=100)
				//	pk::printf("hp {},{}->{}\n",pk::decode(pk::get_name(p)),무장체력[i],p.hp);
				if((p.hp==1 || (p.hp - 무장체력[i] < 0 and p.hp < 20)) and (unit==null || (unit!=null && GetMinHP(unit).get_id() == p.get_id()))) // 도망자
				{
					도망자처리(p, unit);
				}//도망자
			}//무장

		}
		
		
		void 부대제거(pk::unit@ unit, int type)
		{
			//위너가 제거되는경우, 루저는 살아있으니깐, 새날로직이 돌아간다.
			//신분이 포로가 되고나서 무력겸헝치가 업데이트되는듯하다 따라서 못잡는다.
			if(unit.member[0] >=0 && unit.member[0] < 무력경험치.length)
			{
				pk::person@ p=pk::get_person(unit.member[0]);
				if(체크일기토(pk::get_person(unit.member[0]),null, unit))
					새날();
				//else if((pk::get_member_count(unit)!= 1 or (pk::get_member_count(unit)==1 && p.mibun != 신분_포로 && p.mibun != 신분_사망))
				//	and p!=null and p.hp - 무장체력[p.get_id()] < 0 and p.hp < 20)
				//	새날();
			}
			if(unit.member[1] >=0 && unit.member[1] < 무력경험치.length)
			{
				pk::person@ p=pk::get_person(unit.member[1]);
				if(체크일기토(pk::get_person(unit.member[1]),null, unit))
					새날();
				//else if((pk::get_member_count(unit)!= 1 or (pk::get_member_count(unit)==1 && p.mibun != 신분_포로 && p.mibun != 신분_사망))
				//	and p!=null and p.hp - 무장체력[p.get_id()] < 0 and p.hp < 20)
				//	새날();
			}
			if(unit.member[2] >=0 && unit.member[2] < 무력경험치.length)
			{
				pk::person@ p=pk::get_person(unit.member[2]);
				if(체크일기토(pk::get_person(unit.member[2]),null, unit))
					새날();
				//else if((pk::get_member_count(unit)!= 1 or(pk::get_member_count(unit)==1 && p.mibun != 신분_포로 && p.mibun != 신분_사망))
				//	and p!=null and p.hp - 무장체력[p.get_id()] < 0 and p.hp < 20)
				//	새날();
			}
		}

		void onTurn(pk::force@ force)
		{
			새날();
		}
		void 새날()
		{
			새날_포로처리();
			새날_사망처리();
			새날_도망자처리();
			


			for(int i =0;i<무력경험치.length;i++)
			{
				pk::person@ p = pk::get_person(i);
				if(p==null)
					continue;
				
				int off = p.stat_exp[무장능력_무력]-무력경험치[i];
				if(off>=10 && !IsAlready(p))
				{
					//pk::printf("miss {},{}\n", pk::decode(pk::get_name(p)),off);
				}
				
				
				무력경험치[i] = p.stat_exp[무장능력_무력];
				무장위치[i] = p.get_pos();
				무장체력[i] = p.hp;
			}
			
			pk::list<pk::person@> persons포로 = pk::get_person_list(pk::mibun_flags(신분_포로));
			_포로카운트 = persons포로.count;
			_포로리스트 = persons포로;
			pk::list<pk::person@> persons사망= pk::get_person_list(pk::mibun_flags(신분_사망));
			_사망카운트 = persons사망.count;
			_사망자리스트 = persons사망;
			
		}


		void 부대행동완료(pk::unit@ unit)
		{
			부대제거(unit,0);		
		}

		void 부대좌표변경(pk::unit@ unit, const pk::point &in pt)
		{
			if(unit.member[0] >=0 and unit.member[0] < 무장위치.length) 
				무장위치[unit.member[0]] = pt;
			if(unit.member[1] >=0 and unit.member[1] < 무장위치.length)
				무장위치[unit.member[1]] = pt;
			if(unit.member[2] >=0 and unit.member[2] < 무장위치.length)
				무장위치[unit.member[2]] = pt;
				
		}

		void 부대경험치(pk::unit@ unit, int type)
		{
			//부대제거(unit,type);		
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
