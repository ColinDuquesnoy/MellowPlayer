#pragma once

#include <QtGui/QImage>

namespace MellowPlayer::Domain
{
    class ILogger;
}

namespace MellowPlayer::Infrastructure
{
    class Base64Helper : public QObject
    {
        Q_OBJECT
    public:
        explicit Base64Helper(QObject* parent = nullptr);

        Q_INVOKABLE bool isBase64(const QString& uri);
        Q_INVOKABLE QImage getImage(const QString& uri);
        Q_INVOKABLE bool saveToFile(const QString& uri, const QString& path);
        Q_INVOKABLE QString getImageProviderUrl(const QString& url);

    private:
        Domain::ILogger& logger_;
    };
}
