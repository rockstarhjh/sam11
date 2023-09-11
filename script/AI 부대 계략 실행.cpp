/*
	@���� : masterpiecek
	@���� : AI�δ밡 ��ó�� ���������� �����ϴ� ���δ� ���� �� �ش�δ븦 ���� �跫 ���� �� ������ �����մϴ�.


	[ AI�δ� �跫���� ]

	1. �跫 ����δ밡 �跫�� �����ϱ� ���� �����ؾ��� ���ǵ� (��ȣ ���� ������ ���� �⺻��)
	 1) ����δ�κ��� ���ذŸ�(8ĭ) �̳��� ���δ� ����
	 2) ����δ��� �δ����� ���ذ�(30) �̻�
	 3) ����δ��� Ư�� �δ�ɷ��� ���ذ�(70) �̸�
	 4) ����δ��� �δ������� ���ذ�(����A) �̸�
	 5) ����δ밡 ���⺰�� Ư�� Ư�⸦ �̺��� (�������� ����)

	2. �跫 ����δ밡 �跫�� �� ���δ� �˻�
	 1) �跫 ���δ��� ���� Ȯ�� (��ȣ ���� ������ ���� �⺻��)
	  (1) ���δ��� �δ뺴���� ���ذ�(1500) �̻�
	  (2) ���δ��� �δ����� ���ذ�(20) �̻�
	  (3) ���δ��� Ư�� �δ�ɷ��� ���ذ�(40) �̻�
	  (4) ���δ��� �δ������� ���ذ�(����C) �ʰ�
	  (5) ����δ��� ���δ뿡 ���� �跫 ����Ȯ�� ������ ���� (�������� ����)
	   - ��庰�� ������ �޶��� : ���1(������ ����Ǵ� ��󿡰� �õ�), ���2(Ȯ���� ����Ǵ� ��󿡰� �õ�)
	 2) ���δ� �� ��
	  - �������Ǻ��� ���ϸ�, ������ ��� ���������� ��
	  (1) ���δ��� ������ ������� : ������ ��������� �����ϴ� ���δ븦 �켱
	    - ������ ���� �� ���� ���� ���� �� ���ÿ� ������ �������� �δ븦 �켱
	  (2) ���δ��� �����δ� : ����δ밡 ��ȯƯ�� ���� �� ���δ��� ������ǥ�� ����δ��� ���δ밡 �����ϴ� ��츦 �켱
	  (3) ���δ��� �δ�ɷ�(���ݷ�) : �������� �켱
	  (4) ���δ��� �δ�ɷ�(����) : �������� �켱
	  (5) ���δ��� �δ뺴�� : �������� �켱
	  (6) ����δ�� ���δ��� �Ÿ� : �������� �켱
	  (7) ���δ��� �δ����� : �������� �켱
	  (8) ���δ��� �δ��� : Ŭ���� �켱
	  (9) ����δ��� ���δ뿡 ���� �跫����Ȯ�� : �������� �켱 (��, Ȯ�������� ��忡 ����)
	  (10) ���δ��� �δ뱸���� : �������� �켱
	  (11) ���δ� �ֺ��� �����ϴ� ����δ��� ���� �δ��(5ĭ �̳�) : �������� �켱
	  (12) ���δ� �ֺ��� �����ϴ� ����δ��� ���� �����(5ĭ �̳�) : �������� �켱
	  (13) ���δ� �ֺ��� �����ϴ� ����δ��� �Ʊ� �δ��(5ĭ �̳�) : �������� �켱
	  (14) ���δ� �ֺ��� �����ϴ� ����δ��� �Ʊ� �����(5ĭ �̳�) : �������� �켱

	3. ����δ밡 �跫 ���������� �����ϰ� ���δ밡 �����ϴ� ��� �跫 ����δ밡 �̵��� �ʿ����� Ȯ��
	 1) ���δ밡 ����δ��� �跫���� �ۿ� �����ϴ� ���
	 2) ����δ밡 ������ ���� �����ϴ� ���
	 3) ����δ밡 Ư���ü��� ���� �ȿ� ��ġ�ϴ� ���
	  - �ü��� �ڵ����� �� ������ ���� Ȯ��
	 4) ����δ밡 �����δ��� ���

	4. �跫 ����δ밡 �̵��� �ʿ��� ��� �̵� �ĺ���ǥ �˻�
	 1) �̵� �ĺ���ǥ�� ���� Ȯ��
	  (1) ��������(�����౺ �̿��� ��)�� ���� �ʴ� ��ǥ
	  (2) �������� �ƴ� ��ǥ
	  (3) �ü����� ���� ��ǥ
	   - �ü��� �ڵ����� �� ������ ���� Ȯ��
	 2) �ĺ���ǥ �� ��
	  - ���δ�κ��� �� ��ǥ �켱

	5. ���� ��� ���ǵ��� ������ ��� ����δ밡 ���δ븦 ���� �跫 ����
	 - ���ǿ� �ɸ� ��쿡�� �ش� AI�δ��� ���� �ӹ��� ����
	 1) �̵��� �ʿ��� ��쿡�� �̵� ������ ��ǥ�� �����ϴ� ��� �̵� �� �跫 ����
	 2) �̵��� �ʿ���� ��쿡�� ���� ��ġ���� �跫 ����
*/

namespace AI�δ�_�跫����
{

/// ============================================ < ���� ���� > ============================================


/// [ �Ϲ� ���� ]


	/// AI�δ��� �跫���� ��� ���뿩�� ����
	const array<bool> AI�δ�_�跫����_�����δ�_���� = {/*�÷��̾� ���ӱ���*/true, /*��ǻ��*/true};
	const array<bool> AI�δ�_�跫����_�����δ�_���� = {/*�÷��̾� ���ӱ���*/true, /*��ǻ��*/true};


	/// ���弼�� �δ� ���뿩�� ����
	const bool ���弼��_���� = true;


	/// ��ǻ�� ���� �δ��� ��� �÷��̾� ������ �δ븸�� ������� �跫�� �����ϵ��� ���� ���� ����
	const bool ��ǻ�ͺδ�_�跫������_�÷��̾����� = false;


	/// ����δ밡 ������ �跫 ���
	// �Էµ� �׸��� ������� �跫�� �õ� (�跫 �׸��� ���� ���� �� ������ ����, ���ο� �׸� �߰� ����)
	const array<int> ����跫_�϶� = {�跫_����, �跫_����};


	/// ����δ밡 �跫�� �����ϱ� ���� ���δ븦 �˻��� ����δ�κ����� ���ذŸ� (���ذŸ� �̳��� ���δ븸�� �˻�)
	const int �跫����_���ذŸ� = 8;


	/// ����δ��� ���δ뿡 ���� �跫 ����Ȯ�� ���� ���� ���

	// ��� 1 : ���������� (����Ȯ���� �����Ͽ� ������ Ȯ���� �δ븦 ������θ� �跫 ����, ������ �δ븦 ������δ� �õ����� ����)
	// ��� 2 : Ȯ�������� (����Ȯ���� ������ ����Ȯ������ ���� �δ븸�� ������� �跫 ����, ���� ������ ���� ����)
	const array<int> ����Ȯ��_������ = {/*�÷��̾� ���ӱ���*/2, /*��ǻ��*/2};

	// ���2 ���ü��� : ���δ뿡 ���� �跫�� ����Ȯ���� ������ �̸��� ��� �õ����� ���� ('���2' �������� ����)
	const array<int> �������_����Ȯ�� = {/*�÷��̾� ���ӱ���*/75, /*��ǻ��*/75};


	/// ���δ� ��ó�� ����δ밡 �̵��� �ĺ���ǥ �˻� �� ����

	// �ĺ� �̵���ǥ�� ��õ ����, ������ ���ظ� �Դ� ������ ��� �ĺ���ǥ���� ����ų�� ����
	const array<bool> �ĺ��̵���ǥ_�˻���_����������ǥ_���� = {/*�÷��̾� ���ӱ���*/true, /*��ǻ��*/true};

	// �ĺ� �̵���ǥ�� �������� ��� �ĺ���ǥ���� ����ų�� ����
	const array<bool> �ĺ��̵���ǥ_�˻���_��������ǥ_���� = {/*�÷��̾� ���ӱ���*/true, /*��ǻ��*/true};

	// �ĺ� �̵���ǥ�� Ư���ü��� ���� ���� �ִ� ��� �ĺ���ǥ���� ����ų�� ����
	const array<bool> �ĺ��̵���ǥ_�˻���_�ü�������ǥ_���� = {/*�÷��̾� ���ӱ���*/true, /*��ǻ��*/true};


	/// ����δ밡 ȸ���� ���ü� ����
	// 1. ���� ��ġ������ ����δ� �̵� �ʿ俩�� Ȯ�� �� 
	// 2. �ĺ� �̵���ǥ������ �ü����� Ȯ�� ��
	const array<array<int>> ȸ�Ǵ��_�ü� =
	{
		/*�����ü�*/ {�ü�_����, �ü�_����, �ü�_�ױ�},
		/*����ü�*/ {�ü�_��, �ü�_���, �ü�_��ä, �ü�_�ó�, �ü�_�����, �ü�_������, �ü�_��������, �ü�_������1, �ü�_������2},
		/* ��ֹ� */ {},
		/*  ����  */ {�ü�_�Ҿ�, �ü�_ȭ����, �ü�_��ȭ��, �ü�_ȭ��, �ü�_ȭ��, �ü�_ȭ����, �ü�_��ȭ��, �ü�_����},
		/*�����ü�*/ {}
	};


/// -------------------------------------------------------------------------------------------------------


/// [ ����δ� ���� ���� ]


	/// ����δ��� �δ������� ���ۺδ��� ��� �跫�� �������� ����
	const array<bool> ����δ�_���ۺδ�_���� = {/*�÷��̾� ���ӱ���*/false, /*��ǻ��*/false};


	/// ����δ��� ����� ���ذ� �̸��� ��� �跫�� �������� ���� (����� �跫 �Һ��� �̸��� ���� �翬�� �Ұ���)
	const array<bool> ����δ�_�������_���� = {/*�÷��̾� ���ӱ���*/true, /*��ǻ��*/true};
	const array<int> ����δ�_���ر�� = {/*�÷��̾� ���ӱ���*/30, /*��ǻ��*/30};


