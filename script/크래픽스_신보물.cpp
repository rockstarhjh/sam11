/*
@������: ũ���Ƚ�
@Update: 2024.1.27,���ʹ���
@Update: 2024.1.28,�ϱ��� ���ڰ��� ó��
@Update: 2024.1.28,���� ����, ��å,����,������ ��� �������� ����,
@Update: 2024.1.28,�����߰�.
@Update: 2024.1.30,�����߽߰� ����ó��
@Update: 2024.2.1,����ó��
@Update: 2024.2.7,����Ư���� �λ������ �ʵ��� ����
@Update: 2024.2.8,ȥ��,���׿�,����,���Ư�����,�λ����� �߰�
@Update: 2024.2.9,����Ž�� ����ó��,get_unit���� ����
@Update: 2024.2.11,ȭ����� ȭ��Ư�� ����ȵǴ� ��������
@Update: 2024.2.12,��Ÿ �� �α� �Ϻ� ����
@Update: 2024.2.13,AI�� �нú� ȿ������ �ߺ�������� �ʵ��� ����
@Update: 2024.2.17,�ߺ����� �����������¹�������
@Update: 2024.2.18,���̺�ε�� ���ʼ����� ���׹��� ����
@Update: 2024.5.2, ����0�����϶� ó��
@Update: 2024.5.3, ����ȿ����, �ൿȸ��
@Update: 2024.5.6, ��������
@Update: 2024.5.7, ȥ��,��ų �α�ǥ��, AI������Ż ǥ�� ����
@Update: 2024.5.11, �ź��� ȭ��Ư�� ���������� ���°��� ������ ����
@Update: 2024.5.11, ����ȿ����, �ൿȸ��
@Update: 2024.5.15, AI�ź��� �̺�Ʈ ���忡�� �ϻ����� �ʵ��� ����
@Update: 2024.5.22, �������� �Ʊ����� �������� �ʵ��� ����
@Update: 2024.5.30, ���������� ������ ������ ����ȸ��, ����Ư�� �����߰�, TurnEnd�ϱ���� �������� TunrStart���� RentBack
@Update: 2024.6.1, �����ϰ� �ִ� �������κ��� ������ �������� ����, �ϱ��� ������ �ع��� ��� �ν��ϵ��� ����
@Update: 2024.6.1, ����ȸ��Ư��, ��ұ�Ư�� �߰�
@Update: 2024.6.2, ����Ư�� �߰�, ���� ����
@Update: 2024.7.20, ����Ư��,��������Ȯ��, �跫����Ȯ��, ��������Ȯ���߰�



*/
namespace �ź���_Items
{
	const int ������� = -1;//�������� ������
	const int �������� = -1;//�������� ������


	const bool ����_�������� = false;
	const bool ����_��������_�α�ǥ�� = false;

	const int ������_����_�Ÿ� = 30;//30ĭ
	const int ������_����_�Ÿ�_���� = 10;//10ĭ
	const int ����Ȯ��_���� = 1000; //��� �δ��� �ൿ�ϷḶ��,���忡��, �ź���Ž�� �õ�, 1/1000;

	/* ����Ư�⸮��Ʈ
		
		�鸶: ���ݷ��� �����ǳ�, �⺴���� Ȱ��°��� �ȵ�.
		�ý�: ����ũ�������� ����ǳ� �ý����ν� �Ʊ��� �Ƚ�°� ����ȵ�
		���: ����ũ��Ƽ���� ����,
		����: ZOC���þȵ�
		����: �λ���� �ȵ�
		ö��: �������ݹ��ȵ�
		ģ��,ģ��,ģ��,ģ�� : �����߻� ��� �ȵ�.


		����,��,�ɸ�,����,�߸�,����,��ȣ,�̵�,����
		����,����(�Ϻ�),����,�־�,
		����,����,����,����,�п�,���(�Ϻ�),����,����(�Ϻ�),����,â��,����,â��,�ؽ�,����,�ý�(�Ϻ�),����,����,����,����,����
		�鸶(�Ϻ�),�޽�,����,��ǳ,����,ģ��(�Ϻ�),ģ��(�Ϻ�),ģ��(�Ϻ�),ģ��(�Ϻ�)
		����,����,ȭ��,�,�ұ�,�ݰ�,ö��(�Ϻ�)
		�Ż�,���,�汹,�ⷫ,��,�˰�,ȭ��,����,��å,����,�ݰ�,����,���,ħ��,����,�ɸ�,����,��å
	*/

	const int ����Ư��_������_ȭ��߻� = 0; //�����ݿ� ȭ�谡 �߻��մϴ�.
	const int ����Ư��_����_ȭ��_��ȭ = 1; //������, �Ͻ��۽� �����Ʊ��� ���� ���ϴ�.
	const int ����Ư��_����_ȥ��_����_���� = 2;//������, �Ͻ��۽ÿ� �����Ʊ��� ȥ��,���� ���¸� �����մϴ�.
	const int ����Ư��_����_���� = 3;//������������ ���ڸ� ����Ʈ���ϴ�.
	const int ����Ư��_����_���÷���_������ = 4;//������ ������ �����������Ե� �������� �߻��մϴ�.
	const int ����Ư��_������_�߰������� = 5;//������ �������� �߰��������� �߻��մϴ�.
	const int ����Ư��_�־� = 6;//�������� ����Ҽ� �ְ� 30�� ����� ���Ͽ� �߰��˴ϴ�.
	const int ����Ư��_������_�漺��_���� = 7;//������ ������ �漺���� ���Ͻ�ŵ�ϴ�.
	const int ����Ư��_��ǳ = 8;//������ ������ ����� ũ�� ���ҽ�ŵ�ϴ�.
	const int ����Ư��_�ɰ� = 9;//������ ������ ���� �������� ������ ȸ���մϴ�. ���Ÿ� ���ݵ� ����˴ϴ�.
	const int ����Ư��_��ų = 10;//���� Ȯ���� ������ �������� �����ϴ�.
	const int ����Ư��_����Ż�� = 11;//������ �������� 1.5��� ������ Ż���մϴ�.
	const int ����Ư��_ȥ��_���� = 12;//������ ������ ȥ���� ���ߵ˴ϴ�.
	const int ����Ư��_����_���� = 13;//������ ������ ������ ���ߵ˴ϴ�.
	const int ����Ư��_����_���� = 14;//������ ������ ���䰡 ���ߵ˴ϴ�.
	const int ����Ư��_�ϱ���_���� = 15;//��������, ���� ������ �ϱ��䰡 ���ߵ˴ϴ�.
	const int ����Ư��_�����δ�_�ǹ�������_�߰� = 16;//�ڽ� �� �����δ��� �ǹ��������� 2�谡 �˴ϴ�.
	const int ����Ư��_�ⱳ����Ʈ_ȹ�� = 17;//���� �ⱳ����Ʈ�� �����մϴ�.
	const int ����Ư��_�ɷ¿����ӵ���� = 18;//�ɷ¿����ӵ��� 2�� �����ϴ�.
	const int ����Ư��_���׿� = 19;//���������� ���׿��� �������ϴ�.
	const int ����Ư��_�λ����� = 20;//���ݽ� �λ��� ���ߵ˴ϴ�.
	const int ����Ư��_���Ư����� = 21;//�����Ʊ��� ���Ư�⸦ �����մϴ�.(�,ö��,�ұ�,�ݰ�)
	const int ����Ư��_ȥ�� = 22;//����Ư��߻�,ex){����Ư��_ȥ��,����Ư��_����_����,����Ư��_����} ���ڿ� ������ �������� �Ѱ��� �߻�
	const int ����Ư��_���� = 23;//���������� ���谡 �߻��մϴ�.
	const int ����Ư��_������� = 24;//Ȱ���ݽ� ��ǥ������ ������ ������ ���÷��� �������� �߻���ŵ�ϴ�.
	const int ����Ư��_����_ȸ�� = 25;//�����Ʊ��� �δ밡 ȸ���˴ϴ�.
	const int ����Ư��_��ұ� = 26;//�ұ��� ���������Դϴ�.�Һ����϶��� ȥ���� �ɸ��� �ʽ��ϴ�. 2000���������϶�, 90Ȯ���� �����ϴ�.
	const int ����Ư��_��������Ȯ�� = 27;//��������Ȯ���� �߰��˴ϴ�.
	const int ����Ư��_��������Ȯ�� = 28;//��������Ȯ���� �߰��˴ϴ�.
	const int ����Ư��_�跫����Ȯ�� = 29;//�跫����Ȯ���� �߰��˴ϴ�.

	const int ȭ��_Ȯ�� = 100;

	const int ����_Ȯ�� = 100;
	const int ����_�⺻_������ = 500;
	const int ����_����_������ = 500;
	const int ����_�λ�_Ȯ�� = 10;

	const int ���׿�_Ȯ�� = 100;
	const int ���׿�_�⺻_������ = 300;
	const int ���׿�_����_������ = 300;
	const int ���׿�_ȭ��_Ȯ�� = 100;

	const int ����_������ = 1000;//x^2���� ����, ���� Ȯ���� ����������
	const int ����_Ȯ�� = 100;

	const int ����_��ȭ_���� = 2;
	const int ����_ȥ��_����_ȸ��_���� = 2;
	const int ����_ȸ��_���� = 1;

	const int ����_����_ȸ���� = 500;

	const int ��ұ�_���±��� = 2000;
	const int ��ұ�_Ȯ�� = 90;

	const float ���÷���_������_���� = 0.5;
	const float �߰�_������_���� = 0.15;
	const float �ɰ�_���� = 0.25;
	const float �ǹ�������_���� = 2.0;
	const float ����_���� = 2.0;

	const float �־�_��� = 30; //����������밡���ϵ���
	const float ��ǳ_��� = 50;
	const int �漺��_���Ϸ� = 3;

	const int ��ų_Ȯ�� = 2;

	const float ����_������_���� = 1.5;
	const int ȥ��_Ȯ�� = 30;
	const int ����_Ȯ�� = 30;
	const int ����_Ȯ�� = 30;

	const int �ϱ���_ȸ��_����_�� = 10; //������ 10�̻� ������� �ϱ��並 ���� �ʽ��ϴ�.
	const int �ϱ���_����_Ȯ�� = 20;

	const int �ϴ�_�ⱳ����Ʈ = 100;
	const int �λ�����_Ȯ�� = 30;

	const int ��������Ȯ�� = 15;
	const int �跫����Ȯ�� = 15;
	const int ��������Ȯ�� = 30;




	const int ����_RAND = 3;
	
	array<CustomItem@> Ŀ���Ҿ����۽� =
	{
		//�ź���ID,�ź����̸�,�ź����̹������,����Ư�⸮��Ʈ,Ư�⸮��Ʈ, �빫������,����Ÿ��,��ġ, ��������, ���ʺ�������
		CustomItem(0,"ȭ�浵","�ź���\\ȭ�뵵2.png",{����Ư��_������_ȭ��߻�}, {Ư��_�п�,Ư��_ȭ��},0,6,0,0,0,��������_��,40,��������, �������),
		CustomItem(1,"����ȭ�ɰ�","�ź���\\����ȭ�ɰ�.png",{����Ư��_����_ȭ��_��ȭ,����Ư��_����_ȥ��_����_����}, {Ư��_�ݰ�,Ư��_�ұ�,Ư��_ö��},3,3,0,0,0,��������_��,40,��������, �������),
		CustomItem(2,"���������","�ź���\\���������.png", {����Ư��_������_�߰�������}, {Ư��_�п�},0,6,0,0,0,��������_��,40,��������, �������),
		CustomItem(3,"�巡�ｽ���̾�","�ź���\\������1.png", {����Ư��_����_���÷���_������}, {Ư��_�п�},0,6,0,0,0,��������_��,40,��������, �������),
		
		
		CustomItem(6,"û��������","�ź���\\û��������.png",{}, {},0,2,0,0,0,��������_��,20,��������, �������),
		CustomItem(7,"�¸������","�ź���\\�¸��Ǻ���.png",{����Ư��_�ⱳ����Ʈ_ȹ��}, {},0,0,0,0,0,��������_��å,10,��������, �������),
		CustomItem(11,"������","�ź���\\�ٸ���.png",{����Ư��_�λ�����}, {},0,2,0,0,0,��������_�ϱ�,20,��������, �������),
		CustomItem(12,"�������","�ź���\\ĸƾ����.png",{����Ư��_���Ư�����}, {Ư��_�ݰ�,Ư��_�ұ�,Ư��_ö��,Ư��_�},5,0,0,0,0,��������_��å,40,��������, �������),
		
		CustomItem(14,"������","�ź���\\������.png",{����Ư��_�ɷ¿����ӵ����}, {},0,0,0,0,0,��������_��å,10,��������, �������),
		CustomItem(15,"�亸�Ͽ콺Ȱ","�ź���\\�亸�Ͽ콺Ȱ.png",{����Ư��_�������}, {Ư��_�п�},0,6,0,0,0,��������_Ȱ,40,��������, �������),

		CustomItem(16,"�ӷ�","�ź���\\�ӷ�.png",{����Ư��_����_ȸ��}, {},0,0,0,0,0,��������_��å,20,��������, �������)
		


		//�Ǹ������� �ĸ�(,) ������ �������� ����.
	};

	const array<string> �����̹��� =
	{
		"Ebony_����\\���丶.png",
		"Ebony_����\\����.png",
		"Ebony_����\\��Ȳ����.png",
		"Ebony_����\\����.png",
		"Ebony_����\\��ϸ�.png",
		"Ebony_����\\��ϸ�.png",
		"Ebony_����\\��ϸ�.png",
		"Ebony_����\\ĥ������.png",
		"Ebony_����\\��õ��.png",
		"Ebony_����\\û����.png",

		"Ebony_����\\�ְ��.png",
		"Ebony_����\\��õȭ��.png",
		"Ebony_����\\û������.png",
		"Ebony_����\\���Ȼ��.png",
		"Ebony_����\\��û��.png",
		"Ebony_����\\��.png",
		"Ebony_����\\��.png",
		"Ebony_����\\�ܱ�.png",
		"Ebony_����\\�ܱ�.png",
		"Ebony_����\\����.png",

		"Ebony_����\\����.png",
		"Ebony_����\\ö��.png",
		"Ebony_����\\��������-��.png",
		"Ebony_����\\�̱���-��.png",
		"Ebony_����\\�ܱ�.png",
		"Ebony_����\\�ܱ�.png",
		"Ebony_����\\��ȣ���.png",
		"Ebony_����\\��ȣ���.png",
		"Ebony_����\\�Ʊ�.png",
		"Ebony_����\\�Ʊ�.png",

		"Ebony_����\\���ں���.png",
		"Ebony_����\\����24��.png",
		"Ebony_����\\�ʹ��ż�.png",
		"Ebony_����\\����.png",
		"Ebony_����\\�﷫.png",
		"Ebony_����\\����.png",
		"Ebony_����\\������.png",
		"Ebony_����\\����å.png",
		"Ebony_����\\�縶��.png",
		"Ebony_����\\����.png",

		"Ebony_����\\��������.png",
		"Ebony_����\\����.png",
		"Ebony_����\\����.png",
		"",
		"",
		"",
		"",
		"",
		"",
		"",

		"Ebony_����\\������뱸.png",
		"Ebony_����\\�Ǹ����丶.png",
		"Ebony_����\\�����鸶.png",
		"Ebony_����\\�鸶.png",
		"Ebony_����\\�����.png",
		"Ebony_����\\��ȯ��.png",
		"Ebony_����\\��븶.png",
		"Ebony_����\\�����.png",
		"Ebony_����\\���.png",
		"Ebony_����\\�����.png",

		"Ebony_����\\����.png",
		"Ebony_����\\����.png",
		"Ebony_����\\������.png",
		"Ebony_����\\���ǵ�.png",
		"Ebony_����\\�ŵ�.png",
		"Ebony_����\\������.png",
		"Ebony_����\\��ġ��.png",
		"Ebony_����\\ȯ����.png",
		"Ebony_����\\��ö��.png",
		"Ebony_����\\��ε�.png",

		"Ebony_����\\���뵵.png",
		"Ebony_����\\�̺ε�.png",
		"Ebony_����\\�밣��.png",
		"Ebony_����\\ġ���.png",
		"Ebony_����\\���.png",
		"Ebony_����\\öô���.png",
		"Ebony_����\\�ݸ���.png",
		"Ebony_����\\�����.png",
		"Ebony_����\\ö��.png",
		"Ebony_����\\öĥ����Ÿ.png",

		"Ebony_����\\ö����.png",
		"Ebony_����\\������.png",
		"Ebony_����\\��ȭ����.png",
		"Ebony_����\\����.png",
		"Ebony_����\\ö��.png",
		"Ebony_����\\����.png",
		"Ebony_����\\������.png",
		"Ebony_����\\���.png",
		"Ebony_����\\����.png",
		"Ebony_����\\������.png",

		"Ebony_����\\�ÿ��.png",
		"Ebony_����\\ġ��.png",
		"Ebony_����\\�����¾���.png",
		"Ebony_����\\�Ѻ���.png",
		"Ebony_����\\����.png",
		"Ebony_����\\�а�õ��.png",
		"Ebony_����\\����������.png",
		"Ebony_����\\�����嵵.png",
		"Ebony_����\\���߸�.png",
		""
	};


	const int KEY = pk::hash("�ź���");
	const int KEY_EXPORT = pk::hash("�ź���_Export");

	class CustomItem
	{
		pk::person@ owner = null;
		pk::person@ fowner = null;
		string name = "";
		string path = "";
		int id = -1;

		array<int> skills����;
		array<int> skills;

		array<int> �ɷ� = { 0,0,0,0,0 };

		int srcItem = -1;
		int value = 0;
		int type;

		array<int> skillsȥ�� = {};


		CustomItem(){}
		CustomItem(int id0, string str,string path0,array<int> ������ų0, array<int> skills0, int ���,int ����,int ����,int ��ġ��,int �ŷ�,int type0, int value0, int ��������, int ��������)
		{
			id = id0;
			path = path0;
			name = str;
			value = value0;
			skills = skills0;
			
			if (������ų0.length > 1 && ������ų0[0] == ����Ư��_ȥ��)
			{
				skills���� = { ����Ư��_ȥ�� };
				for (int i = 1; i < ������ų0.length; i++)
				{
					skillsȥ��.insertLast(������ų0[i]);
				}
			}
			else 
			{
				skills���� = ������ų0;
			}

			�ɷ� = { ���,����,����,��ġ��,�ŷ� };
			srcItem = ��������;
			type = type0;
			if (�������� >= 0)
			{
				@fowner = pk::get_person(��������);
			}
		}

		void updateOwner(pk::person@ newOwner)
		{
			if (owner != null && newOwner != null && owner.get_id() == newOwner.get_id())
				return;

			if (owner != null)
			{
				if (�ɷ�[0] != 0) apply����ɷ�(owner, ����ɷ�_���, -�ɷ�[0]);
				if (�ɷ�[1] != 0) apply����ɷ�(owner, ����ɷ�_����, -�ɷ�[1]);
				if (�ɷ�[2] != 0) apply����ɷ�(owner, ����ɷ�_����, -�ɷ�[2]);
				if (�ɷ�[3] != 0) apply����ɷ�(owner, ����ɷ�_��ġ, -�ɷ�[3]);
				if (�ɷ�[4] != 0) apply����ɷ�(owner, ����ɷ�_�ŷ�, -�ɷ�[4]);
			}
			
			@owner = newOwner;
			if (newOwner != null)
			{
				if (�ɷ�[0] != 0) apply����ɷ�(newOwner, ����ɷ�_���, �ɷ�[0]);
				if (�ɷ�[1] != 0) apply����ɷ�(newOwner, ����ɷ�_����, �ɷ�[1]);
				if (�ɷ�[2] != 0) apply����ɷ�(newOwner, ����ɷ�_����, �ɷ�[2]);
				if (�ɷ�[3] != 0) apply����ɷ�(newOwner, ����ɷ�_��ġ, �ɷ�[3]);
				if (�ɷ�[4] != 0) apply����ɷ�(newOwner, ����ɷ�_�ŷ�, �ɷ�[4]);
			}
		}

