/*
@������: Tester
@����: �ܱ� �ΰ�����
@����: 2.5.0

@���� : ũ���Ƚ�
2023.8.20,���ձ� �Ἲ��, ���ֺ��°�, ���ú��� ������� �ʴ������� ����
2023.8.26,���ձ� �Ἲ��, ���ֺ��°�, ���ú��� �ƴϰ� ����������

*/

			
namespace �ܱ�����
{
	///////////////////////////////////////////////////////////////////////////////
	/////////////////////////////				///////////////////////////////////
	/////////////////////////////	CUSTOMIZE	///////////////////////////////////
	/////////////////////////////				///////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	const float ��ȣ���������� = 10.0;	
	const bool �����������º� = true;	
	const int ���հἺ�Һ�Ÿ�� = 1; // 0 = �ⱳ����Ʈ, 1 = �ൿ��
	const int �߰����ռ����� = 0;		
	const bool �׻��ִ뺴������ = false;
	const bool ����_���ú��³� = true;
	const int �ּ��������¼� = 2500;
	const int �ѵ����ִ������δ�� = 15;
	const float ����_�߰����ռ����� = 0.2;
	const float �����ּҹ�Ű�� = 0.5;

	///////////////////////////////////////////////////////////////////////////////
	
	const int8 �Ӽ�_���ü� = 0;
	const int8 �Ӽ�_����� = 1;
	const int8 �Ӽ�_���� = 2;
	const int8 �Ӽ�_ž10 = 3;
	const int8 �Ӽ�_���¼��� = 4; // ������
	const int8 �Ӽ�_�������� = 5;
	const int8 �Ӽ�_�� = 6;
	const int8 �Ӽ�_���� = 7;	
	const int8 �Ӽ�_�� = 8; // ���� �Ӽ� ����
             
	const int8 �Ǵ�_�Ǵ���ü = 0;
	const int8 �Ǵ�_�Ǵܴ�� = 1;
	const int8 �Ǵ�_���� = 2;
	const int8 �Ǵ�_�������� = 3;
	const int8 �Ǵ�_���ü� = 4;
	const int8 �Ǵ�_����� = 5;
	const int8 �Ǵ�_����	= 6;
	const int8 �Ǵ�_Ȳ����ȣ���� = 7;
	const int8 �Ǵ�_��ȣ�� = 8;
	const int8 �Ǵ�_����	= 9;
	const int8 �Ǵ�_ž10 = 10;
	const int8 �Ǵ�_������ = 11;
	const int8 �Ǵ�_����������� = 12;
	const int8 �Ǵ�_�����߿���	= 13;
	const int8 �Ǵ�_������ = 14;
	const int8 �Ǵ�_�������� = 15;
	const int8 �Ǵ�_ģ�ֿ��� = 16;
	const int8 �Ǵ�_�������� = 17;
	const int8 �Ǵ�_���	= 18;
	const int8 �Ǵ�_���������ü��� = 19;
	const int8 �Ǵ�_������������� = 20;
	const int8 �Ǵ�_������������ = 21;
	const int8 �Ǵ�_����ɷ� = 22;
	const int8 �Ǵ�_���	= 23;
	const int8 �Ǵ�_�� = 24;
	
	const int8 ��������_���ü� = 0;
	const int8 ��������_����� = 1;
	const int8 ��������_���� = 2;
	const int8 ��������_�� = 3;
	
	const int8 ����� = 1;
	const int KEY = pk::hash("���հἺ");

	class Main
	{
		
		
		// ����			
		array<array<float>> �Ǵܰ���ġ(����_��, array<float>(�Ǵ�_��+1, -1.f));
		array<array<bool>> �Ǵ�ȣ��ȣ(����_��, array<bool>(�Ǵ�_��+1, true));		
		array<array<int>> ���ºΰ��Ӽ�(����_��, array<int>(�Ӽ�_��, -1)); // �߰� ���� �Ӽ� �� ����			
		array<float> �Ǵ�(�Ǵ�_��, -1.f);
		array<array<float>> ���´��Ǵ�(����_�� * ����_��, �Ǵ�);
		array<array<float>> ���´��Ǵܰ��(����_��, array<float>(����_��, 0.f));
		array<array<int8>> ���¿ܱ����(����_��, array<int8>(����_��, -1)); // ���¿ܱ��Ÿ� �ߺ�üũ��
		array<array<int8>> ���´����￩��(����_��, array<int8>(����_��, -1)); // 1: ������
		array<int8> �����߿���(����_��, -1); // 1: ������
		array<int8> �ǹ����￩��(�ǹ�_��, -1); // 1: ������
		array<int8> ���ð�迩��(�ǹ�_��, -1); // 1: ���δ밡 �Ʊ������� ���� ��
		array<array<int8>> ����������(����_��, array<int8>(����_��, -1));
		array<array<int8>> ���µ�������(����_��, array<int8>(����_��, -1));
		dictionary ��Ű�����������;
		dictionary �δ�������_���;
		array<array<int>> �������ո��(����_��, array<int>(��������_��, -1));
		array<array<int8>> ���´뼼�°Ÿ�(����_��, array<int8>(����_��, 3)); // ���� Ŭ ���� �ִ�
		
		float ������Ȯ����� = 0.6; /// 0.7	
		int8 ���������Ǵ�_���� = 6;
		int8 �δ������Ǵ�_���� = 4;
		int8 ��Ű���_���� = 6; // *10��
		float ����_ĭ�̵��� = 4.0; // �̵��� 20 ����
		bool is_���±ݺ����˻� = false;
		
		int index_���´��Ǵ� = 0;								
		int8 daysOfMonth = 0;		
		int8 �ܱ�������� = 0;
		
				
		// ���հ���		
		// ����Ȯ�� ���: �������� ���� �� ������ ���� ���� ����, ���� ���� ����, ���� �ɷ�
		// ���ռ����� set_���´��Ǵ�() �Ŀ� ���������� ������ ���Ѵ�.
		// isBetray() ���� ���ռ����� ������ ������ ����(���ݴ�󼼷��� ����)  ����.
		array<float> prob_������(����_��, -2.f);
		array<pk::int_int> prob_������_desc(); // ������Ȯ���� ���� ������ ���� �迭
		array<int8> rank_���º���(47, -1);
		array<int8> rank_��������(47, -1);
		int8 ���հ����� = 0;
		array<int8> ���սõ�(����_��, -1); // ���� �õ��� ������ ���� �ߺ�����		
		int8 ���սõ�����_�ϼ� = 12;
		array<int8> ���ռ�������(����_��, -1); // ���� ������ ���ձ� ���� ���սõ� ����
		int8 ���ռ�������_�ϼ� = 40;
		array<array<int>> �������ο��ռ���();
		int8 �������� = 1;
		array<int8> �����н�(����_��, 0);
		
		// ���հ��� Ŀ�ǵ�
		// �ǹ� �޴� ����
		int menu_city_id_;
		// �ǹ� �޴� ����
		int menu_force_id_;
		// �޴� Ȱ��ȭ ����
		int8 �޴����Ȱ��ȭ = -1;
		int8 �÷��̾���� = -1;
		// array<int8> �������հἺ�ߺ��õ�(����_��, -1);		
		string ���հ��۸� = "";		
		array<int8> ����_���ռ���(����_��, -1);	
		int8 ����_���ռ�������_�ϼ� = 10;
		// ���� ��� ���
		array<int> ������������(2, -1);		
		int ���Ͱ�������� = 0;
		bool ����ȭ����� = false;
		
		int �ʿ��ൿ�� = 100;    // (�ൿ�� �ʿ䷮: �⺻  ����)
		int �ʿ�ⱳ����Ʈ = 1000; 	   // (�ⱳP �ʿ䷮: �⺻  ����)
				
		int �δ����_�� = 2000;
		float �δ����_�������� = 2.0;
		array<int> ������������(����_��, 0); // ���հἺ�� ���º� ��������
		float ���ֹ��_player = 4.0; // ���ձ� ���º񱳽� �� ��� �÷��̾� �ִ� ���
		array<int8> ��ź�����(����_��, -1);	
		int8 ��ź�����_�ϼ� = 10;		
		
		int line_bigO = 0;
		
		pk::func112_t@ prev_func112_;
		
		
		Main()
		{
			init();
		}
		
		
		// �ʱ�ȭ
		void init()
		{			
			TestLOG();
		
			pk::bind(104, pk::trigger104_t(onScenarioEnd));
			pk::bind(107, pk::trigger107_t(onNewDay));
			pk::bind(108, pk::trigger108_t(onNewMonth));
			pk::bind(109, pk::trigger109_t(onNewSeason));
			pk::bind(110, pk::trigger110_t(onNewYear));
			pk::bind(111, pk::trigger111_t(onTurnStart));
			pk::bind(112, pk::trigger112_t(onTurnEnd));
			pk::bind(120, pk::trigger120_t(onDrawGame));
			
			@prev_func112_ = cast<pk::func112_t@>(pk::get_func(112));
			pk::reset_func(112);
			pk::set_func(112, pk::func112_t(func112));
			
			initMenuItem();
		}	
		
		void TestLOG()
		{
			// util.prnt("string to int ["+parseInt("2.0")+"]");
			// array<string> arr = "asdfsf|sdfsdf|sdfsdf|".split("|");
			// util.prnt("splited string count=["+arr.length+"] [3]=["+arr[2]+"]");
			// util.prnt("neighborMap length yangpyeong=["+neighborMap.�����ǹ�[�ǹ�_����].length+"] bukpyeong=["+neighborMap.�����ǹ�[�ǹ�_����].length+"]");

		}
		
		void initMenuItem()
		{
			
			// �޴� ����			
			pk::menu_item item;
			item.menu = 103;
			item.init = pk::building_menu_item_init_t(initMenu);
			item.is_visible = pk::menu_item_is_visible_t(isMenuVisible);
			item.get_text = pk::menu_item_get_text_t(getMenuText);
			item.is_enabled = pk::menu_item_is_enabled_t(isEnabled);
			item.get_desc = pk::menu_item_get_desc_t(getMenuDesc);
			// item.get_image_id = pk::menu_item_get_image_id_t(getMenuImageID);
			item.handler = pk::menu_item_handler_t(menuHandler);
			pk::add_menu_item(item);
			
		}
		
		pk::int_bool func112(const pk::alliance_cmd_info &in info)
		{
			// util.prnt("reset func112 info actor=["+info.actor.get_force_id()+"] target=["+info.target.get_id()+"]");
			
			// AI �� �÷��̾�� ���Ϳ�û��
			if(!pk::get_force(info.actor.get_force_id()).is_player() and info.target.is_player()){
				������������[0] = info.actor.get_force_id();
				������������[1] = info.target.get_id();
				����ȭ����� = true;
			}
			
			// ���� �ڵ鷯�� �ִٸ� ü��.
			if (prev_func112_ !is null){
				return prev_func112_(info);
			}
			return cast<pk::func112_t@>(pk::get_func(112, true))(info);	
		}
		
		void onDrawGame()
		{
			// cursorOnCity();
			onAllianceCommandCallback();			
				
		}
		
		void onAllianceCommandCallback(){
			if(!����ȭ�����)return;
			// pk::printf(pk::encode("delay=["+���Ͱ��������+"] \n"));
			
			���Ͱ�������� += 1;
			if(���Ͱ�������� > 3){						
				����ȭ����� = false;
				���Ͱ�������� = 0;
				// ���⼭ ���� ��� ó��
				bool ���ͼ������� = !pk::is_enemy(������������[0], ������������[1]);
				
				if(!���ͼ�������){
					pk::add_relations(pk::get_force(������������[0]), ������������[1], -40);	
				}				
			}			
			
		}
		
		// ���� �ߺ� ����Ʈ ����
		int cursor_city_id = -1; 
		
		void cursorOnCity()
		{		
			pk::point cursor_pos = pk::get_cursor_hex_pos();
			if(!pk::is_valid_pos(cursor_pos)) return;
			pk::hex@ hex = pk::get_hex(cursor_pos);
			int terrain_id = hex.terrain;
			if(terrain_id != ����_����){cursor_city_id = -1; return;} // ���� �����ΰ�?
			int city_id = pk::get_city_id(cursor_pos);
			if(!pk::is_valid_city_id(city_id))return; 
			if(cursor_city_id == city_id)return; // �ߺ� ����Ʈ ���� �ΰ�?									
			pk::city@ city_cursor = pk::get_city(city_id);
			if(city_cursor.is_player())return; // �÷��̾� �����ΰ�?
			
			cursor_city_id = city_id;
			// util.prnt("cursor city_id=["+city_id+"]");
			
			string city_cursor_name = pk::decode(pk::get_name(city_cursor));
			pk::say(pk::encode("����� "+city_cursor_name+" �Դϴ�"), pk::get_person(city_cursor.taishu), city_cursor);
		}
		
		
		
		void initializeOnNewSeason(){
			
		}
		
		void initializeOnNewMonth()
		{			
			���¿ܱ���� = array<array<int8>>(����_��, array<int8>(����_��, -1));
			���ºΰ��Ӽ� = array<array<int>>(����_��, array<int>(�Ӽ�_��, -1.f));	
			rank_���º��� = array<int8>(47, -1);		
		}
		
		void initializeOnNewDay()
		{			
				
			rank_�������� = array<int8>(47, -1);	
			prob_������ = array<float>(����_��, -2.f);		
			�����߿��� = array<int8> (����_��, -1);
			�ǹ����￩�� = array<int8>(�ǹ�_��, -1);
			���ð�迩�� = array<int8>(�ǹ�_��, -1);
			���´����￩�� = array<array<int8>>(����_��, array<int8>(����_��, -1));			
			���������� = array<array<int8>>(����_��, array<int8>(����_��, -1));
			���µ������� = array<array<int8>>(����_��, array<int8>(����_��, -1));
			�������ո�� = array<array<int>>(����_��, array<int>(��������_��, -1));			
		}

		// bind
		/*
		�� ���� �����ؾ��� �����Ϳ� �� ���� ������ �����ͷ� ����
		*/
		
		void onNewYear()
		{
			// if(�ܱ�������� == 0)return;
			//pk::printf(pk::encode("onNewYear get_month=["+pk::get_month()+"]\n"));
			//pk::printf(pk::encode("Start! AnnualTribute \n"));
		}	
		
		void onNewSeason()
		{
			// if(�ܱ�������� == 0)return;
			
			//pk::printf(pk::encode("Start! AllianceAttack \n"));			
			
			// �ݳ⿡ �ѹ�
			if(pk::get_month() == 1 or pk::get_month() == 7)�������� = 0;
			
			// ���� ���� �ʱ�ȭ
			initializeOnNewSeason();
		}	

		
		void onNewMonth()
		{
			�ܱ�������� = 1;
			// pk::printf(pk::encode("onNewMonth \n"));
			
			is_���±ݺ����˻�	= false;		
			
			// �ʱ�ȭ
			initializeOnNewMonth();
			
			setForceAttributes();
					
			
		}
		
		void onNewDay()
		{					
			if(�ܱ�������� == 0)return;
			
			// pk::printf(pk::encode("onNewDay \n"));
			line_bigO = 0;			
			
			initializeOnNewDay();
			
			decrease_��Ű�������������();
			decrease_�δ�������_���();
			if(!is_���±ݺ����˻�)setForceGoldFood();
			setIsAtWar();
			// util.prnt("bigO line=["+line_bigO+"] setIsAtWar");
			
			index_���´��Ǵ� = 0;
			set_���´��Ǵ�();			
			set_���´��Ǵ�_weight();
			// util.prnt("bigO line=["+line_bigO+"] index_forcejudge=["+index_���´��Ǵ�+"]  set_forcejudge");
			AddRelationValue();
			// util.prnt("bigO line=["+line_bigO+"] AddRelationValue");
			
			// AnnualTribute
				
			set_rank_��������();
			set_prob_������();				
			// util.prnt("bigO line=["+line_bigO+"] allianceAttack_Probability");
			search_������();
			// util.prnt("bigO line=["+line_bigO+"] search_alliance_enemy");
			
			
		}
		
		void onTurnStart(pk::force@ force){
			if(�ܱ�������� == 0)return;				
			if(isIminzoku(force))return; //�̹��� ����	
			
			// util.prnt("onTurnStart kunshu=["+force.kunshu+"]");
			
			// �޴� ���� ����
			if (force.is_player()){				
				pk::list<pk::city@> cityList = pk::get_city_list(force);
				pk::building@ building0 = pk::city_to_building(cityList[0]);
				initMenu(building0);
			}
			decrease_�������սõ�����(force.get_id());		
			decrease_���սõ�����(force.get_id());
			decrease_���ռ�������(force.get_id());
			decrease_��ź�����(force.get_id());
			
			if(�������� != 1)AnnualTribute(force);			
			if (force.is_player()){
				�޴����Ȱ��ȭ = 1;
				// decrease_�������հἺ�ߺ��õ�();
			}		
			BetrayalAttack(force);// ��Ű���
			
		}
		
		void onTurnEnd(pk::force@ force)
		{
			// util.prnt("onTurnEnd kunshu=["+force.kunshu+"]");
			if (force.is_player())�޴����Ȱ��ȭ = 0;
			
		}
		
		
		
		
		
		
		
		
		
		
		void onScenarioEnd()
		{
			// util.prnt("Scenario End.");
			DeinitLoop();
			�޴����Ȱ��ȭ = -1;
			�ܱ�������� = 0;
			
		}
		
		void DeinitLoop()
		{
			��Ű�����������.deleteAll();
			�δ�������_���.deleteAll();
			���սõ� = array<int8>(����_��, -1);
			���ռ������� = array<int8>(����_��, -1);	
			����_���ռ��� = array<int8>(����_��, -1);
			��ź����� = array<int8>(����_��, -1);
			�������ο��ռ��� = array<array<int>>();	
			�����н� = array<int8>(����_��, 0);
			
		}
		
		void decrease_��Ű�������������(){			
			for (int i=0; i<��Ű�����������.getKeys().length; i++)
			{
				// line_bigO++;
				string key = ��Ű�����������.getKeys()[i];
				int delay = int(��Ű�����������[key]);
				��Ű�����������[key] = delay - 1;	
				// util.prnt("delay mod key=["+key+"] val=["+int(��Ű�����������[key])+"]");
				if(delay <= 1)��Ű�����������.delete(key);				
			}
			
		}
		void decrease_�δ�������_���(){			
			for (int i=0; i<�δ�������_���.getKeys().length; i++)
			{
				// line_bigO++;
				string key = �δ�������_���.getKeys()[i];
				int days = int(�δ�������_���[key]);
				�δ�������_���[key] = days - 1;	
				// util.prnt("days mod key=["+key+"] val=["+int(�δ�������_���[key])+"]");
				if(days <= 1){
					// util.prnt("days del key=["+key+"] val=["+int(�δ�������_���[key])+"]");	
					�δ�������_���.delete(key);					
				}			
			}
			
		}
		
		void decrease_���ռ�������(int force_id){
			
			
			// ���ռ������� +�Ѵ�
			if(���ռ�������[force_id] <= 0 ){
				���ռ�������[force_id] = -1;  
				// util.prnt("alliance_being_forces count=" + �������ο��ռ���.length);
				if(contain_�������ο��ռ���(force_id)){					
					�������ο��ռ���.removeAt(0);
					// util.prnt("remove alliance_being_forces count=" + �������ο��ռ���.length);
				}
			}
			else if(���ռ�������[force_id] > 0){
				���ռ�������[force_id] -= 1; 
				// util.prnt("allianceAttackDelay force_kunshu=["+pk::get_force(force_id).kunshu+"] delay=["+���ռ�������[force_id]+"] ");
				
			}
			
		}
		
		void decrease_���սõ�����(int force_id){			
			if(���սõ�[force_id] >= 0){
				���սõ�[force_id] -= 1; 
				// util.prnt("try_allianceAttack force_kunshu=["+pk::get_force(force_id).kunshu+"] delay=["+���սõ�[force_id]+"] ");
			}
		}
		void decrease_�������սõ�����(int force_id){			
			if(����_���ռ���[force_id] >= 0){
				����_���ռ���[force_id] -= 1; 
				// util.prnt("UserAllianceAttack force_kunshu=["+pk::get_force(force_id).kunshu+"] delay=["+����_���ռ���[force_id]+"] ");
			}
		}
		void decrease_��ź�����(int force_id){			
			if(��ź�����[force_id] >= 0){
				��ź�����[force_id] -= 1; 
				// util.prnt("Send_Sasin force_kunshu=["+pk::get_force(force_id).kunshu+"] delay=["+��ź�����[force_id]+"] ");
			}
		}
		
		bool contain_�������ο��ռ���(int force0_id){
			if(�������ο��ռ���.length == 0)return false;
			string str = "force0_id= ["+force0_id+"] ";
			for (int i = 0; i < �������ο��ռ���[0].length; i++){
				str += �������ο��ռ���[0][i] + ", ";
				// util.prnt("allianceBeingForces0 force0_id=["+force0_id+"] value=["+�������ο��ռ���[0][i]+"] kunshu=["+pk::get_force(�������ο��ռ���[0][i]).kunshu+"] ");
				if(�������ο��ռ���[0][i] == force0_id)return true;
			}
			// util.prnt(str);
			return false;
		}
		
		
		
		
		
