#pragma once

#include <MellowPlayer/Macros.hpp>
#include <QtCore/QString>
#include <MellowPlayer/Entities/Plugin.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class PluginLoaderHelper {
public:
    QString findFileByExtension(const QString &directory, const QString &suffix);
    QString readFileContent(const QString &filePath);
    void readMetadata(const QString &filePath, Entities::Plugin &plugin);
    Entities::Plugin loadPlugin(const QString &directory);
    bool checkPluginDirectory(const QString &directory);
    QString getUserPluginsDirectory();
    QStringList getSearchPaths();
};

END_MELLOWPLAYER_NAMESPACE