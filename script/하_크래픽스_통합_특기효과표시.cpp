/*
@������: ũ���Ƚ�
@Update: 2024.5.9,���ʹ���
@update: 2024.5.17,�߷յ��� ���λ����� ���� �ɼ� �߰�
@update: 2024.5.28,�߷յ��� �̸� ǥ�� ����ȭ
@update: 2024.5.30,�ź��� ���� �߰� ����
*/

namespace ����_United
{
	const bool ���庰Ư��ǥ�� = true;
	const bool ����_ǥ�� = true;

	const int �߷յ���_ǥ���÷� = 0xffffbf00;
	const int �ź���_ǥ���÷� = 0xffff0000;
	const int �ο�ȿ��_ǥ���÷� = 0xff00ff00;

	const int �߷յ���_���λ����� = 80;


	const int ������� = -1;//�������� ������
	const int �������� = -1;//�������� ������

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

	array<GroupInfo> �ο�����Ʈ =
	{
		GroupInfo("��ȣ���屺",{ȿ��_���ɻ��_��},{����_����,����_���,����_����,����_����,����_Ȳ��}),
		GroupInfo("���ھ���",{ȿ��_���ɻ��_��,ȿ��_����_����_��,ȿ��_����_���_��},{����_���,����_����,����_��Ȳ,����_����,����_���}),
		GroupInfo("���߽���",{ȿ��_���ɻ��_��,ȿ��_���ݻ��_��,ȿ��_�����_��},{����_����,����_�Ѽ�,����_����,����_����,����_����,����_����,����_��Ⱦ,����_�̰�,����_����,����_�ļ�}),
		GroupInfo("��������ȣ��",{ȿ��_���ɻ��_��,ȿ��_���������},{����_����,����_Ȳ��,����_�Ѵ�,����_����,����_����,����_����,����_����,����_����,����_����,����_����,����_����,����_����}),
		GroupInfo("�����̱�",{ȿ��_�־�_��},{����_�ұ�, ����_�뱳}),
		GroupInfo("��������",{ȿ��_����_��},{����_����, ����_����,����_���}),
		GroupInfo("Ȳ���ǻ�",{ȿ��_��������ȿ��},{����_����, ����_�ձ�,����_����}),
		GroupInfo("���뵵��",{ȿ��_���������,ȿ��_����_����_��,ȿ��_����_���_��},{����_����, ����_����,����_���,����_����,����_����}),
		GroupInfo("õ�Ϲ���",{ȿ��_������°���,ȿ��_�������簨��},{����_����}),
		GroupInfo("õ�Ϲ���",{ȿ��_������°���,ȿ��_�������簨��},{����_����}),
		GroupInfo("õ�ϱ���",{ȿ��_�跫_��},{����_������, ����_�縶��}),
		GroupInfo("�������",{ȿ��_�跫_��},{����_������, ����_����}),
		GroupInfo("���湮��",{ȿ��_�跫_��,ȿ��_�跫���_��},{����_������, ����_����,����_����}),
		GroupInfo("�ý�",{ȿ��_�����ݵ�ü���},{����_Ȳ��, ����_���Ŀ�,����_����,����_����,����_����}),
		GroupInfo("���ҽֺ�",{ȿ��_���ݻ��_��},{����_�ȷ�, ����_����}),
		GroupInfo("��������",{ȿ��_���ɻ��_��},{����_����,����_����, ����_��� ,����_���}),
		GroupInfo("���ɿ���",{ȿ��_�汹,ȿ��_���ɻ��_��},{����_������,����_����,����_Ȳ����,����_�����}),
		GroupInfo("�̹���",{ȿ��_���ɻ��_��,ȿ��_���ݻ��_��,ȿ��_�����_��},{����_��ȹ,����_����,����_�縶��,����_�õ���}),
		GroupInfo("������",{ȿ��_����_��},{����_��å, ����_����}),
		GroupInfo("��������",{ȿ��_������°���,ȿ��_�������簨��},{����_����, ����_���}),
		GroupInfo("��������",{ȿ��_����_��,ȿ��_�ŷ�_���_��},{����_����, ����_������}),
		GroupInfo("�縶�ȴ�",{ȿ��_��_��},{����_�縶��,����_�縶��, ����_�縶��}),
		GroupInfo("����Ϸ�",{ȿ��_����_����_��,ȿ��_����_���_��,ȿ��_���ݻ��_��},{����_����, ����_����}),
		GroupInfo("��õå��",{ȿ��_�跫_��,ȿ��_����_���_��},{����_����, ����_����, ����_����, ����_����, ����_����}),
		GroupInfo("ȭ��å��",{ȿ��_�跫_��,ȿ��_�跫���_��,ȿ��_����_���_��},{����_��ǳ, ����_����, ����_����, ����_����, ����_����, ����_����, ����_�ɹ�}),
		GroupInfo("����å��",{ȿ��_�跫_��,ȿ��_�跫���_��,ȿ��_����_���_��},{����_Ȳ��, ����_���, ����_����}),
		GroupInfo("����å��",{ȿ��_�跫_��,ȿ��_�跫���_��,ȿ��_�跫_���_����},{����_������, ����_����, ����_����, ����_����, ����_Ȳ��}),
		GroupInfo("����å��",{ȿ��_�跫_��,ȿ��_�跫���_��,ȿ��_����_���_��},{����_���, ����_���, ����_���, ����_����, ����_����}),
		GroupInfo("����ھ�",{ȿ��_���ݻ��_��,ȿ��_������°���,ȿ��_�������簨��,ȿ��_�־�_��},{����_�ձ�,����_����}),
		GroupInfo("����2��",{ȿ��_���ݻ��_��,ȿ��_������°���,ȿ��_�������簨��,ȿ��_�־�_��},{����_��å,����_�»���}),
		GroupInfo("��������",{ȿ��_��_��,ȿ��_��ġ_���_��,ȿ��_����_���_��},{����_����,����_����}),
		GroupInfo("������",{ȿ��_���ɻ��_��,ȿ��_����_����_��,ȿ��_����_���_��,ȿ��_�跫_ũ��Ƽ��_�׻󼺰�},{����_����,����_������}),
		GroupInfo("�˰�",{ȿ��_��ȣ_��,ȿ��_�̵�_��,ȿ��_����_���_��,ȿ��_��ġ_���_��},{����_������,����_����,����_����,����_�̾�,����_����}),
		GroupInfo("ȣǥ��",{ȿ��_���ɻ��_��,ȿ��_����_����_��},{����_����,����_����}),
		GroupInfo("ȭ�Ͻֺ�",{ȿ��_���ݻ��_��},{����_�ȷ�, ����_����}),
		GroupInfo("���ɿ���",{ȿ��_�汹,ȿ��_���ɻ��_��},{����_������,����_����,����_Ȳ����,����_�����}),
		GroupInfo("��������",{ȿ��_��ġ_���_��,ȿ��_��ȣ_��,ȿ��_�̵�_��},{����_���,����_�屲})
		//GroupInfo("�׽�Ʈ",{ȿ��_�跫_���_����,ȿ��_�跫_ũ��Ƽ��_�׻󼺰�,ȿ��_����_����,ȿ��_����_����,ȿ��_����_ȭ��},{����_���,����_����})


	};


	class GroupInfo
	{
		array<int> idsApply;
		array<int> ids;
		pk::list<pk::person@> members;
		pk::list<pk::person@> membersApply;
		string name;
		bool b = false;
		pk::force@ force = null;

		GroupInfo() {}
		GroupInfo(string name0, array<int> arrIds, array<int> arrMember)
		{
			name = name0;
			ids = arrIds;
			for (int i = 0; i < arrMember.length; i++)
			{
				pk::person@ p = pk::get_person(arrMember[i]);
				if (p == null)
					continue;
				members.add(p);
			}
		}
	};
	class ForceInfo
	{
		array<SpecialForceApply@> applies;
		pk::force@ force;
		int numApply = 0;
	};

	class SpecialForceApply
	{
		SpecialForceItem@ item;
		pk::force@ force;
		pk::list<pk::person@> persons;
	};

	class SpecialForceItem
	{
		int id;
		bool bUse;
		int ����;
		int color;

		array<int> fids;
		array<ForceInfo@> currentForces;

		SpecialForceItem() {}
	};

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

	const int Ư������_�⺴_��ȯ���� = 17;
	const int Ư������_â��_���ֺ� = 18;
	const int Ư������_â��_����� = 19;
	const int Ư������_�뺴_��뺴 = 20;
	const int Ư������_�غ�_õ�ݱ��� = 21;

	const int Ư������_�⺴_�� = 22;
	const int Ư������_â��_ȣ�� = 23;
	const int Ư������_�⺴_�ͼ��� = 24;
	const int Ư������_�뺴_ȸ���� = 25;
	const int Ư������_�غ�_ö���� = 26;
	const int Ư������_�غ�_û�Ǻ� = 27;

