#pragma once

#include <MellowPlayer/Macros.hpp>
#include <MellowPlayer/Application/Interfaces/IMprisService.hpp>
#include <memory>

#ifdef Q_OS_LINUX

class QQuickWindow;
PREDECLARE_MELLOWPLAYER_CLASS(Application, IPlayer)
PREDECLARE_MELLOWPLAYER_CLASS(Application, ILocalAlbumArtService)
PREDECLARE_MELLOWPLAYER_CLASS(Application, IMainWindow)
PREDECLARE_MELLOWPLAYER_CLASS(Application, IQtApplication)
PREDECLARE_MELLOWPLAYER_CLASS(Application, ILogger)

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class Mpris2Root;
class Mpris2Player;

class MprisService: public Application::IMprisService {
public:
    MprisService(Application::IPlayer& player,
                 Application::ILocalAlbumArtService& localAlbumArt,
                 Application::IMainWindow& window,
                 Application::IQtApplication& application);
    ~MprisService();

    bool start() override;

private:
    static QString SERVICE_NAME;
    static QString OBJECT_NAME;

    Application::ILogger& logger;
    std::unique_ptr<QObject> parent;
    QObject* mpris2Root;
    QObject* mpris2Player;
    QString serviceName;
};

END_MELLOWPLAYER_NAMESPACE

#endif
