#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include <MellowPlayer/Application/Interfaces/IStreamingServicePluginLoader.hpp>
#include <MellowPlayer/Entities/StreamingServices/StreamingServicePlugin.hpp>
#include "StreamingServicePluginService.hpp"

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(Application)
using namespace std;

StreamingServicePluginService::StreamingServicePluginService(IStreamingServicePluginLoader& pluginLoader) :
        logger(LoggingManager::instance().getLogger("StreamingServicePluginService")),
        pluginLoader(pluginLoader), currentPlugin(nullptr) {
}

void StreamingServicePluginService::load() {
    auto newPlugins = pluginLoader.load();

    for (auto newPlugin: newPlugins) {
        bool pluginFound = false;
        for (auto plugin: pluginList) {
            if (*plugin == *newPlugin) {
                pluginFound = true;
                break;
            }
        }
        if (!pluginFound) {
            LOG_DEBUG(logger, "add plugin: " + newPlugin->getName());
            pluginList.append(newPlugin);
            emit pluginAdded(newPlugin.get());
        }
    }
}

StreamingServicePlugin& StreamingServicePluginService::get(const QString& name) const {
    for (const auto& plugin: pluginList)
        if (plugin->getName() == name)
            return *plugin;
    throw invalid_argument("unknown plugin: " + name.toStdString());
}

void StreamingServicePluginService::setCurrent(StreamingServicePlugin* plugin) {
    if (plugin == currentPlugin)
        return;

    currentPlugin = plugin;
    emit currentPluginChanged(plugin);
    if (plugin)
        LOG_INFO(logger, "current plugin changed: " + plugin->getName());
}

StreamingServicePlugin* StreamingServicePluginService::getCurrent() const {
    return currentPlugin;
}
