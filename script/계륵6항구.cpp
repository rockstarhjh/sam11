namespace 계륵6항구
{
	

		
 class Main
 {
		
		Main()
		{
		  pk::bind(107, pk::trigger107_t(QtrAdmin));
                              }
	
	    void QtrAdmin()
	    {
			
	    auto building_list = pk::list_to_array(pk::get_building_list());
			
                  for (int i = 0; i < building_list.length; i++)
                  {
			
		pk::building@ building = building_list[i];	

		if (building.get_force_id() == -1) continue;

                pk::force@ force = pk::get_force(building.get_force_id());

		int force_id = force.get_id();	

		if (!force.is_player() and pk::is_normal_force(force_id))

			징병(building); 


                    }

	     }
		

        //----------------------------------------------------------------------------------
        // 징병 
        //----------------------------------------------------------------------------------


		void 징병(pk::building@ building)
               {


                         int base_id = building.get_id();



                     if (건물_파양항 == base_id or 건물_노릉항 == base_id or 건물_서하항 == base_id or 건물_하양항 == base_id or 건물_해현항 == base_id or 건물_강도항 == base_id)

                          {

                         if ( pk::get_troops(building) <  5000)

                              {

			      pk::add_troops(building, 1000 , true);

		              } 


                         if ( pk::get_gold(building) <  2000)

                              {

			    pk::add_gold(building, 500, true);

		              } 


                         if ( pk::get_food(building) <  10000)

                              {
			    pk::add_food(building, 2000 , true);

		              }

	                  }
						
		} 

            		
	} 

	Main main;
	
} // namespace