#include "catch.hpp"
#include "DI.hpp"
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <MellowPlayer/Presentation/Factories/SettingViewModelFactory.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/BoolSettingViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/ColorSettingViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/ShortcutSettingViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/EnumSettingViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/StringSettingViewModel.hpp>

USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Presentation)

TEST_CASE("SettingModelFactoryTests") {
    ScopedScope scope;
    auto injector = getTestInjector(scope);
    Settings& settings = injector.create<Settings&>();
    SettingViewModelFactory factory;

    SECTION("createBoolSettingModel") {
        Setting& setting = settings.get(SettingKey::NOTIFICATIONS_ENABLED);
        SettingViewModel* settingModel = factory.create(setting, &settings);
        BoolSettingViewModel* specificSettingModel = qobject_cast<BoolSettingViewModel*>(settingModel);
        REQUIRE(specificSettingModel != nullptr);
    }

    SECTION("createColorSettingModel") {
        Setting& setting = settings.get(SettingKey::APPEARANCE_ACCENT);
        SettingViewModel* settingModel = factory.create(setting, &settings);
        ColorSettingViewModel* specificSettingModel = qobject_cast<ColorSettingViewModel*>(settingModel);
        REQUIRE(specificSettingModel != nullptr);
    }

    SECTION("createShortcutSettingModel") {
        Setting& setting = settings.get(SettingKey::SHORTCUTS_PLAY);
        SettingViewModel* settingModel = factory.create(setting, &settings);
        ShortcutSettingViewModel* specificSettingModel = qobject_cast<ShortcutSettingViewModel*>(settingModel);
        REQUIRE(specificSettingModel != nullptr);
    }

    SECTION("createStringSettingModel by default") {
        Setting& setting = settings.get(SettingKey::PRIVATE_CURRENT_SERVICE);
        SettingViewModel* settingModel = factory.create(setting, &settings);
        StringSettingViewModel* specificSettingModel = qobject_cast<StringSettingViewModel*>(settingModel);
        REQUIRE(specificSettingModel != nullptr);
    }
}

