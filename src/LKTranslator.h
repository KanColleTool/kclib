#ifndef KCLIB_LKTRANSLATOR_H
#define KCLIB_LKTRANSLATOR_H

#include "LKNetworkImpl.h"

class LKTranslator
{
public:
	LKTranslator(LKNetworkImpl *netImpl);
	virtual ~LKTranslator();
	
	LKNetworkImpl *netImpl;
};

#endif
