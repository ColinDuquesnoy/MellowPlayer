#pragma once

#include <MellowPlayer/Macros.hpp>
#include <MellowPlayer/UseCases/Services/IMprisService.hpp>
#include <memory>

#ifdef Q_OS_LINUX

class QQuickWindow;
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, IPlayer)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, ILocalAlbumArtService)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, IMainWindow)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, IQtApplication)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, ILogger)

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class Mpris2Root;
class Mpris2Player;

class MprisService: public UseCases::IMprisService {
public:
    MprisService(UseCases::IPlayer& player,
                 UseCases::ILocalAlbumArtService& localAlbumArt,
                 UseCases::IMainWindow& window,
                 UseCases::IQtApplication& application);
    ~MprisService();

    bool start() override;

private:
    static QString SERVICE_NAME;
    static QString OBJECT_NAME;

    UseCases::ILogger& logger;
    std::unique_ptr<QObject> parent;
    QObject* mpris2Root;
    QObject* mpris2Player;
};

END_MELLOWPLAYER_NAMESPACE

#endif
