#ifdef USE_LIBNOTIFY

#include "Mocks/MainWindowMock.hpp"
#include <MellowPlayer/Application/Notifications/Notifications.hpp>
#include <MellowPlayer/Presentation/Notifications/Presenters/LibnotifyPresenter.hpp>
#include <catch.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;

TEST_CASE("LibnotifyPresenterTests")
{
    auto mainWindowMock = MainWindowMock::get();
    LibnotifyPresenter presenter(mainWindowMock.get());
    presenter.initialize();

    SECTION("display test")
    {
        Notification notif{"title", "message", "", NotificationType::NewSong};
        presenter.display(notif);
        presenter.display(notif);
    }

    SECTION("action callback show main window")
    {
        presenter.onActionCallback();
        Verify(Method(mainWindowMock, show)).Once();
    }
}

#endif
