/*
@ ������: �⸶å��
@ UPDATE: '18.11.4   /  ��������: �跫_����/����/��/���/ȸ��, �δ��ػ�/����
@ UPDATE: '18.11.8   /  ���泻��: �跫_�弳 �߰�, �跫��� Ư������ �ݿ�
@ UPDATE: '18.11.14  /  ���泻��: �Է�_��� �߰�, ���౺�߰�
@ UPDATE: '18.11.24  /  ���泻��: �跫_���� ����(�弳����)+�����߰�, �跫_��� ���� �߰�, �δ��ػ�/���� ���డ�� ���±��� ����, NPC�δ� ��������� �߰�
@ UPDATE: '18.11.25  /  ���泻��: ��ũ��Ʈ ��������, �δ뼳�� ���װ����� ���Ͽ� trigger ���ä��
@ UPDATE: '18.11.30  /  ���泻��: �跫_��� ���׹������� �߰�, �δ�_�ػ� ���ذ� ��������
@ UPDATE: '18.12.3   /  ���泻��: �跫_��� ��ĭ���� ��ǥ�δ� �˻� ��������, �跫_���� �ߵ����� ���� �� �ҷ����� ���� �� �ʱ�ȭ �߰�
@ UPDATE: '18.12.12  /  ���泻��: �跫_��� ��¼Ҹ� ����, shift+��Ŭ�� �޴� �����ൿ ���� ���� ����, �δ�_�ػ�/���� �ֺ����� Ȯ������ �߰�
@ UPDATE: '18.12.21  /  ���泻��: �δ�_���� �������, �跫_���� �߰�
@ UPDATE: '18.12.23  /  ���泻��: �δ�_�ػ�/���� �������� �˻��Լ� ���� ����
@ UPDATE: '18.12.30  /  ���泻��: �跫_���� Ư��_�� ��� ����, �δ�_���� �߰� (���庯����), �跫_���� ���ü� Ż�� ��� �߰�
*/

namespace �����δ�޴�
{
    
    //---------------------------------------------------------------------------------------
    // ���� ���� (true = on, false = off)
    
    // �跫 �޴� �߰����� ����
    const bool �޴�_�跫_���  = true;    // Custom �跫 �� ���� Master ���� (false �� ��� �跫 off)
    const bool �跫_���_���  = true;    // ����δ��� �α� �� �δ� ��� : Ư��_�޽� ��� ('18.11.13)
    
    const bool �跫_����_���  = true;    // �� �¼� �����Ͽ� �⼺ ����, ���ߵ� �δ��� ��� ���� �� ���� ���� ('18.11.9)
    const bool �跫_����_�������� = true;  //  �ߵ�/���ߵ� �δ� �� ������ ���� ('18.11.24)
    const bool �跫_����_�������� = true;  //  �ߵ�/���ߵ� �δ� �� ������ ���� ���θ� Ȯ���ϱ�
    
    const bool �跫_����_���  = true;    // �� �ǹ� ������ ���� ('18.11.9)
    const bool �跫_����_Ż��  = true;    // �� �ü��� ���� ���� ���� �� �ü� Ż�� ('18.12.26)
    
    const bool �跫_����_���  = true;    // ����������� ���� ���� ('18.12.21)
    
    const bool �跫_��_���  = true;    // �Ʊ� 1�δ� ��� ȸ�� ('18.11.6)
    const bool �跫_���_��� = true;    // �Ʊ� �����δ� ��� ȸ�� ('18.11.6)
    const bool �跫_ȸ��_���  = true;    // �Ʊ� �δ� ���ൿ : ���� �Ǵ� ���� ��� ���� ('18.11.6)
    
    // �δ� �޴� �߰����� ����
    const bool �޴�_�δ�_���  = true;    // Custom �δ�޴��� ���� Master ���� (false �� ��� �δ�޴� off)
    const bool �δ�_�ػ�_���  = true;    // 2õ�� �̻� �δ� ���� �ػ� ('18.11.9)
    const bool �δ�_����_���  = true;    // ���� �����δ� ���� �� ���� �ΰ� ('18.11.6)
    const bool �δ�_ȸ��_���  = true;    // ���� �Һ��Ͽ� ���� ȸ�� ('18.11.6)
    const bool �δ�_����_���  = true;    // �δ��� ���� ���� ('18.12.26)
    
    // ���౺ �޴� ����
    const bool �޴�_���౺_���  = true;   // ��� �߰� �Һ��Ͽ� �߰� �̵� �ǽ� ('18.11.13)
    
    // �跫�� ���� Ư�� �ɼ�
    const bool �跫_Ư��_����  = true;        // �跫�� ���� Ư�� ���� ���
    const bool ����_�ݰ�_����  = true;        // true= 50% �Һ�, false = ������ 1 �Һ�
    const bool �跫_����_����  = true;        // ���¼��� ���� �跫 �Һ��� ���� ����
    
    // ���౺ ���� ����
    const int ENERGY_MIN_���౺ = 50;       // ���౺�� �����ϱ� ���� �ּ� ���
    const float MOVEMENT_���౺  = 0.6f;    // [���౺_�̵���]/[�δ�_�̵���] ���� 
    
    // �跫 ���� ����
	const int ENERGY_COST_��� = 15;        
	const int ENERGY_COST_���� = 40;        
	const int ENERGY_COST_���� = 15;
	const int ENERGY_COST_���߼��� = 15;
	const int ENERGY_COST_�ı����� = 15;
	const int CHANCE_����Ż��Ȯ�� = 20;    // ���� �ü��� ���� ���� ���� �� �ü� Ż�� Ȯ�� (0 ~ 100 ����)
	const int ENERGY_COST_��  = 10;
	const int ENERGY_COST_��� = 20;
	const int ENERGY_COST_ȸ�� = 30;
    // �δ� ���� ����
	const int GOLD_COST_����  = 500;   // ���� �����ϴ� ����    
	const int GOLD_COST_ȸ��  = 300;
    
    //---------------------------------------------------------------------------------------

    
	class Main
	{
		Main()
		{
            // �δ� ����ġ ȹ�� Ʈ����
            unit_debate_list.clear();
            pk::bind(173, pk::trigger173_t(onUnitExpAdd)); 
            pk::bind(111, pk::trigger111_t(onTurnStart)); 
            pk::bind(112, pk::trigger112_t(onTurnEnd)); 
            pk::bind(102, pk::trigger102_t(onGameInit));
            
            // �跫 �޴� �߰�
            add_menu_stragety();
            
            // �δ� �޴� �߰�
            add_menu_unit_order();
            
        }
        
        pk::unit@ src_unit;
        pk::unit@ dst_unit;
        pk::point src_pos_;
        pk::point dst_pos_;
        
        pk::unit@ src_unit_debate;
        pk::unit@ dst_unit_debate;
        
        pk::list<pk::unit@> unit_debate_list;
        int debate_result;
    
        void add_menu_stragety()
        {
            //-------------------------------------------------------------
            if (�޴�_�跫_���)
            {
                // ���� : ����������� ���� ����
                if (�跫_����_���)
                {
                    pk::menu_item �跫_����;
                    �跫_����.menu = 115;
                    �跫_����.init = pk::unit_menu_item_init_t(init);
                    �跫_����.get_text = pk::menu_item_get_text_t(getText_�跫_����);
                    �跫_����.get_desc = pk::menu_item_get_desc_t(getDesc_�跫_����);
                    �跫_����.is_visible = pk::menu_item_is_visible_t(isVisible_�跫_����);
                    �跫_����.is_enabled = pk::menu_item_is_enabled_t(isEnabled_�跫_����);
                    �跫_����.get_targets = pk::unit_menu_item_get_targets_t(getTargets_�跫_����);
                    �跫_����.get_chance = pk::unit_menu_item_get_chance_t(getChance_����);
                    �跫_����.handler = pk::unit_menu_item_handler_t(handler_�跫_����);
                    pk::add_menu_item(�跫_����);
                }
                
                // ��� : ��ó�� ���δ븦 ��� ����
                if (�跫_���_���)
                {
                    pk::menu_item �跫_���;
                    �跫_���.menu = 115;
                    �跫_���.init = pk::unit_menu_item_init_t(init);
                    �跫_���.get_text = pk::menu_item_get_text_t(getText_�跫_���);
                    �跫_���.get_desc = pk::menu_item_get_desc_t(getDesc_�跫_���);
                    �跫_���.is_visible = pk::menu_item_is_visible_t(isVisible_�跫_���);
                    �跫_���.is_enabled = pk::menu_item_is_enabled_t(isEnabled_�跫_���);
                    �跫_���.get_targets = pk::unit_menu_item_get_targets_t(getTargets_�跫_���);
                    �跫_���.get_chance = pk::unit_menu_item_get_chance_t(getChance_100);
                    �跫_���.handler = pk::unit_menu_item_handler_t(handler_�跫_���);
                    pk::add_menu_item(�跫_���);
                }
                
                // ���� : �� ���� �¼��� �⼺�� ����
                if (�跫_����_���)
                {
                    pk::menu_item �跫_����;
                    �跫_����.menu = 115;
                    �跫_����.init = pk::unit_menu_item_init_t(init);
                    �跫_����.get_text = pk::menu_item_get_text_t(getText_�跫_����);
                    �跫_����.get_desc = pk::menu_item_get_desc_t(getDesc_�跫_����);
                    �跫_����.is_visible = pk::menu_item_is_visible_t(isVisible_�跫_����);
                    �跫_����.is_enabled = pk::menu_item_is_enabled_t(isEnabled_�跫_����);
                    �跫_����.get_targets = pk::unit_menu_item_get_targets_t(getTargets_�跫_����);
                    �跫_����.get_chance = pk::unit_menu_item_get_chance_t(getChance_����);
                    �跫_����.handler = pk::unit_menu_item_handler_t(handler_�跫_����);
                    pk::add_menu_item(�跫_����);
                }
                
                // �ı� : �� ���� ������ �ı�
                if (�跫_����_���)
                {
                    pk::menu_item �跫_�ı�����;
                    �跫_�ı�����.menu = 115;
                    �跫_�ı�����.init = pk::unit_menu_item_init_t(init);
                    �跫_�ı�����.get_text = pk::menu_item_get_text_t(getText_�跫_�ı�����);
                    �跫_�ı�����.get_desc = pk::menu_item_get_desc_t(getDesc_�跫_�ı�����);
                    �跫_�ı�����.is_visible = pk::menu_item_is_visible_t(isVisible_�跫_�ı�����);
                    �跫_�ı�����.is_enabled = pk::menu_item_is_enabled_t(isEnabled_�跫_�ı�����);
                    �跫_�ı�����.get_targets = pk::unit_menu_item_get_targets_t(getTargets_�跫_�ı�����);
                    �跫_�ı�����.get_chance = pk::unit_menu_item_get_chance_t(getChance_�ı�����);
                    �跫_�ı�����.handler = pk::unit_menu_item_handler_t(handler_�跫_�ı�����);
                    pk::add_menu_item(�跫_�ı�����);
                }
                
                // �� : 1�δ� ��� ȸ��
                if (�跫_��_���)
                {
                    pk::menu_item �跫_��;
                    �跫_��.menu = 115;
                    �跫_��.init = pk::unit_menu_item_init_t(init);
                    �跫_��.get_text = pk::menu_item_get_text_t(getText_�跫_��);
                    �跫_��.get_desc = pk::menu_item_get_desc_t(getDesc_�跫_��);
                    �跫_��.is_visible = pk::menu_item_is_visible_t(isVisible_�跫_��);
                    �跫_��.is_enabled = pk::menu_item_is_enabled_t(isEnabled_�跫_��);
                    �跫_��.get_targets = pk::unit_menu_item_get_targets_t(getTargets_�跫_��);
                    �跫_��.get_chance = pk::unit_menu_item_get_chance_t(getChance_100);
                    �跫_��.handler = pk::unit_menu_item_handler_t(handler_�跫_��);
                    pk::add_menu_item(�跫_��);
                }
                
                // ��� : ���+�����δ� ��� ȸ��
                if (�跫_���_���)
                {
                    pk::menu_item �跫_���;
                    �跫_���.menu = 115;
                    �跫_���.init = pk::unit_menu_item_init_t(init);
                    �跫_���.get_text = pk::menu_item_get_text_t(getText_�跫_���);
                    �跫_���.get_desc = pk::menu_item_get_desc_t(getDesc_�跫_���);
                    �跫_���.is_visible = pk::menu_item_is_visible_t(isVisible_�跫_���);
                    �跫_���.is_enabled = pk::menu_item_is_enabled_t(isEnabled_�跫_���);
                    �跫_���.get_targets = pk::unit_menu_item_get_targets_t(getTargets_�跫_���);
                    �跫_���.get_chance = pk::unit_menu_item_get_chance_t(getChance_100);
                    �跫_���.handler = pk::unit_menu_item_handler_t(handler_�跫_���);
                    pk::add_menu_item(�跫_���);
                }
                  
                // ȸ�� : ��� ���� ����Ͽ� �ൿ�Ϸ� �Ʊ��δ� ���ൿ
                if (�跫_ȸ��_���)
                {
                    pk::menu_item �跫_ȸ��;
                    �跫_ȸ��.menu = 115;
                    �跫_ȸ��.init = pk::unit_menu_item_init_t(init);
                    �跫_ȸ��.get_text = pk::menu_item_get_text_t(getText_�跫_ȸ��);
                    �跫_ȸ��.get_desc = pk::menu_item_get_desc_t(getDesc_�跫_ȸ��);
                    �跫_ȸ��.is_visible = pk::menu_item_is_visible_t(isVisible_�跫_ȸ��);
                    �跫_ȸ��.is_enabled = pk::menu_item_is_enabled_t(isEnabled_�跫_ȸ��);
                    �跫_ȸ��.get_targets = pk::unit_menu_item_get_targets_t(getTargets_�跫_ȸ��);
                    �跫_ȸ��.get_chance = pk::unit_menu_item_get_chance_t(getChance_100);
                    �跫_ȸ��.handler = pk::unit_menu_item_handler_t(handler_�跫_ȸ��);
                    pk::add_menu_item(�跫_ȸ��);
                }
            }
        }
            
