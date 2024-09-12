/*
@만든이: 크래픽스
@Update: 2023.8.30, 최초배포
@Update: 2023.8.31, 군주 인접효과추가, 질주,기각,나선첨 혼란 방어 추가.
@Update: 2023.9.6, 명경위보가, 군주가 아닌 무장에도 적용되었던버그수정
@Update: 2024.5.9, 예외처리
@Update: 2024.5.17 건물데미지도 방어력 처리
@Update: 2024.6.2 군주 소병력 혼란방어 적용되지 않던버그 수정
*/

namespace 군주효과_Lord_Effect
{
	const bool 군주_효과_인접무장만_적용 = true;
	const int 군주_효과_인접거리 = 2;
	
	const bool AI_군주_전체_주악_효과 = true;
	const bool 유저_군주_전체_주악_효과 = false;
	const int 전체_주악_효과 = 4;
	const int 군주_주악_효과 = 4;

	const bool AI_군주_전체_공방_효과 = true;
	const bool 유저_군주_전체_공방_효과 = false;
	const float 전체_공격력_효과 = 0.1;
	const float 군주_공격력_효과 = 0.1;
	const float 전체_방어력_효과 = 0.1;
	const float 군주_방어력_효과 = 0.1;

	const bool AI_군주_전체_전법_효과 = true;
	const bool 유저_군주_전체_전법_효과 = false;
	const int 전체_전법_효과 = 5;
	const int 군주_전법_효과 = 5;
	const int 전체_전법방어_효과 = 5;
	const int 군주_전법방어_효과 = 5;

	const bool AI_군주_전법_크리티컬 = true;
	const bool 유저_군주_전법_크리티컬 = false;
	const bool AI_군주_전법_크리티컬_방어 = true;
	const bool 유저_군주_전법_크리티컬_방어 = false;

	const bool AI_군주_전체_계략_효과 = false;
	const bool 유저_군주_전체_계략_효과 = false;
	const int 전체_계략_효과 = 5;
	const int 군주_계략_효과 = 5;
	const int 전체_계략방어_효과 = 5;
	const int 군주_계략방어_효과 = 5;

	const bool AI_군주_전체_계략_크리티컬= false;
	const bool 유저_군주_전체_계략_크리티컬 = false;
	const int 전체_계략_크리티컬 = 5;
	const int 군주_계략_크리티컬 = 5;
	const int 전체_계략방어_크리티컬 = 5;
	const int 군주_계략방어_크리티컬 = 5;

	const bool AI_군주_기병전법사망_방어 = true;
	const bool 유저_군주_기병전법사망_방어 = true;

	const bool AI_군주_포박안됨 = false;
	const bool 유저_군주_포박안됨 = false;

	const bool AI_군주_명경효과 = false;
	const bool 유저_군주_명경효과 = false;

	const bool AI_군주_질주혼란_방어 = false;
	const bool 유저_군주_질주혼란_방어 = false;

	const bool AI_군주_나선첨혼란_방어 = false;
	const bool 유저_군주_나선첨혼란_방어 = false;

	const bool AI_군주_기각혼란_방어 = false;
	const bool 유저_군주_기각혼란_방어 = false;

	const bool AI_군주_소병력혼란_방어 = true;
	const bool 유저_군주_소병력혼란_방어 = false;



	////////////////////////////////유저 옵션 아님.
	const int 효과_주악 = 0;
	const int 효과_공방 = 1;
	const int 효과_포박 = 2;
	const int 효과_전법 = 3;
	const int 효과_크리티컬 = 4;
	const int 효과_크리티컬_방어 = 5;
	const int 효과_계략 = 6;
	const int 효과_계략_크리티컬 = 7;
	const int 효과_기병전법사망_방어 = 8;
	const int 효과_명경 = 9;
	const int 효과_질주_방어 = 10;
	const int 효과_나선첨_방어 = 11;
	const int 효과_기각_방어 = 12;
	const int 효과_소병력혼란_방어 = 13;



	class Main
	{

