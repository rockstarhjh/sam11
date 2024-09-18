/*
@ ������: �⸶å��
@ UPDATE: '18.11.6   / ��������: ��������ȿ��, �����־�ȿ��, ������ȿ��, �����༺ȿ��
@ UPDATE: '18.11.11  / ���泻��: ����Ʈ ȿ������, ����ȭ��ݰ� �߰�
@ UPDATE: '18.11.23  / ���泻��: AI/Player���������� �߰�, ��������ȸ�� -AI������ �� �ߵ�����
@ UPDATE: '18.11.26  / ���泻��: ����ȭ��ݰ� NPC�δ� ���� ����
@ UPDATE: '18.12.5   / ���泻��: ����ȭ��ݰ� �¼�Ȯ�� ���� �߰�, ȿ���ߵ� �ǹ�Ÿ�� �����ɼ� �߰�
@ UPDATE: '20.8.26   / ���泻��: ķ���ο����� ��ũ��Ʈ ���� ���ϵ��� ����
*/

namespace ��������ȿ��
{
    //---------------------------------------------------------------------------------------
    // ���� ���� (true = on, false = off)
    const bool ��ȭǥ�ü��� = true;
    
    const bool ȿ��_AI�� = false;      // true =AI�� ȿ������, false =������ AI ��� ȿ�� ���� (�ߵ�����)
    const bool ȿ��_Player�� = false;  // true =Player�� ȿ������, false =������ AI ��� ȿ�� ����
    //---------------------------------------------------------------------------------------
    const bool ȿ��_���ü��� = true;  // ���� ������ ���ؼ� ȿ�� ���� ����
    const bool ȿ��_�������� = true;  // ���� ������ ���ؼ� ȿ�� ���� ����
    const bool ȿ��_�ױ����� = true;  // �ױ� ������ ���ؼ� ȿ�� ���� ����
    //---------------------------------------------------------------------------------------
    
    const bool ��������ȸ�� = true;   // �� �� ���� ���� �� ��ġ�� �ջ꿡 ����Ͽ� ���� ȸ��
    const bool �����༺ȿ�� = true;   // Ư��_�༺ ���� ���� ���� ���� ȸ��
    const bool ��������ȿ�� = true;   // �ֺ��� ���� ���� �� ������Ż, ��°���
    
    const bool ����ȭ��ݰ� = true;   // ������ �޶���� �� ���δ뿡 ȭ��ߵ� : Ư��_ȭ��, ȭ�� ��� ('18.11.11)
    
    const bool �����־�ȿ�� = true;   // Ư��_�־� ���� ������ ��� ȸ�� (�û� ȿ�� 2��)
    const bool ������ȿ�� = true;   // Ư��_�� ���� ������ ���� ����
    
    //---------------------------------------------------------------------------------------
    
    
	class Main
	{
		Main()
		{
			pk::bind(107, pk::trigger107_t(onNewDay));
		}

		void onNewDay()     // �Ϻ�
		{
            if (pk::is_campaign()) return;
            
            // ���ӽ��۽ÿ��� �ߵ�����
            if (pk::get_elapsed_days() <= 0) return;
            
            // ����_����
            for (int i = �ǹ�_���ý���; i < �ǹ�_���ó�; i++)
                func_building_effect(pk::get_building(i), ȿ��_���ü���);

            // ����_����
            for (int i = �ǹ�_��������; i < �ǹ�_������; i++)
                func_building_effect(pk::get_building(i), ȿ��_��������);

            // ����_�ױ�
            for (int i = �ǹ�_�ױ�����; i < �ǹ�_�ױ���; i++)
                func_building_effect(pk::get_building(i), ȿ��_�ױ�����);
            
        }
        
        void func_building_effect(pk::building@ building, bool ȿ������)
        {
            if (ȿ������)
            {
                // �ǹ��� ����ȿ�� �Լ� ȣ��
                // �Լ� �������� true/false ������ ���� ȿ�� on/off ���� ����
                func_����_����ȸ��(building, ��������ȸ��);    // �Ϻ� 
                func_����_�༺ȿ��(building, �����༺ȿ��);    // �Ϻ�
                func_����_����ȿ��(building, ��������ȿ��);    // �Ϻ� 
                func_����_ȭ��ݰ�(building, ����ȭ��ݰ�);    // �Ϻ�
                func_����_�־�ȿ��(building, �����־�ȿ��);    // ���� (pk::trigger108_t �̻��)
                func_����_��ȿ��(building, ������ȿ��);    // �б⺰ (pk::trigger109_t �̻��)
            }
        }
        
        
        
