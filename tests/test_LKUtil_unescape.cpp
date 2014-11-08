#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <iostream>
#include <LKUtil.h>

TEST_CASE("Can unescape Naka-chan's name")
{
	std::string s1("\u90A3\u73C2");
	std::string s2 = unescape("\\u90A3\\u73C2");
	
	REQUIRE(s1 == s2);
}

TEST_CASE("Can unescape a sentence with Naka-chan's name")
{
	std::string s1("...\u90A3\u73C2-chan dayo~");
	std::string s2 = unescape("...\\u90A3\\u73C2-chan dayo~");
	
	REQUIRE(s1 == s2);
}
