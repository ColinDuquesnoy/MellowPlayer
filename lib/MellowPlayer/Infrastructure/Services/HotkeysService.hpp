#pragma once

#include <QObject>
#include <MellowPlayer/Macros.hpp>
#include <MellowPlayer/UseCases/Services/IHotkeysService.hpp>

class QxtGlobalShortcut;
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, IPlayer)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, ILogger)

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class HotkeysService: public QObject, public UseCases::IHotkeysService {
    Q_OBJECT
public:
    HotkeysService(UseCases::IPlayer& player);
    ~HotkeysService();

    void start() override;

public slots:
    void togglePlayPause() override;
    void next() override;
    void previous() override;
    void toggleFavoriteSong() override;

private:
    UseCases::ILogger& logger;
    UseCases::IPlayer& player;
    QxtGlobalShortcut* playShortcut;
    QxtGlobalShortcut* nextShortcut;
    QxtGlobalShortcut* previousShortcut;
    QxtGlobalShortcut* favoriteShortcut;
};

END_MELLOWPLAYER_NAMESPACE
