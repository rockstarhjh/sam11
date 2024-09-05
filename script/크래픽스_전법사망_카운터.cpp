/*
@������: ũ���Ƚ�
@Update:2023.9.9 ��Ȯ������, ����˸�� ���ó���Ǵ� ���׼���
*/

namespace �⺴�������_�ϱ���_ī����
{
	const int KEY = pk::hash("�⺴�������_�ϱ���_ī����");
	class DeadInfo
	{
		pk::person@ attacker;
		pk::list<pk::person@> deads;
		pk::list<pk::city@> cities;
		array<int> years;
		array<int> months;
		array<int> days;
	}
	
	class Main
	{
		pk::func203_t@ prev_callback_203;
		pk::func209_t@ prev_callback_209;
		Main()
		{
			@prev_callback_203 = cast<pk::func203_t@>(pk::get_func(203));
			pk::reset_func(203);
			pk::set_func(203, pk::func203_t(callback));                // 202 ���� ���� Ȯ��
			
			@prev_callback_209 = cast<pk::func209_t@>(pk::get_func(209));
			pk::reset_func(209);
			pk::set_func(209, pk::func209_t(callback209));                // 202 ���� ���� Ȯ��

			
			pk::bind(174, pk::trigger174_t(�δ��ൿ�Ϸ�));
			pk::bind(173, pk::trigger173_t(�δ����ġ));
			pk::bind(107, pk::trigger107_t(����));
			
			
			pk::menu_item �⺴�������ī����;
			�⺴�������ī����.menu = 2;
			�⺴�������ī����.is_enabled = pk::menu_item_is_enabled_t(isEnabled);
			�⺴�������ī����.get_desc = pk::menu_item_get_desc_t(getDesc_�⺴�������ī����);
			�⺴�������ī����.get_text = pk::menu_item_get_text_t(getText_�⺴�������ī����);
			�⺴�������ī����.handler = pk::menu_item_handler_t(handler_�⺴�������ī����2);
			pk::add_menu_item(�⺴�������ī����);
			
			pk::bind(102, pk::trigger102_t(Init));
			pk::bind(105, pk::trigger105_t(SaveData));
			
		}
		void Init()
		{
			LoadData();
		}

		void LoadData()
		{
			while(_deads.length > 0)
				_deads.removeLast();
			����ڸ���Ʈ.clear();
			_attackers = {};
			_defenders = {};

			int count = int(pk::load(KEY,0,0));
			pk::printf("deads count : {}---------------\n",count);
			int si=1;
			for(int i=0;i<count;i++)
			{
				DeadInfo di;
				int moo=int(pk::load(KEY,si++,-1));
				int count2 = int(pk::load(KEY,si++,0));
				@di.attacker = pk::get_person(moo);
				for(int j=0;j<count2;j++)
				{
					int moo2 = int(pk::load(KEY,si++,-1));
					int location = int(pk::load(KEY,si++,-1));
					int year = int(pk::load(KEY,si++,-1));
					int month = int(pk::load(KEY,si++,-1));
					int day = int(pk::load(KEY,si++,-1));
					di.deads.add(pk::get_person(moo2));
					di.cities.add(pk::get_city(location));
					di.years.insertLast(year);
					di.months.insertLast(month);
					di.days.insertLast(day);
				}
				_deads.insertLast(di);
			}

			int count2 = int(pk::load(KEY, si++, 0));
			for (int i = 0; i < count2; i++)
			{
				int pp = int(pk::load(KEY, si++, -1));
				pk::person@ p = pp>=0 ? pk::get_person(pp) : null;
				if(p==null)
					continue;
				����ڸ���Ʈ.add(p);
			}
			int count3 = int(pk::load(KEY, si++, 0));
			for (int i = 0; i < count3; i++)
			{
				int p0 = int(pk::load(KEY, si++, -1));
				int p1 = int(pk::load(KEY, si++, -1));
				if(p0<0 || p1<0)
					continue;
				pk::person@ pp0 = p0 >= 0 ? pk::get_person(p0) : null;
				pk::person@ pp1 = p1 >= 0 ? pk::get_person(p1) : null;
				if(pp0==null || pp1==null)
					continue;

				_attackers.insertLast(pp0);
				_defenders.insertLast(pp1);
			}


		}
		void SaveData(int file_id)
		{
			pk::store(KEY,0,_deads.length);
			int li=1;
			for(int i=0;i<_deads.length;i++)
			{
				DeadInfo di = _deads[i];
				pk::store(KEY,li++,di.attacker.get_id());
				pk::store(KEY,li++,di.deads.count);
				
				for(int j=0;j<di.deads.count;j++)
				{
					pk::store(KEY,li++,di.deads[j].get_id());
					pk::store(KEY,li++,di.cities[j].get_id());
					pk::store(KEY,li++,di.years[j]);
					pk::store(KEY,li++,di.months[j]);
					pk::store(KEY,li++,di.days[j]);
				}
			}
			pk::store(KEY, li++, ����ڸ���Ʈ.count);
			for (int i = 0; i < ����ڸ���Ʈ.count; i++)
			{
				pk::store(KEY, li++, ����ڸ���Ʈ[i].get_id());
			}
			pk::store(KEY, li++, _attackers.length);
			for (int i = 0; i < _attackers.length; i++)
			{
				pk::store(KEY, li++, _attackers[i].get_id());
				pk::store(KEY, li++, _defenders[i].get_id());
			}


		}		
		bool isEnabled()
		{
			return true;
		}

