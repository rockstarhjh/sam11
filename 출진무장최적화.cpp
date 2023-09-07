/*
// ������: �⸶å��
// Update: '19.1.11  / ��������: �����δ� ���� �� �ҼӰ����� ���ൿ ����� �ɷº��Ͽ� �δ����� ������
// Update: '19.1.21  / ���泻��: �ߺ� ���� ���� ����
// Update: '19.1.22  / ���泻��: ����/���� ������ȯ �Լ�����, ���ֺ��� ���濡 ���� �ҽ� ���� ������ȯ �߰�
// Update: '19.1.27  / ���泻��: ���� ���� �� ���� �¼� �缳�� �߰�
// Update: '19.2.9   / ���泻��: �ߺ� ���� ���� ���� (���������� Ȯ�� �߰�), ���庯�� �������� �� ����ġ �߰�, �δ� �� ����/���� �������� �߰�
// Update: '19.2.12  / ���泻��: �ߺ� ���� ���ó�� �� ���� �¼� �缳�� �߰�
// Update: '19.2.16  / ���泻��: �ߺ� ���� ���� ���� (���������� ��� ���� üũ), ���庯��� ����/���� �񱳼��� ����,
//                            ���� �ϼ��� �δ� �ƴ� ��� ���庯�� ���۾��ϵ��� ����, �Ǽ����� �Ǵ����� �߰�, 
// Update: '19.2.18  / ���泻��: �ߺ� ���� Ȯ�� �Լ� ���� (�� �δ뿡 ������ �ߺ� ���Ǵ� ��� �߰�)
// Update: '19.3.27  / ���泻��: ���ۺδ뿡 ���ؼ� ���ൿ Ư��_��� �������� ��ü��� �߰�
// Update: '19.5.13  / ���泻��: ���� ���� �� ������ ��ȿ�� �δ����� Ȯ�� ���� �߰�
// Update: '20.9.11  / ���泻��: ķ���ο����� ��ũ��Ʈ �������� �ʵ��� ����, �����ʰ����� ��ȯó�� Ÿ�̹� ����, 
//                            �ߺ��δ� ������� �Լ� ����, ���ڹ�ȯ �Լ��� ���ۺδ� �߰�, ���߹��� ������ ������ �߰�
// Update: '20.9.16  / ���泻��: ����Ư�� ��� ����ġ ����
*/

namespace ������������ȭ
{
    //---------------------------------------------------------------------------------------
    // ��������
    const int  ������������ȭ_�������� = 0;     // 0: ��ǻ��AI �� �÷��̾�_���ӱ��� ���,  1: �÷��̾�_���ӱ��ܸ�, 2: ��ǻ��AI��,  3: ��� ������
    const bool ������������ȭ_������������ = false;   // �������ǰ� ������ ���뿩�� ����, ������ ������ ���õǹǷ� false ����
    const bool ������������ȭ_��ȭǥ�� = true;

    //---------------------------------------------------------------------------------------
    // ������ �������� ���� �ɷ��� ���� �ִ� ��� ���� ���� ������
    const bool ������������ȭ_���庯�� = true;    // true=����,  false=������
    
    // ���ذ� ���� ������ ������ ��� ����
    const int ���庯��_�ɷ±��ذ� = 70;          
    
    // �������� �ɷ� �񱳿� ����ġ (������ �������� ����)
    const float ���庯��_��ְ���ġ = 0.8f;
    const float ���庯��_���°���ġ = 1.0f;
    const float ���庯��_���°���ġ = 0.5f;
    
    // ���庯�� �������� ���� ��� ('19.2.9)
    const bool ���庯��_������������ = true;      // ���������� ���� �� ���� ����
    const int  ���庯��_�������ذ� = 1;           // 0:����_C,   1:����_B,   2:����_A,   3:����_S �̻�
    const float ���庯��_��������ġ = 0.3f;
    
    // ���庯�� Ư�� ������ �켱 ��� ('20.9.16)
    const bool ���庯��_Ư�Ⱑ��ġ = true;    //true=����,  false=������
    
    // �Ǽ����� �Ǵ� ���� ('19.2.15)
    const bool �Ǽ�����_���ܼ��� = true;      // �Ǽ����� ���� ���� �� AI�δ� ���庯�� ���� (Ư��_�༺ ���� �Ǵ� ��/���� ���� �Ǵ�)
    const int �Ǽ�����_���ؼ����� = 1500;     // ���� ������ �̻� & ���� ���� ������ ��� �Ǽ��δ�� ����Ͽ� ���庯�� ����
    const int �Ǽ�����_���غ���  = 3000;     // ���� ������ �̻� & ���� ���� ������ ��� �Ǽ��δ�� ����Ͽ� ���庯�� ����
    
    //---------------------------------------------------------------------------------------
    // ����/���� �ɷ� ���Ͽ� �ɷ� �켱���� ������
    const bool ������������ȭ_�������� = false;     // true= ����,  false= ������
    const bool ��������_������� = false;         // true= �δ��̵� �� ���� ����,  false= �δ����� ���� ����
    const bool ��������_�������� = true;         // ������ ���� ���ְ��ɺ��� �����ϰ�, ��/�� �ɷ� �켱���� ���� ����
    
    //---------------------------------------------------------------------------------------
    
    
    
	class Main
	{
        
        Main()
		{
            pk::bind(102, pk::trigger102_t(onGameInit));
            pk::bind(111, pk::trigger111_t(onTurnStart));
            pk::bind(112, pk::trigger112_t(onTurnEnd));
            
            pk::bind(170, ������������ȭ_Ʈ����_�켱����, pk::trigger170_t(onUnitCreate));
            pk::bind(172, ������������ȭ_Ʈ����_�켱����, pk::trigger172_t(onUnitPosChange));
            
        }
        
        int ������������ȭ_Ʈ����_�켱���� = 100; // ���� �������� ���� ���� (�����δ�����ȭ.cpp ���� ���� ����ǵ��� ���� �ʿ�)
        
        pk::unit@ unit;
        pk::building@ base;
        pk::person@ old_leader;
        pk::person@ new_leader;
        int weapon_heishu = -1;
        bool flag_change_leader = false;
        bool flag_best_leader   = false;
        pk::list<pk::person@> idle_person_list;
        pk::list<pk::unit@> unit_list;
        pk::list<pk::person@> leader_list;
        pk::array<int> leader_location(����_��, -1);
        
        void onGameInit()
        {
            if (pk::is_campaign()) return;
            
            clear_leader_info();
        }
        
        void onTurnStart(pk::force@ force)
        {
            if (pk::is_campaign()) return;
            
            clear_leader_info();
            clear_exceed_amount_base();
        }
        
