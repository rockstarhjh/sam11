/*
@������: �ﵵī�� ȣ���屺����
@����: ���� �δ� ���� ����ȭ  (161012 ���� ����ڿ�)
	�����ϴ� AI �δ��� ����(����)�� Ư��/����/���±ⱳ�� �����Ͽ� ���� �����ϰ� ������
	(Ư�� > ���� >> ���±ⱳ)

  ����) �������/�������� �ⱳ�� �Ϸ��� ���¿��� ����/���� �δ븦 ����� ��
	������ ���� �δ밡 ������ ���� ���� ���� �þ�� ����(�ﱹ�� ������ �ִ� ������ ����)

�δ� ����
- �˺��δ�, �Ϲݺδ�(â��,�غ�,�뺴,�⺴), ����δ�(����,���,����,����)

�� ���� �⺻ ���� ��
 - ����δ�, �˺��δ� -> �Ϲݺδ� (O)
 - �˺��δ�, �Ϲݺδ� -> ����δ� (X)
 - ���� ���� Ư�� (��. ����) ���� �δ��� ���� ������ ���� �δ�� ����Ǵ� ��쵵 ����
  ������, ���� ������ ��� (������ ����) ��� ������ ����δ� �������� �ʱ� ������
  ����� ����� �������� �ʴ� ������ ������ �� ����.
   ��ǻ�� ���� �δ�� ��� Ȯ������ ����
*/
/*
// ������ : �ﵵī�� �⸶å��
// ��������('20.9.11) : 
//       ��ǻ�ͼ���_����������_��� �ɼ� �߰�, Ʈ���ſ켱���� �ݿ�,
//       ��ǻ�ͼ��� ��������/���� ���� �� �ݺ��� �ɼ� ���� �߰� (���� �˰��� �����ɼ� ��ɸ� ��ܿ� �߰�)
//       ��ǻ�ͼ���_��������_���� ��� �� �δ�˸��� �ƴ� ���ǿ����� �����ϴ� ���� ���� (��������, ������� ��)
//       �������� �� set_amount_weapon �Լ��� ��������� ���� ������ ���� �������� �̵�������ȸ �Ǿ� �̵��Ұ��������� �̵������� ���� ����
//       �������濡 ���� ���� ��ȯ���� ���� (���ֻ��� ���� �� �������� �̵���, �������� �̻� ���ߵǴ� ���� ����)
//        ������ ��ȯ���� ������ ���� �������� ������ �δ� ������� �ݿ��ϴ� ���� ��ȯ���� ������ ���߾� �̵��� ������� ����
//        ������ ��ȯ���� ������ ���� ���� ������ ���� ������� �� �����ȯ�ϴ� �Լ� ���ʿ� (Ʈ���� ����)
//       ��� Ʈ���ſ� �켱 ���� ������ �߰� (�ٸ� ��ġ���� ���� �� �켱���� ���� �ʿ�)
// ��������('20.10.18) : ����/�ױ� ��������� �������� �����̸� �������� ����
*/

namespace ����_�����δ뺴������ȭ
{
////////////////////////////////////////////////////////////////////////////
bool  ���ӽ��۽�_�ȳ��޽���_ǥ�� = false;
bool  ��������Ȯ��â_�ѹ���ǥ�� = true;     // (�⺻�� false) false�� ��� ���ӷε� �ø��� Ȯ��, true �� ��� ���� ���� �� ������ ��� ����
bool  ��������_��� = true;	                 // (�⺻�� true), false �� ���, ��� �δ��� ���� ���� ����� ������� ����. (������ ����)
////////////////////////////////////////////////////////////////////////////
///* ����� ���� ���� ����
bool  �÷��̾�_���ӱ���_��������_��� = true;	// (�⺻�� true), false �� ���, ���� ���ܿ����� ���� �δ� ���� ������ ���� ���� - ������ ���� ������ų ��쵵 �ڵ� �����!
bool  �÷��̾�_���ӱ���_����������_��� = false;	// (�⺻�� false), true �� ���, ���� ������� ������� ���� ����, false �� ���, ���Ⱑ ������ �������δ� ������� ����, ����) 
bool  ��ǻ�ͼ���_����������_��� = false;	    // (�⺻�� true),  true �� ���, ���� ������� ������� ���� ����, false �� ���, ���Ⱑ ������ �������δ� ������� ����, ����)
bool  ��ǻ�ͼ���_��������_����  = false; 	    // (�⺻�� true),  true �� ���, ���������� ���غ��� ������ ��� ���غ������� ��������, false �� ���, ���� �����ϴ��� �������� ����
float ��ǻ�ͼ���_���º���_����  = 0.4f;        // (�⺻�� 0.4f),  ��ǻ�ͼ���_��������_���� true �� ���, �������°� ������� ���غ��� �̻����� �δ����� ���, false �� ���, ���� �����ϴ��� �������� ����
bool  ��ǻ�ͼ���_������ȯ_�ݺ��� = false; 	    // (�⺻�� true),  true �� ���, ����δ� �� �Ϲݺδ� ���� �� �δ� �� +400, false �� ���, �ݺ��� ����
bool  ��ǻ�ͼ���_��������_����  = false; 	    // (�⺻�� true),  true �� ���, �δ� ���� ���� �� ����, false �� ���, ���� �����ϴ��� �������� ����
bool  ��ǻ�ͼ���_��������_����  = false;       // (�⺻�� true),  true �� ���, �������� �δ� �˸� �� �Ҽ� �������� ���� ��ȯ, false �� ���, ���� ��ȯ ����
bool  ����δ�_������� = true;	// (�⺻�� true), false �� ���, �����ϴ� ��� �δ�� �Ϲݺδ�θ� ����
bool  ����δ�_�����˸� = false;	// (�⺻�� false), ����δ� ���� �˸� ���� - �˸�â(Ȯ�� Ŭ�� �ʿ�)���� ǥ��
// �� [����δ�_�������] ������ false �� [����δ�_�������] ������ ������ true �� ��
bool  ����δ�_������� = true;	// (�⺻�� true), false �� ���, ����δ�� �״�� ������
bool  �Ϲݺδ�_������� = true;	// (�⺻�� true), �Ϲݺδ븦 �� ���� �Ϲݺδ�� ������ ������ ����
bool  �˺��δ�_������� = true;	// (�⺻�� true), �˺��δ븦 �Ϲݺδ�� ������ ������ ����
bool  ��������_ǥ�� = false;	// (�⺻�� false), �δ밡 �����ϴ� ���� ǥ�� ����
bool  ����Ư��_��������_��������_������� = false;	// (�⺻�� false), ���� Ư�� �δ� ����/��� -> ����/���� ���� ����
int   ����δ�_��������_���� = ����_B;	// (�⺻�� ����_B), ����_C / ����_B / ����_A / ����_S ���·� �Է�, ���� ���� �̸��� �������� ����
int   �Ϲݺδ�_��������_�������� = 1;	// (�⺻�� 1)
int   ����δ�_��������_�������� = 1;	// (�⺻�� 1)

bool  �����ױ�_��������δ�_������� = true;
//*/

class ChangeBetterWeapon
{
	string �����δ뺴������ȭ_���� = "v20161017";