        void add_menu_unit_order()
        {
            //-------------------------------------------------------------
            // ���౺ : ����� �Һ��Ͽ� �߰� �̵�
            if (�޴�_���౺_���)
            {
                pk::menu_item �޴�_���౺;
                �޴�_���౺.menu = 1;
                �޴�_���౺.init = pk::unit_menu_item_init_t(init);
                �޴�_���౺.get_text = pk::menu_item_get_text_t(getText_�޴�_���౺);
                �޴�_���౺.get_desc = pk::menu_item_get_desc_t(getDesc_�޴�_���౺);
                �޴�_���౺.is_visible = pk::menu_item_is_visible_t(isVisible_�޴�_���౺);
                �޴�_���౺.is_enabled = pk::menu_item_is_enabled_t(isEnabled_�޴�_���౺);
                �޴�_���౺.get_targets = pk::unit_menu_item_get_targets_t(getTargets_�޴�_���౺);
                �޴�_���౺.get_chance = pk::unit_menu_item_get_chance_t(getChance_100);
                �޴�_���౺.handler = pk::unit_menu_item_handler_t(handler_�޴�_���౺);
                pk::add_menu_item(�޴�_���౺);
            }
            
            
            //-------------------------------------------------------------
            if (�޴�_�δ�_���)
            {
                pk::menu_item �δ�;
                int �δ�_����;

                �δ�.menu = 1;
                �δ�.get_text = cast<pk::menu_item_get_text_t@>(function() { return pk::encode("�δ�"); });
                �δ�_���� = pk::add_menu_item(�δ�);
                
                // �δ�޴� : �ػ�
                if (�δ�_�ػ�_���)
                {
                    pk::menu_item �δ�_�ػ�;
                    �δ�_�ػ�.menu = �δ�_����;
                    �δ�_�ػ�.init = pk::unit_menu_item_init_t(init);
                    �δ�_�ػ�.get_text = pk::menu_item_get_text_t(getText_�δ�_�ػ�);
                    �δ�_�ػ�.get_desc = pk::menu_item_get_desc_t(getDesc_�δ�_�ػ�);
                    �δ�_�ػ�.is_visible = pk::menu_item_is_visible_t(isVisible_�δ�_�ػ�);
                    �δ�_�ػ�.is_enabled = pk::menu_item_is_enabled_t(isEnabled_�δ�_�ػ�);
                    �δ�_�ػ�.get_targets = pk::unit_menu_item_get_targets_t(getTargets_�δ�_�ػ�);
                    �δ�_�ػ�.get_chance = pk::unit_menu_item_get_chance_t(getChance_100);
                    �δ�_�ػ�.handler = pk::unit_menu_item_handler_t(handler_�δ�_�ػ�);
                    pk::add_menu_item(�δ�_�ػ�);
                }
                
                // �δ�޴� : ����
                if (�δ�_����_���)
                {
                    pk::menu_item �δ�_����;
                    �δ�_����.menu = �δ�_����;
                    �δ�_����.init = pk::unit_menu_item_init_t(init);
                    �δ�_����.get_text = pk::menu_item_get_text_t(getText_�δ�_����);
                    �δ�_����.get_desc = pk::menu_item_get_desc_t(getDesc_�δ�_����);
                    �δ�_����.is_visible = pk::menu_item_is_visible_t(isVisible_�δ�_����);
                    �δ�_����.is_enabled = pk::menu_item_is_enabled_t(isEnabled_�δ�_����);
                    �δ�_����.get_targets = pk::unit_menu_item_get_targets_t(getTargets_�δ�_����);
                    �δ�_����.get_chance = pk::unit_menu_item_get_chance_t(getChance_100);
                    �δ�_����.handler = pk::unit_menu_item_handler_t(handler_�δ�_����);
                    pk::add_menu_item(�δ�_����);
                }
                
                // ȸ�� : ������ ����Ͽ� 1�δ� ���� ȸ��
                if (�δ�_ȸ��_���)
                {
                    pk::menu_item �δ�_ȸ��;
                    �δ�_ȸ��.menu = �δ�_����;
                    �δ�_ȸ��.init = pk::unit_menu_item_init_t(init);
                    �δ�_ȸ��.get_text = pk::menu_item_get_text_t(getText_�δ�_ȸ��);
                    �δ�_ȸ��.get_desc = pk::menu_item_get_desc_t(getDesc_�δ�_ȸ��);
                    �δ�_ȸ��.is_visible = pk::menu_item_is_visible_t(isVisible_�δ�_ȸ��);
                    �δ�_ȸ��.is_enabled = pk::menu_item_is_enabled_t(isEnabled_�δ�_ȸ��);
                    �δ�_ȸ��.get_targets = pk::unit_menu_item_get_targets_t(getTargets_�δ�_ȸ��);
                    �δ�_ȸ��.get_chance = pk::unit_menu_item_get_chance_t(getChance_100);
                    �δ�_ȸ��.handler = pk::unit_menu_item_handler_t(handler_�δ�_ȸ��);
                    pk::add_menu_item(�δ�_ȸ��);
                }
                
                // ���� : �δ� ������ ����
                if (�δ�_����_���)
                {
                    pk::menu_item �δ�_����;
                    �δ�_����.menu = �δ�_����;
                    �δ�_����.init = pk::unit_menu_item_init_t(init);
                    �δ�_����.get_text = pk::menu_item_get_text_t(getText_�δ�_����);
                    �δ�_����.get_desc = pk::menu_item_get_desc_t(getDesc_�δ�_����);
                    �δ�_����.is_visible = pk::menu_item_is_visible_t(isVisible_�δ�_����);
                    �δ�_����.is_enabled = pk::menu_item_is_enabled_t(isEnabled_�δ�_����);
                    �δ�_����.get_targets = pk::unit_menu_item_get_targets_t(getTargets_�δ�_����);
                    �δ�_����.get_chance = pk::unit_menu_item_get_chance_t(getChance_100);
                    �δ�_����.handler = pk::unit_menu_item_handler_t(handler_�δ�_����);
                    pk::add_menu_item(�δ�_����);
                }
                
                
            }
            
            
		}

        //---------------------------------------------------------------------------
        
        void onUnitExpAdd(pk::unit@ unit, int type)
        {
            if (pk::is_campaign()) return;
            
            // �δ밡 ����ġ ȹ������ ��, ������ �δ븮��Ʈ�� ���� �� ���� �ߵ�
            if (unit_debate_list.contains(unit))
            {
                pk::scene(pk::scene_t(scene_���߼���)); // ���� �ִϸ��̼� �ҷ�����
                func_debate_result();                 // �δ뼳�� ��� �ݿ�
                
                unit_debate_list.clear();               // ����Ʈ �ʱ�ȭ
            }
            
        }
        void onTurnStart(pk::force@ force) 
        {
            if (pk::is_campaign()) return;
            unit_debate_list.clear();               // ����Ʈ �ʱ�ȭ
        }
        void onTurnEnd(pk::force@ force)
        {
            if (pk::is_campaign()) return;
            unit_debate_list.clear();               // ����Ʈ �ʱ�ȭ
        }
        void onGameInit()
        {
            if (pk::is_campaign()) return;
            unit_debate_list.clear();               // ����Ʈ �ʱ�ȭ
        }
        
        
        //---------------------------------------------------------------------------
        //---------------------------------------------------------------------------
        
		void init(pk::unit@ unit, pk::point src_pos)
		{
			@src_unit = @unit;
			src_pos_ = src_pos;
		}
        
		int getChance_100(pk::point dst_pos)
		{
			return 100;
		}
        
        //---------------------------------------------------------------------------
        // �跫 ���� ���� �Լ�
        //---------------------------------------------------------------------------
        uint8 func_stragety_cost(int energy_cost)
        {
            if (!�跫_Ư��_����) return energy_cost;
            
            uint8 n = uint8(energy_cost);
            if (src_unit.has_skill(Ư��_����))
            {
                if (����_�ݰ�_����)
                    n /= 2; // ��� �Ҹ� ���� ����
                else
                    n = 1;  // ��� �Ҹ� ������ 1��
            }
            
            //���¼��� ���� ��� �Ҹ� ���� - �Һδ� ��� �Ҹ� ����, ��δ� ��� �Ҹ� ����
            if (�跫_����_����)
            {
                if (src_unit.troops <= 2000)
                    n = uint8(n * pk::min(10.f, 2000.f/src_unit.troops));         // �ִ� 10�� �Ҹ�
                else if (src_unit.troops >= 10000)
                    n = uint8(n * pk::max(0.5f, (2-src_unit.troops/10000.f)));    // �ּ� 50% �Ҹ�
            }
            
            return n;
        }
        
