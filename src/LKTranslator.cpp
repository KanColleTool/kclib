#include "LKTranslator.h"
#include "LKUtil.h"

std::string LKTranslator::translate(std::string line, std::string lastPathComponent, std::string jsonKey)
{
	// Ignore blank or numeric lines
	if(isBlank(line) || isNumeric(line))
		return line;
	
	std::string real_line = unescape(line);
	uint32_t crc = crc32(real_line.c_str());
	
	auto it = translationData.find(crc);
	if(it != translationData.end())
		return it->second;
	
	return line;
}
