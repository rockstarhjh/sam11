/*
@ ������ : �⸶å��
@ UPDATE : '18.10.21  / ���泻��: ������ ����ȿ�� ����
@ UPDATE : '18.11.8   / ���泻��: �������� �ɼ� �߰�, �������� ũ��Ƽ�ú����߰�, �����������߰�
@ UPDATE : '18.11.27  / ���泻��: �������⿡ ��������� �߰�
@ UPDATE : '19.2.16   / ���泻��: ������ ���� �ұ�/�ݰ� �ߵ� �� �������� ó�� + �� ����Ʈ ǥ�� + �ݰݴ���� ����ǰ� ����
@ UPDATE : '19.2.21   / ���泻��: Ŀ���� ��ȭǥ�ð� ���� ���Ŀ� ǥ�õǵ��� ����ġȹ��Ʈ���� ������� ����, ����÷ȥ��Ȯ�� �������� �ɼ� �߰�
@ UPDATE : '19.3.3    / ���泻��: �Ĺ��ǰݽ� ȥ��ȿ�� ��� �߰�
@ UPDATE : '19.6.17   / ���泻��: �Ĺ��ǰݽ� ȥ��ȿ�� �ݰ����� ���� ����
@ UPDATE : '19.11.21  / ���泻��: ��Ư�⿬�� Ȱ��ȭ �� ���������� ���Ÿ��ߵ� ���� ����, AI�δ� ��������ȭ �ɼ� �߰�
@ UPDATE : '20.4.11   / ���泻��: ���������� �����ļ� ������ ����
@ UPDATE : '20.8.25   / ���泻��: ����÷ȥ��Ȯ�� �ɼ�OFF ó�� (pk2.1 �Ź������� ���� ������)
@ UPDATE : '20.8.29   / ���泻��: ķ���ο����� Ŀ���� ���� ��� �Ұ��ϵ��� ����
@ UPDATE : '20.10.6   / ���泻��: ��Ư�⿬�� ��Ÿ� Ȯ������ ����, ��������ȭ Ȯ������ ���� (�뺴������)
@ UPDATE : '20.10.17  / ���泻��: ��Ư�⿬�� �ߵ��Լ� ���� ���� (Ư��_���, ������ ������� ����), AI�δ�_�뺴ȭ������ �߰� (���Ȱ������ ȭ�÷� ����)
@ UPDATE : '20.11.9   / ���泻��: ��ǳ/���� ��µ����� ���� ���� ����
*/

namespace �δ���_����_�����
{
    //---------------------------------------------------------------------------------------
    // ���� ���� (true = on, false = off)
    const bool ��ȭǥ�ü��� = true;   // Ŀ���� ȿ�� �ߵ� �� ��ȭǥ�� ���� (false ����)
    
	const bool ���ȿ������ = true;   // ��¿� ����Ͽ� ������ ���� ���� ȿ��
    const bool ����������� = true;   // ���� �� �������� ���� ���ݺδ� �������, �ǰݺδ� ��°���
    const bool ����ȿ������ = true;   // ���� �� �������� �� �������� ���� �ݿ�����
    const bool �ֺ��δ뼳�� = true;   // �ֺ� �Ʊ��δ밡 ���� �Ǵ� �����̰ų�, Ư��_�Ż�, Ư��_��� ���� �� ����ȿ��
    const bool �������⼳�� = true;   // ���� �� �δ� ���� ���⿡ ���� ������ ����ȿ�� ����
    const bool �������Ư�� = true;   // ���� �� ����� ���Ư��(ö��,�ұ�,�ݰ�) ȿ�� ����
    const bool ������������ = true;   // ������ Ư���� �������� ������ ������ �δ�� ũ��Ƽ�� ���ݷ� ���� 
    
    const bool ����ȿ������ = true;   // ���º� ���� ȿ�� ����
    const bool ����Ư�⼳�� = true;   // ������ Ư�⿡ ���� ������ ���� ȿ�� ����
    const bool �����ɷ��ջ� = true;   // true: ���� �� ������� �ɷ�ġ �ջ� ��� ����, false: ����ó�� �¼� �ɷ¸� ����
    const bool ���������� = true;   // ����(����,����,�ױ�)�� ������ �δ��� ������ ��� ���� ����
    
    const float ��������� = 0.8f;   // ��ü���� ��������� ������ ����
    
    //---------------------------------------------------------------------------------------
    // ����÷ȥ��Ȯ�� �������� (204 ����÷ ȥ�� Ȯ��.cpp �̵��� ����) --- pk2.1 �Ź������� ���� �����Ǿ� OFF ó����
    const bool ����÷ȥ��Ȯ��_�������� = false;   // ���� �� ������� : ȥ����������� ���� ����ó�� �� �ִϸ��̼� ����� �� ����
    const int  ����÷_ũ��Ƽ��ȥ��Ȯ�� = 100;    // �⺻��=100, ũ��Ƽ���� �� ȥ��Ȯ����
    const int  ����÷_��������ȥ��Ȯ�� = 30;     // �⺻��=30, ũ��Ƽ�� �ƴ� �� ȥ��Ȯ���� 
    
    // �δ� �Ĺ��ǰݽ� ȥ��ȿ�� : �������⼳��=true �� Ȱ��ȭ�Ǵ� �߰� �ɼ�
    const bool �Ĺ��ǰݽ�_ȥ������ = true;   // �δ� �Ĺ��ǰݽ� ����Ȯ���� ȥ��ȿ�� (true=����, false=������)
    const int  �Ĺ��ǰݽ�_ȥ��Ȯ�� = 10;     // �Ĺ��ǰݽ�_ȥ������=true �� ȥ�� Ȯ���� (0~100)
    
    // ��Ư�⿬�� Ȱ��ȭ �� ���������� ���Ÿ����� �ߵ��Ǵ� ���� ���� (true ����)
    const bool ��Ư�⿬��_�ߵ����� = true;     // ��Ư�⿬�� Ȱ��ȭ �� ���������� ���Ÿ��ߵ� ���� ����
    
    // AI�δ� ���� �ɼ�
    const bool AI�δ�_��������ȭ = false;    // AI�δ� ���� �� ȿ������ ������ ����
    const bool AI�δ�_�뺴ȭ������ = true;   // AI�δ� ���� �� �뺴 ����� ������ ȭ�÷� ����
    
    //---------------------------------------------------------------------------------------
    
    
    class Main
	{
        
		Main()
		{
			pk::set_func(209, pk::func209_t(callback));
            
            pk::bind(173, pk::trigger173_t(onUnitExpAdd));
		}
        
