#include "catch.hpp"
#include "DI.hpp"
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/ColorSettingViewModel.hpp>
#include <QtTest/QSignalSpy>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;

TEST_CASE("ColorSettingViewModelTests") {
    ScopedScope scope;
    auto injector = getTestInjector(scope);
    Settings& settings = injector.create<Settings&>();
    Setting& setting = settings.get(SettingKey::APPEARANCE_ACCENT);
    ColorSettingViewModel model(setting, nullptr);
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

