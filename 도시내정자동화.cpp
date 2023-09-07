
	/// ���� �ڵ�ȭ �׸� (���ú� ���/���� ���� ����)
	//	- �� �׸񺰷� ��� ���ÿ� ���Ͽ� �ϰ������� ���/���� ���� ���� ����
	// 1. ���� (�ʱ� ���� : ����)
	// 2. �Ʒ� (�ʱ� ���� : ����)
	// 3. ¡�� (�ʱ� ���� : ����)
	// 4. ���� (�ʱ� ���� : ����)
	// 5. ���� (�ʱ� ���� : ����)

	/// ���� �ڵ�ȭ ��� ����
	// 1. �÷��̾� 1���� ���ø� ����
	// 2. ������ �� ��� ����
	// 3. ���� ��� ������ ���� ������ �⺻ ������ �����ؾ� ���� (�ൿ��, ��, �ൿ���� ����, �ʿ� �ü� ��)
	//	- ��, �ൿ���� ��쿡�� �Ҹ� ���� �������� ����
	// 4. '���'���� ������ ���� �׸� ���ؼ��� ����
	// 5. ������ ���� �ڵ�ȭ ������ �����ϴ� ��쿡�� ����
	// 6. ���� ��� ���� �� �޽��� ǥ�� (�޽��� �ڽ�, �α� �޽��� - ǥ������ ���� ���� ����)

	/// ���� �ڵ�ȭ ���� (���ú� ���� ���� ����)
	//	- �� �׸񺰷� ��� ���ÿ� ���Ͽ� �ϰ������� ���� ���� ����
	// 1. ��������_ġ��		(�ʱ� ���� : 90)	- ������ ġ���� ������ �������� ġ�� ������ ��� ���� 
	// 2. �Ʒñ���_��º���	(�ʱ� ���� : 95(%))	- ������ �ִ� ��� ��� ���� ����� ������ ������ �Ʒú��� ������ ��� �Ʒ�
	// 3. ¡������_ġ��		(�ʱ� ���� : 95)	- ������ ġ���� ������ ¡������ ġ�� �̻��� ��� ¡��
	// 4. ¡������_��		(�ʱ� ���� : 2000)	- ������ ���� ������ ¡������ �� �̻��� ��� ¡��
	// 5. ¡������_��������	(�ʱ� ���� : 150(%))- ������ ���� ���� ��� ���� ������ ������ ������ ¡������ �������� �̻��� ��� ¡��
	// 6. �������_�漺��	(�ʱ� ���� : 90)	- ������ �漺���� ������ ������� �漺�� ������ ��� ����

	/// ���� �ڵ�ȭ ���� ��� (����, ������ ���� ����)
	//  - ��� ���ÿ� ���Ͽ� �ϰ������� ���� ���� ��� ���� ����
	// ��� 1 : ���� - �Ʒ� - ¡�� - ���� - ���� (�ʱ� ����)
	// ��� 2 : ���� - ¡�� - �Ʒ� - ���� - ����
	// ��� 3 : ¡�� - ���� - �Ʒ� - ���� - ����
	// ��� 4 : ¡�� - �Ʒ� - ���� - ���� - ����
	// ��� 5 : �Ʒ� - ¡�� - ���� - ���� - ����
	// ��� 6 : �Ʒ� - ���� - ¡�� - ���� - ����

	/// ���� ����
	// 1. ������ �÷����ϴ� ���̺� ������ �ε��� ��쿡�� �׸񺰷� �ʱ� ������ �ٸ��� �����Ǿ� ���� �� �ֽ��ϴ�.
	//	- ���̺� ������ �̵��Ͻô� ��� PK2.1 ��ġ �� SaveData ������ �������ϵ� �Բ� �Ű� �����ϼž� ������ �����˴ϴ�.
	//	(���� ���� ������ �ش� ������ ���̺� ���Ͽ� ����Ǵ� ������ ���Դϴ�. 'ö�ű���.cpp' ���� ������ ���������Դϴ�.)
	// 2. �ڼ��� ���ø� ���ѱ� ��� ������ �ʱ�ȭ ����
	//	- ���� �ڵ�ȭ ���� ������ : �ʱ�ȭ�� (���� ��Żȯ �� �ʱ� �������� �ʱ�ȭ)
	//	- ���� �ڵ�ȭ �׸� ���/���� ������ : �ʱ�ȭ�� (���� ��Żȯ �� �ʱ� �������� �ʱ�ȭ)
	//	- ���� �ڵ�ȭ ���� ������ : �ʱ�ȭ���� ���� (���� ��Żȯ �� ���� �������� �ݿ���)
	// 3. ���ÿ� Ŀ���� �������� ȭ�� ���� ��ܿ� ���� �ڵ�ȭ ���� ������ ǥ�õ˴ϴ�.
	//	- ���� �ڵ�ȭ ����, ���� �ڵ�ȭ �׸� ���/���� ����, ���� �ڵ�ȭ ���ذ��� ������ �ݿ��Ǿ� ǥ�õ˴ϴ�.
	// 4. ���� �ڵ�ȭ�� ���� ����(�� ���ÿ� ����)������ �̷������ �ʽ��ϴ�.
	// 5. ������ ������ �Ʒ� CUSTOMIZE �κ��� �����Ͻñ� �ٶ��ϴ�.
	// 6. "ö�ű���" �ؽ� ���� KEY �ε��� ��ȣ(uint16)�� 50~650 �������� ����߽��ϴ�.
	//	- ���� 'ö�ű���.cpp' ���Ͽ����� 0~47 ����ϰ� �ֽ��ϴ�.

namespace ���ó����ڵ�ȭ
{

/// ================================== CUSTOMIZE ============================================


	/// ���� �ڵ�ȭ ���� �� �ൿ�� �Ҹ� ���� ����
	const bool �����ڵ�ȭ_�ൿ�¼Ҹ�_���� = true;	// true = �ൿ�� �Ҹ�, �ൿ�� ���� �� �̼���

	/// ���� �ڵ�ȭ ���� �� �޽��� �ڽ� ǥ�� ����
	const bool �����ڵ�ȭ_�޽����ڽ�_ǥ�� = true;	// true = �޽��� �ڽ� ǥ��, false = �α� �޽��� ǥ��

	/// Ŀ���� �ڼ��� 1���� ���ÿ� ���� ��� ��� ȭ�� ���� ��ܿ� ���� �ڵ�ȭ �������¸� ǥ��
	const bool �����ڵ�ȭ_��������ǥ�� = true;

///	-----------------------------------------------------------------------------------------

	/// ����Ű ����

	// ���� ��� ���� �޴�
	const string �����޴�_���� = "Z";
	const string �����޴�_����_�ϰ����� = "1";
	const string �����޴�_���� = "2";

	// ���/���� ���� �޴�
	const string �����޴�_������ = "X";
	const string �����޴�_������_�ϰ�����_����ȭ = "Q";
	const string �����޴�_������_�ϰ����� = "1";
	const string �����޴�_������_���� = "2";
	const string �����޴�_������_�Ʒ� = "3";
	const string �����޴�_������_¡�� = "4";
	const string �����޴�_������_���� = "5";
	const string �����޴�_������_���� = "6";

	// ���� ���� ���� �޴�
	const string �����޴�_���� = "C";
	const string �����޴�_����_�ϰ����� = "1";
	const string �����޴�_����_����_ġ�� = "2";
	const string �����޴�_����_�Ʒ�_��º��� = "3";
	const string �����޴�_����_¡��_ġ�� = "4";
	const string �����޴�_����_¡��_�� = "5";
	const string �����޴�_����_¡��_�������� = "6";
	const string �����޴�_����_����_�漺�� = "7";

///	-----------------------------------------------------------------------------------------

	/// ���� ���� �ڵ�ȭ ���� ����

	// ���ۺδ밡 ������ ������ ���� ���� ��� ������ ���� ����
	const float ���ۺ��º��� = 0.5f;

	// true = �Ĺ� ���÷κ��� ��� ���ñ��� ���� (��� ���� = �� ���ÿ� �Ÿ� 2)
	// false = �Ĺ�, ��� ���÷κ��� ���, ���� ���ñ��� ���� (���� ���� = �� ���ÿ� �Ÿ� 1)
	const bool �����Ѱ輳��_��赵�ñ��� = true;

	// ���ۺδ밡 ������ ������ �ִ� ���� ��� ���� ������ ����
	// �⺻�� ���� : ���� ������ �ִ� ������ 0.5�� �̻��� ��� ����
	const float ���۰�������_�������� = 0.5f;

	// ���ۺδ밡 ������ ������ ���� ���� ��� ���� ������ ����
	// �⺻�� ���� : ���� ������ ���� ������ 1.5�� �̻��� ��� ����
	const float ���۰�������_�������� = 1.5f;

	// ���� �ĺ� ������ �ִ� ���� ��� ���� ������ ����
	// �⺻�� ���� : ���� �ĺ� ������ ���� ������ �ִ� ������ 0.5�� ������ ��� ����
	const float �����ʿ�����_��������1 = 0.5f;

	// ���ۺδ밡 ������ ������ ���� ��� ���� �ĺ� ������ ���� ����
	// �⺻�� ���� : ���� �ĺ� ������ ���� ������ ���ۺδ밡 ������ ���� ���� ������ 0.5�� ������ ��� ����
	const float �����ʿ�����_��������2 = 0.5f;


/// =========================================================================================


	const bool ����� = false;

	/// ���� ����� �ؽ� ��
	// �׽�Ʈ ��� pk::hash �Լ��� "ö�ű���" ���� �ٸ� ������ �ؽ� ���� �������� �ʴ� ������ ������
	// �ε����ϰ� "ö�ű���" ������ �ؽ� ���� ����ϵ� �ε��� ���� ������ 'ö�ű���.cpp' ���ϰ� �浹���� �ʵ��� ����
	const int KEY = pk::hash("ö�ű���");

	/// �׸� KEY index �� (uint16)
	// ���� : 'ö�ű���.cpp'���� ����ϴ� KEY �ε��� �� ���� : 0 <= i < 47 (��ü ���� �� = 47)
	const int KEY_�ε�����_�߰�_���� = 50;					//  50	<= i <	 92 (��ü ���� �� = 42)
	const int KEY_�ε�����_�߰�_���� = 100;					// 100	<= i <	147 (��ü ���� �� = 47)
	const int KEY_�ε�����_�߰�_�Ʒ� = 150;					// 150	<= i <	197 (��ü ���� �� = 47)
	const int KEY_�ε�����_�߰�_¡�� = 200;					// 200	<= i <	247 (��ü ���� �� = 47)
	const int KEY_�ε�����_�߰�_���� = 250;					// 250	<= i <	297 (��ü ���� �� = 47)
	const int KEY_�ε�����_�߰�_�������_�漺�� = 300;		// 300	<= i <	342 (��ü ���� �� = 42)
	const int KEY_�ε�����_�߰�_���� = 350;					// 350	<= i <	397 (��ü ���� �� = 47)
	const int KEY_�ε�����_�߰�_��������_ġ�� = 400;		// 400	<= i <	442 (��ü ���� �� = 42)
	const int KEY_�ε�����_�߰�_�Ʒñ���_��º��� = 450;	// 450	<= i <	492 (��ü ���� �� = 42)
	const int KEY_�ε�����_�߰�_¡������_ġ�� = 500;		// 500	<= i <	542 (��ü ���� �� = 42)
	const int KEY_�ε�����_�߰�_¡������_�� = 550;			// 550	<= i <	592 (��ü ���� �� = 42)
	const int KEY_�ε�����_�߰�_¡������_�������� = 600;	// 600	<= i <	642 (��ü ���� �� = 42)

	/// ���� �ڵ�ȭ �ε����� �׸�
	const int �����ڵ�ȭ_���� = 0;
	const int �����ڵ�ȭ_�Ʒ� = 1;
	const int �����ڵ�ȭ_¡�� = 2;
	const int �����ڵ�ȭ_���� = 3;
	const int �����ڵ�ȭ_���� = 4;

	/// ���� : ���� �޴�
	// ���� : ����, ¡��(����), ����(����), ����, �ŷ�
	// ���� : �Ʒ�(����), ����(����)
	// ���� : Ž��, ���, ����(����)
	// �ܱ� : ��ȣ���, ��ȣź��, ������


