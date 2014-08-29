#include <kclib/qt/LKQtNetworkImpl.h>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>

LKQtNetworkImpl::LKQtNetworkImpl():
	LKNetworkImpl()
{
	connect(&nm, SIGNAL(finished(QNetworkReply*)), this, SLOT(onRequestFinished(QNetworkReply*)));
}

LKQtNetworkImpl::~LKQtNetworkImpl()
{
	
}

void LKQtNetworkImpl::get(const std::string &url, handler_fn callback)
{
	QNetworkReply *reply = nm.get(QNetworkRequest(QUrl(QString::fromStdString(url))));
	_registerReply(reply, callback);
}

void LKQtNetworkImpl::post(const std::string &url, std::vector<char> body, handler_fn callback)
{
	QNetworkReply *reply = nm.post(QNetworkRequest(QUrl(QString::fromStdString(url))), QByteArray(body.data(), body.size()));
	_registerReply(reply, callback);
}

void LKQtNetworkImpl::onRequestFinished(QNetworkReply *reply)
{
	handler_fn callback = handlers.value(reply);
	QByteArray body = reply->readAll();
	callback(reply->error() == QNetworkReply::NoError, std::vector<char>(body.data(), body.data() + body.size()));
	handlers.remove(reply);
}

void LKQtNetworkImpl::_registerReply(QNetworkReply *reply, handler_fn callback)
{
	handlers.insert(reply, callback);
	
	if(synchronous)
	{
		QEventLoop loop;
		connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
		loop.exec();
	}
}
