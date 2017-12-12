#pragma once

#include <QtCore/QObject>
#include <QtCore/QIODevice>
#include <QtNetwork/QLocalSocket>

namespace MellowPlayer::Infrastructure
{
    class ILocalSocket: public QObject
    {
        Q_OBJECT
    public:
        virtual void connectToServer(const QString &name, QIODevice::OpenMode openMode = QIODevice::ReadWrite) = 0;
        virtual void disconnectFromServer() = 0;
        virtual void write(const QString& data) = 0;
        virtual QString readAll() = 0;
        virtual void setQLocalSocket(QLocalSocket* localSocket) = 0;

    signals:
        void connected();
        void disconnected();
        void error();
        void readyRead();
    };

    class LocalSocket: public ILocalSocket
    {
        Q_OBJECT;
    public:
        LocalSocket();

        void connectToServer(const QString& name, QIODevice::OpenMode openMode) override;
        void disconnectFromServer() override;
        void write(const QString& data) override;
        QString readAll() override;
        void setQLocalSocket(QLocalSocket* localSocket) override;

    private:
        void initSignals();

        QLocalSocket* qLocalSocket_;
    };
}
