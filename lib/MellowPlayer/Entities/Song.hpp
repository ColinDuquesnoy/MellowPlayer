#pragma once

#include <QtCore/QObject>
#include <MellowPlayer/Macros.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(Entities)

class Song: public QObject {
    Q_OBJECT
    Q_PROPERTY(QString uniqueId READ getUniqueId CONSTANT)
    Q_PROPERTY(QString title READ getTitle CONSTANT)
    Q_PROPERTY(QString artist READ getArtist CONSTANT)
    Q_PROPERTY(QString album READ getAlbum CONSTANT)
    Q_PROPERTY(QString artUrl READ getArtUrl CONSTANT)
    Q_PROPERTY(double duration READ getDuration NOTIFY durationChanged)
    Q_PROPERTY(bool isFavorite READ getIsFavorite NOTIFY isFavoriteChanged)

public:
    Song();
    Song(const QString& uniqueId, const QString& title, const QString& artist, const QString& album,
         const QString& artUrl, double duration, bool isFavorite);

    QString getUniqueId() const;
    QString getTitle() const;
    QString getArtist() const;
    QString getAlbum() const;
    QString getArtUrl() const;
    double getDuration() const;
    bool getIsFavorite() const;

    void setDuration(double value);
    void setIsFavorite(bool value);

    bool operator==(const Song& other) const { return uniqueId == other.uniqueId; }
    bool operator!=(const Song& other) const { return !this->operator==(other); }

signals:
    void durationChanged();
    void isFavoriteChanged();

private:
    QString uniqueId;
    QString title;
    QString artist;
    QString album;
    QString artUrl;
    double duration; // in seconds
    bool isFavorite;
};

END_MELLOWPLAYER_NAMESPACE
