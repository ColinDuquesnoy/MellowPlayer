#include "catch.hpp"
#include "DI.hpp"
#include <MellowPlayer/Presentation/Models/Settings/SettingsCategoryModel.hpp>
USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Presentation)

TEST_CASE("SettingsCategoryModelTests") {
    ScopedScope scope;
    auto injector = getTestInjector(scope);
    Settings& settings = injector.create<Settings&>();
    SettingsCategoryModel model(&settings.getCategory("main"), nullptr);

    REQUIRE(model.getName().toStdString() == "General");
    REQUIRE(!model.getIcon().isEmpty());
    REQUIRE(!model.getQmlComponent().isEmpty());
    REQUIRE(model.getSettingsModel()->rowCount() > 1);
}

TEST_CASE("CustomSettingsCategoryModelTests") {
    ScopedScope scope;
    auto injector = getTestInjector(scope);
    Settings& settings = injector.create<Settings&>();
    CustomSettingsCategoryModel model("CategoryName", "CategoryIcon", "CategoryQmlComponent", nullptr);

    REQUIRE(model.getName() == "CategoryName");
    REQUIRE(model.getIcon() == "CategoryIcon");
    REQUIRE(model.getQmlComponent() == "CategoryQmlComponent");
    REQUIRE(model.getSettingsModel()->rowCount() == 0);
}

