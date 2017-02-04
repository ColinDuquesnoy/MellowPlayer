#pragma once

#include <MellowPlayer/Macros.hpp>
#include <MellowPlayer/UseCases.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class PluginLoader: public UseCases::IPluginLoader {
public:
    PluginLoader(UseCases::LoggingManager& loggingManager);
    Entities::PluginList loadPlugins() const override;

private:
    std::unique_ptr<Entities::Plugin> loadPlugin(const QString &directory) const;
    QString findFileByExtension(const QString &directory, const QString &suffix) const;
    QString readFileContent(const QString &filePath) const;
    Entities::PluginMetadata readMetadata(const QString &filePath) const;
    bool checkPluginDirectory(const QString &directory) const;
    QString getUserPluginsDirectory() const;
    QStringList getSearchPaths() const;

    UseCases::ILogger& logger_;
};

END_MELLOWPLAYER_NAMESPACE
