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

class QDBusPendingCallWatcher;
class OrgGnomeSettingsDaemonMediaKeysInterface;


// Adapted from Clementine's gnomeglobalshortcutbackend
class GnomemediakeysPlugin :
        public QObject,
        public IExtension
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID IExtension_iid FILE "gnomemediakeys.json")
    Q_INTERFACES(IExtension)

public:
    explicit GnomemediakeysPlugin(QObject* parent=NULL);

    void setup();
    void teardown();
    const PluginMetaData& metaData() const;

private slots:
    void registerFinished(QDBusPendingCallWatcher* watcher);
    void gnomeMediaKeyPressed(const QString& _, const QString& key);
private:
    OrgGnomeSettingsDaemonMediaKeysInterface* m_interface;
    bool m_connected;
};
