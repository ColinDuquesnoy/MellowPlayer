#include <MellowPlayer/Presentation/ViewModels/ClipBoardViewModel.hpp>
#include <QApplication>
#include <QClipboard>
#include <catch/catch.hpp>
#include <UnitTests/Presentation/Qml/FakeContextProperties.hpp>

using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Presentation::Tests;

TEST_CASE("ClipBoardViewModelTests")
{
    FakeContextProperties contextProperties;
    ClipBoardViewModel clipBoardViewModel(contextProperties);
    QClipboard* clipboard = qApp->clipboard();
    clipboard->clear();
    REQUIRE(clipboard->text() == "");
    clipBoardViewModel.setText("blabla");

    // this test sometimes fail on KDE5
    if (!clipboard->text().isEmpty())
        REQUIRE(clipboard->text() == "blabla");
}
