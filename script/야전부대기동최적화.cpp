/*
// �ۼ���: �⸶å��
// Update: '20.10.24    / ���ʳ��� : �뺴/��������δ� �������� ȸ�Ǳ⵿ �߰�, ������ �����δ� ��ǥȮ�� �⵿ �߰�
// Update: '20.10.30    / �������� : �����⵿ �Ϲݺδ� Ȯ������ ��������

*/


namespace �����δ�⵿����ȭ
{
    
    //=======================================================================================
   
    // ���� �� ���δ� �������� �ʴ� ��ġ�� ȸ�Ǳ⵿
    const bool ��������_ȸ�Ǳ⵿ = true;        // true=����, false=������ (�뺴,����,����: ȸ�Ǳ⵿)
    const bool �����δ�_ȸ�Ǳ⵿ = true;        // true=����, false=������ (����: ȸ�Ǳ⵿)
    
    // ���� ������ �� �⵿����ȭ
    const bool ���ð���_�������⵿ = true;       // ���� ���� �ֺ� ��������(1��:����/���, 2��:�뺴/����/����)�⵿. �̵��� ��ǥ Ȯ���Ͽ� ��������
    const bool �����ױ�_�������⵿ = true;       // ����/�ױ� �ֺ� ��������(1��:����/���, 2��:�뺴/����/����)�⵿. �̵��� ��ǥ Ȯ���Ͽ� ��������
    const int  ��������_�⵿�δ�� = 3;          // �������ݿ� �������� �⵿ �δ�� ���� (�ϴ�/������, �ּ�=1~�ִ�=5)
    
    const bool �����δ�_�켱_�⵿ = true;       // ���� �ֺ� ��������(����,���,����,����)�� ���� ��� �Ϲݺδ뺸�� ���� �̵��Ͽ� ��������
    
    //=======================================================================================
    
	class Main
	{

		Main()
		{
            pk::bind(111, pk::trigger111_t(onTurnStart));
		}
        
		pk::func261_t@ prev_callback_261;
        
        //---------------------------------------------------------------------------------------
        
        // AI���� ��ũ��Ʈ (�δ��ൿ �켱������ ���Ͽ� 261�Լ� ��� �Ͻ��� Ʈ���� ���)
		void onTurnStart(pk::force@ force)
		{
			int force_id = force.get_id();
            if (!pk::is_campaign())
			{
                // �̹��� ������ ����, ���̵� Ư�� �ÿ��� ����
                if (pk::is_normal_force(force_id) and pk::get_scenario().difficulty == ���̵�_Ư�� and !force.is_player())
                {
                    // �����ױ� ������
                    if (�����ױ�_�������⵿)
                    {
                        for (int j = �ǹ�_��������; j < �ǹ�_�ױ���; j++)
                        {
                            pk::building@ dst_base = pk::get_building(j);
                            if (pk::enemies_around(dst_base) and pk::is_enemy(dst_base, force))
                            {
                                func_siege_formation(dst_base, force);
                            }
                        }
                    }
                    // ���ð��� ������
                    if (���ð���_�������⵿)
                    {
                        for (int j = �ǹ�_���ý���; j < �ǹ�_���ó�; j++)
                        {
                            pk::building@ dst_base = pk::get_building(j);
                            if (pk::enemies_around(dst_base) and pk::is_enemy(dst_base, force))
                            {
                                func_siege_formation(dst_base, force);
                                if (�����δ�_�켱_�⵿)
                                    func_siege_prior_atk(dst_base, force);
                            }
                        }
                    }
                    
                    // ȸ�� �⵿ ��ũ��Ʈ
                    if (�����δ�_ȸ�Ǳ⵿ or ��������_ȸ�Ǳ⵿)
                    {
                        pk::array<pk::unit@> arr_unit_force = pk::list_to_array(pk::get_unit_list(force));
                        if (�����δ�_ȸ�Ǳ⵿)
                        {
                            for (int i = 0 ; i < int(arr_unit_force.length); i++)
                                func_siegeram_evasion(arr_unit_force[i]);
                        }
                        if (��������_ȸ�Ǳ⵿) 
                        {
                            for (int i = 0 ; i < int(arr_unit_force.length); i++)
                                func_archer_evasion(arr_unit_force[i]);
                        }
                    }                    
                }
			}
		}
        
        
        // ���� �Ӽ� Ȯ��
        bool is_dir_weapon(int weapon_id) { return ((����_�� <= weapon_id and weapon_id <= ����_����) and weapon_id != ����_��); }
        bool is_siege_weapon(int weapon_id) { return (����_���� <= weapon_id and weapon_id <= ����_���); }
        bool is_siegeram_weapon(int weapon_id) { return (����_���� == weapon_id or weapon_id == ����_���); }
        bool is_siegerng_weapon(int weapon_id) { return (����_���� == weapon_id or weapon_id == ����_����); }
        bool is_ship_weapon(int weapon_id) { return (weapon_id == ����_���� or weapon_id == ����_����); }
        
        
        
        //=======================================================================================
        //      ��������δ� ȸ�Ǳ⵿(�뺴,����,����) , �����δ� ȸ�Ǳ⵿(����)
        //---------------------------------------------------------------------------------------
        
