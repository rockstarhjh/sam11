/*     
// ������: �⸶å��
// Update: '19.2.17  / ��������: �����δ��� ���¼� ���� �׽�Ʈ, �������� �Ǵ�
// Update: '19.2.27  / ��������: ������������ ���ñ������� �����ջ� ����, �ֵ��� ���� Ʈ���� �߰�, �ּ� ��ݺ��� ���Ѱ��� �ӽ�����
// Update: '19.3.3   / ��������: �����δ� �������� �߰� (�跫�δ�, �����δ�)
// Update: '20.8.26  / ��������: ķ���ο����� ��ũ��Ʈ �������� �ʵ��� ����
// Update: '20.9.14  / ��������: �δ��ӹ� �� ������ǥ Ȯ�� ���� �߰�
// Update: '20.9.20  / ��������: ������� �� �����ּҹ�� ���� ����ϵ��� ����
*/

namespace ������������ȭ
{
	
    //---------------------------------------------------------------------------------------
    // ���� ����
    const int  ������������ȭ_�������� = 0;     // 0: ��ǻ��AI �� �÷��̾�_���ӱ��� ���,  1: �÷��̾�_���ӱ��ܸ�, 2: ��ǻ��AI��,  3: ��� ������
    const bool ������������ȭ_������������ = false;   // �������ǰ� ������ ���뿩�� ����, ������ �δ��� ���õǹǷ� false ����
    const bool ������������_��ȭǥ�� = false;       // ���� �� ���� ���� ��� �޽��� ǥ��
    
    //---------------------------------------------------------------------------------------
    
    // ��ݺ������� �ɼǼ���
    const bool ��ݺ�������_�������� = true;      // ��ݺδ��� ���� ���Ѽ��� (false=������ : ��Ÿ �ɼ� ����)
    
    const bool ��ݺ�������_�ּ��������� = true;   // ��ݺδ��� �ּҺ��� ���Ѽ���
    const int  ��ݺ�������_�ּ����Ѻ��� = 1000;   // ��ݺδ��� �ּҺ��� ���� (���� �⺻�� = 5000)
    const bool ��ݺ�������_�ִ��������� = true;   // ��ݺδ��� �ִ뺴�� ���Ѽ���
    const int  ��ݺ�������_�ִ����Ѻ��� = 12000;  // ��ݺδ��� �ִ뺴�� ����
    const bool ��ݺ�������_�ɷ°���ġ���� = true;  // ��ݺδ��� �ִ뺴�� ���� �� ����/��� ��� �ɷ¿� ���� ����ġ ���� (��ü�δ� ���� ����)
    const int  ��ݺ�������_�����ܿ����� = 5000;   // ��ݺδ��� ���� �� �ҼӰ����� �ּ��ܿ�����
	
    // �Ǽ����� ���� : ���/���� ��� ����
    const bool �Ǽ�����_���ܼ��� = true;      // �Ǽ����� ���� ���� �� AI�δ� ���庯�� ���� (Ư��_�༺ ���� �Ǵ� ��/���� ���� �Ǵ�)
    const int �Ǽ�����_���ؼ����� = 1500;     // ���� ������ �̻� & ���� ���� ������ ��� �Ǽ��δ�� ����Ͽ� ���庯�� ����
    const int �Ǽ�����_���غ���  = 3000;     // ���� ������ �̻� & ���� ���� ������ ��� �Ǽ��δ�� ����Ͽ� ���庯�� ����
    
    //---------------------------------------------------------------------------------------
    
    // ������������ �ɼǼ���
    const bool ������������_�������� = true;     // �����δ��� ���� ���Ѽ��� (false=������, ��Ÿ �ɼ� ����)
    const int  ������������_�����ܿ����� = 5000;   // ��ݺδ��� ���� �� �ҼӰ����� �ּ��ܿ�����
    
    // �����δ� ���� : ���� �δ뿡�� ����
    const bool  �����δ�_���Ѽ���  = true;  // true=��������, false=������
    const int  �����δ�_���ѱ��غ��� = 5000;   // �����δ��� ���غ��� ����
    const int  �����δ�_����������� = 1500;   // �δ������� ���� ���غ��� ��� �߰��� ��޴� ���´��� (����C �߰�����, ����S ������ 3�� �߰�) 
    
