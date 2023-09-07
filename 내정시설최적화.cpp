/*
// ������: �⸶å��
// Update: '18.12.7    / ��������: ���Խü�_�����Ǽ�(���� �ֺ� ������ ��������, ��â �ֺ� ������ �������� ����)
// Update: '19.1.5     / ���泻��: ���Խü�_��ġ�̵�(�ָ� ������ ����/������ ����/��â �ֺ��� �����ü��� ��ġ ����), ���Խü�_�����(����/��â ��ġ�� �߸� ������ �ü� �����)
// Update: '19.1.9     / ���泻��: ���Խü�_��ġ�̵� ���� ���� (���г�, �뵵�� �� �߰�)
// Update: '19.1.30    / ���泻��: ���๫�� �̸� ���� ���� ����
// Update: '19.2.25    / ���泻��: �����_���¼��� �ɼ� ����/��ũ��Ʈ ����ġ ����, �����Ǽ� �� ��ġ�̵� �˰��� ���¼��� �ɼ� �߰�
// Update: '19.11.25   / ���泻��: ����� ���๫�� ���� �˰��� ����
// Update: '20.8.24    / ���泻��: core2.dll �Ź��� ���� �� ���Խü�_��ġ�̵� ��� ���� ����
// Update: '20.9.20    / ���泻��: ���Խü�_��ġ�̵� ���� ���� (���۴�, ����, ����, ����ü�3�� �߰�), ����/��â ����� ���� ����
*/

namespace �����ü�����ȭ
{
    //---------------------------------------------------------------------------------------
    // ���� ���� (true = on, false = off)
    const bool ���Խü�_�����Ǽ� = true;     // ����/����/����/��â ����� ���� ('18.12.7)
    const int  �����Ǽ�_���¼��� = 0;        // 0: ��� ����, 1: AI���¸� ����, 2: Player���� ��ü����, 3: Player_1���ܸ� ����
    
    const bool ���Խü�_��ġ�̵� = true;    // �ָ� ������ ����/������ ����/��â �ֺ��� �����ü��� ��ġ ����
    const int  ��ġ�̵�_���¼��� = 0;       // 0: ��� ����, 1: AI���¸� ����, 2: Player���� ��ü����, 3: Player_1���ܸ� ����
    
    //---------------------------------------------------------------------------------------
    const bool ���Խü�_����� = true;     // �߸� ������ ��ġ�� ����/��â �ٽ����� ('19.1.4)
    const bool �����_����Ȯ�� = true;
    const int  �����_���ص��ñ� = 500;
    const int  �����_���¼��� = 0;        // 0: ��� ����, 1: AI���¸� ����, 2: Player���� ��ü����, 3: Player_1���ܸ� ����
    
    //---------------------------------------------------------------------------------------
    
	class Main
	{
        
        Main()
		{
            pk::bind(111, pk::trigger111_t(onTurnStart));
            pk::bind(112, pk::trigger112_t(onTurnEnd));
        }
        
        void onTurnStart(pk::force@ force)
        {
            if (pk::is_campaign()) return;
            
            if (���Խü�_�����Ǽ�)
                optimize_force_city_facility(force);    // ���԰��� �����ü� �Ǽ� ����ȭ
        }
        
        
        void onTurnEnd(pk::force@ force)
        {
            if (pk::is_campaign()) return;
            
            if (���Խü�_��ġ�̵� or ���Խü�_�����)
                rebuild_force_city_facility(force);     // �ü� ��ġ ���� �Ǵ� ����� ����
        }
        
        //---------------------------------------------------------------------------------------
        
        // ���� ���� �ɼ�
        bool check_force_option(pk::force@ force, bool enable, int option)
        {
            if (!enable) return false;
            
            // ���¼��� = 0: ��� ����, 1: AI���¸� ����, 2: Player���� ��ü����, 3: Player_1���ܸ� ����
            if (option == 0) return true;
            if (option == 1 and !force.is_player()) return true;
            if (option == 2 and force.is_player())  return true;
            if (option == 3 and pk::is_player_controlled(force)) return true;

            return false;
        }
        
        //---------------------------------------------------------------------------------------
        // ���Խü� ����ȭ
        //---------------------------------------------------------------------------------------
        
