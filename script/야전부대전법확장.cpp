/*
@������: �⸶å��
@Update: '19.3.2   / ��������: �ⱳ���߿� ���� ������ �߰����� �������
@Update: '19.5.4   / ���泻��: Ÿ��Ʋȭ�� �ʱ�ȭ ���� �߰�

*/

namespace �����δ�����Ȯ��
{
    //---------------------------------------------------------------------------------------
    // ���� ����
    const bool �����δ�����_�ⱳ���� = true;  // �ⱳ�� ���� ������ �߰����� ������� (��������, �������� ��밡��)
    
    const bool �����δ�����_�������� = true;  // ���� & �����ⱳ ���߽� ���������� �ļ� ���� �߰�
    const bool �����δ�����_�������� = true;  // �����ⱳ ���� �� ���������� ������ �����߰�
    
    
    //---------------------------------------------------------------------------------------
    
    
	class Main
	{
        
        Main()
		{
            pk::bind(102, pk::trigger102_t(onGameInit));
            pk::bind(111, pk::trigger111_t(onTurnStart));
            pk::bind(112, pk::trigger112_t(onTurnEnd));
            
            pk::bind(100, pk::trigger100_t(onGameTitle));
        }
        
        //---------------------------------------------------------------------------------------
        
        // ��ũ��Ʈ ������ ���� (��������)
        pk::array<bool> â������(����_��, false);
        pk::array<bool> �غ�����(����_��, false);
        pk::array<bool> �뺴����(����_��, false);
        pk::array<bool> �⺴����(����_��, false);
        pk::array<bool> ��������(����_��, false);
        pk::array<bool> �������(����_��, false);
        pk::array<bool> ��������(����_��, false);
        pk::array<bool> ��������(����_��, false);
        pk::array<bool> �ְ�����(����_��, false);
        pk::array<bool> ��������(����_��, false);
        pk::array<bool> ��������(����_��, false);

        //---------------------------------------------------------------------------------------
        
        // ���� �ʱ�ȭ
        void onGameInit()
        {
            change_tactics_name();
            
            pk::force@ force = pk::get_force(pk::get_current_turn_force_id());
            
            onTurnStart(force);     // �� ���� �Լ� ����
        }
        
        // ���� ���� �� : ������ ���������� ���, ���� ���ǿ� ���� ������ ����������
        void onTurnStart(pk::force@ force)
        {
            reset_tactics_info();   // �ʱ�ȭ
            //backup_tactics_info();  // ���
            
            if (�����δ�����_�ⱳ����)
                custom_tech_tactics(force); // Ŀ���� �ⱳ���� ����
        }
        
        // ���� ���� �� ������ ���������� ����
        void onTurnEnd(pk::force@ force)
        {
            reset_tactics_info();   // �ʱ�ȭ
        }
        
        
        // Ÿ��Ʋ ȭ��
        void onGameTitle()
        {
            backup_tactics_info();  // ���
        }
        
        //---------------------------------------------------------------------------------------
        
        // ���� ��Ī ���� �Լ�
        void change_tactics_name()
        {
            pk::get_tactics(����_����ȭ��).name = pk::encode("����ȭ��");
        }
        
        //---------------------------------------------------------------------------------------
        
        // Ŀ���� �ⱳ���� ���� �Լ�
        void custom_tech_tactics(pk::force@ force)
        {
            if (!pk::is_normal_force(force)) return;
            
            // �����ⱳ : Ÿ���� ���� ��밡��
            if (�����δ�����_��������)
            {
                // ����â�� : Ⱦġ ��밡��
                if (pk::has_tech(force, �ⱳ_����â��))
                    pk::get_equipment(����_â).tactics[����_Ⱦġ] = true;
                
                // �����غ� : ����÷ ��밡��
                if (pk::has_tech(force, �ⱳ_�����غ�))
                    pk::get_equipment(����_��).tactics[����_����÷] = true;
                    
                // �����뺴 : ����ȭ�� ��밡��
                if (pk::has_tech(force, �ⱳ_�����뺴))
                    pk::get_equipment(����_��).tactics[����_����ȭ��] = true;
                    
                // �����⺴ : ȭ�� ��밡��
                if (pk::has_tech(force, �ⱳ_�����⺴))
                    pk::get_equipment(����_����).tactics[����_ȭ��] = true;
            }
        
            // �ⱳ_���� & �����ⱳ : �����ļ� ��밡��
            if (�����δ�����_�������� and pk::has_tech(force, �ⱳ_����))
            {
                if (pk::has_tech(force, �ⱳ_����â��))
                    pk::get_equipment(����_â).tactics[����_�����ļ�] = true;
                
                if (pk::has_tech(force, �ⱳ_�����غ�))
                    pk::get_equipment(����_��).tactics[����_�����ļ�] = true;
                
                if (pk::has_tech(force, �ⱳ_�����뺴))
                    pk::get_equipment(����_��).tactics[����_�����ļ�] = true;
                
                if (pk::has_tech(force, �ⱳ_�����⺴))
                    pk::get_equipment(����_����).tactics[����_�����ļ�] = true;
            }
            
        }
        
        
        //---------------------------------------------------------------------------------------
        
        // â�س�� ���� ���� ���
        void backup_tactics_info()
        {
            for (int i = 0; i < ����_��; i++)
            {
                â������[i] = pk::get_equipment(����_â).tactics[i];
                �غ�����[i] = pk::get_equipment(����_��).tactics[i];
                �뺴����[i] = pk::get_equipment(����_��).tactics[i];
                �⺴����[i] = pk::get_equipment(����_����).tactics[i];
                ��������[i] = pk::get_equipment(����_����).tactics[i];
                �������[i] = pk::get_equipment(����_���).tactics[i];
                ��������[i] = pk::get_equipment(����_����).tactics[i];
                ��������[i] = pk::get_equipment(����_����).tactics[i];
                �ְ�����[i] = pk::get_equipment(����_�ְ�).tactics[i];
                ��������[i] = pk::get_equipment(����_����).tactics[i];
                ��������[i] = pk::get_equipment(����_����).tactics[i];
            }
        }
        
        // â�س�� ���� ���� ��������
        void reset_tactics_info()
        {
            for (int i = 0; i < ����_��; i++)
            {
                pk::get_equipment(����_â).tactics[i]  = â������[i];
                pk::get_equipment(����_��).tactics[i]  = �غ�����[i];
                pk::get_equipment(����_��).tactics[i]  = �뺴����[i];
                pk::get_equipment(����_����).tactics[i] = �⺴����[i];
                pk::get_equipment(����_����).tactics[i] = ��������[i];
                pk::get_equipment(����_���).tactics[i] = �������[i];
                pk::get_equipment(����_����).tactics[i] = ��������[i];
                pk::get_equipment(����_����).tactics[i] = ��������[i];
                pk::get_equipment(����_�ְ�).tactics[i] = �ְ�����[i];
                pk::get_equipment(����_����).tactics[i] = ��������[i];
                pk::get_equipment(����_����).tactics[i] = ��������[i];
            }
        }
        
        //---------------------------------------------------------------------------------------
    }
    
	Main main;
}

