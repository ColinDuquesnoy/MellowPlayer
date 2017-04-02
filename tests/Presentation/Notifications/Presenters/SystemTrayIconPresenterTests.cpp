#include <catch.hpp>
#include <MellowPlayer/UseCases/Notifications/Notifications.hpp>
#include <MellowPlayer/Presentation/Notifications/Presenters/SystemTrayIconPresenter.hpp>
#include <Mocks/SystemTrayIconMock.hpp>

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

TEST_CASE("SystemTrayIconPresenterTests") {
    auto systemTrayIconMock = SystemTrayIconMock::get();
    SystemTrayIconPresenter presenter(systemTrayIconMock.get());
    presenter.initialize();
    Verify(Method(systemTrayIconMock, show)).Once();

    SECTION("display test") {
        Notification notif{"title", "message", "", NotificationType::Song};
        presenter.display(notif);
        Verify(Method(systemTrayIconMock, showMessage).Using("title", "message")).Once();
    }
}