bool 처형_인간관계_의형제 = true; // 무장 사망시 의형제무장의 혐오무장 등록
bool 처형_인간관계_배우자 = true; // 무장 사망시 배우자무장의 혐오무장 등록
bool 처형_인간관계_혈연 = true; // 무장 사망시 혈연무장의 혐오무장 등록
bool 처형_인간관계_후계자 = true; // 군주 사망시 후임군주의 혐오무장 등록
bool 사망_기병전법_혐오무장 = true; // 무장이 포로처형이 아닌 기병전법으로 사망시 군주가 아닌 기병부대장을 혐오무장으로 등록
bool 처형_인간관계_친애무장 = false; // 무장 사망시 사망한 장수를 친애무장으로 등록한 장수가 하야하거나 독립

namespace 인간관계
{
	class Main
	{
		Main()
		{
			pk::bind(103, pk::trigger103_t(callbackStart));
			pk::bind(107, pk::trigger107_t(callbackDay));
			pk::bind(112, pk::trigger112_t(callbackTurnEnd));
			pk::bind(171, pk::trigger171_t(callbackDef));
			pk::bind(173, pk::trigger173_t(callbackAtt));
			pk::bind(172, pk::trigger172_t(callbackMov));
		}

		array<array<int>> attack_array;
		array<array<int>> test_array;

		array<array<int>> defender_array;
		array<array<int>> lose_person_array;
		array<int> remove_index;

		void callbackStart()
		{
			lose_person_array.removeRange(0, lose_person_array.length);
			defender_array.removeRange(0, defender_array.length);
			for (int i = 0; i < 무장_끝; i++)
			{
				pk::person@ person = pk::get_person(i);
				if (pk::is_alive(person) )
				{
					setFriend(person);
				}
			}
		}

		void callbackDay()
		{
			remove_index.removeRange(0, remove_index.length);

			for( int i=0; i<lose_person_array.length; i++ )
			{
				pk::person@ person = pk::get_person(lose_person_array[i][0]);
				if(pk::is_alive(person) == false)
				{
					remove_index.insertLast(i);
				}
				else
				{
					lose_person_array[i][1] = person.get_force_id();
					lose_person_array[i][2] = person.mibun;
				}
			}

			for(int i=0; i<remove_index.length; i++)
			{
				lose_person_array.removeAt(remove_index[i] - (i));
			}
		}

