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
#include "mellowplayer/plugins.h"
#include "mellowplayer/extensionsmanager.h"
#include "mellowplayer/services.h"


//---------------------------------------------------------
ExtensionsManager::ExtensionsManager(QObject* parent):
    QObject(parent)
{

}

//---------------------------------------------------------
void ExtensionsManager::loadPlugin(IExtension* iExtension,
                                   QPluginLoader* pluginLoader)
{
    PluginMetaData meta = this->extractMetaData(pluginLoader);
    if(this->metaData.find(meta.name) == this->metaData.end())
    {
        this->metaData[meta.name] = meta;
        this->extensions[meta.name] = iExtension;
        iExtension->setup();
        qDebug() << "Extension plugin loaded: ";
        qDebug() << "  - name: " << meta.name;
        qDebug() << "  - version: " << meta.version;
    }
    else
    {
        qWarning() << "A plugin with the same name already exists, this plugin "
                      "instance will be discared";
    }
}

//---------------------------------------------------------
ExtensionsManager::PluginMetaData ExtensionsManager::extractMetaData(
        QPluginLoader* pluginLoader)
{
    PluginMetaData meta;
    meta.name = pluginLoader->metaData().value(
                "MetaData").toObject().value("name").toString();
    meta.author = pluginLoader->metaData().value(
                "MetaData").toObject().value("author").toString();
    meta.website = pluginLoader->metaData().value(
                "MetaData").toObject().value("website").toString();
    meta.version = pluginLoader->metaData().value(
                "MetaData").toObject().value("version").toString();
    meta.description= pluginLoader->metaData().value(
                "MetaData").toObject().value("description").toString();
    return meta;
}
