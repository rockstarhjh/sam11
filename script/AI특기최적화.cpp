/*
@������: ũ���Ƚ�
@Update: 2024.5.26
@Update: 2024.5.31, ���¿䱸ġ���� �跫Ư�⿡ ����,��ȯ,�͸� �߰�
@Update: 2024.6.1, ��ų����� ��������
@Update: 2024.6.4, ���������� ������ �䱸ġ���� ������ �跫Ư�� ����
@Update: 2024.6.5, ������ ��� -1�� �������� ó��
*/
namespace AIƯ������ȭ_SkillOptimization
{
	//��������, �� ����ũ�� ������� �����߽��ϴ�.
	array<int> Ư������ȭ_���ܹ��� = 
	{ 
		����_��Ź,����_����,����_�ձ�,����_��ȣ,����_������,����_���,����_����,����_����,����_����,����_����,����_����,����_�ѹ�,����_����,
		����_��â,����_����,����_����,����_���,����_���,����_����,����_������,����_������,����_���캸,����_����,����_����,����_�縶��,����_����
	};

	const int ��������_����_�䱸ġ = 70; //����̳� ������ 70���� ������ ������������ �Ǵ��մϴ�.
	const int ��������_���_�䱸ġ = 70;
	const int �跫Ư��_����_�䱸ġ = 70; //���´� ������ �跫Ư�⸦ ���� �ʵ��� �մϴ�.

	const bool ���ֹ���_���� = true; //���ֹ����� ��� ���� Ư�⸦ ������찡 ���� �߰��߽��ϴ�.
	
	const bool �ű�Ư��_����ȭ = true; //�ű�Ư�Ⱓ�� ��ȯ�� �մϴ�.
	const bool ���Ư��_����ȭ = true; //���Ư�Ⱓ�� ��ȯ�� �մϴ�.
	const bool ����Ư��_����ȭ = true; //����Ư��,�ú�Ư��,����Ư��,�⺴Ư��,â��Ư��,�غ�Ư��,����Ư��,����Ư�Ⱓ�� ��ȯ�� �մϴ�.
	
	const bool ����Ư��_��ȯ_��� = true; //���������� ����Ư�⸦ ������� ��ȯ�մϴ�.
	const bool ����Ư��_��_����_��ȯ_��� = true;//���������� ����Ư�⸦ ������� ��ȯ�մϴ�.
	const bool ����Ư��_��_�ɸ�_����_��ȯ_��� = true;//���������� ����Ư�⸦ ������� ��ȯ�մϴ�.
	const bool ����Ư��_��ȣ_�̵�_¡��_¡��_��ȯ_��� = true;//���������� ����Ư�⸦ ������� ��ȯ�մϴ�.
	const bool ����Ư��_����_��ȯ_��� = true;//���������� ����Ư�⸦ ������� ��ȯ�մϴ�.


	array<int> �ű�Ư�� = { Ư��_���, Ư��_�ؽ�, Ư��_�ý�, Ư��_����,Ư��_����, Ư��_â��,Ư��_����};
	array<int> ���Ư�� = { Ư��_����, Ư��_����, Ư��_����, Ư��_����,Ư��_����, Ư��_â��};

	//����Ư��� ��ȯ�Ͻø� ���������� Ư�ⱳȯ �Ͼ�ϴ�. ������ ���� �ʴ� ���
	array<int> ����Ư�� = { Ư��_���� };
	array<int> �ú�Ư�� = { Ư��_��� };
	array<int> ����Ư�� = { Ư��_����, Ư��_�ɰ� };
	array<int> �⺴Ư�� = { Ư��_���� ,Ư��_�鸶 ,Ư��_�౺};
	array<int> â��Ư�� = { };
	array<int> �غ�Ư�� = { };
	array<int> ����Ư�� = { Ư��_����,Ư��_���� ,Ư��_�޽�,Ư��_����};
	array<int> ����Ư�� = { Ư��_����, Ư��_��Ÿ ,Ư��_����};
	/// /////////////////////////////////////////////////////////////////////////////////////////
	

	array<int> �����Ư�� = { Ư��_����,Ư��_����,Ư��_����,Ư��_����,Ư��_�п� };

	array<int> ��üƯ�� = { Ư��_����,Ư��_�Ӿ�,Ư��_����,Ư��_��Ż,Ư��_���,Ư��_����,Ư��_ȣ��,Ư��_�־�,Ư��_���� };
	array<int> ��üƯ��2= { Ư��_����,Ư��_����,Ư��_��ǳ ,Ư��_����,Ư��_���� };

