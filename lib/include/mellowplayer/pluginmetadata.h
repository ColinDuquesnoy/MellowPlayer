#ifndef PLUGINMETADATA
#define PLUGINMETADATA

#include <QIcon>
#include <QString>


/*!
 * \brief The PluginMetaData struct contains the metadata of a
 * MellowPlayer plugin.
 */
struct PluginMetaData
{
    QString name;           /*!< Name of the plugin */
    QString author;         /*!< Author of the plugin */
    QString website;        /*!< Plugin website */
    QString version;        /*!< Plugin version */
    QString description;    /*!< Plugin description, use html for cloud
                                 services plugins */
    QIcon   icon;           /*!< Plugin icon, optional*/
};

#endif // PLUGINMETADATA

