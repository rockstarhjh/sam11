/*
@ ������: �⸶å��
@ Update: '18.10.21  / ���泻��: ������ַ¼��ĺ���, �̵���_���¼���, �̵���_��������, �̵���_��ּ���, �̵���_��¼���, �̵���_��������, ����ȿ������ ��� �ݿ�
@ Update: '18.11.6   / ���泻��: �����ɼ� �߰� (��ɺ��� ����)
@ Update: '18.12.1   / ���泻��: ���ۺδ� �̵��� ���� (����ȿ�� ����, ����ȿ�� ����)
@ Update: '18.12.27  / ���泻��: �̵���_���伳�� ��� �߰�
@ Update: '20.8.29   / ���泻��: ����/���/����/��ġ/�ŷ� ���Ŀ� overflow ���� �߰�, �δ� ����/���� ����� ���ÿɼ� �߰�, �̵���_�ִ����� �߰�
*/

namespace �δ�_�ɷ�ġ
{
    
    //---------------------------------------------------------------------------------------
    // ���� ���� (true = on, false = off)
    const bool ������ַ�_���ĺ��� = true;   // true: ����ɷ� �����ϴ� �ű� ���� ����, false: ���� ��� ����
    
    const bool  ���ݷ�_���ĺ��� = true;   // true: ���ݷ� (����+��� �����ջ�), false: ���� ��� ���� (���ݷ� = ���¸� �ݿ�)
    const float ���ݷ�_��ֺ��� = 0.20f;  // ���ݷ¿� �ջ��� ��ַ� ���� (0.0f~1.0f)
    
    const bool  ����_���ĺ��� = true;   // true: ���� (���+���� �����ջ�), false: ���� ��� ���� (���� = ��ָ� �ݿ�)
    const float ����_���º��� = 0.20f;  // ���¿� �ջ��� ��ַ� ���� (0.0f~1.0f)
    
    const bool �̵���_���¼��� = true;   // ���¼��� ���� �̵��� ����
    const bool �̵���_�������� = true;   // ������ ���� �̵��� ����
    const bool �̵���_��ּ��� = true;   // ��ַ¿� ���� �̵��� ����
    const bool �̵���_��¼��� = true;   // ��¿� ���� �̵��� ����
    const bool �̵���_�������� = true;   // ������ ���� �̵��� ����
    const bool �̵���_���伳�� = true;   // �ڱ�/Ÿ�� ���ο� ���� �̵��� ����
    
    const bool �̵���_�ִ����� = true;   // true: �̵��� max=40, false: �̵��� max ���Ѿ���
    
    const bool ����ȿ������ = true;   // ���º� ���� ȿ�� ����
    
    //---------------------------------------------------------------------------------------
    
	class Main
	{
		Main()
		{
			pk::set_func(163, pk::func163_t(callback));
		}

