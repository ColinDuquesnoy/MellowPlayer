#pragma once

#include <MellowPlayer/Macros.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

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
        APPEARANCE_THEME,
        GENERAL_CHECK_FOR_UPDATES,
        GENERAL_CLOSE_TO_TRAY,
        GENERAL_CONFIRM_EXIT,
        GENERAL_TRAY_ICON,
        NOTIFICATIONS_ENABLED,
        NOTIFICATIONS_NEW_VERSION,
        NOTIFICATIONS_PAUSE,
        NOTIFICATIONS_PLAY,
        PRIVATE_CURRENT_SERVICE,
        PRIVATE_SHOW_CLOSE_TO_TRAY_MESSAGE,
        SHORTCUTS_NEXT,
        SHORTCUTS_PLAY,
        SHORTCUTS_PREVIOUS
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
        enumToString << "appearance/theme";
        enumToString << "general/check-for-updates";
        enumToString << "general/close-to-tray";
        enumToString << "general/confirm-exit";
        enumToString << "general/tray-icon";
        enumToString << "notifications/enabled";
        enumToString << "notifications/new-version";
        enumToString << "notifications/pause";
        enumToString << "notifications/play";
        enumToString << "private/current-service";
        enumToString << "private/show-close-to-tray-message";
        enumToString << "shortcuts/next";
        enumToString << "shortcuts/play";
        enumToString << "shortcuts/previous";

        return enumToString[static_cast<int>(key)];
    }
};

END_MELLOWPLAYER_NAMESPACE