/*
// �ۼ���: �⸶å��
// Update: '20.10.21    / ���ʳ��� : ���� ����/�ױ� �� ���� �������� ��ݺδ� ����

*/


namespace �������
{
    
    //=======================================================================================
    // ����/�ױ� �� ���� (by �⸶å��)
    const bool �����ױ�_���� = true;        // true=����, false=������ (�뺴,����,����: �Ĺ����� ����)
    
    const int  �������_�ִ������δ�� = 2;       // �� �������� �������� ������� ������ �δ�� (1~3)
    const int  �������_�����ּҺ��� = 3500;     // �ش� ����/�ױ����� ���� �� ���� �ּҺ���
    const int  �������_�����ּҺ��� = 2000;     // ������ �δ��� �ּҺ��� ����
    const int  �������_�����ִ뺴�� = 5000;     // ������ �δ��� �ִ뺴�� ����
    
    //=======================================================================================
    
	class Main
	{

		Main()
		{
			@prev_callback_261 = cast<pk::func261_t@>(pk::get_func(261));
			pk::reset_func(261);
			pk::set_func(261, pk::func261_t(callback_261));
            
		}
        
		pk::func261_t@ prev_callback_261;
        array<bool> arr_base_defence(�ǹ�_������, false);
        
        
        //---------------------------------------------------------------------------------------
        
        // AI���� ��ũ��Ʈ
		bool callback_261(pk::force@ force)
		{
			int force_id = force.get_id();
            if (!pk::is_campaign())
			{
                // �÷��̾�, �̹��� ������ ����, ���̵� Ư�� �ÿ��� ����
                if (!force.is_player() and pk::is_normal_force(force_id) and pk::get_scenario().difficulty == ���̵�_Ư��)
                {
                    if (�����ױ�_����) func_base_defence(force);
                }
			}

			// ���� �ڵ鷯�� �ִٸ� ü��.
			if (prev_callback_261 !is null)
				return prev_callback_261(force);
            
			return false;
		}
        
        
        
        
        //=======================================================================================
        //      ������� �δ�����        
        //---------------------------------------------------------------------------------------
        
        //----- ������� �����Լ�
        void func_base_defence(pk::force@ force)
        {
            int force_id = force.get_id();
            for (int i = �ǹ�_��������; i < �ǹ�_�ױ���; i++)
            {
                arr_base_defence[i] = false;
                
                pk::building@ base = pk::get_building(i);
                pk::district@ district = pk::get_district(base.get_district_id());
                
                bool cmd = false;
                if (base.get_force_id() == force_id and enemy_unit_around(base))
                {
                    if (����׸��) pk::info(pk::format("�����ױ����: {}", pk::decode(pk::get_name(base)) ));
                    
                    int max_count = pk::max(1, pk::min(3, �������_�ִ������δ��));
                    for (int push_count = 0; push_count < max_count; push_count++)
                        cmd = (PushCoveringUnit(base) or cmd);
                }
                
                if (cmd) arr_base_defence[i] = true;
            }
        }
        
        // ***** �� ���� ��� ***** //
        bool PushCoveringUnit(pk::building@ src_base)
		{
            // �δ� �����ǥ ����
            pk::point dst_pos = get_dst_pos_nearby(src_base);
            if (dst_pos == -1) return false;
            
            // ���ݸ�ǥ�δ� ����
            pk::unit@ target = list_enemy_unit[0];
            
            // �����δ� ����
            int unit_id = PushRangeDefUnit(src_base, dst_pos, target, true);     
            if (unit_id != -1) return true;
            
			return false;
		}
        
        /** �� �����ʿ� �Ǵ� **/
        bool enemy_unit_around(pk::building@ base)
		{
            if (!pk::is_alive(base)) return false;
            int base_type = base.facility;
            if (base_type != �ü�_���� and base_type != �ü�_�ױ�) return false;
            
            list_enemy_unit.clear();
            
            int enemy_troops = 0;   // ������ ������ ���δ� �� Ȯ�� �߰�
            pk::array<pk::point> range = pk::range(base.pos, 1, 1);
			for (int i = 0; i < int(range.length); i++)
			{
				pk::unit@ unit = pk::get_unit(range[i]);
				if (pk::is_alive(unit) and pk::is_enemy(base, unit) and !list_enemy_unit.contains(unit))
                {
                    enemy_troops += unit.troops;
                    list_enemy_unit.add(unit);
                }
			}
            int count = pk::get_idle_person_list(base).count;
            if (count > 0 and pk::get_troops(base) >= (�������_�����ּҺ��� + �������_�����ּҺ���) and list_enemy_unit.count > 0 and enemy_troops >= 4000) 
                return true;
            
            return false;
        }
        
