#pragma once

#include <MellowPlayer/Domain/Properties.hpp>
#include <QtCore/QObject>

namespace MellowPlayer::Domain
{
    class WebPlayerScript : public QObject
    {
        Q_OBJECT
        READONLY_PROPERTY(QString, code, updateCode)
        CONSTANT_PROPERTY(QString, constants)
    public:
        WebPlayerScript();
        bool isValid() const;

        Q_INVOKABLE QString update() const;
        Q_INVOKABLE QString play() const;
        Q_INVOKABLE QString pause() const;
        Q_INVOKABLE QString next() const;
        Q_INVOKABLE QString previous() const;
        Q_INVOKABLE QString setVolume(double volume) const;
        Q_INVOKABLE QString addToFavorites() const;
        Q_INVOKABLE QString removeFromFavorites() const;
        Q_INVOKABLE QString seekToPosition(double position) const;

        virtual void load() = 0;
    };
}
