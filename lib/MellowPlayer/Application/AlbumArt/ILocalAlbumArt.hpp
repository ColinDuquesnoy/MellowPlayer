#pragma once

#include <QObject>

namespace MellowPlayer::Application
{
    class Song;

    class ILocalAlbumArt : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString url READ url NOTIFY urlChanged)
    public:
        virtual ~ILocalAlbumArt();
        virtual const QString& url() const = 0;
        virtual bool isSongArtReady(const Application::Song& song) = 0;

    signals:
        void urlChanged();
    };
}
