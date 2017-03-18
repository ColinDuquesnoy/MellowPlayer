#include "PlayersService.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)
using namespace std;

PlayersService::PlayersService(PluginManager& pluginManager) {
    connect(&pluginManager, &PluginManager::pluginAdded,
            this, &PlayersService::onServiceAdded);
    for (auto& plugin: pluginManager.getAll()) {
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
