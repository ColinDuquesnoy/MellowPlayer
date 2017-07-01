#include <catch.hpp>
#include <MellowPlayer/Presentation/Models/StreamingServices/StreamingServicesModel.hpp>
#include "qt-qml-models/QQmlObjectListModel.hpp"
#include "Mocks/StreamingServiceLoaderMock.hpp"
#include "DI.hpp"

USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Presentation)
USING_MELLOWPLAYER_NAMESPACE(Infrastructure)
using namespace fakeit;

TEST_CASE("StreamingServicesModel", "[UnitTest]") {
    ScopedScope scope;
    auto injector = getTestInjector(scope);
    StreamingServices& streamingServices = injector.create<StreamingServices&>();
    streamingServices.load();
    StreamingServicesModel& viewModel = injector.create<StreamingServicesModel&>();
    viewModel.initialize();
    viewModel.reload();

    StreamingServiceModel* service1 = viewModel.getModel()->at(0);
    StreamingServiceModel* service2 = viewModel.getModel()->at(1);
    StreamingServiceModel* service3 = viewModel.getModel()->at(2);

    REQUIRE(viewModel.getModel()->count() == streamingServices.getAll().count());

    SECTION("setCurrentService_change_currentIndex") {
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

    SECTION("next change current service if more than one service is running") {
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

    SECTION("previous change current service if more than one service is running") {
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
}