    // �跫�δ� ���� : ���� �δ뿡�� ����
    const bool  �跫�δ�_���Ѽ���  = true;  // true=��������, false=������
    const bool  �跫�δ�_������� = true;   // �δ� ������ S�̻��� ��� �����δ�� ��� (��� Ư�� ����)    
    // ��/�� �迭 Ư��� ������ �����δ� ��� (�跫�Կ� Ư�� �������� ����)
    // �Ż�,���,����,�͸�,��ȯ�� ������ �跫�δ� ��� (���°���� ����)
    const bool  �跫�δ�_Ư���� = true;     // �跫�Կ� Ư�� ������ �δ� ��� (���°���� ����)
    const float �跫�δ�_���°���� = 1.5f;    // �δ������� �δ������� ��� ���� �̻��̸� �跫�δ�� ���
    const int  �跫�δ�_�ִ����Ѻ��� = 5000;   // �跫�δ��� �ִ뺴�� ����
    
    //---------------------------------------------------------------------------------------
    
    
	class Main
	{
		
		Main()
		{
            pk::bind(102, pk::trigger102_t(onGameInit));
            pk::bind(132, pk::trigger132_t(onForceLeaveControl));
            pk::bind(111, pk::trigger111_t(onTurnStart));
            
			pk::bind(170, ������������ȭ_Ʈ����_�켱����, pk::trigger170_t(onUnitCreate));
            pk::bind(172, ������������ȭ_Ʈ����_�켱����, pk::trigger172_t(onUnitPosChange));
		}
		
        
        int ������������ȭ_Ʈ����_�켱���� = 99; // ���� �������� ���� ���� (�����δ�����ȭ.cpp ũ�� ������������ȭ.cpp ���� ���� ���� �ʿ�)
        
        array<int> def_troopsbase(�ǹ�_���ó�, 0);   // ���� �� ��������
        array<int> def_troops_sum(�ǹ�_���ó�, 0);   // ���� �� ���� ������
        array<int> def_unit_count(�ǹ�_���ó�, 0);   // ���� �� ���� �δ��
        array<int> atk_troops_sum(�ǹ�_���ó�, 0);   // ���� �� ���ݱ� ������
        array<int> atk_unit_count(�ǹ�_���ó�, 0);   // ���� �� ���ݱ� �δ��
        
        bool limit_defence = false;
        bool limit_attack = false;
        pk::list<pk::unit@> limit_def_unit_list;
        pk::list<pk::unit@> limit_atk_unit_list;
        
        //---------------------------------------------------------------------------------------

        void onGameInit()
        {
            if (pk::is_campaign()) return;
            
            pk::force@ force = pk::get_force(pk::get_current_turn_force_id());
            onTurnStart(force);
        }
        
        void onForceLeaveControl(pk::force@ force)
		{
            if (pk::is_campaign()) return;
            
            // �� ���� ���� ������ : �����ϴ� ������, �δ�� ������Ʈ
            clear_engage_info();
            update_engage_info();
        }
            
        void onTurnStart(pk::force@ force)
        {
            if (pk::is_campaign()) return;
            
            // �� ���� ���� ������ : �����ϴ� ������, �δ�� ������Ʈ
            clear_engage_info();
            update_engage_info();
        }
        
        // �δ� ���� �� �������� ��󿩺� �Ǵ�
		void onUnitCreate(pk::unit@ unit, int type) 
		{
            if (pk::is_campaign()) return;
            
            // ���� �ʱ�ȭ
            limit_defence = false;
            limit_attack = false;
            limit_def_unit_list.clear();
            limit_atk_unit_list.clear();
            
            // �������� �����δ����� Ȯ��
            if (!check_valid_unit(unit, type)) return ;
            // �������� ����ȭ�� ���� Ȯ��
            if (!check_force_option(unit)) return ;
            // AI�Ǽ������� ��� 
            if (�Ǽ�����_���ܼ��� and check_construction_unit(unit)) return ;
            // �����δ� �ҼӰ���
            pk::building@ base = pk::get_building(pk::get_service(unit));
            if (!pk::is_alive(base)) return;
            // �ҼӰ����� ������ ���ÿ� ���ϼ����� �ƴϸ� ����
            if (base.get_force_id() != pk::get_city(pk::get_city_id(base.pos)).get_force_id()) return;
            
            // ���δ� ħ��Ȯ��
            bool is_invaded = check_enemy_invasion(base);
            if (is_invaded and ��ݺ�������_��������)
            {
                limit_defence = true;
                limit_def_unit_list.add(unit);
            }
            else if (!is_invaded and ������������_��������)
            {
                limit_attack = true;
                limit_atk_unit_list.add(unit);
            }
		}
        