		void callback(pk::unit_attr& attr, const pk::detail::arrayptr<pk::person@> &in member, int weapon_id, uint troops, int type, int status, bool navy, bool shoubyou)
		{
			pk::person@ leader = member[0];
            

			if (!pk::is_alive(leader))
				return;

			pk::force@ force = pk::get_force(leader.get_force_id());
            
            // ������ �Ҽӵ� �δ� �Ǵ� �ǹ� ��ȯ ('18.10.10)
            int unit_energy = 0;
            pk::building@ building = pk::hex_object_to_building(pk::get_hex_object(leader.location));
            pk::unit@ unit;
            if (!pk::is_alive(building))    // ������ �ǹ��� �ҼӵǾ� ���� ������ �δ� ��°� ���
            {
                @unit = pk::get_unit(pk::get_unit_id(leader));
                unit_energy = unit.energy;
            }
            else                            // ������ �ǹ� �ҼӵǾ� ���� �δ� �� ���̸� ���� ��°� ���
            {
                unit_energy = pk::get_energy(building);
            }
            
            

			if (!pk::is_alive(force))
				return;
			if (!pk::is_valid_equipment_id(weapon_id) or !pk::is_valid_unit_type(type) or !pk::is_valid_unit_status(status))
				return;

			
            
			// ������ ���ٸ�	
            if ((member[1] is null) and (member[2] is null))
			{
				for (int i = 0; i < ����ɷ�_��; i++)	// ���� �ɷ�ġ �״�� ���
					attr.stat[i] =  pk::min(255, (shoubyou ? leader.stat[i] : leader.max_stat[i]));
			}
            // ������ �ִٸ�
			else
			{
				// ���� ���谡 �ִٸ� �������� ����
				if (func_4960d0(leader, member[1]) or func_4960d0(leader, member[2]) or func_4960d0(member[1], member[2]))
				{
					for (int i = 0; i < ����ɷ�_��; i++)
						attr.stat[i] =  pk::min(255, (shoubyou ? leader.stat[i] : leader.max_stat[i]));
				}
				// ���� ���谡 ���ٸ� ����
				else
				{
					for (int i = 0; i < ����ɷ�_��; i++)
					{
						int a = 0, b = 0;
						int leader_stat =  pk::min(255, (shoubyou ? leader.stat[i] : leader.max_stat[i]));

						// ���, ������ ���� ���迡 ���� ����
						if (i <= ����ɷ�_����)
						{
                            if (������ַ�_���ĺ���)
                            {
                                // �ű� ���� ���� : ���� + ����1���� + ����2����   ('18.10.9)
                                if (member[1] !is null)     // �ű� �Լ� : ����1 ������
                                    a = func_sub_stat(leader, leader_stat, member[1], (shoubyou ? member[1].stat[i] : member[1].max_stat[i]) ); 
                                if (member[2] !is null)     // �ű� �Լ� : ����2 ������
                                    b = func_sub_stat(leader, leader_stat, member[2], (shoubyou ? member[2].stat[i] : member[2].max_stat[i]) );
                                
                                attr.stat[i] = pk::min(255, (leader_stat + a + b));   // 255 ���Ϸ� �ջ�
                            }
                            else
                            {
                                // ���� ���� ��� : MAX[(����&����1),(����&����2)]
                                if (member[1] !is null)
                                    a = func_495ff0(leader, leader_stat, member[1], shoubyou ? member[1].stat[i] : member[1].max_stat[i]);
                                if (member[2] !is null)
                                    b = func_495ff0(leader, leader_stat, member[2], shoubyou ? member[2].stat[i] : member[2].max_stat[i]);
                                attr.stat[i] = pk::min(255, pk::max(a, b));   // �ִ밪
                            }
                            
						}
						// ����, ��ġ, �ŷ��� �ִ밪
						else
						{
							if (member[1] !is null)
								a = pk::max(leader_stat, shoubyou ? member[1].stat[i] : member[1].max_stat[i]);
							if (member[2] !is null)
								b = pk::max(leader_stat, shoubyou ? member[2].stat[i] : member[2].max_stat[i]);
                            
                            attr.stat[i] = pk::min(255, pk::max(a, b));   // �ִ밪
						}

					}
				}
			}

            
			// ������ �ִ밪
			for (int i = 0; i < ����_��; i++)
			{
				int n = 0;
				for (int j = 0; j < member.length; j++)
				{
					if (member[j] !is null)
						n = pk::max(n, member[j].tekisei[i]);
				}
				attr.tekisei[i] = n;
			}

			pk::equipment@ equipment = pk::get_equipment(weapon_id);

			float apt = float(pk::core["����"][attr.tekisei[pk::equipment_id_to_heishu(weapon_id)]]["�δ�ɷ�ġ"]); // (attr.tekisei[pk::equipment_id_to_heishu(weapon_id)] + 7) * 0.1;
			float sts = 1.f;
			float str = 1.f;
			float ldr = 1.f;
			int atk = equipment.stat[����ɷ�_����];
			int def = equipment.stat[����ɷ�_���];
			int mov = equipment.stat[����ɷ�_�̵�];
            
			
			int defskill_�ұ� = Ư��_�ұ�;	
			int defskill_�ݰ� = Ư��_�ݰ�;	
			int defskill_ö�� = Ư��_ö��;

			if (weapon_id == ����_�� or (weapon_id == ����_�ְ� and type == �δ�����_����))	
				apt = 0.6f;

			if (status == �δ����_ȥ��)
				sts = 0.8f;

			if (type == �δ�����_����)
			{
				str = 0.4f;
				ldr = 1.f / 3.f;
			}

			if (weapon_id <= ����_����)
			{
				int tech_id = -1;	
				
				if (weapon_id == ����_â)
				{
					tech_id = �ⱳ_����â��;
				}
				if (weapon_id == ����_��)
				{
					tech_id = �ⱳ_�����غ�;
				}
				if (weapon_id == ����_��)
				{
					tech_id = �ⱳ_�����뺴;
				}
				if (weapon_id == ����_����)
				{
					tech_id = �ⱳ_�����⺴;
				}

				if (pk::has_tech(force, tech_id))
				{
					atk = atk + 10;
					def = def + 10;
				}
				
			}
            
            // ------------------------------- //
            // ����/���� �߰� ȿ�� ���� �� �ۼ��� ��ġ //
            // ------------------------------- //
            
            
            /* ���� ���� ����
            // ��� Ư������ ���� ���� : �������� ��ø ����
            if (pk::has_skill(member, defskill_�ұ�))
                def = def + 10;
            if (pk::has_skill(member, defskill_�ݰ�))
                def = def + 10;
            if (pk::has_skill(member, defskill_ö��))
                def = def + 15;
            */
            
            
			/* 
				[����] �δ� �ɷ��� �����ϴ� ��ҵ� < ����(����), ���(���), �Ǽ�(��ġ) > 
				attr.stat[�δ�ɷ�_����] = pk::min(255.f, pk::max(1.f, (attr.stat[�δ�ɷ�_����] * atk * apt * 0.01f) * str * sts));
				attr.stat[�δ�ɷ�_���] = pk::min(255.f, pk::max(1.f, (attr.stat[�δ�ɷ�_���] * def * apt * 0.01f) * ldr * sts));
				attr.stat[�δ�ɷ�_�Ǽ�] = pk::min(255.f, pk::max(1.f, (attr.stat[�δ�ɷ�_��ġ] * 2.f / 3 + 50) * ldr * sts));
			*/
            float atk_stat_ratio = 0.0f;
            float def_stat_ratio = 0.0f;
            
			if  (���ݷ�_���ĺ���)
                atk_stat_ratio = pk::min(1.0f, pk::max(0.0f, ���ݷ�_��ֺ���));
            else
                atk_stat_ratio = 0.0f;
            
            if  (����_���ĺ���)
                def_stat_ratio = pk::min(1.0f, pk::max(0.0f, ����_���º���));
            else
                def_stat_ratio = 0.0f;
                        
            
			// �δ� ���ݷ� = (��)����, (��)����� �Բ� ���� (�ջ�)
			attr.stat[�δ�ɷ�_����] = int(pk::min(255.f, pk::max(1.f, (((1.f-atk_stat_ratio)*attr.stat[�δ�ɷ�_����]+atk_stat_ratio*attr.stat[�δ�ɷ�_���])/ 1.0f * atk * apt * 0.01f ) * str * sts)));
			// �δ� ���� = (��)���, (��)������ �Բ� ���� (�ջ�)
			attr.stat[�δ�ɷ�_���] = int(pk::min(255.f, pk::max(1.f, (((1.f-def_stat_ratio)*attr.stat[�δ�ɷ�_���]+def_stat_ratio*attr.stat[�δ�ɷ�_����])/ 1.0f * def * apt * 0.01f ) * ldr * sts)));
            
			// �δ� ���� = ����
			attr.stat[�δ�ɷ�_����] = int(pk::min(255.f,(attr.stat[�δ�ɷ�_����] ) / 1.f));
			// �δ� �Ǽ� (������ ����)
			attr.stat[�δ�ɷ�_�Ǽ�] = int(pk::min(255.f, pk::max(1.f, (attr.stat[�δ�ɷ�_��ġ] * 2.f / 3.f + 50) * ldr * sts)));
			
            
            //--------------------------------------------------------------------------------
            // �δ� ���ǿ� ���� �̵��� ���� ȿ��
            
            // �δ뺰 ���, ��ַ�, ����, ���¼� ȿ�� �̵��� ���� ���� �߰� ('18.10.7)
            float mov_var = mov;  
            
            // ���¼��� ���� �̵��� ���� : �⺻ �̵��� +1, 3000�� ���� �ø��� �̵��� ���� ('18.10.9)
            if (�̵���_���¼���)
            {
                if (type == �δ�����_����)
                    mov_var = mov_var + 1 - pk::min(5,(troops / 6000));    // ���ۺδ� �̵��� ���� ������ ('18.11.24)
                else
                    mov_var = mov_var + 1 - pk::min(10,(troops / 3000));    // �����δ� �̵��� ���� ������
            }
            
            // ���� ������ ���� �̵��� ���� S��=+10%, C��=-20%('18.10.8)
            if (�̵���_��������)
            {
                if (type == �δ�����_����)    // �����δ뿡 ���Ͽ� ���� ��� �߰� ('18.11.26)
                    mov_var = mov_var * (1.f + 0.1f * pk::min(2, (attr.tekisei[pk::equipment_id_to_heishu(weapon_id)] - ����_A))); 
            }
            
            // �δ뺰 ��ַ¿� ���� �̵��� ���� 85% ~ 105% ���� : ��ַ� 75�� �� ��0% ('18.10.7)
            if (�̵���_��ּ���)
                mov_var = mov_var * (0.85f + 0.20f * (attr.stat[�δ�ɷ�_���] / 100.f));
            
            // �δ뺰 ��¿� ���� �̵��� 80% ~ 110% ���� : ��� 80�� �� 100% ('18.10.10)
            if (�̵���_��¼���)
                mov_var = mov_var * (0.80f + 0.30f * (unit_energy / 120.f));
            
            // ������ ���� �̵��� ���� ȿ�� ('18.10.9)
            if (�̵���_��������)
            {
                switch(pk::get_season())            // pk::get_season()= 0:��, 1:����, 2:����, 3:�ܿ�
                {
                    case ����_����: mov_var -= 2; break;    // ������ �̵��� -2
                    case ����_�ܿ�: mov_var -= 4; break;    // ������ �̵��� -4
                }
            }
            
            // �δ��� ��ǥ ���信 ���� �̵��� ȿ�� : �Ʊ����信�� �̵��� ���, �������信�� �̵��� ���� ('18.12.27)
            if (�̵���_���伳�� and pk::is_alive(unit))
            {
                pk::building@ area_building = pk::get_building(pk::get_building_id(unit.pos));
                if (pk::is_alive(area_building))
                {
                    if (unit.get_force_id() == area_building.get_force_id())
                        mov_var = mov_var * 1.1f;   // �Ʊ����信�� �̵��� 10%���� 
                    else if (pk::is_enemy(unit, area_building))
                        mov_var = mov_var * 0.9f;   // �������信�� �̵��� 10% ���� 
                }
            }
            
            // �δ뺰 ���� ���� �̵���
            mov = int(mov_var);
            
            //--------------------------------------------------------------------------------
            // ���� ��ũ��Ʈ ���� : �ⱳ �� ����/����� Ư¡ �ݿ�
            
			if (type == �δ�����_����)
			{
				switch (weapon_id)
				{
				case ����_â:
                    if (pk::has_tech(force, �ⱳ_����â��))
						mov = mov + 6;
					break;
                    
				case ����_��:
                    if (pk::has_tech(force, �ⱳ_�����غ�))
						mov = mov + 6;
					break;
                    
				case ����_��:
                    if (pk::has_tech(force, �ⱳ_�����뺴))
						mov = mov + 6;
					break;
                    
				case ����_����:
                    if (pk::has_tech(force, �ⱳ_�縶����))
						mov = mov + 2;
                    if (pk::has_tech(force, �ⱳ_�����⺴))   // �����⺴ �̵��� ���� ('18.10.5)
						mov = mov + 4;
					break;
                    
				case ����_����:
                    if (pk::has_tech(force, �ⱳ_���భȭ))   // ���భȭ �̵��� ���� ('18.10.5)
						mov = mov + 4;
					break;
                    
				case ����_����:
                    if (pk::has_tech(force, �ⱳ_���భȭ))    // ���భȭ �̵��� ���� ('18.10.5)
						mov = mov + 4;
					break;
                    
				case ����_����:
                    if (pk::has_tech(force, �ⱳ_���భȭ))    // ���భȭ �̵��� ���� ('18.10.5)
						mov = mov + 4;
					break;
                    
				case ����_���:
					if (pk::has_tech(force, �ⱳ_���భȭ))
						mov = mov + 4;
					break;
				}

                
				if (weapon_id <= ����_��)
				{
					mov = mov + int(pk::core::skill_constant(member, Ư��_����)); // 5
				}
				else if (weapon_id == ����_����)
				{
					if (pk::has_skill(member, Ư��_����))
						mov = mov + int(pk::core::skill_constant(member, Ư��_����)); // 5
					else if (pk::has_skill(member, Ư��_�౺))
						mov = mov + int(pk::core::skill_constant(member, Ư��_�౺)); // 3
                    
                    // ���º� ���� �̵��� ���� ('18.10.1) - �⺴ ���� �縶���� ȿ�� +2
                    if (����ȿ������ and pk::has_tech(force, �ⱳ_�縶����))
                    {
                        if (pk::get_kunshu_id(force) == ����_������)
                            mov = mov + 2;
                        else if (pk::get_kunshu_id(force) == ����_����)
                            mov = mov + 2;
                        else if (pk::get_kunshu_id(force) == pk::get_kunshu_id(pk::get_person(����_����)))
                            mov = mov + 2;
                        else if (pk::get_kunshu_id(force) == ����_��Ź)
                            mov = mov + 2;
                        else if (pk::get_kunshu_id(force) == ����_����)
                            mov = mov + 2;
                    }
				}
                else if (weapon_id <= ����_���)
                {
                    // ���º� ���� �̵��� ���� ('18.10.1) - ���� �Ǵ� ������ ������ ���� ���భȭ ȿ�� +4
                    if (����ȿ������ and pk::has_tech(force, �ⱳ_���భȭ))
                    {
                        if (pk::get_kunshu_id(force) == ����_����)
                            mov = mov + 2;
                        else if (pk::get_kunshu_id(force) == pk::get_kunshu_id(pk::get_person(����_����)))
                            mov = mov + 2;
                    }
                }
                
			}
			else if (type == �δ�����_����)   // ���ۺδ�
			{
				if (pk::has_tech(force, �ⱳ_�������))
                    mov = mov + 3;
                
                mov = mov + 5;
				mov = mov + int(pk::core::skill_constant(member, Ư��_���)); // 5
               
               
                if (����ȿ������ and pk::has_tech(force, �ⱳ_�������))
				{
                    if (weapon_id == ����_�ְ�) //���� ���� ���
                    {
                        // ���º� ��۷� ���� ('18.10.4) - ���� ���� �Ǵ� ����/����� ������ ��� ������� ���� ȿ�� +4
                        if (pk::get_kunshu_id(force) == ����_�հ�)
                            mov = mov + 4;
                        else if (pk::get_kunshu_id(force) == ����_��å)
                            mov = mov + 4;
                        else if (pk::get_kunshu_id(force) == ����_�ձ�)
                            mov = mov + 4;
                        else if (pk::get_kunshu_id(force) == pk::get_kunshu_id(pk::get_person(����_����)))
                            mov = mov + 4;
                        else if (pk::get_kunshu_id(force) == pk::get_kunshu_id(pk::get_person(����_���)))
                            mov = mov + 4;
                    }
                     
                    else    //���� ���� ���
                    {
                        // ���º� ��۷� ���� ('18.10.4) - ���� ���� �Ǵ� ������/Ȳ������ ������ ��� ������� ���� ȿ�� +3
                        if (pk::get_kunshu_id(force) == ����_����)
                            mov = mov + 3;
                        else if (pk::get_kunshu_id(force) == ����_����)
                            mov = mov + 3;
                        else if (pk::get_kunshu_id(force) == pk::get_kunshu_id(pk::get_person(����_������)))
                            mov = mov + 3;
                        else if (pk::get_kunshu_id(force) == pk::get_kunshu_id(pk::get_person(����_Ȳ����)))
                            mov = mov + 3;
                    }
                }
			}
            
			if (navy)   //���� �δ��� ���
            {
				mov = mov + int(pk::core::skill_constant(member, Ư��_��Ÿ)); // 4
                
                if (����ȿ������)
                {
                    mov += 4; // �δ������� �����̵��� �ݿ��� ���� ���Ϸ� �⺻ �̵��� ����
                    // ���º� ���� �̵��� ���� ('18.10.1) - ����/���� ���� ���������δ� �̵���ȭ - ���భȭ �ⱳ���� �� �����
                    if (pk::has_tech(force, �ⱳ_���భȭ) and (type != �δ�����_����)) //���ۺ����� �ƴ�
                    {
                        if (pk::get_kunshu_id(force) == ����_�հ�)
                            mov = mov + 4;
                        else if (pk::get_kunshu_id(force) == ����_��å)
                            mov = mov + 4;
                        else if (pk::get_kunshu_id(force) == ����_�ձ�)
                            mov = mov + 4;
                        else if (pk::get_kunshu_id(force) == pk::get_kunshu_id(pk::get_person(����_����)))
                            mov = mov + 4;
                        else if (pk::get_kunshu_id(force) == pk::get_kunshu_id(pk::get_person(����_����)))
                            mov = mov + 4;
                        else if (pk::get_kunshu_id(force) == pk::get_kunshu_id(pk::get_person(����_����)))
                            mov = mov + 4;
                            
                        else if (pk::get_kunshu_id(force) == ����_��ǥ)
                            mov = mov + 4;
                        else if (pk::get_kunshu_id(force) == pk::get_kunshu_id(pk::get_person(����_ä��)))
                            mov = mov + 4;
                    }
                }
            }
            
            // '20.8.29, �̵��� �ִ밪 ���� ���� �߰�
            if (�̵���_�ִ�����)
                mov = pk::min(40, mov);
            
			attr.stat[�δ�ɷ�_�̵�] = pk::max(1, mov);   // '20.8.29, �̵��� �ּҰ� ���� �߰� (0 ���Ϸ� �� ��� ���� ƨ�� �� ����)
		}

        
        
