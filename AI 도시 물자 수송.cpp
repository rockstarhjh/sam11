/*
	@���� : masterpiecek
	@���� : ���� AI������ �������� ���õ� ���� ���� ������ ��Ȱ�ϰ� �̷������ �ʴ� �κ��� ����
*/

namespace AI����_���ڼ���
{

/// ============================================ < ���� ���� > ============================================

/// [ ���۱⺻���� ���� ]

	// ���� ������ü�� ��� ���뿩�� ����
	const array<bool> AI_���ù��ڼ���_���� = {/*�÷��̾� ���ӱ���*/true, /*��ǻ��*/true};

	// ���� �ó������� ��������� ���ذ� �̸��� ��� �������� ����
	const int ���۱⺻����_������� = 6;

	// ������ ���ü��� ���ذ� �̸��� ��� �������� ����
	const int ���۱⺻����_���µ��ü� = 3;

/// -------------------------------------------------------------------------------------------------------

/// [ ���۰������� ���� ] : ���ۺδ밡 ������ ������ ����

	// ���ۺδ밡 ������ ���÷κ��� ���ذŸ� �̳��� ���ñ����� ���δ밡 �����ϴ� ��� ���δ�� �� ��������� ���ذ� �̻��̶�� �������� ����
	const array<bool> ���۰�������_���δ�����_���� = {/*�÷��̾� ���ӱ���*/true, /*��ǻ��*/true};
	const int ���۰�������_�������δ�Ÿ� = 12;
	const int ���۰�������_�������δ�� = 2;
	const int ���۰�������_����������� = 4000;

	// ���ۺδ밡 ������ ������ �ִ뺴�� ��� ���纴���� ����(%)�� ���ذ� �̸��� ��� ����
	const array<bool> ���۰�������_��������_���� = {/*�÷��̾� ���ӱ���*/true, /*��ǻ��*/true};
	const array<int> ���۰�������_��������_���� = {/*�÷��̾� ���ӱ���*/50, /*��ǻ��*/50};

	// ���ۺδ밡 ������ ������ ���纴�� ��� ���纴���� ����(%)�� ���ذ� �̸��� ��� ����
	const array<bool> ���۰�������_��������_���� = {/*�÷��̾� ���ӱ���*/true, /*��ǻ��*/true};
	const array<int> ���۰�������_��������_���� = {/*�÷��̾� ���ӱ���*/150, /*��ǻ��*/150};

/// -------------------------------------------------------------------------------------------------------

/// [ �����ʿ����� ���� ] : ������ ���� ������ ����

	// ������ ���� ���÷κ��� ���ذŸ� �̳��� ���ñ����� ���δ밡 �����ϴ� ��� ���δ� �� ��������� ���ذ� �̻��̶�� ���۹��� ����
	const array<bool> �����ʿ�����_���δ�����_���� = {/*�÷��̾� ���ӱ���*/true, /*��ǻ��*/true};
	const int �����ʿ�����_�������δ�Ÿ� = 12;
	const int �����ʿ�����_�������δ�� = 3;
	const int �����ʿ�����_����������� = 6000;

	// ������ ���� ������ �ִ뺴�� ��� ���纴���� ������ ���ذ��� �ʰ��ϴ� ��� ���۹��� ����
	const array<bool> �����ʿ�����_��������1_���� = {/*�÷��̾� ���ӱ���*/true, /*��ǻ��*/true};
	const array<int> �����ʿ�����_��������1_���� = {/*�÷��̾� ���ӱ���*/50, /*��ǻ��*/50};

	// ���ۺδ밡 ������ ������ ���纴�� ��� ������ ���� ������ ���纴���� ������ ���ذ��� �ʰ��ϴ� ��� ���۹��� ����
	const array<bool> �����ʿ�����_��������2_���� = {/*�÷��̾� ���ӱ���*/true, /*��ǻ��*/true};
	const array<int> �����ʿ�����_��������2_���� = {/*�÷��̾� ���ӱ���*/50, /*��ǻ��*/50};

	// ������ ���� ���ð� ���� ���ذ� �߻��߰ų� �߻��� ������ ��� ���۹��� ���� (���û��°� ������ ��� ���� ���뿩�� ����)
	const array<bool> �����ʿ�����_��������_���� = {/*�÷��̾� ���ӱ���*/true, /*��ǻ��*/true};
	const array<bool> ��������_���浵��_�������� = {/*�÷��̾� ���ӱ���*/true, /*��ǻ��*/true};

	// ������ ���� ���ð� �޶ѱ� ���ذ� �߻��߰ų� �߻��� ������ ��� ���۹��� ���� (���û��°� ������ ��� ���� ���뿩�� ����)
	const array<bool> �����ʿ�����_�޶ѱ�����_���� = {/*�÷��̾� ���ӱ���*/true, /*��ǻ��*/true};
	const array<bool> �޶ѱ�����_���浵��_�������� = {/*�÷��̾� ���ӱ���*/true, /*��ǻ��*/true};

/// -------------------------------------------------------------------------------------------------------

/// [ ���ۺδ� ���� ���� ]

	// ���ۺδ��� ���� ���� �� ���� �漺�� �̸��� ������ ����
	const int ���ۺδ�_�����ĺ�_�����漺�� = 85;

	// ���ۺδ� ���� ���� �� �ĺ����� �� ���Ư�� ���������� �ֿ켱 �������� �������� ����
	const bool ���ۺδ�����_���Ư��_�ݿ� = true;

