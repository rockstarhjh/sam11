/*
@������: ũ���Ƚ�
@Update: 2023.8.14,���ʹ���
@Update: 2023.8.24,����ÿ��� ����Ž���� ��ߵ�������� ����.
@Update: 2023.9.10, ����Ž��, ��ߵ�� �ֱ�ɼ� �߰�.
@Update: 2024.5.27 ������, �����ڵ����, ����ڵ�Ž��, ������_AI����, AI���Ǽ��¸���ø�繫������ ��� �߰�.
*/
namespace AI������_AI_Recuite_v2
{
	const bool AI_����Ž�� = true;//�����ൿ�� �Ҹ��ؼ�, ����Ž���� �մϴ�.
	const int AI_����Ž��_�ֱ� = 30; //10������ �Է��ϼ���. 20�Ͽ� �ѹ�
	
	const bool AI_��ߵ�� = true;//�����ൿ�� �Ҹ��ؼ�, ��߹��带 ����մϴ�.
	const int AI_��ߵ��_�ֱ� = 10; //10�Ͽ� �ѹ�

	const bool AI_������ = false;// 2�޿������� �������ÿ� �ִ°��, �ڵ����� �ش絵�ÿ� ����.(�����ൿ �Ҹ� ����)
	const int AI_������_�����Ⱓ = 360; //������ 1�⵿�� �������� ���� �ʽ��ϴ�.

	const bool AI_�����ڵ���� = true;//���ΰ� �漺���� 90�̸��� �Ǹ� �ڵ����� ���˴ϴ�.(�����ൿ �Ҹ� ����)
	const int AI_�����ڵ����_�漺�� = 80;//AI���� �����϶�,80�̸��ΰ�� �ڵ�����.
	const int AI_�����ڵ����_�漺��_���� = 90;//���������� AI�� �����϶�, 90�̸��ΰ�� �ڵ�����.
	const int AI_�����ڵ����_Ȯ�� = 20;//��������� AI�� ���ε�� Ȯ���Դϴ�.(20%�̴ϱ� 5���̸� ���� ��� ������� ���ΰ� ���Ǵ¼�)

	const bool AI_�����ڵ����_������ = false; //�������� �������¿� �ִ°�� �����ڵ�������� �ʽ��ϴ�.
	const bool AI_�����ڵ����_�κ� = false; //�κΰ� ���� ���¿� �ִ°�� �����ڵ�������� �ʽ��ϴ�.
	const bool AI_�����ڵ����_��ģ = false;//��ģ�� ���� ���¿� �ִ°�� �����ڵ�������� �ʽ��ϴ�.
	const bool AI_�����ڵ����_��ģ = false;//��ģ�� ���� ���¿� �ִ°�� �����ڵ�������� �ʽ��ϴ�.

	const bool AI_����ڵ�Ž�� = true;//AI���Ž���� ���� �ʾƵ� �������� Ž���˴ϴ�.(�����ൿ �Ҹ� ����)
	const int AI_����ڵ�Ž��_Ȯ�� = 20;
	const int AI_����ڵ�Ž��_�����Ⱓ = 360;//������ 1�⵿�� ����ڵ�Ž���� ���� �ʽ��ϴ�.


	//������翡�� ������� ����, ������ AI���� ���ÿ��� �� ��ư�, AI�� �������� ���ÿ��� ������
	//40�϶� 80������ ���ε���Ҽ� �־�� ��Ȳ�� 66�� ��밡��, ���� �°ų� �׷��� 80�뿡�� ��밡���ϱ��մϴ�.
	const bool ������_AI���� = true;
	const int ����_������_�ΰ���ġ = -15;//������ AI���� ����Ҷ�,30%Ȯ���� �� ��(��ư�) 
	const int AI_������_�ΰ���ġ = 15;//AI�� ���� ���� ����Ҷ� 30%Ȯ���� ����(����)


	//�������� �����, �⺻�������� ���¸���� Ȯ�������� ����� �����ϴµ�, AI���� ���¸���ÿ��� Ȯ���� �ƴ� 100%�� �����ϵ���
	//������ ��� �������� ���ڼ��� �״�� ����, �⺻������ Ȯ�������� ����
	const bool AI����_���¸����_��繫������ = true;

	const bool AI����_���¸����_����ó��_���� = true;//AI�� ���¸���� ���θ� Ǯ���ִ°�츦 �����մϴ�.


