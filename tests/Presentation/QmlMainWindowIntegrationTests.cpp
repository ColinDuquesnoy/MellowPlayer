#include <catch.hpp>
#include <MellowPlayer/Presentation/QmlMainWindow.hpp>
#include <DI.hpp>

USE_MELLOWPLAYER_NAMESPACE(Presentation)

TEST_CASE("QmlMainWindowIntegrationTests", "[IntegrationTests]") {
    ScopedScope scope;
    auto injector = getTestInjector(scope);
    QmlMainWindow& mainWindow = injector.create<QmlMainWindow&>();

    mainWindow.show();
    mainWindow.hide();
}
