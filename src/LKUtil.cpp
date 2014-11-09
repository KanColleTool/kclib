#include "LKUtil.h"
#include <regex>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <locale>
#include <codecvt>
#include "crc32.h"

std::string unescape(std::string str)
{
	// Make a regex that matches all \uXXXX sequences
	std::regex re("\\\\u[0-9a-fA-F]{4}");
	std::sregex_iterator begin(str.begin(), str.end(), re);
	std::sregex_iterator end;
	
	// We need a second string to replace in, and keep track of the position
	// shift caused by replacing ranges with strings of a different length
	std::string retval(str);
	int offset = 0;
	
	// Loop through all the matches
	for(std::sregex_iterator it = begin; it != end; it++)
	{
		// Convert the match into a char32_t, and go from there to a u32string
		// Thank you, C++11, these things - it'd be incredibly painful in C++03
		const std::smatch &match = *it;
		char32_t ch = stoi(match.str().substr(2), nullptr, 16);
		std::u32string s32(&ch, 1);
		
		// Use a codec to convert from std::u32string to std::string
		std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;
		std::string s = convert.to_bytes(s32);
		
		// Replace in the output string, keeping track of position shifts
		retval.replace(match.position() + offset, match.length(), s);
		offset += s.size() - match.length();
	}
	
	return retval;
}

std::string escape(std::string str)
{
	// Convert the unescaped string into a u32string, so that we can treat it
	// as an UTF-32 array, and loop over one of any character at a time - as
	// opposed to one _char_ at a time, as with std::string; one char is not a
	// meaningful representation of anything outside of ASCII.
	std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;
	std::u32string s32 = convert.from_bytes(str);
	
	// Use a hex-mode std::stringstream for free formatting of anything outside
	// of the ASCII range (character codes 0-255); just remember the \u prefix
	std::stringstream ss;
	ss << std::hex;
	for(auto it = s32.begin(); it != s32.end(); it++)
	{
		char32_t &c = *it;
		if(c <= 255)
			ss << static_cast<char>(c);
		else
			ss << "\\u" << c;
	}
	
	return ss.str();
}

bool isNumeric(std::string str)
{
	// Empty strings are definitely not numeric
	if(str.size() == 0)
		return false;
	
	// If the string contains anything not a digit or blank, it's not numeric
	for(auto it = str.begin(); it != str.end(); it++)
		if(!std::isblank(*it) && !std::isdigit(*it))
			return false;
	
	return true;
}

bool isBlank(std::string str)
{
	// If the string contains anything but blank characters, it's not blank
	for(auto it = str.begin(); it != str.end(); it++)
		if(!std::isblank(*it))
			return false;
	
	return true;
}

uint32_t crc32(std::string str)
{
	const char *cstr = str.c_str();
	return _crc32(0, cstr, strlen(cstr));
}
