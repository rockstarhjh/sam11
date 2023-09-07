/*
�� ���ǻ��� : �� ��ũ��Ʈ�� �⺻ COST ���� ���� �� SCENARIO ���Ͽ� ������ ���� �����ϰ� �����˴ϴ�.

@������: �⸶å��
@Update: '19.1.10  / ��������: �ⱳ���� �ʿ䰪 �������� ��� �߰�,   ���� �ⱳ���� ����� �߰�

*/

namespace �ⱳ��������
{
    //---------------------------------------------------------------------------------------
    // ���� ���� (true = on, false = off)
    
    // �⺻ �ⱳ���� ������ ���� (�� ���ǻ��� Ȯ�� �� ����� �� !!)
    const bool �ⱳ_GOLD_COST_����  = false;
    const bool �ⱳ_TP_COST_����    = false;
    const bool �ⱳ_TIME_COST_����  = false;
    
    const uint16 �ⱳLV1_GOLD_COST = 1000;        // ǥ��: 1000
    const uint16 �ⱳLV1_TP_COST   = 1000;        // ǥ��: 1000
    const uint16 �ⱳLV1_TIME_COST = 3;           // ǥ��: 3
    
    const uint16 �ⱳLV2_GOLD_COST = 2000;        // ǥ��: 2000
    const uint16 �ⱳLV2_TP_COST   = 2000;        // ǥ��: 2000
    const uint16 �ⱳLV2_TIME_COST = 4;           // ǥ��: 4    
    
    const uint16 �ⱳLV3_GOLD_COST = 5000;        // ǥ��: 5000
    const uint16 �ⱳLV3_TP_COST   = 3000;        // ǥ��: 3000
    const uint16 �ⱳLV3_TIME_COST = 6;           // ǥ��: 6
    
    const uint16 �ⱳLV4_GOLD_COST = 10000;       // ǥ��: 10000
    const uint16 �ⱳLV4_TP_COST   = 5000;        // ǥ��: 5000
    const uint16 �ⱳLV4_TIME_COST = 9;           // ǥ��: 9
    
    const bool �޽���_LOGâ_ǥ�� = false;           // launcher log â�� ���� ���� ǥ��
    
    //---------------------------------------------------------------------------------------
    
    // ���� Ȯ���� �ش� �Ͽ� �ⱳ���� ��� ����
    const bool �ⱳ_COST_��뼳�� = true;
    const int �ⱳ_COST_���Ȯ��  = 20;             // 0~100 ���̰� ���
    
    
    //---------------------------------------------------------------------------------------
    
	class Main
	{
        // ���������� �ⱳ���� �ʱⰪ
        array<array<uint16>> custom_tech_cost = { {�ⱳLV1_GOLD_COST, �ⱳLV1_TP_COST, �ⱳLV1_TIME_COST} ,
                                                  {�ⱳLV2_GOLD_COST, �ⱳLV2_TP_COST, �ⱳLV2_TIME_COST} ,
                                                  {�ⱳLV3_GOLD_COST, �ⱳLV3_TP_COST, �ⱳLV3_TIME_COST} ,
                                                  {�ⱳLV4_GOLD_COST, �ⱳLV4_TP_COST, �ⱳLV4_TIME_COST} };
        // �ⱳ������ (����� Ȱ��)
        array<uint16> tech_cost_gold(�ⱳ_��, 0);
        array<uint16> tech_cost_tp  (�ⱳ_��, 0);
        array<uint16> tech_cost_time(�ⱳ_��, 0);
        
        
        
        Main()
		{
            pk::bind(102, pk::trigger102_t(onGameInit));
            pk::bind(111, pk::trigger111_t(onTurnStart));
            pk::bind(112, pk::trigger112_t(onTurnEnd));
            
            pk::bind(100, pk::trigger100_t(onGameTitle));
        }
        
        //---------------------------------------------------------------------------------------
        
        
        // Ÿ��Ʋ ȭ��
        void onGameTitle()
        {
            onGameInit();
        }
        
            
        // �����ʱ�ȭ �� ���������� ����
        void onGameInit()
        {
            if (pk::is_campaign()) return;
            
            // ���������� ����
            if (�ⱳ_GOLD_COST_���� or �ⱳ_TP_COST_���� or �ⱳ_TIME_COST_����)
            {
                for (int tech_id = 0; tech_id < �ⱳ_��; tech_id++)
                {
                    int tech_lv = tech_id % 4;
                    if (�ⱳ_GOLD_COST_����) change_tech_gold(tech_id, custom_tech_cost[tech_lv][0], false);
                    if (�ⱳ_TP_COST_����)   change_tech_tp  (tech_id, custom_tech_cost[tech_lv][1], false);
                    if (�ⱳ_TIME_COST_����) change_tech_time(tech_id, custom_tech_cost[tech_lv][2], false);
                }
            }
            
            // �ⱳ ������ ���
            backup_tech_cost();
        }
        
        //---------------------------------------------------------------------------------------
        
        // ���� ���� �� �ⱳ ������ ����
        void onTurnEnd(pk::force@ force)
        {
            if (pk::is_campaign()) return;
            
            reset_tech_cost();
        }
        
