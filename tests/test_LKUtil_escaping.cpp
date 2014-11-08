#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <iostream>
#include <LKUtil.h>

TEST_CASE("Can unescape Naka-chan's name")
{
	std::string s1("\u90a3\u73c2");
	std::string s2 = unescape("\\u90a3\\u73c2");
	
	REQUIRE(s1 == s2);
}

TEST_CASE("Can unescape a sentence with Naka-chan's name")
{
	std::string s1("...\u90a3\u73c2-chan dayo~");
	std::string s2 = unescape("...\\u90a3\\u73c2-chan dayo~");
	
	REQUIRE(s1 == s2);
}

TEST_CASE("Can escape Naka-chan's name")
{
	std::string s1("\\u90a3\\u73c2");
	std::string s2 = escape("\u90a3\u73c2");
	
	REQUIRE(s1 == s2);
}

TEST_CASE("Can escape a sentence with Naka-chan's name")
{
	std::string s1("...\\u90a3\\u73c2-chan dayo~");
	std::string s2 = escape("...\u90a3\u73c2-chan dayo~");
	
	REQUIRE(s1 == s2);
}
