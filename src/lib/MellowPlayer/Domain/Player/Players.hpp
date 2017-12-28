#pragma once

#include <memory>
#include <QObject>
#include <QString>
#include <QMap>

namespace MellowPlayer::Domain
{
    class Player;
    class StreamingService;
    class StreamingServices;

    class Players : public QObject
    {
        Q_OBJECT
    public:
        explicit Players(StreamingServices& streamingServices);

        std::shared_ptr<Player> get(const QString& serviceName) const;

    private slots:
        void onServiceAdded(Domain::StreamingService* service);

    private:
        QMap<QString, std::shared_ptr<Player>> players_;
    };
}
