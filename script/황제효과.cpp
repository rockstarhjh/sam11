/*
@������: ũ���Ƚ�
@Update: 2023.8.26,���ʹ���
@Update: 2023.8.27,�ױ����� �Ʒý� ��¿ö��� �ʴ¹��� ����
@Update: 2023.8.31,AI�� ����Ȯ���� ������ ����, AI�� �������ݸ���� ����, 
@Update: 2023.9.1,AI������ ���ְ� �켱������ �������� ���׸� ����.
@Update: 2024.1.31,�������ݸ�ɽ� �����ð��� 1�� ����
@Update: 2024.3.6,��������, �������ݸ�� �ɼ� �߰�.
@Update: 2024.5.13,IsAlready ���׼���
@Update: 2024.5.22, ���������� �߸��Ǵ� ���׼���
@Update: 2024.5.27, ����� ���� ���ŵǴ� ���׼���
@Update: 2024.6.6, ���� ���ݸ�� �ൿ�� ����
*/

namespace Ȳ��ȿ��_Emperor
{
	

	const int �ൿ�� = 20;
	const bool Ȳ��_����_���� = false;
	const bool ��_����_���� = false;

	const bool �������� = true;
	const bool �������ݸ�� = true;

	const float AI_����_����_��_���� = 0.3; //AI���� 30% ���Ϸ� ������ �����Ҽ� ������ ������.
	const int ����_�������ݸ��_�Ⱓ = 360; //1��
	const int AI_�������ݸ��_Ȯ�� = 5; //5%, 1�⿡ 1~2ȸ �õ�

	const int �۾������� = FONT_BIG;
	//const int �۾������� = FONT_SMALL;        
	const int ������ġ_���� = 200;
	const int ������ġ_���� = 600;

	const bool ���� = true;
	const int �����÷� = 0x40000000;
	const int �������� = 10;



	const bool Ȳ��_�߰�_��_ȹ�� = true;
	float Ȳ��_�߰�_��_���� = 0.5;

	const bool Ȳ��_�߰�_����_ȹ�� = true;
	float Ȳ��_�߰�_����_���� = 0.5;

	const bool Ȳ��_�߰�_�ⱳ_ȹ�� = true;
	int Ȳ��_�߰�_�ⱳ = 100;

	const bool Ȳ��_�߰�_�ൿ��_ȹ�� = true;
	float Ȳ��_�߰�_�ൿ��_���� = 0.5;

	const bool Ȳ��_�߰�_�漺������_ȹ�� = true;
	float Ȳ��_�߰�_�漺������_���� = 0.5;

	const bool Ȳ��_�߰�_ġ������_ȹ�� = true;
	float Ȳ��_�߰�_ġ������_���� = 0.5;

	const bool Ȳ��_�߰�_¡��ġ������_ȹ�� = true;
	float Ȳ��_�߰�_¡��ġ������_���� = 0.5;

	const bool Ȳ��_�߰�_¡������_ȹ�� = false;
	float Ȳ��_�߰�_¡������_���� = 0.2;

	const bool Ȳ��_�߰�_������Ȯ��_ȹ�� = true;
	float Ȳ��_�߰�_������Ȯ��_���� = 0.5;

	const bool Ȳ��_�߰�_���_ȹ�� = true;
	float Ȳ��_�߰�_���_���� = 0.5;


	const bool AI_����_����_���_���� = true;
	int AI_����_��_�ּҺ��� = 10000;
	int AI_����_��_�ּҺ��� = 20000;

	int AI_����_��_�ּҺ���_����_�ױ� = 5000;
	int AI_����_��_�ּҺ���_����_�ױ� = 10000;


	int AI_����_����1_�����ϼ� = 200; //�ٷ������� ������ �����ϼ�
	int AI_����_����2_�����ϼ� = 260; //�Ѵܰ� �ǳʶپ ������ ��� ������ ���� �ϼ�
	int AI_����_����3_�����ϼ� = 320; //�δܰ� �ǳʶپ ������ ��� ������ ���� �ϼ�


	const array<int> ������� =
	{
		300000,//Ȳ��
		250000,//��
		200000,//��
		150000,//��縶
		100000,//���屺
		60000,//�����߶���
		40000,//�츲�߶���
		20000,//�ָ�
		10000//���ڻ�
	};

	array<int> �������굵�� =
	{
		����_��, ����_����, ����_����, ����_���, ����_����, ����_����, ����_����, ����_����, ����_���, ����_�û�, ����_����, ����_����, ����_�ž�, ����_����,����_�Ǿ�, ����_���,����_���,����_����
	};

	const int KEY = pk::hash("Ȳ��ȿ��");

	class ForceInfo
	{
		pk::force@ force;
		int startDay;
		pk::city@ city;
	};

	class AllyInfo
	{
		pk::force@ force0;
		pk::force@ force1;
		int troops0;
		int troops1;
	};

	class AttackInfo
	{
		array<pk::person@> members = { null,null,null };
		int food;
		int troops;
		int money = 0;
		int ����;
		bool b����=false;
		bool b����=false;

	};

	class Main
	{

		pk::func100_t@ prev_callback_100;
		pk::func101_t@ prev_callback_101;
		pk::func104_t@ prev_callback_104;
		pk::func105_t@ prev_callback_105;
		pk::func150_t@ prev_callback_150;
		pk::func151_t@ prev_callback_151;
		pk::func152_t@ prev_callback_152;
		pk::func153_t@ prev_callback_153;
		pk::func155_t@ prev_callback_155;
		pk::func158_t@ prev_callback_158;
		pk::func162_t@ prev_callback_162;

		Main()
		{
			if (��������)
			{
				pk::menu_item item;
				item.menu = 105;
				item.pos = 13;
				item.init = pk::building_menu_item_init_t(BuyTitleInit);
				item.is_enabled = pk::menu_item_is_enabled_t(IsBuyTitleEnabled);
				item.get_text = pk::menu_item_get_text_t(GetBuyTitleText);
				item.get_desc = pk::menu_item_get_desc_t(GetBuyTitleDesc);
				item.handler = pk::menu_item_handler_t(BuyTitleHandler);
				pk::add_menu_item(item);
			}

			if (�������ݸ��)
			{
				pk::menu_item item�������ݸ��;
				item�������ݸ��.menu = 103;
				item�������ݸ��.pos = 13;
				item�������ݸ��.init = pk::building_menu_item_init_t(TitleAttackCommandInit);
				item�������ݸ��.is_enabled = pk::menu_item_is_enabled_t(IsTitleAttackCommandEnabled);
				item�������ݸ��.get_text = pk::menu_item_get_text_t(GetTitleAttackCommandText);
				item�������ݸ��.get_desc = pk::menu_item_get_desc_t(GetTitleAttackCommandDesc);
				item�������ݸ��.handler = pk::menu_item_handler_t(TitleAttackCommandHandler);
				pk::add_menu_item(item�������ݸ��);
			}



			@prev_callback_100 = cast<pk::func100_t@>(pk::get_func(100));
			pk::reset_func(100);
			pk::set_func(100, pk::func100_t(func100));                // 150 �� ����


			@prev_callback_101 = cast<pk::func101_t@>(pk::get_func(101));
			pk::reset_func(101);
			pk::set_func(101, pk::func101_t(func101));                // 150 �� ����


			@prev_callback_104 = cast<pk::func104_t@>(pk::get_func(104));
			pk::reset_func(104);
			pk::set_func(104, pk::func104_t(func104));                // 150 �� ����

			@prev_callback_105 = cast<pk::func105_t@>(pk::get_func(105));
			pk::reset_func(105);
			pk::set_func(105, pk::func105_t(func105));                // 150 �� ����

			@prev_callback_150 = cast<pk::func150_t@>(pk::get_func(150));
			pk::reset_func(150);
			pk::set_func(150, pk::func150_t(func150));                // 150 �� ����

			@prev_callback_151 = cast<pk::func151_t@>(pk::get_func(151));
			pk::reset_func(151);
			pk::set_func(151, pk::func151_t(func151));                // 151 ���� ����

			@prev_callback_152 = cast<pk::func152_t@>(pk::get_func(152));
			pk::reset_func(152);
			pk::set_func(152, pk::func152_t(func152));                // 152 ����,�ױ�, �� ����

			@prev_callback_153 = cast<pk::func153_t@>(pk::get_func(153));
			pk::reset_func(153);
			pk::set_func(153, pk::func153_t(func153));                // 153 ����,�ױ�, ���� ����


			@prev_callback_155 = cast<pk::func155_t@>(pk::get_func(155));
			pk::reset_func(155);
			pk::set_func(155, pk::func155_t(func155));                // 153 ����,�ױ�, ���� ����

			@prev_callback_158 = cast<pk::func158_t@>(pk::get_func(158));
			pk::reset_func(158);
			pk::set_func(158, pk::func158_t(func158));                // 153 ����,�ױ�, ���� ����

			@prev_callback_162 = cast<pk::func162_t@>(pk::get_func(162));
			pk::reset_func(162);
			pk::set_func(162, pk::func162_t(func162));                // �ൿ��

			pk::bind(107, pk::trigger107_t(onNewDay));
			pk::bind(102, pk::trigger102_t(Init));
			pk::bind(105, pk::trigger105_t(SaveData));

			pk::bind(120, pk::trigger120_t(UpdatePerFrame));


		}
		void Init()
		{
			LoadData();
		}

