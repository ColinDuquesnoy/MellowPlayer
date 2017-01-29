#pragma once

#include <MellowPlayer/Macros.hpp>
#include <QtCore/QString>

BEGIN_MELLOWPLAYER_NAMESPACE(Entities)

/**
 * @brief The song structure contains the data of the current song.
 */
struct Song {
    /**
     * @brief Unique id of the song.
     */
    QString uniqueId;

    /**
     * @brief Title of the song.
     */
    QString title;

    /**
     * @brief Name of the artist.
     */
    QString artist;

    /**
     * @brief Name of the album
     */
    QString album;

    /**
     * @brief Album art url.
     */
    QString artUrl;

    /**
     * @brief Duration of the seconds (number of seconds).
     */
    double duration;

    /**
     * @brief Whether the song is part of the favorites song of the user.
     */
    bool isFavorite;

    Song()
        : uniqueId(""),
          title(""),
          artist(""),
          album(""),
          artUrl(""),
          duration(0),
          isFavorite(false) {

    }
};

END_MELLOWPLAYER_NAMESPACE
