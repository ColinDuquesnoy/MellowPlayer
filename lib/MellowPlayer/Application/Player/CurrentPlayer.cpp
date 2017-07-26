#include "CurrentPlayer.hpp"
#include "Player.hpp"
#include "Players.hpp"
#include <MellowPlayer/Application/StreamingServices/StreamingService.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Application;
using namespace std;

CurrentPlayer::CurrentPlayer(Players& players, StreamingServicesController& streamingServices)
        : players(players), streamingServices(streamingServices), currentPlayer(nullptr)
{

    connect(&streamingServices, &StreamingServicesController::currentChanged, this, &CurrentPlayer::onCurrentServiceChanged);

    if (streamingServices.getCurrent() != nullptr)
        onCurrentServiceChanged(streamingServices.getCurrent());
}

void CurrentPlayer::togglePlayPause()
{
    if (currentPlayer)
        currentPlayer->togglePlayPause();
}

void CurrentPlayer::play()
{
    if (currentPlayer)
        currentPlayer->play();
}

void CurrentPlayer::pause()
{
    if (currentPlayer)
        currentPlayer->pause();
}

void CurrentPlayer::next()
{
    if (currentPlayer)
        currentPlayer->next();
}

void CurrentPlayer::previous()
{
    if (currentPlayer)
        currentPlayer->previous();
}

void CurrentPlayer::seekToPosition(double position)
{
    if (currentPlayer)
        currentPlayer->seekToPosition(position);
}

void CurrentPlayer::setVolume(double volume)
{
    if (currentPlayer)
        currentPlayer->setVolume(volume);
}

void CurrentPlayer::toggleFavoriteSong()
{
    if (currentPlayer)
        currentPlayer->toggleFavoriteSong();
}

void CurrentPlayer::addToFavorites()
{
    if (currentPlayer)
        currentPlayer->addToFavorites();
}

void CurrentPlayer::removeFromFavorites()
{
    if (currentPlayer)
        currentPlayer->removeFromFavorites();
}

Song* CurrentPlayer::getCurrentSong()
{
    if (currentPlayer != nullptr && currentPlayer->getCurrentSong() != nullptr)
        return currentPlayer->getCurrentSong();
    return &nullSong;
}

double CurrentPlayer::getPosition() const
{
    if (currentPlayer)
        return currentPlayer->getPosition();
    return 0;
}

PlaybackStatus CurrentPlayer::getPlaybackStatus() const
{
    if (currentPlayer)
        return currentPlayer->getPlaybackStatus();
    return PlaybackStatus::Stopped;
}

bool CurrentPlayer::getCanSeek() const
{
    if (currentPlayer)
        return currentPlayer->getCanSeek();
    return false;
}

bool CurrentPlayer::getCanGoNext() const
{
    if (currentPlayer)
        return currentPlayer->getCanGoNext();
    return false;
}

bool CurrentPlayer::getCanGoPrevious() const
{
    if (currentPlayer)
        return currentPlayer->getCanGoPrevious();
    return false;
}

bool CurrentPlayer::getCanAddToFavorites() const
{
    if (currentPlayer)
        return currentPlayer->getCanAddToFavorites();
    return false;
}

double CurrentPlayer::getVolume() const
{
    if (currentPlayer)
        return currentPlayer->getVolume();
    return 0;
}

void CurrentPlayer::onCurrentServiceChanged(StreamingService* streamingService)
{
    if (streamingService == nullptr)
        return;
    auto player = players.get(streamingService->getName());
    if (player != currentPlayer) {
        if (currentPlayer != nullptr) {
            disconnect(currentPlayer.get(), &Player::currentSongChanged, this, &CurrentPlayer::currentSongChanged);
            disconnect(currentPlayer.get(), &Player::positionChanged, this, &CurrentPlayer::positionChanged);
            disconnect(currentPlayer.get(), &Player::playbackStatusChanged, this, &CurrentPlayer::playbackStatusChanged);
            disconnect(currentPlayer.get(), &Player::canSeekChanged, this, &CurrentPlayer::canSeekChanged);
            disconnect(currentPlayer.get(), &Player::canGoNextChanged, this, &CurrentPlayer::canGoNextChanged);
            disconnect(currentPlayer.get(), &Player::canGoPreviousChanged, this, &CurrentPlayer::canGoPreviousChanged);
            disconnect(currentPlayer.get(), &Player::canAddToFavoritesChanged, this, &CurrentPlayer::canAddToFavoritesChanged);
            disconnect(currentPlayer.get(), &Player::volumeChanged, this, &CurrentPlayer::volumeChanged);
            disconnect(currentPlayer.get(), &Player::isPlayingChanged, this, &CurrentPlayer::isPlayingChanged);
            disconnect(currentPlayer.get(), &Player::isStoppedChanged, this, &CurrentPlayer::isStoppedChanged);
            currentPlayer->suspend();
        }

        currentPlayer = player;

        connect(currentPlayer.get(), &Player::currentSongChanged, this, &CurrentPlayer::currentSongChanged);
        connect(currentPlayer.get(), &Player::positionChanged, this, &CurrentPlayer::positionChanged);
        connect(currentPlayer.get(), &Player::playbackStatusChanged, this, &CurrentPlayer::playbackStatusChanged);
        connect(currentPlayer.get(), &Player::canSeekChanged, this, &CurrentPlayer::canSeekChanged);
        connect(currentPlayer.get(), &Player::canGoNextChanged, this, &CurrentPlayer::canGoNextChanged);
        connect(currentPlayer.get(), &Player::canGoPreviousChanged, this, &CurrentPlayer::canGoPreviousChanged);
        connect(currentPlayer.get(), &Player::canAddToFavoritesChanged, this, &CurrentPlayer::canAddToFavoritesChanged);
        connect(currentPlayer.get(), &Player::volumeChanged, this, &CurrentPlayer::volumeChanged);
        connect(currentPlayer.get(), &Player::isPlayingChanged, this, &CurrentPlayer::isPlayingChanged);
        connect(currentPlayer.get(), &Player::isStoppedChanged, this, &CurrentPlayer::isStoppedChanged);
        currentPlayer->resume();

        emit currentSongChanged(currentPlayer->getCurrentSong());
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

QString CurrentPlayer::getServiceName() const
{
    if (currentPlayer)
        return currentPlayer->getServiceName();
    return "";
}

bool CurrentPlayer::isPlaying() const
{
    if (currentPlayer)
        return currentPlayer->isPlaying();
    return false;
}

bool CurrentPlayer::isStopped() const
{
    if (currentPlayer)
        return currentPlayer->isStopped();
    return true;
}
