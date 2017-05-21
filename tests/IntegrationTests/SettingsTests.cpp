#include "catch.hpp"
#include <MellowPlayer/UseCases/Settings/ApplicationSettings.hpp>
#include <MellowPlayer/UseCases/Settings/SettingsCategory.hpp>
#include <MellowPlayer/UseCases/Settings/Setting.hpp>
#include <MellowPlayer/Infrastructure/Configuration/SettingsSchemaLoader.hpp>
#include <MellowPlayer/Infrastructure/Configuration/QSettingsProvider.hpp>
#include <QtTest/QSignalSpy>

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

#define NB_CONFIGS 4

TEST_CASE("SettingsTests") {
    QSettingsProvider settingsProvider;
    SettingsSchemaLoader loader;
    ApplicationSettings settings(loader, settingsProvider);

    SettingsCategory* generalCategory = settings.getCategories()[0];

    SECTION("ConfigSchemaTests") {
        SECTION("getCategories") {
            REQUIRE(settings.getCategories().count() == NB_CONFIGS);
        }
        SECTION("getCategory") {
            REQUIRE(&settings.getCategory("general") == generalCategory);
            REQUIRE_THROWS(settings.getCategory("foo"));
        }

        SECTION("getSetting") {
            REQUIRE_NOTHROW(settings.getSetting("general/confirm-exit"));
            REQUIRE_THROWS(settings.getCategory("foo"));
        }
    }

    SECTION("ConfigCategoryTests") {
        SECTION("attributes") {
            REQUIRE(generalCategory->getName() == "General");
            REQUIRE(generalCategory->getKey() == "general");
            REQUIRE(generalCategory->getIcon() == "");
            REQUIRE(generalCategory->getSettings().count() > 1);
        }

        SECTION("getSetting") {
            REQUIRE_NOTHROW(generalCategory->getSetting("confirm-exit"));
            REQUIRE_THROWS(generalCategory->getSetting("foo"));
        }
    }

    SECTION("SettingTests") {
        SECTION("attributes") {
            const Setting& setting = settings.getSetting("general/confirm-exit");
            REQUIRE(setting.getKey() == "confirm-exit");
            REQUIRE(setting.getName() == "Confirm application exit");
            REQUIRE(setting.getType() == "bool");
            REQUIRE(!setting.getDefaultValue().toBool());

            const Setting& setting2 = settings.getSetting("general/close-to-tray");
            REQUIRE(setting2.getKey() == "close-to-tray");
            REQUIRE(setting2.getDefaultValue().toBool());
        }

        SECTION("getValue returns default value initially") {
            const Setting& setting = settings.getSetting("general/confirm-exit");
            REQUIRE(!setting.getValue().toBool());

            const Setting& setting2 = settings.getSetting("general/close-to-tray");
            REQUIRE(setting2.getValue().toBool());
        }

        SECTION("setValue") {
            Setting& setting = settings.getSetting("general/confirm-exit");
            setting.setValue(true);
            REQUIRE(setting.getValue().toBool());
        }

        SECTION("isEnabled always enabled setting") {
            const Setting& setting = settings.getSetting("general/confirm-exit");
            REQUIRE(setting.isEnabled());
        }

        SECTION("isEnabled setting enabled if enableCondition is true") {
            Setting& notificationsEnabled = settings.getSetting("notifications/enabled");
            Setting& playNotificationEnabled = settings.getSetting("notifications/play");
            QSignalSpy spy(&playNotificationEnabled, SIGNAL(isEnabledChanged()));
            REQUIRE(notificationsEnabled.getValue().toBool());
            REQUIRE(playNotificationEnabled.isEnabled());

            notificationsEnabled.setValue(false);
            REQUIRE(spy.count() == 1);
            REQUIRE(!playNotificationEnabled.isEnabled());
        }

        SECTION("isEnabled setting enabled if enableCondition is not true") {
            Setting& adaptiveTheme = settings.getSetting("appearance/adaptive-theme");
            Setting& accent = settings.getSetting("appearance/accent");
            QSignalSpy spy(&accent, SIGNAL(isEnabledChanged()));
            REQUIRE(adaptiveTheme.getValue().toBool());
            REQUIRE(!accent.isEnabled());

            adaptiveTheme.setValue(false);
            REQUIRE(spy.count() == 1);
            REQUIRE(accent.isEnabled());
        }
    }
}
