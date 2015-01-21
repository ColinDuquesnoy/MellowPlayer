#ifndef TRAYICON
#define TRAYICON

#include <QObject>
#include <QSystemTrayIcon>

#ifdef __kde_support__
class KStatusNotifierItem;
#endif

/**
 * @brief The TrayIcon class is a wrapper over the various tray
 * icon implementations (currently QSystemTrayIcon or KStatusNotifierItem).
 */
class TrayIcon: public QObject
{
    Q_OBJECT
public:
    explicit TrayIcon(QObject* parent);
    ~TrayIcon();

    void close();
    void setIcon(const QIcon& icon);
    void setContextMenu(QMenu* menu);
    void setToolTip(const QString& toolTip);
    void showMessage(const QString& message, const QString &icon="mellowplayer");

signals:
    void activated(bool active);

private slots:
    void onKF5IconActivated(bool state, QPoint pos);
    void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);

private:
#ifdef __kde_support__
    KStatusNotifierItem* trayIcon;
#else
    QSystemTrayIcon* trayIcon;
#endif
};

#endif // TRAYICON

