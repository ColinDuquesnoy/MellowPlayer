#pragma once

#include "MellowPlayer/Application/Player/Player.hpp"
#include <MellowPlayer/Application/StreamingServices/StreamingServicesController.hpp>
#include <QMap>

namespace MellowPlayer::Application
{
    class Players : public QObject
    {
        Q_OBJECT
    public:
        Players(StreamingServicesController &streamingServices);

        std::shared_ptr<Player> get(const QString &serviceName) const;

    private slots:
        void onServiceAdded(Application::StreamingService *service);

    private:
        QMap<QString, std::shared_ptr<Player>> players;
    };
}