		void LoadData()
		{
			while (_fis.length > 0)
				_fis.removeLast();

			int count = int(pk::load(KEY, 0, 0));
			int loadIndex = 1;
			for (int i = 0; i < count; i++)
			{
				ForceInfo fi;
				@fi.force = pk::get_force(int(pk::load(KEY, loadIndex++, -1)));
				fi.startDay = int(pk::load(KEY, loadIndex++, -1));
				@fi.city= pk::get_city(int(pk::load(KEY, loadIndex++, -1)));
				_fis.insertLast(fi);
			}

			//pk::u8printf("load count {}\n",_moveInfo.length);
		}

		void SaveData(int file_id)
		{
			pk::store(KEY, 0, _fis.length);
			int saveIndex = 1;
			for (int i = 0; i < _fis.length; i++)
			{
				ForceInfo@ mi = _fis[i];
				pk::store(KEY, saveIndex++, mi.force.get_id());
				pk::store(KEY, saveIndex++, mi.startDay);
				pk::store(KEY, saveIndex++, mi.city.get_id());
			}
		}

		void UpdatePerFrame()
		{
			if (_fis.length == 0)
				return;

			int w = ������ġ_����;
			int h = ������ġ_����;
			int xMax = -1;

			for (int i = 0; i < _fis.length; i++)
			{
				ForceInfo@ fi = _fis[i];
				string str = pk::format("��������:\x1b[2x{}\x1b[0x��,{}", (fi.startDay + ����_�������ݸ��_�Ⱓ - pk::get_elapsed_days()) / 10, pk::decode(pk::get_name(fi.city)));
				int offset = (�۾������� == FONT_BIG ? 30 : 20);


				pk::point point;
				point.x = w;
				point.y = h; h += offset;
				pk::draw_text(pk::encode(str), point, -1, �۾�������, 0x00000000);

				pk::size size0 = pk::get_size(�۾�������, pk::encode(str));
				if (size0.width > xMax)
					xMax = size0.width;
			}
			if (����)
			{
				int off = ��������;
				pk::point pt(������ġ_���� - off, ������ġ_���� - off);
				pk::rectangle r1(pt, pk::size(xMax + off * 2, h - ������ġ_���� + off * 2));
				pk::draw_filled_rect(r1, �����÷�);
			}




		}


		void Ȳ���߰��ⱳ()
		{
			if (!Ȳ��_�߰�_�ⱳ_ȹ��)
				return;

			pk::list<pk::force@> forces = pk::get_force_list();
			for (int i = 0; i < forces.count; i++)
			{
				pk::force@ force = forces[i];
				if (!pk::is_protecting_the_emperor(force))
					continue;

				force.tp = pk::min(force.tp + Ȳ��_�߰�_�ⱳ, 10000);
				break;
			}
		}
		void AI��������()
		{
			if (!��������)
				return;
			pk::list<pk::force@> forces = pk::get_force_list();
			for (int i = 0; i < forces.count; i++)
			{
				pk::force@ force = forces[i];
				if (!pk::is_protecting_the_emperor(force))
					continue;
				if(force.is_player())
					continue;

				if (force.title == ����_Ȳ�� || force.title == ����_�� || force.title == ����_��)
					continue;

				int tgold = �������[force.title - 1];
				if(GetGold(force) * AI_����_����_��_���� < tgold)
					continue;

				BuyTitle(force, force.title - 1);

				force.title = force.title - 1;

				pk::person@ kunshu = pk::get_person(force.kunshu);
				pk::title@ title = pk::get_title(force.title);

				string str = pk::format("\x1b[2x{}\x1b[0x, \x1b[2x{}\x1b[0x ��������",pk::decode(pk::get_name(kunshu)),pk::decode(pk::get_name(title)));
				pk::history_log(kunshu.get_pos(), force.color, pk::encode(str));
				break;
			}
		}

		array<pk::force@> neighborForces(pk::force@ forceMy)
		{
			array<pk::force@> arr;
			pk::list<pk::force@> forces = pk::get_force_list();
			for (int i = 0; i < forces.count; i++)
			{
				pk::force@ force = forces[i];
				if(forceMy.get_id() == force.get_id())
					continue;

				if (!pk::is_neighbor_force(forceMy, force))
					continue;

				arr.insertLast(force);
			}
			return arr;
		}


		int getTroops(pk::force@ force)
		{
			int troops = 0;
			pk::list<pk::building@> blist = pk::get_building_list();
			for (int i = 0; i < blist.count; i++)
			{
				pk::building@ b = blist[i];
				if (b.get_force_id() != force.get_id())
					continue;

				pk::city@ city = pk::building_to_city(b);
				if (city != null)
				{
					troops += city.troops;
				}
				pk::gate@ gate = pk::building_to_gate(b);
				if (gate != null)
				{
					troops += gate.troops;
				}
				pk::port@ port = pk::building_to_port(b);
				if (port != null)
				{
					troops += port.troops;
				}
			}
			return troops;
		}

		bool isAlready(pk::force@ force)
		{
			for (int i = 0; i < _fis.length; i++)
			{
				pk::force@ force2 = _fis[i].force;
				if (force2.get_id() == force.get_id())
					return true;
			}
			return false;
		}
		
		array<pk::force@> findTargets(pk::force@ forceMy)
		{
			array<pk::force@> forces = neighborForces(forceMy);

			AllyInfo@ maxAlly = null;
			int maxTroops = 0;

			for (int i = 0; i < forces.length-1; i++)
			{
				pk::force@ force0 = forces[i];
				if(!isAlready(force0))
					continue;

				for (int j = i; j < forces.length; j++)
				{
					pk::force@ force1 = forces[j];
					if(!force0.ally[force1.get_id()])
						continue;
					if(!isAlready(force1))
						continue;

					AllyInfo ai;
					@ai.force0 = force0;
					@ai.force1 = force1;
					ai.troops0 = getTroops(force0);
					ai.troops1 = getTroops(force1);

					if (ai.troops0 + ai.troops1 > maxTroops)
					{
						maxTroops = ai.troops0 + ai.troops1;
						@maxAlly = ai;
					}
				}
			}
			return maxAlly != null ? {maxAlly.force0, maxAlly.force1} : array<pk::force@>();
		}

