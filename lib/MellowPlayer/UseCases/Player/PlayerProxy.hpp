#pragma once

#include <memory>
#include <QObject>
#include <MellowPlayer/Macros.hpp>
#include "IPlayer.hpp"
#include "Song.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class Player;
class PlayersService;
class Plugin;
class PluginManager;

class PlayerProxy: public IPlayer {
    Q_OBJECT
public:
    PlayerProxy(PlayersService& playersService, PluginManager& pluginManager);

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

    Song* getCurrentSong() override;
    double getPosition() const override;
    PlaybackStatus getPlaybackStatus() const override;
    bool getCanSeek() const override;
    bool getCanGoNext() const override;
    bool getCanGoPrevious() const override;
    bool getCanAddToFavorites() const override;
    double getVolume() const override;
    QString getServiceName() const override;

private slots:
    void onCurrentPluginChanged(UseCases::Plugin* plugin);

private:
    PlayersService& players;
    PluginManager& pluginManager;
    Song nullSong;

    std::shared_ptr<Player> currentPlayer;
};

END_MELLOWPLAYER_NAMESPACE
