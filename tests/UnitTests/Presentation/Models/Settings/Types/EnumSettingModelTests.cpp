#include "catch.hpp"
#include "DI.hpp"
#include <MellowPlayer/Presentation/Models/Settings/Types/EnumSettingModel.hpp>
#include <QtTest/QSignalSpy>

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

TEST_CASE("EnumSettingModelTests") {
    ScopedScope scope;
    auto injector = getTestInjector(scope);
    Settings& settings = injector.create<Settings&>();
    Setting& setting = settings.get(SettingKey::APPEARANCE_THEME);
    EnumSettingModel model(setting, nullptr);
    QSignalSpy spy(&model, SIGNAL(valueChanged()));

    SECTION("setValue") {
        REQUIRE(model.getValue() == "Light");
        REQUIRE(spy.count() == 0);
        model.setValue("Dark");
        REQUIRE(model.getValue() == "Dark");
        REQUIRE(spy.count() == 1);
        model.setValue("Light");
    }

    SECTION("getValues") {
        QStringList expected;
        expected << "Light";
        expected << "Dark";
        REQUIRE(model.getValues() == expected);
    }

    SECTION("QML Component looks valid") {
        REQUIRE(model.getQmlComponent().toLower().contains("enum"));
    }
}

