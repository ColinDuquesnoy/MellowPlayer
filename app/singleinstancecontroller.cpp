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
            this, SLOT(onSocketError(QLocalSocket::LocalSocketError)));
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
    qDebug() << "Starting the application";
    this->app = app;
    this->localSocket->connectToServer(APP_NAME, QIODevice::WriteOnly);
}

//---------------------------------------------------------
void SingleInstanceController::onSocketConnected()
{
    // This means the server is already running and we have to exit.
    qDebug() << "Another instance is already running, quitting...";
    QTimer::singleShot(250, &this->app->quit);
}

//---------------------------------------------------------
void SingleInstanceController::onSocketError(QLocalSocket::LocalSocketError error)
{
    qDebug() << "No other instances are running, performing startup";
    if(!this->localServer->listen(APP_NAME))
        qWarning() << "Failed to start local server, cannot ensure unique "
                      "application instance (error=" << error << ")";
    this->app->initialize();
}

//---------------------------------------------------------
void SingleInstanceController::onNewConnection()
{
    this->app->raise();
}
