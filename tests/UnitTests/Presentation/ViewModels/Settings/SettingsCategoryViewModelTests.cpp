#include "catch.hpp"
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <MellowPlayer/Application/Settings/Settings.hpp>
#include <MellowPlayer/Presentation/ViewModels/ThemeViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/SettingsCategoryViewModel.hpp>
#include <Utils/DependencyPool.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Tests;

TEST_CASE("SettingsCategoryViewModelTests") {
    DependencyPool pool;
    Settings& settings = pool.getSettings();
    ThemeViewModel& themeViewModel = pool.getThemeViewModel();
    SettingsCategoryViewModel model(themeViewModel, &settings.getCategory("main"));

    REQUIRE(model.getName().toStdString() == "General");
    REQUIRE(!model.getIcon().isEmpty());
    REQUIRE(!model.getQmlComponent().isEmpty());
    REQUIRE(model.getSettingsModel()->count() > 1);
}

TEST_CASE("CustomSettingsCategoryViewModelTests") {
    DependencyPool pool;
    Settings& settings = pool.getSettings();
    ThemeViewModel& themeViewModel = pool.getThemeViewModel();
    CustomSettingsCategoryViewModel model("CategoryName", "CategoryIcon", "CategoryQmlComponent", themeViewModel);

    REQUIRE(model.getName() == "CategoryName");
    REQUIRE(model.getIcon() == "CategoryIcon");
    REQUIRE(model.getQmlComponent() == "CategoryQmlComponent");
    REQUIRE(model.getSettingsModel()->count() == 0);
}