		void transfer(pk::person@ p0, pk::person@ p1, pk::item@ item)
		{
			array<pk::item@> arr;
			if (p0 != null)
			{
				for (int i = 0; i < ����_��; i++)
				{
					pk::item@ it = pk::get_item(i);
					if (it == null)
						continue;

					if (it.owner == p0.get_id() && it.id != item.id)
					{
						it.owner = -1;
						it.update();
						arr.insertLast(it);
					}
				}
			}
			if (p0 == null)
			{
				item.owner = p1.get_id();
				item.location = p1.service;
			}
			pk::transfer_item(p0!=null ? p0 : p1, p1);
			
			if (p0 != null)
			{
				for (int i = 0; i < arr.length; i++)
				{
					pk::item@ it = arr[i];
					it.owner = p0.get_id();
					it.update();
				}
				pk::transfer_item(p0, p0);
			}
		}

		array<int> updateRent(pk::item@ item)
		{
			pk::person@ powner = pk::get_person(item.owner);

			//item.owner = owner.get_id();
			//item.location = owner.service;
			//item.update();
			//if (powner != null) powner.update();
			//owner.update();



			array<int> bbb = { owner.max_stat[����ɷ�_���],owner.max_stat[����ɷ�_����],owner.max_stat[����ɷ�_����] ,owner.max_stat[����ɷ�_��ġ] ,owner.max_stat[����ɷ�_�ŷ�] };

			//pk::printf("base:{},{}\n", owner.base_stat[����ɷ�_���], owner.base_stat[����ɷ�_����]);
			//pk::printf("max:{},{}\n", owner.max_stat[����ɷ�_���], owner.max_stat[����ɷ�_����]);
			//pk::printf("cur:{},{}\n", owner.stat[����ɷ�_���], owner.stat[����ɷ�_����]);

			transfer(powner, owner, item);

			//pk::printf("base2:{},{}\n", owner.base_stat[����ɷ�_���], owner.base_stat[����ɷ�_����]);
			//pk::printf("max2:{},{}\n", owner.max_stat[����ɷ�_���], owner.max_stat[����ɷ�_����]);
			//pk::printf("cur2:{},{}\n", owner.stat[����ɷ�_���], owner.stat[����ɷ�_����]);

			array<int> rented(5, 0);
			for (int i = 0; i < bbb.length; i++)
				rented[i] = owner.max_stat[i] - bbb[i];
			for (int i = 0; i < bbb.length; i++)
				owner.base_stat[i] = owner.base_stat[i] - rented[i];
			owner.update();

			//pk::printf("base3:{},{}\n", owner.base_stat[����ɷ�_���], owner.base_stat[����ɷ�_����]);
			//pk::printf("max3:{},{}\n", owner.max_stat[����ɷ�_���], owner.max_stat[����ɷ�_����]);
			//pk::printf("cur3:{},{}\n", owner.stat[����ɷ�_���], owner.stat[����ɷ�_����]);



			if (powner != null)
			{
				//array<int> bbb2 = { powner.max_stat[����ɷ�_���],powner.max_stat[����ɷ�_����],powner.max_stat[����ɷ�_����] ,powner.max_stat[����ɷ�_��ġ] ,powner.max_stat[����ɷ�_�ŷ�] };
				//array<int> bbb2 = { powner.base_stat[����ɷ�_���],powner.base_stat[����ɷ�_����],powner.base_stat[����ɷ�_����] ,powner.base_stat[����ɷ�_��ġ] ,powner.base_stat[����ɷ�_�ŷ�] };
				for (int i = 0; i < rented.length; i++)
					powner.base_stat[i] = powner.base_stat[i] + rented[i];
				powner.update();
			}

			return rented;
		}
		void removeRent(pk::item@ item,pk::person@ newOwner)
		{
			//item.owner = newOwner!=null ? newOwner.get_id() : -1;
			//item.location = newOwner != null ? newOwner.service : item.location;
			//item.update();
			//owner.update();
			//if (newOwner != null) newOwner.update();

			//if (newOwner != null)
			//{
			//	//array<int> bbb2 = { newOwner.max_stat[����ɷ�_���],newOwner.max_stat[����ɷ�_����],newOwner.max_stat[����ɷ�_����] ,newOwner.max_stat[����ɷ�_��ġ] ,newOwner.max_stat[����ɷ�_�ŷ�] };
			//	array<int> bbb2 = { newOwner.base_stat[����ɷ�_���],newOwner.base_stat[����ɷ�_����],newOwner.base_stat[����ɷ�_����] ,newOwner.base_stat[����ɷ�_��ġ] ,newOwner.base_stat[����ɷ�_�ŷ�] };
			//	pk::transfer_item(newOwner, newOwner);
			//	for (int i = 0; i < bbb2.length; i++)
			//		newOwner.base_stat[i] = bbb2[i];
			//	newOwner.update();
			//}


			array<int> bbb = { owner.max_stat[����ɷ�_���],owner.max_stat[����ɷ�_����],owner.max_stat[����ɷ�_����] ,owner.max_stat[����ɷ�_��ġ] ,owner.max_stat[����ɷ�_�ŷ�] };
			//array<int> bbb = { owner.base_stat[����ɷ�_���],owner.base_stat[����ɷ�_����],owner.base_stat[����ɷ�_����] ,owner.base_stat[����ɷ�_��ġ] ,owner.base_stat[����ɷ�_�ŷ�] };
			//pk::transfer_item(owner, owner);
			//owner.update();

			transfer(owner, newOwner, item);

			array<int> rented(5, 0);
			for (int i = 0; i < bbb.length; i++)
				rented[i] = bbb[i] - owner.max_stat[i];
			for (int i = 0; i < rented.length; i++)
			{
				owner.base_stat[i] = owner.base_stat[i] + rented[i];
				newOwner.base_stat[i] = newOwner.base_stat[i] - rented[i];
			}
			newOwner.update();
			owner.update();

			//pk::printf("{},base4:{},{}\n", getName(owner), owner.base_stat[����ɷ�_���], owner.base_stat[����ɷ�_����]);
			//pk::printf("{},max4:{},{}\n", getName(owner),owner.max_stat[����ɷ�_���], owner.max_stat[����ɷ�_����]);
			//pk::printf("{},cur4:{},{}\n", getName(owner),owner.stat[����ɷ�_���], owner.stat[����ɷ�_����]);
			//
			//pk::printf("{},base4:{},{}\n", getName(newOwner), newOwner.base_stat[����ɷ�_���], newOwner.base_stat[����ɷ�_����]);
			//pk::printf("{},max4:{},{}\n", getName(newOwner), newOwner.max_stat[����ɷ�_���], newOwner.max_stat[����ɷ�_����]);
			//pk::printf("{},cur4:{},{}\n", getName(newOwner), newOwner.stat[����ɷ�_���], newOwner.stat[����ɷ�_����]);

		}

		void removeRent(pk::item@ item, pk::person@ pOwner, pk::person@ newOwner)
		{
			array<int> bbb = { newOwner.max_stat[����ɷ�_���],newOwner.max_stat[����ɷ�_����],newOwner.max_stat[����ɷ�_����] ,newOwner.max_stat[����ɷ�_��ġ] ,newOwner.max_stat[����ɷ�_�ŷ�] };

			transfer(pOwner, newOwner, item);

			array<int> rented(5, 0);
			for (int i = 0; i < bbb.length; i++)
				rented[i] = newOwner.max_stat[i] - bbb[i];
			for (int i = 0; i < rented.length; i++)
			{
				newOwner.base_stat[i] = newOwner.base_stat[i] - rented[i];
			}
			newOwner.update();

			//pk::printf("{},base4:{},{}\n", getName(newOwner), newOwner.base_stat[����ɷ�_���], newOwner.base_stat[����ɷ�_����]);
			//pk::printf("{},max4:{},{}\n", getName(newOwner), newOwner.max_stat[����ɷ�_���], newOwner.max_stat[����ɷ�_����]);
			//pk::printf("{},cur4:{},{}\n", getName(newOwner), newOwner.stat[����ɷ�_���], newOwner.stat[����ɷ�_����]);

		}

		string getName(pk::object@ obj)
		{
			return obj != null ? pk::decode(pk::get_name(obj)) : "null";
		}


		bool hasSkill(int skill)
		{
			for (int i = 0; i < skills.length; i++)
			{
				if (skills[i] == skill)
					return true;
			}
			return false;
		}

		void apply����ɷ�(pk::person@ p, int type, int value)
		{
			p.base_stat[type] = p.base_stat[type] + value;
			p.update();
		}

	};

	class ItemRent
	{
		CustomItem@ citem = null;
		pk::item@ item;
		pk::person@ owner0;
		pk::person@ owner;
		array<int> rented;

		void rent()
		{
			//pk::printf("rent:{},{}\n", citem.name, getName(item));
			rented = citem.updateRent(item);
			//pk::printf("rented:{},{},{},{},{}\n", rented[0], rented[1], rented[2], rented[3], rented[4]);

			if (����_��������_�α�ǥ��)
			{
				pk::force@ force = pk::get_force(owner.get_force_id());
				pk::person@ kunshu = pk::get_person(force.kunshu);

				string str = pk::format("\x1b[2x{}\x1b[0x,\x1b[2x{}\x1b[0x�� \x1b[29x{}\x1b[0x �뿩", getName(owner), getName(owner0), getName(item));
				pk::history_log(kunshu.get_pos(), force.color, pk::encode(str));
			}

		}
		void rentBack()
		{

			//�����������ؼ�, ������ �����Ȳ����, rented��ŭ ȸ�������ش�.
			if ((owner.mibun == �ź�_��� || owner.mibun ==�ź�_����) && item.owner != owner.get_id())
			{
				//pk::printf("���:{}, rentBack:{},newOwner:{}\n",getName(owner), citem.name,getName(pk::get_person(item.owner)));
				for (int i = 0; i < rented.length; i++)
				{
					owner.base_stat[i] = owner.base_stat[i] + rented[i];
				}
				owner.update();
				citem.removeRent(item,pk::get_person(item.owner), owner0);
				//pk::printf("rentBack:{}\n", getName(pk::get_person(item.owner)));
			}
			else 
			{
				//pk::printf("rentBack:{},{}\n", citem.name, getName(item));
				citem.removeRent(item, owner0);
				//pk::printf("rentBack:{}\n", getName(pk::get_person(item.owner)));
			}

			if (����_��������_�α�ǥ��)
			{
				pk::force@ force = pk::get_force(owner.get_force_id());
				pk::person@ kunshu = force!=null ? pk::get_person(force.kunshu) : null;
				string str = pk::format("\x1b[2x{}\x1b[0x,\x1b[2x{}\x1b[0x�� \x1b[29x{}\x1b[0x �ݳ�", getName(owner), getName(owner0), getName(item));
				pk::history_log(kunshu!=null ? kunshu.get_pos() : pk::point(0,0), force != null ? force.color : 0, pk::encode(str));
			}
		}
		string getName(pk::object@ obj)
		{
			return obj != null ? pk::decode(pk::get_name(obj)) : "null";
		}


	}
	class ItemDisplay
	{
		CustomItem@ citem = null;
		pk::item@ item = null;
		pk::person@ owner = null;
		int itemCount = 0;
		string name;
		int value;
		string path;
	};


	class Main
	{
		pk::func203_t@ prev_callback_203�⺴�������;
		pk::func110_t@ prev_callback_110�����߰�Ȯ��;
		pk::func258_t@ prev_callback_258;
		pk::func202_t@ prev_callback_202;

		pk::func201_t@ prev_callback_201;
		pk::func209_t@ prev_callback_209;
		pk::func206_t@ prev_callback_206;

		pk::func200_t@ prev_callback_200;
		pk::func220_t@ prev_callback_220;

		pk::func214_t@ prev_callback_214;

		pk::func205_t@ prev_callback_205;
		pk::func207_t@ prev_callback_207;
		pk::func216_t@ prev_callback_216;


		pk::func164_t@ prev_callback_164;
		pk::func167_t@ prev_callback_167;
		pk::func100_t@ prev_callback_100;
		pk::func102_t@ prev_callback_102;
		pk::func103_t@ prev_callback_103;
		pk::func150_t@ prev_callback_150;
		pk::func152_t@ prev_callback_152;
		pk::func151_t@ prev_callback_151;
		pk::func153_t@ prev_callback_153;
		pk::func155_t@ prev_callback_155;

		Main()
		{
			@prev_callback_203�⺴������� = cast<pk::func203_t@>(pk::get_func(203));
			pk::reset_func(203);
			pk::set_func(203, pk::func203_t(callback203�⺴�������));

			@prev_callback_110�����߰�Ȯ�� = cast<pk::func110_t@>(pk::get_func(110));
			pk::reset_func(110);
			pk::set_func(110, pk::func110_t(callback110�����߰�Ȯ��));

			@prev_callback_258 = cast<pk::func258_t@>(pk::get_func(258));
			pk::reset_func(258);
			pk::set_func(258, pk::func258_t(callback258));

			@prev_callback_202 = cast<pk::func202_t@>(pk::get_func(202));
			pk::reset_func(202);
			pk::set_func(202, pk::func202_t(callback202));

			@prev_callback_205 = cast<pk::func205_t@>(pk::get_func(205));
			pk::reset_func(205);
			pk::set_func(205, pk::func205_t(callback205));

			@prev_callback_200 = cast<pk::func200_t@>(pk::get_func(200));
			pk::reset_func(200);
			pk::set_func(200, pk::func200_t(callback200));

			@prev_callback_214 = cast<pk::func214_t@>(pk::get_func(214));
			pk::reset_func(214);
			pk::set_func(214, pk::func214_t(callback214));

			@prev_callback_206 = cast<pk::func206_t@>(pk::get_func(206));
			pk::reset_func(206);
			pk::set_func(206, pk::func206_t(callback206));

			@prev_callback_207 = cast<pk::func207_t@>(pk::get_func(207));
			pk::reset_func(207);
			pk::set_func(207, pk::func207_t(callback207));

			@prev_callback_209 = cast<pk::func209_t@>(pk::get_func(209));
			pk::reset_func(209);
			pk::set_func(209, pk::func209_t(callback209));

			@prev_callback_201 = cast<pk::func201_t@>(pk::get_func(201));
			pk::reset_func(201);
			pk::set_func(201, pk::func201_t(callback201));

			@prev_callback_220 = cast<pk::func220_t@>(pk::get_func(220));
			pk::reset_func(220);
			pk::set_func(220, pk::func220_t(callback220));


			@prev_callback_167 = cast<pk::func167_t@>(pk::get_func(167));
			pk::reset_func(167);
			pk::set_func(167, pk::func167_t(callback167));

			@prev_callback_100 = cast<pk::func100_t@>(pk::get_func(100));
			pk::reset_func(100);
			pk::set_func(100, pk::func100_t(callback100));

			@prev_callback_102 = cast<pk::func102_t@>(pk::get_func(102));
			pk::reset_func(102);
			pk::set_func(102, pk::func102_t(callback102));

			@prev_callback_103 = cast<pk::func103_t@>(pk::get_func(103));
			pk::reset_func(103);
			pk::set_func(103, pk::func103_t(callback103));

			@prev_callback_150 = cast<pk::func150_t@>(pk::get_func(150));
			pk::reset_func(150);
			pk::set_func(150, pk::func150_t(callback150));

			@prev_callback_152 = cast<pk::func152_t@>(pk::get_func(152));
			pk::reset_func(152);
			pk::set_func(152, pk::func152_t(callback152));

			@prev_callback_151 = cast<pk::func151_t@>(pk::get_func(151));
			pk::reset_func(151);
			pk::set_func(151, pk::func151_t(callback151));

			@prev_callback_153 = cast<pk::func153_t@>(pk::get_func(153));
			pk::reset_func(153);
			pk::set_func(153, pk::func153_t(callback153));

			@prev_callback_155 = cast<pk::func155_t@>(pk::get_func(155));
			pk::reset_func(155);
			pk::set_func(155, pk::func155_t(callback155));

			@prev_callback_216 = cast<pk::func216_t@>(pk::get_func(216));
			pk::reset_func(216);
			pk::set_func(216, pk::func216_t(callback216));

			@prev_callback_164 = cast<pk::func164_t@>(pk::get_func(164));
			pk::reset_func(164);
			pk::set_func(164, pk::func164_t(callback164));


			pk::bind(102, pk::trigger102_t(onInit));
			pk::bind(105, pk::trigger105_t(saveData));
			pk::bind(107, pk::trigger107_t(onNewDay));
			pk::bind(174, pk::trigger174_t(onUnitEnd));
			//pk::bind(173, pk::trigger174_t(onUnitExp));
			pk::bind(111, pk::trigger111_t(onTurnStart));
			pk::bind(112, pk::trigger112_t(onTurnEnd));
			pk::bind(170, pk::trigger170_t(onUnitCreate));



			pk::menu_item �ź����϶�;
			�ź����϶�.menu = 2;
			�ź����϶�.is_enabled = pk::menu_item_is_enabled_t(isEnabled);
			�ź����϶�.get_desc = pk::menu_item_get_desc_t(getDesc_�ź����϶�);
			�ź����϶�.get_text = pk::menu_item_get_text_t(getText_�ź����϶�);
			�ź����϶�.handler = pk::menu_item_handler_t(handler_�ź����϶�);
			pk::add_menu_item(�ź����϶�);


			pk::menu_item �ź�������;
			�ź�������.menu = 102;
			�ź�������.pos = 5;
			�ź�������.init = pk::building_menu_item_init_t(�ź�������Init);
			�ź�������.is_enabled = pk::menu_item_is_enabled_t(Is�ź�������Enabled);
			�ź�������.get_text = pk::menu_item_get_text_t(�ź�������Text);
			�ź�������.get_desc = pk::menu_item_get_desc_t(�ź�������Desc);
			�ź�������.handler = pk::menu_item_handler_t(�ź�������Handler);
			pk::add_menu_item(�ź�������);


		}

		array<ItemRent@> _rent;
		pk::list<pk::person@> ����ڸ���Ʈ;
		array<pk::person@> _attackers;
		array<pk::person@> _defenders;


