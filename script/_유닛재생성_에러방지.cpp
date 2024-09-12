/*
@만든이: 크래픽스
@Update: 2024.1.22,병기생산량 추가.
@Update: 2024.5.15,확인기능 추가
@Update: 2024.6.4, 0,0 좌표에 있는 삭제
*/
namespace 유닛재생성_Recreate
{
	class Main
	{
		Main()
		{
			pk::bind(111, pk::trigger111_t(onTurn));
			pk::bind(112, pk::trigger111_t(onTurnEnd));

			pk::menu_item item;
			item.menu = 101;
			item.pos = 13;
			item.init = pk::building_menu_item_init_t(유닛재생성Init);
			item.is_enabled = pk::menu_item_is_enabled_t(Is유닛재생성Enabled);
			item.get_text = pk::menu_item_get_text_t(유닛재생성Text);
			item.get_desc = pk::menu_item_get_desc_t(유닛재생성Desc);
			item.handler = pk::menu_item_handler_t(유닛재생성Handler);
			pk::add_menu_item(item);


		}

		void 유닛재생성Init(pk::building@ building)
		{
		}
		bool Is유닛재생성Enabled()
		{
			return true;
		}
		string 유닛재생성Text()
		{
			return pk::encode("유닛재생성");
		}
		string 유닛재생성Desc()
		{
			return pk::encode("모든유닛을 재생성합니다.(수송/적장제외)");
		}

		pk::list<pk::person@> 포로리스트;
		bool 유닛재생성Handler()
		{
			if (!pk::yes_no(pk::encode("진행하시겠습니까? 모든 부대가 재생성됩니다.")))
				return true;

			포로리스트 = pk::get_person_list(pk::mibun_flags(신분_포로));
			
			pk::list<pk::unit@> us = pk::get_unit_list();
			for (int i = 0; i < us.count; i++)
			{
				createUnit(us[i]);
			}
			return true;
		}


		void onTurn(pk::force@ f)
		{
			pk::list<pk::unit@> us = pk::get_unit_list(f);
			for (int i = 0; i < us.count; i++)
			{
				removeErrorUnit(us[i]);
			}
		}
		void onTurnEnd(pk::force@ f)
		{
			pk::list<pk::unit@> us = pk::get_unit_list(f);
			for (int i = 0; i < us.count; i++)
			{
				removeErrorUnit(us[i]);
			}
		}

		array<int> getWeapon(pk::unit@ u)
		{
			int weapon = 0;
			int weapon2 = 0;
			if (u.weapon != 병기_주가 && u.weapon != 병기_누선 && u.weapon != 병기_투함)
			{
				weapon = u.weapon;
				if (u.stock[병기_주가].amount > 0)
					weapon2 = 병기_주가;
				else if (u.stock[병기_누선].amount > 0)
					weapon2 = 병기_누선;
				else 
					weapon2 = 병기_투함;
			}
			else 
			{
				if (u.stock[병기_창].amount > 0)
					weapon = 병기_창;
				else if (u.stock[병기_극].amount > 0)
					weapon = 병기_극;
				else if (u.stock[병기_노].amount > 0)
					weapon = 병기_노;
				else if (u.stock[병기_군마].amount > 0)
					weapon = 병기_군마;
				else if (u.stock[병기_정란].amount > 0)
					weapon = 병기_정란;
				else if (u.stock[병기_투석].amount > 0)
					weapon = 병기_투석;
				else if (u.stock[병기_목수].amount > 0)
					weapon = 병기_목수;
				else
					weapon = 병기_충차;

				weapon2 = u.weapon;
			}

			return { weapon,weapon2 };
		}

		void removeErrorUnit(pk::unit@ u)
		{
			if (u.type == 부대종류_수송)
				return;
			pk::building@ b = pk::get_building(pk::get_person(u.leader).service);
			if (b == null)
				return;

			pk::point pos = u.get_pos();
			if (!pk::is_valid_pos(pos))
				return;

			pk::person@ leader = pk::get_person(u.leader);
			pk::unit@ u3 = pk::get_unit(pos);
			if (u3 == null || u3.leader != u.leader || (pos.x ==0 && pos.y == 0))
			{
				pk::kill(u);
				pk::printf("에러유닛삭제:{}!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",getName(leader));
				return;
			}
		}

