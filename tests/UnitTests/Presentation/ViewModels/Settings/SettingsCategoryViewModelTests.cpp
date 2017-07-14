#include "catch.hpp"
#include "DI.hpp"
#include <MellowPlayer/Presentation/ViewModels/ThemeViewModel.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;

TEST_CASE("SettingsCategoryViewModelTests") {
    ScopedScope scope;
    auto injector = getTestInjector(scope);
    Settings& settings = injector.create<Settings&>();
    ThemeViewModel& themeViewModel = injector.create<ThemeViewModel&>();
    SettingsCategoryViewModel model(themeViewModel, &settings.getCategory("main"));

    REQUIRE(model.getName().toStdString() == "General");
    REQUIRE(!model.getIcon().isEmpty());
    REQUIRE(!model.getQmlComponent().isEmpty());
    REQUIRE(model.getSettingsModel()->count() > 1);
}

TEST_CASE("CustomSettingsCategoryViewModelTests") {
    ScopedScope scope;
    auto injector = getTestInjector(scope);
    Settings& settings = injector.create<Settings&>();
    ThemeViewModel& themeViewModel = injector.create<ThemeViewModel&>();
    CustomSettingsCategoryViewModel model("CategoryName", "CategoryIcon", "CategoryQmlComponent", themeViewModel);

    REQUIRE(model.getName() == "CategoryName");
    REQUIRE(model.getIcon() == "CategoryIcon");
    REQUIRE(model.getQmlComponent() == "CategoryQmlComponent");
    REQUIRE(model.getSettingsModel()->count() == 0);
}

