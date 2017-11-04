#include "Utils/DependencyPool.hpp"
#include <MellowPlayer/Presentation/ViewModels/MainWindowViewModel.hpp>

using namespace MellowPlayer;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

TEST_CASE("LoadQmlTests")
{
    Tests::DependencyPool pool;
    MainWindowViewModel& mainWindow = pool.getMainWindowViewModel();

    REQUIRE(mainWindow.load());
}