		void breakAlly(pk::force@ force0, pk::force@ force1)
		{
			force0.ally[force1.get_id()] = false;
			force0.relations[force1.get_id()] = 0;
			force0.ceasefire_timer[force1.get_id()] = 1;
			force1.ally[force0.get_id()] = false;
			force1.relations[force0.get_id()] = 0;
			force1.ceasefire_timer[force0.get_id()] = 1;
			force0.update();
			force1.update();
		}

		void AI���ݸ��()
		{
			if (!�������ݸ��)
				return;
			pk::list<pk::force@> forces = pk::get_force_list();
			for (int i = 0; i < forces.count; i++)
			{
				pk::force@ force = forces[i];
				if (!pk::is_protecting_the_emperor(force))
					continue;
				if (force.is_player())
					continue;
				if(!pk::rand_bool(AI_�������ݸ��_Ȯ��))
					continue;


				array<pk::force@> arr=findTargets(force);
				if(arr.length != 2)
					continue;

				//pk::force@ tmp = arr[0];
				//@arr[0] = arr[1];
				//@arr[1] = tmp;

				pk::city@ city = null;
				@city=GetTargetCity(arr[0], arr[1]);
				if(city == null)
					continue;

				if (arr.length == 2 && !arr[0].is_player() && !arr[1].is_player())
				{
					//����
					arr[0].title = arr[0].title - 1;
					//�ܱ� �����̸� ���� ����, ģ�е� 0���� ����
					breakAlly(arr[0], arr[1]);
					Attack(arr[0], arr[1]);
				}
				else if (arr.length == 2 && !arr[0].is_player() && arr[1].is_player())
				{
					arr[0].title = arr[0].title - 1;
					//�ܱ� �����̸� ���� ����, ģ�е� 0���� ����

					breakAlly(arr[0], arr[1]);
					Attack(arr[0], arr[1]);

					
					pk::person@ kunshi = pk::get_person(arr[1].gunshi);
					if (kunshi != null) 
					{
						pk::title@ title = pk::get_title(arr[0].title);
						string str = pk::format("\x1b[2x{}\x1b[0x���� \x1b[2x{}\x1b[0x�� �ް� �츮�� �����մϴ�. ���͵� �������ϴ�.",pk::decode(pk::get_name(arr[0])),pk::decode(pk::get_name(title)));
						pk::message_box(pk::encode(str), kunshi);
					}
				}
				else if (arr.length == 2 && arr[0].is_player())
				{
					@_scene_person = pk::get_person(����_����);
					@_scene_attacker = arr[0];
					@_scene_target = arr[1];
					@_scene_city = city;

					pk::scene(pk::scene_t(Scene�ܱ�AI));
					if (_scene_result)
					{
						ForceInfo fi;
						@fi.force = arr[0];
						@fi.city = city;
						fi.startDay = pk::get_elapsed_days();
						_fis.insertLast(fi);
						
						
						breakAlly(arr[0], arr[1]);
						string str = pk::format("\x1b[2x{}\x1b[0x �� \x1b[2x{}\x1b[0x�� ������ �ı�Ǿ����ϴ�.", pk::decode(pk::get_name(pk::get_person(arr[0].kunshu))), pk::decode(pk::get_name(pk::get_person(arr[1].kunshu))));
						pk::message_box(pk::encode(str));
						pk::play_se(10);

						doMerite(arr[0]);
					}
				}
				break;
			}

		}

		void doMerite(pk::force@ force)
		{
			pk::list<pk::person@> persons = pk::get_person_list(force, pk::mibun_flags(�ź�_�¼�, �ź�_����, �ź�_�Ϲ�, �ź�_����));
			for (int i = 0; i < persons.count; i++)
			{
				pk::person@ p = persons[i];
				p.loyalty += pk::rand(5);
			}

			force.title = force.title - 1;
			pk::title@ title = pk::get_title(force.title);
			string str = pk::format("\x1b[2x{}\x1b[0x �� �Ǿ����ϴ�.. ��� ������ �漺���� �����߽��ϴ�.", pk::decode(pk::get_name(title)));

			pk::message_box(pk::encode(str));

		}

		void doPenalty(pk::force@ force)
		{
			pk::list<pk::person@> persons = pk::get_person_list(force, pk::mibun_flags(�ź�_�¼�, �ź�_����, �ź�_�Ϲ�, �ź�_����));
			for (int i = 0; i < persons.count; i++)
			{
				pk::person@ p = persons[i];
				p.loyalty -= (pk::rand(5)+5);
			}

			force.title = force.title + 1;
			pk::title@ title = pk::get_title(force.title);
			if (title.get_id() == ����_����)
			{
				string str = pk::format("������ ��Ż���߽��ϴ�. ��� ������ �漺���� �϶��߽��ϴ�.", pk::decode(pk::get_name(title)));
				pk::message_box(pk::encode(str));
			}
			else 
			{
				string str = pk::format("\x1b[2x{}\x1b[0x �� ����Ǿ�����. ��� ������ �漺���� �϶��߽��ϴ�.", pk::decode(pk::get_name(title)));
				pk::message_box(pk::encode(str));
			}

		}

		array<ForceInfo> _fis;
		void ������������Ȯ��()
		{
			array<ForceInfo> removes;
			for (int i = 0; i < _fis.length; i++)
			{
				ForceInfo@ fi = _fis[i];
				if (pk::get_elapsed_days() < fi.startDay + ����_�������ݸ��_�Ⱓ)
					continue;

				pk::person@ emp = pk::get_person(����_����);
				if (fi.city.get_force_id() == fi.force.get_id())
				{
					pk::message_box(pk::encode("�ڳװ� �س��� �˾ҳ�"), emp);
					doMerite(fi.force);
				}
				else 
				{
					pk::message_box(pk::encode("�Ǹ�������"), emp);
					doPenalty(fi.force);
				}
				removes.insertLast(fi);
				break;
			}

			for (int i = 0; i < removes.length; i++)
			{
				int index = -1;
				for (int j = 0; j < _fis.length; j++)
				{
					if (removes[i].force.get_id() == _fis[j].force.get_id())
					{
						index = j;
						break;
					}
				}
				if (index != -1)
				{
					//pk::u8printf("remove {},count {}\n",_moveInfo[index].moo.get_id(),_moveInfo.length-1);
					_fis.removeAt(index);
				}
			}
		}

		void onNewDay()
		{
			Ȳ���߰��ⱳ();
			AI��������();
			AI���ݸ��();
			������������Ȯ��();
		}

		int func100(pk::building@ building, const pk::detail::arrayptr<pk::person@>& in actors)
		{
			int amount = prev_callback_100(building, actors);
			pk::force@ force = pk::get_force(building.get_force_id());
			if (force == null)
				return amount;

			if (Ȳ��_�߰�_¡������_ȹ�� and pk::is_protecting_the_emperor(force))
				amount = amount + amount * Ȳ��_�߰�_¡������_����;
			return amount;

		}
		int func101(pk::city@ city, const pk::detail::arrayptr<pk::person@>& in actors, int troops)
		{
			int amount = prev_callback_101(city, actors,troops);
			pk::force@ force = pk::get_force(city.get_force_id());
			if (force == null)
				return amount;

			if (Ȳ��_�߰�_¡��ġ������_ȹ�� and pk::is_protecting_the_emperor(force))
				amount = amount - amount * Ȳ��_�߰�_¡��ġ������_����;
			return amount;
		}

