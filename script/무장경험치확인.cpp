/*
@만든이: 크래픽스
@Update: 2023.9.8,최초배포
@Update: 2023.9.9,행동완료후 적성경험치 표시
@Update: 2023.9.11,공격했을때만 적성경험처표시.
@Update: 2023.9.12,적성경험치 게이지 표시,on/off 옵션추가.
*/

namespace 무장경험치확인
{
	const bool 적성경험치_게이지_표시 = true;
	const bool 적성경험치_텍스트_표시 = true;
	
	const int 표시시간 = 7000;
	array<int> 적성경험치 =
	{
		0, //C
		150,//B
		200,//A
		250,//S
		200,//S1
		250,//S2
		250,//S3
		250,//S4
		250,//S5
		250,//S6
		250,//S7
		250,//S8
		250,//S9
		250,//X
	};
	array<string> 적성경험치_이름 =
	{
		"C","B","A","S","S1","S2","S3","S4","S5","S6","S7","S8","S9","X"
	};



	class UnitInfo
	{
		pk::unit@ unit = null;
		int tick = 0;
	};

	
	class Main
	{
		pk::func209_t@ prev_callback_209;


		Main()
		{
			pk::menu_item item무장경험치확인;
			item무장경험치확인.menu = 2;
			item무장경험치확인.is_enabled = pk::menu_item_is_enabled_t(Is무장경험치확인Enabled);
			item무장경험치확인.get_text = pk::menu_item_get_text_t(Get무장경험치확인Text);
			item무장경험치확인.get_desc = pk::menu_item_get_desc_t(Get무장경험치확인Desc);
			item무장경험치확인.handler = pk::menu_item_handler_t(무장경험치확인Handler);
			pk::add_menu_item(item무장경험치확인);

			pk::bind(120, pk::trigger120_t(UpdatePerFrame));
			pk::bind(173, pk::trigger173_t(부대경험치));
			pk::bind(174, pk::trigger174_t(부대행동완료));

			@prev_callback_209 = cast<pk::func209_t@>(pk::get_func(209));
			pk::reset_func(209);
			pk::set_func(209, pk::func209_t(callback209부대공격));                // 202 전법 성공 확률



			
		}


		array<pk::unit@> _attackers;

		void callback209부대공격(pk::damage_info& info, pk::unit@ attacker, int tactics_id, const pk::point& in target_pos, int type, int critical, bool ambush)
		{
			prev_callback_209(info, attacker, tactics_id, target_pos, type, critical, ambush);
			_attackers.insertLast(attacker);
		}


		void drawProgress(int x,int y,int w,int h,int color0,int color1,int percent)
		{
			pk::size size(w, h);
			pk::point pt(x, y);
			pk::rectangle r0(pt, size);
			pk::draw_rect(r0, color0);

			w = w * percent / 100.0;

			pk::size size1(w, h-2);
			pk::point pt1(x+1, y+1);
			pk::rectangle r1(pt1, size1);

			pk::draw_filled_rect(r1, color1);

		}

		float round(float a)
		{
			int b = a * 10;
			return b / 10.0;
		}

		void 부대경험치(pk::unit@ unit, int type)
		{
			
		}


		array<UnitInfo> _units;
		void 부대행동완료(pk::unit@ unit)
		{
			if (_attackers.length == 0)
				return;

			if (_attackers.findByRef(unit) == -1) 
			{
				_attackers = {};
				return;
			}
				
			if (!pk::is_player_controlled(unit))
				return;

			_attackers = {};

			int index = -1;
			for (int i = 0; i < _units.length; i++)
			{
				UnitInfo@ ui = _units[i];
				if (ui.unit.get_id() == unit.get_id())
				{
					index = i;
					break;
				}
			}

			if (index != -1)
				_units.removeAt(index);

			UnitInfo ui2;
			@ui2.unit = unit;
			ui2.tick = pk::get_tick_count();
			_units.insertLast(ui2);

		}




		void UpdatePerFrame()
		{
			UpdatePerFrameProfile();
			UpdatePerFrameText();
		}

		int getWeaponType(int a)
		{
			int type = -1;
			switch (a)
			{
			case 병기_창:type = 병종_창병; break;
			case 병기_극:type = 병종_극병; break;
			case 병기_노:type = 병종_노병; break;
			case 병기_군마:type = 병종_기병; break;
			case 병기_충차:case 병기_목수:case 병기_정란:case 병기_투석:type = 병종_병기; break;
			case 병기_주가:case 병기_누선:case 병기_투함:type = 병종_수군; break;
			default:
				break;
			}
			return type;
		}

