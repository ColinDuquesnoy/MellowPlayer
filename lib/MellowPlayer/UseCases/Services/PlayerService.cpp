#include <MellowPlayer/Entities/Plugin.hpp>
#include "PlayerService.hpp"

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
using namespace std;

PlayerService::PlayerService(PluginService& pluginService) {
    connect(&pluginService, &PluginService::pluginAdded,
            this, &PlayerService::onServiceAdded);
    for (auto& plugin: pluginService.getAll()) {
        onServiceAdded(plugin.get());
    }
}

shared_ptr<Player> PlayerService::get(const QString& serviceName) const {
    return players[serviceName];
}

void PlayerService::onServiceAdded(Plugin* service) {
    if (!players.contains(service->getName()))
        players[service->getName()] = make_shared<Player>(*service);
}