		/**
			���迡 ���� �ɷ� ����  -- ���� ���� : ����� ����1, ����� ����2 �� �� ���� ��� �� �ִ밪 
		*/
		int func_495ff0(pk::person@ leader, int leader_stat, pk::person@ deputy, int deputy_stat)
		{
			if (leader_stat > deputy_stat)
				return leader_stat;

			int leader_id = leader.get_id();
			int deputy_id = deputy.get_id();

			if (pk::is_gikyoudai(leader, deputy_id) or pk::is_fuufu(leader, deputy_id))
				return deputy_stat;

			if (pk::is_like(leader, deputy_id) or pk::is_like(deputy, leader_id))
				return leader_stat + (deputy_stat - leader_stat) / 2;

			if (pk::is_ketsuen(leader, deputy_id))
				return leader_stat + (deputy_stat - leader_stat) / 3;

			if (pk::is_dislike(leader, deputy_id) or pk::is_dislike(deputy, leader_id))
				return leader_stat;

			return leader_stat + (deputy_stat - leader_stat) / 4;
		}

		/**
			���� ������ �����ϴ� ���谡 �ִ��� Ȯ��
		*/
		bool func_4960d0(pk::person@ a, pk::person@ b)
		{
			if (a !is null and b !is null)
				return pk::is_dislike(a, b.get_id()) or pk::is_dislike(b, a.get_id());
			return false;
		}
        
