#include <catch.hpp>
#include <MellowPlayer/Presentation.hpp>
#include <QtTest/QSignalSpy>
#include "DI.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

TEST_CASE("StreamingServiceModelTests") {
    ScopedScope scope;
    auto injector = getTestInjector(scope);
    PlayersManager& playersManager = injector.create<PlayersManager&>();
    PluginManager& pluginManager = injector.create<PluginManager&>();
    pluginManager.load();
    ApplicationSettings applicationSettings;
    Plugin& plugin1 = *pluginManager.getAll()[0];
    Plugin& plugin2 = *pluginManager.getAll()[1];

    StreamingServiceModel model(plugin1, applicationSettings, playersManager);
    StreamingServiceModel sameModel(plugin1, applicationSettings, playersManager);
    StreamingServiceModel model2(plugin2, applicationSettings, playersManager);

    REQUIRE(model.getColor() == plugin1.getColor());
    REQUIRE(model.getLogo() == plugin1.getLogo());
    REQUIRE(model.getName() == plugin1.getName());
    REQUIRE(model.getPlayer() == playersManager.getPlayer(plugin1.getName()).get());

    REQUIRE(model != model2);
    REQUIRE(model == sameModel);

    REQUIRE(model.getUrl() == plugin1.getUrl());

    QSignalSpy spy(&model, SIGNAL(urlChanged(const QString&)));
    model.setCustomUrl("https://deezer.com/news");
    REQUIRE(model.getUrl() == "https://deezer.com/news");
    REQUIRE(spy.count() == 1);
}