	class Main
	{
		/// ���ú� ���� �ڵ�ȭ ���� ����, ������� �漺�� ����� ���
		// ���� ��� : ���ú��� ���� �� ���� (�ʱ�ȭ ���� ������ ���� �� ����)
		array<int> �����ڵ�ȭ_��������(����_��, 1);	// �ʱ� ���� : ���� ��� 1
		array<int> �������_�漺��(����_��, 90);	// �ʱ� ���� : 90
		array<int> ��������_ġ��(����_��, 90);		// �ʱ� ���� : 90
		array<int> �Ʒñ���_��º���(����_��, 95);	// �ʱ� ���� : 95(%)
		array<int> ¡������_ġ��(����_��, 95);		// �ʱ� ���� : 95
		array<int> ¡������_��(����_��, 2000);		// �ʱ� ���� : 2000
		array<int> ¡������_��������(����_��, 150);	// �ʱ� ���� : 150(%)

		/// ���º� ���� �ڵ�ȭ ��뿩�� ���� ����� ���
		// ���� ��� : ���º��� ��� ���ÿ� ���� ������ ����(��Ʈ ���� Ȱ��)
		array<uint64> ����_��뿩��(����_��, uint64(0));	// �ʱ� ���� : ����
		array<uint64> �Ʒ�_��뿩��(����_��, uint64(0));	// �ʱ� ���� : ����
		array<uint64> ¡��_��뿩��(����_��, uint64(0));	// �ʱ� ���� : ����
		array<uint64> ����_��뿩��(����_��, uint64(0));	// �ʱ� ���� : ����
		array<uint64> ����_��뿩��(����_��, uint64(0));	// �ʱ� ���� : ����

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		Main()
		{
			/// ���� �ڵ�ȭ ���� �޴�
			add_menu_���ó����ڵ�ȭ();

			/// ���� �ڵ�ȭ ���� ǥ��
			// ������ Ŀ���� ���� ��� ��� �ش� ������ ���� �ڵ�ȭ ���� ���� ǥ��
			pk::bind(120, pk::trigger120_t(����ȭ��׸���_���ó����ڵ�ȭ_����ǥ��));

			/// ���� �ڵ�ȭ ���� Ʈ����
			pk::bind(112, pk::trigger112_t(������_���ó����ڵ�ȭ));

			/// ���� ������ Ʈ����
			pk::bind(102, pk::trigger102_t(�ó������ʱ�ȭ_���ó����ڵ�ȭ_�����ҷ�����));
			pk::bind(105, pk::trigger105_t(����_���ó����ڵ�ȭ_��������));
			pk::bind(111, pk::trigger111_t(�Ͻ���_���ó����ڵ�ȭ_�����ʱ�ȭ));
		}

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		void add_menu_���ó����ڵ�ȭ()
		{
			pk::menu_item �����ڵ�ȭ_�����޴�_����;
			int parent_����;
			�����ڵ�ȭ_�����޴�_����.menu = 0;
			�����ڵ�ȭ_�����޴�_����.shortcut = �����޴�_����;
			�����ڵ�ȭ_�����޴�_����.init = pk::building_menu_item_init_t(init);
			�����ڵ�ȭ_�����޴�_����.is_visible = pk::menu_item_is_visible_t(isVisible);
			�����ڵ�ȭ_�����޴�_����.get_text = cast<pk::menu_item_get_text_t@>(function(){return pk::encode("�ڵ����� ����");});
			parent_���� = pk::add_menu_item(�����ڵ�ȭ_�����޴�_����);

			pk::menu_item �����ڵ�ȭ_�����޴�_������;
			int parent_������;
			�����ڵ�ȭ_�����޴�_������.menu = 0;
			�����ڵ�ȭ_�����޴�_������.shortcut = �����޴�_������;
			�����ڵ�ȭ_�����޴�_������.init = pk::building_menu_item_init_t(init);
			�����ڵ�ȭ_�����޴�_������.is_visible = pk::menu_item_is_visible_t(isVisible);
			�����ڵ�ȭ_�����޴�_������.get_text = cast<pk::menu_item_get_text_t@>(function(){return pk::encode("�ڵ����� ���");});
			parent_������ = pk::add_menu_item(�����ڵ�ȭ_�����޴�_������);

			pk::menu_item �����ڵ�ȭ_�����޴�_����;
			int parent_����;
			�����ڵ�ȭ_�����޴�_����.menu = 0;
			�����ڵ�ȭ_�����޴�_����.shortcut = �����޴�_����;
			�����ڵ�ȭ_�����޴�_����.init = pk::building_menu_item_init_t(init);
			�����ڵ�ȭ_�����޴�_����.is_visible = pk::menu_item_is_visible_t(isVisible);
			�����ڵ�ȭ_�����޴�_����.get_text = cast<pk::menu_item_get_text_t@>(function(){return pk::encode("�ڵ����� ����");});
			parent_���� = pk::add_menu_item(�����ڵ�ȭ_�����޴�_����);

			pk::menu_item �����ڵ�ȭ_�޴�_�ϰ�����_����;
			�����ڵ�ȭ_�޴�_�ϰ�����_����.menu = parent_����;
			�����ڵ�ȭ_�޴�_�ϰ�����_����.shortcut = �����޴�_����_�ϰ�����;
			�����ڵ�ȭ_�޴�_�ϰ�����_����.get_text = pk::menu_item_get_text_t(getText_�ϰ�����_����);
			�����ڵ�ȭ_�޴�_�ϰ�����_����.get_desc = pk::menu_item_get_desc_t(getDesc_�ϰ�����_����);
			�����ڵ�ȭ_�޴�_�ϰ�����_����.handler = pk::menu_item_handler_t(handler_�ϰ�����_����);
			pk::add_menu_item(�����ڵ�ȭ_�޴�_�ϰ�����_����);

			pk::menu_item �����ڵ�ȭ_�޴�_����;
			�����ڵ�ȭ_�޴�_����.menu = parent_����;
			�����ڵ�ȭ_�޴�_����.shortcut = �����޴�_����;
			�����ڵ�ȭ_�޴�_����.get_text = pk::menu_item_get_text_t(getText_����);
			�����ڵ�ȭ_�޴�_����.get_desc = pk::menu_item_get_desc_t(getDesc_����);
			�����ڵ�ȭ_�޴�_����.handler = pk::menu_item_handler_t(handler_����);
			pk::add_menu_item(�����ڵ�ȭ_�޴�_����);

			pk::menu_item �����ڵ�ȭ_�޴�_�ϰ�����_��뿩��_����ȭ;
			�����ڵ�ȭ_�޴�_�ϰ�����_��뿩��_����ȭ.menu = parent_������;
			�����ڵ�ȭ_�޴�_�ϰ�����_��뿩��_����ȭ.shortcut = �����޴�_������_�ϰ�����_����ȭ;
			�����ڵ�ȭ_�޴�_�ϰ�����_��뿩��_����ȭ.get_text = pk::menu_item_get_text_t(getText_�ϰ�����_��뿩��_����ȭ);
			�����ڵ�ȭ_�޴�_�ϰ�����_��뿩��_����ȭ.get_desc = pk::menu_item_get_desc_t(getDesc_�ϰ�����_��뿩��_����ȭ);
			�����ڵ�ȭ_�޴�_�ϰ�����_��뿩��_����ȭ.handler = pk::menu_item_handler_t(handler_�ϰ�����_��뿩��_����ȭ);
			pk::add_menu_item(�����ڵ�ȭ_�޴�_�ϰ�����_��뿩��_����ȭ);

			pk::menu_item �����ڵ�ȭ_�޴�_�ϰ�����_��뿩��;
			�����ڵ�ȭ_�޴�_�ϰ�����_��뿩��.menu = parent_������;
			�����ڵ�ȭ_�޴�_�ϰ�����_��뿩��.shortcut = �����޴�_������_�ϰ�����;
			�����ڵ�ȭ_�޴�_�ϰ�����_��뿩��.get_text = pk::menu_item_get_text_t(getText_�ϰ�����_��뿩��);
			�����ڵ�ȭ_�޴�_�ϰ�����_��뿩��.get_desc = pk::menu_item_get_desc_t(getDesc_�ϰ�����_��뿩��);
			�����ڵ�ȭ_�޴�_�ϰ�����_��뿩��.handler = pk::menu_item_handler_t(handler_�ϰ�����_��뿩��);
			pk::add_menu_item(�����ڵ�ȭ_�޴�_�ϰ�����_��뿩��);

			pk::menu_item �����ڵ�ȭ_�޴�_����_��뿩��;
			�����ڵ�ȭ_�޴�_����_��뿩��.menu = parent_������;
			�����ڵ�ȭ_�޴�_����_��뿩��.shortcut = �����޴�_������_����;
			�����ڵ�ȭ_�޴�_����_��뿩��.get_text = pk::menu_item_get_text_t(getText_����);
			�����ڵ�ȭ_�޴�_����_��뿩��.get_desc = pk::menu_item_get_desc_t(getDesc_����);
			�����ڵ�ȭ_�޴�_����_��뿩��.handler = pk::menu_item_handler_t(handler_����);
			pk::add_menu_item(�����ڵ�ȭ_�޴�_����_��뿩��);

			pk::menu_item �����ڵ�ȭ_�޴�_�Ʒ�_��뿩��;
			�����ڵ�ȭ_�޴�_�Ʒ�_��뿩��.menu = parent_������;
			�����ڵ�ȭ_�޴�_�Ʒ�_��뿩��.shortcut = �����޴�_������_�Ʒ�;
			�����ڵ�ȭ_�޴�_�Ʒ�_��뿩��.get_text = pk::menu_item_get_text_t(getText_�Ʒ�);
			�����ڵ�ȭ_�޴�_�Ʒ�_��뿩��.get_desc = pk::menu_item_get_desc_t(getDesc_�Ʒ�);
			�����ڵ�ȭ_�޴�_�Ʒ�_��뿩��.handler = pk::menu_item_handler_t(handler_�Ʒ�);
			pk::add_menu_item(�����ڵ�ȭ_�޴�_�Ʒ�_��뿩��);

			pk::menu_item �����ڵ�ȭ_�޴�_¡��_��뿩��;
			�����ڵ�ȭ_�޴�_¡��_��뿩��.menu = parent_������;
			�����ڵ�ȭ_�޴�_¡��_��뿩��.shortcut = �����޴�_������_¡��;
			�����ڵ�ȭ_�޴�_¡��_��뿩��.get_text = pk::menu_item_get_text_t(getText_¡��);
			�����ڵ�ȭ_�޴�_¡��_��뿩��.get_desc = pk::menu_item_get_desc_t(getDesc_¡��);
			�����ڵ�ȭ_�޴�_¡��_��뿩��.handler = pk::menu_item_handler_t(handler_¡��);
			pk::add_menu_item(�����ڵ�ȭ_�޴�_¡��_��뿩��);

			pk::menu_item �����ڵ�ȭ_�޴�_����_��뿩��;
			�����ڵ�ȭ_�޴�_����_��뿩��.menu = parent_������;
			�����ڵ�ȭ_�޴�_����_��뿩��.shortcut = �����޴�_������_����;
			�����ڵ�ȭ_�޴�_����_��뿩��.get_text = pk::menu_item_get_text_t(getText_����);
			�����ڵ�ȭ_�޴�_����_��뿩��.get_desc = pk::menu_item_get_desc_t(getDesc_����);
			�����ڵ�ȭ_�޴�_����_��뿩��.handler = pk::menu_item_handler_t(handler_����);
			pk::add_menu_item(�����ڵ�ȭ_�޴�_����_��뿩��);

			pk::menu_item �����ڵ�ȭ_�޴�_����_��뿩��;
			�����ڵ�ȭ_�޴�_����_��뿩��.menu = parent_������;
			�����ڵ�ȭ_�޴�_����_��뿩��.shortcut = �����޴�_������_����;
			�����ڵ�ȭ_�޴�_����_��뿩��.get_text = pk::menu_item_get_text_t(getText_����);
			�����ڵ�ȭ_�޴�_����_��뿩��.get_desc = pk::menu_item_get_desc_t(getDesc_����);
			�����ڵ�ȭ_�޴�_����_��뿩��.handler = pk::menu_item_handler_t(handler_����);
			pk::add_menu_item(�����ڵ�ȭ_�޴�_����_��뿩��);

			pk::menu_item �����ڵ�ȭ_�޴�_�ϰ�����_����;
			�����ڵ�ȭ_�޴�_�ϰ�����_����.menu = parent_����;
			�����ڵ�ȭ_�޴�_�ϰ�����_����.shortcut = �����޴�_����_�ϰ�����;
			�����ڵ�ȭ_�޴�_�ϰ�����_����.get_text = pk::menu_item_get_text_t(getText_�ϰ�����_����);
			�����ڵ�ȭ_�޴�_�ϰ�����_����.get_desc = pk::menu_item_get_desc_t(getDesc_�ϰ�����_����);
			�����ڵ�ȭ_�޴�_�ϰ�����_����.handler = pk::menu_item_handler_t(handler_�ϰ�����_����);
			pk::add_menu_item(�����ڵ�ȭ_�޴�_�ϰ�����_����);

			pk::menu_item �����ڵ�ȭ_�޴�_��������_ġ��;
			�����ڵ�ȭ_�޴�_��������_ġ��.menu = parent_����;
			�����ڵ�ȭ_�޴�_��������_ġ��.shortcut = �����޴�_����_����_ġ��;
			�����ڵ�ȭ_�޴�_��������_ġ��.get_text = pk::menu_item_get_text_t(getText_��������_ġ��);
			�����ڵ�ȭ_�޴�_��������_ġ��.get_desc = pk::menu_item_get_desc_t(getDesc_��������_ġ��);
			�����ڵ�ȭ_�޴�_��������_ġ��.handler = pk::menu_item_handler_t(handler_��������_ġ��);
			pk::add_menu_item(�����ڵ�ȭ_�޴�_��������_ġ��);

			pk::menu_item �����ڵ�ȭ_�޴�_�Ʒñ���_��º���;
			�����ڵ�ȭ_�޴�_�Ʒñ���_��º���.menu = parent_����;
			�����ڵ�ȭ_�޴�_�Ʒñ���_��º���.shortcut = �����޴�_����_�Ʒ�_��º���;
			�����ڵ�ȭ_�޴�_�Ʒñ���_��º���.get_text = pk::menu_item_get_text_t(getText_�Ʒñ���_��º���);
			�����ڵ�ȭ_�޴�_�Ʒñ���_��º���.get_desc = pk::menu_item_get_desc_t(getDesc_�Ʒñ���_��º���);
			�����ڵ�ȭ_�޴�_�Ʒñ���_��º���.handler = pk::menu_item_handler_t(handler_�Ʒñ���_��º���);
			pk::add_menu_item(�����ڵ�ȭ_�޴�_�Ʒñ���_��º���);

			pk::menu_item �����ڵ�ȭ_�޴�_¡������_ġ��;
			�����ڵ�ȭ_�޴�_¡������_ġ��.menu = parent_����;
			�����ڵ�ȭ_�޴�_¡������_ġ��.shortcut = �����޴�_����_¡��_ġ��;
			�����ڵ�ȭ_�޴�_¡������_ġ��.get_text = pk::menu_item_get_text_t(getText_¡������_ġ��);
			�����ڵ�ȭ_�޴�_¡������_ġ��.get_desc = pk::menu_item_get_desc_t(getDesc_¡������_ġ��);
			�����ڵ�ȭ_�޴�_¡������_ġ��.handler = pk::menu_item_handler_t(handler_¡������_ġ��);
			pk::add_menu_item(�����ڵ�ȭ_�޴�_¡������_ġ��);

			pk::menu_item �����ڵ�ȭ_�޴�_¡������_��;
			�����ڵ�ȭ_�޴�_¡������_��.menu = parent_����;
			�����ڵ�ȭ_�޴�_¡������_��.shortcut = �����޴�_����_¡��_��;
			�����ڵ�ȭ_�޴�_¡������_��.get_text = pk::menu_item_get_text_t(getText_¡������_��);
			�����ڵ�ȭ_�޴�_¡������_��.get_desc = pk::menu_item_get_desc_t(getDesc_¡������_��);
			�����ڵ�ȭ_�޴�_¡������_��.handler = pk::menu_item_handler_t(handler_¡������_��);
			pk::add_menu_item(�����ڵ�ȭ_�޴�_¡������_��);

			pk::menu_item �����ڵ�ȭ_�޴�_¡������_��������;
			�����ڵ�ȭ_�޴�_¡������_��������.menu = parent_����;
			�����ڵ�ȭ_�޴�_¡������_��������.shortcut = �����޴�_����_¡��_��������;
			�����ڵ�ȭ_�޴�_¡������_��������.get_text = pk::menu_item_get_text_t(getText_¡������_��������);
			�����ڵ�ȭ_�޴�_¡������_��������.get_desc = pk::menu_item_get_desc_t(getDesc_¡������_��������);
			�����ڵ�ȭ_�޴�_¡������_��������.handler = pk::menu_item_handler_t(handler_¡������_��������);
			pk::add_menu_item(�����ڵ�ȭ_�޴�_¡������_��������);

			pk::menu_item �����ڵ�ȭ_�޴�_�������_�漺��;
			�����ڵ�ȭ_�޴�_�������_�漺��.menu = parent_����;
			�����ڵ�ȭ_�޴�_�������_�漺��.shortcut = �����޴�_����_����_�漺��;
			�����ڵ�ȭ_�޴�_�������_�漺��.get_text = pk::menu_item_get_text_t(getText_�������_�漺��);
			�����ڵ�ȭ_�޴�_�������_�漺��.get_desc = pk::menu_item_get_desc_t(getDesc_�������_�漺��);
			�����ڵ�ȭ_�޴�_�������_�漺��.handler = pk::menu_item_handler_t(handler_�������_�漺��);
			pk::add_menu_item(�����ڵ�ȭ_�޴�_�������_�漺��);
		}

