#include "PlayerProxy.hpp"

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)

PlayerProxy::PlayerProxy(StreamingServicesManager& streamingServicesManager)
    : streamingServicesManager(streamingServicesManager), currentPlayer(nullptr) {
    connect(&streamingServicesManager, &StreamingServicesManager::currentServiceChanged,
            this, &PlayerProxy::onCurrentServiceChanged);
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

IPlayer::PlaybackStatus PlayerProxy::getPlaybackStatus() const {
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

void PlayerProxy::onCurrentServiceChanged(StreamingService* service) {
    auto player = service->getPlayer();

    if (player != currentPlayer) {
        if (currentPlayer != nullptr) {
            disconnect(currentPlayer, &Player::currentSongChanged, this, &PlayerProxy::currentSongChanged);
            disconnect(currentPlayer, &Player::positionChanged, this, &PlayerProxy::positionChanged);
            disconnect(currentPlayer, &Player::playbackStatusChanged, this, &PlayerProxy::playbackStatusChanged);
            disconnect(currentPlayer, &Player::canSeekChanged, this, &PlayerProxy::canSeekChanged);
            disconnect(currentPlayer, &Player::canGoNextChanged, this, &PlayerProxy::canGoNextChanged);
            disconnect(currentPlayer, &Player::canGoPreviousChanged, this, &PlayerProxy::canGoPreviousChanged);
            disconnect(currentPlayer, &Player::canAddToFavoritesChanged, this, &PlayerProxy::canAddToFavoritesChanged);
            disconnect(currentPlayer, &Player::volumeChanged, this, &PlayerProxy::volumeChanged);
            currentPlayer->suspend();
        }

        currentPlayer = player;

        connect(currentPlayer, &Player::currentSongChanged, this, &PlayerProxy::currentSongChanged);
        connect(currentPlayer, &Player::positionChanged, this, &PlayerProxy::positionChanged);
        connect(currentPlayer, &Player::playbackStatusChanged, this, &PlayerProxy::playbackStatusChanged);
        connect(currentPlayer, &Player::canSeekChanged, this, &PlayerProxy::canSeekChanged);
        connect(currentPlayer, &Player::canGoNextChanged, this, &PlayerProxy::canGoNextChanged);
        connect(currentPlayer, &Player::canGoPreviousChanged, this, &PlayerProxy::canGoPreviousChanged);
        connect(currentPlayer, &Player::canAddToFavoritesChanged, this, &PlayerProxy::canAddToFavoritesChanged);
        connect(currentPlayer, &Player::volumeChanged, this, &PlayerProxy::volumeChanged);
        currentPlayer->resume();

        emit currentSongChanged(player->getCurrentSong());
        emit positionChanged();
        emit playbackStatusChanged();
        emit canSeekChanged();
        emit canGoNextChanged();
        emit canGoPreviousChanged();
        emit canAddToFavoritesChanged();
        emit volumeChanged();
    }
}