    int �����δ�����ȭ_Ʈ����_�켱����_�δ뺯�� = 50;   // [������������ȭ], [������������ȭ] ��ġ���� ���� ������ ����
    int �����δ�����ȭ_Ʈ����_�켱����_�����ȯ = 255;  // [������������ȭ], [������������ȭ] ��ġ���� ���� ������ ����
	bool bDataInitialized = false;

	float ����ġ_���_���� = 0.2f;

	array<float> ����_�⺻_����ġ(����_��, 0.0f);
	array<float> ����_�⺻_����ġ(����_��, 0.0f);
	array<dictionary> ����_Ư��_����ġ(����_��);
	array<dictionary> ����_Ư��_����ġ(����_��);
	array<int> ������_����_�⺻����Ȯ��(����_��, 100);

	ForceSkillWeight forceSkillWeight;

	bool ��������_�޽���ǥ�� = true;
	int ��������_�޽���ǥ��_�� = 0;	// 0 : �޽��� �ڽ��� ǥ��, 1 : ��ǳ������ ǥ��, 2 : ǥ������ ����
	bool ��������_�޽���ǥ��_Ȯ�� = false;

	bool ��ǻ�ͼ���_����_���� = ��ǻ�ͼ���_��������_����;
    
    bool ��ǻ�ͼ���_����������_��������_��� = true; // (�⺻�� false), true �� ���, ��ǻ�ͼ��� ���� ��忡�� ��ǻ�ͺδ� ����ȭ ����, false �� ���, ��ǻ�ͼ��� ���� ��忡�� ��ǻ�ͺδ� ����ȭ ���� ����
    bool ����_��ε� = false;

	uint changeCount;

	uint countSiegeWeapon;

	uint changeCountFromSiegeToNormalWeapon;
	uint changeCountFromNormalToSiegeWeapon;

	uint cancelCount = 0;
	uint siegeWeaponCreationCount = 0;
	uint64 totalCountCreation = 0;

	RestoreWeaponInfo restoreWeaponInfo1;
	RestoreWeaponInfo restoreWeaponInfo2;

	ChangeBetterWeapon()
	{
		if (��������_���)
			initialize();
	}

	void initialize()
	{
		if (bDataInitialized)
			return;

		// ����ġ�� ���� 1�ܰ� = 1.0f �� ����

		//����_�⺻_����ġ[����_����] = 0.0f;

		����_�⺻_����ġ[����_��] = -20.0f;

		// ������ Ư�� ����ġ ����
		dictionary â��_Ư�� = { {Ư��_����+"", 5.0f}, {Ư��_�п�+"", 5.0f}, {Ư��_����+"", 4.0f}, {Ư��_����+"", 5.0f}, {Ư��_����+"", 5.0f}, {Ư��_â��+"", 5.0f}, {Ư��_â��+"", 5.0f} };//â��
		dictionary �غ�_Ư�� = { {Ư��_����+"", 5.0f}, {Ư��_�п�+"", 5.0f}, {Ư��_����+"", 4.0f}, {Ư��_����+"", 5.0f}, {Ư��_����+"", 5.0f}, {Ư��_�ؽ�+"", 5.0f}, {Ư��_����+"", 5.0f} };//�غ�
		dictionary �뺴_Ư�� = { {Ư��_����+"", 4.5f}, {Ư��_�п�+"", 4.5f}, {Ư��_����+"", 3.5f}, {Ư��_����+"", 4.5f}, {Ư��_�ý�+"", 7.0f}, {Ư��_����+"", 4.0f}, {Ư��_���+"", 2.0f} };//�뺴
		dictionary �⺴_Ư�� = { {Ư��_����+"", 5.0f}, {Ư��_�п�+"", 5.0f}, {Ư��_����+"", 4.0f}, {Ư��_����+"", 5.0f}, {Ư��_���+"", 10.0f}, {Ư��_����+"", 4.0f}, {Ư��_�鸶+"", 2.0f}, {Ư��_����+"", 7.0f} };//�⺴
		dictionary ����_Ư�� = { {Ư��_����+"", 3.0f}, {Ư��_����+"", 2.0f}, {Ư��_�߸�+"", 1.0f} };//����

		//�뺴_Ư��.set( Ư��_�ɰ�+"", -0.2f );
		�뺴_Ư��.set( Ư��_����+"", -0.5f );

		����_Ư��.set( Ư��_����+"", -2.0f );
		����_Ư��.set( Ư��_�ɰ�+"", -2.0f );
		����_Ư��.set( Ư��_����+"", -2.0f );
		����_Ư��.set( Ư��_����+"", -2.0f );
		����_Ư��.set( Ư��_����+"", -2.0f );
		����_Ư��.set( Ư��_��ǳ+"", -1.0f );
		����_Ư��.set( Ư��_�޽�+"", -1.0f );
		����_Ư��.set( Ư��_����+"", -0.5f );

		����_Ư��_����ġ[����_â��] = â��_Ư��;
		����_Ư��_����ġ[����_�غ�] = �غ�_Ư��;
		����_Ư��_����ġ[����_�뺴] = �뺴_Ư��;
		����_Ư��_����ġ[����_�⺴] = �⺴_Ư��;
		����_Ư��_����ġ[����_����] = ����_Ư��;

		// ������ Ư�� ����ġ ����
		//dictionary ����_Ư�� = { };
		//dictionary ���_Ư�� = { };

		// ���� Ư��� ������ �������� ������ �����Ƿ�, ����_���� �� �ƴ� ����_����, ����_���� ���� ������
		dictionary ����_Ư�� = { {Ư��_����+"", 1.0f} };	// ����
		dictionary ����_Ư�� = { {Ư��_����+"", 1.0f} };	// ����

		����_Ư��_����ġ[����_����] = ����_Ư��;
		����_Ư��_����ġ[����_����] = ����_Ư��;

		������_����_�⺻����Ȯ��[����_C] = 15;
		������_����_�⺻����Ȯ��[����_B] = 35;
		������_����_�⺻����Ȯ��[����_A] = 75;

		pk::bind(103, �����δ�����ȭ_Ʈ����_�켱����_�δ뺯��, pk::trigger103_t(CallBack_GameStart));
		pk::bind(170, �����δ�����ȭ_Ʈ����_�켱����_�δ뺯��, pk::trigger170_t(CallBack_UnitCreated));

        // �⸶å�� �߰� (���� ��ȯ ���� ������)
        pk::bind(172, �����δ�����ȭ_Ʈ����_�켱����_�����ȯ, pk::trigger172_t(RestoreUnitWeapon));
		// ------------ �⸶å�� ���� : �����ȯ ������ ���ֻ��� ���Ŀ��� �������� �ķ� �����ϸ鼭 ������� Ʈ���� ����� �ʿ� ��������
        //pk::bind(171, �����δ�����ȭ_Ʈ����_�켱����_�δ뺯��, pk::trigger171_t(CallBack_UnitCreationCanceled));
		
        if (��ǻ�ͼ���_����_����)
			pk::bind(171, �����δ�����ȭ_Ʈ����_�켱����_�δ뺯��, pk::trigger171_t(CallBack_UnitDefeated));

		if (!����δ�_�������)
			����δ�_������� = true;

		bDataInitialized = true;
        
	}