        // ������ ����
        void optimize_force_city_facility(pk::force@ force)
        {
            // ������ ���� ����Ʈ
            pk::array<pk::city@> arr_city_list = pk::list_to_array(pk::get_city_list(force));
            for (int i = 0; i < int(arr_city_list.length); i++)
            {
                if (check_force_option(force, ���Խü�_�����Ǽ�, �����Ǽ�_���¼���))
                    optimize_city_facility(arr_city_list[i]);
            }
        }
        
        // ���ú� �����ü� �˻� �� ����ȭ
        void optimize_city_facility(pk::city@ city)
        {
            int force_id = city.get_force_id();
            if (city is null or !pk::is_valid_force_id(force_id))
                return ;
            
            int sum_facility_hp = 0;
            for (int i = 0; i < int(city.max_devs); i++)
            {
                pk::building@ building = city.dev[i].building;
                if (pk::is_alive(building))
                {
                    int facility_id = building.facility;
                    
                    // �̿ϼ� ����/��â (���Խü� ����ȭ)
                    if (!building.completed and (facility_id == �ü�_��â or facility_id == �ü�_����))
                    {
                        change_center_facility(building);   // �ֺ��� ����/���� ���ؼ� �Ǵ��Ͽ� ���� 
                    }
                    
                    // �ϼ��� ����/��â �ֺ� (���Խü� ����ȭ)
                    if (building.completed and (facility_id == �ü�_��â or facility_id == �ü�_����))
                    {
                        change_yield_facility(building);    // �̿ϼ� �ֺ� ����/���� ���� ����ȭ
                        change_assist_facility(building);   // �̿ϼ� �ֺ� �����ü��� ����/�������� ����
                    }
                    
                }
            }
        }
        
        
        //---------------------------------------------------------------------------------------
        
        // �̿ϼ� �ֺ� ����ü� ����
        void change_yield_facility(pk::building@ building)
        {
            if (!pk::is_alive(building)) return;
            if (!building.completed) return;
            
            int facility_id = building.facility;
            
            // �ϼ��� ��â �ֺ� �ü� �˻�
            if (facility_id == �ü�_��â)
            {
                for (int i = 0; i < ����_��; i++)
                {
                    pk::point neighbor_pos = pk::get_neighbor_pos(building.pos, i);
                    if (pk::is_valid_pos(neighbor_pos))
                    {
                        pk::building@ target_building = pk::get_building(neighbor_pos);
                        // �̿ϼ� �ֺ� ������ �������� ����
                        if (pk::is_alive(target_building) and !target_building.completed and target_building.facility == �ü�_����)
                        {
                            int count_neighbor = count_neighbor_facility(target_building, �ü�_����)
                                               + count_neighbor_facility(target_building, �ü�_����2��)
                                               + count_neighbor_facility(target_building, �ü�_����3��);
                                               
                            if (count_neighbor <= 3)
                            {
                                target_building.facility = �ü�_����;
                                target_building.update();
                            }
                        }                            
                    }
                }
            }
            
            // �ϼ��� ���� �ֺ� �ü� �˻�
            if (facility_id == �ü�_����)
            {
                for (int i = 0; i < ����_��; i++)
                {
                    pk::point neighbor_pos = pk::get_neighbor_pos(building.pos, i);
                    if (pk::is_valid_pos(neighbor_pos))
                    {
                        pk::building@ target_building = pk::get_building(neighbor_pos);
                        
                        // �̿ϼ� �ֺ� ������ �������� ����
                        if (pk::is_alive(target_building) and !target_building.completed and target_building.facility == �ü�_����)
                        {   
                            int count_neighbor = count_neighbor_facility(target_building, �ü�_����) 
                                               + count_neighbor_facility(target_building, �ü�_����2��) 
                                               + count_neighbor_facility(target_building, �ü�_����3��);       
                                               
                            if (count_neighbor <= 3)
                            {         
                                target_building.facility = �ü�_����;
                                target_building.update();
                            }
                        }
                    }
                }
            }
            
        }
        
        //---------------------------------------------------------------------------------------
        
