#pragma once

#include "../Player/IPlayer.hpp"
#include "../Interfaces/IAlbumArtDownloader.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class LocalAlbumArtService: public QObject {
    Q_OBJECT
    Q_PROPERTY(QString url READ getUrl NOTIFY urlChanged)
public:
    LocalAlbumArtService(IPlayer& player, IAlbumArtDownloader& downloader);

    const QString& getUrl() const;

signals:
    void urlChanged();

private slots:
    void onCurrentSongChanged(Entities::Song* song);
    void onDownloadFinished(const QString& newUrl);

private:
    IAlbumArtDownloader& downloader;
    QString url;
};

END_MELLOWPLAYER_NAMESPACE
