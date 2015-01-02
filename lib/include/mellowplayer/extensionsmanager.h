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

#ifndef EXTENSIONSMANAGER_H
#define EXTENSIONSMANAGER_H

#include <QObject>

class QPluginLoader;
class IExtension;


/*!
 * \brief The ExtensionsManager class manages the collection of extension
 * plugins.
 */
class ExtensionsManager : public QObject
{
    Q_OBJECT
public:
    explicit ExtensionsManager(QObject* parent=0);

    struct PluginMetaData
    {
        QString name;
        QString author;
        QString website;
        QString version;
        QString description;
    };

    /*!
     * \brief Adds a cloud music service plugin to the list of managed plugins.
     *
     * **For internal uses only, all the plugins are added by the application.**
     *
     * \param service Service to add.
     * \param pluginLoader Pointer to the plugin loader that loaded the service
     *                     plugin.
     */
    void loadPlugin(IExtension* iExtension, QPluginLoader* pluginLoader);

private:
    PluginMetaData extractMetaData(QPluginLoader* pluginLoader);
    std::map<QString, IExtension*> extensions;
    std::map<QString, PluginMetaData> metaData;
};

#endif // EXTENSIONSMANAGER_H
