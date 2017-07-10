#pragma once

#include <memory>
#include <QObject>
#include <MellowPlayer/Macros.hpp>
#include "IPlayer.hpp"
#include "Song.hpp"

PREDECLARE_MELLOWPLAYER_CLASS(Application, StreamingService)

BEGIN_MELLOWPLAYER_NAMESPACE(Application)

class Player;
class Players;
class StreamingServicesController;

class CurrentPlayer: public IPlayer {
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

    Application::Song* getCurrentSong() override;
    double getPosition() const override;
    PlaybackStatus getPlaybackStatus() const override;
    bool getCanSeek() const override;
    bool getCanGoNext() const override;
    bool getCanGoPrevious() const override;
    bool getCanAddToFavorites() const override;
    double getVolume() const override;
    QString getServiceName() const override;
    bool isPlaying() const override;
    bool isStopped() const override;

private slots:
    void onCurrentServiceChanged(Application::StreamingService* streamingService);

private:
    Players& players;
    StreamingServicesController& streamingServices;
    Application::Song nullSong;

    std::shared_ptr<Player> currentPlayer;
};

END_MELLOWPLAYER_NAMESPACE
