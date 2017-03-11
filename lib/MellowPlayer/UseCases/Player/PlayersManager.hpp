#pragma once

#include <qmap.h>
#include "Player.hpp"
#include "../Plugin/PluginManager.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class PlayersManager: public QObject {
    Q_OBJECT
public:
    PlayersManager(PluginManager& pluginManager);

    std::shared_ptr<Player> getPlayer(const QString& serviceName) const;

private slots:
    void onServiceAdded(UseCases::Plugin* service);

private:
    QMap<QString, std::shared_ptr<Player>> players;
};

END_MELLOWPLAYER_NAMESPACE