		int func104(pk::building@ building, const pk::detail::arrayptr<pk::person@>& in actors)
		{
			int amount = prev_callback_104(building,actors);
			pk::force@ force = pk::get_force(building.get_force_id());
			if (force == null)
				return amount;

			if (Ȳ��_�߰�_ġ������_ȹ�� and pk::is_protecting_the_emperor(force))
				amount = amount + amount * Ȳ��_�߰�_ġ������_����;
			return amount;
		}
		int func105(pk::building@ building, const pk::detail::arrayptr<pk::person@>& in actors)
		{
			int amount = prev_callback_105(building, actors);
			pk::force@ force = pk::get_force(building.get_force_id());
			if (force == null)
				return amount;

			if (Ȳ��_�߰�_���_ȹ�� and pk::is_protecting_the_emperor(force))
				amount = amount + amount * Ȳ��_�߰�_���_����;
			return amount;

		}
		int func150(pk::city@ city)
		{
			int gold = prev_callback_150(city);
			pk::force@ force = pk::get_force(city.get_force_id());
			if (force == null)
				return gold;


			if (Ȳ��_�߰�_��_ȹ�� and pk::is_protecting_the_emperor(force))
				gold = gold + gold * Ȳ��_�߰�_��_����;
			return gold;
		}
		int func151(pk::city@ city)
		{
			int food = prev_callback_151(city);
			pk::force@ force = pk::get_force(city.get_force_id());
			if (force == null)
				return food;

			if (Ȳ��_�߰�_����_ȹ�� and pk::is_protecting_the_emperor(force))
				food = food + food * Ȳ��_�߰�_����_����;
			return food;
		}
		int func152(pk::building@ building, int city_revenue)
		{
			int gold = prev_callback_152(building,city_revenue);
			pk::force@ force = pk::get_force(building.get_force_id());
			if (force == null)
				return gold;

			if (Ȳ��_�߰�_��_ȹ�� and pk::is_protecting_the_emperor(force))
				gold = gold + gold * Ȳ��_�߰�_��_����;
			return gold;
		}
		int func153(pk::building@ building, int city_harvest)
		{
			int food = prev_callback_153(building, city_harvest);
			pk::force@ force = pk::get_force(building.get_force_id());
			if (force == null)
				return food;

			if (Ȳ��_�߰�_����_ȹ�� and pk::is_protecting_the_emperor(force))
				food = food + food * Ȳ��_�߰�_����_����;
			return food;
		}
		int func155(pk::building@ building, pk::person@ person)
		{
			int loyalty = prev_callback_155(building, person);
			pk::force@ force = pk::get_force(building.get_force_id());
			if (force == null)
				return loyalty;

			if (Ȳ��_�߰�_�漺������_ȹ�� and pk::is_protecting_the_emperor(force) and force.get_id() == person.get_force_id())
			{
				if (person.kanshitsu == �ѽ�_�߽�)
					loyalty = 0;
				else
					loyalty = pk::max(0.0, loyalty - loyalty * Ȳ��_�߰�_�漺������_����);
			}
			return loyalty;
		}
		int func158(pk::city@ city)
		{
			int ratio = prev_callback_158(city);
			pk::force@ force = pk::get_force(city.get_force_id());
			if (force == null)
				return ratio;

			if (Ȳ��_�߰�_������Ȯ��_ȹ�� and pk::is_protecting_the_emperor(force))
				ratio = ratio - ratio * Ȳ��_�߰�_������Ȯ��_����;
			return ratio;
		}

		int func162(pk::district@ district)
		{
			int ap = prev_callback_162(district);
			pk::force@ force = pk::get_force(district.get_force_id());
			if (force == null)
				return ap;

			if (Ȳ��_�߰�_�ൿ��_ȹ�� and pk::is_protecting_the_emperor(force))
				ap = ap + ap * Ȳ��_�߰�_�ൿ��_����;
			return ap;
		}




		void TitleAttackCommandInit(pk::building@ building)
		{
			@_force = pk::get_force(building.get_force_id());
			@_building = building;
			@_city = pk::building_to_city(building);
			@_district = pk::get_district(building.get_district_id());
		}
		bool IsTitleAttackCommandEnabled()
		{
			return _district.ap >= �ൿ�� and pk::is_protecting_the_emperor(_force);
		}
		string GetTitleAttackCommandText()
		{
			return pk::encode("�������ݸ��");
		}
		string GetTitleAttackCommandDesc()
		{
			if(!pk::is_protecting_the_emperor(_force))
				return pk::encode("Ȳ���� �˸��ؾ� �մϴ�.");
			else if (_district.ap < �ൿ��)
				return pk::encode(pk::format("�ൿ���� �����մϴ�.(�ൿ��{})", �ൿ��));
			else
				return pk::encode(pk::format("�Ѽ��¿��� ������ �ο��ϰ� �ٸ������� �����ϵ��� �մϴ�. �ൿ��{},Ȳ���˸�)", �ൿ��));
		}

		pk::city@ GetTargetCity(pk::force@ attacker, pk::force@ target)
		{
			//������ ���¼��°��� ������ ����, ������ �ܱ��������� �����Ѵ�.

			int maxNeighborCount = -1;
			int maxTroops = -1;
			pk::city@ maxCity = null;

			pk::list<pk::city@> attackerCities = pk::get_city_list(attacker);
			pk::list<pk::city@> targetCities = pk::get_city_list(target);
			for (int i = 0; i < targetCities.count; i++)
			{
				pk::city@ c = targetCities[i];

				int ncount = 0;

				for (int j = 0; j < attackerCities.count; j++)
				{
					pk::city@ c2 = attackerCities[j];
					int dist = pk::get_city_distance(c.get_id(), c2.get_id());
					if (dist == 1)
						ncount++;
				}

				if (ncount > maxNeighborCount or (ncount == maxNeighborCount and c.troops < maxTroops ))
				{
					maxNeighborCount = ncount;
					maxTroops = c.troops;
					@maxCity = c;
				}
			}

			return maxCity;
		}

