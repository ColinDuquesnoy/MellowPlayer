#pragma once

#include <MellowPlayer/Macros.hpp>
#include <MellowPlayer/Application/Controllers/IMprisController.hpp>
#include <memory>

#ifdef Q_OS_LINUX

class QQuickWindow;
PREDECLARE_MELLOWPLAYER_CLASS(Application, IPlayer)
PREDECLARE_MELLOWPLAYER_CLASS(Application, ILocalAlbumArt)
PREDECLARE_MELLOWPLAYER_CLASS(Application, IMainWindow)
PREDECLARE_MELLOWPLAYER_CLASS(Application, IQtApplication)
PREDECLARE_MELLOWPLAYER_CLASS(Application, ILogger)

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class Mpris2Root;
class Mpris2Player;

class MprisController: public Application::IMprisController {
public:
    MprisController(Application::IPlayer& player,
                    Application::ILocalAlbumArt& localAlbumArt,
                    Application::IMainWindow& window,
                    Application::IQtApplication& application);
    ~MprisController();

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
