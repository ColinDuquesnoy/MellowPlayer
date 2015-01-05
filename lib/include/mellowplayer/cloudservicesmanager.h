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

class QPluginLoader;
class ICloudMusicService;


/*!
 * \brief The CloudServicesManager class manages the collection of cloud music
 * services and let you start and changed the current service.
 *
 */
class CloudServicesManager : public QObject
{
    Q_OBJECT
public:

    explicit CloudServicesManager(QObject* parent=0);

    struct PluginMetaData
    {
        QString name;
        QString author;
        QString website;
        QString version;
        QIcon icon;
        QString description;
        QString htmlDescription;

        /*! Checks if the meta data are valid, i.e. they correspond to a
         * plugin instance */
        bool isValid() const { return name != ""; }
    };

    typedef QList<PluginMetaData> MetaDataList;

    /*!
     * \brief Loads a cloud music service plugin.
     *
     * **For internal uses only, all the plugins are loaded by the application.**
     *
     * \param service Service to add.
     * \param pluginLoader Pointer to the plugin loader that loaded the service
     *                     plugin.
     */
    void loadPlugin(ICloudMusicService* iService, QPluginLoader* pluginLoader);

    /*!
     * @brief Starts the current service.
     *
     * Load the cloud service URL and set the service as the currentService.
     *
     * @return True if the service could be started, False if the service does
     * not exists.
     */
    bool startService(const QString& serviceName);

    /*!
     * \brief Gets the current cloud music service, started by startService.
     *
     * \returns CUrrent cloud music service or NULL if no service has been
     * started.
     */
    ICloudMusicService* currentService() const;

    /*!
     * \brief Returns a sorted list of all plugins' metadata.
     */
    MetaDataList allMetaData() const;

    /*!
     * \brief Gets the metadata structure for a given service
     * \param Name of the service
     * \return Meta data of the given service
     */
    PluginMetaData metaData(const QString& serviceName);

signals:

public slots:

private:
    PluginMetaData extractMetaData(QPluginLoader* pluginLoader);
    QMap<QString, ICloudMusicService*> _services;
    QMap<QString, PluginMetaData> _metaData;
    ICloudMusicService* _currentService;
};

#endif // CLOUDSERVICESMANAGER_H
