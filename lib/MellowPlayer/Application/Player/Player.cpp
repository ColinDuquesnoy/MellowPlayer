#include <QVariantMap>
#include <MellowPlayer/Entities/StreamingServices/StreamingServicePlugin.hpp>
#include <MellowPlayer/Entities/StreamingServices/StreamingServicePluginScript.hpp>
#include <MellowPlayer/Entities/Song.hpp>
#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include "Player.hpp"

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(Application)
using namespace std;

Player::Player(StreamingServicePlugin& plugin) :
        logger(LoggingManager::instance().getLogger("Player-" + plugin.getName().toStdString())),
        currentSong(nullptr), plugin(plugin), pluginScript(*plugin.getScript()) {

}

Player::~Player() = default;

void Player::togglePlayPause() {
    LOG_TRACE(logger, "togglePlayePause");
    if (playbackStatus == PlaybackStatus::Playing)
        pause();
    else
        play();
}

void Player::play() {
    LOG_DEBUG(logger, "play()");
    emit runJavascriptRequested(pluginScript.play());
}

void Player::pause() {
    LOG_DEBUG(logger, "pause()");
    emit runJavascriptRequested(pluginScript.pause());
}

void Player::next() {
    LOG_DEBUG(logger, "next()");
    emit runJavascriptRequested(pluginScript.next());
}

void Player::previous() {
    LOG_DEBUG(logger, "previous()");
    emit runJavascriptRequested(pluginScript.previous());
}

void Player::seekToPosition(double value) {
    LOG_DEBUG(logger, "seekToPosition(" << value << ")");
    emit runJavascriptRequested(pluginScript.seekToPosition(value));
    setPosition(value);
}

void Player::setVolume(double value) {
    LOG_TRACE(logger, "setVolume(" << value << ")");
    emit runJavascriptRequested(pluginScript.setVolume(value));
}

void Player::toggleFavoriteSong() {
    LOG_TRACE(logger, "toggleFavoriteSong()");
    if (currentSong == nullptr)
        return;

    if (currentSong->getIsFavorite())
        removeFromFavorites();
    else
        addToFavorites();
}

void Player::addToFavorites() {
    LOG_TRACE(logger, "addToFavorites()");
    emit runJavascriptRequested(pluginScript.addToFavorites());
}

void Player::removeFromFavorites() {
    LOG_TRACE(logger, "removeFromFavorites()");
    emit runJavascriptRequested(pluginScript.removeFromFavorites());
}

Song* Player::getCurrentSong() {
    return currentSong.get();
}

double Player::getPosition() const {
    return position;
}

PlaybackStatus Player::getPlaybackStatus() const {
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

QString Player::getServiceName() const {
    return plugin.getName();
}

void Player::initialize() {
    LOG_TRACE(logger, "initialize()");
    emit runJavascriptRequested(pluginScript.getConstants() + "\n" + pluginScript.getCode());
}

void Player::refresh() {
    LOG_TRACE(logger, "initialize()");
    emit updateRequested(pluginScript.update());
}

void Player::setUpdateResults(const QVariant& results) {
    LOG_TRACE(logger, "setUpdateResults()");
    QVariantMap resultsMap = results.toMap();

    QString uniqueId = resultsMap.value("songId").toString();
    QString title = resultsMap.value("songTitle").toString();
    QString artist = resultsMap.value("artistName").toString();
    QString album = resultsMap.value("albumTitle").toString();
    QString artUrl = resultsMap.value("artUrl").toString();
    double duration = resultsMap.value("duration").toDouble();
    bool isFavorite = resultsMap.value("isFavorite").toBool();
    auto song = make_unique<Song>(uniqueId, title, artist, album, artUrl, duration, isFavorite);

    PlaybackStatus status = static_cast<PlaybackStatus>(resultsMap.value("playbackStatus").toInt());
    if (status == PlaybackStatus::Paused && !song->isValid())
        status = PlaybackStatus::Stopped;
    setPlaybackStatus(status);
    setCurrentSong(song);
    setPosition(resultsMap.value("position").toDouble());
    setCanSeek(resultsMap.value("canSeek").toBool());
    setCanGoNext(resultsMap.value("canGoNext").toBool());
    setCanGoPrevious(resultsMap.value("canGoPrevious").toBool());
    setCanAddToFavorites(resultsMap.value("canAddToFavorites").toBool());
    setCurrentVolume(resultsMap.value("volume").toDouble());
}

void Player::suspend() {
    LOG_DEBUG(logger, "suspend()");
    suspendedState = playbackStatus;
    if (playbackStatus == PlaybackStatus::Playing) {
        pause();
        playbackStatus = PlaybackStatus::Paused;
    }
}

void Player::resume() {
    LOG_DEBUG(logger, "resume()");
    if (suspendedState == PlaybackStatus::Playing) {
        play();
    }
}

void Player::setCurrentSong(unique_ptr<Song>& song) {
    LOG_TRACE(logger, "setCurrentSong()");
    if (currentSong != nullptr && *currentSong == *song) {
        currentSong->setDuration(song->getDuration());
        currentSong->setIsFavorite(song->getIsFavorite());
        return;
    }

    currentSong = std::move(song);
    LOG_DEBUG(logger, "song changed: " + (currentSong->isValid() ? currentSong->toString() : "NullSong"));
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
    LOG_DEBUG(logger, "playback status changed: " << static_cast<int>(value));
    emit playbackStatusChanged();
    emit isPlayingChanged();
    emit isStoppedChanged();
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

bool Player::operator==(const Player &other) const { return plugin == other.plugin; }

bool Player::operator!=(const Player &other) const { return !operator==(other); }

bool Player::isPlaying() const {
    return playbackStatus == PlaybackStatus::Playing;
}

bool Player::isStopped() const {
    return playbackStatus == PlaybackStatus ::Stopped;
}
