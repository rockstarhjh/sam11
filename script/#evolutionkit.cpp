namespace evolutionkit
{
	class Main
	{
		Main()
		{
			if (!pk::NDEBUG)
				return;
			pk::reset_func(101);
			pk::set_func(101, pk::func101_t(func101));
			pk::reset_func(110);
			pk::set_func(110, pk::func110_t(func110));
			pk::reset_func(152);
			pk::set_func(152, pk::func152_t(func152));
			pk::reset_func(153);
			pk::set_func(153, pk::func153_t(func153));
			pk::reset_func(157);
			pk::set_func(157, pk::func157_t(func157));
			pk::reset_func(168);
			pk::set_func(168, pk::func168_t(func168));
			pk::reset_func(169);
			pk::set_func(169, pk::func169_t(func169));
			pk::reset_func(216);
			pk::set_func(216, pk::func216_t(func216));
			pk::reset_func(217);
			pk::set_func(217, pk::func216_t(func217));
			pk::reset_func(218);
			pk::set_func(218, pk::func216_t(func218));
			pk::reset_func(250);
			pk::set_func(250, pk::func250_t(func250));
			pk::reset_func(251);
			pk::set_func(251, pk::func251_t(func251));
			pk::reset_func(252);
			pk::set_func(252, pk::func252_t(func252));
			pk::reset_func(253);
			pk::set_func(253, pk::func253_t(func253));
			pk::reset_func(254);
			pk::set_func(254, pk::func254_t(func254));
			pk::reset_func(255);
			pk::set_func(255, pk::func255_t(func255));
			@func256_ = cast<pk::func256_t@>(pk::get_func(256));
			pk::reset_func(256);
			pk::set_func(256, pk::func256_t(func256));
			xml();
		}

		/** ��ǻ�� ¡�� �� ġ�� ���� �ݰ� */
		int func101(pk::city@ city, const pk::detail::arrayptr<pk::person@> &in actors, int troops)
		{
			int n = cast<pk::func101_t@>(pk::get_func(101, true))(city, actors, troops);
			if (!city.is_player()) n /= 2;
			return n;
		}

		/** ��ǻ�� ���� �߰� Ȯ�� 2�� */
		int func110(pk::building@ building, pk::person@ actor, pk::item@ item)
		{
			int n = pk::max((61 - item.value) / 20, 1);
			if (!actor.is_player())
				n *= 2;
			return n;
		}

		/** ����, �ױ� �� ���� ���� */
		int func152(pk::building@ building, int city_revenue)
		{
			return city_revenue * 0.01f;
		}

		/** ����, �ױ� ���� ���� ���� */
		int func153(pk::building@ building, int city_harvest)
		{
			return city_harvest * 0.01f;
		}

		/***/
		int func157(pk::person@ prisoner)
		{
			int n = prisoner.prisoner_timer;

			// ���ΰ� ���� 2�� �̸��� ��� Ż������ ����
			if (n < 2)
				return 0;

			n = n - 2;
			if (n < 1)
				n = 1;
			n = n * n * pk::max(prisoner.stat[����ɷ�_����], prisoner.stat[����ɷ�_����], 30) / 166;

			return pk::max(n, 1);
		}

		/***/
		void func168(pk::building@ base, pk::unit@ attacker)
		{
			pk::person@ leader;

			if (pk::is_alive(attacker))
				@leader = pk::get_person(attacker.leader);

			int n = 70;
			int charisma = 20;

			if (pk::is_alive(leader))
				charisma = leader.stat[����ɷ�_�ŷ�];

			pk::set_gold(base, pk::get_gold(base) * n / 100);
			pk::set_food(base, pk::get_food(base) * n / 100);
			pk::set_troops(base, pk::get_troops(base) * n / 100);
			for (int i = 0; i < ����_��; i++)
				pk::set_weapon_amount(base, i, pk::get_weapon_amount(base, i) * n / 100);

			pk::city@ city = pk::building_to_city(base);

			if (!pk::is_alive(city))
				return;

			int city_id = city.get_id();
			int city_force_id = city.get_force_id();
			pk::list<pk::building@> city_devs;
			pk::list<pk::building@> buildings = pk::get_building_list();

			for (int i = 0; i < buildings.count; i++)
			{
				pk::building@ building = buildings[i];
				if (pk::is_alive(building) and pk::get_city_id(building.get_pos()) == city_id)
				{
					switch (pk::get_facility_type(building))
					{
					case �ü�����_�����ü�:
						if (building.completed)
						{
							if (building.facility != �ü�_���۴�)
								city_devs.add(building);
						}
						else
						{
							if (building.facility == �ü�_���۴�)
							{
								pk::item@ item = pk::get_item(����_����);
								if (pk::is_alive(item))
									pk::kill(item);
							}
							else
							{
								pk::kill(building, false);
							}
						}
						break;

					case �ü�����_����ü�:
						if (pk::is_valid_force_id(city_force_id) and city_force_id == building.get_force_id())
						{
							int distance = pk::get_distance(city.get_pos(), building.get_pos());
							int n = 0;

							if (distance <= 4)
								n = 75;
							else if (distance <= 8)
								n = 50;
							else
								n = 30;

							if (pk::rand_bool(n))
								pk::set_district(building, pk::get_district(attacker.get_district_id()), 0);
							else if (pk::rand_bool(20))
								continue;
							else
								pk::kill(building, false);
						}
						break;
					}
				}
			}

			n = city_devs.count;
			if (pk::is_valid_normal_force_id(attacker.get_force_id()))
				n = n - pk::min(charisma / 20, n);
			city_devs.shuffle();
			for (int i = 0; i < n; i++)
				pk::kill(city_devs[i], false);
		}

		/** ���� �δ�� �Ʒ����� ������ �˺� ������ ��� ���� ��, ����, �� ������ ������� ���ϵ�����. */
		bool func169(pk::unit@ unit, int terrain_id)
		{
			if (unit.type == �δ�����_���� and (terrain_id == ����_�� or terrain_id == ����_���� or terrain_id == ����_��)) return false;
			return cast<pk::func169_t@>(pk::get_func(169, true))(unit, terrain_id);
		}

		/***/
		int func216(pk::unit@ unit, const pk::point &in pos)
		{
			if (unit.has_skill(Ư��_ȭ��))
				return 0;
			int n = pk::max(unit.troops * 0.01f, 50.f);
			n += pk::rand(n);
			if (unit.has_skill(Ư��_�))
				n *= 2;
			return n;
		}

		/***/
		int func217(pk::unit@ unit, const pk::point &in pos)
		{
			if (unit.has_skill(Ư��_�ص�))
				return 0;
			int n = pk::max(unit.troops * 0.04f, 200.f);
			n += pk::rand(n);
			return n;
		}

		/***/
		int func218(pk::unit@ unit, const pk::point &in pos)
		{
			if (unit.has_skill(Ư��_����) or unit.has_tech(�ⱳ_�����౺))
				return 0;
			int n = pk::max(unit.troops * 0.02f, 100.f);
			n += pk::rand(n);
			return n;
		}

		/***/
		void func250(pk::ai_context_base@ base_info, int src, const pk::list<pk::building@> &in dst_list)
		{
			int n = 0;
			int empty_dst_count = 0;			

			for (int i = 0; i < dst_list.count; i++)
			{
				pk::building@ building = dst_list[i];
				if (pk::is_alive(building))
				{
					int dst_force_id = building.get_force_id();
					if (pk::is_valid_force_id(dst_force_id))
					{
						if (isEnemy(src, building.get_id()))
							n++;
					}
					else
					{
						empty_dst_count++;
					}
				}
			}

			if (empty_dst_count > 0)
				n++;

			base_info.num_enemy_routes = n;
		}

		bool isEnemy(int src, int dst)
		{
			pk::building@ src_building = pk::get_building(src);
			pk::building@ dst_building = pk::get_building(dst);
			int src_force_id = src_building.get_force_id();
			int dst_force_id = dst_building.get_force_id();
			int route;

			if (pk::is_reachable_neighbor(src, dst, src_force_id))
				return true;

			if (pk::is_reachable_neighbor(dst, src, dst_force_id))
			{
				if (dst < �ǹ�_���ó� and dst_building.get_troops() * 2 < src_building.get_troops())
					return false;
				return true;
			}

			route = pk::get_route(src, dst, src_force_id);
			if (route != ���_����)
				return true;

			route = pk::get_route(dst, src, dst_force_id);
			if (route == ���_������ or route == ���_���� or route == ���_����)
			{
				if (dst < �ǹ�_���ó� and dst_building.get_troops() * 2 < src_building.get_troops())
					return false;
			}
			return route != ���_����;
		}

		/***/
		void func251(pk::ai_context_base@ base_info, pk::building@ base)
		{
			if (base_info.status == ��������_�Ĺ� and base_info.num_idle_officers > 0 and base.get_id() > �ǹ�_��������)
				base_info.ap_needed = 20;
		}

		/***/
		void func252(pk::ai_context@ context)
		{
			@context_ = @context;
			context.bases.sort(function(a, b)
			{
				if ((a.get_id() >= �ǹ�_�������� and b.get_id() < �ǹ�_��������) or (b.get_id() >= �ǹ�_�������� and a.get_id() < �ǹ�_��������))
					return a.get_id() > b.get_id();
				return main.context_.base[a.get_id()].status < main.context_.base[b.get_id()].status;
			});
		}

		pk::ai_context@ context_;

		/***/
		int func253(pk::building@ src, int src_rank, pk::building@ dst, int dst_troops)
		{
			uint dst_max_troops = pk::get_max_troops(dst);

			// �� ����
			if (dst.get_force_id() == -1)
			{
				pk::city@ city = pk::building_to_city(dst);
				// �����̳� �ױ��� ���
				if (city is null)
					return dst_max_troops / 5;
				// ������ ��� �̿� ���ÿ� �� ������ �����Ѵٸ�
				for (int i = 0; i < 6; i++)
				{
					if (city.neighbor[i] != -1 and pk::is_enemy(city, pk::get_city(city.neighbor[i])))
						return dst_max_troops / 2;
				}
				// ������ ������ ���
				return dst_max_troops / 4;
			}

			// ���� �� ����(�ٸ� ���� �δ� ���� ������ ����)
			int src_force_id = src.get_force_id();
			int dst_id = dst.get_id();
			dst_troops = pk::get_troops(dst);
			array<pk::unit@> arr = pk::list_to_array(pk::get_unit_list());
			for (int i = 0; i < arr.length; i++)
			{
				pk::unit@ unit = arr[i];
				if (unit.get_force_id() != src_force_id and pk::get_building_id(unit.get_pos()) == dst_id)
					dst_troops += unit.troops;
			}

			if (dst_troops > dst_max_troops)
				return dst_troops + dst_troops / 4;
			else if (dst_troops * 2 > dst_max_troops)
				return dst_max_troops + dst_max_troops / 4;
			else
				return pk::max(dst_troops, dst_max_troops / 4) * 3;
		}

		/***/
		int func254(pk::building@ building, int troops)
		{
			return troops * 1.25f;
		}

		/***/
		void func255(pk::ai_context@ context, pk::building@ building)
		{
			int building_id = building.get_id();
			pk::ai_context_base@ base = context.base[building_id];

			if (base.enemies_around3)
			{
				context.push_cmd(����AI_���);
				if (building_id >= �ǹ�_���ý��� and building_id < �ǹ�_���ó�)
				{
					// �÷��̾ �������� ���� ��� ��ȭ
					if (base.num_player_units > 0)
					{
						context.push_cmd(����AI_����);
						context.push_cmd(����AI_¡��);
						context.push_cmd(����AI_����);
						context.push_cmd(����AI_¡��);
						context.push_cmd(����AI_����);
						context.push_cmd(����AI_����);
						context.push_cmd(����AI_����);
						context.push_cmd(����AI_ö��);
					}
					else
					{
						context.push_cmd(����AI_¡��);
						context.push_cmd(����AI_����);
						context.push_cmd(����AI_����);
						context.push_cmd(����AI_ö��);
					}
				}
				return;
			}

			if (base.num_idle_officers == 0)
				return;

			if (building_id >= �ǹ�_���ý��� and building_id < �ǹ�_���ó�)
			{
				uint gold = pk::get_gold(building);
				uint officers_needed = pk::max(base.officers_needed, 10);
				uint total_weapons = 0;
				for (int i = ����_â; i <= ����_����; i++)
					total_weapons = total_weapons + pk::get_weapon_amount(building, i);

				switch (base.status)
				{
				case ��������_�Ĺ�:
					context.push_cmd(����AI_����);
					context.push_cmd(����AI_����);
					context.push_cmd(����AI_�ּ�����Ž��);
					context.push_cmd(����AI_�ּҹ�����);
					context.push_cmd(����AI_�ּ�Ÿ���¹�����);
					context.push_cmd(����AI_����);
					context.push_cmd(����AI_�ŷ�);
					context.push_cmd(����AI_�跫);
					context.push_cmd(����AI_����);
					context.push_cmd(����AI_���ü���);
					context.push_cmd(����AI_��������);
					context.push_cmd(����AI_�̵�);
					context.push_cmd(����AI_�ŷ�2);
					context.push_cmd(����AI_¡��);
					context.push_cmd(����AI_�Ʒ�);
					context.push_cmd(����AI_ö��);
					context.push_cmd(����AI_����);
					context.push_cmd(����AI_����պ�);
					context.push_cmd(����AI_��������);
					context.push_cmd(����AI_����Ž��);
					context.push_cmd(����AI_������);
					context.push_cmd(����AI_Ÿ���¹�����);
					context.push_cmd(����AI_����);
					context.push_cmd(����AI_�跫);
					break;

				case ��������_���:
					context.push_cmd(����AI_����);
					context.push_cmd(����AI_���ü���);
					context.push_cmd(����AI_��������);
					context.push_cmd(����AI_�̵�);
					context.push_cmd(����AI_�ּ�����Ž��);
					context.push_cmd(����AI_�ּҹ�����);
					context.push_cmd(����AI_�ּ�Ÿ���¹�����);
					context.push_cmd(����AI_����);
					context.push_cmd(����AI_¡��);
					context.push_cmd(����AI_����);
					context.push_cmd(����AI_�跫);
					context.push_cmd(����AI_�ŷ�2);
					context.push_cmd(����AI_�ŷ�);
					context.push_cmd(����AI_����);
					context.push_cmd(����AI_�Ʒ�);
					context.push_cmd(����AI_ö��);
					context.push_cmd(����AI_����);
					context.push_cmd(����AI_����պ�);
					context.push_cmd(����AI_��������);
					context.push_cmd(����AI_����Ž��);
					context.push_cmd(����AI_������);
					context.push_cmd(����AI_Ÿ���¹�����);
					context.push_cmd(����AI_����);
					context.push_cmd(����AI_�跫);
					break;

				case ��������_����:
					context.push_cmd(����AI_����);
					context.push_cmd(����AI_��ġ);
					context.push_cmd(����AI_��������);
					context.push_cmd(����AI_����);
					context.push_cmd(����AI_�ּ�����Ž��);
					context.push_cmd(����AI_�ּҹ�����);
					context.push_cmd(����AI_�ּ�Ÿ���¹�����);
					context.push_cmd(����AI_����);
					context.push_cmd(����AI_ö��);
					context.push_cmd(����AI_����պ�);
					context.push_cmd(����AI_����);
					// ����� ���� ����� ��� �����ü� 2���� �Ǽ�
					if (base.num_officers >= officers_needed and gold > 1500)
						context.push_cmd(����AI_����);
					// ���Ⱑ ���º��� ���ڸ��ٸ� ������� �켱
					if (total_weapons < pk::get_troops(building) - 5000)
						context.push_cmd(����AI_����);
					context.push_cmd(����AI_¡��);
					context.push_cmd(����AI_����);
					context.push_cmd(����AI_�Ʒ�);
					context.push_cmd(����AI_�ŷ�2);
					context.push_cmd(����AI_�ŷ�);
					context.push_cmd(����AI_����);
					context.push_cmd(����AI_�̵�);
					context.push_cmd(����AI_����Ž��);
					context.push_cmd(����AI_������);
					context.push_cmd(����AI_Ÿ���¹�����);
					context.push_cmd(����AI_����);
					context.push_cmd(����AI_�跫);
					context.push_cmd(����AI_�跫);
					context.push_cmd(����AI_�跫);
					break;

				case ��������_����:
					context.push_cmd(����AI_���);
					// �� ����ü��� ����
					if (base.num_enemy_units == 0)
					{
						context.push_cmd(����AI_����պ�);
						context.push_cmd(����AI_����);
						if (base.num_officers >= officers_needed and gold > 1500)
							context.push_cmd(����AI_����);
					}
					// �� �δ� ����
					else
					{
						// �ڼ��� �δ� ���� ���� �ִ� ���� ���� ���� �� ���� �δ� ������ ���� ���� ö��
						if (base.num_own_units + base.num_idle_officers < base.num_enemy_units)
						{
							context.push_cmd(����AI_ö��);
						}
						else if (base.num_own_units > base.num_enemy_units and pk::get_troops(building) > 15000)
						{
							context.push_cmd(����AI_����պ�);
							context.push_cmd(����AI_����);
						}
					}
					// ���Ⱑ ���º��� ���ڸ��ٸ� ������� �켱
					if (total_weapons < pk::get_troops(building) - 5000)
						context.push_cmd(����AI_����);
					context.push_cmd(����AI_¡��);
					context.push_cmd(����AI_�Ʒ�);
					context.push_cmd(����AI_�ŷ�);
					context.push_cmd(����AI_����);
					context.push_cmd(����AI_����);
					context.push_cmd(����AI_�ŷ�2);
					context.push_cmd(����AI_����);
					context.push_cmd(����AI_����Ž��);
					context.push_cmd(����AI_������);
					context.push_cmd(����AI_Ÿ���¹�����);
					context.push_cmd(����AI_����);
					context.push_cmd(����AI_�跫);
					context.push_cmd(����AI_�跫);
					context.push_cmd(����AI_�跫);
					break;
				}
			}
			else
			{
				switch (base.status)
				{
				case ��������_�Ĺ�:
					context.push_cmd(����AI_����);
					context.push_cmd(����AI_���ü���);
					context.push_cmd(����AI_��������);
					context.push_cmd(����AI_�̵�);
					context.push_cmd(����AI_�Ʒ�);
					context.push_cmd(����AI_�跫);
					context.push_cmd(����AI_����Ž��);
					context.push_cmd(����AI_������);
					context.push_cmd(����AI_Ÿ���¹�����);
					context.push_cmd(����AI_����);
					context.push_cmd(����AI_�跫);
					break;

				case ��������_���:
					context.push_cmd(����AI_����);
					context.push_cmd(����AI_���ü���);
					context.push_cmd(����AI_��������);
					context.push_cmd(����AI_�̵�);
					context.push_cmd(����AI_����);
					context.push_cmd(����AI_�Ʒ�);
					context.push_cmd(����AI_�跫);
					context.push_cmd(����AI_����Ž��);
					context.push_cmd(����AI_������);
					context.push_cmd(����AI_Ÿ���¹�����);
					context.push_cmd(����AI_����);
					context.push_cmd(����AI_�跫);
					break;

				case ��������_����:
					context.push_cmd(����AI_����);
					context.push_cmd(����AI_����);
					context.push_cmd(����AI_��ġ);
					context.push_cmd(����AI_�Ʒ�);
					context.push_cmd(����AI_���ü���);
					context.push_cmd(����AI_�̵�);
					context.push_cmd(����AI_��������);
					context.push_cmd(����AI_�跫);
					context.push_cmd(����AI_����Ž��);
					context.push_cmd(����AI_������);
					context.push_cmd(����AI_Ÿ���¹�����);
					context.push_cmd(����AI_����);
					context.push_cmd(����AI_�跫);
					break;

				case ��������_����:
					context.push_cmd(����AI_���);
					context.push_cmd(����AI_�Ʒ�);
					context.push_cmd(����AI_���ü���);
					context.push_cmd(����AI_�̵�);
					context.push_cmd(����AI_���ü���);
					context.push_cmd(����AI_����);
					context.push_cmd(����AI_�跫);
					break;
				}
			}
		}

		/** ��ǻ�� �ൿ�� �ִ� */
		void func256(pk::ai_context@ context, pk::building@ building, int cmd)
		{
			if (!building.is_player())
			{
				if (pk::get_scenario().ai_table.force[building.get_force_id()].troops_rank > 49)
				{
					pk::get_district(building.get_district_id()).ap = 255;
					context.ap = 255;
				}
			}

			if (func256_ !is null)
				func256_(context, building, cmd);
		}

		pk::func256_t@ func256_;

		void xml()
		{
			// ���
			pk::load_xml("""
			<pk trace="true">
				<���>
					<�Ÿ� â����="3"/>
					<�����౺�Ÿ� â����="3"/>
				</���>
				<����>
					<�̿� ��ȣ="3" ���="�Ϲ�" x="-1" y="-1"/>
					<�Ÿ� ����="1"/>
					<�����౺�Ÿ� ����="1"/>
				</����>
				<����>
					<�̿� ��ȣ="4" ���="����" x="129" y="110"/>
					<�̿� ��ȣ="5" ����="��"/>
					<�Ÿ� ����="2" ������="2"/>
					<�����౺�Ÿ� ������="2"/>
				</����>
				<����>
					<�̿� ��ȣ="1" ���="�Ϲ�" x="-1" y="-1"/>
					<�Ÿ� ����="1"/>
					<�����౺�Ÿ� ����="1"/>
				</����>
				<����>
					<�Ÿ� ��="2"/>
					<�����౺�Ÿ� ��="2"/>
				</����>
				<��>
					<�̿� ��ȣ="4" ����="ȣ�ΰ�" ���="�Ϲ�" x="-1" y="-1"/>
					<�Ÿ� ����="2" ȣ�ΰ�="1"/>
					<�����౺�Ÿ� ����="2" ȣ�ΰ�="1"/>
				</��>
				<�Ǿ�>
					<�̿� ��ȣ="1" ���="�Ϲ�" x="-1" y="-1"/>
					<�Ÿ� ȸ��="1"/>
				</�Ǿ�>
				<ȸ��>
					<�̿� ��ȣ="0" ���="�Ϲ�" x="-1" y="-1"/>
					<�Ÿ� �Ǿ�="1"/>
				</ȸ��>
				<����>
					<�̿� ��ȣ="0" ���="����" x="129" y="110"/>
					<�Ÿ� ����="2"/>
				</����>
				<ȣ�ΰ�>
					<�̿� ��ȣ="3" ����="��" ���="�Ϲ�" x="-1" y="-1"/>
					<�Ÿ� ��="1"/>
					<�����౺�Ÿ� ��="1"/>
				</ȣ�ΰ�>
				<�����>
					<�̿� ��ȣ="2" ����="��"/>
					<�Ÿ� â����="2"/>
					<�����౺�Ÿ� â����="2"/>
				</�����>
				<â����>
					<�̿� ��ȣ="1" ����="��"/>
					<�̿� ��ȣ="2" ����="��"/>
					<�Ÿ� ���="3" �����="2" ������="2"/>
					<�����౺�Ÿ� ���="3" �����="2" ������="2"/>
				</â����>
				<������>
					<�̿� ��ȣ="3" ����="��"/>
					<�Ÿ� â����="2"/>
					<�����౺�Ÿ� â����="2"/>
				</������>
				<�ظ���>
					<�̿� ��ȣ="1" ����="��"/>
					<�Ÿ� ������="2"/>
					<�����౺�Ÿ� ������="2"/>
				</�ظ���>
				<������>
					<�̿� ��ȣ="0" ����="��"/>
					<�̿� ��ȣ="1" ����="��"/>
					<�̿� ��ȣ="2" ����="��"/>
					<�Ÿ� ����="2" �ظ���="2"/>
					<�����౺�Ÿ� ����="2" �ظ���="2"/>
				</������>
				<������>
					<�̿� ��ȣ="3" ����="��"/>
					<�Ÿ� ȣ����="2"/>
					<�����౺�Ÿ� ȣ����="2"/>
				</������>
				<ȣ����>
					<�̿� ��ȣ="2" ����="��"/>
					<�̿� ��ȣ="3" ����="��"/>
					<�Ÿ� ������="2" ȯ����="2"/>
					<�����౺�Ÿ� ������="2" ȯ����="2"/>
				</ȣ����>
				<ȯ����>
					<�̿� ��ȣ="1" ����="��"/>
					<�Ÿ� ȣ����="2"/>
					<�����౺�Ÿ� ȣ����="2"/>
				</ȯ����>
			</pk>
			""");

			// ����
			pk::load_xml("""
			<pk trace="true">
				<���� ��ȣ="59">
					<���� ��="��"/>
				</����>
			</pk>
			""");

			// ��Ÿ
			pk::load_xml("""
			<pk trace="true">
				<�Ǽ���ɹ��׼��� ��="true"/>
				<����ġ�г�Ƽ ��="true"/>
				<�����ݽ����� ��="true"/>
				<������� ��="true"/>
				<������г�Ƽ �ʱ�="" ���="0.9" Ư��="0.7"/>
				<����.�ɷ»���ʿ����ġ ��="30"/>
				<����.�ִ�ɷ�ġ ��="130"/>
				<��Ȱ�������Է¹��� ��="true"/>
				<��ȭ�����׼��� ��="true"/>
				<���ӱ������� ��="true"/>
				<�ϱ���.�ΰ���������ǥ�� ��="true"/>
				<���δ������˸� ��="false"/>
				<��������Ʈ����Ű��� ��="true"/>
				<��Ư�⿬�� ��="true"/>
				<��ǻ�ͳ�Ȱ��ȭ ��="true"/>
				<Ÿ�ϱ�ݼ��� ��="true"/>
				<���࿬�����׼��� ��="true"/>
			</pk>
			""");

			// ��
			pk::load_xml("""
			<pk trace="true">
				<!-- ȣ�� -->
				<hex x="92" y="56" ����="����"/>
				<hex x="92" y="58" ����="����"/>

				<!-- ȣ�ΰ� -->
				<hex x="90" y="76" ����="����"/>
				<hex x="90" y="78" ����="����"/>

				<!-- ���� -->
				<hex x="61" y="76" ����="����"/>
				<hex x="61" y="78" ����="����"/>

				<!-- �԰�� -->
				<hex x="68" y="77" ����="����"/>
				<hex x="68" y="79" ����="����"/>

				<!-- ���� -->
				<hex x="68" y="85" ����="����"/>
				<hex x="68" y="87" ����="����"/>

				<!-- ����� -->
				<hex x="26" y="83" ����="����"/>
				<hex x="26" y="84" ����="����"/>
				<hex x="28" y="83" ����="����"/>
				<hex x="28" y="84" ����="����"/>

				<!-- �˰� -->
				<hex x="13" y="96" ����="����"/>
				<hex x="13" y="97" ����="����"/>
				<hex x="15" y="96" ����="����"/>
				<hex x="15" y="97" ����="����"/>

				<!-- ���Ͱ� -->
				<hex x="22" y="102" ����="����"/>
				<hex x="22" y="103" ����="����"/>
				<hex x="24" y="102" ����="����"/>
				<hex x="24" y="103" ����="����"/>

				<!-- ����� -->
				<hex x="11" y="118" ����="����"/>
				<hex x="11" y="120" ����="����"/>

				<!-- ���װ� -->
				<hex x="7" y="124" ����="����"/>
				<hex x="7" y="125" ����="����"/>
				<hex x="9" y="124" ����="����"/>
				<hex x="9" y="125" ����="����"/>

				<!-- ���� -->
				<hex x="7" y="53" ����="21"/>
				<hex x="7" y="54" ����="21"/>
				<hex x="7" y="55" ����="21"/>
				<hex x="8" y="53" ����="21"/>
				<hex x="8" y="54" ����="21"/>
				<hex x="8" y="55" ����="21"/>
				<hex x="8" y="56" ����="21"/>
				<hex x="8" y="57" ����="21"/>
				<hex x="9" y="52" ����="21"/>
				<hex x="9" y="53" ����="21"/>
				<hex x="9" y="54" ����="21"/>
				<hex x="9" y="55" ����="21"/>
				<hex x="9" y="56" ����="21"/>
				<hex x="10" y="52" ����="21"/>
				<hex x="10" y="53" ����="21"/>
				<hex x="10" y="54" ����="21"/>
				<hex x="10" y="55" ����="21"/>
				<hex x="10" y="56" ����="21"/>
				<hex x="11" y="51" ����="21"/>
				<hex x="11" y="52" ����="21"/>
				<hex x="11" y="53" ����="21"/>
				<hex x="11" y="54" ����="21"/>
				<hex x="11" y="55" ����="21"/>
				<hex x="12" y="51" ����="21"/>
				<hex x="12" y="52" ����="21"/>
				<hex x="12" y="53" ����="21"/>
				<hex x="12" y="54" ����="21"/>
				<hex x="12" y="55" ����="21"/>
				<hex x="13" y="50" ����="21"/>
				<hex x="13" y="51" ����="21"/>
				<hex x="13" y="52" ����="21"/>
				<hex x="13" y="53" ����="21"/>
				<hex x="13" y="54" ����="21"/>
				<hex x="13" y="55" ����="21"/>
				<hex x="14" y="51" ����="21"/>
				<hex x="14" y="52" ����="21"/>
				<hex x="14" y="53" ����="21"/>
				<hex x="14" y="54" ����="21"/>
				<hex x="14" y="55" ����="21"/>
				<hex x="14" y="56" ����="21"/>

				<!-- õ�� -->
				<hex x="9" y="57" ����="20"/>
				<hex x="10" y="57" ����="20"/>
				<hex x="10" y="58" ����="20"/>
				<hex x="11" y="56" ����="20"/>
				<hex x="11" y="57" ����="20"/>
				<hex x="12" y="56" ����="20"/>
				<hex x="12" y="57" ����="20"/>
				<hex x="12" y="58" ����="20"/>
				<hex x="13" y="56" ����="20"/>
				<hex x="13" y="57" ����="20"/>
				<hex x="13" y="58" ����="20"/>
				<hex x="14" y="57" ����="20"/>
				<hex x="14" y="58" ����="20"/>

				<!-- ���� -->
				<hex x="15" y="55" ����="19"/>
				<hex x="15" y="56" ����="19"/>
				<hex x="15" y="57" ����="19"/>

				<!-- ȣ�ΰ� -->
				<hex x="90" y="84" ����="43"/>
				<hex x="90" y="85" ����="43"/>
				<hex x="90" y="86" ����="43"/>
				<hex x="90" y="87" ����="43"/>
				<hex x="91" y="83" ����="43"/>
				<hex x="91" y="84" ����="43"/>
				<hex x="91" y="85" ����="43"/>
				<hex x="91" y="86" ����="43"/>
				<hex x="92" y="83" ����="43"/>
				<hex x="92" y="84" ����="43"/>
				<hex x="93" y="83" ����="43"/>

				<!-- �� -->
				<hex x="89" y="84" ����="16"/>
				<hex x="89" y="85" ����="16"/>
				<hex x="89" y="86" ����="16"/>
				<hex x="89" y="87" ����="16"/>

				<!-- ���� -->
				<hex x="121" y="76" ����="9"/>
				<hex x="121" y="77" ����="9"/>
				<hex x="121" y="78" ����="9"/>
				<hex x="121" y="79" ����="9"/>
				<hex x="121" y="80" ����="9"/>
				<hex x="121" y="81" ����="9"/>
				<hex x="122" y="77" ����="9"/>
				<hex x="122" y="78" ����="9"/>
				<hex x="122" y="79" ����="9"/>
				<hex x="122" y="80" ����="9"/>
				<hex x="122" y="81" ����="9"/>
				<hex x="123" y="77" ����="9"/>
				<hex x="123" y="78" ����="9"/>
				<hex x="123" y="79" ����="9"/>
				<hex x="123" y="80" ����="9"/>
				<hex x="124" y="78" ����="9"/>
				<hex x="124" y="79" ����="9"/>
				<hex x="124" y="80" ����="9"/>
				<hex x="124" y="81" ����="9"/>

				<!-- ���� -->
				<hex x="119" y="77" ����="11"/>
				<hex x="119" y="78" ����="11"/>
				<hex x="119" y="79" ����="11"/>
				<hex x="119" y="80" ����="11"/>
				<hex x="120" y="77" ����="11"/>
				<hex x="120" y="78" ����="11"/>
				<hex x="120" y="79" ����="11"/>
				<hex x="120" y="80" ����="11"/>

				<!-- ���� -->
				<hex x="119" y="81" ����="12"/>
				<hex x="119" y="82" ����="12"/>
				<hex x="120" y="81" ����="12"/>
				<hex x="120" y="82" ����="12"/>

				<!-- �Ǿ� -->
				<hex x="169" y="115" ����="22"/>
				<hex x="169" y="116" ����="22"/>
				<hex x="169" y="117" ����="22"/>
				<hex x="169" y="118" ����="22"/>
				<hex x="169" y="119" ����="22"/>
				<hex x="169" y="120" ����="22"/>
				<hex x="170" y="113" ����="22"/>
				<hex x="170" y="114" ����="22"/>
				<hex x="170" y="115" ����="22"/>
				<hex x="170" y="116" ����="22"/>
				<hex x="170" y="117" ����="22"/>
				<hex x="170" y="118" ����="22"/>
				<hex x="170" y="119" ����="22"/>
				<hex x="170" y="120" ����="22"/>
				<hex x="171" y="111" ����="22"/>
				<hex x="171" y="112" ����="22"/>
				<hex x="171" y="113" ����="22"/>
				<hex x="171" y="114" ����="22"/>
				<hex x="171" y="115" ����="22"/>
				<hex x="171" y="116" ����="22"/>
				<hex x="171" y="117" ����="22"/>
				<hex x="171" y="118" ����="22"/>
				<hex x="171" y="119" ����="22"/>

				<!-- �Ǿ� -->
				<hex x="169" y="103" ����="22"/>
				<hex x="169" y="104" ����="22"/>
				<hex x="170" y="103" ����="22"/>
				<hex x="170" y="104" ����="22"/>
				<hex x="170" y="105" ����="22"/>
				<hex x="171" y="101" ����="22"/>
				<hex x="171" y="102" ����="22"/>
				<hex x="171" y="103" ����="22"/>
				<hex x="171" y="104" ����="22"/>
				<hex x="171" y="105" ����="22"/>
				<hex x="171" y="106" ����="22"/>
				<hex x="171" y="107" ����="22"/>
				<hex x="171" y="108" ����="22"/>
				<hex x="171" y="109" ����="22"/>
				<hex x="171" y="110" ����="22"/>
				<hex x="172" y="102" ����="22"/>
				<hex x="172" y="103" ����="22"/>
				<hex x="172" y="104" ����="22"/>
				<hex x="172" y="105" ����="22"/>
				<hex x="172" y="106" ����="22"/>
				<hex x="172" y="107" ����="22"/>
				<hex x="172" y="108" ����="22"/>
				<hex x="173" y="102" ����="22"/>
				<hex x="173" y="103" ����="22"/>
				<hex x="173" y="104" ����="22"/>
				<hex x="174" y="103" ����="22"/>

				<!-- ȸ�� -->
				<hex x="172" y="115" ����="24"/>
				<hex x="172" y="116" ����="24"/>
				<hex x="172" y="117" ����="24"/>
				<hex x="172" y="118" ����="24"/>
				<hex x="173" y="115" ����="24"/>
				<hex x="173" y="116" ����="24"/>
				<hex x="173" y="117" ����="24"/>
				<hex x="174" y="116" ����="24"/>
				<hex x="174" y="117" ����="24"/>

				<!-- ��� -->
				<hex x="122" y="161" ����="31"/>
				<hex x="122" y="162" ����="31"/>
				<hex x="122" y="163" ����="31"/>
				<hex x="122" y="164" ����="31"/>
				<hex x="123" y="157" ����="31"/>
				<hex x="123" y="158" ����="31"/>
				<hex x="123" y="159" ����="31"/>
				<hex x="123" y="160" ����="31"/>
				<hex x="123" y="161" ����="31"/>
				<hex x="123" y="162" ����="31"/>
				<hex x="123" y="163" ����="31"/>
				<hex x="123" y="164" ����="31"/>
				<hex x="123" y="165" ����="31"/>
				<hex x="123" y="166" ����="31"/>
				<hex x="124" y="158" ����="31"/>
				<hex x="124" y="159" ����="31"/>
				<hex x="124" y="160" ����="31"/>
				<hex x="124" y="161" ����="31"/>
				<hex x="124" y="162" ����="31"/>
				<hex x="124" y="163" ����="31"/>
				<hex x="124" y="164" ����="31"/>
				<hex x="124" y="165" ����="31"/>
				<hex x="124" y="166" ����="31"/>
				<hex x="124" y="167" ����="31"/>
				<hex x="125" y="157" ����="31"/>
				<hex x="125" y="158" ����="31"/>
				<hex x="125" y="159" ����="31"/>
				<hex x="125" y="160" ����="31"/>
				<hex x="125" y="161" ����="31"/>
				<hex x="125" y="162" ����="31"/>
				<hex x="125" y="163" ����="31"/>
				<hex x="125" y="164" ����="31"/>
				<hex x="125" y="165" ����="31"/>
				<hex x="125" y="166" ����="31"/>
				<hex x="125" y="167" ����="31"/>
				<hex x="126" y="157" ����="31"/>
				<hex x="126" y="158" ����="31"/>
				<hex x="126" y="159" ����="31"/>
				<hex x="126" y="160" ����="31"/>
				<hex x="126" y="161" ����="31"/>
				<hex x="126" y="162" ����="31"/>
				<hex x="126" y="163" ����="31"/>
				<hex x="126" y="164" ����="31"/>
				<hex x="126" y="165" ����="31"/>
				<hex x="126" y="166" ����="31"/>
				<hex x="126" y="167" ����="31"/>
				<hex x="126" y="168" ����="31"/>
				<hex x="127" y="157" ����="31"/>
				<hex x="127" y="158" ����="31"/>
				<hex x="127" y="159" ����="31"/>
				<hex x="127" y="160" ����="31"/>
				<hex x="127" y="161" ����="31"/>
				<hex x="127" y="162" ����="31"/>
				<hex x="127" y="163" ����="31"/>
				<hex x="127" y="164" ����="31"/>
				<hex x="127" y="165" ����="31"/>
				<hex x="127" y="166" ����="31"/>
				<hex x="127" y="167" ����="31"/>
				<hex x="126" y="168" ����="31"/>
				<hex x="128" y="165" ����="31"/>
				<hex x="128" y="166" ����="31"/>
				<hex x="128" y="167" ����="31"/>
				<hex x="129" y="166" ����="31"/>

				<!-- ���� -->
				<hex x="32" y="122" ����="35"/>
				<hex x="32" y="123" ����="35"/>
				<hex x="32" y="124" ����="35"/>
				<hex x="32" y="125" ����="35"/>
				<hex x="32" y="126" ����="35"/>
				<hex x="32" y="127" ����="35"/>
				<hex x="33" y="121" ����="35"/>
				<hex x="33" y="122" ����="35"/>
				<hex x="33" y="123" ����="35"/>
				<hex x="33" y="124" ����="35"/>
				<hex x="33" y="125" ����="35"/>
				<hex x="33" y="126" ����="35"/>
				<hex x="34" y="121" ����="35"/>
				<hex x="34" y="122" ����="35"/>
				<hex x="34" y="123" ����="35"/>
				<hex x="34" y="124" ����="35"/>
				<hex x="34" y="125" ����="35"/>
				<hex x="34" y="126" ����="35"/>
				<hex x="35" y="120" ����="35"/>
				<hex x="35" y="121" ����="35"/>
				<hex x="35" y="122" ����="35"/>
				<hex x="35" y="123" ����="35"/>
				<hex x="35" y="124" ����="35"/>
				<hex x="36" y="120" ����="35"/>
				<hex x="36" y="121" ����="35"/>
				<hex x="36" y="122" ����="35"/>
				<hex x="36" y="123" ����="35"/>
				<hex x="36" y="124" ����="35"/>
				<hex x="37" y="119" ����="35"/>
				<hex x="37" y="120" ����="35"/>
				<hex x="37" y="121" ����="35"/>
				<hex x="37" y="122" ����="35"/>
				<hex x="37" y="123" ����="35"/>
				<hex x="38" y="120" ����="35"/>
				<hex x="38" y="121" ����="35"/>
				<hex x="38" y="122" ����="35"/>
				<hex x="38" y="123" ����="35"/>
				<hex x="39" y="120" ����="35"/>
				<hex x="39" y="121" ����="35"/>
				<hex x="39" y="122" ����="35"/>
				<hex x="40" y="120" ����="35"/>
				<hex x="40" y="121" ����="35"/>
				<hex x="40" y="122" ����="35"/>
				<hex x="40" y="123" ����="35"/>
				<hex x="41" y="115" ����="35"/>
				<hex x="41" y="116" ����="35"/>
				<hex x="41" y="117" ����="35"/>
				<hex x="41" y="118" ����="35"/>
				<hex x="41" y="119" ����="35"/>
				<hex x="41" y="120" ����="35"/>
				<hex x="41" y="121" ����="35"/>
				<hex x="41" y="122" ����="35"/>
				<hex x="41" y="123" ����="35"/>
				<hex x="42" y="115" ����="35"/>
				<hex x="42" y="116" ����="35"/>
				<hex x="42" y="117" ����="35"/>
				<hex x="42" y="118" ����="35"/>
				<hex x="42" y="119" ����="35"/>
				<hex x="42" y="120" ����="35"/>
				<hex x="42" y="121" ����="35"/>
				<hex x="42" y="122" ����="35"/>
				<hex x="42" y="123" ����="35"/>
				<hex x="42" y="124" ����="35"/>
				<hex x="43" y="114" ����="35"/>
				<hex x="43" y="115" ����="35"/>
				<hex x="43" y="116" ����="35"/>
				<hex x="43" y="117" ����="35"/>
				<hex x="43" y="118" ����="35"/>
				<hex x="43" y="119" ����="35"/>
				<hex x="43" y="120" ����="35"/>
				<hex x="43" y="121" ����="35"/>
				<hex x="43" y="122" ����="35"/>
				<hex x="43" y="123" ����="35"/>
				<hex x="44" y="115" ����="35"/>
				<hex x="44" y="116" ����="35"/>
				<hex x="44" y="117" ����="35"/>
				<hex x="44" y="118" ����="35"/>
				<hex x="44" y="119" ����="35"/>
				<hex x="44" y="120" ����="35"/>
				<hex x="44" y="121" ����="35"/>
				<hex x="44" y="122" ����="35"/>
				<hex x="44" y="123" ����="35"/>
				<hex x="45" y="115" ����="35"/>
				<hex x="45" y="116" ����="35"/>
				<hex x="45" y="117" ����="35"/>
				<hex x="45" y="118" ����="35"/>
				<hex x="45" y="119" ����="35"/>
				<hex x="45" y="120" ����="35"/>
				<hex x="45" y="121" ����="35"/>
				<hex x="45" y="122" ����="35"/>

				<!-- ��� -->
				<hex x="40" y="102" ����="18"/>
				<hex x="40" y="103" ����="18"/>
				<hex x="40" y="104" ����="18"/>
				<hex x="40" y="105" ����="18"/>
				<hex x="40" y="106" ����="18"/>
				<hex x="40" y="107" ����="18"/>
				<hex x="40" y="108" ����="18"/>
				<hex x="41" y="101" ����="18"/>
				<hex x="41" y="102" ����="18"/>
				<hex x="41" y="103" ����="18"/>
				<hex x="41" y="104" ����="18"/>
				<hex x="41" y="105" ����="18"/>
				<hex x="41" y="106" ����="18"/>
				<hex x="41" y="107" ����="18"/>
				<hex x="41" y="108" ����="18"/>
				<hex x="42" y="98" ����="18"/>
				<hex x="42" y="99" ����="18"/>
				<hex x="42" y="100" ����="18"/>
				<hex x="42" y="101" ����="18"/>
				<hex x="42" y="102" ����="18"/>
				<hex x="42" y="103" ����="18"/>
				<hex x="42" y="104" ����="18"/>
				<hex x="42" y="105" ����="18"/>
				<hex x="42" y="106" ����="18"/>
				<hex x="42" y="107" ����="18"/>
				<hex x="42" y="108" ����="18"/>
				<hex x="42" y="109" ����="18"/>
				<hex x="43" y="100" ����="18"/>
				<hex x="43" y="101" ����="18"/>
				<hex x="43" y="102" ����="18"/>
				<hex x="43" y="103" ����="18"/>
				<hex x="43" y="104" ����="18"/>
				<hex x="43" y="105" ����="18"/>
				<hex x="43" y="106" ����="18"/>
				<hex x="43" y="107" ����="18"/>
				<hex x="43" y="108" ����="18"/>
				<hex x="43" y="109" ����="18"/>
				<hex x="44" y="103" ����="18"/>
				<hex x="44" y="104" ����="18"/>
				<hex x="44" y="105" ����="18"/>
				<hex x="44" y="106" ����="18"/>
				<hex x="44" y="107" ����="18"/>
				<hex x="44" y="108" ����="18"/>
				<hex x="44" y="109" ����="18"/>
				<hex x="45" y="105" ����="18"/>
				<hex x="45" y="106" ����="18"/>
				<hex x="45" y="107" ����="18"/>
				<hex x="45" y="108" ����="18"/>
				<hex x="46" y="106" ����="18"/>
				<hex x="46" y="107" ����="18"/>
				<hex x="46" y="108" ����="18"/>
				<hex x="47" y="106" ����="18"/>
				<hex x="47" y="107" ����="18"/>
				<hex x="48" y="107" ����="18"/>
			</pk>
			""");

			// ����
			pk::load_xml("""
			<pk>
				<���� ��ȣ="0">
					<��ǥ x="174" y="24"/>
					<��ǥ x="175" y="24"/>
					<��ǥ x="176" y="25"/>
					<��ǥ x="177" y="24"/>
					<��ǥ x="178" y="25"/>
				</����>
				<���� ��ȣ="1">
					<��ǥ x="147" y="31"/>
					<��ǥ x="148" y="32"/>
					<��ǥ x="149" y="31"/>
					<��ǥ x="150" y="32"/>
					<��ǥ x="151" y="31"/>
					<��ǥ x="152" y="27"/>
					<��ǥ x="152" y="28"/>
					<��ǥ x="152" y="29"/>
					<��ǥ x="152" y="30"/>
					<��ǥ x="152" y="31"/>
				</����>
				<���� ��ȣ="2">
					<��ǥ x="123" y="28"/>
					<��ǥ x="124" y="28"/>
					<��ǥ x="125" y="27"/>
				</����>
				<���� ��ȣ="3">
					<��ǥ x="144" y="37"/>
					<��ǥ x="145" y="37"/>
					<��ǥ x="146" y="37"/>
					<��ǥ x="147" y="32"/>
					<��ǥ x="147" y="33"/>
					<��ǥ x="147" y="34"/>
					<��ǥ x="147" y="35"/>
					<��ǥ x="147" y="36"/>
				</����>
				<���� ��ȣ="4">
					<��ǥ x="125" y="61"/>
					<��ǥ x="126" y="61"/>
					<��ǥ x="126" y="62"/>
					<��ǥ x="127" y="60"/>
					<��ǥ x="127" y="61"/>
					<��ǥ x="128" y="60"/>
					<��ǥ x="128" y="61"/>
					<��ǥ x="129" y="59"/>
					<��ǥ x="129" y="60"/>
					<��ǥ x="134" y="56"/>
					<��ǥ x="135" y="55"/>
					<��ǥ x="135" y="56"/>
					<��ǥ x="136" y="55"/>
					<��ǥ x="136" y="56"/>
					<��ǥ x="136" y="57"/>
					<��ǥ x="137" y="54"/>
					<��ǥ x="137" y="55"/>
					<��ǥ x="137" y="56"/>
					<��ǥ x="138" y="54"/>
					<��ǥ x="138" y="55"/>
					<��ǥ x="138" y="56"/>
					<��ǥ x="139" y="53"/>
					<��ǥ x="139" y="54"/>
					<��ǥ x="139" y="55"/>
					<��ǥ x="140" y="52"/>
					<��ǥ x="140" y="53"/>
					<��ǥ x="140" y="54"/>
					<��ǥ x="140" y="55"/>
				</����>
				<���� ��ȣ="5">
					<��ǥ x="86" y="52"/>
					<��ǥ x="87" y="51"/>
					<��ǥ x="87" y="52"/>
					<��ǥ x="88" y="51"/>
					<��ǥ x="88" y="52"/>
					<��ǥ x="89" y="50"/>
					<��ǥ x="89" y="51"/>
					<��ǥ x="90" y="50"/>
					<��ǥ x="90" y="51"/>
				</����>
				<���� ��ȣ="6">
					<��ǥ x="100" y="66"/>
					<��ǥ x="101" y="63"/>
					<��ǥ x="101" y="64"/>
					<��ǥ x="101" y="65"/>
					<��ǥ x="102" y="63"/>
					<��ǥ x="102" y="64"/>
					<��ǥ x="102" y="65"/>
					<��ǥ x="103" y="62"/>
					<��ǥ x="103" y="63"/>
					<��ǥ x="103" y="64"/>
					<��ǥ x="104" y="62"/>
					<��ǥ x="104" y="63"/>
					<��ǥ x="104" y="64"/>
				</����>
				<���� ��ȣ="7">
					<��ǥ x="163" y="45"/>
					<��ǥ x="164" y="45"/>
					<��ǥ x="165" y="44"/>
					<��ǥ x="166" y="45"/>
					<��ǥ x="167" y="44"/>
					<��ǥ x="168" y="45"/>
					<��ǥ x="168" y="46"/>
					<��ǥ x="168" y="47"/>
					<��ǥ x="168" y="48"/>
					<��ǥ x="168" y="49"/>
					<��ǥ x="168" y="50"/>
					<��ǥ x="168" y="51"/>
					<��ǥ x="169" y="45"/>
					<��ǥ x="169" y="46"/>
					<��ǥ x="169" y="47"/>
					<��ǥ x="169" y="48"/>
					<��ǥ x="169" y="49"/>
					<��ǥ x="169" y="50"/>
					<��ǥ x="170" y="46"/>
					<��ǥ x="170" y="47"/>
					<��ǥ x="170" y="48"/>
					<��ǥ x="170" y="49"/>
					<��ǥ x="170" y="50"/>
				</����>
				<���� ��ȣ="8">
					<��ǥ x="162" y="73"/>
					<��ǥ x="162" y="74"/>
					<��ǥ x="163" y="68"/>
					<��ǥ x="163" y="72"/>
					<��ǥ x="163" y="73"/>
					<��ǥ x="163" y="74"/>
					<��ǥ x="164" y="69"/>
					<��ǥ x="164" y="72"/>
					<��ǥ x="164" y="73"/>
					<��ǥ x="164" y="74"/>
					<��ǥ x="164" y="75"/>
					<��ǥ x="165" y="69"/>
					<��ǥ x="165" y="70"/>
					<��ǥ x="165" y="71"/>
					<��ǥ x="165" y="72"/>
					<��ǥ x="165" y="73"/>
					<��ǥ x="165" y="74"/>
					<��ǥ x="165" y="75"/>
					<��ǥ x="166" y="70"/>
					<��ǥ x="166" y="71"/>
					<��ǥ x="166" y="72"/>
					<��ǥ x="166" y="73"/>
					<��ǥ x="166" y="74"/>
					<��ǥ x="166" y="75"/>
					<��ǥ x="167" y="70"/>
					<��ǥ x="167" y="71"/>
					<��ǥ x="167" y="72"/>
					<��ǥ x="167" y="73"/>
					<��ǥ x="167" y="74"/>
					<��ǥ x="168" y="71"/>
					<��ǥ x="168" y="72"/>
					<��ǥ x="168" y="73"/>
					<��ǥ x="168" y="74"/>
				</����>
				<���� ��ȣ="9">
					<��ǥ x="135" y="70"/>
					<��ǥ x="135" y="71"/>
					<��ǥ x="136" y="70"/>
					<��ǥ x="137" y="69"/>
					<��ǥ x="138" y="69"/>
				</����>
				<���� ��ȣ="11">
					<��ǥ x="111" y="67"/>
					<��ǥ x="112" y="68"/>
					<��ǥ x="127" y="66"/>
					<��ǥ x="127" y="67"/>
					<��ǥ x="127" y="68"/>
					<��ǥ x="128" y="66"/>
					<��ǥ x="128" y="67"/>
					<��ǥ x="128" y="68"/>
					<��ǥ x="129" y="65"/>
					<��ǥ x="129" y="66"/>
					<��ǥ x="130" y="65"/>
					<��ǥ x="130" y="66"/>
					<��ǥ x="131" y="65"/>
					<��ǥ x="131" y="66"/>
				</����>
				<���� ��ȣ="12">
					<��ǥ x="101" y="73"/>
					<��ǥ x="101" y="74"/>
					<��ǥ x="101" y="75"/>
					<��ǥ x="101" y="76"/>
					<��ǥ x="102" y="73"/>
					<��ǥ x="102" y="74"/>
					<��ǥ x="102" y="75"/>
					<��ǥ x="102" y="76"/>
					<��ǥ x="102" y="77"/>
					<��ǥ x="103" y="72"/>
					<��ǥ x="103" y="73"/>
					<��ǥ x="103" y="76"/>
					<��ǥ x="103" y="77"/>
					<��ǥ x="104" y="73"/>
					<��ǥ x="104" y="74"/>
					<��ǥ x="104" y="77"/>
					<��ǥ x="105" y="73"/>
					<��ǥ x="105" y="74"/>
					<��ǥ x="105" y="76"/>
					<��ǥ x="106" y="74"/>
					<��ǥ x="106" y="75"/>
					<��ǥ x="106" y="76"/>
					<��ǥ x="107" y="74"/>
					<��ǥ x="107" y="75"/>
				</����>
				<���� ��ȣ="13">
					<��ǥ x="89" y="93"/>
					<��ǥ x="89" y="94"/>
					<��ǥ x="89" y="95"/>
					<��ǥ x="89" y="96"/>
					<��ǥ x="89" y="97"/>
					<��ǥ x="89" y="98"/>
					<��ǥ x="102" y="86"/>
					<��ǥ x="103" y="85"/>
					<��ǥ x="103" y="86"/>
					<��ǥ x="104" y="86"/>
					<��ǥ x="104" y="87"/>
					<��ǥ x="105" y="86"/>
					<��ǥ x="105" y="87"/>
					<��ǥ x="106" y="87"/>
				</����>
				<���� ��ȣ="14">
					<��ǥ x="111" y="113"/>
					<��ǥ x="112" y="114"/>
					<��ǥ x="113" y="114"/>
					<��ǥ x="114" y="115"/>
					<��ǥ x="115" y="114"/>
					<��ǥ x="116" y="114"/>
					<��ǥ x="117" y="112"/>
					<��ǥ x="117" y="113"/>
				</����>
				<���� ��ȣ="15">
					<��ǥ x="69" y="75"/>
					<��ǥ x="70" y="76"/>
					<��ǥ x="71" y="71"/>
					<��ǥ x="72" y="71"/>
					<��ǥ x="72" y="72"/>
					<��ǥ x="73" y="70"/>
					<��ǥ x="73" y="71"/>
					<��ǥ x="74" y="71"/>
					<��ǥ x="74" y="72"/>
					<��ǥ x="75" y="71"/>
					<��ǥ x="75" y="72"/>
					<��ǥ x="81" y="69"/>
					<��ǥ x="81" y="70"/>
					<��ǥ x="81" y="71"/>
					<��ǥ x="82" y="69"/>
					<��ǥ x="82" y="70"/>
					<��ǥ x="82" y="71"/>
					<��ǥ x="83" y="68"/>
					<��ǥ x="83" y="69"/>
					<��ǥ x="84" y="68"/>
					<��ǥ x="84" y="69"/>
					<��ǥ x="85" y="68"/>
					<��ǥ x="85" y="69"/>
					<��ǥ x="86" y="69"/>
					<��ǥ x="86" y="70"/>
					<��ǥ x="86" y="71"/>
					<��ǥ x="86" y="72"/>
					<��ǥ x="86" y="73"/>
					<��ǥ x="86" y="74"/>
					<��ǥ x="87" y="69"/>
					<��ǥ x="87" y="70"/>
					<��ǥ x="87" y="71"/>
					<��ǥ x="87" y="72"/>
					<��ǥ x="87" y="73"/>
				</����>
				<���� ��ȣ="16">
					<��ǥ x="71" y="104"/>
					<��ǥ x="72" y="105"/>
					<��ǥ x="73" y="104"/>
				</����>
				<���� ��ȣ="22">
					<��ǥ x="169" y="103"/>
					<��ǥ x="169" y="104"/>
					<��ǥ x="170" y="104"/>
					<��ǥ x="170" y="105"/>
					<��ǥ x="171" y="104"/>
					<��ǥ x="171" y="105"/>
					<��ǥ x="171" y="106"/>
					<��ǥ x="171" y="107"/>
					<��ǥ x="171" y="108"/>
					<��ǥ x="172" y="105"/>
					<��ǥ x="172" y="106"/>
					<��ǥ x="172" y="107"/>
					<��ǥ x="172" y="108"/>
				</����>
				<���� ��ȣ="24">
					<��ǥ x="189" y="121"/>
					<��ǥ x="189" y="122"/>
					<��ǥ x="189" y="123"/>
					<��ǥ x="190" y="121"/>
					<��ǥ x="190" y="122"/>
					<��ǥ x="190" y="123"/>
					<��ǥ x="190" y="124"/>
					<��ǥ x="191" y="120"/>
					<��ǥ x="191" y="121"/>
					<��ǥ x="191" y="122"/>
					<��ǥ x="191" y="123"/>
					<��ǥ x="191" y="124"/>
					<��ǥ x="192" y="120"/>
					<��ǥ x="192" y="121"/>
					<��ǥ x="192" y="122"/>
					<��ǥ x="192" y="123"/>
					<��ǥ x="192" y="124"/>
					<��ǥ x="192" y="125"/>
					<��ǥ x="193" y="119"/>
					<��ǥ x="193" y="120"/>
					<��ǥ x="193" y="121"/>
					<��ǥ x="193" y="122"/>
					<��ǥ x="193" y="123"/>
					<��ǥ x="193" y="124"/>
					<��ǥ x="193" y="125"/>
					<��ǥ x="194" y="119"/>
					<��ǥ x="194" y="120"/>
					<��ǥ x="194" y="121"/>
					<��ǥ x="194" y="122"/>
					<��ǥ x="194" y="123"/>
					<��ǥ x="194" y="124"/>
					<��ǥ x="194" y="125"/>
					<��ǥ x="195" y="119"/>
					<��ǥ x="195" y="120"/>
					<��ǥ x="195" y="121"/>
					<��ǥ x="195" y="122"/>
					<��ǥ x="195" y="123"/>
					<��ǥ x="196" y="120"/>
					<��ǥ x="196" y="121"/>
					<��ǥ x="196" y="122"/>
				</����>
				<���� ��ȣ="25">
					<��ǥ x="138" y="121"/>
					<��ǥ x="139" y="120"/>
					<��ǥ x="140" y="120"/>
					<��ǥ x="147" y="111"/>
					<��ǥ x="148" y="111"/>
					<��ǥ x="148" y="112"/>
					<��ǥ x="149" y="111"/>
					<��ǥ x="149" y="112"/>
					<��ǥ x="150" y="112"/>
					<��ǥ x="150" y="113"/>
				</����>
				<���� ��ȣ="26">
					<��ǥ x="111" y="138"/>
					<��ǥ x="111" y="139"/>
					<��ǥ x="111" y="140"/>
					<��ǥ x="111" y="141"/>
					<��ǥ x="111" y="142"/>
					<��ǥ x="111" y="143"/>
					<��ǥ x="112" y="138"/>
					<��ǥ x="112" y="139"/>
					<��ǥ x="112" y="140"/>
					<��ǥ x="112" y="141"/>
					<��ǥ x="112" y="142"/>
					<��ǥ x="112" y="143"/>
					<��ǥ x="113" y="137"/>
					<��ǥ x="113" y="138"/>
					<��ǥ x="113" y="139"/>
					<��ǥ x="113" y="140"/>
					<��ǥ x="113" y="141"/>
					<��ǥ x="113" y="142"/>
					<��ǥ x="114" y="138"/>
					<��ǥ x="114" y="139"/>
					<��ǥ x="114" y="140"/>
					<��ǥ x="114" y="141"/>
					<��ǥ x="114" y="142"/>
					<��ǥ x="114" y="143"/>
					<��ǥ x="115" y="138"/>
					<��ǥ x="115" y="139"/>
					<��ǥ x="115" y="140"/>
					<��ǥ x="115" y="141"/>
					<��ǥ x="115" y="142"/>
					<��ǥ x="115" y="143"/>
					<��ǥ x="116" y="139"/>
					<��ǥ x="116" y="140"/>
					<��ǥ x="116" y="141"/>
					<��ǥ x="116" y="142"/>
					<��ǥ x="116" y="143"/>
					<��ǥ x="116" y="144"/>
					<��ǥ x="119" y="140"/>
					<��ǥ x="119" y="141"/>
					<��ǥ x="119" y="142"/>
				</����>
				<���� ��ȣ="27">
					<��ǥ x="101" y="121"/>
					<��ǥ x="102" y="122"/>
					<��ǥ x="103" y="122"/>
					<��ǥ x="104" y="122"/>
					<��ǥ x="105" y="121"/>
					<��ǥ x="122" y="121"/>
					<��ǥ x="123" y="120"/>
					<��ǥ x="124" y="120"/>
					<��ǥ x="125" y="119"/>
					<��ǥ x="126" y="119"/>
					<��ǥ x="127" y="116"/>
					<��ǥ x="127" y="117"/>
					<��ǥ x="127" y="118"/>
				</����>
				<���� ��ȣ="28">
					<��ǥ x="83" y="100"/>
					<��ǥ x="84" y="100"/>
					<��ǥ x="85" y="99"/>
				</����>
				<���� ��ȣ="29">
					<��ǥ x="64" y="110"/>
					<��ǥ x="64" y="111"/>
					<��ǥ x="65" y="109"/>
					<��ǥ x="65" y="110"/>
					<��ǥ x="65" y="111"/>
					<��ǥ x="66" y="109"/>
					<��ǥ x="66" y="110"/>
					<��ǥ x="66" y="111"/>
					<��ǥ x="66" y="112"/>
					<��ǥ x="67" y="109"/>
					<��ǥ x="67" y="110"/>
					<��ǥ x="67" y="111"/>
					<��ǥ x="67" y="112"/>
					<��ǥ x="68" y="110"/>
					<��ǥ x="68" y="111"/>
					<��ǥ x="68" y="112"/>
					<��ǥ x="68" y="113"/>
					<��ǥ x="69" y="110"/>
					<��ǥ x="69" y="111"/>
					<��ǥ x="69" y="112"/>
					<��ǥ x="69" y="113"/>
				</����>
				<���� ��ȣ="30">
					<��ǥ x="75" y="129"/>
					<��ǥ x="92" y="130"/>
					<��ǥ x="92" y="131"/>
					<��ǥ x="92" y="132"/>
					<��ǥ x="93" y="129"/>
					<��ǥ x="93" y="130"/>
					<��ǥ x="93" y="131"/>
					<��ǥ x="94" y="129"/>
					<��ǥ x="94" y="130"/>
					<��ǥ x="94" y="131"/>
					<��ǥ x="94" y="132"/>
					<��ǥ x="95" y="129"/>
					<��ǥ x="95" y="130"/>
					<��ǥ x="95" y="131"/>
					<��ǥ x="95" y="132"/>
					<��ǥ x="96" y="130"/>
					<��ǥ x="96" y="131"/>
					<��ǥ x="96" y="132"/>
					<��ǥ x="96" y="133"/>
					<��ǥ x="97" y="130"/>
					<��ǥ x="97" y="131"/>
					<��ǥ x="97" y="132"/>
					<��ǥ x="97" y="133"/>
				</����>
				<���� ��ȣ="32">
					<��ǥ x="78" y="160"/>
					<��ǥ x="79" y="160"/>
					<��ǥ x="80" y="161"/>
				</����>
				<���� ��ȣ="37">
					<��ǥ x="13" y="101"/>
					<��ǥ x="14" y="101"/>
					<��ǥ x="14" y="102"/>
					<��ǥ x="15" y="101"/>
					<��ǥ x="15" y="102"/>
					<��ǥ x="16" y="102"/>
					<��ǥ x="16" y="103"/>
					<��ǥ x="16" y="104"/>
					<��ǥ x="16" y="105"/>
					<��ǥ x="17" y="102"/>
					<��ǥ x="17" y="103"/>
					<��ǥ x="17" y="104"/>
					<��ǥ x="17" y="105"/>
				</����>
				<���� ��ȣ="40">
					<��ǥ x="14" y="177"/>
					<��ǥ x="14" y="178"/>
					<��ǥ x="14" y="179"/>
				</����>
			</pk>
			""");

			// ����
			pk::load_xml("""
			<pk trace="true">
				<���� ��ȣ="0">
					<�ɷ� ����="90" ���="90"/>
					<�̵��º�� ��="10" ����="10" ��="10"/>
				</����>
				<���� ��ȣ="1">
					<�̵��º�� ��="10" ����="10" ��="10"/>
				</����>
				<���� ��ȣ="2">
					<�̵��º�� ��="10" ����="10" ��="10"/>
				</����>
				<���� ��ȣ="3">
					<�̵��º�� ��="10" ����="10" ��="10"/>
				</����>
			</pk>
			""");

			// ����
			pk::load_xml("""
			<pk trace="true">
				<���� ��ȣ="7">
					<�ɷ�ġ ����="7"/>
				</����>
				<���� ��ȣ="8">
					<�ɷ�ġ ����="6"/>
				</����>
				<���� ��ȣ="9">
					<�ɷ�ġ ����="5"/>
				</����>
				<���� ��ȣ="10">
					<�ɷ�ġ ����="5"/>
				</����>
				<���� ��ȣ="11">
					<�ɷ�ġ ����="8"/>
				</����>
				<���� ��ȣ="12">
					<�ɷ�ġ ����="6"/>
				</����>
				<���� ��ȣ="13">
					<�ɷ�ġ ����="6"/>
				</����>
				<���� ��ȣ="14">
					<�ɷ�ġ ����="3"/>
				</����>
				<���� ��ȣ="15">
					<�ɷ�ġ ����="2"/>
				</����>
				<���� ��ȣ="16">
					<�ɷ�ġ ����="2"/>
				</����>
				<���� ��ȣ="17">
					<�ɷ�ġ ����="2"/>
				</����>
				<���� ��ȣ="18">
					<�ɷ�ġ ����="2"/>
				</����>
				<���� ��ȣ="19">
					<�ɷ�ġ ����="2"/>
				</����>
				<���� ��ȣ="20">
					<�ɷ�ġ ����="2"/>
				</����>
				<���� ��ȣ="21">
					<�ɷ�ġ ����="4"/>
				</����>
				<���� ��ȣ="22">
					<�ɷ�ġ ����="4"/>
				</����>
				<���� ��ȣ="23">
					<�ɷ�ġ ����="4"/>
				</����>
				<���� ��ȣ="24">
					<�ɷ�ġ ����="1"/>
				</����>
				<���� ��ȣ="25">
					<�ɷ�ġ ����="1"/>
				</����>
				<���� ��ȣ="26">
					<�ɷ�ġ ����="2"/>
				</����>
				<���� ��ȣ="27">
					<�ɷ�ġ ����="2"/>
				</����>
				<���� ��ȣ="28">
					<�ɷ�ġ ����="1"/>
				</����>
				<���� ��ȣ="29">
					<�ɷ�ġ ����="1"/>
				</����>
				<���� ��ȣ="30">
					<�ɷ�ġ ���="10"/>
				</����>
				<���� ��ȣ="31">
					<�ɷ�ġ ���="2"/>
				</����>
				<���� ��ȣ="32">
					<�ɷ�ġ ���="2"/>
				</����>
				<���� ��ȣ="33">
					<�ɷ�ġ ���="8"/>
				</����>
				<���� ��ȣ="34">
					<�ɷ�ġ ���="8"/>
				</����>
				<���� ��ȣ="35">
					<�ɷ�ġ ���="6"/>
				</����>
				<���� ��ȣ="36">
					<�ɷ�ġ ���="5"/>
				</����>
				<���� ��ȣ="37">
					<�ɷ�ġ ��ġ="3"/>
				</����>
				<���� ��ȣ="38">
					<�ɷ�ġ ���="7"/>
				</����>
				<���� ��ȣ="39">
					<�ɷ�ġ ���="4"/>
				</����>
				<���� ��ȣ="40">
					<�ɷ�ġ ����="2"/>
				</����>
			</pk>
			""");

			// �ü�
			pk::load_xml("""
			<pk trace="true">
				<�ü� ��ȣ="0">
					<�ִ���� ��="3"/>
					<�ڵ����� ��="true"/>
					<��»�� ��="true"/>
					<���ݷ»�� ��="true"/>
				</�ü�>
				<�ü� ��ȣ="1">
					<�ִ���� ��="3"/>
					<�ڵ����� ��="true"/>
					<��»�� ��="true"/>
					<���ݷ»�� ��="true"/>
				</�ü�>
				<�ü� ��ȣ="2">
					<�ִ���� ��="3"/>
					<�ڵ����� ��="true"/>
					<��»�� ��="true"/>
					<���ݷ»�� ��="true"/>
				</�ü�>
				<�ü� ��ȣ="3">
					<��ġ�������� Ȳ����="true" ��="true" ����="true"/>
					<����ü����� ��="1"/>
				</�ü�>
				<�ü� ��ȣ="4">
					<��ġ�������� Ȳ����="true" ��="true" ����="true"/>
					<����ü����� ��="1"/>
				</�ü�>
				<�ü� ��ȣ="5">
					<��ġ�������� Ȳ����="true" ��="true" ����="true"/>
					<����ü����� ��="1"/>
				</�ü�>
				<�ü� ��ȣ="6">
					<��ġ�������� Ȳ����="true" ��="true" ����="true"/>
					<����ü����� ��="1"/>
				</�ü�>
				<�ü� ��ȣ="7">
					<��ġ�������� Ȳ����="true" ��="true" ����="true"/>
					<����ü����� ��="1"/>
				</�ü�>
				<�ü� ��ȣ="8">
					<��ġ�������� Ȳ����="true" ��="true" ����="true"/>
				</�ü�>
				<�ü� ��ȣ="9">
					<��ġ�������� Ȳ����="true" ��="true" ����="true"/>
				</�ü�>
				<�ü� ��ȣ="10">
					<��ġ�������� Ȳ����="true" ��="true" ����="true"/>
					<����ü����� ��="1"/>
				</�ü�>
				<�ü� ��ȣ="11">
					<��ġ�������� Ȳ����="true" ��="true" ����="true"/>
					<����ü����� ��="1"/>
				</�ü�>
				<�ü� ��ȣ="12">
					<��ġ�������� Ȳ����="true" ��="true" ����="true"/>
					<����ü����� ��="1"/>
				</�ü�>
				<�ü� ��ȣ="13">
					<��ġ�������� Ȳ����="true" ��="true" ����="true"/>
					<�ִ���� ��="2"/>
					<����ü����� ��="1"/>
				</�ü�>
				<�ü� ��ȣ="14">
					<�ڵ����� ��="true"/>
				</�ü�>
				<�ü� ��ȣ="15">
					<�ڵ����� ��="true"/>
				</�ü�>
				<�ü� ��ȣ="16">
					<��ġ�������� Ȳ����="true" ��="true" ����="true"/>
				</�ü�>
				<�ü� ��ȣ="17">
					<��ġ�������� Ȳ����="true" ��="true" ����="true"/>
				</�ü�>
				<�ü� ��ȣ="18">
					<��ġ�������� Ȳ����="true" ��="true" ����="true"/>
				</�ü�>
				<�ü� ��ȣ="19">
					<��ġ�������� Ȳ����="true" ��="true" ����="true"/>
				</�ü�>
				<�ü� ��ȣ="20">
					<��ġ�������� ��="true" ����="true" ����="true"/>
				</�ü�>
				<�ü� ��ȣ="21">
					<��ġ�������� Ȳ����="true" ��="true" ����="true"/>
				</�ü�>
				<�ü� ��ȣ="22">
					<��ġ�������� Ȳ����="true" ��="true" ����="true"/>
				</�ü�>
			</pk>
			""");

			// �ΰ�����
			pk::load_xml("""
			<pk trace="true">
				<�ΰ�����.����.������Ž����� ��="true"/>
				<�ΰ�����.����.���氭�� ��="false"/>
				<�ΰ�����.����.�Ͻ����� ��="false"/>
				<�ΰ�����.����.�ִ�ü�����ġ>
					<��ü ����="127" ���尣="127" ����="0" ����="0" ������="0" �����="1" �����="1"/>
				</�ΰ�����.����.�ִ�ü�����ġ>
				<�ΰ�����.����.�ּҽü�����ġ>
					<��ü ����="16"/>
				</�ΰ�����.����.�ּҽü�����ġ>
				<�ΰ�����.����.�ּҽü���>
					<���� ����="0"/>
					<�� ����="0"/>
					<�û� ����="0"/>
					<���� ����="0"/>
					<��� ����="0"/>
				</�ΰ�����.����.�ּҽü���>
				<�ΰ�����.����.Ư������ġ ���尣="127" ����="1" ����="0"/>
				<�ΰ�����.����.Ư������ġ ������="127" �����="0" �ܱ���="1" �跫��="1" ������="1"/>
				<�ΰ�����.����.����ġ.���.���� ��="14"/>
				<�ΰ�����.����.����ġ.�󵵽� ��="80"/>
				<�ΰ�����.����.�����ֿ켱 ��="false"/>
				<�ΰ�����.����.�����ӹ���� ��="false"/>
				<�ΰ�����.����.���±��� ��="0"/>
				<�ΰ�����.����.��±��� ��="85"/>
				<�ΰ�����.����.�ɷ¿켱�δ����� ��="false"/>
				<�ΰ�����.����.���ð�������Ȯ�� ��="false"/>
				<�ΰ�����.����.�������� ��="false"/>
				<�ΰ�����.����.�������ü���� ��="false"/>
				<�ΰ�����.����.�վ����ֿ켱 ��="false"/>
				<�ΰ�����.����.���ú���±��� ��="105"/>
				<�ΰ�����.����.��ȣ������ ��="80"/>
				<�ΰ�����.����.�ּҽü��ʿ� ��="false"/>
				<�ΰ�����.����.�÷��̾�켱 ��="false"/>
				<�ΰ�����.�ⱳ����.���భȭ�켱 ��="false"/>
				<�ΰ�����.������.�ҿ乫������� ��="false"/>
				<�ΰ�����.������.�ּҹ�������� ��="false"/>
				<�ΰ�����.��ġ.���±��� ��="0"/>
				<�ΰ�����.��ġ.�����ݱ��� ��="6000"/>
				<�ΰ�����.����.�������������� ��="false"/>
				<�ΰ�����.����.ġ�ȱ��� ��="98"/>
				<�ΰ�����.����.���±��� ��="0"/>
				<�ΰ�����.����Ž��.�ҿ乫������� ��="false"/>
				<�ΰ�����.����Ž��.�ּҹ�������� ��="false"/>
				<�ΰ�����.¡��.���±��� ��="0"/>
				<�ΰ�����.¡��.ġ�ȱ��� ��="89"/>
				<�ΰ�����.Ÿ���¹�����.�ҿ乫������� ��="false"/>
			</pk>
			""");

			// ����
			pk::load_xml("""
			<pk trace="true">
				<���� ��ȣ="1">
					<�ʿ����ġ ��="15"/>
					<��������Ȯ�� ��="1"/>
				</����>
				<���� ��ȣ="2">
					<�ʿ����ġ ��="20"/>
					<��������Ȯ�� ��="3"/>
				</����>
				<���� ��ȣ="3">
					<�ʿ����ġ ��="30"/>
					<��������Ȯ�� ��="5"/>
				</����>
				<���� ��ȣ="4">
					<�̸� ��="S1"/>
					<�ʿ����ġ ��="45"/>
					<��������Ȯ�� ��="7"/>
				</����>
				<���� ��ȣ="5">
					<�̸� ��="S2"/>
					<�ʿ����ġ ��="60"/>
					<��������Ȯ�� ��="9"/>
				</����>
				<���� ��ȣ="6">
					<�̸� ��="S3"/>
					<�ʿ����ġ ��="80"/>
					<��������Ȯ�� ��="11"/>
				</����>
				<���� ��ȣ="7">
					<�̸� ��="S4"/>
					<�ʿ����ġ ��="100"/>
					<��������Ȯ�� ��="13"/>
				</����>
				<���� ��ȣ="8">
					<�̸� ��="S5"/>
					<�ʿ����ġ ��="120"/>
					<��������Ȯ�� ��="15"/>
				</����>
				<���� ��ȣ="9">
					<�̸� ��="S6"/>
					<�ʿ����ġ ��="140"/>
					<��������Ȯ�� ��="17"/>
				</����>
				<���� ��ȣ="10">
					<�̸� ��="S7"/>
					<�ʿ����ġ ��="175"/>
					<��������Ȯ�� ��="19"/>
				</����>
				<���� ��ȣ="11">
					<�̸� ��="S8"/>
					<�ʿ����ġ ��="200"/>
					<��������Ȯ�� ��="21"/>
				</����>
				<���� ��ȣ="12">
					<�̸� ��="S9"/>
					<�ʿ����ġ ��="225"/>
					<��������Ȯ�� ��="23"/>
				</����>
				<���� ��ȣ="13">
					<�̸� ��="SS"/>
					<�ʿ����ġ ��="250"/>
					<��������Ȯ�� ��="25"/>
				</����>
			</pk>
			""");

			// ����
			pk::load_xml("""
			<pk trace="true">
				<���� ��ȣ="12">
					<���� ��="true"/>
				</����>
				<���� ��ȣ="14">
					<���� ��="true"/>
				</����>
				<���� ��ȣ="15">
					<���� ��="true" ����="true" ��="true"/>
				</����>
				<���� ��ȣ="16">
					<���� ��="true" ����="true"/>
				</����>
				<���� ��ȣ="18">
					<���� ��="true" ����="true" ��="true"/>
				</����>
			</pk>
			""");

			// ����
			pk::load_xml("""
			<pk trace="true">
				<���� ��ȣ="4">
					<ȭ�谡�� ��="true"/>
				</����>
				<���� ��ȣ="6">
					<�̵����� ��="true"/>
					<ȭ�谡�� ��="true"/>
					<�������� ��="������"/>
				</����>
				<���� ��ȣ="13">
					<ȭ�谡�� ��="true"/>
				</����>
				<���� ��ȣ="14">
					<�̵����� ��="true"/>
					<ȭ�谡�� ��="true"/>
					<�������� ��="������"/>
				</����>
				<���� ��ȣ="15">
					<�̵����� ��="true"/>
					<ȭ�谡�� ��="true"/>
					<�������� ��="������"/>
				</����>
				<���� ��ȣ="19">
					<ȭ�谡�� ��="true"/>
				</����>
			</pk>
			""");

			// ī�޶�
			pk::load_xml("""
			<pk trace="true">
				<camera.far ��="1152"/>
				<camera.min_x ��="0"/>
				<camera.max_x ��="5120"/>
				<camera.max_y ��="5120"/>
				<camera.min_angle ��="-89.9999"/>
				<camera.max_angle ��="89.9999"/>
				<camera.zoom_in ��="32"/>
				<camera.zoom_out0 ��="752"/>
				<camera.zoom_out1 ��="852"/>
				<camera.zoom_out2 ��="952"/>
				<camera.through ��="true"/>
			</pk>
			""");
		}
	}

	Main main;
}