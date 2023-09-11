/*
// �ۼ���: �⸶å��
// Update: '18.11.10   / ���泻�� : �������� ��� �ű� �߰�
// Update: '19.3.4     / ���泻�� : �������� ���ð� �Ϻ� ����, ���ۺδ�/�����δ� ���� �˰��� ����, �����δ�� ������� �߰�, �ټ��������� �����⺴ ����
// Update: '19.3.7     / ���泻�� : �������� �����ĺ� ��� �߰�, ����/�ױ��� ���۽� ����/���� �ִ�ġ ���� (���߹���), �������� �˻��Լ� ����
// Update: '19.3.14    / ���泻�� : �����˻���� �߰�, �������� �˻����� ��ġ, ���ð��� ������ ��� �ٹ�� �л����� ��� �߰�, �����⺴ ������ ����/�Ĺ濩�ο� ���� ���غ��� ����
// Update: '19.3.16    / ���泻�� : �������� ������ �������� �����ĺ�
// Update: '19.3.17    / ���泻�� : ���ͼ��¿��� �ĺ����� �߰�
// Update: '19.3.30    / ���泻�� : ���ͼ��¿��� �ĺ����� �������� ����
// Update: '19.5.26    / ���泻�� : ���̵�_Ư�� ���� �ÿ��� �����ϵ��� ����
// Update: '20.2.8     / ���泻�� : ���ͼ��¿����� ������ �����δ�� �⺴�ϵ��� ����
// Update: '20.9.15    / ���泻�� : �������� �뺴Ư�� ����Լ� ���� ����, �����ִ� ��������� �����ȯ �߰�, �������� �����Լ� �и�, �������� ������ ��� �߰�
// Update: '20.9.20    / ���泻�� : �����ֺ� �˻� �� �δ���ǥ�� �������� Ȯ�� �߰� (���� ���� Ÿ������ �Ÿ��� ����� ��� ���ν� �ȵǵ��� ��)
*/


namespace ��������
{
    
    //=======================================================================================
    // ���������� (by �⸶å��)
    const bool ��������_���� = true;       // ���� ���� ���� ���۴� �⺴ ����
    
    const int  ��������_�����˻����� = 5;    // ���� ������������ ���δ븦 �˻��ϴ� �Ÿ� (����/�ױ��� �ִ� 6���� ���ѵ�)
    
    const int  ��������_�����ּҺ��� = 20000;  // ������ �������� �Ĺ����, ���غ��� �̻� ���� �� �ʰ� ���¸�ŭ ���� ����
    const int  ��������_��躴�´��� = 5000;   // �������� ������ ���, ��躴�� ������ �����¿� ����Ͽ� �����ּҺ��� ����
    
    const int  ��������_�ִ��������� = 8000;   // �����δ� ���� �� �ִ뺴�� ����
    const int  ��������_�ּ��������� = 3000;   // ������ �δ� �ּҺ��� ����, ���� ������ �ּҺ��� ���� �̴� �� ���� ����
    const int  ��������_���������Ÿ� = 2;      // ������ ��� �Ÿ� ���� ���� ���� �� ���� �⺴ (1 ~ 3 ����), ����/�ױ��� ������ �Ÿ� 1 �̳��� �˻�
    const int  ��������_������������� = 2;     // ���������� ������ �ܷ������, ���ؼ� �̻��̰� ���ൿ ���� ��� �������� (�� ���� �ֺ��� ���� ��� �ܷ������ �������)
    
    const int  ��������_�����˻���� = 1;      // 0: ���ø� �˻��Ͽ� �����⺴,  1: ����+����+�ױ� ��� �˻��Ͽ� �����⺴
    
    // �δ��������
    // �� 2�� ��� ��� �� ������ �Ÿ�, ������ ������� �������� �������� (���Ÿ�����, �������� ������ų�, �������� �������, �������� ������� �� ���ۺδ� ����)
    const int  ��������_�δ�������� = 2;        // 2: ����/���ۺδ� ��� ���,  1: ���ۺδ븸 ���,  0: �����δ븸 ���
    const int  ��������_������������� = 10;     // �δ��������2 ���� �� : ���������� ����� ���� �̻��� ��� ����������� �Ǵ��Ͽ� ���ۺδ� �⺴
    
    const int  ��������_�����δ�� = 4;      // �� �Ͽ� ���������� �ִ� �δ�� (��, ������ �Ÿ��� ���� �� �������� �������� �δ�� �Ÿ��� 1�� ����, �ּ� 1�δ� ����)
    const int  ��������_���ۺδ�� = 2;      // �� �Ͽ� ���������� �ִ� �δ��
    
    const bool ��������_�����ĺ����� = true;    // �� ������ ���� ħ�� �� ���� �������� ���� �ĺ�����
    
    const bool ��������_���ͼ��¿��� = true;    // ���ͼ����� ���������� ���� �ĺ�
    
    //------------------------------------------------------------
    // ������������ (by �⸶å��)
    const bool ��������_���� = true;       // ������ �������ÿ� ������ �⺴ ���� (���۴�, ��������, �����δ�)
    
    const int  ��������_�����δ��  = 2;     // ���������� �����δ� ���� �δ�� (�ּ�1 ~ �ִ�3)
    
    const bool ��������_���ۺδ���� = false;   // ���������� ���۴� ���
    const int  ��������_���ۺδ�� = 1;     // ���������� ���ۺδ� ���� �δ�� (�ּ�1 ~ �ִ�3)
    
    const bool ��������_����������� = true;   // ���������� �������� ���
    const int  ��������_�����δ�� = 3;      // ���������� �����δ� ���� �δ�� (�ּ�1 ~ �ִ�5)
    
    
    //=======================================================================================
    
	class Main
	{
		pk::func261_t@ prev_callback_261;

		Main()
		{
			@prev_callback_261 = cast<pk::func261_t@>(pk::get_func(261));
			pk::reset_func(261);
			pk::set_func(261, pk::func261_t(callback_261));
		}
        
		bool callback_261(pk::force@ force)
		{
			int force_id = force.get_id();

            if (!pk::is_campaign())
			{
                // �÷��̾�, �̹��� ������ ����.
                // ���̵� Ư�� �ÿ��� ���� �߰� ('19.5.26)
                if (!force.is_player() and pk::is_normal_force(force_id) and pk::get_scenario().difficulty == ���̵�_Ư��)
                {
                    
                    if (��������_����) func_reinforcement(force);   // ���� ���� �⺴ ('18.11.10, �߰�)
                    if (��������_����) func_attack_support(force);  // ������������ �����Լ� ȣ�� ('20.9.14, �߰�)
                }
			}

			// ���� �ڵ鷯�� �ִٸ� ü��.
			if (prev_callback_261 !is null)
				return prev_callback_261(force);
            
			return false;
		}
        
        //---------------------------------------------------------------------------------------
        //          ���� ���� ���� �Լ�
        //---------------------------------------------------------------------------------------
        
        // ��������
        pk::list<pk::building@> list_engage_base;        // ���� �ʿ��� �������� ����Ʈ
        pk::list<pk::building@> list_reinforce_base;     // ���� �������� ����Ʈ
        pk::array<int> arr_reinforce_count(�ǹ�_������, 0);   // ���� �ĺ����� ������� ������
        pk::array<int> arr_engage_troops(�ǹ�_������, 0);     // �������� ������ ������
        pk::array<int> unit_count(2, 0);   // [0] �����δ� ������, [1] ���ۺδ� ������
        
