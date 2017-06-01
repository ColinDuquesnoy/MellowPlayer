#pragma once

#include <MellowPlayer/Application/Interfaces/ILocalAlbumArtService.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(Entities, Song)
PREDECLARE_MELLOWPLAYER_CLASS(Application, IPlayer)
PREDECLARE_MELLOWPLAYER_CLASS(Application, IAlbumArtDownloader)

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class LocalAlbumArtService: public Application::ILocalAlbumArtService {
    Q_OBJECT
public:
    LocalAlbumArtService(Application::IPlayer& player, Application::IAlbumArtDownloader& downloader);

    const QString& getUrl() const override;
    bool isSongArtReady(const Entities::Song& song) override;

private slots:
    void onCurrentSongChanged(Entities::Song* song);
    void onDownloadFinished(const QString& newUrl);

private:
    Application::IAlbumArtDownloader& downloader;
    QString url;
};

END_MELLOWPLAYER_NAMESPACE
