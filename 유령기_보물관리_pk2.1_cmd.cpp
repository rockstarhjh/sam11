/*
@������: ���ɱ�
@����: ���� ���� 2017/12/09

@������: �⸶å��
@����: PK2.1������ ��ȯ '18.12.22

@������: Gistar
@����: ������ ���� ��Ŀ��� cmd�� ����ϵ��� ����
*/

/* 
	������ ������ ������� �ʾ����Ƿ� ���� ������ �������� ����....
*/

bool ���ɱ�_����_����_���뿩�� = true; // ���������� �������� ����
bool ���ɱ�_����_����_�������� = true; // ���� ������ ���� ���� ���ý� �����ϰ� �������� ����, false�� �������� ��ġ�� ���� ���� �������� ������.
bool ���ɱ�_����_����_�������� = true; // ��������� ���� ���� �ְ� ���������� ���³� Ÿ ������ ������ ������, �����ؼ� ����������� �ٰ����� ����
bool ���ɱ�_�����_����_��뿩�� = false; // ���� üũ�� ����ڰ� ���� ������ ����� ������ ����
bool ���ɱ�_�α�_����_ǥ�� = false; // core.log�� ���� �й� �α׸� ǥ���մϴ�.
bool ���ɱ�_�α�_ȭ��_ǥ�� = true; // ȭ�� ���� â�� ���� �й� �α׸� ǥ���մϴ�.
bool ���ɱ�_�α�_�޼���ǥ�� = false; // ȭ�� �޼��� â�� ���� �й� �α׸� ǥ���մϴ�.

int ���ɱ�_����_â��_�ּ� = 80;
int ���ɱ�_����_��_����_�ּ� = 50;
int ���ɱ�_����_��_�빫_�ּ� = 80;
int ���ɱ�_����_Ȱ_�ּ� = 70;
int ���ɱ�_����_�ϱ�_�ּ� = 70;
int ���ɱ�_����_��å_�ּ� = 70;
int ���ɱ�_����_��_����_�ּ� = 0;
int ���ɱ�_����_��_�빫����_�ּ� = 0;

int ���ɱ�_����_â��_�ּ� = 80;
int ���ɱ�_����_��_����_�ּ� = 80;
int ���ɱ�_����_��_�빫_�ּ� = 150;
int ���ɱ�_����_�ϱ�_�ּ� = 70;
int ���ɱ�_����_Ȱ_�ּ� = 70;
int ���ɱ�_����_��å_�ּ� = 75;
int ���ɱ�_����_��_����_�ּ� = 85;
int ���ɱ�_����_��_�빫����_�ּ� = 300;

int ���ɱ�_â��_����_��� = 1;
int ���ɱ�_��_����_����_��� = 2;
int ���ɱ�_��_�빫_����_��� = 4;
int ���ɱ�_�ϱ�_����_��� = 3;
int ���ɱ�_Ȱ_����_��� = 2;
int ���ɱ�_��å_����_��� = 3;
int ���ɱ�_��_����_����_��� = 1;
int ���ɱ�_��_�빫����_����_��� = 5;
int ���ɱ�_����S_������ = 6;

int �ɷ°������_�ִ� = 100;
int ���ְ���_������ = 12;

int ������_���� = 160;

int ���ɱ�_��_�ּҼ�ġ = -100000000;


/*
	����� ���� ����
	
	1. �������ǿ��� - 0 �ϰ�� ��������, 1�ϰ�� �Ϲ�����
	2. �������� - �������� ��ȣ. (pk_enums.h ��������Id ����), ���������� �������� �������� -1�� �Է�.
	3. ������ȣ - ���� ��ȣ.  (pk_enums.h ����Id ����), ������ȣ�� �������� �������� -1�� �Է�.
	4. �ɷ��ִ�ġ
	5. ����ּұ��� 
	6. ��ְ���ġ - ��ġ ���� ��ְ���ġ
	7. �����ּұ��� 
	8. ���°���ġ - ��ġ ���� ���°���ġ
	9. �����ּұ���
	10. ���°���ġ - ��ġ ���� ���°���ġ
	11. ��ġ�ּұ���
	12. ��ġ����ġ - ��ġ ���� ��ġ����ġ
	13. �ŷ��ּұ���
	14. �ŷ°���ġ - ��ġ ���� �ŷ°���ġ
	15. �����ִ�ġ
	16. â�������ּұ��� - (pk_enums.h ����Id ����)
	17. â����������ġ
	18. �غ������ּұ��� - (pk_enums.h ����Id ����)
	19. �غ���������ġ
	20. �뺴�����ּұ��� - (pk_enums.h ����Id ����)
	21. �뺴��������ġ
	22. �⺴�����ּұ��� - (pk_enums.h ����Id ����)
	23. �⺴��������ġ
	24. ���������ּұ��� - (pk_enums.h ����Id ����)
	25. ������������ġ
	26. ���������ּұ��� - (pk_enums.h ����Id ����)
	27. ������������ġ
	28. �漺�ִ�ġ
	29. �漺�ּұ���
	30. �漺������ġ
	31. �����ִ�ġ
	32. �����ּұ���
	33. ��������ġ
	34. �θ��ڽİ���ġ
	35. ����ڰ���ġ
	36. ��������ġ
	37. ����������ġ
	38. ����ģ�ְ���ġ
	39. ����������

	
	���庰 ��ġ�񱳰� ������ =
		(�ɷ�*�ɷ°���ġ)�� �� + (����*��������ġ)�� �� + �漺*�漺����ġ + ����*��������ġ + �θ��ڽİ���ġ + ����ڰ���ġ + ��������ġ + ����������ġ + ����ģ�ְ���ġ + ����(����������)

	�켱�� ���� �� �ɷµ��� �ɷ��ִ�ġ�� ������ �ɷ��ִ�ġ�� ����մϴ� �ٸ� ��ġ���� �ִ�ġ�鵵 ��������.
	�� �ּ�ġ�� ������Ű�� ������� ��ġ������� ���� ���� ������ ������� ������ �ش�. ������ ��� �ּ�ġ�� ������Ű�� ��. ���� ���������� �� ���ǵ�� ��� ����.
	
	ù��°�� ��ǻ�ʹ� ���� ������ȣ�� ���ؼ� ������ �˻��ϰ� ������ȣ�� ��ġ�ϴ� ������ ���� ��� ���ǰ����� ������ ����ڵ��� ��ġ�� ����ؼ� ������ �����Ѵ�.
	�ι�°�� ��ǻ�ʹ� ������������ �´� ������ �ִ��� �˻��ؼ� ��ġ�ϴ� ������ ������� ���ǰ����� ������ ����ڵ��� ��ġ�� ����ؼ� ������ �����Ѵ�.
	����°�� ����� ������ ���� ��� �⺻�������� ����ؼ� �����Ѵ�.
	
	���Ǵ� ��ġ�� ���Ҷ� �� ó���� �ְ��ġ�� ���� ������ ���� ��� ���ɱ�_��_�ּҼ�ġ�� ���ϹǷ� ���ɱ�_��_�ּҼ�ġ���� ���� ���� ���´ٸ� ������ �й������ ����.

*/

array<array<int>> �����_����_���� =
{
	// ������ġ�� �ٹٲ��� �˾ƺ��� ���� 10������ �������ϴ�.
		
	// ���� 1. �ϱ⸦ ��� 80, ���� 90 �̻��� ������� �������, ���°���ġ -1��, ���� 300�� �༭ ��� ������ ������ ������ ���� ���������� ����� ���ַ� �ְ� �غ���....
	{ 1, ��������_�ϱ�, -1, 100, 80, 0, 0, -1, 90, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 300},
		
	// ���� 2. ���ں������� �ּ����Ǿ��� ������ ģ������� ����ġ�� 30�� �ְ� ���� 200���� �ຸ��.
	{ 1, -1, ����_���ں���, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 30, 200},	

	// ���� 3. ������ Ȱ �ּ������� �뺴 ���� B�� ������.
	{ 0, ��������_Ȱ, -1, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, ����_B, 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 0},
		
	// ���� 4. ��å�� ��ַ� 70 �̻��� ���忡 ��� ����ġ 1�� ���� 300�� �༭ ��ַ� ���� ���� ���ַ� �ް� �غ���....
	{ 1, ��������_��å, -1, 100, 70, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 300},
		
	// ���� 5. �乫����� ���� 85 �̻��� ���忡 ���� ����ġ -1�� ���� 300�� �༭ ������ ������ ���밡���� �ѵ� ���ַ� �ް� �غ���....
	{ 1, ��������_�乫��, -1, 100, 0, 0, 85, 0, 0, -1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 300}
};

