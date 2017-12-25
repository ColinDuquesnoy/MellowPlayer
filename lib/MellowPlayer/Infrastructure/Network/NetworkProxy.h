#pragma once

#include <MellowPlayer/Domain/Properties.hpp>
#include <QVariantMap>
#include <QtNetwork/QNetworkProxy>

namespace MellowPlayer::Infrastructure
{
    class NetworkProxy: public QObject
    {
        Q_OBJECT
        Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)
        Q_PROPERTY(QString hostName READ hostName WRITE setHostName NOTIFY hostNameChanged)
        Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)

    public:
        NetworkProxy() = default;
        NetworkProxy(const QVariantMap& rawData);

        bool isEnabled() const;
        void setEnabled(bool value);

        QString hostName() const;
        void setHostName(const QString& hostName);

        int port() const;
        void setPort(int port);

        QNetworkProxy create() const;

        QVariantMap rawData() const;

    signals:
        void changed();
        void enabledChanged();
        void hostNameChanged();
        void portChanged();

    private:
        QVariantMap rawData_;
    };
}
