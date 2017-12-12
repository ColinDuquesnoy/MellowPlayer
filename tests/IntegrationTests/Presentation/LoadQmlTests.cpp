#include "Utils/DependencyPool.hpp"
#include <MellowPlayer/Presentation/ViewModels/MainWindowViewModel.hpp>
#include <MellowPlayer/Presentation/Qml/QmlApplicationEngine.hpp>
#include <MellowPlayer/Presentation/Qml/ContextProperties.hpp>
#include <Mocks/PlayerMock.hpp>

using namespace MellowPlayer;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

TEST_CASE("LoadQmlTests")
{
    QmlApplicationEngine qmlApplicationEngine;
    auto playerMock = PlayerMock::get();
    ContextProperties contextProperties(qmlApplicationEngine, playerMock.get());
    MainWindowViewModel mainWindow(contextProperties, qmlApplicationEngine);
    contextProperties.initialize();

    REQUIRE_NOTHROW(mainWindow.load());
}
