#include "catch.hpp"
#include "DI.hpp"
#include <MellowPlayer/Presentation/Models/Settings/Types/ColorSettingModel.hpp>
#include <QtTest/QSignalSpy>

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

TEST_CASE("ColorSettingModelTests") {
    ScopedScope scope;
    auto injector = getTestInjector(scope);
    Settings& settings = injector.create<Settings&>();
    Setting& setting = settings.get(SettingKey::APPEARANCE_ACCENT);
    ColorSettingModel model(setting, nullptr);
    QSignalSpy spy(&model, SIGNAL(valueChanged()));

    SECTION("setValue") {
        REQUIRE(model.getValue() != "red");
        REQUIRE(spy.count() == 0);
        model.setValue("red");
        REQUIRE(model.getValue() == "red");
        REQUIRE(spy.count() == 1);
    }

    SECTION("QML Component looks valid") {
        REQUIRE(model.getQmlComponent().toLower().contains("color"));
    }
}

