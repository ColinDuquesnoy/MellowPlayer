#pragma once

#include <MellowPlayer/Infrastructure/Network/LocalServer.hpp>
#include "FakeLocalSocket.hpp"

namespace MellowPlayer::Infrastructure::Tests
{
    class FakeLocalServer: public ILocalServer
    {
    public:
        virtual ~FakeLocalServer()
        {
            close();
        }

        void close() override
        {
            closed = true;
        }

        bool listen() override
        {
            isListening = true;
            return true;
        }

        std::unique_ptr<ILocalSocket> nextPendingConnection() override
        {
            auto socket = std::make_unique<FakeLocalSocket>();
            newConnectionSocket = socket.get();
            return std::move(socket);
        }

        bool closed = false;
        bool isListening = false;
        FakeLocalSocket* newConnectionSocket;
    };

    class FakeLocalServerFactory: public IFactory<ILocalServer, QString>
    {
    public:
        std::unique_ptr<ILocalServer> create(QString&&) override
        {
            auto localServer = std::make_unique<FakeLocalServer>();
            lastServerCreated = localServer.get();
            return std::move(localServer);
        }

        FakeLocalServer* lastServerCreated;
    };
}
