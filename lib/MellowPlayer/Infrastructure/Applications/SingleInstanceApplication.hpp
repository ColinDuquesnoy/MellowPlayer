#pragma once

#include <QObject>
#include <QLocalSocket>
#include <QLocalServer>
#include "IApplication.hpp"

namespace MellowPlayer::Application {

    class ILogger;
    class ICommandLineParser;
    class IPlayer;

}

namespace MellowPlayer::Infrastructure {

    class SingleInstanceApplication : public QObject {
        Q_OBJECT
    public:
        SingleInstanceApplication(IApplication& application, Application::ICommandLineParser& commandLineParser,
                                  Application::IPlayer& currentPlayer);

        int run();

    private slots:
        void onSocketConnected();
        void onSocketError();
        void onNewConnection();
        void connectSignalHandlers();
        void quit();
        void onReadyRead();

    private:
        QString getRequestedAcion() const;

        Application::ILogger& logger;
        IApplication& application;
        Application::ICommandLineParser& commandLineParser;
        Application::IPlayer& currentPlayer;
        QLocalSocket localSocket;
        QLocalServer localServer;

        static const QString playPauseAction;
        static const QString nextAction;
        static const QString previousAction;
        static const QString restoreWindowAction;
    };

}
