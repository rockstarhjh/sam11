namespace ����_����_����
{
	class Main
	{
		Main()
		{
			pk::set_func(153, pk::func153_t(callback));
		}

		int callback(pk::building@ building, int city_harvest)
		{
			return city_harvest * 0.80f;
		}
	}

	Main main;
}