		bool Ư��üũ(pk::person@ p, int ����)
		{
			//����,����,�п�,����,�ɰ��� ��� ������ �����ϴ�

			if (pk::has_skill(p, Ư��_����) or pk::has_skill(p, Ư��_����) or pk::has_skill(p, Ư��_�п�) or pk::has_skill(p, Ư��_����) or
				pk::has_skill(p, Ư��_����) or pk::has_skill(p, Ư��_��ǳ) or pk::has_skill(p, Ư��_�޽�) or pk::has_skill(p, Ư��_����) or
				pk::has_skill(p, Ư��_�Ⱒ) or pk::has_skill(p, Ư��_����) or pk::has_skill(p, Ư��_����) or pk::has_skill(p, Ư��_����) or
				pk::has_skill(p, Ư��_�ұ�) or pk::has_skill(p, Ư��_�ݰ�) or pk::has_skill(p, Ư��_ö��) or pk::has_skill(p, Ư��_���) or
				pk::has_skill(p, Ư��_����) or pk::has_skill(p, Ư��_����) or pk::has_skill(p, Ư��_ȣ��) or pk::has_skill(p, Ư��_ȭ��) or
				pk::has_skill(p, Ư��_��) or pk::has_skill(p, Ư��_�ⷫ) or pk::has_skill(p, Ư��_�˰�) or pk::has_skill(p, Ư��_���) or
				pk::has_skill(p, Ư��_����) or pk::has_skill(p, Ư��_��å) or pk::has_skill(p, Ư��_����) or pk::has_skill(p, Ư��_����) or
				pk::has_skill(p, Ư��_ȭ��) or pk::has_skill(p, Ư��_�Ż�) or pk::has_skill(p, Ư��_����) or pk::has_skill(p, Ư��_�͸�) or
				pk::has_skill(p, Ư��_��ȯ) or pk::has_skill(p, Ư��_�ɸ�) or pk::has_skill(p, Ư��_�ݰ�) or pk::has_skill(p, Ư��_�汹) or
				pk::has_skill(p, Ư��_���) or pk::has_skill(p, Ư��_�͹�) or pk::has_skill(p, Ư��_����) or pk::has_skill(p, Ư��_ħ��) or
				pk::has_skill(p, Ư��_���) or pk::has_skill(p, Ư��_�־�) or pk::has_skill(p, Ư��_�û�) or pk::has_skill(p, Ư��_�༺))
			{
				return true;
			}

			if (���� == ����_�⺴)
			{
				if (pk::has_skill(p, Ư��_����) or pk::has_skill(p, Ư��_����) or pk::has_skill(p, Ư��_����) or pk::has_skill(p, Ư��_�౺) or
					pk::has_skill(p, Ư��_����) or pk::has_skill(p, Ư��_�鸶) or pk::has_skill(p, Ư��_����) or pk::has_skill(p, Ư��_���))
				{
					return true;
				}
			}
			else if (���� == ����_â��)
			{
				if (pk::has_skill(p, Ư��_����) or pk::has_skill(p, Ư��_����) or pk::has_skill(p, Ư��_����) or pk::has_skill(p, Ư��_����) or
					pk::has_skill(p, Ư��_â��) or pk::has_skill(p, Ư��_����))
				{
					return true;
				}
			}
			else if (���� == ����_�غ�)
			{
				if (pk::has_skill(p, Ư��_����) or pk::has_skill(p, Ư��_����) or pk::has_skill(p, Ư��_����) or pk::has_skill(p, Ư��_����) or
					pk::has_skill(p, Ư��_����) or pk::has_skill(p, Ư��_�ؽ�) or pk::has_skill(p, Ư��_����))
				{
					return true;
				}
			}
			else if (���� == ����_�뺴)
			{
				if (pk::has_skill(p, Ư��_����) or pk::has_skill(p, Ư��_����) or pk::has_skill(p, Ư��_����) or pk::has_skill(p, Ư��_���) or
					pk::has_skill(p, Ư��_����) or pk::has_skill(p, Ư��_�ý�))
				{
					return true;
				}
			}
			else if (���� == ����_����)
			{
				if (pk::has_skill(p, Ư��_����) or pk::has_skill(p, Ư��_����) or pk::has_skill(p, Ư��_����) or pk::has_skill(p, Ư��_����) or
					pk::has_skill(p, Ư��_����) or pk::has_skill(p, Ư��_����))
				{
					return true;
				}
			}
			//������ �ϴ� ���̸� ������ ����ó���Ǵ�
			//else if (���� == ����_����)
			//{
			//	if (pk::has_skill(p, Ư��_����) or pk::has_skill(p, Ư��_��Ÿ) or pk::has_skill(p, Ư��_����) or pk::has_skill(p, Ư��_����))
			//	{
			//		return true;
			//	}
			//}
			return false;
		}

		bool Is��������(pk::city@ city)
		{
			for (int i = 0; i < �������굵��.length; i++)
			{
				if (�������굵��[i] == city.get_id())
					return true;
			}
			return false;
		}

		bool ����üũ(AttackInfo@ ai, pk::city@ city, int ����)
		{
			if (!AI_����_����_���_���� and ���� == ����_�⺴ and city.weapon_amount[����_����] < ai.troops)
				return false;
			if (!AI_����_����_���_���� and ���� == ����_â�� and city.weapon_amount[����_â] < ai.troops)
				return false;
			if (!AI_����_����_���_���� and ���� == ����_�غ� and city.weapon_amount[����_��] < ai.troops)
				return false;
			if (!AI_����_����_���_���� and ���� == ����_�뺴 and city.weapon_amount[����_��] < ai.troops)
				return false;

			if (!AI_����_����_���_���� and ���� == ����_����)
			{
				pk::force@ force = pk::get_force(city.get_force_id());
				if ((pk::has_tech(force, �ⱳ_�������) and city.weapon_amount[����_���] >= 1) or city.weapon_amount[����_����] >= 1 or
					(pk::has_tech(force, �ⱳ_��������) and city.weapon_amount[����_����] >= 1) or city.weapon_amount[����_����] >= 1)
					return true;
				else
					return false;

			}
			//������ �׻� ���������ϱ⶧���� return true;
			return true;

		}

		void makeMax����(AttackInfo@ ai,pk::city@ city,pk::city@ target)
		{
			int max���� = -1;
			int max���� = -1;

			//���� Ư��,������, ������� Ư���������� ���� , �ִ� ������ �������, ������������ �Ѵ�
			//������� �������� �ؼ�, ������ ������ �ݿ��ǵ���, �����ΰ��, �빫�� ���Ƽ�, �Ϲ������� Ư�⵵ �����Ұ��̴�.

			if (ai.members[2] != null)
			{
				pk::person@ p = ai.members[2];
				for (int i = 0; i < ����_��; i++)
				{
					//������ ������ �����ؾ���
					if(i == ����_����)
						continue;

					if (p.tekisei[i] > max���� and ����üũ(ai, city, i))
					{
						max���� = i;
						max���� = p.tekisei[i];
					}
					else if (p.tekisei[i] == max���� and ����üũ(ai, city, i))
					{
						if (Ư��üũ(p, i))
						{
							max���� = i;
							max���� = p.tekisei[i];
						}
					}
				}
			}
			if (ai.members[1] != null)
			{
				pk::person@ p = ai.members[1];
				for (int i = 0; i < ����_��; i++)
				{
					//������ ������ �����ؾ���
					if(i == ����_����)
						continue;

					if (p.tekisei[i] > max���� and ����üũ(ai, city, i))
					{
						max���� = i;
						max���� = p.tekisei[i];
					}
					else if (p.tekisei[i] == max���� and ����üũ(ai, city, i))
					{
						if (Ư��üũ(p, i))
						{
							max���� = i;
							max���� = p.tekisei[i];
						}
					}
				}
			}
			for (int i = 0; i < ����_��; i++)
			{
				//������ ������ �����ؾ���
				if(i == ����_����)
					continue;

				if (ai.members[0].tekisei[i] > max���� and ����üũ(ai, city, i))
				{
					max���� = i;
					max���� = ai.members[0].tekisei[i];
				}
				else if (ai.members[0].tekisei[i] == max���� and ����üũ(ai, city, i))
				{
					if (Ư��üũ(ai.members[0], i))
					{
						max���� = i;
						max���� = ai.members[0].tekisei[i];
					}
				}
			}


			//pk::printf("max ���� before {}\n",max����);
			pk::force@ force = pk::get_force(city.get_force_id());
			switch (max����)
			{
			case ����_�⺴:ai.���� = ����_����; break;
			case ����_�뺴:ai.���� = ����_��; break;
			case ����_â��:ai.���� = ����_â; break;
			case ����_�غ�:ai.���� = ����_��; break;
			case ����_����:
				//�������� �ֵ� ���� �켱
				if (pk::has_tech(force, �ⱳ_��������) and (AI_����_����_���_���� or city.weapon_amount[����_����] >= 1))
					ai.���� = ����_����;
				else if (AI_����_����_���_���� or city.weapon_amount[����_����] >= 1)
					ai.���� = ����_����;
				else if (pk::has_tech(force, �ⱳ_�������) and (AI_����_����_���_���� or city.weapon_amount[����_���] >= 1))
					ai.���� = ����_���;
				else if (AI_����_����_���_���� or city.weapon_amount[����_����] >= 1)
					ai.���� = ����_����;
				else
					ai.���� = ����_��;
				break;
			default:
				break;
			}

			if (Is��������(city) and Is��������(target))
			{
				if (pk::has_tech(force, �ⱳ_��������) and (AI_����_����_���_���� or city.weapon_amount[����_����] >= 1))
					ai.b���� = true;
				else if (AI_����_����_���_���� or city.weapon_amount[����_����] >= 1)
					ai.b���� = true;

			}
			return;
		}
		bool Has����(AttackInfo@ ai)
		{
			if (pk::has_skill(ai.members[0], Ư��_����))
				return true;
			if (ai.members[1] != null and pk::has_skill(ai.members[1], Ư��_����))
				return true;
			if (ai.members[2] != null and pk::has_skill(ai.members[2], Ư��_����))
				return true;
			return false;
		}