	/// ����δ��� Ư�� �δ�ɷ��� ���ذ� �̻��� ��� �跫�� �������� ����
	const array<bool> ����δ�_�ɷ�����_���� = {/*�÷��̾� ���ӱ���*/true, /*��ǻ��*/true};
	const int ����δ�_����ɷ� = �δ�ɷ�_����;
	const array<int> ����δ�_���شɷ� = {/*�÷��̾� ���ӱ���*/70, /*��ǻ��*/70};


	/// ����δ��� ������ ���ذ� �̻��� ��� �跫�� �������� ����
	// ���� : ���� S ������ ������ ����ϴ� ��� ��ȣ�� �Է��ؾ� �� (���� C�� ��ȣ�� 0�̰� ���� ���� �� �ܰ� ��� �ø��� ��ȣ +1)
	const array<bool> ����δ�_��������_���� = {/*�÷��̾� ���ӱ���*/true, /*��ǻ��*/true};
	const array<int> ����δ�_�������� = {/*�÷��̾� ���ӱ���*/����_A, /*��ǻ��*/����_A};


	/// ����δ밡 ���⺰�� ������ Ư�� Ư�⸦ ������ ��� �跫�� �������� ����

	// Ư������ ���뿩�� ����
	const array<bool> ����δ�_Ư������_���� = {/*�÷��̾� ���ӱ���*/true, /*��ǻ��*/true};

	// Ư�⺰ Ư������ ���뿩�� ����
	const bool ����δ�_�͹�Ư��_���� = true;	// ��� ���⿡ ����
	const bool ����δ�_���Ư��_���� = false;	// ��� ���⿡ ����
	const bool ����δ�_����Ư��_���� = false;	// ���� ������ ��� ���⿡ ����
	const bool ����δ�_�п�Ư��_���� = true;	// ���� ������ ��� ���⿡ ����
	const bool ����δ�_����Ư��_���� = true;	// ���� ������ ��� ���⿡ ����
	const bool ����δ�_����Ư��_���� = true;	// ���� ������ ��� ���⿡ ����

	// ���⺰�� Ư�������� ������ Ư�� ����
	const array<array<int>> ����δ�_���⺰_����Ư�� =
	{
		/* �� */ {},
		/* â */ {Ư��_����, Ư��_����, Ư��_����, Ư��_â��, Ư��_â��, Ư��_����},
		/* �� */ {Ư��_����, Ư��_����, Ư��_����, Ư��_�ؽ�, Ư��_����, Ư��_����, Ư��_�ɰ�, Ư��_��ǳ},
		/* �� */ {Ư��_����, Ư��_����, Ư��_�ý�, Ư��_����},
		/*����*/ {Ư��_����, Ư��_����, Ư��_���, Ư��_����, Ư��_����},
		/*����*/ {Ư��_����, Ư��_����},
		/*����*/ {Ư��_����, Ư��_����, Ư��_����},
		/*����*/ {Ư��_����, Ư��_����, Ư��_����},
		/*���*/ {Ư��_����, Ư��_����},
		/*�ְ�*/ {Ư��_����, Ư��_����},
		/*����*/ {Ư��_����, Ư��_����},
		/*����*/ {Ư��_����, Ư��_����}
	};


/// -------------------------------------------------------------------------------------------------------


/// [ ���δ� ���� ���� ]


	/// ���δ��� ������ ���ذ� �̸��� ��� �跫 �����󿡼� ����
	const array<bool> ���δ�_��������_���� = {/*�÷��̾� ���ӱ���*/true, /*��ǻ��*/true};
	const array<int> ���δ�_���غ��� = {/*�÷��̾� ���ӱ���*/1500, /*��ǻ��*/1500};


	/// ���δ��� ����� ���ذ� �̸��� ��� �跫 �����󿡼� ����
	const array<bool> ���δ�_�������_���� = {/*�÷��̾� ���ӱ���*/true, /*��ǻ��*/true};
	const array<int> ���δ�_���ر�� = {/*�÷��̾� ���ӱ���*/20, /*��ǻ��*/20};


	/// ���δ��� Ư�� �δ�ɷ��� ���ذ� �̸��� ��� �跫 �����󿡼� ����
	const array<bool> ���δ�_�ɷ�����_���� = {/*�÷��̾� ���ӱ���*/true, /*��ǻ��*/true};
	const array<int> ���δ�_���شɷ� = {/*�÷��̾� ���ӱ���*/40, /*��ǻ��*/40};
	const int ���δ�_����ɷ� = �δ�ɷ�_����;


	/// ���δ��� �δ������� ���ذ� ������ ��� �跫 �����󿡼� ����
	// ���� : ���� S ������ ������ ����ϴ� ��� ��ȣ�� �Է��ؾ� �� (���� C�� ��ȣ�� 0�̰� ���� ���� �� �ܰ� ��� �ø��� ��ȣ +1)
	const array<bool> ���δ�_��������_���� = {/*�÷��̾� ���ӱ���*/true, /*��ǻ��*/true};
	const array<int> ���δ�_�������� = {/*�÷��̾� ���ӱ���*/����_C, /*��ǻ��*/����_C};


	/// �跫�� �����ϱ� ���� ���ǵ��� ����� ���δ�� ���� �� ����

	// ���� ��ó���� ������ ��������� �����ϴ� ���δ뿡�� �켱������ �跫�� ����
	const array<bool> ������_�������_���� = {/*�÷��̾� ���ӱ���*/true, /*��ǻ��*/true};
	const int ������_�������_���ذŸ� = 6;
	const int ������_�������_���س������� = 30;
	const int ������_�������_���غ��� = 5000;

	// ����δ밡 ��ȯƯ�⸦ ������ ��� �����δ밡 �ִ� ���δ뿡�� �켱������ �跫�� ����
	const array<bool> ��ȯƯ��_�����δ�_�켱 = {/*�÷��̾� ���ӱ���*/true, /*��ǻ��*/true};


/// =========================================================================================

	// ����� ����
	const bool �����_func261_prev_handler_check = false;
	const bool �����_func262_prev_handler_check = false;
	const bool �����_serach_pos_to_move = false;
	const bool �����_strategy_success_info = false;
	const bool �����_dst_unit_sort_info = false;

	class Main
	{

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		// AI ��ũ��Ʈ �Լ� ü���� ���� ���� �ڵ鷯 �����
		pk::func261_t@ prev_callback_261;

		// �δ� �ӹ� �ڵ鷯 �Լ� ü���� ���� ���� �ڵ鷯 �����
		pk::func262_t@ prev_callback_262;

		// ����δ밡 �跫�� ������ ���δ� �˻� �� �ش� ���δ� ��ó�� �̵������� �ĺ���ǥ �����
		array<pk::point> ���δ뺰_�̵��ĺ���ǥ(�δ�_��, -1);

		// �ĺ� �̵���ǥ �˻� �Լ� ������
		pk::point range_pos_;

		// �ĺ� ���δ� �迭 ���Ŀ�
		int strategy_id_;
		pk::unit@ src_unit_;

		// ������ ������ �ü����� Ȯ�� �� �����
		array<array<int>> ���⺰_������_��ǥ���� =
		{
			/*�ϼ�*/ {4, 15, 32, 55, 84, 119, 160, 207},	/* �� */ {5, 17, 35, 59, 89, 125, 167, 215},
			/*�ϵ�*/ {0,  7, 20, 39, 64,  95, 132, 175},	/*����*/ {3, 13, 29, 51, 79, 113, 153, 199},
			/* �� */ {2, 11, 26, 47, 74, 107, 146, 191},	/*����*/ {1,  9, 23, 43, 69, 101, 139, 183}
		};

	/**
		[ �߰� ������� ]

		�������� �� �ü����� ������ ���, ����δ밡 �̵��� �ĺ���ǥ�� �˻��ϴµ� �־ ������ ������ �� �����ߴµ�
		�ش� ���ǵ��� �������� ���� �̵������� ��ǥ�� ���� ��쿡�� �����ϰ� �跫�� ������ ������ ����
	*/

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		Main()
		{
			// 261�Լ� ���� �ڵ鷯 ����, �Լ� �ʱ�ȭ, �Լ� ������
			@prev_callback_261 = cast<pk::func261_t@>(pk::get_func(261));
			pk::reset_func(261);
			pk::set_func(261, pk::func261_t(func261));

			// 262�Լ� ���� �ڵ鷯 ����, �Լ� �ʱ�ȭ, �Լ� ������
			@prev_callback_262 = cast<pk::func262_t@>(pk::get_func(262));
			pk::reset_func(262);
			pk::set_func(262, pk::func262_t(func262));
		}

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		/**
		@param  force : AI ����
		@return �ڽ��� ó���ߴٸ� true. ��ǻ�Ϳ��� �ñ���� false.
		*/
		/// ���� : AI ��ũ��Ʈ �Լ�(261)�� ����ϴ� ��쿡�� �÷��̾� 1������ �̹� ������ ������
		/// ���� : 261�Լ��� ��ü AI ��ũ��Ʈ�̱� ������ �δ밡 �跫�� ������ �� ���� �ڵ鷯�� ������ ü�����־�� ��
		bool func261(pk::force@ force)
		{
			if (�����_func261_prev_handler_check)
			{
				string force_name = pk::decode(pk::get_name(force));
				pk::info(force_name+" ���� - 261�Լ� ���� �ڵ鷯 ���翩�� : "+(prev_callback_261 is null ? "����" : "����"));
			}

			for (int unit_id = 0; unit_id < �δ�_��; unit_id++)
			{
				pk::unit@ unit = pk::get_unit(unit_id);
				if (!pk::is_alive(unit)) continue;
				if (unit.get_force_id() != force.get_id()) continue;

				// ����δ밡 �����δ��� ��� ���� (�δ� ��ǥ�� �δ� �ҼӰ��� ��ǥ�� ������ ��� ����)
				pk::building@ building = pk::get_building(pk::get_service(unit));
				if (pk::is_alive(building) and unit.pos == building.pos) continue;

				strategy_action_of_AI_unit(unit, force, /*is_deployed*/false);
			}

			if (prev_callback_261 is null) return false;
			return prev_callback_261(force);
		}

