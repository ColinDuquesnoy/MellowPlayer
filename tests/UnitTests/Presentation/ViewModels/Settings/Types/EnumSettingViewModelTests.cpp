#include "catch.hpp"
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <MellowPlayer/Application/Settings/Settings.hpp>
#include <MellowPlayer/Application/Settings/SettingsCategory.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/EnumSettingViewModel.hpp>
#include <QtTest/QSignalSpy>
#include <Utils/DependencyPool.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Tests;

TEST_CASE("EnumSettingViewModelTests")
{
    DependencyPool pool;
    Settings &settings = pool.getSettings();
    SettingsCategory &category = settings.getCategory("appearance");
    Setting::Data settingData;
    settingData.name = "Theme";
    settingData.defaultValue = "Light";
    settingData.enableCondition = "!appearance/adaptive-theme";
    settingData.key = "theme";
    settingData.type = "enum[\"Light\", \"Dark\"]";
    Setting setting(settings, category, settingData);
    EnumSettingViewModel model(setting, nullptr);
    QSignalSpy spy(&model, SIGNAL(valueChanged()));

    SECTION("setValue")
    {
        REQUIRE(model.getValue() == "Light");
        REQUIRE(spy.count() == 0);
        model.setValue("Dark");
        REQUIRE(model.getValue() == "Dark");
        REQUIRE(spy.count() == 1);
        model.setValue("Light");
    }

    SECTION("getValues")
    {
        QStringList expected;
        expected << "Light";
        expected << "Dark";
        REQUIRE(model.getValues() == expected);
    }

    SECTION("QML Component looks valid")
    {
        REQUIRE(model.getQmlComponent().toLower().contains("enum"));
    }
}