        // �δ� �����̵� �� �ʰ����� ��ȯ
        void onUnitPosChange(pk::unit@ unit, const pk::point &in pos)
        {
            if (pk::is_campaign()) return;
            
            if (����׸��)
            {
                string unit_name  = pk::decode(pk::get_name(pk::get_person(unit.leader)));
                string target_info;
                if (unit.target_type == �δ��ӹ����_����) target_info = pk::decode(pk::get_name(pk::get_building(unit.target)));
                if (unit.target_type == �δ��ӹ����_�δ�) target_info = pk::decode(pk::get_name(pk::get_person(pk::get_unit(unit.target).leader)));
                pk::info(pk::format("{}�� {}: {}", unit_name, get_order_info(unit.order), target_info));
            }
            
            // ��� �δ� ����
            if (��ݺ�������_�������� and limit_defence and limit_def_unit_list.contains(unit))
            {
                limit_defence = false;
                limit_def_unit_list.clear();
                
                pk::building@ base = pk::get_building(pk::get_service(unit));
                if (!pk::is_alive(base)) return;
                
                // �δ��ӹ���ǥ Ȯ�� ('20.9.14, �߰�)
                if (unit.order == �δ��ӹ�_����) return;
                // Ÿ���� ���� ���� ����, �ڼ��� Ÿ���� ������� ����
                if (unit.target_type == �δ��ӹ����_����)
                {
                    pk::building@ dst_base = pk::get_building(unit.target);
                    if (pk::is_alive(dst_base))
                    {   
                        if (dst_base.get_force_id() != base.get_force_id()) return;
                        if (dst_base.get_force_id() == base.get_force_id() and dst_base.get_id() != base.get_id()) return;
                    }
                }                
                // �������Ѱ� ��� �Լ�
                int limit_value = get_defence_limit(base, unit);
                // ������������ �Լ� : �ʰ����� �������� ��ȯ
                return_over_troops(base, unit, limit_value);
                
            }
            // ���� �δ� ����
            if (������������_�������� and limit_attack and limit_atk_unit_list.contains(unit))
            {
                limit_attack = false;
                limit_atk_unit_list.clear();
                
                pk::building@ base = pk::get_building(pk::get_service(unit));
                if (!pk::is_alive(base)) return;
                
                // �δ��ӹ���ǥ Ȯ�� ('20.9.14, �߰�)
                if (unit.order == �δ��ӹ�_����) return;
                // �ڼ��� Ÿ���� ������� ����
                if (unit.target_type == �δ��ӹ����_����)
                {
                    pk::building@ dst_base = pk::get_building(unit.target);
                    if (pk::is_alive(dst_base))
                    {   
                        if (dst_base.get_force_id() == base.get_force_id() and dst_base.get_id() != base.get_id()) return;
                    }
                }
                
                // �������Ѱ� ��� �Լ�
                int limit_value = get_attack_limit(base, unit);
                // ������������ �Լ� : �ʰ����� �������� ��ȯ
                return_over_troops(base, unit, limit_value);
                
            }
        }
        
        
        //---------------------------------------------------------------------------------------
        // ������ ���� ��Ȳ ������Ʈ
        //---------------------------------------------------------------------------------------
        
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
        
        
        //---------------------------------------------------------------------------------------
        // ���� ���� ����
        //---------------------------------------------------------------------------------------
        
        // ������������ �Լ� : �������� ���ؿ� ���� �ʰ��� �ҼӰ������� ����/�����/���� ��ȯ
		void return_over_troops(pk::building@ base, pk::unit@ unit, int limit) 
		{
            if (limit <= 0) return;
			if (!pk::is_alive(base) or !pk::is_alive(unit)) return;
            
            int troops = unit.troops;
            if (troops > limit)
            {
                // ���� ��ȯ
                int return_amount = troops - limit;
                pk::add_troops(unit, -return_amount, false);    // �δ� ���� ����
                pk::add_troops(base, +return_amount, false);    // ���� ���� ��ȯ
                
                // ����� ��ȯ
                int weapon_id = pk::get_ground_weapon_id(unit);
                if (����_â <= weapon_id and weapon_id <= ����_����)
                    pk::add_weapon_amount(base, weapon_id, return_amount, false);   // ���� ���� ��ȯ
                
                // ���� ��ȯ
                int food_amount = int(float(unit.food) * float(return_amount) / float(troops));
                pk::add_food(unit, -food_amount, false);        // �δ� ���� ����
                pk::add_food(base, +food_amount, false);        // ���� ���� ����
                
                pk::person@ leader = pk::get_person(unit.leader);
                if (������������_��ȭǥ��)
                {
                    string weapon_name = get_weapon_name(weapon_id);
                    string base_name = pk::decode(pk::get_name(base));
                    pk::say(pk::encode(pk::format("���������������� \x1b[17x{} \x1b[1x{}��\x1b[0x�� \n\x1b[2x{}\x1b[0x(��)�� ��ȯ�ϰڽ��ϴ�", weapon_name, return_amount, base_name)), leader);
                }
                if (����׸��)
                {
                    string name = pk::decode(pk::get_name(leader));
                    pk::info(pk::format("{}�� ��������={} ����={} ��ȯ={} ����={}", name, troops, limit, return_amount, unit.troops));
                }
                
            }
            
		}
        
        
        //---------------------------------------------------------------------------------------
        //   ��� �δ� ����
        //---------------------------------------------------------------------------------------
        
