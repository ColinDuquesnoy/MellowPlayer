#include <MellowPlayer/Presentation/ViewModels/MainWindowViewModel.hpp>
#include <catch/catch.hpp>
#include <UnitTests/Presentation/Qml/FakeContextProperties.hpp>
#include <UnitTests/Presentation/Qml/FakeQmlApplicationEngine.hpp>
#include <QtTest/QSignalSpy>

using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Presentation::Tests;

SCENARIO("MainWindowViewModelTests")
{
    GIVEN("A main window instance")
    {
        FakeContextProperties contextProperties;
        FakeQmlApplicationEngine qmlApplicationEngine;
        MainWindowViewModel mainWindow(contextProperties, qmlApplicationEngine);

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
            QSignalSpy spy(&mainWindow, &MainWindowViewModel::visibleChanged);

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

        WHEN("I call requestQuit")
        {
            QSignalSpy spy(&mainWindow, &MainWindowViewModel::quitRequest);
            mainWindow.requestQuit();

            THEN("quitRequest signal is emitted")
            {
                REQUIRE(spy.count() == 1);
            }
        }
    }
}

