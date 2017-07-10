#include <catch.hpp>
#include <MellowPlayer/Presentation/ViewModels/StreamingServices/StreamingServicesControllerViewModel.hpp>
#include <QtTest/QSignalSpy>
#include "Mocks/StreamingServiceLoaderMock.hpp"
#include "DI.hpp"

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Infrastructure;
using namespace fakeit;

TEST_CASE("StreamingServicesControllerViewModel", "[UnitTest]") {
    ScopedScope scope;
    auto injector = getTestInjector(scope);
    auto loaderMock = StreamingServiceLoaderMock::get();
    StreamingServicesController streamingServices(loaderMock.get());
    streamingServices.load();
    Players players(streamingServices);
    Settings& settings = injector.create<Settings&>();
    FakeWorkDispatcher fakeWorkDispatcher;
    auto creatorMock = StreamingServiceCreatorMock::get();
    StreamingServicesControllerViewModel viewModel(streamingServices, players, settings, fakeWorkDispatcher, creatorMock.get());
    viewModel.initialize();
    viewModel.reload();

    StreamingServiceViewModel* service1 = viewModel.getModel()->at(0);
    StreamingServiceViewModel* service2 = viewModel.getModel()->at(1);
    StreamingServiceViewModel* service3 = viewModel.getModel()->at(2);


    SECTION("setCurrentService changes currentIndex") {
        REQUIRE(viewModel.getModel()->count() == streamingServices.getAll().count());
        REQUIRE(viewModel.getCurrentIndex() == -1);
        REQUIRE(viewModel.getCurrentService() == nullptr);
        viewModel.setCurrentService(viewModel.getModel()->toList()[1]);
        REQUIRE(viewModel.getCurrentIndex() == 1);
        REQUIRE(viewModel.getCurrentService() == viewModel.getModel()->toList()[1]);
        viewModel.setCurrentService(viewModel.getModel()->toList()[1]);
        viewModel.setCurrentIndex(1);
    }

    SECTION("next does not change current service if only one running service") {
        service1->getPlayer()->start();
        service2->getPlayer()->stop();
        service3->getPlayer()->stop();
        viewModel.setCurrentIndex(0);
        REQUIRE(viewModel.getCurrentService() == service1);
        viewModel.next();
        REQUIRE(viewModel.getCurrentService() == service1);
    }

    SECTION("next changes current service if more than one service is running") {
        service1->getPlayer()->start();
        service2->getPlayer()->start();
        service3->getPlayer()->start();
        viewModel.setCurrentIndex(0);
        REQUIRE(viewModel.getCurrentService() == service1);
        viewModel.next();
        REQUIRE(viewModel.getCurrentService() == service2);
        viewModel.next();
        REQUIRE(viewModel.getCurrentService() == service3);
        viewModel.next();
        REQUIRE(viewModel.getCurrentService() == service1);
    }

    SECTION("previous does not change current service if only one running service") {
        service1->getPlayer()->start();
        service2->getPlayer()->stop();
        service3->getPlayer()->stop();
        viewModel.setCurrentIndex(0);
        REQUIRE(viewModel.getCurrentService() == service1);
        viewModel.previous();
        REQUIRE(viewModel.getCurrentService() == service1);
    }

    SECTION("previous changes current service if more than one service is running") {
        service1->getPlayer()->start();
        service2->getPlayer()->start();
        service3->getPlayer()->start();
        viewModel.setCurrentIndex(0);
        REQUIRE(viewModel.getCurrentService() == service1);
        viewModel.previous();
        REQUIRE(viewModel.getCurrentService() == service3);
        viewModel.previous();
        REQUIRE(viewModel.getCurrentService() == service2);
        viewModel.previous();
        REQUIRE(viewModel.getCurrentService() == service1);
    }

    SECTION("create service call creator and reload services") {
        QSignalSpy spy(&viewModel, &StreamingServicesControllerViewModel::serviceCreated);
        viewModel.createService("svName", "svUrl", "authorName", "authorUrl");
        Verify(Method(creatorMock, create));
        Verify(Method(loaderMock, load));
        REQUIRE(spy.count() == 1);
    }
}
