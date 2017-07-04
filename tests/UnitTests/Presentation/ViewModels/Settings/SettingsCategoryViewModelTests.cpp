#include "catch.hpp"
#include "DI.hpp"
#include <MellowPlayer/Presentation/ViewModels/Settings/SettingsCategoryViewModel.hpp>
USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Presentation)

TEST_CASE("SettingsCategoryViewModelTests") {
    ScopedScope scope;
    auto injector = getTestInjector(scope);
    Settings& settings = injector.create<Settings&>();
    SettingsCategoryViewModel model(&settings.getCategory("main"), nullptr);

    REQUIRE(model.getName().toStdString() == "General");
    REQUIRE(!model.getIcon().isEmpty());
    REQUIRE(!model.getQmlComponent().isEmpty());
    REQUIRE(model.getSettingsModel()->count() > 1);
}

TEST_CASE("CustomSettingsCategoryViewModelTests") {
    ScopedScope scope;
    auto injector = getTestInjector(scope);
    CustomSettingsCategoryViewModel model("CategoryName", "CategoryIcon", "CategoryQmlComponent", nullptr);

    REQUIRE(model.getName() == "CategoryName");
    REQUIRE(model.getIcon() == "CategoryIcon");
    REQUIRE(model.getQmlComponent() == "CategoryQmlComponent");
    REQUIRE(model.getSettingsModel()->count() == 0);
}
