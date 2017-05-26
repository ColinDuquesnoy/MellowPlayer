#pragma once

#include <QObject>
#include <MellowPlayer/Macros.hpp>
#include <MellowPlayer/UseCases/Interfaces/IHotkeysService.hpp>

class QxtGlobalShortcut;
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, IPlayer)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, ILogger)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, Setting)
PREDECLARE_MELLOWPLAYER_CLASS(UseCases, Settings)

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class HotkeysService: public QObject, public UseCases::IHotkeysService {
    Q_OBJECT
public:
    HotkeysService(UseCases::IPlayer& player, UseCases::Settings& settings);
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

    UseCases::Setting& playShortcutSetting;
    UseCases::Setting& nextShortcutSetting;
    UseCases::Setting& previousShortcutSetting;
    UseCases::Setting& favoriteShortcutSetting;

    void updateFavoriteShortcut() const;

    void updatePreviousShorcut() const;

    void updateNextShortcut() const;

    void updatePlayShortcut() const;
};

END_MELLOWPLAYER_NAMESPACE
