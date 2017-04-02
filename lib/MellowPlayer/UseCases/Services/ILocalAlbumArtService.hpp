#pragma once

#include <QObject>
#include <MellowPlayer/Macros.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class Song;

class ILocalAlbumArtService: public QObject {
    Q_OBJECT
    Q_PROPERTY(QString url READ getUrl NOTIFY urlChanged)
public:
    virtual ~ILocalAlbumArtService();
    virtual const QString& getUrl() const = 0;
    virtual bool isSongArtReady(const Song& song) = 0;

signals:
    void urlChanged();
};

END_MELLOWPLAYER_NAMESPACE
