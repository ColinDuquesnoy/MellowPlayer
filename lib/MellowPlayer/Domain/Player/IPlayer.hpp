#pragma once

#include <QObject>

namespace MellowPlayer::Domain
{
    class Song;

    enum class PlaybackStatus
    {
        Stopped = 0,
        Playing = 1,
        Paused = 2,
        Buffering = 3,
    };

    class IPlayer : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(Domain::Song* currentSong READ currentSong NOTIFY currentSongChanged)
        Q_PROPERTY(double position READ position NOTIFY positionChanged)
        Q_PROPERTY(PlaybackStatus playbackStatus READ playbackStatus NOTIFY playbackStatusChanged)
        Q_PROPERTY(bool canSeek READ canSeek NOTIFY canSeekChanged)
        Q_PROPERTY(bool canGoNext READ canGoNext NOTIFY canGoNextChanged)
        Q_PROPERTY(bool canGoPrevious READ canGoPrevious NOTIFY canGoPreviousChanged)
        Q_PROPERTY(bool canAddToFavorites READ canAddToFavorites NOTIFY canAddToFavoritesChanged)
        Q_PROPERTY(int volume READ volume NOTIFY volumeChanged)
        Q_PROPERTY(QString serviceName READ serviceName CONSTANT)
        Q_PROPERTY(bool isPlaying READ isPlaying NOTIFY isPlayingChanged)
        Q_PROPERTY(bool isStopped READ isStopped NOTIFY isStoppedChanged)
    public:
        Q_ENUMS(PlaybackStatus)
        IPlayer() = default;
        virtual ~IPlayer() = default;

        virtual void togglePlayPause() = 0;
        virtual void play() = 0;
        virtual void pause() = 0;
        virtual void next() = 0;
        virtual void previous() = 0;
        virtual void seekToPosition(double position) = 0;
        virtual void setVolume(double volume) = 0;
        virtual Domain::Song* currentSong() = 0;
        virtual void toggleFavoriteSong() = 0;
        virtual void addToFavorites() = 0;
        virtual void removeFromFavorites() = 0;

        virtual double position() const = 0;
        virtual PlaybackStatus playbackStatus() const = 0;
        virtual bool canSeek() const = 0;
        virtual bool canGoNext() const = 0;
        virtual bool canGoPrevious() const = 0;
        virtual bool canAddToFavorites() const = 0;
        virtual double volume() const = 0;
        virtual QString serviceName() const = 0;
        virtual bool isPlaying() const = 0;
        virtual bool isStopped() const = 0;

    signals:
        void currentSongChanged(Domain::Song* song);
        void positionChanged();
        void playbackStatusChanged();
        void canSeekChanged();
        void canGoNextChanged();
        void canGoPreviousChanged();
        void canAddToFavoritesChanged();
        void volumeChanged();
        void isPlayingChanged();
        void isStoppedChanged();
    };
}

Q_DECLARE_METATYPE(MellowPlayer::Domain::PlaybackStatus);
