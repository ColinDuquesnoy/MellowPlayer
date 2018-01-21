#include <MellowPlayer/Presentation/ViewModels/ClipBoardViewModel.hpp>
#include <QApplication>
#include <QClipboard>

using namespace MellowPlayer::Presentation;

ClipBoardViewModel::ClipBoardViewModel(IContextProperties& contextProperties)
        : ContextProperty("_clipboard", this, contextProperties)
{
}

void ClipBoardViewModel::setText(const QString& text)
{
    qApp->clipboard()->setText(text);
    emit textCopied(text);
}

bool ClipBoardViewModel::canPaste() const
{
    return !qApp->clipboard()->text().isEmpty();
}