		// ���� �䱸
		void AnnualTribute(pk::force@ force0)
		{
			if(!force0.is_player())return;
			
			int force0_id = force0.get_id();
			
			// ���� �䱸 ���� ã��
			int force_threat_id = -1;
			int troops_temp = -1;
			float dislike = 0.f; // ����
			for (int i = 0; i < index_���´��Ǵ�; i++){
				// ����
				int force_u_id = int(���´��Ǵ�[i][�Ǵ�_�Ǵ���ü]);
				// ��
				int force_i_id = int(���´��Ǵ�[i][�Ǵ�_�Ǵܴ��]);					
				if(force0_id != force_i_id)continue;
				if(pk::get_force(force_u_id).is_player())continue;
				if(���´��Ǵ�[i][�Ǵ�_������] == 1)continue;				
				if(���´��Ǵ�[i][�Ǵ�_���ü�] > 0)continue; //��� ������ ������ ���� ��� �н�
				
				// ������ ���� ��������.
				float want = ���´��Ǵ�[i][�Ǵ�_���];

				//pk::person@ kunshu = pk::get_person(pk::get_force(force_u_id).kunshu);
				//pk::printf(pk::encode("AnnualTribute() force_u_id=["+force_u_id+"] force_u_kunshu=["+kunshu.get_id()+"] force_u_want_me=["+want+"] \n"));
				
				
				if(want > 0)continue;
				
				// ���� �䱸 ���� ���ϱ�
				if(want < dislike){
					force_threat_id = force_u_id;				
					dislike = want;
				}
				
				/*
				// ���� �� ������ ���� ���� ����
				int troops_u = ���ºΰ��Ӽ�[force_u_id][�Ӽ�_����];
				if(troops_temp < troops_u){
					force_threat_id = force_u_id;				
					dislike = want;
				}
				troops_temp = pk::max(troops_u, troops_temp);
				*/
				
				
			} // end - for
			
			//pk::printf(pk::encode("AnnualTribute force_threat_id=["+force_threat_id+"] pass_tribute=["+�����н�[force_threat_id]+"] \n"));
			
			if(force_threat_id == -1){ �������� = 1; return; }			
			if(�����н�[force_threat_id] > 0){ �����н�[force_threat_id] -= 1; �������� = 1; return; }  
			
			
			pk::force@ force_threat = pk::get_force(force_threat_id); // �䱸����
			
			float quantity0 = dislike / ( pk::max(���ºΰ��Ӽ�[force0_id][�Ӽ�_���ü�], 2) );	
			
			// �Ÿ��� ���� 
			quantity0 = quantity0 / float(���´뼼�°Ÿ�[force0_id][force_threat_id] + 1);
			
			float multiplier_quantity = quantity0;
			
			
			
			// ���� �� ���ϱ�
			int tribute_quantity_troops = abs(int(���ºΰ��Ӽ�[force0_id][�Ӽ�_����] * multiplier_quantity));;
			int tribute_quantity_food = abs(int(���ºΰ��Ӽ�[force0_id][�Ӽ�_����] * multiplier_quantity));;
			int tribute_quantity_gold = abs(int(���ºΰ��Ӽ�[force0_id][�Ӽ�_��]	* multiplier_quantity));;
						
			
			// ���� �̺�Ʈ ��
			s_pat_force1_id = force_threat_id;
			s_pat_force0_id = force0_id;
			s_pat_tribute_troops = tribute_quantity_troops;
			s_pat_tribute_food = tribute_quantity_food;
			s_pat_tribute_gold = tribute_quantity_gold;
			
			pk::scene(pk::scene_t(Scene_AnnualTribute));	
			
			
			// 0: ��������(�������), 1: ����, 2: �����ı�, 3: ��������, 4: �����й�
			int result_scene = s_pat_result;	
			
			if(result_scene == 0){		
			
				pk::add_relations(force0, force_threat_id, 50 );	
				
				// ���� �縸ŭ �÷��̾� �ڿ� �Ҹ�. ���ÿ��� ���̳ʽ�
				ModifySupplyForTribute(force0, force_threat, multiplier_quantity);
			}
			else if(result_scene == 2){
				// �ı�
				pk::set_relations(force0, force_threat_id, 0);
				pk::unally(force0, force_threat_id);
				pk::add_relations(force0, force_threat_id, -100);
				
			}
			else if(result_scene == 3){
				�����н�[force_threat_id] += 2;
			}
			else if(result_scene == 4){
				ModifySupplyForTribute(force0, force_threat, multiplier_quantity);
			}
			
			// if(����� > 0)pk::printf(pk::encode("---------------------------------------------------------------------------\n"));
			
			
			�������� = 1;
			
		}
		
		void ModifySupplyForTribute(pk::force@ force, pk::force@ force_threat, float multiplier_negative)
		{
			int gold = 0;
			int food = 0;
			int troops = 0;
			
			//log
			//pk::printf(pk::encode("ModifySupplyForTribute multiplier_negative=["+multiplier_negative+"]"));
			
			// ���� ���
			pk::list<pk::city@> city_list = pk::get_city_list(force);			
			
			for (int i = 0; i < city_list.count; i++)
			{				
				auto building = pk::city_to_building(city_list[i]);
				if (!pk::is_alive(building) or !pk::is_valid_force_id(building.get_force_id()))continue;
				
				int aGold, aFood, aTroops;
				
				pk::add_troops(building, aGold = int(pk::get_troops(building) * multiplier_negative), true);
				pk::add_food(building, aFood = int(pk::get_food(building) * multiplier_negative), true);
				pk::add_gold(building, aTroops = int(pk::get_gold(building) * multiplier_negative), true);
				
				gold += aGold;
				food += aFood;
				troops += aTroops;
				
				
				
				//pk::printf(pk::encode("present troops building=["+building.get_id()+"] get_troops=["+pk::get_troops(building)+"] add_troops=["+int(pk::get_troops(building) * multiplier_negative)+"]\n"));
				
			}
			
			
			// ���� ����
			pk::list<pk::city@> city_threat_list = pk::get_city_list(force_threat);			
			
			for (int j = 0; j < city_threat_list.count; j++)
			{				
				auto building = pk::city_to_building(city_threat_list[j]);
				if (!pk::is_alive(building) or !pk::is_valid_force_id(building.get_force_id()))continue;
				
				pk::add_troops(building, int(abs(troops) / city_threat_list.count), true);
				pk::add_food(building, int(abs(food) / city_threat_list.count), true);
				pk::add_gold(building, int(abs(gold) / city_threat_list.count), true);
				
				//pk::printf(pk::encode("benefit troops building=["+building.get_id()+"] get_troops=["+pk::get_troops(building)+"] add_troops=["+int(abs(troops) / city_threat_list.count)+"]\n"));
				
			}
			
			//pk::printf(pk::encode("-----------------------------------------------------------------------\n"));
		}
		
		
		
		int s_pat_force1_id = -1;
		int s_pat_force0_id = -1;
		int s_pat_tribute_troops = -1;
		int s_pat_tribute_food = -1;
		int s_pat_tribute_gold = -1;
		int s_pat_result = 0; // 0: ��������, 1: ����, 2: �����ı�, 3: ��������, 4: �����й�
		
		void Scene_AnnualTribute()
		{
			
			pk::fade(0);
			pk::sleep();
			pk::background(2);
			pk::fade(255);
			
			pk::force@ force1 = pk::get_force(s_pat_force1_id);
			pk::force@ force0 = pk::get_force(s_pat_force0_id);
			
			pk::person@ force0_kunshu = pk::get_person(force0.kunshu);
			pk::person@ force0_gunshi = pk::get_person(force0.gunshi);
			pk::person@ force0_teller = pk::is_alive(force0_gunshi) ? force0_gunshi : force0_kunshu;
									
			pk::person@ force1_kunshu = pk::get_person(force1.kunshu);
			pk::person@ force1_gunshi = pk::get_person(force1.gunshi);
			pk::person@ force1_emissary = pk::get_person(����_����);
			pk::person@ force1_teller = pk::is_alive(force1_gunshi) ? force1_gunshi : force1_emissary;

			string force0_kunshu_name = pk::decode(pk::get_name(force0_kunshu));			
			string force1_kunshu_name = pk::decode(pk::get_name(force1_kunshu));
			
			string force1_talk0 = "\x1b[1x"+force1_kunshu_name+"\x1b[0x�Բ�����, \n�Ͱ��� ������ ���� �� �ֵ��� ��ȣ�Ͽ� �� ����� �����ϼ̴�. ���� ���ο� �������� ���Ǹ� �ذ� ȣ�Ǹ� �������ٸ�, ���� �� ���� �ٽ����� ���ֶ� �� �� �ְڴ°�. ";
			pk::message_box(pk::encode(force1_talk0), force1_teller);
			
			
			pk::cutin(20);
			
			string force0_talk0 = "�츮 \x1b[1x"+force0_kunshu_name+"\x1b[0x����, \n�ϼ����� �ֿ켱���� ���並 ���ѿԼ�. ������ �� �� ��� ��Ų ���� �������� �ϴ�, ������ ������ �ٸ��ϱ�?";
			pk::message_box(pk::encode(force0_talk0), force0_teller);
			
			s_pat_result = pk::choose(
			pk::encode("���� �䱸: \x1b[16x�� \x1b[18x"+s_pat_tribute_gold+" \x1b[16x���� \x1b[18x"+s_pat_tribute_food+" \x1b[16x���� \x1b[18x"+s_pat_tribute_troops), 
			{ pk::encode("���� ���"), pk::encode("��     ��"), pk::encode("���� �ı�") }
			);
			
			if( s_pat_result == 0){
				string force1_talk1 = "\x1b[1x"+force1_kunshu_name+" "+force0_kunshu_name+" \x1b[0x������ �����Ͽ�.";
				pk::message_box(pk::encode(force1_talk1), force1_teller);
			}
			else if( s_pat_result == 2){
				string strFormated = "\x1b[1x{}\x1b[0x"+hanFix.return_chosa(force1_kunshu_name,3)+" \x1b[1x{}\x1b[0x"+hanFix.return_chosa(force0_kunshu_name,2)+" ������ \x1b[16x�ı�\x1b[0x�߽��ϴ�";				
				pk::message_box(pk::encode(pk::format(strFormated, force1_kunshu_name, force0_kunshu_name )), pk::get_person(����_����));
			}
			
			if(s_pat_result != 1){ pk::background(-1); return; }
			
			// ���� ���� 
			// �̱�� 3, ���� 4
			s_pat_result = pk::debate(force0_teller, force1_teller, true, false).first + 3;
			
			if( s_pat_result == 3){
				string force0_talk1 = "�� ���� ����� �ٽ� �� ���� ���� ���Դϴ�.";
				pk::message_box(pk::encode(force0_talk1), force0_teller);
			}
			else if( s_pat_result == 4){
				string force1_talk1 = "�������� �������� ������ ���� ���̴�";
				pk::message_box(pk::encode(force1_talk1), force1_teller);
			}
			
			pk::background(-1);
			
		}
		
		
		
		void setJudgeWeight(pk::force@ force0)
		{
			
			int force0_id = force0.get_id();
			int force0_kunshu_id = force0.kunshu;
			if(�Ǵܰ���ġ[force0_id][�Ǵ�_����] == force0_kunshu_id)return;
			
			pk::person@ person_kunshu = pk::get_person(force0_kunshu_id);
			
			// 0 �� ��� ����.
			�Ǵܰ���ġ[force0_id][�Ǵ�_����] = force0_kunshu_id;
			�Ǵܰ���ġ[force0_id][�Ǵ�_�Ǵ���ü] = 0.f;
			�Ǵܰ���ġ[force0_id][�Ǵ�_�Ǵܴ��] = 0.f;
			�Ǵܰ���ġ[force0_id][�Ǵ�_��������] = 1.f * (��������_�� - person_kunshu.local_affiliation - 1);
			�Ǵܰ���ġ[force0_id][�Ǵ�_���ü�] = 1.f;
			�Ǵܰ���ġ[force0_id][�Ǵ�_�����] = 1.f;
			�Ǵܰ���ġ[force0_id][�Ǵ�_����] = 1.f;
			�Ǵܰ���ġ[force0_id][�Ǵ�_Ȳ����ȣ����] = 1.f;
			�Ǵܰ���ġ[force0_id][�Ǵ�_��ȣ��] = 1.f;
			�Ǵܰ���ġ[force0_id][�Ǵ�_����] = 2.f;
			�Ǵܰ���ġ[force0_id][�Ǵ�_ž10] = 1.f;
			�Ǵܰ���ġ[force0_id][�Ǵ�_������] = 1.f;
			�Ǵܰ���ġ[force0_id][�Ǵ�_�����������] = 0.f;
			�Ǵܰ���ġ[force0_id][�Ǵ�_�����߿���] = 2.f;
			�Ǵܰ���ġ[force0_id][�Ǵ�_������] = 1.f * person_kunshu.ambition;
			�Ǵܰ���ġ[force0_id][�Ǵ�_��������] = 1.f * person_kunshu.giri;
			�Ǵܰ���ġ[force0_id][�Ǵ�_ģ�ֿ���] = 3.f;
			�Ǵܰ���ġ[force0_id][�Ǵ�_��������] = 3.f;
			�Ǵܰ���ġ[force0_id][�Ǵ�_���] = 0.f;
			�Ǵܰ���ġ[force0_id][�Ǵ�_���������ü���] = 1.f;
			�Ǵܰ���ġ[force0_id][�Ǵ�_�������������] = 1.f;
			�Ǵܰ���ġ[force0_id][�Ǵ�_������������] = 1.f;
			�Ǵܰ���ġ[force0_id][�Ǵ�_����ɷ�] = 0.f;
			�Ǵܰ���ġ[force0_id][�Ǵ�_���] = 0.f;
			�Ǵܰ���ġ[force0_id][�Ǵ�_��] = 0.f;
			
			
			�Ǵ�ȣ��ȣ[force0_id][�Ǵ�_����] = true;
			�Ǵ�ȣ��ȣ[force0_id][�Ǵ�_�Ǵ���ü] = true;
			�Ǵ�ȣ��ȣ[force0_id][�Ǵ�_�Ǵܴ��] = true;
			�Ǵ�ȣ��ȣ[force0_id][�Ǵ�_��������] = false;
			// �Ǵ�ȣ��ȣ[force0_id][�Ǵ�_���ü�] = true;
			// �Ǵ�ȣ��ȣ[force0_id][�Ǵ�_�����] = true;
			// �Ǵ�ȣ��ȣ[force0_id][�Ǵ�_����] = true;
			�Ǵ�ȣ��ȣ[force0_id][�Ǵ�_Ȳ����ȣ����] = true;
			�Ǵ�ȣ��ȣ[force0_id][�Ǵ�_��ȣ��] = true;
			�Ǵ�ȣ��ȣ[force0_id][�Ǵ�_����] = false;
			// �Ǵ�ȣ��ȣ[force0_id][�Ǵ�_ž10] = true;
			�Ǵ�ȣ��ȣ[force0_id][�Ǵ�_������] = false;
			�Ǵ�ȣ��ȣ[force0_id][�Ǵ�_�����������] = true;
			�Ǵ�ȣ��ȣ[force0_id][�Ǵ�_�����߿���] = false;
			�Ǵ�ȣ��ȣ[force0_id][�Ǵ�_������] = true;
			�Ǵ�ȣ��ȣ[force0_id][�Ǵ�_��������] = false;
			�Ǵ�ȣ��ȣ[force0_id][�Ǵ�_ģ�ֿ���] = true;
			�Ǵ�ȣ��ȣ[force0_id][�Ǵ�_��������] = false;
			�Ǵ�ȣ��ȣ[force0_id][�Ǵ�_���] = false;
			// �Ǵ�ȣ��ȣ[force0_id][�Ǵ�_���������ü���] = true;
			// �Ǵ�ȣ��ȣ[force0_id][�Ǵ�_�������������] = true;
			// �Ǵ�ȣ��ȣ[force0_id][�Ǵ�_������������] = true;
			�Ǵ�ȣ��ȣ[force0_id][�Ǵ�_����ɷ�] = true;
			�Ǵ�ȣ��ȣ[force0_id][�Ǵ�_���] = false;
			�Ǵ�ȣ��ȣ[force0_id][�Ǵ�_��] = false;
			
			
		}
		
		
		// ��ȣ�� ����
		void AddRelationValue()
		{
			
			pk::list<pk::force@> force_list = pk::get_force_list(false);
			
			for (int i = 0; i < force_list.count; i++){
				if(isIminzoku(force_list[i]))continue;	
				int force0_id = force_list[i].get_id();
				for (int j = i+1; j < force_list.count; j++){
					if(isIminzoku(force_list[j]))continue;				
					int force2_id = force_list[j].get_id();
					if(force0_id == force2_id)continue;
					// line_bigO++;
					
					float force0_wantAlly = ���´��Ǵܰ��[force0_id][force2_id];
					float force2_wantAlly = ���´��Ǵܰ��[force2_id][force0_id];
					
					float wantSum = force0_wantAlly + force2_wantAlly;
					int add = wantSum * ��ȣ����������;
					add = int( add / float(���´뼼�°Ÿ�[force0_id][force2_id]) );
					
					// util.prnt("AddRelation kunshu0=["+pk::get_force(force0_id).kunshu+"] kunshu2=["+pk::get_force(force2_id).kunshu+"] wantSum=["+wantSum+"] how_far=["+���´뼼�°Ÿ�[force0_id][force2_id]+"] add_relation=["+add+"] ");
					
					// ��ȣ�� ����							
					pk::add_relations(force0_id, force2_id, add);
					
					
					if(force_list[i].is_player() and force_list[j].is_player())continue; // �÷��̾� ������ �ڵ����� Ȥ�� �ı� ���� �ʴ´�.
					
					allyUnally(force_list[i], force_list[j], wantSum, force0_wantAlly, force2_wantAlly);
					
					
				}
			}
			// util.prnt("---------------------------------------------------------------------------------");
			
		}
		
		
		
		/*
		/// ���� �� ���� ���� ��� ��
		int getAverageEnemyCityTroopsAround(pk::force@ force0, pk::building@ building0){
			
			int sumTroops = 0;
			int count = 0;
			pk::city@ city0 = pk::building_to_city(building0);
			array<int> neighbor_cities = neighborMap.��������[city0.get_id()];
			for (int i = 0; i < neighbor_cities.length; i++){
				pk::city@ neighbor_city = pk::get_city(neighbor_cities[i]);	
				int force_id = neighbor_city.get_force_id();
				if(!pk::is_alive(neighbor_city) or !pk::is_valid_force_id(force_id))continue;
				// ���ΰ�?
				if(!pk::is_enemy(force0, pk::get_force(force_id)))continue;
				sumTroops += pk::get_troops(neighbor_city);
				count++;
			}
			return int( sumTroops / float(pk::max(count, 1.0)) );
		}
		*/
		/// �� ������ ���� �������� ���ձ� �Ͽ��ΰ�?
		bool isBeingAllianceForces(int force0_id, int force2_id){
			if(�������ο��ռ���.length == 0)return false;
			for (int i = 0; i < �������ο��ռ���.length; i++){		
				bool isforce0 = false;
				bool isforce2 = false;
				for (int j = 0; j < �������ο��ռ���[i].length; j++){
					if(�������ο��ռ���[i][j] == force0_id)isforce0 = true;
					if(�������ο��ռ���[i][j] == force2_id)isforce2 = true;					
					if(isforce0 and isforce2)return true;
				}
			}
			return false;
		}
		
		/// ������ �δ���� ���°�?
		bool isUnitsAround(pk::force@ force0, pk::city@ city2)
		{
			string key = force0.get_id()+"|"+city2.get_force_id()+"|"+city2.get_id(); // ���ݼ���|��ǥ����|��ǥ����
			
			
			array<pk::point> arr = pk::range(city2.get_pos(), 1, 8);
			for (int j = 0; j < arr.length; j++)
			{
				pk::unit@ dst = pk::get_unit(arr[j]);					
				if (dst is null)continue;

				�δ�������_���.set(key, 2);
				// util.prnt("days set key=["+key+"] val=["+int(�δ�������_���[key])+"]");
				return true;
				
			}
			
			if(�δ�������_���.exists(key) and int(�δ�������_���[key]) > 0){
				// util.prnt("days chk key=["+key+"] val=["+int(�δ�������_���[key])+"]");
				return true;
			}
			else
				return false;
			
		}
		
