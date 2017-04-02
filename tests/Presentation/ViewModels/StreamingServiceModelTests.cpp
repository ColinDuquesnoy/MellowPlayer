#include <catch.hpp>
#include <MellowPlayer/Presentation/ViewModels/StreamingServicesViewModel.hpp>
#include <QtTest/QSignalSpy>
#include "DI.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

TEST_CASE("StreamingServiceModelTests") {
    ScopedScope scope;
    auto injector = getTestInjector(scope);
    PlayersService& playersService = injector.create<PlayersService&>();
    PluginsService& pluginManager = injector.create<PluginsService&>();
    pluginManager.load();
    ApplicationSettings applicationSettings;
    Plugin& plugin1 = *pluginManager.getAll()[0];
    Plugin& plugin2 = *pluginManager.getAll()[1];

    StreamingServiceModel model(plugin1, applicationSettings, playersService);
    StreamingServiceModel sameModel(plugin1, applicationSettings, playersService);
    StreamingServiceModel model2(plugin2, applicationSettings, playersService);

    REQUIRE(model.getColor() == plugin1.getColor());
    REQUIRE(model.getLogo() == plugin1.getLogo());
    REQUIRE(model.getName() == plugin1.getName());
    REQUIRE(model.getPlayer() == playersService.get(plugin1.getName()).get());

    REQUIRE(model != model2);
    REQUIRE(model == sameModel);

    REQUIRE(model.getUrl() == plugin1.getUrl());

    QSignalSpy spy(&model, SIGNAL(urlChanged(const QString&)));
    model.setCustomUrl("https://deezer.com/news");
    REQUIRE(model.getUrl() == "https://deezer.com/news");
    REQUIRE(spy.count() == 1);
}