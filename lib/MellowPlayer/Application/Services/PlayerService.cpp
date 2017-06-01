#include <MellowPlayer/Entities/StreamingServices/StreamingServicePlugin.hpp>
#include <MellowPlayer/Application/Services/StreamingServicePluginService.hpp>
#include "PlayerService.hpp"

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(Application)
using namespace std;

PlayerService::PlayerService(StreamingServicePluginService& pluginService) {
    connect(&pluginService, &StreamingServicePluginService::pluginAdded,
            this, &PlayerService::onServiceAdded);
    for (auto& plugin: pluginService.getAll()) {
        onServiceAdded(plugin.get());
    }
}

shared_ptr<Player> PlayerService::get(const QString& serviceName) const {
    return players[serviceName];
}

void PlayerService::onServiceAdded(StreamingServicePlugin* service) {
    if (!players.contains(service->getName()))
        players[service->getName()] = make_shared<Player>(*service);
}
