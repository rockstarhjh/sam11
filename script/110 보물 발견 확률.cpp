namespace 보물_발견_확률
{
	class Main
	{
		Main()
		{
			pk::set_func(110, pk::func110_t(callback));
		}

		int callback(pk::building@ building, pk::person@ actor, pk::item@ item)
		{
			// 강탈이 5% 확률로 아이템 발견
			if (pk::has_skill(actor, 특기_강탈))
				return 5;
			return pk::max((61 - item.value) / 20, 1);
		}
	}

	Main main;
}