		pk::func209_t@ prev_callback_209;
		pk::func202_t@ prev_callback_202;
		pk::func201_t@ prev_callback_201;
		pk::func203_t@ prev_callback_203;
		pk::func220_t@ prev_callback_220;
		pk::func206_t@ prev_callback_206;
		pk::func207_t@ prev_callback_207;
		pk::func221_t@ prev_callback_221;
		pk::func222_t@ prev_callback_222;
		pk::func223_t@ prev_callback_223;
		pk::func164_t@ prev_callback_164;
		pk::func211_t@ prev_callback_211;


		Main()
		{
			@prev_callback_209 = cast<pk::func209_t@>(pk::get_func(209));
			pk::reset_func(209);
			pk::set_func(209, pk::func209_t(callback209));  

			@prev_callback_202 = cast<pk::func202_t@>(pk::get_func(202));
			pk::reset_func(202);
			pk::set_func(202, pk::func202_t(callback202));

			@prev_callback_201 = cast<pk::func201_t@>(pk::get_func(201));
			pk::reset_func(201);
			pk::set_func(201, pk::func201_t(callback201));

			@prev_callback_203 = cast<pk::func203_t@>(pk::get_func(203));
			pk::reset_func(203);
			pk::set_func(203, pk::func203_t(callback203));


			@prev_callback_220 = cast<pk::func220_t@>(pk::get_func(220));
			pk::reset_func(220);
			pk::set_func(220, pk::func220_t(callback220));

			@prev_callback_206 = cast<pk::func206_t@>(pk::get_func(206));
			pk::reset_func(206);
			pk::set_func(206, pk::func206_t(callback206));

			@prev_callback_207 = cast<pk::func207_t@>(pk::get_func(207));
			pk::reset_func(207);
			pk::set_func(207, pk::func207_t(callback207));

			@prev_callback_221 = cast<pk::func221_t@>(pk::get_func(221));
			pk::reset_func(221);
			pk::set_func(221, pk::func221_t(callback221));

			@prev_callback_222 = cast<pk::func222_t@>(pk::get_func(222));
			pk::reset_func(222);
			pk::set_func(222, pk::func222_t(callback222));

			@prev_callback_223 = cast<pk::func223_t@>(pk::get_func(223));
			pk::reset_func(223);
			pk::set_func(223, pk::func223_t(callback223));

			@prev_callback_164 = cast<pk::func164_t@>(pk::get_func(164));
			pk::reset_func(164);
			pk::set_func(164, pk::func164_t(callback164));

			@prev_callback_211 = cast<pk::func211_t@>(pk::get_func(211));
			pk::reset_func(211);
			pk::set_func(211, pk::func211_t(callback211));


			//pk::bind(107, pk::trigger107_t(onNewDay));
			pk::bind(111, pk::trigger111_t(onTurnStart));

		}
		void onNewDay()
		{
		}

		void onTurnStart(pk::force@ force)
		{
			if (!forceCheck(force,효과_주악))
				return;
			
			pk::list<pk::unit@> units = pk::get_unit_list(force);
			pk::person@ kunshu = pk::get_person(force.kunshu);
			if(kunshu==null || !pk::is_unitize(kunshu))
				return;
			for (int i = 0; i < units.count; i++)
			{
				pk::unit@ u = units[i];
				if (u==null)
					continue;

				if(!areaCheck(u))
					continue;

				int off = u.leader == kunshu.get_id() ? 군주_주악_효과 : 전체_주악_효과;
				pk::add_energy(u, off, true);
			}

		}

		bool forceCheck(pk::unit@ u, int type)
		{
			if (u == null)
				return false;
			return forceCheck(pk::get_person(u.leader), type);
		}
		bool forceCheck(pk::person@ p, int type)
		{
			if(p==null)
				return false;
			return forceCheck(pk::get_force(p.get_force_id()), type);
		}

