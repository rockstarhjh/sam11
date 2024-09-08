namespace 충돌_대미지
{
	class Main
	{
		Main()
		{
			pk::set_func(212, pk::func212_t(callback));
		}

		void callback(pk::damage_info& info, pk::unit@ attacker, pk::hex_object@ sub_target)
		{
			int n = 0;

			// ?
			n = pk::rand(attacker.attr.stat[부대능력_공격]) + attacker.attr.stat[부대능력_공격] / 2;
			info._20 = -pk::max(n, 1);

			pk::unit@ sub_target_unit = pk::hex_object_to_unit(sub_target);

			if (!pk::is_alive(sub_target_unit))
				return;

			pk::force@ sub_target_force = pk::get_force(sub_target_unit.get_force_id());

			if (sub_target.is_instance(pk::unit::type_id))
			{
				n = attacker.attr.stat[부대능력_공격] * 2 - pk::hex_object_to_unit(sub_target).attr.stat[부대능력_방어];
				if (n < 20) n = 20;
				info.troops_damage = pk::max(n + pk::rand(n), 1);

				// 투신 연구시 충돌에 맞으면 재행동
				if (sub_target_unit.has_skill(특기_투신) and sub_target.get_force_id() == attacker.get_force_id() and sub_target_force.sp_ability_researched[4] and pk::get_ability(sub_target_force.sp_ability[4]).skill == 특기_투신)
				{
					pk::set_status(sub_target_unit, sub_target_unit, 부대상태_폭주, 0, true);
					pk::set_status(sub_target_unit, sub_target_unit, 부대상태_통상, 0, true);
					pk::set_action_done(sub_target_unit, false);
					if (!pk::is_player_controlled(sub_target_unit))
					{
						if (sub_target_unit.order != -1)
							pk::run_order(sub_target_unit);
						else
							pk::set_order(sub_target_unit, 부대임무_대기, -1, -1);
					}
				}
			}
			else
			{
				pk::building@ building = pk::hex_object_to_building(sub_target);
				if (!pk::is_trap_type(building))
				{
					n = attacker.attr.stat[부대능력_공격] + pk::rand(attacker.attr.stat[부대능력_공격] / 2);
					n = n / 2;
					info.hp_damage = pk::max(n, 1);
				}
				else if (building.facility == 시설_제방 and !building.completed)
				{
					info.hp_damage = 0;
				}
			}

			info.tactics = -1;
			info.src_pos = attacker.get_pos();
			info.dst_pos = sub_target.get_pos();
		}
	}

	Main main;
}