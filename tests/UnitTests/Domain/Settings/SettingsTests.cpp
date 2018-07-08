#include <catch/catch.hpp>
#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Domain/Settings/SettingsCategory.hpp>
#include <QtTest/QSignalSpy>
#include <Utils/DependencyPool.hpp>
#include <QVersionNumber>

using namespace std;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Tests;

#define NB_CONFIGS 6

TEST_CASE("SettingsTests")
{
    DependencyPool pool;
    Settings& settings = pool.getSettings();
    SettingsCategory* mainCategory = &settings.category("main");

    SECTION("ConfigSchemaTests")
    {
        SECTION("categories")
        {
            REQUIRE(settings.categories().count() >= NB_CONFIGS);
        }
        SECTION("category")
        {
            REQUIRE(&settings.category("main") == mainCategory);
            REQUIRE_THROWS(settings.category("foo"));
        }

        SECTION("get")
        {
            REQUIRE_NOTHROW(settings.get(SettingKey::MAIN_CONFIRM_EXIT));
            REQUIRE_THROWS(settings.category("foo"));
        }

        SECTION("restoreDefaults")
        {
            Setting& setting1 = settings.get(SettingKey::MAIN_SHOW_TRAY_ICON);
            setting1.setValue(!setting1.defaultValue().toBool());
            Setting& setting2 = settings.get(SettingKey::APPEARANCE_THEME);
            setting2.setValue("Other");
            REQUIRE(setting1.value() != setting1.defaultValue());
            REQUIRE(setting2.value() != setting2.defaultValue());

            settings.restoreDefaults();
            REQUIRE(setting1.value() == setting1.defaultValue());
            REQUIRE(setting2.value() == setting2.defaultValue());
        }
    }

    SECTION("ConfigCategoryTests")
    {
        SECTION("attributes")
        {
            REQUIRE(mainCategory->name() == "General");
            REQUIRE(mainCategory->key() == "main");
            REQUIRE(!mainCategory->icon().isEmpty());
            REQUIRE(mainCategory->toList().count() > 1);
        }

        SECTION("get")
        {
            REQUIRE_NOTHROW(mainCategory->get("confirm-exit"));
            REQUIRE_THROWS(mainCategory->get("foo"));
        }

        SECTION("restoreDefaults")
        {
            Setting& setting1 = settings.get(SettingKey::MAIN_SHOW_TRAY_ICON);
            setting1.setValue(!setting1.defaultValue().toBool());
            Setting& setting2 = settings.get(SettingKey::MAIN_CLOSE_TO_TRAY);
            setting2.setValue(!setting1.defaultValue().toBool());
            Setting& fromOtherCategory = settings.get(SettingKey::APPEARANCE_THEME);
            fromOtherCategory.setValue("Other");
            REQUIRE(setting1.value() != setting1.defaultValue());
            REQUIRE(setting2.value() != setting2.defaultValue());
            REQUIRE(fromOtherCategory.value() != fromOtherCategory.defaultValue());

            mainCategory->restoreDefaults();
            REQUIRE(setting1.value() == setting1.defaultValue());
            REQUIRE(setting2.value() == setting2.defaultValue());
            REQUIRE(fromOtherCategory.value() != fromOtherCategory.defaultValue());
            fromOtherCategory.restoreDefaults();
        }
    }

    SECTION("SettingTests")
    {
        SECTION("attributes")
        {
            const Setting& setting = settings.get(SettingKey::MAIN_CONFIRM_EXIT);
            REQUIRE(setting.key() == "confirm-exit");
            REQUIRE(setting.name() == "Confirm application exit");
            REQUIRE(setting.type() == "bool");
            REQUIRE(setting.defaultValue().toBool());

            const Setting& setting2 = settings.get(SettingKey::MAIN_CLOSE_TO_TRAY);
            REQUIRE(setting2.key() == "close-to-tray");
            REQUIRE(setting2.defaultValue().toBool());
        }

        SECTION("value returns default value initially")
        {
            const Setting& setting = settings.get(SettingKey::MAIN_CONFIRM_EXIT);
            REQUIRE(setting.value().toBool());

            const Setting& setting2 = settings.get(SettingKey::MAIN_CLOSE_TO_TRAY);
            REQUIRE(setting2.value().toBool());
        }

        SECTION("setValue")
        {
            Setting& setting = settings.get(SettingKey::MAIN_CONFIRM_EXIT);
            REQUIRE(setting.value() == setting.defaultValue());
            setting.setValue(true);
            REQUIRE(setting.value().toBool());
            setting.restoreDefaults();
            REQUIRE(setting.value() == setting.defaultValue());
        }

        SECTION("isEnabled always enabled setting")
        {
            const Setting& setting = settings.get(SettingKey::MAIN_CONFIRM_EXIT);
            REQUIRE(setting.isEnabled());
        }

        SECTION("isEnabled setting enabled if enableCondition is true")
        {
            SECTION("bool condition")
            {
                Setting& notificationsEnabled = settings.get(SettingKey::NOTIFICATIONS_ENABLED);
                Setting& playNotificationEnabled = settings.get(SettingKey::NOTIFICATIONS_NEW_SONG);
                QSignalSpy spy(&playNotificationEnabled, SIGNAL(isEnabledChanged()));
                REQUIRE(notificationsEnabled.value().toBool());
                REQUIRE(playNotificationEnabled.isEnabled());

                notificationsEnabled.setValue(false);
                REQUIRE(spy.count() == 1);
                REQUIRE(!playNotificationEnabled.isEnabled());
            }

            SECTION("string comparison condition")
            {
                Setting& theme = settings.get(SettingKey::APPEARANCE_THEME);
                Setting& accent = settings.get(SettingKey::APPEARANCE_ACCENT);
                QSignalSpy spy(&accent, SIGNAL(isEnabledChanged()));
                REQUIRE(theme.value().toString() == theme.defaultValue());
                REQUIRE(!accent.isEnabled());

                theme.setValue("Custom");
                REQUIRE(spy.count() == 1);
                REQUIRE(accent.isEnabled());
            }

            SECTION("qtVersion condition, require >= 5.11")
            {
                Setting::Data data;
                data.enableCondition = "qtVersion >= 5.11";
                data.key = "test";
                Setting setting(settings, *mainCategory, data);
                QVersionNumber qtVersion(QT_VERSION_MAJOR, QT_VERSION_MINOR);
                if (qtVersion >= QVersionNumber::fromString("5.11"))
                    REQUIRE(setting.isEnabled());
                else
                    REQUIRE(!setting.isEnabled());
            }

            SECTION("qtVersion condition, require >= 6.5")
            {
                Setting::Data data;
                data.enableCondition = "qtVersion >= 6.5";
                data.key = "test";
                Setting setting(settings, *mainCategory, data);
                REQUIRE(!setting.isEnabled());
            }
        }

        SECTION("get invalid setting key throws")
        {
            REQUIRE_THROWS(settings.get("category/subcategory/key"));
        }
    }
}
