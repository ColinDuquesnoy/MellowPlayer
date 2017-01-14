#include "Song.hpp"

using namespace MellowPlayer::Entities;

Song::Song(QObject *parent)
    : QObject(parent), uniqueId_(""), title_(""), artist_(""), album_(""), artUrl_(""), duration_(0), position_(0), isFavorite_(false) {

}

QString Song::toString() const {
    return "Song(title=\"" + title_ + "\", artist=\"" + artist_ + "\", album=\"" + album_ + "\")";
}

QString Song::uniqueId() const {
    return uniqueId_;
}

QString Song::title() const {
    return title_;
}

void Song::setUniqueId(QString uniqueId) {
    if (uniqueId_ == uniqueId)
        return;

    uniqueId_ = uniqueId;
    emit uniqueIdChanged(uniqueId);
}

void Song::setTitle(QString title) {
    if (title_ == title)
        return;

    title_ = title;
    emit titleChanged(title);
}

QString Song::artist() const {
    return artist_;
}

QString Song::album() const {
    return album_;
}

QString Song::artUrl() const {
    return artUrl_;
}

double Song::duration() const {
    return duration_;
}

bool Song::isFavorite() const {
    return isFavorite_;
}

void Song::setArtist(QString artist) {
    if (artist_ == artist)
        return;

    artist_ = artist;
    emit artistChanged(artist);
}

void Song::setAlbum(QString album) {
    if (album_ == album)
        return;

    album_ = album;
    emit albumChanged(album);
}

void Song::setArtUrl(QString artUrl) {
    if (artUrl_ == artUrl)
        return;

    artUrl_ = artUrl;
    emit artUrlChanged(artUrl);
}

void Song::setDuration(double duration) {
    if (duration_ == duration)
        return;

    duration_ = duration;
    emit durationChanged(duration);
}

void Song::setIsFavorite(bool isFavorite) {
    if (isFavorite == isFavorite_)
        return;

    isFavorite_ = isFavorite;
    emit isFavoriteChanged(isFavorite);
}

