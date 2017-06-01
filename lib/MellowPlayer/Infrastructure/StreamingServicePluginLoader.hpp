#pragma once

#include <MellowPlayer/Macros.hpp>
#include <MellowPlayer/Application/Interfaces/IStreamingServicePluginLoader.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(Application, ILogger)
PREDECLARE_MELLOWPLAYER_STRUCT(Entities, StreamingServicePluginMetadata)
PREDECLARE_MELLOWPLAYER_STRUCT(Entities, StreamingServiceStyle)

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class StreamingServicePluginLoader: public Application::IStreamingServicePluginLoader {
public:
    StreamingServicePluginLoader();
    QList<std::shared_ptr<Entities::StreamingServicePlugin>> load() const override;

private:
    std::unique_ptr<Entities::StreamingServicePlugin> loadPlugin(const QString &directory) const;
    QString findFileByExtension(const QString &directory, const QString &suffix) const;
    QString readFileContent(const QString &filePath) const;
    Entities::StreamingServicePluginMetadata readMetadata(const QString &filePath) const;
    Entities::StreamingServiceStyle readStyle(const QString &filePath) const;
    bool checkPluginDirectory(const QString &directory) const;
    QString getUserPluginsDirectory() const;
    QStringList getSearchPaths() const;
    bool containsPlugin(const QList<std::shared_ptr<Entities::StreamingServicePlugin>> &plugins,
                        std::shared_ptr<Entities::StreamingServicePlugin>& toCheck) const;

    Application::ILogger& logger;
};

END_MELLOWPLAYER_NAMESPACE
