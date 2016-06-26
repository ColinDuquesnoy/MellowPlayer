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
    connect(m_mainWindow->ui()->dockWidgetLyrics, &QDockWidget::visibilityChanged, this, &LyricsController::showLyricsPane);
    showLyricsPane(false);

    m_mainWindow->ui()->textEditLyrics->setAlignment(Qt::AlignCenter);
}

//-------------------------------------
void LyricsController::saveState()
{
    QSettings().setValue("interface/lyricsPaneVisible", m_mainWindow->ui()->dockWidgetLyrics->isVisible());
}

//-------------------------------------
void LyricsController::showLyricsPane(bool show)
{
    if(!m_mainWindow)
        return;
    m_mainWindow->ui()->actionShow_lyrics->blockSignals(true);
    m_mainWindow->ui()->actionShow_lyrics->setChecked(show);
    m_mainWindow->ui()->actionShow_lyrics->blockSignals(false);

    m_mainWindow->ui()->dockWidgetLyrics->blockSignals(true);
    m_mainWindow->ui()->dockWidgetLyrics->setVisible(show);
    m_mainWindow->ui()->dockWidgetLyrics->blockSignals(false);
}

//-------------------------------------
void LyricsController::onPageChanged(int page)
{
    if(page == PAGE_WEB){
        // restore state of lyrics pane
        bool autoShow = QSettings().value("interface/automaticallyShowLyricsPane", false).toBool();
        bool lyricsPaneVisible = QSettings().value("interface/lyricsPaneVisible", false).toBool();
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

    // french stop words (from http://www.ranks.nl/stopwords/french)
    QRegExp frenchStopWords(
        "\\b(alors|au|aucuns|aussi|autre|avant|avec|avoir|bon|car|ce|cela|ces|ceux|chaque|ci|comme|comment|dans|de|des|du"
        "|dedans|dehors|depuis|devrait|doit|donc|dos|début|elle|elles|en|encore|essai|est|et|eu|fait|faites|fois|font|"
        "hors|ici|il|ils|je|juste|la|là|le|les|leur|là|ma|maintenant|mais|mes|mine|moins|mon|mot|même|ni|nommés|notre|nous"
        "|ou|où|par|parce|pas|peut|peu|plupart|pour|pourquoi|chanson|que|quel|quelle|quelles|quels|qui|sa|sans|ses|"
        "seulement|si|sien|son|sont|sous|soyez|sujet|sur|ta|tandis|tellement|tels|tes|ton|tous|tout|trop|très|tu|"
        "voient|vont|votre|vous|vu|ça|étaient|état|étions|été|être|je|suis|mauvais|mauvaise|l'|d'|ne|n'|à|un|une)\\b");
    song = song.replace(frenchStopWords, " ");

    // spanish stop words (from http://www.ranks.nl/stopwords/spanish)
    QRegExp spanishStopWord(
        "\\b(un|una|unas|unos|uno|sobre|todo|también|tras|otro|algún|alguno|alguna|algunos|algunas|ser|es|soy|eres|"
        "somos|sois|estoy|esta|estamos|estais|estan|como|en|para|atras|porque|por|qué|estado|estaba|ante|antes|siendo|"
        "ambos|pero|por|poder|puede|puedo|podemos|podeis|pueden|fui|fue|fuimos|fueron|hacer|hago|hace|hacemos|haceis|"
        "hacen|cada|fin|incluso|primero|desde|conseguir|consigo|consigue|consigues|conseguimos|consiguen|ir|voy|va|"
        "vamos|vais|van|vaya|gueno|ha|tener|tengo|tiene|tenemos|teneis|tienen|el|la|lo|las|los|su|aqui|mio|tuyo|ellos|"
        "ellas|nos|nosotros|vosotros|vosotras|si|dentro|solo|solamente|saber|sabes|sabe|sabemos|sabeis|saben|ultimo|"
        "largo|bastante|haces|muchos|aquellos|aquellas|sus|entonces|tiempo|verdad|verdadero|verdadera|cierto|ciertos|"
        "cierta|ciertas|intentar|intento|intenta|intentas|intentamos|intentais|intentan|dos|bajo|arriba|encima|usar|"
        "uso|usas|usa|usamos|usais|usan|emplear|empleo|empleas|emplean|ampleamos|empleais|valor|muy|era|eras|eramos|"
        "eran|modo|bien|cual|cuando|donde|mientras|quien|con|entre|sin|trabajo|trabajar|trabajas|trabaja|trabajamos|"
        "trabajais|trabajan|podria|podrias|podriamos|podrian|podriais|yo|aquel)\\b");
    song = song.replace(spanishStopWord, " ");

    qDebug() << "***** Searching for" << song;


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
    bool autoShow = QSettings().value("interface/automaticallyShowLyricsPane", false).toBool();

    m_mainWindow->ui()->textEditLyrics->setText("<p>" + lyrics.replace("\n", "<br>") + "</p>");
    m_mainWindow->ui()->textEditLyrics->setAlignment(Qt::AlignCenter);
    if(autoShow){
        showLyricsPane(found);
    }
}
