#include "catch.hpp"
#include "DI.hpp"
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/BoolSettingViewModel.hpp>
#include <QtTest/QSignalSpy>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;

TEST_CASE("BoolSettingViewModelTests") {
    ScopedScope scope;
    auto injector = getTestInjector(scope);
    Settings& settings = injector.create<Settings&>();
    Setting& setting = settings.get(SettingKey::NOTIFICATIONS_ENABLED);
    BoolSettingViewModel model(setting, nullptr);
    QSignalSpy spy(&model, SIGNAL(valueChanged()));

    SECTION("setValue") {
        REQUIRE(model.getValue());
        REQUIRE(spy.count() == 0);
        model.setValue(false);
        REQUIRE(!model.getValue());
        REQUIRE(spy.count() == 1);
        model.setValue(true);
    }

    SECTION("QML Component looks valid") {
        REQUIRE(model.getQmlComponent().toLower().contains("bool"));
    }
}

