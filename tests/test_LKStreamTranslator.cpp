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
		REQUIRE(LKStreamTranslator(tl).process("{\"test\":\"\\u90a3\\u73c2\"}") == "{\"test\":\"Naka\"}");
	}
	
	SECTION("With svdata=")
	{
		REQUIRE(LKStreamTranslator(tl).process("svdata={\"test\":\"\\u90a3\\u73c2\"}") == "svdata={\"test\":\"Naka\"}");
	}
	
	SECTION("Empty/invalid strings")
	{
		REQUIRE(LKStreamTranslator(tl).process("") == "");
		REQUIRE_THROWS(LKStreamTranslator(tl).process("{\"dsfgg\": b}"));
	}
	
	SECTION("Chunks")
	{
		LKStreamTranslator stl(tl);
		std::string output = "";
		
		output += stl.process("{\"");
		output += stl.process("te");
		output += stl.process("");
		output += stl.process("st\":\"\\");
		output += stl.process("u90a3\\u73c2\"");
		output += stl.process("}");
		
		REQUIRE(output == "{\"test\":\"Naka\"}");
	}
}
