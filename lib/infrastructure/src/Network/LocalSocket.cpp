#include <MellowPlayer/Infrastructure/Network/LocalSocket.hpp>

using namespace MellowPlayer::Infrastructure;

LocalSocket::LocalSocket(): qLocalSocket_(new QLocalSocket(this))
{
    initSignals();
}

void LocalSocket::connectToServer(const QString& name, QIODevice::OpenMode openMode)
{
    qLocalSocket_->connectToServer(name, openMode);
}

void LocalSocket::disconnectFromServer()
{
    qLocalSocket_->disconnectFromServer();
}

void LocalSocket::write(const QString& data)
{
    if (qLocalSocket_->state() == QLocalSocket::ConnectedState)
    {
        qLocalSocket_->write(data.toLocal8Bit());
        qLocalSocket_->waitForBytesWritten();
    }
    else
        throw std::logic_error("cannot write data on a socket that is not connected");
}

void LocalSocket::setQLocalSocket(QLocalSocket* localSocket)
{
    delete qLocalSocket_;
    qLocalSocket_ = localSocket;
    initSignals();
}

QString LocalSocket::readAll()
{
    return qLocalSocket_->readAll();
}

void LocalSocket::initSignals() {
    connect(qLocalSocket_, &QLocalSocket::connected, this, &LocalSocket::connected);
    connect(qLocalSocket_, &QLocalSocket::disconnected, this, &LocalSocket::disconnected);
    connect(qLocalSocket_, &QLocalSocket::readyRead, this, &LocalSocket::readyRead);
    connect(qLocalSocket_, QNonConstOverload<QLocalSocket::LocalSocketError>::of(&QLocalSocket::error),
            [=](QLocalSocket::LocalSocketError) { emit error(); });
}
