namespace ����_ó��
{
	class Main
	{
		Main()
		{
			pk::set_func(258, pk::func258_t(callback));
		}

		int callback(pk::person@ prisoner, const pk::prisoner_info &in info)
		{
			pk::person@ judge = pk::get_person(pk::get_kunshu_id(info.taken_by));
			pk::district@ district = pk::get_district(prisoner.district);
			pk::force@ force = pk::get_force(district.force);	
			pk::force@ judge_force = pk::get_force(judge.get_force_id());			

			if (func_4ae3a0(prisoner, judge))
			{
				if(force.player < 0)
				{
					if(prisoner.mibun == �ź�_����)
					{
						pk::play_se(5);
						pk::message_box(pk::get_msg(pk::msg_param(5929, prisoner, judge)), prisoner);
					}	

					if(prisoner.mibun != �ź�_����)
						pk::play_se(3);
				
					pk::history_log(pk::get_current_turn_force_id(), force.color, pk::encode(pk::format("��ȹ���� \x1b[1x{}\x1b[0x, \x1b[2x{}\x1b[0x���� ó����" , pk::decode(pk::get_name(prisoner)) , pk::decode(pk::get_name(judge) ) ) ) );
				}
				
				return ����ó��_ó��;
			}

			if (cast<pk::func111_t>(pk::get_func(111))(prisoner, judge, info.returnable ? 1 : 2, 0))
			{
				if (prisoner.mibun == �ź�_���� && force.player < 0)
				{
					pk::play_se(2);
					pk::message_box(pk::get_msg(pk::msg_param(5881, prisoner, judge)), prisoner);
					pk::history_log(pk::get_current_turn_force_id(), force.color, pk::encode(pk::format("��ȹ���� \x1b[1x{}\x1b[0x��\x1b[2x{}\x1b[0x�� ���ϰ� ��" , pk::decode(pk::get_name(prisoner)) , pk::decode(pk::get_name(judge) ) ) ) );	
				}
				return ����ó��_���;
			}

			if (func_4af5b0(prisoner, judge))
			{	
				if(force.player < 0)
				{
					if(prisoner.mibun == �ź�_����)
					{
						pk::play_se(5);
						pk::message_box(pk::get_msg(pk::msg_param(5929, prisoner, judge)), prisoner);
					}
												
					if(prisoner.mibun != �ź�_����)
						pk::play_se(3);

					pk::history_log(pk::get_current_turn_force_id(), force.color, pk::encode(pk::format("��ȹ���� \x1b[1x{}\x1b[0x��\x1b[2x{}\x1b[0x���� ó����" , pk::decode(pk::get_name(prisoner)) , pk::decode(pk::get_name(judge) ) ) ) );
				}

				return ����ó��_ó��;
			}
				
			if (prisoner.mibun == �ź�_����)
			{
				if(force.player < 0)
				{	
					pk::play_se(6);
					pk::message_box(pk::get_msg(pk::msg_param(5917, prisoner, judge)), prisoner);
					pk::history_log(pk::get_current_turn_force_id(), force.color, pk::encode(pk::format("��ȹ���� \x1b[1x{}\x1b[0x��\x1b[2x{}\x1b[0x���� ����" , pk::decode(pk::get_name(prisoner)) , pk::decode(pk::get_name(judge) ) ) ) );
					
					if(force.relations[judge.get_force_id()] < 50)
						pk::add_relations(force, judge.get_force_id(), 50);
					else	
						pk::set_relations(force, judge.get_force_id(), 99);
				}

				int random = pk::rand(10);
				if(pk::get_aishou_distance(prisoner, judge.get_id()) <= 5 && random < prisoner.giri)
				{
					pk::add_like(prisoner, judge.get_id());
				}

				if(random < prisoner.giri * 2 && pk::get_aishou_distance(prisoner, judge.get_id()) <= 5)
				{
					if( pk::get_troops(force) > pk::get_troops(judge_force) && pk::get_city_count(force) > pk::get_city_count(judge_force)  && pk::get_force_list().count >= 4  )
					{
						int random = pk::rand (36);
						pk::set_ceasefire_timer(force, judge.get_force_id(), 36 + random);
						pk::history_log(pk::get_current_turn_force_id(), force.color, pk::encode(pk::format("\x1b[1x{}\x1b[0x���� \x1b[2x{}\x1b[0x���� ����" , pk::decode(pk::get_name(prisoner)) , pk::decode(pk::get_name(judge) ) ) ) );
					}
				}

				return ����ó��_�ع�;
			}
				
			if (!func_4b0740(info))
			{
				int random = pk::rand(5);
				if(pk::get_aishou_distance(prisoner, judge.get_id()) <= 5 && random < prisoner.giri)
				{
					pk::add_like(prisoner, judge.get_id());
				}
				
				return ����ó��_�ع�;
			}

			return ����ó��_����;
		}