        // �ش�ǹ� ������ Ȯ���ϰ��� �ϴ� �ü� ���� ī��Ʈ
        int count_neighbor_facility(pk::building@ building, int facility_id)
        {
            int count_facility = 0;
            
            for (int j = 0; j < ����_��; j++)
            {
                pk::point neighbor_pos = pk::get_neighbor_pos(building.pos, j);
                if (pk::is_valid_pos(neighbor_pos))
                {
                    pk::building@ neighbor_building = pk::get_building(neighbor_pos);
                    if (pk::is_alive(neighbor_building) and neighbor_building.facility == facility_id)
                        count_facility += 1;
                }
            }
            
            return count_facility;
        }
        
        //---------------------------------------------------------------------------------------
        
        // �̿ϼ� �ֺ� �����ü� ����
        void change_assist_facility(pk::building@ building)
        {
            if (!pk::is_alive(building)) return;
            if (!building.completed) return;
            
            int facility_id = building.facility;
            
            // �ϼ��� ����/��â �ֺ��� ���� �˻�
            if (facility_id == �ü�_���� or facility_id == �ü�_��â)
            {
                int count_valid_pos = 0;
                int count_completed = 0;
                int count_uncompleted = 0;
                for (int i = 0; i < ����_��; i++)
                {
                    pk::point neighbor_pos = pk::get_neighbor_pos(building.pos, i);
                    if (pk::is_valid_pos(neighbor_pos))
                    {
                        count_valid_pos += 1;
                        
                        pk::building@ target_building = pk::get_building(neighbor_pos);
                        if (pk::is_alive(target_building) and �ü�_������ <= target_building.facility and target_building.facility <= �ü�_������)
                        {
                            // �ֺ� �����ü� �� (�ϼ�, �̿ϼ�)
                            if (target_building.completed)
                                count_completed  += 1;
                            else
                                count_uncompleted += 1;
                                       
                        }                            
                    }
                }
                
                // ����/��â �ֺ��� �����ü��� �����ϰ� ���� ���, �̿ϼ� �����ü��� ����/�������� ����
                if ((count_completed + count_uncompleted) >= int((count_valid_pos + 1)/3))
                {
                    for (int i = 0; i < ����_��; i++)
                    {
                        pk::point neighbor_pos = pk::get_neighbor_pos(building.pos, i);
                        if (pk::is_valid_pos(neighbor_pos))
                        {
                            pk::building@ target_building = pk::get_building(neighbor_pos);
                            if (pk::is_alive(target_building) and !target_building.completed and �ü�_������ <= target_building.facility and target_building.facility <= �ü�_������)
                            {
                                if (facility_id == �ü�_����)
                                    target_building.facility = �ü�_����;
                                if (facility_id == �ü�_��â)
                                    target_building.facility = �ü�_����;
                            }                            
                        }
                    }
                    
                }
            }
            
        }
        
        //---------------------------------------------------------------------------------------
        
        // �̿ϼ� �߾� �ü� ����
        void change_center_facility(pk::building@ building)
        {
            if (!pk::is_alive(building)) return;
            if (building.completed) return;
            
            int facility_id = building.facility;
            
            float count_ref = 3.0f;
            
            // �̿ϼ� ����/��â �ֺ��� ���� �˻�
            if (facility_id == �ü�_���� or facility_id == �ü�_��â)
            {
                float count_farm   = 0.f;
                float count_market = 0.f;
                for (int i = 0; i < ����_��; i++)
                {
                    pk::point neighbor_pos = pk::get_neighbor_pos(building.pos, i);
                    if (pk::is_valid_pos(neighbor_pos))
                    {
                        pk::building@ target_building = pk::get_building(neighbor_pos);
                        if (pk::is_alive(target_building))
                        {
                            // �ֺ� ����, ����2��, ����3�� �˻�
                            if (target_building.facility == �ü�_���� and target_building.completed)
                                count_farm += 1.0f;
                            if (target_building.facility == �ü�_����2��)
                                count_farm += 1.25f;
                            if (target_building.facility == �ü�_����3��)
                                count_farm += 1.5f;
                            
                            // �ֺ� ����, ����2��, ����3�� �˻�
                            if (target_building.facility == �ü�_���� and target_building.completed)
                                count_market += 1.0f;
                            if (target_building.facility == �ü�_����2��)
                                count_market += 1.25f;
                            if (target_building.facility == �ü�_����3��)
                                count_market += 1.5f;
                        }
                    }
                }
                // ���� ���� �� ���� �� ���� �� ��â �ü� ����
                if (facility_id == �ü�_���� and count_farm >= count_ref and count_farm > count_market)
                {
                    building.facility = �ü�_��â;   
                    building.update();
                }
                
                // ���� ���� �� ���� �� ��â �� ���� �ü� ����
                if (facility_id == �ü�_��â and count_market >= count_ref and count_market > count_farm)
                {
                    building.facility = �ü�_����;   
                    building.update();
                }
            }
            
        }
        
        
        //---------------------------------------------------------------------------------------
        // ���Խü�_��ġ�̵� / ���Խü�_�����
        //---------------------------------------------------------------------------------------
        
        
        // ������ ����
        void rebuild_force_city_facility(pk::force@ force)
        {
            // ������ ���� ����Ʈ
            pk::array<pk::city@> arr_city_list = pk::list_to_array(pk::get_city_list(force));
            for (int i = 0; i < int(arr_city_list.length); i++)
            {
                if (check_force_option(force, ���Խü�_��ġ�̵�, ��ġ�̵�_���¼���))
                    swap_city_facility(arr_city_list[i]);
                
                if (check_force_option(force, ���Խü�_�����, �����_���¼���))
                    rebuild_city_facility(arr_city_list[i]);
            }
        }
        
