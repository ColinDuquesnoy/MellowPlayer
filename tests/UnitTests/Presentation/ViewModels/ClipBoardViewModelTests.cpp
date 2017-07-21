#include <MellowPlayer/Presentation/ViewModels/ClipBoardViewModel.hpp>
#include <QApplication>
#include <QClipboard>
#include <catch.hpp>

using namespace MellowPlayer::Presentation;

TEST_CASE("ClipBoardViewModelTests")
{
    ClipBoardViewModel clipBoardViewModel;
    QClipboard *clipboard = qApp->clipboard();
    clipboard->clear();
    REQUIRE(clipboard->text() == "");
    clipBoardViewModel.setText("blabla");
    REQUIRE(clipboard->text() == "blabla");
}