        //----- ��������δ� ȸ�Ǳ⵿ �����Լ�
        void func_archer_evasion(pk::unit@ unit)
        {
            if (!check_valid_evasion_unit(unit)) return;
            if (unit.weapon >= ����_�ְ� or unit.weapon == ����_����) return;   // ����, �⺴ ����
            
            pk::unit@ enemy = get_neighbor_enemy_unit(unit);
            if (!pk::is_alive(enemy)) return;  // �ֺ��� ���˵� ���δ� ����
            
            int max_range = get_atk_range(unit).second;
            if (max_range <= 1) return;     // �������� �δ� �ƴ�
            
            // �������������� ���, �̵����ɹ��� ���� ���������� ���� �ִ��� Ȯ��
            if (is_siegerng_weapon(unit.weapon))
            {
                pk::building@ target_base = get_siege_target_base(unit);
                if (pk::is_alive(target_base))
                {
                    atk_target_base(unit, target_base);
                    return;
                }
            }
            
            pk::point prev_pos = unit.pos;
            pk::point evasion_pos = get_evasion_pos(unit, max_range);   // ȸ�Ǳ⵿ �ĺ���ǥ �˻�(�ִ� ��Ÿ� ��)
            if (evasion_pos == -1 or !pk::is_valid_pos(evasion_pos))
                evasion_pos = get_evasion_pos(unit, max_range+2);   // ȸ�Ǳ⵿ �ĺ���ǥ ��˻� (�ִ� ��Ÿ� ��)
            if (evasion_pos == -1 or !pk::is_valid_pos(evasion_pos)) return;    // ��ȿ��ǥ ������ ȸ�Ǳ⵿ �Ұ�
            
            bool is_moved = unit_movement_control(unit, evasion_pos, /*is_func262*/false);
            if (!is_moved) return;
            
            run_order_combat_unit(prev_pos, unit, enemy, 3);
        }
        
        //---------------------------------------------------------------------------------------
        //----- �����δ� ȸ�Ǳ⵿ �����Լ�
        void func_siegeram_evasion(pk::unit@ unit)
        {
            if (!check_valid_evasion_unit(unit)) return;
            if (unit.weapon != ����_����) return;   // ������ ���
            
            pk::unit@ enemy = get_neighbor_enemy_unit(unit);
            if (!pk::is_alive(enemy)) return;  // �ֺ��� ���˵� ���δ� ����
            
            // �̵����ɹ��� ���� ���������� ���� �ִ��� Ȯ��
            pk::building@ target_base = get_siege_target_base(unit);
            if (pk::is_alive(target_base))
            {
                atk_target_base(unit, target_base);
                return;
            }
            
            int max_range = 5;
            pk::point prev_pos = unit.pos;
            pk::point evasion_pos = get_evasion_pos(unit, max_range);   // ȸ�Ǳ⵿ �ĺ���ǥ (�ִ� 5ĭ�� ��ȸ)
            if (evasion_pos == -1 or !pk::is_valid_pos(evasion_pos)) return;
            
            bool is_moved = unit_movement_control(unit, evasion_pos, /*is_func262*/false);
            if (!is_moved) return;
            
            run_order_combat_unit(prev_pos, unit, enemy, 3);
        }
        
        //---------------------------------------------------------------------------------------
        
        bool check_valid_evasion_unit(pk::unit@ unit)
        {
            if (!pk::is_alive(unit)) return false;
            if (unit.action_done) return false;   // �ൿ�Ϸ� �δ�� ����
            if (unit.order == �δ��ӹ�_��) return false;
            if (unit.status != �δ����_���) return false;  // ����δ밡 �ƴϸ� ����
            if (pk::is_player_controlled(unit)) return false;   // �÷��̾� ����
            return true;
        }
        
        void atk_target_base(pk::unit@ unit, pk::building@ target_base)
        {
            pk::set_order(unit, �δ��ӹ�_����, target_base.pos);
            pk::run_order(unit);
            unit.action_done = true;
        }
        
