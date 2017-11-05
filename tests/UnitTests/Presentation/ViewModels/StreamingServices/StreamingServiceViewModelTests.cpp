#include <MellowPlayer/Domain/Player/Players.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServicesController.hpp>
#include <MellowPlayer/Presentation/ViewModels/StreamingServices/StreamingServicesControllerViewModel.hpp>
#include <QtTest/QSignalSpy>
#include <Utils/DependencyPool.hpp>
#include <catch.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Tests;

TEST_CASE("StreamingServiceModelTests", "[UnitTest]")
{
    DependencyPool pool;
    Players& players = pool.getPlayers();
    StreamingServicesController& streamingServices = pool.getStreamingServicesController();
    streamingServices.load();

    ISettingsStore& settingsStore = pool.getSettingsStore();

    StreamingService& service1 = *streamingServices.toList()[0];
    StreamingService& service2 = *streamingServices.toList()[1];

    StreamingServiceViewModel viewModel(service1, settingsStore, pool.getUserScriptFactory(), players);
    StreamingServiceViewModel sameModel(service1, settingsStore, pool.getUserScriptFactory(), players);
    StreamingServiceViewModel model2(service2, settingsStore, pool.getUserScriptFactory(), players);

    SECTION("basic properties")
    {
        REQUIRE(viewModel.logo() == service1.logo());
        REQUIRE(viewModel.name() == service1.name());
        REQUIRE(viewModel.player() == players.get(service1.name()).get());
        REQUIRE(viewModel.url() == service1.url());
    }

    SECTION("equality operator")
    {
        REQUIRE(viewModel != model2);
        REQUIRE(viewModel == sameModel);
    }

    SECTION("set custom url")
    {
        QSignalSpy spy(&viewModel, SIGNAL(urlChanged(const QString&)));
        viewModel.setUrl("https://deezer.com/news");
        REQUIRE(viewModel.url() == "https://deezer.com/news");
        REQUIRE(spy.count() == 1);
    }

    SECTION("sort order is undefined initially")
    {
        REQUIRE(viewModel.sortOrder() == -1);
    }

    SECTION("setSortOrder sortOrderChanged signal is emitted")
    {
        QSignalSpy spy(&viewModel, &StreamingServiceViewModel::sortOrderChanged);
        viewModel.setSortOrder(2);
        REQUIRE(viewModel.sortOrder() == 2);
        REQUIRE(spy.count() == 1);
    }

    SECTION("isEnabled is true initially")
    {
        REQUIRE(viewModel.isEnabled());
    }

    SECTION("setEnabled isEnabledChanged signal is emitted")
    {
        QSignalSpy spy(&viewModel, &StreamingServiceViewModel::isEnabledChanged);
        viewModel.setEnabled(false);
        REQUIRE(!viewModel.isEnabled());
        REQUIRE(spy.count() == 1);
    }
}