//-----------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------

#ifndef LYRICSCONTROLLER_H
#define LYRICSCONTROLLER_H

//---------------------------------------------------------
// Headers
//---------------------------------------------------------
#include <QtNetwork>
#include "controllers/base.h"
#include "utils/songinfo.h"

//---------------------------------------------------------
// Forward declarations
//---------------------------------------------------------
class MainWindow;

class LyricsController : public BaseController {
  Q_OBJECT
public:
  explicit LyricsController(MainWindow *parent = 0);
  void saveState();

public slots:
    void showLyricsPane(bool show);
    void onPageChanged(int page);
    void onSongChanged(const SongInfo &songInfo);
    void onLyricsLoaded(QNetworkReply *reply);

private:
    QNetworkAccessManager *m_nam;
};

#endif // HOTKEYSCONTROLLER_H