        /*----------------------------------------
            ���� ���ط��� ����մϴ�.
            @param[out] damage	����� ����
            @param unit			�δ�
            @param tactics_id	#����Id
            @param target_pos	��ǥ ��ǥ
            @param type			0 ����, 1 �ݰ�, 2 �ݰ�
            @param critical		0 ġ��Ÿ Ȯ�� ���, 1 ġ��Ÿ ���� ����, 2 ġ��Ÿ ���� ����
            @param ambush		0 ���, 1 ����
        ----------------------------------------*/
		void callback(pk::damage_info& info, pk::unit@ attacker, int tactics_id, const pk::point &in target_pos, int type, int critical, bool ambush)
		{
			int force_id = attacker.get_force_id();
			pk::force@ force = pk::get_force(force_id);
			int weapon_id = attacker.weapon;
			int command = func_5aee10(attacker);
			pk::unit@ target_unit = pk::get_unit(target_pos);
			pk::building@ target_building = pk::get_building(target_pos);
            pk::hex_object@ target_obj = pk::get_hex_object(target_pos);
			int atk = 0;
			int troops_atk = 0;
			int buffed = 0;
            
            //---------------------------------------------------------------------------------------
            // ����ġȹ�� ó���� ���� �ʱ�ȭ ('19.2.21)
            @msg_unit = null;
            @msg_person = null;
            msg_string = "";
            
            @nasun_unit = null;
            ����÷_ũ��Ƽ�� = false;
            
            @back_unit = null;
            //---------------------------------------------------------------------------------------

			// ���� �ɷ�ġ
			if (ambush)
				atk = pk::max(attacker.attr.stat[�δ�ɷ�_����] - 5, 1);
			else
				atk = attacker.attr.stat[�δ�ɷ�_����];

            
            // AI�δ� ��������ȭ ('20.10.13)
            if (!pk::is_campaign() and !pk::is_player_controlled(attacker) and !ambush and type == 0)
            {
                if (AI�δ�_�뺴ȭ������ and attacker.weapon == ����_�� )    // �뺴 ������� �� ����ȭ�÷� ����ȭ
                    tactics_id = func_fire_on_arrow(attacker, target_obj, tactics_id);
                
                if (AI�δ�_��������ȭ and target_unit !is null)     // ���� ���� ����ȭ
                    tactics_id = func_dir_tactics_opt(attacker, target_unit, tactics_id);
            }
            
            
			// ���� ���ݷ�, ���� ���
			if (pk::is_valid_tactics_id(tactics_id))
			{
				troops_atk = pk::get_tactics(tactics_id).troops_atk;
				info.tactics_hit = pk::rand_bool(cast<pk::func202_t>(pk::get_func(202))(attacker, attacker.get_pos(), pk::get_hex_object(target_pos), tactics_id));
            }
			else if (pk::is_neighbor_pos(attacker.get_pos(), target_pos))
			{
				troops_atk = 10;
			}

			// ���ݷ� ��� ����
			if (func_5aed80(attacker.get_pos(), force_id))
			{
				buffed = 1;
				info.buffed = true;
					
			}

			// �����
			if (target_unit !is null)
			{
				pk::force@ target_force = pk::get_force(target_unit.get_force_id());
				int facility_id = �ü�_��;
				if (pk::has_tech(target_force, �ⱳ_�ü���ȭ))
					facility_id = �ü�_���;
				if (pk::has_tech(target_force, �ⱳ_������ȭ))
					facility_id = �ü�_��ä;
				if (func_5aedc0(target_unit.get_pos(), 1, pk::get_facility(facility_id).max_range, target_unit.get_force_id()))
					info.debuffer = facility_id;
			}

			// ũ��Ƽ��
			info.critical = false;
			if (critical == 0)
			{
				if (pk::is_valid_tactics_id(tactics_id) and not info.tactics_hit)
					info.critical = false;
				else if (type == 0)
					info.critical = cast<pk::func201_t@>(pk::get_func(201))(attacker, pk::get_hex_object(target_pos), tactics_id, !pk::is_neighbor_pos(attacker.get_pos(), target_pos));
			}
			else if (critical == 1)
			{
				info.critical = true;
			}
			
			float �����_�� = float(pk::core["�����.��"]); // 1.15f
			float �����_�� = float(pk::core["�����.��"]); // 0.85f
			float �����ⱳ_���ݷ� = 1.15f;
			float �ܷñⱳ_���ݷ� = 1.10f;
			float ũ��Ƽ��_���ݷ� = 1.15f;

			// �δ밣 ���� (����)
            if (target_unit !is null)
			{
				info.dst_troops = target_unit.troops;

				float troops_damage = func_5aee60(atk, command, troops_atk, buffed, target_unit.attr.stat[�δ�ɷ�_���], func_5aee10(target_unit));
				
                /* �Ӿ� Ư�� ���� ���� : �ټ� �δ뿡 �ݰ� �� ����ģ ��� ȸ�� ����
				int �δ�_���ȸ�� = 5;
				if (attacker.has_skill(Ư��_�Ӿ�))
					info.energy_heal = �δ�_���ȸ��;
                */
                
                
				switch (weapon_id)
				{
				case ����_â:
					if (pk::is_valid_tactics_id(tactics_id))
					{
						if (target_unit.weapon == ����_��)
                        {
							troops_damage *= �����_��;
                            
                            if (target_unit.has_tech(�ⱳ_ū����))  // �غ� ��� �ⱳȿ�� �߰����� ('18.10.5)
                                troops_damage *= �����_��;
                        }
						else if (target_unit.weapon == ����_����)
							troops_damage *= �����_��;
                        else if (target_unit.weapon == ����_��)
							troops_damage *= �����_��;
					}
                    
					if (pk::has_tech(force, �ⱳ_����â��))
                        troops_damage *= �����ⱳ_���ݷ�; // 1.15f
					else if (pk::has_tech(force, �ⱳ_â���ܷ�))
                        troops_damage *= �ܷñⱳ_���ݷ�; // 1.10f;
                    
                    // ���� Ư�� (����)
					if (����Ư�⼳�� and attacker.has_skill(Ư��_����) and !pk::is_campaign())
                    {
						troops_damage *= 1.15f;
                        
                        if (��ȭǥ�ü��� and pk::is_player_controlled(attacker))
                        {
                            //pk::say(pk::encode("��ī�ο� â���� �޾ƶ�"), pk::get_person(attacker.leader));
                            @msg_unit = @attacker;
                            @msg_person = pk::get_person(attacker.leader);
                            msg_string = "��ī�ο� â���� �޾ƶ�";
                        }
                    }
                    
                    // ���º� �ܷñⱳ ����Ƽ�� [����, ����, ����, ����, �հ�, ��å]�� ������ ��� ('18.9.30)
                    if (����ȿ������ and pk::has_tech(force, �ⱳ_â���ܷ�) and !pk::is_campaign())
                    {
                        
                        if (pk::get_kunshu_id(attacker) == ����_����)
                            troops_damage *= 1.1f;
                        else if (pk::get_kunshu_id(attacker) == ����_����)
                            troops_damage *= 1.1f;
                        else if (pk::get_kunshu_id(attacker) == ����_����)
                            troops_damage *= 1.1f;
                        else if (pk::get_kunshu_id(attacker) == ����_����)
                            troops_damage *= 1.1f;
                        else if (pk::get_kunshu_id(attacker) == ����_�հ�)
                            troops_damage *= 1.1f;
                        
                        else 	
                            troops_damage *= 1.0f; 
                    }
					
					break;

				case ����_��:
					if (pk::is_valid_tactics_id(tactics_id))
					{
						if (target_unit.weapon == ����_����)
							troops_damage *= �����_��;
						else if (target_unit.weapon == ����_â)
							troops_damage *= �����_��;
                        else if (target_unit.weapon == ����_��)    //�뺴 �� �߰� ('18.10.1)
							troops_damage *= �����_��;
					}
                    
                    if (pk::has_tech(force, �ⱳ_�����غ�))
                        troops_damage *= �����ⱳ_���ݷ�; // 1.15f
                    else if (pk::has_tech(force, �ⱳ_�غ��ܷ�))
                        troops_damage *= �ܷñⱳ_���ݷ�; // 1.10f;
                    
					// �̹��� Ư�� (ģ��, ģ��)
					if (����Ư�⼳�� and (attacker.has_skill(Ư��_ģ��) or attacker.has_skill(Ư��_ģ��)) and !pk::is_campaign())
                    {
						troops_damage *= 1.15f;
                        
                        if (��ȭǥ�ü��� and pk::is_player_controlled(attacker))
                        {
                            if (attacker.has_skill(Ư��_ģ��))
                            {
                                //pk::say(pk::encode("�̰��� �������� �����̴�"), pk::get_person(attacker.leader));
                                @msg_unit = @attacker;
                                @msg_person = pk::get_person(attacker.leader);
                                msg_string = "�̰��� �������� �����̴�";
                            }
                            else if (attacker.has_skill(Ư��_ģ��))
                            {
                                //pk::say(pk::encode("�̰��� ������� �����̴�"), pk::get_person(attacker.leader));
                                @msg_unit = @attacker;
                                @msg_person = pk::get_person(attacker.leader);
                                msg_string = "�̰��� ������� �����̴�";
                            }
                        }
                    }
                    
                    // ���º� �ܷñⱳ ����Ƽ�� [����, ����, ����, ����, ��ȹ]�� ������ ��� ('18.9.30)
                    if (����ȿ������ and pk::has_tech(force, �ⱳ_�غ��ܷ�) and !pk::is_campaign())
                    {
                        
                        if (pk::get_kunshu_id(attacker) == ����_����)
                            troops_damage *= 1.1f;
                        else if (pk::get_kunshu_id(attacker) == ����_����)
                            troops_damage *= 1.1f;
                        else if (pk::get_kunshu_id(attacker) == ����_����)
                            troops_damage *= 1.1f;
                        else if (pk::get_kunshu_id(attacker) == ����_����)
                            troops_damage *= 1.1f;
                        else if (pk::get_kunshu_id(attacker) == ����_��ȹ)
                            troops_damage *= 1.2f;
                        
                        else 	
                            troops_damage *= 1.0f;
                    }
                    
					break;

				case ����_��:
					if (pk::is_valid_tactics_id(tactics_id) and pk::equipment_id_to_heishu(target_unit.weapon) == ����_����)
						troops_damage *= �����_��;
                    
                    if (pk::is_valid_tactics_id(tactics_id) and !pk::is_campaign())    
					{
                        // �⺴ ��� �� ��ȭ ('18.10.1), ���Ÿ� ���� ���� �߰� ('18.11.13)
						if (target_unit.weapon == ����_���� and pk::get_distance(attacker.pos, target_unit.pos) >= 2)
                        {
							troops_damage *= �����_��;
                            
                            if (pk::has_tech(force, �ⱳ_����)) // ���� �ⱳ �� �⺴ ��� �� �߰� ('18.10.5)
                                troops_damage *= �����_��;
                        }
                        else if ((target_unit.weapon == ����_��) and (target_unit.has_tech(�ⱳ_ȭ�����)))  // �غ� �� �ⱳȿ�� ���� ('18.10.5)
							troops_damage *= �����_��;
					}
                    
                    if (pk::has_tech(force, �ⱳ_�����뺴))
                        troops_damage *= �����ⱳ_���ݷ�; // 1.15f
                    else if (pk::has_tech(force, �ⱳ_�뺴�ܷ�))
                        troops_damage *= �ܷñⱳ_���ݷ�; // 1.10f;
                    
                    
                    // �ص� Ư���� ��ȭ�� ȿ�� ( ('18.10.14)
					if (����Ư�⼳�� and attacker.has_skill(Ư��_�ص�) and !pk::is_campaign())
                    {   
                        if (!target_unit.has_skill(Ư��_�ص�))
                        {
                            troops_damage *= 1.15f;
                            
                            if (��ȭǥ�ü��� and pk::is_player_controlled(attacker))
                            {
                                //pk::say(pk::encode("�̰��� ��ȭ���� �����̴�"), pk::get_person(attacker.leader));
                                @msg_unit = @attacker;
                                @msg_person = pk::get_person(attacker.leader);
                                msg_string = "�̰��� ��ȭ���� �����̴�";
                            }
                        }
                    }
                    
                    // ���º� �ܷñⱳ ����Ƽ��[�ձ�, ��å, ��ǥ, ����]�� ������ ��� ('18.9.30)
                    if (����ȿ������ and pk::has_tech(force, �ⱳ_�뺴�ܷ�) and !pk::is_campaign())
                    {
                        
                        if (pk::get_kunshu_id(attacker) == ����_�ձ�)
                            troops_damage *= 1.2f;
                        else if (pk::get_kunshu_id(attacker) == ����_��å)
                            troops_damage *= 1.2f;
                        else if (pk::get_kunshu_id(attacker) == ����_��ǥ)
                            troops_damage *= 1.1f;
                        else if (pk::get_kunshu_id(attacker) == ����_����)
                            troops_damage *= 1.1f;
                        
                        else 	
                            troops_damage *= 1.0f;
                    }
                    
					break;

				case ����_����:
					if (pk::is_valid_tactics_id(tactics_id))
					{
						if (target_unit.weapon == ����_â)
							troops_damage *= �����_��;
						else if (target_unit.weapon == ����_��)
							troops_damage *= �����_��;
                        //�뺴 ��� �� ��ȭ('18.10), ���� ���� ���� ('18.11.13)
                        else if (target_unit.weapon == ����_�� and (pk::get_distance(attacker.pos, target_unit.pos) <= 1)  and !pk::is_campaign())    
							troops_damage *= �����_��;
					}
					
                    if (pk::has_tech(force, �ⱳ_�����⺴))
                        troops_damage *= �����ⱳ_���ݷ�; // 1.15f
                    else if (pk::has_tech(force, �ⱳ_�⺴�ܷ�))
                        troops_damage *= �ܷñⱳ_���ݷ�; // 1.10f;
                    
					// �̹��� Ư�� (ģ��, ģ��) : ���� �⺴���ݸ� ���� ('18.10.28)
                    if (!pk::is_campaign())
                    {
                        if (����Ư�⼳�� and (attacker.has_skill(Ư��_ģ��) or attacker.has_skill(Ư��_ģ��)) and (pk::get_distance(attacker.pos, target_unit.pos) <= 1) )
                        {
                            troops_damage *= 1.15f;
                            
                            if (��ȭǥ�ü��� and pk::is_player_controlled(attacker))
                            {
                                if (attacker.has_skill(Ư��_ģ��))
                                {
                                    //pk::say(pk::encode("�̰��� �����⺴�� �����̴�"), pk::get_person(attacker.leader));
                                    @msg_unit = @attacker;
                                    @msg_person = pk::get_person(attacker.leader);
                                    msg_string = "�̰��� �����⺴�� �����̴�";
                                }
                                else if (attacker.has_skill(Ư��_ģ��))
                                {
                                    //pk::say(pk::encode("�̰��� ��ȯ�⺴�� �����̴�"), pk::get_person(attacker.leader));
                                    @msg_unit = @attacker;
                                    @msg_person = pk::get_person(attacker.leader);
                                    msg_string = "�̰��� ��ȯ�⺴�� �����̴�";
                                }
                            }
                        }
                    }
                    // �鸶_Ư�� : ȭ����ݷ� ���� ('18.10.28), �ݰݿ� ������ ('18.11.18)
                    if (!pk::is_campaign())
                    {
                        if (����Ư�⼳�� and attacker.has_skill(Ư��_�鸶) and !target_unit.has_skill(Ư��_�鸶) and (pk::get_distance(attacker.pos, target_unit.pos) > 1) and type == 0)
                        {
                            if (pk::has_tech(force, �ⱳ_���))  // �ⱳ_��� ���� �� ������ ����
                                troops_damage *= 1.4f;
                            else 
                                troops_damage *= 1.2f;
                            
                            if (��ȭǥ�ü��� and pk::is_player_controlled(attacker))
                            {
                                //pk::say(pk::encode("�̰��� �鸶�⺴���� �����̴�"), pk::get_person(attacker.leader));
                                @msg_unit = @attacker;
                                @msg_person = pk::get_person(attacker.leader);
                                msg_string = "�̰��� �鸶�⺴���� �����̴�";
                                
                            }
                        }
                    }
                    // ���º� �ܷñⱳ ����Ƽ�� [���, ������, ����, ����, ��Ź, ����]�� ������ ��� ('18.9.30)
                    if (����ȿ������ and pk::has_tech(force, �ⱳ_�⺴�ܷ�) and !pk::is_campaign())
                    {
                        
                        if (pk::get_kunshu_id(attacker) == ����_������)
                            troops_damage *= 1.2f;
                        else if (pk::get_kunshu_id(attacker) == ����_����)
                            troops_damage *= 1.2f;
                        else if (pk::get_kunshu_id(attacker) == ����_����)
                            troops_damage *= 1.2f;
                        else if (pk::get_kunshu_id(attacker) == ����_����)
                            troops_damage *= 1.2f;
                        else if (pk::get_kunshu_id(attacker) == ����_��Ź)
                            troops_damage *= 1.1f;
                        else if (pk::get_kunshu_id(attacker) == ����_���)
                            troops_damage *= 1.1f;
                        
                        else 	
                            troops_damage *= 1.0f;
                    }
                    
						
					break;

				case ����_����:
                    if (pk::is_valid_tactics_id(tactics_id) and !pk::is_campaign())    
					{
						if (target_unit.weapon == ����_����)    // �⺴ ��� �� ��ȭ ('18.10.1)
                        {
							troops_damage *= �����_��;
                            
                            if (pk::has_tech(force, �ⱳ_����)) // ���� �ⱳ �� �⺴ ��� �� �߰� ('18.10.5)
                                troops_damage *= �����_��;
                        }
                        else if ((target_unit.weapon == ����_��) and (target_unit.has_tech(�ⱳ_ȭ�����)))  // �غ� ��� �ⱳȿ�� ���� ('18.10.5)
							troops_damage *= �����_��;
					}
                    
                    // �ص� Ư���� ��ȭ�� ȿ�� ('18.10.14)
					if (����Ư�⼳�� and attacker.has_skill(Ư��_�ص�) and !pk::is_campaign())
                    {   
                        if (!target_unit.has_skill(Ư��_�ص�))
                        {
                            troops_damage *= 1.15f;
                            
                            if (��ȭǥ�ü��� and pk::is_player_controlled(attacker))
                            {
                                //pk::say(pk::encode("�̰��� ��ȭ���� �����̴�"), pk::get_person(attacker.leader));
                                @msg_unit = @attacker;
                                @msg_person = pk::get_person(attacker.leader);
                                msg_string = "�̰��� ��ȭ���� �����̴�";
                            }
                        }
                    }
                    
                    break;
				
				case ����_�ְ�:
				
					// ���� ���� Ư�� (��Ÿ, ����)
                    if(!pk::is_campaign())
                    {
                        if (attacker.has_skill(Ư��_��Ÿ) or attacker.has_skill(Ư��_����))
                            troops_damage *= 1.05f;
                    }
                    break;
                    
				case ����_����:
				
					// ���� ���� Ư�� (��Ÿ, ����)
                    if(!pk::is_campaign())
                    {
                        if (attacker.has_skill(Ư��_��Ÿ) or attacker.has_skill(Ư��_����))
                            troops_damage *= 1.10f;
                    }                    
					break;
                    
				case ����_����:
					if (pk::is_valid_tactics_id(tactics_id) and pk::equipment_id_to_heishu(target_unit.weapon) == ����_����)
						troops_damage *= 0.8f;
					
					// ���� ���� Ư�� (��Ÿ, ����)
                    if(!pk::is_campaign())
                    {
                        if (attacker.has_skill(Ư��_��Ÿ) or attacker.has_skill(Ư��_����))
                            troops_damage *= 1.15;
                    }
					
					break;
				}
                
                // ������ ����δ뿡 ���� ȭ�� ������ �߰� ('18.10.21)
                // ���� : �տ�, ��ǥ ���� ���� �ι����� ������ ��� - ���ú� �ⱳ ����Ƽ�� ('18.10.21)
                if (pk::is_in_water(attacker) and (attacker.type == �δ�����_����) and !pk::is_campaign())
                {
                    if (pk::is_valid_tactics_id(tactics_id) and (tactics_id == ����_ȭ�� or tactics_id == ����_����ȭ�� or tactics_id == ����_�Լ�ȭ��) )    
					{
						if (!pk::is_in_water(target_unit) and target_unit.weapon == ����_����)    // �⺴ ��� �� ��ȭ ('18.10.1)
                        {
							troops_damage *= �����_��;
                            
                            if (pk::has_tech(force, �ⱳ_����)) // ���� �ⱳ �� �⺴ ��� �� �߰� ('18.10.5)
                                troops_damage *= �����_��;
                        }
                        else if (!pk::is_in_water(target_unit) and (target_unit.weapon == ����_��) and (target_unit.has_tech(�ⱳ_ȭ�����)))  // �غ� ��� �ⱳȿ�� ���� ('18.10.5)
							troops_damage *= �����_��;
                        
					}
                    
                    if (����ȿ������ and pk::has_tech(force, �ⱳ_���ú�))
                    {
                        
                        if (pk::get_kunshu_id(attacker) == ����_�հ�)
                            troops_damage *= 1.2f;
                        else if (pk::get_kunshu_id(attacker) == ����_��å)
                            troops_damage *= 1.2f;
                        else if (pk::get_kunshu_id(attacker) == ����_�ձ�)
                            troops_damage *= 1.15f;
                        else if (pk::get_kunshu_id(attacker) == pk::get_kunshu_id(pk::get_person(����_����)))
                            troops_damage *= 1.15f;
                        else if (pk::get_kunshu_id(attacker) == pk::get_kunshu_id(pk::get_person(����_����)))
                            troops_damage *= 1.15f;
                        else if (pk::get_kunshu_id(attacker) == ����_��ǥ)
                            troops_damage *= 1.1f;
                        else if (pk::get_kunshu_id(attacker) == pk::get_kunshu_id(pk::get_person(����_ä��)))
                            troops_damage *= 1.1f;
                        
                        else
                            troops_damage *= 1.1f;
                        
                    }
                }
                
                

				if (attacker.is_player())
					troops_damage *= float(pk::core["������г�Ƽ"][pk::get_scenario().difficulty]);

                // �������� ���� ������ ũ��Ƽ�� ���ݷ� ���� ���� ('18.11.5)
                if (������������ and !pk::is_campaign())
                {
                    if (func_tactics_city(attacker, weapon_id))
                        ũ��Ƽ��_���ݷ� += 0.05f;
                }
                        
				if (type == 0)
				{
					if (info.critical)
						troops_damage *= ũ��Ƽ��_���ݷ�; // 1.15f;

					info.troops_damage = int(troops_damage);
					if (func_5af230(info, attacker, target_unit, tactics_id))
						troops_damage = 0;
					
                    info.energy_damage = 0;
					if (attacker.has_skill(Ư��_����))
						info.energy_damage += pk::max(0, int(pk::core::skill_constant(attacker, Ư��_����))); // 5

                    if (attacker.has_skill(Ư��_��ǳ))      // ����+��ǳ ��ø ȿ���� ���� ('18.10.9)
						info.energy_damage += pk::max(0, int(pk::core::skill_constant(attacker, Ư��_��ǳ))); // 20

                    if (attacker.has_skill(Ư��_�Ӿ�))      // Ư�� �Ӿ� ȿ�� �ݿ�, �ݰݿ��� ���� �ȵ� ('18.10.21)
                        info.energy_heal = 5;
                    
                    // â�� ���� ����
                    info.food_damage = func_5aecc0(attacker, target_unit);  
					info.food_heal = info.food_damage;
				}
				else
				{
					if (type == 1)
						troops_damage *= 0.9f;
					else if (type == 2)
						troops_damage *= 0.4f;

					// �ݰ��̱� ������ target_unit�� ������ ������ �δ븦 ����.
					if (pk::is_in_water(target_unit))
					{
						if (target_unit.has_skill(Ư��_����) and pk::rand_bool(int(pk::core::skill_constant(target_unit, Ư��_����))))
						{
							troops_damage = 0;
							info.def_skill = Ư��_����;
						}
					}
					else
					{
						if (target_unit.has_skill(Ư��_�޽�) and 
                            (pk::get_hex(target_unit.pos).terrain == ����_�� or pk::rand_bool(int(pk::core::skill_constant(target_unit, Ư��_�޽�))) ) )
						{
							troops_damage = 0;
							info.def_skill = Ư��_�޽�;
						}
					}
				}

				if (target_unit.has_skill(Ư��_�))
                {
					troops_damage = troops_damage / 2;
                    if (��ȭǥ�ü��� and pk::is_player_controlled(attacker))
                    {
                        @msg_unit = @attacker;
                        @msg_person = pk::get_person(target_unit.leader);
                        msg_string = "�츮 ��δ뿡 �¼��ٴ�. ��.";
                    }
                }

				if (info.debuffer == �ü�_��)
					troops_damage *= 0.85f;
				else if (info.debuffer == �ü�_���)
					troops_damage *= 0.75f;
				if (info.debuffer == �ü�_��ä)
					troops_damage *= 0.65f;
                
                if (!pk::is_campaign())
                {
                    // �δ� �� ���� �� �δ���⿡ ���� ������ ���� ('18.11.27)
                    if (�������⼳��)
                    {
                        int damage_dir = func_unit_direction(attacker, target_unit);
                        troops_damage = troops_damage * func_dir_weight(damage_dir);
                        
                        // �Ĺ��ǰݽ� ȥ��ȿ�� ����
                        if (�Ĺ��ǰݽ�_ȥ������ and type == 0 and damage_dir == 3 and int(troops_damage) > 0)
                            @back_unit = target_unit;
                    }
                    
                    // �δ� �� ���� �� �ֺ��δ� ����� �߰� ('18.10.28)
                    if (�ֺ��δ뼳��)
                    {
                        troops_damage = troops_damage * (1.f + func_neighbor_buf(attacker, true)) * (1.f - func_neighbor_buf(target_unit, false));
                    }

                    // �δ� �� ���� �� ������ ���� ȿ�� �߰� ('18.10.11)
                    if (����ȿ������)
                    {
                        troops_damage = troops_damage * (1.f + func_terrain_buf(attacker)) * (1.f - func_terrain_buf(target_unit)); //���� ����
                        troops_damage = troops_damage * (1.f + 0.01f * get_height_diff(attacker.get_pos(), target_unit.get_pos())); //���� ������
                    }
                    
                    
                    // �δ밣 ���� �� ��ȣ ��� ���� �ݿ��� ('18.10.6)
                    if (���ȿ������)
                    {
                        // �����ݺδ� ��¿� ���� �ǰݺδ� ���� 85% ~ 115% ���� : �δ� ��� ȿ�� ('18.10.6)
                        troops_damage = troops_damage * (0.85f + 0.30f * (attacker.energy/120.f)) ;
                        // ���ǰݺδ� ��¿� ���� �ǰݺδ� ���� 85% ~ 115% ���� : �δ� ��� ȿ�� ('18.10.6)
                        troops_damage = troops_damage * (0.85f + 0.30f * ((120 - target_unit.energy)/120.f)) ;
                    }
                    
                    // ��ü���� �⺻ ������� ���� ('18.11.08)
                    troops_damage *= ���������;
                }
                
                // ���� ���ط��� ���� �ǰݴ�� ��°���, ���ݺδ� ��»�� ȿ�� �߻�, �ݰݵ� ����� ('18.10.6)
                if (����������� and !pk::is_campaign())
                {
                    if (pk::is_enemy(attacker, target_unit))  // ���� �ٸ� ������ �δ밣 ���� �ÿ��� ���ȸ�� : ���� �跫 �� ���ȸ�� ���� ('18.10.22)
                    {
                        info.energy_heal = info.energy_heal + int(pk::min(5.f, (troops_damage / 200.f)));   //���� ������������ ���� ��� ������� ������ ����
                    
                        if (troops_damage >= 500)
                        {
                            info.energy_damage = info.energy_damage + int((troops_damage - 500) / 100.f);
                        
                            if (target_unit.has_skill(Ư��_ȣ��))  // Ư��_ȣ�� ���� �δ�� �������� �־ ��� ���� ���� ('18.10.14)
                                info.energy_damage = 0;
                        }
                    }
                    else    // ����(�Ʊ����� ����) �� ���ȸ�� ����, ���������� ����Ͽ� ��� ������ �߻� ('18.10.25)
                    {
                        info.energy_damage = info.energy_damage + int(troops_damage / 100.f);
                    }
                }
                
				info.troops_damage = int(troops_damage);
                
                // �δ���� ���� �� �޽��� �߰� ('19.2.17)
                if (type == 0 and info.troops_damage == 0 and !pk::is_campaign())
                {
                    @msg_unit = @attacker;
                    @msg_person = pk::get_person(attacker.leader);
                    msg_string = "������ ������ �ʴ°�";
                }
                
                // Ư�� �ߵ� �� ���� ��ȿ ��Ÿ� �� �������� Ȯ��, ��Ư�⿬�� ������� ��ġ�� ('19.11.10)
                if (��Ư�⿬��_�ߵ����� and attacker.has_skill(Ư��_����) and pk::is_valid_tactics_id(tactics_id) and !pk::is_campaign())
                {
                    if (pk::is_alive(target_unit) and !func_tactics_valid_target(attacker, target_unit, tactics_id))
                    {
                        info.critical = false;      // ������
                        info.tactics_hit = false;   // ��������
                        info.troops_damage = 0;     // ��������ȿ
                        info.energy_damage = 0;     // ��������ȿ
                        info.food_damage = 0;       // ��������ȿ
                        info.energy_heal = 0;       // ��������ȿ
                        info.food_heal = 0;         // ��������ȿ
                    }
                }
                
                //---------------------------------------------------------------------------------------
                
			}
            // ���� ���� (����)
			else if (target_building !is null and pk::is_general_type(target_building))
			{
				info.dst_troops = pk::get_troops(target_building);

				int facility_id = target_building.facility;
				int troops_atk, dst_atk, dst_def, dst_troops;
                
                // �� �¼� �ɷ�ġ                
				func_5af0e0(troops_atk, dst_atk, dst_def, dst_troops, target_building);
				// ���� ���ط� �⺻
                float troops_damage = func_5aee60(atk, command, troops_atk, buffed, dst_def, dst_troops);

				if (attacker.weapon == ����_����)
				{
					troops_damage *= 1.8f;
				}
				else if (attacker.weapon == ����_����)
				{
					troops_damage *= 1.2f;
				}
				else
				{
                    // ���� ���� ���ط� �缳��
					troops_damage = func_5aee60(atk, int(pk::max(command * 0.75f, 1.f)), troops_atk, buffed, dst_def, dst_troops);
					if (facility_id == �ü�_����)
						troops_damage *= 0.55f;
					else if (facility_id == �ü�_����)
						troops_damage *= 0.45f;
					else if (facility_id == �ü�_�ױ�)
						troops_damage *= 0.60f;
				}

				if (attacker.is_player())
					troops_damage *= float(pk::core["������г�Ƽ"][pk::get_scenario().difficulty]);

				if (type == 0)
				{
					if (info.critical)
						troops_damage *= ũ��Ƽ��_���ݷ�;
                    
                    // �ұ�/�ݰ� Ư�� ����� ������ ���� �� Ư�� �ߵ��Ͽ� �������� ���� �氨 ('18.10.9)
                    if (�������Ư�� and !pk::is_campaign())
                    {
                        int siege_type = 1;     // 1:���� ����, 2:���� ������
                        int defskill_rate = 30;    // Ȯ�� 30%�� ����
                        if (func_citydef_skill(info, target_building, siege_type, defskill_rate) == 1)       // 0: ���Ư�� ����, 1:�ұ�/�ݰ�, 2:ö��
                        {
                            troops_damage *= (defskill_rate/100.f);   // ���� 0 ���� ���� �� ������ �� ����
                            
                            if (��ȭǥ�ü��� and pk::is_player_controlled(attacker))
                            {
                                //pk::say(pk::encode("�����Ҷ��� �����"), pk::get_person(attacker.leader));
                                @msg_unit = @attacker;
                                @msg_person = pk::get_person(attacker.leader);
                                msg_string = "�����Ҷ��� �����";
                            }
                        }
                    }
                    
				}
				else
				{
					if (type == 1)
						troops_damage *= 0.9f;
					else if (type == 2)
						troops_damage *= 0.4f;

					// �ݰ��̱� ������ target_unit�� ������ ������ �δ븦 ����.
					if (pk::is_in_water(target_unit))
					{
						if (target_unit.has_skill(Ư��_����) and pk::rand_bool(int(pk::core::skill_constant(target_unit, Ư��_����))))
						{
							troops_damage = 0;
							info.def_skill = Ư��_����;
						}
					}
					else
					{
						if (target_unit.has_skill(Ư��_�޽�) and 
                            (pk::get_hex(target_unit.pos).terrain == ����_�� or pk::rand_bool(int(pk::core::skill_constant(target_unit, Ư��_�޽�))) ) )
						{
							troops_damage = 0;
							info.def_skill = Ư��_�޽�;
						}
					}
				}
                
                if(!pk::is_campaign())
                {
                    // �δ��ǹ� ���� �ÿ��� �ݿ���, �ǹ� �ݰ��� "�ǹ��� ���� �����.cpp" �����ؾ� �� ('18.10.7)
                    if (���ȿ������)
                    {
                        // �����ݺδ� ��¿� ���� �ǰݴ�� ���� 85% ~ 115% ���� : �δ� ��� ȿ�� ('18.10.6)
                        troops_damage = troops_damage * (0.85f + 0.30f * (attacker.energy/120.f)) ;
                        // ���ǰݴ�� ��¿� ���� �ǰݴ�� ���� 85% ~ 115% ���� : �δ� ��� ȿ�� ('18.10.6)
                        troops_damage = troops_damage * (0.85f + 0.30f * ((120 - target_building.energy)/120.f)) ;
                    }
                    
                    // ��ü���� ������� ���� ('18.11.08)
                    troops_damage *= ���������;
                    
                    // ���� ���ط��� ���� �ǰݴ�� ��°���, ���ݺδ� ��»�� ȿ�� �߻�, �ǹ��ݰ� ����ȵ� ('18.10.6)
                    if (�����������)
                    {
                        info.energy_heal = int(pk::min(5.f, (troops_damage / 200.f)));      //���� ������������ ���� ��� ������� ������ ����
                        if (troops_damage >= 200)
                            info.energy_damage = int((troops_damage - 200) / 100.f);
                    }
                }
                
				info.troops_damage = int(troops_damage);
                
			}
            // ���� ���� (������ & ����)
			if (target_building !is null)
			{
				int facility_id = target_building.facility;
				int hp_atk = 0;
				float hp_damage = 0;

				hp_atk = 5;
				if (pk::is_valid_tactics_id(tactics_id))
					hp_atk = pk::get_tactics(tactics_id).hp_atk;
				else if (pk::is_neighbor_pos(attacker.get_pos(), target_pos))
					hp_atk = 15;
                
                // ���⺰ ������ ������
				if (attacker.weapon == ����_���� or attacker.weapon == ����_���)
					hp_damage = func_5af050(atk, command, hp_atk, buffed);
				else
					hp_damage = func_5aeff0(atk, command, hp_atk, buffed);

                // ũ��Ƽ��
				if (info.critical)
					hp_damage *= ũ��Ƽ��_���ݷ�;

                // ���Ǻ� ����
				if (facility_id >= �ü�_�Ҿ� and facility_id <= �ü�_��ȭ��)
				{
					hp_damage *= 1.6f;
				}
				else if (facility_id >= �ü�_���� and facility_id <= �ü�_����3��)
				{
					hp_damage *= 1.1f;
				}
				else if (facility_id == �ü�_����)
				{
					hp_damage *= 0.7f;
				}
				else if (attacker.weapon != ����_���� and attacker.weapon != ����_���)
				{
					switch (facility_id)
					{
					case �ü�_����:
                    case �ü�_����:
                    case �ü�_�ױ�:
					case �ü�_�����:
					case �ü�_���:
						hp_damage *= 0.9f;
						break;
					case �ü�_����:
						hp_damage *= 0.7f;
						break;
					case �ü�_��:
						hp_damage *= 0.8f;
						break;
					case �ü�_���:
                        hp_damage *= 0.7f;
						break;
					case �ü�_��ä:
						hp_damage *= 0.6f;
						break;
					}
				}
                
                // ���������� �����ļ� ������ ���� ('20.4.11)
                if (attacker.weapon <= ����_���� and tactics_id == ����_�����ļ�)
                    hp_damage *= 0.3f;
                
                
                // ���� ���� �ⱳ�� ���� ������ ������ݿ� ���� ���� ������ ���� ('18.10.28)
                if (facility_id <= �ü�_�ױ� and (attacker.weapon >= ����_���� and attacker.weapon <= ����_���) )
                {
                    if (target_building.has_tech(�ⱳ_������ȭ))
                        hp_damage *= 0.70f;
                    else if (target_building.has_tech(�ⱳ_�ü���ȭ))
                        hp_damage *= 0.85f;
                    else
                        hp_damage *= 1.00f;
                }
                    
                

				if (facility_id == �ü�_���� and not target_building.completed)
					hp_damage = 0;

				if (attacker.has_tech(�ⱳ_����))
				{
					if (attacker.weapon >= ����_�� and attacker.weapon <= ����_����)
					{
						info.troops_damage = int(info.troops_damage * 1.4f);
						hp_damage *= 1.4f;
					}
					else
					{
						info.troops_damage = int(info.troops_damage * 1.2f);
						hp_damage *= 1.2f;
					}
				}

				if (attacker.is_player())
					hp_damage *= float(pk::core["������г�Ƽ"][pk::get_scenario().difficulty]);
                
                if (!pk::is_campaign())
                {                    
                    // ö�� Ư�� ����� ������ ���� �� Ư�� �ߵ��Ͽ� ������ ���� �氨 ('18.10.11)
                    if (�������Ư��)
                    {
                        int siege_type = 2;     // 1:���� ����, 2:���� ������
                        int defskill_rate = 30;    // Ȯ�� 30%�� ����
                        if (func_citydef_skill(info, target_building, siege_type, defskill_rate) == 2)       // 0: ���Ư�� ����, 1:�ұ�/�ݰ�, 2:ö��
                        {
                            hp_damage *= (defskill_rate/100.f);   // ���� 0 ���� ���� �� �뷱�� ������ �� ����
                            
                            if (��ȭǥ�ü��� and pk::is_player_controlled(attacker))
                            {
                                //pk::say(pk::encode("������ ưư�Ѱ�"), pk::get_person(attacker.leader));
                                @msg_unit = @attacker;
                                @msg_person = pk::get_person(attacker.leader);
                                msg_string = "������ ưư�Ѱ�";
                            }
                        }
                    }
                    
                    // �δ��ǹ� ���� �� ������ ���ط� ���� ('18.10.7)
                    if (���ȿ������)
                    {
                        // ���ݺδ� ��¿� ���� �ǰݴ�� ���� 85% ~ 115% ���� : �δ� ��� ȿ�� ('18.10.6)
                        hp_damage = hp_damage * (0.85f + 0.30f * (attacker.energy/120.f)) ;
                        // �ǰݴ�� ��¿� ���� �ǰݴ�� ���� 85% ~ 115% ���� : �δ� ��� ȿ�� ('18.10.6)
                        hp_damage = hp_damage * (0.85f + 0.30f * ((120 - target_building.energy)/120.f)) ;
                    }
                    
                    // ��ü���� ������� ���� ('18.11.08)
                    hp_damage *= ���������;
                }
                
				info.hp_damage = int(hp_damage);
			}		

			info.tactics = tactics_id;
			info.src_pos = attacker.get_pos();
			info.dst_pos = target_pos;
            
            
            // ����÷ȥ��Ȯ��_��������('19.2.21)
            if (����÷ȥ��Ȯ��_�������� and (tactics_id == ����_����÷) and info.tactics_hit and !pk::is_campaign())
            {
                @nasun_unit = @target_unit;
                ����÷_ũ��Ƽ�� = info.critical;
                ����÷_�ǰ��ൿ = target_unit.action_done;
                ����÷_�ǰݻ��� = target_unit.status;
                ����÷_�ǰ�Ÿ�̸� = target_unit.status_timer;
            }
            
            
		}