        bool func_priority(pk::point dst_pos)
		{
            if (!�跫_Ư��_����) return false;
            
            if (src_unit.has_skill(Ư��_�Ż�))
                return true;
            
			pk::unit@ dst_unit = pk::get_unit(dst_pos);
            if (pk::is_alive(dst_unit))
            {
                if (src_unit.has_skill(Ư��_���) and (src_unit.attr.stat[�δ�ɷ�_����] > dst_unit.attr.stat[�δ�ɷ�_����]))
                    return true;
            }
            else if (!pk::is_alive(dst_unit) and pk::get_building(dst_pos) is null and src_unit.has_skill(Ư��_���))
                return true;
        
            return false;
        }
        
        int func_range_add()
		{
            if (!�跫_Ư��_����) return 0;
            
            if (src_unit.has_skill(Ư��_�͸�))
                return 1;
            
            return 0;
        }
        
        //---------------------------------------------------------------------------
        
        bool call_stragety_chance(pk::point dst_pos, int strategy_id)
        {
            int chance = (pk::int_bool(cast<pk::func206_t>(pk::get_func(206))(src_unit, src_pos_, dst_pos, strategy_id))).first;
            return pk::rand_bool(chance);
        }
        
        
        //---------------------------------------------------------------------------
        // �跫_�� (�ﱹ�� ������ ������)
        //---------------------------------------------------------------------------

		string getText_�跫_��()
		{
			return pk::encode(pk::format("�� ({})", func_stragety_cost(ENERGY_COST_��)));
		}

		string getDesc_�跫_��()
		{
            if (pk::get_person(src_unit.leader).rank >= ����_���� and pk::get_person(src_unit.leader).mibun == �ź�_�Ϲ� )
                return pk::encode("������ ���� ����� ������ �� �����ϴ�");
			else if (src_unit.energy < func_stragety_cost(ENERGY_COST_��))
				return pk::encode("����� �����մϴ�");
			else if (getTargets_�跫_��().length == 0)
				return pk::encode("�������� �Ʊ��δ밡 �����ϴ�");
			else
				return pk::encode("����� �Ҹ��Ͽ� �ٸ� �Ʊ��δ��� ����� ȸ���մϴ�");
		}
        
        bool isVisible_�跫_��()
		{
            if (pk::is_campaign()) return false;
            if (pk::get_person(src_unit.leader).rank >= ����_���� and pk::get_person(src_unit.leader).mibun == �ź�_�Ϲ�) return false;
            return true;
        }
        
		bool isEnabled_�跫_��()
		{
            if (pk::get_person(src_unit.leader).rank >= ����_���� and pk::get_person(src_unit.leader).mibun == �ź�_�Ϲ�) return false;
			else if (src_unit.energy < func_stragety_cost(ENERGY_COST_��)) return false;
			return getTargets_�跫_��().length > 0;
		}
        
		pk::array<pk::point_int> getTargets_�跫_��()
		{
			pk::array<pk::point_int> target_units;
			auto range = pk::range(src_pos_, 1, 1 + func_range_add());
			for (int i = 0; i < int(range.length); i++)
			{
				auto dst_unit = pk::get_unit(range[i]);
				if (dst_unit !is null and src_unit.pos != dst_unit.pos and src_unit.get_force_id() == dst_unit.get_force_id())
					target_units.insertLast(pk::point_int(range[i], 1));
			}
			return target_units;
		}

		bool handler_�跫_��(pk::point dst_pos)
		{
			pk::unit@ target_unit = pk::get_unit(dst_pos);
			
			// ���� �δ� �跫 ���� ���� ȿ��, ����/���δ� ��ȭ
			if (pk::is_in_screen(src_pos_))
			{
                pk::play_voice(0x31, pk::get_person(src_unit.leader));  // ���� : �跫2
				pk::play_se(0x39, src_pos_);
                pk::create_effect(0x3a, src_pos_);
			}
            // ���� �δ� ��� ����
			pk::add_energy(src_unit, -func_stragety_cost(ENERGY_COST_��), true);
            pk::say(pk::encode("�Ʊ� �δ븦 �����϶�"), pk::get_person(src_unit.leader));
            
			// ���δ� ��� ȸ�� ����
			pk::add_energy(target_unit, (ENERGY_COST_��/2), true);
            
            pk::say(pk::encode("����. ���� ��ġ�� ��"), pk::get_person(target_unit.leader));
            
            // ȿ�� : ��»�� ȿ��
            if (pk::is_in_screen(target_unit.pos))
                pk::create_effect(0x3d, target_unit.pos);

			// �ⱳ����
			pk::add_tp(pk::get_force(src_unit.get_force_id()), 30, dst_pos);
			// �ɷ°���ġ
			pk::add_stat_exp(src_unit, ����ɷ�_����, 4);
			// ����
			pk::add_kouseki(src_unit, 100);
            
			// �ൿ�Ϸ�
            src_unit.action_done = true;
			if (int(pk::option["San11Option.EnableInfiniteAction"]) != 0)
				src_unit.action_done = false;

			return true;
		}
        
        //---------------------------------------------------------------------------
        // �跫_��� (�ﱹ�� ������ ������)
        //---------------------------------------------------------------------------

		string getText_�跫_���()
		{
			return pk::encode(pk::format("��� ({})", func_stragety_cost(ENERGY_COST_���)));
		}

		string getDesc_�跫_���()
		{
            if (pk::get_person(src_unit.leader).rank >= ����_���� and pk::get_person(src_unit.leader).mibun == �ź�_�Ϲ�)
                return pk::encode("������ ���� ����� ������ �� �����ϴ�");
			else if (src_unit.energy < func_stragety_cost(ENERGY_COST_���))
				return pk::encode("����� �����մϴ�");
			else if (getTargets_�跫_���().length == 0)
				return pk::encode("�������� �Ʊ��δ밡 �����ϴ�");
			else
				return pk::encode("����� �Ҹ��Ͽ� ������ �Ʊ��δ�� �����δ��� ����� ȸ���մϴ�");
		}
        
        bool isVisible_�跫_���()
		{
            if (pk::is_campaign()) return false;
            if (pk::get_person(src_unit.leader).rank >= ����_���� and pk::get_person(src_unit.leader).mibun == �ź�_�Ϲ�) return false;
            return true;
        }

		bool isEnabled_�跫_���()
		{
			if (pk::get_person(src_unit.leader).rank >= ����_���� and pk::get_person(src_unit.leader).mibun == �ź�_�Ϲ�) return false;
			else if (src_unit.energy < func_stragety_cost(ENERGY_COST_���)) return false;
			return getTargets_�跫_���().length > 0;
		}
        
		pk::array<pk::point_int> getTargets_�跫_���()
		{
			pk::array<pk::point_int> target_units;
			auto range = pk::range(src_pos_, 1, 2 + func_range_add());
			for (int i = 0; i < int(range.length); i++)
			{
				auto dst_unit = pk::get_unit(range[i]);
				if (dst_unit !is null and src_unit.pos != dst_unit.pos and src_unit.get_force_id() == dst_unit.get_force_id())
					target_units.insertLast(pk::point_int(range[i], 1));
			}
			return target_units;
		}

		bool handler_�跫_���(pk::point dst_pos)
		{
			pk::unit@ target_unit = pk::get_unit(dst_pos);
			
			// ���� �δ� �跫 ���� ���� ȿ��, ����/���δ� ��ȭ
			if (pk::is_in_screen(src_pos_))
			{
                pk::play_voice(0x31, pk::get_person(src_unit.leader));  // ���� : �跫2
				pk::play_se(0x39, src_pos_);
                pk::create_effect(0x3a, src_pos_);
			}
            // ���� �δ� ��� ����
			pk::add_energy(src_unit, -func_stragety_cost(ENERGY_COST_���), true);
            pk::say(pk::encode("�Ʊ� �δ���� �����϶�"), pk::get_person(src_unit.leader));
            
			// ���δ� ��� ȸ�� ����
			pk::add_energy(target_unit, (ENERGY_COST_���/4), true);
            // ���δ� ���� �δ���� ��� ȸ�� ����
            auto range = pk::range(target_unit.pos, 1, 1);
			for (int i = 0; i < int(range.length); i++)
			{
				auto dst_unit = pk::get_unit(range[i]);
				if (dst_unit !is null and src_unit.pos != dst_unit.pos and src_unit.get_force_id() == dst_unit.get_force_id())
                {
					pk::add_energy(dst_unit, (ENERGY_COST_���/4), true);
                    
                    if (pk::is_in_screen(dst_unit.pos))
                    {
                        pk::say(pk::encode("����"), pk::get_person(dst_unit.leader));
                        // ȿ�� : ��»�� ȿ��
                        if (pk::is_in_screen(dst_unit.pos))
                            pk::create_effect(0x3d, dst_unit.pos);
                    }
                }
			}
            
			// �ⱳ����
			pk::add_tp(pk::get_force(src_unit.get_force_id()), 50, dst_pos);
			// �ɷ°���ġ
			pk::add_stat_exp(src_unit, ����ɷ�_����, 6);
			// ����
			pk::add_kouseki(src_unit, 150);
            
			// �ൿ�Ϸ�
			src_unit.action_done = true;
			if (int(pk::option["San11Option.EnableInfiniteAction"]) != 0)
				src_unit.action_done = false;

			return true;
		}
        
        
        //---------------------------------------------------------------------------
        // �跫_����
        //---------------------------------------------------------------------------
        
		int getChance_�ı�����(pk::point dst_pos)
		{
			return 100;
		}
        
		string getText_�跫_�ı�����()
		{
			return pk::encode(pk::format("���� ({})", func_stragety_cost(ENERGY_COST_�ı�����)));
		}

		string getDesc_�跫_�ı�����()
		{
			if (src_unit.energy < func_stragety_cost(ENERGY_COST_�ı�����))
				return pk::encode("����� �����մϴ�");
            else if (getTargets_�跫_�ı�����().length == 0)
				return pk::encode("�������� �� �ǹ��� �����ϴ�");
			else
				return pk::encode("����� ����Ͽ� ���� �ǹ��� �ı��մϴ�");
		}
        
        bool isVisible_�跫_�ı�����()
        {
            if (pk::is_campaign()) return false;
            return true;
        }
        
		bool isEnabled_�跫_�ı�����()
		{
			if (src_unit.energy < func_stragety_cost(ENERGY_COST_�ı�����)) return false;
			return getTargets_�跫_�ı�����().length > 0;
		}
        
