/*
@������: ũ���Ƚ�
*/

namespace �ϱ���_ī����
{
	const int KEY = pk::hash("�ϱ���_ī����");
	
	const int ���_���� = 0;
	const int ���_��� = 1;
	const int ���_���� = 2;
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
		int ����ī��Ʈ;
		int ����ī��Ʈ;
		int ���ڵ�ī��Ʈ;
		int ������ī��Ʈ;
		int ��ħī��Ʈ;
		int ������ī��Ʈ;
		
		array<DuelInfo> duels;
	}
	
	
	array<int> ���°���ġ;
	array<int> ����ü��;
	array<pk::point> ������ġ;
	
	class Main
	{
		pk::func209_t@ prev_callback_209;
		pk::func258_t@ prev_callback_258;
		Main()
		{
			
			@prev_callback_209 = cast<pk::func209_t@>(pk::get_func(209));
			pk::reset_func(209);
			pk::set_func(209, pk::func209_t(callback209));                // 202 ���� ���� Ȯ��


			//@prev_callback_258 = cast<pk::func258_t@>(pk::get_func(258));
			//pk::reset_func(258);
			//pk::set_func(258, pk::func258_t(callback258));                // 202 ���� ���� Ȯ��


			pk::bind(171, pk::trigger171_t(�δ�����));
			pk::bind(174, pk::trigger174_t(�δ��ൿ�Ϸ�));
			pk::bind(172, pk::trigger172_t(�δ���ǥ����));
			pk::bind(173, pk::trigger173_t(�δ����ġ));
			//pk::bind(107, pk::trigger107_t(����));
			pk::bind(111, pk::trigger111_t(onTurn));


			
			
			
			pk::menu_item �ϱ���ī����;
			�ϱ���ī����.menu = 2;
			�ϱ���ī����.is_enabled = pk::menu_item_is_enabled_t(isEnabled);
			�ϱ���ī����.get_desc = pk::menu_item_get_desc_t(getDesc_�ϱ���ī����);
			�ϱ���ī����.get_text = pk::menu_item_get_text_t(getText_�ϱ���ī����);
			�ϱ���ī����.handler = pk::menu_item_handler_t(handler_�ϱ���ī����2);
			pk::add_menu_item(�ϱ���ī����);
			
			pk::bind(102, pk::trigger102_t(Init));
			pk::bind(105, pk::trigger105_t(SaveData));
			
		}
		void Init()
		{
			LoadData();
			if(���°���ġ.length == 0)
			{

				for(int i =0;i<1100;i++)
				{
					pk::person@ p = pk::get_person(i);
					if(p==null)
						continue;
					���°���ġ.insertLast(p.stat_exp[����ɷ�_����]);
					//���°���ġ[i] = p.stat_exp[����ɷ�_����];
					//pk::printf("exp {}\n",���°���ġ[i]);
					������ġ.insertLast(p.get_pos());
					����ü��.insertLast(p.hp);
				}
				pk::list<pk::person@> persons���� = pk::get_person_list(pk::mibun_flags(�ź�_����));
				_����ī��Ʈ = persons����.count;
				_���θ���Ʈ = persons����;
				pk::list<pk::person@> persons���= pk::get_person_list(pk::mibun_flags(�ź�_���));
				_���ī��Ʈ = persons���.count;
				_����ڸ���Ʈ = persons���;
			}
		}

		void LoadData()
		{
			while(_duels.length > 0)
				_duels.removeAt(0);
			while(���°���ġ.length > 0)
				���°���ġ.removeAt(0);
			while(����ü��.length > 0)
				����ü��.removeAt(0);
			while(������ġ.length > 0)
				������ġ.removeAt(0);
			while (_����ڸ���Ʈ.count > 0)
				_����ڸ���Ʈ.remove_at(0);
			while (_���θ���Ʈ.count > 0)
				_���θ���Ʈ.remove_at(0);


			
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
				���°���ġ.insertLast(a);
			}
			count = int(pk::load(KEY,si++,0));
			for(int i=0;i<count;i++)			
			{
				int a=int(pk::load(KEY,si++,-1));
				����ü��.insertLast(a);
			}
			count = int(pk::load(KEY,si++,0));
			for(int i=0;i<count;i++)			
			{
				int x=int(pk::load(KEY,si++,-1));
				int y=int(pk::load(KEY,si++,-1));
				������ġ.insertLast(pk::point(x,y));
			}
			count = int(pk::load(KEY,si++,0));
			for(int i=0;i<count;i++)			
			{
				pk::person@ person= pk::get_person(int(pk::load(KEY,si++,-1)));
				_���θ���Ʈ.add(person);
			}
			_����ī��Ʈ=_���θ���Ʈ.count;

			count = int(pk::load(KEY,si++,0));
			for(int i=0;i<count;i++)			
			{
				pk::person@ person= pk::get_person(int(pk::load(KEY,si++,-1)));
				_����ڸ���Ʈ.add(person);
			}
			_���ī��Ʈ=_����ڸ���Ʈ.count;

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
			
			pk::store(KEY,li++,���°���ġ.length);
			for(int i=0;i<���°���ġ.length;i++)
			{
				pk::store(KEY,li++,���°���ġ[i]);
			}
			pk::store(KEY,li++,����ü��.length);
			for(int i=0;i<����ü��.length;i++)
			{
				pk::store(KEY,li++,����ü��[i]);
			}
			pk::store(KEY,li++,������ġ.length);
			for(int i=0;i<������ġ.length;i++)
			{
				pk::store(KEY,li++,int(������ġ[i].x));
				pk::store(KEY,li++,int(������ġ[i].y));
			}
			pk::store(KEY,li++,_����ī��Ʈ);
			for(int i=0;i<_���θ���Ʈ.count;i++)
			{
				pk::store(KEY,li++,_���θ���Ʈ[i].get_id());
			}
			pk::store(KEY,li++,_���ī��Ʈ);
			for(int i=0;i<_����ڸ���Ʈ.count;i++)
			{
				pk::store(KEY,li++,_����ڸ���Ʈ[i].get_id());
			}
			
		}		
		bool isEnabled()
		{
			return true;
		}

		string getDesc_�ϱ���ī����()
		{
			return pk::encode("�ϱ��� ��踦 Ȯ���մϴ�.");
		}
		string getText_�ϱ���ī����()
		{
			return pk::encode("�ϱ���ī����");
		}
		
		array<string> Ư�⼳����(255);
		array<string> Ư���̸����(255);
		array<int> Ư����(����_��);
		
		
		void SaveƯ��()
		{
			for(int i=0;i<255;i++)
			{
				pk::skill@ s = pk::get_skill(i);
				if(s==null)
					continue;
				Ư�⼳����[i] = s.desc;
				Ư���̸����[i] = s.name;
			}
			
			for(int i=0;i<����_��;i++)
			{
				pk::person@ p = pk::get_person(i);
				if(p == null)
					continue;
				Ư����[i] = p.skill;
			}
		}
		void LoadƯ��()
		{
			for(int i=0;i<255;i++)
			{
				pk::skill@ s = pk::get_skill(i);
				if(s==null)
					continue;
				s.desc = Ư�⼳����[i];
				s.name = Ư���̸����[i];
			}
			for(int i=0;i<����_��;i++)
			{
				pk::person@ p = pk::get_person(i);
				if(p == null)
					continue;
				p.skill = Ư����[i];
			}
		}
		
		void handler_�ϱ���ī����3()
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
					
					int moo = ri0.person.mibun != �ź�_��� ? ri0.person.stat[����ɷ�_����] : ri0.person.base_stat[����ɷ�_����];
					
					ri0.person.skill = i;
					string str = pk::format("����{},\x1b[2x{}\x1b[0x��,\x1b[29x{}\x1b[0x��,{}����,{}����,{}��ħ,{}����,{}����,{}����"
					,moo,ri0.win,ri0.lose,ri0.����ī��Ʈ,ri0.������ī��Ʈ,ri0.��ħī��Ʈ,ri0.����ī��Ʈ,ri0.���ڵ�ī��Ʈ,ri0.������ī��Ʈ);
					s.desc = pk::encode(str);
					s.name = pk::encode("����");
					ris2.add(ri0.person);
				}

				pk::list<pk::person@> persons = pk::person_selector(pk::encode("���� ����"),pk::encode("������ �������ֽʽÿ�"),ris2,1,1);
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
				int Ư��i=0;
				for(int i=0;i<selected.duels.length;i++)
				{
					DuelInfo@ di = selected.duels[i];
					string str;
					string strResult;
					switch(di.result)
					{
						case ���_����:strResult="����";break;
						case ���_���:strResult="���";break;
						case ���_����:strResult="����";break;
					}
					
					pk::person@ p =null;
					if(di.winner.get_id() == selected.person.get_id())
					{
						int moo0= selected.person.mibun != �ź�_��� ? selected.person.stat[����ɷ�_����] : selected.person.base_stat[����ɷ�_����];
						int moo1= di.loser.mibun != �ź�_��� ? di.loser.stat[����ɷ�_����] : di.loser.base_stat[����ɷ�_����];
						str=pk::format("\x1b[2x{}\x1b[0x({})VS\x1b[29x{}\x1b[0x({}),��,{},{}��,{}��,{}��,{}",pk::decode(pk::get_name(selected.person)),moo0,pk::decode(pk::get_name(di.loser)),moo1,strResult,di.year,di.month,di.day,pk::decode(pk::get_name(di.city)));
						@p = di.loser;
					}
					else
					{
						int moo0= selected.person.mibun != �ź�_��� ? selected.person.stat[����ɷ�_����] : selected.person.base_stat[����ɷ�_����];
						int moo1= di.winner.mibun != �ź�_��� ? di.winner.stat[����ɷ�_����] : di.winner.base_stat[����ɷ�_����];
						str=pk::format("\x1b[29x{}\x1b[0x({})VS\x1b[2x{}\x1b[0x({}),��,{},{}��,{}��,{}��,{}",pk::decode(pk::get_name(selected.person)),moo0,pk::decode(pk::get_name(di.winner)),moo1,strResult,di.year,di.month,di.day,pk::decode(pk::get_name(di.city)));
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
					p.skill = Ư��i;
					pk::get_skill(Ư��i).name = pk::encode("����");
					pk::get_skill(Ư��i).desc = pk::encode(str); Ư��i++; 
					
					ris3.add(p);
				}
				
				pk::person_selector(pk::encode("���� Ȯ��"),pk::encode("�� ������ Ȯ���Ͻʽÿ�"),ris3,0,0);			
			}

		}
		
		bool handler_�ϱ���ī����2()
		{
			try
			{
				SaveƯ��();
				handler_�ϱ���ī����3();
			}
			catch
			{
				LoadƯ��();
			}
			
			LoadƯ��();
			return true;
		}
		
		bool handler_�ϱ���ī����()
		{
			array<ResultInfo> ris = makeResult();

			int si=0;
			ResultInfo@ ri=null;
			while(true)
			{
				array<string> itemArr;
				int count = pk::min(ris.length, si + 4);
				if(si == 0)
					itemArr.insertLast(pk::encode("����"));
				else
					itemArr.insertLast(pk::encode("�ڷ�"));
				for (int i = si; i < count; i++)
				{
					ResultInfo@ ri0 = ris[i];
					
					
					string str = pk::format("\x1b[2x{}\x1b[0x,{}��,{}��,{}����,{}����,{}��ħ,{}����,{}���ڵ�,{}����"
					,pk::decode(pk::get_name(ri0.person)),ri0.win,ri0.lose,ri0.����ī��Ʈ,ri0.������ī��Ʈ,ri0.��ħī��Ʈ,ri0.����ī��Ʈ,ri0.���ڵ�ī��Ʈ,ri0.������ī��Ʈ);
					itemArr.insertLast(pk::encode(str));
				}
				if(si+4 >= ris.length)
					itemArr.insertLast(pk::encode("����"));
				else
					itemArr.insertLast(pk::encode("����"));

				int choose = pk::choose(pk::encode("������ �������ֽʽÿ�"), itemArr);
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
						itemArr2.insertLast(pk::encode("����"));
					else
						itemArr2.insertLast(pk::encode("�ڷ�"));
					for (int i = si2; i < count; i++)
					{
						DuelInfo@ di = ri.duels[i];
						string str;
						string strResult;
						switch(di.result)
						{
							case ���_����:strResult="����";break;
							case ���_���:strResult="���";break;
							case ���_����:strResult="����";break;
						}
						if(di.winner.get_id() == ri.person.get_id())
							str=pk::format("VS \x1b[2x{}\x1b[0x, ��,{},{}��,{}��,{}��,{}",pk::decode(pk::get_name(di.loser)),strResult,di.year,di.month,di.day,pk::decode(pk::get_name(di.city)));
						else
							str=pk::format("VS \x1b[29x{}\x1b[0x, ��,{},{}��,{}��,{}��,{}",pk::decode(pk::get_name(di.winner)),strResult,di.year,di.month,di.day,pk::decode(pk::get_name(di.city)));
						itemArr2.insertLast(pk::encode(str));
					}
					if(si2+4 >= ri.duels.length)
						itemArr2.insertLast(pk::encode("����"));
					else
						itemArr2.insertLast(pk::encode("����"));
					int choose2 = pk::choose(pk::encode("�������ֽʽÿ�"), itemArr2);
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
			array<ResultInfo> ris(����_��);
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
					case ���_����:
					riWinner.������ī��Ʈ++;
					riLoser.���ڵ�ī��Ʈ++;
					break;
					case ���_���:
					riWinner.����ī��Ʈ++;
					riLoser.����ī��Ʈ++;
					break;
					case ���_����:
					riWinner.��ħī��Ʈ++;
					riLoser.������ī��Ʈ++;
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
					if(a.����ī��Ʈ != b.����ī��Ʈ)
						return a.����ī��Ʈ > b.����ī��Ʈ;
					if(a.������ī��Ʈ != b.������ī��Ʈ)
						return a.������ī��Ʈ > b.������ī��Ʈ;
					return a.��ħī��Ʈ > b.��ħī��Ʈ;
				});
			}
			
			return ris2;
		}
		array<DuelInfo> _duels;
		
		void ���º���(pk::person@ person, pk::force@ force)
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
				int maxExp = p1!=null ? p1.stat_exp[����ɷ�_����] - ���°���ġ[p1.get_id()] : 0;
				pk::person@ maxPerson = p1;


				pk::person@ p2 = pk::get_person(unit.member[1]);
				if (p2 != null)
				{
					int exp = p2.stat_exp[����ɷ�_����] - ���°���ġ[p2.get_id()];
					if (exp > maxExp)
					{
						maxExp = exp;
						@maxPerson = p2;
					}
				}
				pk::person@ p3 = pk::get_person(unit.member[2]);
				if (p3 != null)
				{
					int exp = p3.stat_exp[����ɷ�_����] - ���°���ġ[p3.get_id()];
					if (exp > maxExp)
					{
						maxExp = exp;
						@maxPerson = p3;
					}
				}

				if (üũ�ϱ���(maxPerson, prisoner, unit))
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
		
		int _����ī��Ʈ = 0;
		int _���ī��Ʈ = 0;
		
		void ����_����ó��()
		{
			pk::list<pk::person@> persons���� = pk::get_person_list(pk::mibun_flags(�ź�_����));
			int ����ī��Ʈ = persons����.count;
			if(true or _����ī��Ʈ != ����ī��Ʈ)
			{
				for(int i=0;i<persons����.count;i++)
				{
					pk::person@ p = persons����[i];
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
						//�ϱ⸦ �̱�� �δ밡 ���Ͽ� ����Ǹ�?
						//pk::printf("unit null\n");
						continue;
					}
					pk::person@ p1=pk::get_person(unit.member[0]);
					if(p1==null)
					{
						//pk::printf("p1 null {} {} {} x{},y{}\n",unit.member[0],unit.member[1],unit.member[2],p.get_pos().x,p.get_pos().y);
						continue;
					}
						
					
					int maxExp =  p1.stat_exp[����ɷ�_����] - ���°���ġ[p1.get_id()];
					pk::person@ maxPerson = p1;
					
					
					pk::person@ p2 = pk::get_person(unit.member[1]);
					if(p2!=null)
					{
						int exp =  p2.stat_exp[����ɷ�_����] - ���°���ġ[p2.get_id()];
						if(exp > maxExp)
						{
							maxExp = exp;
							@maxPerson = p2;
						}
					}
					pk::person@ p3 = pk::get_person(unit.member[2]);
					if(p3!=null)
					{
						int exp =  p3.stat_exp[����ɷ�_����] - ���°���ġ[p3.get_id()];
						if(exp > maxExp)
						{
							maxExp = exp;
							@maxPerson = p3;
						}
					}
					
					//pk::printf("maxExp {},{}\n",pk::decode(pk::get_name(maxPerson)), maxExp);
					
					if(üũ�ϱ���(maxPerson,p,unit))
					{
						//pk::printf("1:1 {},{},hp{},hp{},{}--------------------\n",pk::decode(pk::get_name(maxPerson)),pk::decode(pk::get_name(p)),maxPerson.hp,p.hp,���_����);
						DuelInfo di;
						@di.winner= maxPerson;
						@di.loser = p;
						p.prisoner_timer = 1;//���������� �������� �̷��� ó�� ���ۿ��� ������?
						di.year = pk::get_year();
						di.month = pk::get_month();
						di.day = pk::get_day();
						int city = pk::get_city_id(p.get_pos());
						@di.city = pk::get_city(city);
						di.result = ���_����;
						_duels.insertLast(di);
						history(di);
					}
					else 
					{
						//�ϱ��信�� �������µ� �ٷ� �ٸ����忡�� ��������
						������ó��(p, null);
					}
				}
			}

			_���θ���Ʈ = persons����;
			_����ī��Ʈ = ����ī��Ʈ;
		}

		bool IsNewCaught(pk::person@ p)
		{
			//if(p.cause_of_death == ����_�ڿ���)
			//	return false;

			for(int i=0;i<_���θ���Ʈ.count;i++)
			{
				pk::person@ p2 = _���θ���Ʈ[i];
				if(p2.get_id() == p.get_id())
					return false;
			}
			return true;
		}

		
		bool IsNewDead(pk::person@ p)
		{
			//if(p.cause_of_death == ����_�ڿ���)
			//	return false;

			for(int i=0;i<_����ڸ���Ʈ.count;i++)
			{
				pk::person@ p2 = _����ڸ���Ʈ[i];
				if(p2.get_id() == p.get_id())
					return false;
			}
			return true;
		}
		
		pk::list<pk::person@> _����ڸ���Ʈ;
		pk::list<pk::person@> _���θ���Ʈ;
		void ����_���ó��()
		{
			pk::list<pk::person@> persons���= pk::get_person_list(pk::mibun_flags(�ź�_���));
			int ���ī��Ʈ = persons���.count;
			if(���ī��Ʈ == _���ī��Ʈ)
				return;
			
				
			for(int i=0;i<persons���.count;i++)
			{
				pk::person@ p = persons���[i];
				if(!IsNewDead(p))
					continue;
				
				�����_ó��(p,���_���);
			}
			
			
			_���ī��Ʈ = ���ī��Ʈ;
			_����ڸ���Ʈ = persons���;

		
		}
		
		bool üũ�ϱ���(pk::person@ winner, pk::person@ loser , pk::unit@ winnerUnit)
		{
			if(winner!=null && loser!=null && winner.get_force_id() == loser.get_force_id())
				return false;
			
			//pk::printf("check0 {},{}\n", winner.stat_exp[����ɷ�_����] - ���°���ġ[winner.get_id()], pk::decode(pk::get_name(winner)));

			//if (winner.stat_exp[����ɷ�_����] - ���°���ġ[winner.get_id()] < 1)
			if (winner.stat_exp[����ɷ�_����] - ���°���ġ[winner.get_id()] < 4)
			{
				return false;
			}
			if(winner.stat_exp[����ɷ�_����] - ���°���ġ[winner.get_id()] >= 10)
			{
				//pk::printf("1:1 ok {},{}\n",pk::decode(pk::get_name(winner)),winner.stat_exp[����ɷ�_����] - ���°���ġ[winner.get_id()]);
				return true;
			}
			//pk::printf("check {},{}\n", winner.stat_exp[����ɷ�_����] - ���°���ġ[winner.get_id()], pk::decode(pk::get_name(winner)));
			
			if(winnerUnit!=null && pk::get_member_count(winnerUnit) >=2)
			{
				pk::person@ p0 = (winnerUnit.member[0] >=0 && winnerUnit.member[0]<���°���ġ.length) ? pk::get_person(winnerUnit.member[0]) : null;
				pk::person@ p1 = (winnerUnit.member[1] >=0 && winnerUnit.member[1]<���°���ġ.length) ? pk::get_person(winnerUnit.member[1]) : null;
				pk::person@ p2 = (winnerUnit.member[2] >=0 && winnerUnit.member[2]<���°���ġ.length) ? pk::get_person(winnerUnit.member[2]) : null;
				float exp0 = float(p0!=null ? p0.stat_exp[����ɷ�_����] - ���°���ġ[p0.get_id()] : -1);
				float exp1 = float(p1!=null ? p1.stat_exp[����ɷ�_����] - ���°���ġ[p1.get_id()] : -1);
				float exp2 = float(p2!=null ? p2.stat_exp[����ɷ�_����] - ���°���ġ[p2.get_id()] : -1);
				bool ����0 = p0!=null ? pk::has_skill(p0,Ư��_����) : false;
				bool ����1 = p1!=null ? pk::has_skill(p1,Ư��_����) : false;
				bool ����2 = p2!=null ? pk::has_skill(p2,Ư��_����) : false;
				if(����0) 
				{
					exp1 = exp1 / 2.0;
					exp2 = exp2 / 2.0;
				}
				if(����1)
				{
					exp0 = exp0 / 2.0;
					exp2 = exp2 / 2.0;
				}
				if(����2)
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
		
		void �����_ó��(pk::person@ p,int resultType)
		{
			//����ڴ� ������ Ȯ��.
			//pk::unit@ unit0 = pk::get_unit(pk::get_unit_id(p));
			//if(unit0 !=null && GetMinHP(unit0).get_id() != p.get_id())
			//	return;
		
			//hp�� �̹� �￩�ִ»�Ȳ���� ���ݹް� ������, �� �����ϴ�. 
			//�ϱ��信�� ���� �״� ��Ȳ������ hp�� 1�̰ų� 10���� �����ϰͰ�����, �������ٰ� ���� ������ ��쵵 �ְ�, 
			if(p.hp >= 10)
			{
				//pk::printf("dead return hp {}\n",pk::decode(pk::get_name(p)),p.hp);
				return;
			}

			//pk::printf("new dead{}\n", getName(p));
		
			array<DuelInfo> dis;
			for(int j=0;j<���°���ġ.length;j++)
			{
				pk::person@ p2 = pk::get_person(j);
				pk::unit@ unit = pk::get_unit(pk::get_unit_id(p2));
					
				bool bRange = pk::is_in_range(������ġ[p.get_id()], 3, p2.get_pos());
				//bRange = true;
				if(bRange && üũ�ϱ���(p2,p,unit)) 
				{
					bool bFound = IsAlready(p2);
					//���� �ϱ��� ��Ͽ� ����,
					if(!bFound) 
					{
						//pk::printf("1:1 {},{},{}---------------------------\n",pk::decode(pk::get_name(p2)),pk::decode(pk::get_name(p)),resultType);
						
						DuelInfo di;
						@di.winner= p2;
						@di.loser = p;
						di.year = pk::get_year();
						di.month = pk::get_month();
						di.day = pk::get_day();
						int city = pk::get_city_id(������ġ[p.get_id()]);
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
					pk::unit@ unit2 = pk::get_unit(pk::get_unit_id(dis[i].winner)); //�����ڰ� ����ɶ��� ����ؼ�	
					int dist = pk::get_distance(dis[i].winner.get_pos(),������ġ[p.get_id()]);
					if(dist == minDist)
					{
						if(minUnit!=null && unit2!=null && minUnit.get_id() == unit2.get_id())
						{
							int off0 = minDi.winner.stat_exp[����ɷ�_����] - ���°���ġ[minDi.winner.get_id()];
							int off1 = dis[i].winner.stat_exp[����ɷ�_����] - ���°���ġ[dis[i].winner.get_id()];
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
				case ���_����:strType="����";break;
				case ���_����:strType="����";break;
				case ���_���:strType="���";break;
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
			
			
			string str0 = pk::format("\x1b[2x{}\x1b[0x({}) VS \x1b[29x{}\x1b[0x({}),{},{}��{}��,{}��{}��",
			pk::decode(pk::get_name(di.winner)),di.winner.stat[����ɷ�_����],pk::decode(pk::get_name(di.loser)),di.loser.stat[����ɷ�_����],
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
		
		void ������ó��(pk::person@ p, pk::unit@ unit)
		{
			if (IsAlready(p))
				return;

			//pk::printf("escaped {}\n", pk::decode(pk::get_name(p)));
			bool bFoundWinner = false;
			array<DuelInfo> dis;
			for (int j = 0; j < ����ü��.length; j++)
			{
				pk::person@ p2 = pk::get_person(j);
				pk::unit@ unit2 = pk::get_unit(pk::get_unit_id(p2)); //�����ڰ� ����ɶ��� ����ؼ�

				bool bFound = IsAlready(p2);
				pk::point pt0 = unit != null ? unit.get_pos() : ������ġ[p.get_id()];
				//pk::point pt0 = ������ġ[p.get_id()];
				pk::point pt1 = unit2 != null ? unit2.get_pos() : ������ġ[p2.get_id()];
				bool bRange = pk::is_in_range(pt0, 4, pt1);
				//auto obj = pk::get_hex_object(pt0);
				//if(obj!=null && obj.get_type_id() == 5)
				//	bRange = true;

				//bRange = true;
				if (!bFound && bRange && üũ�ϱ���(p2, p, pk::get_unit(pk::get_unit_id(p2))))
				{
					//pk::printf("hp {},{},{},{}\n", pk::decode(pk::get_name(p)), p.hp, pk::decode(pk::get_name(p2)), p2.hp);
					DuelInfo di;
					@di.winner = p2.hp > p.hp ? p2 : p;
					@di.loser = p.hp < p2.hp ? p : p2;
					di.year = pk::get_year();
					di.month = pk::get_month();
					di.day = pk::get_day();
					int city = pk::get_city_id(������ġ[p.get_id()]);
					@di.city = pk::get_city(city);
					di.result = ���_����;
					dis.insertLast(di);
					bFoundWinner = true;
				}
			}
			DuelInfo@ ndi = null;
			if (dis.length == 0) //������ ��ȭ�ؼ� ã�´�
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
					pk::unit@ unit2 = pk::get_unit(pk::get_unit_id(dis[i].winner)); //�����ڰ� ����ɶ��� ����ؼ�	
					pk::point pos = unit != null ? unit.get_pos() : ������ġ[p.get_id()];
					pk::point pos2 = unit2 != null ? unit2.get_pos() : ������ġ[dis[i].winner.get_id()];

					int dist = pk::get_distance(pos2, pos);

					//pk::printf("duel dist{},{} \n", pk::decode(pk::get_name(dis[i].winner)), dist);
					if (dist == minDist)
					{
						if (minUnit != null && unit2 != null && minUnit.get_id() == unit2.get_id())
						{
							int off0 = minDi.winner.stat_exp[����ɷ�_����] - ���°���ġ[minDi.winner.get_id()];
							int off1 = dis[i].winner.stat_exp[����ɷ�_����] - ���°���ġ[dis[i].winner.get_id()];
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
			//		, pk::decode(pk::get_name(ndi.winner)), pk::decode(pk::get_name(p)), ndi.winner.hp, p.hp, ���_����);
		}

		void ����_������ó��()
		{
			for(int i=0;i<����ü��.length;i++)
			{
				pk::person@ p=pk::get_person(i);
				if(p.mibun == �ź�_���)
					continue;
				
				pk::unit@ unit = pk::get_unit(pk::get_unit_id(p));
				
				//if(p.hp!=100)
				//	pk::printf("hp {},{}->{}\n",pk::decode(pk::get_name(p)),����ü��[i],p.hp);
				if((p.hp==1 || (p.hp - ����ü��[i] < 0 and p.hp < 20)) and (unit==null || (unit!=null && GetMinHP(unit).get_id() == p.get_id()))) // ������
				{
					������ó��(p, unit);
				}//������
			}//����

		}
		
		
		void �δ�����(pk::unit@ unit, int type)
		{
			//���ʰ� ���ŵǴ°��, ������ ��������ϱ�, ���������� ���ư���.
			//�ź��� ���ΰ� �ǰ��� ���°���ġ�� ������Ʈ�Ǵµ��ϴ� ���� ����´�.
			if(unit.member[0] >=0 && unit.member[0] < ���°���ġ.length)
			{
				pk::person@ p=pk::get_person(unit.member[0]);
				if(üũ�ϱ���(pk::get_person(unit.member[0]),null, unit))
					����();
				//else if((pk::get_member_count(unit)!= 1 or (pk::get_member_count(unit)==1 && p.mibun != �ź�_���� && p.mibun != �ź�_���))
				//	and p!=null and p.hp - ����ü��[p.get_id()] < 0 and p.hp < 20)
				//	����();
			}
			if(unit.member[1] >=0 && unit.member[1] < ���°���ġ.length)
			{
				pk::person@ p=pk::get_person(unit.member[1]);
				if(üũ�ϱ���(pk::get_person(unit.member[1]),null, unit))
					����();
				//else if((pk::get_member_count(unit)!= 1 or (pk::get_member_count(unit)==1 && p.mibun != �ź�_���� && p.mibun != �ź�_���))
				//	and p!=null and p.hp - ����ü��[p.get_id()] < 0 and p.hp < 20)
				//	����();
			}
			if(unit.member[2] >=0 && unit.member[2] < ���°���ġ.length)
			{
				pk::person@ p=pk::get_person(unit.member[2]);
				if(üũ�ϱ���(pk::get_person(unit.member[2]),null, unit))
					����();
				//else if((pk::get_member_count(unit)!= 1 or(pk::get_member_count(unit)==1 && p.mibun != �ź�_���� && p.mibun != �ź�_���))
				//	and p!=null and p.hp - ����ü��[p.get_id()] < 0 and p.hp < 20)
				//	����();
			}
		}

		void onTurn(pk::force@ force)
		{
			����();
		}
		void ����()
		{
			����_����ó��();
			����_���ó��();
			����_������ó��();
			


			for(int i =0;i<���°���ġ.length;i++)
			{
				pk::person@ p = pk::get_person(i);
				if(p==null)
					continue;
				
				int off = p.stat_exp[����ɷ�_����]-���°���ġ[i];
				if(off>=10 && !IsAlready(p))
				{
					//pk::printf("miss {},{}\n", pk::decode(pk::get_name(p)),off);
				}
				
				
				���°���ġ[i] = p.stat_exp[����ɷ�_����];
				������ġ[i] = p.get_pos();
				����ü��[i] = p.hp;
			}
			
			pk::list<pk::person@> persons���� = pk::get_person_list(pk::mibun_flags(�ź�_����));
			_����ī��Ʈ = persons����.count;
			_���θ���Ʈ = persons����;
			pk::list<pk::person@> persons���= pk::get_person_list(pk::mibun_flags(�ź�_���));
			_���ī��Ʈ = persons���.count;
			_����ڸ���Ʈ = persons���;
			
		}


		void �δ��ൿ�Ϸ�(pk::unit@ unit)
		{
			�δ�����(unit,0);		
		}

		void �δ���ǥ����(pk::unit@ unit, const pk::point &in pt)
		{
			if(unit.member[0] >=0 and unit.member[0] < ������ġ.length) 
				������ġ[unit.member[0]] = pt;
			if(unit.member[1] >=0 and unit.member[1] < ������ġ.length)
				������ġ[unit.member[1]] = pt;
			if(unit.member[2] >=0 and unit.member[2] < ������ġ.length)
				������ġ[unit.member[2]] = pt;
				
		}

		void �δ����ġ(pk::unit@ unit, int type)
		{
			//�δ�����(unit,type);		
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