/*
	�� ������ �������� ���. ���Ͽ� �ش� ������ ������� �����ϸ� �����ؼ��� ����������� �й����ش�. �� ������ ��������� ��쿣 ���ش�.
*/
array<array<int>> ���ɱ�_����_���� =
{
	
	{ ����_���丶, ����_����, ����_���� },
	{ ����_����, ����_���� },
	{ ����_��Ȳ����, ����_���� },
	{ ����_����, ����_���� },
	{ ����_��ϸ�1, ����_�ս� },
	{ ����_��ϸ�2 },
	{ ����_��ϸ�3 },
	{ ����_ĥ������ },
	{ ����_��õ��, ����_���� },
	{ ����_û����, ����_���� },
	{ ����_�ڿ��ϴ��, ����_���� },
	{ ����_��õȭ��, ����_���� },
	{ ����_û������, ����_���� },
	{ ����_���, ����_��� },
	{ ����_������, ����_�ս� },
	{ ����_��1 },
	{ ����_��2, ����_���� },
	{ ����_�ܱ�1, ����_���� },
	{ ����_�ܱ�2 },
	{ ����_����1, ����_�»��� },
	{ ����_����2, ����_��å },
	{ ����_ö��, ����_���� },
	{ ����_��������Ȱ },
	{ ����_�̱���Ȱ },
	{ ����_�ܱ�1 },
	{ ����_�ܱ�2 },
	{ ����_��ȣ���1 },
	{ ����_��ȣ���2 },
	{ ����_�Ʊ�1 },
	{ ����_�Ʊ�2 },
	{ ����_���ں���, ����_�հ�, ����_��å, ����_�ձ�, ����_�ջ��� },
	{ ����_����24��, ����_������ },
	{ ����_�ʹ��ż�, ����_���� },
	{ ����_����, ����_����_�°��� },
	{ ����_�﷫, ����_����_�°��� },
	{ ����_����, ����_���� },
	{ ����_������ },
	{ ����_����å },
	{ ����_�縶�� },
	{ ����_���� },
	{ ����_��������, ����_�尢 }
};

/*
	�� ������ ������������ ���. Ư���� �ش� ����鿡�� ������ ���� ������, �̹� ������ ������ �ִٸ� ���������� �ڴʰ� ���͵� ���������� �ʴ´�.
*/
array<array<int>> ���ɱ�_����_����_���� =
{
	
	{ ����_���丶, ����_������, ����_���� },
	{ ����_����, ����_���� },
	{ ����_��Ȳ����, ����_���� },
	{ ����_����, ����_���� },
	{ ����_ĥ������, ����_���� },
	{ ����_��õ��, ����_���� },
	{ ����_û����, ����_������, ����_���� },
	{ ����_�ڿ��ϴ��, ����_���� },
	{ ����_��õȭ��, ����_����, ����_������ },
	{ ����_û������, ����_���� },
	{ ����_���, ����_���� },
	{ ����_�ʹ��ż�, ����_����, ����_���� },
	{ ����_��������, ����_�庸 }
};


���ɱ�_�������� item_manage;	// ���� �������

class ���ɱ�_��������
{
	
	���ɱ�_��������()
	{
		if( !���ɱ�_����_����_���뿩�� )
		{
			���ɱ�_����_����.resize(0);
			���ɱ�_����_����_����.resize(0);
		}
	
		pk::bind(108, pk::trigger108_t(onNewday));
		pk::bind(111, pk::trigger111_t(onTurnEnd));
		pk::bind(111, pk::trigger111_t(onTurnstart));
		pk::bind(112, pk::trigger112_t(onTurnEnd));

	}

	void onNewday()
	{
		if (pk::get_month() % 2 == 1)
			���ɱ�_�׿���������();
	}
	
	void onTurnstart(pk::force@ force)
	{
		if (pk::is_campaign()) return;
		if (!pk::is_alive(force)) return;
		if (!pk::is_normal_force(force)) return;
		if (force.is_player()) return;

		int kunshu_id = force.kunshu;
		int force_id = force.get_id();

		//���ְ� ������ ���� ���� �迭 ����
		array<int> kunshu_item_id = ���ɱ�_���ֺ�������(kunshu_id);

/*		
		for (int i = ��������_��; i < ��������_��å; i++)
		{
			kunshu_item_id[i] = ���ɱ�_���ֺ�������(kunshu_id);
		}
*/

		for (int i = 0; i < ����_��; i++)
		{
			pk::item@ item = pk::get_item(i);
			pk::person@ kunshu = pk::get_person(force.kunshu);

			if (!pk::is_alive(item)) continue;

			int select = -1;

			//���� ���� ������ ������ �н�
			if (!��������Ȯ��(force_id, item))
				continue;

			pk::person@ person = pk::get_person(item.owner);
			pk::building@ build = pk::get_building(person.service);

			//�� ���� �����ڰ� �δ뿡 ���� ���� ��� �н�
			if (person.location > 86)
				continue;

			//������ �����ڰ� �ش� ������ �����ϱ� ������ ��� �н�(������ ��� �ش� ������ ��������, ���������������� �� ���ǿ� ����)
			if (���ɱ�_����_����������(person, item))
				continue;

			// ������ ���� �ɷ� ��Ǿ� �ִ°Ÿ� �Ѿ.
			bool kunshu_flag = false;
			for( uint j=0; j<kunshu_item_id.length; j++)
			{
				if(kunshu_item_id[j] == item.get_id())
					kunshu_flag = true;
			}
		
			if( kunshu_flag ) continue;

			select = ���ɱ�_�����й�( kunshu_id, item );		//���� �˰����� ������ ����

			if (select == -1) 					//������ �����ڰ� ���� ��� �н�
			{	
				string s = "���� <"+pk::decode(item.name)+">, <"+pk::decode(pk::get_name(kunshu))+"> ���¿��� ����� ����.";

            			if( ���ɱ�_�α�_����_ǥ��) pk::info(s);
            			if( ���ɱ�_�α�_ȭ��_ǥ��) pk::history_log(pk::get_building(pk::get_person(item.owner).service).pos, -1, pk::encode(s));
            
            			if( ���ɱ�_�α�_�޼���ǥ��) pk::message_box(pk::encode(s));
				continue;
			}

			if (person.get_id() == select)			//������ �����ڰ� ���� �����ڿ� ���� ��� �н�
			{
				continue;
			}

			pk::person@ person2 = pk::get_person(select);
			pk::award_cmd_info cmd;		//�������� ��� ����
			@cmd.item = item;
			@cmd.base = build;
			@cmd.target = person2;
			int loy1 = 0;
			int loy2 = 0;

			if (person.mibun != �ź�_����)
				loy1 = person.loyalty;
			if (person2.mibun != �ź�_����)
				loy2 = person2.loyalty;

			pk::command(cmd);		//������ ����

			if (person.mibun != �ź�_����)
				person.loyalty = loy1;
			if (person2.mibun != �ź�_����)
				person2.loyalty = loy2;

			string s = "���� <"+pk::decode(pk::get_name(pk::get_person(select)))+">, <"+pk::decode(pk::get_name(person))+">���Լ� ���� <"+pk::decode(item.name)+"> ����";
                
                		if( ���ɱ�_�α�_����_ǥ��) pk::info(s);
                		if( ���ɱ�_�α�_ȭ��_ǥ��) pk::history_log(pk::get_building(pk::get_person(item.owner).service).pos, -1, pk::encode(s));
                
               	 	if( ���ɱ�_�α�_�޼���ǥ��) pk::message_box(pk::encode(s));
		}
	}