	array<int> ����Ư�� = { Ư��_�ݰ�,Ư��_�ұ� ,Ư��_ö�� ,Ư��_� };
	array<int> �跫���Ư�� = { Ư��_���� ,Ư��_ħ�� ,Ư��_��� ,Ư��_����};
	array<int> ȭ��Ư�� = { Ư��_ȭ�� ,Ư��_ȭ�� };
	array<int> �跫Ư�� = { Ư��_�ź� ,Ư��_�� ,Ư��_�ⷫ,Ư��_�˰�,Ư��_���� ,Ư��_��å,Ư��_����,Ư��_�ݰ� };
	array<int> �跫Ư��_���_�Ż�_�ɸ� = { Ư��_���, Ư��_�Ż� ,Ư��_�ɸ�};
	array<int> �跫Ư��_����_�͸�_��ȯ = {Ư��_���� ,Ư��_�͸� ,Ư��_��ȯ};
	array<int> ���_�͹� = { Ư��_��� ,Ư��_�͹�};
	array<int> ����Ư�� = {Ư��_�汹,Ư��_����};
	
	array<int> ����Ư�� = { Ư��_����,Ư��_�߸�,Ư��_���� ,Ư��_���� ,Ư��_�ȷ�,Ư��_���� ,Ư��_��� };
	array<int> ����Ư��_��_���� = {Ư��_��,Ư��_����};
	array<int> ����Ư��_��_�ɸ�_���� = { Ư��_�� ,Ư��_�ɸ�,Ư��_���� };
	array<int> ����Ư��_��ȣ_�̵�_¡��_¡�� = { Ư��_��ȣ ,Ư��_�̵�,Ư��_¡��, Ư��_¡�� };
	array<int> ����Ư��_���� = { Ư��_ģ�� ,Ư��_ģ��,Ư��_ģ�� ,Ư��_ģ�� ,Ư��_ǳ��,Ư��_��� };

	//����Ư��� ��ȯ ���� Ư�� ����///////////////////////////////////////////////////////////////////////////////////////
	array<array<int>> ����Ư��_��ȯ = { ��üƯ��,�跫Ư�� };
	array<array<int>> ����Ư��_��_����_��ȯ = { ��üƯ��2,�跫Ư��_����_�͸�_��ȯ ,�����Ư��,�跫Ư��_���_�Ż�_�ɸ� };
	array<array<int>> ����Ư��_��_�ɸ�_����_��ȯ = { �跫���Ư�� };
	array<array<int>> ����Ư��_��ȣ_�̵�_¡��_¡��_��ȯ = { �跫���Ư��,����Ư�� };
	array<array<int>> ����Ư��_����_��ȯ = { ����Ư��, �跫Ư�� };


	class Main
	{
		Main()
		{
			pk::bind(102, pk::trigger102_t(Init));
			pk::bind(111, pk::trigger111_t(onTurn));
		}
		void Init()
		{

			for (int i = 0; i < ����_��; i++)
			{
				pk::person@ p = pk::get_person(i);
				if(p.is_player())
					continue;
				if ((p.get_id() >= ����_���� && p.get_id() <= ����_�̺�ƮA0) || p.get_id() >= ����_����)
					continue;

				pk::force@ f = pk::get_force(p.get_force_id());
				if(f==null)
					continue;
				if(Ư������ȭ_���ܹ���.find(p.get_id()) >=0)
					continue;
				if(���ֹ���_���� && p.mibun == �ź�_����)
					continue;

				update�ű�Ư��(p, f);
				update���Ư��(p, f);
				update����Ư��(p, f);
				update����Ư��(p, f);
			}
		}
		void onTurn(pk::force@ f)
		{
			if (f.is_player())
				return;
			pk::list<pk::person@> ps = pk::get_person_list(f, pk::mibun_flags(�ź�_����,�ź�_����,�ź�_�¼�,�ź�_�Ϲ�,�ź�_����));
			for (int i = 0; i < ps.count; i++)
			{
				pk::person@ p = ps[i];
				if ((p.get_id() >= ����_���� && p.get_id() <= ����_�̺�ƮA0) || p.get_id() >= ����_����)
					continue;
				if (Ư������ȭ_���ܹ���.find(p.get_id()) >= 0)
					continue;
				if (���ֹ���_���� && p.mibun == �ź�_����)
					continue;


				update�ű�Ư��(p, f);
				update���Ư��(p, f);
				update����Ư��(p, f);
				update����Ư��(p, f);
			}
		}

		bool check��������(pk::person@ p)
		{
			return p.max_stat[����ɷ�_����] >= ��������_����_�䱸ġ || p.max_stat[����ɷ�_���] >= ��������_���_�䱸ġ;
		}