		/**
		@param  unit : �δ� �ӹ� ����δ�
		@return �ڽ��� ó���ߴٸ� true. ��ǻ�Ϳ��� �ñ���� false.
		*/
		/// ���� : pk::run_order �Լ��� ����� ��� �� ��ũ��Ʈ�� ����˴ϴ�. (262 �Լ� ������ pk::run_order �Լ� ��� �� ���ѷ��� �߻�)
		/// ���� : 262�Լ��� �δ� �ӹ� �ڵ鷯�� ������ ��ũ��Ʈ�̹Ƿ� �ش� �δ밡 �跫�� �����ߴٸ� �ൿ�Ϸ�ǹǷ� ���� �ڵ鷯�� ü������ ����
		bool func262(pk::unit@ unit)
		{
			if (�����_func262_prev_handler_check)
			{
				string unit_name = pk::decode(pk::get_name(unit));
				pk::info(unit_name+" - 262�Լ� ���� �ڵ鷯 ���翩�� : "+(prev_callback_262 is null ? "����" : "����"));
			}

			// ����δ밡 �����δ��� ��쿡�� ���� (�δ� ��ǥ�� �δ� �ҼӰ��� ��ǥ�� ������ ��� ����)
			pk::building@ building = pk::get_building(pk::get_service(unit));
			if (pk::is_alive(building) and unit.pos == building.pos)
			{
				pk::force@ force = pk::get_force(unit.get_force_id());
				strategy_action_of_AI_unit(unit, force, /*is_deployed*/true);

				// �跫�� ����� ��� ���� �ڵ鷯�� ü������ ����
				if (unit.pos != building.pos) return true;
			}

			if (prev_callback_262 is null) return false;
			return prev_callback_262(unit);
		}

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		void strategy_action_of_AI_unit(pk::unit@ unit, pk::force@ force, bool is_deployed)
		{
			// �⺻���� : �÷��̾� 1���� �δ� ����
			if (pk::is_player_controlled(unit)) return;

			// �⺻���� : �Ϲݰ��� ���� Ȯ�� (��������, Ʃ�丮��, �̼� ���� ���� �ƴ� ��)
			if (!is_normal_game()) return;

			// �⺻���� : ���弼�� ���뿩�� Ȯ��
			if (!pk::is_normal_force(force) and !���弼��_����) return;

			// �������� : ����δ��� ������ü��(�÷��̾� ���ӱ���, ��ǻ��) ���뿩�� Ȯ��
			int controller_index = get_controller_index(unit);
			if (is_deployed)
			{
				// ����δ밡 �����δ��� ��� ���뿩�� Ȯ��
				if (!AI�δ�_�跫����_�����δ�_����[controller_index]) return;
			}
			else
			{
				// ����δ밡 �����δ��� ��� ���뿩�� Ȯ��
				if (!AI�δ�_�跫����_�����δ�_����[controller_index]) return;
			}

			for (int arr_index = 0; arr_index < int(����跫_�϶�.length); arr_index++)
			{
				int strategy_id = ����跫_�϶�[arr_index];
				func_�跫����(unit, force, strategy_id, controller_index, is_deployed);
			}
		}

		// ����δ밡 �跫 ���δ밡 �����ϴ� ��� �跫���� (�跫������ ���� ����δ��� �̵��� �ʿ��� ��� �̵� �� ����)
		void func_�跫����(pk::unit@ src_unit, pk::force@ src_force, int strategy_id, int controller_index, bool is_deployed)
		{
			// �ĺ� ���δ� �迭 ���Ŀ� ���� ����
			@src_unit_ = @src_unit;
			strategy_id_ = strategy_id;

			// �跫 ����δ밡 �跫������ ���� ������ �����ϴ��� Ȯ��
			int energy_cost = get_energy_cost(src_unit, strategy_id);
			if (!func_����δ�_��������(src_unit, strategy_id, energy_cost, controller_index)) return;

			// �跫���� ���� �ĺ����δ� �˻� (���δ� ���� �� �̵��ĺ���ǥ Ȯ��)
			int strategy_range = src_unit.has_skill(Ư��_�͸�) ? 3 : 2;
			pk::unit@ dst_unit = get_dst_unit(src_unit, src_force, strategy_id, strategy_range, controller_index, is_deployed);
			if (!pk::is_alive(dst_unit)) return;

			// ���δ� �˻� �� �����ߴ� ����δ��� �̵��ĺ���ǥ ��ȯ : �̵��� �ʿ��� ��쿡�� ����� ����
			pk::point pos_to_move = ���δ뺰_�̵��ĺ���ǥ[dst_unit.get_id()];
			if (pk::is_valid_pos(pos_to_move))
			{
				// �̵��ĺ���ǥ�� ��ȿ��(�����) ��� ����δ� �̵��ĺ���ǥ�� �̵� : �δ� �̵���� ����
				/// ���� : pk::get_path(unit, unit.pos, pos) �Լ� ��� �� �������� ���� �߻�
				if (is_deployed)
				{
					/// ���� : 262�Լ��� ����ϴ� �����δ��� ��� pk::run_order �Լ��� ����ϸ� ���ѷ��� �߻�
				//	array<pk::point> unit_path = pk::get_path(src_unit, src_unit.pos, pos_to_move);
					array<pk::point> unit_path = {src_unit.pos, pos_to_move};	// �ӽù��� but �̵� �ִϸ��̼� ���ڿ�������
					pk::move(src_unit, unit_path);
				}
				else
				{
					pk::set_order(src_unit, �δ��ӹ�_�̵�, pos_to_move);
					pk::run_order(src_unit);
				}
			}

			// ����δ� �跫 ���� (��ȯ Ư��, �ݰ� Ư�� �ݿ�)
			func_�跫����(src_unit, src_force, dst_unit, strategy_id, energy_cost, controller_index, is_deployed);
		}

		// �跫 ����δ밡 �跫������ ���� ������ �����ϴ��� Ȯ��
		bool func_����δ�_��������(pk::unit@ src_unit, int strategy_id, int energy_cost, int controller_index)
		{
			// �⺻���� : ����δ�κ��� ���δ븦 �˻��� ���ذŸ� �̳��� ���δ밡 �����ϴ��� Ȯ��
			if (func_�δ��ó_���δ��(src_unit, �跫����_���ذŸ�) == 0) return false;

			// �⺻���� : ����δ��� �δ��ӹ��� ���� ��� ����
			if (src_unit.order == �δ��ӹ�_��) return false;

			// �⺻���� : ����δ밡 �ൿ�Ϸ� ������ ��� ����
			if (src_unit.action_done) return false;

			// �⺻���� : ����δ��� �δ����� �跫�� �Һ��� �̸��� ��� ����
			if (int(src_unit.energy) < energy_cost) return false;

			// �������� : ����δ��� �δ������� ���ۺδ��� ��� ���뿩�� Ȯ��
			if (!����δ�_���ۺδ�_����[controller_index] and src_unit.type == �δ�����_����) return false;

			// �������� : ����δ��� �δ����� ���ر�� �̸��� ��� ����
			if (����δ�_�������_����[controller_index])
			{
				if (int(src_unit.energy) < ����δ�_���ر��[controller_index]) return false;
			}

			// �������� : ����δ��� Ư�� �δ�ɷ��� ���شɷ� �̻��� ��� ����
			if (����δ�_�ɷ�����_����[controller_index])
			{
				if (int(src_unit.attr.stat[����δ�_����ɷ�]) >= ����δ�_���شɷ�[controller_index]) return false;
			}

			// �������� : ����δ��� �δ������� �������� �̻��� ��� ����
			int weapon_id = src_unit.weapon;
			if (����δ�_��������_����[controller_index])
			{
				int src_tekisei = (weapon_id == ����_��) ? 0 : pk::get_tekisei(src_unit, weapon_id);
				if (src_tekisei >= ����δ�_��������[controller_index]) return false;
			}

			// �������� : ����δ밡 �������� ������ Ư�� Ư�⸦ ������ ��� ����
			if (����δ�_Ư������_����[controller_index])
			{
				if (src_unit.has_skill(Ư��_�͹�) and ����δ�_�͹�Ư��_����) return false;
				if (src_unit.has_skill(Ư��_���) and ����δ�_���Ư��_����) return false;

				if (weapon_id != ����_��)
				{
					if (src_unit.has_skill(Ư��_�п�) and ����δ�_�п�Ư��_����) return false;
					if (src_unit.has_skill(Ư��_����) and ����δ�_����Ư��_����) return false;
					if (src_unit.has_skill(Ư��_����) and ����δ�_����Ư��_����) return false;

					/// ���� : '��Ÿ.xml'�� '��Ư�⿬��' ���� 'true'�� ���� �� �������� ���� Ư�Ⱑ �����
					if (src_unit.has_skill(Ư��_����) and ����δ�_����Ư��_����) return false;
				}

				for (int arr_index = 0; arr_index < int(����δ�_���⺰_����Ư��[weapon_id].length); arr_index++)
				{
					int skill_id = ����δ�_���⺰_����Ư��[weapon_id][arr_index];
					if (src_unit.has_skill(skill_id)) return false;
				}
			}

			return true;
		}