        void onTurnEnd(pk::force@ force)
        {
            if (pk::is_campaign()) return;
            if (!pk::is_alive(force) or !pk::is_normal_force(force)) return;  // �Ҽ� ���� Ȯ��  
            
            for (int i = 0; i < �ǹ�_������; i++)
            {
                pk::building@ base_t = pk::get_building(i);
                if (pk::is_alive(base_t) and force.get_id() == base_t.get_force_id())
                    restore_exceed_stocks(base_t);
            }
        }
        
        //---------------------------------------------------------------------------------------
        
        // �δ���� ��
        void onUnitCreate(pk::unit@ unit_t, int type)
        {
            if (pk::is_campaign()) return;
            
            // �������� �����δ����� Ȯ��
            if (!check_valid_unit(unit_t, type)) return ;
            // �������� ����ȭ�� ���� Ȯ��
            if (!check_force_option(unit_t)) return ;
            
            if (����׸��)
            {
                pk::building@ base_t = pk::get_building(pk::get_service(unit_t));
                if (pk::is_alive(base_t)) print_info_base(base_t);
                print_info_unit(unit_t);
            }
            
            // AI�Ǽ������� ��� ('19.2.15)
            if (�Ǽ�����_���ܼ��� and check_construction_unit(unit_t)) return ;
            
            // ���� ���� ���� �ʱ�ȭ (�������� �����)
            flag_change_leader = false;
            unit_list.clear();
            
            // �����δ� ���庯�� ����
            if (������������ȭ_���庯��)
            {
                bool need_leader_change = false;
                
                // ������ �δ������� ���� ����ȭ ���� �δ��� ������ ��� ���� ��ҽ�Ŵ ('19.1.21)
                // �ߺ� ���� Ȯ���� ���Ͽ� ��ü������ �ʱ�ȭ ���� ���·� Ȯ���� (�ߺ� ���� ���� ������!!)
                if (check_duplicated_unit(unit_t)) return;
            
                // ��ü���� ������Ʈ
                @unit = @unit_t;
                @base = pk::get_building(pk::get_service(unit));
                weapon_heishu = pk::equipment_id_to_heishu(unit.weapon);
                
                // ��� ������ ������ �ִ��� Ȯ��
                idle_person_list = pk::get_idle_person_list(base);
                if (idle_person_list.count == 0) return ;    // ���ൿ ���� ���� ����
                
                @old_leader = pk::get_person(unit.leader);
                
                // �����δ� ����
                if (unit.type == �δ�����_����)
                {
                    // ���庯�� ���ص� �Ǵ� ���� �ɷ�ġ Ȯ��
                    if (!check_leader_attr(unit)) return;
                    
                    // ���� �ɷ±��� ���� : ���+����(+����),(+����),(+Ư��) 
                    idle_person_list.sort(function(a, b)
                    {
                        int stat_a = main.get_stat_sum(a, true) + main.get_stat_tekisei(a) + main.get_stat_skill(a);
                        int stat_b = main.get_stat_sum(b, true) + main.get_stat_tekisei(b) + main.get_stat_skill(b);
                        return (stat_a > stat_b);
                    });
                    @new_leader = pk::get_person(idle_person_list[0].get_id());
                    
                    // ���� �ɷ� ���� ('19.2.15 ����)
                    int stat_new_leader = get_stat_sum(new_leader, true)  + get_stat_tekisei(new_leader);     // ���� ����/���� stat����
                    int stat_old_leader = get_stat_sum(old_leader, false) + get_stat_unit_tekisei(unit) 
                                          + int(���庯��_���°���ġ * pk::get_best_member_stat(unit, ����ɷ�_����));  // �δ� ����/���� stat ���� ('19.2.15)
                    
                    // ���� ���� ����
                    if (stat_old_leader < stat_new_leader)
                    {
                        need_leader_change = true;  // ���� �ʿ�
                    }
                }
                // ���ۺδ� ���� ('19.3.27)
                else if (unit.type == �δ�����_����)    
                {
                    if (unit.has_skill(Ư��_���)) return;  // �ҼӺδ� Ư��_��� Ȯ��
                    if (!pk::is_alive(pk::get_person(base.who_has_skill(Ư��_���)))) return;   // �ҼӰ��� Ư��_��� ���� Ȯ��
                    
                    // Ư��_��� ��� ����
                    idle_person_list.sort(function(a, b)
                    {
                        bool a_skill = pk::has_skill(a, Ư��_���);
                        bool b_skill = pk::has_skill(b, Ư��_���);
                        if ( a_skill and !b_skill) return true;
                        if (!a_skill and  b_skill) return false;
                        return  (float(a.stat[����ɷ�_��ġ]) / float(a.stat[����ɷ�_����])) > (float(b.stat[����ɷ�_��ġ]) / float(b.stat[����ɷ�_����]));
                    });
                    @new_leader = pk::get_person(idle_person_list[0].get_id());
                    
                    // ���� ���� ����
                    if (pk::has_skill(new_leader, Ư��_���))
                    {
                        need_leader_change = true;  // ���� �ʿ�
                    }
                }
                
                // ���� ���� ����
                // AI�δ� �������� ���� ('20.9.5)
                if (need_leader_change)
                {
                    bool chk_self_turn = (unit.get_force_id() == pk::get_current_turn_force_id())? true : false;
                    
                    // ��ǻ�� ����
                    if (!unit.is_player())
                    {
                        if (chk_self_turn) select_change_case(unit, 0);  // AI�� ������� ���ϹǷ� ���� ��� ����
                        else               select_change_case(unit, 1);  // ��ǻ�ͼ��� ���� Ȱ��ȭ �� ������� �����ϹǷ�, �δ밡 �ʵ�� �̵��� �Ŀ� ���� �����ϵ��� ��
                    }
                    // �÷��̾� ���� ���ӱ���
                    else if (unit.is_player() and !pk::is_player_controlled(unit))
                        select_change_case(unit, 0);  // AI�� ������� ���ϹǷ� ���� ��� ����
                    // �÷��̾� ���� ��������
                    else if (unit.is_player() and pk::is_player_controlled(unit) and ������������ȭ_������������)
                        select_change_case(unit, 1);  // �÷��̾� ������ ������� �����ϹǷ�, �δ밡 �ʵ�� �̵��� �Ŀ� ���� �����ϵ��� ��
                }
            }
            
            // ����/���� �ɷ� ���Ͽ� �ɷ� �켱 ����
            flag_best_leader = false;
            if (������������ȭ_��������) flag_best_leader = true;
            
        }
        
