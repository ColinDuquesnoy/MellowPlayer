#include "PlayersManager.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)
using namespace std;

PlayersManager::PlayersManager(PluginManager& pluginManager) {
    connect(&pluginManager, &PluginManager::pluginAdded,
            this, &PlayersManager::onServiceAdded);
    for (auto& plugin: pluginManager.getAll()) {
        onServiceAdded(plugin.get());
    }
}

shared_ptr<Player> PlayersManager::getPlayer(const QString& serviceName) const {
    return players[serviceName];
}

void PlayersManager::onServiceAdded(Plugin* service) {
    if (players.contains(service->getName()))
        return;
    players[service->getName()] = make_shared<Player>(*service);
}