		void UpdatePerFrameText()
		{
			int tick = pk::get_tick_count();


			array<UnitInfo> removes;
			for (int i = 0; i < _units.length; i++)
			{
				UnitInfo@ ui = _units[i];
				int off = tick - ui.tick;

				float r = pk::min(1.0, off / float(표시시간));
				if (r == 1.0)
					removes.insertLast(ui);

				r = (r - 0.8) * 5;
				if (r < 0)
					r = 0;
				r = sin(r * 3.141592 * 0.5);

				pk::point point = pk::get_neighbor_pos(ui.unit.get_pos(), 방향_북, 1);
				pk::point point2 = pk::hex_pos_to_screen_pos(point);
				pk::point point3 = pk::hex_pos_to_screen_pos(ui.unit.get_pos());

				pk::point point4;
				point4.x = (point2.x + point3.x) * 0.5;
				point4.y = (point2.y + point3.y) * 0.5;
				point4.y += 10;

				pk::point point5;
				point5.x = (point3.x + point4.x) * 0.5;
				point5.y = (point3.y + point4.y) * 0.5;

				pk::person@ p0 = pk::get_person(ui.unit.member[0]);
				pk::person@ p1 = pk::get_person(ui.unit.member[1]);
				pk::person@ p2 = pk::get_person(ui.unit.member[2]);

				int type = getWeaponType(ui.unit.weapon);
				if(type==-1)
					continue;

				int exp0 = 적성경험치[p0.tekisei[type] + 1];
				int value0 = p0.heishu_exp[type];


				string str = pk::format("{}:{}/{}", 적성경험치_이름[p0.tekisei[type]], value0, exp0);
				if(p1!=null)
					str = str +","+ pk::format("{}:{}/{}", 적성경험치_이름[p1.tekisei[type]],p1.heishu_exp[type], 적성경험치[p1.tekisei[type] + 1]);
				if (p2 != null)
					str = str + "," + pk::format("{}:{}/{}", 적성경험치_이름[p2.tekisei[type]],p2.heishu_exp[type], 적성경험치[p2.tekisei[type] + 1]);


				int color = 0x00ffff00 + int((1 - r) * 0xff) * 0x1000000;
				if(적성경험치_텍스트_표시)
					pk::draw_text(pk::encode(str), point4,color,FONT_SMALL);

				if (!적성경험치_게이지_표시)
					continue;
				//int color2 = 0x600000ff;
				int color2 = 0x000000ff + int((1 - r) * 0x60) * 0x1000000;
				//int color2 = 0x00ffff00+ int((1 - r) * 0x60) * 0x1000000;
				int color3 = 0x00ffffff + int((1 - r) * 0xff) * 0x1000000;
				int h2 = 12;
				int w2 = 75;
				if (p0 != null)
				{
					pk::draw_rect(pk::rectangle(point5, pk::size(w2, h2)), color3);
					int w = w2 * value0 / float(exp0);
					pk::draw_filled_rect(pk::rectangle(pk::point(point5.x + 1, point5.y + 1), pk::size(w, h2-1)), color2);
				}

				int x2 = point5.x;
				if (p1 != null)
				{
					x2 = x2 + w2 + 5;
					pk::draw_rect(pk::rectangle(pk::point(x2,point5.y), pk::size(w2, h2)), color3);
					int w = w2 * p1.heishu_exp[type] / float(적성경험치[p1.tekisei[type] + 1]);
					pk::draw_filled_rect(pk::rectangle(pk::point(x2 + 1, point5.y + 1), pk::size(w, h2 - 1)), color2);
				}
				if (p2 != null)
				{
					x2 = x2 + w2 + 5;
					pk::draw_rect(pk::rectangle(pk::point(x2, point5.y), pk::size(w2, h2)), color3);
					int w = w2 * p2.heishu_exp[type] / float(적성경험치[p2.tekisei[type] + 1]);
					pk::draw_filled_rect(pk::rectangle(pk::point(x2 + 1, point5.y + 1), pk::size(w, h2 - 1)), color2);
				}
			}

			while (removes.length > 0)
			{
				int index = -1;
				for (int i = 0; i < _units.length; i++)
				{
					UnitInfo@ ui = _units[i];
					if (ui.unit.get_id() == removes[0].unit.get_id())
					{
						index = i;
						break;
					}
				}
				if (index >= 0)
					_units.removeAt(index);
				removes.removeAt(0);
			}

		}