        // �δ� ��ǥ �̵� ��
        void onUnitPosChange(pk::unit@ unit_t, const pk::point &in pos)
        {
            if (pk::is_campaign()) return;
            
            // ��ȿ�δ����� Ȯ�� �߰� ('19.5.13)
            if (!pk::is_alive(unit_t) or pk::get_hex(pos).has_building)
            {
                flag_change_leader = false;
                flag_best_leader = false;
                unit_list.clear();
                return;
            }
            // change_case == 0 : 
            if (flag_change_leader and !unit_list.contains(unit_t))
            {
                say_leader_changed();
                flag_change_leader = false;
            }
            // change_case == 1 : �÷��̾� ������ ������� �����ϹǷ�, �δ밡 �ʵ�� �̵��� �Ŀ� ���� �����ϵ��� ��
            if (flag_change_leader and unit_list.contains(unit_t))
            {
                change_unit_leader();
                say_leader_changed();
                flag_change_leader = false;
                unit_list.clear();
            }
            
            
            // ����/���� �ɷ� ���Ͽ� �ɷ� �켱���� ������
            if (������������ȭ_�������� and (��������_������� or flag_best_leader))
            {
                set_best_leader(unit_t);
                flag_best_leader = false;
            }
            
        }
        
        //---------------------------------------------------------------------------------------
        // ���� ���� ������ ����
        void select_change_case(pk::unit@ unit_t, int change_case)
        {
            if (change_case == 0)   // AI auto
            {   // AI�� ������� ���ϹǷ� ���� ��� ����
                // �������� ��ġ���� ���� �����ϵ��� Ʈ���� �켱���� ���� �ʿ�
                change_unit_leader();   
                flag_change_leader = true;
                unit_list.clear();
                
                if (����׸��) pk::info("������������ȭ: ���ֻ��� ���� ���庯��");
            }
            else if (change_case == 1)  // user control
            {   // �����̵� Ʈ���ſ� ����, �����̵� �� ���� ���� �� ����/���� ��ȯ ����
                flag_change_leader = true;
                unit_list.add(unit_t);
                
                if (����׸��) pk::info("������������ȭ: �����̵� �� ���庯��");
            }
        }
            
        // ���� ���� �Լ�
        void change_unit_leader()
        {
            if (old_leader is null or new_leader is null) return;
            if (base is null or unit is null) return;
            
            string old_leader_name = pk::decode(pk::get_name(old_leader));
            string new_leader_name = pk::decode(pk::get_name(new_leader));
            string base_name       = pk::decode(pk::get_name(base));

            if (����׸��)
                pk::info(pk::format("������������ȭ: {}���� {} ��� {} ����", base_name, old_leader_name, new_leader_name));
            
            // �ʰ� ���ֺ��� ���� �Լ� ȣ��
            return_over_troops(base, unit, new_leader);
            
            // �Ҽ� ���� ���� : ���� location ���漳���� ���Ͽ� hex_obj ID ��ȯ
            old_leader.location = pk::get_hex_object_id(base);
            old_leader.update();
            unit.leader = new_leader.get_id();
            new_leader.location = pk::get_hex_object_id(unit);
            new_leader.update();
            unit.update();  // �δ뺴�� �� �δ�ɷ� ������Ʈ
            
            // ���� ���ൿ ����
            old_leader.action_done = false;
            new_leader.action_done = true;
            
            // �¼� �缳�� ('19.1.27)
            pk::reset_taishu(base);
            
            // ������ ���帮��Ʈ �� ��ġ���� �߰� ('19.2.16)
            leader_list.add(new_leader);
            leader_location[new_leader.get_id()] = new_leader.location;
            
        }
        
        void say_leader_changed()
        {
            if (!������������ȭ_��ȭǥ��) return;
            
            if (old_leader is null or new_leader is null) return;
            if (base is null or unit is null) return;
            
            string old_leader_name = pk::decode(pk::get_name(old_leader));
            string new_leader_name = pk::decode(pk::get_name(new_leader));
            string base_name       = pk::decode(pk::get_name(base));
            
            // �������� ����ȭ �ȳ� ��ȭâ
            pk::building@ service = pk::get_building(new_leader.service);
            if (pk::is_alive(service) and (new_leader.location != pk::get_hex_object_id(service)))
                pk::say(pk::encode(pk::format("\x1b[1x{}\x1b[0x�� ��� �� \x1b[1x{}\x1b[0x��(��)\n �����ϰڽ��ϴ�", old_leader_name, new_leader_name)), new_leader);
            
        }
        