        //---------------------------------------------------------------------------------------
        // �ֺ��� �Ϲ������δ� ��� ����
        void run_order_combat_unit(pk::point prev_pos, pk::unit@ unit, pk::unit@ enemy, int range)
        {
            pk::list<pk::unit@> list_unit_combat_evasion;
            
            pk::array<pk::point> arr_range = pk::range(prev_pos, 1, range);
            for (int i = 0; i < int(arr_range.length); i++)
            {
                pk::point pos_t = arr_range[i];
                pk::unit@ unit_atk = pk::get_unit(pos_t);
                if (pk::is_alive(unit_atk) and !unit_atk.action_done and is_dir_weapon(unit_atk.weapon) 
                    and unit_atk.get_id() != unit.get_id() and unit_atk.get_force_id() == unit.get_force_id() 
                    and !pk::is_player_controlled(unit_atk) and unit_atk.target_type == �δ��ӹ����_�δ�)
                {
                    pk::unit@ target = pk::get_unit(unit_atk.target);
                    if (pk::is_alive(target) and target.get_id() == enemy.get_id() and pk::is_enemy(target, unit_atk) and !list_unit_combat_evasion.contains(unit_atk))
                        list_unit_combat_evasion.add(unit_atk);
                }
            }
            if (list_unit_combat_evasion.count == 0) return;

            list_unit_combat_evasion.sort(function(a, b)
            {
                return ((a.attr.stat[�δ�ɷ�_����] + a.attr.stat[�δ�ɷ�_���]) > (b.attr.stat[�δ�ɷ�_����] + b.attr.stat[�δ�ɷ�_���]));
            });
            
            pk::unit@ unit_combat = list_unit_combat_evasion[0];
            if (!unit_combat.action_done)
            {
                pk::run_order(unit_combat);
                unit_combat.action_done = true;
            }
        }
        
        
        //---------------------------------------------------------------------------------------
        // ���� ��ǥ�� ���δ� ���� ���� Ȯ��
        pk::unit@ get_neighbor_enemy_unit(pk::unit@ unit)
        {
            for (int i = 0; i < ����_��; i++)
            {
                pk::point neighbor_pos = pk::get_neighbor_pos(unit.pos, i);
                if (pk::is_valid_pos(neighbor_pos))
                {
                    pk::unit@ unit_t = pk::get_unit(neighbor_pos);
                    if (pk::is_alive(unit_t) and unit_t.get_id() != unit.get_id() and pk::is_enemy(unit, unit_t) and is_dir_weapon(unit_t.weapon))
                        return unit_t;
                }
            }       
            return null;
        }
        //---------------------------------------------------------------------------------------
        // ȸ�Ǳ⵿ �ĺ���ǥ Ȯ�� �Լ�
        pk::unit@ unit_temp;
        int unit_max_range;
        pk::point get_evasion_pos(pk::unit@ unit, int range=1)
        {
            @unit_temp = unit;
            unit_max_range = range;
            
            pk::array<pk::point> arr_evasion_pos;
            pk::array<pk::point> arr_range = pk::get_movable_pos(unit);  // �̵�������ǥ
            for (int j = 0; j < int(arr_range.length); j++)
            {
                bool is_engaged = false;
                pk::point pos = arr_range[j];
                pk::hex@ hex  = pk::get_hex(pos);
                int dist_mov  = pk::get_distance(unit.pos, pos);
                int dist_ref  = pk::max(1, range - 1);
                if (dist_mov <= dist_ref and !hex.has_unit and !hex.has_building)
                {
                    for (int i = 0; i < ����_��; i++)
                    {
                        pk::point neighbor_pos = pk::get_neighbor_pos(pos, i);  // ������ǥ �˻�
                        if (!is_engaged and pk::is_valid_pos(neighbor_pos))
                        {
                            pk::unit@ unit_t = pk::get_unit(neighbor_pos);
                            if (pk::is_alive(unit_t) and unit_t.get_id() != unit.get_id() and pk::is_enemy(unit, unit_t))
                                is_engaged = true;  // ������ǥ�� ���δ� �ִ� ���
                            if (pk::is_on_fire(neighbor_pos))
                                is_engaged = true;  // ȭ�� ��ǥ ����
                        }
                    }      
                    if (!is_engaged) arr_evasion_pos.insertLast(pos);   // ȸ�Ǳ⵿ �ĺ���ǥ �߰�
                }
            }
            if (int(arr_evasion_pos.length) == 0) return -1;
            
            // ���� ��ǥ���� ���� �� ��ġ��
            arr_evasion_pos.sort(function(a, b)
            {
                int dist_a = pk::get_distance(a, main.unit_temp.pos);
                int dist_b = pk::get_distance(b, main.unit_temp.pos);
                if (dist_a != dist_b) return (dist_a < dist_b);
                
                bool pos_t_a = pk::is_valid_pos(main.get_atk_target_pos(main.unit_temp, a, main.unit_max_range));
                bool pos_t_b = pk::is_valid_pos(main.get_atk_target_pos(main.unit_temp, b, main.unit_max_range));
                if ( pos_t_a and !pos_t_b) return true;
                if (!pos_t_a and  pos_t_b) return false;
                
                return (dist_a <= dist_b);
            });
            
            pk::point evasion_pos = arr_evasion_pos[0];
            return evasion_pos;
        }
        
        //---------------------------------------------------------------------------------------
        
        pk::point set_atk_target(pk::unit@ unit, pk::point evasion_pos, int max_range)
        {
            pk::hex_object@ target = get_target_obj(unit, evasion_pos, max_range);
            if (pk::is_alive(target))
            {
                pk::set_order(unit, �δ��ӹ�_����, target.pos); 
                return target.pos;
            }
            return -1;
        }
        
        pk::hex_object@ get_target_obj(pk::unit@ unit, pk::point evasion_pos, int max_range)
        {
            if (unit.weapon == ����_����) return null;
            
            pk::point pos_t = get_atk_target_pos(unit, evasion_pos, max_range);
            if (pos_t != -1 and pk::is_valid_pos(pos_t))
            {
                pk::hex_object@ target = pk::get_hex_object(pos_t);
                if (pk::is_alive(target)) 
                    return target; 
            }
            return null;
        }
        
        // ȸ�� �⵿ �� ���� ��ǥ ����
        pk::point get_atk_target_pos(pk::unit@ unit, pk::point evasion_pos, int max_range)
        {
            pk::point target_pos = -1;
            if (!pk::is_alive(unit)) return -1;
            if (max_range < 1) return -1;
            if (unit.weapon == ����_����) return -1;
            
            pk::array<pk::point> arr_target_pos;
            pk::array<pk::point> arr_atk_range = pk::range(evasion_pos, 1, max_range);
            for (int i = 0; i < int(arr_atk_range.length); i++)
            {
                pk::point pos_t = arr_atk_range[i];
                pk::hex_object@ target = pk::get_hex_object(pos_t);
                if (pk::is_alive(target) and pk::is_enemy(target, unit) and pk::get_hex_object_id(unit) != pk::get_hex_object_id(target))
                    arr_target_pos.insertLast(pos_t);
            }
            if (int(arr_target_pos.length) == 0) return -1;
            
            // ��ǥ ����
            if (int(arr_target_pos.length) > 1)
            {
                arr_target_pos.sort(function(a, b)
                {
                    pk::unit@ unit_a = pk::get_unit(a);
                    pk::unit@ unit_b = pk::get_unit(b);
                    if (pk::is_alive(unit_a) and !pk::is_alive(unit_b)) return true;
                    if (!pk::is_alive(unit_a) and pk::is_alive(unit_b)) return false;
                    if (pk::is_alive(unit_a) and pk::is_alive(unit_a)) return (unit_a.troops < unit_b.troops);
                        
                    pk::building@ building_a = pk::get_building(a);
                    pk::building@ building_b = pk::get_building(b);
                    if (pk::is_alive(building_a) and pk::is_alive(building_b)) return (building_a.hp < building_b.hp);
                    
                    return false;
                });
            }
            target_pos = arr_target_pos[0];
            
            return target_pos;
        }
        