		void BetrayalAttack(pk::force@ force0){
			
			if(force0.is_player())return; // �÷��̾� �н�
			if(�����߿���[force0.get_id()] == 1)return; // �Ʊ� ���ð� �������̸�		
			
			
			// ���� �߸� üũ
			pk::person@ kunshu0 = pk::get_person(force0.kunshu);
			if(kunshu0.ambition == �߸�_�ſ쳷��)return;			
			
			pk::list<pk::city@> force0_city_list = pk::get_city_list(force0);		
				
			array<pk::int_int> targetcity_prob; // Ÿ���ĺ����õ�_Ÿ�ٰ��ɼ�
			
			// ��ǥ���� Ž��
			// �Ʊ� ���õ�� ������ ���� Ž��
			for (int i = 0; i < force0_city_list.count; i++)
			{				
				auto force0_city = force0_city_list[i]; // ��ߵ���
				if (!pk::is_alive(force0_city) or !pk::is_valid_force_id(force0_city.get_force_id()))continue;
				
				array<int> neighbor_city2s = neighborMap.��������[force0_city.get_id()];
				for (int j = 0; j < neighbor_city2s.length; j++){
					pk::city@ city2 = pk::get_city(neighbor_city2s[j]); // Ÿ���ĺ�����
					if(!pk::is_alive(city2) or !pk::is_valid_force_id(city2.get_force_id()))continue;
					
					// �Ʊ����� ����
					if(city2.get_force_id() == force0.get_id())continue;
					
					// ���ձ������ΰ�?
					if(isBeingAllianceForces(force0.get_id(), city2.get_force_id())){
						// util.prnt("isBeingAllianceForces force0_kunshu=["+force0.kunshu+"] force2_kunshu=["+pk::get_force(city2.get_force_id()).kunshu+"]");
						continue;
					}
					
					// ������ ������ �δ���� ���°�?
					if(isUnitsAround(force0, city2))continue;
					
					// �ߺ� ���� ����
					string key = force0.get_id()+"|"+city2.get_id(); // ����|Ÿ�ٵ���
					// util.prnt("delay chk key=["+key+"] val=["+int(��Ű�����������[key])+"]");
					if(��Ű�����������.exists(key) and int(��Ű�����������[key]) > 0)continue;
					
					float prob_Ÿ�� = isBetrayForCities(force0_city.get_id(), city2.get_id(), kunshu0);					
					if(prob_Ÿ�� <= 1.0)continue;
					targetcity_prob.insertLast(pk::int_int(city2.get_id(), int(prob_Ÿ�� * 100) ));
					
				}
			}
			
			if(targetcity_prob.length == 0)return;
			// ���� �������� ���� ���� ���� �� 
			targetcity_prob.sort(function(a,b) { 				
				return a.second > b.second; 
			});
			pk::city@ target_city = pk::get_city(targetcity_prob[0].first); // ��ǥ����

			
			pk::force@ force2 = pk::get_force(target_city.get_force_id());
			pk::person@ kunshu2 = pk::get_person(force2.kunshu);			
			// util.prnt("target_city=["+target_city.get_id()+"] target_troops=["+pk::get_troops(target_city)+"] target_force_kunshu=["+force2.kunshu+"] key=["+(force0.get_id()+"|"+target_city.get_force_id()+"|"+target_city.get_id())+"] ");			
			
			// ģ�ֿ���			
			if(pk::is_like(kunshu0, kunshu2.get_id()))return;
			
			// ��ȣ��
			// if(force0.relations[force2.get_id()] >= ��ſ�ȣ������)return;
			if(!pk::rand_bool(100 - force0.relations[force2.get_id()]))return;
						
			
			// Ÿ�� ���� �Ʊ� ���� Ž��
			pk::list<pk::city@> city1_list; // ������ ���õ�
			array<int> neighbor_city1s = neighborMap.��������[target_city.get_id()];
			for (int k = 0; k < neighbor_city1s.length; k++){
				pk::city@ city1 = pk::get_city(neighbor_city1s[k]);	
				if(!pk::is_alive(city1))continue;				
				// �Ʊ������ΰ�?
				if(city1.get_force_id() != force0.get_id())continue;
												
				// �Ÿ� ����
				int ��_distance = ceil(pk::get_distance(city1.get_pos(), target_city.get_pos()) / ����_ĭ�̵���);
				if(��_distance > 6)continue;
				
				// �� �������� ������?
				if(pk::get_hp(city1) <= pk::get_max_hp(city1) / 2.0)continue;
				
				if(���ð�迩��[city1.get_id()] == 1)continue;
								
				// ������ �������� ���� �ִ°�?
				if(isAroundEnemyThreat(city1))continue;
				
				pk::building@ depart_building = pk::city_to_building(city1);
				// �δ� ���� Ƚ�� set						
				auto person_list = pk::get_idle_person_list(depart_building);
				if (person_list.count == 0)continue; // ������ �δ밡 ����
				auto total_person_list = pk::get_person_list(depart_building, pk::mibun_flags(�ź�_����, �ź�_����, �ź�_�¼�, �ź�_�Ϲ�));
				// ��� ������ ������ �ִ��� Ȯ��.
				if (total_person_list.count - person_list.count >= 2)continue;
				
				city1_list.add(city1);				
			}
			if(city1_list.count == 0)return;
			
			// �����ı�
			string force0_kunshu_name = pk::decode(pk::get_name(pk::get_person(force0.kunshu)));
			string force2_kunshu_name = pk::decode(pk::get_name(pk::get_person(force2.kunshu)));
			
			if(!pk::is_enemy(force0, force2)){
				
				pk::unally(force0, force2.get_id());
				pk::add_relations(force0, force2.get_id(), -100);
				pk::message_box(pk::encode("\x1b[1x"+force0_kunshu_name+"\x1b[0x"+hanFix.return_chosa(force0_kunshu_name,3)+" \x1b[1x"+force2_kunshu_name+"\x1b[0x"+hanFix.return_chosa(force2_kunshu_name,2)+" ������ \x1b[16x�ı�\x1b[0x�߽��ϴ�"), pk::get_person(����_����));	
			}
			else
				pk::add_relations(force0.get_id(), force2.get_id(), -50);
			
			
			// �����޼���			
			string city2_name = pk::decode(pk::get_name(target_city));
			messageBetrayalAttack(kunshu0, force2_kunshu_name, city2_name);
			
			
			//����
			pk::building@ target_building = pk::city_to_building(target_city);
			// int �Ѻδ���غ��¼� = 5000;
			for (int l = 0; l < city1_list.count; l++){
				pk::building@ depart_building = pk::city_to_building(city1_list[l]);
				// �δ� ���� Ƚ�� set						
				auto person_list = pk::get_idle_person_list(depart_building);
				// ��� ������ ������ �ִ��� Ȯ��.
				if (person_list.count == 0)continue; // ������ �δ밡 ����
								
				// ���+������ ���� ������ ����.
				person_list.sort(function(a, b)
				{
					return a.stat[����ɷ�_���] + a.stat[����ɷ�_����] > b.stat[����ɷ�_���] + b.stat[����ɷ�_����];
				});
				
				// �����δ�� ����							
				// int numUnit = pk::min(getBetrayalAttackUnitNumber(�Ѻδ���غ��¼�, target_building), person_list.count);
				// util.prnt("numUnit=["+numUnit+"] target_troops=["+pk::get_troops(target_building)+"] person_list=["+person_list.count+"]");
				
				bool isWarAt = intToBoolean(�ǹ����￩��[depart_building.get_id()]); 
				for (int o = 0; o < person_list.count; o++){
					CreateAUnit(person_list[o], depart_building, target_building, 1.0, isWarAt, o, false, {});
				}				
			}
			
			
			string key = force0.get_id()+"|"+target_city.get_id();
			��Ű�����������.set(key, ��Ű���_����);			
			// util.prnt("delay set key=["+key+"] val=["+int(��Ű�����������[key])+"]");
			
			
		}
		
		void messageBetrayalAttack(pk::person@ kunshu, string kunshu_name, string city_name){
			
			switch (kunshu.character)
			{
			case ����_�ҽ�:				
				pk::message_box(pk::encode("\x1b[1x"+kunshu_name+"\x1b[0x�� ���� \x1b[16x"+city_name+"\x1b[0x"+hanFix.return_chosa(city_name,1)+" ���ϴ� �� �ܿ��� ����̾��� �����ϼ���."), kunshu);
				break;
			case ����_����: 
				pk::message_box(pk::encode("���� \x1b[1x"+kunshu_name+"\x1b[0x�� ���� \x1b[16x"+city_name+"\x1b[0x�� �ִ�"), kunshu);	
				break;
			case ����_���: 
				pk::message_box(pk::encode("\x1b[1x"+kunshu_name+"\x1b[0x�� ���� \x1b[16x"+city_name+"\x1b[0x"+hanFix.return_chosa(city_name,1)+" ģ��!"), kunshu);
				break;
			case ����_����: 
				pk::message_box(pk::encode("\x1b[1x"+kunshu_name+"\x1b[0x�� ���� \x1b[16x"+city_name+"\x1b[0x"+hanFix.return_chosa(city_name,1)+" �ҹٴٷ� ����� ������ ����!"), kunshu);
				break;
			}
			
		}
		
		int getBetrayalAttackUnitNumber(int �Ѻδ���غ��¼�, pk::building@ building2)
		{			
			int troops2 = pk::get_troops(building2);
			int �������� = 10000;
			return ceil((troops2 + ��������) / float(�Ѻδ���غ��¼�));			
		}
		/*
		int getBetrayalAttackUnitNumber(pk::person@ kunshu0, int �Ѻδ���غ��¼�, pk::building@ building2)
		{
			
			int troops2 = pk::get_troops(building2);
			
			switch (kunshu0.character)
			{
			case ����_�ҽ�: 
				return 1;
			case ����_����: 
				return ceil((troops2 * 2.0) / float(�Ѻδ���غ��¼�));
			case ����_���: 
				return ceil((troops2 * 2.0) / float(�Ѻδ���غ��¼� * 1.5));
			case ����_����: 
				return ceil((troops2 * 2.0) / float(�Ѻδ���غ��¼� * 2));
			}
			
			return 1;
			
		}
		*/
		
		float isBetrayForCities(int city0_id, int city2_id, pk::person@ kunshu0)
		{
			
			int city0_troops = pk::max(pk::get_troops(pk::get_city(city0_id)),1);
			int city2_troops = pk::max(pk::get_troops(pk::get_city(city2_id)),1);
						
			
			float result = (float(city0_troops) / float(city2_troops)) / float(�߸�_�� - kunshu0.ambition + 2);
			
			//pk::printf(pk::encode("isBetrayForCities result=["+result+"] \n"));
					
			
			// return result >= 1.0 ? true : false;
			
			return result;
		}
		
		bool areWeAtWar(int force0_id)
		{
			for (int i = 0; i < ����_��; i++){	
				if(���´����￩��[force0_id][i] == 1)return true;
			}
			
			return false;
		}
		
		// ���� ü��
		void allyUnally(pk::force@ force0, pk::force@ force2, float wantSum, float force0_wantAlly, float force2_wantAlly)
		{
			int force0_id = force0.get_id();
			int force2_id = force2.get_id();
			int relations = force0.relations[force2_id];
						
			// �÷��̾ �ڵ����� ���Ϳ�û���� �ʴ´�.
			bool force0_want_more = force0_wantAlly > force2_wantAlly;
			bool will_���� = (relations >= 100 and pk::is_enemy(force0, force2));
			bool will_�ı� = (relations <= 0 and !pk::is_enemy(force0, force2));
			if(will_�ı�)force0_want_more = !force0_want_more;
			pk::force@ force_reqs = force0_want_more ? force0 : force2;
			pk::force@ force_recv = force0_want_more ? force2 : force0;					
			if(force0.is_player()){@force_recv=force0;@force_reqs=force2;}
			if(force2.is_player()){@force_recv=force2;@force_reqs=force0;}
			
			// util.prnt("force_reqs=["+force_reqs.kunshu+"] force_recv=["+force_recv.kunshu+"] force0_want_more=["+force0_want_more+"]");
			
			if(will_���� or will_�ı�)cmd_AllyUnAlly(force_reqs, force_recv, wantSum, (will_���� ? true : false) );
			
		}
		
		
		void cmd_AllyUnAlly(pk::force@ force0, pk::force@ force2, float wantSum, bool willAlly)
		{
			if(��ź�����[force0.get_id()] >= 0)return;
			
			// ��� ���ϱ�
			pk::list<pk::city@> cityList = pk::get_city_list(force0);
			pk::building@ building0 = pk::city_to_building(cityList[0]);
			auto person_list = pk::get_idle_person_list(building0);
			if (person_list.count == 0)return;
			pk::person@ sasin = pk::get_person(person_list[0].get_id());
			
			int force0_id = force0.get_id();	
			int force2_id = force2.get_id();	
			
			if(willAlly){
				
				pk::alliance_cmd_info info;
							
				@info.actor = sasin;
				
				// �׼� ���ϱ�		
				// ��û������ ���� ���� ���� ���̳ʽ�, ���� ���� ���� �÷���
				int diff = ���ºΰ��Ӽ�[force0_id][�Ӽ�_����] - ���ºΰ��Ӽ�[force2_id][�Ӽ�_����];
				float rate = float(���ºΰ��Ӽ�[force0_id][�Ӽ�_����]) / float(pk::max((���ºΰ��Ӽ�[force0_id][�Ӽ�_����] + ���ºΰ��Ӽ�[force2_id][�Ӽ�_����]), 1));				
				int gold_force2_per_city = int(float(���ºΰ��Ӽ�[force2_id][�Ӽ�_��]) / float(pk::max(���ºΰ��Ӽ�[force2_id][�Ӽ�_���ü�], 2)) );
				int gold_force0_per_city = int(float(���ºΰ��Ӽ�[force0_id][�Ӽ�_��]) / float(���ºΰ��Ӽ�[force0_id][�Ӽ�_���ü�]));	
				
				// ��û������ �� ���ϸ� -
				int gold0 = diff > 0 ? -int(rate * gold_force2_per_city) : int(rate * gold_force0_per_city);
				
				// �Ÿ��� ���� 
				gold0 = int( gold0 / float(���´뼼�°Ÿ�[force0_id][force2_id] + 1) );
			
				info.gold = gold0;
				
				// pk::printf(pk::encode("ALLY force0=["+force0.kunshu+"] force2=["+force2.kunshu+"] diff=["+diff+"] rate=["+rate+"] gold_force2_per_city=["+gold_force2_per_city+"] gold_force0_per_city=["+gold_force0_per_city+"] info.gold=["+info.gold+"] \n"));
				// util.prnt("ALLY force0=["+force0.kunshu+"] force2=["+force2.kunshu+"] info.gold=["+info.gold+"]");
				
				@info.target = force2;
				
				pk::command(info);				
				
			}
			else{
				
				pk::annul_alliance_cmd_info info; // �ı�
							
				@info.actor = person_list[0];
				@info.target = force2;
				// util.prnt("UNALLY force0=["+force0.kunshu+"] force2=["+force2.kunshu+"]");
				pk::command(info);
				
			}
			��ź�����[force0_id] = ��ź�����_�ϼ�;
		}
		
		
		
		void set_���´��Ǵ�(){
			
			
			pk::list<pk::force@> force_list = pk::get_force_list(false);
			
			
			for (int i = 0; i < force_list.count; i++){
				if(isIminzoku(force_list[i]))continue;				
				set_���´��Ǵ�_force(force_list[i]);
			}
			
		}
		
		
		// ���� �� ������		
		void set_���´��Ǵ�_force(pk::force@ force0)
		{
			int force0_id = force0.get_id();			
			pk::list<pk::force@> force_list = pk::get_force_list(false);						
					
			
			// ���� �� ã�� ����			
			���ºΰ��Ӽ�[force0_id][�Ӽ�_��������] = 0;
						
			
			for (int i = 0; i < force_list.count; i++){				
				if(isIminzoku(force_list[i]))continue;
				int force1_id = force_list[i].get_id();
				if(���¿ܱ����[force0_id][force1_id] != 1)continue;				
				
								
				// �ڱ��ڽ� ����
				if(force1_id == force0_id)continue;			
				
				// ���� �� ã��				
				if(pk::is_neighbor_force(force0, force_list[i]) and pk::is_enemy(force0, force_list[i])){
					���ºΰ��Ӽ�[force0_id][�Ӽ�_��������] += 1;
					�������ո��[force0_id][��������_���ü�] += ���ºΰ��Ӽ�[force1_id][�Ӽ�_���ü�];
					�������ո��[force0_id][��������_�����] += ���ºΰ��Ӽ�[force1_id][�Ӽ�_�����];
					�������ո��[force0_id][��������_����] += ���ºΰ��Ӽ�[force1_id][�Ӽ�_����];
				}
								
				// ���� �Ǵ� ����
				���´��Ǵ�[index_���´��Ǵ�] = make_�Ǵ�(force0, force_list[i]);
				
				// ���� ���� ���� �� ã�� and ������ �������� �� ã��
				set_������_��������(force0_id, force1_id, ���´��Ǵ�[index_���´��Ǵ�]);
				
				
				index_���´��Ǵ�++;
				
			}
			
			
		}
		
		
		// ���� �Ǵ�
		array<float> make_�Ǵ�(pk::force@ force0, pk::force@ force2)
		{
			int force0_id = force0.get_id();
			int force2_id = force2.get_id();
			array<int> force0_�ΰ��Ӽ� = ���ºΰ��Ӽ�[force0_id];
			array<int> force2_�ΰ��Ӽ� = ���ºΰ��Ӽ�[force2_id];
			
			�Ǵ�[�Ǵ�_�Ǵ���ü] = force0_id;
			
			�Ǵ�[�Ǵ�_�Ǵܴ��] = force2_id;
			
			�Ǵ�[�Ǵ�_��������] = BooleanToFloat(pk::is_neighbor_force(force0, force2));			
			
			�Ǵ�[�Ǵ�_���ü�] = get_�Ǵ�_���ù��庴��(force0_id, force2_id, force0_�ΰ��Ӽ�[�Ӽ�_���ü�], force2_�ΰ��Ӽ�[�Ӽ�_���ü�]);	
			
			�Ǵ�[�Ǵ�_�����] = get_�Ǵ�_���ù��庴��(force0_id, force2_id, force0_�ΰ��Ӽ�[�Ӽ�_�����], force2_�ΰ��Ӽ�[�Ӽ�_�����]);	
			
			�Ǵ�[�Ǵ�_����] = get_�Ǵ�_���ù��庴��(force0_id, force2_id, force0_�ΰ��Ӽ�[�Ӽ�_����], force2_�ΰ��Ӽ�[�Ӽ�_����]);	
			
			�Ǵ�[�Ǵ�_Ȳ����ȣ����] = isProtectHan(force0, force2, pk::is_protecting_the_emperor(force2));
					
			�Ǵ�[�Ǵ�_��ȣ��] = force0.relations[force2_id];			
			
			�Ǵ�[�Ǵ�_����] = pk::get_aishou_distance(pk::get_person(force0.kunshu), (pk::get_person(force2.kunshu)).get_id());
				
			�Ǵ�[�Ǵ�_ž10] = get_�Ǵ�_���ù��庴��(force0_id, force2_id, force0_�ΰ��Ӽ�[�Ӽ�_ž10], force2_�ΰ��Ӽ�[�Ӽ�_ž10]);	
			
			�Ǵ�[�Ǵ�_������] = BooleanToFloat(pk::is_enemy(force0, force2));
			
			�Ǵ�[�Ǵ�_�����߿���] = BooleanToFloat(���´����￩��[force0_id][force2_id] == 1 ? true : false);
			
			//�Ǵ�[�Ǵ�_������] = BooleanToFloat(����������[force0_id][force2_id] == 1 ? true : false);
			
			�Ǵ�[�Ǵ�_ģ�ֿ���] = BooleanToFloat(pk::is_like(pk::get_person(force0.kunshu), force2.kunshu));
			
			�Ǵ�[�Ǵ�_��������] = BooleanToFloat(pk::is_dislike(pk::get_person(force0.kunshu), force2.kunshu));
				
			
			
			return �Ǵ�;
			
		}
		
		float get_�Ǵ�_���ù��庴��(int force0_id, int force2_id, int ��_force0, int ��_force2){
			bool ȣ��ȣ = (��_force2 > ��_force0);
			float ��_���� = float(pk::max(��_force0+��_force2, 1));
			// util.prnt("kunshu0=["+pk::get_force(force0_id).kunshu+"] kunshu2=["+pk::get_force(force2_id).kunshu+"] num_force0=["+��_force0+"] num_force2=["+��_force2+"]");
			return ȣ��ȣ ? ��_force2 / ��_���� : -(��_force0 / ��_����);
		}
		
		
		float isProtectHan(pk::force@ force0, pk::force@ force1, bool isProtectingTheEmperor)
		{
			
			pk::person@ kunshu1 = pk::get_person(force1.kunshu);
			pk::person@ kunshu0 = pk::get_person(force0.kunshu);
			
			float result = 0;
			
			/*
			const int �ѽ�_���� = 0;
			const int �ѽ�_���� = 1;
			const int �ѽ�_�߽� = 2;
			*/
			
			int8 kanshitsu0 = kunshu0.kanshitsu -1;
			int8 kanshitsu1 = kunshu1.kanshitsu -1;
			
			if(kanshitsu0 == 1 and kanshitsu1 == 1 )result = 1;
			else if(kanshitsu0 * kanshitsu1 == -1)result = -1;			
			else result = 0;
			
			//���ʽ�
			if(kanshitsu0 == 1 and isProtectingTheEmperor)result += 1;
			
			
			return result;
		}
		