        // ���� ���� �� �����ϰ� �ⱳ ��� ����
        void onTurnStart(pk::force@ force)
        {
            if (pk::is_campaign()) return;
            
            if (!pk::is_normal_force(force)) return;
            
            if (!�ⱳ_COST_��뼳��) return;
            
            // ���� ���� �ⱳ�� �ִ��� Ȯ��
            int tech_rnd = force.researching_tech;
            if (tech_rnd >= 0) 
            {
                if (force.is_player())
                {
                    string tech_name = pk::decode(pk::get_name(pk::get_tech(tech_rnd)));
                    pk::message_box(pk::encode(pk::format("�� �����ַ� �ߴ���, �̹� \x1b[1x{}\x1b[0x��(��) �����ϰ� �־�����. ������ �� ������.", tech_name)),
                                    pk::get_person(����_�縶��));
                }
                return;
            }
            
            // �ⱳ ��� ����
            if (pk::rand_bool(�ⱳ_COST_���Ȯ��))
            {
                int tech_group = pk::rand(9);   // 9�� �о� �� ���� ����
                int tech_id = get_next_tech_id(force, tech_group);  // ���� �о� �� �̿��� �ܰ��� �ⱳID ��ȯ
                int adv_type = pk::rand(3);     // ����� ��/TP/�Ⱓ �� ���� ����
                
                if (tech_id < 0)
                {
                    if (force.is_player())
                    {
                        pk::array<string> tech_group_name = {"â��","�غ�","�뺴","�⺴","����","�߸�","����","ȭ��","����"}; 
                        string group_name = tech_group_name[tech_group];
                        pk::message_box(pk::encode(pk::format("�� �����ַ� �ߴ���, \x1b[1x{}\x1b[0x �оߴ� �̹� ������ ���Ʊ���. ������ �� ������.", group_name)),
                                        pk::get_person(����_�縶��));
                    }
                    return;
                }
                else
                {
                    string tech_name = pk::decode(pk::get_name(pk::get_tech(tech_id)));
                    string adv_name;
                    
                    int tech_lv = tech_id % 4;
                    switch(adv_type)
                    {
                        case 0: change_tech_gold(tech_id, tech_cost_gold[tech_id], true); adv_name = "��";   break;
                        case 1: change_tech_tp  (tech_id, tech_cost_tp  [tech_id], true); adv_name = "�ⱳ��";   break;
                        case 2: change_tech_time(tech_id, tech_cost_time[tech_id], true); adv_name = "�Ⱓ";  break;
                    }
                    
                    if (force.is_player())
                    {
                        pk::message_box(pk::encode(pk::format("���ø� Ư���� \x1b[1x{}\x1b[0x ������ ��������. \x1b[1x{}\x1b[0x�� �ݸ� ���Գ�. ����.", tech_name, adv_name)),
                                        pk::get_person(����_�縶��));
                    }
                }
            }
        }
        
        
        
        //---------------------------------------------------------------------------------------
        
        void change_tech_gold(int tech_id, uint16 gold_cost, bool advantage)
        {
            pk::tech@ tech = pk::get_tech(tech_id);
            uint16 cost = tech.gold_cost;
            tech.gold_cost = gold_cost / (advantage? 2:1);
            
            if (�ⱳ_GOLD_COST_���� and �޽���_LOGâ_ǥ��) 
                pk::info(pk::format("�ⱳ {} ���ʿ� : {} �� {}", pk::decode(pk::get_name(tech)), cost, gold_cost));
        }
        
        void change_tech_tp(int tech_id, uint16 tp_cost, bool advantage)
        {
            pk::tech@ tech = pk::get_tech(tech_id);
            uint16 cost = tech.tp_cost;
            tech.tp_cost = tp_cost / (advantage? 2:1);
            
            if (�ⱳ_TP_COST_���� and �޽���_LOGâ_ǥ��) 
                pk::info(pk::format("�ⱳ {} �ⱳP�ʿ� : {} �� {}", pk::decode(pk::get_name(tech)), cost, tp_cost));
        }
        
        void change_tech_time(int tech_id, uint16 time_cost, bool advantage)
        {
            pk::tech@ tech = pk::get_tech(tech_id);
            uint16 cost = tech.time_cost;
            tech.time_cost = time_cost / (advantage? 2:1) + (((time_cost % (advantage? 2:1)) == 0)? 0:1);
            
            if (�ⱳ_TIME_COST_���� and �޽���_LOGâ_ǥ��) 
                pk::info(pk::format("�ⱳ {} �����Ⱓ : {} �� {}", pk::decode(pk::get_name(tech)), cost, time_cost));
        }
        
        
        //---------------------------------------------------------------------------------------
        
        
        int get_next_tech_id(pk::force@ force, int tech_group)
        {
            int tech_id = -1;
            for (int tech_lv = 0; tech_lv < 4; tech_lv++)
            {
                int tech_temp = 4 * tech_group + tech_lv;
                
                if (!pk::has_tech(force, tech_temp)) 
                {
                    tech_id = tech_temp;
                    return tech_id;
                }
            }
            return tech_id;
        }
        
        
        void backup_tech_cost()
        {
            for (int tech_id = 0; tech_id < �ⱳ_��; tech_id++)
            {
                pk::tech@ tech = pk::get_tech(tech_id);
                
                tech_cost_gold[tech_id] = tech.gold_cost;
                tech_cost_tp  [tech_id] = tech.tp_cost;
                tech_cost_time[tech_id] = tech.time_cost;
            }
        }
        
        void reset_tech_cost()
        {
            for (int tech_id = 0; tech_id < �ⱳ_��; tech_id++)
            {
                pk::tech@ tech = pk::get_tech(tech_id);
                
                tech.gold_cost = tech_cost_gold[tech_id];
                tech.tp_cost   = tech_cost_tp  [tech_id];
                tech.time_cost = tech_cost_time[tech_id];
            }
        }
        
        //---------------------------------------------------------------------------------------
        
	}

	Main main;
}

