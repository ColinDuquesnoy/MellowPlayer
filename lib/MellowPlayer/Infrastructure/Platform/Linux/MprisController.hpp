#pragma once

#include <MellowPlayer/Domain/Controllers/IMprisController.hpp>
#include <memory>

#ifdef Q_OS_LINUX

namespace MellowPlayer::Domain
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

    class MprisController : public Domain::IMprisController
    {
    public:
        MprisController(Domain::IPlayer& player, Domain::ILocalAlbumArt& localAlbumArt, Domain::IMainWindow& window,
                        Domain::IQtApplication& application);
        ~MprisController();

        bool start() override;

    private:
        static QString SERVICE_NAME;
        static QString OBJECT_NAME;

        Domain::ILogger& logger_;
        std::unique_ptr<QObject> parent_;
        QObject* mpris2Root_;
        QObject* mpris2Player_;
        QString serviceName_;
    };
}

#endif
