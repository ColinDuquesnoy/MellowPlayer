#include <catch/catch.hpp>
#include <fakeit/fakeit.hpp>
#include <MellowPlayer/Domain/UserScripts/IUserScript.hpp>
#include <MellowPlayer/Domain/UserScripts/IUserScriptFactory.hpp>
#include <MellowPlayer/Domain/UserScripts/UserScripts.hpp>
#include <MellowPlayer/Domain/Settings/ISettingsStore.hpp>
#include <MellowPlayer/Presentation/ViewModels/UserScripts/UserScriptsViewModel.hpp>
#include <UnitTests/Domain/UserScripts/FakeUserScript.hpp>
#include <UnitTests/Domain/Settings/FakeSettingsStore.hpp>

using namespace fakeit;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain::Tests;
using namespace MellowPlayer::Presentation;

SCENARIO("UserScriptsViewModelTests")
{
    Mock<IUserScriptFactory> factoryMock;
    When(Method(factoryMock, create)).AlwaysDo([]() -> IUserScript* {
       return new FakeUserScript;
    });
    QString serviceName = "fakeService";
    FakeSettingsStore settingsStore;

    GIVEN("settings are empty")
    {
        settingsStore.clear();
        UserScriptsViewModel viewModel(serviceName, factoryMock.get(), settingsStore);

        WHEN("creating a new UserScriptsViewModel")
        {
            THEN("list model count is 0")
            {
                REQUIRE(viewModel.model()->rowCount() == 0);
            }
        }

        AND_WHEN("add a new user script")
        {
            viewModel.add("name", "/path1");

            THEN("factory is called")
            {
                Verify(Method(factoryMock, create)).Exactly(1);

                AND_THEN("list model count is 1")
                {
                    REQUIRE(viewModel.model()->rowCount() == 1);
                }
            }
        }
    }

    GIVEN("settings have two entries")
    {
        QStringList paths;
        paths << "/path2";
        paths << "/path2";
        settingsStore.setValue("fakeService/userScriptPaths", paths);

        QStringList names;
        names << "DarkTheme";
        names << "AdBlocker";
        settingsStore.setValue("fakeService/userScriptNames", names);

        UserScriptsViewModel viewModel(serviceName, factoryMock.get(), settingsStore);

        WHEN("creating a new UserScriptsViewModel")
        {
            THEN("list model count is 2")
            {
                REQUIRE(viewModel.model()->rowCount() == 2);
            }
        }

        WHEN("checking for valid names")
        {
            THEN("DarkTheme is not valid")
            {
                REQUIRE(!viewModel.isValidName("DarkTheme"));
            }

            THEN("AdBlocker is not valid")
            {
                REQUIRE(!viewModel.isValidName("AdBlocker"));
            }

            THEN("Statistics is valid")
            {
                REQUIRE(viewModel.isValidName("Statistics"));
            }
        }
        
        WHEN("generating a unique name with DarkTheme")
        {
            auto name = viewModel.generateUniqueName("DarkTheme");

            THEN("name is DarkTheme2")
            {
                REQUIRE(name == "DarkTheme2");
            }
        }

        WHEN("generating a unique name with Foo")
        {
            auto name = viewModel.generateUniqueName("Foo");

            THEN("name is Foo")
            {
                REQUIRE(name == "Foo");
            }
        }

        AND_WHEN("remove a script")
        {
            viewModel.remove("AdBlocker");

            THEN("list model count is 1")
            {
                REQUIRE(viewModel.model()->rowCount() == 1);

                AND_THEN("settings paths count is 1") {
                    REQUIRE(settingsStore.value("fakeService/userScriptPaths", QVariant()).toStringList().count() == 1);
                }

                AND_THEN("settings names count is 1") {
                    REQUIRE(settingsStore.value("fakeService/userScriptNames", QVariant()).toStringList().count() == 1);
                }

                AND_THEN("AdBlocker is valid")
                {
                    REQUIRE(viewModel.isValidName("AdBlocker"));
                }
            }
        }
    }
}