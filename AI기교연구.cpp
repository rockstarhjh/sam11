/*
@������: ũ���Ƚ�
@Update: 2023.8.12,���ʹ���
@Update: 2023.8.13,AI�ⱳ����Ʈ�� �������� �ʾƼ� ����.
*/
namespace AI�ⱳ����
{

	const int AI����_�ⱳ = 400;
	const int AI����_�ֱ� = 1;		// AI���� �ֱ�(����)�� �����մϴ�. �ش簪�� 0���� Ŀ�� �մϴ�.
	const int �ִ뿬������ = 1; //�ִ뿬���� �ܰ谡 1�ܰ��϶��� �ⱳ���� ����,
	
const array<array<int>> �ⱳ����Ʈ =
{
{�ⱳ_â���ܷ�, �ⱳ_��������, �ⱳ_���,�ⱳ_����â��} ,
{�ⱳ_�غ��ܷ�, �ⱳ_ȭ�����, �ⱳ_ū����,�ⱳ_�����غ�} ,
{�ⱳ_�뺴�ܷ�, �ⱳ_����, �ⱳ_����,�ⱳ_�����뺴} ,
{�ⱳ_�⺴�ܷ�, �ⱳ_�縶����, �ⱳ_���,�ⱳ_�����⺴},
{�ⱳ_���ú�, �ⱳ_�����౺, �ⱳ_��������,�ⱳ_����},
{�ⱳ_���భȭ, �ⱳ_��������, �ⱳ_��������,�ⱳ_����},
{�ⱳ_��������, �ⱳ_�ü���ȭ, �ⱳ_������ȭ,�ⱳ_��ȭ},
{�ⱳ_�������, �ⱳ_��ȭ��, �ⱳ_ȭ�࿬��,�ⱳ_���࿬��},
{�ⱳ_�������, �ⱳ_�װ�Ȯ��, �ⱳ_��������,�ⱳ_�ν����}
};


	class Main
	{
        Main()
		{
			//test
			//pk::bind(111, pk::trigger111_t(onTurnStart));
			pk::bind(107, pk::trigger108_t(onNewDay));
			pk::bind(108, pk::trigger108_t(onNewMonth));
			
		}


		void onNewMonth()
		{
			pk::list<pk::force@> forces;
			forces.clear();
			forces = pk::get_force_list();
			for (auto i = 0; i < forces.count; i++)
			{
				if (pk::get_month() % AI����_�ֱ� == 1 || AI����_�ֱ� == 1)
				{
					pk::force@ force = forces[i];
					if (!pk::is_alive(force) or !pk::is_normal_force(force) or 
					!pk::is_alive(pk::get_person(force.kunshu)) or force.is_player())
						continue;

					//AI���¸� ����
					force.tp = pk::min(force.tp + AI����_�ⱳ, 10000);
				}
			}
		}
		void onNewDay()
		{
			�ⱳ����üũ();
		}
		
