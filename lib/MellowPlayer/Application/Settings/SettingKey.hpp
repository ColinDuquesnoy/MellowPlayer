#pragma once

#include <QObject>

namespace MellowPlayer::Application
{
    class SettingKey : public QObject
    {
        Q_OBJECT
    public:
        enum Keys
        {
            APPEARANCE_ACCENT,
            APPEARANCE_BACKGROUND,
            APPEARANCE_FOREGROUND,
            APPEARANCE_PRIMARY_BACKGROUND,
            APPEARANCE_PRIMARY_FOREGROUND,
            APPEARANCE_SECONDARY_BACKGROUND,
            APPEARANCE_SECONDARY_FOREGROUND,
            APPEARANCE_THEME,
            MAIN_CHECK_FOR_UPDATES,
            MAIN_CLOSE_TO_TRAY,
            MAIN_CONFIRM_EXIT,
            MAIN_SHOW_TRAY_ICON,
            MAIN_UPDATE_CHANNEL,
            NOTIFICATIONS_ENABLED,
            NOTIFICATIONS_NEW_SONG,
            NOTIFICATIONS_PAUSED,
            NOTIFICATIONS_RESUMED,
            PRIVACY_ENABLE_LISTENING_HISTORY,
            PRIVACY_LISTENING_HISTORY_LIMIT,
            PRIVACY_USER_AGENT,
            PRIVATE_CURRENT_SERVICE,
            PRIVATE_SHOW_CLOSE_TO_TRAY_MESSAGE,
            PRIVATE_WINDOW_HEIGHT,
            PRIVATE_WINDOW_WIDTH,
            SHORTCUTS_ABOUT,
            SHORTCUTS_CHECK_FOR_UPDATE,
            SHORTCUTS_CREATE_PLUGIN,
            SHORTCUTS_FAVORITE,
            SHORTCUTS_LISTENING_HISTORY,
            SHORTCUTS_NEXT,
            SHORTCUTS_NOTIFICATIONS,
            SHORTCUTS_PLAY,
            SHORTCUTS_PREVIOUS,
            SHORTCUTS_QUIT,
            SHORTCUTS_RELOAD,
            SHORTCUTS_REPORT_ISSUE,
            SHORTCUTS_RESTORE_WINDOW,
            SHORTCUTS_SELECT_NEXT_SERVICE,
            SHORTCUTS_SELECT_PREVIOUS_SERVICE,
            SHORTCUTS_SELECT_SERVICE,
            SHORTCUTS_SETTINGS
        };
        Q_ENUM(Keys);

        static QString toString(SettingKey::Keys key)
        {
            QStringList enumToString;

            enumToString << "appearance/accent";
            enumToString << "appearance/background";
            enumToString << "appearance/foreground";
            enumToString << "appearance/primary-background";
            enumToString << "appearance/primary-foreground";
            enumToString << "appearance/secondary-background";
            enumToString << "appearance/secondary-foreground";
            enumToString << "appearance/theme";
            enumToString << "main/check-for-updates";
            enumToString << "main/close-to-tray";
            enumToString << "main/confirm-exit";
            enumToString << "main/show-tray-icon";
            enumToString << "main/update-channel";
            enumToString << "notifications/enabled";
            enumToString << "notifications/new-song";
            enumToString << "notifications/paused";
            enumToString << "notifications/resumed";
            enumToString << "privacy/enable-listening-history";
            enumToString << "privacy/listening-history-limit";
            enumToString << "privacy/user-agent";
            enumToString << "private/current-service";
            enumToString << "private/show-close-to-tray-message";
            enumToString << "private/window-height";
            enumToString << "private/window-width";
            enumToString << "shortcuts/about";
            enumToString << "shortcuts/check-for-update";
            enumToString << "shortcuts/create-plugin";
            enumToString << "shortcuts/favorite";
            enumToString << "shortcuts/listening-history";
            enumToString << "shortcuts/next";
            enumToString << "shortcuts/notifications";
            enumToString << "shortcuts/play";
            enumToString << "shortcuts/previous";
            enumToString << "shortcuts/quit";
            enumToString << "shortcuts/reload";
            enumToString << "shortcuts/report-issue";
            enumToString << "shortcuts/restore-window";
            enumToString << "shortcuts/select-next-service";
            enumToString << "shortcuts/select-previous-service";
            enumToString << "shortcuts/select-service";
            enumToString << "shortcuts/settings";

            return enumToString[static_cast<int>(key)];
        }
    };
}