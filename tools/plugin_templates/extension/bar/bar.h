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
#include <mellowplayer.h>


/*!
 * \brief Provides an extension to MellowPlayer.
 *
 * Rename this class into your own and don't forget to update
 * bar.json into your own.
 */
class BarPlugin :
        public QObject,
        public IExtension
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID IExtension_iid
                      FILE "bar.json")
    Q_INTERFACES(IExtension)

public:
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
};


