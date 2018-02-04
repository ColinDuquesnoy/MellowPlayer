#include <catch/catch.hpp>
#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/SettingsCategoryViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/ThemeViewModel.hpp>
#include <Utils/DependencyPool.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Tests;

TEST_CASE("SettingsCategoryViewModelTests")
{
    DependencyPool pool;
    Settings& settings = pool.getSettings();
    ThemeViewModel& themeViewModel = pool.getThemeViewModel();
    SettingsCategoryViewModel categoryViewModel(themeViewModel, &settings.category("main"));

    REQUIRE(categoryViewModel.name().toStdString() == "General");
    REQUIRE(!categoryViewModel.icon().isEmpty());
    REQUIRE(!categoryViewModel.qmlComponent().isEmpty());
    REQUIRE(categoryViewModel.settingsModel()->count() > 1);

    SECTION("restoreDefaults")
    {
        Setting& inCategorySetting = settings.get(SettingKey::MAIN_CHECK_FOR_UPDATES);
        inCategorySetting.setValue(false);
        Setting& notInCategorySetting = settings.get(SettingKey::APPEARANCE_THEME);
        notInCategorySetting.setValue("Breeze");

        REQUIRE(inCategorySetting.value() != inCategorySetting.defaultValue());
        REQUIRE(notInCategorySetting.value() != notInCategorySetting.defaultValue());

        categoryViewModel.restoreDefaults();

        REQUIRE(inCategorySetting.value() == inCategorySetting.defaultValue());
        REQUIRE(notInCategorySetting.value() != notInCategorySetting.defaultValue());
    }
}

TEST_CASE("CustomSettingsCategoryViewModelTests")
{
    DependencyPool pool;
    ThemeViewModel& themeViewModel = pool.getThemeViewModel();
    CustomSettingsCategoryViewModel model("CategoryName", "CategoryIcon", "CategoryQmlComponent", themeViewModel);

    REQUIRE(model.name() == "CategoryName");
    REQUIRE(model.icon() == "CategoryIcon");
    REQUIRE(model.qmlComponent() == "CategoryQmlComponent");
    REQUIRE(model.settingsModel()->count() == 0);
}
