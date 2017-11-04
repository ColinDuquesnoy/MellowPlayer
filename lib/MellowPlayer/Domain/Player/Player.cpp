#include "Player.hpp"
#include "Song.hpp"
#include <QVariantMap>
#include <QTimer>
#include <MellowPlayer/Domain/Logging/LoggingManager.hpp>
#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServiceScript.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain;
using namespace std;

Player::Player(StreamingService& streamingService)
        : logger_(LoggingManager::logger("Player-" + streamingService.name().toStdString())),
          currentSong_(nullptr),
          streamingService_(streamingService),
          streamingServiceScript_(*streamingService.script()),
          refreshTimer_(new QTimer())
{
    connect(refreshTimer_, &QTimer::timeout, this, &Player::refresh);
    connect(&streamingService, &StreamingService::scriptChanged, this, &Player::loadPlugin);
    refreshTimer_->setInterval(100);
}

Player::~Player() = default;

void Player::togglePlayPause()
{
    LOG_TRACE(logger_, "togglePlayePause");
    if (playbackStatus_ == PlaybackStatus::Playing)
        pause();
    else
        play();
}

void Player::play()
{
    LOG_DEBUG(logger_, "play()");
    emit runJavascriptRequested(streamingServiceScript_.play());
}

void Player::pause()
{
    LOG_DEBUG(logger_, "pause()");
    emit runJavascriptRequested(streamingServiceScript_.pause());
}

void Player::next()
{
    LOG_DEBUG(logger_, "next()");
    emit runJavascriptRequested(streamingServiceScript_.next());
}

void Player::previous()
{
    LOG_DEBUG(logger_, "previous()");
    emit runJavascriptRequested(streamingServiceScript_.previous());
}

void Player::seekToPosition(double value)
{
    LOG_DEBUG(logger_, "seekToPosition(" << value << ")");
    emit runJavascriptRequested(streamingServiceScript_.seekToPosition(value));
    setPosition(value);
}

void Player::setVolume(double value)
{
    LOG_TRACE(logger_, "setVolume(" << value << ")");
    emit runJavascriptRequested(streamingServiceScript_.setVolume(value));
}

void Player::toggleFavoriteSong()
{
    LOG_TRACE(logger_, "toggleFavoriteSong()");
    if (currentSong_ == nullptr)
        return;

    if (currentSong_->isFavorite())
        removeFromFavorites();
    else
        addToFavorites();
}

void Player::addToFavorites()
{
    LOG_TRACE(logger_, "addToFavorites()");
    emit runJavascriptRequested(streamingServiceScript_.addToFavorites());
}

void Player::removeFromFavorites()
{
    LOG_TRACE(logger_, "removeFromFavorites()");
    emit runJavascriptRequested(streamingServiceScript_.removeFromFavorites());
}

Song* Player::currentSong()
{
    return currentSong_.get();
}

double Player::position() const
{
    return position_;
}

PlaybackStatus Player::playbackStatus() const
{
    return playbackStatus_;
}

bool Player::canSeek() const
{
    return canSeek_;
}

bool Player::canGoNext() const
{
    return canGoNext_;
}

bool Player::canGoPrevious() const
{
    return canGoPrevious_;
}

bool Player::canAddToFavorites() const
{
    return canAddToFavorites_;
}

double Player::volume() const
{
    return volume_;
}

QString Player::serviceName() const
{
    return streamingService_.name();
}

void Player::start()
{
    LOG_DEBUG(logger_, "start()");
    isRunning_ = true;
    emit isRunningChanged();
}

void Player::stop()
{
    LOG_DEBUG(logger_, "stop()");
    isRunning_ = false;
    emit isRunningChanged();
    refreshTimer_->stop();
}

bool Player::isRunning() const
{
    return isRunning_;
}

void Player::refresh()
{
    LOG_TRACE(logger_, "refresh()");
    emit updateRequested(streamingServiceScript_.update());
    refreshTimer_->start();
}

void Player::setUpdateResults(const QVariant& results)
{
    LOG_TRACE(logger_, "setUpdateResults()");
    QVariantMap resultsMap = results.toMap();

    QString uniqueId = resultsMap.value("songId").toString().replace("-", "");
    QString title = resultsMap.value("songTitle").toString().replace("\n", "").trimmed();
    QString artist = resultsMap.value("artistName").toString().replace("\n", "").trimmed();
    QString album = resultsMap.value("albumTitle").toString().replace("\n", "").trimmed();
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

void Player::suspend()
{
    LOG_DEBUG(logger_, "suspend()");
    suspendedState_ = playbackStatus_;
    if (playbackStatus_ == PlaybackStatus::Playing) {
        pause();
        playbackStatus_ = PlaybackStatus::Paused;
    }
    refreshTimer_->stop();
}

void Player::resume()
{
    LOG_DEBUG(logger_, "resume()");
    if (suspendedState_ == PlaybackStatus::Playing) {
        play();
    }
    refreshTimer_->start();
}

void Player::setCurrentSong(unique_ptr<Song>& song)
{
    LOG_TRACE(logger_, "setCurrentSong()");
    if (currentSong_ != nullptr && *currentSong_ == *song) {
        currentSong_->setDuration(song->duration());
        currentSong_->setFavorite(song->isFavorite());
        currentSong_->setArtUrl(song->artUrl());
        return;
    }

    currentSong_ = std::move(song);
    LOG_DEBUG(logger_, "song changed: " + (currentSong_->isValid() ? currentSong_->toString() : "NullSong"));
    LOG_TRACE(logger_, "song id:" + currentSong_->uniqueId());
    LOG_TRACE(logger_, "artUrl:" + currentSong_->artUrl());
    emit currentSongChanged(currentSong_.get());
}

void Player::setPosition(double value)
{
    if (value == position_)
        return;

    position_ = value;
    emit positionChanged();
}

void Player::setPlaybackStatus(PlaybackStatus value)
{
    if (value == playbackStatus_)
        return;

    playbackStatus_ = value;
    LOG_DEBUG(logger_, "playback status changed: " << static_cast<int>(value));
    emit playbackStatusChanged();
    emit isPlayingChanged();
    emit isStoppedChanged();
}

void Player::setCanSeek(bool value)
{
    if (value == canSeek_)
        return;

    canSeek_ = value;
    emit canSeekChanged();
}

void Player::setCanGoNext(bool value)
{
    if (value == canGoNext_)
        return;

    canGoNext_ = value;
    emit canGoNextChanged();
}

void Player::setCanGoPrevious(bool value)
{
    if (value == canGoPrevious_)
        return;

    canGoPrevious_ = value;
    emit canGoPreviousChanged();
}

void Player::setCanAddToFavorites(bool value)
{
    if (value == canAddToFavorites_)
        return;

    canAddToFavorites_ = value;
    emit canAddToFavoritesChanged();
}

void Player::setCurrentVolume(double value)
{
    if (value == volume_)
        return;

    volume_ = value;
    emit volumeChanged();
}

bool Player::operator==(const Player& other) const
{
    return streamingService_ == other.streamingService_;
}

bool Player::operator!=(const Player& other) const
{
    return !operator==(other);
}

bool Player::isPlaying() const
{
    return playbackStatus_ == PlaybackStatus::Playing;
}

bool Player::isStopped() const
{
    return playbackStatus_ == PlaybackStatus::Stopped;
}

void Player::loadPlugin()
{
    emit runJavascriptRequested(streamingServiceScript_.constants() + "\n" + streamingServiceScript_.code());
    refreshTimer_->start();
}
