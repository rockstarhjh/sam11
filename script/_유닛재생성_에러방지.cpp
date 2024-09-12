/*
@������: ũ���Ƚ�
@Update: 2024.1.22,������귮 �߰�.
@Update: 2024.5.15,Ȯ�α�� �߰�
@Update: 2024.6.4, 0,0 ��ǥ�� �ִ� ����
*/
namespace ���������_Recreate
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
			item.init = pk::building_menu_item_init_t(���������Init);
			item.is_enabled = pk::menu_item_is_enabled_t(Is���������Enabled);
			item.get_text = pk::menu_item_get_text_t(���������Text);
			item.get_desc = pk::menu_item_get_desc_t(���������Desc);
			item.handler = pk::menu_item_handler_t(���������Handler);
			pk::add_menu_item(item);


		}

		void ���������Init(pk::building@ building)
		{
		}
		bool Is���������Enabled()
		{
			return true;
		}
		string ���������Text()
		{
			return pk::encode("���������");
		}
		string ���������Desc()
		{
			return pk::encode("��������� ������մϴ�.(����/��������)");
		}

		pk::list<pk::person@> ���θ���Ʈ;
		bool ���������Handler()
		{
			if (!pk::yes_no(pk::encode("�����Ͻðڽ��ϱ�? ��� �δ밡 ������˴ϴ�.")))
				return true;

			���θ���Ʈ = pk::get_person_list(pk::mibun_flags(�ź�_����));
			
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
			if (u.weapon != ����_�ְ� && u.weapon != ����_���� && u.weapon != ����_����)
			{
				weapon = u.weapon;
				if (u.stock[����_�ְ�].amount > 0)
					weapon2 = ����_�ְ�;
				else if (u.stock[����_����].amount > 0)
					weapon2 = ����_����;
				else 
					weapon2 = ����_����;
			}
			else 
			{
				if (u.stock[����_â].amount > 0)
					weapon = ����_â;
				else if (u.stock[����_��].amount > 0)
					weapon = ����_��;
				else if (u.stock[����_��].amount > 0)
					weapon = ����_��;
				else if (u.stock[����_����].amount > 0)
					weapon = ����_����;
				else if (u.stock[����_����].amount > 0)
					weapon = ����_����;
				else if (u.stock[����_����].amount > 0)
					weapon = ����_����;
				else if (u.stock[����_���].amount > 0)
					weapon = ����_���;
				else
					weapon = ����_����;

				weapon2 = u.weapon;
			}

			return { weapon,weapon2 };
		}

		void removeErrorUnit(pk::unit@ u)
		{
			if (u.type == �δ�����_����)
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
				pk::printf("�������ֻ���:{}!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",getName(leader));
				return;
			}
		}

		pk::list<pk::person@> get����(pk::unit@ u)
		{
			pk::point pos = u.get_pos();
			pk::list<pk::person@> arr;
			for (int i = 0; i < ���θ���Ʈ.count; i++)
			{
				pk::person@ p = ���θ���Ʈ[i];
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

		void update����(pk::unit@ u, pk::list<pk::person@> arr,array<int> ���αⰣ)
		{
			if (arr.count == 0)
				return;

			for (int i = 0; i < arr.count; i++)
			{
				pk::person@ p = arr[i];
				p.mibun = �ź�_����;
				p.location = u.get_id();
				p.prisoner_timer = ���αⰣ[i];
				p.order = -1;
				p.target[0] = -1;
				p.update();
				pk::printf("���� pos0:{},{}, pos1:{},{}\n", u.get_pos().x, u.get_pos().y, p.get_pos().x, p.get_pos().y);
			}
			u.update();
		}

		void createUnit(pk::unit@ u)
		{
			if (u.type == �δ�����_����)
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
			if (arr[0] >= ����_�� || arr[1] >= ����_��)
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
				pk::printf("�������� ����:{}\n", getName(pk::get_person(u.leader)));
				pk::kill(u);
				return;
			}
			pk::list<pk::person@> ���� = get����(u);
			if (����.count > 0)
				return;
			array<int> ���αⰣ;
			for (int i = 0; i < ����.count; i++)
			{
				���αⰣ.insertLast(����[i].prisoner_timer);
			}


			pk::kill(u);
			//pk::remove(u);
			pk::printf("name:{},{},{},b:{},w:{},w1:{},g:{},f:{},pos:{},{}\n", getName(p0), getName(p1), getName(p2),b.get_id(),arr[0],arr[1],gold,food,pos.x,pos.y);
			pk::unit@ u2=pk::create_unit(b, p0, p1,p2,troops, arr[0], arr[1],gold,food,pos);
			//update����(u2, ����, ���αⰣ);
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

