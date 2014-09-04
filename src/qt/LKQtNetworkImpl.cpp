#include "LKQtNetworkImpl.h"
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>

void LKQtNetworkImpl::get(const std::string &url, handler_fn callback)
{
	QNetworkReply *reply = nm.get(QNetworkRequest(QUrl(QString::fromStdString(url))));
	_registerReply(reply, callback);
}

void LKQtNetworkImpl::post(const std::string &url, std::string body, handler_fn callback)
{
	QNetworkRequest req(QUrl(QString::fromStdString(url)));
	req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
	QNetworkReply *reply = nm.post(req, QByteArray(body.data(), body.size()));
	_registerReply(reply, callback);
}

void LKQtNetworkImpl::onRequestFinished()
{
	QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
	handler_fn callback = handlers.value(reply);
	QByteArray body = reply->readAll();
	bool success = false;
	
	switch(reply->error())
	{
		case QNetworkReply::UnknownNetworkError:
		case QNetworkReply::UnknownProxyError:
		case QNetworkReply::UnknownContentError:
		case QNetworkReply::ProtocolFailure:
			success = false;
		default:
			success = true;
	}
	
	callback(success, reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(), std::vector<char>(body.data(), body.data() + body.size()));
	handlers.remove(reply);
}

void LKQtNetworkImpl::_registerReply(QNetworkReply *reply, handler_fn callback)
{
	handlers.insert(reply, callback);
	connect(reply, SIGNAL(finished()), this, SLOT(onRequestFinished()));
	
	if(synchronous)
	{
		QEventLoop loop;
		connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
		loop.exec();
	}
}
