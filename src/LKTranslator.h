#ifndef KCLIB_LKTRANSLATOR_H
#define KCLIB_LKTRANSLATOR_H

#include "LKNetworkImpl.h"

class LKTranslator
{
public:
	LKTranslator();
	virtual ~LKTranslator();
	
	LKNetworkImpl *netImpl;
	
	/**
	 * Requests the translation from the server.
	 * @param lang The language to fetch the translation for
	 */
	void requestTranslation(std::string lang = "en", std::function<void()> callback);
	
protected:
	/**
	 * Callback for requestTranslation().
	 * @see LKNetworkImpl::handler_fn
	 */
	void translationRequestFinished(bool success, int status, std::vector<char> body);
};

#endif
