#include <MellowPlayer/Application/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingServiceScript.hpp>
#include <Mocks/SettingsProviderMock.hpp>
#include <QtTest/QSignalSpy>
#include <catch.hpp>

using namespace MellowPlayer::Application;

TEST_CASE("StreamingServiceTest", "[UnitTest]")
{
    StreamingServiceMetadata serviceMetadata;

    SECTION("StreamingService.getAuthor")
    {
        serviceMetadata.author = "Colin Duquesnoy";
        StreamingService service(serviceMetadata);
        REQUIRE(service.getAuthor() == serviceMetadata.author);
    }

    SECTION("StreamingService.getAuthorWebsite")
    {
        serviceMetadata.authorWebsite = "https://gitlab.com/ColinDuquesnoy";
        StreamingService service(serviceMetadata);
        REQUIRE(service.getAuthorWebsite() == serviceMetadata.authorWebsite);
    }

    SECTION("StreamingService.getName")
    {
        serviceMetadata.name = "Deezer";
        StreamingService service(serviceMetadata);
        REQUIRE(service.getName() == serviceMetadata.name);
    }

    SECTION("StreamingService.getLogo_validImage")
    {
        serviceMetadata.logoPath = QString(PLUGINS_DIR) + QString("/deezer/logo.svg");
        StreamingService service(serviceMetadata);
#ifdef Q_OS_WIN
        REQUIRE(service.getLogo() == "file:" + serviceMetadata.logoPath);
#else
        REQUIRE(service.getLogo() == "file://" + serviceMetadata.logoPath);
#endif
    }

    SECTION("StreamingService.getLogo_nullImage")
    {
        serviceMetadata.logoPath = "";
        StreamingService service(serviceMetadata);
        REQUIRE(service.getLogo().isEmpty());
    }

    SECTION("StreamingService.getUrl")
    {
        serviceMetadata.url = "https://deezer.com";
        StreamingService service(serviceMetadata);
        REQUIRE(service.getUrl() == serviceMetadata.url);
    }

    SECTION("StreamingService.getScript")
    {
        serviceMetadata.script = "code";
        serviceMetadata.scriptPath = "path";
        StreamingService service(serviceMetadata);
        auto script = service.getScript();
        REQUIRE(script->getCode() == "code");
        REQUIRE(script->getPath() == "path");
    }

    SECTION("StreamingService.getVersion")
    {
        serviceMetadata.version = "1.2";
        StreamingService service(serviceMetadata);
        REQUIRE(service.getVersion() == serviceMetadata.version);
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
