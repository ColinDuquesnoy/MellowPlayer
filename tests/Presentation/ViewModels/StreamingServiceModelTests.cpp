#include <catch.hpp>
#include <MellowPlayer/Presentation/ViewModels/StreamingServicesViewModel.hpp>
#include <QtTest/QSignalSpy>
#include "DI.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

TEST_CASE("StreamingServiceModelTests") {
    ScopedScope scope;
    auto injector = getTestInjector(scope);
    PlayerService& playerService = injector.create<PlayerService&>();
    PluginService& pluginService = injector.create<PluginService&>();
    pluginService.load();
    ApplicationSettings applicationSettings;
    Plugin& plugin1 = *pluginService.getAll()[0];
    Plugin& plugin2 = *pluginService.getAll()[1];

    StreamingServiceModel model(plugin1, applicationSettings, playerService);
    StreamingServiceModel sameModel(plugin1, applicationSettings, playerService);
    StreamingServiceModel model2(plugin2, applicationSettings, playerService);

    REQUIRE(model.getColor() == plugin1.getColor());
    REQUIRE(model.getLogo() == plugin1.getLogo());
    REQUIRE(model.getName() == plugin1.getName());
    REQUIRE(model.getPlayer() == playerService.get(plugin1.getName()).get());

    REQUIRE(model != model2);
    REQUIRE(model == sameModel);

    REQUIRE(model.getUrl() == plugin1.getUrl());

    QSignalSpy spy(&model, SIGNAL(urlChanged(const QString&)));
    model.setCustomUrl("https://deezer.com/news");
    REQUIRE(model.getUrl() == "https://deezer.com/news");
    REQUIRE(spy.count() == 1);
}