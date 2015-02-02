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
 * \brief Display a notification from the system tray icon whenever the current
 * song changed.
 *
 */
class NotificationsPlugin :
        public QObject,
        public IExtension
{
    Q_OBJECT

#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID IExtension_iid
                      FILE "notifications.json")
#endif
    Q_INTERFACES(IExtension)

public:
    explicit NotificationsPlugin(QObject* parent=NULL);

    /*!
     * \brief Setups the extensions: create and register the mpris service and
     * object.
     */
    void setup();

    /*!
     * \brief Returns the plugin's meta data.
     * \return
     */
    const PluginMetaData& metaData() const;

private slots:
    void onArtReady(const QString& art);
};