        // �������Ѱ� ��� �Լ� ('19.2.27)
        int get_defence_limit(pk::building@ base, pk::unit@ unit)
        {
            int city_id = pk::get_city_id(base.pos);
            
            // �� ����+�δ뺴�� ����
            int def_troops  = def_troopsbase[city_id] + def_troops_sum[city_id];
            
            // �����ּҺ��� (���ѱ��ذ� vs.���ݺ����� �ּҰ�)
            int min_limit; 
            if (��ݺ�������_�ּ���������)
                min_limit = pk::max(1, ��ݺ�������_�ּ����Ѻ���, atk_troops_sum[city_id]);
            else 
                min_limit = unit.troops;
            
            // ��� ���ݺ���
            int atk_troops_avg; 
            if (atk_unit_count[city_id] == 0)
                atk_troops_avg = 1;
            else 
                atk_troops_avg = int(atk_troops_sum[city_id] / atk_unit_count[city_id]);
            
            // �����ִ뺴�� ���
            int max_limit; 
            if (��ݺ�������_�ִ���������)
                max_limit = pk::max(3000, pk::min(��ݺ�������_�ִ����Ѻ���, int(get_defence_weight(unit) * atk_troops_avg)));
            else 
                max_limit = unit.troops;
            
            // �����ܿ����� ��� ('20.9.20)
            int base_limit = get_base_limit(base, unit, ��ݺ�������_�����ܿ�����);
            
            // �ִ뺴�� ����ġ ����
            int limit = pk::min(min_limit, max_limit, base_limit);
            
            return int(limit/100)*100;
            
        }
        
        // ��� ���� ����ġ �Լ�
        float get_defence_weight(pk::unit@ unit)
        {
            float weight = 1.1f;
            if (��ݺ�������_�ɷ°���ġ����)
            {
                float avg_stat = (unit.attr.stat[�δ�ɷ�_����] + unit.attr.stat[�δ�ɷ�_���]) / 2.f;
                weight = weight * avg_stat / 50.f; 
            }
            return weight;
        }
        
        // �⺴ �� �����ܿ����� ����� ���Ѱ�
        int get_base_limit(pk::building@ base, pk::unit@ unit, int remain_limit)
        {
            int unit_troops = unit.troops;
            int base_troops = pk::get_troops(base);
            int base_remain = base_troops - pk::max(0, remain_limit);
            int base_limit  = unit_troops;
            if (base_remain > unit_troops)
                base_limit = unit_troops;
            else if (unit_troops > base_remain and base_remain >= 0)
                base_limit = pk::max(1000, unit_troops - (unit_troops - base_remain)/2);
            else if (base_remain < 0 and base_troops > 0)
                base_limit = pk::max(1, base_troops / 2);
            
            return base_limit;
        }
        
        
        //---------------------------------------------------------------------------------------
        // ���� �δ� ����
        //---------------------------------------------------------------------------------------
        
        int get_attack_limit(pk::building@ base, pk::unit@ unit)
        {
            int limit = unit.troops;
            
            // ���� �����δ��� ���
            if (�����δ�_���Ѽ��� and check_siege_unit(unit))
            {
                int tekisei = pk::min(����_S, pk::get_tekisei(unit, pk::get_ground_weapon_id(unit)));
                limit = �����δ�_���ѱ��غ��� + (�����δ�_����������� * (tekisei - ����_C));
            }
            
            // ���� �跫�δ��� ��� 
            else if (�跫�δ�_���Ѽ��� and check_atk_strategy_unit(unit))
            {
                limit = �跫�δ�_�ִ����Ѻ���;
            }
            
            // �����ܿ����� ��� ('20.9.20)
            int base_limit = get_base_limit(base, unit, ������������_�����ܿ�����);
            
            // �ִ뺴�� ����ġ ����
            limit = pk::min(limit, base_limit);
            
            
            return int(limit/100)*100;
        }
        
        
        //---------------------------------------------------------------------------------------
        // ���� ���� ���� Ȯ��
        //---------------------------------------------------------------------------------------
        
