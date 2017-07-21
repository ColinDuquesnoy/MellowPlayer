#pragma once

#include <MellowPlayer/Application/Controllers/IHotkeysController.hpp>
#include <QObject>

class QxtGlobalShortcut;

namespace MellowPlayer::Application
{
    class IPlayer;
    class ILogger;
    class Setting;
    class Settings;
    class IMainWindow;
}

namespace MellowPlayer::Infrastructure
{
    class IApplication;

    class HotkeysController : public QObject, public Application::IHotkeysController
    {
        Q_OBJECT
    public:
        HotkeysController(Application::IPlayer &player, Application::Settings &settings,
                          Application::IMainWindow &mainWindow);
        ~HotkeysController();

        void start() override;

    public slots:
        void togglePlayPause() override;
        void next() override;
        void previous() override;
        void toggleFavoriteSong() override;
        void restoreWindow() override;

    private:
        Application::ILogger &logger;
        Application::IPlayer &player;
        Application::IMainWindow &mainWindow;
        QxtGlobalShortcut *playShortcut;
        QxtGlobalShortcut *nextShortcut;
        QxtGlobalShortcut *previousShortcut;
        QxtGlobalShortcut *favoriteShortcut;
        QxtGlobalShortcut *restoreWindowShortcut;

        Application::Setting &playShortcutSetting;
        Application::Setting &nextShortcutSetting;
        Application::Setting &previousShortcutSetting;
        Application::Setting &favoriteShortcutSetting;
        Application::Setting &restoreWindowShortcutSetting;

        void updateFavoriteShortcut() const;
        void updatePreviousShorcut() const;
        void updateNextShortcut() const;
        void updatePlayShortcut() const;
        void updateRestoreWindowShortcut() const;
    };
}
