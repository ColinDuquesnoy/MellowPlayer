#include "pluginmanager.h"

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
            pluginsDir.cdUp();
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
#ifdef Q_OS_LINUX
    dirs.append(QDir("/usr/share/mellowplayer/plugins"));
    dirs.append(QDir("/usr/share/local/mellowplayer/plugins"));
#endif
    foreach(QDir dir, dirs) {
        QStringList subdirs;
        subdirs.append("services");
        subdirs.append("extensions");
        foreach(QString subdir, subdirs){
            QDir pluginDir(dir);
            if(pluginDir.cd(subdir)){
                qDebug() << "Loading plugins from " << pluginDir.absolutePath();
                foreach (QString fileName, pluginDir.entryList(QDir::Files)) {
                    QPluginLoader loader(pluginDir.absoluteFilePath(fileName));
                    loadPlugin(&loader);
                }
            }
        }
    }
}

//---------------------------------------------------------
void loadPlugin(QPluginLoader* loader)
{
    QObject *plugin = loader->instance();
    if(plugin)
    {
        qDebug() << "Loading plugin: " << plugin;

        // cloud service interface
        ICloudMusicService* iService = qobject_cast<
                ICloudMusicService*>(plugin);
        if(iService)
        {
            Services::cloudServices()->loadPlugin(iService, loader);
            return;
        }

        // extension interface
        // todo
    }
}
