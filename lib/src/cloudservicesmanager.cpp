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
#include <QtWebKitWidgets/QWebView>
#include "mellowplayer/plugins.h"
#include "mellowplayer/cloudservicesmanager.h"
#include "mellowplayer/services.h"


//---------------------------------------------------------
CloudServicesManager::CloudServicesManager(QObject* parent):
    QObject(parent),
    _currentService(NULL)
{

}

//---------------------------------------------------------
void CloudServicesManager::loadPlugin(ICloudMusicService* iService,
                                      QPluginLoader* pluginLoader)
{
    PluginMetaData meta = this->extractMetaData(pluginLoader);
    if(this->_metaData.find(meta.name) == this->_metaData.end())
    {
        this->_metaData[meta.name] = meta;
        this->_services[meta.name] = iService;
        qDebug() << "Cloud service integration plugin loaded: ";
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
CloudServicesManager::PluginMetaData CloudServicesManager::extractMetaData(
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
    meta.icon = QIcon(pluginLoader->metaData().value(
                "MetaData").toObject().value("icon").toString());
    meta.description= pluginLoader->metaData().value(
                "MetaData").toObject().value("description").toString();
    QString htmlDescPath = pluginLoader->metaData().value(
                "MetaData").toObject().value("html_description").toString();
    QFile file(htmlDescPath);
    if(!file.open(QIODevice::ReadOnly)) {
        qWarning() << "failed to open html description file: " << htmlDescPath;
    }
    else
    {
        QTextStream in(&file);
        meta.htmlDescription = in.readAll();
    }

    return meta;
}

//---------------------------------------------------------
ICloudMusicService* CloudServicesManager::currentService() const
{
    return this->_currentService;
}

//---------------------------------------------------------
CloudServicesManager::MetaDataList CloudServicesManager::allMetaData() const
{
    MetaDataList values = this->_metaData.values();
    qSort(values.begin(), values.end(),
          [](const CloudServicesManager::PluginMetaData& a,
             const CloudServicesManager::PluginMetaData& b){
           return a.name < b.name;
          });
    return values;
}

//---------------------------------------------------------
CloudServicesManager::PluginMetaData
    CloudServicesManager::metaData(const QString &serviceName)
{
    if(this->_metaData.find(serviceName) != this->_metaData.end())
        return this->_metaData[serviceName];
    return PluginMetaData();
}

//---------------------------------------------------------
bool CloudServicesManager::startService(const QString& serviceName)
{
    bool retVal = false;
    if(this->_services.find(serviceName) != this->_services.end())
    {
        this->_currentService = this->_services[serviceName];
        Services::webView()->load(this->_currentService->url());
        retVal = true;
    }
    return retVal;
}
