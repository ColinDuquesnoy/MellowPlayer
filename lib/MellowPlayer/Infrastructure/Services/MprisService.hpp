#pragma once

#include <MellowPlayer/Macros.hpp>
#include <MellowPlayer/UseCases.hpp>

#ifdef Q_OS_LINUX

class QQuickWindow;

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class Mpris2Root;
class Mpris2Player;

class MprisService: public UseCases::IMprisService {
public:
    MprisService(UseCases::IPlayer& player, UseCases::LocalAlbumArtService& localAlbumArt, UseCases::IMainWindow& window,
                 UseCases::IQtApplication& application);
    ~MprisService();

    bool start() override;

private:
    static QString SERVICE_NAME;
    static QString OBJECT_NAME;

    Logging::ILogger& logger;
    std::unique_ptr<QObject> parent;
    QObject* mpris2Root;
    QObject* mpris2Player;
};

END_MELLOWPLAYER_NAMESPACE

#endif
