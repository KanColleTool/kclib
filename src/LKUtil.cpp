#include "LKUtil.h"
#include <regex>
#include <algorithm>
#include <iostream>
#include <locale>
#include <codecvt>

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