		/**
			â�� �������� ȹ�� ���� ���
		*/
		int func_5aecc0(pk::unit@ attacker, pk::unit@ target)
		{
			if (pk::is_alive(attacker) and pk::is_alive(target) and attacker.weapon == ����_â and attacker.has_tech(�ⱳ_��������))
			{
				int a = pk::rand(attacker.attr.stat[�δ�ɷ�_����]) + attacker.attr.stat[�δ�ɷ�_����];
				int b = pk::max(attacker.troops / 2, 1);
				int c = target.food;
				int d = pk::get_max_food(attacker) - attacker.food;
				return pk::min(a, b, c, d);
			}
			return 0;
		}

		/**
			���ݷ� ��� ȿ���� ���� �ü� �˻�
		*/
		bool func_5aed80(const pk::point &in pos, int force_id)
		{
			/*
			array<pk::point> range = pk::range(pos, 1, 3);
			for (int i = 0; i < range.length; i++)
			{
				pk::building@ building = pk::get_building(range[i]);
				if (pk::is_alive(building) and building.facility == �ü�_�°�� and building.completed and building.get_force_id() == force_id)
					return true;
			}
			return false;
			*/

			array<pk::point> range = pk::range(pos, 1, int(pk::core["�ü�.�ִ����"]));
			for (int i = 0; i < int(range.length); i++)
			{
				pk::building@ building = pk::get_building(range[i]);
				if (pk::is_alive(building) and building.completed and building.get_force_id() == force_id)
				{
					if (bool(pk::core["�ü�"][building.facility]["���ݷ»��"]) and pk::get_distance(pos, range[i]) <= int(pk::get_facility(building.facility).max_range))
						return true;
				}
			}
			return false;
		}

