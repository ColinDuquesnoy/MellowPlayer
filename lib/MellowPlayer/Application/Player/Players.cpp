#include <MellowPlayer/Application/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingServicesController.hpp>
#include "Players.hpp"

USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Application)
using namespace std;

Players::Players(StreamingServicesController& streamingServices) {
    connect(&streamingServices, &StreamingServicesController::added,
            this, &Players::onServiceAdded);
    for (auto& service: streamingServices.getAll()) {
        onServiceAdded(service.get());
    }
}

shared_ptr<Player> Players::get(const QString& serviceName) const {
    return players[serviceName];
}

void Players::onServiceAdded(StreamingService* service) {
    if (!players.contains(service->getName()))
        players[service->getName()] = make_shared<Player>(*service);
}
