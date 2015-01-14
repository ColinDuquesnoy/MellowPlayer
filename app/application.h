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
#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QTranslator>
#include "singleinstancecontroller.h"

class MainWindow;


/**
 * @brief The MellowPlayerApp class is the main application class.
 *
 * This is where we initializes the application GUI and the associated
 * services (plugins, player interface,...).
 */
class MellowPlayerApp: public QApplication
{
public:
    MellowPlayerApp(int &argc, char **argv);
    ~MellowPlayerApp();

    /*!
     * \brief Initializes the application objects (main windown,...).
     */
    void initialize();

    /*!
     * \brief Raises the main window.
     *
     * Brings the app window to front.
     */
    void raise();

    int exec();

private:
    QTranslator translator;
    SingleInstanceController singleInstanceController;
    MainWindow* mainWindow;
};


#endif // APPLICATION_H