		void set_������_��������(int force0_id, int force1_id, array<float> a_���´��Ǵ� )
		{
			bool isEnemyOfEnemy = false;
			bool isAllianceOfEnemy = false;
			if(���´����￩��[force0_id][force1_id] == 1)isEnemyOfEnemy = true;
			if(isAlly(a_���´��Ǵ�[�Ǵ�_��ȣ��], a_���´��Ǵ�[�Ǵ�_������] ))isAllianceOfEnemy = true;
						
			for (int i = 0; i < ����_��; i++){	
				// line_bigO++;
				if(pk::is_enemy(force1_id, i) and isEnemyOfEnemy){
					����������[force0_id][i] = 1;
				}
				if((���´����￩��[force1_id][i] == 1 ? true : false) and isAllianceOfEnemy){
					���µ�������[force0_id][i] = 1;
				}
			}			
			
		}
		
		bool isAlly(float relations, float isEnemy)
		{
			return relations >= 50.f and isEnemy == 0.f ? true : false;
		}
		
		
		
		void set_���´��Ǵ�_weight()
		{
			
			for (int i = 0; i < index_���´��Ǵ�; i++){						
				
				int force0_id = int(���´��Ǵ�[i][�Ǵ�_�Ǵ���ü]);
				int force1_id = int(���´��Ǵ�[i][�Ǵ�_�Ǵܴ��]);
				
				if (!pk::is_alive(pk::get_force(force0_id)) or !pk::is_valid_force_id(force0_id))continue;	
				if (!pk::is_alive(pk::get_force(force1_id)) or !pk::is_valid_force_id(force1_id))continue;	
				
				if(force0_id == -1)continue;		
				
				
				setJudgeWeight(pk::get_force(force0_id));
				
				float dec_wantally = getWantSum(���´��Ǵ�[i], �Ǵ�ȣ��ȣ[force0_id], �Ǵܰ���ġ[force0_id]);								
					
				���´��Ǵ�[i][�Ǵ�_���] = dec_wantally;			
				���´��Ǵܰ��[force0_id][force1_id] = dec_wantally;
			
			}
				
		}
				
		
		float getWantSum(array<float> a_���´��Ǵ�, array<bool> a_�Ǵ�ȣ��ȣ, array<float> a_�Ǵܰ���ġ)
		{
			
			float n = 0.f;
			int8 cnt_������ = 0;
			int8 idx_�Ǵ� = 0;
			
			int force0_id = int(a_���´��Ǵ�[�Ǵ�_�Ǵ���ü]);
			int force2_id = int(a_���´��Ǵ�[�Ǵ�_�Ǵܴ��]);
			pk::person@ kunshu0 = pk::get_person(pk::get_force(force0_id).kunshu);
			pk::person@ kunshu2 = pk::get_person(pk::get_force(force2_id).kunshu);
			
			array<float> �Ǵܰ�(20, -1.f);
			
			// util.prnt("***********************************************************************************************");
			// util.prnt("---------------------------------- kunshu0=["+kunshu0.get_id()+"] kunshu2=["+kunshu2.get_id()+"] ");
			
			float v = getVal_ȣ��_1(a_���´��Ǵ�[�Ǵ�_��������], a_�Ǵ�ȣ��ȣ[�Ǵ�_��������]) * a_�Ǵܰ���ġ[�Ǵ�_��������];	
			// util.prnt("is_Neighbor=["+v+"]  ");
			�Ǵܰ�[idx_�Ǵ�++] = v; n += v;	
			cnt_������++;
			
			v = a_���´��Ǵ�[�Ǵ�_���ü�] * a_�Ǵܰ���ġ[�Ǵ�_���ü�];
			// util.prnt("City2By=["+v+"]");
			�Ǵܰ�[idx_�Ǵ�++] = v; n += v;	
			cnt_������++;
			
			v = a_���´��Ǵ�[�Ǵ�_�����] * a_�Ǵܰ���ġ[�Ǵ�_�����];
			// util.prnt("Mujang2By=["+v+"]");
			�Ǵܰ�[idx_�Ǵ�++] = v; n += v;	
			cnt_������++;
						
			v = a_���´��Ǵ�[�Ǵ�_����] * a_�Ǵܰ���ġ[�Ǵ�_����];		
			// util.prnt("Troops2By=["+v+"]");			
			�Ǵܰ�[idx_�Ǵ�++] = v; n += v;	
			cnt_������++;
						
			v = getVal_ȣ��_0(a_���´��Ǵ�[�Ǵ�_Ȳ����ȣ����], a_�Ǵ�ȣ��ȣ[�Ǵ�_Ȳ����ȣ����]) * a_�Ǵܰ���ġ[�Ǵ�_Ȳ����ȣ����];		
			// util.prnt("is_protect_Han=["+v+"] ");			
			�Ǵܰ�[idx_�Ǵ�++] = v; n += v;	
			if(v != 0)cnt_������++;
						
			v = (a_���´��Ǵ�[�Ǵ�_��ȣ��] / 100.f) * a_�Ǵܰ���ġ[�Ǵ�_��ȣ��];	
			// util.prnt("Relation=["+v+"] ");			
			�Ǵܰ�[idx_�Ǵ�++] = v; n += v;	
			cnt_������++;
					
			v = (-(a_���´��Ǵ�[�Ǵ�_����]) / 100.f) * a_�Ǵܰ���ġ[�Ǵ�_����];		
			// util.prnt("GungHab=["+v+"] ");
			�Ǵܰ�[idx_�Ǵ�++] = v; n += v;	
			cnt_������++;
			
			v = a_���´��Ǵ�[�Ǵ�_ž10] * a_�Ǵܰ���ġ[�Ǵ�_ž10];
			// util.prnt("Top10By=["+v+"]");
			�Ǵܰ�[idx_�Ǵ�++] = v; n += v;	
			cnt_������++;
			
			v = getVal_ȣ��_0(a_���´��Ǵ�[�Ǵ�_������], a_�Ǵ�ȣ��ȣ[�Ǵ�_������]) * a_�Ǵܰ���ġ[�Ǵ�_������];
			// util.prnt("is_enemy=["+v+"] ");
			�Ǵܰ�[idx_�Ǵ�++] = v; n += v;	
			if(v != 0)cnt_������++;
			
			v = getVal_ȣ��_0(a_���´��Ǵ�[�Ǵ�_�����߿���], a_�Ǵ�ȣ��ȣ[�Ǵ�_�����߿���]) * a_�Ǵܰ���ġ[�Ǵ�_�����߿���];
			// util.prnt("is_atWar=["+v+"] ");
			�Ǵܰ�[idx_�Ǵ�++] = v; n += v;	
			if(v != 0)cnt_������++;
						
			v = getVal_ȣ��_0(a_���´��Ǵ�[�Ǵ�_������] = BooleanToFloat(����������[force0_id][force2_id] == 1 ? true : false), a_�Ǵ�ȣ��ȣ[�Ǵ�_������]) * a_�Ǵܰ���ġ[�Ǵ�_������];
			// util.prnt("is_EnemyOfEnemy=["+v+"] ");
			�Ǵܰ�[idx_�Ǵ�++] = v; n += v;	
			if(v != 0)cnt_������++;
			
			v = getVal_ȣ��_0(a_���´��Ǵ�[�Ǵ�_��������] = BooleanToFloat(���µ�������[force0_id][force2_id] == 1 ? true : false), a_�Ǵ�ȣ��ȣ[�Ǵ�_��������]) * a_�Ǵܰ���ġ[�Ǵ�_��������];
			// util.prnt("is_EnemyOfAlly=["+v+"] ");
			�Ǵܰ�[idx_�Ǵ�++] = v; n += v;	
			if(v != 0)cnt_������++;
			
			v = getVal_ȣ��_0(a_���´��Ǵ�[�Ǵ�_ģ�ֿ���], a_�Ǵ�ȣ��ȣ[�Ǵ�_ģ�ֿ���]) * a_�Ǵܰ���ġ[�Ǵ�_ģ�ֿ���];
			// util.prnt("is_Like=["+v+"] ");
			�Ǵܰ�[idx_�Ǵ�++] = v; n += v;	
			if(v != 0)cnt_������++;
			
			v = getVal_ȣ��_0(a_���´��Ǵ�[�Ǵ�_��������], a_�Ǵ�ȣ��ȣ[�Ǵ�_��������]) * a_�Ǵܰ���ġ[�Ǵ�_��������];
			// util.prnt("is_Dislike=["+v+"] ");
			�Ǵܰ�[idx_�Ǵ�++] = v; n += v;	
			if(v != 0)cnt_������++;
			
			// ���� �� �����հ� �ڽ��� ���� ���� ģȭ ���� ����				
			v = (a_���´��Ǵ�[�Ǵ�_���������ü���] = getVal_ȣ��_����( ���ºΰ��Ӽ�[force0_id][�Ӽ�_���ü�], �������ո��[force0_id][��������_���ü�], kunshu0.character )) * a_�Ǵܰ���ġ[�Ǵ�_���������ü���];	
			// util.prnt("sum_nearEnemyCity=["+v+"] ");
			�Ǵܰ�[idx_�Ǵ�++] = v; n += v;			
			cnt_������++;
			
			v = (a_���´��Ǵ�[�Ǵ�_�������������] = getVal_ȣ��_����( ���ºΰ��Ӽ�[force0_id][�Ӽ�_�����], �������ո��[force0_id][��������_�����], kunshu0.character )) * a_�Ǵܰ���ġ[�Ǵ�_�������������];
			// util.prnt("sum_nearEnemyMujang=["+v+"] ");
			�Ǵܰ�[idx_�Ǵ�++] = v; n += v;			
			cnt_������++;
			
			v = (a_���´��Ǵ�[�Ǵ�_������������] = getVal_ȣ��_����( ���ºΰ��Ӽ�[force0_id][�Ӽ�_����], �������ո��[force0_id][��������_����], kunshu0.character )) * a_�Ǵܰ���ġ[�Ǵ�_������������];
			// util.prnt("sum_nearEnemyTroops=["+v+"] ");
			�Ǵܰ�[idx_�Ǵ�++] = v; n += v;			
			cnt_������++;
			
			
			
			n /= (cnt_������);
			
			
			// util.prnt("---------------------------------- want_ally=["+n+"] ");
			// // util.prnt("kunshu0=["+kunshu0.get_id()+"] kunshu2=["+kunshu2.get_id()+"] want_ally=["+n+"]");
			
			
			return n;
			
		}
		
		
		// ������ ����
		float getGunshiHelp(pk::person@ personGunshi ,float n)
		{
			if(!pk::is_alive(personGunshi))return 0;
			
			float add = (personGunshi.stat[����ɷ�_���]
				 + personGunshi.stat[����ɷ�_����]
				 + personGunshi.stat[����ɷ�_����]
				 + personGunshi.stat[����ɷ�_��ġ]
				 + personGunshi.stat[����ɷ�_�ŷ�]
			) / (����ɷ�_�� * 100.f);
			
			return n > 0 ? add : -add;
		}
		
		float getVal_ȣ��_0(float val, bool isLike)
		{
			if(val > 0){
				return isLike ? 1 : -1;
			}
			else if(val == 0){
				return 0;
			}
			else{
				return isLike ? -1 : 1;
			}					
		}
		float getVal_ȣ��_1(float val, bool isLike)
		{
			if(val > 0){
				return isLike ? 1 : -1;
			}
			else{
				return isLike ? -1 : 1;
			}					
		}
		float getVal_ȣ��_����(float me, float youSum, int character)
		{
			float me_���ݰ� = me * (character + 1);
			float by = me_���ݰ� + youSum;
			if(by == 0)return 0;
			float val = youSum / by;
			return val;
									
		}
		
		
		
		
		
		void set_rank_��������(){
			
			
			pk::list<pk::force@> force_list = pk::get_force_list(false);
			
			
			for (int i = 0; i < force_list.count; i++){
				if(isIminzoku(force_list[i]))continue;				
				int force_id = force_list[i].get_id();
				
				// ���������¼� ���� �ű��
				set_a_rank_��������(force_id);
				
			}
			
			//if(rank_��������[k] == -1)break;
			//pk::printf(pk::encode(pk::format("{} = {}\n", ���ºΰ��Ӽ�[rank_��������[k]][�Ӽ�_��������], rank_��������[k] )));
			
		}
		
		
		void set_a_rank_��������(int force_id)
		{
							
			// ���� ���� ���ϱ�
			for (int j = 0; j < 47; j++){
				int �����¼� = rank_��������[j] == -1 ? 0 : ���ºΰ��Ӽ�[rank_��������[j]][�Ӽ�_��������];
				
				if( �����¼� < ���ºΰ��Ӽ�[force_id][�Ӽ�_��������]){	
				
					int8 tmpForceId = -1;
					int8 tmp2ForceId = -1;
					
					for (int l = j; l < 47; l++){	
						// line_bigO++;
						if(l > j){
							if(tmpForceId == -1)break;
							tmp2ForceId = rank_��������[l];
							rank_��������[l] = tmpForceId;
							tmpForceId = tmp2ForceId;
						}	
						else {
							tmpForceId = rank_��������[l];
							rank_��������[j] = force_id;								
						}							
					}						
					break;
				}									
			} // end - for			
			
		} // end - function
		
		
		
		
		
		
		
		// ���հἺ Ŀ�ǵ�
		
		void initMenu(pk::building@ building)
		{
			menu_city_id_ = -1;
			pk::city@ city = pk::building_to_city(building);
			if (city !is null)
				menu_city_id_ = city.get_id();
			menu_force_id_ = building.get_force_id();
		}
		
		
		bool isEnabled()
		{
			pk::force@ force_menu = pk::get_force(menu_force_id_);
			
			if( ���հἺ�Һ�Ÿ�� == 0 )
			{
				if (force_menu.tp < �ʿ�ⱳ����Ʈ){return false;}
			}
			else if( ���հἺ�Һ�Ÿ�� == 1 )
			{
				if (pk::get_district(pk::get_district_id(force_menu, 1)).ap < �ʿ��ൿ��){return false;}
			}
			
			return true;
		}
		
		string getMenuDesc()
		{	
			pk::force@ force_menu = pk::get_force(menu_force_id_);
			
			string desc = "";
			
			if( ���հἺ�Һ�Ÿ�� == 0 )
			{
				desc = "���ձ� �Ἲ�� �õ��մϴ�. (�ⱳP : "+�ʿ�ⱳ����Ʈ+"�Һ�)";
				if (force_menu.tp < �ʿ�ⱳ����Ʈ){desc = "�ⱳP�� �����մϴ�.(�ⱳP "+�ʿ�ⱳ����Ʈ+")";}
			}
			else if( ���հἺ�Һ�Ÿ�� == 1 )
			{
				desc = "���ձ� �Ἲ�� �õ��մϴ�. (�ൿ�� : "+�ʿ��ൿ��+"�Һ�)";
				if (pk::get_district(pk::get_district_id(force_menu, 1)).ap < �ʿ��ൿ��){desc = "�ൿ���� �����մϴ�.(�ൿ�� "+�ʿ��ൿ��+")";}
			}
			
			return pk::encode(desc);
		}
		
		
		

		bool isMenuVisible()
		{
			return menu_city_id_ != -1 and menu_force_id_ == pk::get_current_turn_force_id();
		}
		string getMenuText()
		{
			return pk::encode("���հἺ");
		}

		int getMenuImageID()
		{
			return 889;
		}

		bool menuHandler()
		{
			
			pk::force@ force_menu = pk::get_force(menu_force_id_);
			
			if(
				�޴����Ȱ��ȭ != 1 
				or ���սõ�[menu_force_id_] >= 0 
				// or �������հἺ�ߺ��õ�[force_menu.get_id()] != 0
				or ( ���հἺ�Һ�Ÿ�� == 0 and force_menu.tp < �ʿ�ⱳ����Ʈ )
				or ( ���հἺ�Һ�Ÿ�� == 1 and pk::get_district(pk::get_district_id(force_menu, 1)).ap < �ʿ��ൿ�� )
				or ����_���ռ���[force_menu.get_id()] >= 0
			){
				
				string talk = "���ձ� �Ἲ ���� �� �Դϴ�. ";
				
				SelectionAllianceEnemies(true);
				
				if(���հ��۸� != ""){ talk = "����\x1b[1x"+���հ��۸�+"\x1b[0x"+hanFix.return_chosa(���հ��۸�,1)+" ���� ���� ���� ���Դϴ�. "; }			
				
				if(���սõ�[menu_force_id_] >= 0)talk += "���� ���� �� �Դϴ�.";
				// else if(�������հἺ�ߺ��õ�[force_menu.get_id()] != 0)talk += "�ϼ� ���� ������ڽ��ϴ�.";
				else if( ���հἺ�Һ�Ÿ�� == 0 and force_menu.tp < �ʿ�ⱳ����Ʈ )talk = "�ⱳ ����Ʈ�� �����մϴ�";
				else if( ���հἺ�Һ�Ÿ�� == 1 and pk::get_district(pk::get_district_id(force_menu, 1)).ap < �ʿ��ൿ�� )talk = "�ൿ���� �����մϴ�";
				else if(����_���ռ���[force_menu.get_id()] >= 0)talk = "���� �������� �� �Դϴ�. ";
				
				// ���� �ι� ���ϱ�		
				pk::person@ teller = getGunshiOrMunkwan(force_menu);			
				pk::message_box(pk::encode(talk), teller);	
			}
			else{
				
				
				// ������ ���ϱ�
				int allianceEnemyForceId = SelectionAllianceEnemies(false);
				if(allianceEnemyForceId < 0)return true;
				// �������հἺ�ߺ��õ�[force_menu.get_id()] == 1;
				// ���ձ� �Ἲ ����								
				doAlliancingAttack(allianceEnemyForceId);
				// ���
				
			}
			
			return true;
			
		}

		
		// ������ force_id ��ȯ
		int SelectionAllianceEnemies(bool Ž����){
			
			// ������ ������ ���
			pk::list<pk::force@> �������ĺ�;
			
			pk::force@ force0 = pk::get_force(menu_force_id_);
			
			// ���ո�ǥ�� �� Ȯ���� ���� ������ ���´�.
			for (int j = 0; j < ����_��; j++){
				pk::force@ force_willEnemy = pk::get_force(j);
				if(!pk::is_alive(force_willEnemy) or !pk::is_valid_force_id(j))continue;
								
				// Ÿ���ĺ��� ���̰�,
				if(!pk::is_enemy(menu_force_id_, j))continue;
				
				// �������̰�,
				if(!pk::is_neighbor_force(force0, force_willEnemy))continue;
				
				//pk::printf(pk::encode("SelectionAllianceEnemies force_willEnemy=["+force_willEnemy.kunshu+"]  \n"));
						
				�������ĺ�.add(force_willEnemy);
				
				
			} // end - for
			
			string string_���հ��ۼ��� = "";
			array<int> answerForceId; // force_id ����
			for (int k = 0; k < �������ĺ�.count; k++){
				string kunshu_name = pk::decode(pk::get_name(pk::get_person(�������ĺ�[k].kunshu)));
				answerForceId.insertLast(�������ĺ�[k].get_id());
				string_���հ��ۼ��� += " " + kunshu_name;
			}
			
			if(Ž����)return 0;
			
			pk::person@ teller = getGunshiOrMunkwan(force0);
			
			// ���� 2 �ܰ�					
			if(answerForceId.length == 0){pk::message_box(pk::encode("���ձ��� ����ų���� ���� �����ϴ�"), teller);return -1;}	
			
			// string talk = "";			
			// if(string_���հ��ۼ��� != ""){ talk = "����\x1b[1x"+string_���հ��ۼ���+"\x1b[0x"+hanFix.return_chosa(string_���հ��ۼ���,1)+" ���� ���� ������ ��ġ�� �ֽ��ϴ�. "; }	
			
						
			// int n = pk::choose(pk::encode("��� ������ ���� ���ձ��� ����Ű�ðڽ��ϱ�?"), answers);
			string selector_desc = pk::encode("����� ������ �����ϼ���.");
			pk::list<pk::force@> selected_enemy = pk::force_selector(pk::encode("���� ����"), selector_desc, �������ĺ�, 1, 1);
			if (int(selected_enemy.count) == 0) return -2;
			string selected_kunshu_name = pk::decode(pk::get_name(pk::get_person(selected_enemy[0].kunshu)));
			if(pk::choose(pk::encode("\x1b[16x"+selected_kunshu_name+"\x1b[0x"+hanFix.return_chosa(selected_kunshu_name,1)+" ���� ���ձ��� ����Ű�ðڽ��ϱ�?"), { pk::encode("��"), pk::encode("�ƴϿ�") }) == 1)return -2;
			
			return selected_enemy[0].get_id();
		}
		
		
		
		
		
		
		void doAlliancingAttack(int force_id_target ){
			
			�÷��̾���� = force_id_target;
			
			pk::force@ force_player = pk::get_force(menu_force_id_);
			// util.prnt("doAlliancingAttack force_player_id=["+menu_force_id_+"] force_kunshu=["+force_player.kunshu+"] gunshi=["+force_player.gunshi+"]");
			
			// ���簡 ���ٸ� ������ �ɷ�ġ �ݿ�
			pk::person@ represent = getGunshiOrKunshu(force_player);
			pk::person@ teller_fail = getGunshiOrMunkwan(force_player);
			
			float promoterEffect = getDistinctEffect(represent.stat[����ɷ�_����]+represent.stat[����ɷ�_��ġ], 200.0, 3);			
			
			float minPossible = prob_������[force_id_target] <= 0 ? ����_�߰����ռ����� : prob_������[force_id_target] + ����_�߰����ռ�����;				
			int chosenPossibility = int((minPossible * promoterEffect * ������Ȯ�����) * 100);
			
			
			// util.prnt("doAlliancingAttack enemy_kunshu=["+pk::get_force(force_id_target).kunshu+"] enemyProb=["+prob_������[force_id_target]+"]  promoterEff=["+promoterEffect+"] chosenPossibility=["+chosenPossibility+"]  ");
			
			if( pk::rand_bool(chosenPossibility) ){	
				
				int result = AllianceAttack(force_player, force_id_target);
				if(result == -1){ // ����!					
					
				}
				else{
					
					doAlliancingAttackFaleMessage(teller_fail, result);// ���հ��ݽ���
				}
				
			}
			else{ // ������ Ȯ�� ����
				doAlliancingAttackFaleMessage(teller_fail, 10);
				
			}
			
			/// ���հἺ �ൿ�� �Һ�
			if(���հἺ�Һ�Ÿ�� == 0){ pk::add_tp(force_player, -�ʿ�ⱳ����Ʈ, force_player.get_pos()); }
			else if(���հἺ�Һ�Ÿ�� == 1){ 
				auto district = pk::get_district(pk::get_district_id(force_player, 1));
				district.ap -= �ʿ��ൿ��;	
			}
			
			���սõ�[menu_force_id_] = ���սõ�����_�ϼ�;
				
			// �ʱ�ȭ	
			�÷��̾���� = -1;
			
		}
		
