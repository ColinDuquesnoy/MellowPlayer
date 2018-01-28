#pragma once

#include <QObject>
#include <MellowPlayer/Presentation/Qml/ContextProperty.hpp>

namespace MellowPlayer::Presentation
{
    class DevToolsWindowViewModel: public QObject, public ContextProperty
    {
        Q_OBJECT
    public:
        DevToolsWindowViewModel(IContextProperties& contextProperties);
    signals:
        void showDevTools();
    };
}