	const int ȿ��_���ɻ��_�� = 0;
	const int ȿ��_���ɻ��_�� = 1;
	const int ȿ��_���ɻ��_�� = 2;
	const int ȿ��_���ݻ��_�� = 3;
	const int ȿ��_���ݻ��_�� = 4;
	const int ȿ��_���ݻ��_�� = 5;
	const int ȿ��_�����_�� = 6;
	const int ȿ��_�����_�� = 7;
	const int ȿ��_�����_�� = 8;
	const int ȿ��_����_�� = 9;
	const int ȿ��_����_�� = 10;
	const int ȿ��_����_�� = 11;
	const int ȿ��_�־�_�� = 12;
	const int ȿ��_�־�_�� = 13;
	const int ȿ��_�־�_�� = 14;
	const int ȿ��_����_����_�� = 15;
	const int ȿ��_����_����_�� = 16;
	const int ȿ��_����_����_�� = 17;
	const int ȿ��_����_���_�� = 18;
	const int ȿ��_����_���_�� = 19;
	const int ȿ��_����_���_�� = 20;
	const int ȿ��_�跫_�� = 21;
	const int ȿ��_�跫_�� = 22;
	const int ȿ��_�跫_�� = 23;
	const int ȿ��_�跫���_�� = 24;
	const int ȿ��_�跫���_�� = 25;
	const int ȿ��_�跫���_�� = 26;
	const int ȿ��_������°��� = 27;
	const int ȿ��_�������簨�� = 28;
	const int ȿ��_��������� = 29;
	const int ȿ��_�����ݵ�ü��� = 30;
	const int ȿ��_��� = 31;
	const int ȿ��_���� = 32;
	const int ȿ��_�汹 = 33;
	const int ȿ��_��������ȿ�� = 34;
	const int ȿ��_�������_�� = 35;
	const int ȿ��_�������_�� = 36;
	const int ȿ��_�������_�� = 37;
	const int ȿ��_��ȣ_�� = 38;
	const int ȿ��_��ȣ_�� = 39;
	const int ȿ��_��ȣ_�� = 40;
	const int ȿ��_�̵�_�� = 41;
	const int ȿ��_�̵�_�� = 42;
	const int ȿ��_�̵�_�� = 43;
	const int ȿ��_��_�� = 44;
	const int ȿ��_��_�� = 45;
	const int ȿ��_��_�� = 46;
	const int ȿ��_�跫_���_���� = 47;
	const int ȿ��_�跫_ũ��Ƽ��_�׻󼺰� = 48;
	const int ȿ��_����_ũ��Ƽ��_�׻󼺰� = 49;
	const int ȿ��_����_�Ұ� = 50;
	const int ȿ��_�⺴_����_���_�Ұ� = 51;
	const int ȿ��_�Һ���_ȥ��_�Ұ� = 52;
	const int ȿ��_����_���� = 53;
	const int ȿ��_����_���� = 54;
	const int ȿ��_����_ȭ�� = 55;
	const int ȿ��_���_���_�� = 56;
	const int ȿ��_���_���_�� = 57;
	const int ȿ��_���_���_�� = 58;
	const int ȿ��_����_���_�� = 59;
	const int ȿ��_����_���_�� = 60;
	const int ȿ��_����_���_�� = 61;
	const int ȿ��_����_���_�� = 62;
	const int ȿ��_����_���_�� = 63;
	const int ȿ��_����_���_�� = 64;
	const int ȿ��_��ġ_���_�� = 65;
	const int ȿ��_��ġ_���_�� = 66;
	const int ȿ��_��ġ_���_�� = 67;
	const int ȿ��_�ŷ�_���_�� = 68;
	const int ȿ��_�ŷ�_���_�� = 69;
	const int ȿ��_�ŷ�_���_�� = 70;
	const int ȿ��_�� = 71;


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
	const int ����Ư��_��ұ� = 26;//�ұ��� ���������Դϴ�. 2000���������϶�, 90Ȯ���� �����ϴ�.


	class CustomItem
	{
		pk::person@ owner = null;
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


