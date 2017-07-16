#pragma once

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <MellowPlayer/Application/Updater/IHttpClient.hpp>


namespace MellowPlayer::Infrastructure {

    class HttpClient: public Application::IHttpClient {
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