	class Info
	{
		pk::person@ p;
		pk::city@ city;
	};

	class Main
	{
		pk::func111_t@ prev_callback_111 = null;
		pk::func220_t@ prev_callback_220 = null;
		pk::func258_t@ prev_callback_258 = null;
		Main()
		{
			pk::bind(102, pk::trigger102_t(onInit));
			pk::bind(107, pk::trigger108_t(onNewDay));

			@prev_callback_258 = cast<pk::func258_t@>(pk::get_func(258));
			pk::reset_func(258);
			pk::set_func(258, pk::func258_t(callback258));

		}
		int callback258(pk::person@ prisoner, const pk::prisoner_info& in info)
		{
			int n = prev_callback_258(prisoner, info);
			if (n != ����ó��_�ع� || !AI����_���¸����_����ó��_����)
				return n;
			if (prisoner.mibun == �ź�_����)
				return ����ó��_�ع�;


			pk::person@ attacker;
			pk::building@ service;
			if (info.attacker.is_instance(pk::unit::type_id))
				@attacker = pk::get_person(pk::hex_object_to_unit(info.attacker).leader);
			else if (info.attacker.is_instance(pk::building::type_id))
				@attacker = pk::get_person(pk::get_taishu_id(pk::hex_object_to_building(info.attacker)));
			else
				@attacker = pk::get_person(pk::get_kunshu_id(info.attacker));

			if (pk::is_alive(attacker))
				@service = pk::get_building(attacker.service);

			// ���θ� ���� ������ �Ҽ��� ���ٸ� �ع�
			if (!pk::is_alive(service)) return ����ó��_�ع�;


			pk::printf("����ó�� �ع� -> ����:{}\n",getName(prisoner));
			return ����ó��_����;
		}

		void onInit()
		{
			_��߸���Ʈ = {};

			pk::list<pk::person@> ps = get��߸���Ʈ();
			for (int i = 0; i < ps.count; i++)
			{
				pk::person@ p = ps[i];
				Info ifo;
				@ifo.p = p;
				@ifo.city = pk::get_city(p.location);
				_��߸���Ʈ.insertLast(ifo);
			}

			if (prev_callback_111 == null)
			{
				@prev_callback_111 = cast<pk::func111_t@>(pk::get_func(111));
				pk::reset_func(111);
				pk::set_func(111, pk::func111_t(callback111));
			}
			if (prev_callback_220 == null)
			{
				@prev_callback_220 = cast<pk::func220_t@>(pk::get_func(220));
				pk::reset_func(220);
				pk::set_func(220, pk::func220_t(callback220));
			}

		}

		void onNewDay()
		{


			update������();
			update����Ž��();
			update��ߵ��();
			update���ε��();
			update����ڵ�Ž��();

			_��߸���Ʈ = {};

			pk::list<pk::person@> ps = get��߸���Ʈ();
			for (int i = 0; i < ps.count; i++)
			{
				pk::person@ p = ps[i];
				Info ifo;
				@ifo.p = p;
				@ifo.city = pk::get_city(p.location);
				_��߸���Ʈ.insertLast(ifo);
			}
		}
		
		int �̹߰߹������ȯ(pk::list<pk::person@> targets)
		{
			int count=0;
			for(int iPerson=0;iPerson < targets.count;iPerson++)
			{
				pk::person@ person = targets[iPerson];
				if(person.mibun == �ź�_�̹߰�)
					count++;
			}
			return count;
		}
		
		pk::list<pk::item@> getKunshuItem(pk::force@ force)
		{	
			pk::list<pk::item@> items;
			for(int iItem=0;iItem<����_��;iItem++)
			{
				pk::item@ item = pk::get_item(iItem);
				if(item == null)
					continue;
				if(item.owner != force.kunshu)
					continue;
				items.add(item);
			}
			return items;
		}
		
		pk::item@ getNewItem(pk::list<pk::item@> oldItems,pk::list<pk::item@> newItems)
		{
			for(int i=0;i<newItems.count;i++)
			{
				pk::item@ item = newItems[i];
				bool bFound = false;
				for(int j=0;j<oldItems.count;j++)
				{
					pk::item@ item2 = oldItems[j];
					if(item.get_id() == item2.get_id())
					{
						bFound = true;
						break;
					}
				}
				if(!bFound)
					return item;
			}
			return null;
		}
		
