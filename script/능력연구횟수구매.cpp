/*
@������: ũ���Ƚ�
@Update: 2023.8.29, ���ʹ���
@Update: 2023.9.2, �׽�Ʈ �ڵ��߰�
*/

namespace �ɷ¿���Ƚ������
{
	const int �ൿ�� = 20;
	
	const int ����_�� = 1000;
	const int ����_�� = 2000;
	const int ����_�� = 3000;
	const int ����_B = 1000;
	const int ����_A = 2000;
	const int Ư��_�� = 1000;
	const int Ư��_�� = 2000;
	const int Ư��_�� = 3000;

	const array<int> �ɷ¿���_�ⱳ =
	{
		����_��,����_��,����_��,����_��,����_��,
		����_��,����_��,����_��,����_��,����_��,
		
		����_��,����_��,����_��,����_��,����_��,
		����_B,����_A,����_B,����_A,����_B,
		
		����_A,����_B,����_A,����_B,����_A,
		����_B,����_A,Ư��_��,Ư��_��,Ư��_��,
		
		Ư��_��,Ư��_��,Ư��_��,Ư��_��,Ư��_��,
		Ư��_��,Ư��_��,Ư��_��,Ư��_��,Ư��_��,
		
		Ư��_��,Ư��_��,Ư��_��,Ư��_��,Ư��_��,
		Ư��_��,Ư��_��,Ư��_��,Ư��_��,Ư��_��,
		
		Ư��_��,Ư��_��,Ư��_��,Ư��_��,Ư��_��,
		Ư��_��,Ư��_��,Ư��_��,Ư��_��,Ư��_��,

		Ư��_��,Ư��_��,Ư��_��,Ư��_��,Ư��_��,
		Ư��_��,Ư��_��,Ư��_��,Ư��_��,Ư��_��,

		Ư��_��,Ư��_��,Ư��_��,Ư��_��,Ư��_��,
		Ư��_��,Ư��_��,Ư��_��,Ư��_��,Ư��_��,

		Ư��_��,Ư��_��,Ư��_��,Ư��_��,Ư��_��,
		Ư��_��,Ư��_��,Ư��_��,Ư��_��,Ư��_��,

		Ư��_��,Ư��_��,Ư��_��,Ư��_��,Ư��_��,
		Ư��_��,Ư��_��,Ư��_��,
	};
	const array<int> �ɷ¿���_�ִ�ο��� =
	{
		5,5,3,5,5,
		3,5,5,3,5,
		5,3,5,5,3,
		5,5,5,5,5,
		5,5,5,5,5,
		5,5,3,3,3,
		3,1,3,3,1,
		3,3,3,3,3,
		1,3,3,3,3,
		3,3,1,5,3,
		3,3,3,5,5,
		5,5,3,5,5,
		3,5,5,3,3,
		3,3,3,5,5,
		5,5,5,5,5,
		5,5,5,3,3,
		3,3,5,5,5,
		5,5,5,5,5,
		5,5,5,3,3,
		3,3,3
	};
	
	const array<string> �ɷ¿���_�̸� =
	{
		"����","����","���","����","����",
		"����","����","����","����","����",
		"����","����","����","����","�Ű�",
		"â��B","â��A","�غ�B","�غ�A","�뺴B",
		"�뺴A","�⺴B","�⺴A","����B","����A",
		"����B","����A","����","����","����",
		"����","�п�","�ź�","���","�ɸ�",
		"�ұ�","�༺","�ݰ�","ö��","��",
		"����","����","���","����","�߸�",
		"����","�ɸ�","��","�ɰ�","â��",
		"�ؽ�","�ý�","����","�౺","����",
		"����","ȣ��","�־�","����","�ȷ�",
		"¡��","ǳ��","���","����","ȭ��",
		"�͸�","��ȯ","�ݰ�","����","�Ⱒ",
		"����","����","����","����","����",
		"���","����","����","����","����",
		"����","�","����","�̵�","�̵�",
		"¡��","¡��","¡��","����","����",
		"����","����","����","���","����",
		"�Ż�","����","�͹�",
		
	};

	class ResearchInfo
	{
		string name;
		int count;
		int id;
		int tp;
		int maxCount;
		int index;
	};



	class Main
	{

		Main()
		{
			pk::menu_item item;
			item.menu = 105;
			item.pos = 13;
			item.init = pk::building_menu_item_init_t(AbilityResearchInit);
			item.is_enabled = pk::menu_item_is_enabled_t(IsAbilityResearchEnabled);
			item.get_text = pk::menu_item_get_text_t(GetAbilityResearchText);
			item.get_desc = pk::menu_item_get_desc_t(GetAbilityResearchDesc);
			item.handler = pk::menu_item_handler_t(AbilityResearchHandler);
			pk::add_menu_item(item);
		}