		// ������ �����ϴ� ���δ�� �� ���ؿ� ���� ���� �� �ֿ켱 ������ ���δ븦 ��ȯ
		pk::unit@ get_dst_unit(pk::unit@ src_unit, pk::force@ src_force, int strategy_id, int strategy_range, int controller_index, bool is_deployed)
		{
			array<pk::unit@> dst_unit_arr = get_dst_unit_arr(src_unit, src_force, strategy_id, strategy_range, controller_index, is_deployed);
			if (int(dst_unit_arr.length) == 0) return null;

			if (�����_dst_unit_sort_info)
			{
				pk::message_box(pk::encode("���δ�迭 ���� ��"));
				for (int i = 0; i < int(dst_unit_arr.length); i++)
				{
					pk::unit@ unit = dst_unit_arr[i];
					string unit_name = pk::decode(pk::get_name(unit));
					pk::message_box(pk::encode("���δ�迭 ���� "+i+" : "+unit_name+"\n�δ���ݷ� : "+int(unit.attr.stat[�δ�ɷ�_����])+"\n�δ����� : "+int(pk::get_tekisei(unit))));
				}
			}
		/**
			[ ���� ] ���δ� �� ���� �켱����

			1. ���δ��� ������ ������� : ������ ��������� �����ϴ� ���δ븦 �켱 (��, ������ ������� ���� ��)
			2. ���δ��� �����δ� : ����δ밡 ��ȯƯ�� ���� �� ���δ��� ������ǥ�� ����δ��� ���δ밡 �����ϴ� ��츦 �켱 (��, ���� ���� ��)
			3. ���δ��� �δ�ɷ�(���ݷ�) : Ŭ���� �켱
			4. ���δ��� �δ�ɷ�(����) : Ŭ���� �켱
			5. ���δ��� �δ뺴�� : �������� �켱
			6. ����δ�� ���δ��� �Ÿ� : �������� �켱
			7. ���δ��� �δ����� : �������� �켱
			8. ���δ��� �δ��� : Ŭ���� �켱
			9. ����δ��� ���δ뿡 ���� �跫����Ȯ�� : �������� �켱 (��, Ȯ�������� ��忡 ����)
			10. ���δ��� �δ뱸���� : �������� �켱
			11. ���δ� �ֺ��� �����ϴ� ����δ��� ���� �δ��(5ĭ �̳�) : �������� �켱
			12. ���δ� �ֺ��� �����ϴ� ����δ��� ���� �����(5ĭ �̳�) : �������� �켱
			13. ���δ� �ֺ��� �����ϴ� ����δ��� �Ʊ� �δ��(5ĭ �̳�) : �������� �켱
			14. ���δ� �ֺ��� �����ϴ� ����δ��� �Ʊ� �����(5ĭ �̳�) : �������� �켱
		*/
		/**
			[ ���� ]

			1. ���� �δ� �� ���� �� �� ���̰��� �ſ� ���� ���� ���� �ָ��� ��Ȳ���� �ݿ��ϰ� ���� ��� ���� ������ ������ �ο��� ���� ������
			   �׷��� ������ �ΰ� �̻��̰� ������ �Ϸ��� �迭�� �׸��� 3�� �̻��� ��쿡�� �׸� ���� �񱳰� �Ұ����� ��Ȳ�� �߻��� �� ����
			2. �迭�̳� ����Ʈ�� ������ ������ ������ ���ǿ� ���Ͽ� ���ܰ� ����� ��츦 ������ ��
			   ������ Ư�� ���ǿ� ���Ͽ� ������ ���ϴ� ��� ����� ���� ó������ �ʰ� �Ǹ� ó������ ���� ����� ���� ���� ���ǿ��� ó���Ǿ� 
			   ���ϴ� ����� �ٸ��� ������ �Ǿ���� �� ����
		*/
			// ���δ��� �׸� �迭�� ���ǿ� ���� ����
			dst_unit_arr.sort(function(a, b)
			{
				// ���δ��� ������ ������� : ������ ��������� �����ϴ� ���δ븦 �켱 (��, ������ ������� ���� ��)
				int controller_index = main.get_controller_index(main.src_unit_);
				if (������_�������_����[controller_index])
				{
					bool a_is_siege_warfare = main.func_������_�������_��������(main.src_unit_, a);
					bool b_is_siege_warfare = main.func_������_�������_��������(main.src_unit_, b);
					if (a_is_siege_warfare and !b_is_siege_warfare) return true;
					else if (!a_is_siege_warfare and b_is_siege_warfare) return false;
				}

				// ���δ��� �����δ� : ����δ밡 ��ȯƯ�� ���� �� ���δ��� ������ǥ�� ����δ��� ���δ밡 �����ϴ� ��츦 �켱 (��, ���� ���� ��)
				if (��ȯƯ��_�����δ�_�켱[controller_index] and main.src_unit_.has_skill(Ư��_��ȯ))
				{
					pk::unit@ a_neighbor_unit = main.get_dst_neighbor_unit(main.src_unit_, a);
					pk::unit@ b_neighbor_unit = main.get_dst_neighbor_unit(main.src_unit_, b);
					if (pk::is_alive(a_neighbor_unit) and !pk::is_alive(b_neighbor_unit)) return true;
					else if (!pk::is_alive(a_neighbor_unit) and pk::is_alive(b_neighbor_unit)) return false;
				}

				// ���δ��� �δ�ɷ�(���ݷ�) : Ŭ���� �켱
				int a_atk_stat = a.attr.stat[�δ�ɷ�_����];
				int b_atk_stat = b.attr.stat[�δ�ɷ�_����];
				if (a_atk_stat != b_atk_stat) return a_atk_stat > b_atk_stat;

				// ���δ��� �δ�ɷ�(����) : Ŭ���� �켱
				int a_int_stat = a.attr.stat[�δ�ɷ�_����];
				int b_int_stat = b.attr.stat[�δ�ɷ�_����];
				if (a_int_stat != b_int_stat) return a_int_stat > b_int_stat;

				// ���δ��� �δ뺴�� : �������� �켱
				if (a.troops != b.troops) return a.troops > b.troops;

				// ����δ�� ���δ��� �Ÿ� : �������� �켱
				int a_distance = pk::get_distance(main.src_unit_.pos, a.pos);
				int b_distance = pk::get_distance(main.src_unit_.pos, b.pos);
				if (a_distance != b_distance) return a_distance < b_distance;

				// ���δ��� �δ����� : �������� �켱
				int a_tekisei = (a.weapon != ����_��) ? pk::get_tekisei(a, a.weapon) : 0;
				int b_tekisei = (b.weapon != ����_��) ? pk::get_tekisei(b, b.weapon) : 0;
				if (a_tekisei != b_tekisei) return a_tekisei > b_tekisei;

				// ���δ��� �δ��� : Ŭ���� �켱
				if (a.energy != b.energy) return a.energy > b.energy;

				// ����δ��� ���δ뿡 ���� �跫����Ȯ�� : �������� �켱 (��, Ȯ�������� ��忡 ����)
				if (����Ȯ��_������[controller_index] == /*Ȯ��������*/2)
				{
					int a_chance = main.get_success_chance(main.src_unit_, a.pos, main.strategy_id_);
					int b_chance = main.get_success_chance(main.src_unit_, b.pos, main.strategy_id_);
					if (a_chance != b_chance) return a_chance > b_chance;
				}

				// ���δ��� �δ뱸���� : �������� �켱
				int a_member_count = pk::get_member_count(a);
				int b_member_count = pk::get_member_count(b);
				if (a_member_count != b_member_count) a_member_count > b_member_count;

				array<int> a_around_info = main.func_���δ�_��ó�δ�_��������_�迭(main.src_unit_, a, /*distance*/5);
				array<int> b_around_info = main.func_���δ�_��ó�δ�_��������_�迭(main.src_unit_, b, /*distance*/5);

				// ���δ� �ֺ��� �����ϴ� ����δ��� ���� �δ��(5ĭ �̳�) : �������� �켱
				if (a_around_info[0] != b_around_info[0]) return a_around_info[0] < b_around_info[0];

				// ���δ� �ֺ��� �����ϴ� ����δ��� ���� �����(5ĭ �̳�) : �������� �켱
				if (a_around_info[1] != b_around_info[1]) return a_around_info[1] < b_around_info[1];

				// ���δ� �ֺ��� �����ϴ� ����δ��� �Ʊ� �δ��(5ĭ �̳�) : �������� �켱
				if (a_around_info[2] != b_around_info[2]) return a_around_info[2] > b_around_info[2];

				// ���δ� �ֺ��� �����ϴ� ����δ��� �Ʊ� �����(5ĭ �̳�) : �������� �켱
				if (a_around_info[3] != b_around_info[3]) return a_around_info[3] > b_around_info[3];

				return true;
			});

			if (�����_dst_unit_sort_info)
			{
				pk::message_box(pk::encode("���δ�迭 ���� ��"));
				for (int i = 0; i < int(dst_unit_arr.length); i++)
				{
					pk::unit@ unit = dst_unit_arr[i];
					string unit_name = pk::decode(pk::get_name(unit));
					pk::message_box(pk::encode("���δ�迭 ���� "+i+" : "+unit_name));
				}
			}

			return dst_unit_arr[0];
		}

		// ���δ� ������ �����ϰ� ����δ밡 �̵��� �ʿ��� ��� �ĺ� �̵���ǥ�� �����ϴ� ���δ� �ĺ��� ��ȯ
		array<pk::unit@> get_dst_unit_arr(pk::unit@ src_unit, pk::force@ src_force, int strategy_id, int strategy_range, int controller_index, bool is_deployed)
		{
			for (int i = 0; i < �δ�_��; i++) ���δ뺰_�̵��ĺ���ǥ[i] = -1;
			array<pk::unit@> dst_unit_arr(0);
			array<pk::point> range_arr = pk::range(src_unit.pos, 1, �跫����_���ذŸ�);
			for (int i = 0; i < int(range_arr.length); i++)
			{
				pk::point dst_pos = range_arr[i];
				pk::unit@ dst_unit = pk::get_unit(dst_pos);
				if (!pk::is_alive(dst_unit)) continue;

				// ��ǻ�� ���� �δ��� ��� �÷��̾� ������ �δ븸�� ������� �跫�� �����ϵ��� ���� ���� Ȯ��
				if (��ǻ�ͺδ�_�跫������_�÷��̾����� and !src_unit.is_player())
				{
					if (!dst_unit.is_player()) continue;
				}

				// �跫�� ���δ밡 �跫������ ���� ������ �����ϴ��� Ȯ��
				if (!func_���δ�_��������(src_unit, dst_unit, strategy_id, controller_index)) continue;

			/**
				[ ���� ] ����δ밡 �̵��� �ʿ䰡 �ִ� ���

				1. ���δ밡 ����δ��� �跫���� �ۿ� �����ϴ� ���
				2. ����δ밡 ������ ���� �����ϴ� ���
				3. ����δ밡 Ư���ü��� ���� �ȿ� ��ġ�ϴ� ���
				4. ����δ밡 �����δ��� ���
			*/
				// ����δ밡 ���� ��ǥ���� �̵��� �ʿ䰡 �ִ� ��� �̸� ���δ� ��ó�� �̵�������ǥ ���翩�� Ȯ��
				int curr_distance = pk::get_distance(src_unit.pos, dst_pos);
				if (curr_distance > strategy_range or pk::is_on_fire(src_unit.pos) or is_in_facility_range(src_unit, src_unit.pos) or is_deployed)
				{
					// ���δ� ��ó�� ����δ밡 �̵��� �ĺ���ǥ �˻�
					pk::point pos_to_move = get_pos_to_move(src_unit, src_force, dst_unit, strategy_range, controller_index);

					// �̵������� �ĺ���ǥ�� ���� ��� ����
					if (!pk::is_valid_pos(pos_to_move)) continue;

					// ���δ� ��ó�� ����δ밡 �̵� ������ ��ǥ�� ����
					���δ뺰_�̵��ĺ���ǥ[dst_unit.get_id()] = pos_to_move;
				}

				// ������ ����� ���δ븦 ����
				dst_unit_arr.insertLast(dst_unit);
			}

			return dst_unit_arr;
		}

