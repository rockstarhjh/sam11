/*
�� ���ǻ��� : �� ��ũ��Ʈ ���� �� ����.xml ���� ����� �Ϻ� ���/���� ���� ������ ���õ˴ϴ�.

@������: �⸶å��
@Update: '18.12.22   / ��������: ���� �ֺ��� [����_��]�� [����_����]�� [����_����]���� �ϰ� ������
@Update: '18.12.23   / ���泻��: [����_����] �� �ִ� �δ� �����ػ� �߰�
@Update: '19.1.2     / ���泻��: ���溰 ������ ���� �߰�, �������ֺ� �������� [����_����]���� �ϰ� ���� 
@Update: '19.2.7     / ���泻��: [����_����] �� �ִ� �ǹ� ����ö�� �߰� 
@Update: '19.2.15    / ���泻��: ������ ���� ������ǥ ���� (ĭ �𼭸����� �����) 
@Update: '20.8.29    / ���泻��: ķ���ο����� Ŀ���Ҽ��� ��Ȱ��ȭ
*/

namespace �����̵�����
{
    //---------------------------------------------------------------------------------------
    // ���� ���� (true = on, false = off)
    
    const bool �����ֺ�����_���漳�� = true;     // ���� �ֺ��� [����_��]�� [����_����]�� [����_����]���� ������
    
    // �����ֺ�����_���漳��=true �� �� :
    const bool �����ֺ�����_���漳�� = true;     // ���� �ֺ��� [����_��]�� [����_����]�� [����_����]���� ������
    const bool �����ֺ�����_���漳�� = true;     // ���� �ֺ��� [����_��]�� [����_����]�� [����_����]���� ������
    const bool �ױ��ֺ�����_���漳�� = true;     // ���� �ֺ��� [����_��]�� [����_����]�� [����_����]���� ������
    
    const int  �����ֺ�����_������� = 7;
    const int  �����ֺ�����_������� = 5;
    const int  �ױ��ֺ�����_������� = 5;
    
    //---------------------------------------------------------------------------------------
    const bool ��������_�δ��ػ꼳�� = true;    // ����: true �� ���� ���� (����� ������ �δ밡 �̵� �� ƨ��)
    //---------------------------------------------------------------------------------------
    
    const bool ����������_���漳�� = true;     // ���� ���̰� ���� �̻��� [����_��]�� [����_����]���� ������
    const int  ����������_���س���_���˳��� = 200;      // ���ǻ��� : 180 ���� ���� �Ұ�
    const int  ����������_���س���_��Ÿ���� = 130;      // ���ǻ��� : 100 ���� ���� �Ұ�
    
    //---------------------------------------------------------------------------------------
    
    const bool �������ֺ�_���漳�� = true;     // ������ �ֺ� �����溸�� �� ���� �������� [����_��]�� [����_����]���� ����   
    
    //---------------------------------------------------------------------------------------
    
	class Main
	{
        
        Main()
		{
            pk::bind(102, pk::trigger102_t(onGameInit));
            pk::bind(112, pk::trigger112_t(onTurnEnd));
        }
        
        void onGameInit()
        {
            if (!pk::is_campaign())
            {
                if (�����ֺ�����_���漳��)
                {
                    if (�����ֺ�����_���漳��)
                    {
                        for (int num = �ǹ�_���ý���; num < �ǹ�_���ó�; num++)
                        {
                            disable_terrain_around_building(num, �����ֺ�����_�������);
                        }
                    }
                    
                    if (�����ֺ�����_���漳��)
                    {
                        for (int num = �ǹ�_��������; num < �ǹ�_������; num++)
                        {
                            disable_terrain_around_building(num, �����ֺ�����_�������);
                        }
                    } 
                    
                    if (�ױ��ֺ�����_���漳��)
                    {
                        for (int num = �ǹ�_�ױ�����; num < �ǹ�_�ױ���; num++)
                        {
                            disable_terrain_around_building(num, �ױ��ֺ�����_�������);
                        }
                    }   
                }
                
                if (����������_���漳��)
                {
                    disable_terrain_high_pos();
                }
                
                if (�������ֺ�_���漳��)
                {
                    disable_terrain_nearby_cliff();
                }
            }
            remove_invalid_object();
            
        }
        
        
        void onTurnEnd(pk::force@ force)
        {
            if (pk::is_campaign()) return;
            remove_invalid_object();
        }
        
