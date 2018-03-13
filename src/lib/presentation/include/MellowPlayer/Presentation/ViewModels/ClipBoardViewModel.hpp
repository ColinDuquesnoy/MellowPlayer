#pragma once

#include <QObject>
#include <MellowPlayer/Presentation/Qml/ContextProperty.hpp>

namespace MellowPlayer::Presentation
{
    class ClipBoardViewModel : public QObject, public ContextProperty
    {
        Q_OBJECT
    public:
        explicit ClipBoardViewModel(IContextProperties& contextProperties);

        Q_INVOKABLE void setText(const QString& text);
        Q_INVOKABLE bool canPaste() const;

    signals:
        void textCopied(const QString& text);
    };
}
