#include <MellowPlayer/Application/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingServices.hpp>
#include "Players.hpp"

USE_MELLOWPLAYER_NAMESPACE(Application)
USE_MELLOWPLAYER_NAMESPACE(Application)
using namespace std;

Players::Players(StreamingServices& streamingServices) {
    connect(&streamingServices, &StreamingServices::added,
            this, &Players::onServiceAdded);
    for (auto& plugin: streamingServices.getAll()) {
        onServiceAdded(plugin.get());
    }
}

shared_ptr<Player> Players::get(const QString& serviceName) const {
    return players[serviceName];
}

void Players::onServiceAdded(StreamingService* service) {
    if (!players.contains(service->getName()))
        players[service->getName()] = make_shared<Player>(*service);
}
