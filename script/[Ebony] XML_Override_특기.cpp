﻿namespace Ebony_XML_Override_특기
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
				
				<기사공격숲제외 값="true"/>
				<계략컷인 값="true"/>
				<초특기연전 값="true"/>
			
			//특기
				<!-- 이동력 상승(기본값: 5) -->
				<강행 값="6"/>

				<!-- 이동력 상승(기본값: 3) -->
				<행군 값="8"/>

				<!-- 이동력 상승(기본값: 4) -->
				<조타 값="10"/>

				<!-- 이동력 상승(기본값: 5) -->
				<운반 값="8"/>

				<!-- 기력 감소(기본값: 5) -->
				<소탕 값="5"/>

				<!-- 기력 감소(기본값: 20) -->
				<위풍 값="20"/>

				<!-- 기력 회복(기본값: 10) -->
				<앙양 값="30"/>

				<!-- 확률(기본값: 50) -->
				<연전 값="50"/>

				<!-- 확률(기본값: 50) -->
				<급습 값="80"/>

				<!-- 확률(기본값: 50) -->
				<강습 값="80"/>

				<!-- 확률(기본값: 50) -->
				<기각 값="75"/>

				<!-- 최소 확률(기본값: 100) -->
				<포박 값="25"/>

				<!-- 확률(기본값: 10) -->
				<강탈 값="30"/>

				<!-- 흡수율(기본값: 0.15) -->
				<심공 값=""/>

				<!-- 병력이 기준 미만일 경우 공격 무시 확률(기본값: <불굴 병력기준="3000" 확률="50"/>) -->
				<불굴 병력기준="3000" 확률="50"/>

				<!-- 피해가 기준 미만일 경우 공격 무시 확률(기본값: <금강 피해기준="500" 확률="50"/>) -->
				<금강 피해기준="750" 확률="50"/>

				<!-- 기력 회복(기본값: 5) -->
				<노발 값="20"/>

				<!-- 확률(기본값: 100) -->
				<질주 값=""/>

				<!-- 확률(기본값: 50) -->
				<맹장 값=""/>

				<!-- 기력 회복(기본값: 5) -->
				<주악 값="4"/>

				<!-- 확률(기본값: <논객 초급="100" 상급="100" 특급="20"/>) -->
				<논객 초급="100" 상급="75" 특급="20"/>

				<!-- 능력치 상승(기본값: 1) -->
				<내조 값="2"/>
			</pk>							
			""");			
		}
	}

	Main main;
}