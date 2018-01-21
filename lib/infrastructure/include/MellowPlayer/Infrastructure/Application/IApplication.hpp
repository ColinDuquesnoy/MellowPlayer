#pragma once

#include <QtCore/QObject>

namespace MellowPlayer::Infrastructure
{
    class IApplication: public QObject
    {
        Q_OBJECT
    public:
        virtual void initialize() = 0;
        virtual int run() = 0;
        virtual void quit() = 0;
        virtual void restart() = 0;
        virtual void restoreWindow() = 0;

    signals:
        void initialized();
        void started();
        void finished();
        void restoreWindowRequest();
        void commitDataRequest();
    };
}
