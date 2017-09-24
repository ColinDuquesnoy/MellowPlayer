#include <catch.hpp>
#include <fakeit.hpp>
#include <MellowPlayer/Application/UserScripts/IUserScript.hpp>
#include <MellowPlayer/Application/UserScripts/IUserScriptFactory.hpp>
#include <MellowPlayer/Application/UserScripts/UserScripts.hpp>
#include <MellowPlayer/Application/Settings/ISettingsProvider.hpp>
#include <MellowPlayer/Presentation/ViewModels/UserScripts/UserScriptsViewModel.hpp>
#include <UnitTests/Application/UserScripts/FakeUserScript.hpp>
#include <Mocks/SettingsProviderMock.hpp>

using namespace fakeit;
using namespace MellowPlayer::Application;
using namespace MellowPlayer::Application::Tests;
using namespace MellowPlayer::Presentation;

SCENARIO("UserScriptsViewModelTests")
{
    Mock<IUserScriptFactory> factoryMock;
    When(Method(factoryMock, create)).AlwaysDo([]() -> IUserScript* {
       return new FakeUserScript;
    });
    QString serviceName = "fakeService";
    auto settingsProviderMock = SettingsProviderMock::get();
    ISettingsProvider& settingsProvider = settingsProviderMock.get();

    GIVEN("settings are empty")
    {
        settingsProvider.clear();
        UserScriptsViewModel viewModel(serviceName, factoryMock.get(), settingsProvider);

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
        settingsProvider.setValue("fakeService/userScriptPaths", paths);

        QStringList names;
        names << "name1";
        names << "name2";
        settingsProvider.setValue("fakeService/userScriptNames", names);

        UserScriptsViewModel viewModel(serviceName, factoryMock.get(), settingsProvider);

        WHEN("creating a new UserScriptsViewModel")
        {
            THEN("list model count is 2")
            {
                REQUIRE(viewModel.model()->rowCount() == 2);
            }
        }

        WHEN("checking for valid names")
        {
            THEN("name1 is not valid")
            {
                REQUIRE(!viewModel.isValidName("name1"));
            }

            THEN("name2 is not valid")
            {
                REQUIRE(!viewModel.isValidName("name2"));
            }

            THEN("name3 is valid")
            {
                REQUIRE(viewModel.isValidName("name3"));
            }
        }

        AND_WHEN("remove a script")
        {
            viewModel.remove("name2");

            THEN("list model count is 1")
            {
                REQUIRE(viewModel.model()->rowCount() == 1);

                AND_THEN("settings paths count is 1") {
                    REQUIRE(settingsProvider.value("fakeService/userScriptPaths").toStringList().count() == 1);
                }

                AND_THEN("settings names count is 1") {
                    REQUIRE(settingsProvider.value("fakeService/userScriptNames").toStringList().count() == 1);
                }

                AND_THEN("name2 is valid")
                {
                    REQUIRE(viewModel.isValidName("name2"));
                }
            }
        }
    }
}