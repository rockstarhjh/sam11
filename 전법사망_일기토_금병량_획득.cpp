/*
@만든이: 크래픽스
@Update: 2023.8.19,최초배포
*/

namespace 기병전법사망_일기토_금병량_획득
{
	class Main
	{
		//pk::func203_t@ prev_callback_203;
		pk::func209_t@ prev_callback_209;
		Main()
		{
			//@prev_callback_203 = cast<pk::func203_t@>(pk::get_func(203));
			//pk::reset_func(203);
			//pk::set_func(203, pk::func203_t(callback));                // 202 전법 성공 확률
			
			@prev_callback_209 = cast<pk::func209_t@>(pk::get_func(209));
			pk::reset_func(209);
			pk::set_func(209, pk::func209_t(callback209));                // 202 전법 성공 확률
			

			pk::bind(171, pk::trigger171_t(부대제거2));
			//pk::bind(173, pk::trigger173_t(부대경험치));
			//pk::bind(174, pk::trigger174_t(부대행동완료));
			pk::bind(107, pk::trigger107_t(새날));
			
		}

		array<pk::person@> _attackers;
		array<pk::person@> _defenders;

		array<int> _defendersUnit;
		array<int> _golds;
		array<int> _foods;
		//int callback(pk::person@ attacker, pk::person@ target, int tactics_id, bool critical)
		//{
		//	_attackers.insertLast(attacker);
		//	_defenders.insertLast(target);
		//	_defendersUnit.insertLast(-1);
		//	_golds.insertLast(0);
		//	_foods.insertLast(0);
		//	
		//	return prev_callback_203(attacker,target,tactics_id,critical);
		//}
		
		void callback209(pk::damage_info& info, pk::unit@ attacker, int tactics_id, const pk::point &in target_pos, int type, int critical, bool ambush)
		{
			
			
			auto obj = pk::get_hex_object(target_pos);
			if(obj.get_type_id() == 11)
			{
				pk::unit@ target = obj;
				
				pk::person@ p = pk::get_person(attacker.leader);
				_attackers.insertLast(p);
				pk::person@ p2 = pk::get_person(target.leader);
				_defenders.insertLast(p2);
				
				//_defendersUnit.insertLast(-1);
				//_golds.insertLast(0);
				//_foods.insertLast(0);
			}
			
			prev_callback_209(info,attacker,tactics_id,target_pos,type,critical,ambush);
		}
		
		void 새날()
		{
			while(_attackers.length > 0)
				_attackers.removeAt(0);
			while(_defenders.length > 0)
				_defenders.removeAt(0);
			while(_defendersUnit.length > 0)
				_defendersUnit.removeAt(0);

			while(_golds.length > 0)
				_golds.removeAt(0);
			while(_foods.length > 0)
				_foods.removeAt(0);
		}

		void 부대행동완료(pk::unit@ unit)
		{
			//부대경험치(unit,0);
		}

		void 부대경험치(pk::unit@ unit, int type)
		{
			if (type == 1)
				return;
			
			for(int i=0;i<_attackers.length;i++)
			{
				if(_attackers[i].get_id() == unit.leader)
				{
					if(_defenders[i].mibun == 신분_사망 or _defenders[i].mibun == 신분_포로)
					{
						pk::add_food(unit,_foods[i]*0.25,true);
						pk::add_gold(unit,_golds[i]*0.5,true);
					}
				}
			}
			
		}
		
		void 부대제거2(pk::unit@ unit, int type)
		{
			if (type == 1)
				return;
			if (unit.member[1] >= 0 || unit.member[2] >= 0)
				return;
		
			for(int i=0;i<_defenders.length;i++)
			{
				if(_defenders[i].get_id() == unit.leader)
				{
					//_defendersUnit[i] = unit.get_id();
					//_golds[i] = unit.gold;
					//_foods[i] = unit.food;
					
					if(unit.troops > 0)
					{
						pk::unit@ unit = pk::get_unit(_attackers[i].get_pos());
						pk::add_food(unit,unit.food*0.25,true);
						pk::add_gold(unit,unit.gold*0.5,true);
					}
				}
			}
		}

		void 부대제거(pk::unit@ unit, int type)
		{
			if (type == 1)
				return;
			if (unit.member[1] >= 0 || unit.member[2] >= 0)
				return;

			pk::person@ leader = pk::get_person(unit.member[0]);
			if (leader == null)
				return;
			
			pk::printf("mibun {}\n",leader.mibun);
			if (leader.mibun != 신분_사망 and leader.mibun != 신분_포로)
				return;

			pk::printf("die ~~~~~~~~~~~~~~~~~~~~~~~");
			for (int i = 0; i < 방향_끝; i++)
			{
				pk::point p = pk::get_neighbor_pos(unit.get_pos(), i);
				auto obj = pk::get_hex_object(p);
				if(obj == null || obj.get_type_id() != 11)
					continue;
				
				pk::unit@ unit2 = obj;
				if(unit2.weapon != 병종_기병 or !unit2.action_done)
					continue;
				if(unit2.get_force_id() == unit.get_force_id())
					continue;

				bool bEffect = unit2.is_player() or unit.is_player();
				pk::add_food(unit2,unit.food * 0.25, bEffect);
				pk::add_gold(unit2,unit.gold * 0.5, bEffect);
				break;
			}

		}
	}
	Main main;
}