	void onTurnEnd(pk::force@ force)
	{
		if (pk::is_campaign()) return;
		if (!pk::is_alive(force)) return;
		if (!pk::is_normal_force(force)) return;
		if (force.is_player()) return;

		int kunshu_id = force.kunshu;
		pk::item@ item;
            	
		if( pk::is_alive(force) and pk::is_normal_force(force) and pk::is_alive(pk::get_person(force.kunshu)) and ( kunshu_id == 660 or kunshu_id == 98 or kunshu_id == 432 or kunshu_id == 289 or kunshu_id == 403 or kunshu_id == 370 ) )
            	{
			int item_user = AI_repair_item_user( kunshu_id );
			if (kunshu_id == 660)
			{
				int bang = 11;
				@item = pk::get_item(bang);
			}
			else if (kunshu_id == 98)
			{
				int chung = 12;
				@item = pk::get_item(chung);
			}
			else if (kunshu_id == 432)
			{
				int samo = 13;
				@item = pk::get_item(samo);
			}
			else if (kunshu_id == 289)
			{
				int bub = 31;
				@item = pk::get_item(bub);
			}
			else if (kunshu_id == 403)
			{
				int tae = 40;
				@item = pk::get_item(tae);
			}
			else if (kunshu_id == 370)
			{
				int suu = 20;
				@item = pk::get_item(suu);
			}

			if (item_user != -1)
			{
				pk::person@ person = pk::get_person(item.owner);
				pk::person@ person2 = pk::get_person(kunshu_id);
				pk::building@ build = pk::get_building(person.service);

				pk::award_cmd_info cmd;
				@cmd.item = item;
				@cmd.base = build;
				@cmd.target = person2;
				int loy1 = 0;
				int loy2 = 0;

				if (person.mibun != �ź�_����)
					loy1 = person.loyalty;
				if (person2.mibun != �ź�_����)
					loy2 = person2.loyalty;

				pk::command(cmd);

				if (person.mibun != �ź�_����)
					person.loyalty = loy1;
				if (person2.mibun != �ź�_����)
					person2.loyalty = loy2;
			}
       		}
	}
}

bool ��������Ȯ��(int force_id, pk::item@ item)
{
	//�ı� �����̳� �̵��� ������ �̺����� ����
	if (item.status == ��������_�ı� or item.status == ��������_�̵���)
		return false;

	pk::person@ person = pk::get_person(item.owner);

	if (person.get_force_id() != force_id)
		return false;
	else
		return true;

	return false;
}

int AI_repair_item_user( int kunshu_id )
{
	pk::person@ kunshu = pk::get_person(kunshu_id);

	//��õȭ��, ����24��, û������, ���Ȼ���� ���� ������ ����(���׼���)
	if (kunshu_id == 660)
	{
		int bang = 11;
		pk::item@ item = pk::get_item(bang);

		if (item.owner != kunshu_id and (pk::get_person(item.owner).get_force_id() == kunshu.get_force_id()) and item.status == ��������_����)
			return kunshu_id;
	}

	if (kunshu_id == 98)
	{
		int chung = 12;
		pk::item@ item = pk::get_item(chung);

		if (item.owner != kunshu_id and (pk::get_person(item.owner).get_force_id() == kunshu.get_force_id()) and item.status == ��������_����)
			return kunshu_id;
	}

	if (kunshu_id == 432)
	{
		int samo = 13;
		pk::item@ item = pk::get_item(samo);

		if (item.owner != kunshu_id and (pk::get_person(item.owner).get_force_id() == kunshu.get_force_id()) and item.status == ��������_����)
			return kunshu_id;
	}

	if (kunshu_id == 289)
	{
		int bub = 31;
		pk::item@ item = pk::get_item(bub);

		if (item.owner != kunshu_id and (pk::get_person(item.owner).get_force_id() == kunshu.get_force_id()) and item.status == ��������_����)
			return kunshu_id;
	}

	if (kunshu_id == 403)
	{
		int tae = 40;
		pk::item@ item = pk::get_item(tae);

		if (item.owner != kunshu_id and (pk::get_person(item.owner).get_force_id() == kunshu.get_force_id()) and item.status == ��������_����)
			return kunshu_id;
	}

	if (kunshu_id == 370)
	{
		int suu = 20;
		pk::item@ item = pk::get_item(suu);

		if (item.owner != kunshu_id and (pk::get_person(item.owner).get_force_id() == kunshu.get_force_id()) and item.status == ��������_����)
			return kunshu_id;
	}

	return -1;
}



/*
	������ ���� �����ϱ�
*/

