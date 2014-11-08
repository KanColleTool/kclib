#ifndef KCLIB_LKUTIL_H
#define KCLIB_LKUTIL_H

#include <string>

/**
 * Unescapes an Unicode-escaped string.
 * 
 * This will replace any \uXXXX escapes with its corresponding character, eg.
 * unescape("\u90A3\u73C2") -> 那珂. Works with UTF32 internally, then converts
 * to std::string's native encoding, which should cover just about everything.
 */
std::string unescape(std::string string);

#endif
