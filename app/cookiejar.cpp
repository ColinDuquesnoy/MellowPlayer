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

#include "cookiejar.h"

//---------------------------------------------------------
CookieJar::CookieJar(QObject* parent):
    QNetworkCookieJar(parent)
{
    this->loadCookies();
}

//---------------------------------------------------------
void CookieJar::purgeCookies()
{
    QSettings().clear();
    // reset all cookies to an empty byte array.
    this->loadCookies();
}

//---------------------------------------------------------
bool CookieJar::setCookiesFromUrl(const QList<QNetworkCookie> &cookieList,
                                  const QUrl &url)
{
    // Update existing cookies and add new cookies to the map
    CookieMap cookieMap = QSettings().value("cookies", CookieMap()).toMap();
    foreach (QNetworkCookie cookie, cookieList) {
        cookieMap[cookie.name()] = cookie.toRawForm();
    }
    QSettings().setValue("cookies", cookieMap);
    return QNetworkCookieJar::setCookiesFromUrl(cookieList, url);
}

//---------------------------------------------------------
void CookieJar::loadCookies()
{
    // set all cookies from the cookie map
    CookieMap map = QSettings().value("cookies", CookieMap()).toMap();
    // we need to convert qvariants to qbytearrays and separate them with
    // a '\n' so that we easily join each byte array into a big array that
    // the base class can use to restore the cloud service cookies.
    QList<QVariant> variantValues = map.values();
    QList<QByteArray> values;
    foreach(QVariant value, variantValues){
        values.append(value.toByteArray());
        values.append("\n");
    }
    qDebug() << "Loading " << map.count() << " cookies";
    this->setAllCookies(QNetworkCookie::parseCookies(values.join()));
}
