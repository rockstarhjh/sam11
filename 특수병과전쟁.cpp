/*
@������: ũ���Ƚ�
@Update: 2023.9.4,���ʹ���
@Update: 2023.9.5,���ν� Ư������ ǥ�� ������ �ʵ��� ����,���� Ư������ ��ġ�� �ʵ��� ����,Ư��������ġ ������ó��
@Update: 2023.9.6,�⺴��������߰�, �����ϱ����߰�, ����ġȹ�� �߰�, �����߰�
@Update: 2023.9.7,���̺�,�ε� ���׼���, AI�ߺ� �������� ���׼���
*/
namespace Ư������
{
	///////////���� �ɼ� ����//////////////////////////////////////////////////////////////////////////
	const bool AI����_��� = false; //�ڲ� �ٿ�ɰ�쿡 ���� �غ�����.AI��������� �� �Ҿ��մϴ�.
	
	//������ ���ĵ��� �⺴�����ܿ��� ���� �ʴ� ����Դϴ�.
	//�⸶å��� ������������ȭ�� ����ø� ����ϴ� ���, ���ĵ��� ���� �⺴���θ� ���ɴϴ�.
	//�⺴���θ� �����µ�, �ٸ������� �ָ� ���� �Ǵ� ��������. �׷��� ���� ���� false�� ����ϼ���.
	const bool AIƯ����������_Ư����� = true;
	const int ����_��� = 25;
	const int Ư������_����_���� = 3;
	const int Ư������_�߰�_���ݷ� = 15;
	const int Ư������_�߰�_���� = 15;
	const int �縶��_����_ȹ��_Ȯ�� = 1;
	const int ����_�ϱ���_Ȯ�� = 5;
	
	const int �������н�_�Ϲݰ���_Ȯ�� = 30;
	const int �������н�_�Ϲݰ���_��������_Ȯ�� = 30;
	const int �������н�_�ݰݸ�_Ȯ�� = 40;

	const int ����_�λ�_Ȯ�� = 30;
	const int ��ȭ��_ȭ��_Ȯ�� = 60;
	const int ����_ȥ��_Ȯ�� = 50;
	const int ��ǳ��_Ȯ�� = 70;
	const int �����_��������_Ȯ�� = 80;
	const int û�ֺ�_�߰�����_Ȯ�� = 30;
	const int ��ô_ȭ��_Ȯ�� = 60;
	const int ȭ����_ȭ��_Ȯ�� = 60;
	const int ����_ȥ��_Ȯ�� = 70;
	const int ����_ȥ��_Ȯ�� = 70;

	const int ����_����_������ = 10; //1�Ÿ��� 10%
	const int ����_����_�ִ�����Ÿ� = 5;//50% ����
	const int ����_����_������ = 5; //1�Ÿ��� 5%

	const int �ع���_�������_�߰� = 50;
	const int ���_�ݰ�_�߰� = 50;

	const int ��������_���_����� = 20;
	const int ��������_�̵���_�߰� = 3;

	const int AI����_����Ȯ�� = 30;
	const int AI����_����Ȯ�� = 30;


	const bool ��ü_����_���_�׽�Ʈ = false;//����Ȯ�ο����� �ʿ��� ��� ����Ͻñ� �ٶ��ϴ�.
	const bool Ư������_������_����_�׽�Ʈ = false;
	const bool �ܼ�_�α�_ǥ�� = true; //���� ������ ������ �� �ְ� �ѵμ���.AI������� �αװ� �ܼ�â�� ǥ�õǴµ�, ���� ǥ�õ��� �ʽ��ϴ�.
	const bool �ܼ�_�α�_ǥ��_���̺�_�ε� = true; //���� ������ ������ �� �ְ� �ѵμ���.AI������� �αװ� �ܼ�â�� ǥ�õǴµ�, ���� ǥ�õ��� �ʽ��ϴ�.

	array<SpecialForceItem> Ư����������Ʈ =
	{
		//Ư������ ���� �ٲٽø� �ȵ˴ϴ�.
		//Ư���������̵�,�����۸���Ʈ,���帮��Ʈ,����,���ʼ�����
		SpecialForceItem(Ư������_�⺴_�鸶����,{}, {����_������}, ����_����,�������),
		SpecialForceItem(Ư������_�⺴_����ö��,{}, {����_����,����_����}, ����_����,�������),
		SpecialForceItem(Ư������_�⺴_ȣǥ��,{}, {����_����,����_����,����_����}, ����_����,�������),
		SpecialForceItem(Ư������_�⺴_������,{}, {}, ����_����,����_��Ź),

		SpecialForceItem(Ư������_â��_û�ֺ�,{����_��õ��}, {}, ����_����,�������),
		SpecialForceItem(Ư������_â��_���̺�,{����_�ڿ��ϴ��}, {}, ����_����,�������),
		SpecialForceItem(Ư������_â��_��ػ�,{}, {����_����}, ����_���ڻ�,�������),
		SpecialForceItem(Ư������_â��_�����,{}, {}, ����_�ָ�,�������),

		SpecialForceItem(Ư������_�غ�_�ܾ纴,{}, {}, ����_����,����_����),
		SpecialForceItem(Ư������_�غ�_�ع���,{}, {}, ����_����,����_�Ѵ�),
		//SpecialForceItem(Ư������_�غ�_���,{}, {}, ����_����,����_���),
		SpecialForceItem(Ư������_�غ�_���,{}, {}, ����_����,����_�õ���),
		SpecialForceItem(Ư������_�غ�_������,{}, {}, ����_����,����_���),

		SpecialForceItem(Ư������_�뺴_���뺴,{}, {}, ����_����,����_����),
		SpecialForceItem(Ư������_�뺴_�����,{}, {}, ����_����,����_����),
		SpecialForceItem(Ư������_�뺴_���뺴,{����_��������Ȱ}, {}, ����_����,�������),
		SpecialForceItem(Ư������_�뺴_���踸��,{}, {}, ����_���ڻ�,�������),
		SpecialForceItem(Ư������_�뺴_��������,{����_�̱���Ȱ}, {����_Ȳ��}, ����_�ָ�,�������)
	};

	///////�������� ������///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	const int ������� = -1;
	int _elapsedDay = 0;
	array<ForceInfo> ���¸���Ʈ;


	const int ����_����_�������� = 0;
	const int ����_����_Ȱ���� = 1;
	const int ����_����_���� = 2;
	const int ����_����_����÷ = 3;
	const int ����_����_�̴�÷ = 4;
	const int ����_����_���� = 5;
	const int ����_����_Ⱦġ = 6;
	const int ����_����_��ǳ = 7;
	const int ����_����_ȭ�� = 8;
	const int ����_����_���� = 9;
	const int ����_����_���� = 10;
	const int ����_����_���� = 11;
	const int ����_����_���� = 12;
	const int ����_����_���� = 13;
	const int ����_����_ȭ��_���� = 14;
	const int ����_����_�ļ�_���� = 15;
	const int ����_����_���_���� = 16;
	const int ����_����_����_���� = 17;
	const int ����_����_��������_�Լ� = 18;
	const int ����_����_Ȱ����_�Լ� = 19;
	const int ����_����_ȭ��_�Լ� = 20;
	const int ����_����_����_�Լ� = 21;
	const int ����_����_�ݵ�_�Լ� = 22;
	const int ����_����_����÷���� = 23;
	const int ����_����_�������ݴ��� = 24;
	const int ����_����_�������ݴ��� = 25;
	const int ����_����_Ȱ���ݴ��� = 26;
	const int ����_����_����_�̴�÷���� = 27;
	const int ����_����_����_�������� = 28;
	const int ����_����_����_�������_1Ÿ�� = 29;
	const int ����_����_����_�������� = 30;
	const int ����_����_����_���Ĵ��� = 31;
	const int ����_����_����_�������� = 32;

	const int Ư������_�⺴_�鸶���� = 0;
	const int Ư������_�⺴_����ö�� = 1;
	const int Ư������_�⺴_ȣǥ�� = 2;
	const int Ư������_�⺴_������ = 3;

	const int Ư������_â��_û�ֺ� = 4;
	const int Ư������_â��_���̺� = 5;
	const int Ư������_â��_��ػ� = 6;
	const int Ư������_â��_����� = 7;

	const int Ư������_�غ�_�ܾ纴 = 8;
	const int Ư������_�غ�_�ع��� = 9;
	const int Ư������_�غ�_��� = 10;
	const int Ư������_�غ�_������ = 11;

	const int Ư������_�뺴_���뺴 = 12;
	const int Ư������_�뺴_����� = 13;
	const int Ư������_�뺴_���뺴 = 14;
	const int Ư������_�뺴_���踸�� = 15;
	const int Ư������_�뺴_�������� = 16;


	const bool ũ��Ƽ��_���Ÿ� = true;
	const bool ũ��Ƽ��_���� = false;

	const int KEY = pk::hash("Ư����������");

	class ForceInfo
	{
		array<SpecialForceApply@> applies;
		pk::force@ force;
		int numPersons = 0;
		int numApply = 0;

		void remove(SpecialForceItem@ it)
		{
			int index = -1;
			for (int i = 0; i < applies.length; i++)
			{
				SpecialForceApply@ sa = applies[i];
				if(sa.item.id != it.id)
					continue;
				index = i;
				break;
			}
			if(index!=-1)
				applies.removeAt(index);
		}
		void add(SpecialForceItem@ it)
		{
			SpecialForceApply sa;
			@sa.item = it;
			@sa.force = force;
			applies.insertLast(sa);
		}
	};

	class SpecialForceApply
	{
		SpecialForceItem@ item;
		pk::force@ force;
		pk::list<pk::person@> persons;
	};

	class SpecialForceItem
	{
		pk::list<pk::item@> items;
		pk::list<pk::person@> persons;
		pk::title@ title;
		int id;
		string name;
		int ����;
		pk::person@ owner = null;
		pk::person@ firstOwner = null;
		pk::point ownerPos;

		array<ForceInfo@> currentForces;

		SpecialForceItem(){}
		SpecialForceItem(int id0, array<int> items0, array<int> persons0, int titleID,int owner0)
		{
			id = id0;
			for (int i = 0; i < items0.length; i++)
			{
				pk::item@ it = pk::get_item(items0[i]);
				if(it==null)
					continue;
				items.add(it);
			}
			for (int i = 0; i < persons0.length; i++)
			{
				pk::person@ it = pk::get_person(persons0[i]);
				if (it == null)
					continue;
				persons.add(it);
			}
			@title = titleID != ����_���� ? pk::get_title(titleID) : null;
			if (items0.length == 0 && persons0.length == 0 && titleID == ����_���� && owner0 != �������)
			{
				@firstOwner = pk::get_person(owner0);
			}

			switch (id0)
			{
			case Ư������_�뺴_���뺴:		name = "���뺴"; ;	���� = ����_�뺴; break;
			case Ư������_�뺴_�����:	name = "�����"; ���� = ����_�뺴; break;
			case Ư������_�뺴_���뺴:		name = "���뺴"; ���� = ����_�뺴; break;
			case Ư������_�뺴_���踸��:	name = "���踸��"; ���� = ����_�뺴;break;
			case Ư������_�뺴_��������:	name = "��������"; ���� = ����_�뺴;break;

			case Ư������_â��_û�ֺ�:		name = "û�ֺ�"; ���� = ����_â��; break;
			case Ư������_â��_���̺�:		name = "���̺�"; ���� = ����_â��; break;
			case Ư������_â��_��ػ�:		name = "��ػ�"; ���� = ����_â��; break;
			case Ư������_â��_�����:	name = "�����"; ���� = ����_â��; break;

			case Ư������_�غ�_�ܾ纴:		name = "�ܾ纴"; ���� = ����_�غ�; break;
			case Ư������_�غ�_�ع���:		name = "�ع���"; ���� = ����_�غ�; break;
			case Ư������_�غ�_���:		name = "���"; ���� = ����_�غ�; break;
			case Ư������_�غ�_������:		name = "������"; ���� = ����_�غ�; break;

			case Ư������_�⺴_�鸶����:		name = "�鸶����"; ���� = ����_�⺴; break;
			case Ư������_�⺴_����ö��:		name = "����ö��"; ���� = ����_�⺴; break;
			case Ư������_�⺴_ȣǥ��:			name = "ȣǥ��"; ���� = ����_�⺴; break;
			case Ư������_�⺴_������:		name = "������"; ���� = ����_�⺴; break;

			default:
				break;
			}
		}
	};



	class Main
	{
		pk::func209_t@ prev_callback_209�δ����;
		pk::func201_t@ prev_callback_201;
		pk::func202_t@ prev_callback_202��������;
		pk::func200_t@ prev_callback_200��������;
		pk::func210_t@ prev_callback_210;
		pk::func221_t@ prev_callback_221;
		pk::func222_t@ prev_callback_222;
		pk::func163_t@ prev_callback_163�δ�ɷ�ġ;
		pk::func203_t@ prev_callback_203�⺴�������;

		
		Main()
		{
			@prev_callback_210 = cast<pk::func210_t@>(pk::get_func(210));
			@prev_callback_221 = cast<pk::func221_t@>(pk::get_func(221));
			@prev_callback_222 = cast<pk::func222_t@>(pk::get_func(222));
			@prev_callback_203�⺴������� = cast<pk::func203_t@>(pk::get_func(203));


			@prev_callback_163�δ�ɷ�ġ = cast<pk::func163_t@>(pk::get_func(163));
			pk::reset_func(163);
			pk::set_func(163, pk::func163_t(callback163));

			@prev_callback_209�δ���� = cast<pk::func209_t@>(pk::get_func(209));
			pk::reset_func(209);
			pk::set_func(209, pk::func209_t(callback209));


			@prev_callback_200�������� = cast<pk::func200_t@>(pk::get_func(200));
			pk::reset_func(200);
			pk::set_func(200, pk::func200_t(callback200));

			@prev_callback_202�������� = cast<pk::func202_t@>(pk::get_func(202));
			pk::reset_func(202);
			pk::set_func(202, pk::func202_t(callback202));

			@prev_callback_201 = cast<pk::func201_t@>(pk::get_func(201));
			pk::reset_func(201);
			pk::set_func(201, pk::func201_t(callback201));


			pk::bind(102, pk::trigger102_t(onInit));
			pk::bind(105, pk::trigger105_t(saveData));
			pk::bind(107, pk::trigger107_t(onNewDay));
			pk::bind(174, pk::trigger174_t(�δ��ൿ�Ϸ�));
			pk::bind(173, pk::trigger173_t(�δ����ġ));
			pk::bind(120, pk::trigger120_t(UpdatePerFrame));
			pk::bind(111, pk::trigger111_t(onTurn));


			int pos = 4;
			int pos2= 3;

			pk::menu_item item����;
			item����.menu = 1;
			item����.pos = pos;
			item����.init = pk::unit_menu_item_init_t(init);
			item����.get_text = pk::menu_item_get_text_t(Get����Text);
			item����.get_desc = pk::menu_item_get_desc_t(Get����Desc);
			item����.is_visible = pk::menu_item_is_visible_t(IsVisible����);
			item����.get_targets = pk::unit_menu_item_get_targets_t(GetTargets����);
			item����.get_chance = pk::unit_menu_item_get_chance_t(GetChance����);
			item����.handler = pk::unit_menu_item_handler_t(����Handler);
			pk::add_menu_item(item����);
			

			pk::menu_item item��ȭ��;
			item��ȭ��.menu = 1;
			item��ȭ��.pos = pos;
			item��ȭ��.init = pk::unit_menu_item_init_t(init);
			item��ȭ��.get_text = pk::menu_item_get_text_t(Get��ȭ��Text);
			item��ȭ��.get_desc = pk::menu_item_get_desc_t(Get��ȭ��Desc);
			item��ȭ��.is_visible = pk::menu_item_is_visible_t(IsVisible��ȭ��);
			item��ȭ��.get_targets = pk::unit_menu_item_get_targets_t(GetTargets��ȭ��);
			item��ȭ��.get_chance = pk::unit_menu_item_get_chance_t(GetChance��ȭ��);
			item��ȭ��.handler = pk::unit_menu_item_handler_t(��ȭ��Handler);
			pk::add_menu_item(item��ȭ��);

			pk::menu_item item����;
			item����.menu = 1;
			item����.pos = pos;
			item����.init = pk::unit_menu_item_init_t(init);
			item����.get_text = pk::menu_item_get_text_t(Get����Text);
			item����.get_desc = pk::menu_item_get_desc_t(Get����Desc);
			item����.is_visible = pk::menu_item_is_visible_t(IsVisible����);
			item����.get_targets = pk::unit_menu_item_get_targets_t(GetTargets����);
			item����.get_chance = pk::unit_menu_item_get_chance_t(GetChance����);
			item����.handler = pk::unit_menu_item_handler_t(����Handler);
			pk::add_menu_item(item����);

			pk::menu_item item��ǳ��;
			item��ǳ��.menu = 1;
			item��ǳ��.pos = pos2;
			item��ǳ��.init = pk::unit_menu_item_init_t(init);
			item��ǳ��.get_text = pk::menu_item_get_text_t(Get��ǳ��Text);
			item��ǳ��.get_desc = pk::menu_item_get_desc_t(Get��ǳ��Desc);
			item��ǳ��.is_visible = pk::menu_item_is_visible_t(IsVisible��ǳ��);
			item��ǳ��.get_targets = pk::unit_menu_item_get_targets_t(GetTargets��ǳ��);
			item��ǳ��.get_chance = pk::unit_menu_item_get_chance_t(GetChance��ǳ��);
			item��ǳ��.handler = pk::unit_menu_item_handler_t(��ǳ��Handler);
			pk::add_menu_item(item��ǳ��);

			pk::menu_item item�س���÷;
			item�س���÷.menu = 1;
			item�س���÷.pos = pos;
			item�س���÷.init = pk::unit_menu_item_init_t(init);
			item�س���÷.get_text = pk::menu_item_get_text_t(Get�س���÷Text);
			item�س���÷.get_desc = pk::menu_item_get_desc_t(Get�س���÷Desc);
			item�س���÷.is_visible = pk::menu_item_is_visible_t(IsVisible�س���÷);
			item�س���÷.get_targets = pk::unit_menu_item_get_targets_t(GetTargets�س���÷);
			item�س���÷.get_chance = pk::unit_menu_item_get_chance_t(GetChance�س���÷);
			item�س���÷.handler = pk::unit_menu_item_handler_t(�س���÷Handler);
			pk::add_menu_item(item�س���÷);

			pk::menu_item item������;
			item������.menu = 1;
			item������.pos = pos;
			item������.init = pk::unit_menu_item_init_t(init);
			item������.get_text = pk::menu_item_get_text_t(Get������Text);
			item������.get_desc = pk::menu_item_get_desc_t(Get������Desc);
			item������.is_visible = pk::menu_item_is_visible_t(IsVisible������);
			item������.get_targets = pk::unit_menu_item_get_targets_t(GetTargets������);
			item������.get_chance = pk::unit_menu_item_get_chance_t(GetChance������);
			item������.handler = pk::unit_menu_item_handler_t(������Handler);
			pk::add_menu_item(item������);

			pk::menu_item itemȭ����;
			itemȭ����.menu = 1;
			itemȭ����.pos = pos2;
			itemȭ����.init = pk::unit_menu_item_init_t(init);
			itemȭ����.get_text = pk::menu_item_get_text_t(Getȭ����Text);
			itemȭ����.get_desc = pk::menu_item_get_desc_t(Getȭ����Desc);
			itemȭ����.is_visible = pk::menu_item_is_visible_t(IsVisibleȭ����);
			itemȭ����.get_targets = pk::unit_menu_item_get_targets_t(GetTargetsȭ����);
			itemȭ����.get_chance = pk::unit_menu_item_get_chance_t(GetChanceȭ����);
			itemȭ����.handler = pk::unit_menu_item_handler_t(ȭ����Handler);
			pk::add_menu_item(itemȭ����);


			pk::menu_item item��ô;
			item��ô.menu = 1;
			item��ô.pos = pos2;
			item��ô.init = pk::unit_menu_item_init_t(init);
			item��ô.get_text = pk::menu_item_get_text_t(Get��ôText);
			item��ô.get_desc = pk::menu_item_get_desc_t(Get��ôDesc);
			item��ô.is_visible = pk::menu_item_is_visible_t(IsVisible��ô);
			item��ô.get_targets = pk::unit_menu_item_get_targets_t(GetTargets��ô);
			item��ô.get_chance = pk::unit_menu_item_get_chance_t(GetChance��ô);
			item��ô.handler = pk::unit_menu_item_handler_t(��ôHandler);
			pk::add_menu_item(item��ô);

			pk::menu_item item����;
			item����.menu = 1;
			item����.pos = pos;
			item����.init = pk::unit_menu_item_init_t(init);
			item����.get_text = pk::menu_item_get_text_t(Get����Text);
			item����.get_desc = pk::menu_item_get_desc_t(Get����Desc);
			item����.is_visible = pk::menu_item_is_visible_t(IsVisible����);
			item����.get_targets = pk::unit_menu_item_get_targets_t(GetTargets����);
			item����.get_chance = pk::unit_menu_item_get_chance_t(GetChance����);
			item����.handler = pk::unit_menu_item_handler_t(����Handler);
			pk::add_menu_item(item����);


			pk::menu_item item����;
			item����.menu = 1;
			item����.pos = pos;
			item����.init = pk::unit_menu_item_init_t(init);
			item����.get_text = pk::menu_item_get_text_t(Get����Text);
			item����.get_desc = pk::menu_item_get_desc_t(Get����Desc);
			item����.is_visible = pk::menu_item_is_visible_t(IsVisible����);
			item����.get_targets = pk::unit_menu_item_get_targets_t(GetTargets����);
			item����.get_chance = pk::unit_menu_item_get_chance_t(GetChance����);
			item����.handler = pk::unit_menu_item_handler_t(����Handler);
			pk::add_menu_item(item����);


			pk::menu_item item����;
			item����.menu = 1;
			item����.pos = pos;
			item����.init = pk::unit_menu_item_init_t(init);
			item����.get_text = pk::menu_item_get_text_t(Get����Text);
			item����.get_desc = pk::menu_item_get_desc_t(Get����Desc);
			item����.is_visible = pk::menu_item_is_visible_t(IsVisible����);
			item����.get_targets = pk::unit_menu_item_get_targets_t(GetTargets����);
			item����.get_chance = pk::unit_menu_item_get_chance_t(GetChance����);
			item����.handler = pk::unit_menu_item_handler_t(����Handler);
			pk::add_menu_item(item����);


			pk::menu_item item�鸶��;
			item�鸶��.menu = 1;
			item�鸶��.pos = pos;
			item�鸶��.init = pk::unit_menu_item_init_t(init);
			item�鸶��.get_text = pk::menu_item_get_text_t(Get�鸶��Text);
			item�鸶��.get_desc = pk::menu_item_get_desc_t(Get�鸶��Desc);
			item�鸶��.is_visible = pk::menu_item_is_visible_t(IsVisible�鸶��);
			item�鸶��.get_targets = pk::unit_menu_item_get_targets_t(GetTargets�鸶��);
			item�鸶��.get_chance = pk::unit_menu_item_get_chance_t(GetChance�鸶��);
			item�鸶��.handler = pk::unit_menu_item_handler_t(�鸶��Handler);
			pk::add_menu_item(item�鸶��);

			pk::menu_item item����;
			item����.menu = 1;
			item����.pos = pos;
			item����.init = pk::unit_menu_item_init_t(init);
			item����.get_text = pk::menu_item_get_text_t(Get����Text);
			item����.get_desc = pk::menu_item_get_desc_t(Get����Desc);
			item����.is_visible = pk::menu_item_is_visible_t(IsVisible����);
			item����.get_targets = pk::unit_menu_item_get_targets_t(GetTargets����);
			item����.get_chance = pk::unit_menu_item_get_chance_t(GetChance����);
			item����.handler = pk::unit_menu_item_handler_t(����Handler);
			pk::add_menu_item(item����);


			pk::menu_item itemƯ����������;
			itemƯ����������.menu = 101;
			itemƯ����������.pos = 18;
			itemƯ����������.init = pk::building_menu_item_init_t(Ư����������Init);
			itemƯ����������.is_enabled = pk::menu_item_is_enabled_t(IsƯ����������Enabled);
			itemƯ����������.get_text = pk::menu_item_get_text_t(GetƯ����������Text);
			itemƯ����������.get_desc = pk::menu_item_get_desc_t(GetƯ����������Desc);
			itemƯ����������.handler = pk::menu_item_handler_t(Ư����������Handler);
			pk::add_menu_item(itemƯ����������);
		}
		bool loadData_old()
		{
			_elapsedDay = int(pk::load(KEY, 0, 0));
			int li = 1;
			int count = int(pk::load(KEY, li++, 0));
			pk::printf("sf old count0 : {}\n", count);
			for (int i = 0; i < count; i++)
			{
				SpecialForceItem@ sf = Ư����������Ʈ[i];
				int oid = int(pk::load(KEY, li++, -1));
				@sf.owner = oid != -1 ? pk::get_person(oid) : null;
				sf.ownerPos.x = int(pk::load(KEY, li++, 0));
				sf.ownerPos.y = int(pk::load(KEY, li++, 0));
				int count2 = int(pk::load(KEY, li++, 0));
				for (int j = 0; j < count2; j++)
				{
					int fid = int(pk::load(KEY, li++, 0));
					ForceInfo@ fi = getForce(fid);
					if (fi == null)
						continue;
					sf.currentForces.insertLast(fi);
				}
			}
			count = int(pk::load(KEY, li++, 0));
			pk::printf("fi old count1 : {}\n", count);
			for (int i = 0; i < count; i++)
			{
				ForceInfo@ fi = ���¸���Ʈ[i];
				if (�ܼ�_�α�_ǥ��_���̺�_�ε�)
					pk::printf("fi {}\n", getName(fi.force));
				fi.numPersons = int(pk::load(KEY, li++, 0));
				fi.numApply = int(pk::load(KEY, li++, 0));
				for (int j = 0; j < fi.numApply; j++)
				{
					int id = int(pk::load(KEY, li++, -1));
					if (�ܼ�_�α�_ǥ��_���̺�_�ε�)
						pk::printf("id li{},id{}\n", li - 1, id);
					SpecialForceItem@ sf = Ư����������Ʈ[id];

					SpecialForceApply sa;
					@sa.force = fi.force;
					@sa.item = sf;
					int count2 = int(pk::load(KEY, li++, -1));

					if (�ܼ�_�α�_ǥ��_���̺�_�ε�)
						pk::printf("pcount li{},{}\n", li - 1, count2);
					for (int k = 0; k < count2; k++)
					{
						int mid = int(pk::load(KEY, li++, -1));
						pk::person@ p = mid != -1 ? pk::get_person(mid) : null;
						if (p == null)
							continue;

						sa.persons.add(p);
						if (�ܼ�_�α�_ǥ��_���̺�_�ε�)
							pk::printf("pcount li{},{}", li - 1, getName(p));
						if (k == count2 - 1 && �ܼ�_�α�_ǥ��_���̺�_�ε�)
							pk::printf("\n");

					}
					fi.applies.insertLast(sa);
				}
			}

			return count > 0;
		}

