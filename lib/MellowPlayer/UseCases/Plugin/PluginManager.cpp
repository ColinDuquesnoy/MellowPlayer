#include "PluginManager.hpp"
#include <stdexcept>

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
using namespace std;

PluginManager::PluginManager(IPluginLoader& pluginLoader)
    : pluginLoader(pluginLoader),
      currentPlugin(nullptr) {
}

void PluginManager::load() {
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
            pluginList.append(newPlugin);
            emit pluginAdded(newPlugin.get());
        }
    }
}

Plugin& PluginManager::get(const QString& name) const {
    for (const auto& plugin: pluginList)
        if (plugin->getName() == name)
            return *plugin;
    throw invalid_argument("unknown plugin: " + name.toStdString());
}

const PluginList& PluginManager::getAll() const {
    return pluginList;
}

void PluginManager::setCurrent(Plugin* plugin) {
    if (plugin == currentPlugin)
        return;
    currentPlugin = plugin;
    emit currentPluginChanged(plugin);
}

Plugin* PluginManager::getCurrent() const {
    return currentPlugin;
}