        //-------------------------------------------------------------------------------------------------
        // ���� �Ǵ� AI�� ���� �� �Ǵ��Լ�
        bool only_AI_unit(pk::unit@ unit)
        {
            if (ȿ��_AI�� and unit.is_player()) return false;
            return true;
        }
        bool only_AI_building(pk::building@ building)
        {
            if (ȿ��_AI�� and building.is_player()) return false;
            return true;
        }
        bool only_player_unit(pk::unit@ unit)
        {
            if (ȿ��_Player�� and !unit.is_player()) return false;
            return true;
        }
        bool only_player_building(pk::building@ building)
        {
            if (ȿ��_Player�� and !building.is_player()) return false;
            return true;
        }
        
        //-------------------------------------------------------------------------------------------------
        //-------------------------------------------------------------------------------------------------
        
        // ���� �� ������ ȸ�� : ��ġ �հ� x10 ('18.11.10)
        void func_����_����ȸ��(pk::building@ building, bool ȿ������)
        {
            // ���� 5ĭ �̳� Player �Ǵ� AI���� ���� ������ Ȯ�� ('18.11.23)
            // AI ������ �ÿ��� ȸ�� ����!!! 
            // Player ������ �ÿ��� ȸ���� 1.5��
            bool engage_AI_unit = false;
            bool engage_player_unit = false;
            auto range = pk::range(building.pos, 1, 5);
            for (int j = 0; j < int(range.length); j++)
            {
                pk::unit@ unit = pk::get_unit(range[j]);
                if (unit !is null and !building.is_player() and !unit.is_player() and pk::is_enemy(building, unit))
                    engage_AI_unit = true;
                if (unit !is null and !building.is_player() and  unit.is_player() and pk::is_enemy(building, unit))
                    engage_player_unit = true;
            }
            
            if (ȿ������ and only_AI_building(building) and !engage_AI_unit)
            {
                if (int(building.hp) < int(pk::get_max_hp(building)))
                {
                    if (pk::is_in_screen(building.pos))
                    {
                        pk::person@ taishu = pk::get_person(pk::get_taishu_id(building));
                        if (��ȭǥ�ü���)
                            pk::say(pk::encode("������ �����ϱ� ���� �����϶�"), taishu );
                    }
                    
                    int build_point = 10 * func_stat_sum(building, ����ɷ�_��ġ); // �� �� ������ ��ġ �ɷ� �κ� �ջ�
                    
                    if (engage_player_unit)    // player �� ���� ���̸� ���� ȸ���� 1.5��
                        build_point = int(build_point * 1.5f);
                    
                    pk::add_hp(building, build_point, true );
                }
                
            }            
        }        
		int func_stat_sum(pk::building@ building, int stat_type)
		{
            //���� �� ���� �ɷ� �ݿ� (�� ������ ��ġ �ջ�) ('18.10.7)
            float add_ratio = 10;    // �ջ� ������ : ���庰 10%
            int stat_sum = 0;
            
            auto list = pk::list_to_array(pk::get_person_list(building, pk::mibun_flags(�ź�_����, �ź�_�¼�, �ź�_�Ϲ�) ) );
            if (0 < list.length)
            {
                for (int i = 0; i < int(list.length); i++)
                {
                    pk::person@ person = list[i];
                    //���� �Ǵ� ������ ���°� �ƴ� ����̸�, �¼��� ���� ���谡 �ƴ� ����� �ɷ� ġ �ջ�
                    if (!pk::is_unitize(person) and !pk::is_absent(person))
                    {
                        stat_sum += int((pk::max(person.stat[stat_type] - 25, 20)) * (add_ratio / 100.f));
                    }
                }
            }
            return stat_sum;
		}
                

