#include <QtCore/QDir>
#include "PluginLoader.hpp"
#include "PluginLoaderHelper.hpp"

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

PluginLoader::PluginLoader(LoggingManager &loggingManager)
    : logger_(loggingManager.getLogger("PluginManager")) {

}

PluginList PluginLoader::loadPlugins() const {
    PluginList plugins;
    PluginLoaderHelper helper;
    for(const QString &path: helper.getSearchPaths()) {
        if (!QDir(path).exists()) {
            LOG_TRACE(logger_, "Skipping plugin path: " << path.toStdString().c_str() << " (directory not found)");
            continue;
        }
        LOG_TRACE(logger_, "Looking for plugins in " << path.toStdString().c_str());
        for(const QFileInfo &directory: QDir(path).entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot)) {
            if (helper.checkPluginDirectory(directory.absoluteFilePath())) {
                Plugin plugin = helper.loadPlugin(directory.absoluteFilePath());
                if (plugin.isValid() && !plugins.contains(plugin)) {
                    LOG_INFO(logger_, plugin.name.toStdString().c_str() << " plugin successfully loaded (from \"" <<
                                      directory.absoluteFilePath().toStdString().c_str() << "\")");
                    plugins.append(plugin);
                }
            }
        }
    }

    return plugins;
}