        //---------------------------------------------------------------------------------------
        
        pk::building@ get_siege_target_base(pk::unit@ unit)
        {
            if (!pk::is_alive(unit) or !is_siege_weapon(unit.weapon)) return null;
           
            int max_atk_range = get_atk_range(unit).second;
            
            pk::list<pk::building@> list_target_base;
            pk::array<pk::point> range = pk::get_movable_pos(unit);  // �̵�������ǥ
            for (int i = 0; i < int(range.length); i++)
			{
                pk::point pos = range[i];
                pk::hex@ hex = pk::get_hex(pos);
                pk::array<pk::point> arr_t = pk::range(pos, 1, max_atk_range);   // �ֺ���ǥ
                for (int j = 0; j < int(arr_t.length); j++)
                {
                    pk::building@ target_base = pk::get_building(arr_t[j]);
                    if (!hex.has_building and !hex.has_unit and pk::is_alive(target_base) 
                        and pk::is_enemy(unit, target_base) and target_base.get_id() < �ǹ�_������
                        and !list_target_base.contains(target_base))
                    {
                        list_target_base.add(target_base);
                    }
                }
			}
            if (list_target_base.count == 0) return null;
            
            // ��ǥ ���� ����
            list_target_base.sort(function(a, b)
            {
                bool city_a = (a.get_id() < �ǹ�_���ó�);
                bool city_b = (b.get_id() < �ǹ�_���ó�);
                if (city_a and !city_b) return true;
                if (!city_a and city_b) return false;
                
                bool gate_a = (�ǹ�_�������� <= a.get_id() and a.get_id() < �ǹ�_�ױ���);
                bool gate_b = (�ǹ�_�������� <= b.get_id() and b.get_id() < �ǹ�_�ױ���);
                if (gate_a and !gate_b) return true;
                if (!gate_a and gate_b) return false;
                
                return (a.hp < b.hp);
            });
            
            pk::building@ target_base = list_target_base[0];
            return target_base;
        }
        
        
        //---------------------------------------------------------------------------------------
        
        // ��Ÿ� --- �̻��
        bool is_valid_range_atk_pos(pk::unit@ src_unit, pk::point target_pos)
        {
            if (!pk::is_alive(src_unit) or !pk::is_valid_pos(target_pos)) return false;
            
            pk::hex@ hex = pk::get_hex(target_pos);
            if (!hex.has_unit) return false;
            
            int atk_range = get_archer_range(src_unit);
            
            if (pk::get_distance(src_unit.pos, target_pos) > atk_range) return false;
            
            if (hex.terrain == ����_�� and src_unit.weapon == ����_��)
            {
                if (src_unit.has_skill(Ư��_���)) return true;
                else return false;
            }
            else return true;
        }
        
        int get_archer_range(pk::unit@ src_unit)
        {
            int atk_range = 1;
            if (src_unit.weapon == ����_��)
                atk_range = 2 + ((src_unit.has_tech(�ⱳ_����))? 1 : 0);
            else if (src_unit.weapon == ����_����)
                atk_range = 1 + ((src_unit.has_tech(�ⱳ_���) or src_unit.has_skill(Ư��_�鸶))? 1 : 0);
            
            return atk_range;
        }
        
        //---------------------------------------------------------------------------------------
        
        // �δ� ���� �ּ�,�ִ� ��Ÿ� �Լ� -- �ű� �߰�, ��밡���� ������ �������ǿ� ���� ���
        pk::int_int get_atk_range(pk::unit@ unit)
        {
            pk::int_int atk_range = pk::int_int(1, 1);
            if (!pk::is_alive(unit) or unit.weapon == ����_��) return atk_range;
        
            int weapon_id = unit.weapon;
            pk::equipment@ epq = pk::get_equipment(unit.weapon);
            string eqp_name = pk::decode(pk::get_name(epq));
            string info = pk::format("{}", eqp_name);
            
            int min_range = 5;
            int max_range = 1;
            
            for (int j = 0; j < ����_��; j++)
            {
                if (epq.tactics[j])
                {
                    pk::tactics@ tts = pk::get_tactics(j);
                    string tts_name = pk::decode(pk::get_name(tts));
                    info += pk::format(" {}({},{})", tts_name, tts.min_range, tts.max_range);
                    min_range = pk::min(min_range, tts.min_range);
                    max_range = pk::max(max_range, tts.max_range);
                }
            }
            if (weapon_id == ����_�� and unit.has_tech(�ⱳ_����)) max_range += 1;
            if (weapon_id == ����_���� and (unit.has_tech(�ⱳ_���) or unit.has_skill(Ư��_�鸶))) max_range = pk::max(2, max_range);
            if ((weapon_id == ����_���� or weapon_id == ����_����) and unit.has_skill(Ư��_����)) max_range += 1;
            
            atk_range = pk::int_int(min_range, max_range);
            info += pk::format(": �ּ�({}),�ִ�({})", min_range, max_range);
            
            //if (����׸��) pk::info(info);
            
            return atk_range;
        }
        
        
        //=======================================================================================
        //          �δ� �⵿ ���� �Լ�
        //---------------------------------------------------------------------------------------
        