		void ����ȭ��׸���_���ó����ڵ�ȭ_����ǥ��()
		{
			if (!�����ڵ�ȭ_��������ǥ��) return;

			// Ŀ���� ����Ű�� ��ǥ
			pk::point cursor_pos = pk::get_cursor_hex_pos();
			if (!pk::is_valid_pos(cursor_pos)) return;

			// Ŀ���� ����Ű�� ��ǥ ���� �ǹ�
			pk::building@ building = pk::get_building(cursor_pos);
			if (building is null) return;

			// Ŀ���� ����Ű�� ��ǥ ���� ����
			pk::city@ city = pk::building_to_city(building);
			if (city is null) return;

			// ������ ��ǥ ���� Ȯ��
			pk::point city_pos = city.get_pos();
			if (!pk::is_valid_pos(city_pos))return;

			// ������ ���� �� ���� ���� Ȯ��
			if (!city.is_player()) return;
			if (!pk::is_player_controlled(city)) return;
			if (city.get_force_id() != pk::get_current_turn_force_id()) return;

			// ���� �ڵ�ȭ ���� ���� ǥ��
			func_�����ڵ�ȭ_����ǥ��(building, pk::get_current_turn_force_id(), city.get_id(), �����ڵ�ȭ_��������[city.get_id()]);
		}

		void ������_���ó����ڵ�ȭ(pk::force@ force)
		{
			if (!force.is_player()) return;	// ��ǻ�� ���� ����

			array<pk::city@> city_list = pk::list_to_array(pk::get_city_list(force));	// ���� ���� ���
			for (int i = 0; i < int(city_list.length); i++)
			{
				pk::city@ city = city_list[i];
				pk::building@ building = pk::city_to_building(city);

				if (�����)
				{
					string city_name = pk::format("���� \x1b[1x{}\x1b[0x", pk::decode(pk::get_name(city)));
					pk::message_box(pk::encode(pk::format("{} Ȯ�ε�", city_name)));
				}

				if (!pk::is_player_controlled(building))			continue;	// �÷��̾� ���ӱ��� ������ ��� ����
				if (pk::get_idle_person_list(building).count == 0)	continue;	// �ൿ���� ������ ���� ��� ����

				/// ���� ����
				// cmd ����ü�� ����Ͽ� ���� ����� �����ϴ� ��� ������ �Ұ����� ��Ȳ�̸� �˾Ƽ� �������� ���� (���� ���� ����)
				// ���� ������ �Ұ����� ��츦 �������� �߰����� �ʾƵ� �� (�ൿ�� �Һ�, �䱸 �ü�, �ൿ���� ���� ����, �� �Һ� ��)
				func_�����ڵ�ȭ(force, city, �����ڵ�ȭ_��������[city.get_id()]);
			}
		}

		void �ó������ʱ�ȭ_���ó����ڵ�ȭ_�����ҷ�����()
		{
			for (int i = 0; i < ����_��; i++)
			{
				�����ڵ�ȭ_��������[i] = int(pk::load(KEY, (i + KEY_�ε�����_�߰�_����), 1));
				�������_�漺��[i] = int(pk::load(KEY, (i + KEY_�ε�����_�߰�_�������_�漺��), 90));
				��������_ġ��[i] = int(pk::load(KEY, (i + KEY_�ε�����_�߰�_��������_ġ��), 90));
				�Ʒñ���_��º���[i] = int(pk::load(KEY, (i + KEY_�ε�����_�߰�_�Ʒñ���_��º���), 95));
				¡������_ġ��[i] = int(pk::load(KEY, (i + KEY_�ε�����_�߰�_¡������_ġ��), 95));
				¡������_��[i] = int(pk::load(KEY, (i + KEY_�ε�����_�߰�_¡������_��), 2000));
				¡������_��������[i] = int(pk::load(KEY, (i + KEY_�ε�����_�߰�_¡������_��������), 150));

				// �ε�� �׸� ���� �ε��� ������ ����� ��� �ʱ�ȭ
				if (�����ڵ�ȭ_��������[i] < 1 or �����ڵ�ȭ_��������[i] > 6) �����ڵ�ȭ_��������[i] = 1;
				if (�������_�漺��[i] < 0 or �������_�漺��[i] > 99) �������_�漺��[i] = 90;
				if (��������_ġ��[i] < 0 or ��������_ġ��[i] > 100) ��������_ġ��[i] = 90;
				if (�Ʒñ���_��º���[i] < 0 or �Ʒñ���_��º���[i] > 100) �Ʒñ���_��º���[i] = 95;
				if (¡������_ġ��[i] < 0 or ¡������_ġ��[i] > 100) ¡������_ġ��[i] = 95;
				if (¡������_��[i] < 0 or ¡������_��[i] > 100000) ¡������_��[i] = 2000;
				if (¡������_��������[i] < 0 or ¡������_��������[i] > 1000) ¡������_��������[i] = 150;
			}
			for (int i = 0; i < ����_��; i++)
			{
				����_��뿩��[i] = uint64(pk::load(KEY, (i + KEY_�ε�����_�߰�_����), uint64(0)));
				�Ʒ�_��뿩��[i] = uint64(pk::load(KEY, (i + KEY_�ε�����_�߰�_�Ʒ�), uint64(0)));
				¡��_��뿩��[i] = uint64(pk::load(KEY, (i + KEY_�ε�����_�߰�_¡��), uint64(0)));
				����_��뿩��[i] = uint64(pk::load(KEY, (i + KEY_�ε�����_�߰�_����), uint64(0)));
				����_��뿩��[i] = uint64(pk::load(KEY, (i + KEY_�ε�����_�߰�_����), uint64(0)));
			}
		}

		void ����_���ó����ڵ�ȭ_��������(int file_id)
		{
			for (int i = 0; i < ����_��; i++)
			{
				pk::store(KEY, (i + KEY_�ε�����_�߰�_����), �����ڵ�ȭ_��������[i]);
				pk::store(KEY, (i + KEY_�ε�����_�߰�_�������_�漺��), �������_�漺��[i]);
				pk::store(KEY, (i + KEY_�ε�����_�߰�_��������_ġ��), ��������_ġ��[i]);
				pk::store(KEY, (i + KEY_�ε�����_�߰�_�Ʒñ���_��º���), �Ʒñ���_��º���[i]);
				pk::store(KEY, (i + KEY_�ε�����_�߰�_¡������_ġ��), ¡������_ġ��[i]);
				pk::store(KEY, (i + KEY_�ε�����_�߰�_¡������_��), ¡������_��[i]);
				pk::store(KEY, (i + KEY_�ε�����_�߰�_¡������_��������), ¡������_��������[i]);
			}
			for (int i = 0; i < ����_��; i++)
			{
				pk::store(KEY, (i + KEY_�ε�����_�߰�_����), ����_��뿩��[i]);
				pk::store(KEY, (i + KEY_�ε�����_�߰�_�Ʒ�), �Ʒ�_��뿩��[i]);
				pk::store(KEY, (i + KEY_�ε�����_�߰�_¡��), ¡��_��뿩��[i]);
				pk::store(KEY, (i + KEY_�ε�����_�߰�_����), ����_��뿩��[i]);
				pk::store(KEY, (i + KEY_�ε�����_�߰�_����), ����_��뿩��[i]);
			}
		}

