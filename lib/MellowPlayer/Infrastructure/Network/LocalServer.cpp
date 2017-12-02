#include "LocalServer.hpp"
#include "LocalSocket.hpp"

using namespace std;
using namespace MellowPlayer::Infrastructure;

LocalServer::LocalServer(IFactory<ILocalSocket>& localSocketFactory, const QString& serverName)
        : localSocketFactory_(localSocketFactory), serverName_(serverName)
{
    QLocalServer::removeServer(serverName);
    connect(&qLocalServer_, &QLocalServer::newConnection, this, &ILocalServer::newConnection);
}

LocalServer::~LocalServer()
{
    close();
}

void LocalServer::close()
{
    qLocalServer_.close();
}

bool LocalServer::listen()
{
   return qLocalServer_.listen(serverName_);
}

unique_ptr<ILocalSocket> LocalServer::nextPendingConnection()
{
    QLocalSocket* qLocalSocket = qLocalServer_.nextPendingConnection();
    unique_ptr<ILocalSocket> localSocket = localSocketFactory_.create();
    localSocket->setQLocalSocket(qLocalSocket);
    return localSocket;
}
