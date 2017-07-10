#include <QApplication>
#include <QClipboard>
#include "ClipBoardViewModel.hpp"

using namespace MellowPlayer::Presentation;

ClipBoardViewModel::ClipBoardViewModel(QObject *parent) : QObject(parent) {

}

void ClipBoardViewModel::setText(const QString &text) {
    qApp->clipboard()->setText(text);
    emit textCopied(text);
}
