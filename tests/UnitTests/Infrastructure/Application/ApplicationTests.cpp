#include <catch/catch.hpp>
#include <MellowPlayer/Infrastructure/BuildConfig.hpp>
#include <MellowPlayer/Infrastructure/Application/Application.hpp>
#include <QtTest/QSignalSpy>
#include "UnitTests/Infrastructure/Application/FakeQtApplication.hpp"
#include <UnitTests/Presentation/Qml/FakeContextProperties.hpp>

using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Infrastructure::Tests;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Presentation::Tests;

SCENARIO("Application tests")
{
    GIVEN("An IQtApplication mock")
    {
        FakeQtApplication qtApplication;
        Application application(qtApplication);

        WHEN("qtApplication.commitDataRequest is emitted, application.commitDataRequest is emitted too")
        {
            QSignalSpy spy(&application, &IApplication::commitDataRequest);
            emit qtApplication.commitDataRequest();
            REQUIRE(spy.count() == 1);
        }

        WHEN("initializing the application")
        {
            QSignalSpy spy(&application, &IApplication::initialized);
            application.initialize();

            AND_THEN("initialized signal is emitted")
            {
                REQUIRE(spy.count() == 1);
            }
        }

        WHEN("running the application")
        {
            QSignalSpy spy(&application, &IApplication::started);
            application.run();

            THEN("Qt Application is running")
            {
                REQUIRE(qtApplication.isRunning);
            }

            THEN("started signal is emitted")
            {
                REQUIRE(spy.count() == 1);
            }
        }

        WHEN("quit the application")
        {
            application.quit();

            THEN("call exit on qtApplication with valid exit code 0")
            {
                REQUIRE(qtApplication.requestedExitCode == 0);
            }
        }

        WHEN("restart the application")
        {
            application.restart();

            THEN("call exit on qtApplication with valid exit code 0")
            {
                REQUIRE(qtApplication.requestedExitCode == 0);
            }
        }

        WHEN("restoreWindow is called")
        {
            QSignalSpy spy(&application, &IApplication::restoreWindowRequest);
            application.restoreWindow();

            THEN("restoreWindowRequest is emitted")
            {
                REQUIRE(spy.count() == 1);
            }
        }
    }
}
