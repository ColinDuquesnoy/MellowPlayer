#include <MellowPlayer/Infrastructure/CommandLineArguments/ICommandLineArguments.hpp>
#include <MellowPlayer/Infrastructure/Application/WithCommandLineArguments.hpp>
#include <Mocks/CommnandLineArgumentsMock.hpp>
#include <Lib/TestMacros.hpp>
#include "ApplicationMock.hpp"

using namespace testing;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Infrastructure::Tests;

SCENARIO("WithCommandLineArgumentsTests")
{
    GIVEN("A CommandLineArguments application")
    {
        NiceMock<ApplicationMock> application;
        NiceMock<CommandLineArgumentsMock> commandLineArguments;

        WithCommandLineArguments commandLineArgumentsApp(application, commandLineArguments);

        WHEN("initialize is called")
        {
            THEN("command line arguments are parsed")
            {
                EXPECT_CALL(commandLineArguments, parse()).Times(1);
            }

            AND_THEN("decorated application is initialized too")
            {
                EXPECT_CALL(application, initialize()).Times(1);
            }

            commandLineArgumentsApp.initialize();
        }
    }
}
