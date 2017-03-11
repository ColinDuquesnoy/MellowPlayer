#pragma once

#include <QObject>
#include <QtDBus>
#include <MellowPlayer/Macros.hpp>
#include <MellowPlayer/UseCases.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class Mpris2Player : public QDBusAbstractAdaptor {
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.mpris.MediaPlayer2.Player")
public:
    explicit Mpris2Player(UseCases::IPlayer& player, UseCases::LocalAlbumArtService& localAlbumArt, QObject *parent=nullptr);

    Q_PROPERTY(QVariantMap Metadata READ metadata)
    Q_PROPERTY(bool CanControl READ canControl)
    Q_PROPERTY(bool CanSeek READ canSeek)
    Q_PROPERTY(bool CanPause READ canPause)
    Q_PROPERTY(bool CanPlay READ canPlay)
    Q_PROPERTY(bool CanStope READ canStop)
    Q_PROPERTY(bool CanGoPrevious READ canGoPrevious)
    Q_PROPERTY(bool CanGoNext READ canGoNext)
    Q_PROPERTY(qlonglong Position READ position)
    Q_PROPERTY(int MinimuRate READ minimumRate)
    Q_PROPERTY(int MaximuRate READ maximumRate)
    Q_PROPERTY(int Rate READ rate WRITE setRate)
    Q_PROPERTY(double Volume READ volume WRITE setVolume)
    Q_PROPERTY(int Shuffle READ shuffle WRITE setShuffle)
    Q_PROPERTY(QString LoopStatus READ loopStatus WRITE setLoopStatus)
    Q_PROPERTY(QString PlaybackStatus READ playbackStatus)

    QString playbackStatus();
    QString loopStatus();
    void setLoopStatus(const QString &status);
    bool shuffle();
    void setShuffle(bool value);
    double volume();
    void setVolume(double value);
    QVariantMap metadata();
    double minimumRate();
    double maximumRate();
    double rate();
    void setRate(float value);
    qlonglong position();
    bool canGoNext();
    bool canGoPrevious();
    bool canPlay();
    bool canStop();
    bool canPause();
    bool canSeek();
    bool canControl();

public slots:
    void PlayPause();
    void Play();
    void Pause();
    void Stop();
    void Next();
    void Previous();
    void Seek(qlonglong position);
    void SetPosition(const QDBusObjectPath &trackId, qlonglong position);

signals:
    void Seeked(qlonglong);

private slots:
    void onPlaybackStatusChanged();
    void onSongChanged(Entities::Song* song);
    void onArtUrlChanged();
    void onPositionChanged();
    void onDurationChanged();
    void onCanSeekChanged();
    void onCanGoPreviousChanged();
    void onCanGoNextChanged();
    void onVolumeChanged();

private:
    QMap<QString, QVariant> toXesam(const Entities::Song& song);
    QString statusToString(UseCases::IPlayer::PlaybackStatus status);
    void signalPlayerUpdate(const QVariantMap &map);
    void signalUpdate(const QVariantMap &map, const QString &interfaceName);

    qlonglong m_length;
    qlonglong previousPosition;
    UseCases::IPlayer& player;
    UseCases::LocalAlbumArtService& localAlbumArt;
    QMap<QString, QVariant> lastMetadata;
};

END_MELLOWPLAYER_NAMESPACE
