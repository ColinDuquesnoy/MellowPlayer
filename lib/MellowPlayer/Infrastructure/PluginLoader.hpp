#pragma once

#include <MellowPlayer/Macros.hpp>
#include <MellowPlayer/UseCases/Interfaces/IPluginLoader.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(UseCases, ILogger)
PREDECLARE_MELLOWPLAYER_STRUCT(UseCases, PluginMetadata)
PREDECLARE_MELLOWPLAYER_STRUCT(UseCases, PluginStyle)

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class PluginLoader: public UseCases::IPluginLoader {
public:
    PluginLoader();
    QList<std::shared_ptr<UseCases::Plugin>> load() const override;

private:
    std::unique_ptr<UseCases::Plugin> loadPlugin(const QString &directory) const;
    QString findFileByExtension(const QString &directory, const QString &suffix) const;
    QString readFileContent(const QString &filePath) const;
    UseCases::PluginMetadata readMetadata(const QString &filePath) const;
    UseCases::PluginStyle readStyle(const QString &filePath) const;
    bool checkPluginDirectory(const QString &directory) const;
    QString getUserPluginsDirectory() const;
    QStringList getSearchPaths() const;
    bool containsPlugin(const QList<std::shared_ptr<UseCases::Plugin>> &plugins,
                        std::shared_ptr<UseCases::Plugin>& toCheck) const;

    UseCases::ILogger& logger;
};

END_MELLOWPLAYER_NAMESPACE