		void �Ͻ���_���ó����ڵ�ȭ_�����ʱ�ȭ(pk::force@ force)
		{
			if (force.is_player())
			{
				int force_id = force.get_id();
				for (int city_id = 0; city_id < ����_��; city_id++)
				{
					pk::city@ city = pk::get_city(city_id);

					// �ش� ������ ���ð� �ƴ� ��� : '����'�� �ʱ�ȭ
					if (city.get_force_id() != force_id)
					{
						// value = false : ��� -> ����
						set(force_id, city_id, false, �����ڵ�ȭ_����);
						set(force_id, city_id, false, �����ڵ�ȭ_�Ʒ�);
						set(force_id, city_id, false, �����ڵ�ȭ_¡��);
						set(force_id, city_id, false, �����ڵ�ȭ_����);
						set(force_id, city_id, false, �����ڵ�ȭ_����);
					}
				}
			}
		}

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		void func_�����ڵ�ȭ_����ǥ��(pk::building@ building, int force_id, int city_id, int �����ڵ�ȭ_����)
		{
			string building_name = pk::decode(pk::get_name(building));

			string title = pk::format("���� �ڵ�ȭ (\x1b[1x{}\x1b[0x)", building_name);

			string order_info = pk::format("(���� ��� : \x1b[1x{}\x1b[0x)", �����ڵ�ȭ_����);

			string inspections_enabled = "�� ���� : " + ((isEnabled(force_id, city_id, �����ڵ�ȭ_����)) ? "\x1b[1x���": "\x1b[1x����");
			string drills_enabled = "�� �Ʒ� : " + ((isEnabled(force_id, city_id, �����ڵ�ȭ_�Ʒ�)) ? "\x1b[1x���": "\x1b[1x����");
			string recruit_enabled = "�� ¡�� : " + ((isEnabled(force_id, city_id, �����ڵ�ȭ_¡��)) ? "\x1b[1x���": "\x1b[1x����");
			string reward_enabled = "�� ���� : " + ((isEnabled(force_id, city_id, �����ڵ�ȭ_����)) ? "\x1b[1x���": "\x1b[1x����");
			string deploy_enabled = "�� ���� : " + ((isEnabled(force_id, city_id, �����ڵ�ȭ_����)) ? "\x1b[1x���": "\x1b[1x����");

			string std_inspections = pk::format("(�������� ġ�� : \x1b[1x{}\x1b[0x)", ��������_ġ��[city_id]);
			string std_drills = pk::format("(�Ʒñ��� ��º��� : \x1b[1x{}\x1b[0x%)", �Ʒñ���_��º���[city_id]);
			string std_recruit_order = pk::format("(¡������ ġ�� : \x1b[1x{}\x1b[0x)", ¡������_ġ��[city_id]);
			string std_recruit_gold = pk::format("(¡������ �� : \x1b[1x{}\x1b[0x)", ¡������_��[city_id]);
			string std_recruit_food = pk::format("(¡������ �������� : \x1b[1x{}\x1b[0x%)", ¡������_��������[city_id]);
			string std_reward = pk::format("(������� �漺�� : \x1b[1x{}\x1b[0x)", �������_�漺��[city_id]);

			array<string> str_�����ڵ�ȭ_����(0);
			if		(�����ڵ�ȭ_���� == 1)	str_�����ڵ�ȭ_���� = {inspections_enabled, drills_enabled, recruit_enabled, reward_enabled, deploy_enabled};
			else if (�����ڵ�ȭ_���� == 2)	str_�����ڵ�ȭ_���� = {inspections_enabled, recruit_enabled, drills_enabled, reward_enabled, deploy_enabled};
			else if (�����ڵ�ȭ_���� == 3)	str_�����ڵ�ȭ_���� = {recruit_enabled, inspections_enabled, drills_enabled, reward_enabled, deploy_enabled};
			else if (�����ڵ�ȭ_���� == 4)	str_�����ڵ�ȭ_���� = {recruit_enabled, drills_enabled, inspections_enabled, reward_enabled, deploy_enabled};
			else if (�����ڵ�ȭ_���� == 5)	str_�����ڵ�ȭ_���� = {drills_enabled, recruit_enabled, inspections_enabled, reward_enabled, deploy_enabled};
			else if (�����ڵ�ȭ_���� == 6)	str_�����ڵ�ȭ_���� = {drills_enabled, inspections_enabled, recruit_enabled, reward_enabled, deploy_enabled};

			array<string> str_��������_����(0);
			if		(�����ڵ�ȭ_���� == 1)	str_��������_���� = {std_inspections, std_drills, std_recruit_order, std_recruit_gold, std_recruit_food, std_reward};
			else if (�����ڵ�ȭ_���� == 2)	str_��������_���� = {std_inspections, std_recruit_order, std_recruit_gold, std_recruit_food, std_drills, std_reward};
			else if (�����ڵ�ȭ_���� == 3)	str_��������_���� = {std_recruit_order, std_recruit_gold, std_recruit_food, std_inspections, std_drills, std_reward};
			else if (�����ڵ�ȭ_���� == 4)	str_��������_���� = {std_recruit_order, std_recruit_gold, std_recruit_food, std_drills, std_inspections, std_reward};
			else if (�����ڵ�ȭ_���� == 5)	str_��������_���� = {std_drills, std_recruit_order, std_recruit_gold, std_recruit_food, std_inspections, std_reward};
			else if (�����ڵ�ȭ_���� == 6)	str_��������_���� = {std_drills, std_inspections, std_recruit_order, std_recruit_gold, std_recruit_food, std_reward};

			int width = int(pk::get_resolution().width) - 230;

			pk::draw_text(pk::encode(title), pk::point(width, 20), 0xffffffff, FONT_BIG, 0xff000000);
			pk::draw_text(pk::encode(order_info), pk::point(width, 55), 0xffffffff, FONT_SMALL, 0xff000000);

			int end = int(str_�����ڵ�ȭ_����.length);
			for (int i = 0; i < end; i++)
			{
				pk::draw_text(pk::encode(str_�����ڵ�ȭ_����[i]), pk::point(width, 75+i*20), 0xffffffff, FONT_SMALL, 0xff000000);
			}
			for (int i = 0; i < int(str_��������_����.length); i++)
			{
				pk::draw_text(pk::encode(str_��������_����[i]), pk::point(width, 75+(i+end)*20), 0xffffffff, FONT_SMALL, 0xff000000);
			}
		}

		void func_�����ڵ�ȭ(pk::force@ force, pk::city@ city, int �����ڵ�ȭ_����)
		{
			if		(�����ڵ�ȭ_���� == 1)	{func_�����ڵ�ȭ_����(force, city);	func_�����ڵ�ȭ_�Ʒ�(force, city);	func_�����ڵ�ȭ_¡��(force, city);}
			else if (�����ڵ�ȭ_���� == 2)	{func_�����ڵ�ȭ_����(force, city);	func_�����ڵ�ȭ_¡��(force, city);	func_�����ڵ�ȭ_�Ʒ�(force, city);}
			else if (�����ڵ�ȭ_���� == 3)	{func_�����ڵ�ȭ_¡��(force, city);	func_�����ڵ�ȭ_����(force, city);	func_�����ڵ�ȭ_�Ʒ�(force, city);}
			else if (�����ڵ�ȭ_���� == 4)	{func_�����ڵ�ȭ_¡��(force, city);	func_�����ڵ�ȭ_�Ʒ�(force, city);	func_�����ڵ�ȭ_����(force, city);}
			else if (�����ڵ�ȭ_���� == 5)	{func_�����ڵ�ȭ_�Ʒ�(force, city);	func_�����ڵ�ȭ_¡��(force, city);	func_�����ڵ�ȭ_����(force, city);}
			else if (�����ڵ�ȭ_���� == 6)	{func_�����ڵ�ȭ_�Ʒ�(force, city);	func_�����ڵ�ȭ_����(force, city);	func_�����ڵ�ȭ_¡��(force, city);}

			func_�����ڵ�ȭ_����(force, city);
			func_�����ڵ�ȭ_����(force, city);
		}

		void func_�����ڵ�ȭ_����(pk::force@ force, pk::city@ city)
		{
			pk::building@ building = pk::city_to_building(city);
			pk::district@ district = pk::get_district(building.get_district_id());
			pk::list<pk::person@> person_list = pk::get_idle_person_list(building);

			string city_name = pk::format("���� \x1b[1x{}\x1b[0x", pk::decode(pk::get_name(city)));

			if (�����) pk::message_box(pk::encode(pk::format("{}�� ���� �������� Ȯ�� ����", city_name)));

			// �⺻ ���� Ȯ��
			if (�����ڵ�ȭ_�ൿ�¼Ҹ�_���� and int(district.ap) < 20)	return;	// �ൿ�� ����
			if (int(person_list.count) == 0)							return;	// �ൿ���� ���� ����
			if (int(city.gold) < 100)									return;	// ���� �� Ȯ��
			if (int(city.public_order) == 100)							return;	// ���� ġ�� Ȯ��

			// ���� ���� Ȯ��
			if (!isEnabled(force.get_id(), city.get_id(), �����ڵ�ȭ_����))	return;	// ���/���� ����
			if (int(city.public_order) > ��������_ġ��[city.get_id()])		return;	// ġ�� ����

			if (�����) pk::message_box(pk::encode(pk::format("{}�� ���� �������� ���", city_name)));

			/// ���� ��� ����
			pk::inspections_cmd_info cmd;

			// ���� ���� ����
			@cmd.base = @building;

			// ���� ���� ����
			person_list.sort(function(a, b){return a.stat[int(pk::core["����.�ɷ�"])] > b.stat[int(pk::core["����.�ɷ�"])];});
			pk::list<pk::person@> actors;
			actors.add(person_list[0]);
			if (int(city.public_order) + func_����ġ������_���(city, building, actors) < 100)
			{
				if (int(person_list.count) > 1)
				{
					actors.add(person_list[1]);

					if (int(city.public_order) + func_����ġ������_���(city, building, actors) < 100)
					{
						if (int(person_list.count) > 2) actors.add(person_list[2]);
					}
				}
			}
			int end = int(actors.count);
			array<string> person_name_list(0);
			for (int i = 0; i < end; i++)
			{
				@cmd.actors[i] = @actors[i];
				person_name_list.insertLast(pk::format("\x1b[1x{}\x1b[0x", pk::decode(pk::get_name(actors[i]))));
			}

			// ���� ��� ����
			if (!�����ڵ�ȭ_�ൿ�¼Ҹ�_����) district.ap += 20;
			bool is_inspections_ended = pk::command(cmd);

			// ���� ���� �޽���
			if (is_inspections_ended)
			{
				string building_name = pk::format("\x1b[1x{}\x1b[0x���� ", pk::decode(pk::get_name(building)));
				string person_names = join(person_name_list, ", ");
				string person_count_info = (end > 1) ? " ��": "";
				string action_info = pk::format(" {}����\n������ ����", end);
				string action_message = building_name + person_names + person_count_info + action_info;

				if (�����ڵ�ȭ_�޽����ڽ�_ǥ��) pk::message_box(pk::encode(action_message));
				else							pk::history_log(building.pos, force.color, pk::encode(action_message));
			}
		}

		// '104 ���� ġ�� ����.cpp' ���� (PK2.1 �⺻ ���� ���� ����)
		int func_����ġ������_���(pk::city@ city, pk::building@ building, pk::list<pk::person@> actors)
		{
			int n = 0;

			for (int i = 0; i < int(actors.count); i++) n = n + actors[i].stat[int(pk::core["����.�ɷ�"])];

			n = n / 28 + 2;

			if (pk::enemies_around(building)) n = n / 2;

			return n;
		}