        bool unit_movement_control(pk::unit@ unit, pk::point evasion_pos, bool is_func262=false)
        {
            pk::hex@ hex = pk::get_hex(evasion_pos);
            if (hex.has_unit or hex.has_building) return false;
            
            bool is_moved = false;
            int max_atk_range = get_atk_range(unit).second;
            int move_distance = pk::get_distance(unit.pos, evasion_pos);
            
            if (unit.order == �δ��ӹ�_��) return false;
            
            // ȸ�Ǳ⵿ ó��
            if (move_distance == 1)  // ȸ�Ǳ⵿ �̵��Ÿ� = 1
            {
                // ȸ�Ǳ⵿ ���� �̵� ó��
                pk::array<pk::point> evasion_path = {unit.pos, evasion_pos};	// �̵����
                pk::move(unit, evasion_path);
                if (unit.pos == evasion_pos) is_moved = true;
            }
            else if (move_distance > 1) // ȸ�Ǳ⵿ �̵��Ÿ� > 1
            {
                // ���� �δ��ӹ� ���� ���
                int prev_order            = unit.order;
                int prev_target           = unit.target;
                int prev_target_type      = unit.target_type;
                pk::point prev_target_pos = unit.target_pos;
               
                // �δ��ӹ� ������Ʈ�� ���� ���� ȸ�� ��Ʈ��
                if (unit.pos != evasion_pos)
                {
                    pk::set_order(unit, �δ��ӹ�_�̵�, evasion_pos);   // ȸ�Ǳ⵿ �������� �̵����
                    pk::run_order(unit);
                    unit.order       = prev_order       ;  
                    unit.target      = prev_target      ;
                    unit.target_type = prev_target_type ;
                    unit.target_pos  = prev_target_pos  ;
                    
                    if (unit.pos == evasion_pos) is_moved = true;
                }
            }
            
            if (is_moved)
            {
                // �̵�ó�� �� ���� ���� �� ����
                if (!unit.action_done and (unit.weapon == ����_�� or unit.weapon == ����_����) and max_atk_range > 1)
                {
                    pk::hex_object@ target = get_target_obj(unit, evasion_pos, max_atk_range);
                    if (pk::is_alive(target)) 
                    {
                        pk::attack(unit, target);
                        unit.action_done = true;  // �δ��ൿ �Ϸ�� ����
                    }
                }
                if (!unit.action_done and unit.weapon != ����_���� and unit.order != �δ��ӹ�_����)
                {
                    pk::point target_pos = set_atk_target(unit, evasion_pos, max_atk_range + (move_distance - 1));   // �δ��ӹ� �������� ����
                    if (!is_func262 and target_pos != -1 and pk::is_valid_pos(target_pos)
                        and pk::get_distance(target_pos, unit.pos) <= max_atk_range and is_siegerng_weapon(unit.weapon))
                    {
                        pk::run_order(unit);
                        unit.action_done = true;  // �δ��ൿ �Ϸ�� ����
                    }
                }
                unit.action_done = true;  // �δ��ൿ �Ϸ�� ����
            
                if (����׸��)
                {
                    pk::person@ leader = pk::get_person(unit.leader);
                    string unit_name = (pk::is_alive(leader))? pk::decode(pk::get_name(leader)) : "??";
                    pk::info(pk::format("�����⵿: {}��({}) �⵿", unit_name, get_weapon_name(unit.weapon)));
                }
            }
            
            return is_moved;
        }
        
        
        
        //=======================================================================================
        //      ����/����/�ױ� ������ �⵿ (�������� �켱�⵿)
        //---------------------------------------------------------------------------------------
        
        void func_siege_prior_atk(pk::building@ dst_base, pk::force@ force)
        {
            if (!pk::is_alive(dst_base) or !pk::is_normal_force(force)) return;
            if (!pk::enemies_around(dst_base)) return;
            string base_name = pk::decode(pk::get_name(dst_base));
            
            // ��ǥ���� �ֺ� �����δ� �˻�
            get_siege_units_nearby(dst_base, force, 3);    // �˻��Ÿ�=3 ���� ����

            if (list_siege_unit_around.count == 0) return;   // ������ �������� ����
            
            pk::array<pk::unit@> arr_siege_unit = pk::list_to_array(list_siege_unit_around);
            for (int i = 0; i < int(arr_siege_unit.length); i++)
            {
                pk::unit@ siege_unit = arr_siege_unit[i];
               
                if (!siege_unit.action_done)
                {
                    pk::set_order(siege_unit, �δ��ӹ�_����, dst_base.pos);
                    pk::run_order(siege_unit);
                    siege_unit.action_done = true;
                    
                    if (����׸��) 
                    {
                        pk::person@ leader = pk::get_person(siege_unit.leader);
                        string siege_unit_name = (pk::is_alive(leader))? pk::decode(pk::get_name(leader)) : "??";
                        string weapon_name = get_weapon_name(siege_unit.weapon);
                        
                        pk::info(pk::format("�����⵿: {}��({}) �켱 {} ����", siege_unit_name, weapon_name, base_name));
                    }
                }
            }
        }
        
        // ���� �ֺ��� �������� �δ� �˻�
        pk::list<pk::unit@> list_siege_unit_around;
        void get_siege_units_nearby(pk::building@ dst_base, pk::force@ force, int search_range)
        {
            if (!pk::is_alive(dst_base) or dst_base.get_id() >= �ǹ�_������) return;
            
            list_siege_unit_around.clear();
            
            int dist_add = (dst_base.facility == �ü�_����)? 1 : 0;
            
            pk::array<pk::point> arr_range = pk::range(dst_base.pos, 1, (search_range + dist_add));
            for (int i = 0; i < int(arr_range.length); i++)
            {
                pk::point pos_t = arr_range[i];
                if (pk::is_valid_pos(pos_t) and (pk::get_building_id(pos_t) == dst_base.get_id() or pk::get_distance(pos_t, dst_base.pos) <= 4))
                {
                    pk::unit@ unit = pk::get_unit(pos_t);
                    if (pk::is_alive(unit) and unit.get_force_id() == force.get_id() and !pk::is_player_controlled(unit) and !pk::is_in_water(unit) and !unit.action_done and unit.status == �δ����_���)
                    {
                        if (is_siege_weapon(unit.weapon) and !list_siege_unit_around.contains(unit))
                            list_siege_unit_around.add(unit);
                    }
                }
            }
        }
        
