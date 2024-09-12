namespace 항장공적감소
{
	class Main
	{
		Main()
		{
			pk::bind(152, pk::trigger152_t(change_force));
		}

		void change_force(pk::person@ person, pk::force@ force)
		{
			person.kouseki /= 2;
		}
	}
	Main main;
}