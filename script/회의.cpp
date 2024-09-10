namespace 회의
{
    // =========================== 커스텀 가능한 부분 ===============================

    const int 회의개최_최소인원 = 4; //  1 ~ 6 사이로 설정할 것(군주를 제외한 숫자입니다).  최대인원 = 6 
    
    /*
        회의의 안건마다 난이도를 각각 1~3단계로 설정해 두었으며, 달성 보상 역시 차등을 두었습니다.
        기교포인트를 제외한 나머지 보상들은 보상을 확정했을 경우에 기존에 설정한 최소~최대값 사이에서 보상이 결정됩니다.
        가령 장수 수명같은 경우에는 1단계 보상의 경우 1년~3년 사이로 획득이 되는 방식입니다.
        특기의 경우에는 해당 단계에 설정된 특기들 중 랜덤하게 결정됩니다.

        만약 보상을 선택하지 않고 심플하게 기교포인트만 받고 싶을 경우에는 보상_선택가능 항목을 false로 변경해주시면 되겠습니다.
    */

    const bool 보상_선택가능 = true;      // false 시 보상이 기교포인트로 고정됨.

    const array<int> 달성보상_충성도 = { 2, 4, 6 };       // 보상 선택에 관계없이 목표 달성 시 증가하는 전체 무장의 충성도 입니다. 실패 시 해당 수치만큼 감소합니다.
    const array<int> 달성보상_공적 = { 1000, 2000, 4000 }; // 보상 선택에 관계없이 목표 달성 시 증가하는 제안자의 공적입니다. 실패해도 감소하지 않습니다.
    const int 실패시_충성도하락_배율 = 2;
    /*
        아래의 보상들의 수치는 앞의 것이 최소, 뒤의 것이 최대값 입니다. 
        보상을 확정했을 경우 범위 내에서 랜덤하게 보상이 지급되고 기교 포인트의 경우에는 반올림한 값이 주어집니다.

        특기의 경우에는 해당 목록중 하나를 랜덤하게 획득합니다.

        만약 가챠 방식이 싫고 정확한 수치대로 보상을 얻고싶으시다면, 양쪽의 숫자를 같게 설정해주시면 됩니다.

        능력이나 병과 경험치의 경우 플레이어의 경험치 세팅값을 모르기 때문에 각자 적당하게 분배해주시면 되겠습니다.
    */
    const array<int> 달성보상_기교_초급 = { 500, 1000 };            // 100 이상의 숫자로 설정
    const array<int> 달성보상_기교_중급 = { 1000, 2500 };
    const array<int> 달성보상_기교_고급 = { 2000, 4000 };

    const array<int> 달성보상_능력경험치_초급 = { 10, 30 };
    const array<int> 달성보상_능력경험치_중급 = { 25, 60 };
    const array<int> 달성보상_능력경험치_고급 = { 50, 100 };

    const array<int> 달성보상_병과경험치_초급 = { 5, 20 };
    const array<int> 달성보상_병과경험치_중급 = { 15, 30 };
    const array<int> 달성보상_병과경험치_고급 = { 25, 50 };

    const array<int> 달성보상_수명_초급 = { 1, 3 };
    const array<int> 달성보상_수명_중급 = { 2, 6 };
    const array<int> 달성보상_수명_고급 = { 4, 10 };

    // 특기 개수는 7개로 통일 할것
    const array<int> 달성보상_특기_초급 = { 특기_사정, 특기_기각, 특기_사수, 특기_난전, 특기_앙양, 특기_불굴, 특기_급습 };
    const array<int> 달성보상_특기_중급 = { 특기_기장, 특기_창장, 특기_극장, 특기_궁장, 특기_수장, 특기_공성, 특기_행군 };
    const array<int> 달성보상_특기_고급 = { 특기_허실, 특기_명경, 특기_통찰, 특기_용장, 특기_포박, 특기_강행, 특기_강운 };

    // ============================================================================

    // ============================ 아래 숫자는 수정하지 말 것 ===========================

    const int 목표_없음 = -1;
    const int 목표_진행 = 0;
    const int 목표_달성 = 1;
    const int 목표_실패 = 2;

    const int 목표_보물수집 = 0;
    const int 목표_무장처단 = 1;
    const int 목표_특정무장 = 2;
    const int 목표_특기무장 = 3;
    const int 목표_능력무장 = 4;
    const int 목표_전체무장 = 5;
    const int 목표_도시공략 = 6;
    const int 목표_도시방비 = 7;
    const int 목표_세력군비 = 8;
    const int 목표_황제옹립 = 9;
    const int 목표_황제폐위 = 10;
    const int 목표_작위제수 = 11;
    const int 목표_기교연구 = 12;
    const int 목표_세력동맹 = 13;
    const int 목표_세력친밀 = 14;
    const int 목표_본거지_아군 = 15;                // 아군 세력내 본거지 0
    const int 목표_본거지_적군 = 16;                // 적 도시에 본거지 발생시키기
    const int 목표_구호탄랑 = 17;                   // 사용안함       
    const int 목표_동작대 = 18;
    const int 목표_동조 = 19;
    const int 목표_고갈 = 20;
    const int 목표_끝 = 21;

    const int 세력군비_창극노 = 0;             // 창극노 합산 1000x, 병사 1000x필요
    const int 세력군비_기마 = 1;               // 기마 1000x 필요
    const int 세력군비_정란 = 2;               // 정란 or 투석 x개 필요
    const int 세력군비_충차 = 3;               // 충차 or 목수 x개 필요
    const int 세력군비_누선 = 4;               // 누선 or 투함 x개 준비
    const int 세력군비_끝 = 5;

    const pk::point 목표상태_좌표 = pk::point(0, 199);
    const pk::point 목표_좌표 = pk::point(1, 199);
    const pk::point 목표조건1_좌표 = pk::point(2, 199);
    const pk::point 목표조건2_좌표 = pk::point(3, 199);
    const pk::point 목표수치_좌표 = pk::point(4, 199);
    const pk::point 목표보상_좌표 = pk::point(5, 199);
    const pk::point 목표제안무장_좌표 = pk::point(6, 199);

    const int 목표상태 = 0;
    const int 목표 = 1;
    const int 목표조건1 = 2;
    const int 목표조건2 = 3;
    const int 목표수치 = 4;
    const int 목표보상 = 5;
    const int 목표제안무장 = 6;

    array<string> 무장능력 = {"통솔", "무력", "지력", "정치", "매력"};
    array<string> 병기 = {"창,극,노", "군마", "공성병기", "선박"};
    const int 창극노 = 0;
    const int 군마 = 1;
    const int 공성병기 = 2;
    const int 선박 = 3;

    const int 회의_개최 = 0;
    const int 회의_미개최 = 1;
    array<string> choose_conference_hold_array = { pk::u8encode("회의를 연다."), pk::u8encode("회의를 열지 않는다.")};

    const int 회의_채택 = 0;
    const int 회의_확인 = 1;
    const int 회의_보류 = 2;
    array<string> choose_conference_decision_array = { pk::u8encode("의견을 채택한다"), pk::u8encode("의견을 확인한다."), pk::u8encode("의견을 보류한다.") };

                                       // 기본값 (각각 1,2,3단계 보상)
    const int 보상_기교 = 0;            // (500 ~ 1500), (1000 ~ 2500), (2000, 4000)
    const int 보상_능력경험치 = 1;      // (10 ~ 30), (25 ~ 60), (50 ~ 100)
    const int 보상_병과경험치 = 2;      // (5 ~ 20) , (15 ~ 30), (25 ~ 50)
    const int 보상_특기 = 3;           // 
    const int 보상_수명 = 4;           // (1 ~ 3), (2 ~ 6), (4 ~ 10)
    const int 보상_끝 = 5;             
    

    class Opinion
    {
        int subject = -1;                // 목표
        int subject_condition1 = -1;     // 목표조건1
        int subject_condition2 = -1;     // 목표조건1
        int subject_count = -1;          // 목표수치
        int subject_level = -1;

        Opinion()
        {

        }

        void set_opinion(int sub, int sub_con1, int sub_con2, int sub_count, int sub_level)
        {
            subject = sub;
            subject_condition1 = sub_con1;
            subject_condition2 = sub_con2;
            subject_count = sub_count;
            subject_level = sub_level;
        }

        void clear()
        {
            subject = -1;
            subject_condition1 = -1;
            subject_condition2 = -1;
            subject_count = -1;
            subject_level = -1;
        }
    };

    class Proposal
    {
        pk::person@ speaker = null;
        Opinion opinion;
        string dialog = "";              // 대사

        //[0] (int) 목표상태 = 목표_없음;
        //
        //[1] (int) 목표 = -1;           
        //[2] (int) 목표조건1 = -1;    // 무장처단, 특정무장 : 무장 ID.  특기무장, 능력무장 : 특기ID, 능력ID.  도시공략, 도시방비 : 도시ID.  
        //                       // 세력군비 : 세력군비ID. 작위제수 : 작위ID. 기교연구 : 기교ID. 세력동맹,친밀 : 목표세력ID.
        //                       // 구호탄랑 : 도시ID
        //
        //[3] (int) 목표조건2 = -1;    // 능력무장 : 능력치 조건값.
        //
        //[4] (int) 목표수치 = -1;     // 특기무장, 능력무장, 전체무장 : 무장 숫자. 도시방비 : 방어건물 갯수. 세력군비 : 병장기, 병사수
        
        Proposal()
        {

        }

        void set_proposal(pk::person@ person, int sub, int sub_con1, int sub_con2, int sub_count, int sub_level)
        {
            @speaker = person;
            opinion.subject = sub;
            opinion.subject_condition1 = sub_con1;
            opinion.subject_condition2 = sub_con2;
            opinion.subject_count = sub_count;
            opinion.subject_level = sub_level;

            if (sub == 목표_보물수집)
            {
                dialog = pk::format("천하에는 \x1b[16x{}\x1b[0x(이)라고 하는 보물이 있다고 하는데, 그것을 꼭 얻고 싶습니다.", pk::u8decode(pk::get_item(sub_con1).name));
            }
            else if (sub == 목표_무장처단)
            {
                pk::person@ target = pk::get_person(sub_con1);
                pk::force@ force = pk::get_force(target.get_force_id());
                string target_force = "";
                if (force.kokugou == -1)
                {
                    target_force = pk::u8decode(pk::get_name(pk::get_person(force.kunshu)));
                }
                else
                {
                    target_force = pk::u8decode(pk::get_kokugou(force.kokugou).get_name());
                }

                dialog = pk::format("\x1b[1x{}\x1b[0x군의 \x1b[2x{}\x1b[0x(은)는 매우 위협적입니다. 서둘러 그자를 처리해야 합니다.", target_force, pk::u8decode(pk::get_name(target)));
            }
            else if (sub == 목표_특정무장)
            {
                pk::person@ target = pk::get_person(sub_con1);

                int 대상무장_통솔 = target.base_stat[무장능력_통솔];
                int 대상무장_무력 = target.base_stat[무장능력_무력];
                int 대상무장_지력 = target.base_stat[무장능력_지력];
                int 대상무장_정치 = target.base_stat[무장능력_정치];
                int 대상무장_매력 = target.base_stat[무장능력_매력];

                if (대상무장_통솔 >= 90)
                {
                    if (대상무장_무력 >= 90 || 대상무장_지력 >= 90 || 대상무장_정치 >= 90 || 대상무장_매력 >= 90)
                    {
                        dialog = pk::format("\x1b[2x{}\x1b[0x에게는 영웅의 풍모가 보입니다. 반드시 우리편으로 끌어들여야 합니다.", pk::u8decode(pk::get_name(target)));
                    }
                    else
                    {
                        dialog = pk::format("\x1b[2x{}\x1b[0x의 군재는 우리군에 반드시 필요한 능력입니다.", pk::u8decode(pk::get_name(target)));
                    }
                }
                else if (대상무장_무력 >= 90)
                {
                    if (대상무장_지력 >= 90 || 대상무장_정치 >= 90 || 대상무장_매력 >= 90)
                    {
                        dialog = pk::format("\x1b[2x{}\x1b[0의 재주는 매우 놀랍습니다. 반드시 우리편으로 끌어들여야 합니다.", pk::u8decode(pk::get_name(target)));
                    }
                    else
                    {
                        dialog = pk::format("\x1b[2x{}\x1b[0x(을)를 우리편으로 만들면 군세가 한층 강해질 것입니다.", pk::u8decode(pk::get_name(target)));
                    }
                }
                else if (대상무장_지력 >= 90)
                {
                    if (대상무장_정치 >= 90 || 대상무장_매력 >= 90)
                    {
                        dialog = pk::format("\x1b[2x{}\x1b[0x의 지모는 천하에 널리 알려졌습니다. 반드시 우리편으로 끌어들여야 합니다.", pk::u8decode(pk::get_name(target)));
                    }
                    else
                    {
                        dialog = pk::format("\x1b[2x{}\x1b[0x(을)를 등용해야 합니다. 그 지혜는 반드시 도움이 될 것입니다.", pk::u8decode(pk::get_name(target)));
                    }
                }
                else if (대상무장_정치 >= 90)
                {
                    if (대상무장_매력 >= 90)
                    {
                        dialog = pk::format("\x1b[2x{}\x1b[0x(은)는 온 나라가 알고있는 재사입니다. 반드시 우리편으로 끌어들여야 합니다.", pk::u8decode(pk::get_name(target)));
                    }
                    else
                    {
                        dialog = pk::format("\x1b[2x{}\x1b[0x(을)를 등용해야 합니다. 우리군에는 그의 식견이 필요합니다.", pk::u8decode(pk::get_name(target)));
                    }
                }
                else if (대상무장_매력 >= 90)
                {
                    dialog = pk::format("\x1b[2x{}\x1b[0x(은)는 뛰어난 인품으로 소문이 자자합니다. 아군에게 도움이 될 것입니다", pk::u8decode(pk::get_name(target)));
                }
                else
                {
                    dialog = pk::format("\x1b[2x{}\x1b[0x(이)라는 인물이 매우 뛰어나다고 합니다. 저희군에 도움이 될테니 등용해야 합니다.", pk::u8decode(pk::get_name(target)));
                }
            }
            else if (sub == 목표_특기무장)
            {
                pk::skill@ skill = pk::get_skill(sub_con1);
                int type = skill.type;

                switch (type)
                {
                case 특기종류_행군:
                    dialog = pk::format("용병에는 신속함이 가장 중요하다고 했습니다. \x1b[1x{}\x1b[0x 특기 무장을 얻어야 합니다.", pk::u8decode(pk::get_name(skill)));
                    break;

                case 특기종류_공격:
                    dialog = pk::format("감히 대적할 수 없는 군세를 갖춰놓아야 합니다. \x1b[1x{}\x1b[0x 특기 무장을 얻어야 합니다.", pk::u8decode(pk::get_name(skill)));
                    break;

                case 특기종류_방어:
                    dialog = pk::format("방어를 단단히 갖춘다면 적은 스스로 물러나게 될 것입니다. \x1b[1x{}\x1b[0x 특기 무장을 얻어야 합니다.", pk::u8decode(pk::get_name(skill)));
                    break;

                case 특기종류_계략:
                    dialog = pk::format("손자왈 싸우지 않고 이기는 것이 최상이라 했습니다. \x1b[1x{}\x1b[0x 특기 무장을 얻어야 합니다.", pk::u8decode(pk::get_name(skill)));
                    break;

                case 특기종류_보조:
                    dialog = pk::format("육도 용도편에 따르면 유능한 보좌관들이 필수라고 보여집니다. \x1b[1x{}\x1b[0x 특기 무장을 얻어야 합니다.", pk::u8decode(pk::get_name(skill)));
                    break;

                case 특기종류_내정:
                    dialog = pk::format("내정을 안정시킨다면 알아서 기회가 찾아올 것입니다. \x1b[1x{}\x1b[0x 특기 무장을 얻어야 합니다.", pk::u8decode(pk::get_name(skill)));
                    break;
                }
               
            }
            else if (sub == 목표_능력무장)
            {
                int curr = 0;

                auto list = pk::get_person_list(pk::get_force(person.get_force_id()), pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반, 신분_포로));

                for (int i = 0; i < list.count; ++i)
                {
                    if (list[i].stat[sub_con1] >= sub_con2)
                        curr++;
                }

                dialog = pk::format("타국에 뒤쳐지지 않기 위해서는 \x1b[1x{}\x1b[0x(이)가 \x1b[2x{}\x1b[0x 이상인 무장이 \x1b[2x{}\x1b[0x명 이상 필요합니다. \n (현재 : {}명)", 무장능력[sub_con1], sub_con2, sub_count, curr);
            }
            else if (sub == 목표_전체무장)
            {
                auto list = pk::get_person_list(pk::get_force(person.get_force_id()), pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반, 신분_포로));
                int curr = list.count;

                dialog = pk::format("인재의 숫자가 곧 국력입니다. 최소 \x1b[2x{}\x1b[0x명 이상의 무장을 모집해야 합니다. \n (현재 : {}명)", sub_count, curr);
            }
            else if (sub == 목표_도시공략)
            {
                pk::city@ target = pk::get_city(sub_con1);
                int city_troops = pk::get_troops(target);
                pk::force@ force = pk::get_force(target.get_force_id());
                string target_force = "";
                
                if (force != null)
                {
                    if (force.kokugou == -1)
                    {
                        target_force = pk::u8decode(pk::get_name(pk::get_person(force.kunshu)));
                    }
                    else
                    {
                        target_force = pk::u8decode(pk::get_kokugou(force.kokugou).get_name());
                    }
                }

                if (force == null)
                {
                    dialog = pk::format("\x1b[2x{}\x1b[0x(은)는 무주공산입니다. 서둘러 아군의 영토로 삼아야 합니다.", pk::u8decode(pk::get_name(target)));
                }
                else
                {
                    if (pk::rand_bool(50))
                    {
                        dialog = pk::format("건방진 \x1b[1x{}\x1b[0x군에게 따끔한 맛을 보여주기 위해 \x1b[2x{}\x1b[0x(을)를 공략해야 합니다. \n\n (\x1b[2x{}\x1b[0x의 병력 : {})", target_force, pk::u8decode(pk::get_name(target)), pk::u8decode(pk::get_name(target)), city_troops);
                    }
                    else
                    {
                        dialog = pk::format("\x1b[2x{}\x1b[0x(을)를 공략할 절호의 기회입니다. 결단을 내려주십시오. \n\n (\x1b[2x{}\x1b[0x의 병력 : {})", pk::u8decode(pk::get_name(target)), pk::u8decode(pk::get_name(target)), city_troops);
                    }
                }
            }
            else if (sub == 목표_도시방비)
            {
                pk::city@ target = pk::get_city(sub_con1);
                dialog = pk::format("\x1b[1x{}\x1b[0x(은)는 아군의 요충지입니다. 적의 공격에 대비하기 위해 방어시설을 \x1b[2x{}\x1b[0x개 이상 건설해야 합니다.", pk::u8decode(pk::get_name(target)), sub_count);
            }
            else if (sub == 목표_세력군비)
            {
                pk::list<pk::building@> list;

                auto all_list = pk::get_building_list();

                for (int i = 0; i < all_list.count; ++i)
                {
                    pk::building@ building = all_list[i];

                    if (building.get_force_id() == person.get_force_id() && (building.get_id() >= 건물_도시시작 && building.get_id() <= 건물_거점끝))
                    {
                        list.add(building);
                    }
                }

                auto building_arr = pk::list_to_array(list);

                int troops = 0;
                int weapons = 0;
                int horses = 0;
                int sieges = 0;
                int ships = 0;

                // 플레이어 소속 거점을 돌면서 병사, 병기 계산
                for (int i = 0; i < building_arr.length; ++i)
                {
                    pk::building@ building = building_arr[i];
                    troops += pk::get_troops(building);
                    weapons += (pk::get_weapon_amount(building, 병기_창) + pk::get_weapon_amount(building, 병기_극) + pk::get_weapon_amount(building, 병기_노));
                    horses += pk::get_weapon_amount(building, 병기_군마);
                    sieges += (pk::get_weapon_amount(building, 병기_충차) + pk::get_weapon_amount(building, 병기_정란) + pk::get_weapon_amount(building, 병기_투석) + pk::get_weapon_amount(building, 병기_목수));
                    ships += (pk::get_weapon_amount(building, 병기_누선) + pk::get_weapon_amount(building, 병기_투함));
                }

                auto unit_arr = pk::list_to_array(pk::get_unit_list(pk::get_force(person.get_force_id())));

                for (int i = 0; i < unit_arr.length; ++i)
                {
                    pk::unit@ unit = unit_arr[i];
                    if (!unit.is_alive())
                        continue;
                    troops += unit.troops;
                    if (unit.type == 부대종류_전투)
                    {
                        int ship = unit.stock[1].id;

                        if (ship == 병기_누선 || ship == 병기_투함)
                        {
                            ships += unit.stock[1].amount;
                        }

                        int weapon = unit.stock[0].id;

                        if (weapon == 병기_창 || weapon == 병기_극 || weapon == 병기_노)
                        {
                            weapons += unit.stock[0].amount;
                        }
                        else if (weapon == 병기_군마)
                        {
                            horses += unit.stock[0].amount;
                        }
                        else if (weapon == 병기_충차 || weapon == 병기_정란 || weapon == 병기_투석 || weapon == 병기_목수)
                        {
                            sieges += unit.stock[0].amount;
                        }
                    }
                    else
                    {
                        weapons += (unit.stock[병기_창].amount + unit.stock[병기_극].amount + unit.stock[병기_노].amount);
                        horses += unit.stock[병기_군마].amount;
                        sieges += (unit.stock[병기_충차].amount + unit.stock[병기_정란].amount + unit.stock[병기_투석].amount + unit.stock[병기_목수].amount);
                        ships += (unit.stock[병기_누선].amount + unit.stock[병기_투함].amount);
                    }
                }

                switch (sub_con1)
                {
                case 창극노:
                    dialog = pk::format("주변의 정세가 심상치 않습니다. 만전을 기해 병사 \x1b[2x{}\x1b[0x명과 \x1b[1x{}\x1b[0x를 도합 \x1b[2x{}\x1b[0x 이상 비축해야 합니다. \n( 현재 병력 : {} )\n( 현재 창극노 : {} )", sub_count * 1000, 병기[sub_con1], sub_count * 1000, troops, weapons);
                    break;

                case 군마:
                    dialog = pk::format("기병을 양성한다면 전투에서 우위를 가져올 수 있습니다. \x1b[1x{}\x1b[0x를 \x1b[2x{}\x1b[0x필 이상 준비해야 합니다. \n( 현재 군마 : {} )", 병기[sub_con1], sub_count * 1000, horses);
                    break;

                case 공성병기:
                    dialog = pk::format("공성전을 대비하기 위해 \x1b[1x{}\x1b[0x를 \x1b[2x{}\x1b[0x개 이상 비축해야 합니다. \n( 현재 공성병기 : {} )", 병기[sub_con1], sub_count, sieges);
                    break;

                case 선박:
                    dialog = pk::format("수상전을 대비하기 위해 \x1b[1x{}\x1b[0x을 \x1b[2x{}\x1b[0x척 이상 비축해야 합니다. \n( 현재 선박 : {} )", 병기[sub_con1], sub_count, ships);
                    break;
                }
            }
            else if (sub == 목표_황제옹립)
            {
                dialog = "\x1b[1x황제\x1b[0x께서 역적의 손아귀에 고통받은지 오래입니다. 어서 폐하를 모셔오도록 합시다.";
            }
            else if (sub == 목표_황제폐위)
            {
                dialog = "\x1b[2x한\x1b[0x나라의 권위는 이미 땅에 떨어진지 오래이며, \x1b[1x황제\x1b[0x는 허수아비에 불과합니다. \x1b[1x황제\x1b[0x를 폐위하고 질서를 바로잡아야 합니다.";
            }
            else if (sub == 목표_작위제수)
            {
                pk::title@ target = pk::get_title(sub_con1);
                if (target.get_id() < 작위_공)
                {
                    dialog = pk::format("주군의 명성과 믿고 따르는 자들을 위해서라도 \x1b[1x{}\x1b[0x에 올라야 한다고 생각합니다.", pk::u8decode(pk::get_name(target)));
                }
                else
                {
                    dialog = pk::format("천하의 대세는 주공을 향하고 있습니다. \x1b[1x{}\x1b[0x에 올라 그 결실을 맺을 때입니다.", pk::u8decode(pk::get_name(target)));
                }
            }
            else if (sub == 목표_기교연구)
            {
                pk::tech@ target = pk::get_tech(sub_con1);
                dialog = pk::format("저희에게는 강력한 기술이 필요합니다. 기교연구 \x1b[1x{}\x1b[0x(을)를 연구해야 합니다.", pk::u8decode(pk::get_name(target)));
            }
            else if (sub == 목표_세력동맹)
            {
                pk::force@ force = pk::get_force(sub_con1);
                string target_force = "";
                if (force.kokugou == -1)
                {
                    target_force = pk::u8decode(pk::get_name(pk::get_person(force.kunshu)));
                }
                else
                {
                    target_force = pk::u8decode(pk::get_kokugou(force.kokugou).get_name());
                }

                dialog = pk::format("현재의 정황으로 살펴보면 \x1b[1x{}\x1b[0x군과의 동맹은 불가피합니다.", target_force);
            }
            else if (sub == 목표_세력친밀)
            {
                pk::force@ force = pk::get_force(sub_con1);
                string target_force = "";
                if (force.kokugou == -1)
                {
                    target_force = pk::u8decode(pk::get_name(pk::get_person(force.kunshu)));
                }
                else
                {
                    target_force = pk::u8decode(pk::get_kokugou(force.kokugou).get_name());
                }

                dialog = pk::format("천하가 안정되지 않았으니 \x1b[1x{}\x1b[0x군과 친밀을 유지해야 합니다.", target_force);
            }
            else if (sub == 목표_본거지_아군)
            {
                dialog = "치안을 강화해서 \x1b[2x본거지\x1b[0x 발생을 억제하는 것이 곧 나라와 백성을 위한 일입니다.";
            }
            else if (sub == 목표_본거지_적군)
            {
                pk::city@ city = pk::get_city(sub_con1);
                pk::force@ force = pk::get_force(city.get_force_id());
                string target_force = "";
                if (force.kokugou == -1)
                {
                    target_force = pk::u8decode(pk::get_name(pk::get_person(force.kunshu)));
                }
                else
                {
                    target_force = pk::u8decode(pk::get_kokugou(force.kokugou).get_name());
                }

                dialog = pk::format("\x1b[1x{}\x1b[0x의 민심이 흉흉하다고 합니다. \x1b[2x본거지\x1b[0x를 발생시켜 \x1b[1x{}\x1b[0x군에게 피해를 주고 싶습니다.", pk::u8decode(pk::get_name(city)), target_force);
            }
            else if (sub == 목표_구호탄랑)
            {
                pk::force@ force = pk::get_force(sub_con1);
                string target_force = "";
                if (force.kokugou == -1)
                {
                    target_force = pk::u8decode(pk::get_name(pk::get_person(force.kunshu)));
                }
                else
                {
                    target_force = pk::u8decode(pk::get_kokugou(force.kokugou).get_name());
                }

                dialog = pk::format("\x1b[1x{}\x1b[0x군에는 그놈과 사이가 나쁜 사람이 있다는 소문입니다. \x1b[2x구호탄랑계\x1b[0x를 사용합시다.", target_force);
            }
            else if (sub == 목표_동작대)
            {
                dialog = "주공의 위엄과 저희군의 위세를 드러내기 위해서 \x1b[2x동작대\x1b[0x를 건축하는것이 어떻습니까.";
            }
            else if (sub == 목표_동조)
            {
                pk::person@ target = pk::get_person(sub_con1);
                dialog = pk::format("\x1b[1x{}\x1b[0x님의 의견은 정말 그 말대로라고 생각합니다.", pk::u8decode(pk::get_name(target)));
            }
            else if (sub == 목표_고갈)
            {
                dialog = "현 상황에서는 마땅한 계책이 없어보입니다.";
            }
            else if (sub == 목표_없음)
            {
                
                dialog = "으으.. 도무지 생각이 나지 않습니다. (연회 자리에나 부를 것이지..)";
            }
        }
        void clear()
        {
            @speaker = null;
            opinion.clear();
            dialog = "";
        }
    };

    class Main
    {
        array<pk::point> data_point = { 목표상태_좌표, 목표_좌표, 목표조건1_좌표, 목표조건2_좌표, 목표수치_좌표, 목표보상_좌표, 목표제안무장_좌표 };
        pk::person@ kunshu = null;
        pk::person@ gunshi = null;
        pk::force@ player_force = null;
        
        pk::array<Proposal> participants(6);
        array<Opinion> opinion_array(목표_끝);
        //array<int> opinion_subject_array = {-1, -1, -1, -1, -1, -1};    // 중복 의견을 막기위한 배열    
        string title = "";
        string descript = "";

        array<pk::building@> data_array(7);    // 데이터를 처리할 건물 5개 ==> 7개로 늘려야할듯 (제안자, 보상등급)  
        Main()
        {
            add_subject_confirm_menu();
            add_subject_renew_menu();           // 테스트 용도의 메뉴 (회의를 강제로 갱신한다)

            pk::bind(102, pk::trigger102_t(init));
            pk::bind(103, pk::trigger103_t(awake));
            pk::bind(107, pk::trigger107_t(update_mission));                    // 달성한 순간에 진행이 끝나는 목표 체크
            pk::bind(110, pk::trigger110_t(new_year_plan));                     // 매년 회의 개최여부
        }

        // 게임 실행시 회의 스크립트 사용여부 확인. 건물이 없을경우 새로 생성
        void init()
        {
            for (int i = 0; i < participants.length; ++i)
            {
                participants[i].clear();
            }

            for (int i = 0; i < data_array.length; ++i)
            {
                @data_array[i] = pk::get_building(data_point[i]);

                if (data_array[i] == null)
                {
                    @data_array[i] = pk::create_building(pk::get_facility(시설_석벽), data_point[i], -1);
                    data_array[i].hp = -1;
                }
            }
        }

        void awake()
        {
            set_player_force();

            if (pk::get_scenario().loaded)
            {
                set_mission_window();
                display_mission();
                return;
            }
            else
            {
                // 회의 개최 선택
                pk::scene(pk::scene_t(choose_conference));
                display_mission();
            }
        }

        void new_year_plan()
        {
            if (pk::get_elapsed_days() <= 10)
            {
                return;
            }

            // 이전 회의 정산        
            pk::scene(pk::scene_t(orginize_conference_scene));
            // 회의 개최 선택
            pk::scene(pk::scene_t(choose_conference));
            display_mission();
        }
        
        // 목표를 수행할 플레이어 세력 세팅
        void set_player_force()
        {
            @player_force = null;
            @kunshu = null; 
            @gunshi = null;

            auto force_array = pk::list_to_array(pk::get_force_list());

            for (int i = 0; i < force_array.length; ++i)
            {
                pk::force@ force = force_array[i];

                if (force.is_alive() && force.is_player())
                {
                    @player_force = force;
                    @kunshu = pk::get_person(force.kunshu);
                    @gunshi = pk::get_person(force.gunshi);
                }
            }
        }

        void update_mission()
        {
            if (get_subject_data(목표) == 목표_본거지_적군)
            {
                if (get_subject_data(목표상태) == 목표_진행)
                {
                    if (check_condition())
                        data_array[목표상태].hp = 목표_달성;
                }
            }
            else if (get_subject_data(목표) == 목표_본거지_아군)
            {
                if (get_subject_data(목표상태) == 목표_진행)
                {
                    if (!check_condition())
                        data_array[목표상태].hp = 목표_실패;
                }
            }
        }

        void choose_conference()
        {
            set_player_force();

            if (!player_force.is_alive())
                return;

            if (!kunshu.is_alive())
                return;

            auto valid_list = pk::get_person_list(player_force, pk::mibun_flags(신분_도독, 신분_태수, 신분_일반));
            // 부하무장이 4명 미만인 경우 개최 불가
            if (valid_list.count < 회의개최_최소인원 || valid_list.count <= 0)
            {
                return;
            }

            int choose;
            
            if (pk::get_elapsed_days() <= 0)
            {
                bool is_possible = false;

                if (gunshi == null)
                {
                    valid_list.sort(function(a, b)
                    {
                        return (a.stat[무장능력_지력] > b.stat[무장능력_지력]); // 무장 정렬 (지력순)
                    });

                    if (valid_list[0].stat[무장능력_지력] >= 80)
                        is_possible = true;

                    if (is_possible)
                        choose = pk::choose(choose_conference_hold_array, pk::u8encode("본격적인 통치에 앞서 회의를 열어 무장들의 의견을 들어보시겠습니까?"), valid_list[0]);
                }
                else
                {
                    choose = pk::choose(choose_conference_hold_array, pk::u8encode("본격적인 통치에 앞서 회의를 열어 무장들의 의견을 들어보시겠습니까?"), gunshi);
                }
            }
            else
            {
                if (gunshi == null)
                    return;

                choose = pk::choose(choose_conference_hold_array, pk::u8encode("새해가 밝았습니다. 회의를 열어 무장들의 의견에 귀를 기울이시지요."), gunshi);
            }

            if (choose == 회의_개최)
            {
                pk::list<pk::person@> person_sel = pk::person_selector(pk::u8encode("무장 선택"), pk::u8encode("회의에 참석할 무장을 선택합니다."), valid_list, 회의개최_최소인원, 6);

                if (person_sel.count < 회의개최_최소인원)
                {
                    pk::message_box(pk::u8encode("무장을 선택을 취소했습니다. 이전 선택으로 돌아갑니다."));
                    choose_conference();
                }
                else
                {
                    pk::list<pk::building@> list;

                    auto all_list = pk::get_building_list();

                    for (int i = 0; i < all_list.count; ++i)
                    {
                        pk::building@ building = all_list[i];

                        if (building.get_force_id() == player_force.get_force_id() && (building.get_id() >= 건물_도시시작 && building.get_id() <= 건물_거점끝))
                        {
                            list.add(building);
                        }
                    }

                    auto building_arr = pk::list_to_array(list);

                    int troops = 0;
                    int weapons = 0;
                    int horses = 0;
                    int sieges = 0;
                    int ships = 0;

                    // 플레이어 소속 거점을 돌면서 병사, 병기 계산
                    for (int i = 0; i < building_arr.length; ++i)
                    {
                        pk::building@ building = building_arr[i];
                        troops += pk::get_troops(building);
                        weapons += (pk::get_weapon_amount(building, 병기_창) + pk::get_weapon_amount(building, 병기_극) + pk::get_weapon_amount(building, 병기_노));
                        horses += pk::get_weapon_amount(building, 병기_군마);
                        sieges += (pk::get_weapon_amount(building, 병기_충차) + pk::get_weapon_amount(building, 병기_정란) + pk::get_weapon_amount(building, 병기_투석) + pk::get_weapon_amount(building, 병기_목수));
                        ships += (pk::get_weapon_amount(building, 병기_누선) + pk::get_weapon_amount(building, 병기_투함));
                    }

                    auto unit_arr = pk::list_to_array(pk::get_unit_list(player_force));

                    for (int i = 0; i < unit_arr.length; ++i)
                    {
                        pk::unit@ unit = unit_arr[i];
                        if (!unit.is_alive())
                            continue;

                        troops += unit.troops;
                        if (unit.type == 부대종류_전투)
                        {
                            int ship = unit.stock[1].id;

                            if (ship == 병기_누선 || ship == 병기_투함)
                            {
                                ships += unit.stock[1].amount;
                            }

                            int weapon = unit.stock[0].id;

                            if (weapon == 병기_창 || weapon == 병기_극 || weapon == 병기_노)
                            {
                                weapons += unit.stock[0].amount;
                            }
                            else if (weapon == 병기_군마)
                            {
                                horses += unit.stock[0].amount;
                            }
                            else if (weapon == 병기_충차 || weapon == 병기_정란 || weapon == 병기_투석 || weapon == 병기_목수)
                            {
                                sieges += unit.stock[0].amount;
                            }
                        }
                        else
                        {
                            weapons += (unit.stock[병기_창].amount + unit.stock[병기_극].amount + unit.stock[병기_노].amount);
                            horses += unit.stock[병기_군마].amount;
                            sieges += (unit.stock[병기_충차].amount + unit.stock[병기_정란].amount + unit.stock[병기_투석].amount + unit.stock[병기_목수].amount);
                            ships += (unit.stock[병기_누선].amount + unit.stock[병기_투함].amount);
                        }
                    }

                    for (int i = 0; i < person_sel.count; ++i)
                    {
                        make_opinion(person_sel[i], troops, weapons, horses, sieges, ships, i);
                    }

                    //pk::scene(pk::scene_t(conference_scene));
                    conference_scene();
                }
            }
        }

        // 참석자의 의견을 생성하는 함수
        void make_opinion(pk::person@ person, int total_troops, int total_weapons, int total_horses, int total_sieges, int total_ships, int index)
        {
            for (int i = 0; i < opinion_array.length; ++i)
            {
                opinion_array[i].clear();
            }
            
            int 통솔 = person.stat[무장능력_통솔];
            int 무력 = person.stat[무장능력_무력];
            int 지력 = person.stat[무장능력_지력];
            int 정치 = person.stat[무장능력_정치];
            int 매력 = person.stat[무장능력_매력];
            int 통무 = 통솔 + 무력;
            int 통지 = 통솔 + 지력;
            int 통정 = 통솔 + 정치;
            int 통매 = 통솔 + 매력;
            int 무지 = 무력 + 지력;
            int 무정 = 무력 + 정치;
            int 무매 = 무력 + 매력;
            int 지정 = 지력 + 정치;
            int 지매 = 지력 + 매력;
            int 정매 = 정치 + 매력;
            int 총합 = 통솔 + 무력 + 지력 + 정치 + 매력;
            
            bool 능력치_2개_80이상 = false;
            int stat_count = 0;
            for (int i = 0; i < 5; ++i)
            {
                if (person.stat[i] >= 80)
                {
                    stat_count += 1;
                }

                if (stat_count >= 2)
                {
                    능력치_2개_80이상 = true;
                    break;
                }
            }

            int count = 0;
            // 능력치에 따라서 안건의 종류가 달라진다.
            // 야망, 의리, 한실

            // 보물수집 체크.  발언조건 : 강탈 혹은 포박 무장이거나  무력이 80 이상이고 의리가 낮음 이하인 무장
            int 의리 = person.giri;
            if (person.skill == 특기_강탈 || person.skill == 특기_포박 || (무력 >= 80 && 의리 <= 의리_낮음))
            {
                int i = pk::rand(100);

                if (i == 보물_옥새)
                {
                    i = i - 1 - pk::rand(41);
                }
                else if (i == 보물_동작)
                {
                    i = i + 1 + pk::rand(57);
                }

                pk::item@ item = pk::get_item(i);
                pk::person@ owner = pk::get_person(item.owner);
                
                // 아이템이 존재하면서 파기된 보물이 아닌 경우
                if (item != null && item.status != 보물상태_파기)
                {
                    // 주인이 없거나
                    if (owner == null)
                    {
                        opinion_array[count].set_opinion(목표_보물수집, i, -1, -1, 3);
                        count += 1;
                    }
                    else
                    {
                        // 아이템 소유자가 플레이어와 같은 세력이 아닌 경우 해당 발언자의 의견 목록에 추가시킨다
                        if (owner.get_force_id() != player_force.get_force_id())
                        {
                            opinion_array[count].set_opinion(목표_보물수집, i, -1, -1, 3);
                            count += 1;
                        }
                    }
                }
            }

            pk::person@ dislike = null;

            // 무장처단 체크. 발언조건 : 무장의 무력 80이상 지력 50미만일때 타국 혐오무장이 존재할 경우. 
            //                   또는 지력 80이상 매력 60미만일때 타국 혐오무장의 총 능력치 합이 300 이상인 경우.
            
            if (pk::get_num_dislikes(person) > 0)
            {
                if (무력 >= 80 && 지력 < 50)
                {
                    for (int i = 0; i < 5; ++i)
                    {
                        pk::person@ temp = pk::get_person(person.disliked[i]);

                        if (temp == null)
                        {
                            continue;
                        }

                        if (!temp.is_alive())
                        {
                            continue;
                        }

                        if (temp.get_force_id() == player_force.get_force_id())
                        {
                            continue;
                        }

                        @dislike = temp;
                    }
                }
                else if (지력 >= 80 && 매력 < 60)
                {
                    for (int i = 0; i < 5; ++i)
                    {
                        pk::person@ temp = pk::get_person(person.disliked[i]);

                        if (temp == null)
                        {
                            continue;
                        }

                        if (!temp.is_alive())
                        {
                            continue;
                        }

                        if (temp.get_force_id() == player_force.get_force_id())
                        {
                            continue;
                        }

                        if ((temp.stat[무장능력_통솔] + temp.stat[무장능력_무력] + temp.stat[무장능력_지력] + temp.stat[무장능력_정치] + temp.stat[무장능력_매력]) < 300)
                        {
                            continue;
                        }

                        @dislike = temp;
                    }
                }

                if (dislike != null)
                {
                    opinion_array[count].set_opinion(목표_무장처단, dislike.get_id(), -1, -1, 3);
                    count += 1;
                }
            }


            pk::person@ recruit_target = null;

            // 특정무장 체크.  발언조건 : 제안자의 정치가 90 이상이거나 안력 특기보유일 경우에 등용 가능한 재야가 세력내에 있을경우
            if (정치 >= 90 || person.skill == 특기_안력)
            {
                auto person_array = pk::list_to_array(pk::get_person_list(pk::mibun_flags(신분_재야, 신분_미발견)));
                
                if (person_array.length > 0)
                {
                    pk::list<pk::person@> target_list;

                    for (int i = 0; i < person_array.length; ++i)
                    {
                        pk::person@ target = person_array[i];

                        // 사망상태인 경우 패스
                        if (!target.is_alive())
                            continue;

                        // 타깃이 플레이어 군주를 혐오할 경우 패스
                        if (pk::is_dislike(target, kunshu.get_id()))
                            continue;
                        
                        // 반대의 경우에도 패스
                        if (pk::is_dislike(kunshu, target.get_id()))
                            continue;

                        pk::building@ building = pk::get_building(target.service);

                        // 플레이어 거점에 소속한 경우 타깃 리스트에 등재
                        if (building.get_force_id() == player_force.get_force_id())
                        {
                            target_list.add(target);
                        }
                    }

                    if (target_list.count > 0)
                    {
                        // 리스트 중에 한명을 랜덤하게 선택
                        int r = pk::rand(target_list.count);

                        @recruit_target = target_list[r];
                        opinion_array[count].set_opinion(목표_특정무장, recruit_target.get_id(), -1, 1, 1);
                        count += 1;
                    }
                }
            }

            // 또는 정치가 80 이상인 무장인 경우
            if (정치 >= 80 && recruit_target == null)
            {
                auto person_array = pk::list_to_array(pk::get_person_list(pk::mibun_flags(신분_도독, 신분_태수, 신분_일반)));
                pk::list<pk::person@> target_list;

                // 등용 불가능한 무장 거르기
                for (int i = 0; i < person_array.length; ++i)
                {
                    pk::person@ target = person_array[i];

                    // 타깃이 사망한 경우 패스
                    if (!target.is_alive())
                        continue;

                    // 충성도가 90 이상인 경우도 패스
                    if (target.loyalty >= 90)
                        continue;

                    // 플레이어 소속 무장인 경우 패스
                    if (target.get_force_id() == player_force.get_force_id())
                        continue;

                    // 타깃이 플레이어 군주를 혐오할 경우 패스
                    if (pk::is_dislike(target, kunshu.get_id()))
                        continue;

                    // 반대의 경우에도 패스
                    if (pk::is_dislike(kunshu, target.get_id()))
                        continue;

                    target_list.add(target);
                }

                if (target_list.count > 0)
                {
                    // 리스트 중에 한명을 랜덤하게 선택
                    int r = pk::rand(target_list.count);

                    @recruit_target = target_list[r];
                    opinion_array[count].set_opinion(목표_특정무장, recruit_target.get_id(), -1, 1, 3);
                    count += 1;
                }
            }

            // 특기, 능력, 전체 무장 체크.  발언조건 : 무장능력치 2개 이상이 80이상인 경우
            if (능력치_2개_80이상)
            {
                auto list = pk::get_person_list(player_force, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반, 신분_포로));
                pk::array<pk::person@> person_array = pk::list_to_array(list);
                // 랜덤하게 발언 조건을 결정
                int r = pk::rand(10000) % 3;

                // 특기무장
                if (r == 0)
                {
                    pk::skill@ skill = pk::get_skill(pk::rand(10000) % 100);
                    bool has_skill = false;
                    // 행군, 공격, 방어, 계략, 보조, 내정계 특기만 제안함
                    if (skill.type < 특기종류_수입)
                    {
                        for (int i = 0; i < person_array.length; ++i)
                        {
                            if (person_array[i].skill == skill.get_id())
                            {
                                has_skill = true;
                                break;
                            }
                        }
                        // 세력내에 보유자가 없을 경우만 제안
                        if (!has_skill)
                        {
                            opinion_array[count].set_opinion(목표_특기무장, skill.get_id(), -1, 1, 2);
                            count += 1;
                        }
                    }
                }
                // 능력무장
                else if (r == 1)
                {
                    // 제안할 무장의 능력치 종류(랜덤)
                    int random_stat = pk::rand(10000) % 5;
                    int c = 0;

                    for (int i = 0; i < person_array.length; ++i)
                    {
                        pk::person@ stat_person = person_array[i];

                        if (stat_person.stat[random_stat] >= 90)
                            c = c + 1;
                    }

                    if (c >= 12)
                    {

                    }
                    else if (c >= 9)
                    {
                        opinion_array[count].set_opinion(목표_능력무장, random_stat, 90, 12, 12 - c);
                        count += 1;
                    }
                    else if (c >= 6)
                    {
                        opinion_array[count].set_opinion(목표_능력무장, random_stat, 90, 9, 9 - c);
                        count += 1;
                    }
                    else if (c >= 3)
                    {
                        opinion_array[count].set_opinion(목표_능력무장, random_stat, 90, 6, 6 - c);
                        count += 1;
                    }
                    else if (c > 0)
                    {
                        opinion_array[count].set_opinion(목표_능력무장, random_stat, 90, 3, 3 - c);
                        count += 1;
                    }
                    else
                    {
                        opinion_array[count].set_opinion(목표_능력무장, random_stat, 90, 1, 2);
                        count += 1;
                    }
                }
                // 전체무장
                else
                {
                    int c = list.count;

                    if (c >= 300)
                    {
                       
                    }
                    else if (c >= 200)
                    {
                        opinion_array[count].set_opinion(목표_전체무장, -1, -1, 300, 2 - ((c - 200) / 50));
                        count += 1;
                    }
                    else if (c >= 150)
                    {
                        opinion_array[count].set_opinion(목표_전체무장, -1, -1, 200, 2 - ((c - 150) / 25));
                        count += 1;
                    }
                    else if (c >= 100)
                    {
                        opinion_array[count].set_opinion(목표_전체무장, -1, -1, 150, 2 - ((c - 100) / 25));
                        count += 1;
                    }
                    else if (c >= 70)
                    {
                        opinion_array[count].set_opinion(목표_전체무장, -1, -1, 100, 2 - ((c - 70) / 15));
                        count += 1;
                    }
                    else if (c >= 50)
                    {
                        opinion_array[count].set_opinion(목표_전체무장, -1, -1, 70, 2 - ((c - 50) / 10));
                        count += 1;
                    }
                    else if (c >= 30)
                    {
                        opinion_array[count].set_opinion(목표_전체무장, -1, -1, 50, 2 - ((c - 30) / 10));
                        count += 1;
                    }
                    else if (c >= 10)
                    {
                        opinion_array[count].set_opinion(목표_전체무장, -1, -1, 30, 2 - ((c - 10) / 10));
                        count += 1;
                    }
                    else
                    {
                        opinion_array[count].set_opinion(목표_전체무장, -1, -1, 10, 2 - (c / 5));
                        count += 1;
                    }
                }
            }

            // 도시공략 체크. 발언조건 :  통무 합 160 이상
            if (통무 >= 160)
            {
                pk::city@ target = get_random_enemy_neighbor_city();

                if (target != null)
                {
                    opinion_array[count].set_opinion(목표_도시공략, target.get_id(), -1, -1, 2);
                    count += 1;
                }
            }

            // 도시방비 체크. 발언조건 : 정매 합 160 이상
            if (정매 >= 160)
            {
                pk::city@ target = get_random_player_neighbor_city();

                if (target != null)
                {
                    opinion_array[count].set_opinion(목표_도시방비, target.get_id(), -1, 8, 2);
                    count += 1;
                }
            }

            // 세력군비 체크. 발언조건 : 통지 또는 무지 합 160 이상. 도시 10개 이하인 경우에만 발생
            if (통지 >= 160 || 무지 >= 160)
            {
                int city_count = pk::get_city_count(player_force);

                if (city_count <= 10)
                {
                    int r = pk::rand(10000) % 4;

                    switch (r)
                    {
                    case 창극노:
                        if (total_weapons <= 20000 * city_count || total_troops <= 20000 * city_count)
                        {
                            opinion_array[count].set_opinion(목표_세력군비, 창극노, -1, 40 * city_count, 1);
                            count += 1;
                        }
                        break;

                    case 군마:
                        if (total_horses <= 20000 * city_count)
                        {
                            opinion_array[count].set_opinion(목표_세력군비, 군마, -1, 40 * city_count, 1);
                            count += 1;
                        }
                        break;

                    case 공성병기:
                        if (total_sieges <= 2 * city_count)
                        {
                            opinion_array[count].set_opinion(목표_세력군비, 공성병기, -1, 4 * city_count, 2);
                            count += 1;
                        }
                        break;

                    case 선박:
                        if (total_ships <= 2 * city_count)
                        {
                            opinion_array[count].set_opinion(목표_세력군비, 선박, -1, 4 * city_count, 2);
                            count += 1;
                        }
                        break;
                    }
                }
            }
            
            int 한실 = person.kanshitsu;
            // 황제옹립 체크.  발언조건 : 매력이 80 이상, 한실중시인 경우
            if (매력 >= 90 && 한실 == 한실_중시 && player_force.kokugou != 국호_황건)
            {
                pk::person@ emperor = pk::get_person(pk::get_scenario().emperor);

                // 황제가 죽었거나 없을 경우 패스
                if (null == emperor)
                {
                   
                }
                else if (emperor.mibun == 신분_사망)
                {
                   
                }
                else
                {
                    if (!pk::is_protecting_the_emperor(player_force))
                    {
                        opinion_array[count].set_opinion(목표_황제옹립, -1, -1, -1, 3);
                        count += 1;
                    }
                }
            }

            // 황제폐위 체크. 발언조건 : 제안자가 한실무시이며 통솔과 지력이 160 이상인 경우, 군주가 한실무시 혹은 황건 세력일때

            if (통지 >= 160 && 한실 == 한실_무시 && (player_force.kokugou == 국호_황건 || kunshu.kanshitsu == 한실_무시))
            {
                pk::person@ emperor = pk::get_person(pk::get_scenario().emperor);

                if (null == emperor)
                {

                }
                else if (emperor.mibun == 신분_사망)
                {

                }
                else
                {
                    if (!pk::is_protecting_the_emperor(player_force))
                    {
                        opinion_array[count].set_opinion(목표_황제폐위, -1, -1, -1, 3);
                        count += 1;
                    }
                }
            }

            int 야망 = person.ambition;

            // 작위제수 체크. 발언조건 : 80인 이상인 능력치가 있으면서 야망이 높음 이상인 경우. 
            //                         대사마 미만일 경우에는 해당조건만 만족
            //                         대사마 부터는 한실 무시인 경우에만
            //                         황건의 경우 나타나지 않음
            if (야망 >= 야망_높음 && (통솔 >= 80 || 무력 >= 80 || 지력 >= 80 || 정치 >= 80 || 매력 >= 80))
            {
                int title = player_force.title;

                if (title != 작위_황제 || player_force.kokugou != 국호_황건)
                {
                    if (title > 작위_대사마)
                    {
                        opinion_array[count].set_opinion(목표_작위제수, title - 1, -1, -1, 2);
                        count += 1;
                    }
                    else
                    {
                        int city_count = pk::get_city_count(player_force);

                        if (city_count >= 10)
                        {
                            if (한실 == 한실_무시)
                            {
                                opinion_array[count].set_opinion(목표_작위제수, title - 1, -1, -1, 3);
                                count += 1;
                            }
                        }
                    }
                }
            }

            // 기교연구 체크. 발언조건 : 능력치 중 2개가 80 이상인 무장. 연구중이 아닌 연구 가능한 기교를 제안
            if (능력치_2개_80이상)
            {
                int r = pk::rand(10000) % 9; // (0 ~ 8)
                int tech;
                for (int i = 0; i < 4; ++i)
                {
                    tech = i + 4 * r;
                    // 연구가 안됐고, 연구중이 아닌 기교인 경우
                    if (!player_force.tech[tech] && player_force.researching_tech != tech)
                    {
                        opinion_array[count].set_opinion(목표_기교연구, tech , -1, -1, pk::max(1, i));
                        count += 1;
                        break;
                    }
                }
            }

            // 세력동맹, 세력친밀 체크. 발언조건 : 지력 정치 합이 160 이상인 무장. 인접하지 않은 동맹이 아닌 국가의 경우
            if (지정 >= 160)
            {
                auto list = pk::get_force_list();

                list.shuffle();

                for (int i = 0; i < list.count; ++i)
                {
                    pk::force@ target = list[i];

                    // 일반적인 세력이 아닌경우 패스
                    if (!pk::is_normal_force(target))
                        continue;

                    // 유저세력인 경우 패스
                    if (target.get_force_id() == player_force.get_force_id())
                        continue;

                    // 이미 동맹인 경우 패스
                    if (player_force.ally[target.get_force_id()])
                        continue;

                    // 인접한 도시가 있는경우 패스
                    if (pk::is_neighbor_force(target, player_force))
                        continue;

                    // 친밀도가 40 이상인 경우 동맹
                    if (player_force.relations[target.get_force_id()] >= 40)
                    {
                        opinion_array[count].set_opinion(목표_세력동맹, target.get_force_id(), -1, -1, 2);
                        count += 1;
                        break;
                    }
                    // 이하인 경우는 친밀을 목표로
                    else
                    {
                        opinion_array[count].set_opinion(목표_세력친밀, target.get_force_id(), -1, -1, 2);
                        count += 1;
                        break;
                    }
                }
            }

            // 본거지 아군 체크. 발언조건 : 매력이 90 이상인 무장. 현재 세력에 본거지가 존재하지 않을 경우
            if (매력 >= 90)
            {
                bool is_satisfy = true;
                
                array<pk::building@> building_arr = pk::list_to_array(pk::get_building_list());

                for (int i = 0; i < building_arr.length; ++i)
                {
                    pk::building@ building = building_arr[i];

                    if (building.facility == 시설_본거지1 || building.facility == 시설_본거지2)
                    {
                        pk::city@ city = pk::get_city(pk::get_city_id(building.get_pos()));

                        if (city.get_force_id() == player_force.get_force_id())
                        {
                            is_satisfy = false;
                            break;
                        }
                    }
                }

                if (is_satisfy)
                {
                    opinion_array[count].set_opinion(목표_본거지_아군, player_force.get_force_id(), -1, -1, 1);
                    count += 1;
                }
            }

            // 본거지 적군 체크. 발언조건 : 지력이 90 이상인 무장. 현재 본거지가 없는 치안 90이하의 인접한 플레이어 세력 및 공백이 아닌 도시
            if (지력 >= 90)
            {
                auto list = get_enemy_neighbor_city_list();
                pk::list<pk::city@> stronghold_list;
                pk::list<pk::city@> valid_list;

                if (list.count != 0)
                {
                    array<pk::building@> building_arr = pk::list_to_array(pk::get_building_list());

                    for (int i = 0; i < building_arr.length; ++i)
                    {
                        pk::building@ building = building_arr[i];

                        if (building.facility == 시설_본거지1 || building.facility == 시설_본거지2)
                        {
                            pk::city@ city = pk::get_city(pk::get_city_id(building.get_pos()));

                            stronghold_list.add(city);
                        }
                    }

                    for (int i = 0; i < list.count; ++i)
                    {
                        pk::city@ city = list[i];

                        if (stronghold_list.count == 0 && city.public_order <= 90)
                        {
                            valid_list.add(city);
                        }
                        else if(!stronghold_list.contains(city) && city.public_order <= 90)
                        {
                            valid_list.add(city);
                        }
                    }

                    if (valid_list.count > 0)
                    {
                        int r = pk::rand(10000) % valid_list.count;

                        opinion_array[count].set_opinion(목표_본거지_적군, valid_list[r].get_id(), -1, -1, 2);
                        count += 1;
                    }
                }
            }

            // 동작대 체크.  발언조건 : 지력 정치 합이 180 이상인 무장. 동작대가 플레이어 소유, 혹은 미발견이면서 업 포함 9개 이상의 도시 소유인 경우 (동작 이벤트는 도시 10개 라고 합니다)
            if (지정 >= 180)
            {
                pk::item@ item = pk::get_item(보물_동작);
                pk::person@ owner = pk::get_person(item.owner);
                
                // 보물이 파기되지 않았고
                if (item.status != 보물상태_파기)
                {
                    // 보물 소유자가 없는 상태에서
                    if (owner == null)
                    {
                        // 플레이어가 업을 포함한 9개 이상의 도시를 소유한 경우
                        if (owner == null && pk::get_city(도시_업).get_force_id() == player_force.get_force_id() && pk::get_city_count(player_force) >= 9)
                        {
                            opinion_array[count].set_opinion(목표_동작대, -1, -1, -1, 2);
                            count += 1;
                        }
                    }
                    else
                    {
                        // 소유자가 플레이어거나
                        if (owner.get_force_id() == player_force.get_force_id())
                        {
                            opinion_array[count].set_opinion(목표_동작대, -1, -1, -1, 1);
                            count += 1;
                        }
                    }
                }
            }

            // 동조 체크. 발언조건 : 70이 넘는 능력치가 있거나 모든 능력치 합 300 이상인 경우, 앞선 순번의 발언자의 의견이 존재할 경우에 한함(목표 없음 또는 목표 고갈은 동조 하지 못함)
            //                      능력치가 부족한 경우에는 동조하지 못하고 목표_없음 으로 간다. 능력치가 괜찮지만 동조할 의견이 없는 경우는 목표_고갈 로 간다.
            if (count == 0)
            {
                int same_opinion = -1;
                //array<int> valid_opinion_arr(6);
                for (int i = 0; i < index; ++i)
                {
                    // 목표가 없는 무장의 동조를 방지
                    if (participants[i].opinion.subject == 목표_없음 || participants[i].opinion.subject == 목표_동조 || participants[i].opinion.subject == 목표_고갈)
                    {
                        continue;
                    }

                    same_opinion = i;
                }
            
                if (통솔 >= 70 || 무력 >= 70 || 지력 >= 70 || 정치 >= 70 || 매력 >= 70)
                {
                    if (same_opinion == -1)
                    {
                        opinion_array[count].set_opinion(목표_고갈, -1, -1, -1, -1);
                        count += 1;
                    }
                    else
                    {
                        opinion_array[count].set_opinion(목표_동조, participants[same_opinion].speaker.get_id(), -1, -1, -1);
                        count += 1;
                    }
                }
                else if (통솔 + 무력 + 지력 + 정치 + 매력 >= 300)
                {
                    if (same_opinion == -1)
                    {
                        opinion_array[count].set_opinion(목표_고갈, -1, -1, -1, -1);
                        count += 1;
                    }
                    else
                    {
                        opinion_array[count].set_opinion(목표_동조, participants[same_opinion].speaker.get_id(), -1, -1, -1);
                        count += 1;
                    }
                }
                else
                {
                    opinion_array[count].set_opinion(목표_없음, -1, -1, -1, -1);
                    count += 1;
                }
            }
            
            // 최종적으로 의견 생성
            int random_opinion;
            
            if (count > 1)
            {
                random_opinion = pk::rand(10000) % count;
            }
            else
            {
                random_opinion = 0;
            }
            
            int selected_subject = opinion_array[random_opinion].subject;


            if (selected_subject == 목표_없음 || selected_subject == 목표_고갈)
            {
                participants[index].set_proposal(person, opinion_array[random_opinion].subject, -1,-1, -1, -1);
            }
            else if (selected_subject == 목표_동조)
            {
                //int target_id = participants[opinion_array[random_opinion].subject_condition1].speaker.get_id();
                
                participants[index].set_proposal(person, opinion_array[random_opinion].subject, opinion_array[random_opinion].subject_condition1, -1, -1, -1);

                //opinion_subject_array[index] = 목표_동조;
            }
            else
            {
                int check = -1;
                int target_id = -1;

                for (int i = 0; i < index; ++i)
                {
                    if (participants[i].opinion.subject == selected_subject)
                    {
                        check = selected_subject;
                        target_id = participants[i].speaker.get_id();
                        break;
                    }
                }

                if (check == -1)
                {
                    participants[index].set_proposal(person, opinion_array[random_opinion].subject, opinion_array[random_opinion].subject_condition1,
                        opinion_array[random_opinion].subject_condition2, opinion_array[random_opinion].subject_count, opinion_array[random_opinion].subject_level);

                    //opinion_subject_array[index] = opinion_array[random_opinion].subject;
                }
                else
                {
                    participants[index].set_proposal(person, 목표_동조, target_id, -1, -1, -1);

                    //opinion_subject_array[index] = 목표_동조;
                }
            }
        }

        void conference_scene()
        {
            pk::council(kunshu, participants[0].speaker, participants[1].speaker,
                participants[2].speaker, participants[3].speaker, participants[4].speaker, participants[5].speaker, pk::council_t(conference));
        }
        
        void orginize_conference_scene()
        {
            if (get_subject_data(목표상태) == 목표_없음)
                return;

            pk::council(kunshu, pk::get_person(무장_문관), pk::get_person(무장_문관),
                pk::get_person(무장_무관), pk::get_person(무장_무관), null, null, pk::council_t(subject_orginize));
        }

        void subject_orginize()
        {
            pk::wait(1000);
            // 성공 10, 실패 13
            if (get_subject_data(목표상태) == 목표_없음)
            {
                reset();
                return;
            }
            else if (get_subject_data(목표상태) == 목표_실패)
            {
                pk::play_se(13);
                pk::message_box(pk::u8encode("유감스럽게도 작년의 목표를 달성하지 못했소.."), kunshu);
                get_penalty();
            }
            else if (get_subject_data(목표상태) == 목표_달성)
            {
                pk::play_se(10);
                pk::message_box(pk::u8encode("모두들 잘해 주었소! 작년의 목표를 달성했소."), kunshu);
                receive_reward();
            }
            else
            {
                if (check_condition())
                {
                    pk::play_se(10);
                    pk::message_box(pk::u8encode("모두들 잘해 주었소! 작년의 목표를 달성했소."), kunshu);
                    receive_reward();
                }
                else
                {
                    pk::play_se(13);
                    pk::message_box(pk::u8encode("유감스럽게도 작년의 목표를 달성하지 못했소.."), kunshu);
                    get_penalty();
                }
            }

            reset();
        }

        void receive_reward()
        {
            int level = get_subject_data(목표보상);
            
            int loyalty = 달성보상_충성도[level - 1];
            int	kouseki = 달성보상_공적[level - 1];

            // 군주와 포로를 제외한 부하들의 리스트
            array<pk::person@> moo_array = pk::list_to_array(pk::get_person_list(player_force, pk::mibun_flags(신분_도독, 신분_태수, 신분_일반)));

            for (int i = 0; i < moo_array.length; ++i)
            {
                pk::add_loyalty(moo_array[i], loyalty);
            }

            pk::person@ proposer = pk::get_person(get_subject_data(목표제안무장));

            if (!보상_선택가능)
            {
                int tp = 1000 * 2 * level;

                if (proposer.is_alive() && proposer.get_force_id() == player_force.get_force_id())
                {
                    pk::play_se(6);
                    pk::message_box(pk::u8encode(pk::format("목표를 달성하여 무장들의 충성도가 증가하고 \x1b[2x{}\x1b[0x의 공적이 증가했습니다. 또한 기교포인트를 \x1b[2x{}\x1b[0x만큼 획득했습니다.", pk::u8decode(pk::get_name(proposer)),tp / 2)));
                    pk::add_tp(pk::get_force(player_force.get_force_id()), tp, kunshu.get_pos());
                    pk::add_kouseki(proposer, kouseki);
                }
                else
                {
                    pk::play_se(6);
                    // 제안자가 사망 또는 배신했을 경우 공적은 증가하지 않는다.
                    pk::message_box(pk::u8encode(pk::format("목표를 달성하여 무장들의 충성도가 증가했습니다. 또한 기교포인트를 \x1b[2x{}\x1b[0x만큼 획득했습니다.", tp / 2)));
                    pk::add_tp(pk::get_force(player_force.get_force_id()), tp, kunshu.get_pos());
                }
            }
            else
            {
                pk::play_se(6);
                pk::message_box(pk::u8encode(pk::format("목표를 달성하여 무장들의 충성도가 증가하고 \x1b[2x{}\x1b[0x의 공적이 증가했습니다.", pk::u8decode(pk::get_name(proposer)))));
                pk::add_kouseki(proposer, kouseki);
                select_reward();
            }
        }

        void select_reward()
        {
            int level = get_subject_data(목표보상);
            int life = pk::get_scenario().life;
            int choose;

            if (life == 수명_가상)
            {
                array<string> reward_array = { pk::u8encode("\x1b[1x기교포인트\x1b[0x"), pk::u8encode("\x1b[2x능력경험치\x1b[0x"), pk::u8encode("\x1b[24x병종경험치\x1b[0x"), pk::u8encode("\x1b[26x무장 특기\x1b[0x") };

                choose = pk::choose(pk::u8encode("보상을 선택해주십시오."), reward_array);
            }
            else
            {
                array<string> reward_array = { pk::u8encode("\x1b[1x기교포인트\x1b[0x"), pk::u8encode("\x1b[2x능력경험치\x1b[0x"), pk::u8encode("\x1b[24x병종경험치\x1b[0x"), pk::u8encode("\x1b[26x무장 특기\x1b[0x"), pk::u8encode("\x1b[27x수명보너스\x1b[0x") };

                choose = pk::choose(pk::u8encode("보상을 선택해주십시오."), reward_array);
            }

            if (!reward_yes_no(choose, level - 1))
                select_reward();
        }

        bool reward_yes_no(int type, int level)
        {
            bool yes_no = false;
            int tp = 0;
            int exp = 0;
            int life = 0;
            int min = 0;
            int max = 0;
            // 포로를 제외한 무장을 보상의 대상으로 선택할 수 있다
            pk::list<pk::person@> valid_list = pk::get_person_list(player_force, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반));
            pk::list<pk::person@> person_sel;
            switch (type)
            {
            case 보상_기교:
                if (level == 0)
                {
                    min = 달성보상_기교_초급[0];
                    max = 달성보상_기교_초급[1];
                }
                else if (level == 1)
                {
                    min = 달성보상_기교_중급[0];
                    max = 달성보상_기교_중급[1];
                }
                else
                {
                    min = 달성보상_기교_고급[0];
                    max = 달성보상_기교_고급[1];
                }

                tp = ((pk::rand(max + 1 - min) + min + 50) / 100) * 100;

                yes_no = pk::yes_no(pk::u8encode(pk::format("\x1b[2x{}\x1b[0x ~ \x1b[2x{}\x1b[0x 사이의 기교 포인트를 획득할 수 있습니다. 기교 포인트를 선택 하시겠습니까?", min, max)));

                if (yes_no)
                {
                    pk::play_se(6);
                    pk::add_tp(pk::get_force(player_force.get_force_id()), tp * 2, kunshu.get_pos());
                    pk::message_box(pk::u8encode(pk::format("기교포인트를 \x1b[2x{}\x1b[0x만큼 획득했습니다.", tp)));
                }
                break;

            case 보상_능력경험치:
                if (level == 0)
                {
                    min = 달성보상_능력경험치_초급[0];
                    max = 달성보상_능력경험치_초급[1];
                }
                else if (level == 1)
                {
                    min = 달성보상_능력경험치_중급[0];
                    max = 달성보상_능력경험치_중급[1];
                }
                else
                {
                    min = 달성보상_능력경험치_고급[0];
                    max = 달성보상_능력경험치_고급[1];
                }

                exp = pk::rand(max + 1 - min) + min;

                yes_no = pk::yes_no(pk::u8encode(pk::format("\x1b[2x{}\x1b[0x ~ \x1b[2x{}\x1b[0x 사이의 \x1b[1x능력경험치\x1b[0x를 획득할 수 있습니다. \x1b[1x능력경험치\x1b[0x를 선택 하시겠습니까?", min, max)));

                if (yes_no)
                {
                    person_sel = pk::person_selector(pk::u8encode("장수 선택"), pk::u8encode("보상을 적용할 무장을 선택합니다."), valid_list, 1, 1);
                    
                    if (person_sel.count > 0)
                    {
                        pk::person@ target = person_sel[0];
                        pk::play_se(6);
                        for (int i = 0; i < 무장능력_끝; ++i)
                        {
                            target.stat_exp[i] = target.stat_exp[i] + exp;
                        }
                        pk::message_box(pk::u8encode(pk::format("\x1b[1x{}\x1b[0x의 모든 \x1b[1x능력경험치\x1b[0x가 \x1b[2x{}\x1b[0x만큼 증가했습니다.", pk::u8decode(pk::get_name(target)), exp)));
                    }
                    else
                    {
                        yes_no = false;
                    }
                }

                break;

            case 보상_병과경험치:
                if (level == 0)
                {
                    min = 달성보상_병과경험치_초급[0];
                    max = 달성보상_병과경험치_초급[1];
                }
                else if (level == 1)
                {
                    min = 달성보상_병과경험치_중급[0];
                    max = 달성보상_병과경험치_중급[1];
                }
                else
                {
                    min = 달성보상_병과경험치_고급[0];
                    max = 달성보상_병과경험치_고급[1];
                }

                exp = pk::rand(max + 1 - min) + min;

                yes_no = pk::yes_no(pk::u8encode(pk::format("\x1b[2x{}\x1b[0x ~ \x1b[2x{}\x1b[0x 사이의 \x1b[1x병과경험치\x1b[0x를 획득할 수 있습니다. \x1b[1x병과경험치\x1b[0x를 선택 하시겠습니까?", min, max)));

                if (yes_no)
                {
                    person_sel = pk::person_selector(pk::u8encode("장수 선택"), pk::u8encode("보상을 적용할 무장을 선택합니다."), valid_list, 1, 1);

                    if (person_sel.count > 0)
                    {
                        pk::person@ target = person_sel[0];
                        pk::play_se(6);
                        for (int i = 0; i < 6; ++i)
                        {
                            target.heishu_exp[i] = target.heishu_exp[i] + exp;
                        }
                        pk::message_box(pk::u8encode(pk::format("\x1b[1x{}\x1b[0x의 모든 \x1b[1x병과경험치\x1b[0x가 \x1b[2x{}\x1b[0x만큼 증가했습니다.", pk::u8decode(pk::get_name(target)), exp)));
                    }
                    else
                    {
                        yes_no = false;
                    }
                }

                break;

            case 보상_특기:
                
                if (level == 0)
                {
                    yes_no = pk::yes_no(pk::u8encode(pk::format("\x1b[2x{}\x1b[0x, \x1b[2x{}\x1b[0x, \x1b[2x{}\x1b[0x, \x1b[2x{}\x1b[0x, \x1b[2x{}\x1b[0x, \x1b[2x{}\x1b[0x, \x1b[2x{}\x1b[0x 중 무작위의 \x1b[1x특기\x1b[0x를 습득하게 됩니다. \x1b[1x특기\x1b[0x를 선택하시겠습니까?", 
                        pk::u8decode(pk::get_skill(달성보상_특기_초급[0]).name), pk::u8decode(pk::get_skill(달성보상_특기_초급[1]).name), pk::u8decode(pk::get_skill(달성보상_특기_초급[2]).name), pk::u8decode(pk::get_skill(달성보상_특기_초급[3]).name),
                        pk::u8decode(pk::get_skill(달성보상_특기_초급[4]).name), pk::u8decode(pk::get_skill(달성보상_특기_초급[5]).name), pk::u8decode(pk::get_skill(달성보상_특기_초급[6]).name))));

                    if (yes_no)
                    {
                        int skill = 달성보상_특기_초급[pk::rand(달성보상_특기_초급.length)];

                        person_sel = pk::person_selector(pk::u8encode("장수 선택"), pk::u8encode("보상을 적용할 무장을 선택합니다."), valid_list, 1, 1);

                        if (person_sel.count > 0)
                        {
                            pk::person@ target = person_sel[0];
                            pk::play_se(6);
                            target.skill = skill;
                            pk::skill@ reward = pk::get_skill(skill);
                            pk::message_box(pk::u8encode(pk::format("\x1b[1x{}\x1b[0x(이)가 특기 \x1b[2x{}\x1b[0x(을)를 습득했습니다.", pk::u8decode(pk::get_name(target)), pk::u8decode(pk::get_name(reward)))));
                        }
                        else
                        {
                            yes_no = false;
                        }
                    }
                }
                else if (level == 1)
                {
                    yes_no = pk::yes_no(pk::u8encode(pk::format("\x1b[2x{}\x1b[0x, \x1b[2x{}\x1b[0x, \x1b[2x{}\x1b[0x, \x1b[2x{}\x1b[0x, \x1b[2x{}\x1b[0x, \x1b[2x{}\x1b[0x, \x1b[2x{}\x1b[0x 중 무작위의 \x1b[1x특기\x1b[0x를 습득하게 됩니다. \x1b[1x특기\x1b[0x를 선택하시겠습니까?",
                        pk::u8decode(pk::get_skill(달성보상_특기_중급[0]).name), pk::u8decode(pk::get_skill(달성보상_특기_중급[1]).name), pk::u8decode(pk::get_skill(달성보상_특기_중급[2]).name), pk::u8decode(pk::get_skill(달성보상_특기_중급[3]).name),
                        pk::u8decode(pk::get_skill(달성보상_특기_중급[4]).name), pk::u8decode(pk::get_skill(달성보상_특기_중급[5]).name), pk::u8decode(pk::get_skill(달성보상_특기_중급[6]).name))));

                    if (yes_no)
                    {
                        int skill = 달성보상_특기_중급[pk::rand(달성보상_특기_중급.length)];

                        person_sel = pk::person_selector(pk::u8encode("장수 선택"), pk::u8encode("보상을 적용할 무장을 선택합니다."), valid_list, 1, 1);

                        if (person_sel.count > 0)
                        {
                            pk::person@ target = person_sel[0];
                            pk::play_se(6);
                            target.skill = skill;
                            pk::skill@ reward = pk::get_skill(skill);
                            pk::message_box(pk::u8encode(pk::format("\x1b[1x{}\x1b[0x(이)가 특기 \x1b[2x{}\x1b[0x(을)를 습득했습니다.", pk::u8decode(pk::get_name(target)), pk::u8decode(pk::get_name(reward)))));
                        }
                        else
                        {
                            yes_no = false;
                        }
                    }
                }
                else
                {
                    yes_no = pk::yes_no(pk::u8encode(pk::format("\x1b[2x{}\x1b[0x, \x1b[2x{}\x1b[0x, \x1b[2x{}\x1b[0x, \x1b[2x{}\x1b[0x, \x1b[2x{}\x1b[0x, \x1b[2x{}\x1b[0x, \x1b[2x{}\x1b[0x 중 무작위의 \x1b[1x특기\x1b[0x를 습득하게 됩니다. \x1b[1x특기\x1b[0x를 선택하시겠습니까?",
                        pk::u8decode(pk::get_skill(달성보상_특기_고급[0]).name), pk::u8decode(pk::get_skill(달성보상_특기_고급[1]).name), pk::u8decode(pk::get_skill(달성보상_특기_고급[2]).name), pk::u8decode(pk::get_skill(달성보상_특기_고급[3]).name),
                        pk::u8decode(pk::get_skill(달성보상_특기_고급[4]).name), pk::u8decode(pk::get_skill(달성보상_특기_고급[5]).name), pk::u8decode(pk::get_skill(달성보상_특기_고급[6]).name))));

                    if (yes_no)
                    {
                        int skill = 달성보상_특기_고급[pk::rand(달성보상_특기_고급.length)];

                        person_sel = pk::person_selector(pk::u8encode("장수 선택"), pk::u8encode("보상을 적용할 무장을 선택합니다."), valid_list, 1, 1);

                        if (person_sel.count > 0)
                        {
                            pk::person@ target = person_sel[0];
                            pk::play_se(6);
                            target.skill = skill;
                            pk::skill@ reward = pk::get_skill(skill);
                            pk::message_box(pk::u8encode(pk::format("\x1b[1x{}\x1b[0x(이)가 특기 \x1b[2x{}\x1b[0x(을)를 습득했습니다.", pk::u8decode(pk::get_name(target)), pk::u8decode(pk::get_name(reward)))));
                        }
                        else
                        {
                            yes_no = false;
                        }
                    }
                }

                break;

            case 보상_수명:
                if (level == 0)
                {
                    min = 달성보상_수명_초급[0];
                    max = 달성보상_수명_초급[1];
                }
                else if (level == 1)
                {
                    min = 달성보상_수명_중급[0];
                    max = 달성보상_수명_중급[1];
                }
                else
                {
                    min = 달성보상_수명_고급[0];
                    max = 달성보상_수명_고급[1];
                }

                life = pk::rand(max + 1 - min) + min;

                yes_no = pk::yes_no(pk::u8encode(pk::format("\x1b[2x{}\x1b[0x ~ \x1b[2x{}\x1b[0x 사이의 \x1b[1x수명\x1b[0x을 획득할 수 있습니다. \x1b[1x수명연장\x1b[0x을 선택 하시겠습니까?", min, max)));

                if (yes_no)
                {
                    person_sel = pk::person_selector(pk::u8encode("장수 선택"), pk::u8encode("보상을 적용할 무장을 선택합니다."), valid_list, 1, 1);

                    if (person_sel.count > 0)
                    {
                        pk::person@ target = person_sel[0];
                        target.death = target.death + life;
                        pk::play_se(6);
                        pk::message_box(pk::u8encode(pk::format("\x1b[1x{}\x1b[0x의 \x1b[1x수명\x1b[0x이 \x1b[2x{}\x1b[0x만큼 늘어났습니다.", pk::u8decode(pk::get_name(target)), life)));
                    }
                    else
                    {
                        yes_no = false;
                    }
                }

                break;
            }

            return yes_no;
        }

        void get_penalty()
        {
            int level = get_subject_data(목표보상);

            int loyalty = 달성보상_충성도[level - 1] * 실패시_충성도하락_배율 * -1;

            // 군주와 포로를 제외한 부하들의 리스트
            array<pk::person@> moo_array = pk::list_to_array(pk::get_person_list(player_force, pk::mibun_flags(신분_도독, 신분_태수, 신분_일반, 신분_포로)));

            for (int i = 0; i < moo_array.length; ++i)
            {
                pk::add_loyalty(moo_array[i], loyalty);
            }

            pk::message_box(pk::u8encode("목표 달성에 실패하여 실망한 무장들의 충성도가 하락했습니다."));
        }

        void set_mission(int mission, int condition1, int condition2, int value)
        {
            data_array[목표상태].hp = 목표_진행;
            data_array[목표].hp = mission;
            data_array[목표조건1].hp = condition1;
            data_array[목표조건2].hp = condition2;
            data_array[목표수치].hp = value;
        }

        // 임무 포기
        void cancel()
        {
            pk::clear_mission();
            data_array[목표상태].hp = 목표_실패;
            data_array[목표].hp = -1;
            data_array[목표조건1].hp = -1;
            data_array[목표조건2].hp = -1;
            data_array[목표수치].hp = -1;
            data_array[목표보상].hp = -1;
            data_array[목표제안무장].hp = -1;
        }

        // 새해 임무 초기화
        void reset()
        {
            data_array[목표상태].hp = 목표_없음;
            data_array[목표].hp = -1;
            data_array[목표조건1].hp = -1;
            data_array[목표조건2].hp = -1;
            data_array[목표수치].hp = -1;
            data_array[목표보상].hp = -1;
            data_array[목표제안무장].hp = -1;
            pk::clear_mission();
            //목표 = 목표_조건1 = 목표_조건2 = 목표_수치 = -1;
            //목표상태 = 목표_없음;
            for (int i = 0; i < participants.length; ++i)
            {
                participants[i].clear();
            }
        }


        // 회의장면을 세팅해주는 함수
        void conference()
        {
            propose(kunshu, "올해의 방침을 결정하는 회의를 열겠소. 모두들 기탄없이 의견을 말해보시오.");
            pk::list<pk::person@> valid_list;
            for (int i = 0; i < participants.length; ++i)
            {
                if (participants[i].speaker == null)
                    continue;

                propose(participants[i].speaker, participants[i].dialog);
                valid_list.add(participants[i].speaker);
            }

            select_opinion(valid_list);
            set_mission_window();
        } 

        void select_opinion(pk::list<pk::person@> valid_list)
        {
            int choose = pk::choose(pk::u8encode("회의를 진행해주십시오."), choose_conference_decision_array);
            pk::list<pk::person@> person_sel;

            if (choose == 회의_채택)
            {
                person_sel = pk::person_selector(pk::u8encode("장수 선택"), pk::u8encode("무장의 의견을 채택합니다."), valid_list, 1, 1);

                if (person_sel.count <= 0)
                {
                    select_opinion(valid_list);
                }
                else
                {
                    int index = -1;

                    for (int i = 0; i < participants.length; ++i)
                    {
                        if (person_sel[0].get_id() == participants[i].speaker.get_id())
                        {
                            index = i;
                            break;
                        }
                    }
                    pk::person@ p;

                    if (participants[index].opinion.subject == 목표_없음 || participants[index].opinion.subject == 목표_고갈)
                    {
                        propose(kunshu, "이렇다 할 의견은 없는것 같군. 올해의 목표는 없소.");
                        set_subject(participants[index], true);
                    }
                    else if (participants[index].opinion.subject == 목표_동조)
                    {
                        int target = participants[index].opinion.subject_condition1;
                        index = -1;
                        for (int i = 0; i < participants.length; ++i)
                        {
                            if (target == participants[i].speaker.get_id())
                            {
                                index = i;
                                break;
                            }
                        }
                        @p = participants[index].speaker;
                        propose(kunshu, pk::format("이번에는 \x1b[2x{}\x1b[0x의 의견이 좋겠군. 이상으로 회의를 마치겠소.", pk::u8decode(pk::get_name(p))));
                        set_subject(participants[index], false);
                    }
                    else
                    {
                        @p = participants[index].speaker;
                        propose(kunshu, pk::format("이번에는 \x1b[2x{}\x1b[0x의 의견이 좋겠군. 이상으로 회의를 마치겠소.", pk::u8decode(pk::get_name(p))));
                        set_subject(participants[index], false);
                    }
                }
            }
            else if (choose == 회의_확인)
            {
                person_sel = pk::person_selector(pk::u8encode("장수 선택"), pk::u8encode("무장의 의견을 확인합니다."), valid_list, 1, 1);

                if (person_sel.count <= 0)
                {
                    select_opinion(valid_list);
                }
                else
                {
                    int index = -1;
                    for (int i = 0; i < participants.length; ++i)
                    {
                        if (person_sel[0].get_id() == participants[i].speaker.get_id())
                        {
                            index = i;
                            break;
                        }
                    }

                    propose(participants[index].speaker, participants[index].dialog);
                    select_opinion(valid_list);
                }
            }
            else if (choose == 회의_보류)
            {
                propose(kunshu, "이렇다 할 의견은 없는것 같군. 올해의 목표는 없소.");
                set_subject(participants[0], true);
            }
        }

        void set_mission_window()
        {
            title = "";
            descript = "";

            int sub = get_subject_data(목표);
            int sub_con1 = get_subject_data(목표조건1);
            int sub_con2 = get_subject_data(목표조건2);
            int sub_count = get_subject_data(목표수치);

            //pk::start_mission(pk::u8encode("관우의 처단"), pk::u8encode(pk::format("관우를 처단하라\n{}", i)), "", "",
            //    -1, pk::u8encode("목표를 중단하시겠습니까?"), pk::mission_abandon_t(cancel));

            if (sub == 목표_없음)
            {
                return;
            }

            if (sub == 목표_보물수집)
            {
                title = "보물 수집";
                descript = pk::format("보물 \x1b[16x{}\x1b[0x 획득", pk::u8decode(pk::get_item(sub_con1).name));
            }
            else if (sub == 목표_무장처단)
            {
                pk::person@ target = pk::get_person(sub_con1);
                title = "무장 처단";
                descript = pk::format("무장 \x1b[2x{}\x1b[0x의 사망", pk::u8decode(pk::get_name(target)));
            }
            else if (sub == 목표_특정무장)
            {
                pk::person@ target = pk::get_person(sub_con1);
                title = "무장 등용";
                descript = pk::format("무장 \x1b[2x{}\x1b[0x(을)를 등용", pk::u8decode(pk::get_name(target)));
            }
            else if (sub == 목표_특기무장)
            {
                pk::skill@ skill = pk::get_skill(sub_con1);
                title = "특기 보유";
                descript = pk::format("특기 \x1b[2x{}\x1b[0x 무장을 보유", pk::u8decode(pk::get_name(skill)));
            }
            else if (sub == 목표_능력무장)
            {
                title = "인재 확충";
                descript = pk::format("\x1b[1x{}\x1b[0x \x1b[2x{}\x1b[0x 이상 무장 \x1b[2x{}\x1b[0x명 이상 보유.", 무장능력[sub_con1], sub_con2, sub_count);
            }
            else if (sub == 목표_전체무장)
            {
                title = "인재 확보";
                descript = pk::format("세력 무장 \x1b[2x{}\x1b[0x명 이상 보유.", sub_count);
            }
            else if (sub == 목표_도시공략)
            {
                pk::city@ target = pk::get_city(sub_con1);
                title = "도시 공략";
                descript = pk::format("도시 \x1b[2x{}\x1b[0x 점령.", pk::u8decode(pk::get_name(target)));
            }
            else if (sub == 목표_도시방비)
            {
                pk::city@ target = pk::get_city(sub_con1);
                title = "도시 방비";
                descript = pk::format("도시 \x1b[1x{}\x1b[0x에 방어시설 \x1b[2x{}\x1b[0x개 이상 건설.", pk::u8decode(pk::get_name(target)), sub_count);
            }
            else if (sub == 목표_세력군비)
            {
                title = "군비 확충";
                switch (sub_con1)
                {
                case 창극노:
                    descript = pk::format("자세력 병사 \x1b[2x{}\x1b[0x이상 \n\x1b[1x{}\x1b[0x를 도합 \x1b[2x{}\x1b[0x 이상 비축.", sub_count * 1000, 병기[sub_con1], sub_count * 1000);
                    break;

                case 군마:
                    descript = pk::format("자세력 \x1b[1x{}\x1b[0x를 \x1b[2x{}\x1b[0x 이상 비축.", 병기[sub_con1], sub_count * 1000);
                    break;

                case 공성병기:
                    descript = pk::format("자세력 \x1b[1x{}\x1b[0x를 \x1b[2x{}\x1b[0x 이상 비축.", 병기[sub_con1], sub_count);
                    break;

                case 선박:
                    descript = pk::format("자세력 \x1b[1x{}\x1b[0x을 \x1b[2x{}\x1b[0x 이상 비축.", 병기[sub_con1], sub_count);
                    break;
                }
            }
            else if (sub  == 목표_황제옹립)
            {
                title = "협천자";
                descript = "\x1b[1x황제\x1b[0x를 보호.";
            }
            else if (sub == 목표_황제폐위)
            {
                title = "역적";
                descript = "\x1b[1x황제\x1b[0x를 폐위.";
            }
            else if (sub == 목표_작위제수)
            {
                title = "작위 제수";
                pk::title@ target = pk::get_title(sub_con1);
                descript = pk::format("작위 \x1b[1x{}\x1b[0x 이상 획득.", pk::u8decode(pk::get_name(target)));
                
            }
            else if (sub == 목표_기교연구)
            {
                pk::tech@ target = pk::get_tech(sub_con1);
                title = "기교 연구";
                descript = pk::format("기교연구 \x1b[1x{}\x1b[0x 획득.", pk::u8decode(pk::get_name(target)));
            }
            else if (sub == 목표_세력동맹)
            {
                title = "세력 동맹";
                pk::force@ force = pk::get_force(sub_con1);
                string target_force = "";
                if (force.kokugou == -1)
                {
                    target_force = pk::u8decode(pk::get_name(pk::get_person(force.kunshu)));
                }
                else
                {
                    target_force = pk::u8decode(pk::get_kokugou(force.kokugou).get_name());
                }

                descript = pk::format("\x1b[1x{}\x1b[0x군과 동맹 유지.", target_force);
            }
            else if (sub == 목표_세력친밀)
            {
                title = "세력 화친";
                pk::force@ force = pk::get_force(sub_con1);
                string target_force = "";
                if (force.kokugou == -1)
                {
                    target_force = pk::u8decode(pk::get_name(pk::get_person(force.kunshu)));
                }
                else
                {
                    target_force = pk::u8decode(pk::get_kokugou(force.kokugou).get_name());
                }

                descript = pk::format("\x1b[1x{}\x1b[0x군과 우호도 \x1b[2x친밀\x1b[0x 유지.", target_force);
            }
            else if (sub == 목표_본거지_아군)
            {
                title = "치안 유지";
                descript = "세력 내 \x1b[2x본거지\x1b[0x 발생 방지.";
            }
            else if (sub == 목표_본거지_적군)
            {
                pk::city@ city = pk::get_city(sub_con1);
                title = "본거지 발생";
                descript = pk::format("도시 \x1b[1x{}\x1b[0x에 \x1b[2x본거지\x1b[0x 발생 유도.", pk::u8decode(pk::get_name(city)));
            }
            else if (sub == 목표_구호탄랑)
            {
                title = "구호탄랑의 계";
                pk::force@ force = pk::get_force(sub_con1);
                string target_force = "";
                if (force.kokugou == -1)
                {
                    target_force = pk::u8decode(pk::get_name(pk::get_person(force.kunshu)));
                }
                else
                {
                    target_force = pk::u8decode(pk::get_kokugou(force.kokugou).get_name());
                }

                descript = pk::format("\x1b[1x{}\x1b[0x군에 반란 유도.", target_force);
            }
            else if (sub == 목표_동작대)
            {
                title = "동작대부";
                descript = "세력 내 \x1b[2x동작대\x1b[0x 건설.";
            }
        }

        void display_mission()
        {
            if (get_subject_data(목표) == -1)
                return;
            else
            {
                pk::start_mission(pk::u8encode(title), pk::u8encode(descript), "", "",
                    -1, pk::u8encode("목표를 중단하시겠습니까? (실패로 처리됩니다.)"), pk::mission_abandon_t(cancel));
            }
        }

        bool check_condition()
        {
            bool is_satisfy = false;

            if (get_subject_data(목표) == 목표_보물수집)
            {
                pk::item@ item = pk::get_item(get_subject_data(목표조건1));
                pk::person@ owner = pk::get_person(item.owner);
                // 해당 보물 소유주가 플레이어 세력이면 성공
                if (player_force.get_force_id() == owner.get_force_id())
                {
                    is_satisfy = true;
                }
            }
            else if (get_subject_data(목표) == 목표_무장처단)
            {
                pk::person@ target = pk::get_person(get_subject_data(목표조건1));
                // 목표 무장이 사망상태면 성공 (플레이어가 사망의 원인이 아니어도 성공)
                if (!target.is_alive())
                    is_satisfy = true;
            }
            else if (get_subject_data(목표) == 목표_특정무장)
            {
                pk::person@ target = pk::get_person(get_subject_data(목표조건1));
                // 목표 무장이 생존중이고, 플레이어 세력에 속하면 성공
                if (target.is_alive() && target.get_force_id() == player_force.get_force_id())
                {
                    is_satisfy = true;
                }
            }
            else if (get_subject_data(목표) == 목표_특기무장)
            {
                auto list = pk::get_person_list(player_force, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반, 신분_포로));
                pk::array<pk::person@> person_array = pk::list_to_array(list);
                
                int count = 0;
                
                for (int i = 0; i < person_array.length; ++i)
                {
                    pk::person@ person = person_array[i];
                    // 생존중인 플레이어의 무장의 특기가 목표와 부합될 경우 카운트 +1
                    if (person.is_alive() && person.skill == get_subject_data(목표조건1))
                    {
                        count++;
                    }
                }
                
                // 목표수치 이상인 경우 성공
                if (count >= get_subject_data(목표수치))
                {
                    is_satisfy = true;
                }
            }
            else if (get_subject_data(목표) == 목표_능력무장)
            {
                auto list = pk::get_person_list(player_force, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반, 신분_포로));
                pk::array<pk::person@> person_array = pk::list_to_array(list);
                int count = 0;

                for (int i = 0; i < person_array.length; ++i)
                {
                    pk::person@ person = person_array[i];
                    // 생존중인 플레이어의 무장의 능력치가 목표 이상일 경우 카운트 +1
                    if (person.is_alive() && person.stat[get_subject_data(목표조건1)] >= get_subject_data(목표조건2))
                    {
                        count++;
                    }
                }

                // 목표수치 이상인 경우 성공
                if (count >= get_subject_data(목표수치))
                {
                    is_satisfy = true;
                }
            }
            else if (get_subject_data(목표) == 목표_전체무장)
            {
                auto list = pk::get_person_list(player_force, pk::mibun_flags(신분_군주, 신분_도독, 신분_태수, 신분_일반, 신분_포로));
                // 플레이어 소속의 무장 숫자가 목표 이상이면 성공
                if (list.count >= get_subject_data(목표수치))
                {
                    is_satisfy = true;
                }
            }
            else if (get_subject_data(목표) == 목표_도시공략)
            {
                pk::city@ city = pk::get_city(get_subject_data(목표조건1));
                // 목표도시가 플레이어 소속이면 성공
                if (player_force.get_force_id() == city.get_force_id())
                {
                    is_satisfy = true;
                }
            }
            else if (get_subject_data(목표) == 목표_도시방비)
            {
                int city_id = pk::get_city(get_subject_data(목표조건1)).get_id();

                // 목표도시가 플레이어 소속이면서
                if (pk::get_city(city_id).get_force_id() == player_force.get_force_id())
                {
                    auto building_arr = pk::list_to_array(pk::get_building_list());
                    int count = 0;
                    for (int i = 0; i < building_arr.length; ++i)
                    {
                        pk::building@ building = building_arr[i];

                        // 목표 도시 소속의 방어건물 체크
                        if (pk::get_city_id(building.get_pos()) == city_id)
                        {
                            if ((building.facility >= 시설_진 && building.facility <= 시설_연노로) || (building.facility >= 시설_투석대 && building.facility <= 시설_석병팔진))
                            {
                                count++;
                            }
                        }
                    }

                    // 방어시설의 숫자가 목표수치 이상이면 성공
                    if (count >= get_subject_data(목표수치))
                    {
                        is_satisfy = true;
                    }
                }
            }
            else if (get_subject_data(목표) == 목표_세력군비)
            {
                pk::list<pk::building@> list;

                auto all_list = pk::get_building_list();

                for (int i = 0; i < all_list.count; ++i)
                {
                    pk::building@ building = all_list[i];

                    if (building.get_force_id() == player_force.get_force_id() && (building.get_id() >= 건물_도시시작 && building.get_id() <= 건물_거점끝))
                    {
                        list.add(building);
                    }
                }

                auto building_arr = pk::list_to_array(list);

                int troops = 0;
                int weapons = 0;
                int horses = 0;
                int sieges = 0;
                int ships = 0;

                // 플레이어 소속 거점을 돌면서 병사, 병기 계산
                for (int i = 0; i < building_arr.length; ++i)
                {
                    pk::building@ building = building_arr[i];
                    troops += pk::get_troops(building);
                    weapons += (pk::get_weapon_amount(building, 병기_창) + pk::get_weapon_amount(building, 병기_극) + pk::get_weapon_amount(building, 병기_노));
                    horses += pk::get_weapon_amount(building, 병기_군마);
                    sieges += (pk::get_weapon_amount(building, 병기_충차) + pk::get_weapon_amount(building, 병기_정란) + pk::get_weapon_amount(building, 병기_투석) + pk::get_weapon_amount(building, 병기_목수));
                    ships += (pk::get_weapon_amount(building, 병기_누선) + pk::get_weapon_amount(building, 병기_투함));
                }

                auto unit_arr = pk::list_to_array(pk::get_unit_list(player_force));

                for (int i = 0; i < unit_arr.length; ++i)
                {
                    pk::unit@ unit = unit_arr[i];
                    if (!unit.is_alive())
                        continue;
                    troops += unit.troops;
                    if (unit.type == 부대종류_전투)
                    {
                        int ship = unit.stock[1].id;

                        if (ship == 병기_누선 || ship == 병기_투함)
                        {
                            ships += unit.stock[1].amount;
                        }

                        int weapon = unit.stock[0].id;

                        if (weapon == 병기_창 || weapon == 병기_극 || weapon == 병기_노)
                        {
                            weapons += unit.stock[0].amount;
                        }
                        else if (weapon == 병기_군마)
                        {
                            horses += unit.stock[0].amount;
                        }
                        else if (weapon == 병기_충차 || weapon == 병기_정란 || weapon == 병기_투석 || weapon == 병기_목수)
                        {
                            sieges += unit.stock[0].amount;
                        }
                    }
                    else
                    {
                        weapons += (unit.stock[병기_창].amount + unit.stock[병기_극].amount + unit.stock[병기_노].amount);
                        horses += unit.stock[병기_군마].amount;
                        sieges += (unit.stock[병기_충차].amount + unit.stock[병기_정란].amount + unit.stock[병기_투석].amount + unit.stock[병기_목수].amount);
                        ships += (unit.stock[병기_누선].amount + unit.stock[병기_투함].amount);
                    }
                }

                // 조건에 해당하는 병사 및 병기 확인 작업
                switch (get_subject_data(목표조건1))
                {
                    case 창극노:
                        if (troops >= get_subject_data(목표수치) * 1000 && weapons >= get_subject_data(목표수치) * 1000)
                        {
                            is_satisfy = true;
                        }
                        break;

                    case 군마:
                        if (horses >= get_subject_data(목표수치) * 1000)
                        {
                            is_satisfy = true;
                        }
                        break;

                    case 공성병기:
                        if (sieges >= get_subject_data(목표수치))
                        {
                            is_satisfy = true;
                        }
                        break;

                    case 선박:
                    if (ships >= get_subject_data(목표수치))
                    {
                        is_satisfy = true;
                    }
                    break;
                }
            }
            else if (get_subject_data(목표) == 목표_황제옹립)
            {
                if(pk::is_protecting_the_emperor(player_force))
                {
                    is_satisfy = true;
                }
            }
            else if (get_subject_data(목표) == 목표_황제폐위)
            {
                is_satisfy = false;
                pk::person@ emperor = pk::get_person(pk::get_scenario().emperor);

                // 황제가 죽었거나 없을 경우 패스
                if (null == emperor)
                {
                    is_satisfy = true;
                }
                else if (emperor.mibun == 신분_사망)
                {
                    is_satisfy = true;
                }
                else
                {

                }
            }
            else if (get_subject_data(목표) == 목표_작위제수)
            {
                if(player_force.title <= get_subject_data(목표조건1))
                {
                    is_satisfy = true;
                }
            }
            else if (get_subject_data(목표) == 목표_기교연구)
            {
                if (pk::has_tech(player_force, get_subject_data(목표조건1)))
                {
                    is_satisfy = true;
                }
            }
            else if (get_subject_data(목표) == 목표_세력동맹)
            {
                if (player_force.ally[get_subject_data(목표조건1)])
                {
                    is_satisfy = true;
                }
            }
            else if (get_subject_data(목표) == 목표_세력친밀)
            {
                if(player_force.relations[get_subject_data(목표조건1)] >= 81)
                {
                    is_satisfy = true;
                }
            }
            else if (get_subject_data(목표) == 목표_본거지_아군)
            {
                is_satisfy = true; 
            
                array<pk::building@> building_arr = pk::list_to_array(pk::get_building_list());

                for (int i = 0; i < building_arr.length; ++i)
                {
                    pk::building@ building = building_arr[i];
                    
                    if (building.facility == 시설_본거지1 || building.facility == 시설_본거지2)
                    {
                        pk::city@ city = pk::get_city(pk::get_city_id(building.get_pos()));

                        if (city.get_force_id() == player_force.get_force_id())
                        {
                            is_satisfy = false;
                        }
                    }
                }
            }
            else if (get_subject_data(목표) == 목표_본거지_적군)
            {
                array<pk::building@> building_arr = pk::list_to_array(pk::get_building_list());

                int city_id = pk::get_city(get_subject_data(목표조건1)).get_id();

                for (int i = 0; i < building_arr.length; ++i)
                {
                    pk::building@ building = building_arr[i];

                    if (building.facility == 시설_본거지1 || building.facility == 시설_본거지2)
                    {
                        if (pk::get_city_id(building.get_pos()) == city_id)
                        {
                            is_satisfy = true;
                        }
                    }
                }
            }
            else if (get_subject_data(목표) == 목표_구호탄랑)
            {
                // 
            }
            else if (get_subject_data(목표) == 목표_동작대)
            {
                array<pk::building@> building_arr = pk::list_to_array(pk::get_building_list());

                for (int i = 0; i < building_arr.length; ++i)
                {
                    pk::building@ building = building_arr[i];

                    if (building.facility == 시설_동작대)
                    {
                        if (building.get_force_id() == player_force.get_force_id())
                        {
                            is_satisfy = true;
                        }
                    }
                }
            }

            return is_satisfy;
        }

        void propose(pk::person@ person, string dialog)
        {
            pk::anim(0, person, 0x37);
            pk::wait(1000);
            pk::message_box(pk::u8encode(dialog), person);
        }

        void set_subject(Proposal proposal, bool is_cancel)
        {
            if (is_cancel)
            {
                data_array[목표상태].hp = 목표_없음;
                data_array[목표].hp = 목표_없음;
                data_array[목표조건1].hp = 목표_없음;
                data_array[목표조건2].hp = 목표_없음;
                data_array[목표수치].hp = 목표_없음;
                data_array[목표보상].hp = 목표_없음;
                data_array[목표제안무장].hp = 목표_없음;
            }
            else
            {
                data_array[목표상태].hp = 목표_진행;
                data_array[목표].hp = proposal.opinion.subject;
                data_array[목표조건1].hp = proposal.opinion.subject_condition1;
                data_array[목표조건2].hp = proposal.opinion.subject_condition2;
                data_array[목표수치].hp = proposal.opinion.subject_count;
                data_array[목표보상].hp = proposal.opinion.subject_level;
                data_array[목표제안무장].hp = proposal.speaker.get_id();
            }
        }

        int get_subject_data(int index)
        {
            int data = data_array[index].hp;

            if (data >= 60000)
            {
                return -1;
            }

            return data_array[index].hp;
        }

        pk::city@ get_random_enemy_neighbor_city()
        {
            pk::array<pk::city@> cityArray = pk::list_to_array(pk::get_city_list());
            pk::list<pk::city@> forceCityList;
            pk::list<pk::city@> validCityList;

            for (int i = 0; i < cityArray.length; ++i)
            {
                pk::city@ city = cityArray[i];

                if (city.get_force_id() == player_force.get_force_id())
                {
                    forceCityList.add(city);
                    //validCityList.add(city);
                }
            }

            for (int i = 0; i < cityArray.length; ++i)
            {
                pk::city@ city = cityArray[i];

                // 자세력 소유 도시가 아닌 도시만 가능
                if (city.get_force_id() != player_force.get_force_id())
                {
                    // 동맹중인 세력은 패스
                    if (true == pk::is_enemy(player_force, city) || city.get_force_id() == -1)
                    {
                        for (int j = 0; j < forceCityList.count; ++j)
                        {
                            if (true == pk::has_neighbor(city, forceCityList[j].get_id()))
                            {
                                validCityList.add(city);
                                break;
                            }
                        }
                    }
                }
            }

            if (validCityList.count != 0)
            {
                return validCityList[pk::rand(validCityList.count)];
            }
            else
            {
                return null;
            }
        }

        pk::list<pk::city@> get_enemy_neighbor_city_list()
        {
            pk::array<pk::city@> cityArray = pk::list_to_array(pk::get_city_list());
            pk::list<pk::city@> forceCityList;
            pk::list<pk::city@> validCityList;

            for (int i = 0; i < cityArray.length; ++i)
            {
                pk::city@ city = cityArray[i];

                if (city.get_force_id() == player_force.get_force_id())
                {
                    forceCityList.add(city);
                    //validCityList.add(city);
                }
            }

            for (int i = 0; i < cityArray.length; ++i)
            {
                pk::city@ city = cityArray[i];

                // 자세력 소유 도시가 아닌 도시만 가능
                if (city.get_force_id() != player_force.get_force_id())
                {
                    if (true == pk::is_enemy(player_force, city))
                    {
                        for (int j = 0; j < forceCityList.count; ++j)
                        {
                            if (true == pk::has_neighbor(city, forceCityList[j].get_id()))
                            {
                                validCityList.add(city);
                                break;
                            }
                        }
                    }
                }
            }

            return validCityList;
        }
        
        pk::city@ get_random_player_neighbor_city()
        {
            pk::array<pk::city@> cityArray = pk::list_to_array(pk::get_city_list());
            pk::list<pk::city@> enemyCityList;
            pk::list<pk::city@> validCityList;
            auto building_arr = pk::list_to_array(pk::get_building_list());

            for (int i = 0; i < cityArray.length; ++i)
            {
                pk::city@ city = cityArray[i];

                if (city.get_force_id() != player_force.get_force_id())
                {
                    enemyCityList.add(city);
                    //validCityList.add(city);
                }
            }

            for (int i = 0; i < cityArray.length; ++i)
            {
                pk::city@ city = cityArray[i];
                int city_id = city.get_id();
                // 자세력 소유 중에서 적의 도시와 인접해 있는 도시만 체크
                if (city.get_force_id() == player_force.get_force_id())
                {
                    for (int j = 0; j < enemyCityList.count; ++j)
                    {
                        if (true == pk::has_neighbor(city, enemyCityList[j].get_id()))
                        {
                            int count = 0;
                            for (int i = 0; i < building_arr.length; ++i)
                            {
                                pk::building@ building = building_arr[i];
                                // 목표 도시 소속의 방어건물 체크
                                if (pk::get_city_id(building.get_pos()) == city_id)
                                {
                                    if ((building.facility >= 시설_진 && building.facility <= 시설_연노로) || (building.facility >= 시설_투석대 && building.facility <= 시설_석병팔진))
                                    {
                                        count++;
                                    }
                                }
                            }

                            // 방어시설의 숫자가 5개 이하인 도시
                            if (count <= 3)
                            {
                                validCityList.add(city);
                                break;
                            }
                        }
                    }
                }
            }

            if (validCityList.count != 0)
            {
                return validCityList[pk::rand(validCityList.count)];
            }
            else
            {
                return null;
            }
        }

        void add_subject_confirm_menu()
        {
            pk::menu_item item;
            item.menu = 2;
            item.is_enabled = pk::menu_item_is_enabled_t(is_enabled);
            item.get_text = pk::menu_item_get_text_t(menu_title);
            item.get_desc = pk::menu_item_get_desc_t(menu_descript);
            item.handler = pk::menu_item_handler_t(subject_confirm_handler);
            pk::add_menu_item(item);
        }

        bool is_enabled()
        {
            return true;
        }

        string menu_title()
        {
            return pk::u8encode("목표 확인");
        }

        string menu_descript()
        {
            return pk::u8encode("회의 목표 달성도를 확인합니다.");
        }

        bool subject_confirm_handler()
        {
            if (get_subject_data(목표상태) == 목표_없음)
            {
                pk::message_box(pk::u8encode("올해 목표는 정하지 않았다."), kunshu);
            }
            else if (get_subject_data(목표상태) == 목표_달성)
            {
                pk::message_box(pk::u8encode("목표는 달성되었던가?"), kunshu);
            }
            else if (get_subject_data(목표상태) == 목표_실패)
            {
                pk::message_box(pk::u8encode("목표는 아쉽게도 실패했군."), kunshu);
            }
            else
            {
                if (check_condition())
                {
                    pk::message_box(pk::u8encode("목표는 달성되었던가?"), kunshu);
                }
                else
                {
                    pk::message_box(pk::u8encode("목표는 진행중이다."), kunshu);
                }
                    
            }

            return true;
        }


        void add_subject_renew_menu()
        {
            pk::menu_item item;
            item.menu = 2;
            item.is_enabled = pk::menu_item_is_enabled_t(is_enabled2);
            item.get_text = pk::menu_item_get_text_t(menu_title2);
            item.get_desc = pk::menu_item_get_desc_t(menu_descript2);
            item.handler = pk::menu_item_handler_t(subject_renew_handler);
            pk::add_menu_item(item);
        }

        bool is_enabled2()
        {
            return true;
        }

        string menu_title2()
        {
            return pk::u8encode("회의 갱신");
        }

        string menu_descript2()
        {
            return pk::u8encode("연간 목표를 강제로 종료하고 새로 시작합니다.");
        }

        bool subject_renew_handler()
        {
            // 이전 회의 정산
            pk::scene(pk::scene_t(orginize_conference_scene));
            // 회의 개최 선택
            pk::scene(pk::scene_t(choose_conference));
            display_mission();

            return true;
        }
    }

    Main main;
}