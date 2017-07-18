#include "catch.hpp"
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/SettingsViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/BoolSettingViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/StringSettingViewModel.hpp>
#include <Utils/DependencyPool.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Tests;

TEST_CASE("SettingsViewModelTests") {
    DependencyPool pool;
    Settings& settings = pool.getSettings();
    ThemeViewModel& themeViewModel = pool.getThemeViewModel();
    SettingsViewModel viewModel(settings, themeViewModel);

    SECTION("get") {
        SettingViewModel* settingModel = viewModel.get(SettingKey::NOTIFICATIONS_ENABLED);
        REQUIRE(settingModel != nullptr);
    }

    SECTION("getCategories") {
        int extraCategories = 2;
        REQUIRE(viewModel.getCategories()->count() - extraCategories == (settings.getCategories().count() - 1));
    }
}
