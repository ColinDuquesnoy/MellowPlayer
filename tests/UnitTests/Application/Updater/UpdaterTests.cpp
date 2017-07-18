#include "catch.hpp"
#include <MellowPlayer/Application/Updater/Updater.hpp>
#include <Mocks/FakeHttpClient.hpp>
#include <MellowPlayer/Application/Updater/Github/GithubReleaseQuerier.hpp>
#include <QtTest/QSignalSpy>
#include "DI.hpp"

using namespace MellowPlayer::Application;

SCENARIO("check for stable updates") {
    FakeHttpClient fakeHttpClient;
    GithubReleaseQuerier querier(fakeHttpClient);
    ScopedScope scope;
    auto injector = getTestInjector(scope);
    Settings& settings = injector.create<Settings&>();
    settings.get(SettingKey::MAIN_UPDATE_CHANNEL).setValue(UpdateChannelStringer::toString(UpdateChannel::Stable));

    GIVEN("current version is 2.2.4 from April 2017") {
        Release currentRelease("2.2.4", QDate::fromString("2017-04-29", Qt::ISODate));
        Updater updater(querier, settings);
        updater.setCurrentRelease(&currentRelease);
        QSignalSpy updateAvailableSpy(&updater, &Updater::updateAvailable);


        WHEN("check for updates") {
            updater.check();

            THEN("update to version version 2.2.5 is available") {
                REQUIRE(updater.isUpdateAvailable());
                REQUIRE(updater.getLatestRelease()->getName() == "2.2.5");
                REQUIRE(updateAvailableSpy.count() == 1);
            }
        }
    }

    GIVEN("current version is 2.2.5 from June 2017") {
        Release currentRelease("2.2.5", QDate::fromString("2017-06-17", Qt::ISODate));
        Updater updater(querier, settings);
        updater.setCurrentRelease(&currentRelease);
        QSignalSpy updateAvailableSpy(&updater, &Updater::updateAvailable);

        WHEN("check for updates") {
            updater.check();

            THEN("no update is available") {
                REQUIRE(!updater.isUpdateAvailable());
                REQUIRE(updater.getLatestRelease()->getName().toStdString() == "2.2.5");
                REQUIRE(updateAvailableSpy.count() == 0);
            }
        }
    }

    GIVEN("current version is 2.95.0 from July 2017") {
        Release currentRelease("2.95.0", QDate::fromString("2017-07-01", Qt::ISODate));
        Updater updater(querier, settings);
        updater.setCurrentRelease(&currentRelease);
        QSignalSpy updateAvailableSpy(&updater, &Updater::updateAvailable);

        WHEN("check for updates") {
            updater.check();

            THEN("no update is available") {
                REQUIRE(!updater.isUpdateAvailable());
                REQUIRE(updater.getLatestRelease()->getName() == "2.95.0");
                REQUIRE(updateAvailableSpy.count() == 0);
            }
        }
    }
}

SCENARIO("check for beta updates") {
    FakeHttpClient fakeHttpClient;
    GithubReleaseQuerier querier(fakeHttpClient);
    ScopedScope scope;
    auto injector = getTestInjector(scope);
    Settings& settings = injector.create<Settings&>();
    settings.get(SettingKey::MAIN_UPDATE_CHANNEL).setValue(UpdateChannelStringer::toString(UpdateChannel::Beta));

    GIVEN("current version is 2.2.4 from April 2017") {
        Release currentRelease("2.2.4", QDate::fromString("2017-04-29", Qt::ISODate));
        Updater updater(querier, settings);
        updater.setCurrentRelease(&currentRelease);
        QSignalSpy updateAvailableSpy(&updater, &Updater::updateAvailable);


        WHEN("check for updates") {
            updater.check();

            THEN("update to version version 2.95.0 is available") {
                REQUIRE(updater.isUpdateAvailable());
                REQUIRE(updater.getLatestRelease()->getName().toStdString() == "2.95.0");
                REQUIRE(updateAvailableSpy.count() == 1);
            }
        }
    }

    GIVEN("current version is 2.95.0 from July 2017") {
        Release currentRelease("2.95.0", QDate::fromString("2017-07-16", Qt::ISODate));
        Updater updater(querier, settings);
        updater.setCurrentRelease(&currentRelease);
        QSignalSpy updateAvailableSpy(&updater, &Updater::updateAvailable);

        WHEN("check for updates") {
            updater.check();

            THEN("no update is available") {
                REQUIRE(!updater.isUpdateAvailable());
                REQUIRE(updater.getLatestRelease()->getName().toStdString() == "2.95.0");
                REQUIRE(updateAvailableSpy.count() == 0);
            }
        }
    }
}

SCENARIO("check for Continuous updates") {
    FakeHttpClient fakeHttpClient;
    GithubReleaseQuerier querier(fakeHttpClient);
    ScopedScope scope;
    auto injector = getTestInjector(scope);
    Settings& settings = injector.create<Settings&>();
    settings.get(SettingKey::MAIN_UPDATE_CHANNEL).setValue(UpdateChannelStringer::toString(UpdateChannel::Continuous));

    GIVEN("current version is 2.2.4 from April 2017") {
        Release currentRelease("2.2.4", QDate::fromString("2017-04-29", Qt::ISODate));
        Updater updater(querier, settings);
        updater.setCurrentRelease(&currentRelease);
        QSignalSpy updateAvailableSpy(&updater, &Updater::updateAvailable);

        WHEN("check for updates") {
            updater.check();

            THEN("update to version version Continuous is available") {
                REQUIRE(updater.isUpdateAvailable());
                REQUIRE(updater.getLatestRelease()->getName() == "Continuous");
                REQUIRE(updateAvailableSpy.count() == 1);
            }
        }
    }

    GIVEN("current version is 2.95.0 from day before latest continuous") {
        Release currentRelease("2.95.0", QDate::fromString("2017-07-14", Qt::ISODate));
        Updater updater(querier, settings);
        updater.setCurrentRelease(&currentRelease);
        QSignalSpy updateAvailableSpy(&updater, &Updater::updateAvailable);

        WHEN("check for updates") {
            updater.check();

            THEN("update to Continuous is available") {
                REQUIRE(updater.isUpdateAvailable());
                REQUIRE(updater.getLatestRelease()->getName().toStdString() == "Continuous");
                REQUIRE(updateAvailableSpy.count() == 1);
            }
        }
    }

    GIVEN("current version is 2.95.0 from day after latest continuous") {
        Release currentRelease("2.95.0", QDate::fromString("2017-07-16", Qt::ISODate));
        Updater updater(querier, settings);
        updater.setCurrentRelease(&currentRelease);
        QSignalSpy updateAvailableSpy(&updater, &Updater::updateAvailable);

        WHEN("check for updates") {
            updater.check();

            THEN("no update is available") {
                REQUIRE(!updater.isUpdateAvailable());
                REQUIRE(updater.getLatestRelease()->getName().toStdString() == "2.95.0");
                REQUIRE(updateAvailableSpy.count() == 0);
            }
        }
    }
}