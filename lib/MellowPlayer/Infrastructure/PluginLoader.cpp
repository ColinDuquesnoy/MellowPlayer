#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QtCore/QSettings>
#include <QtCore/QStandardPaths>
#include <QtCore/QTextStream>
#include <QtGui/QIcon>
#include "PluginLoader.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)
using namespace std;

PluginLoader::PluginLoader():
        logger(LoggingManager::instance().getLogger("PluginManager")) {

}

PluginList PluginLoader::load() const {
    PluginList plugins;
    for (const QString& path: getSearchPaths()) {
        if (!QDir(path).exists()) {
            LOG_TRACE(logger, "Skipping plugin path: " << path.toStdString().c_str() << " (directory not found)");
            continue;
        }
        LOG_TRACE(logger, "Looking for plugins in " << path.toStdString().c_str());
        for (const QFileInfo& directory: QDir(path).entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot)) {
            if (checkPluginDirectory(directory.absoluteFilePath())) {
                shared_ptr<Plugin> plugin = loadPlugin(directory.absoluteFilePath());
                if (plugin->isValid() && !containsPlugin(plugins, plugin)) {
                    LOG_DEBUG(logger, plugin->getName().toStdString().c_str()
                            << " plugin successfully loaded (from \"" <<
                            directory.absoluteFilePath().toStdString().c_str() << "\")");
                    plugins.append(plugin);
                } else {
                    LOG_DEBUG(logger,
                              "Skipping plugin " << plugin->getName().toStdString().c_str()
                                                 << ", already loaded from another source or invalid");
                }
            }
        }
    }

    return plugins;
}

QString PluginLoader::findFileByExtension(const QString& directory, const QString& suffix) const {
            foreach (const QFileInfo& fileInfo,
                     QDir(directory).entryInfoList(QDir::Files | QDir::NoDotAndDotDot)) {
            if (fileInfo.isFile() && fileInfo.suffix() == suffix)
                return fileInfo.absoluteFilePath();
        }
    return QString();
}

QString PluginLoader::readFileContent(const QString& filePath) const {
    QString retVal;

    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        retVal = in.readAll();
    }

    return retVal;
}

PluginMetadata PluginLoader::readMetadata(const QString& filePath) const {
    QSettings meta(filePath, QSettings::IniFormat);

    PluginMetadata pluginMetadata;
    pluginMetadata.author = meta.value("author").toString();
    pluginMetadata.authorWebsite = meta.value("author_website").toString();
    pluginMetadata.logoPath = QFileInfo(QFileInfo(filePath).dir(), meta.value("icon").toString()).absoluteFilePath();
    pluginMetadata.name = meta.value("name").toString();
    pluginMetadata.url = meta.value("url").toString();
    pluginMetadata.version = meta.value("version").toString();
    pluginMetadata.color = meta.value("color").toString();

    return pluginMetadata;
}

unique_ptr<Plugin> PluginLoader::loadPlugin(const QString& directory) const {
    QString metadataPath = findFileByExtension(directory, "ini");
    QString scriptPath = findFileByExtension(directory, "js");
    QString descPath = findFileByExtension(directory, "html");
    QString locale = QLocale::system().name().split("_")[0];
    PluginMetadata metadata = readMetadata(metadataPath);
    metadata.script = readFileContent(scriptPath);
    metadata.scriptPath = scriptPath;

    return make_unique<Plugin>(metadata);
}

bool PluginLoader::checkPluginDirectory(const QString& directory) const {
    QString metadataPath = findFileByExtension(directory, "ini");
    QString scriptPath = findFileByExtension(directory, "js");

    return !scriptPath.isEmpty() && !metadataPath.isEmpty();
}

QString PluginLoader::getUserPluginsDirectory() const {
    return QFileInfo(QStandardPaths::standardLocations(
            QStandardPaths::AppLocalDataLocation)[0], "plugins").absoluteFilePath();
}

QStringList PluginLoader::getSearchPaths() const {
    QStringList paths;
    paths.append(CMAKE_SOURCE_DIR + QString(QDir::separator()) + "src" + QString(QDir::separator()) + "plugins");
    paths.append(QFileInfo(QDir::currentPath(), "plugins").absoluteFilePath());
    paths.append(QFileInfo(qApp->applicationDirPath(), "plugins").absoluteFilePath());
    paths.append(getUserPluginsDirectory());

#ifdef Q_OS_MAC
    QDir pluginsDir(qApp->applicationDirPath());
    pluginsDir.cdUp();
    pluginsDir.cd("PlugIns");
    pluginsDir.cd("services");
    paths.append(pluginsDir.path());
#endif

#ifdef Q_OS_LINUX
    paths.append("/usr/share/mellowplayer/plugins");
    paths.append("/usr/local/share/mellowplayer/plugins");
#endif

    paths.removeDuplicates();

    return paths;
}

bool PluginLoader::containsPlugin(const PluginList& plugins,
                                             shared_ptr<Plugin>& toCheck) const {
    for (auto plugin: plugins) {
        if (*toCheck == *plugin)
            return true;
    }
    return false;
}
