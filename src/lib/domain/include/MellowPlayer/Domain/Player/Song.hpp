#pragma once

#include <QtCore/QObject>
#include <memory>

namespace MellowPlayer::Domain
{
    class Song : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString uniqueId READ uniqueId CONSTANT)
        Q_PROPERTY(QString title READ title CONSTANT)
        Q_PROPERTY(QString artist READ artist CONSTANT)
        Q_PROPERTY(QString album READ album CONSTANT)
        Q_PROPERTY(QString artUrl READ artUrl CONSTANT)
        Q_PROPERTY(double duration READ duration NOTIFY durationChanged)
        Q_PROPERTY(bool isFavorite READ isFavorite NOTIFY isFavoriteChanged)

    public:
        Song();
        Song(const QString& uniqueId, const QString& title, const QString& artist, const QString& album, const QString& artUrl, double duration,
             bool isFavorite);

        QString uniqueId() const;
        QString title() const;
        QString artist() const;
        QString album() const;
        QString artUrl() const;
        double duration() const;
        bool isFavorite() const;

        void setDuration(double value);
        void setFavorite(bool value);
        void setArtUrl(const QString& artUrl);

        bool operator==(const Song& other) const
        {
            return uniqueId_ == other.uniqueId_;
        }
        bool operator!=(const Song& other) const
        {
            return !this->operator==(other);
        }

        Q_INVOKABLE bool isValid() const
        {
            return !uniqueId_.isEmpty() && !toString().isEmpty();
        }

        QString toString() const
        {
            if (!artist_.isEmpty())
                return title_ + " by " + artist_;
            else
                return title_;
        }

        std::shared_ptr<Song> clone() const
        {
            return std::make_shared<Song>(uniqueId(), title(), artist(), album(), artUrl(), duration(), isFavorite());
        }

    signals:
        void durationChanged();
        void isFavoriteChanged();
        void artUrlChanged();

    private:
        QString uniqueId_;
        QString title_;
        QString artist_;
        QString album_;
        QString artUrl_;
        double duration_; // in seconds
        bool isFavorite_;
    };
}