		bool loadData_new()
		{
			_elapsedDay = int(pk::load(KEY, 1, 0));
			int li = 2;
			int count = int(pk::load(KEY, li++, 0));
			pk::printf("sf new count0 : {}\n", count);
			for (int i = 0; i < count; i++)
			{
				SpecialForceItem@ sf = Ư����������Ʈ[i];
				int oid = int(pk::load(KEY, li++, -1));
				@sf.owner = oid != -1 ? pk::get_person(oid) : null;
				sf.ownerPos.x = int(pk::load(KEY, li++, 0));
				sf.ownerPos.y = int(pk::load(KEY, li++, 0));
				int count2 = int(pk::load(KEY, li++, 0));
				for (int j = 0; j < count2; j++)
				{
					int fid = int(pk::load(KEY, li++, 0));
					ForceInfo@ fi = getForce(fid);
					if (fi == null)
						continue;
					sf.currentForces.insertLast(fi);
				}
			}
			count = int(pk::load(KEY, li++, 0));
			pk::printf("fi new count1 : {}\n", count);
			for (int i = 0; i < count; i++)
			{
				int fid = int(pk::load(KEY, li++, 0));
				ForceInfo@ fi = getForce(fid);
				if (fi == null) 
					@fi = ForceInfo();
				if (�ܼ�_�α�_ǥ��_���̺�_�ε�)
					pk::printf("fi {}\n", getName(fi.force));
				fi.numPersons = int(pk::load(KEY, li++, 0));
				fi.numApply = int(pk::load(KEY, li++, 0));
				for (int j = 0; j < fi.numApply; j++)
				{
					int id = int(pk::load(KEY, li++, -1));
					if (�ܼ�_�α�_ǥ��_���̺�_�ε�)
						pk::printf("id li{},id{}\n", li - 1, id);
					SpecialForceItem@ sf = Ư����������Ʈ[id];

					SpecialForceApply sa;
					@sa.force = fi.force;
					@sa.item = sf;
					int count2 = int(pk::load(KEY, li++, -1));

					if (�ܼ�_�α�_ǥ��_���̺�_�ε�)
						pk::printf("pcount li{},{}\n", li - 1, count2);
					for (int k = 0; k < count2; k++)
					{
						int mid = int(pk::load(KEY, li++, -1));
						pk::person@ p = mid != -1 ? pk::get_person(mid) : null;
						if (p == null)
							continue;

						sa.persons.add(p);
						if (�ܼ�_�α�_ǥ��_���̺�_�ε�)
							pk::printf("pcount li{},{}", li - 1, getName(p));
						if (k == count2 - 1 && �ܼ�_�α�_ǥ��_���̺�_�ε�)
							pk::printf("\n");

					}
					fi.applies.insertLast(sa);
				}
			}

			return count > 0;
		}

		bool loadData()
		{
			if (int(pk::load(KEY, 0, 0)) >= 0)
			{
				return loadData_old();
			}
			else
			{
				return loadData_new();
			}

		}
		void saveData(int file_id)
		{
			pk::store(KEY, 0, -1);
			pk::store(KEY, 1, _elapsedDay);
			int si = 2;
			
			pk::store(KEY, si++, Ư����������Ʈ.length);
			for (int i = 0; i < Ư����������Ʈ.length; i++)
			{
				SpecialForceItem@ sf = Ư����������Ʈ[i];
				pk::store(KEY, si++, sf.owner!=null ? sf.owner.get_id() : -1);
				pk::store(KEY, si++, int(sf.ownerPos.x));
				pk::store(KEY, si++, int(sf.ownerPos.y));

				int count2 = sf.currentForces.length;
				pk::store(KEY, si++, count2);
				for (int j = 0; j < count2; j++)
				{
					ForceInfo@ fi = sf.currentForces[j];
					pk::store(KEY, si++, fi!=null && fi.force!=null ? fi.force.get_id() : -1);
				}
			}
			pk::store(KEY, si++, ���¸���Ʈ.length);
			for (int i = 0; i < ���¸���Ʈ.length; i++)
			{
				ForceInfo@ fi = ���¸���Ʈ[i];
				pk::store(KEY, si++, fi.force!=null ? fi.force.get_id() : -1);
				if (fi != null)
				{
					pk::store(KEY, si++, fi.numPersons);
					pk::store(KEY, si++, fi.numApply);
				}
				else
				{
					pk::store(KEY, si++, 0);
					pk::store(KEY, si++, 0);
				}
				if(�ܼ�_�α�_ǥ��_���̺�_�ε�)
					pk::printf("fi {}\n", getName(fi.force));

				for (int j = 0; j < fi.applies.length; j++)
				{
					SpecialForceApply@ sa = fi.applies[j];
					if (sa != null)
					{
						pk::store(KEY, si++, sa.item.id);
						pk::store(KEY, si++, sa.persons.count);
					}
					else 
					{
						pk::store(KEY, si++, -1);
						pk::store(KEY, si++, 0);
					}

					if (�ܼ�_�α�_ǥ��_���̺�_�ε�)
						pk::printf("save si{},{},{}\n", si - 2, sa.item.id, sa.persons.count);
					for (int k = 0; k < sa.persons.count; k++)
					{
						if (�ܼ�_�α�_ǥ��_���̺�_�ε�)
							pk::printf("save si{},{}", si, getName(sa.persons[k]));
						pk::store(KEY, si++, sa.persons[k]!=null ? sa.persons[k].get_id() : -1);
						if(k==sa.persons.count-1 && �ܼ�_�α�_ǥ��_���̺�_�ε�)
							pk::printf("\n");
					}
					
				}
			}
		}

		bool isSkill(pk::person@ f)
		{
			for (int i = 0; i < Ư����������Ʈ.length; i++)
			{
				SpecialForceItem@ sf = Ư����������Ʈ[i];
				if (isSkill(f, sf.id))
					return true;
			}
			return false;
		}

		bool isSkill(pk::person@ f, int type)
		{
			if (f == null)
				return false;
			SpecialForceItem@ sf = getForceItem(type);
			if (sf == null)
				return false;

			for (int i = 0; i < sf.currentForces.length; i++)
			{
				ForceInfo@ fi = sf.currentForces[i];
				if(fi==null)
					continue;
				if (fi.force.get_id() != f.get_force_id())
					continue;



				for (int j = 0; j < fi.applies.length; j++)
				{
					SpecialForceApply@ sa = fi.applies[j];
					if (sa.item.id != type)
						continue;
					//if (f.get_id() == ����_����)
					//	pk::printf("lubu {}\n", sa.item.id);
					for (int k = 0; k < sa.persons.count; k++)
					{
						//if (f.get_id() == ����_����)
						//	pk::printf("lubu {}\n", getName(sa.persons[k]));

						if (sa.persons[k].get_id() == f.get_id())
							return true;
						//if (sa.persons.contains(f))
							//return true;
					}
				}
			}
			return false;
		}
		bool isSkill(pk::force@ f, int type)
		{
			return false;
		}
		bool isSkill(pk::unit@ u, int type)
		{
			SpecialForceItem@ sf = getForceItem(type);
			if (sf == null)
				return false;

			if (!check����(u, sf.����))
				return false;

			pk::person@ p0 = u.member[0] >= 0 && u.member[0] < ����_�� ? pk::get_person(u.member[0]) : null;
			pk::person@ p1 = u.member[1] >= 0 && u.member[1] < ����_�� ? pk::get_person(u.member[1]) : null;
			pk::person@ p2 = u.member[2] >= 0 && u.member[2] < ����_�� ? pk::get_person(u.member[2]) : null;
			return isSkill(p0, type) || isSkill(p1, type) || isSkill(p2, type);
		}
		bool isSkill(pk::unit@ u)
		{
			for (int i = 0; i < Ư����������Ʈ.length; i++)
			{
				SpecialForceItem@ sf = Ư����������Ʈ[i];
				if (isSkill(u, sf.id))
					return true;
			}
			return false;
		}

		int getSkill(pk::unit@ u)
		{
			for (int i = 0; i < Ư����������Ʈ.length; i++)
			{
				SpecialForceItem@ sf = Ư����������Ʈ[i];
				if (isSkill(u, sf.id))
					return sf.id;
			}
			return -1;
		}
		

		SpecialForceItem@ getForceItem(int type)
		{
			return Ư����������Ʈ[type];
		}
		bool check����(pk::unit@ u, int type)
		{
			int ���� = -1;
			switch (u.weapon)
			{
			case ����_��:���� = ����_�뺴; break;
			case ����_â:���� = ����_â��; break;
			case ����_��:���� = ����_�غ�; break;
			case ����_����:���� = ����_�⺴; break;
			}
			return ���� == type;
		}
		int callback200(pk::unit@ assister, pk::unit@ attacker, pk::unit@ target)
		{
			if (isSkill(assister, Ư������_�뺴_�����))
				return �����_��������_Ȯ��;
			return prev_callback_200��������(assister, attacker, target);
		}
		void callback209(pk::damage_info& info, pk::unit@ attacker, int tactics_id, const pk::point& in target_pos, int type, int critical, bool ambush)
		{
			prev_callback_209�δ����(info,attacker, tactics_id, target_pos,type,critical,ambush);
			pk::unit@ u = getUnit(target_pos);
			if ((type ==1 || type ==2) && u != null && isSkill(u, Ư������_�غ�_���))
				info.troops_damage = info.troops_damage + info.troops_damage * ���_�ݰ�_�߰� / 100.0;

			if (isSkill(attacker)) 
				info.troops_damage = info.troops_damage + info.troops_damage * Ư������_�߰�_���ݷ� / 100.0;
			if(u!=null && isSkill(u))
				info.troops_damage = info.troops_damage - info.troops_damage * Ư������_�߰�_���� / 100.0;
		}
		int callback202(pk::unit@ attacker, const pk::point& in pos, pk::hex_object@ target, int tactics_id)
		{
			int n=prev_callback_202��������(attacker, pos, target, tactics_id);
			pk::unit@ u = getUnit(target.get_pos());
			if (u != null && isSkill(u, Ư������_�غ�_�ع���))
				n = pk::max(0,n - �ع���_�������_�߰�);
			return n;
		}

		bool _bCritical = false;
		bool callback201(pk::unit@ attacker, pk::hex_object@ target, int tactics_id, bool ranged)
		{
			bool b = prev_callback_201(attacker, target, tactics_id, ranged);
			_bCritical = b;
			return b;
		}
		void callback163(pk::unit_attr& attr, const pk::detail::arrayptr<pk::person@>& in member, int weapon_id, uint troops, int type, int status, bool navy, bool shoubyou)
		{
			prev_callback_163�δ�ɷ�ġ(attr, member, weapon_id, troops, type, status, navy, shoubyou);

			pk::person@ leader = member[0];
			if (!pk::is_alive(leader))
				return;

			if (isSkill(leader, Ư������_�뺴_��������) || isSkill(member[1], Ư������_�뺴_��������) || isSkill(member[2], Ư������_�뺴_��������))
			{
				attr.stat[�δ�ɷ�_���] = pk::max(0, attr.stat[�δ�ɷ�_���] - attr.stat[�δ�ɷ�_���] * ��������_���_����� / 100.0);
				attr.stat[�δ�ɷ�_�̵�] = attr.stat[�δ�ɷ�_�̵�] + ��������_�̵���_�߰�;
			}
		}

		void �δ����ġ(pk::unit@ unit, int type)
		{
			//pk::person@ leader = pk::get_person(unit.leader);
			//pk::printf("exp {},type{},moo{},tong{},ki{},no{},kuk{}\n"
			//	, getNameLeader(unit), type, leader.stat_exp[����ɷ�_����], leader.stat_exp[����ɷ�_���], leader.heishu_exp[����_�⺴], leader.heishu_exp[����_�뺴], leader.heishu_exp[����_�غ�]);
		}

		void �δ��ൿ�Ϸ�(pk::unit@ unit)
		{
			_bCritical = false;
			if (!isSkill(unit, Ư������_â��_û�ֺ�))
				return;

			for (int i = 0; i < ����_��; i++)
			{
				pk::point pt = pk::get_neighbor_pos(unit.get_pos(), i, 1);
				pk::unit@ u = getUnit(pt);
				if(u==null)
					continue;
				if(!pk::rand_bool(û�ֺ�_�߰�����_Ȯ��))
					continue;
				if(!pk::is_enemy(unit,u))
					continue;
				
				//pk::say(pk::encode("�̰��� û�ֺ��̴�"), pk::get_person(unit.leader), unit);
				pk::damage_info di;
				di.src_pos = unit.get_pos();
				di.dst_pos = pt;
				callback209(di, unit, ����_����, pt, 0, 0, false);
				bool bCri = callback201(unit, u, ����_����, ũ��Ƽ��_����);
				pk::unit_anim(unit, ����_����_��������, {di}, pt, 0, getString("û�ֺ�"), 0);
				if (!�ݰ��ұ�(di, u))
				{
					addTroops(u, di);
					updateAfter(unit, u);
					update(unit, pt, { di },false, bCri);
				}
			}
		}

