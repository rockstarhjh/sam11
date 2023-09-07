// 화타
namespace Ebony_신무장_화타
{
	const int 화타_신무장번호 = 960;	// 화타 신무장 번호 입력
	const int 특기_신의 = 200;
	const int 화타_충성도 = 80;
	const bool 포상금지 = true;
	const bool 충성도변화 = true; // 충성도변화 true false		
	
	class Main
	{
		
		pk::person@ 화타 = pk::get_person(화타_신무장번호);
        
        Main()
		{
            pk::bind(102, pk::trigger102_t(onGameInit));
			pk::bind(107, pk::trigger107_t(callback));
			pk::bind(111, pk::trigger111_t(character_huatuo));
        }
		
		pk::force@ 화타_세력 = pk::get_force(화타.force_id);
		pk::person@ 군주;
		pk::city@ 도시;	
		
		
		void onGameInit()
        {character_huatuo_skill_info();}
		
		void callback()
        {
			auto building_list = pk::list_to_array(pk::get_building_list());
			
            for (int i = 0; i < building_list.length; i++)
            {				
				pk::building@ building = building_list[i];
				shoubyou_set_city(building);
			}
			shoubyou_set_unit();
		}
		
		void character_huatuo_skill_info()
		{
			pk::get_skill(특기_신의).name = pk::u8encode("신의");
			pk::get_skill(특기_신의).desc = pk::u8encode("매턴 자신의 부대나 거점 무장의 부상 완화");
			pk::get_skill(특기_신의).type = 특기종류_보조;
		}
		
		void character_huatuo(pk::force@ force)
        {
			화타.banned_kunshu = -1;
			화타.ban_timer = 0;
			
			if (화타_세력 !is null)
			{					
				if (충성도변화)
				{
					@군주 = pk::get_person(화타_세력.kunshu);				
					화타.aishou = 군주.aishou;
					화타.loyalty = 화타_충성도;
				}
				
				if (포상금지)
				{화타.reward_done = true;}
			}			
		
		}
		
