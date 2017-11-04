#pragma once

#include <MellowPlayer/Infrastructure/Hotkeys/IHotkeys.hpp>
#include <QObject>

class QxtGlobalShortcut;

namespace MellowPlayer::Domain
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

    class Hotkeys : public QObject, public IHotkeys
    {
        Q_OBJECT
    public:
        Hotkeys(Domain::IPlayer& player, Domain::Settings& settings, Domain::IMainWindow& mainWindow);
        ~Hotkeys();

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

        Domain::ILogger& logger_;
        Domain::IPlayer& player_;
        Domain::IMainWindow& mainWindow_;

        QxtGlobalShortcut* playShortcut_;
        QxtGlobalShortcut* nextShortcut_;
        QxtGlobalShortcut* previousShortcut_;
        QxtGlobalShortcut* favoriteShortcut_;
        QxtGlobalShortcut* restoreWindowShortcut_;

        Domain::Setting& playShortcutSetting_;
        Domain::Setting& nextShortcutSetting_;
        Domain::Setting& previousShortcutSetting_;
        Domain::Setting& favoriteShortcutSetting_;
        Domain::Setting& restoreWindowShortcutSetting_;
    };
}
