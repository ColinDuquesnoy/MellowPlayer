#ifndef PLAYBACKSTATUS
#define PLAYBACKSTATUS

#include <QString>

/*!
 * \brief The PlaybackStatus enum enumerates the possible playback status of
 * a song.
 */
enum PlaybackStatus
{
    /*!
      Song is playing
      */
    Playing,
    /*!
      Song has been paused
      */
    Paused,
    /*!
      Song has been stopped
      */
    Stopped,
    /*!
      Song is buffering.
      */
    Buffering
};

/*!
 * \brief Converts a playback status value to a string
 * \param status Status to convert
 * \return String representation of the playback status
 */
inline QString playbackStatusToString(PlaybackStatus status)
{
    switch (status) {
    case Playing:
        return "Playing";
    case Paused:
        return "Paused";
    case Stopped:
        return "Stopped";
    case Buffering:
        return "Buffering";
    }
    return "";
}

#endif // PLAYBACKSTATUS

