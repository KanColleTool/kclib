#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <LKUtil.h>
#include <LKTranslator.h>

TEST_CASE("Translation")
{
	LKTranslator tl;
	tl.loadStatus = LKTranslator::LoadStatusLoaded;
	tl.translationData[crc32("\u90a3\u73c2")] = "Naka";
	tl.translationData[crc32("123")] = "Fail";
	tl.translationData[crc32("")] = "Fail";
	
	SECTION("Unknown and invalid lines are left alone")
	{
		REQUIRE(tl.translate("Test") == "Test");
		REQUIRE(tl.translate("123") == "123");
		REQUIRE(tl.translate("") == "");
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