        //----- �������� �����Լ�
        void func_reinforcement(pk::force@ force)
        {
            int force_id = force.get_id();
            
            list_engage_base.clear();
            list_reinforce_base.clear();
            clear_reinforce_info();
            
            for (int i = (�ǹ�_������ - 1); i >= 0; i--)
            {
                pk::building@ base = pk::get_building(i);
                pk::district@ district = pk::get_district(base.get_district_id());
                
                if (base.get_force_id() == force_id and needReinforce(base))    // �ڼ��� ���� �˻�
                {
                    // �� ������ ���� �� ���� ����
                    if (��������_�����ĺ����� and needPersonSupport(base))
                        PushPersonSupport(base);    // �� ������ �������� �ϴ� 1ȸ ���� (��ȯ ���)

                    // ���� ������ ������ ���� ���� �˻��Ͽ� ������ ������ ���� ���� ���� ('20.9.13)
                    int send_person = getNearestReinforce(base, force, /*has_person*/false);     
                    if (��������_�����ĺ����� and send_person != -1)
                        PushPersonSupport(pk::get_building(send_person));  // ������ ���� �������� ���� ����

                    // �����⺴���� �����˻�
                    int src_target = getNearestReinforce(base, force, /*has_person*/true);
                    if (src_target != -1)
                    {
                        list_engage_base.add(base);     // �����ʿ� ��������Ʈ �߰�
                        
                        // �����ʿ� ������ ������ ���: ���� �ĺ����� ī��Ʈ �߰�
                        if (base.get_id() < �ǹ�_���ó�)   
                            arr_reinforce_count[src_target] += 1;
                    }
                }
            }
            
            // �������� �������� ���� ('19.3.16)
            list_engage_base.sort(function(a, b)
            {
                if (a.get_id() < �ǹ�_���ó� and b.get_id() < �ǹ�_���ó�)
                    return (main.arr_engage_troops[a.get_id()] > main.arr_engage_troops[b.get_id()]);
                
                return (a.get_id() > b.get_id());
            });
            
            // �����ʿ� �������� ���� �⺴ ('19.3.13)
            pk::array<pk::building@> arr_engage_base = pk::list_to_array(list_engage_base);
            for (int i = 0; i < int(arr_engage_base.length); i++)
            {
                list_reinforce_base.clear();    // �����Ϸ� ���� ����Ʈ �ʱ�ȭ
                pk::building@ base = arr_engage_base[i];
                
                unit_count[0] = 0;  // ������ �����δ�� �ʱ�ȭ
                unit_count[1] = 0;  // ������ ���ۺδ�� �ʱ�ȭ
                int push_count = 0;  // push Ƚ�� Ȯ�� ����
                
                int engage_troops = arr_engage_troops[base.get_id()];
                pk::array<int> max_count(2, 0);     // �ִ� �������� �δ��
                max_count[0] = pk::max(1, pk::min(��������_�����δ��, 1 + engage_troops/4000));
                max_count[1] = pk::max(1, ��������_���ۺδ��);
                
                // �������� �˻��� �����Ͽ� ���� ��� �ݺ� ���� ('19.3.4 ����)
                bool cmd = false;
                while(unit_count[0] < max_count[0] and unit_count[1] < max_count[1] and push_count < (max_count[0] + max_count[1]))
                {
                    push_count += 1;
                    cmd = (PushReinforce(base) or cmd);    // ���� �⺴
                }
            }
            
            list_engage_base.clear();
            list_reinforce_base.clear();
            clear_reinforce_info();
        }
        
        
        
        //----------------------------------------------------------------------------------
        //          ���� ����
        //----------------------------------------------------------------------------------
        
        
		/** ������ �ʿ��� ��Ȳ���� �Ǵ� */
		bool needReinforce(pk::building@ base)
		{
			int enemy_units1 = 0;
			int enemy_units2 = 0;
			int enemy_units3 = 0;
			int enemy_troops1 = 0;
			int enemy_troops2 = 0;
			int enemy_troops3 = 0;
			int force_units3 = 0;

            // �����˻�����
            int ref_city_id = pk::get_city_id(base.pos);   // ���� ��ǥ�� �Ҽӵ� ���� Ȯ�� ('20.9.20)
            pk::building@ ref_city = pk::get_building(ref_city_id);
			pk::array<pk::point> range = pk::range(base.pos, 1, ((base.facility == �ü�_����) ? (��������_�����˻����� + 1) : pk::min(6, ��������_�����˻�����)) );
			for (int i = 0; i < int(range.length); i++)
			{
                pk::point pos = range[i];
				pk::unit@ unit = pk::get_unit(pos);
				if (pk::is_alive(unit))
				{
                    int pos_city_id = pk::get_city_id(unit.pos);   // �δ� ��ǥ�� �Ҽӵ� ���� Ȯ�� ('20.9.20)
                    pk::building@ pos_city = pk::get_building(pos_city_id);
                    if (pk::is_alive(pos_city) and pk::is_alive(ref_city) and pos_city_id == ref_city_id)
                    {
                        int distance = pk::get_distance(base.get_pos(), pos);
                        if (pk::is_enemy(base, unit))
                        {
                            if (distance <= 1)
                            {
                                enemy_units1++;
                            }
                            if (distance <= pk::max(3, (��������_�����˻�����/2)))
                            {
                                enemy_units2++;
                                enemy_troops2 += unit.troops;
                            }
                            if (distance <= ��������_�����˻�����)
                            {
                                enemy_units3++;
                                enemy_troops3 += unit.troops;
                            }
                        }
                        else if (base.get_force_id() == unit.get_force_id() and unit.type == �δ�����_����)
                        {
                            if (distance <= ��������_�����˻�����)
                            {
                                force_units3++;
                            }
                        }
                    }
				}
			}
            
			int base_troops = pk::get_troops(base);
            
            // ���� ������ ������Ʈ
            arr_engage_troops[base.get_id()] = (enemy_troops3 - (base_troops + force_units3));
            
            // ���δ� ���� ���ݺδ� ������ ���� ���
            if ((enemy_units1 >= 1 or enemy_units2 >= 2 or enemy_units3 >= 3) and force_units3 <= enemy_units3 and force_units3 > 0)
                return true;
            
			// ���� �⺴ �ߵ� �� �ܿ� ���� ����
			if (base_troops < int(enemy_troops3 * 1.0f) and int(base.hp) > pk::max(500, int(pk::get_max_hp(base) * 0.3f)) and int(base.hp) < int(pk::get_max_hp(base) * 0.9f))
				return true;
            
			// ���� �⺴ �ߵ� �� �ܿ� ���� ����
			if (base_troops < int(enemy_troops2 * 1.0f) and base_troops < int(enemy_troops3 * 0.5f) and int(base.hp) < pk::max(1000, int(pk::get_max_hp(base) * 0.5f)) )
				return true;
            
            // ����/�ױ��� ��� ���� ����, ���� ħ�� �� �ﰢ �����⺴
            if (base.get_id() >= �ǹ�_���ó� and base_troops == 0 and enemy_units3 > 0)
                return true;
            
			return false;
		}
        