	void resetVals()
	{
		��������_�޽���ǥ��_Ȯ�� = false;
		��������_�޽���ǥ�� = !��������_�޽���ǥ��_Ȯ��;
		��������_�޽���ǥ��_�� = 1;

		changeCount = changeCountFromSiegeToNormalWeapon = changeCountFromNormalToSiegeWeapon = countSiegeWeapon = 0;

		cancelCount = 0;
		totalCountCreation = 0;
		siegeWeaponCreationCount = 0;

		forceSkillWeight.initialize();
	}

	void notify()
	{
		if (��������_���)
		{
			string question = "";

			question = "\x1b[1x���� �δ� ���� ����ȭ\x1b[0x�� \x1b[1x����\x1b[0x�ǰ� �ֽ��ϴ�.";
			if (�÷��̾�_���ӱ���_��������_���)
				question += pk::format("(���ӱ��� \x1b[1x�������\x1b[0x, �������� {}\x1b[0x)", (�÷��̾�_���ӱ���_����������_��� ? "\x1b[1x�������" : "\x1b[16x����Ұ�"));
			question += pk::format(" \x1b[28x{}", �����δ뺴������ȭ_����);

			pk::choose({ pk::encode(" Ȯ�� ") }, pk::encode(question), pk::get_person(����_����));
		}
	}

	void CallBack_GameStart()
	{
        if (!����_��ε�)
        {
            resetVals();
            ����_��ε� = true;
            if (!��������Ȯ��â_�ѹ���ǥ��) 
                ����_��ε� = false;
        }
        
        if(���ӽ��۽�_�ȳ��޽���_ǥ��)
            pk::scene(pk::scene_t(notify));
	}

	// �δ� ������ ��ҵǾ��� ��� (���ӱ��� �Ǵ� ��ǻ�� ���� �δ� ���� ��) ... �⸶å�� ���� : ��ǻ�� ���µ� ���Խ�Ŵ
	// NOTE �÷��̾ ���� ����->��Ҹ� �� ��쿡�� ȣ��
	void CallBack_UnitCreationCanceled(pk::unit@ unit, int type)
	{
		if (!pk::is_alive(unit)) return;
        if (type == 1) return;  // ���� ����

        if (!unit.is_player() or (�÷��̾�_���ӱ���_��������_��� and isPlayerDelegatedUnit(unit)))
        {
            pk::building@ base = pk::get_building(pk::get_service(unit));
            pk::building@ buliding_t = pk::get_building(unit.pos);
            if (pk::is_alive(base) && pk::is_alive(buliding_t) && pk::is_valid_building_id(base.get_id())
                && base.get_force_id() == unit.get_force_id() && buliding_t.get_id() == base.get_id())
            {
                string base_name = pk::decode(pk::get_name(base));
                string unit_name = pk::decode(pk::get_name(pk::get_person(unit.leader)));
                if (����׸��) pk::info(pk::format("{}�� �������: {} {}({}), {}({})", unit_name, base_name, ����_�̸�[restoreWeaponInfo1.weapon], pk::get_weapon_amount(base, restoreWeaponInfo1.weapon), ����_�̸�[restoreWeaponInfo2.weapon], pk::get_weapon_amount(base, restoreWeaponInfo2.weapon) ));
                
                if (unit.get_id() == restoreWeaponInfo1.getUnitId()) restoreWeaponInfo1.restoreTo(base);
                if (unit.get_id() == restoreWeaponInfo2.getUnitId()) restoreWeaponInfo2.restoreTo(base);
                
            }
		}
	}

	void CallBack_UnitDefeated(pk::unit@ unit, int type)
	{
		if (!pk::is_alive(unit) || !pk::is_normal_force(unit.get_force_id())) return;

		int weapon = pk::get_ground_weapon_id(unit);
		if (!unit.is_player() && isSiegeWeapon(weapon))
		{
			pk::building@ base = pk::get_building(pk::get_service(unit));
            
			if (pk::is_alive(base) && pk::is_valid_building_id(base.get_id()) && base.get_force_id() == unit.get_force_id())
			{
                // ---------- �⸶å�� �߰� : ���ŵ� ���� ��ġ�� ��������(������� ��Ȳ), ���� �������� ������ ��� ����
                pk::building@ buliding_t = pk::get_building(unit.pos);
                if (type == 1) return;  // ����
                if (pk::is_alive(buliding_t) and buliding_t.get_id() == base.get_id()) return; // �������
                // ------------------------------
                
                auto force = pk::get_force(unit.get_force_id());
				if (!pk::is_alive(force)) return;

				int amount = pk::get_max_troops(unit);
				pk::add_troops(base, amount, true);
				pk::add_food(base, amount*2, true);
				pk::add_weapon_amount(base, weapon, 1);
                
                if (����׸��)
                {
                    string unit_name = pk::decode(pk::get_name(pk::get_person(unit.leader)));
                    string base_name = pk::decode(pk::get_name(base));
                    pk::info(pk::format("�����δ�����ȭ: ��ǻ�ͼ���_��������: {}�� �ҼӰ��� {}(��)�� ����({}),����({}),{}(1) ��ȯ", unit_name, base_name, amount, amount*2, ����_�̸�[weapon]));
                }
			}
		}
	}