		int GetFood(pk::building@ building)
		{
			pk::city@ c = pk::building_to_city(building);
			if(c!=null)
				return c.food;
			pk::gate@ g = pk::building_to_gate(building);
			if (g != null)
				return g.food;
			pk::port@ p = pk::building_to_port(building);
			if (p != null)
				return p.food;
			return 0;
		}
		int GetTroops(pk::building@ building)
		{
			pk::city@ c = pk::building_to_city(building);
			if (c != null)
				return c.troops;
			pk::gate@ g = pk::building_to_gate(building);
			if (g != null)
				return g.troops;
			pk::port@ p = pk::building_to_port(building);
			if (p != null)
				return p.troops;
			return 0;
		}
		int GetGold(pk::force@ force)
		{
			int gold = 0;
			pk::list<pk::building@> blist = pk::get_building_list();
			for (int i = 0; i < blist.count; i++)
			{
				pk::building@ b = blist[i];
				if (b.get_force_id() != force.get_id())
					continue;

				pk::city@ city = pk::building_to_city(b);
				if (city != null)
				{
					gold += city.gold;
				}
				pk::gate@ gate = pk::building_to_gate(b);
				if (gate != null)
				{
					gold += gate.gold;
				}
				pk::port@ port = pk::building_to_port(b);
				if (port != null)
				{
					gold += port.gold;
				}
			}
			return gold;
		}

		array<AttackInfo> Attack1Neighbor(pk::building@ attacker, pk::city@ target)
		{
			return Attack(attacker, target, AI_����_����1_�����ϼ�);
		}
		array<AttackInfo> Attack2Neighbor(pk::building@ attacker, pk::city@ target)
		{
			return Attack(attacker, target, AI_����_����2_�����ϼ�);
		}
		array<AttackInfo> Attack(pk::building@ attacker, pk::city@ target, int foodDay)
		{
			//���̵� �������� �ϸ�, Ȥ�� ���ų�
			pk::list<pk::person@> persons = pk::get_idle_person_list(attacker);
			if (persons.count == 0)
				return array<AttackInfo>();


			//����޼���
			persons.sort(function(a, b) {
				if (a.mibun == �ź�_����)
					return true;
				if (b.mibun == �ź�_����)
					return false;
				if (a.rank != b.rank)
					return a.rank < b.rank;
				if (a.max_stat[����ɷ�_���] != b.max_stat[����ɷ�_���])
					return a.max_stat[����ɷ�_���] > b.max_stat[����ɷ�_���];
				return a.max_stat[����ɷ�_����] >= b.max_stat[����ɷ�_����];
			});

			int minFood = AI_����_��_�ּҺ���;
			if (attacker.get_type_id() == 7 || attacker.get_type_id() == 8)
				minFood = AI_����_��_�ּҺ���_����_�ױ�;

			int minTroops = AI_����_��_�ּҺ���;
			if (attacker.get_type_id() == 7 || attacker.get_type_id() == 8)
				minTroops = AI_����_��_�ּҺ���_����_�ױ�;

			//���弱��
			array<AttackInfo> infos;
			int foods = GetFood(attacker);
			int troops = GetTroops(attacker);
			do
			{
				AttackInfo ai;

				int troop = pk::get_command(persons[0]);
				int food = troop / 100.0 * foodDay;
				if (food > foods or foods - food < minFood)
					break;
				if (troop > troops or troops - troop < minTroops)
					break;

				//pk::printf("tr {}/{}, food {}/{}\n",troop,troops,food,foods);

				troops -= troop;
				foods -= food;
				@ai.members[0] = persons[0];
				ai.troops = troop;
				ai.food = food;
				persons.remove_at(0);
				infos.insertLast(ai);

			} while (persons.count > 0);

			//�ι�° ���弱��,����° ���弱��
			//����Ư�Ⱑ ������ �ϴ� ��Ư�⺸�� �켱�Ѵ�.
			if (persons.count >= 2)
				persons.sort(function(a, b) {

				bool aSkill = false;
				for (int i = 0; i < Ư��_�û�; i++)
				{
					if (pk::has_skill(a, i))
					{
						aSkill = true;
						break;
					}
				}
				bool bSkill = false;
				for (int i = 0; i < Ư��_�û�; i++)
				{
					if (pk::has_skill(b, i))
					{
						bSkill = true;
						break;
					}
				}

				if (aSkill != bSkill)
					return aSkill ? true : false;
				if (a.stat[����ɷ�_����] != b.stat[����ɷ�_����])
					return a.stat[����ɷ�_����] >= b.stat[����ɷ�_����];
				return a.stat[����ɷ�_���] >= b.stat[����ɷ�_���];

			});

			int index = 0;
			while (persons.count > 0 and index < infos.length)
			{
				AttackInfo@ ai = infos[index++];
				@ai.members[1] = persons[0];
				persons.remove_at(0);
			}

			index = 0;
			while (persons.count > 0 and index < infos.length)
			{
				AttackInfo@ ai = infos[index++];
				@ai.members[2] = persons[0];
				persons.remove_at(0);
			}

			return infos;
		}

		pk::unit@ CreateUnit(AttackInfo ai,pk::point pt)
		{


			//ai.food = 20000;



			//pk::march_cmd_info mi;
			//@mi.base = pk::get_building(ai.members[0].service);
			//mi.type = �δ�����_����;
			//mi.gold = 0;
			//mi.food = ai.food;
			//mi.troops = ai.troops;
			//for(int i=0;i<12;i++)
			//{
			//	mi.weapon_amount[i] = 0;
			//}
			//mi.weapon_id[0] = ai.����;
			int mount = ai.troops;
			//ai.���� = ����_â;
			//switch(ai.����)
			//{
			//	case ����_��:
			//	case ����_â:
			//	case ����_��:
			//	case ����_��:
			//	case ����_����:
			//		mount =	ai.troops ;break;
			//	case ����_����:
			//	case ����_����:
			//	case ����_����:
			//	case ����_���:
			//		mount = 1;
			//}

			//mi.weapon_amount[0] = mount;
			//
			//mi.member[0] = ai.members[0].get_id();
			//if(ai.members[1]!=null)
			//	mi.member[1] =	ai.members[1].get_id();
			//else
			//	mi.member[1] = -1;
			//if(ai.members[2]!=null)
			//	mi.member[2] =	ai.members[2].get_id();
			//else
			//	mi.member[2] = -1;
			//
			//pk::printf("before command {} {}\n",ai.����,mount);
			//int uid = pk::command(mi);
			//pk::printf("after command {} {}\n",ai.����,mount);
			//return pk::get_unit(uid);

			int ���� = ����_�ְ�;
			if(ai.b����)
				���� = ����_����;
			else if(ai.b����)
				���� = ����_����;


			return pk::create_unit(pk::get_building(ai.members[0].service), ai.members[0], ai.members[1], ai.members[2],mount,ai.����,����,0,ai.food, pt);
			//return pk::create_unit(pk::get_building(ai.members[0].service), ai.members[0], null, null,mount,ai.����,-1,0,ai.food, pk::get_building(ai.members[0].service).get_pos());
			//return pk::create_unit(pk::get_building(ai.members[0].service), ai.members[0], null, null,mount,ai.����,����,0,ai.food, pt);
		}

