#include <catch/catch.hpp>
#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/BoolSettingViewModel.hpp>
#include <QtTest/QSignalSpy>
#include <Utils/DependencyPool.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Tests;

TEST_CASE("SettingViewModelTests")
{
    DependencyPool pool;
    Settings& settings = pool.getSettings();
    Setting& setting = settings.get(SettingKey::NOTIFICATIONS_ENABLED);
    BoolSettingViewModel model(setting, nullptr);
    QSignalSpy spy(&model, SIGNAL(valueChanged()));

    SECTION("Basic attributes")
    {
        REQUIRE(model.type() == "bool");
        REQUIRE(!model.name().isEmpty());
        REQUIRE(model.enabled());
        REQUIRE(!model.toolTip().isEmpty());
    }

    SECTION("enabled should change when enableCondition is met")
    {
        Setting& dependantSetting = settings.get(SettingKey::NOTIFICATIONS_PAUSED);
        BoolSettingViewModel dependantModel(dependantSetting, nullptr);
        QSignalSpy enabledSpy(&dependantModel, SIGNAL(enabledChanged()));

        REQUIRE(enabledSpy.count() == 0);
        REQUIRE(dependantModel.enabled());

        model.setValue(false);

        REQUIRE(enabledSpy.count() == 1);
        REQUIRE(!dependantModel.enabled());

        model.setValue(true);
    }
}
