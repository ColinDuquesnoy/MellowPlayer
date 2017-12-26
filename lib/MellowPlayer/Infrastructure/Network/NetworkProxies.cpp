#include <MellowPlayer/Domain/StreamingServices/StreamingServices.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Domain/Settings/ISettingsStore.hpp>
#include "NetworkProxies.hpp"
#include "NetworkProxy.hpp"

using namespace std;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

NetworkProxies::NetworkProxies(IQtApplication& qtApplication,
                               ISettingsStore& settingsStore,
                               StreamingServices& streamingServices)
        : qtApplication_(qtApplication),
          settingsStore_(settingsStore),
          streamingServices_(streamingServices)
{
    connect(&streamingServices, &StreamingServices::added, this, &NetworkProxies::onStreamingServiceAdded);
}

std::shared_ptr<NetworkProxy> NetworkProxies::get(const QString& name) const
{
    return items_[name];
}

void NetworkProxies::onStreamingServiceAdded(StreamingService* service)
{
    add(service->name(), make_shared<NetworkProxy>(settingsStore_.value(settingUrl(service->name())).toMap()));
}

void NetworkProxies::add(const QString& serviceName, const shared_ptr<NetworkProxy>& networkProxy)
{
    items_[serviceName] = networkProxy;
    connect(networkProxy.get(), &NetworkProxy::changed, [=]()
    {
        settingsStore_.setValue(settingUrl(serviceName), networkProxy->rawData());
    });
}

QString NetworkProxies::settingUrl(const QString &name) const
{
    return name + "/networkProxy";
}