		void March(pk::city@ city,pk::city@ target, array<AttackInfo> infos)
		{
			array<AttackInfo> infos2;
			for (int i = 0; i < infos.length; i++)
			{
				infos2.insertLast(infos[i]);
			}

			pk::force@ force = pk::get_force(city.get_force_id());
			int dist = 1;
			while (infos2.length > 0)
			{
				for (int i = 0; i < ����_��; i++)
				{
					pk::point pt = pk::get_neighbor_pos(city.get_pos(), i, dist);

					if (pk::get_hex_object(pt) == null)
					{
						AttackInfo@ ai = infos2[0];
						city.food -= ai.food;
						city.troops -= ai.troops;
						makeMax����(ai,city, target);
						if (!AI_����_����_���_���� and ai.���� != ����_��)
						{
							if (ai.���� != ����_���� and ai.���� != ����_���� and ai.���� != ����_��� and ai.���� != ����_���� and ai.���� != ����_���� and ai.���� != ����_����)
								city.weapon_amount[ai.����] = city.weapon_amount[ai.����]-ai.troops;
							else
								city.weapon_amount[ai.����]=city.weapon_amount[ai.����]-1;
						}
						if (!AI_����_����_���_���� and Is��������(city) and Is��������(target))
						{
							if (pk::has_tech(force, �ⱳ_��������) and city.weapon_amount[����_����] >= 1)
								city.weapon_amount[����_����]=city.weapon_amount[����_����]-1;
							else if(city.weapon_amount[����_����] >= 1)
								city.weapon_amount[����_����]=city.weapon_amount[����_����]-1;
						}



						pk::unit@ unit=CreateUnit(infos2[0],pt);
						pk::set_order(unit, �δ��ӹ�_����, target.get_pos());
						infos2.removeAt(0);

						array<pk::point> tmp = {pt};
						pk::set_pos(unit, pt);
						if (infos2.length == 0)
							break;
					}

				}
				dist++;
			}
		}

		void Attack(pk::force@ attacker, pk::force@ target)
		{
			//Ÿ�ٵ����� ���ݵ��ÿ� ������ ���� ����, ���� ������ ����,1�������ô� ����,  2���� ���ô� ���� ����. 3�����̻� ���ú��ʹ� �ϰ͵� ����

			pk::city@ targetCity = GetTargetCity(attacker, target);

			pk::list<pk::building@> buildings = pk::get_building_list();

			array<AttackInfo> infos;

			int totalTroops = 0;
			for (int i = 0; i < buildings.count; i++)
			{
				pk::building@ b = buildings[i];
				pk::city@ c = pk::building_to_city(b);
				if(c==null)
					continue;
				if(c.get_force_id() != attacker.get_id())
					continue;

				pk::building@ b2 = pk::city_to_building(targetCity);
				int dist = pk::get_building_distance(b.get_id(), b2.get_id());
				pk::printf("dist {},{}->{}\n",dist, pk::decode(pk::get_name(b)),pk::decode(pk::get_name(b2)));
				if (dist == 1)
				{
					array<AttackInfo> infos2 = Attack1Neighbor(b, targetCity);
					for (int j = 0; j < infos2.length; j++)
					{
						infos.insertLast(infos2[j]);
					}

					March(c, targetCity,infos2);
				}
				else if (dist == 2 || dist == 3)
				{
					//array<AttackInfo> infos2 = Attack2Neighbor(b, targetCity);
					array<AttackInfo> infos2 = Attack(b, targetCity, dist == 2 ? AI_����_����2_�����ϼ� : AI_����_����3_�����ϼ�);
					for (int j = 0; j < infos2.length; j++)
					{
						infos.insertLast(infos2[j]);
					}

					March(c,targetCity, infos2);
				}
			}

		}
		pk::person@ _scene_person = null;
		pk::force@ _scene_attacker = null;
		pk::force@ _scene_target = null;
		pk::city@ _scene_city = null;
		bool _scene_result = false;
		void Scene�ܱ�()
		{
			pk::person@ kunshu = pk::get_person(_scene_attacker.kunshu);
			pk::person@ gunshi = pk::get_person(_scene_attacker.gunshi);
			pk::diplomacy(_scene_person,kunshu, gunshi,pk::diplomacy_t(�ܱ�));
		}
		void �ܱ�()
		{
			pk::person@ kunshu = pk::get_person(_scene_attacker.kunshu);
			pk::person@ kunshu2 = pk::get_person(_scene_target.kunshu);

			pk::title@ title = pk::get_title(_scene_attacker.title - 1);

			pk::message_box(pk::encode(pk::format("\x1b[2x{}\x1b[0x�� \x1b[2x{}\x1b[0x�� �Ӹ��ϳ��. ���� \x1b[2x{}\x1b[0x�� ����϶�",pk::decode(pk::get_name(kunshu)),pk::decode(title.name),pk::decode(pk::get_name(kunshu2)))), _scene_person);

			if (pk::is_neighbor_force(_scene_attacker, _scene_target))
			{
				pk::message_box(pk::encode("�˰ڽ��ϴ�."), kunshu);
				_scene_result = true;
			}
			else
			{
				pk::message_box(pk::encode("������ ������ �ʾ� ��Ƽ�"),kunshu);
				_scene_result = false;
			}
		}


		void Scene�ܱ�AI()
		{
			pk::person@ kunshu = pk::get_person(_scene_attacker.kunshu);
			pk::person@ gunshi = pk::get_person(_scene_attacker.gunshi);
			pk::diplomacy(_scene_person, kunshu, gunshi, pk::diplomacy_t(�ܱ�AI));
		}
		void �ܱ�AI()
		{
			pk::person@ kunshu = pk::get_person(_scene_attacker.kunshu);
			pk::person@ kunshu2 = pk::get_person(_scene_target.kunshu);

			pk::title@ title = pk::get_title(_scene_attacker.title - 1);


			string str = pk::format("\x1b[2x{}\x1b[0x�� \x1b[2x{}\x1b[0x�� �Ӹ��ϳ��. ���� \x1b[2x{}\x1b[0x�� ���� \x1b[2x{}\x1b[0x�� \x1b[2x{}\x1b[0x�������� ����϶�\n", 
				pk::decode(pk::get_name(kunshu)), pk::decode(title.name), pk::decode(pk::get_name(kunshu2)),pk::decode(pk::get_name(_scene_city)), ����_�������ݸ��_�Ⱓ / 30);
			if (pk::yes_no(pk::encode(str)))
			{
				pk::message_box(pk::encode("�˰ڽ��ϴ�."), kunshu);
				_scene_result = true;
			}
			else 
			{
				pk::message_box(pk::encode("�����ϰڽ��ϴ�."), kunshu);
				_scene_result = false;
			}
		}


