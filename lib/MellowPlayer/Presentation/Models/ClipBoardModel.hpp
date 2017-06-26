#pragma once

#include <QObject>
#include <MellowPlayer/Macros.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class ClipBoardModel: public QObject {
    Q_OBJECT
public:
    ClipBoardModel(QObject* parent= nullptr);

    Q_INVOKABLE void setText(const QString& text);

signals:
    void textCopied(const QString& text);
};

END_MELLOWPLAYER_NAMESPACE