		void UpdatePerFrameProfile()
		{
			if (_person == null)
				return;

			int width = int(pk::get_resolution().width);
			int height = int(pk::get_resolution().height);

			int xoff = 10;
			int off = 40;
			int 음영 = 0x50000000;


			pk::size size(480, 480);
			pk::point pt;
			pt.x = width * 0.5 - size.width * 1.25;
			pt.y = height * 0.5 - size.height * 0.5;

			int xoff0 = 50;
			pk::point pt0;
			pt0.x = pt.x - xoff0;
			pt0.y = pt.y - xoff0;
			pk::size size00(size.width + 750, size.height + xoff0*2);
			pk::rectangle rr0(pt0, size00);
			pk::draw_filled_rect(rr0, 음영);


			pk::rectangle r0(pt,size);
			pk::draw_face(FACE_BIG, _person.face, r0,FACE_R);



			int sx = pt.x + size.width + 50;
			int sy = (height - 40 * 11) * 0.5;
			int sw = 400;
			int sh = 30;


			int exp = int(pk::core["무장.능력상승필요경험치"]);
			int percent = 0;
			

			int 통솔력 = _person.stat_exp[무장능력_통솔] % exp;
			int 무력 = _person.stat_exp[무장능력_무력] % exp;
			int 지력 = _person.stat_exp[무장능력_지력] % exp;
			int 정치력 = _person.stat_exp[무장능력_정치] % exp;
			int 매력 = _person.stat_exp[무장능력_매력] % exp;

			drawProgress(sx, sy, sw, sh, 0xffffffff, 0x400000ff, round(통솔력 / float(exp) * 100)); 
			string str0 = pk::encode(pk::format("\x1b[1x통솔:{}({}%)\x1b[0x", _person.stat[무장능력_통솔], round(통솔력 / float(exp) * 100)));
			pk::draw_text(str0,pk::point(sx+sw+xoff,sy),0xffffffff, FONT_BIG);
			pk::size size0 = pk::get_size(FONT_BIG, str0);
			pk::draw_filled_rect(pk::rectangle(pk::point(sx + sw + xoff, sy), size0), 음영);
			sy += off;

			drawProgress(sx, sy, sw, sh, 0xffffffff, 0x400000ff, round(무력 / float(exp) * 100)); 
			string str1 = pk::encode(pk::format("\x1b[1x무력:{}({}%)\x1b[0x", _person.stat[무장능력_무력], round(무력/ float(exp) * 100)));
			pk::draw_text(str1, pk::point(sx + sw + xoff, sy), 0xffffffff, FONT_BIG);
			pk::size size1 = pk::get_size(FONT_BIG, str1);
			pk::draw_filled_rect(pk::rectangle(pk::point(sx + sw + xoff, sy), size1), 음영);
			sy += off;



			drawProgress(sx, sy, sw, sh, 0xffffffff, 0x400000ff, round(지력 / float(exp) * 100)); 
			string str2 = pk::encode(pk::format("\x1b[1x지력:{}({}%)\x1b[0x", _person.stat[무장능력_지력], round(지력/ float(exp) * 100)));
			pk::draw_text(str2, pk::point(sx + sw + xoff, sy), 0xffffffff, FONT_BIG);
			pk::size size2 = pk::get_size(FONT_BIG, str2);
			pk::draw_filled_rect(pk::rectangle(pk::point(sx + sw + xoff, sy), size2), 음영);
			sy += off;


			drawProgress(sx, sy, sw, sh, 0xffffffff, 0x400000ff, round(정치력 / float(exp) * 100)); 
			string str3 = pk::encode(pk::format("\x1b[1x정치:{}({}%)\x1b[0x", _person.stat[무장능력_정치], round(정치력 / float(exp) * 100)));
			pk::draw_text(str3, pk::point(sx + sw + xoff, sy), 0xffffffff, FONT_BIG);
			pk::size size3 = pk::get_size(FONT_BIG, str3);
			pk::draw_filled_rect(pk::rectangle(pk::point(sx + sw + xoff, sy), size3), 음영);
			sy += off;


			drawProgress(sx, sy, sw, sh, 0xffffffff, 0x400000ff, round(매력 / float(exp) * 100)); 
			string str4 = pk::encode(pk::format("\x1b[1x매력:{}({}%)\x1b[0x", _person.stat[무장능력_매력], round(매력 / float(exp) * 100)));
			pk::draw_text(str4, pk::point(sx + sw + xoff, sy), 0xffffffff, FONT_BIG);
			pk::size size4 = pk::get_size(FONT_BIG, str4);
			pk::draw_filled_rect(pk::rectangle(pk::point(sx + sw + xoff, sy), size4), 음영);
			sy += off;

			exp = 적성경험치[_person.tekisei[병종_창병]+1];
			percent = round(((_person.heishu_exp[병종_창병] % exp) / float(exp)) * 100);
			drawProgress(sx, sy, sw, sh, 0xffffffff, 0x400000ff, percent);
			string str5 = pk::encode(pk::format("\x1b[1x창병:{}({}%)\x1b[0x", 적성경험치_이름[_person.tekisei[병종_창병]], percent));
			pk::draw_text(str5, pk::point(sx + sw + xoff, sy), 0xffffffff, FONT_BIG);
			pk::size size5 = pk::get_size(FONT_BIG, str5);
			pk::draw_filled_rect(pk::rectangle(pk::point(sx + sw + xoff, sy), size5), 음영);
			sy += off;

			exp = 적성경험치[_person.tekisei[병종_극병] + 1];
			percent = round(((_person.heishu_exp[병종_극병] % exp) / float(exp)) * 100);
			drawProgress(sx, sy, sw, sh, 0xffffffff, 0x400000ff, percent);
			string str6 = pk::encode(pk::format("\x1b[1x극병:{}({}%)\x1b[0x", 적성경험치_이름[_person.tekisei[병종_극병]], percent));
			pk::draw_text(str6, pk::point(sx + sw + xoff, sy), 0xffffffff, FONT_BIG);
			pk::size size6 = pk::get_size(FONT_BIG, str6);
			pk::draw_filled_rect(pk::rectangle(pk::point(sx + sw + xoff, sy), size6), 음영);
			sy += off;

			exp = 적성경험치[_person.tekisei[병종_노병] + 1];
			percent = round(((_person.heishu_exp[병종_노병] % exp) / float(exp)) * 100);
			drawProgress(sx, sy, sw, sh, 0xffffffff, 0x400000ff, percent);
			string str7 = pk::encode(pk::format("\x1b[1x노병:{}({}%)\x1b[0x", 적성경험치_이름[_person.tekisei[병종_노병]], percent));
			pk::draw_text(str7, pk::point(sx + sw + xoff, sy), 0xffffffff, FONT_BIG);
			pk::size size7 = pk::get_size(FONT_BIG, str7);
			pk::draw_filled_rect(pk::rectangle(pk::point(sx + sw + xoff, sy), size7), 음영);
			sy += off;

			exp = 적성경험치[_person.tekisei[병종_기병] + 1];
			percent = round(((_person.heishu_exp[병종_기병] % exp) / float(exp)) * 100);
			drawProgress(sx, sy, sw, sh, 0xffffffff, 0x400000ff, percent);
			string str8 = pk::encode(pk::format("\x1b[1x기병:{}({}%)\x1b[0x", 적성경험치_이름[_person.tekisei[병종_기병]], percent));
			pk::draw_text(str8, pk::point(sx + sw + xoff, sy), 0xffffffff, FONT_BIG);
			pk::size size8 = pk::get_size(FONT_BIG, str8);
			pk::draw_filled_rect(pk::rectangle(pk::point(sx + sw + xoff, sy), size8), 음영);
			sy += off;

			exp = 적성경험치[_person.tekisei[병종_병기] + 1];
			percent = round(((_person.heishu_exp[병종_병기] % exp) / float(exp)) * 100);
			drawProgress(sx, sy, sw, sh, 0xffffffff, 0x400000ff, percent);
			string str9 = pk::encode(pk::format("\x1b[1x병기:{}({}%)\x1b[0x", 적성경험치_이름[_person.tekisei[병종_병기]], percent));
			pk::draw_text(str9, pk::point(sx + sw + xoff, sy), 0xffffffff, FONT_BIG);
			pk::size size9 = pk::get_size(FONT_BIG, str9);
			pk::draw_filled_rect(pk::rectangle(pk::point(sx + sw + xoff, sy), size9), 음영);
			sy += off;

			exp = 적성경험치[_person.tekisei[병종_수군] + 1];
			percent = round(((_person.heishu_exp[병종_수군] % exp) / float(exp)) * 100);
			drawProgress(sx, sy, sw, sh, 0xffffffff, 0x400000ff, percent);
			string str10 = pk::encode(pk::format("\x1b[1x수군:{}({}%)\x1b[0x", 적성경험치_이름[_person.tekisei[병종_수군]], percent));
			pk::draw_text(str10, pk::point(sx + sw + xoff, sy), 0xffffffff, FONT_BIG);
			pk::size size10 = pk::get_size(FONT_BIG, str10);
			pk::draw_filled_rect(pk::rectangle(pk::point(sx + sw + xoff, sy), size10), 음영);
			sy += off;

		}

		bool Is무장경험치확인Enabled()
		{
			return true;
		}
		string Get무장경험치확인Text()
		{
			return pk::encode("무장경험치확인");
		}
		string Get무장경험치확인Desc()
		{
			return pk::encode("무장의 경험치를 확인합니다.");
		}

		pk::person@ _person = null;
		bool 무장경험치확인Handler()
		{
			pk::list<pk::person@> persons = pk::get_person_list(pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반, 신분_포로));

			pk::list<pk::person@> selected = pk::person_selector(pk::encode("무장선택"), pk::encode("무장을 선택하세요"), persons, 1, 1);

			@_person = selected[0];

			pk::message_box(pk::encode("확인하세요"));
			@_person = null;
			return true;
		}

		string getNameForce(pk::force@ f)
		{
			pk::person@ kunshu = pk::get_person(f.kunshu);
			return getName(kunshu);
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