        //----------------------------------------------------------------------------------
        
        pk::list<pk::unit@> list_enemy_unit;
        pk::list<pk::person@> person_list;
        
        
        // �ֺ��� �� ��ǥ Ȯ��
        pk::point get_dst_pos_nearby(pk::building@ base)
        {
            pk::array<pk::point> arr_empty_pos;
            pk::array<pk::point> arr_neighbor_pos = pk::range(base.pos, 1, 1);
            for (int i = 0; i < int(arr_neighbor_pos.length); i++)
            {
                pk::point neighbor_pos = arr_neighbor_pos[i];
                if (pk::is_valid_pos(neighbor_pos))
                {
                    pk::hex@ hex = pk::get_hex(neighbor_pos);
                    int terrain_id = hex.terrain;
                    if (pk::is_enabled_terrain(terrain_id) and !hex.has_building and !hex.has_unit)
                    {
                        bool check = true;
                        pk::array<pk::unit@> arr_unit = pk::list_to_array(list_enemy_unit);
                        for (int j = 0; j < int(arr_unit.length); j++)
                        {
                            if (!check or (pk::get_distance(neighbor_pos, arr_unit[j].pos) < 2))
                                check = false;
                            if (!check or bool(pk::core["����"][terrain_id]["�̵�����"]) == false)
                                check = false;
                            if (!check or terrain_id == ����_�� or terrain_id == ����_����)
                                check = false;
                            if (!check or pk::is_on_fire(neighbor_pos))
                                check = false;
                        }
                        if (check)
                            arr_empty_pos.insertLast(neighbor_pos);
                    }
                }
            }
            if (int(arr_empty_pos.length) == 0) return -1;
            
            pk::point dst_pos = arr_empty_pos[0];
            
            return dst_pos;
        }
        
        
        //----------------------------------------------------------------------------------
        
        // �����δ� ���� ó��
        int amt_siege_wpn;
        int amt_range_wpn;
        int amt_dragn_wpn;
        