	// ���ۺδ� ���� ���� �� �ĺ����� �� �ɷ�ġ�� ���� ������ �켱 �����Կ� �־� ������ ����ɷ� ����
	const int ���ۺδ�����_����ɷ� = ����ɷ�_��ġ;

	// ���ۺδ밡 ������ ������ �����׸� ���ۺ���(%) ����
	const array<int> ���ۺ���_��       = {/*�÷��̾� ���ӱ���*/50, /*��ǻ��*/50};
	const array<int> ���ۺ���_����     = {/*�÷��̾� ���ӱ���*/50, /*��ǻ��*/50};
	const array<int> ���ۺ���_����     = {/*�÷��̾� ���ӱ���*/50, /*��ǻ��*/50};
	const array<int> ���ۺ���_�Ϲݺ��� = {/*�÷��̾� ���ӱ���*/50, /*��ǻ��*/50};
	const array<int> ���ۺ���_�������� = {/*�÷��̾� ���ӱ���*/50, /*��ǻ��*/50};
	const array<int> ���ۺ���_�Լ�     = {/*�÷��̾� ���ӱ���*/50, /*��ǻ��*/50};

	// ���ۺδ밡 ������ ���ð� ��������� ��� �����׸� �ּ������� ����
	const array<int> �ּ�������_����_��       = {/*�÷��̾� ���ӱ���*/2000, /*��ǻ��*/2000};
	const array<int> �ּ�������_����_����     = {/*�÷��̾� ���ӱ���*/20000, /*��ǻ��*/20000};
	const array<int> �ּ�������_����_����     = {/*�÷��̾� ���ӱ���*/80000, /*��ǻ��*/80000};
	const array<int> �ּ�������_����_�Ϲݺ��� = {/*�÷��̾� ���ӱ���*/10000, /*��ǻ��*/10000};
	const array<int> �ּ�������_����_�������� = {/*�÷��̾� ���ӱ���*/3, /*��ǻ��*/3};
	const array<int> �ּ�������_����_�Լ�     = {/*�÷��̾� ���ӱ���*/3, /*��ǻ��*/3};

	// ���ۺδ밡 ������ ���ð� �������� ��� �����׸� �ּ������� ����
	const array<int> �ּ�������_���_��       = {/*�÷��̾� ���ӱ���*/2000, /*��ǻ��*/2000};
	const array<int> �ּ�������_���_����     = {/*�÷��̾� ���ӱ���*/10000, /*��ǻ��*/10000};
	const array<int> �ּ�������_���_����     = {/*�÷��̾� ���ӱ���*/40000, /*��ǻ��*/40000};
	const array<int> �ּ�������_���_�Ϲݺ��� = {/*�÷��̾� ���ӱ���*/5000, /*��ǻ��*/5000};
	const array<int> �ּ�������_���_�������� = {/*�÷��̾� ���ӱ���*/0, /*��ǻ��*/0};
	const array<int> �ּ�������_���_�Լ�     = {/*�÷��̾� ���ӱ���*/0, /*��ǻ��*/0};

/// =======================================================================================================

	/// ���û��� ����
	const int ���û���_�Ĺ� = 0, ���û���_��� = 1, ���û���_���� = 2;

	class Main
	{

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		// AI ��ũ��Ʈ �Լ� ü���� ���� ���� �ڵ鷯 �����
		pk::func261_t@ prev_callback_261;

	/**
		[ �߰� ������� ]

		Ư�� ���� �� �ױ��� ���ۺδ��� �̵���ο� ���ԵǾ� �ִµ� �������̶�� ���ۿ� ������ �ް� ��
		(������ �̵����� ������ ���� �޶���)
	*/

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		Main()
		{
			// 261�Լ� ���� �ڵ鷯 ����, �Լ� �ʱ�ȭ, �Լ� ������
			@prev_callback_261 = cast<pk::func261_t@>(pk::get_func(261));
			pk::reset_func(261);
			pk::set_func(261, pk::func261_t(func261));
		}

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		/**
		@param  force : AI ����
		@return �ڽ��� ó���ߴٸ� true. ��ǻ�Ϳ��� �ñ���� false.
		*/
		/// ���� : AI ��ũ��Ʈ �Լ�(261)�� ����ϴ� ��쿡�� �÷��̾� 1������ �̹� ������ ������
		/// ���� : 261�Լ��� ��ü AI ��ũ��Ʈ�̱� ������ ���ۺδ븦 ������Ų �� ���� �ڵ鷯�� ������ ü�����־�� ��
		bool func261(pk::force@ force)
		{
			supplies_transport_of_AI_city(force);

			if (prev_callback_261 is null) return false;
			return prev_callback_261(force);
		}