		void onInit()
		{
			for (int i = 0; i < Ŀ���Ҿ����۽�.length; i++)
			{
				CustomItem@ ci = Ŀ���Ҿ����۽�[i];
				@ci.owner = null;
			}

			if (!loadData())
			{
				for (int i = 0; i < Ŀ���Ҿ����۽�.length; i++)
				{
					CustomItem@ ci = Ŀ���Ҿ����۽�[i];
					if(ci==null || ci.fowner ==null)
						continue;

					pk::person@ o = ci.fowner;
					@ci.owner = null;
					ci.updateOwner(o);
				}
			}

			//for (int i = 0; i < Ŀ���Ҿ����۽�.length; i++)
			//{
			//	CustomItem@ ci = Ŀ���Ҿ����۽�[i];
			//	pk::printf("�ź���:{}\n", getName(ci.owner));
			//}

			exportItem();
		}
		bool loadData()
		{
			����ڸ���Ʈ.clear();
			_attackers = {};
			_defenders = {};

			int count = int(pk::load(KEY, 0, 0));
			int li = 1;
			if (count == 0)
				return false;



			for (int i = 0; i < count; i++)
			{
				CustomItem@ ci = Ŀ���Ҿ����۽�[i];
				int oid = int(pk::load(KEY, li++, -1));
				if(ci!=null)
					@ci.owner = pk::get_person(oid);
			}

			int count2 = int(pk::load(KEY, li++, 0));
			_rent = {};
			
			for (int i = 0; i < count2; i++)
			{
				int cid = int(pk::load(KEY, li++, -1));
				int iid = int(pk::load(KEY, li++, -1));
				int oid0 = int(pk::load(KEY, li++, -1));
				int oid1 = int(pk::load(KEY, li++, -1));

				int len = int(pk::load(KEY, li++, -1));
				array<int> rented(len, 0);
				for (int j = 0; j < len; j++)
					rented[j] = int(pk::load(KEY, li++, 0));

				ItemRent ir;
				@ir.citem = Ŀ���Ҿ����۽�[cid];
				@ir.item = pk::get_item(iid);
				@ir.owner0 = pk::get_person(oid0);
				@ir.owner = pk::get_person(oid1);
				ir.rented = rented;
				_rent.insertLast(ir);
			}

			int count3 = int(pk::load(KEY, li++, 0));
			for (int i = 0; i < count3; i++)
			{
				int pp = int(pk::load(KEY, li++, -1));
				pk::person@ p = pp >= 0 ? pk::get_person(pp) : null;
				if (p == null)
					continue;
				����ڸ���Ʈ.add(p);
			}
			int count5 = int(pk::load(KEY, li++, 0));
			for (int i = 0; i < count5; i++)
			{
				int p0 = int(pk::load(KEY, li++, -1));
				int p1 = int(pk::load(KEY, li++, -1));
				if (p0 < 0 || p1 < 0)
					continue;
				pk::person@ pp0 = p0 >= 0 ? pk::get_person(p0) : null;
				pk::person@ pp1 = p1 >= 0 ? pk::get_person(p1) : null;
				if (pp0 == null || pp1 == null)
					continue;

				_attackers.insertLast(pp0);
				_defenders.insertLast(pp1);
			}

			_turnCount = int(pk::load(KEY, li++, 0));
			return true;
		}
		void saveData(int fd)
		{
			pk::store(KEY, 0, Ŀ���Ҿ����۽�.length);
			int si = 1;
			for (int i = 0; i < Ŀ���Ҿ����۽�.length; i++)
			{
				CustomItem@ ci = Ŀ���Ҿ����۽�[i];
				pk::store(KEY, si++, (ci!=null && ci.owner!=null) ? ci.owner.get_id() : -1);
			}

			pk::store(KEY, si++, _rent.length);
			for (int i = 0; i < _rent.length; i++)
			{
				ItemRent@ ir = _rent[i];
				pk::store(KEY, si++, ir.citem.id);
				pk::store(KEY, si++, ir.item.get_id());
				pk::store(KEY, si++, ir.owner0 != null ? ir.owner0.get_id() : -1);
				pk::store(KEY, si++, ir.owner != null ? ir.owner.get_id() : -1);
				pk::store(KEY, si++, ir.rented.length);
				for (int j = 0; j < ir.rented.length; j++)
				{
					pk::store(KEY, si++, ir.rented[j]);
				}
			}

			pk::store(KEY, si++, ����ڸ���Ʈ.count);
			for (int i = 0; i < ����ڸ���Ʈ.count; i++)
			{
				pk::store(KEY, si++, ����ڸ���Ʈ[i].get_id());
			}
			pk::store(KEY, si++, _attackers.length);
			for (int i = 0; i < _attackers.length; i++)
			{
				pk::store(KEY, si++, _attackers[i].get_id());
				pk::store(KEY, si++, _defenders[i].get_id());
			}

			pk::store(KEY, si++, _turnCount);
		}
		void exportItem()
		{
			pk::store(KEY_EXPORT, 0, Ŀ���Ҿ����۽�.length);
			int si = 1;
			for (int i = 0; i < Ŀ���Ҿ����۽�.length; i++)
			{
				CustomItem@ ci = Ŀ���Ҿ����۽�[i];
				pk::store(KEY_EXPORT, si++, (ci != null && ci.owner != null) ? ci.owner.get_id() : -1);
			}
		}

		void giveItems_��å(CustomItem@ item, pk::force@ force)
		{
			pk::list<pk::person@> persons0 = pk::get_person_list(force, pk::mibun_flags(�ź�_����, �ź�_����, �ź�_�¼�, �ź�_�Ϲ�));
			pk::list<pk::person@> persons;

			for (int i = 0; i < persons0.count; i++)
			{
				pk::person@ p = persons0[i];
				if (p.mibun != �ź�_���� && (hasCustomItemType(p, item.type) || hasItemType(p, item.type)))
					continue;
				if (p.get_id() >= ����_���� && p.get_id() <= ����_�̺�ƮA0 || p.get_id() >= ����_����)
					continue;

				if (p.mibun == �ź�_����)
				{
					int count0 = hasCustomItemTypeCount(p, item.type);
					int count1 = hasItemTypeCount(p, item.type);
					if (count0 + count1 > 1)
						continue;
				}

				persons.add(p);
			}

			if (persons.count > 0)
			{
				persons.sort(function(x, y) {
					int sumX = x.stat[����ɷ�_����] + x.stat[����ɷ�_��ġ];
					int sumY = y.stat[����ɷ�_����] + y.stat[����ɷ�_��ġ];
					return sumX >= sumY;
				});
			}

			//���ְ� ����3�ο� ������ ������ ���ֿ���.
			pk::person@ target = null;
			if (persons.count > 0 && persons[0].mibun == �ź�_����)
				@target = persons[0];
			if (target == null && persons.count > 1 && persons[1].mibun == �ź�_����)
				@target = persons[1];
			if (target == null && persons.count > 2 && persons[2].mibun == �ź�_����)
				@target = persons[2];


			pk::list<pk::person@> person2;

			if (target == null)
			{
				if (persons.count > 0)
					person2.add(persons[0]);
				if (persons.count > 1)
					person2.add(persons[1]);
				if (persons.count > 2)
					person2.add(persons[2]);
				person2.shuffle();
				@target = person2[0];
			}

			if (target.mibun == �ź�_����)
				return;

			pk::person@ kunshu = pk::get_person(force.kunshu);
			string str = pk::format("\x1b[2x{}��\x1b[0x,�ź��� \x1b[29x{}\x1b[0x ,\x1b[2x{}\x1b[0x ���� �ϻ�", getName(kunshu), item.name, getName(target));
			pk::history_log(kunshu != null ? kunshu.get_pos() : pk::point(0, 0), force.color, pk::encode(str));

			item.updateOwner(target);
		}

		void giveItems_��_â_Ȱ_�ϱ�_��(CustomItem@ item, pk::force@ force)
		{
			pk::list<pk::person@> persons0 = pk::get_person_list(force, pk::mibun_flags(�ź�_����, �ź�_����, �ź�_�¼�, �ź�_�Ϲ�));
			pk::list<pk::person@> persons;

			for (int i = 0; i < persons0.count; i++)
			{
				pk::person@ p = persons0[i];
				if(p.mibun != �ź�_���� && (hasCustomItemType(p,item.type) || hasItemType(p,item.type)))
					continue;
				if (p.get_id() >= ����_���� && p.get_id() <= ����_�̺�ƮA0 || p.get_id() >= ����_����)
					continue;

				if (p.mibun == �ź�_����)
				{
					int count0 = hasCustomItemTypeCount(p, item.type);
					int count1 = hasItemTypeCount(p, item.type);
					if(count0 + count1 > 1)
						continue;
				}

				persons.add(p);
			}

			if (persons.count > 0)
			{
				persons.sort(function(x, y) {
					int sumX = x.stat[����ɷ�_����] + x.stat[����ɷ�_���];
					int sumY = y.stat[����ɷ�_����] + y.stat[����ɷ�_���];
					return sumX >= sumY;
				});
			}

			//���ְ� ����3�ο� ������ ������ ���ֿ���.
			pk::person@ target = null;
			if (persons.count > 0 && persons[0].mibun == �ź�_����)
				@target = persons[0];
			if (target==null && persons.count > 1 && persons[1].mibun == �ź�_����)
				@target = persons[1];
			if (target == null && persons.count > 2 && persons[2].mibun == �ź�_����)
				@target = persons[2];


			pk::list<pk::person@> person2;

			if (target == null)
			{
				if (persons.count > 0)
					person2.add(persons[0]);
				if (persons.count > 1)
					person2.add(persons[1]);
				if (persons.count > 2)
					person2.add(persons[2]);
				person2.shuffle();
				@target = person2[0];
			}

			if (target.mibun == �ź�_����)
				return;

			pk::person@ kunshu = pk::get_person(force.kunshu);
			string str = pk::format("\x1b[2x{}��\x1b[0x,�ź��� \x1b[29x{}\x1b[0x ,\x1b[2x{}\x1b[0x ���� �ϻ�", getName(kunshu), item.name, getName(target));
			pk::history_log(kunshu != null ? kunshu.get_pos() : pk::point(0, 0), force.color, pk::encode(str));
			
			item.updateOwner(target);

		}

		void ����ó��()
		{
			for (int i = 0; i < ����_��; i++)
			{
				pk::person@ p = pk::get_person(i);
				if (p == null)
					continue;
				if (p.mibun != �ź�_����)
					continue;
				array<CustomItem@> arr = getCustomItem(p);
				if (arr.length == 0)
					continue;

				pk::unit@ u = getUnit(p.get_pos());
				if(u==null)
					continue;
				for (int j = 0; j < arr.length; j++)
				{
					CustomItem@ ci = arr[j];
					pk::person@ kunshu = pk::get_person(pk::get_force(u.get_force_id()).kunshu);
					@_scene_citem_��Ż = ci;
					@_scene_kunshu_��Ż = kunshu;
					@_scene_item_��Ż = null;
					try
					{
						pk::scene(pk::scene_t(scene_����_��Ż));
					}
					catch
					{
					}
					ci.updateOwner(kunshu);
				}
			}
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


				array<CustomItem@> arr=getCustomItem(p);
				if(arr.length == 0)
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
				if (bFound)
					continue;
				
				bFound = false;

				for (int j = _defenders.length - 1; j >= 0; j--)
				{
					pk::person@ p2 = _defenders[j];
					if (p.get_id() != p2.get_id())
						continue;


					for (int k = 0; k < arr.length; k++)
					{
						CustomItem@ ci = arr[k];
						pk::person@ kunshu = pk::get_person(pk::get_force(_attackers[j].get_force_id()).kunshu);
						@_scene_citem_��Ż = ci;
						@_scene_kunshu_��Ż = kunshu;
						@_scene_item_��Ż = null;
						try
						{
							pk::scene(pk::scene_t(scene_����_��Ż));
						}
						catch
						{

						}

						ci.updateOwner(kunshu);
						bFound = true;
					}

					break;
				}
				if (!bFound)
				{
					for (int k = 0; k < arr.length; k++)
					{
						CustomItem@ ci = arr[k];

						@_scene_citem_��Ż = ci;
						@_scene_item_��Ż = null;
						try
						{
							pk::scene(pk::scene_t(scene_����_���));
						}
						catch
						{
						}

						ci.updateOwner(null);
					}
				}
			}
		}

		void onNewDay()
		{
			_turnCount = 0;
			�����ó��();
			for (int i = 0; i < Ŀ���Ҿ����۽�.length; i++)
			{
				CustomItem@ item = Ŀ���Ҿ����۽�[i];
				if (item == null || item.owner == null)
					continue;
				if(item.owner.mibun != �ź�_����)
					continue;
				if(item.owner.is_player())
					continue;

				if(item.type == ��������_��å)
					giveItems_��å(item, pk::get_force(item.owner.get_force_id()));
				else
					giveItems_��_â_Ȱ_�ϱ�_��(item, pk::get_force(item.owner.get_force_id()));
			}

			while (_attackers.length > 0)
				_attackers.removeAt(0);
			while (_defenders.length > 0)
				_defenders.removeAt(0);


			����ڸ���Ʈ.clear();
			for (int i = 0; i < ����_��; i++)
			{
				pk::person@ p = pk::get_person(i);
				if (p == null)
					continue;

				if (p.mibun != �ź�_���)
					continue;
				����ڸ���Ʈ.add(p);
			}
		}

		bool updateRentArea(array<ItemRent@>@ arr, CustomItem@ it,pk::person@ p,pk::list<pk::force@> forces)
		{
			pk::list<pk::item@> items;
			for (int i = 0; i < ����_��; i++)
			{
				pk::item@ it0 = pk::get_item(i);
				if(it0==null)
					continue;
				if(it0.type==-1)
					continue;
				if(it0.type != it.type)
					continue;
				if(it0.status == ��������_�̵��� || it0.status == ��������_�ı�)
					continue;

				bool bFound = false;
				for (int j = 0; j < arr.length; j++)
				{
					if (arr[j].item.get_id() == it0.get_id())
					{
						bFound = true;
						break;
					}
				}
				if (!bFound)
					items.add(it0);
			}

			for (int i = 0; i < items.count; i++)
			{
				pk::item@ it0 = items[i];
				if (it0.get_id() == it.srcItem)
				{
					pk::person@ owner = null;
					if (it0.owner != -1)
					{
						@owner = pk::get_person(it0.owner);
						if (pk::is_unitize(owner))
						{
							int dist = pk::get_distance(p.get_pos(), owner.get_pos());
							if(dist <= ������_����_�Ÿ� || p.get_force_id() == owner.get_force_id())
								continue;
							bool bFound2 = false;
							for (int j = 0; j < forces.count; j++)
							{
								if (forces[j].get_id() == owner.get_force_id())
								{
									bFound2 = true;
									break;
								}
							}
							if(bFound2)
								continue;
						}
					}

					ItemRent ir0;
					@ir0.citem = it;
					@ir0.item = it0;
					@ir0.owner = p;
					@ir0.owner0 = owner;
					arr.insertLast(ir0);
					return true;
				}
			}


			int minOff = 1000;
			pk::item@ minItem = null;
			for (int i = 0; i < items.count; i++)
			{
				pk::item@ it0 = items[i];
				pk::person@ owner = pk::get_person(it0.owner);
				if (owner != null)
				{
					if (pk::is_unitize(owner))
					{
						int dist = pk::get_distance(p.get_pos(), owner.get_pos());
						if (dist <= ������_����_�Ÿ� || p.get_force_id() == owner.get_force_id())
							continue;

						bool bFound2 = false;
						for (int j = 0; j < forces.count; j++)
						{
							if (forces[j].get_id() == owner.get_force_id())
							{
								bFound2 = true;
								break;
							}
						}
						if (bFound2)
							continue;

					}
				}


				int off1 = pk::abs(it0.value - it.value);
				if (off1 < minOff)
				{
					@minItem = it0;
					minOff = off1;
				}
			}

			if (minItem == null)
				return false;

			ItemRent ir;
			@ir.citem = it;
			@ir.item = minItem;
			@ir.owner = p;
			@ir.owner0 = pk::get_person(minItem.owner);
			arr.insertLast(ir);
			return true;
		}

		void updateRent(pk::person@ p, array<ItemRent@>@ rent,pk::list<pk::force@> forces)
		{
			if (p == null)
				return;
			array<CustomItem@> arr = getCustomItem(p);
			if (arr.length == 0)
				return;

			arr.sort(function(a, b) { return a.value >= b.value; });
			array<int> types;
			for (int i = 0; i < ����_��; i++)
			{
				pk::item@ it = pk::get_item(i);
				if(it==null)
					continue;
				if (it.owner == p.id)
				{
					if(types.find(it.type) == -1)
						types.insertLast(it.type);
				}
			}

			for (int j = 0; j < arr.length; j++)
			{
				CustomItem@ it = arr[j];
				if (types.find(it.type) != -1)
					continue;
				if (it.type == ��������_��å || it.type == ��������_���� || it.type == ��������_����)
					continue;

				bool bFound = false;
				for (int i = 0; i < rent.length; i++)
				{
					ItemRent@ ir = rent[i];
					if (ir.citem.id == it.id)
					{
						bFound = true;
					}
				}
				if(bFound)
					continue;

				if (updateRentArea(rent, it, p,forces))
					types.insertLast(it.type);
				
			}
		}

		ItemRent@ getRent(CustomItem@ ci)
		{
			for (int i = 0; i < _rent.length; i++)
			{
				ItemRent@ ir = _rent[i];
				if (ir.citem.id == ci.id)
					return ir;
			}
			return null;
		}
		void removeRent(ItemRent@ ir)
		{
			ir.rentBack();

			int a=_rent.findByRef(ir);
			_rent.removeAt(a);
			
		}

		void onTurnStart(pk::force@ f)
		{
			for (int i = 0; i < _rent.length; i++)
			{
				ItemRent@ ir = _rent[i];
				ir.rentBack();
			}
			_rent = {};

			������_ó��();
			_attackersPerson���� = {};
			_targetrsPerson���� = {};


			//pk::printf("onTurnStart:{}\n", getName(f));
			exportItem();
			array<pk::person@> ps;
			array<ItemRent@> rent;
			pk::list<pk::person@> persons = pk::get_person_list(f,pk::mibun_flags(�ź�_����, �ź�_����, �ź�_�¼�, �ź�_�Ϲ�));
			if (����_��������)
			{
				pk::list<pk::force@> fs2;
				fs2.add(f);
				pk::list<pk::force@> fs;
				pk::list<pk::unit@> us = pk::get_unit_list(f);
				for (int i = 0; i <us.count ; i++)
				{
					pk::unit@ u = us[i];
					array<pk::point> arr = pk::range(u.get_pos(), 1, ������_����_�Ÿ�_����);
					for (int j = 0; j < arr.length; j++)
					{
						pk::point pt = arr[j];
						pk::unit@ u2 = getUnit(pt);
						if(u2 == null || !pk::is_enemy(u,u2))
							continue;

						pk::force@ f2 = pk::get_force(u2.get_force_id());
						if(f2==null)
							continue;

						bool bFound = false;
						for (int k = 0; k < fs.count; k++)
						{
							pk::force@ ff = fs[k];
							if (ff.get_id() == f2.get_id())
							{
								bFound = true;
								break;
							}
						}
						if (!bFound)
							fs.add(f2);
					}
				}
				
				
				for (int i = 0; i < persons.count; i++)
				{
					pk::person@ p = persons[i];
					pk::unit@ u = getUnit(p.get_pos());
					if (u == null)
						continue;

					updateRent(p, rent,fs);
					ps.insertLast(p);

					array<pk::point> pts = pk::range(u.get_pos(), 1, ������_����_�Ÿ�_����);
					for (int j = 0; j < pts.length; j++)
					{
						pk::point pt = pts[j];
						pk::unit@ u2 = getUnit(pt);
						if (u2 == null || !pk::is_enemy(u, u2))
							continue;
						pk::person@ p0 = pk::get_person(u2.member[0]);
						pk::person@ p1 = pk::get_person(u2.member[1]);
						pk::person@ p2 = pk::get_person(u2.member[2]);
						if (p0 != null && ps.findByRef(p0) == -1)
						{
							updateRent(p0, rent,fs2);
							ps.insertLast(p0);
						}
						if (p1 != null && ps.findByRef(p1) == -1)
						{
							updateRent(p1, rent,fs2);
							ps.insertLast(p1);
						}
						if (p2 != null && ps.findByRef(p2) == -1)
						{
							updateRent(p2, rent,fs2);
							ps.insertLast(p2);
						}
					}
				}
			}
			for (int i = 0; i < rent.length; i++)
			{
				ItemRent@ ir = rent[i];
				ir.rent();
			}
			_rent = rent;


			pk::list<pk::unit@> units = pk::get_unit_list(f);
			for (int i = 0; i < units.count; i++)
			{
				pk::unit@ u = units[i];
				onTurn�־�(u);
				onTurn�־�_����Ư��(u);
				onTurn����_ȭ��(u);
				onTurn����_����_ȸ��(u);
				//onTurn����_����_����(u);
			}
			onTurn�ⱳ����Ʈ(f);
		}
		pk::person@ _scene_attacker = null;
		pk::person@ _scene_target = null;
		pk::unit@ _scene_attackerUnit = null;
		pk::unit@ _scene_targetUnit = null;

