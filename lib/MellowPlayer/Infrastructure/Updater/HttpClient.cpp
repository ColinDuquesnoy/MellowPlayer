#include "HttpClient.hpp"

using namespace MellowPlayer::Infrastructure;

HttpClient::HttpClient() {
    connect(&networkAccessManager_, &QNetworkAccessManager::finished, this, &HttpClient::onFinished);

}

void HttpClient::get(const QString& url) {
    networkAccessManager_.get(QNetworkRequest(QUrl(url)));
}

void HttpClient::onFinished(QNetworkReply* reply) {
    emit replyReceived(reply->readAll());
}