		void update����Ž��()
		{
			if (!AI_����Ž��)
				return;
			//����Ž���� 2���� �ѹ��� , idle �� ������, ��ߵ���� �ؾߵǱ⶧����
			if((pk::get_elapsed_days() % AI_����Ž��_�ֱ�)!=0)
			{
				//pk::u8printf("search days return{}\n",pk::get_elapsed_days());
				return;
			}
				
			
			pk::list<pk::person@> �̹߰߸���Ʈ;
			for(int i=0;i<����_��;i++)
			{
				pk::person@ person = pk::get_person(i);
				if(person.mibun != �ź�_�̹߰�)
					continue;
				�̹߰߸���Ʈ.add(person);
			}
			
			for(int i=0;i<50;i++)
			{
				pk::force@ force = pk::get_force(i);
				if (force==null or !pk::is_alive(force) or !pk::is_normal_force(force) or !pk::is_alive(pk::get_person(force.kunshu)) or force.is_player())
						continue;
				
				pk::list<pk::item@> items0 = getKunshuItem(force);
				
				pk::list<pk::city@> cities = pk::get_city_list(force);
				for(int iCity=0;iCity<cities.count;iCity++)
				{
					pk::city@ city = cities[iCity];
					pk::building@ building = pk::city_to_building(city);
					if(pk::enemies_around(building))
						continue;
					pk::list<pk::person@> plist = pk::get_idle_person_list(building);
					
					pk::list<pk::person@> targets;
					for(int iPerson=0;iPerson < �̹߰߸���Ʈ.count;iPerson++)
					{
						pk::person@ person = �̹߰߸���Ʈ[iPerson];
						if(person.location != building.get_id())
							continue;
						
						targets.add(person);
					}
					//pk::u8printf("mibun count {}\n",targets.count);
					if(targets.count==0)
						continue;
					
					int preCount = targets.count;
					
					for(int iPerson=0;iPerson < plist.count;iPerson++)
					{
						pk::person@ person = plist[iPerson];
						
						pk::search_cmd_info  ei;
						@ei.base = building;
						@ei.actor = person;
						if(pk::command(ei))
						{
							//�Ѹ� �߰��ϸ� �׸��Ѵ�, idle ������ ��뿡 ����ؾߵǱ� ����.
							if(preCount == �̹߰߹������ȯ(targets))
							{
								//test
								//pk::person@ kunshu = pk::get_person(force.kunshu);
								//string s = pk::format("\x1b[2x{}��\x1b[0x,����߰�",pk::decode(pk::get_name(kunshu)));
								//pk::history_log(kunshu.pos, force.color, pk::encode(s));
								break;
							}
							else
							{
								pk::list<pk::item@> items = getKunshuItem(force);
								if(items0.count != items.count) //������ �߰�.
								{
									pk::item@ item=getNewItem(items0, items);
									if(item!=null) 
									{	
										pk::person@ kunshu = pk::get_person(force.kunshu);
										string s = pk::format("\x1b[2x{}��\x1b[0x,���� \x1b[2x{}\x1b[0x �߰�",pk::decode(pk::get_name(kunshu)),pk::decode(item.name));
										pk::history_log(kunshu.pos, force.color, pk::encode(s));
										items0 = items;
									}
								}
							}
						}
					}//iPerson
				}//icity
			}//iForce			
		}
		
