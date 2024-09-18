/*
@ ������: �⸶å��
@ UPDATE: '18.11.6
@ UPDATE: '18.11.27  / ���泻��: ���ӽ��۽ÿ��� �ߵ����ϰ� ����
@ UPDATE: '19.1.4    / ���泻��: ǳ�⼳�� �� ȭ��Ȯ��ȿ�� �߰� 
@ UPDATE: '19.1.19   / ���泻��: ����Ư��ȿ�� �߰�
@ UPDATE: '19.1.22   / ���泻��: ���������ȿ�� �߰�
@ UPDATE: '19.2.3    / ���泻��: ���������ȿ�� NPC�δ� �������� �߰�
@ UPDATE: '19.2.7    / ���泻��: ���������ȿ�� ������ �������� ���� ����
@ UPDATE: '19.2.16   / ���泻��: ��ȭǥ��Ȯ�� �߰�
@ UPDATE: '19.2.19   / ���泻��: ����Ư��ȿ���� ȸ���Ѱ谪 ���� �߰�
@ UPDATE: '19.3.10   / ���泻��: ����δ��۾��� ���� (PK2.1 �⺻���� ��ġ ��� �ٶ�)
@ UPDATE: '20.8.26   / ���泻��: ȭ��Ȯ��ȿ�� ���� ����, ķ���ο����� ��ũ��Ʈ ���۾��ϵ��� ����
*/

namespace �����δ�ȿ��
{
    
    //---------------------------------------------------------------------------------------
    // ���� ���� (true = on, false = off)
    const bool ��ȭǥ�ü��� = true;   // �����δ� ȿ���� ��ȭ ǥ�� ���� ����
    const int  ��ȭǥ��Ȯ�� = 30;     // �����δ� ȿ���� ��ô�ȭ Ȯ�� ����
    
    const bool ��������ȿ�� = true;   // �������� �δ�� ���� ��� ����
    const bool ��������ȿ�� = true;   // ������ ���� �δ��� ����
    const bool ������������ = true;   // ������ ���� �δ��� ����
    const bool ����Ż������ = true;   // ��� ���� �δ� ���� ���� ����
    
    const bool ȭ��Ȯ��ȿ�� = true;    // ���� �ٶ����⿡ ���� ȭ�� Ȯ�� ȿ��
    const int  ȭ��Ȯ��Ȯ�� = 50;
    const bool ǳ��޼���ǥ�� = true;
    
    const bool ����Ư��ȿ�� = true;    // �δ뺴���� �Ҽӵ����� Ư�꺴���� ��ġ�ϸ� �δ��� ����
    const bool ���������ȿ�� = true;   // ������ ���(��)�� �Ҽӵ����� �� ��ġ �� �δ��� ����
    
    //---------------------------------------------------------------------------------------
    
    
	class Main
	{
       
		Main()
		{
            pk::bind(103, pk::trigger103_t(onGameInit));
			pk::bind(107, pk::trigger107_t(onNewDay));
            
            pk::bind(120, pk::trigger120_t(onDrawGame));
		}

		void onNewDay()
		{
            if (pk::is_campaign()) return;
            
            // ���ӽ��۽ÿ��� �ߵ�����
            if (pk::get_elapsed_days() <= 0) return;
            
			auto list = pk::list_to_array(pk::get_unit_list());
			for (int i = 0; i < int(list.length); i++)
			{
				pk::unit@ unit = list[i];
                pk::point pos = unit.get_pos();
                pk::hex@ hex = pk::get_hex(pos);    // �δ��� ��ǥ
                
                
                // �����δ뺰 ȿ������ �Լ� ȣ��
                // �Լ� �������� true/false ������ ���� ȿ�� on/off ���� ����
                func_����_����(unit, pos, hex, ��������ȿ��);
                func_����_����(unit, pos, hex, ��������ȿ��);
                func_����_����(unit, pos, hex, ������������);
                func_����_Ż��(unit, pos, hex, ����Ż������);
                
                func_����Ư��ȿ��(unit, pos, ����Ư��ȿ��);
                func_���������ȿ��(unit, pos, ���������ȿ��);
            }
            
            func_ȭ��Ȯ��ȿ��(ȭ��Ȯ��ȿ��);
        }
        
        
        bool wind_init;
        int  wind_dir;
        