		void onTurnStart(pk::force@ force)
		{
			if (!pk::is_alive(force) or !pk::is_normal_force(force) or
				!pk::is_alive(pk::get_person(force.kunshu)) or force.is_player())
				return;
			
			if (force.researching_tech > 0)
				return;
			
			�ⱳ����(force);

		}
		void �ⱳ����üũ()
		{
			pk::list<pk::force@> forces;
			forces.clear();
			forces = pk::get_force_list();

			for (auto i = 0; i < forces.count; i++)
			{
				pk::force@ force = forces[i];
				if (!pk::is_alive(force) or !pk::is_normal_force(force) or
					!pk::is_alive(pk::get_person(force.kunshu)) or force.is_player())
					continue;

				if(force.researching_tech > 0)
					continue;

				�ⱳ����(force);
			}
		}
		void �ⱳ����(pk::force@ force)
		{
			int maxTechCount = 0;
			int maxTech = -1;

			//�ִ뿬���� �ⱳ���
			int maxSum = 0;
			int maxRank = 0;
			for (auto i = 0; i < �ⱳ����Ʈ.length; i++)
			{
				pk::tech@ tech0 = pk::get_tech(�ⱳ����Ʈ[i][0]);
				pk::tech@ tech1 = pk::get_tech(�ⱳ����Ʈ[i][1]);
				pk::tech@ tech2 = pk::get_tech(�ⱳ����Ʈ[i][2]);
				pk::tech@ tech3 = pk::get_tech(�ⱳ����Ʈ[i][3]);

				int sum = 0;
				int rank = 0;
				if (pk::has_tech(force, tech0.get_id()))
				{
					sum += tech0.tp_cost;
					rank=1;
				}
				if (pk::has_tech(force, tech1.get_id()))
				{
					sum += tech1.tp_cost;
					rank=2;
				}
				if (pk::has_tech(force, tech2.get_id()))
				{
					sum += tech2.tp_cost;
					rank=3;
				}
				if (pk::has_tech(force, tech3.get_id()))
				{
					sum += tech3.tp_cost;
					rank=4;
				}
					

				//�Ϸ�� ��ũ�� ����
				if(sum >= tech0.tp_cost + tech1.tp_cost + tech2.tp_cost + tech3.tp_cost)
					continue;

				if (sum > maxSum) 
				{
					maxTechCount=1;
					maxTech = i;
					maxSum = sum;
					maxRank = rank;
				}
				else if (sum == maxSum) 
				{
					maxTechCount++;
				}
			}

			//�������� �ִ뿬���Ǿ����� �н�
			if (maxTechCount > 1 || maxRank <= �ִ뿬������)
			{
				//pk::u8printf("{},maxTechCount {}, maxRank {}\n",pk::decode(pk::get_name(force)),maxTechCount,maxRank);
				return;
			}
				

			for (auto i = 0; i < 4; i++)
			{
				pk::tech@ tech0 = pk::get_tech(�ⱳ����Ʈ[maxTech][i]);
				if (pk::has_tech(force, tech0.get_id()))
					continue;

				if (force.tp < tech0.tp_cost)
					return;
				
				//���� �����̻�ǰ�, ������ 3���̻�,������ ������ �ֿ켱,
				pk::list<pk::city@> cities = pk::get_city_list(force);
				cities.sort(function(a, b)
				{
					pk::building@ b0 = pk::city_to_building(a);
					pk::building@ b1 = pk::city_to_building(b);
					int count0 = pk::get_idle_person_list(b0).count;
					int count1 = pk::get_idle_person_list(b1).count;
					if (count0 < 3 and count1 < 3)
						return a.gold > b.gold;
					else if (count0 < 3)
						return false;
					else if (count1 < 3)
						return true;

					//����Ư�� üũ�ʿ�
					return a.gold > b.gold;
				});

				

				pk::building@ bb0 = pk::city_to_building(cities[0]);
				pk::list<pk::person@> moos = pk::get_idle_person_list(bb0);
				if (moos.count < 3)
					return;
				if (cities[0].gold < tech0.gold_cost * 1.3) //���� �����ִ� ��Ȳ���� ����
					return;

				//�ʿ�ɷ����� �����ʿ�

				//�ⱳ���� ����
				pk::research_tech_cmd_info ri;
				@ri.base = bb0;
				@ri.actors[0] = moos[0];
				@ri.actors[1] = moos[1];
				@ri.actors[2] = moos[2];
				ri.tech = tech0.get_id();
				if(pk::command(ri))
				{
					pk::person@ kunshu = pk::get_person(force.kunshu);
					string s = "\x1b[2x" + pk::encode(pk::decode(pk::get_name(kunshu)) + "��\x1b[0x \x1b[1x" + "\x1b[0x, �ⱳ������" + pk::decode(tech0.name) + "���������");
					pk::history_log(kunshu.pos, force.color, s);
					return;
				}
				//test
				//else
				//{
				//	pk::person@ kunshu = pk::get_person(force.kunshu);
				//	string s = "\x1b[2x" + pk::encode(pk::decode(pk::get_name(kunshu)) + "��\x1b[0x�� \x1b[1x" + "\x1b[0x, �ⱳ������" + pk::decode(tech0.name) + "���������");
				//	pk::history_log(kunshu.pos, force.color, s);
				//	return;
				//}
					
				


			}
		}

	}

	Main main;
}


