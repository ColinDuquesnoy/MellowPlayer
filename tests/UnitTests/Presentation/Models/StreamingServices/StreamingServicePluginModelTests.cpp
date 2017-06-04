#include <catch.hpp>
#include <MellowPlayer/Presentation/Models/StreamingServices/StreamingServicesModel.hpp>
#include <QtTest/QSignalSpy>
#include "DI.hpp"

USE_MELLOWPLAYER_NAMESPACE(Application)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

TEST_CASE("StreamingServiceModelTests", "[UnitTest]") {
    ScopedScope scope;
    auto injector = getTestInjector(scope);
    Players& players = injector.create<Players&>();
    StreamingServices& streamingServices = injector.create<StreamingServices&>();
    streamingServices.load();
    QSettingsProvider settingsProvider;
    StreamingService& service1 = *streamingServices.getAll()[0];
    StreamingService& service2 = *streamingServices.getAll()[1];

    StreamingServiceModel model(service1, settingsProvider, players);
    StreamingServiceModel sameModel(service1, settingsProvider, players);
    StreamingServiceModel model2(service2, settingsProvider, players);

    SECTION("basic properties") {
        REQUIRE(model.getColor() == service1.getColor());
        REQUIRE(model.getLogo() == service1.getLogo());
        REQUIRE(model.getName() == service1.getName());
        REQUIRE(model.getPlayer() == players.get(service1.getName()).get());
        REQUIRE(model.getUrl() == service1.getUrl());
    }

    SECTION("equality operator") {
        REQUIRE(model != model2);
        REQUIRE(model == sameModel);
    }

    SECTION("set custom url") {
        QSignalSpy spy(&model, SIGNAL(urlChanged(const QString&)));
        model.setUrl("https://deezer.com/news");
        REQUIRE(model.getUrl() == "https://deezer.com/news");
        REQUIRE(spy.count() == 1);
    }
}