		int get����(int weapon, pk::person@ p)
		{
			if (weapon == -1)
				return 0;
			return p.tekisei[weapon];
		}
		int get�ִ���������(pk::person@ p)
		{
			int max = -1;
			int maxIndex = -1;
			for (int i = 0; i < ����_��; i++)
			{
				if (p.tekisei[i] > max)
				{
					maxIndex = i;
					max = p.tekisei[i];
				}
			}
			return maxIndex;
		}

		int getƯ��_����(int Ư��)
		{
			switch (Ư��)
			{
			case Ư��_â��:	case Ư��_â��: return ����_â��;
			case Ư��_����: case Ư��_�ؽ�: return ����_�غ�;
			case Ư��_����: case Ư��_�ý�: return ����_�뺴;
			case Ư��_����: case Ư��_���: return ����_�⺴;
			case Ư��_����: case Ư��_����: return ����_����;
			case Ư��_����: case Ư��_����: return ����_����;
			default:
				break;
			}
			return -1;
		}
		int get����_Ư��_�ű�(int ����)
		{
			switch (����)
			{
			case ����_â��: return Ư��_â��;
			case ����_�غ�: return Ư��_�ؽ�;
			case ����_�뺴: return Ư��_�ý�;
			case ����_�⺴: return Ư��_���;
			case ����_����: return Ư��_����;
			case ����_����: return Ư��_����;
			default:
				break;
			}
			return -1;
		}
		int get����_Ư��_���(int ����)
		{
			switch (����)
			{
			case ����_â��: return Ư��_â��;
			case ����_�غ�: return Ư��_����;
			case ����_�뺴: return Ư��_����;
			case ����_�⺴: return Ư��_����;
			case ����_����: return Ư��_����;
			case ����_����: return Ư��_����;
			default:
				break;
			}
			return -1;
		}

		string get�ִ�����str(int ����)
		{
			switch (����)
			{
			case 0: return "C";
			case 1: return "B";
			case 2: return "A";
			case 3: return "S";
			case 4: return "S1";
			case 5: return "S2";
			case 6: return "S3";
			case 7: return "S4";
			case 8: return "S5";
			case 9: return "S6";
			case 10: return "S7";
			case 11: return "S8";
			case 12: return "S9";
				
			default:return "SX";
				break;
			}
			return "";
		}

