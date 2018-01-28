#pragma once

#include "ApplicationDecorator.hpp"
#include <QtCore/QLockFile>
#include <boost-di-extensions/Factory.hpp>
#include <QTimer>

namespace MellowPlayer::Domain
{
    class ILogger;
    class IPlayer;
}

namespace MellowPlayer::Infrastructure
{
    class IQtApplication;
    class ILocalServer;
    class ILocalSocket;
    class ICommandLineArguments;

    class SingleInstance: public ApplicationDecorator
    {
        Q_OBJECT
    public:
        SingleInstance(const std::shared_ptr<IApplication>& application,
                       IQtApplication& qtApplication,
                       Domain::IPlayer& currentPlayer,
                       ICommandLineArguments& commandLineArguments,
                       IFactory<ILocalServer, QString>& localServer,
                       IFactory<ILocalSocket>& localSocket);
        ~SingleInstance();

        void initialize() override final;
        int run() override final;

        bool isPrimary() const;

        static bool checkForPrimary();

    private slots:
        void pollState();

    private:
        int runPrimaryApplication();
        void onSecondaryApplicationConnected();
        void onSecondaryApplicationActionRequest();

        int runSecondaryApplication();
        void onConnectedToPrimaryApplication();
        void onConnectionErrorWithPrimaryApplication();
        QString requestedAcion() const;

        Domain::ILogger& logger_;
        IQtApplication& qtApplication_;
        Domain::IPlayer& currentPlayer_;
        ICommandLineArguments& commandLineArguments_;
        IFactory<ILocalServer, QString>& localServerFactory_;
        IFactory<ILocalSocket>& localSocketFactory_;
        std::unique_ptr<ILocalServer> localServer_;
        std::unique_ptr<ILocalSocket> localSocket_;
        QString lockFilePath_;
        QLockFile lockFile_;
        bool isPrimary_;
        QTimer pollStateTimer_;

        static const QString playPauseAction_;
        static const QString nextAction_;
        static const QString previousAction_;
        static const QString restoreWindowAction_;
        static const QString toggleFavoriteAction_;
    };
}