		ForceInfo@ getForce(int id)
		{
			for (int i = 0; i < ���¸���Ʈ.length; i++)
			{
				ForceInfo@ fi = ���¸���Ʈ[i];
				if (fi.force.get_id()  == id)
					return fi;
			}
			return null;
		}

		ForceInfo@ getItemOwner(SpecialForceItem@ sf)
		{
			ForceInfo@ fi = null;
			for (int j = 0; j < sf.items.count; j++)
			{
				pk::item@ it = sf.items[j];
				if(it==null)
					continue;;
				pk::person@ p = pk::get_person(it.owner);
				if (p == null)
					continue;
				ForceInfo@ fi2 = getForce(p.get_force_id());
				if(fi2==null)
					continue;
				if (fi != null && fi.force.get_id() != fi2.force.get_id())
					return null;

				@fi = fi2;
			}
			return fi;
		}
		array<ForceInfo@> getPersonsOwner(SpecialForceItem@ sf)
		{
			array<ForceInfo@> arr;
			for (int i = 0; i < sf.persons.count; i++)
			{
				pk::person@ p = sf.persons[i];
				if(p==null)
					continue;

				ForceInfo@ fi2 = getForce(p.get_force_id());
				if(fi2==null)
					continue;
				
				if (arr.findByRef(fi2) == -1)
					arr.insertLast(fi2);
			}
			return arr;
		}
		array<ForceInfo@> getTitleOwner(SpecialForceItem@ sf)
		{
			array<ForceInfo@> arr;
			if (sf.title == null)
				return arr;

			pk::list<pk::force@> forces = pk::get_force_list();
			for (int i = 0; i < forces.count; i++)
			{
				pk::force@ f = forces[i];
				if (f.title <= sf.title.get_id()) 
				{
					ForceInfo@ fi = getForce(f.get_id());
					if(fi==null)
						continue;
					arr.insertLast(fi);
				}
			}
			return arr;
		}
		bool checkItem(SpecialForceItem@ sf, ForceInfo@ itemForce)
		{
			if (itemForce == null)
				return false;
			if (sf.items.count == 0)
				return true;
			return itemForce != null;
		}
		bool checkItem(SpecialForceItem@ sf, ForceInfo@ itemForce,ForceInfo@ other)
		{
			if (sf.items.count == 0)
				return true;

			if (itemForce != null && other != null && itemForce.force!=null && other.force!=null && itemForce.force.get_id() == other.force.get_id())
				return true;
			else if (itemForce == null && other != null)
				return true;
			else if (itemForce != null && other == null)
				return false;
			else 
				return false;
		}
		bool checkPersons(SpecialForceItem@ sf,array<ForceInfo@> arr, ForceInfo@ fi0)
		{
			if (sf.persons.count == 0)
				return true;

			return arr.findByRef(fi0) >= 0;
		}
		bool checkTitle(SpecialForceItem@ sf,array<ForceInfo@> arr,ForceInfo@ fi0)
		{
			if (sf.title == null)
				return true;

			for (int i = 0; i < arr.length; i++)
			{
				ForceInfo@ fi = arr[i];
				if (fi.force.get_id() == fi0.force.get_id())
					return true;
			}
			return false;
		}
		bool checkTitle(SpecialForceItem@ sf, array<ForceInfo@> arr, array<ForceInfo@> arrPersons)
		{
			if (sf.title == null)
				return true;
			if (arr.length == 0)
				return false;

			for (int i = 0; i < arrPersons.length; i++)
			{
				ForceInfo@ fi = arrPersons[i];
				if (arr.findByRef(fi) >= 0)
					return true;
			}
			return false;
		}
		void create���¸���Ʈ()
		{
			while (���¸���Ʈ.length > 0)
				���¸���Ʈ.removeLast();
			pk::list<pk::force@> forces = pk::get_force_list();
			for (int i = 0; i < forces.count; i++)
			{
				pk::force@ f = forces[i];

				ForceInfo fi;
				@fi.force = f;
				���¸���Ʈ.insertLast(fi);
			}
		}
		void updateƯ������()
		{
			if (_elapsedDay == 0)
			{
				for (int i = 0; i < Ư����������Ʈ.length; i++)
				{
					SpecialForceItem@ sf = Ư����������Ʈ[i];
					@sf.owner = sf.firstOwner;
				}
				_elapsedDay++;
			}
			
			for (int i = 0; i < Ư����������Ʈ.length; i++)
			{
				SpecialForceItem@ sf = Ư����������Ʈ[i];
				array<ForceInfo@> currentForces;

				ForceInfo@ forceItem = getItemOwner(sf);
				array<ForceInfo@> forcePersosns = getPersonsOwner(sf);
				array<ForceInfo@> forceTitles = getTitleOwner(sf);
				if (checkItem(sf,forceItem) && checkPersons(sf,forcePersosns, forceItem) && checkTitle(sf, forceTitles, forceItem))
				{
					currentForces.insertLast(forceItem);
				}
				for (int j = 0; j < forcePersosns.length; j++)
				{
					ForceInfo@ fi = forcePersosns[j];
					if(fi==null)
						continue;
					if (checkItem(sf, forceItem, fi) && checkTitle(sf, forceTitles, fi)) 
					{
						if (currentForces.findByRef(fi) == -1)
							currentForces.insertLast(fi);
					}
				}
				for (int j = 0; j < forceTitles.length; j++)
				{
					ForceInfo@ fi = forceTitles[j];
					if (fi == null)
						continue;

					if (checkItem(sf, forceItem, fi) && checkPersons(sf, forcePersosns, fi))
					{
						if (currentForces.findByRef(fi) == -1)
							currentForces.insertLast(fi);
					}
				}
				if (sf.owner != null && forceItem==null && forcePersosns.length == 0 && forceTitles.length == 0)  
				{
					ForceInfo@ fi = getForce(sf.owner.get_force_id());
					if (currentForces.findByRef(fi) == -1)
						currentForces.insertLast(fi);
				}

				if (currentForces.length > 0)
				{
					currentForces.sort(function(a, b) 
					{
						return a.force.get_id() < b.force.get_id();
					});
				}
				if (sf.currentForces.length > 0)
				{
					sf.currentForces.sort(function(a, b)
					{
						return a.force.get_id() < b.force.get_id();
					});
				}

				for (int j = 0; j < sf.currentForces.length; j++)
				{
					ForceInfo@ fi0 = sf.currentForces[j];
					if(fi0==null)
						continue;
					bool bFound = false;
					for (int k = 0; k < currentForces.length; k++)
					{
						ForceInfo@ fi1 = currentForces[k];
						if(fi1==null)
							continue;
						if(fi0.force==null || fi1.force==null || fi0.force.get_id() != fi1.force.get_id())
							continue;
						bFound = true;
						break;
					}
					if (!bFound) 
					{
						pk::person@ kunshu = pk::get_person(fi0.force.kunshu);
						string str = pk::format("\x1b[2x{}��\x1b[0x, \x1b[29x{}\x1b[0x ���", getName(kunshu), sf.name);
						pk::history_log(kunshu !=null ? kunshu.get_pos() : pk::point(0,0), fi0.force.color, pk::encode(str));
						fi0.remove(sf);
					}
				}

				for (int j = 0; j < currentForces.length; j++)
				{
					ForceInfo@ fi0 = currentForces[j];
					if(fi0 == null)
						continue;
					bool bFound = false;
					for (int k = 0; k < sf.currentForces.length; k++)
					{
						ForceInfo@ fi1 = sf.currentForces[k];
						if(fi1 == null)
							continue;
						if (fi0.force.get_id() != fi1.force.get_id())
							continue;
						bFound = true;
						break;
					}
					if (!bFound)
					{
						pk::person@ kunshu = pk::get_person(fi0.force.kunshu);
						string str = pk::format("\x1b[2x{}��\x1b[0x,\x1b[1x{}\x1b[0x ȹ��", getName(kunshu), sf.name);
						pk::history_log(kunshu!=null ? kunshu.get_pos() : pk::point(), fi0.force.color, pk::encode(str));
						fi0.add(sf);
					}
				}
				if (sf.owner != null)
					sf.ownerPos = sf.owner.get_pos();
				sf.currentForces = currentForces;
			}

		}

		bool Ư��üũ(pk::person@ p, array<int> arr)
		{
			for (int i = 0; i < arr.length; i++)
			{
				if (pk::has_skill(p, arr[i]))
					return true;
			}
			return false;
		}

		bool Ư������(SpecialForceApply@ sa,pk::person@ p)
		{
			switch (sa.item.����)
			{
			case ����_�뺴:
				if (Ư��üũ(p, { Ư��_����,Ư��_����,Ư��_�п�,Ư��_�ý�,Ư��_���� }))
					return true;
				if (Ư��üũ(p, { Ư��_���,Ư��_����,Ư��_â��,Ư��_â��,Ư��_�ؽ�,Ư��_����,Ư��_����,Ư��_����,
					Ư��_����,Ư��_����,Ư��_����,Ư��_����,Ư��_����,Ư��_�ɰ�,Ư��_�鸶,Ư��_�౺}))
					return false;
				return true;
			case ����_�⺴:
				if (Ư��üũ(p, { Ư��_����,Ư��_����,Ư��_�п�,Ư��_����,Ư��_�鸶,Ư��_���,Ư��_���� }))
					return true;
				if (Ư��üũ(p, { Ư��_�ý�,Ư��_����,Ư��_â��,Ư��_â��,Ư��_�ؽ�,Ư��_����,Ư��_����,Ư��_����,Ư��_����}))
					return false;
				return true;
			case ����_�غ�:
				if (Ư��üũ(p, { Ư��_����,Ư��_����,Ư��_�ؽ�,Ư��_����,Ư��_����,Ư��_����,Ư��_�п�,Ư��_���� }))
					return true;
				if (Ư��üũ(p, { Ư��_�ý�,Ư��_����,Ư��_â��,Ư��_â��,Ư��_���,Ư��_����,Ư��_����,Ư��_����,Ư��_�鸶,Ư��_����,Ư��_�౺,Ư��_���}))
					return false;
				return true;
			case ����_â��:
				if (Ư��üũ(p, { Ư��_����,Ư��_����,Ư��_�п�,Ư��_���� ,Ư��_â��,Ư��_â��}))
					return true;
				if (Ư��üũ(p, { Ư��_�ý�,Ư��_����,Ư��_�ؽ�,Ư��_â��,Ư��_���,Ư��_����,Ư��_����,Ư��_����,Ư��_�鸶,Ư��_����,Ư��_�౺,Ư��_��� }))
					return false;
				return true;

			default:
				break;
			}
			return true;
		}

		pk::list<pk::person@> AIƯ����������Sort(SpecialForceApply@ sa, pk::list<pk::person@> persons0)
		{
			pk::list<pk::person@> persons;
			if (AIƯ����������_Ư�����)
			{
				for (int i = 0; i < persons0.count; i++)
				{
					if (!Ư������(sa, persons0[i]))
						continue;
					persons.add(persons0[i]);
				}
			}
			else 
			{
				persons = persons0;
			}
			
			switch (sa.item.����)
			{
			case ����_�뺴:
				persons.sort(function(a, b)
				{
					if (a.tekisei[����_�뺴] != b.tekisei[����_�뺴])
						return a.tekisei[����_�뺴] > b.tekisei[����_�뺴];
					if (a.stat[����ɷ�_���] + a.stat[����ɷ�_����] != b.stat[����ɷ�_���] + b.stat[����ɷ�_����])
						return a.stat[����ɷ�_���] + a.stat[����ɷ�_����] > b.stat[����ɷ�_���] + b.stat[����ɷ�_����];
					return true;
				});
				break;
			case ����_â��:
				persons.sort(function(a, b)
				{
					if (a.tekisei[����_â��] != b.tekisei[����_â��])
						return a.tekisei[����_â��] > b.tekisei[����_â��];
					if (a.stat[����ɷ�_���] + a.stat[����ɷ�_����] != b.stat[����ɷ�_���] + b.stat[����ɷ�_����])
						return a.stat[����ɷ�_���] + a.stat[����ɷ�_����] > b.stat[����ɷ�_���] + b.stat[����ɷ�_����];
					return true;
				});
				break;
			case ����_�غ�:
				persons.sort(function(a, b)
				{
					if (a.tekisei[����_�غ�] != b.tekisei[����_�غ�])
						return a.tekisei[����_�غ�] > b.tekisei[����_�غ�];
					if (a.stat[����ɷ�_���] + a.stat[����ɷ�_����] != b.stat[����ɷ�_���] + b.stat[����ɷ�_����])
						return a.stat[����ɷ�_���] + a.stat[����ɷ�_����] > b.stat[����ɷ�_���] + b.stat[����ɷ�_����];
					return true;
				});
				break;
			case ����_�⺴:
				persons.sort(function(a, b)
				{
					if (a.tekisei[����_�⺴] != b.tekisei[����_�⺴])
						return a.tekisei[����_�⺴] > b.tekisei[����_�⺴];
					if (a.stat[����ɷ�_���] + a.stat[����ɷ�_����] != b.stat[����ɷ�_���] + b.stat[����ɷ�_����])
						return a.stat[����ɷ�_���] + a.stat[����ɷ�_����] > b.stat[����ɷ�_���] + b.stat[����ɷ�_����];
					return true;
				});
				break;

			default:
				break;
			}

			return persons;
		}

		void AIƯ����������(SpecialForceApply@ sa, pk::list<pk::person@> persons, int count)
		{
			persons=AIƯ����������Sort(sa, persons);

			pk::list<pk::person@> personsNew;
			for (int i = 0; i < persons.count; i++)
			{
				pk::person@ p = persons[i];
				if(isSkill(p,sa.item.id))
					continue;

				personsNew.add(p);
				if (personsNew.count >= count)
					break;
			}
			sa.persons = personsNew;
		}
		void AIƯ����������Add(SpecialForceApply@ sa, pk::list<pk::person@> persons, int count)
		{
			persons=AIƯ����������Sort(sa, persons);

			pk::list<pk::person@> personsNew;
			for (int i = 0; i < persons.count; i++)
			{
				pk::person@ p = persons[i];
				if(isSkill(p))
					continue;

				personsNew.add(p);
				if (personsNew.count >= count)
					break;
			}

			for (int i = 0; i < personsNew.count; i++)
			{
				sa.persons.add(personsNew[i]);
			}
		}

		void AIƯ����������()
		{
			for (int i = 0; i < ���¸���Ʈ.length; i++)
			{
				ForceInfo@ fi = ���¸���Ʈ[i];
				if (fi.applies.length == 0 || fi.force.is_player()) 
				{
					fi.numApply = fi.applies.length;
					continue;
				}
					

				pk::list<pk::person@> persons = pk::get_person_list(fi.force, pk::mibun_flags(�ź�_����,�ź�_����,�ź�_�¼�,�ź�_�Ϲ�));
				if(fi.numPersons == persons.count && fi.numApply == fi.applies.length)
					continue;
				fi.numPersons = persons.count;
				fi.numApply = fi.applies.length;
				//pk::printf("apply {}\n", getName(fi.force));
				for (int j = 0;  j < fi.applies.length;  j++)
				{
					SpecialForceApply@ sa = fi.applies[j];
					AIƯ����������(sa, persons, Ư������_����_����);
				}
			}
		}
		void AIƯ����������2()
		{
			for (int i = 0; i < ���¸���Ʈ.length; i++)
			{
				ForceInfo@ fi = ���¸���Ʈ[i];
				if (fi.applies.length == 0 || fi.force.is_player())
				{
					fi.numApply = fi.applies.length;
					continue;
				}


				pk::list<pk::person@> persons = pk::get_person_list(fi.force, pk::mibun_flags(�ź�_����, �ź�_����, �ź�_�¼�, �ź�_�Ϲ�));
				//if (fi.numPersons == persons.count && fi.numApply == fi.applies.length)
				//	continue;
				fi.numPersons = persons.count;
				fi.numApply = fi.applies.length;

				for (int j = 0; j < fi.applies.length; j++)
				{
					SpecialForceApply@ sa = fi.applies[j];
					//sa.persons = {};
					sa.persons.clear();
				}
				
				for (int k = 0; k < Ư������_����_����; k++)
				{
					for (int j = 0; j < fi.applies.length; j++)
					{
						SpecialForceApply@ sa = fi.applies[j];
						AIƯ����������Add(sa, persons,1);
					}
				}

			}
		}

		void ����ó��()
		{
			for (int i = 0; i < Ư����������Ʈ.length; i++)
			{
				SpecialForceItem@ sf = Ư����������Ʈ[i];
				if (sf.owner == null) 
					continue;
				if (sf.owner.mibun != �ź�_����) 
					continue;

				pk::unit@ obj= getUnit(sf.owner.get_pos());
				if(obj==null)
					continue;
				pk::force@ force = pk::get_force(obj.get_force_id());
				if(force == null)
					continue;
				pk::person@ person = pk::get_person(force.kunshu);
				if(person==null)
					continue;
				//pk::printf("poro {}->{}\n", getName(sf.owner), getName(person));
				@sf.owner = person;
			}
		}
		void ���ó��()
		{
			for (int i = 0; i < Ư����������Ʈ.length; i++)
			{
				SpecialForceItem@ sf = Ư����������Ʈ[i];
				if (sf.owner == null)
					continue;
				if (sf.owner.mibun != �ź�_���)
					continue;

				int minDistance = 10000;
				pk::force@ minForce = null;
				for (int j = 0; j < ����_��; j++)
				{
					pk::person@ p = pk::get_person(j);
					if(p==null)
						continue;
					pk::force@ force = pk::get_force(p.get_force_id());
					if(force==null || force.get_id () == sf.owner.get_force_id())
						continue;

					int dist = pk::get_distance(p.get_pos(), sf.ownerPos);
					if (dist < minDistance)
					{
						minDistance = dist;
						@minForce = force;
					}
				}

				if(minForce == null)
					continue;
				pk::person@ person = pk::get_person(minForce.kunshu);
				if (person == null)
					continue;
				//pk::printf("die {}->{}\n", getName(sf.owner), getName(person));
				@sf.owner = person;
			}
		}

		void onInit()
		{
			create���¸���Ʈ();
			for (int i = 0; i < Ư����������Ʈ.length; i++)
			{
				Ư����������Ʈ[i].currentForces = {};
				@Ư����������Ʈ[i].owner = null;
			}
			if (!loadData())
			{
				updateƯ������();
				AIƯ����������2();
			}
		}
		void onNewDay()
		{
			����ó��();
			���ó��();
			�縶�ֺ���ȹ��();
			updateƯ������();
			AIƯ����������2();
			_elapsedDay++;
		}
		void onTurn(pk::force@ force)
		{
			AI�������(force);
		}

