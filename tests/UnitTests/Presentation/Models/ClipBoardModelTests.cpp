#include <QApplication>
#include <QClipboard>
#include <catch.hpp>
#include <MellowPlayer/Presentation/Models/ClipBoardModel.hpp>

USE_MELLOWPLAYER_NAMESPACE(Presentation)

TEST_CASE("ClipBoardViewModelTests") {
    ClipBoardModel clipBoardViewModel;
    QClipboard* clipboard = qApp->clipboard();
    clipboard->clear();
    REQUIRE(clipboard->text() == "");
    clipBoardViewModel.setText("blabla");
    REQUIRE(clipboard->text() == "blabla");
}
