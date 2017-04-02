#pragma once

#include <QMap>
#include <MellowPlayer/UseCases/Plugin/PluginManager.hpp>
#include "Player.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class PlayersService: public QObject {
    Q_OBJECT
public:
    PlayersService(PluginManager& pluginManager);

    std::shared_ptr<Player> get(const QString& serviceName) const;

private slots:
    void onServiceAdded(UseCases::Plugin* service);

private:
    QMap<QString, std::shared_ptr<Player>> players;
};

END_MELLOWPLAYER_NAMESPACE
