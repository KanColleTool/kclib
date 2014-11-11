#include "LKTranslator.h"
#include "LKUtil.h"

std::string LKTranslator::translate(std::string line, std::string lastPathComponent, std::string jsonKey)
{
	// Ignore blank or numeric lines
	if(isBlank(line) || isNumeric(line))
		return line;
	
	std::string realLine = unescape(line);
	uint32_t crc = crc32(realLine.c_str());
	
	auto it = translationData.find(crc);
	if(it != translationData.end())
		return it->second;
	else
		this->handleUntranslatedLine(realLine, lastPathComponent, jsonKey);
	
	return line;
}

void LKTranslator::handleUntranslatedLine(std::string line, std::string lastPathComponent, std::string jsonKey)
{
	// We can't report lines that don't have any context to them...
	// (Which should never, ever happen under normal usage!)
	if(lastPathComponent.size() == 0 || jsonKey.size() == 0)
		return;
	
	// We're not reporting anything until we have a blacklist to check against
	if(blacklistLoadStatus != LoadStatusLoaded)
	{
		backlog.push_back({line, lastPathComponent, jsonKey});
		return;
	}
	
	// Go through the backlog upon receiving the blacklist, if there is one
	if(backlog.size() > 0)
	{
		// Clear it first, to prevent an infinite loop
		std::deque<BacklogEntry> backlog_copy = backlog;
		backlog.clear();
		
		// Re-handle every line in it
		for(BacklogEntry &entry : backlog_copy)
			this->handleUntranslatedLine(entry.line, entry.lastPathComponent, entry.jsonKey);
	}
	
	// Check the blacklist
	auto pathBlacklistIt = blacklist.find(lastPathComponent);
	auto wildcardBlacklistIt = blacklist.find("*");
	if(pathBlacklistIt != blacklist.end())
	{
		if(pathBlacklistIt->second.count("*") > 0)
			return; // Path blacklist rejects everything
		if(pathBlacklistIt->second.count(jsonKey) > 0)
			return; // Rejected by path blacklist
	}
	if(wildcardBlacklistIt != blacklist.end() && wildcardBlacklistIt->second.count(jsonKey) > 0)
		return; // Key is rejected globally
	
	if(loadStatus == LoadStatusLoaded && reportCallback)
		reportCallback(line, lastPathComponent, jsonKey);
}
