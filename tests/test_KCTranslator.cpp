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
		REQUIRE(tl.translate("\\u90a3\\u73c2") == "Naka");
	}
}

TEST_CASE("Reporting")
{
	LKTranslator tl;
	
	int reportCallbackHits = 0;
	tl.reportCallback = [&](std::string line, std::string lastPathComponent, std::string key) {
		++reportCallbackHits;
	};
	
	SECTION("Report callback fires, and only when loaded")
	{
		tl.loadStatus = LKTranslator::LoadStatusNotLoaded;
		tl.translate("Definitely no translation", "test", "test");
		REQUIRE(reportCallbackHits == 0);
		
		tl.loadStatus = LKTranslator::LoadStatusLoading;
		tl.translate("Definitely no translation", "test", "test");
		REQUIRE(reportCallbackHits == 0);
		
		tl.loadStatus = LKTranslator::LoadStatusError;
		tl.translate("Definitely no translation", "test", "test");
		REQUIRE(reportCallbackHits == 0);
		
		tl.loadStatus = LKTranslator::LoadStatusLoaded;
		tl.translate("Definitely no translation", "test", "test");
		REQUIRE(reportCallbackHits == 1);
	}
}
