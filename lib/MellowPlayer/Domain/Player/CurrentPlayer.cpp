#include "CurrentPlayer.hpp"
#include "IPlayer.hpp"
#include "Player.hpp"
#include "Players.hpp"
#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServicesController.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain;
using namespace std;

CurrentPlayer::CurrentPlayer(Players& players, StreamingServices& streamingServices)
        : players_(players), streamingServices_(streamingServices), currentPlayer_(nullptr)
{

    connect(&streamingServices, &StreamingServices::currentChanged, this, &CurrentPlayer::onCurrentServiceChanged);

    if (streamingServices.current() != nullptr)
        onCurrentServiceChanged(streamingServices.current());
}

void CurrentPlayer::togglePlayPause()
{
    if (currentPlayer_)
        currentPlayer_->togglePlayPause();
}

void CurrentPlayer::play()
{
    if (currentPlayer_)
        currentPlayer_->play();
}

void CurrentPlayer::pause()
{
    if (currentPlayer_)
        currentPlayer_->pause();
}

void CurrentPlayer::next()
{
    if (currentPlayer_)
        currentPlayer_->next();
}

void CurrentPlayer::previous()
{
    if (currentPlayer_)
        currentPlayer_->previous();
}

void CurrentPlayer::seekToPosition(double position)
{
    if (currentPlayer_)
        currentPlayer_->seekToPosition(position);
}

void CurrentPlayer::setVolume(double volume)
{
    if (currentPlayer_)
        currentPlayer_->setVolume(volume);
}

void CurrentPlayer::toggleFavoriteSong()
{
    if (currentPlayer_)
        currentPlayer_->toggleFavoriteSong();
}

void CurrentPlayer::addToFavorites()
{
    if (currentPlayer_)
        currentPlayer_->addToFavorites();
}

void CurrentPlayer::removeFromFavorites()
{
    if (currentPlayer_)
        currentPlayer_->removeFromFavorites();
}

Song* CurrentPlayer::currentSong()
{
    if (currentPlayer_ != nullptr && currentPlayer_->currentSong() != nullptr)
        return currentPlayer_->currentSong();
    return &nullSong_;
}

double CurrentPlayer::position() const
{
    if (currentPlayer_)
        return currentPlayer_->position();
    return 0;
}

PlaybackStatus CurrentPlayer::playbackStatus() const
{
    if (currentPlayer_)
        return currentPlayer_->playbackStatus();
    return PlaybackStatus::Stopped;
}

bool CurrentPlayer::canSeek() const
{
    if (currentPlayer_)
        return currentPlayer_->canSeek();
    return false;
}

bool CurrentPlayer::canGoNext() const
{
    if (currentPlayer_)
        return currentPlayer_->canGoNext();
    return false;
}

bool CurrentPlayer::canGoPrevious() const
{
    if (currentPlayer_)
        return currentPlayer_->canGoPrevious();
    return false;
}

bool CurrentPlayer::canAddToFavorites() const
{
    if (currentPlayer_)
        return currentPlayer_->canAddToFavorites();
    return false;
}

double CurrentPlayer::volume() const
{
    if (currentPlayer_)
        return currentPlayer_->volume();
    return 0;
}

void CurrentPlayer::onCurrentServiceChanged(StreamingService* streamingService)
{
    if (streamingService == nullptr)
        return;
    auto player = players_.get(streamingService->name());
    if (player != currentPlayer_) {
        if (currentPlayer_ != nullptr) {
            disconnect(currentPlayer_.get(), &Player::currentSongChanged, this, &CurrentPlayer::currentSongChanged);
            disconnect(currentPlayer_.get(), &Player::positionChanged, this, &CurrentPlayer::positionChanged);
            disconnect(currentPlayer_.get(), &Player::playbackStatusChanged, this, &CurrentPlayer::playbackStatusChanged);
            disconnect(currentPlayer_.get(), &Player::canSeekChanged, this, &CurrentPlayer::canSeekChanged);
            disconnect(currentPlayer_.get(), &Player::canGoNextChanged, this, &CurrentPlayer::canGoNextChanged);
            disconnect(currentPlayer_.get(), &Player::canGoPreviousChanged, this, &CurrentPlayer::canGoPreviousChanged);
            disconnect(currentPlayer_.get(), &Player::canAddToFavoritesChanged, this, &CurrentPlayer::canAddToFavoritesChanged);
            disconnect(currentPlayer_.get(), &Player::volumeChanged, this, &CurrentPlayer::volumeChanged);
            disconnect(currentPlayer_.get(), &Player::isPlayingChanged, this, &CurrentPlayer::isPlayingChanged);
            disconnect(currentPlayer_.get(), &Player::isStoppedChanged, this, &CurrentPlayer::isStoppedChanged);
            currentPlayer_->suspend();
        }

        currentPlayer_ = player;

        connect(currentPlayer_.get(), &Player::currentSongChanged, this, &CurrentPlayer::currentSongChanged);
        connect(currentPlayer_.get(), &Player::positionChanged, this, &CurrentPlayer::positionChanged);
        connect(currentPlayer_.get(), &Player::playbackStatusChanged, this, &CurrentPlayer::playbackStatusChanged);
        connect(currentPlayer_.get(), &Player::canSeekChanged, this, &CurrentPlayer::canSeekChanged);
        connect(currentPlayer_.get(), &Player::canGoNextChanged, this, &CurrentPlayer::canGoNextChanged);
        connect(currentPlayer_.get(), &Player::canGoPreviousChanged, this, &CurrentPlayer::canGoPreviousChanged);
        connect(currentPlayer_.get(), &Player::canAddToFavoritesChanged, this, &CurrentPlayer::canAddToFavoritesChanged);
        connect(currentPlayer_.get(), &Player::volumeChanged, this, &CurrentPlayer::volumeChanged);
        connect(currentPlayer_.get(), &Player::isPlayingChanged, this, &CurrentPlayer::isPlayingChanged);
        connect(currentPlayer_.get(), &Player::isStoppedChanged, this, &CurrentPlayer::isStoppedChanged);
        currentPlayer_->resume();

        emit currentSongChanged(currentPlayer_->currentSong());
        emit positionChanged();
        emit playbackStatusChanged();
        emit canSeekChanged();
        emit canGoNextChanged();
        emit canGoPreviousChanged();
        emit canAddToFavoritesChanged();
        emit volumeChanged();
        emit isPlayingChanged();
        emit isStoppedChanged();
    }
}

QString CurrentPlayer::serviceName() const
{
    if (currentPlayer_)
        return currentPlayer_->serviceName();
    return "";
}

bool CurrentPlayer::isPlaying() const
{
    if (currentPlayer_)
        return currentPlayer_->isPlaying();
    return false;
}

bool CurrentPlayer::isStopped() const
{
    if (currentPlayer_)
        return currentPlayer_->isStopped();
    return true;
}