	void CallBack_UnitCreated(pk::unit@ unit, int type)
	{
		++totalCountCreation;

		if (!pk::is_alive(unit)) return;

		if (type != 0 || !IsAllowUnitWeaponChange(unit, �÷��̾�_���ӱ���_��������_���)) return;

		/* NOTE
		�δ� �̵����� 0���� ���� �δ븦 �������� ���ϵ��� �� �ξ��� ��쿡�� ���� ������ ���� ����
		�̵��� 2~4 �� ��� �������� 1ĭ�̹Ƿ�, 1ĭ�� �̵����� ���ϴ� ��� �δ� ������ �ڵ����� ��ҵǴµ�,
		�δ� ���� ���θ� �Ǵ��ϴ� ������ "�δ� ����"�̱� ����.
		*/
		int weapon_mov = unit.attr.stat[�δ�ɷ�_�̵�];
		if (weapon_mov < 2) return;

		auto force = pk::get_force(unit.get_force_id());
		if (!pk::is_alive(force) || !pk::is_normal_force(force.get_id()))
			return;

        // ---------- �⸶å�� �߰� : ��ǻ�� ������ �ش� ���� �ƴ� ��� ���� (��ǻ�ͼ��� ���� ��)
        if (!��ǻ�ͼ���_����������_��������_��� and !unit.is_player() and unit.get_force_id() != pk::get_current_turn_force_id()) 
            return;   
        // ------------------------------
		auto base = pk::get_building(pk::get_service(unit));
		if (!pk::is_alive(base) || !pk::is_valid_building_id(base.get_id()))
			return;

		int weapon = pk::get_ground_weapon_id(unit);
		int currTekisei = getTekiseiEx(unit, weapon);

		if (isSiegeWeapon(weapon))
			++siegeWeaponCreationCount;

		int skill;
		string strSkillNames = "";
		array<string> skillNames(0);
		for (int i=0; i<3; i++)
		{
			auto person = pk::get_person(unit.member[i]);
			if (!pk::is_alive(person)) continue;
			skill = person.skill;
			if (skill >= 0 && skill < Ư��_��) skillNames.insertLast(pk::format("\x1b[17x{}\x1b[0x", pk::decode(pk::get_skill(skill).name)));
		}

		if (skillNames.length() == 0)
			strSkillNames = "\x1b[17x����\x1b[0x";
		else
			strSkillNames = join(skillNames, ",");

		bool bTargetToChange = isTargetToChange(weapon);
		bool bWeaponChanged = false;
		if (bTargetToChange)
			bWeaponChanged = changeWeapon(unit, ����δ�_�������);

		if (pk::get_scenario().difficulty == ���̵�_Ư�� && !unit.is_player())
		{
			if ((int(unit.troops) < int(pk::get_max_troops(unit) * ��ǻ�ͼ���_���º���_����)) && ��ǻ�ͼ���_��������_����)
                unit.troops = int(pk::get_max_troops(unit) * ��ǻ�ͼ���_���º���_����);
		}

		string strFrom = ��������_ǥ�� ? pk::format("\x1b[2x{}\x1b[0x���� ", pk::decode(pk::get_name(base))) : "";
		int newWeapon = pk::get_ground_weapon_id(unit);
		string strUnitInfo = strFrom + pk::format("\x1b[2x{}�� {}\x1b[0x({})", pk::decode(pk::get_name(force)), pk::decode(pk::get_name(unit)), strSkillNames);
		if (bWeaponChanged)
		{
			++changeCount;

			int newTekisei = getTekiseiEx(unit, newWeapon);

			// ���� �δ� -> �Ϲ� �δ��� ���
			if (��ǻ�ͼ���_������ȯ_�ݺ��� && isSiegeWeapon(weapon) && !isSiegeWeapon(newWeapon))
			{
				++changeCountFromSiegeToNormalWeapon;
				pk::add_gold(unit, 400);
			}
			else
			{
				if (isSiegeWeapon(newWeapon)) ++changeCountFromNormalToSiegeWeapon;
			}

			if (!��������_�޽���ǥ��_Ȯ��)
			{
				��������_�޽���ǥ��_Ȯ�� = true;

				string question = pk::encode("�����ϴ� �δ��� ����(����) ���� ������ ǥ���Ͻðڽ��ϱ�?");
				array<string> answer = { pk::encode("�˸�â���� ǥ��"), pk::encode("��ǳ������ ǥ��"), pk::encode(" ǥ������ ����  ") };
				��������_�޽���ǥ��_�� = pk::choose(answer, question, pk::get_person(����_����));

				switch (��������_�޽���ǥ��_��)
				{
				case 0: ��������_�޽���ǥ�� = true; break;
				case 1: ��������_�޽���ǥ�� = true; break;
				case 2: ��������_�޽���ǥ�� = false; break;
				}
			}

			string clr = isSiegeWeapon(weapon) ? "\x1b[24x" : "\x1b[0x";
			string clr2 = isSiegeWeapon(newWeapon) || (newTekisei < currTekisei) ? "\x1b[16x" : (weapon == ����_�� || newTekisei > currTekisei) ? "\x1b[1x" : "\x1b[0x";
			string strWeaponInfo = pk::format("{}\x1b[0x �� {} \x1b[0x����!", clr + ��������(weapon, currTekisei), clr2 + ��������(newWeapon, newTekisei));

            // ----- �⸶å�� �߰� : ������ ������ ������ �޼��� �ȶߵ���
            pk::person@ leader = pk::get_person(unit.leader);
            pk::building@ service = pk::get_building(leader.service);
            bool is_in_base = (pk::is_alive(service) and leader.location == pk::get_hex_object_id(service));
            
			if (��������_�޽���ǥ��_�� == 0) pk::message_box(pk::encode(strUnitInfo + " " + strWeaponInfo), leader);
			else if (��������_�޽���ǥ��_�� == 1 and !is_in_base) pk::balloon(pk::encode(strUnitInfo + " \n" + strWeaponInfo), leader);
		}

		// ���� ������. ���� 30% ����
		if (��ǻ�ͼ���_��������_���� && !unit.is_player() && unit.food < int(unit.troops * 1.3f))
            pk::set_food(unit, int(unit.troops * 1.3f + 0.5f));

		if (isSiegeWeapon(newWeapon))
		{
			++countSiegeWeapon;
			currTekisei = getTekiseiEx(unit, newWeapon);
			if (����δ�_�����˸�) pk::message_box(pk::encode(pk::format(strUnitInfo + "�� \x1b[24x{} \x1b[0x(��)�� �����߽��ϴ�!", ��������(newWeapon, currTekisei))));
		}
	}

