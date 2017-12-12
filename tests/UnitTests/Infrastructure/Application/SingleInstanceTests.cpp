#include <MellowPlayer/Infrastructure/Application/SingleInstance.hpp>
#include <UnitTests/Infrastructure/Application/FakeApplication.hpp>
#include <UnitTests/Infrastructure/Application/FakeQtApplication.hpp>
#include <catch/catch.hpp>
#include <QtTest/QSignalSpy>
#include <Mocks/PlayerMock.hpp>
#include <UnitTests/Infrastructure/Network/FakeLocalSocket.hpp>
#include <UnitTests/Infrastructure/Network/FakeLocalServer.hpp>
#include <Lib/Mocks/FakeCommnandLineArguments.hpp>
#include <QtTest/qtestsystem.h>

using namespace std;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Infrastructure::Tests;

SCENARIO("SingleInstance tests")
{
    FakeLocalSocketFactory primaryLocalSocketFactory;
    FakeLocalServerFactory primaryLocalServerFactory;

    FakeLocalSocketFactory secondaryLocalSocketFactory;
    FakeLocalServerFactory secondaryLocalServerFactory;
    FakeCommandLineArguments commandLineArguments;

    auto playerMock = PlayerMock::get();

    GIVEN("Two SingleInstance application")
    {
        auto primaryDecorated = make_shared<FakeApplication>();
        FakeQtApplication primaryQtApplication;
        SingleInstance primaryInstance(primaryDecorated,
                                       primaryQtApplication,
                                       playerMock.get(),
                                       commandLineArguments,
                                       primaryLocalServerFactory,
                                       primaryLocalSocketFactory);

        auto secondaryDecorated = make_shared<FakeApplication>();
        FakeQtApplication secondaryQtApplication;
        SingleInstance secondaryInstance(secondaryDecorated,
                                         secondaryQtApplication,
                                         playerMock.get(),
                                         commandLineArguments,
                                         secondaryLocalServerFactory,
                                         secondaryLocalSocketFactory);

        WHEN("I initialize the first application")
        {
            QSignalSpy initSpy(&primaryInstance, &IApplication::initialized);
            primaryInstance.initialize();

            THEN("application is primary")
            {
                REQUIRE(primaryInstance.isPrimary());
            }

            AND_THEN("decorated is initialized too")
            {
                REQUIRE(primaryDecorated->isInitialized);
            }

            AND_THEN("initialized signal has been emitted")
            {
                REQUIRE(initSpy.count() == 1);
            }

            AND_WHEN("I run the first application")
            {
                primaryInstance.run();

                THEN("decorated is running")
                {
                    REQUIRE(primaryDecorated->isRunning);
                }

                AND_THEN("server is listening")
                {
                    REQUIRE(primaryLocalServerFactory.lastServerCreated->isListening());
                }

                FakeLocalServer* primaryServer = primaryLocalServerFactory.lastServerCreated;
                emit primaryServer->newConnection();
                FakeLocalSocket* secondarySocket = primaryServer->newConnectionSocket;

                AND_WHEN("the first application receive a 'play-pause' action request from a secondary application")
                {
                    secondarySocket->data = "play-pause";
                    emit secondarySocket->readyRead();

                    THEN("it toggle play/pause on the current player")
                    {
                        Verify(Method(playerMock, togglePlayPause)).Once();
                    }
                }

                AND_WHEN("the first application receive a 'next' action request from a secondary application")
                {
                    secondarySocket->data = "next";
                    emit secondarySocket->readyRead();

                    THEN("it skips to the next song")
                    {
                        Verify(Method(playerMock, next)).Once();
                    }
                }

                AND_WHEN("the first application receive a 'previous' action request from a secondary application")
                {
                    secondarySocket->data = "previous";
                    emit secondarySocket->readyRead();

                    THEN("it skips to the previous songs")
                    {
                        Verify(Method(playerMock, previous)).Once();
                    }
                }

                AND_WHEN("the first application receive a 'restore-window' action request from a secondary application")
                {
                    secondarySocket->data = "restore-windowe";
                    emit secondarySocket->readyRead();

                    THEN("it restores the main window")
                    {
                        REQUIRE(primaryDecorated->restoreWindowRequested);
                    }
                }

                AND_WHEN("the first application receive a 'toggle-favorite' action request from a secondary application")
                {
                    secondarySocket->data = "toggle-favorite";
                    emit secondarySocket->readyRead();

                    THEN("it toggle favorite on the current songs")
                    {
                        Verify(Method(playerMock, toggleFavoriteSong)).Once();
                    }
                }
            }

            AND_WHEN("I initialize the second application")
            {
                QSignalSpy secondaryInitSpy(&primaryInstance, &IApplication::initialized);
                secondaryInstance.initialize();

                THEN("the second application is not primary")
                {
                    REQUIRE(!secondaryInstance.isPrimary());
                }

                AND_THEN("decorated is not initialized")
                {
                    REQUIRE(!secondaryDecorated->isInitialized);
                }

                AND_THEN("initialized signal has not been emitted")
                {
                    REQUIRE(secondaryInitSpy.count() == 0);
                }

                AND_WHEN("I run the second application")
                {
                    secondaryInstance.run();

                    THEN("decorated is not running")
                    {
                        REQUIRE(!secondaryDecorated->isRunning);
                    }

                    AND_THEN("socket is connected to server")
                    {
                        REQUIRE(secondaryLocalSocketFactory.lastSocketCreated->isConnected);
                    }

                    AND_THEN("qt event loop is running")
                    {
                        REQUIRE(secondaryQtApplication.isRunning);
                    }

                    AND_WHEN("it is connected to the primary instance")
                    {
                        emit secondaryLocalSocketFactory.lastSocketCreated->connected();

                        THEN("it tells the primary application to restore the main window")
                        {
                            REQUIRE(secondaryLocalSocketFactory.lastSocketCreated->writtenData == "restore-window\n");
                        }

                        QTest::qWait(100);

                        AND_THEN("it quits the application with exit code 1")
                        {
                            REQUIRE(secondaryQtApplication.requestedExitCode == 1);
                        }
                    }

                    AND_WHEN("commandLineArguments contains 'play-pause' action")
                    {
                        commandLineArguments.setPlayPauseRequested(true);
                        emit secondaryLocalSocketFactory.lastSocketCreated->connected();

                        THEN("it tells the primary application toggle play/pause on the current player")
                        {
                            REQUIRE(secondaryLocalSocketFactory.lastSocketCreated->writtenData == "play-pause\n");
                        }
                    }

                    AND_WHEN("commandLineArguments contains 'next' action")
                    {
                        commandLineArguments.setNextRequested(true);
                        emit secondaryLocalSocketFactory.lastSocketCreated->connected();

                        THEN("it tells the primary application to skipts to the next song")
                        {
                            REQUIRE(secondaryLocalSocketFactory.lastSocketCreated->writtenData == "next\n");
                        }
                    }

                    AND_WHEN("commandLineArguments contains 'previous' action")
                    {
                        commandLineArguments.setPreviousRequested(true);
                        emit secondaryLocalSocketFactory.lastSocketCreated->connected();

                        THEN("it tells the primary application to skips to the previous song")
                        {
                            REQUIRE(secondaryLocalSocketFactory.lastSocketCreated->writtenData == "previous\n");
                        }
                    }

                    AND_WHEN("it failed to connect to the primary instance")
                    {
                        emit secondaryLocalSocketFactory.lastSocketCreated->error();

                        QTest::qWait(100);

                        THEN("it quits the application with exit code 2")
                        {
                            REQUIRE(secondaryQtApplication.requestedExitCode == 2);
                        }
                    }
                }
            }
        }
    }
}
