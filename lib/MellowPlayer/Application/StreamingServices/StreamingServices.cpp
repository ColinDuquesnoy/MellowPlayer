#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include <MellowPlayer/Application/StreamingServices/IStreamingServiceLoader.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingService.hpp>
#include "StreamingServices.hpp"

USE_MELLOWPLAYER_NAMESPACE(Application)
USE_MELLOWPLAYER_NAMESPACE(Application)
using namespace std;

StreamingServices::StreamingServices(IStreamingServiceLoader& loader) :
        logger(LoggingManager::instance().getLogger("StreamingServices")),
        loader(loader), current(nullptr) {
}

void StreamingServices::load() {
    auto newServices = loader.load();

    for (auto newService: newServices) {
        bool found = false;
        for (auto service: services) {
            if (*service == *newService) {
                found = true;
                break;
            }
        }
        if (!found) {
            LOG_DEBUG(logger, "service added: " + newService->getName());
            services.append(newService);
            emit added(newService.get());
        }
    }
}

StreamingService& StreamingServices::get(const QString& name) const {
    for (const auto& service: services)
        if (service->getName() == name)
            return *service;
    throw invalid_argument("unknown service: " + name.toStdString());
}

void StreamingServices::setCurrent(StreamingService* service) {
    if (service == current)
        return;

    current = service;
    emit currentChanged(current);
    if (current)
        LOG_INFO(logger, "current service changed: " + current->getName());
}

StreamingService* StreamingServices::getCurrent() const {
    return current;
}
