#include <MellowPlayer/Domain/Player/Player.hpp>
#include <MellowPlayer/Domain/Player/Players.hpp>
#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServices.hpp>
#include <MellowPlayer/Presentation/ViewModels/StreamingServices/StreamingServicesViewModel.hpp>
#include <Mocks/FakeCommnandLineArguments.hpp>
#include <Mocks/StreamingServiceCreatorMock.hpp>
#include <QtTest/QSignalSpy>
#include <Utils/DependencyPool.hpp>
#include <catch.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Infrastructure::Tests;
using namespace MellowPlayer::Tests;
using namespace fakeit;

TEST_CASE("StreamingServicesControllerViewModel", "[UnitTest]")
{
    DependencyPool pool;
    StreamingServices& streamingServices = pool.getStreamingServices();
    streamingServices.load();
    Players& players = pool.getPlayers();
    Settings& settings = pool.getSettings();
    IWorkDispatcher& workDispatcher = pool.getWorkDispatcher();
    auto creatorMock = StreamingServiceCreatorMock::get();
    FakeCommandLineArguments commandLineArguments;
    StreamingServicesViewModel viewModel(streamingServices, players, settings, workDispatcher, creatorMock.get(),
                                         commandLineArguments, pool.getUserScriptFactory(),
                                         pool.getContextProperties(), pool.getNetworkProxies());
    viewModel.initialize();
    viewModel.reload();

    StreamingServiceViewModel* service1 = viewModel.allServices()->at(0);
    StreamingServiceViewModel* service2 = viewModel.allServices()->at(1);
    StreamingServiceViewModel* service3 = viewModel.allServices()->at(2);

    SECTION("setCurrentService changes currentIndex")
    {
        REQUIRE(viewModel.allServices()->count() == streamingServices.toList().count());
        REQUIRE(viewModel.currentIndex() == -1);
        REQUIRE(viewModel.currentService() == nullptr);
        viewModel.setCurrentService(viewModel.allServices()->toList()[1]);
        REQUIRE(viewModel.currentIndex() == 1);
        REQUIRE(viewModel.currentService() == viewModel.allServices()->toList()[1]);
        viewModel.setCurrentService(viewModel.allServices()->toList()[1]);
        viewModel.setCurrentIndex(1);
    }

    SECTION("next does not change current service if only one running service")
    {
        service1->player()->start();
        service2->player()->stop();
        service3->player()->stop();
        viewModel.setCurrentIndex(0);
        REQUIRE(viewModel.currentService() == service1);
        viewModel.next();
        REQUIRE(viewModel.currentService() == service1);
    }

    SECTION("next changes current service if more than one service is running")
    {
        service1->player()->start();
        service2->player()->start();
        service3->player()->start();
        viewModel.setCurrentIndex(0);
        REQUIRE(viewModel.currentService() == service1);
        viewModel.next();
        REQUIRE(viewModel.currentService() == service2);
        viewModel.next();
        REQUIRE(viewModel.currentService() == service3);
        viewModel.next();
        REQUIRE(viewModel.currentService() == service1);
    }

    SECTION("previous does not change current service if only one running service")
    {
        service1->player()->start();
        service2->player()->stop();
        service3->player()->stop();
        viewModel.setCurrentIndex(0);
        REQUIRE(viewModel.currentService() == service1);
        viewModel.previous();
        REQUIRE(viewModel.currentService() == service1);
    }

    SECTION("previous changes current service if more than one service is running")
    {
        service1->player()->start();
        service2->player()->start();
        service3->player()->start();
        viewModel.setCurrentIndex(0);
        REQUIRE(viewModel.currentService() == service1);
        viewModel.previous();
        REQUIRE(viewModel.currentService() == service3);
        viewModel.previous();
        REQUIRE(viewModel.currentService() == service2);
        viewModel.previous();
        REQUIRE(viewModel.currentService() == service1);
    }

    SECTION("create service call creator and reload services")
    {
        QSignalSpy spy(&viewModel, &StreamingServicesViewModel::serviceCreated);
        viewModel.createService("svName", "svUrl", "authorName", "authorUrl", true, false, false, false, false);
        Verify(Method(creatorMock, create));
        REQUIRE(spy.count() == 1);
    }

    SECTION("Initialize with service set by command line")
    {
        commandLineArguments.setService("Deezer");
        settings.get(SettingKey::PRIVATE_CURRENT_SERVICE).setValue("");

        StreamingServicesViewModel viewModelWithCmdLine(streamingServices, players, settings, workDispatcher,
                                                        creatorMock.get(), commandLineArguments,
                                                        pool.getUserScriptFactory(), pool.getContextProperties(),
                                                        pool.getNetworkProxies());
        REQUIRE(viewModelWithCmdLine.currentIndex() == -1);
        viewModelWithCmdLine.initialize();
        viewModelWithCmdLine.reload();
        REQUIRE(viewModelWithCmdLine.currentIndex() != -1);
    }

    SECTION("currentIndex is -1 when current service is disabled")
    {
        viewModel.setCurrentIndex(0);
        REQUIRE(viewModel.currentIndex() == 0);
        service1->setEnabled(false);
        REQUIRE(viewModel.currentIndex() == -1);
        service1->setSortOrder(0);
        service1->setEnabled(true);
    }

    SECTION("currentIndex does not change if other service is disabled")
    {
        viewModel.setCurrentIndex(0);
        REQUIRE(viewModel.currentIndex() == 0);
        service2->setEnabled(false);
        REQUIRE(viewModel.currentIndex() == 0);
    }
}