	// ����(����) ���� �Լ�
	// bForcedChangeSiegeWeapon : ����� ������ �ٸ� �������� ������ ������
	bool changeWeapon(pk::unit@ unit, bool bForcedChangeSiegeWeapon=false)
	{
        
		if (unit.type != �δ�����_����) return false;

		int weapon = pk::get_ground_weapon_id(unit);

		auto force = pk::get_force(unit.get_force_id());
		if (!(pk::is_alive(force) && pk::is_normal_force(force.get_id()))) return false;

		forceSkillWeight.setForce(unit.get_force_id());

		bool bPlayerDelegatedUnit = isPlayerDelegatedUnit(unit);

		// ����
        //bool isCheckStock = bPlayerDelegatedUnit && !�÷��̾�_���ӱ���_����������_���;
        // ------------ �⸶å�� ���� : ��ǻ�ͼ���_����������_��� ���� ���� ��� �߰�
        bool isCheckStock = (!unit.is_player())? (!��ǻ�ͼ���_����������_���) : (bPlayerDelegatedUnit && !�÷��̾�_���ӱ���_����������_���) ;
        
		int currTekisei = getTekiseiEx(unit, weapon);

		int newWeapon  = getSuitableWeapon(unit, bForcedChangeSiegeWeapon, false, isCheckStock);
		int newTekisei = getTekiseiEx(unit, newWeapon);

		if (weapon == newWeapon) return false;
        
        // ------------ �⸶å�� �߰� : ����/�ױ� ��������� �������� �����̸� �������� ����
        if (�����ױ�_��������δ�_������� and isGateDefenceUnit(unit)) return false;
        
        // ------------ �⸶å�� ���� : ���Ⱑ '��'�� ��� ����ⷮ ������� �߰�
		int weaponCount    = isSiegeWeapon(weapon)    ? 1 : ((weapon    == ����_��)? 0 : unit.troops);
		int newWeaponCount = isSiegeWeapon(newWeapon) ? 1 : ((newWeapon == ����_��)? 0 : unit.troops);
        
        // ------------ �⸶å�� �߰� : ������� ��Ȯ��
        auto base = pk::get_building(pk::get_service(unit));
        if (isCheckStock and !isEnoughStocksOfWeapon(base, newWeapon, newWeaponCount)) return false;
        
        string base_name = pk::decode(pk::get_name(base));
        string unit_name = pk::decode(pk::get_name(pk::get_person(unit.leader)));
        string stock_opt = (isCheckStock)? "�������" : "�����";
        if (����׸��)
            pk::info(pk::format("�����δ�����ȭ: {} ����({}), ���:{}({}),{}({}), �ɼ�:{}", base_name, pk::get_troops(base), ����_�̸�[weapon], pk::get_weapon_amount(base, weapon), ����_�̸�[newWeapon],  pk::get_weapon_amount(base, newWeapon), stock_opt));
        // ------------------------------------
        
        
        // ------------ �⸶å�� ���� : �ּ�ó��
		// ����/��� �� ����/������ ���
		//if (isSiegeWeapon(weapon) && isSiegeWeapon(newWeapon))
		//	weaponCount = newWeaponCount = 0;

		// �Ʒ� �ڵ带 ����Ͽ� ���Ⱚ�� �ٲ� �Ŀ��� getWeapon() �� �ٲٱ� ���� �����θ� ���ϵǹǷ�, '�δ�Ӽ�_�ֹ���' ���� �̿��ؾ� ��.
		// NOTE ���� �����ϴ� ��� �ڵ忡�� getWeapon() ��� queryValue(�δ�Ӽ�_�ֹ���) ���
		pk::set_weapon_amount(unit, 0, pk::get_ground_weapon_id(unit), 0);
		pk::set_weapon_amount(unit, 0, newWeapon, newWeaponCount);
        
        // ------ �⸶å�� �߰� : �δ� �������� �� �ɷ�ġ ������Ʈ (�ſ� �߿�!!!!)
        // ���� �� ���� �� ���� �������� �̵����� Ȯ���� ��ȸ�Ǵ� ���� �߻� -> �̵��Ұ��������� �̵����� -> �������� ���� ����
        unit.update(); 
        
		restoreWeaponInfo1.clear();
		restoreWeaponInfo2.clear();
		
		if (pk::is_alive(base) && pk::is_valid_building_id(base.get_id()) && base.get_force_id() == force.get_id())
		{
            // ------------ �⸶å�� ���� : RestoreUnitWeapon �Լ� �߰��ϸ鼭 �ּ�ó���� (���� �̵� �� ���� ��ȯ �����ϵ��� ����)
			/* NOTE
			// ��ǻ���� ���� ������ �δ��� ���� ���ÿ� ������ �� �� �ֱ� ������ ������ ���⸦ ���� ������ �߰��ϰų� �������� �������� ����. .
			// ����. ���� ������ ��쿡�� �߰� - ���� ����� ���� ��� ����.
			
			if (!unit.is_player() && isSiegeWeapon(weapon)) pk::add_weapon_amount(base, weapon, weaponCount);

			if (�÷��̾�_���ӱ���_��������_��� && bPlayerDelegatedUnit && !�÷��̾�_���ӱ���_����������_���)
			{
				if (weapon != ����_��) pk::add_weapon_amount(base, weapon, weaponCount);
				pk::add_weapon_amount(base, newWeapon, -newWeaponCount);

				restoreWeaponInfo1.setData(unit.get_id(), weapon, -weaponCount);
				restoreWeaponInfo2.setData(unit.get_id(), newWeapon, newWeaponCount);
			}
            */
            
            // ------------ �⸶å�� ���� : �����̵� Ʈ���ſ� RestoreUnitWeapon �Լ� �߰� ����
            unit_id = unit.get_id();
            clear_weapon_info(unit_id);
            isOptimized[unit_id] = true;
            wpn_amount[unit_id] = unit.troops;
            wpn_id_add[unit_id] = weapon;
            wpn_id_sub[unit_id] = newWeapon;
            
            if (����׸��)
                pk::info(pk::format("--- {} {}��({}) ��������: {}��{}", base_name, unit_name, unit.troops, ����_�̸�[weapon], ����_�̸�[newWeapon]));
		}
        
		return true;
	}
    
    
    ////---- �⸶å�� ���� : ������������ȭ.cpp �� ���� Ÿ�̹�, Ʈ���� �켱���� ���� �ʿ�
    int unit_id;
    array<bool> isOptimized(�δ�_��, false);
    array<int> wpn_amount(�δ�_��, 0);
    array<int> wpn_id_add(�δ�_��, -1);
    array<int> wpn_id_sub(�δ�_��, -1);
    
    void RestoreUnitWeapon(pk::unit@ unit, const pk::point &in pos)
    {
        if (!pk::is_alive(unit))	       return;
        if (unit.type == �δ�����_����)		   return;	// ���� �δ� ����
        if (pk::get_hex(pos).has_building) return;	// ������ �������� ���� ���(���� ���) ����

        pk::building@ building = pk::get_building(pk::get_service(unit));
        if (!pk::is_alive(building))	   return;
        if (building.pos != unit.pos)	   return;	// �δ��� �̵� �� ��ġ�� �Ҽ� ������ �ƴ� ��� ����
        string base_name = pk::decode(pk::get_name(building));

        int uid = unit.get_id();
        if (isOptimized[uid])
        {
            // ���� �̵� �� ���º��� ���� �� �־� �̵� �Ϸ���� ���¿� ���� ���� ���ⷮ ���, ��ȯ����� �̵��� ���� �������� ���
            int wpn_amount_add = isSiegeWeapon(wpn_id_add[uid]) ? 1 : ((wpn_id_add[uid] == ����_��)? 0 : wpn_amount[uid]);
            int wpn_amount_sub = isSiegeWeapon(wpn_id_sub[uid]) ? 1 : ((wpn_id_sub[uid] == ����_��)? 0 : wpn_amount[uid]);
            int wpn_before_add = pk::get_weapon_amount(building, wpn_id_add[uid]);
            int wpn_before_sub = pk::get_weapon_amount(building, wpn_id_sub[uid]);
            wpn_amount_sub = pk::min(wpn_amount_sub, pk::get_weapon_amount(building, wpn_id_sub[uid]));
            
            pk::add_weapon_amount(building, wpn_id_add[uid],  wpn_amount_add, false);    // ������ ���� �� ���� ��ȯ
            pk::add_weapon_amount(building, wpn_id_sub[uid], -wpn_amount_sub, false);    // ������ ���� �� ���� ����
            
            int wpn_after_add = pk::get_weapon_amount(building, wpn_id_add[uid]);
            int wpn_after_sub = pk::get_weapon_amount(building, wpn_id_sub[uid]);
            if (����׸��)
            {
                pk::info(pk::format("--- {} ���� �� ����({})", base_name, pk::get_troops(building)));
                pk::info(pk::format("--- {} �����ȯ {}({}��{})", base_name, ����_�̸�[wpn_id_add[uid]], wpn_before_add, wpn_after_add));
                pk::info(pk::format("--- {} �������� {}({}��{})", base_name, ����_�̸�[wpn_id_sub[uid]], wpn_before_sub, wpn_after_sub));
            }
            
            // �δ� ���� ���� �ʱ�ȭ
            clear_weapon_info(uid);
        }
    }
    
    // �δ� ���� ���� �ʱ�ȭ
    void clear_weapon_info(int uid)
    {
        wpn_amount[uid] = 0;
        wpn_id_add[uid] = -1;
        wpn_id_sub[uid] = -1;
        isOptimized[uid] = false;
    }
    
