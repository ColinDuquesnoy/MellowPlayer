#include <catch/catch.hpp>
#include <MellowPlayer/Infrastructure/PlatformFilters/FilterConverter.hpp>

using namespace MellowPlayer::Infrastructure;

SCENARIO("FilterConverter can convert strings to Filter enums")
{
    GIVEN("a FilterConverter instance")
    {
        FilterConverter converter;

        WHEN("filter string is 'All'")
        {
            QString filter = "All";

            THEN("converter return Filter::All")
            {
                REQUIRE(converter.fromString(filter) == Filter::All);
            }
        }

        WHEN("filter string is 'Linux'")
        {
            QString filter = "Linux";

            THEN("converter return Filter::Linux")
            {
                REQUIRE(converter.fromString(filter) == Filter::Linux);
            }
        }

        WHEN("filter string is 'AppImage'")
        {
            QString filter = "AppImage";

            THEN("converter return Filter::AppImage")
            {
                REQUIRE(converter.fromString(filter) == Filter::AppImage);
            }
        }

        WHEN("filter string is 'OSX'")
        {
            QString filter = "OSX";

            THEN("converter return Filter::OSX")
            {
                REQUIRE(converter.fromString(filter) == Filter::OSX);
            }
        }

        WHEN("filter string is 'Windows'")
        {
            QString filter = "Windows";

            THEN("converter return Filter::Windows")
            {
                REQUIRE(converter.fromString(filter) == Filter::Windows);
            }
        }

        WHEN("filter is invalid")
        {
            QString filter = "not a valid filter";

            THEN("converter returns Filter::All")
            {
                REQUIRE(converter.fromString(filter) == Filter::All);
            }
        }

        WHEN("filter has trailing and leading spaces")
        {
            QString filter = " Linux ";

            THEN("filter enum is correct")
            {
                REQUIRE(converter.fromString(filter) == Filter::Linux);
            }
        }
    }
}

SCENARIO("FilterConverter can convert Filter enums to strings")
{
    GIVEN("a FilterConverter instance")
    {
        FilterConverter converter;

        WHEN("filter is Filter::All")
        {
            Filter filter = Filter::All;

            THEN("converter return 'All'")
            {
                REQUIRE(converter.toString(filter) == "All");
            }
        }

        WHEN("filter is Filter::Linux")
        {
            Filter filter = Filter::Linux;

            THEN("converter return 'Linux'")
            {
                REQUIRE(converter.toString(filter) == "Linux");
            }
        }

        WHEN("filter is Filter::AppImage")
        {
            Filter filter = Filter::AppImage;

            THEN("converter return 'AppImage'")
            {
                REQUIRE(converter.toString(filter) == "AppImage");
            }
        }

        WHEN("filter is Filter::OSX")
        {
            Filter filter = Filter::OSX;

            THEN("converter return 'OSX'")
            {
                REQUIRE(converter.toString(filter) == "OSX");
            }
        }

        WHEN("filter is Filter::Windows")
        {
            Filter filter = Filter::Windows;

            THEN("converter return 'Windows'")
            {
                REQUIRE(converter.toString(filter) == "Windows");
            }
        }
    }
}