		bool TitleAttackCommandHandler()
		{
			pk::list<pk::force@> forceAttack = pk::force_selector(pk::encode("���¼���"), pk::encode("������ �ο��� ������ �����մϴ�."),pk::get_force_list(), 1, 1);
			if (forceAttack.count == 0)
				return true;
			if (forceAttack[0].kokugou == ��ȣ_Ȳ��)
			{
				pk::message_box(pk::encode("Ȳ�� ������ ������ �ο��� �� �����ϴ�."));
				return true;
			}
			pk::list<pk::force@> forceTarget= pk::force_selector(pk::encode("���¼���"), pk::encode("����� ������ �����մϴ�."),pk::get_force_list(), 1, 1);
			if (forceTarget.count == 0)
				return true;
			if(forceAttack[0].get_id() == forceTarget[0].get_id())
			{
				pk::message_box(pk::encode("���� �����Դϴ�."));
				return true;
			}

			pk::list<pk::person@> persons= pk::person_selector(pk::encode("���弱��"), pk::encode("�ܱ��� ������ ������ �����մϴ�."), pk::get_idle_person_list(_building), 1, 1);
			if (persons.count == 0)
				return true;

			pk::string str = pk::format("\x1b[2x{}\x1b[0x ���� \x1b[2x{}\x1b[0x�� ����϶�� ����մϱ�?", pk::decode(pk::get_name(forceAttack[0])), pk::decode(pk::get_name(forceTarget[0])));
			if (!pk::yes_no(pk::encode(str)))
				return true;

			persons[0].action_done = true;
			@_scene_person = persons[0];
			@_scene_attacker = forceAttack[0];
			@_scene_target = forceTarget[0];

			_district.ap = pk::max(_district.ap - �ൿ��, 0);

			pk::scene(pk::scene_t(Scene�ܱ�));
			if (_scene_result)
			{
				int newTitle = forceAttack[0].title - 1;

				//����
				forceAttack[0].title = newTitle;
				//�ܱ� �����̸� ���� ����, ģ�е� 0���� ����

				breakAlly(forceAttack[0], forceTarget[0]);


				Attack(forceAttack[0], forceTarget[0]);

				string str22 = pk::format("\x1b[2x{}\x1b[0x �� \x1b[2x{}\x1b[0x�� ������ �ı�Ǿ����ϴ�.", pk::decode(pk::get_name(pk::get_person(forceAttack[0].kunshu))), pk::decode(pk::get_name(pk::get_person(forceTarget[0].kunshu))));
				pk::message_box(pk::encode(str));
				pk::play_se(10);
				return true;
			}
			else
			{
				pk::play_se(13);
				return true;
			}

		}


		pk::force@ _force;
		pk::building@ _building;
		pk::city@ _city;
		pk::district@ _district;
		void BuyTitleInit(pk::building@ building)
		{
			@_force = pk::get_force(building.get_force_id());
			@_building = building;
			@_city = pk::building_to_city(building);
			@_district = pk::get_district(building.get_district_id());
		}
		bool IsBuyTitleEnabled()
		{
			return _district.ap >= �ൿ�� and pk::is_protecting_the_emperor(_force);
		}
		string GetBuyTitleText()
		{
			return pk::encode("��������");
		}
		string GetBuyTitleDesc()
		{
			if(!pk::is_protecting_the_emperor(_force))
				return pk::encode("Ȳ���� �˸��ؾ� �մϴ�.");
			else if (_district.ap < �ൿ��)
				return pk::encode(pk::format("�ൿ���� �����մϴ�.(�ൿ��{})", �ൿ��));
			else
				return pk::encode(pk::format("������ �����մϴ�.(�ൿ��{},Ȳ���˸�)", �ൿ��));
		}

		string GetTitleName(int i)
		{
			string strTitle;
			switch (i)
			{
			case ����_Ȳ��:strTitle = "Ȳ��"; break;
			case ����_��:strTitle = "��"; break;
			case ����_��:strTitle = "��"; break;
			case ����_��縶:strTitle = "��縶"; break;
			case ����_���屺:strTitle = "���屺"; break;
			case ����_�����߶���:strTitle = "�����߶���"; break;
			case ����_�츲�߶���:strTitle = "�츲�߶���"; break;
			case ����_�ָ�:strTitle = "�ָ�"; break;
			case ����_���ڻ�:strTitle = "���ڻ�"; break;
			default:
				break;
			}

			return strTitle;
		}

		

		bool BuyTitle(pk::force@ force, int title)
		{
			int titleGold = �������[title];

			int gold = GetGold(force);
			if (gold < titleGold)
			{
				pk::message_box(pk::encode("���� �����մϴ�."));
				return false;
			}

			pk::list<pk::building@> blist = pk::get_building_list();
			int gold2 = 0;
			for (int i = 0; i < blist.count; i++)
			{
				pk::building@ b = blist[i];
				if(force.get_id() != b.get_force_id())
					continue;

				pk::city@ c = pk::building_to_city(b);
				if (c != null)
				{
					int m0 = titleGold * float(c.gold) / float(gold);
					c.gold -= m0;
					gold2 += m0;
				}
				pk::gate@ g = pk::building_to_gate(b);
				if (g != null)
				{
					int m0 = titleGold * float(g.gold) / float(gold);
					g.gold -= m0;
					gold2 += m0;
				}
				pk::port@ p = pk::building_to_port(b);
				if (p != null)
				{
					int m0 = titleGold * float(p.gold) / float(gold);
					p.gold -= m0;
					gold2 += m0;
				}
			}

			//pk::printf("{}/{} ,{}/{}, {}/{}\n",gold2,item.gold,food2,item.food,troops2,item.troops);
			return true;
		}

		bool BuyTitleHandler()
		{

			while(true)
			{
				int si = 0;
				int title_index = -1;
				int gold = GetGold(_force);
				while (true)
				{
					array<string> itemArr;
					int count = pk::min(�������.length, si + 4);
					if (si == 0)
						itemArr.insertLast(pk::encode("����"));
					else
						itemArr.insertLast(pk::encode("�ڷ�"));

					for (int i = si; i < count; i++)
					{
						string str;
						string strTitle = GetTitleName(i);
						str = pk::format("{},��{}", strTitle, �������[i]);
						itemArr.insertLast(pk::encode(str));
					}

					if (si + 4 >= �������.length)
						itemArr.insertLast(pk::encode("����"));
					else
						itemArr.insertLast(pk::encode("����"));


					int choose2 = pk::choose(pk::encode(pk::format("������ �������ֽʽÿ�. ���� ��{}",gold)), itemArr);
					if (choose2 == itemArr.length - 1)
					{
						si = si + 4;
						if (si >= �������.length)
							return true;
					}
					else if (choose2 == 0)
					{
						si = si - 4;
						if (si < 0)
							return true;
					}
					else
					{
						title_index = si + choose2 - 1;
						break;
					}
				}

				if (title_index == -1)
					continue;
				if (!Ȳ��_����_���� and title_index == ����_Ȳ��)
				{
					pk::message_box(pk::encode("Ȳ���� ������ �� �����ϴ�."));
					continue;
				}
				if (!��_����_���� and title_index == ����_��)
				{
					pk::message_box(pk::encode("���� ������ �� �����ϴ�."));
					continue;
				}

				if (title_index >= _force.title)
				{
					pk::message_box(pk::encode("�̹� ȹ���� �����Դϴ�."));
					continue;
				}
				if (_force.title - title_index > 1)
				{
					pk::message_box(pk::encode(pk::format("{} �� �����մϴ�.",GetTitleName(_force.title - 1))));
					continue;
				}

				string str = pk::format("�� {} -> {}, �����մϱ�?", gold, gold - �������[title_index]);
				if(!pk::yes_no(pk::encode(str)))
					continue;

				if (BuyTitle(_force, title_index))
				{
					_force.title = title_index;
					pk::play_se(10);
				}
				
			}


			return true;
		}
	}
	Main main;
}