		void update��ߵ��()
		{
			if (!AI_��ߵ��)
				return;
			if ((pk::get_elapsed_days() % AI_��ߵ��_�ֱ�) != 0)
			{
				//pk::u8printf("join day return{}\n",pk::get_elapsed_days());
				return;
			}

			pk::list<pk::person@> ��߸���Ʈ = get��߸���Ʈ();
			for(int i=0;i<50;i++)
			{
				pk::force@ force = pk::get_force(i);
				if (force==null or !pk::is_alive(force) or !pk::is_normal_force(force) or !pk::is_alive(pk::get_person(force.kunshu)) or force.is_player())
						continue;
				
				pk::list<pk::city@> cities = pk::get_city_list(force);
				for(int iCity=0;iCity<cities.count;iCity++)
				{
					pk::city@ city = cities[iCity];
					pk::building@ building = pk::city_to_building(city);
					if(pk::enemies_around(building))
						continue;

					pk::list<pk::person@> plist = pk::get_idle_person_list(building);
					
					//���������� ������������� ���õ�
					pk::list<pk::person@> targets;
					for(int iPerson=0;iPerson < ��߸���Ʈ.count;iPerson++)
					{
						pk::person@ person = ��߸���Ʈ[iPerson];
						if(person.location != building.get_id())
							continue;
						
						targets.add(person);
					}
					if(targets.count==0)
						continue;
					
					
					for(int iPerson=0;iPerson < plist.count;iPerson++)
					{
						pk::person@ person = plist[iPerson];
						
						pk::employ_cmd_info ei;
						@ei.base = building;
						@ei.actor = person;
						@ei.target = targets[0];
						if(pk::command(ei))
						{
							if(targets[0].mibun != �ź�_���)
							{
								pk::person@ kunshu = pk::get_person(force.kunshu);
								string s = pk::format("\x1b[2x{}��\x1b[0x,\x1b[2x{}\x1b[0x ���",pk::decode(pk::get_name(kunshu)),pk::decode(pk::get_name(targets[0])));
								pk::history_log(kunshu.pos, force.color, pk::encode(s));
								
								targets.remove_at(0);
								if(targets.count == 0)
									break;
							}
						}
					}
				}//icity
			}//iForce
		}//��ߵ��

		void update������()
		{
			if (!AI_������)
				return;
			if (pk::get_day() != 1)
				return;
			if (pk::get_elapsed_days() < AI_������_�����Ⱓ)
				return;

			pk::list<pk::person@> ps = get��߸���Ʈ();
			for (int i = 0; i < ps.count; i++)
			{
				pk::person@ p = ps[i];
				Info@ ifo = get���Info(p);
				if(ifo==null)
					continue;
				if(ifo.city==null || p.location != ifo.city.get_id())
					continue;

				pk::force@ f = ifo.city.get_force_id() != -1 ? pk::get_force(ifo.city.get_force_id()) : null;
				if(f == null)
					continue;
				if(f.is_player())
					continue;

				p.mibun = �ź�_�Ϲ�;
				p.location = ifo.city.get_id();
				p.service = ifo.city.get_id();
				p.district = pk::city_to_building(ifo.city).get_district_id();
				p.loyalty = 100;
				p.update();

				string str = pk::format("\x1b[2x{}��\x1b[0x,\x1b[1x{}\x1b[0x,\x1b[24x{}\x1b[0x ���� ������", getName(f), getName(ifo.p), getName(pk::get_building(ifo.p.service)));
				pk::history_log(ifo.p.get_pos(), f != null ? f.color : 0, pk::encode(str));
			}
		}

		void update���ε��()
		{
			if (!AI_�����ڵ����)
				return;
			for (int i = 0; i < ����_��; i++)
			{
				pk::person@ person = pk::get_person(i);
				if (person.mibun != �ź�_����)
					continue;
				//������� ���δ� Ȯ����
				if(person.get_force_id() == -1 && !pk::rand_bool(AI_�����ڵ����_Ȯ��))
					continue;
				if (person.loyalty >= (person.is_player() ? AI_�����ڵ����_�漺��_���� : AI_�����ڵ����_�漺��))
					continue;

				bool b������ = false;
				pk::list<pk::person@> ������ = pk::get_gikyoudai_list(person);
				if (������.count > 0)
				{
					for (int j = 0; j < ������.count; j++)
					{
						pk::person@ p = ������[j];
						if(p.get_id() == person.get_id())
							continue;
						if(p.get_force_id() != person.get_force_id())
							continue;
						b������ = true;
						break;
					}
				}
				if(!AI_�����ڵ����_������ && b������)
					continue;

				bool b�κ� = false;
				if (person.spouse >= 0)
				{
					pk::person@ p = pk::get_person(person.spouse);
					if (p != null && p.get_force_id() == person.get_force_id())
						b�κ� = true;
				}
				if(!AI_�����ڵ����_�κ� && b�κ�)
					continue;

				bool b�ƹ��� = false;
				if (person.father >= 0)
				{
					pk::person@ p = pk::get_person(person.father);
					if (p != null && p.get_force_id() == person.get_force_id())
						b�ƹ��� = true;
				}
				if (!AI_�����ڵ����_��ģ && b�ƹ���)
					continue;

				bool b��Ӵ� = false;
				if (person.mother >= 0)
				{
					pk::person@ p = pk::get_person(person.mother);
					if (p != null && p.get_force_id() == person.get_force_id())
						b��Ӵ� = true;
				}
				if (!AI_�����ڵ����_��ģ && b��Ӵ�)
					continue;


				pk::building@ b = null;
				if (person.location < �ǹ�_������)
				{
					@b = pk::get_building(person.location);
				}
				else 
				{
					pk::unit@ u = pk::get_unit(person.get_pos());
					@b = u!=null ? pk::get_building(pk::get_person(u.leader).service) : null;
					//pk::printf("����:{},{},{}\n", getName(person), getNameLeader(u),getName(b));
				}
				if (b == null || (b.facility != �ü�_���� && b.facility != �ü�_���� && b.facility != �ü�_�ױ�))
					continue;
				if(b.is_player())
					continue;

				pk::force@ f = pk::get_force(b.get_force_id());
				if(f==null)
					continue;

				bool bPlayer = person.is_player();

				person.mibun = �ź�_�Ϲ�;
				person.service = b.get_id();
				person.location = b.get_id();
				person.district = b.get_district_id();
				person.loyalty = 100;
				person.update();

				string str = pk::format("\x1b[2x{}��\x1b[0x,\x1b[1x{}\x1b[0x,\x1b[24x{}\x1b[0x ���� ���ε��", getName(f), getName(person), getName(b));
				pk::history_log(person.get_pos(), f != null ? f.color : 0, pk::encode(str));
				if (bPlayer)
				{
					str = pk::format("\x1b[1x{}\x1b[0x�� \x1b[2x{}��\x1b[0x���� ����߽��ϴ�.",getName(person),getName(f));
					pk::message_box(pk::encode(str),pk::get_person(����_����));
				}
			}
		}