		pk::array<pk::point_int> getTargets_�跫_�ı�����()
		{
			pk::array<pk::point_int> target_building;
            auto range = pk::range(src_pos_, 1, 1 + func_range_add());
			for (int i = 0; i < int(range.length); i++)
			{
				auto dst_building = pk::get_building(range[i]);
				if (dst_building !is null and pk::is_enemy(src_unit, dst_building))
					target_building.insertLast(pk::point_int(range[i], 1));
			}
			return target_building;
		}

        
		bool handler_�跫_�ı�����(pk::point dst_pos)
		{
            int hp_damage = int(100 + 2.0 * pk::rand(src_unit.attr.stat[�δ�ɷ�_����]));
            
			pk::building@ target_building = pk::get_building(dst_pos);
			
			// ���� �δ� �跫 ���� ���� ȿ��, ����/���δ� ��ȭ
			if (pk::is_in_screen(src_pos_))
			{
				pk::play_se(0x39, src_pos_);
                pk::create_effect(0x3a, src_pos_);
                switch(pk::rand(2))
                {
                    case 0: pk::play_voice(0x1E, pk::get_person(src_unit.leader)); break;  // ���� : ����_�ü�����1
                    case 1: pk::play_voice(0x1F, pk::get_person(src_unit.leader)); break;  // ���� : ����_�ü�����2
                }
			}
            
            // ���� �δ� ��� ����, ��� ���� ������ ����
			pk::add_energy(src_unit, -func_stragety_cost(ENERGY_COST_�ı�����), true);
            
            pk::person@ taishu = pk::get_person(pk::get_taishu_id(target_building));
            if (!pk::is_alive(taishu) or func_priority(dst_pos) or (pk::rand_bool(pk::min(100, 40 + pk::max(0, src_unit.attr.stat[�δ�ɷ�_����] - taishu.stat[����ɷ�_����]))) ))
            {
                pk::say(pk::encode("���� �㹰�� ������"), pk::get_person(src_unit.leader));
                
                int effect_mode = 0;
                
                // ���ݺδ� �ִϸ��̼� ȿ�� ('18.11.10)
                if (pk::is_in_screen(src_pos_))
                {
                    pk::damage_info info;
                    info.src_pos = src_pos_;
                    info.dst_pos = dst_pos;
                    pk::unit_anim(src_unit, 15, { info });
                    pk::wait(1);
                    pk::stop_unit_anim();
                }
                
                // ������ �����
                pk::add_hp(target_building, -hp_damage, true);
                
                if (target_building.get_id() >= �ǹ�_������ and target_building.hp <= 0)
                {
                    if (pk::is_in_screen(src_pos_))
                    {
                        pk::play_se(0x71, target_building.pos);         //����Ʈ����
                        pk::create_effect(0x5c, target_building.pos);   //����Ʈȿ��
                    }
                    
                    pk::kill(target_building, true);
                }
                
                // ���� Ȯ���� �� �ü� Ż�� : �� ��� ('18.12.26)
                if (�跫_����_Ż�� and pk::is_alive(target_building))
                {
                    if ((src_unit.has_skill(Ư��_��) or pk::rand_bool(CHANCE_����Ż��Ȯ��)) and target_building.facility >= �ü�_�� and target_building.facility <= �ü�_��ä)
                    {
                        int force_id = src_unit.get_force_id();
                        target_building.init_force = force_id;
                        string force_name = pk::decode(pk::get_name(pk::get_force(force_id)));
                        pk::say(pk::encode(pk::format("�������� \x1b[1x{}\x1b[0x���� �����ڽ��ϴ�", force_name)), pk::get_person(����_����), target_building);
                    }
                }
                
                // ����Ʈȿ��
                if (pk::is_in_screen(src_pos_) and pk::is_alive(target_building))
                {
                    if (pk::is_enemy(target_building, src_unit))    // ���� �Ϲ� ����
                    {
                        pk::play_se(0x71, target_building.pos);         //����Ʈ����
                        pk::create_effect(0x21, target_building.pos);   //����Ʈȿ��
                    }
                    else    // Ż�뼺��
                    {
                        pk::play_se(6);            //����Ʈ����   
                    }
                }
                
                // �ⱳ����
                pk::add_tp(pk::get_force(src_unit.get_force_id()), 30, dst_pos);
                // �ɷ°���ġ
                pk::add_stat_exp(src_unit, ����ɷ�_����, 5);
                // ����
                pk::add_kouseki(src_unit, 100);
            }
            else
            {
                pk::say(pk::encode("��. �����߳�"), pk::get_person(src_unit.leader));
            }
            
			// �ൿ�Ϸ�
			src_unit.action_done = true;
			if (int(pk::option["San11Option.EnableInfiniteAction"]) != 0)
				src_unit.action_done = false;

			return true;
		}
        
        
        //---------------------------------------------------------------------------
        // �跫_���� (�ﱹ�� ������ ������)
        //---------------------------------------------------------------------------
        
		int getChance_����(pk::point dst_pos)
		{
			return 100;
		}
        
		string getText_�跫_����()
		{
			return pk::encode(pk::format("���� ({})", func_stragety_cost(ENERGY_COST_����)));
		}

		string getDesc_�跫_����()
		{
			if (src_unit.energy < func_stragety_cost(ENERGY_COST_����))
				return pk::encode("����� �����մϴ�");
            else if (getTargets_�跫_����().length == 0)
				return pk::encode("�������� �¼��� �ִ� �� ������ �����ϴ�");
			else
				return pk::encode("����� ����Ͽ� �� �¼��� �⼺�� �����մϴ�");
		}
        
        bool isVisible_�跫_����()
        {
            if (pk::is_campaign()) return false;
            return true;
        }
        
		bool isEnabled_�跫_����()
		{
			if (src_unit.energy < func_stragety_cost(ENERGY_COST_����)) return false;
			return getTargets_�跫_����().length > 0;
		}
        
		pk::array<pk::point_int> getTargets_�跫_����()
		{
			pk::array<pk::point_int> targets;
            auto range = pk::range(src_pos_, 1, 2 + func_range_add());
			for (int i = 0; i < int(range.length); i++)
			{
				auto dst_building = pk::get_building(range[i]);
				if (dst_building !is null and pk::is_enemy(src_unit, dst_building))
                {
                    pk::person@ taishu = pk::get_person(pk::get_taishu_id(dst_building));
                    
                    if (pk::is_alive(taishu))
                        targets.insertLast(pk::point_int(range[i], 1));
                }
                
                auto enemy_unit = pk::get_unit(range[i]);
				if (enemy_unit !is null and pk::is_enemy(src_unit, enemy_unit))
					targets.insertLast(pk::point_int(range[i], 1));
			}
			return targets;
		}

        
        
		bool handler_�跫_����(pk::point dst_pos)
		{
            
            // ���� ��� ����
			pk::building@ target_building = pk::get_building(dst_pos);
            if (pk::is_alive(target_building))
            {
                // ���� �δ� �跫 ���� ���� ȿ��, ����/���δ� ��ȭ
                if (pk::is_in_screen(src_pos_))
                {
                    pk::play_voice(0x32, pk::get_person(src_unit.leader));  // ���� : �跫1
                    pk::play_se(0x39, src_pos_);
                    pk::create_effect(0x3a, src_pos_);
                }
                
                // ���� �δ� ��� ����, �� ���� �¼� �δ� ����
                pk::add_energy(src_unit, -func_stragety_cost(ENERGY_COST_����), true);
                
                pk::person@ taishu = pk::get_person(pk::get_taishu_id(target_building));
                if (pk::is_alive(taishu) and (func_priority(dst_pos) or src_unit.has_skill(Ư��_��) or (pk::rand_bool(pk::min(100, pk::max(0, src_unit.attr.stat[�δ�ɷ�_����] - taishu.stat[����ɷ�_����]))) )))
                {
                    pk::say(pk::encode("�����ó�� ���� ���� ���Ͷ�"), pk::get_person(src_unit.leader));
                    
                    pk::point NearEmptyPos = func_EmptyPos(target_building);
                    if(pk::is_valid_pos(NearEmptyPos))
                    {
                        int weapon_id = ����_��;
                        int default_troops = pk::min(5000, int(pk::get_troops(target_building)/5) );    // �⺻ ���� ���¼� ����
                        int target_troops = default_troops;
                        
                        func_weapon_select(target_building, default_troops, weapon_id, target_troops);  // ���� ���� �Լ� ȣ��
                        
                        // ���� ���¿� ���� ���� ����
                        int target_food = pk::min( int(target_troops * 1.5f), int(pk::get_food(target_building)/2) );
                        
                        // �δ� ������ ���� ���� ����,����,���� ����
                        pk::add_troops(target_building, -target_troops, false);
                        pk::add_food(target_building, -target_food, false);
                        
                        if (weapon_id != ����_��)
                            pk::add_weapon_amount(target_building, weapon_id, -target_troops, false);
                        
                        // ���ߵ� �δ� ����
                        @dst_unit = pk::create_unit(target_building, taishu, null, null, target_troops, weapon_id, ����_�ְ�, 0, target_food, NearEmptyPos);
                        pk::say(pk::encode("�ҿ���� ������ָ�"), pk::get_person(dst_unit.leader));
                        
                        pk::set_order(dst_unit, �δ��ӹ�_����, src_unit.get_pos());
                        
                        if (�跫_����_��������)
                        {
                            // �Ÿ��� �����ϸ� ���� ����, �뺴�̸� ���Ÿ� ���� ����
                            func_fuck_atk(src_unit, dst_unit, �跫_����_��������);

                            // �δ� ���� �� ����
                            if (pk::is_alive(src_unit) and pk::is_alive(dst_unit))
                            {
                                @dst_unit_debate = @dst_unit;
                                @src_unit_debate = @src_unit;
                            
                                unit_debate_list.clear();
                                unit_debate_list.add(dst_unit);
                            }
                        }
                    
                        // �ⱳ����
                        pk::add_tp(pk::get_force(src_unit.get_force_id()), 30, dst_pos);
                        // �ɷ°���ġ
                        pk::add_stat_exp(src_unit, ����ɷ�_����, 5);
                        // ����
                        pk::add_kouseki(src_unit, 100);
                    }
                }
                else
                {
                    pk::say(pk::encode("������ �� ���ϴ� ��"), pk::get_person(src_unit.leader));
                }
                
            } // ���� ��� ����
            
            // �δ� ��� ����
            @ dst_unit = pk::get_unit(dst_pos);
            if (pk::is_alive(dst_unit))
            {
                // ���� �δ� �跫 ���� ���� ȿ��, ����/���δ� ��ȭ
                if (pk::is_in_screen(src_pos_))
                {
                    pk::play_voice(0x32, pk::get_person(src_unit.leader));  // ���� : �跫1
                    pk::play_se(0x39, src_pos_);
                    pk::create_effect(0x3a, src_pos_);
                }
                
                // ���� �δ� ��� ����, ���δ� ��� ����
                pk::add_energy(src_unit, -func_stragety_cost(ENERGY_COST_����), true);
                func_fuck_msg(src_unit, 0);     // �޼���_�ߵ��δ�
                
                // ������ ���
                int stat_delta = 100;
                if (dst_unit.leader < ����_���� or dst_unit.leader > ����_����)
                    stat_delta = pk::max(0, src_unit.attr.stat[�δ�ɷ�_����] - dst_unit.attr.stat[�δ�ɷ�_����]);
                
                if (func_priority(dst_pos) or src_unit.has_skill(Ư��_��) or (pk::rand_bool(pk::min(100, 40 + pk::max(0, stat_delta))) ) )
                {
                    func_fuck_msg(dst_unit, 1);  // �޼���_����_��ǥ�δ�
                    
                    pk::add_energy(dst_unit, -(src_unit.attr.stat[�δ�ɷ�_����]/5), true);
                    pk::set_order(dst_unit, �δ��ӹ�_����, src_unit.get_pos());    // �ߵ��δ븦 ���� ��ǥ�� ����
                    
                    if (�跫_����_��������)
                    {
                        // �Ÿ��� �����ϸ� ���� ����, �뺴�̸� ���Ÿ� ���� ����
                        func_fuck_atk(src_unit, dst_unit, �跫_����_��������);

                        // �δ� ���� �� ����
                        if (pk::is_alive(src_unit) and pk::is_alive(dst_unit))
                        {
                            @dst_unit_debate = @dst_unit;
                            @src_unit_debate = @src_unit;
                            
                            unit_debate_list.clear();
                            unit_debate_list.add(dst_unit);
                        }
                    }
                    
                    
                    // �ⱳ����
                    pk::add_tp(pk::get_force(src_unit.get_force_id()), 30, dst_pos);
                    // �ɷ°���ġ
                    pk::add_stat_exp(src_unit, ����ɷ�_����, 5);
                    // ����
                    pk::add_kouseki(src_unit, 100);
                }
                else
                {
                    func_fuck_msg(dst_unit, 2);  // �޼���_����_��ǥ�δ�
                }
            }
            
			// �ൿ�Ϸ�
			src_unit.action_done = true;
			if (int(pk::option["San11Option.EnableInfiniteAction"]) != 0)
				src_unit.action_done = false;

			return true;
		}
        
        
        void func_fuck_atk (pk::unit@ attacker, pk::unit@ target, bool ȿ������)
        {
            if (ȿ������)
            {
                if (pk::get_distance(target.pos, attacker.pos) == 1)
                    pk::attack(target, attacker);
                else if (pk::get_distance(target.pos, attacker.pos) == 2 and target.weapon == ����_��)
                    pk::attack(target, attacker);
            }
        }
        
