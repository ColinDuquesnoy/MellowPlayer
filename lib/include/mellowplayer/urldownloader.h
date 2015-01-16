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

#ifndef URLDOWNLOADER
#define URLDOWNLOADER

#include <QtCore>

class QNetworkAccessManager;
class QNetworkReply;

/*!
 * \brief Utility class to download a file from URL.
 *
 * This class is used to retrieve album arts.
 */
class UrlDownloader: public QObject
{
    Q_OBJECT
public:
    explicit UrlDownloader(QObject* parent=NULL);

  /*!
     * \brief Downloads the given url to the specified destination.
     *
     * The finished signal will be emitted when the download has finished.
     *
     * \param url Url of the file to download
     * \param destination File destination
     */
    void download(const QString& url, const QString& destination);
signals:
    /*!
     * \brief Signal emitted when the download has finished.
     *
     * \param fileUrl File path url (on the local file system)
     */
    void finished(const QString& fileUrl);
private slots:
    void onDownloadFinished(QNetworkReply* reply);
private:
    QNetworkAccessManager* nam;
    QString fileUrl;
};

#endif // URLDOWNLOADER

