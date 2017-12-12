#pragma once

#include <QObject>

namespace MellowPlayer::Presentation
{
    class IMainWindow: public QObject
    {
        Q_OBJECT
    public:
        virtual ~IMainWindow() override;

        virtual void load() = 0;
        virtual void show() = 0;
        virtual void hide() = 0;
        virtual void requestQuit() = 0;

    signals:
        void forceQuitRequest();
    };
}
