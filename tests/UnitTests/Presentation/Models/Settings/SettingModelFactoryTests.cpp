#include "catch.hpp"
#include "DI.hpp"
#include <MellowPlayer/UseCases/Settings/Setting.hpp>
#include <MellowPlayer/Presentation/Models/Settings/SettingModelFactory.hpp>
#include <MellowPlayer/Presentation/Models/Settings/Types/BoolSettingModel.hpp>
#include <MellowPlayer/Presentation/Models/Settings/Types/StringSettingModel.hpp>

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

TEST_CASE("SettingModelFactoryTests") {
    ScopedScope scope;
    auto injector = getTestInjector(scope);
    Settings& settings = injector.create<Settings&>();
    SettingModelFactory factory;

    SECTION("createBoolSettingModel") {
        Setting& setting = settings.get(SettingKey::NOTIFICATIONS_ENABLED);
        SettingModel* settingModel = factory.create(setting, &settings);
        BoolSettingModel* boolSettingModel = qobject_cast<BoolSettingModel*>(settingModel);
        REQUIRE(boolSettingModel != nullptr);
    }

    SECTION("createStringSettingModel by default") {
        Setting& setting = settings.get(SettingKey::APPEARANCE_ACCENT);
        SettingModel* settingModel = factory.create(setting, &settings);
        StringSettingModel* stringSettingModel = qobject_cast<StringSettingModel*>(settingModel);
        REQUIRE(stringSettingModel != nullptr);
    }
}

