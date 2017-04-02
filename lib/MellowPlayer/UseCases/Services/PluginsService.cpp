#include <MellowPlayer/UseCases/Logging/LoggingManager.hpp>
#include <MellowPlayer/UseCases/Interfaces/IPluginLoader.hpp>
#include <MellowPlayer/Entities/Plugin.hpp>
#include "PluginsService.hpp"

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
using namespace std;

PluginsService::PluginsService(IPluginLoader& pluginLoader) :
        logger(LoggingManager::instance().getLogger("PluginsService")),
        pluginLoader(pluginLoader), currentPlugin(nullptr) {
}

void PluginsService::load() {
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

Plugin& PluginsService::get(const QString& name) const {
    for (const auto& plugin: pluginList)
        if (plugin->getName() == name)
            return *plugin;
    throw invalid_argument("unknown plugin: " + name.toStdString());
}

const PluginList& PluginsService::getAll() const {
    return pluginList;
}

void PluginsService::setCurrent(Plugin* plugin) {
    if (plugin == currentPlugin)
        return;

    currentPlugin = plugin;
    emit currentPluginChanged(plugin);
}

Plugin* PluginsService::getCurrent() const {
    return currentPlugin;
}
