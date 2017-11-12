#pragma once

#include <QObject>

namespace MellowPlayer::Domain
{
    class IDeprecatedQtApplication : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString buildInfo READ buildInfo CONSTANT)
    public:
        virtual ~IDeprecatedQtApplication();

        virtual void initialize() = 0;
        virtual int run() = 0;
        Q_INVOKABLE virtual void clearCache() const = 0;
        Q_INVOKABLE virtual void clearCookies() const = 0;
        Q_INVOKABLE virtual void requestQuit() = 0;
        Q_INVOKABLE virtual void restart() = 0;
        Q_INVOKABLE virtual void quit() = 0;
        virtual QString buildInfo() const = 0;

        virtual bool restartRequested() const = 0;

    signals:
        void quitRequested();
    };
}