        // �δ��ӹ� ���ݸ�ǥ�� �ش� �������� Ȯ��
        bool is_target_base(pk::unit@ unit, pk::building@ dst_base)
        {
            if (!pk::is_alive(unit) or !pk::is_alive(dst_base)) return false;
            if (unit.target_type == �δ��ӹ����_����)
            {
                pk::building@ base_t = pk::get_building(unit.target);
                if (pk::is_alive(base_t) and base_t.get_id() == dst_base.get_id())
                    return true;
            }
            return false;
        }
    
        //=======================================================================================
        //      ����/����/�ױ� ������ �⵿ (����/���, ����/���� ������ġ ����ȭ)
        //---------------------------------------------------------------------------------------
        
        void func_siege_formation(pk::building@ dst_base, pk::force@ force)
        {
            if (!pk::is_alive(dst_base) or !pk::is_normal_force(force)) return;
            if (!pk::enemies_around(dst_base)) return;
            
            bool cmd_1 = true;
            bool cmd_2 = true;
            int unit_count = 0;
            int push_count = 0;
            int max_count = pk::max(1, pk::min(5, ��������_�⵿�δ��));
            while (push_count < max_count and unit_count < max_count)
            {
                push_count++;
                if (cmd_1 and PushSiegeRamFormation(dst_base, force)) unit_count++;
                else cmd_1 = false;
                
                if (cmd_2 and PushSiegeTwrFormation(dst_base, force)) unit_count++;
                else cmd_2 = false;
            }
        }
        
        // ������������(����/���) ���� ����
        bool PushSiegeRamFormation(pk::building@ dst_base, pk::force@ force)
        {
            // ��ǥ���� �ֺ��� �Ÿ��� �Ϲ�/�����δ� �˻�
            get_atk_units_nearby(dst_base, force, 4);    // �˻��Ÿ� ����

            if (list_siegeram_unit.count == 0) return false;   // �ֺ��� �������� ����
            
            pk::person@ kunshu = pk::get_person(pk::get_kunshu_id(force));
            string force_name = pk::decode(pk::get_name(kunshu));
            string base_name = pk::decode(pk::get_name(dst_base));
            if (����׸��) pk::info(pk::format("�����⵿: {}��{}, ���������δ��={}, �����Ϲݺδ��={}", force_name, base_name, list_siegeram_unit.count, list_combat_unit_n1.count));
            
            // �����δ� ����
            sort_list_siegeram_unit();     // ����Ʈ ����
            pk::unit@ siege_unit = list_siegeram_unit[0];
            
            // ��ǥ���� �ֺ��� ����ǥ �˻�
            int num_empty_pos = count_empty_neighbor_pos(dst_base, siege_unit, /*distance*/1);
            
            // 1���� �Ϲݺδ� ȸ�Ǳ⵿ (�� ��ǥ ���� ���)
            if (list_combat_unit_n1.count > 0 and num_empty_pos == 0)
            {
                sort_list_combat_unit_n1();    // ����Ʈ ����
                pk::unit@ combat_unit = list_combat_unit_n1[0];
                pk::point dst_pos = combat_unit.pos;   // ���� ��ǥ ���� (�����δ밡 �̵��� �ڸ�)
                pk::point evasion_pos = get_evasion_pos(combat_unit, /*max_range*/4);   // ����⵿ �ĺ���ǥ
                if (evasion_pos == -1 or !pk::is_valid_pos(evasion_pos)) return false;    // ��ȿ��ǥ ������ ����⵿ �Ұ�
                
                string combat_unit_name = pk::decode(pk::get_name(pk::get_person(combat_unit.leader)));
                if (����׸��) pk::info(pk::format("�����⵿: {}�� ������ǥ({},{})", combat_unit_name, evasion_pos.x, evasion_pos.y));
                
                bool is_moved = unit_movement_control(combat_unit, evasion_pos, /*is_func262*/false);
                if (!is_moved) return false;     // �̵� �������� ����
            
                // ��ǥ���� �ֺ��� ����ǥ ��˻�
                num_empty_pos = count_empty_neighbor_pos(dst_base, siege_unit, /*distance*/1);
            }
            
            // �����δ� ��������
            if (!siege_unit.action_done and num_empty_pos > 0)
            {
                pk::set_order(siege_unit, �δ��ӹ�_����, dst_base.pos);
                pk::run_order(siege_unit);
                siege_unit.action_done = true;
                
                if (����׸��) 
                {
                    pk::person@ leader = pk::get_person(siege_unit.leader);
                    string siege_unit_name = (pk::is_alive(leader))? pk::decode(pk::get_name(leader)) : "??";
                    string weapon_name = get_weapon_name(siege_unit.weapon);
                    
                    pk::info(pk::format("�����⵿: {}��({}) {} ��������", siege_unit_name, weapon_name, base_name));
                }
                return true;
            }
            return false;
        }
        
