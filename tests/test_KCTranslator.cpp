#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <LKUtil.h>
#include <LKTranslator.h>

TEST_CASE("Translation")
{
	LKTranslator tl;
	tl.loadStatus = LKTranslator::LoadStatusLoaded;
	tl.translationData[crc32("\u90a3\u73c2")] = "Naka";
	
	SECTION("Unknown lines are left alone")
	{
		REQUIRE(tl.translate("Test") == "Test");
	}
	
	SECTION("Can translate Naka's name")
	{
		REQUIRE(tl.translate("\u90a3\u73c2") == "Naka");
	}
	
	SECTION("Can translate Naka's name, when escaped")
	{
		REQUIRE(tl.translate("\\u90a3\\u73c2") == "Naka");
	}
}
