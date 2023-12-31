﻿namespace Ebony_XML_Override_음성_지정_신무장
{
	class Main
	{
		Main()
		{
			if (!pk::NDEBUG)
				return;
			xml();
		}
		void xml()
		{

			pk::load_xml("""
			<pk utf8="true" trace="true">
			/*
				공용음성 목록
				
					남성 : 거만남, 냉정남, 노인남, 대담남, 만족남, 보통남, 소심남, 위엄남, 은근남, 저돌남, 호쾌남, 도적남, 황건적
					여성 : 냉정녀, 대담녀, 보통녀, 요염녀, 위엄녀, 여아			
				
				
				미사용 고유음성 목록
				
					가남풍, 강희, 마요희, 몽염, 방선, 백영, 사마륜, 사마충, 서복, 아린, 여강, 왕분, 왕의, 이래, 장세연, 정안, 조령, 주발, 창평군
					
					참고사항 : 몽염의 경우 조조전 온라인에서 너무 어리게 등장하여 몽무의 음성을 사용합니다.
			*/
			
			//신무장 음성지정 시작
			<!--이명--><무장 번호="850"><음성 값="보통녀"/></무장>
			<!--번궁--><무장 번호="851"><음성 값="대담남"/></무장>
			<!--여치--><무장 번호="852"><음성 값="여치"/></무장>
			<!--번쾌--><무장 번호="853"><음성 값="번쾌"/></무장>
			<!--하후영--><무장 번호="854"><음성 값="하후영"/></무장>
			<!--진평--><무장 번호="855"><음성 값="진평"/></무장>
			<!--조참--><무장 번호="856"><음성 값="조참"/></무장>
			<!--관영--><무장 번호="857"><음성 값="대담남"/></무장>
			<!--왕릉--><무장 번호="858"><음성 값="대담남"/></무장>
			<!--종리말--><무장 번호="859"><음성 값="종리말"/></무장>
			<!--계포--><무장 번호="860"><음성 값="계포"/></무장>
			<!--환초--><무장 번호="861"><음성 값="보통남"/></무장>
			<!--용저--><무장 번호="862"><음성 값="용저"/></무장>
			<!--우희--><무장 번호="863"><음성 값="우희"/></무장>
			<!--공수반--><무장 번호="864"><음성 값="냉정남"/></무장>
			<!--곽외--><무장 번호="865"><음성 값="은근남"/></무장>
			<!--굴원--><무장 번호="866"><음성 값="소심남"/></무장>
			<!--극신--><무장 번호="867"><음성 값="저돌남"/></무장>
			<!--방연--><무장 번호="868"><음성 값="대담남"/></무장>
			<!--범려--><무장 번호="869"><음성 값="은근남"/></무장>
			<!--소진--><무장 번호="870"><음성 값="은근남"/></무장>
			<!--순관--><무장 번호="871"><음성 값="보통녀"/></무장>
			<!--양홍옥--><무장 번호="872"><음성 값="요염녀"/></무장>
			<!--여불위--><무장 번호="873"><음성 값="여불위"/></무장>
			<!--염파--><무장 번호="874"><음성 값="위엄남"/></무장>
			<!--웅의--><무장 번호="875"><음성 값="대담남"/></무장>
			<!--위무기--><무장 번호="876"><음성 값="위엄남"/></무장>
			<!--위앵--><무장 번호="877"><음성 값="냉정남"/></무장>
			<!--이목--><무장 번호="878"><음성 값="위엄남"/></무장>
			<!--이신--><무장 번호="879"><음성 값="이신"/></무장>
			<!--전기--><무장 번호="880"><음성 값="저돌남"/></무장>
			<!--전단--><무장 번호="881"><음성 값="위엄남"/></무장>
			<!--전문--><무장 번호="882"><음성 값="대담남"/></무장>
			<!--전인제--><무장 번호="883"><음성 값="대담남"/></무장>
			<!--조승--><무장 번호="884"><음성 값="냉정남"/></무장>
			<!--조옹--><무장 번호="885"><음성 값="대담남"/></무장>
			<!--추기--><무장 번호="886"><음성 값="냉정남"/></무장>
			<!--한무--><무장 번호="887"><음성 값="냉정남"/></무장>
			<!--한비--><무장 번호="888"><음성 값="소심남"/></무장>
			<!--한세충--><무장 번호="889"><음성 값="호쾌남"/></무장>
			<!--항연--><무장 번호="890"><음성 값="대담남"/></무장>
			<!--황헐--><무장 번호="891"><음성 값="냉정남"/></무장>
			<!--희평--><무장 번호="892"><음성 값="보통남"/></무장>
			<!--가비능--><무장 번호="893"><음성 값="저돌남"/></무장>
			<!--강단--><무장 번호="894"><음성 값="저돌남"/></무장>
			<!--구력거--><무장 번호="895"><음성 값="대담남"/></무장>
			<!--누반--><무장 번호="896"><음성 값="보통남"/></무장>
			<!--답돈--><무장 번호="897"><음성 값="저돌남"/></무장>
			<!--미당대왕--><무장 번호="898"><음성 값="대담남"/></무장>
			<!--반림--><무장 번호="899"><음성 값="만족남"/></무장>
			<!--보도근--><무장 번호="900"><음성 값="저돌남"/></무장>
			<!--비잔--><무장 번호="901"><음성 값="만족남"/></무장>
			<!--아단--><무장 번호="902"><음성 값="대담남"/></무장>
			<!--아하소과--><무장 번호="903"><음성 값="저돌남"/></무장>
			<!--어부라--><무장 번호="904"><음성 값="만족남"/></무장>
			<!--월길--><무장 번호="905"><음성 값="만족남"/></무장>
			<!--유주--><무장 번호="906"><음성 값="저돌남"/></무장>
			<!--유표--><무장 번호="907"><음성 값="저돌남"/></무장>
			<!--철리길--><무장 번호="908"><음성 값="대담남"/></무장>
			<!--토안--><무장 번호="909"><음성 값="저돌남"/></무장>
			<!--해니--><무장 번호="910"><음성 값="저돌남"/></무장>
			<!--호주천--><무장 번호="911"><음성 값="저돌남"/></무장>
			<!--황란--><무장 번호="912"><음성 값="저돌남"/></무장>
			<!--히미코--><무장 번호="913"><음성 값="위엄녀"/></무장>
			<!--나시메--><무장 번호="914"><음성 값="소심남"/></무장>
			<!--츠시고리--><무장 번호="915"><음성 값="대담남"/></무장>
			<!--우자기--><무장 번호="916"><음성 값="거만남"/></무장>
			<!--반씨--><무장 번호="917"><음성 값="위엄녀"/></무장>
			<!--조아--><무장 번호="918"><음성 값="보통녀"/></무장>
			<!--양휘유--><무장 번호="919"><음성 값="냉정녀"/></무장>
			<!--장창포--><무장 번호="920"><음성 값="위엄녀"/></무장>
			<!--조씨정--><무장 번호="921"><음성 값="대담녀"/></무장>
			<!--조절--><무장 번호="922"><음성 값="위엄녀"/></무장>
			<!--조화--><무장 번호="923"><음성 값="보통녀"/></무장>
			<!--최씨--><무장 번호="924"><음성 값="요염녀"/></무장>
			<!--풍씨--><무장 번호="925"><음성 값="보통녀"/></무장>
			<!--하씨--><무장 번호="926"><음성 값="위엄녀"/></무장>
			<!--환씨--><무장 번호="927"><음성 값="보통녀"/></무장>
			<!--후씨--><무장 번호="928"><음성 값="보통녀"/></무장>
			<!--도황--><무장 번호="929"><음성 값="저돌남"/></무장>
			<!--마륭--><무장 번호="930"><음성 값="소심남"/></무장>
			<!--비관--><무장 번호="931"><음성 값="거만남"/></무장>
			<!--석도--><무장 번호="932"><음성 값="냉정남"/></무장>
			<!--선우보--><무장 번호="933"><음성 값="저돌남"/></무장>
			<!--채옹--><무장 번호="934"><음성 값="냉정남"/></무장>
			<!--최주평--><무장 번호="935"><음성 값="소심남"/></무장>
			<!--혜강--><무장 번호="936"><음성 값="소심남"/></무장>
			<!--이세민--><무장 번호="937"><음성 값="위엄남"/></무장>
			<!--이정--><무장 번호="938"><음성 값="대담남"/></무장>
			<!--장손무기--><무장 번호="939"><음성 값="냉정남"/></무장>
			<!--무조--><무장 번호="940"><음성 값="위엄녀"/></무장>
			<!--양옥환--><무장 번호="941"><음성 값="냉정녀"/></무장>
			<!--조헌--><무장 번호="942"><음성 값="냉정녀"/></무장>
			<!--수칙--><무장 번호="943"><음성 값="위엄남"/></무장>
			<!--화목란--><무장 번호="944"><음성 값="보통녀"/></무장>
			<!--테무친--><무장 번호="945"><음성 값="위엄남"/></무장>
			<!--자무카--><무장 번호="946"><음성 값="거만남"/></무장>
			<!--보르테--><무장 번호="947"><음성 값="보통녀"/></무장>
			<!--라찌--><무장 번호="948"><음성 값="대담녀"/></무장>
			<!--쿠빌라이--><무장 번호="949"><음성 값="호쾌남"/></무장>
			<!--야율초재--><무장 번호="950"><음성 값="은근남"/></무장>
			<!--임충--><무장 번호="951"><음성 값="거만남"/></무장>
			<!--호연작--><무장 번호="952"><음성 값="저돌남"/></무장>
			<!--화영--><무장 번호="953"><음성 값="호쾌남"/></무장>
			<!--오용--><무장 번호="954"><음성 값="소심남"/></무장>
			<!--이규--><무장 번호="955"><음성 값="저돌남"/></무장>
			<!--연청--><무장 번호="956"><음성 값="거만남"/></무장>
			<!--좌자--><무장 번호="957"><음성 값="은근남"/></무장>
			<!--우길--><무장 번호="958"><음성 값="소심남"/></무장>
			<!--예형--><무장 번호="959"><음성 값="은근남"/></무장>
			<!--화타--><무장 번호="960"><음성 값="냉정남"/></무장>
			<!--황주호--><무장 번호="961"><음성 값="유방"/></무장>
			<!--황선율--><무장 번호="962"><음성 값="소하"/></무장>
			//신무장 음성지정 끝
			</pk>
			""");			
		}
	}

	Main main;
}