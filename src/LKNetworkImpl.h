#ifndef KCLIB_LKNETWORKIMPL_H
#define KCLIB_LKNETWORKIMPL_H

#include <string>
#include <vector>
#include <functional>

class LKNetworkImpl
{
public:
	typedef std::function<void(bool success, int status, std::vector<char> body)> handler_fn;
	
	LKNetworkImpl() {};
	virtual ~LKNetworkImpl() {};
	
	virtual void get(const std::string &url, handler_fn callback) = 0;
	virtual void post(const std::string &url, std::string body, handler_fn callback) = 0;
};

#endif