		/**
			��, ���, ��ä �˻�
            ����, ����, �ױ� �˻� �߰� ('18.10.28)
		*/
		bool func_5aedc0(const pk::point &in pos, int min, int max, int force_id)
		{
			array<pk::point> range = pk::range(pos, min, max);
			for (int i = 0; i < int(range.length); i++)
			{
				pk::building@ building = pk::get_building(range[i]);
				if (pk::is_alive(building) and (building.facility == �ü�_�� or building.facility == �ü�_��� or building.facility == �ü�_��ä) and building.completed and building.get_force_id() == force_id)
					return true;
                
                if (����������)
                {
                    if (pk::is_alive(building) and (building.facility == �ü�_���� or building.facility == �ü�_���� or building.facility == �ü�_�ױ�) and building.get_force_id() == force_id)
                        return true;
                }
                
			}
			return false;
		}

		/**
			���� ������ ���� ��
		*/
		int func_5aee10(pk::unit@ unit)
		{
			pk::person@ leader = pk::get_person(unit.leader);
			if (pk::is_alive(leader))
				return pk::min(pk::get_command(leader), unit.troops);
			return unit.troops;
		}

		/** �δ�/���� ���� ���� ��� **/
		float func_5aee60(int src_atk, int src_troops, int tactics_atk, int buffed, int dst_def, int dst_troops)
		{
			float n = 0;
			int a = 0;
			int b = 0;
			int c = 0;

			a = pk::max(src_atk, 40);
			a = a * a;

			b = pk::max(dst_def, 40);
			b = b * b;

			//n = pk::sqrt(tactics_atk * 64);
			n = sqrt(tactics_atk * 64);
			n = n + pk::max((src_troops - dst_troops) / 2000, 0);
			n = n + pk::max((a - b) / 300, 0);
			n = n + 50;
			n = n * (buffed + 10);

			a = (src_troops / 100 + 300) * (src_atk + 50) * (src_atk + 50) / 100;
			b = (dst_troops / 100 + 300) * (dst_def + 50) * (dst_def + 50) / 100;
			c = a + b;
			if (a >= b)
				c = a * 100 / c;
			else
				c = pk::max(100 - (b * 100 / c), 1);
			n = n * c;

			a = pk::max(src_troops / 4, 1);
			n = n * pk::min(sqrt(a), 40.f);

			n = n / 2100;
			n = n + src_troops / 200;

			return n;
		}