        // �跫_���߿� �Լ� : �ǹ��� �ߵ��δ� �ֺ� �� ĭ ã��
        pk::point func_EmptyPos(pk::building@ building)
		{
            int max_range = 3;
			auto range = pk::range(building.get_pos(), 1, max_range);
            
            for (int j = 1; j <= int(max_range); j++)     // �ߵ��δ���� �Ÿ�, �����̺��� �ָ�
            {
                for (int i = 0; i < int(range.length); i++) // �������� �Ÿ�, �����̺��� �ָ�
                {
                    pk::hex@ hex = pk::get_hex(range[i]);
                    if (!hex.has_building and !hex.has_unit and (pk::get_distance(range[i], src_unit.pos) <= j) )
                        return range[i];    // ���� ���� �� �ش� ��ġ ��ȯ
                }
            }
			return -1;
		}
        
        // �跫_���߿� �Լ� : ���� ���� (����ȭ �ƴ�, ���� ���� ������ ����� ����)
        void func_weapon_select(pk::building@ building, int troops, int &out weapon_sel, int &out troops_sel)
        {
            int weapon_max = 0;
            
            weapon_sel = 0;
            troops_sel = 0;
            
            for (int i = ����_â; i <= ����_����; i++)
            {
                int weapon_t = pk::get_weapon_amount(building, i);
                if (2000 <= weapon_t and weapon_max <= weapon_t)
                {
                    weapon_max = weapon_t;
                    weapon_sel = i;
                    troops_sel = pk::min(troops, weapon_max);
                }
            }
            
            if (weapon_sel == 0)
            {
                troops_sel = troops;
            }
        }
        
        // �跫_���� �弳�� �Լ� : ���� �޼��� ��Ʈ
        void func_fuck_msg(pk::unit@ msg_unit, int msg_case)
        {
            pk::person@ leader = pk::get_person(msg_unit.leader);
            
            if (msg_case == 0)  // ����_�ߵ��δ�
            {
                switch (pk::rand(4))
                {
                    case 0 : pk::say(pk::encode("������ ������� �޾ҳ�"), leader); break;
                    case 1 : pk::say(pk::encode("������ ���� ��"), leader); break;
                    case 2 : pk::say(pk::encode("�� �� �ڽľ�"), leader); break;
                    case 3 : pk::say(pk::encode("�ֹֺ̾� ���� ��"), leader); break;
                }
            }
            else if (msg_case == 1)  // ����_��ǥ�δ�
            {
                switch (pk::rand(4))
                {
                    case 0 : pk::say(pk::encode("�� ���� ���� ���ְڴ�"), leader); break;
                    case 1 : pk::say(pk::encode("�ű� ��ٸ��� �־��"), leader); break;
                    case 2 : pk::say(pk::encode("���� �׿�����"), leader); break;
                    case 3 : pk::say(pk::encode("�������� ȯ���߱���"), leader); break;
                }
            }
            else if (msg_case == 2)  // ����_��ǥ�δ�
            {
                switch (pk::rand(4))
                {
                    case 0 : pk::say(pk::encode("�׳� �����ض�"), leader); break;
                    case 1 : pk::say(pk::encode("����� �� ����"), leader); break;
                    case 2 : pk::say(pk::encode("����ӱ�"), leader); break;
                    case 3 : pk::say(pk::encode("....."), leader); break;
                }
            }
        }
        
        void scene_���߼���()
		{
            pk::person@ p0 = pk::get_person(src_unit_debate.leader);
            pk::person@ p1 = pk::get_person(dst_unit_debate.leader);
            string p0_name = pk::decode(pk::get_name(p0));
            string p1_name = pk::decode(pk::get_name(p1));
            
            pk::cutin(20);  // ����: �������
            pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x ���� ���� ��밡 �� �� �����̱�", p1_name)), p0);
            pk::message_box(pk::encode(pk::format("\x1b[1x{}\x1b[0x �Ծ߸��� ���� ��밡 ���� �ʼ�", p0_name)), p1);
            debate_result = pk::debate(p0, p1, p0.is_player(), p1.is_player(), false, �跫_����_��������).first;
        }
        
        void func_debate_result()
        {
            // ���� ��� �ݿ�
            if (debate_result == 0)     // �Ŵ� ���� �̱� ���
            {
                func_debate_msg(src_unit_debate, 0);   // �޼���_�¸�
                func_debate_msg(dst_unit_debate, 1);  // �޼���_����
                
                pk::add_energy(src_unit_debate, +2*ENERGY_COST_���߼���, true);
                pk::add_energy(dst_unit_debate, -2*ENERGY_COST_���߼���, true);
                
                pk::add_loyalty(pk::get_person(dst_unit_debate.leader), -5);   // ��ǥ�δ� ������ �漺���� ����
                
            }
            else if (debate_result == 1)    // �޴� ���� �̱� ���
            {
                func_debate_msg(dst_unit_debate, 0);   // �޼���_�¸�
                func_debate_msg(src_unit_debate, 1);  // �޼���_����

                pk::add_energy(dst_unit_debate, +2*ENERGY_COST_���߼���, true);
                pk::add_energy(src_unit_debate, -2*ENERGY_COST_���߼���, true);
                
                pk::add_loyalty(pk::get_person(src_unit_debate.leader), -5);   // �ߵ��δ� ������ �漺���� ����
            }
        }
        
        // ����_������ �Լ� : ���� �޼��� ��Ʈ
        void func_debate_msg(pk::unit@ msg_unit, int msg_case)
        {
            pk::person@ leader = pk::get_person(msg_unit.leader);
            
            if (msg_case == 0)  // �¸��δ�
            {
                switch (pk::rand(4))
                {
                    case 0 : pk::say(pk::encode("�̰��"), leader); break;
                    case 1 : pk::say(pk::encode("���� �� �� �о������"), leader); break;
                    case 2 : pk::say(pk::encode("����� �� ����"), leader); break;
                    case 3 : pk::say(pk::encode("���� ���� �켼�ϱ�"), leader); break;
                }
            }
            else if (msg_case == 1)  // �����δ�
            {
                switch (pk::rand(4))
                {
                    case 0 : pk::say(pk::encode("���°�"), leader); break;
                    case 1 : pk::say(pk::encode("���� ���߱�"), leader); break;
                    case 2 : pk::say(pk::encode("�ȵǰڴ� ��"), leader); break;
                    case 3 : pk::say(pk::encode("�̷� ��Ȳ�̸�.."), leader); break;
                }
            }
            else if (msg_case == 2)  // ���л�Ȳ
            {
                switch (pk::rand(4))
                {
                    case 0 : pk::say(pk::encode("�׳� �����ض�"), leader); break;
                    case 1 : pk::say(pk::encode("����� �� ����"), leader); break;
                    case 2 : pk::say(pk::encode("����ӱ�"), leader); break;
                    case 3 : pk::say(pk::encode("���� ���� �Ҹ���"), leader); break;
                }
            }
        }
        
        //---------------------------------------------------------------------------
        // �跫_ȸ�� (�ﱹ�� ������ ������)
        //---------------------------------------------------------------------------

		string getText_�跫_ȸ��()
		{
			return pk::encode(pk::format("ȸ�� ({})", func_stragety_cost(ENERGY_COST_ȸ��)));
		}

		string getDesc_�跫_ȸ��()
		{
			if (pk::get_person(src_unit.leader).mibun == �ź�_�Ϲ� and !src_unit.has_skill(Ư��_����))
                return pk::encode("�ź��� ���� �Ǵ� ������ �ƴϰų�, Ư��_������ ���� ���� �ʽ��ϴ�");
            else if (src_unit.energy < func_stragety_cost(ENERGY_COST_ȸ��))
				return pk::encode("����� �����մϴ�");
			else if (getTargets_�跫_ȸ��().length == 0)
				return pk::encode("�������� �ൿ�� �Ϸ��� �Ʊ��δ밡 �����ϴ�");
			else
				return pk::encode("����� ���� �Ҹ��Ͽ� �Ʊ� �δ� �ൿ�� �簳�մϴ�");
		}
        
        bool isVisible_�跫_ȸ��()
		{
            if (pk::is_campaign()) return false;
            if (pk::get_person(src_unit.leader).mibun == �ź�_�Ϲ� and !src_unit.has_skill(Ư��_����)) return false;
			return true;
        }
        
		bool isEnabled_�跫_ȸ��()
		{
			if (pk::get_person(src_unit.leader).mibun == �ź�_�Ϲ� and !src_unit.has_skill(Ư��_����)) return false;
            else if (src_unit.energy < func_stragety_cost(ENERGY_COST_ȸ��)) return false;
			return getTargets_�跫_ȸ��().length > 0;
		}
        
		pk::array<pk::point_int> getTargets_�跫_ȸ��()
		{
			pk::array<pk::point_int> target_units;
			auto range = pk::range(src_pos_, 1, 1 + func_range_add());
			for (int i = 0; i < int(range.length); i++)
			{
				auto dst_unit = pk::get_unit(range[i]);
				if (dst_unit !is null and src_unit.pos != dst_unit.pos and src_unit.get_force_id() == dst_unit.get_force_id() and dst_unit.action_done == true and dst_unit.status == �δ����_���)
					target_units.insertLast(pk::point_int(range[i], 1));
			}
			return target_units;
		}

		bool handler_�跫_ȸ��(pk::point dst_pos)
		{
			pk::unit@ target_unit = pk::get_unit(dst_pos);
			
			// ���� �δ� �跫 ���� ���� ȿ��, ����/���δ� ��ȭ
			if (pk::is_in_screen(src_pos_))
			{
                pk::play_voice(0x37, pk::get_person(src_unit.leader));  // ���� : ����_����
				pk::play_se(0x39, src_pos_);
                pk::create_effect(0x3a, src_pos_);
			}
            // ���� �δ� ��� ����
			pk::add_energy(src_unit, -func_stragety_cost(ENERGY_COST_ȸ��), true);
            pk::say(pk::encode("�δ뿡 �ٽ� �����!!"), pk::get_person(src_unit.leader));
            
            // ���ൿ ����
            pk::say(pk::encode("�ٹ����� ���� �������� ��������"), pk::get_person(target_unit.leader));
            target_unit.action_done = false;    // ���δ� �ൿ�簳
            
            // ȿ�� : 
            if (pk::is_in_screen(target_unit.pos))
                pk::create_effect(0x3a, target_unit.pos);

			// �ⱳ����
			pk::add_tp(pk::get_force(src_unit.get_force_id()), 30, dst_pos);
			// �ɷ°���ġ
			pk::add_stat_exp(src_unit, ����ɷ�_����, 4);
			// ����
			pk::add_kouseki(src_unit, 100);
            
			// �ൿ�Ϸ�
			src_unit.action_done = true;
			if (int(pk::option["San11Option.EnableInfiniteAction"]) != 0)
				src_unit.action_done = false;
            
			return true;
		}
        
        
        //---------------------------------------------------------------------------
        // �δ�_�ػ�
        //---------------------------------------------------------------------------