        // ���� �� �ϼ��� ����ü�/�����ü� ��ġ ���� 
        void swap_city_facility(pk::city@ city)
        {
            int force_id = city.get_force_id();
            if (city is null or !pk::is_valid_force_id(force_id))
                return ;
            
            if (!check_city_dev_complete(city)) return;   // ������ Ȯ��
            
            // �ϼ��� ����ü�/�����ü� �� ��ġ ���� ���� 
            swap_yield_facility(city);
                
            
        }
        
        // ���ú� ����� Ȯ�� �� ����
        void rebuild_city_facility(pk::city@ city)
        {
            int force_id = city.get_force_id();
            if (city is null or !pk::is_valid_force_id(force_id))
                return ;
            
            if (!check_city_dev_complete(city)) return;   // ������ Ȯ��
            if (city.max_devs <= 10) return;        // ������ ���� �ؼ� ���� ����
            
            // �ൿ�� �� ���ñ� ���� Ȯ��
            if (int(pk::get_district(city.get_district_id()).ap) > �����_�����ൿ�� and int(city.gold) > �����_���ص��ñ�)
            {
                for (int i = 0; i < int(city.max_devs); i++)
                {
                    pk::building@ building = city.dev[i].building;
                    if (pk::is_alive(building))
                    {
                        rebuild_center_facility(city, building);
                    }
                }
            } 
        }
        
        //---------------------------------------------------------------------------------------
        // ���Խü� ��ġ�̵� (�ָ� ������ ����/������ ����/��â �ֺ��� �����ü��� ��ġ ����)

        // ������ �ü� swapping
        void swap_yield_facility(pk::city@ city)
        {
            if (!pk::is_alive(city)) return;
            
            pk::building@ src_building;
            pk::building@ dst_building;
            int force_id = city.get_force_id();
            
            if (pk::has_facility(city, �ü�_����) and get_facility_count(city, �ü�_����3��) >= 2)
            {
                get_neighbor_assist_facility(city, �ü�_����, dst_building);
                if (pk::is_alive(dst_building))
                {
                    get_isolated_yield_facility(city, �ü�_����3��, �ü�_����, src_building);
                    get_neighbor_assist_facility(city, �ü�_����, dst_building);
                    swap_facility(src_building, dst_building, force_id);    // �ǹ� SWAP
                    
                    get_isolated_yield_facility(city, �ü�_����2��, �ü�_����, src_building);
                    get_neighbor_assist_facility(city, �ü�_����, dst_building);
                    swap_facility(src_building, dst_building, force_id);    // �ǹ� SWAP
                    
                    get_isolated_yield_facility(city, �ü�_����, �ü�_����, src_building);
                    get_neighbor_assist_facility(city, �ü�_����, dst_building);
                    swap_facility(src_building, dst_building, force_id);    // �ǹ� SWAP
                }
            }
            
            if (pk::has_facility(city, �ü�_��â) and get_facility_count(city, �ü�_����3��) >= 2)
            {
                get_neighbor_assist_facility(city, �ü�_��â, dst_building);
                if (pk::is_alive(dst_building))
                {
                    get_isolated_yield_facility(city, �ü�_����3��, �ü�_��â, src_building);
                    get_neighbor_assist_facility(city, �ü�_��â, dst_building);
                    swap_facility(src_building, dst_building, force_id);    // �ǹ� SWAP
                
                    get_isolated_yield_facility(city, �ü�_����2��, �ü�_��â, src_building);
                    get_neighbor_assist_facility(city, �ü�_��â, dst_building);
                    swap_facility(src_building, dst_building, force_id);    // �ǹ� SWAP
                
                    get_isolated_yield_facility(city, �ü�_����, �ü�_��â, src_building);
                    get_neighbor_assist_facility(city, �ü�_��â, dst_building);
                    swap_facility(src_building, dst_building, force_id);    // �ǹ� SWAP
                }
            }
        }
        
