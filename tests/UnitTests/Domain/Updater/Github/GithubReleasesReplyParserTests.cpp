#include "Utils/Helpers.hpp"
#include <MellowPlayer/Domain/Updater/Release.hpp>
#include <MellowPlayer/Domain/Updater/Github/GithubReleasesReplyParser.hpp>
#include <QtTest/QSignalSpy>
#include <catch.hpp>

using namespace MellowPlayer::Domain;

SCENARIO("parse github reply")
{
    GIVEN("a reply parser and a spy object")
    {
        GithubReleasesReplyParser parser;
        QSignalSpy spy(&parser, &GithubReleasesReplyParser::ready);
        REQUIRE(spy.count() == 0);

        WHEN("parsing a valid github releases reply data without stopping")
        {
            parser.parse(getValidReplyData());

            THEN("ready signal has been called 4 times")
            {
                REQUIRE(spy.count() == 4);
            }
        }

        WHEN("parsing a valid github releases reply data and stopping after the "
             "third release")
        {
            int count = 0;
            QObject::connect(&parser, &GithubReleasesReplyParser::ready, [&]() {
                ++count;
                if (count == 3)
                    parser.stop();
            });
            parser.parse(getValidReplyData());

            THEN("ready signal has been called 3 times")
            {
                REQUIRE(spy.count() == 3);
            }
        }
    }
}
