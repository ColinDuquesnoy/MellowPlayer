#include <MellowPlayer/Infrastructure/Updater/Release.hpp>
#include <catch/catch.hpp>

using namespace MellowPlayer::Infrastructure;

SCENARIO("releases validity can be tested")
{
    GIVEN("the current release")
    {
        const Release& currentRelease = Release::current();
        REQUIRE(currentRelease.url().isEmpty());

        WHEN("isValid is called")
        {
            bool isValid = currentRelease.isValid();

            THEN("it always returns True")
            {
                REQUIRE(isValid);
            }
        }
    }

    GIVEN("a release without a version and with a valid date")
    {
        Release release("", QDate::fromString("2117-07-15", Qt::ISODate));

        WHEN("isValid is called")
        {
            bool isValid = release.isValid();

            THEN("it returns False")
            {
                REQUIRE(!isValid);
            }
        }
    }

    GIVEN("a release with a version and no valid date")
    {
        Release release("2.95.0", QDate::fromString("xxxqzdqdz", Qt::ISODate));

        WHEN("isValid is called")
        {
            bool isValid = release.isValid();

            THEN("it returns False")
            {
                REQUIRE(!isValid);
            }
        }
    }

    GIVEN("a release with a version, a valid date, a description but no assets")
    {
        Release release("https://github.com/ColinDuquesnoy/MellowPlayer/releases/tag/2.95.0", "2.95.0", QDate::fromString("2117-07-15", Qt::ISODate),
                        AssetList());

        WHEN("isValid is called")
        {
            bool isValid = release.isValid();

            THEN("it returns False")
            {
                REQUIRE(!isValid);
            }
        }
    }

    GIVEN("a release with a version, a valid date, a description but not enough "
          "assets")
    {
        AssetList assets;
        assets << Asset("MellowPlayer.AppImage", "MellowPlayer.AppImage");
        assets << Asset("MellowPlayer.dmg", "MellowPlayer.dmg");
        // windows installer is missing.
        Release release("https://github.com/ColinDuquesnoy/MellowPlayer/releases/tag/2.95.0", "2.95.0", QDate::fromString("2117-07-15", Qt::ISODate),
                        assets);
        REQUIRE(release.assets().count() == 2);

        WHEN("isValid is called")
        {
            bool isValid = release.isValid();

            THEN("it returns False")
            {
                REQUIRE(!isValid);
            }
        }
    }

    GIVEN("a release with a version, a valid date, a description and all the "
          "required assets")
    {
        AssetList assets;
        assets << Asset("MellowPlayer.AppImage", "https://github.com/ColinDuquesnoy/MellowPlayer/releases/"
                                                 "tag/2.95.0/MellowPlayer.AppImage");
        assets << Asset("MellowPlayer.dmg", "https://github.com/ColinDuquesnoy/"
                                            "MellowPlayer/releases/tag/2.95.0/"
                                            "MellowPlayer.dmg");
        assets << Asset("MellowPlayer_Setup.exe", "https://github.com/ColinDuquesnoy/MellowPlayer/releases/"
                                                  "tag/2.95.0/MellowPlayer_Setup.exe");
        Release release("https://github.com/ColinDuquesnoy/MellowPlayer/releases/tag/2.95.0", "2.95.0", QDate::fromString("2017-07-15", Qt::ISODate),
                        assets);

        WHEN("isValid is called")
        {
            bool isValid = release.isValid();

            THEN("it returns True")
            {
                REQUIRE(isValid);
            }
        }
    }
}

SCENARIO("releases can be compared")
{
    GIVEN("a valid current release, a valid fake newer release and a valid fake "
          "older release")
    {
        const Release& currentRelease = Release::current();
        Release newerRelease("4.0.0", QDate::fromString("2117-07-15", Qt::ISODate));
        Release olderRelease("2.2.0", QDate::fromString("2017-05-15", Qt::ISODate));
        Release sameOlderRelease("2.2.0", QDate::fromString("2017-05-15", Qt::ISODate));

        REQUIRE(currentRelease.isValid());
        REQUIRE(newerRelease.isValid());
        REQUIRE(olderRelease.isValid());

        WHEN("newer release is compared to current release")
        {
            bool isInferior = newerRelease < currentRelease;
            bool isInferiorOrEqual = newerRelease <= currentRelease;
            bool isGreater = newerRelease > currentRelease;
            bool isGreaterOrEqual = newerRelease >= currentRelease;
            bool isEqual = newerRelease == currentRelease;
            bool isDifferent = newerRelease != currentRelease;

            THEN("not isInferior")
            {
                REQUIRE(!isInferior);
            }
            THEN("not isInferiorOrEqual")
            {
                REQUIRE(!isInferiorOrEqual);
            }
            THEN("isGreater")
            {
                REQUIRE(isGreater);
            }
            THEN("isGreaterOrEqual")
            {
                REQUIRE(isGreaterOrEqual);
            }
            THEN("not isEqual")
            {
                REQUIRE(!isEqual);
            }
            THEN("isDifferent")
            {
                REQUIRE(isDifferent);
            }
        }

        WHEN("older release is compared to current release")
        {
            bool isInferior = olderRelease < currentRelease;
            bool isInferiorOrEqual = olderRelease <= currentRelease;
            bool isGreater = olderRelease > currentRelease;
            bool isGreaterOrEqual = olderRelease >= currentRelease;
            bool isEqual = olderRelease == currentRelease;
            bool isDifferent = olderRelease != currentRelease;

            THEN("isInferior")
            {
                REQUIRE(isInferior);
            }
            THEN("isInferiorOrEqual")
            {
                REQUIRE(isInferiorOrEqual);
            }
            THEN("not isGreater")
            {
                REQUIRE(!isGreater);
            }
            THEN("not isGreaterOrEqual")
            {
                REQUIRE(!isGreaterOrEqual);
            }
            THEN("not isEqual")
            {
                REQUIRE(!isEqual);
            }
            THEN("isDifferent")
            {
                REQUIRE(isDifferent);
            }
        }

        WHEN("same releases are compared")
        {
            bool isInferior = olderRelease < sameOlderRelease;
            bool isInferiorOrEqual = olderRelease <= sameOlderRelease;
            bool isGreater = olderRelease > sameOlderRelease;
            bool isGreaterOrEqual = olderRelease >= sameOlderRelease;
            bool isEqual = olderRelease == sameOlderRelease;
            bool isDifferent = olderRelease != sameOlderRelease;

            THEN("not isInferior")
            {
                REQUIRE(!isInferior);
            }
            THEN("isInferiorOrEqual")
            {
                REQUIRE(isInferiorOrEqual);
            }
            THEN("not isGreater")
            {
                REQUIRE(!isGreater);
            }
            THEN("isGreaterOrEqual")
            {
                REQUIRE(isGreaterOrEqual);
            }
            THEN("isEqual")
            {
                REQUIRE(isEqual);
            }
            THEN("not isDifferent")
            {
                REQUIRE(!isDifferent);
            }
        }
    }
}
