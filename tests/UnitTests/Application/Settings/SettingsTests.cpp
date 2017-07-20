#include "catch.hpp"
#include <MellowPlayer/Application/Settings/Settings.hpp>
#include <MellowPlayer/Application/Settings/SettingsCategory.hpp>
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <QtTest/QSignalSpy>
#include <Utils/DependencyPool.hpp>

using namespace std;
using namespace MellowPlayer::Application;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Tests;

#define NB_CONFIGS 6

TEST_CASE("SettingsTests") {
    DependencyPool pool;
    Settings& settings = pool.getSettings();
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

        SECTION("restoreDefaults") {
            Setting& setting1 = settings.get(SettingKey::MAIN_SHOW_TRAY_ICON);
            setting1.setValue(!setting1.getDefaultValue().toBool());
            Setting& setting2 = settings.get(SettingKey::APPEARANCE_THEME);
            setting2.setValue("Other");
            REQUIRE(setting1.getValue() != setting1.getDefaultValue());
            REQUIRE(setting2.getValue() != setting2.getDefaultValue());

            settings.restoreDefaults();
            REQUIRE(setting1.getValue() == setting1.getDefaultValue());
            REQUIRE(setting2.getValue() == setting2.getDefaultValue());
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

        SECTION("restoreDefaults") {
            Setting& setting1 = settings.get(SettingKey::MAIN_SHOW_TRAY_ICON);
            setting1.setValue(!setting1.getDefaultValue().toBool());
            Setting& setting2 = settings.get(SettingKey::MAIN_CLOSE_TO_TRAY);
            setting2.setValue(!setting1.getDefaultValue().toBool());
            Setting& fromOtherCategory = settings.get(SettingKey::APPEARANCE_THEME);
            fromOtherCategory.setValue("Other");
            REQUIRE(setting1.getValue() != setting1.getDefaultValue());
            REQUIRE(setting2.getValue() != setting2.getDefaultValue());
            REQUIRE(fromOtherCategory.getValue() != fromOtherCategory.getDefaultValue());

            mainCategory->restoreDefaults();
            REQUIRE(setting1.getValue() == setting1.getDefaultValue());
            REQUIRE(setting2.getValue() == setting2.getDefaultValue());
            REQUIRE(fromOtherCategory.getValue() != fromOtherCategory.getDefaultValue());
            fromOtherCategory.restoreDefaults();
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
            REQUIRE(setting.getValue() == setting.getDefaultValue());
            setting.setValue(true);
            REQUIRE(setting.getValue().toBool());
            setting.restoreDefaults();
            REQUIRE(setting.getValue() == setting.getDefaultValue());
        }

        SECTION("isEnabled always enabled setting") {
            const Setting& setting = settings.get(SettingKey::MAIN_CONFIRM_EXIT);
            REQUIRE(setting.isEnabled());
        }

        SECTION("isEnabled setting enabled if enableCondition is true") {
            SECTION("bool condition") {
                Setting &notificationsEnabled = settings.get(SettingKey::NOTIFICATIONS_ENABLED);
                Setting &playNotificationEnabled = settings.get(SettingKey::NOTIFICATIONS_NEW_SONG);
                QSignalSpy spy(&playNotificationEnabled, SIGNAL(isEnabledChanged()));
                REQUIRE(notificationsEnabled.getValue().toBool());
                REQUIRE(playNotificationEnabled.isEnabled());

                notificationsEnabled.setValue(false);
                REQUIRE(spy.count() == 1);
                REQUIRE(!playNotificationEnabled.isEnabled());
            }

            SECTION("string comparison condition") {
                Setting &theme = settings.get(SettingKey::APPEARANCE_THEME);
                Setting &accent = settings.get(SettingKey::APPEARANCE_ACCENT);
                QSignalSpy spy(&accent, SIGNAL(isEnabledChanged()));
                REQUIRE(theme.getValue().toString() == "Adaptive");
                REQUIRE(!accent.isEnabled());

                theme.setValue("Custom");
                REQUIRE(spy.count() == 1);
                REQUIRE(accent.isEnabled());
            }
        }

        SECTION("get invalid setting key throws") {
            REQUIRE_THROWS(settings.get("category/subcategory/key"));
        }
    }
}