        int PushRangeDefUnit(pk::building@ src_base, pk::point dst_pos, pk::unit@ target, bool do_cmd = true)
        {
            if (!pk::is_alive(src_base) or !pk::is_valid_pos(dst_pos) or !pk::is_alive(target)) return -1;
            pk::hex@ hex = pk::get_hex(dst_pos);
            if (hex.has_building or hex.has_unit) return -1;    // �̵��Ұ���ǥ
            if (pk::get_distance(src_base.pos, dst_pos) != 1) return -1;
            
            // ��ǥ��ǥ�� �������� Ȯ��
            int terrain_id = pk::get_hex(dst_pos).terrain;
            if (!pk::is_enabled_terrain(terrain_id)) return -1;
            bool is_water_pos = pk::is_water_terrain(terrain_id);

            int src_troops = pk::get_troops(src_base);
            int ref_troops = �������_�����ּҺ���;
            if (src_troops <= (ref_troops + �������_�����ּҺ���)) return -1;    // ���� ����
            
            person_list = pk::get_idle_person_list(src_base);
            if (person_list.count == 0) return -1;   // ���� ����

            // ���� ����, Ư�� ���, ���+���� ���� ������ ����.
			func_sort_person_list();
            pk::person@ leader = pk::get_person(person_list[0].get_id());
            
            // ���Ÿ� ���� ���� ���� Ȯ��
            int siege_rng_id = (pk::has_tech(src_base, �ⱳ_��������))? ����_���� : ����_����;
            main.amt_siege_wpn = pk::get_weapon_amount(src_base, siege_rng_id);
            main.amt_range_wpn = pk::get_weapon_amount(src_base, ����_��);
            main.amt_dragn_wpn = (pk::has_tech(src_base, �ⱳ_���) or pk::has_skill(leader, Ư��_�鸶))? pk::get_weapon_amount(src_base, ����_����) : 0;
            if ((main.amt_range_wpn + main.amt_siege_wpn + main.amt_dragn_wpn) == 0) return -1;
            
            // �� ���� ���� : ���� ���� �ʰ���, ���ְ��ɺ��� Ȯ��
            int def_troops = pk::min(�������_�����ִ뺴��, pk::get_command(leader), pk::max(1, src_troops - ref_troops));
            
            // ���� ���� ����
            int ground_weapon_id = ����_��;    // ���󺴰� �ӽ�����
            int water_weapon_id = ����_�ְ�;
            if (!is_water_pos or leader.tekisei[����_����] == ����_C)
                water_weapon_id = ����_�ְ�;
            else if (is_water_pos)
            {
                if      (pk::get_weapon_amount(src_base, ����_����) > 0) water_weapon_id = ����_����;
                else if (pk::get_weapon_amount(src_base, ����_����) > 0) water_weapon_id = ����_����;
                else water_weapon_id = ����_�ְ�;
            }
            int unit_troops = def_troops;
            
            // ���� ���� ����
            if (!is_water_pos) get_range_weapon(src_base, leader, def_troops, ground_weapon_id, unit_troops);
            if (!is_water_pos and ground_weapon_id == 0) return -1;    // ���� ����
            
            // ���� ���
            int unit_food = int(pk::min(2.0f * unit_troops, pk::max( 0.5f * pk::get_food(src_base), 1.2f * unit_troops)));
            if (unit_food < int(0.5f * unit_troops)) return -1;   // ���� ����
            
            // ���� �̵��������� Ȯ��
            if (bool(pk::core["����"][terrain_id]["�̵�����"]) == false) return -1;
            int terrain_weapon_id = (is_water_pos)? water_weapon_id : ground_weapon_id;
            int movement_cost = pk::get_equipment(terrain_weapon_id).movement_cost[terrain_id];
            if (movement_cost < 0 or movement_cost >= 255) return -1;
            
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
                
                //cmd.order = �δ��ӹ�_�̵�;        // �δ� ����
                //cmd.target_pos = dst_pos;  // ��ǥ ����
                
                cmd.order = �δ��ӹ�_����;        // �δ� ����
                cmd.target_pos = target.pos;  // ��ǥ ����

                // ���� �̵�
                int unit_id = pk::command(cmd);
                if (unit_id == -1) return -1;
                
                pk::unit@ unit_cmd = pk::get_unit(unit_id);
                if (pk::is_alive(unit_cmd))
                {
                    //unit_cmd.action_done = false;   // �δ� ���� �� �α� ���δ븦 �����ϱ� ���� �ൿ �̿Ϸ�� ����
                    //pk::set_order(unit_cmd, �δ��ӹ�_����, target.pos);
                    //pk::run_order(unit_cmd);
                    
                    unit_cmd.action_done = true;    // �δ� �ൿ�Ϸ�� ����
                    
                    if (����׸��) 
                    {
                        string src_name      = pk::decode(pk::get_name(src_base));
                        string unit_name     = pk::decode(pk::get_name(leader));
                        string weapon_name   = get_weapon_name(unit_cmd.weapon);
                        pk::person@ target_p = pk::get_person(target.leader);
                        string target_name   = (pk::is_alive(target_p))? pk::decode(pk::get_name(target_p)) : "";
                        string order_str     = get_order_info(unit_cmd.order);
                        pk::info(pk::format("������: {}��({}), {} �α�({},{})���� {}�� ���", unit_name, weapon_name, src_name, unit_cmd.pos.x, unit_cmd.pos.y, target_name));
                    }
                    return unit_id;
                }
            }
            
            return -1;
        }
        