		/***/
		bool func_4ae3a0(pk::person@ prisoner, pk::person@ judge)
		{
			if (!pk::is_alive(prisoner) or !pk::is_alive(judge))
				return false;
			//if (pk::get_person(prisoner).sex == ����_��)
				//return false;
			if (prisoner.sex == ����_��) return false;
			// Ư�� ������ ��� ó������ ����
			if (prisoner.get_id() == 660) return false;
			if (prisoner.get_id() == 18) return false;
			if (prisoner.get_id() == 343) return false;
			if (prisoner.get_id() == 635) return false;
			if (prisoner.get_id() == 98) return false;
			if (prisoner.get_id() == 395) return false;
			if (prisoner.get_id() == 432) return false;
			if (prisoner.get_id() == 515) return false;
			if (prisoner.get_id() == 185) return false;

			// ���θ� �����ϴ� ���
			if (pk::is_dislike(judge, prisoner.get_id()))
			{
				int d_aishou = pk::get_aishou_distance(prisoner, judge.get_id());
				int n = 100;

				if(d_aishou > 70) 
					n += 20;
				else if(d_aishou > 50) 
					n += 10;
				else if(d_aishou > 30) 
					n += 5;
				else if(d_aishou > 10) 
					n -= 5;
				else if(d_aishou > 5) 
					n -= 10;
				else 
					n -= 20;

				n += judge.stat[1] > judge.stat[2] + 10 ? (judge.stat[1] - judge.stat[2]) : 0;
				n -= (judge.giri - 2) * 20; 
				n -= (prisoner.giri * 2) * (judge.promotion == ���_�Ǹ� ? 5 : 1);
				n += pk::rand(20);
				n = pk::max(n, 0);

				return pk::rand_bool(n);
			}
				
			if (prisoner.mibun == �ź�_����)
			{
				pk::force@ judge_force = pk::get_force(judge.get_force_id());
				pk::force@ prisoner_force = pk::get_force(prisoner.get_force_id());

				if (!pk::is_alive(judge_force) or !pk::is_alive(prisoner_force))
					return false;

				int random = pk::rand(10);

				// ���ΰ� Ȳ���̰� ���� ���� Ȳ���� ��ȣ���� ��� ó��
				if (prisoner_force.title == ����_Ȳ�� and pk::is_protecting_the_emperor(judge_force) and judge.giri <= random)
					return true;

				// ���� Ȳ���̰� ���ΰ� ���� Ȳ���� ��ȣ���� ��� ó��
				if (pk::is_protecting_the_emperor(prisoner_force) and judge_force.title == ����_Ȳ�� and judge.giri <= random)
					return true;
			}

			return false;
		}

		/***/
		bool func_4af5b0(pk::person@ prisoner, pk::person@ judge)
		{
			int prisoner_id = prisoner.get_id();

			// �������� ��� ó������ ����(pk::is_gikyoudai �Լ��� ����ϴ� ���� �´ٰ� ������)
			//if (prisoner.gikyoudai == judge.gikyoudai) return false;
			if(pk::is_gikyoudai(prisoner, judge.get_id())) return false;				

			// �κ��� ��� ó������ ����
			if (pk::is_fuufu(judge, prisoner_id)) return false;

			// ���θ� ģ���ϴ� ��� ó������ ����
			if (pk::is_like(judge, prisoner_id)) return false;
			// ������ ��� ó������ ����
			if (prisoner.sex == ����_��) return false;
			// Ư�� ������ ��� ó������ ����
			if (prisoner.get_id() == 660) return false;
			if (prisoner.get_id() == 18) return false;
			if (prisoner.get_id() == 343) return false;
			if (prisoner.get_id() == 635) return false;
			if (prisoner.get_id() == 98) return false;
			if (prisoner.get_id() == 395) return false;
			if (prisoner.get_id() == 432) return false;
			if (prisoner.get_id() == 515) return false;
			if (prisoner.get_id() == 185) return false;
			

			int max_stat = 0;
			int avg_stat = 0;
			int death = 10;

			for (int i = 0; i < ����ɷ�_��; i++)
			{
				int s = prisoner.stat[i];
				max_stat = pk::max(max_stat, s);
				avg_stat = avg_stat + s;
			}
			avg_stat = avg_stat / ����ɷ�_��;

			switch (pk::get_scenario().battle_death)
			{
				case ����_����: death = 20; break;
				case ����_ǥ��: death = 20; break;
				case ����_����: death = 0; break;
			}
			
			int d_aishou = pk::get_aishou_distance(prisoner, judge.get_id());
					
			int n = 0;

			if (prisoner.mibun == �ź�_����)
			{
				if(d_aishou > 70) 
					n += 15;
				else if(d_aishou > 50) 
					n += 10;
				else if(d_aishou > 30) 
					n += 5;
				else if(d_aishou > 10) 
					n -= 5;
				else if(d_aishou > 5) 
					n -= 10;
				else 
					n -= 20;
				
				n += (judge.ambition + (prisoner.ambition*1.5f) ) * 8;
				n -= (pk::max(max_stat, 50) + pk::max(avg_stat, 50)) / 2;
				n += (20 - (judge.giri * 4) ) * 5;
				n -= (judge.promotion == ���_�Ǹ� ? prisoner.giri * 4 : prisoner.giri * -4);
				n -= death;
				n -= pk::rand(20 + (judge.giri * 5));
				n += judge.stat[1] > judge.stat[2] + 10 ? (judge.stat[1] - judge.stat[2]) : 0;
				n = pk::max(n, 0);
			}
			else
			{
				if(d_aishou > 70) 
					n += 20;
				else if(d_aishou > 50) 
					n += 10;
				else if(d_aishou > 30) 
					n += 5;
				else if(d_aishou > 10) 
					n -= 5;
				else if(d_aishou > 5) 
					n -= 10;
				else 
					n -= 20;

				n += 120 - (pk::max(max_stat, 50) + pk::max(avg_stat, 50)) / 2;
				n -= pk::max(prisoner.kouseki, 20000) / 2000 * (judge.promotion == ���_���� ? 1.5f : 1);
				n -= (prisoner.giri) * (judge.promotion == ���_�Ǹ� ? 5 : 1);
				n -= pk::rand(25) * (judge.promotion == ���_���� ? 1.5f : 1);
				n -= judge.giri * (10 + pk::rand(5));
				n -= death;
				n -= pk::rand(10 + (judge.giri * 2));
				n = pk::max(n, 0);
			}

			// ���ΰ� ���ָ� �����ϴ� ���
			if (pk::is_dislike(prisoner, judge.get_id()))
				 n = n + n;



			return pk::rand_bool(n);
		}

