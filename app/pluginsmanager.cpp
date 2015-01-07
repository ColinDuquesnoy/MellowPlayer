#include "pluginsmanager.h"

#include <QPluginLoader>
#include <QtCore>

#include "mellowplayer.h"


void loadPlugin(QPluginLoader* plugin);

//---------------------------------------------------------
QDir getLocalPluginsDir()
{
    QDir pluginsDir(qApp->applicationDirPath());
    #if defined(Q_OS_WIN)
        if (pluginsDir.dirName().toLower() == "debug" ||
                pluginsDir.dirName().toLower() == "release")
            pluginsDir.cdUp();
    #elif defined(Q_OS_MAC)
        if (pluginsDir.dirName() == "MacOS") {
            pluginsDir.cdUp();
        }
    #endif
    pluginsDir.cd("plugins");
    QDir servicesPluginsDir = QDir(pluginsDir);

    return servicesPluginsDir;
}

void loadPlugins()
{
    QList<QDir> dirs = QList<QDir>();
    dirs.append(getLocalPluginsDir());
    // allow user to try their plugins by starting the app from a directory
    // where they built their plugins, without needing to install the compiled
    // plugin anywhere
    dirs.append(QDir::currentPath());
    QDir home = QDir::home();
#if defined(Q_OS_LINUX)
    // users plugins (in home directory)
    #define HOME_PLUGINS ".local/share/mellowplayer/plugins"
    QString pth = home.path() + "/" + HOME_PLUGINS;
    qDebug() << pth;
    QDir().mkpath(pth);
    home.cd(HOME_PLUGINS);
    dirs.append(home);
    // builtin plugins installed in PREFIX/share/mellowplayer/plugins
    dirs.append(QDir("/usr/share/mellowplayer/plugins"));
    dirs.append(QDir("/usr/share/local/mellowplayer/plugins"));
#elif defined(Q_OS_MAC)
    // todo
#elif defined(Q_OS_WIN32)
    // todo
#endif
    foreach(QDir pluginDir, dirs) {
        if(!pluginDir.exists())
            continue;
        qDebug() << "Loading plugins from " << pluginDir.absolutePath();
        foreach (QString fileName, pluginDir.entryList(QDir::Files))
        {
            QString work(fileName);
            // Skip invalid plugin filenames (a plugin needs mpp_ prefix)
            if(!work.replace("lib", "").startsWith("mpp_"))
                continue;
            QPluginLoader loader(pluginDir.absoluteFilePath(fileName));
            loadPlugin(&loader);
        }
    }
}

//---------------------------------------------------------
void loadPlugin(QPluginLoader* loader)
{
    QObject *plugin = loader->instance();
    if(plugin)
    {
        qDebug() << "Loading plugin " << plugin
                 << " (" << loader->fileName() << ")";

        // cloud service interface
        ICloudMusicService* iService = qobject_cast<
                ICloudMusicService*>(plugin);
        if(iService)
        {
            Services::cloudServices()->_loadPlugin(iService, loader);
            return;
        }

        // Extension interface
        IExtension* iExtension = qobject_cast<IExtension*>(plugin);
        if(iExtension)
        {
            Services::extensions()->loadPlugin(iExtension, loader);
            return;
        }
    }
}