        //---------------------------------------------------------------------------
        
        void disable_terrain_around_building(int building_id, int around_range)
        {
            pk::building@ building = pk::get_building(building_id);
            pk::array<pk::point> range = pk::range(building.pos, 1, around_range);
            for (int j = 0; j < int(range.length); j++)
            {
                pk::hex@ hex = pk::get_hex(range[j]);
                if (hex.terrain == ����_�� or hex.terrain == ����_����)
                {
                    hex.terrain = ����_����;
                }
            }
            
        }
        
        void disable_terrain_high_pos()
        {
            for (int pos_x = 0; pos_x < 200; pos_x++)
            {
                for (int pos_y = 0; pos_y < 200; pos_y++)
                {
                    pk::point pos;
                    pos.x = pos_x;
                    pos.y = pos_y;
                    
                    pk::hex@ hex = pk::get_hex(pos);
                    
                    // ���溰 ���س���
                    int region_id = pk::get_region_id(pk::get_city(pk::get_city_id(pos)));
                    int ref_height = 0;
                    if (region_id >= ����_����)
                        ref_height = pk::max(180, ����������_���س���_���˳���);
                    else
                        ref_height = pk::max(100, ����������_���س���_��Ÿ����);
                    
                    // �ش� ��ǥ ���� ����
                    int pos_height = pk::get_height_map(pk::hex_pos_to_height_map_pos(pos) + 2).height;
                    if (hex.terrain == ����_�� and pos_height >= ref_height)
                    {
                        hex.terrain = ����_����;
                    }
                }
            }
        }
        
        void disable_terrain_nearby_cliff()
        {
            for (int pos_x = 0; pos_x < 200; pos_x++)
            {
                for (int pos_y = 0; pos_y < 200; pos_y++)
                {
                    pk::point pos;
                    pos.x = pos_x;
                    pos.y = pos_y;
                    
                    pk::hex@ hex = pk::get_hex(pos);
                    if (hex.terrain == ����_������)
                    {
                        int pos_height = pk::get_height_map(pk::hex_pos_to_height_map_pos(pos) + 2).height;
                        for (int dir = 0; dir < ����_��; dir++)
                        {
                            pk::point neighbor_pos = pk::get_neighbor_pos(pos, dir);
                            if (pk::is_valid_pos(neighbor_pos))
                            {
                                pk::hex@ neighbor_hex = pk::get_hex(neighbor_pos);
                                int neighbor_height = pk::get_height_map(pk::hex_pos_to_height_map_pos(neighbor_pos) + 2).height;
                                if (neighbor_hex.terrain == ����_�� and (pos_height >= neighbor_height))
                                {
                                    neighbor_hex.terrain = ����_����;
                                }
                            }
                        }
                    }
                }
            }
        }
        
        //---------------------------------------------------------------------------
        
        void remove_invalid_object()
        {
            for (int pos_x = 0; pos_x < 200; pos_x++)
            {
                for (int pos_y = 0; pos_y < 200; pos_y++)
                {
                    pk::point pos;
                    pos.x = pos_x;
                    pos.y = pos_y;
                    
                    pk::hex@ hex = pk::get_hex(pos);
                    if (hex.terrain == ����_���� and hex.has_unit)
                        pk::kill(pk::get_unit(pos));
                    
                    if (hex.terrain == ����_���� and hex.has_building)
                        pk::kill(pk::get_building(pos));
                }
            }
            
        }
        
        
        
	}

	Main main;
}

