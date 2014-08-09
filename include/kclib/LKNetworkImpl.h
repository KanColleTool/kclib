#ifndef KCLIB_LKNETWORKIMPL_H
#define KCLIB_LKNETWORKIMPL_H

#include <string>
#include <vector>
#include <functional>

class LKNetworkImpl
{
public:
	LKNetworkImpl() {};
	virtual ~LKNetworkImpl() {};
	
	virtual void get(const std::string &url, std::function<void(bool success, std::vector<char> body)> callback) = 0;
	virtual void post(const std::string &url, std::vector<char> body, std::function<void(bool success, std::vector<char> body)> callback) = 0;
};

#endif