		void func_�����ڵ�ȭ_�Ʒ�(pk::force@ force, pk::city@ city)
		{
			pk::building@ building = pk::city_to_building(city);
			pk::district@ district = pk::get_district(building.get_district_id());
			pk::list<pk::person@> person_list = pk::get_idle_person_list(building);
			int city_max_energy = (pk::has_tech(city, �ⱳ_���ú�)) ? 120 : 100;

			string city_name = pk::format("���� \x1b[1x{}\x1b[0x", pk::decode(pk::get_name(city)));

			if (�����) pk::message_box(pk::encode(pk::format("{} �Ʒ� �������� Ȯ�� ����", city_name)));

			// �⺻ ���� Ȯ��
			if (�����ڵ�ȭ_�ൿ�¼Ҹ�_���� and int(district.ap) < 20)	return;	// �ൿ�� ����
			if (int(person_list.count) == 0)							return;	// �ൿ���� ���� ����
			if (int(city.energy) == city_max_energy)					return;	// ���� ��� Ȯ��

			// ���� ���� Ȯ��
			if (!isEnabled(force.get_id(), city.get_id(), �����ڵ�ȭ_�Ʒ�))	return;	// ���/���� ����
			if (�����)
			{
				pk::message_box(pk::encode(pk::format("�ִ� ��� ��� ���� ��� ���� : {}", float(city.energy) / float(city_max_energy))));
				pk::message_box(pk::encode(pk::format("�Ʒñ��� ��º��� : {}", float(�Ʒñ���_��º���[city.get_id()]) / 100.0f)));
			}
			if (float(city.energy) / float(city_max_energy) > float(�Ʒñ���_��º���[city.get_id()]) / 100.0f) return;	// ��º��� ����
		
			if (�����) pk::message_box(pk::encode(pk::format("{} �Ʒ� �������� ���", city_name)));

			/// �Ʒ� ��� ����
			pk::drill_cmd_info cmd;

			// �Ʒ� ���� ����
			@cmd.base = @building;

			// �Ʒ� ���� ����
			person_list.sort(function(a, b){return a.stat[int(pk::core["�Ʒ�.�ɷ�"])] > b.stat[int(pk::core["�Ʒ�.�ɷ�"])];});
			pk::list<pk::person@> actors;
			actors.add(person_list[0]);
			if (int(city.energy) + func_�Ʒñ������_���(city, building, actors) < city_max_energy)
			{
				if (int(person_list.count) > 1)
				{
					actors.add(person_list[1]);

					if (int(city.energy) + func_�Ʒñ������_���(city, building, actors) < city_max_energy)
					{
						if (int(person_list.count) > 2) actors.add(person_list[2]);
					}
				}
			}
			int end = int(actors.count);
			array<string> person_name_list(0);
			for (int i = 0; i < end; i++)
			{
				@cmd.actors[i] = @actors[i];
				person_name_list.insertLast(pk::format("\x1b[1x{}\x1b[0x", pk::decode(pk::get_name(actors[i]))));
			}

			// �Ʒ� ��� ����
			if (!�����ڵ�ȭ_�ൿ�¼Ҹ�_����) district.ap += 20;
			bool is_drills_ended = pk::command(cmd);

			// �Ʒ� ���� �޽���
			if (is_drills_ended)
			{
				string building_name = pk::format("\x1b[1x{}\x1b[0x���� ", pk::decode(pk::get_name(building)));
				string person_names = join(person_name_list, ", ");
				string person_count_info = (end > 1) ? " ��": "";
				string action_info = pk::format(" {}����\n�Ʒ��� ����", end);
				string action_message = building_name + person_names + person_count_info + action_info;

				if (�����ڵ�ȭ_�޽����ڽ�_ǥ��)	pk::message_box(pk::encode(action_message));
				else							pk::history_log(building.pos, force.color, pk::encode(action_message));
			}
		}

		// '105 �Ʒ� ��� ����.cpp' ���� (PK2.1 �⺻ ���� ���� ����)
		int func_�Ʒñ������_���(pk::city@ city, pk::building@ building, pk::list<pk::person@> actors)
		{
			int n = 0, max = pk::INT32_MIN;

			for (int i = 0; i < int(actors.count); i++)
			{
				int s = actors[i].stat[int(pk::core["�Ʒ�.�ɷ�"])];
				n += s;
				max = pk::max(max, s);
			}

			n = (n + max) / pk::min(building.get_troops() / 2000 + 20, 100) + 3;

			if (building.facility == �ü�_���� and pk::has_facility(city, �ü�_������)) n = int(n * 1.5f);

			return n;
		}

		void func_�����ڵ�ȭ_¡��(pk::force@ force, pk::city@ city)
		{
			pk::building@ building = pk::city_to_building(city);
			pk::district@ district = pk::get_district(building.get_district_id());
			pk::list<pk::person@> person_list = pk::get_idle_person_list(building);

			string city_name = pk::format("���� \x1b[1x{}\x1b[0x", pk::decode(pk::get_name(city)));

			if (�����) pk::message_box(pk::encode(pk::format("{} ¡�� �������� Ȯ�� ����", city_name)));


			// �⺻ ���� Ȯ��
			if (�����ڵ�ȭ_�ൿ�¼Ҹ�_���� and int(district.ap) < 20)	return;	// �ൿ�� ����
			if (int(person_list.count) == 0)							return;	// �ൿ���� ���� ����
			if (int(city.gold) < 300)									return;	// ���� �� Ȯ��
			if (!pk::has_facility(city, �ü�_����) and !pk::has_facility(city, �ü�_����2��) and !pk::has_facility(city, �ü�_����3��)) return;	// ���� �ü� Ȯ��

			// ���� ���� Ȯ��
			if (!isEnabled(force.get_id(), city.get_id(), �����ڵ�ȭ_¡��))	return;	// ���/���� ����
			if (int(city.public_order) < ¡������_ġ��[city.get_id()])		return;	// ġ�� ����
			if (int(city.gold) < ¡������_��[city.get_id()])				return;	// �� ����
			if (�����)
			{
				pk::message_box(pk::encode(pk::format("���� ���� ��� ���� ���� ���� : {}", float(city.food) / float(city.troops))));
				pk::message_box(pk::encode(pk::format("¡������ �������� : {}", float(¡������_��������[city.get_id()]) / 100.0f)));
			}
			if (float(city.food) / float(city.troops) < float(¡������_��������[city.get_id()]) / 100.0f) return;	// �������� ����

			if (�����) pk::message_box(pk::encode(pk::format("{} ¡�� �������� ���", city_name)));

			/// ¡�� ��� ����
			pk::recruit_cmd_info cmd;

			// ¡�� ���� ����
			@cmd.base = @building;

			// ¡�� ���� ����
			pk::person@ ¡��Ư��_�������� = null;
			int ¡��Ư��_��������_��ȣ = -1;
			int ¡��Ư��_��������_¡���ɷ� = 0;
			for (int i = 0; i < int(person_list.count); i++)
			{
				pk::person@ person_candidate = person_list[i];
				if (!pk::has_skill(person_candidate, int(pk::core["¡��.Ư��"])))							continue;
				if (int(person_candidate.stat[int(pk::core["¡��.�ɷ�"])]) < ¡��Ư��_��������_¡���ɷ�)	continue;

				¡��Ư��_��������_¡���ɷ� = person_candidate.stat[int(pk::core["¡��.�ɷ�"])];
				¡��Ư��_��������_��ȣ = i;
				@¡��Ư��_�������� = @person_candidate;
			}
			pk::list<pk::person@> actors;
			if (¡��Ư��_�������� is null)
			{
				person_list.sort(function(a, b){return a.stat[int(pk::core["¡��.�ɷ�"])] > b.stat[int(pk::core["¡��.�ɷ�"])];});
				actors.add(person_list[0]);
				if (int(city.troops) + func_¡����������_���(city, building, actors) < int(city.max_troops))
				{
					if (int(person_list.count) > 1)
					{
						actors.add(person_list[1]);

						if (int(city.troops) + func_¡����������_���(city, building, actors) < int(city.max_troops))
						{
							if (int(person_list.count) > 2) actors.add(person_list[2]);
						}
					}
				}
			}
			else
			{
				person_list.remove_at(¡��Ư��_��������_��ȣ);
				person_list.sort(function(a, b){return a.stat[int(pk::core["¡��.�ɷ�"])] > b.stat[int(pk::core["¡��.�ɷ�"])];});
				actors.add(¡��Ư��_��������);
				if (int(city.troops) + func_¡����������_���(city, building, actors) < int(city.max_troops))
				{
					if (int(person_list.count) > 1)
					{
						actors.add(person_list[0]);

						if (int(city.troops) + func_¡����������_���(city, building, actors) < int(city.max_troops))
						{
							if (int(person_list.count) > 2) actors.add(person_list[1]);
						}
					}
				}
			}
			int end = int(actors.count);
			array<string> person_name_list(0);
			for (int i = 0; i < end; i++)
			{
				@cmd.actors[i] = @actors[i];
				person_name_list.insertLast(pk::format("\x1b[1x{}\x1b[0x", pk::decode(pk::get_name(actors[i]))));
			}

			// ¡�� ��� ����
			if (!�����ڵ�ȭ_�ൿ�¼Ҹ�_����) district.ap += 20;
			bool is_recruit_ended = pk::command(cmd);

			// ¡�� ���� �޽���
			if (is_recruit_ended)
			{
				string building_name = pk::format("\x1b[1x{}\x1b[0x���� ", pk::decode(pk::get_name(building)));
				string person_names = join(person_name_list, ", ");
				string person_count_info = (end > 1) ? " ��": "";
				string action_info = pk::format(" {}����\n¡���� ����", end);
				string action_message = building_name + person_names + person_count_info + action_info;

				if (�����ڵ�ȭ_�޽����ڽ�_ǥ��)	pk::message_box(pk::encode(action_message));
				else							pk::history_log(building.pos, force.color, pk::encode(action_message));
			}
		}

		// '100 ¡�� ���� ����.cpp' ���� (PK2.1 �⺻ ���� ���� ����)
		int func_¡����������_���(pk::city@ city, pk::building@ building, pk::list<pk::person@> actors)
		{
			int n = 0, sum = 0, mul = 100;

			for (int i = 0; i < int(actors.count); i++)
			{
				sum += actors[i].stat[int(pk::core["¡��.�ɷ�"])];
				if (pk::has_skill(actors[i], int(pk::core["¡��.Ư��"]))) mul = 150;
			}

			n = int((1000 + (int(city.public_order) + 20) * sum * 5 / 100) * mul / 100 * func_5c4600(city));

			if (pk::get_scenario().difficulty == ���̵�_Ư�� and !city.is_player()) n *= 2;

			if (pk::enemies_around(building)) n /= 2;

			return n;
		}

		float func_5c4600(pk::city@ city)
		{
			int level1 = 0, level2 = 0;

			for (int i = 0; i < city.max_devs; i++)
			{
				pk::building@ building = city.dev[i].building;
				if (pk::is_alive(building))
				{
					switch (building.facility)
					{
						case �ü�_����		: building.completed ? level1++	: 0;		break;
						case �ü�_����2��	: building.completed ? level2++	: level1++;	break;
						case �ü�_����3��	: building.completed ? 0		: level2++;	break;
					}
				}
			}

			if (int(city.barracks_counter) > level1 + level2)	return 1.5f;
			if (int(city.barracks_counter) > level1)			return 1.2f;
			return 1.f;
		}

		void func_�����ڵ�ȭ_����(pk::force@ force, pk::city@ city)
		{
			pk::building@ building = pk::city_to_building(city);
			pk::district@ district = pk::get_district(building.get_district_id());

			// ���� ���� Ȯ��
			if (!isEnabled(force.get_id(), city.get_id(), �����ڵ�ȭ_����)) return;	// ���/���� ����

			/// ���� ��� ����
			pk::reward_cmd_info cmd;

			// ���� ���� ����
			@cmd.base = @building;

			// ���� ����
			int recover_ap = 0;
			uint mibun_flags = pk::mibun_flags(�ź�_����, �ź�_�¼�, �ź�_�Ϲ�);
			array<pk::person@> person_list = pk::list_to_array(pk::get_person_list(force, mibun_flags));
			for (int i = 0; i < int(person_list.length); i++)
			{
				pk::person@ person = person_list[i];

				// �⺻ ���� Ȯ��
				if (�����ڵ�ȭ_�ൿ�¼Ҹ�_���� and int(district.ap) < (5 * (1 + int((cmd.actors).count))))	break;	// �ൿ�� ����
				if (city.gold < (100 * (1 + int((cmd.actors).count))))										break;	// ���� �� Ȯ��

				// ���� ���� Ȯ��
				if (int(person.loyalty) > �������_�漺��[city.get_id()]) continue;	// �漺�� ����

				if (!�����ڵ�ȭ_�ൿ�¼Ҹ�_����) recover_ap += 5;

				cmd.actors.add(person);
			}

			// ���� ��� ����
			if (!�����ڵ�ȭ_�ൿ�¼Ҹ�_����) district.ap += recover_ap;
			bool is_reward_ended = pk::command(cmd);

			// ���� ���� �޽���
			if (is_reward_ended)
			{
				int reward_count = int((cmd.actors).count);
				string building_name = pk::decode(pk::get_name(building));
				string action_info = pk::format("\x1b[1x{}\x1b[0x���� \x1b[1x{}\x1b[0x���� ����", building_name, reward_count);

				if (�����ڵ�ȭ_�޽����ڽ�_ǥ��)	pk::message_box(pk::encode(action_info));
				else							pk::history_log(building.pos, force.color, pk::encode(action_info));
			}
		}

