#include <catch/catch.hpp>
#include <fakeit/fakeit.hpp>
#include <MellowPlayer/Domain/UserScripts/IUserScript.hpp>
#include <MellowPlayer/Domain/UserScripts/IUserScriptFactory.hpp>
#include <MellowPlayer/Domain/UserScripts/UserScripts.hpp>
#include <MellowPlayer/Domain/Settings/ISettingsStore.hpp>
#include <UnitTests/Domain/Settings/FakeSettingsStore.hpp>

using namespace fakeit;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain::Tests;

#ifdef QT_DEBUG
SCENARIO("UserScriptsTests")
{
    Mock<IUserScript> userScriptMock;
    When(Method(userScriptMock, path)).AlwaysReturn("/path");
    When(Method(userScriptMock, code)).AlwaysReturn("code");
    When(Method(userScriptMock, name)).AlwaysReturn("name");
    Fake(Method(userScriptMock, setName));
    Fake(Method(userScriptMock, removeFile));
    When(Method(userScriptMock, load)).AlwaysReturn(true);
    When(Method(userScriptMock, import)).AlwaysReturn(true);
    Fake(Dtor(userScriptMock));
    IUserScript& userScript = userScriptMock.get();

    Mock<IUserScriptFactory> factoryMock;
    When(Method(factoryMock, create)).AlwaysReturn(&userScript);

    QString serviceName = "fakeService";
    FakeSettingsStore settingsStore;
    settingsStore.clear();


    GIVEN("empty settings")
    {
        UserScripts userScripts(serviceName, factoryMock.get(), settingsStore);

        WHEN("get count")
        {
            THEN("count is zero")
            {
                REQUIRE(userScripts.count() == 0);
            }
        }

        WHEN("add script")
        {
            userScripts.add("name", "/path");

            THEN("factory is called")
            {
                Verify(Method(factoryMock, create)).Exactly(1);

                AND_THEN("name is set")
                {
                    Verify(Method(userScriptMock, setName)).Exactly(1);

                    AND_THEN("import is called")
                    {
                        Verify(Method(userScriptMock, import)).Exactly(1);

                        AND_THEN("count is 1")
                        {
                            REQUIRE(userScripts.count() == 1);

                            AND_THEN("settings are saved")
                            {
                                REQUIRE(settingsStore.value("fakeService/userScriptPaths", QStringList()).toStringList().count() == 1);
                                REQUIRE(settingsStore.value("fakeService/userScriptNames", QStringList()).toStringList().count() == 1);
                            }
                        }
                    }
                }
            }

            AND_WHEN("remove is called")
            {
                userScripts.remove("name");

                THEN("file is removed")
                {
                    Verify(Method(userScriptMock, removeFile)).Exactly(1);
                }

                THEN("count is zero")
                {
                    REQUIRE(userScripts.count() == 0);

                    AND_THEN("settings paths count is 0") {
                        REQUIRE(settingsStore.value("fakeService/userScriptPaths", QVariant()).toStringList().count() == 0);
                    }

                    AND_THEN("settings names count is 0") {
                        REQUIRE(settingsStore.value("fakeService/userScriptNames", QVariant()).toStringList().count() == 0);
                    }
                }
            }
        }
    }

    GIVEN("2 scripts in settings")
    {
        QStringList paths;
        paths << "/path2";
        paths << "/path2";
        settingsStore.setValue("fakeService/userScriptPaths", paths);

        QStringList names;
        names << "name1";
        names << "name2";
        settingsStore.setValue("fakeService/userScriptNames", names);

        WHEN("creating a UserScripts instance")
        {
            UserScripts userScripts(serviceName, factoryMock.get(), settingsStore);

            THEN("factory called once")
            {
                Verify(Method(factoryMock, create)).Exactly(2);

                AND_THEN("name is set")
                {
                    Verify(Method(userScriptMock, setName)).Exactly(2);

                    AND_THEN("load is called")
                    {
                        Verify(Method(userScriptMock, load)).Exactly(2);

                        AND_THEN("count is 2")
                        {
                            REQUIRE(userScripts.count() == 2);
                        }
                    }
                }
            }
        }

    }
}
#endif
