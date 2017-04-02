#pragma once

#include <MellowPlayer/Macros.hpp>
#include <MellowPlayer/UseCases/Interfaces/IPluginLoader.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(UseCases, ILogger)
PREDECLARE_MELLOWPLAYER_STRUCT(Entities, PluginMetadata)
PREDECLARE_MELLOWPLAYER_STRUCT(Entities, PluginStyle)

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class PluginLoader: public UseCases::IPluginLoader {
public:
    PluginLoader();
    QList<std::shared_ptr<Entities::Plugin>> load() const override;

private:
    std::unique_ptr<Entities::Plugin> loadPlugin(const QString &directory) const;
    QString findFileByExtension(const QString &directory, const QString &suffix) const;
    QString readFileContent(const QString &filePath) const;
    Entities::PluginMetadata readMetadata(const QString &filePath) const;
    Entities::PluginStyle readStyle(const QString &filePath) const;
    bool checkPluginDirectory(const QString &directory) const;
    QString getUserPluginsDirectory() const;
    QStringList getSearchPaths() const;
    bool containsPlugin(const QList<std::shared_ptr<Entities::Plugin>> &plugins,
                        std::shared_ptr<Entities::Plugin>& toCheck) const;

    UseCases::ILogger& logger;
};

END_MELLOWPLAYER_NAMESPACE