array<int> ���ɱ�_���ֺ�������(int kunshu_id)
{
	pk::person@ kunshu = pk::get_person(kunshu_id);

	array<int> kunshu_item_id = { -1, -1, -1, -1, -1, -1 };
	array<int> kunshu_item_value = { -1, -1, -1, -1, -1, -1 };

	for( int i=0 ; i < ����_�� ; i++ )
	{
		pk::item@ item = pk::get_item(i);
		
		// ���������� ���� �̻��̸� �Ѿ
		if( item.type >= ��������_���� )
			continue;
		
		if( !pk::is_alive(item) or item.status != ��������_���� or !pk::is_alive(pk::get_person(item.owner)) )
			continue;
		
		//  ������ ������ ���� �ƴ϶�� �Ѿ.
		if( item.owner != kunshu_id )
			continue;
		
		// ������ ������ ������ ���.
		
		// ������ �ڼ��� �� ������ ���������� ��쿡�� ������ ���߿� ����������� �� �����̹Ƿ� �Ѿ��.
		if( ���ɱ�_��������_����üũ( item.get_id(), kunshu.get_force_id() ) != -1 )
			continue;
		
		// ���� ������ �� ������ ��������(or ����)��� ���߿� ó���ϰ� �� �״� �Ѿ��.
		if (���ɱ�_��������_üũ(item.get_id(), kunshu_id))
			continue;
		else if (���ɱ�_������������_üũ(item.get_id(), kunshu_id))
			continue;
		
		int item_value = ���ɱ�_����_����_�������� ? pk::rand(50) : item.value;

		// 1. ���������� ���� ������ ����� ������ üũ
		if( ���ɱ�_�����_����_��뿩�� and ���ɱ�_�����_����_üũ( item, 0, true ) >= 0 )
		{
			int cond_index = ���ɱ�_�����_����_üũ( item, 0, true );
			
			//MessageBox().talk(" �������� üũ " + kunshu.name + " " + item.name + " �������� ���� index =" + ���ɱ�_�����_����_üũ( item, 0, true ));
			
			// ���ְ� ����������� �����ϰ�, ���� ��ġ�� �� ���ٸ�....
			if( ���ɱ�_�����_����_����_üũ( kunshu, cond_index ) and item_value > kunshu_item_value[item.type] )
			{
				kunshu_item_id[item.type] = item.get_id(); kunshu_item_value[item.type] = item_value;
			}
			continue;	// �켱������ ���� ���ǵ��� �Ѿ��.
		}
		
		// 2. ���������� ���� ������ ����� ������ üũ
		if( ���ɱ�_�����_����_��뿩�� and ���ɱ�_�����_����_üũ( item, 1, true ) >= 0 )
		{
			int cond_index = ���ɱ�_�����_����_üũ( item, 1, true );
			
			//MessageBox().talk(" �������� üũ " + kunshu.name + " " + item.name + " �������� ���� index =" + ���ɱ�_�����_����_üũ( item, 1, true ));
			
			// ���ְ� ����������� �����ϰ�, ���� ��ġ�� �� ���ٸ�....
			if( ���ɱ�_�����_����_����_üũ( kunshu, cond_index ) and item_value > kunshu_item_value[item.type] )
			{
				kunshu_item_id[item.type] = item.get_id(); kunshu_item_value[item.type] = item_value;
			}
			
			continue;	// �켱������ ���� ���ǵ��� �Ѿ��.
		}

		// 3. �⺻������ üũ
		if( item.type == ��������_�乫�� and item_value > kunshu_item_value[��������_�乫��] and ���ɱ�_����_â��_����( kunshu, ���ɱ�_����_â��_�ּ�, ����_A ) )
		{
			kunshu_item_id[��������_�乫��] = item.get_id(); kunshu_item_value[��������_�乫��] = item_value;
		}
	
		// �˷�
		if( item.type == ��������_�� and item_value > kunshu_item_value[��������_��] and ���ɱ�_����_��_����( kunshu, ���ɱ�_����_��_����_�ּ�, ���ɱ�_����_��_�빫_�ּ� ) )
		{
			kunshu_item_id[��������_��] = item.get_id(); kunshu_item_value[��������_��] = item_value;
		}
		
		// �ϱ��
		if( item.type == ��������_�ϱ� and item_value > kunshu_item_value[��������_�ϱ�] and int(kunshu.stat[����ɷ�_����]) >= ���ɱ�_����_�ϱ�_�ּ� )
		{
			kunshu_item_id[��������_�ϱ�] = item.get_id(); kunshu_item_value[��������_�ϱ�] = item_value;
		}
		
		// Ȱ�� ( ���� ������ ���� ���ɱ�_����_Ȱ_�ּ� �̻� �뺴���� A �̻� or �ú� �迭 Ư���� ��� )
		if( item.type == ��������_Ȱ and item_value > kunshu_item_value[��������_Ȱ] and ���ɱ�_����_Ȱ_����( kunshu, ���ɱ�_����_Ȱ_�ּ�, ����_A ) )
		{
			kunshu_item_id[��������_Ȱ] = item.get_id(); kunshu_item_value[��������_Ȱ] = item_value;
		}
		
		// ��å�� ( ���� ������ ������ ���ɱ�_����_����_�ּ� �̻��� ��� )
		if( item.type == ��������_��å and item_value > kunshu_item_value[��������_��å] and int(kunshu.stat[����ɷ�_����]) >= ���ɱ�_����_��å_�ּ� )
		{
			kunshu_item_id[��������_��å] = item.get_id(); kunshu_item_value[��������_��å] = item_value;
		}
		
		//����
		if( item.type == ��������_�� and item_value > kunshu_item_value[��������_��] and  ���ɱ�_����_��_����( kunshu, kunshu, ���ɱ�_����_��_����_�ּ�, ���ɱ�_����_��_�빫����_�ּ�) ) 
		{
			kunshu_item_id[��������_��] = item.get_id(); kunshu_item_value[��������_��] = item_value;
		}
	}

	// ������ ���������� �����ϴ� �۾�.
	for( int i=0 ; i < ����_�� ; i++ )
	{
		pk::item@ item = pk::get_item(i);
		
		// ���������� ���� �̻��̸� �Ѿ
		if( item.type >= ��������_���� )
			continue;
		
		if( !pk::is_alive(item) or item.status != ��������_���� or !pk::is_alive(pk::get_person(item.owner)) )
			continue;
		
		// �������� ������ �Ϲ����� ���°� �ƴϸ� �Ѿ.
		if( !( pk::get_person(item.owner).mibun >= �ź�_���� and pk::get_person(item.owner).mibun <= �ź�_�Ϲ� ) )
			continue;
		
		//  ������ ���� ��������� ���� �ƴ϶�� �Ѿ.
		if( !( pk::get_person(item.owner).get_force_id() == kunshu.get_force_id() and item.type < ��������_����) )
			continue;
		
		// ���� ���������� ��� üũ
		if( ���ɱ�_��������_üũ( item.get_id(), kunshu_id ) and item.owner == kunshu_id )
		{
			kunshu_item_id[item.type] = item.get_id();
			kunshu_item_value[item.type] = item.value;
		}

		if( ���ɱ�_������������_üũ( item.get_id(), kunshu_id ) and item.owner == kunshu_id )
		{
			kunshu_item_id[item.type] = item.get_id();
			kunshu_item_value[item.type] = item.value;
		}
	}

	return kunshu_item_id;
}

/*
	���ְ� ������ �й��ϴ� �Լ�
*/

