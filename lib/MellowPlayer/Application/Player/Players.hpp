#pragma once

#include <memory>
#include <QObject>
#include <QString>
#include <QMap>

namespace MellowPlayer::Application
{
    class Player;
    class StreamingService;
    class StreamingServicesController;

    class Players : public QObject
    {
        Q_OBJECT
    public:
        explicit Players(StreamingServicesController& streamingServices);

        std::shared_ptr<Player> get(const QString& serviceName) const;

    private slots:
        void onServiceAdded(Application::StreamingService* service);

    private:
        QMap<QString, std::shared_ptr<Player>> players_;
    };
}
