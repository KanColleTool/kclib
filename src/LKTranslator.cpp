#include "LKTranslator.h"
#include <functional>
#include <sstream>
#include <iostream>

LKTranslator::LKTranslator():
	netImpl(LKNetworkImpl::create())
{
	
}

LKTranslator::~LKTranslator()
{
	
}

void LKTranslator::requestTranslation(std::string lang, std::function<void()> callback)
{
	std::stringstream ss;
	ss << "http://api.comeonandsl.am/translation/" << lang << "/";
	
	netImpl->get(ss.str(), [=](bool success, int status, std::vector<char> body) {
		std::cout << "Received translation data!" << std::endl;
		std::cout << "Status: " << (success ? "Success" : "Failure") << " (" << status << ")" << std::endl;
	});
}

void LKTranslator::translationRequestFinished(bool success, int status, std::vector<char> body)
{
	std::cout << "Received translation data!" << std::endl;
	std::cout << "Status: " << (success ? "Success" : "Failure") << " (" << status << ")" << std::endl;
}