    // ����/�ױ� ���δ����� Ȯ��
    bool isGateDefenceUnit(pk::unit@ unit)
    {
        if (!pk::is_alive(unit)) return false;
        
        int base_id = pk::get_service(unit);
        pk::building@ base = pk::get_building(base_id);
        if (!pk::is_alive(base)) return false;
        if (!pk::enemies_around(base)) return false;    // �����ƴ�
        
        int weapon_id = unit.weapon;
        if (�ǹ�_�������� <= base_id and base_id < �ǹ�_�ױ���)
        {
            if (weapon_id == ����_�� or weapon_id == ����_���� or weapon_id == ����_����) return true;
            if (weapon_id == ����_���� and unit.has_tech(�ⱳ_���)) return true;
        }
        return false;
    }
    
    
    bool ����׸�� = false;
    ////----
    
    
    
	// ���⿡ ���� ��� ����ġ (Ư��, �ⱳ) ����
	float getWeaponWeight(pk::unit@ unit, int weapon, int tekisei=0)
	{
		if (!pk::is_valid_equipment_id(weapon)) return 0.0f;
		//int weapon_type = pk::equipment_id_to_heishu(weapon);
		return getWeaponWeightExceptForceSkill(unit, weapon, tekisei) + forceSkillWeight.getWeight(unit.get_force_id(), weapon);
	}

	// ���� �ⱳ ������ ���⿡ ���� ����ġ ���
	float getWeaponWeightExceptForceSkill(pk::unit@ unit, int weapon, int tekisei=0)
	{
		if (!pk::is_valid_equipment_id(weapon)) return 0.0f;
		int weapon_type = pk::equipment_id_to_heishu(weapon);
		return ����_�⺻_����ġ[weapon] + getWeaponTypeWeight(unit, weapon_type, tekisei) + getWeaponSkillWeight(unit, weapon, tekisei);
	}

	// ������ ���� ����ġ ����
	// weapon_type : ����, heishu
	float getWeaponTypeWeight(pk::unit@ unit, int weapon_type, int tekisei=0)
	{
		if (weapon_type < 0 || weapon_type >= ����_��) return 0.0f;

		float weight = ����_�⺻_����ġ[weapon_type];
		array<string> Ư��_Ű_�迭 = ����_Ư��_����ġ[weapon_type].getKeys();
		int len = Ư��_Ű_�迭.length();
		for (int i=0; i<len; i++)
		{
			int skill = parseInt(Ư��_Ű_�迭[i]);
			if (unit.has_skill(skill))
				weight += float(����_Ư��_����ġ[weapon_type][Ư��_Ű_�迭[i]]);
		}
		return weight;
	}

	// ������ Ư�� ����ġ ����
	float getWeaponSkillWeight(pk::unit@ unit, int weapon, int tekisei=0)
	{
		if (weapon < ����_�� || weapon >= ����_��) return 0.0f;

		float weight = 0.0f;
		array<string> Ư��_Ű_�迭 = ����_Ư��_����ġ[weapon].getKeys();
		int len = Ư��_Ű_�迭.length();
		for (int i=0; i<len; i++)
		{
			int skill = parseInt(Ư��_Ű_�迭[i]);
			if (unit.has_skill(skill))
				weight += float(����_Ư��_����ġ[weapon][Ư��_Ű_�迭[i]]);
		}
		return weight;
	}

	// �δ� �Ҽ� ���� �� ���� ȿ���� ���� ���⸦ ����.
	// useSiegeWeapon �� includeSiegeWeapon �� �켱
	// @useSiegeWeapon : �������� ��� ����
	// @includeSiegeWeapon : �������⸦ �˻��� ������ ����
	// @checkStock : ���� ��� Ȯ�� ����
	int getSuitableWeapon(pk::unit@ unit, bool useSiegeWeapon=true, bool includeSiegeWeapon=false, bool checkStock=false)
	{
		// ����
        /*if (!useSiegeWeapon) */includeSiegeWeapon = false;

		int weapon = pk::get_ground_weapon_id(unit);

		if (����Ư��_��������_��������_������� && (weapon == ����_���� || weapon == ����_���) && unit.has_skill(Ư��_����))
			weapon = forceSkillWeight.getWeapon(����_����);

		int tekisei = getTekiseiEx(unit, weapon);

		float weight = tekisei + getWeaponWeight(unit, weapon) + ����ġ_���_����;

		if (isSiegeWeapon(weapon))
		{
			// ��� ������ C �� ������ �뺴 ����
			if (tekisei == ����_C && getTopTekisei(unit, true) == ����_C)
				return ����_��;

			if (tekisei >= ����δ�_��������_����)
				weight += ����δ�_��������_��������;

			// ���� ������ ������� ���� ��� '���������� �˺����� ���'
			if (!useSiegeWeapon)
			{
				//weapon = ����_��;
				//weight = ����_�⺻_����ġ[weapon];
                weight = ����_�⺻_����ġ[����_��];
			}
		}
		else
			weight += �Ϲݺδ�_��������_��������;

		array<int> weapons = getBetterWeapons(unit, weapon, weight, includeSiegeWeapon);

		if (weapons.length() == 0)
		{
			if (isSiegeWeapon(weapon))
			{
				if (tekisei > ����_A) tekisei = ����_A;
				int prob = pk::min(100, ������_����_�⺻����Ȯ��[tekisei] + int(unit.attr.stat[�δ�ɷ�_����]/5 + unit.attr.stat[�δ�ɷ�_���]/4));

				//if (tekisei >= ����δ�_��������_���� && pk::rand_bool(prob))
				//  return weapon;
                
                //----- �⸶å�� ���� : �������� ��밡�� ���� �ÿ���
                if (!useSiegeWeapon) weapon = ����_��;
				if (tekisei >= ����δ�_��������_���� and pk::rand_bool(prob) and useSiegeWeapon) return weapon;

				weapons = getBetterWeapons(unit, weapon, tekisei + ����ġ_���_����, includeSiegeWeapon);
			}
			else
				return weapon;
		}

		int requiredStocks = checkStock ? unit.troops : 0;
		int candidateWeapon;
		float errorVal = ����ġ_���_����;

		auto base = pk::get_building(pk::get_service(unit));

		for (int i=weapons.length()-1; i>=0; i--)
		{
			if (!isEnoughStocksOfWeapon(base, weapons[i], requiredStocks)
				|| canIgnoreDeviation(unit, weapon, weapons[i], errorVal))
				weapons.removeAt(i);
		}

		int iCandidateCount = weapons.length();
		if (iCandidateCount == 0)
			return weapon;

		candidateWeapon = weapons[pk::rand(iCandidateCount, unit.attr.stat[�δ�ɷ�_����], unit.attr.stat[�δ�ɷ�_���], datetime().get_second(), 0, 0, 0, 0)];

        //----- �⸶å�� �߰� : �������� ���Ұ� ���� �� �˺����� �������� ó��
        if (isSiegeWeapon(candidateWeapon) and !useSiegeWeapon) return ����_��;
        
		return candidateWeapon;
	}