		pk::force@ _force;
		pk::building@ _building;
		pk::city@ _city;
		pk::district@ _district;
		void AbilityResearchInit(pk::building@ building)
		{
			@_force = pk::get_force(building.get_force_id());
			@_building = building;
			@_city = pk::building_to_city(building);
			@_district = pk::get_district(building.get_district_id());
		}
		bool IsAbilityResearchEnabled()
		{
			return _district.ap >= �ൿ��;
		}
		string GetAbilityResearchText()
		{
			return pk::encode("�ɷ¿���Ƚ������");
		}
		string GetAbilityResearchDesc()
		{
			if (_district.ap < �ൿ��)
				return pk::encode(pk::format("�ൿ���� �����մϴ�.(�ൿ��{})", �ൿ��));
			else
				return pk::encode(pk::format("�ɷ¿���Ƚ���� �����մϴ�.(�ൿ��{})", �ൿ��));
		}

		array<ResearchInfo> makeList()
		{
			array<ResearchInfo> ris;

			int count = 48;
			//for (int i = 0; i < _force.ability_researched.length; i++)
			for (int i = 0; i < count; i++)
			{
				//_force.ability_researched[i] = true;
				//_force.training_counter[i] = 3;
				//pk::printf("abil i{},count{}\n",i,_force.training_counter[i]);
			}

			for (int i = 0; i < count; i++)
			{
				if(!_force.ability_researched[i])
					continue;
				ResearchInfo ri;
				ri.count = _force.training_counter[i];
				ri.id = i;
				ri.maxCount = �ɷ¿���_�ִ�ο���[i];
				ri.name = pk::format("{}",�ɷ¿���_�̸�[i]);
				ri.tp = �ɷ¿���_�ⱳ[i];
				ris.insertLast(ri);
			}
			
			int count2 = 10;
			for (int i = 0; i < count2; i++)
			{
				if (!_force.sp_ability_researched[i])
					continue;
				int index = _force.sp_ability[i];
				ResearchInfo ri;
				ri.count = _force.sp_training_counter[i];
				ri.maxCount = �ɷ¿���_�ִ�ο���[index];
				ri.name = �ɷ¿���_�̸�[index];
				ri.id = index;
				ri.index = i;
				ri.tp = �ɷ¿���_�ⱳ[index];
				ris.insertLast(ri);
			}


			return ris;
		}

		bool AbilityResearchHandler()
		{
			
			while (true)
			{
				int si=0;
				array<ResearchInfo> ris = makeList();
				ResearchInfo@ chooseItem;
				while (true)
				{
					array<string> itemArr;
					array<ResearchInfo> itemArr2;
					int count = pk::min(ris.length, si + 4);
					if (si == 0)
						itemArr.insertLast(pk::encode("����"));
					else
						itemArr.insertLast(pk::encode("�ڷ�"));

					for (int i = si; i < count; i++)
					{
						ResearchInfo@ ri = ris[i];
						string str;
						str = pk::format("{},{}/{},�ⱳ{}", ri.name, ri.count,ri.maxCount, ri.tp);
						itemArr.insertLast(pk::encode(str));
						itemArr2.insertLast(ri);
					}
					if (si + 4 >= ris.length)
						itemArr.insertLast(pk::encode("����"));
					else
						itemArr.insertLast(pk::encode("����"));

					int choose2 = pk::choose(pk::encode("�ɷ��� �������ֽʽÿ�"), itemArr);
					if (choose2 == itemArr.length - 1)
					{
						si = si + 4;
						if (si >= ris.length)
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
						@chooseItem = itemArr2[choose2 - 1];
						break;
					}
				}

				if(chooseItem == null)
					continue;

				if (_force.tp < chooseItem.tp) 
				{
					pk::message_box(pk::encode("�ⱳ�� �����մϴ�."));
					continue;
				}
				if(_district.ap < �ൿ��)
				{
					pk::message_box(pk::encode("�ൿ���� �����մϴ�."));
					continue;
				}
				int value = chooseItem.id < 48 ? _force.training_counter[chooseItem.id] : _force.training_counter[chooseItem.index];
				if (!pk::yes_no(pk::encode(pk::format("{} {}/{}�����մϱ�?", chooseItem.name, chooseItem.count, value))))
					continue;

				//if (chooseItem.id < 48)
				//{
				//	if (_force.training_counter[chooseItem.id] == 0)
				//	{
				//		pk::message_box(pk::encode("���� �ִ� Ƚ�� �Դϴ�."));
				//		continue;
				//	}
				//}
				//else 
				//{
				//	if (_force.sp_training_counter[chooseItem.index] == 0)
				//	{
				//		pk::message_box(pk::encode("���� �ִ� Ƚ�� �Դϴ�."));
				//		continue;
				//	}
				//}
					
				
				//if(!pk::yes_no(pk::encode(pk::format("{}�� ȸ���� �����մϱ�?",chooseItem.name))))
				//	continue;

				if(chooseItem.id < 48)
					_force.training_counter[chooseItem.id]=pk::max(0, _force.training_counter[chooseItem.id]-1);
				else
					_force.sp_training_counter[chooseItem.index]=pk::max(0,_force.sp_training_counter[chooseItem.index]-1);

				
				pk::play_se(10);
				_force.tp -= chooseItem.tp;
				_district.ap -=�ൿ��;
				_force.update();
				
				si = 0;
				@chooseItem = null;
			}//while
			return true;

		}//funcio


	}

	Main main;
}


