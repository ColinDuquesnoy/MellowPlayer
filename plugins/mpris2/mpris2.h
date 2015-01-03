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
#include <QObject>
#include <QtDBus>
#include <mellowplayer.h>

class Mpris2Root;
class Mpris2Player;

/*!
 * \brief Provides MPRIS2 support to MellowPlayer
 *
 * MPRIS clients will see the MellowPlayer application. You can interact with
 * the player, song data are send on the bus but there is no playlist support.
 *
 * At the moment you cannot seek or change the volume but this is planned!
 *
 */
class Mpris2Plugin :
        public QObject,
        public IExtension
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID IExtension_iid
                      FILE "mpris2.json")
    Q_INTERFACES(IExtension)

public:
    explicit Mpris2Plugin(QObject* parent=NULL);

    /*!
     * \brief Setups the extensions: create and register the mpris service and
     * object.
     */
    void setup();

    /*!
     * \brief Tears the extension down: unregister the service and object.
     */
    void teardown();

    /*!
     * \brief Returns the MPRIS2 configuration widget.
     *
     * \return QWidget*
     */
    QWidget* settingsWidget();
private:
    Mpris2Root* root;       /*!< Mpris2 root interface */
    Mpris2Player* player;   /*!< Mpris2 player interface */
};


