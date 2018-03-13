#include <catch/catch.hpp>
#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Presentation/Factories/SettingViewModelFactory.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/BoolSettingViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/ColorSettingViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/EnumSettingViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/ShortcutSettingViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/StringSettingViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/ThemeSettingViewModel.hpp>
#include <Utils/DependencyPool.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

TEST_CASE("SettingModelFactoryTests")
{
    MellowPlayer::Tests::DependencyPool pool;
    Settings& settings = pool.getSettings();
    ThemeViewModel& themeViewModel = pool.getThemeViewModel();
    SettingViewModelFactory factory(themeViewModel);

    SECTION("createBoolSettingModel")
    {
        Setting& setting = settings.get(SettingKey::NOTIFICATIONS_ENABLED);
        SettingViewModel* settingModel = factory.create(setting, &settings);
        BoolSettingViewModel* specificSettingModel = qobject_cast<BoolSettingViewModel*>(settingModel);
        REQUIRE(specificSettingModel != nullptr);
    }

    SECTION("createColorSettingModel")
    {
        Setting& setting = settings.get(SettingKey::APPEARANCE_ACCENT);
        SettingViewModel* settingModel = factory.create(setting, &settings);
        ColorSettingViewModel* specificSettingModel = qobject_cast<ColorSettingViewModel*>(settingModel);
        REQUIRE(specificSettingModel != nullptr);
    }

    SECTION("createShortcutSettingModel")
    {
        Setting& setting = settings.get(SettingKey::SHORTCUTS_PLAY);
        SettingViewModel* settingModel = factory.create(setting, &settings);
        ShortcutSettingViewModel* specificSettingModel = qobject_cast<ShortcutSettingViewModel*>(settingModel);
        REQUIRE(specificSettingModel != nullptr);
    }

    SECTION("createStringSettingModel by default")
    {
        Setting& setting = settings.get(SettingKey::PRIVATE_CURRENT_SERVICE);
        SettingViewModel* settingModel = factory.create(setting, &settings);
        StringSettingViewModel* specificSettingModel = qobject_cast<StringSettingViewModel*>(settingModel);
        REQUIRE(specificSettingModel != nullptr);
    }

    SECTION("createThemeSettingViewModel")
    {
        Setting& setting = settings.get(SettingKey::APPEARANCE_THEME);
        SettingViewModel* settingModel = factory.create(setting, &settings);
        ThemeSettingViewModel* specificSettingModel = qobject_cast<ThemeSettingViewModel*>(settingModel);
        REQUIRE(specificSettingModel != nullptr);
    }
}