        // ���� ���Խü� �˻�
        void get_isolated_yield_facility(pk::city@ city, int facility_id, int neighbor_id, pk::building@ &out src_building)
        {
            if (!pk::is_alive(city)) return;
            
            @src_building = null;
            for (int i = 0; i < int(city.max_devs); i++)
            {
                pk::building@ building = city.dev[i].building;
                if (pk::is_alive(building))
                {
                    if (building.facility == facility_id and building.completed and count_neighbor_facility(building, neighbor_id) == 0)
                    {
                        @src_building = @building;
                        return;
                    }
                }
            }
        }
        
        // ������ �����ü� �˻�
        void get_neighbor_assist_facility(pk::city@ city, int facility_id, pk::building@ &out dst_building)
        {
            if (!pk::is_alive(city)) return;
            
            @dst_building = null;
            for (int i = 0; i < int(city.max_devs); i++)
            {
                pk::building@ building = city.dev[i].building;
                if (pk::is_alive(building) and building.facility == facility_id)
                {
                    // ������ ���� �ü� �˻�
                    for (int j = 0; j < ����_��; j++)
                    {
                        pk::point neighbor_pos = pk::get_neighbor_pos(building.pos, j);
                        if (pk::is_valid_pos(neighbor_pos))
                        {
                            pk::building@ building_t = pk::get_building(neighbor_pos);
                            if (pk::is_alive(building_t) and building_t.completed 
                                and ((�ü�_������ <= building_t.facility and building_t.facility <= �ü�_���г�) or building_t.facility == �ü�_���۴�
                                      or building_t.facility == �ü�_���� or building_t.facility <= �ü�_����
                                      or building_t.facility == �ü�_����3�� or building_t.facility == �ü�_���尣3�� or building_t.facility == �ü�_������3��) )
                            {
                                /*
                                @dst_building = @building_t;
                                return;
                                */
                                
                                // '20.8.24, �߰�
                                for (int k = 0; k < int(city.max_devs); k++)    
                                {
                                    pk::building@ building_k = city.dev[k].building;
                                    if (pk::is_alive(building_k))
                                    {
                                        if (building_t.get_id() == building_k.get_id())
                                        {
                                            @dst_building = @building_t;
                                            return;
                                        }
                                    }
                                }
                                
                            }                            
                        }
                    }
                }
            }  
        }
        
        // �ü� swapping �Լ�
        void swap_facility(pk::building@ src_building, pk::building@ dst_building, int force_id)
        {
            if (!pk::is_valid_force_id(force_id)) return ;
            if (!pk::is_alive(src_building)) return ;
            if (!pk::is_alive(dst_building)) return ;
            
            int src_id  = src_building.facility;
            int dst_id  = dst_building.facility;
            pk::point src_pos = src_building.pos;
            pk::point dst_pos = dst_building.pos;
            int src_hp  = src_building.hp;
            int dst_hp  = dst_building.hp;
            
            // �Ź��� core2.dll �����߻����� ���� �ü� ���� ('20.8.24)
            pk::kill(src_building, false);
            pk::kill(dst_building, false);
            
            pk::create_building(pk::get_facility(src_id), dst_pos, force_id);
            pk::building@ new_src = pk::get_building(dst_pos);
            pk::complete(new_src);
            new_src.hp = src_hp;    // �ǹ� ������ �缳�� �߰� ('20.9.20)
            new_src.update();
            
            pk::create_building(pk::get_facility(dst_id), src_pos, force_id);
            pk::building@ new_dst = pk::get_building(src_pos);
            pk::complete(new_dst);
            new_dst.hp = dst_hp;    // �ǹ� ������ �缳�� �߰� ('20.9.20)
            new_dst.update();
        }
        
        
        
