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
            isListening_ = true;
            return true;
        }

        bool isListening() const override
        {
            return isListening_;
        }

        QString serverSocketFilePath() const override
        {
            return "";
        }

        std::unique_ptr<ILocalSocket> nextPendingConnection() override
        {
            auto socket = std::make_unique<FakeLocalSocket>();
            newConnectionSocket = socket.get();
            return std::move(socket);
        }

        bool closed = false;
        FakeLocalSocket* newConnectionSocket;

    private:
        bool isListening_ = false;
    };

    class FakeLocalServerFactory: public IFactory<ILocalServer, QString>
    {
    public:
        std::unique_ptr<ILocalServer> create(QString&&) const override
        {
            auto localServer = std::make_unique<FakeLocalServer>();

            auto nonConstThis = const_cast<FakeLocalServerFactory*>(this);
            nonConstThis->lastServerCreated = localServer.get();

            return std::move(localServer);
        }

        FakeLocalServer* lastServerCreated;
    };
}