		void callbackTurnEnd(pk::force@ force)
		{
			pk::person@ attacker = pk::get_person(force.kunshu);
			remove_index.removeRange(0, remove_index.length);

			for( int i=0; i<lose_person_array.length; i++ )
			{
				if(pk::is_alive(pk::get_person(lose_person_array[i][0])) == false)
				{
					remove_index.insertLast(i);
					if(lose_person_array[i][2] == 신분_군주)
					{
						pk::force@ death_force = pk::get_force(lose_person_array[i][1]);
						pk::person@ successor = pk::get_person(death_force.kunshu);

						if(lose_person_array[i][1] != force.get_id() && death_force.kunshu >= 0 && attacker.get_id() != successor.get_id() && 처형_인간관계_후계자 )
						{
							pk::add_dislike(successor, attacker.get_id());

							if(lose_person_array[i][1] >= 0)
								pk::history_log(pk::get_current_turn_force_id(), pk::get_force(lose_person_array[i][1]).color, pk::encode(pk::format("후계자 \x1b[1x{}\x1b[0x, \x1b[2x{}\x1b[0x측을 원수로 지정" , pk::decode(pk::get_name(successor)) , pk::decode(pk::get_name(attacker) ) ) ) );
							else
								pk::history_log(pk::get_current_turn_force_id(), -1, pk::encode(pk::format("후계자 \x1b[1x{}\x1b[0x, \x1b[2x{}\x1b[0x측을 원수로 지정" , pk::decode(pk::get_name(successor)) , pk::decode(pk::get_name(attacker) ) ) ) );
						}
					}
					
					for(int j=3; j<lose_person_array[i].length; j++)
					{
						pk::person@ person = pk::get_person( lose_person_array[i][j] );
						
						if(pk::is_alive(person) == false)
							continue;
	
						if(pk::is_iminzoku(person) || pk::is_bandit(person) )
							continue;

						if(isFriend(attacker, person) == true)
							continue;

						if(lose_person_array[i][1] != force.get_id() && person.get_id() != attacker.get_id())
						{
							pk::add_dislike(person, attacker.get_id());

							if(person.get_force_id() >= 0)
								pk::history_log(pk::get_current_turn_force_id(), pk::get_force(person.get_force_id()).color, pk::encode(pk::format("\x1b[1x{}\x1b[0x, \x1b[2x{}\x1b[0x측을 원수로 지정" , pk::decode(pk::get_name(person)) , pk::decode(pk::get_name(attacker) ) ) ) );
							else
								pk::history_log(pk::get_current_turn_force_id(), -1, pk::encode(pk::format("\x1b[1x{}\x1b[0x, \x1b[2x{}\x1b[0x측을 원수로 지정" , pk::decode(pk::get_name(person)) , pk::decode(pk::get_name(attacker) ) ) ) );

							if(attacker.mibun == 신분_군주 && person.get_force_id() >= 0 && attacker.get_force_id() == person.get_force_id() && person.get_id() != attacker.get_id())
							{
								int d_aishou = pk::get_aishou_distance(person, attacker.get_id());

								if(person.ambition * 3 > pk::rand(12) && person.service != attacker.service && d_aishou > 5)
								{
									//pk::history_log(pk::get_current_turn_force_id(), pk::get_force(person.get_force_id()).color, pk::encode(pk::format("\x1b[1x{}\x1b[0x. \x1b[2x{}\x1b[0x세력에 불만을 품고 독립" , pk::decode(pk::get_name(person)) , pk::decode(pk::get_name(attacker) ) ) ) );
									pk::hanran(person);
								}
								if(person.get_force_id() == attacker.get_force_id() && d_aishou > 5)
								{
									pk::history_log(pk::get_current_turn_force_id(), pk::get_force(person.get_force_id()).color, pk::encode(pk::format("\x1b[1x{}\x1b[0x. \x1b[2x{}\x1b[0x세력에 불만을 품고 하야" , pk::decode(pk::get_name(person)) , pk::decode(pk::get_name(attacker) ) ) ) );
									pk::resign(person);
								}
							}
						}
						else
						{

						}	
					}

				
				}
			}
			
			for(int i=0; i<remove_index.length; i++)
			{
				lose_person_array.removeAt(remove_index[i] - (i));
			}

			for( int i=0; i<defender_array.length; i++ )
			{
				if(pk::is_alive(pk::get_person(defender_array[i][0])) == true ) 
					continue;
				
				if(defender_array[i].length < 4)
					continue;				

				pk::person@ defender = pk::get_person(pk::get_force(defender_array[i][3]).kunshu);

				if(defender_array[i][2] == 신분_군주)
				{
					pk::force@ death_force = pk::get_force(defender_array[i][1]);
					pk::person@ successor = pk::get_person(death_force.kunshu);
					
					if(defender_array[i][1] == force.get_id() && death_force.kunshu >= 0 && successor.get_id() != defender.get_id() && 처형_인간관계_후계자)
					{
						pk::add_dislike(successor, defender.get_id());

						if(defender_array[i][1] >= 0)
							pk::history_log(pk::get_current_turn_force_id(), pk::get_force(defender_array[i][1]).color, pk::encode(pk::format("후계자 \x1b[1x{}\x1b[0x. \x1b[2x{}\x1b[0x측을 원수로 지정" , pk::decode(pk::get_name(successor)) , pk::decode(pk::get_name(defender) ) ) ) );
						else
							pk::history_log(pk::get_current_turn_force_id(), -1, pk::encode(pk::format("후계자 \x1b[1x{}\x1b[0x. \x1b[2x{}\x1b[0x측을 원수로 지정" , pk::decode(pk::get_name(successor)) , pk::decode(pk::get_name(defender) ) ) ) );
					}							
				}

				for(int j=4; j<defender_array[i].length; j++)
				{
					pk::person@ person = pk::get_person( defender_array[i][j] );
						
					if(pk::is_alive(person) == false)
						continue;
	
					if(pk::is_iminzoku(person) || pk::is_bandit(person) )
						continue;

					if( isFriend(defender, person) == true)
						continue;
	
					if(defender_array[i][1] == force.get_id() && person.get_id() != defender.get_id())
					{
						pk::add_dislike(person, defender.get_id());

						if(person.get_force_id() >= 0)
							pk::history_log(pk::get_current_turn_force_id(), pk::get_force(person.get_force_id()).color, pk::encode(pk::format("\x1b[1x{}\x1b[0x. \x1b[2x{}\x1b[0x측을 원수로 지정" , pk::decode(pk::get_name(person)) , pk::decode(pk::get_name(defender) ) ) ) );
						else	
							pk::history_log(pk::get_current_turn_force_id(), -1, pk::encode(pk::format("\x1b[1x{}\x1b[0x. \x1b[2x{}\x1b[0x측을 원수로 지정" , pk::decode(pk::get_name(person)) , pk::decode(pk::get_name(defender) ) ) ) );

						if(defender.mibun == 신분_군주 && person.get_force_id() >= 0 && defender.get_force_id() == person.get_force_id() && person.get_id() != defender.get_id())
						{
							int d_aishou = pk::get_aishou_distance(person, defender.get_id());

							if(person.ambition * 3 > pk::rand(12) && person.service != defender.service && d_aishou > 5)
							{
								pk::hanran(person);
							}
							if(person.get_force_id() == defender.get_force_id() && d_aishou > 5)
							{
								pk::history_log(pk::get_current_turn_force_id(), pk::get_force(person.get_force_id()).color, pk::encode(pk::format("\x1b[1x{}\x1b[0x. \x1b[2x{}\x1b[0x세력에 불만을 품고 하야" , pk::decode(pk::get_name(person)) , pk::decode(pk::get_name(defender) ) ) ) );
								pk::resign(person);
							}
						}
					}	
				}	
			}

			defender_array.removeRange(0, defender_array.length);
		}

