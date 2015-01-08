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

#include <QPluginLoader>
#include <QFile>
#include "mellowplayer/interfaces.h"
#include "mellowplayer/extensionsmanager.h"
#include "mellowplayer/services.h"


//---------------------------------------------------------
ExtensionPlugin::ExtensionPlugin(QObject* parent):
    QObject(parent),
    interface(NULL)
{

}

//---------------------------------------------------------
ExtensionsManager::ExtensionsManager(QObject* parent):
    QObject(parent)
{

}

//---------------------------------------------------------
void ExtensionsManager::loadPlugin(IExtension* iExtension,
                                   QPluginLoader* pluginLoader)
{
    ExtensionPlugin* plugin = this->extractMetaData(pluginLoader);
    if(!this->plugin(plugin->name))
    {
        plugin->interface = iExtension;
        this->_plugins.append(plugin);
        qDebug() << tr("Extension plugin loaded: ");
        qDebug() << tr("  - name: ") << plugin->name;
        qDebug() << tr("  - version: ") << plugin->version;
        plugin->interface->setup();
    }
    else
    {
        qWarning() << tr("A plugin with the same name already exists, this plugin "
                         "instance will be discared");
    }
}

//---------------------------------------------------------
void ExtensionsManager::teardown()
{
    foreach(ExtensionPlugin* p, this->_plugins)
        p->interface->teardown();
}

//---------------------------------------------------------
ExtensionPlugin* ExtensionsManager::plugin(const QString &name) const
{
    foreach(ExtensionPlugin* p, this->_plugins)
    {
        if(p->name == name)
            return p;
    }
    return NULL; // invalid plugin
}

//---------------------------------------------------------
ExtensionPlugin *ExtensionsManager::extractMetaData(
        QPluginLoader* pluginLoader)
{
    ExtensionPlugin* plugin = new ExtensionPlugin(this);
    plugin->name = pluginLoader->metaData().value(
                "MetaData").toObject().value("name").toString();
    plugin->author = pluginLoader->metaData().value(
                "MetaData").toObject().value("author").toString();
    plugin->website = pluginLoader->metaData().value(
                "MetaData").toObject().value("website").toString();
    plugin->version = pluginLoader->metaData().value(
                "MetaData").toObject().value("version").toString();
    plugin->description= pluginLoader->metaData().value(
                "MetaData").toObject().value("description").toString();
    return plugin;
}
