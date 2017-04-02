#ifdef USE_SNORENOTIFY

#include "SnorenotifyPresenter.hpp"
#include <MellowPlayer/Presentation/IconProvider.hpp>

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

SnorenotifyPresenter::SnorenotifyPresenter(IMainWindow& mainWindow):
        mainWindow(mainWindow), logger(LoggingManager::instance().getLogger("SnorenotifyPresenter")),
        snoreApp("MellowPlayer", IconProvider::windowIcon()) {
}

void SnorenotifyPresenter::initialize() {
    Snore::SnoreCore &snoreCore = Snore::SnoreCore::instance();
    snoreCore.registerApplication(snoreApp);
    snoreCore.setDefaultApplication(snoreApp);
    snoreCore.loadPlugins(Snore::SnorePlugin::All);

    LOG_INFO(logger, "backend started: " + snoreCore.primaryNotificationBackend());
    connect(&snoreCore, &Snore::SnoreCore::actionInvoked, this, &SnorenotifyPresenter::onActionInvoked);
}

bool SnorenotifyPresenter::display(const Notification& notification) {
    LOG_TRACE(logger, "display(" + notification.toString() + ")");
    Snore::SnoreCore &snoreCore = Snore::SnoreCore::instance();
    QString title = notification.title;
    QString message = notification.description;
    QIcon icon(notification.icon);
    
    if (icon.isNull())
        icon = IconProvider::windowIcon();

    if (!snoreApp.constHints().value("use-markup").toBool()) {
        title = Snore::Utils::normalizeMarkup(title, Snore::Utils::NoMarkup);
        message = Snore::Utils::normalizeMarkup(message, Snore::Utils::NoMarkup);
    }

    int timeout = 5; // todo make this configurable
    if (oldNotification.isValid())
        snoreCore.requestCloseNotification(oldNotification, Snore::Notification::Replaced);

    Snore::Notification notif(snoreApp, snoreApp.defaultAlert(), title, message, icon, timeout);
    notif.addAction(Snore::Action(0, tr("Open")));
    snoreCore.broadcastNotification(notif);
    oldNotification = notif;
    return true;
}

void SnorenotifyPresenter::onActionInvoked(const Snore::Notification&) {
    LOG_TRACE(logger, "onActionInvoked()");
    mainWindow.show();
}

#endif