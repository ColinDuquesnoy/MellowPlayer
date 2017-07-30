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
        MprisController(Application::IPlayer& player, Application::ILocalAlbumArt& localAlbumArt, Application::IMainWindow& window,
                        Application::IQtApplication& application);
        ~MprisController();

        bool start() override;

    private:
        static QString SERVICE_NAME;
        static QString OBJECT_NAME;

        Application::ILogger& logger_;
        std::unique_ptr<QObject> parent_;
        QObject* mpris2Root_;
        QObject* mpris2Player_;
        QString serviceName_;
    };
}

#endif
