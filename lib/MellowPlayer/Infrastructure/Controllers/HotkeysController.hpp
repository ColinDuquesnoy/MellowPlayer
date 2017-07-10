#pragma once

#include <QObject>
#include <MellowPlayer/Application/Controllers/IHotkeysController.hpp>

class QxtGlobalShortcut;

namespace MellowPlayer::Application {

    class IPlayer;
    class ILogger;
    class Setting;
    class Settings;

}

namespace MellowPlayer::Infrastructure {

    class HotkeysController: public QObject, public Application::IHotkeysController {
        Q_OBJECT
    public:
        HotkeysController(Application::IPlayer& player, Application::Settings& settings);
        ~HotkeysController();

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

}
