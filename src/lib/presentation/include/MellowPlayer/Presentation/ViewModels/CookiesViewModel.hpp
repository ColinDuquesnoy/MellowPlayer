#pragma once

#include <QtCore/QObject>
#include <MellowPlayer/Presentation/Qml/ContextProperty.hpp>

namespace MellowPlayer::Presentation
{
    class CookiesViewModel: public QObject, public ContextProperty
    {
        Q_OBJECT
    public:
        explicit CookiesViewModel(IContextProperties& contextProperties);

        Q_INVOKABLE void clear();
    };
}
