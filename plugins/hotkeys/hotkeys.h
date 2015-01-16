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

class QxtGlobalShortcut;

/*!
 * \brief Provides hotkeys capabilities to control the media player.
 *
 * On KDE, we use KGlobalAccel. This means that the settings must be configured
 * using K System Preferences.
 *
 * On other platforms/desktop environmnemts, we use QxtGlobalShortcut.
 */
class HotkeysPlugin :
        public QObject,
        public IExtension
{
    Q_OBJECT
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID IExtension_iid
                      FILE "hotkeys.json")
#endif
    Q_INTERFACES(IExtension)

public:
    const PluginMetaData &metaData() const;
    void setup();
    void teardown();
    QString description() const;

    QWidget* settingsWidget() const;
    void resetSettings(QWidget* widget) const;
    void restoreDefaultSettings(QWidget* widget) const;
    void applySettings(QWidget* widget) const;

private:
#ifndef __kde_support__
    QList<QxtGlobalShortcut*> shortcuts;
#endif
};
