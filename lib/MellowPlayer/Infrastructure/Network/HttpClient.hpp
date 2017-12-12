#pragma once

#include <MellowPlayer/Infrastructure/Network/IHttpClient.hpp>
#include <QtNetwork/QNetworkAccessManager>

class QNetworkReply;

namespace MellowPlayer::Infrastructure
{
    class HttpClient : public IHttpClient
    {
        Q_OBJECT
    public:
        HttpClient();
        void get(const QString& url) override;

    private slots:
        void onFinished(QNetworkReply* reply);

    private:
        QNetworkAccessManager networkAccessManager_;
    };
}