		void scene_�ϱ���()
		{
			pk::message_box(pk::encode("������ ã�Ҵ�"), _scene_attacker);
			pk::message_box(pk::encode("���� ��ȸ�ϰ� �ɰ��̴�"), _scene_target);

			bool b0 = pk::is_player_controlled(_scene_attackerUnit);
			bool b1 = pk::is_player_controlled(_scene_targetUnit);

			pk::duel(_scene_attackerUnit, _scene_targetUnit, _scene_attacker, null, null, _scene_target, null, null, b0, b1, 0, b0 || b1).first;
		}

		int _turnCount = 0;
		void onTurnEnd(pk::force@ f)
		{
			//pk::printf("onTurnEnd:{},{}\n", _turnCount++, getName(f));
			pk::list<pk::unit@> units = pk::get_unit_list(f);
			for (int i = 0; i < units.count; i++)
			{
				pk::unit@ unit = units[i];
				if(!has����skill(unit, ����Ư��_�ϱ���_����))
					continue;

				for (int j = 0; j < 6; j++)
				{
					pk::point pt = pk::get_neighbor_pos(unit.get_pos(), j, 1);
					pk::unit@ unit2 = getUnit(pt);
					if (unit2 == null || !pk::is_enemy(unit, unit2))
						continue;
					if (!pk::rand_bool(�ϱ���_����_Ȯ��))
						continue;
					if(pk::get_person(unit2.leader).stat[����ɷ�_����] > pk::get_person(unit.leader).stat[����ɷ�_����] + �ϱ���_ȸ��_����_��)
						continue;

					@_scene_attackerUnit = unit;
					@_scene_targetUnit = unit2;
					@_scene_attacker = pk::get_person(unit.leader);
					@_scene_target = pk::get_person(unit2.leader);
					pk::scene(pk::scene_t(scene_�ϱ���));
					break;
				}
			}

			if (pk::get_force_list(true).count == _turnCount)
			{
				//pk::printf("onTurnEnd clear\n");
				for (int i = 0; i < _rent.length; i++)
				{
					ItemRent@ ir = _rent[i];
					ir.rentBack();
				}
				_rent = {};
			}

			_attackers���� = {};
			_targets���� = {};
			_damages���� = {};
			_points���� = {};

			for (int i = 0; i < units.count; i++)
			{
				pk::unit@ u = units[i];
				onTurn����_ȭ��(u);
				//onTurn����_����_����(u);
			}

			onTurn����_����_����AI(f);
			����ó��();
			//pk::printf("onTurnEnd:{}\n", getName(f));
		}

		void onTurn����_����_����AI(pk::force@ f)
		{
			pk::list<pk::unit@> us = pk::get_unit_list(f);

			pk::list<pk::unit@> already;
			for (int i = 0; i < us.count; i++)
			{
				pk::unit@ u = us[i];
				if(!pk::is_valid_pos(u.get_pos()))
					continue;

				array<pk::point> arr = pk::range(u.get_pos(),1,5);
				for (int j = 0; j < arr.length; j++)
				{
					pk::point pt = arr[j];
					pk::unit@ u2 = pk::is_valid_pos(pt) ? pk::get_unit(pt) : null;
					if (u2 == null)
						continue;
					bool bFound = false;
					for (int k = 0; k < already.count; k++)
					{
						pk::unit@ uu = already[k];
						if(uu.get_id() != u2.get_id())
							continue;

						bFound = true;
						break;
					}
					if(bFound)
						continue;

					if(!onTurn����_����_����(u2))
						continue;
					already.add(u2);
				}
			}
		}

		bool onTurn����_����_����(pk::unit@ u)
		{
			if (!has����skill(u, ����Ư��_����_ȥ��_����_����))
				return false;

			array<pk::point> pts = pk::range(u.get_pos(), 0, ����_ȥ��_����_ȸ��_����);
			for (int i = 0; i < pts.length; i++)
			{
				pk::point pt = pts[i];
				pk::unit@ unit = getUnit(pt);
				if(unit==null || pk::is_enemy(u,unit))
					continue;

				if (unit.status != �δ����_���)
				{
					//pk::create_effect(0x3c, unit.get_pos());
					create_effect(0x3c, unit.get_pos());
					pk::set_status(unit, u, �δ����_���, 0);
					pk::set_action_done(u, false);
					u.action_done = false;
					u.update();
					pk::say(pk::encode("�� ��Ҽ�"), pk::get_person(unit.leader), unit);
				}
			}
			return true;
		}
		void onTurn����_ȭ��(pk::unit@ u)
		{
			if (!has����skill(u, ����Ư��_����_ȭ��_��ȭ))
				return;

			array<pk::point> pts = pk::range(u.get_pos(), 0, ����_��ȭ_����);
			for (int i = 0; i < pts.length; i++)
			{
				pk::point pt = pts[i];
				pk::unit@ unit = getUnit(pt);
				if (unit == null || pk::is_enemy(u, unit))
					continue;
				if(!pk::is_on_fire(pt))
					continue;
				//pk::printf("{},ȭ��0\n", getNameLeader(unit));
				create_effect(0x3b, pt);
				pk::get_hex(pt).fire_timer = 0;
			}
		}
		void onTurn����_����_ȸ��(pk::unit@ u)
		{
			if (!has����skill(u, ����Ư��_����_ȸ��))
				return;


			array<pk::point> pts = pk::range(u.get_pos(), 0, ����_ȸ��_����);
			for (int i = 0; i < pts.length; i++)
			{
				pk::point pt = pts[i];
				pk::unit@ unit = getUnit(pt);
				if (unit == null || pk::is_enemy(u, unit))
					continue;

				pk::add_troops(unit, ����_����_ȸ����, true);
			}
		}

		void onTurn�ⱳ����Ʈ(pk::force@ f)
		{
			pk::list<pk::person@> persons = pk::get_person_list(f, pk::mibun_flags(�ź�_����, �ź�_����, �ź�_�¼�, �ź�_�Ϲ�));
			bool b = false;

			for (int i = 0; i < persons.count; i++)
			{
				pk::person@ p = persons[i];
				if (has����skill(p, ����Ư��_�ⱳ����Ʈ_ȹ��))
				{
					b = true;
					break;
				}
			}
			if (b)
			{
				pk::add_tp(f, �ϴ�_�ⱳ����Ʈ, pk::get_person(f.kunshu).get_pos());
			}

			b = false;
			for (int i = 0; i < persons.count; i++)
			{
				pk::person@ p = persons[i];
				if (has����skill(p, ����Ư��_�ɷ¿����ӵ����))
				{
					b = true;
					break;
				}
			}
			if (b)
			{
				if(f.researching_ability_timer >1)
					f.researching_ability_timer--;
			}

		}


		void onTurn�־�(pk::unit@ u)
		{
			if (u.has_skill(Ư��_�־�))
				return;
			if (!hasCustomItemSkill(u, Ư��_�־�))
				return;

			pk::person@ l = pk::get_person(u.leader);
			int bskill = l.skill;

			setSkill(l, Ư��_�־�);
			pk::add_energy(u, int(pk::core::skill_constant(l.get_id(), Ư��_�־�)), true);
			resetSkill(l, bskill);
		}


		void onTurn�־�_����Ư��(pk::unit@ u)
		{
			if (!has����skill(u, ����Ư��_�־�))
				return;
			pk::add_energy(u, �־�_���, true);
		}


		bool hasCustomItem(pk::person@ p)
		{
			for (int i = 0; i < Ŀ���Ҿ����۽�.length; i++)
			{
				CustomItem@ ci = Ŀ���Ҿ����۽�[i];
				if(ci!=null)
					continue;
				if (ci.owner == null)
					continue;
				if (ci.owner.get_id() == p.get_id())
					return true;
			}
			return false;
		}

		bool hasCustomItemType(pk::person@ p, int type)
		{
			for (int i = 0; i < Ŀ���Ҿ����۽�.length; i++)
			{
				CustomItem@ ci = Ŀ���Ҿ����۽�[i];
				if (ci != null)
					continue;
				if (ci.owner == null)
					continue;
				if (ci.owner.get_id() != p.get_id())
					continue;

				if (ci.type == type)
					return true;
			}
			return false;

		}
		int hasCustomItemTypeCount(pk::person@ p, int type)
		{
			int count = 0;
			for (int i = 0; i < Ŀ���Ҿ����۽�.length; i++)
			{
				CustomItem@ ci = Ŀ���Ҿ����۽�[i];
				if (ci != null)
					continue;
				if (ci.owner == null)
					continue;
				if (ci.owner.get_id() != p.get_id())
					continue;

				if (ci.type == type)
					count++;
			}
			return count;

		}

		bool hasItemType(pk::person@ p, int type)
		{
			for (int i = 0; i < ����_��; i++)
			{
				pk::item@ it = pk::get_item(i);
				if(it==null)
					continue;
				if(it.type==-1)
					continue;
				if(it==null || it.owner != p.get_id())
					continue;

				if (it.type == type)
					return true;
			}
			return false;
		}
		int hasItemTypeCount(pk::person@ p, int type)
		{
			int count = 0;
			for (int i = 0; i < ����_��; i++)
			{
				pk::item@ it = pk::get_item(i);
				if (it == null || it.owner != p.get_id())
					continue;
				if (it.type == -1)
					continue;

				if (it.type == type)
					count++;
			}
			return count;

		}

		bool hasCustomItemSkill(pk::unit@ u, int skill)
		{
			pk::person@ p0 = pk::get_person(u.member[0]);
			pk::person@ p1 = pk::get_person(u.member[1]);
			pk::person@ p2 = pk::get_person(u.member[2]);

			return hasCustomItemSkill(p0, skill) || hasCustomItemSkill(p1, skill) || hasCustomItemSkill(p2, skill);
		}

		bool hasCustomItemSkill(pk::person@ p,int skill)
		{
			if (p == null)
				return false;
			for (int i = 0; i < Ŀ���Ҿ����۽�.length; i++)
			{
				CustomItem@ ci = Ŀ���Ҿ����۽�[i];
				if(ci==null)
					continue;
				if (ci.owner == null)
					continue;
				if (ci.owner.get_id() != p.get_id())
					continue;

				for (int j = 0; j < ci.skills.length; j++)
				{
					if (skill == ci.skills[j])
						return true;
				}
			}
			return false;
		}



		array<CustomItem@> getCustomItem(pk::unit@ u)
		{
			array<CustomItem@> arr;
			for (int i = 0; i < Ŀ���Ҿ����۽�.length; i++)
			{
				CustomItem@ ci = Ŀ���Ҿ����۽�[i];
				if (ci == null)
					continue;
				if (ci.owner == null)
					continue;
				
				if (ci.owner.get_id() == u.member[0])
				{
					arr.insertLast(ci);
				}
				if (ci.owner.get_id() == u.member[1])
				{
					arr.insertLast(ci);
				}
				if (ci.owner.get_id() == u.member[2])
				{
					arr.insertLast(ci);
				}
			}
			return arr;
		}
		array<CustomItem@> getCustomItem(pk::person@ p)
		{
			array<CustomItem@> arr;
			for (int i = 0; i < Ŀ���Ҿ����۽�.length; i++)
			{
				CustomItem@ ci = Ŀ���Ҿ����۽�[i];
				if(ci==null)
					continue;
				if (ci.owner == null)
					continue;
				if (ci.owner.get_id() == p.get_id())
				{
					arr.insertLast(ci);
				}
			}
			return arr;
		}
		array<pk::item@> getItem(pk::person@ p)
		{
			array<pk::item@> arr;
			for (int i = 0; i < ����_��; i++)
			{
				pk::item@ ci = pk::get_item(i);
				if(ci==null)
					continue;
				if(ci.type == -1)
					continue;
				if (ci.owner == -1)
					continue;
				if (ci.owner == p.get_id())
				{
					arr.insertLast(ci);
				}
			}
			return arr;
		}


		void ������_ó��(pk::person@ p, pk::force@ f)
		{
			if (p.hp != 1 || p.order != �����ӹ�_��ȯ || p.mibun == �ź�_���� || p.mibun == �ź�_���)
				return;
			if (f == null)
				return;
			pk::person@ kunshu = pk::get_person(f.kunshu);
			if (kunshu == null)
				return;

			pk::printf("������:{},���:{}\n", getName(p), getName(f));
			array<CustomItem@> arr = getCustomItem(p);
			if (arr.length == 0)
				return;

			for (int k = 0; k < arr.length; k++)
			{
				CustomItem@ ci = arr[k];
				ItemRent@ ir = getRent(ci);
				if (ir != null)
					removeRent(ir);

				pk::person@ kunshu = kunshu;
				@_scene_citem_��Ż = ci;
				@_scene_kunshu_��Ż = kunshu;
				@_scene_item_��Ż = null;
				try
				{
					pk::scene(pk::scene_t(scene_����_��Ż));
				}
				catch
				{
				}
				ci.updateOwner(kunshu);
			}
		}

		void ������_ó��()
		{
			for (int i = 0; i < _attackersPerson����.length; i++)
			{
				pk::list<pk::person@> ps0 = _attackersPerson����[i];
				pk::list<pk::person@> ps1 = _targetrsPerson����[i];
				if(ps0.count == 0 || ps1.count == 0)
					continue;
				for (int j = 0; j < ps0.count; j++)
				{
					������_ó��(ps0[j], pk::get_force(ps1[0].get_force_id()));
				}

				for (int j = 0; j < ps1.count; j++)
				{
					������_ó��(ps1[j], pk::get_force(ps0[0].get_force_id()));
				}
			}
		}

		CustomItem@ _scene_citem_��Ż = null;
		pk::item@ _scene_item_��Ż = null;
		pk::person@ _scene_kunshu_��Ż = null;

		void scene_����_��Ż()
		{
			string path;
			path = _scene_citem_��Ż != null ? _scene_citem_��Ż.path : �����̹���[_scene_item_��Ż.get_id()];
			if (_scene_kunshu_��Ż.is_player())
			{
				pk::background(pk::format("{}", path));
				if(_scene_citem_��Ż != null)
					pk::message_box(pk::encode(pk::format("�ź��� \x1b[29x{}\x1b[0x ������ϴ�.", _scene_citem_��Ż.name)));
				else
					pk::message_box(pk::encode(pk::format("���� \x1b[29x{}\x1b[0x ������ϴ�.", getName(_scene_item_��Ż))));

			}

			pk::force@ force = pk::get_force(_scene_kunshu_��Ż.get_force_id());

			string str = "";
			if (_scene_citem_��Ż != null)
				str = pk::format("\x1b[2x{}��\x1b[0x,�ź��� \x1b[29x{}\x1b[0x ȹ��", getName(_scene_kunshu_��Ż), _scene_citem_��Ż.name);
			else
				str = pk::format("\x1b[2x{}��\x1b[0x,���� \x1b[29x{}\x1b[0x ȹ��", getName(_scene_kunshu_��Ż), getName(_scene_item_��Ż));

			pk::history_log(_scene_kunshu_��Ż != null ? _scene_kunshu_��Ż.get_pos() : pk::point(0, 0), force.color, pk::encode(str));

			if(_scene_kunshu_��Ż.is_player())
				pk::background(-1);
		}

		void scene_����_���()
		{
			string path;
			path = _scene_citem_��Ż != null ? _scene_citem_��Ż.path : �����̹���[_scene_item_��Ż.get_id()];
			pk::background(pk::format("{}", path));
			if (_scene_citem_��Ż != null)
				pk::message_box(pk::encode(pk::format("�ź��� \x1b[29x{}\x1b[0x ���", _scene_citem_��Ż.name)));
			else
				pk::message_box(pk::encode(pk::format("���� \x1b[29x{}\x1b[0x ���", getName(_scene_item_��Ż))));

			string str = "";
			if (_scene_citem_��Ż != null)
				str = pk::format("�ź��� \x1b[29x{}\x1b[0x ���", _scene_citem_��Ż.name);
			else
				str = pk::format("���� \x1b[29x{}\x1b[0x ���", getName(_scene_item_��Ż));

			pk::history_log(pk::point(0, 0), 0, pk::encode(str));
			
			pk::background(-1);
		}

		void callback220����(const pk::destroy_info& in info, pk::list<pk::person@>& captured, pk::list<pk::person@>& escaped, bool tactics_bonus)
		{
			if (captured.count == 0)
				return;

			pk::hex_object@ attacker = info.attacker;
			pk::person@ judge = pk::get_person(pk::get_force(attacker.get_force_id()).kunshu);
			if (judge == null)
				return;

			for (int i = 0; i < captured.count; i++)
			{
				pk::person@ p = captured[i];
				array<CustomItem@> arr = getCustomItem(p);
				if (arr.length > 0)
				{
					for (int j = 0; j < arr.length; j++)
					{
						CustomItem@ ci = arr[j];
						ItemRent@ ir = getRent(ci);
						if (ir != null)
							removeRent(ir);


						@_scene_citem_��Ż = ci;
						@_scene_kunshu_��Ż = judge;
						@_scene_item_��Ż = null;

						try
						{
							if (_scene_kunshu_��Ż.is_player())
								pk::scene(pk::scene_t(scene_����_��Ż));
							else
								scene_����_��Ż();
						}
						catch
						{
							
						}

						ci.updateOwner(judge);
					}
				}
				array<pk::item@> arr2 = getItem(p);
				if (arr2.length > 0)
				{
					for (int j = 0; j < arr2.length; j++)
					{
						pk::item@ ci = arr2[j];

						@_scene_citem_��Ż = null;
						@_scene_kunshu_��Ż = judge;
						@_scene_item_��Ż = ci;

						try
						{
							if (_scene_kunshu_��Ż.is_player())
								pk::scene(pk::scene_t(scene_����_��Ż));
							else
								scene_����_��Ż();
						}
						catch
						{
						}

						//ci.location = judge.service;
						//ci.owner = judge.get_id();
						//ci.update();
						//judge.update();
					}
					//pk::transfer_item(judge, judge);
				}
			}
		}


		int callback203�⺴�������(pk::person@ attacker, pk::person@ target, int tactics_id, bool critical)
		{
			bool bFound = false;
			for (int i = 0; i < _attackers.length; i++)
			{
				if (attacker.get_id() != _attackers[i].get_id())
					continue;
				if (target.get_id() != _defenders[i].get_id())
					continue;

				bFound = true;
				break;
			}

			if (!bFound)
			{
				_attackers.insertLast(attacker);
				_defenders.insertLast(target);
			}


			return prev_callback_203�⺴�������(attacker, target, tactics_id, critical);
		}

		int callback110�����߰�Ȯ��(pk::building@ building, pk::person@ actor, pk::item@ item)
		{
			if (Ŀ���Ҿ����۽�.length > 0)
			{
				array<CustomItem@> items;
				for (int i = 0; i < Ŀ���Ҿ����۽�.length; i++)
				{
					CustomItem@ ci0 = Ŀ���Ҿ����۽�[i];
					if(ci0==null || ci0.owner!=null)
						continue;
					//if(ci0.name != "�������")
					//	continue;


					items.insertLast(ci0);
				}
				
				if (items.length > 0)
				{
					int a = pk::rand(items.length);
					CustomItem@ ci = items[a];
					if (ci.owner == null)
					{
						int n = pk::max(pk::max((61 - ci.value), 0) / 20, 1);
						//if (actor.is_player())
						//	n = 0;
						//else
						//	n = 100;
						////n = 0;
						//n = 100;
						if (pk::rand_bool(n))
						{
							@_scene_item = ci;
							@_scene_actor = actor;
							pk::scene(pk::scene_t(scene_�����߰�));
							return 0;
						}
					}
				}
			}
			return prev_callback_110�����߰�Ȯ��(building, actor, item);
		}




