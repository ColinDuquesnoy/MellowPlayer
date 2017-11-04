#pragma once

#include <MellowPlayer/Domain/Updater/IHttpClient.hpp>
#include <QtNetwork/QNetworkAccessManager>

class QNetworkReply;

namespace MellowPlayer::Infrastructure
{
    class HttpClient : public Domain::IHttpClient
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
