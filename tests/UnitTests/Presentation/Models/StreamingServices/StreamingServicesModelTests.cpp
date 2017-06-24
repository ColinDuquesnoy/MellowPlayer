#include <catch.hpp>
#include <MellowPlayer/Presentation/Models/StreamingServices/StreamingServicesModel.hpp>
#include "qt-qml-models/QQmlObjectListModel.hpp"
#include "Mocks/StreamingServiceLoaderMock.hpp"
#include "DI.hpp"

USE_MELLOWPLAYER_NAMESPACE(Application)
USE_MELLOWPLAYER_NAMESPACE(Presentation)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)
using namespace fakeit;

TEST_CASE("StreamingServicesModel", "[UnitTest]") {
    ScopedScope scope;
    auto injector = getTestInjector(scope);
    StreamingServices& streamingServices = injector.create<StreamingServices&>();
    streamingServices.load();
    StreamingServicesModel& viewModel = injector.create<StreamingServicesModel&>();
    viewModel.initialize();
    viewModel.reload();

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
}

