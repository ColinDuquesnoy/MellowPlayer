#include <MellowPlayer/Infrastructure/CommandLineArguments/ICommandLineArguments.hpp>
#include <MellowPlayer/Infrastructure/Application/WithCommandLineArguments.hpp>
#include <Mocks/FakeCommnandLineArguments.hpp>
#include <Lib/TestMacros.hpp>
#include "FakeApplication.hpp"

using namespace std;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Infrastructure::Tests;

SCENARIO("WithCommandLineArgumentsTests")
{
    GIVEN("A CommandLineArguments application")
    {
        auto decorated = make_shared<FakeApplication>();
        FakeCommandLineArguments commandLineArguments;

        WithCommandLineArguments commandLineArgumentsApp(decorated, commandLineArguments);

        WHEN("initialize is called")
        {
            commandLineArgumentsApp.initialize();

            THEN("command line arguments are parsed")
            {
                REQUIRE(commandLineArguments.parsed);
            }

            AND_THEN("decorated application is initialized too")
            {
                REQUIRE(decorated->isInitialized);
            }
        }
    }
}