		void update����ڵ�Ž��()
		{
			if (!AI_����ڵ�Ž��)
				return;
			if (pk::get_elapsed_days() < AI_����ڵ�Ž��_�����Ⱓ)
				return;

			for (int i = 0; i < ����_��; i++)
			{
				pk::person@ person = pk::get_person(i);
				if (person.mibun != �ź�_�̹߰�)
					continue;

				pk::building@ b = pk::get_building(person.location);
				if(b == null || b.is_player())
					continue;
				if(!pk::rand_bool(AI_����ڵ�Ž��_Ȯ��))
					continue;

				person.mibun = �ź�_���;
				person.update();


				string str = pk::format("\x1b[1x{}\x1b[0x,\x1b[24x{}\x1b[0x ���� ������ ����", getName(person), getName(b));
				pk::history_log(person.get_pos(), 0, pk::encode(str));
			}
		}

		Info@ get���Info(pk::person@ p)
		{
			for (int i = 0; i < _��߸���Ʈ.length; i++)
			{
				Info@ ifo = _��߸���Ʈ[i];
				if (ifo.p.get_id() == p.get_id())
					return ifo;
			}
			return null;
		}

		array<Info> _��߸���Ʈ;
		pk::list<pk::person@> get��߸���Ʈ()
		{
			pk::list<pk::person@> ��߸���Ʈ;
			for (int i = 0; i < ����_��; i++)
			{
				pk::person@ person = pk::get_person(i);
				if (person.mibun != �ź�_���)
					continue;
				��߸���Ʈ.add(person);
			}
			��߸���Ʈ.sort(function(a, b) {
				int sumA = 0;
				for (int i = 0; i < ����ɷ�_��; i++)
					sumA += a.base_stat[i];
				int sumB = 0;
				for (int i = 0; i < ����ɷ�_��; i++)
					sumB += b.base_stat[i];

				return sumA > sumB;
			});

			return ��߸���Ʈ;
		}


