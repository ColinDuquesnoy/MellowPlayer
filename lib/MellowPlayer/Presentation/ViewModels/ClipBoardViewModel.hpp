#pragma once

#include <QObject>
#include <MellowPlayer/Macros.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class ClipBoardViewModel: public QObject {
    Q_OBJECT
public:
    ClipBoardViewModel(QObject* parent= nullptr);

    Q_INVOKABLE void setText(const QString& text);
};

END_MELLOWPLAYER_NAMESPACE
