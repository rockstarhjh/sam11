namespace 특기_업화
{

	array<int> 특기부여_목록 =
	{
		무장_육손
	};

	const int 특기_업화 = 241;  // 웬만하면 수정 X
   
	class Main
	{	
		pk::func206_t@ prev_callback_206;
		pk::func214_t@ prev_callback_214;

		Main()
		{
			pk::bind(102, pk::trigger102_t(SetSkill));
			
			@prev_callback_206 = cast<pk::func206_t@>(pk::get_func(206));
			pk::reset_func(206);			
			pk::set_func(206, pk::func206_t(func206));

			@prev_callback_214 = cast<pk::func214_t@>(pk::get_func(214));
			pk::reset_func(214);			
			pk::set_func(214, pk::func214_t(func214));
		}

		void SetSkill()
		{
			pk::get_skill(특기_업화).name = pk::u8encode("업화");
			pk::get_skill(특기_업화).desc = pk::u8encode("숲에 있는 적부대에 반드시 화계 성공. 적부대를 혼란시킨다.");
			pk::get_skill(특기_업화).type = 특기종류_계략;
			

			if (특기부여_목록.length != 0)
			{
				for (int i = 0; i < 특기부여_목록.length; ++i)
				{
					특기부여(pk::get_person(특기부여_목록[i]));
				}
			}
		}

		void 특기부여(pk::person @p)
		{
			p.skill = 특기_업화;
		}
///////////////////////////////////////////계략 성공률
		pk::int_bool func206(pk::unit@ src, const pk::point &in src_pos, const pk::point &in dst_pos, int strategy_id)
		{
			pk::unit@ dst = pk::get_unit(dst_pos);

			if (dst !is null and src.has_skill(특기_업화) and strategy_id == 계략_화계)
			{
				if (dst.has_skill(특기_신산)) return pk::int_bool(0, true);
				if (dst.has_skill(특기_통찰)) return pk::int_bool(0, true);
				if (pk::get_hex(dst.get_pos()).terrain == 지형_숲) return pk::int_bool(100, false);
			}
		
			return prev_callback_206(src, src_pos, dst_pos, strategy_id);
		}
///////////////////////////////////////////화계 데미지
		void func214(pk::damage_info& info, pk::unit@ attacker, pk::hex_object@ target, bool critical)
		{
			
			if (target !is null and attacker.has_skill(특기_업화) and pk::is_enemy(attacker, target) and pk::get_hex(target.get_pos()).terrain == 지형_숲)
				pk::set_status(target, attacker, 부대상태_혼란, 1, true);

			if (prev_callback_214 !is null)
				prev_callback_214(info, attacker, target, critical);
		}
	}

	Main main;
}