		void func_�����ڵ�ȭ_����(pk::force@ force, pk::city@ city)
		{
			pk::building@ building = pk::city_to_building(city);
			pk::district@ district = pk::get_district(building.get_district_id());

			// �⺻ ���� Ȯ��
			if (�����ڵ�ȭ_�ൿ�¼Ҹ�_���� and int(district.ap) < 10)	return;	// �ൿ�� ����
			if (pk::get_idle_person_list(building).count == 0)			return;	// �ൿ���� ���� ����

			// ���� ���� Ȯ��
			if (!isEnabled(force.get_id(), city.get_id(), �����ڵ�ȭ_����)) return;	// ���/���� ����

			// ���� �Ѱ� ���� ���� (�����ϴ� ����)
			if (�����Ѱ輳��_��赵�ñ���)
			{
				if (func_��ó_�����ü�(city, 2) > 0) return;
			}
			else
			{
				if (func_��ó_�����ü�(city, 1) > 0) return;
			}

			// ���� ���� Ȯ��
			for (int i = 0; i < 6; i++)
			{
				pk::city@ neighbor_city = pk::get_city(city.neighbor[i]);
				if (neighbor_city is null)							continue;	// ��� �ִ� ���� ���� ��ȣ�� ��� ����
				if (!pk::is_alive(neighbor_city))					continue;
				if (neighbor_city.get_force_id() != force.get_id()) continue;	// ���� ���ð� �ش� ������ �ƴ� ��� ����

				pk::building@ neighbor_building = pk::city_to_building(neighbor_city);

				// �⺻ ���� Ȯ��
				if (�����ڵ�ȭ_�ൿ�¼Ҹ�_���� and int(district.ap) < 10)	return;	// �ൿ�� ����
				if (pk::get_idle_person_list(building).count == 0)			return;	// �ൿ���� ���� ����

				// ���� ���� (�����ϴ� ����)
				if (city.troops < int(city.max_troops * ���۰�������_��������)) return;

				// ���� ���� (�����ϴ� ����)
				if (city.food < int(city.troops * ���۰�������_��������)) return;

				// ���� �Ѱ� ���� ���� (���۹޴� ����)
				if (�����Ѱ輳��_��赵�ñ���)
				{
					if (func_��ó_�����ü�(neighbor_city, 1) > 0) continue;
				}

				// �÷��̾� ���ӱ��� ���� ���� (���۹޴� ����)
				if (neighbor_building.is_player() and !pk::is_player_controlled(neighbor_building)) continue;

				// ���� ���� (���۹޴� ����)
				if (neighbor_city.troops > int(neighbor_city.max_troops * �����ʿ�����_��������1)) continue;

				// ���� ���� (�����ϴ� ���� vs ���۹޴� ����)
				if (neighbor_city.troops > int(city.troops * �����ʿ�����_��������2)) continue;

				// ��ó �� ���ü� ����  (�����ϴ� ���� vs ���۹޴� ����)
				if (!func_��ó_�����ü�_����_��������(city, neighbor_city)) continue;

				if (!�����ڵ�ȭ_�ൿ�¼Ҹ�_����) district.ap += 10;

				func_���ۺδ�����(building, neighbor_building);
			}
		}

		void func_���ۺδ�����(pk::building@ building, pk::building@ neighbor_building)
		{
			/// ���� ��� ����
			pk::com_deploy_cmd_info cmd;

			// ���� ����
			@cmd.base = @building;

			// ���� �δ� ����
			cmd.type = �δ�����_����;

			// ���� �δ� ����
            pk::list<pk::person@> person_list = pk::get_idle_person_list(building);
			person_list.sort(function(a, b){return a.stat[����ɷ�_��ġ] > b.stat[����ɷ�_��ġ];});
			cmd.member[0] = person_list[0].get_id();

			// ���� �δ� ��
			int ���۷�_��_�ִ�ġ = pk::min(pk::get_gold(building), pk::get_max_gold(neighbor_building) - pk::get_gold(neighbor_building));
			cmd.gold = (pk::get_gold(building) >= 10000) ? pk::min(���۷�_��_�ִ�ġ, (pk::get_gold(building) / 2)) : (pk::get_gold(building) / 4);

			// ���� �δ� ����
			int ���۷�_����_�ִ�ġ = pk::min(pk::get_troops(building), pk::get_max_troops(neighbor_building) - pk::get_troops(neighbor_building));
			���۷�_����_�ִ�ġ = pk::min(60000, ���۷�_����_�ִ�ġ);
			int ���۷�_���� = pk::min(���۷�_����_�ִ�ġ, int(pk::get_troops(building) * ���ۺ��º���));
			cmd.troops = ���۷�_����;

			// ���� �δ� ����
			float ������� = (pk::get_food(building) >= int(pk::get_troops(building) * 2.0f)) ? 3.0f : 1.5f;
			int ���۷�_����_�ִ�ġ = pk::min(pk::get_food(building), pk::get_max_food(neighbor_building) - pk::get_food(neighbor_building));
			cmd.food = (pk::get_food(building) >= 100000) ? pk::max((pk::get_food(building) / 2), pk::min(���۷�_����_�ִ�ġ, int(���۷�_���� * �������))) : (pk::get_food(building) / 2);

            // ���� �δ� ����(���۷�)
			// ���� : 0��, 1â, 2��, 3��, 4����, 5����, 6����, 7����, 8���, 9�ְ�, 10����, 11����
			array<int> ���۷�_����(12, 0);
            for (int i = 0; i < ����_��; i++)
			{
				int ���۷�_����_�ִ�ġ = pk::get_max_weapon_amount(neighbor_building, i) - pk::get_weapon_amount(neighbor_building, i);
				���۷�_����[i] = pk::min(���۷�_����_�ִ�ġ, pk::get_weapon_amount(building, i) / 2);
				cmd.weapon_id[i] = i;
				cmd.weapon_amount[i] = ���۷�_����[i];
			}

			// ���� �δ� �ӹ�
			cmd.order = �δ��ӹ�_�̵�;

			// ���� �δ� ��ǥ ��ǥ
			cmd.target_pos = neighbor_building.pos;

			// ���� ��� ����
			int unit_id = pk::command(cmd);

			// ���� ���� �޽���
			if (unit_id != -1)
			{
				pk::unit@ unit = pk::get_unit(unit_id);
				string unit_name = pk::format("\x1b[1x{}\x1b[0x", pk::decode(pk::get_name(unit)));
				string building_name = pk::format("\x1b[1x{}\x1b[0x", pk::decode(pk::get_name(building)));
				string neighbor_building_name = pk::format("\x1b[1x{}\x1b[0x", pk::decode(pk::get_name(neighbor_building)));
				string action_message = pk::format("{}�� {}�� ������ ���� {}���� ����", unit_name, neighbor_building_name, building_name);
				pk::force@ force = pk::get_force(building.get_force_id());

				if (�����ڵ�ȭ_�޽����ڽ�_ǥ��)	pk::message_box(pk::encode(action_message));
				else							pk::history_log(building.pos, force.color, pk::encode(action_message));

				// ���� �δ� �ൿ �Ϸ�
				unit.action_done = true;
			}
		}

		bool func_��ó_�����ü�_����_��������(pk::city@ city, pk::city@ neighbor_city)
		{
			if		(func_��ó_�����ü�(city, 1) < func_��ó_�����ü�(neighbor_city, 1)) return true;
			else if (func_��ó_�����ü�(city, 1) > func_��ó_�����ü�(neighbor_city, 1)) return false;
			else
			{
				if		(func_��ó_�����ü�(city, 2) < func_��ó_�����ü�(neighbor_city, 2)) return true;
				else if (func_��ó_�����ü�(city, 2) > func_��ó_�����ü�(neighbor_city, 2)) return false;
				else
				{
					if		(func_��ó_�����ü�(city, 3) < func_��ó_�����ü�(neighbor_city, 3)) return true;
					else if (func_��ó_�����ü�(city, 3) > func_��ó_�����ü�(neighbor_city, 3)) return false;
					else
					{
						if		(func_��ó_�����ü�(city, 4) < func_��ó_�����ü�(neighbor_city, 4)) return true;
						else if (func_��ó_�����ü�(city, 4) > func_��ó_�����ü�(neighbor_city, 4)) return false;
						else
						{
							if		(func_��ó_�����ü�(city, 5) < func_��ó_�����ü�(neighbor_city, 5)) return true;
							else if (func_��ó_�����ü�(city, 5) > func_��ó_�����ü�(neighbor_city, 5)) return false;
							else
							{
								if		(func_��ó_�����ü�(city, 6) < func_��ó_�����ü�(neighbor_city, 6)) return true;
								else if (func_��ó_�����ü�(city, 6) > func_��ó_�����ü�(neighbor_city, 6)) return false;
								else
								{
									if		(func_��ó_�����ü�(city, 7) < func_��ó_�����ü�(neighbor_city, 7)) return true;
									else if (func_��ó_�����ü�(city, 7) > func_��ó_�����ü�(neighbor_city, 7)) return false;
									else
									{
										if (func_��ó_�����ü�(city, 8) < func_��ó_�����ü�(neighbor_city, 8)) return true;
										else																	return false;
									}
								}
							}
						}
					}
				}
			}
		}

		int func_��ó_�����ü�(pk::city@ city, int ���ðŸ�)
		{
			int enemy_city_count = 0;

			array<pk::city@> cities = pk::list_to_array(pk::get_city_list());
			for (int i = 0; i < int(cities.length); i++)
			{
				pk::city@ neighbor_city = cities[i];

				// ���� �� ������ �̵� �ҿ��ϼ� ����
				int distance = pk::get_city_distance(city.get_id(), neighbor_city.get_id());

				if (distance > ���ðŸ�)				continue;
				if (!pk::is_enemy(city, neighbor_city))	continue;

				enemy_city_count++;
			}

			return enemy_city_count;
		}

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		int menu_city_id_;	// �ǹ� �޴� ����
		int menu_force_id_;	// �ǹ� �޴� ����
		pk::building@ building_;

		void init(pk::building@ building)
		{
			@building_ = @building;
			pk::city@ city = pk::building_to_city(building);

			menu_city_id_ = (city !is null) ? city.get_id() : -1;
			menu_force_id_ = building.get_force_id();
		}

		bool isVisible()
		{
			if (building_.get_id() >= ����_��) return false;
			if (!pk::is_player_controlled(pk::get_city(menu_city_id_))) return false;	// �÷��̾� ���ӱ��� ������ ��� ����

			return menu_city_id_ != -1 and menu_force_id_ == pk::get_current_turn_force_id();
		}

		string getText_�ϰ�����_����()
		{
			return pk::encode("�ϰ� ����    ");
		}
		string getDesc_�ϰ�����_����()
		{
			return pk::encode("��ü ���� �� ������ ������ ���� ���� ��带 �ϰ������� �����մϴ�.");
		}
		bool handler_�ϰ�����_����()
		{
			func_�ϰ�����_����(); return true;
		}
		void func_�ϰ�����_����()
		{
			pk::district@ district = pk::get_district(pk::get_district_id(pk::get_force(menu_force_id_), 1));
			array<pk::building@> selected_cities_arr;
			pk::list<pk::city@> city_list = pk::get_city_list(district);
			string desc_���� = pk::encode("���� �ڵ�ȭ ���� ��带 ������ ���ø� �����Ͻʽÿ�.");
			selected_cities_arr = pk::list_to_array(pk::city_selector(pk::encode("���� ����"), desc_����, city_list, 1, int(city_list.count)));
			if (int(selected_cities_arr.length) == 0) return;
			array<string> str_order = {"��� 1 : ���� - �Ʒ� - ¡�� - ���� - ����", "��� 2 : ���� - ¡�� - �Ʒ� - ���� - ����", "��� 3 : ¡�� - ���� - �Ʒ� - ���� - ����", "��� 4 : ¡�� - �Ʒ� - ���� - ���� - ����", "��� 5 : �Ʒ� - ¡�� - ���� - ���� - ����", "��� 6 : �Ʒ� - ���� - ¡�� - ���� - ����"};
			pk::message_box(pk::encode(str_order[0] + "\n" + str_order[1] + "\n" + str_order[2] + "\n" + str_order[3] + "\n" + str_order[4] + "\n" + str_order[5]));
			pk::int_bool set_order = pk::numberpad(pk::encode("�������"), 1, 6, 1, pk::numberpad_t(numberpad_t));
			array<string> city_name_list(0);
			for (int i = 0; i < int(selected_cities_arr.length); i++)
			{
			//	pk::city@ city = pk::building_to_city(selected_cities_arr[i]);	// pk::building_to_city �Լ� �������� ����
				pk::city@ city = pk::get_city(selected_cities_arr[i].get_id());
				city_name_list.insertLast(pk::format("\x1b[1x{}\x1b[0x", pk::decode(pk::get_name(city))));
				if (set_order.second) �����ڵ�ȭ_��������[city.get_id()] = set_order.first;
			}
			string city_names = join(city_name_list, ", ");
			string city_count_info = (int(selected_cities_arr.length) > 1) ? " ��": "";
			pk::message_box(pk::encode(pk::format("{}{} {}�� ������ ���� �ڵ�ȭ ���� ��带 ����\n{}", city_names, city_count_info, int(selected_cities_arr.length), str_order[int(set_order.first) - 1])));
		}

