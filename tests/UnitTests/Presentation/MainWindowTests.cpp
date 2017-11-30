#include <MellowPlayer/Presentation/MainWindow.hpp>
#include <catch/catch.hpp>
#include <UnitTests/Presentation/Qml/FakeContextProperties.hpp>
#include <UnitTests/Presentation/Qml/FakeQmlApplicationEngine.hpp>
#include <QtTest/QSignalSpy>

using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Presentation::Tests;

SCENARIO("MainWindowTests")
{
    GIVEN("A main window instance")
    {
        FakeContextProperties contextProperties;
        FakeQmlApplicationEngine qmlApplicationEngine;
        MainWindow mainWindow(contextProperties, qmlApplicationEngine);

        WHEN("Creating main window")
        {
            THEN("it is added to the context properties")
            {
                contextProperties.contains(mainWindow);
            }

            AND_THEN("window is not yet visible")
            {
                REQUIRE(!mainWindow.isVisible());
            }
        }

        WHEN("getting the name of the main window context property")
        {
            THEN("name is not empty")
            {
                REQUIRE(!mainWindow.name().isEmpty());
            }
        }

        WHEN("getting the context property as a QObject")
        {
            THEN("object is not null")
            {
                REQUIRE(mainWindow.asQObject() != nullptr);
            }
        }

        WHEN("loading window")
        {
            mainWindow.load();

            THEN("import path is defined")
            {
                REQUIRE(qmlApplicationEngine.importPathsCount() != 0);
            }

            AND_THEN("qmlApplicationEngine is loaded")
            {
                REQUIRE(qmlApplicationEngine.isLoaded());
            }
        }

        WHEN("showing the window")
        {
            QSignalSpy spy(&mainWindow, &MainWindow::visibleChanged);

            mainWindow.show();

            THEN("window is visible")
            {
                REQUIRE(mainWindow.isVisible());
            }

            AND_THEN("visibleChanged has been emitted")
            {
                REQUIRE(spy.count() == 1);
            }

            AND_WHEN("hiding the window")
            {
                mainWindow.hide();

                THEN("window is not visible anymore")
                {
                    REQUIRE(!mainWindow.isVisible());
                }

                AND_THEN("visibleChanged has been emitted once again")
                {
                    REQUIRE(spy.count() == 2);
                }
            }
        }
    }
}