		//매턴 화타와 같은 소속 도시의 무장을 치료
		void shoubyou_set_city(pk::building@ building)
        {
			
			auto mibun_list = pk::list_to_array(pk::get_person_list(building, pk::mibun_flags(신분_군주,신분_도독,신분_태수,신분_일반)));
			
			if (0 < mibun_list.length)
			{
				
				for (int i = 0; i < mibun_list.length; i++)
				{
					
					pk::person@ person_t = mibun_list[i];
	
					
					if (person_t.location == 화타.location and !pk::is_absent(화타) and !pk::is_unitize(화타))
					{	
				
						pk::point pos = 화타.get_pos();						
				
						if (person_t.get_id() != 무장_화타2)
						{
							string person_t_name = pk::u8decode(pk::get_name(person_t));
							
							switch (person_t.shoubyou)
							{
								case 0 : break;
								case 1 : 										
									switch (pk::rand(3))
									{
										case 0 : pk::say(pk::u8encode(pk::format("차도가 좋습니다, {}님!", person_t_name)), 화타);break;
										case 1 : pk::say(pk::u8encode(pk::format("{}님, 경과가 좋습니다!", person_t_name)), 화타);break;
										case 2 : pk::say(pk::u8encode(pk::format("{}님.\n이제 곧 완치될 것입니다.", person_t_name)), 화타);break;
									}
									break;
								case 2 :
									switch (pk::rand(3))
									{
										case 0 : pk::say(pk::u8encode(pk::format("{}님.\n상처가 아직 심합니다.", person_t_name)), 화타);break;
										case 1 : pk::say(pk::u8encode(pk::format("아직 무리하시면 안 되옵니다,\n{}님.", person_t_name)), 화타);break;
										case 2 : pk::say(pk::u8encode(pk::format("{}님\n가급적 후방에 머무르소서..", person_t_name)), 화타);break;
									}
									break;
								case 3 :
									switch (pk::rand(3))
									{
										case 0 : pk::say(pk::u8encode(pk::format("{}님! 아니, 어찌 이런..", person_t_name)), 화타);break;
										case 1 : pk::say(pk::u8encode(pk::format("{}님, 이런 상처라니..", person_t_name)), 화타);break;
										case 2 : pk::say(pk::u8encode(pk::format("{}님.\n뼈의 독을 긁어내야 합니다.", person_t_name)), 화타);break;
									}
									break;

							}
						}
						
						if (person_t.get_id() == 무장_화타2)
						{
							switch (person_t.shoubyou)
							{
								case 0 : break;
								case 1 : 										
									switch (pk::rand(3))
									{
										case 0 : pk::say(pk::u8encode("차도가 좋군.."), 화타);break;
										case 1 : pk::say(pk::u8encode("경과가 좋구나.."), 화타);break;
										case 2 : pk::say(pk::u8encode("이제 곧.."), 화타);break;
									}
									break;
								case 2 :
									switch (pk::rand(3))
									{
										case 0 : pk::say(pk::u8encode("상처가 아직 심해.."), 화타);break;
										case 1 : pk::say(pk::u8encode("힘을 내야 한다.."), 화타);break;
										case 2 : pk::say(pk::u8encode("내가 살아야 더 많은 사람을.."), 화타);break;
									}
									break;
								case 3 :
									switch (pk::rand(3))
									{
										case 0 : pk::say(pk::u8encode("아니, 어찌 이런.."), 화타);break;
										case 1 : pk::say(pk::u8encode("으윽.. 이런 상처라니.."), 화타);break;
										case 2 : pk::say(pk::u8encode("뼈까지 다친 것인가.."), 화타);break;
									}
									break;

							}
						}
						
						if (person_t.shoubyou >= 1)
						{
							pk::play_se(80, pos);
							pk::create_effect(0x4d, pos);
							
							person_t.shoubyou -= 1;
						}
					
						if (person_t.shoubyou < 0)
						{person_t.shoubyou = 0;}
						person_t.update();
					}
					
					
					if (person_t.get_id() == 무장_화타2)
					{
						switch (pk::rand(13))
						{
							case 0 : pk::say(pk::u8encode("저는 사실 의사가 아니고\n선비입니다.."), 화타);break;
							case 1 : pk::say(pk::u8encode("선비.. 저는 선비이옵니다.."), 화타);break;
							case 2 : break;
							case 3 : break;
							case 4 : break;
							case 5 : break;
							case 6 : break;
							case 7 : break;
							case 8 : break;
							case 9 : break;
							case 10 : break;
							case 11 : break;
							case 12 : break;
							case 13 : break;
						}
					}
					
					
				}
				
			}
			
		}
		
