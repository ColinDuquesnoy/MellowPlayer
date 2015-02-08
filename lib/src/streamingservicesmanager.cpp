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

#include <QFile>
#include <QPluginLoader>
#include <QMainWindow>
#include <QMessageBox>
#include <QWebView>
#include "mellowplayer/interfaces.h"
#include "mellowplayer/streamingservicesmanager.h"
#include "mellowplayer/services.h"


//---------------------------------------------------------
StreamingServicesManager::StreamingServicesManager(QObject* parent):
    QObject(parent),
    m_currentService(NULL)
{

}

//---------------------------------------------------------
void StreamingServicesManager::_loadPlugin(IStreamingService* iService)
{
    if(!plugin(iService->metaData().name))
    {
        m_plugins.append(iService);
        qDebug() << "Music streaming service integration plugin loaded: ";
        qDebug() << "  - name: " << iService->metaData().name;
        qDebug() << "  - version: " << iService->metaData().version;
    }
    else
    {
        qWarning() << "A plugin with the same name already exists, this plugin "
                      "instance will be discared";
    }
}

//---------------------------------------------------------
IStreamingService* StreamingServicesManager::currentService() const
{
    return m_currentService;
}

//---------------------------------------------------------
StreamingServicesList StreamingServicesManager::plugins() const
{
    return m_plugins;
}

//---------------------------------------------------------
IStreamingService* StreamingServicesManager::plugin(
    const QString &serviceName) const
{
    QString name = QString(serviceName).toLower().replace(" ", "");
    foreach(IStreamingService* p, m_plugins)
    {
        if(p->metaData().name.toLower().replace(" ", "") == name)
            return p;
    }
    return NULL;  // invalid plugin
}

//---------------------------------------------------------
bool StreamingServicesManager::startService(const QString& serviceName) {
    bool retVal = true;
    IStreamingService* p = plugin(serviceName);
    if(!p)
        retVal = false;
    else
    {
        if(!Services::hasFlash() && p->flashRequired())
        {
            QMessageBox::warning(
                Services::mainWindow(),
                tr("Flash player plugin missing"),
                tr("The flash player plugin is missing on your system.\n\n"
                   "This service cannot be used without flash.\nPlease "
                   "install the latest flash player plugin from adobe and try "
                   "again!"));
            retVal = false;
        }
        else if(p != m_currentService || Services::webView()->url() != p->url())
        {
            m_currentService = p;
            qDebug() << "Starting service " << serviceName
                     << "(" << p->url() << ")";
            Services::webView()->load(m_currentService->url());
            retVal = true;
        }
    }
    return retVal;
}
