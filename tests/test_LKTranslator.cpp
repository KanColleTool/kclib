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
	tl.loadStatus = LKTranslator::LoadStatusLoaded;
	tl.blacklistLoadStatus = LKTranslator::LoadStatusLoaded;
	
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

TEST_CASE("Blacklisting")
{
	LKTranslator tl;
	tl.loadStatus = LKTranslator::LoadStatusLoaded;
	tl.blacklist["test"] = { "blacklisted" };
	tl.blacklist["wcblacklisted"] = { "*" };
	tl.blacklist["*"] = { "wcblacklisted" };
	
	int reportCallbackHits = 0;
	tl.reportCallback = [&](std::string line, std::string lastPathComponent, std::string key) {
		++reportCallbackHits;
	};
	
	SECTION("Report callback does not fire without a blacklist loaded")
	{
		for(int i = LKTranslator::LoadStatusNotLoaded; i < (int)LKTranslator::LoadStatusError; i++)
		{
			reportCallbackHits = 0;
			tl.blacklistLoadStatus = (LKTranslator::LoadStatus)LKTranslator::LoadStatusNotLoaded;
			tl.translate("Definitely no translation", "test", "test");
			REQUIRE(reportCallbackHits == (tl.blacklistLoadStatus == LKTranslator::LoadStatusLoaded ? 1 : 0));
		}
	}
	
	SECTION("Blacklisting works properly")
	{
		tl.blacklistLoadStatus = LKTranslator::LoadStatusLoaded;
		
		reportCallbackHits = 0;
		tl.translate("Definitely no translation", "test", "test");
		REQUIRE(reportCallbackHits == 1);
		
		reportCallbackHits = 0;
		tl.translate("Definitely no translation", "test", "blacklisted");
		REQUIRE(reportCallbackHits == 0);
		
		reportCallbackHits = 0;
		tl.translate("Definitely no translation", "wcblacklisted", "qwerty");
		REQUIRE(reportCallbackHits == 0);
		
		reportCallbackHits = 0;
		tl.translate("Definitely no translation", "qwerty", "wcblacklisted");
		REQUIRE(reportCallbackHits == 0);
	}
}

TEST_CASE("Backlog")
{
	LKTranslator tl;
	tl.loadStatus = LKTranslator::LoadStatusLoaded;
	
	int reportCallbackHits = 0;
	tl.reportCallback = [&](std::string line, std::string lastPathComponent, std::string key) {
		++reportCallbackHits;
	};
	
	tl.translate("Line 1", "test", "test");
	tl.translate("Line 2", "test", "test");
	tl.translate("Line 3", "test", "test");
	REQUIRE(reportCallbackHits == 0);
	
	tl.blacklistLoadStatus = LKTranslator::LoadStatusLoaded;
	
	tl.translate("Final line", "test", "test");
	REQUIRE(reportCallbackHits == 4);
}
