#ifndef KCLIB_LKQTNETWORKIMPL_H
#define KCLIB_LKQTNETWORKIMPL_H

#include "../LKNetworkImpl.h"
#include <QObject>
#include <QNetworkAccessManager>

class LKQtNetworkImpl : public QObject, public LKNetworkImpl
{
	Q_OBJECT
	
public:
	virtual void get(const std::string &url, handler_fn callback) override;
	virtual void post(const std::string &url, std::string body, handler_fn callback) override;
	
	// For testing purposes only!
	bool synchronous = false;
	
protected:
	void _registerReply(QNetworkReply *reply, handler_fn callback);
	
	QMap<QNetworkReply*,handler_fn> handlers;
	QNetworkAccessManager nm;
	
protected slots:
	void onRequestFinished();
};

#endif
