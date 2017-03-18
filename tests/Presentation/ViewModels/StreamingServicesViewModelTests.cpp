#include <catch.hpp>
#include <MellowPlayer/Presentation.hpp>
#include <MellowPlayer/Infrastructure.hpp>
#include "../../Mocks/PluginLoaderMock.hpp"
#include "DI.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)
using namespace fakeit;

TEST_CASE("StreamingServicesViewModel") {
    ScopedScope scope;
    auto injector = getTestInjector(scope);
    PluginManager& servicesManager = injector.create<PluginManager&>();
    servicesManager.load();
    StreamingServicesViewModel& viewModel = injector.create<StreamingServicesViewModel&>();
    viewModel.initialize();
    viewModel.reload();

    REQUIRE(viewModel.getModel()->rowCount() == servicesManager.getAll().count());

    SECTION("setCurrentService_change_currentIndex") {
        REQUIRE(viewModel.getCurrentIndex() == -1);
        REQUIRE(viewModel.getCurrentService() == nullptr);
        viewModel.setCurrentService(viewModel.getModel()->getItems()[1]);
        REQUIRE(viewModel.getCurrentIndex() == 1);
        REQUIRE(viewModel.getCurrentService() == viewModel.getModel()->getItems()[1]);
        viewModel.setCurrentService(viewModel.getModel()->getItems()[1]);
        viewModel.setCurrentIndex(1);
    }
}