        // ������������(����/����) ���� ����
        bool PushSiegeTwrFormation(pk::building@ dst_base, pk::force@ force)
        {
            // ��ǥ���� �ֺ��� �Ÿ��� �Ϲ�/�����δ� �˻�
            get_atk_units_nearby(dst_base, force, 4);    // �˻��Ÿ� ����

            if (list_range_unit.count == 0) return false;   // �ֺ��� �������� ����
            
            pk::person@ kunshu = pk::get_person(pk::get_kunshu_id(force));
            string force_name = pk::decode(pk::get_name(kunshu));
            string base_name = pk::decode(pk::get_name(dst_base));
            if (����׸��) pk::info(pk::format("�����⵿: {}��{}, ���������δ��={}, �Ϲݺδ��={}", force_name, base_name, list_range_unit.count, list_combat_unit_n2.count));
            
            // �����δ� ����
            sort_list_range_unit();     // ����Ʈ ����
            pk::unit@ siege_unit = list_range_unit[0];
            
            // ��ǥ���� �ֺ��� ����ǥ �˻�
            int num_empty_pos = count_empty_neighbor_pos(dst_base, siege_unit, /*distance*/2);
            
            // 2���� �Ϲݺδ� ȸ�Ǳ⵿
            if (list_combat_unit_n2.count > 0 and num_empty_pos == 0)
            {
                sort_list_combat_unit_n2();    // ����Ʈ ����
                pk::unit@ combat_unit = list_combat_unit_n2[0];
                pk::point dst_pos = combat_unit.pos;   // ���� ��ǥ ���� (�����δ밡 �̵��� �ڸ�)
                pk::point evasion_pos = get_evasion_pos(combat_unit, /*max_range*/4);   // ����⵿ �ĺ���ǥ
                if (evasion_pos == -1 or !pk::is_valid_pos(evasion_pos)) return false;    // ��ȿ��ǥ ������ ����⵿ �Ұ�
                
                string combat_unit_name = pk::decode(pk::get_name(pk::get_person(combat_unit.leader)));
                if (����׸��) pk::info(pk::format("�����⵿: {}�� ������ǥ({},{})", combat_unit_name, evasion_pos.x, evasion_pos.y));
                
                bool is_moved = unit_movement_control(combat_unit, evasion_pos, /*is_func262*/false);
                if (!is_moved) return false;     // �̵� �������� ����
                
                // ��ǥ���� �ֺ��� ����ǥ ��˻�
                num_empty_pos = count_empty_neighbor_pos(dst_base, siege_unit, /*distance*/2);
            }
            
            // �����δ� ��������
            if (!siege_unit.action_done and num_empty_pos > 0)
            {
                pk::set_order(siege_unit, �δ��ӹ�_����, dst_base.pos);
                pk::run_order(siege_unit);
                siege_unit.action_done = true;
                
                if (����׸��) 
                {
                    pk::person@ leader = pk::get_person(siege_unit.leader);
                    string siege_unit_name = (pk::is_alive(leader))? pk::decode(pk::get_name(leader)) : "??";
                    string weapon_name = get_weapon_name(siege_unit.weapon);
                    
                    pk::info(pk::format("�����⵿: {}��({}) {} ��������", siege_unit_name, weapon_name, base_name));
                }
                return true;
            }
            return false;
        }
        
        
        
        //---------------------------------------------------------------------------------------
        
        pk::list<pk::unit@> list_combat_unit_n1;
        pk::list<pk::unit@> list_combat_unit_n2;
        pk::list<pk::unit@> list_siegeram_unit;
        pk::list<pk::unit@> list_range_unit;
        
        // ���� �ֺ��� �δ� �˻� (���ൿ �� ������¿��� �ϰ�, �����δ�� �������⸸)
        void get_atk_units_nearby(pk::building@ dst_base, pk::force@ force, int search_range)
        {
            if (!pk::is_alive(dst_base) or !pk::is_normal_force(force) or dst_base.get_id() >= �ǹ�_������) return;
            
            list_combat_unit_n1.clear();
            list_combat_unit_n2.clear();
            list_siegeram_unit.clear();
            list_range_unit.clear();
            
            int dist_add = (dst_base.facility == �ü�_����)? 1 : 0;
            
            pk::array<pk::point> arr_range = pk::range(dst_base.pos, 1, (search_range + dist_add));
            for (int i = 0; i < int(arr_range.length); i++)
            {
                pk::point pos_t = arr_range[i];
                if (pk::is_valid_pos(pos_t) and (pk::get_building_id(pos_t) == dst_base.get_id() or pk::get_distance(pos_t, dst_base.pos) <= 4))
                {
                    pk::unit@ unit = pk::get_unit(pos_t);
                    if (pk::is_alive(unit) and unit.get_force_id() == force.get_id() and !pk::is_player_controlled(unit) and !pk::is_in_water(unit) and !unit.action_done and unit.status == �δ����_���)
                    {
                        pk::int_int unit_range = get_atk_range(unit);
                        int min_range = unit_range.first;
                        int max_range = unit_range.second;
                        int distance = pk::get_distance(unit.pos, dst_base.pos) - dist_add;
                        // ����/���, �ٰŸ�/���Ÿ�
                        if (is_siegeram_weapon(unit.weapon))
                        {
                            if (distance > 1 and !list_siegeram_unit.contains(unit))   // 1�� ����
                                list_siegeram_unit.add(unit);
                        }
                        // �������� : ��/����/���� (�����Ÿ��� �ִ� �δ�� ����Ʈ���� ����)
                        if (is_siegerng_weapon(unit.weapon) or unit.weapon == ����_��)
                        {
                            if (!(min_range <= distance and distance <= max_range) and !list_range_unit.contains(unit))
                                list_range_unit.add(unit);
                        }
                        // �Ϲݺδ� (â�س��)
                        if (unit.weapon <= ����_����)
                        {
                            if (distance == 1 and !list_combat_unit_n1.contains(unit))  // 1��
                                list_combat_unit_n1.add(unit);
                            else if (distance == 2 and distance > max_range and !list_combat_unit_n2.contains(unit))    // 2��
                                list_combat_unit_n2.add(unit);
                        }
                    }
                }
            }
        }
        