        // ���ְ��ɺ��� ���� �� �ҼӰ������� ����/���� ��ȯ (���ۺδ�� ���ְ��ɺ��� ������)
        void return_over_troops(pk::building@ base_t, pk::unit@ unit_t, pk::person@ leader_t)
        {
            if (leader_t is null) return;
            if (base_t is null or unit_t is null) return;
            if (unit_t.type == �δ�����_����) return;    // ���ۺδ� ����
            
            int troops  = int(unit_t.troops);
            int command = int(pk::get_command(leader_t));


            if (troops > command)
            {
                int return_amount = troops - command;
                int weapon_id = pk::get_ground_weapon_id(unit_t);
                
                // �޽���
                string weapon_name = get_weapon_name(weapon_id);
                string base_name = pk::decode(pk::get_name(base_t));
                string unit_name = pk::decode(pk::get_name(new_leader));
                
                // ���� ��ȯ �� �ʰ����� Ȯ�� ('20.9.11)
                int exceed_troops = pk::max(0, (return_amount + pk::get_troops(base_t) - pk::get_max_troops(base_t)));
                
                // ���� ��ȯ ����
                pk::set_troops(unit_t, command);                  // �δ� ���� ���� ('20.9.7)
                pk::add_troops(base_t, +return_amount, false);    // ���� ���� ��ȯ
                unit_t.update();    // �δ����� �� �ɷ�ġ ������Ʈ
                
                // ���� ��ȯ (���� ����ϴ� â,��,��,������ �ش�)
                bool flag_exceed = false;
                int exceed_weapon = 0;
                if (����_â <= weapon_id and weapon_id <= ����_����)
                {
                    // ���� ��ȯ �� �ʰ����� Ȯ�� ('20.9.11)
                    exceed_weapon = pk::max(0, (return_amount + pk::get_weapon_amount(base_t, weapon_id) - pk::get_max_weapon_amount(base_t, weapon_id)));
                    // ���� ���� ��ȯ
                    pk::add_weapon_amount(base_t, weapon_id, return_amount, false);   
                }
                
                // ��ȯ�ʰ� ����/���� ���� ���� ('20.9.12, ������ �� �ϰ� ���ȯ)
                string exceed_info = pk::format("{}�� {} ��ȯ�ʰ� ", unit_name, base_name);
                if (exceed_troops > 0 or exceed_weapon > 0)
                {
                    flag_exceed = true;
                    int base_id = base_t.get_id();
                    is_exceed_base[base_id] = true;
                    exceed_amount_base[base_id][0]           += exceed_troops;   // ����
                    exceed_amount_base[base_id][3+weapon_id] += exceed_weapon;   // ����
                    
                    if (exceed_troops > 0) exceed_info += pk::format(",{}({})", arr_amount_name[0]          , exceed_troops);
                    if (exceed_weapon > 0) exceed_info += pk::format(",{}({})", arr_amount_name[3+weapon_id], exceed_weapon);
                }
                
                // ó�� ��� �޽���
                if (������������ȭ_��ȭǥ��)
                    pk::say(pk::encode(pk::format("���ֺ��濡 ���� \x1b[17x{} \x1b[1x{}��\x1b[0x�� \n\x1b[2x{}\x1b[0x(��)�� ��ȯ�ϰڽ��ϴ�", weapon_name, return_amount, base_name)), new_leader);

                if (����׸��)
                {
                    pk::info(pk::format("{}�� ���ֺ���: {} {}��({}��{}) {}(��)�� ��ȯ", unit_name, weapon_name, return_amount, troops, command, base_name));
                    
                    if (flag_exceed)
                        pk::info(pk::format("{}", exceed_info));
                    else
                        pk::info(pk::format("{}:����", exceed_info));
                }
            }
        }
        
        
        //---------------------------------------------------------------------------------------
        // ����׸�忡�� ����/�δ� ���� �ܼ�â�� ���
        void print_info_base(pk::building@ base_t)
        {        
            if (!pk::is_alive(base_t)) return;
            
            string base_name = pk::decode(pk::get_name(base_t));
            string wpn_info  = "";
            for (int i = 0; i < ����_��; i++)
            {
                int wpn_amt = pk::get_weapon_amount(base_t, i);
                if (wpn_amt > 0)
                    wpn_info += pk::format(",{}({})", pk::decode(pk::get_name(pk::get_equipment(i))), wpn_amt);
            }
                
            pk::info(pk::format("{} ���: ����({}),��({}),����({}){}", base_name, pk::get_troops(base_t), pk::get_gold(base_t), pk::get_food(base_t), wpn_info));
        }
        void print_info_unit(pk::unit@ unit_t)
        {
            if (!pk::is_alive(unit_t)) return;
            
            string unit_name = pk::decode(pk::get_name(pk::get_person(unit_t.leader)));
            int gnd_wpn_id   = pk::get_ground_weapon_id(unit_t);
            int sea_wpn_id   = pk::get_sea_weapon_id(unit_t);
            string gnd_wpn_name  = pk::decode(pk::get_name(pk::get_equipment(gnd_wpn_id)));
            string sea_wpn_name  = pk::decode(pk::get_name(pk::get_equipment(sea_wpn_id)));
            
            pk::info(pk::format("{}�� ����({},{},{})", unit_name, unit_t.troops, gnd_wpn_name, sea_wpn_name));
        }
        
        //---------------------------------------------------------------------------------------
        //---------------------------------------------------------------------------------------
        
        // �ߺ� �����δ����� Ȯ���ϰ� ���� ��ҽ�Ŵ
        bool check_duplicated_unit(pk::unit@ unit_t)
        {
            if (!pk::is_alive(unit_t)) return false;
            
            // �δ� ���� ���� ����
            pk::array<pk::person@> members(3, null);
            for (int i = 0; i < 3; i++)
            {
                pk::person@ member_t = pk::get_person(unit_t.member[i]);
                if (pk::is_alive(member_t))
                    @members[i] = @member_t;
            }
            
            // �ߺ� ���� ���� Ȯ�� �Լ� ('19.2.18)
            bool dupl_check = false;
            pk::list<pk::person@> dupl_leaders;
            dupl_leaders.clear();
            for (int i = 0; i < 3; i++)
            {
                if (leader_list.contains(members[i]))
                {
                    dupl_check = true;  // �ߺ� ��ȿ
                    dupl_leaders.add(members[i]);   // �ߺ�����Ʈ �߰�
                }
            }
            
            // �ߺ������� ���
            if (pk::is_alive(base) and dupl_check)
            {
                
                // ������� �Լ� --- ���ڹ�ȯ ��� ���� ('20.9.9)
                int unit_id   = unit_t.get_id();
                int leader_id = unit_t.leader;
                update_unit_cancel_info(unit_t, base);   // ��������� �δ��� �������� ����
                update_exceed_amount(unit_t, base);      // ���ڹ�ȯ �� �ʰ��Ǿ� ���ߵǴ� ���ڷ� ��� (������ �� �ٽ� ��ȯ)
                restore_unit_stocks(unit_id, leader_id); // �δ� ���ڹ�ȯ ����
                cancel_unit_march(unit_t);               // ������� ���� (�δ�����), ���� ���� ����
                
                if (����׸��) print_info_base(base);
                
                // ������ ���� �ൿ: ��������Ͽ����Ƿ� ���ൿ���� ���� ('19.2.18)
                for (int j = 0; j < 3; j++) // ����δ빫�� (�ִ�3�����)
                {
                    pk::person@ member_t = members[j];
                    if (pk::is_alive(member_t) and !dupl_leaders.contains(member_t))
                    {
                        member_t.location = pk::get_hex_object_id(base);
                        member_t.action_done = false;
                        member_t.update();
                    }
                }
                
                // �ߺ������� ������ ���� ������ �Լ� ('19.2.18)
                pk::array<pk::person@> arr_dupl = pk::list_to_array(dupl_leaders);
                for (int j = 0; j < int(arr_dupl.length); j++)
                {
                    pk::person@ dupl_leader = arr_dupl[j];
                    int location_id = leader_location[dupl_leader.get_id()];
                    pk::unit@ dupl_unit = pk::get_unit(pk::hex_object_id_to_unit_id(location_id));
                    if (pk::is_alive(dupl_unit))
                    {
                        dupl_leader.location = location_id;
                        dupl_unit.update();
                    }
                    else
                    {
                        dupl_leader.location = pk::get_hex_object_id(base);
                        base.update();
                    }
                    dupl_leader.action_done = true;
                }
                
                // �¼� ������Ʈ ('19.2.12)
                pk::reset_taishu(base);
                
                return true;
            }
            return false;
        }
        
        
        // ���� ��� �Լ�
        void cancel_unit_march(pk::unit@ unit_t)
        {
            string unit_name = pk::decode(pk::get_name(pk::get_person(unit_t.leader)));
            
            // �δ��ػ�
            pk::kill(unit_t);
            
            // �ൿ�� ��ȯ
            pk::district@ district = pk::get_district(base.get_district_id());
            district.ap += get_march_ap(base);
            
            if (����׸��)
                pk::info(pk::format("{}�� �ߺ��������", unit_name));
        }
        
        
        //---------------------------------------------------------------------------------------

