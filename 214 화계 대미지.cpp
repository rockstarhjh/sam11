/**********************************************************************************
Reference : [PK2.1] 214 화계 대미지.cpp
Updated by 윤돌

22.11.16
	Modified	폭약연성 대미지 적용 조건 - 공격유닛이 폭약연성 기교를 배웠을 때 기준으로 한정시킴으로써 원본에서의 bug 가능성 차단
	Modified	info.hp_damage - 건물을 화공 공격시 폭약연성 기교 습득시 대미지 50 증가 적용

22.12.1
	BugFixed	null pointer error fix - 유닛 피격시 위치이동되면서 화계대미지 입을 경우
	
23.1.8
	Modified	공성 병기, 수군의 경우 20% 화공 대미지 증가 적용 (대미지시스템개선패치의 유닛간 상성과 연계)
	
**********************************************************************************/


namespace 화계_대미지
{
	class Main
	{
		Main()
		{
			pk::set_func(214, pk::func214_t(callback));
		}

		void callback(pk::damage_info& info, pk::unit@ attacker, pk::hex_object@ target, bool critical)
		{
			int atk = 0;

			if (target.is_instance(pk::unit::type_id))		// 공격 대상이 유닛?
			{
				pk::unit@ target_unit = pk::hex_object_to_unit(target);
				
				atk = 350;
				info.troops_damage = atk + pk::rand(200);
						
				if (pk::is_alive(attacker) and attacker.has_tech(기교_폭약연성))
				{
					info.troops_damage += atk;
					info.atk_tech = 기교_폭약연성;
				}

				if (pk::is_alive(attacker) and attacker.has_skill(특기_화신))
				{
					info.troops_damage *= 2.5f;
					info.atk_skill = 특기_화신;
				}

				if (target_unit.weapon > 병기_군마)			// 개선 : 병기 및 함선일 경우 20% 피해 증가
					info.troops_damage *= 1.2f;

				if (target.has_skill(특기_등갑))
				{
					info.troops_damage *= 2;
					info.def_skill = 특기_등갑;
				}
				else if (target.has_skill(특기_화신))
				{
					info.troops_damage = 0;
					info.def_skill = 특기_화신;
				}
			}
			else if (target.is_instance(pk::building::type_id))	// 공격 대상이 건물?
			{
				atk = 100;
				info.hp_damage = atk + pk::rand(50);

				// 복구중 제방은 화공 실패 처리, 아니면 폭약연성에 의한 대미지 증가 처리 (+양념)
				pk::building@ building = pk::hex_object_to_building(target);
				if (building.facility == 시설_제방 and !building.completed)		
				{
					info.hp_damage = 0;
				}
				else if (pk::is_alive(attacker) and attacker.has_tech(기교_폭약연성))
				{
					info.hp_damage += int(atk * 0.5f);
					info.atk_tech = 기교_폭약연성;
				}
			}

			info.tactics = -1;
			if (pk::is_alive(attacker))
				info.src_pos = attacker.get_pos();
			info.dst_pos = target.get_pos();
		}
	}

	Main main;
}