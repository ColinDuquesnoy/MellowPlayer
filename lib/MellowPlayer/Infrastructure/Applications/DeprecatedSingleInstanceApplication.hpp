#pragma once

#include <QLocalServer>
#include <QLocalSocket>
#include <QObject>

namespace MellowPlayer::Domain
{
    class ILogger;
    class ICommandLineParser;
    class IPlayer;
}

namespace MellowPlayer::Infrastructure
{
    class IDeprecatedApplication;

    class DeprecatedSingleInstanceApplication : public QObject
    {
        Q_OBJECT
    public:
        DeprecatedSingleInstanceApplication(IDeprecatedApplication& application,
                                  Domain::ICommandLineParser& commandLineParser,
                                  Domain::IPlayer& currentPlayer);

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

        Domain::ILogger& logger_;
        IDeprecatedApplication& application_;
        Domain::ICommandLineParser& commandLineParser_;
        Domain::IPlayer& currentPlayer_;
        QLocalSocket localSocket_;
        QLocalServer localServer_;

        static const QString playPauseAction_;
        static const QString nextAction_;
        static const QString previousAction_;
        static const QString restoreWindowAction_;
        static const QString toggleFavoriteAction_;
    };
}
