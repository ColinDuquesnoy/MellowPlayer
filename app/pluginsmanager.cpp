#include "pluginsmanager.h"

#include <QPluginLoader>
#include <QtCore>

#include "mellowplayer.h"

//---------------------------------------------------------
void loadPlugin(QObject* plugin)
{
    // cloud service interface
    ICloudMusicService* iService = qobject_cast<
            ICloudMusicService*>(plugin);
    if(iService)
    {
        Services::cloudServices()->_loadPlugin(iService);
        return;
    }

    // Extension interface
    IExtension* iExtension = qobject_cast<IExtension*>(plugin);
    if(iExtension)
    {
        Services::extensions()->loadPlugin(iExtension);
        return;
    }
}

void loadPlugins()
{
    // static plugins
    foreach (QObject *plugin, QPluginLoader::staticInstances())
        loadPlugin(plugin);
}
