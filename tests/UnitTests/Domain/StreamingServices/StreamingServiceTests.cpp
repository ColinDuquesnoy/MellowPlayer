#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServiceScript.hpp>
#include <QtTest/QSignalSpy>
#include <catch/catch.hpp>

using namespace MellowPlayer::Domain;

TEST_CASE("StreamingServiceTest", "[UnitTest]")
{
    StreamingServiceMetadata serviceMetadata;

    SECTION("StreamingService.author")
    {
        serviceMetadata.author = "Colin Duquesnoy";
        StreamingService service(serviceMetadata);
        REQUIRE(service.author() == serviceMetadata.author);
    }

    SECTION("StreamingService.authorWebsite")
    {
        serviceMetadata.authorWebsite = "https://gitlab.com/ColinDuquesnoy";
        StreamingService service(serviceMetadata);
        REQUIRE(service.authorWebsite() == serviceMetadata.authorWebsite);
    }

    SECTION("StreamingService.name")
    {
        serviceMetadata.name = "Deezer";
        StreamingService service(serviceMetadata);
        REQUIRE(service.name() == serviceMetadata.name);
    }

    SECTION("StreamingService.getLogo_validImage")
    {
        serviceMetadata.logoPath = QString(PLUGINS_DIR) + QString("/deezer/logo.svg");
        StreamingService service(serviceMetadata);
#ifdef Q_OS_WIN
        REQUIRE(service.logo() == "file:" + serviceMetadata.logoPath);
#else
        REQUIRE(service.logo() == "file://" + serviceMetadata.logoPath);
#endif
    }

    SECTION("StreamingService.getLogo_nullImage")
    {
        serviceMetadata.logoPath = "";
        StreamingService service(serviceMetadata);
        REQUIRE(service.logo().isEmpty());
    }

    SECTION("StreamingService.url")
    {
        serviceMetadata.url = "https://deezer.com";
        StreamingService service(serviceMetadata);
        REQUIRE(service.url() == serviceMetadata.url);
    }

    SECTION("StreamingService.script")
    {
        serviceMetadata.script = "code";
        serviceMetadata.scriptPath = "path";
        StreamingService service(serviceMetadata);
        auto script = service.script();
        REQUIRE(script->code() == "code");
        REQUIRE(script->path() == "path");
    }

    SECTION("StreamingService.version")
    {
        serviceMetadata.version = "1.2";
        StreamingService service(serviceMetadata);
        REQUIRE(service.version() == serviceMetadata.version);
    }

    SECTION("StreamingService.equalityOperator")
    {
        StreamingServiceMetadata serviceMetadata1;
        serviceMetadata1.name = "Deezer";
        serviceMetadata1.url = "https://deezer.com";
        StreamingService service0(serviceMetadata1);

        StreamingServiceMetadata serviceMetadata2;
        serviceMetadata2.name = "Spotify";
        serviceMetadata2.url = "https://play.spotify.com";
        StreamingService service1(serviceMetadata2);

        StreamingService service2(serviceMetadata1);

        REQUIRE(service0 != service1);
        REQUIRE(service0 == service2);
    }
}
