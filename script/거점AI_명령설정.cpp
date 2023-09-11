/*
// ������: �ﵵī�� �⸶å��
// Update: '20.10.21   / ��������: ���� AI ��ɼ���, [255 ���� AI �ൿ ����.cpp] �� ���� ��� ���� �� ��ũ��Ʈ ����
*/

namespace ����AI_��ɼ���
{
    //---------------------------------------------------------------------------------------
    // ���� ���� (true = on, false = off)
    const bool �÷��̾�_���ӱ���_�����̵�_���缳������ = true;   // ���ӱ��� ���� �޴��� ���� �㰡/������ ���� �̵�/��ȯ ��� �����ϱ�
    const bool �÷��̾�_���ӱ���_�����̵�_�׻�������� = true;   // ���缳������=false �� ��쿡�� ����, ���ӱ����� �̵�/��ȯ ��� ������ ����
    
    const bool AI����_�����������_���±��ؼ��� = true;        // ���� ������ ���غ��� �̸��� �� ��� �����δ� ��� ��������
    const int  AI����_�����������_���±��ذ�_���ð��� = 5000;  // �������� ������ ���ذ� �̸��� �� ��� ��� ����������
    const int  AI����_�����������_���±��ذ�_�����ױ� = 3000;  // �������� ������ ���ذ� �̸��� �� ��� ��� ����������
    
    const bool AI����_������������_���±��ؼ��� = true;        // ���� ������ ���غ��� �̸��� �� ��� �����δ� ���� ��������
    const int  AI����_������������_���±��ذ�_���ð��� = 5000;  // �������� ������ ���ذ� �̸��� �� ��� ���� ����������
    const int  AI����_������������_���±��ذ�_�����ױ� = 3000;  // �������� ������ ���ذ� �̸��� �� ��� ���� ����������
    
    //---------------------------------------------------------------------------------------
    
	class Main
	{
        
		Main()
		{
			@prev_callback_256 = cast<pk::func256_t@>(pk::get_func(256));
			pk::reset_func(256);
			pk::set_func(256, pk::func256_t(callback_256));
            
            @prev_callback_257 = cast<pk::func257_t@>(pk::get_func(257));
			pk::reset_func(257);
			pk::set_func(257, pk::func257_t(callback_257));
            
            pk::bind(111, pk::trigger111_t(onTurnStart));
		}

        pk::func256_t@ prev_callback_256;
        pk::func257_t@ prev_callback_257;
        int temp_ap;
        
        array<array<bool>> arr_cmd_canceled(�ǹ�_������, array<bool>(28, false));
        array<int> arr_building_ap(�ǹ�_������, 0);
        
        //---------------------------------------------------------------------------------------
        
        // 256�Լ� : AI ��ɽ��� �� ��������
		void callback_256(pk::ai_context@ context, pk::building@ building, int cmd)
		{
            if (!pk::is_campaign() and building !is null and building.get_id() < �ǹ�_������)
            {
                int base_id = building.get_id();
                pk::district@ district = pk::get_district(building.get_district_id());
                arr_building_ap[base_id] = context.ap;  // �ൿ�� ����
                
                // �÷��̾� ���ӱ��� �����̵����� ����
                if ((cmd == ����AI_�̵� or cmd == ����AI_��ȯ) and !arr_cmd_canceled[base_id][cmd])
                {
                    if (building.is_player() and !pk::is_player_controlled(building))
                    {
                        if (�÷��̾�_���ӱ���_�����̵�_���缳������ and !district.personnel)
                            cancel_cmd_256(context, building, cmd);   // ���ӱ��� ������� �� �����̵�/��ȯ ���
                        else if (�÷��̾�_���ӱ���_�����̵�_�׻��������) 
                            cancel_cmd_256(context, building, cmd);
                    }
                }
                // ���� ��� ���� ��������
                if (cmd == ����AI_��� and !arr_cmd_canceled[base_id][cmd])
                {
                    if (AI����_�����������_���±��ؼ���)
                    {
                        int min_troops;
                        if (base_id < �ǹ�_���ó�)
                            min_troops = pk::max(0, AI����_�����������_���±��ذ�_���ð���);
                        else if (�ǹ�_�������� <= base_id and base_id < �ǹ�_�ױ���)
                            min_troops = pk::max(0, AI����_�����������_���±��ذ�_�����ױ�);
                        
                        if (pk::get_troops(building) < min_troops) 
                            cancel_cmd_256(context, building, cmd);
                    }
                }
                // ���� ���� ���� ��������
                if (cmd == ����AI_���� and !arr_cmd_canceled[base_id][cmd])
                {
                    if (AI����_������������_���±��ؼ���)
                    {
                        int min_troops;
                        if (base_id < �ǹ�_���ó�)
                            min_troops = pk::max(0, AI����_������������_���±��ذ�_���ð���);
                        else if (�ǹ�_�������� <= base_id and base_id < �ǹ�_�ױ���)
                            min_troops = pk::max(0, AI����_������������_���±��ذ�_�����ױ�);
                        
                        if (pk::get_troops(building) < min_troops) 
                            cancel_cmd_256(context, building, cmd);
                    }
                }
            }
            
			if (prev_callback_256 !is null)
				prev_callback_256(context, building, cmd);
		}