		bool forceCheck(pk::force@ force , int type)
		{
			if(force==null)
				return false;
			switch (type)
			{
			case 효과_주악:
				if (force.is_player() and 유저_군주_전체_주악_효과)
					return true;
				if (!force.is_player() and AI_군주_전체_주악_효과)
					return true;
				break;
			case 효과_공방:
				if (force.is_player() and 유저_군주_전체_공방_효과)
					return true;
				if (!force.is_player() and AI_군주_전체_공방_효과)
					return true;
				break;
			case 효과_포박:
				if (force.is_player() and 유저_군주_포박안됨)
					return true;
				if (!force.is_player() and AI_군주_포박안됨)
					return true;
				break;
			case 효과_전법:
				if (force.is_player() and 유저_군주_전체_전법_효과)
					return true;
				if (!force.is_player() and AI_군주_전체_전법_효과)
					return true;
				break;
			case 효과_크리티컬:
				if (force.is_player() and 유저_군주_전법_크리티컬)
					return true;
				if (!force.is_player() and AI_군주_전법_크리티컬)
					return true;
				break;
			case 효과_크리티컬_방어:
				if (force.is_player() and 유저_군주_전법_크리티컬_방어)
					return true;
				if (!force.is_player() and AI_군주_전법_크리티컬_방어)
					return true;
				break;
			case 효과_계략:
				if (force.is_player() and 유저_군주_전체_계략_효과)
					return true;
				if (!force.is_player() and AI_군주_전체_계략_효과)
					return true;
				break;
			case 효과_계략_크리티컬:
				if (force.is_player() and 유저_군주_전체_계략_크리티컬)
					return true;
				if (!force.is_player() and AI_군주_전체_계략_크리티컬)
					return true;
				break;
			case 효과_기병전법사망_방어:
				if (force.is_player() and 유저_군주_기병전법사망_방어)
					return true;
				if (!force.is_player() and AI_군주_기병전법사망_방어)
					return true;
				break;
			case 효과_명경:
				if (force.is_player() and 유저_군주_명경효과)
					return true;
				if (!force.is_player() and AI_군주_명경효과)
					return true;
				break;
			case 효과_질주_방어:
				if (force.is_player() and 유저_군주_질주혼란_방어)
					return true;
				if (!force.is_player() and AI_군주_질주혼란_방어)
					return true;
				break;
			case 효과_나선첨_방어:
				if (force.is_player() and 유저_군주_나선첨혼란_방어)
					return true;
				if (!force.is_player() and AI_군주_나선첨혼란_방어)
					return true;
				break;
			case 효과_기각_방어:
				if (force.is_player() and 유저_군주_기각혼란_방어)
					return true;
				if (!force.is_player() and AI_군주_기각혼란_방어)
					return true;
				break;
			case 효과_소병력혼란_방어:
				if (force.is_player() and 유저_군주_소병력혼란_방어)
					return true;
				if (!force.is_player() and AI_군주_소병력혼란_방어)
					return true;
				break;
			}


			return false;
		}
		bool kunshuCheck(pk::person@ p)
		{
			pk::force@ force=pk::get_force(p.get_force_id());
			if (force == null)
				return false;

			return force.kunshu == p.get_id();
		}

		bool isKunshu(pk::unit@ u)
		{
			pk::force@ p = pk::get_force(u.get_force_id());
			if (p == null)
				return false;
			pk::person@ kunshu = pk::get_person(p.kunshu);

			return kunshu.get_id() == u.leader;

		}

		bool areaCheck(pk::unit@ u)
		{
			if(u==null)
				return false;
			pk::force@ p = pk::get_force(u.get_force_id());
			if(p==null)
				return false;
			pk::person@ kunshu = pk::get_person(p.kunshu);
			if(kunshu==null)
				return false;

			pk::point pt0 = kunshu.get_pos();
			pk::point pt1 = u.get_pos();
			if (!pk::is_valid_pos(pt0) || !pk::is_valid_pos(pt1))
				return false;

			if (군주_효과_인접무장만_적용)
			{
				return pk::get_distance(pt0, pt1) <= 군주_효과_인접거리;
			}
			else 
			{
				return pk::get_city_id(pt0) == pk::get_city_id(pt1);
			}
		}