        //---------------------------------------------------------------------------------------
        // ����/��â ��ġ �߸� ������ ��� �ٽ� ����
        
        int �����_�����ൿ�� = 30;     // ��������!!
        int answer = 0;     // 0:��,  1:�ƴϿ�,  2:��(���),  3:�ƴϿ�(���)
        
        
        // �߾ӽü� ��ġ�� �����
        void rebuild_center_facility(pk::city@ city, pk::building@ building)
        {
            if (!pk::is_alive(building)) return;
            
            int count_neighbor = 0; 
            int facility_id = building.facility;
            
            // ���� �ȿ� ����/���� �ƴϸ� �ٽ� ����
            if (!pk::has_facility(city, �ü�_����))
            {
                count_neighbor = count_neighbor_facility(building, �ü�_����) + count_neighbor_facility(building, �ü�_����2��) + count_neighbor_facility(building, �ü�_����3��);
                if (count_neighbor >= 3 and facility_id != �ü�_���� and facility_id != �ü�_����2�� and facility_id != �ü�_����3�� and facility_id != �ü�_����)
                {
                    rebuild_facility(city, building, �ü�_����);    // ����� �����
                }
            }
            
            // ���� �ȿ� ����/��â�� �ƴϸ� �ٽ� ����
            if (!pk::has_facility(city, �ü�_��â))
            {
                count_neighbor = count_neighbor_facility(building, �ü�_����) + count_neighbor_facility(building, �ü�_����2��) + count_neighbor_facility(building, �ü�_����3��);
                if (count_neighbor >= 3 and facility_id != �ü�_���� and facility_id != �ü�_����2�� and facility_id != �ü�_����3�� and facility_id != �ü�_��â)
                {
                    rebuild_facility(city, building, �ü�_��â);    // ��â���� �����
                }
            }            
        }
        
        //---------------------------------------------------------------------------------------
        
