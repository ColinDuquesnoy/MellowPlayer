#ifndef PLUGINMETADATA
#define PLUGINMETADATA

#include <QIcon>
#include <QPluginLoader>
#include <QString>

struct PluginMetaData
{
    // Plugin metadata.
    QString name;   /*!< Name of the plugin */
    QString author; /*!< Author of the plugin */
    QString website;/*!< Plugin website */
    QString version;/*!< Plugin version */
    QIcon   icon;   /*!< Plugin icon */
};

PluginMetaData extractMetaData(QPluginLoader* pluginLoader);

#endif // PLUGINMETADATA

