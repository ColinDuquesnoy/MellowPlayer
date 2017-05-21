#include "catch.hpp"
#include "DI.hpp"
#include <MellowPlayer/UseCases/Settings/Setting.hpp>
#include <MellowPlayer/Presentation/Models/Settings/SettingsModel.hpp>
#include <MellowPlayer/Presentation/Models/Settings/Types/BoolSettingModel.hpp>
#include <MellowPlayer/Presentation/Models/Settings/Types/StringSettingModel.hpp>

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

TEST_CASE("SettingsModelTests") {
    ScopedScope scope;
    auto injector = getTestInjector(scope);
    Settings& settings = injector.create<Settings&>();
    SettingsModel model(settings);

    SECTION("createBoolSettingModel") {
        SettingModel* settingModel = model.get(SettingKey::NOTIFICATIONS_ENABLED);
        BoolSettingModel* boolSettingModel = qobject_cast<BoolSettingModel*>(settingModel);
        REQUIRE(boolSettingModel != nullptr);
    }

    SECTION("createStringSettingModel by default") {
        Setting& setting = settings.get(SettingKey::APPEARANCE_ACCENT);
        SettingModel* settingModel = model.get(SettingKey::APPEARANCE_ACCENT);
        StringSettingModel* stringSettingModel = qobject_cast<StringSettingModel*>(settingModel);
        REQUIRE(stringSettingModel != nullptr);
    }
}

