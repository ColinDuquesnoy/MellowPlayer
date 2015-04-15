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

#include "mellowplayer/cookiejar.h"

//---------------------------------------------------------
CookieJar::CookieJar(const QString &serviceName, QObject* parent):
    QNetworkCookieJar(parent),
    serviceName(serviceName)
{
    loadCookies();
}

//---------------------------------------------------------
void CookieJar::purgeCookies()
{
    QSettings().setValue("cookies-" + serviceName, CookieMap());
    loadCookies();
}

//---------------------------------------------------------
bool CookieJar::setCookiesFromUrl(const QList<QNetworkCookie> &cookieList,
                                  const QUrl &url)
{
    // Update existing cookies and add new cookies to the map
    CookieMap cookieMap = QSettings().value("cookies-" + serviceName, CookieMap()).toMap();
    foreach (QNetworkCookie cookie, cookieList) {
        cookieMap[cookie.name()] = cookie.toRawForm();
    }
    QSettings().setValue("cookies-" + serviceName, cookieMap);
    return QNetworkCookieJar::setCookiesFromUrl(cookieList, url);
}

//---------------------------------------------------------
void CookieJar::loadCookies()
{
    // set all cookies from the cookie map
    CookieMap map = QSettings().value("cookies-" + serviceName, CookieMap()).toMap();
    // we need to convert qvariants to qbytearrays and separate them with
    // a '\n' so that we easily join each byte array into a big array that
    // the base class can use to restore the streaming service cookies.
    QList<QVariant> variantValues = map.values();
    QList<QByteArray> values;
    QByteArray array;
    foreach(QVariant value, variantValues){
        array += value.toByteArray();
        array += "\n";
    }
    qDebug() << QString("Loading %1 cookies").arg(map.count());
    setAllCookies(QNetworkCookie::parseCookies(array));
}
