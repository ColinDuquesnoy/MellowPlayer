#include <QDebug>
#include "Player.hpp"

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
using namespace std;

Player::Player(StreamingService& streamingService)
    : currentSong(nullptr), streamingService(streamingService), pluginScript(*streamingService.getScript()) {

}

void Player::togglePlayPause() {
    if (playbackStatus == PlaybackStatus::Playing)
        pause();
    else
        play();
}

void Player::play() {
    if (playbackStatus != PlaybackStatus::Playing) {
        emit runJavascriptRequested(pluginScript.play());
        setPlaybackStatus(PlaybackStatus::Playing);
    }
}

void Player::pause() {
    if (playbackStatus == PlaybackStatus::Playing) {
        emit runJavascriptRequested(pluginScript.pause());
        setPlaybackStatus(PlaybackStatus::Paused);
    }
}

void Player::next() {
    emit runJavascriptRequested(pluginScript.next());
}

void Player::previous() {
    emit runJavascriptRequested(pluginScript.previous());
}

void Player::seekToPosition(double value) {
    emit runJavascriptRequested(pluginScript.seekToPosition(value));
}

void Player::setVolume(double volume) {
    emit runJavascriptRequested(pluginScript.setVolume(volume));
}

void Player::toggleFavoriteSong() {
    if (currentSong == nullptr)
        return;

    if (currentSong->getIsFavorite())
        removeFromFavorites();
    else
        addToFavorites();
}

void Player::addToFavorites() {
    emit runJavascriptRequested(pluginScript.addToFavorites());
}

void Player::removeFromFavorites() {
    emit runJavascriptRequested(pluginScript.removeFromFavorites());
}

Song* Player::getCurrentSong() {
    return currentSong.get();
}

double Player::getPosition() const {
    return position;
}

IPlayer::PlaybackStatus Player::getPlaybackStatus() const {
    return playbackStatus;
}

bool Player::getCanSeek() const {
    return canSeek;
}

bool Player::getCanGoNext() const {
    return canGoNext;
}

bool Player::getCanGoPrevious() const {
    return canGoPrevious;
}

bool Player::getCanAddToFavorites() const {
    return canAddToFavorites;
}

double Player::getVolume() const {
    return volume;
}

void Player::initialize() {
    emit runJavascriptRequested(pluginScript.getConstants() + "\n" + pluginScript.getCode());
}

void Player::refresh() {
    emit updateRequested(pluginScript.update());
}

void Player::setUpdateResults(const QVariant& results) {
    QVariantMap resultsMap = results.toMap();

    QString uniqueId = resultsMap.value("songId").toString();
    QString title = resultsMap.value("songTitle").toString();
    QString artist = resultsMap.value("artistName").toString();
    QString album = resultsMap.value("albumTitle").toString();
    QString artUrl = resultsMap.value("artUrl").toString();
    double duration = resultsMap.value("duration").toDouble();
    bool isFavorite = resultsMap.value("isFavorite").toBool();
    auto song = make_unique<Song>(uniqueId, title, artist, album, artUrl, duration, isFavorite);
    setCurrentSong(song);

    setPosition(resultsMap.value("position").toDouble());
    setPlaybackStatus(static_cast<PlaybackStatus>(resultsMap.value("playbackStatus").toInt()));
    setCanSeek(resultsMap.value("canSeek").toBool());
    setCanGoNext(resultsMap.value("canGoNext").toBool());
    setCanGoPrevious(resultsMap.value("canGoPrevious").toBool());
    setCanAddToFavorites(resultsMap.value("canAddToFavorites").toBool());
    setCurrentVolume(resultsMap.value("volume").toDouble());
}

void Player::suspend() {
    suspendedState = playbackStatus;
    pause();
}

void Player::resume() {
    if (suspendedState == PlaybackStatus::Playing)
        play();
}

void Player::setCurrentSong(unique_ptr<Song>& song) {
    if (currentSong != nullptr && *currentSong == *song) {
        currentSong->setDuration(song->getDuration());
        currentSong->setIsFavorite(song->getIsFavorite());
        return;
    }

    currentSong = std::move(song);
    emit currentSongChanged(currentSong.get());
}

void Player::setPosition(double value) {
    if (value == position)
        return;
    
    position = value;
    emit positionChanged();        
}

void Player::setPlaybackStatus(PlaybackStatus value) {
    if (value == playbackStatus)
        return;

    playbackStatus = value;
    emit playbackStatusChanged();
}

void Player::setCanSeek(bool value) {
    if (value == canSeek)
        return;

    canSeek = value;
    emit canSeekChanged();
}

void Player::setCanGoNext(bool value) {
    if (value == canGoNext)
        return;

    canGoNext = value;
    emit canGoNextChanged();
}

void Player::setCanGoPrevious(bool value) {
    if (value == canGoPrevious)
        return;

    canGoPrevious = value;
    emit canGoPreviousChanged();
}

void Player::setCanAddToFavorites(bool value) {
    if (value == canAddToFavorites)
        return;

    canAddToFavorites = value;
    emit canAddToFavoritesChanged();
}

void Player::setCurrentVolume(double value) {
    if (value == volume)
        return;

    volume = value;
    emit volumeChanged();
}
