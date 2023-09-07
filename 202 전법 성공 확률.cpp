namespace 전법_성공_확률
{
	class Main
	{
		Main()
		{
			pk::set_func(202, pk::func202_t(callback));
		}

		int callback(pk::unit@ attacker, const pk::point &in pos, pk::hex_object@ target, int tactics_id)
		{
            pk::unit @ target_unit = pk::hex_object_to_unit(target);
            
			if (target.is_instance(pk::unit::type_id) and target_unit.status != 부대상태_통상)
				return 100;
            
			int n = 0;
			pk::point temp;

			// if (pk::get_tekisei(attacker) == 적성_A) n = 5; else if (pk::get_tekisei(attacker) == 적성_S) n = 10;
			n = int(pk::core["적성"][pk::get_tekisei(attacker)]["전법성공확률"]) + pk::core::tactics_chance(attacker.leader);
            
            
            
			switch (tactics_id)
			{
			case 전법_돌출:
                n = n + push_bonus(get_height_diff(attacker.get_pos(), target.get_pos())) + 70;
				break;
            case 전법_이단첨:
                n = n + push_bonus(get_height_diff(attacker.get_pos(), target.get_pos())) + 65;
				temp = pk::get_neighbor_pos(target.get_pos(), pk::get_direction(attacker.get_pos(), target.get_pos()));
				n = n + cutoff_diff(get_height_diff(target.get_pos(), temp));
				break;
			case 전법_나선첨:
				n = n + push_bonus(get_height_diff(attacker.get_pos(), target.get_pos())) + 60;
				break;

                
			case 전법_갈퀴:
				n = n + pull_bonus(get_height_diff(attacker.get_pos(), target.get_pos())) + 70;
				temp = pk::get_neighbor_pos(attacker.get_pos(), pk::get_direction(target.get_pos(), attacker.get_pos()));
				n = n + cutoff_diff(get_height_diff(attacker.get_pos(), temp));
				break;
			case 전법_횡치:
            case 전법_선풍:
            
            
			case 전법_화시:
				n = n + hiya_terrain_bonus(pk::get_hex(target.get_pos()).terrain) + 75;
				break;
			case 전법_관시:
				n = n + 70;
				break;
            case 전법_난사:
                
                
            case 전법_돌격:
				n = n + push_bonus(get_height_diff(attacker.get_pos(), target.get_pos())) + 70;
				break;
			case 전법_돌진:
				n = n + push_bonus(get_height_diff(attacker.get_pos(), target.get_pos())) + 65;
				temp = pk::get_neighbor_pos(target.get_pos(), pk::get_direction(attacker.get_pos(), target.get_pos()));
				n = n + cutoff_diff(get_height_diff(target.get_pos(), temp));
				break;
			case 전법_돌파:
				n = n + push_bonus(get_height_diff(attacker.get_pos(), target.get_pos())) + 60;
				break;
			
			
			case 전법_함선격돌:
				n = n + 65;
				break;

			default:        // 병기 간접 공격 성공율 = 100%
				return 100;
			}
            
            // 공격부대 병력수에 따라 전법 성공률 보정 ('18.10.13)
            if (attacker.troops <= 1000)
                n = int(n * pk::max(0.1f, attacker.troops/1000.f));         // 소부대 시 전법성공률 1/10배 까지 감소
            
            
            // 공격/피격 부대의 특기 보유에 따른 전법 성공율 보정 ('18.10.18)
            if (target.is_instance(pk::unit::type_id) and target_unit.status == 부대상태_통상 and pk::is_valid_tactics_id(tactics_id))
            {
                // 공격부대가 강운 특기 보유 시 전법 성공율 최소 80% 
                if (attacker.has_skill(특기_강운) )
                    return pk::max(80, n);  
                // 피격부대가 통찰 특기 보유 시 전법 성공율 최대 50% : 공격전법 실패 시 통상공격이 되기 ?문에 불굴/금강처럼 일정 확률로 회피하는 것과는 다름 
                if (target_unit.has_skill(특기_통찰) )
                    return pk::min(50, n);
                // 공격부대가 정묘 특기 보유 시 전법 성공율 10% 추가
                if (attacker.has_skill(특기_정묘) )
                    return pk::min(100, n + 10); 
            }
            
                
			return n;
		}

        
        
        
        
		// 5af5b0
		int get_height_diff(const pk::point &in src, const pk::point &in dst)
		{
			return pk::get_height_map(pk::hex_pos_to_height_map_pos(src) + 2).height - pk::get_height_map(pk::hex_pos_to_height_map_pos(dst) + 2).height;
		}

		// 5af6b0
		int push_bonus(int n)
		{
			return cutoff_diff(n) + 5;
		}

		// 5af6f0
		int pull_bonus(int n)
		{
			return 5 - cutoff_diff(n);
		}
        

		// 5af680
		int cutoff_diff(int n)
		{
			// 상대보다 높음
			if (n >= 10)
				return 10;
			// 상대보다 높음
			else if (n >= 5)
				return 5;
			// 평지
			else if (n >= -5)
				return 0;
			// 상대보다 낮음
			else if (n >= -10)
				return -5;
			// 상대보다 낮음
			else
				return -10;
		}
        

		// 849ae0 지형에 따른 화시 확률 보너스
		int hiya_terrain_bonus(int terrain)
		{
			switch (terrain)
			{
			case 지형_땅: return -5;
			case 지형_모래: return -5;
			case 지형_습지: return -15;
			case 지형_독천: return -15;
			case 지형_숲: return 10;
			case 지형_내: return -10;
			case 지형_강: return -10;
			case 지형_바다: return -10;
			case 지형_여울: return -10;
			case 지형_샛길: return -5;
			}
			return 0;
		}
        
        
	}

	Main main;
}