		//부대괴멸
		void callbackDef(pk::unit@ unit, int type)
		{
			if(type > 0)
				return;

			for( int i=0; i<defender_array.length; i++ )
			{
				if(unit.leader != defender_array[i][0])
					continue;

				pk::person@ lose_person = pk::get_person(defender_array[i][0]);

				for (int j = 0; j < 무장_끝; j++)
				{
					pk::person@ person = pk::get_person(j);
					if (pk::is_alive(person) && person.get_id() != lose_person.get_id() && isFriend(lose_person, person))
					{
						defender_array[i].insertLast(person.get_id());
					}
				}
			}
		}

		void callbackAtt(pk::unit@ unit, int type)
		{
			pk::force@ force = pk::get_force(unit.get_force_id());

			if(pk::get_current_turn_force_id() == unit.get_force_id())
			{
				pk::person@ attacker = pk::get_person(unit.leader);
				array<int> arr;
				arr.insertLast(unit.leader);
				arr.insertLast(unit.get_force_id());
				arr.insertLast(attacker.mibun);
				defender_array.insertLast(arr);
				attack_array.insertLast(arr);				

				if (pk::is_alive(attacker))
				{
					arr.insertLast(attacker.get_id());
				}

				if(사망_기병전법_혐오무장 == false)
					return;

				if( (type >= 33 && type <= 40) || type == 88 )
				{
					addDislike(force, attacker);
				}
			}
			else if(defender_array.length > 0)	
			{
				defender_array[defender_array.length-1].insertLast(unit.get_force_id());
			}		
		}

		void callbackMov(pk::unit@ unit, const pk::point &in)
		{
			pk::force@ force = pk::get_force(pk::get_current_turn_force_id());
			pk::person@ attacker = pk::get_person(force.kunshu);
			addDislike(force, attacker);
		}

