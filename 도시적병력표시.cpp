/*
@만든이: 크래픽스
@Update: 2023.8.23, 최초배포
*/

namespace 도시적병력표시
{
	const int 글씨사이즈 = FONT_BIG;        
	//const int 글씨사이즈 = FONT_SMALL;        
	const int 시작위치_가로 = 200;
	const int 시작위치_세로 = 300;

	class ForceInfo
	{
		int troops = 0;
		pk::list<pk::unit@> units;
		pk::force@ force;
		int manCount = 0;
	};

	class Main
	{
        Main()
		{
			pk::bind(120, pk::trigger120_t(UpdatePerFrame));
		}
		void UpdatePerFrame()
		{
			pk::point pt = pk::get_cursor_hex_pos();
			auto obj = pk::get_hex_object(pt);
			if (obj==null or obj.get_type_id() != 5)
				return;
			pk::building@ building = obj;
			
			pk::city@ city = pk::building_to_city(building);
			if(city ==null)
				return;
			
			pk::force@ force = pk::get_force(city.get_force_id());
			
			
			int width = int(pk::get_resolution().width);
            int height = int(pk::get_resolution().height);

			array<ForceInfo> forces;

			pk::list<pk::unit@> units = pk::get_unit_list();
			for (int i = 0; i < units.count; i++)
			{
				pk::unit@ u = units[i];
				if(pk::get_city_id(u.get_pos()) != city.get_id())
					continue;

				ForceInfo@ fi2 = null;
				for (int j = 0; j < forces.length; j++)
				{
					ForceInfo@ fi = forces[j];
					if(fi.force.get_id() != u.get_force_id())
						continue;
					
					@fi2 = fi;
					@fi2.force = pk::get_force(u.get_force_id());
					fi2.units.add(u);
					fi2.troops += u.troops;
					fi2.manCount += pk::get_member_count(u);
					break;
				}
				if(fi2 == null)
				{
					ForceInfo fi;
					@fi.force = pk::get_force(u.get_force_id());
					fi.units.add(u);
					fi.troops = u.troops;
					fi.manCount = pk::get_member_count(u);
					forces.insertLast(fi);
				}
			}

			ForceInfo@ my = null;
			int index = 0;
			for (int i = 0; i < forces.length; i++)
			{
				ForceInfo@ fi = forces[i];
				if(fi.force.get_id() != city.get_force_id())
					continue;
				index = i;
				@my = fi;
				break;
			}
			if (my != null)
			{
				//my.troops += city.troops;
				forces.removeAt(index);
				forces.insertAt(0,my);
			}
			else 
			{
				ForceInfo fi;
				@fi.force = pk::get_force(city.get_force_id());
				fi.troops = 0;
				fi.manCount = 0;
				//fi.troops = city.troops;
				forces.insertAt(0,fi);
			}



			int w = 시작위치_가로;
			int h = 시작위치_세로;


			for (int i = 0; i < forces.length; i++)
			{
				ForceInfo@ fi = forces[i];
				
				for(int j=0;j<fi.units.count;j++)
				{
					//pk::highlight(fi.units[j].get_pos(),false);
					
					pk::point point = pk::hex_pos_to_screen_pos(fi.units[j].get_pos());
					pk::size size0(24,24);
					pk::rectangle r0(point, size0);
					//pk::draw_filled_rect(r0, 0x3000ff00);
					
					
					pk::draw_rect(r0,0xff000000);
					if(i==0)
						pk::draw_filled_rect(r0, 0x3000ff00);
					else 
					{
						if(pk::is_enemy(force, fi.force))
							pk::draw_filled_rect(r0, 0x30ff0000);
						else
							pk::draw_filled_rect(r0, 0x30ffff00);
					}
						
				}
					

				int offset = (글씨사이즈 == FONT_BIG ? 30 : 20);
				string str;
				if(i==0)
					str=pk::format("\x1b[2x{}\x1b[0x군,{}부대,{}명,{}명,{}명",pk::decode(pk::get_name(fi.force)), fi.units.count, fi.manCount,fi.troops,city.troops);
				else if(pk::is_enemy(force, fi.force))
					str=pk::format("\x1b[29x{}\x1b[0x군,{}부대,{}명,{}명",pk::decode(pk::get_name(fi.force)), fi.units.count, fi.manCount,fi.troops);
				else
					str=pk::format("\x1b[19x{}\x1b[0x군,{}부대,{}명,{}명",pk::decode(pk::get_name(fi.force)), fi.units.count, fi.manCount,fi.troops);

				pk::point point;
				point.x = w;
				point.y = h; h += offset;
				pk::draw_text(pk::encode(str), point, -1, 글씨사이즈, 0x00000000);

			}


		}


	}

	Main main;
}

