#include "GithubReleasesReplyParser.hpp"
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>

using namespace MellowPlayer::Application;

void GithubReleasesReplyParser::parse(const QByteArray& replyData)
{
    stopRequested_ = false;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(replyData);
    if (!jsonDocument.isArray())
        return;
    QJsonArray array = jsonDocument.array();
    for (int releaseIndex = 0; releaseIndex < array.count(); ++releaseIndex) {
        QJsonObject obj = array.at(releaseIndex).toObject();
        QString url = obj.value("html_url").toString();
        QString version = obj.value("name").toString();
        QDate date = QDateTime::fromString(obj.value("created_at").toString(), Qt::ISODate).date();
        QString description = obj.value("body").toString();
        bool preRelease = obj.value("prerelease").toBool();
        AssetList assets;
        QJsonArray assetArray = obj.value("assets").toArray();
        for (int assetIndex = 0; assetIndex < assetArray.count(); ++assetIndex) {
            QJsonObject assetObj = assetArray.at(assetIndex).toObject();
            Asset asset(assetObj.value("name").toString(), assetObj.value("browser_download_url").toString());
            assets << asset;
        }

        Release* release = new Release(url, version, date, assets, preRelease, this);

        emit ready(release);

        if (stopRequested_)
            return;
    }
}

void GithubReleasesReplyParser::stop()
{
    stopRequested_ = true;
}
