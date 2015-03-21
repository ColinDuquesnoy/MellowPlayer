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

#ifndef COOKIEJAR_H
#define COOKIEJAR_H

#include <QtNetwork>
#include <QtCore>

typedef QMap<QString, QVariant> CookieMap;
Q_DECLARE_METATYPE(CookieMap)

/*!
 * \brief The CookieJar class manages the cookies cache.
 *
 * It stores the cookies in a CookieMap using QSettings. There is a function
 * to purge the cookies.
 */
class CookieJar : public QNetworkCookieJar
{

public:
    explicit CookieJar(const QString& serviceName, QObject *parent=NULL);

    /*!
     * @brief Purge the cookies cache.
     */
    void purgeCookies();

    /*!
     * \brief Adds the cookies in the cookieList to this cookie jar.
     */
    bool setCookiesFromUrl(const QList<QNetworkCookie> &cookieList,
                           const QUrl &url);

private:
    void loadCookies();
    QString serviceName;
};

#endif // COOKIEJAR_H
