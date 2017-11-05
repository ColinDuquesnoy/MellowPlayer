#include <MellowPlayer/Domain/Plugins/PluginMetadata.hpp>
#include <catch.hpp>
#include <QtTest/QSignalSpy>

using namespace MellowPlayer::Domain;

SCENARIO("PluginMetadataTests")
{
    GIVEN("Empty metadata")
    {
        PluginMetadata metadata;

        WHEN("updateName")
        {
            QSignalSpy spy(&metadata, &PluginMetadata::nameChanged);

            metadata.updateName("foo");

            THEN("getName return new name")
            {
                REQUIRE(metadata.name() == "foo");
            }

            AND_THEN("nameChanged signal is emitted")
            {
                REQUIRE(spy.count() == 1);
            }
        }

        WHEN("updateAuthor")
        {
            QSignalSpy spy(&metadata, &PluginMetadata::authorChanged);

            metadata.updateAuthor("foo");

            THEN("getAuthor return new author")
            {
                REQUIRE(metadata.author() == "foo");
            }

            AND_THEN("authorChanged signal is emitted")
            {
                REQUIRE(spy.count() == 1);
            }
        }

        WHEN("updateAuthorUrl")
        {
            QSignalSpy spy(&metadata, &PluginMetadata::authorUrlChanged);

            metadata.updateAuthorUrl("foo");

            THEN("getAuthorUrl return new authorUrl")
            {
                REQUIRE(metadata.authorUrl() == "foo");
            }

            AND_THEN("authorUrlChanged signal is emitted")
            {
                REQUIRE(spy.count() == 1);
            }
        }

        WHEN("updateLogo")
        {
            QSignalSpy spy(&metadata, &PluginMetadata::logoChanged);

            metadata.updateLogo("foo");

            THEN("getLogo return new logo")
            {
                REQUIRE(metadata.logo() == "foo");
            }

            AND_THEN("logoChanged signal is emitted")
            {
                REQUIRE(spy.count() == 1);
            }
        }


        WHEN("updateVersion")
        {
            QSignalSpy spy(&metadata, &PluginMetadata::versionChanged);

            metadata.updateVersion("foo");

            THEN("getVersion return new version")
            {
                REQUIRE(metadata.version() == "foo");
            }

            AND_THEN("versionChanged signal is emitted")
            {
                REQUIRE(spy.count() == 1);
            }
        }
    }
}
