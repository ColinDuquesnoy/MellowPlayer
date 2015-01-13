#ifndef PLUGINMETADATA
#define PLUGINMETADATA

#include <QIcon>
#include <QPluginLoader>
#include <QString>
#include "mellowplayer/exports.h"


struct DLL_EXPORT PluginMetaData
{
    // Plugin metadata.
    QString name;   /*!< Name of the plugin */
    QString author; /*!< Author of the plugin */
    QString website;/*!< Plugin website */
    QString version;/*!< Plugin version */
    QIcon   icon;   /*!< Plugin icon */
};

DLL_EXPORT PluginMetaData extractMetaData(QPluginLoader* pluginLoader);

#endif // PLUGINMETADATA

