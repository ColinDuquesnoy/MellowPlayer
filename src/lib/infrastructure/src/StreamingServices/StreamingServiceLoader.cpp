#include <MellowPlayer/Infrastructure/StreamingServices/StreamingServiceLoader.hpp>
#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Domain/Settings/SettingsCategory.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Infrastructure/Theme/ThemeLoader.hpp>
#include <QDebug>
#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QJsonDocument>
#include <QtCore/QSettings>
#include <QtCore/QStandardPaths>
#include <QtGui/QIcon>
#include <MellowPlayer/Infrastructure/BuildConfig.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;
using namespace std;

StreamingServiceLoader::StreamingServiceLoader(Settings &settings)
        : logger_(Loggers::logger("StreamingServiceLoader")),
          _settings(settings)
{
}

QList<shared_ptr<StreamingService>> StreamingServiceLoader::load() const
{
    QList<shared_ptr<StreamingService>> services;
    for (const QString& path : searchPaths()) {
        if (!QDir(path).exists()) {
            LOG_DEBUG(logger_, "skipping plugin directory: " << path.toStdString().c_str() << " (directory not found)");
            continue;
        }
        LOG_DEBUG(logger_, "looking for services in " << path.toStdString().c_str());
        for (const QFileInfo& directory : QDir(path).entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot)) {
            if (checkServiceDirectory(directory.absoluteFilePath())) {
                shared_ptr<StreamingService> service = loadService(directory.absoluteFilePath());
                if (service == nullptr)
                    continue;
                if (service->isValid() && !containsService(services, service)) {
                    LOG_INFO(logger_, service->name() + " streamingService successfully loaded (from \"" + directory.absoluteFilePath() + "\")");
                    services.append(service);
                } else {
                    LOG_DEBUG(logger_, "skipping streamingService " + service->name() + ", already loaded from another source or invalid");
                }
            }
        }
    }

    return services;
}

QString StreamingServiceLoader::findFile(const QString& directory, const QString& suffix) const
{
    foreach (const QFileInfo& fileInfo, QDir(directory).entryInfoList(QDir::Files | QDir::NoDotAndDotDot)) {
        if (fileInfo.isFile() && fileInfo.absoluteFilePath().endsWith(suffix))
            return fileInfo.absoluteFilePath();
    }
    return QString();
}

QString StreamingServiceLoader::readFileContent(const QString& filePath)
{
    QString retVal;

    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        retVal = in.readAll();
    }

    return retVal;
}

std::shared_ptr<SettingsCategory> StreamingServiceLoader::readSettings(const QString &name, const QString& filePath) const
{
    if (filePath.isEmpty() || !QFileInfo::exists(filePath))
        return nullptr;
    auto content = readFileContent(filePath);
    auto jsonDocument = QJsonDocument::fromJson(content.toUtf8());
    SettingsCategory::Data settingsData;
    settingsData.name = "Options";
    settingsData.key = name.toLower().trimmed() + "_options";
    settingsData.parameters = jsonDocument.array();
    return make_shared<SettingsCategory>(settingsData, &_settings);
}

StreamingServiceMetadata StreamingServiceLoader::readMetadata(const QString& filePath) const
{
    QSettings meta(filePath, QSettings::IniFormat);

    QString supportedPlatforms = meta.value("supported_platforms").toString();

    if (platformFilters_.match(supportedPlatforms)) {
        StreamingServiceMetadata serviceMetadata;
        serviceMetadata.author = meta.value("author").toString();
        serviceMetadata.authorWebsite = meta.value("author_website").toString();
        serviceMetadata.logoPath = QFileInfo(QFileInfo(filePath).dir(), meta.value("icon").toString()).absoluteFilePath();
        serviceMetadata.name = meta.value("name").toString();
        serviceMetadata.url = meta.value("url").toString();
        serviceMetadata.version = meta.value("version").toString();

        return serviceMetadata;
    }
    else
        throw runtime_error("plugin not supported");
}

Theme StreamingServiceLoader::readTheme(const QString& filePath)
{

    static ThemeLoader loader;
    return loader.load(filePath);
}

unique_ptr<StreamingService> StreamingServiceLoader::loadService(const QString& directory) const
{
    QString metadataPath = findFile(directory, "ini");
    QString scriptPath = findFile(directory, "js");
    QString themePath = findFile(directory, "theme.json");
    QString settingsPath = findFile(directory, "settings.json");
    QString locale = QLocale::system().name().split("_")[0];
    StreamingServiceMetadata metadata;
    try {
         metadata = readMetadata(metadataPath);
    }
    catch (std::runtime_error&) {
        LOG_INFO(logger_, "plugin is not supported on this platform");
        return nullptr;
    }
    metadata.pluginDirectory = directory;
    metadata.script = readFileContent(scriptPath);
    metadata.scriptPath = scriptPath;
    Theme theme = readTheme(themePath);
    auto settings = readSettings(metadata.name, settingsPath);
    return make_unique<StreamingService>(metadata, theme, settings);
}

bool StreamingServiceLoader::checkServiceDirectory(const QString& directory) const
{
    QString metadataPath = findFile(directory, "ini");
    QString scriptPath = findFile(directory, "js");

    return !scriptPath.isEmpty() && !metadataPath.isEmpty();
}

QString StreamingServiceLoader::userDirectory()
{
    return QFileInfo(QStandardPaths::standardLocations(QStandardPaths::AppLocalDataLocation)[0], "plugins").absoluteFilePath();
}

QStringList StreamingServiceLoader::searchPaths() const
{
    QStringList paths;

    paths.append(BuildConfig::getSourceDir() + QDir::separator() + "src/plugins/web");
    paths.append(QFileInfo(QDir::currentPath(), "plugins").absoluteFilePath());
    // appimage path is in /$mountpoint/usr/bin/../share/mellowplayer/plugins
    paths.append(QFileInfo(qApp->applicationDirPath(), "../share/mellowplayer/plugins").absoluteFilePath());
    paths.append(QFileInfo(qApp->applicationDirPath(), "plugins").absoluteFilePath());
    paths.append(userDirectory());

#ifdef Q_OS_MAC
    QDir pluginsDir(qApp->applicationDirPath());
    pluginsDir.cdUp();
    pluginsDir.cd("PlugIns");
    pluginsDir.cd("services");
    pluginsDir.cd("web");
    paths.append(pluginsDir.path());
#endif

#if defined(Q_OS_LINUX) || defined(Q_OS_FREEBSD)
    paths.append("/usr/share/mellowplayer/plugins");
    paths.append("/usr/local/share/mellowplayer/plugins");
#endif

    paths.removeDuplicates();

    return paths;
}

bool StreamingServiceLoader::containsService(const QList<shared_ptr<StreamingService>>& services, shared_ptr<StreamingService>& toCheck) const
{
    for (auto service : services) {
        if (*toCheck == *service)
            return true;
    }
    return false;
}