		pk::list<pk::person@> get포로(pk::unit@ u)
		{
			pk::point pos = u.get_pos();
			pk::list<pk::person@> arr;
			for (int i = 0; i < 포로리스트.count; i++)
			{
				pk::person@ p = 포로리스트[i];
				pk::point pos2 = p.get_pos();
				//pk::printf("location:{},servcie:{}\n", p.location, p.service);
				//if (u.get_id() != p.location)
				//	continue;
				if(pos.x != pos2.x || pos.y != pos2.y)
					continue;

				arr.add(p);
			}
			return arr;
		}

		void update포로(pk::unit@ u, pk::list<pk::person@> arr,array<int> 포로기간)
		{
			if (arr.count == 0)
				return;

			for (int i = 0; i < arr.count; i++)
			{
				pk::person@ p = arr[i];
				p.mibun = 신분_포로;
				p.location = u.get_id();
				p.prisoner_timer = 포로기간[i];
				p.order = -1;
				p.target[0] = -1;
				p.update();
				pk::printf("포로 pos0:{},{}, pos1:{},{}\n", u.get_pos().x, u.get_pos().y, p.get_pos().x, p.get_pos().y);
			}
			u.update();
		}

		void createUnit(pk::unit@ u)
		{
			if (u.type == 부대종류_수송)
				return;
			pk::building@ b = pk::get_building(pk::get_person(u.leader).service);
			if (b == null)
			{
				pk::printf("no building kill,{}\n",getName(pk::get_person(u.leader)));
				pk::kill(u);
				return;
			}
			if (!pk::is_valid_pos(u.get_pos()))
			{
				pk::printf("valid kill,{}\n", getName(pk::get_person(u.leader)));
				pk::kill(u);
				return;
			}
				

			pk::person@ p0 = pk::get_person(u.member[0]);
			pk::person@ p1 = pk::get_person(u.member[1]);
			pk::person@ p2 = pk::get_person(u.member[2]);
			
			array<int> arr = getWeapon(u);
			if (arr[0] >= 병기_끝 || arr[1] >= 병기_끝)
				return;
			int troops = u.troops;
			int food = u.food;
			int gold = u.gold;
			int energy = u.energy;
			pk::point pos = u.get_pos();
			if (!pk::is_valid_pos(pos))
				return;
			int status = u.status;
			int direction = u.direction;
			int order = u.order;
			int target = u.target;
			int target_type = u.target_type;
			pk::point target_pos = u.target_pos;
			uint flags = u.flags;
			bool done = u.action_done;
			int req = u.requested_from;

			pk::unit@ u3 = pk::get_unit(pos);
			if (u3 == null || u3.leader != u.leader || (pos.x == 0 && pos.y == 0)) 
			{
				pk::printf("에러유닛 삭제:{}\n", getName(pk::get_person(u.leader)));
				pk::kill(u);
				return;
			}
			pk::list<pk::person@> 포로 = get포로(u);
			if (포로.count > 0)
				return;
			array<int> 포로기간;
			for (int i = 0; i < 포로.count; i++)
			{
				포로기간.insertLast(포로[i].prisoner_timer);
			}


			pk::kill(u);
			//pk::remove(u);
			pk::printf("name:{},{},{},b:{},w:{},w1:{},g:{},f:{},pos:{},{}\n", getName(p0), getName(p1), getName(p2),b.get_id(),arr[0],arr[1],gold,food,pos.x,pos.y);
			pk::unit@ u2=pk::create_unit(b, p0, p1,p2,troops, arr[0], arr[1],gold,food,pos);
			//update포로(u2, 포로, 포로기간);
			u2.energy = energy;
			u2.status = status;
			u2.direction = direction;
			u2.order = order;
			u2.target = target;
			u2.target_type = target_type;
			u2.target_pos = target_pos;
			u2.flags = flags;
			u2.action_done = done;
			u2.requested_from = req;
			u2.update();
		}

		string getName(pk::person@ p)
		{
			return p != null ? pk::decode(pk::get_name(p)) : "null";
		}
	}

	Main main;
}

