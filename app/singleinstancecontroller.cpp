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
#include "singleinstancecontroller.h"
#include "application.h"

#define APP_NAME "MellowPlayer"


//---------------------------------------------------------
SingleInstanceController::SingleInstanceController(QObject* parent):
    QObject(parent),
    localSocket(new QLocalSocket()),
    localServer(new QLocalServer()),
    app(NULL)
{
    connect(this->localSocket, &QLocalSocket::connected,
            this, &SingleInstanceController::onSocketConnected);

    connect(this->localServer, &QLocalServer::newConnection,
            this, &SingleInstanceController::onNewConnection);

    connect(this->localSocket, SIGNAL(error(QLocalSocket::LocalSocketError)),
            this, SLOT(onSocketError()));
}

//---------------------------------------------------------
SingleInstanceController::~SingleInstanceController()
{
    delete this->localServer;
    delete this->localSocket;
}

//---------------------------------------------------------
void SingleInstanceController::start(MellowPlayerApp* app)
{
    qDebug() << tr("Starting the application");
    this->app = app;
    this->localSocket->connectToServer(APP_NAME, QIODevice::WriteOnly);
}

//---------------------------------------------------------
void SingleInstanceController::onSocketConnected()
{
    // This means the server is already running and we have to exit.
    qDebug() << tr("Another instance is already running, quitting...");
    QTimer::singleShot(250, &this->app->quit);
}

//---------------------------------------------------------
void SingleInstanceController::onSocketError()
{
#ifndef QT_DEBUG
    if(!this->localServer->listen(APP_NAME))
        qWarning() << tr("Failed to start local server, cannot ensure unique "
                         "application instance");
#endif
    this->app->initialize();
}

//---------------------------------------------------------
void SingleInstanceController::onNewConnection()
{
    this->app->raise();
}