		void addDislike(pk::force@ force, pk::person@ attacker)
		{
			remove_index.removeRange(0, remove_index.length);

			for( int i=0; i<lose_person_array.length; i++ )
			{
				if(pk::is_alive(pk::get_person(lose_person_array[i][0])) == false)
				{
					remove_index.insertLast(i);
					if(lose_person_array[i][2] == 신분_군주)
					{
						pk::force@ death_force = pk::get_force(lose_person_array[i][1]);
						pk::person@ successor = pk::get_person(death_force.kunshu);

						if(lose_person_array[i][1] != force.get_id() && death_force.kunshu >= 0 && attacker.get_id() != successor.get_id() && 처형_인간관계_후계자 )
						{
							pk::add_dislike(successor, attacker.get_id());

							if(lose_person_array[i][1] >= 0)
								pk::history_log(pk::get_current_turn_force_id(), pk::get_force(lose_person_array[i][1]).color, pk::encode(pk::format("후계자 \x1b[1x{}\x1b[0x, \x1b[2x{}\x1b[0x측을 원수로 지정" , pk::decode(pk::get_name(successor)) , pk::decode(pk::get_name(attacker) ) ) ) );
							else
								pk::history_log(pk::get_current_turn_force_id(), -1, pk::encode(pk::format("후계자 \x1b[1x{}\x1b[0x, \x1b[2x{}\x1b[0x측을 원수로 지정" , pk::decode(pk::get_name(successor)) , pk::decode(pk::get_name(attacker) ) ) ) );
						}
					}
					
					for(int j=3; j<lose_person_array[i].length; j++)
					{
						pk::person@ person = pk::get_person( lose_person_array[i][j] );
						
						if(pk::is_alive(person) == false)
							continue;
	
						if(pk::is_iminzoku(person) || pk::is_bandit(person) )
							continue;

						if(isFriend(attacker, person) == true)
							continue;

						if(lose_person_array[i][1] != force.get_id() && person.get_id() != attacker.get_id())
						{
							pk::add_dislike(person, attacker.get_id());

							if(person.get_force_id() >= 0)
								pk::history_log(pk::get_current_turn_force_id(), pk::get_force(person.get_force_id()).color, pk::encode(pk::format("\x1b[1x{}\x1b[0x, \x1b[2x{}\x1b[0x측을 원수로 지정" , pk::decode(pk::get_name(person)) , pk::decode(pk::get_name(attacker) ) ) ) );
							else
								pk::history_log(pk::get_current_turn_force_id(), -1, pk::encode(pk::format("\x1b[1x{}\x1b[0x, \x1b[2x{}\x1b[0x측을 원수로 지정" , pk::decode(pk::get_name(person)) , pk::decode(pk::get_name(attacker) ) ) ) );

							if(attacker.mibun == 신분_군주 && person.get_force_id() >= 0 && attacker.get_force_id() == person.get_force_id() && person.get_id() != attacker.get_id())
							{
								int d_aishou = pk::get_aishou_distance(person, attacker.get_id());

								if(person.ambition * 3 > pk::rand(12) && person.service != attacker.service && d_aishou > 5)
								{
									pk::hanran(person);
								}
								if(person.get_force_id() == attacker.get_force_id() && d_aishou > 5)
								{
									pk::history_log(pk::get_current_turn_force_id(), pk::get_force(person.get_force_id()).color, pk::encode(pk::format("\x1b[1x{}\x1b[0x. \x1b[2x{}\x1b[0x세력에 불만을 품고 하야" , pk::decode(pk::get_name(person)) , pk::decode(pk::get_name(attacker) ) ) ) );
									pk::resign(person);
								}
							}
						}
						else
						{

						}	
					}
				}
			}

			for(int i=0; i<remove_index.length; i++)
			{
				lose_person_array.removeAt(remove_index[i] - (i));
			}
		}

		void setFriend(pk::person@ lose_person)
		{
			array<int> arr;

			arr.insertLast(lose_person.get_id());
			arr.insertLast(lose_person.get_force_id());
			arr.insertLast(lose_person.mibun);

			for (int i = 0; i < 무장_끝; i++)
			{
				pk::person@ person = pk::get_person(i);
				if (pk::is_alive(person) && person.get_id() != lose_person.get_id() && isFriend(lose_person, person))
				{
					arr.insertLast(person.get_id());
				}
			}

			lose_person_array.insertLast(arr);
		}

		bool isFriend(pk::person@ person1, pk::person@ person2)
		{
			bool result = false;

			if(pk::is_gikyoudai(person1, person2.get_id()) && 처형_인간관계_의형제)
				result = true;
			if(pk::is_fuufu(person1, person2.get_id()) && 처형_인간관계_배우자)
				result = true;
			if(pk::is_ketsuen(person1, person2.get_id()) && 처형_인간관계_혈연)
				result = true;
			if(pk::is_oyako(person1, person2.get_id()) && 처형_인간관계_혈연)
				result = true;
			if(pk::is_like(person2, person1.get_id()) && 처형_인간관계_친애무장)
				result = true;
			if(pk::is_dislike(person2, person1.get_id()))
				result = false;

			return result;	
		}
	}

	Main main;
}