int ���ɱ�_�����й�( int kunshu_id, pk::item@ item )
{
	pk::person@ kunshu = pk::get_person(kunshu_id);
	
	if( ���ɱ�_��������_üũ(item.get_id(), item.owner) )
		return -1;
	else if (���ɱ�_������������_üũ(item.get_id(), item.owner))
		return -1;
		
	// ���³� ���� ������ �����ڰ� �ƴ� ���������� �ִ��� üũ
	int unique_id = ���ɱ�_��������_����üũ( item.get_id(), kunshu.get_force_id() );
	pk::person@ unique_p = pk::get_person(unique_id);
		
	// ���������� ���ų� �Ϲ����� ���°� �ƴϸ� �Ѿ.
	if( unique_id != -1 and pk::is_alive(unique_p) and ( unique_p.mibun >= �ź�_���� and unique_p.mibun <= �ź�_�Ϲ� ) and unique_p.location <= 86)
	{
		if( !pk::is_dislike(kunshu, unique_id) and ���ɱ�_����_����_�������� and item.owner != kunshu_id )
			return unique_id;
		else if ( !pk::is_dislike(kunshu, unique_id) and item.owner == kunshu_id )
			return unique_id;
	}
		
		// ���������� ���� ����� ���� ������ ������ ������ �ִٸ� ���ֿ��� �ݳ�.
		//���ɱ�_����_�ݳ�( unique_id, kunshu_id, item.type );

	
	pk::force@ kunshu_force = pk::get_force(kunshu.get_force_id() ) ;
	pk::array<pk::person@> officers = pk::list_to_array(pk::get_person_list(kunshu_force, pk::mibun_flags(�ź�_����, �ź�_�¼�, �ź�_�Ϲ�)));

	int force_id = kunshu.get_force_id();

/*
	for (int i = 0; i < ����_��; i++)
	{
		pk::person@ person = pk::get_person(i);
		if (pk::is_alive(person))
		{
			if (person.get_force_id() == force_id && person.mibun != �ź�_���� && person.mibun != �ź�_����)
			{
				officers.add(person);
			}
		}
	}
*/

	int best_person_id = -1;
	int best_person_value = ���ɱ�_��_�ּҼ�ġ;
		
	//  ����鿡 ���� ���� üũ.
	for (auto officer = 0; officer < officers.length; officer++)
	{
		if( officers[officer].get_id() == kunshu_id or pk::is_dislike(kunshu, officers[officer].get_id()) ) // ���� �����̰ų� ������ ��������� ��� �Ѿ.
			continue;
				
		// ��� ������ �Ϲ����� ���°� �ƴϸ� �Ѿ.
		if( !( officers[officer].mibun >= �ź�_���� and officers[officer].mibun <= �ź�_�Ϲ� ) )
			continue;
		
		if ( officers[officer].location > 86 )
			continue;

		if( ���ɱ�_��������_üũ(item.get_id(), officers[officer].get_id()) )
			return officers[officer].get_id();

		// 1. ���������� ���� ������ ����� ������ üũ
		if( ���ɱ�_�����_����_��뿩�� and ���ɱ�_�����_����_üũ( item, 0, false ) >= 0 )
		{
			int cond_index = ���ɱ�_�����_����_üũ( item, 0, false );
			int officer_value = ���ɱ�_�����_����_����_��ġ( officers[officer], cond_index );
				
			// ������ ����������� �����ϰ� ������ ��������� ��ġ����� ������� �ٸ� ������� �ְ��ġ���� ���ٸ�....
			if( ���ɱ�_�����_����_����_üũ( officers[officer], cond_index ) and officer_value > best_person_value )
				{ best_person_id = officers[officer].get_id(); best_person_value = officer_value;}
				
			continue;	// �켱������ ���� ���ǵ��� �Ѿ��.
		}
			
		// 2. ���������� ���� ������ ����� ������ üũ
		if( ���ɱ�_�����_����_��뿩�� and ���ɱ�_�����_����_üũ( item, 1, false ) >= 0 )
		{
			int cond_index = ���ɱ�_�����_����_üũ( item, 1, false );
			int officer_value = ���ɱ�_�����_����_����_��ġ( officers[officer], cond_index );
				
			// ������ ����������� �����ϰ� ������ ��������� ��ġ����� ������� �ٸ� ������� �ְ��ġ���� ���ٸ�....
			if( ���ɱ�_�����_����_����_üũ( officers[officer], cond_index ) and officer_value > best_person_value )
				{ best_person_id = officers[officer].get_id(); best_person_value = officer_value;}
				
			continue;	// �켱������ ���� ���ǵ��� �Ѿ��.
		}
			
		// 3. �⺻������ üũ
		if( 
			( item.type == ��������_�乫�� and ���ɱ�_����_â��_����( officers[officer], ���ɱ�_����_â��_�ּ�, ����_A ) ) 
			or ( item.type == ��������_�� and ���ɱ�_����_��_����( officers[officer], ���ɱ�_����_��_����_�ּ�, ���ɱ�_����_��_�빫_�ּ� ) ) 
			or ( item.type == ��������_�ϱ� and int(officers[officer].stat[����ɷ�_����]) >= ���ɱ�_����_�ϱ�_�ּ� )
			or ( item.type == ��������_Ȱ and ���ɱ�_����_Ȱ_����( officers[officer], ���ɱ�_����_Ȱ_�ּ�, ����_A ) )
			or ( item.type == ��������_��å and int(officers[officer].stat[����ɷ�_����]) >= ���ɱ�_����_��å_�ּ� )
			or ( item.type == ��������_�� and ���ɱ�_����_��_����( officers[officer], kunshu, ���ɱ�_����_��_����_�ּ�, ���ɱ�_����_��_�빫����_�ּ�) )
		)
		{
			int officer_value = pk::rand(������_����);
				
			// ������ ����, �������̰ų� ģ������� ��쿡�� ���ְ���_������.
			if( pk::is_ketsuen(kunshu, officers[officer].get_id()) or pk::is_gikyoudai(kunshu, officers[officer].get_id()) or pk::is_like(kunshu, officers[officer].get_id()) )
				officer_value += ���ְ���_������;
				
			// â,���� ��� ����(�ִ� �ɷ°������_�ִ�)-���ɱ�_����_â��_�ּҸ�ŭ ������.
			if( item.type == ��������_�乫�� )
			{
				officer_value +=  pk::max( pk::min( officers[officer].stat[����ɷ�_����], �ɷ°������_�ִ� )-���ɱ�_����_â��_�ּ�, 0 )/���ɱ�_â��_����_���;
					
				if( officers[officer].tekisei[����_â��] >= ����_S or officers[officer].tekisei[����_�غ�] >= ����_S )
					officer_value += ���ɱ�_����S_������;
			}
			
			// ���� ��� (����(�ִ� �ɷ°������_�ִ�)-���ɱ�_����_��_�ּ�)/2 or (�빫�հ�(�ִ� �ɷ°������_�ִ�*2)-���ɱ�_����_��_�빫_�ּ�)/2 �� ���� ������ ������.
			if( item.type == ��������_�� )
				officer_value +=  pk::max( pk::max( pk::min( officers[officer].stat[����ɷ�_����], �ɷ°������_�ִ� )-���ɱ�_����_��_����_�ּ�, 0 )/���ɱ�_��_����_����_���, pk::max( pk::min( officers[officer].stat[����ɷ�_���] + officers[officer].stat[����ɷ�_����], �ɷ°������_�ִ�*2 )-���ɱ�_����_��_�빫_�ּ�, 0)/���ɱ�_��_�빫_����_���) ;
				
			// �ϱ��� ��� (����(�ִ� �ɷ°������_�ִ�)-���ɱ�_����_�ϱ�_�ּ�)/2��ŭ ������.
			if( item.type == ��������_�ϱ� )
				officer_value +=  pk::max( pk::min( officers[officer].stat[����ɷ�_����], �ɷ°������_�ִ� )-���ɱ�_����_�ϱ�_�ּ�, 0 )/���ɱ�_�ϱ�_����_���;
				
			// Ȱ�� ��� (����(�ִ� �ɷ°������_�ִ�)-���ɱ�_����_Ȱ_�ּ�)/2��ŭ ������.
			if( item.type == ��������_Ȱ )
			{
				officer_value +=  pk::max( pk::min( officers[officer].stat[����ɷ�_����], �ɷ°������_�ִ� )-���ɱ�_����_Ȱ_�ּ�, 0 )/���ɱ�_Ȱ_����_���;
				if( officers[officer].tekisei[����_�뺴] >= ����_S or ( officers[officer].skill == Ư��_���� or officers[officer].skill == Ư��_�ý� ) )
					officer_value += ���ɱ�_����S_������;
			}
				
			// ��å�� ��� (����(�ִ� �ɷ°������_�ִ�)-���ɱ�_����_��å_�ּ�)/2��ŭ ������.
			if( item.type == ��������_��å  )
				officer_value +=  pk::max( pk::min( officers[officer].stat[����ɷ�_����], �ɷ°������_�ִ� )-���ɱ�_����_��å_�ּ�, 0 )/���ɱ�_��å_����_���;
				
			// ���� ��� ����(�ִ� �ɷ°������_�ִ�)-���ɱ�_����_��_����_�ּ�/2 or (�빫���� �հ�(�ִ� �ɷ°������_�ִ�*4)-���ɱ�_����_��_�빫����_�ּ�)/4 �� ���� ������ ������
			if( item.type == ��������_�� )
				officer_value +=  pk::max( pk::max( pk::min( officers[officer].stat[����ɷ�_����], �ɷ°������_�ִ� )-���ɱ�_����_��_����_�ּ�, 0 )/���ɱ�_��_����_����_���, pk::max( pk::min( officers[officer].stat[����ɷ�_���] + officers[officer].stat[����ɷ�_����] + officers[officer].stat[����ɷ�_����] + officers[officer].stat[����ɷ�_�ŷ�], �ɷ°������_�ִ�*4)-���ɱ�_����_��_�빫����_�ּ�, 0)/���ɱ�_��_�빫����_����_��� ) ;
				
			if( officer_value > best_person_value )
				{ best_person_id = officers[officer].get_id(); best_person_value = officer_value;}
		}
	}
		
	// ���õ� ������ ���� ������ �ٸ� ���Ⱑ �ִ��� Ȯ��
	if( best_person_id != -1 )
	{
		if( !���ɱ�_��������_����_üũ( best_person_id, item.type ) )
		{
			return best_person_id;
		}
	}

	return -1;
}

