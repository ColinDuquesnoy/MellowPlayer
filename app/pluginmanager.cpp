#include "pluginmanager.h"

#include <QPluginLoader>
#include <QtCore>

#include "mellowplayer.h"


void loadPlugin(QPluginLoader* plugin);

//---------------------------------------------------------
void loadPlugins()
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
    servicesPluginsDir.cd("services");

    qDebug() << "Loading plugins from " << servicesPluginsDir.absolutePath();

    foreach (QString fileName, servicesPluginsDir.entryList(QDir::Files)) {
        QPluginLoader loader(servicesPluginsDir.absoluteFilePath(fileName));
        loadPlugin(&loader);
    }
}

//---------------------------------------------------------
void loadPlugin(QPluginLoader* loader)
{
    QObject *plugin = loader->instance();
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