		int callback205(pk::unit@ src, int strategy_id)
		{
			int bSkill = -2;
			pk::person@ leader = pk::get_person(src.leader);
			if (leader != null && !src.has_skill(Ư��_����) && hasCustomItemSkill(src,Ư��_����))
			{
				bSkill = leader.skill;
				setSkill(leader, Ư��_����);
			}

			int n = prev_callback_205(src, strategy_id);
			if (leader != null && bSkill != -2)
			{
				//leader.skill = bSkill;
				resetSkill(leader, bSkill);
			}

			return n;
		}
		int callback200(pk::unit@ assister, pk::unit@ attacker, pk::unit@ target)
		{
			int bSkill = -2;
			pk::person@ leader = pk::get_person(attacker.leader);
			if (leader != null && !assister.has_skill(Ư��_����) && hasCustomItemSkill(assister,Ư��_����))
			{
				bSkill = leader.skill;
				setSkill(leader, Ư��_����);
			}

			int n = prev_callback_200(assister, attacker, target);
			if (has����skill(assister, ����Ư��_��������Ȯ��))
			{
				n = pk::min(100, n + ��������Ȯ��);
			}


			if (leader != null && bSkill != -2)
			{
				resetSkill(leader, bSkill);
			}

			return n;
		}

		void callback214(pk::damage_info& info, pk::unit@ attacker, pk::hex_object@ target0, bool critical)
		{
			int bSkill = -2;
			pk::person@ leader = attacker != null ? pk::get_person(attacker.leader) : null;
			if (leader != null && !attacker.has_skill(Ư��_ȭ��) && hasCustomItemSkill(attacker,Ư��_ȭ��))
			{
				bSkill = leader.skill;
				setSkill(leader, Ư��_ȭ��);
			}

			pk::unit@ target = pk::hex_object_to_unit(target0);

			int bSkillTarget = -2;
			pk::person@ leaderTarget = target != null ? pk::get_person(target.leader) : null;
			if (leaderTarget != null && !target.has_skill(Ư��_ȭ��) && hasCustomItemSkill(leaderTarget, Ư��_ȭ��))
			{
				bSkillTarget = leaderTarget.skill;
				setSkill(leaderTarget, Ư��_ȭ��);
			}
			if (bSkillTarget == -2 && leaderTarget != null && !target.has_skill(Ư��_����) && hasCustomItemSkill(leaderTarget, Ư��_����))
			{
				bSkillTarget = leaderTarget.skill;
				setSkill(leaderTarget, Ư��_����);
			}
			if (bSkillTarget==-2 && leaderTarget != null && !target.has_skill(Ư��_�) && hasCustomItemSkill(leaderTarget,Ư��_�))
			{
				bSkillTarget = leaderTarget.skill;
				setSkill(leaderTarget, Ư��_�);
			}



			prev_callback_214(info, attacker, target0, critical);

			if (leader != null && bSkill != -2)
			{
				resetSkill(leader, bSkill);
			}
			if (leaderTarget != null && bSkillTarget != -2)
			{
				resetSkill(leaderTarget, bSkillTarget);
			}
		}

		int callback216(pk::unit@ unit, const pk::point& in pos)
		{
			int n = prev_callback_216(unit, pos);
			if (hasCustomItemSkill(unit, Ư��_ȭ��))
				n = 0;
			return n;
		}


		pk::int_bool callback206(pk::unit@ src, const pk::point& in src_pos, const pk::point& in dst_pos, int strategy_id)
		{
			pk::unit@ target_unit = getUnit(dst_pos);
			pk::unit@ attacker = src;


			int bSkill = -2;
			pk::person@ leader = pk::get_person(src.leader);
			if (leader != null)
			{
				int skill = -1;
				array<int> skills = { Ư��_�Ż�,Ư��_���,Ư��_�汹,Ư��_�ⷫ,Ư��_��,Ư��_�˰�,Ư��_ȭ��,Ư��_����,Ư��_��å };

				for (int i = 0; i < skills.length; i++)
				{
					int a = skills[i];
					if (strategy_id != �跫_ȭ�� && a == Ư��_ȭ��)
						continue;
					if (strategy_id != �跫_���� && a == Ư��_��)
						continue;
					if (strategy_id != �跫_���� && a == Ư��_�˰�)
						continue;
					if (strategy_id != �跫_���� && a == Ư��_�ⷫ)
						continue;
					if (attacker.has_skill(a))
						break;
					if (hasCustomItemSkill(attacker,a))
					{
						skill = a;
						break;
					}
				}

				if (skill >= 0)
				{
					bSkill = leader.skill;
					setSkill(leader, skill);
				}
			}

			int bSkillTarget = -2;
			pk::person@ leaderTarget = target_unit != null ? pk::get_person(target_unit.leader) : null;
			if (leaderTarget != null)
			{
				int skill = -1;
				array<int> skills = { Ư��_�Ż�,Ư��_����,Ư��_ȭ��,Ư��_�ݰ�,Ư��_����,Ư��_���,Ư��_ħ��,Ư��_���� };

				for (int i = 0; i < skills.length; i++)
				{
					int a = skills[i];
					if (strategy_id != �跫_ȭ�� && a == Ư��_ȭ��)
						continue;
					if (strategy_id != �跫_���� && a == Ư��_����)
						continue;
					if (strategy_id != �跫_���� && a == Ư��_ħ��)
						continue;

					if (target_unit.has_skill(a))
						break;
					if (hasCustomItemSkill(target_unit, a))
					{
						skill = a;
						break;
					}
				}

				if (skill >= 0)
				{
					bSkillTarget = leaderTarget.skill;
					setSkill(leaderTarget, skill);
				}
			}

			auto arr = prev_callback_206(src, src_pos, dst_pos, strategy_id);
			if (has����skill(src, ����Ư��_�跫����Ȯ��))
			{
				arr.first = pk::min(100, arr.first + �跫����Ȯ��);
			}

			if (bSkill != -2 && leader != null)
			{
				resetSkill(leader, bSkill);
			}
			if (bSkillTarget != -2 && leaderTarget != null)
			{
				resetSkill(leaderTarget, bSkillTarget);
			}


			return arr;
		}


		int callback207(pk::unit@ attacker, const pk::point& in src_pos, const pk::point& in dst_pos, int strategy_id)
		{

			int bSkill = -2;
			pk::person@ leader = pk::get_person(attacker.leader);
			if (leader != null)
			{
				int skill = -1;
				array<int> skills = { Ư��_�Ż�,Ư��_�ɸ�,Ư��_����,Ư��_��å };

				for (int i = 0; i < skills.length; i++)
				{
					int a = skills[i];
					if (attacker.has_skill(a))
						break;
					if (hasCustomItemSkill(attacker, a))
					{
						skill = a;
						break;
					}
				}

				if (skill >= 0)
				{
					bSkill = leader.skill;
					setSkill(leader, skill);
				}

			}

			int n = prev_callback_207(attacker, src_pos, dst_pos, strategy_id);
			if (leader != null && bSkill != -2)
			{
				resetSkill(leader, bSkill);
			}



			return n;
		}

		void callback209(pk::damage_info& info, pk::unit@ attacker, int tactics_id, const pk::point& in target_pos, int type, int critical, bool ambush)
		{
			//����,��ǳ,����,�޽�,�,�鸶,ģ��,ģ��,ģ��,ģ��
			pk::unit@ target_unit = getUnit(target_pos);
			array<int> skillsTarget = { -2,-2,-2 };
			pk::person@ leaderTarget = target_unit != null ? pk::get_person(target_unit.leader) : null;
			if (target_unit != null && leaderTarget != null)
			{
				array<int> targetSkills00 = { Ư��_�, Ư��_�ݰ�, Ư��_�ұ�, Ư��_ö��};
				array<int> targetSkills0;
				while (targetSkills00.length > 0)
				{
					int aa = pk::rand(targetSkills00.length);
					targetSkills0.insertLast(targetSkills00[aa]);
					targetSkills00.removeAt(aa);
				}

				array<int> targetSkills;
				for (int i = 0; i < targetSkills0.length; i++)
				{
					int a = targetSkills0[i];
					if (target_unit.has_skill(a))
						continue;
					if (!hasCustomItemSkill(target_unit, a))
					{
						bool bbb = false;
						array<pk::point> pts = pk::range(target_unit.get_pos(), 1, 1);
						for (int j = 0; j < pts.length; j++)
						{
							pk::point pt = pts[j];
							pk::unit@ uu = getUnit(pt);
							if(uu==null || pk::is_enemy(target_unit,uu))
								continue;

							if (has����skill(uu, ����Ư��_���Ư�����)) 
							{
								if (uu.has_skill(a) || hasCustomItemSkill(uu,a))
								{
									bbb = true;
									break;
								}
							}
						}
						if(!bbb)
							continue;
					}
						

					targetSkills.insertLast(a);
				}

				int j = 0;
				for (int i = 0; i < pk::get_member_count(target_unit); i++)
				{
					pk::person@ p = pk::get_person(target_unit.member[i]);
					if (p == null)
						continue;
					if (j == targetSkills.length)
						break;

					//ö��,�ݰ�,�ұ�,
					skillsTarget[i] = p.skill;
					setSkill(p, targetSkills[j]);
					j++;
					continue;
				}
			}

			array<int> skills = { -2,-2,-2 };
			if (target_unit != null)
			{
				array<int> targetSkills0 = { Ư��_�鸶, Ư��_�޽�, Ư��_��ǳ,Ư��_ģ��,Ư��_ģ��,Ư��_ģ��,Ư��_ģ��,Ư��_����,Ư��_���� };
				array<int> targetSkills;
				for (int i = 0; i < targetSkills0.length; i++)
				{
					int a = targetSkills0[i];
					if (attacker.has_skill(a))
						continue;
					if (!hasCustomItemSkill(attacker, a))
						continue;

					targetSkills.insertLast(a);
				}


				int j = 0;
				for (int i = 0; i < pk::get_member_count(attacker); i++)
				{
					pk::person@ p = pk::get_person(attacker.member[i]);
					if (p == null)
						continue;
					if (j == targetSkills.length)
						break;

					if (pk::get_distance(attacker.pos, target_unit.pos) > 1 && targetSkills[j] == Ư��_�鸶 && attacker.weapon == ����_����)
					{
						skills[i] = p.skill;
						setSkill(p, Ư��_�鸶);
						j++;
						continue;
					}
					if (pk::is_in_water(attacker) && targetSkills[j] == Ư��_����)
					{
						skills[i] = p.skill;
						setSkill(p, Ư��_����);
						j++;
						continue;
					}
					if (!pk::is_in_water(attacker) && targetSkills[j] == Ư��_�޽�)
					{
						skills[i] = p.skill;
						setSkill(p, Ư��_�޽�);
						j++;
						continue;
					}
					if (attacker.weapon == ����_���� && (targetSkills[j] == Ư��_ģ�� || targetSkills[j] == Ư��_ģ��))
					{
						skills[i] = p.skill;
						setSkill(p, targetSkills[j]);
						j++;
						continue;
					}
					if (attacker.weapon == ����_�� && (targetSkills[j] == Ư��_ģ�� || targetSkills[j] == Ư��_ģ��))
					{
						skills[i] = p.skill;
						setSkill(p, targetSkills[j]);
						j++;
						continue;
					}

					//��ǳ,����
					skills[i] = p.skill;
					setSkill(p, targetSkills[j]);
					j++;
					continue;
				}
			}



			prev_callback_209(info, attacker, tactics_id, target_pos, type, critical, ambush);
			if (target_unit != null && has����skill(target_unit, ����Ư��_��ұ�) && target_unit.troops <= ��ұ�_���±��� && pk::rand_bool(��ұ�_Ȯ��))
			{
				info.troops_damage = 0;
				info.def_skill = Ư��_�ұ�;
				info.tactics_hit = false;
				info.critical = false;
			}
			if (type == 0 && target_unit!=null && has����skill(attacker, ����Ư��_��ų) && pk::rand_bool(��ų_Ȯ��))
			{
				info.troops_damage = target_unit.troops + 1;
				string str = pk::encode(pk::format("�ź���, ��ųȿ�� �߻�, {}�밡 {}���� ������ {} �Ҹ�!!!!\n",getNameLeader(attacker),getNameLeader(target_unit), info.troops_damage));
				pk::history_log(attacker.get_pos(), pk::get_force(attacker.get_force_id()).color,str);
			}
			if (target_unit != null && has����skill(attacker, ����Ư��_����Ż��))
			{
				info.food_damage = info.food_heal = info.troops_damage * ����_������_����;
			}
			if (target_unit == null)
			{
				pk::building@ building = pk::hex_object_to_building(pk::get_hex_object(target_pos));
				if (building != null)
				{
					if (has����skill(attacker, ����Ư��_�����δ�_�ǹ�������_�߰�))
					{
						info.troops_damage *= �ǹ�������_����;
						info.hp_damage *= �ǹ�������_����;
					}
					else
					{
						for (int j = 0; j < 6; j++)
						{
							pk::point pt = pk::get_neighbor_pos(attacker.get_pos(), j, 1);
							pk::unit@ unit2 = getUnit(pt);
							if (unit2 == null || pk::is_enemy(attacker, unit2))
								continue;

							if (has����skill(unit2, ����Ư��_�����δ�_�ǹ�������_�߰�))
							{
								info.troops_damage *= �ǹ�������_����;
								info.hp_damage *= �ǹ�������_����;
								break;
							}
						}
					}
				}
			}

			if (target_unit != null)
			{
				for (int i = 0; i < pk::get_member_count(target_unit); i++)
				{
					int a = skillsTarget[i];
					if (a != -2)
					{
						resetSkill(pk::get_person(target_unit.member[i]), a);
					}
				}
			}
			if (attacker!=null)
			{
				for (int i = 0; i < pk::get_member_count(attacker); i++)
				{
					int a = skills[i];
					if (a != -2)
					{
						resetSkill(pk::get_person(attacker.member[i]), a);
					}
				}
			}

			pk::hex_object@ obj = pk::get_hex_object(target_pos);
			if (attacker != null && obj != null)
			{
				if (!IsAlready����(attacker, obj, info.troops_damage))
				{
					_attackers����.insertLast(attacker);
					_targets����.insertLast(obj);
					_damages����.insertLast(info);
					_points����.insertLast(obj.get_pos());

					pk::list<pk::person@> l;
					pk::list<pk::person@> l2;

					if(pk::is_valid_person_id(attacker.member[0])) 
						l.add(pk::get_person(attacker.member[0]));
					if (pk::is_valid_person_id(attacker.member[1]))
						l.add(pk::get_person(attacker.member[1]));
					if (pk::is_valid_person_id(attacker.member[2]))
						l.add(pk::get_person(attacker.member[2]));

					if (target_unit != null) 
					{
						if (pk::is_valid_person_id(target_unit.member[0]))
							l2.add(pk::get_person(target_unit.member[0]));
						if (pk::is_valid_person_id(target_unit.member[1]))
							l2.add(pk::get_person(target_unit.member[1]));
						if (pk::is_valid_person_id(target_unit.member[2]))
							l2.add(pk::get_person(target_unit.member[2]));
					}

					_attackersPerson����.insertLast(l);
					_targetrsPerson����.insertLast(l2);
				}
			}
		}

		int callback164(pk::unit@ unit)
		{
			int n = prev_callback_164(unit);
			if (!has����skill(unit, ����Ư��_��ұ�))
				return n;
			return 0;
		}


		bool IsAlready����(pk::unit@ u, pk::hex_object@ obj, int damage)
		{
			for (int i = 0; i < _attackers����.length; i++)
			{
				pk::unit@ u0 = _attackers����[i];
				if (u0.get_id() == u.get_id() && obj.get_id() == _targets����[i].get_id())
				{
					if (damage > _damages����[i].troops_damage)
						_damages����[i].troops_damage = damage;
					return true;
				}
			}
			return false;
		}

		array<pk::list<pk::person@>> _attackersPerson����;
		array<pk::list<pk::person@>> _targetrsPerson����;
		array<pk::unit@> _attackers����;
		array<pk::hex_object@> _targets����;
		array<pk::damage_info> _damages����;
		array<pk::point> _points����;
		bool has����skill(pk::person@ p, int type)
		{
			if (p == null)
				return false;
			for (int i = 0; i < Ŀ���Ҿ����۽�.length; i++)
			{
				CustomItem@ ci = Ŀ���Ҿ����۽�[i];
				if (ci == null)
					continue;
				if(ci.owner == null)
					continue;
				if(ci.owner.get_id() != p.get_id())
					continue;

				for (int j = 0; j < ci.skills����.length; j++)
				{
					if (ci.skills����[j] == type)
						return true;
				}
			}
			return false;
		}
		bool has����skill(pk::unit@ u, int type)
		{
			return has����skill(pk::get_person(u.member[0]), type) || has����skill(pk::get_person(u.member[1]), type) || has����skill(pk::get_person(u.member[2]), type);
		}

		void clearAttacker����(pk::unit@ u)
		{
			_attackers���� = {};
			_targets���� = {};
			_damages���� = {};
			_points���� = {};
			//_attackersPerson���� = {};
			//_targetrsPerson���� = {};
			return;
			while (true)
			{
				int a = _attackers����.findByRef(u);
				if (a < 0)
					break;
				_attackers����.removeAt(a);
				_targets����.removeAt(a);
				_damages����.removeAt(a);
				_points����.removeAt(a);
			}
		}

		array<pk::hex_object@> getAttacker����(pk::unit@ u)
		{
			array<pk::hex_object@> arr;
			for (int i = 0; i < _attackers����.length; i++)
			{
				pk::unit@ u0 = _attackers����[i];
				if (u0.get_id() == u.get_id())
				{
					arr.insertLast(_targets����[i]);
				}
			}
			return arr;
		}
		array<pk::damage_info> getAttackerDamages����(pk::unit@ u)
		{
			array<pk::damage_info> arr;
			for (int i = 0; i < _attackers����.length; i++)
			{
				pk::unit@ u0 = _attackers����[i];
				if (u0.get_id() == u.get_id())
				{
					arr.insertLast(_damages����[i]);
				}
			}
			return arr;
		}
		array<pk::point> getAttackerPoints����(pk::unit@ u)
		{
			array<pk::point> arr;
			for (int i = 0; i < _attackers����.length; i++)
			{
				pk::unit@ u0 = _attackers����[i];
				if (u0.get_id() == u.get_id())
				{
					arr.insertLast(_points����[i]);
				}
			}
			return arr;
		}


