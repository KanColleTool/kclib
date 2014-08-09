#ifndef KCLIB_LKQTNETWORKIMPL_H
#define KCLIB_LKQTNETWORKIMPL_H

#include "../LKNetworkImpl.h"
#include <QObject>
#include <QNetworkAccessManager>

class LKQtNetworkImpl : public LKNetworkImpl, public QObject
{
	Q_OBJECT
	
public:
	LKQtNetworkImpl();
	virtual ~LKQtNetworkImpl();
	
	virtual void get(const std::string &url, std::function<void(bool success, std::vector<char> body)> callback);
	virtual void post(const std::string &url, std::vector<char> body, std::function<void(bool success, std::vector<char> body)> callback);
	
protected:
	QNetworkAccessManager nm;
};

#endif
