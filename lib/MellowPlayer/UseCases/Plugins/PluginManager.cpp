#include "PluginManagerTests.hpp"
#include <stdexcept>

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
using namespace std;

PluginManager::PluginManager(IPluginLoader &pluginLoader)
    : pluginLoader_(pluginLoader),
      plugins_(pluginLoader.loadPlugins()) {

}

const Plugin &PluginManager::plugin(const QString &name) const {
    for(const auto& plugin: plugins_)
        if (plugin.name == name)
            return plugin;
    throw invalid_argument("unknown plugin: " + name.toStdString());
}