/*
	������ �����ڰ� �������� �׽�Ʈ
*/
bool ���ɱ�_����_����������(pk::person@ p, pk::item@ item)
{
	pk::person@ kunshu = pk::get_person(pk::get_kunshu_id(p)); // ����
	int force_id = p.get_force_id();
		
	// ���������� ���� �̻��̸� �Ѿ
	if( item.type >= ��������_���� )
		return true;
		
	// ���������̰ų� �������������̸� �Ѿ
	if( ���ɱ�_��������_üũ( item.get_id(), p.get_id() ) or ���ɱ�_������������_üũ( item.get_id(), p.get_id() ) )
		return true;
		
	// ��� ������ �Ϲ����� ���°� �ƴϸ� �Ѿ. �λ� ���� ���¶�� ���򰡵Ǿ ����ϰ� �������ϴ� �ǰ��� ���常 ������� ��.
	if( !( p.mibun >= �ź�_���� and p.mibun <= �ź�_�Ϲ� ) or p.shoubyou != ��_�ǰ� )
		return true;

	if ( p.mibun == �ź�_���� )
		return false;

	for(uint i=0; i<���ɱ�_����_����.length; i++)
	{
		for (uint j = 1; j<���ɱ�_����_����[i].length; j++)
		{
			pk::person@ p2 = pk::get_person(���ɱ�_����_����[i][j]);
			
			if( ���ɱ�_����_����[i][0] == item.get_id() and pk::is_alive(p2) and p2.get_id() != item.owner and p2.get_force_id() == force_id and p2.mibun >= �ź�_���� and p2.mibun <= �ź�_�Ϲ�)
			{
				if (p2.location <= 86)
					return false;
			}
		}
	}
		
	// 1. ���������� ���� ������ ����� ������ üũ
	if( ���ɱ�_�����_����_��뿩�� and ���ɱ�_�����_����_üũ( item, 0, false ) >= 0 )
	{
		int cond_index = ���ɱ�_�����_����_üũ( item, 0, false );
			
		// ������ ����������� �����Ѵٸ�.....
		if( ���ɱ�_�����_����_����_üũ( p, cond_index ) )
		{
			return true;
		}
	} 
	// 2. ���������� ���� ������ ����� ������ üũ
	else if( ���ɱ�_�����_����_��뿩�� and ���ɱ�_�����_����_üũ( item, 1, false ) >= 0 )
	{
		int cond_index = ���ɱ�_�����_����_üũ( item, 1, false );
			
		// ������ ����������� �����Ѵٸ�.....
		if( ���ɱ�_�����_����_����_üũ( p, cond_index ) )
		{
			return true;
		}
	}
		// 3. �⺻���� üũ �� ���ؿ� ������ �Ѿ
	else if( 
			( item.type == ��������_�乫�� and ���ɱ�_����_â��_����( p, ���ɱ�_����_â��_�ּ�, ����_A ) ) 
			or ( item.type == ��������_�� and ���ɱ�_����_��_����( p, ���ɱ�_����_��_����_�ּ�, ���ɱ�_����_��_�빫_�ּ� ) ) 
			or ( item.type == ��������_�ϱ� and int(p.stat[����ɷ�_����]) >= ���ɱ�_����_�ϱ�_�ּ� )
			or ( item.type == ��������_Ȱ and ���ɱ�_����_Ȱ_����( p, ���ɱ�_����_Ȱ_�ּ�, ����_A ) )
			or ( item.type == ��������_��å and int(p.stat[����ɷ�_����]) >= ���ɱ�_����_��å_�ּ� )
			or ( item.type == ��������_�� and ���ɱ�_����_��_����( p, kunshu, ���ɱ�_����_��_����_�ּ�, ���ɱ�_����_��_�빫����_�ּ�) )
		)
	{
		return true;
	}
		
        	return false;

}

void ���ɱ�_�׿���������( )
{
	array<ItemBest@> item_best_list;
	
	// ���ָ� ������ �Ϲ������ �� ���� 1�� �̻� ���� ������� ����
	for( int i=0 ; i < ����_�� ; i++ )
	{
		pk::item@ item = pk::get_item(i);
		pk::person@ p = pk::get_person(item.owner);
		
		// ���������� ���� �̻��̸� �Ѿ
		if( item.type >= ��������_���� )
			continue;
		
		if( !pk::is_alive(item) or item.status != ��������_���� or !pk::is_alive(p)
			or !pk::is_alive(pk::get_force(p.get_force_id())) or !pk::is_alive(pk::get_person(pk::get_kunshu_id(p))) )
			continue;
		
		// ���ָ� �Ѿ.
		if( p.mibun == �ź�_���� )
			continue;
		
		// �÷��̾� �����̸� �Ѿ.
		if( p.is_player() )
			continue;		
		
		// ��� ������ �Ϲ����� ���°� �ƴϸ� �Ѿ.
		if( !( p.mibun >= �ź�_���� and p.mibun <= �ź�_�Ϲ� ) )
			continue;
		
		ItemBest temp(p.get_id());
		int index_temp = item_best_list.find(temp);
		
		// array�� ������ ������ ���� ������ �߰����� array�� �߰�
		if( index_temp < 0 )
		{
			bool is_unique = ( ���ɱ�_��������_üũ( item.get_id(), p.get_id() ) or ���ɱ�_������������_üũ( item.get_id(), p.get_id() ) ) ? true : false;
			temp.setValue( item.type, item.get_id(), item.value, is_unique);
			item_best_list.insertLast(temp);
		}
		else // �̹� �ִ� ������� ���������� �� �� ���� ������ �߰� ( ���� Ȥ�� ���� ������ ���� ��� ��ġ �� �� �� )
		{
			// ���� ������ ���������̸� �� ������ ������ �Է�
			bool is_unique = ( ���ɱ�_��������_üũ( item.get_id(), p.get_id() ) or ���ɱ�_������������_üũ( item.get_id(), p.get_id() ) ) ? true : false;
			if( is_unique )
				item_best_list[index_temp].setValue( item.type, item.get_id(), item.value, is_unique);
			
			// (�������� ������ �ְų� ���� ��ġ�� ���� ���)�� �ƴ� ��쿣 ���ο� ������ ������ �Է�
			if( !(item_best_list[index_temp].is_unique[item.type] or item_best_list[index_temp].item_value[item.type] >= item.value) )
				item_best_list[index_temp].setValue( item.type, item.get_id(), item.value, is_unique);
		}
	}
	

	// ���� 1�� �̻� ������ �ִ� ����� ������� ������ �ְ��� ������ ����� ����. 
	for( int i=0 ; i < ����_�� ; i++ )
	{
		pk::item@ item = pk::get_item(i);
		pk::person@ p = pk::get_person(item.owner);
		
		// ���������� ���� �̻��̸� �Ѿ
		if( item.type >= ��������_���� )
			continue;
		
		if( !pk::is_alive(item) or item.status != ��������_���� or !pk::is_alive(p)
			or !pk::is_alive(pk::get_force(p.get_force_id())) or !pk::is_alive(pk::get_person(pk::get_force(p.get_force_id()).kunshu)) )
			continue;
			
		pk::person@ kunshu = pk::get_person(pk::get_force(p.get_force_id()).kunshu); // ����
		
		// ���ָ� �Ѿ.
		if( p.mibun == �ź�_���� )
			continue;
		
		// �÷��̾� �����̸� �Ѿ.
		if( p.is_player() )
			continue;
		
		// ��� ������ �Ϲ����� ���°� �ƴϸ� �Ѿ.
		if( !( p.mibun >= �ź�_���� and p.mibun <= �ź�_�Ϲ� ) )
			continue;
		
		for( uint j=0; j<item_best_list.length; j++)
		{
			// ���纸���� ��������� �ٸ��� �Ѿ.
			if( item_best_list[j].person_id != p.get_id() )
				continue;
			
			// �ش� ����� ����(or ����) �����̸� �Ѿ
			if( ���ɱ�_��������_üũ( item.get_id(), p.get_id() ) or ���ɱ�_������������_üũ( item.get_id(), p.get_id() ) )
				continue;
			
			// ���� ����� ������ ������ �ְ��� �����̸� �Ѿ
			if( item_best_list[j].item_id[item.type] == item.get_id() )
				continue;
			
			// �ش���� ���� �����̶�� ���ְ� ����
			string s = "���� <"+pk::decode(pk::get_name(kunshu))+">, <"+pk::decode(pk::get_name(pk::get_person(item.owner)))+"> �׿������� ���� <"+pk::decode(item.name)+"> ����";
			item.owner = kunshu.get_id();		
                      
            		if( ���ɱ�_�α�_����_ǥ��) pk::info(s);
            		if( ���ɱ�_�α�_ȭ��_ǥ��) pk::history_log(pk::get_building(pk::get_person(item.owner).service).pos, -1, pk::encode(s));
            
            		if( ���ɱ�_�α�_�޼���ǥ��) pk::message_box(pk::encode(s));
		}
	}
	
}