        // �������� �����δ����� Ȯ��
        bool check_valid_unit(pk::unit@ unit_t, int type)
        {
            if (!pk::is_alive(unit_t))      return false;
            if (type != 0)                  return false;	// ���� �δ밡 �ƴ� ��� ���� (���� ���� �δ�)
			if (unit_t.type != �δ�����_����)	return false;	// ���� �δ� ����
            if (unit_t.attr.stat[�δ�ɷ�_�̵�] < 2)	return false;	// 2ĭ �̻� �̵��Ұ� �� �δ���� �ڵ� ��� (�̵��� 2~4 = ���� 1ĭ)
            if (pk::get_service(unit_t) >= �ǹ�_������) return false;      // �Ҽ� ���� Ȯ��
            
            int force_id = unit_t.get_force_id();
            pk::force@ force = pk::get_force(force_id);
			if (!pk::is_alive(force) or !pk::is_normal_force(force)) return false;  // �Ҽ� ���� Ȯ��  
            if (force_id != pk::get_current_turn_force_id()) return false;  // ���� �ϼ��� �ƴ� ��� ('19.2.15)        
            
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
        
        //---------------------------------------------------------------------------------------
        
        // ����������� �Ǵ� �Լ� : ħ���� ���δ� ���¼��� Ȯ��
        bool check_enemy_invasion(pk::building@ base)
        {
            if (!pk::is_alive(base)) return false;
            
            int city_id = pk::get_city_id(base.pos);
            if (atk_unit_count[city_id] == 0) return false;
            
            return true;
        }
        
        // �Ǽ����� ���� �Ǵ� ('19.2.15)
        bool check_construction_unit(pk::unit@ unit)
        {
            if (pk::is_player_controlled(unit)) return false; // ���������� ������ ����
            
            if (unit.has_skill(Ư��_�༺) and unit.gold >= �Ǽ�����_���ؼ�����) return true;  // �༺ Ư��
            
            if (unit.type == �δ�����_���� and pk::get_member_count(unit) <= 1)   // 1�δ�
            {
                if (unit.gold >= �Ǽ�����_���ؼ����� and unit.troops <= �Ǽ�����_���غ���) 
                    return true; 
            }
            return false;
        }
        
        // �����δ� ���� �Ǵ� �Լ� ('19.3.3)
        bool check_siege_unit(pk::unit@ unit)
        {
            if (pk::is_player_controlled(unit)) return false; // ���������� ������ ����
            
            int weapon_id = pk::get_ground_weapon_id(unit);
            if (pk::equipment_id_to_heishu(weapon_id) == ����_����)
                return true;
            
            return false;
        }
        
        
        // ���� �跫�δ� ���� �Ǵ� �Լ� ('19.3.1)
        bool check_atk_strategy_unit(pk::unit@ unit)
        {
            if (pk::is_player_controlled(unit)) return false; // ���������� ������ ����
            
            // �δ� ���� ���� : S�̻��� ��� �����δ� ���
            if (�跫�δ�_������� and pk::get_tekisei(unit) >= ����_S)
                return false;
            
            // ���� Ư�� Ȯ��
            for (int i = 0; i < 3; i++)
            {
                pk::person@ member = pk::get_person(unit.member[i]);
                if (pk::is_alive(member))
                {
                    int skill_id = member.skill;
                    pk::skill@ skill = pk::get_skill(skill_id);
                    
                    // ��/�� �迭 ����Ư���� ��� �����δ� ��� 
                    if (skill_id >= Ư��_â�� and skill_id <= Ư��_����)
                        return false;   
                    
                    // �跫Ư�� ���
                    if (�跫�δ�_Ư���� and pk::is_alive(skill))
                    {
                        if (skill.type == Ư������_�跫) return true;    
                    }
                }
            }
            
            // ������ ��� Ư��
            if (unit.has_skill(Ư��_�Ż�) or unit.has_skill(Ư��_���) or unit.has_skill(Ư��_����) 
                or unit.has_skill(Ư��_�͸�) or unit.has_skill(Ư��_��ȯ)) 
                return true;
            
            // ���� �� ���� ���� �Ǵ�
            float stat_ratio = float(2.0f * unit.attr.stat[�δ�ɷ�_����] / (unit.attr.stat[�δ�ɷ�_����] + unit.attr.stat[�δ�ɷ�_���]));
            if (stat_ratio >= �跫�δ�_���°����) 
                return true;
            
            return false;
        }
        
		
        //---------------------------------------------------------------------------------------
        
        
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
        
        
        bool ����׸�� = false;
        
	} 

	Main main;
	
} 