		string getText_�δ�_�ػ�()
        {
			return pk::encode("�ػ�");
        }
        
		string getDesc_�δ�_�ػ�()
        {
            if (src_unit.troops < 2000)
                return pk::encode("���� 2õ�� �̻� ������ �� �ֽ��ϴ�");
            else if (count_enemies_around(src_pos_) >= 1) 
                return pk::encode("�ֺ��� ������ �־� ������ �� �����ϴ�");
            else
                return pk::encode("�δ븦 �ػ��մϴ� (���� ���� �ҽ� �� ����� ��ȯ)");
        }
        
        
        bool isVisible_�δ�_�ػ�()
		{
            if (pk::is_campaign()) return false;
			return true;
        }
        
		bool isEnabled_�δ�_�ػ�()
		{
            if (src_unit.troops < 2000) return false;
            else if (count_enemies_around(src_pos_) >= 1) return false;
            return getTargets_�δ�_�ػ�().length > 0;
        }
        
		pk::array<pk::point_int> getTargets_�δ�_�ػ�()
		{
            pk::array<pk::point_int> target_units;
            
            if (count_enemies_around(src_pos_) < 1)
            {
                target_units.insertLast(pk::point_int(src_pos_, 1));
			}
            return target_units;
		}

		bool handler_�δ�_�ػ�(pk::point dst_pos)
		{
			pk::unit@ target_unit = pk::get_unit(dst_pos);

			// �ൿ�Ϸ�
			src_unit.action_done = true;
			if (int(pk::option["San11Option.EnableInfiniteAction"]) != 0)
				src_unit.action_done = false;
            
            // �δ� �ػ�
            pk::say(pk::encode("�δ븦 �ػ��ϰڼ�"), pk::get_person(target_unit.leader));
            
            pk::add_troops(target_unit, -target_unit.troops, false);
            if (target_unit.troops <= 0)
                pk::kill(target_unit);

			return true;
		}
        
        // ������ ���δ�, ���ǹ� �� �˻�
        int count_enemies_around(pk::point pos)
        {
            int count_enemy = 0;
            int max_range = 5;
            
            pk::array<pk::point> range = pk::range(pos, 1, max_range);
            for (int i = 0; i < int(range.length); i++)
            {
                pk::unit@ unit_around = pk::get_unit(range[i]);
                if (unit_around !is null and pk::is_enemy(src_unit, unit_around))
                    count_enemy += 1;
                
                pk::building@ building_around = pk::get_building(range[i]);
                if (building_around !is null and pk::is_enemy(src_unit, building_around))
                    count_enemy += 1;
            }
            
            return count_enemy;
        }
        
        
        //---------------------------------------------------------------------------
        // �δ�_���� (�ﱹ��13 ������)
        //---------------------------------------------------------------------------

		string getText_�δ�_����()
        {
			return pk::encode("����");
        }
            
		string getDesc_�δ�_����()
		{
            if (pk::get_person(src_unit.leader).rank >= ����_���� and pk::get_person(src_unit.leader).mibun == �ź�_�Ϲ�)
                return pk::encode("������ ���� ����� ������ �� �����ϴ�");
            else if (src_unit.troops < 2000)
                return pk::encode("���� 2õ�� �̻� ������ �� �ֽ��ϴ�");
            else if (count_enemies_around(src_pos_) >= 1) 
                return pk::encode("�ֺ��� ������ �־� ������ �� �����ϴ�");
			else if (getTargets_�δ�_����().length == 0)
				return pk::encode("�������� ���� ������ �Ʊ��δ밡 �����ϴ�");
			else
				return pk::encode("���δ뿡 ������ �����մϴ�");
		}
        
		bool isVisible_�δ�_����()
        {
            if (pk::is_campaign()) return false;
            return true;
        }
        
		
		bool isEnabled_�δ�_����()
		{
            if (pk::get_person(src_unit.leader).rank >= ����_���� and pk::get_person(src_unit.leader).mibun == �ź�_�Ϲ�) return false;
            else if (src_unit.troops < 2000) return false;
            else if (count_enemies_around(src_pos_) >= 1) return false;
			return getTargets_�δ�_����().length > 0;
		}
        
		pk::array<pk::point_int> getTargets_�δ�_����()
		{
			pk::array<pk::point_int> target_units;
            
            if (count_enemies_around(src_pos_) < 1) 
            {
                auto range = pk::range(src_pos_, 1, 1);
                for (int i = 0; i < int(range.length); i++)
                {
                    auto dst_unit = pk::get_unit(range[i]);
                    if (dst_unit !is null and src_unit.pos != dst_unit.pos and src_unit.get_force_id() == dst_unit.get_force_id() and pk::get_ground_weapon_id(src_unit) ==  pk::get_ground_weapon_id(dst_unit))
                        target_units.insertLast(pk::point_int(range[i], 1));
                }
            }
			return target_units;
		}

		bool handler_�δ�_����(pk::point dst_pos)
		{
			pk::unit@ target_unit = pk::get_unit(dst_pos);
			
			// ���� �δ� �跫 ���� ���� ȿ��, ����/���δ� ��ȭ
			if (pk::is_in_screen(src_pos_))
			{
				pk::play_se(0x39, src_pos_);
				//pk::wait(1, 1000);
			}
            
            int troops_re_org = pk::min(src_unit.troops, (pk::get_max_troops(target_unit) - target_unit.troops));
            int energy_re_org = ((troops_re_org * src_unit.energy) + (target_unit.troops * target_unit.energy)) / (troops_re_org + target_unit.troops);
            
            int food_re_org = pk::min(src_unit.food, (2*troops_re_org));
            
            
            // ����δ� ���°���, ��������
            pk::add_troops(src_unit, -troops_re_org, true);
            pk::add_food(src_unit, -food_re_org, true);
            
            if (src_unit.troops == 0)
            {
                pk::say(pk::encode("�츮 �δ�� �ػ��Ѵ�"), pk::get_person(src_unit.leader));
                pk::kill(src_unit);
            }
            else
            {
                pk::say(pk::encode("������ �ѱ�ڼ�"), pk::get_person(src_unit.leader));
            }

            
            // ���δ� ��������
            pk::add_troops(target_unit, troops_re_org, true);
            pk::say(pk::encode("����� �������� ���� ������"), pk::get_person(target_unit.leader));
            // ���δ� ��������
            pk::add_food(target_unit, food_re_org, true);
            // ���δ� �������
            pk::add_energy(target_unit, (energy_re_org - target_unit.energy), true);
            
            // ȿ�� : ��»��(����)
            if (pk::is_in_screen(target_unit.pos))
                pk::create_effect(0x4c, target_unit.pos);
            
			// �ൿ�Ϸ�
			src_unit.action_done = true;
			if (int(pk::option["San11Option.EnableInfiniteAction"]) != 0)
				src_unit.action_done = false;

			return true;
		}
        
        
        
        //---------------------------------------------------------------------------
        // �δ�_ȸ��
        //---------------------------------------------------------------------------
        
		string getText_�δ�_ȸ��()
		{
			return pk::encode(pk::format("ȸ�� ��{}", GOLD_COST_ȸ��));
		}

		string getDesc_�δ�_ȸ��()
		{
			if (pk::get_person(src_unit.leader).rank >= ����_���� and pk::get_person(src_unit.leader).mibun == �ź�_�Ϲ�)
                return pk::encode("������ ���� ����� ������ �� �����ϴ�");
			else if (src_unit.gold < GOLD_COST_ȸ��)
				return pk::encode("�������� �����մϴ�");
            else if (count_enemies_around(src_pos_) >= 1) 
                return pk::encode("�ֺ��� ������ �־� ������ �� �����ϴ�");
			else
				return pk::encode("�������� ����Ͽ� ������ ȸ���մϴ�");
		}
        
        bool isVisible_�δ�_ȸ��()
		{
            if (pk::is_campaign()) return false;
			return true;
        }
        
		bool isEnabled_�δ�_ȸ��()
		{
			if (pk::get_person(src_unit.leader).rank >= ����_���� and pk::get_person(src_unit.leader).mibun == �ź�_�Ϲ�) return false;
            else if (src_unit.gold < GOLD_COST_ȸ��) return false;
            else if (count_enemies_around(src_pos_) >= 1) return false;
			return getTargets_�δ�_ȸ��().length > 0;
		}
        
		pk::array<pk::point_int> getTargets_�δ�_ȸ��()
		{
			pk::array<pk::point_int> target_units;
            target_units.insertLast(pk::point_int(src_pos_, 1));
            
            auto range = pk::range(src_pos_, 1, 2 + func_range_add());
			for (int i = 0; i < int(range.length); i++)
			{
				auto dst_unit = pk::get_unit(range[i]);
				if (dst_unit !is null and src_unit.pos != dst_unit.pos and src_unit.get_force_id() == dst_unit.get_force_id())
					target_units.insertLast(pk::point_int(range[i], 1));
			}
            
			return target_units;
		}

        
		bool handler_�δ�_ȸ��(pk::point dst_pos)
		{
			pk::unit@ target_unit = pk::get_unit(dst_pos);
			
			// ���� �δ� �跫 ���� ���� ȿ��, ����/���δ� ��ȭ
			if (pk::is_in_screen(src_pos_))
			{
                pk::play_voice(0x37, pk::get_person(src_unit.leader));  // ���� : ����
				pk::play_se(0x39, src_pos_);
                pk::create_effect(0x4a, src_pos_);  // ȿ��: ��»��(����)
			}
            // ���� �δ� ������ ����, ���� ȸ��
            pk::say(pk::encode("�λ󺴵��� ġ���϶�"), pk::get_person(src_unit.leader));
			pk::add_gold(src_unit, -GOLD_COST_ȸ��, true);
			pk::add_troops(target_unit, (GOLD_COST_ȸ��/40 * src_unit.attr.stat[�δ�ɷ�_���]), true);
            
			// �ⱳ����
			pk::add_tp(pk::get_force(src_unit.get_force_id()), 20, dst_pos);
			// �ɷ°���ġ
			pk::add_stat_exp(src_unit, ����ɷ�_���, 4);
			// ����
			pk::add_kouseki(src_unit, 100);
            
			// �ൿ�Ϸ�
			src_unit.action_done = true;
			if (int(pk::option["San11Option.EnableInfiniteAction"]) != 0)
				src_unit.action_done = false;

			return true;
		}
        
        
        
        //---------------------------------------------------------------------------
        // �δ�_����
        //---------------------------------------------------------------------------
        
		string getText_�δ�_����()
		{
			return pk::encode("����");
		}

		string getDesc_�δ�_����()
		{
            if (!pk::is_alive(pk::get_person(src_unit.member[1]))) 
                return pk::encode("������ �����ϴ�");
            else if (count_enemies_around(src_pos_) >= 1) 
                return pk::encode("�ֺ��� ������ �־� ������ �� �����ϴ�");
            return pk::encode("�δ��� ������ �����մϴ�");
		}
        
        bool isVisible_�δ�_����()
		{
            if (pk::is_campaign()) return false;
            return true;
		}
                
