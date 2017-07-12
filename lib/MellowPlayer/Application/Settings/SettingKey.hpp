#pragma once

#include <QObject>

namespace MellowPlayer::Application {

    class SettingKey: public QObject {
        Q_OBJECT
    public:
        enum Keys {
            APPEARANCE_ACCENT,
            APPEARANCE_ADAPTIVE_THEME,
            APPEARANCE_BACKGROUND,
            APPEARANCE_FOREGROUND,
            APPEARANCE_PRIMARY_BACKGROUND,
            APPEARANCE_PRIMARY_FOREGROUND,
            APPEARANCE_SECONDARY_BACKGROUND,
            APPEARANCE_SECONDARY_FOREGROUND,
            MAIN_CLOSE_TO_TRAY,
            MAIN_CONFIRM_EXIT,
            MAIN_SHOW_TRAY_ICON,
            NOTIFICATIONS_ENABLED,
            NOTIFICATIONS_NEW_SONG,
            NOTIFICATIONS_NEW_VERSION,
            NOTIFICATIONS_PAUSED,
            NOTIFICATIONS_RESUMED,
            PRIVACY_CHECK_FOR_UPDATES,
            PRIVACY_ENABLE_LISTENING_HISTORY,
            PRIVACY_LISTENING_HISTORY_LIMIT,
            PRIVATE_CURRENT_SERVICE,
            PRIVATE_SHOW_CLOSE_TO_TRAY_MESSAGE,
            SHORTCUTS_ABOUT,
            SHORTCUTS_FAVORITE,
            SHORTCUTS_LISTENING_HISTORY,
            SHORTCUTS_NEXT,
            SHORTCUTS_NOTIFICATIONS,
            SHORTCUTS_PLAY,
            SHORTCUTS_PREVIOUS,
            SHORTCUTS_QUIT,
            SHORTCUTS_RELOAD,
            SHORTCUTS_RESTORE_WINDOW,
            SHORTCUTS_SELECT_NEXT_SERVICE,
            SHORTCUTS_SELECT_PREVIOUS_SERVICE,
            SHORTCUTS_SELECT_SERVICE,
            SHORTCUTS_SETTINGS
        };
        Q_ENUM(Keys);

        static QString toString(SettingKey::Keys key) {
            QStringList enumToString;

            enumToString << "appearance/accent";
            enumToString << "appearance/adaptive-theme";
            enumToString << "appearance/background";
            enumToString << "appearance/foreground";
            enumToString << "appearance/primary-background";
            enumToString << "appearance/primary-foreground";
            enumToString << "appearance/secondary-background";
            enumToString << "appearance/secondary-foreground";
            enumToString << "main/close-to-tray";
            enumToString << "main/confirm-exit";
            enumToString << "main/show-tray-icon";
            enumToString << "notifications/enabled";
            enumToString << "notifications/new-song";
            enumToString << "notifications/new-version";
            enumToString << "notifications/paused";
            enumToString << "notifications/resumed";
            enumToString << "privacy/check-for-updates";
            enumToString << "privacy/enable-listening-history";
            enumToString << "privacy/listening-history-limit";
            enumToString << "private/current-service";
            enumToString << "private/show-close-to-tray-message";
            enumToString << "shortcuts/about";
            enumToString << "shortcuts/favorite";
            enumToString << "shortcuts/listening-history";
            enumToString << "shortcuts/next";
            enumToString << "shortcuts/notifications";
            enumToString << "shortcuts/play";
            enumToString << "shortcuts/previous";
            enumToString << "shortcuts/quit";
            enumToString << "shortcuts/reload";
            enumToString << "shortcuts/restore-window";
            enumToString << "shortcuts/select-next-service";
            enumToString << "shortcuts/select-previous-service";
            enumToString << "shortcuts/select-service";
            enumToString << "shortcuts/settings";

            return enumToString[static_cast<int>(key)];
        }
    };

}