        void onGameInit()
        {
            if (pk::is_campaign()) return;
            
            main.wind_init = true;
            main.wind_dir = pk::rand(����_��);
            
            show_log_wind_dir(main.wind_dir);
        }
        
        void onDrawGame()
		{
            if (pk::is_campaign()) return;
            
            if (ȭ��Ȯ��ȿ��)
            {
                string wind_name = get_wind_name(main.wind_dir);
                pk::draw_text(pk::encode(wind_name), pk::point(250, 45), 0xffffffff, FONT_BIG, 0xff000000);
            }
        }
        
        
        //---------------------------------------------------------------------------------------
        // ����Ư�� ���� �δ밡 �������� ��� ��� ������ �߻� ('18.10.24)
        void func_����_����(pk::unit@ unit, pk::point pos, pk::hex@ hex, bool ȿ������)
        {
            if (ȿ������)
            {
                    
                int cnt_enemy = 0;
                array<pk::point> arr = pk::range(pos, 1, 1);
                for (int j = 0; j < int(arr.length); j++)
                {
                    pk::unit@ target_unit = pk::get_unit(arr[j]);
                    if (target_unit !is null and pk::is_enemy(unit, target_unit))
                    {
                        cnt_enemy += 1; 
                    }
                }
                if ((cnt_enemy >= 3) and !unit.has_skill(Ư��_����))
                {
                    pk::add_energy(unit, -(2 + cnt_enemy), true);      // �������ϸ� ��� -5 �̻�
                    
                    if (��ȭǥ�ü��� and pk::is_in_screen(pos))
                        pk::say(pk::encode("� �������� �����϶�"), pk::get_person(unit.leader));
                    
                }
                
            }
        }
        
        //---------------------------------------------------------------------------------------
        // Ȥ��/Ȥ�� ���� �� ���� ��� ���� ȿ��
        void func_����_����(pk::unit@ unit, pk::point pos, pk::hex@ hex, bool ȿ������)
        {
            int energy_damage = -1;     // ���� �����δ� ������� �⺻

            if (ȿ������)
            {
              
                int unit_tekisei = pk::get_tekisei(unit);
                switch(pk::get_season())
                {
                    case ����_���� :         // 1.���� : �Ϻ� A���� ������ ��ŭ ����
                        energy_damage = energy_damage + unit_tekisei - ����_A -1;
                        
                        if (��ȭǥ�ü��� and pk::rand_bool(��ȭǥ��Ȯ��) and pk::is_in_screen(pos))  // ȭ�� �� �δ븸 ��ȭ ǥ��
                        {
                            switch (pk::rand(4))
                            {
                                case 0: pk::say(pk::encode("Ȥ���⿡�� ������� ��ġ�±�"), pk::get_person(unit.leader)); break;
                                case 1: pk::say(pk::encode("������ �Ծ���"), pk::get_person(unit.leader)); break;
                                case 2: pk::say(pk::encode("�޻��� �ʹ� ������"), pk::get_person(unit.leader)); break;
                                case 3: pk::say(pk::encode("���� Ÿ��� ���±���"), pk::get_person(unit.leader)); break;
                            }
                        }
                        break;
                        
                    case ����_�ܿ�:         // 3.�ܿ� : �Ϻ� S���� ������ + 1 ��ŭ ����
                        energy_damage = energy_damage + unit_tekisei - ����_S -1;
                        
                        if (��ȭǥ�ü��� and pk::rand_bool(��ȭǥ��Ȯ��) and pk::is_in_screen(pos))  // ȭ�� �� �δ븸 ��ȭ ǥ��
                        {
                            switch (pk::rand(4))
                            {
                                case 0: pk::say(pk::encode("Ȥ�ѱ⿡�� ������� ��ġ�±�"), pk::get_person(unit.leader)); break;
                                case 1: pk::say(pk::encode("������ Ÿ�±�"), pk::get_person(unit.leader)); break;
                                case 2: pk::say(pk::encode("�� �ٶ��� �ż���"), pk::get_person(unit.leader)); break;
                                case 3: pk::say(pk::encode("��� ���� �� ����"), pk::get_person(unit.leader)); break;
                            }
                        }
                        break;
                }
            }
            
            // ��� ���� ó��
            pk::add_energy(unit, energy_damage, true);   
            
        }
             