		/** �¼��� ����鿡 ���� ������ �����ɷ� **/
        //���� �� "�ź�_�Ϲ�" �� ���� �ɷ� �ݿ� (�� ������ ����, ���, ���� �κ� �ջ�) ('18.10.7)
		void func_5af0e0(int &out src_atk, int &out dst_atk, int &out dst_def, int &out dst_troops, pk::building@ building)
		{
			src_atk = 10;
            
			pk::person@ taishu = pk::get_person(pk::get_taishu_id(building));
			if (pk::is_alive(taishu))
			{
                //�¼� �ɷ� �ݿ� (�⺻)
				dst_atk = pk::max(taishu.stat[����ɷ�_����] - 25, 40);
				dst_def = pk::max(taishu.stat[����ɷ�_���] - 25, 40);
				dst_troops = pk::min(pk::get_troops(building), pk::get_command(taishu));
                
                //���� �� "�ź�_�Ϲ�" �� ���� �ɷ� �ݿ� (�� ������ ����, ���, ���� �κ� �ջ�) ('18.10.7)
                if (�����ɷ��ջ�)
                {
                    float ilban_support = 5;    // �¼� �� ���� �ɷ� ġ �ջ� ������ : ���庰 5%
                    auto ilban_list = pk::list_to_array(pk::get_person_list(building, pk::mibun_flags(�ź�_�Ϲ�) ) );
                    if (0 < ilban_list.length)
                    {
                        for (int i = 0; i < int(ilban_list.length); i++)
                        {
                            pk::person@ ilban = ilban_list[i];
                            //���� �Ǵ� ������ ���°� �ƴ� ����̸�, �¼��� ���� ���谡 �ƴ� ����� �ɷ� ġ �ջ�
                            if (!pk::is_unitize(ilban) and !pk::is_absent(ilban) and !pk::is_dislike(taishu, ilban.get_id()) and !pk::is_dislike(ilban, taishu.get_id()) )
                            {
                                dst_atk += int((pk::max(ilban.stat[����ɷ�_����] - 25, 20)) * (ilban_support / 100.f));
                                dst_def += int((pk::max(ilban.stat[����ɷ�_���] - 25, 20)) * (ilban_support / 100.f));
                                dst_troops += int((pk::min(pk::get_troops(building), pk::get_command(ilban))) * (ilban_support / 100.f));
                            }
                        }
                    }
                }
            }
			else
			{
				dst_atk = 30;
				dst_def = 30;
				//dst_troops = pk::min(pk::get_troops(building), 7000);
				dst_troops = pk::min(pk::get_troops(building), 5000); //���ֺ��� ����ġ ����
				if (dst_troops != 0)
					dst_troops = pk::max(dst_troops, 500);
			}
		}

		/** ���� ������ ���� ��� (��Ÿ) **/
		float func_5aeff0(int src_atk, int src_troops, int tactics_atk, int buffed)
		{
			src_troops = pk::max(src_troops, 1);
			float a = sqrt(src_atk * src_atk / 15.f);
			float b = sqrt(src_troops);
			float c = tactics_atk * 4 + 100;
			float d = buffed + 10;
			return a * b * c * d / 10000;
		}

		/** ���� ������ ���� ��� (����/���) **/
		float func_5af050(int src_atk, int src_troops, int tactics_atk, int buffed)
		{
			src_troops = pk::max(src_troops, 1);
			float a = sqrt(src_atk * src_atk / 15.f);
			float b = sqrt(src_troops);
			float c = tactics_atk * 4 + 100;
			float d = buffed + 10;
			return a * pk::min(b, 40.f) * c * d / 10000 + (src_troops / 25) + b;
		}