		int callback164(pk::unit@ unit)
		{
			int n = prev_callback_164(unit);
			if (forceCheck(unit, 효과_소병력혼란_방어) && isKunshu(unit))
			{
				n = 0;
			}
			return n;
		}

		int callback221(pk::unit@ attacker, pk::unit@ target, bool critical)
		{
			int n = prev_callback_221(attacker, target, critical);
			if (forceCheck(target, 효과_나선첨_방어) && isKunshu(target)) 
			{
				n = 0;
			}
			return n;
		}
		int callback222(pk::unit@ attacker, pk::unit@ target)
		{
			int n = prev_callback_222(attacker, target);
			if (forceCheck(target, 효과_질주_방어) && isKunshu(target))
			{
				n = 0;
			}
			return n;
		}
		int callback223(pk::unit@ attacker, pk::unit@ target)
		{
			int n = prev_callback_223(attacker, target);
			if (forceCheck(target, 효과_기각_방어) && isKunshu(target))
			{
				n = 0;
			}
			return n;
		}



		void callback209(pk::damage_info& info, pk::unit@ attacker, int tactics_id, const pk::point& in target_pos, int type, int critical, bool ambush)
		{
			prev_callback_209(info, attacker, tactics_id, target_pos, type, critical, ambush);
			if(attacker==null)
				return;
			pk::force@ fa = pk::get_force(attacker.get_force_id());
			if(fa==null)
				return;
			pk::person@ akunshu = pk::get_person(fa.kunshu);
			if(akunshu == null)
				return;
			if(!pk::is_valid_pos(attacker.get_pos()) || !pk::is_valid_pos(akunshu.get_pos()))
				return;
			if (forceCheck(fa,효과_공방) && pk::get_city_id(attacker.get_pos()) == pk::get_city_id(akunshu.get_pos()))
			{
				float off = attacker.leader == akunshu.get_id() ? 군주_공격력_효과: 전체_공격력_효과;
				info.troops_damage = info.troops_damage + info.troops_damage * off;
			}

			pk::unit@ target = pk::get_unit(target_pos);
			if (target == null)
				return;

			pk::force@ ft = pk::get_force(target.get_force_id());
			if(ft == null)
				return;
			pk::person@ tkunshu = pk::get_person(ft.kunshu);
			if(tkunshu==null)
				return;
			if(!pk::is_valid_pos(tkunshu.get_pos()) || !pk::is_valid_pos(tkunshu.get_pos()))
				return;

			if (forceCheck(ft, 효과_공방) && pk::get_city_id(target.get_pos()) == pk::get_city_id(tkunshu.get_pos()))
			{
				float off = target.leader == tkunshu.get_id() ? 군주_방어력_효과: 전체_방어력_효과;
				info.troops_damage = info.troops_damage - info.troops_damage * off;
			}

		}

		void callback211(pk::damage_info& info, pk::building@ attacker, pk::hex_object@ target)
		{
			prev_callback_211(info, attacker, target);
			pk::unit@ u = pk::is_valid_pos(target.get_pos()) ? pk::get_unit(target.get_pos()) : null;
			if (u != null)
			{
				pk::force@ ft = pk::get_force(u.get_force_id());
				if (ft == null)
					return;
				pk::person@ tkunshu = pk::get_person(ft.kunshu);
				if (tkunshu == null)
					return;
				if (!pk::is_valid_pos(tkunshu.get_pos()) || !pk::is_valid_pos(tkunshu.get_pos()))
					return;

				if (forceCheck(ft, 효과_공방) && pk::get_city_id(u.get_pos()) == pk::get_city_id(tkunshu.get_pos()))
				{
					float off = u.leader == tkunshu.get_id() ? 군주_방어력_효과 : 전체_방어력_효과;
					info.troops_damage = info.troops_damage - info.troops_damage * off;
				}
			}
		}