	// ����ġ ���� ��������
	bool canIgnoreDeviation(pk::unit@ unit, int weapon, int weapon2, float errVal=0.3f)
	{
		// ���� ����� ū ���̰� ���� ��� AI �� ���� ���� ����
		float currWpW = getTekiseiEx(unit, weapon) + getWeaponWeight(unit, weapon);
		float candiWpW = getTekiseiEx(unit, weapon2) + getWeaponWeight(unit, weapon2);

		float diffVal = candiWpW - currWpW;
		return diffVal >= 0 && diffVal <= errVal;
	}

	bool isSiegeWeapon(int weapon) { return (weapon >= ����_���� && weapon <= ����_���); }

	int getTekiseiEx(pk::unit@ unit, int weapon)
	{
		return !pk::is_valid_equipment_id(weapon) ? 0 : pk::get_tekisei(unit, weapon);
	}

	bool IsDelegate(int district_no) { return pk::get_district(district_no).get_id() != 1; }

	// ������ �ٲ� �������
	// allowPlayerDelegatedUnit : ���ӱ��� ���� ���� ��� ����
	bool IsAllowUnitWeaponChange(pk::unit@ unit, bool allowPlayerDelegatedUnit=false)
	{
		// �̹���, ���� ����
		if (!pk::is_normal_force(unit.get_force_id())) return false;

		// ���� �δ� ����
		if (unit.type != �δ�����_����) return false;

		if (!unit.is_player()) return true;

		if (allowPlayerDelegatedUnit && isPlayerDelegatedUnit(unit)) return true;

		return false;
	}

	// �÷��̾� ���� ���� �δ� ����
	bool isPlayerDelegatedUnit(pk::unit@ unit)
	{
		return unit.is_player() && !pk::is_player_controlled(unit);
	}

	// ������ ����(����) ��� ������� ����
	bool isEnoughStocksOfWeapon(pk::building@ building, int weapon, int count)
	{
		if (weapon == ����_��) return true;

		if (pk::is_alive(building) && pk::is_valid_building_id(building.get_id()))
		{
			if (pk::get_weapon_amount(building, weapon) >= count) return true;
		}
		return false;
	}

	bool isDefenceUnit(pk::unit@ unit, int startWeapon=����_â)
	{
		if (startWeapon == ����_��) return true;
		else if (isSiegeWeapon(startWeapon)) return false;

		if (int(unit.troops) == pk::get_max_troops(unit))
			if (unit.food > int(unit.troops * 2))
				return false;
		else
		{
			if (unit.gold >= 1000) return true;
		}

		if (startWeapon == ����_���� && unit.gold >= 1500) return true;

		return int(unit.troops) < int(unit.food * 2);
	}

	bool isTargetToChange(int weapon)
	{
		bool bVal = true;
		switch (weapon)
		{
		case ����_��:

			bVal = �˺��δ�_�������;

			break;

		case ����_����:
		case ����_���:
		case ����_����:
		case ����_����:

			bVal = ����δ�_�������;

			break;

		default:	// â��, �غ�, �뺴, �⺴

			bVal = �Ϲݺδ�_�������;

			break;
		}
		return bVal;
	}

	int getTopTekisei(pk::unit@ unit, bool bIncludeSiegeWeapon=false)
	{
		int start = ����_â;
		int end = bIncludeSiegeWeapon ? ����_���� : ����_����;
		int best = 0;

		for (int i=start; i<=end; i++)
		{
			best = pk::max(getTekiseiEx(unit, i), best);
		}
		return best;
	}

	bool hasBetterWeapon(pk::unit@ unit, int weapon, float weight, bool bIncludeSiegeWeapon=false, bool bIgnoreForceSkill=false)
	{
		int start = ����_â;
		int end = bIncludeSiegeWeapon ? ����_���� : ����_����;

		int candidateWeapon;
		for (int i=start; i<=end; i++)
		{
			candidateWeapon = forceSkillWeight.getWeapon(i);
			if (weapon == i)
				continue;

			float compVal = getTekiseiEx(unit, i) + getWeaponWeight(unit, i);
			if (compVal > weight)
				return true;
		}
		return false;
	}

	array<int> getBetterWeapons(pk::unit@ unit, int weapon, float weight, bool bIncludeSiegeWeapon=false)
	{
		int start = ����_â;
		int end = bIncludeSiegeWeapon ? ����_���� : ����_����;

		array<int> candidates(0);

		int candidateWeapon;
		for (int i=start; i<=end; i++)
		{
			candidateWeapon = forceSkillWeight.getWeapon(i);
			if (weapon == candidateWeapon) continue;

			float skillWeight = getWeaponWeight(unit, candidateWeapon);
			int candidateTekisei = getTekiseiEx(unit, candidateWeapon);
			float compVal = candidateTekisei + skillWeight;

			if (compVal > weight)
			{
				int count = candidates.length();
				if (count == 0)
				{
					candidates.insertLast(candidateWeapon);
					continue;
				}

				for (int j=0; j<count; j++)
				{
					float valueCandidate = getTekiseiEx(unit, candidates[j]) + getWeaponWeight(unit, candidates[j]);
					if (compVal > valueCandidate)
					{
						candidates.resize(0);
						candidates.insertAt(j, candidateWeapon);
						break;
					}
					else if (compVal == valueCandidate)
					{
						candidates.insertAt(j+1, candidateWeapon);
						break;
					}
				}
			}
		}

		return candidates;
	}

	// note �迭�� ���� �������� ���� �Լ��� �������!
	array<string> ����_�̸� = {"��", "â", "��", "��", "����", "����", "����", "����", "���", "�ְ�", "����", "����" };

	string �����̸�(int equipment)
	{
		if (equipment < 0 || equipment >= ����_��) return "�� > " + equipment;
		return ����_�̸�[equipment];
	}

	array<string> ����_�̸� = {"â��", "�غ�", "�뺴", "�⺴", "����", "����"};

	string �����̸�By����(int equipment)
	{
		if (equipment == ����_��) return "�˺�";
		return �����̸�(pk::equipment_id_to_heishu(equipment));
	}

	string �����̸�(int heishu)
	{
		if (heishu < 0 || heishu >= ����_��) return "��";
		return ����_�̸�[heishu];
	}

	string �����̸�(int equipment)
	{
		switch(equipment)
		{
		case ����_����: return "�⺴";
		case ����_��:
		case ����_â:
		case ����_��:
		case ����_��:
			return ����_�̸�[equipment] + "��";
		}
		return ����_�̸�[equipment];
	}

	string ��������(int weapon, int tekisei)
	{
		return ��������(weapon, tekisei) + " (" + �����̸�By����(weapon) + ")";
	}

	string ��������(int weapon, int tekisei)
	{
		return �����̸�(weapon) + (weapon == ����_�� ? "" : �����̸�(tekisei));
	}

	string �����̸�(int tekisei)
	{
        string str_tekisei = "";
        switch(tekisei)
        {
            case ����_C: str_tekisei = "C"; break;
            case ����_B: str_tekisei = "B"; break;
            case ����_A: str_tekisei = "A"; break;
            case ����_S: str_tekisei = "S"; break;
        }
        return str_tekisei;
        
		//int limit = int(pk::core["�ִ�����"]);
		//if (tekisei < 0 || tekisei >= limit) return "";
		//return string(pk::core["����"][tekisei]["�̸�"]);
	}
    
    

};

class RestoreWeaponInfo
{
	private int unitNo;
	int weapon;
	int count;

