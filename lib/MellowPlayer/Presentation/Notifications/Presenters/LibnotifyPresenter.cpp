#include "LibnotifyPresenter.hpp"
#include "LibnotifyStrings.hpp"
#include <MellowPlayer/Application/IMainWindow.hpp>
#include <MellowPlayer/Application/Logging/ILogger.hpp>
#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include <MellowPlayer/Application/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Application/Notifications/Notifications.hpp>
#include <libnotify/notify.h>

using namespace std;
using namespace MellowPlayer::Application;
using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;

LibnotifyPresenter* LibnotifyPresenter::instance_ = nullptr;

void notify_action_callback(NotifyNotification*, char*, gpointer)
{
    LibnotifyPresenter::onActionCallback();
}

LibnotifyPresenter::LibnotifyPresenter(IMainWindow& mainWindow)
        : logger_(LoggingManager::logger("LibnotifyPresenter")), mainWindow_(mainWindow), previousNotification_(nullptr)
{
    instance_ = this;
}

void LibnotifyPresenter::initialize()
{
    notify_init("MellowPlayer");
    LOG_DEBUG(logger_, "service started")
}

bool LibnotifyPresenter::display(const Notification& notification)
{
    static LibnotifyStrings strings;

    if (previousNotification_)
        notify_notification_close(previousNotification_, 0);
    QString title = "MellowPlayer - " + notification.title;
    NotifyNotification* n =
    notify_notification_new(title.toStdString().c_str(), notification.description.toStdString().c_str(), notification.icon.toStdString().c_str());
    notify_notification_set_timeout(n, 5000);
    string openStr = strings.open();
    notify_notification_add_action(n, "open", strings.open().c_str(),
                                   (NotifyActionCallback)notify_action_callback, nullptr, nullptr);
    bool success = static_cast<bool>(notify_notification_show(n, 0));
    previousNotification_ = n;
    return success;
}

void LibnotifyPresenter::onActionCallback()
{
    instance_->mainWindow_.show();
}
