#pragma once

#include <QMap>
#include <MellowPlayer/UseCases/Services/PluginsService.hpp>
#include "MellowPlayer/UseCases/Player/Player.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class PlayersService: public QObject {
    Q_OBJECT
public:
    PlayersService(PluginsService& pluginManager);

    std::shared_ptr<Player> get(const QString& serviceName) const;

private slots:
    void onServiceAdded(Entities::Plugin* service);

private:
    QMap<QString, std::shared_ptr<Player>> players;
};

END_MELLOWPLAYER_NAMESPACE