		void supplies_transport_of_AI_city(pk::force@ force)
		{
			// �̺�Ʈ �߻��� ���� �⺻���� Ȯ�� : �������, ���µ��ü� ��
			int controller_index = get_controller_index(force);
			if (!func_���۱⺻����_��������(force, controller_index)) return;

			for (int city_id = 0; city_id < ����_��; city_id++)
			{
				pk::city@ city = pk::get_city(city_id);
				if (!pk::is_alive(city)) continue;
				if (city.get_force_id() != force.get_id()) continue;

				// �⺻���� : // �÷��̾� 1���� ���� ����
				if (pk::is_player_controlled(city)) continue;

				// ���ۺδ밡 ������ ���ð� ������ �������� ���� Ȯ��
				pk::building@ building = pk::city_to_building(city);
				if (!func_���۰�������_��������(city, building, controller_index)) continue;

				// ���ۺδ밡 ������ ������ �ڼ��� �������� �� ���۹��� �ĺ����� �˻�
				array<pk::city@> neighbor_city_arr = func_���۹�������_�ĺ��˻�(city, controller_index);
				if (int(neighbor_city_arr.length) == 0) continue;

				// ���۹��� �ĺ����� �� �켱������ ���� ����
				neighbor_city_arr.sort(function(a, b){return main.func_���ð�_�켱����_��(a, b);});
				pk::city@ neighbor_city = neighbor_city_arr[0];
				if (!pk::is_alive(neighbor_city)) continue;

				// ���ۺδ밡 ������ ���÷κ��� ���۹��� ���÷� ���ۺδ� ����
				pk::building@ neighbor_building = pk::city_to_building(neighbor_city);
				func_���ۺδ�_����(city, building, neighbor_building, controller_index);
			}
		}

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		// �̺�Ʈ �߻��� ���� �⺻���� Ȯ��
		bool func_���۱⺻����_��������(pk::force@ force, int controller_index)
		{
			// �⺻���� : �Ϲݰ��� ���� Ȯ�� (��������, Ʃ�丮��, �̼� ���� ���� �ƴ� ��)
			if (!is_normal_game()) return false;

			// �⺻���� : �Ϲݼ��� ���� Ȯ�� (���弼�� ����)
			if (!pk::is_normal_force(force)) return false;

			// �������� : ������� ���� Ȯ��
			if (!AI_���ù��ڼ���_����[controller_index]) return false;

			// �������� : ���� �ó������� ��������� ���ذ� �̸��� ��� �������� ����
			if (pk::get_elapsed_months() < ���۱⺻����_�������) return false;

			// �������� : ������ ���ü��� ���ذ� �̸��� ��� �������� ����
			if (pk::get_city_count(force) < ���۱⺻����_���µ��ü�) return false;

			return true;
		}

		// ���ۺδ밡 ������ ���ð� ������ �������� ���� Ȯ��
		bool func_���۰�������_��������(pk::city@ city, pk::building@ building, int controller_index)
		{
			// �⺻���� : ���ۺδ밡 ������ ������ ���û��°� �Ĺ�(���ðŸ� 2 �̳��� �����ð� ���� ���)�� ��� ����
			int city_status = get_city_status(city);
			if (city_status == ���û���_�Ĺ�) return false;

			// �⺻���� : ���ÿ� �ൿ������ ������ ���� ��� ����
			if (pk::get_idle_person_list(building).count == 0) return false;

			// �⺻���� : ������ ���۸�� ������ ���� �ൿ���� ������� ���� ��� ����
			/// ���� : ���� ����� �ൿ�� �Ҹ��� 10
			if (!ap_is_enough(city, 10, �ü�_�����)) return false;

			// �������� : ���ۺδ밡 ������ ���÷κ��� �����Ÿ� �̳��� ���ñ����� ������ �̻��� ���δ� �� �������� �����ϴ� ��� ����
			if (���۰�������_���δ�����_����[controller_index])
			{
				int enemy_units = func_���ñ���_���δ��(city, ���۰�������_�������δ�Ÿ�);
				int enemy_troops = func_���ñ���_�������(city, ���۰�������_�������δ�Ÿ�);
				if (enemy_units >= ���۰�������_�������δ�� and enemy_troops >= ���۰�������_�����������) return false;
			}

			// �������� : ���ۺδ밡 ������ ������ �ִ뺴�� ��� ���纴���� ������ ���ذ� �̸��� ��� ����
			int city_troops = int(city.troops);
			int city_max_troops = int(city.max_troops);
			if (���۰�������_��������_����[controller_index])
			{
				/// ���� : 0�� �� �� �ִ� �׸�(����)�� ������ �� �и� 0�� ���� �ʵ��� ����
				if (city_troops < city_max_troops * ���۰�������_��������_����[controller_index] / 100) return false;
			}

			// �������� : ���ۺδ밡 ������ ������ ���纴�� ��� ���纴���� ������ ���ذ� �̸��� ��� ����
			int city_food = int(city.food);
			if (���۰�������_��������_����[controller_index])
			{
				/// ���� : 0�� �� �� �ִ� �׸�(����)�� ������ �� �и� 0�� ���� �ʵ��� ����
				if (city_food < city_troops * ���۰�������_��������_����[controller_index] / 100) return false;
			}

			return true;
		}

		// ���ۺδ밡 ������ ������ �ڼ��� �������� �� ���۹��� �ĺ����ø� �˻�
		array<pk::city@> func_���۹�������_�ĺ��˻�(pk::city@ city, int controller_index)
		{
			array<pk::city@> neighbor_city_arr(0);
			for (int dir_index = 0; dir_index < 6; dir_index++)
			{
				pk::city@ neighbor_city = pk::get_city(city.neighbor[dir_index]);
				if (!pk::is_alive(neighbor_city)) continue;
				if (neighbor_city.get_force_id() != city.get_force_id()) continue;

				// ������ ���� ������ ���� Ȯ��
				if (!func_�����ʿ�����_��������(city, neighbor_city, controller_index)) continue;

				neighbor_city_arr.insertLast(neighbor_city);
			}

			return neighbor_city_arr;
		}

