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

#ifndef SINGLEINSTANCECONTROLLER_H
#define SINGLEINSTANCECONTROLLER_H

#include <QObject>
#include <QtNetwork>

class MellowPlayerApp;

/*!
 * \brief The SingleApplication class is the base class for our application.
 *
 * We ensure that a single application instance is running by using a local
 * server. We first check if we can connect to the local server. In case of
 * error we start the app (no other instance is running since we could not
 * connect to the server). In case of success we just quit the application.
 * If the local server receives a new connection, we simply raise the main
 * window, this gives the illusion no other instance has been started.
 */
class SingleInstanceController : public QObject
{
    Q_OBJECT
public:
    explicit SingleInstanceController(QObject *parent=0);
    ~SingleInstanceController();

    /*!
     * \brief Starts the application and make sure one single instance is
     * running.
     */
    void start(MellowPlayerApp* app);

public slots:
    void onSocketConnected();
    void onSocketError(QLocalSocket::LocalSocketError error);
    void onNewConnection();

private:
    QLocalSocket* localSocket;
    QLocalServer* localServer;
    MellowPlayerApp* app;
};



#endif // SINGLEINSTANCECONTROLLER_H
