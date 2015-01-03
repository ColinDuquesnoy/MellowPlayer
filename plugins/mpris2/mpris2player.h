#ifndef MPRIS2PLAYER_H
#define MPRIS2PLAYER_H

#include <QObject>
#include <QtDBus>
#include <mellowplayer.h>


/*!
 * \brief The Mpris2Player class implements the MPRIS Player Interface
 *
 * http://specifications.freedesktop.org/mpris-spec/latest/Player_Interface.html
 */
class Mpris2Player : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.mpris.MediaPlayer2.Player")

public:
    explicit Mpris2Player(QObject* parent=NULL);

    Q_PROPERTY(QVariantMap Metadata     READ metadata                          )
    Q_PROPERTY(bool     CanControl      READ canControl                        )
    Q_PROPERTY(bool     CanSeek         READ canSeek                           )
    Q_PROPERTY(bool     CanPause        READ canPause                          )
    Q_PROPERTY(bool     CanPlay         READ canPlay                           )
    Q_PROPERTY(bool     CanGoPrevious   READ canGoPrevious                     )
    Q_PROPERTY(bool     CanGoNext       READ canGoNext                         )
    Q_PROPERTY(int      Position        READ position                          )
    Q_PROPERTY(int      MinimuRate      READ minimumRate                       )
    Q_PROPERTY(int      MaximuRate      READ maximumRate                       )
    Q_PROPERTY(int      Rate            READ rate           WRITE setRate      )
    Q_PROPERTY(float    Volume          READ volume         WRITE setVolume    )
    Q_PROPERTY(int      Shuffle         READ shuffle        WRITE setShuffle   )
    Q_PROPERTY(QString  LoopStatus      READ loopStatus     WRITE setLoopStatus)
    Q_PROPERTY(QString  PlaybackStatus  READ playbackStatus                    )

public slots:
    void PlayPause();
    void Play();
    void Pause();
    void Stop();
    void Next();
    void Previous();
    void Seek(int position);

private slots:
    void onPlaybackStatusChanged(PlaybackStatus status);
    void onSongChanged(const SongInfo& song);
    void onArtReady(const QString& artFilePathUrl);

private:
    void signalUpdate(const QVariantMap &map);

    QString                 playbackStatus();
    QString                 loopStatus();
    void                    setLoopStatus(const QString& status);
    bool                    shuffle();
    void                    setShuffle(bool value);
    float                   volume();
    void                    setVolume(float);
    QVariantMap             metadata();
    float                   minimumRate();
    float                   maximumRate();
    float                   rate();
    void                    setRate(float value);
    int                     position();
    bool                    canGoNext();
    bool                    canGoPrevious();
    bool                    canPlay();
    bool                    canPause();
    bool                    canSeek();
    bool                    canControl();

    QMap<QString, QVariant> toXesam(const SongInfo& song,
                                    const QString& artFilePathUrl="");

};

#endif // MPRIS2PLAYER_H
