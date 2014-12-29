//---------------------------------------------------------
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
//---------------------------------------------------------

#include <QPluginLoader>
#include <QtCore>
#include "mellowplayer.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"


//---------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Services::_setWebView(ui->webView);
    loadPlugins();
}

//---------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}

//---------------------------------------------------------
void MainWindow::loadPlugins()
{
    QDir pluginsDir(qApp->applicationDirPath());

    #if defined(Q_OS_WIN)
        if (pluginsDir.dirName().toLower() == "debug" ||
                pluginsDir.dirName().toLower() == "release")
            pluginsDir.cdUp();
    #elif defined(Q_OS_MAC)
        if (pluginsDir.dirName() == "MacOS") {
            pluginsDir.cdUp();
            pluginsDir.cdUp();
            pluginsDir.cdUp();
        }
    #endif
    pluginsDir.cd("plugins");

    QDir servicesPluginsDir = QDir(pluginsDir);
    servicesPluginsDir.cd("services");

    qDebug() << "Loading plugins from " << servicesPluginsDir.absolutePath();

    foreach (QString fileName, servicesPluginsDir.entryList(QDir::Files)) {
        QPluginLoader loader(servicesPluginsDir.absoluteFilePath(fileName));
        this->loadPlugin(&loader);
    }
}

//---------------------------------------------------------
void MainWindow::loadPlugin(QPluginLoader* loader)
{
    QObject *plugin = loader->instance();
    qDebug() << "Loading plugin: " << plugin;

    // cloud service interface
    ICloudMusicService* iService = qobject_cast<
            ICloudMusicService*>(plugin);
    if(iService)
    {
        Services::cloudServicesManager()->loadPlugin(iService, loader);
        return;
    }

    // extension interface
    // todo
}
