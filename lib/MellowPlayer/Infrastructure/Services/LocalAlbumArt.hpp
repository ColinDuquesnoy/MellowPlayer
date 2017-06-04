#pragma once

#include <MellowPlayer/Application/Utils/AlbumArt/ILocalAlbumArt.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(Application, Song)
PREDECLARE_MELLOWPLAYER_CLASS(Application, IPlayer)
PREDECLARE_MELLOWPLAYER_CLASS(Application, IAlbumArtDownloader)

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class LocalAlbumArt: public Application::ILocalAlbumArt {
    Q_OBJECT
public:
    LocalAlbumArt(Application::IPlayer& player, Application::IAlbumArtDownloader& downloader);

    const QString& getUrl() const override;
    bool isSongArtReady(const Application::Song& song) override;

private slots:
    void onCurrentSongChanged(Application::Song* song);
    void onDownloadFinished(const QString& newUrl);

private:
    Application::IAlbumArtDownloader& downloader;
    QString url;
};

END_MELLOWPLAYER_NAMESPACE
