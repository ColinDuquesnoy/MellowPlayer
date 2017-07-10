#pragma once

#include <QObject>

namespace MellowPlayer::Presentation {

    class ClipBoardViewModel: public QObject {
        Q_OBJECT
    public:
        ClipBoardViewModel(QObject* parent= nullptr);

        Q_INVOKABLE void setText(const QString& text);

    signals:
        void textCopied(const QString& text);
    };

}