		string getText_����()
		{
			switch(�����ڵ�ȭ_��������[menu_city_id_])
			{
				case 1	: return pk::encode("���� ��� : 1");
				case 2	: return pk::encode("���� ��� : 2");
				case 3	: return pk::encode("���� ��� : 3");
				case 4	: return pk::encode("���� ��� : 4");
				case 5	: return pk::encode("���� ��� : 5");
				case 6	: return pk::encode("���� ��� : 6");
			}

			return pk::encode("");
		}

		string getDesc_����()
		{
			switch(�����ڵ�ȭ_��������[menu_city_id_])
			{
				case 1	: return pk::encode("���� : ���� - �Ʒ� - ¡�� - ���� - ����");
				case 2	: return pk::encode("���� : ���� - ¡�� - �Ʒ� - ���� - ����");
				case 3	: return pk::encode("���� : ¡�� - ���� - �Ʒ� - ���� - ����");
				case 4	: return pk::encode("���� : ¡�� - �Ʒ� - ���� - ���� - ����");
				case 5	: return pk::encode("���� : �Ʒ� - ¡�� - ���� - ���� - ����");
				case 6	: return pk::encode("���� : �Ʒ� - ���� - ¡�� - ���� - ����");
			}

			return pk::encode("");
		}

		bool handler_����()
		{
			if		(�����ڵ�ȭ_��������[menu_city_id_] == 1)	�����ڵ�ȭ_��������[menu_city_id_] = 2;
			else if (�����ڵ�ȭ_��������[menu_city_id_] == 2)	�����ڵ�ȭ_��������[menu_city_id_] = 3;
			else if (�����ڵ�ȭ_��������[menu_city_id_] == 3)	�����ڵ�ȭ_��������[menu_city_id_] = 4;
			else if (�����ڵ�ȭ_��������[menu_city_id_] == 4)	�����ڵ�ȭ_��������[menu_city_id_] = 5;
			else if (�����ڵ�ȭ_��������[menu_city_id_] == 5)	�����ڵ�ȭ_��������[menu_city_id_] = 6;
			else if (�����ڵ�ȭ_��������[menu_city_id_] == 6)	�����ڵ�ȭ_��������[menu_city_id_] = 1;
			else												�����ڵ�ȭ_��������[menu_city_id_] = 1;

			if (menu_force_id_ == pk::get_current_turn_force_id())
			{
				string city_name = pk::decode(pk::get_name(pk::city_to_building(pk::get_city(menu_city_id_))));
				string toggle_msg = pk::encode(pk::format("\x1b[1x{}\x1b[0x���� ���� �ڵ�ȭ ���� ����(��� \x1b[1x{}\x1b[0x)\n", city_name, �����ڵ�ȭ_��������[menu_city_id_]));
				string order_info = getDesc_����();
				pk::message_box(toggle_msg + order_info);
			}

			return true;
		}

		//MUSSO
		string getText_�ϰ�����_��뿩��_����ȭ()
		{
			return pk::encode("��ü �ϰ�����");
		}

		string getText_�ϰ�����_��뿩��()
		{
			return pk::encode("���� �ϰ�����");
		}
		string getDesc_�ϰ�����_��뿩��_����ȭ()
		{
			return pk::encode("������ ���µ��ÿ��� ����, �Ʒ�, ������ �ڵ����� ��� ���θ� �����մϴ�.");
		}		
		string getDesc_�ϰ�����_��뿩��()
		{
			return pk::encode("������ ���µ��ÿ��� �׸� �ڵ����� ��� ���θ� �����մϴ�.");
		}
		
		//MUSSO
		bool handler_�ϰ�����_��뿩��_����ȭ()
		{
			func_�ϰ�����_��뿩��_����ȭ(); return true;
		}
		void func_�ϰ�����_��뿩��_����ȭ()
		{
			pk::district@ district = pk::get_district(pk::get_district_id(pk::get_force(menu_force_id_), 1));
			array<pk::building@> selected_cities_arr;
			pk::list<pk::city@> city_list = pk::get_city_list(district);
			// array<string> answers_�׸�_arr = {pk::encode("����"), pk::encode("�Ʒ�"), pk::encode("¡��"), pk::encode("����"), pk::encode("����"), pk::encode("���")};
			array<string> answers_������_arr = {pk::encode("�ϰ� ���"), pk::encode("�ϰ� ����"), pk::encode("�ڷ�")};
			array<string> desc_������_arr = {"���", "����"};
			string desc_������ = "";
			// int n = pk::choose(pk::encode("�ϰ������� ������ �׸��� �����Ͻʽÿ�."), answers_�׸�_arr);
			for (int i = 0; i < 5; i++)
			{
				// if (n != i) continue;

				int m = pk::choose(pk::encode("������ ������ ����, �Ʒ�, ������ �ڵ������� ���/�����մϴ�."), answers_������_arr);
				for (int j = 0; j < 2; j++)
				{
					if (m != j) continue;

					// desc_������ = pk::format("{}�� {}�� ���ø� �����Ͻʽÿ�.", pk::decode(answers_�׸�_arr[n]), desc_������_arr[m]);
					selected_cities_arr = pk::list_to_array(pk::city_selector(pk::encode("���� ����"), pk::encode(desc_������), city_list, 1, int(city_list.count)));
					if (int(selected_cities_arr.length) == 0) return;
					array<string> city_name_list(0);
					for (int k = 0; k < int(selected_cities_arr.length); k++)
					{
						// pk::city@ city = pk::building_to_city(selected_cities_arr[k]);	// pk::building_to_city �Լ� �������� ����
						pk::city@ city = pk::get_city(selected_cities_arr[k].get_id());
						city_name_list.insertLast(pk::format("\x1b[1x{}\x1b[0x", pk::decode(pk::get_name(city))));
						bool ���������� = (m == 0) ? true : false;
						set(menu_force_id_, city.get_id(), ����������, 0);	//����
						set(menu_force_id_, city.get_id(), ����������, 1);	//�Ʒ�
						// set(menu_force_id_, city.get_id(), ����������, 2);	//¡��
						set(menu_force_id_, city.get_id(), ����������, 3);	//����
					}
					string city_names = join(city_name_list, ", ");
					string city_count_info = (int(selected_cities_arr.length) > 1) ? " ��": "";
					pk::message_box(pk::encode(pk::format("{}{} {}�� ������ ������ \x1b[1x{}\x1b[0x", city_names, city_count_info, int(selected_cities_arr.length), desc_������_arr[m])));
					return;
					
				}
				if (m == 2) return;
			}
			// if (n == 5) return;
			
		}
		
		
		
		bool handler_�ϰ�����_��뿩��()
		{
			func_�ϰ�����_��뿩��(); return true;
		}
		void func_�ϰ�����_��뿩��()
		{
			pk::district@ district = pk::get_district(pk::get_district_id(pk::get_force(menu_force_id_), 1));
			array<pk::building@> selected_cities_arr;
			pk::list<pk::city@> city_list = pk::get_city_list(district);
			array<string> answers_�׸�_arr = {pk::encode("����"), pk::encode("�Ʒ�"), pk::encode("¡��"), pk::encode("����"), pk::encode("����"), pk::encode("���")};
			array<string> answers_������_arr = {pk::encode("�ϰ� ���"), pk::encode("�ϰ� ����"), pk::encode("�ڷ�")};
			array<string> desc_������_arr = {"���", "����"};
			string desc_������ = "";
			int n = pk::choose(pk::encode("�ϰ������� ������ �׸��� �����Ͻʽÿ�."), answers_�׸�_arr);
			for (int i = 0; i < 5; i++)
			{
				if (n != i) continue;

				int m = pk::choose(pk::encode("���/���� ���θ� �����Ͻʽÿ�."), answers_������_arr);
				for (int j = 0; j < 2; j++)
				{
					if (m != j) continue;

					desc_������ = pk::format("{}�� {}�� ���ø� �����Ͻʽÿ�.", pk::decode(answers_�׸�_arr[n]), desc_������_arr[m]);
					selected_cities_arr = pk::list_to_array(pk::city_selector(pk::encode("���� ����"), pk::encode(desc_������), city_list, 1, int(city_list.count)));
					if (int(selected_cities_arr.length) == 0) return;
					array<string> city_name_list(0);
					for (int k = 0; k < int(selected_cities_arr.length); k++)
					{
					//	pk::city@ city = pk::building_to_city(selected_cities_arr[k]);	// pk::building_to_city �Լ� �������� ����
						pk::city@ city = pk::get_city(selected_cities_arr[k].get_id());
						city_name_list.insertLast(pk::format("\x1b[1x{}\x1b[0x", pk::decode(pk::get_name(city))));
						bool ���������� = (m == 0) ? true : false;
						set(menu_force_id_, city.get_id(), ����������, n);	// true : ���� -> ���, false : ��� -> ����
					}
					string city_names = join(city_name_list, ", ");
					string city_count_info = (int(selected_cities_arr.length) > 1) ? " ��": "";
					pk::message_box(pk::encode(pk::format("{}{} {}�� ������ \x1b[1x{}\x1b[0x�� \x1b[1x{}\x1b[0x", city_names, city_count_info, int(selected_cities_arr.length), pk::decode(answers_�׸�_arr[n]), desc_������_arr[m])));
				}
				if (m == 2)	func_�ϰ�����_��뿩��();
			}
			if (n == 5) return;
		}

		string getText_����()
		{
			return isEnabled(menu_force_id_, menu_city_id_, �����ڵ�ȭ_����) ? pk::encode("���� ���") : pk::encode("���� ����");
		}
		string getDesc_����()
		{
			return isEnabled(menu_force_id_, menu_city_id_, �����ڵ�ȭ_����) ? pk::encode("������ ���� �����Դϴ�.") : pk::encode("������ ������ �����Դϴ�.");
		}
		bool handler_����()
		{
			toggle(menu_force_id_, menu_city_id_, �����ڵ�ȭ_����);	return true;
		}

		string getText_�Ʒ�()
		{
			return isEnabled(menu_force_id_, menu_city_id_, �����ڵ�ȭ_�Ʒ�) ? pk::encode("�Ʒ� ���") : pk::encode("�Ʒ� ����");
		}
		string getDesc_�Ʒ�()
		{
			return isEnabled(menu_force_id_, menu_city_id_, �����ڵ�ȭ_�Ʒ�) ? pk::encode("�Ʒ��� ���� �����Դϴ�.") : pk::encode("�Ʒ��� ������ �����Դϴ�.");
		}
		bool handler_�Ʒ�()
		{
			toggle(menu_force_id_, menu_city_id_, �����ڵ�ȭ_�Ʒ�);	return true;
		}

		string getText_¡��()
		{
			return isEnabled(menu_force_id_, menu_city_id_, �����ڵ�ȭ_¡��) ? pk::encode("¡�� ���") : pk::encode("¡�� ����");
		}
		string getDesc_¡��()
		{
			return isEnabled(menu_force_id_, menu_city_id_, �����ڵ�ȭ_¡��) ? pk::encode("¡���� ���� �����Դϴ�.") : pk::encode("¡���� ������ �����Դϴ�.");
		}
		bool handler_¡��()
		{
			toggle(menu_force_id_, menu_city_id_, �����ڵ�ȭ_¡��);	return true;
		}

		string getText_����()
		{
			return isEnabled(menu_force_id_, menu_city_id_, �����ڵ�ȭ_����) ? pk::encode("���� ���") : pk::encode("���� ����");
		}
		string getDesc_����()
		{
			return isEnabled(menu_force_id_, menu_city_id_, �����ڵ�ȭ_����) ? pk::encode("������ ���� �����Դϴ�.") : pk::encode("������ ������ �����Դϴ�.");
		}
		bool handler_����()
		{
			toggle(menu_force_id_, menu_city_id_, �����ڵ�ȭ_����);	return true;
		}

		string getText_����()
		{
			return isEnabled(menu_force_id_, menu_city_id_, �����ڵ�ȭ_����) ? pk::encode("���� ���") : pk::encode("���� ����");
		}
		string getDesc_����()
		{
			return isEnabled(menu_force_id_, menu_city_id_, �����ڵ�ȭ_����) ? pk::encode("������ ���� �����Դϴ�.") : pk::encode("������ ������ �����Դϴ�.");
		}
		bool handler_����()
		{
			toggle(menu_force_id_, menu_city_id_, �����ڵ�ȭ_����);	return true;
		}

