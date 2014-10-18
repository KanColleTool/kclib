#ifndef KCLIB_LKTRANSLATOR_H
#define KCLIB_LKTRANSLATOR_H

#include <functional>
#include <map>
#include <string>

/**
 * Handles translation of lines via a CRC32 lookup table.
 */
class LKTranslator
{
public:
	enum LoadStatus {
		LoadStatusNotLoaded,
		LoadStatusLoading,
		LoadStatusLoaded,
		LoadStatusError
	};
	
	LKTranslator();
	virtual ~LKTranslator();
	
	std::string translate(std::string line, std::string path = "", std::string key = "");
	
	LoadStatus loadStatus;
	std::map<uint32_t, std::string> translations;
	
	std::function<void(std::string line, std::string path, std::string key)> reportCallback;
};

#endif
