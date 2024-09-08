﻿namespace Ebony_XML_Override_무장
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
			<조형번호 골격="" 투구="" 얼굴="" 상체="" 망토="" 팔="" 다리="" 화살통="" 왼손무기="" 오른손무기="" 말=""/>
			<조형텍스처 투구="" 얼굴="" 상체="" 망토="" 팔="" 다리="" 화살통="" 왼손무기="Ebony_조형\[무기]\" 오른손무기="Ebony_조형\[무기]\" 말=""/>
			0 창 1 사모 2 언월도 3 화극
			<노년조형번호 나이="" 골격="" 투구="" 얼굴="" 상체="" 망토="" 팔="" 다리="" 화살통=""/>
			<노년조형텍스처 나이="" 투구="" 얼굴="" 상체="" 망토="" 팔="" 다리="" 화살통=""/>
			*/
			pk::load_xml("""
			<pk utf8="true" trace="true">		
			<!--항적-->
			<무장 번호="810">
				<부가무력 값="12"/><전법성공확률보너스 값="5"/><지원공격확률보너스 값="-5"/><특기 값="위풍"/><위풍 값="10"/>
			</무장>
			<!--조운-->
			<무장 번호="395">
				<부가무력 값="5"/><특기 값="창신,통찰"/><전법성공확률보너스 값="5"/><지원공격확률보너스 값="5"/>
			</무장>
			<!--관우-->
			<무장 번호="98">
				<부가무력 값="5"/><전법성공확률보너스 값="5"/><지원공격확률보너스 값="5"/>
			</무장>
			<!--장비-->
			<무장 번호="432">
				<부가무력 값="5"/><전법성공확률보너스 값="5"/><지원공격확률보너스 값="5"/>
			</무장>	
			<!--마초-->
			<무장 번호="515">
				<부가무력 값="5"/><전법성공확률보너스 값="5"/><지원공격확률보너스 값="5"/>
			</무장>
			<!--황충-->
			<무장 번호="185">
				<부가무력 값="5"/><전법성공확률보너스 값="5"/><지원공격확률보너스 값="5"/>
			</무장>
			<!--조인-->
			<무장 번호="341">
				<특기 값="철벽,금강"/>
			</무장>
					
			</pk>
			""");			
		}
	}

	Main main;
}