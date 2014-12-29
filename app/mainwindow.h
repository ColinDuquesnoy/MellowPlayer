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

#include <QMainWindow>

class Player;
class QPluginLoader;
namespace Ui {
class MainWindow;
}


//! Implements the main window of the application.
/*!
  This object is the main object of the application, it contains
  pointers to the various managers of the applications: the plugin
  manager, the cloud services integrations manager, the player
  interface,...
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

    //! Returns a pointer to the player interface.
    Player* getPlayer() const;

private:
    void loadPlugins();
    void loadPlugin(QPluginLoader* plugin);
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
