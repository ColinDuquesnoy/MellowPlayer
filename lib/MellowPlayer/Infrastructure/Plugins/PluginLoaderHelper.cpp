#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QtCore/QSettings>
#include <QtCore/QStandardPaths>
#include <QtCore/QTextStream>
#include <QtGui/QIcon>
#include "PluginLoaderHelper.hpp"

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

QString PluginLoaderHelper::findFileByExtension(const QString &directory, const QString &suffix) {
        foreach (const QFileInfo &fileInfo,
                 QDir(directory).entryInfoList(QDir::Files | QDir::NoDotAndDotDot)) {
            if (fileInfo.isFile() && fileInfo.suffix() == suffix)
                return fileInfo.absoluteFilePath();
        }
    return QString();
}

QString PluginLoaderHelper::readFileContent(const QString &filePath) {
    QString retVal;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        return retVal;
    }

    QTextStream in(&file);
    retVal = in.readAll();
    file.close();

    return retVal;
}

PluginMetadata PluginLoaderHelper::readMetadata(const QString &filePath) {
    QSettings meta(filePath, QSettings::IniFormat);

    PluginMetadata pluginMetadata;
    pluginMetadata.author = meta.value("author").toString();
    pluginMetadata.authorWebsite = meta.value("author_website").toString();
    pluginMetadata.logoPath = QFileInfo(QFileInfo(filePath).dir(), meta.value("icon").toString()).absoluteFilePath();
    pluginMetadata.name = meta.value("name").toString();
    pluginMetadata.url = meta.value("url").toString();
    pluginMetadata.version = meta.value("version").toString();

    return pluginMetadata;
}

Plugin PluginLoaderHelper::loadPlugin(const QString &directory) {
    QString metadataPath = findFileByExtension(directory, "ini");
    QString scriptPath = findFileByExtension(directory, "js");
    QString descPath = findFileByExtension(directory, "html");
    QString locale = QLocale::system().name().split("_")[0];
    PluginMetadata metadata = readMetadata(metadataPath);
    metadata.script = readFileContent(scriptPath);
    metadata.scriptPath = scriptPath;

    return Plugin(metadata);
}

bool PluginLoaderHelper::checkPluginDirectory(const QString &directory) {
    QString metadataPath = findFileByExtension(directory, "ini");
    QString scriptPath = findFileByExtension(directory, "js");

    return !scriptPath.isEmpty() && !metadataPath.isEmpty();
}

QString PluginLoaderHelper::getUserPluginsDirectory() {
    return QFileInfo(QStandardPaths::standardLocations(
        QStandardPaths::AppLocalDataLocation)[0], "plugins").absoluteFilePath();
}

QStringList PluginLoaderHelper::getSearchPaths() {
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