		bool callback201(pk::unit@ attacker, pk::hex_object@ target, int tactics_id, bool ranged)
		{
			int bSkill = -2;
			pk::person@ leader = pk::get_person(attacker.leader);
			if (leader != null)
			{
				int skill = -1;
				pk::unit@ target_unit = pk::hex_object_to_unit(target);
				if ((target_unit !is null and (pk::get_hex(attacker.get_pos()).terrain != ����_�� or (pk::get_hex(attacker.get_pos()).terrain == ����_�� and !attacker.has_skill(Ư��_����)))))
				{
					if (pk::get_hex(attacker.get_pos()).terrain == ����_�� && hasCustomItemSkill(attacker, Ư��_����))
						skill = Ư��_����;

					if (skill == -1 && !(pk::is_valid_tactics_id(tactics_id)))
					{
						if (!attacker.has_skill(Ư��_����) && hasCustomItemSkill(attacker, Ư��_����))
							skill = Ư��_����;
						if (skill == -1 && !attacker.has_skill(Ư��_����) && !attacker.has_skill(Ư��_����) && hasCustomItemSkill(attacker, Ư��_����))
							skill = Ư��_����;
						if (skill == -1 && ranged && !attacker.has_skill(Ư��_����) && !attacker.has_skill(Ư��_�鸶) && hasCustomItemSkill(attacker, Ư��_�鸶) && attacker.weapon == ����_����)
							skill = Ư��_�鸶;
					}
					else if (skill == -1)
					{
						switch (attacker.weapon)
						{
						case ����_����:
							if (!attacker.has_skill(Ư��_�п�) && !attacker.has_skill(Ư��_���))
							{
								if (hasCustomItemSkill(attacker, Ư��_�п�))
									skill = Ư��_�п�;
								if (skill == -1 && hasCustomItemSkill(attacker, Ư��_���))
									skill = Ư��_���;

								if (skill == -1 && !attacker.has_skill(Ư��_����) && !attacker.has_skill(Ư��_����) && !attacker.has_skill(Ư��_����))
								{
									if (skill == -1 && hasCustomItemSkill(attacker, Ư��_����))
										skill = Ư��_����;
									if (skill == -1 && hasCustomItemSkill(attacker, Ư��_����))
										skill = Ư��_����;
									if (skill == -1 && hasCustomItemSkill(attacker, Ư��_����))
										skill = Ư��_����;
								}
							}
							break;
						case ����_â:
							if (!attacker.has_skill(Ư��_�п�) && !attacker.has_skill(Ư��_â��) && !attacker.has_skill(Ư��_����))
							{
								if (hasCustomItemSkill(attacker, Ư��_�п�))
									skill = Ư��_�п�;
								if (skill == -1 && hasCustomItemSkill(attacker, Ư��_â��))
									skill = Ư��_â��;
								if (skill == -1 && hasCustomItemSkill(attacker, Ư��_����))
									skill = Ư��_����;

								if (skill == -1 && !attacker.has_skill(Ư��_����) && !attacker.has_skill(Ư��_����) && !attacker.has_skill(Ư��_â��))
								{
									if (skill == -1 && hasCustomItemSkill(attacker, Ư��_����))
										skill = Ư��_����;
									if (skill == -1 && hasCustomItemSkill(attacker, Ư��_����))
										skill = Ư��_����;
									if (skill == -1 && hasCustomItemSkill(attacker, Ư��_â��))
										skill = Ư��_â��;
								}
							}
							break;
						case ����_��:
							if (!attacker.has_skill(Ư��_�п�) && !attacker.has_skill(Ư��_�ؽ�) && !attacker.has_skill(Ư��_����))
							{
								if (hasCustomItemSkill(attacker, Ư��_�п�))
									skill = Ư��_�п�;
								if (skill == -1 && hasCustomItemSkill(attacker, Ư��_�ؽ�))
									skill = Ư��_�ؽ�;
								if (skill == -1 && hasCustomItemSkill(attacker, Ư��_����))
									skill = Ư��_����;

								if (skill == -1 && !attacker.has_skill(Ư��_����) && !attacker.has_skill(Ư��_����) && !attacker.has_skill(Ư��_����))
								{
									if (skill == -1 && hasCustomItemSkill(attacker, Ư��_����))
										skill = Ư��_����;
									if (skill == -1 && hasCustomItemSkill(attacker, Ư��_����))
										skill = Ư��_����;
									if (skill == -1 && hasCustomItemSkill(attacker, Ư��_����))
										skill = Ư��_����;
								}
							}
							break;
						case ����_��:
							if (!attacker.has_skill(Ư��_�п�) && !attacker.has_skill(Ư��_�ý�))
							{
								if (hasCustomItemSkill(attacker, Ư��_�п�))
									skill = Ư��_�п�;
								if (skill == -1 && hasCustomItemSkill(attacker, Ư��_�ý�))
									skill = Ư��_�ý�;

								if (skill == -1 && !attacker.has_skill(Ư��_����) && !attacker.has_skill(Ư��_����) && !attacker.has_skill(Ư��_����))
								{
									if (skill == -1 && hasCustomItemSkill(attacker, Ư��_����))
										skill = Ư��_����;
									if (skill == -1 && hasCustomItemSkill(attacker, Ư��_����))
										skill = Ư��_����;
									if (skill == -1 && hasCustomItemSkill(attacker, Ư��_����))
										skill = Ư��_����;
								}
							}
							break;
						case ����_����:
						case ����_����:
						case ����_���:
							if (!attacker.has_skill(Ư��_�п�) && !attacker.has_skill(Ư��_����))
							{
								if (hasCustomItemSkill(attacker, Ư��_�п�))
									skill = Ư��_�п�;
								if (skill == -1 && hasCustomItemSkill(attacker, Ư��_����))
									skill = Ư��_����;

								if (skill == -1 && !attacker.has_skill(Ư��_����) && !attacker.has_skill(Ư��_����) && !attacker.has_skill(Ư��_����))
								{
									if (skill == -1 && hasCustomItemSkill(attacker, Ư��_����))
										skill = Ư��_����;
									if (skill == -1 && hasCustomItemSkill(attacker, Ư��_����))
										skill = Ư��_����;
									if (skill == -1 && hasCustomItemSkill(attacker, Ư��_����))
										skill = Ư��_����;
								}
							}
							break;
						case ����_�ְ�:
						case ����_����:
						case ����_����:
							if (!attacker.has_skill(Ư��_�п�) && !attacker.has_skill(Ư��_����))
							{
								if (hasCustomItemSkill(attacker, Ư��_�п�))
									skill = Ư��_�п�;
								if (skill == -1 && hasCustomItemSkill(attacker, Ư��_����))
									skill = Ư��_����;

								if (skill == -1 && !attacker.has_skill(Ư��_����) && !attacker.has_skill(Ư��_����) && !attacker.has_skill(Ư��_����))
								{
									if (skill == -1 && hasCustomItemSkill(attacker, Ư��_����))
										skill = Ư��_����;
									if (skill == -1 && hasCustomItemSkill(attacker, Ư��_����))
										skill = Ư��_����;
									if (skill == -1 && hasCustomItemSkill(attacker, Ư��_����))
										skill = Ư��_����;
								}
							}
							break;

						}//end of switch
					}//end of skill
				}



				if (skill >= 0)
				{
					bSkill = leader.skill;
					setSkill(leader, skill);
				}
			}


			bool bCri = prev_callback_201(attacker, target, tactics_id, ranged);
			if (leader != null)
			{
				if (bSkill != -2)
				{
					resetSkill(leader, bSkill);
				}
			}

			return bCri;
		}
		int callback258(pk::person@ prisoner, const pk::prisoner_info& in info)
		{
			pk::person@ p = prisoner;
			pk::person@ judge = pk::get_person(pk::get_kunshu_id(info.attacker));

			array<CustomItem@> arr = getCustomItem(p);
			if (arr.length > 0)
			{
				for (int i = 0; i < arr.length; i++)
				{
					CustomItem@ ci = arr[i];
					ItemRent@ ir = getRent(ci);
					if (ir != null)
						removeRent(ir);


					@_scene_citem_��Ż = ci;
					@_scene_kunshu_��Ż = judge;
					@_scene_item_��Ż = null;
					try
					{
						if (judge.is_player())
							pk::scene(pk::scene_t(scene_����_��Ż));
						else
							scene_����_��Ż();
					}
					catch
					{
					}

					ci.updateOwner(judge);
				}
			}
			array<pk::item@> arr2 = getItem(p);
			if (arr2.length > 0)
			{
				for (int i = 0; i < arr2.length; i++)
				{
					pk::item@ ci = arr2[i];

					@_scene_citem_��Ż = null;
					@_scene_kunshu_��Ż = judge;
					@_scene_item_��Ż = ci;

					try
					{
						if (judge.is_player())
							pk::scene(pk::scene_t(scene_����_��Ż));
						else
							scene_����_��Ż();
					}
					catch
					{
					}

				}
			}
			
			
			return prev_callback_258(prisoner, info);
		}

		void callback220(const pk::destroy_info& in info, pk::list<pk::person@>& captured, pk::list<pk::person@>& escaped, bool tactics_bonus)
		{
			pk::hex_object@ attacker0 = info.attacker;
			pk::hex_object@ target0 = info.target;

			pk::unit@ attacker = pk::hex_object_to_unit(attacker0);
			pk::unit@ target = getUnit(target0.get_pos());

			int bSkill = -2;
			pk::person@ leader = attacker != null ? pk::get_person(attacker.leader) : null;
			if (leader != null)
			{
				if (hasCustomItemSkill(attacker, Ư��_����))
				{
					bSkill = leader.skill;
					setSkill(leader, Ư��_����);
				}
			}

			int bSkillTarget = -2;
			pk::person@ leaderTarget = target != null ? pk::get_person(target.leader) : null;
			if (leaderTarget != null)
			{
				if (hasCustomItemSkill(leaderTarget, Ư��_����))
				{
					bSkillTarget = leaderTarget.skill;
					setSkill(leaderTarget, Ư��_����);
				}
				else if (hasCustomItemSkill(leaderTarget, Ư��_����))
				{
					bSkillTarget = leaderTarget.skill;
					setSkill(leaderTarget, Ư��_����);
				}
			}

			//pk::hex_object@ targetDebug = info.target;
			//if (targetDebug != null)
			//{
			//	pk::unit@ u = pk::hex_object_to_unit(targetDebug);
			//	if (u != null && pk::get_person(u.leader).mibun != �ź�_����)
			//	{
			//		pk::person@ p0 = pk::get_person(u.member[0]);
			//		pk::person@ p1 = pk::get_person(u.member[1]);
			//		pk::person@ p2 = pk::get_person(u.member[2]);
			//		if (p0 != null) captured.add(p0);
			//		if (p1 != null) captured.add(p1);
			//		if (p2 != null) captured.add(p2);
			//	}
			//}
			prev_callback_220(info, captured, escaped, tactics_bonus);

			if (leader != null && bSkill != -2)
			{
				resetSkill(leader, bSkill);
			}
			if (leaderTarget != null && bSkillTarget != -2)
			{
				resetSkill(leaderTarget, bSkillTarget);
			}

			callback220����(info, captured, escaped, tactics_bonus);
		}
		
		int callback202(pk::unit@ attacker, const pk::point& in pos, pk::hex_object@ target, int tactics_id)
		{
			int n = prev_callback_202(attacker, pos, target, tactics_id);
			if (has����skill(attacker, ����Ư��_��������Ȯ��))
			{
				n = pk::min(100, n + ��������Ȯ��);
			}
			return n;
		}



		int callback167(pk::building@ building)
		{
			pk::list<pk::person@> persons = pk::get_person_list(building, pk::mibun_flags(�ź�_����,�ź�_����,�ź�_�¼�,�ź�_�Ϲ�));
			pk::person@ tp = null;
			for (int i = 0; i < persons.count; i++)
			{
				pk::person@ p = persons[i];
				if (hasCustomItemSkill(p, Ư��_����))
				{
					@tp = p;
					break;
				}
			}

			int bskill = -2;
			if (tp != null)
			{
				bskill = tp.skill;
				setSkill(tp, Ư��_����);
			}

			int n = prev_callback_167(building);

			if (bskill != -2)
			{
				resetSkill(tp, bskill);
			}
			return n;
		}
		
		int callback100(pk::building@ building, const pk::detail::arrayptr<pk::person@>& in actors)
		{
			pk::person@ tp = null;
			for (int i = 0; i < actors.length; i++)
			{
				pk::person@ p = actors[i];
				if (hasCustomItemSkill(p, Ư��_��))
				{
					@tp = p;
					break;
				}
			}

			int bskill = -2;
			if (tp != null)
			{
				bskill = tp.skill;
				setSkill(tp, Ư��_��);
			}

			int n = prev_callback_100(building,actors);

			if (bskill != -2)
			{
				resetSkill(tp, bskill);
			}
			return n;
		}

		int callback102(pk::city@ city, const pk::detail::arrayptr<pk::person@>& in actors, int weapon_id)
		{
			int skill = -1;
			if (weapon_id == ����_����)
				skill = Ư��_����;
			if (weapon_id == ����_�� || weapon_id == ����_â || weapon_id == ����_��)
				skill = Ư��_�ɸ�;
			if(skill == -1)
				return prev_callback_102(city, actors, weapon_id);


			pk::person@ tp = null;
			for (int i = 0; i < actors.length; i++)
			{
				pk::person@ p = actors[i];
				if (hasCustomItemSkill(p, skill))
				{
					@tp = p;
					break;
				}
			}

			int bskill = -2;
			if (tp != null)
			{
				bskill = tp.skill;
				setSkill(tp, skill);
			}

			int n = prev_callback_102(city, actors, weapon_id);

			if (bskill != -2)
			{
				resetSkill(tp, bskill);
			}
			return n;

		}

		int callback103(const pk::detail::arrayptr<pk::person@>& in actors, int weapon_id)
		{
			int skill = -1;
			if (weapon_id == ����_���� || weapon_id == ����_���� || weapon_id == ����_���� || weapon_id == ����_���)
				skill = Ư��_�߸�;
			if (weapon_id == ����_���� || weapon_id == ����_����)
				skill = Ư��_����;
			if (skill == -1)
				return prev_callback_103(actors, weapon_id);


			pk::person@ tp = null;
			for (int i = 0; i < actors.length; i++)
			{
				pk::person@ p = actors[i];
				if (hasCustomItemSkill(p, skill))
				{
					@tp = p;
					break;
				}
			}

			int bskill = -2;
			if (tp != null)
			{
				bskill = tp.skill;
				setSkill(tp, skill);
			}

			int n = prev_callback_103(actors, weapon_id);

			if (bskill != -2)
			{
				resetSkill(tp, bskill);
			}
			return n;

		}

		int callback150(pk::city@ city)
		{
			pk::list<pk::person@> persons = pk::get_person_list(pk::city_to_building(city), pk::mibun_flags(�ź�_����, �ź�_����, �ź�_�¼�, �ź�_�Ϲ�));
			pk::person@ tp = null;
			for (int i = 0; i < persons.count; i++)
			{
				pk::person@ p = persons[i];
				if (hasCustomItemSkill(p, Ư��_��ȣ))
				{
					@tp = p;
					break;
				}
			}

			int bskill = -2;
			if (tp != null)
			{
				bskill = tp.skill;
				setSkill(tp, Ư��_��ȣ);
			}

			int n = prev_callback_150(city);

			if (bskill != -2)
			{
				resetSkill(tp, bskill);
			}
			return n;

		}

		int callback152(pk::building@ building, int city_revenue)
		{
			pk::list<pk::person@> persons = pk::get_person_list(building, pk::mibun_flags(�ź�_����, �ź�_����, �ź�_�¼�, �ź�_�Ϲ�));
			pk::person@ tp = null;
			for (int i = 0; i < persons.count; i++)
			{
				pk::person@ p = persons[i];
				if (hasCustomItemSkill(p, Ư��_��ȣ))
				{
					@tp = p;
					break;
				}
			}

			int bskill = -2;
			if (tp != null)
			{
				bskill = tp.skill;
				setSkill(tp, Ư��_��ȣ);
			}

			int n = prev_callback_152(building,city_revenue);

			if (bskill != -2)
			{
				resetSkill(tp, bskill);
			}
			return n;
		}

		int callback151(pk::city@ city)
		{
			pk::list<pk::person@> persons = pk::get_person_list(pk::city_to_building(city), pk::mibun_flags(�ź�_����, �ź�_����, �ź�_�¼�, �ź�_�Ϲ�));
			pk::person@ tp = null;
			for (int i = 0; i < persons.count; i++)
			{
				pk::person@ p = persons[i];
				if (hasCustomItemSkill(p, Ư��_�̵�))
				{
					@tp = p;
					break;
				}
			}

			int bskill = -2;
			if (tp != null)
			{
				bskill = tp.skill;
				setSkill(tp, Ư��_�̵�);
			}

			int n = prev_callback_151(city);

			if (bskill != -2)
			{
				resetSkill(tp, bskill);
			}
			return n;

		}

		int callback153(pk::building@ building, int city_harvest)
		{
			pk::list<pk::person@> persons = pk::get_person_list(building, pk::mibun_flags(�ź�_����, �ź�_����, �ź�_�¼�, �ź�_�Ϲ�));
			pk::person@ tp = null;
			for (int i = 0; i < persons.count; i++)
			{
				pk::person@ p = persons[i];
				if (hasCustomItemSkill(p, Ư��_�̵�))
				{
					@tp = p;
					break;
				}
			}

			int bskill = -2;
			if (tp != null)
			{
				bskill = tp.skill;
				setSkill(tp, Ư��_�̵�);
			}

			int n = prev_callback_153(building, city_harvest);

			if (bskill != -2)
			{
				resetSkill(tp, bskill);
			}
			return n;

		}

		int callback155(pk::building@ building, pk::person@ person)
		{
			pk::list<pk::person@> persons = pk::get_person_list(building, pk::mibun_flags(�ź�_����, �ź�_����, �ź�_�¼�, �ź�_�Ϲ�));
			pk::person@ tp = null;
			for (int i = 0; i < persons.count; i++)
			{
				pk::person@ p = persons[i];
				if (hasCustomItemSkill(p, Ư��_����))
				{
					@tp = p;
					break;
				}
			}

			int bskill = -2;
			if (tp != null)
			{
				bskill = tp.skill;
				setSkill(tp, Ư��_����);
			}

			int n = prev_callback_155(building, person);

			if (bskill != -2)
			{
				resetSkill(tp, bskill);
			}
			return n;
		}



		
		
		pk::person@ _scene_actor;
		CustomItem@ _scene_item;

		void scene_�����߰�()
		{
			if (_scene_actor == null)
				return;
			CustomItem@ ci = _scene_item;
			pk::force@ force = pk::get_force(_scene_actor.get_force_id());
			pk::person@ kunshu = pk::get_person(force.kunshu);
			if (_scene_actor.is_player())
			{
				pk::background(pk::format("{}", ci.path));
				pk::message_box(pk::encode(pk::format("�ź��� {} �߰��߽��ϴ�.", ci.name)));
			}

			string str = pk::format("\x1b[2x{}��\x1b[0x,�ź��� \x1b[29x{}\x1b[0x �߰�", getName(kunshu), ci.name);
			pk::history_log(kunshu != null ? kunshu.get_pos() : pk::point(0, 0), force.color, pk::encode(str));

			ci.updateOwner(kunshu);
			//�����߰�;

			if (_scene_actor.is_player())
				pk::background(-1);
		}

		void �����߰�(pk::unit@ unit)
		{
			if (pk::rand(����Ȯ��_����) == 0/* || unit.is_player()*/)
			{
				array<CustomItem@> arr;
				for (int i = 0; i < Ŀ���Ҿ����۽�.length; i++)
				{
					CustomItem@ ci = Ŀ���Ҿ����۽�[i];
					if (ci == null)
						continue;
					if (ci.owner == null)
						arr.insertLast(ci);
				}

				if (arr.length > 0)
				{
					int a = pk::rand(arr.length);

					@_scene_actor = pk::get_person(unit.leader);
					@_scene_item = arr[a];
					pk::scene(pk::scene_t(scene_�����߰�));
				}
			}
		}