		// �跫�� ���δ밡 �跫������ ���� ������ �����ϴ��� Ȯ��
		bool func_���δ�_��������(pk::unit@ src_unit, pk::unit@ dst_unit, int strategy_id, int controller_index)
		{
			// �⺻���� : ����δ�� ���δ� �ĺ��� ���� �ƴ� ��� ����
			if (!pk::is_enemy(src_unit, dst_unit)) return false;

			// �⺻���� : ���δ��� �δ���°� �����°� �ƴ� ��� ����
			if (dst_unit.status != �δ����_���) return false;

			// �������� : ���δ��� ������ ���غ��� �̸��� ��� ����
			if (���δ�_��������_����[controller_index])
			{
				if (int(dst_unit.troops) < ���δ�_���غ���[controller_index]) return false;
			}

			// �������� : ���δ��� ����� ���ر�� �̸��� ��� ����
			if (���δ�_�������_����[controller_index])
			{
				if (int(dst_unit.energy) < ���δ�_���ر��[controller_index]) return false;
			}

			// �������� : ���δ��� Ư�� �δ�ɷ��� ���شɷ� �̸��� ��� ����
			if (���δ�_�ɷ�����_����[controller_index])
			{
				if (int(dst_unit.attr.stat[���δ�_����ɷ�]) < ���δ�_���شɷ�[controller_index]) return false;
			}

			// �������� : ���δ��� �δ������� �������� ������ ��� ����
			if (���δ�_��������_����[controller_index])
			{
				int weapon_id = dst_unit.weapon;
				int dst_tekisei = (weapon_id == ����_��) ? 0 : pk::get_tekisei(dst_unit, weapon_id);
				if (dst_tekisei <= ���δ�_��������[controller_index]) return false;
			}

			// �������� : ��庰 ����δ��� ���δ뿡 ���� �跫�� ����Ȯ�� Ȯ��
			int success_chance = get_success_chance(src_unit, dst_unit.pos, strategy_id);
			if (����Ȯ��_������[controller_index] == /*����������*/1)
			{
				// ��� 1 : ����Ȯ���� �������� ���� ��� ����
				/// ���� : '���1'�� ��� ������ ����Ǵ� ���δ뿡�Ը� ����
				if (!pk::rand_bool(success_chance)) return false;

			/**
				[ ���� ]

				'206 �跫 ���� Ȯ��.cpp' ������ ���� ���� �����δ� �跫�� ���ĵǴ� ��� ������ ����Ȯ���� 0�� ��ȯ�ǹǷ�
				�跫�� �������� ��ü�� ����Ȯ�� ��������(is_success)�� �Ǵ��ϸ� �����
				�׷��� '206 �跫 ���� Ȯ��.cpp'�� �����ϴ� ��� ���� ������ ����� Ȯ�������� �߰�
			*/
				// ���δ��� ����δ뿡 ���� �跫�� ���ĵǴ� ��� ����
				bool is_detected = strategy_is_detected(src_unit, dst_unit.pos, strategy_id);
				if (is_detected) return false;
			}
			else if (����Ȯ��_������[controller_index] == /*Ȯ��������*/2)
			{
				// ��� 2 : ����Ȯ���� ����Ȯ�� �̸��� ��� ����
				/// ���� : '���2'�� ��� Ȯ���� ����Ǵ� ���δ뿡�Ը� ����
				if (success_chance < �������_����Ȯ��[controller_index]) return false;
			}

			return true;
		}

		// ����δ밡 �̵��� ���δ� ��ó�� �ĺ���ǥ ��ȯ (��, �̵��� �ʿ��� ��� �˻�)
		pk::point get_pos_to_move(pk::unit@ src_unit, pk::force@ src_force, pk::unit@ dst_unit, int strategy_range, int controller_index)
		{
			if (�����_serach_pos_to_move)
			{
				string src_unit_name = pk::decode(pk::get_name(src_unit));
				pk::message_box(pk::encode("�̵�������ǥ Ȯ�ν��� : "+src_unit_name));
			}

			// �跫 ���δ� ��ó�� ����δ밡 �̵��� �ĺ���ǥ �˻� (�� �Ÿ����� �˻�)
			array<pk::point> pos_to_move_arr(0);
			int longest_distance = 0;
			array<pk::point> range_arr = pk::range(dst_unit.pos, 1, strategy_range);
			for (int i = int(range_arr.length) - 1; i >= 0; i--)
			{
				pk::point pos_to_move = range_arr[i];
				if (!pk::is_valid_pos(pos_to_move)) continue;

				// �⺻���� : ����δ밡 �̵��� �ĺ���ǥ�� ����δ��� ��ǥ�� ������ ��� ����
				if (pos_to_move == src_unit.pos) continue;

				// �⺻���� : ����δ밡 �̵��� �ĺ���ǥ�� �ǹ� �Ǵ� �δ밡 �����ϴ� ĭ�� ��� ����
				pk::hex@ hex = pk::get_hex(pos_to_move);
				if (hex.has_building) continue;
				if (hex.has_unit) continue;

				// �⺻���� : ����δ밡 �̵��� �ĺ���ǥ�� ������ ��ȿ���� �ʰų� ������ �Ұ����� ������ ��� ����
				int terrain_id = hex.terrain;
				if (!pk::is_valid_terrain_id(terrain_id)) continue;
				if (!pk::is_enabled_terrain(terrain_id)) continue;

				// �⺻���� : ����δ밡 �̵��� �ĺ���ǥ�� �̵��� �Ұ����� ��ǥ�� ��� ����
				/// ���� : pk::get_movable_pos() �Լ����� '����.xml', '169 ���� �̵� ���� ����.cpp'�� �̵����� ���� ���� ������ ��� �ݿ��� ����
				array<pk::point> movable_pos_arr = pk::get_movable_pos(src_unit);
				if (movable_pos_arr.find(pos_to_move) < 0) continue;

				if (�����_serach_pos_to_move)
				{
					string terrain_damage_type_name = "����";
					int terrain_damage_type = int(pk::core["����"][terrain_id]["��������"]);
					if      (terrain_damage_type == 1) terrain_damage_type_name = "��õ";
					else if (terrain_damage_type == 2) terrain_damage_type_name = "������";
					range_pos_ = pos_to_move;
					pk::scene(cast<pk::scene_t@>(function(){pk::highlight(main.range_pos_, true);}));
					pk::message_box(pk::encode("�������� : "+terrain_damage_type_name));
					pk::scene(cast<pk::scene_t@>(function(){pk::remove_all_highlights();}));
				}

			/**
				[ ���� ] �������� ����

				1. �������ش� �����౺ �ⱳ������ �Ǿ� ���� ���� ��쿡 ����
				2. ������ �������� �� - ����(0), ��õ(1), ������(2) ('����.xml' ����)
			*/
				// �������� : ����δ밡 �̵��� �ĺ���ǥ�� ������ �������ظ� �Դ� ������ ��� �̵��� ������� Ȯ��
				if (�ĺ��̵���ǥ_�˻���_����������ǥ_����[controller_index])
				{
					// ����δ밡 �̵��� �ĺ���ǥ�� ������ �������ظ� �Դ� ������ ��� ����
					int terrain_damage_type = int(pk::core["����"][terrain_id]["��������"]);
					if (!pk::has_tech(src_force, �ⱳ_�����౺) and terrain_damage_type != /*�������� �� : ����*/0) continue;
				}

				// �������� : ����δ밡 �̵��� �ĺ���ǥ�� �������� ��� ����
				if (�ĺ��̵���ǥ_�˻���_��������ǥ_����[controller_index])
				{
					if (pk::is_on_fire(pos_to_move)) continue;
				}

				// �������� : ����δ밡 �̵��� �ĺ���ǥ�� Ư���ü��� ���� �ȿ� ��ġ�ϴ� ��� ����
				if (�ĺ��̵���ǥ_�˻���_�ü�������ǥ_����[controller_index])
				{
					if (is_in_facility_range(src_unit, pos_to_move)) continue;
				}

				// ������ : ����δ��� ��ǥ�� ����δ밡 �̵��� �ĺ���ǥ �� �Ÿ��� ���� �� (�� �Ÿ� �켱)
				int curr_distance = pk::get_distance(src_unit.pos, pos_to_move);
				if (curr_distance < longest_distance) continue;

				pos_to_move_arr.insertLast(pos_to_move);
				longest_distance = curr_distance;
			}

			if (int(pos_to_move_arr.length) == 0) return -1;
			return pos_to_move_arr[pk::rand(int(pos_to_move_arr.length))];
		}

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	/**
		[ ���� ] �跫���� �⺻����

		1. ����δ� �Һ��� ó��
		2. �跫ȿ��
		 1) ����δ� �跫����ȿ��
		 2) �跫���� �� ����δ� �� ����ǥ(�ǹ�, �δ�) �跫����ȿ��
		 3) �跫���� �� ����δ� �� ����ǥ(�ǹ�, �δ�) �跫����ȿ��
		 4) ����δ� �跫��������
		  (1) �ⱳ ����Ʈ
		  (2) �ɷ� ����ġ(����)
		  (3) ����
		3. ����δ� �ൿ�Ϸ� ó��
		4. ����δ� ��ȯ Ư�� ó��
		5. ���δ� �ݰ� Ư�� ó��
	*/
		void func_�跫����(pk::unit@ src_unit, pk::force@ src_force, pk::unit@ dst_unit, int strategy_id, int energy_cost, int controller_index, bool is_deployed)
		{
			// ���غδ� �跫 �Һ��� ����
			pk::add_energy(src_unit, -energy_cost, false);

			// �跫 ���� (�Ϲݽ���)
			bool is_success = func_�跫ȿ��(src_unit, src_force, dst_unit, strategy_id, /*is_chain_reaction*/false, /*is_counter_plan*/false, controller_index, is_deployed);

		/**
			[ ���� ] ��ȯ Ư�� ����

			1. ��ȯ Ư��� ���� �跫 ���� ��󿡰� �跫�� �����ؾ� �����δ뿡 �ߵ���
			2. ��ȯ Ư�Ⱑ ����Ǵ� �跫 - ȭ��, ��ȭ, ����, ����, ���� (����, ����, ���, ���� ������)
			3. �跫 ȭ�� ���� �� ���� ��󺰷� ������� ��ȯ Ư�Ⱑ �ߵ��Ǵ� ��� (��������� ������ ��� ������ ����)
			 1) �δ� ���� �� �����δ� �ߵ�
			 2) �ǹ� ���� �� �����ǹ� �̹ߵ�(��, ������ ���� �ߵ�)
			 3) �δ� ���� �� �����ǹ� �̹ߵ�
			 4) �ǹ� ���� �� �����δ� �ߵ�
			4. �跫 ȭ���� ��ȯ �ߵ� �ÿ��� ��ȯƯ�� ���������� ��ȯ �ߵ� ��簡 ��µ��� ����
		*/
			// �Ϲݽ��� �跫�� �����߰� ����δ밡 ��ȯƯ�⸦ ������ ��� �߰� �跫 ���� (��ȯ�ߵ�)
			if (is_success and src_unit.has_skill(Ư��_��ȯ))
			{
				// ���δ��� �����δ� �˻�
				pk::unit@ dst_neighbor_unit = get_dst_neighbor_unit(src_unit, dst_unit);
				if (pk::is_alive(dst_neighbor_unit))
				{
					func_�跫ȿ��(src_unit, src_force, dst_neighbor_unit, strategy_id, /*is_chain_reaction*/true, /*is_counter_plan*/false, controller_index, is_deployed);
				}
			}

			// �Ϲݽ��� �跫�� �����߰� ���δ밡 �ݰ�Ư�⸦ ������ ��� �߰� �跫 ���� (�ݰ�ߵ�)
		/**
			[ ���� ] �ݰ� Ư�� ����

			1. ����δ� ��ȯ Ư�� �ߵ� �� ���δ� �ݰ� Ư�Ⱑ �ߵ����� ���� (��ȯ�� ���� �ݰ� �޾�ġ�� �ȵ�)
			2. ���δ� �ݰ� Ư�� �ߵ� �� ����δ� �ݰ� Ư�Ⱑ �ߵ����� ���� (�ݰ迡 ���� �ݰ� �޾�ġ�� �ȵ�)
			3. �ݰ� Ư�� �ߵ� �� �跫 ����δ뿡 �跫�� �����ֹǷ� ������ ���δ밡 ����δ밡 �� (���� ��뿡 ����)
			4. �ݰ� Ư�� �ߵ� �� ����δ�κ��� �õ� ���ߴ� �跫�� ���δ뿡�� �����ϰ� �����ֱ�� ������ �跫 ���� ȿ���� �⺻ ȿ���� �ٸ�
			 - �跫 ����δ��� �跫����ȿ�� �� ���, ȿ����, ȿ���� �ٸ� (������ ����)
		*/
			if (!is_success and dst_unit.has_skill(Ư��_�ݰ�))
			{
				// ���δ밡 ����δ뿡�� �޾Ҵ� �跫�� �ݴ�� ����
				func_�跫ȿ��(dst_unit, src_force, src_unit, strategy_id, /*is_chain_reaction*/false, /*is_counter_plan*/true, controller_index, is_deployed);
			}

			// ����δ� �ൿ�Ϸ�
			src_unit.action_done = true;
		}

