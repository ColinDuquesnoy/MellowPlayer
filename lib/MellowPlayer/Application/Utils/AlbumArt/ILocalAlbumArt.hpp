#pragma once

#include <QObject>
#include <MellowPlayer/Macros.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(Application, Song)

BEGIN_MELLOWPLAYER_NAMESPACE(Application)

class ILocalAlbumArt: public QObject {
    Q_OBJECT
    Q_PROPERTY(QString url READ getUrl NOTIFY urlChanged)
public:
    virtual ~ILocalAlbumArt();
    virtual const QString& getUrl() const = 0;
    virtual bool isSongArtReady(const Application::Song& song) = 0;

signals:
    void urlChanged();
};

END_MELLOWPLAYER_NAMESPACE