        // �ü� ����� ���� Ȯ�� �� ����
        void rebuild_facility(pk::city@ city, pk::building@ building, int rebuild_id)
        {
            // �ൿ�� Ȯ���� ���� ���� ���� ��ȯ
            pk::district@ district = pk::get_district(city.get_district_id());
            
            // ���డ�� ���� Ȯ��
            pk::list<pk::person@> list_idle_person = pk::get_idle_person_list(pk::city_to_building(city));
            if (list_idle_person.count == 0) return;
            
            // ��ġ���� ���� ������ ����
            list_idle_person.sort(function(a, b)
            {
                return a.stat[����ɷ�_��ġ] > b.stat[����ɷ�_��ġ];
            } );
            
            // �ü� ������
            float hp_delta = float(int(pk::get_facility(rebuild_id).hp));
            
            // ���� �۾��ϼ� �� �ּҴɷ�ġ ���
            pk::array<pk::person@> arr_idle_person = pk::list_to_array(list_idle_person);
            int min_actors = pk::min(3, pk::max(1, int(arr_idle_person.length)/2));     // �����ο� �ڵ�����
            float max_stat = 0.0f;
            for (int i = 0; i < min_actors; i++)    //�ִ밡�� �ɷ�ġ�ջ�
            {
                float stat_weight;
                if (i == 0) stat_weight = 1.5f;
                else        stat_weight = 0.5f;
                max_stat += float(arr_idle_person[i].stat[����ɷ�_��ġ]) * stat_weight;  
            }
            int   ref_per = int(hp_delta / max_stat) + (((hp_delta % max_stat) > 0)? 1 : 0); // �Ǽ��Ⱓ ���� (�ø�)
            float ref_stat = hp_delta / float(ref_per);                                      // ���� �ջ�ɷ�ġ
            
            
            // �����ο� ���๫�� �ڵ�����
            pk::list<pk::person@> person_sel;
            float sum_stat = 0.0f;
            for (int i = 0; i < min_actors; i++)
            {   
                float stat_weight;
                if (i == 0) stat_weight = 1.5f;
                else        stat_weight = 0.5f;     
                
                pk::person@ actor_t;
                for (int j = (int(arr_idle_person.length) - 1); j >= 0; j--)
                {
                    if (!person_sel.contains(arr_idle_person[j]))
                    {
                        @actor_t = arr_idle_person[j];
                        if ((float(actor_t.stat[����ɷ�_��ġ]) * stat_weight + sum_stat) > ref_stat) break;
                    }
                }
                if (pk::is_alive(actor_t))
                {
                    person_sel.add(actor_t);
                    sum_stat += actor_t.stat[����ɷ�_��ġ] * stat_weight;
                }
                if (sum_stat > ref_stat) break;
            }
            pk::array<pk::person@> actors = pk::list_to_array(person_sel);
            
            // �� �Һ� �� (ö�ŵ� �ǹ���� ��ȯ �� ����� ���)
            int gold_cost = int(pk::get_facility(rebuild_id).gold_cost) - int(pk::get_facility(building.facility).gold_cost);
            
            // ���� Ȯ�� �� ����� ����
            if (int(district.ap) >= �����_�����ൿ�� and pk::is_alive(actors[0]) and int(sum_stat) >= 70 and int(city.gold) > pk::max(gold_cost, �����_���ص��ñ�))
            {
                if (pk::is_player_controlled(city) and �����_����Ȯ�� and answer <= 1)
                {
                    @building_t = @building;
                    pk::scene(pk::scene_t(goto_facility));
                    
                    pk::person@ kunshu = pk::get_person(pk::get_kunshu_id(city));
                    string actor_name;
                    for (int i = 0; i < int(actors.length); i++)
                    {
                        pk::person@ actor_t = actors[i];
                        if (i == 0) actor_name = pk::decode(pk::get_name(actor_t));
                        else        actor_name = actor_name + ", " + pk::decode(pk::get_name(actor_t));
                    }
                    string city_name = pk::decode(pk::get_name(city));
                    string facility_name1 = pk::decode(pk::get_facility(building.facility).name);
                    string facility_name2 = pk::decode(pk::get_facility(rebuild_id).name);
                    
                    answer = pk::choose({ pk::encode("��"), pk::encode("�ƴϿ�"), pk::encode("��(���)"), pk::encode("�ƴϿ�(���)") }, 
                                          pk::encode(pk::format("\x1b[1x{}\x1b[0x���� \x1b[1x{}\x1b[0x�� \x1b[1x{}\x1b[0x�� \x1b[1x{}\x1b[0x���� ����� ��Ű�ڽ��ϱ�?\n (�� {} �Ҹ�)", actor_name, city_name, facility_name1, facility_name2, gold_cost)), 
                                          kunshu );
                    
                    pk::scene(pk::scene_t(remove_highlights));
                }
                
                // ����� ����
                if ((pk::is_player_controlled(city) and (answer == 0 or answer == 2)) or !pk::is_player_controlled(city))
                {
                    // �ٽ� ���� �ǹ��� �ʼ��ü��̸� �Ǽ��� �߰�Ȯ��
                    if (check_essential_facility(building.facility))
                        remove_assist_facility(city, building);   
                    
                    // ����� ���� �Լ�
                    rebuild_command(city, building, actors, rebuild_id);
                
                    // ö�ŵ� �ǹ���� ��ȯ �� ����� ��� ����
                    pk::add_gold(city, -gold_cost, true);
                }
            }
        }
        
        //---------------------------------------------------------------------------------------
        
        // ����� ���� �Լ�
        void rebuild_command(pk::city@ city, pk::building@ building, pk::array<pk::person@> actors, int rebuild_id)
        {
            // ��������
            pk::develop_cmd_info cmd_develop;
            @cmd_develop.base = pk::city_to_building(city);
            for(int i = 0; i < int(actors.length); i++)
            {
                @cmd_develop.actors[i] = actors[i];
            }
            cmd_develop.facility = rebuild_id;
            cmd_develop.pos = building.pos;
            
            // ���� �ǹ� ���� (�ִϸ��̼� ȿ�� ����)
            pk::kill(building, false);
            pk::district@ district = pk::get_district(city.get_district_id());
            district.ap -= 10;
            
            // ���� ����
            pk::command(cmd_develop);
        }
        
        //---------------------------------------------------------------------------------------
        