        //-------------------------------------------------------------------------------------------------
        // ���� �ֺ��� ���δ� ���� ��� ���� �� ��� ���� ('18.10.21)
        void func_����_����ȿ��(pk::building@ building, bool ȿ������)
        {
            if (ȿ������ and only_player_building(building))
            {
                if (pk::enemies_around(building))
                {
                    int n = pk::max(pk::get_troops(building), 100);
                    n = int(pk::rand(400) + 40 * sqrt(n / 100));
                
                    pk::add_troops(building, -n, true);   // ����ȿ���� ���� ���� 
                    pk::add_energy(building, -3, true);   // ����ȿ���� ��� 3 ����
                }
                
            }
        }
        
        //-------------------------------------------------------------------------------------------------
        // ������ ���δ� �޶� ���� ��� ȭ�� �ߵ� ('18.11.11)
        void func_����_ȭ��ݰ�(pk::building@ building, bool ȿ������)
        {
            if (ȿ������ and only_AI_building(building))
            {
                int msg_count = 0;
                int dst_range = (building.get_id() < �ǹ�_���ó�)? 2 : 1;
                
                array<pk::point> arr = pk::range(building.pos, dst_range, dst_range);
                for (int j = 0; j < int(arr.length); j++)
                {
                    pk::unit@ unit = pk::get_unit(arr[j]);
                    if (unit !is null and pk::is_enemy(unit, building))
                    {
                        int fire_chance = 0;
                        int fire_timer = 0;
                        int fire_person_id = 0;
                        
                        pk::person@ taishu = pk::get_person(pk::get_taishu_id(building));
                        
                        int stat_delta = 100;
                        if (taishu is null) 
                            stat_delta = 0;
                        else if (unit.leader < ����_���� or unit.leader > ����_����)
                            stat_delta = pk::max(0, taishu.stat[����ɷ�_����] - unit.attr.stat[�δ�ɷ�_����]);
                        
                        // �ߵ� Ȯ�� �� Ÿ�̸� ����
                        if (taishu is null) 
                            fire_chance = 0;
                        else if (pk::is_valid_person_id(building.who_has_skill(Ư��_ȭ��)))
                        {
                            fire_chance = 100;
                            fire_timer = 1;
                            fire_person_id = building.who_has_skill(Ư��_ȭ��);
                        }
                        else if (pk::is_valid_person_id(building.who_has_skill(Ư��_ȭ��)))
                        {
                            fire_chance = pk::min(100, stat_delta + 50);
                            fire_timer = 1;
                            fire_person_id = building.who_has_skill(Ư��_ȭ��);
                        }
                        else
                        {
                            fire_chance = pk::min(100, stat_delta);
                            fire_person_id = pk::get_taishu_id(building);
                        }
                        

                        // ȭ�� �ߵ�
                        if (pk::rand_bool(fire_chance) and !pk::is_on_fire(unit.pos))
                        {
                            if (��ȭǥ�ü��� and pk::is_in_screen(building.pos) and msg_count == 0)
                            {
                                msg_count = 1;
                                pk::say(pk::encode("�߰ſ� �⸧�� ���� �����"), pk::get_person(fire_person_id) );
                                pk::play_se(0x39, building.pos);
                                switch (pk::rand(3))
                                {
                                    case 0: pk::play_voice(0x33, pk::get_person(fire_person_id) ); break;   // ���� : ȭ��
                                    case 1: pk::play_voice(0x34, pk::get_person(fire_person_id) ); break;   // ���� : ȭ��
                                    case 2: pk::play_voice(0x35, pk::get_person(fire_person_id) ); break;   // ���� : ȭ��
                                }
                            }
                            
                            pk::create_fire(unit.pos, pk::rand(1) + 1 + fire_timer, unit, true);
                            
                            if (��ȭǥ�ü��� and pk::is_in_screen(building.pos))
                            {
                                switch (pk::rand(4))
                                {
                                    case 0: pk::say(pk::encode("���ƾ�.."), pk::get_person(����_����), unit); break;
                                    case 1: pk::say(pk::encode("�� ��"), pk::get_person(����_����), unit); break;
                                    case 2: pk::say(pk::encode("���� ���� ���ض�"), pk::get_person(����_����), unit); break;
                                    case 3: pk::say(pk::encode("��. ���̴�!"), pk::get_person(����_����), unit); break;
                                }
                            }
                        }
                        
                    }
                }
            }
        }
        
