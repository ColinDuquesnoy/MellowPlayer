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
