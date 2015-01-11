//---------------------------------------------------------
//
// This file is part of MellowPlayer.
//
// MellowPlayer is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MellowPlayer is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with MellowPlayer.  If not, see <http://www.gnu.org/licenses/>.
//
//---------------------------------------------------------

#ifndef CLOUDSERVICESMANAGER_H
#define CLOUDSERVICESMANAGER_H

#include <QIcon>
#include <QMap>
#include <QObject>
#include "mellowplayer/pluginmetadata.h"

class ICloudMusicService;

/*!
 * \brief The Plugin class regroups the plugin interface with it's metada.
 */
class CloudServicePlugin: public QObject
{
    Q_OBJECT
public:
    explicit CloudServicePlugin(ICloudMusicService* interface,
                                const PluginMetaData& meta,
                                QObject* parent=NULL);

    PluginMetaData metaData;  /*!< Plugins meta data */
    ICloudMusicService* interface;  /*!< Pointer to the plugin interface */
};

typedef QList<CloudServicePlugin*> CloudPluginList;

/*!
 * \brief The CloudServicesManager class manages the collection of cloud music
 * service plugins and let you easily start or change the current service.
 *
 */
class CloudServicesManager : public QObject
{
    Q_OBJECT
public:

    explicit CloudServicesManager(QObject* parent=0);

    /*!
     * \internal
     * \brief Loads a cloud music service plugin.
     *
     * **For internal uses only, all the plugins are loaded by the application.**
     *
     * \param service Service to add.
     * \param pluginLoader Pointer to the plugin loader that loaded the service
     *                     plugin.
     */
    void _loadPlugin(ICloudMusicService* iService, QPluginLoader* pluginLoader);

    /*!
     * @brief Starts the current service.
     *
     * Load the cloud service URL and set the service plugin as the
     * currentService.
     *
     * @return Start status: true on succes, false on error.
     */
    bool startService(const QString& serviceName);

    /*!
     * \brief Gets the current cloud music service, started by startService.
     *
     * \returns Current cloud music service interface or NULL if no service has
     * been started.
     */
    ICloudMusicService* currentService() const;

    /*!
     * \brief Returns the list of loaded plugins.
     */
    CloudPluginList plugins() const;

    /*!
     * \brief Gets a plugin by specifying its name.
     *
     * Note that if no plugin could be found, the method will return
     * an invalid Plugin. For that reason, you should always check plugin
     * validity using Plugin::isValid().
     *
     * \param Name of the plugin to retrieve.
     */
    CloudServicePlugin* plugin(const QString& serviceName) const;

signals:

public slots:

private:
    CloudPluginList _plugins;
    ICloudMusicService* _currentService;
};

#endif // CLOUDSERVICESMANAGER_H
