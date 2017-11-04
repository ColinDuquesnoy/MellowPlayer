#include "StreamingServicesController.hpp"
#include "IStreamingServiceLoader.hpp"
#include "IStreamingServiceWatcher.hpp"
#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/LoggingManager.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain;
using namespace std;

StreamingServicesController::StreamingServicesController(IStreamingServiceLoader& loader, IStreamingServiceWatcher& watcher)
        : logger_(LoggingManager::logger("StreamingServicesController")), loader_(loader), watcher_(watcher), current_(nullptr)
{
}

void StreamingServicesController::load()
{
    auto newServices = loader_.load();

    for (auto newService : newServices) {
        bool found = false;
        for (auto service : services_) {
            if (*service == *newService) {
                found = true;
                break;
            }
        }
        if (!found) {
            LOG_DEBUG(logger_, "service added: " + newService->name());
            services_.append(newService);
            if (!newService->pluginDirectory().startsWith("/usr/") && !newService->pluginDirectory().startsWith("/tmp/"))
                watcher_.watch(*newService);
            emit added(newService.get());
        }
    }
}

StreamingService& StreamingServicesController::get(const QString& name) const
{
    for (const auto& service : services_)
        if (service->name() == name)
            return *service;
    throw invalid_argument("unknown service: " + name.toStdString());
}

void StreamingServicesController::setCurrent(StreamingService* service)
{
    if (service == current_)
        return;

    current_ = service;
    emit currentChanged(current_);
    if (current_)
        LOG_DEBUG(logger_, "current service changed: " + current_->name());
}

StreamingService* StreamingServicesController::current() const
{
    return current_;
}
