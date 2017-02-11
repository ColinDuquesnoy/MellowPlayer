#include "StreamingServicesManager.hpp"
#include <stdexcept>

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
using namespace std;

StreamingServicesManager::StreamingServicesManager(IStreamingServicesLoader& pluginLoader)
    : pluginLoader(pluginLoader),
      currentService(nullptr) {
}

StreamingService& StreamingServicesManager::getService(const QString& name) const {
    for (const auto& plugin: streamingServices)
        if (plugin->getName() == name)
            return *plugin;
    throw invalid_argument("unknown plugin: " + name.toStdString());
}

const StreamingServicesList& StreamingServicesManager::getServices() const {
    return streamingServices;
}

void StreamingServicesManager::load() {
    auto newPlugins = pluginLoader.load();

    for (auto newPlugin: newPlugins) {
        bool pluginFound = false;
        for (auto plugin: streamingServices) {
            if (*plugin == *newPlugin) {
                pluginFound = true;
                break;
            }
        }
        if (!pluginFound) {
            streamingServices.append(newPlugin);
            emit serviceAdded(newPlugin.get());
        }
    }

    for (auto plugin: streamingServices) {
        bool pluginFound = false;
        for (auto newPlugin: newPlugins) {
            if (*plugin == *newPlugin) {
                pluginFound = true;
                break;
            }
        }
        if (!pluginFound) {
            streamingServices.removeOne(plugin);
            emit serviceRemoved(plugin.get());
        }
    }
}

void StreamingServicesManager::setCurrentService(StreamingService* service) {
    if (service == currentService)
        return;
    currentService = service;
    emit currentServiceChanged(service);
}

StreamingService* StreamingServicesManager::getCurrentService() const {
    return currentService;
}
