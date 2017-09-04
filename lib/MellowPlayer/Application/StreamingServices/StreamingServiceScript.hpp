#pragma once

#include <QtCore/QObject>

namespace MellowPlayer::Application
{
    class StreamingServiceScript : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString code READ code NOTIFY codeChanged);
        Q_PROPERTY(QString path READ path CONSTANT);

    public:
        StreamingServiceScript(const QString& code, const QString& path);

        bool isValid() const;

        QString constants() const;

        QString code() const;
        void setCode(const QString& value);

        const QString& path() const;

        Q_INVOKABLE QString update() const;
        Q_INVOKABLE QString play() const;
        Q_INVOKABLE QString pause() const;
        Q_INVOKABLE QString next() const;
        Q_INVOKABLE QString previous() const;
        Q_INVOKABLE QString setVolume(double volume) const;
        Q_INVOKABLE QString addToFavorites() const;
        Q_INVOKABLE QString removeFromFavorites() const;
        Q_INVOKABLE QString seekToPosition(double position) const;

    signals:
        void codeChanged(QString);

    private:
        QString code_;
        QString path_;
    };
}