		// ������ ���� ������ ���� Ȯ��
		bool func_�����ʿ�����_��������(pk::city@ city, pk::city@ neighbor_city, int controller_index)
		{
			// �⺻���� : ������ ���� ������ ���û��°� �Ĺ�(���ðŸ� 2 �̳��� �����ð� ���� ���)�� ��� ����
			int neighbor_city_status = get_city_status(neighbor_city);
			if (neighbor_city_status == ���û���_�Ĺ�) return false;

			// �⺻���� : ���ۺδ밡 ������ ������ ���û��°� ���, ���۹��� ������ ���û��°� ������ ��� ����
			int city_status = get_city_status(city);
			if (city_status == ���û���_��� and neighbor_city_status == ���û���_����) return false;

			// �⺻���� : ������ ���� ���÷� ���ϰ� �ִ� ���ۺδ밡 �̹� �����ϴ� ��� ����
			if (func_Ư�����ø�ǥ_�������ۺδ�_���翩��(neighbor_city)) return false;

			// �������� : ������ ���� ���÷κ��� �����Ÿ� �̳��� ���ñ����� ������ �̻��� ���δ� �� �������� �����ϴ� ��� ����
			if (�����ʿ�����_���δ�����_����[controller_index])
			{
				int enemy_units = func_���ñ���_���δ��(neighbor_city, �����ʿ�����_�������δ�Ÿ�);
				int enemy_troops = func_���ñ���_�������(neighbor_city, �����ʿ�����_�������δ�Ÿ�);
				if (enemy_units >= �����ʿ�����_�������δ�� and enemy_troops >= �����ʿ�����_�����������) return false;
			}

			// �������� : ������ ���� ������ �ִ뺴�� ��� ���纴���� ������ ���ذ��� �ʰ��ϴ� ��� ����
			int neighbor_city_troops = int(neighbor_city.troops);
			int neighbor_city_max_troops = int(neighbor_city.max_troops);
			if (�����ʿ�����_��������1_����[controller_index])
			{
				/// ���� : 0�� �� �� �ִ� �׸�(����)�� ������ �� �и� 0�� ���� �ʵ��� ����
				if (neighbor_city_troops > neighbor_city_max_troops * �����ʿ�����_��������1_����[controller_index] / 100) return false;
			}

			// �������� : ���ۺδ밡 ������ ������ ���纴�� ��� ������ ���� ������ ���纴���� ������ ���ذ��� �ʰ��ϴ� ��� ����
			int city_troops = int(city.troops);
			if (�����ʿ�����_��������2_����[controller_index])
			{
				/// ���� : 0�� �� �� �ִ� �׸�(����)�� ������ �� �и� 0�� ���� �ʵ��� ����
				if (neighbor_city_troops > city_troops * �����ʿ�����_��������2_����[controller_index] / 100) return false;
			}

			// �������� : ������ ���� ���ð� ���� ���ذ� �߻��߰ų� �߻��� ������ ��� ����
			if (�����ʿ�����_��������_����[controller_index])
			{
				// ���û��°� ������ ��� ���뿩�� Ȯ��
				if (neighbor_city_status == ���û���_��� or (!��������_���浵��_��������[controller_index] and neighbor_city_status == ���û���_����))
				{
					// ���� ���ذ� �߻��� ���
					if (neighbor_city.ekibyou) return false;

					// ���� ���ذ� �߻��� ������ ���
					/// ���� : ���ذ� �߻������� ��� ���� �б�(����)�� �Ǹ� �߻���
					if (neighbor_city.next_ekibyou and next_turn_is_next_quarter()) return false;
				}
			}

			// �������� : ������ ���� ���ð� �޶ѱ� ���ذ� �߻��߰ų� �߻��� ������ ��� ����
			if (�����ʿ�����_�޶ѱ�����_����[controller_index])
			{
				// ���û��°� ������ ��� ���뿩�� Ȯ��
				if (neighbor_city_status == ���û���_��� or (!�޶ѱ�����_���浵��_��������[controller_index] and neighbor_city_status == ���û���_����))
				{
					// �޶ѱ� ���ذ� �߻��� ���
					if (neighbor_city.inago) return false;

					// �޶ѱ� ���ذ� �߻��� ������ ���
					/// ���� : ���ذ� �߻������� ��� ���� �б�(����)�� �Ǹ� �߻���
					if (neighbor_city.next_inago and next_turn_is_next_quarter()) return false;
				}
			}

			// ���û��°� �������� ���� ���
			if (city_status == ���û���_���� and neighbor_city_status == ���û���_����)
			{
				// �⺻���� : ���� �����ü��� ���ۺδ밡 ������ ���ð� ���۹��� ������ ��������� �ʰ��ϴ� ��� ����
				if (func_�����ֺ�_�����ü�(city, 1) > func_�����ֺ�_�����ü�(neighbor_city, 1) * 2) return false;

				// �⺻���� : ���� ������ ������� ���ۺδ밡 ������ ���ð� ���۹��� ������ ��������� �ʰ��ϴ� ��� ����
				else if (func_����������_�����(city) > func_����������_�����(neighbor_city) * 2) return false;
			}

			// ���û��°� ���� ���� ��� : ���ðŸ��� �����ü� ��
			if (city_status == ���û���_��� and neighbor_city_status == ���û���_���)
			{
				for (int distance = 2; distance <= 8; distance++)
				{
					// �⺻���� : ���ðŸ����� ������ �ֺ� �����ü��� ���ۺδ밡 ������ ���ð� ���۹��� ������ ��������� �ʰ��ϴ� ��� ����
					if (func_�����ֺ�_�����ü�(city, distance) > func_�����ֺ�_�����ü�(neighbor_city, distance) * 2) return false;
				}
			}

			return true;
		}

