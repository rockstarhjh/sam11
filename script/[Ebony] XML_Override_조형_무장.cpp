﻿namespace Ebony_XML_Override_조형_무장
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
			/* 무장
				<조형번호 골격="" 투구="" 얼굴="" 상체="" 망토="" 팔="" 다리="" />
				<조형텍스처 투구="" 얼굴="" 상체="" 망토="" 팔="" 다리="" />
				0 창 1 사모 2 언월도 3 화극
				<노년조형번호 나이="" 골격="" 투구="" 얼굴="" 상체="" 망토="" 팔="" 다리="" />
				<노년조형텍스처 나이="" 투구="" 얼굴="" 상체="" 망토="" 팔="" 다리="" />
			*/
			pk::load_xml("""
			<pk utf8="true" trace="true">
			<!--곽가-->
			<무장 번호="63">
				<조형번호 골격="" 투구="83" 얼굴="83" 상체="01" 망토="" 팔="89" 다리="89"/>
				<조형텍스처 얼굴="Ebony_조형\곽가\83_얼굴_곽가.png" 상체="Ebony_조형\곽가\01_상체_곽가.png" 망토="" 팔="" 다리=""/>
			</무장>
			<!--허저-->
			<무장 번호="144">
				<조형번호 골격="2" 투구="10" 얼굴="10"/>
				<조형텍스처 투구="Ebony_조형\허저\10_투구_허저.png" 얼굴="Ebony_조형\허저\10_얼굴_허저.png"/>
			</무장>				
			<!--전위-->
			<무장 번호="471">
				<조형번호 골격="2" 투구="30" 얼굴="10" 망토="04"/>
				<조형텍스처 투구="Ebony_조형\전위\30_투구_전위.png" 얼굴="Ebony_조형\전위\10_얼굴_전위.png" 망토="Ebony_조형\[망토]\04_망토_Red.png"/>
			</무장>	
			/*청년 조형을 넣으려했으나 나이별로 모델링을 바꿀 수 없는 걸로 보여 주석처리
			<!--유비-->
			<무장 번호="635">
				<조형 나이="20" 골격="" 투구="5" 얼굴="5" 상체="11" 망토="11" 팔="11" 다리="11"/>
				<조형텍스처 투구="" 얼굴="" 상체="Ebony_조형\유비\청년\11_상체_유비.png" 망토="Ebony_조형\유비\청년\11_망토_유비.png" 팔="Ebony_조형\유비\청년\11_팔_유비.png" 다리="Ebony_조형\유비\청년\11_다리_유비.png"/>
				<조형 나이="40" 골격="" 투구="5" 얼굴="5" 상체="5" 망토="5" 팔="5" 다리="5"/>
				<노년조형텍스처 나이="40" 투구="" 얼굴="" 상체="Ebony_조형\유비\05_상체_유비.png" 망토="" 팔="Ebony_조형\유비\05_팔_유비.png" 다리="Ebony_조형\유비\05_다리_유비.png"/>
			*/
			</무장>
			<!--축융-->
			<무장 번호="248">
				<조형텍스처 팔="Ebony_조형\[팔]\34_팔.png" 왼손무기="Ebony_조형\[무기]\창_Yellow01.png" 오른손무기="Ebony_조형\[무기]\창_Yellow01.png"/>
			</무장>		
			<!--항적-->
			<무장 번호="810">
				<조형번호 골격="" 투구="26" 얼굴="24" 상체="06" 망토="18" 팔="06" 다리="06" 화살통="06"/>
				<조형텍스처 투구="Ebony_조형\항적\26_투구_항적.png" 얼굴="Ebony_조형\항적\24_얼굴_항적.png" 상체="Ebony_조형\항적\06_상체_항적.png" 망토="Ebony_조형\[망토]\무관3_망토_Red.png" 팔="Ebony_조형\항적\06_팔_항적.png" 다리="Ebony_조형\항적\06_다리_항적.png"/>
			</무장>
			/*<!--영포-->
			<무장 번호="812">
				<조형번호 골격="" 투구="18" 얼굴="36" 상체="00" 망토="03" 팔="75" 다리="00" />
				<조형텍스처 투구="Ebony_조형\영포\18_투구_영포.png" 얼굴="Ebony_조형\영포\36_얼굴_영포.png" 상체="Ebony_조형\영포\00_상체_영포.png" 망토="Ebony_조형\[망토]\03_망토_Blue2.png" 팔="" 다리="Ebony_조형\영포\00_다리_영포.png" />
			</무장>*/
			<!--유방-->
			<무장 번호="813">
				<조형번호 골격="" 투구="05" 얼굴="05" 상체="05" 망토="05" 팔="05" 다리="05" 화살통="05"/>
				<조형텍스처 투구="Ebony_조형\유방\05_투구_유방.png" 얼굴="Ebony_조형\유방\05_얼굴_유방.png" 상체="Ebony_조형\유방\05_상체_유방.png" 망토="" 팔="" 다리=""/>
			</무장>
			<!--양대안-->
			<무장 번호="818">
				<조형번호 골격="" 투구="26" 얼굴="83" 상체="76" 망토="03" 팔="76" 다리="76" 화살통="76"/>
				<조형텍스처 투구="Ebony_조형\양대안\26_투구_양대안.png" 얼굴="Ebony_조형\양대안\83_얼굴_양대안.png" 상체="" 망토="Ebony_조형\[망토]\03_망토_Red2.png" 팔="" 다리=""/>
			</무장>
			<!--고장공-->
			<무장 번호="820">
				<조형번호 골격="" 투구="19" 얼굴="07" 상체="76" 망토="03" 팔="76" 다리="76" 화살통="76"/>
				<조형텍스처 투구="Ebony_조형\고장공\19_투구_고장공.png" 얼굴="Ebony_조형\고장공\07_얼굴_고장공.png" 상체="Ebony_조형\[상체]\무관3_상체_판형_Red.png" 망토="Ebony_조형\[망토]\03_망토_Red.png" 팔="" 다리=""/>
			</무장>			
			<!--위지공-->
			<무장 번호="823">
				<조형번호 골격="2" 투구="27" 얼굴="10" 상체="76" 망토="-1" 팔="76" 다리="76" 화살통="76"/>
				<조형텍스처 투구="Ebony_조형\[투구]\27_투구_관모형.png" 얼굴="Ebony_조형\위지공\10_얼굴_위지공.png" 상체="Ebony_조형\[상체]\무관3_상체_사슬형_Red.png" 망토="" 팔="" 다리=""/>
			</무장>
			<!--왕릉-->
			<무장 번호="858">
				<조형번호 골격="" 투구="19" 얼굴="" 상체="" 망토="" 팔="" 다리="" 화살통=""/>
				<조형텍스처 투구="Ebony_조형\고장공\19_투구_고장공.png"/>
			</무장>
			<!--황주호-->
			<무장 번호="961">
				<조형번호 골격="" 투구="26" 얼굴="24" 상체="06" 망토="18" 팔="06" 다리="06" 화살통="06"/>
				<조형텍스처 투구="Ebony_조형\항적\26_투구_항적.png" 얼굴="Ebony_조형\항적\24_얼굴_항적.png" 상체="Ebony_조형\항적\06_상체_항적.png" 망토="Ebony_조형\[망토]\무관3_망토_Red.png" 팔="Ebony_조형\항적\06_팔_항적.png" 다리="Ebony_조형\항적\06_다리_항적.png"/>
			<!--황선율-->
			<무장 번호="962">
				<조형번호 골격="2" 투구="27" 얼굴="10" 상체="76" 망토="-1" 팔="76" 다리="76" 화살통="76"/>
				<조형텍스처 투구="Ebony_조형\[투구]\27_투구_관모형.png" 얼굴="Ebony_조형\위지공\10_얼굴_위지공.png" 상체="Ebony_조형\[상체]\무관3_상체_사슬형_Red.png" 망토="" 팔="" 다리=""/>
			</pk>
			""");			
		}
	}

	Main main;
}