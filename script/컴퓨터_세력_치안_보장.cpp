namespace 컴퓨터_세력_치안_보장
{
			
 class Main
 {
		
		Main()
		{
		  pk::bind(107, pk::trigger107_t(auto_order));
                }
	
	    void auto_order()
	    {
			
	    auto building_list = pk::list_to_array(pk::get_building_list());
			
                  for (int i = 0; i < building_list.length; i++)
                  {
			
		pk::building@ building = building_list[i];



		if (building.get_force_id() == -1) continue;

                pk::force@ force = pk::get_force(building.get_force_id());

		int force_id = force.get_id();	

		if (!force.is_player() and pk::is_normal_force(force_id))


			치안(building); 	


                    }

	     }
		

        //----------------------------------------------------------------------------------
        // 컴퓨터 세력 치안이 100이하로 떨어져도 자동 치안 유지
        //----------------------------------------------------------------------------------


		void 치안(pk::building@ building)
               {
                    pk::city@ city = pk::building_to_city(building); 				
                    pk::person@ taishu = pk::get_person(pk::get_taishu_id(building));	
	            pk::person@ kunshu = pk::get_person(pk::get_kunshu_id(building));	

                    int force_id = building.get_force_id();           

 if (pk::is_alive(building) and pk::is_normal_force(force_id) and building.get_force_id() != -1 and 건물_도시시작 <= building.get_id() and building.get_id() < 건물_도시끝 )
			{



			   pk::add_public_order(city, 100, true);
			   pk::add_energy(city, 120, true);			   


                        }

						
		} 



           


		
	} 

	Main main;
	
} // namespace