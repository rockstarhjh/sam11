﻿namespace Ebony_XML_Override_컷인_커스텀
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
			// <!--2000--><무장 번호="">	<컷인 값="Ebony_컷인/2000.png"/></무장>
			// 초상화 번호와 같은 줄의 `무장 번호=""`에 발탁장수, 이민족, 혹은 새로 만드신 무장 번호를 반 에디터 등에서 확인해서 쓰시면 컷인이 나옵니다.
			// 무장컷인
			pk::load_xml("""
			<pk utf8="true" trace="true">
			<!--미사용 남-->
			<!--2000--><무장 번호="">	<컷인 값="Ebony_컷인/2000.png"/></무장>
			<!--2001--><무장 번호="">	<컷인 값="Ebony_컷인/2001.png"/></무장>
			<!--2002--><무장 번호="">	<컷인 값="Ebony_컷인/2002.png"/></무장>
			<!--2003--><무장 번호="">	<컷인 값="Ebony_컷인/2003.png"/></무장>
			<!--2004--><무장 번호="">	<컷인 값="Ebony_컷인/2004.png"/></무장>
			<!--2005--><무장 번호="">	<컷인 값="Ebony_컷인/2005.png"/></무장>
			<!--2006--><무장 번호="">	<컷인 값="Ebony_컷인/2006.png"/></무장>
			<!--2007--><무장 번호="">	<컷인 값="Ebony_컷인/2007.png"/></무장>
			<!--2008--><무장 번호="">	<컷인 값="Ebony_컷인/2008.png"/></무장>
			<!--2009--><무장 번호="">	<컷인 값="Ebony_컷인/2009.png"/></무장>
			<!--2010--><무장 번호="">	<컷인 값="Ebony_컷인/2010.png"/></무장>
			<!--2011--><무장 번호="">	<컷인 값="Ebony_컷인/2011.png"/></무장>
			<!--2012--><무장 번호="">	<컷인 값="Ebony_컷인/2012.png"/></무장>
			<!--2013--><무장 번호="">	<컷인 값="Ebony_컷인/2013.png"/></무장>
			<!--2014--><무장 번호="">	<컷인 값="Ebony_컷인/2014.png"/></무장>
			<!--2015--><무장 번호="">	<컷인 값="Ebony_컷인/2015.png"/></무장>
			<!--2016--><무장 번호="">	<컷인 값="Ebony_컷인/2016.png"/></무장>
			<!--2017--><무장 번호="">	<컷인 값="Ebony_컷인/2017.png"/></무장>
			<!--2018--><무장 번호="">	<컷인 값="Ebony_컷인/2018.png"/></무장>
			<!--2019--><무장 번호="">	<컷인 값="Ebony_컷인/2019.png"/></무장>
			<!--2020--><무장 번호="">	<컷인 값="Ebony_컷인/2020.png"/></무장>
			<!--2021--><무장 번호="">	<컷인 값="Ebony_컷인/2021.png"/></무장>
			<!--2022--><무장 번호="">	<컷인 값="Ebony_컷인/2022.png"/></무장>
			<!--2023--><무장 번호="">	<컷인 값="Ebony_컷인/2023.png"/></무장>
			<!--2024--><무장 번호="">	<컷인 값="Ebony_컷인/2024.png"/></무장>
			<!--2025--><무장 번호="">	<컷인 값="Ebony_컷인/2025.png"/></무장>
			<!--2026--><무장 번호="">	<컷인 값="Ebony_컷인/2026.png"/></무장>
			<!--2027--><무장 번호="">	<컷인 값="Ebony_컷인/2027.png"/></무장>
			<!--2028--><무장 번호="">	<컷인 값="Ebony_컷인/2028.png"/></무장>
			<!--2029--><무장 번호="">	<컷인 값="Ebony_컷인/2029.png"/></무장>
			<!--2030--><무장 번호="">	<컷인 값="Ebony_컷인/2030.png"/></무장>
			<!--2031--><무장 번호="">	<컷인 값="Ebony_컷인/2031.png"/></무장>
			<!--2032--><무장 번호="">	<컷인 값="Ebony_컷인/2032.png"/></무장>
			<!--2033--><무장 번호="">	<컷인 값="Ebony_컷인/2033.png"/></무장>
			<!--2034--><무장 번호="">	<컷인 값="Ebony_컷인/2034.png"/></무장>
			<!--2035--><무장 번호="">	<컷인 값="Ebony_컷인/2035.png"/></무장>
			<!--2036--><무장 번호="">	<컷인 값="Ebony_컷인/2036.png"/></무장>
			<!--2037--><무장 번호="">	<컷인 값="Ebony_컷인/2037.png"/></무장>
			<!--2038--><무장 번호="">	<컷인 값="Ebony_컷인/2038.png"/></무장>
			<!--2039--><무장 번호="">	<컷인 값="Ebony_컷인/2039.png"/></무장>
			<!--2040--><무장 번호="">	<컷인 값="Ebony_컷인/2040.png"/></무장>
			<!--2041--><무장 번호="">	<컷인 값="Ebony_컷인/2041.png"/></무장>
			<!--2042--><무장 번호="">	<컷인 값="Ebony_컷인/2042.png"/></무장>
			<!--2043--><무장 번호="">	<컷인 값="Ebony_컷인/2043.png"/></무장>
			<!--2044--><무장 번호="">	<컷인 값="Ebony_컷인/2044.png"/></무장>
			<!--2045--><무장 번호="">	<컷인 값="Ebony_컷인/2045.png"/></무장>
			<!--2046--><무장 번호="">	<컷인 값="Ebony_컷인/2046.png"/></무장>
			<!--2047--><무장 번호="">	<컷인 값="Ebony_컷인/2047.png"/></무장>
			<!--2048--><무장 번호="">	<컷인 값="Ebony_컷인/2048.png"/></무장>
			<!--2049--><무장 번호="">	<컷인 값="Ebony_컷인/2049.png"/></무장>
			<!--2050--><무장 번호="">	<컷인 값="Ebony_컷인/2050.png"/></무장>
			<!--2051--><무장 번호="">	<컷인 값="Ebony_컷인/2051.png"/></무장>
			<!--2052--><무장 번호="">	<컷인 값="Ebony_컷인/2052.png"/></무장>
			<!--2053--><무장 번호="">	<컷인 값="Ebony_컷인/2053.png"/></무장>
			<!--2054--><무장 번호="">	<컷인 값="Ebony_컷인/2054.png"/></무장>
			<!--2055--><무장 번호="">	<컷인 값="Ebony_컷인/2055.png"/></무장>
			<!--2056--><무장 번호="">	<컷인 값="Ebony_컷인/2056.png"/></무장>
			<!--2057--><무장 번호="">	<컷인 값="Ebony_컷인/2057.png"/></무장>
			<!--2058--><무장 번호="">	<컷인 값="Ebony_컷인/2058.png"/></무장>
			<!--2059--><무장 번호="">	<컷인 값="Ebony_컷인/2059.png"/></무장>
			<!--2060--><무장 번호="">	<컷인 값="Ebony_컷인/2060.png"/></무장>
			<!--2061--><무장 번호="">	<컷인 값="Ebony_컷인/2061.png"/></무장>
			<!--2062--><무장 번호="">	<컷인 값="Ebony_컷인/2062.png"/></무장>
			<!--2063--><무장 번호="">	<컷인 값="Ebony_컷인/2063.png"/></무장>
			<!--2064--><무장 번호="">	<컷인 값="Ebony_컷인/2064.png"/></무장>
			<!--2065--><무장 번호="">	<컷인 값="Ebony_컷인/2065.png"/></무장>
			<!--2066--><무장 번호="">	<컷인 값="Ebony_컷인/2066.png"/></무장>
			<!--2067--><무장 번호="">	<컷인 값="Ebony_컷인/2067.png"/></무장>
			<!--2068--><무장 번호="">	<컷인 값="Ebony_컷인/2068.png"/></무장>
			<!--2069--><무장 번호="">	<컷인 값="Ebony_컷인/2069.png"/></무장>
			<!--2070--><무장 번호="">	<컷인 값="Ebony_컷인/2070.png"/></무장>
			<!--2071--><무장 번호="">	<컷인 값="Ebony_컷인/2071.png"/></무장>
			<!--2072--><무장 번호="">	<컷인 값="Ebony_컷인/2072.png"/></무장>
			<!--2073--><무장 번호="">	<컷인 값="Ebony_컷인/2073.png"/></무장>
			<!--2074--><무장 번호="">	<컷인 값="Ebony_컷인/2074.png"/></무장>
			<!--2075--><무장 번호="">	<컷인 값="Ebony_컷인/2075.png"/></무장>
			<!--2076--><무장 번호="">	<컷인 값="Ebony_컷인/2076.png"/></무장>
			<!--2077--><무장 번호="">	<컷인 값="Ebony_컷인/2077.png"/></무장>
			<!--2078--><무장 번호="">	<컷인 값="Ebony_컷인/2078.png"/></무장>
			<!--2079--><무장 번호="">	<컷인 값="Ebony_컷인/2079.png"/></무장>
			<!--2080--><무장 번호="">	<컷인 값="Ebony_컷인/2080.png"/></무장>
			<!--2081--><무장 번호="">	<컷인 값="Ebony_컷인/2081.png"/></무장>
			<!--2082--><무장 번호="">	<컷인 값="Ebony_컷인/2082.png"/></무장>
			<!--2083--><무장 번호="">	<컷인 값="Ebony_컷인/2083.png"/></무장>
			<!--2084--><무장 번호="">	<컷인 값="Ebony_컷인/2084.png"/></무장>
			<!--2085--><무장 번호="">	<컷인 값="Ebony_컷인/2085.png"/></무장>
			<!--2086--><무장 번호="">	<컷인 값="Ebony_컷인/2086.png"/></무장>
			<!--2087--><무장 번호="">	<컷인 값="Ebony_컷인/2087.png"/></무장>
			<!--2088--><무장 번호="">	<컷인 값="Ebony_컷인/2088.png"/></무장>
			<!--미사용 여-->
			<!--2100--><무장 번호="">	<컷인 값="Ebony_컷인/2100.png"/></무장>
			<!--2101--><무장 번호="">	<컷인 값="Ebony_컷인/2101.png"/></무장>
			<!--2102--><무장 번호="">	<컷인 값="Ebony_컷인/2102.png"/></무장>
			<!--2103--><무장 번호="">	<컷인 값="Ebony_컷인/2103.png"/></무장>
			<!--2104--><무장 번호="">	<컷인 값="Ebony_컷인/2104.png"/></무장>
			<!--2105--><무장 번호="">	<컷인 값="Ebony_컷인/2105.png"/></무장>
			<!--2106--><무장 번호="">	<컷인 값="Ebony_컷인/2106.png"/></무장>
			<!--2107--><무장 번호="">	<컷인 값="Ebony_컷인/2107.png"/></무장>
			<!--2108--><무장 번호="">	<컷인 값="Ebony_컷인/2108.png"/></무장>
			<!--2109--><무장 번호="">	<컷인 값="Ebony_컷인/2109.png"/></무장>
			<!--2110--><무장 번호="">	<컷인 값="Ebony_컷인/2110.png"/></무장>
			<!--2111--><무장 번호="">	<컷인 값="Ebony_컷인/2111.png"/></무장>
			<!--2112--><무장 번호="">	<컷인 값="Ebony_컷인/2112.png"/></무장>
			<!--2113--><무장 번호="">	<컷인 값="Ebony_컷인/2113.png"/></무장>
			<!--2114--><무장 번호="">	<컷인 값="Ebony_컷인/2114.png"/></무장>
			<!--2115--><무장 번호="">	<컷인 값="Ebony_컷인/2115.png"/></무장>
			<!--2116--><무장 번호="">	<컷인 값="Ebony_컷인/2116.png"/></무장>
			<!--2117--><무장 번호="">	<컷인 값="Ebony_컷인/2117.png"/></무장>
			<!--2118--><무장 번호="">	<컷인 값="Ebony_컷인/2118.png"/></무장>
			<!--2119--><무장 번호="">	<컷인 값="Ebony_컷인/2119.png"/></무장>
			<!--2120--><무장 번호="">	<컷인 값="Ebony_컷인/2120.png"/></무장>
			<!--2121--><무장 번호="">	<컷인 값="Ebony_컷인/2121.png"/></무장>
			<!--2122--><무장 번호="">	<컷인 값="Ebony_컷인/2122.png"/></무장>
			<!--2123--><무장 번호="">	<컷인 값="Ebony_컷인/2123.png"/></무장>
			<!--2124--><무장 번호="">	<컷인 값="Ebony_컷인/2124.png"/></무장>
			<!--2125--><무장 번호="">	<컷인 값="Ebony_컷인/2125.png"/></무장>
			<!--2126--><무장 번호="">	<컷인 값="Ebony_컷인/2126.png"/></무장>
			<!--2127--><무장 번호="">	<컷인 값="Ebony_컷인/2127.png"/></무장>
			<!--2128--><무장 번호="">	<컷인 값="Ebony_컷인/2128.png"/></무장>
			<!--2129--><무장 번호="">	<컷인 값="Ebony_컷인/2129.png"/></무장>
			<!--2130--><무장 번호="">	<컷인 값="Ebony_컷인/2130.png"/></무장>
			<!--2131--><무장 번호="">	<컷인 값="Ebony_컷인/2131.png"/></무장>
			<!--2132--><무장 번호="">	<컷인 값="Ebony_컷인/2132.png"/></무장>
			<!--2133--><무장 번호="">	<컷인 값="Ebony_컷인/2133.png"/></무장>
			<!--2134--><무장 번호="">	<컷인 값="Ebony_컷인/2134.png"/></무장>
			<!--2135--><무장 번호="">	<컷인 값="Ebony_컷인/2135.png"/></무장>
			<!--2136--><무장 번호="">	<컷인 값="Ebony_컷인/2136.png"/></무장>
			<!--2137--><무장 번호="">	<컷인 값="Ebony_컷인/2137.png"/></무장>
			<!--2138--><무장 번호="">	<컷인 값="Ebony_컷인/2138.png"/></무장>
			<!--2139--><무장 번호="">	<컷인 값="Ebony_컷인/2139.png"/></무장>
			<!--2140--><무장 번호="">	<컷인 값="Ebony_컷인/2140.png"/></무장>
			<!--2141--><무장 번호="">	<컷인 값="Ebony_컷인/2141.png"/></무장>
			<!--2142--><무장 번호="">	<컷인 값="Ebony_컷인/2142.png"/></무장>
			<!--2143--><무장 번호="">	<컷인 값="Ebony_컷인/2143.png"/></무장>
			<!--2144--><무장 번호="">	<컷인 값="Ebony_컷인/2144.png"/></무장>
			<!--2145--><무장 번호="">	<컷인 값="Ebony_컷인/2145.png"/></무장>
			<!--2146--><무장 번호="">	<컷인 값="Ebony_컷인/2146.png"/></무장>
			<!--2147--><무장 번호="">	<컷인 값="Ebony_컷인/2147.png"/></무장>
			<!--2148--><무장 번호="">	<컷인 값="Ebony_컷인/2148.png"/></무장>
			<!--2149--><무장 번호="">	<컷인 값="Ebony_컷인/2149.png"/></무장>
			<!--2150--><무장 번호="">	<컷인 값="Ebony_컷인/2150.png"/></무장>
			<!--2151--><무장 번호="">	<컷인 값="Ebony_컷인/2151.png"/></무장>
			<!--2152--><무장 번호="">	<컷인 값="Ebony_컷인/2152.png"/></무장>
			<!--2153--><무장 번호="">	<컷인 값="Ebony_컷인/2153.png"/></무장>
			<!--2154--><무장 번호="">	<컷인 값="Ebony_컷인/2154.png"/></무장>
			<!--2155--><무장 번호="">	<컷인 값="Ebony_컷인/2155.png"/></무장>
			<!--2156--><무장 번호="">	<컷인 값="Ebony_컷인/2156.png"/></무장>
			<!--2157--><무장 번호="">	<컷인 값="Ebony_컷인/2157.png"/></무장>
			<!--2158--><무장 번호="">	<컷인 값="Ebony_컷인/2158.png"/></무장>
			<!--2159--><무장 번호="">	<컷인 값="Ebony_컷인/2159.png"/></무장>
			<!--2160--><무장 번호="">	<컷인 값="Ebony_컷인/2160.png"/></무장>
			<!--2161--><무장 번호="">	<컷인 값="Ebony_컷인/2161.png"/></무장>
			<!--2162--><무장 번호="">	<컷인 값="Ebony_컷인/2162.png"/></무장>
			<!--2163--><무장 번호="">	<컷인 값="Ebony_컷인/2163.png"/></무장>
			<!--2164--><무장 번호="">	<컷인 값="Ebony_컷인/2164.png"/></무장>
			</pk>
			""");			
		}
	}

	Main main;
}