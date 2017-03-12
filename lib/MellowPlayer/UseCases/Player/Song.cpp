#include "Song.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)

Song::Song() : uniqueId(""), title(""), artist(""), album(""), artUrl(""), duration(0), isFavorite(false) {
}

Song::Song(const QString& uniqueId, const QString& title, const QString& artist, const QString& album,
           const QString& artUrl, double duration, bool isFavorite) :
        uniqueId(uniqueId), title(title), artist(artist), album(album), artUrl(artUrl), duration(duration),
        isFavorite(isFavorite) {
}

QString Song::getUniqueId() const {
    return uniqueId;
}

QString Song::getTitle() const {
    return title;
}

QString Song::getArtist() const {
    return artist;
}

QString Song::getAlbum() const {
    return album;
}

QString Song::getArtUrl() const {
    return artUrl;
}

double Song::getDuration() const {
    return duration;
}

bool Song::getIsFavorite() const {
    return isFavorite;
}

void Song::setDuration(double value) {
    if (value == duration)
        return;

    duration = value;
    emit durationChanged();
}

void Song::setIsFavorite(bool value) {
    if (value == isFavorite)
        return;

    isFavorite = value;
    emit isFavoriteChanged();
}