        //---------------------------------------------------------------------------------------
        
        // �Ϲ������δ� ����Ʈ ���� (�뺴 �켱, �뺴�δ�� ���� �δ� �켱, �����δ�� ���� �δ� �켱)
        void sort_list_combat_unit_n1()
        {
            if (list_combat_unit_n1.count <= 1) return;

            list_combat_unit_n1.sort(function(a, b)
            {
                bool skill_a = (a.has_skill(Ư��_����) or a.has_skill(Ư��_����));
                bool skill_b = (b.has_skill(Ư��_����) or b.has_skill(Ư��_����));
                
                int wpn_a = pk::get_ground_weapon_id(a);
                int wpn_b = pk::get_ground_weapon_id(b);
                if (wpn_a == ����_�� and wpn_b != ����_��) return true;
                if (wpn_a != ����_�� and wpn_b == ����_��) return false;
                if (wpn_a == ����_�� and wpn_b == ����_��)
                {
                    if ( skill_a and !skill_b) return true;
                    if (!skill_a and  skill_b) return false;
                    return (a.attr.stat[�δ�ɷ�_����] > b.attr.stat[�δ�ɷ�_����]);
                }
                    
                return (a.attr.stat[�δ�ɷ�_����] < b.attr.stat[�δ�ɷ�_����]);
            });
        }
        
        // �Ϲ������δ� ����Ʈ ���� (�����δ� �켱)
        void sort_list_combat_unit_n2()
        {
            if (list_combat_unit_n2.count <= 1) return;

            list_combat_unit_n2.sort(function(a, b)
            {
                int wpn_a = pk::get_ground_weapon_id(a);
                int wpn_b = pk::get_ground_weapon_id(b);
                if (wpn_a != ����_�� and wpn_b != ����_��) return (a.attr.stat[�δ�ɷ�_����] < b.attr.stat[�δ�ɷ�_����]);
                if (wpn_a == ����_�� and wpn_b != ����_��) return false;
                if (wpn_a != ����_�� and wpn_b == ����_��) return true;
                    
                return (a.attr.stat[�δ�ɷ�_����] < b.attr.stat[�δ�ɷ�_����]);
            });
        }
        
        // �������� �����δ� ����Ʈ ���� (Ư�� �켱, ���ݷ� �켱)
        void sort_list_siegeram_unit()
        {
            if (list_siegeram_unit.count <= 1) return;

            list_siegeram_unit.sort(function(a, b)
            {
                bool skill_a = (a.has_skill(Ư��_����) or a.has_skill(Ư��_����));
                bool skill_b = (b.has_skill(Ư��_����) or b.has_skill(Ư��_����));
                
                if ( skill_a and !skill_b) return true;
                if (!skill_a and  skill_b) return false;
                    
                return (a.attr.stat[�δ�ɷ�_����] > b.attr.stat[�δ�ɷ�_����]);
            });
        }
        
        
        // ��������δ� ����Ʈ ���� (�������� �켱, Ư�� �켱, ���ݷ� �켱)
        void sort_list_range_unit()
        {
            if (list_range_unit.count <= 1) return;

            list_range_unit.sort(function(a, b)
            {
                bool siege_a = main.is_siegerng_weapon(a.weapon);
                bool siege_b = main.is_siegerng_weapon(b.weapon);
                if ( siege_a and !siege_b) return true;
                if (!siege_a and  siege_b) return false;
                
                bool skill_a = (a.has_skill(Ư��_����) or a.has_skill(Ư��_����));
                bool skill_b = (b.has_skill(Ư��_����) or b.has_skill(Ư��_����));
                if ( skill_a and !skill_b) return true;
                if (!skill_a and  skill_b) return false;
                    
                return (a.attr.stat[�δ�ɷ�_����] > b.attr.stat[�δ�ɷ�_����]);
            });
        }
        
        //---------------------------------------------------------------------------------------
        // �ֺ��� ����ִ� ���� ��ǥ ���� ��ȯ
        int count_empty_neighbor_pos(pk::building@ dst_base, pk::unit@ unit, int distance=1)
        {
            if (!pk::is_alive(dst_base) or !pk::is_alive(unit)) return -1;
            
            int dist_add = (dst_base.facility == �ü�_����)? 1 : 0;
            int dist_search = pk::max(1, pk::min(2, distance));
            
            pk::array<pk::point> arr_range = pk::get_movable_pos(unit);
            pk::array<pk::point> arr_empty_pos;
            for (int i = 0; i < int(arr_range.length); i++)
            {    
                pk::point pos_t = arr_range[i];
                int dist_pos = pk::get_distance(pos_t, dst_base.pos) - dist_add;
                pk::hex@ hex = pk::get_hex(pos_t);
                if (dist_search == dist_pos and !hex.has_building and !hex.has_unit and !pk::is_water_terrain(hex.terrain))
                    arr_empty_pos.insertLast(pos_t);
            }
            
            if (����׸��) pk::info(pk::format("�����⵿: ����ǥ��={}", int(arr_empty_pos.length)));
            
            return int(arr_empty_pos.length);
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
        
        //---------------------------------------------------------------------------------------
        
        
        bool ����׸�� = false;
        
        
        
        
	};

	Main main;
}