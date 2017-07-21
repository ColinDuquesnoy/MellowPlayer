#include "StreamingServicesController.hpp"
#include "IStreamingServiceLoader.hpp"
#include "IStreamingServiceWatcher.hpp"
#include "StreamingService.hpp"
#include <MellowPlayer/Application/Logging/LoggingManager.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Application;
using namespace std;

StreamingServicesController::StreamingServicesController(IStreamingServiceLoader &loader, IStreamingServiceWatcher &watcher)
        : logger(LoggingManager::instance().getLogger("StreamingServicesController")), loader(loader), watcher(watcher), current(nullptr)
{
}

void StreamingServicesController::load()
{
    auto newServices = loader.load();

    for (auto newService : newServices) {
        bool found = false;
        for (auto service : services) {
            if (*service == *newService) {
                found = true;
                break;
            }
        }
        if (!found) {
            LOG_DEBUG(logger, "service added: " + newService->getName());
            services.append(newService);
            if (!newService->getPluginDirectory().startsWith("/usr/") && !newService->getPluginDirectory().startsWith("/tmp/"))
                watcher.watch(*newService);
            emit added(newService.get());
        }
    }
}

StreamingService &StreamingServicesController::get(const QString &name) const
{
    for (const auto &service : services)
        if (service->getName() == name)
            return *service;
    throw invalid_argument("unknown service: " + name.toStdString());
}

void StreamingServicesController::setCurrent(StreamingService *service)
{
    if (service == current)
        return;

    current = service;
    emit currentChanged(current);
    if (current)
        LOG_DEBUG(logger, "current service changed: " + current->getName());
}

StreamingService *StreamingServicesController::getCurrent() const
{
    return current;
}
