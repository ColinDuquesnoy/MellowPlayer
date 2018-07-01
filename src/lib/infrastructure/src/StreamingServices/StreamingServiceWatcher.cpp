#include <MellowPlayer/Infrastructure/StreamingServices/StreamingServiceWatcher.hpp>
#include <MellowPlayer/Infrastructure/StreamingServices/StreamingServiceLoader.hpp>
#include <QtCore/QDir>
#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>

using namespace std;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

StreamingServiceWatcher::StreamingServiceWatcher() : logger_(Loggers::logger("StreamingServiceWatcher"))
{
    connect(&fileSystemWatcher_, &QFileSystemWatcher::fileChanged, this, &StreamingServiceWatcher::onFileChanged);
}

void StreamingServiceWatcher::watch(StreamingService& serviceToWatch)
{
    const QString pluginDirectory = serviceToWatch.pluginDirectory();
    const QString themePath = QDir::cleanPath(pluginDirectory + "/" + "theme.json");
    const QString scriptPath = QDir::cleanPath(pluginDirectory + "/" + "integration.js");

    pluginInfo_.insert(pluginDirectory, new PluginInfo(serviceToWatch, scriptPath, themePath, this));

    watchPath(themePath);
    watchPath(scriptPath);
}

void StreamingServiceWatcher::watchPath(const QString& path)
{
    LOG_TRACE(logger_, "Watching path: " + path);
    fileSystemWatcher_.addPath(path);
}

void StreamingServiceWatcher::onFileChanged(const QString& path)
{
    LOG_INFO(logger_, "Plugin file changed: " + path);
    QFileInfo fileInfo(path);
    const QString pluginDir = fileInfo.dir().absolutePath();
    const QString name = fileInfo.baseName();
    StreamingService& service = pluginInfo_[pluginDir]->service_;

    if (name == "integration") {
        service.updateScript(StreamingServiceLoader::readFileContent(path));
    } else {
        Theme theme = StreamingServiceLoader::readTheme(path);
        service.updateTheme(theme);
    }

    fileSystemWatcher_.removePath(path);
    fileSystemWatcher_.addPath(path);
}

StreamingServiceWatcher::PluginInfo::PluginInfo(StreamingService &service, QString scriptPath, QString themePath,
                                                QObject *parent)
        : QObject(parent), service_(service), scriptPath_(scriptPath), themePath_(themePath)
{
}
