#pragma once

#include <QMap>
#include <MellowPlayer/UseCases/Services/PluginService.hpp>
#include "MellowPlayer/UseCases/Player/Player.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class PlayerService: public QObject {
    Q_OBJECT
public:
    PlayerService(PluginService& pluginService);

    std::shared_ptr<Player> get(const QString& serviceName) const;

private slots:
    void onServiceAdded(Entities::Plugin* service);

private:
    QMap<QString, std::shared_ptr<Player>> players;
};

END_MELLOWPLAYER_NAMESPACE
