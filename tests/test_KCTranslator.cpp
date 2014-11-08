#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <LKUtil.h>
#include <LKTranslator.h>

TEST_CASE("translate()")
{
	LKTranslator tl;
	tl.loadStatus = LKTranslator::LoadStatusLoaded;
	
	const char *nakasName = "\u90a3\u73c2";
	tl.translationData[crc32(0, nakasName, strlen(nakasName))] = "Naka";
	
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