		/**
		@return 'city_a'�� 'city_b'���� ���º��� �켱������ ������ ����
		*/
		// ���۹��� ���� �� ���º��� �켱���� ��
		bool func_���ð�_�켱����_��(pk::city@ city_a, pk::city@ city_b)
		{
			// ���û��� : �����º��� ������¸� �켱
			int a_city_status = get_city_status(city_a);
			int b_city_status = get_city_status(city_b);
			if (a_city_status != b_city_status) return a_city_status > b_city_status;

			// ���û��°� �������� ���� ���
			if (a_city_status == ���û���_���� and b_city_status == ���û���_����)
			{
				// ���� �����ü� : �������� �켱
				int a_around_enenmy_cities = func_�����ֺ�_�����ü�(city_a, 1);
				int b_around_enenmy_cities = func_�����ֺ�_�����ü�(city_b, 1);
				if (a_around_enenmy_cities != b_around_enenmy_cities)
					return a_around_enenmy_cities > b_around_enenmy_cities;

				// ���ñ��� ���� ����(���� �� �ױ�) �� �������� ���� : �������� �켱
				int a_area_enemy_base_troops = func_���ñ���_������_����(city_a);
				int b_area_enemy_base_troops = func_���ñ���_������_����(city_b);
				if (a_area_enemy_base_troops != b_area_enemy_base_troops)
					return a_area_enemy_base_troops > b_area_enemy_base_troops;

				// ���� �������� ����� : �������� �켱
				int a_neighbor_enemy_city_troops = func_����������_�����(city_a);
				int b_neighbor_enemy_city_troops = func_����������_�����(city_b);
				if (a_neighbor_enemy_city_troops != b_neighbor_enemy_city_troops)
					return a_neighbor_enemy_city_troops > b_neighbor_enemy_city_troops;
			}

			// ���û��°� ���� ���� ���
			if (a_city_status == ���û���_��� and b_city_status == ���û���_���)
			{
				// �����ֺ� �����ü� : �������� �켱 (���ðŸ��� �Ǵ�, ���ðŸ� 2���� ��)
				for (int distance = 2; distance <= 8; distance++)
				{
					int a_around_enenmy_cities = func_�����ֺ�_�����ü�(city_a, distance);
					int b_around_enenmy_cities = func_�����ֺ�_�����ü�(city_b, distance);
					if (a_around_enenmy_cities != b_around_enenmy_cities)
						return a_around_enenmy_cities > b_around_enenmy_cities;
				}
			}

			// ���ú��� : �������� �켱
			int a_troops = city_a.troops;
			int b_troops = city_b.troops;
			return a_troops < b_troops;
		}

		// ���ۺδ� ����
		/// ���� : cmd_info ����ü�� Ȱ���� AI�� ������� ���� �� �ش����� �ൿ���� �ڵ� ������ (��, ������ �ൿ���� �����ϸ� �������� ����)
		void func_���ۺδ�_����(pk::city@ city, pk::building@ building, pk::building@ neighbor_building, int controller_index)
		{
			// ��ǻ�� ������� ����
			pk::com_deploy_cmd_info cmd;

			// ��������
			@cmd.base = @building;

			// �����δ� ����
			cmd.type = �δ�����_����;

			// �����δ� ����
			cmd.member[0] = get_unit_leader_id(building);

			// �����δ� ����
			int city_status = get_city_status(city);
			cmd.troops = get_troops_transport_volume(building, neighbor_building, city_status, controller_index);

			// �����δ� ��
			cmd.gold = get_gold_transport_volume(building, neighbor_building, city_status, controller_index);

			// �����δ� ����
			cmd.food = get_food_transport_volume(building, neighbor_building, city_status, controller_index);

			// �����δ� ����
            for (int weapon_id = 0; weapon_id < ����_��; weapon_id++)
			{
				cmd.weapon_id[weapon_id] = weapon_id;
				cmd.weapon_amount[weapon_id] = get_wpn_transport_volume(building, neighbor_building, weapon_id, city_status, controller_index);
			}

			// �����δ� �ӹ�
			cmd.order = �δ��ӹ�_�̵�;

			// �����δ� �����ǥ
			cmd.target_pos = neighbor_building.pos;

			// ������� ����
			int unit_id = pk::command(cmd);

			// �����δ� �ൿ�Ϸ� ó��
			/// ���� : cmd_info ����ü�� Ȱ���� AI�� ������� ���� �� ������ �δ��� �ൿ�Ϸ� ���� �ʼ�
			if (unit_id != -1) pk::get_unit(unit_id).action_done = true;
		}

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		// �Ϲݰ��ӿ��� ��ȯ : ��������, Ʃ�丮��, �̼� ���� ���� �ƴ� ��
		bool is_normal_game()
		{
			return (!pk::is_campaign() and !pk::is_mission_running());
		}

		// ������ ������ü ���� ��ȯ
		int get_controller_index(pk::force@ force)
		{
			return (force.is_player() ? /*�÷��̾� ���ӱ���*/0 : /*��ǻ��*/1);
		}

	/**
		[ ���� ] ���û��� : �Ÿ��� ���� �� ������ �̵� �ҿ� �ϼ�(�ҿ��ϼ� 10��) ����

		1. �Ĺ� : ���ðŸ� 2 ���� �������� ���ð� ���� ��� (���ðŸ� 3 ���� �������� ���ð� ����)
		2. ��� : ���ðŸ� 1 ���� �������� ���ð� ���� ��� (���ðŸ� 2 ���� �������� ���ð� ����)
		3. ���� : ���ðŸ� 1 ���� �������� ���ð� �ִ� ���
	*/
		// ������ ���û��� ��ȯ
		int get_city_status(pk::city@ city)
		{
			if      (func_�����ֺ�_�����ü�(city, /*distance*/2) == 0) return ���û���_�Ĺ�;
			else if (func_�����ֺ�_�����ü�(city, /*distance*/1) == 0) return ���û���_���;
			else                                                       return ���û���_����;
		}

