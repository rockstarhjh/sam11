/*
	@���� : masterpiecek
	@���� : PK2.1���� ���� Ư�⸦ ������ ������ ȥ�� �� �ɷ�ġ�� ������� �ʴ� ���� ����
*/

namespace Ư��_����
{
	class Main
	{

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		bool ����� = false;
		array<bool> ���庰_ȥ�ο���(����_��);

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		Main()
		{
			pk::bind(102, pk::trigger102_t(�ó������ʱ�ȭ));
			pk::bind(111, pk::trigger111_t(�Ͻ���));
			pk::bind(112, pk::trigger112_t(������));
			pk::bind(120, pk::trigger120_t(����ȭ��׸���));
		}

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		void �ó������ʱ�ȭ()         { update_info_of_person(); }
		void �Ͻ���(pk::force@ force) { update_info_of_person(); }
		void ������(pk::force@ force) { update_info_of_person(); }
		void ����ȭ��׸���()         { action_of_spousal_support(); }

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		void update_info_of_person()
		{
			for (int person_id = 0; person_id < ����_��; person_id++)
			{
				pk::person@ person = pk::get_person(person_id);
				if (!pk::is_alive(person)) continue;

				���庰_ȥ�ο���[person_id] = (person.spouse == -1) ? false : true;
			}
		}

		void action_of_spousal_support()
		{
			for (int person_id = 0; person_id < ����_��; person_id++)
			{
				pk::person@ person = pk::get_person(person_id);
				if (!pk::is_alive(person)) continue;
				if (���庰_ȥ�ο���[person_id]) continue;

				int spouse_id = person.spouse;
				if (spouse_id == -1) continue;
				if (!pk::is_fuufu(person, spouse_id)) continue;

				pk::person@ spouse = pk::get_person(spouse_id);

				if (�����)
				{
					string person_name = pk::decode(pk::get_name(person));
					string spouse_name = pk::decode(pk::get_name(spouse));
					pk::info("���� �� ȥ�� �̺�Ʈ Ȯ�� : "+person_name+", "+spouse_name);
				}

				���庰_ȥ�ο���[person_id] = true;
				���庰_ȥ�ο���[spouse_id] = true;

				if (pk::has_skill(person, Ư��_����) or pk::has_skill(spouse, Ư��_����))
				{
					add_base_stat(person, person_id, spouse, spouse_id);
				}
			}
		}

		void add_base_stat(pk::person@ person, int person_id, pk::person@ spouse, int spouse_id)
		{
			int person_constant = int(pk::core::skill_constant(person_id, Ư��_����, 0));
			int spouse_constant = int(pk::core::skill_constant(spouse_id, Ư��_����, 0));
			int skill_constant = pk::max(person_constant, spouse_constant);

			if (�����)
			{
				string person_name = pk::decode(pk::get_name(person));
				string spouse_name = pk::decode(pk::get_name(spouse));
				pk::info("���� Ư���� : "+person_name+"("+person_constant+"), "+spouse_name+"("+spouse_constant+"), ����("+skill_constant+")");
			}

			for (int stat_id = 0; stat_id < ����ɷ�_��; stat_id++)
			{
			/// ���� : int pk::add_base_stat(person@ self, int type, int value) - �ش� �Լ� ��� �� �������� �߻�
				person.base_stat[stat_id] = person.base_stat[stat_id] + skill_constant;
				spouse.base_stat[stat_id] = spouse.base_stat[stat_id] + skill_constant;
			}

			person.update();
			spouse.update();
		}

///	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	}

	Main main;
}