		void callback220(const pk::destroy_info& in info, pk::list<pk::person@>& captured, pk::list<pk::person@>& escaped, bool tactics_bonus)
		{
			prev_callback_220(info, captured, escaped, tactics_bonus);
			if (!AI����_���¸����_��繫������)
				return;

			pk::hex_object@ attacker = info.attacker;
			pk::hex_object@ target = info.target;

			int attacker_force_id = attacker.get_force_id();
			int target_force_id = target.get_force_id();
			pk::building@ attacker_building = attacker.get_type_id() == pk::building::type_id ? attacker : null;
			pk::unit@ attacker_unit = attacker.get_type_id() == pk::unit::type_id ? attacker : null;
			pk::building@ target_building = target.get_type_id() == pk::building::type_id ? target : null;
			pk::unit@ target_unit = target.get_type_id() == pk::unit::type_id ? target : null;
			int target_border_radius = pk::is_alive(target_building) and target_building.facility == �ü�_���� ? 2 : 1;
			pk::point attacker_pos = attacker.get_pos();
			pk::point target_pos = target.get_pos();
			bool in_border = pk::is_in_range(target_pos, target_border_radius, attacker_pos);
			bool cant_capture = !pk::is_valid_normal_force_id(attacker_force_id) or !pk::is_valid_normal_force_id(target_force_id);
			bool penalty = pk::get_scenario().difficulty == ���̵�_Ư�� and attacker.is_player() and not target.is_player();
			bool has_hobaku_skill = false;
			int hobaku_chance = 0;

			if (pk::is_alive(target_building) && !info.releasable && !attacker.is_player())
			{
				pk::printf("escaped:{},captured:{}\n",escaped.count,captured.count);

				pk::list<pk::person@> ps = pk::get_person_list(target_building, pk::mibun_flags(�ź�_����, �ź�_����, �ź�_�¼�, �ź�_�Ϲ�));
				captured.clear();
				for (int i = 0; i < ps.count; i++)
				{
					pk::person@ p = ps[i];
					pk::printf("���� -> ����:{}\n", getName(p));
					captured.add(p);
				}
				escaped.clear();
			}
		}


		bool callback111(pk::person@ target, pk::person@ actor, int type, int seed)
		{
			bool b = prev_callback_111(target, actor, type, seed);
			if (!������_AI����)
				return b;

			bool bPlayer0 = actor != null && actor.is_player();
			bool bPlayer1 = target != null && target.is_player();
			if (!bPlayer0 && !bPlayer1)
				return b;
			if (target != null && target.mibun == �ź�_���)
				return b;
			if (target.mibun == �ź�_���� && target.get_force_id() == -1)
				return b;

			if (bPlayer0 && !bPlayer1) //������ ���
			{
				//���������� ����
				if (!b)
					return b;

				//��ư��ؼ� ���
				return _callback111(target, actor, type, seed, ����_������_�ΰ���ġ);
			}
			else if (!bPlayer0 && bPlayer1) //AI�� ���
			{
				//���������� ����
				if (b)
					return b;
				//�����ؼ� ���
				return _callback111(target, actor, type, seed, AI_������_�ΰ���ġ);
			}

			return b;


		}

		bool _callback111(pk::person@ target, pk::person@ actor, int type, int seed,int off)
		{
			if (!pk::is_alive(target) or !pk::is_alive(actor)) return false;

			// ���� ������ ���ְ� ���ٸ� �׻� ����
			pk::person@ actor_kunshu = pk::get_person(pk::get_kunshu_id(actor));
			if (!pk::is_alive(actor_kunshu)) return false;

			// Ư���� ���谡 �ִ��� Ȯ��
			pk::bool_bool tuple = func_4b0040(target, actor, type);
			if (tuple.first) return tuple.second;

			int giri = 10;
			if (type != 0) giri = pk::min(15 - target.giri * 2, 10);
			int n = pk::min(func_5c6030(target, actor, type, seed) * giri / 10, 100);

			// ����ó���� ���
			if (type != 0) return pk::rand_bool(n);

			return (n + off)> pk::rand(100, seed, target.get_id(), actor.get_id(), target.loyalty, actor.stat[����ɷ�_�ŷ�], pk::get_aishou_distance(actor, target.get_id()), 0);
		}