		/** �δ� ���ⱳ �� ���Ư�� ȿ�� �ݿ� **/
        // ���Ư�� ȿ�� �������� �����ݿ��� ����, �������ݿ��� �ۿ��ϵ��� ��ũ��Ʈ ����
		bool func_5af230(pk::damage_info& info, pk::unit@ attacker, pk::unit@ target, int tactics_id)
		{
            // �������� ���� �κ� ���� ��ũ��Ʈ �̵� : ������/�������� ���� ���� ��� Ư�� �ߵ� ('18.10.9)
            if (target.status == �δ����_���)
            {
                if (target.has_skill(Ư��_�ұ�))
                {
                    if (int(target.troops) < int(pk::core::skill_constant(target, Ư��_�ұ�)) and pk::rand_bool(int(pk::core::skill_constant(target, Ư��_�ұ�, 1))))
                    {
                        info.def_skill = Ư��_�ұ�;
                        
                        if (pk::is_valid_tactics_id(tactics_id))
                            info.tactics_hit = false;
                        
                        return true;
                    }
                }
                float buf_rate = 1.f;
                if (target.has_skill(Ư��_�ݰ�))
                {
                    if (pk::is_valid_tactics_id(tactics_id))    // ������ ������ ��� Ư��_�ߵ� ���ط� ���� x1.5�� ����
                        buf_rate = 1.5f;
                    
                    if (info.troops_damage < (int(pk::core::skill_constant(target, Ư��_�ݰ�))*buf_rate) and pk::rand_bool(int(pk::core::skill_constant(target, Ư��_�ݰ�, 1))))
                    {
                        info.def_skill = Ư��_�ݰ�;
                        
                        if (pk::is_valid_tactics_id(tactics_id))
                            info.tactics_hit = false;

                        return true;
                    }
                }
                
                if (target.has_skill(Ư��_ö��))    // ö�� Ư�� ���� 30% Ȯ���� ��ȿȭ ('19.6.19)
                {
                    if (pk::is_valid_tactics_id(tactics_id) and pk::rand_bool(30))
                    {
                        info.def_skill = Ư��_ö��;
                        info.tactics_hit = false;
                        
                        return true;
                    }
                }
            }
            
            // ���Ư�� ���� ��� ������ �������� Ȯ�� : ������ ��� false ��ȯ �� �Լ� ����, ��Ÿ�� ��� ����� �غ� �ⱳȿ�� ����
            else if (!pk::is_valid_tactics_id(tactics_id))
            {
                pk::point attacker_pos = attacker.get_pos();
                pk::point target_pos = target.get_pos();

                if (target.weapon == ����_��)
                {
                    if (target.has_tech(�ⱳ_ȭ�����))
                    {
                        if (!pk::is_neighbor_pos(attacker_pos, target_pos) and pk::rand_bool(30))
                        {
                            info.def_tech = �ⱳ_ȭ�����;
                            return true;
                        }
                    }
                    if (target.has_tech(�ⱳ_ū����))
                    {
                        if (pk::is_neighbor_pos(attacker_pos, target_pos) and pk::rand_bool(30))
                        {
                            info.def_tech = �ⱳ_ū����;
                            return true;
                        }
                    }
                }
            }

			return false;
		}
        // --------------------------------------------------------
        
        // --------------------------------------------------------
        // �ұ�/�ݰ� Ư�� ����� ������ ���� �� Ư�� �ߵ� ('18.10.9)
        int func_citydef_skill(pk::damage_info& info, pk::building@ building, int siege_type, int defskill_rate)
		{
            auto defender_list = pk::list_to_array(pk::get_person_list(building, pk::mibun_flags(�ź�_����,�ź�_����,�ź�_�¼�,�ź�_�Ϲ�) ) );
            if (0 < defender_list.length)
            {
                for (int i = 0; i < int(defender_list.length); i++)
                {
                    pk::person@ defender = defender_list[i];
                    
                    //���� �Ǵ� ������ ���°� �ƴ� ����� !!!!
                    if (!pk::is_unitize(defender) and !pk::is_absent(defender))
                    {
                        // ������ Ư��_�ұ� ��� ���� ��� �ߵ� ('18.10.9)
                        if ((siege_type == 1) and pk::has_skill(defender, Ư��_�ұ�) and (building.troops < 3000) and pk::rand_bool(defskill_rate))
                            return 1;       // ���� ��� ȿ��

                        // ������ Ư��_�ݰ� ��� ���� ��� �ߵ� ('18.10.9)
                        if ((siege_type == 1) and pk::has_skill(defender, Ư��_�ݰ�) and (info.troops_damage < 500) and pk::rand_bool(defskill_rate))
                            return 1;       // ���� ��� ȿ��
                        
                        // ������ Ư��_ö�� ��� ���� ��� �ߵ� ('18.10.11)
                        if ((siege_type == 2) and pk::has_skill(defender, Ư��_ö��) and pk::rand_bool(defskill_rate))
                            return 2;       // ������ ��� ȿ��
                    }
                }
            }
            return 0;
        }
        
        // --------------------------------------------------------
        
        
        // --------------------------------------------------------
        // �δ� �� ���� �� ������ ���� ������ ����Ƽ�� �߰� ('18.10.11)
        float func_terrain_buf(pk::unit @ unit)
        {
            int weapon_id = unit.weapon;
            float terrain_buf = 0.f;
            pk::hex@ unit_hex = pk::get_hex(unit.get_pos());    // �δ��� ��ǥ
            switch (unit_hex.terrain)                           // ��ǥ�� ����
            {
                case ����_�ʿ�  : 
                                if      (weapon_id == ����_â)   terrain_buf = 0.05f;
                                else if (weapon_id == ����_����)  terrain_buf = 0.10f;
                                break;
                case ����_��  :    
                                if      (weapon_id == ����_â)   terrain_buf = 0.05f;
                                else if (weapon_id == ����_��)   terrain_buf = 0.05f;
                                else if (weapon_id == ����_����)  terrain_buf = 0.05f;
                                break;
                case ����_��  : 
                                if      (weapon_id == ����_â)   terrain_buf = 0.05f;
                                else if (weapon_id == ����_����)  terrain_buf = 0.05f;
                                break;
                case ����_����  : 
                                if      (weapon_id == ����_â)   terrain_buf = -0.05f;
                                else if (weapon_id == ����_��)   terrain_buf = 0.10f;
                                else if (weapon_id == ����_��)   terrain_buf = -0.05f;
                                else if (weapon_id == ����_����)  terrain_buf = -0.10f;
                                break;
                case ����_��õ  : 
                                if      (weapon_id == ����_â)   terrain_buf = -0.10f;
                                else if (weapon_id == ����_��)   terrain_buf = 0.05f;
                                else if (weapon_id == ����_��)   terrain_buf = -0.10f;
                                else if (weapon_id == ����_����)  terrain_buf = -0.15f;
                                break;
                case ����_��   : 
                                if      (weapon_id == ����_â)   terrain_buf = 0.10f;
                                else if (weapon_id == ����_��)   terrain_buf = 0.05f;
                                else if (weapon_id == ����_��)   terrain_buf = 0.15f;
                                else if (weapon_id == ����_����)  terrain_buf = -0.10f;
                                break;
                case ����_Ȳ����:  
                                if      (weapon_id == ����_â)   terrain_buf = -0.05f;
                                else if (weapon_id == ����_����)  terrain_buf = 0.05f;
                                break;
                case ����_���  : 
                                if      (weapon_id == ����_â)   terrain_buf = 0.05f;
                                else if (weapon_id == ����_��)   terrain_buf = 0.05f;
                                else if (weapon_id == ����_��)   terrain_buf = 0.05f;
                                else if (weapon_id == ����_����)  terrain_buf = 0.05f;
                                break;
                case ����_��  : 
                                if      (weapon_id == ����_â)   terrain_buf = 0.15f;
                                else if (weapon_id == ����_��)   terrain_buf = 0.15f;
                                else if (weapon_id == ����_��)   terrain_buf = 0.15f;
                                else if (weapon_id == ����_����)  terrain_buf = 0.10f;
                                break;
            }
            
            // Ư��_�ź� �����δ�� ���� ������� ��/��/���濡�� 15% �߰� ����Ƽ�� ('18.10.14)
            if (unit.has_skill(Ư��_�ź�) and (unit_hex.terrain == ����_�� or unit_hex.terrain == ����_�� or unit_hex.terrain == ����_���� ) )
                terrain_buf += 0.15f;
            // Ư��_�ص� �����δ�� ���� ������� ��õ���� 15% �߰� ����Ƽ�� ('18.10.17)
            else if (unit.has_skill(Ư��_�ص�) and (unit_hex.terrain == ����_��õ) )
                terrain_buf += 0.15f;
            // Ư��_���� �����δ�� ���� ������� ������/��/���濡�� 15% �߰� ����Ƽ�� ('18.10.17)
            else if (unit.has_skill(Ư��_����) and (unit_hex.terrain == ����_������ or unit_hex.terrain == ����_�� or unit_hex.terrain == ����_����) )
                terrain_buf += 0.15f;
            
            return terrain_buf;
        }
        
        
        // �δ밣 ���� ������ ('18.10.14)
        int get_height_diff(const pk::point &in src, const pk::point &in dst)
		{
			return pk::get_height_map(pk::hex_pos_to_height_map_pos(src) + 2).height - pk::get_height_map(pk::hex_pos_to_height_map_pos(dst) + 2).height;
		}
        
        
        // --------------------------------------------------------
        // �δ� �� ���� �� �ֺ� �δ뿡 ���� ������ ���� ��� ('18.10.28)
        float func_neighbor_buf(pk::unit @ unit, bool ������ȭ)
        {
            float neighbor_buf = 0.f;
            int neighbor_range = 1;
            
            pk::point pos = unit.get_pos();
            
            array<pk::point> arr = pk::range(pos, 1, neighbor_range);
            for (int j = 0; j < int(arr.length); j++)
            {
                pk::unit@ search_unit = pk::get_unit(arr[j]);
                if (search_unit !is null and !pk::is_enemy(unit, search_unit))  // �ֺ��δ밡 �Ʊ��� ���
                {
                    // �Ʊ��δ����� �źп� ���� ���� 
                    if (search_unit.leader == pk::get_kunshu_id(unit))  // �Ʊ��δ밡 �����̸� : ������ ���� ������ �� ��ȭ �ٸ��� ('18.10.28)
                    {
                        switch (pk::get_force(unit.get_force_id()).title)
                        {
                        case ����_Ȳ��:
                            neighbor_buf += 0.15f;   // 15% ����
                            
                            if (��ȭǥ�ü��� and ������ȭ and pk::is_player_controlled(unit))
                            {
                                //pk::say(pk::encode("���Ͽ� �Բ� �ϰڽ��ϴ�"), pk::get_person(unit.leader));
                                @msg_unit = @unit;
                                @msg_person = pk::get_person(unit.leader);
                                msg_string = "���Ͽ� �Բ� �ϰڽ��ϴ�";
                            }
                            break;
                            
                        case ����_��:
                            neighbor_buf += 0.10f;   // 10% ����
                            
                            if (��ȭǥ�ü��� and ������ȭ and pk::is_player_controlled(unit))
                            {
                                //pk::say(pk::encode("���Ͽ� �Բ� �ϰڽ��ϴ�"), pk::get_person(unit.leader));
                                @msg_unit = @unit;
                                @msg_person = pk::get_person(unit.leader);
                                msg_string = "���Ͽ� �Բ� �ϰڽ��ϴ�";
                            }
                            break;
                            
                        case ����_��:
                            neighbor_buf += 0.05f;   // 5% ����
                            
                            if (��ȭǥ�ü��� and ������ȭ and pk::is_player_controlled(unit))
                            {
                                //pk::say(pk::encode("���� �Բ� �ϰڼ�"), pk::get_person(unit.leader));
                                @msg_unit = @unit;
                                @msg_person = pk::get_person(unit.leader);
                                msg_string = "���� �Բ� �ϰڽ��ϴ�";
                            }
                            break;
                            
                        default:
                            neighbor_buf += 0.05f;   // 5% ����
                            
                            if (��ȭǥ�ü��� and ������ȭ and pk::is_player_controlled(unit))
                            {
                                //pk::say(pk::encode("�ֱ��� �Բ� �ϰڼ�"), pk::get_person(unit.leader));
                                @msg_unit = @unit;
                                @msg_person = pk::get_person(unit.leader);
                                msg_string = "�ֱ��� �Բ� �ϰڽ��ϴ�";
                            }
                            break;
                        }
                    }
                    else if (search_unit.leader == pk::get_totoku_id(unit))  // �Ʊ��δ밡 ���� ���� �����̸� ('18.10.28)
                    {
                        neighbor_buf += 0.05f;   // 5% ����
                        
                        if (��ȭǥ�ü��� and ������ȭ and pk::is_player_controlled(unit))
                        {
                            //pk::say(pk::encode("������ �Բ� �Ѵ�"), pk::get_person(unit.leader));
                            @msg_unit = @unit;
                            @msg_person = pk::get_person(unit.leader);
                            msg_string = "������ �Բ� �Ѵ�";
                        }
                    }                        
                    
                    
                    // �Ʊ��δ����� Ư�⿡ ���� ����
                    if (search_unit.has_skill(Ư��_�Ż�))  // �Ʊ��δ밡 Ư��_�Ż� ���� �� ���� ('18.10.28)
                    {
                        neighbor_buf += 0.10f;   // 10% ����
                        
                        if (��ȭǥ�ü��� and ������ȭ and pk::is_player_controlled(unit))
                        {
                            //pk::say(pk::encode("�Ż������� �ߵ��϶�"), pk::get_person(search_unit.leader));
                            @msg_unit = @unit;
                            @msg_person = pk::get_person(search_unit.leader);
                            msg_string = "�Ż������� �ߵ��϶�";
                        }
                        
                    }
                    if (search_unit.has_skill(Ư��_���))  // �Ʊ��δ밡 Ư��_��� ���� �� ���� ('18.10.28)
                    {
                        neighbor_buf += 0.05f;   // 5% ����
                        
                        if (��ȭǥ�ü��� and ������ȭ and pk::is_player_controlled(unit))
                        {
                            //pk::say(pk::encode("����ǽ� ������ ���Ķ�"), pk::get_person(search_unit.leader));
                            @msg_unit = @unit;
                            @msg_person = pk::get_person(search_unit.leader);
                            msg_string = "����ǽ� ������ ���Ķ�";
                        }
                    }
                    
                }
            }
                
            return neighbor_buf;
        }
        