		void onUnitEnd����(pk::unit@ unit)
		{
			array<pk::hex_object@> arr = getAttacker����(unit);
			array<pk::damage_info> arrDemage = getAttackerDamages����(unit);
			for (int i = 0; i < arr.length; i++)
			{
				pk::damage_info dem = arrDemage[i];
				pk::printf("����:{},{}\n", getNameLeader(pk::hex_object_to_unit(arr[i])), dem.tactics);
			}

		}
		void onUnitCreate(pk::unit@ unit, int type)
		{
			array<ItemRent@> removes;
			for (int i = 0; i < _rent.length; i++)
			{
				ItemRent@ ir = _rent[i];
				if(ir.owner0 == null)
					continue;

				if (ir.owner0.get_id() == unit.member[0])
				{
					removes.insertLast(ir);
				}
				if (ir.owner0.get_id() == unit.member[1])
				{
					removes.insertLast(ir);
				}
				if (ir.owner0.get_id() == unit.member[2])
				{
					removes.insertLast(ir);
				}
			}

			while (removes.length>0)
			{
				removes[0].rentBack();
				removes.removeAt(0);
			}
		}
		void onUnitEnd(pk::unit@ unit)
		{
			�����߰�(unit);

			int chaos = -1;
			if (has����skill(unit, ����Ư��_ȥ��))
			{
				array<CustomItem@> items=getCustomItem(unit);
				for (int i = 0; i < items.length; i++)
				{
					CustomItem@ it = items[i];
					if (it.skills����.length > 0 && it.skills����[0] == ����Ư��_ȥ��)
					{
						chaos = it.skillsȥ��[pk::rand(it.skillsȥ��.length)];
						string strChaos = "";
						switch (chaos)
						{
						case ����Ư��_������_ȭ��߻�:strChaos = "������ȭ��"; break;
						case ����Ư��_����_����:strChaos = "��������"; break;
						case ����Ư��_����_���÷���_������:strChaos = "�������÷���"; break;
						case ����Ư��_������_�߰�������:strChaos = "�߰�������"; break;
						case ����Ư��_������_�漺��_����:strChaos = "�漺������"; break;
						case ����Ư��_��ǳ:strChaos = "��ǳ"; break;
						case ����Ư��_�ɰ�:strChaos = "�ɰ�"; break;
						case ����Ư��_��ų:strChaos = "��ų"; break;
						case ����Ư��_����Ż��:strChaos = "����Ż��"; break;
						case ����Ư��_ȥ��_����:strChaos = "ȥ��_����"; break;
						case ����Ư��_����_����:strChaos = "����_����"; break;
						case ����Ư��_����_����:strChaos = "����_����"; break;
						case ����Ư��_�ϱ���_����:strChaos = "�ϱ���_����"; break;
						case ����Ư��_���׿�:strChaos = "���׿�"; break;
						case ����Ư��_�λ�����:strChaos = "�λ�����"; break;
						case ����Ư��_����:strChaos = "����"; break;
						default:
							break;
						}
						string str = pk::encode(pk::format("�ź��� ȥ��ȿ�� \x1b[29x{}\x1b[0x �߻� !!!!,",strChaos));
						pk::history_log(unit.get_pos(), pk::get_force(unit.get_force_id()).color, str);
						break;
					}
				}
			}

			//if (hasCustomItemSkill(unit, Ư��_����) && !unit.has_skill(Ư��_����))
			//{
			//	onUnitEnd����(unit);
			//}
			
			if (hasCustomItemSkill(unit, Ư��_����) && unit.weapon == ����_����)
			{
				pk::func222_t@ func = cast<pk::func222_t@>(pk::get_func(222));
				array<pk::hex_object@> arr = getAttacker����(unit);
				for (int i = 0; i < arr.length; i++)
				{
					pk::hex_object@ obj = arr[i];
					if (obj == null || !obj.is_alive())
						continue;
					if (!pk::is_valid_pos(obj.get_pos()))
						continue;

					pk::unit@ unit2 = getUnit(obj.get_pos());
					if (unit2 == null || !pk::is_enemy(unit, unit2))
						continue;
					
					if (unit.attr.stat[�δ�ɷ�_����] > unit2.attr.stat[�δ�ɷ�_����])
					{
						pk::set_status(unit2, unit, �δ����_ȥ��, pk::rand(2) + 1, true);
					}
				}
			}
			if (has����skill(unit, ����Ư��_�λ�����) || chaos == ����Ư��_�λ�����)
			{
				array<pk::hex_object@> arr = getAttacker����(unit);
				for (int i = 0; i < arr.length; i++)
				{
					pk::hex_object@ obj = arr[i];
					if (obj == null || !obj.is_alive())
						continue;
					if (!pk::is_valid_pos(obj.get_pos()))
						continue;

					pk::unit@ unit2 = pk::hex_object_to_unit(obj);
					if(unit2==null || !pk::is_enemy(unit,unit2))
						continue;

					if(pk::rand_bool(�λ�����_Ȯ��)) injury(pk::get_person(unit2.member[0]));
					if(pk::rand_bool(�λ�����_Ȯ��)) injury(pk::get_person(unit2.member[1]));
					if(pk::rand_bool(�λ�����_Ȯ��)) injury(pk::get_person(unit2.member[2]));
				}
			}
			if (has����skill(unit, ����Ư��_������_ȭ��߻�) || chaos == ����Ư��_������_ȭ��߻�)
			{
				array<pk::hex_object@> arr = getAttacker����(unit);
				for (int i = 0; i < arr.length; i++)
				{
					pk::hex_object@ obj = arr[i];
					if(obj == null || !obj.is_alive())
						continue;
					if(!pk::rand_bool(ȭ��_Ȯ��))
						continue;
					if(!pk::is_valid_pos(obj.get_pos()))
						continue;
					if(!pk::is_enemy(unit,obj))
						continue;

					pk::create_fire(obj.get_pos(), pk::rand(2) + 1, unit);
					pk::unit@ u = getUnit(obj.get_pos());
					if (u != null && pk::rand(����_RAND) == 0)
					{
						pk::say(pk::encode("���ڱ� ���� ���..."), pk::get_person(u.leader), u);
					}
				}
			}
			if (has����skill(unit, ����Ư��_������_�漺��_����) || chaos == ����Ư��_������_�漺��_����)
			{
				array<pk::hex_object@> arr = getAttacker����(unit);
				for (int i = 0; i < arr.length; i++)
				{
					pk::hex_object@ obj = arr[i];
					if (obj == null || !obj.is_alive())
						continue;
					if (!pk::is_valid_pos(obj.get_pos()))
						continue;

					pk::unit@ unit2 = getUnit(obj.get_pos());
					if (unit2 == null || !pk::is_enemy(unit, unit2))
						continue;

					pk::person@ p0 = pk::get_person(unit2.member[0]);
					if (p0!=null) pk::add_loyalty(p0, -�漺��_���Ϸ�);
					pk::person@ p1 = pk::get_person(unit2.member[1]);
					if (p1 != null) pk::add_loyalty(p1, -�漺��_���Ϸ�);
					pk::person@ p2 = pk::get_person(unit2.member[2]);
					if (p2 != null) pk::add_loyalty(p2, -�漺��_���Ϸ�);

					if (p0 != null && pk::rand(����_RAND) == 0)
					{
						pk::say(pk::encode("�ֱ��� ���� �Ⱦ��ϴ°� ����."), p0, unit2);
					}
				}
			}
			if (has����skill(unit, ����Ư��_ȥ��_����) || chaos == ����Ư��_ȥ��_����)
			{
				array<pk::hex_object@> arr = getAttacker����(unit);
				for (int i = 0; i < arr.length; i++)
				{
					pk::hex_object@ obj = arr[i];
					if (obj == null || !obj.is_alive())
						continue;
					if (!pk::is_valid_pos(obj.get_pos()))
						continue;

					pk::unit@ unit2 = getUnit(obj.get_pos());
					if (unit2 == null || !pk::is_enemy(unit, unit2))
						continue;
					if(!pk::rand_bool(ȥ��_Ȯ��))
						continue;

					pk::set_status(unit2, unit, �δ����_ȥ��, pk::rand(2) + 1, true);
					if (pk::rand(����_RAND) == 0)
					{
						pk::say(pk::encode("�̰� �������̳�???"), pk::get_person(unit2.leader), unit2);
					}

				}
			}
			if (has����skill(unit, ����Ư��_����_����) || chaos == ����Ư��_����_����)
			{
				array<pk::hex_object@> arr = getAttacker����(unit);
				for (int i = 0; i < arr.length; i++)
				{
					pk::hex_object@ obj = arr[i];
					if (obj == null || !obj.is_alive())
						continue;
					if (!pk::is_valid_pos(obj.get_pos()))
						continue;

					pk::unit@ unit2 = getUnit(obj.get_pos());
					if (unit2 == null || !pk::is_enemy(unit, unit2))
						continue;
					if (!pk::rand_bool(����_Ȯ��))
						continue;

					pk::set_status(unit2, unit, �δ����_����, pk::rand(2) + 1, true);
					if (pk::rand(����_RAND) == 0)
					{
						pk::say(pk::encode("���� �³�???"), pk::get_person(unit2.leader), unit2);
					}

				}
			}
			if (has����skill(unit, ����Ư��_����_����) || chaos == ����Ư��_����_����)
			{
				array<pk::hex_object@> arr = getAttacker����(unit);
				for (int i = 0; i < arr.length; i++)
				{
					pk::hex_object@ obj = arr[i];
					if (obj == null || !obj.is_alive())
						continue;
					if (!pk::is_valid_pos(obj.get_pos()))
						continue;

					pk::unit@ unit2 = getUnit(obj.get_pos());
					if (unit2 == null || !pk::is_enemy(unit, unit2))
						continue;
					if (!pk::rand_bool(����_Ȯ��))
						continue;

					array<pk::unit@> units;
					for (int j = 0; j < 6; j++)
					{
						pk::point pt = pk::get_neighbor_pos(unit2.get_pos(), j, 1);
						pk::unit@ unit3 = getUnit(pt);
						if (unit3 == null || pk::is_enemy(unit3, unit2))
							continue;

						units.insertLast(unit3);
					}
					if(units.length == 0)
						continue;
					pk::unit@ target = units[pk::rand(units.length)];
					pk::attack(unit2, target);
					pk::say(pk::encode("���Ƽ�? �������̿�"), pk::get_person(target.leader) ,target);
				}
			}
			if (has����skill(unit, ����Ư��_��ǳ) || chaos == ����Ư��_��ǳ)
			{
				array<pk::hex_object@> arr = getAttacker����(unit);
				for (int i = 0; i < arr.length; i++)
				{
					pk::hex_object@ obj = arr[i];
					if (obj == null || !obj.is_alive())
						continue;
					if (!pk::is_valid_pos(obj.get_pos()))
						continue;

					pk::unit@ unit2 = getUnit(obj.get_pos());
					if (unit2 == null || !pk::is_enemy(unit, unit2))
						continue;

					pk::add_energy(unit2, -��ǳ_���, true);
				}
			}
			if (has����skill(unit, ����Ư��_������_�߰�������) || chaos == ����Ư��_������_�߰�������)
			{
				array<pk::point> arr = getAttackerPoints����(unit);
				array<pk::damage_info> arrDemage = getAttackerDamages����(unit);
				for (int i = 0; i < arr.length; i++)
				{
					pk::hex_object@ obj = pk::get_hex_object(arr[i]);
					if(obj == null || !pk::is_enemy(unit,obj))
						continue;
					if (!pk::is_valid_pos(obj.get_pos()))
						continue;

					pk::damage_info di = arrDemage[i];
					if(di.troops_damage==0)
						continue;

					
					create_effect(0x4c, obj.get_pos());
					pk::unit@ u = pk::hex_object_to_unit(obj);
					if (u != null)
					{
						pk::add_troops(u, -(di.troops_damage * �߰�_������_����), true);
					}
					else 
					{
						pk::building@ b = pk::hex_object_to_building(obj);
						pk::add_troops(b, -(di.troops_damage * �߰�_������_����), true);
						pk::add_hp(b, -(di.hp_damage * �߰�_������_����), true);
					}
					updateAfter(unit, obj);
				}
			}
			if (has����skill(unit, ����Ư��_�ɰ�) || chaos == ����Ư��_�ɰ�)
			{
				array<pk::point> arr = getAttackerPoints����(unit);
				array<pk::damage_info> arrDemage = getAttackerDamages����(unit);
				int sum = 0;
				for (int i = 0; i < arr.length; i++)
				{
					pk::hex_object@ obj = pk::get_hex_object(arr[i]);
					if (obj == null || !pk::is_enemy(unit, obj))
						continue;
					if (!pk::is_valid_pos(obj.get_pos()))
						continue;

					pk::damage_info di = arrDemage[i];
					if (di.troops_damage == 0)
						continue;

					pk::unit@ u = pk::hex_object_to_unit(obj);
					if (u == null)
						continue;

					sum += (di.troops_damage * �ɰ�_����);
				}
				if (sum > 0)
					pk::add_troops(unit, sum, true);
			}
			if (has����skill(unit, ����Ư��_����_����) || chaos == ����Ư��_����_����)
			{
				array<pk::point> pts = pk::range(unit.get_pos(), 0, 1);
				for (int i = 0; i < pts.length; i++)
				{
					pk::point pt = pts[i];
					pk::unit@ unit2 = getUnit(pt);
					if (unit2 == null || !pk::is_enemy(unit, unit2))
						continue;
					if (!pk::rand_bool(����_Ȯ��))
						continue;

					play_se(121, unit2.get_pos());
					create_effect(0x40, unit2.get_pos());
					//create_effect(0x89, unit2.get_pos());
					pk::add_troops(unit2, -(����_�⺻_������+pk::rand(����_����_������)), true);
					if (updateAfter(unit, unit2))
					{
						if (pk::rand_bool(����_�λ�_Ȯ��)) injury(pk::get_person(unit2.member[0]));
						if (pk::rand_bool(����_�λ�_Ȯ��)) injury(pk::get_person(unit2.member[1]));
						if (pk::rand_bool(����_�λ�_Ȯ��)) injury(pk::get_person(unit2.member[2]));

						if (pk::rand(����_RAND) == 0)
						{
							pk::say(pk::encode("���� �ϴÿ� ������?"), pk::get_person(unit2.leader), unit2);
						}
					}
				}
			}
			if (has����skill(unit, ����Ư��_���׿�) || chaos == ����Ư��_���׿�)
			{
				array<pk::point> pts = pk::range(unit.get_pos(), 0, 1);
				for (int i = 0; i < pts.length; i++)
				{
					pk::point pt = pts[i];
					pk::unit@ unit2 = getUnit(pt);
					if (unit2 == null || !pk::is_enemy(unit, unit2))
						continue;
					if (!pk::rand_bool(���׿�_Ȯ��))
						continue;

					doMeteo(unit,unit2);
					updateAfter(unit, unit2);
					if (pk::rand(����_RAND) == 0)
					{
						pk::say(pk::encode("�ﱹ�ô뿡 ���??"), pk::get_person(unit2.leader), unit2);
					}
				}
			}
			if (has����skill(unit, ����Ư��_����) || chaos == ����Ư��_����)
			{
				array<pk::point> pts = pk::range(unit.get_pos(), 0, 1);
				for (int i = 0; i < pts.length; i++)
				{
					pk::point pt = pts[i];
					pk::unit@ unit2 = getUnit(pt);
					if (unit2 == null || !pk::is_enemy(unit, unit2))
						continue;
					if (!pk::rand_bool(����_Ȯ��))
						continue;

					float aa = pk::rand(100) / 99.0;
					int dem = aa * aa * ����_������;

					play_se(119, unit2.get_pos());
					create_effect(0xb, unit2.get_pos());
					pk::add_troops(unit2, -dem, true);
					updateAfter(unit, unit2);
					if (pk::rand(����_RAND) == 0)
					{
						pk::say(pk::encode("�޷���??"), pk::get_person(unit2.leader), unit2);
					}
				}
			}

			if (has����skill(unit, ����Ư��_����_���÷���_������) || chaos == ����Ư��_����_���÷���_������)
			{
				dictionary dict;
				array<pk::point> arr = getAttackerPoints����(unit);
				array<pk::damage_info> arrDemage = getAttackerDamages����(unit);

				for (int i = 0; i < arr.length; i++)
				{
					pk::unit@ u = getUnit(arr[i]);
					if (u == null)
						continue;

					if (dict.exists(pk::format("{}", u.get_id())))
						continue;
					dict[pk::format("{}", u.get_id())] = 3;
				}

				array<pk::unit@> arr2;
				array<pk::damage_info> arr2Demage;

				for (int i = 0; i < arr.length; i++)
				{
					pk::damage_info objDem = arrDemage[i];
					if(objDem.troops_damage == 0)
						continue;

					array<pk::point> pts = pk::range(arr[i], 0, 1);
					for (int j = 0; j < pts.length; j++)
					{
						pk::point pt = pts[j];
						pk::unit@ u2 = getUnit(pt);
						if(u2==null || !pk::is_enemy(unit,u2))
							continue;
						if(dict.exists(pk::format("{}",u2.get_id())))
							continue;
						dict[pk::format("{}", u2.get_id())] = 3;
						arr2.insertLast(u2);
						arr2Demage.insertLast(objDem);
					}
				}

				for (int i = 0; i < arr2.length; i++)
				{
					pk::unit@ u = arr2[i];
					pk::damage_info objDem = arr2Demage[i];
					create_effect(0x4a, u.get_pos());
					pk::add_troops(u, -objDem.troops_damage * ���÷���_������_����, true);
					updateAfter(unit, u);

					if (pk::rand(����_RAND) == 0)
					{
						pk::say(pk::encode("������� ���״°��̳�.."), pk::get_person(u.leader), u);
					}
				}
			}

			if (has����skill(unit, ����Ư��_�������) && unit.weapon == ����_��)
			{
				array<pk::point> parr;
				array<int> parrDam;
				array<pk::point> arr = getAttackerPoints����(unit);
				array<pk::damage_info> arrDemage = getAttackerDamages����(unit);

				for (int i = 0; i < arr.length; i++)
				{
					array<pk::point> parr2 = get����path(unit.get_pos(), arr[i]);
					for (int j = 0; j < parr2.length; j++)
					{
						pk::point ppp = parr2[j];
						bool bFound = false;
						for (int k = 0; k < parr.length; k++)
						{
							pk::point ppp2 = parr[k];
							if (ppp == ppp2)
							{
								bFound = true;
								break;
							}
						}
						if (!bFound)
						{
							for (int k = 0; k < arr.length; k++)
							{
								pk::point ppp2 = arr[k];
								if (ppp == ppp2)
								{
									bFound = true;
									break;
								}
							}
							if (!bFound)
							{
								parr.insertLast(ppp);
								parrDam.insertLast(arrDemage[i].troops_damage);
							}
						}
					}
				}



				for (int i = 0; i < parr.length; i++)
				{
					pk::point ppp = parr[i];
					pk::unit@ uu = getUnit(ppp);
					if (uu == null || !pk::is_enemy(uu,unit))
						continue;

					create_effect(0x4a, uu.get_pos());
					pk::add_troops(uu, -parrDam[i] * ���÷���_������_����, true);
					//if(has����skill(unit, ����Ư��_������_ȭ��߻�))
					//	pk::create_fire(uu.get_pos(), pk::rand(2) + 1, unit);
					updateAfter(unit, uu);
					if (pk::rand(����_RAND) == 0)
					{
						pk::say(pk::encode("������� ���״°��̳�.."), pk::get_person(uu.leader), uu);
					}
				}
			}
			������_ó��();
			clearAttacker����(unit);
		}

