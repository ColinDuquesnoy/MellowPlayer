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

#ifndef ICONS_H
#define ICONS_H

#include <QIcon>

/*!
 * \brief The Icons class contains a set of static functions for easily
 * accessing the application icons.
 *
 * The returned icons will always use the defined icon theme on linux and
 * fallback to the icons stored in mellowplayer.qrc.
 */
class Icons
{
public:
    /*!
     * \brief Gets the "play" icon
     * \return QIcon
     */
    static QIcon play();

    /*!
     * \brief Gets the "pause" icon
     * \return QIcon
     */
    static QIcon pause();

    /*!
     * \brief Gets the "stop" icon
     * \return QIcon
     */
    static QIcon stop();

    /*!
     * \brief Gets the "loading" icon
     * \return QIcon
     */
    static QIcon loading();

    /*!
     * \brief Gets the "next" icon
     * \return QIcon
     */
    static QIcon next();

    /*!
     * \brief Gets the "previous" icon
     * \return QIcon
     */
    static QIcon previous();

    /*!
     * \brief Gets the "select music streaming service" icon
     * \return QIcon
     */
    static QIcon selectStreamingService();

    /*!
     * \brief Gets the "preferences" icon
     * \return QIcon
     */
    static QIcon preferences();

    /*!
     * \brief Gets the "quit" icon
     * \return QIcon
     */
    static QIcon quit();

    /*!
     * \brief Gets the "about" icon
     * \return QIcon
     */
    static QIcon about();

    /*!
     * \brief Gets the "report bug" icon
     * \return QIcon
     */
    static QIcon reportBug();

    /*!
     * \brief Gets the application icon
     * \return QIcon
     */
    static QIcon mellowPlayer();

    /*!
     * \brief Gets the application icon
     * \return QIcon
     */
    static QIcon trayIcon();

    static QIcon interface();
    static QIcon shortcuts();
    static QIcon plugins();

    static QIcon userTrash();
};

#endif // ICONS_H
