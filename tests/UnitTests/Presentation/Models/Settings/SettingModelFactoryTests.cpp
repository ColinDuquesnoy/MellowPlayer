#include "catch.hpp"
#include "DI.hpp"
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <MellowPlayer/Presentation/Models/Settings/SettingModelFactory.hpp>
#include <MellowPlayer/Presentation/Models/Settings/Types/BoolSettingModel.hpp>
#include <MellowPlayer/Presentation/Models/Settings/Types/ColorSettingModel.hpp>
#include <MellowPlayer/Presentation/Models/Settings/Types/ShortcutSettingModel.hpp>
#include <MellowPlayer/Presentation/Models/Settings/Types/EnumSettingModel.hpp>
#include <MellowPlayer/Presentation/Models/Settings/Types/StringSettingModel.hpp>

USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Presentation)

TEST_CASE("SettingModelFactoryTests") {
    ScopedScope scope;
    auto injector = getTestInjector(scope);
    Settings& settings = injector.create<Settings&>();
    SettingModelFactory factory;

    SECTION("createBoolSettingModel") {
        Setting& setting = settings.get(SettingKey::NOTIFICATIONS_ENABLED);
        SettingModel* settingModel = factory.create(setting, &settings);
        BoolSettingModel* specificSettingModel = qobject_cast<BoolSettingModel*>(settingModel);
        REQUIRE(specificSettingModel != nullptr);
    }

    SECTION("createColorSettingModel") {
        Setting& setting = settings.get(SettingKey::APPEARANCE_ACCENT);
        SettingModel* settingModel = factory.create(setting, &settings);
        ColorSettingModel* specificSettingModel = qobject_cast<ColorSettingModel*>(settingModel);
        REQUIRE(specificSettingModel != nullptr);
    }

    SECTION("createShortcutSettingModel") {
        Setting& setting = settings.get(SettingKey::SHORTCUTS_PLAY);
        SettingModel* settingModel = factory.create(setting, &settings);
        ShortcutSettingModel* specificSettingModel = qobject_cast<ShortcutSettingModel*>(settingModel);
        REQUIRE(specificSettingModel != nullptr);
    }

    SECTION("createStringSettingModel by default") {
        Setting& setting = settings.get(SettingKey::PRIVATE_CURRENT_SERVICE);
        SettingModel* settingModel = factory.create(setting, &settings);
        StringSettingModel* specificSettingModel = qobject_cast<StringSettingModel*>(settingModel);
        REQUIRE(specificSettingModel != nullptr);
    }
}

