#include "catch.hpp"
#include <MellowPlayer/UseCases/Settings/Settings.hpp>
#include <MellowPlayer/UseCases/Settings/SettingsCategory.hpp>
#include <MellowPlayer/UseCases/Settings/Setting.hpp>
#include <MellowPlayer/Infrastructure/Settings/SettingsSchemaLoader.hpp>
#include <MellowPlayer/Infrastructure/Settings/QSettingsProvider.hpp>
#include <QtTest/QSignalSpy>

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

#define NB_CONFIGS 6

TEST_CASE("SettingsTests") {
    QSettingsProvider settingsProvider;
    SettingsSchemaLoader loader;
    Settings settings(loader, settingsProvider);
    SettingsCategory* mainCategory = &settings.getCategory("main");

    SECTION("ConfigSchemaTests") {
        SECTION("getCategories") {
            REQUIRE(settings.getCategories().count() >= NB_CONFIGS);
        }
        SECTION("getCategory") {
            REQUIRE(&settings.getCategory("main") == mainCategory);
            REQUIRE_THROWS(settings.getCategory("foo"));
        }

        SECTION("get") {
            REQUIRE_NOTHROW(settings.get(SettingKey::MAIN_CONFIRM_EXIT));
            REQUIRE_THROWS(settings.getCategory("foo"));
        }
    }

    SECTION("ConfigCategoryTests") {
        SECTION("attributes") {
            REQUIRE(mainCategory->getName() == "General");
            REQUIRE(mainCategory->getKey() == "main");
            REQUIRE(!mainCategory->getIcon().isEmpty());
            REQUIRE(mainCategory->getSettings().count() > 1);
        }

        SECTION("get") {
            REQUIRE_NOTHROW(mainCategory->getSetting("confirm-exit"));
            REQUIRE_THROWS(mainCategory->getSetting("foo"));
        }
    }

    SECTION("SettingTests") {
        SECTION("attributes") {
            const Setting& setting = settings.get(SettingKey::MAIN_CONFIRM_EXIT);
            REQUIRE(setting.getKey() == "confirm-exit");
            REQUIRE(setting.getName() == "Confirm application exit");
            REQUIRE(setting.getType() == "bool");
            REQUIRE(setting.getDefaultValue().toBool());

            const Setting& setting2 = settings.get(SettingKey::MAIN_CLOSE_TO_TRAY);
            REQUIRE(setting2.getKey() == "close-to-tray");
            REQUIRE(setting2.getDefaultValue().toBool());
        }

        SECTION("getValue returns default value initially") {
            const Setting& setting = settings.get(SettingKey::MAIN_CONFIRM_EXIT);
            REQUIRE(setting.getValue().toBool());

            const Setting& setting2 = settings.get(SettingKey::MAIN_CLOSE_TO_TRAY);
            REQUIRE(setting2.getValue().toBool());
        }

        SECTION("setValue") {
            Setting& setting = settings.get(SettingKey::MAIN_CONFIRM_EXIT);
            setting.setValue(true);
            REQUIRE(setting.getValue().toBool());
        }

        SECTION("isEnabled always enabled setting") {
            const Setting& setting = settings.get(SettingKey::MAIN_CONFIRM_EXIT);
            REQUIRE(setting.isEnabled());
        }

        SECTION("isEnabled setting enabled if enableCondition is true") {
            Setting& notificationsEnabled = settings.get(SettingKey::NOTIFICATIONS_ENABLED);
            Setting& playNotificationEnabled = settings.get(SettingKey::NOTIFICATIONS_PLAY);
            QSignalSpy spy(&playNotificationEnabled, SIGNAL(isEnabledChanged()));
            REQUIRE(notificationsEnabled.getValue().toBool());
            REQUIRE(playNotificationEnabled.isEnabled());

            notificationsEnabled.setValue(false);
            REQUIRE(spy.count() == 1);
            REQUIRE(!playNotificationEnabled.isEnabled());
        }
    }
}
