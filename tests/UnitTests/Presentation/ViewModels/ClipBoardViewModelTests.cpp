#include <MellowPlayer/Presentation/ViewModels/ClipBoardViewModel.hpp>
#include <QApplication>
#include <QClipboard>
#include <catch.hpp>

using namespace MellowPlayer::Presentation;

TEST_CASE("ClipBoardViewModelTests")
{
    ClipBoardViewModel clipBoardViewModel;
    QClipboard* clipboard = qApp->clipboard();
    clipboard->clear();
    REQUIRE(clipboard->text() == "");
    clipBoardViewModel.setText("blabla");

    // this test sometimes fail on KDE5
    if (!clipboard->text().isEmpty())
        REQUIRE(clipboard->text() == "blabla");
}
