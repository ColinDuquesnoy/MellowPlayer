#pragma once

#include <MellowPlayer/Macros.hpp>
#include "Song.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class IPlayer: public QObject
{
    Q_OBJECT
    Q_PROPERTY(Song* currentSong READ getCurrentSong NOTIFY currentSongChanged)
    Q_PROPERTY(double position READ getPosition NOTIFY positionChanged)
    Q_PROPERTY(PlaybackStatus playbackStatus READ getPlaybackStatus NOTIFY playbackStatusChanged)
    Q_PROPERTY(bool canSeek READ getCanSeek NOTIFY canSeekChanged)
    Q_PROPERTY(bool canGoNext READ getCanGoNext NOTIFY canGoNextChanged)
    Q_PROPERTY(bool canGoPrevious READ getCanGoPrevious NOTIFY canGoPreviousChanged)
    Q_PROPERTY(bool canAddToFavorites READ getCanAddToFavorites NOTIFY canAddToFavoritesChanged)
    Q_PROPERTY(int volume READ getVolume NOTIFY volumeChanged)
public:
    enum class PlaybackStatus {
        Stopped = 0,
        Playing = 1,
        Paused = 2,
        Buffering = 3
    };
    Q_ENUMS(PlaybackStatus)

    virtual ~IPlayer() = default;

    virtual void togglePlayPause() = 0;
    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void next() = 0;
    virtual void previous() = 0;
    virtual void seekToPosition(double position) = 0;
    virtual void setVolume(double volume) = 0;
    virtual Song* getCurrentSong() = 0;
    virtual void toggleFavoriteSong() = 0;
    virtual void addToFavorites() = 0;
    virtual void removeFromFavorites() = 0;

    virtual double getPosition() const = 0;
    virtual PlaybackStatus getPlaybackStatus() const = 0;
    virtual bool getCanSeek() const = 0;
    virtual bool getCanGoNext() const = 0;
    virtual bool getCanGoPrevious() const = 0;
    virtual bool getCanAddToFavorites() const = 0;
    virtual double getVolume() const = 0;

signals:
    void currentSongChanged(Song* song);
    void positionChanged();
    void playbackStatusChanged();
    void canSeekChanged();
    void canGoNextChanged();
    void canGoPreviousChanged();
    void canAddToFavoritesChanged();
    void volumeChanged();
};

END_MELLOWPLAYER_NAMESPACE

Q_DECLARE_METATYPE(MellowPlayer::UseCases::IPlayer::PlaybackStatus);