        // ���� ��ȯ ���� �ʱ�ȭ
        array<int> unit_cancel_info(18, -1);
        void clear_unit_cancel_info()
        {
            for (int i = 0; i < 18; i++)
            {
                if (i < 3) unit_cancel_info[i] = -1;
                else unit_cancel_info[i] = 0;
            }
        }
        
        // ���� ��ȯ ���� �������� �� ���� (����ID, �ҼӰ���ID, Ÿ��, ����, ��, ����, ����_0~11)
        void update_unit_cancel_info(pk::unit@ unit_t, pk::building@ base_t)
        {
            if(!pk::is_alive(unit_t)) return;
            if(!pk::is_alive(base_t)) return;
            
            // ���� ��ȯ ���� �ʱ�ȭ
            clear_unit_cancel_info();
            
            // �δ� ���� ������Ʈ
            unit_cancel_info[0] = unit_t.get_id();
            unit_cancel_info[1] = base_t.get_id();
            unit_cancel_info[2] = unit_t.type;
            unit_cancel_info[3] = unit_t.troops;
            unit_cancel_info[4] = unit_t.gold;
            unit_cancel_info[5] = unit_t.food;
            
            if (unit_t.type == �δ�����_����)
            {
                // ���󺴱�
                int gnd_wpn_id = pk::get_ground_weapon_id(unit_t);
                int gnd_wpn_amount = 0;
                if     (����_���� <= gnd_wpn_id and gnd_wpn_id <= ����_���) gnd_wpn_amount = 1;
                else if (����_â <= gnd_wpn_id and gnd_wpn_id <= ����_����) gnd_wpn_amount = unit_t.troops;
                // �Լ�����
                int sea_wpn_id = pk::get_sea_weapon_id(unit_t);
                int sea_wpn_amount = (����_�ְ� < sea_wpn_id)? 1 : 0;
                
                unit_cancel_info[6] = gnd_wpn_id;
                unit_cancel_info[7] = gnd_wpn_amount;
                unit_cancel_info[8] = sea_wpn_id;
                unit_cancel_info[9] = sea_wpn_amount;
            }
            else if (unit_t.type == �δ�����_����)
            {
                for (int i = 0; i < 12; i++)
                    unit_cancel_info[6 + i] = unit_t.stock[i].amount;
            }            
        }
        
        // �δ����� �� �������� ���ڹ�ȯ �����Լ� (����ID �� Key������ �̿�)
        void restore_unit_stocks(int unit_id, int leader_id)
        {
            if (unit_cancel_info[0] != unit_id) return;
            
            // �δ� ���� ������Ʈ
            pk::building@ base_t = pk::get_building(unit_cancel_info[1]);   // ����
            int type   = unit_cancel_info[2];   // �δ����� (����, ����)
            int troops = unit_cancel_info[3];   // ����
            int gold   = unit_cancel_info[4];   // ��
            int food   = unit_cancel_info[5];   // ����
            
            string unit_name = pk::decode(pk::get_name(pk::get_person(leader_id)));
            string base_name = pk::decode(pk::get_name(base_t));
            
            // ����: �Ҽӵ��÷� ����/��/���� ���� �ǵ���
            pk::add_gold(base_t, gold, false);
            pk::add_food(base_t, food, false);
            pk::add_troops(base_t, troops, false);
            
            string restore_info = pk::format("����({}),��({}),����({})", troops, gold, food);
            
            if (type == �δ�����_����)
            {
                int gnd_wpn_id     = unit_cancel_info[6];
                int gnd_wpn_amount = unit_cancel_info[7];
                int sea_wpn_id     = unit_cancel_info[8];
                int sea_wpn_amount = unit_cancel_info[9];
                
                if (gnd_wpn_id > 0 and gnd_wpn_amount > 0)
                    pk::add_weapon_amount(base_t, gnd_wpn_id, gnd_wpn_amount, false);
                
                if (sea_wpn_id > ����_�ְ� and sea_wpn_amount > 0)
                    pk::add_weapon_amount(base_t, sea_wpn_id, sea_wpn_amount, false);
                
                string gnd_wpn_name = pk::decode(pk::get_name(pk::get_equipment(gnd_wpn_id)));
                string sea_wpn_name = pk::decode(pk::get_name(pk::get_equipment(sea_wpn_id)));
                restore_info += pk::format(",{}({}),{}({})", gnd_wpn_name, gnd_wpn_amount, sea_wpn_name, sea_wpn_amount);
            }
            else if (type == �δ�����_����)
            {
                for (int i = 0; i < ����_��; i++)
                {
                    int wpn_amount = unit_cancel_info[6 + i];
                    if (wpn_amount > 0)
                    {
                        pk::add_weapon_amount(base, i, wpn_amount, false);
                    
                        string wpn_name = pk::decode(pk::get_name(pk::get_equipment(i)));
                        restore_info += pk::format(",{}({})", wpn_name, wpn_amount);
                    }
                }
            }     
            
            if (����׸��)
                pk::info(pk::format("{}�� �ߺ��������, {}(��)�� {} ��ȯ", unit_name, base_name, restore_info));
            
            // ���� ��ȯ ���� �ʱ�ȭ
            clear_unit_cancel_info();
        }
        
        
        // ���� ��ȯ �Լ� ----- ���ۺδ� �߰� ('20.9.6) ... ������� ����
        void return_unit_stocks(pk::unit@ unit_t)
        {
            string unit_name = pk::decode(pk::get_name(pk::get_person(unit_t.leader)));
            string base_name = pk::decode(pk::get_name(base));
            
            // ����: �Ҽӵ��÷� ����/��/���� ���� �ǵ���
            pk::add_gold(base, unit_t.gold, false);
            pk::add_food(base, unit_t.food, false);
            pk::add_troops(base, unit_t.troops, false);
            
            string restore_info = pk::format("����({}),��({}),����({})", unit_t.troops, unit_t.gold, unit_t.food);
            
            // �����δ�: �Ҽӵ��÷� ����� ���� �ǵ���
            if (unit_t.type == �δ�����_����)
            {   
                // ���󺴱�
                int gnd_wpn_id = pk::get_ground_weapon_id(unit_t);
                int gnd_wpn_amount = 0;
                if     (����_���� <= gnd_wpn_id and gnd_wpn_id <= ����_���) gnd_wpn_amount = 1;
                else if (����_â <= gnd_wpn_id and gnd_wpn_id <= ����_����) gnd_wpn_amount = unit_t.troops;
                if (gnd_wpn_id > 0 and gnd_wpn_amount > 0)
                    pk::add_weapon_amount(base, gnd_wpn_id, gnd_wpn_amount, false);
                // �Լ�����
                int sea_wpn_id = pk::get_sea_weapon_id(unit_t);
                int sea_wpn_amount = (����_�ְ� < sea_wpn_id)? 1 : 0;
                if (sea_wpn_id > ����_�ְ� and sea_wpn_amount > 0)
                    pk::add_weapon_amount(base, sea_wpn_id, sea_wpn_amount, false);
                
                string gnd_wpn_name = pk::decode(pk::get_name(pk::get_equipment(gnd_wpn_id)));
                string sea_wpn_name = pk::decode(pk::get_name(pk::get_equipment(sea_wpn_id)));
                restore_info += pk::format(",{}({}),{}({})", gnd_wpn_name, gnd_wpn_amount, sea_wpn_name, sea_wpn_amount);
            }
            // ���ۺδ�: �Ҽӵ��÷� ����� ���� �ǵ���
            else if (unit_t.type == �δ�����_����)
            {   
                for (int i = 0; i < ����_��; i++)
                {
                    int wpn_amount = unit_t.stock[i].amount;
                    if (wpn_amount > 0)
                    {
                        pk::add_weapon_amount(base, i, wpn_amount, false);
                    
                        string wpn_name = pk::decode(pk::get_name(pk::get_equipment(i)));
                        restore_info += pk::format(",{}({})", wpn_name, wpn_amount);
                    }
                }
            }
            
            if (����׸��)
                pk::info(pk::format("{}�� �ߺ��������, {}(��)�� {} ��ȯ", unit_name, base_name, restore_info));
        }
        
