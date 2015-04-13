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
    m_localSocket(new QLocalSocket()),
    m_localServer(new QLocalServer()),
    m_app(NULL)
{
    connect(m_localSocket, SIGNAL(connected()),
            this, SLOT(onSocketConnected()));

    connect(m_localServer, SIGNAL(newConnection()),
            this, SLOT(onNewConnection()));

    connect(m_localSocket, SIGNAL(error(QLocalSocket::LocalSocketError)),
            this, SLOT(onSocketError()));
}

//---------------------------------------------------------
SingleInstanceController::~SingleInstanceController()
{
    delete m_localServer;
    delete m_localSocket;
}

//---------------------------------------------------------
void SingleInstanceController::start(MellowPlayerApp* app)
{
    qDebug() << "Starting the application";
    m_app = app;
#ifndef QT_DEBUG
    m_localSocket->connectToServer(APP_NAME, QIODevice::WriteOnly);
#else
    app->initialize();
#endif
}

void SingleInstanceController::close()
{
    m_localServer->close();
}

//---------------------------------------------------------
void SingleInstanceController::onSocketConnected()
{

    // This means the server is already running and we have to exit.
    qDebug() << "Another instance is already running, quitting...";
    QTimer::singleShot(250, m_app, SLOT(quit()));
}

//---------------------------------------------------------
void SingleInstanceController::onSocketError()
{
    if(!m_localServer->listen(APP_NAME))
        qWarning() << "Failed to start local server, cannot ensure unique "
                      "application instance";
    m_app->initialize();
}

//---------------------------------------------------------
void SingleInstanceController::onNewConnection()
{
    m_app->raise();
}
