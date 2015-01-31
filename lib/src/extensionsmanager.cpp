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
#include "mellowplayer/playbackstatus.h"
#include "mellowplayer/services.h"

//---------------------------------------------------------
ExtensionsManager::ExtensionsManager(QObject* parent):
    QObject(parent)
{

}

//---------------------------------------------------------
void ExtensionsManager::loadPlugin(IExtension* iExtension)
{
    if(!plugin(iExtension->metaData().name))
    {
        m_plugins.append(iExtension);
        qDebug() << "Extension plugin loaded: ";
        qDebug() << "  - name: " << iExtension->metaData().name;
        qDebug() << "  - version: " << iExtension->metaData().version;
        if(QSettings().value(iExtension->metaData().name, true).toBool())
            iExtension->setup();
    }
    else
    {
        qWarning() << "A plugin with the same name already exists, this "
                      "plugin instance will be discared";
    }
}

//---------------------------------------------------------
void ExtensionsManager::teardown()
{
    foreach(IExtension* p, m_plugins)
        p->teardown();
}

//---------------------------------------------------------
IExtension *ExtensionsManager::plugin(const QString &name) const
{
    foreach(IExtension* p, m_plugins)
    {
        if(p->metaData().name == name)
            return p;
    }
    return NULL; // invalid plugin
}

//---------------------------------------------------------
ExtensionPluginList ExtensionsManager::plugins() const
{
    return m_plugins;
}