        // --------------------------------------------------------
        // ���� ���� ���� ���� ���� ('18.11.5)
        bool func_tactics_city(pk::unit@ attacker, int weapon_id)
        {
            int kunshu_id = pk::get_kunshu_id(attacker);
            switch (weapon_id)
            {
                case ����_â:
                    if (kunshu_id == pk::get_kunshu_id(pk::get_building(����_����)))
                        return true;
                    else if (kunshu_id == pk::get_kunshu_id(pk::get_building(����_��)))
                        return true;
                    break;
                    
                case ����_��:
                    if (kunshu_id == pk::get_kunshu_id(pk::get_building(����_�)))
                        return true;
                    else if (kunshu_id == pk::get_kunshu_id(pk::get_building(����_���)))
                        return true;
                    break;
                    
                case ����_��:
                    if (kunshu_id == pk::get_kunshu_id(pk::get_building(����_����)))
                        return true;
                    else if (kunshu_id == pk::get_kunshu_id(pk::get_building(����_ȸ��)))
                        return true;
                    break;
                    
                case ����_����:
                    if (kunshu_id == pk::get_kunshu_id(pk::get_building(����_����)))
                        return true;
                    else if (kunshu_id == pk::get_kunshu_id(pk::get_building(����_����)))
                        return true;
                    break;
            }
            return false;
        }
        
        
        // --------------------------------------------------------
        // �δ� �� ���� �� �ǰݺδ� ���⿡ ���� ����� ���� ('18.11.27)
        int func_unit_direction(pk::unit@ attacker, pk::unit@ target_unit)
        {
            int dir_unit = target_unit.direction;    // �ǰݺδ��� �������
            int dir_atk = pk::get_direction(target_unit.pos, attacker.pos);  // ������ �ǰݹ���
            
            int damage_dir = -1;
            
            switch (dir_unit)
            {
                case ����_�ϼ�:  
                    if      (dir_atk == ����_�ϼ�)                      damage_dir = 0;   // ����
                    else if (dir_atk == ����_�� or dir_atk == ����_����)  damage_dir = 1;   // ����
                    else if (dir_atk == ����_�ϵ� or dir_atk == ����_��)  damage_dir = 2;   // ����
                    else if (dir_atk == ����_����)                      damage_dir = 3;   // �ĸ�
                    break;
                    
                case ����_�� :  
                    if      (dir_atk == ����_��)                        damage_dir = 0;   // ����
                    else if (dir_atk == ����_�ϼ� or dir_atk == ����_�ϵ�) damage_dir = 1;   // ���� 
                    else if (dir_atk == ����_���� or dir_atk == ����_����) damage_dir = 2;   // ���� 
                    else if (dir_atk == ����_��)                        damage_dir = 3;   // �ĸ�
                    break;
                    
                case ����_�ϵ�: 
                    if      (dir_atk == ����_�ϵ�)                      damage_dir = 0;   // ����
                    else if (dir_atk == ����_�� or dir_atk == ����_����)  damage_dir = 1;   // ����
                    else if (dir_atk == ����_�ϼ� or dir_atk == ����_��)  damage_dir = 2;   // ����
                    else if (dir_atk == ����_����)                      damage_dir = 3;   // �ĸ�
                    break;
                    
                case ����_����:  
                    if      (dir_atk == ����_����)                      damage_dir = 0;   // ����   
                    else if (dir_atk == ����_�ϼ� or dir_atk == ����_��)  damage_dir = 1;   // ����
                    else if (dir_atk == ����_�� or dir_atk == ����_����)  damage_dir = 2;   // ����
                    else if (dir_atk == ����_�ϵ�)                      damage_dir = 3;   // �ĸ�
                    break;
                    
                case ����_�� :
                    if      (dir_atk == ����_��)                        damage_dir = 0;   // ����
                    else if (dir_atk == ����_���� or dir_atk == ����_����) damage_dir = 1;   // ����
                    else if (dir_atk == ����_�ϼ� or dir_atk == ����_�ϵ�) damage_dir = 2;   // ����
                    else if (dir_atk == ����_��)                        damage_dir = 3;   // �ĸ�
                    break;
                    
                case ����_����:  
                    if      (dir_atk == ����_����)                      damage_dir = 0;   // ����
                    else if (dir_atk == ����_�� or dir_atk == ����_�ϵ�)  damage_dir = 1;   // ����
                    else if (dir_atk == ����_���� or dir_atk == ����_��)  damage_dir = 2;   // ����
                    else if (dir_atk == ����_�ϼ�)                      damage_dir = 3;   // �ĸ�
                    break;
                    
            }
            
            return damage_dir;
            
        }
        
        // ����ġ ��ȯ�Լ��� �����ȯ �Լ��� �и� ('19.2.26)
        float func_dir_weight(int damage_dir)
        {
            float ���Ⱑ��ġ_���� = 0.95f;
            float ���Ⱑ��ġ_���� = 1.00f;
            float ���Ⱑ��ġ_���� = 1.05f;
            float ���Ⱑ��ġ_�ĸ� = 1.10f;
            
            float damage_buf = 1.f;
            
            switch (damage_dir)
            {
                case 0: damage_buf = ���Ⱑ��ġ_����; break;  // ���� ����� ����ġ
                case 1: damage_buf = ���Ⱑ��ġ_����; break;  // ���� ����� ����ġ
                case 2: damage_buf = ���Ⱑ��ġ_����; break;  // ���� ����� ����ġ
                case 3: damage_buf = ���Ⱑ��ġ_�ĸ�; break;  // �ĸ� ����� ����ġ
            }
            
            return damage_buf;
        }
        
        //------------------------------------------------------------------------------------------
        // ���� �ߵ� �� ��Ÿ�/���� ��ȿ �������� Ȯ�� ('19.11.10)
        bool func_tactics_valid_target(pk::unit@ attacker, pk::unit@ target_unit, int tactics_id)
        {
            int combat_range = pk::get_distance(attacker.pos, target_unit.pos);
            int terrain_id = pk::get_hex(target_unit.pos).terrain;
            
            pk::tactics@ tactics_t = pk::get_tactics(tactics_id);
            int  max_range = tactics_t.max_range;
            int  min_range = tactics_t.min_range;
            if (max_range == 1 and combat_range > max_range) return false;
            /*
            bool terrain_valid;
            if (terrain_id == ����_�� and attacker.has_skill(Ư��_���) 
                and ((����_ȭ�� <= tactics_id and tactics_id <= ����_����) or tactics_id == ����_����ȭ�� or tactics_id == ����_�Լ�ȭ��))
                terrain_valid = true;
            else
                terrain_valid = tactics_t.terrain[terrain_id];
            if (!terrain_valid) return false;
            */
            return true;
        }
        
