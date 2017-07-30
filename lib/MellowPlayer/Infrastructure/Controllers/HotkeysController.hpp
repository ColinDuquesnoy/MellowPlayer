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
        HotkeysController(Application::IPlayer& player, Application::Settings& settings, Application::IMainWindow& mainWindow);
        ~HotkeysController();

        void start() override;

    public slots:
        void togglePlayPause() override;
        void next() override;
        void previous() override;
        void toggleFavoriteSong() override;
        void restoreWindow() override;

    private:
        void updateFavoriteShortcut() const;
        void updatePreviousShorcut() const;
        void updateNextShortcut() const;
        void updatePlayShortcut() const;
        void updateRestoreWindowShortcut() const;

        Application::ILogger& logger_;
        Application::IPlayer& player_;
        Application::IMainWindow& mainWindow_;

        QxtGlobalShortcut* playShortcut_;
        QxtGlobalShortcut* nextShortcut_;
        QxtGlobalShortcut* previousShortcut_;
        QxtGlobalShortcut* favoriteShortcut_;
        QxtGlobalShortcut* restoreWindowShortcut_;

        Application::Setting& playShortcutSetting_;
        Application::Setting& nextShortcutSetting_;
        Application::Setting& previousShortcutSetting_;
        Application::Setting& favoriteShortcutSetting_;
        Application::Setting& restoreWindowShortcutSetting_;
    };
}