		void doAlliancingAttackFaleMessage(pk::person@ speaker, int result){
			
			pk::scene(pk::scene_t(Scene_ResultDoAlliancingAttack));		
			
			string talk = "���ձ� �Ἲ�� �����߽��ϴ�. ";				
			switch (result)
			{
			case 1: 
				talk += "���޹����� ���� ���⸦ ������ �ֽ��ϴ�.";
				break;
			case 2: 
				talk += "����� �����ϴ� ������ �����ϴ�.";
				break;
			case 3: 				
				break;
			case 4: 
				break;
			case 5: 
				talk += "������ �����մϴ�.";
				break;
			case 10:
				talk += "���� ������ �ʾҽ��ϴ�.";
				break;
			}
			
			pk::message_box(pk::encode(talk), speaker);
		}
		
		void Scene_ResultDoAlliancingAttack(){
			pk::fade(0);
			pk::sleep();
			pk::fade(255);
			
		}
		
		// ���� ���: ���� Ȥ�� ����
		pk::person@ getGunshiOrKunshu(pk::force@ force){
			// util.prnt("getGunshiOrKunshu menu_force_id_=["+menu_force_id_+"] force_id=["+force.get_id()+"] kunshu_id=["+force.kunshu+"] gunshi_id=["+force.gunshi+"]");
			pk::person@ gunshi = pk::get_person(force.gunshi);
			pk::person@ kunshu = pk::get_person(force.kunshu);
			pk::person@ speaker = pk::is_alive(gunshi) ? gunshi : kunshu;
			return speaker;
		}
		// ���� ���: ���� Ȥ�� ����
		pk::person@ getGunshiOrMunkwan(pk::force@ force){
			// util.prnt("getGunshiOrMunkwan gunshi=["+force.gunshi+"]");
			pk::person@ gunshi = pk::get_person(force.gunshi);
			pk::person@ speaker = pk::is_alive(gunshi) ? gunshi : pk::get_person(����_����);
			return speaker;
		}
		
		void set_prob_������()
		{
			prob_������_desc = array<pk::int_int>(); // ����id_Ȯ�������
			
			float grade_top_���º��� = 1.f;
			float grade_top_�������� = 0.5f;
			float cut = 0.f;
			// 10 �� ���±�����. ���ϴ� ���� �̹Ƿ� üũ ����.
			for (int i = 0; i < 10; i++){				
				if(rank_���º���[i] == -1 or rank_��������[i] == -1)break; // ������ ���ϴ� ����� ���� ���µ�.				
				// line_bigO++;
				float grade_���º��� = grade_top_���º��� + cut;
				float grade_�������� = grade_top_�������� + cut;
				
				if(grade_���º��� >= 0){
					if(prob_������[rank_���º���[i]] == -2.f)prob_������[rank_���º���[i]] = grade_���º���;
					else{prob_������[rank_���º���[i]] += grade_���º���;}
				}							
				
				if(grade_�������� >= 0){
					if(prob_������[rank_��������[i]] == -2.f)prob_������[rank_��������[i]] = grade_��������;
					else{prob_������[rank_��������[i]] += grade_��������;}	
				}
				
				
				pk::int_int prob = pk::int_int(rank_���º���[i], (prob_������[rank_���º���[i]]) * 100);
				int find_idx = prob_������_desc.findByRef(prob);
				if(find_idx < 0)prob_������_desc.insertLast(prob);
				else { prob_������_desc[find_idx] = prob; }
				
								
				// util.prnt("i=["+i+"] troops_top_force["+pk::get_force(rank_���º���[i]).kunshu+"]=["+prob_������[rank_���º���[i]]+"] neighbor_enemy_top["+pk::get_force(rank_��������[i]).kunshu+"]=["+prob_������[rank_��������[i]]+"] ");
								
				cut -= 0.1f;
			}
			// util.prnt("prob length=["+prob_������_desc.length+"]");
			if(prob_������_desc.length > 0){
				prob_������_desc.sort(function(a,b) { 				
					return a.second > b.second; 
				});
			}
			
			
			/*
			// log
			for (int j = 0; j < prob_������_desc.length; j++){
				pk::int_int prob = prob_������_desc[j];
				// util.prnt("prob_enemy_desc force_id=["+prob.first+"] force_kushu=["+pk::get_force(prob.first).kunshu+"] prob=["+prob.second+"] ");
			}
			*/
			
			// util.prnt("--------------------------------------------------------------------------------------------------");
		}
		
		void search_������(){
			
			
			pk::list<pk::force@> force0_list = pk::get_force_list(false); // ������ �ĺ�
			
			
			for (int i = 0; i < force0_list.count; i++){
				if(isIminzoku(force0_list[i]))continue;				
				// ������ ����
				int force0_id = force0_list[i].get_id();
				pk::force@ force0 = force0_list[i];				
				if(force0.is_player())continue;
				if(���սõ�[force0_id] >= 0)continue;
				if(���ռ�������[force0_id] >= 1)continue;				
				
				// ���簡 ���ٸ� ������ �ɷ�ġ �ݿ�				
				pk::person@ leader = getGunshiOrKunshu(force0);
				
				float leaderEffect = getDistinctEffect(leader.stat[����ɷ�_����]+leader.stat[����ɷ�_��ġ], 200.0, 3);
				
				// ���ո�ǥ�� �� Ȯ���� ���� ������ ���´�.
				for (int j = 0; j < prob_������_desc.length; j++){
					
					pk::int_int prob = prob_������_desc[j];
					int force2_id = prob.first;
					pk::force@ force2 = pk::get_force(force2_id);
					
					if(!pk::is_alive(force2) or !pk::is_valid_force_id(force2_id))continue;		
					
					if(force2_id == force0_id)continue;	// �ڱ��ڽ� ����						
					
					if(���´����￩��[force0_id][force2_id] != 1)continue;	// �������� �������ΰ�
					
					if(!pk::is_neighbor_force(force0, force2))continue; // �������ΰ�
					
					// line_bigO++;
					
					// �� ���� �󸶳� ���Ѱ�? 
					float ���ּ��´�������� = 
						���ºΰ��Ӽ�[force2.get_id()][�Ӽ�_����] / float(pk::max((���ºΰ��Ӽ�[force0_id][�Ӽ�_����] + ���ºΰ��Ӽ�[force2.get_id()][�Ӽ�_����]), 1));						
					���ּ��´�������� = �����������º� ? ���ּ��´�������� : 1.0;
					
					// ��ȣ��
					float relations = pk::max(((100 - force0.relations[force2_id]) / 100.f), 0.1f);					
					
					float ������Ȯ�� = ������Ȯ����� * prob_������[force2_id] * ���ּ��´�������� * (relations * relations * relations);						
					int chosenPossibility = int(( ������Ȯ�� * leaderEffect ) * 100);
					
					
					if( getRandom(chosenPossibility, 11) ){	
						
						���հ����� = force2_id;
						int result = AllianceAttack(force0, force2_id);	
						
						���սõ�[force0_id] = ���սõ�����_�ϼ�;
						
						// util.prnt("Alliance leader=["+force0.kunshu+"] enemy=["+force2.kunshu+"] enemyProb=["+prob_������[force2_id]+"]  leaderEff=["+leaderEffect+"] enemyTroopsRate=["+floor(���ּ��´��������*100)/100+"] relations=["+relations+"] chosenPossibility=["+chosenPossibility+"] result=["+result+"]");
						// pk::printf(pk::encode("----------------------------------------- success? ["+result+"] -------------------------------------------\n"));
						
						return;
					}	
					
				} // end - for				
			} // end - for
			
			
			// pk::printf(pk::encode("-------------------------------------------- fail -----------------------------------------------\n"));
			
			
		}
		
		// cnt �� Ȧ��
		bool getRandom(float prob, int8 cnt){
			
			int8 t = 0;
			int8 f = 0;
			
			while (cnt > 0){
				cnt -= 1;
				if( pk::rand_bool(prob) ){t+=1;}else{f+=1;}
			}
			// util.prnt("prob=["+prob+"] t=["+t+"] f=["+f+"]");			
			return t > f ? true : false;
		}
		
		/// ���ձ� ���� ���� �ֺ� �������� �˻�
		void addAllianceCities(int city0_id, int city2_id, array<AllianceInfo@> &���ձ�����, array<int> &����Ƚ��, array<int> arr_���ձ�����){
			
			array<int> neighbor_cities = neighborMap.��������[city0_id];
			for (int i = 0; i < neighbor_cities.length; i++){
				pk::city@ neighbor_city = pk::get_city(neighbor_cities[i]);
				int force_id = neighbor_city.get_force_id();
				if(!pk::is_alive(neighbor_city) or !pk::is_valid_force_id(force_id))continue;			
				// ���ձ� �Ͽ� �ΰ�?
				if(!isAllianceForce(force_id, arr_���ձ�����))continue;			
				
				// �������� �߰�
				// util.prnt("addAllianceCities force=["+force_id+"] city=["+neighbor_city.get_id()+"] city2=["+city2_id+"] num_go=["+����Ƚ��[neighbor_city.get_id()]+"]");
				���ձ�����.insertLast(AllianceInfo(force_id, neighbor_city.get_id(), city2_id, false));
				����Ƚ��[neighbor_city.get_id()] += 1; // ��ߵ��� ���� ����Ƚ��
			}
			
		}
				
		void set_���ձ�_��������(array<AllianceInfo@> &���ձ�����){
			dictionary dic;
			for (int i = 0; i < ���ձ�����.length; i++){
				pk::city@ city0 = pk::get_city( ���ձ�����[i].��ߵ���);
				pk::city@ city2 = pk::get_city( ���ձ�����[i].��������);			
				string key = city0.get_id() + "";
				if(dic.exists(key)){
					auto arr = cast<array<int>>(dic[key]);	
					arr.insertLast(city2.get_id());					
				}					
				else{
					array<int> arr = {city2.get_id()};
					dic.set(key, arr);
				}					
			}
			for (int i=0; i<dic.getKeys().length; i++){
				string key = dic.getKeys()[i];
				auto arr = cast<array<int>>(dic[key]);	
				arr.sort(function(a,b) {
					pk::city@ city0 = pk::get_city(a);
					pk::city@ city2 = pk::get_city(b);					
					return pk::get_troops(city0) < pk::get_troops(city2); 
				});				
			}
			for (int i = 0; i < ���ձ�����.length; i++){
				string key = ���ձ�����[i].��ߵ��� + "";
				auto arr = cast<array<int>>(dic[key]);
				���ձ�����[i].�������� = arr[0];
			}
		}
		