	/**
		[ ���� ] �跫 ȿ��(�Լ�)

		1. ���� : pk::face_cutin(int id) / pk::face_cutin(unit@ unit)
		 - ũ��Ƽ�� �ߵ� �� ���
		 - �÷��̾� ���� �δ��� ��쿡�� ���
		 - '��Ÿ.xml'�� '�跫����' ������ 'true'�� ��쿡�� ���
		2. ���   : pk::msg_param ����ü �Ӽ��� Ȱ��
		 - msg ������ s11 ���� ��� ��ȯ ���� (�跫���� ���� - S11MSG01.s11 ����)
		3. ���� : pk::play_voice(person@ person)
		4. ȿ���� : pk::play_se(int id, pk::point pos) / pk::play_se(int id)
		5. ȿ�� : pk::create_effect(int id, pk::point pos)
		6. ó�� : ����ü �Ӽ��̳� �Լ� ���
		 - �跫���� �߰��� �ʿ��ؼ� ����ϴ� �Լ��� ���� ���, ȿ����, ȿ�� ���� ���ԵǴ� ��찡 ����
		7. ���   : pk::wait(int min, int max)
		 - ȿ�� �ִϸ��̼��� ��Ȱ�� ������ ���� ���
		 - pk::is_in_screen() �Լ� �ȿ��� ������� ������ �������� ���� �߻� ����
		 - pk::scene() �Լ� ������ ������� ������ ���۸� �߻� : pk::scene(cast<pk::scene_t@>(function(){pk::wait(1, 1000);}));
	*/
	/**
		[ ���� ] �跫�� ó�� ���� �Լ�

		1. ȭ��, ��ȭ, ���� : pk::create_fire(pk::point pos, int timer(�ϼ�), unit@ by = null, bool critical = false)
		 - ����ȿ�� : ȿ��(�� ���� �� ����), ȿ����(�� �Ҹ�)
		2. ����, ����, ���� : pk::set_status(unit@ self, unit@ by, int status, int time, bool sound = true)
		 - �Ű����� : self(��������δ�), by(�������ߺδ�), status(�δ����), time(����ī����), sound(ȿ������¿���)
		 - ����ȿ�� : �α׸޽���(���δ� ���º�ȭ), ���(���δ� ���º�ȭ), ȿ����(���δ� ���º�ȭ), ȿ��(���δ� ���º�ȭ)
		3. ����, ���� : pk::attack(unit@ unit, hex_object@ target)
		4. ��� : 
		5. ���� : 
	*/
		bool func_�跫ȿ��(pk::unit@ src_unit, pk::force@ src_force, pk::unit@ dst_unit, int strategy_id, bool is_chain_reaction, bool is_counter_plan, int controller_index, bool is_deployed)
		{
			// ����δ� �� ���δ��� �跫���� ���� Ȯ�� (����, ���, ���� ����)
			/// ���� : ��ȯ �� �ݰ� Ư�� �ߵ� �� �⺻�����δ� �ش�Ư�� ���������� �跫ȿ���� ���õ� ��ü�� �� (������ ��� ���� ����)
			pk::person@ src_person = pk::get_person(src_unit.leader);
			pk::person@ dst_leader = pk::get_person(dst_unit.leader);
			if      (is_chain_reaction) @src_person = pk::get_person(src_unit.who_has_skill(Ư��_��ȯ));
			else if (is_counter_plan)   @src_person = pk::get_person(src_unit.who_has_skill(Ư��_�ݰ�));

			// �跫 ũ��Ƽ�� ���� Ȯ��
			bool is_critical = pk::rand_bool(get_critical_chance(src_unit, dst_unit.pos, strategy_id));

			// ����δ��� �跫����ȿ�� : ����, ���, ����, ȿ����, ȿ��
			func_�跫����ȿ��_����δ�(src_unit, src_person, dst_leader, strategy_id, is_critical, is_chain_reaction, is_counter_plan);

			// ��庰 �跫 ����Ȯ�� �� ���Ŀ��� ����
			bool is_success = pk::rand_bool(get_success_chance(src_unit, dst_unit.pos, strategy_id));
			bool is_detected = strategy_is_detected(src_unit, dst_unit.pos, strategy_id);
			if (!is_chain_reaction and !is_counter_plan and ����Ȯ��_������[controller_index] == /*����������*/1)
			{
				/// ���� : '���1'�� ��� ���δ븦 �˻��� �� ����Ȯ���� �����ϴ� ��츸 �����߱� ������ ���⼭�� ������ �����ϴ� ������ ����
				///        (��, '���1'�̶�� �ص� ��ȯ�̳� �ݰ� Ư��� ���� �跫�� ������ ���� �޶��� ��� ���� ����Ȯ���� �ٽ� Ȯ����)
				is_success = true;
				is_detected = false;
			}

			/// ���� : �跫�� ���ĵǸ� ������ �������� ���ϹǷ� �跫�� �������� ��ü�� ����Ȯ�� ��������(is_success)�� �Ǵ��ϸ� ��
			if (is_success)
			{
				// ���δ��� �跫����ȿ�� : ���, ����, ȿ����, ȿ��, ó��
				func_�跫����ȿ��_���δ�(src_unit, dst_unit, dst_leader, strategy_id, is_critical);
			}
			else
			{
				// ���δ��� �跫����ȿ�� : ���, ����, ȿ����, ȿ��
				func_�跫����ȿ��_���δ�(dst_unit, dst_leader, is_detected);
			}

			// ����δ��� �跫�������� : �ⱳ����Ʈ, �ɷ°���ġ, ����
			/// ���� : �ⱳ, ����ġ, ���� ���� �⺻�����δ� �跫�� ������ ����δ븸 ȹ���� (��ȯ, �ݰ迡 ���� �跫 ���� �ÿ��� ����)
			func_�跫��������_����δ�(src_unit, src_force, dst_unit, is_success, is_critical, strategy_id);

			if (�����_strategy_success_info)
			{
				string src_force_name = pk::decode(pk::get_name(src_force));
				string src_unit_name = pk::decode(pk::get_name(src_unit));
				pk::building@ building = pk::get_building(pk::get_service(src_unit));
				string src_building_name = pk::is_alive(building) ? pk::decode(pk::get_name(building)) : "����";
				string dst_unit_name = pk::decode(pk::get_name(dst_unit));
				string src_person_name = pk::decode(pk::get_name(src_person));
				string strategy_info = (strategy_id == �跫_����) ? "����" : "����";
				string success_info = (is_success) ? "����" : "����";
				string skill_info = (is_chain_reaction) ? "��ȯ�ߵ�" : (is_counter_plan ? "�ݰ�ߵ�" : "�Ϲݽ���");
				pk::info(skill_info+" : "+src_force_name+"�� "+src_person_name+"("+(is_deployed ? "�����δ�("+src_building_name+")" : "�����δ�")+")");
				pk::info(src_unit_name+"�� "+dst_unit_name+"���� "+strategy_info+" "+success_info+" ("+skill_info+")");
			}

			return is_success;
		}

