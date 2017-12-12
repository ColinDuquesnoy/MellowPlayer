#pragma once

#include <QtCore/QObject>
#include <MellowPlayer/Presentation/Qml/ContextProperty.hpp>

namespace MellowPlayer::Presentation
{
    class CacheViewModel: public QObject, public ContextProperty
    {
        Q_OBJECT
    public:
        explicit CacheViewModel(IContextProperties& contextProperties);

        Q_INVOKABLE void clear();
    };
}
