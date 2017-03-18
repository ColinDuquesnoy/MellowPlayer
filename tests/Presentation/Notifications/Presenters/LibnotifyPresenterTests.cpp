#ifdef USE_LIBNOTIFY

#include <catch.hpp>
#include <MellowPlayer/Presentation.hpp>
#include "Mocks/MainWindowMock.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

TEST_CASE("LibnotifyPresenterTests") {
    auto mainWindowMock = MainWindowMock::get();
    LibnotifyPresenter presenter(mainWindowMock.get());
    presenter.initialize();

    SECTION("display test") {
        Notification notif{"title", "message", "", NotificationType::Song};
        presenter.display(notif);
        presenter.display(notif);
    }

    SECTION("action callback show main window") {
        presenter.onActionCallback();
        Verify(Method(mainWindowMock, show)).Once();
    }
}

#endif
