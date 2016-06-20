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

//---------------------------------------------------------
// Headers
//---------------------------------------------------------
#include <QAction>
#include <QDomDocument>
#include <qxtglobalshortcut.h>
#include "controllers/lyrics.h"
#include "controllers/player.h"
#include "views/mainwindow.h"
#include "ui_mainwindow.h"


#define LYRICS_ENGINE_URL "http://api.chartlyrics.com/apiv1.asmx/SearchLyricDirect?artist=%1&song=%2"

//---------------------------------------------------------
// Implementations
//---------------------------------------------------------
//-------------------------------------
LyricsController::LyricsController(MainWindow *parent)
    : BaseController("lyrics", parent) {

    m_nam  = new QNetworkAccessManager(this);
    connect(m_mainWindow->ui()->actionShow_lyrics, &QAction::toggled, this, &LyricsController::showLyricsPane);
    connect(m_mainWindow->ui()->stackedWidget, &QStackedWidget::currentChanged, this, &LyricsController::onPageChanged);
    connect(m_mainWindow->player(), &PlayerController::songChanged, this, &LyricsController::onSongChanged);
    connect(m_nam, &QNetworkAccessManager::finished, this, &LyricsController::onLyricsLoaded);
    showLyricsPane(false);

    m_mainWindow->ui()->textEditLyrics->setAlignment(Qt::AlignCenter);
}

//-------------------------------------
void LyricsController::saveState()
{
    QSettings().setValue("lyricsPaneVisible", m_mainWindow->ui()->dockWidgetLyrics->isVisible());
}

//-------------------------------------
void LyricsController::showLyricsPane(bool show)
{
    m_mainWindow->ui()->actionShow_lyrics->blockSignals(true);
    m_mainWindow->ui()->actionShow_lyrics->setChecked(show);
    m_mainWindow->ui()->actionShow_lyrics->blockSignals(false);

    m_mainWindow->ui()->dockWidgetLyrics->setVisible(show);
}

//-------------------------------------
void LyricsController::onPageChanged(int page)
{
    if(page == PAGE_WEB){
        // restore state of lyrics pane
        bool autoShow = QSettings().value("automaticallyShowLyricsPane", true).toBool();
        bool lyricsPaneVisible = QSettings().value("lyricsPaneVisible", false).toBool();
        if(!autoShow){
            m_mainWindow->ui()->dockWidgetLyrics->setVisible(lyricsPaneVisible);
        }
    } else {
        showLyricsPane(false);
    }
}

//-------------------------------------
void LyricsController::onSongChanged(const SongInfo &songInfo)
{
    QString baseUrl(LYRICS_ENGINE_URL);
    QString artist = QString(songInfo.ArtistName).toLower();
    QString song = QString(songInfo.SongTitle).toLower();

    // replace stop words (see http://www.chartlyrics.com/api.aspx STOP WORDS)
    // french words
    QRegExp frenchStopWords("\\s?(le|la|les|du|des|de|chanson|encore|autre|ici|là|mauvaise)\\s+");
//    while(frenchStopWords.indexIn(song) != -1)
    song = song.replace(frenchStopWords, " ");

    qDebug() << "Song" << song;


    QString url = baseUrl.arg(artist).arg(song);

    m_mainWindow->ui()->textEditLyrics->clear();
    m_mainWindow->ui()->textEditLyrics->setAlignment(Qt::AlignCenter);


    m_nam->get(QNetworkRequest(url));
    qDebug() << "Lyrics URL: " << url;
}

//-------------------------------------
void LyricsController::onLyricsLoaded(QNetworkReply* reply)
{
    bool found = false;
    QString lyrics = tr("Lyrics not found");
    QByteArray data = reply->readAll();

    QDomDocument doc;
    doc.setContent(data);
    QDomElement root = doc.documentElement();
    QDomNodeList children = root.childNodes();
    for(int i = 0; i < children.count(); ++i){
        QDomElement elem = children.at(i).toElement();
        if(elem.tagName() == "Lyric"){
            if(!elem.text().isEmpty()) {
                lyrics = elem.text();
                found = true;
            }
        }
    }
    bool autoShow = QSettings().value("automaticallyShowLyricsPane", true).toBool();

    m_mainWindow->ui()->textEditLyrics->setText("<p>" + lyrics.replace("\n", "<br>") + "</p>");
    m_mainWindow->ui()->textEditLyrics->setAlignment(Qt::AlignCenter);
    if(autoShow){
        m_mainWindow->ui()->dockWidgetLyrics->setVisible(found);
    }
}