		/***/
		bool func_4b0740(const pk::prisoner_info &in info)
		{
			// �����Ų��� ��� �ع�
			if (!info.returnable) return false;

			// ������ ������ ���θ� ���� ���
			if (info.object.is_instance(pk::building::type_id))
			{
				// �δ밡 ������ �ƴ϶�� �ع�
				if (!info.taken_by.is_instance(pk::unit::type_id)) return false;

				pk::building@ building = pk::hex_object_to_building(info.object);
				pk::unit@ unit = pk::hex_object_to_unit(info.taken_by);
				int pay = 0;

				// �δ� ������� ���� ��
				for (int i = 0; i < 3; i++)
				{
					pk::person@ member = pk::get_person(unit.member[i]);
					if (pk::is_alive(member) and member.mibun >= �ź�_���� and member.mibun <= �ź�_�Ϲ�)
					{
						pk::rank@ rank = pk::get_rank(member.rank);
						if (pk::is_alive(rank))
							pay += rank.pay;
					}
				}

				// �δ밡 ��� �ִ� ���� ��� ��
				pay += (pk::get_person_list(pk::get_hex_object_id(unit), pk::mibun_flags(�ź�_����)).count + 2) * 50;

				pay *= 2;

				// ���� �����ϴٸ� �ع�
				if (unit.gold + pk::get_gold(building) < pay) return false;
			}
			// �δ븦 ������ ���θ� ���� ���
			else
			{
				pk::person@ taken_by;
				pk::building@ service;
				int pay = 0;

				if (info.taken_by.is_instance(pk::unit::type_id))
					@taken_by = pk::get_person(pk::hex_object_to_unit(info.taken_by).leader);
				else if (info.taken_by.is_instance(pk::building::type_id))
					@taken_by = pk::get_person(pk::get_taishu_id(pk::hex_object_to_building(info.taken_by)));
				else
					@taken_by = pk::get_person(pk::get_kunshu_id(info.taken_by));

				if (pk::is_alive(taken_by))
					@service = pk::get_building(taken_by.service);

				// ���θ� ���� ������ �Ҽ��� ���ٸ� �ع�
				if (!pk::is_alive(service)) return false;

				// �Ҽ� ���� ������� ���� ��
				pk::list<pk::person@> list = pk::get_person_list(service, pk::mibun_flags(�ź�_����, �ź�_�¼�, �ź�_�Ϲ�));
				for (int i = 0; i < list.count; i++)
				{
					pk::rank@ rank = pk::get_rank(list[i].rank);
					if (pk::is_alive(rank))
						pay += rank.pay;
				}

				// �Ҽ� ���� ���� ��� ��
				pay += (pk::get_person_list(pk::get_hex_object_id(service), pk::mibun_flags(�ź�_����)).count + 2) * 50;

				pay *= 2;

				// �Ҽ� �������� ��ȯ���� �� ���θ� ������ �� �ִ� ����� �����ϴٸ� �ع�
				if (pk::get_gold(service) < pay) return false;
			}

			return true;
		}
	}

	Main main;
}