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
    Q_PLUGIN_METADATA(IID IExtension_iid FILE "notifications.json")
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

    /*!
     * \brief Returns the settings widget associated with the extension.
     *
     * Implement this method if you need to show a settings widget in the
     * application preferences dialog. Return NULL if you don't need to show
     * any settings. If you return a non-null widget, you will also need to
     * implement: resetSettings, restoreDefaultSettings and applySettings.
     */
    QWidget* settingsWidget() const;

    /*!
     * \brief Reset the plugin settings
     * \param widget Pointer to the settings widget returned by
     *  setttingsWidget()
     */
    void resetSettings(QWidget* widget) const;

    /*!
     * \brief Restore the plugin settings to their default values.
     * \param widget Pointer to the settings widget returned by
     *  setttingsWidget()
     */
    void restoreDefaultSettings() const;

    /*!
     * \brief Apply plugin settings.
     *
     * \param widget Pointer to the settings widget returned by
     *  setttingsWidget()
     */
    void applySettings(QWidget* widget) const;


    QString saveServiceIconToTemp();
private slots:
    void onSongStarted(const SongInfo& song);
    void onArtReady(const QString& art);
    void onPlaybackStatusChanged(PlaybackStatus status);

private:
    void notifySongChange();
    bool m_wasPlaying;
    bool m_songStarted;
    bool m_artReady;
    QString m_art;
};