        //---------------------------------------------------------------------------------------  
        void func_����_����(pk::unit@ unit, pk::point pos, pk::hex@ hex, bool ȿ������)
        {   
            if (ȿ������)
            {        
                // �δ밡 ��� �౺ �� ���� ��� -2
                if (hex.terrain == ����_��) 
                {
                    if (��ȭǥ�ü��� and pk::is_in_screen(pos))  // ȭ�� �� �δ븸 ��ȭ ǥ��
                    {
                        switch (pk::rand(4))
                        {
                            case 0: pk::say(pk::encode("�� ��� ������ �ȴ�"), pk::get_person(unit.leader)); break;
                            case 1: pk::say(pk::encode("����౺�� ������� ��ġ�� �ϴ±�"), pk::get_person(unit.leader)); break;
                            case 2: pk::say(pk::encode("������ �����. �ӵ��� ����"), pk::get_person(unit.leader)); break;
                            case 3: pk::say(pk::encode("������ ���տ� �ִ�"), pk::get_person(unit.leader)); break;
                        }
                    }
                    
                    pk::add_energy(unit, -2, true);
                }
            }
        }
                
                
        //---------------------------------------------------------------------------------------     
        // �����δ� Ż���� ȿ��       
        void func_����_Ż��(pk::unit@ unit, pk::point pos, pk::hex@ hex, bool ȿ������)
        {
            if (ȿ������)
            { 
        
                uint troops_loss = 0;
                
                // ȥ�� �δ� Ż���� ȿ�� : ���� 5% ��Ż
                if (unit.status == �δ����_ȥ��)
                {
                    troops_loss = int(pk::min(unit.troops, pk::max(100.f, unit.troops*0.05f)));
                    pk::add_troops(unit, -troops_loss, true );
                    
                    if (��ȭǥ�ü��� and pk::is_in_screen(pos))  // ȭ�� �� �δ븸 ��ȭ ǥ��
                    {
                        switch (pk::rand(4))
                        {
                            case 0: pk::say(pk::encode("���� ȥ���� �����ؾ� �ȴ�"), pk::get_person(unit.leader));  break;
                            case 1: pk::say(pk::encode("������� ��������"), pk::get_person(unit.leader));  break;
                            case 2: pk::say(pk::encode("�δ븦 � �����϶�"), pk::get_person(unit.leader)); break;
                            case 3: pk::say(pk::encode("�̴�� ���ٰ��� �����Ѵ�"), pk::get_person(unit.leader)); break;
                        }
                    }
                }
                
                // ��� ���� �δ� Ż���� ȿ�� : �����δ� ��� 10���� �� ����10%, 25���� �� ����5% ����
                if (unit.energy <= 25)
                {
                    if (unit.energy <= 10)
                    {
                        troops_loss = int(pk::min(unit.troops, pk::max(100.f, unit.troops*0.10f)));
                        pk::add_troops(unit, -troops_loss, true );
                    }
                    else if (unit.energy <= 25)
                    {
                        troops_loss = int(pk::min(unit.troops, pk::max(100.f, unit.troops*0.05f)));
                        pk::add_troops(unit, -troops_loss, true );
                    }
                    
                    
                    if (��ȭǥ�ü��� and pk::is_in_screen(pos))  // ȭ�� �� �δ븸 ��ȭ ǥ��
                    {
                        switch (pk::rand(4))
                        {
                            case 0: pk::say(pk::encode("Ż������ �����ϴ±�"), pk::get_person(unit.leader));  break;
                            case 1: pk::say(pk::encode("������� ��������"), pk::get_person(unit.leader));  break;
                            case 2: pk::say(pk::encode("�δ� ��Ⱑ ���� �ƴϱ�"), pk::get_person(unit.leader)); break;
                            case 3: pk::say(pk::encode("�̴�� ���ٰ��� �����Ѵ�"), pk::get_person(unit.leader)); break;
                        }
                    }
                }
                // ���� 0 �� �Ǹ� �δ� �˸�
                if (unit.troops == 0)       
                    pk::kill(unit);
                
            }
        }   
        