/*
	�ش� ���� �ְ��� ���� ����� Ŭ����
*/
class ItemBest
{
	int person_id = -1; // ���� ��ȣ
	array<int> item_id = { -1, -1, -1, -1, -1, -1, -1, -1 }; // ������ ������ȣ
	array<int> item_value = { -1, -1, -1, -1, -1, -1, -1, -1 }; // ������ ������ġ
	array<bool> is_unique = { false, false, false, false, false, false, false, false }; // ������ �������� ����

	ItemBest(int person_id)
	{
		this.person_id = person_id;
	}
	
	void setValue( int item_type, int item_id, int item_value, bool is_unique)
	{
		this.item_id[item_type] = item_id;
		this.item_value[item_type] = item_value;
		this.is_unique[item_type] = is_unique;
	}
	
	bool opEquals( ItemBest& in_ )
	{
		return this.person_id == in_.person_id;
	}
	
}

/* 
	�ش� ������ ������ ����������� üũ
*/
bool ���ɱ�_��������_üũ( int item_id, int player_id )
{

	for(uint i=0; i<���ɱ�_����_����.length; i++)
	{
		for(uint j=1; j<���ɱ�_����_����[i].length; j++)
		{
			if( ���ɱ�_����_����[i][0] == item_id and ���ɱ�_����_����[i][j] == player_id )
				return true;
		}
	}		
	
	return false;
}

/* 
	�ش� ������ ������ ��������������� üũ
*/
bool ���ɱ�_������������_üũ( int item_id, int player_id )
{

	for(uint i=0; i<���ɱ�_����_����_����.length; i++)
	{
		for(uint j=1; j<���ɱ�_����_����_����[i].length; j++)
		{
			if( ���ɱ�_����_����_����[i][0] == item_id and ���ɱ�_����_����_����[i][j] == player_id )
				return true;
		}
	}		
	
	return false;
}

/*
	�ش� ������ ��������� ���� ���� �ִ��� üũ ( �����ϰ�� Array���� ���� ó�� �߰ߵǴ� ���� ���� )
	��, ���� ������ �������� ��� üũ���� �ʰ� ���� ��������� ã�´�.
	���� ������ ���� �����ڰ� ���������� ��� �� �Լ��δ� ã������ ����.
*/
int ���ɱ�_��������_����üũ( int item_id, int force_id )
{
	
	for(uint i=0; i<���ɱ�_����_����.length; i++)
	{
		for(uint j=1; j<���ɱ�_����_����[i].length; j++)
		{
			pk::person@ p = pk::get_person(���ɱ�_����_����[i][j]);
			
			if( ���ɱ�_����_����[i][0] == item_id and pk::is_alive(p) and p.get_id() != pk::get_item(item_id).owner
				and p.get_force_id() == force_id and p.mibun >= �ź�_���� and p.mibun <= �ź�_�Ϲ� )
				return ���ɱ�_����_����[i][j];
		}
	}		
	
	return -1;
}

/*
	�ش� ������ ���� �ִ��� Ȯ��
*/
bool ���ɱ�_��������_����_üũ( int person_id, int item_type )
{
	for( int i=0 ; i < ����_�� ; i++ )
	{
		pk::item@ item= pk::get_item(i);
		
		if( !pk::is_alive(item) or item.status != ��������_���� )
			continue;
		
		if ( item.owner == person_id and item.type == item_type )
		{
			
			string s = "���� <"+pk::decode(pk::get_name(pk::get_person(person_id)))+">, ���� ������ �ٸ� �Ϲݺ��� <"+pk::decode(item.name)+"> ����....";
			
            		if( ���ɱ�_�α�_����_ǥ��) pk::info(s);
           	 		if( ���ɱ�_�α�_ȭ��_ǥ��) pk::history_log(pk::get_building(pk::get_person(item.owner).service).pos, -1, pk::encode(s));
            
            		if( ���ɱ�_�α�_�޼���ǥ��) pk::message_box(pk::encode(s));
			
			return true;
		}
	}
	
	return false;
}

/*
	���� �ݳ�
*/
void ���ɱ�_����_�ݳ�( int person_id, int kunshu_id, int item_type )
{
	for( int i=0 ; i < ����_�� ; i++ )
	{
		pk::item@ item = pk::get_item(i);
		
		if( !pk::is_alive(item) or item.status != ��������_���� )
			continue;
		
		if ( item.owner == person_id and item.type == item_type 
			and !���ɱ�_��������_üũ( item.get_id(), person_id ) and !���ɱ�_������������_üũ( item.get_id(), person_id ) )
		{
			string s = "���� <"+pk::decode(pk::get_name(pk::get_person(person_id)))+">, <"+pk::decode(pk::get_name(pk::get_person(kunshu_id)))+">���� �Ϲݺ��� <"+pk::decode(item.name)+"> �ݳ�";
			
			item.owner = kunshu_id;

            /*
			if( ���ɱ�_�α�_����_ǥ��) Logger().trace(s);
			if( ���ɱ�_�α�_ȭ��_ǥ��) MessageBox().historylog( Point(), -1, s);
            */
            if( ���ɱ�_�α�_����_ǥ��) pk::info(s);
            if( ���ɱ�_�α�_ȭ��_ǥ��) pk::history_log(pk::get_building(pk::get_person(item.owner).service).pos, -1, pk::encode(s));
            
            if( ���ɱ�_�α�_�޼���ǥ��) pk::message_box(pk::encode(s));
		}
	}
}


/*
	������ â, ���� ������ �� �ִ��� ���� üũ
*/
bool ���ɱ�_����_â��_����( pk::person@ p, int power, int apt )
{
	
	if(  ( int(p.stat[����ɷ�_����]) >= power and ( int(p.tekisei[����_â��]) >= apt or int(p.tekisei[����_�غ�]) >= apt) ) or 
		 ( int(p.skill) == Ư��_â�� or int(p.skill) == Ư��_���� or int(p.skill) == Ư��_â�� 
		 or int(p.skill) == Ư��_�ؽ� or int(p.skill) == Ư��_���� or int(p.skill) == Ư��_����
		 or int(p.skill) == Ư��_���� or int(p.skill) == Ư��_���� or int(p.skill) == Ư��_�п� ) )
		 return true;
		 
	return false;
}

/*
	������ ���� ������ �� �ִ��� ���� üũ
	
	@param overall �� �� �հ� üũ ����
*/
bool ���ɱ�_����_��_����( pk::person@ p, int power, int overall )
{
	
	if( int(p.stat[����ɷ�_����]) >= power or int(p.stat[����ɷ�_����] + p.stat[����ɷ�_���] ) >= overall )
		return true;
	
	return false;
}

/*
	������ Ȱ�� ������ �� �ִ��� ���� üũ
*/
bool ���ɱ�_����_Ȱ_����( pk::person@ p, int power, int apt )
{
	
	if(  ( int(p.stat[����ɷ�_����]) >= power and int(p.tekisei[����_�뺴]) >= apt ) or 
		 ( int(p.skill) == Ư��_���� or int(p.skill) == Ư��_�ý� or int(p.skill) == Ư��_��� or int(p.skill) == Ư��_����
		 or int(p.skill) == Ư��_���� or int(p.skill) == Ư��_���� or int(p.skill) == Ư��_�п� ) ) 
		 return true;
		 
	return false;
}

/*
	������ ���� ������ �� �ִ��� ���� üũ
	
	@param overall �� �� �� �� �հ� üũ ����
*/
bool ���ɱ�_����_��_����( pk::person@ p, pk::person@ kunshu, int power, int overall )
{
	// ���� �����̰ų� ����, �������ų� ������ ģ������� ��� �� �ɷº� ĿƮ���� 10�� �϶�.
	if( kunshu.get_id() == p.get_id() or pk::is_like(kunshu, p.get_id()) or pk::is_ketsuen(kunshu, p.get_id()) or pk::is_gikyoudai(kunshu, p.get_id()) )
	{
		power -= 10;
		overall -= 40;
	}

	if( int(p.stat[����ɷ�_����]) >= power or int( p.stat[����ɷ�_����] + p.stat[����ɷ�_���] + p.stat[����ɷ�_����] + p.stat[����ɷ�_�ŷ�] ) >= overall )
		return true;
	
	return false;
}

