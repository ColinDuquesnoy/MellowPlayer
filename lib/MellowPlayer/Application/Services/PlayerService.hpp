#pragma once

#include <QMap>
#include <MellowPlayer/Application/Services/StreamingServicePluginService.hpp>
#include "MellowPlayer/Application/Player/Player.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(Application)

class PlayerService: public QObject {
    Q_OBJECT
public:
    PlayerService(StreamingServicePluginService& pluginService);

    std::shared_ptr<Player> get(const QString& serviceName) const;

private slots:
    void onServiceAdded(Entities::StreamingServicePlugin* service);

private:
    QMap<QString, std::shared_ptr<Player>> players;
};

END_MELLOWPLAYER_NAMESPACE
