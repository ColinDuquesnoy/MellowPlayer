#pragma once

#include <MellowPlayer/Macros.hpp>
#include <MellowPlayer/Entities.hpp>
#include <MellowPlayer/UseCases.hpp>
#include <MellowPlayer/Logging.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class PluginLoader: public UseCases::IPluginLoader {
public:
    PluginLoader();
    Entities::PluginList load() const override;

private:
    std::unique_ptr<Entities::Plugin> loadPlugin(const QString &directory) const;
    QString findFileByExtension(const QString &directory, const QString &suffix) const;
    QString readFileContent(const QString &filePath) const;
    Entities::PluginMetadata readMetadata(const QString &filePath) const;
    bool checkPluginDirectory(const QString &directory) const;
    QString getUserPluginsDirectory() const;
    QStringList getSearchPaths() const;
    bool containsPlugin(const Entities::PluginList &plugins, std::shared_ptr<Entities::Plugin>& toCheck) const;

    Logging::ILogger& logger;
};

END_MELLOWPLAYER_NAMESPACE