		int AllianceAttack(pk::force@ force_leader, int target_force_id){
			
			// �÷��̾�ձ��޴��� Ȱ��ȭ ������ return
			if(force_leader.is_player() and �÷��̾���� == -1 )return 3;	
			
			pk::force@ target_force = pk::get_force(target_force_id);
			if (!pk::is_alive(target_force) or !pk::is_valid_force_id(target_force_id))return 0;	
			
			
			string force_leader_kunshu_name = pk::decode(pk::get_name(pk::get_person(force_leader.kunshu)));
			string target_kunshu_name = pk::decode(pk::get_name(pk::get_person(pk::get_force(target_force_id).kunshu)));
			
			// ���ձ� ���� �迭
			array<AllianceInfo@> ���ձ�����;
			array<int> ����Ƚ��(����_��, 0);		
			
			string last_kunshu_name = "";
			
			// �÷��̾� ���� 			
			array<pk::bool_bool> alliancePlayers(����_��, pk::bool_bool(false, false));// ���ձ�����, ��������			
			array<int> ���ձ�����_distinct; // ���� ������ ��� ����
			
			// ���ձ� ���� �̸���
			string msg1 = "";
			
			// ���ձ� ã��
			// �� ���� �� ������ ���� Ž��
			pk::list<pk::city@> target_city_list = pk::get_city_list(target_force);
			for (int i = 0; i < target_city_list.count; i++)
			{				
				auto target_city = target_city_list[i];
				if (!pk::is_alive(target_city) or !pk::is_valid_force_id(target_city.get_force_id()))continue;
				
				array<int> neighbor_cities = neighborMap.��������[target_city.get_id()];
				for (int j = 0; j < neighbor_cities.length; j++){
					
					pk::city@ neighbor_city = pk::get_city(neighbor_cities[j]);					
					if(!pk::is_alive(neighbor_city) or !pk::is_valid_force_id(neighbor_city.get_force_id()))continue;
					// ������ ������ �ƴѰ�?
					if(neighbor_city.get_force_id() == target_force_id)continue;
					
					// line_bigO++;
					
														
					int ally_force_id = neighbor_city.get_force_id();	
					pk::force@ ally_force = pk::get_force(ally_force_id);
					
					// ���ձ� ������ ��ȿ�Ѱ�?
					if (!pk::is_alive(ally_force) or !pk::is_valid_force_id(ally_force_id))continue;	
								
					// �������� �� �����ΰ�?
					// if(!pk::is_enemy(ally_force_id, target_force_id))continue;
					
					// �÷��̾ ���ձ��ΰ�?
					bool is_player_alliance = ally_force.is_player();					
					if(is_player_alliance)alliancePlayers[ally_force_id].first = true;
					
					// �������°��� ��ȣ��
					// �������� ������ �ʵ� �Ⱦ�
					if( !is_player_alliance and (force_leader.relations[ally_force_id] < 30) )continue;
										
					���ձ�����.insertLast(AllianceInfo(ally_force_id, neighbor_city.get_id(), target_city.get_id(), false));
					����Ƚ��[neighbor_city.get_id()] += 1; // ��ߵ��� ���� ����Ƚ��
					
					
					// �ߺ����� 
					if(���ձ�����_distinct.find(ally_force_id) < 0){
						���ձ�����_distinct.insertLast(ally_force_id);
						// ���ռ��� ���� ����
						// if(ally_force_id != force_leader.get_id())�����Ҽ��¼�_��������++;
						
					}
					
				}
				
			}
			
			
			pk::person@ kunshu_target = pk::get_person(target_force.kunshu);
			pk::person@ kunshu_leader = pk::get_person(force_leader.kunshu);
			pk::person@ leader_represent = getGunshiOrKunshu(force_leader);	
			float leaderEff = getDistinctEffect(leader_represent.stat[����ɷ�_����], 100.0, 4);	// �������
			
			
			// ������ ���ձ��� ���� ���
			if(���ձ�����.length == 0)return 1;
			
			// ���ձ��� �ڽ��� ���¸� ���� ���. ���� ������ ������ ����.
			// util.prnt("cnt_alliance_distinct=["+���ձ�����_distinct.length+"] ");
			if(���ձ�����_distinct.length <= 1)return 2;
			
			set_���ձ�_��������(���ձ�����);
			
			/// �߰� ��������
			int length_���ձ����� = ���ձ�����.length;
			for (int p = 0; p < length_���ձ�����; p++){
				// util.prnt("addAllianceCities AllianceInfoList=["+���ձ�����.length+"]");
				addAllianceCities( ���ձ�����[p].��ߵ���,  ���ձ�����[p].��������, ���ձ�����, ����Ƚ��, ���ձ�����_distinct);					
			}
			
			/// ���� ���� ����
			array<int8> ���������ߺ�����(�ǹ�_������, -1);
			int length_���ձ�����3 = ���ձ�����.length;
			for (int p = 0; p < length_���ձ�����3; p++){
				pk::city@ city0 = pk::get_city( ���ձ�����[p].��ߵ���);				
				pk::building@ building0 = pk::city_to_building(city0);
				bool isWarAt = intToBoolean(�ǹ����￩��[building0.get_id()]); 									
				/// �������� ���ÿ��� ���� ����.
				if(!isWarAt or ���������ߺ�����[building0.get_id()] == 1)continue;
				���������ߺ�����[building0.get_id()] = 1;
				prepareReinforcement(building0, ���ձ�����, ����Ƚ��, ���ձ�����_distinct, leaderEff);					
			}
			
			
			/// ���� �غ�			
			
			int ����_���ձ� = 0;
			array<int8> ����_�������ߺ�(�ǹ�_������, -1);
			int ����_������ = 0;
			array<array<pk::person@>> ����������(�ǹ�_������, {});
			array<UnitInfo@> ��������;	
			array<int> �������ú���(�ǹ�_������, -1);
			array<int> �������ú���(�ǹ�_������, -1);			
			������������ = array<int>(����_��, 0);
			
			for (int m = 0; m < ���ձ�����.length; m++){
				// if(���ձ�����[m] == -1 or ��ߵ���[m] == -1 or ��������[m] == -1)continue;	
				// pk::force@ force_ally = pk::get_force(���ձ�����[m].���ձ�����);
				// util.prnt("force kunshu=["+force_ally.kunshu+"] from=["+���ձ�����[m].��ߵ���+"] to=["+���ձ�����[m].��������+"] is_player=["+force_ally.is_player()+"] ");
				
				/// �÷��̾� ������ �ڵ����� �δ븦 �������� �ʴ´�
				if(pk::get_force(���ձ�����[m].���ձ�����).is_player())continue;				
				// line_bigO++;
				
				pk::city@ city0 = pk::get_city( ���ձ�����[m].��ߵ���);				
				pk::building@ building0 = pk::city_to_building(city0);
				pk::building@ building2 = pk::city_to_building(pk::get_city( ���ձ�����[m].��������));
				bool isWarAt = intToBoolean(�ǹ����￩��[building0.get_id()]); 
					
				/// �Ÿ��� �ִ������Ÿ� �̻��̸� ���
				int ��_distance = ceil(pk::get_distance(building0.get_pos(), building2.get_pos()) / ����_ĭ�̵���);
				if(��_distance > 13)continue;
					
				/// ������ ���� ���ϱ� 
				if(����_�������ߺ�[building2.get_id()] == -1){
					����_������ += pk::get_troops(building2);
					����_�������ߺ�[building2.get_id()] = 1;
				}
				
				if(isWarAt)continue; // ���ð� �������̸� pass		
				
				if(isAroundEnemyThreat(city0))continue; // ������ �������� ���� �ִ°�?
					
				
				/// ���� ���� ���ϱ�
				/// ���� ������ ���� ���ϱ�
				auto person_list = pk::get_idle_person_list(building0);
				if (person_list.count == 0)continue;
				person_list.sort(function(a, b){ return a.stat[����ɷ�_���] + a.stat[����ɷ�_����] > b.stat[����ɷ�_���] + b.stat[����ɷ�_����]; });				
				/// �� ���ÿ��� ����Ƚ���� ���� �����δ��
				int numUnit = pk::min(int( person_list.count ), �ѵ����ִ������δ��);		
				if(����Ƚ��[city0.get_id()] > 0) numUnit = int(numUnit / float(����Ƚ��[city0.get_id()]));	
				// util.prnt("remove_person_1 building=["+building0.get_id()+"] person_list=["+person_list.count+"] person_gone=["+����������[building0.get_id()].length+"]");								
				// util.prnt("-------------------------------------------------------------------------");
				auto person_array = remove_�ߺ�_persons(get_personIds(person_list), ����������[building0.get_id()]); //���� �������� ����
				numUnit = pk::min(numUnit, person_array.length);
				// get_personIds(person_array); // for Debug
				array<int> ��������;
				int �����δ뺴�� = 0;
				int ����_���� = �������ú���[building0.get_id()];
				�������ú���[building0.get_id()] = ����_���� == -1 ? pk::get_troops(building0) : ����_����;
				int ����_���� = �������ú���[building0.get_id()];
				�������ú���[building0.get_id()] = ����_���� == -1 ? pk::get_food(building0) : ����_����;
				// util.prnt("building0["+building0.get_id()+"] troops=["+�������ú���[building0.get_id()]+"] food=["+�������ú���[building0.get_id()]+"]");
				for (int o = 0; o < numUnit; o++){
					pk::person@ p = pk::get_person(person_array[o]); 
					int rank_troops = pk::get_rank( p.rank).command;
					rank_troops = GetTroops(p);
					int troops = rank_troops;
					int food = int(troops * �δ����_��������);
					bool isLackingTroops = false;
					bool isLackingFood = false;
					if(�������ú���[building0.get_id()] < troops){ 
						isLackingTroops = true;
						if(!�׻��ִ뺴������)troops = �ּ��������¼�;
					}					
					int cost_food = int(food * leaderEff);
					if(�������ú���[building0.get_id()] <= food){isLackingFood = true;}						
					if(isLackingFood)continue;
					if(����_���ú��³� and isLackingTroops)continue;						
					
					�����δ뺴�� += troops;	
					��������.insertLast( p.get_id());
					����������[building0.get_id()].insertLast(p);
					������������[p.get_force_id()] += troops;
					// util.prnt("Unit_to_Go person=["+p.get_id()+"]");
					
					// ���� ���� ����			
					if(!isLackingTroops)�������ú���[building0.get_id()] -= troops;
					if(!isLackingFood)�������ú���[building0.get_id()] -= cost_food;						
				}
				����_���ձ� += �����δ뺴��;
				// get_personIds(����������[building0.get_id()]); // for Debug
				// util.prnt("Get_Troops building=["+building0.get_id()+"] person_array=["+person_array.length+"] person_gone=["+����������[building0.get_id()].length+"]");				
				
				��������.insertLast(UnitInfo(��������, building0.get_id(), building2.get_id(), isWarAt, numUnit, ���ձ�����[m].isReinforcement));				
				����Ƚ��[city0.get_id()] -= 1;
				
				
			} // end - for
			
			
			/// �����̴��� �������� �е����̸� ���ֿ� ���� ������ �ı��ϰ� ���տ� �����Ѵ�.
			/// ���������� ���� ������ ����. 
			array<int> �����ı⼼��;
			���ձ�����_distinct.sort(function(a,b) { 			
				return main.������������[a] > main.������������[b]; 
			});
			int ����_���ձ�_�ı�ݿ� = ����_���ձ�; // �������� ���Ϳ��ΰ� �ݿ���.
			for (int i = 0; i < ���ձ�����_distinct.length; i++){	
				pk::force@ force = pk::get_force(���ձ�����_distinct[i]);
				pk::person@ kunshu = pk::get_person(force.kunshu);				
				if(pk::is_enemy(force, target_force))continue; // �������� ���Ͱ��谡 �ƴϸ� �ش����� �ʴ´�.
				if(pk::is_like(kunshu, target_force.kunshu))continue; // �������� ģ�� ����� �ı����� �ʴ´�.
				
				/// �����ı� ����
				if(!is_���պ��º�(kunshu, ����_���ձ�_�ı�ݿ�, ����_������, get_���ֹ�Ź��(kunshu, force.relations[target_force_id])))
				{ // �������� ��������.
					����_���ձ�_�ı�ݿ�-=������������[force.get_id()]; 
					// util.prnt("remove_from_alliance ["+force.kunshu+"]");
					continue; 
				}
				// util.prnt("betray_alliance ["+force.kunshu+"]");
				�����ı⼼��.insertLast(force.get_id());
							
			}
			
			

			/// ���ձ����¼� VS ���������¼� ��			
			float ���ֹ�� = force_leader.is_player() ? ���ֹ��_player : get_���ֹ��_���պ�����(kunshu_leader);
			if(����_���ձ�_�ı�ݿ� <= 0 or !is_���պ��º�(kunshu_leader, ����_���ձ�_�ı�ݿ�, ����_������, ���ֹ�� ))return 5;				
			
			
			
			if(���ձ�����_distinct.length > 1){ // �����ָ� ������ ���ռ����� ���� ���(�÷��̾������)
				
				���ձ�����_distinct.sort(function(a,b) { 					
					if(pk::get_force(a).is_player())return false;
					if(pk::get_force(b).is_player())return true;
					return main.���ºΰ��Ӽ�[a][�Ӽ�_����] > main.���ºΰ��Ӽ�[b][�Ӽ�_����]; 
				});
				
				// get_forceIds(���ձ�����_distinct); // for Debug
						
				int alliance_top_force_id = ���ձ�����_distinct[0];
				int alliance_top2_force_id = ���ձ�����_distinct[1];	
				
				// ����: ���� ������ ���ձ� �ְ����°� ����� �Ѵ�	
				// ���ձ� �ְ� ����
				pk::force@ force_topAlly = pk::get_force(alliance_top_force_id);					
				if(force_leader.get_id() == alliance_top_force_id)@force_topAlly = pk::get_force(alliance_top2_force_id);	
				
				pk::person@ topAlly_represent = getGunshiOrKunshu(force_topAlly);
				
				// pk::printf(pk::encode("Alliance Leader_kunshu=["+force_leader.kunshu+"] target_kunshu=["+target_force.kunshu+"] top1=["+alliance_top_force_id+"] top2=["+alliance_top2_force_id+"]  \n"));					

				if(DebateForAllyVSAlly(���ձ�����_distinct, kunshu_target, leader_represent, topAlly_represent) == 1)return 4;
				
			}
			
			
			
			/// SCENE: Player ���տ���	
			
			s_fa_unAlly_forces = �����ı⼼��;
			s_fa_alliancePlayers = alliancePlayers;
			s_fa_leader_force_id = force_leader.get_id();
			s_fa_target_force_id = target_force_id;
			s_fa_alliance_force = ���ձ�����_distinct;
			pk::scene(pk::scene_t(Scene_FormingAlliance));
			alliancePlayers = s_fa_alliancePlayers;
			
			/// �÷��̾�� �����Ŀ��� ���ձ��� ������ ȥ���� ���
			// util.prnt("is_alliance_toSay=["+is_����ҿ��ռ���+"] is_player_involved=["+is_�÷��̾�_����(alliancePlayers)+"] ");
			if(!is_����ҿ��ռ��� and !is_�÷��̾�_����(alliancePlayers) )return 2;
			
			
			
			
			// ���� ���� �� �������� & ��ȣ�� ����
			// ���°� �� �� ���� ��������
			array<array<int8>> ���ռ��´뼼�°��ѹ�(����_��, array<int8>(����_��, -1));
			array<int> �������ռ���;
			for (int k = 0; k < ���ձ�����.length; k++){	
				pk::force@ force0 = pk::get_force(���ձ�����[k].���ձ�����);
				int ally0_id = force0.get_id();
				for (int l = k; l < ���ձ�����.length; l++){					
					pk::force@ force1 = pk::get_force(���ձ�����[l].���ձ�����);										
					int ally1_id = force1.get_id();		
					
					if(���ձ�����[l].���ձ����� == ���ձ�����[k].���ձ�����){setAllianceAttackFlag(alliancePlayers, ally0_id, ally1_id, �������ռ���); continue;}
					
					// �������� �� �����ΰ�?
					if(!pk::is_enemy(ally0_id, target_force_id))continue;
					if(!pk::is_enemy(ally1_id, target_force_id))continue;
					
					if(���ռ��´뼼�°��ѹ�[ally0_id][ally1_id] == 1)continue;
					if(���ռ��´뼼�°��ѹ�[ally1_id][ally0_id] == 1)continue;		
					// line_bigO++;
					���ռ��´뼼�°��ѹ�[ally0_id][ally1_id] = 1;
					���ռ��´뼼�°��ѹ�[ally1_id][ally0_id] = 1;
					
					
					// �÷��̾ ������ �������� ���,	
					if(	(alliancePlayers[ally0_id].first and !alliancePlayers[ally0_id].second) or
						(alliancePlayers[ally1_id].first and !alliancePlayers[ally1_id].second)
					){						
						pk::add_relations(ally0_id, ally1_id, -30);	
						continue;
					}
					
					// pk::printf(pk::encode("ceasefire ally0_kunshu=["+force0.kunshu+"] ally1_kunshu=["+force1.kunshu+"] \n"));
					
					pk::add_relations(ally0_id, ally1_id, 20);					
					pk::set_ceasefire_timer(force0, force1, 20);
					
					setAllianceAttackFlag(alliancePlayers, ally0_id, ally1_id, �������ռ���);
					
				}
			}
			�������ο��ռ���.insertLast(�������ռ���);
			// util.prnt("insert alliance_being_forces count=" + �������ο��ռ���.length);
			
			
			// ����
			// util.prnt("AllianceInfos length=["+���ձ�����.length+"]");
			for (int i = 0; i < ��������.length; i++){
				UnitInfo info = ��������[i];
				pk::building@ �����ǹ� = pk::get_building(info.����_����);
				if(!pk::is_enemy(�����ǹ�.get_force_id(), target_force_id))continue;
				pk::building@ building2 = pk::get_building(info.����_��ǥ);
				
				// util.prnt("UnitInfos i=["+i+"] num_unit=["+info.����_�δ��+"] city0=["+info.����_����+"] city2=["+info.����_��ǥ+"]");				
				for (int j = 0; j < info.����_����.length; j++){					
					CreateAUnit(pk::get_person(info.����_����[j]), �����ǹ�, pk::get_building(info.����_��ǥ), leaderEff, info.����_���￩��, j, info.isReinforcement, {});					
				}
			}
			
			
			//pk::printf(pk::encode("------------------------------------------------------ \n"));
			
			
			return -1;
			
		} // end - AllianceAttack
		
		array<int> get_personIds(pk::list<pk::person@> lst){
			array<int> ids;
			string str = "";
			for (int i = 0; i < lst.count; i++){
				ids.insertLast(lst[i].get_id());
				str += lst[i].get_id() + ", ";
			}
			// util.prnt(str);
			return ids;
		}
		array<int> get_personIds(array<pk::person@> arr){
			array<int> ids;
			string str = "";
			for (int i = 0; i < arr.length; i++){
				ids.insertLast(arr[i].get_id());
				str += arr[i].get_id() + ", ";
			}
			// util.prnt(str);
			return ids;
		}
		array<int> get_personIds(array<int> arr){
			array<int> ids;
			string str = "";
			for (int i = 0; i < arr.length; i++){
				ids.insertLast(arr[i]);
				str += arr[i] + ", ";
			}
			// util.prnt(str);
			return ids;
		}
		
		array<int> get_forceIds(array<int> arr){
			array<int> ids;
			string str = "";
			for (int i = 0; i < arr.length; i++){
				ids.insertLast(arr[i]);
				str += arr[i] + "("+���ºΰ��Ӽ�[arr[i]][�Ӽ�_����] +"), ";
			}
			// util.prnt(str);
			return ids;
		}
		///  �ߺ� ���� ����. 
		///  arr0 : ��� ���
		///  arr1 : ���� ���	
		array<int> remove_�ߺ�_persons(array<int> arr0, array<pk::person@> arr1){			
			array<int> arr2;
			for (int j = 0; j < arr1.length; j++){
				pk::person@ p1 = arr1[j];				
				int idx_p1 = arr0.find(p1.get_id());
				// util.prnt("p1=["+p1.get_id()+"] index=["+idx_p1+"]");
				if(idx_p1 >= 0){
					// util.prnt("REMOVE double_person=["+p1.get_id()+"] index=["+idx_p1+"]");
					arr0.removeAt(idx_p1); 
				}
			}
			
			return arr0;
		}
		
		/// ������ �� ������ ������ ��� x�� ������ �Ǵ��� 
		bool isAroundEnemyThreat(pk::city@ city0){
			int troops0 = pk::get_troops(city0);
			pk::force@ force0 = pk::get_force(city0.get_force_id());
			array<int> neighbor_cities = neighborMap.��������[city0.get_id()];
			for (int i = 0; i < neighbor_cities.length; i++){
				pk::city@ neighbor_city = pk::get_city(neighbor_cities[i]);
				int force_id = neighbor_city.get_force_id();
				if(!pk::is_alive(neighbor_city) or !pk::is_valid_force_id(force_id))continue;				
				if(!pk::is_enemy(force0, pk::get_force(force_id)))continue;	// ���� �ƴѰ�?			
				int troops2 = pk::get_troops(neighbor_city);
				// ������ ���ݿ� ���� ������ ���� �Ǵ�
				if(isEnemyThreat(pk::get_person(force0.kunshu), troops0, troops2)){
					// util.prnt("EnemyThreat TRUE  city0_troops=["+pk::get_troops(city0)+"] enemy_city_troops=["+troops+"] ");
					return true;
				}
			}
			return false;
		}
		
		/// ������ ���ݿ� ���� ���� ����ų�� ���θ� ���Ѵ�. 
		bool is_���պ��º�(pk::person@ kunshu0, int ����_���ձ�, int ����_������, float ���ֹ��)
		{
			// util.prnt("kunshu=["+kunshu0.get_id()+"] Character=["+kunshu0.character+"] Alliance=["+����_���ձ�+"] Enemy=["+����_������+"] return: "+(����_������ / float(pk::max(����_���ձ�, 1)))+" <= "+���ֹ��+" ");	
			if( (����_������ / float(pk::max(����_���ձ�, 1))) <= ���ֹ��)
				return true; // ���ռ���			
			return false; // ���ս���						
		}
		
		/// �� ���� ������ ���� �Ǵ�
		bool isEnemyThreat(pk::person@ kunshu0, int troops0, int troops2)
		{			
			float ���ֹ�� = get_���ֹ��_���谨��(kunshu0);
			float ���º��� = troops2 / float(pk::max(troops0, 1));
			// util.prnt("isEnemyThreat kunhsu_val=["+���ֹ��+"] troops_val=["+���º���+"]");
			if(���º��� < ���ֹ��)return false;
			return true;
		}
		
		/// �������ú����� ���絵�ú��� ��� ������ �ΰ�?
		float get_���ֹ��_���谨��(pk::person@ kunshu){
			switch (kunshu.character)
			{
			case ����_�ҽ�:				
				return 1.5;
			case ����_����: 	
				return 2.0;
			case ����_���: 
				return 2.5;
			case ����_����: 
				return 3.0;
			}
			return 2.0;
		}
		
		/// ���ձ����� ��� ���������� ������ ������ ����ų �� �ִ°�?
		float get_���ֹ��_���պ�����(pk::person@ kunshu){
			switch (kunshu.character)
			{
			case ����_�ҽ�:				
				return 1.5;
			case ����_����: 	
				return 2.0;
			case ����_���: 
				return 2.5;
			case ����_����: 
				return 3.0;
			}
			return 1.5;
		}	
		
		/// ���ձ����� ��� ���������� ������ ��Ź����� ��°�?		
		/// relations: ���ֿ� ���������� ��ȣ��
		float get_���ֹ�Ź��(pk::person@ kunshu, int relations){
			float rel = pk::max(((100 - relations) / 100.f), �����ּҹ�Ű��);		
			// util.prnt("kunshu.character="+kunshu.character+" relations="+relations+" rel="+rel+"");			
			switch (kunshu.character)
			{
			case ����_�ҽ�:					
				return 1.5 * rel;
			case ����_����: 	
				return 2.0 * rel;
			case ����_���: 
				return 2.5 * rel;
			case ����_����: 
				return 3.5 * rel;
			}
			return 1.0 * rel;
		}
		
		
		bool is_�÷��̾�_����(array<pk::bool_bool> arr){			
			for (int i = 0; i < arr.length; i++){
				if(!arr[i].first)continue; // ���ձ� �ĺ��ΰ�?
				if(arr[i].second)return true; // ���ձ� �����ߴ°�?
			}
			return false;
		}
		
		void setAllianceAttackFlag(array<pk::bool_bool> alliancePlayers, int ally0_id, int ally1_id, array<int> &�������ռ���){
			
			// ���� ���� ���µ��� ���𳻿� �ߺ� ���� �߻� ����
			���ռ�������[ally0_id] = ���ռ�������_�ϼ�;
			���ռ�������[ally1_id] = ���ռ�������_�ϼ�;					
			
			if(�������ռ���.find(ally0_id) < 0)�������ռ���.insertLast(ally0_id);
			if(�������ռ���.find(ally1_id) < 0)�������ռ���.insertLast(ally1_id);
			
			// �÷��̾� �����ΰ�?
			if(alliancePlayers[ally0_id].first)����_���ռ���[ally0_id] = ����_���ռ�������_�ϼ�;
			if(alliancePlayers[ally1_id].first)����_���ռ���[ally1_id] = ����_���ռ�������_�ϼ�;
		}
		
		array<int> s_fa_unAlly_forces;
		pk::array<pk::bool_bool> s_fa_alliancePlayers;
		int s_fa_leader_force_id = -1;
		int s_fa_target_force_id = -1;
		array<int> s_fa_alliance_force; // �÷��̾� ���ÿ��ΰ� �ݿ��� ���� ���� ���ձ�����.
		bool is_����ҿ��ռ��� = true;
		
		void Scene_FormingAlliance()
		{
			
			pk::force@ force_leader = pk::get_force(s_fa_leader_force_id);
			pk::force@ force_target = pk::get_force(s_fa_target_force_id);
			string leader_kunshu_name = pk::decode(pk::get_name(pk::get_person(force_leader.kunshu)));	
			string target_kunshu_name = pk::decode(pk::get_name(pk::get_person(force_target.kunshu)));				
						
								
			// ���ձ� �÷��̾� ����ŭ ����
			bool is_read = false;
			for (int i = 0; i < s_fa_alliancePlayers.length; i++){					
				if(s_fa_alliancePlayers[i].first == false)continue;
				
				pk::force@ force_player = pk::get_force(i);	// i �� force_id �ΰ�? +1 �ؾ� force_id �ΰ�			
				bool isPlayerAllianceLeader = (force_player.get_id() == s_fa_leader_force_id);
				string player_kunshu_name = pk::decode(pk::get_name(pk::get_person(force_player.kunshu)));				
				// pk::person@ speaker = getGunshiOrMunkwan(force_player);	
				
				/// �÷��̾�� ��� ����. �� ��.
				if(!is_read and !isPlayerAllianceLeader){
					pk::fade(0);
					pk::sleep();
					pk::background(85);
					pk::fade(255);
					pk::play_se(16);
					
					pk::message_box(pk::encode(
						"���� \x1b[16x"+target_kunshu_name+"\x1b[0x"+hanFix.return_chosa(target_kunshu_name,0)+" ������ ���� �����ϰ�, �ܷ����� �纹�� ä���, ������ ���ϰ� ����� ��Ż�ߴ�. \x1b[1x"+leader_kunshu_name+"\x1b[0x"+hanFix.return_chosa(leader_kunshu_name,0)+" ���� ��� ������ ����϶�."
					));
					is_read = true;
				}
				
				
				if(isPlayerAllianceLeader){ 
					s_fa_alliancePlayers[i].second = true;
				}
				else{
					/// �������� �����̾��ٰ� �ı��ϴ� ���
					string str_�ı����� = "";
					bool is_������ = !pk::is_enemy(force_player, force_target);
					if(is_������)str_�ı����� = "������ �ı��ϰ� ";						
						
					if(pk::choose(pk::encode("\x1b[2x"+player_kunshu_name+"\x1b[0x��, "+str_�ı�����+"\x1b[16x��"+target_kunshu_name+"����\x1b[0x���� �����մϱ�?"), { pk::encode("��"), pk::encode("�ƴϿ�") }) != 1){ // ��
						s_fa_alliancePlayers[i].second = true;						
						if(is_������)s_fa_unAlly_forces.insertLast(i);
					}						
					else{  // �ƴϿ�					
						s_fa_alliance_force.removeAt(s_fa_alliance_force.find(i));		
						int idx_unAlly = s_fa_unAlly_forces.find(i);						
						if(idx_unAlly >= 0)s_fa_unAlly_forces.removeAt(idx_unAlly);
					}						
				}
			}			
			
			// �������� �����̾��ٰ� �ı��ϴ� ���� �޼���
			for (int i = 0; i < s_fa_unAlly_forces.length; i++){	
				pk::force@ force = pk::get_force(s_fa_unAlly_forces[i]);
				pk::person@ kunshu = pk::get_person(force.kunshu);
				string kunshu_name0 = pk::decode(pk::get_name(pk::get_person(force.kunshu)));
				string kunshu_name2 = pk::decode(pk::get_name(pk::get_person(force_target.kunshu)));	
				pk::unally(force, force_target.get_id());
				pk::add_relations(force, force_target.get_id(), -100);
				pk::message_box(pk::encode("\x1b[1x"+kunshu_name0+"\x1b[0x"+hanFix.return_chosa(kunshu_name0,3)+" \x1b[1x"+kunshu_name2+"\x1b[0x"+hanFix.return_chosa(kunshu_name2,2)+" ������ \x1b[16x�ı�\x1b[0x�߽��ϴ�"), pk::get_person(����_����));	
			
			}
			
			auto allyForces_say = s_fa_alliance_force;
			allyForces_say.removeAt(allyForces_say.find(s_fa_leader_force_id));//��޴�� -> ���� ����		
			string msg_���ձ����̸� = getAllianceKunshuNames(allyForces_say, s_fa_target_force_id);
			is_����ҿ��ռ��� = (msg_���ձ����̸� != "");
			
			if(is_����ҿ��ռ���){
				pk::background(11);
				pk::play_se(10); //25?
				pk::message_box(pk::encode("���� \x1b[1x"+leader_kunshu_name+"\x1b[0x"+hanFix.return_chosa(leader_kunshu_name,2)+" \x1b[16x��"+target_kunshu_name+"����\x1b[0x�� �Ἲ�߽��ϴ�\n���ձ����� \x1b[1x"+msg_���ձ����̸�+"\x1b[0x"+hanFix.return_chosa(msg_���ձ����̸�,2)+" �����߽��ϴ�."));					
			}
			
			// ��Ȳ3: �������� �÷��̾��� ���.
			if(force_target.is_player() and is_����ҿ��ռ���){				
				pk::person@ player_is_target_speaker = getGunshiOrMunkwan(force_target);
				
				pk::background(11);
				pk::play_se(11);
				pk::message_box(pk::encode("\x1b[2x"+target_kunshu_name+"\x1b[0x��, \x1b[16x"+leader_kunshu_name+" ���ձ�\x1b[0x�� �츮 ����� ó������ �ֽ��ϴ�"), player_is_target_speaker);
			}
			
			pk::background(-1);
			
		}
		
