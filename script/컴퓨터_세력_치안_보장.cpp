namespace ��ǻ��_����_ġ��_����
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


			ġ��(building); 	


                    }

	     }
		

        //----------------------------------------------------------------------------------
        // ��ǻ�� ���� ġ���� 100���Ϸ� �������� �ڵ� ġ�� ����
        //----------------------------------------------------------------------------------


		void ġ��(pk::building@ building)
               {
                    pk::city@ city = pk::building_to_city(building); 				
                    pk::person@ taishu = pk::get_person(pk::get_taishu_id(building));	
	            pk::person@ kunshu = pk::get_person(pk::get_kunshu_id(building));	

                    int force_id = building.get_force_id();           

 if (pk::is_alive(building) and pk::is_normal_force(force_id) and building.get_force_id() != -1 and �ǹ�_���ý��� <= building.get_id() and building.get_id() < �ǹ�_���ó� )
			{



			   pk::add_public_order(city, 100, true);
			   pk::add_energy(city, 120, true);			   


                        }

						
		} 



           


		
	} 

	Main main;
	
} // namespace