		void UpdatePerFrame()
		{
			if (_bCritical)
				return;
			for (int i = 0; i < ���¸���Ʈ.length; i++)
			{
				ForceInfo@ fi = ���¸���Ʈ[i];

				array<pk::unit@> units;
				for (int j = 0; j < fi.applies.length; j++)
				{
					SpecialForceApply@ sa = fi.applies[j];
					if(sa==null)
						continue;
					for (int k = 0; k < sa.persons.count; k++)
					{
						pk::person@ p = sa.persons[k];
						pk::unit@ u = getUnit(p.get_pos());
						if (u == null)
							continue;
						if (!check����(u, sa.item.����))
							continue;

						if(units.findByRef(u)==-1)
							units.insertLast(u);
					}//k
				}//j

				for (int j = 0; j < units.length; j++)
				{
					pk::unit@ u = units[j];
					string str = "";
					for (int k = 0; k < Ư����������Ʈ.length; k++)
					{
						SpecialForceItem sf = Ư����������Ʈ[k];
						if (!isSkill(u, k)) 
						{
							//pk::printf("isskill return{}\n", getNameLeader(u));
							continue;
						}
							
						if(str == "")
							str = str + pk::format("\x1b[1x{}\x1b[0x", sf.name);
						else
							str = str + pk::format("\x1b[1x {}\x1b[0x", sf.name);
					}
					pk::point point = pk::hex_pos_to_screen_pos(u.get_pos());
					pk::draw_text(pk::encode(str), point);
					pk::size size0 = pk::get_size(FONT_SMALL, str);
					pk::rectangle r0(point, size0);
					pk::draw_filled_rect(r0, 0x40000000);
				}

			}//i
		}
		void �縶�ֺ���ȹ��()
		{
			SpecialForceItem@ item = null;
			for (int i = 0; i < Ư����������Ʈ.length; i++)
			{
				SpecialForceItem@ sf = Ư����������Ʈ[i];
				//pk::printf("sf {},len{},item{},persons{},title{},onwer:{}\n", sf.name, sf.currentForces.length, sf.items.count, sf.persons.count,getName(sf.title),getName(sf.owner));
				if(sf.currentForces.length != 0)
					continue;
				if(sf.items.count!=0 || sf.persons.count!=0 || sf.title!=null || sf.owner!=null)
					continue;
				if(!pk::rand_bool(�縶��_����_ȹ��_Ȯ��))
					continue;
				@item = sf;
				break;
			}
			if (item == null)
				return;

			pk::list<pk::force@> forces = pk::get_force_list();
			forces.shuffle();
			while (!forces[0].is_player())
				forces.remove_at(0);

			pk::person@ kunshu = pk::get_person(forces[0].kunshu);
			if (kunshu == null)
				return;
			@item.owner = kunshu;
			if (forces[0].is_player())
			{
				string str = pk::format("\x1b[2x{}\x1b[0x�� �ְڳ�. �鼺���� �̷Ӱ� �ϴµ� ����ϰԳ�.",item.name);
				pk::message_box(pk::encode(str), pk::get_person(����_�縶��));
			}

			string str2 = pk::format("\x1b[2x{}��\x1b[0x,\x1b[2x{}\x1b[0x �縶�ַκ��� ȹ��",getName(forces[0]), item.name);
			pk::history_log(kunshu.get_pos(), forces[0].color, pk::encode(str2));
		}
		/////////////////////////Ư���������� �޴�


		pk::force@ _force;
		pk::building@ _building;
		pk::district@ _district;
		void Ư����������Init(pk::building@ building)
		{
			@_force = pk::get_force(building.get_force_id());
			@_building = building;
		}
		bool IsƯ����������Enabled()
		{
			return true;
		}
		string GetƯ����������Text()
		{
			return pk::encode("Ư����������");
		}
		string GetƯ����������Desc()
		{
			return pk::encode("Ư�������� �����մϴ�.");
		}


		void select(SpecialForceApply@ sa)
		{
			pk::list<pk::person@> persons0 = pk::get_person_list(_force, pk::mibun_flags(�ź�_����, �ź�_����, �ź�_�¼�, �ź�_�Ϲ�));
			pk::list<pk::person@> persons;
			for (int i = 0; i < persons0.count; i++)
			{
				pk::person@ p = persons0[i];
				for (int j = 0; j < sa.persons.count; j++)
				{
					if (p.get_id() == sa.persons[j].get_id())
					{
						persons.add(p);
						break;
					}
				}
			}

			ForceInfo@ fi = getForce(sa.force.get_id());
			for (int i = 0; i < persons0.count; i++)
			{
				pk::person@ p = persons0[i];
				bool bFound = false;
				for (int j = 0; j < persons.count; j++)
				{
					if (p.get_id() == persons[j].get_id())
					{
						bFound = true;
						break;
					}
				}
				if(bFound)
					continue;

				for (int i = 0; i < fi.applies.length; i++)
				{
					SpecialForceApply@ sa2 = fi.applies[i];
					if (sa2.item.id == sa.item.id)
						continue;
					if (sa2.persons.contains(p))
					{
						bFound = true;
						break;
					}
				}
				if (bFound)
					continue;
				if(!Ư������_������_����_�׽�Ʈ && pk::is_unitize(p))
					continue;

				persons.add(p);
			}

			pk::list<pk::person@> newPersons = pk::person_selector(pk::encode("���� ����"), pk::encode("Ư�������� ������ ������ �����Ͻʽÿ�"), persons, 0, Ư������_����_����, sa.persons);
			sa.persons = newPersons;
		}

		bool Ư����������Handler()
		{
			array<SpecialForceApply@> sfs;
			for (int i = 0; i < ���¸���Ʈ.length; i++)
			{
				ForceInfo@ fi = ���¸���Ʈ[i];
				for (int j = 0; j < fi.applies.length; j++)
					sfs.insertLast(fi.applies[j]);
			}

			if (sfs.length > 1) 
			{
				sfs.sort(function(a, b)
				{
					bool b0 = a.force.is_player();
					bool b1 = b.force.is_player();
					if (b0 == b1)
						return true;
					else if (b0 && !b1)
						return true;
					else if (!b0 && b0)
						return false;
					else
						return false;
				});
			}

			int si = 0;
			SpecialForceApply@ selected = null;
			while (true)
			{
				array<string> itemArr;
				array<SpecialForceApply@> itemArr2;
				int count = pk::min(sfs.length, si + 4);
				if (si == 0)
					itemArr.insertLast(pk::encode("����"));
				else
					itemArr.insertLast(pk::encode("�ڷ�"));
				for (int i = si; i < count; i++)
				{
					SpecialForceApply@ sa = sfs[i];
					string str = "";
					if (sa.persons.count == 0) 
					{
						str = pk::format("{},{}��,����", sa.item.name, getName(sa.force));
					}
					else 
					{
						string str0 = "";
						for (int j = 0; j < sa.persons.count; j++)
						{
							if (j != sa.persons.count - 1)
								str0 = str0 + pk::format("{}", getName(sa.persons[j])) + ",";
							else
								str0 = str0 + pk::format("{}", getName(sa.persons[j]));
						}
						str = pk::format("{},{}��,{}", sa.item.name, getName(sa.force), str0);
					}
					
					itemArr.insertLast(pk::encode(str));
					itemArr2.insertLast(sa);
				}
				if (si + 4 >= sfs.length)
					itemArr.insertLast(pk::encode("����"));
				else
					itemArr.insertLast(pk::encode("����"));

				int choose = pk::choose(pk::encode("�������ֽʽÿ�"), itemArr);
				if (choose == itemArr.length - 1)
				{
					si = si + 4;
					if (si >= sfs.length)
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
					@selected = itemArr2[choose - 1];
				}
				if (selected == null)
					continue;

				if (selected.force.get_id() != _force.get_id()) 
				{
					pk::message_box(pk::encode("Ÿ������ ������ �� �����ϴ�."));
					@selected = null;
					continue;
				}
				select(selected);
				@selected = null;
			}


			return true;
		}
		///////////////////////////////////AI�������

