#include <catch/catch.hpp>
#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/BoolSettingViewModel.hpp>
#include <QtTest/QSignalSpy>
#include <Utils/DependencyPool.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Tests;

TEST_CASE("BoolSettingViewModelTests")
{
    DependencyPool pool;
    Settings& settings = pool.getSettings();
    Setting& setting = settings.get(SettingKey::NOTIFICATIONS_ENABLED);
    BoolSettingViewModel model(setting, nullptr);
    QSignalSpy spy(&model, SIGNAL(valueChanged()));

    SECTION("setValue")
    {
        REQUIRE(model.getValue());
        REQUIRE(spy.count() == 0);
        model.setValue(false);
        REQUIRE(!model.getValue());
        REQUIRE(spy.count() == 1);
        model.setValue(true);
    }

    SECTION("QML Component looks valid")
    {
        REQUIRE(model.qmlComponent().toLower().contains("bool"));
    }
}