		string getAllianceKunshuNames(array<int> force_ids, int force_target_id){
			string msg = "";
			for (int i = 0; i < force_ids.length; i++){				
				if(!pk::is_enemy(force_ids[i], force_target_id))continue;
				// util.prnt("is_Enemy ["+pk::get_force(force_ids[i]).kunshu+"] with ["+pk::get_force(force_target_id).kunshu+"]");
				
				string kunshu_name = pk::decode(pk::get_name(pk::get_person(pk::get_force(force_ids[i]).kunshu)));				
				if(i == force_ids.length - 1)msg += kunshu_name;
				else msg += kunshu_name + " ";
				
			}
			return msg;
		}
		
		bool isPort(int building_id){
			for (int i = �ǹ�_�ױ�����; i <= �ǹ�_�ױ���; i++){
				if(i == building_id)return true;
			}
			return false;
		}
		
		bool isGate(int building_id){
			for (int i = �ǹ�_��������; i <= �ǹ�_������; i++){
				if(i == building_id)return true;
			}
			return false;
		}
		
		
		
		
		// ��ǥ �ǹ��� ������ ���ձ� ���� Ž���ؼ� ����
		void prepareReinforcement(
			pk::building@ building2, 
			array<AllianceInfo@> &���ձ�����, 
			array<int> &����Ƚ��, 
			array<int> arr_���ձ�����, 
			float leaderEff){
					
			pk::city@ city2 = pk::building_to_city(building2);
			array<int> neighbor_cities = neighborMap.��������[city2.get_id()]; // city_ids
			for (int i = 0; i < neighbor_cities.length; i++){
				pk::city@ neighbor_city = pk::get_city(neighbor_cities[i]);					
				if(!pk::is_alive(neighbor_city) or !pk::is_valid_force_id(neighbor_city.get_force_id()))continue;
				int reinforce_id = neighbor_city.get_force_id();	
				pk::force@ reinforce = pk::get_force(reinforce_id);				
				// ���� ������ ��ȿ�Ѱ�?
				if (!pk::is_alive(reinforce) or !pk::is_valid_force_id(reinforce_id))continue;								
				// ���ձ� �Ͽ� �ΰ�?
				if(!isAllianceForce(reinforce_id, arr_���ձ�����))continue;
				
				// util.prnt("Reinforcement kunshu=["+reinforce.kunshu+"] city=["+neighbor_city.get_id()+"] city2=["+city2.get_id()+"] num_go=["+����Ƚ��[neighbor_city.get_id()]+"]");
				���ձ�����.insertLast(AllianceInfo(reinforce_id, neighbor_city.get_id(), city2.get_id(), true));
				����Ƚ��[neighbor_city.get_id()] += 1; // ��ߵ��� ���� ����Ƚ��
					
			}
				
		}
		
		bool isAllianceForce(int force_id, array<int> arr_���ձ�����){
			for (int i = 0; i < arr_���ձ�����.length; i++){	
				
				if(force_id == arr_���ձ�����[i])return true;
			}
			return false;
		}
		
		
		
		// ���ձ� ���� ���� VS ���ձ��ִ뼼�� ����
		// �̱�� 0, ���� 1
		int DebateForAllyVSAlly(array<int> ���ձ�����_distinct, pk::person@ target_kunshu, pk::person@ promoter0, pk::person@ counterpartner)
		{
			int result = 1;
			
			// �����ְ� �÷��̾�� ����
			if(promoter0.is_player()){
				s_pvsp_target_kunshu_id = target_kunshu.get_id();
				s_pvsp_promoter0_id = promoter0.get_id();
				s_pvsp_counterpartner_id = counterpartner.get_id();
				
				pk::scene(pk::scene_t(Scene_PromoterVSPromoter));					
				result = s_pvsp_result;
				
			}
			else{
				
				// if(!�߻��ٶ�������)return 0;
				
				result = WishDecSumForDebate(���ձ�����_distinct, target_kunshu);
				
			}
			
			return result;
			
		}
		
		/// ���ռ��¹迭 ���
		array<int> get_���ձ����¹迭(array<AllianceInfo@> ���ձ�����){
			array<int> arr_���ձ�����;
			for (int i = 0; i < ���ձ�����.length; i++){
				arr_���ձ�����.insertLast(���ձ�����[i].���ձ�����);
			}
			return arr_���ձ�����;
		}
		
		
		int WishDecSumForDebate(array<int> ���ձ�����_distinct, pk::person@ target_kunshu){
			
			pk::force@ force_target = pk::get_force(target_kunshu.get_force_id());
			
			// ���ձ��� �������� ���� �ٶ��� �� Ȯ��
			
			array<int> force_ids_sorted = util.bubble_sort_desc(���ձ�����_distinct, ���ձ�����_distinct.length);		
			
			
			float likeDec = 0.f;
			float disLikeDec = 0.f;
			
			// int tmp = -1; // For Distinct
			for (int i = 0; i < force_ids_sorted.length; i++){				
				// if(force_ids_sorted[i] == -1)break;
				// �ߺ� �Ÿ���
				// if(tmp == force_ids_sorted[i])continue;
				// tmp = force_ids_sorted[i];
				int force_id_alliance = force_ids_sorted[i];;
				
				float valJudge = floor(���´��Ǵܰ��[force_id_alliance][force_target.get_id()] * 100) / 100.f;
				valJudge = pk::get_force(force_id_alliance).relations[force_target.get_id()] <= 0 ? -1 : valJudge; // ��ȣ���� 0�̸�. �������� ģ���� ��̰� �ƿ����°����� �Ǵ�.
				
				// pk::printf(pk::encode("kunshu=["+pk::get_force(force_id_alliance).kunshu+"] valJudge=["+valJudge+"] \n"));
				
				if(valJudge < 0){ disLikeDec += -valJudge; }
				else { likeDec += valJudge; }
				
			}
			float ��_like = likeDec + disLikeDec == 0 ? 1 : likeDec + disLikeDec;
			float sumWishDec = disLikeDec / ��_like;
			
			
			bool isSuccess = getRandom((sumWishDec * 100) + �߰����ռ�����, 11);
			
			// pk::printf(pk::encode("WishDecSumForDebate isSuccess=["+isSuccess+"] sumWishDecPerc=["+(sumWishDec * 100)+"] \n"));
			
			return isSuccess ? 0 : 1;
			
			
		}
		
		
		int s_pvsp_target_kunshu_id = -1;
		int s_pvsp_promoter0_id = -1;
		int s_pvsp_counterpartner_id = -1;
		int s_pvsp_result = 1;
		
		void Scene_PromoterVSPromoter()
		{
			
			pk::fade(0);
			pk::sleep();
			pk::background(53);
			pk::fade(255);
						
			pk::person@ promoter0 = pk::get_person(s_pvsp_promoter0_id);
			pk::person@ promoter1 = pk::get_person(s_pvsp_counterpartner_id);
			pk::person@ target_kunshu = pk::get_person(s_pvsp_target_kunshu_id);
			
			string target_kunshu_name = pk::decode(pk::get_name(target_kunshu));
			string promoter1_talk1 = "���� õ���� �뼼�� \x1b[2x"+target_kunshu_name+"\x1b[0x"+hanFix.return_chosa(target_kunshu_name,5)+" �Ѿ��. �ѳ����� ����� ���ϰ�, �νɵ� ������ �ְŴ� ���� õ���� �帧�� �Ž����� ���� ����Ų�� ���̿�?";
			pk::message_box(pk::encode(promoter1_talk1), promoter1);	
			pk::message_box(pk::encode("���Ķ�!"), promoter0);
			s_pvsp_result = pk::debate(promoter0, promoter1, true, false).first;
			
			pk::background(-1);
			
		}
		
		
		
		
		bool is_beingAtWar(pk::building@ building)
		{
			
			array<pk::point> arr = pk::range(building.get_pos(), 1, ���������Ǵ�_����);
			for (int j = 0; j < arr.length; j++)
			{
				auto obj = pk::get_hex_object(arr[j]);
				if(obj is null or obj.get_force_id() < 0)continue;
				
				if (pk::is_enemy(building, obj))return true;
				
				
			}
			// util.prnt("isAtWar building=["+building.get_id()+"] [false]");
			return false;
		}
		
		
		array<int> isAtWarEnemies(pk::building@ building)
		{
			int ������̵��ε��� = 0;
			array<int> ������̵�((pk::get_unit_list()).count, -1); // �ε���0 ���� ������ ����
			array<pk::point> arr = pk::range(building.get_pos(), 1, ���������Ǵ�_����);
			for (int j = 0; j < arr.length; j++)
			{
				pk::unit@ dst = pk::get_unit(arr[j]);					
				if (dst is null)continue;

				if (pk::is_enemy(building, dst)){
					
					������̵�[������̵��ε���+=1] = dst.get_id();
					
				}
				
			}
			������̵�[0] = ������̵��ε���;
			return ������̵�;
		}
		
		
		
		
		int GetTroops(pk::person@ mem0)
		{
			int maxCommnd = pk::get_rank(mem0.rank).command;	
			pk::force@ force= pk::get_force(mem0.force_id);

			if(force.kokugou == ��ȣ_Ȳ��)
			{
				maxCommnd = 15000;
			}
			else if(mem0.mibun == �ź�_����)
			{
				switch(force.title)
				{
					case ����_Ȳ��:maxCommnd=15000;break;
					case ����_��:
					case ����_��:maxCommnd=14000;break;
					case ����_��縶:
					case ����_���屺:maxCommnd=13000;break;
					case ����_�����߶���:
					case ����_�츲�߶���:maxCommnd=12000;break;
					case ����_�ָ�:
					case ����_���ڻ�:maxCommnd=11000;break;
					default: maxCommnd=10000; break;
				}
			}
			
			if(pk::has_tech(force, �ⱳ_��������))
				maxCommnd += 3000;
			
			return maxCommnd;
		}
		
		
		
		void CreateAUnit(pk::person@ mem0, pk::building@ base, pk::building@ base2, float costPercentage, bool isAtWar, int idxNumUnit, bool isReinforcement, array<int> ������̵� )
		{
						
			if(!pk::is_valid_person_id(mem0.get_id()) or !pk::is_alive(mem0))return;
			
			int rank_troops = pk::get_rank(mem0.rank).command;	
			rank_troops = GetTroops(mem0);
			// int distance = pk::get_distance(base.get_pos(), base2.get_pos()); /// ĭ �� 
			// int ��_distance = ceil(distance / ����_ĭ�̵���); /// �ɸ��� �ð�. x��
			
			// int building_distance = pk::get_building_distance(base.get_id(), base2.get_id(), base.get_force_id());
			// int city_distance = pk::get_city_distance(pk::building_to_city(base).get_id(), pk::building_to_city(base2).get_id());
			// int point_distance = pk::get_distance(base.get_pos(), base2.get_pos()); // ����̵��Ҹ� 5 25ĭ�̸� �Ҹ� �̵��� 75 �̵��� 25�� �⸶���� �����ϴµ��� 3���� �ɸ���.
			// util.prnt("base=["+base.get_id()+"] base2=["+base2.get_id()+"] get_distance=["+point_distance+"] get_city_distance=["+city_distance+"] get_building_distance=["+distance+"] distance_x10=["+��_distance+"] ");			
			
			int troops = rank_troops;
			
			
			
			
			
			
			int gold = �δ����_��;
			// int food = int((troops / 10.0) * ��_distance * 2.0);
			int food = int(troops * �δ����_��������);
						
			// ���� ����
			bool isLackingTroops = false;
			bool isLackingGold = false;
			bool isLackingFood = false;			
			
			if( pk::get_troops(base) < troops ){ 
				isLackingTroops = true;
				if(!�׻��ִ뺴������)troops = �ּ��������¼�;
			}			
			int cost_gold = int(gold * costPercentage);
			int cost_food = int(food * costPercentage);				
			if( pk::get_gold(base) <= gold ){isLackingGold = true;}
			if( pk::get_food(base) <= food ){isLackingFood = true;}
			
			if(isLackingFood)return;
			if(����_���ú��³� and isLackingTroops)return;
			
			// ������ �δ� �������� ���� ������ �δ븦 �������� �ʴ´�.		
			pk::point emptyPos = getEmptyPos(base);
			if(!pk::is_valid_pos(emptyPos))return;
			
			// �ִ� ���� �߿� ����
			int best_weapon_id = getBestWeaponId(base, mem0);
			int cost_weapon = int(troops * costPercentage);				
			pk::unit@ unit = pk::create_unit(base, mem0, null, null, troops, best_weapon_id, ����_�ְ�, gold, food, emptyPos);
			
			
			// �δ� ������ ������ ��� ���� ����
			if (!pk::is_alive(unit)){ pk::remove(unit);return; }

			// ��� ����(pk::create_unit �Լ��� ù ��° �Ķ���ͷ� �����ߴٸ� �ʿ����.)
			//unit.energy = 100;

			// int enemy_leader_id = -1; // for Debug
			
			// if(isReinforcement){
				// pk::set_order(unit, �δ��ӹ�_����, base2.get_pos());				
			// }
			// else{				
				// if(isAtWar){
					// pk::set_order(unit, �δ��ӹ�_����, base2.get_pos());
				// }
				// else{
					// pk::set_order(unit, �δ��ӹ�_����, base2.get_pos());
				// }				
			// }
			pk::set_order(unit, �δ��ӹ�_����, base2.get_pos());
			
			// ���� ���� ����			
			if(!isLackingTroops)pk::add_troops(base, -int(unit.troops));
			if(!isLackingGold)pk::add_gold(base, -cost_gold);
			if(!isLackingFood)pk::add_food(base, -cost_food);
			int weapon_count = isSiegeWeapon(best_weapon_id) ? 1 : cost_weapon;
			pk::add_weapon_amount(base, best_weapon_id, -weapon_count);
			
			// util.prnt("leader=["+unit.leader+"] force_kunshu=["+pk::get_force(unit.get_force_id()).kunshu+"] base0=["+base.get_id()+"] base2=["+base2.get_id()+"] troops=["+unit.troops+"] order=["+unit.order+"] isReinforcement=["+isReinforcement+"] ");
			
			
		}
		
		pk::point getEmptyPos(pk::building@ building_)
		{
			auto arr = pk::range(building_.get_pos(), 1, 3);
			for (int i = 0; i < arr.length; i++)
			{
				pk::hex@ hex = pk::get_hex(arr[i]);
				int terrain_id = hex.terrain;
				
				//pk::printf(pk::encode("terrain id=["+terrain_id+"] is_enabled_terrain=["+pk::is_enabled_terrain(terrain_id)+"] is_valid_terrain_id=["+pk::is_valid_terrain_id(terrain_id)+"] is_water_terrain=["+pk::is_water_terrain(terrain_id)+"] \n"));
				
				if (!hex.has_building 
					and !hex.has_unit 
					and pk::is_valid_terrain_id(terrain_id) 
					and pk::is_enabled_terrain(terrain_id)
					and terrain_id != ����_��
					and terrain_id != ����_��
				)return arr[i];
				
			}
			return -1;
		}
		
		
		int getBestWeaponId(pk::building@ base, pk::person@ person)
		{
			pk::force@ force = pk::get_force(person.get_force_id());
			pk::city@ city = pk::building_to_city(base);			
			
			// �ְ� ����
			int best_tekisei = ����_C;
			int best_weapon_id = ����_��;
			for (int i = 0; i < ����_��; i++)
			{
				if(����_���ú��³� and pk::get_weapon_amount(base, i) <= 0)continue;
				if(isSeaWeapon(i))continue;				
				if(i == ����_��� and !pk::has_tech(force, �ⱳ_�������))continue;
				
				int tekisei = i == ����_�� ? 0 : person.tekisei[pk::equipment_id_to_heishu(i)];
				if(best_tekisei < tekisei)best_weapon_id = i;
				
				// pk::printf(pk::encode(pk::format("getBestWeaponId i={} person.tekisei={} best_tekisei={} \n",i, tekisei, best_tekisei )));
				
				best_tekisei = pk::max(tekisei, best_tekisei);
				
			}
			
			return best_weapon_id;
		}
		
		bool isSeaWeapon(int weapon_id){return (weapon_id >= ����_�ְ�);}
		
		bool isSiegeWeapon(int weapon) { return (weapon >= ����_���� && weapon <= ����_���); }
		
		float getPersonEffect(pk::person@ person_)
		{
			
			float person_effect = 0.1f;
			
			if(pk::is_alive(person_)){
				person_effect = (person_.stat[����ɷ�_���]
					 + person_.stat[����ɷ�_����]
					 + person_.stat[����ɷ�_����]
					 + person_.stat[����ɷ�_��ġ]
					 + person_.stat[����ɷ�_�ŷ�]
				) / float(����ɷ�_�� * 100.f);
			}
			
			return person_effect;
			
		}
		
		float getDistinctEffect(int stat, float divisor, int8 diff)
		{
			if(stat >= divisor)return 0.9f;		
			//return (stat / divisor) * (stat/ divisor) * (stat/ divisor);
			
			float stat1 = (stat / divisor);
			
			while (diff > 0){
				diff -= 1;
				float val = stat1 * (stat / divisor);
				stat1 = floor(val * 100) / 100.0f;	// ����			
			}
			
			return stat1;
			
		}
		
		
		// �Ӽ� �� ����
		
		void setForceAttributes()
		{			
			
			
			// ���´� ������ �ʿ��� ���� ���⼭ �����Ѵ�.
			// �ϳ� �þ ������ '�Ӽ���_��' +1
			
			
			pk::list<pk::force@> force_list = pk::get_force_list(false);
			
			
			for (int i = 0; i < force_list.count; i++){
				if(isIminzoku(force_list[i]))continue;
				
				int force_id = force_list[i].get_id();				
				
				setDistrictAttrSum(force_list[i]);
				
				setForceTroopsRanking(force_id);
				
				// �ܱ� ��� ã��
				setNegotiationTarget(force_list[i]);
				
			}
			
			
			setTop10MujangAttrSum();
			
		}
		
		void setForceTroopsRanking(int force_id)
		{
							
			// ���� ���� ���ϱ�
			for (int j = 0; j < 47; j++){
				double ���������º��� = rank_���º���[j] == -1 ? 0 : ���ºΰ��Ӽ�[rank_���º���[j]][�Ӽ�_����];
				
				if( ���������º��� < ���ºΰ��Ӽ�[force_id][�Ӽ�_����]){	
				
					int8 tmpForceId = -1;
					int8 tmp2ForceId = -1;
					
					for (int l = j; l < 47; l++){		
						if(l > j){
							if(tmpForceId == -1)break;
							tmp2ForceId = rank_���º���[l];
							rank_���º���[l] = tmpForceId;
							tmpForceId = tmp2ForceId;
						}	
						else {
							tmpForceId = rank_���º���[l];
							rank_���º���[j] = force_id;								
						}							
					}						
					break;
				}					
				
			}
			
		}
		