		string getText_�ϰ�����_����()
		{
			return pk::encode("�ϰ� ����        ");
		}
		string getDesc_�ϰ�����_����()
		{
			return pk::encode("��ü ���� �� ������ ������ ���� ��������� �ϰ������� �����մϴ�.");
		}
		bool handler_�ϰ�����_����()
		{
			func_�ϰ�����_����(); return true;
		}
		void func_�ϰ�����_����()
		{
			pk::district@ district = pk::get_district(pk::get_district_id(pk::get_force(menu_force_id_), 1));
			array<pk::building@> selected_cities_arr;
			pk::list<pk::city@> city_list = pk::get_city_list(district);
			array<string> answers_�׸�_arr = {pk::encode("�������� ġ��"), pk::encode("�Ʒñ��� ��º���"), pk::encode("¡������ ġ��"), pk::encode("¡������ ��"), pk::encode("¡������ ��������"), pk::encode("������� �漺��")};
			string desc_���� = "";
			int n = pk::choose(pk::encode("�ϰ������� ������ �׸��� �����Ͻʽÿ�."), answers_�׸�_arr);	// @items ������ �ִ� 6��
			for (int i = 0; i < 6; i++)
			{
				if (n != i) continue;

				desc_���� = pk::format("������ ������ ���ø� �����Ͻʽÿ�. ({})", pk::decode(answers_�׸�_arr[n]));
				selected_cities_arr = pk::list_to_array(pk::city_selector(pk::encode("���� ����"), pk::encode(desc_����), city_list, 1, int(city_list.count)));
				if (int(selected_cities_arr.length) == 0) return;

				array<int> max_num = {99, 99, 100, 100000, 1000, 99};
				array<int> def_num = {90, 95, 95, 2000, 150, 90};
				pk::int_bool set_standard = pk::numberpad(pk::encode("��������"), 0, max_num[n], def_num[n], pk::numberpad_t(numberpad_t));
				if (set_standard.second)
				{
					array<string> city_name_list(0);
					for (int k = 0; k < int(selected_cities_arr.length); k++)
					{
					//	pk::city@ city = pk::building_to_city(selected_cities_arr[k]);	// pk::building_to_city �Լ� �������� ����
						pk::city@ city = pk::get_city(selected_cities_arr[k].get_id());
						city_name_list.insertLast(pk::format("\x1b[1x{}\x1b[0x", pk::decode(pk::get_name(city))));

						if		(n == 0) ��������_ġ��[city.get_id()] = set_standard.first;
						else if (n == 1) �Ʒñ���_��º���[city.get_id()] = set_standard.first;
						else if (n == 2) ¡������_ġ��[city.get_id()] = set_standard.first;
						else if (n == 3) ¡������_��[city.get_id()] = set_standard.first;
						else if (n == 4) ¡������_��������[city.get_id()] = set_standard.first;
						else if (n == 5) �������_�漺��[city.get_id()] = set_standard.first;
					}
					string city_names = join(city_name_list, ", ");
					string city_count_info_1 = (int(selected_cities_arr.length) > 1) ? " ��": "";
					string city_count_info_2 = (int(selected_cities_arr.length) > 1) ? "�ϰ� ": "";
					pk::message_box(pk::encode(pk::format("{}{} {}�� ������ \x1b[1x{}\x1b[0x {}���� (\x1b[1x{}\x1b[0x)", city_names, city_count_info_1, int(selected_cities_arr.length), pk::decode(answers_�׸�_arr[n]), city_count_info_2, set_standard.first)));
				}
			}
		}

		string getText_��������_ġ��()
		{
			return pk::encode("�������� ġ��    ");
		}
		string getDesc_��������_ġ��()
		{
			return pk::encode(pk::format("������ ġ���� {} ������ ��� �����մϴ�.", ��������_ġ��[menu_city_id_]));
		}
		bool handler_��������_ġ��()
		{
			// �������� ġ�� ����
			pk::int_bool set_public_order = pk::numberpad(pk::encode("��������"), 0, 99, ��������_ġ��[menu_city_id_], pk::numberpad_t(numberpad_t));

			if (set_public_order.second) ��������_ġ��[menu_city_id_] = set_public_order.first;

			return true;
		}

		string getText_�Ʒñ���_��º���()
		{
			return pk::encode("�Ʒñ��� ��º���");
		}
		string getDesc_�Ʒñ���_��º���()
		{
			return pk::encode(pk::format("������ �ִ� ��� ��� ���� ����� {}% ������ ��� �����մϴ�.", �Ʒñ���_��º���[menu_city_id_]));
		}
		bool handler_�Ʒñ���_��º���()
		{
			// �Ʒñ��� ��º��� ����
			pk::int_bool set_drills = pk::numberpad(pk::encode("��������"), 0, 99, �Ʒñ���_��º���[menu_city_id_], pk::numberpad_t(numberpad_t));

			if (set_drills.second) �Ʒñ���_��º���[menu_city_id_] = set_drills.first;

			return true;
		}

		string getText_¡������_ġ��()
		{
			return pk::encode("¡������ ġ��    ");
		}
		string getDesc_¡������_ġ��()
		{
			return pk::encode(pk::format("������ ġ���� {} �̻��� ��� ¡���մϴ�.", ¡������_ġ��[menu_city_id_]));
		}
		bool handler_¡������_ġ��()
		{
			// ¡������ ġ�� ����
			pk::int_bool set_recruit_order = pk::numberpad(pk::encode("��������"), 0, 100, ¡������_ġ��[menu_city_id_], pk::numberpad_t(numberpad_t));

			if (set_recruit_order.second) ¡������_ġ��[menu_city_id_] = set_recruit_order.first;

			return true;
		}

		string getText_¡������_��()
		{
			return pk::encode("¡������ ��      ");
		}
		string getDesc_¡������_��()
		{
			return pk::encode(pk::format("������ ���� {} �̻��� ��� ¡���մϴ�.", ¡������_��[menu_city_id_]));
		}
		bool handler_¡������_��()
		{
			// ¡������ �� ����
			pk::int_bool set_recruit_gold = pk::numberpad(pk::encode("��������"), 0, 100000, ¡������_��[menu_city_id_], pk::numberpad_t(numberpad_t));

			if (set_recruit_gold.second) ¡������_��[menu_city_id_] = set_recruit_gold.first;

			return true;
		}

		string getText_¡������_��������()
		{
			return pk::encode("¡������ ��������");
		}
		string getDesc_¡������_��������()
		{
			return pk::encode(pk::format("������ ���� ���� ��� ���� ���� ������ {}% �̻��� ��� ¡���մϴ�.", ¡������_��������[menu_city_id_]));
		}
		bool handler_¡������_��������()
		{
			// ¡������ �������� ����
			pk::int_bool set_recruit_food = pk::numberpad(pk::encode("��������"), 0, 1000, ¡������_��������[menu_city_id_], pk::numberpad_t(numberpad_t));

			if (set_recruit_food.second) ¡������_��������[menu_city_id_] = set_recruit_food.first;

			return true;
		}

		string getText_�������_�漺��()
		{
			return pk::encode("������� �漺��  ");
		}
		string getDesc_�������_�漺��()
		{
			return pk::encode(pk::format("������ �漺���� {} ������ ��� �����մϴ�.", �������_�漺��[menu_city_id_]));
		}
		bool handler_�������_�漺��()
		{
			// ������� �漺�� ����
			pk::int_bool set_loyaty = pk::numberpad(pk::encode("��������"), 0, 99, �������_�漺��[menu_city_id_], pk::numberpad_t(numberpad_t));

			if (set_loyaty.second) �������_�漺��[menu_city_id_] = set_loyaty.first;

			return true;
		}

		string numberpad_t(int line, int original_value, int current_value)
		{
			return pk::encode("");
		}

		bool isEnabled(int force_id, int city_id, int �����ڵ�ȭ_�׸�)
		{
			if		(�����ڵ�ȭ_�׸� == �����ڵ�ȭ_����) return (����_��뿩��[force_id] & (uint64(1) << city_id)) != 0;
			else if (�����ڵ�ȭ_�׸� == �����ڵ�ȭ_�Ʒ�) return (�Ʒ�_��뿩��[force_id] & (uint64(1) << city_id)) != 0;
			else if (�����ڵ�ȭ_�׸� == �����ڵ�ȭ_¡��) return (¡��_��뿩��[force_id] & (uint64(1) << city_id)) != 0;
			else if (�����ڵ�ȭ_�׸� == �����ڵ�ȭ_����) return (����_��뿩��[force_id] & (uint64(1) << city_id)) != 0;
			else if (�����ڵ�ȭ_�׸� == �����ڵ�ȭ_����) return (����_��뿩��[force_id] & (uint64(1) << city_id)) != 0;

			return false;
		}

		void toggle(int force_id, int city_id, int �����ڵ�ȭ_�׸�)
		{
			bool ��뿩�� = false;
			string �׸��̸� = "";
			array<string> �׸��̸�_��� = {"\x1b[1x����\x1b[0x", "\x1b[1x�Ʒ�\x1b[0x", "\x1b[1x¡��\x1b[0x", "\x1b[1x����\x1b[0x", "\x1b[1x����\x1b[0x"};
			for (int i = 0; i < 5; i++)
			{
				if (�����ڵ�ȭ_�׸� == i)
				{
					��뿩�� = isEnabled(force_id, city_id, i);
					�׸��̸� = �׸��̸�_���[i];
				}
			}
			string str_��뿩�� = (!��뿩��) ? "\x1b[1x���\x1b[0x" : "\x1b[1x����\x1b[0x";	// bool���� �ٲ� �����̹Ƿ� �ݴ�� ����

			if (��뿩��)	set(force_id, city_id, false, �����ڵ�ȭ_�׸�);	// value = false : ��� -> ����
			else			set(force_id, city_id, true, �����ڵ�ȭ_�׸�);	// value = true : ���� -> ���

			if (force_id == pk::get_current_turn_force_id())
			{
				string city_name = pk::decode(pk::get_name(pk::city_to_building(pk::get_city(city_id))));
				string toggle_msg = pk::format("\x1b[1x{}\x1b[0x���� {} ���� �ڵ�ȭ�� {}", city_name, �׸��̸�, str_��뿩��);
				pk::message_box(pk::encode(toggle_msg));
			}
		}

		void set(int force_id, int city_id, bool value, int �����ڵ�ȭ_�׸�)
		{
			if (value)
			{
				// value = true : ���� -> ���
				if		(�����ڵ�ȭ_�׸� == �����ڵ�ȭ_����) ����_��뿩��[force_id] = ����_��뿩��[force_id] | uint64(1) << city_id;
				else if (�����ڵ�ȭ_�׸� == �����ڵ�ȭ_�Ʒ�) �Ʒ�_��뿩��[force_id] = �Ʒ�_��뿩��[force_id] | uint64(1) << city_id;
				else if (�����ڵ�ȭ_�׸� == �����ڵ�ȭ_¡��) ¡��_��뿩��[force_id] = ¡��_��뿩��[force_id] | uint64(1) << city_id;
				else if (�����ڵ�ȭ_�׸� == �����ڵ�ȭ_����) ����_��뿩��[force_id] = ����_��뿩��[force_id] | uint64(1) << city_id;
				else if (�����ڵ�ȭ_�׸� == �����ڵ�ȭ_����) ����_��뿩��[force_id] = ����_��뿩��[force_id] | uint64(1) << city_id;
			}
			else
			{
				// value = false : ��� -> ����
				if		(�����ڵ�ȭ_�׸� == �����ڵ�ȭ_����) ����_��뿩��[force_id] = ����_��뿩��[force_id] & ~(uint64(1) << city_id);
				else if (�����ڵ�ȭ_�׸� == �����ڵ�ȭ_�Ʒ�) �Ʒ�_��뿩��[force_id] = �Ʒ�_��뿩��[force_id] & ~(uint64(1) << city_id);
				else if (�����ڵ�ȭ_�׸� == �����ڵ�ȭ_¡��) ¡��_��뿩��[force_id] = ¡��_��뿩��[force_id] & ~(uint64(1) << city_id);
				else if (�����ڵ�ȭ_�׸� == �����ڵ�ȭ_����) ����_��뿩��[force_id] = ����_��뿩��[force_id] & ~(uint64(1) << city_id);
				else if (�����ڵ�ȭ_�׸� == �����ڵ�ȭ_����) ����_��뿩��[force_id] = ����_��뿩��[force_id] & ~(uint64(1) << city_id);
			}
		}

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	}

	Main main;
}