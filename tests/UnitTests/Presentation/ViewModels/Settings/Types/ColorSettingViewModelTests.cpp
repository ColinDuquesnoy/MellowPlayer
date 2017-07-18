#include "catch.hpp"
#include <QtTest/QSignalSpy>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/ColorSettingViewModel.hpp>
#include <MellowPlayer/Application/Settings/Settings.hpp>
#include <Utils/DependencyPool.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Tests;

TEST_CASE("ColorSettingViewModelTests") {
    DependencyPool pool;
    Settings& settings = pool.getSettings();
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

