#pragma once

#include <QtCore/QObject>

namespace MellowPlayer::Application {

    class IHttpClient: public QObject {
        Q_OBJECT
    public:
        virtual ~IHttpClient();
        virtual void get(const QString& url) = 0;

    signals:
        void replyReceived(const QByteArray& replyData);

    };

}