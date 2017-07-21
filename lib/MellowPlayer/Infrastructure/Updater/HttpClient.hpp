#pragma once

#include <MellowPlayer/Application/Updater/IHttpClient.hpp>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

namespace MellowPlayer::Infrastructure
{
    class HttpClient : public Application::IHttpClient
    {
        Q_OBJECT
    public:
        HttpClient();
        void get(const QString &url) override;

    private slots:
        void onFinished(QNetworkReply *reply);

    private:
        QNetworkAccessManager networkAccessManager_;
    };
}
