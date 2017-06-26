#include <QApplication>
#include <QClipboard>
#include "MellowPlayer/Presentation/Models/ClipBoardModel.hpp"

USE_MELLOWPLAYER_NAMESPACE(Presentation)

ClipBoardModel::ClipBoardModel(QObject *parent) : QObject(parent) {

}

void ClipBoardModel::setText(const QString &text) {
    qApp->clipboard()->setText(text);
    emit textCopied(text);
}