        //------------------------------------------------------------------------------------------
        // AI�δ� ���� ���� �Լ� ('19.11.21)
        int func_dir_tactics_opt(pk::unit@ attacker, pk::unit@ target_unit, int tactics_id)
        {
            int tactics_opt = tactics_id;   // �⺻���� �Է°�
            if (!pk::is_alive(target_unit)) return tactics_id;
            if (attacker.weapon > ����_���� or attacker.weapon == ����_��) return tactics_id;
            if (pk::get_current_turn_force_id() != attacker.get_force_id()) return tactics_id;
            
            int atk_dist = pk::get_distance(attacker.pos, target_unit.pos); // �����Ÿ�
            int atk_dir = pk::get_direction(attacker.pos, target_unit.pos); // ���ݹ���
            int def_dir = pk::get_direction(target_unit.pos, attacker.pos); // �ǰݹ���
            
            pk::point pos_b1 = pk::get_neighbor_pos(attacker.pos, def_dir, 1);
            pk::point pos_n1 = pk::get_neighbor_pos(target_unit.pos, atk_dir, 1);
            pk::point pos_n2 = pk::get_neighbor_pos(target_unit.pos, atk_dir, 2);
            
            pk::unit@ unit_n1 = (pk::is_valid_pos(pos_n1))? pk::get_unit(pos_n1) : null;
            pk::unit@ unit_n2 = (pk::is_valid_pos(pos_n2))? pk::get_unit(pos_n2) : null;
            bool enemy_n1 = (pk::is_alive(unit_n1))? pk::is_enemy(attacker, unit_n1) : false;
            bool enemy_n2 = (pk::is_alive(unit_n2))? pk::is_enemy(attacker, unit_n2) : false;
            
            pk::hex@ hex_n1 = (pk::is_valid_pos(pos_n1))? pk::get_hex(pos_n1) : null;
            pk::hex@ hex_n2 = (pk::is_valid_pos(pos_n2))? pk::get_hex(pos_n2) : null;
            bool empty_n1 = (hex_n1 !is null)? (!hex_n1.has_unit and !hex_n1.has_building) : false;
            bool empty_n2 = (hex_n2 !is null)? (!hex_n2.has_unit and !hex_n2.has_building) : false;
            
            bool fire_n0 = pk::is_on_fire(target_unit.pos);
            bool fire_n1 = (pk::is_valid_pos(pos_n1))? pk::is_on_fire(pos_n1) : false;
            bool fire_n2 = (pk::is_valid_pos(pos_n2))? pk::is_on_fire(pos_n2) : false;
            bool fire_b1 = (pk::is_valid_pos(pos_b1))? pk::is_on_fire(pos_b1) : false;
            
            if (pk::is_valid_tactics_id(tactics_id) and (atk_dist == 1))    // ��������, ���/�������� ����
            {
                //----- â�� ���� (����÷, �̴�÷, ����)
                // ����_����÷ ���� Ȯ�� (������밡��, �������, ����, ���δ밡 ������)
                if (check_tactics_enable(attacker, target_unit, ����_����÷) and target_unit.status == �δ����_���)
                    tactics_opt = ����_����÷;
                
                // ����_�̴�÷ ���� Ȯ�� (������밡��, �������, ����, �浹���δ� ��ȿ)
                else if (check_tactics_enable(attacker, target_unit, ����_�̴�÷) and empty_n1 and (enemy_n2 or fire_n2))
                    tactics_opt = ����_�̴�÷;
                
                // ����_���� ���� Ȯ�� (������밡��, �������, ����, �浹���δ� ��ȿ)
                else if (check_tactics_enable(attacker, target_unit, ����_����) and (empty_n1 or enemy_n1 or fire_n1))
                    tactics_opt = ����_����;
                
                //----- �⺴ ���� (����, ����, ����)
                // ����_���� ���� Ȯ�� (������밡��, �������, ����, ������ ��ġ ��ĭ)
                else if (check_tactics_enable(attacker, target_unit, ����_����) and empty_n1 and !enemy_n2 and !fire_n1)
                    tactics_opt = ����_����;
                
                // ����_���� ���� Ȯ�� (������밡��, �������, ����, ������ ��ġ ��ĭ)
                else if (check_tactics_enable(attacker, target_unit, ����_����) and empty_n1 and !fire_n1 and (empty_n2 or fire_n2))
                    tactics_opt = ����_����;
                
                // ����_���� ���� Ȯ�� (������밡��, �������, ����)
                else if (check_tactics_enable(attacker, target_unit, ����_����) and !fire_n0)
                    tactics_opt = ����_����;
                
                //----- �غ� ���� (Ⱦġ, ��ǳ, ����)
                // ����_Ⱦġ ���� Ȯ�� (������밡��, �������, ����, ������ ���δ� Ȯ��)
                else if (check_tactics_enable(attacker, target_unit, ����_Ⱦġ) and (count_neighbor_enemies(attacker, target_unit, ����_Ⱦġ) >= 1))
                    tactics_opt = ����_Ⱦġ;

                // ����_��ǳ ���� Ȯ�� (������밡��, �������, ����, ������ ���δ� Ȯ��)
                else if (check_tactics_enable(attacker, target_unit, ����_��ǳ) and (count_neighbor_enemies(attacker, target_unit, ����_��ǳ) >= 3))
                    tactics_opt = ����_��ǳ;
                
                // ����_���� ���� Ȯ�� (������밡��, �������, ����)
                else if (check_tactics_enable(attacker, target_unit, ����_����) and !fire_b1)
                    tactics_opt = ����_����;
                
            }
            
            // �α�â�� ǥ��
            if (����׸�� and (tactics_id != tactics_opt))
            {
                string leader_name = pk::decode(pk::get_name(pk::get_person(attacker.leader)));
                pk::info(pk::format("{}�δ�����: {} �� {}", leader_name, get_tactics_name(tactics_id), get_tactics_name(tactics_opt)));
            }
            
            return tactics_opt;
        }
        
        // �뺴 ���Ȱ���� �� ȭ�� ����ȭ
        int func_fire_on_arrow(pk::unit@ attacker, pk::hex_object@ target_obj, int tactics_id)
        {
            int tactics_opt = tactics_id;   // �⺻���� �Է°�
            if (!pk::is_alive(target_obj)) return tactics_id;
            if (attacker.weapon != ����_��) return tactics_id;
            if (pk::get_current_turn_force_id() != attacker.get_force_id()) return tactics_id;
            int atk_dist = pk::get_distance(attacker.pos, target_obj.pos); // �����Ÿ�
            
            if (atk_dist > 1 and !pk::is_valid_tactics_id(tactics_id))
            {
                int tekisei = pk::get_tekisei(attacker, attacker.weapon);
                pk::equipment@ atk_eqp  = pk::get_equipment(attacker.weapon);
                pk::tactics@ fire_arrow = pk::get_tactics(����_ȭ��);
                pk::hex@ hex_dst = pk::get_hex(target_obj.pos);
                
                // ȭ��������밡�ɿ��� : ����, ���, ����, ���� üũ
                bool chk_eqp = atk_eqp.tactics[����_ȭ��];
                bool chk_tekisei = tekisei >= fire_arrow.tekisei;
                bool chk_energy = (attacker.energy >= fire_arrow.energy_cost);
                bool chk_range = (fire_arrow.min_range <= atk_dist and atk_dist <= fire_arrow.max_range);
                bool chk_terrain = fire_arrow.terrain[hex_dst.terrain];
                if (chk_eqp and chk_tekisei and chk_energy and chk_range and chk_terrain)
                    tactics_opt = ����_ȭ��;
            }            
            return tactics_opt;
        }
        
        
        bool check_tactics_enable(pk::unit@ src, pk::unit@ dst, int tactics_id)
        {
            bool tactics_en = false;
            int tekisei = pk::get_tekisei(src, src.weapon);
            pk::equipment@ atk_eqp  = pk::get_equipment(src.weapon);
            pk::tactics@ tactics = pk::get_tactics(tactics_id);
            pk::hex@ hex_dst = pk::get_hex(dst.pos);
            
            // ������밡�ɿ��� : ����, ���, ����, ���� üũ
            tactics_en = (atk_eqp.tactics[tactics_id] and (src.energy >= tactics.energy_cost) and (tekisei >= tactics.tekisei) and tactics.terrain[hex_dst.terrain]);
                
            return tactics_en;
        }
        
        int count_neighbor_enemies(pk::unit@ src, pk::unit@ dst, int tactics_id)
        {
            int count = 0;
            for (int i = 0; i < ����_��; i++)
            {
                pk::point pos_t = pk::get_neighbor_pos(src.pos, i);
                pk::unit@ unit_t = (pk::is_valid_pos(pos_t))? pk::get_unit(pos_t) : null;
                if (pk::is_valid_pos(pos_t) and pk::is_alive(unit_t) and pk::is_enemy(src, unit_t) and unit_t.get_id() != dst.get_id())
                {
                    if (tactics_id == ����_Ⱦġ and pk::get_distance(dst.pos, unit_t.pos) == 1)
                        count++;
                    else if (tactics_id == ����_��ǳ)
                        count++;
                }
            }
            return count;
        }

        bool check_splash_valid(pk::unit@ src, pk::unit@ dst)
        {
            int count_force = 0;
            int count_enemy = 0;
            for (int i = 0; i < ����_��; i++)
            {
                pk::point pos_t = pk::get_neighbor_pos(dst.pos, i);
                pk::unit@ unit_t = (pk::is_valid_pos(pos_t))? pk::get_unit(pos_t) : null;
                pk::hex@ hex_t = pk::get_hex(pos_t);
                if (pk::is_valid_pos(pos_t) and pk::is_alive(unit_t) and unit_t.get_id() != dst.get_id())
                {
                    if (!pk::is_enemy(src, unit_t)) count_force++;
                    if ( pk::is_enemy(src, unit_t)) 
                    {
                        if (hex_t.terrain != ����_��) count_enemy++;
                        if (hex_t.terrain == ����_�� and src.has_skill(Ư��_���)) count_enemy++;
                    }
                }
            }
            if (count_enemy >= pk::max(2, (count_force + 1))) return true;
            return false;
        }
        
        string get_tactics_name(int tactics_id)
        {
            pk::array<string> str_tactics = {"����", "����÷", "�̴�÷", "����", "Ⱦġ", "��ǳ", "ȭ��", "����", "����", "����", "����", "����", "����ȭ��", "�����ļ�", "�������", "��������", "�Լ�ȭ��", "�Լ��ݵ�", "�Լ�����"};
            if (tactics_id < 0 or tactics_id >= ����_��) return "���";
            return str_tactics[tactics_id];
        }
        
        //------------------------------------------------------------------------------------------
        // �δ� ����ġ ȹ�� �� �߰�ó�� 
        //------------------------------------------------------------------------------------------
        
        // ���� �޽��� ó���� ����
        pk::unit@   msg_unit;
        pk::person@ msg_person;
        string      msg_string = "";
        
        // ����÷ ó���� ����
        pk::unit@ unit;
        pk::unit@ nasun_unit;
        bool ����÷_ũ��Ƽ��;  // ����÷ ���� �� ũ��Ƽ�� ����
        bool ����÷_�ǰ��ൿ;  // ����÷ �ǰݺδ��� �ൿ�Ϸ� ����
        int  ����÷_�ǰݻ���;  // ����÷ �ǰݺδ��� �δ���� ����
        int  ����÷_�ǰ�Ÿ�̸�;  // ����÷ �ǰݺδ��� �δ���� Ÿ�̸�
        
        // �Ĺ��ǰ� ȥ��ó���� ����
        pk::unit@ back_unit;
        
        
        // ����ġ ȹ�� �� ó�� �Լ�
        void onUnitExpAdd(pk::unit@ unit, int type)
        {
            // Ŀ���� ��ȭǥ��
            if (��ȭǥ�ü��� and pk::is_alive(unit) and pk::is_alive(msg_unit) and unit.get_id() == msg_unit.get_id())
            {
                pk::say(pk::encode(msg_string), msg_person);
            }
            @msg_unit = null;
            @msg_person = null;
            msg_string = "";
            
            // ����÷ȥ��Ȯ��_��������
            if (����÷ȥ��Ȯ��_�������� and pk::is_alive(unit) and pk::is_alive(nasun_unit))
            {
                pk::person@ def_leader = pk::get_person(nasun_unit.leader);
                int ����÷ȥ��Ȯ�� = (����÷_ũ��Ƽ��)? ����÷_ũ��Ƽ��ȥ��Ȯ�� : ����÷_��������ȥ��Ȯ��;
                int ����÷ȥ���ð� = (����÷_ũ��Ƽ��)? 2 : 1;
                
                if (pk::rand_bool(����÷ȥ��Ȯ��))
                {
                    pk::set_status(nasun_unit, unit, �δ����_ȥ��, ����÷ȥ���ð�, true);
                }
                else
                {
                    pk::set_status(nasun_unit, unit, ����÷_�ǰݻ���, ����÷_�ǰ�Ÿ�̸�, false);  // ȥ�����¸� ������ �ǰ� ��� �δ���·� ����
                    nasun_unit.action_done = ����÷_�ǰ��ൿ;                       // �ǰ� ��� �ൿ���·� �缳��
                    
                    if (����÷_�ǰݻ��� == �δ����_���)
                        pk::say(pk::encode("������ �δ�ȥ���� ���߱�"), def_leader);
                }
            }
            @nasun_unit = null;
            ����÷_ũ��Ƽ�� = false;
            
            // �Ĺ��ǰ� ȥ��ó��
            if (�������⼳�� and �Ĺ��ǰݽ�_ȥ������ and pk::is_alive(unit) and pk::is_alive(back_unit))
            {
                if (pk::rand_bool(�Ĺ��ǰݽ�_ȥ��Ȯ��) and back_unit.status == �δ����_���)
                {
                    pk::set_status(back_unit, unit, �δ����_ȥ��, 1, true);
                    pk::say(pk::encode("��. �Ĺ� ������ �����߱�.."), pk::get_person(unit.leader));
                }
            }
            @back_unit = null;
            
        }
        //------------------------------------------------------------------------------------------
        
        bool ����׸�� = false;
        
	}

	Main main;
}