        //---------------------------------------------------------------------------------------
        //---------------------------------------------------------------------------------------
        
        // ���� ��ȯ �� �ʰ��� �����ߴٰ� ������ �� �ϰ� �ݿ�
        array<bool> is_exceed_base(�ǹ�_������, false);
        array<array<int>> max_amount_base(�ǹ�_������, array<int>(15, 0));
        array<array<int>> exceed_amount_base(�ǹ�_������, array<int>(15, 0));
        array<string> arr_amount_name = {"����", "��", "����", "��", "â", "��", "��", "����", "����", "����", "����", "���", "�ְ�", "����", "����"};
        
        // ���� �ʰ��� ���� : ����, ��, ����, ����0~11
        void update_exceed_amount(pk::unit@ unit_t, pk::building@ base_t)
        {
            if (!pk::is_alive(base_t)) return;
            if (!pk::is_alive(unit_t)) return;
            
            update_max_amount_base(base_t);
            
            // --- ���� ���� ��� Ȯ��
            array<int> arr_amount_base(15, 0);
            arr_amount_base[0] = pk::get_troops(base_t);  // ����
            arr_amount_base[1] = pk::get_gold(base_t);    // ��
            arr_amount_base[2] = pk::get_food(base_t);    // ����
            for (int j = 0; j < ����_��; j++)
            {
                arr_amount_base[3 + j] = pk::get_weapon_amount(base_t, j);
            }
            
            // ��� �ʰ� ��ȯ�� ���
            string unit_name = pk::decode(pk::get_name(pk::get_person(unit_t.leader)));
            string base_name = pk::decode(pk::get_name(base_t));
            string exceed_info_t = pk::format("{}�� {} ��ȯ�ʰ� ", unit_name, base_name);
            string exceed_info   = exceed_info_t;
            
            int base_id = base_t.get_id();
            if (unit_t.type == �δ�����_����)
            {
                for (int i = 0; i < 15; i++)    // ����, ��, ����, ����0~11 �ʰ���
                {
                    int exceed_amount = pk::max(0, (arr_amount_base[i] + unit_cancel_info[3+i]) - max_amount_base[base_id][i]);
                    exceed_amount_base[base_id][i] += exceed_amount;
                    
                    if (exceed_amount > 0) exceed_info += pk::format(",{}({})", arr_amount_name[i], exceed_amount);
                }
            }
            else if (unit_t.type == �δ�����_����)
            {
                for (int i = 0; i < 3; i++) // ����, ��, ���� �ʰ���
                {
                    int exceed_amount = pk::max(0, (arr_amount_base[i] + unit_cancel_info[3+i]) - max_amount_base[base_id][i]);
                    exceed_amount_base[base_id][i] += exceed_amount;
                    
                    if (exceed_amount > 0) exceed_info += pk::format(",{}({})", arr_amount_name[i], exceed_amount);
                }
                // �����δ� ���� �ʰ���
                int gnd_wpn_id     = unit_cancel_info[6];
                int gnd_wpn_amount = unit_cancel_info[7];
                int sea_wpn_id     = unit_cancel_info[8];
                int sea_wpn_amount = unit_cancel_info[9];
                
                int exceed_gnd_wpn = pk::max(0, (arr_amount_base[3+gnd_wpn_id] + gnd_wpn_amount) - max_amount_base[base_id][3+gnd_wpn_id]);
                int exceed_sea_wpn = pk::max(0, (arr_amount_base[3+sea_wpn_id] + sea_wpn_amount) - max_amount_base[base_id][3+sea_wpn_id]);
                
                exceed_amount_base[base_id][3+gnd_wpn_id] += exceed_gnd_wpn;
                exceed_amount_base[base_id][3+sea_wpn_id] += exceed_sea_wpn;
                
                if (exceed_gnd_wpn > 0) exceed_info += pk::format(",{}({})", arr_amount_name[3+gnd_wpn_id], exceed_gnd_wpn);
                if (exceed_sea_wpn > 0) exceed_info += pk::format(",{}({})", arr_amount_name[3+sea_wpn_id], exceed_sea_wpn);
            }

            // �ʰ����� �߻� ���� flag
            bool flag_exceed = false;
            if (exceed_info_t != exceed_info)
            {
                flag_exceed = true;
                is_exceed_base[base_id] = true;
            }
            
            if (����׸��)
            {
                if (flag_exceed)
                    pk::info(pk::format("{}", exceed_info));
                else
                    pk::info(pk::format("{}:����", exceed_info_t));
            }
        }
        
        // �ʰ� ���� ������ ��ȯ : ����, ��, ����, ����0~11
        void restore_exceed_stocks(pk::building@ base_t)
        {
            if (!pk::is_alive(base_t)) return;
            
            int base_id = base_t.get_id();
            if (!is_exceed_base[base_id]) return;   // �ʰ����� �̹߻� ���� ����
            
            pk::add_troops(base_t, exceed_amount_base[base_id][0], false); // ����
            pk::add_gold(base_t,   exceed_amount_base[base_id][1], false); // ��
            pk::add_food(base_t,   exceed_amount_base[base_id][2], false); // ����
            
            string base_name = pk::decode(pk::get_name(base_t));
            string restore_info = pk::format("����({}),��({}),����({})", exceed_amount_base[base_id][0], exceed_amount_base[base_id][1], exceed_amount_base[base_id][2]);
            
            for (int j = 0; j < ����_��; j++)
            {
                int exceed_amount = exceed_amount_base[base_id][3 + j];
                pk::add_weapon_amount(base_t, j, exceed_amount);    // ����
                
                string wpn_name = pk::decode(pk::get_name(pk::get_equipment(j)));
                if (exceed_amount > 0)
                    restore_info += pk::format(",{}({})", wpn_name, exceed_amount);
            }
            
            if (����׸��)
            {
                pk::info(pk::format("{} �ʰ����� ��ȯó��: {} ��ȯ", base_name, restore_info));
                print_info_base(base_t);
            }
        }
        
