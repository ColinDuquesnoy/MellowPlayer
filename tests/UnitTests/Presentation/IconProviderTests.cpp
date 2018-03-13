#include <MellowPlayer/Domain/Settings/ISettingsStore.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Infrastructure/Settings/SettingsSchemaLoader.hpp>
#include <MellowPlayer/Presentation/IconProvider.hpp>
#include <QtCore>
#include <catch/catch.hpp>
#include <fakeit/fakeit.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Infrastructure;
using namespace fakeit;

bool isNullIcon(QIcon icon)
{
    return icon.pixmap(64, 64).isNull();
}

TEST_CASE("IconProviderTests")
{
    SECTION("windowIcon")
    {
        REQUIRE(!isNullIcon(IconProvider::windowIcon()));
    }
    SECTION("restoreWindow")
    {
        REQUIRE(!isNullIcon(IconProvider::restoreWindow()));
    }
    SECTION("play")
    {
        REQUIRE(!isNullIcon(IconProvider::play()));
    }
    SECTION("pause")
    {
        REQUIRE(!isNullIcon(IconProvider::pause()));
    }
    SECTION("next")
    {
        REQUIRE(!isNullIcon(IconProvider::next()));
    }
    SECTION("previous")
    {
        REQUIRE(!isNullIcon(IconProvider::previous()));
    }
    SECTION("quit")
    {
        REQUIRE(!isNullIcon(IconProvider::quit()));
    }
    SECTION("trayIcon")
    {
        REQUIRE(!isNullIcon(IconProvider::trayIcon()));
    }
}
