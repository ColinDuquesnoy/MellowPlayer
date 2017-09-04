#pragma once

#include <QLocalServer>
#include <QLocalSocket>
#include <QObject>

namespace MellowPlayer::Application
{
    class ILogger;
    class ICommandLineParser;
    class IPlayer;
}

namespace MellowPlayer::Infrastructure
{
    class IApplication;

    class SingleInstanceApplication : public QObject
    {
        Q_OBJECT
    public:
        SingleInstanceApplication(IApplication& application,
                                  Application::ICommandLineParser& commandLineParser,
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
        QString requestedAcion() const;

        Application::ILogger& logger_;
        IApplication& application_;
        Application::ICommandLineParser& commandLineParser_;
        Application::IPlayer& currentPlayer_;
        QLocalSocket localSocket_;
        QLocalServer localServer_;

        static const QString playPauseAction_;
        static const QString nextAction_;
        static const QString previousAction_;
        static const QString restoreWindowAction_;
        static const QString toggleFavoriteAction_;
    };
}
