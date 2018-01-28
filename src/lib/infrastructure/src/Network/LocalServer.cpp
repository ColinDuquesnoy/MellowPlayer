#include <MellowPlayer/Infrastructure/Network/LocalServer.hpp>
#include <MellowPlayer/Infrastructure/Network/LocalSocket.hpp>

using namespace std;
using namespace MellowPlayer::Infrastructure;

LocalServer::LocalServer(IFactory<ILocalSocket>& localSocketFactory, const QString& serverName)
        : localSocketFactory_(localSocketFactory), serverName_(serverName)
{
    QLocalServer::removeServer(serverName);
    connect(&qLocalServer_, &QLocalServer::newConnection, this, &ILocalServer::newConnection);
}

void LocalServer::close()
{
    qLocalServer_.close();
}

bool LocalServer::listen()
{
   return qLocalServer_.listen(serverName_);
}

bool LocalServer::isListening() const
{
    return qLocalServer_.isListening();
}

unique_ptr<ILocalSocket> LocalServer::nextPendingConnection()
{
    QLocalSocket* qLocalSocket = qLocalServer_.nextPendingConnection();
    unique_ptr<ILocalSocket> localSocket = localSocketFactory_.create();
    localSocket->setQLocalSocket(qLocalSocket);
    return localSocket;
}

QString LocalServer::serverSocketFilePath() const
{
    return qLocalServer_.fullServerName();
}