		void update�ű�Ư��(pk::person@ p,pk::force@ f)
		{
			if (!�ű�Ư��_����ȭ)
				return;
			if (�ű�Ư��.find(p.skill) == -1)
				return;

			if (p.tekisei[0] < 0 && p.tekisei[1] < 0 && p.tekisei[2] < 0 && p.tekisei[3] < 0 && p.tekisei[4] < 0 && p.tekisei[5] < 0)
			{
				int ���� = getƯ��_����(p.skill);
				for (int i = 0; i < 6; i++)
				{
					p.tekisei[i] = ����_B;
				}
				p.tekisei[����] = ����_S;
				string strType = "";
				switch (����)
				{
				case ����_â��: strType = "â��"; break;
				case ����_�غ�: strType = "�غ�"; break;
				case ����_�뺴: strType = "�뺴"; break;
				case ����_�⺴: strType = "�⺴"; break;
				case ����_����: strType = "����"; break;
				case ����_����: strType = "����"; break;
				default:
					break;
				}

				string str = pk::format("\x1b[2x{}��\x1b[0x,\x1b[1x{}\x1b[0x,{},S ����ȭ", getName(f), getName(p), strType);
				pk::history_log(p.get_pos(), f != null ? f.color : 0, pk::encode(str));
				return;
			}

			int bskill = p.skill;
			if (p.skill != Ư��_����)
			{
				int a = get����(getƯ��_����(p.skill), p);
				if (a < ����_S) 
				{
					int �ִ��������� = get�ִ���������(p);
					int �ִ����� = get����(�ִ���������,p);
					//pk::printf("�ִ�����:{},{}\n", getName(p), get�ִ�����str(�ִ�����));
					if (�ִ����� > a) 
					{
						int s = get����_Ư��_�ű�(�ִ���������);
						if(!pk::has_skill(p,s))
							p.skill = s;
					}
				}
			}
			else 
			{
				int a = get����(����_�غ�,p);
				int b = get����(����_â��,p);
				if (a < ����_S && b < ����_S)
				{
					int �ִ��������� = get�ִ���������(p);
					int �ִ����� = get����(�ִ���������,p);
					if (�ִ��������� != ����_�غ� && �ִ��������� != ����_â�� && (�ִ����� > a && �ִ����� > b))
					{
						int s = get����_Ư��_�ű�(�ִ���������);
						if (!pk::has_skill(p, s))
							p.skill = s;
					}
				}
			}
			if (bskill == p.skill)
				return;

			string str = pk::format("\x1b[2x{}��\x1b[0x,\x1b[1x{}\x1b[0x,{}->{} ����ȭ", getName(f), getName(p),getNameSkill(bskill),getNameSkill(p.skill));
			pk::history_log(p.get_pos(), f != null ? f.color : 0, pk::encode(str));
		}
		void update���Ư��(pk::person@ p, pk::force@ f)
		{
			if (!���Ư��_����ȭ)
				return;
			if (���Ư��.find(p.skill) == -1)
				return;


			if (p.tekisei[0] < 0 && p.tekisei[1] < 0 && p.tekisei[2] < 0 && p.tekisei[3] < 0 && p.tekisei[4] < 0 && p.tekisei[5] < 0)
			{
				int ���� = getƯ��_����(p.skill);
				for (int i = 0; i < 6; i++)
				{
					p.tekisei[i] = ����_B;
				}
				p.tekisei[����] = ����_S;
				string strType = "";
				switch (����)
				{
				case ����_â��: strType = "â��"; break;
				case ����_�غ�: strType = "�غ�"; break;
				case ����_�뺴: strType = "�뺴"; break;
				case ����_�⺴: strType = "�⺴"; break;
				case ����_����: strType = "����"; break;
				case ����_����: strType = "����"; break;
				default:
					break;
				}

				string str = pk::format("\x1b[2x{}��\x1b[0x,\x1b[1x{}\x1b[0x,{},S ����ȭ", getName(f), getName(p), strType);
				pk::history_log(p.get_pos(), f != null ? f.color : 0, pk::encode(str));
				return;
			}


			int bskill = p.skill;


			int a = get����(getƯ��_����(p.skill), p);
			if (a < ����_S)
			{
				int �ִ��������� = get�ִ���������(p);
				int �ִ����� = get����(�ִ���������,p);
				if (�ִ����� > a) 
				{
					int s = get����_Ư��_���(�ִ���������);
					if (!pk::has_skill(p, s))
						p.skill = s;
				}
			}
			if (bskill == p.skill)
				return;

			string str = pk::format("\x1b[2x{}��\x1b[0x,\x1b[1x{}\x1b[0x,{}->{} ����ȭ", getName(f), getName(p), getNameSkill(bskill), getNameSkill(p.skill));
			pk::history_log(p.get_pos(), f != null ? f.color : 0, pk::encode(str));
		}

		array<int> get����Ư��(int ����)
		{
			switch (����)
			{
			case ����_â��: return â��Ư��;
			case ����_�غ�: return �غ�Ư��;
			case ����_�뺴: return �ú�Ư��;
			case ����_�⺴: return �⺴Ư��;
			case ����_����: return ����Ư��;
			case ����_����: return ����Ư��;
			default:
				break;
			}
			array<int> arr;
			return arr;
		}

		void updateSkill(pk::person@ p, array<int> arr)
		{
			array<int> arr2 = arr;
			while (arr2.length > 0)
			{
				int r = pk::rand(arr2.length);
				int s = arr2[r];
				if (!pk::has_skill(p, s))
				{
					p.skill = s;
					return;
				}

				arr2.removeAt(r);
			}
		}

		void updateSkill(pk::person@ p, array<array<int>> arr)
		{
			array<int> arr2;
			for (int i = 0; i < arr.length; i++)
			{
				for (int j = 0; j < arr[i].length; j++)
				{
					int s = arr[i][j];
					if (p.max_stat[����ɷ�_����] < �跫Ư��_����_�䱸ġ || p.max_stat[����ɷ�_����] > ��������_����_�䱸ġ)
					{
						if (�跫Ư��.find(s) >= 0 || �跫Ư��_���_�Ż�_�ɸ�.find(s) >= 0 || �跫Ư��_����_�͸�_��ȯ.find(s) >= 0)
						{
							continue;
						}
					}
					arr2.insertLast(s);
				}
			}
			updateSkill(p, arr2);
		}

