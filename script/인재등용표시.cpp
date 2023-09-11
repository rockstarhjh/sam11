/*
@������: ũ���Ƚ�
@Update: 2023.8.23,���ʹ���
*/

namespace ������ǥ��
{
	const int �۾������� = FONT_BIG;        
	//const int �۾������� = FONT_SMALL;        
	const int ������ġ_���� = 500;
	const int ������ġ_���� = 50;
	const int ����ǥ��_���� = 5;
	
	const int ǥ���ִ�_�漺�� = 90;
	const bool ����_ǥ�� = false;
	
	class  ManInfo
	{
		pk::building@ building;
		pk::person@ person;
		int dist;
	}
	
	pk::func157_t@ prev_callback_157;
	class Main
	{
		Main()
		{
			@prev_callback_157 = cast<pk::func157_t@>(pk::get_func(157));
			
			pk::bind(120, pk::trigger120_t(UpdatePerFrame));
		}
		void UpdatePerFrame()
		{
			int force_id = pk::get_current_turn_force_id();
            pk::force@ force = pk::get_force(force_id);
            if (null == force or !force.is_player())
                return;

			pk::building@ capital = pk::get_building(pk::get_person(force.kunshu).service);

			pk::list<pk::city@> cities = pk::get_city_list(force);
			array<ManInfo> mans;
			pk::list<pk::person@> persons = pk::get_person_list(pk::mibun_flags(�ź�_�Ϲ�, �ź�_�¼�, �ź�_����, �ź�_���, �ź�_����));
			for(int i=0;i<persons.count;i++)
			{
				pk::person@ p = persons[i];
				if(!����_ǥ�� and p.mibun == �ź�_����)
					continue;

				if (p.mibun == �ź�_��� or p.mibun == �ź�_����)
				{
					bool bFound = false;
					for (int j = 0; j < cities.count; j++)
					{
						if (cities[j].get_id() != p.location)
							continue;
						bFound = true;
						break;
					}
					if(!bFound)
						continue;
				}

				if(p.loyalty >= ǥ���ִ�_�漺��)
					continue;


				ManInfo mi;
				@mi.person = p;
				@mi.building = pk::get_building(p.service);
				mi.dist = pk::get_building_distance(capital.get_id(), mi.building.get_id()) * 10;
				mans.insertLast(mi);
			}

			if(mans.length >1)
				mans.sort(function(a, b) { return a.person.loyalty < b.person.loyalty; });

			int w = ������ġ_����;
			int h = ������ġ_����;

			int count = pk::min(����ǥ��_����, mans.length);
			for (int i = 0; i < count; i++)
			{
				ManInfo mi = mans[i];

				int offset = (�۾������� == FONT_BIG ? 30 : 20);
				string strMibun = "�Ϲ�";
				switch (mi.person.mibun)
				{
				case �ź�_�¼�:strMibun = "�¼�"; break;
				case �ź�_����:strMibun = "����"; break;
				case �ź�_���:strMibun = "���"; break;
				case �ź�_����:strMibun = "����"; break;
				default:
					break;
				}
				string str = pk::format("����:\x1b[2x{}\x1b[0x,{},{},{}��,{}", pk::decode(pk::get_name(mi.person)),mi.person.loyalty, strMibun,mi.dist, pk::decode(pk::get_name(mi.building)));

				pk::point point;
				point.x = w;
				point.y = h; h += offset;
				pk::draw_text(pk::encode(str), point, -1, �۾�������, 0x00000000);
			}
		}
	}

	Main main;
}