        //-------------------------------------------------------------------------------------------------
        // ���� �� Ư��_�־� ������ �Ҽ� �� ��� ȸ�� +5 ~ +10 ('18.10.21)
        void func_����_�־�ȿ��(pk::building@ building, bool ȿ������)
        {            
            if (ȿ������ and only_AI_building(building))
            {
                // ���� ����, �ſ� 1�Ͽ� �ߵ�
                int cheer_point = 0;
                if (pk::is_valid_person_id(building.who_has_skill(Ư��_�־�)) and (pk::get_day() == 1))
                {
                    if (pk::get_energy(building) < pk::get_max_energy(building))
                    {
                        if (��ȭǥ�ü��� and pk::is_in_screen(building.pos))
                        {
                            pk::say(pk::encode("������� ��⸦ ȸ���϶�"), pk::get_person(building.who_has_skill(Ư��_�־�)) );
                            pk::play_se(0x39, building.pos);
                            pk::play_voice(0x37, pk::get_person(building.who_has_skill(Ư��_�־�)) );   // ���� : ����_����
                        }
                        
                        cheer_point = 5;
                        if (pk::is_valid_person_id(building.who_has_skill(Ư��_�û�)) )
                            cheer_point *= 2;
                        
                        pk::add_energy(building, cheer_point, true);
                    }
                }
                
            }
        }  
         
        //-------------------------------------------------------------------------------------------------
        // ���� �� Ư��_�� ������ �Ҽ� �� �źб⺰ ���� ���� : �ŷ� x 10 ('18.10.22)
        void func_����_��ȿ��(pk::building@ building, bool ȿ������)
        {       
            if (ȿ������ and only_AI_building(building))
            {
                // �б⺰ ����, �źб� ù�� 1�Ͽ��� �ߵ�
                int famous_point = 0;
                if (pk::is_valid_person_id(building.who_has_skill(Ư��_��)) and pk::is_first_month_of_quarter(pk::get_month()) and (pk::get_day() == 1) )
                {
                    if (pk::get_troops(building) < pk::get_max_troops(building))
                    {
                        if (��ȭǥ�ü��� and pk::is_in_screen(building.pos))
                        {
                            pk::say(pk::encode("���� ����� �޾��ֽʽÿ�"), pk::get_person(����_û��), building);
                            pk::play_se(0x39, building.pos);
                            pk::play_voice(0x31, pk::get_person(building.who_has_skill(Ư��_��)) );   // ���� : ����_�跫2
                        }
                        
                        famous_point += 10 * (pk::get_person(building.who_has_skill(Ư��_��)).stat[����ɷ�_�ŷ�]);
                        pk::add_troops(building, famous_point, true );
                    }
                    
                }
                
            }
        }
        
        //-------------------------------------------------------------------------------------------------
        // ���� �� Ư��_�༺ ������ �Ҽ� �� ������ ȸ�� : ��ġ x 5 ('18.10.22)
        void func_����_�༺ȿ��(pk::building@ building, bool ȿ������)
        {
            if (ȿ������ and only_AI_building(building))
            {
                int build_point = 0;
                if (pk::is_valid_person_id(building.who_has_skill(Ư��_�༺)) )
                {
                    if (int(building.hp) < int(pk::get_max_hp(building)))
                    {
                        if (��ȭǥ�ü��� and pk::is_in_screen(building.pos))
                        {
                            pk::say(pk::encode("� ������ �����϶�"), pk::get_person(building.who_has_skill(Ư��_�༺)) );
                            pk::play_se(0x39, building.pos);
                            switch(pk::rand(2))
                            {
                                case 0 : pk::play_voice(0x39, pk::get_person(building.who_has_skill(Ư��_�༺)) ); break;   // ���� : ��ġ
                                case 1 : pk::play_voice(0x3a, pk::get_person(building.who_has_skill(Ư��_�༺)) ); break;   // ���� : ��ġ
                            }
                        }
                        
                        build_point += 5 * (pk::get_person(building.who_has_skill(Ư��_�༺)).stat[����ɷ�_��ġ]);
                        pk::add_hp(building, build_point, true );
                    }
                }
                
            }
        }
        
        
        //-------------------------------------------------------------------------------------------------
        
	}

	Main main;
}