		bool isEnabled_�δ�_����()
		{
            if (!pk::is_alive(pk::get_person(src_unit.member[1]))) return false;
            else if (count_enemies_around(src_pos_) >= 1) return false;
			return getTargets_�δ�_����().length > 0;
		}
        
		pk::array<pk::point_int> getTargets_�δ�_����()
		{
            pk::array<pk::point_int> target_units;
            
            if (count_enemies_around(src_pos_) < 1)
            {
                target_units.insertLast(pk::point_int(src_pos_, 1));
			}
            return target_units;
		}
        
		bool handler_�δ�_����(pk::point dst_pos)
		{
			pk::unit@ target_unit = pk::get_unit(dst_pos);
			
            // ����/���� ����Ʈ
			pk::person@ p0 = pk::get_person(target_unit.member[0]);
			pk::person@ p1 = pk::get_person(target_unit.member[1]);
			pk::person@ p2 = pk::get_person(target_unit.member[2]);
            
            pk::list<pk::person@> member_list;
            if (pk::is_alive(p0)) member_list.add(p0);
            if (pk::is_alive(p1)) member_list.add(p1);
            if (pk::is_alive(p2)) member_list.add(p2);
            
            // ���ֺ��� Ȯ��
            int cmd_old = pk::get_command(p0);
            int cmd_new;
            
            // ���� ����
            bool confirm = false;
            pk::list<pk::person@> leader_sel;
            int leader_id;
            pk::person@ leader;
            string leader_name;
            while (!confirm)
            {
                leader_sel = pk::person_selector(pk::encode("���� ����"), pk::encode("�δ��� ������ �����մϴ�."), member_list, 1, 1);
                if (leader_sel.count == 0) return false; // ��� ����
               
                leader_id = leader_sel[0].get_id();      // ������ �����ȣ
                if (leader_id == target_unit.member[0])
                {
                    pk::message_box(pk::encode("������ �������� �ʾҽ��ϴ�"));
                }
                else
                {       
                    @leader = pk::get_person(leader_id);
                    leader_name = pk::decode(pk::get_name(leader));
                    cmd_new = pk::get_command(leader);
                    confirm = pk::yes_no(pk::encode(pk::format("\x1b[1x{}\x1b[0x��(��) �� �������� �����Ͻðڽ��ϱ�?\n(���ֺ��� {} �� \x1b[1x{}\x1b[0x)", leader_name, cmd_old, cmd_new)));
                }
            }
            
            // ����/���� ����ID swap
            if (leader_id == target_unit.member[2])
            {
                target_unit.member[2] = target_unit.member[0];
                target_unit.member[0] = leader_id;
            }
            else if (leader_id == target_unit.member[1])
            {
                target_unit.member[1] = target_unit.member[0];
                target_unit.member[0] = leader_id;
            }
            else if (leader_id == target_unit.member[0])
            {
                target_unit.member[0] = leader_id;
            }
            target_unit.update();
            
            // ���ο� ������ ��ȭǥ��
            if (pk::is_in_screen(src_pos_))
            {
                pk::say(pk::encode(pk::format("���ݺ��� �� \x1b[1x{}\x1b[0x��(��)\n�δ��� ���ָ� �ðڼ�", leader_name)), leader);
            }
            
            // ���ֺ��� �ʰ� �� �δ� ���� ����
            if (int(target_unit.troops) > int(cmd_new))
                pk::add_troops(target_unit, int(target_unit.troops - cmd_new), true);
            
			// �ൿ�Ϸ�
			src_unit.action_done = true;
			if (int(pk::option["San11Option.EnableInfiniteAction"]) != 0)
				src_unit.action_done = false;

			return true;
		}
        
        
        
        //---------------------------------------------------------------------------
        // �޴�_���౺ (�ﱹ��7 ������)
        //---------------------------------------------------------------------------

		string getText_�޴�_���౺()
        {
			return pk::encode("���౺");
        }
        
		string getDesc_�޴�_���౺()
		{
			if (pk::get_person(src_unit.leader).rank >= ����_���� and pk::get_person(src_unit.leader).mibun == �ź�_�Ϲ�)
                return pk::encode("������ ���� ����� ������ �� �����ϴ�");
			else if (src_unit.energy < ENERGY_MIN_���౺)
				return pk::encode("�ּ� ���� ����� �����մϴ�");
			else
				return pk::encode(pk::format("����� ����Ͽ� �߰� �̵��մϴ� (�ּұ�� {} �̻��ʿ�)", ENERGY_MIN_���౺));
		}
        
		bool isVisible_�޴�_���౺()
        {
            if (pk::is_campaign()) return false;
            return true;
        }
        
		bool isEnabled_�޴�_���౺()
		{
			if (pk::get_person(src_unit.leader).rank >= ����_���� and pk::get_person(src_unit.leader).mibun == �ź�_�Ϲ�) return false;
            else if (src_unit.energy < ENERGY_MIN_���౺) return false;
			return getTargets_�޴�_���౺().length > 0;
		}
        
		pk::array<pk::point_int> getTargets_�޴�_���౺()
		{
            int movement = int(MOVEMENT_���౺ * src_unit.attr.stat[�δ�ɷ�_�̵�]);
            
            // �̵� ��ǥ ���� ȹ��
            pk::array<pk::point_int> target_pos;
			auto range = pk::get_movable_pos(src_unit, src_pos_, movement); // �̵������� ��θ� ȹ��
            for (int i = 0; i < int(range.length); i++)
			{
                pk::hex@ hex = pk::get_hex(range[i]);
                target_pos.insertLast(pk::point_int(range[i], 1));
			}
            return target_pos;
		}

		bool handler_�޴�_���౺(pk::point dst_pos)
		{
            // �߰� �̵��� ����
            int movement = int(MOVEMENT_���౺ * src_unit.attr.stat[�δ�ɷ�_�̵�]);
            int cost_sum = 0;   // �� �̵� cost ���ϱ�
            int cost_next = 0;
            
            // �δ� ��ġ ����
            pk::hex@ hex = pk::get_hex(src_unit.pos);
            int terrain_id = hex.terrain;
            // �δ� ����
            int weapon_id = pk::is_water_terrain(terrain_id) ? pk::get_sea_weapon_id(src_unit) : pk::get_ground_weapon_id(src_unit);
			pk::equipment@ equipment = pk::get_equipment(weapon_id);
            
            
            // ��ǥ�������� �̵� ��� ȹ��
            array<pk::point> steps;
            // �߰��̵�����
            auto paths = pk::get_path(src_unit, src_unit.pos, dst_pos);
            
            // �߰��̵�����
            for (int i = 0; i < int(paths.length); i++)
            {
                @hex = pk::get_hex(paths[i]);
                terrain_id = hex.terrain;
                weapon_id = pk::is_water_terrain(terrain_id) ? pk::get_sea_weapon_id(src_unit) : pk::get_ground_weapon_id(src_unit);
                @ equipment = pk::get_equipment(weapon_id);

                steps.insertLast(paths[i]); //�߰��̵����� �߰�
                if (i > 0)
                    cost_sum += equipment.movement_cost[terrain_id];
                
            }
            
            // �����̵�����
            @hex = pk::get_hex(dst_pos);
            terrain_id = hex.terrain;
            weapon_id = pk::is_water_terrain(terrain_id) ? pk::get_sea_weapon_id(src_unit) : pk::get_ground_weapon_id(src_unit);
            @ equipment = pk::get_equipment(weapon_id);

            steps.insertLast(dst_pos);  //�����̵����� �߰�
            cost_sum += equipment.movement_cost[terrain_id];
        
            // �δ� ���౺ ����
            if (steps.length != 0)
            {
                // ���� �δ� �跫 ���� ���� ȿ��
                if (pk::is_in_screen(src_pos_))
                {
                    //pk::play_se(0x39, src_pos_);
                    //pk::create_effect(0x3a, src_pos_);
                    switch(pk::rand(2))
                    {
                        case 0: pk::play_voice(0x1A, pk::get_person(src_unit.leader)); break; // ���� : ����_�̵�
                        case 1: pk::play_voice(0x1B, pk::get_person(src_unit.leader)); break; // ���� : ����_�̵�
                    }
                }
                
                pk::say(pk::encode("� ������ �����϶�"), pk::get_person(src_unit.leader));
                pk::move(src_unit, steps); // ��ü��� �ϰ��̵�
                
                // [�̵���λ� �̵� cost] x 50%] ��ŭ ��� �Ҹ�
                pk::add_energy(src_unit, -int(0.50f * cost_sum), true);
                // ������ 5% x [�̵���λ� �̵� cost]/[�� �̵���] ��ŭ ���� ��Ż
                pk::add_troops(src_unit, -int(0.05f * src_unit.troops * cost_sum / movement), true);
                
            }
            
            // �ൿ�Ϸ�
			src_unit.action_done = true;
			if (int(pk::option["San11Option.EnableInfiniteAction"]) != 0)
				src_unit.action_done = false;
            

			return true;
		}
        
        
        
        
        //---------------------------------------------------------------------------
        // �跫_��� (�ﱹ��10 ������)
        //---------------------------------------------------------------------------

		string getText_�跫_���()
        {
			return pk::encode(pk::format("��� ({})", func_stragety_cost(ENERGY_COST_���)));
        }
        
		string getDesc_�跫_���()
		{
            if (src_unit.weapon > ����_���� and !pk::is_in_water(src_unit))
                return pk::encode("���� ������ ������ �� �ֽ��ϴ�");
			else if (src_unit.weapon == ����_�ְ� and pk::is_in_water(src_unit))
                return pk::encode("�ְ��� ������ �� �����ϴ�");
			else if (src_unit.energy < ENERGY_COST_���)
				return pk::encode("����� �����մϴ�");
			else
				return pk::encode(pk::format("����� ����Ͽ� ���� ����մϴ� (��� {} �Ҹ�)", ENERGY_COST_���));
		}
        
        bool isVisible_�跫_���()
		{
            if (pk::is_campaign()) return false;
            //if (src_unit.weapon > ����_���� and !pk::is_in_water(src_unit)) return false;
            //else if (src_unit.weapon == ����_�ְ� and pk::is_in_water(src_unit)) return false;
            return true;
        }

		bool isEnabled_�跫_���()
		{
            if (src_unit.weapon > ����_���� and !pk::is_in_water(src_unit)) return false;
            else if (src_unit.weapon == ����_�ְ� and pk::is_in_water(src_unit)) return false;
            return getTargets_�跫_���().length > 0;
		}
        
		pk::array<pk::point_int> getTargets_�跫_���()
		{
            int movement = int(MOVEMENT_���౺ * src_unit.attr.stat[�δ�ɷ�_�̵�]);
            
            // �̵� ��ǥ ���� ȹ��
            pk::array<pk::point_int> target_pos;
			auto range = pk::get_movable_pos(src_unit, src_pos_, movement); // �̵������� ��θ� ȹ��
            for (int i = 0; i < int(range.length); i++)
			{
                auto arr = pk::range(range[i], 1, 1);
                for (int j = 0; j < int(arr.length); j++)
                {
                    pk::unit@ target_unit = pk::get_unit(arr[j]);
                    if (target_unit !is null and pk::is_enemy(src_unit, target_unit) and pk::is_valid_pos(getEmptyPos(arr[j])))
                        target_pos.insertLast(pk::point_int(arr[j], 0));
                }
			}
            return target_pos;
		}
        
