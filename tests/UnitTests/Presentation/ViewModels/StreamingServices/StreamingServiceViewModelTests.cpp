#include <catch.hpp>
#include <MellowPlayer/Presentation/ViewModels/StreamingServices/StreamingServicesControllerViewModel.hpp>
#include <QtTest/QSignalSpy>
#include "DI.hpp"

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;

TEST_CASE("StreamingServiceModelTests", "[UnitTest]") {
    ScopedScope scope;
    auto injector = getTestInjector(scope);
    Players& players = injector.create<Players&>();
    StreamingServicesController& streamingServices = injector.create<StreamingServicesController&>();
    streamingServices.load();
    QSettingsProvider settingsProvider;
    StreamingService& service1 = *streamingServices.getAll()[0];
    StreamingService& service2 = *streamingServices.getAll()[1];

    StreamingServiceViewModel viewModel(service1, settingsProvider, players);
    StreamingServiceViewModel sameModel(service1, settingsProvider, players);
    StreamingServiceViewModel model2(service2, settingsProvider, players);

    SECTION("basic properties") {
        REQUIRE(viewModel.getLogo() == service1.getLogo());
        REQUIRE(viewModel.getName() == service1.getName());
        REQUIRE(viewModel.getPlayer() == players.get(service1.getName()).get());
        REQUIRE(viewModel.getUrl() == service1.getUrl());
    }

    SECTION("equality operator") {
        REQUIRE(viewModel != model2);
        REQUIRE(viewModel == sameModel);
    }

    SECTION("set custom url") {
        QSignalSpy spy(&viewModel, SIGNAL(urlChanged(const QString&)));
        viewModel.setUrl("https://deezer.com/news");
        REQUIRE(viewModel.getUrl() == "https://deezer.com/news");
        REQUIRE(spy.count() == 1);
    }

    SECTION("sort order is undefined initially") {
        REQUIRE(viewModel.getSortOrder() == -1);
    }

    SECTION("setSortOrder sortOrderChanged signal is emitted") {
        QSignalSpy spy(&viewModel, &StreamingServiceViewModel::sortOrderChanged);
        viewModel.setSortOrder(2);
        REQUIRE(viewModel.getSortOrder() == 2);
        REQUIRE(spy.count() == 1);
    }

    SECTION("isEnabled is true initially") {
        REQUIRE(viewModel.isEnabled());
    }

    SECTION("setEnabled isEnabledChanged signal is emitted") {
        QSignalSpy spy(&viewModel, &StreamingServiceViewModel::isEnabledChanged);
        viewModel.setEnabled(false);
        REQUIRE(!viewModel.isEnabled());
        REQUIRE(spy.count() == 1);
    }
}