		bool AI�������_���뺴_����(pk::unit@ u)
		{
			//���������� ã�� �߻�
			if (!pk::rand_bool(AI����_����Ȯ��))
				return false;
			
			int dist = getMaxAttackDistance(u)+1;
			//int dist = 3;
			int minDist = 2;
			int curDist = 2;

			int maxAttack = 0;
			pk::unit@ maxUnit = null;
			pk::point maxPos;

			array<pk::point> arr = pk::get_movable_pos(u);
			for (int i0 = 0; i0 < arr.length; i0++)
			{
				pk::point pt0 = arr[i0];
				if (!pk::is_in_screen(pt0))
					continue;

				while (curDist <= dist)
				{
					for (int i = 0; i < ����_��; i++)
					{
						pk::point pt = pk::get_neighbor_pos(pt0, i, curDist);
						pk::unit@ unit = getUnit(pt);
						if (unit == null || !pk::is_enemy(u, unit))
							continue;
						if (!checkHex�뺴(u, pt))
							continue;

						if (unit.attr.stat[�δ�ɷ�_����] > maxAttack)
						{
							maxAttack = unit.attr.stat[�δ�ɷ�_����];
							@maxUnit = unit;
							maxPos = pt0;
						}
					}
					curDist++;
				}
			}

			if (maxUnit == null)
				return false;

			if(�ܼ�_�α�_ǥ��)
				pk::printf("sniper start{}->{}\n",getNameLeader(u), getNameLeader(maxUnit));
			pk::move(u, { maxPos });
			execute����(u, maxUnit.get_pos());
			if (�ܼ�_�α�_ǥ��)
				pk::printf("sniper end{}->{}\n", getNameLeader(u), getNameLeader(maxUnit));

			return true;
		}
		bool AI�������_���뺴_��ȭ��(pk::unit@ u)
		{
			//3���̻�Ǹ� �߻�
			int dist = getMaxAttackDistance(u);
			//int dist = 2;
			int minDist = 2;
			int curDist = 2;
			bool b�ý� = u.has_skill(Ư��_�ý�);
			
			array<pk::point> arr = pk::get_movable_pos(u);
			for (int i0 = 0; i0 < arr.length; i0++)
			{
				pk::point pt0 = arr[i0];
				if (!pk::is_in_screen(pt0))
					continue;

				while (curDist <= dist)
				{
					for (int i = 0; i < ����_��; i++)
					{
						pk::point pt = pk::get_neighbor_pos(pt0, i, curDist);
						pk::unit@ unit = getUnit(pt);
						if (unit == null || !pk::is_enemy(u, unit))
							continue;
						if (!checkHex�뺴(u, pt))
							continue;

						int acount = 0;
						bool bMine = false;
						array<pk::point> arr = pk::range(pt, 1, 1);
						for (int j = 0; j < arr.length; j++)
						{
							pk::point pt2 = arr[j];
							pk::unit@ unit2 = getUnit(pt2);
							if (unit2 == null)
								continue;
							if (!checkHex�뺴(u, pt2))
								continue;

							if (!b�ý� && !pk::is_enemy(u, unit2))
							{
								bMine = true;
								break;
							}
							acount++;
						}
						if (bMine || acount < 3)
							continue;

						if (�ܼ�_�α�_ǥ��)
							pk::printf("greate fire start{} -> {}\n", getNameLeader(u), getNameLeader(unit));
						pk::move(u, { pt0 });
						execute��ȭ��(u, pt);
						if (�ܼ�_�α�_ǥ��)
							pk::printf("greate fire end{} -> {}\n", getNameLeader(u), getNameLeader(unit));
						return true;

					}
					curDist++;
				}
			}


			return false;
		}
		bool AI�������_���踸��_����(pk::unit@ u)
		{
			if (!pk::rand_bool(AI����_����Ȯ��))
				return false;

			int maxAttack = 0;
			pk::unit@ maxUnit = null;
			pk::point maxPos;

			array<pk::point> arr = pk::get_movable_pos(u);
			for (int i0 = 0; i0 < arr.length; i0++)
			{
				pk::point pt0 = arr[i0];
				if (!pk::is_in_screen(pt0))
					continue;

				for (int i = 0; i < ����_��; i++)
				{
					pk::point pt = pk::get_neighbor_pos(pt0, i, 1);
					pk::unit@ unit = getUnit(pt);
					if (unit == null || !pk::is_enemy(u, unit))
						continue;

					if (unit.attr.stat[�δ�ɷ�_����] > maxAttack)
					{
						maxPos = pt0;
						maxAttack = unit.attr.stat[�δ�ɷ�_����];
						@maxUnit = unit;
					}
				}
			}

			if (maxUnit == null)
				return false;

			if (�ܼ�_�α�_ǥ��)
				pk::printf("counter attack start {} -> {}\n", getNameLeader(u), getNameLeader(maxUnit));
			pk::move(u, { maxPos });
			execute����(u, maxUnit.get_pos());
			if (�ܼ�_�α�_ǥ��)
				pk::printf("counter attack end {} -> {}\n", getNameLeader(u), getNameLeader(maxUnit));
			return true;
		}
		bool AI�������_��������_��ǳ��(pk::unit@ u)
		{
			int dist = getMaxAttackDistance(u);
			bool b�ý� = u.has_skill(Ư��_�ý�);

			array<pk::point> arr = pk::get_movable_pos(u);
			for (int i0 = 0; i0 < arr.length; i0++)
			{
				pk::point pt0 = arr[i0];
				if (!pk::is_in_screen(pt0))
					continue;

				array<pk::point> range = pk::range(pt0, 2, dist);
				for (int i = 0; i < range.length; i++)
				{
					pk::point pt = range[i];
					array<pk::point> range2 = pk::range(pt, 0, 2);
					int acount = 0;
					bool bMine = false;

					pk::unit@ unit = pk::get_unit(pt);
					if (unit == null)
						continue;
					if (!pk::is_enemy(u, unit))
						continue;
					if (!checkHex�뺴(u, pt))
						continue;

					for (int j = 0; j < range2.length; j++)
					{
						pk::point pt2 = range2[j];
						pk::unit@ unit2 = getUnit(pt2);
						if (unit2 == null)
							continue;
						if (!checkHex�뺴(u, pt2))
							continue;

						if (!b�ý� && !pk::is_enemy(u, unit2))
						{
							bMine = true;
							break;
						}
						acount++;
					}

					if (bMine || acount < 3)
						continue;

					if(�ܼ�_�α�_ǥ��)
						pk::printf("storm start {}->{}\n", getNameLeader(u), getNameLeader(unit));
					pk::move(u, { pt0 });
					execute��ǳ��(u, pt);
					if (�ܼ�_�α�_ǥ��)
						pk::printf("storm end {}->{}\n", getNameLeader(u), getNameLeader(unit));
					return true;
				}
			}



			
			return false;
		}
		bool AI�������_���̺�_�س���÷(pk::unit@ u)
		{
			int dist = 2;

			int maxAttack = 0;
			pk::unit@ maxUnit = null;
			pk::point maxPos;

			array<pk::point> arr = pk::get_movable_pos(u);
			for (int i0 = 0; i0 < arr.length; i0++)
			{
				pk::point pt0 = arr[i0];
				if (!pk::is_in_screen(pt0))
					continue;

				array<pk::point> range = pk::range(pt0, 2, 2);
				for (int i = 0; i < range.length; i++)
				{
					pk::point pt = range[i];
					pk::unit@ unit = getUnit(pt);
					if (unit == null || !pk::is_enemy(u, unit))
						continue;
					if (!checkHexâ��(pt))
						continue;

					int dist = pk::get_distance(u.get_pos(), pt);
					if (dist == 2)
					{
						int dir = pk::get_direction(u.get_pos(), pt);
						pk::point ptCenter = pk::get_neighbor_pos(u.get_pos(), dir, 1);
						//ptCenter.x = (u.get_pos().x + pt.x) * 0.5;
						//ptCenter.y = (u.get_pos().y + pt.y) * 0.5;
						pk::hex_object@ obj = pk::get_hex_object(ptCenter);
						//pk::printf("pos x{},y{}\n", ptCenter.x, ptCenter.y);
						//if (obj != null)
						//	pk::printf("obj type {},x{},y{}\n", obj.get_type_id(), ptCenter.x, ptCenter.y);
						//else
						//{
						//	pk::printf("obj null x{},y{}\n", ptCenter.x, ptCenter.y);
						//}

						if (obj != null && obj.get_type_id() != 11)
						{
							pk::printf("length return {}\n", getNameLeader(u));
							continue;
						}
						if (obj == null && pk::get_hex(ptCenter).terrain == ����_����)
						{
							pk::printf("length return {}\n", getNameLeader(u));
							continue;
						}

					}

					if (unit.attr.stat[�δ�ɷ�_����] > maxAttack)
					{
						maxPos = pt0;
						maxAttack = unit.attr.stat[�δ�ɷ�_����];
						@maxUnit = unit;
					}
				}
			}



			if (maxUnit == null)
				return false;

			if(�ܼ�_�α�_ǥ��)
				pk::printf("nasunchum start {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			pk::move(u, { maxPos });
			execute�س���÷(u, maxUnit.get_pos());
			if (�ܼ�_�α�_ǥ��)
				pk::printf("nasunchum end {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
			return true;
		}

		bool AI�������_��ػ�_������(pk::unit@ u)
		{
			array<pk::point> arr = pk::get_movable_pos(u);
			for (int i0 = 0; i0 < arr.length; i0++)
			{
				pk::point pt0 = arr[i0];
				if (!pk::is_in_screen(pt0))
					continue;

				for (int i = 0; i < ����_��; i++)
				{
					pk::point pt = pk::get_neighbor_pos(pt0, i, 1);
					pk::unit@ unit = getUnit(pt);
					if (unit == null || !pk::is_enemy(u, unit))
						continue;
					if (!checkHexâ��(pt))
						continue;

					pk::point pt1 = pk::get_neighbor_pos(pt0, i, 2);
					pk::point pt2 = pk::get_neighbor_pos(pt0, i, 3);
					pk::unit@ unit1 = getUnit(pt1);
					pk::unit@ unit2 = getUnit(pt2);
					if (unit1 != null && pk::is_enemy(u, unit1) || 
						(unit1 ==null &&  unit2 != null && pk::is_enemy(u, unit2)))
					{
						
						if (�ܼ�_�α�_ǥ��)
							pk::printf("noShadow start {}->{}\n", getNameLeader(u), getNameLeader(unit));
						pk::move(u, { pt0 });
						execute������(u, pt);
						if (�ܼ�_�α�_ǥ��)
							pk::printf("noShadow no {}->{}\n", getNameLeader(u), getNameLeader(unit));
						return true;
					}
				}
			}
			return true;
		}
		bool AI�������_�����_ȭ����(pk::unit@ u)
		{
			array<pk::point> arr = pk::get_movable_pos(u);
			for (int i0 = 0; i0 < arr.length; i0++)
			{
				pk::point pt0 = arr[i0];
				if (!pk::is_in_screen(pt0))
					continue;

				for (int i = 0; i < ����_��; i++)
				{
					pk::point pt = pk::get_neighbor_pos(pt0, i, 1);
					pk::unit@ unit = getUnit(pt);
					if (unit == null || !pk::is_enemy(u, unit))
						continue;
					if (!checkHexâ��(pt))
						continue;

					pk::point pt1 = pk::get_neighbor_pos(pt0, i, 2);
					pk::point pt2 = pk::get_neighbor_pos(pt0, i, 3);
					pk::unit@ unit1 = getUnit(pt1);
					pk::unit@ unit2 = getUnit(pt2);
					if (unit1 != null && pk::is_enemy(u, unit1) || 
						(unit1 ==null && unit2 != null && pk::is_enemy(u, unit2)))
					{

						if (�ܼ�_�α�_ǥ��)
							pk::printf("fireball start {}->{}\n", getNameLeader(u), getNameLeader(unit));
						pk::move(u, { pt0 });
						executeȭ����(u, pt);
						if (�ܼ�_�α�_ǥ��)
							pk::printf("fireball end {}->{}\n", getNameLeader(u), getNameLeader(unit));
						return true;
					}
				}
			}
			return false;
		}
		bool AI�������_�ܾ纴_��ô(pk::unit@ u)
		{
			int maxRatio = 0;
			pk::unit@ maxUnit = null;
			pk::point maxPos;
			int acount = 0;

			array<pk::point> arr = pk::get_movable_pos(u);
			for (int i0 = 0; i0 < arr.length; i0++)
			{
				pk::point pt0 = arr[i0];
				if (!pk::is_in_screen(pt0))
					continue;

				array<pk::point> arr = pk::range(pt0, 1, 1);
				for (int i = 0; i < arr.length; i++)
				{
					pk::point pt = arr[i];
					pk::unit@ unit = getUnit(pt);
					if (unit == null || !pk::is_enemy(u, unit))
						continue;

					acount++;
					int nTactics = callback202(u, pt, unit, ����_��ǳ);
					if (nTactics > maxRatio)
					{
						@maxUnit = unit;
						maxRatio = nTactics;
						maxPos = pt0;
					}
				}
			}
			
			if (acount >= 2 && maxUnit!=null)
			{
				if (�ܼ�_�α�_ǥ��)
					pk::printf("fireAll start {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
				pk::move(u, { maxPos });
				execute��ô(u, maxUnit.get_pos());
				if (�ܼ�_�α�_ǥ��)
					pk::printf("fireAll end {}->{}\n", getNameLeader(u), getNameLeader(maxUnit));
				return true;
			}
			return false;
		}

		bool AI�������_������_����(pk::unit@ u)
		{
			//2���̻�Ǹ� �߻�
			int dist = getMaxAttackDistance(u);

			array<pk::point> arr = pk::get_movable_pos(u);
			for (int i0 = 0; i0 < arr.length; i0++)
			{
				pk::point pt0 = arr[i0];
				if (!pk::is_in_screen(pt0))
					continue;

				for (int i = 0; i < ����_��; i++)
				{
					pk::point pt = pk::get_neighbor_pos(pt0, i, dist);
					pk::unit@ unit = getUnit(pt);
					if (unit == null || !pk::is_enemy(u, unit))
						continue;
					if (!checkHex�غ�(pt))
						continue;

					array<pk::point> arr = getȾġpos(pt0, pt);
					pk::unit@ u0 = getUnit(arr[0]);
					pk::unit@ u1 = getUnit(arr[1]);
					if (u0 != null && pk::is_enemy(u, u0) || u1 != null && pk::is_enemy(u, u1))
					{
						if (�ܼ�_�α�_ǥ��)
							pk::printf("doCharm start {}->{}\n", getNameLeader(u), getNameLeader(unit));
						pk::move(u, { pt0 });
						execute����(u, pt);
						if (�ܼ�_�α�_ǥ��)
							pk::printf("doCharm end {}->{}\n", getNameLeader(u), getNameLeader(unit));
						return true;
					}
				}
			}

			return false;
		}
		bool AI�������_����ö��_����(pk::unit@ u,bool bMulpa)
		{
			array<pk::point> arr = pk::get_movable_pos(u);

			int maxDist = 0;
			pk::unit@ maxUnit = null;
			pk::point maxPt;
			for (int i = 0; i < arr.length; i++)
			{
				pk::point pt = arr[i];
				if (!pk::is_in_screen(pt))
					continue;

				int dist = pk::get_distance(pt, u.get_pos());
				if(dist<2)
					continue;

				for (int j = 0; j < ����_��; j++)
				{
					pk::point pt2 = pk::get_neighbor_pos(pt, j, 1);
					int dist2 = pk::get_distance(u.get_pos(), pt2);
					if(dist2<3)
						continue;
					pk::unit@ unit = getUnit(pt2);
					if (unit == null || !pk::is_enemy(u, unit))
						continue;
					if(!checkHex�⺴(pt2))
						continue;
					if (dist2 > maxDist)
					{
						maxDist = dist2;
						@maxUnit = unit;
						maxPt = pt;
					}
				}
			}
			if (maxUnit == null)
				return false;

			if(�ܼ�_�α�_ǥ��)
				pk::printf("{} start {}->{}\n", bMulpa ? "moveAttackerPower":"moveAttackEnergy", getNameLeader(u), getNameLeader(maxUnit));
			pk::move(u, {maxPt});
			if (bMulpa)
				execute����(u, maxUnit.get_pos());
			else
				execute����(u, maxUnit.get_pos());
			if (�ܼ�_�α�_ǥ��)
				pk::printf("{} end {}->{}\n", bMulpa ? "moveAttackerPower" : "moveAttackEnergy", getNameLeader(u), getNameLeader(maxUnit));
			return true;
		}

		bool AI�������_ȣǥ��_����(pk::unit@ u)
		{
			array<pk::point> arr = pk::get_movable_pos(u);
			for (int i = 0; i < arr.length; i++)
			{
				pk::point pt = arr[i];
				if (!pk::is_in_screen(pt))
					continue;

				for (int j = 0; j < ����_��; j++)
				{
					pk::point pt2 = pk::get_neighbor_pos(pt, j, 1);
					pk::unit@ unit = getUnit(pt2);
					if (unit == null || !pk::is_enemy(u, unit))
						continue;
					if(!checkHex�⺴(pt2))
						continue;

					array<pk::point> arr = getȾġpos(pt, pt2);
					pk::unit@ u0 = checkHex�⺴(arr[0]) ? getUnit(arr[0]) : null;
					pk::unit@ u1 = checkHex�⺴(arr[1]) ? getUnit(arr[1]) : null;
					if (u0 != null && pk::is_enemy(u, u0) || u1 != null && pk::is_enemy(u, u1))
					{
						if (�ܼ�_�α�_ǥ��)
							pk::printf("nando start {}->{}\n", getNameLeader(u), getNameLeader(unit));
						pk::move(u, { pt });
						execute����(u, pt2);
						if (�ܼ�_�α�_ǥ��)
							pk::printf("nando end {}->{}\n", getNameLeader(u), getNameLeader(unit));
						return true;
					}
				}
			}
			return false;
		}
		bool AI�������_�鸶����_�鸶��(pk::unit@ u)
		{
			int maxDist = getMaxAttackDistance(u);
			maxDist = 2;
			
			bool b�ý� = u.has_skill(Ư��_�ý�);
			array<pk::point> arr = pk::get_movable_pos(u);
			for (int i = 0; i < arr.length; i++)
			{
				pk::point pt = arr[i];
				if(!pk::is_in_screen(pt))
					continue;
				array<pk::point> arr2 = pk::range(pt, 1, maxDist);
				for (int j = 0; j < arr2.length; j++)
				{
					pk::point pt2 = arr2[j];
					pk::unit@ unit = getUnit(pt2);
					if (unit == null || !pk::is_enemy(u, unit))
						continue;
					if (!checkHex�⺴(pt2))
						continue;
					int acount = 0;
					array<pk::point> arr3 = pk::range(pt2, 0, 1);
					bool bMine = false;
					for (int k = 0; k < arr3.length; k++)
					{
						pk::point pt3 = arr3[k];
						pk::unit@ unit2 = getUnit(pt3);
						if (unit2 == null || !pk::is_enemy(u, unit2))
							continue;
						if (!checkHex�⺴(pt3))
							continue;
						if (!b�ý� && !pk::is_enemy(u, unit2))
						{
							bMine = true;
							break;
						}
						acount++;
					}
					if (bMine || acount < 3) 
						continue;
						
					if (�ܼ�_�α�_ǥ��)
						pk::printf("white horse start {}->{}\n", getNameLeader(u), getNameLeader(unit));
					pk::move(u, { pt });
					execute�鸶��(u, pt2);
					if (�ܼ�_�α�_ǥ��)
						pk::printf("white horse end {}->{}\n", getNameLeader(u), getNameLeader(unit));
					return true;
				}
			}
			return false;

		}

		void AI�������(pk::force@ force)
		{
			if (force.is_player() || !AI����_���)
				return;

			pk::list<pk::unit@> units = pk::get_unit_list(force);
			for (int i = 0; i < units.count; i++)
			{
				pk::unit@ u = units[i];
				if(!pk::is_in_screen(u.get_pos()))
					continue;

				int n = 0;
				try
				{
					n = int(pk::core["����"][pk::get_tekisei(u)]["��������Ȯ��"]) + pk::core::tactics_chance(u.leader);
				}
				catch
				{
					pk::printf("try catch return {}\n", getNameLeader(u));
					continue;
				}
				
					

				if(u.energy < ����_���)
					continue;
				//AI�������_���踸��_����(u);
				//continue;
				int skill = getSkill(u);
				if(skill == -1)
					continue;

				//pk::printf("ai tacticks {}\n", getNameLeader(u));
				bool b = false;
				
				switch (skill)
				{
				case Ư������_�뺴_���뺴:b=AI�������_���뺴_����(u); break;
				case Ư������_�뺴_���뺴:b=AI�������_���뺴_��ȭ��(u); break;
				case Ư������_�뺴_���踸��:b = AI�������_���踸��_����(u); break;
				case Ư������_�뺴_��������:b = AI�������_��������_��ǳ��(u); break;
				case Ư������_â��_���̺�:b = AI�������_���̺�_�س���÷(u); break;
				case Ư������_â��_��ػ�:b = AI�������_��ػ�_������(u); break;
				case Ư������_â��_�����:b = AI�������_�����_ȭ����(u); break;
				case Ư������_�غ�_�ܾ纴:b = AI�������_�ܾ纴_��ô(u); break;
				case Ư������_�غ�_������:b = AI�������_������_����(u); break;
				case Ư������_�⺴_����ö��:b = AI�������_����ö��_����(u,true); break;
				case Ư������_�⺴_������:b = AI�������_����ö��_����(u, false); break;
				case Ư������_�⺴_ȣǥ��:b = AI�������_ȣǥ��_����(u); break;
				case Ư������_�⺴_�鸶����:b = AI�������_�鸶����_�鸶��(u); break;
				
				default:
					break;
				}
			}
		}

		/////////////////////////////////����
		pk::unit@ _unit;
		pk::point _src_pos;
		pk::point _src_pos0;
		void init(pk::unit@ unit, pk::point src_pos)
		{
			@_unit = unit;
			_src_pos = src_pos;
			_src_pos0 = unit.get_pos();
			@_force = pk::get_force(_unit.get_force_id());
		}
		bool IsVisible����()
		{
			return ��ü_����_���_�׽�Ʈ || isSkill(_unit, Ư������_�뺴_���뺴);
		}
		string Get����Text()
		{
			return pk::encode("����");
		}
		string Get����Desc()
		{
			return pk::encode("��Ÿ����� Ȱ�� ��� �λ�Ȯ���� �����մϴ�.");
		}
		pk::array<pk::point_int> GetTargets����()
		{
			pk::array<pk::point_int> targets;

			pk::force@ f = pk::get_force(_unit.get_force_id());
			
			auto range=pk::range(_src_pos,2,pk::has_tech(f,�ⱳ_����) ? 4 : 3);
			for(int i=0;i<range.length;i++)
			{
				pk::hex_object@ obj=pk::get_hex_object(range[i]);
				if (obj == null)
					continue;
				if(_force!=null && _force.get_id() == obj.get_force_id())
					continue;
				if(!checkHex�뺴(_unit,range[i]))
					continue;

				targets.insertLast(pk::point_int(range[i], 0));
			}
			return targets;
		}
		int GetChance����(pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return 0;

			return callback202(_unit, dst_pos, target, ����_����);
		}

		void execute����(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			int nTactics = callback202(unit0, dst_pos, target, ����_����);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), ����_����, ũ��Ƽ��_���Ÿ�);

			//bTactics = false;
			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, ����_����_Ȱ����, bCri);
			}
			else
			{
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, ����_����, dst_pos, 0, bCri ? 1 : 0, false);
				if (!�ݰ��ұ�(di, target))
				{
					pk::unit_anim(unit0, ����_����_����, { di }, pk::point(-1, -1), 0, "", 0);
					if (bCri)
						cutin(unit0);
					addTroops(target, di.troops_damage);

					pk::unit@ u = getUnit(di.dst_pos);
					if (u != null && !u.has_skill(Ư��_ȣ��))
					{
						if (u.member[0] >= 0 && u.member[0] < ����_�� && pk::rand_bool(����_�λ�_Ȯ��))
							injury(pk::get_person(u.member[0]));
						if (u.member[1] >= 0 && u.member[1] < ����_�� && pk::rand_bool(����_�λ�_Ȯ��))
							injury(pk::get_person(u.member[1]));
						if (u.member[2] >= 0 && u.member[2] < ����_�� && pk::rand_bool(����_�λ�_Ȯ��))
							injury(pk::get_person(u.member[2]));
					}
					bool re=update(unit0, dst_pos, { di }, ũ��Ƽ��_���Ÿ�,bCri);
					re=updateAfter(unit0, target);
					if (re && ����(unit0))
					{
						pk::unit_anim(unit0, ����_����_����, { di }, pk::point(-1, -1), 0, "", 0);
						if (bCri)
							cutin(unit0);
						addTroops(target, di.troops_damage);

						@u = getUnit(di.dst_pos);
						if (u != null && !u.has_skill(Ư��_ȣ��))
						{
							if (u.member[0] >= 0 && u.member[0] < ����_�� && pk::rand_bool(����_�λ�_Ȯ��))
								injury(pk::get_person(u.member[0]));
							if (u.member[1] >= 0 && u.member[1] < ����_�� && pk::rand_bool(����_�λ�_Ȯ��))
								injury(pk::get_person(u.member[1]));
							if (u.member[2] >= 0 && u.member[2] < ����_�� && pk::rand_bool(����_�λ�_Ȯ��))
								injury(pk::get_person(u.member[2]));
						}
						update(unit0, dst_pos, { di }, ũ��Ƽ��_���Ÿ�,bCri);
						updateAfter(unit0, target);
					}
				}
			}
			update(unit0, target, dst_pos, dst_pos);
		}

		//���뺴
		bool ����Handler(pk::point dst_pos)
		{
			execute����(_unit, dst_pos);
			return true;
		}
		bool IsVisible��ȭ��()
		{
			return ��ü_����_���_�׽�Ʈ || isSkill(_unit, Ư������_�뺴_���뺴);
		}
		string Get��ȭ��Text()
		{
			return pk::encode("��ȭ��");
		}
		string Get��ȭ��Desc()
		{
			return pk::encode("ȭ�� �����Դϴ�.");
		}
		pk::array<pk::point_int> GetTargets��ȭ��()
		{
			pk::array<pk::point_int> targets;

			pk::force@ f = pk::get_force(_unit.get_force_id());

			auto range = pk::range(_src_pos, 2, pk::has_tech(f, �ⱳ_����) ? 3 : 2);
			for (int i = 0; i < range.length; i++)
			{
				pk::hex_object@ obj = pk::get_hex_object(range[i]);
				if (obj == null)
					continue;
				if (_force != null && _force.get_id() == obj.get_force_id())
					continue;
				if(!checkHex�뺴(_unit,range[i]))
					continue;

				targets.insertLast(pk::point_int(range[i], 0));
			}
			return targets;
		}
		int GetChance��ȭ��(pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return 0;

			return callback202(_unit, dst_pos, target, ����_����);
		}

		void execute��ȭ��(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			int nTactics = callback202(unit0, dst_pos, target, ����_����);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), ����_����, ũ��Ƽ��_���Ÿ�);
			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, ����_����_Ȱ����, bCri);
			}
			else
			{
				array<pk::damage_info> dis;
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, ����_����, dst_pos, 0, bCri ? 1 : 0, false);

				if (!�ݰ��ұ�(di, target))
				{
					dis.insertLast(di);

					for (int i = 0; i < 6; i++)
					{
						pk::point pt = pk::get_neighbor_pos(dst_pos, i, 1);
						pk::hex_object@ obj = pk::get_hex_object(pt);
						if (obj == null)
							continue;
						if (unit0.has_skill(Ư��_�ý�) && !pk::is_enemy(unit0, obj))
							continue;

						pk::damage_info di2;
						di2.src_pos = unit0.get_pos();
						di2.dst_pos = pt;

						callback209(di2, unit0, ����_����, pt, 0, bCri ? 1 : 0, false);
						dis.insertLast(di2);
					}
					pk::unit_anim(unit0, ����_����_����, dis, pk::point(-1), 0, getString("��ȭ��"), 0);
					if (bCri) 
						cutin(unit0);
						
					for (int i = 0; i < dis.length; i++)
					{
						pk::damage_info di = dis[i];
						pk::hex_object@ u = pk::get_hex_object(di.dst_pos);
						if (u == null)
							continue;
						addTroops(u, di);
						updateAfter(unit0, u);
						if (pk::rand_bool(��ȭ��_ȭ��_Ȯ��)) 
							pk::create_fire(u.get_pos(), pk::rand(3) + 1, unit0, false);
					}
					bool re=update(unit0, dst_pos, dis, ũ��Ƽ��_���Ÿ�,bCri);
					if (re && ����(unit0))
					{
						pk::unit_anim(unit0, ����_����_����, dis, pk::point(-1), 0, getString("��ȭ��"), 0);
						if (bCri)
							cutin(unit0);

						for (int i = 0; i < dis.length; i++)
						{
							pk::damage_info di = dis[i];
							pk::hex_object@ u = pk::get_hex_object(di.dst_pos);
							if (u == null)
								continue;
							addTroops(u, di);
							updateAfter(unit0, u);
							if (pk::rand_bool(��ȭ��_ȭ��_Ȯ��))
								pk::create_fire(u.get_pos(), pk::rand(3) + 1, unit0, false);
						}
						update(unit0, dst_pos, dis, ũ��Ƽ��_���Ÿ�, bCri);
					}
				}
			}
			update(unit0, target, dst_pos, dst_pos);
		}

		//���뺴
		bool ��ȭ��Handler(pk::point dst_pos)
		{
			execute��ȭ��(_unit, dst_pos);
			return true;
		}
		bool IsVisible����()
		{
			return ��ü_����_���_�׽�Ʈ || isSkill(_unit, Ư������_�뺴_���踸��);
		}
		string Get����Text()
		{
			return pk::encode("����");
		}
		string Get����Desc()
		{
			return pk::encode("������������ ��Ȥ ȥ���� �����մϴ�.");
		}
		pk::array<pk::point_int> GetTargets����()
		{
			pk::array<pk::point_int> targets;

			pk::force@ f = pk::get_force(_unit.get_force_id());

			auto range = pk::range(_src_pos, 1,1);
			for (int i = 0; i < range.length; i++)
			{
				pk::hex_object@ obj = pk::get_hex_object(range[i]);
				if (obj == null)
					continue;
				if (_force != null && _force.get_id() == obj.get_force_id())
					continue;

				targets.insertLast(pk::point_int(range[i], 0));
			}
			return targets;

		}
		int GetChance����(pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return 0;

			return callback202(_unit, dst_pos, target, ����_ȭ��);
		}
		void execute����(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			int nTactics = callback202(unit0, dst_pos, target, ����_ȭ��);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), ����_ȭ��, ũ��Ƽ��_���Ÿ�);


			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, ����_����_��������, bCri);
			}
			else
			{
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, ����_ȭ��, dst_pos, 0, bCri ? 1 : 0, false);
				if (!�ݰ��ұ�(di, target))
				{
					pk::unit_anim(unit0, ����_����_��������, { di }, dst_pos, 0, getString("����"), 0);
					if (bCri)
						cutin(unit0);

					addTroops(target, di);
					updateAfter(unit0, target);
					pk::unit@ u = pk::is_valid_pos(target.get_pos()) ? getUnit(target.get_pos()) : null;
					if (u != null && pk::rand_bool(����_ȥ��_Ȯ��))
						updateChaos(u, unit0);

					bool re=update(unit0, dst_pos, { di }, ũ��Ƽ��_����, bCri);
					if (re && ����(unit0))
					{
						pk::unit_anim(unit0, ����_����_��������, { di }, dst_pos, 0, getString("����"), 0);
						if (bCri)
							cutin(unit0);

						addTroops(target, di);
						updateAfter(unit0, target);
						pk::unit@ u = pk::is_valid_pos(target.get_pos()) ? getUnit(target.get_pos()) : null;
						if (u != null && pk::rand_bool(����_ȥ��_Ȯ��))
							updateChaos(u, unit0);

						update(unit0, dst_pos, { di }, ũ��Ƽ��_����, bCri);
					}
				}
			}

			update(unit0, target, dst_pos, dst_pos);
			return;
		}

		//���踸��
		bool ����Handler(pk::point dst_pos)
		{
			execute����(_unit, dst_pos);
			return true;
		}

		bool IsVisible��ǳ��()
		{
			return ��ü_����_���_�׽�Ʈ || isSkill(_unit, Ư������_�뺴_��������);
		}
		string Get��ǳ��Text()
		{
			return pk::encode("��ǳ��");
		}
		string Get��ǳ��Desc()
		{
			return pk::encode("���� 2ĭ ������ ���� ��� ����մϴ�.");
		}
		pk::array<pk::point_int> GetTargets��ǳ��()
		{
			return GetTargets��ȭ��();
		}
		int GetChance��ǳ��(pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return 0;

			return callback202(_unit, dst_pos, target, ����_����);
		}
		
		void execute��ǳ��(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;


			int nTactics = callback202(unit0, dst_pos, target, ����_����);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), ����_����, ũ��Ƽ��_���Ÿ�);

			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, ����_����_Ȱ����, bCri);
			}
			else
			{

				array<pk::damage_info> dis;
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, ����_����, dst_pos, 0, bCri ? 1 : 0, false);

				if (!�ݰ��ұ�(di, target))
				{
					dis.insertLast(di);

					array<pk::point> range = pk::range(dst_pos, 1, 2);
					for (int i = 0; i < range.length; i++)
					{
						pk::point pt = range[i];
						if (pk::get_hex_object(pt) != null && pk::rand_bool(��ǳ��_Ȯ��))
						{
							pk::damage_info di2;
							di2.src_pos = unit0.get_pos();
							di2.dst_pos = pt;
							callback209(di2, unit0, ����_����, pt, 0, bCri ? 1 : 0, false);
							dis.insertLast(di2);
						}
					}
					pk::unit_anim(unit0, ����_����_����, dis, dst_pos, 0);
					if (bCri)
						cutin(unit0);


					for (int i = 0; i < dis.length; i++)
					{
						pk::damage_info di = dis[i];
						pk::hex_object@ obj = getUnit(di.dst_pos);
						if (obj == null)
							continue;
						if (unit0.has_skill(Ư��_�ý�) && unit0.get_force_id() == obj.get_force_id())
							continue;
						if (unit0.get_id() == obj.get_id())
							continue;

						addTroops(obj, di);
						updateAfter(unit0, obj);
					}
					bool re=update(unit0, dst_pos, dis, ũ��Ƽ��_���Ÿ�, bCri);
					if (re && ����(unit0))
					{
						pk::unit_anim(unit0, ����_����_����, dis, dst_pos, 0);
						if (bCri)
							cutin(unit0);

						for (int i = 0; i < dis.length; i++)
						{
							pk::damage_info di = dis[i];
							pk::hex_object@ obj = getUnit(di.dst_pos);
							if (obj == null)
								continue;
							if (unit0.has_skill(Ư��_�ý�) && unit0.get_force_id() == obj.get_force_id())
								continue;
							if (unit0.get_id() == obj.get_id())
								continue;

							addTroops(obj, di);
							updateAfter(unit0, obj);
						}
						update(unit0, dst_pos, dis, ũ��Ƽ��_���Ÿ�, bCri);
					}
				}

			}

			update(unit0, target, dst_pos, dst_pos);
		}

		//��������
		bool ��ǳ��Handler(pk::point dst_pos)
		{
			execute��ǳ��(_unit, dst_pos);
			return true;
		}

		bool IsVisible�س���÷()
		{
			return ��ü_����_���_�׽�Ʈ || isSkill(_unit, Ư������_â��_���̺�);
		}
		string Get�س���÷Text()
		{
			return pk::encode("�س���÷");
		}
		string Get�س���÷Desc()
		{
			return pk::encode("���� 2ĭ ���� ����÷�� ����� �� �ֽ��ϴ�.");
		}
		pk::array<pk::point_int> GetTargets�س���÷()
		{
			pk::array<pk::point_int> targets;
			pk::force@ f = pk::get_force(_unit.get_force_id());
			auto range = pk::range(_src_pos, 1, 2);
			for (int i = 0; i < range.length; i++)
			{
				pk::hex_object@ obj = pk::get_hex_object(range[i]);
				if (obj == null)
					continue;
				if (_force != null && _force.get_id() == obj.get_force_id())
					continue;

				//�߰��� �ǹ��ִ°��
				int dist = pk::get_distance(_src_pos, range[i]);
				if (dist == 2) 
				{
					pk::point ptCenter;
					ptCenter.x = (_src_pos.x + range[i].x) * 0.5;
					ptCenter.y = (_src_pos.y + range[i].y) * 0.5;
					pk::hex_object@ obj = pk::get_hex_object(ptCenter);
					if(obj!=null && obj.get_type_id()!=11)
						continue;
				}

				if(!checkHexâ��(range[i]))
					continue;
				targets.insertLast(pk::point_int(range[i], 0));
			}
			return targets;

		}
		int GetChance�س���÷(pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return 0;

			return callback202(_unit, dst_pos, target, ����_����÷);
		}

		void execute�س���÷(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			int nTactics = callback202(unit0, dst_pos, target, ����_����÷);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), ����_����÷, ũ��Ƽ��_����);


			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, ����_����_��������, bCri);
			}
			else
			{
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, ����_����÷, dst_pos, 0, bCri ? 1 : 0, false);
				if (!�ݰ��ұ�(di, target))
				{
					pk::unit_anim(unit0, ����_����_����÷, { di }, dst_pos, 0, getString("�س���÷"), 0);
					if (bCri)
						cutin(unit0);

					addTroops(target, di);
					updateAfter(unit0, target);


					pk::unit@ u = getUnit(di.dst_pos);
					if (u != null && prev_callback_221(unit0, u, bCri) > 0)
						updateChaos(u, unit0);
					bool re=update(unit0, dst_pos, { di }, ũ��Ƽ��_����, bCri);
					if (re && ����(unit0))
					{
						pk::unit_anim(unit0, ����_����_����÷, { di }, dst_pos, 0, getString("�س���÷"), 0);
						if (bCri)
							cutin(unit0);

						addTroops(target, di);
						updateAfter(unit0, target);


						pk::unit@ u = getUnit(di.dst_pos);
						if (u != null && prev_callback_221(unit0, u, bCri) > 0)
							updateChaos(u, unit0);
						update(unit0, dst_pos, { di }, ũ��Ƽ��_����, bCri);
					}
				}

			}

			update(unit0, target, dst_pos, dst_pos);
		}

		//���̺�
		bool �س���÷Handler(pk::point dst_pos) //���̺�
		{
			execute�س���÷(_unit, dst_pos);
			return true;
		}


		bool IsVisible������()
		{
			return ��ü_����_���_�׽�Ʈ || isSkill(_unit, Ư������_â��_��ػ�);
		}
		string Get������Text()
		{
			return pk::encode("������");
		}
		string Get������Desc()
		{
			return pk::encode("�̴�÷�� ����ϸ� ����Ȯ���� ȥ��ȿ���� �߻��մϴ�.");
		}
		pk::array<pk::point_int> GetTargets������()
		{
			pk::array<pk::point_int> targets;
			pk::force@ f = pk::get_force(_unit.get_force_id());
			auto range = pk::range(_src_pos, 1, 1);
			for (int i = 0; i < range.length; i++)
			{
				pk::hex_object@ obj = pk::get_hex_object(range[i]);
				if (obj == null)
					continue;
				if (_force != null && _force.get_id() == obj.get_force_id())
					continue;
				if(!checkHexâ��(range[i]))
					continue;
				targets.insertLast(pk::point_int(range[i], 0));
			}
			return targets;

		}
		int GetChance������(pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return 0;

			return callback202(_unit, dst_pos, target, ����_�̴�÷);
		}

		void execute������(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			pk::point dst_pos2 = dst_pos;

			int nTactics = callback202(unit0, dst_pos, target, ����_�̴�÷);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), ����_�̴�÷, ũ��Ƽ��_����);
			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, 1, bCri);
			}
			else
			{
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, ����_�̴�÷, dst_pos, 0, bCri ? 1 : 0, false);
				if (!�ݰ��ұ�(di, target))
				{
					int dir = pk::get_direction(unit0.get_pos(), dst_pos);
					pk::point ptA = pk::get_neighbor_pos(dst_pos, dir, 2);
					di.src_move_pos = unit0.get_pos();
					di.dst_move_pos = MovePoint(dst_pos, ptA);
					pk::unit_anim(unit0, ����_����_�̴�÷, { di }, dst_pos, 0, getString("������"), 0);
					if (bCri)
						cutin(unit0);

					pk::unit@ u = getUnit(di.dst_pos);
					if (u != null && (prev_callback_221(unit0, u, bCri) > 0))
					{
						updateChaos(u, unit0);
						pk::move(u, { MovePoint(dst_pos, ptA) });
					}
					if (ptA.x != di.dst_move_pos.x || ptA.y != di.dst_move_pos.y)
					{
						int dir2 = pk::get_direction(di.dst_move_pos, ptA);
						int dist2 = pk::get_distance(di.dst_move_pos, ptA);
						for (int i = 0; i < dist2; i++)
						{
							pk::point pt = pk::get_neighbor_pos(di.dst_move_pos, dir2, i);
							pk::unit@ ptu = pk::get_unit(pt);
							if (ptu != null && pk::is_enemy(unit0, ptu) && (prev_callback_221(unit0, ptu, bCri) > 0))
								updateChaos(ptu, unit0);
						}
					}

					addTroops(target, di);
					updateAfter(unit0, target);
					bool re=update(unit0, dst_pos, { di }, ũ��Ƽ��_����, bCri);
					pk::point dst_pos2 = di.dst_move_pos;
					if (re && ����(unit0))
					{
						pk::point ptA = pk::get_neighbor_pos(dst_pos2, dir, 2);
						di.src_move_pos = unit0.get_pos();
						di.dst_move_pos = MovePoint(dst_pos2, ptA);
						pk::unit_anim(unit0, ����_����_�̴�÷, { di }, dst_pos2, 0, getString("������"), 0);
						if (bCri)
							cutin(unit0);

						pk::unit@ u = getUnit(dst_pos2);
						if (u != null && (prev_callback_221(unit0, u, bCri) > 0))
						{
							updateChaos(u, unit0);
							pk::move(u, { MovePoint(dst_pos, ptA) });
						}
						if (ptA.x != di.dst_move_pos.x || ptA.y != di.dst_move_pos.y)
						{
							int dir2 = pk::get_direction(di.dst_move_pos, ptA);
							int dist2 = pk::get_distance(di.dst_move_pos, ptA);
							for (int i = 0; i < dist2; i++)
							{
								pk::point pt = pk::get_neighbor_pos(di.dst_move_pos, dir2, i);
								pk::unit@ ptu = pk::get_unit(pt);
								if (ptu != null && pk::is_enemy(unit0, ptu) && (prev_callback_221(unit0, ptu, bCri) > 0))
									updateChaos(ptu, unit0);
							}
						}


						addTroops(target, di);
						updateAfter(unit0, target);
						update(unit0, dst_pos2, { di }, ũ��Ƽ��_����, bCri);
						dst_pos2 = di.dst_move_pos;

					}
				}

			}//bTatics
			update(unit0, target, dst_pos, dst_pos2);
		}
		//��ػ�
		bool ������Handler(pk::point dst_pos)
		{
			execute������(_unit, dst_pos);
			return true;
		}

		bool IsVisibleȭ����()
		{
			return ��ü_����_���_�׽�Ʈ || isSkill(_unit, Ư������_â��_�����);
		}
		string Getȭ����Text()
		{
			return pk::encode("ȭ����");
		}
		string Getȭ����Desc()
		{
			return pk::encode("3ĭ���� �̴�÷�� ����ϰ� ����Ȯ���� ȭ�谡 �߻��մϴ�.");
		}
		pk::array<pk::point_int> GetTargetsȭ����()
		{
			return GetTargets������();
		}
		int GetChanceȭ����(pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return 0;

			return callback202(_unit, dst_pos, target, ����_�̴�÷);
		}

		void executeȭ����(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			int nTactics = callback202(unit0, dst_pos, target, ����_�̴�÷);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), ����_�̴�÷, ũ��Ƽ��_����);
			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, ����_����_��������, bCri);
			}
			else
			{
				pk::damage_info di0;
				di0.src_pos = unit0.get_pos();
				di0.dst_pos = dst_pos;
				callback209(di0, unit0, ����_�̴�÷, dst_pos, 0, bCri ? 1 : 0, false);
				if (!�ݰ��ұ�(di0, target))
				{
					array<pk::damage_info> dis;
					int dir = pk::get_direction(unit0.get_pos(), dst_pos);
					for (int i = 0; i < 3; i++)
					{
						pk::point pt = pk::get_neighbor_pos(unit0.get_pos(), dir, i + 1);
						pk::hex_object@ obj = pk::get_hex_object(pt);
						if (obj == null)
							continue;
						if (!pk::is_enemy(unit0, obj))
							continue;
						if (!checkHexâ��(pt))
							continue;

						pk::damage_info di2;
						di2.src_pos = unit0.get_pos();
						di2.dst_pos = pt;

						callback209(di2, unit0, ����_�̴�÷, pt, 0, bCri ? 1 : 0, false);
						dis.insertLast(di2);
					}
					pk::unit_anim(unit0, ����_����_�̴�÷, dis, dst_pos, 0, getString("ȭ����"), 0);
					if (bCri)
						cutin(unit0);

					for (int i = 0; i < dis.length; i++)
					{
						pk::damage_info di = dis[i];
						pk::hex_object@ hex = pk::get_hex_object(di.dst_pos);
						if (hex == null)
							continue;
						addTroops(hex, di);
						if (pk::rand_bool(ȭ����_ȭ��_Ȯ��))
							pk::create_fire(hex.get_pos(), pk::rand(3) + 1, unit0, false);
						updateAfter(unit0, hex);
					}
					bool re=update(unit0, dst_pos, dis, ũ��Ƽ��_����, bCri);
					if (re && ����(unit0))
					{
						pk::unit_anim(unit0, ����_����_�̴�÷, dis, dst_pos, 0, getString("ȭ����"), 0);
						if (bCri)
							cutin(unit0);

						for (int i = 0; i < dis.length; i++)
						{
							pk::damage_info di = dis[i];
							pk::hex_object@ hex = pk::get_hex_object(di.dst_pos);
							if (hex == null)
								continue;
							addTroops(hex, di);
							if (pk::rand_bool(ȭ����_ȭ��_Ȯ��))
								pk::create_fire(hex.get_pos(), pk::rand(3) + 1, unit0, false);
							updateAfter(unit0, hex);
						}
						update(unit0, dst_pos, dis, ũ��Ƽ��_����, bCri);
					}
				}
			}
			update(unit0, target, dst_pos, dst_pos);
		}

		//�����
		bool ȭ����Handler(pk::point dst_pos)
		{
			executeȭ����(_unit, dst_pos);
			return true;
		}

		bool IsVisible��ô()
		{
			return ��ü_����_���_�׽�Ʈ || isSkill(_unit, Ư������_�غ�_�ܾ纴);
		}
		string Get��ôText()
		{
			return pk::encode("��ô");
		}
		string Get��ôDesc()
		{
			return pk::encode("ȭ�谡 ����Ȯ���� �߻��ϴ� ��ǳ�� ����մϴ�.");
		}
		pk::array<pk::point_int> GetTargets��ô()
		{
			pk::array<pk::point_int> targets;
			pk::force@ f = pk::get_force(_unit.get_force_id());
			auto range = pk::range(_src_pos, 1, 1);
			for (int i = 0; i < range.length; i++)
			{
				pk::hex_object@ obj = pk::get_hex_object(range[i]);
				if (obj == null)
					continue;
				if (_force != null && _force.get_id() == obj.get_force_id())
					continue;
				if(!checkHex�غ�(range[i]))
					continue;

				targets.insertLast(pk::point_int(range[i], 0));
			}
			return targets;

		}
		int GetChance��ô(pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return 0;

			return callback202(_unit, dst_pos, target, ����_��ǳ);
		}

		void execute��ô(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;


			int nTactics = callback202(unit0, dst_pos, target, ����_��ǳ);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), ����_��ǳ, ũ��Ƽ��_����);
			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, ����_����_��������, bCri);
			}
			else
			{

				pk::damage_info di0;
				di0.src_pos = unit0.get_pos();
				di0.dst_pos = dst_pos;
				callback209(di0, unit0, ����_��ǳ, dst_pos, 0, bCri ? 1 : 0, false);
				if (!�ݰ��ұ�(di0, target))
				{
					array<pk::damage_info> dis;
					for (int i = 0; i < 6; i++)
					{
						pk::point pt = pk::get_neighbor_pos(unit0.get_pos(), i, 1);
						pk::hex_object@ obj = pk::get_hex_object(pt);
						if (obj == null)
							continue;
						if (!pk::is_enemy(unit0, obj))
							continue;

						pk::damage_info di2;
						di2.src_pos = unit0.get_pos();
						di2.dst_pos = pt;

						callback209(di2, unit0, ����_��ǳ, pt, 0, bCri ? 1 : 0, false);
						dis.insertLast(di2);
					}
					pk::unit_anim(unit0, ����_����_��ǳ, dis, dst_pos, 0, getString("��ô"), 0);
					if (bCri)
						cutin(unit0);

					for (int i = 0; i < dis.length; i++)
					{
						pk::damage_info di = dis[i];
						pk::hex_object@ hex = pk::get_hex_object(di.dst_pos);
						if (hex == null)
							continue;
						addTroops(hex, di);
						if (pk::rand_bool(��ô_ȭ��_Ȯ��))
							pk::create_fire(hex.get_pos(), pk::rand(3) + 1, unit0, false);
						updateAfter(unit0, hex);
					}
					bool re=update(unit0, dst_pos, dis, ũ��Ƽ��_����, bCri);
					if (re && ����(unit0))
					{
						pk::unit_anim(unit0, ����_����_��ǳ, dis, dst_pos, 0, getString("��ô"), 0);
						if (bCri)
							cutin(unit0);

						for (int i = 0; i < dis.length; i++)
						{
							pk::damage_info di = dis[i];
							pk::hex_object@ hex = pk::get_hex_object(di.dst_pos);
							if (hex == null)
								continue;
							addTroops(hex, di);
							if (pk::rand_bool(��ô_ȭ��_Ȯ��))
								pk::create_fire(hex.get_pos(), pk::rand(3) + 1, unit0, false);
							updateAfter(unit0, hex);
						}
						update(unit0, dst_pos, dis, ũ��Ƽ��_����, bCri);
					}
				}
			}

			update(unit0, target, dst_pos, dst_pos);
		}
		//�ܾ纴
		bool ��ôHandler(pk::point dst_pos)
		{
			execute��ô(_unit, dst_pos);
			return true;
		}


		bool IsVisible����()
		{
			return ��ü_����_���_�׽�Ʈ || isSkill(_unit, Ư������_�غ�_������);
		}
		string Get����Text()
		{
			return pk::encode("����");
		}
		string Get����Desc()
		{
			return pk::encode("ȥ���� ����Ȯ���� �߻��ϴ� Ⱦġ�� ����մϴ�.");
		}
		pk::array<pk::point_int> GetTargets����()
		{
			return GetTargets��ô();
		}
		int GetChance����(pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return 0;

			return callback202(_unit, dst_pos, target, ����_Ⱦġ);
		}

		void execute����(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			int nTactics = callback202(unit0, dst_pos, target, ����_Ⱦġ);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), ����_Ⱦġ, ũ��Ƽ��_����);

			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, ����_����_��������, bCri);
			}
			else
			{
				array<pk::damage_info> dis;
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, ����_Ⱦġ, dst_pos, 0, bCri ? 1 : 0, false);
				if (!�ݰ��ұ�(di, target))
				{
					dis.insertLast(di);

					array<pk::point> arr = getȾġpos(unit0.get_pos(), dst_pos);
					pk::unit@ u0 = getUnit(arr[0]);
					if (u0 != null && pk::is_enemy(unit0, u0))
					{
						pk::damage_info di1;
						di1.src_pos = unit0.get_pos();
						di1.dst_pos = arr[0];
						callback209(di1, unit0, ����_Ⱦġ, arr[0], 0, bCri ? 1 : 0, false);
						dis.insertLast(di1);
					}
					pk::unit@ u1 = getUnit(arr[1]);
					if (u1 != null && pk::is_enemy(unit0, u1))
					{
						pk::damage_info di1;
						di1.src_pos = unit0.get_pos();
						di1.dst_pos = arr[1];
						callback209(di1, unit0, ����_Ⱦġ, arr[1], 0, bCri ? 1 : 0, false);
						dis.insertLast(di1);
					}

					pk::unit_anim(unit0, ����_����_Ⱦġ, { di }, dst_pos, 0, getString("����"), 0);
					if (bCri)
						cutin(unit0);

					for (int i = 0; i < dis.length; i++)
					{
						pk::damage_info ddi = dis[i];
						pk::unit@ u = getUnit(ddi.dst_pos);
						if (u == null)
							continue;

						addTroops(u, ddi);
						updateAfter(unit0, u);
						pk::unit@ uu = getUnit(ddi.dst_pos);
						if (uu != null && prev_callback_221(unit0, u, bCri) > 0 && pk::rand_bool(����_ȥ��_Ȯ��))
							updateChaos(uu, unit0);
					}
					bool re=update(unit0, dst_pos, dis, ũ��Ƽ��_����, bCri);
					if (re && ����(unit0))
					{
						pk::unit_anim(unit0, ����_����_Ⱦġ, { di }, dst_pos, 0, getString("����"), 0);
						if (bCri)
							cutin(unit0);

						for (int i = 0; i < dis.length; i++)
						{
							pk::damage_info ddi = dis[i];
							pk::unit@ u = getUnit(ddi.dst_pos);
							if (u == null)
								continue;

							addTroops(u, ddi);
							updateAfter(unit0, u);
							pk::unit@ uu = getUnit(ddi.dst_pos);
							if (uu != null && prev_callback_221(unit0, u, bCri) > 0 && pk::rand_bool(����_ȥ��_Ȯ��))
								updateChaos(uu, unit0);
						}
					}
					update(unit0, dst_pos, dis, ũ��Ƽ��_����, bCri);
				}
			}
			update(unit0, target, dst_pos, dst_pos);
		}

		//������
		bool ����Handler(pk::point dst_pos)
		{
			execute����(_unit, dst_pos);
			return true;
		}

		
		bool IsVisible����()
		{
			return ��ü_����_���_�׽�Ʈ || isSkill(_unit, Ư������_�⺴_����ö��);
		}
		string Get����Text()
		{
			return pk::encode("����");
		}
		string Get����Desc()
		{
			return pk::encode("�̵����ݽ� �̵��Ÿ���ŭ ���ݷ��� �����մϴ�.");
		}
		pk::array<pk::point_int> GetTargets����()
		{
			pk::array<pk::point_int> targets;

			pk::force@ f = pk::get_force(_unit.get_force_id());

			auto range = pk::range(_src_pos, 1, 1);
			for (int i = 0; i < range.length; i++)
			{
				pk::hex_object@ obj = pk::get_hex_object(range[i]);
				if (obj == null)
					continue;
				if (_force != null && _force.get_id() == obj.get_force_id())
					continue;
				if(!checkHex�⺴(range[i]))
					continue;
				targets.insertLast(pk::point_int(range[i], 0));
			}
			return targets;

		}
		int GetChance����(pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return 0;

			return callback202(_unit, dst_pos, target, ����_����);
		}

		void execute����(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			pk::point dst_pos2 = dst_pos;
			int nTactics = callback202(unit0, dst_pos, target, ����_����);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), ����_����, ũ��Ƽ��_����);


			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, ����_����_��������, bCri);
			}
			else
			{
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, ����_����, dst_pos, 0, bCri ? 1 : 0, false);

				int dist = pk::min(����_����_�ִ�����Ÿ�, pk::get_distance(unit0.get_pos(), _src_pos0));
				//pk::printf("dist {} x{},y{},x{},y{}\n", dist, unit0.get_pos().x, unit0.get_pos().y, _src_pos2.x, _src_pos2.y);
				di.troops_damage = di.troops_damage + float(di.troops_damage) * float(dist) * float(����_����_������) / 100.0;

				if (!�ݰ��ұ�(di, target))
				{
					int dir = pk::get_direction(unit0.get_pos(), dst_pos);
					pk::point ptA = pk::get_neighbor_pos(unit0.get_pos(), dir, 2);
					pk::point ptT = pk::get_neighbor_pos(dst_pos, dir, 2);
					di.src_move_pos = MoveThrough(unit0.get_pos(), ptA);
					//di.dst_move_pos = MovePoint(dst_pos, ptT);

					pk::unit_anim(unit0, ����_����_����, { di }, dst_pos, 0, getString("����"), 0);
					if (bCri)
						cutin(unit0);

					pk::unit@ u = getUnit(di.dst_pos);
					if (u != null)
					{
						//pk::move(u, { MovePoint(dst_pos, ptT) });
						if (unit0.has_skill(Ư��_����) && prev_callback_222(unit0, u) > 0)
							updateChaos(u, unit0);
					}

					pk::move(unit0, { MoveThrough(unit0.get_pos(), ptA) });

					addTroops(target, di);
					updateAfter(unit0, target);
					bool re=update(unit0, dst_pos, { di }, ũ��Ƽ��_����, bCri);
					//dst_pos2 = di.dst_move_pos;
					if (re && ����(unit0))
					{
						dir = pk::get_direction(unit0.get_pos(), dst_pos);
						pk::point ptA = pk::get_neighbor_pos(unit0.get_pos(), dir, 2);
						pk::point ptT = pk::get_neighbor_pos(dst_pos, dir, 2);
						di.src_move_pos = MoveThrough(unit0.get_pos(), ptA);
						//di.dst_move_pos = MovePoint(dst_pos, ptT);

						pk::unit_anim(unit0, ����_����_����, { di }, dst_pos, 0, getString("����"), 0);
						if (bCri)
							cutin(unit0);

						pk::unit@ u = getUnit(di.dst_pos);
						if (u != null)
						{
							//pk::move(u, { MovePoint(dst_pos, ptT) });
							if (unit0.has_skill(Ư��_����) && prev_callback_222(unit0, u) > 0)
								updateChaos(u, unit0);
						}

						pk::move(unit0, { MoveThrough(unit0.get_pos(), ptA) });

						addTroops(target, di);
						updateAfter(unit0, target);
						update(unit0, dst_pos, { di }, ũ��Ƽ��_����, bCri);
					}
				}
			}

			update(unit0, target, dst_pos, dst_pos2);
		}

		//����ö��
		bool ����Handler(pk::point dst_pos)
		{
			execute����(_unit, dst_pos);
			return true;
		}


		bool IsVisible����()
		{
			return ��ü_����_���_�׽�Ʈ || isSkill(_unit, Ư������_�⺴_ȣǥ��);
		}
		string Get����Text()
		{
			return pk::encode("����");
		}
		string Get����Desc()
		{
			return pk::encode("���� Ⱦġ�� ����մϴ�.");
		}
		pk::array<pk::point_int> GetTargets����()
		{
			return GetTargets����();

		}
		int GetChance����(pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return 0;

			return callback202(_unit, dst_pos, target, ����_����);
		}

		void execute����(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			int nTactics = callback202(unit0, dst_pos, target, ����_����);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), ����_����, ũ��Ƽ��_����);


			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, ����_����_��������, bCri);
			}
			else
			{
				array<pk::damage_info> dis;
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, ����_����, dst_pos, 0, bCri ? 1 : 0, false);
				dis.insertLast(di);
				if (!�ݰ��ұ�(di, target))
				{
					array<pk::point> arr = getȾġpos(unit0.get_pos(), dst_pos);
					pk::unit@ u0 = getUnit(arr[0]);
					if (u0 != null && pk::is_enemy(unit0, u0))
					{
						pk::damage_info di1;
						di1.src_pos = unit0.get_pos();
						di1.dst_pos = arr[0];
						callback209(di1, unit0, ����_����, arr[0], 0, bCri ? 1 : 0, false);
						dis.insertLast(di1);
					}
					pk::unit@ u1 = getUnit(arr[1]);
					if (u1 != null && pk::is_enemy(unit0, u1))
					{
						pk::damage_info di1;
						di1.src_pos = unit0.get_pos();
						di1.dst_pos = arr[1];
						callback209(di1, unit0, ����_����, arr[1], 0, bCri ? 1 : 0, false);
						dis.insertLast(di1);
					}

					pk::unit_anim(unit0, ����_����_Ⱦġ, { di }, dst_pos, 0, getString("����"), 0);
					if (bCri)
						cutin(unit0);

					for (int i = 0; i < dis.length; i++)
					{
						pk::damage_info ddi = dis[i];
						pk::unit@ u = getUnit(ddi.dst_pos);
						if (u == null)
							continue;

						addTroops(u, ddi);
						updateAfter(unit0, u);
						pk::unit@ uu = getUnit(ddi.dst_pos);
						if (uu != null)
						{
							if (i == 0)
							{
								if (unit0.has_skill(Ư��_����) && prev_callback_222(unit0, uu) > 0)
									updateChaos(uu, unit0);
							}
							else
							{
								if (unit0.has_skill(Ư��_����) && prev_callback_222(unit0, uu) > 0 && pk::rand_bool(����_ȥ��_Ȯ��))
									updateChaos(uu, unit0);
							}
						}
					}
					bool re=update(unit0, dst_pos, dis, ũ��Ƽ��_����, bCri);
					if (re && ����(unit0))
					{
						pk::unit_anim(unit0, ����_����_Ⱦġ, { di }, dst_pos, 0, getString("����"), 0);
						if (bCri)
							cutin(unit0);

						for (int i = 0; i < dis.length; i++)
						{
							pk::damage_info ddi = dis[i];
							pk::unit@ u = getUnit(ddi.dst_pos);
							if (u == null)
								continue;

							addTroops(u, ddi);
							updateAfter(unit0, u);
							pk::unit@ uu = getUnit(ddi.dst_pos);
							if (uu != null)
							{
								if (i == 0)
								{
									if (unit0.has_skill(Ư��_����) && prev_callback_222(unit0, uu) > 0)
										updateChaos(uu, unit0);
								}
								else
								{
									if (unit0.has_skill(Ư��_����) && prev_callback_222(unit0, uu) > 0 && pk::rand_bool(����_ȥ��_Ȯ��))
										updateChaos(uu, unit0);
								}
							}
						}
						update(unit0, dst_pos, dis, ũ��Ƽ��_����, bCri);
					}
				}
			}
			update(unit0, target, dst_pos, dst_pos);
		}

		//ȣǥ��
		bool ����Handler(pk::point dst_pos)
		{
			execute����(_unit, dst_pos);
			return true;
		}


		bool IsVisible�鸶��()
		{
			return ��ü_����_���_�׽�Ʈ || isSkill(_unit, Ư������_�⺴_�鸶����);
		}
		string Get�鸶��Text()
		{
			return pk::encode("�鸶��");
		}
		string Get�鸶��Desc()
		{
			return pk::encode("���縦 ����մϴ�.");
		}
		pk::array<pk::point_int> GetTargets�鸶��()
		{
			return GetTargets��ȭ��();

		}
		int GetChance�鸶��(pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return 0;

			return callback202(_unit, dst_pos, target, ����_����);
		}

		void execute�鸶��(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			int nTactics = callback202(unit0, dst_pos, target, ����_����);
			bool bTactics = pk::rand_bool(nTactics);
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), ����_����, ũ��Ƽ��_���Ÿ�);


			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, ����_����_Ȱ����, bCri);
			}
			else
			{
				array<pk::damage_info> dis;
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, ����_����, dst_pos, 0, bCri ? 1 : 0, false);
				dis.insertLast(di);


				if (!�ݰ��ұ�(di, target))
				{
					for (int i = 0; i < 6; i++)
					{
						pk::point pt = pk::get_neighbor_pos(dst_pos, i, 1);
						pk::hex_object@ obj = pk::get_hex_object(pt);
						if (obj == null)
							continue;
						if (unit0.has_skill(Ư��_�ý�) && !pk::is_enemy(unit0, obj))
							continue;


						pk::damage_info di2;
						di2.src_pos = unit0.get_pos();
						di2.dst_pos = pt;

						callback209(di2, unit0, ����_����, pt, 0, bCri ? 1 : 0, false);
						dis.insertLast(di2);
					}
					pk::unit_anim(unit0, ����_����_����, dis, dst_pos, 0, getString("�鸶��"), 0);
					//pk::unit_anim(unit0, ����_����_����, dis, dst_pos, 0, "", 0);
					if (bCri)
						cutin(unit0);

					for (int i = 0; i < dis.length; i++)
					{
						pk::damage_info di = dis[i];
						pk::unit@ obj = getUnit(di.dst_pos);
						if (obj == null)
							continue;
						addTroops(obj, di);
						updateAfter(unit0, obj);
					}

					bool re=update(unit0, dst_pos, dis, ũ��Ƽ��_���Ÿ�, bCri);
					if (re && ����(unit0))
					{
						pk::unit_anim(unit0, ����_����_����, dis, dst_pos, 0, getString("�鸶��"), 0);
						if (bCri)
							cutin(unit0);

						for (int i = 0; i < dis.length; i++)
						{
							pk::damage_info di = dis[i];
							pk::unit@ obj = getUnit(di.dst_pos);
							if (obj == null)
								continue;
							addTroops(obj, di);
							updateAfter(unit0, obj);
						}
						update(unit0, dst_pos, dis, ũ��Ƽ��_���Ÿ�, bCri);
					}
				}
			}

			update(unit0, target, dst_pos, dst_pos);
		}

		//�鸶����
		bool �鸶��Handler(pk::point dst_pos)
		{
			execute�鸶��(_unit, dst_pos);
			return true;
		}

		bool IsVisible����()
		{
			return ��ü_����_���_�׽�Ʈ || isSkill(_unit, Ư������_�⺴_������);
		}
		string Get����Text()
		{
			return pk::encode("����");
		}
		string Get����Desc()
		{
			return pk::encode("�̵����ݽ� �̵��Ÿ���ŭ ������������ �����մϴ�.");
		}
		pk::array<pk::point_int> GetTargets����()
		{
			return GetTargets����();

		}
		int GetChance����(pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return 0;

			int dist = pk::get_distance(_unit.get_pos(), dst_pos) - 1;
			int n = dist * ����_����_������;
			int nTactics = callback202(_unit, dst_pos, target, ����_����);
			return pk::min(100, nTactics + n);
		}


		void execute����(pk::unit@ unit0, pk::point dst_pos)
		{
			pk::hex_object@ target = pk::get_hex_object(dst_pos);
			if (target == null)
				return;

			pk::point dst_pos2 = dst_pos;

			int dist = pk::get_distance(unit0.get_pos(), _src_pos0);
			int n = dist * ����_����_������;

			int nTactics = callback202(unit0, dst_pos, target, ����_����);
			bool bTactics = pk::rand_bool(pk::min(100, nTactics + n));
			bool bCri = callback201(unit0, pk::get_hex_object(dst_pos), ����_����, ũ��Ƽ��_����);

			if (!bTactics)
			{
				attackFail(unit0, target, dst_pos, ����_����_��������, bCri);
			}
			else
			{
				pk::damage_info di;
				di.src_pos = unit0.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, unit0, ����_����, dst_pos, 0, bCri ? 1 : 0, false);

				if (!�ݰ��ұ�(di, target))
				{
					int dir = pk::get_direction(unit0.get_pos(), dst_pos);
					pk::point ptA = pk::get_neighbor_pos(unit0.get_pos(), dir, 2);
					pk::point ptT = pk::get_neighbor_pos(dst_pos, dir, 2);
					di.src_move_pos = MoveThrough(unit0.get_pos(), ptA);
					//di.dst_move_pos = MovePoint(dst_pos, ptT);
					pk::unit_anim(unit0, ����_����_����, { di }, dst_pos, 0, getString("����"), 0);
					if (bCri)
						cutin(unit0);

					pk::unit@ u = getUnit(di.dst_pos);
					if (u != null)
					{
						//pk::move(u, { MovePoint(dst_pos, ptT) });
						if (unit0.has_skill(Ư��_����) && prev_callback_222(unit0, u) > 0)
							updateChaos(u, unit0);
					}
					pk::move(unit0, { MoveThrough(unit0.get_pos(), ptA) });

					addTroops(target, di);
					updateAfter(unit0, target);
					bool re=update(unit0, dst_pos, { di }, ũ��Ƽ��_����, bCri);
					//dst_pos2 = di.dst_move_pos;
					if (re && ����(unit0))
					{
						dir = pk::get_direction(unit0.get_pos(), dst_pos);
						pk::point ptA = pk::get_neighbor_pos(unit0.get_pos(), dir, 2);
						pk::point ptT = pk::get_neighbor_pos(dst_pos, dir, 2);
						di.src_move_pos = MoveThrough(unit0.get_pos(), ptA);
						//di.dst_move_pos = MovePoint(dst_pos, ptT);
						pk::unit_anim(unit0, ����_����_����, { di }, dst_pos, 0, getString("����"), 0);
						if (bCri)
							cutin(unit0);

						pk::unit@ u = getUnit(di.dst_pos);
						if (u != null)
						{
							//pk::move(u, { MovePoint(dst_pos, ptT) });
							if (unit0.has_skill(Ư��_����) && prev_callback_222(unit0, u) > 0)
								updateChaos(u, unit0);
						}
						pk::move(unit0, { MoveThrough(unit0.get_pos(), ptA) });

						addTroops(target, di);
						updateAfter(unit0, target);
						update(unit0, dst_pos, { di }, ũ��Ƽ��_����, bCri);
					}
				}
			}

			update(unit0, target, dst_pos, dst_pos2);
		}
		//������ 
		bool ����Handler(pk::point dst_pos)
		{
			execute����(_unit, dst_pos);
			return true;
		}


		string getString(string str)
		{
			switch (pk::rand(4))
			{
			case 0:
				return pk::encode(pk::format("�̰��� {}��",str));
			case 1:
				return pk::encode(pk::format("{} ���� �����ָ�", str));
			case 2:
				return pk::encode(pk::format("���� ��� {} ������", str));
			case 3:
				return pk::encode(pk::format("{} ���� �¼��� ����", str));
			default:
				break;
			}
			return "";
		}

		array<pk::point> getȾġpos(pk::point spos, pk::point dpos)
		{
			array<pk::point> pts;
			int dir = pk::get_direction(spos, dpos);
			switch (dir)
			{
			case ����_��:
				pts.insertLast(pk::get_neighbor_pos(spos, ����_����, 1));
				pts.insertLast(pk::get_neighbor_pos(spos, ����_����, 1));
				break;
			case ����_����:
				pts.insertLast(pk::get_neighbor_pos(spos, ����_�ϵ�, 1));
				pts.insertLast(pk::get_neighbor_pos(spos, ����_��, 1));
				break;
			case ����_�ϵ�:
				pts.insertLast(pk::get_neighbor_pos(spos, ����_��, 1));
				pts.insertLast(pk::get_neighbor_pos(spos, ����_����, 1));
				break;
			case ����_��:
				pts.insertLast(pk::get_neighbor_pos(spos, ����_�ϼ�, 1));
				pts.insertLast(pk::get_neighbor_pos(spos, ����_�ϵ�, 1));
				break;
			case ����_�ϼ�:
				pts.insertLast(pk::get_neighbor_pos(spos, ����_����, 1));
				pts.insertLast(pk::get_neighbor_pos(spos, ����_��, 1));
				break;
			case ����_����:
				pts.insertLast(pk::get_neighbor_pos(spos, ����_�ϼ�, 1));
				pts.insertLast(pk::get_neighbor_pos(spos, ����_��, 1));
				break;
			default:
				break;
			}
			return pts;
		}

		pk::point MoveThrough(pk::point pos0, pk::point pos)
		{
			if (pk::get_hex_object(pos) != null)
				return pos0;
			else
				return pos;
		}
		pk::point MovePoint(pk::point pos0, pk::point pos)
		{
			int dir = pk::get_direction(pos0, pos);

			pk::point pt0 = pk::get_neighbor_pos(pos0, dir, 1);
			if (pk::get_hex_object(pt0) != null)
				return pos0;
			if (pt0.x == pos.x && pt0.y == pos.y)
			{
				return pt0;
			}
			pk::point pt1 = pk::get_neighbor_pos(pos0, dir, 2);
			if (pk::get_hex_object(pt1) != null)
			{
				return pt0;
			}
			else
			{
				return pt1;
			}


		}
		void Move(pk::unit@ u, pk::point pos)
		{
			int dir = pk::get_direction(u.get_pos(), pos);

			pk::point pt0 = pk::get_neighbor_pos(u.get_pos(), dir, 1);
			if (pk::get_hex_object(pt0) != null)
				return;

			if (pt0.x == pos.x && pt0.y == pos.y)
			{
				pk::set_pos(u,  pt0);
				pk::move(u, { pt0 });
				return;
			}

			pk::point pt1 = pk::get_neighbor_pos(u.get_pos(), dir, 2);
			if (pk::get_hex_object(pt1) != null)
			{
				pk::set_pos(u, pt0);
				pk::move(u, { pt0 });
			}
			else
			{
				pk::set_pos(u, pt1);
				pk::move(u, { pt1 });
			}
				
		}

		int getChaosTime(pk::unit@ u)
		{
			int max = pk::max(u.attr.stat[�δ�ɷ�_���], u.attr.stat[�δ�ɷ�_����]);
			int time = pk::max((1 - (max - 50) / 40.0), 0.0) * 2 + 2;
			return time;
		}
		int getMaxAttackDistance(pk::unit@ u)
		{
			pk::force@ f = pk::get_force(u.get_force_id());
			switch (u.weapon)
			{
			case ����_â:
			case ����_��:
			case ����_����:
				if (pk::has_tech(f, �ⱳ_���) || u.has_skill(Ư��_�鸶))
					return 2;
				return  1;
			case ����_��:
				return pk::has_tech(f, �ⱳ_����) ? 3 : 2;
			default:
				break;
			}
			return 0;
		}

		void updateAssist(pk::unit@ attacker, pk::hex_object@ target, pk::point dst_pos)
		{
			pk::unit@ targetu = target!=null ? getUnit(target.get_pos()) : null;
			if (targetu == null)
				return;

			array<pk::point> arr = pk::range(dst_pos, 1, 4);
			for (int i = 0; i < arr.length; i++)
			{
				pk::point pt = arr[i];
				pk::unit@ u = getUnit(pt);
				if(u==null)
					continue;
				if(u.get_id() == attacker.get_id())
					continue;
				if(u.get_force_id()!=attacker.get_force_id())
					continue;

				int dist = pk::get_distance(u.get_pos(), dst_pos);
				if (getMaxAttackDistance(u) < dist)
					continue;

				int n = callback200(u, attacker, target);
				if(!pk::rand_bool(n))
					continue;

				pk::damage_info di;
				di.src_pos = u.get_pos();
				di.dst_pos = dst_pos;
				prev_callback_210(di, u, dst_pos);


				string str = "";
				switch (pk::rand(3))
				{
				case 0:str = "�̰͵� �޾ƶ�";break;
				case 1:str = "�̰� ���";break;
				case 2:str = "���� ������ �ʾҴ�";break;
				}
				pk::unit_anim(u, dist > 1 ? 1 : 0, {di}, dst_pos, 0, pk::encode(str), 0);

				string str2 = "";
				switch (pk::rand(3))
				{
				case 0:str = pk::format("���� {} ��",pk::decode(pk::get_name(pk::get_person(u.leader))));break;
				case 1:str = "���� ����";break;
				case 2:str = "�̰���~";break;
				}
				pk::say(str2, pk::get_person(attacker.leader), attacker);

				addTroops(targetu, di.troops_damage);
				updateAfter(u, target);
			}
		}

		void attackFail(pk::unit@ attacker, pk::hex_object@ target, pk::point dst_pos,int type,bool bCri)
		{
			bool bCri2 = type == ����_����_Ȱ���� ? ũ��Ƽ��_���Ÿ� : ũ��Ƽ��_����;
			int r = pk::rand(100);
			if (r <= �������н�_�Ϲݰ���_Ȯ��)
			{
				pk::damage_info di;
				di.src_pos = attacker.get_pos();
				di.dst_pos = dst_pos;
				callback209(di, attacker, 0, dst_pos, 0, bCri ? 1 : 0, false);
				pk::unit_anim(attacker, type, { di }, dst_pos, 0, pk::encode("ĩ �̰͹ۿ�.."), 0);
				if (!�ݰ��ұ�(di, target))
				{
					addTroops(target, di);
					updateAfter(attacker, target);
					update(attacker, dst_pos, { di }, bCri2,false);
					if (����(attacker))
					{
						pk::unit_anim(attacker, type, { di }, dst_pos, 0, pk::encode("ĩ �̰͹ۿ�.."), 0);
						addTroops(target, di);
						updateAfter(attacker, target);
						update(attacker, dst_pos, { di }, bCri2,false);
					}
				}
				
			}
			else if (r > �������н�_�Ϲݰ���_Ȯ�� and r < �������н�_�Ϲݰ���_Ȯ�� + �������н�_�Ϲݰ���_��������_Ȯ��)
			{
				pk::damage_info di;
				di.src_pos = attacker.get_pos();
				di.dst_pos = dst_pos;
				di.troops_damage = 0;
				//prev_callback_202��������(di, attacker, type, dst_pos, 0, bCri ? 1 : 0, false);

				pk::unit_anim(attacker, type, { di }, dst_pos, 0, pk::encode("������ �ʴ°�.."), 0);
				addTroops(target, di);
				updateAfter(attacker, target);
				update(attacker, dst_pos, { di }, bCri2, false);
			}
			else
			{
				int dist = pk::get_distance(attacker.get_pos(), dst_pos);
				if (getMaxAttackDistance(target) < dist)
					return;
				
				pk::damage_info di;
				di.src_pos = dst_pos;
				di.dst_pos = attacker.get_pos();
				callback209(di, target, 1, attacker.get_pos(), 0, bCri ? 1 : 0, false);

				pk::unit_anim(target, type, { di }, attacker.get_pos(), 1, pk::encode("�ݰ��̴�"), 0);
				addTroops(attacker, di);
				updateAfter(target, attacker);
				update(attacker, dst_pos, { di }, bCri2,false,true);
			}
		}
		bool updateAfter(pk::unit@ attacker, pk::hex_object@ target)
		{
			if (target == null)
				return false;

			pk::unit@ targetU = getUnit(target.get_pos());
			if(targetU!=null && targetU.troops == 0)
			{
				int dist = pk::get_distance(attacker.get_pos(), target.get_pos());
				//pk::printf("kill start\n");
				pk::kill(targetU, attacker, dist == 1, attacker.weapon == ����_��);
				//pk::printf("kill end\n");
				if (attacker.has_skill(Ư��_�Ӿ�)) 
					pk::add_energy(attacker, int(pk::core::skill_constant(attacker, Ư��_�Ӿ�)), true);
				return false;
			}
			else 
			{
				pk::building@ b = target;
				if(b.hp==0)
					pk::kill(b);
				return false;
			}
			return true;

		}

		void update����(pk::unit@ attacker, pk::hex_object@ target, pk::point dest0)
		{
			pk::unit@ u = target!=null ? getUnit(target.get_pos()) : null;
			if (u == null || !attacker.has_skill(Ư��_����) || u.has_skill(Ư��_ȣ��))
				return;
			if (target.get_pos().x == dest0.x && target.get_pos().y == dest0.y)
				return;

			int maxValue = int(pk::core::skill_constant(attacker, Ư��_����));
			if (u.member[0] >= 0 && u.member[0] < ����_�� && pk::rand_bool(maxValue))
				injury(pk::get_person(u.member[0]));
			if (u.member[1] >= 0 && u.member[1] < ����_�� && pk::rand_bool(maxValue))
				injury(pk::get_person(u.member[1]));
			if (u.member[2] >= 0 && u.member[2] < ����_�� && pk::rand_bool(maxValue))
				injury(pk::get_person(u.member[2]));
		}
		void injury(pk::person@ p)
		{
			string strType = "";
			switch (p.shoubyou)
			{
			case ��_�ǰ�:p.shoubyou = ��_����; strType = "����"; break;
			case ��_����:p.shoubyou = ��_����; strType = "����"; break;
			case ��_����:p.shoubyou = ��_���; strType = "���"; break;

			default:
				break;
			}
			p.update();

			switch (pk::rand(3))
			{
			case 0: pk::say(pk::encode("����.."), p, getUnit(p.get_pos())); break;
			case 1: pk::say(pk::encode("���⼱ �λ���.."), p, getUnit(p.get_pos())); break;
			case 2: pk::say(pk::encode("�ƾ�..�̷���"), p, getUnit(p.get_pos())); break;
			default:
				break;
			}
			
			pk::force@ force = pk::get_force(p.get_force_id());
			pk::person@ kunshu = force!=null ? pk::get_person(force.kunshu) : null;
			if (kunshu != null)
			{
				string str = pk::format("\x1b[2x{}\x1b[0x�� \x1b[2x{}\x1b[0x,\x1b[29x{}\x1b[0x ����",getName(kunshu),getName(p) ,strType);
				pk::history_log(p.get_pos(), force != null ? force.color : -1, pk::encode(str));
			}
		}


		string getName(pk::force@ f)
		{
			if (f == null)
				return "null";
			return getName(pk::get_person(f.kunshu));
		}
		string getName(pk::object@ obj)
		{
			return obj!=null ? pk::decode(pk::get_name(obj)) : "null";
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

		void addTroops(pk::hex_object@ obj, pk::damage_info di, bool bEffect = true)
		{
			addTroops(obj, di.troops_damage, bEffect);
		}
		void addTroops(pk::hex_object@ obj,int value,bool bEffect = true)
		{
			pk::unit@ u;
			pk::building@ b;
			pk::city@ c;
			switch (obj.get_type_id())
			{
			case 11: @u = obj;pk::add_troops(u, -value, bEffect);break;
			case 5: case 6:case 7: case 8:
				@b = obj; pk::add_troops(b, -value, bEffect); break;
			default:
				break;
			}
		}


		void updateChaos(pk::unit@ u, pk::unit@ u2)
		{
			//u.status = �δ����_ȥ��;
			//u.status_timer = getChaosTime(u);
			//pk::play_se(2);

			pk::set_status(u, u2, �δ����_ȥ��, getChaosTime(u),true);
		}
		bool update(pk::unit@ u, pk::point dst_pos, array<pk::damage_info>@ dis,bool bRanged,bool bCri,bool success = true, bool bCounter = false)
		{
			pk::unit@ attacker = u;
			pk::add_stat_exp(attacker, ����ɷ�_����, success ? 4 : 1);
			pk::add_kouseki(attacker, success ? 100 : 10);
			
			int type = -1;
			switch (attacker.weapon)
			{
			case ����_â:type = ����_â��; break;
			case ����_��:type = ����_�뺴; break;
			case ����_��:type = ����_�غ�; break;
			case ����_����:type = ����_�⺴; break;
			default:
				break;
			}
			if (type != -1)
			{
				
				if (attacker.leader >= 0 && attacker.leader < ����_��)
				{
					pk::person@ p0 = pk::get_person(attacker.leader);
					pk::add_heishu_exp(p0, type, success ? 4 : 1);
				}
				if (attacker.member[1] >= 0 && attacker.member[1] < ����_��)
				{
					pk::person@ p0 = pk::get_person(attacker.member[1]);
					pk::add_heishu_exp(p0, type, success ? 4 : 1);
				}
				if (attacker.member[2] >= 0 && attacker.member[2] < ����_��)
				{
					pk::person@ p0 = pk::get_person(attacker.member[2]);
					pk::add_heishu_exp(p0, type, success ? 4 : 1);
				}
			}
			pk::unit@ targetU = getUnit(dst_pos);
			if (targetU != null)
			{
				pk::add_stat_exp(targetU, ����ɷ�_���, 1);
				
				int type2 = -1;
				switch (targetU.weapon)
				{
				case ����_â:type2 = ����_â��; break;
				case ����_��:type2 = ����_�뺴; break;
				case ����_��:type2 = ����_�غ�; break;
				case ����_����:type2 = ����_�⺴; break;
				case ����_����:case ����_����:case ����_����:case ����_���:type2 = ����_����; break;
				case ����_�ְ�:case ����_����:case ����_����:type2 = ����_����;break;
				default:
					break;
				}
				if (type2 != -1)
				{
					if (targetU.leader >= 0 && targetU.leader < ����_��)
					{
						pk::person@ p0 = pk::get_person(targetU.leader);
						pk::add_heishu_exp(p0, type, 1);
					}
					if (targetU.member[1] >= 0 && targetU.member[1] < ����_��)
					{
						pk::person@ p0 = pk::get_person(targetU.member[1]);
						pk::add_heishu_exp(p0, type, 1);
					}
					if (targetU.member[2] >= 0 && targetU.member[2] < ����_��)
					{
						pk::person@ p0 = pk::get_person(targetU.member[2]);
						pk::add_heishu_exp(p0, type, 1);
					}
				}
			}

			if (!bCounter)
			{
				int sum = 0;
				for (int i = 0; i < dis.length; i++)
				{
					pk::damage_info di = dis[i];
					pk::point ptDst = di.dst_move_pos;
					if (ptDst.x == -1 && ptDst.y == -1)
						ptDst = di.dst_pos;

					pk::unit@ dstU = getUnit(ptDst);
					if (dstU == null)
						continue;
					if (u.has_skill(Ư��_����))
						pk::add_energy(dstU, -int(pk::core::skill_constant(u, Ư��_����)), true);
					if (u.has_skill(Ư��_��ǳ))
						pk::add_energy(dstU, -int(pk::core::skill_constant(u, Ư��_��ǳ)), true);

					sum += di.troops_damage;
				}
				if (!bRanged && u.has_skill(Ư��_�ɰ�))
					pk::add_troops(u, float(pk::core::skill_constant(u, Ư��_�ɰ�)) * sum, true);
			}

			if (success && targetU!=null && pk::rand_bool(����_�ϱ���_Ȯ��))
			{
				@_scene_attackerUnit = attacker;
				@_scene_targetUnit = targetU;
				@_scene_attacker = pk::get_person(attacker.leader);
				@_scene_target = pk::get_person(targetU.leader);
				pk::message_box(pk::encode("������ ã�Ҵ�"), _scene_attacker);
				pk::message_box(pk::encode("���� ��ȸ�ϰ� �ɰ��̴�"), _scene_target);
				pk::scene(pk::scene_t(scene_�ϱ���));
			}

			@targetU = getUnit(dst_pos);
			if (success && targetU != null && u.weapon == ����_����)
			{
				pk::person@ l = pk::get_person(u.leader);
				bool bDie = false;
				if (targetU.leader >= 0 && targetU.leader < ����_��)
				{
					pk::person@ p0 = pk::get_person(targetU.leader);
					int n=prev_callback_203�⺴�������(l, p0, ����_����, bCri);
					if (pk::rand_bool(n)) 
					{
						pk::message_box(pk::encode("���ϴ�.."), p0);
						pk::kill(p0, l, targetU, null, 0);
						bDie = true;
					}
				}
				if (!bDie && targetU.member[1] >= 0 && targetU.member[1] < ����_��)
				{
					pk::person@ p0 = pk::get_person(targetU.member[1]);
					int n=prev_callback_203�⺴�������(l, p0, ����_����, bCri);
					if (pk::rand_bool(n))
					{
						pk::kill(p0, l, targetU, null, 0);
						pk::message_box(pk::encode("���ϴ�.."), p0);
						bDie = true;
					}
				}
				if (!bDie && targetU.member[2] >= 0 && targetU.member[2] < ����_��)
				{
					pk::person@ p0 = pk::get_person(targetU.member[2]);
					int n = prev_callback_203�⺴�������(l, p0, ����_����, bCri);
					if (pk::rand_bool(n))
					{
						pk::kill(p0, l, targetU, null, 0);
						pk::message_box(pk::encode("���ϴ�.."), p0);
						bDie = true;
					}
				}
			}

			return getUnit(dst_pos) != null;
		}

		int _duel_result = 0;
		pk::person@ _scene_attacker = null;
		pk::person@ _scene_target = null;
		pk::unit@ _scene_attackerUnit = null;
		pk::unit@ _scene_targetUnit = null;

		void scene_�ϱ���()
		{
			//pk::printf("tatical 1:1 {},{}------------------\n",getName(_scene_attacker), getName(_scene_target));
			bool b0 = pk::is_player_controlled(_scene_attackerUnit);
			bool b1 = pk::is_player_controlled(_scene_targetUnit);
			_duel_result = pk::duel(_scene_attackerUnit, _scene_targetUnit, _scene_attacker, null, null, _scene_target, null, null, b0,b1, 0, b0 || b1).first;
		}

		void update(pk::unit@ u, pk::hex_object@ target, pk::point dst_pos,pk::point dst_pos2)
		{
			updateAssist(u, target, dst_pos2);
			update����(u, target, dst_pos);
			pk::add_energy(u, -����_���, true);
			u.action_done = true;
		}
		bool �ݰ��ұ�(pk::damage_info di,pk::hex_object@ target)
		{
			pk::unit@ u = target!=null ? getUnit(target.get_pos()) : null;
			if (u == null)
				return false;

			if (u.has_skill(Ư��_�ݰ�))
			{
				int val = int(pk::core::skill_constant(u, Ư��_�ݰ�, 0));
				int ratio = int(pk::core::skill_constant(u, Ư��_�ݰ�, 1));
				if (di.troops_damage < val && pk::rand_bool(ratio))
				{
					pk::play_se(7);
					return true;
				}
			}
			if (u.has_skill(Ư��_�ұ�))
			{
				int val = int(pk::core::skill_constant(u, Ư��_�ݰ�, 0));
				int ratio = int(pk::core::skill_constant(u, Ư��_�ݰ�, 1));
				if (u.troops < val && pk::rand_bool(ratio))
				{
					pk::play_se(7);
					return true;
				}
			}
			return false;
		}
		bool ����(pk::unit@ u)
		{
			int val = int(pk::core::skill_constant(u, Ư��_����));
			bool b = bool(pk::core["��Ư�⿬��"]);
			return b && u.has_skill(Ư��_����) && pk::rand_bool(val);
		}
		void cutin(pk::unit@ u)
		{
			if (!pk::is_player_controlled(u))
				return;
			pk::face_cutin(u);
		}
		pk::unit@ getUnit(pk::point pos)
		{
			return pk::is_valid_pos(pos) ? pk::get_unit(pos) : null;
		}
		bool checkHex�뺴(pk::unit@ u, pk::point pt)
		{
			if (!u.has_skill(Ư��_���) && pk::get_hex(pt).terrain == ����_��)
				return false;
			int h = pk::get_hex(pt).terrain;
			if (h == ����_�� || h == ����_�ٴ� || h == ����_��)
				return false;
			return true;
		}
		bool checkHexâ��(pk::point pt)
		{
			int h = pk::get_hex(pt).terrain;
			if (h == ����_�� || h == ����_�ٴ� || h == ����_�� || h == ����_��)
				return false;
			return true;
		}
		bool checkHex�غ�(pk::point pt)
		{
			int h = pk::get_hex(pt).terrain;
			if (h == ����_�� || h == ����_�ٴ� || h == ����_��)
				return false;
			return true;
		}
		bool checkHex�⺴(pk::point pt)
		{
			switch (pk::get_hex(pt).terrain)
			{
			case ����_���:
			case ����_�ʿ�:
			case ����_��:
			case ����_��:
				return true;
			}
			return false;
		}


	}//Main
	Main main;
}

