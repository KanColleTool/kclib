#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <iostream>
#include <LKUtil.h>

TEST_CASE("unescape()")
{
	std::string naka = "\u90a3\u73c2";
	std::string nakaEscaped = "\\u90a3\\u73c2";
	
	std::string sentencePrefix = "Waai! ";
	std::string sentenceSuffix = "-chan dayo!";
	
	std::string sentence = sentencePrefix + naka + sentenceSuffix;
	std::string sentenceEscaped = sentencePrefix + nakaEscaped + sentenceSuffix;
	
	SECTION("Can unescape Naka-chan's name")
	{
		REQUIRE(unescape(nakaEscaped) == naka);
	}
	
	SECTION("Can escape Naka-chan's name")
	{
		REQUIRE(escape(naka) == nakaEscaped);
	}
	
	SECTION("Can unescape a sentence with Naka-chan's name in it")
	{
		REQUIRE(unescape(sentenceEscaped) == sentence);
	}
	
	SECTION("Can escape a sentence with Naka's name in it")
	{
		REQUIRE(escape(sentence) == sentenceEscaped);
	}
}
