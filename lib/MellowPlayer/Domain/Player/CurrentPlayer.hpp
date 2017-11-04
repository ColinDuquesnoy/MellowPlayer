#pragma once

#include "IPlayer.hpp"
#include "Song.hpp"
#include <QObject>
#include <memory>

namespace MellowPlayer::Domain
{
    class Player;
    class Players;
    class StreamingServicesController;
    class StreamingService;

    class CurrentPlayer : public IPlayer
    {
        Q_OBJECT
    public:
        CurrentPlayer(Players& players, StreamingServicesController& streamingServices);

        Q_INVOKABLE void togglePlayPause() override;
        Q_INVOKABLE void play() override;
        Q_INVOKABLE void pause() override;
        Q_INVOKABLE void next() override;
        Q_INVOKABLE void previous() override;
        Q_INVOKABLE void seekToPosition(double position) override;
        Q_INVOKABLE void setVolume(double volume) override;
        Q_INVOKABLE void toggleFavoriteSong() override;
        Q_INVOKABLE void addToFavorites() override;
        Q_INVOKABLE void removeFromFavorites() override;

        Domain::Song* currentSong() override;
        double position() const override;
        PlaybackStatus playbackStatus() const override;
        bool canSeek() const override;
        bool canGoNext() const override;
        bool canGoPrevious() const override;
        bool canAddToFavorites() const override;
        double volume() const override;
        QString serviceName() const override;
        bool isPlaying() const override;
        bool isStopped() const override;

    private slots:
        void onCurrentServiceChanged(Domain::StreamingService* streamingService);

    private:
        Players& players_;
        StreamingServicesController& streamingServices_;
        Domain::Song nullSong_;

        std::shared_ptr<Player> currentPlayer_;
    };
}