        void goto_facility()
        {
            pk::point pos = building_t.pos;
            for (int i = 0; i < 4; i++)
            {
                pk::point pos_t;
                pos_t.x = pos.x + 1;
                pos_t.y = pos.y;
                if (pk::is_valid_pos(pos_t))
                    pos.x = pos.x + 1;
            }
            
            if (!pk::is_in_screen(pos))
                pk::move_screen(pos, 1);
            
            pk::highlight(building_t.pos, true);  
        }
        void remove_highlights()
        {
            pk::remove_all_highlights();
        }
        
        pk::building@ building_t;
        
        //---------------------------------------------------------------------------------------
        
        
        // �����ü� �Ǽ��� 100% ���� Ȯ��
        bool check_city_dev_complete(pk::city@ city)
        {
            if (city.num_devs < city.max_devs)
                return false;
            
            return true;
        }
        
        //---------------------------------------------------------------------------------------
        
        // �ʼ��ü����� Ȯ��
        bool check_essential_facility(int facility_id)
        {
            if (facility_id <= �ü�_��â or facility_id >= �ü�_����2��)
                return true;
            if (facility_id == �ü�_����� or facility_id == �ü�_�����)
                return true;
            
            return false;
        }
        
        // �Ǽ��� Ȯ���� ���� �����ü� 1�� ����ö��
        void remove_assist_facility(pk::city@ city, pk::building@ building_self)
        {
            bool removed = false;
            int count_facility = 0;
            
            if (pk::has_facility(city, �ü�_�Ͻ���))
            {
                removed = remove_facility(city, building_self, �ü�_�Ͻ���); 
                if (removed) return;
            }
            for (int remove_id = �ü�_������; remove_id <= �ü�_������; remove_id++)
            {
                if (pk::has_facility(city, remove_id))
                {
                    removed = remove_facility(city, building_self, remove_id); 
                    if (removed) return;
                }
            }
            if (pk::has_facility(city, �ü�_���г�))
            {
                removed = remove_facility(city, building_self, �ü�_���г�); 
                if (removed) return;
            }
            
            count_facility = get_facility_count(city, �ü�_��â);
            if (count_facility > 1)    // ��â ������ �������� �ϼ��ǹ��� ö��
            {
                for (int i = 0; i < count_facility; i++)
                {
                    removed = remove_facility(city, building_self, �ü�_��â); 
                    if (removed) return;
                }
            }
            count_facility = get_facility_count(city, �ü�_����);
            if (count_facility > 1)    // ���� ������ �������� �ϼ��ǹ��� ö��
            {
                for (int i = 0; i < count_facility; i++)
                {
                    removed = remove_facility(city, building_self, �ü�_����); 
                    if (removed) return;
                }
            }
            
            if (pk::has_facility(city, �ü�_����))
            {
                removed = remove_facility(city, building_self, �ü�_����); 
                if (removed) return;
            }
            if (pk::has_facility(city, �ü�_����))
            {
                removed = remove_facility(city, building_self, �ü�_����); 
                if (removed) return;
            }
            
        }
        
        // �ϼ��� �ü� ����ö��
        bool remove_facility(pk::city@ city, pk::building@ building_self, int remove_id)
        {
            pk::district@ district = pk::get_district(city.get_district_id());
            int gold_cost = int(pk::get_facility(remove_id).gold_cost);
            
            for (int i = 0; i < int(city.max_devs); i++)
            {
                pk::building@ building = city.dev[i].building;
                if (pk::is_alive(building))
                {
                    if (building.facility == remove_id and building.completed and building.pos != building_self.pos)
                    {
                        // ���� ö�Ÿ� ���� �ൿ�°� ö�Žü� ��� ����
                        district.ap += 10;  
                        pk::add_gold(city, gold_cost, false);
                        
                        // ����ö��
                        pk::destroy_cmd_info cmd_destroy;
                        @cmd_destroy.building = building;
                        pk::command(cmd_destroy);
                        
                        return true;    // ö�ſϷ�
                    }
                }
            }
            return false;   // ö�Ž���
        }
        
        // �ϼ��� �ü��� ī��Ʈ �Լ�
        int get_facility_count(pk::city@ city, int count_id)
        {
            int count = 0;
            for (int i = 0; i < int(city.max_devs); i++)
            {
                pk::building@ building = city.dev[i].building;
                if (pk::is_alive(building))
                {
                    if (building.facility == count_id)
                        count += 1;
                }
            }
            return count;
        }
        
        //---------------------------------------------------------------------------------------           
	}
    

    
	Main main;
}