        // --------------------------------------------------------------------------------------
        //**  ���迡 ���� �ɷ� ����  -- �ű� ���� : �� ������ �ɷ� �������� ��� �� ����+����1+����2 ���� �ջ� **/
        int func_sub_stat(pk::person@ leader, int leader_stat, pk::person@ deputy, int deputy_stat)
		{
            
			int leader_id = leader.get_id();
			int deputy_id = deputy.get_id();
            
            int stat_add = 0;
            
            // ���� ���� ������ ��� : ���� ����
            if (pk::is_dislike(leader, deputy_id) or pk::is_dislike(deputy, leader_id))
				stat_add = 0;
            // ������ �Ǵ� �κ� ������ ��� : ���� �ɷ��� 25% ����
            else if (pk::is_gikyoudai(leader, deputy_id) or pk::is_fuufu(leader, deputy_id))
				stat_add = int(pk::max(0.25f*deputy_stat, 1.f*(deputy_stat-leader_stat)));
            // ���� ������ ��� : ���� �ɷ��� 20% ����
			else if (pk::is_ketsuen(leader, deputy_id))
				stat_add = int(0.2f * deputy_stat);
            // ����/������ ģ�� ������ ��� : ���� �ɷ��� 15% ����
			else if (pk::is_like(leader, deputy_id) or pk::is_like(deputy, leader_id))
				stat_add = int(0.15f * deputy_stat);
            // ��Ÿ ���� : ���� �ɷ��� 10% ����
			else
				stat_add = int(0.1f * deputy_stat);
            
            return stat_add;
        }
        // --------------------------------------------------------------------------------------
        
	}

	Main main;
}

