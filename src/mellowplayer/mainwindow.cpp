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

#include "mainwindow.h"
#include "player.h"
#include "plugins.h"
#include "ui_mainwindow.h"


//---------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    player = new Player(this);
    loadPlugins();
}

//---------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadPlugins()
{
    qDebug() << "Loading static plugins";
    foreach(QObject *plugin, QPluginLoader::staticInstances())
        loadPlugin(plugin);

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
    qDebug() << "Loading dynamic plugins from " << pluginsDir.absolutePath();
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = loader.instance();
        if (plugin)
            loadPlugin(plugin);
    }
}

void MainWindow::loadPlugin(QObject *plugin)
{
    qDebug() << "  -> loading plugin: " << plugin;
}