        // ���� �ִ밪 ������Ʈ
        void update_max_amount_base(pk::building@ base_t)
        {
            if (!pk::is_alive(base_t)) return;
            
            int base_id = base_t.get_id();
            max_amount_base[base_id][0] = pk::get_max_troops(base_t);  // ����
            max_amount_base[base_id][1] = pk::get_max_gold(base_t);    // ��
            max_amount_base[base_id][2] = pk::get_max_food(base_t);    // ����
            
            for (int j = 0; j < ����_��; j++)
            {
                max_amount_base[base_id][3 + j] = pk::get_max_weapon_amount(base_t, j);
            }
            
        }
        
        // ������ �ʰ� ��ȯ�� �ʱ�ȭ
        void clear_exceed_amount_base()
        {
            for (int i = 0; i < �ǹ�_������; i++)
            {
                is_exceed_base[i] = false;
                
                for (int j = 0; j < 15; j++)
                {
                    exceed_amount_base[i][j] = 0;
                }
            }
        }
        
        
        //---------------------------------------------------------------------------------------
        //---------------------------------------------------------------------------------------
        
        void set_best_leader(pk::unit@ unit_t)
        {
            if (!pk::is_alive(unit_t)) return ;
            
            // �������� ����ȭ�� ���� Ȯ��
            if (!check_force_option(unit_t)) return ;
            
            // ���� ������
            pk::person@ leader0 = pk::get_person(unit_t.leader);    // ���� ����
            pk::list<pk::person@> member_list;
            for (int i = 0; i < 3; i++)
            {
                pk::person@ person_t = pk::get_person(unit_t.member[i]);
                if (pk::is_alive(person_t))
                    member_list.add(person_t);
            }
            // �ܵ� �� �δ��� ��� �������
            if (member_list.count < 2) return;  
            
            // ���+���� ���� ���� ���� (����, ���� ����)
            member_list.sort(function(a, b)
            {
                int stat_a = main.get_stat_sum(a, false);
                int stat_b = main.get_stat_sum(b, false);
                int cmd_a = pk::get_command(a);
                int cmd_b = pk::get_command(b);

                if (��������_��������)  return (stat_a > stat_b);
                else   return ((cmd_a == cmd_b)? (stat_a > stat_b) : (cmd_a > cmd_b));
            });
            
            // �ʰ� ���ֺ��� ���� �Լ� ȣ��
            return_over_troops(base, unit_t, member_list[0]);
            
            // ����/���� ������
            for (int j = 0; j < int(member_list.count); j++)
            {
                unit_t.member[j] = member_list[j].get_id();
                unit_t.update();
            }
            pk::person@ leader1 = pk::get_person(unit_t.leader);    // �� ����
            
            // �δ����� ����ȭ �ȳ� ��ȭâ
            if (������������ȭ_��ȭǥ�� and leader0.get_id() != leader1.get_id() )
            {
                string old_leader_name = pk::decode(pk::get_name(leader0));
                string new_leader_name = pk::decode(pk::get_name(leader1));
                pk::say(pk::encode(pk::format("�������� \x1b[1x{}\x1b[0x�� ���\n\x1b[1x{}\x1b[0x��(��) �δ븦 �����ϰڽ��ϴ�", old_leader_name, new_leader_name)), leader1);
            }
        }
        
        //---------------------------------------------------------------------------------------
        
        // �������� �����δ����� Ȯ��
        bool check_valid_unit(pk::unit@ unit_t, int type)
        {
            if (!pk::is_alive(unit_t))      return false;
            if (type != 0)                  return false;	// ���� �δ밡 �ƴ� ��� ���� (���� ���� �δ�)
			
            if (unit_t.attr.stat[�δ�ɷ�_�̵�] < 2)	return false;	// 2ĭ �̻� �̵��Ұ� �� �δ���� �ڵ� ��� (�̵��� 2~4 = ���� 1ĭ)
            if (pk::get_service(unit_t) >= �ǹ�_������) return false;      // �Ҽ� ���� Ȯ��
            
            int force_id = unit_t.get_force_id();
            pk::force@ force = pk::get_force(force_id);
			if (!pk::is_alive(force) or !pk::is_normal_force(force)) return false;  // �Ҽ� ���� Ȯ��  
            //if (force_id != pk::get_current_turn_force_id()) return false;  // ���� �ϼ��� �ƴ� ��� ('19.2.15)        
            
            return true;
        }
        
        // �������� ����ȭ�� ���� Ȯ��
        bool check_force_option(pk::unit@ unit_t)
        {
            // �÷��̾� ���� ������ (������ �δ��� �����ϸ鼭 �������ϹǷ� ������ ����)
            if (pk::is_player_controlled(unit_t)) 
            {
                if (������������ȭ_������������) return true;
                else return false;   
            }
            
            // 0: ��ǻ��AI �� �÷��̾�_���ӱ��� ���,  1: �÷��̾�_���ӱ��ܸ�, 2: ��ǻ��AI��,  3: ��� ������
            if      (������������ȭ_�������� == 0 and !pk::is_player_controlled(unit_t)) return true;
            else if (������������ȭ_�������� == 1 and unit_t.is_player() and !pk::is_player_controlled(unit_t)) return true;
            else if (������������ȭ_�������� == 2 and !unit_t.is_player()) return true;
            else if (������������ȭ_�������� == 3) return false;
            
            return false;
        }
        
        // �Ǽ����� ���� �Ǵ� ('19.2.15)
        bool check_construction_unit(pk::unit@ unit_t)
        {
            if (pk::is_player_controlled(unit_t)) return false; // ���������� ������ ����
            
            if (unit_t.has_skill(Ư��_�༺) and unit_t.gold >= �Ǽ�����_���ؼ�����) return true;  // �༺ Ư��
            
            if (unit_t.type == �δ�����_���� and pk::get_member_count(unit_t) <= 1)   // 1�δ�
            {
                if (unit_t.gold >= �Ǽ�����_���ؼ����� and unit_t.troops <= �Ǽ�����_���غ���) 
                    return true; 
            }
            return false;
        }
        
