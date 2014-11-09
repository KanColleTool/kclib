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

/**
 * Escapes an Unicode string.
 * 
 * This is basically the reverse of unescape(), and will turn a string like
 * "那珂" back into "\u90A3\u73C2".
 */
std::string escape(std::string string);

/**
 * Is this string numeric?
 * 
 * That is, does it contain nothing but digits (0-9)?
 */
bool isNumeric(std::string string);

/**
 * Is this string blank?
 * 
 * That is, is it zero-length or contain nothing but whitespace?
 */
bool isBlank(std::string string);

/**
 * Calculates a crc32 checksum of the given string.
 */
uint32_t crc32(std::string str);

#endif
