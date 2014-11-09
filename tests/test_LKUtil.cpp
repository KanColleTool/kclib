#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <iostream>
#include <LKUtil.h>

TEST_CASE("unescape()/escape()")
{
	std::string naka = "\u90a3\u73c2";
	std::string nakaEscaped = "\\u90a3\\u73c2";
	
	std::string sentencePrefix = "Waai! ";
	std::string sentenceSuffix = "-chan dayo!";
	
	std::string sentence = sentencePrefix + naka + sentenceSuffix;
	std::string sentenceEscaped = sentencePrefix + nakaEscaped + sentenceSuffix;
	
	SECTION("Can unescape things")
	{
		REQUIRE(unescape(nakaEscaped) == naka);
		REQUIRE(unescape(sentenceEscaped) == sentence);
	}
	
	SECTION("Can escape things")
	{
		REQUIRE(escape(naka) == nakaEscaped);
		REQUIRE(escape(sentence) == sentenceEscaped);
	}
}

TEST_CASE("isNumeric()")
{
	REQUIRE_FALSE(isNumeric(""));
	REQUIRE_FALSE(isNumeric("qwertyuiop"));
	
	REQUIRE(isNumeric("1234567890"));
}

TEST_CASE("isBlank()")
{
	REQUIRE_FALSE(isBlank("qwertyuiop"));
	REQUIRE(isBlank(""));
	REQUIRE(isBlank(" "));
	REQUIRE(isBlank("\t"));
}

TEST_CASE("crc32()")
{
	REQUIRE(crc32("\u90a3\u73c2") == 124853853);
}
