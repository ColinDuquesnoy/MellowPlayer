#pragma once

#include <QObject>

namespace MellowPlayer::Domain
{
    class Song;

    class ILocalAlbumArt : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString url READ url NOTIFY urlChanged)
    public:
        virtual ~ILocalAlbumArt();
        virtual const QString& url() const = 0;
        virtual bool isReady(const Domain::Song& song) = 0;

    signals:
        void urlChanged();
    };
}