		//매턴 화타 부대의 무장을 치료
		void shoubyou_set_unit() 
		{
			
			auto list = pk::list_to_array(pk::get_unit_list());
			
			for (int i = 0; i < list.length; i++)
			{
			
				pk::unit@ src = list[i];
				pk::point pos = src.get_pos();
				
				pk::person@ src_leader = pk::get_person(src.leader);
				pk::person@ src_deputy1 = pk::get_person(src.member[1]);
				pk::person@ src_deputy2 = pk::get_person(src.member[2]);
				
				int deputy1 = src.member[1];
				int deputy2 = src.member[2];
				
                bool cure_leader = false;
				bool cure_leader_self = false;
				bool cure_deputy1 = false;
				bool cure_deputy1_self = false;				
				bool cure_deputy2 = false;
				bool cure_deputy2_self = false;				
				
				//src_leader.get_id() != 무장_화타2
				
				if (src.has_skill(특기_신의) and !pk::is_alive(src_deputy1) and !pk::is_alive(src_deputy2))
                {	
					//주장 치료
					if (src_leader.shoubyou >= 1)
					{
						pk::play_se(80, pos);
						pk::create_effect(0x4d, pos);
						
                        cure_leader_self = true;
					}
                }
				
				
				else if (src.has_skill(특기_신의) and pk::is_alive(src_deputy1) and !pk::is_alive(src_deputy2))
                {
					
					if (src_leader.shoubyou >= 1 or src_deputy1.shoubyou >= 1)
					{
						pk::play_se(80, pos);
						pk::create_effect(0x4d, pos);
					}
					
					//주장 치료
					if (src_leader.shoubyou >= 1 and src_leader.get_id() != 무장_화타2 )
                        cure_leader = true;
					else if (src_leader.shoubyou >= 1 and src_leader.get_id() == 무장_화타2 )
                        cure_leader_self = true;
					
					//부장1 치료
					if (src_deputy1.shoubyou >= 1 and src_deputy1.get_id() != 무장_화타2 )
                        cure_deputy1 = true;
					else if (src_deputy1.shoubyou >= 1 and src_deputy1.get_id() == 무장_화타2 )
                        cure_deputy1_self = true;
                }
				
                else if (src.has_skill(특기_신의) and pk::is_alive(src_deputy1) and pk::is_alive(src_deputy2))
                {
					
					if (src_leader.shoubyou >= 1 or src_deputy1.shoubyou >= 1 or src_deputy2.shoubyou >= 1)
					{
						pk::play_se(80, pos);
						pk::create_effect(0x4d, pos);
					}					
					
					//주장 치료
					if (src_leader.shoubyou >= 1 and src_leader.get_id() != 무장_화타2 )
                        cure_leader = true;
					else if (src_leader.shoubyou >= 1 and src_leader.get_id() == 무장_화타2 )
                        cure_leader_self = true;
					
					//부장1 치료
					if (src_deputy1.shoubyou >= 1 and src_deputy1.get_id() != 무장_화타2 )
                        cure_deputy1 = true;
					else if (src_deputy1.shoubyou >= 1 and src_deputy1.get_id() == 무장_화타2 )
                        cure_deputy1_self = true;
					
					//부장2 치료
					if (src_deputy2.shoubyou >= 1 and src_deputy2.get_id() != 무장_화타2 )
                        cure_deputy2 = true;
					else if (src_deputy2.shoubyou >= 1 and src_deputy2.get_id() == 무장_화타2 )
                        cure_deputy2_self = true;
                }
				
                //치료
                if (cure_leader)
                {
					string src_leader_name = pk::u8decode(pk::get_name(src_leader));
					
					switch (src_leader.shoubyou)
					{
						case 0 : break;
						case 1 : 										
							switch (pk::rand(3))
							{
								case 0 : pk::say(pk::u8encode(pk::format("차도가 좋습니다, {}님!", src_leader_name)), 화타);break;
								case 1 : pk::say(pk::u8encode(pk::format("{}님, 경과가 좋습니다!", src_leader_name)), 화타);break;
								case 2 : pk::say(pk::u8encode(pk::format("{}님.\n이제 곧 완치될 것입니다.", src_leader_name)), 화타);break;
							}
							break;
						case 2 :
							switch (pk::rand(3))
							{
								case 0 : pk::say(pk::u8encode(pk::format("{}님.\n상처가 아직 심합니다.", src_leader_name)), 화타);break;
								case 1 : pk::say(pk::u8encode(pk::format("아직 무리하시면 안 되옵니다,\n{}님.", src_leader_name)), 화타);break;
								case 2 : pk::say(pk::u8encode(pk::format("{}님\n가급적 후방에 머무르소서..", src_leader_name)), 화타);break;
							}
							break;
						case 3 :
							switch (pk::rand(3))
							{
								case 0 : pk::say(pk::u8encode(pk::format("{}님! 아니, 어찌 이런..", src_leader_name)), 화타);break;
								case 1 : pk::say(pk::u8encode(pk::format("{}님, 이런 상처라니..", src_leader_name)), 화타);break;
								case 2 : pk::say(pk::u8encode(pk::format("{}님.\n뼈의 독을 긁어내야 합니다.", src_leader_name)), 화타);break;
							}
							break;
					}
					
					src_leader.shoubyou -= 1;
					
					if (src_leader.shoubyou < 0)
					{src_leader.shoubyou = 0;}
					src_leader.update();
                }
				
                if (cure_leader_self)
                {
					string src_leader_name = pk::u8decode(pk::get_name(src_leader));
				
					switch (src_leader.shoubyou)
					{
						case 0 : break;
						case 1 : 										
							switch (pk::rand(3))
							{
								case 0 : pk::say(pk::u8encode(pk::format("차도가 좋군..", src_leader_name)), 화타);break;
								case 1 : pk::say(pk::u8encode(pk::format("경과가 좋구나..", src_leader_name)), 화타);break;
								case 2 : pk::say(pk::u8encode(pk::format("이제 곧..", src_leader_name)), 화타);break;
							}
							break;
						case 2 :
							switch (pk::rand(3))
							{
								case 0 : pk::say(pk::u8encode(pk::format("상처가 아직 심해..", src_leader_name)), 화타);break;
								case 1 : pk::say(pk::u8encode(pk::format("내가 왜 전장에..", src_leader_name)), 화타);break;
								case 2 : pk::say(pk::u8encode(pk::format("내가 살아야 더 많은 사람을..", src_leader_name)), 화타);break;
							}
						case 3 :
							switch (pk::rand(3))
							{
								case 0 : pk::say(pk::u8encode(pk::format("아니, 어찌 이런..", src_leader_name)), 화타);break;
								case 1 : pk::say(pk::u8encode(pk::format("으윽.. 이런 상처라니..", src_leader_name)), 화타);break;
								case 2 : pk::say(pk::u8encode(pk::format("뼈까지 다친 것인가..", src_leader_name)), 화타);break;
							}
							break;
					}
					
					src_leader.shoubyou -= 1;
					
					if (src_leader.shoubyou < 0)
					{src_leader.shoubyou = 0;}
					src_leader.update();					
                }
				
				if (cure_deputy1)
                {
					string src_deputy1_name = pk::u8decode(pk::get_name(src_deputy1));			
				
					switch (src_deputy1.shoubyou)
					{
						case 0 : break;
						case 1 : 										
							switch (pk::rand(3))
							{
								case 0 : pk::say(pk::u8encode(pk::format("차도가 좋습니다, {}님!", src_deputy1_name)), 화타);break;
								case 1 : pk::say(pk::u8encode(pk::format("{}님, 경과가 좋습니다!", src_deputy1_name)), 화타);break;
								case 2 : pk::say(pk::u8encode(pk::format("{}님.\n이제 곧 완치될 것입니다.", src_deputy1_name)), 화타);break;
							}
							break;
						case 2 :
							switch (pk::rand(3))
							{
								case 0 : pk::say(pk::u8encode(pk::format("{}님.\n상처가 아직 심합니다.", src_deputy1_name)), 화타);break;
								case 1 : pk::say(pk::u8encode(pk::format("아직 무리하시면 안 되옵니다,\n{}님.", src_deputy1_name)), 화타);break;
								case 2 : pk::say(pk::u8encode(pk::format("{}님\n가급적 후방에 머무르소서..", src_deputy1_name)), 화타);break;
							}
							break;
						case 3 :
							switch (pk::rand(3))
							{
								case 0 : pk::say(pk::u8encode(pk::format("{}님! 아니, 어찌 이런..", src_deputy1_name)), 화타);break;
								case 1 : pk::say(pk::u8encode(pk::format("{}님, 이런 상처라니..", src_deputy1_name)), 화타);break;
								case 2 : pk::say(pk::u8encode(pk::format("{}님.\n뼈의 독을 긁어내야 합니다.", src_deputy1_name)), 화타);break;
							}
							break;
					}
					
					src_deputy1.shoubyou -= 1;
					
					if (src_deputy1.shoubyou < 0)
					{src_deputy1.shoubyou = 0;}
					src_deputy1.update();					
                }
				
				if (cure_deputy1_self)
                {
					string src_deputy1_name = pk::u8decode(pk::get_name(src_deputy1));			
					
					switch (src_deputy1.shoubyou)
					{
						case 0 : break;
						case 1 : 										
							switch (pk::rand(3))
							{
								case 0 : pk::say(pk::u8encode(pk::format("차도가 좋군..", src_deputy1_name)), 화타);break;
								case 1 : pk::say(pk::u8encode(pk::format("경과가 좋구나..", src_deputy1_name)), 화타);break;
								case 2 : pk::say(pk::u8encode(pk::format("이제 곧..", src_deputy1_name)), 화타);break;
							}
							break;
						case 2 :
							switch (pk::rand(3))
							{
								case 0 : pk::say(pk::u8encode(pk::format("상처가 아직 심해..", src_deputy1_name)), 화타);break;
								case 1 : pk::say(pk::u8encode(pk::format("내가 왜 전장에..", src_deputy1_name)), 화타);break;
								case 2 : pk::say(pk::u8encode(pk::format("내가 살아야 더 많은 사람을..", src_deputy1_name)), 화타);break;
							}
							break;
						case 3 :
							switch (pk::rand(3))
							{
								case 0 : pk::say(pk::u8encode(pk::format("아니, 어찌 이런..", src_deputy1_name)), 화타);break;
								case 1 : pk::say(pk::u8encode(pk::format("으윽.. 이런 상처라니..", src_deputy1_name)), 화타);break;
								case 2 : pk::say(pk::u8encode(pk::format("뼈까지 다친 것인가..", src_deputy1_name)), 화타);break;
							}
							break;
					}
					
					src_deputy1.shoubyou -= 1;
					
					if (src_deputy1.shoubyou < 0)
					{src_deputy1.shoubyou = 0;}
					src_deputy1.update();
                }
				
				if (cure_deputy2)
                {
					string src_deputy2_name = pk::u8decode(pk::get_name(src_deputy2));			
					switch (src_deputy2.shoubyou)
					{
						case 0 : break;
						case 1 : 										
							switch (pk::rand(3))
							{
								case 0 : pk::say(pk::u8encode(pk::format("차도가 좋습니다, {}님!", src_deputy2_name)), 화타);break;
								case 1 : pk::say(pk::u8encode(pk::format("{}님, 경과가 좋습니다!", src_deputy2_name)), 화타);break;
								case 2 : pk::say(pk::u8encode(pk::format("{}님.\n이제 곧 완치될 것입니다.", src_deputy2_name)), 화타);break;
							}
							break;
						case 2 :
							switch (pk::rand(3))
							{
								case 0 : pk::say(pk::u8encode(pk::format("{}님.\n상처가 아직 심합니다.", src_deputy2_name)), 화타);break;
								case 1 : pk::say(pk::u8encode(pk::format("아직 무리하시면 안 되옵니다,\n{}님.", src_deputy2_name)), 화타);break;
								case 2 : pk::say(pk::u8encode(pk::format("{}님\n가급적 후방에 머무르소서..", src_deputy2_name)), 화타);break;
							}
							break;
						case 3 :
							switch (pk::rand(3))
							{
								case 0 : pk::say(pk::u8encode(pk::format("{}님! 아니, 어찌 이런..", src_deputy2_name)), 화타);break;
								case 1 : pk::say(pk::u8encode(pk::format("{}님, 이런 상처라니..", src_deputy2_name)), 화타);break;
								case 2 : pk::say(pk::u8encode(pk::format("{}님.\n뼈의 독을 긁어내야 합니다.", src_deputy2_name)), 화타);break;
							}
							break;
					}
					
					src_deputy2.shoubyou -= 1;
					
					if (src_deputy2.shoubyou < 0)
					{src_deputy2.shoubyou = 0;}
					src_deputy2.update();					
                }
				
				if (cure_deputy2_self)
                {
					string src_deputy2_name = pk::u8decode(pk::get_name(src_deputy2));			
					switch (src_deputy2.shoubyou)
					{
						case 0 : break;
						case 1 : 										
							switch (pk::rand(3))
							{
								case 0 : pk::say(pk::u8encode(pk::format("차도가 좋군..", src_deputy2_name)), 화타);break;
								case 1 : pk::say(pk::u8encode(pk::format("경과가 좋구나..", src_deputy2_name)), 화타);break;
								case 2 : pk::say(pk::u8encode(pk::format("이제 곧..", src_deputy2_name)), 화타);break;
							}
							break;
						case 2 :
							switch (pk::rand(3))
							{
								case 0 : pk::say(pk::u8encode(pk::format("상처가 아직 심해..", src_deputy2_name)), 화타);break;
								case 1 : pk::say(pk::u8encode(pk::format("내가 왜 전장에..", src_deputy2_name)), 화타);break;
								case 2 : pk::say(pk::u8encode(pk::format("내가 살아야 더 많은 사람을..", src_deputy2_name)), 화타);break;
							}
							break;
						case 3 :
							switch (pk::rand(3))
							{
								case 0 : pk::say(pk::u8encode(pk::format("아니, 어찌 이런..", src_deputy2_name)), 화타);break;
								case 1 : pk::say(pk::u8encode(pk::format("으윽.. 이런 상처라니..", src_deputy2_name)), 화타);break;
								case 2 : pk::say(pk::u8encode(pk::format("뼈까지 다친 것인가..", src_deputy2_name)), 화타);break;
							}
							break;
					}
					
					src_deputy2.shoubyou -= 1;
					
					if (src_deputy2.shoubyou < 0)
					{src_deputy2.shoubyou = 0;}
					src_deputy2.update();
                }
							
			}

		} 
		
	}
	Main main;
}