		// ��ɽ����� ���� �ൿ�� ��п��� Ȯ��
		/// ���� : ������ �����ü� �� ����� ���� �� ����޴��� ��� ����� �ൿ�� �Ҹ� �ݰ�
		bool ap_is_enough(pk::city@ city, int needed_ap, int buff_facility_id)
		{
			if (pk::has_facility(city, buff_facility_id)) needed_ap /= 2;
			pk::district@ district = pk::get_district(city.get_district_id());
			return (int(district.ap) >= needed_ap);
		}

		// ���� ���� ���� �б�(����)���� Ȯ��
		/// ���� : ������ ���� ��¥�� 1/1(��), 4/1(����), 7/1(����), 10/1(�ܿ�), ���� ������ ���� ���� 12/21, 3/21, 6/21, 9/21�� ��
		bool next_turn_is_next_quarter()
		{
			return (pk::get_month() % 3 == 0 and pk::get_day() == 21);
		}

		// ���ñ��� �� ���÷κ��� �����Ÿ�(��ǥ�Ÿ�) �̳��� ���δ�� ��ȯ
		int func_���ñ���_���δ��(pk::city@ city, int distance)
		{
			int enemy_units = 0;
			array<pk::point> range_arr = pk::range(city.get_pos(), 1, distance);
			for (int pos_index = 0; pos_index < int(range_arr.length); pos_index++)
			{
				pk::point range_pos = range_arr[pos_index];
				int area_city_id = pk::get_city_id(range_pos);
				if (city.get_id() != area_city_id) continue;

				pk::unit@ unit = pk::get_unit(range_pos);
				if (!pk::is_alive(unit)) continue;
				if (!pk::is_enemy(city, unit)) continue;

				enemy_units++;
			}

			return enemy_units;
		}

		// ���ñ��� �� ���÷κ��� �����Ÿ�(��ǥ�Ÿ�) �̳��� ������� ��ȯ
		int func_���ñ���_�������(pk::city@ city, int distance)
		{
			int enemy_troops = 0;
			array<pk::point> range_arr = pk::range(city.get_pos(), 1, distance);
			for (int pos_index = 0; pos_index < int(range_arr.length); pos_index++)
			{
				pk::point range_pos = range_arr[pos_index];
				int area_city_id = pk::get_city_id(range_pos);
				if (city.get_id() != area_city_id) continue;

				pk::unit@ unit = pk::get_unit(range_pos);
				if (!pk::is_alive(unit)) continue;
				if (!pk::is_enemy(city, unit)) continue;

				enemy_troops += unit.troops;
			}

			return enemy_troops;
		}

		// Ư�� ���ø� ���� ��ǥ�� �ϰ� �ִ� ���� ������ ���ۺδ밡 �����ϴ��� ����
		bool func_Ư�����ø�ǥ_�������ۺδ�_���翩��(pk::city@ city)
		{
			for (int unit_id = 0; unit_id < �δ�_��; unit_id++)
			{
				pk::unit@ unit = pk::get_unit(unit_id);
				if (!pk::is_alive(unit)) continue;

				// �δ��� ������ ���ۺδ밡 �ƴ� ��� ����
				if (unit.type != �δ�����_����) continue;

				// �δ��� �ӹ��� �̵��� �ƴ� ��� ����
				if (unit.order != �δ��ӹ�_�̵�) continue;

				// �δ��� ������ ���ص����� ���°� �������� ���� ��� ����
				if (unit.get_force_id() != city.get_force_id()) continue;

				// �δ��� ��ǥ��ǥ�� ���ص����� ��ǥ�� �ƴ� ��� ����
				if (unit.target_pos != city.get_pos()) continue;

				return true;
			}

			return false;
		}

		// ���÷κ��� �����Ÿ�(���ðŸ�) �̳��� �����ü� ��ȯ
		/// ���� : ���ðŸ��� ������ ���� �� �̵� �ϼ�(�ҿ��ϼ� 10��) ����
		int func_�����ֺ�_�����ü�(pk::city@ city, int distance)
		{
			int enemy_cities = 0;
			for (int city_id = 0; city_id < ����_��; city_id++)
			{
				pk::city@ enemy_city = pk::get_city(city_id);
				if (!pk::is_alive(enemy_city)) continue;

				// �˻����� ���� ����
				if (city.get_id() == city_id) continue;

				// �˻����� ���ÿ� Ȯ�δ�� ���ð� ���� �ƴ� ��� ����
				if (!pk::is_enemy(city, enemy_city)) continue;

				// ���� �� �Ÿ��� �����Ÿ��� �ʰ��ϴ� ��� ����
				int city_distance = pk::get_city_distance(city.get_id(), city_id);
				if (city_distance > distance) continue;

				enemy_cities++;
			}

			return enemy_cities;
		}

