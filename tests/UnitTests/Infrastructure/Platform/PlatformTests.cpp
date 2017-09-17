#include <catch.hpp>
#include <MellowPlayer/Infrastructure/Platform/Platform.hpp>

using namespace MellowPlayer::Infrastructure;

SCENARIO("PlatformTests")
{
    GIVEN("A platform instance")
    {
        Platform platform;

        WHEN("Call name()")
        {
            auto name = platform.name();

            THEN("name is not empty")
            {
                REQUIRE(!name.isEmpty());
            }
        }

#ifdef Q_OS_LINUX
        WHEN("on GNU/Linux with no APPIMAGE environment variable defined")
        {
            THEN("isLinux returns true")
            {
                REQUIRE(platform.isLinux());
            }

            THEN("isAppImage returns false")
            {
                REQUIRE(!platform.isAppImage());
            }

            THEN("isOsx returns false")
            {
                REQUIRE(!platform.isOsx());
            }

            THEN("isWindows returns false")
            {
                REQUIRE(!platform.isWindows());
            }
        }

        WHEN("on GNU/Linux with APPIMAGE environment variable defined")
        {
            qputenv("APPIMAGE", "/path/to/appimage");

            THEN("isAppImage returns true")
            {
                REQUIRE(platform.isAppImage());
            }

            THEN("isLinux returns false")
            {
                REQUIRE(!platform.isLinux());
            }

            THEN("isOsx returns false")
            {
                REQUIRE(!platform.isOsx());
            }

            THEN("isWindows returns false")
            {
                REQUIRE(!platform.isWindows());
            }

            qputenv("APPIMAGE", "");
        }
#endif

#ifdef Q_OS_OSX
        WHEN("on Mac OSX")
        {
            THEN("isOsx returns true")
            {
                REQUIRE(platform.isOsx());
            }

            THEN("isLinux returns false")
            {
                REQUIRE(!platform.isLinux());
            }

            THEN("isAppImage returns false")
            {
                REQUIRE(!platform.isAppImage());
            }

            THEN("isWindows returns false")
            {
                REQUIRE(!platform.isWindows());
            }
        }
#endif

#ifdef Q_OS_WIN
        WHEN("on Windows")
        {
            THEN("isWindows returns true")
            {
                REQUIRE(platform.isWindows());
            }

            THEN("isOsx returns false")
            {
                REQUIRE(!platform.isOsx());
            }

            THEN("isLinux returns false")
            {
                REQUIRE(!platform.isLinux());
            }

            THEN("isAppImage returns false")
            {
                REQUIRE(!platform.isAppImage());
            }
        }
#endif

    }
}