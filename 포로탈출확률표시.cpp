/*
@������: ũ���Ƚ�
@Update: 2023.8.23,���ʹ���
*/

namespace ����Ż��Ȯ��ǥ��
{
	const int �۾������� = FONT_BIG;        
	//const int �۾������� = FONT_SMALL;        
	const int ������ġ_���� = 900;
	const int ������ġ_���� = 50;
	const int ����ǥ��_���� = 5;
	
	
	class  CapturedInfo
	{
		pk::building@ building;
		pk::person@ person;
		int day;
		int percent;
	}
	
	class Main
	{
		pk::func157_t@ prev_callback_157;
		
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


			pk::list<pk::city@> cities = pk::get_city_list(force);
			array<CapturedInfo> captured;
			pk::list<pk::person@> persons = pk::get_person_list(pk::mibun_flags(�ź�_����));
			for(int i=0;i<persons.count;i++)
			{
				pk::person@ p = persons[i];

				bool bFound = false;
				for (int j = 0; j < cities.count; j++)
				{
					if (cities[j].get_id() != p.location)
						continue;
					bFound = true;
					break;
				}
				if (bFound)
				{
					CapturedInfo ci;
					@ci.person = p;
					ci.day = p.prisoner_timer * 10;
					@ci.building = pk::get_building(p.location);
					ci.percent=prev_callback_157(p);

					captured.insertLast(ci);
				}
			}

			if(captured.length > 1)
				captured.sort(function(a, b) { return a.percent > b.percent; });

			int w = ������ġ_����;
			int h = ������ġ_����;

			int count = pk::min(����ǥ��_����, captured.length);

			for (int i = 0; i < count; i++)
			{
				CapturedInfo ci = captured[i];

				int offset = (�۾������� == FONT_BIG ? 30 : 20);
				string str = pk::format("����:\x1b[2x{}\x1b[0x,�漺{},{}%,{}��,{}", pk::decode(pk::get_name(ci.person)),ci.person.loyalty, ci.percent ,ci.day, pk::decode(pk::get_name(ci.building)));

				pk::point point;
				point.x = w;
				point.y = h; h += offset;
				pk::draw_text(pk::encode(str), point, -1, �۾�������, 0x00000000);
			}
		}
	}

	Main main;
}
