#include "catch.hpp"
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <MellowPlayer/Application/Settings/Settings.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/SettingsCategoryViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/ThemeViewModel.hpp>
#include <Utils/DependencyPool.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Tests;

TEST_CASE("SettingsCategoryViewModelTests")
{
    DependencyPool pool;
    Settings &settings = pool.getSettings();
    ThemeViewModel &themeViewModel = pool.getThemeViewModel();
    SettingsCategoryViewModel categoryViewModel(themeViewModel, &settings.getCategory("main"));

    REQUIRE(categoryViewModel.getName().toStdString() == "General");
    REQUIRE(!categoryViewModel.getIcon().isEmpty());
    REQUIRE(!categoryViewModel.getQmlComponent().isEmpty());
    REQUIRE(categoryViewModel.getSettingsModel()->count() > 1);

    SECTION("restoreDefaults")
    {
        Setting &inCategorySetting = settings.get(SettingKey::MAIN_CHECK_FOR_UPDATES);
        inCategorySetting.setValue(false);
        Setting &notInCategorySetting = settings.get(SettingKey::APPEARANCE_THEME);
        notInCategorySetting.setValue("Breeze");

        REQUIRE(inCategorySetting.getValue() != inCategorySetting.getDefaultValue());
        REQUIRE(notInCategorySetting.getValue() != notInCategorySetting.getDefaultValue());

        categoryViewModel.restoreDefaults();

        REQUIRE(inCategorySetting.getValue() == inCategorySetting.getDefaultValue());
        REQUIRE(notInCategorySetting.getValue() != notInCategorySetting.getDefaultValue());
    }
}

TEST_CASE("CustomSettingsCategoryViewModelTests")
{
    DependencyPool pool;
    Settings &settings = pool.getSettings();
    ThemeViewModel &themeViewModel = pool.getThemeViewModel();
    CustomSettingsCategoryViewModel model("CategoryName", "CategoryIcon", "CategoryQmlComponent", themeViewModel);

    REQUIRE(model.getName() == "CategoryName");
    REQUIRE(model.getIcon() == "CategoryIcon");
    REQUIRE(model.getQmlComponent() == "CategoryQmlComponent");
    REQUIRE(model.getSettingsModel()->count() == 0);
}
