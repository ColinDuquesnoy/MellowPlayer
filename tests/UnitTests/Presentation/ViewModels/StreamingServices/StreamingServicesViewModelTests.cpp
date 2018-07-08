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
#include <catch/catch.hpp>

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
                                         pool.getContextProperties(), pool.getNetworkProxies(), pool.getThemeViewModel());
    viewModel.initialize();
    viewModel.reload();

    StreamingServiceViewModel* service1 = viewModel.allServices()->at(0);
    StreamingServiceViewModel* service2 = viewModel.allServices()->at(1);
    StreamingServiceViewModel* service3 = viewModel.allServices()->at(2);

    SECTION("setCurrentService changes current streaming service")
    {
        REQUIRE(viewModel.currentService() == nullptr);
        viewModel.setCurrentService(viewModel.allServices()->toList()[1]);
        REQUIRE(viewModel.currentService()->streamingService() == streamingServices.current());
        viewModel.setCurrentService(nullptr);
    }

    SECTION("next does not change current service if only one active service")
    {
        service1->setActive(true);
        service2->setActive(false);
        service3->setActive(false);
        viewModel.setCurrentService(service1);
        REQUIRE(viewModel.currentService() == service1);
        viewModel.next();
        REQUIRE(viewModel.currentService() == service1);
    }

    SECTION("next changes current service if more than one service is running")
    {
        service1->setActive(true);
        service2->setActive(true);
        service3->setActive(true);
        viewModel.setCurrentService(service1);
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
        service1->setActive(true);
        service2->setActive(false);
        service3->setActive(false);
        viewModel.setCurrentService(service1);
        REQUIRE(viewModel.currentService() == service1);
        viewModel.previous();
        REQUIRE(viewModel.currentService() == service1);
    }

    SECTION("previous changes current service if more than one service is running")
    {
        service1->setActive(true);
        service2->setActive(true);
        service3->setActive(true);
        viewModel.setCurrentService(service1);
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
                                                        pool.getNetworkProxies(), pool.getThemeViewModel());
        REQUIRE(viewModelWithCmdLine.currentService() == nullptr);
        viewModelWithCmdLine.initialize();
        viewModelWithCmdLine.reload();
        REQUIRE(viewModelWithCmdLine.currentService() != nullptr);
    }
}
