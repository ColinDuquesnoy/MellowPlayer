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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QWidget>
#include <QMainWindow>
#include <QCloseEvent>

class TrayIcon;

namespace Ui {
class MainWindow;
}

//! Implements the main window of the application.
class MainWindow : public QMainWindow
{
    Q_OBJECT
    friend class DlgPreferences;

public:
    explicit MainWindow(bool debug, QWidget *parent = 0);
    ~MainWindow();

    /*!
     * \brief Shows the web page
     */
    void showWebPage();

    /*!
     * \brief Shows the home page
     */
    void showHomePage();

    /*!
     * \brief Save window geometry and state
     */
    void saveGeometryAndState();

private slots:
    void onLinkClicked(QUrl url);
    void onPlayPauseTriggered();
    void onStopTriggered();
    void onNextTriggered();
    void onPreviousTriggered();
    void onTrayIconActivated(bool active);
    void onSelectServiceTriggered();
    void onPreferencesTriggered();
    void updatePlayer();
    void onAboutTriggered();
    void onAboutQtTriggered();
    void onWikiTriggered();
    void onReportBugTriggered();
    void quit();
    void onAddToFavorites();
    void onLoadFinished(bool ok);

private:
    void closeEvent(QCloseEvent* event);
    void setupIcons();
    void setupActions();
    void setupTrayIcon();
    void setupUpdateTimer();
    void setupWebView(bool debug);
    void connectSlots();

    void restoreGeometryAndState();

    Ui::MainWindow *m_ui;
    QTimer* m_updateTimer;
    TrayIcon* m_trayIcon;
};

#endif // MAINWINDOW_H