		// ���� �������� ����� Ȯ��
		/// ���� : ���ðŸ��� 2(�������� ���� ����)������ �����δ� �Ÿ��� ������� ������ �� �� �ִ� �Ÿ��� ���õ� ���� (��â - �ž�)
		/// ���� : ���ðŸ��� 1(������ ����)������ �����δ� �Ÿ��� �־ ������ ���� ���� �Ÿ��� ���õ� ���� (�û� - �Ǿ�)
		int func_����������_�����(pk::city@ city)
		{
			int enemy_troops = 0;
			for (int dir_index = 0; dir_index < 6; dir_index++)
			{
				pk::city@ neighbor_city = pk::get_city(city.neighbor[dir_index]);
				if (!pk::is_alive(neighbor_city)) continue;
				if (!pk::is_enemy(city, neighbor_city)) continue;

				enemy_troops += int(neighbor_city.troops);
			}

			return enemy_troops;
		}

	/**
		[ ���� ] ���ú� ���� �� �ױ����� ��ǥ�Ÿ� (�ִܰŸ� ����)

		 1. ���� : ������(15)
		 2. ���� :   ȣ��(18), ������(28)
		 3.   �� : �鸶��(10)
		 4. ��� : �����( 5)
		 5. ���� : ������(15), â����(16)
		 6. �Ϻ� : �ظ���(10), ������(19)
		 7. ���� : ������( 6)
		 8. ���� : ������(10)
		 9. ���� : ������( 6), ȣ�ΰ�(11), ������(18)
		10. ��� :   ����( 8), ��ǳ��(11), �԰��(15),   ����(20), �Ͼ���(21)
		11. ���� : �����( 6)
		12. �ڵ� : ���Ͱ�(11),   �˰�(14)
		13. ���� : ���װ�( 8), �μ���(13)
		14. ���� : ������( 8)
		15. ��� : �渪��( 6)
		16. �ž� : ȣ����( 6)
		17. ��� : �߷���(11)
		18. ���� : ������( 9), ������(15), ������(17)
		19. ���� : ������(10), ������(12)
		20. ��� : ������(20)
		21. ���� : �ϱ���( 7)
		22. �û� : ������( 7), ������(10), �ľ���(20), �븪��(40)
		23. ���� : ������(18)
		24. ���� : ȯ����( 6)
		25. �Ǿ� : ��ȣ��( 6), ȣ����(19)
		26.   �� : �����(10)
		27. ȸ�� : ������( 8)
	*/
		// ���ñ��� ���� ����(���� �� �ױ�) �� �������� ���� Ȯ��
		/// ���� : ���ñ����� ���������� �Ÿ��� �ʹ� �ְų� ������ �������� �ƴ� ������ ������
		int func_���ñ���_������_����(pk::city@ city)
		{
			int enemy_troops = 0;
			for (int i = 0; i < 5; i++)
			{
				int building_id = city.gate[i];
				if (building_id == -1) continue;

				// ���ñ����� ���������� �Ÿ��� �ʹ� �ְų� ������ �������� �ƴ� ���� Ȯ��
				if (func_���ܴ��_���ñ�������_�ش翩��(city, building_id)) continue;

				pk::building@ building = pk::get_building(building_id);
				if (!pk::is_enemy(city, building)) continue;

				int building_troops = pk::get_troops(building);
				enemy_troops += building_troops;
			}

			return enemy_troops;
		}

		// ���ñ����� ���������� �Ÿ��� �ʹ� �ְų� ������ �������� �ƴ� ���� Ȯ��
		bool func_���ܴ��_���ñ�������_�ش翩��(pk::city@ city, int building_id)
		{
			int city_id = city.get_id();
			if (city_id == �ǹ�_���� and building_id == �ǹ�_������) return true;
			if (city_id == �ǹ�_�Ϻ� and building_id == �ǹ�_������) return true;
			if (city_id == �ǹ�_���� and building_id == �ǹ�_������) return true;
			if (city_id == �ǹ�_��� and building_id == �ǹ�_�Ͼ���) return true;
			if (city_id == �ǹ�_�û� and building_id == �ǹ�_�ľ���) return true;
			if (city_id == �ǹ�_�û� and building_id == �ǹ�_�븪��) return true;

			return false;
		}

		// ���ۺδ� ���� ���� (�����ĺ� ���� ����)
		int get_unit_leader_id(pk::building@ building)
		{
            array<pk::person@> person_arr = pk::list_to_array(pk::get_idle_person_list(building));
			person_arr.sort(function(a, b)
			{
				// �켱����1 - ������ Ư�� : ���Ư�⸦ �����ϰ� �ִ� ������ �켱
				if (���ۺδ�����_���Ư��_�ݿ�)
				{
					bool a_has_skill = pk::has_skill(a, Ư��_���);
					bool b_has_skill = pk::has_skill(b, Ư��_���);
					if (a_has_skill and !b_has_skill) return true;
					if (!a_has_skill and b_has_skill) return false;
				}

				// �켱����2 - ������ Ư�� ����ɷ� : �������� �켱
				int a_stat = a.stat[���ۺδ�����_����ɷ�];
				int b_stat = b.stat[���ۺδ�����_����ɷ�];
				if (a_stat != b_stat) return a_stat > b_stat;

				// �켱����3 - ������ �Ǹ� : �������� �켱
				int a_giri = a.giri;
				int b_giri = b.giri;
				return a_giri > b_giri;
			});

			// �������� : ���ۺδ� �����ĺ� ���� �� �漺���� ���ذ� �̻��� ���常�� ����
			int leader_id = -1;
			for (int person_index = 0; person_index < int(person_arr.length); person_index++)
			{
				pk::person@ leader = person_arr[person_index];
				if (leader.loyalty < ���ۺδ�_�����ĺ�_�����漺��) continue;

				leader_id = leader.get_id();

				/// ���� : ���� ���� �� for ������ �������� ������ �漺�� ������ �����ϴ� �ļ��� ������ ������
				break;
			}

			return leader_id;
		}

