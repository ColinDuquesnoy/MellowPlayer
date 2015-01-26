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

#ifndef STREAMINGSERVICESMANAGER_H
#define STREAMINGSERVICESMANAGER_H

#include <QIcon>
#include <QMap>
#include <QObject>
#include "mellowplayer/pluginmetadata.h"

class IStreamingService;

typedef QList<IStreamingService*> StreamingServicesList;

/*!
 * \brief The StreamingServicesManager class manages the collection of
 * music streaming service integration plugins and let you easily start or
 * change the current streaming service.
 */
class StreamingServicesManager : public QObject
{
    Q_OBJECT
public:

    explicit StreamingServicesManager(QObject* parent=0);

    /*!
     * \internal
     * \brief Loads a music streaming service integration plugin.
     *
     * **For internal uses only, all the plugins are loaded by the
     * application.**
     *
     * \param service Service to add.
     * \param pluginLoader Pointer to the plugin loader that loaded the service
     *                     plugin.
     */
    void _loadPlugin(IStreamingService* iService);

    /*!
     * @brief Starts the current service.
     *
     * Load the streaming service URL and set the service plugin as the
     * currentService.
     *
     * @return Start status: true on succes, false on error.
     */
    bool startService(const QString& serviceName);

    /*!
     * \brief Gets the current streaming service, started by startService.
     *
     * \returns Current music streaming service integration interface or NULL
     * if no service has been started yet.
     */
    IStreamingService* currentService() const;

    /*!
     * \brief Returns the list of loaded plugins.
     */
    StreamingServicesList plugins() const;

    /*!
     * \brief Gets a plugin by specifying its name.
     *
     * Note that if no plugin could be found, the method will return
     * an invalid Plugin. For that reason, you should always check plugin
     * validity using Plugin::isValid().
     *
     * \param serviceName of the plugin to retrieve.
     */
    IStreamingService* plugin(const QString& serviceName) const;

signals:

public slots:

private:
    StreamingServicesList _plugins;
    IStreamingService* _currentService;
};

#endif // STREAMINGSERVICESMANAGER_H
