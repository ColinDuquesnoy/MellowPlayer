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
#include <QWebView>
#include "mellowplayer/interfaces.h"
#include "mellowplayer/streamingservicesmanager.h"
#include "mellowplayer/services.h"

//---------------------------------------------------------
StreamingServicesManager::StreamingServicesManager(QObject* parent):
    QObject(parent),
    _currentService(NULL)
{

}

//---------------------------------------------------------
void StreamingServicesManager::_loadPlugin(IStreamingServiceIntegration* iService)
{
    if(!this->plugin(iService->metaData().name))
    {
        this->_plugins.append(iService);
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
IStreamingServiceIntegration* StreamingServicesManager::currentService() const
{
    return this->_currentService;
}

//---------------------------------------------------------
StreamingServicesList StreamingServicesManager::plugins() const
{
    return this->_plugins;
}

//---------------------------------------------------------
IStreamingServiceIntegration* StreamingServicesManager::plugin(
    const QString &serviceName) const
{
    foreach(IStreamingServiceIntegration* p, this->_plugins)
    {
        if(p->metaData().name == serviceName)
            return p;
    }
    return NULL;  // invalid plugin
}

//---------------------------------------------------------
bool StreamingServicesManager::startService(const QString& serviceName) {
    bool retVal = false;
    IStreamingServiceIntegration* p = this->plugin(serviceName);
    if(p && p != this->_currentService)
    {
        this->_currentService = p;
        qDebug() << "Starting service " << serviceName
                 << "(" << p->url() << ")";
        Services::webView()->load(this->_currentService->url());
        retVal = true;
    }
    return retVal;
}
