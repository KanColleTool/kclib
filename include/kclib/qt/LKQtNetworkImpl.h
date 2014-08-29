#ifndef KCLIB_LKQTNETWORKIMPL_H
#define KCLIB_LKQTNETWORKIMPL_H

#include "../LKNetworkImpl.h"
#include <QObject>
#include <QNetworkAccessManager>

class LKQtNetworkImpl : public LKNetworkImpl, public QObject
{
	Q_OBJECT
	
public:
	typedef std::function<void(bool success, std::vector<char> body)> handler_fn;
	
	LKQtNetworkImpl();
	virtual ~LKQtNetworkImpl();
	
	virtual void get(const std::string &url, handler_fn callback);
	virtual void post(const std::string &url, std::vector<char> body, handler_fn callback);
	
	// For testing purposes only!
	bool synchronous = false;
	
protected:
	void _registerReply(QNetworkReply *reply, handler_fn callback);
	
	QMap<QNetworkReply*,handler_fn> handlers;
	QNetworkAccessManager nm;
	
protected slots:
	void onRequestFinished(QNetworkReply *reply);
};

#endif