        //---------------------------------------------------------------------------------------
        void func_ȭ��Ȯ��ȿ��(bool ȿ������)
        {
            if (ȿ������)
            {
                pk::array<pk::point> arr_fire;
                
                // ǳ�� ������Ʈ
                if (wind_init) 
                    wind_init = false;  // �ó����� ���� �Ǵ� �ε� ��
                else if (pk::get_day() == 1 and pk::is_first_month_of_quarter(pk::get_month()))
                    main.wind_dir = pk::rand(����_��);  // �� ������ �Ǹ� �������� ǳ�� ����
                else
                    main.wind_dir = get_wind_dir(main.wind_dir);  // �����ϰ� ���� �̼� ����
                
                // ǳ�� �ȳ�
                if (ǳ��޼���ǥ�� and pk::get_player_count() > 0) 
                    show_log_wind_dir(main.wind_dir);
                
                int fire_dir = pk::get_opposite_direction(main.wind_dir);
                for (int pos_x = 0; pos_x < 200; pos_x++)
                {
                    for (int pos_y = 0; pos_y < 200; pos_y++)
                    {
                        pk::point pos;
                        pos.x = pos_x;
                        pos.y = pos_y;
                        
                        pk::hex@ hex = pk::get_hex(pos);
                        if (pk::is_valid_pos(pos) and pk::is_valid_hex_direction(fire_dir) and pk::is_on_fire(pos) and !contains_pos(arr_fire, pos))
                        {
                            pk::point neighbor_pos = pk::get_neighbor_pos(pos, fire_dir);
                            if (pk::is_valid_pos(neighbor_pos))
                            {
                                pk::hex@ neighbor_hex = pk::get_hex(neighbor_pos);
                                int terrain_id = neighbor_hex.terrain;
                                
                                if (pk::rand_bool(ȭ��Ȯ��Ȯ��) and pk::is_enabled_terrain(terrain_id) )
                                {
                                    if (!pk::is_water_terrain(terrain_id) or (pk::is_water_terrain(terrain_id) and neighbor_hex.has_unit))
                                    {
                                        arr_fire.insertLast(neighbor_pos);
                                        pk::create_fire(neighbor_pos, (1 + pk::rand(2)) );
                                        
                                        pk::unit@ unit = pk::get_unit(neighbor_pos);
                                        if (unit !is null and pk::is_in_screen(neighbor_pos))
                                        {
                                            switch (pk::rand(4))
                                            {
                                                case 0: pk::say(pk::encode("��Ȳ���� ����!"), pk::get_person(unit.leader)); break;
                                                case 1: pk::say(pk::encode("� ���� ����"), pk::get_person(unit.leader)); break;
                                                case 2: pk::say(pk::encode("���� ������ �ʵ��� �ض�"), pk::get_person(unit.leader)); break;
                                                case 3: pk::say(pk::encode("���⸦ ����� �Ѵ�"), pk::get_person(unit.leader)); break;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        
        // ǳ�� ���� �Լ�
        int get_wind_dir(int seed_dir)
        {
            int new_dir;
            int rand_dir = pk::rand(5);
            
            switch(seed_dir)
            {
                case ����_�ϼ�: 
                    switch(rand_dir)
                    {
                        case 0: new_dir = ����_����; break;
                        case 1: new_dir = ����_����; break;
                        case 2: new_dir = ����_�ϼ�; break;
                        case 3: new_dir = ����_��; break;
                        case 4: new_dir = ����_��; break;
                    }
                    break;
                    
                case ����_�� :
                    switch(rand_dir)
                    {
                        case 0: new_dir = ����_�ϼ�; break;
                        case 1: new_dir = ����_�ϼ�; break;
                        case 2: new_dir = ����_��; break;
                        case 3: new_dir = ����_�ϵ�; break;
                        case 4: new_dir = ����_�ϵ�; break;
                    }
                    break;
                    
                case ����_�ϵ�:
                    switch(rand_dir)
                    {
                        case 0: new_dir = ����_��; break;
                        case 1: new_dir = ����_��; break;
                        case 2: new_dir = ����_�ϵ�; break;
                        case 3: new_dir = ����_����; break;
                        case 4: new_dir = ����_����; break;
                    }
                    break;
                    
                case ����_����:
                    switch(rand_dir)
                    {
                        case 0: new_dir = ����_��; break;
                        case 1: new_dir = ����_��; break;
                        case 2: new_dir = ����_����; break;
                        case 3: new_dir = ����_�ϼ�; break;
                        case 4: new_dir = ����_�ϼ�; break;
                    }
                    break;
                    
                case ����_�� : 
                    switch(rand_dir)
                    {
                        case 0: new_dir = ����_����; break;
                        case 1: new_dir = ����_����; break;
                        case 2: new_dir = ����_��; break;
                        case 3: new_dir = ����_����; break;
                        case 4: new_dir = ����_����; break;
                    }
                    break;
                    
                case ����_����:
                    switch(rand_dir)
                    {
                        case 0: new_dir = ����_�ϵ�; break;
                        case 1: new_dir = ����_�ϵ�; break;
                        case 2: new_dir = ����_����; break;
                        case 3: new_dir = ����_��; break;
                        case 4: new_dir = ����_��; break;
                    }
                    break;
            }
            
            return new_dir;
        }
        
        // ǳ�� �޼��� ��� �Լ�
        void show_log_wind_dir(int direction)
        {
            string wind_name = get_wind_name(direction);
            
            int pause = int(pk::option["MessagePause"]);
            pk::option["MessagePause"] = 5;
            switch(pk::rand(4))
            {
                case 0: pk::message_box(pk::encode(pk::format("���� �ٶ��� \x1b[1x{}\x1b[0x�̶��", wind_name)), pk::get_person(����_����)); break;
                case 1: pk::message_box(pk::encode(pk::format("��...\x1b[1x{}\x1b[0x�� �δ±���", wind_name)), pk::get_person(����_����)); break;
                case 2: pk::message_box(pk::encode(pk::format("�̺���. \x1b[1x{}\x1b[0x�� �Ҿ���±���", wind_name)), pk::get_person(����_���)); break;
                case 3: pk::message_box(pk::encode(pk::format("ǳ���� �ƴ°�? \x1b[1x{}\x1b[0x�̶��", wind_name)), pk::get_person(����_����)); break;
            }
            pk::option["MessagePause"] = pause;
        }
        
        
        // ǳ��� ��ȯ �Լ�
        string get_wind_name(int direction)
        {
            string wind_name;
            switch(direction)
            {
               case ����_�ϼ� : wind_name = "�ϼ�ǳ";  break;
               case ����_��  : wind_name = "��ǳ";  break;
               case ����_�ϵ� : wind_name = "�ϵ�ǳ";  break;
               case ����_���� : wind_name = "����ǳ";  break;
               case ����_��  : wind_name = "��ǳ";  break;
               case ����_���� : wind_name = "����ǳ";  break;
            }
            return wind_name;
        }
        
        
        bool contains_pos(pk::array<pk::point> arr_pos, pk::point pos)
        {
            for (int i = 0; i < int(arr_pos.length); i++)
            {
                if (pos == arr_pos[i]) return true;
            }
            
            return false;
        }
        
        //---------------------------------------------------------------------------------------
        
        
        void func_����Ư��ȿ��(pk::unit@ unit, pk::point pos, bool ȿ������)
        {
            if (!pk::is_normal_force(unit.get_force_id())) return;
            
            if (ȿ������)
            {
                pk::city@ city = pk::get_city(pk::get_service(unit));
                if (pk::is_alive(city))
                {
                    int weapon_heishu = pk::equipment_id_to_heishu(unit.weapon);
                    
                    // �Ҽӵ��ð� �뵵���� ��� ���� ȸ��
                    if (pk::is_large_city(city) and unit.type == �δ�����_���� and unit.troops < 3000)
                    {
                        pk::add_troops(unit, int(0.05f * unit.troops), true); 
                    }
                    // �δ� ������ �Ҽӵ��� Ư��� ��ġ�ϸ� ��� ȸ��
                    if (city.tokusan[weapon_heishu] and unit.energy < 40)
                    {
                        if (��ȭǥ�ü��� and pk::rand_bool(��ȭǥ��Ȯ��) and pk::is_in_screen(pos))  // ȭ�� �� �δ븸 ��ȭ ǥ��
                        {
                            string city_name = pk::decode(pk::get_name(city));
                            string weapon_name = get_weapon_name(unit.weapon);
                            
                            switch(pk::rand(4))
                            {
                            case 0: pk::say(pk::encode(pk::format("�̰��� \x1b[2x{} \x1b[1x{}\x1b[0x�� �⼼��", city_name, weapon_name)), pk::get_person(unit.leader)); break;
                            case 1: pk::say(pk::encode(pk::format("\x1b[2x{} \x1b[1x{}\x1b[0x�� ������ ��������", city_name, weapon_name)), pk::get_person(unit.leader)); break;
                            case 2: pk::say(pk::encode(pk::format("\x1b[2x{}�� �ڰ�� \x1b[1x{}\x1b[0x�� ��������", city_name, weapon_name)), pk::get_person(unit.leader)); break;
                            case 3: pk::say(pk::encode(pk::format("\x1b[2x{}��� \x1b[1x{}\x1b[0x�̴�", city_name, weapon_name)), pk::get_person(unit.leader)); break;
                            }
                        }
                        
                        pk::add_energy(unit, +5, true); 
                    }
                    
                }
            }
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
        
        
        void func_���������ȿ��(pk::unit@ unit, pk::point pos, bool ȿ������)
        {
            if (!pk::is_normal_force(unit.get_force_id())) return;
            
            if (ȿ������)
            {
                pk::person@ leader = pk::get_person(unit.leader);
                int birth_province = leader.birthplace;
                
                pk::building@ building = pk::get_building(pk::get_service(unit));
                if (!pk::is_alive(building)) return;
                    
                pk::city@ service_city = pk::get_city(pk::get_city_id(building.pos));
                int service_province = service_city.province;
            
                if (birth_province == service_province)
                {
                    if (��ȭǥ�ü��� and pk::rand_bool(��ȭǥ��Ȯ��) and pk::is_in_screen(pos))  // ȭ�� �� �δ븸 ��ȭ ǥ��
                    {
                        string service_province_name = pk::decode(pk::get_name(pk::get_province(service_province)));
                        
                        switch(pk::rand(4))
                        {
                        case 0: pk::say(pk::encode(pk::format("������ \x1b[1x{}����\x1b[0x ������ \n�Բ���� ����� ���±�", service_province_name)), pk::get_person(unit.leader)); break;
                        case 1: pk::say(pk::encode(pk::format("\x1b[1x{}����\x1b[0x ������̿� ���� ������", service_province_name)), pk::get_person(unit.leader)); break;
                        case 2: pk::say(pk::encode(pk::format("���� \x1b[1x{}����\x1b[0x ����̶��", service_province_name)), pk::get_person(unit.leader)); break;
                        case 3: pk::say(pk::encode(pk::format("\x1b[1x{}����\x1b[0x ��� �δ��� ������ ��������", service_province_name)), pk::get_person(unit.leader)); break;
                        }
                    }
                    
                    pk::add_energy(unit, +5, true); 
                }
            }
        }
        
        
        //---------------------------------------------------------------------------------------
        
	}

	Main main;
}