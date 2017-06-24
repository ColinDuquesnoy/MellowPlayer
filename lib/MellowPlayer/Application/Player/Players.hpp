#pragma once

#include <QMap>
#include <MellowPlayer/Application/StreamingServices/StreamingServices.hpp>
#include "MellowPlayer/Application/Player/Player.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(Application)

class Players: public QObject {
    Q_OBJECT
public:
    Players(StreamingServices& streamingServices);

    std::shared_ptr<Player> get(const QString& serviceName) const;

private slots:
    void onServiceAdded(Application::StreamingService* service);

private:
    QMap<QString, std::shared_ptr<Player>> players;
};

END_MELLOWPLAYER_NAMESPACE
