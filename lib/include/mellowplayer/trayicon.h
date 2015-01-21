//---------------------------------------------------------
//
// This file is part of MellowPlayer.
//
// MellowPlayer is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MellowPlayer is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with MellowPlayer.  If not, see <http://www.gnu.org/licenses/>.
//
//---------------------------------------------------------

#ifndef TRAYICON
#define TRAYICON

#include <QObject>
#include <QSystemTrayIcon>

#ifdef __kde_support__
class KStatusNotifierItem;
#endif


/**
 * @brief The TrayIcon class is a small wrapper over the various tray
 * icon implementations.
 *
 * Currently we support QSystemTrayIcon and KStatusNotifierItem.
 */
class TrayIcon: public QObject
{
    Q_OBJECT
public:
    explicit TrayIcon(QObject* parent);
    ~TrayIcon();

    /*!
     * @brief Sets the icon of the entry in the system tray.
     *
     * @param icon The new icon to set.
     */
    void setIcon(const QIcon& icon);

    /*!
     * @brief Sets the tray icon's context menu.
     *
     * @param menu The new context menu to set.
     */
    void setContextMenu(QMenu* menu);

    /*!
     * \brief Sets the tray icon's tooltip.
     *
     * \param toolTip The new tooltip text.
     */
    void setToolTip(const QString& toolTip);

    /*!
     * \brief Shows a message from the tray icon (i.e. display a desktop
     * notification).
     *
     * \param message Message to display.
     * \param icon The message icon. Used only for KDE builds.
     */
    void showMessage(const QString& message,
                     const QString &icon="mellowplayer");

signals:
    /**
     * @brief Signal emitted when the tray icon is activated.
     *
     * @param active Specifies whether the main window should be visible or not.
     */
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