		/** ���� ���� �̻��� ���� ����� �Ʊ� ������ ����. */
        pk::building@ dst_t;
		int getNearestReinforce(pk::building@ dst, pk::force@ force, bool has_person=true)
		{
			int best_src = -1;
			int best_distance = 1;
            int dst_id = dst.get_id();
            
            pk::city@ city_of_dst = pk::get_city(pk::get_city_id(dst.pos));
            bool is_enemy_line = pk::is_enemy(city_of_dst, force);
            int max_distance = (dst_id >= �ǹ�_���ó�)? (is_enemy_line? 2 : 1) : pk::max(1, pk::min(3, ��������_���������Ÿ�));
            bool reinforce_mode = pk::is_enemy(force, dst);   // true: ������, false: �ڼ��� �Ǵ� ���ͱ�
            if (reinforce_mode) max_distance = pk::min(2, max_distance); // �������� ��� �˻��Ÿ� 2 ���Ϸ� ����
            
            @dst_t = @dst;
            pk::list<pk::building@> src_list; 
            
            int search_base = �ǹ�_���ó�;
            if      (has_person and ��������_�����˻���� == 0) search_base = �ǹ�_���ó�;
            else if (has_person and ��������_�����˻���� == 1) search_base = �ǹ�_������;
            else if (!has_person) search_base = �ǹ�_������;     // �˻����� �߰� ('20.9.13)
            
			// ���� ���� ���� �˻�
			for (int i = 0; i < search_base; i++)
			{
				pk::building@ src = pk::get_building(i);
                int src_id = src.get_id();
                
                bool check_reinforce_force = false;
                if (!reinforce_mode)   // �ڼ��� �Ǵ� ���ͱ� ���� �˻�
                    check_reinforce_force = (��������_���ͼ��¿���)? (!pk::is_enemy(dst, src) and !src.is_player()) : (dst.get_force_id() == src.get_force_id() and !src.is_player());
                else    // Ÿ���� ���� �˻� (�Լ����� ������ ����)
                    check_reinforce_force = (pk::is_enemy(dst, src) and !src.is_player()) and (force.get_id() == src.get_force_id());
                
                // Ÿ ����, �����ƴ�, �����ʿ���� �ƴ�, �����Ϸ���� �ƴ�
				if (dst_id != src_id and check_reinforce_force and !pk::enemies_around(src) 
                    and !needReinforce(src) and !list_reinforce_base.contains(src) and !list_attack_base.contains(src))
                {
                    // ���ðŸ�
                    int city_dist = -1;
                    if (dst_id < �ǹ�_���ó� and src_id < �ǹ�_���ó�)
                        city_dist = pk::get_city_distance(dst_id, src_id);
                    
                    // �����Ÿ�
                    int base_dist = pk::get_building_distance(dst_id, src_id, dst.get_force_id());
                    
                    // �Ÿ� ���� ���� ��
                    if ( (0 <= base_dist and base_dist <= max_distance) or city_dist == 1)
                    {
                        int enemy_weight = countNeighborEnemyBase(src);
                        int ref_troops = (enemy_weight * ��������_��躴�´���) + ��������_�����ּҺ���;
                        int src_troops = pk::get_troops(src);
                        int src_food = pk::get_food(src);
                        
                        int ref_p_count = pk::max(1, (enemy_weight / 4) + ��������_�������������);
                        int person_count = pk::get_person_list(src, pk::mibun_flags(�ź�_����, �ź�_����, �ź�_�¼�, �ź�_�Ϲ�)).count;
                        int idle_p_count = pk::get_idle_person_list(src).count;
                        
                        int weapon_amount = 0;
                        int siege_amount = 0;
            
                        for (int j = ����_â; j <= ����_����; j++)     // â�س븶 ������� ���ϱ�
                        {
                            weapon_amount += pk::get_weapon_amount(src, j);
                        }
                        for (int j = ����_����; j <= ����_���; j++)     // �������� ���� ���ϱ�
                        {
                            siege_amount += pk::get_weapon_amount(src, j);
                        }
                        
                        // ���������� ���� (�����, ����, ����, ���� ������)
                        if (((has_person and person_count >= ref_p_count and idle_p_count > 0) or (!has_person and person_count == 0))
                            and src_troops > ref_troops and weapon_amount >= ref_troops and src_food >= int(1.5f * ref_troops))
                        {
                            if (!reinforce_mode)    // �ڼ��� �Ǵ� ���ͱ�
                            {
                                best_src = src_id;
                                src_list.add(src);  // �������� ��������Ʈ
                            }
                            else if (reinforce_mode and siege_amount > 2)  // ������, �������� �������� �߰� Ȯ��
                            {
                                best_src = src_id;
                                src_list.add(src);  // �������� ��������Ʈ
                            }
                        }
                    }
                }
			}
            
            // �������� ��������Ʈ ���� (���� �Ÿ� ��������, ��ǥ�Ÿ� ��������)
            if (src_list.count == 0)
                best_src = -1;
            else
            {
                src_list.sort(function(a, b)
                {
                    int build_dist_a = pk::get_building_distance(a.get_id(), main.dst_t.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.dst_t.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.dst_t.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.dst_t.pos);
                    
                    return (build_dist_a != build_dist_b)? (build_dist_a < build_dist_b) : (pos_dist_a < pos_dist_b);
                });
                best_src = src_list[0].get_id();
            }
            
			return best_src;
		}

        //----------------------------------------------------------------------------------
        
        // ***** �ֺ� ������ �� Ȯ�� ***** //
        int countNeighborEnemyBase(pk::building@ src)
        {
            int weight = 0;
            int troops = 0;
            for (int i = 0; i < �ǹ�_������; i++)
			{
                pk::building@ dst = pk::get_building(i);
                int src_id = src.get_id();
                int dst_id = dst.get_id();
                
                if (src_id != dst_id and pk::is_neighbor_base(src_id, dst_id) and pk::is_enemy(src, dst))
                    troops += pk::get_troops(dst);
            }
            
            weight = int(troops / ��������_��躴�´���);
            return weight;
        }
        
        
        //----------------------------------------------------------------------------------
        
        
		// ***** ���� ���� ��� ***** //
        bool PushReinforce(pk::building@ dst_base)
		{
			// ���� �δ밡 ������ �α� ������ �ִ��� Ȯ��
            pk::force@ force = pk::get_force(dst_base.get_force_id());
			int target = getNearestReinforce(dst_base, force, /*has_person*/true);
			if (target == -1) return false;

            // ���� ���� ����
            pk::building@ src_base = pk::get_building(target);
            int src_id = src_base.get_id();
            int dst_id = dst_base.get_id();
            
            // ���� �δ� ���� �Ǵ� ('19.3.4)
            int reinforce_type = -1;
            if (��������_���ͼ��¿��� and !pk::is_enemy(src_base, dst_base) and src_base.get_force_id() != dst_base.get_force_id())
                reinforce_type = �δ�����_����; // ���ͼ��¿����� ������ �����δ� ('20.2.8)
            else
            {
                if (��������_�δ�������� == 0) reinforce_type = �δ�����_����;   // ������ �����δ�
                if (��������_�δ�������� == 1) reinforce_type = �δ�����_����;   // ������ ���ۺδ�
                if (��������_�δ�������� == 2) reinforce_type = get_reinforce_unit_type(src_base, dst_base);
            }
            if (reinforce_type < 0 or reinforce_type > �δ�����_��) return false;
            
            // ���������� ��ǥ������ �Ÿ�
            int distance = pk::get_building_distance(src_id, dst_id, src_base.get_force_id());
            
            // ��ǥ���� ���� ��� �л� ('19.3.13)
            int divide = pk::max(1, arr_reinforce_count[src_id]);
            
            // ���� �Ÿ� �� ������ ���� �������� �δ�� ���� ('19.3.5)
            int engage_troops = arr_engage_troops[dst_base.get_id()];
            pk::array<int> max_unit(2, 0);  // �ִ� �������� �δ��
            max_unit[0] = pk::max(1, pk::min(1 + engage_troops/4000  , int((��������_�����δ�� - (distance - 1))/divide) ) );
            max_unit[1] = pk::max(1, int( ��������_���ۺδ��/divide) );
            
            if (dst_id >= �ǹ�_���ó�)   // ����/������ �� �������� 1�δ븸
            {
                max_unit[0] = 1;
                max_unit[1] = 1;
            }
            
            int push_count = 0;  // push Ƚ�� Ȯ�� ����
            
            // ������������ �ݺ������� ���� ��� ���� ('19.3.4)
            while(unit_count[0] < max_unit[0] and unit_count[1] < max_unit[1] and  push_count < (max_unit[0] + max_unit[1]))
            {
                push_count += 1;
                
                if (reinforce_type == �δ�����_����)
                {
                    int unit_id = PushTransportUnit(src_base, dst_base, true);  // ���ۺδ� ����
                    if (unit_id != -1)
                    {
                        unit_count[1] += 1;     // ���ۺδ� ī��Ʈ
                        if (!list_reinforce_base.contains(src_base))
                            list_reinforce_base.add(src_base);
                    }
                }
                else if (reinforce_type == �δ�����_����)
                {
                    int unit_id = PushCombatUnit(src_base, dst_base, true);     // �����δ� ����
                    if (unit_id != -1)
                    {
                        unit_count[0] += 1;     // �����δ� ī��Ʈ
                        if (!list_reinforce_base.contains(src_base))
                            list_reinforce_base.add(src_base);
                    }
                }
            }
            if ((unit_count[0] + unit_count[1]) > 0) return true;
            
			return false;
		}
        
        //----------------------------------------------------------------------------------
        
