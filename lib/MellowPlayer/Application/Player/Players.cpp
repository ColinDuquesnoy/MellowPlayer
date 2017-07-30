#include "Players.hpp"
#include <MellowPlayer/Application/StreamingServices/StreamingService.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Application;
using namespace std;

Players::Players(StreamingServicesController& streamingServices)
{
    connect(&streamingServices, &StreamingServicesController::added, this, &Players::onServiceAdded);
    for (auto& service : streamingServices.toList()) {
        onServiceAdded(service.get());
    }
}

shared_ptr<Player> Players::get(const QString& serviceName) const
{
    return players_[serviceName];
}

void Players::onServiceAdded(StreamingService* service)
{
    if (!players_.contains(service->name()))
        players_[service->name()] = make_shared<Player>(*service);
}