		/**
			��ǥ ����� ���� ���� ���̿� Ư���� ���谡 �ִ��� �Ǵ��մϴ�.
			@return Ư���� ���� ����, ��� ���� ����
		*/
		pk::bool_bool func_4b0040(pk::person@ target, pk::person@ actor, int type)
		{
			int target_force_id = target.get_force_id();
			// ��ȯ �������� ��Ÿ��
			bool is_valid_target_force_id = pk::is_valid_force_id(target_force_id);

			// ��ǥ ������ ������ ���
			if (type == 2) is_valid_target_force_id = false;

			if (!pk::is_alive(target) or !pk::is_alive(actor)) return pk::bool_bool(true, false);

			int actor_kunshu_id = pk::get_kunshu_id(actor);
			pk::person@ actor_kunshu = pk::get_person(actor_kunshu_id);

			// ���� ������ ���¿� ���ְ� ���� ��� �׻� ����
			if (!pk::is_alive(actor_kunshu)) return pk::bool_bool(true, false);

			// ��ǥ ������ ��� ���� ���ְ� ���� ������ ������ ��� �׻� ����
			if (target.banned_kunshu == actor_kunshu_id) return pk::bool_bool(true, false);

			// ��ǥ ������ ������ ��� �׻� ����
			if (target.mibun == �ź�_���� and is_valid_target_force_id) return pk::bool_bool(true, false);

			pk::person@ target_gikyoudai = pk::get_person(target.gikyoudai);

			// ��ǥ ������ ������ ����(2��)
			if (pk::is_alive(target_gikyoudai) and @target_gikyoudai != @target)
			{
				// ��ǥ ������ �������� ���� ������ ��� �׻� ����
				if (is_valid_target_force_id and pk::is_valid_force_id(target_force_id) and target_gikyoudai.get_force_id() == target_force_id) return pk::bool_bool(true, false);
				// ��ǥ ������ ���� ���� ������ ���ֳ� ���� ����� �������� ��� �׻� ����
				if (@target_gikyoudai == @actor_kunshu or @target_gikyoudai == @actor) return pk::bool_bool(true, true);
			}

			pk::person@ target_spouse = pk::get_person(target.spouse);

			// ��ǥ ������ ����ڿ� ���� ������ ��� �׻� ����
			if (pk::is_alive(target_spouse))
			{
				if (is_valid_target_force_id and pk::is_valid_force_id(target_force_id) and target_spouse.get_force_id() == target_force_id)
					return pk::bool_bool(true, false);
			}

			pk::list<pk::person@> target_gikyoudai_list = pk::get_gikyoudai_list(target);

			// ��ǥ ������ �������� ���� ������ ��� �׻� ����
			if (is_valid_target_force_id and pk::is_alive(target_gikyoudai) and pk::is_valid_force_id(target_force_id))
			{
				for (int i = 0; i < target_gikyoudai_list.size; i++)
				{
					if (target_gikyoudai_list[i].get_force_id() == target_force_id)
						return pk::bool_bool(true, false);
				}
			}

			// ��ǥ ������ �������� �ٸ� ���¿� �ҼӵǾ� �ִٸ� �׻� ����
			if (pk::is_alive(target_gikyoudai) and @target_gikyoudai != @target)
			{
				int gikyoudai_force_id = target_gikyoudai.get_force_id();
				if (is_valid_target_force_id or target_force_id != gikyoudai_force_id)
				{
					if (pk::is_valid_force_id(gikyoudai_force_id) and actor_kunshu.get_force_id() != gikyoudai_force_id)
						return pk::bool_bool(true, false);
				}
			}

			// ��ǥ ������ ����ڰ� �ٸ� ���¿� �ҼӵǾ� �ִٸ� �׻� ����
			if (pk::is_alive(target_spouse))
			{
				int spouse_force_id = target_spouse.get_force_id();
				if (is_valid_target_force_id or target_force_id != spouse_force_id)
				{
					if (pk::is_valid_force_id(spouse_force_id) and actor_kunshu.get_force_id() != spouse_force_id)
						return pk::bool_bool(true, false);
				}
			}

			// ��ǥ ������ ����ڰ� ���� �����̰ų� ���� ������ ������ ��� �׻� ����
			if (pk::is_alive(target_spouse))
			{
				if (@target_spouse == @actor_kunshu or @target_spouse == @actor)
					return pk::bool_bool(true, true);
			}

			// ��ǥ ������ ���� ������ ���ָ� �����ϴ� ��� �׻� ����
			if (pk::is_dislike(target, actor_kunshu_id)) return pk::bool_bool(true, false);

			int actor_id = actor.get_id();

			// ��ǥ ������ ���� ������ �����ϴ� ��� �׻� ����
			if (pk::is_dislike(target, actor_id)) return pk::bool_bool(true, false);

			int actor_force_id = actor.get_force_id();
			int target_kunshu_id = pk::get_kunshu_id(target);

			if (type == 0)
			{
				// ��ǥ ������ ���� ����� �������� �κ��̰ų�, ���� ������ ���ֿ� �������� �κ��ΰ�� �׻� ����
				if (pk::is_gikyoudai(target, actor_id) or pk::is_gikyoudai(target, actor_kunshu_id) or pk::is_fuufu(target, actor_id) or pk::is_fuufu(target, actor_kunshu_id)) return pk::bool_bool(true, true);

				// ��ǥ ������ �漺��, �Ǹ� ���� 96 �̻��� ��� �׻� ����
				if (target.loyalty + target.giri >= 96) return pk::bool_bool(true, false);

				// ��ǥ ������ �������� ���� ������ ���¿� �ҼӵǾ� �ִٸ� �׻� ����
				if (pk::is_alive(target_gikyoudai) and target_gikyoudai.get_force_id() == actor_force_id) return pk::bool_bool(true, true);

				// ��ǥ ������ ����ڰ� ���� ������ ���¿� �ҼӵǾ� �ִٸ� �׻� ����
				if (pk::is_alive(target_spouse) and target_spouse.get_force_id() == actor_force_id) return pk::bool_bool(true, true);

				// ��ǥ ������ ��ǥ ������ ���ָ� ģ���Ѵٸ� �׻� ����
				if (target.mibun != �ź�_���� and pk::is_valid_person_id(target_kunshu_id) and pk::is_like(target, target_kunshu_id)) return pk::bool_bool(true, false);

				// ��ǥ ������ ���� �����̳� ���� ������ ���ָ� ģ���Ѵٸ� �׻� ����
				if (pk::is_like(target, actor_id) or pk::is_like(target, actor_kunshu_id)) return pk::bool_bool(true, true);
			}
			else
			{
				// ��ǥ ������ �������� ���� ������ ���¿� �ҼӵǾ� �ִٸ� �׻� ����
				for (int i = 0; i < target_gikyoudai_list.size; i++)
				{
					if (target_gikyoudai_list[i].get_force_id() == actor_force_id)
						return pk::bool_bool(true, true);
				}

				// ��ǥ ������ ����ڰ� ���� ������ ���¿� �ҼӵǾ� �ִٸ� �׻� ����
				if (pk::is_alive(target_spouse) and target_spouse.get_force_id() == actor_force_id) return pk::bool_bool(true, true);

				// ��ǥ ������ ��ǥ ������ ���ָ� ģ���Ѵٸ� �׻� ����
				if (is_valid_target_force_id and target.mibun != �ź�_���� and pk::is_valid_person_id(target_kunshu_id) and pk::is_like(target, target_kunshu_id)) return pk::bool_bool(true, false);

				// ��ǥ ������ ���� ������ ���ָ� ģ���Ѵٸ� �׻� ����
				if (pk::is_like(target, actor_kunshu_id)) return pk::bool_bool(true, true);
			}

			return pk::bool_bool(false, false);
		}