		void func_�跫����ȿ��_����δ�(pk::unit@ src_unit, pk::person@ src_person, pk::person@ dst_leader, int strategy_id, bool is_critical, bool is_chain_reaction, bool is_counter_plan)
		{
			if (pk::is_in_screen(src_unit.pos))
			{
				// ����δ� ��ȯ�ߵ� �� �߰� ���
				if (is_chain_reaction)
				{
					// ����δ� ��ȯ�ߵ� ��� (��ȯƯ�� ��������)
					say_message(7574, /*p0*/src_person, /*p1*/null, /*u0*/null, /*p0_u*/src_unit);

					// ���
					pk::scene(cast<pk::scene_t@>(function(){pk::wait(1, 500);}));
				}

				// ����δ� �跫���� ����
			/**
				[ ���� ] ���� ����

				1. �÷��̾� ����(���ӱ��� ����) �δ밡 ũ��Ƽ�� �ߵ� �ÿ��� ��µ�
				2. ���� ��� �� ��µǴ� ������ ����
				 1) �Ϲݽ��� : �δ��� ����
				 2) ��ȯ�ߵ� : �δ� �� ��ȯƯ�� ��������
				 3) �ݰ�ߵ� : �δ��� ����
			*/
				if (bool(pk::core["�跫����"]) and is_critical and src_unit.is_player())
				{
					// ��ȯ�ߵ� ��
					if (is_chain_reaction)
					{
						// ���� ����
						pk::play_voice(33, src_person);

						// ���� ȿ����
						pk::play_se(25);

						// ���� ȿ��
						int cutin_id = pk::get_cutin_id(src_person);
						pk::face_cutin(cutin_id);
					}

					// �Ϲݽ��� �� �ݰ�ߵ� ��
					else
					{
						// ���� ȿ��
						pk::face_cutin(src_unit);	// ����, ȿ���� ����
					}
				}

				// ����δ� �跫���� ���
				int msg_id = (is_counter_plan) ? 7575 : (strategy_id == �跫_���� ? 7108 : 7095);
				pk::person@ person1 = (is_counter_plan) ? null : dst_leader;
				say_message(msg_id, /*p0*/src_person, /*p1*/person1, /*u0*/null, /*p0_u*/src_unit);

				// ����δ� �跫���� ����
				pk::play_voice(50, src_person);

				// ����δ� �跫���� ȿ����
				if      (is_counter_plan) pk::play_se(91, src_unit.pos);
				else if (is_critical)     pk::play_se(79);
				else                      pk::play_se(57, src_unit.pos);

				// ����δ� �跫���� ȿ��
				int effect_id = (is_counter_plan) ? 77 : (is_critical ? 79 : 58);
				pk::create_effect(effect_id, src_unit.pos);

				// ���
				pk::scene(cast<pk::scene_t@>(function(){pk::wait(1, 1000);}));
			}
		}

		void func_�跫����ȿ��_���δ�(pk::unit@ src_unit, pk::unit@ dst_unit, pk::person@ dst_leader, int strategy_id, bool is_critical)
		{
			if (pk::is_in_screen(dst_unit.pos))
			{
				// ���δ� �跫���� ���
				int msg_id = (strategy_id == �跫_����) ? 5846 : 5860;
				pk::unit@ unit0 = (strategy_id == �跫_����) ? null : dst_unit;
				say_message(msg_id, /*p0*/dst_leader, /*p1*/null, /*u0*/unit0, /*p0_u*/dst_unit);	// pk::set_status() �Լ��� ���Ե� ���

				// ���δ� �跫���� ����
				int voice_id = pk::rand_bool(50) ? 66 : 68;
				pk::play_voice(voice_id, dst_leader);

				// ���δ� �跫���� ȿ����1
				int sound1_id = dst_unit.is_player() ? 3 : 2;
				pk::play_se(sound1_id);	// pk::set_status() �Լ��� ���Ե� ȿ����

				// ���δ� �跫���� ȿ����2
				int sound2_id = (strategy_id == �跫_����) ? 39 : 40;
				pk::play_se(sound2_id, dst_unit.pos);	// pk::set_status() �Լ��� ���Ե� ȿ����
			}

			// ���δ� �跫���� ȿ��, ó��
			/// ���� : ���� �� ���� �跫 �������� ���� ����ī���ʹ� ũ��Ƽ�� �̹ߵ��ÿ��� Ȯ���� ���� 2, 1�� ������ (Ȯ�� �̻�)
			int status = (strategy_id == �跫_����) ? �δ����_ȥ�� : �δ����_����;
			int time = (is_critical) ? 5 : (pk::rand_bool(20) ? 2 : 1);
			bool sound = false;
			pk::set_status(dst_unit, src_unit, status, time, sound);	// �α׸޽���, ���(���δ�), ȿ����(���δ�), ȿ�� ����

			if (pk::is_in_screen(dst_unit.pos))
			{
				// ���
				pk::scene(cast<pk::scene_t@>(function(){pk::wait(1, 500);}));
			}
		}

		void func_�跫����ȿ��_���δ�(pk::unit@ dst_unit, pk::person@ dst_leader, bool is_detected)
		{
			if (pk::is_in_screen(dst_unit.pos))
			{
				// ���δ� �跫���� ���
				say_message(7206, /*p0*/dst_leader, /*p1*/null, /*u0*/null, /*p0_u*/dst_unit);

			/**
				[ ���� ] �跫�� ���� ���� ����

				1. �跫�� ���ĵǴ� ��쿡�� �跫��� ȿ���� �ߵ��ǹǷ� �ܼ��� �跫�� ������ ���ʹ� �ٸ�
				2. Ư�⺰ ���İ� ������ �跫 (206 �跫 ���� Ȯ��.cpp ����)
				 - �Ż� �� ���� Ư���� ��쿡�� ����δ��� ��ǥ���(�δ�)�� ���� ���¿��� ������ �����ؾ� ���� �ߵ�
				 1) �Ż� : ȭ��, ����, ����, ����, ����
				 2) ���� : ȭ��, ����, ����, ����, ����
				 3) ���� : ȭ��, ����, ����, ����, ����, ���
				 4) ȭ�� : ȭ��
				 5) ��� : ����, ����
				 6) ���� : ����
				 7) ħ�� : ����
			*/
				if (is_detected)
				{
					// ���δ� �跫����(����) ����
					pk::play_voice(69, dst_leader);

					// ���δ� �跫����(����) ȿ����
					pk::play_se(95, dst_unit.pos);

					// ���δ� �跫����(����) ȿ��
					pk::create_effect(84, dst_unit.pos);
				}
				else
				{
					// ���δ� �跫����(�ܼ�����) ����
					pk::play_voice(70, dst_leader);

					// ���δ� �跫����(�ܼ�����) ȿ����, ȿ�� : ����
				}

				// ���
				pk::scene(cast<pk::scene_t@>(function(){pk::wait(1, 500);}));
			}
		}

		void func_�跫��������_����δ�(pk::unit@ src_unit, pk::force@ src_force, pk::unit@ dst_unit, bool is_success, bool is_critical, int strategy_id)
		{
			// �ⱳ ����Ʈ ȹ��
			int tech_point = (is_success) ? 10 : 0;
			pk::add_tp(src_force, tech_point, dst_unit.pos); // ȿ��, ȿ���� ����

			// �ɷ� ����ġ ��� : ����
			int stat_exp = (is_success) ? 3 : 1;
			pk::add_stat_exp(src_unit, ����ɷ�_����, stat_exp);

			// ���� ���
			int kouseki_point = (is_success) ? (is_critical ? 200 : 100) : 20;
			pk::add_kouseki(src_unit, kouseki_point);
		}

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		// �Ϲݰ��ӿ��� ��ȯ : ��������, Ʃ�丮��, �̼� ���� ���� �ƴ� ��
		bool is_normal_game()
		{
			return (!pk::is_campaign() and !pk::is_mission_running());
		}

		// �δ��� ������ü ���� ��ȯ
		int get_controller_index(pk::unit@ unit)
		{
			return (unit.is_player() ? /*�÷��̾� ���ӱ���*/0 : /*��ǻ��*/1);
		}

		// Ư�� �δ�κ��� �����Ÿ� �̳��� �����ϴ� ���� �δ�� ��ȯ
		int func_�δ��ó_���δ��(pk::unit@ unit, int distance)
		{
			int enemy_units = 0;
			array<pk::point> range = pk::range(unit.pos, 1, distance);
			for (int i = 0; i < int(range.length); i++)
			{
				pk::unit@ enemy_unit = pk::get_unit(range[i]);
				if (!pk::is_alive(enemy_unit)) continue;
				if (!pk::is_enemy(unit, enemy_unit)) continue;

				enemy_units++;
			}

			return enemy_units;
		}