	RestoreWeaponInfo()
	{
		clear();
	}

	int getUnitId()
	{
		return unitNo;
	}

	void setData(int unit_no, int weapon, int count)
	{
		unitNo = unit_no;
		this.weapon = weapon;
		this.count = count;
	}

	void restoreTo(int base_no)
	{
		restoreTo(pk::get_building(base_no));
	}

	void clear()
	{
		setData(-1, ����_��, 0);
	}

	void restoreTo(pk::building@ base)
	{
		if (unitNo < 0 || count == 0) return;

		if (pk::is_valid_building_id(base.get_id()))
		{
			if (weapon != ����_��) pk::add_weapon_amount(base, weapon, count);
		}

		clear();
	}
};

// ������ �ⱳ�� ���� ���� ����ġ ������ Ŭ����
class ForceSkillWeight
{
	int forceNo;

	array<int> ����_�迭(����_��);
	array<float> ����_����ġ_�迭(����_��, 0.0f);

	ForceSkillWeight()
	{
	}

	void initialize()
	{
		forceNo = -1;

		for (int i=����_â; i<=����_���; i++) ����_����ġ_�迭[i] = 0.0f;

		for (int i = 0; i < ����_��; i++) { ����_�迭[i] = i; }

		setForce(forceNo);
	}

	void setForce(int forceNo)
	{
		if (this.forceNo == forceNo) return;

		auto force = pk::get_force(forceNo);
		if (pk::is_alive(force) && pk::is_valid_force_id(forceNo))
		{
			for (int i=����_â; i<=����_���; i++) ����_����ġ_�迭[i] = 0.0f;

			����_����ġ_�迭[����_â] += (pk::has_tech(force, �ⱳ_â���ܷ�) ? 0.1f : 0.0f);
			����_����ġ_�迭[����_â] += (pk::has_tech(force, �ⱳ_��������) ? 0.1f : 0.0f);
			����_����ġ_�迭[����_â] += (pk::has_tech(force, �ⱳ_���) ? 0.1f : 0.0f);
			����_����ġ_�迭[����_â] += (pk::has_tech(force, �ⱳ_����â��) ? 0.7f : 0.0f);

			����_����ġ_�迭[����_��] += (pk::has_tech(force, �ⱳ_�غ��ܷ�) ? 0.1f : 0.0f);
			����_����ġ_�迭[����_��] += (pk::has_tech(force, �ⱳ_ȭ�����) ? 0.1f : 0.0f);
			����_����ġ_�迭[����_��] += (pk::has_tech(force, �ⱳ_ū����) ? 0.1f : 0.0f);
			����_����ġ_�迭[����_��] += (pk::has_tech(force, �ⱳ_�����غ�) ? 0.7f : 0.0f);

			����_����ġ_�迭[����_��] += (pk::has_tech(force, �ⱳ_�뺴�ܷ�) ? 0.1f : 0.0f);
			����_����ġ_�迭[����_��] += (pk::has_tech(force, �ⱳ_����) ? 0.1f : 0.0f);
			����_����ġ_�迭[����_��] += (pk::has_tech(force, �ⱳ_����) ? 0.1f : 0.0f);
			����_����ġ_�迭[����_��] += (pk::has_tech(force, �ⱳ_�����뺴) ? 0.7f : 0.0f);

			����_����ġ_�迭[����_����] += (pk::has_tech(force, �ⱳ_�⺴�ܷ�) ? 0.1f : 0.0f);
			����_����ġ_�迭[����_����] += (pk::has_tech(force, �ⱳ_�縶����) ? 0.1f : 0.0f);
			����_����ġ_�迭[����_����] += (pk::has_tech(force, �ⱳ_���) ? 0.1f : 0.0f);
			����_����ġ_�迭[����_����] += (pk::has_tech(force, �ⱳ_�����⺴) ? 0.7f : 0.0f);

			float techWeight = (pk::has_tech(force, �ⱳ_���భȭ) ? 0.2f : 0.0f);

			����_����ġ_�迭[����_����] += techWeight;
			����_����ġ_�迭[����_����] += techWeight;
			����_����ġ_�迭[����_����] += techWeight + (pk::has_tech(force, �ⱳ_��������) ? 0.2f : 0.0f) + (pk::has_tech(force, �ⱳ_����) ? 0.1f : 0.0f);
			����_����ġ_�迭[����_���] += techWeight + (pk::has_tech(force, �ⱳ_�������) ? 0.1f : 0.0f);

			����_�迭[����_����] = pk::has_tech(force, �ⱳ_�������) ? ����_��� : ����_����;
			����_�迭[����_����] = pk::has_tech(force, �ⱳ_��������) ? ����_���� : ����_����;
		}

		this.forceNo = forceNo;
	}

	float getWeight(int weapon)
	{
		return ����_����ġ_�迭[weapon];
	}

	float getWeight(int forceNo, int weapon)
	{
		setForce(forceNo);
		return getWeight(weapon);
	}

	int getWeapon(int weapon)
	{
		return ����_�迭[weapon];
	}
    
};

ChangeBetterWeapon zgChangeBetterWeapon;

}	// end of namesapce

/*
namespace cwt
{
	// note �迭�� ���� �������� ���� �Լ��� �������!
	array<string> ����_�̸� = {"��", "â", "��", "��", "����", "����", "����", "����", "���", "�ְ�", "����", "����" };

	string �����̸�(int equipment)
	{
		if (equipment < 0 || equipment >= ����_��) return "�� > " + equipment;
		return ����_�̸�[equipment];
	}

	array<string> ����_�̸� = {"â��", "�غ�", "�뺴", "�⺴", "����", "����"};

	string �����̸�By����(int equipment)
	{
		if (equipment == ����_��) return "�˺�";
		return �����̸�(pk::equipment_id_to_heishu(equipment));
	}

	string �����̸�(int heishu)
	{
		if (heishu < 0 || heishu >= ����_��) return "��";
		return ����_�̸�[heishu];
	}

	string �����̸�(int equipment)
	{
		switch(equipment)
		{
		case ����_����: return "�⺴";
		case ����_��:
		case ����_â:
		case ����_��:
		case ����_��:
			return ����_�̸�[equipment] + "��";
		}
		return ����_�̸�[equipment];
	}

	string ��������(int weapon, int tekisei)
	{
		return ��������(weapon, tekisei) + " (" + �����̸�By����(weapon) + ")";
	}

	string ��������(int weapon, int tekisei)
	{
		return �����̸�(weapon) + (weapon == ����_�� ? "" : �����̸�(tekisei));
	}

	array<string> ����_�̸� = {"C", "B", "A", "S", "S1", "S2", "S3", "S4", "S5", "S6", "S7", "S8", "S9", "SS"};

	string �����̸�(int tekisei)
	{
		int limit = ����_�̸�.length();
		if (tekisei < 0 || tekisei >= limit) return "";
		return ����_�̸�[tekisei];
	}
}*/