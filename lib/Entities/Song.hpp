#pragma once

#include <Common/Macros.hpp>
#include <QtCore>
#include <chrono>

BEGIN_MELLOWPLAYER_NAMESPACE(Entities)

/**
 * @brief The Song class holds the information about a song (title, artist, album, ...).
 */
class Song: public QObject
{
    Q_OBJECT
    /**
     * @brief The unique id of the song.
     */
    Q_PROPERTY(QString uniqueId READ uniqueId WRITE setUniqueId NOTIFY uniqueIdChanged)

    /**
     * @brief The title of the song.
     */
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)

    /**
     * @brief The name of the artist.
     */
    Q_PROPERTY(QString artist READ artist WRITE setArtist NOTIFY artistChanged)

    /**
     * @brief The name of the album.
     */
    Q_PROPERTY(QString album READ album WRITE setAlbum NOTIFY albumChanged)

    /**
     * @brief The song art url. Optional.
     */
    Q_PROPERTY(QString artUrl READ artUrl WRITE setArtUrl NOTIFY artUrlChanged)

    /**
     * @brief The duration of the song [seconds].
     */
    Q_PROPERTY(double duration READ duration WRITE setDuration NOTIFY durationChanged)

    /**
     * @bried
     */
    Q_PROPERTY(bool isFavorite READ isFavorite WRITE setIsFavorite NOTIFY isFavoriteChanged)
public:
    explicit Song(QObject* parent= nullptr);

    QString toString() const;

    QString uniqueId() const;
    QString title() const;
    QString artist() const;
    QString album() const;
    QString artUrl() const;
    double duration() const;
    bool isFavorite() const;

public slots:
    void setUniqueId(QString uniqueId);
    void setTitle(QString title);
    void setArtist(QString artist);
    void setAlbum(QString album);
    void setArtUrl(QString artUrl);
    void setDuration(double duration);
    void setIsFavorite(bool isFavorite);

signals:
    void uniqueIdChanged(QString uniqueId);
    void titleChanged(QString title);
    void artistChanged(QString artist);
    void albumChanged(QString album);
    void artUrlChanged(QString artUrl);
    void durationChanged(double duration);
    void isFavoriteChanged(bool favorite);

private:
    QString uniqueId_;
    QString title_;
    QString artist_;
    QString album_;
    QString artUrl_;
    double duration_;
    double position_;
    bool isFavorite_;
};

END_MELLOWPLAYER_NAMESPACE