		void update����Ư��(pk::person@ p, pk::force@ f)
		{
			if (!����Ư��_����ȭ)
				return;
			if (p.skill == -1)
				return;
			if (����Ư��.find(p.skill) == -1 && �ú�Ư��.find(p.skill) == -1 && �⺴Ư��.find(p.skill) == -1 && â��Ư��.find(p.skill) == -1 && �غ�Ư��.find(p.skill) == -1 &&
				����Ư��.find(p.skill) == -1 && ����Ư��.find(p.skill) == -1)
				return;

		
			int bskill = p.skill;

			if (����Ư��.find(p.skill) >= 0)
			{
				int �ִ뺴�� = get�ִ���������(p);
				if (�ִ뺴�� == ����_����)
				{
					updateSkill(p, ����Ư��);
				}
				else if (�ִ뺴�� == ����_����)
				{
					updateSkill(p, ����Ư��);
				}
				else 
				{
					return;
				}
			}
			else 
			{
				int a = -1;
				if (����Ư��.find(p.skill) >= 0)
					a = get����(����_����,p);
				if (a == -1 && �ú�Ư��.find(p.skill) >= 0)
					a = get����(����_�뺴,p);
				if (a == -1 && ����Ư��.find(p.skill) >= 0)
					a = get����(����_����, p);
				if (a == -1 && �⺴Ư��.find(p.skill) >= 0)
					a = get����(����_�⺴,p);
				if (a==-1 && ����Ư��.find(p.skill) >= 0)
				{
					int a0 = get����(����_â��, p);
					int a1 = get����(����_�غ�, p);
					int a2 = get����(����_�⺴, p);
					a = pk::max(pk::max(a0, a1), a2);
				}
				if (a == -1 && â��Ư��.find(p.skill) >= 0)
					a = get����(����_â��,p);
				if (a == -1 && �غ�Ư��.find(p.skill) >= 0)
					a = get����(����_�غ�,p);

				if (a < ����_S)
				{
					int �ִ��������� = get�ִ���������(p);
					int �ִ����� = get����(�ִ���������,p);
					if (�ִ����� > a)
					{
						array<int> arr = get����Ư��(�ִ���������);
						updateSkill(p, arr);
					}
				}
			}

			if (bskill == p.skill)
				return;

			string str = pk::format("\x1b[2x{}��\x1b[0x,\x1b[1x{}\x1b[0x,{}->{} ����ȭ", getName(f), getName(p), getNameSkill(bskill), getNameSkill(p.skill));
			pk::history_log(p.get_pos(), f != null ? f.color : 0, pk::encode(str));
		}

		void update����Ư��(pk::person@ p, pk::force@ f)
		{
			if (!check��������(p))
				return;

			array<array<int>> arrs;
			if (����Ư��_��ȯ_��� && ����Ư��.find(p.skill) >= 0)
			{
				arrs = ����Ư��_��ȯ;
			}
			else if (����Ư��_��_����_��ȯ_��� && ����Ư��_��_����.find(p.skill) >= 0)
			{
				arrs = ����Ư��_��_����_��ȯ;
			}
			else if (����Ư��_��_�ɸ�_����_��ȯ_��� && ����Ư��_��_�ɸ�_����.find(p.skill) >= 0)
			{
				arrs = ����Ư��_��_�ɸ�_����_��ȯ;
			}
			else if (����Ư��_��ȣ_�̵�_¡��_¡��_��ȯ_��� && ����Ư��_��ȣ_�̵�_¡��_¡��.find(p.skill) >= 0)
			{
				arrs = ����Ư��_��ȣ_�̵�_¡��_¡��_��ȯ;
			}
			else if(����Ư��_����_��ȯ_��� && ����Ư��_����.find(p.skill) >= 0)
			{
				arrs = ����Ư��_����_��ȯ;
			}
			if (arrs.length == 0)
				return;

			int bskill = p.skill;
			updateSkill(p, arrs);

			if (bskill == p.skill)
				return;

			string str = pk::format("\x1b[2x{}��\x1b[0x,\x1b[1x{}\x1b[0x,{}->{} ����ȭ", getName(f), getName(p), getNameSkill(bskill), getNameSkill(p.skill));
			pk::history_log(p.get_pos(), f != null ? f.color : 0, pk::encode(str));
		}

		string getNameSkill(int skill)
		{
			return getName(pk::get_skill(skill));
		}
		string getName(pk::force@ f)
		{
			if (f == null)
				return "null";
			return getName(pk::get_person(f.kunshu));
		}
		string getName(pk::object@ obj)
		{
			return obj != null ? pk::decode(pk::get_name(obj)) : "null";
		}
		string getNameLeader(pk::unit@ obj)
		{
			if (obj == null)
				return "null";
			pk::person@ p = pk::get_person(obj.leader);
			if (p == null)
				return "null";
			return pk::decode(pk::get_name(p));
		}

	}

	Main main;
}

