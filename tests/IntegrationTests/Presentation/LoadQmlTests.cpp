#include <catch.hpp>
#include <QtTest/QSignalSpy>
#include <MellowPlayer/Presentation/ViewModels/MainWindowViewModel.hpp>
#include "Utils/DependencyPool.hpp"

using namespace MellowPlayer;
using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;

TEST_CASE("LoadQmlTests") {
    Tests::DependencyPool pool;
    MainWindowViewModel& mainWindow = pool.getMainWindowViewModel();

    REQUIRE(mainWindow.load());
}
