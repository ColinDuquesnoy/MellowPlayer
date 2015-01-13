#ifndef URLDOWNLOADER
#define URLDOWNLOADER

#include <QtCore>
#include "mellowplayer/exports.h"

class QNetworkAccessManager;
class QNetworkReply;

class DLL_EXPORT UrlDownloader: public QObject
{
    Q_OBJECT
public:
    explicit UrlDownloader(QObject* parent=NULL);
    void download(const QString& url, const QString& destination);
signals:
    void finished(const QString& fileUrl);
private slots:
    void onDownloadFinished(QNetworkReply* reply);
private:
    QNetworkAccessManager* nam;
    QString fileUrl;
};

#endif // URLDOWNLOADER

