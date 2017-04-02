#include <MellowPlayer/Entities/Plugin.hpp>
#include "PlayersService.hpp"

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
using namespace std;

PlayersService::PlayersService(PluginService& pluginService) {
    connect(&pluginService, &PluginService::pluginAdded,
            this, &PlayersService::onServiceAdded);
    for (auto& plugin: pluginService.getAll()) {
        onServiceAdded(plugin.get());
    }
}

shared_ptr<Player> PlayersService::get(const QString& serviceName) const {
    return players[serviceName];
}

void PlayersService::onServiceAdded(Plugin* service) {
    if (!players.contains(service->getName()))
        players[service->getName()] = make_shared<Player>(*service);
}