        // �������� �� �������� ������� ������ �δ����� ���� ('19.3.4)
        int get_reinforce_unit_type(pk::building@ src_base, pk::building@ dst_base)
        {
            if (!pk::is_alive(src_base) or !pk::is_alive(dst_base)) return -1;

            // ������ �Ҽӹ��� ����
            pk::list<pk::person@> list_src_men = pk::get_person_list(src_base, pk::mibun_flags(�ź�_����, �ź�_����, �ź�_�¼�, �ź�_�Ϲ�));
            pk::list<pk::person@> list_dst_men = pk::get_person_list(dst_base, pk::mibun_flags(�ź�_����, �ź�_����, �ź�_�¼�, �ź�_�Ϲ�));
            
            // �����
            int src_count = list_src_men.count;    // �������� ���ൿ �����
            int dst_count = list_dst_men.count;    // ��ǥ���� ��ü �����
            
            // �����Ÿ�
            int distance = pk::get_building_distance(src_base.get_id(), dst_base.get_id(), src_base.get_force_id());
            
            // ���� �δ����� ����
            int reinforce_type = -1;
            if (pk::get_troops(dst_base) < 3000 and unit_count[1] < 1)
                reinforce_type = �δ�����_����;    // ���º��� ������ ���ۺδ� �Ⱥ��� ��� ���ۺδ� ����
            
            else if (distance <= 1)
                reinforce_type = �δ�����_����;    // ����� �Ÿ��� ��� : �����δ�
            
            else if (dst_count == 0)
                reinforce_type = �δ�����_����;    // ��ǥ���� ������� �� : �����δ�
            
            else if (dst_count >= pk::max(1, ��������_�������������))
                reinforce_type = �δ�����_����;    // ��ǥ���� n�� �̻� : ���ۺδ�
            
            else if (src_count <= pk::max(1, ��������_�������������)) 
                reinforce_type = �δ�����_����;    // �������� ���� ��� : ���ۺδ�
            
            else                     
                reinforce_type = �δ�����_����;    // �����δ�
            
            return reinforce_type;
        }
        
        // �ǹ�ID�� ���� ���� ������ ��ȯ
        int get_base_type(int building_id)
        {
            int type = -1;
            if (�ǹ�_���ý��� <= building_id and building_id < �ǹ�_���ó�) type = 0;
            if (�ǹ�_�������� <= building_id and building_id < �ǹ�_������) type = 1;
            if (�ǹ�_�ױ����� <= building_id and building_id < �ǹ�_�ױ���) type = 2;
            return type;
        }
        
        //----------------------------------------------------------------------------------
        
        // ���ۺδ� ���� ó��
        int PushTransportUnit(pk::building@ src_base, pk::building@ dst_base, bool do_cmd = true)
        {
            if (!pk::is_alive(src_base) or !pk::is_alive(dst_base)) return -1;
            
            int enemy_weight = countNeighborEnemyBase(src_base);    // ������ ����ġ
            int ref_troops = (enemy_weight * ��������_��躴�´���) + ��������_�����ּҺ���;
            if (pk::get_troops(src_base) <= (ref_troops + ��������_�ּ���������)) return -1;    // ���� ����
              
            int person_count = pk::get_person_list(src_base, pk::mibun_flags(�ź�_����, �ź�_����, �ź�_�¼�, �ź�_�Ϲ�)).count;
            if (person_count <= pk::max(1, (enemy_weight/4) + ��������_�������������)) return -1;   // ���� ����
            
            auto person_list = pk::get_idle_person_list(src_base);
            int base_type = get_base_type(dst_base.get_id());
            if (base_type == 0 and person_list.count <= 1) return -1;   // ���� ���� (����)
            if (base_type > 0  and person_list.count < 1)  return -1;   // ���� ���� (����,�ױ�)
            
            // ��ġ�� ���� ������ ����.
			person_list.sort(function(a, b)
			{
				return (float(a.stat[����ɷ�_��ġ]) / float(a.stat[����ɷ�_����])) > (float(b.stat[����ɷ�_��ġ]) / float(b.stat[����ɷ�_����]));
			});
            pk::person@ leader = pk::get_person(person_list[0].get_id());
            
            // ���� ���� ���� : ���� ���� �ʰ���
            int reinforce_troops = pk::min( pk::max(1, (45000 - ref_troops)), pk::max(1, pk::get_troops(src_base) - ref_troops));
            
            // �������� ����/�ױ��� ��� �������� ����
            if (base_type > 0)
            {
                if (pk::has_tech(dst_base, �ⱳ_�װ�Ȯ��))
                    reinforce_troops = pk::min(20000, reinforce_troops);
                else
                    reinforce_troops = pk::min(10000, reinforce_troops);
            }
            
            // ���� ���
            int unit_food = int(pk::min(2.0f * reinforce_troops, pk::max( 0.5f * pk::get_food(src_base), 1.2f * reinforce_troops)));
            if (unit_food < int(0.5f * reinforce_troops)) return -1;   // ���� ����
            
            // ���� ���
            if (do_cmd)
            {
                // ���� ��� ���� ����.
                pk::com_deploy_cmd_info cmd;
                @cmd.base = @src_base;
                cmd.type = �δ�����_����;
                cmd.member[0] = leader.get_id();
                cmd.gold = (pk::get_gold(src_base) >= 1000) ? int(pk::min(2000.f, pk::get_gold(src_base) * 0.1f)) : 0;
                cmd.food = pk::min(unit_food, 500000);
                cmd.troops = pk::min(60000, pk::max(1, reinforce_troops));
                
                // â�س븶 ������� ���ϱ�
                int weapon_sum = 0;
                for (int j = ����_â; j <= ����_����; j++)     
                {
                    weapon_sum += pk::get_weapon_amount(src_base, j);
                }
                
                // ���� ��ü ������ ���¸�ŭ, ���⺰ ������� ���
                int i = 0;
                for (int weapon_id = ����_â; weapon_id <= ����_����; weapon_id++)
                {
                    int weapon_amount = int(pk::get_weapon_amount(src_base, weapon_id) * 0.9f);
                    if (weapon_id <= ����_���� and weapon_amount > 0)
                    {
                        cmd.weapon_id[i] = weapon_id;
                        cmd.weapon_amount[i] = pk::min(100000, weapon_amount, reinforce_troops * weapon_amount / weapon_sum);
                        i++;
                    }
                    else if (is_siege_weapon(weapon_id) and weapon_amount > 0)
                    {
                        cmd.weapon_id[i] = weapon_id;
                        cmd.weapon_amount[i] = pk::min(100, (1 + weapon_amount / 4));
                        i++;
                    }
                }
                
                cmd.order = �δ��ӹ�_�̵�;
                cmd.target_pos = dst_base.get_pos();  // ��ǥ�� �������� ����

                // ����.
                int unit_id = pk::command(cmd);
                pk::unit@ unit_cmd = pk::get_unit(unit_id);
                if (pk::is_alive(unit_cmd))
                {
                    unit_cmd.action_done = true;
                    
                    if (����׸��) 
                    {
                        string src_name  = pk::decode(pk::get_name(src_base));
                        string dst_name  = pk::decode(pk::get_name(dst_base));
                        string unit_name = pk::decode(pk::get_name(leader));
                        string order_str = get_order_info(unit_cmd.order);
                        string cmd_info  = (pk::is_enemy(src_base, dst_base))? "��������" : "��������";
                        pk::info(pk::format("{}: {}�� {}: {}��{}", cmd_info, unit_name, order_str, src_name, dst_name));
                    }
                    return unit_id;
                }
            }
            
            return -1;
        }
        
        //----------------------------------------------------------------------------------
        
