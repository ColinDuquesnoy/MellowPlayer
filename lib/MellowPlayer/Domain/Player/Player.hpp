#pragma once

#include "IPlayer.hpp"
#include <memory>

class QTimer;

namespace MellowPlayer::Domain
{
    class ILogger;
    class Song;
    class StreamingService;
    class StreamingServiceScript;

    class Player : public IPlayer
    {
        Q_OBJECT
        Q_PROPERTY(bool isRunning READ isRunning NOTIFY isRunningChanged)
    public:
        explicit Player(Domain::StreamingService& streamingService);
        ~Player() override;

        // IPlayer
        Q_INVOKABLE void togglePlayPause() override;
        Q_INVOKABLE void play() override;
        Q_INVOKABLE void pause() override;
        Q_INVOKABLE void next() override;
        Q_INVOKABLE void previous() override;
        Q_INVOKABLE void seekToPosition(double value) override;
        Q_INVOKABLE void setVolume(double volume) override;
        Q_INVOKABLE void toggleFavoriteSong() override;
        Q_INVOKABLE void addToFavorites() override;
        Q_INVOKABLE void removeFromFavorites() override;

        Domain::Song* currentSong() override;
        double position() const override;
        PlaybackStatus playbackStatus() const override;
        bool canSeek() const override;
        bool canGoNext() const override;
        bool canGoPrevious() const override;
        bool canAddToFavorites() const override;
        double volume() const override;
        QString serviceName() const override;
        bool isPlaying() const override;
        bool isStopped() const override;

        // invoked by WebView (QML)
        Q_INVOKABLE void start();
        Q_INVOKABLE void stop();
        Q_INVOKABLE bool isRunning() const;
        Q_INVOKABLE void setUpdateResults(const QVariant& results);

        // invoked by CurrentPlayer
        void suspend();
        void resume();

        bool operator==(const Player& other) const;
        bool operator!=(const Player& other) const;

        void setPlaybackStatus(PlaybackStatus value);

    signals:
        void runJavascriptRequested(const QString& script);
        void updateRequested(const QString& script);
        void isRunningChanged();

    public slots:
        void refresh();
        void loadPlugin();

    private:
        void setCurrentSong(std::unique_ptr<Domain::Song>& song);
        void setPosition(double value);
        void setCanSeek(bool value);
        void setCanGoNext(bool value);
        void setCanGoPrevious(bool value);
        void setCanAddToFavorites(bool value);
        void setCurrentVolume(double value);

        ILogger& logger_;
        double position_ = false;
        PlaybackStatus playbackStatus_ = PlaybackStatus::Stopped;
        bool canSeek_ = false;
        bool canGoNext_ = false;
        bool canGoPrevious_ = false;
        bool canAddToFavorites_ = false;
        double volume_ = 1;
        std::unique_ptr<Domain::Song> currentSong_;
        Domain::StreamingService& streamingService_;
        Domain::StreamingServiceScript& streamingServiceScript_;
        PlaybackStatus suspendedState_ = PlaybackStatus::Stopped;
        bool isRunning_ = false;
        std::unique_ptr<QTimer> refreshTimer_;
    };
}
