#pragma once

#include <QObject>

namespace MellowPlayer::Presentation
{
    class DevToolsWindowViewModel: public QObject
    {
        Q_OBJECT
    signals:
        void showDevTools();
    };
}
