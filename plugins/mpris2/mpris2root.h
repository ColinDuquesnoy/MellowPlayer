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

#ifndef MPRIS2ROOT_H
#define MPRIS2ROOT_H

#include <QObject>
#include <QtDBus>


/*!
 * \brief The Mpris2Root class implements the MPRIS2 Root interface
 *
 * http://specifications.freedesktop.org/mpris-spec/latest/Media_Player.html
 */
class Mpris2Root:
        QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.mpris.MediaPlayer2")
public:
    explicit Mpris2Root(QObject* parent=NULL);
    Q_PROPERTY(bool CanRaise READ canRaise)
    Q_PROPERTY(bool CanQuit READ canQuit)
    Q_PROPERTY(bool HasTrackList READ hasTrackList)
    Q_PROPERTY(bool CanSetFullscreen READ canSetFullscreen)
    Q_PROPERTY(bool Fullscreen READ fullscreen WRITE setFullscreen)
    Q_PROPERTY(QString Identity READ identity)
    Q_PROPERTY(QString DesktopEntry READ desktopEntry)
    Q_PROPERTY(QStringList SupportedUriSchemes READ supportedUriSchemes)
    Q_PROPERTY(QStringList SupportedMimeTypes READ supportedMimeTypes)

public slots:
    void Raise();
    void Quit();

private:
    bool canRaise();
    bool canQuit();
    bool hasTrackList();
    bool canSetFullscreen();
    bool fullscreen();
    void setFullscreen(bool value);
    QString identity();
    QString desktopEntry();
    QStringList supportedUriSchemes();
    QStringList supportedMimeTypes();
};

#endif // MPRIS2ROOT_H
