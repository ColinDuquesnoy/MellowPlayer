#pragma once

#include "Player.hpp"
#include "StreamingServicesManager.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class PlayerProxy: public IPlayer {
    Q_OBJECT
public:
    PlayerProxy(StreamingServicesManager& streamingServicesManager);

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

    Entities::Song* getCurrentSong() override;
    double getPosition() const override;
    PlaybackStatus getPlaybackStatus() const override;
    bool getCanSeek() const override;
    bool getCanGoNext() const override;
    bool getCanGoPrevious() const override;
    bool getCanAddToFavorites() const override;
    double getVolume() const override;

private slots:
    void onCurrentServiceChanged(StreamingService* service);

private:
    StreamingServicesManager& streamingServicesManager;
    Entities::Song nullSong;
    Player* currentPlayer;
};

END_MELLOWPLAYER_NAMESPACE
