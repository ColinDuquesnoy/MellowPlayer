#include <MellowPlayer/Presentation/Notifications/Notification.hpp>
#include <MellowPlayer/Presentation/Notifications/Presenters/SystemTrayIconPresenter.hpp>
#include <Mocks/SystemTrayIconMock.hpp>
#include <catch/catch.hpp>

using namespace MellowPlayer::Presentation;

TEST_CASE("SystemTrayIconPresenterTests")
{
    auto systemTrayIconMock = SystemTrayIconMock::get();
    SystemTrayIconPresenter presenter(systemTrayIconMock.get());
    presenter.initialize();
    Verify(Method(systemTrayIconMock, show)).Once();

    SECTION("display test")
    {
        Notification notif{"title", "message", "", NotificationType::NewSong};
        presenter.display(notif);
        Verify(Method(systemTrayIconMock, showMessage).Using("title", "message")).Once();
    }
}
