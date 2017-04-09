#include <MellowPlayer/UseCases/Logging/LoggingManager.hpp>
#include <MellowPlayer/UseCases/Interfaces/IPluginLoader.hpp>
#include <MellowPlayer/Entities/Plugin.hpp>
#include "PluginService.hpp"

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
using namespace std;

PluginService::PluginService(IPluginLoader& pluginLoader) :
        logger(LoggingManager::instance().getLogger("PluginService")),
        pluginLoader(pluginLoader), currentPlugin(nullptr) {
}

void PluginService::load() {
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

Plugin& PluginService::get(const QString& name) const {
    for (const auto& plugin: pluginList)
        if (plugin->getName() == name)
            return *plugin;
    throw invalid_argument("unknown plugin: " + name.toStdString());
}

void PluginService::setCurrent(Plugin* plugin) {
    if (plugin == currentPlugin)
        return;

    currentPlugin = plugin;
    emit currentPluginChanged(plugin);
    if (plugin)
        LOG_INFO(logger, "current plugin changed: " + plugin->getName());
}

Plugin* PluginService::getCurrent() const {
    return currentPlugin;
}
