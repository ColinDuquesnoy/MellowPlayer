#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QtCore/QSettings>
#include <QtCore/QStandardPaths>
#include <QtCore/QTextStream>
#include <QtGui/QIcon>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingServiceMetadata.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingServiceStyle.hpp>
#include "StreamingServiceLoader.hpp"
#include <QDebug>

USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Infrastructure)
using namespace std;

StreamingServiceLoader::StreamingServiceLoader() :
        logger(LoggingManager::instance().getLogger("StreamingServiceLoader")) {

}

QList<shared_ptr<StreamingService>> StreamingServiceLoader::load() const {
    QList<shared_ptr<StreamingService>> services;
    for (const QString& path: getSearchPaths()) {
        if (!QDir(path).exists()) {
            LOG_DEBUG(logger, "skipping plugin directory: " << path.toStdString().c_str() << " (directory not found)");
            continue;
        }
        LOG_DEBUG(logger, "looking for services in " << path.toStdString().c_str());
        for (const QFileInfo& directory: QDir(path).entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot)) {
            if (checkServiceDirectory(directory.absoluteFilePath())) {
                shared_ptr<StreamingService> service = loadService(directory.absoluteFilePath());
                if (service->isValid() && !containsService(services, service)) {
                    LOG_DEBUG(logger, service->getName() + " streamingService successfully loaded (from \"" +
                                      directory.absoluteFilePath() + "\")");
                    services.append(service);
                } else {
                    LOG_DEBUG(logger, "skipping streamingService " + service->getName() +
                                      ", already loaded from another source or invalid");
                }
            }
        }
    }

    return services;
}

QString StreamingServiceLoader::findFileByExtension(const QString& directory, const QString& suffix) const {
            foreach (const QFileInfo& fileInfo,
                     QDir(directory).entryInfoList(QDir::Files | QDir::NoDotAndDotDot)) {
            if (fileInfo.isFile() && fileInfo.suffix() == suffix)
                return fileInfo.absoluteFilePath();
        }
    return QString();
}

QString StreamingServiceLoader::readFileContent(const QString& filePath) const {
    QString retVal;

    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        retVal = in.readAll();
    }

    return retVal;
}

StreamingServiceMetadata StreamingServiceLoader::readMetadata(const QString& filePath) const {
    QSettings meta(filePath, QSettings::IniFormat);

    StreamingServiceMetadata serviceMetadata;
    serviceMetadata.author = meta.value("author").toString();
    serviceMetadata.authorWebsite = meta.value("author_website").toString();
    serviceMetadata.logoPath = QFileInfo(QFileInfo(filePath).dir(), meta.value("icon").toString()).absoluteFilePath();
    serviceMetadata.name = meta.value("name").toString();
    serviceMetadata.url = meta.value("url").toString();
    serviceMetadata.version = meta.value("version").toString();

    return serviceMetadata;
}

StreamingServiceStyle StreamingServiceLoader::readStyle(const QString& filePath) const {
    StreamingServiceStyle style;

    if (QFileInfo(filePath).exists()) {
        QFile file(filePath);
        if (file.open(QFile::ReadOnly | QFile::Text)) {
            QJsonDocument document = QJsonDocument::fromJson(file.readAll().data());
            QJsonObject object = document.object();
            style.accent = object.value("accent").toString();
            style.background = object.value("background").toString();
            style.foreground = object.value("foreground").toString();
            style.primary = object.value("primary").toString();
            style.primaryForeground = object.value("primaryForeground").toString();
            style.secondary = object.value("secondary").toString();
            style.secondaryForeground = object.value("secondaryForeground").toString();
        }
    }

    return style;
}

unique_ptr<StreamingService> StreamingServiceLoader::loadService(const QString& directory) const {
    QString metadataPath = findFileByExtension(directory, "ini");
    QString scriptPath = findFileByExtension(directory, "js");
    QString stylePath = findFileByExtension(directory, "json");
    QString locale = QLocale::system().name().split("_")[0];
    StreamingServiceMetadata metadata = readMetadata(metadataPath);
    metadata.script = readFileContent(scriptPath);
    metadata.scriptPath = scriptPath;
    StreamingServiceStyle style = readStyle(stylePath);

    return make_unique<StreamingService>(metadata, style);
}

bool StreamingServiceLoader::checkServiceDirectory(const QString& directory) const {
    QString metadataPath = findFileByExtension(directory, "ini");
    QString scriptPath = findFileByExtension(directory, "js");

    return !scriptPath.isEmpty() && !metadataPath.isEmpty();
}

QString StreamingServiceLoader::getUserDirectory() {
    return QFileInfo(QStandardPaths::standardLocations(
            QStandardPaths::AppLocalDataLocation)[0], "plugins").absoluteFilePath();
}

QStringList StreamingServiceLoader::getSearchPaths() const {
    QStringList paths;

    paths.append(CMAKE_SOURCE_DIR + QString(QDir::separator()) + "plugins");
    paths.append(QFileInfo(QDir::currentPath(), "plugins").absoluteFilePath());
    // appimage path is in /$mountpoint/usr/bin/../share/mellowplayer/plugins
    paths.append(QFileInfo(qApp->applicationDirPath(), "../share/mellowplayer/plugins").absoluteFilePath());
    paths.append(QFileInfo(qApp->applicationDirPath(), "plugins").absoluteFilePath());
    paths.append(getUserDirectory());

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

bool StreamingServiceLoader::containsService(const QList<shared_ptr<StreamingService>>& services,
                                             shared_ptr<StreamingService>& toCheck) const {
    for (auto service: services) {
        if (*toCheck == *service)
            return true;
    }
    return false;
}
