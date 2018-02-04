#include <catch/catch.hpp>
#include <UnitTests/Domain/UserScripts/FakeUserScript.hpp>
#include <MellowPlayer/Presentation/ViewModels/UserScripts/UserScriptViewModel.hpp>
#include <QtTest/QSignalSpy>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain::Tests;
using namespace MellowPlayer::Presentation;

SCENARIO("UserScritViewModelTests")
{
    GIVEN("a fake user script")
    {
        FakeUserScript userScript;
        userScript.setName("name");
        userScript.import("/path");

        WHEN("a view model is created") {
            UserScriptViewModel viewModel(userScript);
            QSignalSpy spy(&viewModel, &UserScriptViewModel::nameChanged);

            THEN("code is the same as the user script code")
            {
                REQUIRE(viewModel.code() == userScript.code());
            }

            THEN("name is the same as the user script name")
            {
                REQUIRE(viewModel.name() == userScript.name());
            }

            THEN("path is the same as the user script path")
            {
                REQUIRE(viewModel.path() == userScript.path());
            }

            AND_WHEN("another name is set")
            {
                viewModel.setName("Another name");

                THEN("new name is saved")
                {
                    REQUIRE(viewModel.name() == "Another name");

                    AND_THEN("nameChanged signal is emitted")
                    {
                        REQUIRE(spy.count() == 1);
                    }
                }
            }
        }

    }
}
