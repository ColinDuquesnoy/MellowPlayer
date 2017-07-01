#include "catch.hpp"
#include "DI.hpp"
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <MellowPlayer/Application/Settings/SettingsCategory.hpp>
#include <MellowPlayer/Application/Settings/Settings.hpp>
#include <MellowPlayer/Presentation/Models/Settings/Types/EnumSettingModel.hpp>
#include <QtTest/QSignalSpy>

USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Presentation)

TEST_CASE("EnumSettingModelTests") {
    ScopedScope scope;
    auto injector = getTestInjector(scope);
    Settings& settings = injector.create<Settings&>();
    SettingsCategory& category = settings.getCategory("appearance");
    Setting::Data settingData;
    settingData.name = "Theme";
    settingData.defaultValue = "Light";
    settingData.enableCondition = "!appearance/adaptive-theme";
    settingData.key = "theme";
    settingData.type = "enum[\"Light\", \"Dark\"]";
    Setting setting(settings, category, settingData);
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