        // �����δ� ���� ó��
        int PushCombatUnit(pk::building@ src_base, pk::building@ dst_base, bool do_cmd = true)
        {
            if (!pk::is_alive(src_base) or !pk::is_alive(dst_base)) return -1;
            
            int enemy_weight = countNeighborEnemyBase(src_base);    // ������ ����ġ
            int ref_troops = (enemy_weight * ��������_��躴�´���) + ��������_�����ּҺ���;
            if (pk::get_troops(src_base) <= (ref_troops + ��������_�ּ���������)) return -1;    // ���� ����
            
            int person_count = pk::get_person_list(src_base, pk::mibun_flags(�ź�_����, �ź�_����, �ź�_�¼�, �ź�_�Ϲ�)).count;
            if (person_count <= pk::max(1, (enemy_weight/4) + ��������_�������������)) return -1;   // ���� ����
            
            auto person_list = pk::get_idle_person_list(src_base);
            if (person_list.count == 0) return -1;   // ���� ����
            
            // �������� ����/�ױ��� ��� �뺴 ���� ���
            int base_type = get_base_type(dst_base.get_id());
            cmd_archer = (base_type > 0);
            
            // ���+���� ���� ������ ����.
			person_list.sort(function(a, b)
			{
                if (main.cmd_archer)    // �뺴 ��� ����
                {
                    // �ú� Ư�� �ݿ� ('20.9.13)
                    bool a_archer = (pk::has_skill(a, Ư��_�ý�) or pk::has_skill(a, Ư��_����) or pk::has_skill(a, Ư��_���));
                    bool b_archer = (pk::has_skill(b, Ư��_�ý�) or pk::has_skill(b, Ư��_����) or pk::has_skill(b, Ư��_���));
                    if ( a_archer and !b_archer) return true;   
                    if (!a_archer and  b_archer) return false;  
                    // �ú� ����
                    if (a.tekisei[����_�뺴] != b.tekisei[����_�뺴]) return (a.tekisei[����_�뺴] > b.tekisei[����_�뺴]);
                    // ���� �ɷ�
                    return (a.stat[����ɷ�_����] + a.stat[����ɷ�_���]) > (b.stat[����ɷ�_����] + b.stat[����ɷ�_���]);
                }
                
				return (a.stat[����ɷ�_����] + a.stat[����ɷ�_���]) > (b.stat[����ɷ�_����] + b.stat[����ɷ�_���]);
			});
            pk::person@ leader = pk::get_person(person_list[0].get_id());
            
            // ���� ���� ���� : ���� ���� �ʰ���, ���ְ��ɺ��� Ȯ��
            int reinforce_troops = pk::min(��������_�ִ���������, pk::get_command(leader), pk::max(1, pk::get_troops(src_base) - ref_troops));

            // ���� ���� ����
            int ground_weapon_id = ����_��;
            int water_weapon_id = ����_�ְ�;
            int unit_troops = reinforce_troops;
            
            // ���� ���� ����
            get_ground_weapon(src_base, leader, reinforce_troops, ground_weapon_id, unit_troops);
            if (ground_weapon_id == 0) return -1;    // ���� ����
            
            // ���� ���� ����
            if (check_building_has_port(src_base) and check_building_has_port(dst_base))
            {
                if (leader.tekisei[����_����] == ����_C)
                    water_weapon_id = ����_�ְ�;
                else
                {
                    if      (pk::get_weapon_amount(src_base, ����_����) > 0) water_weapon_id = ����_����;
                    else if (pk::get_weapon_amount(src_base, ����_����) > 0) water_weapon_id = ����_����;
                    else water_weapon_id = ����_�ְ�;
                }
            }
            else
                water_weapon_id = ����_�ְ�;
            
            // ���� ���
            int unit_food = int(pk::min(2.0f * unit_troops, pk::max( 0.5f * pk::get_food(src_base), 1.2f * unit_troops)));
            if (unit_food < int(0.5f * unit_troops)) return -1;   // ���� ����
            
            // ���� ���
            if (do_cmd)
            {
                // ���� ��� ���� ����.
                pk::com_deploy_cmd_info cmd;
                @cmd.base = @src_base;
                cmd.type = �δ�����_����;
                cmd.member[0] = leader.get_id();
                cmd.gold = (pk::get_gold(src_base) >= 1000) ? int(pk::min(1000.f, pk::get_gold(src_base) * 0.1f)) : 0;
                cmd.troops = pk::max(1, unit_troops);
                cmd.weapon_id[0] = ground_weapon_id;
                cmd.weapon_id[1] = water_weapon_id;
                cmd.weapon_amount[0] = (is_siege_weapon(ground_weapon_id))? 1 : pk::max(1, unit_troops);
                cmd.weapon_amount[1] = (water_weapon_id == ����_�ְ�)? 0 : 1;
                cmd.food = pk::min(50000, unit_food);

                cmd.order = (src_base.get_force_id() == dst_base.get_force_id())? �δ��ӹ�_���� : 
                                             ((pk::is_enemy(src_base, dst_base))? �δ��ӹ�_���� : �δ��ӹ�_�̵�);    // �ڼ���, ������, ���ͱ�

                cmd.target_pos = dst_base.get_pos();  // ��ǥ�� �������� ����

                // ����.
                int unit_id = pk::command(cmd);
                pk::unit@ unit_cmd = pk::get_unit(unit_id);
                if (pk::is_alive(unit_cmd))
                {
                    unit_cmd.action_done = true;
                    
                    if (����׸��) 
                    {
                        string src_name  = pk::decode(pk::get_name(src_base));
                        string dst_name  = pk::decode(pk::get_name(dst_base));
                        string unit_name = pk::decode(pk::get_name(leader));
                        string order_str = get_order_info(unit_cmd.order);
                        string cmd_info  = (pk::is_enemy(src_base, dst_base))? "��������" : "��������";
                        pk::info(pk::format("{}: {}�� {}: {}��{}", cmd_info, unit_name, order_str, src_name, dst_name));
                    }
                    return unit_id;
                }
            }
            
            return -1;
        }
        
        // �뺴��� ��������
        bool cmd_archer = false;    
        
        
        // �������� �δ� ���� ó��
        int PushSiegeUnit(pk::building@ src_base, pk::building@ dst_base, bool do_cmd = true)
        {
            if (!pk::is_alive(src_base) or !pk::is_alive(dst_base)) return -1;
            
            int enemy_weight = countNeighborEnemyBase(src_base);    // ������ ����ġ
            int ref_troops = (enemy_weight * ��������_��躴�´���) + ��������_�����ּҺ���;
            if (pk::get_troops(src_base) <= (ref_troops + ��������_�ּ���������)) return -1;    // ���� ����
            
            int person_count = pk::get_person_list(src_base, pk::mibun_flags(�ź�_����, �ź�_����, �ź�_�¼�, �ź�_�Ϲ�)).count;
            if (person_count <= pk::max(1, (enemy_weight/4) + ��������_�������������)) return -1;   // ���� ����
            
            auto person_list = pk::get_idle_person_list(src_base);
            if (person_list.count == 0) return -1;   // ���� ����

            // ���� �������� ��� Ȯ��
            int siege_dir_id = (pk::has_tech(src_base, �ⱳ_�������))? ����_��� : ����_����;
            int siege_rng_id = (pk::has_tech(src_base, �ⱳ_��������))? ����_���� : ����_����;
            int amt_siege_dir = pk::get_weapon_amount(src_base, siege_dir_id);  // ���� �������� ����
            int amt_siege_rng = pk::get_weapon_amount(src_base, siege_rng_id);  // ���� �������� ����
            if ((amt_siege_rng + amt_siege_dir) == 0) return -1;     // �������� ����
            
            // ����Ư�� ���, ���ȸ�� Ư�� ���, ���+���� ���� ������ ����.
			person_list.sort(function(a, b)
			{
                // ���� Ư�� ���
                bool a_skill = (pk::has_skill(a, Ư��_����) or pk::has_skill(a, Ư��_����) or pk::has_skill(a, Ư��_����));
                bool b_skill = (pk::has_skill(b, Ư��_����) or pk::has_skill(b, Ư��_����) or pk::has_skill(b, Ư��_����));
                if ( a_skill and !b_skill) return true;   
                if (!a_skill and  b_skill) return false;  
                // ���ȸ�� Ư�� ���
                bool a_energy = (pk::has_skill(a, Ư��_�־�) or pk::has_skill(a, Ư��_�û�) or pk::has_skill(a, Ư��_���));
                bool b_energy = (pk::has_skill(b, Ư��_�־�) or pk::has_skill(b, Ư��_�û�) or pk::has_skill(b, Ư��_���));
                if ( a_energy and !b_energy) return true;   
                if (!a_energy and  b_energy) return false;  
                // ���� ����
                if (a.tekisei[����_����] != b.tekisei[����_����]) return (a.tekisei[����_����] > b.tekisei[����_����]);
                // ���� �ɷ�
                return (a.stat[����ɷ�_����] + a.stat[����ɷ�_���]) > (b.stat[����ɷ�_����] + b.stat[����ɷ�_���]);
			});
            pk::person@ leader = pk::get_person(person_list[0].get_id());
            
            // ���� ���� ���� : ���� ���� �ʰ���, ���ְ��ɺ��� Ȯ��
            int reinforce_troops = pk::min(��������_�ִ���������, pk::get_command(leader), pk::max(1, pk::get_troops(src_base) - ref_troops));

            // ���� ���� ����
            int ground_weapon_id = ����_��;
            int water_weapon_id = ����_�ְ�;
            int unit_troops = reinforce_troops;
            
            // ���� ����������� �켱 ���� (����Ư��� ����, ����Ư��� ���� ���� �켱 ����)
            if      (amt_siege_rng > 0 and pk::has_skill(leader, Ư��_����)) ground_weapon_id = siege_rng_id;
            else if (amt_siege_dir > 0 and pk::has_skill(leader, Ư��_����)) ground_weapon_id = siege_dir_id;
            else if (amt_siege_rng > 0)  ground_weapon_id = siege_rng_id;
            else if (amt_siege_dir > 0)  ground_weapon_id = siege_dir_id;
            
            
            // ���� ���
            int unit_food = int(pk::min(2.0f * unit_troops, pk::max( 0.5f * pk::get_food(src_base), 1.2f * unit_troops)));
            if (unit_food < int(0.5f * unit_troops)) return -1;   // ���� ����
            
            // ���� ���
            if (do_cmd)
            {
                // ���� ��� ���� ����.
                pk::com_deploy_cmd_info cmd;
                @cmd.base = @src_base;
                cmd.type = �δ�����_����;
                cmd.member[0] = leader.get_id();
                cmd.gold = 0;   // �������� �δ�� �Ǽ��Ұ��� �ݼ��� ����
                cmd.troops = pk::max(1, unit_troops);
                cmd.weapon_id[0] = ground_weapon_id;
                cmd.weapon_id[1] = water_weapon_id;
                cmd.weapon_amount[0] = (is_siege_weapon(ground_weapon_id))? 1 : pk::max(1, unit_troops);
                cmd.weapon_amount[1] = (water_weapon_id == ����_�ְ�)? 0 : 1;
                cmd.food = pk::min(50000, unit_food);

                cmd.order = (src_base.get_force_id() == dst_base.get_force_id())? �δ��ӹ�_���� : 
                                             ((pk::is_enemy(src_base, dst_base))? �δ��ӹ�_���� : �δ��ӹ�_�̵�);    // �ڼ���, ������, ���ͱ�

                cmd.target_pos = dst_base.get_pos();  // ��ǥ�� �������� ����
                
                // ����.
                int unit_id = pk::command(cmd);
                pk::unit@ unit_cmd = pk::get_unit(unit_id);
                if (pk::is_alive(unit_cmd))
                {
                    unit_cmd.action_done = true;
                    
                    if (����׸��) 
                    {
                        string src_name  = pk::decode(pk::get_name(src_base));
                        string dst_name  = pk::decode(pk::get_name(dst_base));
                        string unit_name = pk::decode(pk::get_name(leader));
                        string order_str = get_order_info(unit_cmd.order);
                        string cmd_info  = (pk::is_enemy(src_base, dst_base))? "��������" : "��������";
                        pk::info(pk::format("{}: {}�� {}: {}��{}", cmd_info, unit_name, order_str, src_name, dst_name));
                    }
                    return unit_id;
                }
            }
            
            return -1;
        }
        
        
        //----------------------------------------------------------------------------------
        
