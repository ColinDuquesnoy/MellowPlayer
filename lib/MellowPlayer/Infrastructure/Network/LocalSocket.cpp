#include "LocalSocket.hpp"

using namespace MellowPlayer::Infrastructure;

LocalSocket::LocalSocket(): qLocalSocket_(new QLocalSocket(this))
{
    connect(qLocalSocket_, &QLocalSocket::connected, this, &ILocalSocket::connected);
    connect(qLocalSocket_, &QLocalSocket::readyRead, this, &ILocalSocket::readyRead);
    connect(qLocalSocket_, SIGNAL(error(QLocalSocket::LocalSocketError)), this, SLOT(error()));
}

LocalSocket::~LocalSocket()
{
    disconnectFromServer();
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
    connect(qLocalSocket_, &QLocalSocket::connected, this, &ILocalSocket::connected);
    connect(qLocalSocket_, &QLocalSocket::readyRead, this, &ILocalSocket::readyRead);
    connect(qLocalSocket_, SIGNAL(error(QLocalSocket::LocalSocketError)), this, SLOT(error()));
}

QString LocalSocket::readAll()
{
    return qLocalSocket_->readAll();
}
