#include <MellowPlayer/Infrastructure/System/File.hpp>
#include <catch.hpp>

using namespace MellowPlayer::Infrastructure;

SCENARIO("FileTests")
{
    GIVEN("A file that exsits" )
    {
        File file(":/MellowPlayer/Domain/PluginTemplate/integration.js");
        REQUIRE(file.exists());

        WHEN("opening file")
        {
            bool isOpen = file.open();

            THEN("file is open")
            {
                REQUIRE(isOpen);
            }

            AND_THEN("file content is not empty")
            {
                REQUIRE(!file.content().isEmpty());
            }
        }
    }
}
