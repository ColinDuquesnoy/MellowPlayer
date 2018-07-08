#include <MellowPlayer/Domain/StreamingServices/StreamingServiceMetadata.hpp>
#include <catch/catch.hpp>

using namespace MellowPlayer::Domain;
using namespace std;

TEST_CASE("StreamingServiceMetadataTests", "[UnitTest]")
{
    SECTION("StreamingService.DefaultCtor")
    {
        StreamingServiceMetadata metadata;

        REQUIRE(metadata.author == "");
        REQUIRE(metadata.authorWebsite == "");
        REQUIRE(metadata.logoPath == "");
        REQUIRE(metadata.name == "");
        REQUIRE(metadata.url == "");
        REQUIRE(metadata.script == "");
        REQUIRE(metadata.version == "");
    }

    SECTION("StreamingService.isValid")
    {
        StreamingServiceMetadata metadata;

        REQUIRE(!metadata.isValid());
        metadata.url = "https://deezer.com";
        REQUIRE(!metadata.isValid());
        metadata.name = "Deezer";
        REQUIRE(!metadata.isValid());
        metadata.script = "function test() { }";
        REQUIRE(metadata.isValid());
    }

    SECTION("StreamingService.operator==")
    {
        StreamingServiceMetadata metadata;
        StreamingServiceMetadata metadata1;

        REQUIRE(metadata == metadata1);
        metadata.url = "https://deezer.com";
        REQUIRE(metadata != metadata1);
        metadata.url = "";
        metadata.name = "Deezer";
        REQUIRE(metadata != metadata1);
    }
}