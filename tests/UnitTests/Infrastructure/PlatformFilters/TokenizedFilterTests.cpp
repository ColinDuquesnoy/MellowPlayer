#include <catch/catch.hpp>
#include <MellowPlayer/Infrastructure/PlatformFilters/TokenizedFilters.hpp>
#include <QtCore/QList>

using namespace MellowPlayer::Infrastructure;

SCENARIO("TokenizedFilterTests")
{
    GIVEN("a TokenizedFilterTests instantiated with filter=\"Windows,Linux,OSX\"")
    {
        QString filtersString = "Windows-Linux-OSX";
        TokenizedFilters tokenizedFilters(filtersString);

        WHEN("iterating on the filters")
        {
            QList<Filter> filters;
            for(auto filter: tokenizedFilters)
                filters.append(filter);

            THEN("filters count is 3")
            {
                REQUIRE(filters.count() == 3);
            }

            THEN("filters are in the correct order")
            {
                QList<Filter> expectedFilters = {
                        Filter::Windows,
                        Filter::Linux,
                        Filter::OSX
                };

                REQUIRE(filters == expectedFilters);
            }
        }

        WHEN("converting the tokens to a string")
        {
            THEN("we get the original string back")
            {
                REQUIRE(tokenizedFilters.join().toStdString() == filtersString.toStdString());
            }
        }
    }
}