/*
	������ ����Ǵ� ����� ������ �ִ��� üũ�Ѵ�
	
	@param pk::item@ üũ�� ����
	@param type 0 - ����������ȣ�� üũ, 1 - ���������� üũ
	@param is_kunshu ���� �������� ����
	@return ��ġ�ϴ� ������ �ִٸ� ������ index�� ����, ������ -1 ����
*/
int ���ɱ�_�����_����_üũ( pk::item@ item, int type, bool is_kunshu )
{
	int is_kunshu_num = is_kunshu ? 0 : 1;
	
	for( uint i=0; i<�����_����_����.length; i++ )
	{
		if( type == 0 and �����_����_����[i][2] == item.get_id() and �����_����_����[i][0] == is_kunshu_num )
			return i;
		
		if( type == 1 and �����_����_����[i][1] == item.type and �����_����_����[i][0] == is_kunshu_num )
			return i;
	}

	return -1;
}

/*
	������ �ش� index�� ���ǽ��� ������ ������Ű���� ����
*/
bool ���ɱ�_�����_����_����_üũ( pk::person@ p, int index )
{
	int min_leader = �����_����_����[index][4];
	int min_power = �����_����_����[index][6];
	int min_int = �����_����_����[index][8];
	int min_pol = �����_����_����[index][10];
	int min_char = �����_����_����[index][12];
	
	int min_spear = �����_����_����[index][15];
	int min_polearm = �����_����_����[index][17];
	int min_bow = �����_����_����[index][19];
	int min_horse = �����_����_����[index][21];
	int min_mecha = �����_����_����[index][23];
	int min_water = �����_����_����[index][25];
	
	int min_loyalty = �����_����_����[index][28];
	int min_exploit = �����_����_����[index][31];
	
	if( int(p.stat[����ɷ�_���]) >= min_leader and int(p.stat[����ɷ�_����]) >= min_power and int(p.stat[����ɷ�_����]) >= min_int and int(p.stat[����ɷ�_��ġ]) >= min_pol and int(p.stat[����ɷ�_�ŷ�]) >= min_char and
		int(p.tekisei[����_â��]) >= min_spear and int(p.tekisei[����_�غ�]) >= min_polearm and int(p.tekisei[����_�뺴]) >= min_bow and 
		int(p.tekisei[����_�⺴]) >= min_horse and int(p.tekisei[����_����]) >= min_mecha and int(p.tekisei[����_����]) >= min_water and 
		int(p.loyalty) >= min_loyalty and int(p.kouseki) >= min_exploit )
		return true;
		
	return false;
}

/*
	������ �ش� index�� ���ǽĿ� ���� ��ġ�� ����ؼ� ����
*/
int ���ɱ�_�����_����_����_��ġ( pk::person@ p, int index )
{
	//pk::Random random(win32api::GetTickCount()+p.get_id()*p.get_id()+p.get_force_id());
    
	int value = 0;
	int kunshu_id = pk::get_force(p.get_force_id()).kunshu;
	
	int max_stat = �����_����_����[index][3];
	int mul_leader = �����_����_����[index][5];
	int mul_power = �����_����_����[index][7];
	int mul_int = �����_����_����[index][9];
	int mul_pol = �����_����_����[index][11];
	int mul_char = �����_����_����[index][13];
	int max_apt = �����_����_����[index][14];
	int mul_spear = �����_����_����[index][16];
	int mul_polearm = �����_����_����[index][18];
	int mul_bow = �����_����_����[index][20];
	int mul_horse = �����_����_����[index][22];
	int mul_mecha = �����_����_����[index][24];
	int mul_water = �����_����_����[index][26];
	int max_loyalty = �����_����_����[index][27];
	int mul_loyalty = �����_����_����[index][29];
	int max_exploit = �����_����_����[index][30];
	int mul_exploit = �����_����_����[index][32];
	int mul_parent_child = �����_����_����[index][33];
	int mul_spouse = �����_����_����[index][34];
	int mul_blood = �����_����_����[index][35];
	int mul_brother = �����_����_����[index][36];
	int mul_like = �����_����_����[index][37];
	int random_max = �����_����_����[index][38];
	
	value += pk::min(p.stat[����ɷ�_���], max_stat) * mul_leader;
	value += pk::min(p.stat[����ɷ�_����], max_stat) * mul_power;
	value += pk::min(p.stat[����ɷ�_����], max_stat) * mul_int;
	value += pk::min(p.stat[����ɷ�_��ġ], max_stat) * mul_pol;
	value += pk::min(p.stat[����ɷ�_�ŷ�], max_stat) * mul_char;
	
	value += pk::min(p.tekisei[����_â��], max_apt) * mul_spear;
	value += pk::min(p.tekisei[����_�غ�], max_apt) * mul_polearm;
	value += pk::min(p.tekisei[����_�뺴], max_apt) * mul_bow;
	value += pk::min(p.tekisei[����_�⺴], max_apt) * mul_horse;
	value += pk::min(p.tekisei[����_����], max_apt) * mul_mecha;
	value += pk::min(p.tekisei[����_����], max_apt) * mul_water;
	
	value += pk::min(p.loyalty, max_loyalty) * mul_loyalty;
	value += pk::min(p.kouseki, max_exploit) * mul_exploit;
	value += ( pk::is_oyako(p, kunshu_id) ? 1 : 0 )* mul_parent_child;
	value += ( pk::is_fuufu(p, kunshu_id) ? 1 : 0 )* mul_spouse;
	value += ( pk::is_ketsuen(p, kunshu_id) ? 1 : 0 )* mul_blood;
	value += ( pk::is_gikyoudai(p, kunshu_id) ? 1 : 0 )* mul_brother;
	value += ( pk::is_like(p, kunshu_id) ? 1 : 0 )* mul_like;
	
	//int temp = random(random_max);
	int temp = pk::rand(random_max);
	value += temp;
	
	// Logger().trace("<"+p.get_id()+"> �̸� : " + p.name + ", Tick="+win32api::GetTickCount()+" ����="+temp+" ��ġ=" + value );
	
	return value;
}


/*
	�ӽ÷� ������ ���������� �ٷ�� Ŭ����
	

	������ �ɷ¿� ���� ������ ���� �� �̹� ������ ������ �ִ� ������ 
	������ �ɷ�ġ�� ���ԵǾ ���Ǵ� ������ �߻��ؼ�, �װ� ���� ���ؼ�
	������ �ɷ��� üũ�ϱ� ���� �� array�� �������� �����ָ� �ӽ÷� ����� ��
	�������� ����鿡�Լ� ���� ������ �� �ɷ�ġ�� üũ�Ѵ�.
	�ɷ�ġ üũ�� ���� �Ŀ��� �� Array�� �ִ� ���������� ���� �ٽ� �������� �����ش�.
	�߸� ����ϸ� ���������� ������ ������ �ɼ� �����Ƿ� 
	�ڵ� �� �������� �ӽ÷� ���ҾҴٰ� �����ֱ� �������� �Ժη� ������ ���������� ���� ��ƾ�� ��������� �ȵȴ�. 
	�⺻�� ��� -1
*/

class TempItemHistory
{
	array<int> temp_item_array(����_��, -1); 	
	
	TempItemHistory(){}
	
	void save()
	{
		for( int i=0 ; i < ����_�� ; i++ )
		{		
			pk::item@ item= pk::get_item(i);
			
			temp_item_array[i] = item.owner;	
			item.owner = -1;
		}
	}
	
	void rollBack()
	{
		for( int i=0 ; i < ����_�� ; i++ )
		{		
			pk::item@ item= pk::get_item(i);

			item.owner = temp_item_array[i];			
			temp_item_array[i] = -1;
		}
	}
}