		// �跫 ����δ� �� ���δ��� ��� ��� : msg ������ s11 ���� ��� ��ȯ (�跫���� ���� - S11MSG01.s11 ����)
		void say_message(int msg_id, pk::person@ p0, pk::person@ p1, pk::unit@ u0, pk::unit@ p0_u)
		{
			pk::msg_param msg_param(msg_id, p0, p1);
			@msg_param.unit[0] = @u0;
			pk::say(pk::get_msg(msg_param), p0, p0_u);
		}

		// �跫 ����δ��� �Һ��� ��ȯ
		int get_energy_cost(pk::unit@ src_unit, int strategy_id)
		{
			return cast<pk::func205_t>(pk::get_func(205))(src_unit, strategy_id);
		}

		// �跫 ����δ��� ���δ뿡 ���� ����Ȯ�� ��ȯ
		int get_success_chance(pk::unit@ src_unit, pk::point dst_pos, int strategy_id)
		{
			return cast<pk::func206_t>(pk::get_func(206))(src_unit, src_unit.pos, dst_pos, strategy_id).first;
		}

		// �跫 ���δ��� ����δ뿡 ���� ���Ŀ��� ��ȯ
		bool strategy_is_detected(pk::unit@ src_unit, pk::point dst_pos, int strategy_id)
		{
			return cast<pk::func206_t>(pk::get_func(206))(src_unit, src_unit.pos, dst_pos, strategy_id).second;
		}

		// �跫 ����δ��� ũ��Ƽ�� Ȯ�� ��ȯ
		int get_critical_chance(pk::unit@ src_unit, pk::point dst_pos, int strategy_id)
		{
			return cast<pk::func207_t>(pk::get_func(207))(src_unit, src_unit.pos, dst_pos, strategy_id);
		}

		// ���δ��� ������ǥ�� �����ϴ� ����δ��� ���δ� ��ȯ
		pk::unit@ get_dst_neighbor_unit(pk::unit@ src_unit, pk::unit@ dst_unit)
		{
			array<pk::unit@> dst_neighbor_unit_arr(0);
			array<pk::point> ring_arr = pk::ring(dst_unit.pos, 1);
			for (int i = 0; i < int(ring_arr.length); i++)
			{
				pk::point dst_neighbor_pos = ring_arr[i];
				pk::unit@ dst_neighbor_unit = pk::get_unit(dst_neighbor_pos);
				if (!pk::is_alive(dst_neighbor_unit)) continue;
				if (!pk::is_enemy(src_unit, dst_neighbor_unit)) continue;
				if (dst_neighbor_unit.status != �δ����_���) continue;

				dst_neighbor_unit_arr.insertLast(dst_neighbor_unit);
			}

			if (int(dst_neighbor_unit_arr.length) == 0) return null;
			return dst_neighbor_unit_arr[pk::rand(int(dst_neighbor_unit_arr.length))];
		}

		// ����δ밡 Ư�� ��ǥ���� �ü����� ���� �����ϴ��� ���� ��ȯ
		bool is_in_facility_range(pk::unit@ src_unit, pk::point pos)
		{
			array<int> ������_���� = {�ü�_�Ҿ�, �ü�_ȭ����, �ü�_��ȭ��, �ü�_ȭ��};
			array<int> ������_���� = {�ü�_ȭ��, �ü�_ȭ����, �ü�_��ȭ��, �ü�_����};

			/// ���� : �ü��� �ִ������ 0 �̻� 10 ���� ('�ü�.xml' ����)
			array<pk::point> range_arr = pk::range(pos, 1, 10);
			for (int pos_index = 0; pos_index < int(range_arr.length); pos_index++)
			{
				pk::point range_pos = range_arr[pos_index];
				pk::building@ building = pk::get_building(range_pos);
				if (!pk::is_alive(building)) continue;

				// ������ ȸ�Ǵ�� �ü��� �ƴϸ� ����
				/// ���� : ȸ�Ǵ�� �ü� �迭
				int facility_id = building.facility;
				pk::facility@ facility = pk::get_facility(facility_id);
				if (ȸ�Ǵ��_�ü�[facility.type].find(facility_id) < 0) continue;

				// ������ �ƴ� �ü��� ������ �Ʊ��� ��� ����
				if (facility.type != �ü�����_���� and !pk::is_enemy(src_unit, building)) continue;

				/// ���� : �ü��� �ִ�Ÿ��� ��ǥ�Ÿ��� ���ϴ� �� ������ ��쿡�� '�ִ�Ÿ�+1'�� ���ؾ� ��(���ð� �ʿ��� �� ĭ�� ������ �����ϱ� ����)
				int min_range = facility.min_range;
				int max_range = (facility_id == �ü�_����) ? facility.max_range + 1 : facility.max_range;
				int distance = pk::get_distance(pos, range_pos);
				bool auto_attack = bool(pk::core["�ü�"][facility_id]["�ڵ�����"]);

				// �δ밡 �ü����� ���� �����ϴ��� Ȯ��
				if (distance >= min_range and distance <= max_range)
				{
					// �δ밡 �ü����� ���� �ִ��� Ȯ�� : ��������, ������ ����(�Ҿ�, ȭ����, ��ȭ��, ȭ��)
					if (facility_id == �ü�_�������� or ������_����.find(facility_id) >= 0) return true;

					// �δ밡 �ü����� ���� �ְ� �ش�ü��� �������� ��ġ�ϴ��� Ȯ�� : ������ ����(ȭ��, ȭ����, ��ȭ��, ����)
					else if (������_����.find(facility_id) >= 0)
					{
						// 5ĭ �̳��� Ȯ��
						int direction = pk::get_direction(pos, range_pos);
						if (distance <= 5 and ���⺰_������_��ǥ����[direction].find(pos_index) >= 0) return true;
					}

					// �δ밡 �ü����� ���� �ְ� �ش�ü��� �ڵ������� Ȱ��ȭ�Ǿ� �ִ��� Ȯ��
					/// ���� : ȸ�Ǵ�� �ü� �迭
					else if (auto_attack) return true;
				}
			}

			return false;
		}

		// ���δ� �ֺ��� �����ϴ� ����δ��� ���� �δ�� �� �����, �Ʊ� �δ�� �� ����� ��ȯ
		array<int> func_���δ�_��ó�δ�_��������_�迭(pk::unit@ src_unit, pk::unit@ dst_unit, int distance)
		{
			array<int> units_and_troops_info(4, 0);
			array<pk::point> range = pk::range(dst_unit.pos, 1, distance);
			for (int i = 0; i < int(range.length); i++)
			{
				pk::unit@ unit = pk::get_unit(range[i]);
				if (!pk::is_alive(unit)) continue;
				if (@unit == @src_unit) continue;

				if (pk::is_enemy(src_unit, unit))
				{
					// �迭 ���� 0 : ���δ� �ֺ��� �����ϴ� ����δ��� ���� �δ��
					units_and_troops_info[0]++;

					// �迭 ���� 1 : ���δ� �ֺ��� �����ϴ� ����δ��� ���� �����
					units_and_troops_info[1] += unit.troops;
				}
				else
				{
					// �迭 ���� 2 : ���δ� �ֺ��� �����ϴ� ����δ��� �Ʊ� �δ��
					units_and_troops_info[2]++;

					// �迭 ���� 3 : ���δ� �ֺ��� �����ϴ� ����δ��� �Ʊ� �����
					units_and_troops_info[3] += unit.troops;
				}
			}

			return units_and_troops_info;
		}

	/**
		[ ���� ] ���� ������ �������

		1. ������ ��������� �����ϴ� ���δ뿡�� �켱������ �跫�� ����
		2. ������ ��� �Ǵ�����
		 1) �������� : ���δ� ��ǥ������ ���ð� ����δ� ������ �Ʊ� ������ ��
		 2) �Ÿ����� : ���δ� ��ǥ������ ���ÿ� ���δ� ������ �Ÿ��� �����Ÿ� �̸��� ��
		 3) �������� : ���δ��� ������ ���������� ��
		 4) �������� : ���δ� ��ǥ���� ������ �������� �ش絵�� �ִ볻���� �������� ������ ��
	*/
		bool func_������_�������_��������(pk::unit@ src_unit, pk::unit@ dst_unit)
		{
			pk::city@ area_city = pk::get_city(pk::get_city_id(dst_unit.pos));
			if (!pk::is_alive(area_city)) return false;

			// �������� : ���δ� ��ǥ������ ���ð� ����δ� ������ ���� ������ ��� ����
			if (pk::is_enemy(area_city, src_unit)) return false;

			// �Ÿ����� : ���δ� ��ǥ������ ���ÿ� ���δ� ������ �Ÿ��� �����Ÿ� �̻��� ��� ����
			/// ���� : ���ð� �ʿ��� �� ĭ�� ������ �����ϱ� ������ ���� ���ϴ� �Ÿ��� ���ϱ� ���ؼ��� -1�� ���־�� ��
			int distance = pk::get_distance(area_city.get_pos(), dst_unit.pos) - 1;
			if (distance >= ������_�������_���ذŸ�) return false;

			// �������� : ���δ��� ������ �������Ⱑ �ƴ� ��� ����
			/// ���� : �������� ���� �����ؿ��� ��찡 �����Ƿ� ���� ���������� ���Ⱑ �ƴ� ���󺴱�� �ݿ�
			int dst_ground_wpn_id = pk::get_ground_weapon_id(dst_unit);
			int dst_heishu = pk::equipment_id_to_heishu(dst_ground_wpn_id);
			if (dst_heishu != ����_����) return false;

			// �������� : ���δ� ��ǥ���� ������ �������� �ش絵�� �ִ볻���� ���������� �ʰ��ϴ� ��� ����
			if (int(pk::get_hp(area_city)) > int(area_city.max_hp) * ������_�������_���س������� / 100) return false;

			// �������� : ���δ� ��ǥ���� ������ ������ ���ذ��� �ʰ��ϴ� ��� ����
			if (int(area_city.troops) > ������_�������_���غ���) return false;

			return true;
		}

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	}

	Main main;
}