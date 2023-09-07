/*
���� by �ϼ���

�� ��ũ��Ʈ�� PK2.1 �⺻ ���� ��ũ��Ʈ �� �ϳ��̸�, �⸶å����� ������ �����Ͻ� ��ũ��Ʈ�Դϴ�.
���⿡ ���� �߰��� �����ϰ� ��� ������ �ߴµ���.
���� �� �ܿ������� ���� ���� ���ϸ鼭 �� ����� ������ ö���� �ϵ��� �߰� ������ �Ͽ����ϴ�.

[���� ����]
1. ������ ö�� �ϴ� ���� �� '�ܿ� ������ �ƽ��ƽ��� ���'�� ���� ���� 2200 �̸��� ��쿡 ö�� �ϵ��� ���� �߰� 
2. '�ܿ� ������ �ƽ��ƽ��� ���2' �׸� �߰�
3. '�ܿ� ������ �ƽ��ƽ��� ��� 2 ' �׸� �߰�

*/



/*
pk2.1 �⺻�����Ǵ� ����ö�� ��ɿ��� ����

@������: �⸶å��
@Update: '19.3.5     / ���泻�� : ����ö�� ���ð� ����, ���� �������� ����� ���� ��ũ��Ʈ�� �и�, ���Ÿ��̵�/�ӽõ��ּ��� ��� �߰�
@Update: '19.3.9     / ���泻�� : ����ö�� ���� ���ð� ����, �����˻���� �߰�
@Update: '19.4.5     / ���泻�� : ������ ������ ��� ö���Ұ�

*/


namespace ����ö��
{
    
    //---------------------------------------------------------------------------------------
    // ���� ����
    
    const bool  ����ö��_���Ÿ��̵�  = true;     // ö���δ� �̵� 1ȸ �߰� (��õ��� : ���ʽ��̵����� Ż��)
    const bool  ����ö��_�Ͻõ��ּ��� = true;     // ö���δ� �������� ����ȿ�� �Ͻ����� (��õ��� : ������ ���İ���)
    
    const float ����ö��_����ȸ���� = 0.50f;    // ö�� �� ��/���� ȸ���� (0.0f ~ 1.0f ����)
    const float ����ö��_����ȸ���� = 0.95f;    // ö�� �� ���� ȸ����   (0.0f ~ 1.0f ����)
    
    const int   ����ö��_�����˻���� = 1;       // 0: ���ø� �˻��Ͽ� ö��,  1: ����+����+�ױ� ��� �˻��Ͽ� ö��
    
    //---------------------------------------------------------------------------------------
    
    
    
	class Main
	{
		pk::func261_t@ prev_callback_;

		Main()
		{
			@prev_callback_ = cast<pk::func261_t@>(pk::get_func(261));
			pk::reset_func(261);
			pk::set_func(261, pk::func261_t(callback));
		}
        
        int retreat_skill = -1; // ��������
        

		bool callback(pk::force@ force)
		{
			int force_id = force.get_id();

            if (!pk::is_campaign())
            {                
                // �÷��̾�, �̹��� ������ ����.
                if (!force.is_player() and pk::is_normal_force(force_id))
                {
                    for (int i = 0; i < �ǹ�_������; i++)
                    {
                        auto base = pk::get_building(i);
                        
                        if (base.get_force_id() == force_id and needRetreat(base))
                            PushRetreat(base);
                              
                    }
                }
            }
            
			// ���� �ڵ鷯�� �ִٸ� ü��.
			if (prev_callback_ !is null)
				return prev_callback_(force);
			return false;
		}
        
        
        
        //----------------------------------------------------------------------------------
        //          ���� ö�� 
        //----------------------------------------------------------------------------------
        
