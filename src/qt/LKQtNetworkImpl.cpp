#include <kclib/qt/LKQtNetworkImpl.h>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>

LKQtNetworkImpl::LKQtNetworkImpl():
	LKNetworkImpl()
{
	connect(&nm, SIGNAL(finished(QNetworkReply*)), this, SLOT(onRequestFinished(QNetworkReply*)));
}

LKQtNetworkImpl::~LKQtNetworkImpl()
{
	
}

void LKQtNetworkImpl::get(const std::string &url, std::function<void(bool success, std::vector<char> body)> callback)
{
	QNetworkReply *reply = nm.get(QNetworkRequest(QUrl(QString::fromStdString(url))));
	handlers[reply] = callback;
}

void LKQtNetworkImpl::post(const std::string &url, std::vector<char> body, std::function<void(bool success, std::vector<char> body)> callback)
{
	QNetworkReply *reply = nm.post(QNetworkRequest(QUrl(QString::fromStdString(url))), QByteArray(body.data(), body.size()));
	handlers.insert(reply, callback);
}

void LKQtNetworkImpl::onRequestFinished(QNetworkReply *reply)
{
	handler_fn callback = handlers.value(reply);
	QByteArray body = reply->readAll();
	callback(reply->error() == QNetworkReply::NoError, std::vector<char>(body.data(), body.data() + body.size()));
}