		// ����: �̿��� ���� ������ �ܱ����� �ʴ´�.
		void setNegotiationTarget(pk::force@ force0)
		{
			int force0_id = force0.get_id();
			int strategic = pk::get_person(force0.kunshu).strategic_tendency;
			
			int depth = 0;
			if(strategic == ��������_��ȭ����){
				depth = 3;
			}
			else if(strategic == ��������_������){ 
				depth = 1;
			}
			else if(strategic == ��������_��������){	
				depth = 0;
			}
			else { // ����
				depth = 2;
			}
			
			
			FindNegoTarget(force0_id, -1, force0, depth);
			
		}
		
		
		void FindNegoTarget(int root, int force0_id_prev, pk::force@ force0, int depth)
		{
			if(depth < 1)return;
			
			int force0_id = force0.get_id();
			if(force0_id_prev != force0_id)depth -= 1;
			
			pk::list<pk::force@> force_list = pk::get_force_list(false);
			for (int i = 0; i < force_list.count; i++){				
				
				if(isIminzoku(force_list[i]))continue;					
				int force1_id = force_list[i].get_id();	
				if(force1_id == root)continue;	
				if(force1_id == force0_id)continue;	
				// if(���¿ܱ����[root][force1_id] == 1)continue;
				
				
				if(pk::is_neighbor_force(force0, force_list[i]))
				{
					���¿ܱ����[root][force1_id] = 1;	
					
					// ���� Ŭ ���� �ְ�
					���´뼼�°Ÿ�[root][force1_id] = pk::min(3 - depth, ���´뼼�°Ÿ�[root][force1_id]); // depth = 0, 1, 2
									
					// util.prnt("FindNegoTarget root=["+pk::get_force(root).kunshu+"] force0_id=["+pk::get_force(force0_id).kunshu+"] force1_id=["+pk::get_force(force1_id).kunshu+"] depth=["+depth+"] distance=["+(3 - depth)+"]");
					
					FindNegoTarget(root, force0_id, pk::get_force(force1_id), depth);
					
				}
			}
			
		}
		
		// ���� �ϳ� ���ܵ� �Ӽ��� ��
		void setDistrictAttrSum(pk::force@ force)
		{			
			int force_id = force.get_id();	
			
			pk::list<pk::district@> force_district_list = pk::get_district_list(force);
			
			//�ʱ�ȭ
			���ºΰ��Ӽ�[force_id][�Ӽ�_���ü�]	= 0;
			���ºΰ��Ӽ�[force_id][�Ӽ�_�����]	= 0;
			���ºΰ��Ӽ�[force_id][�Ӽ�_����]	= 0;
			
			for (int i = 0; i < force_district_list.count; i++)
			{				
				auto district = force_district_list[i];
				if (!pk::is_alive(district))continue;
				
				���ºΰ��Ӽ�[force_id][�Ӽ�_���ü�] += district.query_value(���ܼӼ�_���ü�);
				���ºΰ��Ӽ�[force_id][�Ӽ�_�����] += district.query_value(���ܼӼ�_�����);
				���ºΰ��Ӽ�[force_id][�Ӽ�_����] 	+= district.query_value(���ܼӼ�_����);
			}
			
				
		}
		
		void setTop10MujangAttrSum()
		{
			
			// ���º� ž10 ����� ����
			array<int> ����ž10(����_��, 0);
			pk::list<pk::person@> mujang_list = pk::get_person_list(pk::mibun_flags(�ź�_����, �ź�_����, �ź�_�¼�, �ź�_�Ϲ�));
			
			
			// ���� �빫 ��������
			mujang_list.sort(function(a, b)
			{
				int sum_a = a.stat[����ɷ�_���] + a.stat[����ɷ�_����];
				int sum_b = b.stat[����ɷ�_���] + b.stat[����ɷ�_����];
				return sum_a > sum_b;
			});
			
			// Top 10 ���� ��� + ����
			for (int i = 0; i < mujang_list.count; i++)
			{
				
				auto person = mujang_list[i];
				int force_id = person.get_force_id();
				//pk::printf(pk::encode(pk::format("force_id = {}\n",force_id)));
				if(force_id == -1)continue;
				if(����ž10[force_id] > 9)continue;
				
				���ºΰ��Ӽ�[force_id][�Ӽ�_ž10] 	+= person.stat[����ɷ�_���] + person.stat[����ɷ�_����];
				����ž10[force_id] += 1;
					
			}
			
		}
		
		void setIsAtWar()
		{			
		
			// �δ�
			auto list = pk::list_to_array(pk::get_unit_list());
			for (int l = 0; l < list.length; l++)
			{
				pk::unit@ unit0 = list[l];
				set_��迩��_�����ֺ�(unit0);
				// set_���￩��_�δ��ֺ�(unit0);
			}
			
		}
		
		void setForceGoldFood(){
			array<pk::building@> arr = pk::list_to_array(pk::get_building_list());
			for (int i = 0; i < arr.length; i++)
			{
				pk::building@ building0 = arr[i];
				int force0_id = building0.get_force_id();
				if(!pk::is_alive(building0) or !pk::is_valid_force_id(force0_id))return;
				���ºΰ��Ӽ�[force0_id][�Ӽ�_��] += pk::get_gold(building0);
				���ºΰ��Ӽ�[force0_id][�Ӽ�_����] += pk::get_food(building0);	
			}			
			is_���±ݺ����˻� = true;
		}

		void set_��迩��_�����ֺ�(pk::unit@ unit0){
			pk::city@ city = pk::get_city(pk::get_city_id(unit0.pos));
			// util.prnt("unit_is_enemycity leader=["+unit0.leader+"] on_the_city=["+city.get_id()+"] is_warning=["+pk::is_enemy(city, unit0)+"] ");
			if(pk::is_enemy(city, unit0)){
				���ð�迩��[city.get_id()] = 1;
				
				���´����￩��[city.get_force_id()][unit0.get_force_id()] = 1;
				���´����￩��[unit0.get_force_id()][city.get_force_id()] = 1;
				�����߿���[city.get_force_id()] = 1;
				�����߿���[unit0.get_force_id()] = 1;
				�ǹ����￩��[pk::city_to_building(city).get_id()] = 1;
				
				
			}
		}

		
		
		bool isIminzoku(pk::force@ force)
		{
			if(
				force.kunshu == ����_��ȯ�θ� 
				or force.kunshu == ����_���θ�
				or force.kunshu == ����_����θ�
				or force.kunshu == ����_�����θ� 
				or force.kunshu == ����_����
			)return true;
			return false;
		}
		float BooleanToFloat(pk::bool val)
		{
			if(val){
				return 1.f;
			}
			else{
				return 0.f;
			}
			
		}
		bool intToBoolean(int val){
			return (val == 1);
		}
		
	} // end - Main
	
	/*
	array<array<pk::person@>> ����_����;
			array<int> ����_����;
			array<int> ����_��ǥ;
			array<bool> ����_���￩��;
			array<int> ����_�δ��;
	
	*/

	/// �δ���������
	class UnitInfo{
		
		UnitInfo(){}		
		UnitInfo(array<int> ����_����, int ����_����, int ����_��ǥ, bool ����_���￩��, int ����_�δ��, bool isReinforcement) { 			
			this.����_���� = ����_����;
			this.����_���� = ����_����;
			this.����_��ǥ = ����_��ǥ;
			this.����_���￩�� = ����_���￩��;
			this.����_�δ�� = ����_�δ��;
			this.isReinforcement = isReinforcement;
		}		
		/// property
		array<int> ����_����;
		int ����_����;
		int ����_��ǥ;
		bool ����_���￩��;
		int ����_�δ��;
		bool isReinforcement;
	}
	
	/// ���ձ�����
	class AllianceInfo{
		
		AllianceInfo(){}		
		AllianceInfo(int ���ձ�����, int ��ߵ���, int ��������, bool isReinforcement) { 						
			this.���ձ����� = ���ձ�����;
			this.��ߵ��� = ��ߵ���;
			this.�������� = ��������;
			this.isReinforcement = isReinforcement;
		}		
		/// property
		int ���ձ�����;
		int ��ߵ���;
		int ��������;
		bool isReinforcement;
	}
	
	
	
	
	
	
		
	/*
	@������: ���ɱ�
	@����: �ϼ��� �ѱ��� ��ħ�� ���� ����ó��
	*/
	
	
	
	/**
		���� Ÿ��
	*/
	enum �ѱ�_����Id {
		����_����	 = 0,
		����_����	 = 1,
		����_�̰�	 = 2,
		����_����	 = 3,
		����_�� = 4,
		����_���η�  = 5
	}
		
	class  HanFix
	{
		
		HanFix()
		{
			
		}
		


		array<array<string>> ����_�迭 = { { "��", "��" }, { "��", "��" }, { "��", "��"}, {"��", "��"}, {"��",""}, {"����", "��"} };	

		/**
			�ܾ �´� ���縦 �����մϴ�.
			
			@param s ���縦 ���� �ܾ� 
			@param type ������ ���� �ѱ�_����Id�� ���� �з��մϴ�.
			@return ����
		*/
		string return_chosa(string s, int type)
		{
			if( type < 0 || type > int(����_�迭.length()) ) return s;
			
			if(isJongSung(s))
				return (����_�迭[type][0]);
			else
				return (����_�迭[type][1]);
		}

		/**
			�ܾ ���縦 �ٿ��� �����մϴ�. 
			
			@param s ���縦 ���� �ܾ� 
			@param type ������ ���� �ѱ�_����Id�� ���� �з��մϴ�.
			@return ���縦 ���� �ܾ� 
		*/
		string add_chosa(string s, int type)
		{
			
			if( type < 0 || type > int(����_�迭.length()) ) return s;
			
			if(isJongSung(s))
				return (s + ����_�迭[type][0]);
			else
				return (s + ����_�迭[type][1]);
			
		}

		/**
			�ܾ�(���� ����)�� ���縦 �ٿ��� �����մϴ�. 
			
			@param s ���縦 ���� �ܾ� 
			@param type ������ ���� �ѱ�_����Id�� ���� �з��մϴ�.
			@param color ���� ��ȣ 
			@return ���縦 ���� �ܾ� 
		*/
		string add_chosa_color(string s, int type, int color)
		{
			if( type < 0 || type > int(����_�迭.length()) ) return s;

			if(isJongSung(s))
				return (pk::format("\x1b[{}x{}\x1b[0x{}", color, s, ����_�迭[type][0]));
			else
				return (pk::format("\x1b[{}x{}\x1b[0x{}", color, s, ����_�迭[type][1]));
		}

		/**
			�־��� �ܾ ��ħ(����)�� �ִ����� �˻��Ѵ�.
			
			@param s ���縦 ���� �ܾ�
			@return ��ħ����
		*/

		bool isJongSung(string s)
		{			
			array<string> dictDoubleWord = {
				"��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��",
				"��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "�Ԥ��¤�", "��", "��", "��", "��", "��", "��", "��", "��", "�Ԥ��Ҥ�",
				"��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "�Ԥ��¤�", "��", "��", "��", "�Ԥ��ɤ�", "��", "��", "��", "��", "��",
				"��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "�Ԥ��¤�", "��", "��", "��", "��", "��", "��", "��", "��", "��",
				"��", "�Ԥ�����", "��", "��", "��", "�Ԥ��ˤ�", "��", "�Ԥ��Ф�", "��", "��", "��", "�Ԥ��¤�", "��", "�Ԥ��Ƥ�", "��", "��", "�Ԥ��ͤ�", "��", "��", "��", "��",
				"��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "�Ԥ��¤�", "��", "��", "��", "�Ԥ��ɤ�", "��", "��", "��", "��", "�Ԥ��Ҥ�",
				"��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "�Ԥ��¤�", "��", "��", "��", "�Ԥ��ɤ�", "��", "��", "��", "��", "�Ԥ��Ҥ�",
				"��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "�Ԥ��¤�", "��", "��", "��", "��", "��", "��", "��", "��", "�Ԥ��Ҥ�",
				"��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "�Ԥ��¤�", "��", "�Ԥ��Ƥ�", "�Ԥ��Ȥ�", "�Ԥ��ɤ�", "�Ԥ��ͤ�", "�Ԥ��Τ�", "��", "�Ԥ��Ϥ�", "�Ԥ��Ҥ�",
				"��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "�Ԥ��Ҥ�",
				"��", "�Ԥ�����", "��", "�Ԥ��Ť�", "��", "��", "��", "�Ԥ��Ф�", "��", "��", "��", "�Ԥ��¤�", "��", "�Ԥ��Ƥ�", "��", "��", "��", "��", "��", "��", "��",
				"��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��",
				"��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "�Ԥ��Ҥ�",
				"¥", "¹", "¼", "��", "��", "�Ԥ��ˤ�", "��", "��", "��", "��", "°", "�Ԥ��¤�", "��", "�Ԥ��Ƥ�", "��", "��", "��", "�Ԥ��Τ�", "��", "��", "�Ԥ��Ҥ�",
				"��", "í", "ó", "��", "��", "��", "��", "��", "��", "ġ", "ä", "�Ԥ��¤�", "ü", "��", "��", "�Ԥ��ɤ�", "��", "��", "��", "��", "�Ԥ��Ҥ�",
				"ī", "ļ", "Ŀ", "��", "��", "��", "��", "ť", "ũ", "Ű", "ĳ", "�Ԥ��¤�", "��", "��", "��", "��", "��", "��", "��", "��", "�Ԥ��Ҥ�",
				"Ÿ", "��", "��", "��", "��", "��", "��", "Ʃ", "Ʈ", "Ƽ", "��", "�Ԥ��¤�", "��", "��", "��", "��", "��", "ơ", "��", "Ƣ", "Ʒ",
				"��", "��", "��", "��", "��", "ǥ", "Ǫ", "ǻ", "��", "��", "��", "�Ԥ��¤�", "��", "��", "ǡ", "�Ԥ��ɤ�", "Ǵ", "�Ԥ��Τ�", "ǣ", "Ƕ", "�Ԥ��Ҥ�",
			"��", "��", "��", "��", "ȣ", "ȿ", "��", "��", "��", "��", "��", "�Ԥ��¤�", "��", "��", "ȭ", "ȳ", "��", "��", "ȸ", "��", "��"};
			
			if( s.length() < 2 ) return false;
			
			string last = s.substr(s.length()-2,2);
			
			for(uint i=0; i<dictDoubleWord.length(); i++ )
			{
				if( last == dictDoubleWord[i] )
					return false;
			}
			
			return true;
		}
			
		
	} // end - class
	
	
	
	
	class  Util
	{
		
		
		Util()
		{
			
		}
		
		 
		void prnt(string str)
		{
			pk::printf(pk::encode(str + " \n"));			
		}
		
		array<int> bubble_sort_asce(array<int> list, int n)
		{
		  int c, d, t;
		 
		  for (c = 0 ; c < n - 1; c++)
		  {
			for (d = 0 ; d < n - c - 1; d++)
			{
			  if (list[d] > list[d+1])
			  {
				/* Swapping */
		 
				t         = list[d];
				list[d]   = list[d+1];
				list[d+1] = t;
			  }
			}
		  }
		  return list;
		}
		
		array<int> bubble_sort_desc(array<int> list, int n)
		{
		  int c, d, t;
		 
		  for (c = 0 ; c < n - 1; c++)
		  {
			for (d = 0 ; d < n - c - 1; d++)
			{
			  if (list[d] < list[d+1])
			  {
				/* Swapping */
		 
				t         = list[d];
				list[d]   = list[d+1];
				list[d+1] = t;
			  }
			}
		  }
		  return list;
		}
		
		
	
	}
	
	
	
	
	
	class  NeighborMap
	{		
		array<array<int>> ��������(����_��, array<int>(0, -1));
				
		NeighborMap(){
			init();
		}
		
		void init(){
			mapNeighborCity();
		}
		
		bool isNeighborCity(int building0_id, int building1_id)
		{
			array<int> neighbors = ��������[building0_id];
			for(int i=0; i < neighbors.length; i++ ){
				if(neighbors[i] == building1_id)return true;
			}
			return false;
		}
		
		void mapNeighborCity()
		{
			// ��,���� ���� �� �� �ִ� ���� ������ ����
			
			��������[����_���� ] = {����_����, ����_����, ����_�Ϻ�, ����_���};
			��������[����_���� ] = {����_��, ����_����, ����_����};
			��������[����_��  ] = {����_����, ����_����, ����_����, ����_���, ����_��};
			��������[����_���� ] = {����_����, ����_��, ����_���, ����_����, ����_��};
			��������[����_��� ] = {����_����, ����_��, ����_��, ����_����, ����_����, ����_����, ����_����, ����_����, ����_����, ����_���};
			��������[����_���� ] = {����_��, ����_��, ����_���, ����_���, ����_����, ����_����};
			��������[����_��  ] = {����_���, ����_��, ����_����, ����_����, ����_����, ����_����, ����_����, ����_���};
			��������[����_���� ] = {����_�Ϻ�, ����_����, ����_���, ����_����};
			��������[����_�Ϻ� ] = {����_����, ����_����, ����_����, ����_����, ����_�Ǿ�, ����_��, ����_ȸ��};
			��������[����_���� ] = {����_�Ϻ�, ����_����, ����_����, ����_����, ����_��â, ����_����};
			��������[����_���� ] = {����_��â, ����_����, ����_�Ϻ�, ����_����, ����_����, ����_����, ����_����, ����_����, ����_�Ǿ�};
			��������[����_���� ] = {����_����, ����_����, ����_����, ����_��â, ����_����, ����_����, ����_��, ����_���};
			��������[����_���� ] = {����_��â, ����_����, ����_����, ����_��, ����_����, ����_����, ����_����, ����_���, ����_��};
			��������[����_��â ] = {����_����, ����_����, ����_��, ����_����, ����_�ž�, ����_����, ����_����, ����_����, ����_����};
			��������[����_���� ] = {����_��â, ����_�ž�, ����_����, ����_����, ����_����, ����_����, ����_����, ����_����};
			��������[����_���� ] = {����_���, ����_��, ����_����, ����_��â, ����_����, ����_��, ����_���};
			��������[����_��  ] = {����_����, ����_���, ����_��â, ����_����, ����_�ž�, ����_���, ����_���};
			��������[����_��� ] = {����_����, ����_����, ����_��, ����_����, ����_õ��, ����_����, ����_��, ����_���};
			��������[����_��� ] = {����_����, ����_��, ����_�ž�, ����_���};
			��������[����_���� ] = {����_����, ����_õ��, ����_���};
			��������[����_õ�� ] = {����_����, ����_����, ����_����, ����_�ڵ�, ����_���};
			��������[����_���� ] = {����_����, ����_õ��};
			��������[����_�Ǿ� ] = {����_�Ϻ�, ����_����, ����_����, ����_��, ����_ȸ��, ����_�û�};
			��������[����_��  ] = {����_ȸ��, ����_�Ǿ�, ����_�Ϻ�, ����_�û�};
			��������[����_ȸ�� ] = {����_��, ����_�Ǿ�, ����_�û�, ����_�Ϻ�};
			��������[����_���� ] = {����_����, ����_�Ǿ�, ����_����, ����_����, ����_�û�, ����_��â};
			��������[����_�û� ] = {����_����, ����_����, ����_�Ǿ�, ����_���, ����_����, ����_���, ����_�ž�, ����_����, ����_ȸ��, ����_��};
			��������[����_���� ] = {����_�ž�, ����_����, ����_����, ����_����, ����_�û�, ����_���, ����_����, ����_����, ����_���};
			��������[����_�ž� ] = {����_��, ����_���, ����_����, ����_��â, ����_���, ����_����, ����_����, ����_�û�, ����_���};
			��������[����_��� ] = {����_����, ����_�ž�, ����_���, ����_��, ����_����, ����_�û�, ����_����, ����_���};
			��������[����_���� ] = {����_���, ����_����, ����_����, ����_�ž�, ����_���, ����_�û�, ����_����};
			��������[����_��� ] = {����_���, ����_�û�, ����_����, ����_����, ����_����, ����_����, ����_���, ����_�ž�};
			��������[����_���� ] = {����_����, ����_����, ����_���, ����_���, ����_����, ����_����, ����_�û�};
			��������[����_��� ] = {����_���, ����_����, ����_����};
			��������[����_���� ] = {����_����, ����_���, ����_���};
			��������[����_���� ] = {����_����, ����_����, ����_����, ����_����, ����_���};
			��������[����_���� ] = {����_�ڵ�, ����_���, ����_õ��, ����_���, ����_����, ����_����, ����_����};
			��������[����_�ڵ� ] = {����_����, ����_����, ����_����, ����_õ��};
			��������[����_���� ] = {����_����, ����_�ڵ�, ����_�ǳ�, ����_����, ����_����, ����_�};
			��������[����_���� ] = {����_�ڵ�, ����_����, ����_�ǳ�, ����_�, ����_����};
			��������[����_�ǳ� ] = {����_����, ����_����, ����_�};
			��������[����_� ] = {����_�ǳ�, ����_����, ����_����};
			
		}
		
	}
	
	
	Util util;
	HanFix hanFix;
	NeighborMap neighborMap;
	Main main;
	
} // end - namespacee