#include <MellowPlayer/Infrastructure/Network/ApplicationNetworkProxy.hpp>
#include <MellowPlayer/Infrastructure/Network/NetworkProxies.hpp>
#include <MellowPlayer/Infrastructure/Network/NetworkProxy.hpp>
#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServices.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;


ApplicationNetworkProxy::ApplicationNetworkProxy(StreamingServices& streamingServices, INetworkProxies& networkProxies)
        : logger_(Loggers::logger("ApplicationNetworkProxy")),
          initialNetworkProxy_(QNetworkProxy::applicationProxy()),
          streamingServices_(streamingServices),
          networkProxies_(networkProxies)
{
    connect(&streamingServices, &StreamingServices::currentChanged, this, &ApplicationNetworkProxy::onCurrentStreamingServiceChanged);
}

void ApplicationNetworkProxy::onCurrentStreamingServiceChanged(StreamingService* service)
{
    if (currentNetworkProxy_)
        disconnect(currentNetworkProxy_.get(), &NetworkProxy::changed, this, &ApplicationNetworkProxy::updateNetworkProxy);

    if (service != nullptr) {
        currentServiceName_ = service->name();
        currentNetworkProxy_ = networkProxies_.get(service->name());
        connect(currentNetworkProxy_.get(), &NetworkProxy::changed, this, &ApplicationNetworkProxy::updateNetworkProxy);
    }
    else
        currentNetworkProxy_ = nullptr;

    updateNetworkProxy();
}

void ApplicationNetworkProxy::updateNetworkProxy()
{
    if (currentNetworkProxy_ != nullptr && currentNetworkProxy_->isValid())
    {
        LOG_INFO(logger_, QString("Using %1 network proxy settings: %2").arg(currentServiceName_).arg(currentNetworkProxy_->toString()));
        QNetworkProxy::setApplicationProxy(currentNetworkProxy_->create());
    }
    else if (QNetworkProxy::applicationProxy() != initialNetworkProxy_) {
        LOG_INFO(logger_, "Restoring initial network proxy");
        QNetworkProxy::setApplicationProxy(initialNetworkProxy_);
    }
}

ApplicationNetworkProxy::~ApplicationNetworkProxy()
{
    QNetworkProxy::setApplicationProxy(initialNetworkProxy_);
}
