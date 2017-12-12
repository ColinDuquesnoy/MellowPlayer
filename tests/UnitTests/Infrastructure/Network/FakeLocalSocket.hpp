#pragma once

#include <MellowPlayer/Infrastructure/Network/LocalSocket.hpp>
#include <boost-di-extensions/Factory.hpp>

namespace MellowPlayer::Infrastructure::Tests
{
    class FakeLocalSocket: public ILocalSocket
    {
    public:
        virtual ~FakeLocalSocket()
        {
            disconnectFromServer();
        }

        void connectToServer(const QString& name, QIODevice::OpenMode) override
        {
            serverName = name;
            isConnected = true;
        }

        void disconnectFromServer() override
        {
            isDisconnected = true;
        }

        void write(const QString& data) override
        {
            writtenData += data;
        }

        QString readAll() override
        {
            return data;
        }

        QString writtenData;
        QLocalSocket* qLocalSocket = nullptr;
        bool isConnected = false;
        bool isDisconnected = false;
        QString serverName;
        QString data;

    protected:
        void setQLocalSocket(QLocalSocket* localSocket) override
        {
            qLocalSocket = localSocket;
        }
    };

    class FakeLocalSocketFactory: public IFactory<ILocalSocket>
    {
    public:
        std::unique_ptr<ILocalSocket> create() const override
        {
            auto socket = std::make_unique<FakeLocalSocket>();

            auto nonConstThis = const_cast<FakeLocalSocketFactory*>(this);
            nonConstThis->lastSocketCreated = socket.get();

            return std::move(socket);
        }

        FakeLocalSocket* lastSocketCreated;
    };
}