		/***/
		int func_5c6030(pk::person@ target, pk::person@ actor, int type, int seed)
		{
			if (!pk::is_alive(target) or !pk::is_alive(actor)) return 0;

			int loyalty = target.loyalty;
			int aishou = 25;
			int giri = target.giri;
			int target_kunshu_id = pk::get_kunshu_id(target);
			int actor_kunshu_id = pk::get_kunshu_id(actor);
			int n = 0;

			if (type == 2)
				loyalty = pk::min(loyalty, 70);

			// ��ǥ ������ ����̰ų� ����� ������ ������ ���
			if (target.mibun == �ź�_��� or (target.mibun == �ź�_���� and !pk::is_valid_force_id(target.get_force_id())))
				loyalty = pk::get_scenario().difficulty == ���̵�_�ʱ� ? 60 : 70;

			if (pk::is_valid_person_id(target_kunshu_id))
				aishou = pk::get_aishou_distance(target, target_kunshu_id);

			if (target.mibun == �ź�_���)
				giri = �Ǹ�_����;

			n = (aishou - pk::get_aishou_distance(target, actor_kunshu_id)) / 5;
			n -= (giri + 18) * loyalty * 5 / 100;
			n += pk::max(actor.stat[����ɷ�_�ŷ�], 30) * 3 / 5;
			n -= pk::is_like(target, target_kunshu_id) ? 15 : 0;
			n -= pk::is_oyako(target, target_kunshu_id) ? 15 : 0;
			n += pk::is_dislike(target, target_kunshu_id) ? 15 : 0;
			n += pk::rand(�Ǹ�_�� - giri, actor.get_id(), target.get_id(), actor.stat[����ɷ�_�ŷ�], seed, actor_kunshu_id, 0, 0);
			n += target.mibun == �ź�_���� ? 15 : 0;
			n += 45;

			return pk::max(n, 0);
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


