#include <catch.hpp>
#include <fakeit.hpp>
#include <MellowPlayer/Presentation/IconProvider.hpp>

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)
using namespace fakeit;

bool isNullIcon(QIcon icon) {
    return icon.pixmap(64, 64).isNull();
}

TEST_CASE("IconProviderTests") {
    SECTION("windowIcon") { REQUIRE(!isNullIcon(IconProvider::windowIcon())); }
    SECTION("restoreWindow") { REQUIRE(!isNullIcon(IconProvider::restoreWindow())); }
    SECTION("play") { REQUIRE(!isNullIcon(IconProvider::play())); }
    SECTION("next") { REQUIRE(!isNullIcon(IconProvider::next())); }
    SECTION("previous") { REQUIRE(!isNullIcon(IconProvider::previous())); }
    SECTION("quit") { REQUIRE(!isNullIcon(IconProvider::quit())); }

    SECTION("trayIcon") {
        Mock<IApplicationSettings> appSettingsMock;
        When(Method(appSettingsMock, getTrayIcon)).Return("", __FILE__, "folder-music");

        IconProvider iconProvider(appSettingsMock.get());

        // default icon
        REQUIRE(!isNullIcon(iconProvider.trayIcon()));

        // from file (not an image, should be null)
        REQUIRE(isNullIcon(iconProvider.trayIcon()));

#ifndef Q_OS_LINUX
        // from theme, should not be null on Linux
        REQUIRE(isNullIcon(iconProvider.trayIcon()));
#endif

    }
}