        // ���庯�� ���ص� �Ǵ� �δ�ɷ�ġ ���� Ȯ��
        bool check_leader_attr(pk::unit@ unit_t)
        {
            int stat_ref = int(���庯��_�ɷ±��ذ� * (���庯��_��ְ���ġ + ���庯��_���°���ġ + ���庯��_���°���ġ));
            
            pk::person@ leader_t = pk::get_person(unit_t.leader);
            
            // �񱳿� ����� ���°� ���� : �������� �� �δ����� ('19.2.15)
            //int stat_chk = get_stat_sum(leader_t, true);
            int stat_chk = get_stat_sum(leader_t, false) + int(���庯��_���°���ġ * pk::get_best_member_stat(unit_t, ����ɷ�_����));
            
            bool chk_tekisei = true;
            if (���庯��_������������)
            {
                //chk_tekisei = (leader_t.tekisei[weapon_heishu] > pk::max(0, pk::min(3, ���庯��_�������ذ�))); //��������
                chk_tekisei = (pk::get_tekisei(unit_t) > pk::max(0, pk::min(3, ���庯��_�������ذ�)));           //�δ�����
            }
            if (stat_chk > stat_ref and chk_tekisei) return false;
            
            return true;
        }
        
        //---------------------------------------------------------------------------------------
        
        // �δ����� �ൿ�� ���
        int get_march_ap(pk::building@ building)
        {
            pk::city@ city = pk::building_to_city(building);
            if (pk::is_alive(city))
            {
                if (pk::has_facility(city, �ü�_�����))
                    return 5;
            }
            return 10;
        }
        
        // ���� �ɷ�ġ ����
        int get_stat_sum(pk::person@ person_t, bool include_wisdom)
        {
            int stat = int(���庯��_��ְ���ġ * person_t.stat[����ɷ�_���] 
                         + ���庯��_���°���ġ * person_t.stat[����ɷ�_����]);
                         
            if (include_wisdom)
                stat += int(���庯��_���°���ġ * person_t.stat[����ɷ�_����]);
            
            return stat;
        }
        
        // ���� ���� �ɷ°���ġ ȯ��
        int get_stat_tekisei(pk::person@ person_t)
        {
            int stat = 0;
            int tekisei = person_t.tekisei[weapon_heishu];
            if (���庯��_������������)
            {
                int stat_base = (tekisei > pk::max(0, pk::min(3, ���庯��_�������ذ�)))? 30 : 0;
                stat = int(���庯��_��������ġ * (stat_base + 15 * pk::min(3, tekisei)));
            }
            return stat;
        }
        
        // �δ� ���� �ɷ°���ġ ȯ��
        int get_stat_unit_tekisei(pk::unit@ unit_t)
        {
            int stat = 0;
            int tekisei = pk::get_tekisei(unit_t, unit_t.weapon);
            if (���庯��_������������)
            {
                int stat_base = (tekisei > pk::max(0, pk::min(3, ���庯��_�������ذ�)))? 30 : 0;
                stat = int(���庯��_��������ġ * (stat_base + 15 * pk::min(3, tekisei)));
            }
            return stat;
        }
        
        // ���� Ư�� ����ġ ȯ��
        int get_stat_skill(pk::person@ person_t)
        {
            int stat = 0;
            if(���庯��_Ư�Ⱑ��ġ)
            {
                if (pk::has_skill(person_t, Ư��_����)) stat = pk::max(5, stat);
                if (pk::has_skill(person_t, Ư��_�п�)) stat = pk::max(5, stat);
                if (pk::has_skill(person_t, Ư��_����)) stat = pk::max(3, stat);
                    
                if (weapon_heishu == ����_â��)
                {
                    if (pk::has_skill(person_t, Ư��_����)) stat = pk::max(4, stat);
                    if (pk::has_skill(person_t, Ư��_����)) stat = pk::max(4, stat);
                    if (pk::has_skill(person_t, Ư��_â��)) stat = pk::max(4, stat);
                    if (pk::has_skill(person_t, Ư��_â��)) stat = pk::max(3, stat);
                    if (pk::has_skill(person_t, Ư��_����)) stat = pk::max(3, stat);
                }
                else if (weapon_heishu == ����_�غ�)
                {
                    if (pk::has_skill(person_t, Ư��_����)) stat = pk::max(4, stat);
                    if (pk::has_skill(person_t, Ư��_����)) stat = pk::max(4, stat);
                    if (pk::has_skill(person_t, Ư��_�ؽ�)) stat = pk::max(4, stat);
                    if (pk::has_skill(person_t, Ư��_â��)) stat = pk::max(3, stat);
                    if (pk::has_skill(person_t, Ư��_����)) stat = pk::max(3, stat);
                    if (pk::has_skill(person_t, Ư��_��ǳ)) stat = pk::max(3, stat);
                }
                else if (weapon_heishu == ����_�뺴)
                {
                    if (pk::has_skill(person_t, Ư��_����)) stat = pk::max(3, stat);
                    if (pk::has_skill(person_t, Ư��_�ý�)) stat = pk::max(5, stat);
                    if (pk::has_skill(person_t, Ư��_����)) stat = pk::max(4, stat);
                    if (pk::has_skill(person_t, Ư��_���)) stat = pk::max(3, stat);
                    if (pk::has_skill(person_t, Ư��_��ǳ)) stat = pk::max(3, stat);
                }
                else if (weapon_heishu == ����_�⺴)
                {
                    if (pk::has_skill(person_t, Ư��_����)) stat = pk::max(3, stat);
                    if (pk::has_skill(person_t, Ư��_���)) stat = pk::max(5, stat);
                    if (pk::has_skill(person_t, Ư��_����)) stat = pk::max(4, stat);
                    if (pk::has_skill(person_t, Ư��_�鸶)) stat = pk::max(4, stat);
                    if (pk::has_skill(person_t, Ư��_����)) stat = pk::max(4, stat);
                    if (pk::has_skill(person_t, Ư��_����)) stat = pk::max(3, stat);
                }
                else if (weapon_heishu == ����_����)
                {
                    if (pk::has_skill(person_t, Ư��_����)) stat = pk::max(5, stat);
                    if (pk::has_skill(person_t, Ư��_����)) stat = pk::max(4, stat);
                    if (pk::has_skill(person_t, Ư��_����)) stat = pk::max(4, stat);
                    if (pk::has_skill(person_t, Ư��_�־�)) stat = pk::max(2, stat);
                }
            }
            return stat;
        }
        
        
        //---------------------------------------------------------------------------------------
        
        // �������� ���� �ʱ�ȭ
        void clear_leader_info()
        {
            leader_list.clear();
            for (int i = 0; i < ����_��; i++)
            {
                leader_location[i] = -1;
            }
        }
        
        // ���� �ʱ�ȭ �Լ� (�̻��)
        void clear_variant()
        {
            @old_leader = null;
            @new_leader = null;
            @unit = null;
            @base = null;  
        }
        
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
        
        //---------------------------------------------------------------------------------------
        
        bool ����׸�� = false;
        
    }
    
	Main main;
}

