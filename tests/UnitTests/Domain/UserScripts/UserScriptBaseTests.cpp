#include <catch/catch.hpp>
#include <MellowPlayer/Domain/UserScripts/UserScriptBase.hpp>
#include "FakeUserScript.hpp"

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain::Tests;

SCENARIO("UserScriptBaseTests")
{
    GIVEN("A fake user script")
    {
        FakeUserScript userScript;

        WHEN("in initial state")
        {
            THEN("path is empty")
            {
                REQUIRE(userScript.path().isEmpty());
            }

            THEN("name is empty")
            {
                REQUIRE(userScript.name().isEmpty());
            }

            THEN("code is empty")
            {
                REQUIRE(userScript.code().isEmpty());
            }
        }

        WHEN("setName")
        {
            userScript.setName("toto");
            THEN("name is set")
            {
                REQUIRE(userScript.name() == "toto");
            }
        }

        WHEN("fake load is called")
        {
            userScript.load("/a/path");

            THEN("path is set")
            {
                REQUIRE(userScript.path() == "/a/path");
            }

            THEN("code is set")
            {
                REQUIRE(userScript.code() == FAKE_USER_SCRIPT_CODE);
            }
        }
    }
}
