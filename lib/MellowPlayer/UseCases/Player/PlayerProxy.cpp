#include <MellowPlayer/UseCases/Plugin/PluginManager.hpp>
#include <MellowPlayer/UseCases/Plugin/Plugin.hpp>
#include "PlayerProxy.hpp"
#include "Player.hpp"
#include "PlayersService.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)
using namespace std;

PlayerProxy::PlayerProxy(PlayersService& playersService, PluginManager& pluginManager)
    : players(playersService), pluginManager(pluginManager), currentPlayer(nullptr) {

    connect(&pluginManager, &PluginManager::currentPluginChanged,
            this, &PlayerProxy::onCurrentPluginChanged);

    if(pluginManager.getCurrent() != nullptr)
        onCurrentPluginChanged(pluginManager.getCurrent());
}

void PlayerProxy::togglePlayPause() {
    if (currentPlayer)
        currentPlayer->togglePlayPause();
}

void PlayerProxy::play() {
    if (currentPlayer)
        currentPlayer->play();
}

void PlayerProxy::pause() {
    if (currentPlayer)
        currentPlayer->pause();
}

void PlayerProxy::next() {
    if (currentPlayer)
        currentPlayer->next();
}

void PlayerProxy::previous() {
    if (currentPlayer)
        currentPlayer->previous();
}

void PlayerProxy::seekToPosition(double position) {
    if (currentPlayer)
        currentPlayer->seekToPosition(position);
}

void PlayerProxy::setVolume(double volume) {
    if (currentPlayer)
        currentPlayer->setVolume(volume);
}

void PlayerProxy::toggleFavoriteSong() {
    if (currentPlayer)
        currentPlayer->toggleFavoriteSong();
}

void PlayerProxy::addToFavorites() {
    if (currentPlayer)
        currentPlayer->addToFavorites();
}

void PlayerProxy::removeFromFavorites() {
    if (currentPlayer)
        currentPlayer->removeFromFavorites();
}

Song* PlayerProxy::getCurrentSong() {
    if (currentPlayer != nullptr && currentPlayer->getCurrentSong() != nullptr)
        return currentPlayer->getCurrentSong();
    return &nullSong;
}

double PlayerProxy::getPosition() const {
    if (currentPlayer)
        return currentPlayer->getPosition();
    return 0;
}

PlaybackStatus PlayerProxy::getPlaybackStatus() const {
    if (currentPlayer)
        return currentPlayer->getPlaybackStatus();
    return PlaybackStatus::Stopped;
}

bool PlayerProxy::getCanSeek() const {
    if (currentPlayer)
        return currentPlayer->getCanSeek();
    return false;
}

bool PlayerProxy::getCanGoNext() const {
    if (currentPlayer)
        return currentPlayer->getCanGoNext();
    return false;
}

bool PlayerProxy::getCanGoPrevious() const {
    if (currentPlayer)
        return currentPlayer->getCanGoPrevious();
    return false;
}

bool PlayerProxy::getCanAddToFavorites() const {
    if (currentPlayer)
        return currentPlayer->getCanAddToFavorites();
    return false;
}

double PlayerProxy::getVolume() const {
    if (currentPlayer)
        return currentPlayer->getVolume();
    return 0;
}

void PlayerProxy::onCurrentPluginChanged(Plugin* plugin) {
    if (plugin == nullptr)
        return;
    auto player = players.get(plugin->getName());
    if (player != currentPlayer) {
        if (currentPlayer != nullptr) {
            disconnect(currentPlayer.get(), &Player::currentSongChanged, this, &PlayerProxy::currentSongChanged);
            disconnect(currentPlayer.get(), &Player::positionChanged, this, &PlayerProxy::positionChanged);
            disconnect(currentPlayer.get(), &Player::playbackStatusChanged, this, &PlayerProxy::playbackStatusChanged);
            disconnect(currentPlayer.get(), &Player::canSeekChanged, this, &PlayerProxy::canSeekChanged);
            disconnect(currentPlayer.get(), &Player::canGoNextChanged, this, &PlayerProxy::canGoNextChanged);
            disconnect(currentPlayer.get(), &Player::canGoPreviousChanged, this, &PlayerProxy::canGoPreviousChanged);
            disconnect(currentPlayer.get(), &Player::canAddToFavoritesChanged, this, &PlayerProxy::canAddToFavoritesChanged);
            disconnect(currentPlayer.get(), &Player::volumeChanged, this, &PlayerProxy::volumeChanged);
            currentPlayer->suspend();
        }

        currentPlayer = player;

        connect(currentPlayer.get(), &Player::currentSongChanged, this, &PlayerProxy::currentSongChanged);
        connect(currentPlayer.get(), &Player::positionChanged, this, &PlayerProxy::positionChanged);
        connect(currentPlayer.get(), &Player::playbackStatusChanged, this, &PlayerProxy::playbackStatusChanged);
        connect(currentPlayer.get(), &Player::canSeekChanged, this, &PlayerProxy::canSeekChanged);
        connect(currentPlayer.get(), &Player::canGoNextChanged, this, &PlayerProxy::canGoNextChanged);
        connect(currentPlayer.get(), &Player::canGoPreviousChanged, this, &PlayerProxy::canGoPreviousChanged);
        connect(currentPlayer.get(), &Player::canAddToFavoritesChanged, this, &PlayerProxy::canAddToFavoritesChanged);
        connect(currentPlayer.get(), &Player::volumeChanged, this, &PlayerProxy::volumeChanged);
        currentPlayer->resume();

        emit currentSongChanged(currentPlayer->getCurrentSong());
        emit positionChanged();
        emit playbackStatusChanged();
        emit canSeekChanged();
        emit canGoNextChanged();
        emit canGoPreviousChanged();
        emit canAddToFavoritesChanged();
        emit volumeChanged();
    }
}

QString PlayerProxy::getServiceName() const {
    if (currentPlayer)
        return currentPlayer->getServiceName();
    return "";
}
