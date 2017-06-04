#pragma once


#include <MellowPlayer/Application/Notifications/INotificationPresenter.hpp>
#include <libsnore/snore.h>

PREDECLARE_MELLOWPLAYER_CLASS(Application, ILogger)
PREDECLARE_MELLOWPLAYER_CLASS(Application, IMainWindow)

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class SnorenotifyPresenter: public QObject, public Application::INotificationPresenter {
    Q_OBJECT
public:
    SnorenotifyPresenter(Application::IMainWindow& mainWindow);
    void initialize() override;
    bool display(const Application::Notification& notification) override;

private slots:
    void onActionInvoked(const Snore::Notification &notification);

private:
    Application::IMainWindow& mainWindow;
    Application::ILogger& logger;
    Snore::Application snoreApp;
    Snore::Notification oldNotification;
};

END_MELLOWPLAYER_NAMESPACE