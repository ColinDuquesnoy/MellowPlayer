#include <catch/catch.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/ShortcutSettingViewModel.hpp>
#include <QtTest/QSignalSpy>
#include <Utils/DependencyPool.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Tests;

TEST_CASE("ShortcutSettingViewModelTests")
{
    DependencyPool pool;
    Settings& settings = pool.getSettings();
    Setting& setting = settings.get(SettingKey::SHORTCUTS_PLAY);
    ShortcutSettingViewModel model(setting, nullptr);
    model.setValue("Ctrl+Alt+P");
    QSignalSpy spy(&model, SIGNAL(valueChanged()));

    SECTION("setValue")
    {
        REQUIRE(model.getValue() == "Ctrl+Alt+P");
        REQUIRE(spy.count() == 0);
        model.setValue("Ctrl+P");
        REQUIRE(model.getValue() == "Ctrl+P");
        REQUIRE(spy.count() == 1);
        model.setValue("Ctrl+Alt+P");
    }

    SECTION("keySequenceToString")
    {
        REQUIRE(model.keySequenceToString(Qt::Key_M, Qt::ControlModifier).toStdString() == "Ctrl+M");
        REQUIRE(model.keySequenceToString(Qt::Key_M, Qt::AltModifier).toStdString() == "Alt+M");
        REQUIRE(model.keySequenceToString(Qt::Key_M, Qt::ShiftModifier).toStdString() == "Shift+M");
        REQUIRE(model.keySequenceToString(Qt::Key_M, Qt::MetaModifier).toStdString() == "Meta+M");
        REQUIRE(model.keySequenceToString(Qt::Key_unknown, Qt::ControlModifier).contains("Ctrl+"));
    }

    SECTION("isValidKeySequence")
    {
        REQUIRE(model.isValidKeySequence(Qt::Key_M, Qt::ControlModifier));
        REQUIRE(model.isValidKeySequence(Qt::Key_M, Qt::AltModifier));
        REQUIRE(model.isValidKeySequence(Qt::Key_M, Qt::ShiftModifier));
        REQUIRE(model.isValidKeySequence(Qt::Key_M, Qt::MetaModifier));
        REQUIRE(!model.isValidKeySequence(Qt::Key_Control, Qt::AltModifier));
        REQUIRE(!model.isValidKeySequence(Qt::Key_Alt, Qt::ControlModifier));
        REQUIRE(!model.isValidKeySequence(Qt::Key_Meta, Qt::ControlModifier));
        REQUIRE(!model.isValidKeySequence(Qt::Key_Shift, Qt::ControlModifier));
        REQUIRE(!model.isValidKeySequence(Qt::Key_unknown, Qt::ControlModifier));
        REQUIRE(!model.isValidKeySequence(Qt::Key_M, 0));
    }

    SECTION("QML Component looks valid")
    {
        REQUIRE(model.qmlComponent().toLower().contains("shortcut"));
    }
}
