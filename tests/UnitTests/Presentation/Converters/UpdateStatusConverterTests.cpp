#include <catch.hpp>
#include <MellowPlayer/Presentation/Converters/UpdaterStatusConverter.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Infrastructure;

SCENARIO("Updater status can be converted to a string") {
    GIVEN("UpdaterStatus::None") {
        Updater::Status status = Updater::Status::None;

        WHEN("converting to string") {
            QString statusString = UpdaterStatusConverter::toString(status);

            THEN("the string is empty") {
                REQUIRE(statusString.isEmpty());
            }
        }
    }

    GIVEN("UpdaterStatus::Checking") {
        Updater::Status status = Updater::Status::Checking;

        WHEN("converting to string") {
            QString statusString = UpdaterStatusConverter::toString(status);

            THEN("the string is valid") {
                REQUIRE(statusString == UpdaterStatusConverter::CHECKING);
            }
        }
    }

    GIVEN("UpdaterStatus::Downloading") {
        Updater::Status status = Updater::Status::Downloading;

        WHEN("converting to string") {
            QString statusString = UpdaterStatusConverter::toString(status);

            THEN("the string is valid") {
                REQUIRE(statusString == UpdaterStatusConverter::DOWNLOADING);
            }
        }
    }

    GIVEN("UpdaterStatus::Installing") {
        Updater::Status status = Updater::Status::Installing;

        WHEN("converting to string") {
            QString statusString = UpdaterStatusConverter::toString(status);

            THEN("the string is valid") {
                REQUIRE(statusString == UpdaterStatusConverter::INSTALLING);
            }
        }
    }
}

SCENARIO("Updater status can be converted from a string") {
    GIVEN("an empty status string") {
        QString statusString = "";

        WHEN("converting from string") {
            Updater::Status status = UpdaterStatusConverter::fromString(statusString);

            THEN("Status is None") {
                REQUIRE(status == Updater::Status::None);
            }
        }
    }

    GIVEN("a valid status string") {
        QString statusString = UpdaterStatusConverter::CHECKING;

        WHEN("converting from string") {
            Updater::Status status = UpdaterStatusConverter::fromString(statusString);

            THEN("Status is valid") {
                REQUIRE(status == Updater::Status::Checking);
            }
        }
    }

    GIVEN("an invalid status string") {
        QString statusString = "foo";

        WHEN("converting from string") {
            Updater::Status status = UpdaterStatusConverter::fromString(statusString);

            THEN("Status is None") {
                REQUIRE(status == Updater::Status::None);
            }
        }
    }
}