		string getDesc_�⺴�������ī����()
		{
			return pk::encode("������� ��踦 Ȯ���մϴ�.");
		}
		string getText_�⺴�������ī����()
		{
			return pk::encode("�������ī����");
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
		void handler_�⺴�������ī����3()
		{
			if(_deads.length > 0)
				_deads.sort(function(a,b)
				{
					return a.deads.count >= b.deads.count;
				});
				
			while(true)
			{
				int count = pk::min(255, _deads.length);
				pk::list<pk::person@> ris2;

				for(int i=0;i<count;i++)
				{
					DeadInfo@ di = _deads[i];
					pk::skill@ s = pk::get_skill(i);
					if(s==null)
						continue;
					string str;
					di.attacker.skill = i;
					pk::force@ force = pk::get_force(di.attacker.get_force_id());
					int moo = di.attacker.mibun != �ź�_��� ? di.attacker.stat[����ɷ�_����] : di.attacker.base_stat[����ɷ�_����];
					str = pk::format("\x1b[1x{}\x1b[0x,����{},{}��,{}ȸ",pk::decode(pk::get_name(di.attacker)),moo,force!=null ? pk::decode(pk::get_name(force)) : "??",di.deads.count);
					s.desc = pk::encode(str);
					s.name = pk::encode("����");
					ris2.add(di.attacker);
				}

				pk::list<pk::person@> persons = pk::person_selector(pk::encode("���� ����"),pk::encode("������ �������ֽʽÿ�"),ris2,1,1);
				if(persons.count==0)
					return;
				
				DeadInfo@ selected = null;
				for(int i=0;i<count;i++)
				{
					DeadInfo@ di = _deads[i];
					if(di.attacker.get_id() == persons[0].get_id())
					{
						@selected = di;
						break;
					}
				}
				if(selected==null)
					continue;
				
				pk::list<pk::person@> ris3;
				int ii=0;
				int Ư��i=0;
				for(int i=0;i<selected.deads.count;i++)
				{
					pk::person@ person = selected.deads[i];
					pk::city@ city= selected.cities[i];
					string day;
					if(selected.days[i] == 10)
						day = "���";
					else if(selected.days[i] == 10)
						day = "�߼�";
					else
						day = "�ϼ�";
					
					int moo = person.mibun != �ź�_��� ? person.stat[����ɷ�_����] : person.base_stat[����ɷ�_����];
					string str;
					str = pk::format("\x1b[1x{}\x1b[0x VS \x1b[29x{}\x1b[0x,����{},{},{}�� {}�� {}", pk::decode(pk::get_name(selected.attacker)),pk::decode(pk::get_name(person)),moo,pk::decode(pk::get_name(city)),selected.years[i], selected.months[i],day);
	
					pk::person@ p = person;
	
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
		
		bool handler_�⺴�������ī����2()
		{
			try
			{
				SaveƯ��();
				handler_�⺴�������ī����3();
			}
			catch
			{
				LoadƯ��();
			}
			
			LoadƯ��();
			return true;

		}
		bool handler_�⺴�������ī����()
		{
			if(_deads.length > 0)
				_deads.sort(function(a,b)
				{
					return a.deads.count >= b.deads.count;
				});
			
			int si = 0;
			DeadInfo@ chooseItem = null;
			while(true)
			{
				array<string> itemArr;

				int count = pk::min(_deads.length, si + 5);									
				for (int i = si; i < count; i++)
				{
					DeadInfo@ di = _deads[i];
					string str;
					pk::force@ force = pk::get_force(di.attacker.get_force_id());
					str = pk::format("{},{}��,{}",pk::decode(pk::get_name(di.attacker)),force!=null ? pk::decode(pk::get_name(force)) : "??",di.deads.count);
					itemArr.insertLast(pk::encode(str));
				}
				
				if(si+5 >= _deads.length)
					itemArr.insertLast(pk::encode("����"));
				else
					itemArr.insertLast(pk::encode("����"));

				int choose = pk::choose(pk::encode("�󼼳����� ������ ������ �����Ͻʽÿ�"), itemArr);
				if(choose == itemArr.length -1)
				{
					si = si + 5;
					if (si >= _deads.length)
						break;
				}
				else
				{
					@chooseItem = _deads[si+choose];
				}
				if(chooseItem == null)
					continue;
				
				int si2=0;
				while(true)
				{
					array<string> itemArr2;
					int count2 = pk::min(chooseItem.deads.count, si2 + 5);
				
					for (int i = si2; i < count2; i++)
					{
						pk::person@ person = chooseItem.deads[i];
						pk::city@ city= chooseItem.cities[i];
						string day;
						if(chooseItem.days[i] == 10)
							day = "���";
						else if(chooseItem.days[i] == 10)
							day = "�߼�";
						else
							day = "�ϼ�";
						string str;
						str = pk::format("\x1b[29x{}\x1b[0x,{},{}�� {}�� {}",pk::decode(pk::get_name(person)),pk::decode(pk::get_name(city)),chooseItem.years[i], chooseItem.months[i],day);
						itemArr2.insertLast(pk::encode(str));
					}
					if(si2+5 >= chooseItem.deads.count)
						itemArr2.insertLast(pk::encode("����"));
					else
						itemArr2.insertLast(pk::encode("����"));
					
					int choose2 = pk::choose(pk::encode("������ �����Ͻʽÿ�"),itemArr2);
					if (choose2 == itemArr2.length - 1)
					{
						si2 = si2 + 5;
						if (si2 >= chooseItem.deads.count)
							break;
					}
				}
				
				@chooseItem = null;
				si = 0;

			}//while ����
			return true;
		}

		bool isAlready(pk::person@ attacker, pk::person@ target)
		{
			if (attacker == null || target == null)
				return true;

			for (int i = 0; i < _attackers.length; i++)
			{
				if (_attackers[i].get_id() == attacker.get_id() && _defenders[i].get_id() == target.get_id())
					return true;
			}
			return false;
		}

		pk::person@ getPerson(int a)
		{
			if (a < 0 || a >= ����_��)
				return null;

			return pk::get_person(a);
		}


		void callback209(pk::damage_info& info, pk::unit@ attacker, int tactics_id, const pk::point &in target_pos, int type, int critical, bool ambush)
		{
			auto obj = pk::get_hex_object(target_pos);
			if(false && obj.get_type_id() == 11 && tactics_id >=0)
			{
				pk::unit@ target = pk::get_unit(target_pos);
				if (target != null)
				{
					pk::person@ p = pk::get_person(attacker.leader);
					pk::person@ p0 = pk::get_person(target.leader);
					pk::person@ p1 = getPerson(target.member[1]);
					pk::person@ p2 = getPerson(target.member[2]);

					if (!isAlready(p, p0))
					{
						_attackers.insertLast(p);
						_defenders.insertLast(p0);
					}
					if (!isAlready(p, p1))
					{
						_attackers.insertLast(p);
						_defenders.insertLast(p1);
					}
					if (!isAlready(p, p2))
					{
						_attackers.insertLast(p);
						_defenders.insertLast(p2);
					}
				}
				
				//pk::printf("attack {},{}\n", attacker.leader,target.leader);
			}
			
			prev_callback_209(info,attacker,tactics_id,target_pos,type,critical,ambush);
		}
		
		array<DeadInfo> _deads;

		array<pk::person@> _attackers;
		array<pk::person@> _defenders;


		pk::list<pk::person@> ����ڸ���Ʈ;

		int callback(pk::person@ attacker, pk::person@ target, int tactics_id, bool critical)
		{
			bool bFound = false;
			for(int i=0;i<_attackers.length;i++)
			{
				if(attacker.get_id() != _attackers[i].get_id()) 
					continue;
				if(target.get_id() != _defenders[i].get_id())
					continue;
					
				bFound = true;
				break;
			}
			
			if(!bFound)
			{
				_attackers.insertLast(attacker);
				_defenders.insertLast(target);
			}
			
			
			return prev_callback_203(attacker,target,tactics_id,critical);
		}
		
		void �����ó��()
		{
			for (int i = 0; i < ����_��; i++)
			{
				pk::person@ p = pk::get_person(i);
				if (p == null)
					continue;

				if (p.mibun != �ź�_��� || p.get_id() == ����_���� || getName(p) == "����")
					continue;
				if(p.hp < 10)
					continue;

				bool bFound = false;
				for (int k = 0; k < ����ڸ���Ʈ.count; k++)
				{
					pk::person@ p2 = ����ڸ���Ʈ[k];
					if (p.get_id() == p2.get_id())
					{
						bFound = true;
						break;
					}
				}
				if(bFound)
					continue;


				int minDist = 0;
				pk::person@ minPerson = null;
				for (int j = _defenders.length-1; j >= 0; j--)
				{
					pk::person@ p2 = _defenders[j];
					if (p.get_id() != p2.get_id())
						continue;

					UpdateDead(_attackers[j],p2);
					break;
				}
			}

		}
		
		void ����()
		{
			�����ó��();

			while(_attackers.length > 0)
				_attackers.removeAt(0);
			while(_defenders.length > 0)
				_defenders.removeAt(0);

			����ڸ���Ʈ.clear();
			for (int i = 0; i < ����_��; i++)
			{
				pk::person@ p = pk::get_person(i);
				if(p==null)
					continue;

				if(p.mibun != �ź�_���)
					continue;
				����ڸ���Ʈ.add(p);
			}
		}

		void �δ��ൿ�Ϸ�(pk::unit@ unit)
		{
			//����,����� Ȯ��
			for(int i=0;i<_attackers.length;i++)
			{
				if(_attackers[i].get_id() == unit.leader)
				{
					if (_defenders[i].get_id() == ����_���� || getName(_defenders[i]) == "����")
					{
						pk::unit@ unit2 = pk::get_unit(_defenders[i].get_pos());
						if (unit2 != null && unit2.troops == 0)
							return;
					}
					if(_defenders[i].mibun == �ź�_���)
					{
						UpdateDead(_attackers[i],_defenders[i]);
					}
				}
			}
		}
		
		void UpdateDead(pk::person@ attacker, pk::person@ dead)
		{
			pk::force@ force = pk::get_force(attacker.get_force_id());
			for(int j=0;j<_deads.length;j++)
			{
				DeadInfo@ di = _deads[j];
				if(di.attacker.get_id() != attacker.get_id())
					continue;
				
				if(di.years[di.years.length-1] == pk::get_year() and
				di.months[di.months.length-1] == pk::get_month() and
				di.days[di.days.length-1] == pk::get_day())
				{
					//pk::printf("same return--------------\n");
					return;
				}

				int dcount0 = pk::get_day_count(pk::get_year(), pk::get_month(), pk::get_day());
				int dcount1 = pk::get_day_count(di.years[di.years.length - 1], di.months[di.months.length - 1], di.days[di.days.length - 1]);
				
				//pk::printf("day count {},{}\n", dcount0,dcount1);
				if (dcount0 - dcount1 <= 10)
				{
					//pk::printf("same return day {},{}--------------\n",getName(attacker),getName(dead));
					return;
				}



					
				//pk::printf("dead {}, {}\n",pk::decode(pk::get_name(attacker)),pk::decode(pk::get_name(dead)));
				
				di.deads.add(dead);
				
				int city = pk::get_city_id(attacker.get_pos());
				di.cities.add(pk::get_city(city));
				di.years.insertLast(pk::get_year());
				di.months.insertLast(pk::get_month());
				di.days.insertLast(pk::get_day());

				string str = pk::format("\x1b[1x{}\x1b[0x �������� \x1b[29x{}\x1b[0x ���,{}ȸ", getName(attacker), getName(dead),di.deads.count);
				pk::history_log(attacker.get_pos(), force != null ? force.color : -1, pk::encode(str));

				return;
			}
			
			//pk::printf("dead {}, {}\n",pk::decode(pk::get_name(attacker)),pk::decode(pk::get_name(dead)));
			
			DeadInfo di;
			@di.attacker=attacker;
			di.deads.add(dead);
			
			int city = pk::get_city_id(attacker.get_pos());
			di.cities.add(pk::get_city(city));
			di.years.insertLast(pk::get_year());
			di.months.insertLast(pk::get_month());
			di.days.insertLast(pk::get_day());
			
			string str = pk::format("\x1b[1x{}\x1b[0x �������� \x1b[29x{}\x1b[0x ���,1ȸ",getName(attacker),getName(dead));
			
			_deads.insertLast(di);
			pk::history_log(attacker.get_pos(), force != null ? force.color : -1, pk::encode(str));
		}

		void �δ����ġ(pk::unit@ unit, int type)
		{
			if (type == 1)
				return;
			
			for(int i=0;i<_attackers.length;i++)
			{
				if(_attackers[i].get_id() == unit.leader)
				{
					if (_defenders[i].get_id() == ����_���� || getName(_defenders[i]) == "����")
					{
						pk::unit@ unit2 = pk::get_unit(_defenders[i].get_pos());
						if (unit2 != null && unit2.troops == 0)
							return;
					}
					if(_defenders[i].mibun == �ź�_���)
					{
						UpdateDead(_attackers[i],_defenders[i]);
					}
				}
			}
			
		}

		string getName(pk::object@ obj)
		{
			return obj != null ? pk::decode(pk::get_name(obj)) : "null";
		}
		
	}
	Main main;
}
