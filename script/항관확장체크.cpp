namespace �װ�Ȯ��üũ
{

	class Main
	{
		

				
		Main()
		{
			pk::bind(103, pk::trigger103_t(callback));
			pk::bind(112, pk::trigger112_t(callback2));
		}
		
		void callback()
		{	
			if (pk::get_scenario().loaded) return;
			
			
			auto force_list = pk::list_to_array(pk::get_force_list());		
			for (int i = 0; i < force_list.length; i++)
			{
				pk::force@ force = force_list[i];
				if (!force.is_player() and pk::is_normal_force(force) and !pk::has_tech(force, �ⱳ_�װ�Ȯ��))


                                force.tech[�ⱳ_�װ�Ȯ��] = true;


                                force.update();

			} 




			
		} //callback


		void callback2(pk::force@ force)
		{	

						
			auto force_list = pk::list_to_array(pk::get_force_list());		
			for (int i = 0; i < force_list.length; i++)
			{
				pk::force@ force = force_list[i];
				if (!force.is_player() and pk::is_normal_force(force) and !pk::has_tech(force, �ⱳ_�װ�Ȯ��))


                                force.tech[�ⱳ_�װ�Ȯ��] = true;


                                force.update();

			} 




			
		} //callback2
		
	} // class Main

	Main main;
}