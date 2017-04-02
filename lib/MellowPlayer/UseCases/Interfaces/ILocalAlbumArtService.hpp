#pragma once

#include <QObject>
#include <MellowPlayer/Macros.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(Entities, Song)

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class ILocalAlbumArtService: public QObject {
    Q_OBJECT
    Q_PROPERTY(QString url READ getUrl NOTIFY urlChanged)
public:
    virtual ~ILocalAlbumArtService();
    virtual const QString& getUrl() const = 0;
    virtual bool isSongArtReady(const Entities::Song& song) = 0;

signals:
    void urlChanged();
};

END_MELLOWPLAYER_NAMESPACE