		pk::point getEmptyPos(pk::point dst_pos)
		{
            pk::point EmptyPos = -1;
            int pos_range = 0;
            
			auto arr = pk::range(dst_pos, 1, 1);
			for (int i = 0; i < int(arr.length); i++)
			{
				pk::hex@ hex = pk::get_hex(arr[i]);
				if (pk::is_enabled_terrain(hex.terrain) and !hex.has_building and !hex.has_unit and pos_range <= pk::get_distance(src_pos_, arr[i]) )
                {
                    pos_range = pk::get_distance(src_pos_, arr[i]);
                    EmptyPos = arr[i];
                }
			}
			return EmptyPos;
		}
        
        bool handler_�跫_���(pk::point dst_pos)
		{
            pk::unit@ target_unit = pk::get_unit(dst_pos);
            
            // ��� ���δ� �ֺ� �ָ��ִ� �� ĭ ȹ��
            pk::point emptyPos = getEmptyPos(dst_pos);
            
            array<pk::point> steps;
            if (pk::is_valid_pos(emptyPos))
            {
                // ����δ� ��� ����
                pk::add_energy(src_unit, -func_stragety_cost(ENERGY_COST_���), true);
                
                if (pk::is_in_screen(src_pos_))
                {
                    pk::play_se(0x39, src_pos_);
                    pk::create_effect(0x3a, src_pos_);
                }
                
                int stat_delta = 100;
                if (target_unit.leader < ����_���� or target_unit.leader > ����_����)
                    stat_delta = pk::max(0, src_unit.attr.stat[�δ�ɷ�_����] - target_unit.attr.stat[�δ�ɷ�_����]);
                
                if (func_priority(dst_pos) or pk::rand_bool(pk::min(100, 40 + pk::max(0, stat_delta)) )
                    or (src_unit.has_skill(Ư��_�޽�) and !pk::is_in_water(src_unit)) 
                    or (src_unit.has_skill(Ư��_����) and pk::is_in_water(src_unit)) )
                {
                    if (pk::is_in_screen(src_pos_))
                    {
                        switch(pk::rand(2))
                        {
                            case 0: pk::play_voice(0x1C, pk::get_person(src_unit.leader)); break; // ���� : ����_����
                            case 1: pk::play_voice(0x1D, pk::get_person(src_unit.leader)); break; // ���� : ����_����
                        }
                    }
                    
                    //---------------------------------------------
                    // �д� �ӽ� �����Ͽ� �����ϴ� ���
                    pk::person@ src_leader = pk::get_person(src_unit.leader);
                    pk::person@ attacker = pk::get_person(����_����);
                    
                    pk::force@ force = pk::get_force(src_unit.get_force_id());
                    int district_num = pk::get_district_id(force, 1);
                    
                    // �д� ���� ����
                    pk::set_district(attacker, district_num); 
                    attacker.mibun = �ź�_�Ϲ�;
                    attacker.birth = pk::get_year() - 30;
                    attacker.death = pk::min(353, attacker.birth + 99);
                    attacker.appearance = pk::get_year() - 10;
                    // �ɷ�ġ : ������ 80%
                    attacker.base_stat[����ɷ�_���] = int(1.0f * src_leader.stat[����ɷ�_���]);
                    attacker.base_stat[����ɷ�_����] = int(1.0f * src_leader.stat[����ɷ�_����]);
                    attacker.base_stat[����ɷ�_����] = int(1.0f * src_leader.stat[����ɷ�_����]);
                    attacker.base_stat[����ɷ�_��ġ] = int(1.0f * src_leader.stat[����ɷ�_��ġ]);
                    attacker.base_stat[����ɷ�_�ŷ�] = int(1.0f * src_leader.stat[����ɷ�_�ŷ�]);
                    
                    int ground_weapon = pk::get_ground_weapon_id(src_unit);
                    
                    // �ɷ�ġ �ݿ�.
                    attacker.update();
                    
                    int troops = src_unit.troops;
                    int gold = 0;
                    int food = troops;
                    
                    pk::unit@ atk_unit = pk::create_unit(pk::get_building(pk::get_service(src_unit)), attacker, null, null, troops, ground_weapon, ����_�ְ�, gold, food, emptyPos);
                    pk::set_energy(atk_unit, src_unit.energy);  // ���δ� ��°� �ݿ�
                    
                    if (pk::is_in_screen(emptyPos))
                        pk::create_effect(0x4b, emptyPos);
                    
                    pk::attack(atk_unit, target_unit);  // �� �δ뿡 ���� ����
                    
                    if(pk::rand_bool(30))       // 30% Ȯ���� �� �δ� ȥ��
                        pk::set_status(target_unit, atk_unit, �δ����_ȥ��, 2, true);
                    
                    pk::add_troops(src_unit, -(troops - atk_unit.troops)/2, true);  // �д� ���� ���� ��ȯ
                    
                    if (!pk::is_alive(atk_unit))
                        pk::reset(attacker);
                    
                    pk::add_troops(atk_unit, -atk_unit.troops, false);
                    if (atk_unit.troops <= 0)
                    {
                        pk::kill(atk_unit);                 // �д� �ػ�
                        pk::reset(attacker);
                    }
                    
                    //---------------------------------------------
                    
                    if (pk::is_in_screen(src_pos_))
                    {
                        switch(pk::rand(4))
                        {
                            case 0: pk::say(pk::encode("�̷�. ����ߴ�"), pk::get_person(target_unit.leader)); break;
                            case 1: pk::say(pk::encode("���� ����ΰ�"), pk::get_person(target_unit.leader)); break;
                            case 2: pk::say(pk::encode("��ü ��� ��Ÿ�� ���̳�"), pk::get_person(target_unit.leader)); break;
                            case 3: pk::say(pk::encode("������ ���ٵ���"), pk::get_person(target_unit.leader)); break;
                        }
                        switch(pk::rand(4))
                        {
                            case 0: pk::say(pk::encode("����� �����߱�"), pk::get_person(src_unit.leader)); break;
                            case 1: pk::say(pk::encode("���� �Ĺ��� �����ϴ� �Ŵ�"), pk::get_person(src_unit.leader)); break;
                            case 2: pk::say(pk::encode("������"), pk::get_person(src_unit.leader)); break;
                            case 3: pk::say(pk::encode("���� ������ �������±�"), pk::get_person(src_unit.leader)); break;
                        }
                    }
                    
                    // �ⱳ����
                    pk::add_tp(pk::get_force(src_unit.get_force_id()), 20, dst_pos);
                    // �ɷ°���ġ
                    pk::add_stat_exp(src_unit, ����ɷ�_���, 4);
                    // ����
                    pk::add_kouseki(src_unit, 100);
                }
                else
                {
                    if (pk::is_in_screen(src_pos_))
                    {
                        switch(pk::rand(2))
                        {
                            case 0: pk::play_voice(0x45, pk::get_person(src_unit.leader)); break; // ���� : ����_�跫����
                            case 1: pk::play_voice(0x46, pk::get_person(src_unit.leader)); break; // ���� : ����_�跫����
                        }
                        pk::say(pk::encode("��� ������ �̹� �����ߴ�"), pk::get_person(target_unit.leader));
                        pk::say(pk::encode("���� ��ġ ä���°�"), pk::get_person(src_unit.leader));
                    }
                }
            }
            
            // �ൿ�Ϸ�
			src_unit.action_done = true;
			if (int(pk::option["San11Option.EnableInfiniteAction"]) != 0)
				src_unit.action_done = false;
            
            return true;
        }
        
        
        
        
        //---------------------------------------------------------------------------
        // �跫_����
        //---------------------------------------------------------------------------
        
		int getChance_����(pk::point dst_pos)
		{
			return 100;
		}
        
		string getText_�跫_����()
		{
			return pk::encode(pk::format("���� ({})", func_stragety_cost(ENERGY_COST_����)));
		}

		string getDesc_�跫_����()
		{
			if (src_unit.energy < func_stragety_cost(ENERGY_COST_����))
				return pk::encode("����� �����մϴ�");
            else if (getTargets_�跫_����().length == 0)
				return pk::encode("���� ������ ������ �����ϴ�");
			else
				return pk::encode("���� ������ �����մϴ�");
		}
        
        
        bool isVisible_�跫_����()
		{
            if (pk::is_campaign()) return false;
            return true;
		}
               
               
		bool isEnabled_�跫_����()
		{
			if (src_unit.energy < func_stragety_cost(ENERGY_COST_����)) return false;
			return getTargets_�跫_����().length > 0;
		}
        
		pk::array<pk::point_int> getTargets_�跫_����()
		{
			pk::array<pk::point_int> targets;
            auto range = pk::range(src_pos_, 1, 1);
			for (int i = 0; i < int(range.length); i++)
			{
                pk::hex@ hex = pk::get_hex(range[i]);
				if (pk::is_enabled_terrain(hex.terrain) and hex.terrain == ����_�� 
                    and get_height_diff(src_pos_, range[i]) >= 0 
                    and !hex.has_building and (!hex.has_unit or src_unit.pos == range[i]))
                    {
                        targets.insertLast(pk::point_int(range[i], 1));
                    }
			}
			return targets;
		}
        
        bool handler_�跫_����(pk::point dst_pos)
		{
            // ����δ� ��� ����
            pk::add_energy(src_unit, -func_stragety_cost(ENERGY_COST_����), true);
            
            if (func_priority(dst_pos) or pk::rand_bool(pk::min(100, pk::max(0, src_unit.attr.stat[�δ�ɷ�_����]))) )
            {
                // ���� ����
                pk::create_building(pk::get_facility(�ü�_����), dst_pos, src_unit.get_force_id());    
                pk::building@ building = pk::get_building(dst_pos);
                pk::complete(building);
                
                // ���� ����
                pk::attack(src_unit, pk::get_hex_object(dst_pos)); 
                
                
                if (pk::is_in_screen(src_pos_))
                {
                    switch(pk::rand(4))
                    {
                        case 0: pk::say(pk::encode("������ �����߱�"), pk::get_person(src_unit.leader)); break;
                        case 1: pk::say(pk::encode("�����̶� �̷�����"), pk::get_person(src_unit.leader)); break;
                        case 2: pk::say(pk::encode("������"), pk::get_person(src_unit.leader)); break;
                        case 3: pk::say(pk::encode("���� �� �������� ��"), pk::get_person(src_unit.leader)); break;
                    }
                }
                
                // �ⱳ����
                pk::add_tp(pk::get_force(src_unit.get_force_id()), 10, dst_pos);
                // �ɷ°���ġ
                pk::add_stat_exp(src_unit, ����ɷ�_���, 4);
                // ����
                pk::add_kouseki(src_unit, 100);
            }
            else
            {
                if (pk::is_in_screen(src_pos_))
                {
                    switch(pk::rand(2))
                    {
                        case 0: pk::say(pk::encode("������ �����ߴ°�"), pk::get_person(src_unit.leader)); break;
                        case 1: pk::say(pk::encode("������ ���� ���°�"), pk::get_person(src_unit.leader)); break;
                    }
                }
            }
            
            // �ൿ�Ϸ�
			src_unit.action_done = true;
			if (int(pk::option["San11Option.EnableInfiniteAction"]) != 0)
				src_unit.action_done = false;
            
            return true;
        }

        int get_height_diff(const pk::point &in src, const pk::point &in dst)
		{
			return pk::get_height_map(pk::hex_pos_to_height_map_pos(src) + 2).height - pk::get_height_map(pk::hex_pos_to_height_map_pos(dst) + 2).height;
		}
        
	}

	Main main;
}