		/** ö���� �ʿ��� �������� �Ǵ�(���ǹ��� �ſ� ����� �����Դϴ�. �Ը��� �°� �����ؼ� ����� ������.) */
		bool needRetreat(pk::building@ base)
		{
			// ������ �� �δ� ��
			int enemy_units1 = 0;
			// 3ĭ �̳� �� �δ� ��
			int enemy_units3 = 0;
			// 3ĭ �̳� �� ���� ��
			int enemy_troops3 = 0;

			auto range = pk::range(base.get_pos(), 1, 4 + (base.facility == �ü�_���� ? 1 : 0));
			for (int i = 0; i < int(range.length); i++)
			{
				auto unit = pk::get_unit(range[i]);
				if (pk::is_alive(unit))
				{
					int distance = pk::get_distance(base.get_pos(), range[i]);
					if (pk::is_enemy(base, unit))
					{
						if (distance <= 1)
						{
							enemy_units1++;
						}
						if (distance <= 3)
						{
							enemy_units3++;
							enemy_troops3 += unit.troops;
						}
					}
					else
					{
					}
				}
			}

			if (enemy_units1 >= 10)  // ���� ���� ���·� ö�� �Ұ�
				return false;
			int base_troops = pk::get_troops(base);
			int base_hp = base.hp;
			// �ܿ� ������ �ƽ��ƽ��� ���
			if (enemy_units3 > 0 and base_troops < enemy_troops3 * 0.8f and base_hp < pk::max(500, int(pk::get_max_hp(base) * 0.3f)) )
				return true;

			// �ܿ� ������ �ƽ��ƽ��� ��� 2 (2020.08.31. �ϼ��� �߰�)
			if (enemy_units3 > 0 and enemy_troops3 >= 4000 and base_hp <= 700 )
				return true;


			// �ܿ� ������ �ƽ��ƽ��� ���  
			// 2200�� ���� �̸� �߰� ,�ϼ��� ���� 2021.01.15
			
			if (enemy_units3 > 0 and base_troops < pk::max(1, int(enemy_troops3 * 0.1f)) and base_troops < 2200 )
				return true;

			// �ܿ� ������ �ƽ��ƽ��� ���2,�ϼ��� ���� 2021.01.15 
			if (enemy_units3 > 0 and int(base_troops * 3.8f) < enemy_troops3 and base_troops < 1500 )
				return true;

            
			return false;
		}


		/** ö�� ��� */
		bool PushRetreat(pk::building@ base)
		{
			// ��� ������ ������ �ִ��� Ȯ��.
			auto person_list = pk::get_idle_person_list(base);
			if (person_list.count == 0) return false;

			// ö���� ���� ������ �ִ��� Ȯ��.
			int target = getNearestBase(base);
			if (target == -1) return false;

            pk::list<pk::person@> actors;
            for (int i = 0; i < person_list.count; i++)
            {
            if (pk::is_unitize(person_list[i])) continue;
            if (pk::is_absent(person_list[i])) continue;				
            if (person_list[i].order != -1) continue;				
            if (person_list[i].get_force_id() != base.get_force_id()) continue; 
            if (person_list[i].get_force_id() != pk::get_building(target).get_force_id()) continue; 
            if (person_list[i].location != person_list[i].service) continue;
            if (person_list[i].action_done) continue;
            if (pk::is_absent(person_list[i])) continue;
            if (person_list[i].mibun == �ź�_����) continue;
            if (person_list[i].mibun == �ź�_���) continue;

            if (!pk::is_unitize(person_list[i]) and !pk::is_absent(person_list[i])
		and person_list[i].order == -1 and person_list[i].get_force_id() == base.get_force_id() and person_list[i].get_force_id() == pk::get_building(target).get_force_id() 
                and person_list[i].location == person_list[i].service and !person_list[i].action_done and !pk::is_absent(person_list[i])
                and (person_list[i].mibun == �ź�_���� or person_list[i].mibun == �ź�_���� or person_list[i].mibun == �ź�_�¼� or person_list[i].mibun == �ź�_�Ϲ�)) 
				
                actors.add(person_list[i]);
            }

       if (actors.count == 0 ) return false;

			// ��ġ�� ���� ������ ����.
			actors.sort(function(a, b)
			{
				return (a.stat[����ɷ�_��ġ] / a.stat[����ɷ�_����]) > (b.stat[����ɷ�_��ġ] / b.stat[����ɷ�_����]);
			});
            pk::person@ leader = pk::get_person(actors[0].get_id());
            
            // �ӽ� ���� ȿ�� ('19.3.6)
            if (����ö��_�Ͻõ��ּ���)
            {
                retreat_skill = leader.skill;   // Ư�� ���
                leader.skill = Ư��_����;         // ���� Ư�� �ο�
            }
            

            float supply_rate = pk::min(1.0f, pk::max(0.0f, ����ö��_����ȸ����));
            float weapon_rate = pk::min(1.0f, pk::max(0.0f, ����ö��_����ȸ����));
            
			// ���� ��� ���� ����.
			pk::com_deploy_cmd_info cmd;
			@cmd.base = @base;
			cmd.type = �δ�����_����;
			cmd.member[0] = leader.get_id();
			cmd.gold = pk::min(int(pk::get_gold(base) * supply_rate), 100000);
			cmd.food = pk::min(int(pk::get_food(base) * supply_rate), 500000);
			cmd.troops = pk::min(int(pk::max(1.f, pk::get_troops(base) * 0.60f)), 60000);
			int i = 0;
			for (int weapon_id = 0; weapon_id < ����_��; weapon_id++)
			{
                int weapon_amount = 0;
                if (weapon_id < ����_����)
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id) * weapon_rate), 100000);
                else
                    weapon_amount = pk::min(int(pk::get_weapon_amount(base, weapon_id)), 100);
                
