#include "catch.hpp"
#include "DI.hpp"
#include <MellowPlayer/UseCases/Settings/Setting.hpp>
#include <MellowPlayer/Presentation/Models/Settings/Types/BoolSettingModel.hpp>
#include <QtTest/QSignalSpy>

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

TEST_CASE("SettingModelTests") {
    ScopedScope scope;
    auto injector = getTestInjector(scope);
    Settings& settings = injector.create<Settings&>();
    Setting& setting = settings.get(SettingKey::NOTIFICATIONS_ENABLED);
    BoolSettingModel model(setting, nullptr);
    QSignalSpy spy(&model, SIGNAL(valueChanged()));

    SECTION("Basic attributes") {
        REQUIRE(model.getType() == "bool");
        REQUIRE(!model.getName().isEmpty());
        REQUIRE(model.getEnabled());
        REQUIRE(!model.getToolTip().isEmpty());
    }

    SECTION("enabled should change when enableCondition is met") {
        Setting& dependantSetting = settings.get(SettingKey::NOTIFICATIONS_PAUSED);
        BoolSettingModel dependantModel(dependantSetting, nullptr);
        QSignalSpy enabledSpy(&dependantModel, SIGNAL(enabledChanged()));

        REQUIRE(enabledSpy.count() == 0);
        REQUIRE(dependantModel.getEnabled());

        model.setValue(false);

        REQUIRE(enabledSpy.count() == 1);
        REQUIRE(!dependantModel.getEnabled());

        model.setValue(true);
    }

}