        //---------------------------------------------------------------------------------------
        
        // 257�Լ� : AI ��ɽ��� �� ��������
		void callback_257(pk::ai_context@ context, pk::building@ building, int cmd)
		{
            int base_id = building.get_id();
            
            // ��� ��ҿϷ� �� �ൿ�� ����ó��
            if (arr_cmd_canceled[base_id][cmd] and context.ap == 0)
            {
                context.ap = temp_ap;   // �ൿ�� ����
                arr_cmd_canceled[base_id][cmd] = false;
                
                if (����׸��) pk::info(pk::format("---����AI: {}, �ൿ��({}), {} ��ҿϷ�", pk::decode(pk::get_name(building)), context.ap, get_cmd_info(cmd) ));
            }
            
            // �ൿ�� ������ ���, ��ɽ����� ������ ����
            if (context.ap < arr_building_ap[base_id])
            {
                if (����׸��) pk::info(pk::format("---����AI: {}, �ൿ��({}��{}), {} ����Ϸ�", pk::decode(pk::get_name(building)), arr_building_ap[base_id], context.ap , get_cmd_info(cmd) ));
            }
            
			if (prev_callback_257 !is null)
				prev_callback_257(context, building, cmd);
		}
        
        
        // ��� ��Ҹ� ���� �ൿ�� �������� �Լ�
        void cancel_cmd_256(pk::ai_context@ context, pk::building@ building, int cmd)
        {
            temp_ap = context.ap;
            context.ap = 0;     // �ൿ�� ��� �� 0 ���� ó��
            
            int base_id = building.get_id();
            arr_cmd_canceled[base_id][cmd] = true;
            
            if (����׸��) pk::info(pk::format("---����AI: {}, �ൿ��({}), {} ��Ҽ���", pk::decode(pk::get_name(building)), temp_ap, get_cmd_info(cmd) ));
        }
        
        // �Ͻ��� �� ��ɱ������� ���� �ʱ�ȭ
        void onTurnStart(pk::force@ force)
        {
            if (pk::is_campaign()) return;
            
            for (int i = 0; i < �ǹ�_������; i++)
            {
                for (int j = 0; j < 28; j++)
                    arr_cmd_canceled[i][j] = false;
            }
            
        }
        
        //---------------------------------------------------------------------------------------
        
        string get_cmd_info(int cmd)
        {
            string str_cmd;
            switch(cmd)
            {
                case 1  : str_cmd = "����"          ; break;
                case 2  : str_cmd = "¡��"          ; break;
                case 3  : str_cmd = "����"          ; break;
                case 4  : str_cmd = "����"          ; break;
                case 5  : str_cmd = "�ŷ�"          ; break;
                case 6  : str_cmd = "�Ʒ�"          ; break;
                case 7  : str_cmd = "���"          ; break;
                case 8  : str_cmd = "����"          ; break;
                case 9  : str_cmd = "��ġ"          ; break;
                case 10 : str_cmd = "��������"       ; break;
                case 11 : str_cmd = "���ü���"       ; break;
                case 12 : str_cmd = "�̵�"          ; break;
                case 13 : str_cmd = "��ȯ"          ; break;
                case 14 : str_cmd = "����Ž��"       ; break;
                case 15 : str_cmd = "������"       ; break;
                case 16 : str_cmd = "����"          ; break;
                case 17 : str_cmd = "��ȣ���"       ; break;
                case 18 : str_cmd = "��ȣź��"       ; break;
                case 19 : str_cmd = "������"       ; break;
                case 20 : str_cmd = "Ÿ���¹�����"   ; break;
                case 21 : str_cmd = "ö��"          ; break;
                case 22 : str_cmd = "�跫"          ; break;
                case 23 : str_cmd = "�ּ�����Ž��"    ; break;
                case 24 : str_cmd = "�ּҹ�����"    ; break;
                case 25 : str_cmd = "�ּ�Ÿ���¹�����"; break;
                case 26 : str_cmd = "�ŷ�2"         ; break;
                case 27 : str_cmd = "����պ�"       ; break;
            }
            return str_cmd;
        }
        
        //---------------------------------------------------------------------------------------

        bool ����׸�� = false;

	}

	Main main;
}

