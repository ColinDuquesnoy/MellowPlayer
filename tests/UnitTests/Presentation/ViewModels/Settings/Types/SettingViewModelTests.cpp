#include "catch.hpp"
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <MellowPlayer/Application/Settings/Settings.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/BoolSettingViewModel.hpp>
#include <QtTest/QSignalSpy>
#include <Utils/DependencyPool.hpp>

using namespace MellowPlayer::Application;
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
        REQUIRE(model.getType() == "bool");
        REQUIRE(!model.getName().isEmpty());
        REQUIRE(model.getEnabled());
        REQUIRE(!model.getToolTip().isEmpty());
    }

    SECTION("enabled should change when enableCondition is met")
    {
        Setting& dependantSetting = settings.get(SettingKey::NOTIFICATIONS_PAUSED);
        BoolSettingViewModel dependantModel(dependantSetting, nullptr);
        QSignalSpy enabledSpy(&dependantModel, SIGNAL(enabledChanged()));

        REQUIRE(enabledSpy.count() == 0);
        REQUIRE(dependantModel.getEnabled());

        model.setValue(false);

        REQUIRE(enabledSpy.count() == 1);
        REQUIRE(!dependantModel.getEnabled());

        model.setValue(true);
    }
}
