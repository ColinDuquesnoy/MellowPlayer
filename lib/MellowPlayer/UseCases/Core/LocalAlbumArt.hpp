#pragma once

#include "../Interfaces/IPlayer.hpp"
#include "../Interfaces/IAlbumArtDownloader.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class LocalAlbumArt: public QObject {
    Q_OBJECT
    Q_PROPERTY(QString url READ getUrl NOTIFY urlChanged)
public:
    LocalAlbumArt(IPlayer& player, IAlbumArtDownloader& downloader);

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
