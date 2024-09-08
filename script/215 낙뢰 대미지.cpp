namespace 낙뢰_대미지
{
	class Main
	{
		Main()
		{
			pk::set_func(215, pk::func215_t(callback));
		}

		void callback(pk::damage_info& info, pk::unit@ attacker, pk::hex_object@ target, bool critical)
		{
			pk::force@ target_force = pk::get_force(target.get_force_id());
			pk::unit@ target_unit = pk::hex_object_to_unit(target);

			if (target.is_instance(pk::unit::type_id))
			{
				info.troops_damage = 1500 + pk::rand(1000);
				
				if (target_unit.has_skill(특기_도주) and target_unit.get_force_id() == attacker.get_force_id())
				{
					// 도주 연구시 1% 피해만을 받고 피격시 재행동
					if (target_force.sp_ability_researched[6] and pk::get_ability(target_force.sp_ability[6]).skill == 특기_도주)
					{
						info.troops_damage *= 0.01f;
						pk::set_status(target_unit, target_unit, 부대상태_폭주, 0, true);
						pk::set_status(target_unit, target_unit, 부대상태_통상, 0, true);
						pk::set_action_done(target_unit, false);
						if (pk::is_alive(target_unit) and !pk::is_player_controlled(target_unit))
						{
							if (target_unit.order != -1)
								pk::run_order(target_unit);
							else
								pk::set_order(target_unit, 부대임무_대기, -1, -1);
						}
					}
				}
			}
			else
			{
				info.hp_damage = 700 + pk::rand(300);
				// 회복중인 제방일 경우 무효
				pk::building@ building = pk::hex_object_to_building(target);
				if (building.facility == 시설_제방 and !building.completed)
					info.hp_damage = 0;
			}

			info.tactics = -1;
			info.src_pos = attacker.get_pos();
			info.dst_pos = target.get_pos();
		}
	}

	Main main;
}