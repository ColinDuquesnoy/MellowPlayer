#include "catch.hpp"
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/SettingsViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/BoolSettingViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/StringSettingViewModel.hpp>
#include <Utils/DependencyPool.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Tests;

TEST_CASE("SettingsViewModelTests")
{
    DependencyPool pool;
    Settings& settings = pool.getSettings();
    ThemeViewModel& themeViewModel = pool.getThemeViewModel();
    SettingsViewModel settingsViewModel(settings, themeViewModel);

    SECTION("get")
    {
        SettingViewModel* settingModel = settingsViewModel.get(SettingKey::NOTIFICATIONS_ENABLED);
        REQUIRE(settingModel != nullptr);
    }

    SECTION("categories")
    {
        int extraCategories = 2;
        REQUIRE(settingsViewModel.categories()->count() - extraCategories == (settings.categories().count() - 1));
    }

    SECTION("restoreDefaults")
    {
        Setting& s1 = settings.get(SettingKey::NOTIFICATIONS_ENABLED);
        s1.setValue(false);
        Setting& s2 = settings.get(SettingKey::APPEARANCE_THEME);
        s2.setValue("Breeze");

        REQUIRE(s1.value() != s1.defaultValue());
        REQUIRE(s2.value() != s2.defaultValue());

        settingsViewModel.restoreDefaults();

        REQUIRE(s1.value() == s1.defaultValue());
        REQUIRE(s2.value() == s2.defaultValue());
    }
}
