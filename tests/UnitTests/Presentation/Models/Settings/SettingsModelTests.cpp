#include "catch.hpp"
#include "DI.hpp"
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <MellowPlayer/Presentation/Models/Settings/SettingsModel.hpp>
#include <MellowPlayer/Presentation/Models/Settings/Types/BoolSettingModel.hpp>
#include <MellowPlayer/Presentation/Models/Settings/Types/StringSettingModel.hpp>

USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Presentation)

TEST_CASE("SettingsModelTests") {
    ScopedScope scope;
    auto injector = getTestInjector(scope);
    Settings& settings = injector.create<Settings&>();
    SettingsModel model(settings);

    SECTION("get") {
        SettingModel* settingModel = model.get(SettingKey::NOTIFICATIONS_ENABLED);
        REQUIRE(settingModel != nullptr);
    }

    SECTION("getCategories") {
        int extraCategories = 2;
        REQUIRE(model.getCategories()->rowCount() - extraCategories == (settings.getCategories().count() - 1));
    }
}