				if (weapon_amount > 0)
				{
					cmd.weapon_id[i] = weapon_id;
					cmd.weapon_amount[i] = weapon_amount;
					i++;
				}
			}
			cmd.order = �δ��ӹ�_�̵�;
			cmd.target_pos = pk::get_building(target).get_pos();

			// ����.
			int unit_id = pk::command(cmd);
            pk::unit@ unit_cmd = pk::get_unit(unit_id);
			if (pk::is_alive(unit_cmd))
				unit_cmd.action_done = (!����ö��_���Ÿ��̵�);  // �⺻�� true ���� false �� �����Ͽ� 2ȸ �̵��ϵ��� �� ('19.3.5)
            
            
            pk::say(pk::encode("� ������ �����Ͽ� ö���϶�"), leader);
            
            // �ӽ� ���� ȿ�� ('19.3.6)
            if (����ö��_�Ͻõ��ּ���)
            {
                leader.skill = retreat_skill;         // Ư�� ����
            }
            
            
			return true;
		}
        
		/** ���� ����� �Ʊ� ������ ����. */
        pk::building@ src_t;
		int getNearestBase(pk::building@ src)
		{
			int best_dst = -1;
			int best_distance = 0;
            int src_id = src.get_id();
            pk::list<pk::building@> dst_list; 
            @src_t = @src;
            
            int search_base = �ǹ�_���ó�;
            if      (����ö��_�����˻���� == 0) search_base = �ǹ�_���ó�;
            else if (����ö��_�����˻���� == 1) search_base = �ǹ�_������;
            
            pk::force@ force = pk::get_force(src.get_force_id());
            
			// ö�� ���� �˻�
            if (pk::get_city_list(force).count <= 1 and src_id < �ǹ�_���ó�)
                return -1;      // ������ ������ ��� ö�� �Ұ�
            else
            {
                for (int i = 0; i < search_base; i++)
                {
                    pk::building@ dst = pk::get_building(i);
                    int dst_id = dst.get_id();
                    
                    if (src_id != dst_id and src.get_force_id() == dst.get_force_id())
                    {
                        best_dst = dst_id;
                        dst_list.add(dst);  // ö������ ��������Ʈ �߰�
                    }
                }
            }
            
            // �������� ��������Ʈ ���� (���� �Ÿ� ��������, ��ǥ�Ÿ� ��������)
            if (dst_list.count == 0)
                best_dst = -1;
            else
            {
                dst_list.sort(function(a, b)
                {
                    int build_dist_a = pk::get_building_distance(a.get_id(), main.src_t.get_id(), a.get_force_id());
                    int build_dist_b = pk::get_building_distance(b.get_id(), main.src_t.get_id(), b.get_force_id());

                    int pos_dist_a = pk::get_distance(a.pos, main.src_t.pos);
                    int pos_dist_b = pk::get_distance(b.pos, main.src_t.pos);
                    
                    if (build_dist_a != build_dist_b) 
                        return (build_dist_a < build_dist_b);
                    
                    return (pos_dist_a < pos_dist_b);
                });
                best_dst = dst_list[0].get_id();
            }
                
            
            
			return best_dst;
		}
        
        
	};

	Main main;
}