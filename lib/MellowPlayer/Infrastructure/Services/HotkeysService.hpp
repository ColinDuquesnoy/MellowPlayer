#pragma once

#include <QObject>
#include <MellowPlayer/Macros.hpp>
#include <MellowPlayer/Application/Interfaces/IHotkeysService.hpp>

class QxtGlobalShortcut;
PREDECLARE_MELLOWPLAYER_CLASS(Application, IPlayer)
PREDECLARE_MELLOWPLAYER_CLASS(Application, ILogger)
PREDECLARE_MELLOWPLAYER_CLASS(Application, Setting)
PREDECLARE_MELLOWPLAYER_CLASS(Application, Settings)

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class HotkeysService: public QObject, public Application::IHotkeysService {
    Q_OBJECT
public:
    HotkeysService(Application::IPlayer& player, Application::Settings& settings);
    ~HotkeysService();

    void start() override;

public slots:
    void togglePlayPause() override;
    void next() override;
    void previous() override;
    void toggleFavoriteSong() override;

private:
    Application::ILogger& logger;
    Application::IPlayer& player;
    QxtGlobalShortcut* playShortcut;
    QxtGlobalShortcut* nextShortcut;
    QxtGlobalShortcut* previousShortcut;
    QxtGlobalShortcut* favoriteShortcut;

    Application::Setting& playShortcutSetting;
    Application::Setting& nextShortcutSetting;
    Application::Setting& previousShortcutSetting;
    Application::Setting& favoriteShortcutSetting;

    void updateFavoriteShortcut() const;

    void updatePreviousShorcut() const;

    void updateNextShortcut() const;

    void updatePlayShortcut() const;
};

END_MELLOWPLAYER_NAMESPACE
