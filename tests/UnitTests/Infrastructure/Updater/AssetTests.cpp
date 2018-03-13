#include <MellowPlayer/Infrastructure/Updater/Asset.hpp>
#include <catch/catch.hpp>

using namespace MellowPlayer::Infrastructure;

SCENARIO("asset validity can be tested")
{
    GIVEN("an asset with a valid asset name and an invalid url")
    {
        Asset asset("MellowPlayer-x86_64.AppImage", "");

        REQUIRE(asset.name() == "MellowPlayer-x86_64.AppImage");
        REQUIRE(asset.url() == "");

        WHEN("isValid is called")
        {
            bool isValid = asset.isValid();
            THEN("it returns False")
            {
                REQUIRE(!isValid);
            }
        }
    }

    GIVEN("an asset with an valid asset name and a valid url")
    {
        Asset asset("MellowPlayer.zip", "https://github.com/ColinDuquesnoy/"
                                        "MellowPlayer/releases/download/2.95.0/"
                                        "MellowPlayer.zip");
        WHEN("isValid is called")
        {
            bool isValid = asset.isValid();
            THEN("it returns False")
            {
                REQUIRE(!isValid);
            }
        }
    }

    GIVEN("an AppImage asset with a valid url")
    {
        Asset asset("MellowPlayer-x86_64.AppImage", "https://github.com/ColinDuquesnoy/MellowPlayer/releases/"
                                                    "download/2.95.0/MellowPlayer-x86_64.AppImage");
        WHEN("isValid is called")
        {
            bool isValid = asset.isValid();
            THEN("it returns True")
            {
                REQUIRE(isValid);
            }
        }
    }

    GIVEN("an dmg asset with a valid url")
    {
        Asset asset("MellowPlayer.dmg", "https://github.com/ColinDuquesnoy/"
                                        "MellowPlayer/releases/download/2.95.0/"
                                        "MellowPlayer.dmg");
        WHEN("isValid is called")
        {
            bool isValid = asset.isValid();
            THEN("it returns True")
            {
                REQUIRE(isValid);
            }
        }
    }

    GIVEN("an WindowsInstaller asset with a valid url")
    {
        Asset asset("MellowPlayer_Setup.exe", "https://github.com/ColinDuquesnoy/"
                                              "MellowPlayer/releases/download/"
                                              "2.95.0/MellowPlayer_Setup.exe");
        WHEN("isValid is called")
        {
            bool isValid = asset.isValid();
            THEN("it returns True")
            {
                REQUIRE(isValid);
            }
        }
    }
}

SCENARIO("Asset type is queryable")
{
    GIVEN("3 different asset types")
    {
        Asset appImageAsset("MellowPlayer-x86_64.AppImage", "https://github.com/ColinDuquesnoy/MellowPlayer/"
                                                            "releases/download/2.95.0/"
                                                            "MellowPlayer-x86_64.AppImage");
        Asset dmgAsset("MellowPlayer.dmg", "https://github.com/ColinDuquesnoy/"
                                           "MellowPlayer/releases/download/2.95.0/"
                                           "MellowPlayer.dmg");
        Asset windowsInstallerAsset("MellowPlayer_Setup.exe", "https://github.com/ColinDuquesnoy/"
                                                              "MellowPlayer/releases/download/2.95.0/"
                                                              "MellowPlayer_Setup.exe");

        WHEN("querying appImage asset type")
        {
            bool isAppImage = appImageAsset.isAppImage();
            bool isWindowsInstaller = appImageAsset.isWindowsInstaller();
            bool isDmg = appImageAsset.isDmg();

            THEN("isAppImage is True")
            {
                REQUIRE(isAppImage);
            }
            THEN("isWindowsInstaller is False")
            {
                REQUIRE(!isWindowsInstaller);
            }
            THEN("isDmg is False")
            {
                REQUIRE(!isDmg);
            }
        }

        WHEN("querying windowsInstaller asset type")
        {
            bool isAppImage = windowsInstallerAsset.isAppImage();
            bool isWindowsInstaller = windowsInstallerAsset.isWindowsInstaller();
            bool isDmg = windowsInstallerAsset.isDmg();

            THEN("isAppImage is FALSE")
            {
                REQUIRE(!isAppImage);
            }
            THEN("isWindowsInstaller is True")
            {
                REQUIRE(isWindowsInstaller);
            }
            THEN("isDmg is False")
            {
                REQUIRE(!isDmg);
            }
        }

        WHEN("querying dmg asset type")
        {
            bool isAppImage = dmgAsset.isAppImage();
            bool isWindowsInstaller = dmgAsset.isWindowsInstaller();
            bool isDmg = dmgAsset.isDmg();

            THEN("isAppImage is False")
            {
                REQUIRE(!isAppImage);
            }
            THEN("isWindowsInstaller is False")
            {
                REQUIRE(!isWindowsInstaller);
            }
            THEN("isDmg is True")
            {
                REQUIRE(isDmg);
            }
        }
    }
}