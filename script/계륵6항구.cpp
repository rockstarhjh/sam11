namespace �踤6�ױ�
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

			¡��(building); 


                    }

	     }
		

        //----------------------------------------------------------------------------------
        // ¡�� 
        //----------------------------------------------------------------------------------


		void ¡��(pk::building@ building)
               {


                         int base_id = building.get_id();



                     if (�ǹ�_�ľ��� == base_id or �ǹ�_�븪�� == base_id or �ǹ�_������ == base_id or �ǹ�_�Ͼ��� == base_id or �ǹ�_������ == base_id or �ǹ�_������ == base_id)

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