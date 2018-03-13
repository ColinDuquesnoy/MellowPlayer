#include <catch/catch.hpp>
#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/SettingsViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/BoolSettingViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/StringSettingViewModel.hpp>
#include <Utils/DependencyPool.hpp>
#include <UnitTests/Presentation/FakeMainWindow.hpp>
#include <UnitTests/Presentation/Qml/FakeContextProperties.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Presentation::Tests;
using namespace MellowPlayer::Tests;

TEST_CASE("SettingsViewModelTests")
{
    DependencyPool pool;
    Settings& settings = pool.getSettings();
    ThemeViewModel& themeViewModel = pool.getThemeViewModel();
    FakeContextProperties contextProperties;
    SettingsViewModel settingsViewModel(settings, themeViewModel, contextProperties);

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
