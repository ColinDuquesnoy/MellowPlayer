#include <QtNetwork>
#include "mellowplayer/urldownloader.h"


UrlDownloader::UrlDownloader(QObject *parent):
    QObject(parent),
    nam(NULL)
{
}

void UrlDownloader::download(const QString &url, const QString &destination)
{
    this->nam = new QNetworkAccessManager(this);
    this->fileUrl = destination;
    connect(this->nam, &QNetworkAccessManager::finished,
            this, &UrlDownloader::onDownloadFinished);
    this->nam->get(QNetworkRequest(QUrl(url)));
    qDebug() << "Downloading " << url << " to " << destination;
}

void UrlDownloader::onDownloadFinished(QNetworkReply *reply)
{
    qDebug() << "Download finished: " << this->fileUrl;
    QFile file(this->fileUrl);
    if(file.open(QIODevice::WriteOnly))
    {
        file.write(reply->readAll());
        file.close();
    }
    emit this->finished(this->fileUrl);
}
