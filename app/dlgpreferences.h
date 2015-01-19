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

#ifndef DLGPREFERENCES_H
#define DLGPREFERENCES_H

#include <QMainWindow>
#include <QDialog>
#include <QIcon>


namespace Ui {
    class DialogPreferences;
}
class MainWindow;


/*!
 * \brief The DlgPreferences class implement the preferences dialog.
 */
class DlgPreferences: public QDialog
{
    Q_OBJECT
public:
    explicit DlgPreferences(MainWindow *parent=NULL);
    ~DlgPreferences();

    /*!
     * \brief Convenience method for editing the application
     * preferences
     *
     * \param parent Parent widget of the dialog.
     * \return True if the dialog was accepted.
     */
    static bool editPreferences(MainWindow *parent);

    /*!
     * \brief Utility method to load a tray icon from string.
     *
     * The string can be a fully qualified file system path or a resource path.
     *
     * \param path Path of the icon to create
     * \return Icon instance
     */
    static QIcon trayIconFrom(const QString& path);

    void restart();
private slots:
    void onCategoryChanged(int category);
    void reset();
    void restoreDefaults();
    void updateTrayIcon(const QString& iconPath);
    void chooseTrayIconFile();
    void onCurrentPluginChanged(int currentIndex);
    void onPluginStateChanged(int state);
    void onClearCookiesClicked();
    void onClearPreferencesClicked();

private:
    void resetInterface();
    void resetShortcuts();
    void resetPlugins();

    void restoreInterface();
    void restoreShortcuts();
    void restorePlugins();

    void applyInterface();
    void applyShortcuts();
    void applyPlugins();


private:
    Ui::DialogPreferences* ui;
    MainWindow* mainWindow;
};

#endif // DLGPREFERENCES_H