        // ���� ���� �Լ�
        void get_ground_weapon(pk::building@ base, pk::person@ leader, int troops_max, int &out weapon_sel, int &out troops_sel)
        {
            int troops_min = ��������_�ּ���������;
            int weapon_max = 0;
            int best_tekisei = ����_C;
            
            weapon_sel = ����_��;
            troops_sel = 0;
            
            // �뺴 ��� ����
            if (cmd_archer)
            {
                int tekisei = leader.tekisei[pk::equipment_id_to_heishu(����_�뺴)];
                int weapon = pk::get_weapon_amount(base, ����_��);
                if (troops_min <= weapon and ����_B <= tekisei)
                {
                    weapon_sel = ����_��;
                    troops_sel = pk::min(weapon, troops_max);
                }
            }
            // �Ϲ� ����
            else    
            {
                // �⺴���� �̻� ������ ���� �� �ְ� ���� Ȯ��
                for (int id = ����_â; id <= ����_����; id++)
                {
                    int tekisei = leader.tekisei[pk::equipment_id_to_heishu(id)];
                    int weapon_t = pk::get_weapon_amount(base, id);
                    if (troops_min <= weapon_t and best_tekisei <= tekisei)
                        best_tekisei = tekisei;
                }
                
                // �ְ� ���� �̻��� ���� �� ���� ���� ���� ���� ����
                for (int id = ����_â; id <= ����_����; id++)
                {
                    int tekisei = leader.tekisei[pk::equipment_id_to_heishu(id)];
                    int weapon_t = pk::get_weapon_amount(base, id);
                    if (troops_min <= weapon_t and weapon_max <= weapon_t and best_tekisei <= tekisei)
                    {
                        best_tekisei = tekisei;
                        weapon_max = weapon_t;
                        weapon_sel = id;
                        troops_sel = pk::min(weapon_max, troops_max);
                    }
                }
            }
            
            if (weapon_sel == 0)
            {
                troops_sel = troops_min;
            }
        }
        
        bool is_siege_weapon(int weapon_id)
        {
            if (����_���� <= weapon_id and weapon_id <= ����_���) return true;
            return false;
        }
        
        bool check_building_has_port(pk::building@ base)
        {
            bool has_port = false;
            int base_id = base.get_id();
            if (�ǹ�_�ױ����� <= base_id and base_id < �ǹ�_�ױ���) return true;
            
            if (�ǹ�_���ý��� <= base_id and base_id < �ǹ�_���ó�)
            {
                pk::city@ city = pk::building_to_city(base);
                for (int i = 0; i < 5; i++)
                {
                    int sub_id = city.gate[i];
                    if (sub_id != -1)
                    {
                        pk::building@ sub_t = pk::get_building(sub_id);
                        if (pk::is_alive(sub_t) and (�ǹ�_�ױ����� <= sub_id and sub_id < �ǹ�_�ױ���)) return true;
                    }
                }
            }
            return false;
        }
        
        
        //----------------------------------------------------------------------------------
        /** ���� ��� ���� ī��Ʈ �ʱ�ȭ **/
        void clear_reinforce_info()
        {
            for (int i = 0; i < �ǹ�_������; i++)
            {
                arr_reinforce_count[i] = 0;
            }
        }
        
        
        
        //----------------------------------------------------------------------------------
        //  �� ���� ���� ����
        //----------------------------------------------------------------------------------
        
        /** �����İ��� �ʿ����� �Ǵ� **/
        bool needPersonSupport(pk::building@ base)
		{
            if (!pk::is_alive(base)) return false;
            
            int enemy_troops = 0;   // ������ ���� �� Ȯ�� �߰�
            pk::array<pk::point> range = pk::range(base.pos, 1, ((base.facility == �ü�_����) ? 6 : 5));
			for (int i = 0; i < int(range.length); i++)
			{
				pk::unit@ unit = pk::get_unit(range[i]);
				if (pk::is_alive(unit) and pk::is_enemy(base, unit))
                    enemy_troops += unit.troops;
			}
            
            int count = pk::get_person_list(base, pk::mibun_flags(�ź�_����, �ź�_����, �ź�_�¼�, �ź�_�Ϲ�)).count;
            if (count == 0 and pk::get_troops(base) >= 1000 and (pk::enemies_around(base) or enemy_troops >= 4000)) 
                return true;
            
            return false;
        }
        
        // ***** ���� ���� ��� ***** //
        bool PushPersonSupport(pk::building@ dst_base)
        {
            // ������ �ִ� �α� ������ �ִ��� Ȯ��
			int target = getNearestPerson(dst_base);
			if (target == -1) return false;
            
            // �������� ���� �ҼӰ���
            pk::building@ src_base = pk::get_building(target);
            
            int person_count = pk::get_person_list(src_base, pk::mibun_flags(�ź�_����, �ź�_����, �ź�_�¼�, �ź�_�Ϲ�)).count;
            if (person_count <= pk::max(1, ��������_�������������)) return false;   // ���� ����
            
            // ���ൿ ���帮��Ʈ
            auto person_list = pk::get_idle_person_list(src_base);
            if (person_list.count == 0) return false;   // ���� ����
            
            // ���+���� ���� ������ ����.
			person_list.sort(function(a, b)
			{
				return (a.stat[����ɷ�_����] + a.stat[����ɷ�_���]) > (b.stat[����ɷ�_����] + b.stat[����ɷ�_���]);
			});
            
            // ��ȯ�� �����
            int max = pk::max(1, pk::min(5, (person_list.count / 4)));
            
            // ��ȯ ��� ����
            pk::list<pk::person@> actors;
            for (int i = 0; i < max; i++)
            {
                actors.add(person_list[i]);
            }
            
            // ��ȯ ���
            pk::summon_cmd_info cmd_summon;
            @cmd_summon.base   = dst_base;
            cmd_summon.actors  = actors;
            pk::command(cmd_summon);
            
            return true;
        }
        