		CustomItem() {}
		CustomItem(int id0, string str, string path0, array<int> ������ų0, array<int> skills0, int ���, int ����, int ����, int ��ġ��, int �ŷ�, int type0, int value0, int ��������, int ��������)
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
				@owner = pk::get_person(��������);
			}
		}

		void updateOwner(pk::person@ newOwner)
		{
			@owner = newOwner;
		}

	}
	const int KEY_�߷յ��� = pk::hash("�߷յ���_Export");
	const int KEY_�ź��� = pk::hash("�ź���_Export");
	const int KEY_Ư������ = pk::hash("Ư����������_Export");
	const int KEY_�ο�ȿ�� = pk::hash("�ο�ȿ��_Export");

	class UnitInfo
	{
		pk::unit@ unit;
		int y;
	};
	class Main
	{
		pk::func201_t@ prev_callback_201;
		pk::func207_t@ prev_callback_207;
		
		bool _bCritical = false;
		Main()
		{
			
			@prev_callback_201 = cast<pk::func201_t@>(pk::get_func(201));
			pk::reset_func(201);
			pk::set_func(201, pk::func201_t(callback201));                // 202 ���� ���� Ȯ��


			@prev_callback_207 = cast<pk::func207_t@>(pk::get_func(207));
			pk::reset_func(207);
			pk::set_func(207, pk::func207_t(callback207));                // 202 ���� ���� Ȯ��

			pk::menu_item ����Ư��;
			����Ư��.menu = 2;
			����Ư��.is_enabled = pk::menu_item_is_enabled_t(isEnabled);
			����Ư��.get_desc = pk::menu_item_get_desc_t(getDesc_����Ư��);
			����Ư��.get_text = pk::menu_item_get_text_t(getText_����Ư��);
			����Ư��.handler = pk::menu_item_handler_t(handler_����Ư��);
			pk::add_menu_item(����Ư��);
			
			pk::bind(120, pk::trigger120_t(UpdatePerFrame));
			pk::bind(174, pk::trigger174_t(�δ��ൿ�Ϸ�));
			pk::bind(107, pk::trigger107_t(onDay));
			pk::bind(102, pk::trigger102_t(onInit));
			pk::bind(111, pk::trigger111_t(onTurnStart));


		}
		void onDay()
		{
			onDay�߷յ���();
			loadƯ������();
			load�ο�ȿ��();
		}
		void onInit()
		{
			onDay�߷յ���();
			load�ź���();
			loadƯ������();
			load�ο�ȿ��();
		}
		void onTurnStart(pk::force@ f)
		{
			load�ź���();
		}

		bool callback201(pk::unit@ attacker, pk::hex_object@ target, int tactics_id, bool ranged)
		{
			bool b = prev_callback_201(attacker,target,tactics_id,ranged);
			_bCritical = b;
			return b;
		}
		int callback207(pk::unit@ src, const pk::point& in src_pos, const pk::point& in dst_pos, int strategy_id)
		{
			_bCritical = true;
			return prev_callback_207(src, src_pos, dst_pos, strategy_id);
		}
		
		void �δ��ൿ�Ϸ�(pk::unit@ unit)
		{
			_bCritical = false;
		}
		pk::force@ _force;
		pk::building@ _building;
		pk::city@ _city;
		pk::district@ _district;
		bool isEnabled()
		{
			return true;
		}

		string getDesc_����Ư��()
		{
			return pk::encode("������ ���� Ư�⸦ Ȯ���մϴ�.");
		}
		string getText_����Ư��()
		{
			return pk::encode("����Ư��Ȯ��");
		}
		bool handler_����Ư��()
		{
			pk::list<pk::person@> moos;
			for (int i = 0; i < ����_��; i++)
			{
				pk::person@ person = pk::get_person(i);
				if (person == null)
					continue;

				moos.add(person);
			}

			pk::list<pk::person@> person_sel2 = pk::person_selector(pk::encode("���� ����"), pk::encode("������ �����մϴ�."), moos, 1, 1);
			if (person_sel2.count == 0)
				return false;

			string str = "";
			pk::person@ moo = person_sel2[0];
			for (int i = 0; i < 255; i++)
			{
				if (pk::has_skill(moo, i))
				{
					str = str + pk::decode(pk::get_skill(i).get_name()) + " ";
				}
			}
			if (str == "")
			{
				pk::message_box(pk::encode("Ư�Ⱑ �����ϴ�."));
				return true;
			}

			pk::message_box(pk::encode(str), moo);
			return true;
		}
		
		void UpdatePerFrameƯ��()
		{
			pk::point pt = pk::get_cursor_hex_pos();
			auto obj = pk::get_hex_object(pt);
			if (obj == null or obj.get_type_id() != 11)
				return;

			pk::unit@ unit = pk::get_unit(pt);
			if (����_ǥ��)
				����ǥ��(unit);
			else
				����ǥ��(unit);
		}

		array<UnitInfo@> _units = {};
		void UpdatePerFrame�̸�()
		{
			_units = {};
			//UpdatePerFrame�̸�_Ư������();
			//UpdatePerFrame�̸�_�ο�ȿ��();
			//UpdatePerFrame�̸�_�ź���();
			//UpdatePerFrame�̸�_�߷յ���();

		}

		UnitInfo@ getUnit(pk::unit@ u)
		{
			if (u == null)
				return null;
			for (int i = 0; i < _units.length; i++)
			{
				UnitInfo@ ui = _units[i];
				if (ui.unit.get_id() == u.get_id())
					return ui;
			}
			return null;
		}

		void UpdatePerFrame()
		{
			//pk::unit@ unit = pk::get_selected_unit();
			//if (unit == null)
			//	return;

			if (_bCritical)
				return;
			UpdatePerFrameƯ��();
			UpdatePerFrame�̸�();
		}
		void ����ǥ��(pk::unit@ unit)
		{
			string str;
			if (!���庰Ư��ǥ��)
			{
				array<int> arr;
				for (int i = 0; i < 255; i++)
				{
					pk::person@ p0 = pk::get_person(unit.member[0]);
					pk::person@ p1 = pk::get_person(unit.member[1]);
					pk::person@ p2 = pk::get_person(unit.member[2]);
					if ((p0 != null and pk::has_skill(p0, i)) or
						(p1 != null and pk::has_skill(p1, i)) or
						(p2 != null and pk::has_skill(p2, i)))
					{
						arr.insertLast(i);
					}
				}
				if (arr.length == 0)
					return;

				arr.sort(function(a, b)
				{
					pk::skill@ s0 = pk::get_skill(a);
					pk::skill@ s1 = pk::get_skill(b);
					return s0.type <= s1.type;
				});


				for (int i = 0; i < arr.length; i++)
				{
					if (i != arr.length - 1)
						str = str + pk::decode(pk::get_skill(arr[i]).name) + " ";
					else
						str = str + pk::decode(pk::get_skill(arr[i]).name);
				}
			}
			else
			{
				array<array<int>> arrs = { array<int>(),array<int>() ,array<int>() };
				if (unit.member[0] >= 0 and unit.member[0] < ����_��)
				{
					for (int i = 0; i < 255; i++)
					{
						pk::person@ p0 = pk::get_person(unit.member[0]);
						if (p0 != null and pk::has_skill(p0, i))
							arrs[0].insertLast(i);
					}
				}
				if (unit.member[1] >= 0 and unit.member[1] < ����_��)
				{
					for (int i = 0; i < 255; i++)
					{
						pk::person@ p0 = pk::get_person(unit.member[1]);
						if (p0 != null and pk::has_skill(p0, i))
							arrs[1].insertLast(i);
					}
				}
				if (unit.member[2] >= 0 and unit.member[2] < ����_��)
				{
					array<int> arr;
					for (int i = 0; i < 255; i++)
					{
						pk::person@ p0 = pk::get_person(unit.member[2]);
						if (p0 != null and pk::has_skill(p0, i))
							arrs[2].insertLast(i);
					}
				}

				str = "";
				for (int i = 0; i < arrs.length; i++)
				{
					if (i != 0)
						str = str + ",";
					if (unit.member[i] >= 0 and unit.member[i] < ����_��)
					{
						str = str + pk::format("\x1b[1x{}\x1b[0x", pk::decode(pk::get_name(pk::get_person(unit.member[i])))) + ":";
						if (arrs[i].length == 0)
							str = str + "����";
						else
						{
							for (int j = 0; j < arrs[i].length; j++)
							{
								if (j != arrs[i].length - 1)
									str = str + pk::decode(pk::get_skill(arrs[i][j]).name) + " ";
								else
									str = str + pk::decode(pk::get_skill(arrs[i][j]).name);
							}
						}
					}
				}
			}

			string str2 = pk::format("��:{},��:{},��:{},��:{},��:{},��:{}"
				, unit.attr.stat[�δ�ɷ�_����], unit.attr.stat[�δ�ɷ�_���], unit.attr.stat[�δ�ɷ�_���],
				unit.attr.stat[�δ�ɷ�_����], unit.attr.stat[�δ�ɷ�_����], unit.attr.stat[�δ�ɷ�_��ġ]);


			pk::point point3 = pk::get_neighbor_pos(unit.get_pos(), ����_����, 1);
			pk::point point4 = pk::hex_pos_to_screen_pos(point3);

			pk::point point2 = point4;
			point2.y += 40;


			pk::size size0 = pk::get_size(FONT_SMALL, pk::encode(str2));
			pk::size size1 = pk::get_size(FONT_SMALL, pk::encode(str));

			size0.width += 5;
			size0.height *= 1.25;
			size1.width += 5;
			size1.height *= 1.25;


			point4.x = (point2.x + point4.x) * 0.5;
			point4.y = (point2.y + point4.y) * 0.5;

			pk::draw_text(pk::encode(str), point2);
			pk::draw_text(pk::encode(str2), point4);

			pk::rectangle r0(point4, size0);
			pk::rectangle r1(point2, size1);

			pk::draw_filled_rect(r0, 0x40000000);
			pk::draw_filled_rect(r1, 0x40000000);

			int offY = 60;

			string str�߷յ��� = UpdateFrameȮ��_�߷յ���_����(unit);
			if (str�߷յ��� != "")
			{
				point3 = pk::get_neighbor_pos(unit.get_pos(), ����_����, 1);
				point4 = pk::hex_pos_to_screen_pos(point3);
				point2 = point4;
				point2.y += offY;
				offY += 20;

				pk::draw_text(pk::encode(str�߷յ���), point2, �߷յ���_ǥ���÷�);
			}
			
			string str�߷յ���2 = get�߷յ����̸�(unit, false);
			if (str�߷յ���2 != "")
			{
				point3 = pk::get_neighbor_pos(unit.get_pos(), ����_����, 1);
				point4 = pk::hex_pos_to_screen_pos(point3);
				point2 = point4;
				point2.y += offY;
				offY += 20;

				pk::draw_text(pk::encode(str�߷յ���2), point2, �߷յ���_ǥ���÷�);
			}

			string str�ź��� = UpdateFrameȮ��_�ź���(unit);
			if(str�ź��� != "")
			{
				point3 = pk::get_neighbor_pos(unit.get_pos(), ����_����, 1);
				point4 = pk::hex_pos_to_screen_pos(point3);
				point2 = point4;
				point2.y += offY;
				offY += 20;

				pk::draw_text(pk::encode(str�ź���), point2, �ź���_ǥ���÷�);
			}
			string str�ο�ȿ�� = UpdateFrameȮ��_�ο�ȿ��(unit);
			if (str�ο�ȿ�� != "")
			{
				point3 = pk::get_neighbor_pos(unit.get_pos(), ����_����, 1);
				point4 = pk::hex_pos_to_screen_pos(point3);
				point2 = point4;
				point2.y += offY;
				offY += 20;

				pk::draw_text(pk::encode(str�ο�ȿ��), point2, �ο�ȿ��_ǥ���÷�);
			}

		}
		void ����ǥ��(pk::unit@ unit)
		{
			array<array<int>> arrs = { array<int>(),array<int>() ,array<int>() };
			if (unit.member[0] >= 0 and unit.member[0] < ����_��)
			{
				for (int i = 0; i < 255; i++)
				{
					pk::person@ p0 = pk::get_person(unit.member[0]);
					if (p0 != null and pk::has_skill(p0, i))
						arrs[0].insertLast(i);
				}
			}
			if (unit.member[1] >= 0 and unit.member[1] < ����_��)
			{
				for (int i = 0; i < 255; i++)
				{
					pk::person@ p0 = pk::get_person(unit.member[1]);
					if (p0 != null and pk::has_skill(p0, i))
						arrs[1].insertLast(i);
				}
			}
			if (unit.member[2] >= 0 and unit.member[2] < ����_��)
			{
				array<int> arr;
				for (int i = 0; i < 255; i++)
				{
					pk::person@ p0 = pk::get_person(unit.member[2]);
					if (p0 != null and pk::has_skill(p0, i))
						arrs[2].insertLast(i);
				}
			}

			string str = "";
			str= pk::format("��:{},��:{},��:{},��:{},��:{},��:{}"
				, unit.attr.stat[�δ�ɷ�_����], unit.attr.stat[�δ�ɷ�_���], unit.attr.stat[�δ�ɷ�_���],
				unit.attr.stat[�δ�ɷ�_����], unit.attr.stat[�δ�ɷ�_����], unit.attr.stat[�δ�ɷ�_��ġ]);

			pk::point point1 = pk::get_neighbor_pos(unit.get_pos(), ����_��, 1);
			pk::point point2 = pk::hex_pos_to_screen_pos(point1);

			pk::size size0 = pk::get_size(FONT_SMALL, str);
			size0.width += 5;
			size0.height *= 1.25;

			pk::draw_text(pk::encode(str), point2);
			pk::rectangle r0(point2, size0);
			pk::draw_filled_rect(r0, 0x40000000);

			int h = 20;
			str = "";
			for (int i = 0; i < arrs.length; i++)
			{
				if (unit.member[i] <0 || unit.member[i] >= ����_��)
					continue;

				str = "";
				str = str + pk::format("\x1b[1x{}\x1b[0x", pk::decode(pk::get_name(pk::get_person(unit.member[i])))) + ":";
				if (arrs[i].length == 0)
					str = str + "����";
				else
				{
					for (int j = 0; j < arrs[i].length; j++)
					{
						if (j != arrs[i].length - 1)
							str = str + pk::decode(pk::get_skill(arrs[i][j]).name) + " ";
						else
							str = str + pk::decode(pk::get_skill(arrs[i][j]).name);
					}
				}

				pk::point point3 = pk::get_neighbor_pos(unit.get_pos(), ����_��, 1);
				pk::point point4 = pk::hex_pos_to_screen_pos(point3);
				point4.y += h;

				pk::size size1 = pk::get_size(FONT_SMALL, pk::encode(str));
				size1.width += 5;
				size1.height *= 1.25;

				pk::draw_text(pk::encode(str), point4);
				pk::rectangle r1(point4, size1);
				pk::draw_filled_rect(r1, 0x40000000);

				h += 20;
			}
		}

		///�߷յ���////////////////////
		array<pk::person@> _�߷յ�������Ʈ;
		array < array<pk::person@>> _�߷յ�����ŷ����Ʈ;
		array<array<array<int>>> _�߷յ���Ư�⸮��Ʈ;
		int _�߷յ���_Ư��_���� = 0;

		bool check�߷յ���(pk::person@ p, int type)
		{
			if (p == null)
				return false;
			if (_�߷յ�������Ʈ.length == 0)
				return false;
			for (int i = 0; i < _�߷յ�������Ʈ.length; i++)
			{
				pk::person@ pi = _�߷յ�������Ʈ[i];
				if (pi.get_id() == p.get_id())
				{
					array<int> arr = _�߷յ���Ư�⸮��Ʈ[0][i];
					if (arr.find(type) >= 0)
						return true;
				}
			}

			for (int i = 0; i < _�߷յ�����ŷ����Ʈ.length; i++)//i����
			{
				array<pk::person@> pis = _�߷յ�����ŷ����Ʈ[i];
				for (int j = 0; j < pis.length; j++)//j����
				{
					pk::person@ pi = pis[j];
					if (pi.get_id() == p.get_id())
					{
						array<array<int>> arr = _�߷յ���Ư�⸮��Ʈ[i + 1];
						if (j >= arr.length)
							continue;
						if (arr[j].find(type) >= 0)
							return true;
					}
				}
			}

			return false;
		}
		int onDay�߷յ���_Ư��(int li)
		{
			int count = int(pk::load(KEY_�߷յ���, li++, 0));
			array<array<int>> arr;

			for (int i = 0; i < count; i++)
			{
				array<int> arr0;
				int count2 = int(pk::load(KEY_�߷յ���, li++, 0));
				for (int j = 0; j < count2; j++)
				{
					int a=int(pk::load(KEY_�߷յ���, li++, 0));
					arr0.insertLast(a);
				}
				arr.insertLast(arr0);
			}
			_�߷յ���Ư�⸮��Ʈ.insertLast(arr);
			return li;
		}
		void onDay�߷յ���()
		{
			_�߷յ�������Ʈ = {};
			_�߷յ�����ŷ����Ʈ = {};
			_�߷յ���Ư�⸮��Ʈ = {};
			int count = int(pk::load(KEY_�߷յ���, 0, 0));
			if (count == 0)
				return;

			int li = 1;
			for (int i = 0; i < count; i++)
			{
				pk::person@ p = pk::get_person(int(pk::load(KEY_�߷յ���, li++, 0)));
				//pk::printf("�߷յ��� {} ,{}\n", i, getName(p));
				_�߷յ�������Ʈ.insertLast(p);
			}

			int count2 = int(pk::load(KEY_�߷յ���, li++, 0));
			for (int i = 0; i < count2; i++)
			{

				array<pk::person@> arr;
				int count3 = int(pk::load(KEY_�߷յ���, li++, 0));
				for (int j = 0; j < count3; j++)
				{
					pk::person@ p = pk::get_person(int(pk::load(KEY_�߷յ���, li++, 0)));
					arr.insertLast(p);
				}
				_�߷յ�����ŷ����Ʈ.insertLast(arr);
			}

			for (int i = 0; i < 25; i++)
			{
				li=onDay�߷յ���_Ư��(li);
			}

			_�߷յ���_Ư��_���� = int(pk::load(KEY_�߷յ���, li++, 0));

		}

		string UpdateFrameȮ��_�߷յ���_����(pk::unit@ unit)
		{
			if (_�߷յ�������Ʈ.length == 0)
				return "";

			array<array<int>> arrs = { array<int>(),array<int>() ,array<int>() };
			if (unit.member[0] >= 0 and unit.member[0] < ����_��)
			{
				for (int i = 0; i < _�߷յ���_Ư��_����; i++)
				{
					pk::person@ p0 = pk::get_person(unit.member[0]);
					if (p0 != null and check�߷յ���(p0, i))
						arrs[0].insertLast(i);
				}
			}
			if (unit.member[1] >= 0 and unit.member[1] < ����_��)
			{
				for (int i = 0; i < _�߷յ���_Ư��_����; i++)
				{
					pk::person@ p0 = pk::get_person(unit.member[1]);
					if (p0 != null and check�߷յ���(p0, i))
						arrs[1].insertLast(i);
				}
			}
			if (unit.member[2] >= 0 and unit.member[2] < ����_��)
			{
				array<int> arr;
				for (int i = 0; i < _�߷յ���_Ư��_����; i++)
				{
					pk::person@ p0 = pk::get_person(unit.member[2]);
					if (p0 != null and check�߷յ���(p0, i))
						arrs[2].insertLast(i);
				}
			}

			string str = "";
			for (int i = 0; i < arrs.length; i++)
			{
				if (arrs[i].length == 0)
					continue;
				if (unit.member[i] >= 0 and unit.member[i] < ����_��)
				{
					if (str != "")
						str = str + ",";

					str = str + pk::format("\x1b[1x{}\x1b[0x", pk::decode(pk::get_name(pk::get_person(unit.member[i])))) + ":";
					for (int j = 0; j < arrs[i].length; j++)
					{
						string strName;
						switch (arrs[i][j])
						{
						case 0:strName = "�����ൿ"; break;
						case 1:strName = "�ɰ�(��)"; break; case  2:strName = "�ɰ�(��)"; break; case 3:strName = "�ɰ�(��)"; break;
						case 4:strName = "�־�(��)"; break; case  5:strName = "�־�(��)"; break; case 6:strName = "�־�(��)"; break;
						case 7:strName = "��ǳ(��)"; break; case  8:strName = "��ǳ(��)"; break; case 9:strName = "��ǳ(��)"; break;
						case 10:strName = "�ݰ�"; break; case  11:strName = "�ұ�"; break; case 12:strName = "ö��"; break;
						case 13:strName = "�"; break;	case 14:strName = "���"; break;	case 15:strName = "����"; break;
						case 16:strName = "����(��)"; break; case  17:strName = "����(��)"; break; case 18:strName = "����(��)"; break;
						case 19:strName = "����(��)"; break; case  20:strName = "����(��)"; break; case 21:strName = "����(��)"; break;
						case 22:strName = "ũ��Ƽ��"; break; case 23:strName = "�ý�"; break;
						case 24:strName = "���÷���(��)"; break; case 25:strName = "���÷���(��)"; break; case 26:strName = "���÷���(��)"; break;
						case 27:strName = "���ݷ�(��)"; break; case 28:strName = "���ݷ�(��)"; break; case 29:strName = "���ݷ�(��)"; break;
						case 30:strName = "����(��)"; break; case 31:strName = "����(��)"; break; case 32:strName = "����(��)"; break;
						case 33:strName = "�ϱ���(��)"; break; case 34:strName = "�ϱ���(��)"; break; case 35:strName = "�ϱ���(��)"; break;
						case 36:strName = "��(��)"; break; case 37:strName = "��(��)"; break; case 38:strName = "��(��)"; break;
						case 39:strName = "�ɸ�(��)"; break; case 40:strName = "�ɸ�(��)"; break; case 41:strName = "�ɸ�(��)"; break;
						case 42:strName = "�Ż�"; break; case 43:strName = "���"; break; case 44:strName = "�ɸ�"; break;
						case 45:strName = "��ȯ"; break; case 49:strName = "���ھȵ�"; break;
						case 46:strName = "�⺴���(��)"; break; case 47:strName = "�⺴���(��)"; break; case 48:strName = "�⺴���(��)"; break;
						case 50:strName = "�Һ���(��)"; break; case 51:strName = "�Һ���(��)"; break; case 52:strName = "�Һ���(��)"; break;
						case 53:strName = "����(��)"; break; case 54:strName = "����(��)"; break; case 55:strName = "����(��)"; break;
						case 56:strName = "�跫(��)"; break; case 57:strName = "�跫(��)"; break; case 58:strName = "�跫(��)"; break;
						case 59:strName = "�̼�(��)"; break; case 60:strName = "�̼�(��)"; break; case 61:strName = "�̼�(��)"; break;
						case 62:strName = "����(��)"; break; case 63:strName = "����(��)"; break; case 64:strName = "����(��)"; break;
						default:
							break;
						}
						if (j != arrs[i].length - 1)
							str = str + pk::format("{} ", strName);
						else
							str = str + pk::format("{}", strName);
					}
				}
			}
			return str;
		}


		void UpdatePerFrame�̸�_�߷յ���()
		{
			if (_�߷յ�������Ʈ.length == 0)
				return;

			array<pk::unit@> arr;
			for (int i = 0; i < _�߷յ�������Ʈ.length; i++)
			{
				pk::person@ pi = _�߷յ�������Ʈ[i];
				pk::unit@ u = pk::is_valid_pos(pi.get_pos()) ? pk::get_unit(pi.get_pos()) : null;
				if (u == null)
					continue;
				if (arr.findByRef(u) == -1)
					arr.insertLast(u);
			}

			for (int i = 0; i < _�߷յ�����ŷ����Ʈ.length; i++)
			{
				array<pk::person@> arr2 = _�߷յ�����ŷ����Ʈ[i];
				for (int j = 0; j < arr2.length; j++)
				{
					pk::person@ pi = arr2[j];
					pk::unit@ u = pk::is_valid_pos(pi.get_pos()) ? pk::get_unit(pi.get_pos()) : null;
					if (u == null)
						continue;
					if (arr.findByRef(u) == -1)
						arr.insertLast(u);
				}
			}


			_UpdateFrameName(arr);
		}

		string get�߷յ����̸�(pk::unit@ u,bool b�̸�)
		{
			array<string> strs;
			string str = "";
			int br = getBallonRank(u);
			if (br == 1)
				str = str + "�߷յ���";
			else if (br <= 10)
				str = str + pk::format("�߷յ���{}��", br);

			int minBR = 100;
			string str2 = "";
			for (int j = 0; j < 22; j++)
			{
				br = getRank(u, j);
				if (br <= 3)
				{
					string strType = "";
					switch (j)
					{
					case 0: strType = "���"; break;
					case 1: strType = "����"; break;
					case 2: strType = "����"; break;
					case 3: strType = "��ġ"; break;
					case 4: strType = "�ŷ�"; break;
					case 5: strType = "â��"; break;
					case 6: strType = "�غ�"; break;
					case 7: strType = "�뺴"; break;
					case 8: strType = "�⺴"; break;
					case 9: strType = "����"; break;
					case 10: strType = "����"; break;
					case 11: strType = "����"; break;
					case 12: strType = "����"; break;
					case 13: strType = "��������"; break;
					case 14: strType = "�˸�"; break;
					case 15: strType = "����"; break;
					case 16: strType = "����"; break;
					case 17: strType = "Damage"; break;
					case 18: strType = "���";  break;
					case 19: strType = "�������";  break;
					case 20: strType = "�ϱ��";  break;
					case 21: strType = "�ϱ�����";  break;
					case 22: strType = "�跫"; break;
					case 23: strType = "�跫����";  break;
					default:
						break;
					}

					if (br < minBR)
					{
						minBR = br;
						if (minBR == 1)
							str2 = pk::format("{}��", strType);
						else
							str2 = pk::format("{}{}��", strType, br);
					}
					if (!b�̸�)
					{
						if (br == 1)
						{
							if (str == "")
								str = str + pk::format("{}��", strType);
							else
								str = str + pk::format(",{}��", strType);
						}
						else
						{
							if (str == "")
								str = str + pk::format("{}{}��", strType, br);
							else
								str = str + pk::format(",{}{}��", strType, br);
						}

						//pk::size sz = pk::get_size(FONT_SMALL, pk::encode(str));
						//if (sz.width > �߷յ���_���λ�����)
						//{
						//	strs.insertLast(str);
						//	str = "";
						//}
					}
					strs.insertLast("");
				}
			}
			if (strs.length == 0 && str == "")
				return "";

			if (!b�̸�)
				return str;
			if (str != "")
			{
				if (strs.length > 0)
					str = pk::format("{}({})", str, strs.length + 1);
				else
					str = pk::format("{}", str);
			}
			else
			{
				if (strs.length > 1)
					str = pk::format("{}({})", str2, strs.length);
				else
					str = pk::format("{}", str2);
			}

			return str;
		}

		void _UpdateFrameName(array<pk::unit@> units)
		{
			for (int i = 0; i < units.length; i++)
			{
				pk::unit@ u = units[i];
				if (!pk::is_in_screen(u.get_pos()))
					continue;
				string str = get�߷յ����̸�(u,true);
				if(str=="")
					continue;

				array<string> strs2;
				strs2.insertLast(str);

				for (int j = 0; j < strs2.length; j++)
				{
					pk::point point = pk::hex_pos_to_screen_pos(u.get_pos());

					str = strs2[j];
					UnitInfo@ ui = getUnit(u);
					if (ui == null)
					{
						@ui = UnitInfo();
						ui.y = 0;
						@ui.unit = u;
						_units.insertLast(ui);
					}
					point.y += ui.y;
					ui.y += 20;
					pk::draw_text(pk::encode(str), point, �߷յ���_ǥ���÷�);
					if (true)
					{
						pk::size size0 = pk::get_size(FONT_SMALL, pk::encode(str));
						pk::rectangle r0(point, size0);
						pk::draw_filled_rect(r0, 0x40000000);
					}
				}
			}
		}

		int getBallonRank(pk::unit@ u)
		{
			int a = getBallonRank(pk::get_person(u.member[0]));
			int b = getBallonRank(pk::get_person(u.member[1]));
			int c = getBallonRank(pk::get_person(u.member[2]));
			return pk::min(pk::min(a, b), c);
		}
		int getRank(pk::unit@ u, int type)
		{
			int a = getRank(pk::get_person(u.member[0]), type);
			int b = getRank(pk::get_person(u.member[1]), type);
			int c = getRank(pk::get_person(u.member[2]), type);
			return pk::min(pk::min(a, b), c);
		}

		int getBallonRank(pk::person@ p)
		{
			if (p == null)
				return 100;
			if (_�߷յ�������Ʈ.length == 0)
				return 100;
			for (int i = 0; i < _�߷յ�������Ʈ.length; i++)
			{
				pk::person@ pi = _�߷յ�������Ʈ[i];
				if (pi.get_id() == p.get_id())
				{
					return i + 1;
				}
			}
			return 100;
		}
		int getRank(pk::person@ p, int type)
		{
			if (p == null)
				return 100;
			if (_�߷յ�����ŷ����Ʈ.length == 0)
				return 100;
			array<pk::person@> pis = _�߷յ�����ŷ����Ʈ[type];
			for (int j = 0; j < pis.length; j++)//j����
			{
				pk::person@ pi = pis[j];
				if (pi.get_id() == p.get_id())
				{
					return j + 1;
				}
			}
			return 100;
		}
		///�ź���////////////////////////////////////////////////////////////////

		void load�ź���()
		{
			for (int i = 0; i < Ŀ���Ҿ����۽�.length; i++)
			{
				CustomItem@ ci = Ŀ���Ҿ����۽�[i];
				@ci.owner = null;
			}
			int count = int(pk::load(KEY_�ź���, 0, 0));
			int li = 1;
			if (count == 0)
			{
				return;
			}
			for (int i = 0; i < count; i++)
			{
				CustomItem@ ci = Ŀ���Ҿ����۽�[i];
				int oid = int(pk::load(KEY_�ź���, li++, -1));
				if (ci != null)
					@ci.owner = pk::get_person(oid);
			}
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
				if (ci == null)
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

		void UpdatePerFrame�̸�_�ź���()
		{
			array<pk::unit@> us;
			for (int i = 0; i < Ŀ���Ҿ����۽�.length; i++)
			{
				CustomItem@ ci = Ŀ���Ҿ����۽�[i];
				if (ci.owner == null)
					continue;
				pk::unit@ u = getUnit(ci.owner.get_pos());
				if (u == null)
					continue;
				if (!pk::is_in_screen(ci.owner.get_pos()))
					continue;

				if(us.findByRef(u)==-1)
					us.insertLast(u);
			}
			
			for (int i = 0; i < us.length; i++)
			{
				pk::unit@ u = us[i];
				array<CustomItem@> arr=getCustomItem(u);
				string str;
				for (int j = 0; j < arr.length; j++)
				{
					CustomItem@ ci = arr[j];
					if (j == 0)
						str = str + ci.name;
					else
						str = str + " " + ci.name;
				}
				UnitInfo@ ui = getUnit(u);
				if (ui == null)
				{
					@ui = UnitInfo();
					ui.y = 0;
					@ui.unit = u;
					_units.insertLast(ui);
				}
				pk::point point = pk::hex_pos_to_screen_pos(u.get_pos());
				point.y += ui.y;
				ui.y += 20;
				pk::draw_text(pk::encode(str), point, �ź���_ǥ���÷�);
				if (true)
				{
					pk::size size0 = pk::get_size(FONT_SMALL, pk::encode(str));
					pk::rectangle r0(point, size0);
					pk::draw_filled_rect(r0, 0x40000000);
				}
			}

		}

		string UpdateFrameȮ��_�ź���(pk::unit@ unit)
		{
			array<array<CustomItem@>> arrs = { array<CustomItem@>(),array<CustomItem@>() ,array<CustomItem@>() };
			if (unit.member[0] >= 0 and unit.member[0] < ����_��)
			{
				pk::person@ p0 = pk::get_person(unit.member[0]);
				array<CustomItem@> arr=getCustomItem(p0);
				arrs[0] = arr;
			}
			if (unit.member[1] >= 0 and unit.member[1] < ����_��)
			{
				pk::person@ p0 = pk::get_person(unit.member[1]);
				array<CustomItem@> arr = getCustomItem(p0);
				arrs[1] = arr;
			}
			if (unit.member[2] >= 0 and unit.member[2] < ����_��)
			{
				pk::person@ p0 = pk::get_person(unit.member[2]);
				array<CustomItem@> arr = getCustomItem(p0);
				arrs[2] = arr;
			}
			string str = "";
			for (int i = 0; i < arrs.length; i++)
			{
				array<CustomItem@> arr = arrs[i];
				if(arr.length ==0)
					continue;

				pk::person@ p = pk::get_person(unit.member[i]);
				str = str + pk::format("\x1b[1x{}\x1b[0x", pk::decode(pk::get_name(pk::get_person(unit.member[i])))) + ":";
				string str2 = "";
				for (int j = 0; j < arr.length; j++)
				{
					CustomItem@ ci = arr[j];
					for (int k = 0; k < ci.skills����.length; k++)
					{
						string strType = "";
						switch (ci.skills����[k])
						{
						case ����Ư��_������_ȭ��߻�: strType = "ȭ�����"; break;
						case ����Ư��_����_ȥ��_����_����: strType = "��������"; break;
						case ����Ư��_����_ȭ��_��ȭ: strType = "������ȭ"; break;
						case ����Ư��_����_����: strType = "��������"; break;
						case ����Ư��_����_���÷���_������: strType = "���÷���"; break;
						case ����Ư��_������_�߰�������: strType = "�߰�������"; break;
						case ����Ư��_�־�: strType = "�����־�"; break;
						case ����Ư��_������_�漺��_����: strType = "�漺������"; break;
						case ����Ư��_��ǳ: strType = "������ǳ"; break;
						case ����Ư��_�ɰ�: strType = "�����ɰ�"; break;
						case ����Ư��_��ų: strType = "��ų"; break;
						case ����Ư��_����Ż��: strType = "����Ż��"; break;
						case ����Ư��_ȥ��_����: strType = "ȥ��"; break;
						case ����Ư��_����_����: strType = "����"; break;
						case ����Ư��_����_����: strType = "����"; break;
						case ����Ư��_�ϱ���_����: strType = "�ϱ���"; break;
						case ����Ư��_�����δ�_�ǹ�������_�߰�: strType = "�ǹ�������"; break;
						case ����Ư��_�ⱳ����Ʈ_ȹ��: strType = "�ⱳ����Ʈ"; break;
						case ����Ư��_�ɷ¿����ӵ����: strType = "�ɷ¿����ӵ�"; break;
						case ����Ư��_���׿�: strType = "���׿�"; break;
						case ����Ư��_�λ�����: strType = "��������"; break;
						case ����Ư��_���Ư�����: strType = "���Ư�����"; break;
						case ����Ư��_ȥ��: strType = "ȥ��"; break;
						case ����Ư��_����: strType = "����"; break;
						case ����Ư��_�������: strType = "�������"; break;
						case ����Ư��_����_ȸ��: strType = "����ȸ��"; break;
						case ����Ư��_��ұ�:	strType = "��ұ�"; break;
						default:
							break;
						}
						if(strType=="")
							continue;
						if(str2=="")
							str2 = strType;
						else
							str2 = str2 + " " + strType;
					}
					for (int k = 0; k < ci.skills.length; k++)
					{
						pk::skill@ s = pk::get_skill(ci.skills[k]);
						if(str2=="")
							str2 = pk::decode(s.name);
						else
							str2 = str2 + " " + pk::decode(s.name);
					}
				}
				str = str + str2;
			}
			return str;

		}
		//Ư������////////////////////////////////////////////////

		array<SpecialForceItem@> Ư����������Ʈ;
		array<ForceInfo@> ���¸���Ʈ;

		void loadƯ������()
		{
			Ư����������Ʈ = {};
			���¸���Ʈ = {};

			int count = int(pk::load(KEY_Ư������, 0, 0));
			if (count == 0)
				return;

			int li = 1;
			for (int i = 0; i < count; i++)
			{
				SpecialForceItem sf;
				sf.id = int(pk::load(KEY_Ư������, li++, 0));
				sf.bUse = int(pk::load(KEY_Ư������, li++, 0)) == 1 ? true : false;
				sf.���� = int(pk::load(KEY_Ư������, li++, 0));
				sf.color = int(pk::load(KEY_Ư������, li++, 0));

				int count22 = int(pk::load(KEY_Ư������, li++, 0));
				sf.currentForces = {};
				sf.fids = {};
				for (int j = 0; j < count22; j++)
				{
					int fid = int(pk::load(KEY_Ư������, li++, 0));
					sf.fids.insertLast(fid);
				}
				Ư����������Ʈ.insertLast(sf);
			}


			int count2 = int(pk::load(KEY_Ư������, li++, 0));
			for (int i = 0; i < count2; i++)
			{
				ForceInfo fi;
				int fid = int(pk::load(KEY_Ư������, li++, -1));
				@fi.force = fid >= 0 ? pk::get_force(fid) : null;
				fi.numApply = int(pk::load(KEY_Ư������, li++, 0));
				for (int j = 0; j < fi.numApply; j++)
				{
					SpecialForceApply sfa;
					@sfa.force = fi.force;
					int fid2 = int(pk::load(KEY_Ư������, li++, -1));
					@sfa.item = Ư����������Ʈ[fid2];

					int count22 = int(pk::load(KEY_Ư������, li++, -1));
					for (int k = 0; k < count22; k++)
					{
						int pid = int(pk::load(KEY_Ư������, li++, -1));
						pk::person@ p = pk::get_person(pid);
						sfa.persons.add(p);
					}

					fi.applies.insertLast(sfa);
				}


				���¸���Ʈ.insertLast(fi);
			}


			for (int i = 0; i < Ư����������Ʈ.length; i++)
			{
				SpecialForceItem@ sf = Ư����������Ʈ[i];
				for (int j = 0; j < sf.fids.length; j++)
				{
					int fid = sf.fids[j];
					ForceInfo@ fi = null;
					for (int k = 0; k < ���¸���Ʈ.length; k++)
					{
						ForceInfo@ fi0 = ���¸���Ʈ[k];
						if (fi0.force.get_id() == fid)
						{
							@fi = fi0;
							break;
						}
					}
					if(fi==null)
						continue;
					
					sf.currentForces.insertLast(fi);
				}
			}

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
		bool isSkill(pk::person@ f, int type)
		{
			if (f == null)
				return false;
			SpecialForceItem@ sf = getForceItem(type);
			if (sf == null)
				return false;

			if (!sf.bUse)
				return false;
			for (int i = 0; i < sf.currentForces.length; i++)
			{
				ForceInfo@ fi = sf.currentForces[i];
				if (fi == null)
					continue;
				if (fi.force.get_id() != f.get_force_id())
					continue;

				for (int j = 0; j < fi.applies.length; j++)
				{
					SpecialForceApply@ sa = fi.applies[j];
					if (sa.item.id != type)
						continue;
					for (int k = 0; k < sa.persons.count; k++)
					{
						if (sa.persons[k].get_id() == f.get_id())
							return true;
						//if (sa.persons.contains(f))
							//return true;
					}
				}
			}
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
		SpecialForceItem@ getForceItem(int type)
		{
			return Ư����������Ʈ[type];
		}
		pk::unit@ getUnit(pk::point pos)
		{
			return pk::is_valid_pos(pos) ? pk::get_unit(pos) : null;
		}

		void UpdatePerFrame�̸�_Ư������()
		{
			for (int i = 0; i < ���¸���Ʈ.length; i++)
			{
				ForceInfo@ fi = ���¸���Ʈ[i];

				array<pk::unit@> units;
				for (int j = 0; j < fi.applies.length; j++)
				{
					SpecialForceApply@ sa = fi.applies[j];
					if (sa == null)
						continue;
					for (int k = 0; k < sa.persons.count; k++)
					{
						pk::person@ p = sa.persons[k];
						if (!pk::is_in_screen(p.get_pos()))
							continue;
						pk::unit@ u = getUnit(p.get_pos());
						if (u == null)
							continue;
						if (!check����(u, sa.item.����))
							continue;
						if (units.findByRef(u) == -1)
							units.insertLast(u);
					}//k
				}//j

				for (int j = 0; j < units.length; j++)
				{
					pk::unit@ u = units[j];
					string str = "";

					int color = 0;
					for (int k = 0; k < Ư����������Ʈ.length; k++)
					{
						SpecialForceItem sf = Ư����������Ʈ[k];
						if (!sf.bUse)
							continue;
						if (!isSkill(u, k))
						{
							continue;
						}

						string name = "";
						switch (sf.id)
						{
						case Ư������_�⺴_�鸶����: name = "�鸶����"; break;
						case Ư������_�⺴_����ö��: name = "����ö��"; break;
						case Ư������_�⺴_ȣǥ��: name = "ȣǥ��"; break;
						case Ư������_�⺴_������: name = "������"; break;
						case Ư������_â��_û�ֺ�: name = "û�ֺ�"; break;
						case Ư������_â��_���̺�: name = "���̺�"; break;
						case Ư������_â��_��ػ�: name = "��ػ�"; break;
						case Ư������_â��_�����: name = "�����"; break;
						case Ư������_�غ�_�ܾ纴: name = "�ܾ纴"; break;
						case Ư������_�غ�_�ع���: name = "�ع���"; break;
						case Ư������_�غ�_���: name = "���"; break;
						case Ư������_�غ�_������: name = "������"; break;
						case Ư������_�뺴_���뺴: name = "���뺴"; break;
						case Ư������_�뺴_�����: name = "�����"; break;
						case Ư������_�뺴_���뺴: name = "���뺴"; break;
						case Ư������_�뺴_���踸��: name = "���踸��"; break;
						case Ư������_�뺴_��������: name = "��������"; break;
						case Ư������_�⺴_��ȯ����: name = "��ȯ����"; break;
						case Ư������_â��_���ֺ�: name = "���ֺ�"; break;
						case Ư������_â��_�����: name = "�����"; break;
						case Ư������_�뺴_��뺴: name = "��뺴"; break;
						case Ư������_�غ�_õ�ݱ���: name = "õ�ݱ���"; break;
						case Ư������_�⺴_��: name = "��"; break;
						case Ư������_â��_ȣ��: name = "ȣ��"; break;
						case Ư������_�⺴_�ͼ���: name = "�ͼ���"; break;
						case Ư������_�뺴_ȸ����: name = "ȸ����"; break;
						case Ư������_�غ�_ö����: name = "ö����"; break;
						case Ư������_�غ�_û�Ǻ�: name = "û�Ǻ�"; break;
						default:
							break;
						}


						if (str == "")
							str = str + pk::format("{}", name);
						else
							str = str + pk::format(" {}", name);

						color = sf.color;
					}
					if (str == "")
						continue;


					pk::point point = pk::hex_pos_to_screen_pos(u.get_pos());

					UnitInfo@ ui = getUnit(u);
					if (ui == null)
					{
						@ui = UnitInfo();
						ui.y = 0;
						@ui.unit = u;
						_units.insertLast(ui);
					}
					point.y += ui.y;
					ui.y += 20;

					pk::draw_text(pk::encode(str), point, color);
					if (true)
					{
						pk::size size0 = pk::get_size(FONT_SMALL, pk::encode(str));
						pk::rectangle r0(point, size0);
						pk::draw_filled_rect(r0, 0x40000000);
					}
				}

			}//����

		}

		//�ο�ȿ��///////////////////////////////////////////////////////
		bool checkGroup(pk::unit@ u, int id)
		{
			return getGroup(u, id) != null;
		}
		bool checkGroup(pk::person@ p, int id)
		{
			return getGroup(p, id) != null;
		}

		GroupInfo@ getGroup(pk::unit@ u, int id)
		{
			pk::person@ p0 = u.member[0] >= 0 and u.member[0] < ����_�� ? pk::get_person(u.member[0]) : null;
			GroupInfo@ gi = getGroup(p0, id);
			if (gi != null)
				return gi;
			pk::person@ p1 = u.member[1] >= 0 and u.member[1] < ����_�� ? pk::get_person(u.member[1]) : null;
			GroupInfo@ gi1 = getGroup(p1, id);
			if (gi1 != null)
				return gi1;
			pk::person@ p2 = u.member[2] >= 0 and u.member[2] < ����_�� ? pk::get_person(u.member[2]) : null;
			GroupInfo@ gi2 = getGroup(p2, id);
			return gi2;
		}
		GroupInfo@ getGroup(pk::person@ p, int id)
		{
			if (p == null)
				return null;
			pk::force@ force = pk::get_force(p.get_force_id());
			array<GroupInfo@> arr = getForces(force, { id });
			if (arr.length == 0)
				return null;

			for (int i = 0; i < arr.length; i++)
			{
				GroupInfo@ gi = arr[i];
				for (int k = 0; k < gi.members.count; k++)
				{
					pk::person@ pp = gi.members[k];
					if (pp.get_id() == p.get_id())
						return gi;
				}

			}
			return null;
		}
		array<GroupInfo@> getForces(pk::force@ force, array<int> ids)
		{
			array<GroupInfo@> gis;
			if (force == null)
				return gis;

			for (int i = 0; i < �ο�����Ʈ.length; i++)
			{
				GroupInfo@ gi = �ο�����Ʈ[i];
				if (gi.force != null && gi.force.get_id() == force.get_id())
				{
					bool bFound = false;
					for (int k = 0; k < ids.length; k++)
					{
						int id = ids[k];
						for (int j = 0; j < gi.ids.length; j++)
						{
							if (id == gi.ids[j])
							{
								bFound = true;
								break;
							}
						}
						if (bFound)
							break;
					}
					if (bFound)
						gis.insertLast(gi);
				}
			}
			return gis;
		}

		bool checkGroupType(pk::unit@ u, int id)
		{
			if (u == null)
				return false;
			return checkGroupType(pk::get_person(u.member[0]),id) || checkGroupType(pk::get_person(u.member[1]),id) || checkGroupType(pk::get_person(u.member[2]),id);
		}

		bool checkGroupType(pk::person@ p, int id)
		{
			if (p == null)
				return false;
			GroupInfo@ gi = �ο�����Ʈ[id];
			if (!gi.b)
				return false;
			if (gi.members.count == 0)
				return false;

			for (int j = 0; j < gi.members.count; j++)
			{
				pk::person@ pp = gi.members[j];
				if (pp.get_id() == p.get_id())
					return true;
			}
			return false;
		}


		void load�ο�ȿ��()
		{
			for (int i = 0; i < �ο�����Ʈ.length; i++)
			{
				GroupInfo@ gi = �ο�����Ʈ[i];
				gi.idsApply = {};
				gi.membersApply.clear();
				@gi.force = null;
				gi.b = false;
			}

			int count = int(pk::load(KEY_�ο�ȿ��, 0, 0));
			if (count == 0)
				return;

			int li = 1;
			for (int i = 0; i < count; i++)
			{
				GroupInfo@ gi = �ο�����Ʈ[i];
				int bi = int(pk::load(KEY_�ο�ȿ��, li++, 0));
				gi.b = bi == 1;
				@gi.force = pk::get_force(int(pk::load(KEY_�ο�ȿ��, li++, 0)));
				int count2 = int(pk::load(KEY_�ο�ȿ��, li++, 0));
				for (int k = 0; k < count2; k++)
				{
					gi.idsApply.insertLast(int(pk::load(KEY_�ο�ȿ��, li++, 0)));
				}
				int count3 = int(pk::load(KEY_�ο�ȿ��, li++, 0));
				for (int k = 0; k < count3; k++)
				{
					pk::person@ p = pk::get_person(int(pk::load(KEY_�ο�ȿ��, li++, 0)));
					if (p == null)
						continue;
					gi.membersApply.add(p);
				}
			}


		}

		void UpdatePerFrame�̸�_�ο�ȿ��()
		{
			array<pk::unit@> units;
			for (int i = 0; i < �ο�����Ʈ.length; i++)
			{
				GroupInfo@ gi = �ο�����Ʈ[i];
				if(!gi.b)
					continue;
				if(gi.members.count == 0)
					continue;

				for (int j = 0; j < gi.members.count; j++)
				{
					pk::person@ p = gi.members[j];
					if(!pk::is_in_screen(p.get_pos()))
						continue;

					pk::unit@ u = getUnit(p.get_pos());
					if(u==null)
						continue;
					if (units.findByRef(u) == -1)
						units.insertLast(u);
				}
			}

			for (int i = 0; i < units.length; i++)
			{
				pk::unit@ u = units[i];
				string str = "";
				for (int j = 0; j < �ο�����Ʈ.length; j++)
				{
					if (checkGroupType(u, j)) 
					{
						if(str=="")
							str = str + �ο�����Ʈ[j].name;
						else
							str = str + " "+�ο�����Ʈ[j].name;
					}
				}
				if(str == "")
					continue;

				pk::point point = pk::hex_pos_to_screen_pos(u.get_pos());

				UnitInfo@ ui = getUnit(u);
				if (ui == null)
				{
					@ui = UnitInfo();
					ui.y = 0;
					@ui.unit = u;
					_units.insertLast(ui);
				}
				point.y += ui.y;
				ui.y += 20;

				pk::draw_text(pk::encode(str), point, �ο�ȿ��_ǥ���÷�);
				if (true)
				{
					pk::size size0 = pk::get_size(FONT_SMALL, pk::encode(str));
					pk::rectangle r0(point, size0);
					pk::draw_filled_rect(r0, 0x40000000);
				}
			}
		}


		string UpdateFrameȮ��_�ο�ȿ��(pk::unit@ unit)
		{
			array<array<int>> arr = { array<int>(),array<int>() ,array<int>() };

			if (unit.member[0] >= 0 and unit.member[0] < ����_��)
			{
				pk::person@ p0 = pk::get_person(unit.member[0]);
				array<int> arr0;
				for (int i = 0; i < ȿ��_��; i++)
				{
					if (checkGroup(p0, i))
						arr0.insertLast(i);
				}
				arr[0] = arr0;
			}
			if (unit.member[1] >= 0 and unit.member[1] < ����_��)
			{
				pk::person@ p0 = pk::get_person(unit.member[1]);
				array<int> arr0;
				for (int i = 0; i < ȿ��_��; i++)
				{
					if (checkGroup(p0, i))
						arr0.insertLast(i);
				}
				arr[1] = arr0;
			}
			if (unit.member[2] >= 0 and unit.member[2] < ����_��)
			{
				pk::person@ p0 = pk::get_person(unit.member[2]);
				array<int> arr0;
				for (int i = 0; i < ȿ��_��; i++)
				{
					if (checkGroup(p0, i))
						arr0.insertLast(i);
				}
				arr[2] = arr0;
			}

			string str = "";
			for (int i = 0; i < arr.length; i++)
			{
				if(arr[i].length == 0)
					continue;
				pk::person@ p = pk::get_person(unit.member[i]);
				str = str + pk::format("\x1b[1x{}\x1b[0x", pk::decode(pk::get_name(pk::get_person(unit.member[i])))) + ":";
				string str2 = "";
				for (int j = 0; j < arr[i].length; j++)
				{
					string strType;
					switch (arr[i][j])
					{
					case ȿ��_���ɻ��_��: strType = "����(��)"; break; case ȿ��_���ɻ��_��: strType = "����(��)"; break; case ȿ��_���ɻ��_��: strType = "����(��)"; break;
					case ȿ��_���ݻ��_��: strType = "���ݷ�(��)"; break; case ȿ��_���ݻ��_��: strType = "���ݷ�(��)"; break; case ȿ��_���ݻ��_��: strType = "���ݷ�(��)"; break;
					case ȿ��_�����_��: strType = "����(��)"; break; case ȿ��_�����_��: strType = "����(��)"; break; case ȿ��_�����_��: strType = "����(��)"; break;
					case ȿ��_����_��: strType = "����(��)"; break; case ȿ��_����_��: strType = "����(��)"; break; case ȿ��_����_��: strType = "����(��)"; break;
					case ȿ��_�־�_��: strType = "�־�(��)"; break; case ȿ��_�־�_��: strType = "�־�(��)"; break; case ȿ��_�־�_��: strType = "�־�(��)"; break;
					case ȿ��_����_����_��: strType = "��������(��)"; break; case ȿ��_����_����_��: strType = "��������(��)"; break; case ȿ��_����_����_��: strType = "��������(��)"; break;
					case ȿ��_����_���_��: strType = "�������(��)"; break; case ȿ��_����_���_��: strType = "�������(��)"; break; case ȿ��_����_���_��: strType = "�������(��)"; break;
					case ȿ��_�跫_��: strType = "�跫(��)"; break; case ȿ��_�跫_��: strType = "�跫(��)"; break; case ȿ��_�跫_��: strType = "�跫(��)"; break;
					case ȿ��_�跫���_��: strType = "�跫���(��)"; break; case ȿ��_�跫���_��: strType = "�跫���(��)"; break; case ȿ��_�跫���_��: strType = "�跫���(��)"; break;
					case ȿ��_������°���: strType = "������°���"; break;	case ȿ��_�������簨��: strType = "�������簨��"; break;
					case ȿ��_���������: strType = "������"; break;	case ȿ��_�����ݵ�ü���: strType = "�����׻󼺰�"; break;
					case ȿ��_���: strType = "���"; break; case ȿ��_����: strType = "����"; break; case ȿ��_�汹: strType = "�汹"; break; case ȿ��_��������ȿ��: strType = "��������"; break;
					case ȿ��_�������_��: strType = "����(��)"; break; case ȿ��_�������_��: strType = "����(��)"; break; case ȿ��_�������_��: strType = "����(��)"; break;
					case ȿ��_��ȣ_��: strType = "��ȣ(��)"; break; case ȿ��_��ȣ_��: strType = "��ȣ(��)"; break; case ȿ��_��ȣ_��: strType = "��ȣ(��)"; break;
					case ȿ��_�̵�_��: strType = "�̵�(��)"; break; case ȿ��_�̵�_��: strType = "�̵�(��)"; break; case ȿ��_�̵�_��: strType = "�̵�(��)"; break;
					case ȿ��_��_��: strType = "��(��)"; break; case ȿ��_��_��: strType = "��(��)"; break; case ȿ��_��_��: strType = "��(��)"; break;
					case ȿ��_�跫_���_����: strType = "�跫��°���"; break; case ȿ��_�跫_ũ��Ƽ��_�׻󼺰�: strType = "�跫�׻�ũ��"; break; case ȿ��_����_ũ��Ƽ��_�׻󼺰�: strType = "�����׻�ũ��"; break;
					case ȿ��_����_�Ұ�: strType = "���ںҰ�"; break; case ȿ��_�⺴_����_���_�Ұ�: strType = "��������Ұ�"; break; case ȿ��_�Һ���_ȥ��_�Ұ�: strType = "�Һ���ȥ���Ұ�"; break;
					case ȿ��_����_����: strType = "��������"; break; case ȿ��_����_����: strType = "��������"; break; case ȿ��_����_ȭ��: strType = "����ȭ��"; break;
					case ȿ��_���_���_��: strType = "���(��)"; break; case ȿ��_���_���_��: strType = "���(��)"; break; case ȿ��_���_���_��: strType = "���(��)"; break;
					case ȿ��_����_���_��: strType = "����(��)"; break; case ȿ��_����_���_��: strType = "����(��)"; break; case ȿ��_����_���_��: strType = "����(��)"; break;
					case ȿ��_����_���_��: strType = "����(��)"; break; case ȿ��_����_���_��: strType = "����(��)"; break; case ȿ��_����_���_��: strType = "����(��)"; break;
					case ȿ��_��ġ_���_��: strType = "��ġ(��)"; break; case ȿ��_��ġ_���_��: strType = "��ġ(��)"; break; case ȿ��_��ġ_���_��: strType = "��ġ(��)"; break;
					case ȿ��_�ŷ�_���_��: strType = "�ŷ�(��)"; break; case ȿ��_�ŷ�_���_��: strType = "�ŷ�(��)"; break; case ȿ��_�ŷ�_���_��: strType = "�ŷ�(��)"; break;

					default:
						break;
					}
					if (str2 == "")
						str2 = strType;
					else
						str2 = str2 + " " + strType;

				}
				str = str + str2;
			}
			

			return str;
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


		///////////////////////////////////////////////
	}
	Main main;
}

