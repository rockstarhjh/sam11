/*
@만든이: 크래픽스
@Update: 2023.8.12,최초배포
@Update: 2023.8.19,화면위치의 유닉의 다중특기를 확인
*/

namespace 다중특기확인
{
	class Main
	{
        Main()
		{
			pk::menu_item 다중특기;
			다중특기.menu = 2;
			다중특기.is_enabled = pk::menu_item_is_enabled_t(isEnabled);
			다중특기.get_desc = pk::menu_item_get_desc_t(getDesc_다중특기);
			다중특기.get_text = pk::menu_item_get_text_t(getText_다중특기);
			다중특기.handler = pk::menu_item_handler_t(handler_다중특기);
			pk::add_menu_item(다중특기);
			
			pk::bind(120, pk::trigger120_t(UpdatePerFrame));
		}
		void UpdatePerFrame()
		{
			//pk::unit@ unit = pk::get_selected_unit();
			//if (unit == null)
			//	return;

			pk::point pt = pk::get_cursor_hex_pos();
			auto obj = pk::get_hex_object(pt);
			if (obj==null or obj.get_type_id() != 11)
				return;
			
			pk::unit@ unit = obj;

			array<int> arr;
			for (int i = 0; i < 특기_끝; i++)
			{
				pk::person@ p0 = pk::get_person(unit.member[0]);
				pk::person@ p1 = pk::get_person(unit.member[1]);
				pk::person@ p2 = pk::get_person(unit.member[2]);
				if ((p0!=null and pk::has_skill(p0, i)) or 
					(p1!=null and pk::has_skill(p1, i)) or 
					(p2!=null and pk::has_skill(p2, i)))  
				{
					arr.insertLast(i);
				}
			}
			if(arr.length == 0)
				return;

			arr.sort(function(a, b) 
			{
				pk::skill@ s0 = pk::get_skill(a);
				pk::skill@ s1 = pk::get_skill(b);
				return s0.type <= s1.type;
			});

			string str;
			for (int i = 0; i < arr.length; i++)
			{
				if (i != arr.length - 1)
					str = str + pk::decode(pk::get_skill(arr[i]).name) + " ";
				else
					str = str + pk::decode(pk::get_skill(arr[i]).name);
			}

			pk::point point= pk::get_neighbor_pos(unit.get_pos(), 방향_남동,1);
			pk::point point2 = pk::hex_pos_to_screen_pos(point);
			
			
			//point2.x = point2.x - (str.length()/2 * 20);
			pk::draw_text(pk::encode(str),point2);
		}

		pk::force@ _force;
		pk::building@ _building;
		pk::city@ _city;
		pk::district@ _district;
		bool isEnabled()
		{
			return true;
		}

		string getDesc_다중특기()
		{
			return pk::encode("무장의 다중 특기를 확인합니다.");
		}
		string getText_다중특기()
		{
			return pk::encode("다중특기확인");
		}
		bool handler_다중특기()
		{
			pk::list<pk::person@> moos;
			for (int i = 0; i < 무장_끝; i++)
			{
				pk::person@ person= pk::get_person(i);
				if(person==null)
					continue;

				moos.add(person);
			}

			pk::list<pk::person@> person_sel2 = pk::person_selector(pk::encode("무장 선택"), pk::encode("무장을 선택합니다."), moos, 1, 1);
			if (person_sel2.count == 0)
				return false;

			string str = "";
			pk::person@ moo = person_sel2[0];
			for (int i = 0; i < 특기_끝; i++)
			{
				if (pk::has_skill(moo, i)) 
				{
					str = str + pk::decode(pk::get_skill(i).get_name()) + " ";
				}
			}

			pk::message_box(pk::encode(str), moo);
			return true;
		}
	}

	Main main;
}

