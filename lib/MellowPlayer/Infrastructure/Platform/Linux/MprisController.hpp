#pragma once

#include <MellowPlayer/Application/Controllers/IMprisController.hpp>
#include <memory>

#ifdef Q_OS_LINUX

namespace MellowPlayer::Application
{
    class IPlayer;
    class ILocalAlbumArt;
    class IMainWindow;
    class IQtApplication;
    class ILogger;
}

namespace MellowPlayer::Infrastructure
{
    class Mpris2Root;
    class Mpris2Player;

    class MprisController : public Application::IMprisController
    {
    public:
        MprisController(Application::IPlayer &player, Application::ILocalAlbumArt &localAlbumArt, Application::IMainWindow &window,
                        Application::IQtApplication &application);
        ~MprisController();

        bool start() override;

    private:
        static QString SERVICE_NAME;
        static QString OBJECT_NAME;

        Application::ILogger &logger;
        std::unique_ptr<QObject> parent;
        QObject *mpris2Root;
        QObject *mpris2Player;
        QString serviceName;
    };
}

#endif
