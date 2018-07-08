#include <MellowPlayer/Presentation/Converters/UpdaterStatusConverter.hpp>
#include <catch/catch.hpp>

using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Presentation;

SCENARIO("Updater status can be converted to a string")
{
    UpdaterStatusConverter converter;
    UpdaterStatusStrings strings;

    GIVEN("UpdaterStatus::None")
    {
        Updater::Status status = Updater::Status::None;

        WHEN("converting to string")
        {
            QString statusString = converter.toString(status);

            THEN("the string is None")
            {
                REQUIRE(statusString == strings.none());
            }
        }
    }

    GIVEN("UpdaterStatus::Checking")
    {
        Updater::Status status = Updater::Status::Checking;

        WHEN("converting to string")
        {
            QString statusString = converter.toString(status);

            THEN("the string is valid")
            {
                REQUIRE(statusString == strings.checking());
            }
        }
    }

    GIVEN("UpdaterStatus::Downloading")
    {
        Updater::Status status = Updater::Status::Downloading;

        WHEN("converting to string")
        {
            QString statusString = converter.toString(status);

            THEN("the string is valid")
            {
                REQUIRE(statusString == strings.downloading());
            }
        }
    }

    GIVEN("UpdaterStatus::Installing")
    {
        Updater::Status status = Updater::Status::Installing;

        WHEN("converting to string")
        {
            QString statusString = converter.toString(status);

            THEN("the string is valid")
            {
                REQUIRE(statusString == strings.installing());
            }
        }
    }
}

SCENARIO("Updater status can be converted from a string")
{
    UpdaterStatusConverter converter;
    UpdaterStatusStrings strings;

    GIVEN("an empty status string")
    {
        QString statusString = "";

        WHEN("converting from string")
        {
            Updater::Status status = converter.fromString(statusString);

            THEN("Status is None")
            {
                REQUIRE(status == Updater::Status::None);
            }
        }
    }

    GIVEN("a None status string")
    {
        QString statusString = strings.none();

        WHEN("converting from string")
        {
            Updater::Status status = converter.fromString(statusString);

            THEN("Status is None")
            {
                REQUIRE(status == Updater::Status::None);
            }
        }
    }

    GIVEN("a valid status string")
    {
        QString statusString = strings.checking();

        WHEN("converting from string")
        {
            Updater::Status status = converter.fromString(statusString);

            THEN("Status is valid")
            {
                REQUIRE(status == Updater::Status::Checking);
            }
        }
    }

    GIVEN("an invalid status string")
    {
        QString statusString = "foo";

        WHEN("converting from string")
        {
            Updater::Status status = converter.fromString(statusString);

            THEN("Status is None")
            {
                REQUIRE(status == Updater::Status::None);
            }
        }
    }
}