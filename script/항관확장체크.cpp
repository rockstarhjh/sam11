namespace 항관확장체크
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
				if (!force.is_player() and pk::is_normal_force(force) and !pk::has_tech(force, 기교_항관확장))


                                force.tech[기교_항관확장] = true;


                                force.update();

			} 




			
		} //callback


		void callback2(pk::force@ force)
		{	

						
			auto force_list = pk::list_to_array(pk::get_force_list());		
			for (int i = 0; i < force_list.length; i++)
			{
				pk::force@ force = force_list[i];
				if (!force.is_player() and pk::is_normal_force(force) and !pk::has_tech(force, 기교_항관확장))


                                force.tech[기교_항관확장] = true;


                                force.update();

			} 




			
		} //callback2
		
	} // class Main

	Main main;
}