        /** ������ �ִ� ����� �Ʊ� ������ ����. */
        int getNearestPerson(pk::building@ dst)
		{
			int best_src = -1;
			int best_distance = 0;
            
			// �������� Ȯ��.
			for (int i = 0; i < �ǹ�_������; i++)
			{
				pk::building@ src = pk::get_building(i);
                
				if (dst.get_id() != i and dst.get_force_id() == src.get_force_id() and (!pk::enemies_around(src) and !needReinforce(src)) )
                {
                    int distance = pk::get_building_distance(dst.get_id(), i, dst.get_force_id());
                    
                    auto person_list = pk::get_idle_person_list(src);
                    
                    int max_distance = pk::max(1, pk::min(3, ��������_���������Ÿ�));
                    if ((0 <= distance and distance < best_distance and distance <= max_distance) or best_src == -1)
                    {
                        if (person_list.count > ��������_�������������)
                        {
                            best_src = i;
                            best_distance = distance;
                        }
                    }
                }
			}
			return best_src;
		}
        
        
        
        //---------------------------------------------------------------------------------------
        //  ������������ �����Լ�
        //---------------------------------------------------------------------------------------
        
        pk::list<pk::building@> list_target_base;     // ������ �ʿ��� �������� ����Ʈ
        pk::list<pk::building@> list_attack_base;     // ������ �������� ����Ʈ
        
        
        void func_attack_support(pk::force@ force)
        {
            int force_id = force.get_id();
            
            // �� ���� ���� ������ : �����ϴ� ������, �δ�� ������Ʈ
            clear_engage_info();
            update_engage_info();
            list_target_base.clear();
            list_attack_base.clear();
            
            for (int i = (�ǹ�_���ó� - 1); i >= 0; i--)
            {
                pk::building@ dst_base = pk::get_building(i);
                int atk_force_id = get_force_invaded(dst_base);
                if (pk::is_enemy(force, dst_base) and is_invaded_base(dst_base) and atk_force_id == force_id) // Ÿ���� ���� ���� ����
                {
                    int src_target = getNearestReinforce(dst_base, force, /*has_person*/true);    // �������� ������ ���� ��ȯ
                    pk::building@ src_base = pk::get_building(src_target);
                    if (pk::is_alive(src_base) and !list_target_base.contains(dst_base))
                        list_target_base.add(dst_base);
                }
            }
            
            // ���� �������� �������� ���� (������ �켼 ���� �켱 �ĺ�)
            list_target_base.sort(function(a, b)
            {
                if (a.get_id() < �ǹ�_���ó� and b.get_id() < �ǹ�_���ó�)
                    return (main.get_engage_status(a.get_id()) < main.get_engage_status(b.get_id()));
                
                return (a.get_id() > b.get_id());
            });
            
            // ���� �������� ���������� ������ �߰� �ĺ�
            pk::array<pk::building@> arr_target_base = pk::list_to_array(list_target_base);
            for (int i = 0; i < int(arr_target_base.length); i++)
            {
                list_attack_base.clear();
                pk::building@ dst_base = arr_target_base[i];
            
                bool cmd = PushAttackSupport(dst_base, force);
            }
            
            // �� ���� ���� ������ : �����ϴ� ������, �δ�� ������Ʈ
            clear_engage_info();
            update_engage_info();
            list_target_base.clear();
            list_attack_base.clear();
        }
        
        
        
        //---------------------------------------------------------------------------------------
        
        // �������� �������� ���� �δ����� ����
        bool PushAttackSupport(pk::building@ dst_base, pk::force@ force)
        {
            // ���� �δ밡 ������ �α� ������ �ִ��� Ȯ��
            int src_target = getNearestReinforce(dst_base, force, /*has_person*/true);
			if (src_target == -1) return false;
            
            // ������ ���� ����
            pk::building@ src_base = pk::get_building(src_target);
            
            int city_id = pk::get_city_id(dst_base.pos);    // ������ ���� ����
            int status  = get_engage_status(city_id);   // ��-�� ������ : �������� ������ ���, �������� ������ ����
            string status_info = "";
            
            bool cmd = false;
            if ((2*ref_status) <= status and status < (4*ref_status))
            {   // ������ �켼
                status_info = "������ ���� �켼";
                int num_atk_support_unit = count_atk_unit_type(src_base, dst_base, �δ�����_����, /*siege_weapon*/false);
                int unit_type = (!��������_���ۺδ���� or pk::enemies_around(src_base) or num_atk_support_unit > max_unit_supply)? �δ�����_���� : �δ�����_����;
                cmd = (PushAttackUnit(dst_base, src_base, unit_type, /*siege_weapon*/false, /*max_unit*/1) or cmd); // ���� or ���ۺδ�
            }
            else if (0 <= status and status < (2*ref_status))
            {   // ���� ġ��
                status_info = "���� ġ��";
                int num_atk_support_unit = count_atk_unit_type(src_base, dst_base, �δ�����_����, /*siege_weapon*/true);
                bool siege = (!��������_����������� or pk::enemies_around(src_base) or num_atk_support_unit > max_unit_siege)? false : true;
                cmd = (PushAttackUnit(dst_base, src_base, �δ�����_����, /*siege_weapon*/siege, /*max_unit*/1) or cmd); // ���� or �����δ�
            }
            else if ((-1*ref_status) <= status and status < 0)
            {   // ������ �켼
                status_info = "������ ���� �켼";
                int max_unit = (pk::enemies_around(src_base))? 1 : max_unit_combat;
                cmd = (PushAttackUnit(dst_base, src_base, �δ�����_����, /*siege_weapon*/false, /*max_unit*/max_unit) or cmd); // �����δ�
            }
        
            if (����׸��)
            {
                pk::force@ def_force  = pk::get_force(dst_base.get_force_id());
                pk::force@ atk_force  = force;
                string dst_name       = pk::decode(pk::get_name(dst_base));
                string src_name       = pk::decode(pk::get_name(src_base));
                string def_force_name = pk::decode(pk::get_name(pk::get_person(def_force.kunshu)));
                string atk_force_name = pk::decode(pk::get_name(pk::get_person(atk_force.kunshu)));
                
                if (cmd)
                    pk::info(pk::format("{}��, {}�� {} ���� ��, {} ({}���� �ĺ�)", atk_force_name, def_force_name, dst_name, status_info, src_name));
            }
            return true;
        }
        
        int ref_status = 10000;    // �������_���غ���
        int max_unit_combat = pk::max(1, pk::min(3, ��������_�����δ��));
        int max_unit_supply = pk::max(1, pk::min(3, ��������_���ۺδ��));
        int max_unit_siege  = pk::max(1, pk::min(5, ��������_�����δ��));
        
        
        bool PushAttackUnit(pk::building@ dst_base, pk::building@ src_base, int attack_type, bool siege_weapon=false, int max_unit=1)
        {
            // ���� ���� ����
            int src_id = src_base.get_id();
            int dst_id = dst_base.get_id();

            // ���� ��� ����
            int unit_count = 0;
            int push_count = 0;  // push Ƚ�� Ȯ�� ����
            
            if (dst_id >= �ǹ�_���ó�)   // ����/������ �� �������� 1�δ븸
                max_unit = 1;
                
            // ������������ �ݺ������� ���� ��� ����
            while(unit_count < max_unit and push_count < max_unit)
            {
                push_count += 1;
                
                if (attack_type == �δ�����_����)
                {
                    int unit_id = PushTransportUnit(src_base, dst_base, true);  // ���ۺδ� ����
                    if (unit_id != -1)
                    {
                        unit_count += 1;     // ���ۺδ� ī��Ʈ
                        if (!list_attack_base.contains(src_base))
                            list_attack_base.add(src_base);
                    }
                }
                else if (attack_type == �δ�����_���� and !siege_weapon)
                {
                   int unit_id = PushCombatUnit(src_base, dst_base, true);     // �����δ� ����
                    if (unit_id != -1)
                    {
                        unit_count += 1;     // �����δ� ī��Ʈ
                        if (!list_attack_base.contains(src_base))
                            list_attack_base.add(src_base);
                    }
                }
                else if (attack_type == �δ�����_���� and siege_weapon)
                {
                    int unit_id = PushSiegeUnit(src_base, dst_base, true);     // �����δ� ����
                    if (unit_id != -1)
                    {
                        unit_count += 1;     // �����δ� ī��Ʈ
                        if (!list_attack_base.contains(src_base))
                            list_attack_base.add(src_base);
                    }
                }
            }
            if (unit_count > 0) return true;
            
			return false;
        }
        