		pk::point get����center(pk::point pt0)
		{
			pk::point point = pk::hex_pos_to_screen_pos(pt0);

			pk::point pt = pk::get_neighbor_pos(pt0, ����_��, 1);
			pk::point point1 = pk::hex_pos_to_screen_pos(pt);

			pt = pk::hex_pos_to_screen_pos(pt0);
			pk::point pt2 = pk::hex_pos_to_screen_pos(pk::get_neighbor_pos(pt0, ����_��, 1));
			pk::point point2 = pk::point(pt2.x + pt2.y - pt.y, pt2.y);


			pt = pk::hex_pos_to_screen_pos(pt0);
			pt2 = pk::hex_pos_to_screen_pos(pk::get_neighbor_pos(pt0, ����_��, 1));
			pk::point point3 = pk::point(pt.x + pt2.y - pt.y, pt.y);


			return pk::point((point.x + point1.x + point2.x + point3.x) / 4, (point.y + point1.y + point2.y + point3.y) / 4);
		}

		array<pk::point> get����path(pk::point pos0, pk::point pos1)
		{
			pk::point cpos0 = get����center(pos0);
			pk::point cpos1 = get����center(pos1);

			array<pk::point> arr;
			for (int i = 0; i < 20; i++)
			{
				pk::point pt;
				pt.x = cpos0.x + (cpos1.x - cpos0.x) * (i / 19.0);
				pt.y = cpos0.y + (cpos1.y - cpos0.y) * (i / 19.0);

				pk::point hexPt = pk::screen_pos_to_hex_pos(pt);

				bool bFound = false;
				for (int j = 0; j < arr.length; j++)
				{
					if (hexPt == arr[j])
					{
						bFound = true;
						break;
					}
				}
				if (!bFound)
					arr.insertLast(hexPt);
			}
			return arr;
		}


		pk::point dst_pos_;
		void doMeteo(pk::unit@ unit, pk::unit@ target)
		{
			pk::point src_pos_ = unit.get_pos();
			pk::point dst_pos = target.get_pos();
			// ���� �δ� �跫 ���� ����, ȿ�� ����
			if (pk::is_in_screen(src_pos_))
			{
				pk::play_voice(0x35, pk::get_person(unit.leader));
				pk::play_se(0x39, src_pos_);
				pk::create_effect(0x3a, src_pos_);
				pk::wait(1, 1000);
			}

			// ����� ���
			int troops_damage = (���׿�_�⺻_������ + pk::rand(���׿�_����_������));

			// ��ǥ �δ� �ִϸ��̼�
			if (pk::is_in_screen(dst_pos))
			{
				dst_pos_ = dst_pos;
				// � ȿ�� ����
				auto handle = pk::create_effect(0x6b, dst_pos, function(handle, delta) {
					// � �������� �Ҹ�
					if (delta == -1) {
						pk::play_se(0x56, main.dst_pos_);
					}
					// �ִϸ��̼��� �����ٸ� ����
					else if (handle.elapsed > 500) {
						pk::create_effect(0xe, main.dst_pos_);
						pk::play_se(0x71, main.dst_pos_);
						return true;
					}

					auto v = pk::hex_pos_to_world_pos(main.dst_pos_);
					v.y = v.y + 120 - handle.elapsed / 500.f * 120;
					auto m = pk::matrix4();
					m.translate(v);
					handle.m = m;
					return false;
				});

				// ����� �ִϸ��̼�
				pk::damage_info info;
				info.troops_damage = troops_damage;
				info.dst_pos = dst_pos;
				pk::unit_anim(target, 32, { info }, -1, 500, pk::encode("�ƾ�~"));

				// �δ� �ִϸ��̼��� �����ų� Ŭ������ ������ �� ���� ���
				pk::wait(1);

				// �����Ѱ�츦 ���� �ִϸ��̼� ����, ȿ�� ����
				pk::stop_unit_anim();
				pk::remove(handle);
			}

			// ����� ����
			pk::add_troops(target, -troops_damage, true);
			if(pk::rand_bool(���׿�_ȭ��_Ȯ��))
				pk::create_fire(dst_pos, pk::rand(2) + 2, unit, true);
			return;
		}

		bool isEnabled()
		{
			return true;
		}

		string getDesc_�ź����϶�()
		{
			return pk::encode("�ź����� Ȯ���մϴ�.");
		}
		string getText_�ź����϶�()
		{
			return pk::encode("�ź����϶�");
		}

		array<string> Ư�⼳����(255);
		array<string> Ư���̸����(255);
		array<int> Ư����(����_��);
		void SaveƯ��()
		{
			for (int i = 0; i < 255; i++)
			{
				pk::skill@ s = pk::get_skill(i);
				if (s == null)
					continue;
				Ư�⼳����[i] = s.desc;
				Ư���̸����[i] = s.name;
			}

			for (int i = 0; i < ����_��; i++)
			{
				pk::person@ p = pk::get_person(i);
				if (p == null)
					continue;
				Ư����[i] = p.skill;
			}
		}
		void LoadƯ��()
		{
			for (int i = 0; i < 255; i++)
			{
				pk::skill@ s = pk::get_skill(i);
				if (s == null)
					continue;
				s.desc = Ư�⼳����[i];
				s.name = Ư���̸����[i];
			}
			for (int i = 0; i < ����_��; i++)
			{
				pk::person@ p = pk::get_person(i);
				if (p == null)
					continue;
				p.skill = Ư����[i];
			}
		}


		bool isRented(pk::item@ it)
		{
			for (int i = 0; i < _rent.length; i++)
			{
				ItemRent@ ir = _rent[i];
				if (ir.item.get_id() == it.get_id())
				{
					return true;
				}
			}
			return false;
		}
		pk::person@ getRentedOwner(pk::item@ it)
		{
			for (int i = 0; i < _rent.length; i++)
			{
				ItemRent@ ir = _rent[i];
				if (ir.item.get_id() == it.get_id())
				{
					return ir.owner0;
				}
			}
			return null;
		}
		

		array<ItemDisplay@> compute(pk::force@ force=null)
		{
			dictionary dict;
			array<ItemDisplay@> arr;
			for (int i = 0; i < ����_��; i++)
			{
				pk::item@ it = pk::get_item(i);
				if(it==null)
					continue;
				if(it.type == -1)
					continue;


				//pk::printf("type:{},{},{}\n", i, it.type,it.status);
				pk::person@ owner = pk::get_person(it.owner);
				if (isRented(it))
				{
					@owner = getRentedOwner(it);
				}
				if(force!=null && (owner == null || owner.get_force_id() != force.get_id()))
					continue;

				ItemDisplay id;
				@id.item = it;
				@id.owner = owner;
				id.value = it.value;
				id.name = getName(it);
				id.path = �����̹���[it.get_id()];
				arr.insertLast(id);

				if (owner != null)
				{
					string key = pk::format("{}", owner.get_id());
					int count = 0;
					if (dict.exists(key)) 
						count = int(dict[key]);
					count++;
					dict[key] = count;
				}
			}
			for (int i = 0; i < Ŀ���Ҿ����۽�.length; i++)
			{
				CustomItem@  it = Ŀ���Ҿ����۽�[i];
				if(it==null)
					continue;

				if (force != null && (it.owner == null || it.owner.get_force_id() != force.get_id()))
					continue;

				ItemDisplay id;
				@id.citem = it;
				@id.owner = it.owner;
				id.value = it.value;
				id.name = it.name;
				id.path = it.path;
				arr.insertLast(id);

				if (it.owner != null)
				{
					string key = pk::format("{}", it.owner.get_id());
					int count = 0;
					if (dict.exists(key))
						count = int(dict[key]);
					count++;
					dict[key] = count;
				}
			}

			for (int i = 0; i < arr.length; i++)
			{
				ItemDisplay@ id = arr[i];
				if(id.owner == null)
					continue;

				string key = pk::format("{}", id.owner.get_id());
				id.itemCount = int(dict[key]);
			}


			arr.sort(function(x, y)
			{
				if (x.itemCount != y.itemCount)
					return x.itemCount > y.itemCount;

				if (x.owner != null && y.owner != null)
					return x.owner.get_id() <= y.owner.get_id();
				else if (x.owner != null)
					return true;
				else if (y.owner != null)
					return false;
				return true;
			});
			return arr;
		}

		void handler_�ź����϶�2()
		{
			array<ItemDisplay@> arr = compute();
			while (true)
			{
				int count = pk::min(255, arr.length);
				pk::list<pk::person@> ris2;

				for (int i = 0; i < count; i++)
				{
					ItemDisplay@ di = arr[i];
					pk::skill@ s = pk::get_skill(i);
					if(di == null)
						continue;

					pk::person@ p = pk::get_person(i);
					p.skill = s.get_id();

					string str = ""; 
					if(di.citem!=null)
						str=pk::format("\x1b[2x{}\x1b[0x,\x1b[18x{}\x1b[0x,��ġ:{}", di.owner != null ? getName(di.owner) : "����", di.name, di.value);
					else
						str = pk::format("\x1b[2x{}\x1b[0x,\x1b[1x{}\x1b[0x,��ġ:{}", di.owner != null ? getName(di.owner) : "����", di.name, di.value);

					s.desc = pk::encode(str);
					if (s.name == "")
						s.name = pk::encode("����");
					//s.name = pk::encode("������");

					ris2.add(p);
				}

				pk::list<pk::person@> persons = pk::person_selector(pk::encode("���� ����"), pk::encode("������ �������ֽʽÿ�"), ris2, 1, 1);
				if (persons.count == 0)
					return;

				@_scene_item_display = arr[persons[0].get_id()];
				pk::scene(pk::scene_t(scene_����ǥ��));
			}
		}

		ItemDisplay@ _scene_item_display = null;
		void scene_����ǥ��()
		{
			ItemDisplay@ di = _scene_item_display;
			pk::background(_scene_item_display.path);
			

			string str;
			if (_scene_item_display.item != null)
			{
				str = pk::format("\x1b[1x{}\x1b[0x,\x1b[1x{}\x1b[0x,��ġ:{}", di.owner != null ? getName(di.owner) : "����", di.name, di.value);
				str = str + "\n�ΰ��ɷ� ��ȸ�Ұ�";
			}
			else 
			{
				CustomItem@ ci = di.citem;
				pk::item@ src= pk::get_item(ci.srcItem);
				str = pk::format("\x1b[1x{}\x1b[0x,\x1b[1x{}\x1b[0x,��ġ:{},����:{}\n", di.owner != null ? getName(di.owner) : "����", di.name, di.value,getName(src));
				str = str+ pk::format("��:{},��:{},��:{},��:{},��:{}\n", ci.�ɷ�[0], ci.�ɷ�[1], ci.�ɷ�[2], ci.�ɷ�[3], ci.�ɷ�[4]);
				str = str + "Ư��:";
				for (int i = 0; i < ci.skills.length; i++)
				{
					if(i!=ci.skills.length-1)
						str = str + pk::format("\x1b[1x{}\x1b[0x ",getName(pk::get_skill(ci.skills[i])));
					else
						str = str + pk::format("\x1b[1x{}\x1b[0x", getName(pk::get_skill(ci.skills[i])));
				}
			}

			pk::message_box(pk::encode(str));
			pk::background(-1);
		}

		bool handler_�ź����϶�()
		{
			try
			{
				SaveƯ��();
				handler_�ź����϶�2();
			}
			catch
			{
				LoadƯ��();
			}

			LoadƯ��();
			return true;
		}


		pk::force@ _force;
		pk::building@ _building;
		pk::city@ _city;
		pk::district@ _district;
		void �ź�������Init(pk::building@ building)
		{
			@_force = pk::get_force(building.get_force_id());
			@_building = building;
			@_city = pk::building_to_city(building);
			@_district = pk::get_district(building.get_district_id());
		}

		bool Is�ź�������Enabled()
		{
			return compute(_force).length > 0 && _district.ap >= 10;
		}

		string �ź�������Desc()
		{
			return pk::encode(pk::format("����/�ź����� �����մϴ�(�ൿ��{})",10));
		}
		string �ź�������Text()
		{
			return pk::encode("�ź�������");
		}
		
		void �ź�������Handler2()
		{
			array<ItemDisplay@> arr = compute(_force);

			while (_district.ap >= 10)
			{
				int count = pk::min(255, arr.length);
				pk::list<pk::person@> ris2;

				for (int i = 0; i < count; i++)
				{
					ItemDisplay@ di = arr[i];
					pk::skill@ s = pk::get_skill(i);
					if (di == null)
						continue;

					pk::person@ p = pk::get_person(i);
					p.skill = s.get_id();

					string str = "";
					if (di.citem != null)
						str = pk::format("\x1b[2x{}\x1b[0x,\x1b[18x{}\x1b[0x,��ġ:{}", di.owner != null ? getName(di.owner) : "����", di.name, di.value);
					else
						str = pk::format("\x1b[2x{}\x1b[0x,\x1b[1x{}\x1b[0x,��ġ:{}", di.owner != null ? getName(di.owner) : "����", di.name, di.value);

					s.desc = pk::encode(str);

					if(s.name == "")
						s.name = pk::encode("����");

					ris2.add(p);
				}

				pk::list<pk::person@> persons = pk::person_selector(pk::encode("���� ����"), pk::encode("������ �������ֽʽÿ�"), ris2, 1, 1);
				if (persons.count == 0)
					return;

				@_scene_item_display = arr[persons[0].get_id()];
				pk::scene(pk::scene_t(scene_��������));

				pk::message_box(pk::encode("������ ������ ������ �����ϼ���."));


				pk::list<pk::person@> persons0 = pk::get_person_list(_force, pk::mibun_flags(�ź�_����,�ź�_�¼�,�ź�_����,�ź�_�Ϲ�));
				persons0.remove_at(persons0.index_of(_scene_item_display.owner));
				pk::list<pk::person@> persons1 = pk::person_selector(pk::encode("���� ����"), pk::encode("������ �������ֽʽÿ�"), persons0, 1, 1);
				if(persons1.count == 0)
					continue;

				if (_scene_item_display.owner.mibun != �ź�_����)
				{
					pk::message_box(pk::encode("�ƿ� ��¥��!!!"), _scene_item_display.owner);
					_scene_item_display.owner.loyalty = pk::max(0,_scene_item_display.owner.loyalty -_scene_item_display.value);
					pk::message_box(pk::encode(pk::format("�漺���� {}�� �϶��߽��ϴ�", _scene_item_display.owner.loyalty)));
				}

				if (_scene_item_display.citem != null)
				{
					_scene_item_display.citem.updateOwner(persons1[0]);
				}
				else 
				{
					_scene_item_display.item.owner = persons1[0].get_id();
					_scene_item_display.item.update();
					persons1[0].update();
				}

				if (persons1[0].mibun != �ź�_����)
				{
					pk::message_box(pk::encode("�����մϴ�.!!!"), persons1[0]);
					persons1[0].loyalty = pk::min(255, persons1[0].loyalty + _scene_item_display.value);
					pk::message_box(pk::encode(pk::format("�漺���� {}�� ����߽��ϴ�", persons1[0].loyalty)));
				}

				_district.ap = pk::max(_district.ap - 10,0);
				arr = compute(_force);
			}
		}

		void scene_��������()
		{
			ItemDisplay@ di = _scene_item_display;
			pk::background(_scene_item_display.path);


			string str;
			if (_scene_item_display.item != null)
			{
				str = pk::format("\x1b[1x{}\x1b[0x,\x1b[1x{}\x1b[0x,��ġ:{}\n", di.owner != null ? getName(di.owner) : "����", di.name, di.value);
				str = str + "�ΰ��ɷ� ��ȸ�Ұ�";
			}
			else
			{
				CustomItem@ ci = di.citem;
				pk::item@ src = pk::get_item(ci.srcItem);
				str = pk::format("\x1b[1x{}\x1b[0x,\x1b[1x{}\x1b[0x,��ġ:{},����:{}\n", di.owner != null ? getName(di.owner) : "����", di.name, di.value, getName(src));
				str = str + pk::format("��:{},��:{},��:{},��:{},��:{}\n", ci.�ɷ�[0], ci.�ɷ�[1], ci.�ɷ�[2], ci.�ɷ�[3], ci.�ɷ�[4]);
				str = str + "Ư��:";
				for (int i = 0; i < ci.skills.length; i++)
				{
					if (i != ci.skills.length - 1)
						str = str + pk::format("\x1b[1x{}\x1b[0x ", getName(pk::get_skill(ci.skills[i])));
					else
						str = str + pk::format("\x1b[1x{}\x1b[0x", getName(pk::get_skill(ci.skills[i])));
				}
			}

			pk::message_box(pk::encode(str));
			pk::background(-1);
		}

		bool �ź�������Handler()
		{
			try
			{
				SaveƯ��();
				�ź�������Handler2();
			}
			catch
			{
				LoadƯ��();
			}

			LoadƯ��();
			return true;

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
		void setSkill(pk::person@ p, int skill)
		{
			p.skill = skill;
			//pk::skill@ s = pk::get_skill(skill);
			//if (s == null)
			//	pk::printf("set {},null\n", pk::decode(pk::get_name(p)));
			//else
			//	pk::printf("set {},{}\n", pk::decode(pk::get_name(p)), pk::decode(pk::get_name(s)));

		}
		void resetSkill(pk::person@ p, int skill)
		{
			p.skill = skill;
			//pk::skill@ s = pk::get_skill(skill);
			//if (s == null)
			//	pk::printf("reset {},{}\n", pk::decode(pk::get_name(p)), skill);
			//else
			//	pk::printf("reset {},{}\n", pk::decode(pk::get_name(p)), pk::decode(pk::get_name(s)));
		}
		pk::unit@ getUnit(pk::point pos)
		{
			return pk::is_valid_pos(pos) ? pk::get_unit(pos) : null;
		}
		void injury(pk::person@ p)
		{
			if (p == null)
				return;
			if (pk::has_skill(p, Ư��_����))
				return;
			if (p.shoubyou == ��_���)
				return;

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
			pk::person@ kunshu = force != null ? pk::get_person(force.kunshu) : null;
			if (kunshu != null)
			{
				string str = pk::format("\x1b[2x{}\x1b[0x�� \x1b[2x{}\x1b[0x,\x1b[29x{}\x1b[0x ����", getName(kunshu), getName(p), strType);
				pk::history_log(p.get_pos(), force != null ? force.color : -1, pk::encode(str));
			}
		}

		bool updateAfter(pk::unit@ attacker, pk::hex_object@ target)
		{
			if (target == null)
				return false;

			pk::unit@ targetU = getUnit(target.get_pos());
			if (targetU != null && targetU.troops == 0)
			{
				int dist = pk::get_distance(attacker.get_pos(), target.get_pos());
				//pk::printf("kill start\n");
				pk::create_death_effect(targetU, attacker, target.get_pos());
				pk::kill(targetU, attacker, dist == 1, attacker.weapon == ����_��);

				//pk::printf("kill end\n");
				return false;
			}
			else
			{
				pk::building@ b = pk::hex_object_to_building(target);
				if (b != null)
				{
					if (b.hp <= 0)
					{
						pk::city@ city = pk::building_to_city(b);
						pk::gate@ gate = pk::building_to_gate(b);
						pk::port@ port = pk::building_to_port(b);

						if (city != null || gate != null || port != null)
						{
							pk::set_hp(b, 1);
						}
						else
						{
							pk::destroy_cmd_info di;
							@di.building = b;
							pk::command(di);
							return false;
						}
					}
				}
			}
			return true;

		}

		void create_effect(int type, pk::point pt)
		{
			if (!pk::is_in_screen(pt))
				return;
			pk::create_effect(type, pt);
		}
		void play_se(int type, pk::point pt)
		{
			if (!pk::is_in_screen(pt))
				return;

			//pk::play_se(0x39, pt);
			//pk::play_se(type, pt);
			pk::play_se(type);
		}

	}//Main
	Main main;
}