		// �� ���۷� ����
		int get_gold_transport_volume(pk::building@ building, pk::building@ neighbor_building, int city_status, int controller_index)
		{
			// �⺻���� : ���� ���ۺδ� �� �ִ���۷�
			int gold = 100000;

			// �⺻���� : ���۹��� ������ �� ��� Ȯ�� (��� �ִ�ġ������ ���� Ȯ��)
			gold = pk::min(gold, pk::get_max_gold(neighbor_building) - pk::get_gold(neighbor_building));

			// �������� : ���ۺδ밡 ������ ������ �� ��� �ּ������� Ȯ��
			array<int> �ּ�������_�� = (city_status == ���û���_����) ? �ּ�������_����_�� : �ּ�������_���_��;
			gold = pk::min(gold, pk::max(0, pk::get_gold(building) - �ּ�������_��[controller_index]));

			// �������� : ���ۺδ밡 ������ ������ �� ��� �� ������ ���� Ȯ��
			gold = pk::min(gold, pk::get_gold(building) * ���ۺ���_��[controller_index] / 100);

			return gold;
		}

		// ���� ���۷� ����
		int get_food_transport_volume(pk::building@ building, pk::building@ neighbor_building, int city_status, int controller_index)
		{
			// �⺻���� : ���� ���ۺδ� ���� �ִ���۷�
			int food = 500000;

			// �⺻���� : ���۹��� ������ ���� ��� Ȯ�� (��� �ִ�ġ������ ���� Ȯ��)
			food = pk::min(food, pk::get_max_food(neighbor_building) - pk::get_food(neighbor_building));

			// �������� : ���ۺδ밡 ������ ������ ���� ��� �ּ������� Ȯ��
			array<int> �ּ�������_���� = (city_status == ���û���_����) ? �ּ�������_����_���� : �ּ�������_���_����;
			food = pk::min(food, pk::max(0, pk::get_food(building) - �ּ�������_����[controller_index]));

			// �������� : ���ۺδ밡 ������ ������ ���� ��� �� ������ ���� Ȯ��
			food = pk::min(food, pk::get_food(building) * ���ۺ���_����[controller_index] / 100);

			return food;
		}

		// ���� ���۷� ����
		int get_troops_transport_volume(pk::building@ building, pk::building@ neighbor_building, int city_status, int controller_index)
		{
			// �⺻���� : ���� ���ۺδ� ���� �ִ���۷�
			int troops = 60000;

			// �⺻���� : ���۹��� ������ ���� ��� Ȯ�� (��� �ִ�ġ������ ���� Ȯ��)
			troops = pk::min(troops, pk::get_max_troops(neighbor_building) - pk::get_troops(neighbor_building));

			// �������� : ���ۺδ밡 ������ ������ ���� ��� �ּ������� Ȯ��
			array<int> �ּ�������_���� = (city_status == ���û���_����) ? �ּ�������_����_���� : �ּ�������_���_����;
			troops = pk::min(troops, pk::max(0, pk::get_troops(building) - �ּ�������_����[controller_index]));

			// �������� : ���ۺδ밡 ������ ������ ���� ��� �� ������ ���� Ȯ��
			troops = pk::min(troops, pk::get_troops(building) * ���ۺ���_����[controller_index] / 100);

			return troops;
		}

		// ���� ���۷� ����
		int get_wpn_transport_volume(pk::building@ building, pk::building@ neighbor_building, int weapon_id, int city_status, int controller_index)
		{
			// �⺻���� : ���� ���ۺδ� ���� �ִ���۷�
			int wpn_amount = (weapon_id < ����_����) ? 100000 : 100;

			// �⺻���� : ���۹��� ������ ���� ��� Ȯ�� (��� �ִ�ġ������ ���� Ȯ��)
			wpn_amount = pk::min(wpn_amount, pk::get_max_weapon_amount(neighbor_building, weapon_id) - pk::get_weapon_amount(neighbor_building, weapon_id));

			// �������� : ���ۺδ밡 ������ ������ ���� ��� �ּ������� Ȯ��
			array<int> �ּ�������_����(0);
			if      (weapon_id < ����_����) �ּ�������_���� = (city_status == ���û���_����) ? �ּ�������_����_�Ϲݺ��� : �ּ�������_���_�Ϲݺ���;
			else if (weapon_id < ����_�ְ�) �ּ�������_���� = (city_status == ���û���_����) ? �ּ�������_����_�������� : �ּ�������_���_��������;
			else                            �ּ�������_���� = (city_status == ���û���_����) ? �ּ�������_����_�Լ� : �ּ�������_���_�Լ�;
			wpn_amount = pk::min(wpn_amount, pk::max(0, pk::get_weapon_amount(building, weapon_id) - �ּ�������_����[controller_index]));

			// �������� : ���ۺδ밡 ������ ������ ���� ��� �� ������ ���� Ȯ��
			int ���ۺ���_���� = 0;
			if      (weapon_id < ����_����) ���ۺ���_���� = ���ۺ���_�Ϲݺ���[controller_index];
			else if (weapon_id < ����_�ְ�) ���ۺ���_���� = ���ۺ���_��������[controller_index];
			else                            ���ۺ���_���� = ���ۺ���_�Լ�[controller_index];
			wpn_amount = pk::min(wpn_amount, pk::get_weapon_amount(building, weapon_id) * ���ۺ���_���� / 100);

			return wpn_amount;
		}

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	}

	Main main;
}