        // ��ǥ �� �������� ���� ���� �δ��
        int count_atk_unit_type(pk::building@ src_base, pk::building@ dst_base, int check_type, bool siege_weapon=false)
        {
            int count = 0;
            if (!pk::is_alive(src_base) or !pk::is_alive(dst_base)) return -1;
            int src_id = src_base.get_id();
            int dst_id = dst_base.get_id();
            if (src_id == dst_id) return -1;
            
            pk::district@ district = pk::get_district(src_base.get_district_id());
            pk::array<pk::unit@> arr_unit = pk::list_to_array(pk::get_unit_list(district));
            for (int i = 0; i < int(arr_unit.length); i++)
            {
                pk::unit@ unit = arr_unit[i];
                int service_id = pk::get_service(unit);
                
                bool is_valid_type = false;
                if (check_type == �δ�����_����)
                    is_valid_type = (unit.type == check_type);
                else if (check_type == �δ�����_����)
                {
                    if (siege_weapon and is_siege_weapon(pk::get_ground_weapon_id(unit)))
                        is_valid_type = (unit.type == check_type);
                    else if (!siege_weapon and !is_siege_weapon(pk::get_ground_weapon_id(unit)))
                        is_valid_type = (unit.type == check_type);
                }
                
                if (is_valid_type and service_id == src_id and unit.target_type == �δ��ӹ����_����)
                {
                    pk::building@ building_t = pk::get_building(unit.target);
                    if (pk::is_alive(building_t) and building_t.get_id() == dst_id and pk::is_enemy(unit, building_t))
                        count++;
                }
            }
            return count;
        }
        
        
        
        //---------------------------------------------------------------------------------------
        // ������ ���� ��Ȳ ������Ʈ
        //---------------------------------------------------------------------------------------
        
        // ��������
        array<int> def_troopsbase(�ǹ�_���ó�, 0);   // ���� �� ��������
        array<int> def_troops_sum(�ǹ�_���ó�, 0);   // ���� �� ���� ������
        array<int> def_unit_count(�ǹ�_���ó�, 0);   // ���� �� ���� �δ��
        array<int> atk_troops_sum(�ǹ�_���ó�, 0);   // ���� �� ���ݱ� ������
        array<int> atk_unit_count(�ǹ�_���ó�, 0);   // ���� �� ���ݱ� �δ��
        
        // �� ���� ���� ������ : �������� �ʱ�ȭ
        void clear_engage_info()
        {
            for (int city_id = 0; city_id < �ǹ�_���ó�; city_id++)
            {
                def_troopsbase[city_id] = 0;
                def_troops_sum[city_id] = 0;
                def_unit_count[city_id] = 0;
                atk_troops_sum[city_id] = 0;
                atk_unit_count[city_id] = 0;
            }
        }
        
        // �� ���� ���� ������ : �����ϴ� ������, �δ�� ������Ʈ
        void update_engage_info()
        {
            pk::array<pk::unit@> arr_unit = pk::list_to_array(pk::get_unit_list());
            for (int i = 0; i < int(arr_unit.length); i++)
            {
                pk::unit@ unit = arr_unit[i];
                int unit_id = unit.get_id();
                int city_id = pk::get_city_id(unit.pos);    // �δ밡 ��ġ�� ��ǥ ������ ����
                if (city_id >= 0 and city_id <= �ǹ�_���ó�)
                {
                    pk::city@ city = pk::get_city(city_id);
                    if (unit.get_force_id() == city.get_force_id()) // �δ�� ������ ���� ����
                    {
                        def_troops_sum[city_id] += unit.troops; // ���� ���񺴷���
                        def_unit_count[city_id] += 1;           // ���� ����δ��
                    }
                    else if (pk::is_enemy(unit, city))          // �δ�� ������ ���뼼��
                    {
                        atk_troops_sum[city_id] += unit.troops; // ���� ���ݺ�����
                        atk_unit_count[city_id] += 1;           // ���� ���ݺδ��
                    }
                }
            }
            for (int city_id = 0; city_id < �ǹ�_���ó�; city_id++)
            {
                pk::city@ city = pk::get_city(city_id);
                def_troopsbase[city_id] = pk::get_troops(city);
            }
        }
        
        // ħ���� ���δ� ���¼��� Ȯ��
        bool is_invaded_base(pk::building@ base)
        {
            if (!pk::is_alive(base)) return false;
            
            int city_id = pk::get_city_id(base.pos);
            if (atk_unit_count[city_id] == 0) return false;
            
            if (atk_unit_count[city_id] <= 2 and get_engage_status(city_id) < 0) return false;
            
            return true;
        }
        
        // ħ���� ���� Ȯ��
        int get_force_invaded(pk::building@ base)
        {
            // ���� �� �� �δ���� �Ҽ� ���� ī��Ʈ
            pk::array<int> arr_force_unit_count(����_��, 0);
            pk::array<pk::point> range = pk::range(base.pos, 1, 6);
            for (int i = 0; i < int(range.length); i++)
            {
                pk::unit@ unit = pk::get_unit(range[i]);
                if (pk::is_alive(unit) and pk::is_enemy(unit, base))
                    arr_force_unit_count[unit.get_force_id()]++;
            }
            // ���� ���� ���δ��� �ҼӼ��� ��ȯ
            int max_force_id    = -1;
            int max_force_count = -1;
            for (int j = 0; j < ����_��; j++)
            {
                int count = arr_force_unit_count[j];
                if (max_force_count < count)
                {
                    max_force_count = count;
                    max_force_id = j;
                }
            }
            
            if (max_force_count <= 0) return -1;
            if (!pk::is_normal_force(max_force_id)) return -1;
            
            return max_force_id;
        }
        
        // ���� ���� �� ���
        int get_engage_status(int city_id)
        {
            if (city_id < 0 and city_id > �ǹ�_���ó�) return 0;
            
            int def_base_troops = def_troopsbase[city_id];
            int def_unit_troops = def_troops_sum[city_id];
            int atk_unit_troops = atk_troops_sum[city_id];
            
            int status = atk_unit_troops - (def_base_troops + def_unit_troops);
            return status;      // �������� ������ ���, �������� ������ ����
        }
        
        
        
        //---------------------------------------------------------------------------------------
        
        string get_order_info(int order)
        {
            string name;
            switch(order)
            {
                case 0  : name = "�δ��ӹ�_���"; break;
                case 1  : name = "�δ��ӹ�_�̵�"; break;
                case 2  : name = "�δ��ӹ�_��ġ"; break;
                case 3  : name = "�δ��ӹ�_����"; break;
                case 4  : name = "�δ��ӹ�_��"; break;
                case 5  : name = "�δ��ӹ�_����"; break;
                case 6  : name = "�δ��ӹ�_ȣ��"; break;
                case 7  : name = "�δ��ӹ�_����"; break;
                case 8  : name = "�δ��ӹ�_����"; break;
                case 9  : name = "�δ��ӹ�_����"; break;
                case 10 : name = "�δ��ӹ�_����"; break;
                case 11 : name = "�δ��ӹ�_����"; break;
                case 12 : name = "�δ��ӹ�_����"; break;
                case 13 : name = "�δ��ӹ�_��" ; break;
                default : name = "�δ��ӹ�_����"; break;
            }
            
            return name;
        }
        
        //---------------------------------------------------------------------------------------
        bool ����׸�� = false;
        
        
        
        
	};

	Main main;
}