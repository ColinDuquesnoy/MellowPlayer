#include <MellowPlayer/Infrastructure/Network/HttpClient.hpp>
#include <QtNetwork/QNetworkReply>


using namespace MellowPlayer::Infrastructure;

HttpClient::HttpClient()
{
    connect(&networkAccessManager_, &QNetworkAccessManager::finished, this, &HttpClient::onFinished);
}

void HttpClient::get(const QString& url)
{
    networkAccessManager_.get(QNetworkRequest(QUrl(url)));
}

void HttpClient::onFinished(QNetworkReply* reply)
{
    if (reply->error() != QNetworkReply::NoError)
        qWarning() << "http request failed: " << reply->errorString();
    emit replyReceived(reply->readAll());
}