        // �뺴��� ��������
        bool cmd_archer = false;    
        
        
        void func_sort_person_list()
        {
            person_list.sort(function(a, b)
			{
                // �뺴 Ư�� �ݿ� ('20.9.13)
                if (main.amt_range_wpn > 0)
                {
                    bool a_archer = (pk::has_skill(a, Ư��_�ý�) or pk::has_skill(a, Ư��_����) or pk::has_skill(a, Ư��_���));
                    bool b_archer = (pk::has_skill(b, Ư��_�ý�) or pk::has_skill(b, Ư��_����) or pk::has_skill(b, Ư��_���));
                    if ( a_archer and !b_archer) return true;   
                    if (!a_archer and  b_archer) return false;  
                    // �뺴 ����
                    if (a.tekisei[����_�뺴] != b.tekisei[����_�뺴]) return (a.tekisei[����_�뺴] > b.tekisei[����_�뺴]);
                }
                // ���� Ư�� ���
                else if (main.amt_siege_wpn > 0)
                {
                    bool a_skill = (pk::has_skill(a, Ư��_����) or pk::has_skill(a, Ư��_����) or pk::has_skill(a, Ư��_����));
                    bool b_skill = (pk::has_skill(b, Ư��_�ý�) or pk::has_skill(b, Ư��_����) or pk::has_skill(b, Ư��_����));
                    if ( a_skill and !b_skill) return true;   
                    if (!a_skill and  b_skill) return false;  
                    // ���ȸ�� Ư�� ���
                    bool a_energy = (pk::has_skill(a, Ư��_�־�) or pk::has_skill(a, Ư��_�û�) or pk::has_skill(a, Ư��_���));
                    bool b_energy = (pk::has_skill(b, Ư��_�־�) or pk::has_skill(b, Ư��_�û�) or pk::has_skill(b, Ư��_���));
                    if ( a_energy and !b_energy) return true;   
                    if (!a_energy and  b_energy) return false;  
                    // ���� ����
                    if (a.tekisei[����_����] != b.tekisei[����_����]) return (a.tekisei[����_����] > b.tekisei[����_����]);
                }
                // �鸶 Ư�� ���
                else if (main.amt_dragn_wpn > 0)
                {
                    bool a_dragn = (pk::has_skill(a, Ư��_���) or pk::has_skill(a, Ư��_����) or pk::has_skill(a, Ư��_�鸶));
                    bool b_dragn = (pk::has_skill(b, Ư��_���) or pk::has_skill(b, Ư��_����) or pk::has_skill(b, Ư��_�鸶));
                    if ( a_dragn and !b_dragn) return true;   
                    if (!a_dragn and  b_dragn) return false;  
                    // �뺴 ����
                    if (a.tekisei[����_�⺴] != b.tekisei[����_�⺴]) return (a.tekisei[����_�⺴] > b.tekisei[����_�⺴]);
                }
                // ���� �ɷ�
                return (a.stat[����ɷ�_����] + a.stat[����ɷ�_���]) > (b.stat[����ɷ�_����] + b.stat[����ɷ�_���]);
			});
    }
        
        
        //----------------------------------------------------------------------------------
        
        // ���� ���� �Լ�
        void get_range_weapon(pk::building@ src_base, pk::person@ leader, int troops_max, int &out weapon_sel, int &out troops_sel)
        {
            int troops_min = �������_�����ּҺ���;
            int weapon_max = 0;
            int best_tekisei = ����_C;
            
            weapon_sel = ����_��;
            troops_sel = 0;
            
            // �뺴 ����
            if (main.amt_range_wpn > 0 and weapon_sel == ����_��)
            {
                int tekisei = leader.tekisei[pk::equipment_id_to_heishu(����_�뺴)];
                if (troops_min <= amt_range_wpn and ����_B <= tekisei)
                {
                    weapon_sel = ����_��;
                    troops_sel = pk::min(amt_range_wpn, troops_max);
                }
            }
            // ������������ ����
            else if (main.amt_siege_wpn > 0 and weapon_sel == ����_��)
            {
                weapon_sel = ����_��;
                troops_sel = pk::min(4000, troops_max);
            }
            // ��籺�� ����
            else if (main.amt_dragn_wpn > 0 and weapon_sel == ����_��)
            {
                if (troops_min <= amt_dragn_wpn)
                {
                    weapon_sel = ����_����;
                    troops_sel = pk::min(amt_dragn_wpn, troops_max);
                }
            }
            
            if (weapon_sel == ����_��)
            {
                troops_sel = troops_min;
            }
        }
        
        // ���� �Ӽ� Ȯ��
        bool is_dir_weapon(int weapon_id) { return ((����_�� <= weapon_id and weapon_id <= ����_����) and weapon_id != ����_��); }
        bool is_siege_weapon(int weapon_id) { return (����_���� <= weapon_id and weapon_id <= ����_���); }
        bool is_ship_weapon(int weapon_id) { return (weapon_id == ����_���� or weapon_id == ����_����); }
        
        
        //=======================================================================================
        
        
        
        
        string get_weapon_name(int weapon_id)
        {
            string weapon_name;
            switch(weapon_id)
            {
                case ����_��  : weapon_name = "�˺�"; break;
                case ����_â  : weapon_name = "â��"; break;
                case ����_��  : weapon_name = "�غ�"; break;
                case ����_��  : weapon_name = "�뺴"; break;
                case ����_���� : weapon_name = "�⺴"; break;
                case ����_���� : weapon_name = "����"; break;
                case ����_���� : weapon_name = "����"; break;
                case ����_���� : weapon_name = "����"; break;
                case ����_��� : weapon_name = "���"; break;
                case ����_�ְ� : weapon_name = "����"; break;
                case ����_���� : weapon_name = "����"; break;
                case ����_���� : weapon_name = "����"; break;
                default : weapon_name = "??"; break;
            }
            return weapon_name;
        }
        
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