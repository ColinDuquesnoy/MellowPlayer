#include <MellowPlayer/Domain/Player/Song.hpp>
#include <cmath>

using namespace std;
using namespace MellowPlayer::Domain;

Song::Song() : duration_(0), isFavorite_(false)
{
}

Song::Song(const QString& uniqueId, const QString& title, const QString& artist, const QString& album, const QString& artUrl, double duration,
           bool isFavorite)
        : uniqueId_(uniqueId), title_(title), artist_(artist), album_(album), artUrl_(artUrl), duration_(duration), isFavorite_(isFavorite)
{
}

QString Song::uniqueId() const
{
    return uniqueId_;
}

QString Song::title() const
{
    return title_;
}

QString Song::artist() const
{
    return artist_;
}

QString Song::album() const
{
    return album_;
}

QString Song::artUrl() const
{
    return artUrl_;
}

double Song::duration() const
{
    return duration_;
}

bool Song::isFavorite() const
{
    return isFavorite_;
}

void Song::setDuration(double value)
{
    if (abs(duration_ - value) < 2)
        return;

    duration_ = value;
    emit durationChanged();
}

void Song::setFavorite(bool value)
{
    if (value == isFavorite_)
        return;

    isFavorite_ = value;
    emit isFavoriteChanged();
}

void Song::setArtUrl(const QString& artUrl)
{
    if (artUrl != artUrl_) {
        artUrl_ = artUrl;
        emit artUrlChanged();
    }
}
