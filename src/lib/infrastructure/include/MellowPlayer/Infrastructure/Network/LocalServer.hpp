#pragma once

#include <QtCore/QObject>
#include <memory>
#include <QtNetwork/QLocalServer>
#include <boost-di-extensions/Factory.hpp>

namespace MellowPlayer::Infrastructure
{
    class ILocalSocket;

    class ILocalServer: public QObject
    {
        Q_OBJECT
    public:
        virtual void close() = 0;
        virtual bool listen() = 0;
        virtual bool isListening() const = 0;
        virtual std::unique_ptr<ILocalSocket> nextPendingConnection() = 0;
        virtual QString serverSocketFilePath() const = 0;

    signals:
        void newConnection();
    };

    class LocalServer: public ILocalServer
    {
    public:
        LocalServer(IFactory<ILocalSocket>& localSocketFactory, const QString& serverName);

        void close() override;
        bool listen() override;
        bool isListening() const override;
        std::unique_ptr<ILocalSocket> nextPendingConnection() override;
        QString serverSocketFilePath() const override;

    private:
        IFactory<ILocalSocket>& localSocketFactory_;
        QString serverName_;
        QLocalServer qLocalServer_;
    };
}