		int callback202(pk::unit@ attacker, const pk::point& in pos, pk::hex_object@ target, int tactics_id)
		{
			int n=prev_callback_202(attacker, pos, target, tactics_id);

			if (forceCheck(attacker, 효과_전법) && areaCheck(attacker))
			{
				int amount = isKunshu(attacker) ? 군주_전법_효과 : 전체_전법_효과;
				return pk::min(n + amount,100);
			}
			pk::unit@ u = target;
			if (u!=null && forceCheck(u, 효과_전법) && areaCheck(u))
			{
				int amount = isKunshu(attacker) ? 군주_전법_효과 : 전체_전법_효과;
				return pk::max(n - amount,0);
			}
			return n;
		}

		void callback220(const pk::destroy_info& in info, pk::list<pk::person@>& captured, pk::list<pk::person@>& escaped, bool tactics_bonus)
		{
			prev_callback_220(info, captured, escaped, tactics_bonus);
			if (captured.count == 0) 
			{
				//for (int i = 0; i < escaped.count; i++)
				//{
				//	captured.add(escaped[i]);
				//}
				//while (escaped.count > 0)
				//	escaped.remove_at(0);
				return;
			}
				

			if (!info.releasable)
				return;

			
			int index = -1;
			for (int i = 0; i < captured.count; i++)
			{
				pk::person@ p = captured[i];
				if(!forceCheck(p,효과_포박))
					continue;

				if (kunshuCheck(p)) 
				{
					//pk::printf("escaped kunshu----------------------\n");
					index = i;
					break;
				}
				
			}
			if (index != -1)
				captured.remove_at(index);
		}

		bool callback201(pk::unit@ attacker, pk::hex_object@ target, int tactics_id, bool ranged)
		{
			bool b=prev_callback_201(attacker, target, tactics_id, ranged);
			
			if (forceCheck(attacker, 효과_크리티컬) && areaCheck(attacker) && isKunshu(attacker))
			{
				return true;
			}
				

			pk::unit@ u = target;
			if (u!=null && forceCheck(u, 효과_크리티컬_방어) && areaCheck(u) && isKunshu(u))
			{
				return false;
			}
				

			return b;
		}


		pk::int_bool callback206(pk::unit@ src, const pk::point& in src_pos, const pk::point& in dst_pos, int strategy_id)
		{
			pk::int_bool re = prev_callback_206(src, src_pos, dst_pos, strategy_id);
			if (forceCheck(src, 효과_계략) && areaCheck(src))
			{
				re.first = pk::min(100, re.first + (isKunshu(src) ? 군주_계략_효과 : 전체_계략_효과));
			}

			pk::unit@ target = pk::get_unit(dst_pos);
			if (target!=null && forceCheck(target, 효과_계략) && areaCheck(target))
			{
				re.first = pk::max(0,re.first - (isKunshu(target) ? 군주_계략_효과 : 전체_계략_효과));
			}
			if (target != null && isKunshu(target) && forceCheck(target, 효과_명경) && areaCheck(target) && (strategy_id == 계략_교란 || strategy_id == 계략_위보))
			{
				re.first = 0;
				re.second = true;
			}
			return re;
		}

		int callback207(pk::unit@ src, const pk::point& in src_pos, const pk::point& in dst_pos, int strategy_id)
		{
			int n = prev_callback_207(src, src_pos, dst_pos, strategy_id);
			if (forceCheck(src, 효과_계략_크리티컬) && areaCheck(src))
			{
				n = pk::min(100,n + (isKunshu(src) ? 군주_계략_크리티컬 : 전체_계략_크리티컬));
			}

			pk::unit@ target = pk::get_unit(dst_pos);
			if (target != null && forceCheck(target, 효과_계략) && areaCheck(target))
			{
				n = pk::max(0,n - (isKunshu(src) ? 군주_계략방어_크리티컬 : 전체_계략방어_크리티컬));
			}
			return n;

		}

		int callback203(pk::person@ attacker, pk::person@ target, int tactics_id, bool critical)
		{
			int n = prev_callback_203(attacker, target, tactics_id,critical);
			if (forceCheck(target, 효과_기병전법사망_방어) && target.mibun == 신분_군주) 
			{
				//pk::printf("night attack zero\n");
				n = 0;
			}
				

			return n;

		}



	}
	Main main;
}

