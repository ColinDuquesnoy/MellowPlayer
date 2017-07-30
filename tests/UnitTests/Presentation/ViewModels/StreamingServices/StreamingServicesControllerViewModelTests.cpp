#include <MellowPlayer/Application/Player/Players.hpp>
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <MellowPlayer/Application/Settings/Settings.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Presentation/ViewModels/StreamingServices/StreamingServicesControllerViewModel.hpp>
#include <Mocks/CommnandLineParserMock.hpp>
#include <Mocks/StreamingServiceCreatorMock.hpp>
#include <QtTest/QSignalSpy>
#include <Utils/DependencyPool.hpp>
#include <catch.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Tests;
using namespace fakeit;

TEST_CASE("StreamingServicesControllerViewModel", "[UnitTest]")
{
    DependencyPool pool;
    StreamingServicesController& streamingServices = pool.getStreamingServicesController();
    streamingServices.load();
    Players& players = pool.getPlayers();
    Settings& settings = pool.getSettings();
    IWorkDispatcher& workDispatcher = pool.getWorkDispatcher();
    auto creatorMock = StreamingServiceCreatorMock::get();
    auto commandLineParserMock = CommandLineParserMock::get();
    StreamingServicesControllerViewModel viewModel(streamingServices, players, settings, workDispatcher, creatorMock.get(),
                                                   commandLineParserMock.get());
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
        QSignalSpy spy(&viewModel, &StreamingServicesControllerViewModel::serviceCreated);
        viewModel.createService("svName", "svUrl", "authorName", "authorUrl");
        Verify(Method(creatorMock, create));
        REQUIRE(spy.count() == 1);
    }

    SECTION("Initialize with service set by command line")
    {
        settings.get(SettingKey::PRIVATE_CURRENT_SERVICE).setValue("");
        When(Method(commandLineParserMock, service)).AlwaysReturn("Deezer");
        StreamingServicesControllerViewModel viewModelWithCmdLine(streamingServices, players, settings, workDispatcher, creatorMock.get(),
                                                                  commandLineParserMock.get());
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
