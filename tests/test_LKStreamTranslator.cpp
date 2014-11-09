#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <iostream>
#include <LKUtil.h>
#include <LKStreamTranslator.h>

TEST_CASE("Translation")
{
	LKTranslator tl;
	tl.loadStatus = LKTranslator::LoadStatusLoaded;
	tl.translationData[crc32("\u90a3\u73c2")] = "Naka";
	
	SECTION("Normal JSON")
	{
		LKStreamTranslator stl(tl);
		REQUIRE(stl.process("{\"test\":\"\\u90a3\\u73c2\"}") == "{\"test\":\"Naka\"}");
	}
	
	SECTION("With svdata=")
	{
		LKStreamTranslator stl(tl);
		REQUIRE(stl.process("svdata={\"test\":\"\\u90a3\\u73c2\"}") == "svdata={\"test\":\"Naka\"}");
	}
}
